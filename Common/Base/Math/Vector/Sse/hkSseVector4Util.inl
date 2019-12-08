/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#define HK_VECTOR4UTIL_exitMmx
template <typename FT>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<FT>::exitMmx()
{
#	ifndef HK_ARCH_X64
	_mm_empty();
#	endif
}

#define HK_VECTOR4fUTIL_atan2Approximation
template <>
HK_FORCE_INLINE hkSimdFloat32 HK_CALL hkVector4UtilImpl<hkFloat32>::atan2Approximation(hkSimdFloat32Parameter y, hkSimdFloat32Parameter x)
{
	hkSimdFloat32 result;
	result.m_real = hkMath::quadAtan2(y.m_real,x.m_real);
	return result;
}
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::atan2Approximation(hkVector4fParameter y, hkVector4fParameter x, hkVector4f& result)
{
	result.m_quad = hkMath::quadAtan2(y.m_quad, x.m_quad);
}

#define HK_VECTOR4fUTIL_logApproximation
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::logApproximation(hkVector4fParameter v, hkVector4f& result)
{
	result.m_quad = hkMath::quadLog(v.m_quad);
}

#define HK_VECTOR4fUTIL_sinCos
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::sinCos(hkVector4fParameter r, hkVector4f& sc)
{
	sc.m_quad = hkMath::quadSinCos(r.m_quad);
}
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::sinCos(hkSimdFloat32Parameter r, hkVector4f& sc)
{
	hkVector4f rr; rr.setAll(r);
	sc.m_quad = hkMath::quadSinCos(rr.m_quad);
}
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::sinCos(hkSimdFloat32Parameter r, hkSimdFloat32& s, hkSimdFloat32& c)
{
	hkVector4f rr; rr.setAll(r);
	hkVector4f sc; sc.m_quad = hkMath::quadSinCos(rr.m_quad);
	s = sc.getComponent<0>();
	c = sc.getComponent<1>();
}

#define HK_VECTOR4fUTIL_sinCosApproximation
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::sinCosApproximation(hkVector4fParameter r, hkVector4f& sc)
{
	sc.m_quad = hkMath::quadSinCosApproximation(r.m_quad);
}
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::sinCosApproximation(hkSimdFloat32Parameter r, hkVector4f& sc)
{
	hkVector4f rr; rr.setAll(r);
	sc.m_quad = hkMath::quadSinCosApproximation(rr.m_quad);
}
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::sinCosApproximation(hkSimdFloat32Parameter r, hkSimdFloat32& s, hkSimdFloat32& c)
{
	hkVector4f rr; rr.setAll(r);
	hkVector4f sc; sc.m_quad = hkMath::quadSinCosApproximation(rr.m_quad);
	s = sc.getComponent<0>();
	c = sc.getComponent<1>();
}

#define HK_VECTOR4fUTIL_aSinAcos
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::aSin(hkVector4fParameter r, hkVector4f& sc)
{
	sc.m_quad = hkMath::quadAsin(r.m_quad);
}
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::aCos(hkVector4fParameter r, hkVector4f& sc)
{
	sc.m_quad = hkMath::quadAcos(r.m_quad);
}
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::aSinAcos(hkVector4fParameter r, hkVector4f& sc)
{
	sc.m_quad = hkMath::quadAsinAcos(r.m_quad);
}
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::aSinAcos(hkSimdFloat32Parameter r, hkVector4f& sc)
{
	hkVector4f rr; rr.setAll(r);
	sc.m_quad = hkMath::quadAsinAcos(rr.m_quad);
}
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::aSinAcos(hkSimdFloat32Parameter r, hkSimdFloat32& s, hkSimdFloat32& c)
{
	hkVector4f rr; rr.setAll(r);
	hkVector4f sc; sc.m_quad = hkMath::quadAsinAcos(rr.m_quad);
	s = sc.getComponent<0>();
	c = sc.getComponent<1>();
}

#if HK_SSE_VERSION >= 0x41
// yep, we have a dot product instruction

