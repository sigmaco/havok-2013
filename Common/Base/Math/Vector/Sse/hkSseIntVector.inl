/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

/// Features available in SSE:
#define HK_INT_VECTOR_NATIVE_MISALIGNED
#define HK_INT_VECTOR_NATIVE_LOGIC
#define HK_INT_VECTOR_NATIVE_ARITH
#define HK_INT_VECTOR_NATIVE_FIXEDSHIFT
#define HK_INT_VECTOR_NATIVE_BYTESHIFT128
// #define HK_INT_VECTOR_NATIVE_BITSHIFT128 // No whole-vector bitshifting in SSE
// #define HK_INT_VECTOR_NATIVE_VARIABLESHIFT // No variable vector shifts in SSE
#define HK_INT_VECTOR_NATIVE_MERGEPACK
#define HK_INT_VECTOR_NATIVE_SHUFFLE
#define HK_INT_VECTOR_NATIVE_VPERM
#define HK_INT_VECTOR_NATIVE_SPLAT
#define HK_INT_VECTOR_NATIVE_FLOATCONV

#define HK_INT_VECTOR_loadAsFloat32BitRepresentation
HK_FORCE_INLINE void hkIntVector::loadAsFloat32BitRepresentation(const hkVector4d& x)
{
#if HK_SSE_VERSION >= 0x50
	__m128 xyzw = _mm256_cvtpd_ps(x.m_quad);
	this->m_quad = _mm_castps_si128(xyzw);
#else
	HK_WARN_ONCE_ON_DEBUG_IF( true, 0x9f75ba24, "loadAsFloat32BitRepresentation is not fully checked - enforcing a copy" );
	__m128 xy = _mm_cvtpd_ps(x.m_quad.xy);
	__m128 zw = _mm_cvtpd_ps(x.m_quad.zw);
	__m128 xyzw = _mm_shuffle_ps(xy,zw,_MM_SHUFFLE(1,0,1,0));
	this->m_quad = _mm_castps_si128(xyzw);
#endif
}

HK_FORCE_INLINE void hkIntVector::storeAsFloat32BitRepresentation( hkVector4d& out ) const
{
	out.load<4>( (hkFloat32*)this );
}

HK_FORCE_INLINE void hkIntVector::loadAsFloat32BitRepresentation(const hkVector4f& x)
{
	this->m_quad = _mm_castps_si128(x.m_quad);
}

HK_FORCE_INLINE void hkIntVector::storeAsFloat32BitRepresentation( hkVector4f& out ) const
{
	out.m_quad = _mm_castsi128_ps(this->m_quad);
}

//
// Clearing, loading, and storing
//

HK_FORCE_INLINE void hkIntVector::setZero()
{
	m_quad = _mm_setzero_si128();
}

HK_FORCE_INLINE void hkIntVector::setAll(const int& i)
{
	m_quad = _mm_set1_epi32(i);
}

HK_FORCE_INLINE void hkIntVector::setFirstComponent(int value)
{
	m_quad = _mm_cvtsi32_si128(value);
}

#if HK_SSE_VERSION >= 0x41
template <int I>
HK_FORCE_INLINE void hkIntVector::setComponent(int value)
{
	HK_INT_VECTOR_SUBINDEX_CHECK;
	m_quad = _mm_insert_epi32(m_quad, value, I);
}
#else
template <>
HK_FORCE_INLINE void hkIntVector::setComponent<0>(int value)
{
	hkQuadUint val = _mm_set1_epi32(value);
	m_quad = _mm_castps_si128(_mm_move_ss( _mm_castsi128_ps(m_quad), _mm_castsi128_ps(val) ));
}
template <>
HK_FORCE_INLINE void hkIntVector::setComponent<1>(int value)
{
	hkQuadUint val = _mm_set1_epi32(value);
	__m128 q = _mm_castsi128_ps(m_quad);
	m_quad = _mm_castps_si128(_mm_shuffle_ps( _mm_unpacklo_ps(q, _mm_castsi128_ps(val)), q, _MM_SHUFFLE(3,2,1,0)));
}
template <>
HK_FORCE_INLINE void hkIntVector::setComponent<2>(int value)
{
	hkQuadUint val = _mm_set1_epi32(value);
	__m128 q = _mm_castsi128_ps(m_quad);
	m_quad = _mm_castps_si128(_mm_shuffle_ps( q, _mm_unpackhi_ps(q, _mm_castsi128_ps(val)), _MM_SHUFFLE(2,3,1,0)));
}
template <>
HK_FORCE_INLINE void hkIntVector::setComponent<3>(int value)
{
	hkQuadUint val = _mm_set1_epi32(value);
	__m128 q = _mm_castsi128_ps(m_quad);
	m_quad = _mm_castps_si128(_mm_shuffle_ps( q, _mm_unpackhi_ps(q, _mm_castsi128_ps(val)), _MM_SHUFFLE(3,0,1,0)));
}
template <int N>
HK_FORCE_INLINE void hkIntVector::setComponent(int value)
{
	HK_INT_VECTOR_NOT_IMPLEMENTED;
}
#endif

HK_FORCE_INLINE void hkIntVector::setComponent(int componentIdx, int value)
{
	hkVector4fComparison cmp;	cmp.set((hkVector4fComparison::Mask)(hkVector4ComparisonMask::MASK_X << componentIdx));
	const __m128i cmpMask		= _mm_castps_si128(cmp.m_mask);
	const __m128i val			= _mm_set1_epi32(value);

	m_quad = _mm_or_si128(_mm_and_si128(cmpMask, val), _mm_andnot_si128(cmpMask, m_quad));
}

HK_FORCE_INLINE void hkIntVector::set(int x, int y, int z, int w)
{
	m_quad = _mm_setr_epi32(x, y, z, w);
}

template <>
HK_FORCE_INLINE int hkIntVector::getComponent<0>() const
{
	return _mm_cvtsi128_si32(m_quad);
}

template <int I>
HK_FORCE_INLINE int hkIntVector::getComponent() const
{
	HK_INT_VECTOR_SUBINDEX_CHECK;
#if HK_SSE_VERSION >= 0x41
	return _mm_extract_epi32(m_quad, I);
#else
	return _mm_cvtsi128_si32(_mm_shuffle_epi32(m_quad, _MM_SHUFFLE(I,I,I,I)));
#endif
}

template <int I>
HK_FORCE_INLINE hkUint8  hkIntVector::getU8 () const
{
	HK_COMPILE_TIME_ASSERT2((I>=0)&&(I<16), HK_INT_VECTOR_SUBVECTOR_INDEX_OUT_OF_RANGE);
#if HK_SSE_VERSION >= 0x41
	return hkUint8(_mm_extract_epi8(m_quad, I));
#else
#if defined(HK_COMPILER_GCC) && (HK_COMPILER_GCC_VERSION < 40600)
	return ((const hkUint8*)this)[I];
#else
	return HK_M128(m_quad).m128i_u8[I];
#endif
#endif
}

template <int I>
HK_FORCE_INLINE hkUint16 hkIntVector::getU16() const
{
	HK_COMPILE_TIME_ASSERT2((I>=0)&&(I<8), HK_INT_VECTOR_SUBVECTOR_INDEX_OUT_OF_RANGE);
	return hkUint16(_mm_extract_epi16(m_quad, I));
}

template <int I>
HK_FORCE_INLINE hkUint32 hkIntVector::getU32() const
{
	return getComponent<I>();
}

HK_FORCE_INLINE hkUint32 hkIntVector::getU32(int idx) const
{
	HK_MATH_ASSERT(0xfabb2300, idx>=0 && idx<4, "int vector subindex out of range");
	return HK_M128(m_quad).m128i_u32[idx];
}

HK_FORCE_INLINE int hkIntVector::getComponent(int idx) const
{
	HK_MATH_ASSERT(0x6d0c31d7, (idx >= 0) && (idx < 4), "index out of bounds for component access");
	switch ( idx )
	{
	case 1:  return getComponent<1>();
	case 2:  return getComponent<2>();
	case 3:  return getComponent<3>();
	default: return getComponent<0>();
	}
}

template <>
HK_FORCE_INLINE void hkIntVector::loadNotAligned<4>(const hkUint32* p)
{
	m_quad = _mm_loadu_si128((const __m128i*) p);
}

template <>
HK_FORCE_INLINE void hkIntVector::loadNotAligned<3>(const hkUint32* p)
{
	m_quad = _mm_set_epi32(0, p[2], p[1], p[0]);
	HK_ON_DEBUG(HK_M128(m_quad).m128i_u32[3] = 0xffffffff;)
}

template <>
HK_FORCE_INLINE void hkIntVector::loadNotAligned<2>(const hkUint32* p)
{
	m_quad = _mm_loadl_epi64((const __m128i*)p);
	HK_ON_DEBUG(HK_M128(m_quad).m128i_u32[2] = 0xffffffff; HK_M128(m_quad).m128i_u32[3] = 0xffffffff;)
}

template <>
HK_FORCE_INLINE void hkIntVector::loadNotAligned<1>(const hkUint32* p)
{
	m_quad = _mm_castps_si128(_mm_load_ss((const float*)p));
	HK_ON_DEBUG(HK_M128(m_quad).m128i_u32[1] = 0xffffffff; HK_M128(m_quad).m128i_u32[2] = 0xffffffff; HK_M128(m_quad).m128i_u32[3] = 0xffffffff;)
}

template <int N>
HK_FORCE_INLINE void hkIntVector::loadNotAligned(const hkUint32* p)
{
	HK_INT_VECTOR_NOT_IMPLEMENTED;
}

template <>
HK_FORCE_INLINE void hkIntVector::storeNotAligned<4>(hkUint32* p) const
{
	_mm_storeu_si128((__m128i*) p, m_quad);
}

template <>
HK_FORCE_INLINE void hkIntVector::storeNotAligned<3>(hkUint32* p) const
{
	_mm_storel_epi64((__m128i*) p, m_quad);
	const hkQuadUint p2 = _mm_shuffle_epi32(m_quad,_MM_SHUFFLE(2,2,2,2));
	_mm_store_ss((float*)(p+2), _mm_castsi128_ps(p2));
}

