/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */


HK_FORCE_INLINE /*static*/ const hkSimdDouble64 HK_CALL hkSimdDouble64::convert(const hkSingleDouble64& x)
{
	hkSimdDouble64 sr;
	sr.m_real = x;
	return sr;
	//HK_ASSERT(0x7c3a4d98, *(hkUint64*)&(x.m128d_f64[0]) == *(hkUint64*)&(x.m128d_f64[1]) );
}

template<int vectorConstant>
HK_FORCE_INLINE /*static*/ const hkSimdDouble64 HK_CALL hkSimdDouble64::getConstant()
{
	HK_COMPILE_TIME_ASSERT2( 
		(vectorConstant!=HK_QUADREAL_1000) && (vectorConstant!=HK_QUADREAL_0100) && (vectorConstant!=HK_QUADREAL_0010) && (vectorConstant!=HK_QUADREAL_0001) &&
		(vectorConstant!=HK_QUADREAL_m11m11) && (vectorConstant!=HK_QUADREAL_1248) && (vectorConstant!=HK_QUADREAL_8421) && (vectorConstant!=HK_QUADREAL_1010)  && (vectorConstant!=HK_QUADREAL_1100)
		, HK_SIMDDOUBLE_ILLEGAL_CONSTANT_REQUEST);
#if HK_SSE_VERSION >= 0x50
	return convert(*(const hkSingleDouble64*)(g_vectordConstants + vectorConstant));
#else
	return convert((*(g_vectordConstants + vectorConstant)).xy);
#endif
}

HK_FORCE_INLINE /*static*/ const hkSimdDouble64 HK_CALL hkSimdDouble64::getConstant(hkVectorConstant constant)
{
	HK_MATH_ASSERT( 0x909ff234,
		(constant!=HK_QUADREAL_1000) && (constant!=HK_QUADREAL_0100) && (constant!=HK_QUADREAL_0010) && (constant!=HK_QUADREAL_0001) &&
		(constant!=HK_QUADREAL_m11m11) && (constant!=HK_QUADREAL_1248) && (constant!=HK_QUADREAL_8421) && (constant!=HK_QUADREAL_1010)  && (constant!=HK_QUADREAL_1100)
		, "not a simdreal constant");
#if HK_SSE_VERSION >= 0x50
	return convert(*(const hkSingleDouble64*)(g_vectordConstants + constant));
#else
	return convert((*(g_vectordConstants + constant)).xy);
#endif
}

#ifndef HK_DISABLE_IMPLICIT_SIMDREAL_FLOAT_CONVERSION
HK_FORCE_INLINE hkSimdDouble64::hkSimdDouble64(const hkDouble64& x)
{
#if HK_SSE_VERSION >= 0x30
	m_real = _mm_loaddup_pd(&x);
#else
	m_real = _mm_load1_pd(&x);
#endif
}

HK_FORCE_INLINE hkSimdDouble64::operator hkDouble64() const
{
	hkDouble64 s;
	_mm_store_sd(&s, m_real);
	return s;
}
#endif

HK_FORCE_INLINE hkDouble64 hkSimdDouble64::getReal() const
{
	hkDouble64 s;
	_mm_store_sd(&s, m_real);
	return s;
}

HK_FORCE_INLINE void hkSimdDouble64::setFromFloat(const hkFloat32& x)
{
	__m128 f = _mm_load_ss(&x);
	__m128d d = _mm_cvtps_pd(f);
	m_real = _mm_shuffle_pd(d,d,_MM_SHUFFLE2(0,0));
}

HK_FORCE_INLINE void hkSimdDouble64::setFromFloat(const hkDouble64& x)
{
#if HK_SSE_VERSION >= 0x30
	m_real = _mm_loaddup_pd(&x);
#else
	m_real = _mm_load1_pd(&x);
#endif
}

HK_FORCE_INLINE void hkSimdDouble64::setFromHalf(const hkHalf& h)
{
#if defined(HK_HALF_IS_FLOAT)
	__m128 f = _mm_load1_ps((const float*)&h);
#else
	float x; h.store(&x); // do conversion in SSE
	__m128 f = _mm_load1_ps(&x);
#endif
	m_real = _mm_cvtps_pd(f);
}

HK_FORCE_INLINE void hkSimdDouble64::setFromInt32(const hkInt32&  x)
{
	__m128d ix = _mm_cvtsi32_sd(_mm_setzero_pd(),x);
	m_real = _mm_shuffle_pd(ix,ix,_MM_SHUFFLE2(0,0));
}


HK_FORCE_INLINE void hkSimdDouble64::setFromUint16(const hkUint16& x)
{
	int i = x;
	setFromInt32(i);
}

HK_FORCE_INLINE void hkSimdDouble64::setFromUint8(const hkUint8& x)
{
	int i = x;
	setFromInt32(i);
}

HK_FORCE_INLINE void hkSimdDouble64::setZero()
{
	m_real = _mm_setzero_pd();
}


HK_FORCE_INLINE void hkSimdDouble64::storeSaturateInt32(hkInt32* HK_RESTRICT result) const
{
	*result = _mm_cvtsi128_si32(_mm_cvttpd_epi32(m_real));
}


HK_FORCE_INLINE void hkSimdDouble64::storeSaturateUint16(hkUint16* HK_RESTRICT result) const
{
	hkSingleDouble64 clamped   = _mm_max_pd(m_real,_mm_setzero_pd());	
	clamped = _mm_min_pd(clamped,_mm_set1_pd(65535.0));
	*result = hkUint16(_mm_cvtsi128_si32(_mm_cvttpd_epi32(clamped)));
}

HK_FORCE_INLINE const hkSimdDouble64 hkSimdDouble64::operator+ (hkSimdDouble64Parameter r) const
{
	return hkSimdDouble64::convert(_mm_add_pd(m_real,r.m_real));
}

HK_FORCE_INLINE const hkSimdDouble64 hkSimdDouble64::operator- (hkSimdDouble64Parameter r) const
{
	return hkSimdDouble64::convert(_mm_sub_pd(m_real,r.m_real));
}

HK_FORCE_INLINE const hkSimdDouble64 hkSimdDouble64::operator* (hkSimdDouble64Parameter r) const
{
	return hkSimdDouble64::convert(_mm_mul_pd(m_real,r.m_real));
}

#ifdef HK_DISABLE_OLD_VECTOR4_INTERFACE

HK_FORCE_INLINE bool hkSimdDouble64::operator< (hkSimdDouble64Parameter r) const
{
	return _mm_ucomilt_sd(m_real, r.m_real);
}

