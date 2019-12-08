/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKBASE_HKBASEDEFS_H
#define HKBASE_HKBASEDEFS_H

// Uncomment the next line if you want to build with double precision math
//#define HK_REAL_IS_DOUBLE

#if !defined(HK_REAL_IS_DOUBLE)
#	define HK_REAL_IS_FLOAT
#endif

//
// compiler
//
#if defined(__clang__)
#	define HK_COMPILER_CLANG
#elif defined(__SNC__) 
#	define HK_COMPILER_SNC
#elif defined(__GNUC__) || defined(__CC_ARM) || defined(__ARMCC__) || defined(__ghs__)
#	define HK_COMPILER_GCC // ARMCC and GCC are very similar so often can treat them the same.
#	if defined(__CC_ARM) || defined(__ARMCC__)
#		define HK_COMPILER_ARMCC
#   elif defined(__ghs__)
#		define HK_COMPILER_GHS
#	endif
#elif defined(_MSC_VER) // Intel compiler defines this too (most of the time, not on LRB etc though)
#	define HK_COMPILER_MSVC
#elif defined(__MWERKS__)
#	define HK_COMPILER_MWERKS
#else
#	error Could not detect compiler
#endif

//
// architecture
//
#if defined(__i386__) || defined(_M_IX86)
#	define HK_ARCH_IA32
#	define HK_ENDIAN_LITTLE 1
#	define HK_ENDIAN_BIG	0
#	define HK_POINTER_SIZE 4
#	define HK_NUM_SIMD_REGISTERS 8
#elif defined(_M_AMD64) || defined(_M_X64) || defined(__amd64) || defined(__x86_64)
#	define HK_ARCH_X64
#	define HK_ENDIAN_LITTLE 1
#	define HK_ENDIAN_BIG	0
#	define HK_POINTER_SIZE 8
#	define HK_ARCH_SUPPORTS_INT64
#	define HK_NUM_SIMD_REGISTERS 16
#elif defined(_PPC_) || defined(__POWERPC__) || defined(_M_PPC) || defined(_M_PPCBE) || defined(GEKKO) || defined(EPPC)
#	define HK_ARCH_PPC
#	define HK_ENDIAN_LITTLE 0
#	define HK_ENDIAN_BIG	1
#	define HK_POINTER_SIZE 4
#	define HK_ARCH_SUPPORTS_INT64
#	define HK_NUM_SIMD_REGISTERS 8
#elif defined(__PPU__) && defined(__CELLOS_LV2__)
#	define HK_ARCH_PS3
#	define HK_ENDIAN_LITTLE 0
#	define HK_ENDIAN_BIG	1
#	define HK_POINTER_SIZE 4
#	define HK_ARCH_SUPPORTS_INT64
#	define HK_NUM_SIMD_REGISTERS 32
#elif defined(__SPU__) && defined(__CELLOS_LV2__)
#	define HK_ARCH_PS3SPU
#	define HK_ENDIAN_LITTLE 0
#	define HK_ENDIAN_BIG	1
#	define HK_POINTER_SIZE 4
#	define HK_NUM_SIMD_REGISTERS 128
#elif defined(arm) || defined(__arm__) || defined(_M_ARM)
#   define HK_ARCH_ARM
#   if defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7__) || defined(__ARM_ARCH_7R__) || defined (__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__) || ( defined(_M_ARM) && (_M_ARM >= 7) )
#       define HK_ARCH_ARM_V7 1
#   elif defined(__ARM_ARCH_6__) || defined(__ARM_ARCH_6J__) || defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_6Z__) || defined(__ARM_ARCH_6ZK__) || defined(__ARM_ARCH_6T2__) || defined(NN_PROCESSOR_ARM) || defined(NN_PROCESSOR_ARM_V6) || ( defined(_M_ARM) && (_M_ARM < 7) )
#       define HK_ARCH_ARM_V6 1
#	else 
#		error Unexpected ARM arch
#   endif
#   if defined(__ARMEB__)
#	   define HK_ENDIAN_LITTLE 0
#	   define HK_ENDIAN_BIG	1
#   else 
#	   define HK_ENDIAN_LITTLE 1
#	   define HK_ENDIAN_BIG	0
#   endif
#	define HK_POINTER_SIZE 4
#	define HK_NATIVE_ALIGN_CHECK 0x7 // ptr & 0x7 == 0 for 8 bytes. This works for runtime, but Havok serialization currentlty assumes 16 for some stuff..
#	define HK_NUM_SIMD_REGISTERS 8
#else
#	error Could not autodetect target architecture
#endif


