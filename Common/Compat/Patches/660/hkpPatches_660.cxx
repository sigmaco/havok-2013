/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Physics specific product patches applied to release 660.
// This file is #included by hkpPatches_660.cpp

HK_PATCH_BEGIN("hkpExtendedMeshShape", 1, "hkpExtendedMeshShape", 2)
	HK_PATCH_MEMBER_ADDED_INT("cachedNumChildShapes", -1)
HK_PATCH_END()


HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpCompressedMeshShapeBigTriangle", 0)
	HK_PATCH_MEMBER_ADDED("a", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("b", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("c", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("m", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED_INT("weldingInfo", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpCompressedMeshShapeChunk", 0)
	HK_PATCH_MEMBER_ADDED("offset", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("vertices", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("indices", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("stripLengths", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("weldingInfo", TYPE_ARRAY_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpCompressedMeshShape", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkpShapeCollection")
	HK_PATCH_MEMBER_ADDED("radius", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED_BYTE("weldingType", 6)
	HK_PATCH_MEMBER_ADDED("bigVertices", TYPE_ARRAY_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("bigTriangles", TYPE_ARRAY_STRUCT, "hkpCompressedMeshShapeBigTriangle", 0)
	HK_PATCH_MEMBER_ADDED("chunks", TYPE_ARRAY_OBJECT, "hkpCompressedMeshShapeChunk", 0)
	HK_PATCH_MEMBER_ADDED("error", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("bounds", TYPE_STRUCT, "hkAabb", 0)
	HK_PATCH_DEPENDS("hkpShapeCollection", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkpShape", 0)
	HK_PATCH_DEPENDS("hkpCompressedMeshShapeBigTriangle", 0)
	HK_PATCH_DEPENDS("hkAabb", 0)
	HK_PATCH_DEPENDS("hkpCompressedMeshShapeChunk", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpCompressedMeshShape", 0, "hkpCompressedMeshShape", 1)
	HK_PATCH_MEMBER_ADDED("numChunkTriangles", TYPE_ARRAY_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpCompressedMeshShapeBigTriangle", 0, "hkpCompressedMeshShapeBigTriangle", 1)
	HK_PATCH_MEMBER_REMOVED("m", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("material", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpCompressedMeshShape", 1, "hkpCompressedMeshShape", 2)
	HK_PATCH_MEMBER_ADDED("bitsPerIndex", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("bitsPerWIndex", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("wIndexMask", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("indexMask", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("materialStridingType", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("materialStriding", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpCompressedMeshShapeChunk", 0, "hkpCompressedMeshShapeChunk", 1)
	HK_PATCH_MEMBER_ADDED("materials", TYPE_ARRAY_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpCompressedMeshShape", 2, "hkpCompressedMeshShape", 3)
	HK_PATCH_MEMBER_REMOVED("materialStridingType", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("materialStriding", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("materialType", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("materials", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("materials16", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("materials8", TYPE_ARRAY_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpCompressedMeshShapeChunk", 1, "hkpCompressedMeshShapeChunk", 2)
	HK_PATCH_MEMBER_REMOVED("materials", TYPE_ARRAY_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("materialInfo", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpCompressedMeshShape", 3, "hkpCompressedMeshShape", 4)
	HK_PATCH_MEMBER_ADDED("transforms", TYPE_ARRAY_VEC_16, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpCompressedMeshShapeChunk", 2, "hkpCompressedMeshShapeChunk", 3)
	HK_PATCH_MEMBER_ADDED("chunkRef", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("transformIndex", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpEntity", 1, "hkpEntity", 2)
	HK_PATCH_MEMBER_RENAMED("processContactCallbackDelay", "contactPointCallbackDelay")
	HK_PATCH_MEMBER_RENAMED("numUserDatasInContactPointProperties", "numShapeKeysInContactPointProperties")
	HK_PATCH_MEMBER_ADDED("responseModifierFlags", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpCompressedMeshShapeConvexPiece", 0)
	HK_PATCH_MEMBER_ADDED("offset", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("vertices", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("faceVertices", TYPE_ARRAY_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("faceOffsets", TYPE_ARRAY_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("reference", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("transformIndex", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpCompressedMeshShape", 4, "hkpCompressedMeshShape", 5)
	HK_PATCH_MEMBER_ADDED("convexPieces", TYPE_ARRAY_OBJECT, "hkpCompressedMeshShapeConvexPiece", 0)
	HK_PATCH_DEPENDS("hkpCompressedMeshShapeConvexPiece", 0)
	//HK_PATCH_FUNCTION(hkpCompressedMeshShape_4_to_5)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpPolytopeShape", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkpConvexShape")
	HK_PATCH_MEMBER_ADDED("aabbHalfExtents", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("aabbCenter", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("externalFacesBitfield", TYPE_OBJECT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("numExternalFaces", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("facesOffsets", TYPE_OBJECT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("numInternalFaces", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("faceVertices", TYPE_OBJECT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("edgesWeldingValues", TYPE_OBJECT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("vertices", TYPE_ARRAY_VEC_4, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkpShape", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkpConvexShape", 0)
	HK_PATCH_DEPENDS("hkpSphereRepShape", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpCompressedMeshShapeConvexPiece", 0, "hkpCompressedMeshShapeConvexPiece", 1)
	HK_PATCH_MEMBER_REMOVED("faceOffsets", TYPE_ARRAY_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("faceOffsets", TYPE_ARRAY_INT, HK_NULL, 0)
	//HK_PATCH_FUNCTION(hkpCompressedMeshShapeConvexPiece_0_to_1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkWorldMemoryAvailableWatchDog", 0, "hkWorldMemoryAvailableWatchDog", 1)
	HK_PATCH_MEMBER_REMOVED("minMemoryAvailable", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpDefaultWorldMemoryWatchDog", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkWorldMemoryAvailableWatchDog")
	HK_PATCH_MEMBER_ADDED("minHeapMemoryAvailable", TYPE_INT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkWorldMemoryAvailableWatchDog", 1)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpNamedMeshMaterial", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkpMeshMaterial")
	HK_PATCH_MEMBER_ADDED("name", TYPE_CSTRING, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkpMeshMaterial", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpStorageExtendedMeshShapeMeshSubpartStorage", 2, "hkpStorageExtendedMeshShapeMeshSubpartStorage", 3)
	HK_PATCH_MEMBER_ADDED("namedMaterials", TYPE_ARRAY_STRUCT, "hkpNamedMeshMaterial", 0)
	HK_PATCH_DEPENDS("hkpNamedMeshMaterial", 0)
	HK_PATCH_DEPENDS("hkpMeshMaterial", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpCompressedPolytopeShape", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkpConvexShape")
	HK_PATCH_MEMBER_ADDED("aabbHalfExtents", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("aabbCenter", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("externalFacesBitfield", TYPE_OBJECT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("numExternalFaces", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("facesOffsets", TYPE_OBJECT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("numInternalFaces", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("faceVertices", TYPE_OBJECT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("edgesWeldingValues", TYPE_OBJECT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("vertices", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("quantization", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("offset", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("transform", TYPE_VEC_16, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkpShape", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkpConvexShape", 0)
	HK_PATCH_DEPENDS("hkpSphereRepShape", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpPolytopeShape", 0, HK_NULL, HK_CLASS_REMOVED)
	HK_PATCH_PARENT_SET("hkpConvexShape", HK_NULL)
	HK_PATCH_MEMBER_REMOVED("aabbHalfExtents", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("aabbCenter", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("externalFacesBitfield", TYPE_OBJECT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("numExternalFaces", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("facesOffsets", TYPE_OBJECT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("numInternalFaces", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("faceVertices", TYPE_OBJECT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("edgesWeldingValues", TYPE_OBJECT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("vertices", TYPE_ARRAY_VEC_4, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkpShape", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkpConvexShape", 0)
	HK_PATCH_DEPENDS("hkpSphereRepShape", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpCompressedMeshShape", 5, "hkpCompressedMeshShape", 6)
	HK_PATCH_MEMBER_ADDED("meshMaterials", TYPE_OBJECT, "hkpMeshMaterial", 0)
	HK_PATCH_MEMBER_ADDED("materialStriding", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("numMaterials", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("namedMaterials", TYPE_ARRAY_STRUCT, "hkpNamedMeshMaterial", 0)
	HK_PATCH_DEPENDS("hkpNamedMeshMaterial", 0)
	HK_PATCH_DEPENDS("hkpMeshMaterial", 0)
	//HK_PATCH_FUNCTION(hkpCompressedMeshShape_5_to_6)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpCompressedMeshShapeConvexPiece", 1, "hkpCompressedMeshShapeConvexPiece", 2)
	HK_PATCH_MEMBER_ADDED("aabbCenter", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("aabbHalfExtents", TYPE_VEC_4, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpCompressedMeshShapeChunk", 3, "hkpCompressedMeshShapeChunk", 4)
	HK_PATCH_MEMBER_REMOVED("chunkRef", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("reference", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpWorldCinfo", 3, "hkpWorldCinfo", 4)
	HK_PATCH_MEMBER_ADDED_BYTE("fireCollisionCallbacks", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpConstraintInstanceSmallArraySerializeOverrideType", 0, "hkpConstraintInstanceSmallArraySerializeOverrideType", 1)
	HK_PATCH_MEMBER_REMOVED("data", TYPE_OBJECT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpEntitySmallArraySerializeOverrideType", 0, "hkpEntitySmallArraySerializeOverrideType", 1)
	HK_PATCH_MEMBER_REMOVED("data", TYPE_OBJECT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpDefaultWorldMemoryWatchDog", 0, "hkpDefaultWorldMemoryWatchDog", 1)
	HK_PATCH_MEMBER_REMOVED("minHeapMemoryAvailable", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("freeHeapMemoryRequested", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpDisplayBindingData", 0, "hkpDisplayBindingData", 1)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
HK_PATCH_END()

HK_PATCH_BEGIN("hkpPhysicsSystemDisplayBinding", 0, "hkpDisplayBindingDataPhysicsSystem", 1)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
HK_PATCH_END()

HK_PATCH_BEGIN("hkpRigidBodyDisplayBinding", 0, "hkpDisplayBindingDataRigidBody", 1)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
HK_PATCH_END()

HK_PATCH_BEGIN("hkpSimpleShapePhantomCollisionDetail", 0, HK_NULL, HK_CLASS_REMOVED)
	HK_PATCH_MEMBER_REMOVED("collidable", TYPE_OBJECT, "hkpCollidable", 0)
	HK_PATCH_DEPENDS("hkpCdBody", 0)
	HK_PATCH_DEPENDS("hkpCollidable", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpShapeRayCastInput", 0, HK_NULL, HK_CLASS_REMOVED)
	HK_PATCH_MEMBER_REMOVED("from", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("to", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("filterInfo", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("rayShapeCollectionFilter", TYPE_OBJECT, "hkpRayShapeCollectionFilter", 0)
	HK_PATCH_DEPENDS("hkpRayShapeCollectionFilter", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpShapeRayBundleCastInput", 0, HK_NULL, HK_CLASS_REMOVED)
	HK_PATCH_MEMBER_REMOVED("from", TYPE_TUPLE_VEC_4, HK_NULL, 3)
	HK_PATCH_MEMBER_REMOVED("to", TYPE_TUPLE_VEC_4, HK_NULL, 3)
	HK_PATCH_MEMBER_REMOVED("filterInfo", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("rayShapeCollectionFilter", TYPE_OBJECT, "hkpRayShapeCollectionFilter", 0)
	HK_PATCH_DEPENDS("hkpRayShapeCollectionFilter", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpCdBody", 0, "hkpCdBody", 1)
	HK_PATCH_MEMBER_REMOVED("parent", TYPE_OBJECT, "hkpCdBody", 0)
	HK_PATCH_MEMBER_ADDED("parent", TYPE_VOID, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpWorldCinfo", 4, "hkpWorldCinfo", 5)
	HK_PATCH_MEMBER_ADDED("treeUpdateType", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED_BYTE("useMultipleTree", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpCompressedPolytopeShape", 0, HK_NULL, HK_CLASS_REMOVED)
	HK_PATCH_PARENT_SET("hkpConvexShape", HK_NULL)
	HK_PATCH_MEMBER_REMOVED("aabbHalfExtents", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("aabbCenter", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("externalFacesBitfield", TYPE_OBJECT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("numExternalFaces", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("facesOffsets", TYPE_OBJECT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("numInternalFaces", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("faceVertices", TYPE_OBJECT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("edgesWeldingValues", TYPE_OBJECT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("vertices", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("quantization", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("offset", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("transform", TYPE_VEC_16, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkpShape", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkpConvexShape", 0)
	HK_PATCH_DEPENDS("hkpSphereRepShape", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpCompressedMeshShapeConvexPiece", 2, "hkpCompressedMeshShapeConvexPiece", 3)
	HK_PATCH_MEMBER_REMOVED("aabbCenter", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("aabbHalfExtents", TYPE_VEC_4, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpConvexVerticesShape", 1, "hkpConvexVerticesShape", 2)
	HK_PATCH_MEMBER_ADDED("convexPiece", TYPE_OBJECT, "hkpCompressedMeshShapeConvexPiece", 0)
	HK_PATCH_DEPENDS("hkpCompressedMeshShapeConvexPiece", 2)
	//HK_PATCH_FUNCTION(hkpConvexVerticesShape_1_to_2)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpWorldCinfo", 5, "hkpWorldCinfo", 6)
	HK_PATCH_MEMBER_ADDED_INT("maxNumToiCollisionPairsSinglethreaded", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpCompressedMeshShape", 6, "hkpCompressedMeshShape", 7)
	HK_PATCH_MEMBER_REMOVED("meshMaterials", TYPE_OBJECT, "hkpMeshMaterial", 0)
	HK_PATCH_DEPENDS("hkpMeshMaterial", 0)
	//HK_PATCH_FUNCTION(hkpCompressedMeshShape_6_to_7)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpCompressedMeshShape", 7, "hkpCompressedMeshShape", 8)
	HK_PATCH_MEMBER_REMOVED("numChunkTriangles", TYPE_ARRAY_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpStorageExtendedMeshShapeShapeSubpartStorage", 1, "hkpStorageExtendedMeshShapeShapeSubpartStorage", 2)
	HK_PATCH_MEMBER_REMOVED("shapes", TYPE_ARRAY_OBJECT, "hkpConvexShape", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpExtendedMeshShapeShapesSubpart", 0, "hkpExtendedMeshShapeShapesSubpart", 1)
	HK_PATCH_MEMBER_REMOVED("offsetSet", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("rotationSet", TYPE_BYTE, HK_NULL, 0)
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