#define HK_VECTOR4fUTIL_rotateInversePoints
template <>
HK_FORCE_INLINE void	HK_CALL hkVector4UtilImpl<hkFloat32>::rotateInversePoints( const hkRotationf& r, const hkVector4f* vectorsIn, int numVectors, hkVector4f* vectorsOut )
{
	HK_MATH_ASSERT( 0xf0200104, numVectors > 0, "At least one vector to rotate required");

	const hkQuadFloat32 c0 = r.getColumn<0>().m_quad;
	const hkQuadFloat32 c1 = r.getColumn<1>().m_quad;
	const hkQuadFloat32 c2 = r.getColumn<2>().m_quad;
	for( int i = 0; i < numVectors; ++i )
	{
		const hkQuadFloat32 b = vectorsIn[i].m_quad;
		const hkQuadFloat32 r0 = _mm_dp_ps( c0, b, 0x71 );
		const hkQuadFloat32 r1 = _mm_dp_ps( c1, b, 0x72 );
		const hkQuadFloat32 r2 = _mm_dp_ps( c2, b, 0x74 );

		vectorsOut[i].m_quad = _mm_or_ps( _mm_or_ps(r0, r1), r2 );
	}
}

#define HK_VECTOR4fUTIL_dot3_3vs3
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::dot3_3vs3(hkVector4fParameter a0, hkVector4fParameter b0, hkVector4fParameter a1, hkVector4fParameter b1, hkVector4fParameter a2, hkVector4fParameter b2, hkVector4f& dotsOut)
{
	const hkQuadFloat32 dp0 = _mm_dp_ps(a0.m_quad, b0.m_quad, 0x71);
	const hkQuadFloat32 dp1 = _mm_dp_ps(a1.m_quad, b1.m_quad, 0x72);
	const hkQuadFloat32 dp2 = _mm_dp_ps(a2.m_quad, b2.m_quad, 0x74);
	dotsOut.m_quad = _mm_or_ps(_mm_or_ps(dp0,dp1), dp2);
}

#define HK_VECTOR4fUTIL_dot3_4vs4
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::dot3_4vs4(hkVector4fParameter a0, hkVector4fParameter b0, hkVector4fParameter a1, hkVector4fParameter b1, hkVector4fParameter a2, hkVector4fParameter b2, hkVector4fParameter a3, hkVector4fParameter b3, hkVector4f& dotsOut)
{
	const hkQuadFloat32 dp0 = _mm_dp_ps(a0.m_quad, b0.m_quad, 0x71);
	const hkQuadFloat32 dp1 = _mm_dp_ps(a1.m_quad, b1.m_quad, 0x72);
	const hkQuadFloat32 dp2 = _mm_dp_ps(a2.m_quad, b2.m_quad, 0x74);
	const hkQuadFloat32 dp3 = _mm_dp_ps(a3.m_quad, b3.m_quad, 0x78);
	dotsOut.m_quad = _mm_or_ps(_mm_or_ps(dp0, dp1), _mm_or_ps(dp2, dp3));
}

#define HK_VECTOR4fUTIL_dot4_4vs4
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::dot4_4vs4( hkVector4fParameter a0, hkVector4fParameter b0, hkVector4fParameter a1, hkVector4fParameter b1, hkVector4fParameter a2, hkVector4fParameter b2, hkVector4fParameter a3, hkVector4fParameter b3, hkVector4f& dotsOut)
{
	const hkQuadFloat32 dp0 = _mm_dp_ps(a0.m_quad, b0.m_quad, 0xF1);
	const hkQuadFloat32 dp1 = _mm_dp_ps(a1.m_quad, b1.m_quad, 0xF2);
	const hkQuadFloat32 dp2 = _mm_dp_ps(a2.m_quad, b2.m_quad, 0xF4);
	const hkQuadFloat32 dp3 = _mm_dp_ps(a3.m_quad, b3.m_quad, 0xF8);
	dotsOut.m_quad = _mm_or_ps(_mm_or_ps(dp0, dp1), _mm_or_ps(dp2, dp3));
}

#define HK_VECTOR4fUTIL_dot3_1vs4
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::dot3_1vs4( hkVector4fParameter v, hkVector4fParameter a0, hkVector4fParameter a1, hkVector4fParameter a2, hkVector4fParameter a3, hkVector4f& dotsOut)
{
	const hkQuadFloat32 dp0 = _mm_dp_ps(v.m_quad, a0.m_quad, 0x71);
	const hkQuadFloat32 dp1 = _mm_dp_ps(v.m_quad, a1.m_quad, 0x72);
	const hkQuadFloat32 dp2 = _mm_dp_ps(v.m_quad, a2.m_quad, 0x74);
	const hkQuadFloat32 dp3 = _mm_dp_ps(v.m_quad, a3.m_quad, 0x78);
	dotsOut.m_quad = _mm_or_ps(_mm_or_ps(dp0, dp1), _mm_or_ps(dp2, dp3));
}

