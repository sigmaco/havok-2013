/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

//
//	Gets the node having the given Id.

HK_FORCE_INLINE const hkcdSolidPlanarGeometry::Node& hkcdSolidPlanarGeometry::getNode(NodeId nodeId) const	{	return m_nodes[nodeId];	}
HK_FORCE_INLINE hkcdSolidPlanarGeometry::Node& hkcdSolidPlanarGeometry::accessNode(NodeId nodeId)			{	return m_nodes[nodeId];	}

//
//	Returns the nodes

HK_FORCE_INLINE const hkcdSolidPlanarGeometry::NodeStorage& hkcdSolidPlanarGeometry::getNodes() const
{
	return m_nodes;
}

//
//	Returns the planar geometry managing the planes of this solid

HK_FORCE_INLINE hkcdPlanarGeometry* hkcdSolidPlanarGeometry::accessGeometry()			{	return const_cast<hkcdPlanarGeometry*>(m_geometry.val());	}
HK_FORCE_INLINE const hkcdPlanarGeometry* hkcdSolidPlanarGeometry::getGeometry() const	{	return m_geometry;	}

//
//	Returns true if the tree is valid

HK_FORCE_INLINE bool hkcdSolidPlanarGeometry::isValid() const
{
	return m_rootNodeId.isValid();
}

//
//	Returns true if the tree represent the empty set

HK_FORCE_INLINE bool hkcdSolidPlanarGeometry::isEmpty() const
{
	return (isValid() && getNodeLabel(m_rootNodeId) == NODE_TYPE_OUT);
}

//
//	Returns true if the given node is internal

HK_FORCE_INLINE bool hkcdSolidPlanarGeometry::isInternal(NodeId nodeId) const
{
	if ( nodeId.isValid() )
	{
		const Node& node = getNode(nodeId);
		return node.isAllocated() && (node.m_typeAndFlags == NODE_TYPE_INTERNAL);
	}
	return false;
}

//
//	Returns the Id of the root node

HK_FORCE_INLINE const hkcdSolidPlanarGeometry::NodeId hkcdSolidPlanarGeometry::getRootNodeId() const
{
	return m_rootNodeId;
}

//
//	Returns the label of a given leaf node

HK_FORCE_INLINE hkcdSolidPlanarGeometry::NodeTypes hkcdSolidPlanarGeometry::getNodeLabel(NodeId nodeId) const
{
	const Node& node = getNode(nodeId);
	return (hkcdSolidPlanarGeometry::NodeTypes)node.m_typeAndFlags;
}

//
//	Creates a new internal node

HK_FORCE_INLINE hkcdSolidPlanarGeometry::NodeId hkcdSolidPlanarGeometry::createNode(PlaneId splitPlaneId, NodeId leftChild, NodeId rightChild)
{
	const NodeId nodeId = m_nodes.allocate();
	Node& node = accessNode(nodeId);

	node.m_planeId		= splitPlaneId;
	node.m_left			= leftChild;
	node.m_right		= rightChild;
	node.m_typeAndFlags	= NODE_TYPE_INTERNAL;
	node.m_data			= 0;
	return nodeId;
}

//
// Default nodes accessors

HK_FORCE_INLINE hkcdSolidPlanarGeometry::NodeId hkcdSolidPlanarGeometry::createInsideNode(NodeId parentId)
{
	NodeId inNodeId				= m_nodes.allocate();
	Node& nodeIn				= m_nodes[inNodeId];
	nodeIn.m_left				= NodeId::invalid();
	nodeIn.m_right				= NodeId::invalid();
	nodeIn.m_typeAndFlags		= NODE_TYPE_IN;
	nodeIn.m_planeId			= PlaneId::invalid();
	nodeIn.m_parent				= parentId;
	nodeIn.m_data				= 0;
	return inNodeId;
}

HK_FORCE_INLINE hkcdSolidPlanarGeometry::NodeId hkcdSolidPlanarGeometry::createOutsideNode(NodeId parentId)
{
	NodeId outNodeId			= m_nodes.allocate();
	Node& nodeOut				= m_nodes[outNodeId];
	nodeOut.m_left				= NodeId::invalid();
	nodeOut.m_right				= NodeId::invalid();
	nodeOut.m_typeAndFlags		= NODE_TYPE_OUT;
	nodeOut.m_planeId			= PlaneId::invalid();
	nodeOut.m_parent			= parentId;
	nodeOut.m_data				= 0;
	return outNodeId;
}

HK_FORCE_INLINE hkcdSolidPlanarGeometry::NodeId hkcdSolidPlanarGeometry::createUnknownNode(NodeId parentId)
{
	NodeId unknownNodeId		= m_nodes.allocate();
	Node& nodeUnknown			= m_nodes[unknownNodeId];
	nodeUnknown.m_left			= NodeId::invalid();
	nodeUnknown.m_right			= NodeId::invalid();
	nodeUnknown.m_typeAndFlags	= NODE_TYPE_UNKNOWN;
	nodeUnknown.m_planeId		= PlaneId::invalid();
	nodeUnknown.m_parent		= parentId;
	nodeUnknown.m_data			= 0;
	return unknownNodeId;
}

//
//	Sets the root node