template <>
HK_FORCE_INLINE void hkIntVector::storeNotAligned<2>(hkUint32* p) const
{
	_mm_storel_epi64((__m128i*) p, m_quad);
}

template <>
HK_FORCE_INLINE void hkIntVector::storeNotAligned<1>(hkUint32* p) const
{
	_mm_store_ss((float*)p, _mm_castsi128_ps(m_quad));
}

template <int N>
HK_FORCE_INLINE void hkIntVector::storeNotAligned(hkUint32* p) const
{
	HK_INT_VECTOR_NOT_IMPLEMENTED;
}

//
// Logical operations
//

HK_FORCE_INLINE void hkIntVector::setNot(hkIntVectorParameter a)
{
	m_quad = _mm_andnot_si128(a.m_quad, _mm_set1_epi32(-1));
}

HK_FORCE_INLINE hkBool32 hkIntVector::isNegativeAssumingAllValuesEqual(  ) const
{
	HK_MATH_ASSERT(0x252d00fa, HK_M128(m_quad).m128i_u32[0] == HK_M128(m_quad).m128i_u32[1] && HK_M128(m_quad).m128i_u32[0] == HK_M128(m_quad).m128i_u32[2] && HK_M128(m_quad).m128i_u32[0] == HK_M128(m_quad).m128i_u32[3], "assumption all values equal failed");
	return _mm_movemask_ps( _mm_castsi128_ps(m_quad) );
}

HK_FORCE_INLINE const hkVector4Comparison hkIntVector::compareLessThanS32(hkIntVectorParameter b) const
{
#ifdef HK_REAL_IS_DOUBLE
	__m128i m = _mm_cmplt_epi32(m_quad, b.m_quad);
	__m128i xxyy = _mm_unpacklo_epi32(m,m);
	__m128i zzww = _mm_unpackhi_epi32(m,m);
	hkVector4dComparison cmp;
#if HK_SSE_VERSION >= 0x50
	__m256d c = _mm256_broadcast_pd((const __m128d*)&xxyy);
	cmp.m_mask = _mm256_insertf128_pd(c, _mm_castsi128_pd(zzww), 1);
#else
	cmp.m_mask.xy = _mm_castsi128_pd(xxyy);
	cmp.m_mask.zw = _mm_castsi128_pd(zzww);
#endif
	return cmp;
#else
	__m128i m = _mm_cmplt_epi32(m_quad, b.m_quad);
	return hkVector4fComparison::convert(_mm_castsi128_ps(m));
#endif
}

HK_FORCE_INLINE const hkVector4Comparison hkIntVector::lessZeroS32() const
{
	__m128i m = _mm_cmplt_epi32(m_quad, _mm_setzero_si128());
#if defined(HK_REAL_IS_DOUBLE)
	hkVector4Comparison cmp;
	__m128i xxyy = _mm_unpacklo_epi32(m,m);
	__m128i zzww = _mm_unpackhi_epi32(m,m);
#if HK_SSE_VERSION >= 0x50
	__m256d c = _mm256_broadcast_pd((const __m128d*)&xxyy);
	cmp.m_mask = _mm256_insertf128_pd(c, _mm_castsi128_pd(zzww), 1);
#else
	cmp.m_mask.xy = _mm_castsi128_pd(xxyy);
	cmp.m_mask.zw = _mm_castsi128_pd(zzww);
#endif
	return cmp;
#else
	return hkVector4Comparison::convert(_mm_castsi128_ps(m));
#endif
}

HK_FORCE_INLINE const hkVector4Comparison hkIntVector::equalZeroS32() const
{
	__m128i m = _mm_cmpeq_epi32(m_quad, _mm_setzero_si128());
#if defined(HK_REAL_IS_DOUBLE)
	hkVector4Comparison cmp;
	__m128i xxyy = _mm_unpacklo_epi32(m,m);
	__m128i zzww = _mm_unpackhi_epi32(m,m);
#if HK_SSE_VERSION >= 0x50
	__m256d c = _mm256_broadcast_pd((const __m128d*)&xxyy);
	cmp.m_mask = _mm256_insertf128_pd(c, _mm_castsi128_pd(zzww), 1);
#else
	cmp.m_mask.xy = _mm_castsi128_pd(xxyy);
	cmp.m_mask.zw = _mm_castsi128_pd(zzww);
#endif
	return cmp;
#else
	return hkVector4Comparison::convert(_mm_castsi128_ps(m));
#endif
}

HK_FORCE_INLINE const hkVector4Comparison hkIntVector::greaterZeroS32() const
{
	__m128i m = _mm_cmpgt_epi32(m_quad, _mm_setzero_si128());
#if defined(HK_REAL_IS_DOUBLE)
	hkVector4Comparison cmp;
	__m128i xxyy = _mm_unpacklo_epi32(m,m);
	__m128i zzww = _mm_unpackhi_epi32(m,m);
#if HK_SSE_VERSION >= 0x50
	__m256d c = _mm256_broadcast_pd((const __m128d*)&xxyy);
	cmp.m_mask = _mm256_insertf128_pd(c, _mm_castsi128_pd(zzww), 1);
#else
	cmp.m_mask.xy = _mm_castsi128_pd(xxyy);
	cmp.m_mask.zw = _mm_castsi128_pd(zzww);
#endif
	return cmp;
#else
	return hkVector4Comparison::convert(_mm_castsi128_ps(m));
#endif
}

HK_FORCE_INLINE const hkVector4Comparison hkIntVector::greaterEqualS32(hkIntVectorParameter b) const
{
	__m128i m = _mm_or_si128(_mm_cmpgt_epi32(m_quad, b.m_quad), _mm_cmpeq_epi32(m_quad, b.m_quad));
#if defined(HK_REAL_IS_DOUBLE)
	hkVector4Comparison cmp;
	__m128i xxyy = _mm_unpacklo_epi32(m,m);
	__m128i zzww = _mm_unpackhi_epi32(m,m);
#if HK_SSE_VERSION >= 0x50
	__m256d c = _mm256_broadcast_pd((const __m128d*)&xxyy);
	cmp.m_mask = _mm256_insertf128_pd(c, _mm_castsi128_pd(zzww), 1);
#else
	cmp.m_mask.xy = _mm_castsi128_pd(xxyy);
	cmp.m_mask.zw = _mm_castsi128_pd(zzww);
#endif
	return cmp;
#else
	return hkVector4Comparison::convert(_mm_castsi128_ps(m));
#endif
}

HK_FORCE_INLINE const hkVector4Comparison hkIntVector::compareEqualS32( hkIntVectorParameter b ) const
{
#ifdef HK_REAL_IS_DOUBLE
	__m128i m = _mm_cmpeq_epi32(m_quad, b.m_quad);
	__m128i xxyy = _mm_unpacklo_epi32(m,m);
	__m128i zzww = _mm_unpackhi_epi32(m,m);
	hkVector4dComparison cmp;
#if HK_SSE_VERSION >= 0x50
	__m256d c = _mm256_broadcast_pd((const __m128d*)&xxyy);
	cmp.m_mask = _mm256_insertf128_pd(c, _mm_castsi128_pd(zzww), 1);
#else
	cmp.m_mask.xy = _mm_castsi128_pd(xxyy);
	cmp.m_mask.zw = _mm_castsi128_pd(zzww);
#endif
	return cmp;
#else
	__m128i m = _mm_cmpeq_epi32(m_quad, b.m_quad);
	return hkVector4fComparison::convert(_mm_castsi128_ps(m));
#endif
}

HK_FORCE_INLINE void hkIntVector::setOr(hkIntVectorParameter a, hkIntVectorParameter b)
{
	m_quad = _mm_or_si128(a.m_quad, b.m_quad);
}

HK_FORCE_INLINE void hkIntVector::setAnd(hkIntVectorParameter a, hkIntVectorParameter b)
{
	m_quad = _mm_and_si128(a.m_quad, b.m_quad);
}

HK_FORCE_INLINE void hkIntVector::setXor(hkIntVectorParameter a, hkIntVectorParameter b)
{
	m_quad = _mm_xor_si128(a.m_quad, b.m_quad);
}

HK_FORCE_INLINE void hkIntVector::setAndNot(hkIntVectorParameter a, hkIntVectorParameter b)
{
	m_quad = _mm_andnot_si128(b.m_quad, a.m_quad);
}

//
// Arithmetic operations
//

HK_FORCE_INLINE void hkIntVector::setSubU16( hkIntVectorParameter a, hkIntVectorParameter b )
{
	m_quad = _mm_sub_epi16( a.m_quad, b.m_quad );
}

HK_FORCE_INLINE void hkIntVector::setAddU16( hkIntVectorParameter a, hkIntVectorParameter b )
{
	m_quad = _mm_add_epi16( a.m_quad, b.m_quad );
}

HK_FORCE_INLINE void hkIntVector::setSubU32( hkIntVectorParameter a, hkIntVectorParameter b )
{
	m_quad = _mm_sub_epi32( a.m_quad, b.m_quad );
}

HK_FORCE_INLINE void hkIntVector::setSubS32( hkIntVectorParameter a, hkIntVectorParameter b )
{
	m_quad = _mm_sub_epi32( a.m_quad, b.m_quad );
}

HK_FORCE_INLINE void hkIntVector::setAddS32( hkIntVectorParameter a, hkIntVectorParameter b )
{
	m_quad = _mm_add_epi32( a.m_quad, b.m_quad );
}

HK_FORCE_INLINE void hkIntVector::setAddU32( hkIntVectorParameter a, hkIntVectorParameter b )
{
	m_quad = _mm_add_epi32( a.m_quad, b.m_quad );
}

#define HK_INT_VECTOR_ADD64_AVAILABLE
HK_FORCE_INLINE void hkIntVector::setAddU64( hkIntVectorParameter a, hkIntVectorParameter b )
{
	m_quad = _mm_add_epi64( a.m_quad, b.m_quad );
}

