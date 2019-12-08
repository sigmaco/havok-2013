/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_SCENE_EXPORT_MEMORY_H
#define HK_SCENE_EXPORT_MEMORY_H

#include <Common/Base/Memory/System/Util/hkMemoryInitUtil.h>


class hkSceneExportMemThreadCallback
{
public:
		/// Null on thread delete
	virtual void initThread( hkMemoryRouter* m_memoryRouter ) = 0;
};

class hkDefaultSceneExportMemThreadCallback : public hkSceneExportMemThreadCallback
{
public:
	virtual void initThread( hkMemoryRouter* m_memoryRouter );
};

	/// Functions in this namespace are used to initialize thread memory as well as to retrieve information
	/// about singletons.
namespace hkSceneExportMemory
{
		///	Initialized Havok's base system using thread-safe memory
	void HK_CALL baseSystemInit(bool debugMem = false);

		/// Quits Havok's bases system
	void HK_CALL baseSystemQuit();

		/// Retrieves information about the singletons used by this module (DLL or EXE)
	void HK_CALL getBaseSystemSyncInfo( hkMemoryInitUtil::SyncInfo& baseSystemInfo );

	static hkDefaultSceneExportMemThreadCallback g_defaultThreadCallback;
}

#endif //HK_SCENE_EXPORT_MEMORY_H

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
