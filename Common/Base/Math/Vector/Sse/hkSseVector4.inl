/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */


#if HK_SSE_VERSION >= 0x41
#define HK_VECTOR4f_COMBINE_XYZ_W(xyz, w) _mm_blend_ps( xyz, w, 0x8)
#else
#define HK_VECTOR4f_COMBINE_XYZ_W(xyz, w) _mm_shuffle_ps( xyz, _mm_unpackhi_ps(xyz, w), _MM_SHUFFLE(3,0,1,0))
#endif

/* quad, here for inlining */

#ifndef HK_DISABLE_MATH_CONSTRUCTORS
/* construct, assign, zero */
HK_FORCE_INLINE hkVector4f::hkVector4f(hkFloat32 a, hkFloat32 b, hkFloat32 c, hkFloat32 d)
{
	m_quad = _mm_setr_ps(a,b,c,d);
}

HK_FORCE_INLINE hkVector4f::hkVector4f(const hkQuadFloat32& q)
{
	m_quad = q;
}

HK_FORCE_INLINE hkVector4f::hkVector4f(const hkVector4f& v)
{
	m_quad = v.m_quad;
}
#endif

HK_FORCE_INLINE void hkVector4f::set(hkFloat32 a, hkFloat32 b, hkFloat32 c, hkFloat32 d)
{
	m_quad = _mm_setr_ps(a,b,c,d);
}

HK_FORCE_INLINE void hkVector4f::set( hkSimdFloat32Parameter a, hkSimdFloat32Parameter b, hkSimdFloat32Parameter c, hkSimdFloat32Parameter d )
{
	const hkQuadFloat32 ab = _mm_unpacklo_ps(a.m_real, b.m_real);
	const hkQuadFloat32 cd = _mm_unpacklo_ps(c.m_real, d.m_real);
	m_quad = _mm_movelh_ps(ab,cd);
}

HK_FORCE_INLINE void hkVector4f::setAll(const hkFloat32& a)
{
	m_quad = _mm_set1_ps(a);
}

HK_FORCE_INLINE void hkVector4f::setAll(hkSimdFloat32Parameter a)
{
	m_quad = a.m_real;
}

HK_FORCE_INLINE void hkVector4f::setZero()
{
	m_quad = _mm_setzero_ps();
}

#if HK_SSE_VERSION >= 0x41
template <int I> 
HK_FORCE_INLINE void hkVector4f::zeroComponent()
{
	HK_VECTOR4f_SUBINDEX_CHECK;
	m_quad = _mm_blend_ps(m_quad, _mm_setzero_ps(), 1 << I);
}
#else
template <> 
HK_FORCE_INLINE void hkVector4f::zeroComponent<0>()
{
	m_quad = _mm_castsi128_ps(_mm_slli_si128(_mm_srli_si128(_mm_castps_si128(m_quad),4),4));
}
template <>
HK_FORCE_INLINE void hkVector4f::zeroComponent<1>()
{
	m_quad = _mm_shuffle_ps( _mm_unpacklo_ps(m_quad, _mm_setzero_ps()), m_quad, _MM_SHUFFLE(3,2,1,0));
}
template <>
HK_FORCE_INLINE void hkVector4f::zeroComponent<2>()
{
	m_quad = _mm_shuffle_ps( m_quad, _mm_unpackhi_ps(m_quad, _mm_setzero_ps()), _MM_SHUFFLE(2,3,1,0));
}
template <> 
HK_FORCE_INLINE void hkVector4f::zeroComponent<3>()
{
	m_quad = _mm_castsi128_ps(_mm_srli_si128(_mm_slli_si128(_mm_castps_si128(m_quad),4),4));
}
template <int I> 
HK_FORCE_INLINE void hkVector4f::zeroComponent()
{
	HK_VECTOR4f_SUBINDEX_CHECK;
}
#endif

HK_FORCE_INLINE void hkVector4f::zeroComponent(const int i)
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

HK_FORCE_INLINE void hkVector4f::setAdd(hkVector4fParameter v0, hkVector4fParameter v1)
{
	m_quad = _mm_add_ps(v0.m_quad, v1.m_quad);
}

HK_FORCE_INLINE void hkVector4f::setSub(hkVector4fParameter v0, hkVector4fParameter v1)
{
	m_quad = _mm_sub_ps(v0.m_quad, v1.m_quad);
}

HK_FORCE_INLINE void hkVector4f::setMul(hkVector4fParameter v0, hkVector4fParameter v1)
{
	m_quad = _mm_mul_ps(v0.m_quad, v1.m_quad);
}

HK_FORCE_INLINE void hkVector4f::setMul(hkVector4fParameter v1, hkSimdFloat32Parameter r)
{
	m_quad = _mm_mul_ps( r.m_real, v1.m_quad);
}

HK_FORCE_INLINE void hkVector4f::setSubMul(hkVector4fParameter a, hkVector4fParameter b, hkSimdFloat32Parameter r)
{
	m_quad = _mm_sub_ps( a.m_quad, _mm_mul_ps( r.m_real, b.m_quad) );
}

HK_FORCE_INLINE void hkVector4f::setAddMul(hkVector4fParameter a, hkVector4fParameter b, hkSimdFloat32Parameter r)
{
	m_quad = _mm_add_ps( a.m_quad, _mm_mul_ps( r.m_real, b.m_quad) );
}

HK_FORCE_INLINE void hkVector4f::setAddMul(hkVector4fParameter a, hkVector4fParameter x, hkVector4fParameter y)
{
	m_quad = _mm_add_ps( a.m_quad, _mm_mul_ps( x.m_quad, y.m_quad) );
}

HK_FORCE_INLINE void hkVector4f::setSubMul(hkVector4fParameter a, hkVector4fParameter x, hkVector4fParameter y)
{
	m_quad = _mm_sub_ps( a.m_quad, _mm_mul_ps( x.m_quad, y.m_quad) );
}

HK_FORCE_INLINE void hkVector4f::setCross( hkVector4fParameter v0, hkVector4fParameter v1 )
{
	const hkQuadFloat32 cross0 = _mm_mul_ps(v0.m_quad, _mm_shuffle_ps(v1.m_quad, v1.m_quad, _MM_SHUFFLE(3,0,2,1)) );
	const hkQuadFloat32 cross1 = _mm_mul_ps(v1.m_quad, _mm_shuffle_ps(v0.m_quad, v0.m_quad, _MM_SHUFFLE(3,0,2,1)) );
	const hkQuadFloat32 diff   = _mm_sub_ps(cross0, cross1);

	m_quad = _mm_shuffle_ps(diff, diff, _MM_SHUFFLE(3,0,2,1));
}

HK_FORCE_INLINE const hkVector4fComparison hkVector4f::equal(hkVector4fParameter a) const
{
	return hkVector4fComparison::convert(_mm_cmpeq_ps(m_quad, a.m_quad));
}

HK_FORCE_INLINE const hkVector4fComparison hkVector4f::notEqual(hkVector4fParameter a) const
{
	return hkVector4fComparison::convert(_mm_cmpneq_ps(m_quad, a.m_quad));
}

HK_FORCE_INLINE const hkVector4fComparison hkVector4f::less(hkVector4fParameter a) const
{
	return hkVector4fComparison::convert(_mm_cmplt_ps(m_quad, a.m_quad));
}

HK_FORCE_INLINE const hkVector4fComparison hkVector4f::lessEqual(hkVector4fParameter a) const
{
	return hkVector4fComparison::convert(_mm_cmple_ps(m_quad, a.m_quad));
}

HK_FORCE_INLINE const hkVector4fComparison hkVector4f::greater(hkVector4fParameter a) const
{
	return hkVector4fComparison::convert(_mm_cmpgt_ps(m_quad, a.m_quad));
}

HK_FORCE_INLINE const hkVector4fComparison hkVector4f::greaterEqual(hkVector4fParameter a) const
{
	return hkVector4fComparison::convert(_mm_cmpge_ps(m_quad, a.m_quad));
}

HK_FORCE_INLINE const hkVector4fComparison hkVector4f::lessZero() const
{
	return hkVector4fComparison::convert(_mm_cmplt_ps(m_quad, _mm_setzero_ps()));
}

HK_FORCE_INLINE const hkVector4fComparison hkVector4f::lessEqualZero() const
{
	return hkVector4fComparison::convert(_mm_cmple_ps(m_quad, _mm_setzero_ps()));
}

HK_FORCE_INLINE const hkVector4fComparison hkVector4f::greaterZero() const
{
	return hkVector4fComparison::convert(_mm_cmpgt_ps(m_quad, _mm_setzero_ps()));
}

HK_FORCE_INLINE const hkVector4fComparison hkVector4f::greaterEqualZero() const
{
	return hkVector4fComparison::convert(_mm_cmpge_ps(m_quad, _mm_setzero_ps()));
}

HK_FORCE_INLINE const hkVector4fComparison hkVector4f::equalZero() const
{
	return hkVector4fComparison::convert(_mm_cmpeq_ps(m_quad, _mm_setzero_ps()));
}

HK_FORCE_INLINE const hkVector4fComparison hkVector4f::notEqualZero() const
{
	return hkVector4fComparison::convert(_mm_cmpneq_ps(m_quad, _mm_setzero_ps()));
}

HK_FORCE_INLINE void hkVector4f::setSelect( hkVector4fComparisonParameter comp, hkVector4fParameter trueValue, hkVector4fParameter falseValue )
{
#if HK_SSE_VERSION >= 0x41
	m_quad = _mm_blendv_ps(falseValue.m_quad, trueValue.m_quad, comp.m_mask);
#else
	m_quad = _mm_or_ps( _mm_and_ps(comp.m_mask, trueValue.m_quad), _mm_andnot_ps(comp.m_mask, falseValue.m_quad) );
#endif
}

HK_FORCE_INLINE void hkVector4f::zeroIfFalse( hkVector4fComparisonParameter comp )
{
	m_quad = _mm_and_ps(comp.m_mask, m_quad);
}

HK_FORCE_INLINE void hkVector4f::zeroIfTrue( hkVector4fComparisonParameter comp )
{
	m_quad = _mm_andnot_ps(comp.m_mask, m_quad);
}

template<> 
HK_FORCE_INLINE void hkVector4f::setSelect<hkVector4ComparisonMask::MASK_X>( hkVector4fParameter trueValue, hkVector4fParameter falseValue )
{
	m_quad = _mm_move_ss(falseValue.m_quad, trueValue.m_quad);
}

#if HK_SSE_VERSION >= 0x41
template<hkVector4fComparison::Mask M> 
HK_FORCE_INLINE void hkVector4f::setSelect( hkVector4fParameter trueValue, hkVector4fParameter falseValue )
{
	HK_VECTORfCOMPARISON_MASK_CHECK;
	m_quad = _mm_blend_ps(falseValue.m_quad, trueValue.m_quad, M);
}
#else
template<> 
HK_FORCE_INLINE void hkVector4f::setSelect<hkVector4ComparisonMask::MASK_XY>( hkVector4fParameter trueValue, hkVector4fParameter falseValue )
{
	m_quad = _mm_shuffle_ps(trueValue.m_quad, falseValue.m_quad, _MM_SHUFFLE(3,2,1,0));
}

template<> 
HK_FORCE_INLINE void hkVector4f::setSelect<hkVector4ComparisonMask::MASK_XYZ>( hkVector4fParameter trueValue, hkVector4fParameter falseValue )
{
	m_quad = HK_VECTOR4f_COMBINE_XYZ_W(trueValue.m_quad, falseValue.m_quad);
}

