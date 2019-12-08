/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

//
//	Returns the material id

HK_FORCE_INLINE hkUint32 hkcdPlanarGeometryPolygonCollection::Polygon::getMaterialId() const
{
	return m_materialId & PAYLOAD_MASK;
}

HK_FORCE_INLINE void hkcdPlanarGeometryPolygonCollection::Polygon::setMaterialId(int mtlId)
{
	HK_ASSERT(0x1cf0dcaf, !(mtlId & BLOCK_FLAGS_MASK));
	m_materialId = (mtlId & PAYLOAD_MASK) | (m_materialId & BLOCK_FLAGS_MASK);
}

//
//	Returns the support plane id

HK_FORCE_INLINE hkcdPlanarGeometryPolygonCollection::PlaneId hkcdPlanarGeometryPolygonCollection::Polygon::getSupportPlaneId() const
{
	return PlaneId(m_supportId & PAYLOAD_MASK);
}

HK_FORCE_INLINE void hkcdPlanarGeometryPolygonCollection::Polygon::setSupportPlaneId(PlaneId pid)
{
	m_supportId = (m_supportId & BLOCK_FLAGS_MASK) | (pid.valueUnchecked() & PAYLOAD_MASK);
}

//
//	Returns a read-only pointer to the boundary planes

HK_FORCE_INLINE const hkcdPlanarGeometryPolygonCollection::PlaneId* hkcdPlanarGeometryPolygonCollection::Polygon::getBoundaryPlaneIds() const
{
	return reinterpret_cast<const PlaneId*>((&m_supportId) + 1);
}

//
//	Returns the i-th boundary plane Id

HK_FORCE_INLINE hkcdPlanarGeometryPolygonCollection::PlaneId hkcdPlanarGeometryPolygonCollection::Polygon::getBoundaryPlaneId(int i) const
{
	return PlaneId((&m_supportId)[1 + i] & PAYLOAD_MASK);
}

HK_FORCE_INLINE void hkcdPlanarGeometryPolygonCollection::Polygon::setBoundaryPlaneId(int i, PlaneId pid)
{
	hkUint32& p = (&m_supportId)[1 + i];
	p = (p & BLOCK_FLAGS_MASK) | (pid.valueUnchecked() & PAYLOAD_MASK);
}

//
//	Gets / sets the cell ids

HK_FORCE_INLINE hkUint32 hkcdPlanarGeometryPolygonCollection::Polygon::getNegCellId() const
{
	return m_negCellId & PAYLOAD_MASK;
}

HK_FORCE_INLINE void hkcdPlanarGeometryPolygonCollection::Polygon::setNegCellId(hkUint32 cellId)
{
	m_negCellId = (cellId & PAYLOAD_MASK) | (m_negCellId & BLOCK_FLAGS_MASK);
}

HK_FORCE_INLINE hkUint32 hkcdPlanarGeometryPolygonCollection::Polygon::getPosCellId() const
{
	return m_posCellId & PAYLOAD_MASK;
}

HK_FORCE_INLINE void hkcdPlanarGeometryPolygonCollection::Polygon::setPosCellId(hkUint32 cellId)
{
	m_posCellId = (cellId & PAYLOAD_MASK) | (m_posCellId & BLOCK_FLAGS_MASK);
}

//
//	Retrieves the polygon at the given Id.

HK_FORCE_INLINE const hkcdPlanarGeometryPolygonCollection::Polygon& hkcdPlanarGeometryPolygonCollection::getPolygon(PolygonId polyId) const
{
	return *reinterpret_cast<const Polygon*>(&m_storage[polyId.value()]);
}

HK_FORCE_INLINE hkcdPlanarGeometryPolygonCollection::Polygon& hkcdPlanarGeometryPolygonCollection::accessPolygon(PolygonId polyId)
{
	return *reinterpret_cast<Polygon*>(&m_storage[polyId.value()]);
}

//
//	Allocates a polygon

