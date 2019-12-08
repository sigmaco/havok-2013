/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_MX_COMMON_AVX_FUNCTIONS_INL
#define HK_MX_COMMON_AVX_FUNCTIONS_INL

#if defined(HK_REAL_IS_DOUBLE) || (HK_SSE_VERSION < 0x50)
#error This implementation is for 32-Bit float with AVX SIMD instruction set
#endif

namespace hkMxCommon_Implementation
{

// two dot products at once:
// (r0,r1) = (a0.b0) , (a1.b1)
template <int N> HK_FORCE_INLINE __m256 dotProdH(const __m256& a, const __m256& b) { return _mm256_dp_ps(a,b,0x1F); }
template <> HK_FORCE_INLINE __m256 dotProdH<2>(const __m256& a, const __m256& b)   { return _mm256_dp_ps(a,b,0x3F); }
template <> HK_FORCE_INLINE __m256 dotProdH<3>(const __m256& a, const __m256& b)   { return _mm256_dp_ps(a,b,0x7F); }
template <> HK_FORCE_INLINE __m256 dotProdH<4>(const __m256& a, const __m256& b)   { return _mm256_dp_ps(a,b,0xFF); }

// two cross products at once:
// (r0,r1) = (v0_0 x v1_0) , (v0_1 x v1_1)
HK_FORCE_INLINE static __m256 crossH(const __m256& v0, const __m256& v1)
{
	const __m256 cross0 = _mm256_mul_ps( _mm256_permute_ps(v0, _MM256_PERMUTE(3,0,2,1)), _mm256_permute_ps(v1, _MM256_PERMUTE(3,1,0,2)) );
	const __m256 cross1 = _mm256_mul_ps( _mm256_permute_ps(v0, _MM256_PERMUTE(3,1,0,2)), _mm256_permute_ps(v1, _MM256_PERMUTE(3,0,2,1)) );
	return _mm256_sub_ps(cross0, cross1);
}

// 8 reciprocals at once
HK_FORCE_INLINE static __m256 reciprocalH(const __m256& r)
{
	const __m256 rb = _mm256_rcp_ps(r);
	// One Newton-Raphson refinement iteration
	const __m256 rbr = _mm256_mul_ps(r, rb);
	const __m256 d = _mm256_sub_ps(_mm256_set1_ps(2.0f), rbr);
	return _mm256_mul_ps(rb, d);
}

// 8 invSqrt at once
HK_FORCE_INLINE static __m256 reciprocalSquareRootH(const __m256& r)
{
	const __m256 e = _mm256_rsqrt_ps(r);
	// One Newton-Raphson refinement iteration
	const __m256 he = _mm256_mul_ps(_mm256_set1_ps(0.5f),e);
	const __m256 ree = _mm256_mul_ps(_mm256_mul_ps(r,e),e);
	return _mm256_mul_ps(he, _mm256_sub_ps(_mm256_set1_ps(3.0f), ree) );
}

} // namespace

#endif // HK_MX_COMMON_AVX_FUNCTIONS_INL

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
