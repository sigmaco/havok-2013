/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Physics specific product patches applied to release 710.
// This file is #included by hkpPatches_710.cpp

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpCharacterRigidBodyCinfo", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkpCharacterControllerCinfo")
	HK_PATCH_MEMBER_ADDED("collisionFilterInfo", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("shape", TYPE_OBJECT, "hkpShape", 0)
	HK_PATCH_MEMBER_ADDED("position", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("rotation", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED_REAL("mass", 100.000000f)
	HK_PATCH_MEMBER_ADDED_REAL("friction", 0.000000f)
	HK_PATCH_MEMBER_ADDED_REAL("maxLinearVelocity", 20.000000f)
	HK_PATCH_MEMBER_ADDED_REAL("allowedPenetrationDepth", -0.100000f)
	HK_PATCH_MEMBER_ADDED("up", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED_REAL("maxSlope", 1.047198f)
	HK_PATCH_MEMBER_ADDED_REAL("maxForce", 1000.000000f)
	HK_PATCH_MEMBER_ADDED_REAL("unweldingHeightOffsetFactor", 0.500000f)
	HK_PATCH_MEMBER_ADDED_REAL("maxSpeedForSimplexSolver", 10.000000f)
	HK_PATCH_MEMBER_ADDED_REAL("supportDistance", 0.100000f)
	HK_PATCH_MEMBER_ADDED_REAL("hardSupportDistance", 0.000000f)
	HK_PATCH_MEMBER_ADDED("vdbColor", TYPE_INT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkpCharacterControllerCinfo", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpCharacterControllerCinfo", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpMultithreadedVehicleManager", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkpVehicleManager")
	HK_PATCH_DEPENDS("hkpVehicleManager", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpCharacterProxyCinfo", 0, "hkpCharacterProxyCinfo", 1)
	HK_PATCH_PARENT_SET(HK_NULL, "hkpCharacterControllerCinfo")
	HK_PATCH_DEPENDS("hkpCharacterControllerCinfo", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpConvexVerticesShape", 2, "hkpConvexVerticesShape", 3)
	HK_PATCH_MEMBER_REMOVED("convexPiece", TYPE_OBJECT, "hkpCompressedMeshShapeConvexPiece", 0)
	HK_PATCH_DEPENDS("hkpCompressedMeshShapeConvexPiece", 3)
HK_PATCH_END()


//HK_PATCH_BEGIN("hkpWorldCinfo", 8, "hkpWorldCinfo", 9)
//	HK_PATCH_MEMBER_ADDED("enableForceLimitBreachedSecondaryEventsFromToiSolver", TYPE_BYTE, HK_NULL, 0)
//		HK_PATCH_FUNCTION(hkpWorldCinfo_8_to_9)
//HK_PATCH_END()

HK_PATCH_BEGIN("hkpCompressedMeshShape", 8, "hkpCompressedMeshShape", 9)
	HK_PATCH_MEMBER_ADDED("newtransforms", TYPE_ARRAY_VEC_12, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("defaultCollisionFilterInfo", TYPE_INT, HK_NULL, 0)
	HK_PATCH_FUNCTION(hkpCompressedMeshShape_8_to_9)
	HK_PATCH_MEMBER_REMOVED("transforms", TYPE_ARRAY_VEC_16, HK_NULL, 0)
	HK_PATCH_MEMBER_RENAMED("newtransforms", "transforms")
HK_PATCH_END()

HK_PATCH_BEGIN("hkpCompressedMeshShapeBigTriangle", 1, "hkpCompressedMeshShapeBigTriangle", 2)
	HK_PATCH_MEMBER_ADDED_INT("transformIndex", 0xffff)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpExtendedMeshShapeSubpart", 0, "hkpExtendedMeshShapeSubpart", 1)
	HK_PATCH_MEMBER_ADDED_INT("userData", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpExtendedMeshShapeTrianglesSubpart", 2, "hkpExtendedMeshShapeTrianglesSubpart", 3)
	HK_PATCH_MEMBER_REMOVED("userData", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED_VEC_12_IDENTITY("transform")
HK_PATCH_END()

HK_PATCH_BEGIN("hkpExtendedMeshShape", 2, "hkpExtendedMeshShape", 3)
	HK_PATCH_DEPENDS("hkpExtendedMeshShapeTrianglesSubpart", 3)
	HK_PATCH_FUNCTION(hkpExtendedMeshShape_2_to_3)
	HK_PATCH_MEMBER_REMOVED("scaling", TYPE_VEC_4, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpExtendedMeshShapeSubpart", 1, "hkpExtendedMeshShapeSubpart", 2)
	HK_PATCH_MEMBER_REMOVED("materialStriding", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpRackAndPinionConstraintDataAtoms", 0)
	HK_PATCH_MEMBER_ADDED("transforms", TYPE_STRUCT, "hkpSetLocalTransformsConstraintAtom", 0)
	HK_PATCH_MEMBER_ADDED("rackAndPinion", TYPE_STRUCT, "hkpRackAndPinionConstraintAtom", 0)
	HK_PATCH_DEPENDS("hkpRackAndPinionConstraintAtom", 0)
	HK_PATCH_DEPENDS("hkpSetLocalTransformsConstraintAtom", 0)
	HK_PATCH_DEPENDS("hkpConstraintAtom", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpRackAndPinionConstraintAtom", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkpConstraintAtom")
	HK_PATCH_MEMBER_ADDED("pinionRadiusOrScrewPitch", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("isScrew", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("memOffsetToInitialAngleOffset", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("memOffsetToPrevAngle", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("memOffsetToRevolutionCounter", TYPE_INT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkpConstraintAtom", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpRackAndPinionConstraintData", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkpConstraintData")
	HK_PATCH_MEMBER_ADDED("atoms", TYPE_STRUCT, "hkpRackAndPinionConstraintDataAtoms", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkpConstraintData", 0)
	HK_PATCH_DEPENDS("hkpRackAndPinionConstraintDataAtoms", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpCogWheelConstraintAtom", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkpConstraintAtom")
	HK_PATCH_MEMBER_ADDED("cogWheelRadiusA", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("cogWheelRadiusB", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("isScrew", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("memOffsetToInitialAngleOffset", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("memOffsetToPrevAngle", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("memOffsetToRevolutionCounter", TYPE_INT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkpConstraintAtom", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpCogWheelConstraintDataAtoms", 0)
	HK_PATCH_MEMBER_ADDED("transforms", TYPE_STRUCT, "hkpSetLocalTransformsConstraintAtom", 0)
	HK_PATCH_MEMBER_ADDED("cogWheels", TYPE_STRUCT, "hkpCogWheelConstraintAtom", 0)
	HK_PATCH_DEPENDS("hkpSetLocalTransformsConstraintAtom", 0)
	HK_PATCH_DEPENDS("hkpConstraintAtom", 0)
	HK_PATCH_DEPENDS("hkpCogWheelConstraintAtom", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpCogWheelConstraintData", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkpConstraintData")
	HK_PATCH_MEMBER_ADDED("atoms", TYPE_STRUCT, "hkpCogWheelConstraintDataAtoms", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkpConstraintData", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkpCogWheelConstraintDataAtoms", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpEntity", 2, "hkpEntity", 3)
	HK_PATCH_MEMBER_ADDED("npData", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpPairCollisionFilter", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkpCollisionFilter")
	HK_PATCH_MEMBER_ADDED("childFilter", TYPE_OBJECT, "hkpCollisionFilter", 0)
	HK_PATCH_DEPENDS("hkpCollisionFilter", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpConstraintCollisionFilter", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkpPairCollisionFilter")
	HK_PATCH_DEPENDS("hkpPairCollisionFilter", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpPairCollisionFilterMapPairFilterKeyOverrideType", 0)
	HK_PATCH_MEMBER_ADDED("numElems", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("hashMod", TYPE_INT, HK_NULL, 0)
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
