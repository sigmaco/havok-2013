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

#define HK_VECTOR4dUTIL_atan2Approximation
template <>
HK_FORCE_INLINE hkSimdDouble64 HK_CALL hkVector4UtilImpl<hkDouble64>::atan2Approximation(hkSimdDouble64Parameter y, hkSimdDouble64Parameter x)
{
	hkSimdDouble64 result;
	result.m_real = hkMath::twoAtan2(y.m_real,x.m_real);
	return result;
}
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::atan2Approximation(hkVector4dParameter y, hkVector4dParameter x, hkVector4d& result)
{
	result.m_quad.xy = hkMath::twoAtan2(y.m_quad.xy, x.m_quad.xy);
	result.m_quad.zw = hkMath::twoAtan2(y.m_quad.zw, x.m_quad.zw);
}

#define HK_VECTOR4dUTIL_sinCos
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::sinCos(hkVector4dParameter r, hkVector4d& sc)
{
	sc.m_quad.xy = hkMath::twoSinCos(r.m_quad.xy);
	sc.m_quad.zw = hkMath::twoSinCos(r.m_quad.zw);
}
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::sinCos(hkSimdDouble64Parameter r, hkVector4d& sc)
{
	sc.m_quad.xy = hkMath::twoSinCos(r.m_real);
	sc.m_quad.zw = sc.m_quad.xy;
}
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::sinCos(hkSimdDouble64Parameter r, hkSimdDouble64& s, hkSimdDouble64& c)
{
	const __m128d sc = hkMath::twoSinCos(r.m_real);
	s.m_real = _mm_shuffle_pd(sc,sc,_MM_SHUFFLE2(0,0));
	c.m_real = _mm_shuffle_pd(sc,sc,_MM_SHUFFLE2(1,1));
}

#define HK_VECTOR4dUTIL_sinCosApproximation
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::sinCosApproximation(hkVector4dParameter r, hkVector4d& sc)
{
	sc.m_quad.xy = hkMath::twoSinCosApproximation(r.m_quad.xy);
	sc.m_quad.zw = hkMath::twoSinCosApproximation(r.m_quad.zw);
}
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::sinCosApproximation(hkSimdDouble64Parameter r, hkVector4d& sc)
{
	sc.m_quad.xy = hkMath::twoSinCosApproximation(r.m_real);
	sc.m_quad.zw = sc.m_quad.xy;
}
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::sinCosApproximation(hkSimdDouble64Parameter r, hkSimdDouble64& s, hkSimdDouble64& c)
{
	const __m128d sc = hkMath::twoSinCosApproximation(r.m_real);
	s.m_real = _mm_shuffle_pd(sc,sc,_MM_SHUFFLE2(0,0));
	c.m_real = _mm_shuffle_pd(sc,sc,_MM_SHUFFLE2(1,1));
}

#define HK_VECTOR4dUTIL_aSinAcos
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::aSin(hkVector4dParameter r, hkVector4d& sc)
{
	sc.m_quad.xy = hkMath::twoAsin(r.m_quad.xy);
	sc.m_quad.zw = hkMath::twoAsin(r.m_quad.zw);
}
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::aCos(hkVector4dParameter r, hkVector4d& sc)
{
	sc.m_quad.xy = hkMath::twoAcos(r.m_quad.xy);
	sc.m_quad.zw = hkMath::twoAcos(r.m_quad.zw);
}
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::aSinAcos(hkVector4dParameter r, hkVector4d& sc)
{
	sc.m_quad.xy = hkMath::twoAsinAcos(r.m_quad.xy);
	sc.m_quad.zw = hkMath::twoAsinAcos(r.m_quad.zw);
}
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::aSinAcos(hkSimdDouble64Parameter r, hkVector4d& sc)
{
	sc.m_quad.xy = hkMath::twoAsinAcos(r.m_real);
	sc.m_quad.zw = sc.m_quad.xy;
}
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::aSinAcos(hkSimdDouble64Parameter r, hkSimdDouble64& s, hkSimdDouble64& c)
{
	const __m128d sc = hkMath::twoAsinAcos(r.m_real);
	s.m_real = _mm_shuffle_pd(sc,sc,_MM_SHUFFLE2(0,0));
	c.m_real = _mm_shuffle_pd(sc,sc,_MM_SHUFFLE2(1,1));
}