#ifndef HK_NATIVE_ALIGN_CHECK 
#define HK_NATIVE_ALIGN_CHECK 0xf // ptr & 0xf == 0 for 16 bytes
#endif
//
// platform
//
#if defined(__ORBIS__)
#	define HK_PLATFORM_PS4
#	define HK_PLATFORM_IS_CONSOLE 1
#elif defined(__APPLE_CC__)
#   include <TargetConditionals.h> // Specific to the current SDK, in usr\include
#	if defined( HK_ARCH_IA32 )
#     if defined(TARGET_IPHONE_SIMULATOR) && TARGET_IPHONE_SIMULATOR
#			define HK_PLATFORM_IS_CONSOLE 1
#           define HK_PLATFORM_IOS
#           define HK_PLATFORM_IOS_SIM
#     else
#			define HK_PLATFORM_IS_CONSOLE 0
#		    define HK_PLATFORM_MAC386
#     endif
#	elif defined( HK_ARCH_PPC )
#		define HK_PLATFORM_MACPPC
#		define HK_PLATFORM_IS_CONSOLE 0
#   elif defined( HK_ARCH_ARM ) // iPhone /iPod Touch/ iPad
#       define HK_PLATFORM_IOS
#		define HK_PLATFORM_IS_CONSOLE 1
#       if defined(__ARM_NEON__) && defined(HK_ARCH_ARM_V7) && !defined(HK_DISABLE_NEON)
#            define HK_COMPILER_HAS_INTRINSICS_NEON
#		endif
#	else
#		error Mac platform undefined
#	endif
#elif defined(_WIN32) 
#	define HK_PLATFORM_WIN32
#	if defined(_WIN64) 
#		define HK_PLATFORM_X64
#   endif
	// so that we can include this .h before windows etc ones, we use the values not the defines
	#ifndef WINAPI_FAMILY_APP 
		#define WINAPI_FAMILY_APP         0x1
		#define WINAPI_FAMILY_DESKTOP_APP 0x2
		#define WINAPI_FAMILY_PHONE_APP   0x3
		#define ___UNDEF_FAMILY 1
	#endif
#   if defined(WINAPI_FAMILY) && ((WINAPI_FAMILY==WINAPI_FAMILY_APP) || (WINAPI_FAMILY==WINAPI_FAMILY_PHONE_APP))
#		define HK_PLATFORM_WINRT
#		if WINAPI_FAMILY == WINAPI_FAMILY_APP
#			define HK_PLATFORM_METRO 1
#		elif WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP
#			define HK_PLATFORM_IS_CONSOLE 1
#		endif
#	endif
#	ifdef ___UNDEF_FAMILY 
		#undef WINAPI_FAMILY_APP         
		#undef WINAPI_FAMILY_DESKTOP_APP 
		#undef WINAPI_FAMILY_PHONE_APP   
		#undef ___UNDEF_FAMILY
	#endif
