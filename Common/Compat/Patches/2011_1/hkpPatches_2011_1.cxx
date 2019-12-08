/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Physics specific product patches applied to release 2011_1.
// This file is #included by hkpPatches_2011_1.cpp

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpBreakableBodyController", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED_REAL("breakingImpulse", -1.000000f)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpBreakableMaterial", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("strength", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("typeAndFlags", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("properties", TYPE_OBJECT, "hkRefCountedProperties", 0)
	HK_PATCH_DEPENDS("hkRefCountedProperties", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpSimpleBreakableMaterial", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkpBreakableMaterial")
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkpBreakableMaterial", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpBreakableMultiMaterialInverseMappingDescriptor", 0)
	HK_PATCH_MEMBER_ADDED("offset", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("numKeys", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpBreakableMultiMaterialInverseMapping", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("descriptors", TYPE_ARRAY_STRUCT, "hkpBreakableMultiMaterialInverseMappingDescriptor", 0)
	HK_PATCH_MEMBER_ADDED("subShapeIds", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkpBreakableMultiMaterialInverseMappingDescriptor", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpBreakableMultiMaterial", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkpBreakableMaterial")
	HK_PATCH_MEMBER_ADDED("subMaterials", TYPE_ARRAY_OBJECT, "hkpBreakableMaterial", 0)
	HK_PATCH_MEMBER_ADDED("inverseMapping", TYPE_OBJECT, "hkpBreakableMultiMaterialInverseMapping", 0)
	HK_PATCH_DEPENDS("hkpBreakableMultiMaterialInverseMapping", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkpBreakableMaterial", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpListShapeBreakableMaterial", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkpBreakableMultiMaterial")
	HK_PATCH_DEPENDS("hkpBreakableMaterial", 0)
	HK_PATCH_DEPENDS("hkpBreakableMultiMaterial", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpExtendedMeshShapeBreakableMaterial", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkpBreakableMultiMaterial")
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkpBreakableMaterial", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkpBreakableMultiMaterial", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpStaticCompoundShapeBreakableMaterial", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkpBreakableMultiMaterial")
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkpBreakableMaterial", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkpBreakableMultiMaterial", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpBreakableShape", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("physicsShape", TYPE_OBJECT, "hkpShape", 0)
	HK_PATCH_MEMBER_ADDED("material", TYPE_OBJECT, "hkpBreakableMaterial", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkpShape", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkpBreakableMaterial", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpBreakableBody", 0, "hkpBreakableBody", 1)
	HK_PATCH_MEMBER_ADDED("controller", TYPE_OBJECT, "hkpBreakableBodyController", 0)
	HK_PATCH_MEMBER_ADDED("breakableShape", TYPE_OBJECT, "hkpBreakableShape", 0)
	HK_PATCH_MEMBER_ADDED_BYTE("bodyTypeAndFlags", 0)
	HK_PATCH_MEMBER_ADDED_REAL("constraintStrength", 0)
	HK_PATCH_DEPENDS("hkpBreakableShape", 0)
	HK_PATCH_DEPENDS("hkpBreakableBodyController", 0)
	//HK_PATCH_FUNCTION(hkpBreakableBody_0_to_1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpShapeModifier", 0, HK_NULL, HK_CLASS_REMOVED)
	HK_PATCH_PARENT_SET("hkReferencedObject", HK_NULL)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpExtendedMeshShapeSubpart", 2, "hkpExtendedMeshShapeSubpart", 3)
	HK_PATCH_MEMBER_ADDED("typeAndFlags", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("shapeInfo", TYPE_INT, HK_NULL, 0)
	HK_PATCH_FUNCTION(hkpExtendedMeshShapeSubpart_2_to_3)
	HK_PATCH_MEMBER_REMOVED("type", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("materialIndexStridingType", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("numMaterials", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpListShapeChildInfo", 0, "hkpListShapeChildInfo", 1)
	HK_PATCH_MEMBER_ADDED("shapeInfo", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpBvTreeShape", 0, "hkpBvTreeShape", 1)
	HK_PATCH_MEMBER_DEFAULT_SET_INT("bvTreeType", 4)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpConvexTransformShape", 0, "hkpConvexTransformShape", 1)
	HK_PATCH_MEMBER_ADDED("newTransform", TYPE_VEC_12, HK_NULL, 0)
	HK_PATCH_FUNCTION(hkpConvexTransformShape_0_to_1)
	HK_PATCH_MEMBER_REMOVED("transform", TYPE_VEC_16, HK_NULL, 0)
	HK_PATCH_MEMBER_RENAMED("newTransform", "transform")
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpStaticCompoundShapeInstance", 0)
	HK_PATCH_MEMBER_ADDED("transform", TYPE_VEC_12, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("shape", TYPE_OBJECT, "hkpShape", 0)
	HK_PATCH_MEMBER_ADDED("filterInfo", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("childFilterInfoMask", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("userData", TYPE_INT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkpShape", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpStaticCompoundShape", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkpBvTreeShape")
	HK_PATCH_MEMBER_ADDED("numBitsForChildShapeKey", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("instances", TYPE_ARRAY_STRUCT, "hkpStaticCompoundShapeInstance", 0)
	HK_PATCH_MEMBER_ADDED("instanceExtraInfos", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("disabledLargeShapeKeyTable", TYPE_STRUCT, "hkpShapeKeyTable", 0)
	HK_PATCH_MEMBER_ADDED("tree", TYPE_STRUCT, "hkcdStaticTreeDefaultTreeStorage6", 0)
	HK_PATCH_DEPENDS("hkpBvTreeShape", 1)
	HK_PATCH_DEPENDS("hkcdStaticTreeDefaultTreeStorage6", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeDynamicStorage6", 0)
	HK_PATCH_DEPENDS("hkpStaticCompoundShapeInstance", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkpShape", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeTreehkcdStaticTreeDynamicStorage6", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeDynamicStoragehkcdStaticTreeCodec3Axis6", 0)
	HK_PATCH_DEPENDS("hkpShapeKeyTable", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpWorldCinfo", 15, "hkpWorldCinfo", 16)
	HK_PATCH_MEMBER_REMOVED("BETA_useSplitCollisionPipeline", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED_BOOL("BETA_useCompoundSpuElf", false)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("maxConstraintViolation", 18446726481523507000.000000f)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpBvCompressedMeshShape", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkpBvTreeShape")
	HK_PATCH_MEMBER_ADDED("convexRadius", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED_BYTE("weldingType", 6)
	HK_PATCH_MEMBER_ADDED("hasPerTriangleCollisionFilterInfo", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("hasPerTriangleUserData", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("collisionFilterInfoPalette", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("userDataPalette", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("tree", TYPE_STRUCT, "hkpBvCompressedMeshShapeTree", 0)
	HK_PATCH_DEPENDS("hkpBvTreeShape", 1)
	HK_PATCH_DEPENDS("hkcdStaticTreeDynamicStorage5", 0)
	HK_PATCH_DEPENDS("hkcdStaticMeshTreeBase", 0)
	HK_PATCH_DEPENDS("hkpBvCompressedMeshShapeTree", 0)
	HK_PATCH_DEPENDS("hkcdStaticMeshTreehkcdStaticMeshTreeCommonConfigunsignedintunsignedlonglong1121hkpBvCompressedMeshShapeTreeDataRun", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkpShape", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeTreehkcdStaticTreeDynamicStorage5", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeDynamicStoragehkcdStaticTreeCodec3Axis5", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpBvCompressedMeshShapeTreeDataRun", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkcdStaticMeshTreeBasePrimitiveDataRunBaseunsignedint")
	HK_PATCH_DEPENDS("hkcdStaticMeshTreeBasePrimitiveDataRunBaseunsignedint", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdStaticMeshTreehkcdStaticMeshTreeCommonConfigunsignedintunsignedlonglong1121hkpBvCompressedMeshShapeTreeDataRun", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkcdStaticMeshTreeBase")
	HK_PATCH_MEMBER_ADDED("packedVertices", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("sharedVertices", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("primitiveDataRuns", TYPE_ARRAY_STRUCT, "hkpBvCompressedMeshShapeTreeDataRun", 0)
	HK_PATCH_DEPENDS("hkpBvCompressedMeshShapeTreeDataRun", 0)
	HK_PATCH_DEPENDS("hkcdStaticMeshTreeBasePrimitiveDataRunBaseunsignedint", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeDynamicStorage5", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeTreehkcdStaticTreeDynamicStorage5", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeDynamicStoragehkcdStaticTreeCodec3Axis5", 0)
	HK_PATCH_DEPENDS("hkcdStaticMeshTreeBase", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpBvCompressedMeshShapeTree", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkcdStaticMeshTreehkcdStaticMeshTreeCommonConfigunsignedintunsignedlonglong1121hkpBvCompressedMeshShapeTreeDataRun")
	HK_PATCH_DEPENDS("hkcdStaticMeshTreehkcdStaticMeshTreeCommonConfigunsignedintunsignedlonglong1121hkpBvCompressedMeshShapeTreeDataRun", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeDynamicStorage5", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeTreehkcdStaticTreeDynamicStorage5", 0)
	HK_PATCH_DEPENDS("hkcdStaticTreeDynamicStoragehkcdStaticTreeCodec3Axis5", 0)
	HK_PATCH_DEPENDS("hkcdStaticMeshTreeBase", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpShapeKeyTable", 0)
	HK_PATCH_MEMBER_ADDED("lists", TYPE_OBJECT, "hkpShapeKeyTableBlock", 0)
	HK_PATCH_MEMBER_ADDED("occupancyBitField", TYPE_INT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkpShapeKeyTableBlock", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpShapeKeyTableBlock", 0)
	HK_PATCH_MEMBER_ADDED("slots", TYPE_TUPLE_INT, HK_NULL, 63)
	HK_PATCH_MEMBER_ADDED("next", TYPE_OBJECT, "hkpShapeKeyTableBlock", 0)
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
