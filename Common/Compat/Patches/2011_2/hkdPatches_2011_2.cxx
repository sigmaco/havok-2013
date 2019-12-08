/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Destruction specific product patches applied to release 2011_2.
// This file is #included by hkdPatches_2011_2.cpp

HK_PATCH_BEGIN("hkdMeshSimplifierAction", 3, "hkdMeshSimplifierAction", 4)
	HK_PATCH_MEMBER_DEFAULT_SET_BYTE("enableCoplanarMerge", 1)
	HK_PATCH_MEMBER_ADDED_REAL("defaultTolerance", 0.000001f)
	HK_PATCH_MEMBER_ADDED_REAL("positionTolerance", 0.000001f)
	HK_PATCH_MEMBER_ADDED_REAL("angularTolerance", 0.000001f)
	HK_PATCH_MEMBER_ADDED_REAL("normalsTolerance", 0.000001f)
	HK_PATCH_MEMBER_ADDED_REAL("texCoordsTolerance", 0.000001f)
	HK_PATCH_MEMBER_ADDED_REAL("colorTolerance", 0.000001f)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkdMeshOptimizerInfo", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkdInfo")
	HK_PATCH_MEMBER_ADDED_BYTE("optimizationType", 1)
	HK_PATCH_MEMBER_ADDED_INT("numBonesPerSection", 70)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkdInfo", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdMeshSimplifierAction", 4, "hkdMeshSimplifierAction", 5)
	HK_PATCH_MEMBER_ADDED_BYTE("preserveBoundaries", 1)
	HK_PATCH_MEMBER_ADDED_REAL("boundaryTolerance", 0.000010f)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdDebrisFracture", 2, "hkdDebrisFracture", 3)
	HK_PATCH_MEMBER_ADDED_BYTE("generationType", 0)
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
