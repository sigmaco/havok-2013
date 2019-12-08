/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */


#if defined(HK_HALF_IS_FLOAT)
#error not implemented
#endif

#define HK_VECTOR4d_COMBINE_XYZ_W(xyz, w) _mm256_blend_pd( xyz, w, 0x8)

// helper funcs to avoid SSE code
template <int I>
HK_FORCE_INLINE static hkQuadDouble64 broadcastScalar(hkVector4dParameter v)
{
	HK_VECTOR4d_NOT_IMPLEMENTED;
	return g_vectordConstants[HK_QUADREAL_0];
}

template <>
HK_FORCE_INLINE static hkQuadDouble64 broadcastScalar<0>(hkVector4dParameter v)
{
	const hkQuadDouble64 xz = _mm256_permute_pd(v.m_quad, 0x0);
	return _mm256_permute2f128_pd(xz,xz,0x00);
}

template <>
HK_FORCE_INLINE static hkQuadDouble64 broadcastScalar<1>(hkVector4dParameter v)
{
	const hkQuadDouble64 yw = _mm256_permute_pd(v.m_quad, 0xF);
	return _mm256_permute2f128_pd(yw,yw,0x00);
}

template <>
HK_FORCE_INLINE static hkQuadDouble64 broadcastScalar<2>(hkVector4dParameter v)
{
	const hkQuadDouble64 xz = _mm256_permute_pd(v.m_quad, 0x0);
	return _mm256_permute2f128_pd(xz,xz,0x11);
}

template <>
HK_FORCE_INLINE static hkQuadDouble64 broadcastScalar<3>(hkVector4dParameter v)
{
	const hkQuadDouble64 yw = _mm256_permute_pd(v.m_quad, 0xF);
	return _mm256_permute2f128_pd(yw,yw,0x11);
}


/* quad, here for inlining */

#ifndef HK_DISABLE_MATH_CONSTRUCTORS
/* construct, assign, zero */
HK_FORCE_INLINE hkVector4d::hkVector4d(hkDouble64 a, hkDouble64 b, hkDouble64 c, hkDouble64 d)
{
	m_quad = _mm256_setr_pd(a,b,c,d);
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
	m_quad = _mm256_setr_pd(a,b,c,d);
}

HK_FORCE_INLINE void hkVector4d::set( hkSimdDouble64Parameter a, hkSimdDouble64Parameter b, hkSimdDouble64Parameter c, hkSimdDouble64Parameter d )
{
	const __m128d ab128 = _mm_move_sd(b.m_real,a.m_real);
	const __m128d cd128 = _mm_move_sd(d.m_real,c.m_real);
	const __m256d ab = _mm256_broadcast_pd(&ab128);
	const __m256d cd = _mm256_broadcast_pd(&cd128);
	m_quad = _mm256_permute2f128_pd(ab, cd, 0x20);
}

HK_FORCE_INLINE void hkVector4d::setAll(const hkDouble64& a)
{
	m_quad = _mm256_broadcast_sd(&a);
}

HK_FORCE_INLINE void hkVector4d::setAll(hkSimdDouble64Parameter a)
{
	m_quad = _mm256_broadcast_pd(&a.m_real);
}

HK_FORCE_INLINE void hkVector4d::setZero()
{
	m_quad = _mm256_setzero_pd();
}

template <int I> 
HK_FORCE_INLINE void hkVector4d::zeroComponent()
{
	HK_VECTOR4d_SUBINDEX_CHECK;
	m_quad = _mm256_blend_pd(m_quad, _mm256_setzero_pd(), 1<<I);
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
	return hkSimdDouble64::convert(_mm256_extractf128_pd(_mm256_permute_pd(m_quad, 0x0),0));
}

template <>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::getComponent<1>() const
{
	return hkSimdDouble64::convert(_mm256_extractf128_pd(_mm256_permute_pd(m_quad, 0x3),0));
}

template <>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::getComponent<2>() const
{
	return hkSimdDouble64::convert(_mm256_extractf128_pd(_mm256_permute_pd(m_quad, 0x0),1));
}

template <>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::getComponent<3>() const
{
	return hkSimdDouble64::convert(_mm256_extractf128_pd(_mm256_permute_pd(m_quad, 0xC),1));
}

template <int I>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::getComponent() const
{
	HK_VECTOR4d_NOT_IMPLEMENTED;
	return hkSimdDouble64::getConstant<HK_QUADREAL_0>();
}

HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::getComponent(const int i) const
{
	HK_MATH_ASSERT(0x6d0c31d7, i>=0 && i<4, "index out of bounds for component access");

	__m128d selected;

	switch(i)
	{
		case 1:  { selected = _mm256_extractf128_pd(_mm256_permute_pd(m_quad, 0xF),0); } break;
		case 2:  { selected = _mm256_extractf128_pd(_mm256_permute_pd(m_quad, 0x0),1); } break;
		case 3:  { selected = _mm256_extractf128_pd(_mm256_permute_pd(m_quad, 0xF),1); } break;
		default: { selected = _mm256_extractf128_pd(_mm256_permute_pd(m_quad, 0x0),0); } break;
	}

	return hkSimdDouble64::convert(selected);
}

HK_FORCE_INLINE void hkVector4d::setAdd(hkVector4dParameter v0, hkVector4dParameter v1)
{
	m_quad = _mm256_add_pd(v0.m_quad, v1.m_quad);
}

HK_FORCE_INLINE void hkVector4d::setSub(hkVector4dParameter v0, hkVector4dParameter v1)
{
	m_quad = _mm256_sub_pd(v0.m_quad, v1.m_quad);
}

HK_FORCE_INLINE void hkVector4d::setMul(hkVector4dParameter v0, hkVector4dParameter v1)
{
	m_quad = _mm256_mul_pd(v0.m_quad, v1.m_quad);
}

HK_FORCE_INLINE void hkVector4d::setMul(hkVector4dParameter v1, hkSimdDouble64Parameter r)
{
	const hkQuadDouble64 s = _mm256_broadcast_pd(&r.m_real);
	m_quad = _mm256_mul_pd( s, v1.m_quad);
}

HK_FORCE_INLINE void hkVector4d::setSubMul(hkVector4dParameter a, hkVector4dParameter b, hkSimdDouble64Parameter r)
{
	const hkQuadDouble64 s = _mm256_broadcast_pd(&r.m_real);
#if HK_SSE_VERSION >= 0x51
	m_quad = _mm256_fnmadd_pd(s, b.m_quad, a.m_quad);
#else
	m_quad = _mm256_sub_pd( a.m_quad, _mm256_mul_pd( s, b.m_quad) );
#endif
}

HK_FORCE_INLINE void hkVector4d::setAddMul(hkVector4dParameter a, hkVector4dParameter b, hkSimdDouble64Parameter r)
{
	const hkQuadDouble64 s = _mm256_broadcast_pd(&r.m_real);
#if HK_SSE_VERSION >= 0x51
	m_quad = _mm256_fmadd_pd(s, b.m_quad, a.m_quad);
#else
	m_quad = _mm256_add_pd( a.m_quad, _mm256_mul_pd( s, b.m_quad) );
#endif
}

HK_FORCE_INLINE void hkVector4d::setAddMul(hkVector4dParameter a, hkVector4dParameter x, hkVector4dParameter y)
{
#if HK_SSE_VERSION >= 0x51
	m_quad = _mm256_fmadd_pd(y.m_quad, x.m_quad, a.m_quad);
#else
	m_quad = _mm256_add_pd( a.m_quad, _mm256_mul_pd( x.m_quad, y.m_quad) );
#endif
}

HK_FORCE_INLINE void hkVector4d::setSubMul(hkVector4dParameter a, hkVector4dParameter x, hkVector4dParameter y)
{
#if HK_SSE_VERSION >= 0x51
	m_quad = _mm256_fnmadd_pd(y.m_quad, x.m_quad, a.m_quad);
#else
	m_quad = _mm256_sub_pd( a.m_quad, _mm256_mul_pd( x.m_quad, y.m_quad) );
#endif
}

