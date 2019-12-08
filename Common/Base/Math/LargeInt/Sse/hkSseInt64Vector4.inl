/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

//
//	Sets all component of this to i

inline void hkInt64Vector4::setAll(hkInt64 i)
{
#if ( HK_SSE_VERSION >= 0x41 ) && defined(HK_ARCH_X64)
	m_quad.xy = m_quad.zw = _mm_set1_epi64x(i);
#else
	const hkUint32 hi = (i >> 32L) & 0xFFFFFFFF;
	const hkUint32 lo	= i & 0xFFFFFFFF;
	m_quad.xy = _mm_set_epi32(hi, lo, hi, lo);
	m_quad.zw = m_quad.xy;
#endif
}

//
//	Sets this = 0

inline void hkInt64Vector4::setZero()
{
	m_quad.xy = _mm_setzero_si128();
	m_quad.zw = m_quad.xy;
}

//
//	Sets the components of the vector to the given values

inline void hkInt64Vector4::set(hkInt64 x, hkInt64 y, hkInt64 z, hkInt64 w)
{
#if ( HK_SSE_VERSION >= 0x41 ) && defined(HK_ARCH_X64)
	m_quad.xy = _mm_set_epi64x(y, x);
	m_quad.zw = _mm_set_epi64x(w, z);
#else
	HK_ALIGN16(hkInt64) temp[] = {x, y, z, w};
	m_quad.xy = _mm_load_si128((const __m128i*)&temp[0]);	// [x, y]
	m_quad.zw = _mm_load_si128((const __m128i*)&temp[2]);	// [z, w]
#endif
}

//
//	Sets the I-th component to the given value

template <> inline void hkInt64Vector4::setComponent<0>(hkInt64 value)
{
#if ( HK_SSE_VERSION >= 0x41 ) && defined(HK_ARCH_X64)
	m_quad.xy = _mm_insert_epi64(m_quad.xy, value, 0);
#else
	// The unpacklo is to prevent a bug in VS2008 release, where the upper part of the vector is not zeroed!
	const __m128i x = _mm_unpacklo_epi64(_mm_setzero_si128(), _mm_loadl_epi64((__m128i*)&value));	// [val, 0].
	m_quad.xy = _mm_unpackhi_epi64(x, m_quad.xy);			// [y, val]
#endif
}

template <> inline void hkInt64Vector4::setComponent<1>(hkInt64 value)
{
#if ( HK_SSE_VERSION >= 0x41 ) && defined(HK_ARCH_X64)
	m_quad.xy = _mm_insert_epi64(m_quad.xy, value, 1);
#else
	// The unpacklo is to prevent a bug in VS2008 release, where the upper part of the vector is not zeroed!
	const __m128i x = _mm_unpacklo_epi64(_mm_loadl_epi64((__m128i*)&value), _mm_setzero_si128());	// [0, val].
	m_quad.xy = _mm_unpacklo_epi64(m_quad.xy, x);			// [val, x]
#endif
}

template <> inline void hkInt64Vector4::setComponent<2>(hkInt64 value)
{
#if ( HK_SSE_VERSION >= 0x41 ) && defined(HK_ARCH_X64)
	m_quad.zw = _mm_insert_epi64(m_quad.zw, value, 0);
#else
	// The unpacklo is to prevent a bug in VS2008 release, where the upper part of the vector is not zeroed!
	const __m128i x = _mm_unpacklo_epi64(_mm_setzero_si128(), _mm_loadl_epi64((__m128i*)&value));	// [val, 0].
	m_quad.zw = _mm_unpackhi_epi64(x, m_quad.zw);			// [w, val]
#endif
}

template <> inline void hkInt64Vector4::setComponent<3>(hkInt64 value)
{
#if ( HK_SSE_VERSION >= 0x41 ) && defined(HK_ARCH_X64)
	m_quad.zw = _mm_insert_epi64(m_quad.zw, value, 1);
#else
	// The unpacklo is to prevent a bug in VS2008 release, where the upper part of the vector is not zeroed!
	const __m128i x = _mm_unpacklo_epi64(_mm_loadl_epi64((__m128i*)&value), _mm_setzero_si128());	// [0, val].
	m_quad.zw = _mm_unpacklo_epi64(m_quad.zw, x);			// [val, z]
#endif
}

//
//	Sets this = vA - vB

inline void hkInt64Vector4::setSub(hkInt64Vector4Parameter vA, hkInt64Vector4Parameter vB)
{
	m_quad.xy = _mm_sub_epi64(vA.m_quad.xy, vB.m_quad.xy);
	m_quad.zw = _mm_sub_epi64(vA.m_quad.zw, vB.m_quad.zw);
}

//
//	Returns (this < 0)

template <> inline const hkVector4fComparison hkInt64Vector4::lessZero<hkVector4fComparison>() const
{
	// Shift the sign bits
	//		[3, 2, 1, 0]
	// xy = [hiY, loY, hiX, loX]								// [3,		2,	1,		0]
	// zw = [hiW, loW, hiZ, loZ]
	const __m128i sign_xxyy = _mm_srai_epi32(m_quad.xy, 31);	// [y < 0,	*,	x < 0,	*]
	const __m128i sign_zzww = _mm_srai_epi32(m_quad.zw, 31);	// [w < 0,	*,	z < 0,	*]
	const __m128 cmp		= _mm_shuffle_ps(_mm_castsi128_ps(sign_xxyy), _mm_castsi128_ps(sign_zzww), _MM_SHUFFLE(3, 1, 3, 1));
	return hkVector4fComparison::convert(cmp);
}

//
//	Returns (this < 0)

