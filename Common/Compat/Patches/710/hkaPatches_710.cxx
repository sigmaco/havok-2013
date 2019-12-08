/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Animation specific product patches applied to release 710.
// This file is #included by hkaPatches_710.cpp

HK_PATCH_BEGIN("hkaSkeleton", 2, "hkaSkeleton", 3)
	HK_PATCH_MEMBER_ADDED("referenceFloats", TYPE_ARRAY_REAL, HK_NULL, 0)
	HK_PATCH_FUNCTION(hkaSkeleton_2_to_3)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaQuantizedAnimationTrackCompressionParams", 0)
	HK_PATCH_MEMBER_ADDED("rotationTolerance", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("translationTolerance", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("scaleTolerance", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("floatingTolerance", TYPE_REAL, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaQuantizedAnimation", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkaAnimation")
	HK_PATCH_MEMBER_ADDED("data", TYPE_ARRAY_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("endian", TYPE_INT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkaAnimation", 1)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
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
