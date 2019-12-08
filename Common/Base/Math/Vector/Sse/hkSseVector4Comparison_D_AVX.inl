/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#if !defined(HK_REAL_IS_DOUBLE) || HK_SSE_VERSION < 0x50
#error This implementation is for 64-Bit double with AVX SIMD instruction set
#endif

static HK_ALIGN32 (const hkInt64 hkVector4Comparison_maskToComparison[16*4]) = 
{
	0,  0, 0, 0,
	~0,  0, 0, 0,
	0, ~0, 0, 0,
	~0, ~0, 0, 0,
	0,  0,~0, 0,
	~0,  0,~0, 0,
	0, ~0,~0, 0,
	~0, ~0,~0, 0,
	0,  0, 0,~0,
	~0,  0, 0,~0,
	0, ~0, 0,~0,
	~0, ~0, 0,~0,
	0,  0,~0,~0,
	~0,  0,~0,~0,
	0, ~0,~0,~0,
	~0, ~0,~0,~0,
};


HK_FORCE_INLINE /*static*/ const hkVector4dComparison HK_CALL hkVector4dComparison::convert(const hkVector4dMask& x)
{
	hkVector4dComparison c;
	c.m_mask = x;
	return c;
}

HK_FORCE_INLINE void hkVector4dComparison::setAnd( hkVector4dComparisonParameter a, hkVector4dComparisonParameter b )
{ 
	m_mask = _mm256_and_pd( a.m_mask, b.m_mask ); 
}

HK_FORCE_INLINE void hkVector4dComparison::setAndNot( hkVector4dComparisonParameter a, hkVector4dComparisonParameter b )
{
	m_mask = _mm256_andnot_pd(b.m_mask, a.m_mask);
}

HK_FORCE_INLINE void hkVector4dComparison::setXor( hkVector4dComparisonParameter a, hkVector4dComparisonParameter b )
{
	m_mask = _mm256_xor_pd(a.m_mask, b.m_mask);
}

HK_FORCE_INLINE void hkVector4dComparison::setNot( hkVector4dComparisonParameter a )
{ 
	m_mask = _mm256_andnot_pd(a.m_mask, *(const __m256d*)&(hkVector4Comparison_maskToComparison[15*4]));
}

HK_FORCE_INLINE void hkVector4dComparison::setOr( hkVector4dComparisonParameter a, hkVector4dComparisonParameter b ) 
{ 
	m_mask = _mm256_or_pd( a.m_mask, b.m_mask ); 
}

HK_FORCE_INLINE void hkVector4dComparison::setSelect( hkVector4dComparisonParameter comp, hkVector4dComparisonParameter trueValue, hkVector4dComparisonParameter falseValue ) 
{
	m_mask = _mm256_blendv_pd(falseValue.m_mask, trueValue.m_mask, comp.m_mask);
}

HK_FORCE_INLINE void hkVector4dComparison::set( Mask m ) 
{ 
	HK_COMPILE_TIME_ASSERT( hkVector4ComparisonMask::INDEX_X == 0);
	HK_COMPILE_TIME_ASSERT( hkVector4ComparisonMask::MASK_X == 1);
	HK_COMPILE_TIME_ASSERT( hkVector4ComparisonMask::MASK_Y == 2);
	HK_COMPILE_TIME_ASSERT( hkVector4ComparisonMask::MASK_XYZW == 15);

	HK_MATH_ASSERT(0x557dac2a, (m&0xf)==m, "illegal mask value handed in");

	m_mask = _mm256_load_pd( (const hkDouble64*)&(hkVector4Comparison_maskToComparison[m*4]) );
}

template <hkVector4ComparisonMask::Mask M>
HK_FORCE_INLINE void hkVector4dComparison::set() 
{ 
	HK_VECTORdCOMPARISON_MASK_CHECK;
	if (M == MASK_NONE)
	{
		m_mask = _mm256_setzero_pd();
	}
	else
	{
		const __m256d zeros = _mm256_setzero_pd();
		const __m256d ones = _mm256_load_pd( (const hkDouble64*)&(hkVector4Comparison_maskToComparison[15*4]) );
		if (M == MASK_XYZW)
		{
			m_mask = ones;
		}
		else
		{
			m_mask = _mm256_blend_pd(zeros,ones,M);
		}
	}
}

template <hkVector4ComparisonMask::Mask M>
HK_FORCE_INLINE hkBool32 hkVector4dComparison::allAreSet() const 
{ 
	HK_VECTORdCOMPARISON_MASK_CHECK;
	if (M == MASK_NONE)
	{
		return true;
	}
	else
	{
		__m256d comp = _mm256_load_pd( (const hkDouble64*)&(hkVector4Comparison_maskToComparison[M*4]) );
		__m256d mask = _mm256_and_pd(m_mask, comp);
		return _mm256_testc_pd(mask, comp);
	}
}

template <hkVector4ComparisonMask::Mask M>
HK_FORCE_INLINE hkBool32 hkVector4dComparison::anyIsSet() const 
{ 
	HK_VECTORdCOMPARISON_MASK_CHECK;
	if (M == MASK_NONE)
	{
		return false;
	}
	else if (M == MASK_XYZW)
	{
		return _mm256_movemask_pd(m_mask); 
	}
	else
	{
		return _mm256_movemask_pd(m_mask) & M;
	}
}

