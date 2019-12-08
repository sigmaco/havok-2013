/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#ifndef	HKCD_DISTANCES_POINT_TRIANGLE
#define HKCD_DISTANCES_POINT_TRIANGLE

#include <Geometry/Collide/Algorithms/Triangle/hkcdTriangleUtil.h>
#include <Geometry/Internal/Algorithms/Intersect/hkcdIntersectPointTriangle.h>

/// Identify the Voronoi region of a point projected to a triangle.
struct hkcdTriangleVoronoi
{
	enum Region
	{
		INVALID		=	-1,
		VERTEX_0	=	0,
		EDGE_0		=	1,
		VERTEX_1	=	2,
		EDGE_1		=	3,
		VERTEX_2	=	4,
		EDGE_2		=	5,
		INSIDE		=	6
	};

	enum Feature
	{
		VERTEX		=	0,
		EDGE		=	1,
		FACE		=	2
	};

	static HK_FORCE_INLINE hkBool32 isEdge(Region r) { return (hkBool32) (r&1); }
	static HK_FORCE_INLINE hkBool32	isVertex(Region r) { return r < 6 ? (hkBool32)((r+1)&1) : 0; }
	static HK_FORCE_INLINE Feature	getFeature(Region r) { return r == 6 ? FACE : (r&1 ? EDGE : VERTEX); }
};

	/// Computes and returns the squared distance from vP to the triangle (vA, vB, vC).
	/// The normal and optionally the barycentric coordinates of the closest point on the triangle
	/// are also provided on output.
HK_FORCE_INLINE	hkSimdReal HK_CALL hkcdPointTriangleDistanceSquared(hkVector4Parameter vP,
																	hkVector4Parameter vA, hkVector4Parameter vB, hkVector4Parameter vC,
																	hkVector4* HK_RESTRICT normalOut, hkVector4* HK_RESTRICT baryOut);

		/// Project a point on a triangle, returns true if the point is projected inside the triangle.
HK_FORCE_INLINE hkBool32 HK_CALL hkcdPointTriangleProject(	hkVector4Parameter vP, 
																				hkVector4Parameter vA, hkVector4Parameter vB, hkVector4Parameter vC,
																				hkVector4* HK_RESTRICT projectionOut,
																				hkVector4* HK_RESTRICT normalOut = HK_NULL);


/// Project a point on a triangle, returns the voronoi region that the projected point is in.
HK_FORCE_INLINE hkcdTriangleVoronoi::Region HK_CALL hkcdPointTriangleProjectWithVoronoi(	hkVector4Parameter vP, 
																			 hkVector4Parameter vA, hkVector4Parameter vB, hkVector4Parameter vC,
																			 hkVector4* HK_RESTRICT projectionOut,
																			 hkVector4* HK_RESTRICT normalOut = HK_NULL);

#include <Geometry/Internal/Algorithms/Distance/hkcdDistancePointTriangle.inl>

#endif	//	HKCD_DISTANCES_POINT_TRIANGLE

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