HK_FORCE_INLINE hkcdPlanarGeometryPolygonCollection::PolygonId hkcdPlanarGeometryPolygonCollection::alloc(PlaneId supportPlaneId, hkUint32 materialId, int numBoundaryPlanes)
{
	// Allocate polygon storage
	hkUint32 allocSize = hkMath::max2<hkUint32>(MIN_BLOCK_SIZE, (sizeof(Polygon) / sizeof(int)) + numBoundaryPlanes);
	const PolygonId polyId(blockAlloc(allocSize));

	// Set it up
	Polygon& poly = accessPolygon(polyId);
	poly.setMaterialId(materialId);
	poly.setSupportPlaneId(supportPlaneId);

	// Get planes and mark the last one
	hkUint32* planes = reinterpret_cast<hkUint32*>(&poly.m_supportId);
	planes[numBoundaryPlanes] |= END_PAYLOAD_FLAG;

	// Sanity checks
#ifdef HK_DEBUG
	{
		// There should be just one plane marked as the end plane
		for (int k = 0; k < numBoundaryPlanes; k++)
		{
			HK_ASSERT(0x5e96e8a3, !(planes[k] & END_PAYLOAD_FLAG));
		}

		// There should be and end block marker
		HK_ASSERT(0x27fb4c, planes[allocSize - 4] & END_BLOCK_FLAG);

		// There should be no other end block marker
		for (hkUint32 k = 0; k < allocSize - 4; k++)
		{
			HK_ASSERT(0x20fa5bdb, !(planes[k] & END_BLOCK_FLAG));
		}
	}
#endif

	return polyId;
}

//
//	Frees the given polygon

HK_FORCE_INLINE void hkcdPlanarGeometryPolygonCollection::free(PolygonId polyId)
{
	blockFree(polyId.value());
}

//
//	Computes the number of boundary planes

HK_FORCE_INLINE int hkcdPlanarGeometryPolygonCollection::getNumBoundaryPlanes(PolygonId polyId) const
{
	const int* planes = &m_storage[polyId.value() + Polygon::SUPPORT_PLANE_ID_OFFSET];

	int count = 0;
	while ( !(planes[count++] & END_PAYLOAD_FLAG) ) {}
	return count - 1;
}

//
//	Returns the first valid polygon Id

HK_FORCE_INLINE hkcdPlanarGeometryPolygonCollection::PolygonId hkcdPlanarGeometryPolygonCollection::getFirstPolygonId() const
{
	return getNextPolygonId(PolygonId(INVALID_BLOCK_ADDR));
}

//
//	Returns the last valid polygon Id

HK_FORCE_INLINE hkcdPlanarGeometryPolygonCollection::PolygonId hkcdPlanarGeometryPolygonCollection::getLastPolygonId() const
{
	return getPrevPolygonId(PolygonId(m_storage.getSize() - MIN_BLOCK_SIZE));
}

//
//	Returns the next valid polygon Id

HK_FORCE_INLINE hkcdPlanarGeometryPolygonCollection::PolygonId hkcdPlanarGeometryPolygonCollection::getNextPolygonId(PolygonId polyId) const
{
	return PolygonId(getNextAllocatedAddress(polyId.valueUnchecked()));
}

//
//	Returns the next valid polygon Id

HK_FORCE_INLINE hkcdPlanarGeometryPolygonCollection::PolygonId hkcdPlanarGeometryPolygonCollection::getPrevPolygonId(PolygonId polyId) const
{
	return PolygonId(getPrevAllocatedAddress(polyId.valueUnchecked()));
}

//
//	Returns the number of valid polygon Ids stored

HK_FORCE_INLINE int hkcdPlanarGeometryPolygonCollection::getNumPolygons() const
{
	int count = 0;
	for (PolygonId pid = getFirstPolygonId(); pid.isValid(); pid = getNextPolygonId(pid))
	{
		count++;
	}
	return count;
}

//
//	Reverses the boundary winding

HK_FORCE_INLINE void hkcdPlanarGeometryPolygonCollection::flipWinding(PolygonId polyId)
{
	const int n		= getNumBoundaryPlanes(polyId) - 1;
	Polygon& poly	= accessPolygon(polyId);
	for (int i = 0; (i << 1) < n; i++)
	{
		const PlaneId boundI	= poly.getBoundaryPlaneId(i);
		const PlaneId boundNI	= poly.getBoundaryPlaneId(n - i);

		poly.setBoundaryPlaneId(i, boundNI);
		poly.setBoundaryPlaneId(n - i, boundI);
	}

	poly.setSupportPlaneId(hkcdPlanarGeometryPrimitives::getOppositePlaneId(poly.getSupportPlaneId()));
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
