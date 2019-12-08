/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

namespace hkHalf8Util
{

template<hkMathRoundingMode R, hkMathIoMode I>
/*static*/ HK_FORCE_INLINE void pack( hkVector4dParameter v0, hkVector4dParameter v1, hkHalf* HK_RESTRICT packedHalf8 )
{
	v0.store<4, I, R>( packedHalf8 );
	v1.store<4, I, R>( packedHalf8 + 4 );
}


/*static*/ HK_FORCE_INLINE void unpackFirst( hkVector4dParameter packedHalf8, hkVector4d& v0 )
{
	v0.load<4, HK_IO_SIMD_ALIGNED>( (hkHalf*) &packedHalf8 );
}

/*static*/ HK_FORCE_INLINE void unpackSecond( hkVector4dParameter packedHalf8, hkVector4d& v1 )
{
	v1.load<4, HK_IO_SIMD_ALIGNED>( ((hkHalf*) &packedHalf8) + 4 );
}

template<hkMathIoMode I>
/*static*/ HK_FORCE_INLINE void unpack( const hkHalf* HK_RESTRICT packedHalf8, hkVector4d* HK_RESTRICT v0, hkVector4d* HK_RESTRICT v1 )
{
	v0->load<4, I>( packedHalf8 );
	v1->load<4, I>( packedHalf8 + 4 );
}

template<hkMathRoundingMode A>
/*static*/ HK_FORCE_INLINE void packInterleaved( hkVector4dParameter v0, hkVector4dParameter v1, hkVector4d& packedHalf8 )
{
	HK_ALIGN_DOUBLE(hkHalf halves[8]);

	v0.store<4,HK_IO_SIMD_ALIGNED,A>(halves);
	v1.store<4,HK_IO_SIMD_ALIGNED,A>(halves+4);

	hkHalf* HK_RESTRICT outInterleaved = (hkHalf* HK_RESTRICT)&packedHalf8;

	outInterleaved[0] = halves[0];
	outInterleaved[1] = halves[4];
	outInterleaved[2] = halves[1];
	outInterleaved[3] = halves[5];
	outInterleaved[4] = halves[2];
	outInterleaved[5] = halves[6];
	outInterleaved[6] = halves[3];
	outInterleaved[7] = halves[7];
}

/*static*/ HK_FORCE_INLINE void unpackFirstInterleaved( hkVector4dParameter packedHalf8, hkVector4d& v0 )
{
	HK_ALIGN_DOUBLE(hkHalf halves[4]);

	hkHalf* HK_RESTRICT inInterleaved = (hkHalf* HK_RESTRICT)&packedHalf8;

	halves[0] = inInterleaved[0];
	halves[1] = inInterleaved[2];
	halves[2] = inInterleaved[4];
	halves[3] = inInterleaved[6];

	v0.load<4,HK_IO_SIMD_ALIGNED>(halves);
}

/*static*/ HK_FORCE_INLINE void unpackSecondInterleaved( hkVector4dParameter packedHalf8, hkVector4d& v1 )
{
	HK_ALIGN_DOUBLE(hkHalf halves[4]);

	hkHalf* HK_RESTRICT inInterleaved = (hkHalf* HK_RESTRICT)&packedHalf8;

	halves[0] = inInterleaved[1];
	halves[1] = inInterleaved[3];
	halves[2] = inInterleaved[5];
	halves[3] = inInterleaved[7];

	v1.load<4,HK_IO_SIMD_ALIGNED>(halves);
}

/*static*/ HK_FORCE_INLINE void unpackInterleaved( hkVector4dParameter packedHalf8, hkVector4d* HK_RESTRICT v0, hkVector4d* HK_RESTRICT v1 )
{
	HK_ALIGN_DOUBLE(hkHalf halves[8]);

	hkHalf* HK_RESTRICT inInterleaved = (hkHalf* HK_RESTRICT)&packedHalf8;

	halves[0] = inInterleaved[0];
	halves[4] = inInterleaved[1];
	halves[1] = inInterleaved[2];
	halves[5] = inInterleaved[3];
	halves[2] = inInterleaved[4];
	halves[6] = inInterleaved[5];
	halves[3] = inInterleaved[6];
	halves[7] = inInterleaved[7];

	v0->load<4,HK_IO_SIMD_ALIGNED>(halves);
	v1->load<4,HK_IO_SIMD_ALIGNED>(halves+4);
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