#if HK_SSE_VERSION >= 0x41
// yep, we have a dot product instruction

#define HK_VECTOR4dUTIL_rotateInversePoints
template <>
HK_FORCE_INLINE void	HK_CALL hkVector4UtilImpl<hkDouble64>::rotateInversePoints( const hkRotationd& r, const hkVector4d* vectorsIn, int numVectors, hkVector4d* vectorsOut )
{
	HK_MATH_ASSERT( 0xf0200104, numVectors > 0, "At least one vector to rotate required");

	const hkQuadDouble64 c0 = r.getColumn<0>().m_quad;
	const hkQuadDouble64 c1 = r.getColumn<1>().m_quad;
	const hkQuadDouble64 c2 = r.getColumn<2>().m_quad;
	for( int i = 0; i < numVectors; ++i )
	{
		const hkQuadDouble64 b = vectorsIn[i].m_quad;

		const hkSingleDouble64 r0xy = _mm_dp_pd( c0.xy, b.xy, 0x31 );
		const hkSingleDouble64 r0zw = _mm_dp_pd( c0.zw, b.zw, 0x11 );
		const hkSingleDouble64 r0   = _mm_add_pd(r0xy, r0zw);

		const hkSingleDouble64 r1xy = _mm_dp_pd( c1.xy, b.xy, 0x32 );
		const hkSingleDouble64 r1zw = _mm_dp_pd( c1.zw, b.zw, 0x12 );
		const hkSingleDouble64 r1   = _mm_add_pd(r1xy, r1zw);

		vectorsOut[i].m_quad.xy = _mm_or_pd(r0, r1);

		const hkSingleDouble64 r2xy = _mm_dp_pd( c2.xy, b.xy, 0x31 );
		const hkSingleDouble64 r2zw = _mm_dp_pd( c2.zw, b.zw, 0x11 );

		vectorsOut[i].m_quad.zw = _mm_add_pd(r2xy, r2zw);
	}
}

#define HK_VECTOR4dUTIL_dot3_3vs3
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::dot3_3vs3(hkVector4dParameter a0, hkVector4dParameter b0, hkVector4dParameter a1, hkVector4dParameter b1, hkVector4dParameter a2, hkVector4dParameter b2, hkVector4d& dotsOut)
{
	const hkSingleDouble64 dp0xy = _mm_dp_pd(a0.m_quad.xy, b0.m_quad.xy, 0x31);
	const hkSingleDouble64 dp0zw = _mm_dp_pd(a0.m_quad.zw, b0.m_quad.zw, 0x11);
	const hkSingleDouble64 dp0   = _mm_add_pd(dp0xy, dp0zw);

	const hkSingleDouble64 dp1xy = _mm_dp_pd(a1.m_quad.xy, b1.m_quad.xy, 0x32);
	const hkSingleDouble64 dp1zw = _mm_dp_pd(a1.m_quad.zw, b1.m_quad.zw, 0x12);
	const hkSingleDouble64 dp1   = _mm_add_pd(dp1xy, dp1zw);

	dotsOut.m_quad.xy = _mm_or_pd(dp0,dp1);

	const hkSingleDouble64 dp2xy = _mm_dp_pd(a2.m_quad.xy, b2.m_quad.xy, 0x31);
	const hkSingleDouble64 dp2zw = _mm_dp_pd(a2.m_quad.zw, b2.m_quad.zw, 0x11);

	dotsOut.m_quad.zw = _mm_add_pd(dp2xy, dp2zw);
}

