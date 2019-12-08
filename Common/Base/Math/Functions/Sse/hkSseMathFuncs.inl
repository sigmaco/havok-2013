/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#include <Common/Base/Fwd/hkcmath.h>

#define HK_STD_NAMESPACE /*nothing*/

namespace hkMath
{
	//
	// need to implement
	//
#	define HK_MATH_quadReciprocal
	HK_FORCE_INLINE static hkQuadFloat32 HK_CALL quadReciprocal( const hkQuadFloat32& r )
	{
		const hkQuadFloat32 rb = _mm_rcp_ps(r);
		// One Newton-Raphson refinement iteration
		const hkQuadFloat32 rbr = _mm_mul_ps(r, rb);
		const hkQuadFloat32 d = _mm_sub_ps(_mm_set1_ps(2.0f), rbr);
		return _mm_mul_ps(rb, d);
	}

	HK_FORCE_INLINE static hkQuadDouble64 HK_CALL quadReciprocal( const hkQuadDouble64& r )
	{
#if HK_SSE_VERSION >= 0x50
		return _mm256_div_pd(_mm256_set1_pd(1.0), r);
#else
		const __m128 xy = _mm_cvtpd_ps(r.xy);
		const __m128 zw = _mm_cvtpd_ps(r.zw);
		const __m128 xyzw = _mm_shuffle_ps(xy,zw,_MM_SHUFFLE(1,0,1,0));
		const __m128 rb = _mm_rcp_ps(xyzw);
		// One Newton-Raphson refinement iteration
		const __m128 rbr = _mm_mul_ps(xyzw, rb);
		const __m128 d = _mm_sub_ps(_mm_set1_ps(2.0f), rbr);
		const __m128 re = _mm_mul_ps(rb, d);
		hkQuadDouble64 result;
		result.xy = _mm_cvtps_pd(re);
		result.zw = _mm_cvtps_pd(_mm_shuffle_ps(re,re,_MM_SHUFFLE(1,0,3,2)));
		return result;
#endif
	}

#	define HK_MATH_quadReciprocalSquareRoot
	HK_FORCE_INLINE static hkQuadFloat32 HK_CALL quadReciprocalSquareRoot( const hkQuadFloat32& r )
	{
		const hkQuadFloat32 e = _mm_rsqrt_ps(r);
		// One Newton-Raphson refinement iteration
		const hkQuadFloat32 he = _mm_mul_ps(_mm_set1_ps(0.5f),e);
		const hkQuadFloat32 ree = _mm_mul_ps(_mm_mul_ps(r,e),e);
		return _mm_mul_ps(he, _mm_sub_ps(_mm_set1_ps(3.0f), ree) );
	}

	HK_FORCE_INLINE static hkQuadDouble64 HK_CALL quadReciprocalSquareRoot( const hkQuadDouble64& r )
	{
#if HK_SSE_VERSION >= 0x50
		return _mm256_div_pd(_mm256_set1_pd(1.0), _mm256_sqrt_pd(r));
#else
		const __m128 xy = _mm_cvtpd_ps(r.xy);
		const __m128 zw = _mm_cvtpd_ps(r.zw);
		const __m128 xyzw = _mm_shuffle_ps(xy,zw,_MM_SHUFFLE(1,0,1,0));
		const __m128 e = _mm_rsqrt_ps(xyzw);
		// One Newton-Raphson refinement iteration
		const __m128 he = _mm_mul_ps(_mm_set1_ps(0.5f),e);
		const __m128 ree = _mm_mul_ps(_mm_mul_ps(xyzw,e),e);
		const __m128 re = _mm_mul_ps(he, _mm_sub_ps(_mm_set1_ps(3.0f), ree) );
		hkQuadDouble64 result;
		result.xy = _mm_cvtps_pd(re);
		result.zw = _mm_cvtps_pd(_mm_shuffle_ps(re,re,_MM_SHUFFLE(1,0,3,2)));
		return result;
#endif
	}

#	define HK_MATH_quadReciprocalTwoIter
	HK_FORCE_INLINE static hkQuadFloat32 HK_CALL quadReciprocalTwoIter( const hkQuadFloat32& r )
	{
		const __m128 two = _mm_set1_ps(2.0f);
		const hkQuadFloat32 rb = _mm_rcp_ps(r);
		//One round of Newton-Raphson refinement
		const hkQuadFloat32 rbr = _mm_mul_ps(r, rb);
		const hkQuadFloat32 d = _mm_sub_ps(two, rbr);
		const hkQuadFloat32 rb1 = _mm_mul_ps(rb, d);
		//Another round
		const hkQuadFloat32 rbr2 = _mm_mul_ps(r, rb1);
		const hkQuadFloat32 d2 = _mm_sub_ps(two, rbr2);
		return _mm_mul_ps(rb1, d2);
	}

	HK_FORCE_INLINE static hkQuadDouble64 HK_CALL quadReciprocalTwoIter( const hkQuadDouble64& r )
	{
#if HK_SSE_VERSION >= 0x50
		return _mm256_div_pd(_mm256_set1_pd(1.0), r);
#else
		const __m128 two = _mm_set1_ps(2.0f);
		const __m128 xy = _mm_cvtpd_ps(r.xy);
		const __m128 zw = _mm_cvtpd_ps(r.zw);
		const __m128 xyzw = _mm_shuffle_ps(xy,zw,_MM_SHUFFLE(1,0,1,0));
		const __m128 rb = _mm_rcp_ps(xyzw);
		//One round of Newton-Raphson refinement
		const __m128 rbr = _mm_mul_ps(xyzw, rb);
		const __m128 d = _mm_sub_ps(two, rbr);
		const __m128 rb1 = _mm_mul_ps(rb, d);
		//Another round
		const __m128 rbr2 = _mm_mul_ps(xyzw, rb1);
		const __m128 d2 = _mm_sub_ps(two, rbr2);
		const __m128 re = _mm_mul_ps(rb1, d2);
		hkQuadDouble64 result;
		result.xy = _mm_cvtps_pd(re);
		result.zw = _mm_cvtps_pd(_mm_shuffle_ps(re,re,_MM_SHUFFLE(1,0,3,2)));
		return result;
#endif
	}

#	define HK_MATH_quadReciprocalSquareRootTwoIter
	HK_FORCE_INLINE static hkQuadFloat32 HK_CALL quadReciprocalSquareRootTwoIter( const hkQuadFloat32& r )
	{
		const __m128 half = _mm_set1_ps(0.5f);
		const __m128 three = _mm_set1_ps(3.0f);
		const hkQuadFloat32 e = _mm_rsqrt_ps(r);
		// One Newton-Raphson refinement iteration
		const hkQuadFloat32 he = _mm_mul_ps(half,e);
		const hkQuadFloat32 ree = _mm_mul_ps(_mm_mul_ps(r,e),e);
		const hkQuadFloat32 e1 = _mm_mul_ps(he, _mm_sub_ps(three, ree) );
		//Another round
		const hkQuadFloat32 he2 = _mm_mul_ps(half,e1);
		const hkQuadFloat32 ree2 = _mm_mul_ps(_mm_mul_ps(r,e1),e1);
		return _mm_mul_ps(he2, _mm_sub_ps(three, ree2) );
	}

	HK_FORCE_INLINE static hkQuadDouble64 HK_CALL quadReciprocalSquareRootTwoIter( const hkQuadDouble64& r )
	{
#if HK_SSE_VERSION >= 0x50
		return _mm256_div_pd(_mm256_set1_pd(1.0), _mm256_sqrt_pd(r));
#else
		const __m128 half = _mm_set1_ps(0.5f);
		const __m128 three = _mm_set1_ps(3.0f);
		const __m128 xy = _mm_cvtpd_ps(r.xy);
		const __m128 zw = _mm_cvtpd_ps(r.zw);
		const __m128 xyzw = _mm_shuffle_ps(xy,zw,_MM_SHUFFLE(1,0,1,0));
		const __m128 e = _mm_rsqrt_ps(xyzw);
		// One Newton-Raphson refinement iteration
		const __m128 he = _mm_mul_ps(half,e);
		const __m128 ree = _mm_mul_ps(_mm_mul_ps(xyzw,e),e);
		const __m128 e1 = _mm_mul_ps(he, _mm_sub_ps(three, ree) );
		//Another round
		const __m128 he2 = _mm_mul_ps(half,e1);
		const __m128 ree2 = _mm_mul_ps(_mm_mul_ps(xyzw,e1),e1);
		const __m128 re = _mm_mul_ps(he2, _mm_sub_ps(three, ree2) );
		hkQuadDouble64 result;
		result.xy = _mm_cvtps_pd(re);
		result.zw = _mm_cvtps_pd(_mm_shuffle_ps(re,re,_MM_SHUFFLE(1,0,3,2)));
		return result;
#endif
	}

	// 
	// SSE optimized implementations
	//

#	define HK_MATH_sqrt
	HK_FORCE_INLINE static hkFloat32 HK_CALL sqrt(const hkFloat32 r) 
	{ 
		const __m128 s = _mm_sqrt_ss(_mm_load_ss(&r));
		return _mm_cvtss_f32(s);
	}
	HK_FORCE_INLINE static hkDouble64 HK_CALL sqrt(const hkDouble64 r) 
	{ 
		const __m128d s = _mm_sqrt_sd(_mm_setzero_pd(),_mm_load_sd(&r));
		return HK_M128(s).m128d_f64[0];
	}

#	define HK_MATH_sqrtInverse
	HK_FORCE_INLINE static hkFloat32 HK_CALL sqrtInverse(const hkFloat32 r) 
	{ 
		static HK_ALIGN16(const int one[4])	= {  0x3F800000,  0x3F800000,  0x3F800000,  0x3F800000 }; // 1.0
		const __m128 s = _mm_sqrt_ss(_mm_load_ss(&r));
		return _mm_cvtss_f32(_mm_div_ss(*(__m128*)one,s));
	}
	HK_FORCE_INLINE static hkDouble64 HK_CALL sqrtInverse(const hkDouble64 r) 
	{ 
		static HK_ALIGN16( const hkUint64 one[2] )  = { 0x3ff0000000000000ull, 0x3ff0000000000000ull }; // 1.0
		const __m128d s = _mm_sqrt_sd(_mm_setzero_pd(),_mm_load_sd(&r));
		const __m128d q = _mm_div_sd(*(__m128d*)one,s);
		return HK_M128(q).m128d_f64[0];
	}

	namespace 
	{
		HK_FORCE_INLINE static void HK_CALL quadLogHelper(__m128& x)
		{
			static HK_ALIGN16(const unsigned int minNormalizedPosNumber[4])	= {  0x00800000,  0x00800000,  0x00800000,  0x00800000 }; // 1.1754943508222875E-38 (smallest normalized positive number)
			static HK_ALIGN16(const unsigned int one[4])					= {  0x3F800000,  0x3F800000,  0x3F800000,  0x3F800000 }; // 1.0
			static HK_ALIGN16(const			 int invMantissaMask[4])		= { ~0x7f800000, ~0x7f800000, ~0x7f800000, ~0x7f800000 };
			static HK_ALIGN16(const unsigned int int0x7f[4])				= {  0x0000007f,  0x0000007f,  0x0000007f,  0x0000007f };
			static HK_ALIGN16(const unsigned int logP0[4])					= {  0xBF4A21EF,  0xBF4A21EF,  0xBF4A21EF,  0xBF4A21EF }; // -7.89580278884799154124e-1
			static HK_ALIGN16(const unsigned int logQ0[4])					= {  0xC20EB06A,  0xC20EB06A,  0xC20EB06A,  0xC20EB06A }; // -3.56722798256324312549e1
			static HK_ALIGN16(const unsigned int logP1[4])					= {  0x418317E4,  0x418317E4,  0x418317E4,  0x418317E4 }; // 1.63866645699558079767e1
			static HK_ALIGN16(const unsigned int logQ1[4])					= {  0x439C0C01,  0x439C0C01,  0x439C0C01,  0x439C0C01 }; // 3.12093766372244180303e2
			static HK_ALIGN16(const unsigned int logP2[4])					= {  0xC2804831,  0xC2804831,  0xC2804831,  0xC2804831 }; // -6.41409952958715622951e1
			static HK_ALIGN16(const unsigned int logQ2[4])					= {  0xC4406C49,  0xC4406C49,  0xC4406C49,  0xC4406C49 }; // -7.69691943550460008604e2
			static HK_ALIGN16(const unsigned int logC0[4])					= {  0x3F317218,  0x3F317218,  0x3F317218,  0x3F317218 }; // 0.693147180559945

			// cut off denormalized stuff
			x = _mm_max_ps(x, *(__m128*)minNormalizedPosNumber);

			__m128i emm0 = _mm_srli_epi32(_mm_castps_si128(x), 23);

			// keep only the fractional part
			x = _mm_or_ps(_mm_and_ps(x, *(__m128*)invMantissaMask), *(__m128*)one);

			x = _mm_mul_ps(_mm_sub_ps(x, *(__m128*)one), _mm_rcp_ps(_mm_add_ps(x, *(__m128*)one)));
			x = _mm_add_ps(x, x);
			__m128 bs = x;

			x = _mm_mul_ps(x, x);

			__m128 x4 = _mm_mul_ps(*(__m128*)logP0, x);
			__m128 x6 = _mm_mul_ps(*(__m128*)logQ0, x);

			x4 = _mm_add_ps(x4, *(__m128*)logP1);
			x6 = _mm_add_ps(x6, *(__m128*)logQ1);

			x4 = _mm_mul_ps(x4, x);
			x6 = _mm_mul_ps(x6, x);

			x4 = _mm_add_ps(x4, *(__m128*)logP2);
			x6 = _mm_add_ps(x6, *(__m128*)logQ2);

			x = _mm_mul_ps(x, x4);
			x6 = _mm_rcp_ps(x6);

			x = _mm_mul_ps(x, x6);
			x = _mm_mul_ps(x, bs);

			emm0 = _mm_sub_epi32(emm0, *(__m128i*)int0x7f);
			__m128 x1 = _mm_mul_ps(_mm_cvtepi32_ps(emm0), *(__m128*)logC0);

			x = _mm_add_ps(x, bs);
			x = _mm_add_ps(x, x1);
		}
	}

