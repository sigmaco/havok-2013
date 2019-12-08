/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Destruction specific product patches applied to release 2011_3.
// This file is #included by hkdPatches_2011_3.cpp

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkdSplitByPhysicsIslandsAction", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkdAction")
	HK_PATCH_MEMBER_ADDED_BYTE("splitMethod", 0)
	HK_PATCH_MEMBER_ADDED_REAL("distanceForConnection", 0.050000f)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkdAction", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkdStringArrayObject", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("strings", TYPE_ARRAY_CSTRING, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkdScriptedFracture", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkdFracture")
	HK_PATCH_MEMBER_ADDED("scriptPath", TYPE_CSTRING, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("attributes", TYPE_ARRAY_STRUCT, "hkxAttribute", 0)
	HK_PATCH_DEPENDS("hkdFracture", 2)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkxAttribute", 1)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkdSplitByPhysicsIslandsMethod", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdConvexDecompositionAction", 1, "hkdConvexDecompositionAction", 2)
	HK_PATCH_MEMBER_ADDED_BYTE("splitMethod", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdMeshSimplifierAction", 5, "hkdMeshSimplifierAction", 6)
	HK_PATCH_MEMBER_ADDED_BYTE("allowNonManifoldGeom", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkdFlattenHierarchyAction", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkdAction")
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkdAction", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdConvexDecompositionAction", 2, "hkdConvexDecompositionAction", 3)
	HK_PATCH_MEMBER_ADDED_REAL("minVolume", 0.000010f)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdDestructionDemoConfig", 5, "hkdDestructionDemoConfig", 6)
	HK_PATCH_MEMBER_ADDED_BYTE("keepSkinningData", 1)
	HK_PATCH_MEMBER_ADDED_BYTE("enableHwSkinning", 0)
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