#define HK_VECTOR4dUTIL_dot3_4vs4
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::dot3_4vs4(hkVector4dParameter a0, hkVector4dParameter b0, hkVector4dParameter a1, hkVector4dParameter b1, hkVector4dParameter a2, hkVector4dParameter b2, hkVector4dParameter a3, hkVector4dParameter b3, hkVector4d& dotsOut)
{
	const hkSingleDouble64 dp0xy = _mm_dp_pd(a0.m_quad.xy, b0.m_quad.xy, 0x31);
	const hkSingleDouble64 dp0zw = _mm_dp_pd(a0.m_quad.zw, b0.m_quad.zw, 0x11);
	const hkSingleDouble64 dp0   = _mm_add_pd(dp0xy, dp0zw);

	const hkSingleDouble64 dp1xy = _mm_dp_pd(a1.m_quad.xy, b1.m_quad.xy, 0x32);
	const hkSingleDouble64 dp1zw = _mm_dp_pd(a1.m_quad.zw, b1.m_quad.zw, 0x12);
	const hkSingleDouble64 dp1   = _mm_add_pd(dp1xy, dp1zw);

	dotsOut.m_quad.xy = _mm_or_pd(dp0,dp1);

	const hkSingleDouble64 dp2xy = _mm_dp_pd(a2.m_quad.xy, b2.m_quad.xy, 0x31);
	const hkSingleDouble64 dp2zw = _mm_dp_pd(a2.m_quad.zw, b2.m_quad.zw, 0x11);
	const hkSingleDouble64 dp2   = _mm_add_pd(dp2xy, dp2zw);

	const hkSingleDouble64 dp3xy = _mm_dp_pd(a3.m_quad.xy, b3.m_quad.xy, 0x32);
	const hkSingleDouble64 dp3zw = _mm_dp_pd(a3.m_quad.zw, b3.m_quad.zw, 0x12);
	const hkSingleDouble64 dp3   = _mm_add_pd(dp3xy, dp3zw);

	dotsOut.m_quad.zw = _mm_or_pd(dp2,dp3);
}

#define HK_VECTOR4dUTIL_dot4_4vs4
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::dot4_4vs4( hkVector4dParameter a0, hkVector4dParameter b0, hkVector4dParameter a1, hkVector4dParameter b1, hkVector4dParameter a2, hkVector4dParameter b2, hkVector4dParameter a3, hkVector4dParameter b3, hkVector4d& dotsOut)
{
	const hkSingleDouble64 dp0xy = _mm_dp_pd(a0.m_quad.xy, b0.m_quad.xy, 0x31);
	const hkSingleDouble64 dp0zw = _mm_dp_pd(a0.m_quad.zw, b0.m_quad.zw, 0x31);
	const hkSingleDouble64 dp0   = _mm_add_pd(dp0xy, dp0zw);

	const hkSingleDouble64 dp1xy = _mm_dp_pd(a1.m_quad.xy, b1.m_quad.xy, 0x32);
	const hkSingleDouble64 dp1zw = _mm_dp_pd(a1.m_quad.zw, b1.m_quad.zw, 0x32);
	const hkSingleDouble64 dp1   = _mm_add_pd(dp1xy, dp1zw);

	dotsOut.m_quad.xy = _mm_or_pd(dp0,dp1);

	const hkSingleDouble64 dp2xy = _mm_dp_pd(a2.m_quad.xy, b2.m_quad.xy, 0x31);
	const hkSingleDouble64 dp2zw = _mm_dp_pd(a2.m_quad.zw, b2.m_quad.zw, 0x31);
	const hkSingleDouble64 dp2   = _mm_add_pd(dp2xy, dp2zw);

	const hkSingleDouble64 dp3xy = _mm_dp_pd(a3.m_quad.xy, b3.m_quad.xy, 0x32);
	const hkSingleDouble64 dp3zw = _mm_dp_pd(a3.m_quad.zw, b3.m_quad.zw, 0x32);
	const hkSingleDouble64 dp3   = _mm_add_pd(dp3xy, dp3zw);

	dotsOut.m_quad.zw = _mm_or_pd(dp2,dp3);
}