template<hkVector4fComparison::Mask M> 
HK_FORCE_INLINE void hkVector4f::setSelect( hkVector4fParameter trueValue, hkVector4fParameter falseValue )
{
	hkVector4fComparison comp; comp.set<M>();
	setSelect(comp, trueValue, falseValue);
}
#endif


template <>
HK_FORCE_INLINE void hkVector4f::setNeg<1>(hkVector4fParameter v)
{
	__m128i mask = _mm_insert_epi16(_mm_setzero_si128(), 0x8000, 0x1);
	m_quad = _mm_xor_ps(v.m_quad, _mm_castsi128_ps(mask));
}

template <>
HK_FORCE_INLINE void hkVector4f::setNeg<2>(hkVector4fParameter v)
{
	__m128i mask = _mm_insert_epi16(_mm_setzero_si128(), 0x8000, 0x1);
	mask = _mm_shuffle_epi32(mask, _MM_SHUFFLE(1,1,0,0));
	m_quad = _mm_xor_ps(v.m_quad, _mm_castsi128_ps(mask));
}

template <>
HK_FORCE_INLINE void hkVector4f::setNeg<3>(hkVector4fParameter v)
{
	__m128i mask = _mm_insert_epi16(_mm_setzero_si128(), 0x8000, 0x1);
	mask = _mm_shuffle_epi32(mask, _MM_SHUFFLE(1,0,0,0));
	m_quad = _mm_xor_ps(v.m_quad, _mm_castsi128_ps(mask));
}

template <>
HK_FORCE_INLINE void hkVector4f::setNeg<4>(hkVector4fParameter v)
{
	__m128i mask = _mm_insert_epi16(_mm_setzero_si128(), 0x8000, 0x1);
	mask = _mm_shuffle_epi32(mask, _MM_SHUFFLE(0,0,0,0));
	m_quad = _mm_xor_ps(v.m_quad, _mm_castsi128_ps(mask));
}

template <int N>
HK_FORCE_INLINE void hkVector4f::setNeg(hkVector4fParameter v)
{
	HK_VECTOR4f_NOT_IMPLEMENTED;
}

HK_FORCE_INLINE void hkVector4f::setAbs(hkVector4fParameter v)
{
	m_quad = hkMath::quadFabs(v.m_quad); 
}

HK_FORCE_INLINE void hkVector4f::setMin(hkVector4fParameter a, hkVector4fParameter b)
{
	m_quad = _mm_min_ps(a.m_quad, b.m_quad);
}

HK_FORCE_INLINE void hkVector4f::setMax(hkVector4fParameter a, hkVector4fParameter b)
{
	m_quad = _mm_max_ps(a.m_quad, b.m_quad);
}

/* matrix3, rotation, quaternion, transform */

HK_FORCE_INLINE void hkVector4f::_setRotatedDir(const hkMatrix3f& r, hkVector4fParameter b )
{
	const hkQuadFloat32 c0 = r.getColumn<0>().m_quad;
	const hkQuadFloat32 c1 = r.getColumn<1>().m_quad;
	const hkQuadFloat32 c2 = r.getColumn<2>().m_quad;

	const hkQuadFloat32 b0 = _mm_shuffle_ps( b.m_quad, b.m_quad, _MM_SHUFFLE(0,0,0,0));
	const hkQuadFloat32 b1 = _mm_shuffle_ps( b.m_quad, b.m_quad, _MM_SHUFFLE(1,1,1,1));
	const hkQuadFloat32 b2 = _mm_shuffle_ps( b.m_quad, b.m_quad, _MM_SHUFFLE(2,2,2,2));	

	const hkQuadFloat32 r0 = _mm_mul_ps( c0, b0 );
	const hkQuadFloat32 r1 = _mm_mul_ps( c1, b1 );
	const hkQuadFloat32 r2 = _mm_mul_ps( c2, b2 );

	m_quad = _mm_add_ps( _mm_add_ps(r0, r1), r2 );
}

HK_FORCE_INLINE void hkVector4f::_setRotatedInverseDir(const hkMatrix3f& r, hkVector4fParameter b )
{
#if HK_SSE_VERSION >= 0x41
	const hkQuadFloat32 c0 = r.getColumn<0>().m_quad;
	const hkQuadFloat32 c1 = r.getColumn<1>().m_quad;
	const hkQuadFloat32 c2 = r.getColumn<2>().m_quad;

	const hkQuadFloat32 r0 = _mm_dp_ps( c0, b.m_quad, 0x71 );
	const hkQuadFloat32 r1 = _mm_dp_ps( c1, b.m_quad, 0x72 );
	const hkQuadFloat32 r2 = _mm_dp_ps( c2, b.m_quad, 0x74 );

	m_quad = _mm_or_ps( _mm_or_ps(r0, r1), r2 );
#else
	hkVector4f c0 = r.getColumn<0>();
	hkVector4f c1 = r.getColumn<1>();
	hkVector4f c2 = r.getColumn<2>();

	HK_TRANSPOSE3f(c0,c1,c2);

	const hkQuadFloat32 b0 = _mm_shuffle_ps( b.m_quad, b.m_quad, _MM_SHUFFLE(0,0,0,0));
	const hkQuadFloat32 b1 = _mm_shuffle_ps( b.m_quad, b.m_quad, _MM_SHUFFLE(1,1,1,1));
	const hkQuadFloat32 b2 = _mm_shuffle_ps( b.m_quad, b.m_quad, _MM_SHUFFLE(2,2,2,2));	

	const hkQuadFloat32 r0 = _mm_mul_ps( c0.m_quad, b0 );
	const hkQuadFloat32 r1 = _mm_mul_ps( c1.m_quad, b1 );
	const hkQuadFloat32 r2 = _mm_mul_ps( c2.m_quad, b2 );

	m_quad = _mm_add_ps( _mm_add_ps(r0, r1), r2 );
#endif
}


template <>
HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::dot<2>(hkVector4fParameter a) const
{
#if HK_SSE_VERSION >= 0x41
	return hkSimdFloat32::convert(_mm_dp_ps(m_quad, a.m_quad, 0x3F));
#elif HK_SSE_VERSION >= 0x30
	const hkQuadFloat32 x2 = _mm_mul_ps(m_quad,a.m_quad);
	const hkQuadFloat32 hsum = _mm_hadd_ps(x2,x2); // xy zw xy zw
	return hkSimdFloat32::convert(_mm_shuffle_ps(hsum,hsum,_MM_SHUFFLE(0,0,0,0)));
#else
	const hkQuadFloat32 x2 = _mm_mul_ps(m_quad,a.m_quad);
	const hkQuadFloat32 result = _mm_add_ps( _mm_shuffle_ps(x2,x2,_MM_SHUFFLE(1,1,1,1)), _mm_shuffle_ps(x2,x2,_MM_SHUFFLE(0,0,0,0))); // xy xy xy xy
	return hkSimdFloat32::convert(result);
#endif
}

template <>
HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::dot<3>(hkVector4fParameter a) const
{
#if HK_SSE_VERSION >= 0x41
	return hkSimdFloat32::convert(_mm_dp_ps(m_quad, a.m_quad, 0x7F));
#elif HK_SSE_VERSION >= 0x30
	const hkQuadFloat32 x2 = _mm_mul_ps(m_quad,a.m_quad);
	const hkQuadFloat32 hsum = _mm_hadd_ps(x2,x2); // xy zw xy zw
	const hkQuadFloat32 z = _mm_shuffle_ps(x2,x2,_MM_SHUFFLE(2,2,2,2)); // zzzz
	const hkQuadFloat32 hsumz = _mm_add_ps(hsum, z); // xyz zzw xyz zzw
	return hkSimdFloat32::convert(_mm_shuffle_ps(hsumz,hsumz,_MM_SHUFFLE(0,0,0,0)));
#else
	const hkQuadFloat32 x2 = _mm_mul_ps(m_quad,a.m_quad);
	const hkQuadFloat32 xySum = _mm_add_ps( _mm_shuffle_ps(x2,x2,_MM_SHUFFLE(1,1,1,1)), _mm_shuffle_ps(x2,x2,_MM_SHUFFLE(0,0,0,0))); // xy xy xy xy
	const hkQuadFloat32 z = _mm_shuffle_ps(x2,x2,_MM_SHUFFLE(2,2,2,2)); // zzzz
	const hkQuadFloat32 result = _mm_add_ps( z, xySum); // xyz xyz xyz xyz
	return hkSimdFloat32::convert(result);
#endif
}

template <>
HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::dot<4>(hkVector4fParameter a) const
{
#if HK_SSE_VERSION >= 0x41
	return hkSimdFloat32::convert(_mm_dp_ps(m_quad, a.m_quad, 0xFF));
#elif HK_SSE_VERSION >= 0x30
	const hkQuadFloat32 x2 = _mm_mul_ps(m_quad,a.m_quad);
	const hkQuadFloat32 hsum = _mm_hadd_ps(x2,x2); // xy zw xy zw
	return hkSimdFloat32::convert(_mm_hadd_ps(hsum,hsum)); // xyzw all 4
#else
	const hkQuadFloat32 x2 = _mm_mul_ps(m_quad,a.m_quad);
	const hkQuadFloat32 sum0 = _mm_add_ps( _mm_shuffle_ps(x2,x2,_MM_SHUFFLE(1,0,3,2)), x2); // yxwz+xyzw = xy xy zw zw
	const hkQuadFloat32 sum1 = _mm_shuffle_ps(sum0,sum0, _MM_SHUFFLE(2,3,0,1)); // = zw zw xy xy
	const hkQuadFloat32 result = _mm_add_ps( sum0, sum1 ); // = xyzw xyzw xyzw xyzw
	return hkSimdFloat32::convert(result);
#endif
}

template <int N>
HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::dot(hkVector4fParameter a) const
{
	HK_VECTOR4f_NOT_IMPLEMENTED;
	return hkSimdFloat32::getConstant<HK_QUADREAL_0>();
}


HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::dot4xyz1(hkVector4fParameter a) const
{
#if HK_SSE_VERSION >= 0x41
	const hkQuadFloat32 xyz = _mm_dp_ps(m_quad, a.m_quad, 0x7F);
	return hkSimdFloat32::convert(_mm_add_ps(xyz, _mm_shuffle_ps(m_quad, m_quad, _MM_SHUFFLE(3,3,3,3))));
#elif HK_SSE_VERSION >= 0x30
	const hkQuadFloat32 xx2 = _mm_mul_ps(m_quad,a.m_quad);
	const hkQuadFloat32 x2 = HK_VECTOR4f_COMBINE_XYZ_W(xx2, m_quad);	// replace w by this.w
	const hkQuadFloat32 hsum = _mm_hadd_ps(x2,x2); // xy zw xy zw
	return hkSimdFloat32::convert(_mm_hadd_ps(hsum,hsum)); // xyzw all 4
#else
	const hkQuadFloat32 xx2 = _mm_mul_ps(m_quad,a.m_quad);
	const hkQuadFloat32 x2 = HK_VECTOR4f_COMBINE_XYZ_W(xx2, m_quad);	// replace w by this.w
	const hkQuadFloat32 sum0 = _mm_add_ps( _mm_shuffle_ps(x2,x2,_MM_SHUFFLE(1,0,3,2)), x2); // yxwz+xyzw = xy xy zw zw
	const hkQuadFloat32 sum1 = _mm_shuffle_ps(sum0,sum0, _MM_SHUFFLE(2,3,0,1)); // = zw zw xy xy
	const hkQuadFloat32 result = _mm_add_ps( sum0, sum1 ); // = xyzw xyzw xyzw xyzw
	return hkSimdFloat32::convert(result);
#endif
}

