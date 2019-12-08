/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */


static HK_ALIGN16 (const hkInt32 hkVector4fComparison_maskToComparison[16*4]) = 
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

HK_FORCE_INLINE /*static*/ const hkVector4fComparison HK_CALL hkVector4fComparison::convert(const hkVector4fMask& x)
{
	hkVector4fComparison c;
	c.m_mask = x;
	return c;
}

HK_FORCE_INLINE void hkVector4fComparison::setAnd( hkVector4fComparisonParameter a, hkVector4fComparisonParameter b )
{ 
	m_mask = _mm_and_ps( a.m_mask,b.m_mask ); 
}

HK_FORCE_INLINE void hkVector4fComparison::setAndNot( hkVector4fComparisonParameter a, hkVector4fComparisonParameter b )
{
	m_mask = _mm_andnot_ps(b.m_mask, a.m_mask);
}

HK_FORCE_INLINE void hkVector4fComparison::setXor( hkVector4fComparisonParameter a, hkVector4fComparisonParameter b )
{
	m_mask = _mm_xor_ps(a.m_mask, b.m_mask);
}

HK_FORCE_INLINE void hkVector4fComparison::setNot( hkVector4fComparisonParameter a )
{ 
	m_mask = _mm_castsi128_ps(_mm_cmpeq_epi32(_mm_setzero_si128(), _mm_castps_si128(a.m_mask)));
}

HK_FORCE_INLINE void hkVector4fComparison::setOr( hkVector4fComparisonParameter a, hkVector4fComparisonParameter b ) 
{ 
	m_mask = _mm_or_ps( a.m_mask,b.m_mask ); 
}

HK_FORCE_INLINE void hkVector4fComparison::setSelect( hkVector4fComparisonParameter comp, hkVector4fComparisonParameter trueValue, hkVector4fComparisonParameter falseValue ) 
{
#if HK_SSE_VERSION >= 0x41
	m_mask = _mm_blendv_ps(falseValue.m_mask, trueValue.m_mask, comp.m_mask);
#else
	m_mask = _mm_or_ps( _mm_and_ps(comp.m_mask, trueValue.m_mask), _mm_andnot_ps(comp.m_mask, falseValue.m_mask) );
#endif
}

template<> 
HK_FORCE_INLINE void hkVector4fComparison::setSelect<hkVector4fComparison::MASK_X>( hkVector4fComparisonParameter trueValue, hkVector4fComparisonParameter falseValue )
{
	m_mask = _mm_move_ss(falseValue.m_mask, trueValue.m_mask);
}

#if HK_SSE_VERSION >= 0x41
	template<hkVector4ComparisonMask::Mask M> 
	HK_FORCE_INLINE void hkVector4fComparison::setSelect( hkVector4fComparisonParameter trueValue, hkVector4fComparisonParameter falseValue )
	{
		HK_VECTORfCOMPARISON_MASK_CHECK;
		m_mask = _mm_blend_ps(falseValue.m_mask, trueValue.m_mask, M);
	}
#else
	template<> 
	HK_FORCE_INLINE void hkVector4fComparison::setSelect<hkVector4ComparisonMask::MASK_XY>( hkVector4fComparisonParameter trueValue, hkVector4fComparisonParameter falseValue )
	{
		m_mask = _mm_shuffle_ps(trueValue.m_mask, falseValue.m_mask, _MM_SHUFFLE(3,2,1,0));
	}

	template<> 
	HK_FORCE_INLINE void hkVector4fComparison::setSelect<hkVector4ComparisonMask::MASK_XYZ>( hkVector4fComparisonParameter trueValue, hkVector4fComparisonParameter falseValue )
	{
		m_mask = _mm_shuffle_ps( trueValue.m_mask, _mm_unpackhi_ps(trueValue.m_mask, falseValue.m_mask), _MM_SHUFFLE(3,0,1,0));
	}

	template <hkVector4ComparisonMask::Mask M>
	HK_FORCE_INLINE void hkVector4fComparison::setSelect(hkVector4fComparisonParameter trueValue, hkVector4fComparisonParameter falseValue)
	{
		hkVector4fComparison cmp;	cmp.set<M>();
		setSelect(cmp, trueValue, falseValue);
	}
