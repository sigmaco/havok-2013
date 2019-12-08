/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

//
//	Returns this < 0

inline const hkVector4fComparison hkInt128Vector4::lessZero() const
{
	// Shuffle to get the signs:
	//	m_x = [sx, *, *, *]
	//	m_y = [sy, *, *, *]
	//	m_z = [sz, *, *, *]
	//	m_w = [sw, *, *, *]
	const __m128 xy		= _mm_castsi128_ps(_mm_unpackhi_epi32(m_y.m_quad, m_x.m_quad));			// [sx, sy, *, *]
	const __m128 zw		= _mm_castsi128_ps(_mm_unpackhi_epi32(m_w.m_quad, m_z.m_quad));			// [sz, sw, *, *]
	const __m128i xyzw	= _mm_castps_si128(_mm_shuffle_ps(xy, zw, _MM_SHUFFLE(2, 3, 2, 3)));	// [sw, sz, sy, sx]
	const __m128i signs	= _mm_srai_epi32(xyzw, 31);

	return hkVector4fComparison::convert(_mm_castsi128_ps(signs));
}

//
//	Flips the sign of v

template <> inline void hkInt128Vector4::setFlipSign<3>(hkInt128Vector4Parameter v, hkVector4fComparisonParameter signFlip)
{
	const __m128 m				= signFlip.m_mask;
	hkVector4fComparison cmpx;	cmpx.m_mask = _mm_shuffle_ps(m, m, _MM_SHUFFLE(0,0,0,0));	m_x.setFlipSign(v.m_x, cmpx);
	hkVector4fComparison cmpy;	cmpy.m_mask = _mm_shuffle_ps(m, m, _MM_SHUFFLE(1,1,1,1));	m_y.setFlipSign(v.m_y, cmpy);
	hkVector4fComparison cmpz;	cmpz.m_mask = _mm_shuffle_ps(m, m, _MM_SHUFFLE(2,2,2,2));	m_z.setFlipSign(v.m_z, cmpz);
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
