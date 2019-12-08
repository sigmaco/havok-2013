/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// AI specific product patches applied to release 2010_2.
// This file is #included by hkaiPatches_2010_2.cpp

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiNavVolumeGenerationSettingsMaterialConstructionInfo", 0)
	HK_PATCH_MEMBER_ADDED("materialIndex", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("flags", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavVolumeGenerationSettings", 4, "hkaiNavVolumeGenerationSettings", 5)
	HK_PATCH_MEMBER_ADDED_INT("defaultConstructionProperties", 1)
	HK_PATCH_MEMBER_ADDED("materialMap", TYPE_ARRAY_STRUCT, "hkaiNavVolumeGenerationSettingsMaterialConstructionInfo", 0)
	HK_PATCH_DEPENDS("hkaiNavVolumeGenerationSettingsMaterialConstructionInfo", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiNavMeshGenerationSettingsInternalTestingSettings", 1)
	HK_PATCH_MEMBER_ADDED("tinyLoopsThreshold", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("triangulateWithoutLoops", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshGenerationSettings", 14, "hkaiNavMeshGenerationSettings", 15)
        HK_PATCH_MEMBER_ADDED("internalSettings", TYPE_STRUCT, "hkaiNavMeshGenerationSettingsInternalTestingSettings", 0)
        HK_PATCH_DEPENDS("hkaiNavMeshGenerationSettingsInternalTestingSettings", 1)
        //HK_PATCH_FUNCTION(hkaiNavMeshGenerationSettings_14_to_15)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiAvoidanceSolverMovementProperties", 1, "hkaiAvoidanceSolverMovementProperties", 2)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("minVelocity", 0.020000f)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("maxVelocity", 5.640000f)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("maxAcceleration", 20.000000f)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("maxDeceleration", 30.000000f)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("maxAngularVelocity", 1.25f * HK_REAL_PI )
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("maxAngularAcceleration", 37.5f * HK_REAL_PI)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("maxTurnVelocity", 2.820000f)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavVolumeGenerationSettingsMergingSettings", 1, "hkaiNavVolumeGenerationSettingsMergingSettings", 2)
	HK_PATCH_MEMBER_REMOVED("splitMergeProb", TYPE_REAL, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavVolumeGenerationSettingsMaterialConstructionInfo", 0, "hkaiNavVolumeGenerationSettingsMaterialConstructionInfo", 1)
	HK_PATCH_MEMBER_ADDED_INT("resolution", 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiVolumePathfindingUtilFindPathInput", 1, "hkaiVolumePathfindingUtilFindPathInput", 2)
	HK_PATCH_MEMBER_ADDED("checkForDirectPath", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

#if defined(HK_FEATURE_PRODUCT_AI) && defined(HK_FEATURE_PRODUCT_PHYSICS_2012)
HK_PATCH_BEGIN("hkaiPhysicsShapeVolume", 0, "hkaiPhysicsShapeVolume", 1)
	HK_PATCH_MEMBER_ADDED("geometry", TYPE_STRUCT, "hkGeometry", 0)
	HK_PATCH_DEPENDS("hkGeometry", 0)
	//HK_PATCH_FUNCTION(hkaiPhysicsShapeVolume_0_to_1)
HK_PATCH_END()
#endif

// tuple/tuple update
HK_PATCH_BEGIN("hkaiNavMeshCutter", 7, "hkaiNavMeshCutter", 8)
	HK_PATCH_MEMBER_RENAMED("meshInfos", "old_meshInfos")
	HK_PATCH_MEMBER_ADDED("meshInfos",  TYPE_ARRAY_STRUCT, "hkaiNavMeshCutterMeshInfo", 0)
	HK_PATCH_FUNCTION(hkaiNavMeshCutter_7_to_8)
	HK_PATCH_MEMBER_REMOVED("old_meshInfos", TYPE_ARRAY_OBJECT, "hkaiNavMeshCutterMeshInfo", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiNavMeshPathSearchParameters", 0)
	HK_PATCH_MEMBER_ADDED("up", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED_BYTE("outputPathType", 2)
	HK_PATCH_MEMBER_ADDED_BYTE("checkForDirectPath", 1)
	HK_PATCH_MEMBER_ADDED_BYTE("useHierarchicalHeuristic", 0)
	HK_PATCH_MEMBER_ADDED_REAL("heuristicWeight", 1.000000f)
	HK_PATCH_MEMBER_ADDED_REAL("simpleRadiusThreshold", 0.010000f)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiPathfindingUtilFindPathInput", 3, "hkaiPathfindingUtilFindPathInput", 4)
	HK_PATCH_MEMBER_ADDED("searchParameters", TYPE_STRUCT, "hkaiNavMeshPathSearchParameters", 0)
	HK_PATCH_DEPENDS("hkaiNavMeshPathSearchParameters", 0)
	HK_PATCH_FUNCTION(hkaiPathfindingUtilFindPathInput_3_to_4)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiPathfindingUtilFindPathInput", 4, "hkaiPathfindingUtilFindPathInput", 5)
	HK_PATCH_MEMBER_REMOVED("up", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("checkForDirectPath", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("useHierarchyInfo", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("heuristicWeight", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("simpleRadiusThreshold", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("outputPathType", TYPE_BYTE, HK_NULL, 0)
	//HK_PATCH_FUNCTION(hkaiPathfindingUtilFindPathInput_4_to_5)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshPathSearchParameters", 0, "hkaiNavMeshPathSearchParameters", 1)
	HK_PATCH_MEMBER_ADDED_INT("maxOpenSetSizeBytes", 0)
	HK_PATCH_MEMBER_ADDED_INT("maxSearchStateSizeBytes", 0)
	HK_PATCH_MEMBER_ADDED_INT("maxHierarchyOpenSetSizeBytes", 0)
	HK_PATCH_MEMBER_ADDED_INT("maxHierarchySearchStateSizeBytes", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiPathfindingUtilFindPathInput", 5, "hkaiPathfindingUtilFindPathInput", 6)
	HK_PATCH_DEPENDS("hkaiNavMeshPathSearchParameters", 1)
	HK_PATCH_FUNCTION(hkaiPathfindingUtilFindPathInput_5_to_6)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiPathfindingUtilFindPathInput", 6, "hkaiPathfindingUtilFindPathInput", 7)
	HK_PATCH_MEMBER_REMOVED("maxOpenSetSizeBytes", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("maxSearchStateSizeBytes", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("maxHierarchyOpenSetSizeBytes", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("maxHierarchySearchStateSizeBytes", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshPathSearchParameters", 1, "hkaiNavMeshPathSearchParameters", 2)
	HK_PATCH_MEMBER_ADDED_BYTE("userEdgeTraversalTestType", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiWorld", 20, "hkaiWorld", 21)
	HK_PATCH_MEMBER_ADDED_BYTE("performValidationChecks", 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshCutter", 8, "hkaiNavMeshCutter", 9)
	HK_PATCH_MEMBER_ADDED_BYTE("performValidationChecks", 1)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiNavVolumePathSearchParameters", 0)
	HK_PATCH_MEMBER_ADDED("up", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED_BYTE("checkForDirectPath", 1)
	HK_PATCH_MEMBER_ADDED_REAL("heuristicWeight", 1.000000f)
	HK_PATCH_MEMBER_ADDED_INT("maxOpenSetSizeBytes", 0)
	HK_PATCH_MEMBER_ADDED_INT("maxSearchStateSizeBytes", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiVolumePathfindingUtilFindPathInput", 2, "hkaiVolumePathfindingUtilFindPathInput", 3)
	HK_PATCH_MEMBER_ADDED("searchParameters", TYPE_STRUCT, "hkaiNavVolumePathSearchParameters", 0)
	HK_PATCH_DEPENDS("hkaiNavVolumePathSearchParameters", 0)
	HK_PATCH_FUNCTION(hkaiVolumePathfindingUtilFindPathInput_2_to_3)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiVolumePathfindingUtilFindPathInput", 3, "hkaiVolumePathfindingUtilFindPathInput", 4)
	HK_PATCH_MEMBER_REMOVED("up", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("checkForDirectPath", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("heuristicWeight", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("maxOpenSetSizeBytes", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("maxSearchStateSizeBytes", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiPath", 8, "hkaiPath", 9)
	HK_PATCH_MEMBER_RENAMED("segments", "points")
	HK_PATCH_DEPENDS("hkaiPathPathPoint", 0)
	//HK_PATCH_FUNCTION(hkaiPath_8_to_9)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiStreamingManagerSectionInfo", 4, "hkaiStreamingManagerSectionInfo", 5)
	HK_PATCH_MEMBER_RENAMED("sectionPtr", "meshPtr")
	HK_PATCH_MEMBER_RENAMED("clusterGraph", "meshGraphPtr")
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkaiNavMesh", 8)
	HK_PATCH_DEPENDS("hkaiDirectedGraphExplicitCost", 1)
	//HK_PATCH_FUNCTION(hkaiStreamingManagerSectionInfo_4_to_5)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavVolume", 4, "hkaiNavVolume", 5)
	HK_PATCH_MEMBER_RENAMED("uid", "sectionUid")
	//HK_PATCH_FUNCTION(hkaiNavVolume_4_to_5)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiDirectedGraphExplicitCost", 1, "hkaiDirectedGraphExplicitCost", 2)
	HK_PATCH_MEMBER_ADDED_INT("runtimeId", -1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavVolume", 5, "hkaiNavVolume", 6)
	HK_PATCH_MEMBER_DEFAULT_SET_INT("runtimeId", -1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiDirectedGraphExplicitCost", 2, "hkaiDirectedGraphExplicitCost", 3)
	HK_PATCH_MEMBER_DEFAULT_SET_INT("sectionUid", 0)
	HK_PATCH_MEMBER_DEFAULT_SET_INT("runtimeId", 0)
	HK_PATCH_MEMBER_REMOVED("runtimeId", TYPE_INT, HK_NULL, 0)
	HK_PATCH_FUNCTION(hkaiDirectedGraphExplicitCost_2_to_3)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavVolume", 6, "hkaiNavVolume", 7)
	HK_PATCH_MEMBER_DEFAULT_SET_INT("sectionUid", 0)
	HK_PATCH_MEMBER_DEFAULT_SET_INT("runtimeId", 0)
	HK_PATCH_MEMBER_REMOVED("runtimeId", TYPE_INT, HK_NULL, 0)
	HK_PATCH_FUNCTION(hkaiNavVolume_6_to_7)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMesh", 8, "hkaiNavMesh", 9)
	HK_PATCH_MEMBER_DEFAULT_SET_INT("sectionUid", 0)
	HK_PATCH_MEMBER_DEFAULT_SET_INT("runtimeId", 0)
	HK_PATCH_MEMBER_REMOVED("runtimeId", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiUserEdgePairArray", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("edgePairs", TYPE_ARRAY_STRUCT, "hkaiUserEdgeUtilsUserEdgePair", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkaiUserEdgeUtilsUserEdgePair", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiUserEdgeSetupArray", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("edgeSetups", TYPE_ARRAY_STRUCT, "hkaiUserEdgeUtilsUserEdgeSetup", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkaiUserEdgeUtilsUserEdgeSetup", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiUserEdgeUtilsUserEdgeSetup", 0, "hkaiUserEdgeUtilsUserEdgeSetup", 1)
	HK_PATCH_MEMBER_ADDED_BYTE("forceAlign", 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiDirectedGraphExplicitCost", 3, "hkaiDirectedGraphExplicitCost", 4)
	HK_PATCH_MEMBER_ADDED("sectionDependencies", TYPE_ARRAY_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiGraphPathSearchParameters", 0)
	HK_PATCH_MEMBER_ADDED_INT("maxOpenSetSizeBytes", 0)
	HK_PATCH_MEMBER_ADDED_INT("maxSearchStateSizeBytes", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiPathfindingUtilFindGraphPathInput", 0)
	HK_PATCH_MEMBER_ADDED("startNodeKey", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("goalNodeKey", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED_INT("maxNumberOfIterations", 100000)
	HK_PATCH_MEMBER_ADDED("searchParameters", TYPE_STRUCT, "hkaiGraphPathSearchParameters", 0)
	HK_PATCH_DEPENDS("hkaiGraphPathSearchParameters", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshGenerationSettings", 15, "hkaiNavMeshGenerationSettings", 16)
	HK_PATCH_MEMBER_REMOVED("loopReplacementArea", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("loopFinderSettings", TYPE_STRUCT, "hkaiLoopFinderSettings", 0)
	HK_PATCH_MEMBER_REMOVED("pruneColinearHoleVertices", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiLoopFinderSettings", 0, HK_NULL, HK_CLASS_REMOVED)
	HK_PATCH_MEMBER_REMOVED("colinearAngle", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("colinearDistance", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("degenerateLength", TYPE_REAL, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiNavMeshGenerationSettingsRegionPruningSettings", 0)
	HK_PATCH_MEMBER_ADDED_REAL("minRegionArea", 5.0f)
	HK_PATCH_MEMBER_ADDED_REAL("minDistanceToSeedPoints", 1.0f)
	HK_PATCH_MEMBER_ADDED_REAL("borderPreservationTolerance", .1f)
	HK_PATCH_MEMBER_ADDED("regionSeedPoints", TYPE_ARRAY_VEC_4, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshGenerationSettings", 16, "hkaiNavMeshGenerationSettings", 17)
	HK_PATCH_MEMBER_ADDED("regionPruningSettings", TYPE_STRUCT, "hkaiNavMeshGenerationSettingsRegionPruningSettings", 0)
	HK_PATCH_DEPENDS("hkaiNavMeshGenerationSettingsRegionPruningSettings", 0)
	HK_PATCH_FUNCTION(hkaiNavMeshGenerationSettings_16_to_17)
	HK_PATCH_MEMBER_REMOVED("minRegionArea", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("minDistanceToSeedPoints", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("regionSeedPoints", TYPE_ARRAY_VEC_4, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiWorld", 21, "hkaiWorld", 22)
	HK_PATCH_MEMBER_REMOVED("cutter", TYPE_STRUCT, "hkaiNavMeshCutter", 0)
	HK_PATCH_MEMBER_ADDED("cutter", TYPE_OBJECT, "hkaiNavMeshCutter", 0)
	HK_PATCH_DEPENDS("hkaiNavMeshCutter", 8)
	//HK_PATCH_FUNCTION(hkaiWorld_21_to_22)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshSimplificationUtilsSettings", 6, "hkaiNavMeshSimplificationUtilsSettings", 7)
        HK_PATCH_MEMBER_ADDED_BYTE("useConservativeHeightPartitioning", 0)
        HK_PATCH_MEMBER_ADDED_REAL("hertelMehlhornHeightError", 0.010000f)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshSimplificationUtilsSettings", 7, "hkaiNavMeshSimplificationUtilsSettings", 8)
        HK_PATCH_MEMBER_DEFAULT_SET_BYTE("useHeightPartitioning", 0)
        HK_PATCH_MEMBER_DEFAULT_SET_REAL("maxPartitionHeightError", 100.000000f)
        HK_PATCH_MEMBER_ADDED_REAL("maxBorderDistanceError", 2.000000f)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshSimplificationUtilsSettings", 8, "hkaiNavMeshSimplificationUtilsSettings", 9)
        HK_PATCH_MEMBER_ADDED_REAL("nonconvexityThreshold", 0.100000f)
        HK_PATCH_MEMBER_RENAMED("cosConvexThreshold", "cosPlanarityThreshold")
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiPathPathPoint", 0, "hkaiPathPathPoint", 1)
	HK_PATCH_MEMBER_REMOVED("type", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("flags", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiWorld", 22, "hkaiWorld", 23)
	HK_PATCH_MEMBER_ADDED("maxEstimatedIterationsPerStep", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiPathfindingUtilFindPathInput", 7, "hkaiPathfindingUtilFindPathInput", 8)
	HK_PATCH_MEMBER_RENAMED("endPoint", "goalPoints")
	HK_PATCH_MEMBER_RENAMED("startFaceIndex", "startFaceKey")
	HK_PATCH_MEMBER_RENAMED("endFaceIndex", "goalFaceKeys")
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiVolumePathfindingUtilFindPathInput", 4, "hkaiVolumePathfindingUtilFindPathInput", 5)
	HK_PATCH_MEMBER_RENAMED("endPoint", "goalPoints")
	HK_PATCH_MEMBER_RENAMED("startCellIndex", "startCellKey")
	HK_PATCH_MEMBER_RENAMED("endCellIndex", "goalCellKeys")
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMesh", 9, "hkaiNavMesh", 10)
	HK_PATCH_MEMBER_ADDED_INT("userData", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiStaticTree", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("treePtr", TYPE_OBJECT, "hkcdStaticTreeDefaultTreeStorage6", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeDefaultTreeStorage6", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeTreehkcdStaticTreeDynamicStorage6", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeDynamicStorage6", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeDynamicStoragehkcdStaticTreeCodec3Axis6", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavVolumeGenerationSettingsMergingSettings", 2, "hkaiNavVolumeGenerationSettingsMergingSettings", 3)
	HK_PATCH_MEMBER_REMOVED("autoSplit", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("chunkDivsX", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("chunkDivsY", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("chunkDivsZ", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshGenerationSettings", 17, "hkaiNavMeshGenerationSettings", 18)
	HK_PATCH_MEMBER_REMOVED("internalSettings", TYPE_STRUCT, "hkaiNavMeshGenerationSettingsInternalTestingSettings", 0)
	HK_PATCH_DEPENDS("hkaiNavMeshGenerationSettingsInternalTestingSettings", 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshGenerationSettingsInternalTestingSettings", 1, HK_NULL, HK_CLASS_REMOVED)
	HK_PATCH_MEMBER_REMOVED("tinyLoopsThreshold", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("triangulateWithoutLoops", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiStreamingCollection", 0, "hkaiStreamingCollection", 1)
	HK_PATCH_MEMBER_REMOVED("aabb", TYPE_STRUCT, "hkAabb", 0)
	HK_PATCH_DEPENDS("hkAabb", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiCharacter", 17, "hkaiCharacter", 18)
	HK_PATCH_MEMBER_ADDED("desiredFutureDir", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("distToLocalGoal", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("timeToLocalGoal", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("isLocalGoalLast", TYPE_BYTE, HK_NULL, 0)
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
