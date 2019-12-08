/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */


HK_FORCE_INLINE /*static*/ const hkSimdFloat32 HK_CALL hkSimdFloat32::convert(const hkSingleFloat32& x)
{
	hkSimdFloat32 sr;
	sr.m_real = x;
	return sr;
	//HK_ASSERT(0x7c3a4d98, x.m128_i32[0] == x.m128_i32[1] && x.m128_i32[0] == x.m128_i32[2] && x.m128_i32[0] == x.m128_i32[3]);
}

template<int vectorConstant>
HK_FORCE_INLINE /*static*/ const hkSimdFloat32 HK_CALL hkSimdFloat32::getConstant()
{
	HK_COMPILE_TIME_ASSERT2( 
		(vectorConstant!=HK_QUADREAL_1000) && (vectorConstant!=HK_QUADREAL_0100) && (vectorConstant!=HK_QUADREAL_0010) && (vectorConstant!=HK_QUADREAL_0001) &&
		(vectorConstant!=HK_QUADREAL_m11m11) && (vectorConstant!=HK_QUADREAL_1248) && (vectorConstant!=HK_QUADREAL_8421) && (vectorConstant!=HK_QUADREAL_1010)  && (vectorConstant!=HK_QUADREAL_1100)
		, HK_SIMDFLOAT_ILLEGAL_CONSTANT_REQUEST);
	return convert(*(g_vectorfConstants + vectorConstant));
}

HK_FORCE_INLINE /*static*/ const hkSimdFloat32 HK_CALL hkSimdFloat32::getConstant(hkVectorConstant constant)
{
	HK_MATH_ASSERT( 0x909ff234,
		(constant!=HK_QUADREAL_1000) && (constant!=HK_QUADREAL_0100) && (constant!=HK_QUADREAL_0010) && (constant!=HK_QUADREAL_0001) &&
		(constant!=HK_QUADREAL_m11m11) && (constant!=HK_QUADREAL_1248) && (constant!=HK_QUADREAL_8421) && (constant!=HK_QUADREAL_1010)  && (constant!=HK_QUADREAL_1100)
		, "not a simdreal constant");
	return convert(*(g_vectorfConstants + constant));
}

#ifndef HK_DISABLE_IMPLICIT_SIMDREAL_FLOAT_CONVERSION
HK_FORCE_INLINE hkSimdFloat32::hkSimdFloat32(const hkFloat32& x)
{
	m_real = _mm_set1_ps(x);
}

HK_FORCE_INLINE hkSimdFloat32::operator hkFloat32() const
{
	return _mm_cvtss_f32(m_real);
}
#endif

HK_FORCE_INLINE hkFloat32 hkSimdFloat32::getReal() const
{
	return _mm_cvtss_f32(m_real);
}

HK_FORCE_INLINE void hkSimdFloat32::setFromFloat(const hkFloat32& x)
{
	__m128 fx = _mm_load_ss(&x);
	m_real = _mm_shuffle_ps(fx,fx,_MM_SHUFFLE(0,0,0,0));
}

HK_FORCE_INLINE void hkSimdFloat32::setFromFloat(const hkDouble64& x)
{
	__m128d d = _mm_load_sd(&x);
	__m128 f = _mm_cvtpd_ps(d);
	m_real = _mm_shuffle_ps(f,f,_MM_SHUFFLE(0,0,0,0));
}

HK_FORCE_INLINE void hkSimdFloat32::setFromHalf(const hkHalf& h)
{
#if defined(HK_HALF_IS_FLOAT)
	m_real = _mm_load1_ps((const float*)&h);
#else
	float x; h.store(&x);
	setFromFloat(x);
#endif
}

HK_FORCE_INLINE void hkSimdFloat32::setFromInt32(const hkInt32&  x)
{
	__m128 ix = _mm_cvtsi32_ss(_mm_setzero_ps(),x);
	m_real = _mm_shuffle_ps(ix,ix,_MM_SHUFFLE(0,0,0,0));
}


HK_FORCE_INLINE void hkSimdFloat32::setFromUint16(const hkUint16& x)
{
	int i = x;
	setFromInt32(i);
}

HK_FORCE_INLINE void hkSimdFloat32::setFromUint8(const hkUint8& x)
{
	int i = x;
	setFromInt32(i);
}

HK_FORCE_INLINE void hkSimdFloat32::setZero()
{
	m_real = _mm_setzero_ps();
}


HK_FORCE_INLINE void hkSimdFloat32::storeSaturateInt32(hkInt32* HK_RESTRICT result) const
{
	*result = _mm_cvtsi128_si32(_mm_cvttps_epi32(m_real));
}


HK_FORCE_INLINE void hkSimdFloat32::storeSaturateUint16(hkUint16* HK_RESTRICT result) const
{
	hkSingleFloat32 clamped   = _mm_max_ps(m_real,_mm_setzero_ps());	
	clamped = _mm_min_ps(clamped,_mm_set1_ps(65535.0f));
	*result = hkUint16(_mm_cvtsi128_si32(_mm_cvttps_epi32(clamped)));
}


HK_FORCE_INLINE const hkSimdFloat32 hkSimdFloat32::operator+ (hkSimdFloat32Parameter r) const
{
	return hkSimdFloat32::convert(_mm_add_ps(m_real,r.m_real));
}

HK_FORCE_INLINE const hkSimdFloat32 hkSimdFloat32::operator- (hkSimdFloat32Parameter r) const
{
	return hkSimdFloat32::convert(_mm_sub_ps(m_real,r.m_real));
}

HK_FORCE_INLINE const hkSimdFloat32 hkSimdFloat32::operator* (hkSimdFloat32Parameter r) const
{
	return hkSimdFloat32::convert(_mm_mul_ps(m_real,r.m_real));
}


#ifdef HK_DISABLE_OLD_VECTOR4_INTERFACE

HK_FORCE_INLINE bool hkSimdFloat32::operator< (hkSimdFloat32Parameter r) const
{
	return _mm_ucomilt_ss(m_real, r.m_real);
}

HK_FORCE_INLINE bool hkSimdFloat32::operator<= (hkSimdFloat32Parameter r) const
{
	return _mm_ucomile_ss(m_real, r.m_real);
}

