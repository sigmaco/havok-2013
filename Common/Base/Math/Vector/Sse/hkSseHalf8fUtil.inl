/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#if defined(HK_HALF_IS_FLOAT)
#error not implemented
#endif

namespace hkHalf8Util
{

template<hkMathRoundingMode R, hkMathIoMode I>
/*static*/ HK_FORCE_INLINE void pack( hkVector4fParameter v0, hkVector4fParameter v1, hkHalf* HK_RESTRICT packedHalf8 )
{
	hkVector4f vs0, vs1; 
	if ( R == HK_ROUND_NEAREST )
	{
		const hkVector4 packHalf = hkVector4::getConstant<HK_QUADREAL_PACK_HALF>();
		vs0.setMul( v0, packHalf);
		vs1.setMul( v1, packHalf);
	}
	else
	{
		vs0 = v0;
		vs1 = v1;
	}

	const __m128i tmp0 = _mm_srai_epi32( _mm_castps_si128(vs0.m_quad), 16 );
	const __m128i tmp1 = _mm_srai_epi32( _mm_castps_si128(vs1.m_quad), 16 );
	const __m128i result = _mm_packs_epi32(tmp0, tmp1);
	switch (I)
	{
		case HK_IO_NOT_CACHED:
		{
			HK_MATH_ASSERT(0x64216c2f, ( ((hkUlong)packedHalf8) & 0xf ) == 0, "pointer must be aligned for SIMD.");
			_mm_stream_si128((__m128i*)packedHalf8, result);
		}
		break;
		case HK_IO_SIMD_ALIGNED:
		{
			HK_MATH_ASSERT(0x64216c2f, ( ((hkUlong)packedHalf8) & 0xf ) == 0, "pointer must be aligned for SIMD.");
			_mm_store_si128((__m128i*)packedHalf8, result);
		}
		break;
		default:
		{
			_mm_storeu_si128((__m128i*)packedHalf8, result);
		}
		break;
	}
}

/*static*/ HK_FORCE_INLINE void unpackFirst( hkVector4fParameter packedHalf8, hkVector4f& v0)
{
	const __m128i zero = _mm_setzero_si128();
	const __m128i r    = _mm_unpacklo_epi16(zero, _mm_castps_si128(packedHalf8.m_quad));
	v0.m_quad = _mm_castsi128_ps(r);
}

/*static*/ HK_FORCE_INLINE void unpackSecond( hkVector4fParameter packedHalf8, hkVector4f& v1)
{
	const __m128i zero = _mm_setzero_si128();
	const __m128i r    = _mm_unpackhi_epi16(zero, _mm_castps_si128(packedHalf8.m_quad));
	v1.m_quad = _mm_castsi128_ps(r);
}


template<hkMathIoMode I>
/*static*/ HK_FORCE_INLINE void unpack( const hkHalf* HK_RESTRICT packedHalf8, hkVector4f* HK_RESTRICT v0, hkVector4f* HK_RESTRICT v1 )
{
	__m128i halfs;
	switch(I)
	{
		case HK_IO_NOT_CACHED:
#if HK_SSE_VERSION >= 0x41
		{
			HK_MATH_ASSERT(0x64216c2f, ( ((hkUlong)packedHalf8) & 0xf ) == 0, "pointer must be aligned for SIMD.");
			halfs = _mm_stream_load_si128((__m128i*)packedHalf8);
		}
		break;
#endif
		case HK_IO_SIMD_ALIGNED:
		{
			HK_MATH_ASSERT(0x64216c2f, ( ((hkUlong)packedHalf8) & 0xf ) == 0, "pointer must be aligned for SIMD.");
			halfs = _mm_load_si128((const __m128i*)packedHalf8);
		}
		break;
		default:
		{
			halfs = _mm_loadu_si128((const __m128i*)packedHalf8);
		}
		break;
	}
	const __m128i zero = _mm_setzero_si128();
	const __m128i rl   = _mm_unpacklo_epi16(zero, halfs);
	const __m128i rh   = _mm_unpackhi_epi16(zero, halfs);
	v0->m_quad = _mm_castsi128_ps(rl);
	v1->m_quad = _mm_castsi128_ps(rh);
}


template<hkMathRoundingMode A>
/*static*/ HK_FORCE_INLINE void packInterleaved( hkVector4fParameter v0, hkVector4fParameter v1, hkVector4f& packedHalf8 )
{
	hkVector4f vs0, vs1; 
	if ( A == HK_ROUND_NEAREST )
	{
		const hkVector4 packHalf = hkVector4::getConstant<HK_QUADREAL_PACK_HALF>();
		vs0.setMul( v0, packHalf);
		vs1.setMul( v1, packHalf);
	}
	else
	{
		vs0 = v0;
		vs1 = v1;
	}

	const __m128i vs0sh = _mm_slli_epi32(_mm_srli_epi32( _mm_castps_si128( vs0.m_quad ), 16), 16 );
	const __m128i vs1sh = _mm_srli_epi32( _mm_castps_si128( vs1.m_quad ), 16 );
		
	packedHalf8.m_quad = _mm_or_ps( _mm_castsi128_ps(vs0sh), _mm_castsi128_ps(vs1sh) );
}

/*static*/ HK_FORCE_INLINE void unpackFirstInterleaved( hkVector4fParameter packedHalf8, hkVector4f& v0 )
{
	v0.m_quad = _mm_castsi128_ps( _mm_slli_epi32(_mm_srli_epi32( _mm_castps_si128( packedHalf8.m_quad ), 16), 16 ) );
}

/*static*/ HK_FORCE_INLINE void unpackSecondInterleaved( hkVector4fParameter packedHalf8, hkVector4f& v1 )
{
	v1.m_quad = _mm_castsi128_ps( _mm_slli_epi32( _mm_castps_si128( packedHalf8.m_quad ), 16) );
}

/*static*/ HK_FORCE_INLINE void unpackInterleaved( hkVector4fParameter packedHalf8, hkVector4f* HK_RESTRICT v0, hkVector4f* HK_RESTRICT v1 )
{
	unpackFirstInterleaved( packedHalf8, *v0 );
	unpackSecondInterleaved( packedHalf8, *v1 );
}

} // namespace hkHalf8Util

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