	/// Average absolute error 0.000046
	/// Max absolute error 169.777725 for r=1
	/// Max absolute error 0.001070 elsewhere
	/// About 3x faster than ::logf for 4 simultaneous values
	HK_FORCE_INLINE static hkQuadFloat32 HK_CALL quadLog(const hkQuadFloat32 &r)
	{
		
		__m128 x = r;
		quadLogHelper(x);
		return x;
	}

	HK_FORCE_INLINE static hkQuadDouble64 HK_CALL quadLog(const hkQuadDouble64 &r)
	{
		#if HK_SSE_VERSION >= 0x50
		__m128 x = _mm256_cvtpd_ps(r);
#else
		const __m128 xy = _mm_cvtpd_ps(r.xy);
		const __m128 zw = _mm_cvtpd_ps(r.zw);
		__m128 x = _mm_shuffle_ps(xy,zw,_MM_SHUFFLE(1,0,1,0));
#endif
		quadLogHelper(x);

#		if HK_SSE_VERSION >= 0x50
		return _mm256_cvtps_pd(x);
#else
		hkQuadDouble64 result;
		result.xy = _mm_cvtps_pd(x);
		result.zw = _mm_cvtps_pd(_mm_shuffle_ps(x,x,_MM_SHUFFLE(1,0,3,2)));
		return result;
#endif
	}

	/// Average absolute error 0.000069
	/// Max absolute error 0.000763
	/// About 6x faster than ::atan2f for 4 simultaneous values
	HK_FORCE_INLINE static __m128 HK_CALL quadAtan2(const __m128& y, const __m128& x)
	{
		static HK_ALIGN16(const hkUint32 signMask[4])		= { 0x80000000, 0x80000000, 0x80000000, 0x80000000 };
		static HK_ALIGN16(const hkUint32 one[4])			= { 0x3F800000, 0x3F800000, 0x3F800000, 0x3F800000 }; //  1.0
		static HK_ALIGN16(const hkUint32 pi[4])				= { 0x40490FDB, 0x40490FDB, 0x40490FDB, 0x40490FDB }; //  PI
		static HK_ALIGN16(const hkUint32 piOver2[4])		= { 0x3FC90FDB, 0x3FC90FDB, 0x3FC90FDB, 0x3FC90FDB }; //  PI / 2
		static HK_ALIGN16(const hkUint32 t0[4])				= { 0xBDBBB0F6, 0xBDBBB0F6, 0xBDBBB0F6, 0xBDBBB0F6 }; // -0.91646118527267623468e-1
		static HK_ALIGN16(const hkUint32 t1[4])				= { 0xBFB2A61F, 0xBFB2A61F, 0xBFB2A61F, 0xBFB2A61F }; // -0.13956945682312098640e1
		static HK_ALIGN16(const hkUint32 t2[4])				= { 0xC2BCC9B1, 0xC2BCC9B1, 0xC2BCC9B1, 0xC2BCC9B1 }; // -0.94393926122725531747e2
		static HK_ALIGN16(const hkUint32 t3[4])				= { 0x414E36D1, 0x414E36D1, 0x414E36D1, 0x414E36D1 }; //  0.12888383034157279340e2
		static HK_ALIGN16(const hkUint32 s0[4])				= { 0x3FA3CF0F, 0x3FA3CF0F, 0x3FA3CF0F, 0x3FA3CF0F }; //  0.12797564625607904396e1
		static HK_ALIGN16(const hkUint32 s1[4])				= { 0x400C9F34, 0x400C9F34, 0x400C9F34, 0x400C9F34 }; //  0.21972168858277355914e1
		static HK_ALIGN16(const hkUint32 s2[4])				= { 0x40DA37C2, 0x40DA37C2, 0x40DA37C2, 0x40DA37C2 }; //  0.68193064729268275701e1
		static HK_ALIGN16(const hkUint32 s3[4])				= { 0x41E1A443, 0x41E1A443, 0x41E1A443, 0x41E1A443 }; //  0.28205206687035841409e2

		__m128 oneF = *(const __m128*)one;

		__m128 rx = _mm_rcp_ps(x);
		__m128 signMaskF = *(const __m128*)signMask;
		__m128 y_div_x = _mm_mul_ps(y, rx);
		__m128 esp4 = _mm_or_ps(_mm_and_ps(signMaskF, y), *(const __m128*)pi);
		__m128 x_ge_0 = _mm_cmple_ps(_mm_setzero_ps(), rx);

		__m128 minus1F = _mm_or_ps(oneF, signMaskF);
		__m128 x5 = _mm_or_ps(_mm_cmplt_ps(oneF, y_div_x), _mm_cmpnle_ps(minus1F, y_div_x));

		__m128 x4 = _mm_rcp_ps(y_div_x);
#if HK_SSE_VERSION >= 0x41
		x4 = _mm_blendv_ps(y_div_x,x4,x5);
#else
		x4 = _mm_or_ps(_mm_andnot_ps(x5, y_div_x), _mm_and_ps(x5, x4));
#endif
		__m128 x0 = x4;

		x4 = _mm_mul_ps(x4, x4);

		__m128 x1 = _mm_add_ps(*(const __m128*)s0, x4);
		x1 = _mm_mul_ps(_mm_rcp_ps(x1), *(const __m128*)t0);
		__m128 x3 = _mm_add_ps(*(const __m128*)s1, x4);
		x1 = _mm_add_ps(x1, x3);

		x1 = _mm_mul_ps(_mm_rcp_ps(x1), *(const __m128*)t1);
		__m128 x7 = _mm_add_ps(*(const __m128*)s2, x4);
		x1 = _mm_add_ps(x1, x7);

		x1 = _mm_mul_ps(_mm_rcp_ps(x1), *(const __m128*)t2);
		x3 = _mm_add_ps(*(const __m128*)s3, x4);
		__m128 x6 = _mm_mul_ps(*(const __m128*)t3, x0);
		x1 = _mm_add_ps(x1, x3);

		x0 = _mm_and_ps(x0, signMaskF);
		x1 = _mm_mul_ps(_mm_rcp_ps(x1), x6);

		x0 = _mm_sub_ps(_mm_or_ps(x0, *(const __m128*)piOver2), x1);

#if HK_SSE_VERSION >= 0x41
		x0 = _mm_blendv_ps(x1,x0,x5);
#else
		x0 = _mm_or_ps(_mm_andnot_ps(x5, x1), _mm_and_ps(x5, x0));
#endif

		// select case
		x1 = _mm_add_ps(x0, esp4);
#if HK_SSE_VERSION >= 0x41
		x0 = _mm_blendv_ps(x1,x0,x_ge_0);
#else
		x0 = _mm_or_ps(_mm_andnot_ps(x_ge_0, x1),_mm_and_ps(x_ge_0, x0));
#endif

		return x0;
	}

	/// Average absolute error 0.000069
	/// Max absolute error 0.000712
	/// About 1.5x faster than ::atan2 for 2 simultaneous values
	HK_FORCE_INLINE static __m128d HK_CALL twoAtan2(const __m128d& y, const __m128d& x)
	{
		static HK_ALIGN16(const hkUint64 signMask[2])		= { 0x8000000000000000ull, 0x8000000000000000ull };
		static HK_ALIGN16(const hkUint64 one[2])			= { 0x3FF0000000000000ull, 0x3FF0000000000000ull }; //  1.0
		static HK_ALIGN16(const hkUint64 pi[2] )            = { 0x400921FB54442D18ull, 0x400921FB54442D18ull }; // pi
		static HK_ALIGN16(const hkUint64 piOver2[2] )       = { 0x3FF921FB54442D18ull, 0x3FF921FB54442D18ull }; // pi / 2
		static HK_ALIGN16(const hkUint64 t0[2])				= { 0xBFB7761EB9E144ACull, 0xBFB7761EB9E144ACull }; // -0.91646118527267623468e-1
		static HK_ALIGN16(const hkUint64 t1[2])				= { 0xBFF654C3D3DC204Eull, 0xBFF654C3D3DC204Eull }; // -0.13956945682312098640e1
		static HK_ALIGN16(const hkUint64 t2[2])				= { 0xC057993615E9895Cull, 0xC057993615E9895Cull }; // -0.94393926122725531747e2
		static HK_ALIGN16(const hkUint64 t3[2])				= { 0x4029C6DA241C0DB4ull, 0x4029C6DA241C0DB4ull }; //  0.12888383034157279340e2
		static HK_ALIGN16(const hkUint64 s0[2])				= { 0x3FF479E1E998B120ull, 0x3FF479E1E998B120ull }; //  0.12797564625607904396e1
		static HK_ALIGN16(const hkUint64 s1[2])				= { 0x400193E67256CAF0ull, 0x400193E67256CAF0ull }; //  0.21972168858277355914e1
		static HK_ALIGN16(const hkUint64 s2[2])				= { 0x401B46F846AA7CC2ull, 0x401B46F846AA7CC2ull }; //  0.68193064729268275701e1
		static HK_ALIGN16(const hkUint64 s3[2])				= { 0x403C34886CE9BD4Cull, 0x403C34886CE9BD4Cull }; //  0.28205206687035841409e2

		__m128d oneF = *(const __m128d*)one;

		__m128d rx = _mm_cvtps_pd(_mm_rcp_ps(_mm_cvtpd_ps(x)));
		__m128d signMaskF = *(const __m128d*)signMask;
		__m128d y_div_x = _mm_mul_pd(y, rx);
		__m128d esp4 = _mm_or_pd(_mm_and_pd(signMaskF, y), *(const __m128d*)pi);
		__m128d x_ge_0 = _mm_cmple_pd(_mm_setzero_pd(), rx);

		__m128d minus1F = _mm_or_pd(oneF, signMaskF);
		__m128d x5 = _mm_or_pd(_mm_cmplt_pd(oneF, y_div_x), _mm_cmpnle_pd(minus1F, y_div_x));

		__m128d x4 = _mm_cvtps_pd(_mm_rcp_ps(_mm_cvtpd_ps(y_div_x)));
#if HK_SSE_VERSION >= 0x41
		x4 = _mm_blendv_pd(y_div_x,x4,x5);
#else
		x4 = _mm_or_pd(_mm_andnot_pd(x5, y_div_x), _mm_and_pd(x5, x4));
#endif
		__m128d x0 = x4;

		x4 = _mm_mul_pd(x4, x4);

		__m128d x1 = _mm_add_pd(*(const __m128d*)s0, x4);
		x1 = _mm_mul_pd(_mm_cvtps_pd(_mm_rcp_ps(_mm_cvtpd_ps(x1))), *(const __m128d*)t0);
		__m128d x3 = _mm_add_pd(*(const __m128d*)s1, x4);
		x1 = _mm_add_pd(x1, x3);

		x1 = _mm_mul_pd(_mm_cvtps_pd(_mm_rcp_ps(_mm_cvtpd_ps(x1))), *(const __m128d*)t1);
		__m128d x7 = _mm_add_pd(*(const __m128d*)s2, x4);
		x1 = _mm_add_pd(x1, x7);

		x1 = _mm_mul_pd(_mm_cvtps_pd(_mm_rcp_ps(_mm_cvtpd_ps(x1))), *(const __m128d*)t2);
		x3 = _mm_add_pd(*(const __m128d*)s3, x4);
		__m128d x6 = _mm_mul_pd(*(const __m128d*)t3, x0);
		x1 = _mm_add_pd(x1, x3);

		x0 = _mm_and_pd(x0, signMaskF);
		x1 = _mm_mul_pd(_mm_cvtps_pd(_mm_rcp_ps(_mm_cvtpd_ps(x1))), x6);

		x0 = _mm_sub_pd(_mm_or_pd(x0, *(const __m128d*)piOver2), x1);

#if HK_SSE_VERSION >= 0x41
		x0 = _mm_blendv_pd(x1,x0,x5);
#else
		x0 = _mm_or_pd(_mm_andnot_pd(x5, x1), _mm_and_pd(x5, x0));
#endif

		// select case
		x1 = _mm_add_pd(x0, esp4);
#if HK_SSE_VERSION >= 0x41
		x0 = _mm_blendv_pd(x1,x0,x_ge_0);
#else
		x0 = _mm_or_pd(_mm_andnot_pd(x_ge_0, x1),_mm_and_pd(x_ge_0, x0));
#endif

		return x0;
	}

#	define HK_MATH_prefetch128
	HK_FORCE_INLINE static void HK_CALL prefetch128( const void* p)
	{
		_mm_prefetch( (const char*)p, _MM_HINT_NTA );
	}

#	define HK_MATH_forcePrefetch
	template<int SIZE>
	HK_FORCE_INLINE static void HK_CALL forcePrefetch( const void* p )
	{
		const char* q = (const char*)p;
		_mm_prefetch( q, _MM_HINT_NTA );
		if ( SIZE > 64){  _mm_prefetch( q + 64, _MM_HINT_NTA ); }
		if ( SIZE > 128){ _mm_prefetch( q + 128, _MM_HINT_NTA ); }
		if ( SIZE > 192){ _mm_prefetch( q + 192, _MM_HINT_NTA ); }
	}

#	define HK_MATH_hkToIntFast
	HK_FORCE_INLINE static int HK_CALL hkToIntFast( const hkDouble64 r )
	{
		return _mm_cvttsd_si32(_mm_load_sd(&r));
	}
	HK_FORCE_INLINE static int HK_CALL hkToIntFast( const hkFloat32 r )
	{
		return _mm_cvtt_ss2si(_mm_load_ss(&r));
	}

#	define HK_MATH_hkFloatToInt
	HK_FORCE_INLINE static int HK_CALL hkFloatToInt(const hkFloat32 r)
	{
		return hkMath::hkToIntFast(r);
	}
	HK_FORCE_INLINE static int HK_CALL hkFloatToInt(const hkDouble64 r)
	{
		return hkMath::hkToIntFast(r);
	}

