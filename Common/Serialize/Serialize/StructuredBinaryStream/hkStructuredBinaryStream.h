/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#ifndef	HK_STRUCTURED_BINARY_STREAM
#define HK_STRUCTURED_BINARY_STREAM

#include <Common/Base/Types/Geometry/Aabb/hkAabb.h>

//
// Stream base.
//
// 4 bytes : scope(BRANCH or VALUE or ARRAY), size and type. 
// 4 bytes : ID
//		* Others scopes
//		or
//		* Data, x bytes.
//
struct hkStructuredBinaryStream
{
	struct DefaultSerializer
	{
		template <typename T, typename W> static void save(const T& value, W& writer)	{ value.save(writer); }
		template <typename T, typename R> static void load(T& value, R& reader)			{ value.load(reader); }
	};

	struct WriterStream
	{
		WriterStream(hkArray<hkUint8>& buffer) : m_buffer(buffer) {}
		void* expandBy(int n) { return m_buffer.expandBy(n); }
		int getUsed() const { return m_buffer.getSize(); }
		void* access(int off) { return &m_buffer[off]; }
	protected:
		hkArray<hkUint8>&	m_buffer;
	};

	struct FixedWriterStream
	{
		FixedWriterStream(void* buf, int bufSize) : m_buffer(buf), m_bufferSize(bufSize), m_used(0) {}
		void* expandBy(int n)
		{
			HK_ASSERT(0x32acdfc8, m_used+n < m_bufferSize);
			void* p = hkAddByteOffset(m_buffer, m_used);
			m_used += n;
			return p;
		}
		int getUsed() const { return m_used; }
		void* access(int off) { return hkAddByteOffset(m_buffer, off); }
	protected:
		void* m_buffer;
		int m_bufferSize;
		int m_used;
	};

	template< int N >
	struct InplaceWriterStream : public FixedWriterStream
	{
		InplaceWriterStream() : FixedWriterStream(m_buffer, N) {}
		char m_buffer[N];
	};

	struct ReaderStream
	{
		ReaderStream(const hkArray<hkUint8>& buffer) : m_buffer(buffer.begin()), m_length(buffer.getSize()), m_cursor(0) {}
		ReaderStream(const void* buf, int bufSize) : m_buffer( static_cast<const hkUint8*>(buf)), m_length(bufSize), m_cursor(0) {}

		const hkUint8*	m_buffer;
		int				m_length;
		int				m_cursor;
	};

protected:	

	enum HeadType { BRANCH=0, VALUE=1, ARRAY=2 };

	~hkStructuredBinaryStream() { HK_ASSERT2(0xF4E42CEE, m_scopes.getSize() == 0, "Scopes still open on destruction"); }

	hkInplaceArray<int,16>	m_scopes;
};

//
// Writer.
//
template
<
	typename WRITER_STREAM = hkStructuredBinaryStream::WriterStream,
	typename SERIALIZER = hkStructuredBinaryStream::DefaultSerializer
>
struct hkStructuredBinaryStreamWriter : public hkStructuredBinaryStream
{
	typedef WRITER_STREAM StreamType;

	/// Construtor.
	hkStructuredBinaryStreamWriter(WRITER_STREAM& stream) : hkStructuredBinaryStream(), m_stream(stream) {}

	//
	// Queries.
	//

	/// Get a read-write reference to the underlying stream.
	WRITER_STREAM&		getStream() { return m_stream; }

	/// Get a read-only reference to the underlying stream.
	const WRITER_STREAM&	getStream() const { return m_stream; }
	
	//
	// Scopes.
	//

	/// Open a new branch scope.
	inline void	openBranch(hkUint32 branchId) { openScope(BRANCH, branchId); }

	/// Open a new branch scope.
	inline void	openValue(hkUint32 valueId) { openScope(VALUE, valueId); }

	/// Close the current branch or value scope.
	inline void	close() { closeScope(); }

	//
	// Values.
	//

