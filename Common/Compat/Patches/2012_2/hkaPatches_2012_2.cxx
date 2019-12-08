/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Animation specific product patches applied to release 2012_2.
// This file is #included by hkaPatches_2012_2.cpp

#if defined(HK_FEATURE_PRODUCT_PHYSICS)

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hknpRagdollKeyFrameHierarchyUtilityControlData", 0)
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

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hknpRagdollData", 0)
        HK_PATCH_PARENT_SET(HK_NULL, "hknpPhysicsSystemData")
        HK_PATCH_MEMBER_ADDED("skeleton", TYPE_OBJECT, "hkaSkeleton", 0)
        HK_PATCH_MEMBER_ADDED("boneToBodyMap", TYPE_ARRAY_INT, HK_NULL, 0)
        HK_PATCH_DEPENDS("hkBaseObject", 0)
        HK_PATCH_DEPENDS("hknpPhysicsSystemData", 0)
        HK_PATCH_DEPENDS("hkReferencedObject", 0)
        HK_PATCH_DEPENDS("hkaSkeleton", 5)
HK_PATCH_END()

#endif	// HK_FEATURE_PRODUCT_PHYSICS

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