template <> inline const hkVector4dComparison hkInt64Vector4::lessZero<hkVector4dComparison>() const
{
	// Shift the sign bits
	hkVector4dComparison cmp;
#if ( HK_SSE_VERSION >= 0x42 )
	const __m128i zero	= _mm_setzero_si128();
	cmp.m_mask.xy		= _mm_castsi128_pd(_mm_cmpgt_epi64(zero, m_quad.xy));
	cmp.m_mask.zw		= _mm_castsi128_pd(_mm_cmpgt_epi64(zero, m_quad.zw));
#else
	cmp.m_mask.xy		= _mm_castsi128_pd(_mm_shuffle_epi32(_mm_srai_epi32(m_quad.xy, 31), _MM_SHUFFLE(3, 3, 1, 1)));
	cmp.m_mask.zw		= _mm_castsi128_pd(_mm_shuffle_epi32(_mm_srai_epi32(m_quad.zw, 31), _MM_SHUFFLE(3, 3, 1, 1)));
#endif
	return cmp;
}

inline const hkVector4fComparison hkInt64Vector4::lessZero() const
{
	return lessZero<hkVector4fComparison>();
}

//
//	Returns (this == 0)

inline const hkVector4fComparison hkInt64Vector4::equalZero() const
{
	const __m128i zero		= _mm_setzero_si128();
#if ( HK_SSE_VERSION >= 0x41 )
	const __m128 cmp_xxyy	= _mm_castsi128_ps(_mm_cmpeq_epi64(m_quad.xy, zero));			// [cy, cy,	cx, cx]
	const __m128 cmp_zzww	= _mm_castsi128_ps(_mm_cmpeq_epi64(m_quad.zw, zero));			// [cw, cw,	cz, cz]
	const __m128 cmp		= _mm_shuffle_ps(cmp_xxyy, cmp_zzww, _MM_SHUFFLE(3, 1, 3, 1));	// [cw cz cy cx]
#else
	const __m128 cmp_xxyy	= _mm_castsi128_ps(_mm_cmpeq_epi32(m_quad.xy, zero));			// [hiY == 0, loY == 0,	hiX == 0, loX == 0]
	const __m128 cmp_zzww	= _mm_castsi128_ps(_mm_cmpeq_epi32(m_quad.zw, zero));			// [hiW == 0, loW == 0,	hiZ == 0, loZ == 0]
	const __m128 cmpLo		= _mm_shuffle_ps(cmp_xxyy, cmp_zzww, _MM_SHUFFLE(3, 1, 3, 1));	// [hiW == 0, hiZ == 0, hiY == 0, hiX == 0]
	const __m128 cmpHi		= _mm_shuffle_ps(cmp_xxyy, cmp_zzww, _MM_SHUFFLE(2, 0, 2, 0));	// [loW == 0, loZ == 0, loY == 0, loX == 0]
	const __m128 cmp		= _mm_and_ps(cmpLo, cmpHi);
#endif
	return hkVector4fComparison::convert(cmp);
}

//
//	Returns (this == v)

inline const hkVector4fComparison hkInt64Vector4::equal(hkInt64Vector4Parameter v) const
{
#if ( HK_SSE_VERSION >= 0x41 )
	const __m128 cmp_xxyy	= _mm_castsi128_ps(_mm_cmpeq_epi64(m_quad.xy, v.m_quad.xy));	// [cy cy cx cx]
	const __m128 cmp_zzww	= _mm_castsi128_ps(_mm_cmpeq_epi64(m_quad.zw, v.m_quad.zw));	// [cw cw cz cz]
	const __m128 cmp		= _mm_shuffle_ps(cmp_xxyy, cmp_zzww, _MM_SHUFFLE(3, 1, 3, 1));	// [cw cz cy cx]
#else
	const __m128 cmp_xxyy	= _mm_castsi128_ps(_mm_cmpeq_epi32(m_quad.xy, v.m_quad.xy));
	const __m128 cmp_zzww	= _mm_castsi128_ps(_mm_cmpeq_epi32(m_quad.zw, v.m_quad.zw));
	const __m128 cmpLo		= _mm_shuffle_ps(cmp_xxyy, cmp_zzww, _MM_SHUFFLE(3, 1, 3, 1));
	const __m128 cmpHi		= _mm_shuffle_ps(cmp_xxyy, cmp_zzww, _MM_SHUFFLE(2, 0, 2, 0));
	const __m128 cmp		= _mm_and_ps(cmpLo, cmpHi);
#endif

	return hkVector4fComparison::convert(cmp);
}

//
//	Sets this = -v

template <> inline void hkInt64Vector4::setNeg<4>(hkInt64Vector4Parameter v)
{
	const register __m128i zero = _mm_setzero_si128();
	m_quad.xy = _mm_sub_epi64(zero, v.m_quad.xy);
	m_quad.zw = _mm_sub_epi64(zero, v.m_quad.zw);
}

//
//	Sets this = vA & vB

inline void hkInt64Vector4::setAnd(hkInt64Vector4Parameter vA, hkInt64Vector4Parameter vB)
{
	m_quad.xy = _mm_and_si128(vA.m_quad.xy, vB.m_quad.xy);
	m_quad.zw = _mm_and_si128(vA.m_quad.zw, vB.m_quad.zw);
}

//
//	Sets this = cmp ? vTrue : vFalse

inline void hkInt64Vector4::setSelect(hkVector4fComparisonParameter cmp, hkInt64Vector4Parameter vTrue, hkInt64Vector4Parameter vFalse)
{
	const __m128i cmp_xyzw	= _mm_castps_si128(cmp.m_mask);
	const __m128i cmp_xxyy	= _mm_unpacklo_epi32(cmp_xyzw, cmp_xyzw);	// [cmpx, cmpx, cmpy, cmpy]
	const __m128i cmp_zzww	= _mm_unpackhi_epi32(cmp_xyzw, cmp_xyzw);	// [cmpz, cmpz, cmpw, cmpw]

#if ( HK_SSE_VERSION >= 0x41 )
	m_quad.xy = _mm_blendv_epi8(vFalse.m_quad.xy, vTrue.m_quad.xy, cmp_xxyy);
	m_quad.zw = _mm_blendv_epi8(vFalse.m_quad.zw, vTrue.m_quad.zw, cmp_zzww);
#else
	m_quad.xy = _mm_or_si128(_mm_and_si128(cmp_xxyy, vTrue.m_quad.xy), _mm_andnot_si128(cmp_xxyy, vFalse.m_quad.xy));
	m_quad.zw = _mm_or_si128(_mm_and_si128(cmp_zzww, vTrue.m_quad.zw), _mm_andnot_si128(cmp_zzww, vFalse.m_quad.zw));
#endif
}

