/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

// platform specific implementations
#if HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED
#	if defined(HK_COMPILER_HAS_INTRINSICS_IA32)
#			include <Common/Base/Math/Vector/Sse/hkSseVector4.inl>
#			include <Common/Base/Math/Vector/Sse/hkSseVector4Comparison.inl>
#			include <Common/Base/Math/Vector/Sse/hkSseSimdReal.inl>
#			if HK_SSE_VERSION >= 0x50
#				include <Common/Base/Math/Vector/Sse/hkSseVector4_D_AVX.inl>
#				include <Common/Base/Math/Vector/Sse/hkSseVector4Comparison_D_AVX.inl>
#			else
#				include <Common/Base/Math/Vector/Sse/hkSseVector4_D.inl>
#				include <Common/Base/Math/Vector/Sse/hkSseVector4Comparison_D.inl>
#			endif
#			include <Common/Base/Math/Vector/Sse/hkSseSimdReal_D.inl>
#	elif defined(HK_PLATFORM_XBOX360)
#		include <Common/Base/Math/Vector/Xbox360/hkXbox360Vector4.inl>
#		include <Common/Base/Math/Vector/Xbox360/hkXbox360Vector4Comparison.inl>
#		include <Common/Base/Math/Vector/Xbox360/hkXbox360SimdReal.inl>
#		include <Common/Base/Math/Vector/Fpu/hkFpuSimdReald.inl>
#		include <Common/Base/Math/Vector/Fpu/hkFpuVector4d.inl>
#		include <Common/Base/Math/Vector/Fpu/hkFpuVector4dComparison.inl>
#	elif defined(HK_PLATFORM_PS3_PPU) || defined(HK_PLATFORM_PS3_SPU)
#		include <Common/Base/Math/Vector/Ps3/hkPs3Vector4.inl>
#		include <Common/Base/Math/Vector/Ps3/hkPs3Vector4Comparison.inl>
#		include <Common/Base/Math/Vector/Ps3/hkPs3SimdReal.inl>
#		include <Common/Base/Math/Vector/Fpu/hkFpuSimdReald.inl>
#		include <Common/Base/Math/Vector/Fpu/hkFpuVector4d.inl>
#		include <Common/Base/Math/Vector/Fpu/hkFpuVector4dComparison.inl>
#	elif defined(HK_COMPILER_HAS_INTRINSICS_NEON)
#		include <Common/Base/Math/Vector/Neon/hkNeonVector4.inl>
#		include <Common/Base/Math/Vector/Neon/hkNeonVector4Comparison.inl>
#		include <Common/Base/Math/Vector/Neon/hkNeonSimdReal.inl>
#		include <Common/Base/Math/Vector/Fpu/hkFpuSimdReald.inl>
#		include <Common/Base/Math/Vector/Fpu/hkFpuVector4d.inl>
#		include <Common/Base/Math/Vector/Fpu/hkFpuVector4dComparison.inl>
#	elif defined(HK_PLATFORM_LRB)
#		include <Common/Base/Math/Vector/Lrb/hkLrbVector4.inl>
#	else
#		error Dont know how to do simd on this platform
#	endif
#else // no SIMD
#		include <Common/Base/Math/Vector/Fpu/hkFpuVector4.inl>
#		include <Common/Base/Math/Vector/Fpu/hkFpuVector4Comparison.inl>
#		include <Common/Base/Math/Vector/Fpu/hkFpuSimdReal.inl>
#endif // HK_CONFIG_SIMD

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
