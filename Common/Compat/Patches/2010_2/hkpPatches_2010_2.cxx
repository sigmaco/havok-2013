/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Physics specific product patches applied to release 2010_2.
// This file is #included by hkpPatches_2010_2.cpp

HK_PATCH_BEGIN("hkpConvexVerticesShape", 3, "hkpConvexVerticesShape", 4)
	HK_PATCH_MEMBER_ADDED("rotatedVerticesNew", TYPE_ARRAY_STRUCT, "hkFourTransposedPoints", 0)
	HK_PATCH_FUNCTION(hkpConvexVerticesShape_3_to_4)
	HK_PATCH_MEMBER_REMOVED("rotatedVertices", TYPE_ARRAY_STRUCT, "hkpConvexVerticesShapeFourVectors", 0)
	HK_PATCH_MEMBER_RENAMED("rotatedVerticesNew", "rotatedVertices")
	HK_PATCH_DEPENDS("hkpConvexVerticesShapeFourVectors", 0)
	HK_PATCH_DEPENDS("hkFourTransposedPoints", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpWorldCinfo", 11, "hkpWorldCinfo", 12)
	HK_PATCH_MEMBER_ADDED_BOOL("BETA_useSplitCollisionPipelineOnCpu", false)
	HK_PATCH_MEMBER_ADDED_BOOL("BETA_useSplitCollisionPipelineOnSpu", false)
	HK_PATCH_MEMBER_ADDED_BOOL("BETA_useSplitCollisionPipelineForTois", false)
HK_PATCH_END()

// array/array

HK_PATCH_BEGIN("hkpCompressedMeshShape", 9, "hkpCompressedMeshShape", 10)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpCompressedMeshShape", 10, "hkpCompressedMeshShape", 11)
	HK_PATCH_MEMBER_RENAMED("chunks", "old_chunks")
	HK_PATCH_MEMBER_ADDED("chunks",  TYPE_ARRAY_STRUCT, "hkpCompressedMeshShapeChunk", 0)

	HK_PATCH_MEMBER_RENAMED("convexPieces", "old_convexPieces")
	HK_PATCH_MEMBER_ADDED("convexPieces",  TYPE_ARRAY_STRUCT, "hkpCompressedMeshShapeConvexPiece", 0)

	HK_PATCH_FUNCTION(hkpCompressedMeshShape_10_11)

	HK_PATCH_MEMBER_REMOVED("old_chunks", TYPE_ARRAY_OBJECT, "hkpCompressedMeshShapeChunk", 0)
	HK_PATCH_MEMBER_REMOVED("old_convexPieces", TYPE_ARRAY_OBJECT, "hkpCompressedMeshShapeConvexPiece", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpExtendedMeshShape", 3, "hkpExtendedMeshShape", 4)
	HK_PATCH_MEMBER_RENAMED("shapesSubparts", "old_shapesSubparts")
	HK_PATCH_MEMBER_ADDED("shapesSubparts",  TYPE_ARRAY_STRUCT, "hkpExtendedMeshShapeShapesSubpart", 0)
	HK_PATCH_FUNCTION(hkpExtendedMeshShape_3_to_4)
	HK_PATCH_MEMBER_REMOVED("old_shapesSubparts", TYPE_ARRAY_OBJECT, "hkpExtendedMeshShapeShapesSubpart", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpConvexVerticesShapeFourVectors", 0, HK_NULL, HK_CLASS_REMOVED)
	HK_PATCH_MEMBER_REMOVED("x", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("y", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("z", TYPE_VEC_4, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpSimpleContactConstraintDataInfo", 1, "hkpSimpleContactConstraintDataInfo", 2)
	HK_PATCH_MEMBER_REMOVED("data", TYPE_TUPLE_INT, HK_NULL, 5)
	HK_PATCH_MEMBER_ADDED("data", TYPE_TUPLE_REAL, HK_NULL, 4)
	HK_PATCH_MEMBER_REMOVED("index", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("internalData0", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("biNormalAxis", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("rhsRolling", TYPE_TUPLE_REAL, HK_NULL, 2)
	HK_PATCH_MEMBER_ADDED("contactRadius", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_FUNCTION(hkpSimpleContactConstraintDataInfo_1_to_2)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpCompressedMeshShapeConvexPiece", 3, "hkpCompressedMeshShapeConvexPiece", 4)
	HK_PATCH_MEMBER_REMOVED("faceVertices", TYPE_ARRAY_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("faceOffsets", TYPE_ARRAY_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpWorldCinfo", 12, "hkpWorldCinfo", 13)
    HK_PATCH_MEMBER_ADDED_BYTE("standaloneBroadphase", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpProperty", 0, "hkpProperty", 1)
	HK_PATCH_MEMBER_REMOVED("alignmentPadding", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpSampledHeightFieldShape", 0, "hkpSampledHeightFieldShape", 1)
	HK_PATCH_MEMBER_ADDED("coarseTreeData", TYPE_ARRAY_STRUCT, "hkpSampledHeightFieldShapeCoarseMinMaxLevel", 0)
	HK_PATCH_MEMBER_ADDED_INT("coarseness", 0)
	HK_PATCH_MEMBER_ADDED_REAL("raycastMinY", 0)
	HK_PATCH_MEMBER_ADDED_REAL("raycastMaxY", 0)
	HK_PATCH_DEPENDS("hkpSampledHeightFieldShapeCoarseMinMaxLevel", 0)
	//HK_PATCH_FUNCTION(hkpSampledHeightFieldShape_0_to_1)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpSampledHeightFieldShapeCoarseMinMaxLevel", 0)
	HK_PATCH_MEMBER_ADDED("minMaxData", TYPE_ARRAY_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED_INT("xRes", 0)
	HK_PATCH_MEMBER_ADDED_INT("zRes", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpWorldCinfo", 13, "hkpWorldCinfo", 14)
	HK_PATCH_MEMBER_ADDED("broadPhaseType", TYPE_INT, HK_NULL, 0)
	HK_PATCH_FUNCTION(hkpWorldCinfo_13_to_14)
	HK_PATCH_MEMBER_REMOVED("useKdTree", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("useMultipleTree", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("treeUpdateType", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("useHybridBroadphase", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("standaloneBroadphase", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpWorldCinfo", 14, "hkpWorldCinfo", 15)
	HK_PATCH_MEMBER_REMOVED("BETA_useSplitCollisionPipelineOnCpu", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("BETA_useSplitCollisionPipelineOnSpu", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("BETA_useSplitCollisionPipelineForTois", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED_BOOL("BETA_useSplitCollisionPipeline", false)
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