HK_FORCE_INLINE hkBool32 hkVector4dComparison::allAreSet( Mask m ) const 
{ 
	HK_MATH_ASSERT(0x71b4006b, (m&0xf)==m, "illegal mask value handed in");
	__m256d comp = _mm256_load_pd( (const hkDouble64*)&(hkVector4Comparison_maskToComparison[m*4]) );
	__m256d mask = _mm256_and_pd(m_mask, comp);
	return _mm256_testc_pd(mask, comp);
}

HK_FORCE_INLINE hkBool32 hkVector4dComparison::anyIsSet( Mask m ) const 
{ 
	HK_MATH_ASSERT(0x68b44aee, (m&0xf)==m, "illegal mask value handed in");
	return _mm256_movemask_pd(m_mask) & m;
}

HK_FORCE_INLINE hkBool32 hkVector4dComparison::allAreSet() const 
{ 
	return _mm256_testc_pd(m_mask, *(const __m256d*)&(hkVector4Comparison_maskToComparison[15*4]));
}

HK_FORCE_INLINE hkBool32 hkVector4dComparison::anyIsSet() const 
{ 
	return _mm256_movemask_pd(m_mask); 
}

HK_FORCE_INLINE hkVector4ComparisonMask::Mask hkVector4dComparison::getMask() const 
{ 
	return (hkVector4ComparisonMask::Mask)_mm256_movemask_pd(m_mask);
}

HK_FORCE_INLINE hkVector4ComparisonMask::Mask hkVector4dComparison::getMask(Mask m) const 
{ 
	HK_MATH_ASSERT(0x3d2fea61, (m&0xf)==m, "illegal mask value handed in");
	return (hkVector4ComparisonMask::Mask)( _mm256_movemask_pd(m_mask) & m );
}

template <hkVector4ComparisonMask::Mask M>
HK_FORCE_INLINE hkVector4ComparisonMask::Mask hkVector4dComparison::getMask() const 
{ 
	HK_VECTORdCOMPARISON_MASK_CHECK;
	return (hkVector4ComparisonMask::Mask)( _mm256_movemask_pd(m_mask) & M );
}

HK_FORCE_INLINE /*static*/ hkUint32 HK_CALL hkVector4dComparison::getCombinedMask(hkVector4dComparisonParameter ca, hkVector4dComparisonParameter cb, hkVector4dComparisonParameter cc )
{
	return ca.getMask() | (cb.getMask()<<4) | (cc.getMask()<<8);
}

//
//	Horizontal or

template <>
HK_FORCE_INLINE const hkVector4dComparison hkVector4dComparison::horizontalOr<1>() const
{
	const hkQuadDouble64 xxzz = _mm256_movedup_pd(m_mask);

	return hkVector4dComparison::convert(_mm256_permute2f128_pd(xxzz, xxzz, _MM256_PERMUTE2(_MM256_A_LOW, _MM256_A_LOW)));
}

template <>
HK_FORCE_INLINE const hkVector4dComparison hkVector4dComparison::horizontalOr<2>() const
{
	const hkQuadDouble64 yx		= _mm256_permute_pd(m_mask, 0x1);	// [y, x, ...]
	const hkQuadDouble64 xy_xy	= _mm256_or_pd(m_mask, yx);			// [x | y, x | y, ...]

	return hkVector4dComparison::convert(_mm256_permute2f128_pd(xy_xy, xy_xy, _MM256_PERMUTE2(_MM256_A_LOW, _MM256_A_LOW)));
}

template <>
HK_FORCE_INLINE const hkVector4dComparison hkVector4dComparison::horizontalOr<3>() const
{
	const hkQuadDouble64 yxzz	= _mm256_permute_pd(m_mask, 0x1);	// [y, x, z, z]
	const hkQuadDouble64 zz		= _mm256_extractf128_pd(yxzz, 1);	// [z, z, z, z]
	const hkQuadDouble64 xy_xy	= _mm256_or_pd(m_mask, yxzz);		// [x | y, y | x, ...]
	const hkQuadDouble64 xyz	= _mm256_or_pd(xy_xy, zz);			// [x | y | z, x | y | z, ...]

	return hkVector4dComparison::convert(_mm256_permute2f128_pd(xyz, xyz, _MM256_PERMUTE2(_MM256_A_LOW, _MM256_A_LOW)));
}

template <>
HK_FORCE_INLINE const hkVector4dComparison hkVector4dComparison::horizontalOr<4>() const
{
	const hkQuadDouble64 yxwz	= _mm256_permute_pd(m_mask, 0x5);	// [y, x, w, z]
	const hkQuadDouble64 xy_zw	= _mm256_or_pd(m_mask, yxwz);		// [x | y, y | x, z | w, w | z]
	const hkQuadDouble64 zw_xy	= _mm256_permute2f128_pd(xy_zw, xy_zw, _MM256_PERMUTE2(_MM256_A_LOW, _MM256_A_HIGH)); // [z | w, w | z, x | y, y | x]
	const hkQuadDouble64 xyzw	= _mm256_or_pd(xy_zw, zw_xy ); 

	return hkVector4dComparison::convert(xyzw);
}

template <int N>
HK_FORCE_INLINE const hkVector4dComparison hkVector4dComparison::horizontalOr() const
{
	HK_VECTORdCOMPARISON_SUBINDEX_CHECK;
	hkVector4dComparison cmp;
	cmp.set<hkVector4ComparisonMask::MASK_NONE>();
	return cmp;
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
