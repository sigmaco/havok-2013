/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#ifndef	HKCD_DISTANCES_AABB_AABB
#define HKCD_DISTANCES_AABB_AABB

#include <Common/Base/Math/Vector/hkFourTransposedPoints.h>

	/// Computes the distance squared between two non-overlaping AABBs, else returns zero.
HK_FORCE_INLINE hkSimdReal hkcdAabbAabbDistanceSquared(const hkAabb& aabb0, hkVector4Parameter center1, hkVector4Parameter halfExtents1);

	/// Computes the distance squared between two non-overlaping AABBs, else returns zero.
HK_FORCE_INLINE hkSimdReal hkcdAabbAabbDistanceSquared(const hkAabb& aabb0, const hkAabb& aabb1);

	/// Computes the squared distance between a point and an AABB
HK_FORCE_INLINE const hkSimdReal hkcdPointAaabbDistanceSquared(hkVector4Parameter vPt, const hkAabb& aabb);

#include <Geometry/Internal/Algorithms/Distance/hkcdDistanceAabbAabb.inl>

#endif // HKCD_DISTANCES_AABB_AABB

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
