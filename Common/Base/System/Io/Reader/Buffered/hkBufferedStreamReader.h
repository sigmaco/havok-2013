/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKBASE_BUFFERED_STREAMREADER_H
#define HKBASE_BUFFERED_STREAMREADER_H

#include <Common/Base/System/Io/Reader/hkStreamReader.h>

#define HK_BUFFERED_STREAM_DEFAULT_READ_BUFSIZE (16*1024)

	/// Wraps and buffers an existing unbuffered stream.
	/// This takes care of any alignment requirements from the underlying stream
	/// (e.g. read only multiples of N bytes, read to M-byte-aligned addresses).
	/// A side effect of buffering is that peek() becomes available.
class hkBufferedStreamReader : public hkSeekableStreamReader
{
	public:
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
			/// Create a buffered stream from stream 's' with size 'bufSize'.
			/// Adds a reference to 's'.
		hkBufferedStreamReader(hkStreamReader* s, int bufSize=HK_BUFFERED_STREAM_DEFAULT_READ_BUFSIZE);

			/// Removes reference to the reader in the constructor if applicable.
		~hkBufferedStreamReader();

		virtual int read(void* buf, int nbytes);

		virtual int skip(int nbytes);

		virtual int peek(void* buf, int nbytes);

		virtual hkBool isOk() const;

		virtual hkSeekableStreamReader* isSeekTellSupported();

		virtual hkResult seek( int offset, SeekWhence whence);

		virtual int tell() const;

	protected:

		hkStreamReader* m_stream; // child stream
		hkSeekableStreamReader* m_seekStream; // set only if child stream is seekable

		struct Buffer
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE_CLASS, hkBufferedStreamReader::Buffer );

			Buffer(int cap);
			~Buffer();
			char* begin;
			int current; // current byte index
			int size; // end of usable buffer size - only less than capacity on short read
			int capacity; // buffer region is begin,begin+m_capacity
		};

		Buffer m_buf;
};

#endif //HKBASE_BUFFERED_STREAMREADER_H

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
