/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifdef HK_ADP_ATOM
#include <stdio.h>

typedef struct {unsigned long field[4];} ADP_APPLICATIONID;
extern "C" ADP_APPLICATIONID ADP_DEBUG_APPLICATIONID;
extern "C" int __cdecl ADP_Initialize( void );
extern "C" int __cdecl ADP_IsAuthorized( ADP_APPLICATIONID );
extern "C" int __cdecl ADP_Close( void );

ADP_APPLICATIONID applicationID = ADP_DEBUG_APPLICATIONID;
#endif

#include <ContentTools/Common/Filters/FilterTutorial/hctFilterTutorial.h>

// Keycode
#include <Common/Base/keycode.cxx>

// DLL main
HINSTANCE hInstance;
static BOOL CommonControlsInitialized = FALSE;

BOOL WINAPI DllMain(HINSTANCE hinstDLL, ULONG fdwReason, LPVOID lpvReserved)
{
#ifdef HK_ADP_ATOM
	if ( ADP_Initialize() != 0 )
	{
		printf( "Could not initialize ADP licensing system.\n" );
		return -1;
	}
	if ( ADP_IsAuthorized( applicationID ) != 5 )
	{
		printf( "ADP application could not be authorized.\n" );
		return -1;
	}
#endif

	switch ( fdwReason )
	{
		case DLL_PROCESS_ATTACH:
		{
			hInstance = hinstDLL;				// Hang on to this DLL's instance handle.

			if (!CommonControlsInitialized) 
			{

				CommonControlsInitialized = TRUE;
				InitCommonControls();			// Initialize Win32 controls
			}
			break;
		}

		case DLL_PROCESS_DETACH:
		{
			if (CommonControlsInitialized)
			{
				CommonControlsInitialized = FALSE;
			}
		}

		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
			break;
	}

#ifdef HK_ADP_ATOM
	ADP_Close();
#endif

	return TRUE;
}

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
