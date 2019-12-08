/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#if defined(HK_REAL_IS_DOUBLE)
inline void hkSimplePropertyValue::setReal( const hkReal r )
{
	union {
		hkReal r;
		hkUint64 u;
	} u;
	u.r = r;
	m_data = u.u;
}
#else
inline void hkSimplePropertyValue::setReal( const hkReal r )
{
	// Use a union to ensure that the hkReal is
	// always stored in the LSB end of m_data
	// regardless of platform endianness
	union {
		hkReal r;
		hkUint32 u;
	} u;
	u.r = r;
	m_data = u.u;
}
#endif

inline void hkSimplePropertyValue::setInt( const int i )
{
	m_data = i;
}

inline void hkSimplePropertyValue::setUint64(hkUint64 i)
{
	m_data = i;
}

inline void hkSimplePropertyValue::setPtr( void* p )
{
	m_data = reinterpret_cast<hkUlong>(p);
}

// constructors here for inlining

inline hkSimplePropertyValue::hkSimplePropertyValue( const int i )
{ 
	setInt(i);
}

inline hkSimplePropertyValue::hkSimplePropertyValue( const hkUint32 i)
{
	setInt((int)i);
}

inline hkSimplePropertyValue::hkSimplePropertyValue( const hkReal r )
{ 
	setReal(r);
}

inline hkSimplePropertyValue::hkSimplePropertyValue( void* p )
{ 
	setPtr(p);
}

inline hkSimplePropertyValue::hkSimplePropertyValue( hkUint64 i )
{
	setUint64( i );
}

#if defined(HK_REAL_IS_DOUBLE)
inline hkReal hkSimplePropertyValue::getReal() const
{
	union {
		hkReal r;
		hkUint64 u;
	} u;
	u.u = m_data;
	return u.r;
}
#else
inline hkReal hkSimplePropertyValue::getReal() const
{
	// see comment in setReal
	union {
		hkReal r;
		hkUint32 u;
	} u;
	u.u = hkUint32(m_data);
	return u.r;
}
#endif

inline int hkSimplePropertyValue::getInt() const
{
	return static_cast<int>(m_data);
}

inline void* hkSimplePropertyValue::getPtr() const
{
	return reinterpret_cast<void*>(static_cast<hkUlong>(m_data));
}

inline hkUint64 hkSimplePropertyValue::getUint64() const
{
	return m_data;
}

inline hkSimpleProperty::hkSimpleProperty() 
{
}

inline hkSimpleProperty::hkSimpleProperty( hkUint32 key, hkInt32 value ) 
:	m_key(key), m_value(value)
{ 
}

inline hkSimpleProperty::hkSimpleProperty( hkUint32 key, hkSimplePropertyValue value ) 
:	m_key(key), m_value(value)
{ 
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
