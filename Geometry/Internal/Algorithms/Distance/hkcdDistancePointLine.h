/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#ifndef	HKCD_DISTANCES_POINT_LINE
#define HKCD_DISTANCES_POINT_LINE

#include <Common/Base/Math/Vector/hkFourTransposedPoints.h>

	/// Returns the squared distance between a point and an infinite line.
	/// The line is specified as two points on it.
template <typename Vector, typename Scalar>
HK_FORCE_INLINE	static Scalar HK_CALL hkcdPointLineDistanceSquared( const Vector& point, const Vector& lineA, const Vector& lineB, Vector* HK_RESTRICT projectionOut = HK_NULL );

HK_FORCE_INLINE	static hkSimdReal HK_CALL hkcdPointLineDistanceSquared(hkVector4Parameter point, hkVector4Parameter lineA, hkVector4Parameter lineB, hkVector4* HK_RESTRICT projectionOut = HK_NULL );

	/// Returns the squared distance between a point and a line.
	/// If \a projectionOut is not null, it will be set to the projected point position with the fraction stored in the W component.
	/// Note: The line is allowed to be a point.
HK_FORCE_INLINE	static hkSimdReal HK_CALL hkcdPointSegmentDistanceSquared(hkVector4Parameter point, hkVector4Parameter lineStart, hkVector4Parameter lineEnd, hkVector4* HK_RESTRICT projectionOut = HK_NULL);

	/// Bundle version
HK_FORCE_INLINE	static hkVector4 HK_CALL hkcdPointSegmentDistanceSquared(const hkFourTransposedPoints& points, hkVector4Parameter lineStart, hkVector4Parameter lineEnd, hkFourTransposedPoints* HK_RESTRICT projectionOut = HK_NULL);

	/// Returns the squared distance between M points and M lines.
	/// If \a projectionOut is not null, it will be set to the projected point positions with the fractions stored in each W component.
	/// Note: The lines are allowed to be points.
template<int M>
HK_FORCE_INLINE	static hkMxReal<M> HK_CALL hkcdPointSegmentDistanceSquared(hkMxVectorParameter point, hkMxVectorParameter lineStart, hkMxVectorParameter lineEnd, hkMxVector<M>* HK_RESTRICT projectionOut = HK_NULL);

	/// Returns the distance between a point and a capsule (or a segment if capsuleRadius is zero).
	/// \a closestPointAndFractionOut will be set to the closest point on capsule with the segment fraction stored in the W component.
	/// You also get the normal from the capsule in \a normal.
HK_FORCE_INLINE static hkSimdReal HK_CALL hkcdPointCapsuleClosestPoint( hkVector4Parameter point, hkVector4Parameter rayStart, hkVector4Parameter rayEnd,
														hkSimdRealParameter capsuleRadius, hkVector4* HK_RESTRICT closestPointAndFractionOut, hkVector4* HK_RESTRICT normalOut );

#include <Geometry/Internal/Algorithms/Distance/hkcdDistancePointLine.inl>

#endif // HKCD_DISTANCES_POINT_LINE

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
