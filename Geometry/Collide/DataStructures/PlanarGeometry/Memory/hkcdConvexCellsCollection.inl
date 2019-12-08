/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

//
//	Returns true if the cell is a leaf

HK_FORCE_INLINE bool hkcdConvexCellsCollection::Cell::isLeaf() const
{
	return (m_flags & CELL_LEAF_MASK);
}

//
//	Returns true if the cell is empty / solid / unknown

HK_FORCE_INLINE int hkcdConvexCellsCollection::Cell::isEmpty() const	{	return (m_flags & CELL_EMPTY_MASK);	}
HK_FORCE_INLINE int hkcdConvexCellsCollection::Cell::isSolid() const	{	return (m_flags & CELL_SOLID_MASK);	}
HK_FORCE_INLINE int hkcdConvexCellsCollection::Cell::isUnknown() const	{	return !(isEmpty() || isSolid());			}
HK_FORCE_INLINE int hkcdConvexCellsCollection::Cell::isVisited() const	{	return ( m_flags & CELL_VISITED_MASK );}

//
//	Sets the cell as empty / solid

HK_FORCE_INLINE void hkcdConvexCellsCollection::Cell::setEmpty()				{	m_flags &= ~CELL_SOLID_MASK;	m_flags |= CELL_EMPTY_MASK;	}
HK_FORCE_INLINE void hkcdConvexCellsCollection::Cell::setSolid()				{	m_flags &= ~CELL_EMPTY_MASK;	m_flags |= CELL_SOLID_MASK;	}
HK_FORCE_INLINE void hkcdConvexCellsCollection::Cell::setVisited(bool visited)	{	if ( visited )	m_flags = m_flags | CELL_VISITED_MASK;	else m_flags = m_flags & (~CELL_VISITED_MASK); }
HK_FORCE_INLINE void hkcdConvexCellsCollection::Cell::setLeaf(bool leaf)		{	if ( leaf )		m_flags = m_flags | CELL_LEAF_MASK;		else m_flags = m_flags & (~CELL_LEAF_MASK); }

//
//	Returns the cell label

HK_FORCE_INLINE hkcdConvexCellsCollection::Labels hkcdConvexCellsCollection::Cell::getLabel() const
{
	return isEmpty() ? CELL_EMPTY : (isSolid() ? CELL_SOLID : CELL_UNKNOWN);
}

HK_FORCE_INLINE void hkcdConvexCellsCollection::Cell::setLabel(Labels l)
{
	HK_ASSERT(0x11e814a9, (l == CELL_SOLID) || (l == CELL_EMPTY));
	if ( l == CELL_SOLID )	{	setSolid();	}
	else					{	setEmpty();	}
}

//
//	Gets / Sets user data

HK_FORCE_INLINE hkUint32 hkcdConvexCellsCollection::Cell::getUserData() const
{
	return m_userData & PAYLOAD_MASK;
}

HK_FORCE_INLINE void hkcdConvexCellsCollection::Cell::setUserData(hkUint32 data)
{
	m_userData = (m_userData & (~PAYLOAD_MASK)) | (data & PAYLOAD_MASK);
}

//
//	Returns the i-th boundary polygon Id

HK_FORCE_INLINE hkcdConvexCellsCollection::PolygonId hkcdConvexCellsCollection::Cell::getBoundaryPolygonId(int i) const
{
	return PolygonId((&m_flags)[1 + i] & PAYLOAD_MASK);
}

HK_FORCE_INLINE void hkcdConvexCellsCollection::Cell::setBoundaryPolygonId(int i, PolygonId pid)
{
	hkUint32& p = (&m_flags)[1 + i];
	p = (p & BLOCK_FLAGS_MASK) | (pid.valueUnchecked() & PAYLOAD_MASK);
}

//
//	Retrieves the cell at the given Id.

HK_FORCE_INLINE const hkcdConvexCellsCollection::Cell& hkcdConvexCellsCollection::getCell(CellId cellId) const
{
	return *reinterpret_cast<const Cell*>(&m_storage[cellId.value()]);
}

HK_FORCE_INLINE hkcdConvexCellsCollection::Cell& hkcdConvexCellsCollection::accessCell(CellId cellId)
{
	return *reinterpret_cast<Cell*>(&m_storage[cellId.value()]);
}

//
//	Computes the number of boundary polygons

HK_FORCE_INLINE int hkcdConvexCellsCollection::getNumBoundaryPolygons(CellId cellId) const
{
	const int* polys = &m_storage[cellId.value() + hkcdConvexCellsCollection::Cell::FLAGS_OFFSET];

	int count = 0;
	while ( !(polys[count++] & END_PAYLOAD_FLAG) ) {}
	return count - 1;
}

//
//	Returns the first valid cell Id

HK_FORCE_INLINE hkcdConvexCellsCollection::CellId hkcdConvexCellsCollection::getFirstCellId() const
{
	return getNextCellId(CellId(INVALID_BLOCK_ADDR));
}

//
//	Returns the last valid cell Id

HK_FORCE_INLINE hkcdConvexCellsCollection::CellId hkcdConvexCellsCollection::getLastCellId() const
{
	return getPrevCellId(CellId(m_storage.getSize() - MIN_BLOCK_SIZE));
}

//
//	Returns the next valid cell Id

HK_FORCE_INLINE hkcdConvexCellsCollection::CellId hkcdConvexCellsCollection::getNextCellId(CellId cellId) const
{
	return CellId(getNextAllocatedAddress(cellId.valueUnchecked()));
}

//
//	Returns the next valid cell Id

HK_FORCE_INLINE hkcdConvexCellsCollection::CellId hkcdConvexCellsCollection::getPrevCellId(CellId cellId) const
{
	return CellId(getPrevAllocatedAddress(cellId.valueUnchecked()));
}

//
//	Allocates a cell

HK_FORCE_INLINE hkcdConvexCellsCollection::CellId hkcdConvexCellsCollection::allocCell(int numBoundaryPolys)
{
	// Allocate polygon storage
	hkUint32 allocSize = hkMath::max2<hkUint32>(MIN_BLOCK_SIZE, (sizeof(Cell) / sizeof(int)) + numBoundaryPolys);
	const CellId cellId(blockAlloc(allocSize));

	// Set it up
	Cell& cell = accessCell(cellId);
	cell.m_flags = 0;
	HK_ASSERT(0x5a938053, cell.isUnknown());

	// Get polygons and mark the last one
	hkUint32* polys = reinterpret_cast<hkUint32*>(&cell.m_flags);
	polys[numBoundaryPolys] |= END_PAYLOAD_FLAG;

	// Sanity checks
#ifdef HK_DEBUG
	{
		// There should be just one polygon marked as the end plane
		for (int k = 0; k < numBoundaryPolys; k++)
		{
			HK_ASSERT(0x49d67d2d, !(polys[k] & END_PAYLOAD_FLAG));
		}

		// There should be and end block marker
		HK_ASSERT(0x2b9d0370, polys[allocSize - hkcdConvexCellsCollection::Cell::BOUNDARY_POLY_OFFSET] & END_BLOCK_FLAG);

		// There should be no other end block marker
		for (hkUint32 k = 0; k < allocSize - hkcdConvexCellsCollection::Cell::BOUNDARY_POLY_OFFSET; k++)
		{
			HK_ASSERT(0x69e62ff3, !(polys[k] & END_BLOCK_FLAG));
		}
	}
#endif

	return cellId;
}

//
//	Frees the given cell

HK_FORCE_INLINE void hkcdConvexCellsCollection::free(CellId cellId)
{
	blockFree(cellId.value());
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
