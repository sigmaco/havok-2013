/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Destruction specific product patches applied to release 660.
// This file is #included by hkdPatches_660.cpp

HK_PATCH_BEGIN("hkdMeshSimplifierAction", 0, "hkdMeshSimplifierAction", 1)
	HK_PATCH_MEMBER_REMOVED("maxNumberOfVertices", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("minNumberOfVerticesPerShape", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED_INT("maxNumberOfTriangles", 1000)
	HK_PATCH_MEMBER_ADDED_INT("minNumberOfTrianglesPerShape", 4)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdMeshSimplifierAction", 1, "hkdMeshSimplifierAction", 2)
	HK_PATCH_MEMBER_ADDED_BYTE("allowRootShapeSimplification", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdVoronoiFracture", 1, "hkdVoronoiFracture", 2)
	HK_PATCH_MEMBER_ADDED_INT("seed", 180673)
	HK_PATCH_MEMBER_ADDED_INT("numPointsToGenerate", 0)
	HK_PATCH_MEMBER_ADDED_INT("numIterations", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdRaycastGun", 0, "hkdRaycastGun", 1)
	// forceRadius was not used before so safe to just ignore
	HK_PATCH_MEMBER_REMOVED("forceRadius", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED_REAL("beamRadius", 0.1f)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkdControllerSmallArraySerializeOverrideType", 0)
	HK_PATCH_MEMBER_ADDED("data", TYPE_OBJECT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("size", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("capacityAndFlags", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkdIntegrityAnalyzerAction", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkdAction")
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkdAction", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkdMeshSimplifierAction", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkdAction")
	HK_PATCH_MEMBER_ADDED("maxNumberOfVertices", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED_REAL("preferChildSimplification", 0.000000f)
	HK_PATCH_MEMBER_ADDED("minNumberOfVerticesPerShape", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED_BYTE("allowRemovingShapes", 0)
	HK_PATCH_MEMBER_ADDED_BYTE("avoidGaps", 1)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkdAction", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdIntegrityAnalyzerAction", 0, "hkdIntegrityAnalyzerAction", 1)
	HK_PATCH_MEMBER_ADDED_REAL("breakingLength", 8.0f)
	HK_PATCH_MEMBER_ADDED_REAL("fracturePosition", 0.4f)
	HK_PATCH_MEMBER_ADDED_REAL("destructionRadius", 0.000000f)
	HK_PATCH_MEMBER_ADDED_REAL("delay", 0.000000f)
	HK_PATCH_MEMBER_ADDED_REAL("refineRadius", 0.000000f)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdDestructionDemoConfig", 3, "hkdDestructionDemoConfig", 4)
	HK_PATCH_MEMBER_ADDED_REAL("simplyfierPercentToRemove", 0.000000f)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkdShareVerticesAction", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkdAction")
	HK_PATCH_MEMBER_ADDED_INT("maxNumVerticesPerBuffer", 65535)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkdAction", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdBreakableBodySmallArraySerializeOverrideType", 0, "hkdBreakableBodySmallArraySerializeOverrideType", 1)
	HK_PATCH_MEMBER_REMOVED("data", TYPE_OBJECT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdControllerSmallArraySerializeOverrideType", 0, "hkdControllerSmallArraySerializeOverrideType", 1)
	HK_PATCH_MEMBER_REMOVED("data", TYPE_OBJECT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdBreakableShapeContactArea", 0, "hkdBreakableShapeContactArea", 1)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
HK_PATCH_END()

HK_PATCH_BEGIN("hkdDestructionDemoConfig", 4, "hkdDestructionDemoConfig", 5)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
HK_PATCH_END()

HK_PATCH_BEGIN("hkdFracture", 1, "hkdFracture", 2)
	HK_PATCH_MEMBER_REMOVED("connectivityType", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdBreakableShape", 1, "hkdBreakableShape", 2)
	HK_PATCH_MEMBER_REMOVED("parent", TYPE_OBJECT, "hkdBreakableShape", 0)
	HK_PATCH_MEMBER_ADDED("parent", TYPE_VOID, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdGeometry", 0, "hkdGeometry", 1)
	HK_PATCH_MEMBER_REMOVED("parent", TYPE_OBJECT, "hkdGeometry", 0)
	HK_PATCH_MEMBER_ADDED("parent", TYPE_VOID, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdCompoundBreakableShape", 0, "hkdCompoundBreakableShape", 1)
	HK_PATCH_MEMBER_REMOVED("rootBreakableShape", TYPE_OBJECT, "hkdBreakableShape", 0)
	HK_PATCH_MEMBER_ADDED("rootBreakableShape", TYPE_VOID, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdSetRigidBodyPropertiesAction", 0, "hkdSetRigidBodyPropertiesAction", 1)
	HK_PATCH_MEMBER_ADDED_REAL("gravityFactor", 1.0f)
	HK_PATCH_MEMBER_ADDED_REAL("friction", 1.0f)
	HK_PATCH_MEMBER_ADDED_REAL("restitution", 0.000000f)
	HK_PATCH_MEMBER_ADDED_BYTE("setDeactivation", 0)
	HK_PATCH_MEMBER_ADDED_BOOL("enableDeactivation", true)
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