HK_FORCE_INLINE bool hkSimdFloat32::operator> (hkSimdFloat32Parameter r) const
{
	return _mm_ucomigt_ss(m_real, r.m_real);
}

HK_FORCE_INLINE bool hkSimdFloat32::operator>= (hkSimdFloat32Parameter r) const
{
	return _mm_ucomige_ss(m_real, r.m_real);
}

HK_FORCE_INLINE bool hkSimdFloat32::operator== (hkSimdFloat32Parameter r) const
{
	return _mm_ucomieq_ss(m_real, r.m_real);
}

HK_FORCE_INLINE bool hkSimdFloat32::operator!= (hkSimdFloat32Parameter r) const
{
	return _mm_ucomineq_ss(m_real, r.m_real);
}

#endif

HK_FORCE_INLINE const hkSimdFloat32 hkSimdFloat32::operator-() const
{
	return hkSimdFloat32::convert(_mm_sub_ps(_mm_setzero_ps(),m_real));
}

HK_FORCE_INLINE const hkVector4fComparison hkSimdFloat32::less(hkSimdFloat32Parameter a) const
{
	return hkVector4fComparison::convert(_mm_cmplt_ps(m_real, a.m_real));
}

HK_FORCE_INLINE const hkVector4fComparison hkSimdFloat32::greater(hkSimdFloat32Parameter a) const
{
	return hkVector4fComparison::convert(_mm_cmpgt_ps(m_real, a.m_real));
}

HK_FORCE_INLINE const hkVector4fComparison hkSimdFloat32::greaterEqual(hkSimdFloat32Parameter a) const
{
	return hkVector4fComparison::convert(_mm_cmpge_ps(m_real, a.m_real));
}

HK_FORCE_INLINE const hkVector4fComparison hkSimdFloat32::lessEqual(hkSimdFloat32Parameter a) const
{
	return hkVector4fComparison::convert(_mm_cmple_ps(m_real, a.m_real));
}

HK_FORCE_INLINE const hkVector4fComparison hkSimdFloat32::equal(hkSimdFloat32Parameter a) const
{
	return hkVector4fComparison::convert(_mm_cmpeq_ps(m_real, a.m_real));
}

HK_FORCE_INLINE const hkVector4fComparison hkSimdFloat32::notEqual(hkSimdFloat32Parameter a) const
{
	return hkVector4fComparison::convert(_mm_cmpneq_ps(m_real, a.m_real));
}

HK_FORCE_INLINE const hkVector4fComparison hkSimdFloat32::lessZero() const
{
	return hkVector4fComparison::convert(_mm_cmplt_ps(m_real, _mm_setzero_ps()));
}

HK_FORCE_INLINE const hkVector4fComparison hkSimdFloat32::lessEqualZero() const
{
	return hkVector4fComparison::convert(_mm_cmple_ps(m_real, _mm_setzero_ps()));
}

HK_FORCE_INLINE const hkVector4fComparison hkSimdFloat32::greaterZero() const
{
	return hkVector4fComparison::convert(_mm_cmpgt_ps(m_real, _mm_setzero_ps()));
}

HK_FORCE_INLINE const hkVector4fComparison hkSimdFloat32::greaterEqualZero() const
{
	return hkVector4fComparison::convert(_mm_cmpge_ps(m_real, _mm_setzero_ps()));
}

HK_FORCE_INLINE const hkVector4fComparison hkSimdFloat32::equalZero() const
{
	return hkVector4fComparison::convert(_mm_cmpeq_ps(m_real, _mm_setzero_ps()));
}

HK_FORCE_INLINE const hkVector4fComparison hkSimdFloat32::notEqualZero() const
{
	return hkVector4fComparison::convert(_mm_cmpneq_ps(m_real, _mm_setzero_ps()));
}

HK_FORCE_INLINE hkBool32 hkSimdFloat32::isSignBitSet() const
{
	return _mm_movemask_ps(m_real);
}

HK_FORCE_INLINE hkBool32 hkSimdFloat32::isSignBitClear() const
{
	return !_mm_movemask_ps(m_real); 
}

HK_FORCE_INLINE const hkVector4fComparison hkSimdFloat32::signBitSet() const
{
	return hkVector4fComparison::convert( _mm_castsi128_ps(_mm_srai_epi32(_mm_castps_si128(m_real),31)) );
}

HK_FORCE_INLINE const hkVector4fComparison hkSimdFloat32::signBitClear() const
{
	return hkVector4fComparison::convert( _mm_castsi128_ps(_mm_cmpeq_epi32(_mm_srai_epi32(_mm_castps_si128(m_real),31),_mm_setzero_si128())) );
}

HK_FORCE_INLINE hkBool32 hkSimdFloat32::isLess(hkSimdFloat32Parameter a) const
{
	return _mm_ucomilt_ss(m_real, a.m_real);
}

HK_FORCE_INLINE hkBool32 hkSimdFloat32::isLessEqual(hkSimdFloat32Parameter a) const
{
	return _mm_ucomile_ss(m_real, a.m_real);
}

HK_FORCE_INLINE hkBool32 hkSimdFloat32::isGreater(hkSimdFloat32Parameter a) const
{
	return _mm_ucomigt_ss(m_real, a.m_real);
}

HK_FORCE_INLINE hkBool32 hkSimdFloat32::isGreaterEqual(hkSimdFloat32Parameter a) const
{
	return _mm_ucomige_ss(m_real, a.m_real);
}

HK_FORCE_INLINE hkBool32 hkSimdFloat32::isEqual(hkSimdFloat32Parameter a) const
{
	return _mm_ucomieq_ss(m_real, a.m_real);
}

HK_FORCE_INLINE hkBool32 hkSimdFloat32::isNotEqual(hkSimdFloat32Parameter a) const
{
	return _mm_ucomineq_ss(m_real, a.m_real);
}

HK_FORCE_INLINE hkBool32 hkSimdFloat32::isLessZero() const
{
	return _mm_ucomilt_ss(m_real, _mm_setzero_ps());
}

HK_FORCE_INLINE hkBool32 hkSimdFloat32::isLessEqualZero() const
{
	return _mm_ucomile_ss(m_real, _mm_setzero_ps());
}

HK_FORCE_INLINE hkBool32 hkSimdFloat32::isGreaterZero() const
{
	return _mm_ucomigt_ss(m_real, _mm_setzero_ps());
}

