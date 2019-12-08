/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */


// Gcc 4.5.1 can mis-optimise _mm_move_sd
#if defined(HK_COMPILER_GCC) && (HK_COMPILER_GCC_VERSION <= 40501)
#define MOVE_SD(a, b) _mm_shuffle_pd(b, a, _MM_SHUFFLE2(1, 0))
#else
#define MOVE_SD(a, b) _mm_move_sd(a, b)
#endif

#ifndef HK_DISABLE_MATH_CONSTRUCTORS
/* construct, assign, zero */
HK_FORCE_INLINE hkVector4d::hkVector4d(hkDouble64 a, hkDouble64 b, hkDouble64 c, hkDouble64 d)
{
	m_quad.xy = _mm_setr_pd(a,b);
	m_quad.zw = _mm_setr_pd(c,d);
}

HK_FORCE_INLINE hkVector4d::hkVector4d(const hkQuadDouble64& q)
{
	m_quad = q;
}

HK_FORCE_INLINE hkVector4d::hkVector4d(const hkVector4d& v)
{
	m_quad = v.m_quad;
}
#endif

HK_FORCE_INLINE void hkVector4d::set(hkDouble64 a, hkDouble64 b, hkDouble64 c, hkDouble64 d)
{
	m_quad.xy = _mm_setr_pd(a,b);
	m_quad.zw = _mm_setr_pd(c,d);
}

HK_FORCE_INLINE void hkVector4d::set( hkSimdDouble64Parameter a, hkSimdDouble64Parameter b, hkSimdDouble64Parameter c, hkSimdDouble64Parameter d )
{
	m_quad.xy = _mm_unpacklo_pd(a.m_real, b.m_real);
	m_quad.zw = _mm_unpacklo_pd(c.m_real, d.m_real);
}

HK_FORCE_INLINE void hkVector4d::setAll(const hkDouble64& a)
{
#if HK_SSE_VERSION >= 0x30
	m_quad.xy = _mm_loaddup_pd(&a);
	m_quad.zw = _mm_loaddup_pd(&a);
#else
	m_quad.xy = _mm_load1_pd(&a);
	m_quad.zw = _mm_load1_pd(&a);
#endif
}

HK_FORCE_INLINE void hkVector4d::setAll(hkSimdDouble64Parameter a)
{
	m_quad.xy = a.m_real;
	m_quad.zw = a.m_real;
}

HK_FORCE_INLINE void hkVector4d::setZero()
{
	m_quad.xy = _mm_setzero_pd();
	m_quad.zw = _mm_setzero_pd();
}

template <> 
HK_FORCE_INLINE void hkVector4d::zeroComponent<0>()
{
	m_quad.xy = MOVE_SD(m_quad.xy, _mm_setzero_pd());
}

template <> 
HK_FORCE_INLINE void hkVector4d::zeroComponent<1>()
{
	m_quad.xy = MOVE_SD(_mm_setzero_pd(), m_quad.xy);
}

template <> 
HK_FORCE_INLINE void hkVector4d::zeroComponent<2>()
{
	m_quad.zw = MOVE_SD(m_quad.zw, _mm_setzero_pd());
}

template <> 
HK_FORCE_INLINE void hkVector4d::zeroComponent<3>()
{
	m_quad.zw = MOVE_SD(_mm_setzero_pd(), m_quad.zw);
}

template <int N> 
HK_FORCE_INLINE void hkVector4d::zeroComponent()
{
	HK_VECTOR4d_NOT_IMPLEMENTED;
}

HK_FORCE_INLINE void hkVector4d::zeroComponent(const int i)
{
	HK_MATH_ASSERT(0x3bc36625, (i>=0) && (i<4), "Component index out of range");
	switch (i)
	{
		case 3:  zeroComponent<3>(); break;
		case 2:  zeroComponent<2>(); break;
		case 1:  zeroComponent<1>(); break;
		default: zeroComponent<0>(); break;
	}
}

template <>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::getComponent<0>() const
{
	return hkSimdDouble64::convert(_mm_unpacklo_pd(m_quad.xy, m_quad.xy));
}

template <>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::getComponent<1>() const
{
	return hkSimdDouble64::convert(_mm_unpackhi_pd(m_quad.xy, m_quad.xy));
}

template <>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::getComponent<2>() const
{
	return hkSimdDouble64::convert(_mm_unpacklo_pd(m_quad.zw, m_quad.zw));
}

template <>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::getComponent<3>() const
{
	return hkSimdDouble64::convert(_mm_unpackhi_pd(m_quad.zw, m_quad.zw));
}

template <int N>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::getComponent() const
{
	HK_VECTOR4d_NOT_IMPLEMENTED;
	return hkSimdDouble64::getConstant<HK_QUADREAL_0>();
}

HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::getComponent(const int i) const
{
	HK_MATH_ASSERT(0x6d0c31d7, i>=0 && i<4, "index out of bounds for component access");
	switch (i)
	{
		case 1:  return getComponent<1>();
		case 2:  return getComponent<2>();
		case 3:  return getComponent<3>();
		default: return getComponent<0>();
	}
}

HK_FORCE_INLINE void hkVector4d::setAdd(hkVector4dParameter v0, hkVector4dParameter v1)
{
	m_quad.xy = _mm_add_pd(v0.m_quad.xy, v1.m_quad.xy);
	m_quad.zw = _mm_add_pd(v0.m_quad.zw, v1.m_quad.zw);
}

HK_FORCE_INLINE void hkVector4d::setSub(hkVector4dParameter v0, hkVector4dParameter v1)
{
	m_quad.xy = _mm_sub_pd(v0.m_quad.xy, v1.m_quad.xy);
	m_quad.zw = _mm_sub_pd(v0.m_quad.zw, v1.m_quad.zw);
}

HK_FORCE_INLINE void hkVector4d::setMul(hkVector4dParameter v0, hkVector4dParameter v1)
{
	m_quad.xy = _mm_mul_pd(v0.m_quad.xy, v1.m_quad.xy);
	m_quad.zw = _mm_mul_pd(v0.m_quad.zw, v1.m_quad.zw);
}

HK_FORCE_INLINE void hkVector4d::setMul(hkVector4dParameter v1, hkSimdDouble64Parameter r)
{
	m_quad.xy = _mm_mul_pd( r.m_real, v1.m_quad.xy);
	m_quad.zw = _mm_mul_pd( r.m_real, v1.m_quad.zw);
}

HK_FORCE_INLINE void hkVector4d::setSubMul(hkVector4dParameter a, hkVector4dParameter b, hkSimdDouble64Parameter r)
{
	m_quad.xy = _mm_sub_pd( a.m_quad.xy, _mm_mul_pd( r.m_real, b.m_quad.xy) );
	m_quad.zw = _mm_sub_pd( a.m_quad.zw, _mm_mul_pd( r.m_real, b.m_quad.zw) );
}

HK_FORCE_INLINE void hkVector4d::setAddMul(hkVector4dParameter a, hkVector4dParameter b, hkSimdDouble64Parameter r)
{
	m_quad.xy = _mm_add_pd( a.m_quad.xy, _mm_mul_pd( r.m_real, b.m_quad.xy) );
	m_quad.zw = _mm_add_pd( a.m_quad.zw, _mm_mul_pd( r.m_real, b.m_quad.zw) );
}

HK_FORCE_INLINE void hkVector4d::setAddMul(hkVector4dParameter a, hkVector4dParameter x, hkVector4dParameter y)
{
	m_quad.xy = _mm_add_pd( a.m_quad.xy, _mm_mul_pd( x.m_quad.xy, y.m_quad.xy) );
	m_quad.zw = _mm_add_pd( a.m_quad.zw, _mm_mul_pd( x.m_quad.zw, y.m_quad.zw) );
}

HK_FORCE_INLINE void hkVector4d::setSubMul(hkVector4dParameter a, hkVector4dParameter x, hkVector4dParameter y)
{
	m_quad.xy = _mm_sub_pd( a.m_quad.xy, _mm_mul_pd( x.m_quad.xy, y.m_quad.xy) );
	m_quad.zw = _mm_sub_pd( a.m_quad.zw, _mm_mul_pd( x.m_quad.zw, y.m_quad.zw) );
}

HK_FORCE_INLINE void hkVector4d::setCross( hkVector4dParameter v0, hkVector4dParameter v1 )
{
	const hkSingleDouble64 cross0XY = _mm_mul_pd(v0.m_quad.xy, _mm_shuffle_pd(v1.m_quad.xy, v1.m_quad.zw, _MM_SHUFFLE2(0,1)));
	const hkSingleDouble64 cross0ZW = _mm_mul_pd(v0.m_quad.zw, _mm_shuffle_pd(v1.m_quad.xy, v1.m_quad.zw, _MM_SHUFFLE2(1,0)));

	const hkSingleDouble64 cross1XY = _mm_mul_pd(v1.m_quad.xy, _mm_shuffle_pd(v0.m_quad.xy, v0.m_quad.zw, _MM_SHUFFLE2(0,1)));
	const hkSingleDouble64 cross1ZW = _mm_mul_pd(v1.m_quad.zw, _mm_shuffle_pd(v0.m_quad.xy, v0.m_quad.zw, _MM_SHUFFLE2(1,0)));

	const hkSingleDouble64 diffXY = _mm_sub_pd(cross0XY, cross1XY);
	const hkSingleDouble64 diffZW = _mm_sub_pd(cross0ZW, cross1ZW);

	m_quad.xy = _mm_shuffle_pd(diffXY, diffZW, _MM_SHUFFLE2(0,1));
	m_quad.zw = _mm_shuffle_pd(diffXY, diffZW, _MM_SHUFFLE2(1,0));
}

HK_FORCE_INLINE const hkVector4dComparison hkVector4d::equal(hkVector4dParameter a) const
{
	hkVector4dComparison comp;
	comp.m_mask.xy = _mm_cmpeq_pd(m_quad.xy, a.m_quad.xy);
	comp.m_mask.zw = _mm_cmpeq_pd(m_quad.zw, a.m_quad.zw);
	return comp;
}

HK_FORCE_INLINE const hkVector4dComparison hkVector4d::notEqual(hkVector4dParameter a) const
{
	hkVector4dComparison comp;
	comp.m_mask.xy = _mm_cmpneq_pd(m_quad.xy, a.m_quad.xy);
	comp.m_mask.zw = _mm_cmpneq_pd(m_quad.zw, a.m_quad.zw);
	return comp;
}

HK_FORCE_INLINE const hkVector4dComparison hkVector4d::less(hkVector4dParameter a) const
{
	hkVector4dComparison comp;
	comp.m_mask.xy = _mm_cmplt_pd(m_quad.xy, a.m_quad.xy);
	comp.m_mask.zw = _mm_cmplt_pd(m_quad.zw, a.m_quad.zw);
	return comp;
}

HK_FORCE_INLINE const hkVector4dComparison hkVector4d::lessEqual(hkVector4dParameter a) const
{
	hkVector4dComparison comp;
	comp.m_mask.xy = _mm_cmple_pd(m_quad.xy, a.m_quad.xy);
	comp.m_mask.zw = _mm_cmple_pd(m_quad.zw, a.m_quad.zw);
	return comp;
}

HK_FORCE_INLINE const hkVector4dComparison hkVector4d::greater(hkVector4dParameter a) const
{
	hkVector4dComparison comp;
	comp.m_mask.xy = _mm_cmpgt_pd(m_quad.xy, a.m_quad.xy);
	comp.m_mask.zw = _mm_cmpgt_pd(m_quad.zw, a.m_quad.zw);
	return comp;
}

HK_FORCE_INLINE const hkVector4dComparison hkVector4d::greaterEqual(hkVector4dParameter a) const
{
	hkVector4dComparison comp;
	comp.m_mask.xy = _mm_cmpge_pd(m_quad.xy, a.m_quad.xy);
	comp.m_mask.zw = _mm_cmpge_pd(m_quad.zw, a.m_quad.zw);
	return comp;
}

HK_FORCE_INLINE const hkVector4dComparison hkVector4d::lessZero() const
{
	hkVector4dComparison comp;
	const hkSingleDouble64 zero = _mm_setzero_pd();
	comp.m_mask.xy = _mm_cmplt_pd(m_quad.xy, zero);
	comp.m_mask.zw = _mm_cmplt_pd(m_quad.zw, zero);
	return comp;
}

HK_FORCE_INLINE const hkVector4dComparison hkVector4d::lessEqualZero() const
{
	hkVector4dComparison comp;
	const hkSingleDouble64 zero = _mm_setzero_pd();
	comp.m_mask.xy = _mm_cmple_pd(m_quad.xy, zero);
	comp.m_mask.zw = _mm_cmple_pd(m_quad.zw, zero);
	return comp;
}

HK_FORCE_INLINE const hkVector4dComparison hkVector4d::greaterZero() const
{
	hkVector4dComparison comp;
	const hkSingleDouble64 zero = _mm_setzero_pd();
	comp.m_mask.xy = _mm_cmpgt_pd(m_quad.xy, zero);
	comp.m_mask.zw = _mm_cmpgt_pd(m_quad.zw, zero);
	return comp;
}

HK_FORCE_INLINE const hkVector4dComparison hkVector4d::greaterEqualZero() const
{
	hkVector4dComparison comp;
	const hkSingleDouble64 zero = _mm_setzero_pd();
	comp.m_mask.xy = _mm_cmpge_pd(m_quad.xy, zero);
	comp.m_mask.zw = _mm_cmpge_pd(m_quad.zw, zero);
	return comp;
}

HK_FORCE_INLINE const hkVector4dComparison hkVector4d::equalZero() const
{
	hkVector4dComparison comp;
	const hkSingleDouble64 zero = _mm_setzero_pd();
	comp.m_mask.xy = _mm_cmpeq_pd(m_quad.xy, zero);
	comp.m_mask.zw = _mm_cmpeq_pd(m_quad.zw, zero);
	return comp;
}

HK_FORCE_INLINE const hkVector4dComparison hkVector4d::notEqualZero() const
{
	hkVector4dComparison comp;
	const hkSingleDouble64 zero = _mm_setzero_pd();
	comp.m_mask.xy = _mm_cmpneq_pd(m_quad.xy, zero);
	comp.m_mask.zw = _mm_cmpneq_pd(m_quad.zw, zero);
	return comp;
}

HK_FORCE_INLINE void hkVector4d::setSelect( hkVector4dComparisonParameter comp, hkVector4dParameter trueValue, hkVector4dParameter falseValue )
{
#if HK_SSE_VERSION >= 0x41
	m_quad.xy = _mm_blendv_pd(falseValue.m_quad.xy, trueValue.m_quad.xy, comp.m_mask.xy);
	m_quad.zw = _mm_blendv_pd(falseValue.m_quad.zw, trueValue.m_quad.zw, comp.m_mask.zw);
#else
	m_quad.xy = _mm_or_pd( _mm_and_pd(comp.m_mask.xy, trueValue.m_quad.xy), _mm_andnot_pd(comp.m_mask.xy, falseValue.m_quad.xy) );
	m_quad.zw = _mm_or_pd( _mm_and_pd(comp.m_mask.zw, trueValue.m_quad.zw), _mm_andnot_pd(comp.m_mask.zw, falseValue.m_quad.zw) );
#endif
}


template<> 
HK_FORCE_INLINE void hkVector4d::setSelect<hkVector4ComparisonMask::MASK_X>( hkVector4dParameter trueValue, hkVector4dParameter falseValue )
{
	m_quad.xy = MOVE_SD(falseValue.m_quad.xy, trueValue.m_quad.xy);
	m_quad.zw = falseValue.m_quad.zw;
}

template<> 
HK_FORCE_INLINE void hkVector4d::setSelect<hkVector4ComparisonMask::MASK_XY>( hkVector4dParameter trueValue, hkVector4dParameter falseValue )
{
	m_quad.xy = trueValue.m_quad.xy;
	m_quad.zw = falseValue.m_quad.zw;
}

template<> 
HK_FORCE_INLINE void hkVector4d::setSelect<hkVector4ComparisonMask::MASK_XYZ>( hkVector4dParameter trueValue, hkVector4dParameter falseValue )
{
	m_quad.xy = trueValue.m_quad.xy;
	m_quad.zw = MOVE_SD(falseValue.m_quad.zw, trueValue.m_quad.zw);
}

