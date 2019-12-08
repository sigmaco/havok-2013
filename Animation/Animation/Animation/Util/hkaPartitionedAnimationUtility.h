/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_PARTITIONED_ANIMATION_UTILITY_H
#define HK_PARTITIONED_ANIMATION_UTILITY_H

#include <Animation/Animation/Rig/hkaSkeleton.h>

class hkaAnimationBinding;

/// This utility contains helper functions for dealing with partitions including
/// a function to create a partitioned animation for an input animation and a skeleton.
/// This can be used to layer different animations onto a composite animation.
/// The Partitioned Animation is created by removing the transforms from an animation
/// for bones that do not belong to the partitions provided. 
class hkaPartitionedAnimationUtility
{
public:

	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_ANIM_RUNTIME,hkaPartitionedAnimationUtility);

	/// Input structure
	struct Input
	{
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_ANIM_RUNTIME, hkaPartitionedAnimationUtility::Input );

		/// The number of tracks in the animation
		int m_numberOfTransformTracks;					
		/// The number of poses (usually equates to number of frames)
		int m_numberOfPoses;
		/// The original data
		const hkQsTransform* m_animationData;
		/// The skeleton
		const hkaSkeleton* m_skeleton;
		/// The number of partitions
		int m_numberOfPartitions;
		/// The list of partition names to use
		hkStringPtr* m_partitionNames;
	};

	/// Input structure
	struct Output
	{
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_ANIM_RUNTIME, hkaPartitionedAnimationUtility::Output );

		// Animation data that will be filled in
		hkQsTransform* m_transformsOut;
		// Partition Indices of the new animation
		hkInt16* m_partitionIndicesOut;
		//Number of transforms for the new animation
		int m_numTotalTranformsOut;
		//Number of tracks for the new animation
		int m_numTransformTracksOut;
	};

	/// This creates a layered animation by removing the transforms that are not 
	/// associated with a partition specified in the input. 
	static void HK_CALL createPartitionedAnimation( const Input& input, Output& output );

	/// Get the sorted list of partition indices for a skeleton from the provided partitionNames
	static void HK_CALL getPartitionIndices( hkStringPtr* partitionNames, int numPartitionNames, const hkaSkeleton* skeleton, hkInt16* partitionIndicesOut );

	/// Sets the partial dense partition pose to the skeleton's reference pose
	static void HK_CALL setPartitionPoseToReference(const hkaSkeleton* skeleton, const hkInt16* partitionIndices, int numPartitionIndices, hkQsTransform* transformsOut);

	/// Get the number of bones in all partitions
	static hkInt16 HK_CALL getNumberOfBonesInPartitions(const hkArray<hkaSkeleton::Partition>& partitions);

	/// Given the partition map for A to B, return the number of bones in to use for mapping partitions A to partitions B
	static hkInt16 HK_CALL getNumMappedPartitionBones(const hkInt16* aToBPartitionMap, const hkInt16* partitionIndicesSkeletonA, int numPartitionIndicesSkeletonA, const hkaSkeleton* skelB);

	/// Given the partition map for A to B, return the indices that are mapped from A to B
	static void HK_CALL getMappedPartitionIndices(const hkInt16* aToBPartitionMap, const hkInt16* partitionIndicesSkeletonA, int numPartitionIndicesSkeletonA, const hkaSkeleton* skelB, hkInt16* partitionIndicesBOut);

	/// Fill in an array with the partitions from the skeleton
	static void HK_CALL getPartitionsFromIndices(const hkaSkeleton* skeleton, const hkArray<hkInt16>& partitionIndices, hkArray<hkaSkeleton::Partition>& partitionsOut);

	
	/// Maps the pose from a sparse partition pose to the full pose
	static void HK_CALL mapPartitionPoseToFullPose( const hkArray<hkaSkeleton::Partition>& partitions, const hkArray<hkInt16>& partitionIndices, const hkQsTransform* transformsIn, int numTransformsIn, hkQsTransform* transformsOut);

	/// Maps the pose from a sparse partition pose to the full pose
	static void HK_CALL mapPartitionPoseToFullPose( const hkaSkeleton::Partition* partitions, const hkInt16* partitionIndices, int numPartitionIndices, const hkQsTransform* transformsIn, int numTransformsIn, hkQsTransform* transformsOut);

	/// Maps the pose from a sparse partition pose to the full pose
	static void HK_CALL mapPartitionPoseToFullPose( const hkArray<hkaSkeleton::Partition>& animPartitions, const hkQsTransform* transformsIn, int numTransformsIn, hkQsTransform* transformsOut);

	/// Maps the pose from a sparse partition pose to the full pose
	static void HK_CALL mapPartitionPoseToFullPoseWithWeights( const hkArray<hkaSkeleton::Partition>& partitions, const hkArray<hkInt16>& partitionIndices, const hkQsTransform* transformsIn, const hkUint8* weightsIn, int numTransformsIn, hkQsTransform* transformsOut, hkUint8* weightsOut);

	/// Maps the pose from a sparse partition pose to the full pose
	static void HK_CALL mapPartitionPoseToFullPoseWithWeights( const hkaSkeleton::Partition* partitions, const hkInt16* partitionIndices, int numPartitionIndices, const hkQsTransform* transformsIn, const hkUint8* weightsIn, int numTransformsIn, hkQsTransform* transformsOut, hkUint8* weightsOut);

	/// Maps the pose from a sparse partition pose to the full pose
	static void HK_CALL mapPartitionPoseToFullPoseWithWeights( const hkaSkeleton::Partition* partitions, const hkInt16* partitionIndices, int numPartitionIndices, const hkQsTransform* transformsIn, const hkReal* weightsIn, int numTransformsIn, hkQsTransform* transformsOut, hkReal* weightsOut);

	/// Maps the pose from a sparse partition pose to the full pose
	static void HK_CALL mapPartitionPoseToFullPoseWithWeights( const hkArray<hkaSkeleton::Partition>& animPartitions, const hkQsTransform* transformsIn, const hkUint8* weightsIn, int numTransformsIn, hkQsTransform* transformsOut, hkUint8* weightsOut);

	/// Checks that the binding contains valid partition indices for the skeleton.
	static bool HK_CALL hasValidPartitions( const hkaAnimationBinding& binding, const hkaSkeleton& skeleton );

private:
	/// Sort the partition names to match the partition order in the skeleton
	static void HK_CALL sortPartitionNames( hkStringPtr* partitionNames, int numParitionNames, const hkaSkeleton* skeleton, hkStringPtr* partitionNamesOut);
};


#endif // HK_PARTITIONED_ANIMATION_UTILITY_H

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