HK_FORCE_INLINE hkBool32 hkSimdFloat32::isGreaterEqualZero() const
{
	return _mm_ucomige_ss(m_real, _mm_setzero_ps());
}

HK_FORCE_INLINE hkBool32 hkSimdFloat32::isEqualZero() const
{
	return _mm_ucomieq_ss(m_real, _mm_setzero_ps());
}

HK_FORCE_INLINE hkBool32 hkSimdFloat32::isNotEqualZero() const
{
	return _mm_ucomineq_ss(m_real, _mm_setzero_ps());
}

HK_FORCE_INLINE hkBool32 hkSimdFloat32::isOk() const
{
	const hkSingleFloat32 nanMask = _mm_cmpord_ps(m_real, _mm_setzero_ps());
	return _mm_movemask_ps(nanMask);
}

HK_FORCE_INLINE void hkSimdFloat32::setSelect( hkVector4fComparisonParameter comp, hkSimdFloat32Parameter trueValue, hkSimdFloat32Parameter falseValue )
{
	HK_MATH_ASSERT(0xc78f08e, comp.allAreSet() || (comp.getMask() == hkVector4ComparisonMask::MASK_NONE), "illegal compare mask");
#if HK_SSE_VERSION >= 0x41
	m_real = _mm_blendv_ps(falseValue.m_real, trueValue.m_real, comp.m_mask);
#else
	m_real = _mm_or_ps( _mm_and_ps(comp.m_mask, trueValue.m_real), _mm_andnot_ps(comp.m_mask, falseValue.m_real) );
#endif
}

HK_FORCE_INLINE void hkSimdFloat32::zeroIfFalse( hkVector4fComparisonParameter comp )
{
	HK_MATH_ASSERT(0xc78f08e, comp.allAreSet() || (comp.getMask() == hkVector4ComparisonMask::MASK_NONE), "illegal compare mask");
	m_real = _mm_and_ps(comp.m_mask, m_real);
}

HK_FORCE_INLINE void hkSimdFloat32::zeroIfTrue( hkVector4fComparisonParameter comp )
{
	HK_MATH_ASSERT(0xc78f08e, comp.allAreSet() || (comp.getMask() == hkVector4ComparisonMask::MASK_NONE), "illegal compare mask");
	m_real = _mm_andnot_ps(comp.m_mask, m_real);
}

HK_FORCE_INLINE void hkSimdFloat32::setMin(  hkSimdFloat32Parameter a, hkSimdFloat32Parameter b ) 
{
	m_real = _mm_min_ps( a.m_real, b.m_real );
}

HK_FORCE_INLINE void hkSimdFloat32::setMax(  hkSimdFloat32Parameter a, hkSimdFloat32Parameter b ) 
{
	m_real = _mm_max_ps( a.m_real, b.m_real );
}

HK_FORCE_INLINE void hkSimdFloat32::setAbs(  hkSimdFloat32Parameter a )
{
	m_real = hkMath::quadFabs(a.m_real);
}

HK_FORCE_INLINE void hkSimdFloat32::setFloor(  hkSimdFloat32Parameter a )
{
	m_real = hkMath::quadFloor(a.m_real);
}

HK_FORCE_INLINE void hkSimdFloat32::setMod(  hkSimdFloat32Parameter a, hkSimdFloat32Parameter b )
{
	m_real = hkMath::quadMod(a.m_real,b.m_real);
}

HK_FORCE_INLINE void hkSimdFloat32::setFlipSign(hkSimdFloat32Parameter v, hkSimdFloat32Parameter sSign)
{
	const __m128i mask = _mm_slli_epi32(_mm_srli_epi32(_mm_castps_si128(sSign.m_real),31),31);
	m_real = _mm_xor_ps(v.m_real, _mm_castsi128_ps(mask));
}

HK_FORCE_INLINE void hkSimdFloat32::setFlipSign(hkSimdFloat32Parameter v, hkVector4fComparisonParameter mask)
{
	HK_MATH_ASSERT(0x5831c04, mask.allAreSet() || (mask.getMask() == hkVector4ComparisonMask::MASK_NONE), "illegal compare mask");
	const __m128i maskS = _mm_slli_epi32(_mm_srli_epi32(_mm_castps_si128(mask.m_mask),31),31);
	m_real = _mm_xor_ps(v.m_real, _mm_castsi128_ps(maskS));
}





//
// advanced interface
//

