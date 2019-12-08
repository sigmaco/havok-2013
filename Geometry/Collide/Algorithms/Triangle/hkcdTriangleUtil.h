/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#ifndef HKCD_TRIANGLE_UTIL_H
#define HKCD_TRIANGLE_UTIL_H


	/// Triangle utility functions
namespace hkcdTriangleUtil
{
		/// Method to calculate the normalized triangle normal.
		/// Given the vertices, set normal to be the normal.
		/// \param normal (Output) The normal of the triangle
		/// \param a First vertex.
		/// \param b Second vertex.
		/// \param c Third vertex.
	HK_FORCE_INLINE void HK_CALL calcUnitNormal(hkVector4Parameter a, hkVector4Parameter b, hkVector4Parameter c, hkVector4& normal);

		/// Method to calculate the un-normalized triangle normal.
		/// Given the vertices, set normal to be the normal.
		/// \param normal (Output) The normal of the triangle
		/// \param a First vertex.
		/// \param b Second vertex.
		/// \param c Third vertex.
	HK_FORCE_INLINE void HK_CALL calcNonUnitNormal(hkVector4Parameter a, hkVector4Parameter b, hkVector4Parameter c, hkVector4& normal);

		/// Computes the normalized plane equation from the three given vertices
	HK_FORCE_INLINE void HK_CALL calcUnitPlaneEquation(hkVector4Parameter a, hkVector4Parameter b, hkVector4Parameter c, hkVector4& planeOut);

		/// Computes the unnormalized plane equation from the three given vertices
	HK_FORCE_INLINE void HK_CALL calcNonUnitPlaneEquation(hkVector4Parameter a, hkVector4Parameter b, hkVector4Parameter c, hkVector4& planeOut);

		/// Computes twice the area of the given triangle
	HK_FORCE_INLINE hkSimdReal HK_CALL calcDoubleArea(hkVector4Parameter a, hkVector4Parameter b, hkVector4Parameter c);

		/// Method to calculate the triangle centroid.
		/// Given the vertices list, set the centroid to be the centroid of the three vertices.
		/// \param centroid (output) The centroid of the triangle
		/// \param a First vertex.
		/// \param b Second vertex.
		/// \param c Third vertex.
	HK_FORCE_INLINE void HK_CALL calcCentroid(hkVector4Parameter a, hkVector4Parameter b, hkVector4Parameter c, hkVector4& centroid);

		/// Returns true if the point is in front of the Triangle.
		/// Given the plane in which the triangle is embedded, the point is in front if (and only if)
		/// the point is in the half space (defined by the plane) that the normal points into.
		/// \param point The point to examine
		/// \param a First vertex.
		/// \param b Second vertex.
		/// \param c Third vertex.
	HK_FORCE_INLINE hkBool32 HK_CALL isPointInFront(hkVector4Parameter point, hkVector4Parameter a, hkVector4Parameter b, hkVector4Parameter c);

		/// Returns nonzero if the triangle is degenerate.
		/// Degenerate is assumed to be:
		///     - it has very small area (cross product of edges all squared less than given tolerance).
		///     - it has a aspect ratio which will cause collision detection algorithms to fail.
		///
		/// \param a               First vertex.
		/// \param b               Second vertex.
		/// \param c               Third vertex.
		/// \param tolerance	   Minimal acceptable area and squared edge length
	hkBool32 HK_CALL isDegenerate(hkVector4Parameter a, hkVector4Parameter b, hkVector4Parameter c, hkSimdRealParameter tolerance);

		/// Calculate the barycentric coordinates of a point projected onto a triangle.
		/// Note: result 0 and 2 are always sign correct, result 1 is calculated as 1.0f - p0 - p2, this function is not epsilon safe.
	void HK_CALL calcBarycentricCoordinates(hkVector4Parameter pos, hkVector4Parameter t0, hkVector4Parameter t1, hkVector4Parameter t2, hkVector4& result);

		/// Same as calcBarycentricCoordinates but assumes non degenerate triangle.
	HK_FORCE_INLINE void HK_CALL calcBarycentricCoordinatesNonDegenerate(hkVector4Parameter pos, hkVector4Parameter t0, hkVector4Parameter t1, hkVector4Parameter t2, hkVector4& result);

		/// Previous version for computing barycentric coordinates, now deprecated.
	void HK_CALL calcBarycentricCoordinatesDeprecated(hkVector4Parameter pos, hkVector4Parameter t0, hkVector4Parameter t1, hkVector4Parameter t2, hkVector4& result);

		/// Clip a triangle with a plane. Returns the number of edges in the intersection (i.e. either 0, 1, or 3, including degenerate edges where both start
		/// and end points coincide). Assumes that edgesOut is a pre-allocated buffer big enough to fit 6 vertices.
		/// \param a               First vertex.
		/// \param b               Second vertex.
		/// \param c               Third vertex.
		/// \param plane		   Plane equation.
		/// \param edgesOut		   Resulting intersection edges. Includes degenerate edges where both start and end points coincide
		/// \param tolerance	   Intersection tolerance.
	int HK_CALL clipWithPlane(hkVector4Parameter a, hkVector4Parameter b, hkVector4Parameter c, hkVector4Parameter plane, hkSimdRealParameter tolerance, hkVector4 edgesOut[6]);

		/// Checks if a quad is convex and flat within tolerance
	hkBool32 HK_CALL checkForFlatConvexQuad( hkVector4Parameter a, hkVector4Parameter b, hkVector4Parameter c, hkVector4Parameter d, hkReal tolerance);

		/// Returns the sin(angle) of two triangles sharing the edge (edgePoint1-edgePoint0)
	HK_FORCE_INLINE hkSimdReal calcConvexity( hkVector4Parameter normalA, hkVector4Parameter normalB, hkVector4Parameter edgePoint0, hkVector4Parameter edgePoint1 );
}

#include <Geometry/Collide/Algorithms/Triangle/hkcdTriangleUtil.inl>

#endif // HKCD_TRIANGLE_UTIL_H

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