template <>
HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::horizontalAdd<2>() const
{
#if HK_SSE_VERSION >= 0x30
	const hkQuadFloat32 x2 = _mm_hadd_ps(m_quad, m_quad);
	return hkSimdFloat32::convert(_mm_shuffle_ps(x2,x2,_MM_SHUFFLE(0,0,0,0)));
#else
	return hkSimdFloat32::convert(_mm_add_ps( _mm_shuffle_ps(m_quad,m_quad,_MM_SHUFFLE(1,1,1,1)), _mm_shuffle_ps(m_quad,m_quad,_MM_SHUFFLE(0,0,0,0))));
#endif
}

template <>
HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::horizontalAdd<3>() const
{
#if HK_SSE_VERSION >= 0x30
	const hkQuadFloat32 x2 = _mm_hadd_ps(m_quad, m_quad);
	return hkSimdFloat32::convert(_mm_add_ps( _mm_shuffle_ps(m_quad,m_quad,_MM_SHUFFLE(2,2,2,2)), _mm_shuffle_ps(x2,x2,_MM_SHUFFLE(0,0,0,0))));
#else
	const hkQuadFloat32 xySum = _mm_add_ps( _mm_shuffle_ps(m_quad,m_quad,_MM_SHUFFLE(1,1,1,1)), _mm_shuffle_ps(m_quad,m_quad,_MM_SHUFFLE(0,0,0,0)));
	return hkSimdFloat32::convert(_mm_add_ps( _mm_shuffle_ps(m_quad,m_quad,_MM_SHUFFLE(2,2,2,2)), xySum));
#endif
}

template <>
HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::horizontalAdd<4>() const
{
#if HK_SSE_VERSION >= 0x30
	const hkQuadFloat32 x2 = _mm_hadd_ps(m_quad, m_quad);
	return hkSimdFloat32::convert(_mm_hadd_ps(x2, x2));
#else
	const hkQuadFloat32 sum0 = _mm_add_ps( _mm_shuffle_ps(m_quad,m_quad,_MM_SHUFFLE(1,0,3,2)), m_quad); // yxwz+xyzw = xy xy zw zw
	const hkQuadFloat32 sum1 = _mm_shuffle_ps(sum0,sum0, _MM_SHUFFLE(2,3,0,1)); // = zw zw xy xy
	return hkSimdFloat32::convert(_mm_add_ps( sum0, sum1 )); // xywz all 4
#endif
}

template <int N>
HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::horizontalAdd() const
{
	HK_VECTOR4f_NOT_IMPLEMENTED;
	return hkSimdFloat32::getConstant<HK_QUADREAL_0>();
}

template <>
HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::horizontalMul<2>() const
{
	return hkSimdFloat32::convert(_mm_mul_ps( _mm_shuffle_ps(m_quad,m_quad,_MM_SHUFFLE(1,1,1,1)), _mm_shuffle_ps(m_quad,m_quad,_MM_SHUFFLE(0,0,0,0))));
}

template <>
HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::horizontalMul<3>() const
{
	const hkQuadFloat32 xyProd = _mm_mul_ps( _mm_shuffle_ps(m_quad,m_quad,_MM_SHUFFLE(1,1,1,1)), _mm_shuffle_ps(m_quad,m_quad,_MM_SHUFFLE(0,0,0,0)));
	return hkSimdFloat32::convert(_mm_mul_ps( _mm_shuffle_ps(m_quad,m_quad,_MM_SHUFFLE(2,2,2,2)), xyProd));
}

template <>
HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::horizontalMul<4>() const
{
	const hkQuadFloat32 prod0 = _mm_mul_ps( _mm_shuffle_ps(m_quad,m_quad,_MM_SHUFFLE(1,0,3,2)), m_quad); // yxwz*xyzw = xy xy zw zw
	const hkQuadFloat32 prod1 = _mm_shuffle_ps(prod0,prod0, _MM_SHUFFLE(2,3,0,1)); // = zw zw xy xy
	return hkSimdFloat32::convert(_mm_mul_ps( prod0, prod1 )); // xywz all 4
}

template <int N>
HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::horizontalMul() const
{
	HK_VECTOR4f_NOT_IMPLEMENTED;
	return hkSimdFloat32::getConstant<HK_QUADREAL_0>();
}

template <>
HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::horizontalMax<1>() const
{
	return getComponent<0>();
}

template <>
HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::horizontalMax<2>() const
{
	return hkSimdFloat32::convert(_mm_max_ps( _mm_shuffle_ps(m_quad,m_quad,_MM_SHUFFLE(1,1,1,1)), _mm_shuffle_ps(m_quad,m_quad,_MM_SHUFFLE(0,0,0,0))));
}

template <>
HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::horizontalMax<3>() const
{
	const hkQuadFloat32 xy = _mm_max_ps( _mm_shuffle_ps(m_quad,m_quad,_MM_SHUFFLE(1,1,1,1)), _mm_shuffle_ps(m_quad,m_quad,_MM_SHUFFLE(0,0,0,0)));
	return hkSimdFloat32::convert(_mm_max_ps( _mm_shuffle_ps(m_quad,m_quad,_MM_SHUFFLE(2,2,2,2)), xy));
}

template <>
HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::horizontalMax<4>() const
{
	const hkQuadFloat32 sum0 = _mm_max_ps( _mm_shuffle_ps( m_quad, m_quad,_MM_SHUFFLE(1,0,3,2)), m_quad); // yxwz+xyzw = xy xy zw zw
	const hkQuadFloat32 sum1 = _mm_shuffle_ps(sum0,sum0, _MM_SHUFFLE(2,3,0,1)); // = zw zw xy xy
	return hkSimdFloat32::convert(_mm_max_ps( sum0, sum1 )); // xywz all 4
}

template <int N>
HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::horizontalMax() const
{
	HK_VECTOR4f_NOT_IMPLEMENTED;
	return hkSimdFloat32::getConstant<HK_QUADREAL_0>();
}


template <>
HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::horizontalMin<1>() const
{
	return getComponent<0>();
}

template <>
HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::horizontalMin<2>() const
{
	return hkSimdFloat32::convert(_mm_min_ps( _mm_shuffle_ps(m_quad,m_quad,_MM_SHUFFLE(1,1,1,1)), _mm_shuffle_ps(m_quad,m_quad,_MM_SHUFFLE(0,0,0,0))));
}

template <>
HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::horizontalMin<3>() const
{
	const hkQuadFloat32 xy = _mm_min_ps( _mm_shuffle_ps(m_quad,m_quad,_MM_SHUFFLE(1,1,1,1)), _mm_shuffle_ps(m_quad,m_quad,_MM_SHUFFLE(0,0,0,0)));
	return hkSimdFloat32::convert(_mm_min_ps( _mm_shuffle_ps(m_quad,m_quad,_MM_SHUFFLE(2,2,2,2)), xy));
}

template <>
HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::horizontalMin<4>() const
{
	const hkQuadFloat32 sum0 = _mm_min_ps( _mm_shuffle_ps( m_quad, m_quad,_MM_SHUFFLE(1,0,3,2)), m_quad); // yxwz+xyzw = xy xy zw zw
	const hkQuadFloat32 sum1 = _mm_shuffle_ps(sum0,sum0, _MM_SHUFFLE(2,3,0,1)); // = zw zw xy xy
	return hkSimdFloat32::convert(_mm_min_ps( sum0, sum1 )); // xywz all 4
}

template <int N>
HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::horizontalMin() const
{
	HK_VECTOR4f_NOT_IMPLEMENTED;
	return hkSimdFloat32::getConstant<HK_QUADREAL_0>();
}

/* operator () */

HK_FORCE_INLINE hkFloat32& hkVector4f::operator() (int a)
{
	HK_MATH_ASSERT(0x6d0c31d7, a>=0 && a<4, "index out of bounds for component access");
	return HK_M128(m_quad).m128_f32[a];
}

HK_FORCE_INLINE const hkFloat32& hkVector4f::operator() (int a) const
{
	HK_MATH_ASSERT(0x6d0c31d7, a>=0 && a<4, "index out of bounds for component access");
	return HK_M128(m_quad).m128_f32[a];
}

HK_FORCE_INLINE void hkVector4f::setXYZ_W(hkVector4fParameter xyz, hkVector4fParameter w)
{
	m_quad = HK_VECTOR4f_COMBINE_XYZ_W(xyz.m_quad, w.m_quad);
}

HK_FORCE_INLINE void hkVector4f::setXYZ_W(hkVector4fParameter xyz, hkSimdFloat32Parameter w)
{
	m_quad = HK_VECTOR4f_COMBINE_XYZ_W(xyz.m_quad, w.m_real);
}

HK_FORCE_INLINE void hkVector4f::setW(hkVector4fParameter w)
{
	m_quad = HK_VECTOR4f_COMBINE_XYZ_W(m_quad, w.m_quad);
}

HK_FORCE_INLINE void hkVector4f::setXYZ(hkVector4fParameter xyz)
{
	m_quad = HK_VECTOR4f_COMBINE_XYZ_W(xyz.m_quad, m_quad);
}

HK_FORCE_INLINE void hkVector4f::addXYZ(hkVector4fParameter xyz)
{
	m_quad = _mm_add_ps(m_quad, xyz.m_quad);
	HK_ON_DEBUG( HK_M128(m_quad).m128_u32[3] = 0xffffffff; )
}

HK_FORCE_INLINE void hkVector4f::subXYZ(hkVector4fParameter xyz)
{
	m_quad = _mm_sub_ps(m_quad, xyz.m_quad);
	HK_ON_DEBUG( HK_M128(m_quad).m128_u32[3] = 0xffffffff; )
}

HK_FORCE_INLINE void hkVector4f::setXYZ(hkFloat32 v)
{
	const hkQuadFloat32 q = _mm_set1_ps(v);
	m_quad = HK_VECTOR4f_COMBINE_XYZ_W( q, m_quad );
}

HK_FORCE_INLINE void hkVector4f::setXYZ(hkSimdFloat32Parameter v)
{
	m_quad = HK_VECTOR4f_COMBINE_XYZ_W( v.m_real, m_quad );
}

HK_FORCE_INLINE void hkVector4f::setXYZ_0(hkVector4fParameter xyz)
{
	m_quad = HK_VECTOR4f_COMBINE_XYZ_W( xyz.m_quad, _mm_setzero_ps() );
}

HK_FORCE_INLINE void hkVector4f::setBroadcastXYZ(const int i, hkVector4fParameter v)
{
	setBroadcast(i,v);
	HK_ON_DEBUG( HK_M128(m_quad).m128_u32[3] = 0xffffffff; )
}

HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::getComponent(const int i) const
{
	static HK_ALIGN16 (const hkUint32 indexToMask[16]) = 
	{
		0xffffffff, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0xffffffff, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0xffffffff, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0xffffffff
	};

	HK_MATH_ASSERT(0x6d0c31d7, i>=0 && i<4, "index out of bounds for component access");

	const hkQuadFloat32 mask = *(const hkQuadFloat32*)&indexToMask[ i * 4 ];
	hkQuadFloat32 selected = _mm_and_ps(mask, m_quad); 

	const hkQuadFloat32 zwxy = _mm_shuffle_ps( selected, selected, _MM_SHUFFLE(1,0,3,2));
	selected = _mm_or_ps( selected, zwxy );
	const hkQuadFloat32 yxwz = _mm_shuffle_ps( selected, selected, _MM_SHUFFLE(2,3,0,1));
	selected = _mm_or_ps( selected, yxwz );
	return hkSimdFloat32::convert(selected);
}

