/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKCD_SOLID_PLANAR_GEOMETRY_H
#define HKCD_SOLID_PLANAR_GEOMETRY_H

#include <Common/Base/Types/hkHandle.h>
#include <Common/Base/Container/FreeListArray/hkFreeListArray.h>
#include <Common/Base/Algorithm/PseudoRandom/hkPseudoRandomGenerator.h>
#include <Common/Base/Algorithm/Collide/1AxisSweep/hk1AxisSweep.h>

#include <Geometry/Collide/DataStructures/PlanarGeometry/hkcdPlanarGeometry.h>
#include <Geometry/Collide/DataStructures/PlanarGeometry/hkcdConvexCellsTree.h>

/// A solid geometry, represented as a Bsp tree. The actual geometry is managed by a hkcdPlanarGeometry
class hkcdSolidPlanarGeometry : public hkcdPlanarEntity
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_GEOMETRY);

	public:

		// Types
		struct Node;
		HK_DECLARE_HANDLE(NodeId, hkUint32, 0xFFFFFFFFU);
		typedef hkFreeListArray<Node, NodeId, -1, Node>		NodeStorage;
		typedef hkcdPlanarGeometry::DefaultOrientationCache	OrientationCache;

	public:

		// Node type
		enum NodeTypes
		{
			NODE_TYPE_INTERNAL	= 0x0,	///< Internal BSP node
			NODE_TYPE_IN		= 0x1,	///< Leaf SOLID node, shared by all internal nodes
			NODE_TYPE_OUT		= 0x2,	///< Leaf EMPTY / OUTSIDE node, shared by all internal nodes
			NODE_TYPE_UNKNOWN	= 0x3,	///< Leaf unlabeled node, shared by all internal nodes
			NODE_TYPE_INVALID	= 0x4,	///< Value used to mark pre-allocated nodes that will no longer be used when these nodes will be removed from the code.
			NODE_TYPE_FREE		= 0xF,	///< The node is not allocated
		};

		// Node in the BSP tree
		struct Node
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_GEOMETRY, hkcdSolidPlanarGeometry::Node);

			/// Constructor
			HK_FORCE_INLINE Node()
			:	m_parent(NodeId::invalid())
			,	m_typeAndFlags(NODE_TYPE_FREE)
			{}

			/// Returns true if the triangle is allocated
			HK_FORCE_INLINE bool isAllocated() const;

			/// Marks this node as not-allocated
			HK_FORCE_INLINE void clear();

			/// Called by the free-list to initialize an unallocated entry
			HK_FORCE_INLINE static void setEmpty(Node& element, hkUint32 next);

			/// Returns the index of the next free element. Will be called only with empty elements
			HK_FORCE_INLINE static hkUint32 getNext(const Node& element);

			/// Sets the given child id
			HK_FORCE_INLINE void setChildId(int childIdx, NodeId childNodeId);
			
			NodeId	m_parent;			///< Parent node.
			NodeId	m_left;				///< Left child, contains the space behind the splitting plane (inside)
			NodeId	m_right;			///< Right child, contains the space in front of the splitting plane (outside)
			PlaneId m_planeId;			///< Splitting plane
			hkUint32 m_data;			///< User data, typically used to store a spatial CellId
			hkUint32 m_typeAndFlags;	///< Type and flags, a combination of values in NodeTypes
		};

	public:

		/// Constructor
		hkcdSolidPlanarGeometry(const hkcdPlanarGeometry* geom, int initialNodeCapacity = 0);

		/// Copy constructor
		hkcdSolidPlanarGeometry(const hkcdSolidPlanarGeometry& other, bool cloneConvexCells);

		/// Destructor
		virtual ~hkcdSolidPlanarGeometry();

	public:

		/// Builds a convex solid from an array of planes. The planes are assumed to bound a closed convex region, there are no checks to validate the assumption!
		void buildConvex(const PlaneId* HK_RESTRICT planesIn, int numPlanes);

		/// Builds the tree for the given set of planes
		void buildTree(hkcdPlanarGeometry& polySoup, hkPseudoRandomGenerator& rng, hkArray<PlaneId>& planes, const hkArray<PolygonId>& polygons, bool useBoundaryPlanes, hkcdPlanarEntityDebugger* debugger, OrientationCache& orientationCache);

		/// Sets a new geometry. If the plane remapping table is non-null, the plane Ids on all nodes will be re-set as well (i.e. to match the plane Ids in the new geometry)
		void setGeometry(const hkcdPlanarGeometry* newGeom, const int* HK_RESTRICT planeRemapTable);

		/// Remaps the plane Ids using the given remap table
		void remapPlaneIds(const hkArray<int>& planeRemapTable);

		/// Simplifies the tree by collapsing nodes with identical labels. Returns true if something was collapsed
		hkBool32 collapseIdenticalLabels();

		/// Optimizes the storage, by moving all unallocated nodes at the end and releasing unused memory. This will
		/// modify the Ids of the nodes!
		void optimizeStorage();

		/// Collapses any nodes still marked as unknown
		hkBool32 collapseUnknownLabels();

		/// Classifies the polygons into inside, boundary, and outside parts
		HK_FORCE_INLINE void classifyPolygons(	hkcdPlanarGeometry& polySoup, const hkArray<PolygonId>& polygonsIn, OrientationCache& orientationCache,
												hkArray<PolygonId>& insidePieces, hkArray<PolygonId>& boundaryPieces, hkArray<PolygonId>& outsidePieces) const;

		/// Collects all the plane Ids used by the Bsp tree
		void collectUsedPlaneIds(hkBitField& usedPlaneIdsOut) const;

		/// Computes a set of polygons that cover the boundary of the solid
		void computeBoundary(hkcdPlanarGeometry& boundaryGeomOut, hkcdPlanarEntityDebugger* debugger, OrientationCache& orientationCache);

		/// Simplifies this by rebuilding its tree from its boundaries
		void simplifyFromBoundaries(OrientationCache& orientationCache);

		/// Returns the maximum depth of the tree
		int computeMaxDepth() const;

		// Clears the tree
		void clear();
		
		/// Replaces allocated nodes by default ones when possible
		void replaceAllocatedNodesByDefaultNodes();

		/// Computes the number of nodes with the specified label
		int computeNumNodesWithLabel(hkUint32 label) const;

		/// Computes the number of leaf nodes
		int computeNumLeafNodes() const;

	public:

		/// Gets the node having the given Id.
		HK_FORCE_INLINE const Node& getNode(NodeId nodeId) const;
		HK_FORCE_INLINE Node& accessNode(NodeId nodeId);

		/// Returns the nodes
		HK_FORCE_INLINE const NodeStorage& getNodes() const;

		/// Returns the planar geometry managing the planes of this solid
		HK_FORCE_INLINE hkcdPlanarGeometry* accessGeometry();
		HK_FORCE_INLINE const hkcdPlanarGeometry* getGeometry() const;

		/// Returns true if the tree is valid
		HK_FORCE_INLINE bool isValid() const;

		/// Returns true if the tree represent the empty set
		HK_FORCE_INLINE bool isEmpty() const;

		/// Returns true if the given node is internal
		HK_FORCE_INLINE bool isInternal(NodeId nodeId) const;

		/// Default nodes accessors
		HK_FORCE_INLINE NodeId createInsideNode(NodeId parentId);
		HK_FORCE_INLINE NodeId createOutsideNode(NodeId parentId);
		HK_FORCE_INLINE NodeId createUnknownNode(NodeId parentId);

		/// Returns the Id of the root node
		HK_FORCE_INLINE const NodeId getRootNodeId() const;

		/// Returns the label of a given leaf node
		HK_FORCE_INLINE NodeTypes getNodeLabel(NodeId nodeId) const;

		/// Creates a new internal node
		HK_FORCE_INLINE NodeId createNode(PlaneId splitPlaneId, NodeId leftChild, NodeId rightChild);

		/// Sets the root node
		HK_FORCE_INLINE void setRootNode(NodeId rootNodeId);

		/// Returns true if the given node can be collapsed to its parent
		HK_FORCE_INLINE bool canCollapse(NodeId nodeId) const;	

		/// Builds the tree for the given set of planes
		HK_FORCE_INLINE void buildTree(hkcdPlanarGeometry& polySoup, hkPseudoRandomGenerator& rng, hkArray<PlaneId>& planes, const hkArray<PolygonId>& polygons, bool useBoundaryPlanes, hkcdPlanarEntityDebugger* debugger);

		/// Computes a set of polygons that cover the boundary of the solid
		HK_FORCE_INLINE void computeBoundary(hkcdPlanarGeometry& boundaryGeomOut, hkcdPlanarEntityDebugger* debugger = HK_NULL);

		/// Simplifies this by rebuilding its tree from its boundaries
		HK_FORCE_INLINE void simplifyFromBoundaries();

		// Access to convex cell tree

		/// Returns the convex cell tree corresponding to this solid planar geom. Build it if necessary.
		HK_FORCE_INLINE hkcdConvexCellsTree* getOrCreateConvexCellTree(bool withConnectivity = false, bool rebuildIfConnectivityDoesntMatch = true);

		/// Returns the convex cell tree corresponding to this solid planar geom. Can be NULL if the tree has not been computed yet.
		HK_FORCE_INLINE hkcdConvexCellsTree* getConvexCellTree() const;

		/// Returns the convex cell tree corresponding to this solid planar geom. Can be NULL if the tree has not been computed yet.
		HK_FORCE_INLINE void setConvexCellTree(hkcdConvexCellsTree* cellTree);

	protected:

		// Selects a splitting plane from the given list
		int pickSplittingPlane(	const hkcdPlanarGeometry& polySoup, hkPseudoRandomGenerator& rng,
								const PlaneId* HK_RESTRICT planeIds, int numPlaneIds,
								const PolygonId* HK_RESTRICT polygonIds, int numPolygonIds);

		/// Classifies the polygons into inside, boundary, and outside parts
		void classifyPolygons(	hkcdPlanarGeometry& polySoup, NodeId nodeId,
								const hkArray<PolygonId>& polygonsIn, OrientationCache& orientationCache,
								hkArray<PolygonId>& insidePieces, hkArray<PolygonId>& boundaryPieces, hkArray<PolygonId>& outsidePieces) const;

	protected:

		/// The nodes in the Bsp tree
		NodeStorage m_nodes;

		/// The geometry that manages the planes
		hkRefPtr<const hkcdPlanarGeometry> m_geometry;

		hkRefPtr<hkcdConvexCellsTree> m_cellTree;		///< convex cells tree corresponding to this BSP tree

		NodeId m_rootNodeId;	///< The root node
};

#include <Geometry/Collide/DataStructures/PlanarGeometry/hkcdSolidPlanarGeometry.inl>

#endif	//	HKCD_SOLID_PLANAR_GEOMETRY_H

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
