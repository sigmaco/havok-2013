/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Collide specific product patches applied to release 2010_2.
// This file is #included by hkcdPatches_2010_2.cpp

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdDynamicTreeCodec18", 0)
	HK_PATCH_MEMBER_ADDED("aabb", TYPE_STRUCT, "hkAabbHalf", 0)
	HK_PATCH_MEMBER_ADDED("parent", TYPE_INT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkAabbHalf", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdDynamicTreeCodec32", 0)
	HK_PATCH_MEMBER_ADDED("aabb", TYPE_STRUCT, "hkAabb", 0)
	HK_PATCH_DEPENDS("hkAabb", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdDynamicTreeCodecRawunsignedlong", 0)
	HK_PATCH_MEMBER_ADDED("aabb", TYPE_STRUCT, "hkAabb", 0)
	HK_PATCH_MEMBER_ADDED("parent", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("children", TYPE_TUPLE_INT, HK_NULL, 2)
	HK_PATCH_DEPENDS("hkAabb", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdDynamicTreeCodecRawunsignedint", 0)
	HK_PATCH_MEMBER_ADDED("aabb", TYPE_STRUCT, "hkAabb", 0)
	HK_PATCH_MEMBER_ADDED("parent", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("children", TYPE_TUPLE_INT, HK_NULL, 2)
	HK_PATCH_DEPENDS("hkAabb", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdDynamicTreeCodecRawUint", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkcdDynamicTreeCodecRawunsignedint")
	HK_PATCH_DEPENDS("hkcdDynamicTreeCodecRawunsignedint", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdDynamicTreeCodecRawUlong", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkcdDynamicTreeCodecRawunsignedlong")
	HK_PATCH_DEPENDS("hkcdDynamicTreeCodecRawunsignedlong", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdDynamicTreeCentroidMetric", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdDynamicTreeAnisotropicMetric", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdDynamicTreeBalanceMetric", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdDynamicTreeDynamicStorage0hkcdDynamicTreeAnisotropicMetrichkcdDynamicTreeCodec32", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkcdDynamicTreeAnisotropicMetric")
	HK_PATCH_MEMBER_ADDED("nodes", TYPE_ARRAY_STRUCT, "hkcdDynamicTreeCodec32", 0)
	HK_PATCH_MEMBER_ADDED("firstFree", TYPE_INT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeAnisotropicMetric", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeCodec32", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdDynamicTreeDefaultDynamicStoragehkcdDynamicTreeCodec32", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkcdDynamicTreeDynamicStorage0hkcdDynamicTreeAnisotropicMetrichkcdDynamicTreeCodec32")
	HK_PATCH_DEPENDS("hkcdDynamicTreeAnisotropicMetric", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeDynamicStorage0hkcdDynamicTreeAnisotropicMetrichkcdDynamicTreeCodec32", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdDynamicTreeDynamicStorage0hkcdDynamicTreeAnisotropicMetrichkcdDynamicTreeCodecRawUint", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkcdDynamicTreeAnisotropicMetric")
	HK_PATCH_MEMBER_ADDED("nodes", TYPE_ARRAY_STRUCT, "hkcdDynamicTreeCodecRawUint", 0)
	HK_PATCH_MEMBER_ADDED("firstFree", TYPE_INT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeCodecRawUint", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeAnisotropicMetric", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeCodecRawunsignedint", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdDynamicTreeDefaultDynamicStoragehkcdDynamicTreeCodecRawUint", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkcdDynamicTreeDynamicStorage0hkcdDynamicTreeAnisotropicMetrichkcdDynamicTreeCodecRawUint")
	HK_PATCH_DEPENDS("hkcdDynamicTreeDynamicStorage0hkcdDynamicTreeAnisotropicMetrichkcdDynamicTreeCodecRawUint", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeAnisotropicMetric", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdDynamicTreeDynamicStorage0hkcdDynamicTreeAnisotropicMetrichkcdDynamicTreeCodecRawUlong", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkcdDynamicTreeAnisotropicMetric")
	HK_PATCH_MEMBER_ADDED("nodes", TYPE_ARRAY_STRUCT, "hkcdDynamicTreeCodecRawUlong", 0)
	HK_PATCH_MEMBER_ADDED("firstFree", TYPE_INT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeCodecRawUlong", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeAnisotropicMetric", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeCodecRawunsignedlong", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdDynamicTreeDefaultDynamicStoragehkcdDynamicTreeCodecRawUlong", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkcdDynamicTreeDynamicStorage0hkcdDynamicTreeAnisotropicMetrichkcdDynamicTreeCodecRawUlong")
	HK_PATCH_DEPENDS("hkcdDynamicTreeAnisotropicMetric", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeDynamicStorage0hkcdDynamicTreeAnisotropicMetrichkcdDynamicTreeCodecRawUlong", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdDynamicTreeDynamicStorage16", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkcdDynamicTreeDefaultDynamicStoragehkcdDynamicTreeCodec32")
	HK_PATCH_DEPENDS("hkcdDynamicTreeDefaultDynamicStoragehkcdDynamicTreeCodec32", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeAnisotropicMetric", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeDynamicStorage0hkcdDynamicTreeAnisotropicMetrichkcdDynamicTreeCodec32", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdDynamicTreeDynamicStoragePtr", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkcdDynamicTreeDefaultDynamicStoragehkcdDynamicTreeCodecRawUlong")
	HK_PATCH_DEPENDS("hkcdDynamicTreeAnisotropicMetric", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeDynamicStorage0hkcdDynamicTreeAnisotropicMetrichkcdDynamicTreeCodecRawUlong", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeDefaultDynamicStoragehkcdDynamicTreeCodecRawUlong", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdDynamicTreeDynamicStorage32", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkcdDynamicTreeDefaultDynamicStoragehkcdDynamicTreeCodecRawUint")
	HK_PATCH_DEPENDS("hkcdDynamicTreeDefaultDynamicStoragehkcdDynamicTreeCodecRawUint", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeDynamicStorage0hkcdDynamicTreeAnisotropicMetrichkcdDynamicTreeCodecRawUint", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeAnisotropicMetric", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdStaticTreeCodec3Axis", 0)
	HK_PATCH_MEMBER_ADDED("xyz", TYPE_TUPLE_BYTE, HK_NULL, 3)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdStaticTreeCodec3Axis4", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkcdStaticTreeCodec3Axis")
	HK_PATCH_MEMBER_ADDED("data", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeCodec3Axis", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdStaticTreeCodec3Axis5", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkcdStaticTreeCodec3Axis")
	HK_PATCH_MEMBER_ADDED("hiData", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("loData", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeCodec3Axis", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdStaticTreeCodec3Axis6", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkcdStaticTreeCodec3Axis")
	HK_PATCH_MEMBER_ADDED("hiData", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("loData", TYPE_INT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeCodec3Axis", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdStaticTreeCodecRaw", 0)
	HK_PATCH_MEMBER_ADDED("aabb", TYPE_STRUCT, "hkAabb", 0)
	HK_PATCH_DEPENDS("hkAabb", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdStaticTreeDynamicStoragehkcdStaticTreeCodec3Axis4", 0)
	HK_PATCH_MEMBER_ADDED("nodes", TYPE_ARRAY_STRUCT, "hkcdStaticTreeCodec3Axis4", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeCodec3Axis4", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeCodec3Axis", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdStaticTreeDynamicStoragehkcdStaticTreeCodec3Axis5", 0)
	HK_PATCH_MEMBER_ADDED("nodes", TYPE_ARRAY_STRUCT, "hkcdStaticTreeCodec3Axis5", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeCodec3Axis5", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeCodec3Axis", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdStaticTreeDynamicStoragehkcdStaticTreeCodec3Axis6", 0)
	HK_PATCH_MEMBER_ADDED("nodes", TYPE_ARRAY_STRUCT, "hkcdStaticTreeCodec3Axis6", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeCodec3Axis6", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeCodec3Axis", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdStaticTreeDynamicStorage4", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkcdStaticTreeDynamicStoragehkcdStaticTreeCodec3Axis4")
	HK_PATCH_DEPENDS("hkcdStaticTreeDynamicStoragehkcdStaticTreeCodec3Axis4", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdStaticTreeDynamicStorage5", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkcdStaticTreeDynamicStoragehkcdStaticTreeCodec3Axis5")
	HK_PATCH_DEPENDS("hkcdStaticTreeDynamicStoragehkcdStaticTreeCodec3Axis5", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdStaticTreeDynamicStorage6", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkcdStaticTreeDynamicStoragehkcdStaticTreeCodec3Axis6")
	HK_PATCH_DEPENDS("hkcdStaticTreeDynamicStoragehkcdStaticTreeCodec3Axis6", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdStaticTreeDynamicStoragehkcdStaticTreeCodecRaw", 0)
	HK_PATCH_MEMBER_ADDED("nodes", TYPE_ARRAY_STRUCT, "hkcdStaticTreeCodecRaw", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeCodecRaw", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdStaticTreeDynamicStorage32", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkcdStaticTreeDynamicStoragehkcdStaticTreeCodecRaw")
	HK_PATCH_DEPENDS("hkcdStaticTreeDynamicStoragehkcdStaticTreeCodecRaw", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdDynamicTreeTreehkcdDynamicTreeDynamicStoragePtr", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkcdDynamicTreeDynamicStoragePtr")
	HK_PATCH_MEMBER_ADDED("numLeaves", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("path", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("root", TYPE_INT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeAnisotropicMetric", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeDynamicStoragePtr", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeDefaultDynamicStoragehkcdDynamicTreeCodecRawUlong", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeDynamicStorage0hkcdDynamicTreeAnisotropicMetrichkcdDynamicTreeCodecRawUlong", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdDynamicTreeTreehkcdDynamicTreeDynamicStorage16", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkcdDynamicTreeDynamicStorage16")
	HK_PATCH_MEMBER_ADDED("numLeaves", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("path", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("root", TYPE_INT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeDefaultDynamicStoragehkcdDynamicTreeCodec32", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeAnisotropicMetric", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeDynamicStorage16", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeDynamicStorage0hkcdDynamicTreeAnisotropicMetrichkcdDynamicTreeCodec32", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdDynamicTreeTreehkcdDynamicTreeDynamicStorage32", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkcdDynamicTreeDynamicStorage32")
	HK_PATCH_MEMBER_ADDED("numLeaves", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("path", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("root", TYPE_INT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeDefaultDynamicStoragehkcdDynamicTreeCodecRawUint", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeDynamicStorage0hkcdDynamicTreeAnisotropicMetrichkcdDynamicTreeCodecRawUint", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeDynamicStorage32", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeAnisotropicMetric", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdDynamicTreeDefaultTreePtrStorage", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkcdDynamicTreeTreehkcdDynamicTreeDynamicStoragePtr")
	HK_PATCH_DEPENDS("hkcdDynamicTreeTreehkcdDynamicTreeDynamicStoragePtr", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeAnisotropicMetric", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeDynamicStoragePtr", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeDefaultDynamicStoragehkcdDynamicTreeCodecRawUlong", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeDynamicStorage0hkcdDynamicTreeAnisotropicMetrichkcdDynamicTreeCodecRawUlong", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdDynamicTreeDefaultTree32Storage", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkcdDynamicTreeTreehkcdDynamicTreeDynamicStorage16")
	HK_PATCH_DEPENDS("hkcdDynamicTreeDefaultDynamicStoragehkcdDynamicTreeCodec32", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeTreehkcdDynamicTreeDynamicStorage16", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeAnisotropicMetric", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeDynamicStorage16", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeDynamicStorage0hkcdDynamicTreeAnisotropicMetrichkcdDynamicTreeCodec32", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdDynamicTreeDefaultTree48Storage", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkcdDynamicTreeTreehkcdDynamicTreeDynamicStorage32")
	HK_PATCH_DEPENDS("hkcdDynamicTreeDefaultDynamicStoragehkcdDynamicTreeCodecRawUint", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeDynamicStorage0hkcdDynamicTreeAnisotropicMetrichkcdDynamicTreeCodecRawUint", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeDynamicStorage32", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeAnisotropicMetric", 0)
	HK_PATCH_DEPENDS("hkcdDynamicTreeTreehkcdDynamicTreeDynamicStorage32", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdStaticTreeTreehkcdStaticTreeDynamicStorage4", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkcdStaticTreeDynamicStorage4")
	HK_PATCH_MEMBER_ADDED("domain", TYPE_STRUCT, "hkAabb", 0)
	HK_PATCH_DEPENDS("hkAabb", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeDynamicStorage4", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeDynamicStoragehkcdStaticTreeCodec3Axis4", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdStaticTreeTreehkcdStaticTreeDynamicStorage5", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkcdStaticTreeDynamicStorage5")
	HK_PATCH_MEMBER_ADDED("domain", TYPE_STRUCT, "hkAabb", 0)
	HK_PATCH_DEPENDS("hkAabb", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeDynamicStorage5", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeDynamicStoragehkcdStaticTreeCodec3Axis5", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdStaticTreeTreehkcdStaticTreeDynamicStorage6", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkcdStaticTreeDynamicStorage6")
	HK_PATCH_MEMBER_ADDED("domain", TYPE_STRUCT, "hkAabb", 0)
	HK_PATCH_DEPENDS("hkAabb", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeDynamicStorage6", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeDynamicStoragehkcdStaticTreeCodec3Axis6", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdStaticTreeTreehkcdStaticTreeDynamicStorage32", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkcdStaticTreeDynamicStorage32")
	HK_PATCH_MEMBER_ADDED("domain", TYPE_STRUCT, "hkAabb", 0)
	HK_PATCH_DEPENDS("hkAabb", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeDynamicStorage32", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeDynamicStoragehkcdStaticTreeCodecRaw", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdStaticTreeDefaultTreeStorage32", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkcdStaticTreeTreehkcdStaticTreeDynamicStorage32")
	HK_PATCH_DEPENDS("hkcdStaticTreeTreehkcdStaticTreeDynamicStorage32", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeDynamicStorage32", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeDynamicStoragehkcdStaticTreeCodecRaw", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdStaticTreeDefaultTreeStorage4", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkcdStaticTreeTreehkcdStaticTreeDynamicStorage4")
	HK_PATCH_DEPENDS("hkcdStaticTreeDynamicStorage4", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeTreehkcdStaticTreeDynamicStorage4", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeDynamicStoragehkcdStaticTreeCodec3Axis4", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdStaticTreeDefaultTreeStorage5", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkcdStaticTreeTreehkcdStaticTreeDynamicStorage5")
	HK_PATCH_DEPENDS("hkcdStaticTreeDynamicStorage5", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeTreehkcdStaticTreeDynamicStorage5", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeDynamicStoragehkcdStaticTreeCodec3Axis5", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdStaticTreeDefaultTreeStorage6", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkcdStaticTreeTreehkcdStaticTreeDynamicStorage6")
	HK_PATCH_DEPENDS("hkcdStaticTreeDynamicStorage6", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeTreehkcdStaticTreeDynamicStorage6", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeDynamicStoragehkcdStaticTreeCodec3Axis6", 0)
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
