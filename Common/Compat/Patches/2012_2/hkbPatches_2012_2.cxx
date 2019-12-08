/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Behavior specific product patches applied to release 2012_2.
// This file is #included by hkbPatches_2012_2.cpp

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkbProceduralBlenderGenerator", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkbGenerator")
	HK_PATCH_DEPENDS("hkbNode", 1)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkbGenerator", 0)
	HK_PATCH_DEPENDS("hkbBindable", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkbParametricMotionGenerator", 1, "hkbParametricMotionGenerator", 2)
	HK_PATCH_PARENT_SET("hkbGenerator", "hkbProceduralBlenderGenerator")
HK_PATCH_END()

//////////////////////////////////////////////////////////////////////////
// New Physics interface/implementation specific classes
//////////////////////////////////////////////////////////////////////////

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkbConstraintSetup", 0)
	HK_PATCH_MEMBER_ADDED("type", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkbRagdollControllerSetup", 0)
	HK_PATCH_MEMBER_ADDED("type", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkbShapeSetup", 0)
	HK_PATCH_MEMBER_ADDED_REAL("capsuleHeight", 1.7f)
	HK_PATCH_MEMBER_ADDED_REAL("capsuleRadius", 0.4f)
	HK_PATCH_MEMBER_ADDED("fileName", TYPE_CSTRING, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("type", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkbRigidBodySetup", 0)
	HK_PATCH_MEMBER_ADDED_INT("collisionFilterInfo", 1)
	HK_PATCH_MEMBER_ADDED("type", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("shapeSetup", TYPE_STRUCT, "hkbShapeSetup", 0)
	HK_PATCH_DEPENDS("hkbShapeSetup", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkbCharacterControllerSetup", 0)
	HK_PATCH_MEMBER_ADDED("rigidBodySetup", TYPE_STRUCT, "hkbRigidBodySetup", 0)
	HK_PATCH_MEMBER_ADDED("controllerCinfo", TYPE_OBJECT, "hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkbRigidBodySetup", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkbRagdollInterface", 0)
    HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
    HK_PATCH_DEPENDS("hkBaseObject", 0)
    HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkbPhysicsInterface", 0)
    HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
    HK_PATCH_DEPENDS("hkBaseObject", 0)
    HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkbNullPhysicsInterface", 0)
    HK_PATCH_PARENT_SET(HK_NULL, "hkbPhysicsInterface")
    HK_PATCH_DEPENDS("hkbPhysicsInterface", 0)
    HK_PATCH_DEPENDS("hkBaseObject", 0)
    HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkbKeyFrameControlData", 0)
    HK_PATCH_MEMBER_ADDED_REAL("hierarchyGain", 0.170000f)
    HK_PATCH_MEMBER_ADDED_REAL("velocityDamping", 0.000000f)
    HK_PATCH_MEMBER_ADDED_REAL("accelerationGain", 1.000000f)
    HK_PATCH_MEMBER_ADDED_REAL("velocityGain", 0.600000f)
    HK_PATCH_MEMBER_ADDED_REAL("positionGain", 0.050000f)
    HK_PATCH_MEMBER_ADDED_REAL("positionMaxLinearVelocity", 1.400000f)
    HK_PATCH_MEMBER_ADDED_REAL("positionMaxAngularVelocity", 1.800000f)
    HK_PATCH_MEMBER_ADDED_REAL("snapGain", 0.100000f)
    HK_PATCH_MEMBER_ADDED_REAL("snapMaxLinearVelocity", 0.300000f)
    HK_PATCH_MEMBER_ADDED_REAL("snapMaxAngularVelocity", 0.300000f)
    HK_PATCH_MEMBER_ADDED_REAL("snapMaxLinearDistance", 0.030000f)
    HK_PATCH_MEMBER_ADDED_REAL("snapMaxAngularDistance", 0.100000f)
HK_PATCH_END()

#if defined(HK_FEATURE_PRODUCT_PHYSICS_2012)

HK_PATCH_BEGIN("hkbCharacterData", 9, "hkbCharacterData", 10)
	HK_PATCH_MEMBER_ADDED("characterControllerSetup", TYPE_STRUCT, "hkbCharacterControllerSetup", 0)
	HK_PATCH_FUNCTION(hkbCharacterData_9_to_10)
	HK_PATCH_MEMBER_REMOVED("characterControllerInfo", TYPE_STRUCT, "hkbCharacterDataCharacterControllerInfo", 0)
	HK_PATCH_DEPENDS("hkbCharacterControllerSetup", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkbRigidBodyRagdollControlData", 1, "hkbRigidBodyRagdollControlData", 2)
	HK_PATCH_MEMBER_ADDED("keyFrameControlData", TYPE_STRUCT, "hkbKeyFrameControlData", 0)
	HK_PATCH_FUNCTION(hkbRigidBodyRagdollControlData_1_to_2)
	HK_PATCH_MEMBER_REMOVED("keyFrameHierarchyControlData", TYPE_STRUCT, "hkaKeyFrameHierarchyUtilityControlData", 0)
	HK_PATCH_DEPENDS("hkaKeyFrameHierarchyUtilityControlData", 0)
	HK_PATCH_DEPENDS("hkbKeyFrameControlData", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkbpRagdollInterface", 0)
    HK_PATCH_PARENT_SET(HK_NULL, "hkbRagdollInterface")
    HK_PATCH_DEPENDS("hkBaseObject", 0)
    HK_PATCH_DEPENDS("hkbRagdollInterface", 0)
    HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkbpPhysicsInterface", 0)
    HK_PATCH_PARENT_SET(HK_NULL, "hkbPhysicsInterface")
    HK_PATCH_DEPENDS("hkbPhysicsInterface", 0)
    HK_PATCH_DEPENDS("hkBaseObject", 0)
    HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

#endif

#if defined(HK_FEATURE_PRODUCT_PHYSICS)

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkbnpRagdollInterface", 0)
    HK_PATCH_PARENT_SET(HK_NULL, "hkbRagdollInterface")
    HK_PATCH_DEPENDS("hkBaseObject", 0)
    HK_PATCH_DEPENDS("hkbRagdollInterface", 0)
    HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkbnpPhysicsInterface", 0)
    HK_PATCH_PARENT_SET(HK_NULL, "hkbPhysicsInterface")
    HK_PATCH_DEPENDS("hkbPhysicsInterface", 0)
    HK_PATCH_DEPENDS("hkBaseObject", 0)
    HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

#endif

//////////////////////////////////////////////////////////////////////////
// Renamed deprecated Physics implementation specific classes / old dependency clean-up
//////////////////////////////////////////////////////////////////////////

#if defined(HK_FEATURE_PRODUCT_PHYSICS_2012)

HK_PATCH_BEGIN("hkbCharacterDataCharacterControllerInfo", 0, HK_NULL, HK_CLASS_REMOVED)
	HK_PATCH_MEMBER_REMOVED("capsuleHeight", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("capsuleRadius", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("collisionFilterInfo", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("characterControllerCinfo", TYPE_OBJECT, "hkpCharacterControllerCinfo", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkpCharacterControllerCinfo", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkbHandle", 1, "hkbHandle", 2)
	HK_PATCH_MEMBER_REMOVED("rigidBody", TYPE_OBJECT, "hkpRigidBody", 0)
	HK_PATCH_MEMBER_ADDED_POINTER("rigidBody", "hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkpRigidBody", 0)
	HK_PATCH_DEPENDS("hkpEntity", 3)
	HK_PATCH_DEPENDS("hkpWorldObject", 0)
HK_PATCH_END()

#endif

HK_PATCH_BEGIN("hkbTarget", 2, "hkbpTarget", 3)
HK_PATCH_END()

HK_PATCH_BEGIN("hkbTargetRigidBodyModifier", 3, "hkbpTargetRigidBodyModifier", 4)
	HK_PATCH_DEPENDS("hkbpTarget", 3)
HK_PATCH_END()

HK_PATCH_BEGIN("hkbReachTowardTargetModifierHand", 1, "hkbpReachTowardTargetModifierHand", 2)
HK_PATCH_END()

HK_PATCH_BEGIN("hkbReachTowardTargetModifier", 1, "hkbpReachTowardTargetModifier", 2)
	HK_PATCH_DEPENDS("hkbpTarget", 3)
	HK_PATCH_DEPENDS("hkbpReachTowardTargetModifierHand", 2)
HK_PATCH_END()

HK_PATCH_BEGIN("hkbReachModifierHand", 0, "hkbpReachModifierHand", 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkbReachModifier", 0, "hkbpReachModifier", 1)
	HK_PATCH_DEPENDS("hkbpReachModifierHand", 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkbMoveBoneTowardTargetModifier", 2, "hkbpMoveBoneTowardTargetModifier", 3)
	HK_PATCH_DEPENDS("hkbpTarget", 3)
HK_PATCH_END()

HK_PATCH_BEGIN("hkbFaceTargetModifier", 1, "hkbpFaceTargetModifier", 2)
	HK_PATCH_DEPENDS("hkbpTarget", 3)
HK_PATCH_END()

HK_PATCH_BEGIN("hkbControlledReachModifier", 0, "hkbpControlledReachModifier", 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkbConstrainRigidBodyModifier", 1, "hkbpConstrainRigidBodyModifier", 2)
	HK_PATCH_DEPENDS("hkbpTarget", 3)
HK_PATCH_END()

HK_PATCH_BEGIN("hkbCheckRagdollSpeedModifier", 1, "hkbpCheckRagdollSpeedModifier", 2)
HK_PATCH_END()

HK_PATCH_BEGIN("hkbCheckBalanceModifier", 0, "hkbpCheckBalanceModifier", 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkbBalanceModifierStepInfo", 0, "hkbpBalanceModifierStepInfo", 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkbBalanceModifier", 0, "hkbpBalanceModifier", 1)
	HK_PATCH_DEPENDS("hkbpBalanceModifierStepInfo", 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkbCatchFallModifierHand", 1, "hkbpCatchFallModifierHand", 2)
HK_PATCH_END()

HK_PATCH_BEGIN("hkbCatchFallModifier", 1, "hkbpCatchFallModifier", 2)
	HK_PATCH_DEPENDS("hkbpCatchFallModifierHand", 2)
HK_PATCH_END()

HK_PATCH_BEGIN("hkbBalanceRadialSelectorGenerator", 0, "hkbpBalanceRadialSelectorGenerator", 1)
	HK_PATCH_DEPENDS("hkbpCheckBalanceModifier", 1)
HK_PATCH_END()

//////////////////////////////////////////////////////////////////////////
// New Ai interface/implementation specific classes
//////////////////////////////////////////////////////////////////////////

// control data

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkbAiControlControlDataNonBlendable", 0)
	HK_PATCH_MEMBER_ADDED_BYTE("canControl", 1)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkbAiControlControlData", 0)
	HK_PATCH_MEMBER_ADDED("blendable", TYPE_STRUCT, "hkbAiControlControlDataBlendable", 0)
	HK_PATCH_MEMBER_ADDED("nonBlendable", TYPE_STRUCT, "hkbAiControlControlDataNonBlendable", 0)
	HK_PATCH_DEPENDS("hkbAiControlControlDataBlendable", 0)
	HK_PATCH_DEPENDS("hkbAiControlControlDataNonBlendable", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkbAiControlControlDataBlendable", 0)
	HK_PATCH_MEMBER_ADDED_REAL("desiredSpeed", 5.000000f)
	HK_PATCH_MEMBER_ADDED_REAL("maximumSpeed", 5.000000f)
HK_PATCH_END()

HK_PATCH_BEGIN("hkbCharacterData", 8, "hkbCharacterData", 9)
	HK_PATCH_MEMBER_ADDED("aiControlDriverInfo", TYPE_OBJECT, "hkReferencedObject", 0)
HK_PATCH_END()

// commands

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkbAiControlCancelPathCommand", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("characterId", TYPE_INT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkbAiControlPathToCommand", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("characterId", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("goalPoint", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

#if defined(HK_FEATURE_PRODUCT_AI)

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkbAiControlDriverInfo", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED_REAL("radius", 0.400000f)
	HK_PATCH_MEMBER_ADDED_INT("stateSource", 0)
	HK_PATCH_MEMBER_ADDED_INT("customSourceBone", -1)
	HK_PATCH_MEMBER_ADDED_BYTE("loopBackVelocity", 0)
	HK_PATCH_MEMBER_ADDED_REAL("sensorHorizontalExtent", 5.000000f)
	HK_PATCH_MEMBER_ADDED_REAL("sensorHeight", 2.000000f)
	HK_PATCH_MEMBER_ADDED_REAL("wallFollowingAngle", 0.100000f)
	HK_PATCH_MEMBER_ADDED_REAL("velocityHysteresis", 0.010000f)
	HK_PATCH_MEMBER_ADDED_REAL("sidednessChangingPenalty", 0.000000f)
	HK_PATCH_MEMBER_ADDED_REAL("collisionPenalty", 1.000000f)
	HK_PATCH_MEMBER_ADDED_REAL("penetrationPenalty", 100.000000f)
	HK_PATCH_MEMBER_ADDED_INT("maxNeighbors", 16)
	HK_PATCH_MEMBER_ADDED_REAL("leftTurnRadius", -1.000000f)
	HK_PATCH_MEMBER_ADDED_REAL("rightTurnRadius", -1.000000f)
	HK_PATCH_MEMBER_ADDED_REAL("goalDistTolerance", 0.250000f)
	HK_PATCH_MEMBER_ADDED_REAL("userEdgeTolerance", 0.250000f)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkbAiControlModifier", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkbModifier")
	HK_PATCH_MEMBER_ADDED("controlData", TYPE_STRUCT, "hkbAiControlControlData", 0)
	HK_PATCH_DEPENDS("hkbNode", 1)
	HK_PATCH_DEPENDS("hkbAiControlControlData", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkbModifier", 0)
	HK_PATCH_DEPENDS("hkbBindable", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkbAiSteeringModifierSteeringInfo", 0)
	HK_PATCH_MEMBER_ADDED("requestedVelocity", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("forwardSpeed", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("rightSpeed", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("totalSpeed", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("localAngle", TYPE_REAL, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkbAiSteeringModifier", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkbModifier")
	HK_PATCH_MEMBER_ADDED("steeringInfo", TYPE_STRUCT, "hkbAiSteeringModifierSteeringInfo", 0)
	HK_PATCH_MEMBER_ADDED("userEdgeInfo", TYPE_STRUCT, "hkbAiSteeringModifierUserEdgeInfo", 0)
	HK_PATCH_MEMBER_ADDED("eventMapping", TYPE_STRUCT, "hkbAiSteeringModifierEventMapping", 0)
	HK_PATCH_MEMBER_ADDED("defaultControlData", TYPE_STRUCT, "hkbAiControlControlData", 0)
	HK_PATCH_DEPENDS("hkbAiControlControlData", 0)
	HK_PATCH_DEPENDS("hkbNode", 1)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkbAiSteeringModifierEventMapping", 0)
	HK_PATCH_DEPENDS("hkbAiSteeringModifierUserEdgeInfo", 0)
	HK_PATCH_DEPENDS("hkbModifier", 0)
	HK_PATCH_DEPENDS("hkbBindable", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkbAiSteeringModifierSteeringInfo", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkbAiSteeringModifierUserEdgeEvent", 0)
	HK_PATCH_MEMBER_ADDED_INT("userdataId", 0)
	HK_PATCH_MEMBER_ADDED_INT("userdataMask", 0xFFFFFFFF)
	HK_PATCH_MEMBER_ADDED("event", TYPE_STRUCT, "hkbEventProperty", 0)
	HK_PATCH_DEPENDS("hkbEventProperty", 1)
	HK_PATCH_DEPENDS("hkbEventBase", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkbAiSteeringModifierEventMapping", 0)
	HK_PATCH_MEMBER_ADDED("startPath", TYPE_STRUCT, "hkbEventProperty", 0)
	HK_PATCH_MEMBER_ADDED("goalReached", TYPE_STRUCT, "hkbEventProperty", 0)
	HK_PATCH_MEMBER_ADDED("pathCancelled", TYPE_STRUCT, "hkbEventProperty", 0)
	HK_PATCH_MEMBER_ADDED("userEdgeEvents", TYPE_ARRAY_STRUCT, "hkbAiSteeringModifierUserEdgeEvent", 0)
	HK_PATCH_DEPENDS("hkbEventProperty", 1)
	HK_PATCH_DEPENDS("hkbAiSteeringModifierUserEdgeEvent", 0)
	HK_PATCH_DEPENDS("hkbEventBase", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkbAiSteeringModifierInternalState", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("requestedVelocityInternal", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("hasLastUserEdgeEntry", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("lastUserEdgeEntry", TYPE_STRUCT, "hkbAiSteeringModifierInternalUserEdgeInfo", 0)
	HK_PATCH_DEPENDS("hkbAiSteeringModifierInternalUserEdgeInfo", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkbAiSteeringModifierUserEdgeInfo", 0)
	HK_PATCH_MEMBER_ADDED("hasEntryInfoOut", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("entryUserDataOut", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("entryPointOut", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("exitPointOut", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("entryEdgeDirection", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("exitEdgeDirection", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("localAngleToExitPointOut", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("localAngleToTraversalDirectionOut", TYPE_REAL, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkbAiSteeringModifierInternalUserEdgeInfo", 0)
	HK_PATCH_MEMBER_ADDED("entrySection", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("entryPoint", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("entryData", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("oppositeSection", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("entryEdgeDirection", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("edgeTransform", TYPE_VEC_16, HK_NULL, 0)
HK_PATCH_END()

#endif

//////////////////////////////////////////////////////////////////////////
// Demo or Test Related
//////////////////////////////////////////////////////////////////////////

HK_PATCH_BEGIN("hkbDemoConfigStickVariableInfo", 1, HK_NULL, HK_CLASS_REMOVED)
    HK_PATCH_MEMBER_REMOVED("variableName", TYPE_CSTRING, HK_NULL, 0)
    HK_PATCH_MEMBER_REMOVED("minValue", TYPE_REAL, HK_NULL, 0)
    HK_PATCH_MEMBER_REMOVED("maxValue", TYPE_REAL, HK_NULL, 0)
    HK_PATCH_MEMBER_REMOVED("minStickValue", TYPE_REAL, HK_NULL, 0)
    HK_PATCH_MEMBER_REMOVED("maxStickValue", TYPE_REAL, HK_NULL, 0)
    HK_PATCH_MEMBER_REMOVED("stickAxis", TYPE_INT, HK_NULL, 0)
    HK_PATCH_MEMBER_REMOVED("stick", TYPE_INT, HK_NULL, 0)
    HK_PATCH_MEMBER_REMOVED("complimentVariableValue", TYPE_BYTE, HK_NULL, 0)
    HK_PATCH_MEMBER_REMOVED("negateVariableValue", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkbDemoConfigCharacterInfo", 3, HK_NULL, HK_CLASS_REMOVED)
    HK_PATCH_PARENT_SET("hkReferencedObject", HK_NULL)
    HK_PATCH_MEMBER_REMOVED("overrideCharacterDataFilename", TYPE_CSTRING, HK_NULL, 0)
    HK_PATCH_MEMBER_REMOVED("initialPosition", TYPE_VEC_4, HK_NULL, 0)
    HK_PATCH_MEMBER_REMOVED("initialRotation", TYPE_VEC_4, HK_NULL, 0)
    HK_PATCH_MEMBER_REMOVED("modelUpAxis", TYPE_INT, HK_NULL, 0)
    HK_PATCH_MEMBER_REMOVED("ragdollBoneLayers", TYPE_ARRAY_INT, HK_NULL, 0)
    HK_PATCH_MEMBER_REMOVED("overrideBehaviorFilename", TYPE_CSTRING, HK_NULL, 0)
    HK_PATCH_DEPENDS("hkBaseObject", 0)
    HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

#ifdef HK_FEATURE_PRODUCT_PHYSICS_2012

HK_PATCH_BEGIN("hkbDemoConfig", 5, HK_NULL, HK_CLASS_REMOVED)
    HK_PATCH_PARENT_SET("hkReferencedObject", HK_NULL)
    HK_PATCH_MEMBER_REMOVED("characterInfo", TYPE_ARRAY_OBJECT, "hkbDemoConfigCharacterInfo", 0)
    HK_PATCH_MEMBER_REMOVED("terrainInfo", TYPE_ARRAY_STRUCT, "hkbDemoConfigTerrainInfo", 0)
    HK_PATCH_MEMBER_REMOVED("skinAttributeIndices", TYPE_ARRAY_INT, HK_NULL, 0)
    HK_PATCH_MEMBER_REMOVED("buttonPressToEventMap", TYPE_TUPLE_INT, HK_NULL, 16)
    HK_PATCH_MEMBER_REMOVED("buttonReleaseToEventMap", TYPE_TUPLE_INT, HK_NULL, 16)
    HK_PATCH_MEMBER_REMOVED("worldUpAxis", TYPE_INT, HK_NULL, 0)
    HK_PATCH_MEMBER_REMOVED("extraCharacterClones", TYPE_INT, HK_NULL, 0)
    HK_PATCH_MEMBER_REMOVED("numTracks", TYPE_INT, HK_NULL, 0)
    HK_PATCH_MEMBER_REMOVED("proxyHeight", TYPE_REAL, HK_NULL, 0)
    HK_PATCH_MEMBER_REMOVED("proxyRadius", TYPE_REAL, HK_NULL, 0)
    HK_PATCH_MEMBER_REMOVED("proxyOffset", TYPE_REAL, HK_NULL, 0)
    HK_PATCH_MEMBER_REMOVED("rootPath", TYPE_CSTRING, HK_NULL, 0)
    HK_PATCH_MEMBER_REMOVED("projectDataFilename", TYPE_CSTRING, HK_NULL, 0)
    HK_PATCH_MEMBER_REMOVED("useAttachments", TYPE_BYTE, HK_NULL, 0)
    HK_PATCH_MEMBER_REMOVED("useProxy", TYPE_BYTE, HK_NULL, 0)
    HK_PATCH_MEMBER_REMOVED("useSkyBox", TYPE_BYTE, HK_NULL, 0)
    HK_PATCH_MEMBER_REMOVED("useTrackingCamera", TYPE_BYTE, HK_NULL, 0)
    HK_PATCH_MEMBER_REMOVED("accumulateMotion", TYPE_BYTE, HK_NULL, 0)
    HK_PATCH_MEMBER_REMOVED("testCloning", TYPE_BYTE, HK_NULL, 0)
    HK_PATCH_MEMBER_REMOVED("useSplineCompression", TYPE_BYTE, HK_NULL, 0)
    HK_PATCH_MEMBER_REMOVED("gamePadToRotateTerrainAboutItsAxisMap", TYPE_TUPLE_INT, HK_NULL, 6)
    HK_PATCH_MEMBER_REMOVED("gamePadToAddRemoveCharacterMap", TYPE_TUPLE_INT, HK_NULL, 2)
    HK_PATCH_MEMBER_REMOVED("filter", TYPE_OBJECT, "hkpGroupFilter", 0)
    HK_PATCH_MEMBER_REMOVED("stickVariables", TYPE_ARRAY_STRUCT, "hkbDemoConfigStickVariableInfo", 0)
    HK_PATCH_MEMBER_REMOVED("forceLoad", TYPE_BYTE, HK_NULL, 0)
    HK_PATCH_DEPENDS("hkBaseObject", 0)
    HK_PATCH_DEPENDS("hkbDemoConfigCharacterInfo", 3)
    HK_PATCH_DEPENDS("hkbDemoConfigStickVariableInfo", 1)
    HK_PATCH_DEPENDS("hkpGroupFilter", 0)
    HK_PATCH_DEPENDS("hkReferencedObject", 0)
    HK_PATCH_DEPENDS("hkpCollisionFilter", 0)
    HK_PATCH_DEPENDS("hkbDemoConfigTerrainInfo", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkbDemoConfigTerrainInfo", 0, HK_NULL, HK_CLASS_REMOVED)
    HK_PATCH_MEMBER_REMOVED("filename", TYPE_CSTRING, HK_NULL, 0)
    HK_PATCH_MEMBER_REMOVED("layer", TYPE_INT, HK_NULL, 0)
    HK_PATCH_MEMBER_REMOVED("systemGroup", TYPE_INT, HK_NULL, 0)
    HK_PATCH_MEMBER_REMOVED("createDisplayObjects", TYPE_BYTE, HK_NULL, 0)
    HK_PATCH_MEMBER_REMOVED("terrainRigidBody", TYPE_OBJECT, "hkpRigidBody", 0)
    HK_PATCH_DEPENDS("hkpRigidBody", 0)
    HK_PATCH_DEPENDS("hkpEntity", 3)
    HK_PATCH_DEPENDS("hkBaseObject", 0)
    HK_PATCH_DEPENDS("hkpWorldObject", 0)
    HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkbCustomTestGenerator", 0, "hkbCustomTestGenerator", 1)
    HK_PATCH_MEMBER_REMOVED("hkRigidBody", TYPE_OBJECT, "hkpRigidBody", 0)
    HK_PATCH_MEMBER_ADDED_POINTER("hkRigidBody", "hkReferencedObject", 0)
    HK_PATCH_DEPENDS("hkpRigidBody", 0)
    HK_PATCH_DEPENDS("hkpEntity", 3)
    HK_PATCH_DEPENDS("hkpWorldObject", 0)
HK_PATCH_END()

#endif

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