#if HK_SSE_VERSION >= 0x41
template<hkVector4dComparison::Mask M> 
HK_FORCE_INLINE void hkVector4d::setSelect( hkVector4dParameter trueValue, hkVector4dParameter falseValue )
{
	HK_VECTORdCOMPARISON_MASK_CHECK;
	m_quad.xy = _mm_blend_pd(falseValue.m_quad.xy, trueValue.m_quad.xy, M & 0x3);
	m_quad.zw = _mm_blend_pd(falseValue.m_quad.zw, trueValue.m_quad.zw, (M>>2));
}
#else
template<hkVector4dComparison::Mask M> 
HK_FORCE_INLINE void hkVector4d::setSelect( hkVector4dParameter trueValue, hkVector4dParameter falseValue )
{
	hkVector4dComparison comp; comp.set<M>();
	setSelect(comp, trueValue, falseValue);
}
#endif

HK_FORCE_INLINE void hkVector4d::zeroIfFalse( hkVector4dComparisonParameter comp )
{
	m_quad.xy = _mm_and_pd(comp.m_mask.xy, m_quad.xy);
	m_quad.zw = _mm_and_pd(comp.m_mask.zw, m_quad.zw);
}

HK_FORCE_INLINE void hkVector4d::zeroIfTrue( hkVector4dComparisonParameter comp )
{
	m_quad.xy = _mm_andnot_pd(comp.m_mask.xy, m_quad.xy);
	m_quad.zw = _mm_andnot_pd(comp.m_mask.zw, m_quad.zw);
}


template <>
HK_FORCE_INLINE void hkVector4d::setNeg<1>(hkVector4dParameter v)
{
	__m128i mask = _mm_insert_epi16(_mm_setzero_si128(), 0x8000, 0x3);
	m_quad.xy = _mm_xor_pd(v.m_quad.xy, _mm_castsi128_pd(mask));
	m_quad.zw = v.m_quad.zw;
}

template <>
HK_FORCE_INLINE void hkVector4d::setNeg<2>(hkVector4dParameter v)
{
	__m128i mask = _mm_insert_epi16(_mm_setzero_si128(), 0x8000, 0x3);
	mask = _mm_shuffle_epi32(mask, _MM_SHUFFLE(1,0,1,0));
	m_quad.xy = _mm_xor_pd(v.m_quad.xy, _mm_castsi128_pd(mask));
	m_quad.zw = v.m_quad.zw;
}

template <>
HK_FORCE_INLINE void hkVector4d::setNeg<3>(hkVector4dParameter v)
{
	__m128i mask = _mm_insert_epi16(_mm_setzero_si128(), 0x8000, 0x3);
	m_quad.zw = _mm_xor_pd(v.m_quad.zw, _mm_castsi128_pd(mask));
	mask = _mm_shuffle_epi32(mask, _MM_SHUFFLE(1,0,1,0));
	m_quad.xy = _mm_xor_pd(v.m_quad.xy, _mm_castsi128_pd(mask));
}

template <>
HK_FORCE_INLINE void hkVector4d::setNeg<4>(hkVector4dParameter v)
{
	__m128i mask = _mm_insert_epi16(_mm_setzero_si128(), 0x8000, 0x3);
	mask = _mm_shuffle_epi32(mask, _MM_SHUFFLE(1,0,1,0));
	m_quad.xy = _mm_xor_pd(v.m_quad.xy, _mm_castsi128_pd(mask));
	m_quad.zw = _mm_xor_pd(v.m_quad.zw, _mm_castsi128_pd(mask));
}

template <int N>
HK_FORCE_INLINE void hkVector4d::setNeg(hkVector4dParameter v)
{
	HK_VECTOR4d_NOT_IMPLEMENTED;
}

HK_FORCE_INLINE void hkVector4d::setAbs(hkVector4dParameter v)
{
	m_quad.xy = hkMath::twoFabs(v.m_quad.xy);
	m_quad.zw = hkMath::twoFabs(v.m_quad.zw);
}

HK_FORCE_INLINE void hkVector4d::setMin(hkVector4dParameter a, hkVector4dParameter b)
{
	m_quad.xy = _mm_min_pd(a.m_quad.xy, b.m_quad.xy);
	m_quad.zw = _mm_min_pd(a.m_quad.zw, b.m_quad.zw);
}

HK_FORCE_INLINE void hkVector4d::setMax(hkVector4dParameter a, hkVector4dParameter b)
{
	m_quad.xy = _mm_max_pd(a.m_quad.xy, b.m_quad.xy);
	m_quad.zw = _mm_max_pd(a.m_quad.zw, b.m_quad.zw);
}

/* matrix3, rotation, quaternion, transform */

HK_FORCE_INLINE void hkVector4d::_setRotatedDir(const hkMatrix3d& r, hkVector4dParameter b )
{
	const hkQuadDouble64 c0 = r.getColumn<0>().m_quad;
	const hkQuadDouble64 c1 = r.getColumn<1>().m_quad;
	const hkQuadDouble64 c2 = r.getColumn<2>().m_quad;

	const hkSingleDouble64 b0 = _mm_unpacklo_pd( b.m_quad.xy, b.m_quad.xy );
	const hkSingleDouble64 b1 = _mm_unpackhi_pd( b.m_quad.xy, b.m_quad.xy );
	const hkSingleDouble64 b2 = _mm_unpacklo_pd( b.m_quad.zw, b.m_quad.zw );	

	{
		const hkSingleDouble64 r0 = _mm_mul_pd( c0.xy, b0 );
		const hkSingleDouble64 r1 = _mm_mul_pd( c1.xy, b1 );
		const hkSingleDouble64 r2 = _mm_mul_pd( c2.xy, b2 );

		m_quad.xy = _mm_add_pd( _mm_add_pd(r0, r1), r2 );
	}
	{
		const hkSingleDouble64 r0 = _mm_mul_pd( c0.zw, b0 );
		const hkSingleDouble64 r1 = _mm_mul_pd( c1.zw, b1 );
		const hkSingleDouble64 r2 = _mm_mul_pd( c2.zw, b2 );

		m_quad.zw = _mm_add_pd( _mm_add_pd(r0, r1), r2 );
	}
}

HK_FORCE_INLINE void hkVector4d::_setRotatedInverseDir(const hkMatrix3d& r, hkVector4dParameter b )
{
#if HK_SSE_VERSION >= 0x41
	const hkQuadDouble64 c0 = r.getColumn<0>().m_quad;
	const hkQuadDouble64 c1 = r.getColumn<1>().m_quad;
	const hkQuadDouble64 c2 = r.getColumn<2>().m_quad;

	const hkSingleDouble64 r0a = _mm_dp_pd( c0.xy, b.m_quad.xy, 0x31 );
	const hkSingleDouble64 r0b = _mm_dp_pd( c0.zw, b.m_quad.zw, 0x11 );

	const hkSingleDouble64 r1a = _mm_dp_pd( c1.xy, b.m_quad.xy, 0x32 );
	const hkSingleDouble64 r1b = _mm_dp_pd( c1.zw, b.m_quad.zw, 0x12 );

	const hkSingleDouble64 r2a = _mm_dp_pd( c2.xy, b.m_quad.xy, 0x31 );
	const hkSingleDouble64 r2b = _mm_dp_pd( c2.zw, b.m_quad.zw, 0x11 );

	m_quad.xy = _mm_or_pd( _mm_add_pd(r0a, r0b), _mm_add_pd(r1a, r1b) );
	m_quad.zw = _mm_add_pd(r2a, r2b);
#else
	hkVector4d c0 = r.getColumn<0>();
	hkVector4d c1 = r.getColumn<1>();
	hkVector4d c2 = r.getColumn<2>();

	HK_TRANSPOSE3d(c0,c1,c2);

	const hkSingleDouble64 b0 = _mm_unpacklo_pd( b.m_quad.xy, b.m_quad.xy );
	const hkSingleDouble64 b1 = _mm_unpackhi_pd( b.m_quad.xy, b.m_quad.xy );
	const hkSingleDouble64 b2 = _mm_unpacklo_pd( b.m_quad.zw, b.m_quad.zw );	

	{
		const hkSingleDouble64 r0 = _mm_mul_pd( c0.m_quad.xy, b0 );
		const hkSingleDouble64 r1 = _mm_mul_pd( c1.m_quad.xy, b1 );
		const hkSingleDouble64 r2 = _mm_mul_pd( c2.m_quad.xy, b2 );

		m_quad.xy = _mm_add_pd( _mm_add_pd(r0, r1), r2 );
	}
	{
		const hkSingleDouble64 r0 = _mm_mul_pd( c0.m_quad.zw, b0 );
		const hkSingleDouble64 r1 = _mm_mul_pd( c1.m_quad.zw, b1 );
		const hkSingleDouble64 r2 = _mm_mul_pd( c2.m_quad.zw, b2 );

		m_quad.zw = _mm_add_pd( _mm_add_pd(r0, r1), r2 );
	}
#endif
}


template <>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::dot<2>(hkVector4dParameter a) const
{
#if HK_SSE_VERSION >= 0x41
	return hkSimdDouble64::convert(_mm_dp_pd(m_quad.xy, a.m_quad.xy, 0x33));
#elif HK_SSE_VERSION >= 0x30
	const hkSingleDouble64 x2 = _mm_mul_pd(m_quad.xy,a.m_quad.xy);
	return hkSimdDouble64::convert(_mm_hadd_pd(x2,x2));
#else
	const hkSingleDouble64 x2 = _mm_mul_pd(m_quad.xy,a.m_quad.xy);
	const hkSingleDouble64 result = _mm_add_pd( _mm_unpacklo_pd(x2,x2), _mm_unpackhi_pd(x2,x2) ); // xy xy
	return hkSimdDouble64::convert(result);
#endif
}

template <>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::dot<3>(hkVector4dParameter a) const
{
#if HK_SSE_VERSION >= 0x41
	const hkSingleDouble64 xy = _mm_dp_pd(m_quad.xy, a.m_quad.xy, 0x33);
	const hkSingleDouble64 z  = _mm_dp_pd(m_quad.zw, a.m_quad.zw, 0x13);
	return hkSimdDouble64::convert(_mm_add_pd(xy,z));
#elif HK_SSE_VERSION >= 0x30
	const hkSingleDouble64 x2a = _mm_mul_pd(m_quad.xy,a.m_quad.xy);
	const hkSingleDouble64 x2b = _mm_mul_pd(m_quad.zw,a.m_quad.zw);
	const hkSingleDouble64 hsum = _mm_hadd_pd(x2a,x2a); // xy xy
	const hkSingleDouble64 z = _mm_unpacklo_pd(x2b,x2b); // zz
	return hkSimdDouble64::convert(_mm_add_pd(hsum, z)); // xyz xyz
#else
	const hkSingleDouble64 x2a = _mm_mul_pd(m_quad.xy,a.m_quad.xy);
	const hkSingleDouble64 x2b = _mm_mul_pd(m_quad.zw,a.m_quad.zw);
	const hkSingleDouble64 xySum = _mm_add_pd( _mm_unpacklo_pd(x2a,x2a), _mm_unpackhi_pd(x2a,x2a) ); // xy xy
	const hkSingleDouble64 z = _mm_unpacklo_pd(x2b,x2b); // zz
	const hkSingleDouble64 result = _mm_add_pd( z, xySum); // xyz xyz
	return hkSimdDouble64::convert(result);
#endif
}

template <>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::dot<4>(hkVector4dParameter a) const
{
#if HK_SSE_VERSION >= 0x41
	const hkSingleDouble64 xy = _mm_dp_pd(m_quad.xy, a.m_quad.xy, 0x33);
	const hkSingleDouble64 zw = _mm_dp_pd(m_quad.zw, a.m_quad.zw, 0x33);
	return hkSimdDouble64::convert(_mm_add_pd(xy,zw));
#elif HK_SSE_VERSION >= 0x30
	const hkSingleDouble64 x2a = _mm_mul_pd(m_quad.xy,a.m_quad.xy);
	const hkSingleDouble64 x2b = _mm_mul_pd(m_quad.zw,a.m_quad.zw);
	const hkSingleDouble64 hsum0 = _mm_hadd_pd(x2a,x2b); // xy zw
	return hkSimdDouble64::convert(_mm_hadd_pd(hsum0,hsum0)); // xyzw all 4
#else
	const hkSingleDouble64 x2a = _mm_mul_pd(m_quad.xy,a.m_quad.xy);
	const hkSingleDouble64 x2b = _mm_mul_pd(m_quad.zw,a.m_quad.zw);
	const hkSingleDouble64 sum0a = _mm_add_pd( _mm_shuffle_pd(x2a,x2a,_MM_SHUFFLE2(0,1)), x2a); // yx+xy = xy xy
	const hkSingleDouble64 sum0b = _mm_add_pd( _mm_shuffle_pd(x2b,x2b,_MM_SHUFFLE2(0,1)), x2b); // wz+zw = zw zw
	const hkSingleDouble64 result = _mm_add_pd( sum0a, sum0b ); // = xyzw xyzw xyzw xyzw
	return hkSimdDouble64::convert(result);
#endif
}

template <int N>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::dot(hkVector4dParameter a) const
{
	HK_VECTOR4d_NOT_IMPLEMENTED;
	return hkSimdDouble64::getConstant<HK_QUADREAL_0>();
}


HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::dot4xyz1(hkVector4dParameter a) const
{
#if HK_SSE_VERSION >= 0x41
	const hkSingleDouble64 xy = _mm_dp_pd(m_quad.xy, a.m_quad.xy, 0x33);
	const hkSingleDouble64 z  = _mm_dp_pd(m_quad.zw, a.m_quad.zw, 0x13);
	const hkSingleDouble64 xyz= _mm_add_pd(xy,z);
	const hkSingleDouble64 w  = _mm_unpackhi_pd(m_quad.zw, m_quad.zw);
	return hkSimdDouble64::convert(_mm_add_pd(xyz,w));
#elif HK_SSE_VERSION >= 0x30
	const hkSingleDouble64 xx2a = _mm_mul_pd(m_quad.xy,a.m_quad.xy);
	const hkSingleDouble64 xx2bf = _mm_mul_pd(m_quad.zw,a.m_quad.zw);
	const hkSingleDouble64 xx2b = _mm_shuffle_pd(m_quad.zw, xx2bf, _MM_SHUFFLE2(0,1));	// replace w by this.w
	const hkSingleDouble64 hsum0 = _mm_hadd_pd(xx2a,xx2b); // xy zw
	return hkSimdDouble64::convert(_mm_hadd_pd(hsum0,hsum0)); // xyzw all 4
#else
	const hkSingleDouble64 xx2a = _mm_mul_pd(m_quad.xy,a.m_quad.xy);
	const hkSingleDouble64 xx2bf = _mm_mul_pd(m_quad.zw,a.m_quad.zw);
	const hkSingleDouble64 xx2b = _mm_shuffle_pd(m_quad.zw, xx2bf, _MM_SHUFFLE2(0,1));	// replace w by this.w
	const hkSingleDouble64 sum0a = _mm_add_pd( _mm_shuffle_pd(xx2a,xx2a,_MM_SHUFFLE2(0,1)), xx2a); // yx+xy = xy xy
	const hkSingleDouble64 sum0b = _mm_add_pd( _mm_shuffle_pd(xx2b,xx2b,_MM_SHUFFLE2(0,1)), xx2b); // wz+zw = zw zw
	const hkSingleDouble64 result = _mm_add_pd( sum0a, sum0b ); // = xyzw xyzw xyzw xyzw
	return hkSimdDouble64::convert(result);
#endif
}

template <>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::horizontalAdd<2>() const
{
#if HK_SSE_VERSION >= 0x30
	return hkSimdDouble64::convert(_mm_hadd_pd(m_quad.xy, m_quad.xy));
#else
	return hkSimdDouble64::convert(_mm_add_pd( _mm_shuffle_pd(m_quad.xy,m_quad.xy,_MM_SHUFFLE2(0,1)), m_quad.xy));
#endif
}

template <>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::horizontalAdd<3>() const
{
#if HK_SSE_VERSION >= 0x30
	const hkSingleDouble64 x2 = _mm_hadd_pd(m_quad.xy, m_quad.xy);
	return hkSimdDouble64::convert(_mm_add_pd( _mm_unpacklo_pd(m_quad.zw,m_quad.zw), x2));
#else
	const hkSingleDouble64 xySum = _mm_add_pd( _mm_shuffle_pd(m_quad.xy,m_quad.xy,_MM_SHUFFLE2(0,1)), m_quad.xy);
	return hkSimdDouble64::convert(_mm_add_pd( _mm_unpacklo_pd(m_quad.zw,m_quad.zw), xySum));
#endif
}