#define HK_VECTOR4dUTIL_dot3_1vs4
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::dot3_1vs4( hkVector4dParameter v, hkVector4dParameter a0, hkVector4dParameter a1, hkVector4dParameter a2, hkVector4dParameter a3, hkVector4d& dotsOut)
{
	const hkSingleDouble64 dp0xy = _mm_dp_pd(v.m_quad.xy, a0.m_quad.xy, 0x31);
	const hkSingleDouble64 dp0zw = _mm_dp_pd(v.m_quad.zw, a0.m_quad.zw, 0x11);
	const hkSingleDouble64 dp0   = _mm_add_pd(dp0xy, dp0zw);

	const hkSingleDouble64 dp1xy = _mm_dp_pd(v.m_quad.xy, a1.m_quad.xy, 0x32);
	const hkSingleDouble64 dp1zw = _mm_dp_pd(v.m_quad.zw, a1.m_quad.zw, 0x12);
	const hkSingleDouble64 dp1   = _mm_add_pd(dp1xy, dp1zw);

	dotsOut.m_quad.xy = _mm_or_pd(dp0,dp1);

	const hkSingleDouble64 dp2xy = _mm_dp_pd(v.m_quad.xy, a2.m_quad.xy, 0x31);
	const hkSingleDouble64 dp2zw = _mm_dp_pd(v.m_quad.zw, a2.m_quad.zw, 0x11);
	const hkSingleDouble64 dp2   = _mm_add_pd(dp2xy, dp2zw);

	const hkSingleDouble64 dp3xy = _mm_dp_pd(v.m_quad.xy, a3.m_quad.xy, 0x32);
	const hkSingleDouble64 dp3zw = _mm_dp_pd(v.m_quad.zw, a3.m_quad.zw, 0x12);
	const hkSingleDouble64 dp3   = _mm_add_pd(dp3xy, dp3zw);

	dotsOut.m_quad.zw = _mm_or_pd(dp2,dp3);
}

//
//	Sets this vector components: this(i) = vector.dot<4>(AI) for i=0..3

#define HK_VECTOR4dUTIL_dot4_1vs4
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::dot4_1vs4( hkVector4dParameter v, hkVector4dParameter a0, hkVector4dParameter a1, hkVector4dParameter a2, hkVector4dParameter a3, hkVector4d& dotsOut)
{
	const hkSingleDouble64 dp0xy = _mm_dp_pd(v.m_quad.xy, a0.m_quad.xy, 0x31);
	const hkSingleDouble64 dp0zw = _mm_dp_pd(v.m_quad.zw, a0.m_quad.zw, 0x31);
	const hkSingleDouble64 dp0   = _mm_add_pd(dp0xy, dp0zw);

	const hkSingleDouble64 dp1xy = _mm_dp_pd(v.m_quad.xy, a1.m_quad.xy, 0x32);
	const hkSingleDouble64 dp1zw = _mm_dp_pd(v.m_quad.zw, a1.m_quad.zw, 0x32);
	const hkSingleDouble64 dp1   = _mm_add_pd(dp1xy, dp1zw);

	dotsOut.m_quad.xy = _mm_or_pd(dp0,dp1);

	const hkSingleDouble64 dp2xy = _mm_dp_pd(v.m_quad.xy, a2.m_quad.xy, 0x31);
	const hkSingleDouble64 dp2zw = _mm_dp_pd(v.m_quad.zw, a2.m_quad.zw, 0x31);
	const hkSingleDouble64 dp2   = _mm_add_pd(dp2xy, dp2zw);

	const hkSingleDouble64 dp3xy = _mm_dp_pd(v.m_quad.xy, a3.m_quad.xy, 0x32);
	const hkSingleDouble64 dp3zw = _mm_dp_pd(v.m_quad.zw, a3.m_quad.zw, 0x32);
	const hkSingleDouble64 dp3   = _mm_add_pd(dp3xy, dp3zw);

	dotsOut.m_quad.zw = _mm_or_pd(dp2,dp3);
}

//
//	Sets this vector components: this(i) = vector.dot<4>(AI) for i=0..2

