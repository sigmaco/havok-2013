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

inline void hkSimdInt<128>::setFromInt32(hkInt32 i)
{
	const __m128i val = _mm_castps_si128(_mm_load_ss((const float*)&i));											// [0, 0, 0, val]				
	const __m128i sgn = _mm_slli_si128(_mm_srai_epi32(_mm_shuffle_epi32(val, _MM_SHUFFLE(0, 0, 0, 0)), 31), 4);		// [sgn, sgn, sgn, 0]
	m_quad = _mm_or_si128(val, sgn);
}

//
//	Sets this = 0

inline void hkSimdInt<128>::setZero()
{
	m_quad = _mm_setzero_si128();
}

inline void hkSimdInt<128>::setFromInt64(hkInt64 i)
{
	// Load value into lower part
	// The unpacklo is to prevent a bug in VS2008 release, where the upper part of the vector is not zeroed!
	const __m128i val = _mm_unpacklo_epi64(_mm_loadl_epi64((const __m128i*)&i), _mm_setzero_si128());	// [0, val]

	// [sgn, sgn, 0, 0]
	const __m128i sgn = _mm_slli_si128(_mm_srai_epi32(_mm_shuffle_epi32(val, _MM_SHUFFLE(1, 1, 1, 1)), 31), 8);
	m_quad = _mm_or_si128(val, sgn);
}

inline void hkSimdInt<128>::setFromUint64(hkUint64 i)
{
	// Load value into lower part
	// The unpacklo is to prevent a bug in VS2008 release, where the upper part of the vector is not zeroed!
	m_quad = _mm_unpacklo_epi64(_mm_loadl_epi64((const __m128i*)&i), _mm_setzero_si128());	// [0, val]
}

//
//	Sets this = a + b

inline void hkSimdInt<128>::setAdd(const hkSimdInt<128>& origA, const hkSimdInt<128>& origB)
{
	// a = [a1, a0]
	// b = [b1, b0]
	const __m128i ab		= _mm_add_epi64(origA.m_quad, origB.m_quad);    // [lo(a1 + b1), lo(a0 + b0)]

	// Compare ab < a unsigned.
	const __m128i m			= _mm_set1_epi32(0x80000000);
	const __m128i mSum		= _mm_xor_si128(ab, m);
	const __m128i mA		= _mm_xor_si128(origA.m_quad, m);
	const __m128i t			= _mm_cmplt_epi32(mSum, mA);
	const __m128i u			= _mm_cmpgt_epi32(mSum, mA);
	const __m128i z			= _mm_or_si128(t, _mm_shuffle_epi32(t, _MM_SHUFFLE(2, 3, 0, 1)));
	const __m128i carry		= _mm_slli_si128(_mm_srli_epi64(_mm_andnot_si128(_mm_shuffle_epi32(u, _MM_SHUFFLE(3, 3, 1, 1)), z), 63), 8);

	m_quad = _mm_add_epi64(ab, carry);
}

//
//	Increments this = this + 1 (faster than add(1)).

inline void hkSimdInt<128>::increment()
{
	// a = [a1, a0]
	// b = [b1, b0]
	const __m128i m			= _mm_set1_epi32(0x80000000);
	const __m128i ab		= _mm_add_epi64(m_quad, _mm_srli_epi32(_mm_srli_si128(m, 12), 31));    // [lo(a1 + b1), lo(a0 + b0)]

	// Compare ab < a unsigned.
	const __m128i mSum		= _mm_xor_si128(ab, m);
	const __m128i mA		= _mm_xor_si128(m_quad, m);
	const __m128i t			= _mm_cmplt_epi32(mSum, mA);
	const __m128i u			= _mm_cmpgt_epi32(mSum, mA);
	const __m128i z			= _mm_or_si128(t, _mm_shuffle_epi32(t, _MM_SHUFFLE(2, 3, 0, 1)));
	const __m128i carry		= _mm_slli_si128(_mm_srli_epi64(_mm_andnot_si128(_mm_shuffle_epi32(u, _MM_SHUFFLE(3, 3, 1, 1)), z), 63), 8);

	m_quad = _mm_add_epi64(ab, carry);
}

//
//	Returns this < 0

