/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Physics specific product patches applied to release 2011_2.
// This file is #included by hkpPatches_2011_2.cpp

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpShapeBase", 0)
	HK_PATCH_PARENT_SET("hkReferencedObject", "hkcdShape")
	HK_PATCH_DEPENDS("hkcdShape", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpShape", 0, "hkpShape", 1)
	HK_PATCH_PARENT_SET("hkReferencedObject", "hkpShapeBase")
	HK_PATCH_DEPENDS("hkpShapeBase", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpBreakableShape", 0, "hkpBreakableShape", 1)
	HK_PATCH_MEMBER_RENAMED("physicsShape", "oldPhysicsShape")
	HK_PATCH_MEMBER_ADDED("physicsShape", TYPE_OBJECT, "hkcdShape", 0)
	HK_PATCH_FUNCTION(hkpBreakableShape_0_to_1)
	HK_PATCH_MEMBER_REMOVED("oldPhysicsShape", TYPE_OBJECT, "hkpShape", 0)
	HK_PATCH_DEPENDS("hkpShape", 1)
	HK_PATCH_DEPENDS("hkpShapeBase", 0)
	HK_PATCH_DEPENDS("hkcdShape", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpWorldCinfo", 16, "hkpWorldCinfo", 17)
	HK_PATCH_FUNCTION(hkpWorldCinfo_16_to_17)
	HK_PATCH_MEMBER_REMOVED("autoUpdateKdTree", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpConvexTransformShape", 1, "hkpConvexTransformShape", 2)
	HK_PATCH_MEMBER_ADDED("extraScale", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_FUNCTION(hkpConvexTransformShape_1_to_2)
	HK_PATCH_DEPENDS("hkpConvexShape", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpBvCompressedMeshShape", 0, "hkpBvCompressedMeshShape", 1)
	HK_PATCH_MEMBER_RENAMED("hasPerTriangleCollisionFilterInfo", "hasPerPrimitiveCollisionFilterInfo")
	HK_PATCH_MEMBER_RENAMED("hasPerTriangleUserData", "hasPerPrimitiveUserData")	
HK_PATCH_END()

HK_PATCH_BEGIN("hkpVehicleInstanceWheelInfo", 1, "hkpVehicleInstanceWheelInfo", 2)
    HK_PATCH_MEMBER_ADDED_REAL("noSlipIdealSpinVelocity", 0.0f)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpVehicleInstance", 0, "hkpVehicleInstance", 1)
    HK_PATCH_MEMBER_ADDED_REAL("mainSteeringAngleAssumingNoReduction", 0.0f)
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
