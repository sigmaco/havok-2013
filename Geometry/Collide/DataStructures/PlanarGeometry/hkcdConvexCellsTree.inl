/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

//
//	Returns the cell with the given Id

HK_FORCE_INLINE const hkcdConvexCellsTree::Cell& hkcdConvexCellsTree::getCell(CellId cellId) const	{	return m_cells.getCell(cellId);		}
HK_FORCE_INLINE hkcdConvexCellsTree::Cell& hkcdConvexCellsTree::accessCell(CellId cellId)			{	return m_cells.accessCell(cellId);	}

//
//	Returns the cells collection

HK_FORCE_INLINE const hkcdConvexCellsCollection& hkcdConvexCellsTree::getCells() const	{	return m_cells;	}
HK_FORCE_INLINE hkcdConvexCellsCollection& hkcdConvexCellsTree::accessCells()			{	return m_cells;	}

//
//	Returns whether the tree has been built with connectivity information

HK_FORCE_INLINE bool hkcdConvexCellsTree::hasManifoldCells()
{
	return m_buildCellConnectivity;
}

//
//	Creates a polygon for the given splitting plane

HK_FORCE_INLINE void hkcdConvexCellsTree::createSplittingPolygon(PlaneId splitPlaneId, PlaneId* boundsOut) const
{
	// Get splitting plane
	Plane splitPlane;	m_planes->getPlane(splitPlaneId, splitPlane);

	// We'll use the same boundary as the boundary polygon with the normal closest to the split plane normal
	hkInt64Vector4 iNrm;			splitPlane.getExactNormal(iNrm);
	hkInt64Vector4 absN;			absN.setAbs(iNrm);
	const int maxIdx				= absN.getIndexOfMaxComponent<3>();
	const hkVector4fComparison cmpN	= iNrm.lessZero();
	const Bounds boundsTemplate		= (Bounds)(((cmpN.getMask() >> maxIdx) & 1) | (maxIdx << 1));

	const Polygon& polyTemplate	= m_mesh->getPolygon(m_boundingPolys[boundsTemplate]);
	boundsOut[0] = polyTemplate.getBoundaryPlaneId(0);
	boundsOut[1] = polyTemplate.getBoundaryPlaneId(1);
	boundsOut[2] = polyTemplate.getBoundaryPlaneId(2);
	boundsOut[3] = polyTemplate.getBoundaryPlaneId(3);
}

//
//	Adds a closing polygon cap created from the given splitting plane

HK_FORCE_INLINE hkcdConvexCellsTree::PolygonId hkcdConvexCellsTree::addClosingCap(const PlaneId* clippingPlanes, int numPlanes, OrientationCache& orientationCache, PlaneId splitPlaneId)
{
	// Get the number of cell polygons and allocate a working buffer
	const hkUint32 maxNumBounds	= 4 + numPlanes;

	hkInplaceArray<PlaneId, 1024> boundsBuffer;
	boundsBuffer.setSize(maxNumBounds << 1);

	// Create unclipped capping polygon
	PlaneId* inputBounds	= &boundsBuffer[0];
	PlaneId* clippedBounds	= &boundsBuffer[maxNumBounds];
	createSplittingPolygon(splitPlaneId, inputBounds);

	// Clip against all cell boundaries
	const hkUint32 numBounds	= m_mesh->clipPolygon(splitPlaneId, inputBounds, clippedBounds, 4, orientationCache, clippingPlanes, numPlanes);
	const PolygonId splitPolyId = m_mesh->addPolygon(splitPlaneId, 0, numBounds);
	Polygon& poly				= m_mesh->accessPolygon(splitPolyId);
	for (int k = numBounds - 1; k >= 0; k--)
	{
		poly.setBoundaryPlaneId(k, clippedBounds[k]);
	}

	// Add clipped polygon to the cell boundary, thus closing it off
	return splitPolyId;
}

//
//	Check if two neighboring cells can be reached

HK_FORCE_INLINE bool hkcdConvexCellsTree::canGoFromCellThroughPoly(CellId fromCellId, PolygonId throughPolygonId, bool fromOutside)
{
	const Polygon& poly = m_mesh->getPolygon(throughPolygonId);
	// Quick exits 
	if ( poly.getMaterialId() == POLY_SURFACE_OPEN )		return true;
	if ( poly.getMaterialId() == POLY_SURFACE_WATERTIGHT )	return false;

	// Check if we are going in the right direction
	const PlaneId polyPlaneId			= poly.getSupportPlaneId();
	const PlaneId cellPolyPlaneId		= ( poly.getPosCellId() == fromCellId.value() )		? polyPlaneId : hkcdPlanarGeometryPrimitives::getOppositePlaneId(polyPlaneId);
	const PlaneId surfacePlaneId		= ( poly.getMaterialId() == POLY_SURFACE_DIRECT )	? polyPlaneId : hkcdPlanarGeometryPrimitives::getOppositePlaneId(polyPlaneId);
	const bool surfaceTowardsCell		= ( cellPolyPlaneId.value() == surfacePlaneId.value() );

	return ( fromOutside ) ? surfaceTowardsCell : !surfaceTowardsCell;
}

//
//	Computes the number of boundary planes

HK_FORCE_INLINE int hkcdConvexCellsTree::getNumBoundaryPlanes(CellId cellId) const
{
	return m_cells.getNumBoundaryPolygons(cellId);
}

//
//	Returns the requested world boundary plane

HK_FORCE_INLINE hkcdConvexCellsTree::PlaneId hkcdConvexCellsTree::getWorldBoundaryPlaneId(Bounds b) const	{	return m_boundingPlanes[b];	}
HK_FORCE_INLINE void hkcdConvexCellsTree::setWorldBoundaryPlaneId(Bounds b, PlaneId pid)					{	m_boundingPlanes[b] = pid;	}

//
//	Returns the geometry

HK_FORCE_INLINE const hkcdPlanarGeometry* hkcdConvexCellsTree::getGeometry() const	{	return m_mesh;	}

/// Sets the solid planar geometry associated to this tree
HK_FORCE_INLINE void hkcdConvexCellsTree::setSolidPlanarGeom(hkcdSolidPlanarGeometry* sGeom) { m_solidMesh = sGeom; }

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