	/// Write a value.
	template <typename T>
	inline void	writeValue(const T& value, hkUint32 valueId);

	/// Write a sequence of values.
	template <typename T>
	inline void	writeValues(const T* values, int count, hkUint32 valueId);

	//
	// Arrays.
	//

	/// Write an array.
	template <typename T>
	inline void	writeArray(const hkArrayBase<T>& values, hkUint32 arrayId);

	//
	// Data.
	//

	/// Write an hkUint8 data type.
	inline void	writeData(char value) { write(value, m_stream.expandBy(1)); }

	/// Write an hkUint8 data type.
	inline void	writeData(hkUint8 value) { write(value, m_stream.expandBy(1)); }

	/// Write an hkInt8 data type.
	inline void	writeData(hkInt8 value) { write(value, m_stream.expandBy(1)); }

	/// Write an hkUint16 data type.
	inline void	writeData(hkUint16 value) { write(value, m_stream.expandBy(2)); }

	/// Write an hkInt16 data type.
	inline void	writeData(hkInt16 value) { write(value, m_stream.expandBy(2)); }

	/// Write an hkUint32 data type.
	inline void	writeData(hkUint32 value) { write(value, m_stream.expandBy(4)); }

	/// Write an hkInt32 data type.
	inline void	writeData(hkInt32 value) { write(value, m_stream.expandBy(4)); }

	/// Write an hkUint64 data type.
	inline void	writeData(hkUint64 value) { write(value, m_stream.expandBy(8)); }

	/// Write an hkInt64 data type.
	inline void	writeData(hkInt64 value) { write(value, m_stream.expandBy(8)); }

	/// Write an hkReal data type.
	inline void	writeData(hkReal value) { write(value, m_stream.expandBy(sizeof(hkReal))); }

	/// Write an hkVector4 data type.
	inline void writeData(const hkVector4& value) { writeData(value(0)); writeData(value(1)); writeData(value(2)); writeData(value(3)); }

	/// Write an hkAabb data type.
	inline void writeData(const hkAabb& value) { writeData(value.m_min); writeData(value.m_max); }

	/// Write a self-serialized data type.
	template <typename T>
	inline void writeData(const T& value) { SERIALIZER::save(value, *this); }

	/// Write an array of data.
	template <typename T>
	inline void writeData(const T* values, int count) { for(int i=0; i<count; ++i) writeData(values[i]); }

private:

	/// Open a scope.
	inline void	openScope(HeadType type, hkUint32 id);
	
	/// Close a scope.
	inline void	closeScope();
	
	/// Write
	template <typename T>
	inline void write(const T& src, void* dst);

	/// Create an head from a type and a size.
	static HK_FORCE_INLINE hkUint32	getHead(HeadType type, int size) { return (hkUint32) ((size << 2) | type); }
	
	WRITER_STREAM&	m_stream;
};

//
// Reader.
//
template <typename SERIALIZER = hkStructuredBinaryStream::DefaultSerializer>
struct hkStructuredBinaryStreamReader : public hkStructuredBinaryStream
{
	/// Can match any ID.
	enum { ANY_ID = 0xffffffff };

	/// Construtor.
	hkStructuredBinaryStreamReader(ReaderStream& stream) : hkStructuredBinaryStream(), m_stream(stream) {}
	
	//
	// Queries.
	//

	/// Get a read-write reference to the underlying stream.
	ReaderStream&		getStream() { return m_stream; }

	/// Get a read-only reference to the underlying stream.
	const ReaderStream&	getStream() const { return m_stream; }

	/// Return true if the end of the stream has been reached.
	inline bool			eof() const { return m_scopes.isEmpty() && m_stream.m_cursor == (hkUint32)m_stream.m_length; }

	/// Return the current branch, array or value ID.
	inline hkUint32		peek() const { hkUint32 id; peek(m_stream.m_cursor + 4, &id); return id; }

	//
	// Scopes.
	//

	/// Enter a scope.
	inline void		enter(hkUint32 id = ANY_ID, HeadType type = BRANCH);