HK_FORCE_INLINE void hkIntVector::setSubU64( hkIntVectorParameter a, hkIntVectorParameter b )
{
	m_quad = _mm_sub_epi64( a.m_quad, b.m_quad );
}


HK_FORCE_INLINE void hkIntVector::setAddSaturateU32( hkIntVectorParameter a, hkIntVectorParameter b )
{
#if HK_SSE_VERSION >= 0x41
	hkQuadUint max = _mm_set1_epi32(-1);
	hkQuadUint diff = _mm_sub_epi32(max, a.m_quad);
	hkQuadUint smaller = _mm_min_epu32(diff, b.m_quad);
	m_quad = _mm_add_epi32(a.m_quad, smaller);
#else
	// There are no *unsigned* 32-bit compare, min/max, or add/subtract instructions (with or without saturation) in SSE2.
	const hkUint32* HK_RESTRICT qa = HK_M128(a.m_quad).m128i_u32;
	const hkUint32* HK_RESTRICT qb = HK_M128(b.m_quad).m128i_u32;
	hkUint32* HK_RESTRICT qr = HK_M128(m_quad).m128i_u32;
	const hkUint32 max = 0xffffffff;

	qr[0] = (qa[0] < max - qb[0]) ? (qa[0] + qb[0]) : max;
	qr[1] = (qa[1] < max - qb[1]) ? (qa[1] + qb[1]) : max;
	qr[2] = (qa[2] < max - qb[2]) ? (qa[2] + qb[2]) : max;
	qr[3] = (qa[3] < max - qb[3]) ? (qa[3] + qb[3]) : max;
#endif
}

HK_FORCE_INLINE void hkIntVector::setAddSaturateS16( hkIntVectorParameter a, hkIntVectorParameter b )
{
	m_quad = _mm_adds_epi16(a.m_quad, b.m_quad);
}

HK_FORCE_INLINE void hkIntVector::setAddSaturateU16( hkIntVectorParameter a, hkIntVectorParameter b )
{
	m_quad = _mm_adds_epu16(a.m_quad, b.m_quad);
}

HK_FORCE_INLINE void hkIntVector::setSubSaturateU32( hkIntVectorParameter a, hkIntVectorParameter b )
{
#if HK_SSE_VERSION >= 0x41
	hkQuadUint smaller = _mm_min_epu32(a.m_quad, b.m_quad);
	m_quad = _mm_sub_epi32(a.m_quad, smaller);
#else
	// There are no *unsigned* 32-bit compare, min/max, or add/subtract instructions (with or without saturation) in SSE2.
	const hkUint32* HK_RESTRICT qa = HK_M128(a.m_quad).m128i_u32;
	const hkUint32* HK_RESTRICT qb = HK_M128(b.m_quad).m128i_u32;
	hkUint32* HK_RESTRICT qr = HK_M128(m_quad).m128i_u32;

	qr[0] = (qa[0] > qb[0]) ? (qa[0] - qb[0]) : 0;
	qr[1] = (qa[1] > qb[1]) ? (qa[1] - qb[1]) : 0;
	qr[2] = (qa[2] > qb[2]) ? (qa[2] - qb[2]) : 0;
	qr[3] = (qa[3] > qb[3]) ? (qa[3] - qb[3]) : 0;
#endif
}

HK_FORCE_INLINE void hkIntVector::setSubSaturateS16( hkIntVectorParameter a, hkIntVectorParameter b )
{
	m_quad = _mm_subs_epi16(a.m_quad, b.m_quad);
}

HK_FORCE_INLINE void hkIntVector::setSubSaturateU16( hkIntVectorParameter a, hkIntVectorParameter b )
{
	m_quad = _mm_subs_epu16(a.m_quad, b.m_quad);
}

HK_FORCE_INLINE void hkIntVector::setMinU8( hkIntVectorParameter a, hkIntVectorParameter b )
{
	m_quad = _mm_min_epu8 (a.m_quad, b.m_quad);
}

HK_FORCE_INLINE void hkIntVector::setMinS32( hkIntVectorParameter a, hkIntVectorParameter b )
{
#if HK_SSE_VERSION >= 0x41
	m_quad = _mm_min_epi32(a.m_quad, b.m_quad);
#else
	const __m128i cmp = _mm_cmplt_epi32(a.m_quad, b.m_quad);
	m_quad = _mm_or_si128( _mm_and_si128(cmp, a.m_quad), _mm_andnot_si128(cmp, b.m_quad));
#endif
}

HK_FORCE_INLINE void hkIntVector::setMaxS32( hkIntVectorParameter a, hkIntVectorParameter b )
{
#if HK_SSE_VERSION >= 0x41
	m_quad = _mm_max_epi32(a.m_quad, b.m_quad);
#else
	const __m128i cmp = _mm_cmpgt_epi32(a.m_quad, b.m_quad);
	m_quad = _mm_or_si128( _mm_and_si128(cmp, a.m_quad), _mm_andnot_si128(cmp, b.m_quad));
#endif
}

HK_FORCE_INLINE void hkIntVector::setMinS16( hkIntVectorParameter a, hkIntVectorParameter b )
{
#if HK_SSE_VERSION >= 0x41
	m_quad = _mm_min_epi16(a.m_quad, b.m_quad);
#else
	const __m128i cmp = _mm_cmplt_epi16(a.m_quad, b.m_quad);
	m_quad = _mm_or_si128( _mm_and_si128(cmp, a.m_quad), _mm_andnot_si128(cmp, b.m_quad));
#endif
}

HK_FORCE_INLINE void hkIntVector::setMaxS16( hkIntVectorParameter a, hkIntVectorParameter b )
{
#if HK_SSE_VERSION >= 0x41
	m_quad = _mm_max_epi16(a.m_quad, b.m_quad);
#else
	const __m128i cmp = _mm_cmpgt_epi16(a.m_quad, b.m_quad);
	m_quad = _mm_or_si128( _mm_and_si128(cmp, a.m_quad), _mm_andnot_si128(cmp, b.m_quad));
#endif
}

//
// Shift operations
//

template <int shift> 
HK_FORCE_INLINE void hkIntVector::setShiftLeft16( hkIntVectorParameter a)
{
	m_quad =  _mm_slli_epi16( a.m_quad, shift);
}

template <int shift> 
HK_FORCE_INLINE void hkIntVector::setShiftRight16( hkIntVectorParameter a)
{
	m_quad =  _mm_srli_epi16( a.m_quad, shift);
}

template <int shift> 
HK_FORCE_INLINE void hkIntVector::setShiftLeft32( hkIntVectorParameter a)
{
	m_quad =  _mm_slli_epi32( a.m_quad, shift);
}

template <int shift> 
HK_FORCE_INLINE void hkIntVector::setShiftRight32( hkIntVectorParameter a)
{
	m_quad =  _mm_srli_epi32( a.m_quad, shift);	
}

// x, y = high, z, w = low

template <int shift> 
HK_FORCE_INLINE void hkIntVector::setShiftLeft128( hkIntVectorParameter a)
{
	m_quad =  _mm_srli_si128( a.m_quad, shift);
}

template <int shift> 
HK_FORCE_INLINE void hkIntVector::setShiftRight128( hkIntVectorParameter a)
{
	m_quad =  _mm_slli_si128( a.m_quad, shift);
}

template<int shift>
HK_FORCE_INLINE void hkIntVector::setShiftRightS32( hkIntVectorParameter a )
{
	m_quad = _mm_srai_epi32( a.m_quad, shift);
}

template<int shift>
HK_FORCE_INLINE void hkIntVector::setShiftRightS16( hkIntVectorParameter a )
{
	m_quad = _mm_srai_epi16( a.m_quad, shift);
}

HK_FORCE_INLINE void hkIntVector::setShiftLeft16( hkIntVectorParameter a, int shift )
{
	m_quad = _mm_slli_epi16( a.m_quad, shift );
}

HK_FORCE_INLINE void hkIntVector::setShiftLeft32( hkIntVectorParameter a, int shift )
{
	m_quad = _mm_slli_epi32( a.m_quad, shift );
}

HK_FORCE_INLINE void hkIntVector::setShiftRight16( hkIntVectorParameter a, int shift )
{
	m_quad = _mm_srli_epi16( a.m_quad, shift );
}

HK_FORCE_INLINE void hkIntVector::setShiftRight32( hkIntVectorParameter a, int shift )
{
	m_quad = _mm_srli_epi32( a.m_quad, shift );
}

//
// Merge operations
// Stick to the convention that "high" means x,y, "low" means z,w
//
HK_FORCE_INLINE void hkIntVector::setMergeHead32(hkIntVectorParameter a, hkIntVectorParameter b)
{
	m_quad = _mm_unpacklo_epi32(a.m_quad, b.m_quad);
}

HK_FORCE_INLINE void hkIntVector::setMergeTail32(hkIntVectorParameter a, hkIntVectorParameter b)
{
	m_quad = _mm_unpackhi_epi32(a.m_quad, b.m_quad);
}

HK_FORCE_INLINE void hkIntVector::setMergeHead16(hkIntVectorParameter a, hkIntVectorParameter b)
{
	m_quad = _mm_unpacklo_epi16(a.m_quad, b.m_quad);
}

HK_FORCE_INLINE void hkIntVector::setMergeTail16(hkIntVectorParameter a, hkIntVectorParameter b)
{
	m_quad = _mm_unpackhi_epi16(a.m_quad, b.m_quad);
}

HK_FORCE_INLINE void hkIntVector::setMergeHead8(hkIntVectorParameter a, hkIntVectorParameter b)
{
	m_quad = _mm_unpacklo_epi8(a.m_quad, b.m_quad);
}

HK_FORCE_INLINE void hkIntVector::setMergeTail8(hkIntVectorParameter a, hkIntVectorParameter b)
{
	m_quad = _mm_unpackhi_epi8(a.m_quad, b.m_quad);
}