#endif

HK_FORCE_INLINE void hkVector4fComparison::set( Mask m ) 
{ 
	HK_COMPILE_TIME_ASSERT( hkVector4ComparisonMask::INDEX_X == 0);
	HK_COMPILE_TIME_ASSERT( hkVector4ComparisonMask::MASK_X == 1);
	HK_COMPILE_TIME_ASSERT( hkVector4ComparisonMask::MASK_Y == 2);
	HK_COMPILE_TIME_ASSERT( hkVector4ComparisonMask::MASK_XYZW == 15);

	HK_MATH_ASSERT(0x557dac2a, (m&0xf)==m, "illegal mask value handed in");

	m_mask = _mm_load_ps( (const hkFloat32*)&(hkVector4fComparison_maskToComparison[m*4]) );
}

template <hkVector4ComparisonMask::Mask M>
HK_FORCE_INLINE void hkVector4fComparison::set()
{ 
	HK_VECTORfCOMPARISON_MASK_CHECK;
	if (M == MASK_NONE)
	{
		m_mask = _mm_setzero_ps();
	}
	else
	{
#if HK_SSE_VERSION >= 0x41
		const __m128 zeros = _mm_setzero_ps();
		const __m128 ones = _mm_castsi128_ps(_mm_cmpeq_epi32(_mm_setzero_si128(),_mm_setzero_si128()));
		if (M == MASK_XYZW)
		{
			m_mask = ones;
		}
		else
		{
			m_mask = _mm_blend_ps(zeros,ones,M);
		}
#else
		m_mask = _mm_load_ps( (const hkFloat32*)&(hkVector4fComparison_maskToComparison[M*4]) );
#endif
	}
}

template <hkVector4ComparisonMask::Mask M>
HK_FORCE_INLINE hkBool32 hkVector4fComparison::allAreSet() const 
{ 
	HK_VECTORfCOMPARISON_MASK_CHECK;
	if (M == MASK_NONE)
	{
		return true;
	}
	else
	{
#if HK_SSE_VERSION >= 0x41
		if (M == MASK_XYZW)
		{
			return _mm_test_all_ones(_mm_castps_si128(m_mask));
		}
		else
		{
			const __m128 zeros = _mm_setzero_ps();
			const __m128 ones = _mm_castsi128_ps(_mm_cmpeq_epi32(_mm_setzero_si128(),_mm_setzero_si128()));
			__m128 comp = _mm_blend_ps(zeros,ones,M);
			__m128i mask = _mm_and_si128(_mm_castps_si128(m_mask), _mm_castps_si128(comp));
			return _mm_testc_si128(mask, _mm_castps_si128(comp));
		}
#else
		if (M == MASK_XYZW)
		{
			return _mm_movemask_ps(m_mask) == MASK_XYZW; 
		}
		else
		{
			return (_mm_movemask_ps(m_mask) & M) == M; 
		}
#endif
	}
}

template <hkVector4ComparisonMask::Mask M>
HK_FORCE_INLINE hkBool32 hkVector4fComparison::anyIsSet() const 
{ 
	HK_VECTORfCOMPARISON_MASK_CHECK;
	if (M == MASK_NONE)
	{
		return false;
	}
	else if (M == MASK_XYZW)
	{
		return _mm_movemask_ps(m_mask); 
	}
	else
	{
		return _mm_movemask_ps(m_mask) & M; 
	}
}

