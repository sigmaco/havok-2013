/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#include <Common/Base/hkBase.h>
#include <Common/Base/System/StackTracer/hkStackTracer.h>
#include <Common/Base/Fwd/hkcstdio.h>
#include <Common/Base/Fwd/hkwindows.h>

// dbghelp.h has an incorrect version of this block
#ifndef __specstrings
#define __specstrings
#	define __in
#	define __out
#	define __inout
#	define __in_opt
#	define __out_opt
#	define __inout_opt
#	define __in_ecount
#	define __out_ecount(A)
#	define __inout_ecount
#	define __in_bcount
#	define __out_bcount(A)
#	define __inout_bcount
#	define __deref_opt_out
#	define __deref_out
#	define __out_xcount(A)
#endif
typedef hkUlong ULONG_PTR, *PULONG_PTR;

// VC7 and higher:
#include <dbghelp.h>

typedef BOOL    (__stdcall *tSymInitialize)( IN HANDLE hProcess, IN PSTR UserSearchPath, IN BOOL fInvadeProcess );
typedef BOOL    (__stdcall *tSymRefreshModuleList)( IN HANDLE hProcess );
typedef DWORD   (__stdcall *tSymGetOptions)( VOID );
typedef DWORD   (__stdcall *tSymSetOptions)( IN DWORD SymOptions );
typedef BOOL    (__stdcall *tSymFromAddr)( IN HANDLE hProcess, IN DWORD64 dwAddr, OUT PDWORD64 pdwDisplacement, OUT PSYMBOL_INFO Symbol );
typedef BOOL    (__stdcall *tStackWalk64)( DWORD MachineType, HANDLE hProcess, HANDLE hThread, LPSTACKFRAME64 StackFrame, PVOID ContextRecord, PREAD_PROCESS_MEMORY_ROUTINE64 ReadMemoryRoutine, PFUNCTION_TABLE_ACCESS_ROUTINE64 FunctionTableAccessRoutine, PGET_MODULE_BASE_ROUTINE64 GetModuleBaseRoutine, PTRANSLATE_ADDRESS_ROUTINE64 TranslateAddress );
typedef PVOID   (__stdcall *tSymFunctionTableAccess64)( HANDLE hProcess, DWORD64 AddrBase );
typedef DWORD64 (__stdcall *tSymGetModuleBase64)( IN HANDLE hProcess, IN DWORD64 dwAddr );
typedef BOOL    (__stdcall *tSymGetLineFromAddr64)( IN HANDLE hProcess, IN DWORD64 dwAddr, OUT PDWORD64 pdwDisplacement, OUT PIMAGEHLP_LINE64 Line );
typedef BOOL    (__stdcall *tSymCleanup)( IN HANDLE hProcess );
typedef void	(__stdcall *tRtlCaptureContext)(OUT PCONTEXT context);
typedef USHORT  (__stdcall *tRtlCaptureStackBackTrace)(IN ULONG FramesToSkip, IN ULONG FramesToCapture, OUT PVOID *BackTrace, OUT PULONG BackTraceHash);

#define NATIVE_WARN_IF(A, T) if (A) { OutputDebugStringA("Havok StackTracer: " T "\r\n"); } else
#define LOAD_FUNCTION(A) if(1) { p##A = (t##A) GetProcAddress(hDbgHelpDll, #A); HK_ASSERT2(0x7ff2db1c, p##A, "Could not load symbol " #A " from dbghelp.dll. Version is too old."); } else
#define LOAD_FUNCTION_WARN(A) if(1) { p##A = (t##A) GetProcAddress(hDbgHelpDll, #A); NATIVE_WARN_IF( p##A == HK_NULL, "Could not load symbol " #A " from dbghelp.dll, version too old, but will continue without it."); } else
#define IMPL ((hkStackTracerWin32Data*)m_impl)
extern const char* hkStackTracerDbghelpPath;
const char* hkStackTracerDbghelpPath = "dbghelp.dll";

struct hkStackTracerWin32Data
{
	// We'd like the stack tracer to behave mostly like a refcounted object. i.e. unload the dbghelp.dll when
	// the last user of stacktracing is finished with it. The complication here is that some of the memory
	// allocators need the stack tracer to live past basesystem::quit. e.g. for leak detection.

	// To do this we essentially reimplement our own refcounting with "m_usageCount".
	// We use a critical section "m_lock" to protect from loading the dll twice.

