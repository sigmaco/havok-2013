/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Common specific product patches applied to release 2011_2.
// This file is #included by hkPatches_2011_2.cpp

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkSetunsignedinthkContainerHeapAllocatorhkMapOperationsunsignedint", 0)
	HK_PATCH_MEMBER_ADDED("elem", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("numElems", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkSetUint32", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkSetunsignedinthkContainerHeapAllocatorhkMapOperationsunsignedint")
	HK_PATCH_DEPENDS("hkSetunsignedinthkContainerHeapAllocatorhkMapOperationsunsignedint", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkxBlob", 1)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("data", TYPE_ARRAY_BYTE, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkSkinnedMeshShapePart", 0)
	HK_PATCH_MEMBER_ADDED("startVertex", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("numVertices", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("startIndex", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("numIndices", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("boneIndex", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("meshSectionIndex", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("boundingSphere", TYPE_VEC_4, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkSkinnedMeshShapeBoneSection", 0)
	HK_PATCH_MEMBER_ADDED("meshBuffer", TYPE_OBJECT, "hkMeshShape", 0)
	HK_PATCH_MEMBER_ADDED("startBoneIndex", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("numBones", TYPE_INT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkMeshShape", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkSkinnedMeshShape", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkSkinnedRefMeshShape", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkMeshShape")
	HK_PATCH_MEMBER_ADDED("skinnedMeshShape", TYPE_OBJECT, "hkSkinnedMeshShape", 0)
	HK_PATCH_MEMBER_ADDED("bones", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("localFromRootTransforms", TYPE_ARRAY_STRUCT, "hkQTransform", 0)
	HK_PATCH_MEMBER_ADDED("name", TYPE_CSTRING, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkMeshShape", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkSkinnedMeshShape", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkQTransform", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkStorageSkinnedMeshShape", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkSkinnedMeshShape")
	HK_PATCH_MEMBER_ADDED("boneSections", TYPE_ARRAY_STRUCT, "hkSkinnedMeshShapeBoneSection", 0)
	HK_PATCH_MEMBER_ADDED("parts", TYPE_ARRAY_STRUCT, "hkSkinnedMeshShapePart", 0)
	HK_PATCH_MEMBER_ADDED("name", TYPE_CSTRING, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkSkinnedMeshShape", 0)
	HK_PATCH_DEPENDS("hkSkinnedMeshShapeBoneSection", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkSkinnedMeshShapePart", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkxBlobMeshShape", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkMeshShape")
	HK_PATCH_MEMBER_ADDED("blob", TYPE_STRUCT, "hkxBlob", 0)
	HK_PATCH_MEMBER_ADDED("name", TYPE_CSTRING, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkMeshShape", 0)
	HK_PATCH_DEPENDS("hkxBlob", 1)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
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