//
//	Sets this = v << shr by component

template <int I>
inline void hkInt64Vector4::setShiftLeft(hkInt64Vector4Parameter v)
{
	m_quad.xy = _mm_slli_epi64(v.m_quad.xy, I);
	m_quad.zw = _mm_slli_epi64(v.m_quad.zw, I);
}

inline void hkInt64Vector4::setShiftLeft(hkInt64Vector4Parameter v, int I)
{
	m_quad.xy = _mm_slli_epi64(v.m_quad.xy, I);
	m_quad.zw = _mm_slli_epi64(v.m_quad.zw, I);
}

namespace hkInt64Vector4Impl
{
	template <hkMathValueType VAL> struct Shr {};

	template <> struct Shr<HK_VALUE_UNSIGNED>
	{
		static inline void HK_CALL shr(hkInt64Vector4Parameter vIn, hkInt64Vector4& vOut, int I)
		{
			vOut.m_quad.xy = _mm_srli_epi64(vIn.m_quad.xy, I);
			vOut.m_quad.zw = _mm_srli_epi64(vIn.m_quad.zw, I);
		}
	};

	template <> struct Shr<HK_VALUE_SIGNED>
	{
		static inline void HK_CALL shr(hkInt64Vector4Parameter vIn, hkInt64Vector4& vOut, int I)
		{
			// Shift the unsigned values
			const __m128i xy = _mm_srli_epi64(vIn.m_quad.xy, I);	// This sets the first I bits to 0, oblivious to their sign
			const __m128i zw = _mm_srli_epi64(vIn.m_quad.zw, I);

			// Get the signs
			const __m128i sxy = _mm_slli_epi64(_mm_srai_epi32(_mm_shuffle_epi32(vIn.m_quad.xy, _MM_SHUFFLE(3, 3, 1, 1)), 31), 64 - I);
			const __m128i szw = _mm_slli_epi64(_mm_srai_epi32(_mm_shuffle_epi32(vIn.m_quad.zw, _MM_SHUFFLE(3, 3, 1, 1)), 31), 64 - I);

			// Or with the signs
			vOut.m_quad.xy = _mm_or_si128(xy, sxy);
			vOut.m_quad.zw = _mm_or_si128(zw, szw);
		}
	};
}

//
//	Sets this = v >> I by component

template <int I, hkMathValueType VAL>
inline void hkInt64Vector4::setShiftRight(hkInt64Vector4Parameter v)
{
	hkInt64Vector4Impl::Shr<VAL>::shr(v, *this, I);
}

template <int I>
inline void hkInt64Vector4::setShiftRight(hkInt64Vector4Parameter v)
{
	setShiftRight<HK_VALUE_UNSIGNED>(v, I);
}

template <hkMathValueType VAL>
inline void hkInt64Vector4::setShiftRight(hkInt64Vector4Parameter v, int I)
{
	hkInt64Vector4Impl::Shr<VAL>::shr(v, *this, I);
}

namespace hkInt64Vector4Impl
{
	// Multiples vector vA = [hiB, loB, hiA, loA] with vector vX = [*, y *, x]. The * is considered to be the lo duplicated component, i.e. [y, y, x, x]
	static inline void HK_CALL vec2x64_mul_32(const __m128i& vA, hkIntVectorParameter vX, hkSimdInt<128>& axOut, hkSimdInt<128>& byOut)
	{
		// [3, 2, 1, 0]
		// [*, y, *, x]
		// [hiB, loB, hiA, loA] 

		// We must compute:
		//		byOut = (hiB * y) << 32 + loB * y
		//		axOut = (hiA * x) << 32 + loA * x
		const __m128i a0b0	= _mm_mul_epu32(vA, vX.m_quad);		// [hi(loB * y), lo(loB * y),	hi(loA * x), lo(loA * x)]
		const __m128i hiAB	= _mm_srli_epi64(vA, 32);			// [0, hiB, 0, hiA]
		const __m128i a1b0	= _mm_mul_epu32(hiAB, vX.m_quad);	// [hi(hiB * y), lo(hiB * y),	hi(hiA * x), lo(hiA * x)]

		// Accumulate results into 3 registers:
		//	r0 = [0..63], r1 = [32..95], r2 = [64..127]
		__m128i r2 = _mm_srli_epi64(a1b0, 32);								// [0, hi(hiB * y),	0, hi(hiA * x)]
		__m128i r1 = _mm_srli_epi64(_mm_slli_epi64(a1b0, 32), 32);			// [0, lo(hiB * y),	0, lo(hiA * x)]
		r1 = _mm_add_epi64(r1, _mm_srli_epi64(a0b0, 32));					// [lo(hiB * y) + hi(loB * y),	lo(hiA * x) + hi(loA * x)]
		r2 = _mm_add_epi64(r2, _mm_srli_epi64(r1, 32));						// [hi(hiB * y) + hi(lo(hiB * y) + hi(loB * y)), hi(hiA * x) + hi(lo(hiA * x) + hi(loA * x))]

		// Finally, gather the results into the outputs
		// At the moment, the registers hold the values:
		//		a0b0 = [*, by0, *, ax0]
		//		r1 = [*, by1, *, ax1]
		//		r2 = [by3, by2, ax3, ax2]

		// We need
		//		n1 = [r2_3, r2_2, by1, by0]
		//		n2 = [r2_1, r2_0, ax1, ax0]
		__m128i r0 = _mm_or_si128(_mm_slli_epi64(r1, 32), _mm_srli_epi64(_mm_slli_epi64(a0b0, 32), 32));						// [by1, by0, ax1, ax0]
		byOut.m_quad = _mm_castps_si128(_mm_shuffle_ps(_mm_castsi128_ps(r0), _mm_castsi128_ps(r2), _MM_SHUFFLE(3, 2, 3, 2)));	// [by3, by2, by1, by0]
		axOut.m_quad = _mm_castps_si128(_mm_shuffle_ps(_mm_castsi128_ps(r0), _mm_castsi128_ps(r2), _MM_SHUFFLE(1, 0, 1, 0)));	// [ax3, ax2, ax1, ax0]
	}

