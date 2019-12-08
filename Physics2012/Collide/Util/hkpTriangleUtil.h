/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_COLLIDE2_TRIANGLEUTIL_H
#define HK_COLLIDE2_TRIANGLEUTIL_H

#include <Geometry/Collide/Algorithms/Triangle/hkcdTriangleUtil.h>
#include <Geometry/Internal/Algorithms/Intersect/hkcdIntersectPointTriangle.h>

extern hkReal hkDefaultTriangleDegeneracyTolerance;

/// Triangle utilities (ray intersection, normal calculation, point-in-triangle tests etc.)
class hkpTriangleUtil
{
	public:
		

		// Utilities...

			/// Method to calculate the (non-normalized) triangle normal.
			/// Given the vertices, set normal to be the non-unit normal.
			/// \param normal (Output) The normal of the triangle
			/// \param a First vertex.
			/// \param b Second vertex.
			/// \param c Third vertex.
		static inline void HK_CALL calcNormal( hkVector4& normal, hkVector4Parameter a, hkVector4Parameter b, hkVector4Parameter c );


			/// Method to calculate the triangle centroid.
			/// Given the vertices list, set the centroid to be the centroid of the three vertices.
			/// \param centroid (output) The centroid of the triangle
			/// \param a First vertex.
			/// \param b Second vertex.
			/// \param c Third vertex.
		static inline void HK_CALL calcCentroid( hkVector4& centroid, hkVector4Parameter a, hkVector4Parameter b, hkVector4Parameter c );


			/// Returns true if the point is in front of the Triangle.
			/// Given the plane in which the triangle is embedded, the point is in front if (and only if)
			/// the point is in the half space (defined by the plane) that the normal points into.
			/// \param point The point to examine
			/// \param a First vertex.
			/// \param b Second vertex.
			/// \param c Third vertex.
		static inline bool HK_CALL inFront( hkVector4Parameter point, hkVector4Parameter a, hkVector4Parameter b, hkVector4Parameter c );


			/// Return true if the point is contained within the Triangle.
			/// Assumes that the point is on the plane containing the Triangle.
			/// \param pt The point to examine
			/// \param a First vertex.
			/// \param b Second vertex.
			/// \param c Third vertex.
		static inline bool HK_CALL containsPoint( hkVector4Parameter pt, hkVector4Parameter a, hkVector4Parameter b, hkVector4Parameter c );

			/// special version of dot3 with no fused multiply additions
		static inline hkReal HK_CALL dot3fullAcc(hkVector4Parameter a, hkVector4Parameter b);

			/// Returns true if the triangle is degenerate.
			/// Degenerate is assumed to be:
			///     - it has very small area (cross product of edges all squared less than given tolerance).
			///     - it has a aspect ratio which will cause collision detection algorithms to fail.
			///
			/// \param a               First vertex.
			/// \param b               Second vertex.
			/// \param c               Third vertex.
			/// \param tolerance	   Minimal acceptable area and squared edge length
		static inline bool HK_CALL isDegenerate(hkVector4Parameter a, hkVector4Parameter b, hkVector4Parameter c , hkReal tolerance = hkDefaultTriangleDegeneracyTolerance);

			/// Intersects a triangle with a plane
			/// \param a               First vertex.
			/// \param b               Second vertex.
			/// \param c               Third vertex.
			/// \param plane		   Plane equation.
			/// \param edgesOut		   Resulting intersection edges. Includes degenerate edges where both start and end points coincide
			/// \param tolerance	   Intersection tolerance.
		static inline void HK_CALL calcPlaneIntersection(hkVector4Parameter a, hkVector4Parameter b, hkVector4Parameter c, hkVector4Parameter plane, hkArray<hkVector4>& edgesOut, hkReal tolerance);

	protected:

		hkpTriangleUtil();

};

#include <Physics2012/Collide/Util/hkpTriangleUtil.inl>

#endif // HK_COLLIDE2_TRIANGLEUTIL_H

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