HK_FORCE_INLINE bool hkSimdDouble64::operator<= (hkSimdDouble64Parameter r) const
{
	return _mm_ucomile_sd(m_real, r.m_real);
}

HK_FORCE_INLINE bool hkSimdDouble64::operator> (hkSimdDouble64Parameter r) const
{
	return _mm_ucomigt_sd(m_real, r.m_real);
}

HK_FORCE_INLINE bool hkSimdDouble64::operator>= (hkSimdDouble64Parameter r) const
{
	return _mm_ucomige_sd(m_real, r.m_real);
}

HK_FORCE_INLINE bool hkSimdDouble64::operator== (hkSimdDouble64Parameter r) const
{
	return _mm_ucomieq_sd(m_real, r.m_real);
}

HK_FORCE_INLINE bool hkSimdDouble64::operator!= (hkSimdDouble64Parameter r) const
{
	return _mm_ucomineq_sd(m_real, r.m_real);
}

#endif

HK_FORCE_INLINE const hkSimdDouble64 hkSimdDouble64::operator-() const
{
	return hkSimdDouble64::convert(_mm_sub_pd(_mm_setzero_pd(),m_real));
}

HK_FORCE_INLINE const hkVector4dComparison hkSimdDouble64::less(hkSimdDouble64Parameter a) const
{
	hkVector4dComparison mask;
	const hkSingleDouble64 m = _mm_cmplt_pd(m_real, a.m_real);
#if HK_SSE_VERSION >= 0x50
	mask.m_mask = _mm256_broadcast_pd(&m);
#else
	mask.m_mask.xy = m;
	mask.m_mask.zw = m;
#endif
	return mask;
}

HK_FORCE_INLINE const hkVector4dComparison hkSimdDouble64::greater(hkSimdDouble64Parameter a) const
{
	hkVector4dComparison mask;
	const hkSingleDouble64 m = _mm_cmpgt_pd(m_real, a.m_real);
#if HK_SSE_VERSION >= 0x50
	mask.m_mask = _mm256_broadcast_pd(&m);
#else
	mask.m_mask.xy = m;
	mask.m_mask.zw = m;
#endif
	return mask;
}

HK_FORCE_INLINE const hkVector4dComparison hkSimdDouble64::greaterEqual(hkSimdDouble64Parameter a) const
{
	hkVector4dComparison mask;
	const hkSingleDouble64 m = _mm_cmpge_pd(m_real, a.m_real);
#if HK_SSE_VERSION >= 0x50
	mask.m_mask = _mm256_broadcast_pd(&m);
#else
	mask.m_mask.xy = m;
	mask.m_mask.zw = m;
#endif
	return mask;
}

HK_FORCE_INLINE const hkVector4dComparison hkSimdDouble64::lessEqual(hkSimdDouble64Parameter a) const
{
	hkVector4dComparison mask;
	const hkSingleDouble64 m = _mm_cmple_pd(m_real, a.m_real);
#if HK_SSE_VERSION >= 0x50
	mask.m_mask = _mm256_broadcast_pd(&m);
#else
	mask.m_mask.xy = m;
	mask.m_mask.zw = m;
#endif
	return mask;
}

HK_FORCE_INLINE const hkVector4dComparison hkSimdDouble64::equal(hkSimdDouble64Parameter a) const
{
	hkVector4dComparison mask;
	const hkSingleDouble64 m = _mm_cmpeq_pd(m_real, a.m_real);
#if HK_SSE_VERSION >= 0x50
	mask.m_mask = _mm256_broadcast_pd(&m);
#else
	mask.m_mask.xy = m;
	mask.m_mask.zw = m;
#endif
	return mask;
}

HK_FORCE_INLINE const hkVector4dComparison hkSimdDouble64::notEqual(hkSimdDouble64Parameter a) const
{
	hkVector4dComparison mask;
	const hkSingleDouble64 m = _mm_cmpneq_pd(m_real, a.m_real);
#if HK_SSE_VERSION >= 0x50
	mask.m_mask = _mm256_broadcast_pd(&m);
#else
	mask.m_mask.xy = m;
	mask.m_mask.zw = m;
#endif
	return mask;
}

HK_FORCE_INLINE const hkVector4dComparison hkSimdDouble64::lessZero() const
{
	hkVector4dComparison mask;
	const hkSingleDouble64 m = _mm_cmplt_pd(m_real, _mm_setzero_pd());
#if HK_SSE_VERSION >= 0x50
	mask.m_mask = _mm256_broadcast_pd(&m);
#else
	mask.m_mask.xy = m;
	mask.m_mask.zw = m;
#endif
	return mask;
}

HK_FORCE_INLINE const hkVector4dComparison hkSimdDouble64::lessEqualZero() const
{
	hkVector4dComparison mask;
	const hkSingleDouble64 m = _mm_cmple_pd(m_real, _mm_setzero_pd());
#if HK_SSE_VERSION >= 0x50
	mask.m_mask = _mm256_broadcast_pd(&m);
#else
	mask.m_mask.xy = m;
	mask.m_mask.zw = m;
#endif
	return mask;
}

HK_FORCE_INLINE const hkVector4dComparison hkSimdDouble64::greaterZero() const
{
	hkVector4dComparison mask;
	const hkSingleDouble64 m = _mm_cmpgt_pd(m_real, _mm_setzero_pd());
#if HK_SSE_VERSION >= 0x50
	mask.m_mask = _mm256_broadcast_pd(&m);
#else
	mask.m_mask.xy = m;
	mask.m_mask.zw = m;
#endif
	return mask;
}

HK_FORCE_INLINE const hkVector4dComparison hkSimdDouble64::greaterEqualZero() const
{
	hkVector4dComparison mask;
	const hkSingleDouble64 m = _mm_cmpge_pd(m_real, _mm_setzero_pd());
#if HK_SSE_VERSION >= 0x50
	mask.m_mask = _mm256_broadcast_pd(&m);
#else
	mask.m_mask.xy = m;
	mask.m_mask.zw = m;
#endif
	return mask;
}

HK_FORCE_INLINE const hkVector4dComparison hkSimdDouble64::equalZero() const
{
	hkVector4dComparison mask;
	const hkSingleDouble64 m = _mm_cmpeq_pd(m_real, _mm_setzero_pd());
#if HK_SSE_VERSION >= 0x50
	mask.m_mask = _mm256_broadcast_pd(&m);
#else
	mask.m_mask.xy = m;
	mask.m_mask.zw = m;
#endif
	return mask;
}