namespace hkSimdReal_AdvancedInterface
{

template <hkMathAccuracyMode A, hkMathDivByZeroMode D>
struct unrollf_setReciprocal { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, hkSimdFloat32Parameter a)
{
	HK_SIMDFLOAT_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <hkMathAccuracyMode A>
struct unrollf_setReciprocal<A, HK_DIV_IGNORE> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, hkSimdFloat32Parameter a)
{
	switch (A)
	{
		case HK_ACC_23_BIT: self = hkMath::quadReciprocal(a.m_real); break;
		case HK_ACC_12_BIT: self = _mm_rcp_ps(a.m_real); break;
		default:         self = _mm_div_ps(g_vectorfConstants[HK_QUADREAL_1],a.m_real); break; // HK_ACC_FULL
	}
} };
template <hkMathAccuracyMode A>
struct unrollf_setReciprocal<A, HK_DIV_SET_ZERO> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, hkSimdFloat32Parameter a)
{
	const hkSingleFloat32 equalsZero = _mm_cmpeq_ps(a.m_real, _mm_setzero_ps());
	hkSingleFloat32 e; unrollf_setReciprocal<A, HK_DIV_IGNORE>::apply(e, a);
	self = _mm_andnot_ps(equalsZero, e);
} };
template <hkMathAccuracyMode A>
struct unrollf_setReciprocal<A, HK_DIV_SET_HIGH> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, hkSimdFloat32Parameter a)
{
	const hkSingleFloat32 equalsZero = _mm_cmpeq_ps(a.m_real, _mm_setzero_ps());
	hkSingleFloat32 e; unrollf_setReciprocal<A, HK_DIV_IGNORE>::apply(e, a);
	hkSingleFloat32 huge = _mm_set1_ps(HK_FLOAT_HIGH);
	const __m128i mask = _mm_slli_epi32(_mm_srli_epi32(_mm_castps_si128(a.m_real),31),31);
	huge = _mm_xor_ps(huge, _mm_castsi128_ps(mask));
#if HK_SSE_VERSION >= 0x41
	self = _mm_blendv_ps(e, huge, equalsZero);
#else
	self = _mm_or_ps( _mm_and_ps(equalsZero, huge), _mm_andnot_ps(equalsZero, e) );
#endif
} };
template <hkMathAccuracyMode A>
struct unrollf_setReciprocal<A, HK_DIV_SET_MAX> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, hkSimdFloat32Parameter a)
{
	const hkSingleFloat32 equalsZero = _mm_cmpeq_ps(a.m_real, _mm_setzero_ps());
	hkSingleFloat32 e; unrollf_setReciprocal<A, HK_DIV_IGNORE>::apply(e, a);
	hkSingleFloat32 huge = _mm_set1_ps(HK_FLOAT_MAX);
	const __m128i mask = _mm_slli_epi32(_mm_srli_epi32(_mm_castps_si128(a.m_real),31),31);
	huge = _mm_xor_ps(huge, _mm_castsi128_ps(mask));
#if HK_SSE_VERSION >= 0x41
	self = _mm_blendv_ps(e, huge, equalsZero);
#else
	self = _mm_or_ps( _mm_and_ps(equalsZero, huge), _mm_andnot_ps(equalsZero, e) );
#endif
} };
template <hkMathAccuracyMode A>
struct unrollf_setReciprocal<A, HK_DIV_SET_ZERO_AND_ONE> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, hkSimdFloat32Parameter a)
{
	unrollf_setReciprocal<A, HK_DIV_SET_ZERO>::apply(self, a);
	const hkSingleFloat32 one = g_vectorfConstants[HK_QUADREAL_1];
	const hkSingleFloat32 absVal = hkMath::quadFabs(_mm_sub_ps(self, one));
	const hkSingleFloat32 lessEqualEps = _mm_cmple_ps(absVal, g_vectorfConstants[HK_QUADREAL_EPS]);
#if HK_SSE_VERSION >= 0x41
	self = _mm_blendv_ps(self, one, lessEqualEps);
#else
	self = _mm_or_ps( _mm_and_ps(lessEqualEps, one), _mm_andnot_ps(lessEqualEps, self) );
#endif
} };

} // namespace 

template <hkMathAccuracyMode A, hkMathDivByZeroMode D> 
HK_FORCE_INLINE void hkSimdFloat32::setReciprocal(hkSimdFloat32Parameter a)
{
	hkSimdReal_AdvancedInterface::unrollf_setReciprocal<A,D>::apply(m_real,a);
}

HK_FORCE_INLINE void hkSimdFloat32::setReciprocal(hkSimdFloat32Parameter a)
{
	hkSimdReal_AdvancedInterface::unrollf_setReciprocal<HK_ACC_23_BIT,HK_DIV_IGNORE>::apply(m_real,a);
}

namespace hkSimdReal_AdvancedInterface
{

template <hkMathAccuracyMode A, hkMathDivByZeroMode D>
struct unrollf_setDiv { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, hkSimdFloat32Parameter a, hkSimdFloat32Parameter b)
{
	HK_SIMDFLOAT_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <hkMathAccuracyMode A>
struct unrollf_setDiv<A, HK_DIV_IGNORE> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, hkSimdFloat32Parameter a, hkSimdFloat32Parameter b)
{
	switch (A)
	{
		case HK_ACC_23_BIT: self = _mm_mul_ps(a.m_real, hkMath::quadReciprocal(b.m_real)); break;
		case HK_ACC_12_BIT: self = _mm_mul_ps(a.m_real, _mm_rcp_ps(b.m_real)); break;
		default:			self = _mm_div_ps(a.m_real, b.m_real); break; // HK_ACC_FULL
	}
} };
template <hkMathAccuracyMode A>
struct unrollf_setDiv<A, HK_DIV_SET_ZERO> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, hkSimdFloat32Parameter a, hkSimdFloat32Parameter b)
{
	const hkSingleFloat32 equalsZero = _mm_cmpeq_ps(b.m_real, _mm_setzero_ps());
	hkSingleFloat32 e; unrollf_setDiv<A, HK_DIV_IGNORE>::apply(e, a, b);
	self = _mm_andnot_ps(equalsZero, e);
} };
template <hkMathAccuracyMode A>
struct unrollf_setDiv<A, HK_DIV_SET_HIGH> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, hkSimdFloat32Parameter a, hkSimdFloat32Parameter b)
{
	const hkSingleFloat32 equalsZero = _mm_cmpeq_ps(b.m_real, _mm_setzero_ps());
	hkSingleFloat32 e; unrollf_setDiv<A, HK_DIV_IGNORE>::apply(e, a, b);
	hkSingleFloat32 huge = _mm_set1_ps(HK_FLOAT_HIGH);
	const __m128i mask = _mm_slli_epi32(_mm_srli_epi32(_mm_castps_si128(a.m_real),31),31);
	huge = _mm_xor_ps(huge, _mm_castsi128_ps(mask));
#if HK_SSE_VERSION >= 0x41
	self = _mm_blendv_ps(e, huge, equalsZero);
#else
	self = _mm_or_ps( _mm_and_ps(equalsZero, huge), _mm_andnot_ps(equalsZero, e) );
#endif
} };
template <hkMathAccuracyMode A>
struct unrollf_setDiv<A, HK_DIV_SET_MAX> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, hkSimdFloat32Parameter a, hkSimdFloat32Parameter b)
{
	const hkSingleFloat32 equalsZero = _mm_cmpeq_ps(b.m_real, _mm_setzero_ps());
	hkSingleFloat32 e; unrollf_setDiv<A, HK_DIV_IGNORE>::apply(e, a, b);
	hkSingleFloat32 huge = _mm_set1_ps(HK_FLOAT_MAX);
	const __m128i mask = _mm_slli_epi32(_mm_srli_epi32(_mm_castps_si128(a.m_real),31),31);
	huge = _mm_xor_ps(huge, _mm_castsi128_ps(mask));
#if HK_SSE_VERSION >= 0x41
	self = _mm_blendv_ps(e, huge, equalsZero);
#else
	self = _mm_or_ps( _mm_and_ps(equalsZero, huge), _mm_andnot_ps(equalsZero, e) );
#endif
} };
template <hkMathAccuracyMode A>
struct unrollf_setDiv<A, HK_DIV_SET_ZERO_AND_ONE> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, hkSimdFloat32Parameter a, hkSimdFloat32Parameter b)
{
	unrollf_setDiv<A, HK_DIV_SET_ZERO>::apply(self, a, b);
	const hkSingleFloat32 one = g_vectorfConstants[HK_QUADREAL_1];
	const hkSingleFloat32 absVal = hkMath::quadFabs(_mm_sub_ps(self, one));
	const hkSingleFloat32 lessEqualEps = _mm_cmple_ps(absVal, g_vectorfConstants[HK_QUADREAL_EPS]);
#if HK_SSE_VERSION >= 0x41
	self = _mm_blendv_ps(self, one, lessEqualEps);
#else
	self = _mm_or_ps( _mm_and_ps(lessEqualEps, one), _mm_andnot_ps(lessEqualEps, self) );
#endif
} };

} // namespace 