#define HK_VECTOR4fUTIL_dot3_1vs3
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::dot3_1vs3( hkVector4fParameter v, hkVector4fParameter a0, hkVector4fParameter a1, hkVector4fParameter a2, hkVector4f& dotsOut)
{
	const hkQuadFloat32 dp0 = _mm_dp_ps(v.m_quad, a0.m_quad, 0x71);
	const hkQuadFloat32 dp1 = _mm_dp_ps(v.m_quad, a1.m_quad, 0x72);
	const hkQuadFloat32 dp2 = _mm_dp_ps(v.m_quad, a2.m_quad, 0x74);
	dotsOut.m_quad = _mm_or_ps(_mm_or_ps(dp0, dp1), dp2);
}

//
//	Sets this vector components: this(i) = vector.dot<4>(AI) for i=0..3

#define HK_VECTOR4fUTIL_dot4_1vs4
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::dot4_1vs4( hkVector4fParameter vectorIn, hkVector4fParameter a0, hkVector4fParameter a1, hkVector4fParameter a2, hkVector4fParameter a3, hkVector4f& dotsOut)
{
	const hkQuadFloat32 dp0 = _mm_dp_ps(vectorIn.m_quad, a0.m_quad, 0xF1);
	const hkQuadFloat32 dp1 = _mm_dp_ps(vectorIn.m_quad, a1.m_quad, 0xF2);
	const hkQuadFloat32 dp2 = _mm_dp_ps(vectorIn.m_quad, a2.m_quad, 0xF4);
	const hkQuadFloat32 dp3 = _mm_dp_ps(vectorIn.m_quad, a3.m_quad, 0xF8);

	dotsOut.m_quad = _mm_or_ps(_mm_or_ps(dp0, dp1), _mm_or_ps(dp2, dp3));
}

//
//	Sets this vector components: this(i) = vector.dot<4>(AI) for i=0..2

#define HK_VECTOR4fUTIL_dot4_1vs3
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::dot4_1vs3( hkVector4fParameter vectorIn, hkVector4fParameter a0, hkVector4fParameter a1, hkVector4fParameter a2, hkVector4f& dotsOut)
{
	const hkQuadFloat32 dp0 = _mm_dp_ps(vectorIn.m_quad, a0.m_quad, 0xF1);
	const hkQuadFloat32 dp1 = _mm_dp_ps(vectorIn.m_quad, a1.m_quad, 0xF2);
	const hkQuadFloat32 dp2 = _mm_dp_ps(vectorIn.m_quad, a2.m_quad, 0xF4);

	dotsOut.m_quad = _mm_or_ps(_mm_or_ps(dp0, dp1), dp2);
}

#define HK_VECTOR4fUTIL_dot3_2vs2
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::dot3_2vs2( hkVector4fParameter a0, hkVector4fParameter a2, hkVector4fParameter b0, hkVector4fParameter b1, hkVector4f& dotsOut)
{
	const hkQuadFloat32 dp00 = _mm_dp_ps(a0.m_quad, b0.m_quad, 0x71);
	const hkQuadFloat32 dp01 = _mm_dp_ps(a0.m_quad, b1.m_quad, 0x72);
	const hkQuadFloat32 dp20 = _mm_dp_ps(a2.m_quad, b0.m_quad, 0x74);
	const hkQuadFloat32 dp21 = _mm_dp_ps(a2.m_quad, b1.m_quad, 0x78);
	dotsOut.m_quad = _mm_or_ps(_mm_or_ps(dp00, dp01), _mm_or_ps(dp20, dp21));
}

#elif HK_SSE_VERSION >= 0x30

