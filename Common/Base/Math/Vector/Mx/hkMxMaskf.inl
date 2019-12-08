/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

template <int M>
HK_FORCE_INLINE void hkMxMaskf<M>::horizontalAnd4( hkVector4fComparison& andOut ) const
{
	HK_MXVECTORf_MX_NOT_IMPLEMENTED;
}

template <>
HK_FORCE_INLINE void hkMxMaskf<1>::horizontalAnd4( hkVector4fComparison& andOut ) const
{
	if (m_comp.c[0].allAreSet())
	{
		andOut.set<hkVector4ComparisonMask::MASK_X>();
	}
	else
	{
		andOut.set<hkVector4ComparisonMask::MASK_NONE>();
	}
}

template <>
HK_FORCE_INLINE void hkMxMaskf<2>::horizontalAnd4( hkVector4fComparison& andOut ) const
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)

	hkVector4f v0; v0.m_quad = HK_MASK_TO_VECTORf(m_comp.c[0].m_mask);
	hkVector4f v1; v1.m_quad = HK_MASK_TO_VECTORf(m_comp.c[1].m_mask);
	hkVector4f v2; v2.setZero();
	hkVector4f v3; v3.setZero();
	HK_TRANSPOSE4f( v0, v1, v2, v3 );
	hkVector4fComparison t0; t0.setAnd( (const hkVector4fComparison&)v0, (const hkVector4fComparison&)v1 );
	hkVector4fComparison t1; t1.setAnd( (const hkVector4fComparison&)v2, (const hkVector4fComparison&)v3 );
	andOut.setAnd( t0, t1 );

#else

	int mask =	( m_comp.c[0].allAreSet() ? hkVector4ComparisonMask::MASK_X : hkVector4ComparisonMask::MASK_NONE ) |
				( m_comp.c[1].allAreSet() ? hkVector4ComparisonMask::MASK_Y : hkVector4ComparisonMask::MASK_NONE );
	andOut.set( (hkVector4ComparisonMask::Mask)mask );
#endif
}

template <>
HK_FORCE_INLINE void hkMxMaskf<3>::horizontalAnd4( hkVector4fComparison& andOut ) const
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)

	hkVector4f v0; v0.m_quad = HK_MASK_TO_VECTORf(m_comp.c[0].m_mask);
	hkVector4f v1; v1.m_quad = HK_MASK_TO_VECTORf(m_comp.c[1].m_mask);
	hkVector4f v2; v2.m_quad = HK_MASK_TO_VECTORf(m_comp.c[2].m_mask);
	hkVector4f v3; v3.setZero();
	HK_TRANSPOSE4f( v0, v1, v2, v3 );
	hkVector4fComparison t0; t0.setAnd( (const hkVector4fComparison&)v0, (const hkVector4fComparison&)v1 );
	hkVector4fComparison t1; t1.setAnd( (const hkVector4fComparison&)v2, (const hkVector4fComparison&)v3 );
	andOut.setAnd( t0, t1 );

#else

	int mask =	( m_comp.c[0].allAreSet() ? hkVector4ComparisonMask::MASK_X : hkVector4ComparisonMask::MASK_NONE ) |
				( m_comp.c[1].allAreSet() ? hkVector4ComparisonMask::MASK_Y : hkVector4ComparisonMask::MASK_NONE ) |
				( m_comp.c[2].allAreSet() ? hkVector4ComparisonMask::MASK_Z : hkVector4ComparisonMask::MASK_NONE );
	andOut.set( (hkVector4ComparisonMask::Mask)mask );
#endif
}

template <>
HK_FORCE_INLINE void hkMxMaskf<4>::horizontalAnd4( hkVector4fComparison& andOut ) const
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)

	hkVector4f v0; v0.m_quad = HK_MASK_TO_VECTORf(m_comp.c[0].m_mask);
	hkVector4f v1; v1.m_quad = HK_MASK_TO_VECTORf(m_comp.c[1].m_mask);
	hkVector4f v2; v2.m_quad = HK_MASK_TO_VECTORf(m_comp.c[2].m_mask);
	hkVector4f v3; v3.m_quad = HK_MASK_TO_VECTORf(m_comp.c[3].m_mask);
	HK_TRANSPOSE4f( v0, v1, v2, v3 );
	hkVector4fComparison t0; t0.setAnd( (const hkVector4fComparison&)v0, (const hkVector4fComparison&)v1 );
	hkVector4fComparison t1; t1.setAnd( (const hkVector4fComparison&)v2, (const hkVector4fComparison&)v3 );
	andOut.setAnd( t0, t1 );

