/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKBASE_HKBASE_H
#define HKBASE_HKBASE_H

#include <Common/Base/Types/hkBaseDefs.h>

#if defined HK_COMPILER_MSVC
	// C4100 'identifier' : unreferenced formal parameter
	//		a function need not use all its arguments
	// C4127 conditional expression is constant
	//		constant conditionals are often used inside asserts
	// C4505 'function' : unreferenced local function has been removed
	//		lots of inline functions are not used in a compilation unit
	// C4510 'class' : default constructor could not be generated
	// C4511 'class' : copy constructor could not be generated
	// C4512 'class' : assignment operator could not be generated
	//		many classes are not designed with value semantics
	// C4514 unreferenced inline/local function has been removed
	//		lots of inline functions are not used in a compilation unit
	// C4714 force inlined function not inlined. This warning is only disabled in debug modes.
	// C4481: nonstandard extension used: override specifier 'override'
	//		disable warning if we're using HK_OVERRIDE
#	pragma warning(push)
#	pragma warning(disable: 4100 4127 4324 4505 4510 4511 4512 4514)
//#	pragma warning(disable: 1684 981 1419 1418 271 1572 128 ) // Intel compiler warnings
#	if defined(HK_DEBUG)
#		pragma warning(disable: 4714) 
#	endif
#if (_MSC_VER >= 1400)
#		pragma warning(disable: 4481) 
#	if (_MSC_VER >= 1700) 
#		pragma warning(disable: 6326) // hkMath: constant comapred against constant: happens all the time wth our tenmplated opts
#	endif
#endif
#if (_MSC_VER >= 1700) 
#		pragma warning(disable: 6326) // hkMath: constant comapred against constant: happens all the time wth our tenmplated opts
#endif
#	ifndef _CRT_SECURE_NO_DEPRECATE
#		define _CRT_SECURE_NO_DEPRECATE 1
#	endif
#	ifndef _CRT_NONSTDC_NO_DEPRECATE
#		define _CRT_NONSTDC_NO_DEPRECATE 1
#	endif

#elif defined(HK_COMPILER_GHS)
#	pragma ghs nowarning 1721 // var shadows function. y0 etc delc as functions in no namespace in ghs math.h !?
#	pragma ghs nowarning 381  // extra ;
#	pragma ghs nowarning 826  // unused param
#	pragma ghs nowarning 236  // constant control var
#	pragma ghs nowarning 1931  // sizeof a builtin bool etc
#	pragma ghs nowarning 1795  // __ in name may be not debuggable
#	pragma ghs nowarning 111  // unreachable statement
#	pragma ghs nowarning 177  // func declared but never referenced
#	pragma ghs nowarning 1518  // ansi alaising rules being turned off.. 
#	pragma ghs nowarning 1586  // force noinline on what the compiler thinks is inline warns a lot (on templated classes it seems)


#elif defined HK_COMPILER_ARMCC
	// By default ARMCC is very picky with its warnings

	// 826 = unused var, in Havok when we inherit we always use full arg list, but can ignore it
	// 1297, 1298= Header file not guarded against multiple inclusion, and it interprets .inl files as include files etc which do not need them. 1298 is that what looks like header file guard is not defined, which can happen for non TKBMS headers for PlayStation(R)3 SPU etc
	// 1301, 253, 2530: padding added to struct Blah. A good few structs in Havok have implicit, known, padding
	// 399,831 : no delete[] for a new[], yet it is a placement new[] that is at fault, and placement delete[] raises a further warning. Placement delete[] will never be called.
	// 2525 : pragma push with no pop: this is as intended. If clients want to restore settings after incl Havok they can pop, otherwise leave as is
	// 340 : 'value copied to temporary, reference to temporary used'. Gets triggered by most uses of unions to do type conversion etc, so all false positives in Havok code
	// 401 : non virtual dtor in parent. This will be cleaned up
	// 2523 : use of inline assembler is deprecated (from nn headers, not Havoks)
#	pragma push
#	pragma diag_suppress 826,1297,1298,1301,253,2530,399,831,2525,401,340,2523
#	ifndef HK_DEBUG 
		// 2814 : empty else statement. Should be cleaned up, but all from HK_ASSERT(0x5545d218) style else blocks
#		pragma diag_suppress 2814
#	endif

#elif defined(HK_COMPILER_CLANG)
#	ifndef __HAVOK_PARSER__
#		pragma clang diagnostic ignored "-Wc++11-narrowing"
#	endif
#	pragma clang diagnostic ignored "-Wconstant-logical-operand"
#	pragma clang diagnostic ignored "-Wunused-function"
#	pragma clang diagnostic ignored "-Wunused-variable"
#	pragma clang diagnostic ignored "-Wunused-value"

#elif defined(HK_COMPILER_SNC)
#	pragma diag_push
#		pragma diag_suppress=1787 // ... is not a valid value for the enumeration ... : hkVectorPermutation::Permutation doesn't cover the entire space of permuatations
#		pragma diag_suppress=1786 // violates strict-aliasing rules :
#		pragma diag_suppress=237 // controlling expression is constant : mostly used in debugging code and macros
#		pragma diag_suppress=178 // ... was declared but never referenced : there are some complicated ifdefs which make it difficult to be 100% correct
#		pragma diag_suppress=112 // statement is unreachable : some math library template methods expect a switch to be eliminated and thus all other branches are unreachable
//#	pragma diag_pop // after including havok headers
#endif

#include <Common/Base/Types/hkBaseTypes.h>



#include <Common/Base/Memory/MemoryClasses/hkMemoryClassDefinitions.h>

#include <Common/Base/Memory/Router/hkMemoryRouter.h>

#include <Common/Base/Object/hkBaseObject.h>
#include <Common/Base/Object/hkReferencedObject.h>

#include <Common/Base/Object/hkSingleton.h>
#include <Common/Base/Types/hkRefPtr.h>

#include <Common/Base/System/Io/OStream/hkOStream.h>	/* <todo> remove */

#undef HK_CRITICAL_ASSERT2
#undef HK_ASSERT2
#undef HK_ERROR

#include <Common/Base/System/Error/hkError.h>
#include <Common/Base/Types/hkScopedPtr.h>

struct hkPlacementNewArg;
inline void* operator new(hk_size_t, hkPlacementNewArg* p) { return p; }
inline void* operator new[](hk_size_t, hkPlacementNewArg* p) { return p; }
inline void operator delete(void* /*unused*/, hkPlacementNewArg* /*unused*/) { HK_ASSERT(0x5c4071a3, false); }
inline void operator delete[](void* /*unused*/, hkPlacementNewArg* /*unused*/) { HK_ASSERT(0x7ca45d11, false); }

#include <Common/Base/Types/hkTypeTraits.h>
#include <Common/Base/Memory/Util/hkMemUtil.h>
#include <Common/Base/Container/Array/hkArray.h>
#include <Common/Base/Container/Array/hkSmallArray.h>
#include <Common/Base/Container/PointerMap/hkPointerMap.h>
#include <Common/Base/Types/hkRefVariant.h>
#include <Common/Base/Types/hkUFloat8.h>

#include <Common/Base/Math/hkMath.h>

#include <Common/Base/Container/String/hkString.h>
#include <Common/Base/Container/String/hkStringPtr.h>

#endif // HKBASE_HKBASE_H

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
