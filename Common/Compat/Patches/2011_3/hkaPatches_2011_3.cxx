/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Animation specific product patches applied to release 2011_3.
// This file is #included by hkaPatches_2011_3.cpp
HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaSkeletonPartition", 0)
	HK_PATCH_MEMBER_ADDED("startBoneIndex", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("numBones", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaSkeletonPartition", 0, "hkaSkeletonPartition", 1)
   HK_PATCH_MEMBER_ADDED("name", TYPE_CSTRING, HK_NULL, 0)
HK_PATCH_END()


HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaSkeletonSegment", 0)
	HK_PATCH_MEMBER_ADDED("partitionMask", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("startBoneIndex", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("numBones", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaSkeletonSegment", 0, HK_NULL, HK_CLASS_REMOVED )
	HK_PATCH_MEMBER_REMOVED("partitionMask", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("startBoneIndex", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("numBones", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()


HK_PATCH_BEGIN("hkaAnimationBinding", 1, "hkaAnimationBinding", 2)
   HK_PATCH_MEMBER_ADDED("segmentName", TYPE_CSTRING, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaAnimationBinding", 2, "hkaAnimationBinding", 3)
   HK_PATCH_MEMBER_REMOVED("segmentName", TYPE_CSTRING, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("partitionIndices", TYPE_ARRAY_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaSkeleton", 3, "hkaSkeleton", 4)
	HK_PATCH_MEMBER_ADDED("partitionNames", TYPE_ARRAY_CSTRING, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("segmentNames", TYPE_ARRAY_CSTRING, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("segments", TYPE_ARRAY_STRUCT, "hkaSkeletonSegment", 0)
   HK_PATCH_MEMBER_ADDED("partitions", TYPE_ARRAY_STRUCT, "hkaSkeletonPartition", 0)
   HK_PATCH_DEPENDS("hkaSkeletonPartition", 0)
   HK_PATCH_DEPENDS("hkaSkeletonSegment", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaSkeleton", 4, "hkaSkeleton", 5)
	HK_PATCH_MEMBER_REMOVED("partitionNames", TYPE_ARRAY_CSTRING, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("segmentNames", TYPE_ARRAY_CSTRING, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("segments", TYPE_ARRAY_STRUCT, "hkaSkeletonSegment", 0)
	HK_PATCH_DEPENDS("hkaSkeletonSegment", 0)
HK_PATCH_END()


HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaParameterizedReferenceFrame", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkaDefaultAnimatedReferenceFrame" )
	HK_PATCH_DEPENDS("hkaDefaultAnimatedReferenceFrame", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaAngularReferenceFrame", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkaParameterizedReferenceFrame" )
   HK_PATCH_MEMBER_ADDED("topAngle", TYPE_REAL, HK_NULL, 0)
   HK_PATCH_MEMBER_ADDED("radius", TYPE_REAL, HK_NULL, 0)
   HK_PATCH_DEPENDS("hkaParameterizedReferenceFrame", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaDirectionalReferenceFrame", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkaParameterizedReferenceFrame" )
   HK_PATCH_MEMBER_ADDED("movementDir", TYPE_VEC_4, HK_NULL, 0)
   HK_PATCH_DEPENDS("hkaParameterizedReferenceFrame", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaParameterizedAnimationReferenceFrame", 0)
    HK_PATCH_PARENT_SET(HK_NULL, "hkaDefaultAnimatedReferenceFrame")
    HK_PATCH_MEMBER_ADDED("parameterValues", TYPE_ARRAY_REAL, HK_NULL, 0)
    HK_PATCH_MEMBER_ADDED("parameterTypes", TYPE_ARRAY_INT, HK_NULL, 0)
    HK_PATCH_DEPENDS("hkaAnimatedReferenceFrame", 0)
    HK_PATCH_DEPENDS("hkBaseObject", 0)
    HK_PATCH_DEPENDS("hkaDefaultAnimatedReferenceFrame", 0)
    HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaSkeletonMapperDataPartitionMappingRange", 0)
   HK_PATCH_MEMBER_ADDED("startMappingIndex", TYPE_INT, HK_NULL, 0)
   HK_PATCH_MEMBER_ADDED("numMappings", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaSkeletonMapperData", 1, "hkaSkeletonMapperData", 2)
	HK_PATCH_MEMBER_ADDED("partitionMap", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("simpleMappingPartitionRanges", TYPE_ARRAY_STRUCT, "hkaSkeletonMapperDataPartitionMappingRange", 0)
	HK_PATCH_MEMBER_ADDED("chainMappingPartitionRanges", TYPE_ARRAY_STRUCT, "hkaSkeletonMapperDataPartitionMappingRange", 0)
	HK_PATCH_DEPENDS("hkaSkeletonMapperDataPartitionMappingRange", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaReferencePoseAnimation", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkaAnimation")
	HK_PATCH_MEMBER_ADDED("skeleton", TYPE_OBJECT, "hkaSkeleton", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkaAnimation", 3)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkaSkeleton", 4)
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
