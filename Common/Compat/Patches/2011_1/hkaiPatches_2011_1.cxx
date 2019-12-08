/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// AI specific product patches applied to release 2011_1.
// This file is #included by hkaiPatches_2011_1.cpp

HK_PATCH_BEGIN("hkaiDefaultLocalSteeringPathFollowingProperties", 2, "hkaiPathFollowingProperties", 3 )
	HK_PATCH_MEMBER_ADDED_REAL("repathDistance", 2.000000f)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiDefaultLocalSteering", 0, HK_NULL, HK_CLASS_REMOVED)
	HK_PATCH_PARENT_SET("hkaiLocalSteering", HK_NULL)
	HK_PATCH_MEMBER_REMOVED("pathFollowingProperties", TYPE_STRUCT, "hkaiPathFollowingProperties", 0)
	HK_PATCH_MEMBER_REMOVED("avoidanceProperties", TYPE_OBJECT, "hkaiAvoidanceSolverAvoidanceProperties", 0)
	HK_PATCH_DEPENDS("hkaiLocalSteering", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkaiPathFollowingProperties", 3)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkaiAvoidanceSolverAvoidanceProperties", 6)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiCharacter", 18, "hkaiCharacter", 19)
	HK_PATCH_MEMBER_REMOVED("localSteering", TYPE_OBJECT, "hkaiLocalSteering", 0)
	HK_PATCH_DEPENDS("hkaiLocalSteering", 0)
	//HK_PATCH_FUNCTION(hkaiCharacter_18_to_19)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiLocalSteering", 0, HK_NULL, HK_CLASS_REMOVED)
	HK_PATCH_PARENT_SET("hkReferencedObject", HK_NULL)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiLocalSteeringInput", 0)
	HK_PATCH_MEMBER_ADDED("desiredVelocity", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("desiredFutureDir", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("distToLocalGoal", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("timeToLocalGoal", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("isLocalGoalLast", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiCharacter", 19, "hkaiCharacter", 20)
	HK_PATCH_MEMBER_REMOVED("desiredVelocity", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("desiredFutureDir", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("distToLocalGoal", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("timeToLocalGoal", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("isLocalGoalLast", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiLocalSteeringInput", 0, "hkaiLocalSteeringInput", 1)
	HK_PATCH_MEMBER_ADDED("applyKinematicConstraints", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("applyAvoidanceSteering", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshCutter", 9, "hkaiNavMeshCutter", 10)
	HK_PATCH_MEMBER_ADDED_BYTE("clearanceResetMethod", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiCharacter", 20, "hkaiCharacter", 21)
	HK_PATCH_MEMBER_ADDED_BYTE("avoidanceEnabledMask", 7)
	HK_PATCH_FUNCTION(hkaiCharacter_20_to_21)
	HK_PATCH_MEMBER_REMOVED("avoidanceEnabled", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiWorld", 23, "hkaiWorld", 24)
	HK_PATCH_MEMBER_REMOVED("meshInstance", TYPE_STRUCT, "hkaiNavMeshInstance", 0)
	HK_PATCH_DEPENDS("hkaiNavMeshInstance", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiPathFollowingProperties", 3, "hkaiPathFollowingProperties", 4)
	HK_PATCH_MEMBER_REMOVED("slowdownToEndDist", TYPE_REAL, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiAstarOutputParameters", 0)
	HK_PATCH_MEMBER_ADDED("numIterations", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("goalIndex", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("status", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiPathfindingUtilFindPathOutput", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("visitedEdges", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("pathOut", TYPE_ARRAY_STRUCT, "hkaiPathPathPoint", 0)
	HK_PATCH_MEMBER_ADDED("outputParameters", TYPE_STRUCT, "hkaiAstarOutputParameters", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkaiAstarOutputParameters", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkaiPathPathPoint", 1)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiVolumePathfindingUtilFindPathOutput", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("visitedCells", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("pathOut", TYPE_ARRAY_STRUCT, "hkaiPathPathPoint", 0)
	HK_PATCH_MEMBER_ADDED("outputParameters", TYPE_STRUCT, "hkaiAstarOutputParameters", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkaiAstarOutputParameters", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkaiPathPathPoint", 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiVolumePathfindingUtilFindPathInput", 5, "hkaiVolumePathfindingUtilFindPathInput", 6)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiPathfindingUtilFindPathInput", 8, "hkaiPathfindingUtilFindPathInput", 9)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiNavVolumePathRequestInfo", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("input", TYPE_OBJECT, "hkaiVolumePathfindingUtilFindPathInput", 0)
	HK_PATCH_MEMBER_ADDED("output", TYPE_OBJECT, "hkaiVolumePathfindingUtilFindPathOutput", 0)
	HK_PATCH_MEMBER_ADDED("priority", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("markedForDeletion", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkaiVolumePathfindingUtilFindPathOutput", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkaiVolumePathfindingUtilFindPathInput", 6)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiNavMeshPathRequestInfo", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("input", TYPE_OBJECT, "hkaiPathfindingUtilFindPathInput", 0)
	HK_PATCH_MEMBER_ADDED("output", TYPE_OBJECT, "hkaiPathfindingUtilFindPathOutput", 0)
	HK_PATCH_MEMBER_ADDED("priority", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("markedForDeletion", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkaiPathfindingUtilFindPathInput", 9)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkaiPathfindingUtilFindPathOutput", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshSimplificationUtilsSettings", 9, "hkaiNavMeshSimplificationUtilsSettings", 10)
	HK_PATCH_MEMBER_ADDED_BYTE("mergeLongestEdgesFirst", 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiPath", 9, "hkaiPath", 10)
	HK_PATCH_MEMBER_ADDED_BYTE("referenceFrame", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiPathPathPoint", 1, "hkaiPathPathPoint", 2)
	HK_PATCH_MEMBER_ADDED("sectionId", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiReferenceFrame", 0)
	HK_PATCH_MEMBER_ADDED("transform", TYPE_VEC_16, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("linearVelocity", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("angularVelocity", TYPE_VEC_4, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshInstance", 0, "hkaiNavMeshInstance", 1)
	HK_PATCH_MEMBER_ADDED("referenceFrame", TYPE_STRUCT, "hkaiReferenceFrame", 0)
	HK_PATCH_DEPENDS("hkaiReferenceFrame", 0)
	HK_PATCH_FUNCTION(hkaiNavMeshInstance_0_to_1)
	HK_PATCH_MEMBER_REMOVED("transform", TYPE_VEC_16, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiLocalSteeringInput", 1, "hkaiLocalSteeringInput", 2)
	HK_PATCH_MEMBER_ADDED("currentPosition", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("currentForward", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("currentVelocity", TYPE_VEC_4, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiWorld", 24, "hkaiWorld", 25)
	HK_PATCH_MEMBER_ADDED_BYTE("forceSilhouetteUpdates", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshGenerationSettingsLocalSettings", 1, "hkaiNavMeshGenerationSettingsOverrideSettings", 2)
	HK_PATCH_MEMBER_ADDED("material", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshGenerationSettings", 18, "hkaiNavMeshGenerationSettings", 19)
	HK_PATCH_FUNCTION(hkaiNavMeshGenerationSettings_18_to_19)
	HK_PATCH_MEMBER_RENAMED("localSettings", "overrideSettings")
	HK_PATCH_MEMBER_REMOVED("materialSettingsMap", TYPE_ARRAY_STRUCT, "hkaiNavMeshGenerationSettingsMaterialSimplificationSettingsPair", 0)
	HK_PATCH_DEPENDS("hkaiNavMeshGenerationSettingsMaterialSimplificationSettingsPair", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshGenerationSettingsMaterialSimplificationSettingsPair", 0, HK_NULL, HK_CLASS_REMOVED)
	HK_PATCH_MEMBER_REMOVED("materialIndex", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("simplificationSettings", TYPE_STRUCT, "hkaiNavMeshSimplificationUtilsSettings", 0)
	HK_PATCH_DEPENDS("hkaiNavMeshSimplificationUtilsSettings", 10)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiNavVolumeGenerationSettingsChunkSettings", 0)
	HK_PATCH_MEMBER_ADDED_INT("maxChunkSizeX", 256)
	HK_PATCH_MEMBER_ADDED_INT("maxChunkSizeY", 256)
	HK_PATCH_MEMBER_ADDED_INT("maxChunkSizeZ", 256)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavVolumeGenerationSettings", 5, "hkaiNavVolumeGenerationSettings", 6)
	HK_PATCH_MEMBER_ADDED("chunkSettings", TYPE_STRUCT, "hkaiNavVolumeGenerationSettingsChunkSettings", 0)
	HK_PATCH_DEPENDS("hkaiNavVolumeGenerationSettingsChunkSettings", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshPathSearchParameters", 2, "hkaiNavMeshPathSearchParameters", 3)
	HK_PATCH_MEMBER_ADDED_BOOL("validateInputs", true)
	HK_PATCH_MEMBER_RENAMED("checkForDirectPath", "checkForLineOfSight")
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavVolumePathSearchParameters", 0, "hkaiNavVolumePathSearchParameters", 1)
	HK_PATCH_MEMBER_RENAMED("checkForDirectPath", "checkForLineOfSight")
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshGenerationSettings", 19, "hkaiNavMeshGenerationSettings", 20)
	HK_PATCH_MEMBER_ADDED("boundsAabb", TYPE_STRUCT, "hkAabb", 0)
	HK_PATCH_MEMBER_ADDED_INT("maxNumEdgesPerFace", 255)
	HK_PATCH_DEPENDS("hkAabb", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiWorldCharacterStepCallbackContext", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	 HK_PATCH_MEMBER_ADDED("callbackType", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("characters", TYPE_ARRAY_OBJECT, "hkaiCharacter", 0)
	HK_PATCH_MEMBER_ADDED("localSteeringInputs", TYPE_ARRAY_STRUCT, "hkaiLocalSteeringInput", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkaiLocalSteeringInput", 2)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkaiCharacter", 21)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshInstance", 1, "hkaiNavMeshInstance", 2)
	HK_PATCH_MEMBER_ADDED("cuttingInfo", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_FUNCTION(hkaiNavMeshInstance_1_to_2)
	HK_PATCH_DEPENDS("hkaiNavMeshEdge", 5)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshEdge", 5, "hkaiNavMeshEdge", 6)
	HK_PATCH_MEMBER_REMOVED("cutInfo", TYPE_BYTE, HK_NULL, 0)
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