	/// Skip a scope.
	inline void		skip(hkUint32 id = ANY_ID) { enter(id); m_stream.m_cursor += getLength() - 8; leave(); }
	
	/// Leave the current scope and move the next.
	inline void		leave(hkUint32 id = ANY_ID);
	
	/// Return the length of the current scope.
	inline int		getLength() const { hkUint32 head; peek(m_scopes.back(),&head); return (int)(head >> 2); }

	/// Return the type of the current scope.
	inline HeadType getType() const { hkUint32 head; peek(m_scopes.back(),&head); return (HeadType)(head & 3); }

	/// Return the ID of the current scope.
	inline hkUint32 getID() const { hkUint32 id; peek(m_scopes.back() + 4,&id); return id; }

	//
	// Values.
	//

	/// Read a value.
	template <typename T>
	inline void		readValue(T& value, hkUint32 id = ANY_ID);

	/// Read a sequence of values.
	template <typename T>
	inline void		readValues(T* values, int count, hkUint32 id = ANY_ID);

	//
	// Arrays.
	//

	///
	template <typename T>
	inline void		readArray(hkArray<T>& values, hkUint32 id = ANY_ID);

	//
	// Data.
	//

	/// Read a char data type.
	inline void	readData(char& value) { read(&value); }

	/// Read an hkUint8 data type.
	inline void	readData(hkUint8& value) { read(&value); }

	/// Read an hkInt8 data type.
	inline void	readData(hkInt8& value) { read(&value); }

	/// Read an hkUint16 data type.
	inline void	readData(hkUint16& value) { read(&value); }

	/// Read an hkInt16 data type.
	inline void	readData(hkInt16& value) { read(&value); }

	/// Read an hkUint32 data type.
	inline void	readData(hkUint32& value) { read(&value); }

	/// Read an hkInt32 data type.
	inline void	readData(hkInt32& value) { read(&value); }

	/// Read an hkUint64 data type.
	inline void	readData(hkUint64& value) { read(&value); }

	/// Read an hkInt64 data type.
	inline void	readData(hkInt64& value) { read(&value); }

	/// Read an hkReal data type.
	inline void	readData(hkReal& value) { read(&value); }

	/// Read an hkVector4 data type.
	inline void	readData(hkVector4& value) { readData(value(0)); readData(value(1)); readData(value(2)); readData(value(3)); }

	/// Read an hkAabb data type.
	inline void	readData(hkAabb& value) { readData(value.m_min); readData(value.m_max); }

	/// Read a self-serialized data type.
	template <typename T>
	inline void	readData(T& value) { SERIALIZER::load(value, *this); }

	/// Read an array of data.
	template <typename T>
	inline void	readData(T* values, int count) { for(int i=0; i<count; ++i) readData(values[i]); }

private:

	/// Peek.
	template <typename T>
	inline void	peek(int from, T* value) const;

	/// Read.
	template <typename T>
	inline void	read(T* value) { peek(m_stream.m_cursor, value); m_stream.m_cursor += sizeof(T); }

	ReaderStream&	m_stream;
};


#include <Common/Serialize/Serialize/StructuredBinaryStream/hkStructuredBinaryStream.inl>

#endif // HK_STRUCTURED_BINARY_STREAM

/*
 * Havok SDK - NO SOURCE PC DOWNLOAD, BUILD(#20130718)
 * 
 * Confidential Information of Havok.  (C) Copyright 1999-2013
 * Telekinesys Research Limited t/a Havok. All Rights Reserved. The Havok
 * Logo, and the Havok buzzsaw logo are trademarks of Havok.  Title, ownership
 * rights, and intellectual property rights in the Havok software remain in
 * Havok and/or its suppliers.
 * 
 * Use of this software for evaluation purposes is subject to and indicates
 * acceptance of the End User licence Agreement for this product. A copy of
 * the license is included with this software and is also available at www.havok.com/tryhavok.
 * 
 */