template <> inline const hkVector4fComparison hkSimdInt<128>::lessZero<hkVector4fComparison>() const
{
	// We need to put the sign bit everywhere
	const __m128i a3333 = _mm_shuffle_epi32(_mm_srai_epi32(m_quad, 31), _MM_SHUFFLE(3, 3, 3, 3));
	return hkVector4fComparison::convert(_mm_castsi128_ps(a3333));
}

template <> inline const hkVector4dComparison hkSimdInt<128>::lessZero<hkVector4dComparison>() const
{
	// We need to put the sign bit everywhere
	const __m128i a3333 = _mm_shuffle_epi32(_mm_srai_epi32(m_quad, 31), _MM_SHUFFLE(3, 3, 3, 3));
	hkVector4dComparison cmp;
	cmp.m_mask.xy = cmp.m_mask.zw = _mm_castsi128_pd(a3333);
	return cmp;
}

inline const hkVector4fComparison hkSimdInt<128>::lessZero() const
{
	return lessZero<hkVector4fComparison>();
}

//
//	Returns this == 0

template <> inline const hkVector4fComparison hkSimdInt<128>::equalZero<hkVector4fComparison>() const
{
#if (HK_SSE_VERSION >= 0x41)
	const __m128i xy = _mm_cmpeq_epi64(m_quad,_mm_setzero_si128());		// [x, x, y, y]
	const __m128i yx = _mm_shuffle_epi32(xy, _MM_SHUFFLE(1, 0, 3, 2));	// [y, y, x, x]
	return hkVector4fComparison::convert(_mm_castsi128_ps(_mm_and_si128(xy, yx)));
#else
	hkVector4fComparison cmp;
	cmp.m_mask = _mm_castsi128_ps(_mm_cmpeq_epi32(m_quad, _mm_setzero_si128()));
	return cmp.horizontalAnd<4>();
#endif
}

template <> inline const hkVector4dComparison hkSimdInt<128>::equalZero<hkVector4dComparison>() const
{
	hkVector4dComparison ret;

#if (HK_SSE_VERSION >= 0x41)
	const __m128i xy = _mm_cmpeq_epi64(m_quad,_mm_setzero_si128());		// [x, x, y, y]
	const __m128i yx = _mm_shuffle_epi32(xy, _MM_SHUFFLE(1, 0, 3, 2));	// [y, y, x, x]
	ret.m_mask.xy = ret.m_mask.zw = _mm_castsi128_ps(_mm_and_si128(xy, yx));
#else
	hkVector4fComparison cmp;
	cmp.m_mask = _mm_castsi128_ps(_mm_cmpeq_epi32(m_quad, _mm_setzero_si128()));
	ret.m_mask.xy = ret.m_mask.zw = _mm_castps_pd(cmp.horizontalAnd<4>().m_mask);
#endif

	return ret;
}

inline const hkVector4fComparison hkSimdInt<128>::equalZero() const
{
	return equalZero<hkVector4fComparison>();
}

//
//	Returns this == v

inline const hkVector4fComparison hkSimdInt<128>::equal(const hkSimdInt<128>& v) const
{
#if (HK_SSE_VERSION >= 0x41)
	const __m128i xy = _mm_cmpeq_epi64(m_quad, v.m_quad);				// [x, x, y, y]
	const __m128i yx = _mm_shuffle_epi32(xy, _MM_SHUFFLE(1, 0, 3, 2));	// [y, y, x, x]
	return hkVector4fComparison::convert(_mm_castsi128_ps(_mm_and_si128(xy, yx)));
#else
	hkVector4fComparison cmp;
	cmp.m_mask = _mm_castsi128_ps(_mm_cmpeq_epi32(m_quad, v.m_quad));
	return cmp.horizontalAnd<4>();
#endif
}

//
//	Sets this = cmp ? vTrue : vFalse

inline void hkSimdInt<128>::setSelect(hkVector4fComparisonParameter cmp, const hkSimdInt<128>& vTrue, const hkSimdInt<128>& vFalse)
{
	const __m128i m = _mm_castps_si128(cmp.m_mask);
#if ( HK_SSE_VERSION >= 0x41 )
	m_quad = _mm_blendv_epi8(vFalse.m_quad, vTrue.m_quad, m);
#else
	m_quad = _mm_or_si128(_mm_and_si128(m, vTrue.m_quad), _mm_andnot_si128(m, vFalse.m_quad));
#endif
}

