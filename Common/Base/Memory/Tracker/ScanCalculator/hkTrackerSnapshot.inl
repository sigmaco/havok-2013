/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

HK_FORCE_INLINE const hkArrayBase<hkTrackerSnapshot::ClassAlloc>& hkTrackerSnapshot::getClassAllocs() const 
{ 
	return m_classAllocations; 
}

HK_FORCE_INLINE hkArrayBase<hkTrackerSnapshot::ClassAlloc>& hkTrackerSnapshot::getClassAllocs() 
{ 
	return m_classAllocations; 
}

HK_FORCE_INLINE const char* hkTrackerSnapshot::getMemorySystemStatistics() const 
{
	// The m_memSysStatistics is a dynamic array of characters, once the snapshot
	// is initialized the array will never be changed, and the returned pointer
	// will be valid until the hkTrackerSnapshot instance is valid.
	if(m_memSysStatistics.isEmpty())
	{
		return HK_NULL;
	}
	else
	{
		return &m_memSysStatistics[0];
	}
}

HK_FORCE_INLINE hkBool hkTrackerSnapshot::operator!=(const hkTrackerSnapshot& rhs) const 
{ 
	return !(*this == rhs); 
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