	static inline __m128i HK_CALL vec2x64_mul_32_ret64(const __m128i& vA, hkIntVectorParameter vX)
	{
		// [3, 2, 1, 0]
		// [*, y, *, x]
		// [hiB, loB, hiA, loA] 

		// We must compute:
		//		byOut = (hiB * y) << 32 + loB * y
		//		axOut = (hiA * x) << 32 + loA * x
		const __m128i a0b0	= _mm_mul_epu32(vA, vX.m_quad);		// [hi(loB * y), lo(loB * y),	hi(loA * x), lo(loA * x)]
		const __m128i hiAB	= _mm_srli_epi64(vA, 32);			// [0, hiB, 0, hiA]
		const __m128i a1b0	= _mm_mul_epu32(hiAB, vX.m_quad);	// [hi(hiB * y), lo(hiB * y),	hi(hiA * x), lo(hiA * x)]

		// Accumulate results into 3 registers:
		//	r0 = [0..63], r1 = [32..95], r2 = [64..127]
		__m128i r1	= _mm_srli_epi64(_mm_slli_epi64(a1b0, 32), 32);			// [0, lo(hiB * y),	0, lo(hiA * x)]
		r1			= _mm_add_epi64(r1, _mm_srli_epi64(a0b0, 32));			// [lo(hiB * y) + hi(loB * y),	lo(hiA * x) + hi(loA * x)]

		return _mm_or_si128(_mm_slli_epi64(r1, 32), _mm_srli_epi64(_mm_slli_epi64(a0b0, 32), 32));	// [by1, by0, ax1, ax0]
	}

	// Returns (a > b) ? a : b
	static inline const __m128i HK_CALL vec2x64_max(const __m128i& a, const __m128i& b)
	{
#if (HK_SSE_VERSION >= 0x42)
		return _mm_blendv_epi8(a, b, _mm_cmpgt_epi64(b, a));
#else
		const __m128i signs_a = _mm_shuffle_epi32(_mm_srai_epi32(a, 31), _MM_SHUFFLE(3, 3, 1, 1));
		const __m128i signs_b = _mm_shuffle_epi32(_mm_srai_epi32(b, 31), _MM_SHUFFLE(3, 3, 1, 1));
		const __m128i signs_cmp = _mm_xor_si128(signs_a, signs_b);

		// Result for different signs
		__m128i res2 = _mm_or_si128(_mm_and_si128(signs_a, b), _mm_andnot_si128(signs_a, a));

		// Result for same signs
		const __m128i amb = _mm_sub_epi64(a, b);
		const __m128i cmp = _mm_shuffle_epi32(_mm_srai_epi32(amb, 31), _MM_SHUFFLE(3, 3, 1, 1));
		__m128i res1 = _mm_or_si128(_mm_and_si128(cmp, b), _mm_andnot_si128(cmp, a));
		
		// Choose result
		return  _mm_or_si128(_mm_and_si128(signs_cmp, res2), _mm_andnot_si128(signs_cmp, res1));
#endif
	}
}

//
//	Returns the dot product between this and v

template <> inline const hkSimdInt<128> hkInt64Vector4::dot<3>(hkIntVectorParameter vB) const
{
	// Compute final signs
	hkVector4fComparison cmpFlip;
	{
		const hkVector4fComparison negA	= lessZero();								// [ax < 0, ay < 0, az < 0, aw < 0]
		hkVector4fComparison negB;		negB.set(vB.lessZeroS32().getMask());		// [bx < 0, by < 0, bz < 0, bw < 0]
		hkVector4fComparison negZeroA;	negZeroA.setOr(negA, equalZero());			// [ax <= 0, ay <= 0, az <= 0, aw <= 0]
		hkVector4fComparison negZeroB;	negZeroB.set(vB.equalZeroS32().getMask());
										negZeroB.setOr(negB, negZeroB);				// [bx <= 0, by <= 0, bz <= 0, bw <= 0]

		hkVector4fComparison negA_posB;	negA_posB.setAndNot(negA, negZeroB);		// [(ax < 0) && (bx > 0), ...]
		hkVector4fComparison posA_negB;	posA_negB.setAndNot(negB, negZeroA);		// [(ax > 0) && (bx < 0), ...]
		cmpFlip.setOr(negA_posB, posA_negB);		// [sign(ax * bx), ...]
	}

	// Compute absolute values
	hkInt64Vector4 absA;	absA.setAbs(*this);
	hkIntVector absB;		absB.setAbsS32(vB);
	hkIntVector vXY;		vXY.setPermutation<hkVectorPermutation::XXYY>(absB);	// [vx, vx, vy, vy]
	hkIntVector vZW;		vZW.setPermutation<hkVectorPermutation::ZZWW>(absB);	// [vz, vz, vw, vw]

	// Compute absolute products
	hkInt128Vector4 dots;
	hkInt64Vector4Impl::vec2x64_mul_32(absA.m_quad.xy, vXY, dots.m_x, dots.m_y);
	hkInt64Vector4Impl::vec2x64_mul_32(absA.m_quad.zw, vZW, dots.m_z, dots.m_w);

	// Set signs
	dots.setFlipSign<3>(dots, cmpFlip);

	// Compute and return dot
	dots.m_x.setAdd(dots.m_x, dots.m_y);
	dots.m_x.setAdd(dots.m_x, dots.m_z);
	return dots.m_x;
}

//
//	Returns the I-th component

