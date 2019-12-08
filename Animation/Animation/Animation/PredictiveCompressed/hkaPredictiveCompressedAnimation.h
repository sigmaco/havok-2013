/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_ANIMATION_PREDICTIVE
#define HK_ANIMATION_PREDICTIVE

#include <Animation/Animation/Animation/hkaAnimation.h>
#include <Animation/Animation/Animation/hkaAnimationBinding.h>
#include <Animation/Animation/Animation/Interleaved/hkaInterleavedUncompressedAnimation.h>
#include <Animation/Internal/Compression/Predictive/hkaPredictiveBlockCompression.h>
#include <Animation/Animation/Rig/hkaSkeleton.h>

namespace hkaPredictiveCompressedAnimationUtil
{
	// Utilities, defined in implementation files
	class TrackDecompressor;
	class Range;
}

/// Use Manhattan-norm normalised quaternions. Faster restoration during decompression, somewhat less accurate inter-frame interpolation
#define HK_PREDICTIVE_QUATERNION_MANHATTAN

class hkaPredictiveCompressedAnimation : public hkaAnimation
{
	//+version(1)

	friend class hkaPredictiveCompressedAnimationUtil::TrackDecompressor;
	friend class hkaPredictiveCompressedAnimationUtil::Range;

	public:
		HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_ANIM_COMPRESSED );
		HK_DECLARE_REFLECTION();

		// Static and dynamic tolerances may be given: the dynamic tolerance gives the maximum acceptable error in a decoded
		// channel. Higher tolerances will allow better compression but result in uglier animations. The static tolerance should
		// be >= dynamic tolerance. The entire channel will be encoded as constant if it can be done with a maximum error of at
		// most the static tolerance.
		// The quantization is never more accurate than an error of 2^-15 * (span of the channel), since the values are quantized
		// to 14 bits. If a tolerance of less than this is specified, it will be silently rounded up. Therefore, maximum fidelity
		// is achieved by setting all the tolerances to 0.

			/// A single set of compression parameters.
		struct TrackCompressionParams
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_ANIM_COMPRESSED, hkaPredictiveCompressedAnimation::TrackCompressionParams );
			HK_DECLARE_REFLECTION();

				/// Construct using default tolerances.
			TrackCompressionParams();

			hkReal m_staticTranslationTolerance;
			hkReal m_staticRotationTolerance;
			hkReal m_staticScaleTolerance;
			hkReal m_staticFloatTolerance;
			hkReal m_dynamicTranslationTolerance;
			hkReal m_dynamicRotationTolerance;
			hkReal m_dynamicScaleTolerance;
			hkReal m_dynamicFloatTolerance;
		};
		
			/// Compression parameters for all tracks using a palette.  By default there is one palette entry with default tolerances for all bones and float tracks.
		struct CompressionParams
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_ANIM_COMPRESSED,hkaPredictiveCompressedAnimation::CompressionParams);

				/// Create a single palette entry for all bones and floats, using default tolerances.
			CompressionParams();

				/// Create a single palette entry for all bones and floats, using the given tolerances.
			CompressionParams(	hkReal staticTranslationTolerance, hkReal staticRotationTolerance, hkReal staticScaleTolerance, hkReal staticFloatTolerance,
								hkReal dynamicTranslationTolerance, hkReal dynamicRotationTolerance, hkReal dynamicScaleTolerance, hkReal dynamicFloatTolerance );

			hkReal getStaticTranslationTolerance(int transformTrack) const;
			hkReal getStaticRotationTolerance(int transformTrack) const;
			hkReal getStaticScaleTolerance(int transformTrack) const;
			hkReal getStaticFloatTolerance(int floatTrack) const;

			hkReal getDynamicTranslationTolerance(int transformTrack) const;
			hkReal getDynamicRotationTolerance(int transformTrack) const;
			hkReal getDynamicScaleTolerance(int transformTrack) const;
			hkReal getDynamicFloatTolerance(int floatTrack) const;

			/// List of CompressionParams to enable per-bone compression settings
			hkArray< hkaPredictiveCompressedAnimation::TrackCompressionParams > m_parameterPalette;

			/// An array of indices into the palette above 
			hkArray< hkUint32 > m_trackIndexToPaletteIndex;
			hkArray< hkUint32 > m_floatTrackIndexToPaletteIndex;

		private:

			hkUint32 getTransformTrackPaletteIndex(int bone) const;
			hkUint32 getFloatTrackPaletteIndex(int flt) const;

			// discourage copying
			CompressionParams(const CompressionParams& c) {}
		};

	public:

		/// Construct by compressing an existing animation using default parameters.
		hkaPredictiveCompressedAnimation(const hkaAnimationBinding& binding, const hkaSkeleton& skeleton);

		/// Construct by compressing an existing animation using given tolerances.
		hkaPredictiveCompressedAnimation(const hkaAnimationBinding& binding, const hkaSkeleton& skeleton, const CompressionParams& params);

		hkaPredictiveCompressedAnimation(hkFinishLoadedObjectFlag flag);

		///////////////////////////
		// hkaAnimation interface
		///////////////////////////

			// hkaAnimation interface implementation
		virtual void sampleTracks(hkReal time, hkQsTransform* transformTracksOut, hkReal* floatTracksOut) const HK_OVERRIDE;

			// hkaAnimation interface implementation
		virtual void sampleIndividualTransformTracks( hkReal time, const hkInt16* tracks, hkUint32 numTracks, hkQsTransform* transformOut ) const HK_OVERRIDE;

			// hkaAnimation interface implementation
		virtual void sampleIndividualFloatTracks( hkReal time, const hkInt16* tracks, hkUint32 numTracks, hkReal* out ) const HK_OVERRIDE;

			// hkaAnimation interface implementation
		virtual int getNumOriginalFrames() const HK_OVERRIDE;

			// hkaAnimation interface implementation
		virtual int getNumDataChunks(hkUint32 frame, hkReal delta) const HK_OVERRIDE;

			// hkaAnimation interface implementation
		virtual void getDataChunks(hkUint32 frame, hkReal delta, DataChunk* dataChunks, int m_numDataChunks) const HK_OVERRIDE;

			// hkaAnimation interface implementation
		virtual int getMaxSizeOfCombinedDataChunks() const HK_OVERRIDE;

			// hkaAnimation interface implementation
		virtual int getMaxDecompressionTempBytes() const HK_OVERRIDE;

			// hkaAnimation interface implementation
		virtual bool requiresSkeleton() const HK_OVERRIDE;

			// hkaAnimation interface implementation
		virtual const hkaSkeleton* getSkeleton() const HK_OVERRIDE;

			// hkaAnimation interface implementation
		virtual void setSkeleton( const hkaSkeleton* skeleton ) HK_OVERRIDE;

	public:

			/// Used for SPU deserialization
		void recoverChunkData(const DataChunk* chunks, int numChunks);

		void sampleFullPose( hkQsTransform* bones, hkReal* floats, hkReal time) const;

		void sampleFullPose(	hkUint32 frameIndex, hkReal frameDelta,
								const hkUint8* compressedData, 
								const hkQsTransform* refBones, const hkReal* refFloats,
								int numBones, int numFloats,
								hkQsTransform* bonesOut, hkReal* floatsOut,
								hkUint8* boneWeightsInOut, hkUint8* floatWeightsInOut ) const;

			/// Gets the total size in bytes of the compressed animation.
		int getSizeInBytes() const;

			/// Get a subset of the tracks a given time using data chunks. Sample is calculated using pose[frameIndex] * (1 - frameDelta) + pose[frameIndex+1] * frameDelta.
		static void HK_CALL samplePartialWithDataChunks(	int frameIndex, hkReal frameDelta,
															int numTransformTracks, int numFloatTracks,
															const hkQsTransform* referenceBones, const hkReal* referenceFloats,
															const DataChunk* chunks, int numChunks,
															hkQsTransform* transformTracksOut, hkReal* floatTracksOut );

			/// Gets the number of bones in the skeleton used to create the animation.
		hkInt32 getNumBones() const;

			/// Gets the number of float slots in the skeleton used to create the animation.
		hkInt32 getNumFloatSlots() const;

	private:

		// Construct a predictive animation. Defined in hkaPredictiveCompressedAnimationCtor.cpp
		void build(const hkaAnimationBinding& binding, const hkaSkeleton& skeleton, const CompressionParams& params);

		// Computes the maximum amount of compressed data for any frame in the animation.
		void computeMaxCompressedBytesPerFrame();

		enum StorageClass
		{
			STORAGE_STATIC			= 0, // value is constant throughout the animation, value is stored in m_staticTracks
			STORAGE_REFERENCE		= 1, // value is the same as reference pose and not stored
			STORAGE_DYNAMIC_RANGE	= 2, // value varies, range is stored in m_rangeEndpoints and quantized values are stored
			STORAGE_DYNAMIC_FIXED	= 3, // value varies, range is assumed to be +/- 1 and quantized values are stored
		};

		static int storageIsDynamic(StorageClass x);

		enum IntArrayID
		{
			BLOCK_OFFSETS,
			// When decompressing less that the total number of bones for LOD we need to be
			// able to jump to the first block that contains the float tracks.
			// These offsets are to the start of the first block containing floats,
			// and are relative to the previous element of BLOCK_OFFSETS.
			FIRST_FLOAT_BLOCK_OFFSETS,
			IS_ANIMATED_BITMAP,
			IS_FIXED_RANGE_BITMAP,
			DYNAMIC_BONE_TRACK_INDEX,
			DYNAMIC_FLOAT_TRACK_INDEX,
			STATIC_BONE_TRACK_INDEX,
			STATIC_FLOAT_TRACK_INDEX,
			RENORM_QUATERNION_INDEX,

			NUM_INT_ARRAYS
		};

		// Returns the starting and ending offsets in m_compressedData for the data for a given frame.
		void getCompressedDataOffset(hkUint32 frame, hkUint32& start, hkUint32& end) const;

		// Returns the offset in m_compressedData for the first block containing float tracks, relative to the start of
		// the compressed data for this column of blocks.
		hkUint32 getCompressedDataOffsetForFirstFloatBlock(hkUint32 frame) const;

		// Offsets of the first block of each frame, and the end of the data
		// An animation of 32 dynamic channels and 32 frames will be encoded
		// as 4 blocks. m_blockOffsets will have 2 entries, such that 
		// m_blockOffsets[0], m_blockOffsets[1] gives the compressed data for
		// the first 16 frames (2 blocks).

		// Given the index of a column of blocks (ie, frame/16), returns the block offset.
		// The template parameter can be BLOCK_OFFSETS or FIRST_FLOAT_BLOCK_OFFSETS.
		template<IntArrayID intArrayId>
		hkUint32 getBlockOffset(int blockColumnIndex) const;

		enum FloatArrayID
		{
			STATIC_VALUES,
			DYNAMIC_SCALES,
			DYNAMIC_OFFSETS,

			NUM_FLOAT_ARRAYS
		};

		const hkUint16* getArray(IntArrayID x) const;
		const hkReal* getArray(FloatArrayID x) const;
		int getArrayLength(IntArrayID x) const;
		int getArrayLength(FloatArrayID x) const;

		void addArray(const hkArrayBase<hkUint16>&, IntArrayID);
		void addArray(const hkArrayBase<hkReal>&, FloatArrayID);

		hkArray<hkUint8> m_compressedData;

		// isAnimated bitmap, isFixedRange bitmap, isDynamic bitmap
		hkArray<hkUint16> m_intData;
		hkInt32 m_intArrayOffsets[NUM_INT_ARRAYS];

		hkArray<hkReal> m_floatData;
		hkInt32 m_floatArrayOffsets[NUM_FLOAT_ARRAYS];

		hkInt32 m_numBones;
		hkInt32 m_numFloatSlots;
		hkInt32 m_numFrames;

		// When doing LOD we need to be able to quickly jump to the correct data to decompress the float tracks
		// after having decompressed only some of the bone tracks.  This is the offset into the DYNAMIC_SCALES and DYNAMIC_OFFSETS
		// arrays that correspond the the start of the first block that contains any float tracks.
		hkInt32 m_firstFloatBlockScaleAndOffsetIndex;

		/// Associated skeleton.  You must set this if you want to call any of the decompression interfaces that do not provide a reference pose.
		const hkaSkeleton* m_skeleton; //+nosave
		hkInt32 m_maxCompressedBytesPerFrame; //+nosave
};

#include <Animation/Animation/Animation/PredictiveCompressed/hkaPredictiveCompressedAnimation.inl>

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
