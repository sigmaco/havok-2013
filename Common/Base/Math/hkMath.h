/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_MATH_MATH_H
#define HK_MATH_MATH_H

#include <Common/Base/Types/hkBaseTypes.h>
#include <Common/Base/Config/hkConfigSimd.h>
#include <Common/Base/Fwd/hkcmath.h>
#include <Common/Base/Fwd/hkcfloat.h>


// Temporarily disable the alignment warning for AMD64
#if defined(HK_PLATFORM_X64)
#	pragma warning( disable: 4328 )
#endif

// Function to check whether or not denormals are being flushed to zero.
// All Havok math code expects this mode to be set, and may not function correctly if it isn't.
// Typically operations on denormals are very slow, up to 100 times slower than normal numbers.

void HK_CALL hkCheckFlushDenormals();
#if defined(HK_DEBUG)
#	define HK_CHECK_FLUSH_DENORMALS() hkCheckFlushDenormals()
#else
#	define HK_CHECK_FLUSH_DENORMALS()
#endif


// The order of these includes is crucial.
#include <Common/Base/Math/Header/hkMathHeaderConstantDefinitions.h>
#include <Common/Base/Math/Header/hkMathHeaderEnums.h>
#include <Common/Base/Math/Header/hkMathHeaderTypes.h>
#include <Common/Base/Math/Header/hkMathHeaderConstants.h>
#include <Common/Base/Math/Header/hkMathHeaderFuncs.h>
#include <Common/Base/Math/Header/hkMathHeaderUnions.h>
#include <Common/Base/Math/Header/hkMathHeaderForwardDeclarations.h>
#include <Common/Base/Math/Header/hkMathHeaderIncludes.h>
#include <Common/Base/Math/Header/hkMathHeaderPlatformImplementations.h>
#include <Common/Base/Math/Header/hkMathHeaderSharedImplementations.h>
#include <Common/Base/Math/Header/hkMathHeaderAliases1.h>
#include <Common/Base/Math/Header/hkMathHeaderAliases2.h>
#include <Common/Base/Math/Header/hkMathHeaderMxClasses.h>

#include <Common/Base/Math/hkMathMixedOperators.h>


#endif // HK_MATH_MATH_H

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