#define HK_VECTOR4fUTIL_dot4_4vs4
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::dot4_4vs4( hkVector4fParameter a0, hkVector4fParameter b0, hkVector4fParameter a1, hkVector4fParameter b1, hkVector4fParameter a2, hkVector4fParameter b2, hkVector4fParameter a3, hkVector4fParameter b3, hkVector4f& dotsOut)
{
	const hkQuadFloat32 m0 = _mm_mul_ps(b0.m_quad, a0.m_quad);
	const hkQuadFloat32 m1 = _mm_mul_ps(b1.m_quad, a1.m_quad);
	const hkQuadFloat32 m2 = _mm_mul_ps(b2.m_quad, a2.m_quad);
	const hkQuadFloat32 m3 = _mm_mul_ps(b3.m_quad, a3.m_quad);

	const hkQuadFloat32 hsum0 = _mm_hadd_ps(m0, m0);
	const hkQuadFloat32 hsum1 = _mm_hadd_ps(m1, m1);
	const hkQuadFloat32 hsum2 = _mm_hadd_ps(m2, m2);
	const hkQuadFloat32 hsum3 = _mm_hadd_ps(m3, m3);

	const hkQuadFloat32 dp0 = _mm_hadd_ps(hsum0, hsum0);
	const hkQuadFloat32 dp1 = _mm_hadd_ps(hsum1, hsum1);
	const hkQuadFloat32 dp2 = _mm_hadd_ps(hsum2, hsum2);
	const hkQuadFloat32 dp3 = _mm_hadd_ps(hsum3, hsum3);

	const hkQuadFloat32 zero = _mm_setzero_ps();

	const hkQuadFloat32 dp0z = _mm_shuffle_ps(dp0,zero,_MM_SHUFFLE(0,0,0,0));
	const hkQuadFloat32 dp1z = _mm_shuffle_ps(dp1,zero,_MM_SHUFFLE(1,1,0,0));
	const hkQuadFloat32 dp2z = _mm_shuffle_ps(dp2,zero,_MM_SHUFFLE(2,2,0,0));
	const hkQuadFloat32 dp3z = _mm_shuffle_ps(dp3,zero,_MM_SHUFFLE(3,3,0,0));

	dotsOut.m_quad =                           _mm_shuffle_ps(dp0z,dp2z,_MM_SHUFFLE(3,0,3,0));
	dotsOut.m_quad = _mm_or_ps(dotsOut.m_quad, _mm_shuffle_ps(dp1z,dp3z,_MM_SHUFFLE(0,3,0,3)));
}

#define HK_VECTOR4fUTIL_dot4_1vs4
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::dot4_1vs4( hkVector4fParameter vectorIn, hkVector4fParameter a0, hkVector4fParameter a1, hkVector4fParameter a2, hkVector4fParameter a3, hkVector4f& dotsOut)
{
	const hkQuadFloat32 m0 = _mm_mul_ps(vectorIn.m_quad, a0.m_quad);
	const hkQuadFloat32 m1 = _mm_mul_ps(vectorIn.m_quad, a1.m_quad);
	const hkQuadFloat32 m2 = _mm_mul_ps(vectorIn.m_quad, a2.m_quad);
	const hkQuadFloat32 m3 = _mm_mul_ps(vectorIn.m_quad, a3.m_quad);

	const hkQuadFloat32 hsum0 = _mm_hadd_ps(m0, m0);
	const hkQuadFloat32 hsum1 = _mm_hadd_ps(m1, m1);
	const hkQuadFloat32 hsum2 = _mm_hadd_ps(m2, m2);
	const hkQuadFloat32 hsum3 = _mm_hadd_ps(m3, m3);

	const hkQuadFloat32 dp0 = _mm_hadd_ps(hsum0, hsum0);
	const hkQuadFloat32 dp1 = _mm_hadd_ps(hsum1, hsum1);
	const hkQuadFloat32 dp2 = _mm_hadd_ps(hsum2, hsum2);
	const hkQuadFloat32 dp3 = _mm_hadd_ps(hsum3, hsum3);

	const hkQuadFloat32 zero = _mm_setzero_ps();

	const hkQuadFloat32 dp0z = _mm_shuffle_ps(dp0,zero,_MM_SHUFFLE(0,0,0,0));
	const hkQuadFloat32 dp1z = _mm_shuffle_ps(dp1,zero,_MM_SHUFFLE(1,1,0,0));
	const hkQuadFloat32 dp2z = _mm_shuffle_ps(dp2,zero,_MM_SHUFFLE(2,2,0,0));
	const hkQuadFloat32 dp3z = _mm_shuffle_ps(dp3,zero,_MM_SHUFFLE(3,3,0,0));

	dotsOut.m_quad =                           _mm_shuffle_ps(dp0z,dp2z,_MM_SHUFFLE(3,0,3,0));
	dotsOut.m_quad = _mm_or_ps(dotsOut.m_quad, _mm_shuffle_ps(dp1z,dp3z,_MM_SHUFFLE(0,3,0,3)));
}