template <> inline hkInt64 hkInt64Vector4::getComponent<0>() const
{
#if HK_SSE_VERSION >= 0x41
	return _mm_extract_epi64(m_quad.xy, 0);
#else
	return HK_M128(m_quad.xy).m128i_i64[0];
#endif
}

template <> inline hkInt64 hkInt64Vector4::getComponent<1>() const
{
#if HK_SSE_VERSION >= 0x41
	return _mm_extract_epi64(m_quad.xy, 1);
#else
	return HK_M128(m_quad.xy).m128i_i64[1];
#endif
}

template <> inline hkInt64 hkInt64Vector4::getComponent<2>() const
{
#if HK_SSE_VERSION >= 0x41
	return _mm_extract_epi64(m_quad.zw, 0);
#else
	return HK_M128(m_quad.zw).m128i_i64[0];
#endif
}

template <> inline hkInt64 hkInt64Vector4::getComponent<3>() const
{
#if HK_SSE_VERSION >= 0x41
	return _mm_extract_epi64(m_quad.zw, 1);
#else
	return HK_M128(m_quad.zw).m128i_i64[1];
#endif
}

inline hkInt64 hkInt64Vector4::getComponent(int I) const
{
	HK_MATH_ASSERT(0x6d0c31d7, (I >= 0) && (I < 4), "index out of bounds for component access");
	switch ( I )
	{
	case 1:  return getComponent<1>();
	case 2:  return getComponent<2>();
	case 3:  return getComponent<3>();
	default: return getComponent<0>();
	}
}

//
//	Returns the dot product between this and v

template <> inline hkInt64 hkInt64Vector4::dot_64<3>(hkIntVectorParameter vB) const
{
	// Compute final signs
	hkVector4fComparison cmpFlip;
	{
		const hkVector4fComparison negA	= lessZero();								// [ax < 0, ay < 0, az < 0, aw < 0]
		hkVector4fComparison negB;		negB.set(vB.lessZeroS32().getMask());		// [bx < 0, by < 0, bz < 0, bw < 0]
		hkVector4fComparison negZeroA;	negZeroA.setOr(negA, equalZero());			// [ax <= 0, ay <= 0, az <= 0, aw <= 0]
		hkVector4fComparison negZeroB;	negZeroB.set(vB.equalZeroS32().getMask());
										negZeroB.setOr(negB, negZeroB);				// [bx <= 0, by <= 0, bz <= 0, bw <= 0]

		hkVector4fComparison negA_posB;	negA_posB.setAndNot(negA, negZeroB);		// [(ax < 0) && (bx > 0), ...]
		hkVector4fComparison posA_negB;	posA_negB.setAndNot(negB, negZeroA);		// [(ax > 0) && (bx < 0), ...]
		cmpFlip.setOr(negA_posB, posA_negB);		// [sign(ax * bx), ...]
	}

	// Compute absolute values
	hkInt64Vector4 absA;	absA.setAbs(*this);
	hkIntVector absB;		absB.setAbsS32(vB);
	hkIntVector vXY;		vXY.setPermutation<hkVectorPermutation::XXYY>(absB);	// [vx, vx, vy, vy]
	hkIntVector vZW;		vZW.setPermutation<hkVectorPermutation::ZZWW>(absB);	// [vz, vz, vw, vw]

	// Compute products
	hkInt64Vector4 ret;
	ret.m_quad.xy = hkInt64Vector4Impl::vec2x64_mul_32_ret64(absA.m_quad.xy, vXY);
	ret.m_quad.zw = hkInt64Vector4Impl::vec2x64_mul_32_ret64(absA.m_quad.zw, vZW);
	ret.setFlipSign(ret, cmpFlip);

	// Compute and return dot
	return ret.getComponent<0>() + ret.getComponent<1>() + ret.getComponent<2>();
}

//
//	Sets this = a permutation of the components of v

template <> inline void hkInt64Vector4::setPermutation<hkVectorPermutation::YZXW>(hkInt64Vector4Parameter v)
{
	const __m128d xy = _mm_castsi128_pd(v.m_quad.xy);							// [y, x]
	const __m128d zw = _mm_castsi128_pd(v.m_quad.zw);							// [w, z]
	m_quad.xy = _mm_castpd_si128(_mm_shuffle_pd(xy, zw, _MM_SHUFFLE2(0, 1)));	// [z, y]
	m_quad.zw = _mm_castpd_si128(_mm_move_sd(zw, xy));							// [w, x]
}

template <> inline void hkInt64Vector4::setPermutation<hkVectorPermutation::ZXYW>(hkInt64Vector4Parameter v)
{
	const __m128d xy = _mm_castsi128_pd(v.m_quad.xy);							// [y, x]
	const __m128d zw = _mm_castsi128_pd(v.m_quad.zw);							// [w, z]
	m_quad.xy =  _mm_castpd_si128(_mm_unpacklo_pd(zw, xy));						// [x, z]
	m_quad.zw =  _mm_castpd_si128(_mm_unpackhi_pd(xy, zw));						// [w, y]
}

template <> inline void hkInt64Vector4::setPermutation<hkVectorPermutation::YXWZ>(hkInt64Vector4Parameter v)
{
	const __m128d xy = _mm_castsi128_pd(v.m_quad.xy);							// [y, x]
	const __m128d zw = _mm_castsi128_pd(v.m_quad.zw);							// [w, z]
	m_quad.xy = _mm_castpd_si128(_mm_shuffle_pd(xy, xy, _MM_SHUFFLE2(0, 1)));	// [x, y]
	m_quad.zw = _mm_castpd_si128(_mm_shuffle_pd(zw, zw, _MM_SHUFFLE2(0, 1)));	// [z, w]
}

template <> inline void hkInt64Vector4::setPermutation<hkVectorPermutation::XYWZ>(hkInt64Vector4Parameter v)
{
	const __m128d zw = _mm_castsi128_pd(v.m_quad.zw);							// [w, z]
	m_quad.xy = v.m_quad.xy;													// [y, x]
	m_quad.zw = _mm_castpd_si128(_mm_shuffle_pd(zw, zw, _MM_SHUFFLE2(0, 1)));	// [z, w]
}

