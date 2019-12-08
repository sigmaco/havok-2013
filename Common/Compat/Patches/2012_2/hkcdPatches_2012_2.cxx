/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Collide specific product patches applied to release 2012_2.
// This file is #included by hkcdPatches_2012_2.cpp

#ifdef HK_FEATURE_PRODUCT_AI

HK_PATCH_BEGIN("hkaiStaticTree", 0, "hkcdStaticAabbTree", 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiDynamicTree", 0, "hkcdDynamicAabbTree", 1)
HK_PATCH_END()

#else

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdDynamicAabbTree", 1)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("treePtr", TYPE_OBJECT, "hkcdDynamicTreeDefaultTree48Storage", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeDefaultTree48Storage", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeDefaultDynamicStoragehkcdDynamicTreeCodecRawUint", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeDynamicStorage32", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeDynamicStorage0hkcdDynamicTreeAnisotropicMetrichkcdDynamicTreeCodecRawUint", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeAnisotropicMetric", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeTreehkcdDynamicTreeDynamicStorage32", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdStaticAabbTree", 1)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("treePtr", TYPE_OBJECT, "hkcdStaticTreeDefaultTreeStorage6", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeDefaultTreeStorage6", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeTreehkcdStaticTreeDynamicStorage6", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeDynamicStorage6", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeDynamicStoragehkcdStaticTreeCodec3Axis6", 0)
HK_PATCH_END()

#endif

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
