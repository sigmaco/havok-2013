/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKCD_CONVEX_CELLS_COLLECTION_H
#define HKCD_CONVEX_CELLS_COLLECTION_H

#include <Geometry/Collide/DataStructures/PlanarGeometry/Primitives/hkcdPlanarGeometryPrimitives.h>
#include <Geometry/Collide/DataStructures/PlanarGeometry/Memory/hkcdPlanarGeometryPrimitivesCollection.h>
#include <Geometry/Collide/DataStructures/PlanarGeometry/Memory/hkcdPlanarGeometryPolygonCollection.h>

/// A collection of convex cells.
class hkcdConvexCellsCollection : public hkcdPlanarGeometryPrimitives::Collection<hkcdPlanarGeometryPrimitives::FLIPPED_PLANE_BIT>
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_GEOMETRY, hkcdConvexCellsCollection);

		// Types
		HK_DECLARE_HANDLE(CellId, hkUint32, INVALID_BLOCK_ADDR);
		typedef hkcdPlanarGeometryPrimitives::PlaneId			PlaneId;
		typedef hkcdPlanarGeometryPolygonCollection::PolygonId PolygonId;

	public:

		/// Cell labels
		enum Labels
		{
			CELL_UNKNOWN		= 0,	///< Unknown / unlabeled
			CELL_EMPTY			= 1,	///< Empty space
			CELL_SOLID			= 2,	///< Solid space
		};

		/// Constants
		enum
		{
			CELL_EMPTY_BIT		= 0,
			CELL_SOLID_BIT		= 1,
			CELL_LEAF_BIT		= 2,
			CELL_VISITED_BIT	= 3,
			CELL_EMPTY_MASK		= (1 << CELL_EMPTY_BIT),
			CELL_SOLID_MASK		= (1 << CELL_SOLID_BIT),
			CELL_LEAF_MASK		= (1 << CELL_LEAF_BIT),
			CELL_VISITED_MASK	= (1 << CELL_VISITED_BIT),
		};

	public:

		/// A convex cell, as a collection of 2D convex polygons
		struct Cell
		{
			friend class hkcdConvexCellsCollection;

			enum
			{
				USER_DATA_OFFSET		= 0,
				FLAGS_OFFSET			= 1,
				BOUNDARY_POLY_OFFSET	= 2,
			};
		public:

			/// Returns true if the cell is a leaf
			HK_FORCE_INLINE bool isLeaf() const;

			/// Gets / sets the i-th boundary polygon Id
			HK_FORCE_INLINE PolygonId getBoundaryPolygonId(int i) const;
			HK_FORCE_INLINE void setBoundaryPolygonId(int i, PolygonId pid);

			/// Gets / Sets the cell label
			HK_FORCE_INLINE Labels getLabel() const;
			HK_FORCE_INLINE void setLabel(Labels l);

			/// Returns true if the cell is empty / solid / unknown
			HK_FORCE_INLINE int isEmpty() const;
			HK_FORCE_INLINE int isSolid() const;
			HK_FORCE_INLINE int isUnknown() const;
			HK_FORCE_INLINE int isVisited() const;

			/// Sets the cell as empty / solid
			HK_FORCE_INLINE void setEmpty();
			HK_FORCE_INLINE void setSolid();
			HK_FORCE_INLINE void setVisited(bool visited);
			HK_FORCE_INLINE void setLeaf(bool leaf);

			/// Gets / Sets user data
			HK_FORCE_INLINE hkUint32 getUserData() const;
			HK_FORCE_INLINE void setUserData(hkUint32 data);


		protected:

			hkUint32 m_userData;
			hkUint32 m_flags;			
		};

	public:

		/// Constructor
		hkcdConvexCellsCollection()
		{
			clear();
		}

		/// Retrieves the cell at the given Id.
		HK_FORCE_INLINE const Cell& getCell(CellId cellId) const;
		HK_FORCE_INLINE Cell& accessCell(CellId cellId);

		/// Computes the number of boundary polygons
		HK_FORCE_INLINE int getNumBoundaryPolygons(CellId cellId) const;

		// Allocates a cell having the given number of boundary polygons
		HK_FORCE_INLINE CellId allocCell(int numBoundaryPolys);

		/// Frees the given cell
		HK_FORCE_INLINE void free(CellId cellId);

	public:

		/// Returns the first valid cell Id
		HK_FORCE_INLINE CellId getFirstCellId() const;

		/// Returns the last valid cell Id
		HK_FORCE_INLINE CellId getLastCellId() const;

		/// Returns the next valid cell Id
		HK_FORCE_INLINE CellId getNextCellId(CellId polyId) const;

		/// Returns the previous valid cell Id
		HK_FORCE_INLINE CellId getPrevCellId(CellId polyId) const;
};

#include <Geometry/Collide/DataStructures/PlanarGeometry/Memory/hkcdConvexCellsCollection.inl>

#endif	//	HKCD_CONVEX_CELLS_COLLECTION_H

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