//
// Pack operations
//
HK_FORCE_INLINE void hkIntVector::setConvertU32ToU16( hkIntVectorParameter a, hkIntVectorParameter b )
{
	hkQuadUint a0 = _mm_slli_epi32(a.m_quad, 16);	// moduloU16 by sign extending bit 15
	hkQuadUint b0 = _mm_slli_epi32(b.m_quad, 16);

	a0 = _mm_srai_epi32( a0, 16 );
	b0 = _mm_srai_epi32( b0, 16 );
	m_quad = _mm_packs_epi32(a0, b0);
}

HK_FORCE_INLINE void hkIntVector::setConvertSaturateS32ToU16( hkIntVectorParameter a, hkIntVectorParameter b )
{
	static HK_ALIGN16( const hkUint32 offset[4] )  = { 0x00008000, 0x00008000, 0x00008000, 0x00008000 };
	static HK_ALIGN16( const hkUint32 offset2[4] ) = { 0x80008000, 0x80008000, 0x80008000, 0x80008000 };

	hkQuadUint a0 = _mm_sub_epi32(a.m_quad, *(hkQuadUint*)&offset);		// shift 0 to -max
	hkQuadUint b0 = _mm_sub_epi32(b.m_quad, *(hkQuadUint*)&offset);
	hkQuadUint r  = _mm_packs_epi32(a0, b0);	// signed saturate
	m_quad = _mm_add_epi16( r, *(hkQuadUint*)&offset2 );	// revert shift
}

HK_FORCE_INLINE void hkIntVector::setConvertSaturateS32ToS16( hkIntVectorParameter a, hkIntVectorParameter b )
{
	m_quad  = _mm_packs_epi32(a.m_quad, b.m_quad);	// signed saturate
}

HK_FORCE_INLINE void hkIntVector::setConvertSaturateS16ToU8( hkIntVectorParameter a, hkIntVectorParameter b )
{
	m_quad = _mm_packus_epi16(a.m_quad, b.m_quad);
}

//
//	Sets this.u32[i] = (unsigned int)a.u16[i]

HK_FORCE_INLINE void hkIntVector::setConvertLowerU16ToU32(hkIntVectorParameter a)
{
	m_quad = _mm_unpacklo_epi16(a.m_quad, _mm_setzero_si128());
}

//
//	Sets this.u32[i] = (unsigned int)a.u16[i + 4]

HK_FORCE_INLINE void hkIntVector::setConvertUpperU16ToU32(hkIntVectorParameter a)
{
	m_quad = _mm_unpackhi_epi16(a.m_quad, _mm_setzero_si128());
}

//
// Shuffle
//
template <> 
HK_FORCE_INLINE void hkIntVector::setPermutation<hkVectorPermutation::XYZW>(hkIntVectorParameter v)
{
	m_quad = v.m_quad;
}

template <hkVectorPermutation::Permutation P>
HK_FORCE_INLINE void hkIntVector::setPermutation( hkIntVectorParameter v )
{
	const int shuf = ((P >> (12 - 0)) & 0x03) |
		((P >> ( 8 - 2)) & 0x0c) |
		((P >> ( 4 - 4)) & 0x30) |
		((P << ( 0 + 6)) & 0xc0);

	m_quad = _mm_shuffle_epi32(v.m_quad, shuf); 
}

HK_FORCE_INLINE void hkIntVector::setPermuteU8(hkIntVectorParameter aIn, hkIntVectorParameter mask)
{
#if HK_SSE_VERSION >= 0x31
	HK_ON_DEBUG( const hkUint8* m = HK_M128(mask.m_quad).m128i_u8; for (int i = 0; i < 16; i++) { HK_MATH_ASSERT(0xf820d0c2, (m[i] & 0xF0)==0, "upper 4 bits not zero"); } )
	m_quad = _mm_shuffle_epi8(aIn.m_quad, mask.m_quad);
#else
	const hkUint8* HK_RESTRICT m = HK_M128(mask.m_quad).m128i_u8;
	const hkUint8* HK_RESTRICT a = HK_M128(aIn.m_quad).m128i_u8;
	hkQuadUint q;
	hkUint8* HK_RESTRICT r = HK_M128(q).m128i_u8;
	for (int i = 0; i < 16; i++)
	{
		HK_MATH_ASSERT(0xf820d0c2, (m[i] & 0xF0)==0, "upper 4 bits not zero");
		r[i] = a[m[i]];
	}

	m_quad = q;
#endif
}

HK_FORCE_INLINE void hkIntVector::setPermuteU8(hkIntVectorParameter aIn, hkIntVectorParameter bIn, hkIntVectorParameter mask)
{
#if HK_SSE_VERSION >= 0x31
	hkQuadUint bsel = _mm_set1_epi8(0x0F);
	hkQuadUint nMask = _mm_and_si128(mask.m_quad, bsel); // mask out the 0x80 detect
	hkQuadUint aPerm = _mm_shuffle_epi8(aIn.m_quad, nMask);
	hkQuadUint bPerm = _mm_shuffle_epi8(bIn.m_quad, nMask);
	hkQuadUint selectB = _mm_cmpgt_epi8(mask.m_quad, bsel);
#if HK_SSE_VERSION >= 0x41
	m_quad = _mm_blendv_epi8(aPerm, bPerm, selectB);
#else
	m_quad = _mm_or_si128( _mm_and_si128(selectB, bPerm), _mm_andnot_si128(selectB, aPerm) );
#endif
#else
	const hkUint8* HK_RESTRICT m = HK_M128(mask.m_quad).m128i_u8;
	const hkUint8* HK_RESTRICT a = HK_M128(aIn.m_quad).m128i_u8;
	const hkUint8* HK_RESTRICT b = HK_M128(bIn.m_quad).m128i_u8;
	hkQuadUint q;
	hkUint8* HK_RESTRICT r = HK_M128(q).m128i_u8;
	for (int i = 0; i < 16; i++)
	{
		if (m[i] & 0xF0)
		{
			r[i] = b[m[i] & 0x0F];
		}
		else
		{
			r[i] = a[m[i] & 0x0F];
		}
	}

	m_quad = q;
#endif
}

//
// Splat
//
template <int VALUE> 
HK_FORCE_INLINE void hkIntVector::splatImmediate32()
{
	HK_INT_VECTOR_IMM_SPLAT_VALUE_CHECK;
	m_quad = _mm_set1_epi32(VALUE);
}

template <int VALUE> 
HK_FORCE_INLINE void hkIntVector::splatImmediate16()
{
	HK_INT_VECTOR_IMM_SPLAT_VALUE_CHECK;
	m_quad = _mm_set1_epi16(VALUE);
}

template <int VALUE> 
HK_FORCE_INLINE void hkIntVector::splatImmediate8()
{
	HK_INT_VECTOR_IMM_SPLAT_VALUE_CHECK;
	m_quad = _mm_set1_epi8(VALUE);
}

template <int I> 
HK_FORCE_INLINE void hkIntVector::setBroadcast(hkIntVectorParameter a)
{
	HK_INT_VECTOR_SUBINDEX_CHECK;
	m_quad = _mm_shuffle_epi32( a.m_quad, _MM_SHUFFLE(I,I,I,I) );
}

template<int I>
HK_FORCE_INLINE void hkIntVector::setBroadcast16(hkIntVectorParameter a)
{
	if (I < 4)
	{
		m_quad = _mm_unpacklo_epi16(a.m_quad, a.m_quad);
	}
	else
	{
		m_quad = _mm_unpackhi_epi16(a.m_quad, a.m_quad);
	}
	setBroadcast<I % 4>(*this);
}

template<int I>
HK_FORCE_INLINE void hkIntVector::setBroadcast8(hkIntVectorParameter a)
{
	if (I < 8)
	{
		m_quad = _mm_unpacklo_epi8(a.m_quad, a.m_quad);
	}
	else
	{
		m_quad = _mm_unpackhi_epi8(a.m_quad, a.m_quad);
	}
	setBroadcast16<I % 8>(*this);
}

//
// int <-> float conversion
//

// from Apple's Hardware SSE Performance Programming Guide
// http://developer.apple.com
HK_FORCE_INLINE void hkIntVector::convertU32ToF32(hkVector4f& vOut) const
{
	static HK_ALIGN16( const hkUint32 two16[4] )  = { 0x47800000, 0x47800000, 0x47800000, 0x47800000 }; // 2^16 as float

	// Convert UInt32 to Float32 according to the current rounding mode
	// Avoid double rounding by doing two exact conversions
	// of high and low 16-bit segments

	hkQuadUint hi = _mm_srli_epi32( m_quad, 16 );
	hkQuadUint lo = _mm_srli_epi32( _mm_slli_epi32(  m_quad, 16 ), 16 );
	__m128 fHi = _mm_mul_ps( _mm_cvtepi32_ps( hi ), *(__m128*)&two16);
	__m128 fLo = _mm_cvtepi32_ps( lo );

	// do single rounding according to current rounding mode
	// note that AltiVec always uses round to nearest. We use current
	// rounding mode here, which is round to nearest by default.
	__m128 result = _mm_add_ps( fHi, fLo );

	vOut.m_quad =  result;
}

HK_FORCE_INLINE void hkIntVector::convertU32ToF32(hkVector4d& vOut) const
{
	static HK_ALIGN16( const hkUint32 two16[4] )  = { 0x47800000, 0x47800000, 0x47800000, 0x47800000 }; // 2^16 as float

	// Convert UInt32 to Float32 according to the current rounding mode
	// Avoid double rounding by doing two exact conversions
	// of high and low 16-bit segments

	hkQuadUint hi = _mm_srli_epi32( m_quad, 16 );
	hkQuadUint lo = _mm_srli_epi32( _mm_slli_epi32(  m_quad, 16 ), 16 );
	__m128 fHi = _mm_mul_ps( _mm_cvtepi32_ps( hi ), *(__m128*)&two16);
	__m128 fLo = _mm_cvtepi32_ps( lo );

	// no rounding needed as 32 bit fit into mantissa if calc is done in double precision
#if HK_SSE_VERSION >= 0x50
	__m256d dHi = _mm256_cvtps_pd(fHi);
	__m256d dLo = _mm256_cvtps_pd(fLo);
	vOut.m_quad = _mm256_add_pd( dHi, dLo );
#else
	__m128d dHiXY = _mm_cvtps_pd(fHi);
	__m128d dHiZW = _mm_cvtps_pd(_mm_shuffle_ps(fHi,fHi,_MM_SHUFFLE(1,0,3,2)));
	__m128d dLoXY = _mm_cvtps_pd(fLo);
	__m128d dLoZW = _mm_cvtps_pd(_mm_shuffle_ps(fLo,fLo,_MM_SHUFFLE(1,0,3,2)));
	vOut.m_quad.xy = _mm_add_pd( dHiXY, dLoXY );
	vOut.m_quad.zw = _mm_add_pd( dHiZW, dLoZW );
#endif
}

