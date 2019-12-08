/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKCD_PLANAR_GEOMETRY_BOOLEAN_UTIL_H
#define HKCD_PLANAR_GEOMETRY_BOOLEAN_UTIL_H

#include <Geometry/Collide/DataStructures/PlanarGeometry/hkcdSolidPlanarGeometry.h>

/// Utility for computing boolean operations between planar geometries
class hkcdPlanarGeometryBooleanUtil
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_DESTRUCTION, hkcdPlanarGeometryBooleanUtil);

		// Types
		typedef hkcdPlanarGeometry::PlaneId						PlaneId;
		typedef hkcdPlanarGeometry::PolygonId					PolygonId;
		typedef hkcdPlanarGeometry::DefaultOrientationCache		OrientationCache;

	public:

		/// Supported operations
		enum Operation
		{
			OP_UNION			= 0,	///< Computes the union of A and B
			OP_INTERSECTION		= 1,	///< Computes the intersection of A and B
			OP_DIFFERENCE		= 2,	///< Computes the difference A - B
		};

		/// Boolean state, to be maintained between operations
		struct BooleanState
		{
			BooleanState(OrientationCache& cache)
			:	m_cache(cache)
			{}

			OrientationCache& m_cache;	///< The orientation cache
		};

	public:

		/// Initialize an in-place boolean operation.
		static BooleanState* HK_CALL setOperatorsForInPlaceMerge(OrientationCache& orientationCache, hkcdSolidPlanarGeometry* inputOutputTree, hkcdPlanarGeometry& commonGeom);

		/// Merge in-place. Use this instead of "compute" whenever you need to stack several boolean operation on the same BSP tree.
		static void HK_CALL mergeInPlace(BooleanState* bState, const hkcdSolidPlanarGeometry* treeToMergeWith, Operation op, bool collapse = true);

		/// Finalize th in-place merge.
		static hkcdSolidPlanarGeometry* HK_CALL finalizeInPlaceMerge(BooleanState* bState, bool collapse = false);

		/// Computes A op B. Will assert if called with OP_DIFFERENCE, as that would require flipping the solidB.
		static void HK_CALL compute(const hkcdSolidPlanarGeometry* solidA, Operation op, const hkcdSolidPlanarGeometry* solidB,
									OrientationCache& orientationCache,
									hkRefPtr<const hkcdSolidPlanarGeometry>* resultOut, hkRefPtr<const hkcdSolidPlanarGeometry>* dualResultOut, 
									bool manifoldCells);

		/// Computes the meshes resulting from A op B.
		static void HK_CALL buildMeshes(hkcdSolidPlanarGeometry* solidA, const hkArray<PolygonId>& originalPolygonIdsA, bool closedManifoldA,
										Operation op,
										hkcdSolidPlanarGeometry* solidB, const hkArray<PolygonId>& originalPolygonIdsB, bool closedManifoldB, const hkArray<PolygonId>& polygonIdsNonB,
										OrientationCache& orientationCache,
										hkcdSolidPlanarGeometry* resultAB, hkcdSolidPlanarGeometry* resultAnegB);

	protected:

		/// Replaces the geometry of the given solid with a new one containing just the polygons in the given arrays. The coplanar polygons are pre-intersected so as the result
		/// does not contain overlapping polygons
		static void HK_CALL buildMesh(	hkcdPlanarGeometry& workingGeom,
										const hkArray<PolygonId>& polygonIdsA, const hkArray<PolygonId>& polygonIdsB,
										hkcdSolidPlanarGeometry* result);
};

#endif	//	HKCD_PLANAR_GEOMETRY_BOOLEAN_UTIL_H

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
