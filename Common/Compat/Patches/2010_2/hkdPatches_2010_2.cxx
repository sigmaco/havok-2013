/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Destruction specific product patches applied to release 2010_2.
// This file is #included by hkdPatches_2010_2.cpp

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkdTransformObject", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("transform", TYPE_VEC_16, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdDebrisFracture", 1, "hkdDebrisFracture", 2)
	HK_PATCH_MEMBER_ADDED("controlShapes", TYPE_OBJECT, "hkdBreakableShape", 0)
	HK_PATCH_MEMBER_ADDED("controlShapesTransform", TYPE_VEC_16, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED_BYTE("positionSource", 1)
	HK_PATCH_DEPENDS("hkdBreakableShape", 5)
	//HK_PATCH_FUNCTION(hkdDebrisFracture_1_to_2)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkdDebrisFractureInfoTemplateInfo", 0)
	HK_PATCH_MEMBER_ADDED("templateDebris", TYPE_OBJECT, "hkdBreakableShape", 0)
	HK_PATCH_MEMBER_ADDED_REAL("density", 1.000000f)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkdBreakableShape", 5)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkdDebrisFractureInfo", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkdInfo")
	HK_PATCH_MEMBER_ADDED("info0", TYPE_STRUCT, "hkdDebrisFractureInfoTemplateInfo", 0)
	HK_PATCH_MEMBER_ADDED("info1", TYPE_STRUCT, "hkdDebrisFractureInfoTemplateInfo", 0)
	HK_PATCH_MEMBER_ADDED("info2", TYPE_STRUCT, "hkdDebrisFractureInfoTemplateInfo", 0)
	HK_PATCH_DEPENDS("hkdDebrisFractureInfoTemplateInfo", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkdInfo", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdDecorateFractureFaceActionFractureFaceInfo", 1, "hkdDecorateFractureFaceActionFractureFaceInfo", 2)
	HK_PATCH_MEMBER_ADDED_REAL("randomSpinAngle", 0.000000f)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdCutOutFracture", 1, "hkdCutOutFracture", 2)
	HK_PATCH_MEMBER_ADDED_REAL("minimumOverlap", 0.050000f)
HK_PATCH_END()

// Tuple/Tuple type 

HK_PATCH_BEGIN("hkdDeformableBreakableShapePhysicsSkinShape", 0, "hkdDeformableBreakableShapePhysicsSkinShape", 1)
	HK_PATCH_MEMBER_RENAMED("sections", "old_sections")
	HK_PATCH_MEMBER_ADDED("sections",  TYPE_ARRAY_STRUCT, "hkdDeformableBreakableShapeSkinShapeSection", 0)
	HK_PATCH_FUNCTION(hkdDeformableBreakableShapePhysicsSkinShape_0_to_1)
	HK_PATCH_MEMBER_REMOVED("old_sections", TYPE_ARRAY_OBJECT, "hkdDeformableBreakableShapeSkinShapeSection", 0)
HK_PATCH_END()


HK_PATCH_BEGIN("hkdDecorateFractureFaceActionShapeDecorationInfo", 1, "hkdDecorateFractureFaceActionShapeDecorationInfo", 2)
	HK_PATCH_MEMBER_RENAMED("connectionDecorations", "old_connectionDecorations")
	HK_PATCH_MEMBER_ADDED("connectionDecorations",  TYPE_ARRAY_STRUCT, "hkdDecorateFractureFaceActionConnectionDecorationInfo", 0)
	
	HK_PATCH_FUNCTION(hkdDecorateFractureFaceActionShapeDecorationInfo_1_to_2)

	HK_PATCH_MEMBER_REMOVED("old_connectionDecorations", TYPE_ARRAY_OBJECT, "hkdDecorateFractureFaceActionConnectionDecorationInfo", 0)
HK_PATCH_END()


HK_PATCH_BEGIN("hkdDecalMapActionDecalMapData", 0, "hkdDecalMapActionDecalMapData", 1)
	HK_PATCH_MEMBER_RENAMED("decals", "old_decals")
	HK_PATCH_MEMBER_ADDED("decals",  TYPE_ARRAY_STRUCT, "hkdDecalMapActionDecalMap", 0)

	HK_PATCH_MEMBER_RENAMED("decors", "old_decors")
	HK_PATCH_MEMBER_ADDED("decors",  TYPE_ARRAY_STRUCT, "hkdDecalMapActionDecalMap", 0)

	HK_PATCH_MEMBER_RENAMED("decorInfo", "old_decorInfo")
	HK_PATCH_MEMBER_ADDED("decorInfo",  TYPE_ARRAY_STRUCT, "hkdDecalMapActionDecorMapInfo", 0)

	HK_PATCH_FUNCTION(hkdDecalMapActionDecalMapData_0_to_1)

	HK_PATCH_MEMBER_REMOVED("old_decals", TYPE_ARRAY_OBJECT, "hkdDecalMapActionDecalMap", 0)
	HK_PATCH_MEMBER_REMOVED("old_decors", TYPE_ARRAY_OBJECT, "hkdDecalMapActionDecalMap", 0)
	HK_PATCH_MEMBER_REMOVED("old_decorInfo", TYPE_ARRAY_OBJECT, "hkdDecalMapActionDecorMapInfo", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdBreakableBodyShapeKeyToChildMap", 0, "hkdBreakableBodyShapeKeyToChildMap", 1)
	HK_PATCH_MEMBER_RENAMED("shapeKeyToChild", "old_shapeKeyToChild")
	HK_PATCH_MEMBER_ADDED("shapeKeyToChild",  TYPE_ARRAY_STRUCT, "hkdBreakableBodyShapeKeyToChild", 0)
	HK_PATCH_FUNCTION(hkdBreakableBodyShapeKeyToChildMap_0_to_1)
	HK_PATCH_MEMBER_REMOVED("old_shapeKeyToChild", TYPE_ARRAY_OBJECT, "hkdBreakableBodyShapeKeyToChild", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdMeshSimplifierAction", 2, "hkdMeshSimplifierAction", 3)
	HK_PATCH_MEMBER_ADDED_BYTE("enableCoplanarMerge", 0)
	HK_PATCH_MEMBER_ADDED_REAL("maxCoplanarError", 0.000001f)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdDeformationController", 3, "hkdDeformationController", 4)
	HK_PATCH_MEMBER_ADDED_REAL("hullTolerance", 0.001000f)
	HK_PATCH_MEMBER_ADDED_REAL("shapeWeldingTolerance", 0.010000f)
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
