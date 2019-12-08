/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_ANIMATION_BLEND_H
#define HK_ANIMATION_BLEND_H

namespace hkaBlend
{
// Used for constructing something analogous to a linear combination of poses
// This can be thought of as base := base + sample * sampleW * sampleAlpha
// and for float data, it is. For general poses, the calculations are a little
// more complex, but it can still be used to take a weighted average of poses
// in a way analogous to the operations on vectors.
// sampleW is a per-track weight, and sampleAlpha is a single global alpha
// The template parameter indicates which operations are performed:
//  If BLEND_USE_BASE is not specified, base is assumed to be zero and not blended
//         (useful for initialization, etc.)
//  If BLEND_USE_SAMPLE_WEIGHT is not specified, sampleW is assumed to be 1 everywhere
//  If BLEND_USE_SAMPLE_ALPHA is not specified, sampleAlpha is assumed to be 1.
// At least one of BLEND_USE_SAMPLE_ALPHA and BLEND_USE_SAMPLE_WEIGHT must be specified.
// Specifying all options is the most general function, but using only the necessary
// ones will be faster. Type must be hkReal or hkQsTransform.
// This function is alias-safe (base == sample is OK), but not overlap-safe.
enum {BLEND_USE_BASE=1, BLEND_USE_SAMPLE_WEIGHT=2, BLEND_USE_SAMPLE_ALPHA=4};
template <class Type, int flags>
void HK_CALL blendAddMul(
	Type* base, hkReal* baseW, // accumulator
	const Type* sample, const hkReal* sampleW, hkSimdRealParameter sampleAlpha, // new pose
	int n); // length

// Similar to the above but for additive animations.  Unlike the above, this one does not need to accumulate the weights because they are not needed.
template <class Type, int flags>
void HK_CALL blendAdditive(
	Type* base,
	const Type* sample, const hkReal* sampleW, hkSimdRealParameter sampleAlpha, // new pose
	int n); // length

// After using blendAddMul to combine animations, the resulting pose must be
// normalized before it can be drawn. This is analogous to the division step
// after taking a weighted average. Type must be hkReal or hkQsTransform.
template <class Type>
inline void blendNormalize(Type* transforms, hkReal* weights, int n);
}

#include <Animation/Animation/Playback/SampleAndBlend/hkaBlend.inl>

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
