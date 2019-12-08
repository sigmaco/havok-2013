/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKANIMATION_ANIMATION_HKMIRROREDSKELETALANIMATION_XML_H
#define HKANIMATION_ANIMATION_HKMIRROREDSKELETALANIMATION_XML_H

#include <Animation/Animation/Animation/hkaAnimation.h>
#include <Common/Base/Math/Util/hkConvertCoordinateSpace.h>

class hkaAnimationBinding;
class hkaMirroredSkeleton;

	/// This class allows the user to wrap a child animation and 'mirror' it at runtime, so that
	/// for example the data for a single 'turn left' animation can be (re)used for both 'turn left' and turn right'
	/// runtime playback. Please see the userguide section "Mirroring Animations" for more details.
class hkaMirroredAnimation : public hkaAnimation
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_ANIM_COMPRESSED );

			/// Constructor for hkaMirroredAnimation
			/// \param originalAnimation Animation to mirror
			/// \param originalBinding Binding for the original animation
			/// \param mirroredSkeleton Mirrored skeleton
		hkaMirroredAnimation( const hkaAnimation* originalAnimation,
									 const hkaAnimationBinding* originalBinding,
									 const hkaMirroredSkeleton* mirroredSkeleton );

		~hkaMirroredAnimation();

			/// Create a *new* binding appropriate for this mirrored animation. Deletion must be handled by the user.
			/// \return A new binding appropriate for this mirrored animation.
		hkaAnimationBinding *createMirroredBinding();


		/// Destroy an hkaAnimationBinding created by the createMirroredBinding member function
		/// \param bind Binding to destroy
		static void HK_CALL destroyMirroredBinding( hkaAnimationBinding *binding );

		/// Return original binding
		const hkaAnimationBinding* getOriginalBinding() const;

		// INHERITED FUNCTIONS
		
		virtual void sampleTracks(hkReal time, hkQsTransform* tracksOut, hkReal* floatTracksOut) const HK_OVERRIDE;
			
			/// Get a subset of the first 'maxNumTracks' tracks of a pose at a given time (all tracks from 0 to maxNumTracks-1 inclusive).
		virtual void samplePartialTracks(hkReal time, hkUint32 maxNumTransformTracks, hkQsTransform* transformTracksOut, hkUint32 maxNumFloatTracks, hkReal* floatTracksOut) const HK_OVERRIDE;

			/// Sample individual animation tracks
		virtual void sampleIndividualTransformTracks( hkReal time, const hkInt16* tracks, hkUint32 numTracks, hkQsTransform* transformOut ) const HK_OVERRIDE;

			/// Sample individual floating tracks
		virtual void sampleIndividualFloatTracks( hkReal time, const hkInt16* tracks, hkUint32 numTracks, hkReal* out ) const HK_OVERRIDE;


		/// Returns the number of original samples / frames of animation
		virtual int getNumOriginalFrames() const HK_OVERRIDE;

			/// Return the number of chunks of data required to sample a pose at time t
		virtual int getNumDataChunks(hkUint32 frame, hkReal delta) const HK_OVERRIDE;

			/// Return the maximum total size of all combined chunk data which could be returned by getDataChunks for this animation.
		virtual int getMaxSizeOfCombinedDataChunks() const HK_OVERRIDE;

			/// Return the chunks of data required to sample a pose at time t
		virtual void getDataChunks(hkUint32 frame, hkReal delta, DataChunk* dataChunks, int numDataChunks) const HK_OVERRIDE;

			/// Returns the motion stored (previously extracted from the animation) at time t.
			/// This motion represents the absolute offset from the start of the animation.
		virtual void getExtractedMotionReferenceFrame(hkReal time, hkQsTransform& motionOut) const HK_OVERRIDE;
	
			/// Returns the change in reference frame between two times for extracted motion.
		virtual void getExtractedMotionDeltaReferenceFrame( hkReal time, hkReal nextTime, int loops, hkQsTransform& deltaMotionOut, hkReal cropStartAmount, hkReal cropEndAmount ) const HK_OVERRIDE;

			/// Get all annotations which occur between startTime and deltaTime
			/// \param annotations Must be pre-allocated to the appropriate size. See getNumAnnotations.
			/// \return The number of annotations found
		virtual hkUint32 getAnnotations( hkReal startTime, hkReal deltaTime, TrackAnnotation* annotationsOut, hkUint32 maxNumAnnotations = HK_INT32_MAX ) const HK_OVERRIDE;

	private:

		static const int NUM_EXTRA_CHUNKS = 7;

	public:

			/// Get the chunks for the child animation given the
			/// chunks for an hkaMirroredAnimation.
		static HK_FORCE_INLINE const DataChunk* getChildDataChunks( const DataChunk* dataChunks )
		{
			return dataChunks + NUM_EXTRA_CHUNKS;
		}

			/// Get the number of chunks used for the child animation given the
			/// number of chunks used for an hkaMirroredAnimation.
		static HK_FORCE_INLINE int getNumChildDataChunks( int numDataChunks )
		{
			return numDataChunks - NUM_EXTRA_CHUNKS;
		}

			/// Get a subset of the tracks at a given time using data chunks. Sample is calculated using pose[frameIndex] * (1 - frameDelta) + pose[frameIndex+1] * frameDelta.
		static void HK_CALL samplePartialWithDataChunks(	hkUint32 frameIndex, hkReal frameDelta,
															hkUint32 maxNumTransformTracks, hkUint32 maxNumFloatTracks,
															const hkQsTransform* referenceBones, const hkReal* referenceFloats,
															const DataChunk* dataChunks, int numDataChunks,
															hkQsTransform* transformTracksOut, hkReal* floatTracksOut );

			/// This is called when using jobs to decompress animation.  This function does not support Predictive or Quantized.
		static void HK_CALL samplePartialWithDataChunksDeprecated(	hkUint32 frameIndex, hkReal frameDelta,
																	hkUint32 maxNumTransformTracks, hkQsTransform* transformTracksOut,
																	hkUint32 maxNumFloatTracks, hkReal* floatTracksOut,
																	const DataChunk* dataChunks, int numDataChunks );

			/// This is called when using jobs to decompress animation.  This function should be called after calling samplePartialWithDataChunks.
		static void HK_CALL mirrorDataChunks( const DataChunk* dataChunks, hkUint32 maxNumTransformTracks, hkQsTransform* transformTracksOut );


	private:

			/// Mirror a pose in track space
			/// \param poseInOut Array of transforms
			/// \param n Maximum track to consider
			/// \param additive True if the animation is additive
		void mirrorTrackPose( hkQsTransform* poseInOut, int n, hkBool additive ) const;

			/// Mirror a pose of individual tracks in track space
			/// \param poseInOut Array of transforms
			/// \param trackIndices Array of track indices
			/// \param numTracks Number of tracks to consider
			/// \param additive True if the animation is additive
		void mirrorIndividualTrackPose( hkQsTransform* poseInOut, const hkInt16* trackIndices, hkUint32 numTracks, hkBool additive) const;

			/// Animation tracks which are to be mirrored
		const hkaAnimation *m_originalAnimation;

			/// Original binding
		const hkaAnimationBinding *m_originalBinding;

			/// Skeleton, used to compute the mirroring transforms
		const hkaMirroredSkeleton *m_mirroredSkeleton;

			/// This is a copy of original binding hint for easy DMAing ('Additive' animations mirror differently).
		hkBool m_originalIsAdditive;

			/// The number of partitionIndices in this animation (for easy DMA'ing)
		hkInt16 m_numPartitionIndices;
};

#endif // HKANIMATION_ANIMATION_HKMIRROREDSKELETALANIMATION_XML_H

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
