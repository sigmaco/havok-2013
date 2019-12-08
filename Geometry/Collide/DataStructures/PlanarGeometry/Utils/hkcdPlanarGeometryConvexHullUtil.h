/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKCD_PLANAR_GEOMETRY_CONVEX_HULL_UTIL_H
#define HKCD_PLANAR_GEOMETRY_CONVEX_HULL_UTIL_H

#include <Geometry/Collide/DataStructures/PlanarGeometry/hkcdPlanarGeometry.h>

/// Utility to compute the convex hull of a set of points given in fixed precision
class hkcdPlanarGeometryConvexHullUtil
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_GEOMETRY, hkcdPlanarGeometryConvexHullUtil);

	public:

		/// Builds the convex hull from the given set of points. Returns the number of hull dimensions or -1 if it failed to compute the hull
		static int HK_CALL build(	const hkAabb& coordinateConversionAabb, const hkVector4* verticesIn, const int numVerticesIn, 
									hkRefPtr<hkcdPlanarGeometry>& convexHullOut, hkcdPlanarEntityDebugger* debugger = HK_NULL);
};

#endif	// HKCD_PLANAR_GEOMETRY_CONVEX_HULL_UTIL_H

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