#define HK_VECTOR4fUTIL_dot4_1vs3
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::dot4_1vs3( hkVector4fParameter vectorIn, hkVector4fParameter a0, hkVector4fParameter a1, hkVector4fParameter a2, hkVector4f& dotsOut)
{
	const hkQuadFloat32 m0 = _mm_mul_ps(vectorIn.m_quad, a0.m_quad);
	const hkQuadFloat32 m1 = _mm_mul_ps(vectorIn.m_quad, a1.m_quad);
	const hkQuadFloat32 m2 = _mm_mul_ps(vectorIn.m_quad, a2.m_quad);

	const hkQuadFloat32 hsum0 = _mm_hadd_ps(m0, m0);
	const hkQuadFloat32 hsum1 = _mm_hadd_ps(m1, m1);
	const hkQuadFloat32 hsum2 = _mm_hadd_ps(m2, m2);

	const hkQuadFloat32 dp0 = _mm_hadd_ps(hsum0, hsum0);
	const hkQuadFloat32 dp1 = _mm_hadd_ps(hsum1, hsum1);
	const hkQuadFloat32 dp2 = _mm_hadd_ps(hsum2, hsum2);

	const hkQuadFloat32 zero = _mm_setzero_ps();

	const hkQuadFloat32 dp0z = _mm_shuffle_ps(dp0,zero,_MM_SHUFFLE(0,0,0,0));
	const hkQuadFloat32 dp1z = _mm_shuffle_ps(dp1,zero,_MM_SHUFFLE(1,1,0,0));
	const hkQuadFloat32 dp2z = _mm_shuffle_ps(dp2,zero,_MM_SHUFFLE(2,2,0,0));

	dotsOut.m_quad =                           _mm_shuffle_ps(dp0z,dp2z,_MM_SHUFFLE(3,0,3,0));
	dotsOut.m_quad = _mm_or_ps(dotsOut.m_quad, _mm_shuffle_ps(dp1z,zero,_MM_SHUFFLE(0,3,0,3)));
}

#endif // sse specials



