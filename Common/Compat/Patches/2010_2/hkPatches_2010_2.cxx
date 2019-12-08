/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Common specific product patches applied to release 2010_2.
// This file is #included by hkPatches_2010_2.cpp

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkFourTransposedPoints", 0)
	HK_PATCH_MEMBER_ADDED("vertices", TYPE_TUPLE_VEC_4, HK_NULL, 3)
HK_PATCH_END()

HK_PATCH_BEGIN("hkHalf8", 1, "hkHalf8", 2)
	HK_PATCH_MEMBER_ADDED("halfs", TYPE_TUPLE_INT, HK_NULL, 8)
	HK_PATCH_FUNCTION(hkHalf8_1_to_2)
	HK_PATCH_MEMBER_REMOVED("quad", TYPE_TUPLE_REAL, HK_NULL, 8)
HK_PATCH_END()

// Fixes for new serialized type system

HK_PATCH_BEGIN("hkxMaterial", 1, "hkxMaterial", 2)
	HK_PATCH_MEMBER_RENAMED("extraData", "old_extraData")
	HK_PATCH_MEMBER_ADDED("extraData",  TYPE_OBJECT, "hkReferencedObject", 0)
	HK_PATCH_FUNCTION(hkxMaterial_1_to_2)
	HK_PATCH_MEMBER_REMOVED("old_extraData", TYPE_OBJECT, "hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkMemoryResourceHandle", 2, "hkMemoryResourceHandle", 3)
	HK_PATCH_MEMBER_RENAMED("variant", "old_variant")
	HK_PATCH_MEMBER_ADDED("variant",  TYPE_OBJECT, "hkReferencedObject", 0)
	HK_PATCH_FUNCTION(hkMemoryResourceHandle_2_to_3)
	HK_PATCH_MEMBER_REMOVED("old_variant", TYPE_OBJECT, "hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkxMaterialTextureStage", 0, "hkxMaterialTextureStage", 1)
	HK_PATCH_MEMBER_RENAMED("texture", "old_texture")
	HK_PATCH_MEMBER_ADDED("texture",  TYPE_OBJECT, "hkReferencedObject", 0)
	HK_PATCH_FUNCTION(hkxMaterialTextureStage_0_to_1)
	HK_PATCH_MEMBER_REMOVED("old_texture", TYPE_OBJECT, "hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkxMeshSection", 1, "hkxMeshSection", 2)
	HK_PATCH_MEMBER_RENAMED("userChannels", "old_userChannels")
	HK_PATCH_MEMBER_ADDED("userChannels",  TYPE_ARRAY_OBJECT, "hkReferencedObject", 0)
	HK_PATCH_FUNCTION(hkxMeshSection_1_to_2)
	HK_PATCH_MEMBER_REMOVED("old_userChannels", TYPE_ARRAY_OBJECT, "hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkRootLevelContainerNamedVariant", 0, "hkRootLevelContainerNamedVariant", 1)
	HK_PATCH_MEMBER_RENAMED("variant", "old_variant")
	HK_PATCH_MEMBER_ADDED("variant",  TYPE_OBJECT, "hkReferencedObject", 0)
	HK_PATCH_FUNCTION(hkRootLevelContainerNamedVariant_0_to_1)
	HK_PATCH_MEMBER_REMOVED("old_variant", TYPE_OBJECT, "hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkxAttribute", 0, "hkxAttribute", 1)
	HK_PATCH_MEMBER_RENAMED("value", "old_value")
	HK_PATCH_MEMBER_ADDED("value",  TYPE_OBJECT, "hkReferencedObject", 0)
	HK_PATCH_FUNCTION(hkxAttribute_0_to_1)
	HK_PATCH_MEMBER_REMOVED("old_value", TYPE_OBJECT, "hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkxNode", 1, "hkxNode", 2)
	HK_PATCH_MEMBER_RENAMED("object", "old_object")
	HK_PATCH_MEMBER_ADDED("object",  TYPE_OBJECT, "hkReferencedObject", 0)
	HK_PATCH_FUNCTION(hkxNode_1_to_2)
	HK_PATCH_MEMBER_REMOVED("old_object", TYPE_OBJECT, "hkReferencedObject", 0)
HK_PATCH_END()

// tuple/tuple update

HK_PATCH_BEGIN("hkxAttributeHolder", 1, "hkxAttributeHolder", 2)
	HK_PATCH_MEMBER_RENAMED("attributeGroups", "old_attributeGroups")
	HK_PATCH_MEMBER_ADDED("attributeGroups",  TYPE_ARRAY_STRUCT, "hkxAttributeGroup", 0)
	HK_PATCH_FUNCTION(hkxAttributeHolder_1_to_2)
	HK_PATCH_MEMBER_REMOVED("old_attributeGroups", TYPE_ARRAY_OBJECT, "hkxAttributeGroup", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkIndexedTransformSet", 1, "hkIndexedTransformSet", 2)
	HK_PATCH_MEMBER_RENAMED("indexMappings", "old_indexMappings")
	HK_PATCH_MEMBER_ADDED("indexMappings",  TYPE_ARRAY_STRUCT, "hkMeshBoneIndexMapping", 0)
	HK_PATCH_FUNCTION(hkIndexedTransformSet_1_to_2)
	HK_PATCH_MEMBER_REMOVED("old_indexMappings", TYPE_ARRAY_OBJECT, "hkMeshBoneIndexMapping", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkClass", 0, "hkClass", 1)
	HK_PATCH_MEMBER_RENAMED("declaredEnums", "old_declaredEnums")
	HK_PATCH_MEMBER_ADDED("declaredEnums",  TYPE_ARRAY_STRUCT, "hkClassEnum", 0)
	HK_PATCH_FUNCTION(hkClass_0_1)
	HK_PATCH_MEMBER_REMOVED("old_declaredEnums", TYPE_ARRAY_OBJECT, "hkClassEnum", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkMemoryMeshMaterial", 0, "hkMemoryMeshMaterial", 1)
	HK_PATCH_MEMBER_ADDED("diffuseColor", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("ambientColor", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("specularColor", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("emissiveColor", TYPE_VEC_4, HK_NULL, 0)
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
