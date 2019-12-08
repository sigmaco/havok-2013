/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#if HK_SSE_VERSION < 0x50
#error This implementation is for 64-Bit double with AVX SIMD instruction set
#endif


#define HK_VECTOR4dUTIL_dot4_4vs4
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::dot4_4vs4( hkVector4dParameter a0, hkVector4dParameter b0, hkVector4dParameter a1, hkVector4dParameter b1, hkVector4dParameter a2, hkVector4dParameter b2, hkVector4dParameter a3, hkVector4dParameter b3, hkVector4d& dotsOut)
{
	const hkQuadDouble64 m0 = _mm256_mul_pd(b0.m_quad, a0.m_quad);
	const hkQuadDouble64 m1 = _mm256_mul_pd(b1.m_quad, a1.m_quad);
	const hkQuadDouble64 m2 = _mm256_mul_pd(b2.m_quad, a2.m_quad);
	const hkQuadDouble64 m3 = _mm256_mul_pd(b3.m_quad, a3.m_quad);

	// in-lane sum
	const hkQuadDouble64 hsum0 = _mm256_hadd_pd(m0, m0);
	const hkQuadDouble64 hsum1 = _mm256_hadd_pd(m1, m1);
	const hkQuadDouble64 hsum2 = _mm256_hadd_pd(m2, m2);
	const hkQuadDouble64 hsum3 = _mm256_hadd_pd(m3, m3);

	// cross-lane
	const hkQuadDouble64 hsuminv0 = _mm256_permute2f128_pd(hsum0, hsum0, _MM256_PERMUTE2(_MM256_A_LOW, _MM256_A_HIGH));
	const hkQuadDouble64 hsuminv1 = _mm256_permute2f128_pd(hsum1, hsum1, _MM256_PERMUTE2(_MM256_A_LOW, _MM256_A_HIGH));
	const hkQuadDouble64 hsuminv2 = _mm256_permute2f128_pd(hsum2, hsum2, _MM256_PERMUTE2(_MM256_A_LOW, _MM256_A_HIGH));
	const hkQuadDouble64 hsuminv3 = _mm256_permute2f128_pd(hsum3, hsum3, _MM256_PERMUTE2(_MM256_A_LOW, _MM256_A_HIGH));

	// grand sum
	const hkQuadDouble64 dp0 = _mm256_add_pd(hsum0, hsuminv0);
	const hkQuadDouble64 dp1 = _mm256_add_pd(hsum1, hsuminv1);
	const hkQuadDouble64 dp2 = _mm256_add_pd(hsum2, hsuminv2);
	const hkQuadDouble64 dp3 = _mm256_add_pd(hsum3, hsuminv3);

	const hkQuadDouble64 dp0022 = _mm256_permute2f128_pd(dp0, dp2, 0x20);
	const hkQuadDouble64 dp1133 = _mm256_permute2f128_pd(dp1, dp3, 0x20);

	dotsOut.m_quad = _mm256_shuffle_pd(dp0022, dp1133, _MM256_SHUFFLE(1, 0, 1, 0));
}

