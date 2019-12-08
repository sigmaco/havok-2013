/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#pragma once

#pragma managed(push, off)

#include <Common/Base/hkBase.h>
#include <Common/Base/System/hkBaseSystem.h>
#include <Common/Base/Memory/System/Util/hkMemoryInitUtil.h>
#include <Common/Base/Memory/Allocator/Malloc/hkMallocAllocator.h>

#include <Common/Serialize/Version/hkVersionPatchManager.h>
#include <Common/Serialize/Util/hkBuiltinTypeRegistry.h>

#include <Common/Base/DebugUtil/MultiThreadCheck/hkMultiThreadCheck.h>

#include <Common/Base/Reflection/Registry/hkDefaultClassNameRegistry.h>
#include <Common/Base/Reflection/Registry/hkTypeInfoRegistry.h>
#include <Common/Base/Reflection/Registry/hkVtableClassRegistry.h>

#define HAVOK_TOOLS_BASE_SYSTEM_DLL_MAIN_DECL \
	static void ASSERT_WRAPPER(bool v, const char* str) \
	{ \
		HK_ASSERT2(0x1d9a16fa, v, str); \
	} \
	static hkUint32 __g_numThreads = 0; \
	static HK_THREAD_LOCAL(hkUint32) __g_perThreadInfo; \
	static CRITICAL_SECTION __g_systemCriticalSection; \
	static hkError* __g_pushedError = HK_NULL;\
	BOOL WINAPI DllMain(HINSTANCE hinstDLL, ULONG fdwReason, LPVOID lpvReserved) \
	{ \
		switch ( fdwReason ) \
		{ \
		case DLL_PROCESS_ATTACH: \
			{ \
				InitializeCriticalSectionAndSpinCount( &__g_systemCriticalSection, 1000 ); \
				break; \
			} \
		case DLL_PROCESS_DETACH: \
			{ \
				DeleteCriticalSection( &__g_systemCriticalSection ); \
				break;\
			} \
		case DLL_THREAD_ATTACH:\
		case DLL_THREAD_DETACH:\
			break;\
		}		\
		return TRUE; \
	} \
	static void HAVOK_TOOLS_BASE_SYSTEM_LOCK()  \
	{ 	EnterCriticalSection(&__g_systemCriticalSection); } \
	static void HAVOK_TOOLS_BASE_SYSTEM_UNLOCK()  \
	{	LeaveCriticalSection(&__g_systemCriticalSection); } \
	static void HAVOK_TOOLS_BASE_SYSTEM_INIT(hkMemoryInitUtil::SyncInfo* info) \
	{ \
		extern hkBool hkBaseSystemIsInitialized; \
		if (!hkBaseSystemIsInitialized && info->m_memoryRouter) \
		{ \
			hkMemoryRouter::replaceInstance(info->m_memoryRouter); \
			hkMemorySystem::replaceInstance(info->m_memorySystem); \
			if (info->m_singletonList) \
			{ \
				hkSingletonInitNode* dcnDest = info->m_singletonList->findByName( "hkDefaultClassNameRegistry" );  \
				hkSingletonInitNode* tirDest = info->m_singletonList->findByName( "hkTypeInfoRegistry" );  \
				hkSingletonInitNode* vcrDest = info->m_singletonList->findByName( "hkVtableClassRegistry" );  \
				if (dcnDest)   \
				{  \
					hkDefaultClassNameRegistry* rD = reinterpret_cast<hkDefaultClassNameRegistry*>( *dcnDest->m_value );  \
					rD->registerList( hkBuiltinTypeRegistry::StaticLinkedClasses );  \
				}  \
				if (tirDest)   \
				{  \
					hkTypeInfoRegistry* tD = reinterpret_cast<hkTypeInfoRegistry*>( *tirDest->m_value );  \
					tD->registerList( hkBuiltinTypeRegistry::StaticLinkedTypeInfos );  \
				}  \
				if (vcrDest)   \
				{  \
					hkVtableClassRegistry* vD = reinterpret_cast<hkVtableClassRegistry*>( *vcrDest->m_value );  \
					vD->registerList( hkBuiltinTypeRegistry::StaticLinkedTypeInfos, hkBuiltinTypeRegistry::StaticLinkedClasses );  \
				}  \
				hkSingletonInitNode* verReg= info->m_singletonList->findByName( "hkVersionRegistry" ); \
				const char* restVerReg = HK_NULL; \
				if (verReg) \
				{ \
					restVerReg = verReg->m_name; \
					verReg->m_name = "DONOTSYNC"; \
				} \
				hkSingletonInitNode::populate( hkSingletonInitList, info->m_singletonList ); \
				if (verReg) \
				{ \
					verReg->m_name = restVerReg; \
				} \
			} \
			hkReferencedObject::lockInit(hkReferencedObject::LOCK_MODE_NONE); \
			hkBaseSystem::initSingletons(); \
			hkMonitorStream::init(); \
			hkMultiThreadCheck::staticInit(hkMallocAllocator::m_defaultMallocAllocator); \
			hkBaseSystemIsInitialized = true; \
			__g_numThreads = 1; \
			HK_THREAD_LOCAL_SET(__g_perThreadInfo, 1); \
		} \
		else if (info->m_memoryRouter) /* may be thread init */ \
		{  \
			if ( HK_THREAD_LOCAL_GET(__g_perThreadInfo) == 0) \
			{ \
				ASSERT_WRAPPER(hkMemoryRouter::getInstancePtr() == HK_NULL, "Thread mem router not null"); \
				/*ASSERT_WRAPPER(&hkMemory::getInstance() == info->m_memory, "Memory base does not match");*/ \
				hkMemoryRouter::replaceInstance(info->m_memoryRouter); \
				hkMonitorStream::init(); \
				HK_THREAD_LOCAL_SET(__g_perThreadInfo, 1); \
				__g_numThreads++; \
			} \
			else /* calling init twice: can happen now due to base init from both cloth and preview */ \
			{} \
		} \
	} \
	static void HAVOK_TOOLS_BASE_SYSTEM_UPDATE(hkMemoryInitUtil::SyncInfo* info) \
	{ \
		if (info->m_memoryRouter) \
		{ \
			HAVOK_TOOLS_BASE_SYSTEM_INIT(info); \
		} \
		else \
		{ \
			HAVOK_TOOLS_BASE_SYSTEM_QUIT(); \
		} \
	}

