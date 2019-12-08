/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#ifndef	HKCD_DISTANCES_POINT_QUAD
#define HKCD_DISTANCES_POINT_QUAD

#include <Common/Base/Math/Vector/hkFourTransposedPoints.h>

/// Returns the squared distance between a point and a convex quad assumed to have proper winding.
HK_FORCE_INLINE	const hkSimdReal HK_CALL hkcdPointConvexQuadDistanceSquared(hkVector4Parameter point, hkVector4Parameter quadVtx0, hkVector4Parameter quadVtx1, hkVector4Parameter quadVtx2, hkVector4Parameter quadVtx3,
																			hkVector4Parameter quadNormalIn, hkVector4* HK_RESTRICT projectionOut = HK_NULL);
HK_FORCE_INLINE	const hkSimdReal HK_CALL hkcdPointConvexQuadDistanceSquared(hkVector4Parameter point, const hkVector4* HK_RESTRICT quadVertsIn, hkVector4Parameter quadNormalIn, hkVector4* HK_RESTRICT projectionOut = HK_NULL);

#include <Geometry/Internal/Algorithms/Distance/hkcdDistancePointQuad.inl>

#endif	//	HKCD_DISTANCES_POINT_QUAD

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