#	ifndef HK_PLATFORM_IS_CONSOLE
#		define HK_PLATFORM_IS_CONSOLE 0
#	endif
#elif defined(ANDROID_NDK) || defined(ANDROID) || defined(NDK) || defined(__ANDROID_API__) // Android before Linux as it is that too
#	define HK_PLATFORM_ANDROID
#	define HK_PLATFORM_IS_CONSOLE 1
#	if defined(HK_ARCH_ARM_V7) && !defined(HK_DISABLE_NEON)
#		define HK_COMPILER_HAS_INTRINSICS_NEON 1
#	endif
#elif (defined(__unix__) || defined(__linux__))
#	define HK_PLATFORM_LINUX
#	define HK_PLATFORM_IS_CONSOLE 0
#	if defined(__native_client__) || defined(__nacl__) || defined(NACL)
#		define HK_PLATFORM_NACL
#		undef HK_POINTER_SIZE
#		define HK_POINTER_SIZE 4 // always 4 in NaCl
#	endif
#elif defined(CAFE) || defined(HK_COMPILER_GHS)
#	include <cafe.h>
#	include <ppc_ghs.h> // allow use of intrinsics throughout Havok code
#	define HK_PLATFORM_WIIU
#		define HK_ENABLE_PAIRED_SINGLE_OPTS
#		define HK_VECTOR_PARTS_MUST_BE_VALID
#	define HK_PLATFORM_IS_CONSOLE 1
#elif defined(GEKKO) || defined(__PPCGEKKO__) //Also have custom added HK_REVOLUTION compiler switch
#	define HK_PLATFORM_GC
#	if defined(RVL_OS)
#		define HK_ENABLE_PAIRED_SINGLE_OPTS
#		define HK_PLATFORM_RVL
#	endif
#	define HK_PLATFORM_IS_CONSOLE 1
#elif defined(__PPU__) && defined(__CELLOS_LV2__)
#	define HK_PLATFORM_PS3
#	define HK_PLATFORM_PS3_PPU
#	define HK_PLATFORM_IS_CONSOLE 1
#elif defined(__SPU__) && defined(__CELLOS_LV2__)
#	define HK_PLATFORM_PS3
#	define HK_PLATFORM_PS3_SPU
#	define HK_PLATFORM_SPU
#	define HK_PLATFORM_IS_CONSOLE 1
#elif defined(__CTR__) || defined(NN_PLATFORM_CTR)
#	define HK_PLATFORM_CTR
#	define HK_PLATFORM_IS_CONSOLE 1
#elif (defined(HK_ARCH_ARM) && defined(HK_COMPILER_SNC))
#	define HK_PLATFORM_PSVITA 1
#	define HK_PLATFORM_IS_CONSOLE 1
#	define HK_COMPILER_HAS_INTRINSICS_NEON 1
#else
#	error Could not autodetect target platform.
#endif

#if defined(HK_COMPILER_MSVC) || defined(HK_COMPILER_INTEL)
#	define HK_ALIGN_OF(T) __alignof(T)
#elif defined(HK_COMPILER_GCC) || defined(HK_COMPILER_SNC) || defined(HK_COMPILER_CLANG)
#	define HK_ALIGN_OF(T) __alignof__(T)
#elif defined(HK_COMPILER_MWERKS)
#	define HK_ALIGN_OF(T) __builtin_align(T)
#else
#	error fixme
#endif


//
// types
//

/// hkFloat is provided if floats are explicitly required.
typedef float  hkFloat32;
/// hkDouble is provided if doubles are explicit required.
typedef double hkDouble64;

/// Signed 8 bit integer
typedef signed char		hkChar;
/// Signed 8 bit integer
typedef signed char		hkInt8;
/// Signed 16 bit integer
typedef signed short	hkInt16;
/// Signed 32 bit integer
typedef signed int		hkInt32;

/// Unsigned 8 bit integer
typedef unsigned char	hkUchar;
/// Unsigned 8 bit integer
typedef unsigned char	hkUint8;
/// Unsigned 16 bit integer
typedef unsigned short	hkUint16;
/// Unsigned 32 bit integer
typedef unsigned int	hkUint32;

typedef hkFloat32 hkFloat32;
typedef hkDouble64 hkDouble64;
#define HK_ALIGN_FLOAT HK_ALIGN16
#define HK_ALIGN_DOUBLE HK_ALIGN32
#define HK_FLOAT_ALIGNMENT 16
#define HK_DOUBLE_ALIGNMENT 32
#define HK_FLOAT_SIZE 4
#define HK_DOUBLE_SIZE 8