#define HAVOK_TOOLS_BASE_SYSTEM_QUIT() \
	do { \
		extern hkBool hkBaseSystemIsInitialized; \
		if ( hkBaseSystemIsInitialized ) \
		{ \
			--__g_numThreads; \
			int threadInit = HK_THREAD_LOCAL_GET(__g_perThreadInfo); \
			if ( threadInit ) \
			{ \
				if (__g_numThreads == 0)  \
				{ \
					hkBaseSystem::quit(); \
				} \
				else if (__g_numThreads < 0) \
				{ \
					ASSERT_WRAPPER(false, "Thread num error in a tool plug" ); \
				} \
				else \
				{ \
					if (hkMonitorStream::getInstancePtr()) \
					{ hkMonitorStream::getInstance().quit(); } \
					hkMemoryRouter::replaceInstance(HK_NULL); \
				} \
				HK_THREAD_LOCAL_SET(__g_perThreadInfo, 0); \
			} \
			else \
			{ \
				ASSERT_WRAPPER(false, "Calling quit from a thread which has no init call / quit has already been called." ); \
			} \
		} \
	} while(0)
#define HAVOK_TOOLS_BASE_SYSTEM_GET_INFO(x) \
	do { \
		extern hkBool hkBaseSystemIsInitialized; \
		static hkMemoryInitUtil::SyncInfo g_curRet; \
		if ( hkBaseSystemIsInitialized ) \
		{ \
			g_curRet.m_memoryRouter = hkMemoryRouter::getInstancePtr(); \
			g_curRet.m_singletonList = hkSingletonInitList; \
			g_curRet.m_memorySystem = hkMemorySystem::getInstancePtr(); \
		} \
		else \
		{ \
			hkString::memSet(&g_curRet, 0, sizeof(hkMemoryInitUtil::SyncInfo) ); \
		} \
		x = System::IntPtr((void*)&g_curRet); \
	} while(0)
#define HAVOK_TOOLS_BASE_SYSTEM_GET_INFO_NO_SLIST(x) \
	do { \
	extern hkBool hkBaseSystemIsInitialized; \
	static hkMemoryInitUtil::SyncInfo g_curRet; \
	if ( hkBaseSystemIsInitialized ) \
		{ \
		g_curRet.m_memoryRouter = hkMemoryRouter::getInstancePtr(); \
		g_curRet.m_singletonList = HK_NULL; \
		g_curRet.m_memorySystem = hkMemorySystem::getInstancePtr(); \
		} \
		else \
		{ \
		hkString::memSet(&g_curRet, 0, sizeof(hkMemoryInitUtil::SyncInfo) ); \
		} \
		x = System::IntPtr((void*)&g_curRet); \
	} while(0)

#define HAVOK_TOOLS_BASE_SYSTEM_PUSH_ERROR(x) \
	do { \
		extern hkBool hkBaseSystemIsInitialized; \
		if ( hkBaseSystemIsInitialized ) \
		{ \
			ASSERT_WRAPPER( __g_pushedError == HK_NULL, "Only one push allowed at the moment");\
			__g_pushedError = &hkError::getInstance();\
			__g_pushedError->addReference();\
			hkError* newErr = (hkError*)x.ToPointer();\
			if (newErr) { newErr->addReference(); } \
			hkError::replaceInstance(newErr ); \
		} \
	} while(0)

#define HAVOK_TOOLS_BASE_SYSTEM_POP_ERROR(x) \
	do { \
		extern hkBool hkBaseSystemIsInitialized; \
		if ( hkBaseSystemIsInitialized ) \
		{ \
			ASSERT_WRAPPER( __g_pushedError != HK_NULL, "No error on stack to pop"); \
			hkError::replaceInstance( __g_pushedError ); \
			__g_pushedError = HK_NULL; \
		} \
	} while(0)

#pragma managed(pop)

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
