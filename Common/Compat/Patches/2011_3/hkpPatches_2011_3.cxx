/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Physics specific product patches applied to release 2011_3.
// This file is #included by hkpPatches_2011_3.cpp
HK_PATCH_BEGIN("hkpSerializedAgentNnEntry", 0, "hkpSerializedAgentNnEntry", 1)
	HK_PATCH_MEMBER_REMOVED("nnEntryData", TYPE_TUPLE_BYTE, HK_NULL, 160)
	HK_PATCH_MEMBER_ADDED("nnEntryData", TYPE_TUPLE_BYTE, HK_NULL, 192)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpBvCompressedMeshShape", 1, "hkpBvCompressedMeshShape", 2)
	HK_PATCH_MEMBER_ADDED("userStringPalette", TYPE_ARRAY_CSTRING, HK_NULL, 0)
	HK_PATCH_FUNCTION(hkpBvCompressedMeshShape_1_to_2)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkp3dAngConstraintAtom", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkpConstraintAtom")
	HK_PATCH_MEMBER_ADDED("padding", TYPE_TUPLE_BYTE, HK_NULL, 14)
	HK_PATCH_DEPENDS("hkpConstraintAtom", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpFixedConstraintDataAtoms", 0)
	HK_PATCH_MEMBER_ADDED("transforms", TYPE_STRUCT, "hkpSetLocalTransformsConstraintAtom", 0)
	HK_PATCH_MEMBER_ADDED("setupStabilization", TYPE_STRUCT, "hkpSetupStabilizationAtom", 0)
	HK_PATCH_MEMBER_ADDED("ballSocket", TYPE_STRUCT, "hkpBallSocketConstraintAtom", 0)
	HK_PATCH_MEMBER_ADDED("ang", TYPE_STRUCT, "hkp3dAngConstraintAtom", 0)
	HK_PATCH_DEPENDS("hkpSetupStabilizationAtom", 1)
	HK_PATCH_DEPENDS("hkp3dAngConstraintAtom", 0)
	HK_PATCH_DEPENDS("hkpSetLocalTransformsConstraintAtom", 0)
	HK_PATCH_DEPENDS("hkpConstraintAtom", 0)
	HK_PATCH_DEPENDS("hkpBallSocketConstraintAtom", 3)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpFixedConstraintData", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkpConstraintData")
	HK_PATCH_MEMBER_ADDED("atoms", TYPE_STRUCT, "hkpFixedConstraintDataAtoms", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkpConstraintData", 0)
	HK_PATCH_DEPENDS("hkpFixedConstraintDataAtoms", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpBallSocketChainData", 0, "hkpBallSocketChainData", 1)
	HK_PATCH_MEMBER_ADDED("useStabilizedCode", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpConstraintChainInstance", 0, "hkpConstraintChainInstance", 1)
	HK_PATCH_MEMBER_ADDED("chainConnectedness", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkp3dAngConstraintAtom", 0, "hkp3dAngConstraintAtom", 1)
	HK_PATCH_MEMBER_REMOVED("padding", TYPE_TUPLE_BYTE, HK_NULL, 14)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpModifierConstraintAtom", 0, "hkpModifierConstraintAtom", 1)
	HK_PATCH_MEMBER_REMOVED("pad", TYPE_TUPLE_INT, HK_NULL, 2)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpBallSocketConstraintAtom", 3, "hkpBallSocketConstraintAtom", 4)
	HK_PATCH_MEMBER_RENAMED("maxImpulse", "breachImpulse")
	HK_PATCH_MEMBER_ADDED_BYTE("enableLinearImpulseLimit", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpSetupStabilizationAtom", 1, "hkpSetupStabilizationAtom", 2)
	HK_PATCH_MEMBER_REMOVED("padding", TYPE_TUPLE_BYTE, HK_NULL, 8)
	HK_PATCH_MEMBER_ADDED_REAL("maxLinImpulse", 340282001837565600000000000000000000000.000000f)
	HK_PATCH_MEMBER_ADDED_REAL("maxAngImpulse", 340282001837565600000000000000000000000.000000f)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpDeformableLinConstraintAtom", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkpConstraintAtom")
	HK_PATCH_MEMBER_ADDED_VEC_4("offset", 0.000000f,0.000000f,0.000000f,0.000000f)
	HK_PATCH_MEMBER_ADDED("yieldStrength", TYPE_STRUCT, "hkSymmetricMatrix3", 0)
	HK_PATCH_MEMBER_ADDED("ultimateStrength", TYPE_STRUCT, "hkSymmetricMatrix3", 0)
	HK_PATCH_DEPENDS("hkpConstraintAtom", 0)
	HK_PATCH_DEPENDS("hkSymmetricMatrix3", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpDeformableAngConstraintAtom", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkpConstraintAtom")
	HK_PATCH_MEMBER_ADDED_VEC_4("offset", 0.000000f,0.000000f,0.000000f,1.000000f)
	HK_PATCH_MEMBER_ADDED("yieldStrength", TYPE_STRUCT, "hkSymmetricMatrix3", 0)
	HK_PATCH_MEMBER_ADDED("ultimateStrength", TYPE_STRUCT, "hkSymmetricMatrix3", 0)
	HK_PATCH_DEPENDS("hkpConstraintAtom", 0)
	HK_PATCH_DEPENDS("hkSymmetricMatrix3", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpDeformableFixedConstraintDataAtoms", 0)
	HK_PATCH_MEMBER_ADDED("transforms", TYPE_STRUCT, "hkpSetLocalTransformsConstraintAtom", 0)
	HK_PATCH_MEMBER_ADDED("lin", TYPE_STRUCT, "hkpDeformableLinConstraintAtom", 0)
	HK_PATCH_MEMBER_ADDED("ang", TYPE_STRUCT, "hkpDeformableAngConstraintAtom", 0)
	HK_PATCH_DEPENDS("hkpDeformableAngConstraintAtom", 0)
	HK_PATCH_DEPENDS("hkpDeformableLinConstraintAtom", 0)
	HK_PATCH_DEPENDS("hkpSetLocalTransformsConstraintAtom", 0)
	HK_PATCH_DEPENDS("hkpConstraintAtom", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpDeformableFixedConstraintData", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkpConstraintData")
	HK_PATCH_MEMBER_ADDED("atoms", TYPE_STRUCT, "hkpDeformableFixedConstraintDataAtoms", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkpConstraintData", 0)
	HK_PATCH_DEPENDS("hkpDeformableFixedConstraintDataAtoms", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpStiffSpringConstraintAtom", 0, "hkpStiffSpringConstraintAtom", 1)
	HK_PATCH_MEMBER_ADDED("maxLength", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_FUNCTION(hkpStiffSpringConstraintAtom_0_to_1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpStiffSpringConstraintDataAtoms", 0, "hkpStiffSpringConstraintDataAtoms", 1)
	HK_PATCH_MEMBER_ADDED("setupStabilization", TYPE_STRUCT, "hkpSetupStabilizationAtom", 0)
	HK_PATCH_DEPENDS("hkpSetupStabilizationAtom", 2)
	HK_PATCH_DEPENDS("hkpConstraintAtom", 0)
	HK_PATCH_FUNCTION(hkpStiffSpringConstraintDataAtoms_0_to_1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpAngMotorConstraintAtom", 0, "hkpAngMotorConstraintAtom", 1)
	HK_PATCH_MEMBER_REMOVED("initializedOffset", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("previousTargetAngleOffset", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("correspondingAngLimitSolverResultOffset", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpRagdollMotorConstraintAtom", 0, "hkpRagdollMotorConstraintAtom", 1)
	HK_PATCH_MEMBER_REMOVED("initializedOffset", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("previousTargetAnglesOffset", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpLinMotorConstraintAtom", 0, "hkpLinMotorConstraintAtom", 1)
	HK_PATCH_MEMBER_REMOVED("initializedOffset", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("previousTargetPositionOffset", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpWorldCinfo", 17, "hkpWorldCinfo", 18)
	HK_PATCH_MEMBER_REMOVED("BETA_useCompoundSpuElf", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED_BYTE("useCompoundSpuElf", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpTriSampledHeightFieldBvTreeShape", 0, "hkpTriSampledHeightFieldBvTreeShape", 1)
	HK_PATCH_MEMBER_REMOVED("padding", TYPE_TUPLE_BYTE, HK_NULL, 12)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpCollidableBoundingVolumeData", 0, "hkpCollidableBoundingVolumeData", 1)
	HK_PATCH_MEMBER_REMOVED("padding", TYPE_BYTE, HK_NULL, 0)
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
