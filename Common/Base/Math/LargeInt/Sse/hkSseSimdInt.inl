/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

//
//	Sets this = i

template <>
inline void hkSimdInt<256>::setFromInt32(int i)
{
	m_lo.setFromInt32(i);
	m_hi.m_quad = _mm_shuffle_epi32(m_lo.m_quad, _MM_SHUFFLE(3,3,3,3));
}

//
//	Sets this = a + b

template <>
inline void hkSimdInt<256>::setUnsignedAdd(HalfIntParameter a, HalfIntParameter b)
{
	// a = [a3, a2, a1, a0]
	// b = [b3, b2, b1, b0]
	const __m128i a20 = _mm_srli_epi64(_mm_slli_epi64(a.m_quad, 32), 32);	// [0, a2, 0, a0]
	const __m128i b20 = _mm_srli_epi64(_mm_slli_epi64(b.m_quad, 32), 32);	// [0, b2, 0, b0]
	const __m128i a31 = _mm_srli_epi64(a.m_quad, 32);						// [0, a3, 0, a1]
	const __m128i b31 = _mm_srli_epi64(b.m_quad, 32);						// [0, b3, 0, b1]
	const __m128i ab20 = _mm_add_epi64(a20, b20);	// [a2 + b2, a0 + b0]
	const __m128i ab31 = _mm_add_epi64(a31, b31);	// [a3 + b3, a1 + b1]

	__m128i r0 = ab20;																// [*, a0 + b0]
	__m128i r1 = _mm_add_epi64(_mm_srli_epi64(r0, 32), ab31);						// [*, hi(a0 + b0) + a1 + b1]
	__m128i r2 = _mm_add_epi64(_mm_srli_epi64(r1, 32), _mm_srli_si128(ab20, 8));	// [*, hi(r1) + a2 + b2]
	__m128i r3 = _mm_add_epi64(_mm_srli_epi64(r2, 32), _mm_srli_si128(ab31, 8));	// [*, hi(r2) + a3 + b3]

	// Shuffle everything into the output vector
	// We need [r3.1, r3.0, r2.0, r1.0, r0.0]
	r2 = _mm_unpacklo_epi32(r2, r3);	// [r3.1, r2.1, r3.0, r2.0]
	r0 = _mm_unpacklo_epi32(r0, r1);	// [r1.1, r0.1, r1.0, r0.0] 
	m_lo.m_quad = _mm_castps_si128(_mm_shuffle_ps(_mm_castsi128_ps(r0), _mm_castsi128_ps(r2), _MM_SHUFFLE(1, 0, 1, 0)));	// [r3.0, r2.0, r1.0, r0.0]
	m_hi.m_quad = _mm_srli_si128(r2, 12);																					// [0, 0, 0, r3.1]
}

//
//	Sets this = a * b while ignoring any potential overflows

