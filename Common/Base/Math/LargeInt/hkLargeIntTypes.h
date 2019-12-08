/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#ifndef HK_MATH_LARGE_INT_TYPES_H
#define HK_MATH_LARGE_INT_TYPES_H

//
//	Type shortcuts

class hkInt64Vector4;
class hkInt128Vector4;
typedef const hkInt64Vector4&	hkInt64Vector4Parameter;
typedef const hkInt128Vector4&	hkInt128Vector4Parameter;

#include <Common/Base/Math/Vector/hkIntVector.h>
#include <Common/Base/Math/LargeInt/hkSimdInt.h>
#include <Common/Base/Math/LargeInt/hkInt64Vector4.h>
#include <Common/Base/Math/LargeInt/hkInt128Vector4.h>

#ifndef __HAVOK_PARSER__
#if ( HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED )
#	if defined( HK_COMPILER_HAS_INTRINSICS_IA32 )
#		include <Common/Base/Math/LargeInt/Sse/hkSseInt128Vector4.inl>
#		include <Common/Base/Math/LargeInt/Sse/hkSseSimdInt128.inl>
#		include <Common/Base/Math/LargeInt/Sse/hkSseSimdInt.inl>
#		include <Common/Base/Math/LargeInt/Sse/hkSseInt64Vector4.inl>
#	elif defined(HK_COMPILER_HAS_INTRINSICS_NEON)
#		include <Common/Base/Math/LargeInt/Neon/hkNeonInt128Vector4.inl>
#		include <Common/Base/Math/LargeInt/Neon/hkNeonSimdInt128.inl>
#		include <Common/Base/Math/LargeInt/Neon/hkNeonSimdInt.inl>
#		include <Common/Base/Math/LargeInt/Neon/hkNeonInt64Vector4.inl>
#	else
#		include <Common/Base/Math/LargeInt/Fpu/hkFpuInt128Vector4.inl>
#		include <Common/Base/Math/LargeInt/Fpu/hkFpuSimdInt128.inl>
#		include <Common/Base/Math/LargeInt/Fpu/hkFpuSimdInt.inl>
#		include <Common/Base/Math/LargeInt/Fpu/hkFpuInt64Vector4.inl>
#	endif
#else
#	include <Common/Base/Math/LargeInt/Fpu/hkFpuInt128Vector4.inl>
#	include <Common/Base/Math/LargeInt/Fpu/hkFpuSimdInt128.inl>
#	include <Common/Base/Math/LargeInt/Fpu/hkFpuSimdInt.inl>
#	include <Common/Base/Math/LargeInt/Fpu/hkFpuInt64Vector4.inl>
#endif
#endif

#include <Common/Base/Math/LargeInt/hkInt64Vector4.inl>
#include <Common/Base/Math/LargeInt/hkSimdInt128.inl>
#include <Common/Base/Math/LargeInt/hkSimdInt.inl>
#include <Common/Base/Math/LargeInt/hkInt128Vector4.inl>

#endif	//	HK_MATH_LARGE_INT_H

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
