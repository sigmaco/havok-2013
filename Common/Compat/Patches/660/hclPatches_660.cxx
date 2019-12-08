/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Cloth specific product patches applied to release 660.
// This file is #included by hclPatches_660.cpp

HK_PATCH_BEGIN("hclClothStateBufferAccess", 0, "hclClothStateBufferAccess", 1)
	HK_PATCH_MEMBER_ADDED("shadowBufferIndex", TYPE_INT, HK_NULL, 0)
	HK_PATCH_FUNCTION(hclClothStateBufferAccess_0_to_1)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hclRuntimeConversionInfoSlotConversion", 0)
    HK_PATCH_MEMBER_ADDED("elements", TYPE_TUPLE_BYTE, HK_NULL, 4)
    HK_PATCH_MEMBER_ADDED("numElements", TYPE_BYTE, HK_NULL, 0)
    HK_PATCH_MEMBER_ADDED("index", TYPE_BYTE, HK_NULL, 0)
    HK_PATCH_MEMBER_ADDED("partialWrite", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hclStaticShadowBufferDefinition", 0)
    HK_PATCH_PARENT_SET(HK_NULL, "hclBufferDefinition")
    HK_PATCH_MEMBER_ADDED("staticPositions", TYPE_ARRAY_VEC_4, HK_NULL, 0)
    HK_PATCH_MEMBER_ADDED("staticNormals", TYPE_ARRAY_VEC_4, HK_NULL, 0)
    HK_PATCH_MEMBER_ADDED("staticTangents", TYPE_ARRAY_VEC_4, HK_NULL, 0)
    HK_PATCH_MEMBER_ADDED("staticBiTangents", TYPE_ARRAY_VEC_4, HK_NULL, 0)
    HK_PATCH_MEMBER_ADDED("triangleIndices", TYPE_ARRAY_INT, HK_NULL, 0)
    HK_PATCH_DEPENDS("hkBaseObject", 0)
    HK_PATCH_DEPENDS("hclBufferDefinition", 0)
    HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hclOutputConvertOperator", 0)
    HK_PATCH_PARENT_SET(HK_NULL, "hclOperator")
    HK_PATCH_MEMBER_ADDED("userBufferIndex", TYPE_INT, HK_NULL, 0)
    HK_PATCH_MEMBER_ADDED("shadowBufferIndex", TYPE_INT, HK_NULL, 0)
    HK_PATCH_MEMBER_ADDED("conversionInfo", TYPE_STRUCT, "hclRuntimeConversionInfo", 0)
    HK_PATCH_DEPENDS("hkBaseObject", 0)
    HK_PATCH_DEPENDS("hclOperator", 0)
    HK_PATCH_DEPENDS("hkReferencedObject", 0)
    HK_PATCH_DEPENDS("hclRuntimeConversionInfo", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hclRuntimeConversionInfoElementConversion", 0)
    HK_PATCH_MEMBER_ADDED("index", TYPE_BYTE, HK_NULL, 0)
    HK_PATCH_MEMBER_ADDED("offset", TYPE_BYTE, HK_NULL, 0)
    HK_PATCH_MEMBER_ADDED("conversion", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hclRuntimeConversionInfo", 0)
    HK_PATCH_MEMBER_ADDED("slotConversions", TYPE_TUPLE_STRUCT, "hclRuntimeConversionInfoSlotConversion", 4)
    HK_PATCH_MEMBER_ADDED("elementConversions", TYPE_TUPLE_STRUCT, "hclRuntimeConversionInfoElementConversion", 4)
    HK_PATCH_MEMBER_ADDED("numSlotsConverted", TYPE_BYTE, HK_NULL, 0)
    HK_PATCH_MEMBER_ADDED("numElementsConverted", TYPE_BYTE, HK_NULL, 0)
    HK_PATCH_DEPENDS("hclRuntimeConversionInfoElementConversion", 0)
    HK_PATCH_DEPENDS("hclRuntimeConversionInfoSlotConversion", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hclInputConvertOperator", 0)
    HK_PATCH_PARENT_SET(HK_NULL, "hclOperator")
    HK_PATCH_MEMBER_ADDED("userBufferIndex", TYPE_INT, HK_NULL, 0)
    HK_PATCH_MEMBER_ADDED("shadowBufferIndex", TYPE_INT, HK_NULL, 0)
    HK_PATCH_MEMBER_ADDED("conversionInfo", TYPE_STRUCT, "hclRuntimeConversionInfo", 0)
    HK_PATCH_DEPENDS("hkBaseObject", 0)
    HK_PATCH_DEPENDS("hclOperator", 0)
    HK_PATCH_DEPENDS("hkReferencedObject", 0)
    HK_PATCH_DEPENDS("hclRuntimeConversionInfo", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hclShadowBufferDefinition", 0)
    HK_PATCH_PARENT_SET(HK_NULL, "hclBufferDefinition")
    HK_PATCH_MEMBER_ADDED("shadowPositions", TYPE_BYTE, HK_NULL, 0)
    HK_PATCH_MEMBER_ADDED("shadowNormals", TYPE_BYTE, HK_NULL, 0)
    HK_PATCH_MEMBER_ADDED("shadowTangents", TYPE_BYTE, HK_NULL, 0)
    HK_PATCH_MEMBER_ADDED("shadowBiTangents", TYPE_BYTE, HK_NULL, 0)
    HK_PATCH_MEMBER_ADDED("triangleIndices", TYPE_ARRAY_INT, HK_NULL, 0)
    HK_PATCH_DEPENDS("hkBaseObject", 0)
    HK_PATCH_DEPENDS("hclBufferDefinition", 0)
    HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclClothContainer", 0, "hclClothContainer", 1)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
HK_PATCH_END()

HK_PATCH_BEGIN("hclClothSetupContainer", 0, "hclClothSetupContainer", 1)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
HK_PATCH_END()

HK_PATCH_BEGIN("hclConvexHeightFieldShape", 0, "hclConvexHeightFieldShape", 1)
	HK_PATCH_MEMBER_REMOVED("allocatedHeights", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclSceneDataSetupMesh", 0, "hclSceneDataSetupMesh", 1)
	HK_PATCH_MEMBER_RENAMED("meshBufferInterfaces", "old_meshBufferInterfaces")
	HK_PATCH_MEMBER_ADDED("meshBufferInterfaces", TYPE_ARRAY_OBJECT, "hclSceneDataSetupMeshSection", 0)
	HK_PATCH_FUNCTION(hclSceneDataSetupMesh_0_to_1)
	HK_PATCH_MEMBER_REMOVED("old_meshBufferInterfaces", TYPE_ARRAY_OBJECT, "hclSetupMeshSection", 0)
    HK_PATCH_DEPENDS("hclSetupMeshSection", 0)
    HK_PATCH_DEPENDS("hclSceneDataSetupMeshSection", 0)
HK_PATCH_END()

//7.0 Release

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hclBufferUsage", 0)
	HK_PATCH_MEMBER_ADDED("perComponentFlags", TYPE_TUPLE_BYTE, HK_NULL, 4)
	HK_PATCH_MEMBER_ADDED("trianglesRead", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclClothStateBufferAccess", 1, "hclClothStateBufferAccess", 2)
        HK_PATCH_MEMBER_ADDED("bufferUsage", TYPE_STRUCT, "hclBufferUsage", 0)
		HK_PATCH_FUNCTION(hclClothStateBufferAccess_1_to_2)
		HK_PATCH_MEMBER_REMOVED("accessFlags", TYPE_INT, HK_NULL, 0)
		HK_PATCH_DEPENDS("hclBufferUsage", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclSkinOperator", 1, "hclSkinOperator", 2)
	HK_PATCH_MEMBER_ADDED("partialSkinning", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_FUNCTION(hclSkinOperator_1_to_2)
HK_PATCH_END()

HK_PATCH_BEGIN("hclGatherAllVerticesOperator", 0, "hclGatherAllVerticesOperator", 1)
	HK_PATCH_MEMBER_ADDED("partialGather", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_FUNCTION(hclGatherAllVerticesOperator_0_to_1)
HK_PATCH_END()

HK_PATCH_BEGIN("hclMeshMeshDeformOperator", 1, "hclMeshMeshDeformOperator", 2)
	HK_PATCH_MEMBER_ADDED("partialDeform", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_FUNCTION(hclMeshMeshDeformOperator_1_to_2)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hclUpdateSomeVertexFramesOperatorTriangle", 0)
	HK_PATCH_MEMBER_ADDED("indices", TYPE_TUPLE_INT, HK_NULL, 3)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hclUpdateVertexFramesSetupObject", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hclOperatorSetupObject")
	HK_PATCH_MEMBER_ADDED("name", TYPE_CSTRING, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("buffer", TYPE_OBJECT, "hclBufferSetupObject", 0)
	HK_PATCH_MEMBER_ADDED("vertexSelection", TYPE_STRUCT, "hclVertexSelectionInput", 0)
	HK_PATCH_MEMBER_ADDED("updateNormals", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("updateTangents", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("updateBiTangents", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("flipNormals", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("maxSpuDataSize", TYPE_INT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hclVertexSelectionInput", 0)
	HK_PATCH_DEPENDS("hclOperatorSetupObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hclBufferSetupObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hclUpdateAllVertexFramesOperator", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hclOperator")
	HK_PATCH_MEMBER_ADDED("bufferIdx", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("updateNormals", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("updateTangents", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("updateBiTangents", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("flipNormals", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("vertToNormalID", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("numUniqueNormalIDs", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("referenceVertices", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("tangentEdgeCosAngle", TYPE_ARRAY_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("tangentEdgeSinAngle", TYPE_ARRAY_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("biTangentFlip", TYPE_ARRAY_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("spuSupported", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hclOperator", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hclUpdateSomeVertexFramesOperator", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hclOperator")
	HK_PATCH_MEMBER_ADDED("bufferIdx", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("updateNormals", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("updateTangents", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("updateBiTangents", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("flipNormals", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("involvedTriangles", TYPE_ARRAY_STRUCT, "hclUpdateSomeVertexFramesOperatorTriangle", 0)
	HK_PATCH_MEMBER_ADDED("involvedVertices", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("selectionVertexToInvolvedVertex", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("involvedVertexToNormalID", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("numUniqueNormalIDs", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("referenceVertices", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("tangentEdgeCosAngle", TYPE_ARRAY_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("tangentEdgeSinAngle", TYPE_ARRAY_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("biTangentFlip", TYPE_ARRAY_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("spuSupported", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hclUpdateSomeVertexFramesOperatorTriangle", 0)
	HK_PATCH_DEPENDS("hclOperator", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclStorageSetupMeshSection", 0, "hclStorageSetupMeshSection", 1)
	HK_PATCH_MEMBER_ADDED("normalIDs", TYPE_ARRAY_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclUpdateAllVertexFramesOperator", 0, "hclUpdateAllVertexFramesOperator", 1)
	HK_PATCH_MEMBER_REMOVED("spuSupported", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclUpdateSomeVertexFramesOperator", 0, "hclUpdateSomeVertexFramesOperator", 1)
	HK_PATCH_MEMBER_REMOVED("spuSupported", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclUpdateVertexFramesSetupObject", 0, "hclUpdateVertexFramesSetupObject", 1)
	HK_PATCH_MEMBER_REMOVED("maxSpuDataSize", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclSimClothDataSimulationInfo", 0, "hclSimClothDataSimulationInfo", 1)
	HK_PATCH_MEMBER_ADDED("flipNormals", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclUpdateVertexFramesSetupObject", 1, "hclUpdateVertexFramesSetupObject", 2)
	HK_PATCH_MEMBER_REMOVED("flipNormals", TYPE_BYTE, HK_NULL, 0)
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