/// hkReal is the default floating point type.
#if defined(HK_REAL_IS_DOUBLE)
typedef hkDouble64 hkReal;
#define HK_ALIGN_REAL HK_ALIGN_DOUBLE
#define HK_REAL_ALIGNMENT HK_DOUBLE_ALIGNMENT
#define HK_REAL_SIZE HK_DOUBLE_SIZE
#else
typedef hkFloat32 hkReal;
#define HK_ALIGN_REAL HK_ALIGN_FLOAT
#define HK_REAL_ALIGNMENT HK_FLOAT_ALIGNMENT
#define HK_REAL_SIZE HK_FLOAT_SIZE
#endif

#if defined(HK_ARCH_X64)
#	if defined(HK_PLATFORM_X64)
		typedef unsigned __int64 hkUlong;  // MS- specific
		typedef signed __int64 hkLong;  // MS- specific
#	else
		typedef unsigned long hkUlong; // LINUX64
		typedef signed long hkLong; // LINUX64
#	endif
#elif defined(HK_COMPILER_MSVC) && (_MSC_VER >= 1300)
	typedef unsigned long __w64 hkUlong; // VC7.0 or higher, 64bit warnings
	typedef signed long __w64 hkLong; 
#else
	typedef unsigned long hkUlong;
	typedef signed long hkLong;
#endif


#define HK_CPU_PTR( A ) A

#if defined(__GNUC__) && (__GNUC__ >= 3)
	typedef	__builtin_va_list hk_va_list;
#elif defined(HK_COMPILER_ARMCC)
	#include <stdarg.h>
	typedef	va_list hk_va_list;
#else
	typedef void* hk_va_list;
#endif




//
// useful macros
//

#if  (defined(DEBUG) || defined(_DEBUG) || defined(HK_DEBUG)) && !defined(HK_DISABLE_DEBUG)
#	undef HK_DEBUG
#	define HK_DEBUG
#	define HK_ON_DEBUG(CODE)		CODE
#else
#	undef HK_DEBUG
#	define HK_ON_DEBUG(CODE)
#endif

// use the compiler friendly but programmer ugly version for release only
#ifdef HK_DEBUG
#	define HK_MULTILINE_MACRO_BEGIN	do {
#	define HK_MULTILINE_MACRO_END		} while(0)
#else
#		define HK_MULTILINE_MACRO_BEGIN	if(1) {
#		define HK_MULTILINE_MACRO_END		} else
#endif

#if defined(HK_ARCH_IA32) || defined(HK_ARCH_X64)
#	if defined(HK_COMPILER_MSVC) 
#		define HK_BREAKPOINT(ID) __debugbreak();
#   elif defined(HK_PLATFORM_NACL) // not allowed raise interrupts
#		define HK_BREAKPOINT(ID) ((*((int*)0)) = ID);
#	elif defined(HK_COMPILER_GCC) || defined(HK_COMPILER_CLANG)
#		define HK_BREAKPOINT(ID) asm("int $3")
#	else
#		error unknown asm syntax for PC platform
#	endif
#elif defined(HK_PLATFORM_LRB)
#	include <unistd.h>
#	include <signal.h>
#	define HK_BREAKPOINT(ID) signal(SIGSTOP, HK_NULL);
#elif defined(HK_PLATFORM_PS3_PPU) 
#		define HK_BREAKPOINT(ID) __asm__ volatile ( "tw 31,1,1" )
#elif defined(HK_PLATFORM_PS3_SPU)
#	define HK_BREAKPOINT(ID) __asm__ volatile ("ilhu $0, %0\n\tiohl $0, %1\n\tstopd $0,$0,$0" : : "i"(ID>>16), "i"(ID&0xFFFF) ); 
#elif defined(HK_PLATFORM_XBOX360)
#	define HK_BREAKPOINT(ID) __debugbreak();
#elif defined(HK_PLATFORM_WIIU)
#	define HK_BREAKPOINT(ID) OSDebug();
#elif defined(HK_PLATFORM_GC)
#	define HK_BREAKPOINT(ID)    HK_MULTILINE_MACRO_BEGIN						\
								{                                               \
									register unsigned int HK_ORIGINAL_MSR;		\
									register unsigned int HK_NEW_MSR;			\
									asm volatile								\
									{											\
										mfmsr HK_ORIGINAL_MSR; 					/* Grab the original value of the MSR */ \
										ori HK_NEW_MSR, HK_ORIGINAL_MSR, 0x400; /* or the original MSR with 0x400 and store it */ \
										mtmsr HK_NEW_MSR; 						/* Set the MSR to the new value - this will throw exception 0xD00 */ \
										mtmsr HK_ORIGINAL_MSR; 					/* This puts the MSR back to its original state; required for*/\
																				/* getting out of single-step mode (when the user resumes) */\
									}											\
								}   											\
								HK_MULTILINE_MACRO_END