//
//	Sets this = a & b

inline void hkSimdInt<128>::setAnd(const hkSimdInt<128>& a, const hkSimdInt<128>& b)
{
	m_quad = _mm_and_si128(a.m_quad, b.m_quad);
}

//
//	Sets this = a | b

inline void hkSimdInt<128>::setOr(const hkSimdInt<128>& a, const hkSimdInt<128>& b)
{
	m_quad = _mm_or_si128(a.m_quad, b.m_quad);
}

//
//	Sets this = ~a

inline void hkSimdInt<128>::setNot(const hkSimdInt<128>& v)
{
	m_quad =  _mm_andnot_si128(v.m_quad, _mm_set1_epi32(-1));
}

//
//	Sets this = a << I

template <> inline void hkSimdInt<128>::setShiftLeft<0>	(const hkSimdInt<128>& a)	{ m_quad = a.m_quad; }
template <> inline void hkSimdInt<128>::setShiftLeft<8>	(const hkSimdInt<128>& a)	{ m_quad = _mm_slli_si128(a.m_quad, 1); }
template <> inline void hkSimdInt<128>::setShiftLeft<16>	(const hkSimdInt<128>& a)	{ m_quad = _mm_slli_si128(a.m_quad, 2); }
template <> inline void hkSimdInt<128>::setShiftLeft<24>	(const hkSimdInt<128>& a)	{ m_quad = _mm_slli_si128(a.m_quad, 3); }
template <> inline void hkSimdInt<128>::setShiftLeft<32>	(const hkSimdInt<128>& a)	{ m_quad = _mm_slli_si128(a.m_quad, 4); }
template <> inline void hkSimdInt<128>::setShiftLeft<40>	(const hkSimdInt<128>& a)	{ m_quad = _mm_slli_si128(a.m_quad, 5); }
template <> inline void hkSimdInt<128>::setShiftLeft<48>	(const hkSimdInt<128>& a)	{ m_quad = _mm_slli_si128(a.m_quad, 6); }
template <> inline void hkSimdInt<128>::setShiftLeft<56>	(const hkSimdInt<128>& a)	{ m_quad = _mm_slli_si128(a.m_quad, 7); }
template <> inline void hkSimdInt<128>::setShiftLeft<64>	(const hkSimdInt<128>& a)	{ m_quad = _mm_slli_si128(a.m_quad, 8); }
template <> inline void hkSimdInt<128>::setShiftLeft<72>	(const hkSimdInt<128>& a)	{ m_quad = _mm_slli_si128(a.m_quad, 9); }
template <> inline void hkSimdInt<128>::setShiftLeft<80>	(const hkSimdInt<128>& a)	{ m_quad = _mm_slli_si128(a.m_quad, 10); }
template <> inline void hkSimdInt<128>::setShiftLeft<88>	(const hkSimdInt<128>& a)	{ m_quad = _mm_slli_si128(a.m_quad, 11); }
template <> inline void hkSimdInt<128>::setShiftLeft<96>	(const hkSimdInt<128>& a)	{ m_quad = _mm_slli_si128(a.m_quad, 12); }
template <> inline void hkSimdInt<128>::setShiftLeft<104>	(const hkSimdInt<128>& a)	{ m_quad = _mm_slli_si128(a.m_quad, 13); }
template <> inline void hkSimdInt<128>::setShiftLeft<112>	(const hkSimdInt<128>& a)	{ m_quad = _mm_slli_si128(a.m_quad, 14); }
template <> inline void hkSimdInt<128>::setShiftLeft<120>	(const hkSimdInt<128>& a)	{ m_quad = _mm_slli_si128(a.m_quad, 15); }
template <> inline void hkSimdInt<128>::setShiftLeft<128>	(const hkSimdInt<128>& a)	{ m_quad = _mm_setzero_si128(); }

