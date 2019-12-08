/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Common specific product patches applied to release 2010_1.
// This file is #included by hkPatches_2010_1.cpp

HK_PATCH_BEGIN("hkMotionState", 0, "hkMotionState", 1)
	HK_PATCH_MEMBER_ADDED("timeFactor", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_FUNCTION(hkMotionState_0_to_1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkHalf8", 0, "hkHalf8", 1)
	HK_PATCH_MEMBER_RENAMED("vec", "quad")
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkAabbHalf", 0)
	HK_PATCH_MEMBER_ADDED("data", TYPE_TUPLE_INT, HK_NULL, 6)
	HK_PATCH_MEMBER_ADDED("extras", TYPE_TUPLE_INT, HK_NULL, 2)
HK_PATCH_END()

HK_PATCH_BEGIN("hkxVertexDescriptionElementDecl", 1, "hkxVertexDescriptionElementDecl", 2)
	HK_PATCH_MEMBER_ADDED("numElements", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_FUNCTION(hkxVertexDescriptionElementDecl_1_to_2)
HK_PATCH_END()

// Required by some cloth operators
HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkPackedVector3", 0)
	HK_PATCH_MEMBER_ADDED("values", TYPE_TUPLE_INT, HK_NULL, 4)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkQTransform", 0)
	HK_PATCH_MEMBER_ADDED_VEC_4_IDENTITY("rotation")
	HK_PATCH_MEMBER_ADDED_VEC_4("translation", 0,0,0,0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkPostFinishAttribute", 0)
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
