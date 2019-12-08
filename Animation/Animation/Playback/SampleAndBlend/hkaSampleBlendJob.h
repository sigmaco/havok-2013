/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKA_SAMPLE_BLEND_JOB_H
#define HKA_SAMPLE_BLEND_JOB_H

#include <Animation/Animation/Animation/Mirrored/hkaMirroredSkeleton.h>
#include <Animation/Animation/Animation/PredictiveCompressed/hkaPredictiveCompressedAnimation.h>
#include <Animation/Animation/Animation/Quantized/hkaQuantizedAnimation.h>
#include <Animation/Animation/Animation/SplineCompressed/hkaSplineCompressedAnimation.h>
#include <Animation/Animation/Playback/hkaAnimatedSkeleton.h>
#include <Animation/Animation/Playback/Control/hkaAnimationControl.h>
#include <Animation/Animation/Playback/Multithreaded/hkaJobDoneNotifier.h>
#include <Animation/Animation/Playback/Multithreaded/Common/hkaCommonAnimation.h>
#include <Animation/Animation/Playback/Utilities/hkaBlender.h>
#include <Common/Base/Thread/JobQueue/hkJobQueue.h>

class hkaPose;

class hkaSampleBlendJob : public hkJob
{
public:

	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_ANIMATION, hkaSampleBlendJob);

	/// Represents a single hkaAnimationControl to be sampled and blended
	struct SingleAnimation
	{
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_ANIMATION, hkaSampleBlendJob);

		void build(const hkaSkeleton& skeleton, const hkaAnimationControl& control, int& maxChunkBytesInOut);

		void build(	const hkaSkeleton& skeleton,
					const hkaAnimation& anim,
					hkReal localTime,
					hkQsTransform* bonesOut,
					hkReal* floatSlotsOut,
					const hkaAnimationBinding* binding,
					const hkaSkeletonMapper* mapper,
					const hkArray<hkUint8>* perBoneWeights,
					const hkArray<hkUint8>* perFloatWeights,
					int& maxChunkBytesInOut );

		/// first frame to blend (local time of animation rounded down to a frame boundary)
		hkUint32 m_frameIndex;
		/// delta in [0,1) showing what point between frame (m_frameIndex) and frame (m_frameIndex+1)
		/// should be interpolated.
		hkReal m_frameDelta;

		/// degree to which this animation contributes to final pose. Applied equally to all bones/floats
		hkReal m_weight;

		hkaAnimation::AnimationType m_type;

		// Regular animations require at most 4 chunks (interleaved=3, spline=3, quantized=3, predictive=4).
		// Mirrored animations require an additional 6.
		// Weights and bindings require 4.
		// Skeleton mapper requires 6.
		enum 
		{
			MAX_ANIMATION_CHUNKS = 11,
			MAX_NUM_CHUNKS = 21
		};
		hkaAnimation::DataChunk m_chunks[MAX_NUM_CHUNKS];
		hkInt32 m_numChunks;

		enum SampleFlags
		{
			HAS_BONE_WEIGHTS=1, 
			HAS_FLOAT_WEIGHTS=2,
			HAS_BONE_BINDING=4,
			HAS_FLOAT_BINDING=8,
			HAS_MAPPER=16,
			BLENDMODE_ADDITIVE=32,
			HAS_PARTITIONS = 64,
		};
		hkFlags<SampleFlags, hkInt32> m_flags;

			/// These are used when retargeting, since the other skeleton may have a different number of bones and floats.
		hkInt32 m_numBones;
		hkInt32 m_numFloats;

			/// This should be set if you want the pose for this animation to be DMAed back.
		hkQsTransform* m_bonesOut;

			/// This should be set if you want the floats for this animation to be DMAed back.
		hkReal* m_floatsOut;

			/// The pointer to the partitions on the heap
		hkaSkeleton::Partition* m_partitionArray;

			/// The number of partitions in this animation
		hkInt16 m_numPartitions;
	};

	/// Initialize the job to sample and blend an hkaAnimatedSkeleton.
	/// The output buffers bonesOut and floatsOut must point to enough memory for HK_NEXT_MULTIPLE_OF(4,numBones)
	/// and HK_NEXT_MULTIPLE_OF(4,numFloats), respectively.
	/// The extra elements may be overwritten by garbage during blend.
	/// If numBones or numFloats are not -1 then they indicate how many bones and floats to sample.  If they are -1 then all of the bones and floats are sampled.
	void build(const hkaAnimatedSkeleton* skel, hkQsTransform* bonesOut, hkReal* floatsOut, bool convertToModel = false, int numBones = -1, int numFloats = -1);

	/// Initialize the job to sample and blend an hkaAnimatedSkeleton into an hkaPose.
	/// If numBones or numFloats are not -1 then they indicate how many bones and floats to sample.  If they are -1 then all of the bones and floats are sampled.
	void build(const hkaAnimatedSkeleton* skel, hkaPose* pose, bool convertToModel = false, int numBones = -1, int numFloats = -1);

	/// Call this to start building a job to sample animations without blending them.
	/// You should provide the maximum number of animations the job may process in numAnimations.
	/// The animations must share a common skeleton, which you must pass in.
	/// If you want to convert the poses to model space you may pass in true for convertToModel.
	/// If numBones or numFloats are not -1 then they indicate how many bones and floats to sample.  If they are -1 then all of the bones and floats are sampled.
	void initSampleOnly( int numAnimations, const hkaSkeleton& skeleton, bool convertToModel = false, int numBones = -1, int numFloats = -1 );

	/// Call this after initSampleOnly() to add each animation that you want to decompress.
	/// The output buffers bonesOut and floatsOut must point to enough memory for HK_NEXT_MULTIPLE_OF(4,numBones)
	/// and HK_NEXT_MULTIPLE_OF(4,numFloats), respectively.
	/// The extra elements may be overwritten by garbage during blend.
	/// You can optionally provide a binding for converting to bone space and a mapper for retargeting the animation.
	void addAnimation(	const hkaSkeleton& skeleton,
						const hkaAnimation& anim,
						hkReal localTime,
						hkQsTransform* bonesOut,
						hkReal* floatsOut,
						const hkaAnimationBinding* binding = HK_NULL,
						const hkaSkeletonMapper* mapper = HK_NULL );

