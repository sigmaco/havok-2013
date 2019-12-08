/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

void HK_CALL hkString::memCpy4( void* dst, const void* src, int numWords)
{
	const hkUint32* src32 = reinterpret_cast<const hkUint32*>(src);
	hkUint32* dst32       = reinterpret_cast<      hkUint32*>(dst);
	{
		for (int i = 0; i < numWords; i++)
		{
			*(dst32++) = *(src32++);
		}
	}
}

void HK_CALL hkString::memCpy16( void* dst, const void* src, int numQuads)
{

#if defined(HK_ALIGN_RELAX_CHECKS) // stack allocated vars not aligned to 16 etc, yet a lot of code uses this call to init the vars. As it is only using uint32, it only has to be 4 byte aligned anyway.
	HK_ASSERT2( 0xf022d445, (hkUlong(dst) & 0x03) == 0, "Unaligned address" );
	HK_ASSERT2( 0xf022d446, (hkUlong(src) & 0x03) == 0, "Unaligned address" );
#else
	HK_ASSERT2( 0xf021d445, (hkUlong(dst) & 0xf) == 0, "Unaligned address" );
	HK_ASSERT2( 0xf021d446, (hkUlong(src) & 0xf) == 0, "Unaligned address" );
#endif

	const hkUint32* src32 = reinterpret_cast<const hkUint32*>(src);
	hkUint32* dst32 = reinterpret_cast<      hkUint32*>(dst);
	{
		for (int i = 0; i < numQuads; i++)
		{
			hkUint32 a = src32[0];
			hkUint32 b = src32[1];
			hkUint32 c = src32[2];
			hkUint32 d = src32[3];
			dst32[0] = a;
			dst32[1] = b;
			dst32[2] = c;
			dst32[3] = d;
			dst32+= 4;
			src32+= 4;
		}
	}
}

void HK_CALL hkString::memCpy16NonEmpty( void* dst, const void* src, int numQuads)
{
	HK_ASSERT2( 0xf022d444, numQuads > 0, "Size 0 not allowed" );

#if ( HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED) && ( defined(HK_PLATFORM_WIN32) || defined(HK_PLATFORM_X64) || defined (HK_PLATFORM_PS3_PPU) || defined (HK_PLATFORM_PS3_SPU) || defined( HK_PLATFORM_XBOX360 ) || defined( HK_PLATFORM_PS4 ) )
	
	HK_ASSERT2( 0xf022d445, (hkUlong(dst) & HK_NATIVE_ALIGN_CHECK) == 0, "Unaligned address" );
	HK_ASSERT2( 0xf022d446, (hkUlong(src) & HK_NATIVE_ALIGN_CHECK) == 0, "Unaligned address" );
	const hkQuadFloat32* srcQuad = reinterpret_cast<const hkQuadFloat32*>(src);
	hkQuadFloat32* dstQuad = reinterpret_cast<hkQuadFloat32*>(dst);
	{
		do
		{
			*(dstQuad++) = *(srcQuad++);
		}
		while ( --numQuads > 0 );
	}
	
#else

	#if defined(HK_ALIGN_RELAX_CHECKS)  // stack allocated vars not aligned to 16 etc, yet a lot of code uses this call to init the vars. As it is only using uint32, it only has to be 4 byte aligned anyway.
	    HK_ASSERT2( 0xf022d445, (hkUlong(dst) & 0x03) == 0, "Unaligned address" );
	    HK_ASSERT2( 0xf022d446, (hkUlong(src) & 0x03) == 0, "Unaligned address" );
	#else
	    HK_ASSERT2( 0xf022d445, (hkUlong(dst) & 0xf) == 0, "Unaligned address" );
	    HK_ASSERT2( 0xf022d446, (hkUlong(src) & 0xf) == 0, "Unaligned address" );
	#endif
	const hkUint32* src32 = reinterpret_cast<const hkUint32*>(src);
	hkUint32* dst32 = reinterpret_cast<      hkUint32*>(dst);
	{
		do
		{
			hkUint32 a = src32[0];
			hkUint32 b = src32[1];
			hkUint32 c = src32[2];
			hkUint32 d = src32[3];
			dst32[0] = a;
			dst32[1] = b;
			dst32[2] = c;
			dst32[3] = d;
			dst32+= 4;
			src32+= 4;
		}
		while ( --numQuads > 0 );
	}
#endif
}