HK_FORCE_INLINE void hkIntVector::convertS32ToF32(hkVector4f& vOut) const
{
	vOut.m_quad =  _mm_cvtepi32_ps(m_quad);
}

HK_FORCE_INLINE void hkIntVector::convertS32ToF32(hkVector4d& vOut) const
{
#if HK_SSE_VERSION >= 0x50
	vOut.m_quad = _mm256_cvtepi32_pd(m_quad);
#else
	vOut.m_quad.xy = _mm_cvtepi32_pd(m_quad);
	vOut.m_quad.zw = _mm_cvtepi32_pd(_mm_shuffle_epi32(m_quad, _MM_SHUFFLE(1,0,3,2)));
#endif
}

HK_FORCE_INLINE void hkIntVector::setConvertF32toU32(hkVector4fParameter vIn)
{
	static HK_ALIGN16( const hkUint32 two31[4] )  = { 0x4F000000, 0x4F000000, 0x4F000000, 0x4F000000 }; // 2^31 as float
	__m128 two32 = _mm_add_ps( *(__m128*)&two31, *(__m128*)&two31);

	const __m128 v = vIn.m_quad;

	// check for overflow before conversion to int
	__m128 overflow = _mm_cmpge_ps( v, *(__m128*)&two31 );
	__m128 overflow2 = _mm_cmpge_ps( v, two32 );
	__m128 subval = _mm_and_ps( overflow, *(__m128*)&two31 );
	hkQuadUint addval = _mm_slli_epi32(_mm_castps_si128(overflow), 31);

	// bias the value to signed space if it is >= 2^31
	__m128 f = _mm_sub_ps( v, subval );

	// clip at zero
	f = _mm_max_ps( f, _mm_setzero_ps() );

	// convert to int with saturation
	hkQuadUint result = _mm_cvttps_epi32( f ); // force round to zero like AltiVec

	// unbias
	result = _mm_add_epi32( result, addval );

	// patch up the overflow case
	m_quad = _mm_or_si128( result, _mm_castps_si128(overflow2) );
}


HK_FORCE_INLINE void hkIntVector::setConvertF32toU32(hkVector4dParameter vIn)
{
	static HK_ALIGN16( const hkUint32 two31[4] )  = { 0x4F000000, 0x4F000000, 0x4F000000, 0x4F000000 }; // 2^31 as float
	__m128 two32 = _mm_add_ps( *(__m128*)&two31, *(__m128*)&two31);

#if HK_SSE_VERSION >= 0x50
	const __m128 v = _mm256_cvtpd_ps(vIn.m_quad);
#else
	const __m128 xy = _mm_cvtpd_ps(vIn.m_quad.xy);
	const __m128 zw = _mm_cvtpd_ps(vIn.m_quad.zw);
	const __m128 v = _mm_shuffle_ps(xy,zw,_MM_SHUFFLE(1,0,1,0));
#endif


	// check for overflow before conversion to int
	__m128 overflow = _mm_cmpge_ps( v, *(__m128*)&two31 );
	__m128 overflow2 = _mm_cmpge_ps( v, two32 );
	__m128 subval = _mm_and_ps( overflow, *(__m128*)&two31 );
	hkQuadUint addval = _mm_slli_epi32(_mm_castps_si128(overflow), 31);

	// bias the value to signed space if it is >= 2^31
	__m128 f = _mm_sub_ps( v, subval );

	// clip at zero
	f = _mm_max_ps( f, _mm_setzero_ps() );

	// convert to int with saturation
	hkQuadUint result = _mm_cvttps_epi32( f ); // force round to zero like AltiVec

	// unbias
	result = _mm_add_epi32( result, addval );

	// patch up the overflow case
	m_quad = _mm_or_si128( result, _mm_castps_si128(overflow2) );
}

HK_FORCE_INLINE void hkIntVector::setConvertF32toS32(hkVector4fParameter vIn)
{
	static HK_ALIGN16( const hkUint32 two31[4] )  = { 0x4F000000, 0x4F000000, 0x4F000000, 0x4F000000 }; // 2^31 as float

	const __m128 v = vIn.m_quad;

	// Convert float to signed int, with AltiVec style overflow
	// (i.e. large float -> 0x7fffffff instead of 0x80000000)
	__m128 overflow = _mm_cmpge_ps( v, *(__m128*)&two31);
	hkQuadUint result = _mm_cvttps_epi32( v ); // force round to zero like AltiVec
	m_quad = _mm_xor_si128( result, _mm_castps_si128(overflow) );
}

HK_FORCE_INLINE void hkIntVector::setConvertF32toS32(hkVector4dParameter vIn)
{
	// Convert float to signed int, with AltiVec style overflow
	// (i.e. large float -> 0x7fffffff instead of 0x80000000)

#if HK_SSE_VERSION >= 0x50
	static HK_ALIGN32( const hkUint64 two31[4] )  = { 0x41E0000000000000ull, 0x41E0000000000000ull, 0x41E0000000000000ull, 0x41E0000000000000ull }; // 2^31 as double
	__m256d overflow = _mm256_cmp_pd( vIn.m_quad, *(__m256d*)&two31, _CMP_GE_OQ);
	__m128i result = _mm256_cvttpd_epi32( vIn.m_quad ); // force round to zero like AltiVec
	m_quad = _mm_xor_si128( result, _mm_castpd_si256(overflow) ); // TODO condense 256 bit overflow to 128 bit
#else
	static HK_ALIGN16( const hkUint64 two31[2] )  = { 0x41E0000000000000ull, 0x41E0000000000000ull }; // 2^31 as double
	__m128d overflowXY = _mm_cmpge_pd( vIn.m_quad.xy, *(__m128d*)&two31);
	__m128d overflowZW = _mm_cmpge_pd( vIn.m_quad.zw, *(__m128d*)&two31);
	__m128i resultXY = _mm_cvttpd_epi32( vIn.m_quad.xy ); // force round to zero like AltiVec
	__m128i resultZW = _mm_cvttpd_epi32( vIn.m_quad.zw ); // force round to zero like AltiVec
	__m128i narrowOverflowXY = _mm_shuffle_epi32(_mm_castpd_si128(overflowXY), _MM_SHUFFLE(2,0,2,0));
	__m128i narrowOverflowZW = _mm_shuffle_epi32(_mm_castpd_si128(overflowZW), _MM_SHUFFLE(2,0,2,0));
	resultXY = _mm_xor_si128( resultXY, narrowOverflowXY );
	resultZW = _mm_xor_si128( resultZW, narrowOverflowZW );
	m_quad = _mm_castps_si128(_mm_movelh_ps(_mm_castsi128_ps(resultXY),_mm_castsi128_ps(resultZW)));
#endif
}

template <>
HK_FORCE_INLINE void hkIntVector::load<4>(const hkUint32* p)
{
	HK_MATH_ASSERT(0x70aae483, ((hkUlong)p & 0xf) == 0, "pointer for hkIntVector::load<4> must be 16-byte aligned");
	m_quad = _mm_load_si128((const __m128i*)p);
}

template <int N>
HK_FORCE_INLINE void hkIntVector::load(const hkUint32* p)
{
	HK_MATH_ASSERT(0x70aae483, ( ((hkUlong)p) & ((sizeof(hkUint32)*(N!=3?N:4) )-1) ) == 0, "p must be aligned.");
	loadNotAligned<N>(p);
}

//
//	Store to an aligned address

template <>
HK_FORCE_INLINE void hkIntVector::store<4>(hkUint32* p) const
{
	HK_MATH_ASSERT(0x70aae483, ((hkUlong)p & 0xf) == 0, "pointer for hkIntVector::store<4> must be 16-byte aligned");
	_mm_store_si128((__m128i*)p, m_quad);
}

template <int N>
HK_FORCE_INLINE void hkIntVector::store(hkUint32* p) const
{
	HK_MATH_ASSERT(0x70aae483, ( ((hkUlong)p) & ((sizeof(hkUint32)*(N!=3?N:4) )-1) ) == 0, "p must be aligned.");
	storeNotAligned<N>(p);
}

//
//	Assuming that this = (i0, i1, i2, i3) and v = (v0, v1, v2, v3), the function will set this = (ik, ik, ik, ik)
//	 where k ={0,..., 3} such that vk = max{v0, v1, v2, v3}.