HK_FORCE_INLINE const hkVector4dComparison hkSimdDouble64::notEqualZero() const
{
	hkVector4dComparison mask;
	const hkSingleDouble64 m = _mm_cmpneq_pd(m_real, _mm_setzero_pd());
#if HK_SSE_VERSION >= 0x50
	mask.m_mask = _mm256_broadcast_pd(&m);
#else
	mask.m_mask.xy = m;
	mask.m_mask.zw = m;
#endif
	return mask;
}

HK_FORCE_INLINE hkBool32 hkSimdDouble64::isSignBitSet() const
{
	return _mm_movemask_pd(m_real);
}

HK_FORCE_INLINE hkBool32 hkSimdDouble64::isSignBitClear() const
{
	return !_mm_movemask_pd(m_real);
}

HK_FORCE_INLINE const hkVector4dComparison hkSimdDouble64::signBitSet() const
{
	const __m128i maskS = _mm_srai_epi32(_mm_castpd_si128(m_real),31);
	const __m128i a = _mm_shuffle_epi32(maskS, _MM_SHUFFLE(3,3,1,1)); // no srai_epi64
	hkVector4dComparison mask;
#if HK_SSE_VERSION >= 0x50
	mask.m_mask = _mm256_broadcast_pd((const __m128d*)&a);
#else
	mask.m_mask.xy = _mm_castsi128_pd(a);
	mask.m_mask.zw = _mm_castsi128_pd(a);
#endif
	return mask;
}

HK_FORCE_INLINE const hkVector4dComparison hkSimdDouble64::signBitClear() const
{
	const __m128i maskS = _mm_srai_epi32(_mm_castpd_si128(m_real),31);
	const __m128i a = _mm_shuffle_epi32(maskS, _MM_SHUFFLE(3,3,1,1)); // no srai_epi64
	const __m128i b = _mm_cmpeq_epi32(a,_mm_setzero_si128());
	hkVector4dComparison mask;
#if HK_SSE_VERSION >= 0x50
	mask.m_mask = _mm256_broadcast_pd((const __m128d*)&b);
#else
	mask.m_mask.xy = _mm_castsi128_pd(b);
	mask.m_mask.zw = _mm_castsi128_pd(b);
#endif
	return mask;
}

HK_FORCE_INLINE hkBool32 hkSimdDouble64::isLess(hkSimdDouble64Parameter a) const
{
	return _mm_ucomilt_sd(m_real, a.m_real);
}

HK_FORCE_INLINE hkBool32 hkSimdDouble64::isLessEqual(hkSimdDouble64Parameter a) const
{
	return _mm_ucomile_sd(m_real, a.m_real);
}

HK_FORCE_INLINE hkBool32 hkSimdDouble64::isGreater(hkSimdDouble64Parameter a) const
{
	return _mm_ucomigt_sd(m_real, a.m_real);
}

HK_FORCE_INLINE hkBool32 hkSimdDouble64::isGreaterEqual(hkSimdDouble64Parameter a) const
{
	return _mm_ucomige_sd(m_real, a.m_real);
}

HK_FORCE_INLINE hkBool32 hkSimdDouble64::isEqual(hkSimdDouble64Parameter a) const
{
	return _mm_ucomieq_sd(m_real, a.m_real);
}

HK_FORCE_INLINE hkBool32 hkSimdDouble64::isNotEqual(hkSimdDouble64Parameter a) const
{
	return _mm_ucomineq_sd(m_real, a.m_real);
}

HK_FORCE_INLINE hkBool32 hkSimdDouble64::isLessZero() const
{
	return _mm_ucomilt_sd(m_real, _mm_setzero_pd());
}

HK_FORCE_INLINE hkBool32 hkSimdDouble64::isLessEqualZero() const
{
	return _mm_ucomile_sd(m_real, _mm_setzero_pd());
}

HK_FORCE_INLINE hkBool32 hkSimdDouble64::isGreaterZero() const
{
	return _mm_ucomigt_sd(m_real, _mm_setzero_pd());
}

HK_FORCE_INLINE hkBool32 hkSimdDouble64::isGreaterEqualZero() const
{
	return _mm_ucomige_sd(m_real, _mm_setzero_pd());
}

HK_FORCE_INLINE hkBool32 hkSimdDouble64::isEqualZero() const
{
	return _mm_ucomieq_sd(m_real, _mm_setzero_pd());
}

HK_FORCE_INLINE hkBool32 hkSimdDouble64::isNotEqualZero() const
{
	return _mm_ucomineq_sd(m_real, _mm_setzero_pd());
}

HK_FORCE_INLINE hkBool32 hkSimdDouble64::isOk() const
{
	const hkSingleDouble64 nanMask = _mm_cmpord_pd(m_real, _mm_setzero_pd());
	return _mm_movemask_pd(nanMask);
}

HK_FORCE_INLINE void hkSimdDouble64::setSelect( hkVector4dComparisonParameter comp, hkSimdDouble64Parameter trueValue, hkSimdDouble64Parameter falseValue )
{
	HK_MATH_ASSERT(0xc78f08e, comp.allAreSet() || (comp.getMask() == hkVector4ComparisonMask::MASK_NONE), "illegal compare mask");
#if HK_SSE_VERSION >= 0x50
	m_real = _mm_blendv_pd(falseValue.m_real, trueValue.m_real, _mm256_extractf128_pd(comp.m_mask,0));
#elif HK_SSE_VERSION >= 0x41
	m_real = _mm_blendv_pd(falseValue.m_real, trueValue.m_real, comp.m_mask.xy);
#else
	m_real = _mm_or_pd( _mm_and_pd(comp.m_mask.xy, trueValue.m_real), _mm_andnot_pd(comp.m_mask.xy, falseValue.m_real) );
#endif
}

HK_FORCE_INLINE void hkSimdDouble64::zeroIfFalse( hkVector4dComparisonParameter comp )
{
	HK_MATH_ASSERT(0xc78f08e, comp.allAreSet() || (comp.getMask() == hkVector4ComparisonMask::MASK_NONE), "illegal compare mask");
	m_real = _mm_and_pd(comp.m_mask.xy, m_real);
}

HK_FORCE_INLINE void hkSimdDouble64::zeroIfTrue( hkVector4dComparisonParameter comp )
{
	HK_MATH_ASSERT(0xc78f08e, comp.allAreSet() || (comp.getMask() == hkVector4ComparisonMask::MASK_NONE), "illegal compare mask");
	m_real = _mm_andnot_pd(comp.m_mask.xy, m_real);
}

