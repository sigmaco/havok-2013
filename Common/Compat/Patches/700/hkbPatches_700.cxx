/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Behavior specific product patches applied to release 700.
// This file is #included by hkbPatches_700.cpp

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkbSetWorldFromModelModifier", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkbModifier")
	HK_PATCH_MEMBER_ADDED_VEC_4("translation", 0.000000f,0.000000f,0.000000f,0.000000f)
	HK_PATCH_MEMBER_ADDED_VEC_4("rotation", 0.000000f,0.000000f,0.000000f,1.000000f)
	HK_PATCH_MEMBER_ADDED_BYTE("setTranslation", 1)
	HK_PATCH_MEMBER_ADDED_BYTE("setRotation", 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkbDemoConfig", 2, "hkbDemoConfig", 3)
	HK_PATCH_MEMBER_ADDED_BYTE("forceLoad", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkbDemoConfigCharacterInfo", 1, "hkbDemoConfigCharacterInfo", 2)
	HK_PATCH_MEMBER_ADDED_CSTRING("behaviorFilename", HK_NULL)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkbGetWorldFromModelModifier", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkbModifier")
	HK_PATCH_MEMBER_ADDED_VEC_4("translationOut", 0.000000f,0.000000f,0.000000f,0.000000f)
	HK_PATCH_MEMBER_ADDED_VEC_4("rotationOut", 0.000000f,0.000000f,0.000000f,1.000000f)
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