template <hkMathAccuracyMode A, hkMathDivByZeroMode D> 
HK_FORCE_INLINE void hkSimdFloat32::setDiv(hkSimdFloat32Parameter a, hkSimdFloat32Parameter b)
{
	hkSimdReal_AdvancedInterface::unrollf_setDiv<A,D>::apply(m_real,a,b);
}

HK_FORCE_INLINE void hkSimdFloat32::setDiv(hkSimdFloat32Parameter a, hkSimdFloat32Parameter b)
{
	hkSimdReal_AdvancedInterface::unrollf_setDiv<HK_ACC_23_BIT,HK_DIV_IGNORE>::apply(m_real,a,b);
}

template <hkMathAccuracyMode A, hkMathDivByZeroMode D> 
HK_FORCE_INLINE void hkSimdFloat32::div(hkSimdFloat32Parameter a)
{
	setDiv<A,D>( *this, a );
}

HK_FORCE_INLINE void hkSimdFloat32::div(hkSimdFloat32Parameter a)
{
	setDiv( *this, a );
}

HK_FORCE_INLINE const hkSimdFloat32 hkSimdFloat32::operator/ (hkSimdFloat32Parameter r) const
{
	hkSimdFloat32 q;
	q.setDiv(*this,r);
	return q;
}


namespace hkSimdReal_AdvancedInterface
{

template <hkMathAccuracyMode A, hkMathNegSqrtMode S>
struct unrollf_sqrt { HK_FORCE_INLINE static hkSingleFloat32 apply(hkSimdFloat32Parameter self)
{
	HK_SIMDFLOAT_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
	return _mm_setzero_ps();
} };
template <hkMathAccuracyMode A>
struct unrollf_sqrt<A, HK_SQRT_IGNORE> { HK_FORCE_INLINE static hkSingleFloat32 apply(hkSimdFloat32Parameter self)
{
	switch (A)
	{
		case HK_ACC_23_BIT: return _mm_mul_ps(self.m_real,hkMath::quadReciprocalSquareRoot(self.m_real)); break;
		case HK_ACC_12_BIT: return _mm_mul_ps(self.m_real,_mm_rsqrt_ps(self.m_real)); break;
		default:         return _mm_sqrt_ps(self.m_real); break; // HK_ACC_FULL
	}
} };
template <hkMathAccuracyMode A>
struct unrollf_sqrt<A, HK_SQRT_SET_ZERO> { HK_FORCE_INLINE static hkSingleFloat32 apply(hkSimdFloat32Parameter self)
{
	const hkSingleFloat32 equalsZero = _mm_cmple_ps(self.m_real, _mm_setzero_ps());
	const hkSingleFloat32 e = unrollf_sqrt<A, HK_SQRT_IGNORE>::apply(self);
	return _mm_andnot_ps(equalsZero, e);
} };

} // namespace 

template <hkMathAccuracyMode A, hkMathNegSqrtMode S> 
HK_FORCE_INLINE const hkSimdFloat32 hkSimdFloat32::sqrt() const
{
	return hkSimdFloat32::convert(hkSimdReal_AdvancedInterface::unrollf_sqrt<A,S>::apply(*this));
}

HK_FORCE_INLINE const hkSimdFloat32 hkSimdFloat32::sqrt() const
{
	return hkSimdFloat32::convert(hkSimdReal_AdvancedInterface::unrollf_sqrt<HK_ACC_23_BIT,HK_SQRT_SET_ZERO>::apply(*this));
}



namespace hkSimdReal_AdvancedInterface
{

template <hkMathAccuracyMode A, hkMathNegSqrtMode S>
struct unrollf_sqrtInverse { HK_FORCE_INLINE static hkSingleFloat32 apply(hkSimdFloat32Parameter self)
{
	HK_SIMDFLOAT_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
	return _mm_setzero_ps();
} };
template <hkMathAccuracyMode A>
struct unrollf_sqrtInverse<A, HK_SQRT_IGNORE> { HK_FORCE_INLINE static hkSingleFloat32 apply(hkSimdFloat32Parameter self)
{
	switch (A)
	{
		case HK_ACC_23_BIT: return hkMath::quadReciprocalSquareRoot(self.m_real); break;
		case HK_ACC_12_BIT: return _mm_rsqrt_ps(self.m_real); break;
		default:			return _mm_div_ps(g_vectorfConstants[HK_QUADREAL_1], _mm_sqrt_ps(self.m_real)); break; // HK_ACC_FULL
	}
} };
template <hkMathAccuracyMode A>
struct unrollf_sqrtInverse<A, HK_SQRT_SET_ZERO> { HK_FORCE_INLINE static hkSingleFloat32 apply(hkSimdFloat32Parameter self)
{
	const hkSingleFloat32 equalsZero = _mm_cmple_ps(self.m_real, _mm_setzero_ps());
	const hkSingleFloat32 e = unrollf_sqrtInverse<A, HK_SQRT_IGNORE>::apply(self);
	return _mm_andnot_ps(equalsZero, e);
} };
} // namespace 

template <hkMathAccuracyMode A, hkMathNegSqrtMode S> 
HK_FORCE_INLINE const hkSimdFloat32 hkSimdFloat32::sqrtInverse() const
{
	return hkSimdFloat32::convert(hkSimdReal_AdvancedInterface::unrollf_sqrtInverse<A,S>::apply(*this));
}

