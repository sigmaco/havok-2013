/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Cloth specific product patches applied to release 2011_1.
// This file is #included by hclPatches_2011_1.cpp

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hclStorageSetupMeshSectionSectionEdgeSelectionChannel", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("edgeIndices", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hclStorageSetupMeshEdgeChannel", 0)
	HK_PATCH_MEMBER_ADDED("name", TYPE_CSTRING, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("type", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclStorageSetupMesh", 1, "hclStorageSetupMesh", 2)
	HK_PATCH_MEMBER_ADDED("edgeChannels", TYPE_ARRAY_STRUCT, "hclStorageSetupMeshEdgeChannel", 0)
	HK_PATCH_DEPENDS("hclStorageSetupMeshEdgeChannel", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclStorageSetupMeshSection", 1, "hclStorageSetupMeshSection", 2)
	HK_PATCH_MEMBER_ADDED("sectionEdgeChannels", TYPE_ARRAY_OBJECT, "hclStorageSetupMeshSectionSectionEdgeSelectionChannel", 0)
	HK_PATCH_DEPENDS("hclStorageSetupMeshSectionSectionEdgeSelectionChannel", 0)
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