	HK_FORCE_INLINE static hkQuadUint HK_CALL quadF2I(const hkQuadFloat32& f)
	{
		return _mm_cvttps_epi32(f);
	}

	HK_FORCE_INLINE static hkQuadUint HK_CALL quadF2I(const hkQuadDouble64& f)
	{
#if HK_SSE_VERSION >= 0x50
		return _mm256_cvttpd_epi32(f);
#else
		__m128i xy = _mm_cvttpd_epi32(f.xy);
		__m128i zw = _mm_cvttpd_epi32(f.zw);
		return _mm_castps_si128(_mm_shuffle_ps(_mm_castsi128_ps(xy),_mm_castsi128_ps(zw),_MM_SHUFFLE(1,0,1,0)));
#endif
	}

	HK_FORCE_INLINE static __m128 HK_CALL quadFabs(const __m128 &v)
	{
		return _mm_castsi128_ps( _mm_srli_epi32( _mm_slli_epi32( _mm_castps_si128(v), 1 ), 1 ) ); 
	}

	HK_FORCE_INLINE static __m128d HK_CALL twoFabs(const __m128d &v)
	{
		return _mm_castsi128_pd( _mm_srli_epi64( _mm_slli_epi64( _mm_castpd_si128(v), 1 ), 1 ) ); 
	}

#	define HK_MATH_fabs
	HK_FORCE_INLINE static hkFloat32 HK_CALL fabs(const hkFloat32 r) 
	{ 
		const __m128 v = _mm_load_ss(&r);
		const __m128 abs = quadFabs(v); 
		return _mm_cvtss_f32(abs);
	}
	HK_FORCE_INLINE static hkDouble64 HK_CALL fabs(const hkDouble64 r) 
	{ 
		const __m128d v = _mm_load_sd(&r);
		const __m128d abs = twoFabs(v); 
		return HK_M128(abs).m128d_f64[0];
	}

#if HK_SSE_VERSION >= 0x31
#define HK_MATH_abs
	template<typename T>
	HK_FORCE_INLINE static T HK_CALL abs(T t) { return t < T(0) ? -t : t; }

	template<>
	HK_FORCE_INLINE hkFloat32 HK_CALL abs(hkFloat32 r) { return fabs(r); }

	template<>
	HK_FORCE_INLINE hkDouble64 HK_CALL abs(hkDouble64 r) { return fabs(r); }

	template<>
	HK_FORCE_INLINE hkInt32 HK_CALL abs(hkInt32 r) 
	{ 
		__m128i rr = _mm_cvtsi32_si128(r);
		__m128i rabs = _mm_abs_epi32(rr);
		return _mm_cvtsi128_si32(rabs); 
	}

#endif

#	define HK_MATH_equal
	HK_FORCE_INLINE static bool HK_CALL equal(hkFloat32 x, hkFloat32 y)
	{
		const __m128 xx = _mm_load_ss(&x);
		const __m128 yy = _mm_load_ss(&y);
		const __m128 abs = quadFabs(_mm_sub_ss(xx,yy)); 
		const __m128 tol = _mm_set1_ps(1e-5f);
		const int mask = _mm_ucomile_ss(abs, tol);
		return bool(mask);
	}
	HK_FORCE_INLINE static bool HK_CALL equal(hkFloat32 x, hkFloat32 y, hkFloat32 tolerance2)
	{
		const __m128 xx = _mm_load_ss(&x);
		const __m128 yy = _mm_load_ss(&y);
		const __m128 abs = quadFabs(_mm_sub_ss(xx,yy)); 
		const int mask = _mm_ucomile_ss(abs, _mm_load_ss(&tolerance2));
		return bool(mask);
	}
	HK_FORCE_INLINE static bool HK_CALL equal(hkDouble64 x, hkFloat32 y)
	{
		const __m128d xxd = _mm_load_sd(&x);
		const __m128 xx = _mm_cvtsd_ss(_mm_setzero_ps(), xxd);
		const __m128 yy = _mm_load_ss(&y);
		const __m128 abs = quadFabs(_mm_sub_ss(xx,yy)); 
		const __m128 tol = _mm_set1_ps(1e-5f);
		const int mask = _mm_ucomile_ss(abs, tol);
		return bool(mask);
	}
	HK_FORCE_INLINE static bool HK_CALL equal(hkDouble64 x, hkFloat32 y, hkFloat32 tolerance2)
	{
		const __m128d xxd = _mm_load_sd(&x);
		const __m128 xx = _mm_cvtsd_ss(_mm_setzero_ps(), xxd);
		const __m128 yy = _mm_load_ss(&y);
		const __m128 abs = quadFabs(_mm_sub_ss(xx,yy)); 
		const int mask = _mm_ucomile_ss(abs, _mm_load_ss(&tolerance2));
		return bool(mask);
	}
	HK_FORCE_INLINE static bool HK_CALL equal(hkFloat32 x, hkDouble64 y)
	{
		const __m128d yyd = _mm_load_sd(&y);
		const __m128 yy = _mm_cvtsd_ss(_mm_setzero_ps(), yyd);
		const __m128 xx = _mm_load_ss(&x);
		const __m128 abs = quadFabs(_mm_sub_ss(xx,yy)); 
		const __m128 tol = _mm_set1_ps(1e-5f);
		const int mask = _mm_ucomile_ss(abs, tol);
		return bool(mask);
	}
	HK_FORCE_INLINE static bool HK_CALL equal(hkFloat32 x, hkDouble64 y, hkFloat32 tolerance2)
	{
		const __m128d yyd = _mm_load_sd(&y);
		const __m128 yy = _mm_cvtsd_ss(_mm_setzero_ps(), yyd);
		const __m128 xx = _mm_load_ss(&x);
		const __m128 abs = quadFabs(_mm_sub_ss(xx,yy)); 
		const int mask = _mm_ucomile_ss(abs, _mm_load_ss(&tolerance2));
		return bool(mask);
	}
	HK_FORCE_INLINE static bool HK_CALL equal(hkDouble64 x, hkDouble64 y)
	{
		const __m128d xx = _mm_load_sd(&x);
		const __m128d yy = _mm_load_sd(&y);
		const __m128d abs = twoFabs(_mm_sub_sd(xx,yy));
		const __m128d tol = _mm_set1_pd(1e-5);
		const int mask = _mm_ucomile_sd(abs, tol);
		return bool(mask);
	}
	HK_FORCE_INLINE static bool HK_CALL equal(hkDouble64 x, hkDouble64 y, hkDouble64 tolerance2)
	{
		const __m128d xx = _mm_load_sd(&x);
		const __m128d yy = _mm_load_sd(&y);
		const __m128d abs = twoFabs(_mm_sub_sd(xx,yy)); 
		const int mask = _mm_ucomile_sd(abs, _mm_load_sd(&tolerance2));
		return bool(mask);
	}
	HK_FORCE_INLINE static bool HK_CALL equal(hkDouble64 x, hkDouble64 y, hkFloat32 tolerance2)
	{
		const __m128d xx = _mm_load_sd(&x);
		const __m128d yy = _mm_load_sd(&y);
		const __m128d abs = twoFabs(_mm_sub_sd(xx,yy)); 
		const __m128 tolf = _mm_load_ss(&tolerance2);
		const __m128d told = _mm_cvtss_sd(_mm_setzero_pd(), tolf);
		const int mask = _mm_ucomile_sd(abs, told);
		return bool(mask);
	}


#	define HK_MATH_max2
	template <typename T1,typename T2>
	HK_FORCE_INLINE static T1 HK_CALL max2( T1 x, T2 y)
	{
		return x > (T1)y ? x : (T1)y;
	}
	template <>
	HK_FORCE_INLINE hkFloat32 HK_CALL max2<hkFloat32, hkFloat32>( hkFloat32 x, hkFloat32 y)
	{
		const __m128 v = _mm_max_ss(_mm_load_ss(&x),_mm_load_ss(&y));
		return _mm_cvtss_f32(v);
	}
	template <>
	HK_FORCE_INLINE hkDouble64 HK_CALL max2<hkDouble64, hkDouble64>( hkDouble64 x, hkDouble64 y)
	{
		const __m128d v = _mm_max_sd(_mm_load_sd(&x),_mm_load_sd(&y));
		return HK_M128(v).m128d_f64[0];
	}
#if HK_SSE_VERSION >= 0x41
	template <>
	HK_FORCE_INLINE hkUint32 HK_CALL max2<hkUint32>( hkUint32 x, hkUint32 y)
	{
		const __m128i v = _mm_max_epu32(_mm_cvtsi32_si128(x),_mm_cvtsi32_si128(y));
		return (hkUint32)_mm_cvtsi128_si32(v);
	}
	template <>
	HK_FORCE_INLINE hkInt32 HK_CALL max2<hkInt32>( hkInt32 x, hkInt32 y)
	{
		const __m128i v = _mm_max_epi32(_mm_cvtsi32_si128(x),_mm_cvtsi32_si128(y));
		return _mm_cvtsi128_si32(v);
	}
#endif

#	define HK_MATH_min2
	template <typename T1,typename T2>
	HK_FORCE_INLINE static T1 HK_CALL min2( T1 x, T2 y)
	{
		return x < (T1)y ? x : (T1)y;
	}
	template <>
	HK_FORCE_INLINE hkFloat32 HK_CALL min2<hkFloat32, hkFloat32>( hkFloat32 x, hkFloat32 y)
	{
		const __m128 v = _mm_min_ss(_mm_load_ss(&x),_mm_load_ss(&y));
		return _mm_cvtss_f32(v);
	}
	template <>
	HK_FORCE_INLINE hkDouble64 HK_CALL min2<hkDouble64, hkDouble64>( hkDouble64 x, hkDouble64 y)
	{
		const __m128d v = _mm_min_sd(_mm_load_sd(&x),_mm_load_sd(&y));
		return HK_M128(v).m128d_f64[0];
	}
#if HK_SSE_VERSION >= 0x41
	template <>
	HK_FORCE_INLINE hkUint32 HK_CALL min2<hkUint32>( hkUint32 x, hkUint32 y)
	{
		const __m128i v = _mm_min_epu32(_mm_cvtsi32_si128(x),_mm_cvtsi32_si128(y));
		return (hkUint32)_mm_cvtsi128_si32(v);
	}
	template <>
	HK_FORCE_INLINE hkInt32 HK_CALL min2<hkInt32>( hkInt32 x, hkInt32 y)
	{
		const __m128i v = _mm_min_epi32(_mm_cvtsi32_si128(x),_mm_cvtsi32_si128(y));
		return _mm_cvtsi128_si32(v);
	}
#endif

#	define HK_MATH_clamp
	template <typename T1, typename T2, typename T3>
	HK_FORCE_INLINE static T1 HK_CALL clamp( T1 x, T2 mi, T3 ma)
	{
		if ( x < (T1)mi ) return (T1)mi;
		if ( x > (T1)ma ) return (T1)ma;
		return x;
	}
	template <>
	HK_FORCE_INLINE hkFloat32 HK_CALL clamp<hkFloat32, hkFloat32, hkFloat32>( hkFloat32 x, hkFloat32 mi, hkFloat32 ma)
	{
		const __m128 lo = _mm_max_ss(_mm_load_ss(&x),_mm_load_ss(&mi));
		const __m128 hi = _mm_min_ss(             lo,_mm_load_ss(&ma));
		return _mm_cvtss_f32(hi);
	}
	template <>
	HK_FORCE_INLINE hkDouble64 HK_CALL clamp<hkDouble64, hkDouble64, hkDouble64>( hkDouble64 x, hkDouble64 mi, hkDouble64 ma)
	{
		const __m128d lo = _mm_max_sd(_mm_load_sd(&x),_mm_load_sd(&mi));
		const __m128d hi = _mm_min_sd(             lo,_mm_load_sd(&ma));
		return HK_M128(hi).m128d_f64[0];
	}
#if HK_SSE_VERSION >= 0x41
	template <>
	HK_FORCE_INLINE hkInt32 HK_CALL clamp<hkInt32>( hkInt32 x, hkInt32 mi, hkInt32 ma)
	{
		const __m128i lo = _mm_max_epi32(_mm_cvtsi32_si128(x),_mm_cvtsi32_si128(mi));
		const __m128i hi = _mm_min_epi32(                  lo,_mm_cvtsi32_si128(ma));
		return _mm_cvtsi128_si32(hi);
	}
	template <>
	HK_FORCE_INLINE hkUint32 HK_CALL clamp<hkUint32>( hkUint32 x, hkUint32 mi, hkUint32 ma)
	{
		const __m128i lo = _mm_max_epu32(_mm_cvtsi32_si128(x),_mm_cvtsi32_si128(mi));
		const __m128i hi = _mm_min_epu32(                  lo,_mm_cvtsi32_si128(ma));
		return (hkUint32)_mm_cvtsi128_si32(hi);
	}
#endif