#define HK_VECTOR4dUTIL_dot4_1vs3
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::dot4_1vs3( hkVector4dParameter v, hkVector4dParameter a0, hkVector4dParameter a1, hkVector4dParameter a2, hkVector4d& dotsOut)
{
	const hkSingleDouble64 dp0xy = _mm_dp_pd(v.m_quad.xy, a0.m_quad.xy, 0x31);
	const hkSingleDouble64 dp0zw = _mm_dp_pd(v.m_quad.zw, a0.m_quad.zw, 0x31);
	const hkSingleDouble64 dp0   = _mm_add_pd(dp0xy, dp0zw);

	const hkSingleDouble64 dp1xy = _mm_dp_pd(v.m_quad.xy, a1.m_quad.xy, 0x32);
	const hkSingleDouble64 dp1zw = _mm_dp_pd(v.m_quad.zw, a1.m_quad.zw, 0x32);
	const hkSingleDouble64 dp1   = _mm_add_pd(dp1xy, dp1zw);

	dotsOut.m_quad.xy = _mm_or_pd(dp0,dp1);

	const hkSingleDouble64 dp2xy = _mm_dp_pd(v.m_quad.xy, a2.m_quad.xy, 0x31);
	const hkSingleDouble64 dp2zw = _mm_dp_pd(v.m_quad.zw, a2.m_quad.zw, 0x31);
	const hkSingleDouble64 dp2   = _mm_add_pd(dp2xy, dp2zw);

	dotsOut.m_quad.zw = dp2;
}

#define HK_VECTOR4dUTIL_dot3_2vs2
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::dot3_2vs2( hkVector4dParameter a0, hkVector4dParameter a2, hkVector4dParameter b0, hkVector4dParameter b1, hkVector4d& dotsOut)
{
	const hkSingleDouble64 dp0xy = _mm_dp_pd(a0.m_quad.xy, b0.m_quad.xy, 0x31);
	const hkSingleDouble64 dp0zw = _mm_dp_pd(a0.m_quad.zw, b0.m_quad.zw, 0x11);
	const hkSingleDouble64 dp0   = _mm_add_pd(dp0xy, dp0zw);

	const hkSingleDouble64 dp1xy = _mm_dp_pd(a0.m_quad.xy, b1.m_quad.xy, 0x32);
	const hkSingleDouble64 dp1zw = _mm_dp_pd(a0.m_quad.zw, b1.m_quad.zw, 0x12);
	const hkSingleDouble64 dp1   = _mm_add_pd(dp1xy, dp1zw);

	dotsOut.m_quad.xy = _mm_or_pd(dp0,dp1);

	const hkSingleDouble64 dp2xy = _mm_dp_pd(a2.m_quad.xy, b0.m_quad.xy, 0x31);
	const hkSingleDouble64 dp2zw = _mm_dp_pd(a2.m_quad.zw, b0.m_quad.zw, 0x11);
	const hkSingleDouble64 dp2   = _mm_add_pd(dp2xy, dp2zw);

	const hkSingleDouble64 dp3xy = _mm_dp_pd(a2.m_quad.xy, b1.m_quad.xy, 0x32);
	const hkSingleDouble64 dp3zw = _mm_dp_pd(a2.m_quad.zw, b1.m_quad.zw, 0x12);
	const hkSingleDouble64 dp3   = _mm_add_pd(dp3xy, dp3zw);

	dotsOut.m_quad.zw = _mm_or_pd(dp2,dp3);
}

#elif HK_SSE_VERSION >= 0x30

