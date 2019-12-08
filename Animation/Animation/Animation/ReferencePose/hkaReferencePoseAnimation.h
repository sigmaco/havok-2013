/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_ANIMATION_REFERENCE_POSE
#define HK_ANIMATION_REFERENCE_POSE

#include <Animation/Animation/Animation/hkaAnimation.h>
#include <Animation/Animation/Rig/hkaSkeleton.h>

/// This is a simple animation type which simply returns the reference pose of the skeleton.
/// It is useful as a fallback in case other animations can't be loaded in time.
class hkaReferencePoseAnimation : public hkaAnimation
{
	public:
		HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_ANIM_UNCOMPRESSED );
		HK_DECLARE_REFLECTION();

			// Constructor creates a refpose animation from the provided skeleton.
			// If numTransformTracks and numFloatTracks are provided, they will be set for the animation
			// creating a partial animation (similar to calling samplePartialTracks with the provided
			// values).
		hkaReferencePoseAnimation(const hkaSkeleton& skeleton, int numTransformTracks = -1, int numFloatTracks = -1);

		///////////////////////////
		// hkaAnimation interface
		///////////////////////////

			// hkaAnimation interface implementation
		virtual void sampleTracks(hkReal time, hkQsTransform* transformTracksOut, hkReal* floatTracksOut) const HK_OVERRIDE;

			// hkaAnimation interface implementation
		virtual void samplePartialTracks( hkReal time,
										  hkUint32 maxNumTransformTracks, hkQsTransform* transformTracksOut,
										  hkUint32 maxNumFloatTracks, hkReal* floatTracksOut) const HK_OVERRIDE;

			// hkaAnimation interface implementation
		virtual void sampleIndividualTransformTracks( hkReal time, const hkInt16* tracks, hkUint32 numTracks, hkQsTransform* transformOut ) const HK_OVERRIDE;

			// hkaAnimation interface implementation
		virtual void sampleIndividualFloatTracks( hkReal time, const hkInt16* tracks, hkUint32 numTracks, hkReal* out ) const HK_OVERRIDE;

			// hkaAnimation interface implementation
		virtual int getNumOriginalFrames() const HK_OVERRIDE;

			// hkaAnimation interface implementation
		virtual bool requiresSkeleton() const HK_OVERRIDE;

			// hkaAnimation interface implementation
		virtual const hkaSkeleton* getSkeleton() const HK_OVERRIDE;

			// hkaAnimation interface implementation
		virtual void setSkeleton( const hkaSkeleton* skeleton ) HK_OVERRIDE;

			/// Gets the number of bones in the skeleton used to create the animation.
		hkInt32 getNumBones() const;

			/// Gets the number of float slots in the skeleton used to create the animation.
		hkInt32 getNumFloatSlots() const;

			// hkaAnimation interface implementation
		virtual int getNumDataChunks(hkUint32 frame, hkReal delta) const HK_OVERRIDE;

			// hkaAnimation interface implementation
		virtual void getDataChunks(hkUint32 frame, hkReal delta, DataChunk* dataChunks, int m_numDataChunks) const HK_OVERRIDE;

			// hkaAnimation interface implementation
		virtual int getMaxSizeOfCombinedDataChunks() const HK_OVERRIDE;
		
			/// Get a subset of the tracks a given time using data chunks.
		static void HK_CALL samplePartialWithDataChunks(int numTransformTracks, int numFloatTracks,
														const hkQsTransform* referenceBones, const hkReal* referenceFloats,
														const DataChunk* chunks, int numChunks,
														hkQsTransform* transformTracksOut, hkReal* floatTracksOut );

	private:

		hkRefPtr<const hkaSkeleton> m_skeleton;

	public:

		hkaReferencePoseAnimation(hkFinishLoadedObjectFlag flag)
			: hkaAnimation(flag), m_skeleton(flag) {}
};

#include <Animation/Animation/Animation/ReferencePose/hkaReferencePoseAnimation.inl>

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