template <> inline void hkInt64Vector4::setPermutation<hkVectorPermutation::YYWW>(hkInt64Vector4Parameter v)
{
	const __m128d xy = _mm_castsi128_pd(v.m_quad.xy);							// [y, x]
	const __m128d zw = _mm_castsi128_pd(v.m_quad.zw);							// [w, z]
	m_quad.xy = _mm_castpd_si128(_mm_shuffle_pd(xy, xy, _MM_SHUFFLE2(1, 1)));	// [y, y]
	m_quad.zw = _mm_castpd_si128(_mm_shuffle_pd(zw, zw, _MM_SHUFFLE2(1, 1)));	// [w, w]
}

template <> inline void hkInt64Vector4::setPermutation<hkVectorPermutation::WWWW>(hkInt64Vector4Parameter v)
{
	const __m128d zw = _mm_castsi128_pd(v.m_quad.zw);							// [w, z]
	m_quad.zw = _mm_castpd_si128(_mm_shuffle_pd(zw, zw, _MM_SHUFFLE2(1, 1)));	// [w, w]
	m_quad.xy = m_quad.zw;
}

/*template <>
inline void hkInt64Vector4::setUnsignedMul_128<1>(hkInt64Vector4Parameter origA, hkInt64Vector4Parameter origB)
{
	// origA.xy = [a1a0, *]
	// origB.xy = [b1b0, *]

	// Combine vectors
	const __m128i x = _mm_shuffle_epi32(origA.m_quad.xy, _MM_SHUFFLE(3, 2, 2, 3));	// [a1, a0, a0, a1]
	const __m128i y = _mm_shuffle_epi32(origB.m_quad.xy, _MM_SHUFFLE(3, 2, 3, 2));	// [b1, b0, b1, b0]

	// We must compute [ (a1 * b1) << 64 + (a1 * b0 + a0 * b1) << 32 + a0 * b0, ...]
	const __m128i a0b0_a1b0	= _mm_mul_epu32(x, y);												// [a0b0, a1b0]
	const __m128i a1b1_a0b1	= _mm_mul_epu32(_mm_srli_epi64(x, 32), _mm_srli_epi64(y, 32));		// [a1b1, a0b1]

	// Accumulate results into 3 registers:
	//	r0 = [0..63], r1 = [32..95], r2 = [64..127]
	__m128i r2 = _mm_add_epi64(	_mm_add_epi64(a1b1, _mm_srli_epi64(a1b0, 32)),
								_mm_srli_epi64(a0b1, 32));						// r2 = [a1b1 + hi(a1b0) + hi(a0b1), ]
	__m128i r1 = _mm_add_epi64(	_mm_srli_epi64(_mm_slli_epi64(a0b1, 32), 32),
								_mm_srli_epi64(_mm_slli_epi64(a1b0, 32), 32));	// r1 = [lo(a0b1) + lo(a1b0), lo(c0d1) + lo(c1d0)]
	r1 = _mm_add_epi64(r1, _mm_srli_epi64(a0b0, 32));							// r1 = [lo(a0b1) + lo(a1b0) + hi(a0b0), lo(c0d1) + lo(c1d0) + hi(c0d0)]
	r2 = _mm_add_epi64(r2, _mm_srli_epi64(r1, 32));								// r2 = [a1b1 + hi(a1b0) + hi(a0b1) + hi(r1), c1d1 + hi(c1d0) + hi(c0d1) + hi(r1)]
	__m128i r0 = _mm_or_si128	(_mm_slli_epi64(r1, 32),
								_mm_srli_epi64(_mm_slli_epi64(a0b0, 32), 32));	// r0 = [*, lo(a0b0), *, lo(c0d0)]
	// We need
	//		n1 = [r2.3, r2.2, r1.2, r0.2]
	//		n2 = [r2.1, r2.0, r1.0, r0.0]
	m_quad.xy = _mm_castps_si128(_mm_shuffle_ps(_mm_castsi128_ps(r2), _mm_castsi128_ps(r0), _MM_SHUFFLE(3, 2, 3, 2)));	// [r2.3, r2.2, r1.2, lo(a0b0)]
	m_quad.zw = _mm_castps_si128(_mm_shuffle_ps(_mm_castsi128_ps(r2), _mm_castsi128_ps(r0), _MM_SHUFFLE(1, 0, 1, 0)));	// [r2.1, r2.0, r1.0, lo(c0d0)]
}*/