#define HK_VECTOR4dUTIL_dot4_4vs4
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::dot4_4vs4( hkVector4dParameter a0, hkVector4dParameter b0, hkVector4dParameter a1, hkVector4dParameter b1, hkVector4dParameter a2, hkVector4dParameter b2, hkVector4dParameter a3, hkVector4dParameter b3, hkVector4d& dotsOut)
{
	const hkSingleDouble64 m0xy = _mm_mul_pd(b0.m_quad.xy, a0.m_quad.xy);
	const hkSingleDouble64 m1xy = _mm_mul_pd(b1.m_quad.xy, a1.m_quad.xy);
	const hkSingleDouble64 m2xy = _mm_mul_pd(b2.m_quad.xy, a2.m_quad.xy);
	const hkSingleDouble64 m3xy = _mm_mul_pd(b3.m_quad.xy, a3.m_quad.xy);
	const hkSingleDouble64 m0zw = _mm_mul_pd(b0.m_quad.zw, a0.m_quad.zw);
	const hkSingleDouble64 m1zw = _mm_mul_pd(b1.m_quad.zw, a1.m_quad.zw);
	const hkSingleDouble64 m2zw = _mm_mul_pd(b2.m_quad.zw, a2.m_quad.zw);
	const hkSingleDouble64 m3zw = _mm_mul_pd(b3.m_quad.zw, a3.m_quad.zw);

	const hkSingleDouble64 hsum0 = _mm_hadd_pd(m0xy, m0zw);
	const hkSingleDouble64 hsum1 = _mm_hadd_pd(m1xy, m1zw);
	const hkSingleDouble64 hsum2 = _mm_hadd_pd(m2xy, m2zw);
	const hkSingleDouble64 hsum3 = _mm_hadd_pd(m3xy, m3zw);

	const hkSingleDouble64 dp0 = _mm_hadd_pd(hsum0, hsum0);
	const hkSingleDouble64 dp1 = _mm_hadd_pd(hsum1, hsum1);
	const hkSingleDouble64 dp2 = _mm_hadd_pd(hsum2, hsum2);
	const hkSingleDouble64 dp3 = _mm_hadd_pd(hsum3, hsum3);

	dotsOut.m_quad.xy = MOVE_SD(dp1,dp0);
	dotsOut.m_quad.zw = MOVE_SD(dp3,dp2);
}

#define HK_VECTOR4dUTIL_dot4_1vs4
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::dot4_1vs4( hkVector4dParameter vectorIn, hkVector4dParameter a0, hkVector4dParameter a1, hkVector4dParameter a2, hkVector4dParameter a3, hkVector4d& dotsOut)
{
	const hkSingleDouble64 m0xy = _mm_mul_pd(vectorIn.m_quad.xy, a0.m_quad.xy);
	const hkSingleDouble64 m1xy = _mm_mul_pd(vectorIn.m_quad.xy, a1.m_quad.xy);
	const hkSingleDouble64 m2xy = _mm_mul_pd(vectorIn.m_quad.xy, a2.m_quad.xy);
	const hkSingleDouble64 m3xy = _mm_mul_pd(vectorIn.m_quad.xy, a3.m_quad.xy);
	const hkSingleDouble64 m0zw = _mm_mul_pd(vectorIn.m_quad.zw, a0.m_quad.zw);
	const hkSingleDouble64 m1zw = _mm_mul_pd(vectorIn.m_quad.zw, a1.m_quad.zw);
	const hkSingleDouble64 m2zw = _mm_mul_pd(vectorIn.m_quad.zw, a2.m_quad.zw);
	const hkSingleDouble64 m3zw = _mm_mul_pd(vectorIn.m_quad.zw, a3.m_quad.zw);

	const hkSingleDouble64 hsum0 = _mm_hadd_pd(m0xy, m0zw);
	const hkSingleDouble64 hsum1 = _mm_hadd_pd(m1xy, m1zw);
	const hkSingleDouble64 hsum2 = _mm_hadd_pd(m2xy, m2zw);
	const hkSingleDouble64 hsum3 = _mm_hadd_pd(m3xy, m3zw);

	const hkSingleDouble64 dp0 = _mm_hadd_pd(hsum0, hsum0);
	const hkSingleDouble64 dp1 = _mm_hadd_pd(hsum1, hsum1);
	const hkSingleDouble64 dp2 = _mm_hadd_pd(hsum2, hsum2);
	const hkSingleDouble64 dp3 = _mm_hadd_pd(hsum3, hsum3);

	dotsOut.m_quad.xy = MOVE_SD(dp1,dp0);
	dotsOut.m_quad.zw = MOVE_SD(dp3,dp2);
}

