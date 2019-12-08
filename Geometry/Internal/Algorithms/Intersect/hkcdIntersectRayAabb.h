/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#ifndef	HKCD_INTERSECTIONS_RAY_AABB
#define HKCD_INTERSECTIONS_RAY_AABB

#include <Geometry/Internal/Types/hkcdRay.h>
#include <Common/Base/Types/Geometry/Aabb/hkAabb.h>


	/// Returns true if the ray intersects the AABB.
HK_FORCE_INLINE	hkBool32	hkcdIntersectRayAabb(const struct hkcdRay& ray, const hkAabb& aabb, hkSimdReal* HK_RESTRICT fractionInOut);

HK_FORCE_INLINE	hkVector4Comparison	hkcdIntersectRayAabbBundle(const hkcdRay& ray,
														const hkFourTransposedPoints& aabbMin, const hkFourTransposedPoints& aabbMax,
														const hkVector4& fraction);


	/// Returns true if the ray starting at the origin intersects the AABB.
HK_FORCE_INLINE	hkBool32	hkcdRayDirectionAabbIntersect(hkVector4Parameter rayInvDirection, const hkAabb& aabb, hkSimdReal* HK_RESTRICT fractionInOut);

HK_FORCE_INLINE	hkVector4Comparison	hkcdRayDirectionAabbBundleIntersect(hkVector4Parameter rayInvDirection,
																const hkFourTransposedPoints& aabbMin, const hkFourTransposedPoints& aabbMax,
																const hkVector4& fraction);


	/// Returns a bit mask corresponding to the AABBs intersecting the ray.
	/// Test result with hkVector4ComparisonMask::MASK_X for aabb0, hkVector4ComparisonMask::MASK_Y for aabb1 and so on.
HK_FORCE_INLINE int			hkcdIntersectRayBundleAabb(	const hkcdRay& ray, 
															const hkAabb& aabb0, const hkAabb& aabb1, const hkAabb& aabb2, const hkAabb& aabb3, 
															const hkSimdReal& earlyOutHitFraction);

#include <Geometry/Internal/Algorithms/Intersect/hkcdIntersectRayAabb.inl>

#endif // HKCD_INTERSECTIONS_RAY_AABB

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
