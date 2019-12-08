/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#ifndef	HKCD_CONTAINMENT_POINT_IN_TRIANGLE
#define HKCD_CONTAINMENT_POINT_IN_TRIANGLE

#include <Geometry/Collide/Algorithms/Triangle/hkcdTriangleUtil.h>


/// Tests whether the given point vP is inside the triangle (vA, vB, vC). The triangle normal is also required as input in vN.
/// On success (i.e. point in triangle), the function provides the barycentric coordinates if baryOut is not null.
HK_FORCE_INLINE hkBool32 HK_CALL hkcdIntersectPointTriangle(hkVector4Parameter vP,
													 hkVector4Parameter vA, hkVector4Parameter vB, hkVector4Parameter vC,
													 hkVector4Parameter vN,
													 hkSimdRealParameter tolerance,
													 hkVector4* HK_RESTRICT baryOut = HK_NULL);

/// Tests whether the given point vP is inside the triangle (vA, vB, vC).
/// On success (i.e. point in triangle), the function provides the barycentric coordinates if baryOut is not null.
HK_FORCE_INLINE hkBool32 HK_CALL hkcdIntersectPointTriangle(hkVector4Parameter vP,
													 hkVector4Parameter vA, hkVector4Parameter vB, hkVector4Parameter vC,
													 hkSimdRealParameter tolerance,
													 hkVector4* HK_RESTRICT baryOut = HK_NULL);

#include <Geometry/Internal/Algorithms/Intersect/hkcdIntersectPointTriangle.inl>

#endif	//	HKCD_CONTAINMENT_POINT_IN_TRIANGLE

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