template <>
inline void hkSimdInt<256>::setUnsignedMul(const hkSimdInt<256>& origA, int origB)
{
	// a = [a7 a6 a5 a4][a3 a2 a1 a0], b = [*, *, *, b]
    const __m128i a_7654    = origA.m_hi.m_quad;				// [a7, a6, a5, a4]
    const __m128i a_3210    = origA.m_lo.m_quad;				// [a3, a2, a1, a0]
    const __m128i b			= _mm_set1_epi32(origB);			// [b, b, b, b]

    // Shuffle and compute all products
    const __m128i a2_a0_b = _mm_mul_epu32(a_3210, b);						// [a2 b, a0 b]
    const __m128i a3_a1_b = _mm_mul_epu32(_mm_srli_si128(a_3210, 4), b);	// [a3 b, a1 b]
    const __m128i a6_a4_b = _mm_mul_epu32(a_7654, b);						// [a6 b, a4 b]
    const __m128i a7_a5_b = _mm_mul_epu32(_mm_srli_si128(a_7654, 4), b);	// [a7 b, a5 b]

    // We need to sum:
    //                                                                   hi(a0 b) lo(a0 b)
    //                                                          hi(a1 b) lo(a1 b)
    //                                                 hi(a2 b) lo(a2 b)
    //                                        hi(a3 b) lo(a3 b)
    //                               hi(a4 b) lo(a4 b)
    //                      hi(a5 b) lo(a5 b)
    //             hi(a6 b) lo(a6 b)    
    //    hi(a7 b) lo(a7 b)
    __m128i a31 = _mm_add_epi64(a3_a1_b, _mm_srli_epi64(a2_a0_b, 32));    // [(a3 b) + hi(a2 b), (a1 b) + hi(a0 b)]
    __m128i a75 = _mm_add_epi64(a7_a5_b, _mm_srli_epi64(a6_a4_b, 32));    // [(a7 b) + hi(a6 b), (a5 b) + hi(a4 b)]
    __m128i a42 = _mm_castpd_si128(_mm_shuffle_pd( _mm_castsi128_pd(a2_a0_b), _mm_castsi128_pd(a6_a4_b), _MM_SHUFFLE2(0, 1)));		// [a4 b, a2 b]
    __m128i a20 = _mm_add_epi64(_mm_srli_epi64(a31, 32), _mm_srli_epi64(_mm_slli_epi64(a42, 32), 32));								// [hi(a31[1]) + lo(a4 b), hi(a31[0]) + lo(a2 b)]
    __m128i a67 = _mm_add_epi64(_mm_srli_epi64(a75, 32), _mm_srli_si128(_mm_slli_si128(a6_a4_b, 4), 12));							// [*, hi(a75[0]) + lo(a6 b)]
    __m128i a7531 = _mm_castpd_si128(_mm_shuffle_pd(_mm_castsi128_pd(a31), _mm_castsi128_pd(a75), _MM_SHUFFLE2(0,1)));				// [a75[0], a31[1]]

    a7531 = _mm_add_epi64(_mm_srli_epi64(a20, 32), _mm_srli_epi64(_mm_slli_epi64(a7531, 32), 32));							// [lo(a75[0]) + hi(a20[1]), lo(a31[1]) + hi(a20[0])]
    a75 = _mm_add_epi64(a75, _mm_slli_si128(_mm_srli_epi64(a67, 32), 8));													// [a75[1] + hi(a67[0]), *]
    a67 = _mm_castpd_si128(_mm_shuffle_pd(_mm_castsi128_pd(a20), _mm_castsi128_pd(a67), _MM_SHUFFLE2(0,1)));				// [a67[0], a20[1]]
    a67 = _mm_add_epi64(_mm_srli_epi64(a7531, 32), _mm_srli_epi64(_mm_slli_epi64(a67, 32), 32));							// [hi(a7531[1]) + lo(a67[0]), hi(a7531[0]) + lo(a20[1])]

    // Can compute the lowest 128 bits
    const __m128i retLo = _mm_unpacklo_epi64(	_mm_unpacklo_epi32(a2_a0_b, a31),	// [*, *, lo(a31[0]), lo(a0 b)]
												_mm_unpacklo_epi32(a20, a7531)		// [*, *, lo(a7531[0]), lo(a20[0])]
											);										// [lo(a7531[0]), lo(a20[0]), lo(a31[0]), lo(a0 b)]


    a75 = _mm_or_si128(a75, _mm_srli_si128(_mm_slli_si128(a7531, 4), 12));						// [a75[1], lo(a7531[1])]
    a75 = _mm_add_epi64(a75, _mm_srli_epi64(a67, 32));											// [a75[1] + hi(a67[1]), a75[0] + hi(a67[0]]
    a20 = _mm_add_epi64(_mm_srli_epi64(a75, 32), _mm_srli_si128(_mm_slli_si128(a67, 4), 12));	// [*, hi(a75[0]) + lo(a67[1])]
    a67 = _mm_unpacklo_epi32(a67, a75);															// [*, *, lo(a75[0]), lo(a67[0])]
    a75 = _mm_add_epi64(a75, _mm_srli_si128(_mm_slli_si128(a20, 8), 4));						// [a75[1] + hi(a20[1]), *]
    a75 = _mm_unpacklo_epi32(a20, _mm_srli_si128(a75, 8));										// [*, *, lo(a75[0]), lo(a20[0])]

    // Can compute the high 128 bits
    const __m128i retHi = _mm_unpacklo_epi64(a67, a75);											// [lo(a75[1]), lo(a20[0]), lo(a75[0]), lo(a67[0])]

    m_hi.m_quad = retHi;
    m_lo.m_quad = retLo;
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