#define HK_VECTOR4dUTIL_dot4_1vs3
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::dot4_1vs3( hkVector4dParameter vectorIn, hkVector4dParameter a0, hkVector4dParameter a1, hkVector4dParameter a2, hkVector4d& dotsOut)
{
	const hkSingleDouble64 m0xy = _mm_mul_pd(vectorIn.m_quad.xy, a0.m_quad.xy);
	const hkSingleDouble64 m1xy = _mm_mul_pd(vectorIn.m_quad.xy, a1.m_quad.xy);
	const hkSingleDouble64 m2xy = _mm_mul_pd(vectorIn.m_quad.xy, a2.m_quad.xy);

	const hkSingleDouble64 m0zw = _mm_mul_pd(vectorIn.m_quad.zw, a0.m_quad.zw);
	const hkSingleDouble64 m1zw = _mm_mul_pd(vectorIn.m_quad.zw, a1.m_quad.zw);
	const hkSingleDouble64 m2zw = _mm_mul_pd(vectorIn.m_quad.zw, a2.m_quad.zw);

	const hkSingleDouble64 hsum0 = _mm_hadd_pd(m0xy, m0zw);
	const hkSingleDouble64 hsum1 = _mm_hadd_pd(m1xy, m1zw);
	const hkSingleDouble64 hsum2 = _mm_hadd_pd(m2xy, m2zw);

	const hkSingleDouble64 dp0 = _mm_hadd_pd(hsum0, hsum0);
	const hkSingleDouble64 dp1 = _mm_hadd_pd(hsum1, hsum1);
	const hkSingleDouble64 dp2 = _mm_hadd_pd(hsum2, hsum2);

	dotsOut.m_quad.xy = MOVE_SD(dp1,dp0);
	dotsOut.m_quad.zw = dp2;
}

#endif // sse specials

