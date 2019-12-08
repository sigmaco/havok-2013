/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_SKELETON_MAPPER_H
#define HK_SKELETON_MAPPER_H

#include <Animation/Animation/Mapper/hkaSkeletonMapperData.h>
#include <Animation/Animation/Rig/hkaSkeleton.h>

class hkaPose;
class hkaAnimationBinding;

extern const hkClass hkaSkeletonMapperClass;

/// This run-time class converts a pose from one skeleton (A) to another (B). The poses can be specified by either hkaPose objects or arrays of transforms.
/// It uses mapping data (hkaSkeletonMapperData), which can be created using the hkaSkeletonMapperUtils utility class.
class hkaSkeletonMapper : public hkReferencedObject
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_ANIM_RIG );
		HK_DECLARE_REFLECTION();

			/// Constructor - Takes mapping data as a parameter; this data can be created using the hkaSkeletonMapperUtils class.
		hkaSkeletonMapper( const hkaSkeletonMapperData& mapping );

			/// Destructor
		virtual ~hkaSkeletonMapper();

			/// Constraints source.
		enum ConstraintSource
		{
				/// No constraints
			NO_CONSTRAINTS,
				/// Reference pose
			REFERENCE_POSE,
				/// Current pose
			CURRENT_POSE
		};

			/// Maps a pose from one skeleton to another, matching model space configurations.
			/// Used for mapping the pose between ragdoll and hi-res skeletons
			/// \param poseAModelSpace      The poseA in model space. The number of elements must be equal to mapping.m_skeletonA->m_numBones
			/// \param originalPoseBLocalSpace The poseB in local space. The number of elements must be equal to mapping.m_skeletonB->m_numBones.
			///                                This pose is used as an additional input to calculate output bones which do
			///                                not map simply to an input bone
			///                                like bones in the middle of a chain or unmapped bones.
			/// \param poseBModelSpaceInOut The output pose. The number of elements must be equal to mapping.m_skeletonB->m_numBones.
			///                             Typically for all mapped bones, this array is a simply output parameter. For unmapped bones
			///                             (especially the root bone), the output may be untouched
			/// \param source Chooses between no adjustment, using the reference pose or the current pose when adjusting bone lengths. Usually the current pose is the best choice.
		void HK_CALL mapPose(const hkQsTransform* poseAModelSpace, const hkQsTransform* originalPoseBLocalSpace, hkQsTransform* poseBModelSpaceInOut, ConstraintSource source ) const;


			/// Maps a pose from a skeleton to another in local space.
			/// Used for animation retargeting from one skeleton to another
			/// \param poseALocalSpace      The poseA in model space. The number of elements must be equal to mapping.m_skeletonA->m_numBones
			/// \param poseBLocalSpaceInOut The output pose. The number of elements must be equal to mapping.m_skeletonB->m_numBones. This pose should be initialized, as the transform of some of the bones in B may be used.  Should be initialized to the reference pose when used with retargeting.                             
		void HK_CALL mapPoseLocalSpace(	const hkQsTransform* poseALocalSpace, hkQsTransform* poseBLocalSpaceInOut, bool additive ) const;

			/// Maps a pose from a skeleton to another in local space.
			/// Used for animation retargeting from one skeleton to another
			/// \param poseALocalSpace      The poseA in model space. The number of elements must be equal to mapping.m_skeletonA->m_numBones
			/// \param poseBLocalSpaceInOut The output pose. The number of elements must be equal to mapping.m_skeletonB->m_numBones. This pose should be initialized, as the transform of some of the bones in B may be used.  Should be initialized to the reference pose when used with retargeting.                             
			/// \param boneToTrackIndicesA	Optional mapping from bones to tracks (for sparse poses)
			/// \param boneToTrackIndicesB	Optional mapping from bones to tracks (for sparse poses)
			/// \param weightsA             The optional bone weights associated with poseA.
			/// \param weightsBOut          The optional bone weights associated with poseB.  The bone weights from weightsA will be mapped to weightsBOut. The weights of unmapped bones will be left unchanged in weightsBOut.
		void HK_CALL mapPoseLocalSpace(	const hkQsTransform* poseALocalSpace, hkQsTransform* poseBLocalSpaceInOut,
										const hkInt16* boneToTrackIndicesA, const hkInt16* boneToTrackIndicesB, bool additive,
										const hkReal* weightsA = HK_NULL, hkReal* weightsBOut = HK_NULL ) const;
		/// Maps a pose from a skeleton to another in local space.
		/// Used for animation retargeting from one skeleton to another
		/// \param poseALocalSpace      The poseA in model space. The number of elements must be equal to numBonesA
		/// \param poseBLocalSpaceInOut The output pose. The number of elements must be equal to numBonesB. This pose should be initialized, as the transform of some of the bones in B may be used.  Should be initialized to the reference pose when used with retargeting.
		/// \param partitionIndicesA	The partition indices corresponding to poseA.
		/// \param mapToFullPose		Whether the poses coming in and out are partial poses (need to map densely) or they are full poses (need to map sparsely)
		/// \param weightsA             The optional bone weights associated with poseA.
		/// \param weightsBOut          The optional bone weights associated with poseB.  The bone weights from weightsA will be mapped to weightsBOut. The weights of unmapped bones will be left unchanged in weightsBOut.
		void HK_CALL mapPoseLocalSpace(	const hkQsTransform* poseALocalSpace,
										hkQsTransform* poseBLocalSpaceInOut,
										const hkArray<hkInt16>& partitionIndicesA,
										bool additive,
										bool mapToFullPose = true,
										const hkReal* weightsA = HK_NULL, 
										hkReal* weightsBOut = HK_NULL ) const;

		/// Maps a pose from a skeleton to another in local space.
		/// Used for animation retargeting from one skeleton to another
		/// \param poseALocalSpace      The poseA in model space. The number of elements must be equal to mapping.m_skeletonA->m_numBones
		/// \param poseBLocalSpaceInOut The output pose. The number of elements must be equal to mapping.m_skeletonB->m_numBones. This pose should be initialized, as the transform of some of the bones in B may be used.  Should be initialized to the reference pose when used with retargeting.                             
		/// \param boneToTrackIndicesA	Optional mapping from bones to tracks (for sparse poses)
		/// \param boneToTrackIndicesB	Optional mapping from bones to tracks (for sparse poses)
		/// \param partitionIndicesA	The partition indices corresponding to poseA.
		/// \param mapToFullPose		Whether the poses coming in and out are partial poses (need to map densely) or they are full poses (need to map sparsely)
		/// \param weightsA             The optional bone weights associated with poseA.
		/// \param weightsBOut          The optional bone weights associated with poseB.  The bone weights from weightsA will be mapped to weightsBOut. The weights of unmapped bones will be left unchanged in weightsBOut.
		void HK_CALL mapPoseLocalSpace(	const hkQsTransform* poseALocalSpace, 
										hkQsTransform* poseBLocalSpaceInOut,
										const hkInt16* boneToTrackIndicesA, 
										const hkInt16* boneToTrackIndicesB,
										const hkArray<hkInt16>& partitionIndicesA,
										bool additive,
										bool mapToFullPose = true,
										const hkReal* weightsA = HK_NULL, 
										hkReal* weightsBOut = HK_NULL ) const;

			/// Maps a pose from one skeleton to another, using hkaPose objects.
			/// May be used for either Ragdoll mapping, or animation retargeting
			/// \param poseAIn    The input pose. The skeleton of poseAIn should be the same skeleton as m_mapping.m_skeletonA
			/// \param poseBInOut The output pose. This pose should be initialized, as the transform of some of the bones in B may be used. Should be initialized to the reference pose when used with retargeting.
			///                   The skeleton of poseBInOut should be the same skeleton as in m_mapping.m_skeletonB
			/// \param source     Chooses between no adjustment, using the reference pose or the current pose when adjusting bone lengths. Usually the current pose is the best choice.
		void HK_CALL mapPose(const hkaPose& poseAIn, hkaPose& poseBInOut, ConstraintSource source = NO_CONSTRAINTS ) const;


			/// Maps the extracted motion from one character to another.
			/// Needed for animation retargeting only
		void HK_CALL mapExtractedMotion( const hkQsTransform& deltaMotionIn, hkQsTransform& deltaMotionOut ) const;

			/// This function creates additional binding information
			/// needed when retargeting partial (sparse) animations.
			/// Given an animation intended for skeletonA (src), the
			/// m_transformTrackToBoneIndices are inverted to form
			/// boneToTrack indices. Additionally trackToBone and
			/// boneToTrack indices are created for skeletonB (dst)
			/// using the mapping from the hkaSkeletonMapperData.
			/// Unmapped bones and incomplete chains in skeletonA
			/// are culled from the dst arrays.
		void initializeBindingMaps( const hkaAnimationBinding* binding, hkArray< hkInt16 >& srcBoneToTrackIndicesOut, hkArray< hkInt16 >& dstBoneToTrackIndicesOut, hkArray< hkInt16 >& dstTrackToBoneIndicesOut ) const;
	

			/// The following utility functions typically do not need to be
			/// called directly by the user. They are needed internally for
			/// animation retargeting.
			///
			/// These utilities combine an additive pose with the
			/// reference pose, and extract an additive pose from a
			/// combined one, respectively. The additive pose may
			/// be full, or sparse. Sparse poses must specify the
			/// boneToTrack mapping; full poses may leave this null.
		static void combinedPoseFromAdditivePoseAndReferencePose( const hkQsTransform* additivePose, const hkQsTransform* referencePose, const hkInt16* boneToTrackIndices, hkInt32 startBoneIndex, hkInt32 numBones, hkQsTransform* combinedPoseOut );
		static void additivePoseFromCombinedPoseAndReferencePose( const hkQsTransform* combinedPose, const hkQsTransform* referencePose, const hkInt16* boneToTrackIndices, hkInt32 startBoneIndex, hkInt32 numBones, hkQsTransform* additivePoseOut );
	
			/// Lower level worker function that implements both
			/// combinedPoseFromAdditivePoseAndReferencePose or
			/// additivePoseFromCombinedPoseAndReferencePose
		static void combineSparsePoseWithFullPose( const hkQsTransform* sparsePose, const hkQsTransform* fullPose, const hkInt16* sparsePoseBoneToTrackIndices, hkInt32 startBoneIndex, hkInt32 numBones, hkQsTransform* sparseMulFull_sparseOut );


	public:

			/// The mapping data
		class hkaSkeletonMapperData m_mapping;

	public:

			/// Intended for DEBUG builds only - Checks the mapping
			/// data and generates HK_WARN errors for troublesome
			/// mappings; called by the constructor in DEBUG.
		static void HK_CALL checkMapping(const hkaSkeletonMapperData& mapping);	
		static void HK_CALL checkMappingLocalSpace(const hkaSkeletonMapperData& mapping);
		static bool HK_CALL checkTransform( hkaSkeletonMapperData::MappingType type, const hkQsTransform& q );

	private:

			/// Utility function called from mapPoseLocalSpace	
		static void HK_CALL mapPoseLocalSpaceInternal(	const hkaSkeletonMapperData& mapping,
														const hkQsTransform* poseALocalSpaceOriginal, 
														hkQsTransform* poseBLocalSpaceInOut,
														const hkInt16* boneToTrackIndicesA, 
														const hkInt16* boneToTrackIndicesB,
														const hkArray<hkInt16>& partitionIndicesA,
														bool additive,
														bool mapToFullPose,
														const hkReal* weightsA, 
														hkReal* weightsBOut );

		/*HK_FORCE_INLINE*/ static void setMulWithScaling( hkaSkeletonMapperData::MappingType type, hkQsTransform& dst, const hkQsTransform &t1, const hkQsTransform &t2 );

	public:

		hkaSkeletonMapper( hkFinishLoadedObjectFlag f ) : hkReferencedObject(f), m_mapping(f) { }
};


#endif // HK_SKELETON_MAPPER_H

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
