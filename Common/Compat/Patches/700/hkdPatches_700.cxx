/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Destruction specific product patches applied to release 700.
// This file is #included by hkdPatches_700.cpp

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkdSplitInHalfController", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkdController")
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkdController", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkdBuildingController", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkdController")
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkdController", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkdDecorateFractureFaceActionDecorationPlacement", 0)
	HK_PATCH_MEMBER_ADDED("position", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("rotation", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("graphicsSource", TYPE_OBJECT, "hkdBreakableShape", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkdBreakableShape", 2)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkdDecorateFractureFaceActionConnectionDecorationInfo", 0)
	HK_PATCH_MEMBER_ADDED("owningAction", TYPE_OBJECT, "hkdAction", 0)
	HK_PATCH_MEMBER_ADDED("otherShape", TYPE_OBJECT, "hkdBreakableShape", 0)
	HK_PATCH_MEMBER_ADDED("decorations", TYPE_ARRAY_STRUCT, "hkdDecorateFractureFaceActionDecorationPlacement", 0)
	HK_PATCH_DEPENDS("hkdDecorateFractureFaceActionDecorationPlacement", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkdAction", 0)
	HK_PATCH_DEPENDS("hkdBreakableShape", 2)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkdObjectPropertiesProperty", 0)
	HK_PATCH_MEMBER_ADDED("key", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("object", TYPE_OBJECT, "hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkdObjectProperties", 0)
	HK_PATCH_MEMBER_ADDED("properties", TYPE_ARRAY_STRUCT, "hkdObjectPropertiesProperty", 0)
	HK_PATCH_DEPENDS("hkdObjectPropertiesProperty", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkdDecorateFractureFaceActionShapeDecorationInfo", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("connectionDecorations", TYPE_ARRAY_OBJECT, "hkdDecorateFractureFaceActionConnectionDecorationInfo", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkdDecorateFractureFaceActionConnectionDecorationInfo", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdBreakableShape", 2, "hkdBreakableShape", 3)
	HK_PATCH_MEMBER_ADDED("objectProperties", TYPE_STRUCT, "hkdObjectProperties", 0)
	HK_PATCH_DEPENDS("hkdObjectProperties", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdShapeInstanceInfo", 0, "hkdShapeInstanceInfo", 1)
	HK_PATCH_MEMBER_ADDED("tempControllerData", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdDecorateFractureFaceAction", 1, "hkdDecorateFractureFaceAction", 2)
	HK_PATCH_MEMBER_REMOVED("frontDir", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("right", TYPE_STRUCT, "hkdDecorateFractureFaceActionFractureFaceInfo", 0)
	HK_PATCH_MEMBER_REMOVED("left", TYPE_STRUCT, "hkdDecorateFractureFaceActionFractureFaceInfo", 0)
	HK_PATCH_MEMBER_ADDED_REAL("minFractureLength", 0.1f)
	HK_PATCH_MEMBER_ADDED_BYTE("decorateWhat", 0)
	HK_PATCH_MEMBER_ADDED_BYTE("alignDecorations", 0)
	HK_PATCH_MEMBER_ADDED("frontDirPolicy", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("controlShapes", TYPE_OBJECT, "hkdBreakableShape", 0)
	HK_PATCH_MEMBER_ADDED_VEC_4("frontDirection", 1.0f, 0.0f, 0.0f, 0.0f)
	HK_PATCH_MEMBER_ADDED_VEC_16_IDENTITY("controlShapesTransform")
	HK_PATCH_MEMBER_ADDED("side", TYPE_STRUCT, "hkdDecorateFractureFaceActionFractureFaceInfo", 0)
	HK_PATCH_MEMBER_ADDED("flat", TYPE_STRUCT, "hkdDecorateFractureFaceActionFractureFaceInfo", 0)
	HK_PATCH_DEPENDS("hkdDecorateFractureFaceActionFractureFaceInfo", 0)
	HK_PATCH_DEPENDS("hkdBreakableShape", 3)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkdBreakableBodyShapeKeyToChild", 0)
	HK_PATCH_MEMBER_ADDED("keys", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("child", TYPE_OBJECT, "hkdBreakableShape", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkdBreakableShape", 3)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdBreakableBody", 1, "hkdBreakableBody", 2)
	HK_PATCH_MEMBER_ADDED("shapeKeyToChild", TYPE_ARRAY_OBJECT, "hkdBreakableBodyShapeKeyToChild", 0)
	HK_PATCH_DEPENDS("hkdBreakableBodyShapeKeyToChild", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdBody", 2, "hkdBody", 3)
	HK_PATCH_MEMBER_ADDED_BYTE("bodyType", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdBreakableBody", 2, "hkdBreakableBody", 3)
	HK_PATCH_MEMBER_ADDED("bodyType", TYPE_BYTE, HK_NULL, 0)
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
