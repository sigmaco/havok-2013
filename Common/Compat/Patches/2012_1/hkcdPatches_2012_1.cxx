/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Collide specific product patches applied to release 2012_1.
// This file is #included by hkcdPatches_2012_1.cpp

HK_PATCH_BEGIN("hkcdStaticMeshTreeBaseSection", 2, "hkcdStaticMeshTreeBaseSection", 3)
	HK_PATCH_MEMBER_REMOVED("unusedData", TYPE_TUPLE_BYTE, HK_NULL, 2)
	HK_PATCH_MEMBER_ADDED("unusedData", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("layerData", TYPE_BYTE, HK_NULL, 0)
	//HK_PATCH_FUNCTION(hkcdStaticMeshTreeBaseSection_2_to_3)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdStaticPvs", 0)
	HK_PATCH_MEMBER_ADDED("cells", TYPE_STRUCT, "hkcdStaticTreeTreehkcdStaticTreeDynamicStorage6", 0)
	HK_PATCH_MEMBER_ADDED("bytesPerCells", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("cellsPerBlock", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("pvs", TYPE_ARRAY_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("map", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("blocks", TYPE_ARRAY_STRUCT, "hkcdStaticPvsBlockHeader", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeDynamicStorage6", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeTreehkcdStaticTreeDynamicStorage6", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeDynamicStoragehkcdStaticTreeCodec3Axis6", 0)
	HK_PATCH_DEPENDS("hkcdStaticPvsBlockHeader", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdStaticPvsBlockHeader", 0)
	HK_PATCH_MEMBER_ADDED("offset", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("length", TYPE_INT, HK_NULL, 0)
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