	hkStackTracerWin32Data()
	{
		InitializeCriticalSection(&m_lock);
		m_lockInitialized = true;
	}

	~hkStackTracerWin32Data()
	{
		m_lockInitialized = false;
		DeleteCriticalSection(&m_lock);
	}

		// The extra checking in enterLock & leaveLock is because the order of static constructors is unpredictable.
		// In (single threaded) startup code there may be a static hkStackTracer instance which could cause beginUsage()
		// to be called before the critical section has been initialized.

	inline void enterLock()
	{
		if( m_lockInitialized )
		{
			EnterCriticalSection(&m_lock);
		}
	}
	inline void leaveLock()
	{
		if( m_lockInitialized )
		{
			LeaveCriticalSection(&m_lock);
		}
	}

		// If you do not get symbols in the stack trace, it could be because the version of dbghelp.dll
		// in your path is too old. You can download a new one from
		// http://msdn.microsoft.com/library/default.asp?url=/library/en-us/debug/base/dbghelp_versions.asp
		// And set an explicit path for the dll to load
		// extern const char* hkStackTracerDbghelpPath;
		// hkStackTracerDbghelpPath = "C:\\Program Files\\Debugging Tools for Windows\\dbghelp.dll";
	void beginUsage()
	{
		enterLock();
		if( m_usageCount++ == 0 )
		{
			hDbgHelpDll = LoadLibraryA(hkStackTracerDbghelpPath);
			NATIVE_WARN_IF( hDbgHelpDll == HK_NULL, "hkStackTracer: Unable to load dbghelp.dll");
			
			if (hDbgHelpDll)
			{
				hKernel32Dll = LoadLibraryA("kernel32.dll");
				NATIVE_WARN_IF( hKernel32Dll == HK_NULL, "hkStackTracer: Unable to load kernel32.dll");

				LOAD_FUNCTION(SymInitialize);
				LOAD_FUNCTION_WARN(SymRefreshModuleList);
				LOAD_FUNCTION(SymGetOptions);
				LOAD_FUNCTION(SymSetOptions);
				LOAD_FUNCTION(SymFromAddr);
				LOAD_FUNCTION(StackWalk64);
				LOAD_FUNCTION(SymFunctionTableAccess64);
				LOAD_FUNCTION(SymGetModuleBase64);
				LOAD_FUNCTION(SymGetLineFromAddr64);
				LOAD_FUNCTION(SymCleanup);

				pRtlCaptureContext = (tRtlCaptureContext)GetProcAddress(hKernel32Dll, "RtlCaptureContext");
				pRtlCaptureStackBackTrace = (tRtlCaptureStackBackTrace)GetProcAddress(hKernel32Dll, "RtlCaptureStackBackTrace");

				DWORD symOptions = pSymGetOptions();
				symOptions |= SYMOPT_LOAD_LINES | SYMOPT_DEBUG | SYMOPT_DEFERRED_LOADS;
				pSymSetOptions( symOptions );

				// Temporarily suppress message box in case of error
				#if (_WIN32_WINNT >= 0x0600)
					UINT prevErrMode = GetErrorMode();
					SetErrorMode(SEM_FAILCRITICALERRORS);
				#endif

				// The stack tracer is used in a global static, so can't use error singleton
				HK_ON_DEBUG( BOOL initsymbols = ) pSymInitialize( GetCurrentProcess(), HK_NULL, TRUE);
				HK_ON_DEBUG( NATIVE_WARN_IF( initsymbols == FALSE, "hkStackTracer: No debug symbols found for current Process, stack trace may fail.") );

				#if (_WIN32_WINNT >= 0x0600)
					SetErrorMode(prevErrMode);
				#endif
			}
		}
		leaveLock();
	}

	void endUsage()
	{
		enterLock();
		if( --m_usageCount == 0 )
		{
			if( pSymCleanup )
			{
				pSymCleanup( GetCurrentProcess() );
			}
			pSymInitialize = 0;
			pSymRefreshModuleList = 0;
			pSymGetOptions = 0;
			pSymSetOptions = 0;
			pSymFromAddr = 0;
			pStackWalk64 = 0;
			pSymFunctionTableAccess64 = 0;
			pSymGetModuleBase64 = 0;
			pSymGetLineFromAddr64 = 0;
			pSymCleanup = 0;
			pRtlCaptureContext = 0;
			FreeLibrary( hKernel32Dll );
			FreeLibrary( hDbgHelpDll );
			hDbgHelpDll = 0;
		}
		leaveLock();
	}

