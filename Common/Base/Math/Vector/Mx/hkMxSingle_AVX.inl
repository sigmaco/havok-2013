/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#if defined(HK_REAL_IS_DOUBLE) || (HK_SSE_VERSION < 0x50)
#error This implementation is for 32-Bit float with AVX SIMD instruction set
#endif

#ifndef HK_DISABLE_MATH_CONSTRUCTORS

template <int M>
HK_FORCE_INLINE hkMxSinglef<M>::hkMxSinglef(hkSimdFloat32Parameter v)
{
	m_single.s = _mm256_broadcast_ps(&v.m_real);
}

template <int M>
HK_FORCE_INLINE hkMxSinglef<M>::hkMxSinglef(hkVector4fParameter v)
{
	m_single.s = _mm256_broadcast_ps(&v.m_quad);
}

#endif

template <int M>
HK_FORCE_INLINE void hkMxSinglef<M>::operator= ( hkMxSinglefParameter v )
{
	m_single.s = v.m_single.s;
}

template <int M>
HK_FORCE_INLINE const hkVector4f& hkMxSinglef<M>::getVector() const
{
	hkVector4f s;
	s.m_quad = _mm256_extractf128_ps(m_single.s, 0x0);
	return s;
}

template <int M>
HK_FORCE_INLINE void hkMxSinglef<M>::setVector(hkVector4fParameter r)
{
	m_single.s = _mm256_broadcast_ps(&r.m_quad);
}

template <int M>
HK_FORCE_INLINE void hkMxSinglef<M>::setZero()
{
	m_single.s = _mm256_setzero_ps();
}

template <int M>
template<int C>
HK_FORCE_INLINE void hkMxSinglef<M>::setConstant()
{
	m_single.s = _mm256_broadcast_ps(g_vectorfConstants + C);
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
