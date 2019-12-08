/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */


template <typename T>
HK_FORCE_INLINE hkFixedCapacityArray<T>::hkFixedCapacityArray()
:	m_data(HK_NULL)
,	m_size(0)
,	m_capacity(0)
,	m_usesExternalBuffer(0)
{
}


template <typename T>
HK_FORCE_INLINE hkFixedCapacityArray<T>::hkFixedCapacityArray(int n, const char* descriptor)
:	m_size(0)
,	m_numOverflows(0)
,	m_capacity(n)
,	m_usesExternalBuffer(0)
{
	m_data = hkAllocateStack<T>(n, descriptor);
}

template <typename T>
HK_FORCE_INLINE hkFixedCapacityArray<T>::hkFixedCapacityArray(void* buffer, int bufferSize, const char* descriptor)
:	m_data((T*)buffer)
,	m_size(0)
,	m_numOverflows(0)
,	m_capacity(bufferSize / sizeof(T))
,	m_usesExternalBuffer(1)
{
}

template <typename T>
HK_FORCE_INLINE hkFixedCapacityArray<T>::~hkFixedCapacityArray()
{
	HK_ASSERT2( 0xf0345456, m_data == HK_NULL || m_usesExternalBuffer, "You have to explicitely release memory with the hkFixedCapacityArray");
}


template <typename T>
HK_FORCE_INLINE void hkFixedCapacityArray<T>::clearAndDeallocate()
{
	releaseMemory();
	HK_ON_DEBUG(m_data = HK_NULL);
	HK_ON_DEBUG(m_size = 0);
	HK_ON_DEBUG(m_capacity = 0);
}


template <typename T>
HK_FORCE_INLINE T& hkFixedCapacityArray<T>::operator[] (int i)
{
	HK_ASSERT(0x394e9c6c,  i >= 0 && i < m_size );
	return m_data[i];
}


template <typename T>
HK_FORCE_INLINE const T& hkFixedCapacityArray<T>::operator[] (int i) const
{
	HK_ASSERT(0x264718f3,  i >= 0 && i < m_size  );
	return m_data[i];
}


template <typename T>
HK_FORCE_INLINE int hkFixedCapacityArray<T>::getSize() const
{
	return m_size;
}


template <typename T>
HK_FORCE_INLINE int hkFixedCapacityArray<T>::getCapacity() const
{
	return m_capacity;
}


template <typename T>
HK_FORCE_INLINE void hkFixedCapacityArray<T>::setSize(int size)
{
	HK_ASSERT(0xaf2718f3,  m_size <= m_capacity);
	m_size = size;
}


template <typename T>
HK_FORCE_INLINE T& hkFixedCapacityArray<T>::back()
{
	HK_ASSERT(0x52595f9b, m_size );
	return m_data[ m_size - 1 ];
}


template <typename T>
HK_FORCE_INLINE const T& hkFixedCapacityArray<T>::back() const
{
	HK_ASSERT(0x6e984e36, m_size );
	return m_data[ m_size -1 ];
}


template <typename T>
HK_FORCE_INLINE bool hkFixedCapacityArray<T>::isEmpty() const
{
	return m_size == 0;
}

template <typename T>
HK_FORCE_INLINE bool hkFixedCapacityArray<T>::isFull() const
{
	return m_size >= m_capacity;
}


template <typename T>
HK_FORCE_INLINE void hkFixedCapacityArray<T>::releaseMemory()
{
	if (m_data && 0 == m_usesExternalBuffer)
	{
		hkDeallocateStack(m_data, m_capacity);
	}
}


template <typename T>
HK_FORCE_INLINE int hkFixedCapacityArray<T>::indexOf(const T& t) const
{
	for(int i = 0; i < m_size; ++i)
	{
		if( m_data[i] == t )
		{
			return i;
		}
	}
	return -1;
}


template <typename T>
HK_FORCE_INLINE T& hkFixedCapacityArray<T>::expandOne( )
{
	int size = m_size;
	if(size == m_capacity)
	{
		HK_ON_DEBUG(HK_WARN(0xaf768203, "hkSafeArray::expandOne() : Capacity exhausted. Re-using (overwriting) last element."));
		size--;
		m_numOverflows = m_numOverflows+1;
	}
	T& result = m_data[size];
	size++;
	m_size = size;
	return result;
}


template <typename T>
HK_FORCE_INLINE void hkFixedCapacityArray<T>::pushBack(const T& t)
{
	int size = m_size;
	if(size == m_capacity)
	{
#ifdef HK_DEBUG
		HK_WARN(0xaf768205, "hkSafeArray::pushBack() : Capacity exhausted. Re-using (overwriting) last element.");
#endif
		size--;
		m_numOverflows = m_numOverflows+1;
	}
	m_data[size++] = t;
	m_size = size;
}


template <typename T>
typename hkFixedCapacityArray<T>::iterator hkFixedCapacityArray<T>::begin() 
{
	return m_data;
}


template <typename T>
typename hkFixedCapacityArray<T>::iterator hkFixedCapacityArray<T>::end()
{
	return m_data + m_size;
}


template <typename T>
typename hkFixedCapacityArray<T>::const_iterator hkFixedCapacityArray<T>::begin() const
{
	return m_data;
}


template <typename T>
typename hkFixedCapacityArray<T>::const_iterator hkFixedCapacityArray<T>::end() const
{
	return m_data + m_size;
}


template <typename T>
HK_FORCE_INLINE int hkFixedCapacityArray<T>::getNumOverflows() const
{
	return m_numOverflows;
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