HK_FORCE_INLINE void hkIntVector::broadcastComponentAtVectorMax(hkVector4fParameter vIn)
{
	const __m128 v = vIn.m_quad;

	__m128 tmpV0 = _mm_shuffle_ps(v, v, _MM_SHUFFLE(0, 3, 2, 1));	// tmpV0 = (vy, vz, vw, vx)
	hkQuadUint tmpI0 = _mm_shuffle_epi32(m_quad, _MM_SHUFFLE(0, 3, 2, 1));			// tmpI0 = (iy, iz, iw, ix)

	// tmpI1	= [ (vx >= vy) ? ix : iy, *, (vz >= vw) ? iz : iw, * ]
	//			= [ idx(vx, vy), *, idx(vz, vw), * ]
	hkQuadUint cmp		= _mm_castps_si128(_mm_cmpge_ps(tmpV0, v));
#if HK_SSE_VERSION >= 0x41
	hkQuadUint tmpI1	= _mm_blendv_epi8(m_quad, tmpI0, cmp);
#else
	hkQuadUint tmpI1	= _mm_or_si128( _mm_and_si128(cmp, tmpI0), _mm_andnot_si128(cmp, m_quad) );
#endif
	// tmpV1 = [max(vx, vy), *, max(vz, vw), *]
	__m128 tmpV1 = _mm_max_ps(tmpV0, v);

	// tmpV0 = [max(vz, vw), *]
	// tmpI0 = [idx(vz, vw), *]
	tmpV0 = _mm_shuffle_ps(tmpV1, tmpV1, _MM_SHUFFLE(2, 2, 2, 2));
	tmpI0 = _mm_shuffle_epi32(tmpI1, _MM_SHUFFLE(2, 2, 2, 2));

	cmp		= _mm_castps_si128(_mm_cmpge_ps(tmpV0, tmpV1));
#if HK_SSE_VERSION >= 0x41
	tmpI1	= _mm_blendv_epi8(tmpI1, tmpI0, cmp);
#else
	tmpI1	= _mm_or_si128( _mm_and_si128(cmp, tmpI0), _mm_andnot_si128(cmp, tmpI1));
#endif
	m_quad	= _mm_shuffle_epi32(tmpI1, _MM_SHUFFLE(0, 0, 0, 0));
}


HK_FORCE_INLINE void hkIntVector::broadcastComponentAtVectorMax(hkVector4dParameter vIn)
{
#if HK_SSE_VERSION >= 0x50
	const __m128 v = _mm256_cvtpd_ps(vIn.m_quad);
#else
	const __m128 xy = _mm_cvtpd_ps(vIn.m_quad.xy);
	const __m128 zw = _mm_cvtpd_ps(vIn.m_quad.zw);
	const __m128 v = _mm_shuffle_ps(xy,zw,_MM_SHUFFLE(1,0,1,0));
#endif


	__m128 tmpV0 = _mm_shuffle_ps(v, v, _MM_SHUFFLE(0, 3, 2, 1));	// tmpV0 = (vy, vz, vw, vx)
	hkQuadUint tmpI0 = _mm_shuffle_epi32(m_quad, _MM_SHUFFLE(0, 3, 2, 1));			// tmpI0 = (iy, iz, iw, ix)

	// tmpI1	= [ (vx >= vy) ? ix : iy, *, (vz >= vw) ? iz : iw, * ]
	//			= [ idx(vx, vy), *, idx(vz, vw), * ]
	hkQuadUint cmp		= _mm_castps_si128(_mm_cmpge_ps(tmpV0, v));
#if HK_SSE_VERSION >= 0x41
	hkQuadUint tmpI1	= _mm_blendv_epi8(m_quad, tmpI0, cmp);
#else
	hkQuadUint tmpI1	= _mm_or_si128( _mm_and_si128(cmp, tmpI0), _mm_andnot_si128(cmp, m_quad) );
#endif
	// tmpV1 = [max(vx, vy), *, max(vz, vw), *]
	__m128 tmpV1 = _mm_max_ps(tmpV0, v);

	// tmpV0 = [max(vz, vw), *]
	// tmpI0 = [idx(vz, vw), *]
	tmpV0 = _mm_shuffle_ps(tmpV1, tmpV1, _MM_SHUFFLE(2, 2, 2, 2));
	tmpI0 = _mm_shuffle_epi32(tmpI1, _MM_SHUFFLE(2, 2, 2, 2));

	cmp		= _mm_castps_si128(_mm_cmpge_ps(tmpV0, tmpV1));
#if HK_SSE_VERSION >= 0x41
	tmpI1	= _mm_blendv_epi8(tmpI1, tmpI0, cmp);
#else
	tmpI1	= _mm_or_si128( _mm_and_si128(cmp, tmpI0), _mm_andnot_si128(cmp, tmpI1));
#endif
	m_quad	= _mm_shuffle_epi32(tmpI1, _MM_SHUFFLE(0, 0, 0, 0));
}

//
//	Assuming that this = (i0, i1, i2, i3) and v = (v0, v1, v2, v3), the function will return ik
//	where k in {0,..., 3} such that vk = max{v0, v1, v2, v3}.

HK_FORCE_INLINE int hkIntVector::getComponentAtVectorMax(hkVector4fParameter vIn) const
{
	const __m128 v = vIn.m_quad;

	__m128 tmpV0 = _mm_shuffle_ps(v, v, _MM_SHUFFLE(0, 3, 2, 1));	// tmpV0 = (vy, vz, vw, vx)
	hkQuadUint tmpI0 = _mm_shuffle_epi32(m_quad, _MM_SHUFFLE(0, 3, 2, 1));			// tmpI0 = (iy, iz, iw, ix)

	// tmpI1	= [ (vx >= vy) ? ix : iy, *, (vz >= vw) ? iz : iw, * ]
	//			= [ idx(vx, vy), *, idx(vz, vw), * ]
	hkQuadUint cmp		= _mm_castps_si128(_mm_cmpge_ps(tmpV0, v));
#if HK_SSE_VERSION >= 0x41
	hkQuadUint tmpI1	= _mm_blendv_epi8(m_quad, tmpI0, cmp);
#else
	hkQuadUint tmpI1	= _mm_or_si128( _mm_and_si128(cmp, tmpI0), _mm_andnot_si128(cmp, m_quad) );
#endif

	// tmpV1 = [max(vx, vy), *, max(vz, vw), *]
	__m128 tmpV1 = _mm_max_ps(tmpV0, v);

	// tmpV0 = [max(vz, vw), *]
	// tmpI0 = [idx(vz, vw), *]
	tmpV0 = _mm_shuffle_ps(tmpV1, tmpV1, _MM_SHUFFLE(2, 2, 2, 2));
	tmpI0 = _mm_shuffle_epi32(tmpI1, _MM_SHUFFLE(2, 2, 2, 2));

	cmp		= _mm_castps_si128(_mm_cmpge_ps(tmpV0, tmpV1));
#if HK_SSE_VERSION >= 0x41
	tmpI0	= _mm_blendv_epi8(tmpI1, tmpI0, cmp);
#else
	tmpI0	= _mm_or_si128( _mm_and_si128(cmp, tmpI0), _mm_andnot_si128(cmp, tmpI1));
#endif

	// The value we're interested in is at component 0
	return _mm_cvtsi128_si32(tmpI0);
}


HK_FORCE_INLINE int hkIntVector::getComponentAtVectorMax(hkVector4dParameter vIn) const
{
#if HK_SSE_VERSION >= 0x50
	const __m128 v = _mm256_cvtpd_ps(vIn.m_quad);
#else
	const __m128 xy = _mm_cvtpd_ps(vIn.m_quad.xy);
	const __m128 zw = _mm_cvtpd_ps(vIn.m_quad.zw);
	const __m128 v = _mm_shuffle_ps(xy,zw,_MM_SHUFFLE(1,0,1,0));
#endif

	__m128 tmpV0 = _mm_shuffle_ps(v, v, _MM_SHUFFLE(0, 3, 2, 1));	// tmpV0 = (vy, vz, vw, vx)
	hkQuadUint tmpI0 = _mm_shuffle_epi32(m_quad, _MM_SHUFFLE(0, 3, 2, 1));			// tmpI0 = (iy, iz, iw, ix)

	// tmpI1	= [ (vx >= vy) ? ix : iy, *, (vz >= vw) ? iz : iw, * ]
	//			= [ idx(vx, vy), *, idx(vz, vw), * ]
	hkQuadUint cmp		= _mm_castps_si128(_mm_cmpge_ps(tmpV0, v));
#if HK_SSE_VERSION >= 0x41
	hkQuadUint tmpI1	= _mm_blendv_epi8(m_quad, tmpI0, cmp);
#else
	hkQuadUint tmpI1	= _mm_or_si128( _mm_and_si128(cmp, tmpI0), _mm_andnot_si128(cmp, m_quad) );
#endif

	// tmpV1 = [max(vx, vy), *, max(vz, vw), *]
	__m128 tmpV1 = _mm_max_ps(tmpV0, v);

	// tmpV0 = [max(vz, vw), *]
	// tmpI0 = [idx(vz, vw), *]
	tmpV0 = _mm_shuffle_ps(tmpV1, tmpV1, _MM_SHUFFLE(2, 2, 2, 2));
	tmpI0 = _mm_shuffle_epi32(tmpI1, _MM_SHUFFLE(2, 2, 2, 2));

	cmp		= _mm_castps_si128(_mm_cmpge_ps(tmpV0, tmpV1));
#if HK_SSE_VERSION >= 0x41
	tmpI0	= _mm_blendv_epi8(tmpI1, tmpI0, cmp);
#else
	tmpI0	= _mm_or_si128( _mm_and_si128(cmp, tmpI0), _mm_andnot_si128(cmp, tmpI1));
#endif

	// The value we're interested in is at component 0
	return _mm_cvtsi128_si32(tmpI0);
}


HK_FORCE_INLINE void hkIntVector::setSelect(hkVector4fComparisonParameter selectMask, hkIntVectorParameter trueValue, hkIntVectorParameter falseValue)
{
	hkQuadUint mask = _mm_castps_si128(selectMask.m_mask);

#if HK_SSE_VERSION >= 0x41
	m_quad = _mm_blendv_epi8(falseValue.m_quad, trueValue.m_quad, mask);
#else
	m_quad = _mm_or_si128( _mm_and_si128(mask, trueValue.m_quad), _mm_andnot_si128(mask, falseValue.m_quad));
#endif
}