template <>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::horizontalAdd<4>() const
{
#if HK_SSE_VERSION >= 0x30
	const hkSingleDouble64 x2a = _mm_hadd_pd(m_quad.xy, m_quad.zw);
	return hkSimdDouble64::convert(_mm_hadd_pd(x2a, x2a));
#else
	const hkSingleDouble64 sum0 = _mm_add_pd( _mm_shuffle_pd(m_quad.xy,m_quad.xy,_MM_SHUFFLE2(0,1)), m_quad.xy); // yx+xy = xy xy
	const hkSingleDouble64 sum1 = _mm_add_pd( _mm_shuffle_pd(m_quad.zw,m_quad.zw,_MM_SHUFFLE2(0,1)), m_quad.zw); // wz+zw = zw zw
	return hkSimdDouble64::convert(_mm_add_pd( sum0, sum1 )); // xywz all 4
#endif
}

template <int N>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::horizontalAdd() const
{
	HK_VECTOR4d_NOT_IMPLEMENTED;
	return hkSimdDouble64::getConstant<HK_QUADREAL_0>();
}

template <>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::horizontalMul<2>() const
{
	return hkSimdDouble64::convert(_mm_mul_pd( _mm_shuffle_pd(m_quad.xy,m_quad.xy,_MM_SHUFFLE2(0,1)), m_quad.xy));
}

template <>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::horizontalMul<3>() const
{
	const hkSingleDouble64 xyProd = _mm_mul_pd( _mm_shuffle_pd(m_quad.xy,m_quad.xy,_MM_SHUFFLE2(0,1)), m_quad.xy);
	return hkSimdDouble64::convert(_mm_mul_pd( _mm_unpacklo_pd(m_quad.zw,m_quad.zw), xyProd));
}

template <>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::horizontalMul<4>() const
{
	const hkSingleDouble64 prod0 = _mm_mul_pd( _mm_shuffle_pd(m_quad.xy,m_quad.xy,_MM_SHUFFLE2(0,1)), m_quad.xy); // yx*xy = xy xy
	const hkSingleDouble64 prod1 = _mm_mul_pd( _mm_shuffle_pd(m_quad.zw,m_quad.zw,_MM_SHUFFLE2(0,1)), m_quad.zw); // wz*zw = zw zw
	return hkSimdDouble64::convert(_mm_mul_pd( prod0, prod1 )); // xywz all 4
}

template <int N>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::horizontalMul() const
{
	HK_VECTOR4d_NOT_IMPLEMENTED;
	return hkSimdDouble64::getConstant<HK_QUADREAL_0>();
}

template <>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::horizontalMin<1>() const
{
	return getComponent<0>();
}

template <>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::horizontalMin<2>() const
{
	return hkSimdDouble64::convert(_mm_min_pd( _mm_shuffle_pd(m_quad.xy,m_quad.xy,_MM_SHUFFLE2(0,1)), m_quad.xy));
}

template <>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::horizontalMin<3>() const
{
	const hkSingleDouble64 xy = _mm_min_pd( _mm_shuffle_pd(m_quad.xy,m_quad.xy,_MM_SHUFFLE2(0,1)), m_quad.xy);
	return hkSimdDouble64::convert(_mm_min_pd( _mm_unpacklo_pd(m_quad.zw,m_quad.zw), xy));
}

template <>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::horizontalMin<4>() const
{
	const hkSingleDouble64 sum0 = _mm_min_pd( _mm_shuffle_pd( m_quad.xy, m_quad.xy,_MM_SHUFFLE2(0,1)), m_quad.xy); // yx+xy = xy xy
	const hkSingleDouble64 sum1 = _mm_min_pd( _mm_shuffle_pd( m_quad.zw, m_quad.zw,_MM_SHUFFLE2(0,1)), m_quad.zw); // wz+zw = zw zw
	return hkSimdDouble64::convert(_mm_min_pd( sum0, sum1 )); // xywz all 4
}

template <int N>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::horizontalMin() const
{
	HK_VECTOR4d_NOT_IMPLEMENTED;
	return hkSimdDouble64::getConstant<HK_QUADREAL_0>();
}

/* operator () */

HK_FORCE_INLINE hkDouble64& hkVector4d::operator() (int a)
{
	HK_MATH_ASSERT(0x6d0c31d7, a>=0 && a<4, "index out of bounds for component access");
	if (a<2)
		return HK_M128(m_quad.xy).m128d_f64[a];
	else
		return HK_M128(m_quad.zw).m128d_f64[a-2];
}

HK_FORCE_INLINE const hkDouble64& hkVector4d::operator() (int a) const
{
	HK_MATH_ASSERT(0x6d0c31d7, a>=0 && a<4, "index out of bounds for component access");
	if (a<2)
		return HK_M128(m_quad.xy).m128d_f64[a];
	else
		return HK_M128(m_quad.zw).m128d_f64[a-2];
}

HK_FORCE_INLINE void hkVector4d::setXYZ_W(hkVector4dParameter xyz, hkVector4dParameter w)
{
	m_quad.xy = xyz.m_quad.xy;
	m_quad.zw = MOVE_SD(w.m_quad.zw, xyz.m_quad.zw);
}

HK_FORCE_INLINE void hkVector4d::setXYZ_W(hkVector4dParameter xyz, hkSimdDouble64Parameter w)
{
	m_quad.xy = xyz.m_quad.xy;
	m_quad.zw = MOVE_SD(w.m_real, xyz.m_quad.zw);
}

HK_FORCE_INLINE void hkVector4d::setW(hkVector4dParameter w)
{
	m_quad.zw = MOVE_SD(w.m_quad.zw, m_quad.zw);
}

HK_FORCE_INLINE void hkVector4d::setXYZ(hkVector4dParameter xyz)
{
	m_quad.xy = xyz.m_quad.xy;
	m_quad.zw = MOVE_SD(m_quad.zw, xyz.m_quad.zw);
}

HK_FORCE_INLINE void hkVector4d::addXYZ(hkVector4dParameter xyz)
{
	m_quad.xy = _mm_add_pd(m_quad.xy, xyz.m_quad.xy);
	m_quad.zw = _mm_add_pd(m_quad.zw, xyz.m_quad.zw);
	HK_ON_DEBUG( *(hkUint64*)&(HK_M128(m_quad.zw).m128d_f64[1]) = 0xffffffffffffffff; )
}

HK_FORCE_INLINE void hkVector4d::subXYZ(hkVector4dParameter xyz)
{
	m_quad.xy = _mm_sub_pd(m_quad.xy, xyz.m_quad.xy);
	m_quad.zw = _mm_sub_pd(m_quad.zw, xyz.m_quad.zw);
	HK_ON_DEBUG( *(hkUint64*)&(HK_M128(m_quad.zw).m128d_f64[1]) = 0xffffffffffffffff; )
}

HK_FORCE_INLINE void hkVector4d::setXYZ(hkDouble64 v)
{
#if HK_SSE_VERSION >= 0x30
	m_quad.xy = _mm_loaddup_pd(&v);
#else
	m_quad.xy = _mm_load1_pd(&v);
#endif
	m_quad.zw = MOVE_SD(m_quad.zw,m_quad.xy);
}

HK_FORCE_INLINE void hkVector4d::setXYZ(hkSimdDouble64Parameter v)
{
	m_quad.xy = v.m_real;
	m_quad.zw = MOVE_SD(m_quad.zw, v.m_real);
}

HK_FORCE_INLINE void hkVector4d::setXYZ_0(hkVector4dParameter xyz)
{
	m_quad.xy = xyz.m_quad.xy;
	m_quad.zw = MOVE_SD(_mm_setzero_pd(), xyz.m_quad.zw);
}

HK_FORCE_INLINE void hkVector4d::setBroadcastXYZ(const int i, hkVector4dParameter v)
{
	setBroadcast(i,v);
	HK_ON_DEBUG( *(hkUint64*)&(HK_M128(m_quad.zw).m128d_f64[1]) = 0xffffffffffffffff; )
}

HK_FORCE_INLINE void hkVector4d::setComponent(const int i, hkSimdDouble64Parameter val)
{
	static HK_ALIGN16 (const hkUint64 indexToMask[4]) = 
	{
		0xffffffffffffffff, 0x0000000000000000,
		0x0000000000000000, 0xffffffffffffffff,
	};

	HK_MATH_ASSERT(0x6d0c31d7, i>=0 && i<4, "index out of bounds for component access");

	if (i<2)
	{
		const hkSingleDouble64 mask = *(const hkSingleDouble64*)&indexToMask[i*2];
#if HK_SSE_VERSION >= 0x41
		m_quad.xy = _mm_blendv_pd(m_quad.xy, val.m_real, mask);
#else
		m_quad.xy = _mm_or_pd( _mm_and_pd(mask, val.m_real), _mm_andnot_pd(mask, m_quad.xy) );
#endif
	}
	else
	{
		const hkSingleDouble64 mask = *(const hkSingleDouble64*)&indexToMask[(i-2)*2];
#if HK_SSE_VERSION >= 0x41
		m_quad.zw = _mm_blendv_pd(m_quad.zw, val.m_real, mask);
#else
		m_quad.zw = _mm_or_pd( _mm_and_pd(mask, val.m_real), _mm_andnot_pd(mask, m_quad.zw) );
#endif
	}
}

template <>
HK_FORCE_INLINE void hkVector4d::setComponent<0>(hkSimdDouble64Parameter val)
{
	m_quad.xy = MOVE_SD( m_quad.xy, val.m_real );
}
template <>
HK_FORCE_INLINE void hkVector4d::setComponent<1>(hkSimdDouble64Parameter val)
{
	m_quad.xy = MOVE_SD( val.m_real, m_quad.xy );
}
template <>
HK_FORCE_INLINE void hkVector4d::setComponent<2>(hkSimdDouble64Parameter val)
{
	m_quad.zw = MOVE_SD( m_quad.zw, val.m_real);
}
template <>
HK_FORCE_INLINE void hkVector4d::setComponent<3>(hkSimdDouble64Parameter val)
{
	m_quad.zw = MOVE_SD( val.m_real, m_quad.zw);
}

template <int I>
HK_FORCE_INLINE void hkVector4d::setComponent(hkSimdDouble64Parameter val)
{
	HK_VECTOR4d_SUBINDEX_CHECK;
}

template <>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::horizontalMax<1>() const
{
	return getComponent<0>();
}

template <>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::horizontalMax<2>() const
{
	return hkSimdDouble64::convert(_mm_max_pd( _mm_shuffle_pd(m_quad.xy,m_quad.xy,_MM_SHUFFLE2(0,1)), m_quad.xy));
}

template <>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::horizontalMax<3>() const
{
	const hkSingleDouble64 xy = _mm_max_pd( _mm_shuffle_pd(m_quad.xy,m_quad.xy,_MM_SHUFFLE2(0,1)), m_quad.xy);
	return hkSimdDouble64::convert(_mm_max_pd( _mm_unpacklo_pd(m_quad.zw,m_quad.zw), xy));
}

template <>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::horizontalMax<4>() const
{
	const hkSingleDouble64 sum0 = _mm_max_pd( _mm_shuffle_pd( m_quad.xy, m_quad.xy,_MM_SHUFFLE2(0,1)), m_quad.xy); // yx+xy = xy xy
	const hkSingleDouble64 sum1 = _mm_max_pd( _mm_shuffle_pd( m_quad.zw, m_quad.zw,_MM_SHUFFLE2(0,1)), m_quad.zw); // wz+zw = zw zw
	return hkSimdDouble64::convert(_mm_max_pd( sum0, sum1 )); // xywz all 4
}

template <int N>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::horizontalMax() const
{
	HK_VECTOR4d_NOT_IMPLEMENTED;
	return hkSimdDouble64::getConstant<HK_QUADREAL_0>();
}

HK_FORCE_INLINE void hkVector4d::reduceToHalfPrecision()
{
#if defined(HK_HALF_IS_FLOAT)
	static HK_ALIGN16(const hkUint64 mask[2])      = {0xFFFFFFFF00000000ull, 0xFFFFFFFF00000000ull};
	m_quad.xy = _mm_and_pd(m_quad.xy, *((__m128d*)&mask) );
	m_quad.zw = _mm_and_pd(m_quad.zw, *((__m128d*)&mask) );
#else
	__m128 xy = _mm_cvtpd_ps(m_quad.xy);
	__m128 zw = _mm_cvtpd_ps(m_quad.zw);
	__m128 xyzw = _mm_shuffle_ps(xy,zw,_MM_SHUFFLE(1,0,1,0));
#if HK_SSE_VERSION >= 0x41
	xyzw = _mm_castsi128_ps(_mm_blend_epi16(_mm_castps_si128(xyzw), _mm_setzero_si128(), 0x55));
#else
	__m128i precisionMask = _mm_set1_epi32(0xffff0000);
	xyzw = _mm_and_ps( xyzw, _mm_castsi128_ps(precisionMask) );
#endif
	m_quad.xy = _mm_cvtps_pd(xyzw);
	m_quad.zw = _mm_cvtps_pd(_mm_shuffle_ps(xyzw,xyzw,_MM_SHUFFLE(1,0,3,2)));
#endif
}

template <> 
HK_FORCE_INLINE hkBool32 hkVector4d::isOk<1>() const
{
	const hkSingleDouble64 nanMask = _mm_cmpord_pd(m_quad.xy, _mm_setzero_pd());
	return (_mm_movemask_pd(nanMask) & 0x1);
}

template <> 
HK_FORCE_INLINE hkBool32 hkVector4d::isOk<2>() const
{
	const hkSingleDouble64 nanMask = _mm_cmpunord_pd(m_quad.xy, _mm_setzero_pd());
	return !_mm_movemask_pd(nanMask);
}

template <> 
HK_FORCE_INLINE hkBool32 hkVector4d::isOk<3>() const
{
	const hkSingleDouble64 zero = _mm_setzero_pd();
	const hkSingleDouble64 nanMaskXY = _mm_cmpunord_pd(m_quad.xy, zero);
	const hkSingleDouble64 nanMaskZW = _mm_cmpord_pd(m_quad.zw, zero);
	return (!_mm_movemask_pd(nanMaskXY) && (_mm_movemask_pd(nanMaskZW)&0x1));
}

template <> 
HK_FORCE_INLINE hkBool32 hkVector4d::isOk<4>() const
{
	const hkSingleDouble64 zero = _mm_setzero_pd();
	const hkSingleDouble64 nanMaskXY = _mm_cmpunord_pd(m_quad.xy, zero);
	const hkSingleDouble64 nanMaskZW = _mm_cmpunord_pd(m_quad.zw, zero);
	return !(_mm_movemask_pd(nanMaskXY) || _mm_movemask_pd(nanMaskZW));
}

template <int N> 
HK_FORCE_INLINE hkBool32 hkVector4d::isOk() const
{
	HK_VECTOR4d_NOT_IMPLEMENTED;
	return false;
}