	// Define but don't implement the specializations for hkSimdFloat32.
	// On MSVC, accidentally calling these can cause misaligned SSE access.
	template <>
	HK_FORCE_INLINE hkSimdFloat32 HK_CALL min2<hkSimdFloat32, hkSimdFloat32>( hkSimdFloat32 x, hkSimdFloat32 y);

	template <>
	HK_FORCE_INLINE hkSimdFloat32 HK_CALL max2<hkSimdFloat32, hkSimdFloat32>( hkSimdFloat32 x, hkSimdFloat32 y);

	template <>
	HK_FORCE_INLINE hkSimdFloat32 HK_CALL clamp<hkSimdFloat32, hkSimdFloat32, hkSimdFloat32>( hkSimdFloat32 x, hkSimdFloat32 mi, hkSimdFloat32 ma);

	template <>
	HK_FORCE_INLINE hkSimdDouble64 HK_CALL min2<hkSimdDouble64, hkSimdDouble64>( hkSimdDouble64 x, hkSimdDouble64 y);

	template <>
	HK_FORCE_INLINE hkSimdDouble64 HK_CALL max2<hkSimdDouble64, hkSimdDouble64>( hkSimdDouble64 x, hkSimdDouble64 y);

	template <>
	HK_FORCE_INLINE hkSimdDouble64 HK_CALL clamp<hkSimdDouble64, hkSimdDouble64, hkSimdDouble64>( hkSimdDouble64 x, hkSimdDouble64 mi, hkSimdDouble64 ma);



	HK_FORCE_INLINE static __m128 HK_CALL quadFloor(const __m128 &v)
	{
#if HK_SSE_VERSION >= 0x41
		const __m128 result = _mm_floor_ps(v);
#else
		static HK_ALIGN16( const hkUint32 two23[4] )  = { 0x4B000000, 0x4B000000, 0x4B000000, 0x4B000000 }; // 2^23 as float

		const __m128 b = _mm_castsi128_ps( _mm_srli_epi32( _mm_slli_epi32( _mm_castps_si128(v), 1 ), 1 ) ); // fabs(v)
		const __m128 d = _mm_sub_ps( _mm_add_ps( _mm_add_ps( _mm_sub_ps( v, *(__m128*)&two23 ), *(__m128*)&two23 ), *(__m128*)&two23 ), *(__m128*)&two23 ); // the meat of floor
		const __m128 largeMaskE = _mm_cmpgt_ps( b, *(__m128*)&two23 ); // $ffffffff if v >= 2^23
		const __m128 g = _mm_cmplt_ps( v, d ); // check for possible off by one error
		const __m128 h = _mm_cvtepi32_ps( _mm_castps_si128(g) ); // convert positive check result to -1.0, negative to 0.0
		const __m128 t = _mm_add_ps( d, h ); // add in the error if there is one

		// Select between output result and input value based on v >= 2^23
		const __m128 result = _mm_or_ps( _mm_and_ps(largeMaskE, v), _mm_andnot_ps(largeMaskE, t) );
#endif
		return result;
	}

	HK_FORCE_INLINE static __m128d HK_CALL twoFloor(const __m128d &v)
	{
#if HK_SSE_VERSION >= 0x41
		const __m128d result = _mm_floor_pd(v);
#else
		static HK_ALIGN16( const hkUint64 two52[2] )  = { 0x4330000000000000ull, 0x4330000000000000ull }; // 2^52 as double

		const __m128d b = _mm_castsi128_pd( _mm_srli_epi64( _mm_slli_epi64( _mm_castpd_si128(v), 1 ), 1 ) ); // fabs(v)
		const __m128d d = _mm_sub_pd( _mm_add_pd( _mm_add_pd( _mm_sub_pd( v, *(__m128d*)&two52 ), *(__m128d*)&two52 ), *(__m128d*)&two52 ), *(__m128d*)&two52 ); // the meat of floor
		const __m128d largeMaskE = _mm_cmpgt_pd( b, *(__m128d*)&two52 ); // $ffffffffffffffff if v >= 2^52
		const __m128d g = _mm_cmplt_pd( v, d ); // check for possible off by one error
		const __m128d h = _mm_cvtepi32_pd( _mm_castpd_si128(g) ); // convert positive check result to -1.0, negative to 0.0 (only need the lower 64 bit anyways, so cvtepi32 is fine)
		const __m128d t = _mm_add_pd( d, h ); // add in the error if there is one

		// Select between output result and input value based on v >= 2^52
		const __m128d result = _mm_or_pd( _mm_and_pd(largeMaskE, v), _mm_andnot_pd(largeMaskE, t) );
#endif
		return result;
	}

#	define HK_MATH_floor
	HK_FORCE_INLINE static hkFloat32 HK_CALL floor(const hkFloat32 r) 
	{ 
		const __m128 v = _mm_load_ss(&r);
		const __m128 result = quadFloor(v);
		return _mm_cvtss_f32(result);
	}
	HK_FORCE_INLINE static hkDouble64 HK_CALL floor(const hkDouble64 r) 
	{ 
		const __m128d v = _mm_load_sd(&r);
		const __m128d result = twoFloor(v);
		return HK_M128(result).m128d_f64[0];
	}

#	define HK_MATH_hkFloor
	HK_FORCE_INLINE static hkFloat32 HK_CALL hkFloor(const hkFloat32 r)
	{
		return hkMath::floor(r);
	}
	HK_FORCE_INLINE static hkDouble64 HK_CALL hkFloor(const hkDouble64 r)
	{
		return hkMath::floor(r);
	}

#	define HK_MATH_hkFloorToInt
	HK_FORCE_INLINE static int HK_CALL hkFloorToInt(const hkFloat32 r)
	{
		const __m128 v = _mm_load_ss(&r);
		const __m128 result = quadFloor(v);
		return _mm_cvtt_ss2si(result);
	}
	HK_FORCE_INLINE static int HK_CALL hkFloorToInt(const hkDouble64 r)
	{
		const __m128d v = _mm_load_sd(&r);
		const __m128d result = twoFloor(v);
		return _mm_cvttsd_si32(result);
	}

#	define HK_MATH_ceil
	HK_FORCE_INLINE static hkFloat32 HK_CALL ceil( const hkFloat32 r ) 
	{ 
		const __m128 v = _mm_load_ss(&r);
#if HK_SSE_VERSION >= 0x41
		const __m128 result = _mm_ceil_ss(v, v);
#else
		static HK_ALIGN16(const hkUint32 one[4])			= { 0x3F800000, 0x3F800000, 0x3F800000, 0x3F800000 }; //  1.0
		const __m128 result = _mm_add_ps(*(__m128*)one, quadFloor(v));
#endif
		return _mm_cvtss_f32(result);
	}
	HK_FORCE_INLINE static hkDouble64 HK_CALL ceil( const hkDouble64 r ) 
	{ 
		const __m128d v = _mm_load_sd(&r);
#if HK_SSE_VERSION >= 0x41
		const __m128d result = _mm_ceil_sd(v, v);
#else
		static HK_ALIGN16(const hkUint64 one[2])			= { 0x3FF0000000000000ull, 0x3FF0000000000000ull }; //  1.0
		const __m128d result = _mm_add_pd(*(__m128d*)one, twoFloor(v));
#endif
		return HK_M128(result).m128d_f64[0];
	}

	HK_FORCE_INLINE static __m128 HK_CALL quadMod(const __m128 &a, const __m128 &b)
	{
		const __m128 denomIsZero = _mm_cmpeq_ps(b,_mm_setzero_ps());
		const __m128 q = quadFloor(_mm_div_ps(a,b));
		__m128 result = _mm_sub_ps(a, _mm_mul_ps(q,b));
		return _mm_andnot_ps(denomIsZero, result);
	}

	HK_FORCE_INLINE static __m128d HK_CALL twoMod(const __m128d &a, const __m128d &b)
	{
		const __m128d denomIsZero = _mm_cmpeq_pd(b,_mm_setzero_pd());
		const __m128d q = twoFloor(_mm_div_pd(a,b));
		__m128d result = _mm_sub_pd(a, _mm_mul_pd(q,b));
		return _mm_andnot_pd(denomIsZero, result);
	}

#	define HK_MATH_fmod
	HK_FORCE_INLINE static hkFloat32 HK_CALL fmod(const hkFloat32 n, const hkFloat32 d) 
	{ 
		const __m128 numer = _mm_load_ss(&n);
		const __m128 denom = _mm_load_ss(&d);
		__m128 result = quadMod(numer, denom);
		return _mm_cvtss_f32(result);
	}
	HK_FORCE_INLINE static hkDouble64 HK_CALL fmod(const hkDouble64 n, const hkDouble64 d) 
	{ 
		const __m128d numer = _mm_load_sd(&n);
		const __m128d denom = _mm_load_sd(&d);
		__m128d result = twoMod(numer, denom);
		return HK_M128(result).m128d_f64[0];
	}

#	define HK_MATH_signBitSet
	HK_FORCE_INLINE static bool HK_CALL signBitSet(const hkFloat32& r)
	{
		return (bool)_mm_movemask_ps(_mm_load_ss(&r));
	}
	HK_FORCE_INLINE static bool HK_CALL signBitSet(const hkDouble64& r)
	{
		return (bool)_mm_movemask_pd(_mm_load_sd(&r));
	}

#	define HK_MATH_logApproximation
	HK_FORCE_INLINE static hkFloat32 HK_CALL logApproximation(const hkFloat32& r)
	{
		const hkQuadFloat32 q = _mm_load1_ps(&r);
		const hkQuadFloat32 l = quadLog(q);
		return _mm_cvtss_f32(l);
	}