#define HK_VECTOR4dUTIL_convertQuaternionToRotation
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::convertQuaternionToRotation( hkQuaterniondParameter qi, hkRotationd& rotationOut )
{
	HK_MATH_ASSERT(0x1ff88f0e, qi.isOk(), "hkQuaterniond not normalized/invalid!");

	static HK_ALIGN16( const hkUint64 negateMaskY[2]  ) = { 0x0000000000000000ull, 0x8000000000000000ull };
	static HK_ALIGN16( const hkUint64 negateMaskX[2]  ) = { 0x8000000000000000ull, 0x0000000000000000ull };
	static HK_ALIGN16( const hkUint64 negateMaskXY[2] ) = { 0x8000000000000000ull, 0x8000000000000000ull };

	const hkQuadDouble64 xyzw = qi.m_vec.m_quad;
	hkQuadDouble64 xyzw2;
	xyzw2.xy = _mm_add_pd(xyzw.xy,xyzw.xy);									// xyzw2 = x2, y2, z2, w2
	xyzw2.zw = _mm_add_pd(xyzw.zw,xyzw.zw);

	// temps
	__m128d z2z2 = _mm_unpacklo_pd(xyzw2.zw,xyzw2.zw);
	__m128d tmp1 = _mm_mul_sd(xyzw.xy,xyzw2.xy);							// tmp1 = xx2, y

	// calculate the 9 products

	hkQuadDouble64 tmp2;
	{
		__m128d yx = _mm_shuffle_pd(xyzw.xy,xyzw.xy, _MM_SHUFFLE2(0,1));
		__m128d y2y2 = _mm_unpackhi_pd(xyzw2.xy,xyzw2.xy);
		tmp2.xy = _mm_mul_pd(yx,y2y2);
		tmp2.zw = _mm_mul_pd(xyzw.xy,z2z2);									// tmp2 = yy2, xy2, xz2, yz2
	}

	hkQuadDouble64 tmp4;
	{
		__m128d ww = _mm_unpackhi_pd(xyzw.zw,xyzw.zw);
		__m128d y2x2 = _mm_shuffle_pd(xyzw2.xy,xyzw2.xy, _MM_SHUFFLE2(0,1));
		tmp4.xy = _mm_mul_pd(xyzw.zw,z2z2);
		tmp4.zw = _mm_mul_pd(ww,y2x2);										// tmp4 = zz2, wz2, wy2, wx2
	}

	// calculate the last two elements of the third row
	__m128d tmp6 = g_vectordConstants[HK_QUADREAL_1000].xy;					// tmp6 = 1, 0
	tmp6 = _mm_sub_sd( tmp6, tmp1 );										// tmp6 = -xx2+1, 0
	tmp6 = _mm_sub_sd( tmp6, tmp2.xy );										// tmp6 = -xx2-yy2+1, 0

	// calculate first row
	tmp2.xy = _mm_xor_pd( tmp2.xy, *(const __m128d*)&negateMaskY );
	tmp2.zw = _mm_xor_pd( tmp2.zw, *(const __m128d*)&negateMaskXY );			// tmp2 = yy2, -xy2, -xz2, -yz2
	tmp4.xy = _mm_xor_pd( tmp4.xy, *(const __m128d*)&negateMaskX );
	tmp4.zw = _mm_xor_pd( tmp4.zw, *(const __m128d*)&negateMaskXY );			// tmp4 = -zz2,   wz2, -wy2, -wx2
	tmp4.xy = _mm_add_sd (tmp4.xy, g_vectordConstants[HK_QUADREAL_1000].xy );// tmp4 = -zz2+1, wz2, -wy2, -wx2
	hkVector4d tmp3;
	{
		tmp3.m_quad.xy = _mm_sub_pd(tmp4.xy,tmp2.xy);
		tmp3.m_quad.zw = _mm_sub_pd(tmp4.zw,tmp2.zw);						// tmp3 = -yy2-zz2+1, xy2+wz2, xz2-wy2, yz2-wx2
	}
	rotationOut.setColumn<0>(tmp3);											// row0 = -yy2-zz2+1, xy2+wz2, xz2-wy2, yz2-wx2

	// calculate second row
	tmp2.xy = MOVE_SD( tmp2.xy, tmp1 );									// tmp2 = xx2, -xy2, -xz2, -yz2
	tmp4.xy = _mm_xor_pd( tmp4.xy, *(const __m128d*)&negateMaskY );
	tmp4.zw = _mm_xor_pd( tmp4.zw, *(const __m128d*)&negateMaskXY );			// tmp4 = -zz2+1, -wz2, wy2, wx2
	tmp4.xy = _mm_sub_pd(tmp4.xy,tmp2.xy);
	tmp4.zw = _mm_sub_pd(tmp4.zw,tmp2.zw);									// tmp4 = -xx2-zz2+1, xy2-wz2, xz2+wy2, yz2+wx2
	hkVector4d tmp5;
	{
		tmp5.m_quad.xy = _mm_shuffle_pd(tmp4.xy,tmp4.xy,_MM_SHUFFLE2(0,1));
		tmp5.m_quad.zw = _mm_shuffle_pd(tmp4.zw,tmp4.zw,_MM_SHUFFLE2(0,1));	// tmp5 = xy2-wz2, -xx2-zz2+1, yz2+wx2, xz2+wy2
	}
	rotationOut.setColumn<1>(tmp5);											// row1 = xy2-wz2, -xx2-zz2+1, yz2+wx2, xz2+wy2

	// calculate third row
	{
		tmp3.m_quad.xy = _mm_unpackhi_pd(tmp5.m_quad.zw,tmp3.m_quad.zw);
		tmp3.m_quad.zw = tmp6;												// tmp3 = xz2+wy2, yz2-wx2, -xx2-yy2+1, 0
	}
	rotationOut.setColumn<2>(tmp3);											// row2 = xz2+wy2, yz2-wx2, -xx2-yy2+1, 0
}

#define HK_VECTOR4dUTIL_convertComparison
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::convertComparison(hkVector4dComparisonParameter cin, hkVector4fComparison& cout)
{
	__m128i xzxz = _mm_unpacklo_epi32(_mm_castpd_si128(cin.m_mask.xy),_mm_castpd_si128(cin.m_mask.zw));
	__m128i ywyw = _mm_unpackhi_epi32(_mm_castpd_si128(cin.m_mask.xy),_mm_castpd_si128(cin.m_mask.zw));
	cout.m_mask = _mm_castsi128_ps(_mm_unpacklo_epi32(xzxz,ywyw));
}
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::convertComparison(hkVector4dComparisonParameter cin, hkVector4dComparison& cout)
{
	cout.m_mask.xy = cin.m_mask.xy;
	cout.m_mask.zw = cin.m_mask.zw;
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
