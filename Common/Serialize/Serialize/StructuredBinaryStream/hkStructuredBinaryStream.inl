/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

//
// Writer.
//

//
template <typename STREAM_WRITER, typename SERIALIZER>
template <typename T>
inline void	hkStructuredBinaryStreamWriter<STREAM_WRITER, SERIALIZER>::writeValue(const T& value, hkUint32 valueId)
{
	openScope(VALUE, valueId);
	writeData(value);
	close();
}

//
template <typename STREAM_WRITER, typename SERIALIZER>
template <typename T>
inline void	hkStructuredBinaryStreamWriter<STREAM_WRITER, SERIALIZER>::writeValues(const T* values, int count, hkUint32 valueId)
{
	openScope(VALUE, valueId);
	writeData(values, count);
	close();
}

//
template <typename STREAM_WRITER, typename SERIALIZER>
template <typename T>
inline void	hkStructuredBinaryStreamWriter<STREAM_WRITER, SERIALIZER>::writeArray(const hkArrayBase<T>& values, hkUint32 arrayId)
{
	openScope(ARRAY, arrayId);
	writeData((hkUint32)values.getSize());
	for(int i=0; i<values.getSize(); ++i) writeData(values[i]);
	close();
}

//
template <typename STREAM_WRITER, typename SERIALIZER>
inline void	hkStructuredBinaryStreamWriter<STREAM_WRITER, SERIALIZER>::openScope(HeadType type, hkUint32 id)
{
	m_scopes.pushBack(m_stream.getUsed());
	*((hkUint32*)m_stream.expandBy(4)) = (hkUint32)type;
	writeData(id);
}

//
template <typename STREAM_WRITER, typename SERIALIZER>
inline void	hkStructuredBinaryStreamWriter<STREAM_WRITER, SERIALIZER>::closeScope()
{
	const hkUint32 head = (hkUint32) m_scopes.back(); m_scopes.popBack();
	const HeadType type = (HeadType) (*(const hkUint32*)m_stream.access(head));
	write(getHead(type, m_stream.getUsed() - head), m_stream.access(head));
}

//
template <typename STREAM_WRITER, typename SERIALIZER>
template <typename T>
inline void hkStructuredBinaryStreamWriter<STREAM_WRITER, SERIALIZER>::write(const T& src, void* dst)
{
	hkUint8* d = static_cast<hkUint8*>(dst);
#if HK_ENDIAN_BIG
	for(int i=0; i<(int)sizeof(T); ++i) d[i] = ((const hkUint8*)&src)[i];
#else
	for(int i=0; i<(int)sizeof(T); ++i) d[i] = ((const hkUint8*)&src)[sizeof(T) - i - 1];
#endif
}

//
// Reader.
//

//
template <typename SERIALIZER>
inline void		hkStructuredBinaryStreamReader<SERIALIZER>::enter(hkUint32 id, HeadType type)
{
	if(id != ANY_ID && peek() != id) { HK_ERROR(0x32CB55F1, "Invalid scope ID, requested #"<<id<<" gets #"<<peek()); }
	m_scopes.pushBack(m_stream.m_cursor);
	m_stream.m_cursor	+=	8;
	if(getType() != type) { HK_ERROR(0x32CB55F3, "Invalid scope type, requested #"<<type<<" gets #"<<getType()); }
}

//
template <typename SERIALIZER>
inline void		hkStructuredBinaryStreamReader<SERIALIZER>::leave(hkUint32 id)
{
	if(id != ANY_ID && getID() != id) {					HK_ERROR(0x32CB55F4, "Invalid scope ID, requested #"<<id<<" gets #"<<getID()); }
	if(m_stream.m_cursor != m_scopes.back() + getLength()) { HK_ERROR(0x32CB55F5, "Scope has been read or skipped to the end."); }
	m_scopes.popBack();
}

//
template <typename SERIALIZER>
template <typename T>
inline void		hkStructuredBinaryStreamReader<SERIALIZER>::readValue(T& value, hkUint32 id)
{
	enter(id, VALUE);
	readData(value);
	leave();
}

//
template <typename SERIALIZER>
template <typename T>
inline void		hkStructuredBinaryStreamReader<SERIALIZER>::readValues(T* values, int count, hkUint32 id)
{
	enter(id, VALUE);
	readData(values, count);
	leave();
}

//
template <typename SERIALIZER>
template <typename T>
inline void		hkStructuredBinaryStreamReader<SERIALIZER>::readArray(hkArray<T>& values, hkUint32 id)
{
	enter(id, ARRAY);
	hkUint32 count; readData(count);
	values.setSize(count);
	readData(values.begin(), values.getSize());
	leave();
}

//
template <typename SERIALIZER>
template <typename T>
inline void	hkStructuredBinaryStreamReader<SERIALIZER>::peek(int from, T* value) const
{
	const hkUint8* src = &m_stream.m_buffer[from];
	#if HK_ENDIAN_BIG
	for(int i=0; i < (int)sizeof(T); ++i) ((hkUint8*)value)[i] = src[i];
	#else
	for(int i=0; i < (int)sizeof(T); ++i) ((hkUint8*)value)[i] = src[sizeof(T) - i - 1];
	#endif
}

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