	HK_FORCE_INLINE static hkDouble64 HK_CALL logApproximation(const hkDouble64& r)
	{
#if HK_SSE_VERSION >= 0x50
		hkQuadDouble64 q = _mm256_set1_pd(r);
		hkQuadDouble64 l = quadLog(q);
		return l.m256d_f64[0];
#else
		hkQuadDouble64 q;
		q.xy = _mm_load1_pd(&r);
		q.zw = _mm_load1_pd(&r);
		hkQuadDouble64 l = quadLog(q); // change this!
		return HK_M128(l.xy).m128d_f64[0];
#endif
	}

#	define HK_MATH_atan2Approximation
	HK_FORCE_INLINE static hkFloat32 HK_CALL atan2Approximation( const hkFloat32& y, const hkFloat32& x )
	{
		__m128 qy = _mm_load_ss(&y);
		__m128 qx = _mm_load_ss(&x);
		__m128 a = quadAtan2(qy,qx);
		return _mm_cvtss_f32(a);
	}
	HK_FORCE_INLINE static hkDouble64 HK_CALL atan2Approximation( const hkDouble64& y, const hkDouble64& x )
	{
		__m128d qy = _mm_load_sd(&y);
		__m128d qx = _mm_load_sd(&x);
		__m128d a = twoAtan2(qy,qx);
		return HK_M128(a).m128d_f64[0];
	}

	/// Average absolute error 0.001961
	/// Max absolute error 0.013429
	/// About 10x faster than ::sinf for 4 simultaneous values
	HK_FORCE_INLINE static __m128 HK_CALL quadSinApproximation(const __m128& inX)
	{
		static HK_ALIGN16( const hkUint32 twopi[4] )  = { 0x40C90FDB, 0x40C90FDB, 0x40C90FDB, 0x40C90FDB }; // 2*pi
		static HK_ALIGN16( const hkUint32 pi[4] )     = { 0x40490FDB, 0x40490FDB, 0x40490FDB, 0x40490FDB }; // pi
		static HK_ALIGN16( const hkUint32 B[4] )      = { 0x3FA2F983, 0x3FA2F983, 0x3FA2F983, 0x3FA2F983 }; // 4/pi
		static HK_ALIGN16( const hkUint32 C[4] )      = { 0xBECF817B, 0xBECF817B, 0xBECF817B, 0xBECF817B }; // -4/(pi*pi)
		static HK_ALIGN16( const hkUint32 P[4] )      = { 0x3E666666, 0x3E666666, 0x3E666666, 0x3E666666 }; // 0.225

		__m128 x = inX;

		// xx = remap to [0,pi]
		__m128 gePi = _mm_cmpnlt_ps(x, *(__m128*)&pi);
		__m128 limit = _mm_and_ps(gePi, *(__m128*)&twopi);
		__m128 xx = _mm_sub_ps(x, limit);

		// y = B * x + C * x * abs(xx)
		__m128 abs = quadFabs(xx); 
		__m128 y = _mm_mul_ps(abs, xx);
		__m128 Bx = _mm_mul_ps(xx, *(__m128*)&B);
		__m128 Cx_abs = _mm_mul_ps(y, *(__m128*)&C);
		__m128 parabola = _mm_add_ps(Bx, Cx_abs);

		// y = P * (y * abs(y) - y) + y
		abs = quadFabs(parabola); 
		y = _mm_sub_ps(_mm_mul_ps(parabola, abs),parabola);
		__m128 blend = _mm_mul_ps(y, *(__m128*)&P);
		__m128 result = _mm_add_ps(blend, parabola);

		return result;
	}


	/// Average absolute error 0.001961
	/// Max absolute error 0.013429
	/// About 10x faster than ::sin for 4 simultaneous values
	HK_FORCE_INLINE static __m128d HK_CALL twoSinApproximation(const __m128d& inX)
	{
		static HK_ALIGN16( const hkUint64 twopi[2] )  = { 0x401921FB54442D18ull, 0x401921FB54442D18ull }; // 2*pi
		static HK_ALIGN16( const hkUint64 pi[2] )     = { 0x400921FB54442D18ull, 0x400921FB54442D18ull }; // pi
		static HK_ALIGN16( const hkUint64 B[2] )      = { 0x3FF45F306DC9C883ull, 0x3FF45F306DC9C883ull }; // 4/pi
		static HK_ALIGN16( const hkUint64 C[2] )      = { 0xBFD9F02F6222C720ull, 0xBFD9F02F6222C720ull }; // -4/(pi*pi)
		static HK_ALIGN16( const hkUint64 P[2] )      = { 0x3FCCCCCCCCCCCCCDull, 0x3FCCCCCCCCCCCCCDull }; // 0.225

		__m128d x = inX;

		// xx = remap to [0,pi]
		__m128d gePi = _mm_cmpnlt_pd(x, *(__m128d*)&pi);
		__m128d limit = _mm_and_pd(gePi, *(__m128d*)&twopi);
		__m128d xx = _mm_sub_pd(x, limit);

		// y = B * x + C * x * abs(xx)
		__m128d abs = twoFabs(xx); 
		__m128d y = _mm_mul_pd(abs, xx);
		__m128d Bx = _mm_mul_pd(xx, *(__m128d*)&B);
		__m128d Cx_abs = _mm_mul_pd(y, *(__m128d*)&C);
		__m128d parabola = _mm_add_pd(Bx, Cx_abs);

		// y = P * (y * abs(y) - y) + y
		abs = twoFabs(parabola); 
		y = _mm_sub_pd(_mm_mul_pd(parabola, abs),parabola);
		__m128d blend = _mm_mul_pd(y, *(__m128d*)&P);
		__m128d result = _mm_add_pd(blend, parabola);

		return result;
	}

	/// Adapted from the book "Methods and Programs for Mathematical Functions",
	/// Stephen Lloyd Baluk Moshier, Prentice-Hall, 1989
	///
	/// Range reduction is into intervals of pi/4.  The reduction error is nearly eliminated 
	/// by extended precision modular arithmetic.
	/// 
	/// Two polynomial approximating functions are employed.
	/// Between 0 and pi/4 the sine is approximated by
	///      x  +  x**3 P(x**2).
	/// Between pi/4 and pi/2 the cosine is represented as
	///      1  -  x**2 Q(x**2).
	/// 
	/// ACCURACY: matches cmath on MSVC
	/// 
	///                      Relative error:
	/// arithmetic   domain        peak       rms
	///    IEEE    -4096,+4096    1.2e-7     3.0e-8
	///    IEEE    -8192,+8192    3.0e-7     3.0e-8
	/// Partial loss of accuracy begins to occur at x = 2^13
	/// = 8192. Results may be meaningless for x >= 2^24
	///
	/// PERFORMANCE: About 4.3x faster than ::sinf for 4 simultaneous values

	HK_FORCE_INLINE static __m128 HK_CALL quadSin(const __m128& inX)
	{
		HK_ALIGN16(static const hkInt32 sinCoeff0[4]) = { 0xB94CA1F9, 0xB94CA1F9, 0xB94CA1F9, 0xB94CA1F9 }; // -1.9515295891e-4
		HK_ALIGN16(static const hkInt32 sinCoeff1[4]) = { 0x3C08839E, 0x3C08839E, 0x3C08839E, 0x3C08839E }; //  8.3321608736e-3
		HK_ALIGN16(static const hkInt32 sinCoeff2[4]) = { 0xBE2AAAA3, 0xBE2AAAA3, 0xBE2AAAA3, 0xBE2AAAA3 }; // -1.6666654611e-1

		HK_ALIGN16(static const hkInt32 cosCoeff0[4]) = { 0x37CCF5CE, 0x37CCF5CE, 0x37CCF5CE, 0x37CCF5CE }; //  2.443315711809948e-005
		HK_ALIGN16(static const hkInt32 cosCoeff1[4]) = { 0xBAB6061A, 0xBAB6061A, 0xBAB6061A, 0xBAB6061A }; // -1.388731625493765e-003
		HK_ALIGN16(static const hkInt32 cosCoeff2[4]) = { 0x3D2AAAA5, 0x3D2AAAA5, 0x3D2AAAA5, 0x3D2AAAA5 }; //  4.166664568298827e-002

		HK_ALIGN16(static const hkInt32 signMask[4])  = { 0x80000000, 0x80000000, 0x80000000, 0x80000000 };
		HK_ALIGN16(static const hkInt32 fourDivPi[4]) = { 0x3FA2F983, 0x3FA2F983, 0x3FA2F983, 0x3FA2F983 }; // 4 / Pi
		HK_ALIGN16(static const hkInt32 DP1[4])       = { 0xBF490000, 0xBF490000, 0xBF490000, 0xBF490000 }; // -0.78515625
		HK_ALIGN16(static const hkInt32 DP2[4])       = { 0xB97DA000, 0xB97DA000, 0xB97DA000, 0xB97DA000 }; // -2.4187564849853515625e-4
		HK_ALIGN16(static const hkInt32 DP3[4])       = { 0xB3222169, 0xB3222169, 0xB3222169, 0xB3222169 }; // -3.77489497744594108e-8
		HK_ALIGN16(static const hkInt32 floatOne[4])  = { 0x3F800000, 0x3F800000, 0x3F800000, 0x3F800000 }; // 1.0
		HK_ALIGN16(static const hkInt32 floatHalf[4]) = { 0x3F000000, 0x3F000000, 0x3F000000, 0x3F000000 }; // 0.5
		HK_ALIGN16(static const hkInt32 intOne[4])    = { 0x00000001, 0x00000001, 0x00000001, 0x00000001 };

		__m128 x = inX;

		// get abs and sign
		__m128 sign_bit = x;
		x = _mm_andnot_ps( *(__m128*)signMask, x);
		sign_bit = _mm_and_ps(sign_bit, *(__m128*)signMask);

		// scale by 4/Pi
		__m128 y = _mm_mul_ps(x, *(__m128*)fourDivPi);

		__m128i one = *(__m128i*)intOne;
		__m128i two = _mm_add_epi32(one,one);
		__m128i four = _mm_add_epi32(two,two);
		// store the integer part of y in emm2
		__m128i emm2 = _mm_cvttps_epi32(y);
		// j=(j+1) & (~1)
		emm2 = _mm_add_epi32(emm2, one);
		emm2 = _mm_andnot_si128(one, emm2);
		y = _mm_cvtepi32_ps(emm2);
		// get the swap sign flag
		__m128i emm0 = _mm_and_si128(emm2, four);
		emm0 = _mm_slli_epi32(emm0, 29);
		// get the polynom selection mask 
		emm2 = _mm_and_si128(emm2, two);
		emm2 = _mm_cmpeq_epi32(emm2, _mm_setzero_si128());

		__m128 swap_sign_bit = _mm_castsi128_ps(emm0);
		__m128 poly_mask = _mm_castsi128_ps(emm2);
		sign_bit = _mm_xor_ps(sign_bit, swap_sign_bit);

		// The magic pass: Extended precision modular arithmetic
		//   x = ((x - y * DP1) - y * DP2) - y * DP3
		__m128 xmm1 = *(__m128*)DP1;
		__m128 xmm2 = *(__m128*)DP2;
		__m128 xmm3 = *(__m128*)DP3;
		xmm1 = _mm_mul_ps(y, xmm1);
		xmm2 = _mm_mul_ps(y, xmm2);
		xmm3 = _mm_mul_ps(y, xmm3);
		x = _mm_add_ps(x, xmm1);
		x = _mm_add_ps(x, xmm2);
		x = _mm_add_ps(x, xmm3);

		// Evaluate the first polynom  (0 <= x <= Pi/4)
		y = *(__m128*)cosCoeff0;
		__m128 z = _mm_mul_ps(x,x);

		y = _mm_mul_ps(y, z);
		y = _mm_add_ps(y, *(__m128*)cosCoeff1);
		y = _mm_mul_ps(y, z);
		y = _mm_add_ps(y, *(__m128*)cosCoeff2);
		y = _mm_mul_ps(y, z);
		y = _mm_mul_ps(y, z);
		__m128 tmp = _mm_mul_ps(z, *(__m128*)floatHalf);
		y = _mm_sub_ps(y, tmp);
		y = _mm_add_ps(y, *(__m128*)floatOne);

		// Evaluate the second polynom  (Pi/4 <= x <= 0)
		__m128 y2 = *(__m128*)sinCoeff0;
		y2 = _mm_mul_ps(y2, z);
		y2 = _mm_add_ps(y2, *(__m128*)sinCoeff1);
		y2 = _mm_mul_ps(y2, z);
		y2 = _mm_add_ps(y2, *(__m128*)sinCoeff2);
		y2 = _mm_mul_ps(y2, z);
		y2 = _mm_mul_ps(y2, x);
		y2 = _mm_add_ps(y2, x);

		// select the correct result from the two polynoms
#if HK_SSE_VERSION >= 0x41
		y = _mm_blendv_ps(y,y2,poly_mask);
#else
		y2 = _mm_and_ps(poly_mask, y2);
		y = _mm_andnot_ps(poly_mask, y);
		y = _mm_or_ps(y,y2);
#endif
		// update the sign
		y = _mm_xor_ps(y, sign_bit);

		return y;
	}