HK_FORCE_INLINE void hkVector4d::setCross( hkVector4dParameter v0, hkVector4dParameter v1 )
{
	__m128d v0_xy = _mm256_extractf128_pd(v0.m_quad, 0);
	__m128d v0_zw = _mm256_extractf128_pd(v0.m_quad, 1);
	__m128d v1_xy = _mm256_extractf128_pd(v1.m_quad, 0);
	__m128d v1_zw = _mm256_extractf128_pd(v1.m_quad, 1);

	// x = y0z1 - z0y1
	__m128d x2 = _mm_mul_pd(_mm_shuffle_pd(v0_xy, v0_zw, _MM_SHUFFLE2(0,1)), _mm_shuffle_pd(v1_zw, v1_xy, _MM_SHUFFLE2(1,0)));
	__m128d x = _mm_sub_pd(x2, _mm_shuffle_pd(x2, x2, _MM_SHUFFLE2(0,1)));

	// y = z0x1 - x0z1
	__m128d y2 = _mm_mul_pd(_mm_shuffle_pd(v0_zw, v0_xy, _MM_SHUFFLE2(0,0)), _mm_shuffle_pd(v1_xy, v1_zw, _MM_SHUFFLE2(0,0)));
	__m128d y = _mm_sub_pd(y2, _mm_shuffle_pd(y2, y2, _MM_SHUFFLE2(0,1)));

	__m128d quad_xy = _mm_shuffle_pd(x, y, _MM_SHUFFLE2(0,0));

	// z = x0y1 - y0x1
	__m128d z2 = _mm_mul_pd(v0_xy, _mm_shuffle_pd(v1_xy, v1_xy, _MM_SHUFFLE2(0,1)));
	__m128d quad_zw = _mm_sub_pd(z2, _mm_shuffle_pd(z2, z2, _MM_SHUFFLE2(0,1)));

	m_quad = _mm256_broadcast_pd(&quad_xy);
	m_quad = _mm256_insertf128_pd(m_quad, quad_zw, 1);
}

HK_FORCE_INLINE const hkVector4dComparison hkVector4d::equal(hkVector4dParameter a) const
{
	const hkQuadDouble64 mask =  _mm256_cmp_pd(m_quad, a.m_quad, _CMP_EQ_OQ);
	return hkVector4dComparison::convert(mask);
}

HK_FORCE_INLINE const hkVector4dComparison hkVector4d::notEqual(hkVector4dParameter a) const
{
	const hkQuadDouble64 mask =  _mm256_cmp_pd(m_quad, a.m_quad, _CMP_NEQ_OQ);
	return hkVector4dComparison::convert(mask);
}

HK_FORCE_INLINE const hkVector4dComparison hkVector4d::less(hkVector4dParameter a) const
{
	const hkQuadDouble64 mask =  _mm256_cmp_pd(m_quad, a.m_quad, _CMP_LT_OQ);
	return hkVector4dComparison::convert(mask);
}

HK_FORCE_INLINE const hkVector4dComparison hkVector4d::lessEqual(hkVector4dParameter a) const
{
	const hkQuadDouble64 mask =  _mm256_cmp_pd(m_quad, a.m_quad, _CMP_LE_OQ);
	return hkVector4dComparison::convert(mask);
}

HK_FORCE_INLINE const hkVector4dComparison hkVector4d::greater(hkVector4dParameter a) const
{
	const hkQuadDouble64 mask =  _mm256_cmp_pd(m_quad, a.m_quad, _CMP_GT_OQ);
	return hkVector4dComparison::convert(mask);
}

HK_FORCE_INLINE const hkVector4dComparison hkVector4d::greaterEqual(hkVector4dParameter a) const
{
	const hkQuadDouble64 mask =  _mm256_cmp_pd(m_quad, a.m_quad, _CMP_GE_OQ);
	return hkVector4dComparison::convert(mask);
}

HK_FORCE_INLINE const hkVector4dComparison hkVector4d::lessZero() const
{
	const hkQuadDouble64 mask =  _mm256_cmp_pd(m_quad, _mm256_setzero_pd(), _CMP_LT_OQ);
	return hkVector4dComparison::convert(mask);
}

HK_FORCE_INLINE const hkVector4dComparison hkVector4d::lessEqualZero() const
{
	const hkQuadDouble64 mask =  _mm256_cmp_pd(m_quad, _mm256_setzero_pd(), _CMP_LE_OQ);
	return hkVector4dComparison::convert(mask);
}

HK_FORCE_INLINE const hkVector4dComparison hkVector4d::greaterZero() const
{
	const hkQuadDouble64 mask =  _mm256_cmp_pd(m_quad, _mm256_setzero_pd(), _CMP_GT_OQ);
	return hkVector4dComparison::convert(mask);
}

HK_FORCE_INLINE const hkVector4dComparison hkVector4d::greaterEqualZero() const
{
	const hkQuadDouble64 mask =  _mm256_cmp_pd(m_quad, _mm256_setzero_pd(), _CMP_GE_OQ);
	return hkVector4dComparison::convert(mask);
}

HK_FORCE_INLINE const hkVector4dComparison hkVector4d::equalZero() const
{
	const hkQuadDouble64 mask =  _mm256_cmp_pd(m_quad, _mm256_setzero_pd(), _CMP_EQ_OQ);
	return hkVector4dComparison::convert(mask);
}

HK_FORCE_INLINE const hkVector4dComparison hkVector4d::notEqualZero() const
{
	const hkQuadDouble64 mask =  _mm256_cmp_pd(m_quad, _mm256_setzero_pd(), _CMP_NEQ_OQ);
	return hkVector4dComparison::convert(mask);
}

HK_FORCE_INLINE void hkVector4d::setSelect( hkVector4dComparisonParameter comp, hkVector4dParameter trueValue, hkVector4dParameter falseValue )
{
	m_quad = _mm256_blendv_pd(falseValue.m_quad, trueValue.m_quad, comp.m_mask);
}

HK_FORCE_INLINE void hkVector4d::zeroIfFalse( hkVector4dComparisonParameter comp )
{
	m_quad = _mm256_and_pd(comp.m_mask, m_quad);
}

HK_FORCE_INLINE void hkVector4d::zeroIfTrue( hkVector4dComparisonParameter comp )
{
	m_quad = _mm256_andnot_pd(comp.m_mask, m_quad);
}


template<hkVector4dComparison::Mask M> 
HK_FORCE_INLINE void hkVector4d::setSelect( hkVector4dParameter trueValue, hkVector4dParameter falseValue )
{
	m_quad = _mm256_blend_pd(falseValue.m_quad, trueValue.m_quad, M);
}

template <>
HK_FORCE_INLINE void hkVector4d::setNeg<1>(hkVector4dParameter v)
{
	static HK_ALIGN32( const hkUint64 negateMask[4] ) = { 0x8000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000 }; // todo constant
	m_quad = _mm256_xor_pd(v.m_quad, *(const hkQuadDouble64*)&negateMask);
}

template <>
HK_FORCE_INLINE void hkVector4d::setNeg<2>(hkVector4dParameter v)
{
	static HK_ALIGN32( const hkUint64 negateMask[4] ) = { 0x8000000000000000, 0x8000000000000000, 0x0000000000000000, 0x0000000000000000 }; // todo constant
	m_quad = _mm256_xor_pd(v.m_quad, *(const hkQuadDouble64*)&negateMask);
}

template <>
HK_FORCE_INLINE void hkVector4d::setNeg<3>(hkVector4dParameter v)
{
	static HK_ALIGN32( const hkUint64 negateMask[4] ) = { 0x8000000000000000, 0x8000000000000000, 0x8000000000000000, 0x0000000000000000 }; // todo constant
	m_quad = _mm256_xor_pd(v.m_quad, *(const hkQuadDouble64*)&negateMask);
}

template <>
HK_FORCE_INLINE void hkVector4d::setNeg<4>(hkVector4dParameter v)
{
	static HK_ALIGN32( const hkUint64 negateMask[4] ) = { 0x8000000000000000, 0x8000000000000000, 0x8000000000000000, 0x8000000000000000 }; // todo constant
	m_quad = _mm256_xor_pd(v.m_quad, *(const hkQuadDouble64*)&negateMask);
}

template <int N>
HK_FORCE_INLINE void hkVector4d::setNeg(hkVector4dParameter v)
{
	HK_VECTOR4d_NOT_IMPLEMENTED;
}

HK_FORCE_INLINE void hkVector4d::setAbs(hkVector4dParameter v)
{
	m_quad = hkMath::quadFabs(v.m_quad);
}

HK_FORCE_INLINE void hkVector4d::setMin(hkVector4dParameter a, hkVector4dParameter b)
{
	m_quad = _mm256_min_pd(a.m_quad, b.m_quad);
}

HK_FORCE_INLINE void hkVector4d::setMax(hkVector4dParameter a, hkVector4dParameter b)
{
	m_quad = _mm256_max_pd(a.m_quad, b.m_quad);
}

/* matrix3, rotation, quaternion, transform */

HK_FORCE_INLINE void hkVector4d::_setRotatedDir(const hkMatrix3d& r, hkVector4dParameter b )
{
	const hkQuadDouble64 c0 = r.getColumn<0>().m_quad;
	const hkQuadDouble64 c1 = r.getColumn<1>().m_quad;
	const hkQuadDouble64 c2 = r.getColumn<2>().m_quad;

	const hkQuadDouble64 b_xxzz = _mm256_permute_pd( b.m_quad, 0x0);
	const hkQuadDouble64 b_yyww = _mm256_permute_pd( b.m_quad, 0xF);

	const hkQuadDouble64 b0 = _mm256_permute2f128_pd(b_xxzz, b_xxzz, 0x00);
	const hkQuadDouble64 b1 = _mm256_permute2f128_pd(b_yyww, b_yyww, 0x00);
	const hkQuadDouble64 b2 = _mm256_permute2f128_pd(b_xxzz, b_xxzz, 0x11);	

	const hkQuadDouble64 r0 = _mm256_mul_pd( c0, b0 );
	const hkQuadDouble64 r1 = _mm256_mul_pd( c1, b1 );
	const hkQuadDouble64 r2 = _mm256_mul_pd( c2, b2 );

	m_quad = _mm256_add_pd( _mm256_add_pd(r0, r1), r2 );
}

