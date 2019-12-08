/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Cloth specific product patches applied to release 2012_2.
// This file is #included by hclPatches_2012_2.cpp

HK_PATCH_BEGIN("hclMeshMeshDeformSetupObject", 1, "hclMeshMeshDeformSetupObject", 2)
	HK_PATCH_MEMBER_ADDED("influenceRadiusPerVertex", TYPE_STRUCT, "hclVertexFloatInput", 0)
	HK_PATCH_MEMBER_ADDED("useMeshTopology", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_DEPENDS("hclVertexFloatInput", 0)
	HK_PATCH_FUNCTION(hclMeshMeshDeformSetupObject_1_to_2)
	HK_PATCH_MEMBER_REMOVED("influenceRadius", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("inputTrianglesSubsetThreshold", TYPE_REAL, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclLocalRangeSetupObject", 1, "hclLocalRangeSetupObject", 2)
	HK_PATCH_MEMBER_ADDED("localRangeShape", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclLocalRangeConstraintSet", 2, "hclLocalRangeConstraintSet", 3)
	HK_PATCH_MEMBER_ADDED("shapeType", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclStretchLinkSetupObject", 0, "hclStretchLinkSetupObject", 1)
	HK_PATCH_MEMBER_ADDED("useStretchDirection", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("useMeshTopology", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclBoneSpaceDeformerThreeBlendEntryBlock", 0, "hclBoneSpaceDeformerThreeBlendEntryBlock", 1)
	HK_PATCH_MEMBER_REMOVED("padding", TYPE_TUPLE_BYTE, HK_NULL, 8)
HK_PATCH_END()

HK_PATCH_BEGIN("hclBoneSpaceDeformerFourBlendEntryBlock", 0, "hclBoneSpaceDeformerFourBlendEntryBlock", 1)
	HK_PATCH_MEMBER_REMOVED("padding", TYPE_TUPLE_BYTE, HK_NULL, 8)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hclConvexPlanesShape", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hclShape")
	HK_PATCH_MEMBER_ADDED("planeEquations", TYPE_ARRAY_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("localFromWorld", TYPE_VEC_16, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("worldFromLocal", TYPE_VEC_16, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("objAabb", TYPE_STRUCT, "hkAabb", 0)
	HK_PATCH_MEMBER_ADDED("geomCentroid", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_DEPENDS("hclShape", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkAabb", 0)
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
