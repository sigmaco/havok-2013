/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_hkUnionFileSystem_H
#define HK_hkUnionFileSystem_H

#include <Common/Base/System/Io/FileSystem/hkFileSystem.h>

	/// Virtual filesystem as a combination of sub-filesystems.
	/// The current implementation is rather simpleminded. The requested
	/// operation is tried on each mount (which has a matching prefix)
	/// in turn (most recently mounted first). An empty prefix is considered
	/// to always match so will often be used as a final fallback.
	/// 
	/// A typical setup for a mobile device might have several mounts:
	/// a readonly mount into the application bundle, then a read-write
	/// mount into an sdcard location. And finally a catch-all mount to
	/// handle absolute paths.
	/// 1. ("Resources", "/path/to/app/bundle/Resources", writable=False)
	/// 2. ("Resources", "/mnt/sdcard/Havok/Resources", writable=True)
	/// 3. ("", "", writable=False)
	/// 
	/// There is no support for whiteouts so if a file exists in more than
	/// one mount, it will still be present after removing the first one.
	/// Similarly when iterating, a file with the same name but different 
	/// contents may be returned.
class hkUnionFileSystem : public hkFileSystem
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_STREAM);

		virtual hkRefNew<hkStreamReader> openReader(const char* name, OpenFlags flags);

		virtual hkRefNew<hkStreamWriter> openWriter(const char* name, OpenFlags flags);

		virtual Result remove(const char* path);

		virtual Result mkdir(const char* path);

		virtual Result stat( const char* path, Entry& entryOut );

		virtual hkFileSystem* resolvePath( const char* pathIn, hkStringBuf& pathOut );

			/// 
		struct Mount
		{
			HK_DECLARE_PLACEMENT_ALLOCATOR();

			hkRefPtr<hkFileSystem> m_fs;
			hkStringPtr m_srcPath;
			hkStringPtr m_dstPath;
			hkBool m_writable;
		};

			/// Mount a filesystem so that accesses to the srcPath hierarchy map to accesses
			/// in the underlying filesystem's dstPath hierarchy.
		void mount(hkFileSystem* fs, const char* srcPath, const char* dstPath, hkBool writable); 

		virtual hkRefNew<Iterator::Impl> createIterator( const char* top, const char* wildcard );

	protected:

		hkArray<Mount> m_mounts;
};

#endif //HK_hkUnionFileSystem_H

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
