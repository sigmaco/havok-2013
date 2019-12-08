/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

	//
	// Win32
	//

inline hkCriticalSection::~hkCriticalSection()
{
	DeleteCriticalSection(&m_section );
}

inline void hkCriticalSection::setTimersEnabled()
{
#ifdef HK_TIME_CRITICAL_SECTION_LOCKS
	HK_THREAD_LOCAL_SET(hkCriticalSection__m_timeLocks, 1);
#endif
}
inline void hkCriticalSection::setTimersDisabled()
{
#ifdef HK_TIME_CRITICAL_SECTION_LOCKS
	HK_THREAD_LOCAL_SET(hkCriticalSection__m_timeLocks, 0);
#endif
}

#ifndef HK_TIME_CRITICAL_SECTION_LOCKS
	inline void hkCriticalSection::enter()
	{
		EnterCriticalSection(&m_section );
	}

	inline void hkCriticalSection::leave()
	{
		LeaveCriticalSection(&m_section );
	}
#else // HK_TIME_CRITICAL_SECTION_LOCKS



	inline void hkCriticalSection::leave()
	{
		LeaveCriticalSection(&m_section );
	}
#endif // HK_TIME_CRITICAL_SECTION_LOCKS


HK_FORCE_INLINE hkUint32 HK_CALL hkCriticalSection::atomicExchangeAdd(hkUint32* var, int increment)
{
// #if defined(HK_PLATFORM_SPU)
// 	// do not use this call in SPU code, it will not work in case of running in the simulator
// 	// use hkDmaManager::atomicExchangeAdd instead which does the correct thing in both cases
// 	HK_ASSERT2(0xa10a996,0,"not implemented");
// 	return 0;
// #else
	return InterlockedExchangeAdd( (LONG*)var, increment);
// #endif
}


HK_FORCE_INLINE hkUint32 hkCriticalSection::waitForValueEqual( hkUint32* var, hkUint32 value )
{
	volatile hkUint32* pVar = (volatile hkUint32*)var;
	hkUint32 ret;

	while ( (ret=*pVar) != value )
	{
#if defined(HK_PLATFORM_WIN32) && !defined(HK_PLATFORM_WINRT)
		Sleep(0);
#elif defined(HK_ARCH_IA32) || defined(HK_ARCH_X64)
		_mm_pause();
#endif
	}

	return ret;
}

HK_FORCE_INLINE hkUint32 hkCriticalSection::waitForValueNotEqual( hkUint32* var, hkUint32 value )
{
	volatile hkUint32* pVar = (volatile hkUint32*)var;
	hkUint32 ret;

	while ( (ret=*pVar) == value )
	{
#if defined(HK_PLATFORM_WIN32) && !defined(HK_PLATFORM_WINRT)
		Sleep(0);
#elif defined(HK_ARCH_IA32) || defined(HK_ARCH_X64)
		_mm_pause();
#endif
	}
	
	return ret;
}

HK_FORCE_INLINE hkUint16 hkCriticalSection::waitForValueNotEqual( hkUint16* var, hkUint16 value )
{
	volatile hkUint16* pVar = (volatile hkUint16*)var;
	hkUint16 ret;

	while ( (ret=*pVar) == value )
	{
#if defined(HK_PLATFORM_WIN32) && !defined(HK_PLATFORM_WINRT)
		Sleep(0);
#elif defined(HK_ARCH_IA32) || defined(HK_ARCH_X64)
		_mm_pause();
#endif
	}

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
