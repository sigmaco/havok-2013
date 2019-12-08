/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKCD_PLANAR_GEOMETRY_POLYGON_COLLECTION_H
#define HKCD_PLANAR_GEOMETRY_POLYGON_COLLECTION_H

#include <Geometry/Collide/DataStructures/PlanarGeometry/Primitives/hkcdPlanarGeometryPrimitives.h>
#include <Geometry/Collide/DataStructures/PlanarGeometry/Memory/hkcdPlanarGeometryPrimitivesCollection.h>

/// A collection of polygons.
class hkcdPlanarGeometryPolygonCollection : public hkcdPlanarGeometryPrimitives::Collection<hkcdPlanarGeometryPrimitives::FLIPPED_PLANE_BIT>
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_GEOMETRY, hkcdPlanarGeometryPolygonCollection);

		// Types
		HK_DECLARE_HANDLE(PolygonId, hkUint32, INVALID_BLOCK_ADDR);
		typedef hkcdPlanarGeometryPrimitives::PlaneId PlaneId;

	public:

		/// A polygon, defined by a support plane and a CCW set of bounding planes along its edges.
		struct Polygon
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_GEOMETRY, hkcdPlanarGeometryPolygonCollection::Polygon);
			friend class hkcdPlanarGeometryPolygonCollection;	

			enum
			{
				MATERIAL_ID_OFFSET		= 0,
				POSITIVE_CELL_ID_OFFSET	= 1,
				NEGATIVE_CELL_ID_OFFSET	= 2,
				SUPPORT_PLANE_ID_OFFSET	= 3,
				BOUNDARY_PLANES_OFFSET	= 4,
			};

			public:

				/// Returns the material Id
				HK_FORCE_INLINE hkUint32 getMaterialId() const;
				HK_FORCE_INLINE void setMaterialId(int mtlId);

				/// Returns the support plane Id
				HK_FORCE_INLINE PlaneId getSupportPlaneId() const;
				HK_FORCE_INLINE void setSupportPlaneId(PlaneId pid);

				/// Returns a read-only pointer to the boundary planes
				HK_FORCE_INLINE const PlaneId* getBoundaryPlaneIds() const;

				/// Gets / sets the i-th boundary plane Id
				HK_FORCE_INLINE PlaneId getBoundaryPlaneId(int i) const;
				HK_FORCE_INLINE void setBoundaryPlaneId(int i, PlaneId pid);

				/// Gets / sets the cell ids
				HK_FORCE_INLINE hkUint32 getNegCellId() const;
				HK_FORCE_INLINE void setNegCellId(hkUint32 cellId);
				HK_FORCE_INLINE hkUint32 getPosCellId() const;
				HK_FORCE_INLINE void setPosCellId(hkUint32 cellId);

			protected:

				hkUint32 m_materialId;
				hkUint32 m_posCellId;
				hkUint32 m_negCellId;
				hkUint32 m_supportId;
		};

	public:

		/// Constructor
		hkcdPlanarGeometryPolygonCollection();

		/// Copy constructor
		hkcdPlanarGeometryPolygonCollection(const hkcdPlanarGeometryPolygonCollection& other);

		/// Compacts the storage
		void compactStorage();

	public:

		/// Retrieves the polygon at the given Id.
		HK_FORCE_INLINE const Polygon& getPolygon(PolygonId polyId) const;
		HK_FORCE_INLINE Polygon& accessPolygon(PolygonId polyId);

		/// Computes the number of boundary planes
		HK_FORCE_INLINE int getNumBoundaryPlanes(PolygonId polyId) const;

		/// Reverses the boundary winding
		HK_FORCE_INLINE void flipWinding(PolygonId polyId);

		// Allocates a polygon having the given number of boundary planes
		HK_FORCE_INLINE PolygonId alloc(PlaneId supportPlaneId, hkUint32 materialId, int numBoundaryPlanes);

		/// Frees the given polygon
		HK_FORCE_INLINE void free(PolygonId polyId);

		/// Returns the first valid polygon Id
		HK_FORCE_INLINE PolygonId getFirstPolygonId() const;

		/// Returns the last valid polygon Id
		HK_FORCE_INLINE PolygonId getLastPolygonId() const;

		/// Returns the next valid polygon Id
		HK_FORCE_INLINE PolygonId getNextPolygonId(PolygonId polyId) const;

		/// Returns the previous valid polygon Id
		HK_FORCE_INLINE PolygonId getPrevPolygonId(PolygonId polyId) const;

		/// Returns the number of valid polygon Ids stored
		HK_FORCE_INLINE int getNumPolygons() const;
};

#include <Geometry/Collide/DataStructures/PlanarGeometry/Memory/hkcdPlanarGeometryPolygonCollection.inl>

#endif	//	HKCD_PLANAR_GEOMETRY_POLYGON_COLLECTION_H

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
