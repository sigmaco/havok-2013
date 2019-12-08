/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Destruction specific product patches applied to release 2011_1.
// This file is #included by hkdPatches_2011_1.cpp

HK_PATCH_BEGIN("hkdShockWaveAction", 0, "hkdShockWaveAction", 1)
	HK_PATCH_MEMBER_ADDED_BYTE("triggerType", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdDecorateFractureFaceActionFractureFaceInfo", 2, "hkdDecorateFractureFaceActionFractureFaceInfo", 3)
	HK_PATCH_MEMBER_ADDED_BYTE("allowRandomFlipX", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdDecorateFractureFaceActionConnectionDecorationInfo", 1, "hkdDecorateFractureFaceActionConnectionDecorationInfo", 2)
	HK_PATCH_MEMBER_REMOVED("placements", TYPE_ARRAY_STRUCT, "hkdDecorateFractureFaceActionDecorationPlacement", 0)
	HK_PATCH_MEMBER_REMOVED("boxIndices", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("compressedPlacements", TYPE_ARRAY_STRUCT, "hkdDecorateFractureFaceActionCompressedDecorationPlacement", 0)
	HK_PATCH_MEMBER_ADDED("startIndex", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("numDecorations", TYPE_INT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkdDecorateFractureFaceActionCompressedDecorationPlacement", 0)
	//HK_PATCH_FUNCTION(hkdDecorateFractureFaceActionConnectionDecorationInfo_1_to_2)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdDecorateFractureFaceActionCompressedDecorationPlacement", 0, "hkdDecorateFractureFaceActionCompressedDecorationPlacement", 1)
	HK_PATCH_MEMBER_REMOVED("graphicsIdx", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("boundingBoxIdx", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdDecorateFractureFaceActionDecorationPlacement", 1, HK_NULL, HK_CLASS_REMOVED)
	HK_PATCH_MEMBER_REMOVED("pos", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("rot", TYPE_VEC_4, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdDecorateFractureFaceActionGlobalDecorationData", 0, "hkdDecorateFractureFaceActionGlobalDecorationData", 1)
	HK_PATCH_MEMBER_ADDED("rawTransforms", TYPE_ARRAY_STRUCT, "hkQTransform", 0)
	HK_PATCH_MEMBER_ADDED("compressedPlacements", TYPE_ARRAY_STRUCT, "hkdDecorateFractureFaceActionCompressedDecorationPlacement", 0)
	HK_PATCH_MEMBER_ADDED("indexBuffer", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("graphicsRanges", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkdDecorateFractureFaceActionCompressedDecorationPlacement", 0)
	HK_PATCH_DEPENDS("hkQTransform", 0)
	//HK_PATCH_FUNCTION(hkdDecorateFractureFaceActionGlobalDecorationData_0_to_1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdDecorateFractureFaceAction", 6, "hkdDecorateFractureFaceAction", 7)
	HK_PATCH_MEMBER_ADDED_BYTE("forceBorderOnEdges", 0)
	HK_PATCH_MEMBER_ADDED_REAL("maxAngleBetweenEdges", 6.283185f)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdDecorateFractureFaceAction", 7, "hkdDecorateFractureFaceAction", 8)
	HK_PATCH_MEMBER_ADDED_BYTE("keepFixedDecorations", 1)
	HK_PATCH_MEMBER_REMOVED("compressDecorations", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED_BYTE("decorationsStorage", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdBreakableShape", 5, "hkdBreakableShape", 6)
	HK_PATCH_DEPENDS("hkHalf8", 2)
	HK_PATCH_DEPENDS("hkpShape", 0)
	HK_PATCH_DEPENDS("hkpBreakableMaterial", 0)
	HK_PATCH_DEPENDS("hkpSimpleBreakableMaterial", 0)
	HK_PATCH_MEMBER_RENAMED("physicsShape", "oldPhysicsShape")
	HK_PATCH_PARENT_SET("hkReferencedObject", "hkpBreakableShape")
	HK_PATCH_DEPENDS("hkpBreakableShape", 0)
	HK_PATCH_MEMBER_ADDED("temp_inertiaAndValues", TYPE_VEC_8, HK_NULL, 0)
	HK_PATCH_FUNCTION(hkdBreakableShape_5_to_6)
	HK_PATCH_MEMBER_REMOVED("oldPhysicsShape", TYPE_OBJECT, "hkpShape", 0)
	HK_PATCH_MEMBER_REMOVED("strength", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("inertiaAndValues", TYPE_OBJECT, HK_NULL, 0)
	HK_PATCH_MEMBER_RENAMED("temp_inertiaAndValues", "inertiaAndValues")
HK_PATCH_END()

HK_PATCH_BEGIN("hkdDeformableBreakableShapePhysicsSkinInstance", 0, "hkdDeformableBreakableShapePhysicsSkinInstance", 1)
	HK_PATCH_MEMBER_ADDED("deformableCompound", TYPE_OBJECT, "hkpBreakableShape", 0)
	HK_PATCH_FUNCTION(hkdDeformableBreakableShapePhysicsSkinInstance_0_to_1)
	HK_PATCH_MEMBER_REMOVED("physicsShape", TYPE_OBJECT, "hkpShape", 0)
	HK_PATCH_MEMBER_REMOVED("sections", TYPE_ARRAY_STRUCT, "hkdDeformableBreakableShapeSkinShapeSectionInstance", 0)
	HK_PATCH_DEPENDS("hkpShape", 0)
	HK_PATCH_DEPENDS("hkpBreakableShape", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdDeformableBreakableShapeSkinShapeSectionInstance", 0, HK_NULL, HK_CLASS_REMOVED)
	HK_PATCH_MEMBER_REMOVED("key", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("shape", TYPE_OBJECT, "hkpShape", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkpShape", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkdDeformableBreakableShapeDeformationProperty", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("sectionIndex", TYPE_INT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdBuildingController", 0, "hkdBuildingController", 1)
	HK_PATCH_MEMBER_ADDED_BYTE("physicsShapeType", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdBreakableBody", 5, "hkdBreakableBody", 6)
	HK_PATCH_MEMBER_RENAMED("controller", "oldController")
	HK_PATCH_MEMBER_RENAMED("breakableShape", "oldBreakableShape")
	HK_PATCH_MEMBER_RENAMED("constraintStrength", "oldConstraintStrength")
	HK_PATCH_MEMBER_RENAMED("bodyTypeAndFlags", "oldBodyTypeAndFlags")
	HK_PATCH_DEPENDS("hkdController", 0)
	HK_PATCH_DEPENDS("hkpBreakableBody", 0)
	//HK_PATCH_FUNCTION(hkdBreakableBody_5_to_6)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdController", 0, "hkdController", 1)
	HK_PATCH_DEPENDS("hkpBreakableBodyController", 0)
	HK_PATCH_PARENT_SET("hkReferencedObject", "hkpBreakableBodyController")
HK_PATCH_END()

HK_PATCH_BEGIN("hkdBreakableBody", 6, "hkdBreakableBody", 7)
	HK_PATCH_DEPENDS("hkpBreakableBody", 1)
	HK_PATCH_FUNCTION(hkdBreakableBody_6_to_7)
	HK_PATCH_MEMBER_REMOVED("oldController", TYPE_OBJECT, "hkdController", 0)
	HK_PATCH_MEMBER_REMOVED("oldBreakableShape", TYPE_OBJECT, "hkdBreakableShape", 0)
	HK_PATCH_MEMBER_REMOVED("oldConstraintStrength", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("oldBodyTypeAndFlags", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdDeformationController", 4, "hkdDeformationController", 5)
	HK_PATCH_MEMBER_RENAMED("strength", "deformationStrength")
HK_PATCH_END()

HK_PATCH_BEGIN("hkdBreakableBodyShapeKeyToChild", 0, HK_NULL, HK_CLASS_REMOVED)
	HK_PATCH_MEMBER_REMOVED("keys", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("child", TYPE_OBJECT, "hkdBreakableShape", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkpBreakableShape", 0)
	HK_PATCH_DEPENDS("hkdBreakableShape", 6)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdBreakableBodyShapeKeyToChildMap", 1, HK_NULL, HK_CLASS_REMOVED)
	HK_PATCH_PARENT_SET("hkReferencedObject", HK_NULL)
	HK_PATCH_MEMBER_REMOVED("shapeKeyToChild", TYPE_ARRAY_STRUCT, "hkdBreakableBodyShapeKeyToChild", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkdBreakableBodyShapeKeyToChild", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdDeformableBreakableShapePhysicsSkinInstance", 1, "hkdDeformableBreakableShapePhysicsSkinInstance", 2)
	HK_PATCH_DEPENDS("hkpShapeModifier", 0)
	HK_PATCH_PARENT_SET("hkpShapeModifier", "hkReferencedObject")
	HK_PATCH_MEMBER_REMOVED("deformableCompound", TYPE_OBJECT, "hkpBreakableShape", 0)
	HK_PATCH_DEPENDS("hkpBreakableShape", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	//HK_PATCH_FUNCTION(hkdDeformableBreakableShapePhysicsSkinInstance_1_to_2)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdDeformableBreakableShapeBoneInfo", 0, "hkdDeformableBreakableShapeBoneInfo", 1)
	HK_PATCH_MEMBER_ADDED("comAndSoftness", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_FUNCTION(hkdDeformableBreakableShapeBoneInfo_0_to_1)
	HK_PATCH_MEMBER_REMOVED("softness", TYPE_REAL, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdDecorateFractureFaceActionGlobalDecorationData", 1, "hkdDecorateFractureFaceActionGlobalDecorationData", 2)
	HK_PATCH_MEMBER_ADDED("halfTransforms", TYPE_ARRAY_STRUCT, "hkFloat16Transform", 0)
	HK_PATCH_DEPENDS("hkFloat16Transform", 0)
	//HK_PATCH_FUNCTION(hkdDecorateFractureFaceActionGlobalDecorationData_1_to_2)
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