template <int I>
HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::getComponent() const
{
	HK_VECTOR4f_SUBINDEX_CHECK;
	return hkSimdFloat32::convert(_mm_shuffle_ps(m_quad, m_quad, _MM_SHUFFLE(I,I,I,I)));
}


HK_FORCE_INLINE void hkVector4f::setComponent(const int i, hkSimdFloat32Parameter val)
{
	static HK_ALIGN16 (const hkUint32 indexToMask[16]) = 
	{
		0xffffffff, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0xffffffff, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0xffffffff, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0xffffffff
	};

	HK_MATH_ASSERT(0x6d0c31d7, i>=0 && i<4, "index out of bounds for component access");

	const hkQuadFloat32 mask = *(const hkQuadFloat32*)&indexToMask[ i * 4 ];

#if HK_SSE_VERSION >= 0x41
	m_quad = _mm_blendv_ps(m_quad, val.m_real, mask);
#else
	m_quad = _mm_or_ps( _mm_and_ps(mask, val.m_real), _mm_andnot_ps(mask, m_quad) );
#endif
}


#if HK_SSE_VERSION >= 0x41
template <int I>
HK_FORCE_INLINE void hkVector4f::setComponent(hkSimdFloat32Parameter val)
{
	HK_VECTOR4f_SUBINDEX_CHECK;
	m_quad = _mm_blend_ps(m_quad, val.m_real, 0x1 << I);
}
#else
template <>
HK_FORCE_INLINE void hkVector4f::setComponent<0>(hkSimdFloat32Parameter val)
{
	m_quad = _mm_move_ss( m_quad, val.m_real );
}
template <>
HK_FORCE_INLINE void hkVector4f::setComponent<1>(hkSimdFloat32Parameter val)
{
	m_quad = _mm_shuffle_ps( _mm_unpacklo_ps(m_quad, val.m_real), m_quad, _MM_SHUFFLE(3,2,1,0));
}
template <>
HK_FORCE_INLINE void hkVector4f::setComponent<2>(hkSimdFloat32Parameter val)
{
	m_quad = _mm_shuffle_ps( m_quad, _mm_unpackhi_ps(m_quad, val.m_real), _MM_SHUFFLE(2,3,1,0));
}
template <>
HK_FORCE_INLINE void hkVector4f::setComponent<3>(hkSimdFloat32Parameter val)
{
	m_quad = _mm_shuffle_ps( m_quad, _mm_unpackhi_ps(m_quad, val.m_real), _MM_SHUFFLE(3,0,1,0));
}
template <int N>
HK_FORCE_INLINE void hkVector4f::setComponent(hkSimdFloat32Parameter val)
{
	HK_VECTOR4f_NOT_IMPLEMENTED;
}
#endif


HK_FORCE_INLINE void hkVector4f::reduceToHalfPrecision()
{
#if !defined(HK_HALF_IS_FLOAT)
#if HK_SSE_VERSION >= 0x41
	m_quad = _mm_castsi128_ps(_mm_blend_epi16(_mm_castps_si128(m_quad), _mm_setzero_si128(), 0x55));
#else
	__m128i precisionMask = _mm_set1_epi32(0xffff0000);
	m_quad = _mm_and_ps( m_quad, _mm_castsi128_ps(precisionMask) );
#endif
#endif
}


template <> 
HK_FORCE_INLINE hkBool32 hkVector4f::isOk<1>() const
{
	const hkQuadFloat32 nanMask = _mm_cmpord_ps(m_quad, _mm_setzero_ps());
	return (_mm_movemask_ps(nanMask) & 0x1);
}

template <> 
HK_FORCE_INLINE hkBool32 hkVector4f::isOk<2>() const
{
	const hkQuadFloat32 nanMask = _mm_cmpunord_ps(m_quad, _mm_setzero_ps());
	return !(_mm_movemask_ps(nanMask) & 0x3);
}

template <> 
HK_FORCE_INLINE hkBool32 hkVector4f::isOk<3>() const
{
	const hkQuadFloat32 nanMask = _mm_cmpunord_ps(m_quad, _mm_setzero_ps());
	return !(_mm_movemask_ps(nanMask) & 0x7);
}

template <> 
HK_FORCE_INLINE hkBool32 hkVector4f::isOk<4>() const
{
	const hkQuadFloat32 nanMask = _mm_cmpunord_ps(m_quad, _mm_setzero_ps());
	return !_mm_movemask_ps(nanMask);
}

template <int N> 
HK_FORCE_INLINE hkBool32 hkVector4f::isOk() const
{
	HK_VECTOR4f_NOT_IMPLEMENTED;
	return false;
}


template <> 
HK_FORCE_INLINE void hkVector4f::setPermutation<hkVectorPermutation::XYZW>(hkVector4fParameter v)
{
	m_quad = v.m_quad;
}

#if HK_SSE_VERSION >= 0x30
template <> 
HK_FORCE_INLINE void hkVector4f::setPermutation<hkVectorPermutation::XXZZ>(hkVector4fParameter v)
{
	m_quad = _mm_moveldup_ps(v.m_quad);
}

template <> 
HK_FORCE_INLINE void hkVector4f::setPermutation<hkVectorPermutation::YYWW>(hkVector4fParameter v)
{
	m_quad = _mm_movehdup_ps(v.m_quad);
}
#endif

template <> 
HK_FORCE_INLINE void hkVector4f::setPermutation<hkVectorPermutation::XXYY>(hkVector4fParameter v)
{
	m_quad = _mm_unpacklo_ps(v.m_quad,v.m_quad);
}

template <hkVectorPermutation::Permutation P> 
HK_FORCE_INLINE void hkVector4f::setPermutation(hkVector4fParameter v)
{
	const int shuf = ((P >> (12 - 0)) & 0x03) |
		((P >> ( 8 - 2)) & 0x0c) |
		((P >> ( 4 - 4)) & 0x30) |
		((P << ( 0 + 6)) & 0xc0);

	m_quad = _mm_shuffle_ps(v.m_quad, v.m_quad, shuf); 
}

HK_FORCE_INLINE const hkVector4fComparison hkVector4f::signBitSet() const
{
	return hkVector4fComparison::convert( _mm_castsi128_ps(_mm_srai_epi32(_mm_castps_si128(m_quad),31)) );
}

HK_FORCE_INLINE const hkVector4fComparison hkVector4f::signBitClear() const
{
	return hkVector4fComparison::convert( _mm_castsi128_ps(_mm_cmpeq_epi32(_mm_srai_epi32(_mm_castps_si128(m_quad),31),_mm_setzero_si128())) );
}

HK_FORCE_INLINE void hkVector4f::setFlipSign(hkVector4fParameter v, hkVector4fComparisonParameter mask)
{
	const __m128i maskS = _mm_slli_epi32(_mm_srli_epi32(_mm_castps_si128(mask.m_mask),31),31);
	m_quad = _mm_xor_ps(v.m_quad, _mm_castsi128_ps(maskS));
}

HK_FORCE_INLINE void hkVector4f::setFlipSign(hkVector4fParameter v, hkVector4fParameter vSign)
{
	const __m128i mask = _mm_slli_epi32(_mm_srli_epi32(_mm_castps_si128(vSign.m_quad),31),31);
	m_quad = _mm_xor_ps(v.m_quad, _mm_castsi128_ps(mask));
}

HK_FORCE_INLINE void hkVector4f::setFlipSign(hkVector4fParameter v, hkSimdFloat32Parameter sSign)
{
	const __m128i mask = _mm_slli_epi32(_mm_srli_epi32(_mm_castps_si128(sSign.m_real),31),31);
	m_quad = _mm_xor_ps(v.m_quad, _mm_castsi128_ps(mask));
}


//
// advanced interface
//

namespace hkVector4_AdvancedInterface
{

template <hkMathAccuracyMode A, hkMathDivByZeroMode D>
struct unrollf_setReciprocal { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, hkVector4fParameter a)
{
	HK_VECTOR4f_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <hkMathAccuracyMode A>
struct unrollf_setReciprocal<A, HK_DIV_IGNORE> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, hkVector4fParameter a)
{
	switch (A)
	{
		case HK_ACC_23_BIT: self = hkMath::quadReciprocal(a.m_quad); break;
		case HK_ACC_12_BIT: self = _mm_rcp_ps(a.m_quad); break;
		default:         self = _mm_div_ps(g_vectorfConstants[HK_QUADREAL_1],a.m_quad); break; // HK_ACC_FULL
	}
} };
template <hkMathAccuracyMode A>
struct unrollf_setReciprocal<A, HK_DIV_SET_ZERO> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, hkVector4fParameter a)
{
	const hkQuadFloat32 equalsZero = _mm_cmpeq_ps(a.m_quad, _mm_setzero_ps());
	hkQuadFloat32 e; unrollf_setReciprocal<A, HK_DIV_IGNORE>::apply(e, a);
	self = _mm_andnot_ps(equalsZero, e);
} };
template <hkMathAccuracyMode A>
struct unrollf_setReciprocal<A, HK_DIV_SET_HIGH> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, hkVector4fParameter a)
{
	const hkQuadFloat32 equalsZero = _mm_cmpeq_ps(a.m_quad, _mm_setzero_ps());
	hkQuadFloat32 e; unrollf_setReciprocal<A, HK_DIV_IGNORE>::apply(e, a);
	hkQuadFloat32 huge = _mm_set1_ps(HK_FLOAT_HIGH);
	const __m128i mask = _mm_slli_epi32(_mm_srli_epi32(_mm_castps_si128(a.m_quad),31),31);
	huge = _mm_xor_ps(huge, _mm_castsi128_ps(mask));
#if HK_SSE_VERSION >= 0x41
	self = _mm_blendv_ps(e, huge, equalsZero);
#else
	self = _mm_or_ps( _mm_and_ps(equalsZero, huge), _mm_andnot_ps(equalsZero, e) );
#endif
} };
template <hkMathAccuracyMode A>
struct unrollf_setReciprocal<A, HK_DIV_SET_MAX> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, hkVector4fParameter a)
{
	const hkQuadFloat32 equalsZero = _mm_cmpeq_ps(a.m_quad, _mm_setzero_ps());
	hkQuadFloat32 e; unrollf_setReciprocal<A, HK_DIV_IGNORE>::apply(e, a);
	hkQuadFloat32 huge = _mm_set1_ps(HK_FLOAT_MAX);
	const __m128i mask = _mm_slli_epi32(_mm_srli_epi32(_mm_castps_si128(a.m_quad),31),31);
	huge = _mm_xor_ps(huge, _mm_castsi128_ps(mask));
#if HK_SSE_VERSION >= 0x41
	self = _mm_blendv_ps(e, huge, equalsZero);
#else
	self = _mm_or_ps( _mm_and_ps(equalsZero, huge), _mm_andnot_ps(equalsZero, e) );
#endif
} };
template <hkMathAccuracyMode A>
struct unrollf_setReciprocal<A, HK_DIV_SET_ZERO_AND_ONE> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, hkVector4fParameter a)
{
	unrollf_setReciprocal<A, HK_DIV_SET_ZERO>::apply(self, a);
	const hkQuadFloat32 one = g_vectorfConstants[HK_QUADREAL_1];
	const hkQuadFloat32 absVal = hkMath::quadFabs(_mm_sub_ps(self, one));
	const hkQuadFloat32 lessEqualEps = _mm_cmple_ps(absVal, g_vectorfConstants[HK_QUADREAL_EPS]);
#if HK_SSE_VERSION >= 0x41
	self = _mm_blendv_ps(self, one, lessEqualEps);
#else
	self = _mm_or_ps( _mm_and_ps(lessEqualEps, one), _mm_andnot_ps(lessEqualEps, self) );
#endif
} };

} // namespace 