template <>
inline void hkInt64Vector4::setUnsignedMul_128<2>(hkInt64Vector4Parameter origA, hkInt64Vector4Parameter origB)
{
	// origA.xy = [a1a0, *]	origA.zw = [c1c0, *]
	// origB.xy = [b1b0, *]	origB.zw = [d1d0, *]

	// Combine vectors
	const __m128i x = _mm_castpd_si128(_mm_unpackhi_pd(_mm_castsi128_pd(origA.m_quad.zw), _mm_castsi128_pd(origA.m_quad.xy)));	// [a1a0, c1c0]
	const __m128i y = _mm_castpd_si128(_mm_unpackhi_pd(_mm_castsi128_pd(origB.m_quad.zw), _mm_castsi128_pd(origB.m_quad.xy)));	// [b1b0, d1d0]

	// We must compute [ (a1 * b1) << 64 + (a1 * b0 + a0 * b1) << 32 + a0 * b0, ...]
	const __m128i a0b0	= _mm_mul_epu32(x, y);			// [a0b0, c0d0]
	const __m128i xhi	= _mm_srli_epi64(x, 32);		// [a1, c1]
	const __m128i yhi	= _mm_srli_epi64(y, 32);		// [b1, d1]
	const __m128i a1b0	= _mm_mul_epu32(xhi, y);		// [a1b0, c1d0]
	const __m128i a0b1	= _mm_mul_epu32(x, yhi);		// [a0b1, c0d1]
	const __m128i a1b1	= _mm_mul_epu32(xhi, yhi);		// [a1b1, c1d1]

	// Accumulate results into 3 registers:
	//	r0 = [0..63], r1 = [32..95], r2 = [64..127]
	__m128i r2 = _mm_add_epi64(	_mm_add_epi64(a1b1, _mm_srli_epi64(a1b0, 32)),
								_mm_srli_epi64(a0b1, 32));						// r2 = [a1b1 + hi(a1b0) + hi(a0b1), c1d1 + hi(c1d0) + hi(c0d1)]
	__m128i r1 = _mm_add_epi64(	_mm_srli_epi64(_mm_slli_epi64(a0b1, 32), 32),
								_mm_srli_epi64(_mm_slli_epi64(a1b0, 32), 32));	// r1 = [lo(a0b1) + lo(a1b0), lo(c0d1) + lo(c1d0)]
	r1 = _mm_add_epi64(r1, _mm_srli_epi64(a0b0, 32));							// r1 = [lo(a0b1) + lo(a1b0) + hi(a0b0), lo(c0d1) + lo(c1d0) + hi(c0d0)]
	r2 = _mm_add_epi64(r2, _mm_srli_epi64(r1, 32));								// r2 = [a1b1 + hi(a1b0) + hi(a0b1) + hi(r1), c1d1 + hi(c1d0) + hi(c0d1) + hi(r1)]
	__m128i r0 = _mm_or_si128	(_mm_slli_epi64(r1, 32),
								_mm_srli_epi64(_mm_slli_epi64(a0b0, 32), 32));	// r0 = [*, lo(a0b0), *, lo(c0d0)]
	// We need
	//		n1 = [r2.3, r2.2, r1.2, r0.2]
	//		n2 = [r2.1, r2.0, r1.0, r0.0]
	m_quad.xy = _mm_castps_si128(_mm_shuffle_ps(_mm_castsi128_ps(r2), _mm_castsi128_ps(r0), _MM_SHUFFLE(3, 2, 3, 2)));	// [r2.3, r2.2, r1.2, lo(a0b0)]
	m_quad.zw = _mm_castps_si128(_mm_shuffle_ps(_mm_castsi128_ps(r2), _mm_castsi128_ps(r0), _MM_SHUFFLE(1, 0, 1, 0)));	// [r2.1, r2.0, r1.0, lo(c0d0)]
}

//
//	Sets this.xy = a.x * b.x this.zw = a.z * b.z, i.e. multiplies the 2 64-bit operands and returns 2 128-bit numbers

inline void hkInt64Vector4::setMul_128(hkInt64Vector4Parameter origA, hkInt64Vector4Parameter origB)
{
	// origA.xy = [a1a0, *]	origA.zw = [c1c0, *]
	// origB.xy = [b1b0, *]	origB.zw = [d1d0, *]
	hkInt64Vector4 absA;	absA.setAbs(origA);
	hkInt64Vector4 absB;	absB.setAbs(origB);
	hkInt64Vector4 absAB;	absAB.setUnsignedMul_128<2>(absA, absB);

	// Set proper signs
	{
		const hkVector4fComparison negA	= origA.lessZero();							// [*, a < 0, *, c < 0]
		const hkVector4fComparison negB	= origB.lessZero();							// [*, b < 0, *, d < 0]
		hkVector4fComparison negZeroA;	negZeroA.setOr(negA, origA.equalZero());	// [*, a <= 0, *, c <= 0]
		hkVector4fComparison negZeroB;	negZeroB.setOr(negB, origB.equalZero());	// [*, b <= 0, *, d <= 0]
		hkVector4fComparison negA_posB;	negA_posB.setAndNot(negA, negZeroB);
		hkVector4fComparison posA_negB;	posA_negB.setAndNot(negB, negZeroA);
		hkVector4fComparison neg;		neg.setOr(negA_posB, posA_negB);			// [*, sign(ab), *, sign(cd)]

		// Set proper signs
		hkVector4fComparison signAb;	signAb.m_mask = _mm_shuffle_ps(neg.m_mask, neg.m_mask, _MM_SHUFFLE(1, 1, 1, 1));
		hkVector4fComparison signCd; signCd.m_mask = _mm_shuffle_ps(neg.m_mask, neg.m_mask, _MM_SHUFFLE(3, 3, 3, 3));
		hkSimdInt<128> tmpAb;		absAB.storeXy(tmpAb);
		hkSimdInt<128> tmpCd;		absAB.storeZw(tmpCd);
		tmpAb.setFlipSign(tmpAb, signAb);
		tmpCd.setFlipSign(tmpCd, signCd);
		loadXy(tmpAb);
		loadZw(tmpCd);
	}
}

//
//	Sets this = vA * vB

inline void hkInt64Vector4::setMul(hkIntVectorParameter origA, hkIntVectorParameter origB)
{
	// Remove signs
	hkIntVector vA;	vA.setAbsS32(origA);
	hkIntVector vB;	vB.setAbsS32(origB);

	// Shuffle
	hkIntVector a_xy;	a_xy.setPermutation<hkVectorPermutation::XXYY>(vA);	// [ax, ax, ay, ay]
	hkIntVector a_zw;	a_zw.setPermutation<hkVectorPermutation::ZZWW>(vA);	// [az, az, aw, aw]
	hkIntVector b_xy;	b_xy.setPermutation<hkVectorPermutation::XXYY>(vB);	// [bx, bx, by, by]
	hkIntVector b_zw;	b_zw.setPermutation<hkVectorPermutation::ZZWW>(vB);	// [bx, bx, by, by]

	// Multiply unsigned values
	hkInt64Vector4 absAB;
	absAB.m_quad.xy = _mm_mul_epu32(a_xy.m_quad, b_xy.m_quad);	// [ax * bx, ay * by]
	absAB.m_quad.zw = _mm_mul_epu32(a_zw.m_quad, b_zw.m_quad);	// [bz * bw, bz * bw]

	// Compute signs
	hkVector4Comparison negA_posB;	negA_posB.setAnd(origA.lessZeroS32(), origB.greaterZeroS32());
	hkVector4Comparison posA_negB;	posA_negB.setAnd(origB.lessZeroS32(), origA.greaterZeroS32());
	hkVector4Comparison negAB;		negAB.setOr(negA_posB, posA_negB);

	// Flip signs if case
#ifdef HK_REAL_IS_DOUBLE
	hkVector4fComparison negABf;	negABf.set(negAB.getMask());
	setFlipSign(absAB, negABf);
#else
	setFlipSign(absAB, negAB);
#endif
}

