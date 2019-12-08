/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Destruction specific product patches applied to release 2010_1.
// This file is #included by hkdPatches_2010_1.cpp

HK_PATCH_BEGIN("hkdVoronoiFracture", 3, "hkdVoronoiFracture", 4)
	HK_PATCH_MEMBER_REMOVED("pivots", TYPE_ARRAY_VEC_4, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdRandomSplitFracture", 0, "hkdRandomSplitFracture", 1)
	HK_PATCH_MEMBER_ADDED_INT("randomSeed1", 123)
	HK_PATCH_MEMBER_ADDED_INT("randomSeed2", 456)
	HK_PATCH_MEMBER_ADDED_INT("randomSeed3", 789)
	HK_PATCH_MEMBER_ADDED_INT("randomSeed4", 101112)
	HK_PATCH_MEMBER_ADDED_REAL("randomRange", 1.000000f)
	HK_PATCH_FUNCTION(hkdRandomSplitFracture_0_to_1)
	HK_PATCH_MEMBER_REMOVED("randomSeed", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdDecorateFractureFaceAction", 4, "hkdDecorateFractureFaceAction", 5)
	HK_PATCH_MEMBER_ADDED_REAL("linearTolerance", 0.000100f)
	HK_PATCH_MEMBER_ADDED_REAL("angularTolerance", 0.000100f)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkdDeformableBreakableShapeSkinShapeSection", 0)
	HK_PATCH_MEMBER_ADDED("indexBuffer", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("boneIndices", TYPE_ARRAY_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkdDeformableBreakableShapeSkinShapeSectionInstance", 0)
	HK_PATCH_MEMBER_ADDED("key", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("shape", TYPE_OBJECT, "hkpShape", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkpShape", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkdDeformableBreakableShapeBoneDeformationData", 0)
	HK_PATCH_MEMBER_ADDED("weight", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("index", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkdDeformableBreakableShapeBoneInfo", 0)
	HK_PATCH_MEMBER_ADDED("modelSpaceBindPoseTransform", TYPE_STRUCT, "hkQTransform", 0)
	HK_PATCH_MEMBER_ADDED("softness", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkQTransform", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkdDeformableBreakableShapePhysicsSkinShape", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("bones", TYPE_ARRAY_STRUCT, "hkdDeformableBreakableShapeBoneInfo", 0)
	HK_PATCH_MEMBER_ADDED("vertices", TYPE_ARRAY_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("deformationData", TYPE_ARRAY_STRUCT, "hkdDeformableBreakableShapeBoneDeformationData", 0)
	HK_PATCH_MEMBER_ADDED("sections", TYPE_ARRAY_OBJECT, "hkdDeformableBreakableShapeSkinShapeSection", 0)
	HK_PATCH_DEPENDS("hkQTransform", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkdDeformableBreakableShapeBoneInfo", 0)
	HK_PATCH_DEPENDS("hkdDeformableBreakableShapeSkinShapeSection", 0)
	HK_PATCH_DEPENDS("hkdDeformableBreakableShapeBoneDeformationData", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkdDeformableBreakableShapePhysicsSkinInstance", 0)
	HK_PATCH_PARENT_SET("hkReferencedObject", "hkpShapeModifier")
	HK_PATCH_MEMBER_ADDED("modelSpaceBoneTransforms", TYPE_ARRAY_STRUCT, "hkQTransform", 0)
	HK_PATCH_MEMBER_ADDED("physicsShape", TYPE_OBJECT, "hkpShape", 0)
	HK_PATCH_MEMBER_ADDED("skinShape", TYPE_OBJECT, "hkdDeformableBreakableShapePhysicsSkinShape", 0)
	HK_PATCH_MEMBER_ADDED("vertices", TYPE_ARRAY_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("sections", TYPE_ARRAY_STRUCT, "hkdDeformableBreakableShapeSkinShapeSectionInstance", 0)
	HK_PATCH_DEPENDS("hkQTransform", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkpShape", 0)
	HK_PATCH_DEPENDS("hkpShapeModifier", 0)
	HK_PATCH_DEPENDS("hkdDeformableBreakableShapePhysicsSkinShape", 0)
	HK_PATCH_DEPENDS("hkdDeformableBreakableShapeSkinShapeSectionInstance", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdDeformableBreakableBodyMemento", 0, "hkdDeformableBreakableBodyMemento", 1)
	HK_PATCH_MEMBER_REMOVED("shapeIndices", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("transforms", TYPE_ARRAY_VEC_16, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("transforms", TYPE_ARRAY_STRUCT, "hkQTransform", 0)
	HK_PATCH_DEPENDS("hkQTransform", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdDeformableBreakableShape", 2, "hkdDeformableBreakableShape", 3)
	HK_PATCH_MEMBER_REMOVED("childKeys", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("origChildTransformRotations", TYPE_ARRAY_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("origChildTransformTranslations", TYPE_ARRAY_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("physicsSkinShape", TYPE_OBJECT, "hkdDeformableBreakableShapePhysicsSkinShape", 0)
	HK_PATCH_DEPENDS("hkdDeformableBreakableShapePhysicsSkinShape", 0)
	//HK_PATCH_FUNCTION(hkdDeformableBreakableShape_2_to_3)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdDeformationController", 2, "hkdDeformationController", 3)
	HK_PATCH_MEMBER_ADDED_REAL("constraintStrength", 0.000000f)
	HK_PATCH_MEMBER_ADDED_REAL("constraintBreakingLimit", 0.000000f)
	HK_PATCH_MEMBER_ADDED_REAL("maxDeformationAngle", 90.000000f)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdShapeInstanceInfo", 3, "hkdShapeInstanceInfo", 4)
	HK_PATCH_MEMBER_ADDED("transform", TYPE_STRUCT, "hkQTransform", 0)
	HK_PATCH_FUNCTION(hkdShapeInstanceInfo_3_to_4)
	HK_PATCH_MEMBER_REMOVED("translation", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("rotation", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkQTransform", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdExplosionForceAction", 0, "hkdExplosionForceAction", 1)
	HK_PATCH_MEMBER_ADDED_BYTE("explosionCenterSpace", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdDecorateFractureFaceAction", 5, "hkdDecorateFractureFaceAction", 6)
	HK_PATCH_MEMBER_ADDED_INT("numCornerDecorationAttempts", -1)
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
