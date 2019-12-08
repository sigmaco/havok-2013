/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Common specific product patches applied to release 2012_1.
// This file is #included by hkPatches_2012_1.cpp

HK_PATCH_BEGIN("hkxLight", 2, "hkxLight", 3)
		HK_PATCH_MEMBER_ADDED("decayRate", TYPE_INT, HK_NULL, 0)
		HK_PATCH_MEMBER_DEFAULT_SET_INT("decayRate", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkUFloat8", 0)
		HK_PATCH_MEMBER_ADDED("value", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkContactPointMaterial", 0, "hkContactPointMaterial", 1)
		HK_PATCH_DEPENDS("hkUFloat8", 0)
		HK_PATCH_MEMBER_ADDED("friction_tmp", TYPE_STRUCT, "hkUFloat8", 0)
		HK_PATCH_MEMBER_ADDED("maxImpulse_tmp", TYPE_STRUCT, "hkUFloat8", 0)
		HK_PATCH_FUNCTION(hkContactPointMaterial_0_to_1)
		HK_PATCH_MEMBER_REMOVED("friction", TYPE_BYTE, HK_NULL, 0)
		HK_PATCH_MEMBER_REMOVED("maxImpulse", TYPE_BYTE, HK_NULL, 0)
		HK_PATCH_MEMBER_RENAMED("friction_tmp", "friction")
		HK_PATCH_MEMBER_RENAMED("maxImpulse_tmp", "maxImpulse")
HK_PATCH_END()

HK_PATCH_BEGIN("hkMotionState", 1, "hkMotionState", 2)
		HK_PATCH_DEPENDS("hkUFloat8", 0)
		HK_PATCH_MEMBER_ADDED("maxLinearVelocity_tmp", TYPE_STRUCT, "hkUFloat8", 0)
		HK_PATCH_MEMBER_ADDED("maxAngularVelocity_tmp", TYPE_STRUCT, "hkUFloat8", 0)
		HK_PATCH_FUNCTION(hkMotionState_1_to_2)
		HK_PATCH_MEMBER_REMOVED("maxLinearVelocity", TYPE_BYTE, HK_NULL, 0)
		HK_PATCH_MEMBER_REMOVED("maxAngularVelocity", TYPE_BYTE, HK_NULL, 0)
		HK_PATCH_MEMBER_RENAMED("maxLinearVelocity_tmp", "maxLinearVelocity")
		HK_PATCH_MEMBER_RENAMED("maxAngularVelocity_tmp", "maxAngularVelocity")
HK_PATCH_END()

HK_PATCH_BEGIN("hkxVertexDescriptionElementDecl", 2, "hkxVertexDescriptionElementDecl", 3)
	HK_PATCH_MEMBER_ADDED("hint", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkxMeshSection", 3, "hkxMeshSection", 4)
HK_PATCH_MEMBER_ADDED("linearKeyFrameHints", TYPE_ARRAY_REAL, HK_NULL, 0)
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