//
//	Returns the maximum component among the first N.

template <>
inline hkInt64 hkInt64Vector4::horizontalMax<3>() const
{
	__m128d zw	= _mm_castsi128_pd(m_quad.zw);									// [w, z]
	__m128i	zz	= _mm_castpd_si128(_mm_shuffle_pd(zw, zw, _MM_SHUFFLE2(0, 0)));	// [z, z]
	__m128i xy	= hkInt64Vector4Impl::vec2x64_max(m_quad.xy, zz);				// [max(y, z), max(x, z)]

	zw	= _mm_castsi128_pd(xy);
	zz	= _mm_castpd_si128(_mm_shuffle_pd(zw, zw, _MM_SHUFFLE2(0, 1)));			// [max(x, z), max(y, z)]
	zz	= hkInt64Vector4Impl::vec2x64_max(xy, zz);								// max(x, y, z)

#if HK_SSE_VERSION >= 0x41
	return _mm_extract_epi64(zz, 0);
#else
	return HK_M128(zz).m128i_i64[0];
#endif
}

//
//	Sets the I-th component to zero.

template <> inline void hkInt64Vector4::zeroComponent<0>()		{	m_quad.xy = _mm_unpackhi_epi64(_mm_setzero_si128(), m_quad.xy);	}
template <> inline void hkInt64Vector4::zeroComponent<1>()		{	m_quad.xy = _mm_unpacklo_epi64(m_quad.xy, _mm_setzero_si128());	}
template <> inline void hkInt64Vector4::zeroComponent<2>()		{	m_quad.zw = _mm_unpackhi_epi64(_mm_setzero_si128(), m_quad.zw);	}
template <> inline void hkInt64Vector4::zeroComponent<3>()		{	m_quad.zw = _mm_unpacklo_epi64(m_quad.zw, _mm_setzero_si128());	}

//
//	Sets this.z |= Hi[x], this.w |= Lo[x]

// inline void hkInt64Vector4::orZW(const hkSimdInt<128>& x)
// {
// 	const __m128d hilo = _mm_castsi128_pd(x.m_quad);										// [hiX, loX]
// 	const __m128i lohi = _mm_castpd_si128(_mm_shuffle_pd(hilo, hilo, _MM_SHUFFLE2(0, 1)));	// [loX, hiX]
// 
// 	m_quad.zw = _mm_or_si128(m_quad.zw, lohi);	// [w | loX, z | hiX]
// }

//
//	Loads the .xy components of this from a 128-bit int, where x is the High part and y is the Low part.

inline void hkInt64Vector4::loadXy(const hkSimdInt<128>& xyIn)
{
	const __m128d hilo	= _mm_castsi128_pd(xyIn.m_quad);									// [hiX, loX]
	m_quad.xy			= _mm_castpd_si128(_mm_shuffle_pd(hilo, hilo, _MM_SHUFFLE2(0, 1)));	// [loX, hiX]
}

//
//	Loads the .zw components of this from a 128-bit int, where z is the High part and w is the Low part.

inline void hkInt64Vector4::loadZw(const hkSimdInt<128>& zwIn)
{
	const __m128d hilo	= _mm_castsi128_pd(zwIn.m_quad);									// [hiX, loX]
	m_quad.zw			= _mm_castpd_si128(_mm_shuffle_pd(hilo, hilo, _MM_SHUFFLE2(0, 1)));	// [loX, hiX]
}

//
//	Retrieves the x and y components as an 128-bit int i, where x = Hi[i] and y = Lo[i]

inline void hkInt64Vector4::storeXy(hkSimdInt<128>& x) const
{
	const __m128d xy = _mm_castsi128_pd(m_quad.xy);								// [y, x]
	x.m_quad = _mm_castpd_si128(_mm_shuffle_pd(xy, xy, _MM_SHUFFLE2(0, 1)));	// [x, y]
}

//
//	Retrieves the z and w components as an 128-bit int x, where z = Hi[x] and w = Lo[x]

inline void hkInt64Vector4::storeZw(hkSimdInt<128>& x) const
{
	const __m128d wz = _mm_castsi128_pd(m_quad.zw);								// [w, z]
	x.m_quad = _mm_castpd_si128(_mm_shuffle_pd(wz, wz, _MM_SHUFFLE2(0, 1)));	// [z, w]
}

//
//	Sets this = a / b. Both a and b are assumed to be unsigned!

inline void hkInt64Vector4::setUnsignedDiv(hkInt64Vector4Parameter a, hkInt64Vector4Parameter b)
{
	const hkUint64 dx = (hkUint64)a.getComponent<0>() / (hkUint64)b.getComponent<0>();
	const hkUint64 dy = (hkUint64)a.getComponent<1>() / (hkUint64)b.getComponent<1>();
	const hkUint64 dz = (hkUint64)a.getComponent<2>() / (hkUint64)b.getComponent<2>();
	const hkUint64 dw = (hkUint64)a.getComponent<3>() / (hkUint64)b.getComponent<3>();

	set(dx, dy, dz, dw);
}

//
//	Converts the 4 64-bit ints to doubles

inline void hkInt64Vector4::convertS64ToF64(hkVector4d& vOut) const
{
	vOut.set((double)getComponent<0>(), (double)getComponent<1>(), (double)getComponent<2>(), (double)getComponent<3>());
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