	/// Double precision version of above
	///
	///                      Relative error:
	/// arithmetic   domain        peak       rms
	///    IEEE -1.07e9,+1.07e9  2.1e-16     5.4e-17
	/// Partial loss of accuracy begins to occur at x = 2**30
	/// = 1.074e9.  The loss is not gradual, but jumps suddenly to
	/// about 1 part in 10e7.  Results may be meaningless for
	/// x > 2**49 = 5.6e14.
	///
	/// PERFORMANCE: About 1.3x faster than ::sin for 2 simultaneous values

	HK_FORCE_INLINE static __m128d HK_CALL twoSin(const __m128d& inX)
	{
		HK_ALIGN16(static const hkInt64 sinCoeff0[2]) = { 0x3de5d8fd1fd19ccdull, 0x3de5d8fd1fd19ccdull }; //  1.58962301576546568060E-10
		HK_ALIGN16(static const hkInt64 sinCoeff1[2]) = { 0xbe5ae5e5a9291f5dull, 0xbe5ae5e5a9291f5dull }; // -2.50507477628578072866E-8
		HK_ALIGN16(static const hkInt64 sinCoeff2[2]) = { 0x3ec71de3567d48a1ull, 0x3ec71de3567d48a1ull }; //  2.75573136213857245213E-6
		HK_ALIGN16(static const hkInt64 sinCoeff3[2]) = { 0xbf2a01a019bfdf03ull, 0xbf2a01a019bfdf03ull }; // -1.98412698295895385996E-4
		HK_ALIGN16(static const hkInt64 sinCoeff4[2]) = { 0x3f8111111110f7d0ull, 0x3f8111111110f7d0ull }; //  8.33333333332211858878E-3
		HK_ALIGN16(static const hkInt64 sinCoeff5[2]) = { 0xbfc5555555555548ull, 0xbfc5555555555548ull }; // -1.66666666666666307295E-1

		HK_ALIGN16(static const hkInt64 cosCoeff0[2]) = { 0xbda8fa49a0861a9bull, 0xbda8fa49a0861a9bull }; // -1.13585365213876817300E-11
		HK_ALIGN16(static const hkInt64 cosCoeff1[2]) = { 0x3e21ee9d7b4e3f05ull, 0x3e21ee9d7b4e3f05ull }; //  2.08757008419747316778E-9
		HK_ALIGN16(static const hkInt64 cosCoeff2[2]) = { 0xbe927e4f7eac4bc6ull, 0xbe927e4f7eac4bc6ull }; // -2.75573141792967388112E-7
		HK_ALIGN16(static const hkInt64 cosCoeff3[2]) = { 0x3efa01a019c844f5ull, 0x3efa01a019c844f5ull }; //  2.48015872888517045348E-5
		HK_ALIGN16(static const hkInt64 cosCoeff4[2]) = { 0xbf56c16c16c14f91ull, 0xbf56c16c16c14f91ull }; // -1.38888888888730564116E-3
		HK_ALIGN16(static const hkInt64 cosCoeff5[2]) = { 0x3fa555555555554bull, 0x3fa555555555554bull }; //  4.16666666666665929218E-2

		HK_ALIGN16(static const hkInt64 signMask[2])  = { 0x8000000000000000ull, 0x8000000000000000ull };
		HK_ALIGN16(static const hkInt64 fourDivPi[2]) = { 0x3FF45F306DC9C883ull, 0x3FF45F306DC9C883ull }; // 4 / Pi
		HK_ALIGN16(static const hkInt64 DP1[2])       = { 0xbfe921fb40000000ull, 0xbfe921fb40000000ull }; // -7.85398125648498535156E-1
		HK_ALIGN16(static const hkInt64 DP2[2])       = { 0xbe64442d00000000ull, 0xbe64442d00000000ull }; // -3.77489470793079817668E-8
		HK_ALIGN16(static const hkInt64 DP3[2])       = { 0xbce8469898cc5170ull, 0xbce8469898cc5170ull }; // -2.69515142907905952645E-15
		HK_ALIGN16(static const hkInt64 floatOne[2])  = { 0x3FF0000000000000ull, 0x3FF0000000000000ull }; // 1.0
		HK_ALIGN16(static const hkInt64 floatHalf[2]) = { 0x3FE0000000000000ull, 0x3FE0000000000000ull }; // 0.5
		HK_ALIGN16(static const hkInt32 intOne[4])    = { 0x00000001, 0x00000001, 0x00000001, 0x00000001 };

		__m128d x = inX;

		// get abs and sign
		__m128d sign_bit = x;
		x = _mm_andnot_pd( *(__m128d*)signMask, x);
		sign_bit = _mm_and_pd(sign_bit, *(__m128d*)signMask);

		// scale by 4/Pi
		__m128d y = _mm_mul_pd(x, *(__m128d*)fourDivPi);

		__m128i one = *(__m128i*)intOne;
		__m128i two = _mm_add_epi32(one,one);
		__m128i four = _mm_add_epi32(two,two);
		// store the integer part of y in emm2
		__m128i emm2 = _mm_cvttpd_epi32(y);
		// j=(j+1) & (~1)
		emm2 = _mm_add_epi32(emm2, one);
		emm2 = _mm_andnot_si128(one, emm2);
		y = _mm_cvtepi32_pd(emm2);
		// get the swap sign flag
		__m128i emm0 = _mm_and_si128(emm2, four);
		emm0 = _mm_slli_epi32(emm0, 29);
		emm0 = _mm_shuffle_epi32(emm0, _MM_SHUFFLE(1,1,0,0));
		// get the polynom selection mask 
		emm2 = _mm_and_si128(emm2, two);
		emm2 = _mm_cmpeq_epi32(emm2, _mm_setzero_si128());
		emm2 = _mm_shuffle_epi32(emm2, _MM_SHUFFLE(1,1,0,0));

		__m128d swap_sign_bit = _mm_castsi128_pd(emm0);
		__m128d poly_mask = _mm_castsi128_pd(emm2);
		sign_bit = _mm_xor_pd(sign_bit, swap_sign_bit);

		// The magic pass: Extended precision modular arithmetic
		//   x = ((x - y * DP1) - y * DP2) - y * DP3
		__m128d xmm1 = *(__m128d*)DP1;
		__m128d xmm2 = *(__m128d*)DP2;
		__m128d xmm3 = *(__m128d*)DP3;
		xmm1 = _mm_mul_pd(y, xmm1);
		xmm2 = _mm_mul_pd(y, xmm2);
		xmm3 = _mm_mul_pd(y, xmm3);
		x = _mm_add_pd(x, xmm1);
		x = _mm_add_pd(x, xmm2);
		x = _mm_add_pd(x, xmm3);

		__m128d z = _mm_mul_pd(x,x);

		// Evaluate the first polynom  (0 <= x <= Pi/4)
		y = *(__m128d*)cosCoeff0;
		y = _mm_mul_pd(y, z);
		y = _mm_add_pd(y, *(__m128d*)cosCoeff1);
		y = _mm_mul_pd(y, z);
		y = _mm_add_pd(y, *(__m128d*)cosCoeff2);
		y = _mm_mul_pd(y, z);
		y = _mm_add_pd(y, *(__m128d*)cosCoeff3);
		y = _mm_mul_pd(y, z);
		y = _mm_add_pd(y, *(__m128d*)cosCoeff4);
		y = _mm_mul_pd(y, z);
		y = _mm_add_pd(y, *(__m128d*)cosCoeff5);
		y = _mm_mul_pd(y, z);
		y = _mm_mul_pd(y, z);
		__m128d tmp = _mm_mul_pd(z, *(__m128d*)floatHalf);
		y = _mm_sub_pd(y, tmp);
		y = _mm_add_pd(y, *(__m128d*)floatOne);

		// Evaluate the second polynom  (Pi/4 <= x <= 0)
		__m128d y2 = *(__m128d*)sinCoeff0;
		y2 = _mm_mul_pd(y2, z);
		y2 = _mm_add_pd(y2, *(__m128d*)sinCoeff1);
		y2 = _mm_mul_pd(y2, z);
		y2 = _mm_add_pd(y2, *(__m128d*)sinCoeff2);
		y2 = _mm_mul_pd(y2, z);
		y2 = _mm_add_pd(y2, *(__m128d*)sinCoeff3);
		y2 = _mm_mul_pd(y2, z);
		y2 = _mm_add_pd(y2, *(__m128d*)sinCoeff4);
		y2 = _mm_mul_pd(y2, z);
		y2 = _mm_add_pd(y2, *(__m128d*)sinCoeff5);
		y2 = _mm_mul_pd(y2, z);
		y2 = _mm_mul_pd(y2, x);
		y2 = _mm_add_pd(y2, x);

		// select the correct result from the two polynoms
#if HK_SSE_VERSION >= 0x41
		y = _mm_blendv_pd(y,y2,poly_mask);
#else
		y2 = _mm_and_pd(poly_mask, y2);
		y = _mm_andnot_pd(poly_mask, y);
		y = _mm_or_pd(y,y2);
#endif
		// update the sign
		y = _mm_xor_pd(y, sign_bit);

		return y;
	}

	/// Adapted from the book "Methods and Programs for Mathematical Functions",
	/// Stephen Lloyd Baluk Moshier, Prentice-Hall, 1989
	///
	/// A polynomial of the form x + x**3 P(x**2)
	/// is used for |x| in the interval [0, 0.5].  If |x| > 0.5 it is
	/// transformed by the identity
	///
	///    asin(x) = pi/2 - 2 asin( sqrt( (1-x)/2 ) ).
	///
	/// ACCURACY: matches cmath on MSVC
	///
	///                      Relative error:
	/// arithmetic   domain      peak         rms
	///    IEEE     -1, 1       2.5e-7       5.0e-8
	///
	/// PERFORMANCE: About 8x faster than ::asinf for 4 simultaneous values

	HK_FORCE_INLINE static __m128 HK_CALL quadAsin(const __m128& xx) 
	{
		HK_ALIGN16(static const hkInt32 signMask[4])     = { 0x80000000, 0x80000000, 0x80000000, 0x80000000 };
		HK_ALIGN16(static const hkInt32 linearLimit[4])  = { 0x38D1B717, 0x38D1B717, 0x38D1B717, 0x38D1B717 }; // 1e-4
		HK_ALIGN16(static const hkInt32 floatOne[4])     = { 0x3F800000, 0x3F800000, 0x3F800000, 0x3F800000 }; // 1.0
		HK_ALIGN16(static const hkInt32 floatHalf[4])    = { 0x3F000000, 0x3F000000, 0x3F000000, 0x3F000000 }; // 0.5
		HK_ALIGN16(static const hkInt32 piover2[4])      = { 0x3FC90FDB, 0x3FC90FDB, 0x3FC90FDB, 0x3FC90FDB }; // pi/2
		HK_ALIGN16(static const hkInt32 coeff4[4])       = { 0x3D2CB352, 0x3D2CB352, 0x3D2CB352, 0x3D2CB352 }; // 4.2163199048E-2
		HK_ALIGN16(static const hkInt32 coeff3[4])       = { 0x3CC617E3, 0x3CC617E3, 0x3CC617E3, 0x3CC617E3 }; // 2.4181311049E-2
		HK_ALIGN16(static const hkInt32 coeff2[4])       = { 0x3D3A3EC7, 0x3D3A3EC7, 0x3D3A3EC7, 0x3D3A3EC7 }; // 4.5470025998E-2
		HK_ALIGN16(static const hkInt32 coeff1[4])       = { 0x3D9980F6, 0x3D9980F6, 0x3D9980F6, 0x3D9980F6 }; // 7.4953002686E-2
		HK_ALIGN16(static const hkInt32 coeff0[4])       = { 0x3E2AAAE4, 0x3E2AAAE4, 0x3E2AAAE4, 0x3E2AAAE4 }; // 1.6666752422E-1

		__m128 a = _mm_andnot_ps( *(__m128*)signMask, xx);
		__m128 sign = _mm_and_ps(*(__m128*)signMask, xx);

		// linear approximation
		__m128 lessLimit = _mm_cmplt_ps(a,*(__m128*)linearLimit);

		// a > 0.5
		__m128 zGT = _mm_mul_ps(*(__m128*)floatHalf, _mm_sub_ps(*(__m128*)floatOne, a));
		__m128 xGT = _mm_sqrt_ps(zGT);

		// a <= 0.5
		__m128 xLE = a;
		__m128 zLE = _mm_mul_ps(xLE,xLE);

		// select polynom
		__m128 rangeMask = _mm_cmpgt_ps(a, *(__m128*)floatHalf);
#if HK_SSE_VERSION >= 0x41
		__m128 x = _mm_blendv_ps(xLE,xGT,rangeMask);
		__m128 z = _mm_blendv_ps(zLE,zGT,rangeMask);
#else
		__m128 x = _mm_or_ps(_mm_andnot_ps(rangeMask, xLE),_mm_and_ps(rangeMask, xGT));
		__m128 z = _mm_or_ps(_mm_andnot_ps(rangeMask, zLE),_mm_and_ps(rangeMask, zGT));
#endif

		// zz = (((((c4*z)+c3)*z+c2)*z+c1)*z+c0)*z*x+x
		__m128 zz = _mm_mul_ps(*(__m128*)coeff4, z);
		zz = _mm_add_ps(*(__m128*)coeff3, zz);
		zz = _mm_mul_ps(zz,z);
		zz = _mm_add_ps(*(__m128*)coeff2, zz);
		zz = _mm_mul_ps(zz,z);
		zz = _mm_add_ps(*(__m128*)coeff1, zz);
		zz = _mm_mul_ps(zz,z);
		zz = _mm_add_ps(*(__m128*)coeff0, zz);
		zz = _mm_mul_ps(zz,z);
		zz = _mm_mul_ps(zz,x);
		zz = _mm_add_ps(zz,x);

		// transform
		__m128 zzGT = _mm_add_ps(zz,zz);
		zzGT = _mm_sub_ps(*(__m128*)piover2,zzGT);
#if HK_SSE_VERSION >= 0x41
		zz = _mm_blendv_ps(zz,zzGT,rangeMask);
#else
		zz = _mm_or_ps(_mm_andnot_ps(rangeMask, zz),_mm_and_ps(rangeMask, zzGT));
#endif

		// select linear approximation
#if HK_SSE_VERSION >= 0x41
		zz = _mm_blendv_ps(zz,a,lessLimit);
#else
		zz = _mm_or_ps(_mm_andnot_ps(lessLimit, zz),_mm_and_ps(lessLimit, a));
#endif

		// update the sign
		zz = _mm_xor_ps(zz, sign);

		return zz;
	}

