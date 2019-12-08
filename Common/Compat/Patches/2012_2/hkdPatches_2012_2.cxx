/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Destruction specific product patches applied to release 2012_2.
// This file is #included by hkdPatches_2012_2.cpp

HK_PATCH_BEGIN("hkdDecorateFractureFaceActionGlobalDecorationData", 2, "hkdDecorateFractureFaceActionGlobalDecorationData", 3)
	HK_PATCH_MEMBER_RENAMED("rawTransforms", "old_rawTransforms")
	HK_PATCH_MEMBER_ADDED("rawTransforms", TYPE_ARRAY_REAL, HK_NULL, 0)
	HK_PATCH_FUNCTION(hkdDecorateFractureFaceActionGlobalDecorationData_2_to_3)
	HK_PATCH_MEMBER_REMOVED("old_rawTransforms", TYPE_ARRAY_STRUCT, "hkQTransform", 0)
	HK_PATCH_DEPENDS("hkQTransform", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdFracture", 2, "hkdFracture", 3)
	HK_PATCH_MEMBER_ADDED_BYTE("allowOpenMeshes", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdWoodController", 0, "hkdWoodController", 1)
	HK_PATCH_MEMBER_ADDED_REAL("maxDeformationAngle", 10.000000f)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdShape", 3, "hkdShape", 4)
	HK_PATCH_MEMBER_ADDED_REAL("elasticity", 200.000000f)
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