HK_FORCE_INLINE void hkIntVector::setSelect(hkVector4dComparisonParameter selectMask, hkIntVectorParameter trueValue, hkIntVectorParameter falseValue)
{
#if HK_SSE_VERSION >= 0x50
	__m128i xxyy = _mm256_extractf128_si256(_mm256_castpd_si256(selectMask.m_mask), 0);
	__m128i zzww = _mm256_extractf128_si256(_mm256_castpd_si256(selectMask.m_mask), 1);
	__m128i xzxz = _mm_unpacklo_epi32(xxyy,zzww);
	__m128i ywyw = _mm_unpackhi_epi32(xxyy,zzww);
	hkQuadUint mask = _mm_unpacklo_epi32(xzxz,ywyw);
#else
	__m128i xzxz = _mm_unpacklo_epi32(_mm_castpd_si128(selectMask.m_mask.xy),_mm_castpd_si128(selectMask.m_mask.zw));
	__m128i ywyw = _mm_unpackhi_epi32(_mm_castpd_si128(selectMask.m_mask.xy),_mm_castpd_si128(selectMask.m_mask.zw));
	hkQuadUint mask = _mm_unpacklo_epi32(xzxz,ywyw);
#endif

#if HK_SSE_VERSION >= 0x41
	m_quad = _mm_blendv_epi8(falseValue.m_quad, trueValue.m_quad, mask);
#else
	m_quad = _mm_or_si128( _mm_and_si128(mask, trueValue.m_quad), _mm_andnot_si128(mask, falseValue.m_quad));
#endif
}

template<> 
HK_FORCE_INLINE void hkIntVector::setSelect<hkVector4ComparisonMask::MASK_NONE>( hkIntVectorParameter trueValue, hkIntVectorParameter falseValue )
{
	m_quad = falseValue.m_quad;
}

template<> 
HK_FORCE_INLINE void hkIntVector::setSelect<hkVector4ComparisonMask::MASK_XYZW>( hkIntVectorParameter trueValue, hkIntVectorParameter falseValue )
{
	m_quad = trueValue.m_quad;
}

template<> 
HK_FORCE_INLINE void hkIntVector::setSelect<hkVector4ComparisonMask::MASK_X>( hkIntVectorParameter trueValue, hkIntVectorParameter falseValue )
{
	m_quad = _mm_castps_si128(_mm_move_ss(_mm_castsi128_ps(falseValue.m_quad), _mm_castsi128_ps(trueValue.m_quad)));
}


#if HK_SSE_VERSION >= 0x41
template<hkVector4ComparisonMask::Mask M> 
HK_FORCE_INLINE void hkIntVector::setSelect( hkIntVectorParameter trueValue, hkIntVectorParameter falseValue )
{
	//HK_VECTORCOMPARISON_MASK_CHECK;
	m_quad = _mm_castps_si128(_mm_blend_ps(_mm_castsi128_ps(falseValue.m_quad), _mm_castsi128_ps(trueValue.m_quad), M));
}
#else
template<> 
HK_FORCE_INLINE void hkIntVector::setSelect<hkVector4ComparisonMask::MASK_XY>( hkIntVectorParameter trueValue, hkIntVectorParameter falseValue )
{
	m_quad = _mm_castps_si128(_mm_shuffle_ps(_mm_castsi128_ps(trueValue.m_quad), _mm_castsi128_ps(falseValue.m_quad), _MM_SHUFFLE(3,2,1,0)));
}


template<> 
HK_FORCE_INLINE void hkIntVector::setSelect<hkVector4ComparisonMask::MASK_XYZ>( hkIntVectorParameter trueValue, hkIntVectorParameter falseValue )
{
	m_quad = _mm_castps_si128(_mm_shuffle_ps( _mm_castsi128_ps(trueValue.m_quad), _mm_unpackhi_ps(_mm_castsi128_ps(trueValue.m_quad), _mm_castsi128_ps(falseValue.m_quad)), _MM_SHUFFLE(3,0,1,0)));
}

template<hkVector4ComparisonMask::Mask M> 
HK_FORCE_INLINE void hkIntVector::setSelect( hkIntVectorParameter trueValue, hkIntVectorParameter falseValue )
{
	hkVector4fComparison comp; comp.set<M>();
	setSelect(comp, trueValue, falseValue);
}
#endif

template <hkIntVectorConstant vectorConstant>
HK_FORCE_INLINE /*static*/ const hkIntVector& HK_CALL hkIntVector::getConstant()
{
	return *(const hkIntVector*) (g_intVectorConstants + vectorConstant);
}

HK_FORCE_INLINE /*static*/ const hkIntVector& HK_CALL hkIntVector::getConstant(hkIntVectorConstant constant)
{
	return *(const hkIntVector*) (g_intVectorConstants + constant);
}

/// result.u32[i] = highshorts.u16[i]<<16 + lowShorts.u16[i]. highShorts.u16/lowShorts.u16[4..7] are ignored
HK_FORCE_INLINE void hkIntVector::setCombineHead16To32( hkIntVectorParameter highShorts, hkIntVectorParameter lowShorts )
{
	setMergeHead16(lowShorts, highShorts);
}

/// result.u32[i] = highshorts.u16[4+i]<<16 + lowShorts.u16[4+i]. highShorts.u16/lowShorts.u16[0..3] are ignored
HK_FORCE_INLINE void hkIntVector::setCombineTail16To32( hkIntVectorParameter highShorts, hkIntVectorParameter lowShorts )
{
	setMergeTail16(lowShorts, highShorts);
}

/// result.u16[i] = highshorts.u8[i]<<16 + lowShorts.u8[i]. highShorts.u8/lowShorts.u8[8..15] are ignored
HK_FORCE_INLINE void hkIntVector::setCombineHead8To16( hkIntVectorParameter highShorts, hkIntVectorParameter lowShorts )
{
	setMergeHead8(lowShorts, highShorts);
}

/// result.u16[i] = highshorts.u8[8+i]<<16 + lowShorts.u8[8+i]. highShorts.u8/lowShorts.u8[0..7] are ignored
HK_FORCE_INLINE void hkIntVector::setCombineTail8To16( hkIntVectorParameter highShorts, hkIntVectorParameter lowShorts )
{
	setMergeTail8(lowShorts, highShorts);
}

HK_FORCE_INLINE void hkIntVector::setSplit8To32( hkIntVectorParameter bytes )
{
	hkIntVector zero;zero.setZero();
	hkIntVector i16; i16.setCombineHead8To16( zero, bytes );
	setCombineHead16To32(zero, i16);
}
//
//	Sets this = -v

template <> HK_FORCE_INLINE void hkIntVector::setNegS32<4>(hkIntVectorParameter v)
{
	m_quad = _mm_sub_epi32(_mm_setzero_si128(), v.m_quad);
}

template <>
HK_FORCE_INLINE int hkIntVector::horizontalMinS32<1>() const
{
	return getComponent<0>();
}

template <>
HK_FORCE_INLINE int hkIntVector::horizontalMinS32<2>() const
{
	const __m128i x		= _mm_shuffle_epi32(m_quad,_MM_SHUFFLE(0,0,0,0));
	const __m128i y		= _mm_shuffle_epi32(m_quad,_MM_SHUFFLE(1,1,1,1));
	const __m128i mask	= _mm_cmplt_epi32(x, y);
	const __m128i xy	= _mm_or_si128(_mm_and_si128(mask, x), _mm_andnot_si128(mask, y));

	return _mm_cvtsi128_si32(xy);
}

template <>
HK_FORCE_INLINE int hkIntVector::horizontalMinS32<3>() const
{
	const __m128i x		= _mm_shuffle_epi32(m_quad,_MM_SHUFFLE(0,0,0,0));
	const __m128i y		= _mm_shuffle_epi32(m_quad,_MM_SHUFFLE(1,1,1,1));
	const __m128i z		= _mm_shuffle_epi32(m_quad,_MM_SHUFFLE(2,2,2,2));
	const __m128i mxy	= _mm_cmplt_epi32(x, y);
	const __m128i xy	= _mm_or_si128(_mm_and_si128(mxy, x), _mm_andnot_si128(mxy, y));
	const __m128i mxyz	= _mm_cmplt_epi32(xy, z);
	const __m128i xyz	= _mm_or_si128(_mm_and_si128(mxyz, xy), _mm_andnot_si128(mxyz, z));

	return _mm_cvtsi128_si32(xyz);
}

template <>
HK_FORCE_INLINE int hkIntVector::horizontalMinS32<4>() const
{
	const __m128i yxwz	= _mm_shuffle_epi32(m_quad, _MM_SHUFFLE(1,0,3,2));	// [y, x, w, z]
	const __m128i m0	= _mm_cmplt_epi32(yxwz, m_quad);
	const __m128i sum0	= _mm_or_si128(_mm_and_si128(m0, yxwz), _mm_andnot_si128(m0, m_quad));
	const __m128i sum1	= _mm_shuffle_epi32(sum0, _MM_SHUFFLE(2,3,0,1)); // = zw zw xy xy
	const __m128i m1	= _mm_cmplt_epi32(sum0, sum1);
	const __m128i sum2	= _mm_or_si128(_mm_and_si128(m1, sum0), _mm_andnot_si128(m1, sum1));

	return _mm_cvtsi128_si32(sum2); // xywz all 4
}

template <int N>
HK_FORCE_INLINE int hkIntVector::horizontalMinS32() const
{
	HK_INT_VECTOR_NOT_IMPLEMENTED;
	return 0;
}

template <>
HK_FORCE_INLINE int hkIntVector::horizontalMaxS32<1>() const
{
	return getComponent<0>();
}

template <>
HK_FORCE_INLINE int hkIntVector::horizontalMaxS32<2>() const
{
	const __m128i x		= _mm_shuffle_epi32(m_quad,_MM_SHUFFLE(0,0,0,0));
	const __m128i y		= _mm_shuffle_epi32(m_quad,_MM_SHUFFLE(1,1,1,1));
	const __m128i mask	= _mm_cmpgt_epi32(x, y);
	const __m128i xy	= _mm_or_si128(_mm_and_si128(mask, x), _mm_andnot_si128(mask, y));

	return _mm_cvtsi128_si32(xy);
}

