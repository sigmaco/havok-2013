/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Common specific product patches applied to release 2012_2.
// This file is #included by hkPatches_2012_2.cpp

HK_PATCH_BEGIN("hkxVertexBufferVertexData", 0, "hkxVertexBufferVertexData", 1)
	HK_PATCH_MEMBER_RENAMED("vectorData", "old_vectorData")
	HK_PATCH_MEMBER_ADDED("vectorData", TYPE_ARRAY_REAL, HK_NULL, 0)
	HK_PATCH_FUNCTION(hkxVertexBufferVertexData_0_to_1)
	HK_PATCH_MEMBER_REMOVED("old_vectorData", TYPE_ARRAY_VEC_4, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkxAnimatedQuaternion", 1, "hkxAnimatedQuaternion", 2)
	HK_PATCH_MEMBER_RENAMED("quaternions", "old_quaternions")
	HK_PATCH_MEMBER_ADDED("quaternions", TYPE_ARRAY_REAL, HK_NULL, 0)
	HK_PATCH_FUNCTION(hkxAnimatedQuaternion_1_to_2)
	HK_PATCH_MEMBER_REMOVED("old_quaternions", TYPE_ARRAY_VEC_4, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkxAnimatedMatrix", 1, "hkxAnimatedMatrix", 2)
	HK_PATCH_MEMBER_RENAMED("matrices", "old_matrices")
	HK_PATCH_MEMBER_ADDED("matrices", TYPE_ARRAY_REAL, HK_NULL, 0)
	HK_PATCH_FUNCTION(hkxAnimatedMatrix_1_to_2)
	HK_PATCH_MEMBER_REMOVED("old_matrices", TYPE_ARRAY_VEC_16, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkxVertexVectorDataChannel", 1, "hkxVertexVectorDataChannel", 2)
	HK_PATCH_MEMBER_RENAMED("perVertexVectors", "old_perVertexVectors")
	HK_PATCH_MEMBER_ADDED("perVertexVectors", TYPE_ARRAY_REAL, HK_NULL, 0)
	HK_PATCH_FUNCTION(hkxVertexVectorDataChannel_1_to_2)
	HK_PATCH_MEMBER_REMOVED("old_perVertexVectors", TYPE_ARRAY_VEC_4, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkxAnimatedVector", 1, "hkxAnimatedVector", 2)
	HK_PATCH_MEMBER_RENAMED("vectors", "old_vectors")
	HK_PATCH_MEMBER_ADDED("vectors", TYPE_ARRAY_REAL, HK_NULL, 0)
	HK_PATCH_FUNCTION(hkxAnimatedVector_1_to_2)
	HK_PATCH_MEMBER_REMOVED("old_vectors", TYPE_ARRAY_VEC_4, HK_NULL, 0)
HK_PATCH_END()

#if defined(HK_REAL_IS_DOUBLE)

HK_PATCH_BEGIN("hkSweptTransform", 0, "hkSweptTransformd", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkQTransform", 0, "hkQTransformd", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkFourTransposedPoints", 0, "hkFourTransposedPointsd", 0)
HK_PATCH_END()


#else

HK_PATCH_BEGIN("hkSweptTransform", 0, "hkSweptTransformf", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkQTransform", 0, "hkQTransformf", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkFourTransposedPoints", 0, "hkFourTransposedPointsf", 0)
HK_PATCH_END()

#endif

HK_PATCH_BEGIN("hkSymmetricMatrix3", 0, HK_NULL, HK_CLASS_REMOVED)
	HK_PATCH_MEMBER_REMOVED("diag", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("offDiag", TYPE_VEC_4, HK_NULL, 0)
HK_PATCH_END()


#ifdef HK_FEATURE_PRODUCT_PHYSICS_2012
HK_PATCH_BEGIN("hkpPropertyValue", 0, "hkSimplePropertyValue", 1) 
HK_PATCH_END()

HK_PATCH_BEGIN("hkpProperty", 1, "hkSimpleProperty", 2) 
HK_PATCH_END()
#else
// These classes were renamed from hkp to hk prefixes (inter-product rename). 
// If not using Physics2012, this patch will take care of adding a new equivalent class.
HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkSimplePropertyValue", 1)
	HK_PATCH_MEMBER_ADDED("data", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkSimpleProperty", 2)
	HK_PATCH_MEMBER_ADDED("key", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("value", TYPE_STRUCT, "hkSimplePropertyValue", 0)
HK_PATCH_END()

#endif

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkStringObject", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("string", TYPE_CSTRING, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkSkinnedMeshShapeBoneSet", 0)
	HK_PATCH_MEMBER_ADDED("boneBufferOffset", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("numBones", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkSkinBinding", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkMeshShape")
	HK_PATCH_MEMBER_ADDED("skin", TYPE_OBJECT, "hkMeshShape", 0)
	HK_PATCH_MEMBER_ADDED("worldFromBoneTransforms", TYPE_ARRAY_VEC_16, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("boneNames", TYPE_ARRAY_CSTRING, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkMeshShape", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkSkinnedMeshShapePart", 0, "hkSkinnedMeshShapePart", 1)
	HK_PATCH_MEMBER_ADDED("boneSetId", TYPE_INT, HK_NULL, 0)
	HK_PATCH_FUNCTION(hkSkinnedMeshShapePart_0_to_1)
	HK_PATCH_MEMBER_REMOVED("boneIndex", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkStorageSkinnedMeshShape", 0, "hkStorageSkinnedMeshShape", 1)
	HK_PATCH_MEMBER_ADDED("bonesBuffer", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("boneSets", TYPE_ARRAY_STRUCT, "hkSkinnedMeshShapeBoneSet", 0)
	HK_PATCH_DEPENDS("hkSkinnedMeshShapeBoneSet", 0)
	HK_PATCH_FUNCTION(hkStorageSkinnedMeshShape_0_to_1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkSkinnedMeshShapeBoneSection", 0, "hkSkinnedMeshShapeBoneSection", 1)
	HK_PATCH_MEMBER_ADDED("startBoneSetId", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("numBoneSets", TYPE_INT, HK_NULL, 0)
	HK_PATCH_FUNCTION(hkSkinnedMeshShapeBoneSection_0_to_1)
	HK_PATCH_MEMBER_REMOVED("startBoneIndex", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("numBones", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkGeometry", 0, "hkGeometry", 1)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkIntRealPair", 0)
	HK_PATCH_MEMBER_ADDED("key", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("value", TYPE_REAL, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkSetIntFloatPair", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkSethkIntRealPairhkContainerHeapAllocatorhkMapOperationshkIntRealPair")
	HK_PATCH_DEPENDS("hkSethkIntRealPairhkContainerHeapAllocatorhkMapOperationshkIntRealPair", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkSethkIntRealPairhkContainerHeapAllocatorhkMapOperationshkIntRealPair", 0)
	HK_PATCH_MEMBER_ADDED("elem", TYPE_ARRAY_STRUCT, "hkIntRealPair", 0)
	HK_PATCH_MEMBER_ADDED("numElems", TYPE_INT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkIntRealPair", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkRefCountedProperties", 0, "hkRefCountedProperties", 1)
	HK_PATCH_PARENT_SET("hkReferencedObject", HK_NULL)
HK_PATCH_END()


#ifdef HK_FEATURE_PRODUCT_PHYSICS_2012
	HK_PATCH_BEGIN("hkpMassProperties", 0, "hkMassProperties", 1) 
	HK_PATCH_END()
#else
// This class was renamed hkMassProperties from hkpMassProperties (inter-product rename). If not using Physics2012,
// this patch will take care of adding a new equivalent class.
HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkMassProperties", 1)
	HK_PATCH_MEMBER_ADDED("volume", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("mass", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("centerOfMass", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("inertiaTensor", TYPE_VEC_12, HK_NULL, 0)
HK_PATCH_END()
#endif

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