HK_FORCE_INLINE hkBool32 hkVector4fComparison::allAreSet( Mask m ) const 
{ 
	HK_MATH_ASSERT(0x71b4006b, (m&0xf)==m, "illegal mask value handed in");
#if HK_SSE_VERSION >= 0x41
	__m128i comp = _mm_load_si128( (const __m128i*)&(hkVector4fComparison_maskToComparison[m*4]) );
	__m128i mask = _mm_and_si128(_mm_castps_si128(m_mask), comp);
	return _mm_testc_si128(mask, comp);
#else
	return (_mm_movemask_ps(m_mask) & m) == m; 
#endif
}

HK_FORCE_INLINE hkBool32 hkVector4fComparison::anyIsSet( Mask m ) const 
{ 
	HK_MATH_ASSERT(0x68b44aee, (m&0xf)==m, "illegal mask value handed in");
	return _mm_movemask_ps(m_mask) & m; 
}

HK_FORCE_INLINE hkBool32 hkVector4fComparison::allAreSet() const 
{ 
#if HK_SSE_VERSION >= 0x41
	return _mm_test_all_ones(_mm_castps_si128(m_mask));
#else
	return _mm_movemask_ps(m_mask) == MASK_XYZW; 
#endif
}

HK_FORCE_INLINE hkBool32 hkVector4fComparison::anyIsSet() const 
{ 
	return _mm_movemask_ps(m_mask); 
}

HK_FORCE_INLINE hkVector4ComparisonMask::Mask hkVector4fComparison::getMask() const 
{ 
	return (hkVector4ComparisonMask::Mask)_mm_movemask_ps(m_mask); 
}

HK_FORCE_INLINE hkVector4ComparisonMask::Mask hkVector4fComparison::getMask(Mask m) const 
{ 
	HK_MATH_ASSERT(0x3d2fea61, (m&0xf)==m, "illegal mask value handed in");
	return (hkVector4ComparisonMask::Mask)(_mm_movemask_ps(m_mask) & m); 
}

template <hkVector4ComparisonMask::Mask M>
HK_FORCE_INLINE hkVector4ComparisonMask::Mask hkVector4fComparison::getMask() const 
{ 
	HK_VECTORfCOMPARISON_MASK_CHECK;
	return (hkVector4ComparisonMask::Mask)(_mm_movemask_ps(m_mask) & M); 
}

HK_FORCE_INLINE /*static*/ hkUint32 HK_CALL hkVector4fComparison::getCombinedMask(hkVector4fComparisonParameter ca, hkVector4fComparisonParameter cb, hkVector4fComparisonParameter cc )
{
	return _mm_movemask_ps(ca.m_mask) | (_mm_movemask_ps(cb.m_mask)<<4 ) | (_mm_movemask_ps(cc.m_mask)<<8);
}

//
//	Horizontal or

template <>
HK_FORCE_INLINE const hkVector4fComparison hkVector4fComparison::horizontalOr<1>() const
{
	return hkVector4fComparison::convert(_mm_shuffle_ps(m_mask, m_mask, _MM_SHUFFLE(0, 0, 0, 0)));
}

template <>
HK_FORCE_INLINE const hkVector4fComparison hkVector4fComparison::horizontalOr<2>() const
{
	return hkVector4fComparison::convert( _mm_or_ps(	_mm_shuffle_ps(m_mask, m_mask, _MM_SHUFFLE(0, 0, 0, 0)),	// [x, x, x, x]
													_mm_shuffle_ps(m_mask, m_mask, _MM_SHUFFLE(1, 1, 1, 1))) );	// [y, y, y, y]
}

template <>
HK_FORCE_INLINE const hkVector4fComparison hkVector4fComparison::horizontalOr<3>() const
{
	const hkVector4fMask xy	= _mm_or_ps(	_mm_shuffle_ps(m_mask, m_mask, _MM_SHUFFLE(0, 0, 0, 0)),				// [x, x, x, x]
											_mm_shuffle_ps(m_mask, m_mask, _MM_SHUFFLE(1, 1, 1, 1)));				// [y, y, y, y]

	return hkVector4fComparison::convert( _mm_or_ps(	xy, _mm_shuffle_ps(m_mask, m_mask, _MM_SHUFFLE(2, 2, 2, 2))) );	// [z, z, z, z]
}