#define HK_VECTOR4fUTIL_convertQuaternionToRotation
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::convertQuaternionToRotation( hkQuaternionfParameter qi, hkRotationf& rotationOut )
{
	HK_MATH_ASSERT(0x1ff88f0e, qi.isOk(), "hkQuaternionf not normalized/invalid!");

	static HK_ALIGN16( const hkUint32 negateMask0[4] ) = { 0x00000000, 0x80000000, 0x80000000, 0x80000000 };
	static HK_ALIGN16( const hkUint32 negateMask1[4] ) = { 0x80000000, 0x00000000, 0x80000000, 0x80000000 };

	const hkQuadFloat32 xyzw = qi.m_vec.m_quad;
	const hkQuadFloat32 xyzw2 = _mm_add_ps(xyzw,xyzw);							// xyzw2 = x2, y2, z2, w2

	// calculate the 9 products

	hkQuadFloat32 tmp2 = _mm_shuffle_ps(xyzw, xyzw, _MM_SHUFFLE(1,0,0,1));		// tmp2 = y, x, x, y
	hkQuadFloat32 tmp3 = _mm_shuffle_ps(xyzw2, xyzw2, _MM_SHUFFLE(2,2,1,1) );	// tmp3 = y2, y2, z2, z2
	tmp2 = _mm_mul_ps(tmp2,tmp3);											// tmp2 = yy2, xy2, xz2, yz2

	hkQuadFloat32 tmp4 = _mm_shuffle_ps(xyzw, xyzw, _MM_SHUFFLE(3,3,3,2) );	// tmp4 = z, w, w, w
	hkQuadFloat32 tmp5 = _mm_shuffle_ps(xyzw2, xyzw2, _MM_SHUFFLE(0,1,2,2) );	// tmp5 = z2, z2, y2, x2
	tmp4 = _mm_mul_ps(tmp4,tmp5);											// tmp4 = zz2, wz2, wy2, wx2

	hkQuadFloat32 tmp1 = _mm_mul_ss( xyzw, xyzw2 );							// tmp1 = xx2, y, z, w

	// calculate the last two elements of the third row
	hkQuadFloat32 tmp6 = g_vectorfConstants[HK_QUADREAL_1000];					// tmp6 = 1, 0, 0, 0
	tmp6 = _mm_sub_ss( tmp6, tmp1 );										// tmp6 = -xx2+1, 0, 0, 0
	tmp6 = _mm_sub_ss( tmp6, tmp2 );										// tmp6 = -xx2-yy2+1, 0, 0, 0

	// calculate first row
	tmp2 = _mm_xor_ps ( tmp2, *(const hkQuadFloat32*)&negateMask0 );			// tmp2 = yy2, -xy2, -xz2, -yz2
	tmp4 = _mm_xor_ps ( tmp4, *(const hkQuadFloat32*)&negateMask1 );			// tmp4 = -zz2, wz2, -wy2, -wx2
	tmp4 = _mm_add_ss ( tmp4, g_vectorfConstants[HK_QUADREAL_1000]); 		// tmp4 = -zz2+1, wz2, -wy2, -wx2
	tmp3 = _mm_sub_ps(tmp4,tmp2);											// tmp3 = -yy2-zz2+1, xy2+wz2, xz2-wy2, yz2-wx2
	rotationOut.setColumn<0>((const hkVector4f&)tmp3);						// row0 = -yy2-zz2+1, xy2+wz2, xz2-wy2, yz2-wx2

	// calculate second row
	tmp2 = _mm_move_ss( tmp2, tmp1 );										// tmp2 = xx2, -xy2, -xz2, -yz2
	tmp4 = _mm_xor_ps ( tmp4, *(const hkQuadFloat32*)&negateMask0 );			// tmp4 = -zz2+1, -wz2, wy2, wx2
	tmp4 = _mm_sub_ps(tmp4,tmp2);											// tmp4 = -xx2-zz2+1, xy2-wz2, xz2+wy2, yz2+wx2
	tmp4 = _mm_shuffle_ps(tmp4, tmp4, _MM_SHUFFLE(2,3,0,1) );
	rotationOut.setColumn<1>((const hkVector4f&)tmp4);						// row1 = xy2-wz2, -xx2-zz2+1, yz2+wx2, xz2+wy2

	// calculate third row
	tmp3 = _mm_movehl_ps( tmp3, tmp4 );										// tmp3 = yz2+wx2, xz2+wy2, xz2-wy2, yz2-wx2
	tmp3 = _mm_shuffle_ps(tmp3,tmp6, _MM_SHUFFLE(2,0,3,1) );				// tmp3 = xz2+wy2, yz2-wx2, -xx2-yy2+1, 0
	rotationOut.setColumn<2>((const hkVector4f&)tmp3);						// row2 = xz2+wy2, yz2-wx2, -xx2-yy2+1, 0
}

#define HK_VECTOR4fUTIL_setPermutation2
template <typename FT>
template<unsigned int i, unsigned int j, unsigned int k, unsigned int l>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<FT>::setPermutation2(hkVector4fParameter a, hkVector4fParameter b, hkVector4f & out)
{
	HK_COMPILE_TIME_ASSERT(i<8 && j<8 && k<8 && l<8);
	HK_COMPILE_TIME_ASSERT(i>=0 && j>=0 && k>=0 && l>=0);

	hkQuadFloat32 tmp1 = _mm_shuffle_ps(a.m_quad, b.m_quad, _MM_SHUFFLE(j&3, i&3, j&3, i&3));
	hkQuadFloat32 tmp2 = _mm_shuffle_ps(a.m_quad, b.m_quad, _MM_SHUFFLE(l&3, k&3, l&3, k&3));

	out.m_quad = _mm_shuffle_ps(tmp1, tmp2, _MM_SHUFFLE((l&4)?3:1, (k&4)?2:0, (j&4)?3:1, (i&4)?2:0));
}

#define HK_VECTOR4fUTIL_convertComparison
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::convertComparison(hkVector4fComparisonParameter cin, hkVector4dComparison& cout)
{
	cout.m_mask.xy = _mm_castps_pd(_mm_shuffle_ps( cin.m_mask, cin.m_mask, _MM_SHUFFLE(1,1,0,0) ));
	cout.m_mask.zw = _mm_castps_pd(_mm_shuffle_ps( cin.m_mask, cin.m_mask, _MM_SHUFFLE(3,3,2,2) ));
}
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::convertComparison(hkVector4fComparisonParameter cin, hkVector4fComparison& cout)
{
	cout.m_mask = cin.m_mask;
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
