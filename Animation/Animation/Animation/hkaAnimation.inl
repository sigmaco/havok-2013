/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

HK_FORCE_INLINE hkaAnimation::hkaAnimation() : m_type(HK_UNKNOWN_ANIMATION)
{
	m_duration = 0.0f;
	m_numberOfTransformTracks = 0;
	m_numberOfFloatTracks = 0;
	m_extractedMotion = HK_NULL;
}

HK_FORCE_INLINE hkaAnimation::AnimationType hkaAnimation::getType() const
{
	return m_type;
}

HK_FORCE_INLINE void hkaAnimation::getFrameAndDelta( hkReal time, hkUint32& frameOut, hkReal& deltaOut ) const
{
	const hkUint32 maxFrameIndex = getNumOriginalFrames() - 1;
	
	const hkReal frameFloat = (m_duration > 0) ? (time / m_duration) * maxFrameIndex : 0;
	frameOut = static_cast<hkUint32>( frameFloat );

	// Handle any roundoff error: We are always interpolating between pose[frameOut] and pose[frameOut+1]
    if(frameOut > maxFrameIndex - 1)
	{
		frameOut = maxFrameIndex - 1;
		deltaOut = 1.0f;
		return;
	}

	deltaOut = hkMath::clamp(frameFloat - frameOut, hkReal(0.0f), hkReal(1.0f));
}

HK_FORCE_INLINE hkBool hkaAnimation::hasExtractedMotion() const
{
	return m_extractedMotion != HK_NULL;
}

HK_FORCE_INLINE void hkaAnimation::setExtractedMotion( const hkaAnimatedReferenceFrame* extractedMotion )
{
	m_extractedMotion = extractedMotion;
}

HK_FORCE_INLINE const hkaAnimatedReferenceFrame* hkaAnimation::getExtractedMotion() const
{
	return m_extractedMotion;
}

HK_FORCE_INLINE void hkaAnimation::getExtractedMotionReferenceFrame(hkReal time, hkQsTransform& motionOut) const
{
	return m_extractedMotion->getReferenceFrame( time, motionOut );
}

HK_FORCE_INLINE void hkaAnimation::getExtractedMotionDeltaReferenceFrame( hkReal time, hkReal nextTime, int loops, hkQsTransform& deltaMotionOut, hkReal cropStartAmount, hkReal cropEndAmount ) const
{
	return m_extractedMotion->getDeltaReferenceFrame( time, nextTime, loops, deltaMotionOut, cropStartAmount, cropEndAmount );
}

/// Sample a single animation track
HK_FORCE_INLINE void hkaAnimation::sampleSingleTransformTrack( hkReal time, hkInt16 track, hkQsTransform* transformOut ) const
{
	return sampleIndividualTransformTracks( time, &track, 1, transformOut );
}

/// Sample a single floating track
HK_FORCE_INLINE void hkaAnimation::sampleSingleFloatTrack( hkReal time, hkInt16 track, hkReal* out ) const
{
	return sampleIndividualFloatTracks( time, &track, 1, out );
}

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