	/// Double precision version of above except that it uses
	/// a rational function of the form x + x**3 P(x**2)/Q(x**2)
	///
	///                      Relative error:
	/// arithmetic   domain        peak       rms
	///    IEEE     -1, 1       1.9e-16     5.4e-17
	///
	/// PERFORMANCE: About 2x faster than ::asin for 2 simultaneous values

	HK_FORCE_INLINE static __m128d HK_CALL twoAsin(const __m128d& xx) 
	{
		HK_ALIGN16(static const hkInt64 signMask[2])     = { 0x8000000000000000ull, 0x8000000000000000ull };
		HK_ALIGN16(static const hkInt64 linearLimit[2])  = { 0x3E45798EE2308C3Aull, 0x3E45798EE2308C3Aull }; // 1e-8
		HK_ALIGN16(static const hkInt64 floatOne[2])     = { 0x3FF0000000000000ull, 0x3FF0000000000000ull }; // 1.0
		HK_ALIGN16(static const hkInt64 limit[2])        = { 0x3FE4000000000000ull, 0x3FE4000000000000ull }; // 0.625
		HK_ALIGN16(static const hkInt64 piover4[2])      = { 0x3FE921FB54442D18ull, 0x3FE921FB54442D18ull }; // pi/4
		HK_ALIGN16(static const hkInt64 morebits[2])     = { 0x3C91A62633145C07ull, 0x3C91A62633145C07ull }; // 6.123233995736765886130E-17
		HK_ALIGN16(static const hkInt64 R0[2])           = { 0x3f684fc3988e9f08ull, 0x3f684fc3988e9f08ull }; //  2.967721961301243206100E-3
		HK_ALIGN16(static const hkInt64 R1[2])           = { 0xbfe2079259f9290full, 0xbfe2079259f9290full }; // -5.634242780008963776856E-1
		HK_ALIGN16(static const hkInt64 R2[2])           = { 0x401bdff5baf33e6aull, 0x401bdff5baf33e6aull }; //  6.968710824104713396794E0
		HK_ALIGN16(static const hkInt64 R3[2])           = { 0xc03991aaac01ab68ull, 0xc03991aaac01ab68ull }; // -2.556901049652824852289E1
		HK_ALIGN16(static const hkInt64 R4[2])           = { 0x403c896240f3081dull, 0x403c896240f3081dull }; //  2.853665548261061424989E1
		HK_ALIGN16(static const hkInt64 S1[2])           = { 0xc035f2a2b6bf5d8cull, 0xc035f2a2b6bf5d8cull }; // -2.194779531642920639778E1
		HK_ALIGN16(static const hkInt64 S2[2])           = { 0x40626219af6a7f42ull, 0x40626219af6a7f42ull }; //  1.470656354026814941758E2
		HK_ALIGN16(static const hkInt64 S3[2])           = { 0xc077fe08959063eeull, 0xc077fe08959063eeull }; // -3.838770957603691357202E2
		HK_ALIGN16(static const hkInt64 S4[2])           = { 0x40756709b0b644beull, 0x40756709b0b644beull }; //  3.424398657913078477438E2
		HK_ALIGN16(static const hkInt64 P0[2])           = { 0x3f716b9b0bd48ad3ull, 0x3f716b9b0bd48ad3ull }; //  4.253011369004428248960E-3
		HK_ALIGN16(static const hkInt64 P1[2])           = { 0xbfe34341333e5c16ull, 0xbfe34341333e5c16ull }; // -6.019598008014123785661E-1
		HK_ALIGN16(static const hkInt64 P2[2])           = { 0x4015c74b178a2dd9ull, 0x4015c74b178a2dd9ull }; //  5.444622390564711410273E0
		HK_ALIGN16(static const hkInt64 P3[2])           = { 0xc0304331de27907bull, 0xc0304331de27907bull }; // -1.626247967210700244449E1
		HK_ALIGN16(static const hkInt64 P4[2])           = { 0x40339007da779259ull, 0x40339007da779259ull }; //  1.956261983317594739197E1
		HK_ALIGN16(static const hkInt64 P5[2])           = { 0xc020656c06ceafd5ull, 0xc020656c06ceafd5ull }; // -8.198089802484824371615E0
		HK_ALIGN16(static const hkInt64 Q1[2])           = { 0xc02d7b590b5e0eabull, 0xc02d7b590b5e0eabull }; // -1.474091372988853791896E1
		HK_ALIGN16(static const hkInt64 Q2[2])           = { 0x40519fc025fe9054ull, 0x40519fc025fe9054ull }; //  7.049610280856842141659E1
		HK_ALIGN16(static const hkInt64 Q3[2])           = { 0xc06265bb6d3576d7ull, 0xc06265bb6d3576d7ull }; // -1.471791292232726029859E2
		HK_ALIGN16(static const hkInt64 Q4[2])           = { 0x4061705684ffbf9dull, 0x4061705684ffbf9dull }; //  1.395105614657485689735E2
		HK_ALIGN16(static const hkInt64 Q5[2])           = { 0xc04898220a3607acull, 0xc04898220a3607acull }; // -4.918853881490881290097E1


		__m128d a = _mm_andnot_pd( *(__m128d*)signMask, xx);
		__m128d sign = _mm_and_pd(*(__m128d*)signMask, xx);

		// linear approximation
		__m128d lessLimit = _mm_cmplt_pd(a,*(__m128d*)linearLimit);

		__m128d selectGT = _mm_cmpgt_pd(a, *(__m128d*)limit);

		// a > 0.625
		__m128d zGT;
		{
			__m128d zz = _mm_sub_pd(*(__m128d*)floatOne, a);

			__m128d polR = _mm_mul_pd(*(__m128d*)R0, zz);
			polR = _mm_add_pd(polR, *(__m128d*)R1);
			polR = _mm_mul_pd(polR, zz);
			polR = _mm_add_pd(polR, *(__m128d*)R2);
			polR = _mm_mul_pd(polR, zz);
			polR = _mm_add_pd(polR, *(__m128d*)R3);
			polR = _mm_mul_pd(polR, zz);
			polR = _mm_add_pd(polR, *(__m128d*)R4);
			polR = _mm_mul_pd(polR, zz);

			__m128d polS = zz; // coeff0 = 1
			polS = _mm_add_pd(polS, *(__m128d*)S1);
			polS = _mm_mul_pd(polS, zz);
			polS = _mm_add_pd(polS, *(__m128d*)S2);
			polS = _mm_mul_pd(polS, zz);
			polS = _mm_add_pd(polS, *(__m128d*)S3);
			polS = _mm_mul_pd(polS, zz);
			polS = _mm_add_pd(polS, *(__m128d*)S4);

			__m128d p = _mm_div_pd(polR,polS);
			zz = _mm_sqrt_pd(_mm_add_pd(zz,zz));
			zGT = _mm_sub_pd(*(__m128d*)piover4, zz);
			zz = _mm_sub_pd(_mm_mul_pd(zz,p),*(__m128d*)morebits);
			zGT = _mm_sub_pd(zGT,zz);
			zGT = _mm_add_pd(zGT, *(__m128d*)piover4);
		}

		// a <= 0.625
		__m128d zLT;
		{
			__m128d zz = _mm_mul_pd(a,a);

			__m128d polP = _mm_mul_pd(*(__m128d*)P0, zz);
			polP = _mm_add_pd(polP, *(__m128d*)P1);
			polP = _mm_mul_pd(polP, zz);
			polP = _mm_add_pd(polP, *(__m128d*)P2);
			polP = _mm_mul_pd(polP, zz);
			polP = _mm_add_pd(polP, *(__m128d*)P3);
			polP = _mm_mul_pd(polP, zz);
			polP = _mm_add_pd(polP, *(__m128d*)P4);
			polP = _mm_mul_pd(polP, zz);
			polP = _mm_add_pd(polP, *(__m128d*)P5);
			polP = _mm_mul_pd(polP, zz);

			__m128d polQ = zz; // coeff0 = 1
			polQ = _mm_add_pd(polQ, *(__m128d*)Q1);
			polQ = _mm_mul_pd(polQ, zz);
			polQ = _mm_add_pd(polQ, *(__m128d*)Q2);
			polQ = _mm_mul_pd(polQ, zz);
			polQ = _mm_add_pd(polQ, *(__m128d*)Q3);
			polQ = _mm_mul_pd(polQ, zz);
			polQ = _mm_add_pd(polQ, *(__m128d*)Q4);
			polQ = _mm_mul_pd(polQ, zz);
			polQ = _mm_add_pd(polQ, *(__m128d*)Q5);

			zLT = _mm_div_pd(polP,polQ);
			zLT = _mm_mul_pd(a,zLT);
			zLT = _mm_add_pd(a,zLT);
		}

		__m128d z;

		// select case and linear approximation
#if HK_SSE_VERSION >= 0x41
		z = _mm_blendv_pd(zLT,zGT,selectGT);
		z = _mm_blendv_pd(z,a,lessLimit);
#else
		z = _mm_or_pd(_mm_andnot_pd(selectGT, zLT),_mm_and_pd(selectGT, zGT));
		z = _mm_or_pd(_mm_andnot_pd(lessLimit, z),_mm_and_pd(lessLimit, a));
#endif

		// update the sign
		z = _mm_xor_pd(z, sign);

		return z;
	}



	/// Properties see quadSinApproximation
	HK_FORCE_INLINE static __m128 HK_CALL quadCosApproximation(const __m128& x)
	{
		// cos(x) = sin(x + pi/2)
		static HK_ALIGN16( const hkUint32 pihalf[4] ) = { 0x3FC90FDB, 0x3FC90FDB, 0x3FC90FDB, 0x3FC90FDB };
		__m128 xx = _mm_add_ps(x, *(__m128*)&pihalf);
		return quadSinApproximation(xx);
	}

	/// Properties see quadSinApproximation
	HK_FORCE_INLINE static __m128d HK_CALL twoCosApproximation(const __m128d& x)
	{
		// cos(x) = sin(x + pi/2)
		static HK_ALIGN16( const hkUint64 pihalf[2] ) = { 0x3FF921FB54442D18ull, 0x3FF921FB54442D18ull };
		__m128d xx = _mm_add_pd(x, *(__m128d*)&pihalf);
		return twoSinApproximation(xx);
	}

	/// Properties see quadSin
	HK_FORCE_INLINE static __m128 HK_CALL quadCos(const __m128& x)
	{
		// cos(x) = sin(x + pi/2)
		static HK_ALIGN16( const hkUint32 pihalf[4] ) = { 0x3FC90FDB, 0x3FC90FDB, 0x3FC90FDB, 0x3FC90FDB };
		__m128 xx = _mm_add_ps(x, *(__m128*)&pihalf);
		return quadSin(xx);
	}