HK_FORCE_INLINE void hkcdSolidPlanarGeometry::setRootNode(NodeId rootNodeId)
{
	m_rootNodeId = rootNodeId;
}

//
//	Returns true if the given node can be collapsed to its parent

HK_FORCE_INLINE bool hkcdSolidPlanarGeometry::canCollapse(NodeId nodeId) const
{
	if ( !nodeId.isValid() ) return false;
	const Node& node		= getNode(nodeId);
	const Node& nodeLeft	= getNode(node.m_left);
	const Node& nodeRight	= getNode(node.m_right);
	return	(nodeLeft.m_typeAndFlags == nodeRight.m_typeAndFlags) &&
			((nodeLeft.m_typeAndFlags == hkcdSolidPlanarGeometry::NODE_TYPE_IN) || (nodeLeft.m_typeAndFlags == hkcdSolidPlanarGeometry::NODE_TYPE_OUT));
}

//
//	Returns true if the triangle is allocated

HK_FORCE_INLINE bool hkcdSolidPlanarGeometry::Node::isAllocated() const
{
	return m_typeAndFlags != NODE_TYPE_FREE;
}

//
//	Marks this node as not-allocated

HK_FORCE_INLINE void hkcdSolidPlanarGeometry::Node::clear()
{
	m_typeAndFlags = NODE_TYPE_FREE;
}

//
//	Called by the free-list to initialize an unallocated entry

HK_FORCE_INLINE void hkcdSolidPlanarGeometry::Node::setEmpty(Node& element, hkUint32 next)
{
	(hkUint32&)element = next;	element.clear();
}

//
//	Returns the index of the next free element. Will be called only with empty elements

HK_FORCE_INLINE hkUint32 hkcdSolidPlanarGeometry::Node::getNext(const Node& element)
{
	return (hkUint32&)element;
}

//
//	Sets the given child id

HK_FORCE_INLINE void hkcdSolidPlanarGeometry::Node::setChildId(int childIdx, NodeId childNodeId)
{
	(&m_left)[childIdx] = childNodeId;
}

//
//	Classifies the polygons into inside, boundary, and outside parts

HK_FORCE_INLINE void hkcdSolidPlanarGeometry::classifyPolygons(	hkcdPlanarGeometry& polySoup, const hkArray<PolygonId>& polygonsIn, OrientationCache& orientationCache,
																hkArray<PolygonId>& insidePieces, hkArray<PolygonId>& boundaryPieces, hkArray<PolygonId>& outsidePieces) const
{
	classifyPolygons(polySoup, getRootNodeId(), polygonsIn, orientationCache, insidePieces, boundaryPieces, outsidePieces);
}

//
//	Recursively builds the tree for the given set of planes

HK_FORCE_INLINE void hkcdSolidPlanarGeometry::buildTree(hkcdPlanarGeometry& polySoup, hkPseudoRandomGenerator& rng, hkArray<PlaneId>& srcPlaneIds, const hkArray<PolygonId>& srcPolygonIds, bool useBoundaryPlanes, hkcdPlanarEntityDebugger* debugger)
{
	OrientationCache oCache;
	buildTree(polySoup, rng, srcPlaneIds, srcPolygonIds, useBoundaryPlanes, debugger, oCache);
}

//
//	Simplifies this by rebuilding its tree from its boundaries

HK_FORCE_INLINE void hkcdSolidPlanarGeometry::simplifyFromBoundaries()
{
	OrientationCache orientationCache;
	simplifyFromBoundaries(orientationCache);
}

//
//	Computes a set of polygons that cover the boundary of the solid

HK_FORCE_INLINE void hkcdSolidPlanarGeometry::computeBoundary(hkcdPlanarGeometry& boundaryGeomOut, hkcdPlanarEntityDebugger* debugger)
{
	OrientationCache orientationCache;
	computeBoundary(boundaryGeomOut, debugger, orientationCache);
}

//
//	Returns the convex cell tree corresponding to this solid planar geom. Build it if necessary.

HK_FORCE_INLINE hkcdConvexCellsTree* hkcdSolidPlanarGeometry::getOrCreateConvexCellTree(bool withConnectivity, bool rebuildIfConnectivityDoesntMatch)
{
	if ( !m_cellTree.val() || ( rebuildIfConnectivityDoesntMatch && (m_cellTree->hasManifoldCells() != withConnectivity)) )
	{
		// Build the tree now
		m_cellTree.setAndDontIncrementRefCount(new hkcdConvexCellsTree(const_cast<hkcdPlanarGeometry*>(m_geometry.val()), true));
		m_cellTree->buildFromSolidPlanarGeom(this, withConnectivity);
	}
	return getConvexCellTree();
}

//
//	Returns the convex cell tree corresponding to this solid planar geom. Can be NULL if the tree has not been computed yet.

HK_FORCE_INLINE hkcdConvexCellsTree* hkcdSolidPlanarGeometry::getConvexCellTree() const
{
	return m_cellTree;
}

//
//	Returns the convex cell tree corresponding to this solid planar geom. Can be NULL if the tree has not been computed yet.

HK_FORCE_INLINE void hkcdSolidPlanarGeometry::setConvexCellTree(hkcdConvexCellsTree* cellTree)
{
	m_cellTree = cellTree;
	if ( m_cellTree.val() ) m_cellTree->setSolidPlanarGeom(this);
}

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
