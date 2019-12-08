/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Collide specific product patches applied to release 2011_1.
// This file is #included by hkcdPatches_2011_1.cpp

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdStaticMeshTreeBaseSectionDataRuns", 0)
	HK_PATCH_MEMBER_ADDED("data", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdStaticMeshTreeBaseSectionSharedVertices", 0)
	HK_PATCH_MEMBER_ADDED("data", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdStaticMeshTreeBaseSectionPrimitives", 0)
	HK_PATCH_MEMBER_ADDED("data", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdStaticMeshTreeBase", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkcdStaticTreeTreehkcdStaticTreeDynamicStorage5")
	HK_PATCH_MEMBER_ADDED("numPrimitiveKeys", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("bitsPerKey", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("maxKeyValue", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("sections", TYPE_ARRAY_STRUCT, "hkcdStaticMeshTreeBaseSection", 0)
	HK_PATCH_MEMBER_ADDED("primitives", TYPE_ARRAY_STRUCT, "hkcdStaticMeshTreeBasePrimitive", 0)
	HK_PATCH_MEMBER_ADDED("sharedVerticesIndex", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkcdStaticMeshTreeBaseSection", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeDynamicStorage4", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeDynamicStorage5", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeTreehkcdStaticTreeDynamicStorage4", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeTreehkcdStaticTreeDynamicStorage5", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeDynamicStoragehkcdStaticTreeCodec3Axis5", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeDynamicStoragehkcdStaticTreeCodec3Axis4", 0)
	HK_PATCH_DEPENDS("hkcdStaticMeshTreeBasePrimitive", 0)
HK_PATCH_END()

#ifdef HK_FEATURE_PRODUCT_PHYSICS_2012

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdStaticMeshTreeBasePrimitiveDataRunBaseunsignedint", 0)
	HK_PATCH_MEMBER_ADDED("value", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("index", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("count", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

#endif

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdStaticMeshTreeBasePrimitiveDataRunBaseunsignedshort", 0)
	HK_PATCH_MEMBER_ADDED("value", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("index", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("count", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdStaticMeshTreeDefaultDataRun", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkcdStaticMeshTreeBasePrimitiveDataRunBaseunsignedshort")
	HK_PATCH_DEPENDS("hkcdStaticMeshTreeBasePrimitiveDataRunBaseunsignedshort", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdStaticMeshTreeBaseSection", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkcdStaticTreeTreehkcdStaticTreeDynamicStorage4")
	HK_PATCH_MEMBER_ADDED("codecParms", TYPE_TUPLE_REAL, HK_NULL, 6)
	HK_PATCH_MEMBER_ADDED("firstPackedVertex", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("sharedVertices", TYPE_STRUCT, "hkcdStaticMeshTreeBaseSectionSharedVertices", 0)
	HK_PATCH_MEMBER_ADDED("primitives", TYPE_STRUCT, "hkcdStaticMeshTreeBaseSectionPrimitives", 0)
	HK_PATCH_MEMBER_ADDED("dataRuns", TYPE_STRUCT, "hkcdStaticMeshTreeBaseSectionDataRuns", 0)
	HK_PATCH_MEMBER_ADDED("numPackedVertices", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("numSharedIndices", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("leafIndex", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("unusedData", TYPE_TUPLE_BYTE, HK_NULL, 3)
	HK_PATCH_DEPENDS("hkcdStaticMeshTreeBaseSectionPrimitives", 0)
	HK_PATCH_DEPENDS("hkcdStaticMeshTreeBaseSectionSharedVertices", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeDynamicStorage4", 0)
	HK_PATCH_DEPENDS("hkcdStaticMeshTreeBaseSectionDataRuns", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeTreehkcdStaticTreeDynamicStorage4", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeDynamicStoragehkcdStaticTreeCodec3Axis4", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdStaticMeshTreeBasePrimitive", 0)
	HK_PATCH_MEMBER_ADDED("indices", TYPE_TUPLE_BYTE, HK_NULL, 4)
HK_PATCH_END()

HK_PATCH_BEGIN("hkcdStaticMeshTreeBaseSection", 0, "hkcdStaticMeshTreeBaseSection", 1)
	HK_PATCH_MEMBER_ADDED("page", TYPE_BYTE, HK_NULL, 0)
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
