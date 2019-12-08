/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_PREDICTIVE_BLOCK_H
#define HK_PREDICTIVE_BLOCK_H

// Compression of 16x16 blocks of animation data
// Each block holds the values of 16 channels for 16 frames, quantized as 14-bit numbers.
// A channel is a single real-valued function, there are 9 channels per bone track (3 transform,
// 3 rotation and 3 position) and 1 per float track.

// To allow blending between two frames, the blocks overlap by one frame, so that only one
// block need be sampled even at block boundaries.

// This part of the compression is lossless, although the data must be lossily quantized to
// at most 14-bit precision before using it.


namespace hkaPredictiveBlockCompression
{


struct Block{

	// Size of a block
	enum{FRAMES=16, CHANNELS=16};

	// Largest and smallest acceptable values
	enum{MAX_CODEABLE = (1<<13)-1, MIN_CODEABLE=-(1<<13)};

	// Largest size of a block after compression (blocks can get slightly bigger)
	enum{MAX_COMPRESSED_SIZE = CHANNELS + (16 * FRAMES * CHANNELS) / 8};

	// Frame overlap between successive blocks
	enum{FRAME_OVERLAP = 1};

	HK_ALIGN16(hkInt16 data[CHANNELS][FRAMES]);
};


// Compress a block of data. Returns a pointer past the end of the compressed
// data. If less than an entire block is needed, nframes and nchannels may be
// less than Block::FRAMES and Block::CHANNELS. If so, the values of the uncoded
// channels/frames are undefined after decompression.
hkUint8* encodeBlock(Block* data, int nframes, int nchannels, hkUint8* out);

// Decompress a block of data. Returns a pointer past the end of the compressed data.
const hkUint8* decodeWholeBlock(const hkUint8* data, Block* block);

// Decompress a single frame (0 <= whichFrame < Block::FRAMES)
const hkUint8* decodeSingleFrame(const hkUint8* data, int whichFrame, hkInt16* frameData);

// Decompress a pair of adjacent frames, given by the number of the first one
// (0 <= whichFrame < Block::FRAMES - 1)
const hkUint8* decodeAdjacentFrames(const hkUint8* data, int whichFrame, hkInt16* frameData);


// Depending on CPU architecture, the above functions may dispatch either to the vector or scalar
// decoders.

// Figure out if the CPU has the features necessary for the vector decoder to be efficient
#if defined(HK_INT_VECTOR_NATIVE_MISALIGNED) && 	defined(HK_INT_VECTOR_NATIVE_BITSHIFT128) && 	defined(HK_INT_VECTOR_NATIVE_VARIABLESHIFT) && 	defined(HK_INT_VECTOR_NATIVE_VPERM) && 	defined(HK_INT_VECTOR_NATIVE_FLOATCONV)
#		define HK_PREDICTIVE_DEFAULT_DECODER VectorDecoder
#		define HK_PREDICTIVE_BUILD_VECTOR_DECODER
#else
#		define HK_PREDICTIVE_DEFAULT_DECODER ScalarDecoder
#endif



#ifdef HK_PREDICTIVE_BUILD_VECTOR_DECODER
namespace VectorDecoder
{
	const hkUint8* decodeSingleFrame(const hkUint8* data, int whichFrame, hkInt16* frameData);
	const hkUint8* decodeAdjacentFrames(const hkUint8* data, int whichFrame, hkInt16* frameData);
	const hkUint8* decodeWholeBlock(const hkUint8* data, Block* block);
}
#endif

namespace ScalarDecoder
{
	const hkUint8* decodeSingleFrame(const hkUint8* data, int whichFrame, hkInt16* frameData);
	const hkUint8* decodeAdjacentFrames(const hkUint8* data, int whichFrame, hkInt16* frameData);
	const hkUint8* decodeWholeBlock(const hkUint8* data, Block* block);
}

namespace ScalarEncoder
{
	hkUint8* encodeBlock(Block* data, int nframes, int nchannels, hkUint8* out);
}

}
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
