/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_hkNativeFileSystem_H
#define HK_hkNativeFileSystem_H

#include <Common/Base/System/Io/FileSystem/hkFileSystem.h>

#if defined(HK_PLATFORM_WINRT)
	#include <Common/Base/System/Io/Platform/WinRT/hkWinRTFileSystem.h>
	typedef hkWinRTFileSystem hkNativeFileSystem;
#elif defined(HK_PLATFORM_WIN32) || defined(HK_PLATFORM_XBOX) || defined(HK_PLATFORM_XBOX360)
	#include <Common/Base/System/Io/Platform/Win32/hkWin32FileSystem.h>
	typedef hkWin32FileSystem hkNativeFileSystem;
#elif defined(HK_PLATFORM_PS3_PPU)
	#include <Common/Base/System/Io/Platform/Ps3/hkPs3FileSystem.h>
	typedef hkPs3FileSystem hkNativeFileSystem;
#elif defined(HK_PLATFORM_PSVITA)
	#include <Common/Base/System/Io/Platform/PsVita/hkPsVitaFileSystem.h>
	typedef hkPsVitaFileSystem hkNativeFileSystem;
#elif defined(HK_PLATFORM_RVL) || defined(HK_PLATFORM_GC)
	#include <Common/Base/System/Io/Platform/Wii/hkWiiFileSystem.h>
	typedef hkWiiFileSystem hkNativeFileSystem;
#elif defined(HK_PLATFORM_ANDROID)
	#include <Common/Base/System/Io/Platform/Android/hkAndroidAssetManagerFileSystem.h>
	typedef hkAndroidAssetManagerFileSystem hkNativeFileSystem;
#elif defined(HK_PLATFORM_MAC386) || defined(HK_PLATFORM_MACPPC) || defined(HK_PLATFORM_LINUX) || defined(HK_PLATFORM_IOS)
	#include <Common/Base/System/Io/Platform/Posix/hkPosixFileSystem.h>
	typedef hkPosixFileSystem hkNativeFileSystem;
#elif defined(HK_PLATFORM_WIIU)
	#include <Common/Base/System/Io/Platform/WiiU/hkWiiuFileSystem.h>
	typedef hkWiiuFileSystem hkNativeFileSystem;
#elif defined(HK_PLATFORM_PS4)
	#include <Common/Base/System/Io/Platform/Ps4/hkPs4FileSystem.h>
	typedef hkPs4FileSystem hkNativeFileSystem;
#else
	#error nofs
#endif

#endif //HK_hkNativeFileSystem_H

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