template <int I>
inline void hkSimdInt<128>::setShiftLeft(const hkSimdInt<128>& a)
{
	// Shift first part, in number of bytes
	const __m128i tmpShift = _mm_slli_si128(a.m_quad, ((I) >> 3));

	// Shift rest, with the remaining number of bits
	// tmpShift = [hi, lo]
	// shiftR	= [hi, lo] >> (64 - (N & 7)) = most significant (N & 7) bits
	__m128i shiftR = _mm_srli_epi64(tmpShift, 64 - (I & 7));

	// shiftR	= [0x0...0lo, 0] 
	shiftR = _mm_castps_si128(_mm_shuffle_ps(_mm_setzero_ps(), _mm_castsi128_ps(shiftR), _MM_SHUFFLE(1, 0, 1, 0)));		
	m_quad = _mm_or_si128(_mm_slli_epi64(tmpShift, I & 7), shiftR);
}

//
//	Sets this = a >> I

template <> inline void hkSimdInt<128>::setShiftRight<0, HK_VALUE_UNSIGNED>	(const hkSimdInt<128>& a)	{ m_quad = a.m_quad; }
template <> inline void hkSimdInt<128>::setShiftRight<8, HK_VALUE_UNSIGNED>	(const hkSimdInt<128>& a)	{ m_quad = _mm_srli_si128(a.m_quad, 1); }
template <> inline void hkSimdInt<128>::setShiftRight<16, HK_VALUE_UNSIGNED>	(const hkSimdInt<128>& a)	{ m_quad = _mm_srli_si128(a.m_quad, 2); }
template <> inline void hkSimdInt<128>::setShiftRight<24, HK_VALUE_UNSIGNED>	(const hkSimdInt<128>& a)	{ m_quad = _mm_srli_si128(a.m_quad, 3); }
template <> inline void hkSimdInt<128>::setShiftRight<32, HK_VALUE_UNSIGNED>	(const hkSimdInt<128>& a)	{ m_quad = _mm_srli_si128(a.m_quad, 4); }
template <> inline void hkSimdInt<128>::setShiftRight<40, HK_VALUE_UNSIGNED>	(const hkSimdInt<128>& a)	{ m_quad = _mm_srli_si128(a.m_quad, 5); }
template <> inline void hkSimdInt<128>::setShiftRight<48, HK_VALUE_UNSIGNED>	(const hkSimdInt<128>& a)	{ m_quad = _mm_srli_si128(a.m_quad, 6); }
template <> inline void hkSimdInt<128>::setShiftRight<56, HK_VALUE_UNSIGNED>	(const hkSimdInt<128>& a)	{ m_quad = _mm_srli_si128(a.m_quad, 7); }
template <> inline void hkSimdInt<128>::setShiftRight<64, HK_VALUE_UNSIGNED>	(const hkSimdInt<128>& a)	{ m_quad = _mm_srli_si128(a.m_quad, 8); }
template <> inline void hkSimdInt<128>::setShiftRight<72, HK_VALUE_UNSIGNED>	(const hkSimdInt<128>& a)	{ m_quad = _mm_srli_si128(a.m_quad, 9); }
template <> inline void hkSimdInt<128>::setShiftRight<80, HK_VALUE_UNSIGNED>	(const hkSimdInt<128>& a)	{ m_quad = _mm_srli_si128(a.m_quad, 10); }
template <> inline void hkSimdInt<128>::setShiftRight<88, HK_VALUE_UNSIGNED>	(const hkSimdInt<128>& a)	{ m_quad = _mm_srli_si128(a.m_quad, 11); }
template <> inline void hkSimdInt<128>::setShiftRight<96, HK_VALUE_UNSIGNED>	(const hkSimdInt<128>& a)	{ m_quad = _mm_srli_si128(a.m_quad, 12); }
template <> inline void hkSimdInt<128>::setShiftRight<104, HK_VALUE_UNSIGNED>	(const hkSimdInt<128>& a)	{ m_quad = _mm_srli_si128(a.m_quad, 13); }
template <> inline void hkSimdInt<128>::setShiftRight<112, HK_VALUE_UNSIGNED>	(const hkSimdInt<128>& a)	{ m_quad = _mm_srli_si128(a.m_quad, 14); }
template <> inline void hkSimdInt<128>::setShiftRight<120, HK_VALUE_UNSIGNED>	(const hkSimdInt<128>& a)	{ m_quad = _mm_srli_si128(a.m_quad, 15); }
template <> inline void hkSimdInt<128>::setShiftRight<128, HK_VALUE_UNSIGNED>	(const hkSimdInt<128>& a)	{ m_quad = _mm_setzero_si128(); }