template <hkMathAccuracyMode A, hkMathDivByZeroMode D>
HK_FORCE_INLINE void hkVector4f::setReciprocal(hkVector4fParameter a)
{
	hkVector4_AdvancedInterface::unrollf_setReciprocal<A,D>::apply(m_quad,a);
}

HK_FORCE_INLINE void hkVector4f::setReciprocal(hkVector4fParameter a)
{
	hkVector4_AdvancedInterface::unrollf_setReciprocal<HK_ACC_23_BIT,HK_DIV_IGNORE>::apply(m_quad,a);
}



namespace hkVector4_AdvancedInterface
{

template <hkMathAccuracyMode A, hkMathDivByZeroMode D>
struct unrollf_setDiv { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, hkVector4fParameter a, hkVector4fParameter b)
{
	HK_VECTOR4f_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <hkMathAccuracyMode A>
struct unrollf_setDiv<A, HK_DIV_IGNORE> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, hkVector4fParameter a, hkVector4fParameter b)
{
	switch (A)
	{
		case HK_ACC_23_BIT: self = _mm_mul_ps(a.m_quad,hkMath::quadReciprocal(b.m_quad)); break;
		case HK_ACC_12_BIT: self = _mm_mul_ps(a.m_quad,_mm_rcp_ps(b.m_quad)); break;
		default:         self = _mm_div_ps(a.m_quad,b.m_quad); break; // HK_ACC_FULL
	}
} };
template <hkMathAccuracyMode A>
struct unrollf_setDiv<A, HK_DIV_SET_ZERO> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, hkVector4fParameter a, hkVector4fParameter b)
{
	const hkQuadFloat32 equalsZero = _mm_cmpeq_ps(b.m_quad, _mm_setzero_ps());
	hkQuadFloat32 e; unrollf_setDiv<A, HK_DIV_IGNORE>::apply(e, a, b);
	self = _mm_andnot_ps(equalsZero, e);
} };
template <hkMathAccuracyMode A>
struct unrollf_setDiv<A, HK_DIV_SET_HIGH> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, hkVector4fParameter a, hkVector4fParameter b)
{
	const hkQuadFloat32 equalsZero = _mm_cmpeq_ps(b.m_quad, _mm_setzero_ps());
	hkQuadFloat32 e; unrollf_setDiv<A, HK_DIV_IGNORE>::apply(e, a, b);
	hkQuadFloat32 huge = _mm_set1_ps(HK_FLOAT_HIGH);
	const __m128i mask = _mm_slli_epi32(_mm_srli_epi32(_mm_castps_si128(a.m_quad),31),31);
	huge = _mm_xor_ps(huge, _mm_castsi128_ps(mask));
#if HK_SSE_VERSION >= 0x41
	self = _mm_blendv_ps(e, huge, equalsZero);
#else
	self = _mm_or_ps( _mm_and_ps(equalsZero, huge), _mm_andnot_ps(equalsZero, e) );
#endif
} };
template <hkMathAccuracyMode A>
struct unrollf_setDiv<A, HK_DIV_SET_MAX> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, hkVector4fParameter a, hkVector4fParameter b)
{
	const hkQuadFloat32 equalsZero = _mm_cmpeq_ps(b.m_quad, _mm_setzero_ps());
	hkQuadFloat32 e; unrollf_setDiv<A, HK_DIV_IGNORE>::apply(e, a, b);
	hkQuadFloat32 huge = _mm_set1_ps(HK_FLOAT_MAX);
	const __m128i mask = _mm_slli_epi32(_mm_srli_epi32(_mm_castps_si128(a.m_quad),31),31);
	huge = _mm_xor_ps(huge, _mm_castsi128_ps(mask));
#if HK_SSE_VERSION >= 0x41
	self = _mm_blendv_ps(e, huge, equalsZero);
#else
	self = _mm_or_ps( _mm_and_ps(equalsZero, huge), _mm_andnot_ps(equalsZero, e) );
#endif
} };
template <hkMathAccuracyMode A>
struct unrollf_setDiv<A, HK_DIV_SET_ZERO_AND_ONE> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, hkVector4fParameter a, hkVector4fParameter b)
{
	unrollf_setDiv<A, HK_DIV_SET_ZERO>::apply(self, a, b);
	const hkQuadFloat32 one = g_vectorfConstants[HK_QUADREAL_1];
	const hkQuadFloat32 absVal = hkMath::quadFabs(_mm_sub_ps(self, one));
	const hkQuadFloat32 lessEqualEps = _mm_cmple_ps(absVal, g_vectorfConstants[HK_QUADREAL_EPS]);
#if HK_SSE_VERSION >= 0x41
	self = _mm_blendv_ps(self, one, lessEqualEps);
#else
	self = _mm_or_ps( _mm_and_ps(lessEqualEps, one), _mm_andnot_ps(lessEqualEps, self) );
#endif
} };

} // namespace 

template <hkMathAccuracyMode A, hkMathDivByZeroMode D>
HK_FORCE_INLINE void hkVector4f::setDiv(hkVector4fParameter v0, hkVector4fParameter v1)
{
	hkVector4_AdvancedInterface::unrollf_setDiv<A,D>::apply(m_quad,v0,v1);
}

HK_FORCE_INLINE void hkVector4f::setDiv(hkVector4fParameter v0, hkVector4fParameter v1)
{
	hkVector4_AdvancedInterface::unrollf_setDiv<HK_ACC_23_BIT,HK_DIV_IGNORE>::apply(m_quad,v0,v1);
}

template <hkMathAccuracyMode A, hkMathDivByZeroMode D>
HK_FORCE_INLINE void hkVector4f::div(hkVector4fParameter a)
{
	setDiv<A,D>( *this, a );
}

HK_FORCE_INLINE void hkVector4f::div(hkVector4fParameter a)
{
	setDiv( *this, a );
}



namespace hkVector4_AdvancedInterface
{

template <hkMathAccuracyMode A, hkMathNegSqrtMode S>
struct unrollf_setSqrt { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, hkVector4fParameter a)
{
	HK_VECTOR4f_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <hkMathAccuracyMode A>
struct unrollf_setSqrt<A, HK_SQRT_IGNORE> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, hkVector4fParameter a)
{
	switch (A)
	{
		case HK_ACC_23_BIT: self = _mm_mul_ps(a.m_quad,hkMath::quadReciprocalSquareRoot(a.m_quad)); break;
		case HK_ACC_12_BIT: self = _mm_mul_ps(a.m_quad,_mm_rsqrt_ps(a.m_quad)); break;
		default:         self = _mm_sqrt_ps(a.m_quad); break; // HK_ACC_FULL
	}
} };
template <hkMathAccuracyMode A>
struct unrollf_setSqrt<A, HK_SQRT_SET_ZERO> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, hkVector4fParameter a)
{
	const hkQuadFloat32 equalsZero = _mm_cmple_ps(a.m_quad, _mm_setzero_ps());
	hkQuadFloat32 e; unrollf_setSqrt<A, HK_SQRT_IGNORE>::apply(e,a);
	self = _mm_andnot_ps(equalsZero, e);
} };

} // namespace 

template <hkMathAccuracyMode A, hkMathNegSqrtMode S>
HK_FORCE_INLINE void hkVector4f::setSqrt(hkVector4fParameter a)
{
	hkVector4_AdvancedInterface::unrollf_setSqrt<A,S>::apply(m_quad, a);
}

HK_FORCE_INLINE void hkVector4f::setSqrt(hkVector4fParameter a)
{
	hkVector4_AdvancedInterface::unrollf_setSqrt<HK_ACC_23_BIT,HK_SQRT_SET_ZERO>::apply(m_quad, a);
}



namespace hkVector4_AdvancedInterface
{

template <hkMathAccuracyMode A, hkMathNegSqrtMode S>
struct unrollf_setSqrtInverse { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, hkVector4fParameter a)
{
	HK_VECTOR4f_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <hkMathAccuracyMode A>
struct unrollf_setSqrtInverse<A, HK_SQRT_IGNORE> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, hkVector4fParameter a)
{
	switch (A)
	{
		case HK_ACC_23_BIT: self = hkMath::quadReciprocalSquareRoot(a.m_quad); break;
		case HK_ACC_12_BIT: self = _mm_rsqrt_ps(a.m_quad); break;
		default:			self = _mm_div_ps(g_vectorfConstants[HK_QUADREAL_1], _mm_sqrt_ps(a.m_quad)); break; // HK_ACC_FULL
	}
} };
template <hkMathAccuracyMode A>
struct unrollf_setSqrtInverse<A, HK_SQRT_SET_ZERO> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, hkVector4fParameter a)
{
	const hkQuadFloat32 equalsZero = _mm_cmple_ps(a.m_quad, _mm_setzero_ps());
	hkQuadFloat32 e; unrollf_setSqrtInverse<A, HK_SQRT_IGNORE>::apply(e,a);
	self = _mm_andnot_ps(equalsZero, e);
} };
} // namespace 

template <hkMathAccuracyMode A, hkMathNegSqrtMode S>
HK_FORCE_INLINE void hkVector4f::setSqrtInverse(hkVector4fParameter a)
{
	hkVector4_AdvancedInterface::unrollf_setSqrtInverse<A,S>::apply(m_quad,a);
}

HK_FORCE_INLINE void hkVector4f::setSqrtInverse(hkVector4fParameter a)
{
	hkVector4_AdvancedInterface::unrollf_setSqrtInverse<HK_ACC_23_BIT,HK_SQRT_SET_ZERO>::apply(m_quad,a);
}