HK_FORCE_INLINE void hkVector4d::_setRotatedInverseDir(const hkMatrix3d& r, hkVector4dParameter b )
{
	hkVector4d c0 = r.getColumn<0>();
	hkVector4d c1 = r.getColumn<1>();
	hkVector4d c2 = r.getColumn<2>();

	HK_TRANSPOSE3(c0,c1,c2);

	const hkQuadDouble64 b_xxzz = _mm256_permute_pd( b.m_quad, 0x0);
	const hkQuadDouble64 b_yyww = _mm256_permute_pd( b.m_quad, 0xF);

	const hkQuadDouble64 b0 = _mm256_permute2f128_pd(b_xxzz, b_xxzz, 0x00);
	const hkQuadDouble64 b1 = _mm256_permute2f128_pd(b_yyww, b_yyww, 0x00);
	const hkQuadDouble64 b2 = _mm256_permute2f128_pd(b_xxzz, b_xxzz, 0x11);	

	const hkQuadDouble64 r0 = _mm256_mul_pd( c0.m_quad, b0 );
	const hkQuadDouble64 r1 = _mm256_mul_pd( c1.m_quad, b1 );
	const hkQuadDouble64 r2 = _mm256_mul_pd( c2.m_quad, b2 );

	m_quad = _mm256_add_pd( _mm256_add_pd(r0, r1), r2 );
}


template <>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::dot<2>(hkVector4dParameter a) const
{
	const hkQuadDouble64 x2 = _mm256_mul_pd(m_quad,a.m_quad);
	const hkQuadDouble64 hsum = _mm256_hadd_pd(x2,x2); // xy xy zw zw
	return hkSimdDouble64::convert(_mm256_extractf128_pd(hsum,0));
}

template <>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::dot<3>(hkVector4dParameter a) const
{
	const hkQuadDouble64 x2 = _mm256_mul_pd(m_quad,a.m_quad);
	const hkQuadDouble64 hsum = _mm256_hadd_pd(x2,x2); // xy xy zw zw
	const hkQuadDouble64 x2z = _mm256_permute_pd(x2, 0x0);
	const hkQuadDouble64 z = _mm256_permute2f128_pd(x2z,x2z,0x11); // z z z z
	const hkQuadDouble64 hsumz = _mm256_add_pd(hsum, z); // xyz xyz zzw zzw
	return hkSimdDouble64::convert(_mm256_extractf128_pd(hsumz,0));
}

template <>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::dot<4>(hkVector4dParameter a) const
{
	const hkQuadDouble64 x2 = _mm256_mul_pd(m_quad,a.m_quad);
	const hkQuadDouble64 hsum = _mm256_hadd_pd(x2,x2); // xy xy zw zw
	const hkQuadDouble64 hsuminv = _mm256_permute2f128_pd(hsum, hsum, _MM256_PERMUTE2(_MM256_A_LOW, _MM256_A_HIGH)); // zw zw xy xy
	return hkSimdDouble64::convert(_mm256_extractf128_pd(_mm256_add_pd(hsum,hsuminv),0)); // xyzw xyzw xyzw xyzw
}

template <int N>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::dot(hkVector4dParameter a) const
{
	HK_VECTOR4d_NOT_IMPLEMENTED;
	return hkSimdDouble64::getConstant<HK_QUADREAL_0>();
}


HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::dot4xyz1(hkVector4dParameter a) const
{
	const hkQuadDouble64 xx2 = _mm256_mul_pd(m_quad,a.m_quad);
	const hkQuadDouble64 x2 = HK_VECTOR4d_COMBINE_XYZ_W(xx2, m_quad);	// replace w by this.w
	const hkQuadDouble64 hsum = _mm256_hadd_pd(x2,x2); // xy xy zw zw
	const hkQuadDouble64 hsuminv = _mm256_permute2f128_pd(hsum, hsum, _MM256_PERMUTE2(_MM256_A_LOW, _MM256_A_HIGH)); // zw zw xy xy
	return hkSimdDouble64::convert(_mm256_extractf128_pd(_mm256_add_pd(hsum,hsuminv),0)); // xyzw xyzw xyzw xyzw
}

template <>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::horizontalAdd<2>() const
{
	const hkQuadDouble64 x2 = _mm256_hadd_pd(m_quad, m_quad); // xy xy zw zw
	return hkSimdDouble64::convert(_mm256_extractf128_pd(x2,0));
}

template <>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::horizontalAdd<3>() const
{
	const hkQuadDouble64 x2 = _mm256_hadd_pd(m_quad, m_quad); // xy xy zw zw
	const hkQuadDouble64 z = broadcastScalar<2>(*this); // z z z z
	const hkQuadDouble64 hsumz = _mm256_add_pd(x2, z); // xyz xyz zzw zzw
	return hkSimdDouble64::convert(_mm256_extractf128_pd(hsumz,0));
}

template <>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::horizontalAdd<4>() const
{
	const hkQuadDouble64 hsum = _mm256_hadd_pd(m_quad, m_quad); // xy xy zw zw
	const hkQuadDouble64 hsuminv = _mm256_permute2f128_pd(hsum, hsum, _MM256_PERMUTE2(_MM256_A_LOW, _MM256_A_HIGH)); // zw zw xy xy
	return hkSimdDouble64::convert(_mm256_extractf128_pd(_mm256_add_pd(hsum,hsuminv),0)); // xyzw xyzw xyzw xyzw
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
	const hkSimdDouble64 x = getComponent<0>() * getComponent<1>();
	return x;
}

template <>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::horizontalMul<3>() const
{
	const hkSimdDouble64 x = getComponent<0>() * getComponent<1>() * getComponent<2>();
	return x;
}

template <>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::horizontalMul<4>() const
{
	// todo hmul?
	const hkSimdDouble64 x = getComponent<0>() * getComponent<1>() * getComponent<2>() * getComponent<3>();
	return x;
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
	const hkQuadDouble64 yx = _mm256_permute_pd(m_quad, 0x1);
	return hkSimdDouble64::convert(_mm256_extractf128_pd(_mm256_min_pd( m_quad, yx ),0));
}

template <>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::horizontalMin<3>() const
{
	const hkQuadDouble64 xyzz = _mm256_permute_pd(m_quad, 0x2);
	const hkQuadDouble64 yxzz = _mm256_permute_pd(m_quad, 0x1);
	const hkQuadDouble64 m = _mm256_min_pd( xyzz, yxzz );           // min (x,y) (y,x) (z,z) (z,z)
	const hkQuadDouble64 minv = _mm256_permute2f128_pd(m, m, _MM256_PERMUTE2(_MM256_A_LOW, _MM256_A_HIGH)); // min (z,z) (z,z) (x,y) (y,x)
	const hkQuadDouble64 mall = _mm256_min_pd( m, minv );           // min (x,y,z,z) all 4
	return hkSimdDouble64::convert(_mm256_extractf128_pd(mall,0));
}

template <>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::horizontalMin<4>() const
{
	const hkQuadDouble64 yxwz = _mm256_permute_pd(m_quad, 0x5);
	const hkQuadDouble64 m = _mm256_min_pd( m_quad, yxwz );         // min (x,y) (y,x) (z,w) (w,z)
	const hkQuadDouble64 minv = _mm256_permute2f128_pd(m, m, _MM256_PERMUTE2(_MM256_A_LOW, _MM256_A_HIGH)); // min (z,w) (w,z) (x,y) (y,x)
	const hkQuadDouble64 mall = _mm256_min_pd( m, minv );           // min (x,y,z,w) all 4
	return hkSimdDouble64::convert(_mm256_extractf128_pd(mall,0));
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
	return m_quad.m256d_f64[a];
}

HK_FORCE_INLINE const hkDouble64& hkVector4d::operator() (int a) const
{
	HK_MATH_ASSERT(0x6d0c31d7, a>=0 && a<4, "index out of bounds for component access");
	return m_quad.m256d_f64[a];
}

HK_FORCE_INLINE void hkVector4d::setXYZ_W(hkVector4dParameter xyz, hkVector4dParameter w)
{
	m_quad = HK_VECTOR4d_COMBINE_XYZ_W(xyz.m_quad, w.m_quad);
}

HK_FORCE_INLINE void hkVector4d::setXYZ_W(hkVector4dParameter xyz, hkSimdDouble64Parameter w)
{
	const hkQuadDouble64 s = _mm256_broadcast_pd(&w.m_real);
	m_quad = HK_VECTOR4d_COMBINE_XYZ_W(xyz.m_quad, s);
}