namespace hkSimdInt128Impl
{
	template <int N, hkMathValueType VAL> struct Shr {};

	template <int N> struct Shr<N, HK_VALUE_UNSIGNED>
	{
		static inline void HK_CALL shr(const hkSimdInt<128>& iIn, hkSimdInt<128>& iOut)
		{
			// Shift first part, in number of bytes
			const __m128i tmpShift = _mm_srli_si128(iIn.m_quad, ((N) >> 3));

			// Shift rest, with the remaining number of bits
			// tmpShift = [hi, lo]
			// shiftR	= [hi, lo] << (64 - (N & 7)) = least significant (N & 7) bits
			__m128i shiftL = _mm_slli_epi64(tmpShift, 64 - (N & 7));

			// shiftR	= [0, 0x0...0hi] 
			shiftL = _mm_castps_si128(_mm_shuffle_ps(_mm_castsi128_ps(shiftL), _mm_setzero_ps(), _MM_SHUFFLE(1, 0, 3, 2)));		
			iOut.m_quad = _mm_or_si128(_mm_srli_epi64(tmpShift, N & 7), shiftL);
		}
	};

	template <int N> struct Shr<N, HK_VALUE_SIGNED>
	{
		static inline void HK_CALL shr(const hkSimdInt<128>& iIn, hkSimdInt<128>& iOut)
		{
			hkSimdInt<128> u;	u.setShiftRight<N, HK_VALUE_UNSIGNED>(iIn);
			hkSimdInt<128> s;	s.m_quad = _mm_srai_epi32(_mm_shuffle_epi32(iIn.m_quad, _MM_SHUFFLE(3, 3, 3, 3)), 31);
			s.setShiftLeft<128 - N>(s);
			iOut.setOr(u, s);
		}
	};
}

template <int I, hkMathValueType VAL>
inline void hkSimdInt<128>::setShiftRight(const hkSimdInt<128>& a)
{
	hkSimdInt128Impl::Shr<I, VAL>::shr(a, *this);
}

template <int I>
inline void hkSimdInt<128>::setShiftRight(const hkSimdInt<128>& a)
{
	setShiftRight<I, HK_VALUE_UNSIGNED>(a);
}

//
//	Returns the I-th 32-bit word, where LSB = 0, MSB = 3

template <>	inline int hkSimdInt<128>::getWord<0>() const	{	return _mm_cvtsi128_si32(m_quad);	}
template <int I>
inline int hkSimdInt<128>::getWord() const
{
#if HK_SSE_VERSION >= 0x41
	return _mm_extract_epi32(m_quad, I);
#else
	return _mm_cvtsi128_si32(_mm_shuffle_epi32(m_quad, _MM_SHUFFLE(I,I,I,I)));
#endif
}

//
//	Returns the I-th 64-bit word, where LSB = 0, MSB = 3

template <int I> inline hkInt64 hkSimdInt<128>::getDoubleWord() const
{
#if HK_SSE_VERSION >= 0x41
	return _mm_extract_epi64(m_quad, I);
#else
	return HK_M128(m_quad).m128i_i64[I];
#endif
}

//
//	Returns the number of leading zeros

inline int hkSimdInt<128>::countLeadingZeros() const
{
	const int nz1 = (int)hkMath::countLeadingZeros<hkUint64>(getDoubleWord<1>());
	const int nz0 = (int)hkMath::countLeadingZeros<hkUint64>(getDoubleWord<0>());
	return nz1 + (nz1 >> 6) * nz0;
}

//
//	Returns the number of trailing zeros

inline int hkSimdInt<128>::countTrailingZeros() const
{
	const int nz1 = hkMath::countTrailingZeros<hkUint64>(getDoubleWord<1>());
	const int nz0 = hkMath::countTrailingZeros<hkUint64>(getDoubleWord<0>());
	return	nz0 + (nz0 < 64 ? 0 : nz1);
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
