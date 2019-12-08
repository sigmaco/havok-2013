/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Stream

template<typename T>
HK_FORCE_INLINE hkBlockStream<T>::hkBlockStream( Allocator* tlAllocator, bool zeroNewBlocks /* = false */ ) 
: hkBlockStreamBase::Stream( tlAllocator, zeroNewBlocks )
{}

template<typename T>
HK_FORCE_INLINE hkBlockStream<T>::hkBlockStream()
:	hkBlockStreamBase::Stream()
{}

template<typename T>
HK_FORCE_INLINE hkBlockStream<T>::~hkBlockStream()
{}

template<typename T>
HK_FORCE_INLINE void hkBlockStream<T>::clearAndSteal( Allocator* tlAllocator, hkBlockStream<T>* inStream )
{ 
	hkBlockStreamBase::Stream::clear(tlAllocator); 
	hkBlockStreamBase::Stream::append(tlAllocator, inStream); 
}

	
// Writer

template<typename T>
HK_FORCE_INLINE T* hkBlockStream<T>::Writer::write16( const T* HK_RESTRICT data, int numBytes )
{
	HK_ASSERT(0xaf142e11, (numBytes & 0x0f) == 0);
	T *dstCache = (T*)hkBlockStreamBase::Writer::reserveBytes( numBytes );
	hkString::memCpy16NonEmpty( dstCache, data, numBytes>>4 );
	advance( numBytes );
	return dstCache;
}

template <typename T>
template <typename T2>
HK_FORCE_INLINE T2* hkBlockStream<T>::Writer::write16( const T2* HK_RESTRICT data, int numBytes )
{
	HK_ASSERT(0xaf142e11, (numBytes & 0x0f) == 0);
	T2 *dstCache = (T2*)hkBlockStreamBase::Writer::reserveBytes( numBytes );
	hkString::memCpy16NonEmpty( dstCache, data, numBytes>>4 );
	advance( numBytes );
	return dstCache;
}

template <typename T>
HK_FORCE_INLINE T*  hkBlockStream<T>::Writer::write16( const T* HK_RESTRICT data )
{
	return write16( data, data->getSizeInBytes() );
}

template <typename T>
HK_FORCE_INLINE T* hkBlockStream<T>::Writer::write( const T* HK_RESTRICT data, int numBytes )
{
	T *dstCache = (T*)hkBlockStreamBase::Writer::reserveBytes( numBytes );
	hkString::memCpy4( dstCache, data, numBytes>>2 );
	advance( numBytes );
	return dstCache;
}

template <typename T>
HK_FORCE_INLINE T* hkBlockStream<T>::Writer::write( const T* HK_RESTRICT data )
{
	return write( data, data->getSizeInBytes() );
}

template <typename T>
HK_FORCE_INLINE	T* hkBlockStream<T>::Writer::advanceAndReserveNext( int currentNumBytes, int reservedNumBytes )
{
	return (T*)hkBlockStreamBase::Writer::advanceAndReserveNext( currentNumBytes, reservedNumBytes );
}

template <typename T>
HK_FORCE_INLINE	T*  hkBlockStream<T>::Writer::reserve( int numBytes )
{
	HK_ASSERT(0xaf1e132f, hkSizeOf(T) <= numBytes);
	return (T*)hkBlockStreamBase::Writer::reserveBytes(numBytes);
}

template <typename T>
template<typename T2>
HK_FORCE_INLINE	T2*  hkBlockStream<T>::Writer::reserve()
{
	return (T2*)hkBlockStreamBase::Writer::reserveBytes(sizeof(T2));
}

template <typename T>
template<typename T2>
HK_FORCE_INLINE	T2*  hkBlockStream<T>::Writer::reserve( int numBytes )
{
	return (T2*)hkBlockStreamBase::Writer::reserveBytes(numBytes);
}

template <typename T>
HK_FORCE_INLINE bool hkBlockStream<T>::Writer::isValid()
{
	return m_blockStream != HK_NULL;
}

// Reader

template <typename T>
HK_FORCE_INLINE	const T* hkBlockStream<T>::Reader::advanceAndAccessNext( int thisElemSize )
{ 
	return (const T*)hkBlockStreamBase::Reader::advanceAndAccessNext(thisElemSize); 
}

template <typename T>
template <typename T2>
HK_FORCE_INLINE const T2* hkBlockStream<T>::Reader::advanceAndAccessNext( int thisElemSize )
{
	return (const T2*)hkBlockStreamBase::Reader::advanceAndAccessNext(thisElemSize);  
}

template <typename T>
template <typename T2>
HK_FORCE_INLINE	const T2* hkBlockStream<T>::Reader::advanceAndAccessNext( )
{ 
	return (const T2*)hkBlockStreamBase::Reader::advanceAndAccessNext(sizeof(T2));  
}

template <typename T>
HK_FORCE_INLINE	const T* hkBlockStream<T>::Reader::access()
{ 
	return (T*)hkBlockStreamBase::Reader::access(); 
}

template <typename T>
template <typename T2>
HK_FORCE_INLINE	const T2* hkBlockStream<T>::Reader::access()
{ 
	return (T2*)hkBlockStreamBase::Reader::access(); 
}


template <typename T>
HK_FORCE_INLINE const T* hkBlockStream<T>::Reader::advanceAndAccessNext( const T* HK_RESTRICT data )
{ 
	return advanceAndAccessNext( data->getSizeInBytes()); 
}

// Modifier

template <typename T>
HK_FORCE_INLINE	T* hkBlockStream<T>::Modifier::advanceAndAccessNext( int thisElemSize )
{ 
	return (T*)hkBlockStreamBase::Modifier::advanceAndAccessNext(thisElemSize);
}

template <typename T>
template <typename T2>
HK_FORCE_INLINE	T2*  hkBlockStream<T>::Modifier::advanceAndAccessNext( int thisElemSize )
{
	return (T2*)hkBlockStreamBase::Modifier::advanceAndAccessNext(thisElemSize);
}

template <typename T>
HK_FORCE_INLINE	T*  hkBlockStream<T>::Modifier::access()
{ 
	return (T*)hkBlockStreamBase::Modifier::access(); 
}

template <typename T>
template <typename T2>
HK_FORCE_INLINE	T2*  hkBlockStream<T>::Modifier::access(){ 
	return (T2*)hkBlockStreamBase::Modifier::access(); 
}

// Consumer

template <typename T>
HK_FORCE_INLINE void hkBlockStream<T>::Consumer::setToRange( Allocator* allocator, hkBlockStream<T>* stream, hkBlockStream<T>* streamPpu, const hkBlockStreamBase::Range* range ){
	 hkBlockStreamBase::Consumer::setToRange( allocator, stream, streamPpu, range ); 
}

template <typename T>
HK_FORCE_INLINE	const T* hkBlockStream<T>::Consumer::access()
{
	return (T*)hkBlockStreamBase::Consumer::access(); 
}

template <typename T>
HK_FORCE_INLINE	const T* hkBlockStream<T>::Consumer::consumeAndAccessNext( int thisElemSize )
{ 
	return (const T*)hkBlockStreamBase::Consumer::consumeAndAccessNext(thisElemSize); 
}

template <typename T>
HK_FORCE_INLINE const T* hkBlockStream<T>::Consumer::consumeAndAccessNext( const T* HK_RESTRICT data )
{
	return consumeAndAccessNext( data->getSizeInBytes()); 
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