HK_FORCE_INLINE void hkVector4d::setW(hkVector4dParameter w)
{
	m_quad = HK_VECTOR4d_COMBINE_XYZ_W(m_quad, w.m_quad);
}

HK_FORCE_INLINE void hkVector4d::setXYZ(hkVector4dParameter xyz)
{
	m_quad = HK_VECTOR4d_COMBINE_XYZ_W(xyz.m_quad, m_quad);
}

HK_FORCE_INLINE void hkVector4d::addXYZ(hkVector4dParameter xyz)
{
	m_quad = _mm256_add_pd(m_quad, xyz.m_quad);
	HK_ON_DEBUG( *(hkUint64*)&(m_quad.m256d_f64[3]) = 0xffffffffffffffff; )
}

HK_FORCE_INLINE void hkVector4d::subXYZ(hkVector4dParameter xyz)
{
	m_quad = _mm256_sub_pd(m_quad, xyz.m_quad);
	HK_ON_DEBUG( *(hkUint64*)&(m_quad.m256d_f64[3]) = 0xffffffffffffffff; )
}

HK_FORCE_INLINE void hkVector4d::setXYZ(hkDouble64 v)
{
	const hkQuadDouble64 q = _mm256_set1_pd(v);
	m_quad = HK_VECTOR4d_COMBINE_XYZ_W( q, m_quad );
}

HK_FORCE_INLINE void hkVector4d::setXYZ(hkSimdDouble64Parameter v)
{
	const hkQuadDouble64 s = _mm256_broadcast_pd(&v.m_real);
	m_quad = HK_VECTOR4d_COMBINE_XYZ_W( s, m_quad );
}

HK_FORCE_INLINE void hkVector4d::setXYZ_0(hkVector4dParameter xyz)
{
	m_quad = HK_VECTOR4d_COMBINE_XYZ_W(xyz.m_quad, _mm256_setzero_pd());
}

HK_FORCE_INLINE void hkVector4d::setBroadcastXYZ(const int i, hkVector4dParameter v)
{
	setBroadcast(i,v);
	HK_ON_DEBUG( *(hkUint64*)&(m_quad.m256d_f64[3]) = 0xffffffffffffffff; )
}



HK_FORCE_INLINE void hkVector4d::setComponent(const int i, hkSimdDouble64Parameter val)
{
	static HK_ALIGN32 (const hkUint64 indexToMask[4*4]) = 
	{
		0xffffffffffffffff, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
		0x0000000000000000, 0xffffffffffffffff, 0x0000000000000000, 0x0000000000000000,
		0x0000000000000000, 0x0000000000000000, 0xffffffffffffffff, 0x0000000000000000,
		0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0xffffffffffffffff
	};

	HK_MATH_ASSERT(0x6d0c31d7, i>=0 && i<4, "index out of bounds for component access");

	const hkQuadDouble64 mask = *(const hkQuadDouble64*)&indexToMask[ i * 4 ];
	const hkQuadDouble64 s = _mm256_broadcast_pd(&val.m_real);

	m_quad = _mm256_blendv_pd(m_quad, s, mask);
}

template <int I>
HK_FORCE_INLINE void hkVector4d::setComponent(hkSimdDouble64Parameter val)
{
	HK_VECTOR4d_SUBINDEX_CHECK;
	const hkQuadDouble64 s = _mm256_broadcast_pd(&val.m_real);
	m_quad = _mm256_blend_pd(m_quad, s, 0x1 << I);
}

template <>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::horizontalMax<1>() const
{
	return getComponent<0>();
}

template <>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::horizontalMax<2>() const
{
	const hkQuadDouble64 yx = _mm256_permute_pd(m_quad, 0x1);
	return hkSimdDouble64::convert(_mm256_extractf128_pd(_mm256_max_pd( m_quad, yx ),0));
}

template <>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::horizontalMax<3>() const
{
	const hkQuadDouble64 xyzz = _mm256_permute_pd(m_quad, 0x2);
	const hkQuadDouble64 yxzz = _mm256_permute_pd(m_quad, 0x1);
	const hkQuadDouble64 m = _mm256_max_pd( xyzz, yxzz );           // max (x,y) (y,x) (z,z) (z,z)
	const hkQuadDouble64 minv = _mm256_permute2f128_pd(m, m, _MM256_PERMUTE2(_MM256_A_LOW, _MM256_A_HIGH)); // max (z,z) (z,z) (x,y) (y,x)
	const hkQuadDouble64 mall = _mm256_max_pd( m, minv );           // max (x,y,z,z) all 4
	return hkSimdDouble64::convert(_mm256_extractf128_pd(mall,0));
}

template <>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::horizontalMax<4>() const
{
	const hkQuadDouble64 yxwz = _mm256_permute_pd(m_quad, 0x5);
	const hkQuadDouble64 m = _mm256_max_pd( m_quad, yxwz );         // max (x,y) (y,x) (z,w) (w,z)
	const hkQuadDouble64 minv = _mm256_permute2f128_pd(m, m, _MM256_PERMUTE2(_MM256_A_LOW, _MM256_A_HIGH)); // max (z,w) (w,z) (x,y) (y,x)
	const hkQuadDouble64 mall = _mm256_max_pd( m, minv );           // max (x,y,z,w) all 4
	return hkSimdDouble64::convert(_mm256_extractf128_pd(mall,0));
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
	static HK_ALIGN32(const hkUint64 mask[4])      = {0xFFFFFFFF00000000ull, 0xFFFFFFFF00000000ull, 0xFFFFFFFF00000000ull, 0xFFFFFFFF00000000ull};
	m_quad = _mm256_and_pd(m_quad, *((__m256d*)&mask) );
#else
	__m128 xyzw = _mm256_cvtpd_ps(m_quad);
#if HK_SSE_VERSION >= 0x41
	xyzw = _mm_castsi128_ps(_mm_blend_epi16(_mm_castps_si128(xyzw), _mm_setzero_si128(), 0x55));
#else
	__m128i precisionMask = _mm_set1_epi32(0xffff0000);
	xyzw = _mm_and_ps( xyzw, _mm_castsi128_ps(precisionMask) );
#endif
	m_quad = _mm256_cvtps_pd(xyzw);
#endif
}

template <> 
HK_FORCE_INLINE hkBool32 hkVector4d::isOk<1>() const
{
	const hkQuadDouble64 nanMask = _mm256_cmp_pd(m_quad, _mm256_setzero_pd(), _CMP_UNORD_Q);
	return !(_mm256_movemask_pd(nanMask) & 0x1);
}

template <> 
HK_FORCE_INLINE hkBool32 hkVector4d::isOk<2>() const
{
	const hkQuadDouble64 nanMask = _mm256_cmp_pd(m_quad, _mm256_setzero_pd(), _CMP_UNORD_Q);
	return !(_mm256_movemask_pd(nanMask) & 0x3);
}

template <> 
HK_FORCE_INLINE hkBool32 hkVector4d::isOk<3>() const
{
	const hkQuadDouble64 nanMask = _mm256_cmp_pd(m_quad, _mm256_setzero_pd(), _CMP_UNORD_Q);
	return !(_mm256_movemask_pd(nanMask) & 0x7);
}

template <> 
HK_FORCE_INLINE hkBool32 hkVector4d::isOk<4>() const
{
	const hkQuadDouble64 nanMask = _mm256_cmp_pd(m_quad, _mm256_setzero_pd(), _CMP_UNORD_Q);
	return !(_mm256_movemask_pd(nanMask));
}

template <int N> 
HK_FORCE_INLINE hkBool32 hkVector4d::isOk() const
{
	HK_VECTOR4d_NOT_IMPLEMENTED;
	return false;
}