#else

	int mask =	( m_comp.c[0].allAreSet() ? hkVector4ComparisonMask::MASK_X : hkVector4ComparisonMask::MASK_NONE ) |
				( m_comp.c[1].allAreSet() ? hkVector4ComparisonMask::MASK_Y : hkVector4ComparisonMask::MASK_NONE ) |
				( m_comp.c[2].allAreSet() ? hkVector4ComparisonMask::MASK_Z : hkVector4ComparisonMask::MASK_NONE ) |
				( m_comp.c[3].allAreSet() ? hkVector4ComparisonMask::MASK_W : hkVector4ComparisonMask::MASK_NONE ) ;
	andOut.set( (hkVector4ComparisonMask::Mask)mask );
#endif
}



namespace hkMxMaskf_Implementation
{
template <int I, hkVector4ComparisonMask::Mask MASK> struct setMH { HK_FORCE_INLINE static void apply(hkVector4fComparison* m) { setMH<I-1,MASK>::apply(m); m[I-1].set<MASK>(); } };
template <hkVector4ComparisonMask::Mask MASK> struct setMH<1,MASK> { HK_FORCE_INLINE static void apply(hkVector4fComparison* m) { m[0].set<MASK>(); } };
}
template <int M>
template <hkVector4ComparisonMask::Mask MASK>
HK_FORCE_INLINE void hkMxMaskf<M>::setAll()
{
	hkMxMaskf_Implementation::setMH<M,MASK>::apply(m_comp.c);
}

template <int M>
template <int I>
HK_FORCE_INLINE void hkMxMaskf<M>::set( hkVector4fComparisonParameter a )
{
	HK_MXVECTORf_MX_SUBINDEX_CHECK;
	m_comp.c[I] = a;
}

template <int M>
template <int I>
HK_FORCE_INLINE const hkVector4fComparison& hkMxMaskf<M>::get() const
{
	HK_MXVECTORf_MX_SUBINDEX_CHECK;
	return m_comp.c[I];
}


namespace hkMxMaskf_Implementation
{
template <int I> HK_FORCE_INLINE void setAndMH(hkVector4fComparison* m, const hkVector4fComparison* a, const hkVector4fComparison* b) { setAndMH<I-1>(m,a,b); m[I-1].setAnd(a[I-1], b[I-1]); }
template <> HK_FORCE_INLINE void setAndMH<1>(hkVector4fComparison* m, const hkVector4fComparison* a, const hkVector4fComparison* b) { m[0].setAnd(a[0], b[0]); }
}
template <int M>
HK_FORCE_INLINE void hkMxMaskf<M>::setAnd(hkMxMaskParameterf a, hkMxMaskParameterf b)
{
	hkMxMaskf_Implementation::setAndMH<M>(m_comp.c, a.m_comp.c, b.m_comp.c);
}

namespace hkMxMaskf_Implementation
{
template <int I> HK_FORCE_INLINE void setOrMH(hkVector4fComparison* m, const hkVector4fComparison* a, const hkVector4fComparison* b) { setOrMH<I-1>(m,a,b); m[I-1].setOr(a[I-1], b[I-1]); }
template <> HK_FORCE_INLINE void setOrMH<1>(hkVector4fComparison* m, const hkVector4fComparison* a, const hkVector4fComparison* b) { m[0].setOr(a[0], b[0]); }
}
template <int M>
HK_FORCE_INLINE void hkMxMaskf<M>::setOr(hkMxMaskParameterf a, hkMxMaskParameterf b)
{
	hkMxMaskf_Implementation::setOrMH<M>(m_comp.c, a.m_comp.c, b.m_comp.c);
}


namespace hkMxMaskf_Implementation
{
template <int I> HK_FORCE_INLINE void anyIsSetMH(const hkVector4fComparison* m, hkBool32& b) { anyIsSetMH<I-1>(m,b); b |= m[I-1].anyIsSet(); }
template <> HK_FORCE_INLINE void anyIsSetMH<1>(const hkVector4fComparison* m, hkBool32& b) { b = m[0].anyIsSet(); }
template <int I> HK_FORCE_INLINE void anyIsSetOrMH(const hkVector4fComparison* m, hkVector4fComparison& b) { anyIsSetOrMH<I-1>(m,b); b.setOr(b, m[I-1]); }
template <> HK_FORCE_INLINE void anyIsSetOrMH<1>(const hkVector4fComparison* m, hkVector4fComparison& b) { b = m[0]; }
}
template <int M>
HK_FORCE_INLINE hkBool32 hkMxMaskf<M>::anyIsSet() const
{
	hkBool32 anySet;
	hkMxMaskf_Implementation::anyIsSetMH<M>(m_comp.c, anySet);
	return anySet;
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