#if HK_SSE_VERSION >= 0x30
template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::XXZZ>(hkVector4dParameter v)
{
	m_quad.xy = _mm_movedup_pd(v.m_quad.xy);
	m_quad.zw = _mm_movedup_pd(v.m_quad.zw);
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::XXYY>(hkVector4dParameter v)
{
	m_quad.zw = _mm_unpackhi_pd(v.m_quad.xy,v.m_quad.xy);
	m_quad.xy = _mm_movedup_pd(v.m_quad.xy);
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::XXXX>(hkVector4dParameter v)
{
	m_quad.zw = _mm_movedup_pd(v.m_quad.xy);
	m_quad.xy = m_quad.zw;
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::ZZZZ>(hkVector4dParameter v)
{
	m_quad.xy = _mm_movedup_pd(v.m_quad.zw);
	m_quad.zw = m_quad.xy;
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::ZYZZ>(hkVector4dParameter v)
{
	m_quad.xy = MOVE_SD( v.m_quad.xy, v.m_quad.zw );
	m_quad.zw = _mm_movedup_pd(v.m_quad.zw);
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::ZZYY>(hkVector4dParameter v)
{
	const __m128d yy = _mm_unpackhi_pd(v.m_quad.xy,v.m_quad.xy);
	m_quad.xy = _mm_movedup_pd(v.m_quad.zw);
	m_quad.zw = yy;
}
#else
template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::XXZZ>(hkVector4dParameter v)
{
	m_quad.xy = _mm_unpacklo_pd(v.m_quad.xy,v.m_quad.xy);
	m_quad.zw = _mm_unpacklo_pd(v.m_quad.zw,v.m_quad.zw);
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::XXYY>(hkVector4dParameter v)
{
	m_quad.zw = _mm_unpackhi_pd(v.m_quad.xy,v.m_quad.xy);
	m_quad.xy = _mm_unpacklo_pd(v.m_quad.xy,v.m_quad.xy);
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::XXXX>(hkVector4dParameter v)
{
	m_quad.zw = _mm_unpacklo_pd(v.m_quad.xy,v.m_quad.xy);
	m_quad.xy = m_quad.zw;
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::ZZZZ>(hkVector4dParameter v)
{
	m_quad.xy = _mm_unpacklo_pd(v.m_quad.zw,v.m_quad.zw);
	m_quad.zw = m_quad.xy;
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::ZYZZ>(hkVector4dParameter v)
{
	m_quad.xy = MOVE_SD( v.m_quad.xy, v.m_quad.zw );
	m_quad.zw = _mm_unpacklo_pd(v.m_quad.zw,v.m_quad.zw);
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::ZYZW>(hkVector4dParameter v)
{
	m_quad.xy = MOVE_SD( v.m_quad.xy, v.m_quad.zw );
	m_quad.zw = v.m_quad.zw;
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::ZZYY>(hkVector4dParameter v)
{
	const __m128d yy = _mm_unpackhi_pd(v.m_quad.xy,v.m_quad.xy);
	m_quad.xy = _mm_unpacklo_pd(v.m_quad.zw,v.m_quad.zw);
	m_quad.zw = yy;
}
#endif

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::YYYY>(hkVector4dParameter v)
{
	m_quad.zw = _mm_unpackhi_pd(v.m_quad.xy,v.m_quad.xy);
	m_quad.xy = m_quad.zw;
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::YYWW>(hkVector4dParameter v)
{
	m_quad.xy = _mm_unpackhi_pd(v.m_quad.xy,v.m_quad.xy);
	m_quad.zw = _mm_unpackhi_pd(v.m_quad.zw,v.m_quad.zw);
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::YYXX>(hkVector4dParameter v)
{
	m_quad.zw = _mm_unpacklo_pd(v.m_quad.xy,v.m_quad.xy);
	m_quad.xy = _mm_unpackhi_pd(v.m_quad.xy,v.m_quad.xy);
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::XZYW>(hkVector4dParameter v)
{
	const __m128d xy = v.m_quad.xy;
	m_quad.xy = _mm_unpacklo_pd(xy,v.m_quad.zw);
	m_quad.zw = _mm_unpackhi_pd(xy,v.m_quad.zw);
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::YXXY>(hkVector4dParameter v)
{
	m_quad.zw = v.m_quad.xy;
	m_quad.xy = _mm_shuffle_pd( v.m_quad.xy, v.m_quad.xy,_MM_SHUFFLE2(0,1));
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::YXZW>(hkVector4dParameter v)
{
	m_quad.xy = _mm_shuffle_pd( v.m_quad.xy, v.m_quad.xy,_MM_SHUFFLE2(0,1));
	m_quad.zw = v.m_quad.zw;
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::YXWW>(hkVector4dParameter v)
{
	m_quad.xy = _mm_shuffle_pd( v.m_quad.xy, v.m_quad.xy,_MM_SHUFFLE2(0,1));
	m_quad.zw = _mm_unpackhi_pd(v.m_quad.zw,v.m_quad.zw);
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::YZXW>(hkVector4dParameter v)
{
	const __m128d xy = v.m_quad.xy;
	m_quad.xy = _mm_shuffle_pd( xy, v.m_quad.zw, _MM_SHUFFLE2(0,1));
	m_quad.zw = MOVE_SD( v.m_quad.zw, xy );
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::YZZW>(hkVector4dParameter v)
{
	const __m128d xy = v.m_quad.xy;
	m_quad.xy = _mm_shuffle_pd( xy, v.m_quad.zw, _MM_SHUFFLE2(0,1));
	m_quad.zw = v.m_quad.zw;
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::YZZY>(hkVector4dParameter v)
{
	const __m128d xy = v.m_quad.xy;
	m_quad.xy = _mm_shuffle_pd( xy, v.m_quad.zw, _MM_SHUFFLE2(0,1));
	m_quad.zw = MOVE_SD(xy, v.m_quad.zw);
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::YZXZ>(hkVector4dParameter v)
{
	const __m128d xy = v.m_quad.xy;
	m_quad.xy = _mm_shuffle_pd( xy, v.m_quad.zw, _MM_SHUFFLE2(0,1));
	m_quad.zw = _mm_unpacklo_pd( xy, v.m_quad.zw );
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::YZWX>(hkVector4dParameter v)
{
	const __m128d xy = v.m_quad.xy;
	m_quad.xy = _mm_shuffle_pd( xy, v.m_quad.zw, _MM_SHUFFLE2(0,1));
	m_quad.zw = _mm_shuffle_pd( v.m_quad.zw, xy, _MM_SHUFFLE2(0,1));
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::YWZX>(hkVector4dParameter v)
{
	const __m128d xy = v.m_quad.xy;
	m_quad.xy = _mm_unpackhi_pd( xy, v.m_quad.zw );
	m_quad.zw = _mm_unpacklo_pd( v.m_quad.zw, xy );
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::XYWZ>(hkVector4dParameter v)
{
	m_quad.xy = v.m_quad.xy;
	m_quad.zw = _mm_shuffle_pd( v.m_quad.zw, v.m_quad.zw,_MM_SHUFFLE2(0,1));
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::XYXY>(hkVector4dParameter v)
{
	m_quad.zw = v.m_quad.xy;
	m_quad.xy = v.m_quad.xy;
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::ZWZW>(hkVector4dParameter v)
{
	m_quad.xy = v.m_quad.zw;
	m_quad.zw = v.m_quad.zw;
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::ZWXY>(hkVector4dParameter v)
{
	const __m128d xy = v.m_quad.xy;
	m_quad.xy = v.m_quad.zw;
	m_quad.zw = xy;
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::ZWXW>(hkVector4dParameter v)
{
	const __m128d xy = v.m_quad.xy;
	m_quad.xy = v.m_quad.zw;
	m_quad.zw = MOVE_SD( v.m_quad.zw, xy );
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::WXXW>(hkVector4dParameter v)
{
	const __m128d xy = v.m_quad.xy;
	m_quad.xy = _mm_shuffle_pd( v.m_quad.zw, xy, _MM_SHUFFLE2(0,1));
	m_quad.zw = MOVE_SD( v.m_quad.zw, xy );
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::ZXYW>(hkVector4dParameter v)
{
	const __m128d xy = v.m_quad.xy;
	m_quad.xy = _mm_unpacklo_pd(v.m_quad.zw, xy);
	m_quad.zw = _mm_unpackhi_pd(xy, v.m_quad.zw);
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::ZXYZ>(hkVector4dParameter v)
{
	const __m128d xy = v.m_quad.xy;
	m_quad.xy = _mm_unpacklo_pd(v.m_quad.zw, xy);
	m_quad.zw = _mm_shuffle_pd(xy, v.m_quad.zw, _MM_SHUFFLE2(0,1));
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::WXYZ>(hkVector4dParameter v)
{
	const __m128d xy = v.m_quad.xy;
	m_quad.xy = _mm_shuffle_pd( v.m_quad.zw, xy, _MM_SHUFFLE2(0,1));
	m_quad.zw = _mm_shuffle_pd( xy, v.m_quad.zw, _MM_SHUFFLE2(0,1));
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::WZYX>(hkVector4dParameter v)
{
	const __m128d xy = v.m_quad.xy;
	m_quad.xy = _mm_shuffle_pd( v.m_quad.zw, v.m_quad.zw, _MM_SHUFFLE2(0,1));
	m_quad.zw = _mm_shuffle_pd(          xy,          xy, _MM_SHUFFLE2(0,1));
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::XYZW>(hkVector4dParameter v)
{
	m_quad = v.m_quad;
}

template <hkVectorPermutation::Permutation P> 
HK_FORCE_INLINE void hkVector4d::setPermutation(hkVector4dParameter v)
{
	// temp vars for alias safety
	const hkSimdDouble64 X = v.getComponent<(P>>12)&0x3>();
	const hkSimdDouble64 Y = v.getComponent<(P>>8)&0x3>();
	const hkSimdDouble64 Z = v.getComponent<(P>>4)&0x3>();
	const hkSimdDouble64 W = v.getComponent<(P)&0x3>();

	m_quad.xy = MOVE_SD(Y.m_real, X.m_real);
	m_quad.zw = MOVE_SD(W.m_real, Z.m_real);
}

HK_FORCE_INLINE const hkVector4dComparison hkVector4d::signBitSet() const
{
	const __m128i maskXY = _mm_srai_epi32(_mm_castpd_si128(m_quad.xy),31);
	const __m128i maskZW = _mm_srai_epi32(_mm_castpd_si128(m_quad.zw),31);
	const __m128i aXY = _mm_shuffle_epi32(maskXY, _MM_SHUFFLE(3,3,1,1)); // no srai_epi64
	const __m128i aZW = _mm_shuffle_epi32(maskZW, _MM_SHUFFLE(3,3,1,1));
	hkVector4dComparison mask;
	mask.m_mask.xy = _mm_castsi128_pd(aXY);
	mask.m_mask.zw = _mm_castsi128_pd(aZW);
	return mask;
}

HK_FORCE_INLINE const hkVector4dComparison hkVector4d::signBitClear() const
{
	hkVector4dComparison mask;
#if HK_SSE_VERSION >= 0x41
	const __m128i aXY = _mm_srli_epi64(_mm_castpd_si128(m_quad.xy),63);
	const __m128i aZW = _mm_srli_epi64(_mm_castpd_si128(m_quad.zw),63);
	mask.m_mask.xy = _mm_castsi128_pd(_mm_cmpeq_epi64(aXY,_mm_setzero_si128()));
	mask.m_mask.zw = _mm_castsi128_pd(_mm_cmpeq_epi64(aZW,_mm_setzero_si128()));
#else
	const __m128i maskXY = _mm_srai_epi32(_mm_castpd_si128(m_quad.xy),31);
	const __m128i maskZW = _mm_srai_epi32(_mm_castpd_si128(m_quad.zw),31);
	const __m128i aXY = _mm_shuffle_epi32(maskXY, _MM_SHUFFLE(3,3,1,1)); // no srai_epi64
	const __m128i aZW = _mm_shuffle_epi32(maskZW, _MM_SHUFFLE(3,3,1,1));
	mask.m_mask.xy = _mm_castsi128_pd(_mm_cmpeq_epi32(aXY,_mm_setzero_si128()));
	mask.m_mask.zw = _mm_castsi128_pd(_mm_cmpeq_epi32(aZW,_mm_setzero_si128()));
#endif
	return mask;
}

HK_FORCE_INLINE void hkVector4d::setFlipSign(hkVector4dParameter v, hkVector4dComparisonParameter mask)
{
	const __m128i maskXY = _mm_slli_epi64(_mm_srli_epi64(_mm_castpd_si128(mask.m_mask.xy),63),63);
	const __m128i maskZW = _mm_slli_epi64(_mm_srli_epi64(_mm_castpd_si128(mask.m_mask.zw),63),63);
	m_quad.xy = _mm_xor_pd(v.m_quad.xy, _mm_castsi128_pd(maskXY));
	m_quad.zw = _mm_xor_pd(v.m_quad.zw, _mm_castsi128_pd(maskZW));
}

HK_FORCE_INLINE void hkVector4d::setFlipSign(hkVector4dParameter v, hkVector4dParameter vSign)
{
	const __m128i maskXY = _mm_slli_epi64(_mm_srli_epi64(_mm_castpd_si128(vSign.m_quad.xy),63),63);
	const __m128i maskZW = _mm_slli_epi64(_mm_srli_epi64(_mm_castpd_si128(vSign.m_quad.zw),63),63);
	m_quad.xy = _mm_xor_pd(v.m_quad.xy, _mm_castsi128_pd(maskXY));
	m_quad.zw = _mm_xor_pd(v.m_quad.zw, _mm_castsi128_pd(maskZW));
}

HK_FORCE_INLINE void hkVector4d::setFlipSign(hkVector4dParameter v, hkSimdDouble64Parameter sSign)
{
	const __m128i mask = _mm_slli_epi64(_mm_srli_epi64(_mm_castpd_si128(sSign.m_real),63),63);
	m_quad.xy = _mm_xor_pd(v.m_quad.xy, _mm_castsi128_pd(mask));
	m_quad.zw = _mm_xor_pd(v.m_quad.zw, _mm_castsi128_pd(mask));
}



//
// advanced interface
//

namespace hkVector4_AdvancedInterface
{

template <hkMathAccuracyMode A, hkMathDivByZeroMode D>
struct unrolld_setReciprocal { HK_FORCE_INLINE static void apply(hkQuadDouble64& self, hkVector4dParameter a)
{
	HK_VECTOR4d_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <hkMathAccuracyMode A>
struct unrolld_setReciprocal<A, HK_DIV_IGNORE> { HK_FORCE_INLINE static void apply(hkQuadDouble64& self, hkVector4dParameter a)
{
	switch (A)
	{
		case HK_ACC_23_BIT: 
			{
				self = hkMath::quadReciprocal(a.m_quad); 
			}
			break;
		case HK_ACC_12_BIT: 
			{
				const __m128 xy = _mm_cvtpd_ps(a.m_quad.xy);
				const __m128 zw = _mm_cvtpd_ps(a.m_quad.zw);
				const __m128 xyzw = _mm_shuffle_ps(xy,zw,_MM_SHUFFLE(1,0,1,0));
				const __m128 re = _mm_rcp_ps(xyzw);
				self.xy = _mm_cvtps_pd(re);
				self.zw = _mm_cvtps_pd(_mm_shuffle_ps(re,re,_MM_SHUFFLE(1,0,3,2)));
			}
			break;
		default:         
			{
				self.xy = _mm_div_pd(g_vectordConstants[HK_QUADREAL_1].xy, a.m_quad.xy);
				self.zw = _mm_div_pd(g_vectordConstants[HK_QUADREAL_1].xy, a.m_quad.zw);
			}
			break; // HK_ACC_FULL
	}
} };
template <hkMathAccuracyMode A>
struct unrolld_setReciprocal<A, HK_DIV_SET_ZERO> { HK_FORCE_INLINE static void apply(hkQuadDouble64& self, hkVector4dParameter a)
{
	const __m128d equalsZeroXY = _mm_cmpeq_pd(a.m_quad.xy, _mm_setzero_pd());
	const __m128d equalsZeroZW = _mm_cmpeq_pd(a.m_quad.zw, _mm_setzero_pd());
	hkQuadDouble64 e; unrolld_setReciprocal<A, HK_DIV_IGNORE>::apply(e, a);
	self.xy = _mm_andnot_pd(equalsZeroXY, e.xy);
	self.zw = _mm_andnot_pd(equalsZeroZW, e.zw);
} };
template <hkMathAccuracyMode A>
struct unrolld_setReciprocal<A, HK_DIV_SET_HIGH> { HK_FORCE_INLINE static void apply(hkQuadDouble64& self, hkVector4dParameter a)
{
	const __m128d equalsZeroXY = _mm_cmpeq_pd(a.m_quad.xy, _mm_setzero_pd());
	const __m128d equalsZeroZW = _mm_cmpeq_pd(a.m_quad.zw, _mm_setzero_pd());
	hkQuadDouble64 e; unrolld_setReciprocal<A, HK_DIV_IGNORE>::apply(e, a);
	const __m128d huge = _mm_set1_pd(HK_DOUBLE_HIGH);
	const __m128i maskXY = _mm_slli_epi64(_mm_srli_epi64(_mm_castpd_si128(a.m_quad.xy),63),63);
	const __m128i maskZW = _mm_slli_epi64(_mm_srli_epi64(_mm_castpd_si128(a.m_quad.zw),63),63);
	const __m128d hugeXY = _mm_xor_pd(huge, _mm_castsi128_pd(maskXY));
	const __m128d hugeZW = _mm_xor_pd(huge, _mm_castsi128_pd(maskZW));
#if HK_SSE_VERSION >= 0x41
	self.xy = _mm_blendv_pd(e.xy, hugeXY, equalsZeroXY);
	self.zw = _mm_blendv_pd(e.zw, hugeZW, equalsZeroZW);
#else
	self.xy = _mm_or_pd( _mm_and_pd(equalsZeroXY, hugeXY), _mm_andnot_pd(equalsZeroXY, e.xy) );
	self.zw = _mm_or_pd( _mm_and_pd(equalsZeroZW, hugeZW), _mm_andnot_pd(equalsZeroZW, e.zw) );
#endif
} };
template <hkMathAccuracyMode A>
struct unrolld_setReciprocal<A, HK_DIV_SET_MAX> { HK_FORCE_INLINE static void apply(hkQuadDouble64& self, hkVector4dParameter a)
{
	const __m128d equalsZeroXY = _mm_cmpeq_pd(a.m_quad.xy, _mm_setzero_pd());
	const __m128d equalsZeroZW = _mm_cmpeq_pd(a.m_quad.zw, _mm_setzero_pd());
	hkQuadDouble64 e; unrolld_setReciprocal<A, HK_DIV_IGNORE>::apply(e, a);
	const __m128d huge = _mm_set1_pd(HK_DOUBLE_MAX);
	const __m128i maskXY = _mm_slli_epi64(_mm_srli_epi64(_mm_castpd_si128(a.m_quad.xy),63),63);
	const __m128i maskZW = _mm_slli_epi64(_mm_srli_epi64(_mm_castpd_si128(a.m_quad.zw),63),63);
	const __m128d hugeXY = _mm_xor_pd(huge, _mm_castsi128_pd(maskXY));
	const __m128d hugeZW = _mm_xor_pd(huge, _mm_castsi128_pd(maskZW));
#if HK_SSE_VERSION >= 0x41
	self.xy = _mm_blendv_pd(e.xy, hugeXY, equalsZeroXY);
	self.zw = _mm_blendv_pd(e.zw, hugeZW, equalsZeroZW);
#else
	self.xy = _mm_or_pd( _mm_and_pd(equalsZeroXY, hugeXY), _mm_andnot_pd(equalsZeroXY, e.xy) );
	self.zw = _mm_or_pd( _mm_and_pd(equalsZeroZW, hugeZW), _mm_andnot_pd(equalsZeroZW, e.zw) );
#endif
} };
template <hkMathAccuracyMode A>
struct unrolld_setReciprocal<A, HK_DIV_SET_ZERO_AND_ONE> { HK_FORCE_INLINE static void apply(hkQuadDouble64& self, hkVector4dParameter a)
{
	unrolld_setReciprocal<A, HK_DIV_SET_ZERO>::apply(self, a);
	const __m128d one = g_vectordConstants[HK_QUADREAL_1].xy;
	const __m128d eps = g_vectordConstants[HK_QUADREAL_EPS].xy;
	const __m128d absValXY = hkMath::twoFabs(_mm_sub_pd(self.xy, one));
	const __m128d absValZW = hkMath::twoFabs(_mm_sub_pd(self.zw, one));
	const __m128d lessEqualEpsXY = _mm_cmple_pd(absValXY, eps);
	const __m128d lessEqualEpsZW = _mm_cmple_pd(absValZW, eps);
#if HK_SSE_VERSION >= 0x41
	self.xy = _mm_blendv_pd(self.xy, one, lessEqualEpsXY);
	self.zw = _mm_blendv_pd(self.zw, one, lessEqualEpsZW);
#else
	self.xy = _mm_or_pd( _mm_and_pd(lessEqualEpsXY, one), _mm_andnot_pd(lessEqualEpsXY, self.xy) );
	self.zw = _mm_or_pd( _mm_and_pd(lessEqualEpsZW, one), _mm_andnot_pd(lessEqualEpsZW, self.zw) );
#endif
} };

} // namespace 

template <hkMathAccuracyMode A, hkMathDivByZeroMode D>
HK_FORCE_INLINE void hkVector4d::setReciprocal(hkVector4dParameter a)
{
	hkVector4_AdvancedInterface::unrolld_setReciprocal<A,D>::apply(m_quad,a);
}

HK_FORCE_INLINE void hkVector4d::setReciprocal(hkVector4dParameter a)
{
	hkVector4_AdvancedInterface::unrolld_setReciprocal<HK_ACC_23_BIT,HK_DIV_IGNORE>::apply(m_quad,a);
}



namespace hkVector4_AdvancedInterface
{

template <hkMathAccuracyMode A, hkMathDivByZeroMode D>
struct unrolld_setDiv { HK_FORCE_INLINE static void apply(hkQuadDouble64& self, hkVector4dParameter a, hkVector4dParameter b)
{
	HK_VECTOR4d_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <hkMathAccuracyMode A>
struct unrolld_setDiv<A, HK_DIV_IGNORE> { HK_FORCE_INLINE static void apply(hkQuadDouble64& self, hkVector4dParameter a, hkVector4dParameter b)
{
	switch (A)
	{
		case HK_ACC_23_BIT: 
			{
				const hkQuadDouble64 re = hkMath::quadReciprocal(b.m_quad); 
				self.xy = _mm_mul_pd(a.m_quad.xy,re.xy); 
				self.zw = _mm_mul_pd(a.m_quad.zw,re.zw); 
			}
			break;
		case HK_ACC_12_BIT: 
			{
				const __m128 xy = _mm_cvtpd_ps(b.m_quad.xy);
				const __m128 zw = _mm_cvtpd_ps(b.m_quad.zw);
				const __m128 xyzw = _mm_shuffle_ps(xy,zw,_MM_SHUFFLE(1,0,1,0));
				const __m128 re = _mm_rcp_ps(xyzw);
				self.xy = _mm_mul_pd(a.m_quad.xy,_mm_cvtps_pd(re));
				self.zw = _mm_mul_pd(a.m_quad.zw,_mm_cvtps_pd(_mm_shuffle_ps(re,re,_MM_SHUFFLE(1,0,3,2))));
			}
			break;
		default:         
			{
				self.xy = _mm_div_pd(a.m_quad.xy, b.m_quad.xy);
				self.zw = _mm_div_pd(a.m_quad.zw, b.m_quad.zw);
			}
			break; // HK_ACC_FULL
	}
} };
template <hkMathAccuracyMode A>
struct unrolld_setDiv<A, HK_DIV_SET_ZERO> { HK_FORCE_INLINE static void apply(hkQuadDouble64& self, hkVector4dParameter a, hkVector4dParameter b)
{
	const __m128d equalsZeroXY = _mm_cmpeq_pd(b.m_quad.xy, _mm_setzero_pd());
	const __m128d equalsZeroZW = _mm_cmpeq_pd(b.m_quad.zw, _mm_setzero_pd());
	hkQuadDouble64 e; unrolld_setDiv<A, HK_DIV_IGNORE>::apply(e,a,b);
	self.xy = _mm_andnot_pd(equalsZeroXY, e.xy);
	self.zw = _mm_andnot_pd(equalsZeroZW, e.zw);
} };
template <hkMathAccuracyMode A>
struct unrolld_setDiv<A, HK_DIV_SET_HIGH> { HK_FORCE_INLINE static void apply(hkQuadDouble64& self, hkVector4dParameter a, hkVector4dParameter b)
{
	const __m128d equalsZeroXY = _mm_cmpeq_pd(b.m_quad.xy, _mm_setzero_pd());
	const __m128d equalsZeroZW = _mm_cmpeq_pd(b.m_quad.zw, _mm_setzero_pd());
	hkQuadDouble64 e; unrolld_setDiv<A, HK_DIV_IGNORE>::apply(e, a, b);
	const __m128d huge = _mm_set1_pd(HK_DOUBLE_HIGH);
	const __m128i maskXY = _mm_slli_epi64(_mm_srli_epi64(_mm_castpd_si128(a.m_quad.xy),63),63);
	const __m128i maskZW = _mm_slli_epi64(_mm_srli_epi64(_mm_castpd_si128(a.m_quad.zw),63),63);
	const __m128d hugeXY = _mm_xor_pd(huge, _mm_castsi128_pd(maskXY));
	const __m128d hugeZW = _mm_xor_pd(huge, _mm_castsi128_pd(maskZW));
#if HK_SSE_VERSION >= 0x41
	self.xy = _mm_blendv_pd(e.xy, hugeXY, equalsZeroXY);
	self.zw = _mm_blendv_pd(e.zw, hugeZW, equalsZeroZW);
#else
	self.xy = _mm_or_pd( _mm_and_pd(equalsZeroXY, hugeXY), _mm_andnot_pd(equalsZeroXY, e.xy) );
	self.zw = _mm_or_pd( _mm_and_pd(equalsZeroZW, hugeZW), _mm_andnot_pd(equalsZeroZW, e.zw) );
#endif
} };
template <hkMathAccuracyMode A>
struct unrolld_setDiv<A, HK_DIV_SET_MAX> { HK_FORCE_INLINE static void apply(hkQuadDouble64& self, hkVector4dParameter a, hkVector4dParameter b)
{
	const __m128d equalsZeroXY = _mm_cmpeq_pd(b.m_quad.xy, _mm_setzero_pd());
	const __m128d equalsZeroZW = _mm_cmpeq_pd(b.m_quad.zw, _mm_setzero_pd());
	hkQuadDouble64 e; unrolld_setDiv<A, HK_DIV_IGNORE>::apply(e, a, b);
	const __m128d huge = _mm_set1_pd(HK_DOUBLE_MAX);
	const __m128i maskXY = _mm_slli_epi64(_mm_srli_epi64(_mm_castpd_si128(a.m_quad.xy),63),63);
	const __m128i maskZW = _mm_slli_epi64(_mm_srli_epi64(_mm_castpd_si128(a.m_quad.zw),63),63);
	const __m128d hugeXY = _mm_xor_pd(huge, _mm_castsi128_pd(maskXY));
	const __m128d hugeZW = _mm_xor_pd(huge, _mm_castsi128_pd(maskZW));
#if HK_SSE_VERSION >= 0x41
	self.xy = _mm_blendv_pd(e.xy, hugeXY, equalsZeroXY);
	self.zw = _mm_blendv_pd(e.zw, hugeZW, equalsZeroZW);
#else
	self.xy = _mm_or_pd( _mm_and_pd(equalsZeroXY, hugeXY), _mm_andnot_pd(equalsZeroXY, e.xy) );
	self.zw = _mm_or_pd( _mm_and_pd(equalsZeroZW, hugeZW), _mm_andnot_pd(equalsZeroZW, e.zw) );
#endif
} };
template <hkMathAccuracyMode A>
struct unrolld_setDiv<A, HK_DIV_SET_ZERO_AND_ONE> { HK_FORCE_INLINE static void apply(hkQuadDouble64& self, hkVector4dParameter a, hkVector4dParameter b)
{
	unrolld_setDiv<A, HK_DIV_SET_ZERO>::apply(self, a, b);
	const __m128d one = g_vectordConstants[HK_QUADREAL_1].xy;
	const __m128d eps = g_vectordConstants[HK_QUADREAL_EPS].xy;
	const __m128d absValXY = hkMath::twoFabs(_mm_sub_pd(self.xy, one));
	const __m128d absValZW = hkMath::twoFabs(_mm_sub_pd(self.zw, one));
	const __m128d lessEqualEpsXY = _mm_cmple_pd(absValXY, eps);
	const __m128d lessEqualEpsZW = _mm_cmple_pd(absValZW, eps);
#if HK_SSE_VERSION >= 0x41
	self.xy = _mm_blendv_pd(self.xy, one, lessEqualEpsXY);
	self.zw = _mm_blendv_pd(self.zw, one, lessEqualEpsZW);
#else
	self.xy = _mm_or_pd( _mm_and_pd(lessEqualEpsXY, one), _mm_andnot_pd(lessEqualEpsXY, self.xy) );
	self.zw = _mm_or_pd( _mm_and_pd(lessEqualEpsZW, one), _mm_andnot_pd(lessEqualEpsZW, self.zw) );
#endif
} };

} // namespace 

template <hkMathAccuracyMode A, hkMathDivByZeroMode D>
HK_FORCE_INLINE void hkVector4d::setDiv(hkVector4dParameter v0, hkVector4dParameter v1)
{
	hkVector4_AdvancedInterface::unrolld_setDiv<A,D>::apply(m_quad,v0,v1);
}

HK_FORCE_INLINE void hkVector4d::setDiv(hkVector4dParameter v0, hkVector4dParameter v1)
{
	hkVector4_AdvancedInterface::unrolld_setDiv<HK_ACC_23_BIT,HK_DIV_IGNORE>::apply(m_quad,v0,v1);
}

template <hkMathAccuracyMode A, hkMathDivByZeroMode D>
HK_FORCE_INLINE void hkVector4d::div(hkVector4dParameter a)
{
	setDiv<A,D>( *this, a );
}

HK_FORCE_INLINE void hkVector4d::div(hkVector4dParameter a)
{
	setDiv( *this, a );
}



namespace hkVector4_AdvancedInterface
{

template <hkMathAccuracyMode A, hkMathNegSqrtMode S>
struct unrolld_setSqrt { HK_FORCE_INLINE static void apply(hkQuadDouble64& self, hkVector4dParameter a)
{
	HK_VECTOR4d_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <hkMathAccuracyMode A>
struct unrolld_setSqrt<A, HK_SQRT_IGNORE> { HK_FORCE_INLINE static void apply(hkQuadDouble64& self, hkVector4dParameter a)
{
	switch (A)
	{
		case HK_ACC_23_BIT: 
			{
				const hkQuadDouble64 re = hkMath::quadReciprocalSquareRoot(a.m_quad); 
				self.xy = _mm_mul_pd(a.m_quad.xy,re.xy); 
				self.zw = _mm_mul_pd(a.m_quad.zw,re.zw); 
			}
			break;
		case HK_ACC_12_BIT: 
			{
				const __m128 xy = _mm_cvtpd_ps(a.m_quad.xy);
				const __m128 zw = _mm_cvtpd_ps(a.m_quad.zw);
				const __m128 xyzw = _mm_shuffle_ps(xy,zw,_MM_SHUFFLE(1,0,1,0));
				const __m128 re = _mm_rsqrt_ps(xyzw);
				self.xy = _mm_mul_pd(a.m_quad.xy,_mm_cvtps_pd(re));
				self.zw = _mm_mul_pd(a.m_quad.zw,_mm_cvtps_pd(_mm_shuffle_ps(re,re,_MM_SHUFFLE(1,0,3,2))));
			}
			break;
		default:         
			{
				self.xy = _mm_sqrt_pd(a.m_quad.xy); 
				self.zw = _mm_sqrt_pd(a.m_quad.zw); 
			}
			break; // HK_ACC_FULL
	}
} };
template <hkMathAccuracyMode A>
struct unrolld_setSqrt<A, HK_SQRT_SET_ZERO> { HK_FORCE_INLINE static void apply(hkQuadDouble64& self, hkVector4dParameter a)
{
	const __m128d equalsZeroXY = _mm_cmple_pd(a.m_quad.xy, _mm_setzero_pd());
	const __m128d equalsZeroZW = _mm_cmple_pd(a.m_quad.zw, _mm_setzero_pd());
	hkQuadDouble64 e; unrolld_setSqrt<A, HK_SQRT_IGNORE>::apply(e,a);
	self.xy = _mm_andnot_pd(equalsZeroXY, e.xy);
	self.zw = _mm_andnot_pd(equalsZeroZW, e.zw);
} };

} // namespace 

template <hkMathAccuracyMode A, hkMathNegSqrtMode S>
HK_FORCE_INLINE void hkVector4d::setSqrt(hkVector4dParameter a)
{
	hkVector4_AdvancedInterface::unrolld_setSqrt<A,S>::apply(m_quad, a);
}

HK_FORCE_INLINE void hkVector4d::setSqrt(hkVector4dParameter a)
{
	hkVector4_AdvancedInterface::unrolld_setSqrt<HK_ACC_23_BIT,HK_SQRT_SET_ZERO>::apply(m_quad, a);
}



namespace hkVector4_AdvancedInterface
{

template <hkMathAccuracyMode A, hkMathNegSqrtMode S>
struct unrolld_setSqrtInverse { HK_FORCE_INLINE static void apply(hkQuadDouble64& self, hkVector4dParameter a)
{
	HK_VECTOR4d_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <hkMathAccuracyMode A>
struct unrolld_setSqrtInverse<A, HK_SQRT_IGNORE> { HK_FORCE_INLINE static void apply(hkQuadDouble64& self, hkVector4dParameter a)
{
	switch (A)
	{
		case HK_ACC_23_BIT: 
			{
				self = hkMath::quadReciprocalSquareRoot(a.m_quad); 
			}
			break;
		case HK_ACC_12_BIT: 
			{
				const __m128 xy = _mm_cvtpd_ps(a.m_quad.xy);
				const __m128 zw = _mm_cvtpd_ps(a.m_quad.zw);
				const __m128 xyzw = _mm_shuffle_ps(xy,zw,_MM_SHUFFLE(1,0,1,0));
				const __m128 re = _mm_rsqrt_ps(xyzw);
				self.xy = _mm_cvtps_pd(re);
				self.zw = _mm_cvtps_pd(_mm_shuffle_ps(re,re,_MM_SHUFFLE(1,0,3,2)));
			}
			break;
		default:         
			{
				self.xy = _mm_div_pd(g_vectordConstants[HK_QUADREAL_1].xy, _mm_sqrt_pd(a.m_quad.xy));
				self.zw = _mm_div_pd(g_vectordConstants[HK_QUADREAL_1].xy, _mm_sqrt_pd(a.m_quad.zw));
			}
			break; // HK_ACC_FULL
	}
} };
template <hkMathAccuracyMode A>
struct unrolld_setSqrtInverse<A, HK_SQRT_SET_ZERO> { HK_FORCE_INLINE static void apply(hkQuadDouble64& self, hkVector4dParameter a)
{
	const __m128d equalsZeroXY = _mm_cmple_pd(a.m_quad.xy, _mm_setzero_pd());
	const __m128d equalsZeroZW = _mm_cmple_pd(a.m_quad.zw, _mm_setzero_pd());
	hkQuadDouble64 e; unrolld_setSqrtInverse<A, HK_SQRT_IGNORE>::apply(e,a);
	self.xy = _mm_andnot_pd(equalsZeroXY, e.xy);
	self.zw = _mm_andnot_pd(equalsZeroZW, e.zw);
} };
} // namespace 

template <hkMathAccuracyMode A, hkMathNegSqrtMode S>
HK_FORCE_INLINE void hkVector4d::setSqrtInverse(hkVector4dParameter a)
{
	hkVector4_AdvancedInterface::unrolld_setSqrtInverse<A,S>::apply(m_quad,a);
}

HK_FORCE_INLINE void hkVector4d::setSqrtInverse(hkVector4dParameter a)
{
	hkVector4_AdvancedInterface::unrolld_setSqrtInverse<HK_ACC_23_BIT,HK_SQRT_SET_ZERO>::apply(m_quad,a);
}



namespace hkVector4_AdvancedInterface
{
template <int N, hkMathIoMode A>
struct unrolld_load { HK_FORCE_INLINE static void apply(hkQuadDouble64& self, const hkFloat32* HK_RESTRICT p)
{
	HK_VECTOR4d_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <int N, hkMathIoMode A>
struct unrolld_load_D { HK_FORCE_INLINE static void apply(hkQuadDouble64& self, const hkDouble64* HK_RESTRICT p)
{
	HK_VECTOR4d_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <int N>
struct unrolld_load<N, HK_IO_BYTE_ALIGNED> { HK_FORCE_INLINE static void apply(hkQuadDouble64& self, const hkFloat32* HK_RESTRICT p)
{
	switch (N)
	{
	case 1:
		{
			__m128 a = _mm_load_ss(p);
			self.xy = _mm_cvtps_pd(a);
			HK_ON_DEBUG( *(hkUint64*)&(HK_M128(self.xy).m128d_f64[1]) = 0xffffffffffffffff; )
			HK_ON_DEBUG( *(hkUint64*)&(HK_M128(self.zw).m128d_f64[0]) = 0xffffffffffffffff; *(hkUint64*)&(HK_M128(self.zw).m128d_f64[1]) = 0xffffffffffffffff; )
		}
		break;
	case 2:
		{
			__m128d a = _mm_load_sd((const double*)p);
			self.xy = _mm_cvtps_pd(_mm_castpd_ps(a));
			HK_ON_DEBUG( *(hkUint64*)&(HK_M128(self.zw).m128d_f64[0]) = 0xffffffffffffffff; *(hkUint64*)&(HK_M128(self.zw).m128d_f64[1]) = 0xffffffffffffffff; )
		}
		break;
	case 3:
		{
			__m128d a = _mm_load_sd((const double*)p);
			__m128 b = _mm_load_ss(p+2);
			self.xy = _mm_cvtps_pd(_mm_castpd_ps(a));
			self.zw = _mm_cvtps_pd(b);
			HK_ON_DEBUG( *(hkUint64*)&(HK_M128(self.zw).m128d_f64[1]) = 0xffffffffffffffff; )
		}
		break;
	default:
		{
#if HK_SSE_VERSION >= 0x30
			__m128 a = _mm_castsi128_ps(_mm_lddqu_si128((const __m128i*)p));
#else
			__m128 a = _mm_loadu_ps(p);
#endif
			self.xy = _mm_cvtps_pd(a);
			self.zw = _mm_cvtps_pd(_mm_shuffle_ps(a,a,_MM_SHUFFLE(1,0,3,2)));
		}
		break;
	}
} };
template <int N>
struct unrolld_load_D<N, HK_IO_BYTE_ALIGNED> { HK_FORCE_INLINE static void apply(hkQuadDouble64& self, const hkDouble64* HK_RESTRICT p)
{
	switch (N)
	{
	case 1:
		{
			self.xy = _mm_load_sd(p);
			HK_ON_DEBUG( *(hkUint64*)&(HK_M128(self.xy).m128d_f64[1]) = 0xffffffffffffffff; )
			HK_ON_DEBUG( *(hkUint64*)&(HK_M128(self.zw).m128d_f64[0]) = 0xffffffffffffffff; *(hkUint64*)&(HK_M128(self.zw).m128d_f64[1]) = 0xffffffffffffffff; )
		}
		break;
	case 2:
		{
#if HK_SSE_VERSION >= 0x30
			self.xy = _mm_castsi128_pd(_mm_lddqu_si128((const __m128i*)p));
#else
			self.xy = _mm_loadu_pd(p);
#endif
			HK_ON_DEBUG( *(hkUint64*)&(HK_M128(self.zw).m128d_f64[0]) = 0xffffffffffffffff; *(hkUint64*)&(HK_M128(self.zw).m128d_f64[1]) = 0xffffffffffffffff; )
		}
		break;
	case 3:
		{
#if HK_SSE_VERSION >= 0x30
			self.xy = _mm_castsi128_pd(_mm_lddqu_si128((const __m128i*)p));
#else
			self.xy = _mm_loadu_pd(p);
#endif
			self.zw = _mm_load_sd(p+2);
			HK_ON_DEBUG( *(hkUint64*)&(HK_M128(self.zw).m128d_f64[1]) = 0xffffffffffffffff; )
		}
		break;
	default:
		{
#if HK_SSE_VERSION >= 0x30
			self.xy = _mm_castsi128_pd(_mm_lddqu_si128((const __m128i*)p));
			self.zw = _mm_castsi128_pd(_mm_lddqu_si128((const __m128i*)(p+2)));
#else
			self.xy = _mm_loadu_pd(p);
			self.zw = _mm_loadu_pd(p+2);
#endif
		}
		break;
	}
} };
template <int N>
struct unrolld_load<N, HK_IO_NATIVE_ALIGNED> { HK_FORCE_INLINE static void apply(hkQuadDouble64& self, const hkFloat32* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & (sizeof(hkFloat32)-1) ) == 0, "pointer must be aligned to native size of hkFloat32.");
	unrolld_load<N, HK_IO_BYTE_ALIGNED>::apply(self,p);
} };
template <int N>
struct unrolld_load_D<N, HK_IO_NATIVE_ALIGNED> { HK_FORCE_INLINE static void apply(hkQuadDouble64& self, const hkDouble64* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & (sizeof(hkDouble64)-1) ) == 0, "pointer must be aligned to native size of hkDouble64.");
	unrolld_load_D<N, HK_IO_BYTE_ALIGNED>::apply(self,p);
} };
template <int N>
struct unrolld_load<N, HK_IO_SIMD_ALIGNED> { HK_FORCE_INLINE static void apply(hkQuadDouble64& self, const hkFloat32* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & ((sizeof(hkFloat32)*(N!=3?N:4) )-1) ) == 0, "pointer must be aligned for SIMD.");
	if (N==4)
	{
		__m128 a = _mm_load_ps(p);
		self.xy = _mm_cvtps_pd(a);
		self.zw = _mm_cvtps_pd(_mm_shuffle_ps(a,a,_MM_SHUFFLE(1,0,3,2)));
	}
	else
	{
		unrolld_load<N, HK_IO_NATIVE_ALIGNED>::apply(self,p);
	}
} };
template <int N>
struct unrolld_load_D<N, HK_IO_SIMD_ALIGNED> { HK_FORCE_INLINE static void apply(hkQuadDouble64& self, const hkDouble64* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & ((sizeof(hkDouble64)*(N!=3?N:4) )-1) ) == 0, "pointer must be aligned for SIMD.");
	switch (N)
	{
	case 2:
		{
			self.xy = _mm_load_pd(p);
			HK_ON_DEBUG( *(hkUint64*)&(HK_M128(self.zw).m128d_f64[0]) = 0xffffffffffffffff; *(hkUint64*)&(HK_M128(self.zw).m128d_f64[1]) = 0xffffffffffffffff; )
		}
		break;
	case 3:
		{
			self.xy = _mm_load_pd(p);
			self.zw = _mm_load_sd(p+2);
			HK_ON_DEBUG( *(hkUint64*)&(HK_M128(self.zw).m128d_f64[1]) = 0xffffffffffffffff; )
		}
		break;
	case 4:
		{
			self.xy = _mm_load_pd(p);
			self.zw = _mm_load_pd(p+2);
		}
		break;
	default:
		{
			unrolld_load_D<N, HK_IO_NATIVE_ALIGNED>::apply(self,p);
		}
		break;
	}
} };
template <int N>
struct unrolld_load<N, HK_IO_NOT_CACHED> { HK_FORCE_INLINE static void apply(hkQuadDouble64& self, const hkFloat32* HK_RESTRICT p)
{
#if HK_SSE_VERSION >= 0x41
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & ((sizeof(hkFloat32)*(N!=3?N:4) )-1) ) == 0, "pointer must be aligned for SIMD.");
	if (N==4)
	{
		__m128 a = _mm_castsi128_ps(_mm_stream_load_si128((__m128i*) p));
		self.xy = _mm_cvtps_pd(a);
		self.zw = _mm_cvtps_pd(_mm_shuffle_ps(a,a,_MM_SHUFFLE(1,0,3,2)));
	}
	else
	{
		unrolld_load<N, HK_IO_SIMD_ALIGNED>::apply(self,p);
	}
#else
	unrolld_load<N, HK_IO_SIMD_ALIGNED>::apply(self,p);
#endif
} };
template <int N>
struct unrolld_load_D<N, HK_IO_NOT_CACHED> { HK_FORCE_INLINE static void apply(hkQuadDouble64& self, const hkDouble64* HK_RESTRICT p)
{
#if HK_SSE_VERSION >= 0x41
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & ((sizeof(hkDouble64)*(N!=3?N:4) )-1) ) == 0, "pointer must be aligned for SIMD.");
	switch (N)
	{
	case 2:
		{
			self.xy = _mm_castsi128_pd(_mm_stream_load_si128((__m128i*) p));
			HK_ON_DEBUG( *(hkUint64*)&(HK_M128(self.zw).m128d_f64[0]) = 0xffffffffffffffff; *(hkUint64*)&(HK_M128(self.zw).m128d_f64[1]) = 0xffffffffffffffff; )
		}
		break;
	case 3:
		{
			self.xy = _mm_castsi128_pd(_mm_stream_load_si128((__m128i*) p));
			self.zw = _mm_load_sd(p+2);
			HK_ON_DEBUG( *(hkUint64*)&(HK_M128(self.zw).m128d_f64[1]) = 0xffffffffffffffff; )
		}
		break;
	case 4:
		{
			self.xy = _mm_castsi128_pd(_mm_stream_load_si128((__m128i*) p));
			self.zw = _mm_castsi128_pd(_mm_stream_load_si128((__m128i*)(p+2)));
		}
		break;
	default:
		{
			unrolld_load_D<N, HK_IO_SIMD_ALIGNED>::apply(self,p);
		}
		break;
	}
#else
	unrolld_load_D<N, HK_IO_SIMD_ALIGNED>::apply(self,p);
#endif
} };
} // namespace 

template <int N, hkMathIoMode A>
HK_FORCE_INLINE void hkVector4d::load(const hkFloat32* p)
{
	HK_VECTOR4d_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrolld_load<N,A>::apply(m_quad, p);
}

template <int N, hkMathIoMode A>
HK_FORCE_INLINE void hkVector4d::load(const hkDouble64* p)
{
	HK_VECTOR4d_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrolld_load_D<N,A>::apply(m_quad, p);
}

template <int N>
HK_FORCE_INLINE void hkVector4d::load(const hkFloat32* p)
{
	HK_VECTOR4d_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrolld_load<N,HK_IO_SIMD_ALIGNED>::apply(m_quad, p);
}

template <int N>
HK_FORCE_INLINE void hkVector4d::load(const hkDouble64* p)
{
	HK_VECTOR4d_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrolld_load_D<N,HK_IO_SIMD_ALIGNED>::apply(m_quad, p);
}




namespace hkVector4_AdvancedInterface
{
template <int N, hkMathIoMode A>
struct unrolld_loadH { HK_FORCE_INLINE static void apply(hkQuadDouble64& self, const hkHalf* HK_RESTRICT p)
{
	HK_VECTOR4d_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <int N>
struct unrolld_loadH<N, HK_IO_BYTE_ALIGNED> { HK_FORCE_INLINE static void apply(hkQuadDouble64& self, const hkHalf* HK_RESTRICT p)
{
#if defined(HK_HALF_IS_FLOAT)
	switch (N)
	{
	case 1:
		{
			__m128 twofloats = _mm_load_ss((const float*)p);
			self.xy = _mm_cvtps_pd(twofloats);
			HK_ON_DEBUG( *(hkUint64*)&(HK_M128(self.xy).m128d_f64[1]) = 0xffffffffffffffff; )
			HK_ON_DEBUG( *(hkUint64*)&(HK_M128(self.zw).m128d_f64[0]) = 0xffffffffffffffff; *(hkUint64*)&(HK_M128(self.zw).m128d_f64[1]) = 0xffffffffffffffff; )
		}
		break;
	case 2:
		{
			__m128  twofloats = _mm_castpd_ps(_mm_load_sd((const double*)p));
			self.xy = _mm_cvtps_pd(twofloats);
			HK_ON_DEBUG( *(hkUint64*)&(HK_M128(self.zw).m128d_f64[0]) = 0xffffffffffffffff; *(hkUint64*)&(HK_M128(self.zw).m128d_f64[1]) = 0xffffffffffffffff; )
		}
		break;
	case 3:
		{
			__m128 xy = _mm_castpd_ps(_mm_load_sd((const double*)p));
			__m128 z = _mm_load_ss((const float*)p+2);
			__m128  fourfloats = _mm_movelh_ps(xy,z);
			self.xy = _mm_cvtps_pd(fourfloats);
			self.zw = _mm_cvtps_pd(_mm_shuffle_ps(fourfloats,fourfloats,_MM_SHUFFLE(1,0,3,2)));
			HK_ON_DEBUG( *(hkUint64*)&(HK_M128(self.zw).m128d_f64[1]) = 0xffffffffffffffff; )
		}
		break;
	default:
		{
#if HK_SSE_VERSION >= 0x30
			__m128  fourfloats = _mm_castsi128_ps(_mm_lddqu_si128((const __m128i*)p));
#else
			__m128  fourfloats = _mm_loadu_ps((const float*)p);
#endif
			self.xy = _mm_cvtps_pd(fourfloats);
			self.zw = _mm_cvtps_pd(_mm_shuffle_ps(fourfloats,fourfloats,_MM_SHUFFLE(1,0,3,2)));
		}
		break;
	}
#else
	switch (N)
	{
	case 1:
		{
			float x; p[0].store(&x);
			__m128 twofloats = _mm_set_ss(x);
			self.xy = _mm_cvtps_pd(twofloats);
			HK_ON_DEBUG( *(hkUint64*)&(HK_M128(self.xy).m128d_f64[1]) = 0xffffffffffffffff; )
			HK_ON_DEBUG( *(hkUint64*)&(HK_M128(self.zw).m128d_f64[0]) = 0xffffffffffffffff; *(hkUint64*)&(HK_M128(self.zw).m128d_f64[1]) = 0xffffffffffffffff; )
		}
		break;
	case 2:
		{
			__m128i twohalfs = _mm_castps_si128( _mm_load_ss((const float*)p) );
			__m128  twofloats = _mm_castsi128_ps( _mm_unpacklo_epi16(_mm_setzero_si128(), twohalfs) );
			self.xy = _mm_cvtps_pd(twofloats);
			HK_ON_DEBUG( *(hkUint64*)&(HK_M128(self.zw).m128d_f64[0]) = 0xffffffffffffffff; *(hkUint64*)&(HK_M128(self.zw).m128d_f64[1]) = 0xffffffffffffffff; )
		}
		break;
	case 3:
		{
			HK_ALIGN16(hkHalf tmp[4]);
			tmp[0] = p[0];
			tmp[1] = p[1];
			tmp[2] = p[2];
			__m128i fourhalfs = _mm_loadl_epi64((const __m128i*)tmp);
			__m128  fourfloats = _mm_castsi128_ps( _mm_unpacklo_epi16(_mm_setzero_si128(), fourhalfs) );
			self.xy = _mm_cvtps_pd(fourfloats);
			self.zw = _mm_cvtps_pd(_mm_shuffle_ps(fourfloats,fourfloats,_MM_SHUFFLE(1,0,3,2)));
			HK_ON_DEBUG( *(hkUint64*)&(HK_M128(self.zw).m128d_f64[1]) = 0xffffffffffffffff; )
		}
		break;
	default:
		{
			__m128i fourhalfs = _mm_castpd_si128(_mm_load_sd((const double*)p));
			__m128  fourfloats = _mm_castsi128_ps( _mm_unpacklo_epi16(_mm_setzero_si128(), fourhalfs) );
			self.xy = _mm_cvtps_pd(fourfloats);
			self.zw = _mm_cvtps_pd(_mm_shuffle_ps(fourfloats,fourfloats,_MM_SHUFFLE(1,0,3,2)));
		}
		break;
	}
#endif
} };
template <int N>
struct unrolld_loadH<N, HK_IO_NATIVE_ALIGNED> { HK_FORCE_INLINE static void apply(hkQuadDouble64& self, const hkHalf* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & (sizeof(hkHalf)-1) ) == 0, "pointer must be aligned to native size of hkHalf.");
	unrolld_loadH<N, HK_IO_BYTE_ALIGNED>::apply(self,p);
} };
template <int N>
struct unrolld_loadH<N, HK_IO_SIMD_ALIGNED> { HK_FORCE_INLINE static void apply(hkQuadDouble64& self, const hkHalf* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & ((sizeof(hkHalf)*(N!=3?N:4) )-1) ) == 0, "pointer must be aligned for SIMD.");
	switch (N)
	{
	case 4:
#if defined(HK_HALF_IS_FLOAT)
		{
			__m128  fourfloats = _mm_load_ps((const float*)p);
			self.xy = _mm_cvtps_pd(fourfloats);
			self.zw = _mm_cvtps_pd(_mm_shuffle_ps(fourfloats,fourfloats,_MM_SHUFFLE(1,0,3,2)));
		}
#else
		{
			__m128i fourhalfs = _mm_loadl_epi64((const __m128i*)p);
			__m128  fourfloats = _mm_castsi128_ps( _mm_unpacklo_epi16(_mm_setzero_si128(), fourhalfs) );
			self.xy = _mm_cvtps_pd(fourfloats);
			self.zw = _mm_cvtps_pd(_mm_shuffle_ps(fourfloats,fourfloats,_MM_SHUFFLE(1,0,3,2)));
		}
#endif
		break;
	default:
		{
			unrolld_loadH<N, HK_IO_NATIVE_ALIGNED>::apply(self,p);
		}
		break;
	}
} };
template <int N>
struct unrolld_loadH<N, HK_IO_NOT_CACHED> { HK_FORCE_INLINE static void apply(hkQuadDouble64& self, const hkHalf* HK_RESTRICT p)
{
#if defined(HK_HALF_IS_FLOAT)
#if HK_SSE_VERSION >= 0x41
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & ((sizeof(hkHalf)*(N!=3?N:4) )-1) ) == 0, "pointer must be aligned for SIMD.");
	switch (N)
	{
	case 4: 
		{
			__m128  fourfloats = _mm_castsi128_ps(_mm_stream_load_si128((__m128i*) p));
			self.xy = _mm_cvtps_pd(fourfloats);
			self.zw = _mm_cvtps_pd(_mm_shuffle_ps(fourfloats,fourfloats,_MM_SHUFFLE(1,0,3,2)));
		}
		break;
	default:
		{
			unrolld_loadH<N, HK_IO_SIMD_ALIGNED>::apply(self,p);
		}
		break;
	}
#else
	unrolld_loadH<N, HK_IO_SIMD_ALIGNED>::apply(self,p);
#endif
#else
	unrolld_loadH<N, HK_IO_SIMD_ALIGNED>::apply(self,p);
#endif
} };
} // namespace 

template <int N, hkMathIoMode A>
HK_FORCE_INLINE void hkVector4d::load(const hkHalf* p)
{
	HK_VECTOR4d_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrolld_loadH<N,A>::apply(m_quad, p);
}

template <int N>
HK_FORCE_INLINE void hkVector4d::load(const hkHalf* p)
{
	HK_VECTOR4d_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrolld_loadH<N,HK_IO_SIMD_ALIGNED>::apply(m_quad, p);
}



namespace hkVector4_AdvancedInterface
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
template <int N, hkMathIoMode A>
struct unrolld_loadF16 { HK_FORCE_INLINE static void apply(hkQuadDouble64& self, const hkFloat16* HK_RESTRICT p)
{
	HK_VECTOR4d_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <int N>
struct unrolld_loadF16<N, HK_IO_BYTE_ALIGNED> { HK_FORCE_INLINE static void apply(hkQuadDouble64& self, const hkFloat16* HK_RESTRICT p)
{
	__m128i r;
	switch (N)
	{
	case 1:
		{
			HK_ALIGN16(hkFloat16 tmp[2]);
			tmp[0] = p[0];
			r = _mm_castps_si128(_mm_load_ss((const float*)tmp));
		}
		break;
	case 2:
		{
			r = _mm_castps_si128(_mm_load_ss((const float*)p));
		}
		break;
	case 3:
		{
			HK_ALIGN16(hkFloat16 tmp[4]);
			tmp[0] = p[0];
			tmp[1] = p[1];
			tmp[2] = p[2];
			r = _mm_loadl_epi64((const __m128i*)tmp);
		}
		break;
	default:
		{
			r = _mm_castpd_si128(_mm_load_sd((const double*)p));
		}
		break;
	}

	__m128 fourfloats;
	unpackF16F32(r, fourfloats);

	switch (N)
	{
	case 1:
		{
			self.xy = _mm_cvtps_pd(fourfloats);
			HK_ON_DEBUG( *(hkUint64*)&(HK_M128(self.xy).m128d_f64[1]) = 0xffffffffffffffff; )
			HK_ON_DEBUG( *(hkUint64*)&(HK_M128(self.zw).m128d_f64[0]) = 0xffffffffffffffff; *(hkUint64*)&(HK_M128(self.zw).m128d_f64[1]) = 0xffffffffffffffff; )
		}
		break;
	case 2:
		{
			self.xy = _mm_cvtps_pd(fourfloats);
			HK_ON_DEBUG( *(hkUint64*)&(HK_M128(self.zw).m128d_f64[0]) = 0xffffffffffffffff; *(hkUint64*)&(HK_M128(self.zw).m128d_f64[1]) = 0xffffffffffffffff; )
		}
		break;
	case 3:
		{
			self.xy = _mm_cvtps_pd(fourfloats);
			self.zw = _mm_cvtps_pd(_mm_shuffle_ps(fourfloats,fourfloats,_MM_SHUFFLE(1,0,3,2)));
			HK_ON_DEBUG( *(hkUint64*)&(HK_M128(self.zw).m128d_f64[1]) = 0xffffffffffffffff; )
		}
		break;
	default:
		{
			self.xy = _mm_cvtps_pd(fourfloats);
			self.zw = _mm_cvtps_pd(_mm_shuffle_ps(fourfloats,fourfloats,_MM_SHUFFLE(1,0,3,2)));
		}
		break;
	}
} };
template <int N>
struct unrolld_loadF16<N, HK_IO_NATIVE_ALIGNED> { HK_FORCE_INLINE static void apply(hkQuadDouble64& self, const hkFloat16* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & (sizeof(hkFloat16)-1) ) == 0, "pointer must be aligned to native size of hkFloat16.");
	unrolld_loadF16<N, HK_IO_BYTE_ALIGNED>::apply(self,p);
} };
template <int N>
struct unrolld_loadF16<N, HK_IO_SIMD_ALIGNED> { HK_FORCE_INLINE static void apply(hkQuadDouble64& self, const hkFloat16* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & ((sizeof(hkFloat16)*(N!=3?N:4) )-1) ) == 0, "pointer must be aligned for SIMD.");
	unrolld_loadF16<N, HK_IO_NATIVE_ALIGNED>::apply(self,p);
} };
template <int N>
struct unrolld_loadF16<N, HK_IO_NOT_CACHED> { HK_FORCE_INLINE static void apply(hkQuadDouble64& self, const hkFloat16* HK_RESTRICT p)
{
	unrolld_loadF16<N, HK_IO_SIMD_ALIGNED>::apply(self,p);
} };
} // namespace 

template <int N, hkMathIoMode A>
HK_FORCE_INLINE void hkVector4d::load(const hkFloat16* p)
{
	HK_VECTOR4d_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrolld_loadF16<N,A>::apply(m_quad, p);
}

template <int N>
HK_FORCE_INLINE void hkVector4d::load(const hkFloat16* p)
{
	HK_VECTOR4d_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrolld_loadF16<N,HK_IO_SIMD_ALIGNED>::apply(m_quad, p);
}



namespace hkVector4_AdvancedInterface
{
template <int N, hkMathIoMode A>
struct unrolld_store { HK_FORCE_INLINE static void apply(const hkQuadDouble64& self, hkFloat32* HK_RESTRICT p)
{
	HK_VECTOR4d_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <int N, hkMathIoMode A>
struct unrolld_store_D { HK_FORCE_INLINE static void apply(const hkQuadDouble64& self, hkDouble64* HK_RESTRICT p)
{
	HK_VECTOR4d_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <int N>
struct unrolld_store<N, HK_IO_BYTE_ALIGNED> { HK_FORCE_INLINE static void apply(const hkQuadDouble64& self, hkFloat32* HK_RESTRICT p)
{
	switch (N)
	{
	case 1:
		{
			__m128 a = _mm_cvtpd_ps(self.xy);
			_mm_store_ss(p, a);
		}
		break;
	case 2:
		{
			__m128 a = _mm_cvtpd_ps(self.xy);
			_mm_store_sd((double*)p, _mm_castps_pd(a));
		}
		break;
	case 3:
		{
			__m128 a = _mm_cvtpd_ps(self.xy);
			__m128 b = _mm_cvtpd_ps(self.zw);
			_mm_store_sd((double*)p, _mm_castps_pd(a));
			_mm_store_ss(p+2, b);
		}
		break;
	default:
		{
			__m128 a = _mm_cvtpd_ps(self.xy);
			__m128 b = _mm_cvtpd_ps(self.zw);
			__m128 xyzw = _mm_movelh_ps(a,b);
			_mm_storeu_ps(p, xyzw);
		}
		break;
	}
} };
template <int N>
struct unrolld_store_D<N, HK_IO_BYTE_ALIGNED> { HK_FORCE_INLINE static void apply(const hkQuadDouble64& self, hkDouble64* HK_RESTRICT p)
{
	switch (N)
	{
	case 1:
		{
			_mm_store_sd(p, self.xy);
		}
		break;
	case 2:
		{
			_mm_storeu_pd(p, self.xy);
		}
		break;
	case 3:
		{
			_mm_storeu_pd(p, self.xy);
			_mm_store_sd(p+2, self.zw);
		}
		break;
	default:
		{
			_mm_storeu_pd(p, self.xy);
			_mm_storeu_pd(p+2, self.zw);
		}
		break;
	}
} };
template <int N>
struct unrolld_store<N, HK_IO_NATIVE_ALIGNED> { HK_FORCE_INLINE static void apply(const hkQuadDouble64& self, hkFloat32* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & (sizeof(hkFloat32)-1) ) == 0, "pointer must be aligned to native size of hkFloat32.");
	unrolld_store<N, HK_IO_BYTE_ALIGNED>::apply(self,p);
} };
template <int N>
struct unrolld_store_D<N, HK_IO_NATIVE_ALIGNED> { HK_FORCE_INLINE static void apply(const hkQuadDouble64& self, hkDouble64* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & (sizeof(hkDouble64)-1) ) == 0, "pointer must be aligned to native size of hkDouble64.");
	unrolld_store_D<N, HK_IO_BYTE_ALIGNED>::apply(self,p);
} };
template <int N>
struct unrolld_store<N, HK_IO_SIMD_ALIGNED> { HK_FORCE_INLINE static void apply(const hkQuadDouble64& self, hkFloat32* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & ((sizeof(hkFloat32)*(N!=3?N:4) )-1) ) == 0, "pointer must be aligned for SIMD.");
	if (N==4)
	{
		__m128 a = _mm_cvtpd_ps(self.xy);
		__m128 b = _mm_cvtpd_ps(self.zw);
		__m128 xyzw = _mm_movelh_ps(a,b);
		_mm_store_ps(p, xyzw);
	}
	else
	{
		unrolld_store<N, HK_IO_NATIVE_ALIGNED>::apply(self,p);
	}
} };
template <int N>
struct unrolld_store_D<N, HK_IO_SIMD_ALIGNED> { HK_FORCE_INLINE static void apply(const hkQuadDouble64& self, hkDouble64* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & ((sizeof(hkDouble64)*(N!=3?N:4) )-1) ) == 0, "pointer must be aligned for SIMD.");
	switch (N)
	{
	case 2:
		{
			_mm_store_pd(p, self.xy);
		}
		break;
	case 3:
		{
			_mm_store_pd(p, self.xy);
			_mm_store_sd(p+2, self.zw);
		}
		break;
	case 4:
		{
			_mm_store_pd(p, self.xy);
			_mm_store_pd(p+2, self.zw);
		}
		break;
	default:
		{
			unrolld_store_D<N, HK_IO_NATIVE_ALIGNED>::apply(self,p);
		}
		break;
	}
} };
template <int N>
struct unrolld_store<N, HK_IO_NOT_CACHED> { HK_FORCE_INLINE static void apply(const hkQuadDouble64& self, hkFloat32* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & ((sizeof(hkFloat32)*(N!=3?N:4) )-1) ) == 0, "pointer must be aligned for SIMD.");
	if (N==4)
	{
		__m128 a = _mm_cvtpd_ps(self.xy);
		__m128 b = _mm_cvtpd_ps(self.zw);
		__m128 xyzw = _mm_movelh_ps(a,b);
		_mm_stream_ps(p, xyzw);
	}
	else
	{
		unrolld_store<N, HK_IO_SIMD_ALIGNED>::apply(self,p);
	}
} };
template <int N>
struct unrolld_store_D<N, HK_IO_NOT_CACHED> { HK_FORCE_INLINE static void apply(const hkQuadDouble64& self, hkDouble64* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & ((sizeof(hkDouble64)*(N!=3?N:4) )-1) ) == 0, "pointer must be aligned for SIMD.");
	switch (N)
	{
	case 2:
		{
			_mm_stream_pd(p, self.xy);
		}
		break;
	case 3:
		{
			_mm_stream_pd(p, self.xy);
			_mm_store_sd(p+2, self.zw);
		}
		break;
	case 4:
		{
			_mm_stream_pd(p, self.xy);
			_mm_stream_pd(p+2, self.zw);
		}
		break;
	default:
		{
			unrolld_store_D<N, HK_IO_SIMD_ALIGNED>::apply(self,p);
		}
		break;
	}
} };
} // namespace 

template <int N, hkMathIoMode A, hkMathRoundingMode R> 
HK_FORCE_INLINE void hkVector4d::store(hkFloat32* p) const
{
	HK_VECTOR4d_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrolld_store<N,A>::apply(m_quad, p);
}

template <int N, hkMathIoMode A, hkMathRoundingMode R> 
HK_FORCE_INLINE void hkVector4d::store(hkDouble64* p) const
{
	HK_VECTOR4d_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrolld_store_D<N,A>::apply(m_quad, p);
}

template <int N, hkMathIoMode A> 
HK_FORCE_INLINE void hkVector4d::store(hkFloat32* p) const
{
	HK_VECTOR4d_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrolld_store<N,A>::apply(m_quad, p);
}

template <int N, hkMathIoMode A> 
HK_FORCE_INLINE void hkVector4d::store(hkDouble64* p) const
{
	HK_VECTOR4d_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrolld_store_D<N,A>::apply(m_quad, p);
}

template <int N> 
HK_FORCE_INLINE void hkVector4d::store(hkFloat32* p) const
{
	HK_VECTOR4d_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrolld_store<N,HK_IO_SIMD_ALIGNED>::apply(m_quad, p);
}

template <int N> 
HK_FORCE_INLINE void hkVector4d::store(hkDouble64* p) const
{
	HK_VECTOR4d_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrolld_store_D<N,HK_IO_SIMD_ALIGNED>::apply(m_quad, p);
}


namespace hkVector4_AdvancedInterface
{
template <int N, hkMathRoundingMode R>
HK_FORCE_INLINE static void convertf64half(const hkQuadDouble64& self, __m128i& packed)
{
	static HK_ALIGN16(const unsigned int scale[4])      = {0x3F808000, 0x3F808000, 0x3F808000, 0x3F808000}; // 1 + 1/256 as float32

	__m128 xyzw;
	if (N<3)
	{
		xyzw = _mm_cvtpd_ps(self.xy);
	}
	else
	{
		__m128 xy = _mm_cvtpd_ps(self.xy);
		__m128 zw = _mm_cvtpd_ps(self.zw);
		xyzw = _mm_shuffle_ps(xy,zw,_MM_SHUFFLE(1,0,1,0));
	}

	if (R == HK_ROUND_NEAREST)
	{
		xyzw = _mm_mul_ps(xyzw, *((__m128*)&scale));
	}

	__m128i tmp0 = _mm_srai_epi32( _mm_castps_si128(xyzw), 16 );
	packed = _mm_packs_epi32(tmp0, tmp0);
}
template <int N, hkMathIoMode A, hkMathRoundingMode R>
struct unrolld_storeH { HK_FORCE_INLINE static void apply(const hkQuadDouble64& self, hkHalf* HK_RESTRICT p)
{
	HK_VECTOR4d_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <int N, hkMathRoundingMode R>
struct unrolld_storeH<N, HK_IO_BYTE_ALIGNED, R> { HK_FORCE_INLINE static void apply(const hkQuadDouble64& self, hkHalf* HK_RESTRICT p)
{
#if defined(HK_HALF_IS_FLOAT)
	static HK_ALIGN16(const hkUint64 mask[2])      = {0xFFFFFFFF00000000ull, 0xFFFFFFFF00000000ull};

	switch (N)
	{
	case 1:
		{
			__m128d vs0;
			if (R == HK_ROUND_NEAREST)
				vs0 = self.xy;
			else
				vs0 = _mm_and_pd(self.xy, *((__m128d*)&mask));
			_mm_store_ss((float*)p, _mm_cvtpd_ps(vs0));
		}
		break;
	case 2:
		{
			__m128d vs0;
			if (R == HK_ROUND_NEAREST)
				vs0 = self.xy;
			else
				vs0 = _mm_and_pd(self.xy, *((__m128d*)&mask));
			__m128 twofloats = _mm_cvtpd_ps(vs0);
			_mm_store_sd((double*) p, _mm_castps_pd(twofloats));
		}
		break;
	case 3:
		{
			__m128d xy;
			__m128d zw;
			if (R == HK_ROUND_NEAREST)
			{
				xy = self.xy;
				zw = self.zw;
			}
			else
			{
				xy = _mm_and_pd(self.xy, *((__m128d*)&mask));
				zw = _mm_and_pd(self.zw, *((__m128d*)&mask));
			}
			__m128 xy_f = _mm_cvtpd_ps(xy);
			__m128 zw_f = _mm_cvtpd_ps(zw);
			_mm_store_sd((double*) p, _mm_castps_pd(xy_f));
			_mm_store_ss((float*)p+2, zw_f);
		}
		break;
	default:
		{
			__m128d xy;
			__m128d zw;
			if (R == HK_ROUND_NEAREST)
			{
				xy = self.xy;
				zw = self.zw;
			}
			else
			{
				xy = _mm_and_pd(self.xy, *((__m128d*)&mask));
				zw = _mm_and_pd(self.zw, *((__m128d*)&mask));
			}
			__m128 xy_f = _mm_cvtpd_ps(xy);
			__m128 zw_f = _mm_cvtpd_ps(zw);
			__m128 xyzw = _mm_shuffle_ps(xy_f,zw_f,_MM_SHUFFLE(1,0,1,0));
			_mm_storeu_ps((float*)p, xyzw);
		}
		break;
	}
#else
	__m128i packed;
	convertf64half<N,R>(self,packed);

	switch (N)
	{
	case 1:
		{
			HK_ALIGN16(hkHalf tmp[2]);
			_mm_store_ss((float*)tmp, _mm_castsi128_ps(packed));
			p[0] = tmp[0];
		}
		break;
	case 2:
		{
			_mm_store_ss((float*)p, _mm_castsi128_ps(packed));
		}
		break;
	case 3:
		{
			HK_ALIGN16(hkHalf tmp[4]);
			_mm_storel_epi64((__m128i*)tmp, packed);
			p[0] = tmp[0];
			p[1] = tmp[1];
			p[2] = tmp[2];
		}
		break;
	default:
		{
			_mm_store_sd((double*) p, _mm_castsi128_pd(packed));
		}
		break;
	}
#endif
} };
template <int N, hkMathRoundingMode R>
struct unrolld_storeH<N, HK_IO_NATIVE_ALIGNED, R> { HK_FORCE_INLINE static void apply(const hkQuadDouble64& self, hkHalf* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & (sizeof(hkHalf)-1) ) == 0, "pointer must be aligned to native size of hkHalf.");
	unrolld_storeH<N, HK_IO_BYTE_ALIGNED, R>::apply(self,p);
} };
template <int N, hkMathRoundingMode R>
struct unrolld_storeH<N, HK_IO_SIMD_ALIGNED, R> { HK_FORCE_INLINE static void apply(const hkQuadDouble64& self, hkHalf* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & ((sizeof(hkHalf)*(N!=3?N:4) )-1) ) == 0, "pointer must be aligned for SIMD.");
#if defined(HK_HALF_IS_FLOAT)
	static HK_ALIGN16(const hkUint64 mask[2])      = {0xFFFFFFFF00000000ull, 0xFFFFFFFF00000000ull};
#endif
	switch (N)
	{
	case 4:
		{
#if defined(HK_HALF_IS_FLOAT)
			__m128d xy;
			__m128d zw;
			if (R == HK_ROUND_NEAREST)
			{
				xy = self.xy;
				zw = self.zw;
			}
			else
			{
				xy = _mm_and_pd(self.xy, *((__m128d*)&mask));
				zw = _mm_and_pd(self.zw, *((__m128d*)&mask));
			}
			__m128 xy_f = _mm_cvtpd_ps(xy);
			__m128 zw_f = _mm_cvtpd_ps(zw);
			__m128 xyzw = _mm_shuffle_ps(xy_f,zw_f,_MM_SHUFFLE(1,0,1,0));
			_mm_store_ps((float*)p, xyzw);
#else
			__m128i packed;
			convertf64half<N,R>(self,packed);
			_mm_storel_epi64((__m128i*)p, packed);
#endif
		}
		break;
	default:
		{
			unrolld_storeH<N, HK_IO_NATIVE_ALIGNED, R>::apply(self,p);
		}
		break;
	}
} };
template <int N, hkMathRoundingMode R>
struct unrolld_storeH<N, HK_IO_NOT_CACHED, R> { HK_FORCE_INLINE static void apply(const hkQuadDouble64& self, hkHalf* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & ((sizeof(hkHalf)*(N!=3?N:4) )-1) ) == 0, "pointer must be aligned for SIMD.");
#if defined(HK_HALF_IS_FLOAT)
	static HK_ALIGN16(const hkUint64 mask[2])      = {0xFFFFFFFF00000000ull, 0xFFFFFFFF00000000ull};
	switch (N)
	{
	case 4: 
		{
			__m128d xy;
			__m128d zw;
			if (R == HK_ROUND_NEAREST)
			{
				xy = self.xy;
				zw = self.zw;
			}
			else
			{
				xy = _mm_and_pd(self.xy, *((__m128d*)&mask));
				zw = _mm_and_pd(self.zw, *((__m128d*)&mask));
			}
			__m128 xy_f = _mm_cvtpd_ps(xy);
			__m128 zw_f = _mm_cvtpd_ps(zw);
			__m128 xyzw = _mm_shuffle_ps(xy_f,zw_f,_MM_SHUFFLE(1,0,1,0));
			_mm_stream_ps((float*)p, xyzw);
		}
		break;
	default:
		{
			unrolld_storeH<N, HK_IO_SIMD_ALIGNED, R>::apply(self,p);
		}
		break;
	}
#else
	unrolld_storeH<N, HK_IO_SIMD_ALIGNED, R>::apply(self,p);
#endif
} };
} // namespace 

template <int N, hkMathIoMode A, hkMathRoundingMode R> 
HK_FORCE_INLINE void hkVector4d::store(hkHalf* p) const
{
	HK_VECTOR4d_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrolld_storeH<N,A,R>::apply(m_quad, p);
}

template <int N, hkMathIoMode A> 
HK_FORCE_INLINE void hkVector4d::store(hkHalf* p) const
{
	HK_VECTOR4d_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrolld_storeH<N,A,HK_ROUND_DEFAULT>::apply(m_quad, p);
}

template <int N> 
HK_FORCE_INLINE void hkVector4d::store(hkHalf* p) const
{
	HK_VECTOR4d_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrolld_storeH<N,HK_IO_SIMD_ALIGNED,HK_ROUND_DEFAULT>::apply(m_quad, p);
}




namespace hkVector4_AdvancedInterface
{
template <int N, hkMathRoundingMode R>
HK_FORCE_INLINE static void convertf64f16(const hkQuadDouble64& self, __m128i& packed)
{
	static HK_ALIGN16(const unsigned int infinity[4]) = {0x47FFE000, 0x47FFE000, 0x47FFE000, 0x47FFE000};
	static HK_ALIGN16(const unsigned int denormal[4]) = {0x38800000, 0x38800000, 0x38800000, 0x38800000};
	static HK_ALIGN16(const unsigned int fixup[4])    = {0x48000000, 0x48000000, 0x48000000, 0x48000000};
	static HK_ALIGN16(const unsigned int round1[4])   = {0x00000001, 0x00000001, 0x00000001, 0x00000001};
	static HK_ALIGN16(const unsigned int round2[4])   = {0x00000FFF, 0x00000FFF, 0x00000FFF, 0x00000FFF};
	static HK_ALIGN16(const unsigned int base[4])     = {0x00007FFF, 0x00007FFF, 0x00007FFF, 0x00007FFF};
	static HK_ALIGN16(const unsigned int integer[4])  = {0x52000000, 0x52000000, 0x52000000, 0x52000000};

	__m128 xyzw;
	if (N<3)
	{
		xyzw = _mm_cvtpd_ps(self.xy);
	}
	else
	{
		__m128 xy = _mm_cvtpd_ps(self.xy);
		__m128 zw = _mm_cvtpd_ps(self.zw);
		xyzw = _mm_shuffle_ps(xy,zw,_MM_SHUFFLE(1,0,1,0));
	}

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
template <int N, hkMathIoMode A, hkMathRoundingMode R>
struct unrolld_storeF16 { HK_FORCE_INLINE static void apply(const hkQuadDouble64& self, hkFloat16* HK_RESTRICT p)
{
	HK_VECTOR4d_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <int N, hkMathRoundingMode R>
struct unrolld_storeF16<N, HK_IO_BYTE_ALIGNED, R> { HK_FORCE_INLINE static void apply(const hkQuadDouble64& self, hkFloat16* HK_RESTRICT p)
{
	__m128i packed;
	convertf64f16<N,R>(self,packed);
	switch (N)
	{
	case 1:
		{
			HK_ALIGN16(hkFloat16 tmp[2]);
			_mm_store_ss((float*)tmp, _mm_castsi128_ps(packed));
			p[0] = tmp[0];
		}
		break;
	case 2:
		{
			_mm_store_ss((float*)p, _mm_castsi128_ps(packed));
		}
		break;
	case 3:
		{
			HK_ALIGN16(hkFloat16 tmp[4]);
			_mm_storel_epi64((__m128i*)tmp, packed);
			p[0] = tmp[0];
			p[1] = tmp[1];
			p[2] = tmp[2];
		}
		break;
	default:
		{
			_mm_store_sd((double*) p, _mm_castsi128_pd(packed));
		}
		break;
	}
} };
template <int N, hkMathRoundingMode R>
struct unrolld_storeF16<N, HK_IO_NATIVE_ALIGNED, R> { HK_FORCE_INLINE static void apply(const hkQuadDouble64& self, hkFloat16* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & (sizeof(hkFloat16)-1) ) == 0, "pointer must be aligned to native size of hkFloat16.");
	unrolld_storeF16<N, HK_IO_BYTE_ALIGNED, R>::apply(self,p);
} };
template <int N, hkMathRoundingMode R>
struct unrolld_storeF16<N, HK_IO_SIMD_ALIGNED, R> { HK_FORCE_INLINE static void apply(const hkQuadDouble64& self, hkFloat16* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & ((sizeof(hkFloat16)*(N!=3?N:4) )-1) ) == 0, "pointer must be aligned for SIMD.");
	switch (N)
	{
	case 4:
		{
			__m128i packed;
			convertf64f16<N,R>(self,packed);
			_mm_storel_epi64((__m128i*)p, packed);
		}
		break;
	default:
		{
			unrolld_storeF16<N, HK_IO_NATIVE_ALIGNED, R>::apply(self,p);
		}
		break;
	}
} };
template <int N, hkMathRoundingMode R>
struct unrolld_storeF16<N, HK_IO_NOT_CACHED, R> { HK_FORCE_INLINE static void apply(const hkQuadDouble64& self, hkFloat16* HK_RESTRICT p)
{
	unrolld_storeF16<N, HK_IO_SIMD_ALIGNED, R>::apply(self,p);
} };
} // namespace 

template <int N, hkMathIoMode A, hkMathRoundingMode R> 
HK_FORCE_INLINE void hkVector4d::store(hkFloat16* p) const
{
	HK_VECTOR4d_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrolld_storeF16<N,A,R>::apply(m_quad, p);
}

template <int N, hkMathIoMode A> 
HK_FORCE_INLINE void hkVector4d::store(hkFloat16* p) const
{
	HK_VECTOR4d_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrolld_storeF16<N,A,HK_ROUND_DEFAULT>::apply(m_quad, p);
}

template <int N> 
HK_FORCE_INLINE void hkVector4d::store(hkFloat16* p) const
{
	HK_VECTOR4d_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrolld_storeF16<N,HK_IO_SIMD_ALIGNED,HK_ROUND_DEFAULT>::apply(m_quad, p);
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