template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::XYXY>(hkVector4dParameter v)
{
	m_quad = _mm256_permute2f128_pd(v.m_quad, v.m_quad, _MM256_PERMUTE2(_MM256_A_LOW, _MM256_A_LOW));
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::ZWXY>(hkVector4dParameter v)
{
	m_quad = _mm256_permute2f128_pd(v.m_quad, v.m_quad, _MM256_PERMUTE2(_MM256_A_LOW, _MM256_A_HIGH));
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::ZWZW>(hkVector4dParameter v)
{
	m_quad = _mm256_permute2f128_pd(v.m_quad, v.m_quad, _MM256_PERMUTE2(_MM256_A_HIGH, _MM256_A_HIGH));
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::ZWXW>(hkVector4dParameter v)
{
	__m256d zwxy = _mm256_permute2f128_pd(v.m_quad, v.m_quad, _MM256_PERMUTE2(_MM256_A_LOW, _MM256_A_HIGH));
	m_quad = _mm256_blend_pd(zwxy, v.m_quad, 0x8);
}

// template <> 
// HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::ZXYW>(hkVector4dParameter v)
// {
// }

// template <> 
// HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::ZXYZ>(hkVector4dParameter v)
// {
// }

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::XXZZ>(hkVector4dParameter v)
{
	m_quad = _mm256_movedup_pd(v.m_quad);
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::XXYY>(hkVector4dParameter v)
{
	__m256d xyxy = _mm256_permute2f128_pd(v.m_quad, v.m_quad, _MM256_PERMUTE2(_MM256_A_LOW, _MM256_A_LOW));
	m_quad = _mm256_permute_pd(xyxy, 0xC);
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::XXXX>(hkVector4dParameter v)
{
	__m256d xxzz = _mm256_movedup_pd(v.m_quad);
	m_quad = _mm256_permute2f128_pd(xxzz, xxzz, _MM256_PERMUTE2(_MM256_A_LOW, _MM256_A_LOW));
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::YYYY>(hkVector4dParameter v)
{
	__m256d xyxy = _mm256_permute2f128_pd(v.m_quad, v.m_quad, _MM256_PERMUTE2(_MM256_A_LOW, _MM256_A_LOW));
	m_quad = _mm256_unpackhi_pd(xyxy);
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::ZZZZ>(hkVector4dParameter v)
{
	__m256d xxzz = _mm256_movedup_pd(v.m_quad);
	m_quad = _mm256_permute2f128_pd(xxzz, xxzz, _MM256_PERMUTE2(_MM256_A_HIGH, _MM256_A_HIGH));
}

// template <> 
// HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::ZYZZ>(hkVector4dParameter v)
// {
// }

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::XYZZ>(hkVector4dParameter v)
{
	m_quad = _mm256_permute_pd(v.m_quad, 0x2);
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::YYXX>(hkVector4dParameter v)
{
	__m256d xxyy = _mm256_unpacklo_pd(v.m_quad);
	m_quad = _mm256_permute2f128_pd(xxyy, xxyy, _MM256_PERMUTE2(_MM256_A_LOW, _MM256_A_HIGH));
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::ZZYY>(hkVector4dParameter v)
{
	__m256d xxzz = _mm256_unpacklo_pd(v.m_quad, v.m_quad);
	__m256d yyww = _mm256_unpackhi_pd(v.m_quad, v.m_quad);
	m_quad = _mm256_permute2f128_pd(xxzz,yyww,_MM256_PERMUTE2(_MM256_A_LOW, _MM256_A_HIGH));
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::YXWZ>(hkVector4dParameter v)
{
	m_quad = _mm256_permute_pd(v.m_quad, 0x5);
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::YXXY>(hkVector4dParameter v)
{
	__m256d yxwz = _mm256_permute_pd(v.m_quad, 0x5);
	m_quad = _mm256_permute2f128_pd(yxwz, v.m_quad, _MM256_PERMUTE2(_MM256_A_LOW, _MM256_A_LOW));
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::XYWZ>(hkVector4dParameter v)
{
	m_quad = _mm256_permute_pd(v.m_quad, 0x6);
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::XZYW>(hkVector4dParameter v)
{
	__m256d yyzz = _mm256_permute_pd(v.m_quad, 0x3);
	__m256d zzyy = _mm256_permute2f128_pd(yyzz, yyzz, _MM256_PERMUTE2(_MM256_A_LOW, _MM256_A_HIGH));
	m_quad = _mm256_blend_pd(v.m_quad, zzyy, 0x6);
}

// template <> 
// HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::YZXW>(hkVector4dParameter v)
// {
// }

// template <> 
// HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::YZXZ>(hkVector4dParameter v)
// {
// }

// template <> 
// HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::YZWX>(hkVector4dParameter v)
// {
// }

// template <> 
// HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::YWZX>(hkVector4dParameter v)
// {
// }

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::YXZW>(hkVector4dParameter v)
{
	m_quad = _mm256_permute_pd(v.m_quad, 0x9);
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::XYZW>(hkVector4dParameter v)
{
	m_quad = v.m_quad;
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::YXWW>(hkVector4dParameter v)
{
	m_quad = _mm256_permute_pd(v.m_quad, 0xD);
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::XYWW>(hkVector4dParameter v)
{
	m_quad = _mm256_permute_pd(v.m_quad, 0xE);
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::YYWW>(hkVector4dParameter v)
{
	m_quad = _mm256_unpackhi_pd(v.m_quad);
}

template <> 
HK_FORCE_INLINE void hkVector4d::setPermutation<hkVectorPermutation::WXYZ>(hkVector4dParameter v)
{
	__m256d yxwz = _mm256_permute_pd(v.m_quad, 0x5);
	__m256d zwxy = _mm256_permute2f128_pd(v.m_quad, v.m_quad, _MM256_PERMUTE2(_MM256_A_LOW, _MM256_A_HIGH));
	m_quad = _mm256_shuffle_pd(zwxy, yxwz, _MM256_SHUFFLE(1,1,1,1));
}

template <hkVectorPermutation::Permutation P> 
HK_FORCE_INLINE void hkVector4d::setPermutation(hkVector4dParameter v)
{
	const hkQuadDouble64 X = broadcastScalar<(P>>12)&0x3>(v);
	const hkQuadDouble64 Y = broadcastScalar<(P>>8)&0x3>(v);
	const hkQuadDouble64 Z = broadcastScalar<(P>>4)&0x3>(v);
	const hkQuadDouble64 W = broadcastScalar<(P)&0x3>(v);

	const hkQuadDouble64 xxzz = _mm256_permute2f128_pd(X, Z, _MM256_PERMUTE2(_MM256_A_HIGH, _MM256_A_LOW));
	const hkQuadDouble64 yyww = _mm256_permute2f128_pd(Y, W, _MM256_PERMUTE2(_MM256_A_HIGH, _MM256_A_LOW));
	m_quad = _mm256_shuffle_pd(xxzz, yyww, _MM256_SHUFFLE(1,0,1,0));
}

HK_FORCE_INLINE const hkVector4dComparison hkVector4d::signBitSet() const
{
	const __m256i s = _mm256_srai_epi32(_mm256_castpd_si256(m_quad),31); // ssssssssXXXXXXXX all 4
	hkQuadDouble64 q = _mm256_castps_pd(_mm256_movehdup_ps(_mm256_castsi256_ps(s)));
	return hkVector4dComparison::convert(q);
}

HK_FORCE_INLINE const hkVector4dComparison hkVector4d::signBitClear() const
{
	const __m256i s = _mm256_srai_epi32(_mm256_castpd_si256(m_quad),31); // ssssssssXXXXXXXX all 4
	const __m256i mask = _mm256_cmpeq_epi32(s,_mm256_setzero_si256());   // mmmmmmmmXXXXXXXX all 4
	hkQuadDouble64 q = _mm256_castps_pd(_mm256_movehdup_ps(_mm256_castsi256_ps(mask)));
	return hkVector4dComparison::convert(q);
}

HK_FORCE_INLINE void hkVector4d::setFlipSign(hkVector4dParameter v, hkVector4dComparisonParameter mask)
{
	const __m256i s = _mm256_slli_epi32(_mm256_srli_epi32(_mm256_castpd_si256(mask.m_mask),31),31); // s0000000XXXXXXXX all 4
	m_quad = _mm256_xor_pd(v.m_quad, _mm256_castps_pd(_mm256_blend_ps(_mm256_castsi256_ps(s),_mm256_setzero_ps(),0xaa)));
}

HK_FORCE_INLINE void hkVector4d::setFlipSign(hkVector4dParameter v, hkVector4dParameter vSign)
{
	const __m256i s = _mm256_slli_epi32(_mm256_srli_epi32(_mm256_castpd_si256(vSign.m_quad),31),31); // s0000000XXXXXXXX all 4
	m_quad = _mm256_xor_pd(v.m_quad, _mm256_castps_pd(_mm256_blend_ps(_mm256_castsi256_ps(s),_mm256_setzero_ps(),0xaa)));
}

HK_FORCE_INLINE void hkVector4d::setFlipSign(hkVector4dParameter v, hkSimdDouble64Parameter sSign)
{
	const __m128i mask = _mm_slli_epi64(_mm_srli_epi64(_mm_castpd_si128(sSign.m_real),63),63);
	const hkQuadDouble64 s = _mm256_broadcast_pd(&_mm_castsi128_pd(mask));
	m_quad = _mm256_xor_pd(v.m_quad, s);
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
				const __m128 xyzw = _mm256_cvtpd_ps(a.m_quad);
				const __m128 re = _mm_rcp_ps(xyzw);
				self = _mm256_cvtps_pd(re);
			}
			break;
		default:		 
			{
				self = _mm256_div_pd(g_vectordConstants[HK_QUADREAL_1], a.m_quad); 
			}
			break; // HK_ACC_FULL
	}
} };
template <hkMathAccuracyMode A>
struct unrolld_setReciprocal<A, HK_DIV_SET_ZERO> { HK_FORCE_INLINE static void apply(hkQuadDouble64& self, hkVector4dParameter a)
{
	const hkQuadDouble64 equalsZero = _mm256_cmp_pd(a.m_quad, _mm256_setzero_pd(), _CMP_EQ_OQ);
	hkQuadDouble64 e; unrolld_setReciprocal<A, HK_DIV_IGNORE>::apply(e, a);
	self = _mm256_andnot_pd(equalsZero, e);
} };
template <hkMathAccuracyMode A>
struct unrolld_setReciprocal<A, HK_DIV_SET_HIGH> { HK_FORCE_INLINE static void apply(hkQuadDouble64& self, hkVector4dParameter a)
{
	const hkQuadDouble64 equalsZero = _mm256_cmp_pd(a.m_quad, _mm256_setzero_pd(), _CMP_EQ_OQ);
	hkQuadDouble64 e; unrolld_setReciprocal<A, HK_DIV_IGNORE>::apply(e, a);
	const hkQuadDouble64 huge = _mm256_set1_pd(HK_DOUBLE_HIGH);
	self = _mm256_blendv_pd(e, huge, equalsZero);
} };
template <hkMathAccuracyMode A>
struct unrolld_setReciprocal<A, HK_DIV_SET_MAX> { HK_FORCE_INLINE static void apply(hkQuadDouble64& self, hkVector4dParameter a)
{
	const hkQuadDouble64 equalsZero = _mm256_cmp_pd(a.m_quad, _mm256_setzero_pd(), _CMP_EQ_OQ);
	hkQuadDouble64 e; unrolld_setReciprocal<A, HK_DIV_IGNORE>::apply(e, a);
	const hkQuadDouble64 huge = _mm256_set1_pd(HK_DOUBLE_MAX);
	self = _mm256_blendv_pd(e, huge, equalsZero);
} };
template <hkMathAccuracyMode A>
struct unrolld_setReciprocal<A, HK_DIV_SET_ZERO_AND_ONE> { HK_FORCE_INLINE static void apply(hkQuadDouble64& self, hkVector4dParameter a)
{
	unrolld_setReciprocal<A, HK_DIV_SET_ZERO>::apply(self, a);
	const hkQuadDouble64 one = g_vectordConstants[HK_QUADREAL_1];
	const hkQuadDouble64 absVal = hkMath::quadFabs(_mm256_sub_pd(self, one));
	const hkQuadDouble64 lessEqualEps = _mm256_cmp_pd(absVal, g_vectordConstants[HK_QUADREAL_EPS], _CMP_LE_OQ);
	self = _mm256_blendv_pd(self, one, lessEqualEps);
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
				self = _mm256_mul_pd(a.m_quad,re); 
			}
			break;
		case HK_ACC_12_BIT: 
			{
				const __m128 xyzw = _mm256_cvtpd_ps(a.m_quad);
				const __m128 re = _mm_rcp_ps(xyzw);
				self = _mm256_mul_pd(a.m_quad,_mm256_cvtps_pd(re));
			}
			break;
		default:         
			{
				self = _mm256_div_pd(a.m_quad, b.m_quad); 
			}
			break; // HK_ACC_FULL
	}
} };
template <hkMathAccuracyMode A>
struct unrolld_setDiv<A, HK_DIV_SET_ZERO> { HK_FORCE_INLINE static void apply(hkQuadDouble64& self, hkVector4dParameter a, hkVector4dParameter b)
{
	const hkQuadDouble64 equalsZero = _mm256_cmp_pd(b.m_quad, _mm256_setzero_pd(), _CMP_EQ_OQ);
	hkQuadDouble64 e; unrolld_setDiv<A, HK_DIV_IGNORE>::apply(e, a, b);
	self = _mm256_andnot_pd(equalsZero, e);
} };
template <hkMathAccuracyMode A>
struct unrolld_setDiv<A, HK_DIV_SET_HIGH> { HK_FORCE_INLINE static void apply(hkQuadDouble64& self, hkVector4dParameter a, hkVector4dParameter b)
{
	static HK_ALIGN32( const hkUint64 signmask[4] ) = { 0x8000000000000000, 0x8000000000000000, 0x8000000000000000, 0x8000000000000000 };
	const hkQuadDouble64 equalsZero = _mm256_cmp_pd(b.m_quad, _mm256_setzero_pd(), _CMP_EQ_OQ);
	hkQuadDouble64 e; unrolld_setDiv<A, HK_DIV_IGNORE>::apply(e, a, b);
	hkQuadDouble64 huge = _mm256_set1_pd(HK_DOUBLE_HIGH);
	huge = _mm256_xor_pd(huge, _mm256_and_pd(a.m_quad, *(const __m256d*)&signmask));
	self = _mm256_blendv_pd(e, huge, equalsZero);
} };
template <hkMathAccuracyMode A>
struct unrolld_setDiv<A, HK_DIV_SET_MAX> { HK_FORCE_INLINE static void apply(hkQuadDouble64& self, hkVector4dParameter a, hkVector4dParameter b)
{
	static HK_ALIGN32( const hkUint64 signmask[4] ) = { 0x8000000000000000, 0x8000000000000000, 0x8000000000000000, 0x8000000000000000 };
	const hkQuadDouble64 equalsZero = _mm256_cmp_pd(b.m_quad, _mm256_setzero_pd(), _CMP_EQ_OQ);
	hkQuadDouble64 e; unrolld_setDiv<A, HK_DIV_IGNORE>::apply(e, a, b);
	hkQuadDouble64 huge = _mm256_set1_pd(HK_DOUBLE_MAX);
	huge = _mm256_xor_pd(huge, _mm256_and_pd(a.m_quad, *(const __m256d*)&signmask));
	self = _mm256_blendv_pd(e, huge, equalsZero);
} };
template <hkMathAccuracyMode A>
struct unrolld_setDiv<A, HK_DIV_SET_ZERO_AND_ONE> { HK_FORCE_INLINE static void apply(hkQuadDouble64& self, hkVector4dParameter a, hkVector4dParameter b)
{
	unrolld_setDiv<A, HK_DIV_SET_ZERO>::apply(self, a, b);
	const hkQuadDouble64 one = g_vectordConstants[HK_QUADREAL_1];
	const hkQuadDouble64 absVal = hkMath::quadFabs(_mm256_sub_pd(self, one));
	const hkQuadDouble64 lessEqualEps = _mm256_cmp_pd(absVal, g_vectordConstants[HK_QUADREAL_EPS], _CMP_LE_OQ);
	self = _mm256_blendv_pd(self, one, lessEqualEps);
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
				self = _mm256_mul_pd(a.m_quad,re); 
			}
			break;
		case HK_ACC_12_BIT: 
			{
				const __m128 xyzw = _mm256_cvtpd_ps(a.m_quad);
				const __m128 re = _mm_rsqrt_ps(xyzw);
				self = _mm256_mul_pd(a.m_quad,_mm256_cvtps_pd(re));
			}
			break;
		default:         
			{
				self = _mm256_sqrt_pd(a.m_quad); 
			}
			break; // HK_ACC_FULL
	}
} };
template <hkMathAccuracyMode A>
struct unrolld_setSqrt<A, HK_SQRT_SET_ZERO> { HK_FORCE_INLINE static void apply(hkQuadDouble64& self, hkVector4dParameter a)
{
	const hkQuadDouble64 equalsZero = _mm256_cmp_pd(a.m_quad, _mm256_setzero_pd(), _CMP_LE_OQ);
	hkQuadDouble64 e; unrolld_setSqrt<A, HK_SQRT_IGNORE>::apply(e,a);
	self = _mm256_andnot_pd(equalsZero, e);
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
			const __m128 xyzw = _mm256_cvtpd_ps(a.m_quad);
			const __m128 re = _mm_rsqrt_ps(xyzw);
			self = _mm256_cvtps_pd(re);
		}
		break;
	default:         
		{
			self = _mm256_div_pd(g_vectordConstants[HK_QUADREAL_1], _mm256_sqrt_pd(a.m_quad));
		}
		break; // HK_ACC_FULL
	}
} };
template <hkMathAccuracyMode A>
struct unrolld_setSqrtInverse<A, HK_SQRT_SET_ZERO> { HK_FORCE_INLINE static void apply(hkQuadDouble64& self, hkVector4dParameter a)
{
	const hkQuadDouble64 equalsZero = _mm256_cmp_pd(a.m_quad, _mm256_setzero_pd(), _CMP_LE_OQ);
	hkQuadDouble64 e; unrolld_setSqrtInverse<A, HK_SQRT_IGNORE>::apply(e,a);
	self = _mm256_andnot_pd(equalsZero, e);
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
			self = _mm256_cvtps_pd(a);
			HK_ON_DEBUG( *(hkUint64*)&(self.m256d_f64[1]) = 0xffffffffffffffff; )
			HK_ON_DEBUG( *(hkUint64*)&(self.m256d_f64[2]) = 0xffffffffffffffff; *(hkUint64*)&(self.m256d_f64[3]) = 0xffffffffffffffff; )
		}
		break;
	case 2:
		{
			__m128d a = _mm_load_sd((const double*)p);
			self = _mm256_cvtps_pd(_mm_castpd_ps(a));
			HK_ON_DEBUG( *(hkUint64*)&(self.m256d_f64[2]) = 0xffffffffffffffff; *(hkUint64*)&(self.m256d_f64[3]) = 0xffffffffffffffff; )
		}
		break;
	case 3:
		{
			__m128d a = _mm_load_sd((const double*)p);
			__m128d b = _mm_cvtps_pd(_mm_load_ss(p+2));
			self = _mm256_cvtps_pd(_mm_castpd_ps(a));
			self = _mm256_insertf128_pd(self, b, 1);
			HK_ON_DEBUG( *(hkUint64*)&(self.m256d_f64[3]) = 0xffffffffffffffff; )
		}
		break;
	default:
		{
			__m128 a = _mm_castsi128_ps(_mm_lddqu_si128((const __m128i*)p));
			self = _mm256_cvtps_pd(a);
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
			self = _mm256_broadcast_sd(p);
			HK_ON_DEBUG( *(hkUint64*)&(self.m256d_f64[1]) = 0xffffffffffffffff; )
			HK_ON_DEBUG( *(hkUint64*)&(self.m256d_f64[2]) = 0xffffffffffffffff; *(hkUint64*)&(self.m256d_f64[3]) = 0xffffffffffffffff; )
		}
		break;
	case 2:
		{
			__m128d a = _mm_loadu_pd(p);
			self = _mm256_broadcast_pd(&a);
			HK_ON_DEBUG( *(hkUint64*)&(self.m256d_f64[2]) = 0xffffffffffffffff; *(hkUint64*)&(self.m256d_f64[3]) = 0xffffffffffffffff; )
		}
		break;
	case 3:
		{
			__m128d a = _mm_loadu_pd(p);
			__m128d b = _mm_load_sd(p+2);
			self = _mm256_broadcast_pd(&a);
			self = _mm256_insertf128_pd(self, b, 1);
			HK_ON_DEBUG( *(hkUint64*)&(self.m256d_f64[3]) = 0xffffffffffffffff; )
		}
		break;
	default:
		{
			self = _mm256_loadu_pd(p);
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
		self = _mm256_cvtps_pd(a);
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
			__m128d a = _mm_load_pd(p);
			self = _mm256_broadcast_pd(&a);
			HK_ON_DEBUG( *(hkUint64*)&(self.m256d_f64[2]) = 0xffffffffffffffff; *(hkUint64*)&(self.m256d_f64[3]) = 0xffffffffffffffff; )
		}
		break;
	case 3:
		{
			__m128d a = _mm_load_pd(p);
			__m128d b = _mm_load_sd(p+2);
			self = _mm256_broadcast_pd(&a);
			self = _mm256_insertf128_pd(self, b, 1);
			HK_ON_DEBUG( *(hkUint64*)&(self.m256d_f64[3]) = 0xffffffffffffffff; )
		}
		break;
	case 4:
		{
			self = _mm256_load_pd(p);
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
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & ((sizeof(hkFloat32)*(N!=3?N:4) )-1) ) == 0, "pointer must be aligned for SIMD.");
	if (N==4)
	{
		__m128 a = _mm_castsi128_ps(_mm_stream_load_si128((__m128i*) p));
		self = _mm256_cvtps_pd(a);
	}
	else
	{
		unrolld_load<N, HK_IO_SIMD_ALIGNED>::apply(self,p);
	}
} };
template <int N>
struct unrolld_load_D<N, HK_IO_NOT_CACHED> { HK_FORCE_INLINE static void apply(hkQuadDouble64& self, const hkDouble64* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & ((sizeof(hkDouble64)*(N!=3?N:4) )-1) ) == 0, "pointer must be aligned for SIMD.");
	switch (N)
	{
	case 2:
		{
			__m128d a = _mm_castsi128_pd(_mm_stream_load_si128((__m128i*) p));
			self = _mm256_broadcast_pd(&a);
			HK_ON_DEBUG( *(hkUint64*)&(self.m256d_f64[2]) = 0xffffffffffffffff; *(hkUint64*)&(self.m256d_f64[3]) = 0xffffffffffffffff; )
		}
		break;
	case 3:
		{
			__m128d a = _mm_castsi128_pd(_mm_stream_load_si128((__m128i*) p));
			__m128d b = _mm_load_sd(p+2);
			self = _mm256_broadcast_pd(&a);
			self = _mm256_insertf128_pd(self, b, 1);
			HK_ON_DEBUG( *(hkUint64*)&(self.m256d_f64[3]) = 0xffffffffffffffff; )
		}
		break;
	case 4:
		{
			__m128d a = _mm_castsi128_pd(_mm_stream_load_si128((__m128i*) p));
			__m128d b = _mm_castsi128_pd(_mm_stream_load_si128((__m128i*)(p+2)));
			self = _mm256_broadcast_pd(&a);
			self = _mm256_insertf128_pd(self, b, 1);
		}
		break;
	default:
		{
			unrolld_load_D<N, HK_IO_SIMD_ALIGNED>::apply(self,p);
		}
		break;
	}
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
			self = _mm256_cvtps_pd(twofloats);
			HK_ON_DEBUG( *(hkUint64*)&(self.m128d_f64[1]) = 0xffffffffffffffff; )
			HK_ON_DEBUG( *(hkUint64*)&(self.m128d_f64[0]) = 0xffffffffffffffff; *(hkUint64*)&(self.m128d_f64[1]) = 0xffffffffffffffff; )
		}
		break;
	case 2:
		{
			__m128  twofloats = _mm_castpd_ps(_mm_load_sd((const double*)p));
			self = _mm256_cvtps_pd(twofloats);
			HK_ON_DEBUG( *(hkUint64*)&(self.m128d_f64[0]) = 0xffffffffffffffff; *(hkUint64*)&(self.m128d_f64[1]) = 0xffffffffffffffff; )
		}
		break;
	case 3:
		{
			__m128 xy = _mm_castpd_ps(_mm_load_sd((const double*)p));
			__m128 z = _mm_load_ss((const float*)p+2);
			__m128  fourfloats = _mm_movelh_ps(xy,z);
			self = _mm256_cvtps_pd(fourfloats);
			HK_ON_DEBUG( *(hkUint64*)&(self.m128d_f64[1]) = 0xffffffffffffffff; )
		}
		break;
	default:
		{
#if HK_SSE_VERSION >= 0x30
			__m128  fourfloats = _mm_castsi128_ps(_mm_lddqu_si128((const __m128i*)p));
#else
			__m128  fourfloats = _mm_loadu_ps((const float*)p);
#endif
			self = _mm256_cvtps_pd(fourfloats);
		}
		break;
	}
#else
	switch (N)
	{
	case 1:
		{
			HK_ALIGN16(hkHalf tmp[2]);
			tmp[0] = p[0];
			__m128i twohalfs = _mm_castps_si128( _mm_load_ss((const float*)tmp) );
			__m128  twofloats = _mm_castsi128_ps( _mm_unpacklo_epi16(_mm_setzero_si128(), twohalfs) );
			self = _mm256_cvtps_pd(twofloats);
			HK_ON_DEBUG( *(hkUint64*)&(self.m256d_f64[1]) = 0xffffffffffffffff; *(hkUint64*)&(self.m256d_f64[2]) = 0xffffffffffffffff; *(hkUint64*)&(self.m256d_f64[3]) = 0xffffffffffffffff; )
		}
		break;
	case 2:
		{
			__m128i twohalfs = _mm_castps_si128( _mm_load_ss((const float*)p) );
			__m128  twofloats = _mm_castsi128_ps( _mm_unpacklo_epi16(_mm_setzero_si128(), twohalfs) );
			self = _mm256_cvtps_pd(twofloats);
			HK_ON_DEBUG( *(hkUint64*)&(self.m256d_f64[2]) = 0xffffffffffffffff; *(hkUint64*)&(self.m256d_f64[3]) = 0xffffffffffffffff; )
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
			self = _mm256_cvtps_pd(fourfloats);
			HK_ON_DEBUG( *(hkUint64*)&(self.m256d_f64[3]) = 0xffffffffffffffff; )
		}
		break;
	default:
		{
			__m128i fourhalfs = _mm_loadl_epi64((const __m128i*)p);
			__m128  fourfloats = _mm_castsi128_ps( _mm_unpacklo_epi16(_mm_setzero_si128(), fourhalfs) );
			self = _mm256_cvtps_pd(fourfloats);
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
		{
#if defined(HK_HALF_IS_FLOAT)
			__m128  fourfloats = _mm_load_ps((const float*)p);
#else
			__m128i fourhalfs = _mm_loadl_epi64((const __m128i*)p);
			__m128  fourfloats = _mm_castsi128_ps( _mm_unpacklo_epi16(_mm_setzero_si128(), fourhalfs) );
#endif
			self = _mm256_cvtps_pd(fourfloats);
		}
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
	unrolld_loadH<N, HK_IO_SIMD_ALIGNED>::apply(self,p);
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
	self = _mm256_cvtps_pd(fourfloats);

#ifdef HK_DEBUG
	switch (N)
	{
	case 1: *(hkUint64*)&(self.m256d_f64[1]) = 0xffffffffffffffff;
	case 2: *(hkUint64*)&(self.m256d_f64[2]) = 0xffffffffffffffff;
	case 3: *(hkUint64*)&(self.m256d_f64[3]) = 0xffffffffffffffff;
	default:
		break;
	}
#endif
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
	__m128 xyzw = _mm256_cvtpd_ps(self);
	switch (N)
	{
	case 1:
		{
			_mm_store_ss(p, xyzw);
		}
		break;
	case 2:
		{
			_mm_store_sd((double*)p, _mm_castps_pd(xyzw));
		}
		break;
	case 3:
		{
			_mm_store_sd((double*)p, _mm_castps_pd(xyzw));
			_mm_store_ss(p+2, _mm_movehl_ps(xyzw,xyzw));
		}
		break;
	default:
		{
			_mm_storeu_ps(p, xyzw);
		}
		break;
	}
} };
template <int N>
struct unrolld_store_D<N, HK_IO_BYTE_ALIGNED> { HK_FORCE_INLINE static void apply(const hkQuadDouble64& self, hkDouble64* HK_RESTRICT p)
{
	static HK_ALIGN32( const hkUint64 mask1[4] ) = { 0xffffffffffffffff, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000 };
	static HK_ALIGN32( const hkUint64 mask2[4] ) = { 0xffffffffffffffff, 0xffffffffffffffff, 0x0000000000000000, 0x0000000000000000 };
	static HK_ALIGN32( const hkUint64 mask3[4] ) = { 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0x0000000000000000 };
	switch (N)
	{
	case 1:
		{
			_mm256_maskstore_pd(p, *(__m256i*)&mask1, self);
		}
		break;
	case 2:
		{
			_mm256_maskstore_pd(p, *(__m256i*)&mask2, self);
		}
		break;
	case 3:
		{
			_mm256_maskstore_pd(p, *(__m256i*)&mask3, self);
		}
		break;
	default:
		{
			_mm256_storeu_pd(p, self);
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
		__m128 xyzw = _mm256_cvtpd_ps(self);
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
	if (N==4)
	{
		_mm256_store_pd(p, self);
	}
	else
	{
		unrolld_store_D<N, HK_IO_NATIVE_ALIGNED>::apply(self,p);
	}
} };
template <int N>
struct unrolld_store<N, HK_IO_NOT_CACHED> { HK_FORCE_INLINE static void apply(const hkQuadDouble64& self, hkFloat32* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & ((sizeof(hkFloat32)*(N!=3?N:4) )-1) ) == 0, "pointer must be aligned for SIMD.");
	if (N==4)
	{
		__m128 xyzw = _mm256_cvtpd_ps(self);
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
	if (N==4)
	{
		_mm256_stream_pd(p, self);
	}
	else
	{
		unrolld_store_D<N, HK_IO_SIMD_ALIGNED>::apply(self,p);
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
template <hkMathRoundingMode R>
HK_FORCE_INLINE static void convertf64half(const hkQuadDouble64& self, __m128i& packed)
{
	static HK_ALIGN16(const unsigned int scale[4])      = {0x3F808000, 0x3F808000, 0x3F808000, 0x3F808000}; // 1 + 1/256 as float32

	__m128 xyzw = _mm256_cvtpd_ps(self);

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
	static HK_ALIGN32(const hkUint64 mask[4])      = {0xFFFFFFFF00000000ull, 0xFFFFFFFF00000000ull, 0xFFFFFFFF00000000ull, 0xFFFFFFFF00000000ull};

	switch (N)
	{
	case 1:
		{
			__m256d vs0;
			if (R == HK_ROUND_NEAREST)
				vs0 = self;
			else
				vs0 = _mm256_and_pd(self, *((__m256d*)&mask));
			_mm_store_ss((float*)p, _mm256_cvtpd_ps(vs0));
		}
		break;
	case 2:
		{
			__m256d vs0;
			if (R == HK_ROUND_NEAREST)
				vs0 = self;
			else
				vs0 = _mm256_and_pd(self, *((__m256d*)&mask));
			__m128 twofloats = _mm256_cvtpd_ps(vs0);
			_mm_store_sd((double*) p, _mm_castps_pd(twofloats));
		}
		break;
	case 3:
		{
			__m256d xyzw;
			if (R == HK_ROUND_NEAREST)
			{
				xyzw = self;
			}
			else
			{
				xyzw = _mm256_and_pd(self, *((__m256d*)&mask));
			}
			__m128 xyzw_f = _mm256_cvtpd_ps(xyzw);
			_mm_store_sd((double*) p, _mm_castps_pd(xyzw_f));
			_mm_store_ss((float*)p+2, _mm_movehl_ps(xyzw_f,xyzw_f));
		}
		break;
	default:
		{
			__m256d xyzw;
			if (R == HK_ROUND_NEAREST)
			{
				xyzw = self;
			}
			else
			{
				xyzw = _mm256_and_pd(self, *((__m256d*)&mask));
			}
			__m128 xyzw_f = _mm256_cvtpd_ps(xyzw);
			_mm_storeu_ps((float*)p, xyzw_f);
		}
		break;
	}
#else
	__m128i packed;
	convertf64half<R>(self,packed);

	switch (N)
	{
	case 1:
		{
			HK_ALIGN16(hkHalf tmp[2];)
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
			HK_ALIGN16(hkHalf tmp[4];)
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
	switch (N)
	{
	case 4:
		{
#if defined(HK_HALF_IS_FLOAT)
			__m256d xyzw;
			if (R == HK_ROUND_NEAREST)
			{
				xyzw = self;
			}
			else
			{
				xyzw = _mm256_and_pd(self, *((__m256d*)&mask));
			}
			__m128 xyzw_f = _mm256_cvtpd_ps(xyzw);
			_mm_store_ps((float*)p, xyzw_f);
#else
			__m128i packed;
			convertf64half<R>(self,packed);
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
	switch (N)
	{
	case 4:
		{
#if defined(HK_HALF_IS_FLOAT)
			__m256d xyzw;
			if (R == HK_ROUND_NEAREST)
			{
				xyzw = self;
			}
			else
			{
				xyzw = _mm256_and_pd(self, *((__m256d*)&mask));
			}
			__m128 xyzw_f = _mm256_cvtpd_ps(xyzw);
			_mm_stream_ps((float*)p, xyzw_f);
#else
			__m128i packed;
			convertf64half<R>(self,packed);
			_mm_storel_epi64((__m128i*)p, packed);
#endif
		}
		break;
	default:
		{
			unrolld_storeH<N, HK_IO_SIMD_ALIGNED, R>::apply(self,p);
		}
		break;
	}
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
template <hkMathRoundingMode R>
HK_FORCE_INLINE static void convertf64f16(const hkQuadDouble64& self, __m128i& packed)
{
	static HK_ALIGN16(const unsigned int abs[4])      = {0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF};
	static HK_ALIGN16(const unsigned int infinity[4]) = {0x47FFE000, 0x47FFE000, 0x47FFE000, 0x47FFE000};
	static HK_ALIGN16(const unsigned int denormal[4]) = {0x38800000, 0x38800000, 0x38800000, 0x38800000};
	static HK_ALIGN16(const unsigned int fixup[4])    = {0x48000000, 0x48000000, 0x48000000, 0x48000000};
	static HK_ALIGN16(const unsigned int round1[4])   = {0x00000001, 0x00000001, 0x00000001, 0x00000001};
	static HK_ALIGN16(const unsigned int round2[4])   = {0x00000FFF, 0x00000FFF, 0x00000FFF, 0x00000FFF};
	static HK_ALIGN16(const unsigned int sign[4])     = {0x80000000, 0x80000000, 0x80000000, 0x80000000};
	static HK_ALIGN16(const unsigned int base[4])     = {0x00007FFF, 0x00007FFF, 0x00007FFF, 0x00007FFF};
	static HK_ALIGN16(const unsigned int integer[4])  = {0x52000000, 0x52000000, 0x52000000, 0x52000000};

	__m128 xyzw = _mm256_cvtpd_ps(self);

	// Compute masks
	__m128 r_abs = _mm_and_ps(xyzw, *(__m128*)abs);
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
	__m128i extract_sign = _mm_srai_epi32(_mm_and_si128(_mm_castps_si128(xyzw), *(__m128i*)sign), 16);
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
	convertf64f16<R>(self,packed);
	switch (N)
	{
	case 1:
		{
			HK_ALIGN16(hkFloat16 tmp[2];)
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
			HK_ALIGN16(hkFloat16 tmp[4];)
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
			convertf64f16<R>(self,packed);
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
