/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Physics specific product patches applied to release 700.
// This file is #included by hkpPatches_700.cpp

HK_PATCH_BEGIN("hkpWorldCinfo", 6, "hkpWorldCinfo", 7)
	HK_PATCH_MEMBER_ADDED_REAL("maxConstraintViolation", 340282001837565600000000000000000000000.000000f)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpWorldCinfo", 7, "hkpWorldCinfo", 8)
	HK_PATCH_MEMBER_ADDED_BYTE("allowIntegrationOfIslandsWithoutConstraintsInASeparateJob", 0)
HK_PATCH_END()

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