	/// Properties see twoSin
	HK_FORCE_INLINE static __m128d HK_CALL twoCos(const __m128d& x)
	{
		// cos(x) = sin(x + pi/2)
		static HK_ALIGN16( const hkUint64 pihalf[2] ) = { 0x3FF921FB54442D18ull, 0x3FF921FB54442D18ull };
		__m128d xx = _mm_add_pd(x, *(__m128d*)&pihalf);
		return twoSin(xx);
	}

	HK_FORCE_INLINE static __m128 HK_CALL quadAcos(const __m128& xx) 
	{
		// acos(x) = pi/2 - asin(x)
		HK_ALIGN16(static const hkInt32 piover2[4])      = { 0x3FC90FDB, 0x3FC90FDB, 0x3FC90FDB, 0x3FC90FDB };
		__m128 x = _mm_sub_ps(*(__m128*)piover2, quadAsin(xx));
		return x;
	}

	HK_FORCE_INLINE static __m128d HK_CALL twoAcos(const __m128d& xx) 
	{
		// acos(x) = pi/2 - asin(x)
		HK_ALIGN16(static const hkInt64 piover2[2])      = { 0x3FF921FB54442D18ull, 0x3FF921FB54442D18ull };
		__m128d x = _mm_sub_pd(*(__m128d*)piover2, twoAsin(xx));
		return x;
	}

	/// Calc cos/sin at the same time: xyzw -> sin(x)cos(y)sin(z)cos(w)
	/// Properties see quadSinApproximation
	HK_FORCE_INLINE static __m128 HK_CALL quadSinCosApproximation(const __m128& x)
	{
		// cos(x) = sin(x + pi/2)
		static HK_ALIGN16( const hkUint32 offset[4] ) = { 0x00000000, 0x3FC90FDB, 0x00000000, 0x3FC90FDB };
		__m128 xx = _mm_add_ps(x, *(__m128*)&offset);
		return quadSinApproximation(xx);
	}

	/// Calc cos/sin at the same time: xy -> sin(x)cos(y)
	/// Properties see twoSinApproximation
	HK_FORCE_INLINE static __m128d HK_CALL twoSinCosApproximation(const __m128d& x)
	{
		// cos(x) = sin(x + pi/2)
		static HK_ALIGN16( const hkUint64 offset[2] ) = { 0x0000000000000000ull, 0x3FF921FB54442D18ull };
		__m128d xx = _mm_add_pd(x, *(__m128d*)&offset);
		return twoSinApproximation(xx);
	}

	/// Calc cos/sin at the same time: xyzw -> sin(x)cos(y)sin(z)cos(w)
	/// Properties see quadSin
	HK_FORCE_INLINE static __m128 HK_CALL quadSinCos(const __m128& x)
	{
		// cos(x) = sin(x + pi/2)
		static HK_ALIGN16( const hkUint32 offset[4] ) = { 0x00000000, 0x3FC90FDB, 0x00000000, 0x3FC90FDB };
		__m128 xx = _mm_add_ps(x, *(__m128*)&offset);
		return quadSin(xx);
	}

	/// Calc cos/sin at the same time: xy -> sin(x)cos(y)
	/// Properties see twoSin
	HK_FORCE_INLINE static __m128d HK_CALL twoSinCos(const __m128d& x)
	{
		// cos(x) = sin(x + pi/2)
		static HK_ALIGN16( const hkUint64 offset[2] ) = { 0x0000000000000000ull, 0x3FF921FB54442D18ull };
		__m128d xx = _mm_add_pd(x, *(__m128d*)&offset);
		return twoSin(xx);
	}

	/// Calc acos/asin at the same time: xyzw -> asin(x)acos(y)asin(z)acos(w)
	/// Properties see quadAsin
	HK_FORCE_INLINE static __m128 HK_CALL quadAsinAcos(const __m128& x)
	{
		// acos(x) = pi/2 - asin(x)
		HK_ALIGN16(static const hkInt32 piover2[4])      = { 0x3FC90FDB, 0x3FC90FDB, 0x3FC90FDB, 0x3FC90FDB };
		__m128 asinx = quadAsin(x);
		__m128 acosx = _mm_sub_ps(*(__m128*)piover2, asinx);
#if HK_SSE_VERSION >= 0x41
		return _mm_blend_ps(asinx,acosx,0xA);
#else
		HK_ALIGN16(static const hkInt32 selectGT[4])     = { 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF };
		return _mm_or_ps(_mm_andnot_ps(*(__m128*)selectGT, asinx),_mm_and_ps(*(__m128*)selectGT, acosx));
#endif
	}

	/// Calc acos/asin at the same time: xy -> asin(x)acos(y)
	/// Properties see twoAsin
	HK_FORCE_INLINE static __m128d HK_CALL twoAsinAcos(const __m128d& x)
	{
		// acos(x) = pi/2 - asin(x)
		HK_ALIGN16(static const hkInt64 piover2[2])      = { 0x3FF921FB54442D18ull, 0x3FF921FB54442D18ull };
		__m128d asinx = twoAsin(x);
		__m128d acosx = _mm_sub_pd(*(__m128d*)piover2, asinx);
		return _mm_move_sd(acosx, asinx);
	}

#	define HK_MATH_sin
	HK_FORCE_INLINE static hkFloat32 HK_CALL sin (const hkFloat32 r) 
	{ 
		__m128 rr = _mm_load_ss(&r);
		__m128 s = quadSin(rr);
		return _mm_cvtss_f32(s);
	}
	HK_FORCE_INLINE static hkDouble64 HK_CALL sin (const hkDouble64 r) 
	{ 
		__m128d rr = _mm_load_sd(&r);
		__m128d s = twoSin(rr);
		return HK_M128(s).m128d_f64[0];
	}

#	define HK_MATH_cos
	HK_FORCE_INLINE static hkFloat32 HK_CALL cos (const hkFloat32 r) 
	{ 
		__m128 rr = _mm_load_ss(&r);
		__m128 c = quadCos(rr);
		return _mm_cvtss_f32(c);
	}
	HK_FORCE_INLINE static hkDouble64 HK_CALL cos (const hkDouble64 r) 
	{ 
		__m128d rr = _mm_load_sd(&r);
		__m128d s = twoCos(rr);
		return HK_M128(s).m128d_f64[0];
	}

#	define HK_MATH_asin
	HK_FORCE_INLINE static hkFloat32 HK_CALL asin(const hkFloat32 r)
	{
		HK_ALIGN16(static const hkInt32 floatOne[4])     = { 0x3F800000, 0x3F800000, 0x3F800000, 0x3F800000 }; //  1.0
		HK_ALIGN16(static const hkInt32 floatMOne[4])    = { 0xBF800000, 0xBF800000, 0xBF800000, 0xBF800000 }; // -1.0

		// be generous about numbers outside range
		HK_ASSERT(0x286a6f5f,  hkMath::fabs(r) < 1.001f ); // assert imported from default impl
		__m128 rr = _mm_load_ss(&r);
		rr = _mm_max_ps(rr, *(__m128*)floatMOne);
		rr = _mm_min_ps(rr, *(__m128*)floatOne);
		__m128 s = quadAsin(rr);
		return _mm_cvtss_f32(s);
	}
	HK_FORCE_INLINE static hkDouble64 HK_CALL asin(const hkDouble64 r)
	{
		HK_ALIGN16(static const hkInt64 floatOne[2])     = { 0x3FF0000000000000ull, 0x3FF0000000000000ull }; //  1.0
		HK_ALIGN16(static const hkInt64 floatMOne[2])    = { 0xBFF0000000000000ull, 0xBFF0000000000000ull }; // -1.0

		// be generous about numbers outside range
		HK_ASSERT(0x286a6f5f,  hkMath::fabs(r) < 1.001 ); // assert imported from default impl
		__m128d rr = _mm_load_sd(&r);
		rr = _mm_max_pd(rr, *(__m128d*)floatMOne);
		rr = _mm_min_pd(rr, *(__m128d*)floatOne);
		__m128d s = twoAsin(rr);
		return HK_M128(s).m128d_f64[0];
	}

#	define HK_MATH_acos
	HK_FORCE_INLINE static hkFloat32 HK_CALL acos(const hkFloat32 r)
	{
		HK_ALIGN16(static const hkInt32 floatOne[4])     = { 0x3F800000, 0x3F800000, 0x3F800000, 0x3F800000 }; //  1.0
		HK_ALIGN16(static const hkInt32 floatMOne[4])    = { 0xBF800000, 0xBF800000, 0xBF800000, 0xBF800000 }; // -1.0

		// be generous about numbers outside range
		HK_ASSERT(0x41278654,  hkMath::fabs(r) < 1.001f ); // assert imported from default impl
		__m128 rr = _mm_load_ss(&r);
		rr = _mm_max_ps(rr, *(__m128*)floatMOne);
		rr = _mm_min_ps(rr, *(__m128*)floatOne);
		__m128 s = quadAcos(rr);
		return _mm_cvtss_f32(s);
	}
	HK_FORCE_INLINE static hkDouble64 HK_CALL acos(const hkDouble64 r)
	{
		HK_ALIGN16(static const hkInt64 floatOne[2])     = { 0x3FF0000000000000ull, 0x3FF0000000000000ull }; //  1.0
		HK_ALIGN16(static const hkInt64 floatMOne[2])    = { 0xBFF0000000000000ull, 0xBFF0000000000000ull }; // -1.0

		// be generous about numbers outside range
		HK_ASSERT(0x41278654,  hkMath::fabs(r) < 1.001 ); // assert imported from default impl
		__m128d rr = _mm_load_sd(&r);
		rr = _mm_max_pd(rr, *(__m128d*)floatMOne);
		rr = _mm_min_pd(rr, *(__m128d*)floatOne);
		__m128d s = twoAcos(rr);
		return HK_M128(s).m128d_f64[0];
	}



	// Returns the number of bits set to one in the given number
#	define HK_MATH_countBitsSet
#if HK_SSE_VERSION >= 0x42
	HK_FORCE_INLINE static int HK_CALL countBitsSet(hkUint32 number)
	{
		return  _mm_popcnt_u32(number);
	}
#elif HK_SSE_VERSION >= 0x31
	HK_FORCE_INLINE static int HK_CALL countBitsSet(hkUint32 number)
	{
		const __m128i mask_lo = _mm_set1_epi8(0x0F);
		const __m128i mask_popcnt = _mm_setr_epi8(0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4);

		__m128i cnt = _mm_cvtsi32_si128(number);
		__m128i lo = _mm_and_si128(cnt, mask_lo);
		__m128i hi = _mm_and_si128(_mm_srli_epi16(cnt, 4), mask_lo);
		lo = _mm_shuffle_epi8(mask_popcnt, lo);
		hi = _mm_shuffle_epi8(mask_popcnt, hi);
		cnt = _mm_add_epi8(lo, hi);
		// Horizontally sum up byte counters
		__m128i sum = _mm_sad_epu8(cnt, _mm_setzero_si128());
		// Horizontally add 32-bit accumulators
		sum = _mm_add_epi32(_mm_shuffle_epi32(sum, _MM_SHUFFLE(1,0,3,2)), sum);
		return _mm_cvtsi128_si32(sum);
	}
#else
	HK_FORCE_INLINE static int HK_CALL countBitsSet(hkUint32 number)
	{
		const __m128i mask1 = _mm_set1_epi8(0x55);
		const __m128i mask2 = _mm_set1_epi8(0x33);
		const __m128i mask4 = _mm_set1_epi8(0x0F);

		__m128i cnt = _mm_cvtsi32_si128(number);
		cnt = _mm_add_epi8( _mm_and_si128(cnt, mask1), _mm_and_si128(_mm_srli_epi16(cnt, 1), mask1) );
		cnt = _mm_add_epi8( _mm_and_si128(cnt, mask2), _mm_and_si128(_mm_srli_epi16(cnt, 2), mask2) );
		cnt = _mm_and_si128( _mm_add_epi8(cnt, _mm_srli_epi16(cnt, 4)), mask4 );
		// Horizontally sum up byte counters
		__m128i sum = _mm_sad_epu8(cnt, _mm_setzero_si128());
		// Horizontally add 32-bit accumulators
		sum = _mm_add_epi32(_mm_shuffle_epi32(sum, _MM_SHUFFLE(1,0,3,2)), sum);
		return _mm_cvtsi128_si32(sum);
	}
#endif

#	define HK_MATH_isPower2
	HK_FORCE_INLINE static bool isPower2(unsigned int v)
	{
		return countBitsSet(v)==1;
	}
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
