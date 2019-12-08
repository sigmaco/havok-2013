/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Common specific product patches applied to release 710.
// This file is #included by hkPatches_710.cpp

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkMemoryMeshMaterial", 0)
        HK_PATCH_PARENT_SET(HK_NULL, "hkMeshMaterial")
        HK_PATCH_MEMBER_ADDED("materialName", TYPE_CSTRING, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("textures", TYPE_ARRAY_OBJECT, "hkMeshTexture", 0)
        HK_PATCH_DEPENDS("hkBaseObject", 0)
        HK_PATCH_DEPENDS("hkMeshMaterial", 0)
        HK_PATCH_DEPENDS("hkReferencedObject", 0)
        HK_PATCH_DEPENDS("hkMeshTexture", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkMemoryMeshVertexBuffer", 0)
        HK_PATCH_PARENT_SET(HK_NULL, "hkMeshVertexBuffer")
        HK_PATCH_MEMBER_ADDED("format", TYPE_STRUCT, "hkVertexFormat", 0)
        HK_PATCH_MEMBER_ADDED("elementOffsets", TYPE_TUPLE_INT, HK_NULL, 32)
        HK_PATCH_MEMBER_ADDED("memory", TYPE_ARRAY_BYTE, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("vertexStride", TYPE_INT, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("locked", TYPE_BYTE, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("numVertices", TYPE_INT, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("isSharable", TYPE_BYTE, HK_NULL, 0)
        HK_PATCH_DEPENDS("hkBaseObject", 0)
        HK_PATCH_DEPENDS("hkMeshVertexBuffer", 0)
        HK_PATCH_DEPENDS("hkReferencedObject", 0)
        HK_PATCH_DEPENDS("hkVertexFormat", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkVertexFormatElement", 0)
        HK_PATCH_MEMBER_ADDED("dataType", TYPE_BYTE, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("numValues", TYPE_BYTE, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("usage", TYPE_BYTE, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("subUsage", TYPE_BYTE, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("flags", TYPE_BYTE, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("pad", TYPE_TUPLE_BYTE, HK_NULL, 3)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkMultipleVertexBufferElementInfo", 0)
        HK_PATCH_MEMBER_ADDED("vertexBufferIndex", TYPE_BYTE, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("elementIndex", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkMultipleVertexBuffer", 0)
        HK_PATCH_PARENT_SET(HK_NULL, "hkMeshVertexBuffer")
        HK_PATCH_MEMBER_ADDED("vertexFormat", TYPE_STRUCT, "hkVertexFormat", 0)
        HK_PATCH_MEMBER_ADDED("lockedElements", TYPE_ARRAY_STRUCT, "hkMultipleVertexBufferLockedElement", 0)
        HK_PATCH_MEMBER_ADDED("lockedBuffer", TYPE_OBJECT, "hkMemoryMeshVertexBuffer", 0)
        HK_PATCH_MEMBER_ADDED("elementInfos", TYPE_ARRAY_STRUCT, "hkMultipleVertexBufferElementInfo", 0)
        HK_PATCH_MEMBER_ADDED("vertexBufferInfos", TYPE_ARRAY_STRUCT, "hkMultipleVertexBufferVertexBufferInfo", 0)
        HK_PATCH_MEMBER_ADDED("numVertices", TYPE_INT, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("isLocked", TYPE_BYTE, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("updateCount", TYPE_INT, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("writeLock", TYPE_BYTE, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("isSharable", TYPE_BYTE, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("constructionComplete", TYPE_BYTE, HK_NULL, 0)
        HK_PATCH_DEPENDS("hkBaseObject", 0)
        HK_PATCH_DEPENDS("hkMeshVertexBuffer", 0)
        HK_PATCH_DEPENDS("hkMemoryMeshVertexBuffer", 0)
        HK_PATCH_DEPENDS("hkMultipleVertexBufferElementInfo", 0)
        HK_PATCH_DEPENDS("hkMultipleVertexBufferVertexBufferInfo", 0)
        HK_PATCH_DEPENDS("hkReferencedObject", 0)
        HK_PATCH_DEPENDS("hkMultipleVertexBufferLockedElement", 0)
        HK_PATCH_DEPENDS("hkVertexFormat", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkIndexedTransformSet", 0)
        HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
        HK_PATCH_MEMBER_ADDED("matrices", TYPE_ARRAY_VEC_16, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("inverseMatrices", TYPE_ARRAY_VEC_16, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("matricesOrder", TYPE_ARRAY_INT, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("matricesNames", TYPE_ARRAY_CSTRING, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("allMatricesAreAffine", TYPE_BYTE, HK_NULL, 0)
        HK_PATCH_DEPENDS("hkBaseObject", 0)
        HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkMeshBody", 0)
        HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
        HK_PATCH_DEPENDS("hkBaseObject", 0)
        HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkMemoryMeshTexture", 0)
        HK_PATCH_PARENT_SET(HK_NULL, "hkMeshTexture")
        HK_PATCH_MEMBER_ADDED("data", TYPE_ARRAY_BYTE, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("format", TYPE_INT, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("hasMipMaps", TYPE_BYTE, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("filterMode", TYPE_INT, HK_NULL, 0)
        HK_PATCH_DEPENDS("hkBaseObject", 0)
        HK_PATCH_DEPENDS("hkMeshTexture", 0)
        HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkMemoryMeshBody", 0)
        HK_PATCH_PARENT_SET(HK_NULL, "hkMeshBody")
        HK_PATCH_MEMBER_ADDED("transform", TYPE_VEC_16, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("transformSet", TYPE_OBJECT, "hkIndexedTransformSet", 0)
        HK_PATCH_MEMBER_ADDED("shape", TYPE_OBJECT, "hkMeshShape", 0)
        HK_PATCH_MEMBER_ADDED("vertexBuffers", TYPE_ARRAY_OBJECT, "hkMeshVertexBuffer", 0)
        HK_PATCH_MEMBER_ADDED("name", TYPE_CSTRING, HK_NULL, 0)
        HK_PATCH_DEPENDS("hkMeshShape", 0)
        HK_PATCH_DEPENDS("hkMeshBody", 0)
        HK_PATCH_DEPENDS("hkBaseObject", 0)
        HK_PATCH_DEPENDS("hkIndexedTransformSet", 0)
        HK_PATCH_DEPENDS("hkMeshVertexBuffer", 0)
        HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkMeshTexture", 0)
        HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
        HK_PATCH_DEPENDS("hkBaseObject", 0)
        HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkMultipleVertexBufferVertexBufferInfo", 0)
        HK_PATCH_MEMBER_ADDED("vertexBuffer", TYPE_OBJECT, "hkMeshVertexBuffer", 0)
        HK_PATCH_MEMBER_ADDED("isLocked", TYPE_BYTE, HK_NULL, 0)
        HK_PATCH_DEPENDS("hkBaseObject", 0)
        HK_PATCH_DEPENDS("hkMeshVertexBuffer", 0)
        HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkMultipleVertexBufferLockedElement", 0)
        HK_PATCH_MEMBER_ADDED("vertexBufferIndex", TYPE_BYTE, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("elementIndex", TYPE_BYTE, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("lockedBufferIndex", TYPE_BYTE, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("vertexFormatIndex", TYPE_BYTE, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("lockFlags", TYPE_BYTE, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("outputBufferIndex", TYPE_BYTE, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("emulatedIndex", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkVertexFormat", 0)
        HK_PATCH_MEMBER_ADDED("elements", TYPE_TUPLE_STRUCT, "hkVertexFormatElement", 32)
        HK_PATCH_MEMBER_ADDED("numElements", TYPE_INT, HK_NULL, 0)
        HK_PATCH_DEPENDS("hkVertexFormatElement", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkMeshBoneIndexMapping", 0)
		HK_PATCH_MEMBER_ADDED("mapping", TYPE_ARRAY_INT, HK_NULL, 0)
HK_PATCH_END()


HK_PATCH_BEGIN("hkIndexedTransformSet", 0, "hkIndexedTransformSet", 1)
		HK_PATCH_MEMBER_ADDED("indexMappings", TYPE_ARRAY_OBJECT, "hkMeshBoneIndexMapping", 0)
HK_PATCH_DEPENDS("hkMeshBoneIndexMapping", 0)

HK_PATCH_END()

HK_PATCH_BEGIN("hkMemoryMeshTexture", 0, "hkMemoryMeshTexture", 1)
		HK_PATCH_MEMBER_ADDED("usageHint", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkPackfileHeader", 0, "hkPackfileHeader", 1)
		HK_PATCH_MEMBER_REMOVED("pad", TYPE_TUPLE_INT, HK_NULL, 2)
		HK_PATCH_MEMBER_ADDED("flags", TYPE_INT, HK_NULL, 0)
		HK_PATCH_MEMBER_ADDED("pad", TYPE_TUPLE_INT, HK_NULL, 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkMemoryMeshTexture", 1, "hkMemoryMeshTexture", 2)
        HK_PATCH_MEMBER_ADDED("filename", TYPE_CSTRING, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("textureCoordChannel", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkxMaterialProperty", 0)
	HK_PATCH_MEMBER_ADDED("key", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("value", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkxMaterial", 0, "hkxMaterial", 1)
	HK_PATCH_MEMBER_ADDED("properties", TYPE_ARRAY_STRUCT, "hkxMaterialProperty", 0)
	HK_PATCH_DEPENDS("hkxMaterialProperty", 0)
	//HK_PATCH_FUNCTION(hkxMaterial_0_to_1)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkHalf8", 0)
	HK_PATCH_MEMBER_ADDED("vec", TYPE_TUPLE_REAL, HK_NULL, 8)
HK_PATCH_END()

HK_PATCH_BEGIN("hkMemoryMeshVertexBuffer", 0, "hkMemoryMeshVertexBuffer", 1)
        HK_PATCH_MEMBER_ADDED("isBigEndian", TYPE_BYTE, HK_NULL, 0)
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