public:

	/// deallocate any memory still held by the job
	void destroy();


	hkaSampleBlendJob()
			: hkJob( HK_JOB_TYPE_ANIMATION_SAMPLE_AND_BLEND, 0, sizeof(*this), HK_JOB_SPU_TYPE_DISABLED )
	{
		m_skel = HK_NULL;
		m_referenceBones = HK_NULL;
		m_referenceFloats = HK_NULL;
		m_bones = HK_NULL;
		m_parentIndices = HK_NULL;
		m_animations = HK_NULL;
		m_bonesOut = HK_NULL;
		m_floatsOut = HK_NULL;
		m_numBones = 0;
		m_numSkeletonBones = 0;
		m_numFloats = 0;
		m_chunkBufferSize = 0;
		m_referencePoseWeightThreshold = 0.0f;
		m_numAnimationsAllocated = 0;
		m_numAnims = 0;
		m_convertToModel = false;
		m_sampleOnly = false;
		m_useSlerpForQuantized = false;
	}

	hkaSampleBlendJob(const hkaAnimatedSkeleton* skel, hkQsTransform* bonesOut, hkReal* floatOut, bool convertToModel = false, int numBones = -1, int numFloats = -1)
			: hkJob( HK_JOB_TYPE_ANIMATION_SAMPLE_AND_BLEND, 0, sizeof(*this), HK_JOB_SPU_TYPE_DISABLED )
	{
		m_skel = HK_NULL;
		m_referenceBones = HK_NULL;
		m_referenceFloats = HK_NULL;
		m_bones = HK_NULL;
		m_parentIndices = HK_NULL;
		m_animations = HK_NULL;
		m_bonesOut = HK_NULL;
		m_floatsOut = HK_NULL;
		m_numBones = 0;
		m_numSkeletonBones = 0;
		m_numFloats = 0;
		m_chunkBufferSize = 0;
		m_referencePoseWeightThreshold = 0.0f;
		m_numAnimationsAllocated = 0;
		m_numAnims = 0;
		m_convertToModel = false;
		m_sampleOnly = false;
		m_useSlerpForQuantized = false;

		build(skel, bonesOut, floatOut, convertToModel, numBones, numFloats);
	}

	~hkaSampleBlendJob()
	{
		destroy();
	}

	/// skeleton being sampled
	const hkaAnimatedSkeleton* m_skel;

	/// reference pose (bones)
	const hkQsTransform* m_referenceBones;

	/// reference pose (floats)
	const hkReal* m_referenceFloats;

	// the bones from the skeleton (needed only if retargeting)
	const hkaBone* m_bones;

	/// parent indices if converting to model coordinates or retargeting, HK_NULL otherwise
	const hkInt16* m_parentIndices;

	/// Information about the animations being sampled.
	SingleAnimation* m_animations;

	/// output pose (bones). May be HK_NULL, when numBones is 0.
	hkQsTransform* m_bonesOut;

	/// output pose (floats). May be HK_NULL, when numFloats is 0.
	hkReal* m_floatsOut;

	/// Notifies via a semaphore or bool when the job is done.
	hkaJobDoneNotifier m_jobDoneNotifier;

	/// number of bones to sample. May be less than the number of bones in the skeleton for LOD sampling
	hkInt16 m_numBones;

	/// number of bones to sample. May be less than the number of bones in the skeleton for LOD sampling
	hkInt16 m_numSkeletonBones;

	/// number of floats to sample. May be less than the number of bones in the skeleton for LOD sampling
	int m_numFloats;

	/// maximum amount of data to DMA for any individual animation
	int m_chunkBufferSize;

	/// If a bone weight falls below this threshold the reference pose is blended in.
	hkReal m_referencePoseWeightThreshold;

	/// The size of m_animations.
	hkUint16 m_numAnimationsAllocated;

	/// The number of animations in m_animations.
	hkUint16 m_numAnims;

	/// Whether to convert the outputs to model space.
	hkBool m_convertToModel;

	/// Whether this job represents a blend or just animation sampling.
	hkBool m_sampleOnly;

	/// Whether to use slerp to interpolate quaternions when an animation is quantized.  Otherwise, linear interpolation is used.
	hkBool m_useSlerpForQuantized;
};

/// Sample and blend some animations. This function may be called directly (for single-threaded CPU sampling), or
/// will be called internally if job queues are used.
void HK_CALL executeSampleBlendJob(const hkaSampleBlendJob& job);

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
