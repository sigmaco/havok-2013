/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Cloth specific product patches applied to release 710.
// This file is #included by hclPatches_710.cpp

HK_PATCH_BEGIN("hclSimClothData", 0, "hclSimClothData", 1)
	HK_PATCH_MEMBER_ADDED("staticCollisionMasks", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("maxCollisionPairs", TYPE_INT, HK_NULL, 0)
	HK_PATCH_FUNCTION(hclSimClothData_0_to_1)
	HK_PATCH_DEPENDS("hclSimClothDataCollisionPair", 0)
	HK_PATCH_MEMBER_REMOVED("enableMidPhase", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("staticCollisionPairs", TYPE_ARRAY_STRUCT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclCapsuleShape", 0, "hclCapsuleShape", 1)
	HK_PATCH_MEMBER_ADDED("capLenSqrdInv", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_FUNCTION(hclCapsuleShape_0_to_1)
	HK_PATCH_MEMBER_REMOVED("capLenSqrd", TYPE_REAL, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hclTaperedCapsuleShape", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hclShape")
	HK_PATCH_MEMBER_ADDED("small", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("big", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("smallRadius", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("bigRadius", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("coneApex", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("coneAxis", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("l", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("d", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("dVec", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("cosTheta", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("sinTheta", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("tanTheta", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("tanThetaSqr", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("tanThetaVecNeg", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_DEPENDS("hclShape", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclSimClothDataCollisionPair", 0, HK_NULL, HK_CLASS_REMOVED)
        HK_PATCH_MEMBER_REMOVED("particleIndex", TYPE_INT, HK_NULL, 0)
        HK_PATCH_MEMBER_REMOVED("collidableIndex", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclCollidable", 0, "hclCollidable", 1)
        HK_PATCH_MEMBER_REMOVED("stepMovement", TYPE_REAL, HK_NULL, 0)
        HK_PATCH_MEMBER_REMOVED("radius", TYPE_REAL, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclSimClothSetupObject", 0, "hclSimClothSetupObject", 1)
        HK_PATCH_MEMBER_REMOVED("enableMidPhase", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclSimulateSetupObject", 0, "hclSimulateSetupObject", 1)
	HK_PATCH_MEMBER_ADDED("collideAndSolve", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclSimulateOperator", 0, "hclSimulateOperator", 1)
	HK_PATCH_MEMBER_ADDED("collideAndSolve", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hclSimClothDataCollidableTransformMap", 0)
    HK_PATCH_MEMBER_ADDED_INT("transformSetIndex", -1)
    HK_PATCH_MEMBER_ADDED("transformIndices", TYPE_ARRAY_INT, HK_NULL, 0)
    HK_PATCH_MEMBER_ADDED("offsets", TYPE_ARRAY_VEC_16, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclSimClothSetupObject", 1, "hclSimClothSetupObject", 2)
    HK_PATCH_MEMBER_ADDED("collidableTransformSet", TYPE_OBJECT, "hclTransformSetSetupObject", 0)
    HK_PATCH_DEPENDS("hclTransformSetSetupObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclSimClothData", 1, "hclSimClothData", 2)
    HK_PATCH_MEMBER_ADDED("collidableTransformMap", TYPE_STRUCT, "hclSimClothDataCollidableTransformMap", 0)
    HK_PATCH_DEPENDS("hclSimClothDataCollidableTransformMap", 0)
    HK_PATCH_FUNCTION(hclSimClothData_1_to_2)
HK_PATCH_END()

HK_PATCH_BEGIN("hclTaperedCapsuleShape", 0, "hclTaperedCapsuleShape", 1)
	HK_PATCH_MEMBER_ADDED("lVec", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("vPerm", TYPE_VEC_4, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclSimClothSetupObjectPerInstanceCollidable", 0, "hclSimClothSetupObjectPerInstanceCollidable", 1)
   HK_PATCH_MEMBER_ADDED("drivingBoneName", TYPE_CSTRING, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hclBendStiffnessConstraintSet", 0)
        HK_PATCH_PARENT_SET(HK_NULL, "hclConstraintSet")
        HK_PATCH_MEMBER_ADDED("links", TYPE_ARRAY_STRUCT, "hclBendStiffnessConstraintSetLink", 0)
        HK_PATCH_DEPENDS("hkBaseObject", 0)
        HK_PATCH_DEPENDS("hclConstraintSet", 0)
        HK_PATCH_DEPENDS("hclBendStiffnessConstraintSetLink", 0)
        HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hclBendStiffnessSetupObject", 0)
        HK_PATCH_PARENT_SET(HK_NULL, "hclConstraintSetSetupObject")
        HK_PATCH_MEMBER_ADDED("name", TYPE_CSTRING, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("simulationMesh", TYPE_OBJECT, "hclSimulationSetupMesh", 0)
        HK_PATCH_MEMBER_ADDED("vertexSelection", TYPE_STRUCT, "hclVertexSelectionInput", 0)
        HK_PATCH_MEMBER_ADDED("bendStiffness", TYPE_STRUCT, "hclVertexFloatInput", 0)
        HK_PATCH_DEPENDS("hclSimulationSetupMesh", 0)
        HK_PATCH_DEPENDS("hkBaseObject", 0)
        HK_PATCH_DEPENDS("hclVertexSelectionInput", 0)
        HK_PATCH_DEPENDS("hclVertexFloatInput", 0)
        HK_PATCH_DEPENDS("hclConstraintSetSetupObject", 0)
        HK_PATCH_DEPENDS("hclSetupMesh", 0)
        HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hclBendStiffnessConstraintSetLink", 0)
        HK_PATCH_MEMBER_ADDED("particleA", TYPE_INT, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("particleB", TYPE_INT, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("particleC", TYPE_INT, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("particleD", TYPE_INT, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("weightA", TYPE_REAL, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("weightB", TYPE_REAL, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("weightC", TYPE_REAL, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("weightD", TYPE_REAL, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("bendStiffness", TYPE_REAL, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclBendStiffnessConstraintSet", 0, "hclBendStiffnessConstraintSet", 1)
		HK_PATCH_MEMBER_ADDED("useRestPoseConfig", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclBendStiffnessSetupObject", 0, "hclBendStiffnessSetupObject", 1)
		HK_PATCH_MEMBER_ADDED("useRestPoseConfig", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclBendStiffnessConstraintSetLink", 0, "hclBendStiffnessConstraintSetLink", 1)
		HK_PATCH_MEMBER_ADDED("restCurvature", TYPE_REAL, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclUpdateAllVertexFramesOperator", 1, "hclUpdateAllVertexFramesOperator", 2)
	HK_PATCH_MEMBER_ADDED("triangleFlips", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_FUNCTION(hclUpdateAllVertexFramesOperator_1_to_2)
	HK_PATCH_MEMBER_REMOVED("flipNormals", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclUpdateSomeVertexFramesOperator", 1, "hclUpdateSomeVertexFramesOperator", 2)
	HK_PATCH_MEMBER_ADDED("triangleFlips", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_FUNCTION(hclUpdateSomeVertexFramesOperator_1_to_2)
	HK_PATCH_MEMBER_REMOVED("flipNormals", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclSimClothData", 2, "hclSimClothData", 3)
	HK_PATCH_MEMBER_ADDED("triangleFlips", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_FUNCTION(hclSimClothData_2_to_3)
	HK_PATCH_DEPENDS("hclSimClothDataSimulationInfo", 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hclSimClothDataSimulationInfo", 1, "hclSimClothDataSimulationInfo", 2)
	HK_PATCH_MEMBER_REMOVED("flipNormals", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hclStandardLinkConstraintSetMx", 0)
        HK_PATCH_PARENT_SET(HK_NULL, "hclConstraintSet")
        HK_PATCH_MEMBER_ADDED("batches", TYPE_ARRAY_STRUCT, "hclStandardLinkConstraintSetMxBatch", 0)
        HK_PATCH_MEMBER_ADDED("singles", TYPE_ARRAY_STRUCT, "hclStandardLinkConstraintSetMxSingle", 0)
        HK_PATCH_DEPENDS("hclStandardLinkConstraintSetMxBatch", 0)
        HK_PATCH_DEPENDS("hclStandardLinkConstraintSetMxSingle", 0)
        HK_PATCH_DEPENDS("hkBaseObject", 0)
        HK_PATCH_DEPENDS("hclConstraintSet", 0)
        HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hclStandardLinkConstraintSetMxBatch", 0)
        HK_PATCH_MEMBER_ADDED("restLengths", TYPE_TUPLE_REAL, HK_NULL, 16)
        HK_PATCH_MEMBER_ADDED("stiffnessesA", TYPE_TUPLE_REAL, HK_NULL, 16)
        HK_PATCH_MEMBER_ADDED("stiffnessesB", TYPE_TUPLE_REAL, HK_NULL, 16)
        HK_PATCH_MEMBER_ADDED("particlesA", TYPE_TUPLE_INT, HK_NULL, 16)
        HK_PATCH_MEMBER_ADDED("particlesB", TYPE_TUPLE_INT, HK_NULL, 16)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hclStandardLinkConstraintSetMxSingle", 0)
        HK_PATCH_MEMBER_ADDED("restLength", TYPE_REAL, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("stiffnessA", TYPE_REAL, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("stiffnessB", TYPE_REAL, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("particleA", TYPE_INT, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("particleB", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hclStretchLinkConstraintSetMxBatch", 0)
        HK_PATCH_MEMBER_ADDED("restLengths", TYPE_TUPLE_REAL, HK_NULL, 16)
        HK_PATCH_MEMBER_ADDED("stiffnesses", TYPE_TUPLE_REAL, HK_NULL, 16)
        HK_PATCH_MEMBER_ADDED("particlesA", TYPE_TUPLE_INT, HK_NULL, 16)
        HK_PATCH_MEMBER_ADDED("particlesB", TYPE_TUPLE_INT, HK_NULL, 16)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hclStretchLinkConstraintSetMxSingle", 0)
        HK_PATCH_MEMBER_ADDED("restLength", TYPE_REAL, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("stiffness", TYPE_REAL, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("particleA", TYPE_INT, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("particleB", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hclStretchLinkConstraintSetMx", 0)
        HK_PATCH_PARENT_SET(HK_NULL, "hclConstraintSet")
        HK_PATCH_MEMBER_ADDED("batches", TYPE_ARRAY_STRUCT, "hclStretchLinkConstraintSetMxBatch", 0)
        HK_PATCH_MEMBER_ADDED("singles", TYPE_ARRAY_STRUCT, "hclStretchLinkConstraintSetMxSingle", 0)
        HK_PATCH_DEPENDS("hkBaseObject", 0)
        HK_PATCH_DEPENDS("hclConstraintSet", 0)
        HK_PATCH_DEPENDS("hclStretchLinkConstraintSetMxBatch", 0)
        HK_PATCH_DEPENDS("hclStretchLinkConstraintSetMxSingle", 0)
        HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hclBendLinkConstraintSetMx", 0)
        HK_PATCH_PARENT_SET(HK_NULL, "hclConstraintSet")
        HK_PATCH_MEMBER_ADDED("batches", TYPE_ARRAY_STRUCT, "hclBendLinkConstraintSetMxBatch", 0)
        HK_PATCH_MEMBER_ADDED("singles", TYPE_ARRAY_STRUCT, "hclBendLinkConstraintSetMxSingle", 0)
        HK_PATCH_DEPENDS("hkBaseObject", 0)
        HK_PATCH_DEPENDS("hclConstraintSet", 0)
        HK_PATCH_DEPENDS("hclBendLinkConstraintSetMxSingle", 0)
        HK_PATCH_DEPENDS("hkReferencedObject", 0)
        HK_PATCH_DEPENDS("hclBendLinkConstraintSetMxBatch", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hclBendLinkConstraintSetMxBatch", 0)
        HK_PATCH_MEMBER_ADDED("bendMinLengths", TYPE_TUPLE_REAL, HK_NULL, 16)
        HK_PATCH_MEMBER_ADDED("stretchMaxLengths", TYPE_TUPLE_REAL, HK_NULL, 16)
        HK_PATCH_MEMBER_ADDED("stretchStiffnesses", TYPE_TUPLE_REAL, HK_NULL, 16)
        HK_PATCH_MEMBER_ADDED("bendStiffnesses", TYPE_TUPLE_REAL, HK_NULL, 16)
        HK_PATCH_MEMBER_ADDED("invMassesA", TYPE_TUPLE_REAL, HK_NULL, 16)
        HK_PATCH_MEMBER_ADDED("invMassesB", TYPE_TUPLE_REAL, HK_NULL, 16)
        HK_PATCH_MEMBER_ADDED("particlesA", TYPE_TUPLE_INT, HK_NULL, 16)
        HK_PATCH_MEMBER_ADDED("particlesB", TYPE_TUPLE_INT, HK_NULL, 16)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hclBendLinkConstraintSetMxSingle", 0)
        HK_PATCH_MEMBER_ADDED("bendMinLength", TYPE_REAL, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("stretchMaxLength", TYPE_REAL, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("stretchStiffness", TYPE_REAL, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("bendStiffness", TYPE_REAL, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("invMassA", TYPE_REAL, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("invMassB", TYPE_REAL, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("particleA", TYPE_INT, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("particleB", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclVolumeConstraintSetupObject", 0, "hclVolumeConstraintSetupObject", 1)
	HK_PATCH_MEMBER_ADDED("useDeprecatedMethod", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_FUNCTION(hclVolumeConstraintSetupObject_0_to_1)
HK_PATCH_END()

HK_PATCH_BEGIN("hclVolumeConstraint", 0, "hclVolumeConstraint", 1)
	HK_PATCH_MEMBER_ADDED("useDeprecatedMethod", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_FUNCTION(hclVolumeConstraint_0_to_1)
HK_PATCH_END()

HK_PATCH_BEGIN("hclTaperedCapsuleShape", 1, "hclTaperedCapsuleShape", 2)
	HK_PATCH_MEMBER_REMOVED("vPerm", TYPE_VEC_4, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclSimClothData", 3, "hclSimClothData", 4)
	HK_PATCH_MEMBER_ADDED("maxParticleRadius", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_FUNCTION(hclSimClothData_3_to_4)
HK_PATCH_END()

HK_PATCH_BEGIN("hclClothData", 0, "hclClothData", 1)
	HK_PATCH_MEMBER_ADDED("targetPlatform", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclLocalRangeConstraintSet", 0, "hclLocalRangeConstraintSet", 1)
	HK_PATCH_MEMBER_ADDED("applyNormalComponent", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_FUNCTION(hclLocalRangeConstraintSet_0_to_1)
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