	CRITICAL_SECTION m_lock;
	bool m_lockInitialized;
	int m_usageCount;
	HINSTANCE hDbgHelpDll;
	HINSTANCE hKernel32Dll;
	tSymInitialize pSymInitialize;
	tSymRefreshModuleList pSymRefreshModuleList;
	tSymGetOptions pSymGetOptions;
	tSymSetOptions pSymSetOptions;
	tSymFromAddr pSymFromAddr;
	tStackWalk64 pStackWalk64;
	tSymFunctionTableAccess64 pSymFunctionTableAccess64;
	tSymGetModuleBase64 pSymGetModuleBase64;
	tSymGetLineFromAddr64 pSymGetLineFromAddr64;
	tSymCleanup pSymCleanup;
	tRtlCaptureContext pRtlCaptureContext;
	tRtlCaptureStackBackTrace pRtlCaptureStackBackTrace;
};

static hkStackTracerWin32Data _stackTracerWin32DataBuf;

hkStackTracer::hkStackTracer()
{
	// By having the tracer as a singleton and then all dlls then using that one 
	// singleton, the m_impl will point at the orig init data, not any uninit dll ver that may be knocking about. 
	m_impl = &_stackTracerWin32DataBuf;
	IMPL->beginUsage();
}

hkStackTracer::~hkStackTracer()
{
	IMPL->endUsage();
}

void hkStackTracer::dumpStackTrace( const hkUlong* trace, int maxtrace, printFunc pfunc, void* context ) const
{
	SYMBOL_INFO_PACKAGE sym;
	sym.si.SizeOfStruct = sizeof(sym.si);
	sym.si.MaxNameLen = sizeof(sym.name);

	HANDLE curproc = GetCurrentProcess();

	for( int i = 0; i < maxtrace; ++i)
	{
		// Subtract 4 to try and get the calling symbol
		// and not the address being returned to
		hkUlong symaddress = trace[i];

		DWORD64 displacement = 0;
		BOOL ok_symbol = IMPL->pSymFromAddr( 
			curproc, 
			DWORD64(symaddress),
			&displacement,
			&sym.si);

		if(! ok_symbol)
		{
 			static bool haveWarned;
 			if( ! haveWarned )
 			{
				OutputDebugStringA(	"**************************************************************\n" \
									"* Cannot find symbol for an address\n" \
									"* Either debug information was not found or your version of\n" \
									"* dbghelp.dll may be too old to understand the debug format.\n" \
									"* For more information, see comments in hkStackTracerWin32.cxx\n" \
									"* " __FILE__ "\n" \
									"**************************************************************" );
				haveWarned = 1;
			}

			::strcpy(sym.si.Name, "(unknown - see comments in hkStackTracerWin32.cxx)");
		}
		IMAGEHLP_LINE64 line;
		::memset(&line, 0, sizeof(line));
		line.SizeOfStruct = sizeof(line);

		IMPL->pSymGetLineFromAddr64(
			curproc,
			DWORD64(symaddress),
			&displacement,
			&line);

		char trace[2048];
		_snprintf(trace, 2048, "%s(%i):'%s'\n", line.FileName, line.LineNumber, sym.si.Name);
		pfunc(trace, context);
	}
}

int hkStackTracer::getStackTrace( hkUlong* trace, int maxtrace )
{
	// This will only work correctly if Frame Pointer Optimization is disabled for the
	// stack frame concerned. hkCheckingMemorySystem already does this -- customer code
	// must disable it explicitly in the project options or with #pragma optimize("y", off)

	// The stack trace will end when a frame without a frame pointer is encountered
	if(IMPL->pRtlCaptureStackBackTrace)
	{
		return IMPL->pRtlCaptureStackBackTrace(0, maxtrace, (PVOID *)trace, NULL);
	}
	return 0;
}

void hkStackTracer::refreshSymbols()
{
	if (IMPL->pSymRefreshModuleList)
	{
		IMPL->pSymRefreshModuleList( GetCurrentProcess() );
	}
}

void hkStackTracer::getModuleInfo( printFunc pfunc, void* context ) const
{
	char module[1024];
	if( GetModuleFileNameA( HK_NULL, module, 1024 ) > 0 )
	{
		char buf[1024];
		hkString::snprintf( buf, 1024, "Win32 \"%s\"", module );
		pfunc( buf, context );
	}
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
