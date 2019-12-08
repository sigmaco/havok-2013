/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Ai specific product patches applied to release 2012_1.
// This file is #included by hkaiPatches_2012_1.cpp

HK_PATCH_BEGIN("hkaiAstarOutputParameters", 0, "hkaiAstarOutputParameters", 1)
	HK_PATCH_MEMBER_DEFAULT_SET_INT("numIterations", 0)
	HK_PATCH_MEMBER_DEFAULT_SET_INT("goalIndex", -1)
	HK_PATCH_MEMBER_DEFAULT_SET_INT("status", 0)
	HK_PATCH_MEMBER_ADDED_BYTE("terminationCause", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiPathFollowingProperties", 4, "hkaiPathFollowingProperties",5)
	HK_PATCH_MEMBER_ADDED_INT("incompleteRepathSegments", 8)
	HK_PATCH_MEMBER_ADDED_BYTE("repairPaths", 1)
	HK_PATCH_MEMBER_ADDED_BYTE("setManualControlOnUserEdges", 0)
	HK_PATCH_MEMBER_ADDED_REAL("userEdgeTolerance", 0.250000f)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiAvoidanceSolverMovementProperties", 5, "hkaiAvoidanceSolverMovementProperties", 6)
	HK_PATCH_MEMBER_ADDED_REAL("leftTurnRadius", -1.000000f)
	HK_PATCH_MEMBER_ADDED_REAL("rightTurnRadius", -1.000000f)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiAvoidanceSolverAvoidanceProperties", 9, "hkaiAvoidanceSolverAvoidanceProperties", 10)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("limitBoundaryDistance", -1.000000f)
	HK_PATCH_MEMBER_ADDED_BYTE("avoidanceSolverType", 0)
	HK_PATCH_MEMBER_ADDED_BYTE("nearbyBoundariesSearchType", 1)
	HK_PATCH_MEMBER_ADDED_REAL("velocityHysteresis", 0.010000f)
	HK_PATCH_MEMBER_ADDED_REAL("sidednessChangingPenalty", 0.000000f)
	HK_PATCH_MEMBER_ADDED_INT("maxNeighbors", 16)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("wallFollowingFactor", 0.010000f)
	HK_PATCH_MEMBER_ADDED("localSensorAabb", TYPE_STRUCT, "hkAabb", 0)
	HK_PATCH_DEPENDS("hkAabb", 0)
	HK_PATCH_MEMBER_ADDED_REAL("wallFollowingAngle", 0.100000f)
	HK_PATCH_FUNCTION(hkaiAvoidanceSolverAvoidanceProperties_9_to_10)
	HK_PATCH_MEMBER_REMOVED("wallFollowingFactor", TYPE_REAL, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiLocalSteeringInput", 4, "hkaiLocalSteeringInput", 5)
	HK_PATCH_MEMBER_ADDED("sidednessChangingPenalty", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("maximumVelocity", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("velocityHysteresis", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("enableLocalSteering", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("localGoalPlane", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("wallFollowingAngle", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_FUNCTION(hkaiLocalSteeringInput_4_to_5)
	HK_PATCH_MEMBER_REMOVED("wallFollowingFactor", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("nextCorner", TYPE_VEC_4, HK_NULL, 0)
HK_PATCH_END()


HK_PATCH_BEGIN("hkaiNavMesh", 13, "hkaiNavMesh", 14)
	HK_PATCH_MEMBER_ADDED("faceData", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("edgeData", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED_INT("faceDataStriding", 1)
	HK_PATCH_MEMBER_ADDED_INT("edgeDataStriding", 1)
	HK_PATCH_FUNCTION(hkaiNavMesh_13_to_14)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshInstance", 3, "hkaiNavMeshInstance", 4)
	HK_PATCH_MEMBER_ADDED("instancedFaceData", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("instancedEdgeData", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("ownedFaceData", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("ownedEdgeData", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_FUNCTION(hkaiNavMeshInstance_3_to_4)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshEdge", 7, "hkaiNavMeshEdge", 8)
	HK_PATCH_MEMBER_REMOVED("data", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("padding", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshFace", 5, "hkaiNavMeshFace", 6)
	HK_PATCH_MEMBER_REMOVED("data", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiNavMeshSimplificationUtilsExtraVertexSettings", 0)
	HK_PATCH_MEMBER_ADDED_REAL("vertexFraction", 0.025000f)
	HK_PATCH_MEMBER_ADDED_REAL("minPartitionArea", 1000.000000f)
	HK_PATCH_MEMBER_ADDED_INT("numSmoothingIterations", 20)
	HK_PATCH_MEMBER_ADDED_REAL("iterationDamping", 0.050000f)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshSimplificationUtilsSettings", 11, "hkaiNavMeshSimplificationUtilsSettings", 12)
	HK_PATCH_MEMBER_ADDED("extraVertexSettings", TYPE_STRUCT, "hkaiNavMeshSimplificationUtilsExtraVertexSettings", 0)
	HK_PATCH_DEPENDS("hkaiNavMeshSimplificationUtilsExtraVertexSettings", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiCharacter", 26, "hkaiCharacter", 27)
	HK_PATCH_MEMBER_REMOVED("maxNeighbors", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("avoidanceSolverType", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("nearbyBoundariesSearchType", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("localSensorAabb", TYPE_STRUCT, "hkAabb", 0)
	HK_PATCH_DEPENDS("hkAabb", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiEdgePathEdge", 0)
	HK_PATCH_MEMBER_ADDED("left", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("right", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("up", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("followingTransform", TYPE_VEC_16, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("face", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("flags", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiEdgePath", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("edges", TYPE_ARRAY_STRUCT, "hkaiEdgePathEdge", 0)
	HK_PATCH_MEMBER_ADDED("edgeData", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED_INT("edgeDataStriding", 0)
	HK_PATCH_MEMBER_ADDED("leftTurnRadius", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("rightTurnRadius", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkaiEdgePathEdge", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiPersistentFaceKey", 0)
	HK_PATCH_MEMBER_ADDED("key", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("offset", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiEdgePathEdge", 0, "hkaiEdgePathEdge", 1)
	HK_PATCH_MEMBER_ADDED("facePersistent", TYPE_STRUCT, "hkaiPersistentFaceKey", 0)
	HK_PATCH_FUNCTION(hkaiEdgePathEdge_0_to_1)
	HK_PATCH_MEMBER_REMOVED("face", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_RENAMED("facePersistent", "face")
	HK_PATCH_DEPENDS("hkaiPersistentFaceKey", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiAvoidanceSolverSphereObstacle", 0)
	HK_PATCH_MEMBER_ADDED("sphere", TYPE_STRUCT, "hkSphere", 0)
	HK_PATCH_MEMBER_ADDED("velocity", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkSphere", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiAvoidanceSolverBoundaryObstacle", 0)
	HK_PATCH_MEMBER_ADDED("start", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("end", TYPE_VEC_4, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiSimpleObstacleGenerator", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkaiObstacleGenerator")
	HK_PATCH_MEMBER_ADDED("localAabb", TYPE_STRUCT, "hkAabb", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkAabb", 0)
	HK_PATCH_DEPENDS("hkaiObstacleGenerator", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

#if defined(HK_FEATURE_PRODUCT_AI) && defined(HK_FEATURE_PRODUCT_PHYSICS_2012)
HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiRigidBodyObstacleGenerator", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkaiObstacleGenerator")
	HK_PATCH_MEMBER_ADDED_REAL("velocityThreshold", 3.000000f)
	HK_PATCH_MEMBER_ADDED("rigidBody", TYPE_OBJECT, "hkpRigidBody", 0)
	HK_PATCH_DEPENDS("hkpRigidBody", 0)
	HK_PATCH_DEPENDS("hkpEntity", 3)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkpWorldObject", 0)
	HK_PATCH_DEPENDS("hkaiObstacleGenerator", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()
#endif

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiObstacleGenerator", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("useSpheres", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("useBoundaries", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("clipBoundaries", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("transform", TYPE_VEC_16, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("spheres", TYPE_ARRAY_STRUCT, "hkaiAvoidanceSolverSphereObstacle", 0)
	HK_PATCH_MEMBER_ADDED("boundaries", TYPE_ARRAY_STRUCT, "hkaiAvoidanceSolverBoundaryObstacle", 0)
	HK_PATCH_MEMBER_ADDED("userData", TYPE_INT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkaiAvoidanceSolverBoundaryObstacle", 0)
	HK_PATCH_DEPENDS("hkaiAvoidanceSolverSphereObstacle", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiWorld", 29, "hkaiWorld", 30)
	HK_PATCH_MEMBER_ADDED("obstacleGenerators", TYPE_ARRAY_OBJECT, "hkaiObstacleGenerator", 0)
	HK_PATCH_DEPENDS("hkaiObstacleGenerator", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiWorldCharacterStepSerializableContext", 1, "hkaiWorldCharacterStepSerializableContext", 2)
	HK_PATCH_MEMBER_ADDED("obstacleGenerators", TYPE_ARRAY_OBJECT, "hkaiObstacleGenerator", 0)
	HK_PATCH_DEPENDS("hkaiObstacleGenerator", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiPointCloudSilhouetteGenerator", 0, "hkaiPointCloudSilhouetteGenerator", 1)
	HK_PATCH_MEMBER_ADDED("silhouetteSizes", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED_BYTE("silhouetteDetailLevel", 1)
	//HK_PATCH_FUNCTION(hkaiPointCloudSilhouetteGenerator_0_to_1)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiRigidBodySilhouetteGeneratorBase", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkaiPointCloudSilhouetteGenerator")
	HK_PATCH_MEMBER_ADDED_VEC_4("linearVelocityAndThreshold", 0.000000f,0.000000f,0.000000f,3.000000f)
	HK_PATCH_DEPENDS("hkaiSilhouetteGenerator", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkaiPointCloudSilhouetteGenerator", 1)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

#if defined(HK_FEATURE_PRODUCT_AI) && defined(HK_FEATURE_PRODUCT_PHYSICS_2012)
HK_PATCH_BEGIN("hkaiRigidBodySilhouetteGenerator", 0, "hkaiRigidBodySilhouetteGenerator", 1)
	HK_PATCH_PARENT_SET("hkaiSilhouetteGenerator", "hkaiRigidBodySilhouetteGeneratorBase")
	//HK_PATCH_FUNCTION(hkaiRigidBodySilhouetteGenerator_0_to_1)
	HK_PATCH_MEMBER_REMOVED("detailLevel", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("linearVelocityAndThreshold", TYPE_VEC_4, HK_NULL, 0)
HK_PATCH_END()
#endif

HK_PATCH_BEGIN("hkaiEdgeGeometryFace", 0, "hkaiEdgeGeometryFace", 1)
	HK_PATCH_MEMBER_ADDED("flags", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiDefaultAstarEdgeFilter", 1)
	HK_PATCH_PARENT_SET(HK_NULL, "hkaiAstarEdgeFilter")
	HK_PATCH_MEMBER_ADDED("edgeMaskLookupTable", TYPE_TUPLE_INT, HK_NULL, 32)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkaiAstarEdgeFilter", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiAstarEdgeFilter", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("type", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()


HK_PATCH_BEGIN("hkaiDefaultNavMeshCostModifier", 1, "hkaiDefaultNavMeshCostModifier", 2)
	HK_PATCH_MEMBER_REMOVED("edgeMaskLookupTable", TYPE_TUPLE_INT, HK_NULL, 32)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiLineOfSightUtilInputBase", 0, "hkaiLineOfSightUtilInputBase", 1)
	HK_PATCH_MEMBER_ADDED("edgeFilter", TYPE_OBJECT, "hkaiAstarEdgeFilter", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkaiAstarEdgeFilter", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	//HK_PATCH_FUNCTION(hkaiLineOfSightUtilInputBase_0_to_1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiCharacter", 27, "hkaiCharacter", 28)
	HK_PATCH_MEMBER_ADDED_POINTER("edgeFilter", "hkaiAstarEdgeFilter", 0)
	HK_PATCH_MEMBER_REMOVED("volumeCostModifier",TYPE_OBJECT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkaiAstarEdgeFilter", 0)
	//HK_PATCH_FUNCTION(hkaiCharacter_27_to_28)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshSimplificationUtilsExtraVertexSettings", 0, "hkaiNavMeshSimplificationUtilsExtraVertexSettings", 1)
	HK_PATCH_MEMBER_ADDED("userVertices", TYPE_ARRAY_VEC_4, HK_NULL, 0)
HK_PATCH_END()

// Rename
HK_PATCH_BEGIN("hkaiNavMeshCostModifier", 2, "hkaiAstarCostModifier", 3)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiDefaultNavMeshCostModifier", 2, "hkaiDefaultAstarCostModifier", 3)
	HK_PATCH_MEMBER_ADDED("costMultiplierLookupTable", TYPE_TUPLE_REAL, HK_NULL, 32)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiDefaultNavVolumeCostModifier", 1, HK_NULL, HK_CLASS_REMOVED)
	HK_PATCH_PARENT_SET("hkaiNavVolumeCostModifier", HK_NULL)
	HK_PATCH_MEMBER_REMOVED("cellMaskLookupTable", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("costMultiplierLookupTable", TYPE_TUPLE_REAL, HK_NULL, 32)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkaiNavVolumeCostModifier", 1)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavVolumeCostModifier", 1, HK_NULL, HK_CLASS_REMOVED)
	HK_PATCH_PARENT_SET("hkReferencedObject", HK_NULL)
	HK_PATCH_MEMBER_REMOVED("type", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiDefaultAstarEdgeFilter", 1, "hkaiDefaultAstarEdgeFilter", 2)
	HK_PATCH_MEMBER_ADDED("cellMaskLookupTable", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavVolumePathSearchParameters", 2, "hkaiNavVolumePathSearchParameters", 3)
	HK_PATCH_MEMBER_ADDED_BYTE("lineOfSightFlags", 1)
	HK_PATCH_MEMBER_REMOVED("checkForLineOfSight", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiSplitGenerationUtilsSettings", 0)
	HK_PATCH_MEMBER_ADDED_BYTE("simplificationOptions", 1)
	HK_PATCH_MEMBER_ADDED_BYTE("generateClusterGraphs", 0)
	HK_PATCH_MEMBER_ADDED_INT("desiredFacesPerCluster", 20)
	HK_PATCH_MEMBER_ADDED_REAL("borderPreserveShrinkSize", 0.100000f)
	HK_PATCH_MEMBER_ADDED_INT("numX", 1)
	HK_PATCH_MEMBER_ADDED_INT("numY", 1)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiSplitGenerationSnapshot", 0)
	HK_PATCH_MEMBER_ADDED("generationSnapshot", TYPE_STRUCT, "hkaiNavMeshGenerationSnapshot", 0)
	HK_PATCH_MEMBER_ADDED("splitSettings", TYPE_STRUCT, "hkaiSplitGenerationUtilsSettings", 0)
	HK_PATCH_DEPENDS("hkaiNavMeshGenerationSnapshot", 1)
	HK_PATCH_DEPENDS("hkaiSplitGenerationUtilsSettings", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshGenerationSettingsOverrideSettings", 2, "hkaiNavMeshGenerationSettingsOverrideSettings", 3)
	HK_PATCH_MEMBER_ADDED_BYTE("characterWidthUsage", 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshGenerationSettingsRegionPruningSettings", 0, "hkaiNavMeshGenerationSettingsRegionPruningSettings", 1)
	HK_PATCH_MEMBER_ADDED_BYTE("preserveVerticalBorderRegions", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshPathSearchParameters", 8, "hkaiNavMeshPathSearchParameters", 9)
	HK_PATCH_MEMBER_ADDED_BYTE("useGrandparentDistanceCalculation", 1)
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
