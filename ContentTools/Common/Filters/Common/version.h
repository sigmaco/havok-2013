/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef INC_HCT_VERSION_H
#define INC_HCT_VERSION_H

#define HCT_VERSION_YEAR  11
#define HCT_VERSION_MAJOR 1
#define HCT_VERSION_MINOR 0
#define HCT_VERSION_BUILD 1
#define HCT_CURRENT_VERSION_STRING		"2013.1.0.1 (2013.1 r1)"
#define HCT_CURRENT_VERSION_UNICODE		L"2013.1.0.1 (2013.1 r1)"

#define HCT_MAKE_VERSION(year, major, minor, build) ( ((year) << 24) | ((major) << 16) | ((minor)<<8) | (build) )
#define HCT_CURRENT_VERSION HCT_MAKE_VERSION( HCT_VERSION_YEAR, HCT_VERSION_MAJOR, HCT_VERSION_MINOR, HCT_VERSION_BUILD )

#define HCT_IS_MINOR_COMPATIBLE(thisVer, otherVer) ( (thisVer & ~0x000ff) == (otherVer & ~0x000ff) )

#if defined (HK_PLATFORM_X64)
#define ENVVAR_FILTER_ROOT "HAVOK_TOOLS_ROOT_X64"
#else
#define ENVVAR_FILTER_ROOT "HAVOK_TOOLS_ROOT"
#endif

#endif // INC_HCT_VERSION_H

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