HK_FORCE_INLINE const hkSimdFloat32 hkSimdFloat32::sqrtInverse() const
{
	return hkSimdFloat32::convert(hkSimdReal_AdvancedInterface::unrollf_sqrtInverse<HK_ACC_23_BIT,HK_SQRT_SET_ZERO>::apply(*this));
}



namespace hkSimdReal_AdvancedInterface
{
template <hkMathIoMode A>
struct unrollf_load { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, const hkFloat32* HK_RESTRICT p)
{
	HK_SIMDFLOAT_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <hkMathIoMode A>
struct unrollf_load_D { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, const hkDouble64* HK_RESTRICT p)
{
	HK_SIMDFLOAT_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <>
struct unrollf_load<HK_IO_BYTE_ALIGNED> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, const hkFloat32* HK_RESTRICT p)
{
	self = _mm_load1_ps(p);
} };
template <>
struct unrollf_load_D<HK_IO_BYTE_ALIGNED> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, const hkDouble64* HK_RESTRICT p)
{
	__m128d a = _mm_load_sd(p);
	__m128 f = _mm_cvtpd_ps(a);
	self = _mm_shuffle_ps(f,f,_MM_SHUFFLE(0,0,0,0));
} };
template <>
struct unrollf_load<HK_IO_NATIVE_ALIGNED> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, const hkFloat32* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & (sizeof(hkFloat32)-1) ) == 0, "pointer must be aligned to native size of hkFloat32.");
	unrollf_load<HK_IO_BYTE_ALIGNED>::apply(self,p);
} };
template <>
struct unrollf_load_D<HK_IO_NATIVE_ALIGNED> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, const hkDouble64* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & (sizeof(hkDouble64)-1) ) == 0, "pointer must be aligned to native size of hkDouble64.");
	unrollf_load_D<HK_IO_BYTE_ALIGNED>::apply(self,p);
} };
template <>
struct unrollf_load<HK_IO_SIMD_ALIGNED> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, const hkFloat32* HK_RESTRICT p)
{
	unrollf_load<HK_IO_NATIVE_ALIGNED>::apply(self,p);
} };
template <>
struct unrollf_load_D<HK_IO_SIMD_ALIGNED> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, const hkDouble64* HK_RESTRICT p)
{
	unrollf_load_D<HK_IO_NATIVE_ALIGNED>::apply(self,p);
} };
template <>
struct unrollf_load<HK_IO_NOT_CACHED> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, const hkFloat32* HK_RESTRICT p)
{
	unrollf_load<HK_IO_SIMD_ALIGNED>::apply(self,p);
} };
template <>
struct unrollf_load_D<HK_IO_NOT_CACHED> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, const hkDouble64* HK_RESTRICT p)
{
	unrollf_load_D<HK_IO_SIMD_ALIGNED>::apply(self,p);
} };
} // namespace 

template <int N, hkMathIoMode A>
HK_FORCE_INLINE void hkSimdFloat32::load(const hkFloat32 *p )
{
	HK_SIMDFLOAT_DIMENSION_CHECK;
	hkSimdReal_AdvancedInterface::unrollf_load<A>::apply(m_real, p);
}

template <int N, hkMathIoMode A>
HK_FORCE_INLINE void hkSimdFloat32::load(const hkDouble64 *p )
{
	HK_SIMDFLOAT_DIMENSION_CHECK;
	hkSimdReal_AdvancedInterface::unrollf_load_D<A>::apply(m_real, p);
}

template <int N>
HK_FORCE_INLINE void hkSimdFloat32::load(const hkFloat32 *p )
{
	HK_SIMDFLOAT_DIMENSION_CHECK;
	hkSimdReal_AdvancedInterface::unrollf_load<HK_IO_SIMD_ALIGNED>::apply(m_real, p);
}

template <int N>
HK_FORCE_INLINE void hkSimdFloat32::load(const hkDouble64 *p )
{
	HK_SIMDFLOAT_DIMENSION_CHECK;
	hkSimdReal_AdvancedInterface::unrollf_load_D<HK_IO_SIMD_ALIGNED>::apply(m_real, p);
}




namespace hkSimdReal_AdvancedInterface
{
template <hkMathIoMode A>
struct unrollf_loadH { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, const hkHalf* HK_RESTRICT p)
{
	HK_SIMDFLOAT_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <>
struct unrollf_loadH<HK_IO_BYTE_ALIGNED> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, const hkHalf* HK_RESTRICT p)
{
#if defined(HK_HALF_IS_FLOAT)
	self = _mm_load1_ps((const float*)p);
#else
	float x; p[0].store(&x);
	self = _mm_set1_ps(x);
#endif
} };
template <>
struct unrollf_loadH<HK_IO_NATIVE_ALIGNED> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, const hkHalf* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & (sizeof(hkHalf)-1) ) == 0, "pointer must be aligned to native size of hkHalf.");
	unrollf_loadH<HK_IO_BYTE_ALIGNED>::apply(self,p);
} };
template <>
struct unrollf_loadH<HK_IO_SIMD_ALIGNED> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, const hkHalf* HK_RESTRICT p)
{
	unrollf_loadH<HK_IO_NATIVE_ALIGNED>::apply(self,p);
} };
template <>
struct unrollf_loadH<HK_IO_NOT_CACHED> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, const hkHalf* HK_RESTRICT p)
{
	unrollf_loadH<HK_IO_SIMD_ALIGNED>::apply(self,p);
} };
} // namespace 

template <int N, hkMathIoMode A>
HK_FORCE_INLINE void hkSimdFloat32::load(const hkHalf *p )
{
	HK_SIMDFLOAT_DIMENSION_CHECK;
	hkSimdReal_AdvancedInterface::unrollf_loadH<A>::apply(m_real, p);
}

template <int N>
HK_FORCE_INLINE void hkSimdFloat32::load(const hkHalf *p )
{
	HK_SIMDFLOAT_DIMENSION_CHECK;
	hkSimdReal_AdvancedInterface::unrollf_loadH<HK_IO_SIMD_ALIGNED>::apply(m_real, p);
}