template <>
HK_FORCE_INLINE int hkIntVector::horizontalMaxS32<3>() const
{
	const __m128i x		= _mm_shuffle_epi32(m_quad,_MM_SHUFFLE(0,0,0,0));
	const __m128i y		= _mm_shuffle_epi32(m_quad,_MM_SHUFFLE(1,1,1,1));
	const __m128i z		= _mm_shuffle_epi32(m_quad,_MM_SHUFFLE(2,2,2,2));
	const __m128i mxy	= _mm_cmpgt_epi32(x, y);
	const __m128i xy	= _mm_or_si128(_mm_and_si128(mxy, x), _mm_andnot_si128(mxy, y));
	const __m128i mxyz	= _mm_cmpgt_epi32(xy, z);
	const __m128i xyz	= _mm_or_si128(_mm_and_si128(mxyz, xy), _mm_andnot_si128(mxyz, z));

	return _mm_cvtsi128_si32(xyz);
}

template <>
HK_FORCE_INLINE int hkIntVector::horizontalMaxS32<4>() const
{
	const __m128i yxwz	= _mm_shuffle_epi32(m_quad, _MM_SHUFFLE(1,0,3,2));	// [y, x, w, z]
	const __m128i m0	= _mm_cmpgt_epi32(yxwz, m_quad);
	const __m128i sum0	= _mm_or_si128(_mm_and_si128(m0, yxwz), _mm_andnot_si128(m0, m_quad));
	const __m128i sum1	= _mm_shuffle_epi32(sum0, _MM_SHUFFLE(2,3,0,1)); // = zw zw xy xy
	const __m128i m1	= _mm_cmpgt_epi32(sum0, sum1);
	const __m128i sum2	= _mm_or_si128(_mm_and_si128(m1, sum0), _mm_andnot_si128(m1, sum1));

	return _mm_cvtsi128_si32(sum2); // xywz all 4
}

//
//	Returns the sum of the first N components

template <> HK_FORCE_INLINE int hkIntVector::horizontalAddS32<1>() const
{
	return getComponent<0>();
}

template <> HK_FORCE_INLINE int hkIntVector::horizontalAddS32<2>() const
{
	const __m128i x = _mm_shuffle_epi32(m_quad,_MM_SHUFFLE(0,0,0,0));
	const __m128i y = _mm_shuffle_epi32(m_quad,_MM_SHUFFLE(1,1,1,1));
	return _mm_cvtsi128_si32(_mm_add_epi32(x, y));
}

template <> HK_FORCE_INLINE int hkIntVector::horizontalAddS32<3>() const
{
	return _mm_cvtsi128_si32(	_mm_add_epi32(	_mm_add_epi32(	_mm_shuffle_epi32(m_quad,_MM_SHUFFLE(0,0,0,0)),
																_mm_shuffle_epi32(m_quad,_MM_SHUFFLE(1,1,1,1))),
												_mm_shuffle_epi32(m_quad,_MM_SHUFFLE(2,2,2,2))));
}

template <> HK_FORCE_INLINE int hkIntVector::horizontalAddS32<4>() const
{
	const __m128i yxwz	= _mm_shuffle_epi32(m_quad, _MM_SHUFFLE(1,0,3,2));	// [y, x, w, z]
	const __m128i sum0	= _mm_add_epi32(yxwz, m_quad);						// [x+y, x+y, z+w, z+w]
	const __m128i sum1	= _mm_shuffle_epi32(sum0, _MM_SHUFFLE(2,3,0,1));	// [z+w, z+w, x+y, x+y]
	return _mm_cvtsi128_si32(_mm_add_epi32(sum0, sum1));					// xywz all 4
}

//
//	Returns the xor of the first N components

template <> HK_FORCE_INLINE int hkIntVector::horizontalXorS32<1>() const
{
	return getComponent<0>();
}

template <> HK_FORCE_INLINE int hkIntVector::horizontalXorS32<2>() const
{
	const __m128i x = _mm_shuffle_epi32(m_quad,_MM_SHUFFLE(0,0,0,0));
	const __m128i y = _mm_shuffle_epi32(m_quad,_MM_SHUFFLE(1,1,1,1));
	return _mm_cvtsi128_si32(_mm_xor_si128(x, y));
}

template <> HK_FORCE_INLINE int hkIntVector::horizontalXorS32<3>() const
{
	return _mm_cvtsi128_si32(	_mm_xor_si128(	_mm_xor_si128(	_mm_shuffle_epi32(m_quad,_MM_SHUFFLE(0,0,0,0)),
		_mm_shuffle_epi32(m_quad,_MM_SHUFFLE(1,1,1,1))),
		_mm_shuffle_epi32(m_quad,_MM_SHUFFLE(2,2,2,2))));
}

template <> HK_FORCE_INLINE int hkIntVector::horizontalXorS32<4>() const
{
	const __m128i yxwz	= _mm_shuffle_epi32(m_quad, _MM_SHUFFLE(1,0,3,2));	// [y, x, w, z]
	const __m128i sum0	= _mm_xor_si128(yxwz, m_quad);						// [x+y, x+y, z+w, z+w]
	const __m128i sum1	= _mm_shuffle_epi32(sum0, _MM_SHUFFLE(2,3,0,1));	// [z+w, z+w, x+y, x+y]
	return _mm_cvtsi128_si32(_mm_xor_si128(sum0, sum1));					// xywz all 4
}

template <int N>
HK_FORCE_INLINE int hkIntVector::horizontalMaxS32() const
{
	HK_INT_VECTOR_NOT_IMPLEMENTED;
	return 0;
}

//
//	Returns the dot product of the first N components

template <>
HK_FORCE_INLINE hkInt64 hkIntVector::dot<1>(hkIntVectorParameter v) const
{
#if ( HK_SSE_VERSION >= 0x41 )
	return _mm_extract_epi64(_mm_mul_epi32(m_quad, v.m_quad), 0);
#else
	return	(hkInt64)v.getComponent<0>() * (hkInt64)getComponent<0>();
#endif
}

template <>
HK_FORCE_INLINE hkInt64 hkIntVector::dot<2>(hkIntVectorParameter v) const
{
#if ( HK_SSE_VERSION >= 0x41 )
	const __m128i d_2_0		= _mm_mul_epi32(m_quad, v.m_quad);											// [a2b2, a0b0]
	const __m128i d_3_1		= _mm_mul_epi32(_mm_srli_si128(m_quad, 4), _mm_srli_si128(v.m_quad, 4));	// [a3b3, a1b1]
	return _mm_extract_epi64(_mm_add_epi64(d_2_0, d_3_1), 0);
#else
	return	(hkInt64)v.getComponent<0>() * (hkInt64)getComponent<0>() + 
			(hkInt64)v.getComponent<1>() * (hkInt64)getComponent<1>();
#endif
}

template <>
HK_FORCE_INLINE hkInt64 hkIntVector::dot<3>(hkIntVectorParameter v) const
{
#if ( HK_SSE_VERSION >= 0x41 )
	const __m128i d_2_0		= _mm_mul_epi32(m_quad, v.m_quad);											// [a2b2, a0b0]
	const __m128i d_3_1		= _mm_mul_epi32(_mm_srli_si128(m_quad, 4), _mm_srli_si128(v.m_quad, 4));	// [a3b3, a1b1]
	const __m128i d_23_01	= _mm_add_epi64(d_2_0, d_3_1);												// [a2b2 + a3b3, a0b0 + a1b1]
	const __m128i d_0_2		= _mm_shuffle_epi32(d_2_0, _MM_SHUFFLE(1, 0, 3, 2));						// [a0b0, a2b2]
	return _mm_extract_epi64(_mm_add_epi64(d_0_2, d_23_01), 0);
#else
	return	(hkInt64)v.getComponent<0>() * (hkInt64)getComponent<0>() + 
			(hkInt64)v.getComponent<1>() * (hkInt64)getComponent<1>() + 
			(hkInt64)v.getComponent<2>() * (hkInt64)getComponent<2>();
#endif
}

template <>
HK_FORCE_INLINE hkInt64 hkIntVector::dot<4>(hkIntVectorParameter v) const
{
#if ( HK_SSE_VERSION >= 0x41 )
	const __m128i d_2_0		= _mm_mul_epi32(m_quad, v.m_quad);											// [a2b2, a0b0]
	const __m128i d_3_1		= _mm_mul_epi32(_mm_srli_si128(m_quad, 4), _mm_srli_si128(v.m_quad, 4));	// [a3b3, a1b1]
	const __m128i d_23_01	= _mm_add_epi64(d_2_0, d_3_1);												// [a2b2 + a3b3, a0b0 + a1b1]
	const __m128i d_01_23	= _mm_shuffle_epi32(d_23_01, _MM_SHUFFLE(1, 0, 3, 2));						// [a0b0 + a1b1, a2b2 + a3b3]
	return _mm_extract_epi64(_mm_add_epi64(d_01_23, d_23_01), 0);
#else
	return	(hkInt64)v.getComponent<0>() * (hkInt64)getComponent<0>() + 
			(hkInt64)v.getComponent<1>() * (hkInt64)getComponent<1>() + 
			(hkInt64)v.getComponent<2>() * (hkInt64)getComponent<2>() +
			(hkInt64)v.getComponent<3>() * (hkInt64)getComponent<3>();
#endif
}

//
//	Sets this = va * vb

HK_FORCE_INLINE void hkIntVector::setMul(hkIntVectorParameter vA, hkIntVectorParameter vB)
{
#if ( HK_SSE_VERSION >= 0x41 )
	m_quad = _mm_mullo_epi32(vA.m_quad, vB.m_quad);
#else
	const __m128i tmp1 = _mm_mul_epu32(vA.m_quad, vB.m_quad);
	const __m128i tmp2 = _mm_mul_epu32( _mm_srli_si128(vA.m_quad, 4), _mm_srli_si128(vB.m_quad, 4));
	m_quad = _mm_unpacklo_epi32(_mm_shuffle_epi32(tmp1, _MM_SHUFFLE (0, 0, 2, 0)), _mm_shuffle_epi32(tmp2, _MM_SHUFFLE (0, 0, 2, 0)));
#endif
}

//
//	Sets this = abs(v)

#if ( HK_SSE_VERSION >= 0x30 )
#	define HK_INT_VECTOR_setAbs

HK_FORCE_INLINE void hkIntVector::setAbsS32(hkIntVectorParameter v)
{
	m_quad = _mm_abs_epi32(v.m_quad);
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