namespace hkVector4_AdvancedInterface
{
template <int N, hkMathIoMode A>
struct unrollf_load { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, const hkFloat32* HK_RESTRICT p)
{
	HK_VECTOR4f_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <int N, hkMathIoMode A>
struct unrollf_load_D { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, const hkDouble64* HK_RESTRICT p)
{
	HK_VECTOR4f_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <int N>
struct unrollf_load<N, HK_IO_BYTE_ALIGNED> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, const hkFloat32* HK_RESTRICT p)
{
	switch (N)
	{
		case 1:
			{
				self = _mm_load_ss(p);
				HK_ON_DEBUG(HK_M128(self).m128_u32[1] = 0xffffffff; HK_M128(self).m128_u32[2] = 0xffffffff; HK_M128(self).m128_u32[3] = 0xffffffff;)
			}
			break;
		case 2:
			{
				self = _mm_castpd_ps(_mm_load_sd((const double*)p));
				HK_ON_DEBUG(HK_M128(self).m128_u32[2] = 0xffffffff; HK_M128(self).m128_u32[3] = 0xffffffff;)
			}
			break;
		case 3:
			{
				__m128 xy = _mm_castpd_ps(_mm_load_sd((const double*)p));
				__m128 z = _mm_load_ss(p+2);
				self = _mm_movelh_ps(xy,z);
				HK_ON_DEBUG(HK_M128(self).m128_u32[3] = 0xffffffff;)
			}
			break;
		default:
			{
#if HK_SSE_VERSION >= 0x30
				self = _mm_castsi128_ps(_mm_lddqu_si128((const __m128i*)p));
#else
				self = _mm_loadu_ps(p);
#endif
			}
			break;
	}
} };
template <int N>
struct unrollf_load_D<N, HK_IO_BYTE_ALIGNED> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, const hkDouble64* HK_RESTRICT p)
{
	switch (N)
	{
	case 1:
		{
			__m128d a = _mm_load_sd(p);
			self = _mm_cvtpd_ps(a);
			HK_ON_DEBUG(HK_M128(self).m128_u32[1] = 0xffffffff; HK_M128(self).m128_u32[2] = 0xffffffff; HK_M128(self).m128_u32[3] = 0xffffffff;)
		}
		break;
	case 2:
		{
#if HK_SSE_VERSION >= 0x30
			__m128d a = _mm_castsi128_pd(_mm_lddqu_si128((const __m128i*)p));
#else
			__m128d a = _mm_loadu_pd(p);
#endif
			self = _mm_cvtpd_ps(a);
			HK_ON_DEBUG(HK_M128(self).m128_u32[2] = 0xffffffff; HK_M128(self).m128_u32[3] = 0xffffffff;)
		}
		break;
	case 3:
		{
#if HK_SSE_VERSION >= 0x30
			__m128d a = _mm_castsi128_pd(_mm_lddqu_si128((const __m128i*)p));
#else
			__m128d a = _mm_loadu_pd(p);
#endif
			__m128d b = _mm_load_sd(p+2);

			__m128 xy = _mm_cvtpd_ps(a);
			__m128 z = _mm_cvtpd_ps(b);
			self = _mm_movelh_ps(xy,z);
			HK_ON_DEBUG(HK_M128(self).m128_u32[3] = 0xffffffff;)
		}
		break;
	default:
		{
#if HK_SSE_VERSION >= 0x30
			__m128d a = _mm_castsi128_pd(_mm_lddqu_si128((const __m128i*)p));
			__m128d b = _mm_castsi128_pd(_mm_lddqu_si128((const __m128i*)(p+2)));
#else
			__m128d a = _mm_loadu_pd(p);
			__m128d b = _mm_loadu_pd(p+2);
#endif

			__m128 xy = _mm_cvtpd_ps(a);
			__m128 zw = _mm_cvtpd_ps(b);
			self = _mm_movelh_ps(xy,zw);
		}
		break;
	}
} };
template <int N>
struct unrollf_load<N, HK_IO_NATIVE_ALIGNED> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, const hkFloat32* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & (sizeof(hkFloat32)-1) ) == 0, "pointer must be aligned to native size of hkFloat32.");
	unrollf_load<N, HK_IO_BYTE_ALIGNED>::apply(self,p);
} };
template <int N>
struct unrollf_load_D<N, HK_IO_NATIVE_ALIGNED> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, const hkDouble64* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & (sizeof(hkDouble64)-1) ) == 0, "pointer must be aligned to native size of hkDouble64.");
	unrollf_load_D<N, HK_IO_BYTE_ALIGNED>::apply(self,p);
} };
template <int N>
struct unrollf_load<N, HK_IO_SIMD_ALIGNED> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, const hkFloat32* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & ((sizeof(hkFloat32)*(N!=3?N:4) )-1) ) == 0, "pointer must be aligned for SIMD.");
	if (N==4)
	{
		self = _mm_load_ps(p);
	}
	else
	{
		unrollf_load<N, HK_IO_NATIVE_ALIGNED>::apply(self,p);
	}
} };
template <int N>
struct unrollf_load_D<N, HK_IO_SIMD_ALIGNED> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, const hkDouble64* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & ((sizeof(hkDouble64)*(N!=3?N:4) )-1) ) == 0, "pointer must be aligned for SIMD.");
	switch (N)
	{
	case 4:
		{
			__m128d a = _mm_load_pd(p);
			__m128d b = _mm_load_pd(p+2);
			__m128 xy = _mm_cvtpd_ps(a);
			__m128 zw = _mm_cvtpd_ps(b);
			self = _mm_movelh_ps(xy,zw);
		}
		break;
	case 3:
		{
			__m128d a = _mm_load_pd(p);
			__m128d b = _mm_load_sd(p+2);
			__m128 xy = _mm_cvtpd_ps(a);
			__m128 z = _mm_cvtpd_ps(b);
			self = _mm_movelh_ps(xy,z);
			HK_ON_DEBUG(HK_M128(self).m128_u32[3] = 0xffffffff;)
		}
		break;
	case 2:
		{
			__m128d a = _mm_load_pd(p);
			self = _mm_cvtpd_ps(a);
			HK_ON_DEBUG(HK_M128(self).m128_u32[2] = 0xffffffff; HK_M128(self).m128_u32[3] = 0xffffffff;)
		}
		break;
	default:
		{
			unrollf_load_D<N, HK_IO_NATIVE_ALIGNED>::apply(self,p);
		}
		break;
	}
} };
template <int N>
struct unrollf_load<N, HK_IO_NOT_CACHED> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, const hkFloat32* HK_RESTRICT p)
{
#if HK_SSE_VERSION >= 0x41
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & ((sizeof(hkFloat32)*(N!=3?N:4) )-1) ) == 0, "pointer must be aligned for SIMD.");
	if (N==4)
	{
		self = _mm_castsi128_ps(_mm_stream_load_si128((__m128i*) p));
	}
	else
	{
		unrollf_load<N, HK_IO_SIMD_ALIGNED>::apply(self,p);
	}
#else
	unrollf_load<N, HK_IO_SIMD_ALIGNED>::apply(self,p);
#endif
} };
template <int N>
struct unrollf_load_D<N, HK_IO_NOT_CACHED> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, const hkDouble64* HK_RESTRICT p)
{
#if HK_SSE_VERSION >= 0x41
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & ((sizeof(hkDouble64)*(N!=3?N:4) )-1) ) == 0, "pointer must be aligned for SIMD.");
	switch (N)
	{
	case 4:
		{
			__m128d a = _mm_castsi128_pd(_mm_stream_load_si128((__m128i*) p));
			__m128d b = _mm_castsi128_pd(_mm_stream_load_si128((__m128i*) (p+2)));
			__m128 xy = _mm_cvtpd_ps(a);
			__m128 zw = _mm_cvtpd_ps(b);
			self = _mm_movelh_ps(xy,zw);
		}
		break;
	case 3:
		{
			__m128d a = _mm_castsi128_pd(_mm_stream_load_si128((__m128i*) p));
			__m128d b = _mm_load_sd(p+2);
			__m128 xy = _mm_cvtpd_ps(a);
			__m128 z = _mm_cvtpd_ps(b);
			self = _mm_movelh_ps(xy,z);
			HK_ON_DEBUG(HK_M128(self).m128_u32[3] = 0xffffffff;)
		}
		break;
	case 2:
		{
			__m128d a = _mm_castsi128_pd(_mm_stream_load_si128((__m128i*) p));
			self = _mm_cvtpd_ps(a);
			HK_ON_DEBUG(HK_M128(self).m128_u32[2] = 0xffffffff; HK_M128(self).m128_u32[3] = 0xffffffff;)
		}
		break;
	default:
		{
			unrollf_load_D<N, HK_IO_SIMD_ALIGNED>::apply(self,p);
		}
		break;
	}
#else
	unrollf_load_D<N, HK_IO_SIMD_ALIGNED>::apply(self,p);
#endif
} };
} // namespace 

template <int N, hkMathIoMode A>
HK_FORCE_INLINE void hkVector4f::load(const hkFloat32* p)
{
	HK_VECTOR4f_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrollf_load<N,A>::apply(m_quad, p);
}

template <int N, hkMathIoMode A>
HK_FORCE_INLINE void hkVector4f::load(const hkDouble64* p)
{
	HK_VECTOR4f_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrollf_load_D<N,A>::apply(m_quad, p);
}

template <int N>
HK_FORCE_INLINE void hkVector4f::load(const hkFloat32* p)
{
	HK_VECTOR4f_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrollf_load<N,HK_IO_SIMD_ALIGNED>::apply(m_quad, p);
}

template <int N>
HK_FORCE_INLINE void hkVector4f::load(const hkDouble64* p)
{
	HK_VECTOR4f_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrollf_load_D<N,HK_IO_SIMD_ALIGNED>::apply(m_quad, p);
}




namespace hkVector4_AdvancedInterface
{
template <int N, hkMathIoMode A>
struct unrollf_loadH { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, const hkHalf* HK_RESTRICT p)
{
	HK_VECTOR4f_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <int N>
struct unrollf_loadH<N, HK_IO_BYTE_ALIGNED> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, const hkHalf* HK_RESTRICT p)
{
#if defined(HK_HALF_IS_FLOAT)
	// hkFloat32 is also float in this file
	const hkFloat32* HK_RESTRICT p_r = (const hkFloat32* HK_RESTRICT)p;
	unrollf_load<N,HK_IO_BYTE_ALIGNED>::apply(self, p_r);
#else
	switch (N)
	{
	case 1:
		{
			float x; p[0].store(&x);
			self = _mm_set_ss(x);
			HK_ON_DEBUG(HK_M128(self).m128_u32[1] = 0xffffffff; HK_M128(self).m128_u32[2] = 0xffffffff; HK_M128(self).m128_u32[3] = 0xffffffff;)
		}
		break;
	case 2:
		{
			__m128i twohalfs = _mm_castps_si128( _mm_load_ss((const float*)p) );
			self = _mm_castsi128_ps( _mm_unpacklo_epi16(_mm_setzero_si128(), twohalfs) );
			HK_ON_DEBUG(HK_M128(self).m128_u32[2] = 0xffffffff; HK_M128(self).m128_u32[3] = 0xffffffff;)
		}
		break;
	case 3:
		{
			__m128i h = _mm_castps_si128( _mm_load_ss((const float*)p) );
			__m128 twohalfs = _mm_castsi128_ps( _mm_unpacklo_epi16(_mm_setzero_si128(), h) );
			float x; p[2].store(&x);
			__m128 val = _mm_load1_ps(&x);
			self = _mm_movelh_ps(twohalfs,val);
			HK_ON_DEBUG(HK_M128(self).m128_u32[3] = 0xffffffff;)
		}
		break;
	default:
		{
			__m128i fourhalfs = _mm_castpd_si128(_mm_load_sd((const double*)p));
			self = _mm_castsi128_ps( _mm_unpacklo_epi16(_mm_setzero_si128(), fourhalfs) );
		}
		break;
	}
#endif
} };
template <int N>
struct unrollf_loadH<N, HK_IO_NATIVE_ALIGNED> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, const hkHalf* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & (sizeof(hkHalf)-1) ) == 0, "pointer must be aligned to native size of hkHalf.");
	unrollf_loadH<N, HK_IO_BYTE_ALIGNED>::apply(self,p);
} };
template <int N>
struct unrollf_loadH<N, HK_IO_SIMD_ALIGNED> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, const hkHalf* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & ((sizeof(hkHalf)*(N!=3?N:4) )-1) ) == 0, "pointer must be aligned for SIMD.");
#if defined(HK_HALF_IS_FLOAT)
	// hkFloat32 is also float in this file
	const hkFloat32* HK_RESTRICT p_r = (const hkFloat32* HK_RESTRICT)p;
	unrollf_load<N,HK_IO_SIMD_ALIGNED>::apply(self, p_r);