namespace hkSimdReal_AdvancedInterface
{
template <hkMathIoMode A>
struct unrollf_loadF16 { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, const hkFloat16* HK_RESTRICT p)
{
	HK_SIMDFLOAT_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <>
struct unrollf_loadF16<HK_IO_BYTE_ALIGNED> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, const hkFloat16* HK_RESTRICT p)
{
	hkFloat32 tmp = p[0].getFloat32();
	self = _mm_load1_ps((const float*)&tmp);
} };
template <>
struct unrollf_loadF16<HK_IO_NATIVE_ALIGNED> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, const hkFloat16* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & (sizeof(hkFloat16)-1) ) == 0, "pointer must be aligned to native size of hkFloat16.");
	unrollf_loadF16<HK_IO_BYTE_ALIGNED>::apply(self,p);
} };
template <>
struct unrollf_loadF16<HK_IO_SIMD_ALIGNED> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, const hkFloat16* HK_RESTRICT p)
{
	unrollf_loadF16<HK_IO_NATIVE_ALIGNED>::apply(self,p);
} };
template <>
struct unrollf_loadF16<HK_IO_NOT_CACHED> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, const hkFloat16* HK_RESTRICT p)
{
	unrollf_loadF16<HK_IO_SIMD_ALIGNED>::apply(self,p);
} };
} // namespace 

template <int N, hkMathIoMode A>
HK_FORCE_INLINE void hkSimdFloat32::load(const hkFloat16 *p )
{
	HK_SIMDFLOAT_DIMENSION_CHECK;
	hkSimdReal_AdvancedInterface::unrollf_loadF16<A>::apply(m_real, p);
}

template <int N>
HK_FORCE_INLINE void hkSimdFloat32::load(const hkFloat16 *p )
{
	HK_SIMDFLOAT_DIMENSION_CHECK;
	hkSimdReal_AdvancedInterface::unrollf_loadF16<HK_IO_SIMD_ALIGNED>::apply(m_real, p);
}



namespace hkSimdReal_AdvancedInterface
{
template <hkMathIoMode A>
struct unrollf_store { HK_FORCE_INLINE static void apply(const hkSingleFloat32& self, hkFloat32* HK_RESTRICT p)
{
	HK_SIMDFLOAT_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <hkMathIoMode A>
struct unrollf_store_D { HK_FORCE_INLINE static void apply(const hkSingleFloat32& self, hkDouble64* HK_RESTRICT p)
{
	HK_SIMDFLOAT_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <>
struct unrollf_store<HK_IO_BYTE_ALIGNED> { HK_FORCE_INLINE static void apply(const hkSingleFloat32& self, hkFloat32* HK_RESTRICT p)
{
	_mm_store_ss( p, self );
} };
template <>
struct unrollf_store_D<HK_IO_BYTE_ALIGNED> { HK_FORCE_INLINE static void apply(const hkSingleFloat32& self, hkDouble64* HK_RESTRICT p)
{
	__m128d d = _mm_cvtps_pd(self);
	_mm_store_sd( p, d );
} };
template <>
struct unrollf_store<HK_IO_NATIVE_ALIGNED> { HK_FORCE_INLINE static void apply(const hkSingleFloat32& self, hkFloat32* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & (sizeof(hkFloat32)-1) ) == 0, "pointer must be aligned to native size of hkFloat32.");
	unrollf_store<HK_IO_BYTE_ALIGNED>::apply(self,p);
} };
template <>
struct unrollf_store_D<HK_IO_NATIVE_ALIGNED> { HK_FORCE_INLINE static void apply(const hkSingleFloat32& self, hkDouble64* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & (sizeof(hkDouble64)-1) ) == 0, "pointer must be aligned to native size of hkDouble64.");
	unrollf_store_D<HK_IO_BYTE_ALIGNED>::apply(self,p);
} };
template <>
struct unrollf_store<HK_IO_SIMD_ALIGNED> { HK_FORCE_INLINE static void apply(const hkSingleFloat32& self, hkFloat32* HK_RESTRICT p)
{
	unrollf_store<HK_IO_NATIVE_ALIGNED>::apply(self,p);
} };
template <>
struct unrollf_store_D<HK_IO_SIMD_ALIGNED> { HK_FORCE_INLINE static void apply(const hkSingleFloat32& self, hkDouble64* HK_RESTRICT p)
{
	unrollf_store_D<HK_IO_NATIVE_ALIGNED>::apply(self,p);
} };
template <>
struct unrollf_store<HK_IO_NOT_CACHED> { HK_FORCE_INLINE static void apply(const hkSingleFloat32& self, hkFloat32* HK_RESTRICT p)
{
	unrollf_store<HK_IO_SIMD_ALIGNED>::apply(self,p);
} };
template <>
struct unrollf_store_D<HK_IO_NOT_CACHED> { HK_FORCE_INLINE static void apply(const hkSingleFloat32& self, hkDouble64* HK_RESTRICT p)
{
	unrollf_store_D<HK_IO_SIMD_ALIGNED>::apply(self,p);
} };
} // namespace 

template <int N, hkMathIoMode A, hkMathRoundingMode R>
HK_FORCE_INLINE void hkSimdFloat32::store(  hkFloat32 *p ) const
{
	HK_SIMDFLOAT_DIMENSION_CHECK;
	hkSimdReal_AdvancedInterface::unrollf_store<A>::apply(m_real, p);
}

template <int N, hkMathIoMode A, hkMathRoundingMode R>
HK_FORCE_INLINE void hkSimdFloat32::store(  hkDouble64 *p ) const
{
	HK_SIMDFLOAT_DIMENSION_CHECK;
	hkSimdReal_AdvancedInterface::unrollf_store_D<A>::apply(m_real, p);
}

template <int N, hkMathIoMode A>
HK_FORCE_INLINE void hkSimdFloat32::store(  hkFloat32 *p ) const
{
	HK_SIMDFLOAT_DIMENSION_CHECK;
	hkSimdReal_AdvancedInterface::unrollf_store<A>::apply(m_real, p);
}

template <int N, hkMathIoMode A>
HK_FORCE_INLINE void hkSimdFloat32::store(  hkDouble64 *p ) const
{
	HK_SIMDFLOAT_DIMENSION_CHECK;
	hkSimdReal_AdvancedInterface::unrollf_store_D<A>::apply(m_real, p);
}

