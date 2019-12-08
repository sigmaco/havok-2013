/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_HALF8fUTIL_H
#define HK_HALF8fUTIL_H

#include <Common/Base/Math/Vector/hkVector4f.h>


namespace hkHalf8Util
{
	/// Packs 2 vectors into a vector containing 8 halves  (v0.x, v0.y, v0.z, v0.w, v1.x, ...).
	template<hkMathRoundingMode R, hkMathIoMode I>
	static HK_FORCE_INLINE void pack( hkVector4fParameter v0, hkVector4fParameter v1, hkHalf* HK_RESTRICT packedHalf8 );

	/// Unpacks a vector containing 8 halves into two normal vectors.
	template<hkMathIoMode I>
	static HK_FORCE_INLINE void unpack( const hkHalf* HK_RESTRICT packedHalf8, hkVector4f* HK_RESTRICT v0, hkVector4f* HK_RESTRICT v1 );

	/// Unpacks the first 4 halves of a vector containing 8 halves.
	static HK_FORCE_INLINE void unpackFirst( hkVector4fParameter packedHalf8, hkVector4f& v0 );

	/// Unpacks the second 4 halves of a vector containing 8 halves.
	static HK_FORCE_INLINE void unpackSecond( hkVector4fParameter packedHalf8, hkVector4f& v1 );

	/// Packs 2 vectors into a vector containing 8 halves interleaved (v0.x, v1.x, v0.y, v1.y, ...).
	template<hkMathRoundingMode A>
	static HK_FORCE_INLINE void packInterleaved( hkVector4fParameter v0, hkVector4fParameter v1, hkVector4f& packedHalf8 );

	/// Unpacks a vector containing 8 halves into two normal vectors.
	static HK_FORCE_INLINE void unpackInterleaved( hkVector4fParameter packedHalf8, hkVector4f* HK_RESTRICT v0, hkVector4f* HK_RESTRICT v1 );

	/// Unpacks the first 4 halves of a vector containing 8 halves.
	static HK_FORCE_INLINE void unpackFirstInterleaved( hkVector4fParameter packedHalf8, hkVector4f& v0 );

	/// Unpacks the second 4 halves of a vector containing 8 halves.
	static HK_FORCE_INLINE void unpackSecondInterleaved( hkVector4fParameter packedHalf8, hkVector4f& v1 );
}


#if defined(HK_COMPILER_HAS_INTRINSICS_IA32)
	#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
		#include <Common/Base/Math/Vector/Sse/hkSseHalf8fUtil.inl>
	#else
		#include <Common/Base/Math/Vector/hkHalf8fUtil.inl>
	#endif
#elif defined(HK_PLATFORM_XBOX360)
	#include <Common/Base/Math/Vector/Xbox360/hkXbox360Half8Util.inl>
#elif defined(HK_PLATFORM_PS3)
	#include <Common/Base/Math/Vector/Ps3/hkPs3Half8Util.inl>
// #elif defined(HK_PLATFORM_GC)
// 	#include <Common/Base/Math/Vector/Gc/hkGcHalf8Util.inl>
#elif defined(HK_PLATFORM_ANDROID) && defined(HK_COMPILER_HAS_INTRINSICS_NEON)
	#include <Common/Base/Math/Vector/Neon/hkNeonHalf8Util.inl>
#else
	#include <Common/Base/Math/Vector/hkHalf8fUtil.inl>
#endif


#endif // HK_HALF8UTIL_H

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