#define HK_VECTOR4dUTIL_dot4_1vs4
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::dot4_1vs4( hkVector4dParameter vectorIn, hkVector4dParameter a0, hkVector4dParameter a1, hkVector4dParameter a2, hkVector4dParameter a3, hkVector4d& dotsOut)
{
	const hkQuadDouble64 m0 = _mm256_mul_pd(vectorIn.m_quad, a0.m_quad);
	const hkQuadDouble64 m1 = _mm256_mul_pd(vectorIn.m_quad, a1.m_quad);
	const hkQuadDouble64 m2 = _mm256_mul_pd(vectorIn.m_quad, a2.m_quad);
	const hkQuadDouble64 m3 = _mm256_mul_pd(vectorIn.m_quad, a3.m_quad);

	// in-lane sum
	const hkQuadDouble64 hsum0 = _mm256_hadd_pd(m0, m0);
	const hkQuadDouble64 hsum1 = _mm256_hadd_pd(m1, m1);
	const hkQuadDouble64 hsum2 = _mm256_hadd_pd(m2, m2);
	const hkQuadDouble64 hsum3 = _mm256_hadd_pd(m3, m3);

	// cross-lane
	const hkQuadDouble64 hsuminv0 = _mm256_permute2f128_pd(hsum0, hsum0, _MM256_PERMUTE2(_MM256_A_LOW, _MM256_A_HIGH));
	const hkQuadDouble64 hsuminv1 = _mm256_permute2f128_pd(hsum1, hsum1, _MM256_PERMUTE2(_MM256_A_LOW, _MM256_A_HIGH));
	const hkQuadDouble64 hsuminv2 = _mm256_permute2f128_pd(hsum2, hsum2, _MM256_PERMUTE2(_MM256_A_LOW, _MM256_A_HIGH));
	const hkQuadDouble64 hsuminv3 = _mm256_permute2f128_pd(hsum3, hsum3, _MM256_PERMUTE2(_MM256_A_LOW, _MM256_A_HIGH));

	// grand sum
	const hkQuadDouble64 dp0 = _mm256_add_pd(hsum0, hsuminv0);
	const hkQuadDouble64 dp1 = _mm256_add_pd(hsum1, hsuminv1);
	const hkQuadDouble64 dp2 = _mm256_add_pd(hsum2, hsuminv2);
	const hkQuadDouble64 dp3 = _mm256_add_pd(hsum3, hsuminv3);

	const hkQuadDouble64 dp0022 = _mm256_permute2f128_pd(dp0, dp2, 0x20);
	const hkQuadDouble64 dp1133 = _mm256_permute2f128_pd(dp1, dp3, 0x20);

	dotsOut.m_quad = _mm256_shuffle_pd(dp0022, dp1133, _MM256_SHUFFLE(1, 0, 1, 0));
}

#define HK_VECTOR4dUTIL_dot4_1vs3
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::dot4_1vs3( hkVector4dParameter vectorIn, hkVector4dParameter a0, hkVector4dParameter a1, hkVector4dParameter a2, hkVector4d& dotsOut)
{
	const hkQuadDouble64 m0 = _mm256_mul_pd(vectorIn.m_quad, a0.m_quad);
	const hkQuadDouble64 m1 = _mm256_mul_pd(vectorIn.m_quad, a1.m_quad);
	const hkQuadDouble64 m2 = _mm256_mul_pd(vectorIn.m_quad, a2.m_quad);

	// in-lane sum
	const hkQuadDouble64 hsum0 = _mm256_hadd_pd(m0, m0);
	const hkQuadDouble64 hsum1 = _mm256_hadd_pd(m1, m1);
	const hkQuadDouble64 hsum2 = _mm256_hadd_pd(m2, m2);

	// cross-lane
	const hkQuadDouble64 hsuminv0 = _mm256_permute2f128_pd(hsum0, hsum0, _MM256_PERMUTE2(_MM256_A_LOW, _MM256_A_HIGH));
	const hkQuadDouble64 hsuminv1 = _mm256_permute2f128_pd(hsum1, hsum1, _MM256_PERMUTE2(_MM256_A_LOW, _MM256_A_HIGH));
	const hkQuadDouble64 hsuminv2 = _mm256_permute2f128_pd(hsum2, hsum2, _MM256_PERMUTE2(_MM256_A_LOW, _MM256_A_HIGH));

	// grand sum
	const hkQuadDouble64 dp0 = _mm256_add_pd(hsum0, hsuminv0);
	const hkQuadDouble64 dp1 = _mm256_add_pd(hsum1, hsuminv1);
	const hkQuadDouble64 dp2 = _mm256_add_pd(hsum2, hsuminv2);

	const hkQuadDouble64 dp0022 = _mm256_permute2f128_pd(dp0, dp2, 0x20);
	const hkQuadDouble64 dp1133 = _mm256_permute2f128_pd(dp1, dp1, 0x20);

	dotsOut.m_quad = _mm256_shuffle_pd(dp0022, dp1133, _MM256_SHUFFLE(1, 0, 1, 0));
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