HK_FORCE_INLINE void hkSimdDouble64::setMin(  hkSimdDouble64Parameter a, hkSimdDouble64Parameter b ) 
{
	m_real = _mm_min_pd( a.m_real, b.m_real );
}

HK_FORCE_INLINE void hkSimdDouble64::setMax(  hkSimdDouble64Parameter a, hkSimdDouble64Parameter b ) 
{
	m_real = _mm_max_pd( a.m_real, b.m_real );
}

HK_FORCE_INLINE void hkSimdDouble64::setAbs(  hkSimdDouble64Parameter a )
{
	m_real = _mm_castsi128_pd( _mm_srli_epi64( _mm_slli_epi64( _mm_castpd_si128(a.m_real), 1 ), 1 ) ); 
}

HK_FORCE_INLINE void hkSimdDouble64::setFloor(  hkSimdDouble64Parameter a )
{
	m_real = hkMath::twoFloor(a.m_real);
}

HK_FORCE_INLINE void hkSimdDouble64::setMod(  hkSimdDouble64Parameter a, hkSimdDouble64Parameter b )
{
	const __m128d denomIsZero = _mm_cmpeq_pd(b.m_real,_mm_setzero_pd());
	const __m128d q = hkMath::twoFloor(_mm_div_pd(a.m_real,b.m_real));
	__m128d result = _mm_sub_pd(a.m_real, _mm_mul_pd(q,b.m_real));
	m_real = _mm_andnot_pd(denomIsZero, result);
}

HK_FORCE_INLINE void hkSimdDouble64::setFlipSign(hkSimdDouble64Parameter v, hkSimdDouble64Parameter sSign)
{
	const __m128i mask = _mm_slli_epi64(_mm_srli_epi64(_mm_castpd_si128(sSign.m_real),63),63);
	m_real = _mm_xor_pd(v.m_real, _mm_castsi128_pd(mask));
}

HK_FORCE_INLINE void hkSimdDouble64::setFlipSign(hkSimdDouble64Parameter v, hkVector4dComparisonParameter mask)
{
	HK_MATH_ASSERT(0x5831c04, mask.allAreSet() || (mask.getMask() == hkVector4ComparisonMask::MASK_NONE), "illegal compare mask");
#if HK_SSE_VERSION >= 0x50
	const __m128i maskF = _mm_slli_epi64(_mm_srli_epi64(_mm_castpd_si128(_mm256_extractf128_pd(mask.m_mask,0)),63),63);
#else
	const __m128i maskF = _mm_slli_epi64(_mm_srli_epi64(_mm_castpd_si128(mask.m_mask.xy),63),63);
#endif
	m_real = _mm_xor_pd(v.m_real, _mm_castsi128_pd(maskF));
}


//
// advanced interface
//

