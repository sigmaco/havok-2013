/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
// Build configuration settings
// These are compile time settings for the libraries.
// Changing these values with compiled libs will not work,

// If this setting is changed you must rebuild all Havok libs

// EQSELECT: HK_CONFIG_SIMD, Choose to enable or disable simd instructions:
// This determines whether or not we use simd instructions.

#ifndef HK_BASE_CONFIGSIMD_H
#define HK_BASE_CONFIGSIMD_H

#define HK_CONFIG_SIMD_ENABLED 1 // Enabled
#define HK_CONFIG_SIMD_DISABLED 2 // Disabled

#if !defined(HKBASE_HKBASETYPES_H)
#	error hkbase/hkBase.h needs to be included before this file
#endif

// Uncomment the following line to force a FPU build
//#define HK_CONFIG_SIMD HK_CONFIG_SIMD_DISABLED




#ifndef HK_CONFIG_SIMD

	// win32
#		if defined (HK_ARCH_ARM)
#			define HK_CONFIG_SIMD HK_CONFIG_SIMD_ENABLED // for now
#		elif defined (HK_PLATFORM_X64)
#			if (_MSC_VER == 1500)
#				define HK_CONFIG_SIMD HK_CONFIG_SIMD_DISABLED  // SIMD code path causes ICEs in 64-bit VS2008
#			else
#				define HK_CONFIG_SIMD HK_CONFIG_SIMD_ENABLED
#			endif
#		elif defined(HK_PLATFORM_SIM)
#			define HK_CONFIG_SIMD HK_CONFIG_SIMD_ENABLED
#		else
			// x86
#			define HK_CONFIG_SIMD HK_CONFIG_SIMD_DISABLED
#		endif

#else // ifndef HK_CONFIG_SIMD
#	if (HK_CONFIG_SIMD != HK_CONFIG_SIMD_ENABLED) && (HK_CONFIG_SIMD != HK_CONFIG_SIMD_DISABLED)
#		error invalid config simd option
#	endif
#endif // ifndef HK_CONFIG_SIMD

// HK_SSE_VERSION
#	define HK_SSE_VERSION 0x20
// todo howto detect ? or specify SSE > 2
// 0x20 SSE2
// 0x30 SSE3
// 0x31 SSSE3
// 0x40 SSE4 (AES)
// 0x41 SSE4.1
// 0x42 SSE4.2
// 0x50 AVX
// 0x51 FMA

#endif // HK_BASE_CONFIGSIMD_H

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