#elif defined(HK_PLATFORM_CTR)
#	include <nn/dbg.h>
#	define HK_BREAKPOINT(ID) ::nn::dbg::Break(nn::dbg::BREAK_REASON_ASSERT);

#elif defined(HK_ARCH_ARM)
#	if defined(HK_COMPILER_MSVC) 
#		define HK_BREAKPOINT(ID) __debugbreak();
#	elif defined(HK_COMPILER_SNC) 
#		define HK_BREAKPOINT(ID) __breakpoint(0);
#	else
#		define HK_BREAKPOINT(ID) asm("bkpt 0"); 
#	endif
#else
#	define HK_BREAKPOINT(ID) ((*((int*)0)) = ID);
#endif

#define HK_NULL 0

#if defined (HK_COMPILER_MSVC)
#	if (_MSC_VER >= 1700)
#		define HK_OVERRIDE override
#		define HK_FINAL	final
#		define HK_FINAL_OVERRIDE final override
#	elif (_MSC_VER >= 1600)
#		define HK_OVERRIDE override
#		define HK_FINAL	sealed
#		define HK_FINAL_OVERRIDE sealed override
#	elif (_MSC_VER >=1400)
#		define HK_OVERRIDE override
#		define HK_FINAL
#		define HK_FINAL_OVERRIDE override
#	else
#		define HK_OVERRIDE 
#		define HK_FINAL 
#		define HK_FINAL_OVERRIDE
#	endif
#else
#	define HK_OVERRIDE 
#	define HK_FINAL 
#	define HK_FINAL_OVERRIDE
#endif

/// Note that ALIGNMENT must be a power of two for this to work.
/// Note: to use this macro you must cast your pointer to a byte pointer or to an integer value.
#define HK_NEXT_MULTIPLE_OF(ALIGNMENT, VALUE)  ( ((VALUE) + ((ALIGNMENT)-1)) & (~((ALIGNMENT)+(VALUE)*0-1)) )

/// The offset of a member within a structure
#define HK_OFFSET_OF(CLASS,MEMBER) int(reinterpret_cast<hkLong>(&(reinterpret_cast<CLASS*>(16)->MEMBER))-16)

/// A check for whether the offset of a member within a structure is as expected
#define HK_OFFSET_EQUALS(CLASS,MEMBER,OFFSET) (HK_OFFSET_OF(CLASS,MEMBER)==OFFSET)

/// Join two preprocessor tokens, even when a token is itself a macro.
#define HK_PREPROCESSOR_JOIN_TOKEN(A,B) HK_PREPROCESSOR_JOIN_TOKEN2(A,B)
#define HK_PREPROCESSOR_JOIN_TOKEN2(A,B) HK_PREPROCESSOR_JOIN_TOKEN3(A,B)
#define HK_PREPROCESSOR_JOIN_TOKEN3(A,B) A##B

