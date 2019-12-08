/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKCD_VORONOI_DIAGRAM_UTIL_H
#define HKCD_VORONOI_DIAGRAM_UTIL_H

#include <Geometry/Collide/DataStructures/PlanarGeometry/hkcdSolidPlanarGeometry.h>
#include <Geometry/Collide/DataStructures/PlanarGeometry/hkcdConvexCellsTree.h>

/// Utility that builds a Voronoi diagram out of a set of points
class hkcdVoronoiDiagramUtil
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_GEOMETRY, hkcdVoronoiDiagramUtil);

		// Types
		typedef hkcdConvexCellsTree::Plane					Plane;
		typedef hkcdConvexCellsTree::PlaneId				PlaneId;
		typedef hkcdConvexCellsTree::Cell					Cell;
		typedef hkcdConvexCellsTree::CellId					CellId;
		typedef hkcdSolidPlanarGeometry::Node				Node;
		typedef hkcdSolidPlanarGeometry::NodeId				NodeId;
		typedef hkcdPlanarGeometry::Polygon					Polygon;
		typedef hkcdPlanarGeometry::PolygonId				PolygonId;
		typedef hkcdPlanarGeometry::DefaultOrientationCache	OrientationCache;

	public:

		/// Generic interface for accessing Voronoi sites and the planes between them. The interface is
		/// used as opposed to compute the planes internally, so that callers can access the exact same equations as the util
		struct SitesProvider
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_GEOMETRY, hkcdVoronoiDiagramUtil::SitesProvider);

			/// Destructor
			virtual ~SitesProvider() {}

			/// Returns the number of Voronoi sites
			virtual int getNumSites() const = 0;

			/// Returns the position of the I-th Voronoi site
			virtual void getSitePosition(int i, hkVector4& sitePositionOut) const = 0;

			/// Constructs a plane between the sites A and B. The plane should point from A to B.
			virtual void computePlane(int voronoiSiteA, int voronoiSiteB, Plane& planeOut) = 0;

			/// Adds a plane between the sites A and B. The plane points from A to B.
			virtual void addPlane(int voronoiSiteA, int voronoiSiteB, const Plane& newPlaneIn) = 0;
		};

		/// Builds the diagram from the given set of points. Returns a set of uniquely determined sepparating planes,
		/// a set of Voronoi cells that match one-to-one with the given input points, and their boundary plane Ids.
		/// The boundary plane of a cell is considered to be oriented from m_pointIdxA to m_pointIdxB iif the plane index is positive.
		/// The plane has opposite orientation otherwise.
		static void HK_CALL build(	const hkAabb& coordinateConversionAabb, SitesProvider* sitesProvider,
									hkRefPtr<hkcdConvexCellsTree>& convexTreeOut, hkArray<CellId>& cellIdsOut,
									hkcdPlanarEntityDebugger* debugger = HK_NULL);

		/// Builds the diagram from the given set of points.Returns the result as a BSP tree of planar cuts, with the convex cell Ids stored in the
		/// terminal nodes
		static void HK_CALL buildPlanarCuts(hkcdConvexCellsTree* convexTreeInOut, const hkArray<CellId>& cellIdsIn, hkRefPtr<hkcdSolidPlanarGeometry>& cutsOut);
};

#endif	//	HKCD_VORONOI_DIAGRAM_UTIL_H

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
