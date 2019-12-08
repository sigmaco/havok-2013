/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_MATH_VECTOR4_UTIL_INTERNAL_H
#define HK_MATH_VECTOR4_UTIL_INTERNAL_H

#include <Common/Base/Types/Geometry/Aabb/hkAabb.h>
#include <Common/Base/Math/Vector/hkIntVector.h>
#include <Common/Base/Math/Vector/hkFourTransposedPoints.h>

class hkStringBuf;

// Secret/internal optimized math functions
namespace hkVector4UtilInternal
{
	//
	// AABB utilities.	
	//

	// Compute the surface area of an AABB.
	static HK_FORCE_INLINE hkSimdReal surfaceArea(const hkAabb& aabb);

	// Check for AABB overlaps using 6 separating axis.
	static HK_FORCE_INLINE hkBool32	overlaps6(const hkAabb& aabbA, const hkAabb& aabbB, const hkTransform& BtoA, const hkTransform& AtoB);

	// Compute ray inverse direction from direction.
	static HK_FORCE_INLINE void	computeRayInverseDirection(hkVector4Parameter dir, hkVector4& invDirOut);

	// Check for intersection with a ray starting at the origin between fraction zero and maxFraction.
	static HK_FORCE_INLINE hkBool32	intersectRay(const hkAabb& aabb, hkVector4Parameter rayInvDir, hkSimdRealParameter maxFraction);
	
	// Check for intersection with a ray between fraction zero and maxFraction.
	static HK_FORCE_INLINE hkBool32	intersectRay(const hkAabb& aabb, hkVector4Parameter rayOrg, hkVector4Parameter rayInvDir, hkSimdRealParameter maxFraction);

	// Check for intersection with a ray bundle between fraction zero and maxFraction.
	// The returned hkVector4Comparison components are set depending on which rays hit.
	static HK_FORCE_INLINE hkVector4Comparison intersectRayBundle(const hkAabb& aabb, const hkFourTransposedPoints& rayOrg, const hkFourTransposedPoints& rayInvDir, hkVector4Parameter maxFraction);

	// check a ray against a triangle
	static HK_FORCE_INLINE hkBool32	rayTriangle(hkVector4Parameter rayOrg, hkVector4Parameter rayDir, const hkVector4 v[3], hkSimdReal& fractionInOut, hkVector4& normalOut);
}
		
#if HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED
// #	if defined(HK_COMPILER_HAS_INTRINSICS_IA32)
// #		include <Common/Internal/Math/Sse/hkSseVector4UtilInternal.inl>
// #	elif defined(HK_COMPILER_HAS_INTRINSICS_NEON)
// #		include <Common/Internal/Math//Neon/hkNeonVector4UtilInternal.inl> 
// #	elif defined(HK_PLATFORM_PS3_SPU) || defined(HK_PLATFORM_PS3_PPU)
// #		include <Common/Internal/Math//Ps3/hkPs3Vector4UtilInternal.inl>
// #	elif defined(HK_PLATFORM_XBOX360)
// #		include <Common/Internal/Math/Xbox360/hkXbox360Vector4UtilInternal.inl>
// #	endif
#endif // HK_CONFIG_SIMD

#include <Common/Internal/Math/hkVector4UtilInternal.inl>

#endif // HK_MATH_VECTOR4_UTIL_INTERNAL_H

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