#else
	unrollf_loadH<N, HK_IO_NATIVE_ALIGNED>::apply(self,p);
#endif
} };
template <int N>
struct unrollf_loadH<N, HK_IO_NOT_CACHED> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, const hkHalf* HK_RESTRICT p)
{
#if defined(HK_HALF_IS_FLOAT)
	// hkFloat32 is also float in this file
	const hkFloat32* HK_RESTRICT p_r = (const hkFloat32* HK_RESTRICT)p;
	unrollf_load<N,HK_IO_NOT_CACHED>::apply(self, p_r);
#else
	unrollf_loadH<N, HK_IO_SIMD_ALIGNED>::apply(self,p);
#endif
} };
} // namespace 

template <int N, hkMathIoMode A>
HK_FORCE_INLINE void hkVector4f::load(const hkHalf* p)
{
	HK_VECTOR4f_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrollf_loadH<N,A>::apply(m_quad, p);
}

template <int N>
HK_FORCE_INLINE void hkVector4f::load(const hkHalf* p)
{
	HK_VECTOR4f_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrollf_loadH<N,HK_IO_SIMD_ALIGNED>::apply(m_quad, p);
}



namespace hkVector4_AdvancedInterface
{
template <int N, hkMathIoMode A>
struct unrollf_loadF16 { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, const hkFloat16* HK_RESTRICT p)
{
	HK_VECTOR4f_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <int N>
struct unrollf_loadF16<N, HK_IO_BYTE_ALIGNED> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, const hkFloat16* HK_RESTRICT p)
{
	static HK_ALIGN16(const unsigned int half_sign[4])		  = {0x00008000, 0x00008000, 0x00008000, 0x00008000};
	static HK_ALIGN16(const unsigned int half_exponent[4])	  = {0x00007C00, 0x00007C00, 0x00007C00, 0x00007C00};
	static HK_ALIGN16(const unsigned int half_mantissa[4])	  = {0x000003FF, 0x000003FF, 0x000003FF, 0x000003FF};
	static HK_ALIGN16(const unsigned int half_bias_offset[4]) = {0x0001C000, 0x0001C000, 0x0001C000, 0x0001C000};

	__m128i r;
	switch (N)
	{
	case 1:
		{
			hkFloat16 tmp[2];
			tmp[0] = p[0];
			tmp[1].setZero();
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
			hkFloat16 tmp[4];
			tmp[0] = p[0];
			tmp[1] = p[1];
			tmp[2] = p[2];
			tmp[3].setZero();
			r = _mm_castpd_si128(_mm_load_sd((const double*)tmp));
		}
		break;
	default:
		{
			r = _mm_castpd_si128(_mm_load_sd((const double*)p));
		}
		break;
	}

	__m128i unpacked = _mm_unpacklo_epi16(r, _mm_setzero_si128());

	__m128i sign = _mm_and_si128(unpacked, *(__m128i*)half_sign);
	__m128i exponent = _mm_and_si128(unpacked, *(__m128i*)half_exponent);
	__m128i exp_zero = _mm_cmpeq_epi32(exponent, _mm_setzero_si128());
	__m128i mantissa = _mm_and_si128(unpacked, *(__m128i*)half_mantissa);
	__m128i exp_offset = _mm_andnot_si128(exp_zero, _mm_add_epi32(exponent, *(__m128i*)half_bias_offset));

	__m128i sign_shift = _mm_slli_epi32(sign, 16);
	__m128i exp_mantissa = _mm_slli_epi32(_mm_or_si128(exp_offset,mantissa), 13);

	self = _mm_castsi128_ps(_mm_or_si128(sign_shift, exp_mantissa));

#if defined(HK_DEBUG)
	for(int i=N; i<4; ++i) HK_M128(self).m128_u32[i] = 0xffffffff;
#endif
} };
template <int N>
struct unrollf_loadF16<N, HK_IO_NATIVE_ALIGNED> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, const hkFloat16* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & (sizeof(hkFloat16)-1) ) == 0, "pointer must be aligned to native size of hkFloat16.");
	unrollf_loadF16<N, HK_IO_BYTE_ALIGNED>::apply(self,p);
} };
template <int N>
struct unrollf_loadF16<N, HK_IO_SIMD_ALIGNED> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, const hkFloat16* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & ((sizeof(hkFloat16)*(N!=3?N:4) )-1) ) == 0, "pointer must be aligned for SIMD.");
	unrollf_loadF16<N, HK_IO_NATIVE_ALIGNED>::apply(self,p);
} };
template <int N>
struct unrollf_loadF16<N, HK_IO_NOT_CACHED> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, const hkFloat16* HK_RESTRICT p)
{
	unrollf_loadF16<N, HK_IO_SIMD_ALIGNED>::apply(self,p);
} };
} // namespace 

template <int N, hkMathIoMode A>
HK_FORCE_INLINE void hkVector4f::load(const hkFloat16* p)
{
	HK_VECTOR4f_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrollf_loadF16<N,A>::apply(m_quad, p);
}

template <int N>
HK_FORCE_INLINE void hkVector4f::load(const hkFloat16* p)
{
	HK_VECTOR4f_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrollf_loadF16<N,HK_IO_SIMD_ALIGNED>::apply(m_quad, p);
}



namespace hkVector4_AdvancedInterface
{
template <int N, hkMathIoMode A>
struct unrollf_store { HK_FORCE_INLINE static void apply(const hkQuadFloat32& self, hkFloat32* HK_RESTRICT p)
{
	HK_VECTOR4f_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <int N, hkMathIoMode A>
struct unrollf_store_D { HK_FORCE_INLINE static void apply(const hkQuadFloat32& self, hkDouble64* HK_RESTRICT p)
{
	HK_VECTOR4f_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <int N>
struct unrollf_store<N, HK_IO_BYTE_ALIGNED> { HK_FORCE_INLINE static void apply(const hkQuadFloat32& self, hkFloat32* HK_RESTRICT p)
{
	switch (N)
	{
	case 1:
		{
			_mm_store_ss(p, self);
		}
		break;
	case 2:
		{
			_mm_store_sd((double*) p, _mm_castps_pd(self));
		}
		break;
	case 3:
		{
			_mm_store_sd((double*) p, _mm_castps_pd(self));
			_mm_store_ss(p+2, _mm_movehl_ps(self,self));
		}
		break;
	default:
		{
			_mm_storeu_ps(p, self);
		}
		break;
	}
} };
template <int N>
struct unrollf_store_D<N, HK_IO_BYTE_ALIGNED> { HK_FORCE_INLINE static void apply(const hkQuadFloat32& self, hkDouble64* HK_RESTRICT p)
{
	switch (N)
	{
	case 1:
		{
			__m128d a = _mm_cvtps_pd(self);
			_mm_store_sd(p, a);
		}
		break;
	case 2:
		{
			__m128d a = _mm_cvtps_pd(self);
			_mm_storeu_pd(p, a);
		}
		break;
	case 3:
		{
			__m128d a = _mm_cvtps_pd(self);
			__m128d b = _mm_cvtps_pd(_mm_movehl_ps(self,self));
			_mm_storeu_pd(p, a);
			_mm_store_sd(p+2, b);
		}
		break;
	default:
		{
			__m128d a = _mm_cvtps_pd(self);
			__m128d b = _mm_cvtps_pd(_mm_movehl_ps(self,self));
			_mm_storeu_pd(p, a);
			_mm_storeu_pd(p+2, b);
		}
		break;
	}
} };
template <int N>
struct unrollf_store<N, HK_IO_NATIVE_ALIGNED> { HK_FORCE_INLINE static void apply(const hkQuadFloat32& self, hkFloat32* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & (sizeof(hkFloat32)-1) ) == 0, "pointer must be aligned to native size of hkFloat32.");
	unrollf_store<N, HK_IO_BYTE_ALIGNED>::apply(self,p);
} };
template <int N>
struct unrollf_store_D<N, HK_IO_NATIVE_ALIGNED> { HK_FORCE_INLINE static void apply(const hkQuadFloat32& self, hkDouble64* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & (sizeof(hkDouble64)-1) ) == 0, "pointer must be aligned to native size of hkDouble64.");
	unrollf_store_D<N, HK_IO_BYTE_ALIGNED>::apply(self,p);
} };
template <int N>
struct unrollf_store<N, HK_IO_SIMD_ALIGNED> { HK_FORCE_INLINE static void apply(const hkQuadFloat32& self, hkFloat32* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & ((sizeof(hkFloat32)*(N!=3?N:4) )-1) ) == 0, "pointer must be aligned for SIMD.");
	if (N==4)
	{
		_mm_store_ps(p, self);
	}
	else
	{
		unrollf_store<N, HK_IO_NATIVE_ALIGNED>::apply(self,p);
	}
} };
template <int N>
struct unrollf_store_D<N, HK_IO_SIMD_ALIGNED> { HK_FORCE_INLINE static void apply(const hkQuadFloat32& self, hkDouble64* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & ((sizeof(hkDouble64)*(N!=3?N:4) )-1) ) == 0, "pointer must be aligned for SIMD.");
	switch (N)
	{
	case 2:
		{
			__m128d a = _mm_cvtps_pd(self);
			_mm_store_pd(p, a);
		}
		break;
	case 3:
		{
			__m128d a = _mm_cvtps_pd(self);
			__m128d b = _mm_cvtps_pd(_mm_movehl_ps(self,self));
			_mm_store_pd(p, a);
			_mm_store_sd(p+2, b);
		}
		break;
	case 4:
		{
			__m128d a = _mm_cvtps_pd(self);
			__m128d b = _mm_cvtps_pd(_mm_movehl_ps(self,self));
			_mm_store_pd(p, a);
			_mm_store_pd(p+2, b);
		}
		break;
	default:
		{
			unrollf_store_D<N, HK_IO_NATIVE_ALIGNED>::apply(self,p);
		}
		break;
	}
} };
template <int N>
struct unrollf_store<N, HK_IO_NOT_CACHED> { HK_FORCE_INLINE static void apply(const hkQuadFloat32& self, hkFloat32* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & ((sizeof(hkFloat32)*(N!=3?N:4) )-1) ) == 0, "pointer must be aligned for SIMD.");
	if (N==4)
	{
		_mm_stream_ps(p, self);
	}
	else
	{
		unrollf_store<N, HK_IO_SIMD_ALIGNED>::apply(self,p);
	}
} };
template <int N>
struct unrollf_store_D<N, HK_IO_NOT_CACHED> { HK_FORCE_INLINE static void apply(const hkQuadFloat32& self, hkDouble64* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & ((sizeof(hkDouble64)*(N!=3?N:4) )-1) ) == 0, "pointer must be aligned for SIMD.");
	switch (N)
	{
	case 2:
		{
			__m128d a = _mm_cvtps_pd(self);
			_mm_stream_pd(p, a);
		}
		break;
	case 3:
		{
			__m128d a = _mm_cvtps_pd(self);
			__m128d b = _mm_cvtps_pd(_mm_movehl_ps(self,self));
			_mm_stream_pd(p, a);
			_mm_store_sd(p+2, b);
		}
		break;
	case 4:
		{
			__m128d a = _mm_cvtps_pd(self);
			__m128d b = _mm_cvtps_pd(_mm_movehl_ps(self,self));
			_mm_stream_pd(p, a);
			_mm_stream_pd(p+2, b);
		}
		break;
	default:
		{
			unrollf_store_D<N, HK_IO_SIMD_ALIGNED>::apply(self,p);
		}
		break;
	}
} };
} // namespace 

