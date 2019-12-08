/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE


#if HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED
#	if defined(HK_COMPILER_HAS_INTRINSICS_IA32)
#		include <Common/Base/Math/Functions/Sse/hkSseMathFuncs.inl>
#	elif defined(HK_PLATFORM_XBOX360)
#		include <Common/Base/Math/Functions/Xbox360/hkXbox360MathFuncs.inl>
#	elif defined(HK_ARCH_PS3) || defined(HK_ARCH_PS3SPU)
#		define HK_PLATFORM_SUPPORTS_MANY_SIMD_REGISTERS
#		include <Common/Base/Math/Functions/Ps3/hkPs3MathFuncs.inl>
#	elif defined(HK_COMPILER_HAS_INTRINSICS_NEON)
#		define HK_PLATFORM_SUPPORTS_MANY_SIMD_REGISTERS
#		include <Common/Base/Math/Functions/Neon/hkNeonMathFuncs.inl>
#	else // simd
#		error Unknown platform for SIMD
#	endif
#else // not simd
#		include <Common/Base/Math/Functions/Fpu/hkFpuMathFuncs.inl>
#endif

// platform independent
#include <Common/Base/Math/Functions/hkMathFuncs.h>

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