template<int size>
void HK_CALL hkString::memCpy16(void* dst, const void* src)
{
	HK_ASSERT( 0xf0dedf34, ((size & 0xf) == 0) && (size <= 192) && (size > 0));

	hkString::memCpy16NonEmpty(dst, src, size/16);
}

void HK_CALL hkString::memCpy256(void* dst, const void* src)
{
	hkString::memCpy16NonEmpty(dst, src, 16);
}

void HK_CALL hkString::memSet4(void* dst, const int value, int numWords)
{
	hkUint32* dst32 = reinterpret_cast<      hkUint32*>(dst);
	for (int i = numWords-1; i>=0; i--)
	{
		*dst32 = value;
		dst32++;
	}
}

void HK_CALL hkString::memClear16(void* dst, int numQuads)
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED) && !defined(HK_REAL_IS_DOUBLE)
	HK_ASSERT2( 0xf021d445, (hkUlong(dst) & HK_NATIVE_ALIGN_CHECK ) == 0, "Unaligned address" );
	hkVector4 zero; zero.setZero();
	hkVector4* dstQuad = (hkVector4*)dst;
	for (int i = numQuads-1; i>=0; i--)
	{
		*(dstQuad++) = zero;
	}
#else

#if defined(HK_ALIGN_RELAX_CHECKS) // stack allocated vars not aligned to 16 etc, yet a lot of code uses this call to init the vars. As it is only using uint32, it only has to be 4 byte aligned anyway.
	HK_ASSERT2( 0xf021d445, (hkUlong(dst)   & 0x03) == 0, "Unaligned address" );
#else
	HK_ASSERT2( 0xf021d445, (hkUlong(dst)   & 0xf) == 0, "Unaligned address" );
#endif
	hkUint32* dst32 = reinterpret_cast<      hkUint32*>(dst);
	{
		for (int i = 0; i < numQuads; i++)
		{
			dst32[0] = 0;
			dst32[1] = 0;
			dst32[2] = 0;
			dst32[3] = 0;
			dst32+= 4;
		}
	}
#endif
}


// For size up to 512 bytes, on PlayStation(R)3, this will compile down to a sequence of store instructions
// For larger copies or other platforms, it reverts to the looped version.
template<int size>
void HK_CALL hkString::memSet16(void* dst, const void* HK_RESTRICT src)
{
	HK_ASSERT( 0xf0dedf34, ((size & 0xf) == 0) && (size > 0) );

	{
		hkString::memSet16(dst, src, size/16);
	}
}

void HK_CALL hkString::memSet16(void* dst, const void* value, int numQuads)
{

	HK_ASSERT2( 0xf021d445, (hkUlong(dst) & 0x03) == 0, "Unaligned address" );

	const hkUint32* value32 = reinterpret_cast<const hkUint32*>(value);
	hkUint32* dst32 = reinterpret_cast<      hkUint32*>(dst);
	{
		for (int i = 0; i < numQuads; i++)
		{
			dst32[0] = value32[0];
			dst32[1] = value32[1];
			dst32[2] = value32[2];
			dst32[3] = value32[3];
			dst32+= 4;
		}
	}
}

HK_FORCE_INLINE int HK_CALL hkString::memCmpUint32(const hkUint32* buf1, const hkUint32* buf2, int n)
{
	for (int i =0; i < n; i++)
	{
		if ( buf1[i] == buf2[i] )
		{
			continue;
		}
		if ( buf1[i] < buf2[i] )
		{
			return -1;
		}
		return 1;
	}
	return 0;
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