namespace hkSimdReal_AdvancedInterface
{

template <hkMathAccuracyMode A, hkMathDivByZeroMode D>
struct unrolld_setReciprocal { HK_FORCE_INLINE static void apply(hkSingleDouble64& self, hkSimdDouble64Parameter a)
{
	HK_SIMDDOUBLE_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <hkMathAccuracyMode A>
struct unrolld_setReciprocal<A, HK_DIV_IGNORE> { HK_FORCE_INLINE static void apply(hkSingleDouble64& self, hkSimdDouble64Parameter a)
{
	switch (A)
	{
		case HK_ACC_23_BIT: 
			{
				const __m128 fr = _mm_cvtpd_ps(a.m_real);
				const __m128 r = _mm_rcp_ps(fr);
				const hkSingleDouble64 rb = _mm_cvtps_pd(r);
				// One Newton-Raphson refinement iteration
				const hkSingleDouble64 rbr = _mm_mul_pd(a.m_real, rb);
				const hkSingleDouble64 d = _mm_sub_pd(*(const hkSingleDouble64*)(g_vectordConstants + HK_QUADREAL_2), rbr);
				self = _mm_mul_pd(rb, d);
			}
			break;
		case HK_ACC_12_BIT: 
			{
				const __m128 fr = _mm_cvtpd_ps(a.m_real);
				const __m128 r = _mm_rcp_ps(fr);
				self = _mm_cvtps_pd(r);
			}
			break;
		default:
			{
				self = _mm_div_pd(*(const hkSingleDouble64*)(g_vectordConstants + HK_QUADREAL_1),a.m_real); 
			}
			break; // HK_ACC_FULL
	}
} };
template <hkMathAccuracyMode A>
struct unrolld_setReciprocal<A, HK_DIV_SET_ZERO> { HK_FORCE_INLINE static void apply(hkSingleDouble64& self, hkSimdDouble64Parameter a)
{
	const hkSingleDouble64 equalsZero = _mm_cmpeq_pd(a.m_real, _mm_setzero_pd());
	hkSingleDouble64 e; unrolld_setReciprocal<A, HK_DIV_IGNORE>::apply(e, a);
	self = _mm_andnot_pd(equalsZero, e);
} };
template <hkMathAccuracyMode A>
struct unrolld_setReciprocal<A, HK_DIV_SET_HIGH> { HK_FORCE_INLINE static void apply(hkSingleDouble64& self, hkSimdDouble64Parameter a)
{
	const hkSingleDouble64 equalsZero = _mm_cmpeq_pd(a.m_real, _mm_setzero_pd());
	hkSingleDouble64 e; unrolld_setReciprocal<A, HK_DIV_IGNORE>::apply(e, a);
	hkSingleDouble64 huge = _mm_set1_pd(HK_DOUBLE_HIGH);
	const __m128i maskS = _mm_slli_epi64(_mm_srli_epi64(_mm_castpd_si128(a.m_real),63),63);
	huge = _mm_xor_pd(huge, _mm_castsi128_pd(maskS));
#if HK_SSE_VERSION >= 0x41
	self = _mm_blendv_pd(e, huge, equalsZero);
#else
	self = _mm_or_pd( _mm_and_pd(equalsZero, huge), _mm_andnot_pd(equalsZero, e) );
#endif
} };
template <hkMathAccuracyMode A>
struct unrolld_setReciprocal<A, HK_DIV_SET_MAX> { HK_FORCE_INLINE static void apply(hkSingleDouble64& self, hkSimdDouble64Parameter a)
{
	const hkSingleDouble64 equalsZero = _mm_cmpeq_pd(a.m_real, _mm_setzero_pd());
	hkSingleDouble64 e; unrolld_setReciprocal<A, HK_DIV_IGNORE>::apply(e, a);
	hkSingleDouble64 huge = _mm_set1_pd(HK_DOUBLE_MAX);
	const __m128i maskS = _mm_slli_epi64(_mm_srli_epi64(_mm_castpd_si128(a.m_real),63),63);
	huge = _mm_xor_pd(huge, _mm_castsi128_pd(maskS));
#if HK_SSE_VERSION >= 0x41
	self = _mm_blendv_pd(e, huge, equalsZero);
#else
	self = _mm_or_pd( _mm_and_pd(equalsZero, huge), _mm_andnot_pd(equalsZero, e) );
#endif
} };
template <hkMathAccuracyMode A>
struct unrolld_setReciprocal<A, HK_DIV_SET_ZERO_AND_ONE> { HK_FORCE_INLINE static void apply(hkSingleDouble64& self, hkSimdDouble64Parameter a)
{
	unrolld_setReciprocal<A, HK_DIV_SET_ZERO>::apply(self, a);
	const hkSingleDouble64 one = *((const hkSingleDouble64*)(g_vectordConstants + HK_QUADREAL_1));
	const hkSingleDouble64 absVal = _mm_castsi128_pd( _mm_srli_epi64( _mm_slli_epi64( _mm_castpd_si128(_mm_sub_pd(self, one)), 1 ), 1 ) ); 
	const hkSingleDouble64 lessEqualEps = _mm_cmple_pd(absVal, *((const hkSingleDouble64*)(g_vectordConstants + HK_QUADREAL_EPS)));
#if HK_SSE_VERSION >= 0x41
	self = _mm_blendv_pd(self, one, lessEqualEps);
#else
	self = _mm_or_pd( _mm_and_pd(lessEqualEps, one), _mm_andnot_pd(lessEqualEps, self) );
#endif
} };

} // namespace 

template <hkMathAccuracyMode A, hkMathDivByZeroMode D> 
HK_FORCE_INLINE void hkSimdDouble64::setReciprocal(hkSimdDouble64Parameter a)
{
	hkSimdReal_AdvancedInterface::unrolld_setReciprocal<A,D>::apply(m_real,a);
}

HK_FORCE_INLINE void hkSimdDouble64::setReciprocal(hkSimdDouble64Parameter a)
{
	hkSimdReal_AdvancedInterface::unrolld_setReciprocal<HK_ACC_23_BIT,HK_DIV_IGNORE>::apply(m_real,a);
}



namespace hkSimdReal_AdvancedInterface
{

template <hkMathAccuracyMode A, hkMathDivByZeroMode D>
struct unrolld_setDiv { HK_FORCE_INLINE static void apply(hkSingleDouble64& self, hkSimdDouble64Parameter a, hkSimdDouble64Parameter b)
{
	HK_SIMDDOUBLE_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <hkMathAccuracyMode A>
struct unrolld_setDiv<A, HK_DIV_IGNORE> { HK_FORCE_INLINE static void apply(hkSingleDouble64& self, hkSimdDouble64Parameter a, hkSimdDouble64Parameter b)
{
	if (A == HK_ACC_FULL) 
	{ 
		self = _mm_div_pd(a.m_real, b.m_real); 
	}
	else
	{
		hkSingleDouble64 t;
		unrolld_setReciprocal<A,HK_DIV_IGNORE>::apply(t,b);
		self = _mm_mul_pd(a.m_real,t);
	}
} };
template <hkMathAccuracyMode A>
struct unrolld_setDiv<A, HK_DIV_SET_ZERO> { HK_FORCE_INLINE static void apply(hkSingleDouble64& self, hkSimdDouble64Parameter a, hkSimdDouble64Parameter b)
{
	const hkSingleDouble64 equalsZero = _mm_cmpeq_pd(b.m_real, _mm_setzero_pd());
	hkSingleDouble64 e; unrolld_setDiv<A, HK_DIV_IGNORE>::apply(e, a, b);
	self = _mm_andnot_pd(equalsZero, e);
} };
template <hkMathAccuracyMode A>
struct unrolld_setDiv<A, HK_DIV_SET_HIGH> { HK_FORCE_INLINE static void apply(hkSingleDouble64& self, hkSimdDouble64Parameter a, hkSimdDouble64Parameter b)
{
	const hkSingleDouble64 equalsZero = _mm_cmpeq_pd(b.m_real, _mm_setzero_pd());
	hkSingleDouble64 e; unrolld_setDiv<A, HK_DIV_IGNORE>::apply(e, a, b);
	hkSingleDouble64 huge = _mm_set1_pd(HK_DOUBLE_HIGH);
	const __m128i maskS = _mm_slli_epi64(_mm_srli_epi64(_mm_castpd_si128(a.m_real),63),63);
	huge = _mm_xor_pd(huge, _mm_castsi128_pd(maskS));
#if HK_SSE_VERSION >= 0x41
	self = _mm_blendv_pd(e, huge, equalsZero);
#else
	self = _mm_or_pd( _mm_and_pd(equalsZero, huge), _mm_andnot_pd(equalsZero, e) );
#endif
} };
template <hkMathAccuracyMode A>
struct unrolld_setDiv<A, HK_DIV_SET_MAX> { HK_FORCE_INLINE static void apply(hkSingleDouble64& self, hkSimdDouble64Parameter a, hkSimdDouble64Parameter b)
{
	const hkSingleDouble64 equalsZero = _mm_cmpeq_pd(b.m_real, _mm_setzero_pd());
	hkSingleDouble64 e; unrolld_setDiv<A, HK_DIV_IGNORE>::apply(e, a, b);
	hkSingleDouble64 huge = _mm_set1_pd(HK_DOUBLE_MAX);
	const __m128i maskS = _mm_slli_epi64(_mm_srli_epi64(_mm_castpd_si128(a.m_real),63),63);
	huge = _mm_xor_pd(huge, _mm_castsi128_pd(maskS));
#if HK_SSE_VERSION >= 0x41
	self = _mm_blendv_pd(e, huge, equalsZero);
#else
	self = _mm_or_pd( _mm_and_pd(equalsZero, huge), _mm_andnot_pd(equalsZero, e) );
#endif
} };
template <hkMathAccuracyMode A>
struct unrolld_setDiv<A, HK_DIV_SET_ZERO_AND_ONE> { HK_FORCE_INLINE static void apply(hkSingleDouble64& self, hkSimdDouble64Parameter a, hkSimdDouble64Parameter b)
{
	unrolld_setDiv<A, HK_DIV_SET_ZERO>::apply(self, a, b);
	const hkSingleDouble64 one = *((const hkSingleDouble64*)(g_vectordConstants + HK_QUADREAL_1));
	const hkSingleDouble64 absVal = _mm_castsi128_pd( _mm_srli_epi64( _mm_slli_epi64( _mm_castpd_si128(_mm_sub_pd(self, one)), 1 ), 1 ) ); 
	const hkSingleDouble64 lessEqualEps = _mm_cmple_pd(absVal, *((const hkSingleDouble64*)(g_vectordConstants + HK_QUADREAL_EPS)));
#if HK_SSE_VERSION >= 0x41
	self = _mm_blendv_pd(self, one, lessEqualEps);
#else
	self = _mm_or_pd( _mm_and_pd(lessEqualEps, one), _mm_andnot_pd(lessEqualEps, self) );
#endif
} };

} // namespace 

template <hkMathAccuracyMode A, hkMathDivByZeroMode D> 
HK_FORCE_INLINE void hkSimdDouble64::setDiv(hkSimdDouble64Parameter a, hkSimdDouble64Parameter b)
{
	hkSimdReal_AdvancedInterface::unrolld_setDiv<A,D>::apply(m_real,a,b);
}

HK_FORCE_INLINE void hkSimdDouble64::setDiv(hkSimdDouble64Parameter a, hkSimdDouble64Parameter b)
{
	hkSimdReal_AdvancedInterface::unrolld_setDiv<HK_ACC_23_BIT,HK_DIV_IGNORE>::apply(m_real,a,b);
}

template <hkMathAccuracyMode A, hkMathDivByZeroMode D> 
HK_FORCE_INLINE void hkSimdDouble64::div(hkSimdDouble64Parameter a)
{
	setDiv<A,D>( *this, a );
}

HK_FORCE_INLINE void hkSimdDouble64::div(hkSimdDouble64Parameter a)
{
	setDiv( *this, a );
}

HK_FORCE_INLINE const hkSimdDouble64 hkSimdDouble64::operator/ (hkSimdDouble64Parameter r) const
{
	hkSimdDouble64 q;
	q.setDiv(*this,r);
	return q;
}


namespace hkSimdReal_AdvancedInterface
{

template <hkMathAccuracyMode A, hkMathNegSqrtMode S>
struct unrolld_sqrt { HK_FORCE_INLINE static hkSingleDouble64 apply(hkSimdDouble64Parameter self)
{
	HK_SIMDDOUBLE_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
	return _mm_setzero_pd();
} };
template <hkMathAccuracyMode A>
struct unrolld_sqrt<A, HK_SQRT_IGNORE> { HK_FORCE_INLINE static hkSingleDouble64 apply(hkSimdDouble64Parameter self)
{
	switch (A)
	{
		case HK_ACC_23_BIT: 
			{
				const __m128 fr = _mm_cvtpd_ps(self.m_real);
				const __m128 re = _mm_rsqrt_ps(fr);
				const hkSingleDouble64 e = _mm_cvtps_pd(re);
				// One Newton-Raphson refinement iteration
				const hkSingleDouble64 he = _mm_mul_pd(*(const hkSingleDouble64*)(g_vectordConstants + HK_QUADREAL_INV_2),e);
				const hkSingleDouble64 ree = _mm_mul_pd(_mm_mul_pd(self.m_real,e),e);
				hkSingleDouble64 refined = _mm_mul_pd(he, _mm_sub_pd(*(const hkSingleDouble64*)(g_vectordConstants + HK_QUADREAL_3), ree) );
				return _mm_mul_pd(self.m_real, refined);
			}
			break;
		case HK_ACC_12_BIT: 
			{
				const __m128 fr = _mm_cvtpd_ps(self.m_real);
				const __m128 re = _mm_rsqrt_ps(fr);
				hkSingleDouble64 e = _mm_cvtps_pd(re);
				return _mm_mul_pd(self.m_real, e);
			}
			break;
		default:
			{
				return _mm_sqrt_pd(self.m_real); 
			}
			break; // HK_ACC_FULL
	}
} };
template <hkMathAccuracyMode A>
struct unrolld_sqrt<A, HK_SQRT_SET_ZERO> { HK_FORCE_INLINE static hkSingleDouble64 apply(hkSimdDouble64Parameter self)
{
	const hkSingleDouble64 equalsZero = _mm_cmple_pd(self.m_real, _mm_setzero_pd());
	const hkSingleDouble64 e = unrolld_sqrt<A, HK_SQRT_IGNORE>::apply(self);
	return _mm_andnot_pd(equalsZero, e);
} };

} // namespace 

template <hkMathAccuracyMode A, hkMathNegSqrtMode S> 
HK_FORCE_INLINE const hkSimdDouble64 hkSimdDouble64::sqrt() const
{
	return hkSimdDouble64::convert(hkSimdReal_AdvancedInterface::unrolld_sqrt<A,S>::apply(*this));
}

HK_FORCE_INLINE const hkSimdDouble64 hkSimdDouble64::sqrt() const
{
	return hkSimdDouble64::convert(hkSimdReal_AdvancedInterface::unrolld_sqrt<HK_ACC_23_BIT,HK_SQRT_SET_ZERO>::apply(*this));
}


namespace hkSimdReal_AdvancedInterface
{

template <hkMathAccuracyMode A, hkMathNegSqrtMode S>
struct unrolld_sqrtInverse { HK_FORCE_INLINE static hkSingleDouble64 apply(hkSimdDouble64Parameter self)
{
	HK_SIMDDOUBLE_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
	return _mm_setzero_pd();
} };
template <hkMathAccuracyMode A>
struct unrolld_sqrtInverse<A, HK_SQRT_IGNORE> { HK_FORCE_INLINE static hkSingleDouble64 apply(hkSimdDouble64Parameter self)
{
	switch (A)
	{
		case HK_ACC_23_BIT: 
			{
				const __m128 fr = _mm_cvtpd_ps(self.m_real);
				const __m128 re = _mm_rsqrt_ps(fr);
				const hkSingleDouble64 e = _mm_cvtps_pd(re);
				// One Newton-Raphson refinement iteration
				const hkSingleDouble64 he = _mm_mul_pd(*(const hkSingleDouble64*)(g_vectordConstants + HK_QUADREAL_INV_2),e);
				const hkSingleDouble64 ree = _mm_mul_pd(_mm_mul_pd(self.m_real,e),e);
				return _mm_mul_pd(he, _mm_sub_pd(*(const hkSingleDouble64*)(g_vectordConstants + HK_QUADREAL_3), ree) );
			}
			break;
		case HK_ACC_12_BIT: 
			{
				const __m128 fr = _mm_cvtpd_ps(self.m_real);
				const __m128 re = _mm_rsqrt_ps(fr);
				return _mm_cvtps_pd(re);
			}
			break;
		default:         
			{
				return _mm_div_pd(*(const hkSingleDouble64*)(g_vectordConstants + HK_QUADREAL_1), _mm_sqrt_pd(self.m_real));
			}
			break; // HK_ACC_FULL
	}
} };
template <hkMathAccuracyMode A>
struct unrolld_sqrtInverse<A, HK_SQRT_SET_ZERO> { HK_FORCE_INLINE static hkSingleDouble64 apply(hkSimdDouble64Parameter self)
{
	const hkSingleDouble64 equalsZero = _mm_cmple_pd(self.m_real, _mm_setzero_pd());
	const hkSingleDouble64 e = unrolld_sqrtInverse<A, HK_SQRT_IGNORE>::apply(self);
	return _mm_andnot_pd(equalsZero, e);
} };
} // namespace 

template <hkMathAccuracyMode A, hkMathNegSqrtMode S> 
HK_FORCE_INLINE const hkSimdDouble64 hkSimdDouble64::sqrtInverse() const
{
	return hkSimdDouble64::convert(hkSimdReal_AdvancedInterface::unrolld_sqrtInverse<A,S>::apply(*this));
}

HK_FORCE_INLINE const hkSimdDouble64 hkSimdDouble64::sqrtInverse() const
{
	return hkSimdDouble64::convert(hkSimdReal_AdvancedInterface::unrolld_sqrtInverse<HK_ACC_23_BIT,HK_SQRT_SET_ZERO>::apply(*this));
}


template <int N, hkMathIoMode A>
HK_FORCE_INLINE void hkSimdDouble64::load(const hkFloat32 *p )
{
	HK_SIMDDOUBLE_DIMENSION_CHECK;
	__m128 a = _mm_load_ss(p);
	__m128d d = _mm_cvtps_pd(a);
	m_real = _mm_shuffle_pd(d,d,_MM_SHUFFLE2(0,0));
}

template <int N, hkMathIoMode A>
HK_FORCE_INLINE void hkSimdDouble64::load(const hkDouble64 *p )
{
	HK_SIMDDOUBLE_DIMENSION_CHECK;
#if HK_SSE_VERSION >= 0x30
	m_real = _mm_loaddup_pd(p);
#else
	m_real = _mm_load1_pd(p);
#endif
}

template <int N>
HK_FORCE_INLINE void hkSimdDouble64::load(const hkFloat32 *p )
{
	load<N,HK_IO_BYTE_ALIGNED>(p);
}

template <int N>
HK_FORCE_INLINE void hkSimdDouble64::load(const hkDouble64 *p )
{
	load<N,HK_IO_BYTE_ALIGNED>(p);
}


template <int N, hkMathIoMode A>
HK_FORCE_INLINE void hkSimdDouble64::load(const hkHalf *p )
{
	HK_SIMDDOUBLE_DIMENSION_CHECK;
#if defined(HK_HALF_IS_FLOAT)
	__m128 f = _mm_load_ss((const float*)p);
#else
	float x; p[0].store(&x); // do conversion in SSE
	__m128 f = _mm_load_ss(&x);
#endif
	__m128d d = _mm_cvtps_pd(f);
	m_real = _mm_shuffle_pd(d,d,_MM_SHUFFLE2(0,0));
}

template <int N>
HK_FORCE_INLINE void hkSimdDouble64::load(const hkHalf *p )
{
	load<N,HK_IO_BYTE_ALIGNED>(p);
}

namespace hkSimdReal_AdvancedInterface
{
HK_FORCE_INLINE static void unpackF16F32(const __m128i& f16, __m128& f32)
{
	static HK_ALIGN16(const unsigned int half_sign[4])		  = {0x00008000, 0x00008000, 0x00008000, 0x00008000};
	static HK_ALIGN16(const unsigned int half_exponent[4])	  = {0x00007C00, 0x00007C00, 0x00007C00, 0x00007C00};
	static HK_ALIGN16(const unsigned int half_mantissa[4])	  = {0x000003FF, 0x000003FF, 0x000003FF, 0x000003FF};
	static HK_ALIGN16(const unsigned int half_bias_offset[4]) = {0x0001C000, 0x0001C000, 0x0001C000, 0x0001C000};

	__m128i unpacked = _mm_unpacklo_epi16(f16, _mm_setzero_si128());

	__m128i sign = _mm_and_si128(unpacked, *(__m128i*)half_sign);
	__m128i exponent = _mm_and_si128(unpacked, *(__m128i*)half_exponent);
	__m128i exp_zero = _mm_cmpeq_epi32(exponent, _mm_setzero_si128());
	__m128i mantissa = _mm_and_si128(unpacked, *(__m128i*)half_mantissa);
	__m128i exp_offset = _mm_andnot_si128(exp_zero, _mm_add_epi32(exponent, *(__m128i*)half_bias_offset));

	__m128i sign_shift = _mm_slli_epi32(sign, 16);
	__m128i exp_mantissa = _mm_slli_epi32(_mm_or_si128(exp_offset,mantissa), 13);

	f32 = _mm_castsi128_ps(_mm_or_si128(sign_shift, exp_mantissa));
}
}
template <int N, hkMathIoMode A>
HK_FORCE_INLINE void hkSimdDouble64::load(const hkFloat16 *p )
{
	HK_SIMDDOUBLE_DIMENSION_CHECK;
	HK_ALIGN16(hkFloat16 tmp[2]);
	tmp[0] = tmp[1] = p[0];
	__m128i twohalfs = _mm_castps_si128( _mm_load_ss((const float*)tmp) );
	__m128 twofloats;
	hkSimdReal_AdvancedInterface::unpackF16F32(twohalfs, twofloats);
	m_real = _mm_cvtps_pd(twofloats);
}

template <int N>
HK_FORCE_INLINE void hkSimdDouble64::load(const hkFloat16 *p )
{
	load<N,HK_IO_BYTE_ALIGNED>(p);
}


template <int N, hkMathIoMode A, hkMathRoundingMode R>
HK_FORCE_INLINE void hkSimdDouble64::store(  hkFloat32 *p ) const
{
	HK_SIMDDOUBLE_DIMENSION_CHECK;
	__m128 f = _mm_cvtpd_ps(m_real);
	_mm_store_ss( p, f );
}

template <int N, hkMathIoMode A, hkMathRoundingMode R>
HK_FORCE_INLINE void hkSimdDouble64::store(  hkDouble64 *p ) const
{
	HK_SIMDDOUBLE_DIMENSION_CHECK;
	_mm_store_sd( p, m_real );
}

template <int N, hkMathIoMode A>
HK_FORCE_INLINE void hkSimdDouble64::store(  hkDouble64 *p ) const
{
	store<N,A,HK_ROUND_DEFAULT>(p);
}

template <int N, hkMathIoMode A>
HK_FORCE_INLINE void hkSimdDouble64::store(  hkFloat32 *p ) const
{
	store<N,A,HK_ROUND_DEFAULT>(p);
}

template <int N>
HK_FORCE_INLINE void hkSimdDouble64::store(  hkDouble64 *p ) const
{
	store<N,HK_IO_BYTE_ALIGNED,HK_ROUND_DEFAULT>(p);
}

template <int N>
HK_FORCE_INLINE void hkSimdDouble64::store(  hkFloat32 *p ) const
{
	store<N,HK_IO_BYTE_ALIGNED,HK_ROUND_DEFAULT>(p);
}


template <int N, hkMathIoMode A, hkMathRoundingMode R>
HK_FORCE_INLINE void hkSimdDouble64::store(  hkHalf *p ) const
{
	HK_SIMDDOUBLE_DIMENSION_CHECK;
#if defined(HK_HALF_IS_FLOAT)
	static HK_ALIGN16(const hkUint64 mask[2])      = {0xFFFFFFFF00000000ull, 0xFFFFFFFF00000000ull};
	__m128d  vs0;
	if (R == HK_ROUND_NEAREST)
		vs0 = m_real;
	else
		vs0 = _mm_and_pd( m_real, *((__m128d*)&mask) );
	_mm_store_ss((float*)p, _mm_cvtpd_ps(vs0));
#else
	static HK_ALIGN16(const hkUint32 scale[4])      = {0x3F808000, 0x3F808000, 0x3F808000, 0x3F808000}; // 1 + 1/256 as float32
	__m128  vs0 = _mm_cvtpd_ps(m_real);
	if (R == HK_ROUND_NEAREST)
		vs0 = _mm_mul_ps( vs0, *((__m128*)&scale) );
	__m128i tmp0 = _mm_srai_epi32( _mm_castps_si128(vs0), 16 );
	__m128i tmp1 = _mm_packs_epi32(tmp0, tmp0);
	float ftmp1; _mm_store_ss(&ftmp1, _mm_castsi128_ps(tmp1));
	const hkHalf* HK_RESTRICT htmp1 = (const hkHalf* HK_RESTRICT)&ftmp1;
	p[0] = htmp1[0];
#endif
}

template <int N>
HK_FORCE_INLINE void hkSimdDouble64::store(  hkHalf *p ) const
{
	store<N,HK_IO_SIMD_ALIGNED,HK_ROUND_DEFAULT>(p);
}




namespace hkSimdReal_AdvancedInterface
{
template <hkMathRoundingMode R>
HK_FORCE_INLINE static void convertSingleRealF16(const hkSingleDouble64& self, __m128i& packed)
{
	static HK_ALIGN16(const unsigned int infinity[4]) = {0x47FFE000, 0x47FFE000, 0x47FFE000, 0x47FFE000};
	static HK_ALIGN16(const unsigned int denormal[4]) = {0x38800000, 0x38800000, 0x38800000, 0x38800000};
	static HK_ALIGN16(const unsigned int fixup[4])    = {0x48000000, 0x48000000, 0x48000000, 0x48000000};
	static HK_ALIGN16(const unsigned int round1[4])   = {0x00000001, 0x00000001, 0x00000001, 0x00000001};
	static HK_ALIGN16(const unsigned int round2[4])   = {0x00000FFF, 0x00000FFF, 0x00000FFF, 0x00000FFF};
	static HK_ALIGN16(const unsigned int base[4])     = {0x00007FFF, 0x00007FFF, 0x00007FFF, 0x00007FFF};
	static HK_ALIGN16(const unsigned int integer[4])  = {0x52000000, 0x52000000, 0x52000000, 0x52000000};

	__m128 xyzw = _mm_cvtpd_ps(self);

	// Compute masks
	__m128 r_abs = _mm_castsi128_ps(_mm_srli_epi32(_mm_slli_epi32(_mm_castps_si128(xyzw), 1),1));
	__m128 r_inf = _mm_cmpnlt_ps(r_abs, *(__m128*)infinity);
	__m128 r_den = _mm_cmplt_ps(r_abs, *(__m128*)denormal);

	// Denormal case
	__m128i r_int = _mm_cvttps_epi32( _mm_mul_ps(r_abs, *(__m128*)integer) );

	// Normal case and combine
	__m128i fix = _mm_add_epi32(_mm_castps_si128(r_abs), *(__m128i*)fixup);
	__m128i select_den = _mm_and_si128(r_int, _mm_castps_si128(r_den));
	__m128i select_fix = _mm_andnot_si128(_mm_castps_si128(r_den), fix);
	__m128i all = _mm_or_si128(select_den, select_fix);

	__m128i all_rounded;
	if (R == HK_ROUND_NEAREST)
	{
		// Correct rounding
		__m128i rounded = _mm_add_epi32(_mm_and_si128(_mm_srli_epi32(all, 13), *(__m128i*)round1), *(__m128i*)round2);
		all_rounded = _mm_add_epi32(rounded, all);
	}
	else
	{
		all_rounded = all;
	}

	// Combine with sign and infinity
	__m128i extract_sign = _mm_slli_epi32(_mm_srai_epi32(_mm_castps_si128(xyzw), 31), 15);
	__m128i mantissa = _mm_and_si128(_mm_or_si128(_mm_srli_epi32(all_rounded, 13), _mm_castps_si128(r_inf)), *(__m128i*)base);
	__m128i assembled = _mm_or_si128(mantissa, extract_sign); // Result in lower words of each element

	// Pack
	packed = _mm_packs_epi32(assembled, assembled); // result in lower elements
}
} // namespace 

template <int N, hkMathIoMode A, hkMathRoundingMode R>
HK_FORCE_INLINE void hkSimdDouble64::store(  hkFloat16 *p ) const
{
	HK_SIMDDOUBLE_DIMENSION_CHECK;
	__m128i packed;
	hkSimdReal_AdvancedInterface::convertSingleRealF16<R>(m_real,packed);
	HK_ALIGN16(hkFloat16 tmp[2]);
	_mm_store_ss((float*)tmp, _mm_castsi128_ps(packed));
	p[0] = tmp[0];
}

template <int N>
HK_FORCE_INLINE void hkSimdDouble64::store(  hkFloat16 *p ) const
{
	store<N,HK_IO_BYTE_ALIGNED,HK_ROUND_DEFAULT>(p);
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
