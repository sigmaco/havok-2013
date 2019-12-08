/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Collide specific product patches applied to release 2011_3.
// This file is #included by hkcdPatches_2011_3.cpp

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdDynamicTreeCodecInt16IntAabb", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkAabb16")
	HK_PATCH_DEPENDS("hkAabb16", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdDynamicTreeCodecInt16", 0)
	HK_PATCH_MEMBER_ADDED("aabb", TYPE_STRUCT, "hkcdDynamicTreeCodecInt16IntAabb", 0)
	HK_PATCH_MEMBER_ADDED("parent", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("children", TYPE_TUPLE_INT, HK_NULL, 2)
	HK_PATCH_MEMBER_ADDED("pad", TYPE_INT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeCodecInt16IntAabb", 0)
	HK_PATCH_DEPENDS("hkAabb16", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdDynamicTreeDynamicStorage0hkcdDynamicTreeAnisotropicMetrichkcdDynamicTreeCodecInt16", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkcdDynamicTreeAnisotropicMetric")
	HK_PATCH_MEMBER_ADDED("nodes", TYPE_ARRAY_STRUCT, "hkcdDynamicTreeCodecInt16", 0)
	HK_PATCH_MEMBER_ADDED("firstFree", TYPE_INT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeCodecInt16", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeAnisotropicMetric", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdDynamicTreeDefaultDynamicStoragehkcdDynamicTreeCodecInt16", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkcdDynamicTreeDynamicStorage0hkcdDynamicTreeAnisotropicMetrichkcdDynamicTreeCodecInt16")
	HK_PATCH_DEPENDS("hkcdDynamicTreeDynamicStorage0hkcdDynamicTreeAnisotropicMetrichkcdDynamicTreeCodecInt16", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeAnisotropicMetric", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdDynamicTreeDynamicStorageInt16", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkcdDynamicTreeDefaultDynamicStoragehkcdDynamicTreeCodecInt16")
	HK_PATCH_DEPENDS("hkcdDynamicTreeDefaultDynamicStoragehkcdDynamicTreeCodecInt16", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeDynamicStorage0hkcdDynamicTreeAnisotropicMetrichkcdDynamicTreeCodecInt16", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeAnisotropicMetric", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdDynamicTreeTreehkcdDynamicTreeDynamicStorageInt16", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkcdDynamicTreeDynamicStorageInt16")
	HK_PATCH_MEMBER_ADDED("numLeaves", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("path", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("root", TYPE_INT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeDefaultDynamicStoragehkcdDynamicTreeCodecInt16", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeDynamicStorage0hkcdDynamicTreeAnisotropicMetrichkcdDynamicTreeCodecInt16", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeAnisotropicMetric", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeDynamicStorageInt16", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdDynamicTreeDefaultTreeInt16Storage", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkcdDynamicTreeTreehkcdDynamicTreeDynamicStorageInt16")
	HK_PATCH_DEPENDS("hkcdDynamicTreeDefaultDynamicStoragehkcdDynamicTreeCodecInt16", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeDynamicStorage0hkcdDynamicTreeAnisotropicMetrichkcdDynamicTreeCodecInt16", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeTreehkcdDynamicTreeDynamicStorageInt16", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeAnisotropicMetric", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeDynamicStorageInt16", 0)
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
