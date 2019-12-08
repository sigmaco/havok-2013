/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Ai specific product patches applied to release 2012_2.
// This file is #included by hkaiPatches_2012_2.cpp

HK_PATCH_BEGIN("hkaiAvoidanceSolverAvoidanceProperties", 10, "hkaiAvoidanceProperties", 11)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiAvoidanceSolverMovementProperties", 6, "hkaiMovementProperties", 7)
HK_PATCH_END()


HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiCuttingGeometryInfo", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("geometry", TYPE_STRUCT, "hkGeometry", 0)
	HK_PATCH_MEMBER_ADDED("cuttingTriangles", TYPE_STRUCT, "hkBitField", 0)
	HK_PATCH_DEPENDS("hkBitField", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkGeometry", 1)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()


HK_PATCH_BEGIN("hkaiWorld", 30, "hkaiWorld", 31)
	HK_PATCH_MEMBER_REMOVED("silhouetteMerger", TYPE_OBJECT, "hkaiSilhouetteMerger", 0)
	HK_PATCH_MEMBER_ADDED("silhouetteGenerationParameters", TYPE_STRUCT, "hkaiSilhouetteGenerationParameters", 0)
	HK_PATCH_DEPENDS("hkaiSilhouetteMerger", 0)
	HK_PATCH_DEPENDS("hkaiSilhouetteGenerationParameters", 0)
	//HK_PATCH_FUNCTION(hkaiWorld_30_to_31)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiSilhouetteGenerator", 0, "hkaiSilhouetteGenerator", 1)
	HK_PATCH_MEMBER_ADDED_INT("materialId", -1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiLocalSteeringInput", 5, "hkaiLocalSteeringInput", 6)
	HK_PATCH_MEMBER_REMOVED("useSamplingAvoidanceSolver", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("collisionPenalty", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("penetrationPenalty", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("sidednessChangingPenalty", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("maximumVelocity", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("velocityHysteresis", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("wallFollowingAngle", TYPE_REAL, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiLineOfSightUtilInputBase", 1, "hkaiLineOfSightUtilInputBase", 2)
	HK_PATCH_MEMBER_DEFAULT_SET_BYTE("exactInternalVertexHandling", 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiJumpDetectionSettingsTrajectory", 0, HK_NULL, HK_CLASS_REMOVED)
	HK_PATCH_MEMBER_REMOVED("points", TYPE_ARRAY_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("width", TYPE_REAL, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiJumpDetectionSettingsJumpDescription", 0, HK_NULL, HK_CLASS_REMOVED)
	HK_PATCH_MEMBER_REMOVED("trajectory", TYPE_STRUCT, "hkaiJumpDetectionSettingsTrajectory", 0)
	HK_PATCH_MEMBER_REMOVED("collidingTrajectories", TYPE_ARRAY_STRUCT, "hkaiJumpDetectionSettingsTrajectory", 0)
	HK_PATCH_MEMBER_REMOVED("requiredPortion", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("blockingTrajectories", TYPE_ARRAY_STRUCT, "hkaiJumpDetectionSettingsTrajectory", 0)
	HK_PATCH_MEMBER_REMOVED("requiredTrajectories", TYPE_ARRAY_STRUCT, "hkaiJumpDetectionSettingsTrajectory", 0)
	HK_PATCH_MEMBER_REMOVED("setback", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("reverseDirection", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("startEdgeData", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("endEdgeData", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("traversalCost", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkaiJumpDetectionSettingsTrajectory", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiJumpDetectionSettings", 0, HK_NULL, HK_CLASS_REMOVED)
	HK_PATCH_PARENT_SET("hkReferencedObject", HK_NULL)
	HK_PATCH_MEMBER_REMOVED("jumpDescriptions", TYPE_ARRAY_STRUCT, "hkaiJumpDetectionSettingsJumpDescription", 0)
	HK_PATCH_MEMBER_REMOVED("up", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("navMeshStartZoneSearchHalfHeight", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("geometryStartZoneSearchHalfHeight", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("geometryEndZoneSearchHalfHeight", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("startZoneMergeDistance", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkaiJumpDetectionSettingsJumpDescription", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiOverlapManagerSection", 0, "hkaiOverlapManagerSection", 1)
	HK_PATCH_MEMBER_ADDED("facePriorities", TYPE_STRUCT, "hkSetIntFloatPair", 0)
	HK_PATCH_MEMBER_ADDED("numOriginalFaces", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("faceIsDirty", TYPE_STRUCT, "hkBitField", 0)
	HK_PATCH_DEPENDS("hkBitField", 0)
	HK_PATCH_DEPENDS("hkSethkIntRealPairhkContainerHeapAllocatorhkMapOperationshkIntRealPair", 0)
	HK_PATCH_DEPENDS("hkSetIntFloatPair", 0)
	//HK_PATCH_FUNCTION(hkaiOverlapManagerSection_0_to_1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiOverlapManager", 0, "hkaiOverlapManager", 1)
	HK_PATCH_MEMBER_ADDED_INT("maxCutFacesPerStep", -1)
	HK_PATCH_MEMBER_REMOVED("faceExtrusion", TYPE_VEC_4, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshGenerationSettingsWallClimbingSettings", 0, "hkaiNavMeshGenerationSettingsWallClimbingSettings", 1)
	HK_PATCH_MEMBER_ADDED_BYTE("enableWallClimbing", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshGenerationSettings", 21, "hkaiNavMeshGenerationSettings", 22)
	HK_PATCH_MEMBER_RENAMED("carvedMaterial", "carvedMaterialDeprecated")
	HK_PATCH_MEMBER_RENAMED("carvedCuttingMaterial", "carvedCuttingMaterialDeprecated")
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiSilhouetteGenerator", 1, "hkaiSilhouetteGenerator", 2)
	HK_PATCH_MEMBER_REMOVED("cachedSilhouettes", TYPE_STRUCT, "hkaiConvexSilhouetteSet", 0)
	HK_PATCH_MEMBER_ADDED("cachedSilhouettes", TYPE_OBJECT, "hkaiConvexSilhouetteSet", 0)
	HK_PATCH_MEMBER_REMOVED("cachedSilhouettesTransform", TYPE_STRUCT, "hkQTransform", 0)
	HK_PATCH_DEPENDS("hkaiConvexSilhouetteSet", 0)
	HK_PATCH_DEPENDS("hkQTransform", 0)
	//HK_PATCH_FUNCTION(hkaiSilhouetteGenerator_1_to_2)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiConvexSilhouetteSet", 0, "hkaiConvexSilhouetteSet", 1)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("cachedTransform", TYPE_STRUCT, "hkQTransform", 0)
	HK_PATCH_MEMBER_ADDED("cachedUp", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkQTransform", 0)
	//HK_PATCH_FUNCTION(hkaiConvexSilhouetteSet_0_to_1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiReferenceFrameAndExtrusion", 0, "hkaiReferenceFrameAndExtrusion", 1)
	HK_PATCH_MEMBER_ADDED_BYTE("upTransformMethod", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiEdgePathFollowingCornerInfo", 1)
        HK_PATCH_MEMBER_ADDED("data", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiEdgePathEdge", 1, "hkaiEdgePathEdge", 2)
	HK_PATCH_MEMBER_ADDED("leftFollowingCorner", TYPE_STRUCT, "hkaiEdgePathFollowingCornerInfo", 0)
	HK_PATCH_MEMBER_ADDED("rightFollowingCorner", TYPE_STRUCT, "hkaiEdgePathFollowingCornerInfo", 0)
	HK_PATCH_MEMBER_REMOVED("face", TYPE_STRUCT, "hkaiPersistentFaceKey", 0)
	HK_PATCH_MEMBER_ADDED("edge", TYPE_STRUCT, "hkaiPersistentEdgeKey", 0)
	HK_PATCH_DEPENDS("hkaiPersistentFaceKey", 0)
	HK_PATCH_DEPENDS("hkaiPersistentEdgeKey", 0)
	HK_PATCH_FUNCTION(hkaiEdgePathEdge_2_to_3)
	HK_PATCH_DEPENDS("hkaiEdgePathFollowingCornerInfo", 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshSimplificationUtilsExtraVertexSettings", 1, "hkaiNavMeshSimplificationUtilsExtraVertexSettings", 2)
	HK_PATCH_MEMBER_ADDED_BYTE("addVerticesOnBoundaryEdges", 1)
	HK_PATCH_MEMBER_ADDED_REAL("boundaryEdgeSplitLength", 50.000000f)
	HK_PATCH_MEMBER_ADDED_REAL("userVertexOnBoundaryTolerance", 0.001000f)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshGenerationSettingsEdgeMatchingParameters", 6, "hkaiNavMeshGenerationSettingsEdgeMatchingParameters", 7)
	HK_PATCH_MEMBER_ADDED_REAL("edgeParallelTolerance", 0.000010f)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshSimplificationUtilsExtraVertexSettings", 2, "hkaiNavMeshSimplificationUtilsExtraVertexSettings", 3)
	HK_PATCH_MEMBER_ADDED_BYTE("vertexSelectionMethod", 0)
	HK_PATCH_MEMBER_ADDED_REAL("areaFraction", 0.000125f)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshGenerationSettings", 22, "hkaiNavMeshGenerationSettings", 23)
	HK_PATCH_MEMBER_REMOVED("maxHorizontalRange", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("maxVerticalRange", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("validateInputGeometry", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED_BYTE("setBestFaceCenters", 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiAvoidanceProperties", 11, "hkaiAvoidanceProperties", 12)
	HK_PATCH_MEMBER_ADDED_REAL("dodgingPenalty", 1.000000f)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiIntervalPartitionLibraryPartitionRecord", 0)
	HK_PATCH_MEMBER_ADDED("intervalDataOffset", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("numIntervals", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("hasYData", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("hasIntData", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiClimbUpAnalyzer", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkaiTraversalAnalyzer")
	HK_PATCH_MEMBER_ADDED("maxUnderhang", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("minUpHeight", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("maxUpHeight", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("grabAngle", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("grabScanDepth", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkaiTraversalAnalyzer", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiTraversalAnalysisSettings", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED_VEC_4("up", 0.000000f,0.000000f,1.000000f,0.000000f)
	HK_PATCH_MEMBER_ADDED_REAL("minEdgeLength", 0.100000f)
	HK_PATCH_MEMBER_ADDED_REAL("maxSectionDistance", 5.000000f)
	HK_PATCH_MEMBER_ADDED_REAL("characterHeight", 2.000000f)
	HK_PATCH_MEMBER_ADDED_REAL("characterRadius", 0.200000f)
	HK_PATCH_MEMBER_ADDED_REAL("raiseEdgeHeightLimit", 1.000000f)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiTraversalAnnotationLibrary", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("up", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("intervalPartitionLibrary", TYPE_STRUCT, "hkaiIntervalPartitionLibrary", 0)
	HK_PATCH_MEMBER_ADDED("userEdgePairs", TYPE_ARRAY_STRUCT, "hkaiUserEdgeUtilsUserEdgePair", 0)
	HK_PATCH_MEMBER_ADDED("annotations", TYPE_ARRAY_STRUCT, "hkaiTraversalAnnotationLibraryAnnotation", 0)
	HK_PATCH_MEMBER_ADDED("vectorLibrary", TYPE_ARRAY_VEC_4, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkaiUserEdgeUtilsUserEdgePair", 1)
	HK_PATCH_DEPENDS("hkaiIntervalPartitionLibrary", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkaiTraversalAnnotationLibraryAnnotation", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiVaultAnalyzer", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkaiTraversalAnalyzer")
	HK_PATCH_MEMBER_ADDED("minWallWidth", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("maxWallWidth", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("minWallHeight", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("maxWallHeight", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("maxUpHeight", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("maxDownHeight", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("verticalApex", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("handPlantAngle", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkaiTraversalAnalyzer", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiTraversalAnalyzer", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED_REAL("maxPlanarAngle", HK_REAL_PI/2 - 0.1f)
	HK_PATCH_MEMBER_ADDED_REAL("maxRelativeSlopeAngle", HK_REAL_PI/2)
	HK_PATCH_MEMBER_ADDED("userdata", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("baseCost", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiIntervalPartitionLibrary", 0)
	HK_PATCH_MEMBER_ADDED("data", TYPE_ARRAY_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("partitionRecords", TYPE_ARRAY_STRUCT, "hkaiIntervalPartitionLibraryPartitionRecord", 0)
	HK_PATCH_DEPENDS("hkaiIntervalPartitionLibraryPartitionRecord", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiDuckUnderAnalyzer", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkaiTraversalAnalyzer")
	HK_PATCH_MEMBER_ADDED("maxHorizontalDistance", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("minClearance", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("maxClearance", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("maxHeightDifference", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkaiTraversalAnalyzer", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiTraversalAnnotationLibraryAnnotation", 0)
	HK_PATCH_MEMBER_ADDED("tEquation", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("userdata", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("firstPartitionIndex", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("firstVectorIndex", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("numPartitions", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("numVectors", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("traversalType", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiJumpAnalyzer", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkaiTraversalAnalyzer")
	HK_PATCH_MEMBER_ADDED("maxHorizontalDistance", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("maxUpHeight", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("maxDownHeight", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("verticalApex", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkaiTraversalAnalyzer", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiSplitGenerationUtilsSettings", 0, "hkaiSplitGenerationUtilsSettings", 1)
	HK_PATCH_MEMBER_ADDED_BYTE("splitMethod", 0)
	HK_PATCH_MEMBER_ADDED_INT("maxSplits", 4)
	HK_PATCH_MEMBER_ADDED_INT("desiredTrisPerChunk", 100000)
	HK_PATCH_MEMBER_DEFAULT_SET_INT("numX", 2)
	HK_PATCH_MEMBER_DEFAULT_SET_INT("numY", 2)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiPersistentEdgeKey", 0)
	HK_PATCH_MEMBER_ADDED("faceKey", TYPE_STRUCT, "hkaiPersistentFaceKey", 0)
	HK_PATCH_MEMBER_ADDED("edgeOffset", TYPE_INT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkaiPersistentFaceKey", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiEdgePath", 0, "hkaiEdgePath", 1)
	HK_PATCH_MEMBER_ADDED("characterRadius", TYPE_REAL, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiPathFollowingProperties", 5, "hkaiPathFollowingProperties", 6)
	HK_PATCH_MEMBER_ADDED_BYTE("pullThroughInternalVertices", 1)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiDropDownAnalyzer", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkaiTraversalAnalyzer")
	HK_PATCH_MEMBER_ADDED("minDropDistance", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("maxDropDistance", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("maxUnderhang", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkaiTraversalAnalyzer", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiHierarchyUtilsClusterSettings", 0)
	HK_PATCH_MEMBER_ADDED_INT("desiredFacesPerCluster", 20)
	HK_PATCH_MEMBER_ADDED_BYTE("ensureClusterPerRegion", 1)
	HK_PATCH_MEMBER_ADDED_POINTER("costModifier", "hkaiAstarCostModifier", 0)
	HK_PATCH_MEMBER_ADDED_POINTER("edgeFilter", "hkaiAstarEdgeFilter", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkaiAstarCostModifier", 3)
	HK_PATCH_DEPENDS("hkaiAstarEdgeFilter", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiHierarchyUtils", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavVolume", 9, "hkaiNavVolume", 10)
	HK_PATCH_MEMBER_ADDED_INT("userData", 0)
HK_PATCH_END()


HK_PATCH_BEGIN("hkaiRigidBodySilhouetteGeneratorBase", 0, "hkaiPhysicsBodySilhouetteGeneratorBase", 1)
HK_PATCH_END()

#if defined(HK_FEATURE_PRODUCT_PHYSICS_2012)
HK_PATCH_BEGIN("hkaiPhysicsShapeVolume", 1, "hkaiPhysics2012ShapeVolume", 2)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiRigidBodySilhouetteGenerator", 1, "hkaiPhysics2012BodySilhouetteGenerator", 2)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiRigidBodyObstacleGenerator", 0, "hkaiPhysics2012BodyObstacleGenerator", 1)
HK_PATCH_END()
#endif

HK_PATCH_BEGIN("hkaiNavMeshGenerationSettings", 23, "hkaiNavMeshGenerationSettings", 24)
	HK_PATCH_MEMBER_ADDED_BYTE("checkEdgeGeometryConsistency", 0)
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
