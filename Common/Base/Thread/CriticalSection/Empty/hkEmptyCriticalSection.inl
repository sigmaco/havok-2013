/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

inline hkCriticalSection::hkCriticalSection( int spinCount ) {}
inline hkCriticalSection::~hkCriticalSection() {}
inline void hkCriticalSection::enter(){}
inline void hkCriticalSection::leave() {}
inline void HK_CALL hkCriticalSection::setTimersEnabled(){}
inline void HK_CALL hkCriticalSection::setTimersDisabled(){}

hkUint32 HK_CALL hkCriticalSection::atomicExchangeAdd(hkUint32* var, int value)
{
	hkUint32 r = *var;
	*var += value;
	return r;
}

HK_FORCE_INLINE hkUint32 hkCriticalSection::waitForValueEqual( hkUint32* var, hkUint32 value )
{
	volatile hkUint32* pVar = (volatile hkUint32*)var;
	hkUint32 ret;
	while ( (ret=*pVar) != value ){}
	return ret;
}

HK_FORCE_INLINE hkUint32 hkCriticalSection::waitForValueNotEqual( hkUint32* var, hkUint32 value )
{
	volatile hkUint32* pVar = (volatile hkUint32*)var;
	hkUint32 ret;
	while ( (ret=*pVar) == value ){}
	return ret;
}


HK_FORCE_INLINE hkUint16 hkCriticalSection::waitForValueNotEqual( hkUint16* var, hkUint16 value )
{
	volatile hkUint16* pVar = (volatile hkUint16*)var;
	hkUint16 ret;
	while ( (ret=*pVar) == value ){}
	return ret;
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