template <>
HK_FORCE_INLINE const hkVector4fComparison hkVector4fComparison::horizontalOr<4>() const
{
	const hkVector4fMask or0	= _mm_or_ps(	_mm_shuffle_ps(m_mask, m_mask, _MM_SHUFFLE(1, 0, 3, 2)),	// [y | x, x | y, w | z, z | w]
											m_mask);
	const hkVector4fMask or1	=				_mm_shuffle_ps(or0,or0, _MM_SHUFFLE(2, 3, 0, 1));			// [w | z, z | w, y | x, x | y]

	return hkVector4fComparison::convert(_mm_or_ps(or0, or1));
}

template <int N>
HK_FORCE_INLINE const hkVector4fComparison hkVector4fComparison::horizontalOr() const
{
	HK_VECTORfCOMPARISON_SUBINDEX_CHECK;
	hkVector4fComparison cmp;
	cmp.set<hkVector4ComparisonMask::MASK_NONE>();
	return cmp;
}

//
//	Sets all components of this to the bitwise AND of the first N components, i.e. (mask[0] | mask[1] | ... | mask[I - 1])

template <>
HK_FORCE_INLINE const hkVector4fComparison hkVector4fComparison::horizontalAnd<1>() const
{
	return hkVector4fComparison::convert(_mm_shuffle_ps(m_mask, m_mask, _MM_SHUFFLE(0, 0, 0, 0)));
}

template <>
HK_FORCE_INLINE const hkVector4fComparison hkVector4fComparison::horizontalAnd<2>() const
{
	return hkVector4fComparison::convert( _mm_and_ps(	_mm_shuffle_ps(m_mask, m_mask, _MM_SHUFFLE(0, 0, 0, 0)),	// [x, x, x, x]
														_mm_shuffle_ps(m_mask, m_mask, _MM_SHUFFLE(1, 1, 1, 1))) );	// [y, y, y, y]
}

template <>
HK_FORCE_INLINE const hkVector4fComparison hkVector4fComparison::horizontalAnd<3>() const
{
	const hkVector4fMask xy	= _mm_and_ps(	_mm_shuffle_ps(m_mask, m_mask, _MM_SHUFFLE(0, 0, 0, 0)),				// [x, x, x, x]
											_mm_shuffle_ps(m_mask, m_mask, _MM_SHUFFLE(1, 1, 1, 1)));				// [y, y, y, y]

	return hkVector4fComparison::convert( _mm_and_ps(xy, _mm_shuffle_ps(m_mask, m_mask, _MM_SHUFFLE(2, 2, 2, 2))) );	// [z, z, z, z]
}

template <>
HK_FORCE_INLINE const hkVector4fComparison hkVector4fComparison::horizontalAnd<4>() const
{
	const hkVector4fMask and0	= _mm_and_ps(	_mm_shuffle_ps(m_mask, m_mask, _MM_SHUFFLE(1, 0, 3, 2)),	// [y & x, x & y, w & z, z & w]
												m_mask);
	const hkVector4fMask and1	=				_mm_shuffle_ps(and0,and0, _MM_SHUFFLE(2, 3, 0, 1));			// [w & z, z & w, y & x, x & y]

	return hkVector4fComparison::convert(_mm_and_ps(and0, and1));
}

template <int N>
HK_FORCE_INLINE const hkVector4fComparison hkVector4fComparison::horizontalAnd() const
{
	HK_VECTORfCOMPARISON_SUBINDEX_CHECK;
	hkVector4fComparison cmp;
	cmp.set<hkVector4fComparison::MASK_NONE>();
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