/// Creates an uninitialized buffer large enough for object of type TYPE to fit in while aligned to ALIGN boundary. Creates a pointer VAR to this aligned address.
#define HK_DECLARE_ALIGNED_LOCAL_PTR( TYPE, VAR, ALIGN  )											\
	const int VAR ## BufferSize = ALIGN + sizeof(TYPE);												\
	char VAR ## Buffer[VAR ## BufferSize];															\
	TYPE* VAR = reinterpret_cast<TYPE*>( HK_NEXT_MULTIPLE_OF(ALIGN, hkUlong( VAR ## Buffer )) );	\


//
// compiler specific settings
//


	// *************************************
	//			GCC, SN and CLANG
	// *************************************
#if defined(HK_COMPILER_GCC) || defined(HK_COMPILER_SNC) || defined(HK_COMPILER_GHS) || defined(__GCCXML__) || defined(HK_COMPILER_CLANG)
#       if defined(__GNUC_PATCHLEVEL__)
#   	    define HK_COMPILER_GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 +__GNUC_PATCHLEVEL__)
#	    else
#		    define HK_COMPILER_GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100)
#		endif

#	define HK_RESTRICT __restrict


#	if (HK_COMPILER_GCC_VERSION >= 40000)
#		undef HK_OFFSET_OF
#		define HK_OFFSET_OF(CLASS,MEMBER) __builtin_offsetof(CLASS,MEMBER)
#	elif ( HK_COMPILER_GCC_VERSION >= 30400 ) && !defined( HK_COMPILER_SNC )
#		undef HK_OFFSET_OF
#		define HK_OFFSET_OF(CLASS,MEMBER) (__offsetof__(reinterpret_cast<long>(&reinterpret_cast<CLASS*>(16)->MEMBER)-16))
#	endif

#	if ( HK_COMPILER_GCC_VERSION >= 40000 ) && !defined( HK_COMPILER_SNC )
#		undef HK_OFFSET_EQUALS
#		define HK_OFFSET_EQUALS(C,M,O) true
#	endif

#	define HK_ALIGN(DECL, ALIGNMENT) DECL __attribute__((aligned(ALIGNMENT)))
#	define HK_ALIGN8(DECL) DECL __attribute__((aligned(8)))
#   define HK_ALIGN16(DECL) DECL __attribute__((aligned(16)))
#   define HK_ALIGN32(DECL) DECL __attribute__((aligned(32)))
#   define HK_ALIGN64(DECL) DECL __attribute__((aligned(64)))
#   define HK_ALIGN128(DECL) DECL __attribute__((aligned(128)))
#	define HK_CLASSALIGN(DECL, ALIGNMENT) HK_ALIGN(DECL, ALIGNMENT)
#	define HK_CLASSALIGN8(DECL) HK_ALIGN8(DECL)
#	define HK_CLASSALIGN16(DECL) HK_ALIGN16(DECL)

#	if defined(HK_ARCH_ARM) || defined(HK_COMPILER_GHS) || defined(HK_PLATFORM_IOS_SIM)
#		define HK_ALIGN_RELAX_CHECKS 1
#	endif

#		define HK_VISIBILITY_HIDDEN __attribute__((visibility("hidden")))


		typedef unsigned long long hkUint64;
		typedef long long hkInt64;

		typedef long hkSystemTime;

#if ( defined(HK_PLATFORM_LINUX) && defined(HK_ARCH_X64) && !defined(HK_PLATFORM_NACL) ) || (defined(__GCCXML__) && defined(__x86_64)) // LINUX64 but not NACL64
		typedef long unsigned int hk_size_t;
#	else
		typedef unsigned hk_size_t;
#	endif

#	if (defined(HK_ARCH_IA32) && HK_COMPILER_GCC_VERSION >= 30100) || defined(HK_PLATFORM_NACL)
#		define HK_COMPILER_HAS_INTRINSICS_IA32
#	endif

#ifdef __HAVOK_PARSER__
#   define HK_FORCE_INLINE /*nothing*/
#elif defined(HK_PLATFORM_CTR)
#	define HK_FORCE_INLINE __forceinline
#elif defined(HK_PLATFORM_PS4)
#	define HK_FORCE_INLINE inline __attribute__((always_inline)) 
#else
#	define HK_FORCE_INLINE inline
#endif
// calling convention
#	define HK_CALL
#	define HK_FAST_CALL
// deprecation
#	define HK_DEPRECATED /* nothing */
#	define HK_DEPRECATED2(MSG) /* nothing */
// Section attribute. Placing each function in a different section allows the linker to dead-strip them individually
#	define HK_INIT_FUNCTION2(FN, SECTION_SUFFIX)	__attribute__ ((section (".text_init." #SECTION_SUFFIX))) FN
#	define HK_INIT_FUNCTION(FN)						HK_INIT_FUNCTION2(FN, FN)

	// *************************************
	//			MICROSOFT and INTEL
	// *************************************
#elif defined(HK_COMPILER_MSVC) || defined(HK_COMPILER_INTEL)
#	define HK_COMPILER_SUPPORTS_PCH
#	define HK_COMPILER_MSVC_VERSION _MSC_VER
#	ifdef __INTEL_COMPILER
#		define HK_COMPILER_INTEL_VERSION __INTEL_COMPILER
#	else
#		define HK_COMPILER_INTEL_VERSION _MSC_VER
#	endif
#	if (_MSC_VER >= 1400) // 2005 only
#		define HK_RESTRICT __restrict
#	else
#		define HK_RESTRICT 
#	endif
#	pragma warning( disable : 4786 ) // Debug tuncated to 255:
#	pragma warning( disable : 4530 ) // C++ Exception handler used but not enabled:(used in <xstring>)
#		define HK_ALIGN(DECL, ALIGNMENT) __declspec(align(ALIGNMENT)) DECL
#		define HK_ALIGN8(DECL) __declspec(align(8)) DECL
#		define HK_ALIGN16(DECL) __declspec(align(16)) DECL
#		define HK_ALIGN32(DECL) __declspec(align(32)) DECL
#		define HK_ALIGN64(DECL) __declspec(align(64)) DECL
#		define HK_ALIGN128(DECL) __declspec(align(128)) DECL
#		if !defined(HK_COMPILER_INTEL)
#			define HK_FORCE_INLINE __forceinline
#		else // ICC has no force inline intrinsic
#			define HK_FORCE_INLINE inline
#		endif
#		define HK_CLASSALIGN(DECL, ALIGNMENT) HK_ALIGN(DECL, ALIGNMENT)
#		define HK_CLASSALIGN8(DECL) HK_ALIGN8(DECL)
#		define HK_CLASSALIGN16(DECL) HK_ALIGN16(DECL)
#		define HK_VISIBILITY_HIDDEN /*empty*/
#		define HK_NEVER_INLINE __declspec(noinline)
#	if defined(HK_ARCH_IA32) || defined(HK_ARCH_ARM) 
		typedef unsigned __int64 hkUint64;
		typedef __int64 hkInt64;
		typedef long hkSystemTime;
#		if defined(HK_COMPILER_MSVC) && (_MSC_VER >= 1300)
			typedef unsigned __w64 hk_size_t; // VC7.0 or higher, 64bit warnings
#		else
			typedef unsigned hk_size_t;
#		endif
#		ifdef HK_ARCH_IA32
#			define HK_COMPILER_HAS_INTRINSICS_IA32
#		elif defined(HK_ARCH_ARM) && !defined(HK_DISABLE_NEON)
#			define HK_COMPILER_HAS_INTRINSICS_NEON
#		endif
#	elif defined( HK_ARCH_PPC )
		typedef unsigned __int64 hkUint64;
		typedef __int64 hkInt64;
		typedef unsigned hk_size_t;
		typedef __int64 hkSystemTime; // 64bit time
#		define HK_COMPILER_HAS_INTRINSICS_PPC
#	elif defined(HK_ARCH_X64) || defined(HK_ARCH_LRB)
		typedef unsigned __int64 hkUint64;
		typedef __int64 hkInt64;
		typedef __int64 hkSystemTime;
		typedef unsigned __int64 hk_size_t;
#			define HK_COMPILER_HAS_INTRINSICS_IA32
#	else
#		error No defs for this architecture
#	endif
// calling convention
#	ifndef HK_COMPILER_INTEL
#		define HK_CALL __cdecl
#		define HK_FAST_CALL __fastcall
#	else
#		define HK_CALL 
#		define HK_FAST_CALL 
#	endif
// deprecation
#	if defined(HK_PLATFORM_WIN32) && (_MSC_VER >= 1300) && !defined(MIDL_PASS)
#		define HK_DEPRECATED __declspec(deprecated)
#		define HK_DEPRECATED2(MSG) __declspec(deprecated(MSG))
#	else
#		define HK_DEPRECATED /* nothing */
#		define HK_DEPRECATED2(MSG) /* nothing */
#	endif

	// *************************************
	//			METROWERKS
	// *************************************
#elif defined(HK_COMPILER_MWERKS)
#	define HK_ALIGN(DECL, ALIGNMENT) DECL __attribute__((aligned(ALIGNMENT)))
#	define HK_ALIGN8(DECL) DECL __attribute__((aligned(8)))
#	define HK_ALIGN16(DECL) DECL __attribute__((aligned(16)))
#	define HK_ALIGN32(DECL) DECL __attribute__((aligned(32)))
#	define HK_ALIGN64(DECL) DECL __attribute__((aligned(64)))
#	define HK_ALIGN128(DECL) DECL __attribute__((aligned(128)))
#	define HK_CLASSALIGN(DECL, ALIGNMENT) DECL
#	define HK_CLASSALIGN16(DECL) DECL
#	define HK_VISIBILITY_HIDDEN /*empty*/
		typedef unsigned long long hkUint64;
		typedef long long hkInt64;
			typedef unsigned long hkSystemTime;
		typedef unsigned long hk_size_t;
#	define HK_FORCE_INLINE inline
// calling convention
#	define HK_CALL
#	define HK_FAST_CALL
// deprecation
#	define HK_DEPRECATED /* nothing */
#	define HK_DEPRECATED2(MSG) /* nothing */

#else
#	error Unknown compiler
#endif // compilers

#ifndef HK_LINKONCE_VTABLES
#define HK_LINKONCE_VTABLES 1 
#endif

#ifndef HK_HASHCODE_VTABLE_REGISTRY
#define HK_HASHCODE_VTABLE_REGISTRY 0 
#endif

#ifndef HK_NATIVE_ALIGNMENT
#define HK_NATIVE_ALIGNMENT 16
#endif

#	define HK_ON_PLATFORM_SIM(code)

// HK_PLATFORM_PPU is defined in both PlayStation(R)3 PPU and simulator PPU in the same way that HK_PLATFORM_SPU is defined in 
// PlayStation(R)3 SPU and simulator SPU.

#	define HK_ON_PLATFORM_HAS_SPU(code)

#	define HK_PLATFORM_MULTI_THREAD

#	define HK_ALWAYS_INLINE HK_FORCE_INLINE
#	define HK_LOCAL_INLINE HK_FORCE_INLINE
#	define HK_ASM_SEP(a) 

#ifndef HK_NEVER_INLINE
#	if defined(HK_COMPILER_GCC) && !defined(HK_COMPILER_ARMCC)
#		define HK_NEVER_INLINE __attribute__((noinline))
#else
#		define HK_NEVER_INLINE
#	endif
#endif

#ifndef HK_AUTO_INLINE
#		define HK_AUTO_INLINE HK_FORCE_INLINE
#endif

#	define HK_NOSPU_VIRTUAL virtual
#	define HK_CPU_CONST const

#ifndef HK_RESTRICT
#	define HK_RESTRICT
#endif
#ifndef HK_VERY_UNLIKELY
#	define HK_VERY_UNLIKELY(EXPR) EXPR
#	define HK_VERY_LIKELY(EXPR) EXPR
#endif
#ifndef HK_INIT_FUNCTION
#	define HK_INIT_FUNCTION( FN ) FN
#	define HK_INIT_FUNCTION2(FN, SECTION_SUFFIX) FN
#endif

// VS 2008 x64 compiler bug workaround
#if defined ( HK_COMPILER_MSVC ) &&( _MSC_VER == 1500 ) && defined ( HK_ARCH_X64 ) && defined ( HK_COMPILER_OPTIMIZATIONS_ON )
#		define HK_DISABLE_OPTIMIZATION_VS2008_X64 __pragma(optimize ("g", off))
#		define HK_RESTORE_OPTIMIZATION_VS2008_X64  __pragma(optimize ("g", on))
#else
#		define HK_DISABLE_OPTIMIZATION_VS2008_X64 
#		define HK_RESTORE_OPTIMIZATION_VS2008_X64  
#endif

#endif // HKBASE_HKBASEDEFS_H

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
