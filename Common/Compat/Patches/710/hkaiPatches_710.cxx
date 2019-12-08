/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// AI specific product patches applied to release 710.
// This file is #included by hkaiPatches_710.cpp

HK_PATCH_BEGIN("hkaiNavMeshGenerationSettings", 5, "hkaiNavMeshGenerationSettings", 6)
	HK_PATCH_MEMBER_ADDED_INT("edgeMatchingMetric", 2)
	HK_PATCH_MEMBER_ADDED_INT("edgeConnectionIterations", 2)
	HK_PATCH_FUNCTION(hkaiNavMeshGenerationSettings_5_to_6)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiAvoidanceSolverAvoidanceProperties", 4, "hkaiAvoidanceSolverAvoidanceProperties", 5)
	HK_PATCH_MEMBER_REMOVED("radius", TYPE_REAL, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiCharacter", 10, "hkaiCharacter", 11)
	HK_PATCH_MEMBER_ADDED("desiredVelocity", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_FUNCTION(hkaiCharacter_10_to_11)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshGenerationSettings", 6, "hkaiNavMeshGenerationSettings", 7)
	HK_PATCH_MEMBER_ADDED("carvedMaterial", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("carvedCuttingMaterial", TYPE_INT, HK_NULL, 0)
	HK_PATCH_FUNCTION(hkaiNavMeshGenerationSettings_6_to_7)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiWorld", 10, "hkaiWorld", 11)
	HK_PATCH_MEMBER_REMOVED("pendingGoals", TYPE_ARRAY_STRUCT, "hkaiWorldPendingGoal", 0)
	HK_PATCH_MEMBER_REMOVED("pendingGoalPositions", TYPE_ARRAY_VEC_4, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkaiWorldPendingGoal", 1)
	//HK_PATCH_FUNCTION(hkaiWorld_10_to_11)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiWorldPendingGoal", 1, HK_NULL, HK_CLASS_REMOVED)
	HK_PATCH_MEMBER_REMOVED("numPositions", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("character", TYPE_OBJECT, "hkaiCharacter", 0)
	HK_PATCH_MEMBER_REMOVED("positionIndex", TYPE_INT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkaiCharacter", 11)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiWorld", 11, "hkaiWorld", 12)
	HK_PATCH_MEMBER_REMOVED("characters", TYPE_ARRAY_OBJECT, "hkaiCharacter", 0)
	HK_PATCH_MEMBER_REMOVED("projectionMode", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkaiCharacter", 11)
	//HK_PATCH_FUNCTION(hkaiWorld_11_to_12)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshGenerationSettings", 7, "hkaiNavMeshGenerationSettings", 8)
	HK_PATCH_MEMBER_ADDED_BYTE("validateInputGeometry", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiCharacter", 11, "hkaiCharacter", 12)
	HK_PATCH_MEMBER_ADDED("localSensorAabb", TYPE_STRUCT, "hkAabb", 0)
	HK_PATCH_MEMBER_REMOVED("path", TYPE_OBJECT, "hkaiPath", 0)
	HK_PATCH_DEPENDS("hkAabb", 0)
	HK_PATCH_DEPENDS("hkaiPath", 6)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshEdge", 3, "hkaiNavMeshEdge", 4)
	HK_PATCH_MEMBER_ADDED("padding", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiCharacter", 12, "hkaiCharacter", 13)
	HK_PATCH_MEMBER_ADDED("currentNavMeshFace", TYPE_INT, HK_NULL, 0)
	HK_PATCH_FUNCTION(hkaiCharacter_12_to_13)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiCharacterRepathInformation", 0, "hkaiCharacterRepathInformation", 1)
	HK_PATCH_MEMBER_REMOVED("pathAge", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("meshWasCut", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiWorld", 12, "hkaiWorld", 13)
	HK_PATCH_MEMBER_ADDED("maxRequestsPerStep", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("priorityThreshold", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiDefaultLocalSteeringPathFollowingProperties", 1, "hkaiDefaultLocalSteeringPathFollowingProperties", 2)
	HK_PATCH_MEMBER_REMOVED("changeSegmentDist", TYPE_REAL, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshSimplificationUtilsSettings", 1, "hkaiNavMeshSimplificationUtilsSettings", 2)
	HK_PATCH_MEMBER_ADDED_REAL("cosConvexThreshold", 0.99f)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiWorld", 13, "hkaiWorld", 14)
	HK_PATCH_MEMBER_ADDED("numPathRequestsPerJob", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("numBehaviorUpdatesPerJob", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("numCharactersPerAvoidanceJob", TYPE_INT, HK_NULL, 0)
	HK_PATCH_FUNCTION(hkaiWorld_13_to_14)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiCharacter", 13, "hkaiCharacter", 14)
	HK_PATCH_MEMBER_ADDED("avoidanceProperties", TYPE_OBJECT, "hkaiAvoidanceSolverAvoidanceProperties", 0)
	HK_PATCH_DEPENDS("hkaiAvoidanceSolverAvoidanceProperties", 5)
	//HK_PATCH_FUNCTION(hkaiCharacter_13_to_14)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiCharacter", 14, "hkaiCharacter", 15)
	HK_PATCH_MEMBER_REMOVED("id", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiAvoidanceSolverAvoidanceProperties", 5, "hkaiAvoidanceSolverAvoidanceProperties", 6)
	HK_PATCH_MEMBER_REMOVED("obstaclePenaltyWeight", TYPE_REAL, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshFace", 1, "hkaiNavMeshFace", 2)
	HK_PATCH_MEMBER_ADDED("padding", TYPE_INT, HK_NULL, 0)
	HK_PATCH_FUNCTION(hkaiNavMeshFace_1_to_2)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiWorld", 14, "hkaiWorld", 15)
	HK_PATCH_MEMBER_ADDED("maxPathSearchEdgesOut", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("maxPathSearchSegmentsOut", TYPE_INT, HK_NULL, 0)
	HK_PATCH_FUNCTION(hkaiWorld_14_to_15)
HK_PATCH_END()


HK_PATCH_BEGIN("hkaiDefaultNavMeshCostModifier", 0, "hkaiDefaultNavMeshCostModifier", 1)
	HK_PATCH_PARENT_SET("hkReferencedObject", "hkaiNavMeshCostModifier")
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshCostModifier", 0, "hkaiNavMeshCostModifier", 1)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("type", TYPE_INT, HK_NULL, 0)
	HK_PATCH_FUNCTION(hkaiNavMeshCostModifier_0_to_1)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiNavMeshTraversalInfo", 0)
	HK_PATCH_MEMBER_ADDED("diameter", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("filterInfo", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiPathfindingUtil", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiPathfindingUtilFindPathInput", 0)
	HK_PATCH_MEMBER_ADDED("startPoint", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("endPoint", TYPE_ARRAY_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("up", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("startFaceIndex", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("endFaceIndex", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("maxNumberOfIterations", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("characterInfo", TYPE_STRUCT, "hkaiNavMeshTraversalInfo", 0)
	HK_PATCH_MEMBER_ADDED("smoothingMode", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("searchSphereRadius", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("searchCapsuleRadius", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("checkForDirectPath", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("useHierarchyInfo", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("heuristicWeight", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED_INT("maxOpenSetSizeBytes", 131072)
	HK_PATCH_MEMBER_ADDED_INT("maxSearchStateSizeBytes", 590336)
	HK_PATCH_MEMBER_ADDED_INT("maxHierarchyOpenSetSizeBytes", 32768)
	HK_PATCH_MEMBER_ADDED_INT("maxHierarchySearchStateSizeBytes", 147968)
	HK_PATCH_DEPENDS("hkaiNavMeshTraversalInfo", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiWorld", 15, "hkaiWorld", 16)
	HK_PATCH_MEMBER_ADDED("defaultPathfindingInput", TYPE_STRUCT, "hkaiPathfindingUtilFindPathInput", 0)
	HK_PATCH_DEPENDS("hkaiPathfindingUtilFindPathInput", 0)
	HK_PATCH_FUNCTION(hkaiWorld_15_to_16)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiPlaneVolume", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkaiVolume")
	HK_PATCH_MEMBER_ADDED("planes", TYPE_ARRAY_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("geometry", TYPE_STRUCT, "hkGeometry", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkaiVolume", 0)
	HK_PATCH_DEPENDS("hkGeometry", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiInvertedAabbVolume", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkaiVolume")
	HK_PATCH_MEMBER_ADDED("aabb", TYPE_STRUCT, "hkAabb", 0)
	HK_PATCH_MEMBER_ADDED("geometry", TYPE_STRUCT, "hkGeometry", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkAabb", 0)
	HK_PATCH_DEPENDS("hkaiVolume", 0)
	HK_PATCH_DEPENDS("hkGeometry", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshCostModifier", 1, "hkaiNavMeshCostModifier", 2)
	HK_PATCH_MEMBER_REMOVED("type", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("type", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

#if defined(HK_FEATURE_PRODUCT_AI) && defined(HK_FEATURE_PRODUCT_PHYSICS_2012)
HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiPhysicsShapeVolume", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkaiVolume")
	HK_PATCH_MEMBER_ADDED("shape", TYPE_OBJECT, "hkpShape", 0)
	HK_PATCH_MEMBER_ADDED("shapeTransform", TYPE_VEC_16, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkpShape", 0)
	HK_PATCH_DEPENDS("hkaiVolume", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()
#endif //AI+PHYSICS_2012

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiUserEdgeUtilsObb", 0)
	HK_PATCH_MEMBER_ADDED("transform", TYPE_VEC_16, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("halfExtents", TYPE_VEC_4, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiUserEdgeUtils", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiUserEdgeUtilsUserEdgePair", 0)
	HK_PATCH_MEMBER_ADDED("x", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("y", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("z", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("meshUidA", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("meshUidB", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("faceA", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("faceB", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("userDataA", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("userDataB", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("costAtoB", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("costBtoA", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("direction", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiUserEdgeUtilsUserEdgeSetup", 0)
	HK_PATCH_MEMBER_ADDED("obbA", TYPE_STRUCT, "hkaiUserEdgeUtilsObb", 0)
	HK_PATCH_MEMBER_ADDED("obbB", TYPE_STRUCT, "hkaiUserEdgeUtilsObb", 0)
	HK_PATCH_MEMBER_ADDED("userDataA", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("userDataB", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("costAtoB", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("costBtoA", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("direction", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkaiUserEdgeUtilsObb", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiCharacter", 15, "hkaiCharacter", 16)
	HK_PATCH_MEMBER_REMOVED("currentPathSegment", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("repathInformation", TYPE_STRUCT, "hkaiCharacterRepathInformation", 0)
	HK_PATCH_DEPENDS("hkaiCharacterRepathInformation", 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiCharacterRepathInformation", 1, HK_NULL, HK_CLASS_REMOVED)
	HK_PATCH_MEMBER_REMOVED("pathFailCount", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshGenerationSettings", 8, "hkaiNavMeshGenerationSettings", 9)
	HK_PATCH_MEMBER_RENAMED("minDistanceToSpawnPoints", "minDistanceToSeedPoints")
	HK_PATCH_MEMBER_RENAMED("regionSpawnPoints", "regionSeedPoints")
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshSimplificationUtilsSettings", 2, "hkaiNavMeshSimplificationUtilsSettings", 3)
	HK_PATCH_MEMBER_RENAMED("maxArea", "maxBorderSimplifyArea")
	HK_PATCH_MEMBER_RENAMED("concaveMaxArea", "maxConcaveBorderSimplifyArea")
	HK_PATCH_MEMBER_RENAMED("maxHeightError", "maxBorderHeightError")
	HK_PATCH_MEMBER_RENAMED("maxPartitioningHeight", "maxPartitionHeightError")
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshSimplificationUtilsSettings", 3, "hkaiNavMeshSimplificationUtilsSettings", 4)
	HK_PATCH_MEMBER_ADDED_REAL("boundaryEdgeFilterThreshold", 0.010000f)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiPathfindingUtilFindPathInput", 0, "hkaiPathfindingUtilFindPathInput", 1)
	HK_PATCH_MEMBER_RENAMED("characterInfo", "agentInfo")
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshGenerationSettings", 9, "hkaiNavMeshGenerationSettings", 10)
	HK_PATCH_MEMBER_ADDED_REAL("loopReplacementArea", 0.000000f)
	HK_PATCH_FUNCTION(hkaiNavMeshGenerationSettings_9_to_10)
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