template <int N>
HK_FORCE_INLINE void hkSimdFloat32::store(  hkFloat32 *p ) const
{
	HK_SIMDFLOAT_DIMENSION_CHECK;
	hkSimdReal_AdvancedInterface::unrollf_store<HK_IO_SIMD_ALIGNED>::apply(m_real, p);
}

template <int N>
HK_FORCE_INLINE void hkSimdFloat32::store(  hkDouble64 *p ) const
{
	HK_SIMDFLOAT_DIMENSION_CHECK;
	hkSimdReal_AdvancedInterface::unrollf_store_D<HK_IO_SIMD_ALIGNED>::apply(m_real, p);
}




namespace hkSimdReal_AdvancedInterface
{
template <hkMathIoMode A, hkMathRoundingMode R>
struct unrollf_storeH { HK_FORCE_INLINE static void apply(const hkSingleFloat32& self, hkHalf* HK_RESTRICT p)
{
	HK_SIMDFLOAT_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <hkMathRoundingMode R>
struct unrollf_storeH<HK_IO_BYTE_ALIGNED,R> { HK_FORCE_INLINE static void apply(const hkSingleFloat32& self, hkHalf* HK_RESTRICT p)
{
#if defined(HK_HALF_IS_FLOAT)
	_mm_store_ss((float*)p, self);
#else
	__m128  vs0;
	if (R == HK_ROUND_NEAREST)
		vs0 = _mm_mul_ps( self, g_vectorfConstants[HK_QUADREAL_PACK_HALF] );
	else
		vs0 = self;
	__m128i tmp0 = _mm_srai_epi32( _mm_castps_si128(vs0), 16 );
	__m128i tmp1 = _mm_packs_epi32(tmp0, tmp0);
	float ftmp1; _mm_store_ss(&ftmp1, _mm_castsi128_ps(tmp1));
	const hkHalf* HK_RESTRICT htmp1 = (const hkHalf* HK_RESTRICT)&ftmp1;
	p[0] = htmp1[0];
#endif
} };
template <hkMathRoundingMode R>
struct unrollf_storeH<HK_IO_NATIVE_ALIGNED,R> { HK_FORCE_INLINE static void apply(const hkSingleFloat32& self, hkHalf* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & (sizeof(hkHalf)-1) ) == 0, "pointer must be aligned to native size of hkHalf.");
	unrollf_storeH<HK_IO_BYTE_ALIGNED,R>::apply(self,p);
} };
template <hkMathRoundingMode R>
struct unrollf_storeH<HK_IO_SIMD_ALIGNED,R> { HK_FORCE_INLINE static void apply(const hkSingleFloat32& self, hkHalf* HK_RESTRICT p)
{
	unrollf_storeH<HK_IO_NATIVE_ALIGNED,R>::apply(self,p);
} };
template <hkMathRoundingMode R>
struct unrollf_storeH<HK_IO_NOT_CACHED,R> { HK_FORCE_INLINE static void apply(const hkSingleFloat32& self, hkHalf* HK_RESTRICT p)
{
	unrollf_storeH<HK_IO_SIMD_ALIGNED,R>::apply(self,p);
} };
} // namespace 

template <int N, hkMathIoMode A, hkMathRoundingMode R>
HK_FORCE_INLINE void hkSimdFloat32::store(  hkHalf *p ) const
{
	HK_SIMDFLOAT_DIMENSION_CHECK;
	hkSimdReal_AdvancedInterface::unrollf_storeH<A,R>::apply(m_real, p);
}

template <int N>
HK_FORCE_INLINE void hkSimdFloat32::store(  hkHalf *p ) const
{
	HK_SIMDFLOAT_DIMENSION_CHECK;
	hkSimdReal_AdvancedInterface::unrollf_storeH<HK_IO_SIMD_ALIGNED,HK_ROUND_DEFAULT>::apply(m_real, p);
}




namespace hkSimdReal_AdvancedInterface
{
template <hkMathIoMode A, hkMathRoundingMode R>
struct unrollf_storeF16 { HK_FORCE_INLINE static void apply(const hkSingleFloat32& self, hkFloat16* HK_RESTRICT p)
{
	HK_SIMDFLOAT_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <hkMathRoundingMode R>
struct unrollf_storeF16<HK_IO_BYTE_ALIGNED,R> { HK_FORCE_INLINE static void apply(const hkSingleFloat32& self, hkFloat16* HK_RESTRICT p)
{
	hkFloat32 tmp;
	_mm_store_ss(&tmp, self);
	p[0].setReal<(R == HK_ROUND_NEAREST)>(tmp);
} };
template <hkMathRoundingMode R>
struct unrollf_storeF16<HK_IO_NATIVE_ALIGNED,R> { HK_FORCE_INLINE static void apply(const hkSingleFloat32& self, hkFloat16* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & (sizeof(hkFloat16)-1) ) == 0, "pointer must be aligned to native size of hkFloat16.");
	unrollf_storeF16<HK_IO_BYTE_ALIGNED,R>::apply(self,p);
} };
template <hkMathRoundingMode R>
struct unrollf_storeF16<HK_IO_SIMD_ALIGNED,R> { HK_FORCE_INLINE static void apply(const hkSingleFloat32& self, hkFloat16* HK_RESTRICT p)
{
	unrollf_storeF16<HK_IO_NATIVE_ALIGNED,R>::apply(self,p);
} };
template <hkMathRoundingMode R>
struct unrollf_storeF16<HK_IO_NOT_CACHED,R> { HK_FORCE_INLINE static void apply(const hkSingleFloat32& self, hkFloat16* HK_RESTRICT p)
{
	unrollf_storeF16<HK_IO_SIMD_ALIGNED,R>::apply(self,p);
} };
} // namespace 

template <int N, hkMathIoMode A, hkMathRoundingMode R>
HK_FORCE_INLINE void hkSimdFloat32::store(  hkFloat16 *p ) const
{
	HK_SIMDFLOAT_DIMENSION_CHECK;
	hkSimdReal_AdvancedInterface::unrollf_storeF16<A,R>::apply(m_real, p);
}

template <int N>
HK_FORCE_INLINE void hkSimdFloat32::store(  hkFloat16 *p ) const
{
	HK_SIMDFLOAT_DIMENSION_CHECK;
	hkSimdReal_AdvancedInterface::unrollf_storeF16<HK_IO_SIMD_ALIGNED,HK_ROUND_DEFAULT>::apply(m_real, p);
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
