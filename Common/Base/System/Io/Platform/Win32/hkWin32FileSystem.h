/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_hkWin32FileSystem_H
#define HK_hkWin32FileSystem_H

#include <Common/Base/System/Io/FileSystem/hkFileSystem.h>

class hkWin32FileSystem : public hkFileSystem
{
	public:

		virtual hkRefNew<hkStreamReader> openReader(const char* name, OpenFlags flags);
		virtual hkRefNew<hkStreamWriter> openWriter(const char* name, OpenFlags flags);

		virtual Result remove(const char* path);
		virtual Result mkdir(const char* path);
		
		virtual Result stat( const char* path, Entry& entryOut );
		virtual hkRefNew<Iterator::Impl> createIterator( const char* top, const char* wildcard );
};

#endif // HK_hkWin32FileSystem_H

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
