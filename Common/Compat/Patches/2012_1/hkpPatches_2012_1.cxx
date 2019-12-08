/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Physics specific product patches applied to release 2012_1.
// This file is #included by hkpPatches_2012_1.cpp


HK_PATCH_BEGIN("hkpBallSocketConstraintAtom", 4, "hkpBallSocketConstraintAtom", 5)
	HK_PATCH_DEPENDS("hkUFloat8", 0)
	HK_PATCH_MEMBER_ADDED("velocityStabilizationFactor_tmp", TYPE_STRUCT, "hkUFloat8", 0)
	HK_PATCH_FUNCTION(hkpBallSocketConstraintAtom_4_to_5)
	HK_PATCH_MEMBER_REMOVED("velocityStabilizationFactor", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_RENAMED("velocityStabilizationFactor_tmp", "velocityStabilizationFactor")
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpLinearClearanceConstraintData", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkpConstraintData")
	HK_PATCH_MEMBER_ADDED("atoms", TYPE_STRUCT, "hkpLinearClearanceConstraintDataAtoms", 0)
	HK_PATCH_DEPENDS("hkpLinearClearanceConstraintDataAtoms", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkpConstraintData", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpLinearClearanceConstraintDataAtoms", 0)
	HK_PATCH_MEMBER_ADDED("transforms", TYPE_STRUCT, "hkpSetLocalTransformsConstraintAtom", 0)
	HK_PATCH_MEMBER_ADDED("motor", TYPE_STRUCT, "hkpLinMotorConstraintAtom", 0)
	HK_PATCH_MEMBER_ADDED("friction0", TYPE_STRUCT, "hkpLinFrictionConstraintAtom", 0)
	HK_PATCH_MEMBER_ADDED("friction1", TYPE_STRUCT, "hkpLinFrictionConstraintAtom", 0)
	HK_PATCH_MEMBER_ADDED("friction2", TYPE_STRUCT, "hkpLinFrictionConstraintAtom", 0)
	HK_PATCH_MEMBER_ADDED("ang", TYPE_STRUCT, "hkpAngConstraintAtom", 0)
	HK_PATCH_MEMBER_ADDED("linLimit0", TYPE_STRUCT, "hkpLinLimitConstraintAtom", 0)
	HK_PATCH_MEMBER_ADDED("linLimit1", TYPE_STRUCT, "hkpLinLimitConstraintAtom", 0)
	HK_PATCH_MEMBER_ADDED("linLimit2", TYPE_STRUCT, "hkpLinLimitConstraintAtom", 0)
	HK_PATCH_DEPENDS("hkpLinLimitConstraintAtom", 0)
	HK_PATCH_DEPENDS("hkpSetLocalTransformsConstraintAtom", 0)
	HK_PATCH_DEPENDS("hkpConstraintAtom", 0)
	HK_PATCH_DEPENDS("hkpLinFrictionConstraintAtom", 0)
	HK_PATCH_DEPENDS("hkpAngConstraintAtom", 0)
	HK_PATCH_DEPENDS("hkpLinMotorConstraintAtom", 1)
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