template <int N, hkMathIoMode A, hkMathRoundingMode R> 
HK_FORCE_INLINE void hkVector4f::store(hkFloat32* p) const
{
	HK_VECTOR4f_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrollf_store<N,A>::apply(m_quad, p);
}

template <int N, hkMathIoMode A, hkMathRoundingMode R> 
HK_FORCE_INLINE void hkVector4f::store(hkDouble64* p) const
{
	HK_VECTOR4f_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrollf_store_D<N,A>::apply(m_quad, p);
}

template <int N, hkMathIoMode A> 
HK_FORCE_INLINE void hkVector4f::store(hkFloat32* p) const
{
	HK_VECTOR4f_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrollf_store<N,A>::apply(m_quad, p);
}

template <int N, hkMathIoMode A> 
HK_FORCE_INLINE void hkVector4f::store(hkDouble64* p) const
{
	HK_VECTOR4f_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrollf_store_D<N,A>::apply(m_quad, p);
}

template <int N> 
HK_FORCE_INLINE void hkVector4f::store(hkFloat32* p) const
{
	HK_VECTOR4f_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrollf_store<N,HK_IO_SIMD_ALIGNED>::apply(m_quad, p);
}

template <int N> 
HK_FORCE_INLINE void hkVector4f::store(hkDouble64* p) const
{
	HK_VECTOR4f_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrollf_store_D<N,HK_IO_SIMD_ALIGNED>::apply(m_quad, p);
}


namespace hkVector4_AdvancedInterface
{
template <int N, hkMathIoMode A, hkMathRoundingMode R>
struct unrollf_storeH { HK_FORCE_INLINE static void apply(const hkQuadFloat32& self, hkHalf* HK_RESTRICT p)
{
	HK_VECTOR4f_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <int N, hkMathRoundingMode R>
struct unrollf_storeH<N, HK_IO_BYTE_ALIGNED, R> { HK_FORCE_INLINE static void apply(const hkQuadFloat32& self, hkHalf* HK_RESTRICT p)
{
#if defined(HK_HALF_IS_FLOAT)
	// hkFloat32 is also float in this file
	hkFloat32* HK_RESTRICT p_r = (hkFloat32* HK_RESTRICT)p;
	unrollf_store<N,HK_IO_BYTE_ALIGNED>::apply(self, p_r);
#else
	__m128  vs0;
	if (R == HK_ROUND_NEAREST)
		vs0 = _mm_mul_ps( self, g_vectorfConstants[HK_QUADREAL_PACK_HALF] );
	else
		vs0 = self;
	__m128i tmp0 = _mm_srai_epi32( _mm_castps_si128(vs0), 16 );
	__m128i tmp1 = _mm_packs_epi32(tmp0, tmp0);

	switch (N)
	{
	case 1:
		{
			float ftmp1; _mm_store_ss(&ftmp1, _mm_castsi128_ps(tmp1));
			const hkHalf* HK_RESTRICT htmp1 = (const hkHalf* HK_RESTRICT)&ftmp1;
			p[0] = htmp1[0];
		}
		break;
	case 2:
		{
			_mm_store_ss((float*)p, _mm_castsi128_ps(tmp1));
		}
		break;
	case 3:
		{
			double dtmp1; _mm_store_sd(&dtmp1, _mm_castsi128_pd(tmp1));
			const hkHalf* HK_RESTRICT htmp1 = (const hkHalf* HK_RESTRICT)&dtmp1;
			p[0] = htmp1[0];
			p[1] = htmp1[1];
			p[2] = htmp1[2];
		}
		break;
	default:
		{
			_mm_store_sd((double*) p, _mm_castsi128_pd(tmp1));
		}
		break;
	}
#endif
} };
template <int N, hkMathRoundingMode R>
struct unrollf_storeH<N, HK_IO_NATIVE_ALIGNED, R> { HK_FORCE_INLINE static void apply(const hkQuadFloat32& self, hkHalf* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & (sizeof(hkHalf)-1) ) == 0, "pointer must be aligned to native size of hkHalf.");
	unrollf_storeH<N, HK_IO_BYTE_ALIGNED, R>::apply(self,p);
} };
template <int N, hkMathRoundingMode R>
struct unrollf_storeH<N, HK_IO_SIMD_ALIGNED, R> { HK_FORCE_INLINE static void apply(const hkQuadFloat32& self, hkHalf* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & ((sizeof(hkHalf)*(N!=3?N:4) )-1) ) == 0, "pointer must be aligned for SIMD.");
#if defined(HK_HALF_IS_FLOAT)
	// hkFloat32 is also float in this file
	hkFloat32* HK_RESTRICT p_r = (hkFloat32* HK_RESTRICT)p;
	unrollf_store<N,HK_IO_SIMD_ALIGNED>::apply(self, p_r);
#else
	unrollf_storeH<N, HK_IO_NATIVE_ALIGNED, R>::apply(self,p);
#endif
} };
template <int N, hkMathRoundingMode R>
struct unrollf_storeH<N, HK_IO_NOT_CACHED, R> { HK_FORCE_INLINE static void apply(const hkQuadFloat32& self, hkHalf* HK_RESTRICT p)
{
#if defined(HK_HALF_IS_FLOAT)
	// hkFloat32 is also float in this file
	hkFloat32* HK_RESTRICT p_r = (hkFloat32* HK_RESTRICT)p;
	unrollf_store<N,HK_IO_NOT_CACHED>::apply(self, p_r);
#else
	unrollf_storeH<N, HK_IO_SIMD_ALIGNED, R>::apply(self,p);
#endif
} };
} // namespace 

template <int N, hkMathIoMode A, hkMathRoundingMode R> 
HK_FORCE_INLINE void hkVector4f::store(hkHalf* p) const
{
	HK_VECTOR4f_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrollf_storeH<N,A,R>::apply(m_quad, p);
}

template <int N, hkMathIoMode A> 
HK_FORCE_INLINE void hkVector4f::store(hkHalf* p) const
{
	HK_VECTOR4f_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrollf_storeH<N,A,HK_ROUND_DEFAULT>::apply(m_quad, p);
}

template <int N> 
HK_FORCE_INLINE void hkVector4f::store(hkHalf* p) const
{
	HK_VECTOR4f_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrollf_storeH<N,HK_IO_SIMD_ALIGNED,HK_ROUND_DEFAULT>::apply(m_quad, p);
}




namespace hkVector4_AdvancedInterface
{
template <int N, hkMathIoMode A, hkMathRoundingMode R>
struct unrollf_storeF16 { HK_FORCE_INLINE static void apply(const hkQuadFloat32& self, hkFloat16* HK_RESTRICT p)
{
	HK_VECTOR4f_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <int N, hkMathRoundingMode R>
struct unrollf_storeF16<N, HK_IO_BYTE_ALIGNED, R> { HK_FORCE_INLINE static void apply(const hkQuadFloat32& self, hkFloat16* HK_RESTRICT p)
{
	static HK_ALIGN16(const unsigned int infinity[4]) = {0x47FFE000, 0x47FFE000, 0x47FFE000, 0x47FFE000};
	static HK_ALIGN16(const unsigned int denormal[4]) = {0x38800000, 0x38800000, 0x38800000, 0x38800000};
	static HK_ALIGN16(const unsigned int fixup[4])    = {0x48000000, 0x48000000, 0x48000000, 0x48000000};
	static HK_ALIGN16(const unsigned int round1[4])   = {0x00000001, 0x00000001, 0x00000001, 0x00000001};
	static HK_ALIGN16(const unsigned int round2[4])   = {0x00000FFF, 0x00000FFF, 0x00000FFF, 0x00000FFF};
	static HK_ALIGN16(const unsigned int base[4])     = {0x00007FFF, 0x00007FFF, 0x00007FFF, 0x00007FFF};
	static HK_ALIGN16(const unsigned int integer[4])  = {0x52000000, 0x52000000, 0x52000000, 0x52000000};

	// Compute masks
	__m128 r_abs = _mm_castsi128_ps(_mm_srli_epi32(_mm_slli_epi32(_mm_castps_si128(self),1),1));
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
	__m128i extract_sign = _mm_slli_epi32(_mm_srai_epi32(_mm_castps_si128(self), 31), 15);
	__m128i mantissa = _mm_and_si128(_mm_or_si128(_mm_srli_epi32(all_rounded, 13), _mm_castps_si128(r_inf)), *(__m128i*)base);
	__m128i assembled = _mm_or_si128(mantissa, extract_sign); // Result in lower words of each element

	// Pack
	__m128i packed = _mm_packs_epi32(assembled, assembled); // result in lower elements

	switch (N)
	{
	case 1:
		{
			float ftmp1; _mm_store_ss(&ftmp1, _mm_castsi128_ps(packed));
			const hkFloat16* HK_RESTRICT htmp1 = (const hkFloat16* HK_RESTRICT)&ftmp1;
			p[0] = htmp1[0];
		}
		break;
	case 2:
		{
			_mm_store_ss((float*)p, _mm_castsi128_ps(packed));
		}
		break;
	case 3:
		{
			double dtmp1; _mm_store_sd(&dtmp1, _mm_castsi128_pd(packed));
			const hkFloat16* HK_RESTRICT htmp1 = (const hkFloat16* HK_RESTRICT)&dtmp1;
			p[0] = htmp1[0];
			p[1] = htmp1[1];
			p[2] = htmp1[2];
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
struct unrollf_storeF16<N, HK_IO_NATIVE_ALIGNED, R> { HK_FORCE_INLINE static void apply(const hkQuadFloat32& self, hkFloat16* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & (sizeof(hkFloat16)-1) ) == 0, "pointer must be aligned to native size of hkFloat16.");
	unrollf_storeF16<N, HK_IO_BYTE_ALIGNED, R>::apply(self,p);
} };
template <int N, hkMathRoundingMode R>
struct unrollf_storeF16<N, HK_IO_SIMD_ALIGNED, R> { HK_FORCE_INLINE static void apply(const hkQuadFloat32& self, hkFloat16* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & ((sizeof(hkFloat16)*(N!=3?N:4) )-1) ) == 0, "pointer must be aligned for SIMD.");
	unrollf_storeF16<N, HK_IO_NATIVE_ALIGNED, R>::apply(self,p);
} };
template <int N, hkMathRoundingMode R>
struct unrollf_storeF16<N, HK_IO_NOT_CACHED, R> { HK_FORCE_INLINE static void apply(const hkQuadFloat32& self, hkFloat16* HK_RESTRICT p)
{
	unrollf_storeF16<N, HK_IO_SIMD_ALIGNED, R>::apply(self,p);
} };
} // namespace 

template <int N, hkMathIoMode A, hkMathRoundingMode R> 
HK_FORCE_INLINE void hkVector4f::store(hkFloat16* p) const
{
	HK_VECTOR4f_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrollf_storeF16<N,A,R>::apply(m_quad, p);
}

template <int N, hkMathIoMode A> 
HK_FORCE_INLINE void hkVector4f::store(hkFloat16* p) const
{
	HK_VECTOR4f_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrollf_storeF16<N,A,HK_ROUND_DEFAULT>::apply(m_quad, p);
}

template <int N> 
HK_FORCE_INLINE void hkVector4f::store(hkFloat16* p) const
{
	HK_VECTOR4f_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrollf_storeF16<N,HK_IO_SIMD_ALIGNED,HK_ROUND_DEFAULT>::apply(m_quad, p);
}


#undef HK_VECTOR4f_COMBINE_XYZ_W

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
