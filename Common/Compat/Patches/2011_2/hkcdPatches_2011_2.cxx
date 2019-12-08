/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Collide specific product patches applied to release 2011_2.
// This file is #included by hkcdPatches_2011_2.cpp

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdShapeDispatchType", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdShapeInfoCodecType", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdShapeType", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdShape", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("dispatchType", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("bitsPerKey", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("shapeInfoCodecType", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkcdShapeDispatchType", 0)
	HK_PATCH_DEPENDS("hkcdShapeInfoCodecType", 0)
	HK_PATCH_DEPENDS("hkcdShapeType", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkcdStaticMeshTreeBaseSection", 1, "hkcdStaticMeshTreeBaseSection", 2)
	HK_PATCH_MEMBER_REMOVED("unusedData", TYPE_TUPLE_BYTE, HK_NULL, 3)
	HK_PATCH_MEMBER_ADDED("unusedData", TYPE_TUPLE_BYTE, HK_NULL, 2)
	HK_PATCH_MEMBER_ADDED("flags", TYPE_BYTE, HK_NULL, 0)	
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
