/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// AI specific product patches applied to release 2010_1.
// This file is #included by hkaiPatches_2010_1.cpp

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiMaterialPainter", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("material", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("volume", TYPE_OBJECT, "hkaiVolume", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkaiVolume", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshGenerationSettings", 10, "hkaiNavMeshGenerationSettings", 11)
	HK_PATCH_MEMBER_ADDED("painters", TYPE_ARRAY_OBJECT, "hkaiMaterialPainter", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkaiMaterialPainter", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()


HK_PATCH_BEGIN("hkaiNavMeshFace", 2, "hkaiNavMeshFace", 3)
	HK_PATCH_MEMBER_ADDED("clearancesIndex", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMesh", 4, "hkaiNavMesh", 5)
	HK_PATCH_MEMBER_ADDED("clearanceCache", TYPE_ARRAY_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("globalClearanceCache", TYPE_ARRAY_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("uncutClearanceCacheSize", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("maxGlobalClearance", TYPE_REAL, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshEdge", 4, "hkaiNavMeshEdge", 5)
	HK_PATCH_MEMBER_RENAMED("vertexClearance", "userEdgeCost")
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiNavVolume", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("cells", TYPE_ARRAY_STRUCT, "hkaiNavVolumeCell", 0)
	HK_PATCH_MEMBER_ADDED("edges", TYPE_ARRAY_STRUCT, "hkaiNavVolumeEdge", 0)
	HK_PATCH_MEMBER_ADDED("cellIndices", TYPE_ARRAY_STRUCT, "hkaiNavVolumeFI", 0)
	HK_PATCH_MEMBER_ADDED("cellRegions", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("aabb", TYPE_STRUCT, "hkAabb", 0)
	HK_PATCH_MEMBER_ADDED("res", TYPE_TUPLE_INT, HK_NULL, 3)
	HK_PATCH_MEMBER_ADDED("inputFilename", TYPE_CSTRING, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkaiNavVolumeCell", 0)
	HK_PATCH_DEPENDS("hkaiNavVolumeFI", 0)
	HK_PATCH_DEPENDS("hkAabb", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkaiNavVolumeEdge", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiNavVolumeFI", 0)
	HK_PATCH_MEMBER_ADDED("a", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("b", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiNavVolumeCell", 0)
	HK_PATCH_MEMBER_ADDED("min", TYPE_TUPLE_INT, HK_NULL, 3)
	HK_PATCH_MEMBER_ADDED("max", TYPE_TUPLE_INT, HK_NULL, 3)
	HK_PATCH_MEMBER_ADDED("numEdges", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("startEdgeIndex", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("data", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiNavVolumeEdge", 0)
	HK_PATCH_MEMBER_ADDED("oppositeCell", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiNavVolumeGenerationSettings", 0)
	HK_PATCH_MEMBER_ADDED_REAL("maxHorizontalRange", 10000.000000f)
	HK_PATCH_MEMBER_ADDED_REAL("maxVerticalRange", 1000.000000f)
	HK_PATCH_MEMBER_ADDED_BYTE("validateInputGeometry", 0)
	HK_PATCH_MEMBER_ADDED("up", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("cellDensity", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED_REAL("minRegionVolume", 5.000000f)
	HK_PATCH_MEMBER_ADDED("minDistanceToSeedPoints", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("regionSeedPoints", TYPE_ARRAY_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("carvers", TYPE_ARRAY_OBJECT, "hkaiVolume", 0)
	HK_PATCH_MEMBER_ADDED("painters", TYPE_ARRAY_OBJECT, "hkaiMaterialPainter", 0)
	HK_PATCH_MEMBER_ADDED("saveInputSnapshot", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("snapshotFilename", TYPE_CSTRING, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkaiVolume", 0)
	HK_PATCH_DEPENDS("hkaiMaterialPainter", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()


HK_PATCH_BEGIN("hkaiNavVolumeGenerationSettings", 0, "hkaiNavVolumeGenerationSettings", 1)
	HK_PATCH_MEMBER_ADDED_REAL("characterHeight", 1.750000f)
	HK_PATCH_MEMBER_ADDED_REAL("characterDepth", 0.000000f)
	HK_PATCH_MEMBER_ADDED_REAL("characterWidth", 1.750000f)
	HK_PATCH_MEMBER_ADDED("iterationsStabilizationThreshold", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("maxMergingIterations", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()


HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiNavMeshInstance", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("originalMesh", TYPE_OBJECT, "hkaiNavMesh", 0)
	HK_PATCH_MEMBER_ADDED("edgeMap", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("faceMap", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("instancedFaces", TYPE_ARRAY_STRUCT, "hkaiNavMeshFace", 0)
	HK_PATCH_MEMBER_ADDED("instancedEdges", TYPE_ARRAY_STRUCT, "hkaiNavMeshEdge", 0)
	HK_PATCH_MEMBER_ADDED("ownedFaces", TYPE_ARRAY_STRUCT, "hkaiNavMeshFace", 0)
	HK_PATCH_MEMBER_ADDED("ownedEdges", TYPE_ARRAY_STRUCT, "hkaiNavMeshEdge", 0)
	HK_PATCH_MEMBER_ADDED("ownedVertices", TYPE_ARRAY_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("faceFlags", TYPE_ARRAY_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("clearanceCache", TYPE_ARRAY_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("globalClearanceCache", TYPE_ARRAY_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("faceClearanceIndices", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("maxGlobalClearance", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("transform", TYPE_VEC_16, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkaiNavMeshFace", 4)
	HK_PATCH_DEPENDS("hkaiNavMeshEdge", 5)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkaiNavMesh", 4)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshManager", 3, "hkaiStreamingManager", 4)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshManagerSectionInfo", 1, "hkaiStreamingManagerSectionInfo", 2)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiStreamingCollectionInstanceInfo", 0)
	HK_PATCH_MEMBER_ADDED("instancePtr", TYPE_OBJECT, "hkaiNavMeshInstance",0)
	HK_PATCH_MEMBER_ADDED("clusterGraph", TYPE_OBJECT, "hkaiDirectedGraphExplicitCost", 0)
	HK_PATCH_MEMBER_ADDED("mediator", TYPE_OBJECT, "hkaiNavMeshQueryMediator", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkaiNavMeshQueryMediator", 0)
	HK_PATCH_DEPENDS("hkaiNavMeshInstance", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkaiDirectedGraphExplicitCost", 1)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiStreamingCollection", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("instances", TYPE_ARRAY_STRUCT, "hkaiStreamingCollectionInstanceInfo", 0)
	HK_PATCH_MEMBER_ADDED("aabb", TYPE_STRUCT, "hkAabb", 0)
	HK_PATCH_DEPENDS("hkAabb", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkaiStreamingCollectionInstanceInfo", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiWorld", 16, "hkaiWorld", 17)
	HK_PATCH_MEMBER_REMOVED("streamingManager", TYPE_STRUCT, "hkaiStreamingManager", 0)
	HK_PATCH_MEMBER_ADDED("streamingCollection", TYPE_STRUCT, "hkaiStreamingCollection", 0)
	HK_PATCH_MEMBER_ADDED("meshInstance", TYPE_STRUCT, "hkaiNavMeshInstance", 0)
	HK_PATCH_DEPENDS("hkaiStreamingManager", 4)
	HK_PATCH_DEPENDS("hkaiStreamingCollection", 0)
	HK_PATCH_DEPENDS("hkaiNavMeshInstance", 0)
	//HK_PATCH_FUNCTION(hkaiWorld_16_to_17)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiStreamingManager", 4, "hkaiStreamingManager", 5)
	HK_PATCH_MEMBER_REMOVED("aabb", TYPE_STRUCT, "hkAabb", 0)
	HK_PATCH_DEPENDS("hkAabb", 0)
	//HK_PATCH_FUNCTION(hkaiStreamingManager_4_to_5)
HK_PATCH_END()


HK_PATCH_BEGIN("hkaiNavMeshCutterOriginalEdgeInfo", 1, HK_NULL, HK_CLASS_REMOVED )
	HK_PATCH_MEMBER_REMOVED("oppositeEdge", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("oppositeFace", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("edgeKey", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("faceKey", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()


HK_PATCH_BEGIN("hkaiNavMeshFace", 3, "hkaiNavMeshFace", 4)
	HK_PATCH_MEMBER_REMOVED("clearancesIndex", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMesh", 5, "hkaiNavMesh", 6)
	HK_PATCH_MEMBER_REMOVED("clearanceCache", TYPE_ARRAY_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("globalClearanceCache", TYPE_ARRAY_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("uncutClearanceCacheSize", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("maxGlobalClearance", TYPE_REAL, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiStreamingManagerSectionInfo", 2, "hkaiStreamingManagerSectionInfo", 3)
	HK_PATCH_MEMBER_REMOVED("mediator", TYPE_OBJECT, "hkaiNavMeshQueryMediator", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkaiNavMeshQueryMediator", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	//HK_PATCH_FUNCTION(hkaiStreamingManagerSectionInfo_2_to_3)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiNavVolumeExternalEdgeInfo", 0)
	HK_PATCH_MEMBER_ADDED("edgeIndex", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("cellIndex", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("oppositeUid", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiStreamingCollectionInstanceInfo", 0, "hkaiStreamingCollectionInstanceInfo", 1)
	HK_PATCH_MEMBER_ADDED("volumePtr", TYPE_OBJECT, "hkaiNavVolume", 0)
	HK_PATCH_DEPENDS("hkaiNavVolume", 1)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	//HK_PATCH_FUNCTION(hkaiStreamingCollectionInstanceInfo_0_to_1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavVolume", 0, "hkaiNavVolume", 1)
	HK_PATCH_MEMBER_ADDED("externalEdges", TYPE_ARRAY_STRUCT, "hkaiNavVolumeExternalEdgeInfo", 0)
	HK_PATCH_MEMBER_ADDED("streamingDependencies", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("uid", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("runtimeId", TYPE_INT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkaiNavVolumeExternalEdgeInfo", 0)
	//HK_PATCH_FUNCTION(hkaiNavVolume_0_to_1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavVolumeEdge", 0, "hkaiNavVolumeEdge", 1)
	HK_PATCH_MEMBER_ADDED("flags", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiStreamingManager", 5, "hkaiStreamingManager", 6)
	HK_PATCH_MEMBER_REMOVED("isTemporary", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiStreamingManagerSectionInfo", 3, "hkaiStreamingManagerSectionInfo", 4)
	HK_PATCH_MEMBER_ADDED("volumePtr", TYPE_OBJECT, "hkaiNavVolume", 0)
	HK_PATCH_DEPENDS("hkaiNavVolume", 1)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	//HK_PATCH_FUNCTION(hkaiStreamingManagerSectionInfo_3_to_4)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiVolumePathfindingUtilFindPathInput", 1)
	HK_PATCH_MEMBER_ADDED("startPoint", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("endPoint", TYPE_ARRAY_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("up", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("startCellIndex", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("endCellIndex", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("maxNumberOfIterations", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("agentInfo", TYPE_STRUCT, "hkaiNavMeshTraversalInfo", 0)
	HK_PATCH_MEMBER_ADDED("heuristicWeight", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED_INT("maxOpenSetSizeBytes", 131072)
	HK_PATCH_MEMBER_ADDED_INT("maxSearchStateSizeBytes", 590336)
	HK_PATCH_DEPENDS("hkaiNavMeshTraversalInfo", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiVolumePathfindingUtil", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavVolumeGenerationSettings", 1, "hkaiNavVolumeGenerationSettings", 2)
	HK_PATCH_MEMBER_ADDED("volumeAabb", TYPE_STRUCT, "hkAabb", 0)
	HK_PATCH_DEPENDS("hkAabb", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiNavVolumeCostModifier", 1)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("type", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiDefaultNavVolumeCostModifier", 1)
	HK_PATCH_PARENT_SET(HK_NULL, "hkaiNavVolumeCostModifier")
	HK_PATCH_MEMBER_ADDED("cellMaskLookupTable", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("costMultiplierLookupTable", TYPE_TUPLE_REAL, HK_NULL, 32)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkaiNavVolumeCostModifier", 1)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiNavVolumeGenerationSettingsMergingSettings", 0)
	HK_PATCH_MEMBER_ADDED("nodeWeight", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("edgeWeight", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("multiplier", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("iterationsStabilizationThreshold", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("maxMergingIterations", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavVolumeGenerationSettings", 2, "hkaiNavVolumeGenerationSettings", 3)
	HK_PATCH_MEMBER_REMOVED("iterationsStabilizationThreshold", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("maxMergingIterations", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("mergingSettings", TYPE_STRUCT, "hkaiNavVolumeGenerationSettingsMergingSettings", 0)
	HK_PATCH_DEPENDS("hkaiNavVolumeGenerationSettingsMergingSettings", 0)
	//HK_PATCH_FUNCTION(hkaiNavVolumeGenerationSettings_2_to_3)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavVolumeGenerationSettings", 3, "hkaiNavVolumeGenerationSettings", 4)
	HK_PATCH_MEMBER_DEFAULT_SET_VEC_4("up", 0.000000f,0.000000f,1.000000f,0.000000f)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("minDistanceToSeedPoints", 1.000000f)
	HK_PATCH_MEMBER_DEFAULT_SET_BYTE("saveInputSnapshot", 0)
	HK_PATCH_MEMBER_REMOVED("cellDensity", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED_REAL("cellWidth", 1.000000f)
	HK_PATCH_MEMBER_ADDED_REAL("border", 0.010000f)
	HK_PATCH_MEMBER_ADDED_BYTE("useBorderCells", 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavVolume", 1, "hkaiNavVolume", 2)
	HK_PATCH_MEMBER_REMOVED("cellIndices", TYPE_ARRAY_STRUCT, "hkaiNavVolumeFI", 0)
	HK_PATCH_MEMBER_ADDED("quantizationScale", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("quantizationOffset", TYPE_VEC_4, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavVolumeFI", 0, HK_NULL, HK_CLASS_REMOVED)
	HK_PATCH_MEMBER_REMOVED("a", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("b", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()


HK_PATCH_BEGIN("hkaiNavVolumeGenerationSettingsMergingSettings", 0, "hkaiNavVolumeGenerationSettingsMergingSettings", 1)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("nodeWeight", 10.000000f)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("edgeWeight", 1.000000f)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("multiplier", 1.000000f)
	HK_PATCH_MEMBER_DEFAULT_SET_INT("iterationsStabilizationThreshold", 10)
	HK_PATCH_MEMBER_DEFAULT_SET_INT("maxMergingIterations", 1000000)
	HK_PATCH_MEMBER_ADDED_BYTE("estimateNewEdges", 1)
	HK_PATCH_MEMBER_ADDED_REAL("slopeThreshold", 1.000000f)
	HK_PATCH_MEMBER_ADDED_BYTE("autoSplit", 1)
	HK_PATCH_MEMBER_ADDED_INT("chunkDivsX", 1)
	HK_PATCH_MEMBER_ADDED_INT("chunkDivsY", 1)
	HK_PATCH_MEMBER_ADDED_INT("chunkDivsZ", 1)
	HK_PATCH_MEMBER_ADDED_INT("randomSeed", 123)
	HK_PATCH_MEMBER_ADDED_REAL("splitMergeProb", 0.700000f)
	HK_PATCH_MEMBER_ADDED_BYTE("useSimpleFirstMergePass", 1)
HK_PATCH_END()


HK_PATCH_BEGIN("hkaiNavMeshFace", 4, "hkaiNavMeshFace", 5)
	HK_PATCH_MEMBER_REMOVED("regionId", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("flags", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMesh", 6, "hkaiNavMesh", 7)
	HK_PATCH_MEMBER_REMOVED("numRegions", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()


HK_PATCH_BEGIN("hkaiNavVolume", 2, "hkaiNavVolume", 3)
	HK_PATCH_MEMBER_REMOVED("cellRegions", TYPE_ARRAY_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavVolume", 3, "hkaiNavVolume", 4)
	HK_PATCH_MEMBER_REMOVED("inputFilename", TYPE_CSTRING, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshGenerationSettings", 11, "hkaiNavMeshGenerationSettings", 12)
	HK_PATCH_MEMBER_ADDED_BYTE("characterWidthUsage", 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiWorld", 17, "hkaiWorld", 18)
	HK_PATCH_MEMBER_ADDED("erosionRadius", TYPE_REAL, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMesh", 7, "hkaiNavMesh", 8)
	HK_PATCH_MEMBER_ADDED("erosionRadius", TYPE_REAL, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshGenerationSettings", 12, "hkaiNavMeshGenerationSettings", 13)
	HK_PATCH_MEMBER_REMOVED("mergeColinearEdges", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshGenerationSettingsEdgeMatchingParameters", 1, "hkaiNavMeshGenerationSettingsEdgeMatchingParameters", 2)
	HK_PATCH_MEMBER_ADDED_REAL("edgeTraversibilityHorizontalEpsilon", 0.010000f)
	HK_PATCH_MEMBER_ADDED_REAL("edgeTraversibilityVerticalEpsilon", 0.010000f)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiPathfindingUtilFindPathInput", 1, "hkaiPathfindingUtilFindPathInput", 2)
	HK_PATCH_MEMBER_DEFAULT_SET_INT("maxNumberOfIterations", 100000)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("searchSphereRadius", -1.000000f)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("searchCapsuleRadius", -1.000000f)
	HK_PATCH_MEMBER_DEFAULT_SET_BYTE("useHierarchyInfo", 0)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("heuristicWeight", 1.000000f)
	HK_PATCH_MEMBER_REMOVED("smoothingMode", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED_BYTE("smoothOutputPath", 1)
	HK_PATCH_MEMBER_ADDED_REAL("simpleRadiusThreshold", 0.010000f)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshSimplificationUtilsSettings", 4, "hkaiNavMeshSimplificationUtilsSettings", 5)
	HK_PATCH_MEMBER_ADDED_INT("maxPartitionSize", 40000)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiNavVolumeGenerationSnapshot", 1)
	HK_PATCH_MEMBER_ADDED("geometry", TYPE_STRUCT, "hkGeometry", 0)
	HK_PATCH_MEMBER_ADDED("settings", TYPE_STRUCT, "hkaiNavVolumeGenerationSettings", 0)
	HK_PATCH_DEPENDS("hkGeometry", 0)
	HK_PATCH_DEPENDS("hkaiNavVolumeGenerationSettings", 5)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshGenerationSettings", 13, "hkaiNavMeshGenerationSettings", 14)
	HK_PATCH_MEMBER_ADDED_INT("defaultConstructionProperties", 3)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiPathfindingUtilPathPoint", 0)
	HK_PATCH_MEMBER_ADDED("position", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("userEdgeData", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("userEdgeType", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiPath", 6, "hkaiPath", 7)
	HK_PATCH_MEMBER_REMOVED("segments", TYPE_ARRAY_STRUCT, "hkaiPathSegment", 0)
	HK_PATCH_MEMBER_ADDED("segments", TYPE_ARRAY_STRUCT, "hkaiPathfindingUtilPathPoint", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiPathSegment", 0, HK_NULL, HK_CLASS_REMOVED)
	HK_PATCH_MEMBER_REMOVED("position", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("userEdgeData", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("userEdgeType", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiPathPathPoint", 0)
	HK_PATCH_MEMBER_ADDED("position", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("userEdgeData", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("type", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiPath", 7, "hkaiPath", 8)
	HK_PATCH_MEMBER_REMOVED("segments", TYPE_ARRAY_STRUCT, "hkaiPathfindingUtilPathPoint", 0)
	HK_PATCH_MEMBER_ADDED("segments", TYPE_ARRAY_STRUCT, "hkaiPathPathPoint", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiPathfindingUtilPathPoint", 0, HK_NULL, HK_CLASS_REMOVED)
	HK_PATCH_MEMBER_REMOVED("position", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("userEdgeData", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("userEdgeType", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiWorld", 18, "hkaiWorld", 19)
	HK_PATCH_MEMBER_RENAMED("maxPathSearchSegmentsOut", "maxPathSearchPointsOut")
	HK_PATCH_MEMBER_RENAMED("dynamicMediator", "dynamicNavMeshMediator")
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiPathfindingUtilFindPathInput", 2, "hkaiPathfindingUtilFindPathInput", 3)
	HK_PATCH_MEMBER_REMOVED("smoothOutputPath", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED_BYTE("outputPathType", 2)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiWorld", 19, "hkaiWorld", 20)
	HK_PATCH_MEMBER_ADDED("defaultVolumePathfindingInput", TYPE_STRUCT, "hkaiVolumePathfindingUtilFindPathInput", 0)
	HK_PATCH_DEPENDS("hkaiVolumePathfindingUtilFindPathInput", 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiCharacter", 16, "hkaiCharacter", 17)
	HK_PATCH_MEMBER_ADDED("movementState", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshTraversalInfo", 0, "hkaiAgentTraversalInfo", 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshGenerationSettingsEdgeMatchingParameters", 2, "hkaiNavMeshGenerationSettingsEdgeMatchingParameters", 3)
	HK_PATCH_MEMBER_ADDED_REAL("cosClimbingFaceNormalAlignmentAngle", -0.500000f)
	HK_PATCH_MEMBER_ADDED_REAL("cosClimbingEdgeAlignmentAngle", 0.996195f)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshSimplificationUtilsSettings", 5, "hkaiNavMeshSimplificationUtilsSettings", 6)
	HK_PATCH_MEMBER_ADDED_REAL("maxSharedVertexHorizontalError", 1.000000f)
	HK_PATCH_MEMBER_ADDED_REAL("maxSharedVertexVerticalError", 1.000000f)
	HK_PATCH_MEMBER_ADDED_REAL("maxBoundaryVertexHorizontalError", 1.000000f)
	HK_PATCH_MEMBER_ADDED_REAL("maxBoundaryVertexVerticalError", 1.000000f)
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
