/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

HK_FORCE_INLINE hkUint32 hkaPredictiveCompressedAnimation::CompressionParams::getTransformTrackPaletteIndex(int track) const
{
	if ( m_trackIndexToPaletteIndex.getSize() > track )
	{
		return m_trackIndexToPaletteIndex[track];
	}
	else
	{
		return 0;
	}
}

HK_FORCE_INLINE hkUint32 hkaPredictiveCompressedAnimation::CompressionParams::getFloatTrackPaletteIndex(int track) const
{
	if ( m_floatTrackIndexToPaletteIndex.getSize() > track )
	{
		return m_floatTrackIndexToPaletteIndex[track];
	}
	else
	{
		return 0;
	}
}

HK_FORCE_INLINE hkReal hkaPredictiveCompressedAnimation::CompressionParams::getStaticTranslationTolerance(int track) const 
{ 
	return m_parameterPalette[getTransformTrackPaletteIndex(track)].m_staticTranslationTolerance; 
}

HK_FORCE_INLINE hkReal hkaPredictiveCompressedAnimation::CompressionParams::getStaticRotationTolerance(int track) const
{
	return m_parameterPalette[getTransformTrackPaletteIndex(track)].m_staticRotationTolerance;
}

HK_FORCE_INLINE hkReal hkaPredictiveCompressedAnimation::CompressionParams::getStaticScaleTolerance(int track) const
{
	return m_parameterPalette[getTransformTrackPaletteIndex(track)].m_staticScaleTolerance;
}

HK_FORCE_INLINE hkReal hkaPredictiveCompressedAnimation::CompressionParams::getStaticFloatTolerance(int track) const
{
	return m_parameterPalette[getFloatTrackPaletteIndex(track)].m_staticFloatTolerance;
}

HK_FORCE_INLINE hkReal hkaPredictiveCompressedAnimation::CompressionParams::getDynamicTranslationTolerance(int track) const
{
	return m_parameterPalette[getTransformTrackPaletteIndex(track)].m_dynamicTranslationTolerance;
}

HK_FORCE_INLINE hkReal hkaPredictiveCompressedAnimation::CompressionParams::getDynamicRotationTolerance(int track) const
{
	return m_parameterPalette[getTransformTrackPaletteIndex(track)].m_dynamicRotationTolerance; 
}

HK_FORCE_INLINE hkReal hkaPredictiveCompressedAnimation::CompressionParams::getDynamicScaleTolerance(int track) const
{
	return m_parameterPalette[getTransformTrackPaletteIndex(track)].m_dynamicScaleTolerance;
}

HK_FORCE_INLINE hkReal hkaPredictiveCompressedAnimation::CompressionParams::getDynamicFloatTolerance(int track) const
{
	return m_parameterPalette[getFloatTrackPaletteIndex(track)].m_dynamicFloatTolerance;
}

HK_FORCE_INLINE int hkaPredictiveCompressedAnimation::storageIsDynamic(StorageClass x)
{
	return x == STORAGE_DYNAMIC_RANGE || x == STORAGE_DYNAMIC_FIXED;
}

HK_FORCE_INLINE const hkUint16* hkaPredictiveCompressedAnimation::getArray(IntArrayID x) const
{
	return m_intData.begin() + m_intArrayOffsets[x];
}

HK_FORCE_INLINE const hkReal* hkaPredictiveCompressedAnimation::getArray(FloatArrayID x) const
{
	return m_floatData.begin() + m_floatArrayOffsets[x];
}

HK_FORCE_INLINE int hkaPredictiveCompressedAnimation::getArrayLength(IntArrayID x) const
{
	// there are a few dummy elems at the end of the data arrays
	enum { EXTRA_ELEMS = 16 / sizeof(hkInt16) };
	int start = m_intArrayOffsets[x];
	int end = (x == NUM_INT_ARRAYS - 1) ? (m_intData.getSize() - EXTRA_ELEMS) : m_intArrayOffsets[x+1];
	return end - start;
}

HK_FORCE_INLINE int hkaPredictiveCompressedAnimation::getArrayLength(FloatArrayID x) const
{
	// there are a few dummy elems at the end of the data arrays
	enum { EXTRA_ELEMS = 16 / sizeof(hkInt16) };
	int start = m_floatArrayOffsets[x];
	int end = (x == NUM_FLOAT_ARRAYS - 1) ? (m_floatData.getSize() - EXTRA_ELEMS) : m_floatArrayOffsets[x+1];
	return end - start;
}

template<hkaPredictiveCompressedAnimation::IntArrayID intArrayId>
HK_FORCE_INLINE hkUint32 hkaPredictiveCompressedAnimation::getBlockOffset(int blockColumnIndex) const
{
	const hkUint16* b = getArray(intArrayId);
	return b[blockColumnIndex * 2] | (b[blockColumnIndex*2 + 1] << 16);
}

HK_FORCE_INLINE hkInt32 hkaPredictiveCompressedAnimation::getNumBones() const
{
	return m_numBones;
}

HK_FORCE_INLINE hkInt32 hkaPredictiveCompressedAnimation::getNumFloatSlots() const
{
	return m_numFloatSlots;
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
