/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKCD_PLANAR_GEOMETRY_PREDICATES_H
#define HKCD_PLANAR_GEOMETRY_PREDICATES_H

#include <Common/Base/Math/Vector/hkVector4Util.h>
#include <Geometry/Collide/DataStructures/PlanarGeometry/Primitives/hkcdPlanarGeometryPrimitives.h>

/// Exact geometric predicates
class hkcdPlanarGeometryPredicates
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_GEOMETRY, hkcdPlanarGeometryPredicates);

		// Types
		typedef hkcdPlanarGeometryPrimitives::Plane				Plane;
		typedef hkcdPlanarGeometryPrimitives::ApproxPlaneEqn	ApproxPlaneEqn;
		typedef const ApproxPlaneEqn&							ApproxPlaneEqnParam;
		typedef const Plane&									PlaneParam;

	public:

		/// Orientation types
		enum Orientation
		{
			ON_PLANE			= 0,
			IN_FRONT_OF			= 1,
			BEHIND				= 2,
			INTERSECT			= 3,
			CACHEABLE			= 0x10,
			ORIENTATION_MASK	= 0x0F,
		};

		/// Coplanarity types
		enum Coplanarity
		{
			NOT_COPLANAR	= 0,
			COINCIDENT		= 1,
			OPPOSITE		= 2,
		};

		/// Winding types
		enum Winding
		{
			WINDING_CW			= -1,	///< The winding is clockwise, Dot[planeNormal, Cross[AB, AC]] is negative
			WINDING_COLLINEAR	= 0,	///< No winding, the points are collinear!
			WINDING_CCW			= 1,	///< The winding is counter-clockwise, Dot[planeNormal, Cross[AB, AC]] is positive
			WINDING_UNKNOWN		= 3,	///< Special code returned by the floating-point function to trigger the execution of the fixed-precision predicate
		};

	public:

		/// Returns true if the given planes are coplanar (i.e. coincident)
		static HK_FORCE_INLINE Coplanarity HK_CALL coplanar(PlaneParam planeA, PlaneParam planeB);

		/// Returns true if the vertex defined by three planes (ptPlaneA, ptPlaneB, ptPlaneC) is coplanar to all the given test planes
		static hkBool32 HK_CALL coplanar(PlaneParam ptPlaneA, PlaneParam ptPlaneB, PlaneParam ptPlaneC, const Plane* HK_RESTRICT testPlanes, int numTestPlanes);

		/// Tests for same orientation. Should be preceded by a coplanarity test
		static HK_FORCE_INLINE int HK_CALL sameOrientation(PlaneParam planeA, PlaneParam planeB);

		/// Computes the orientation of the point (ptPlaneA, ptPlaneB, ptPlaneC) with respect to the planeD
		static HK_FORCE_INLINE Orientation HK_CALL approximateOrientation(PlaneParam ptPlaneA, PlaneParam ptPlaneB, PlaneParam ptPlaneC, PlaneParam planeD);

		/// Computes the orientation of the point (ptPlaneA, ptPlaneB, ptPlaneC) with respect to the planeD
		static Orientation HK_CALL orientation(PlaneParam ptPlaneA, PlaneParam ptPlaneB, PlaneParam ptPlaneC, PlaneParam planeD);

		/// Computes the orientation of the point v with respect to the plane p
		static HK_FORCE_INLINE Orientation HK_CALL orientation(hkIntVectorParameter v, PlaneParam p);

		/// Returns true if the edge determined by the intersection of planes A and B is contained on plane C
		static hkBool32 HK_CALL edgeOnPlane(PlaneParam edgePlaneA, PlaneParam edgePlaneB, PlaneParam planeC);

		/// Computes the vector of determinants [PX, PY, PZ, PW], where:
		///				| ax ay az |		    | aw ay az |			| ax aw az |			| ax ay aw |
		///		PW =	| bx by bz |,	PX = -  | bw by bz |,	PY = -  | bx bw bz |,	PZ = -  | bx by bw |
		///				| cx cy cz |			| cw cy cz |		    | cx cw cz |			| cx cy cw |
		static HK_FORCE_INLINE void HK_CALL computeIntersectionDeterminants(ApproxPlaneEqnParam planeEqnA, ApproxPlaneEqnParam planeEqnB, ApproxPlaneEqnParam planeEqnC, ApproxPlaneEqn& determinantsOut);
		static void HK_CALL computeIntersectionDeterminants(const Plane (&planes)[3], hkSimdInt<256>* detX, hkSimdInt<256>* detY, hkSimdInt<256>* detZ, hkSimdInt<256>* detW);

		// Approximates the intersection (i.e. in fixed coordinates) of the 3 given planes
		static HK_FORCE_INLINE void HK_CALL approximateIntersection(const Plane (&planes)[3], hkIntVector& intersectionOut);

		/// Computes an approximate direction for the edge resulting from the intersection of the two given planes
		static void HK_CALL approximateEdgeDirection(PlaneParam planeA, PlaneParam planeB, hkIntVector& edgeDirectionOut);

		/// Computes the winding of the 3 given vertices w.r.t. the given triangle normal.
		static HK_FORCE_INLINE Winding HK_CALL triangleWinding(const Plane (&planesA)[3], const Plane (&planesB)[3], const Plane (&planesC)[3], PlaneParam supportPlane);

	protected:

		// Computes the Det3. Returns true if the result is trustworthy
		static HK_FORCE_INLINE hkBool32 computeApproxDet3(const Plane& planeA, const Plane& planeB, const Plane& planeC, hkVector4dComparison& det3LessZero, hkVector4dComparison& det3EqualZero);
		static HK_FORCE_INLINE void computeExactDet3(const Plane& planeA, const Plane& planeB, const Plane& planeC, hkVector4dComparison& det3LessZero, hkVector4dComparison& det3EqualZero);

		/// Computes the Det4. Returns true if the result is trustworthy
		static HK_FORCE_INLINE hkBool32 computeApproxDet4(const Plane& planeA, const Plane& planeB, const Plane& planeC, const Plane& planeD, hkVector4dComparison& det4LessZero, hkVector4dComparison& det4EqualZero);
		static HK_FORCE_INLINE void computeExactDet4(const Plane& planeA, const Plane& planeB, const Plane& planeC, const Plane& planeD, hkVector4dComparison& det4LessZero, hkVector4dComparison& det4EqualZero);

		static HK_FORCE_INLINE int HK_CALL mulSigns(hkVector4dComparisonParameter negA, hkVector4dComparisonParameter zeroA, hkVector4dComparisonParameter negB, hkVector4dComparisonParameter zeroB);

		/// Estimates the winding of the 3 given vertices w.r.t. the given triangle normal (floating-point).
		static Winding HK_CALL estimateTriangleWinding(const Plane (&planesA)[3], const Plane (&planesB)[3], const Plane (&planesC)[3], const Plane& supportPlane, int axisX, int axisY, int axisZ);

		/// Computes the triangle winding using fixed precision
		static Winding HK_CALL computeExactTriangleWinding(const Plane (&planesA)[3], const Plane (&planesB)[3], const Plane (&planesC)[3], const Plane& supportPlane, int axisX, int axisY, int axisZ);

	public:

		// Statistics
#ifdef HK_DEBUG
		static hkUint32 m_numApproxCalls;	///< Number of times when a call was resolved using floating point arithmetic
		static hkUint32 m_numExactCalls;	///< Number of times when a call was resolved using exact arithmetic

		static hkUint32 m_numApproxDet3;
		static hkUint32 m_numExactDet3;

		static hkUint32 m_numApproxDet4;
		static hkUint32 m_numExactDet4;
#endif
};

#include <Geometry/Collide/DataStructures/PlanarGeometry/Predicates/hkcdPlanarGeometryPredicates.inl>

#endif	//	HKCD_PLANAR_GEOMETRY_PREDICATES_H

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
