/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Physics specific product patches applied to release 2010_1.
// This file is #included by hkpPatches_2010_1.cpp

HK_PATCH_BEGIN("hkpWorldCinfo", 8, "hkpWorldCinfo", 9)
	HK_PATCH_MEMBER_ADDED_BYTE("useHybridBroadphase", 0)
	HK_PATCH_MEMBER_REMOVED("maxSectorsPerCollideTask", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("maxEntriesPerToiCollideTask", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED_BOOL("useSplitCollisionPipelineOnCpu", false)
	HK_PATCH_MEMBER_ADDED_BOOL("useSplitCollisionPipelineOnSpu", false)
	HK_PATCH_MEMBER_ADDED_INT("maxSectorsPerMidphaseCollideTask", 2)
	HK_PATCH_MEMBER_ADDED_INT("maxSectorsPerNarrowphaseCollideTask", 4)
	HK_PATCH_MEMBER_ADDED_BOOL("useSplitCollisionPipelineForTois", false)
	HK_PATCH_MEMBER_ADDED_INT("maxEntriesPerToiMidphaseCollideTask", -1)
	HK_PATCH_MEMBER_ADDED_INT("maxEntriesPerToiNarrowphaseCollideTask", -1)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpShapeModifier", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpTriggerVolume", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("overlappingBodies", TYPE_ARRAY_OBJECT, "hkpRigidBody", 0)
	HK_PATCH_MEMBER_ADDED("eventQueue", TYPE_ARRAY_STRUCT, "hkpTriggerVolumeEventInfo", 0)
	HK_PATCH_MEMBER_ADDED("triggerBody", TYPE_OBJECT, "hkpRigidBody", 0)
	HK_PATCH_MEMBER_ADDED("sequenceNumber", TYPE_INT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkpRigidBody", 0)
	HK_PATCH_DEPENDS("hkpEntity", 3)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkpWorldObject", 0)
	HK_PATCH_DEPENDS("hkpTriggerVolumeEventInfo", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpTriggerVolumeEventInfo", 0)
	HK_PATCH_MEMBER_ADDED("sortValue", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("body", TYPE_OBJECT, "hkpRigidBody", 0)
	HK_PATCH_MEMBER_ADDED("operation", TYPE_INT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkpRigidBody", 0)
	HK_PATCH_DEPENDS("hkpEntity", 3)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkpWorldObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpSetupStabilizationAtom", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkpConstraintAtom")
	HK_PATCH_MEMBER_ADDED_BYTE("enabled", 1)
	HK_PATCH_MEMBER_ADDED_REAL("maxAngle", 18446726481523507000.000000f)
	HK_PATCH_MEMBER_ADDED("padding", TYPE_TUPLE_BYTE, HK_NULL, 8)
	HK_PATCH_DEPENDS("hkpConstraintAtom", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpHingeConstraintDataAtoms", 0, "hkpHingeConstraintDataAtoms", 1)
	HK_PATCH_MEMBER_ADDED("setupStabilization", TYPE_STRUCT, "hkpSetupStabilizationAtom", 0)
	HK_PATCH_DEPENDS("hkpSetupStabilizationAtom", 0)
	HK_PATCH_DEPENDS("hkpConstraintAtom", 0)
	HK_PATCH_FUNCTION(commonConstraintDataAtomsStabilityUpgrade)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpBallSocketConstraintAtom", 1, "hkpBallSocketConstraintAtom", 2)
	HK_PATCH_MEMBER_ADDED_BYTE("solvingMethod", 0)
	HK_PATCH_MEMBER_ADDED_REAL("solverStabilizationFactor", 1.000000f)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpLimitedHingeConstraintDataAtoms", 0, "hkpLimitedHingeConstraintDataAtoms", 1)
	HK_PATCH_MEMBER_ADDED("setupStabilization", TYPE_STRUCT, "hkpSetupStabilizationAtom", 0)
	HK_PATCH_DEPENDS("hkpSetupStabilizationAtom", 0)
	HK_PATCH_DEPENDS("hkpConstraintAtom", 0)
	HK_PATCH_FUNCTION(commonConstraintDataAtomsStabilityUpgrade)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpBallAndSocketConstraintDataAtoms", 0, "hkpBallAndSocketConstraintDataAtoms", 1)
	HK_PATCH_MEMBER_ADDED("setupStabilization", TYPE_STRUCT, "hkpSetupStabilizationAtom", 0)
	HK_PATCH_DEPENDS("hkpSetupStabilizationAtom", 0)
	HK_PATCH_DEPENDS("hkpConstraintAtom", 0)
	HK_PATCH_FUNCTION(commonConstraintDataAtomsStabilityUpgrade)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpRagdollConstraintDataAtoms", 0, "hkpRagdollConstraintDataAtoms", 1)
	HK_PATCH_MEMBER_ADDED("setupStabilization", TYPE_STRUCT, "hkpSetupStabilizationAtom", 0)
	HK_PATCH_DEPENDS("hkpSetupStabilizationAtom", 0)
	HK_PATCH_DEPENDS("hkpConstraintAtom", 0)
	HK_PATCH_FUNCTION(commonConstraintDataAtomsStabilityUpgrade)
HK_PATCH_END()


HK_PATCH_BEGIN("hkpMaterial", 0, "hkpMaterial", 1)
	HK_PATCH_MEMBER_ADDED("rollingFrictionMultiplier", TYPE_REAL, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpSimpleContactConstraintDataInfo", 0, "hkpSimpleContactConstraintDataInfo", 1)
	HK_PATCH_MEMBER_REMOVED("data", TYPE_TUPLE_INT, HK_NULL, 7)
	HK_PATCH_MEMBER_ADDED("data", TYPE_TUPLE_INT, HK_NULL, 5)
	HK_PATCH_MEMBER_ADDED("internalData0", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("rollingFrictionMultiplier", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("internalData1", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_FUNCTION(hkpSimpleContactConstraintDataInfo_0_to_1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpDisplayBindingDataRigidBody", 1, "hkpDisplayBindingDataRigidBody", 2)
	HK_PATCH_MEMBER_ADDED("displayObjectPtr", TYPE_OBJECT, "hkReferencedObject", 0)
	HK_PATCH_FUNCTION(hkpDisplayBindingDataRigidBody_1_to_2)
	HK_PATCH_MEMBER_REMOVED("displayObject", TYPE_OBJECT, "hkxMesh", 0)
	HK_PATCH_DEPENDS("hkxMesh", 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpBallSocketConstraintAtom", 2, "hkpBallSocketConstraintAtom", 3)
	HK_PATCH_MEMBER_DEFAULT_SET_BYTE("solvingMethod", 1)
	HK_PATCH_MEMBER_RENAMED("stabilizationFactor", "velocityStabilizationFactor")
	HK_PATCH_MEMBER_RENAMED("solverStabilizationFactor", "inertiaStabilizationFactor")
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("inertiaStabilizationFactor", 0.000000f)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpSetupStabilizationAtom", 0, "hkpSetupStabilizationAtom", 1)
	HK_PATCH_MEMBER_DEFAULT_SET_BYTE("enabled", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpWorldCinfo", 9, "hkpWorldCinfo", 10)
	HK_PATCH_MEMBER_RENAMED("useSplitCollisionPipelineOnCpu", "BETA_useSplitCollisionPipelineOnCpu")
	HK_PATCH_MEMBER_RENAMED("useSplitCollisionPipelineOnSpu", "BETA_useSplitCollisionPipelineOnSpu")
	HK_PATCH_MEMBER_RENAMED("useSplitCollisionPipelineForTois", "BETA_useSplitCollisionPipelineForTois")
HK_PATCH_END()

HK_PATCH_BEGIN("hkpMaterial", 1, "hkpMaterial", 2)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("rollingFrictionMultiplier", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpWorldCinfo", 10, "hkpWorldCinfo", 11)
	HK_PATCH_MEMBER_REMOVED("BETA_useSplitCollisionPipelineOnCpu", TYPE_INT, 0, 0)
	HK_PATCH_MEMBER_REMOVED("BETA_useSplitCollisionPipelineOnSpu", TYPE_INT, 0, 0)
	HK_PATCH_MEMBER_REMOVED("BETA_useSplitCollisionPipelineForTois", TYPE_INT, 0, 0)
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
