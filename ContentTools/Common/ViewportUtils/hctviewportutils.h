/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef INC_COMMON_VIEWPORT_UTILS_H
#define INC_COMMON_VIEWPORT_UTILS_H

#pragma managed(push, off)

#include <Common/Base/hkBase.h>



class hkRootLevelContainer;

class hkClassNameRegistry;
class hkTypeInfoRegistry;
class hkVtableClassRegistry;

// Similar to a Filter. 
// Perhaps we should make a standard Util DLL interface similar to the Filter DLL interface

class hctViewportUtils
{
	public:

		virtual ~hctViewportUtils() {}

		virtual void setFilterManagerPath( const char* path ) = 0;
		virtual void registerThreadCallback (const class hctFilterThreadCallback* cb)= 0;

		
		enum DllError
		{
			DLL_INTERNAL_ERROR = 0,  // unable to query the DLL at all
			DLL_NO_ERROR = 1,        // DLL did load ok
			DLL_INIT_ERROR = 2       // DLL is not initialized or failed to init internal structures
		};

		// Create the Preview under the given parent. Can give null, but doesn't make as much sense. 
		// Returns the window handle
		virtual void* createPreviewWindow( void* parentWindowHandle, int x, int y, int w, int h ) = 0;
		virtual void resizeWindow( int w, int h ) = 0;
		virtual void destroyPreviewWindow( void* windowHandle ) = 0;

		// To update: Call merge, then either update or filterupdate
		virtual void updateScene( hkRootLevelContainer* newScene ) = 0;
		virtual void filterAndUpdateScene( hkRootLevelContainer* rawScene, char* filterOptions, int filterOptionsSize ) = 0;

};

typedef class hctBaseDll* (HK_CALL *hctGetBaseDllInterfaceFunc)(); /* getBaseDllInterface() */
typedef hctViewportUtils* (HK_CALL *hctGetViewportUtilInterfaceFunc)();  /* getViewportUtilInterface() */
typedef hctViewportUtils::DllError (HK_CALL *hctGetViewportDllErrorFunc)(); /* getViewportDllError() */

#pragma managed(pop)

#endif // INC_COMMON_VIEWPORT_UTILS_H

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
