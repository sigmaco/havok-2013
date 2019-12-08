/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

/// Projects a point onto a convex hull spanned by the given plane equations. Terminates early if the point is further away than indicated by maxDistanceSquared.
/// NOTE: Point and planes must all be defined in the same space.
HK_FORCE_INLINE bool HK_CALL hkcdDistancePointConvex::hkcdPointConvex(	hkVector4Parameter point,
									 const hkVector4* HK_RESTRICT planes, int numPlanes, hkSimdRealParameter maxDistanceSquared,
									 hkVector4& pointOnSurface, hkVector4& surfaceNormal, hkSimdReal& signedDistance, int& numIterationsUsed)
{
	return _hkcdPointConvex(point, planes, numPlanes, maxDistanceSquared, 100, pointOnSurface, surfaceNormal, signedDistance, numIterationsUsed);
}

/// Projects a point onto a convex hull spanned by the given plane equations.
/// NOTE: Point and planes must all be defined in the same space.
HK_FORCE_INLINE bool HK_CALL hkcdDistancePointConvex::hkcdPointConvex(	hkVector4Parameter point,
											 const hkVector4* HK_RESTRICT planes, int numPlanes, 
											 hkVector4& pointOnSurface, hkVector4& surfaceNormal, hkSimdReal& signedDistance, int& numIterationsUsed)
{
	return _hkcdPointConvex(point, planes, numPlanes, hkSimdReal::getConstant<HK_QUADREAL_MAX>(), 100, pointOnSurface, surfaceNormal, signedDistance, numIterationsUsed);
}

/// Approximately projects a point onto a convex hull spanned by the given plane equations.
/// NOTE: Point and planes must all be defined in the same space.
HK_FORCE_INLINE bool HK_CALL hkcdDistancePointConvex::hkcdPointConvexApprox(	hkVector4Parameter point,
												const hkVector4* HK_RESTRICT planes, int numPlanes,
												hkVector4& pointOnSurface, hkVector4& surfaceNormal, hkSimdReal& signedDistance)
{
	int numIterationsUsed;
	return _hkcdPointConvex(point, planes, numPlanes, hkSimdReal::getConstant<HK_QUADREAL_MAX>(), 1, pointOnSurface, surfaceNormal, signedDistance, numIterationsUsed);
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
