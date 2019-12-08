/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

//
//	Converts a vertex from / to float to / from fixed-precision

HK_FORCE_INLINE void hkcdPlanarGeometry::convertWorldPosition(hkVector4Parameter vSrc, hkIntVector& vDst) const
{
	hkVector4 v;	v.setSub(vSrc, m_offsetAndScale);
					v.mul(m_offsetAndScale.getComponent<3>());
					v.setMax(v,hkVector4::getZero());	// We shouldn't have negative numbers at this stage!
	vDst.setConvertF32toS32(v);
}

HK_FORCE_INLINE void hkcdPlanarGeometry::convertFixedPosition(hkIntVectorParameter vSrc, hkVector4& vDst) const
{
	hkSimdReal invScale;	invScale.setReciprocal<HK_ACC_FULL, HK_DIV_IGNORE>(m_offsetAndScale.getComponent<3>());
	hkVector4 v;			vSrc.convertS32ToF32(v);
							v.mul(invScale);
	vDst.setAdd(v, m_offsetAndScale);
}

//
//	Converts a direction from world to fixed-precision

HK_FORCE_INLINE void hkcdPlanarGeometry::convertWorldDirection(hkVector4Parameter vSrc, hkIntVector& vDst) const
{
	hkVector4 v;
	v.setMul(m_offsetAndScale.getComponent<3>(), vSrc);
	vDst.setConvertF32toS32(v);
}

//
//	Gets / sets the offset / scale that has been applied to all coordinates

HK_FORCE_INLINE const hkVector4& hkcdPlanarGeometry::getPositionOffset() const			{	return m_offsetAndScale;	}
HK_FORCE_INLINE const hkSimdReal hkcdPlanarGeometry::getPositionScale() const			{	return m_offsetAndScale.getComponent<3>();	}
HK_FORCE_INLINE void hkcdPlanarGeometry::setPositionOffset(hkVector4Parameter v)		{	const hkSimdReal s = getPositionScale(); m_offsetAndScale = v; setPositionScale(s);	}
HK_FORCE_INLINE void hkcdPlanarGeometry::setPositionScale(hkSimdRealParameter scale)	{	m_offsetAndScale.setComponent<3>(scale);	}

//
//	Return whether this geometry shares its plane with an other one

HK_FORCE_INLINE bool hkcdPlanarGeometry::sharesPlanesWith(const hkcdPlanarGeometry& other) const
{
	return (m_planes == other.m_planes);
}

//
//	Converts the plane equation for the given planeId to world

HK_FORCE_INLINE void hkcdPlanarGeometry::convertPlaneEquation(PlaneId planeId, hkVector4& worldPlaneEqnOut) const
{
	// Get plane and its equation
	Plane p;					m_planes->getPlane(planeId, p);
	hkVector4d dEqn				= p.getApproxEquation();

	// Scale offset
	HK_ALIGN16(hkReal) buf[4];		m_offsetAndScale.store<4, HK_IO_SIMD_ALIGNED>(buf);
	hkVector4d vOffset;				vOffset.load<4, HK_IO_NATIVE_ALIGNED>(buf);
	hkSimdDouble64 invScale			= vOffset.getComponent<3>();
									invScale.setReciprocal<HK_ACC_FULL, HK_DIV_IGNORE>(invScale);
	hkSimdDouble64 dOff;			dOff.setMul(invScale, dEqn.getComponent<3>());
	const hkSimdDouble64 deltaOff	= dEqn.dot<3>(vOffset);
									dOff.sub(deltaOff);

	// Set output
	dEqn.setComponent<3>(dOff);
	dEqn.store<4, HK_IO_SIMD_ALIGNED>(buf);
	worldPlaneEqnOut.load<4, HK_IO_SIMD_ALIGNED>(buf);
}

HK_FORCE_INLINE hkcdPlanarGeometry::PolygonId hkcdPlanarGeometry::addPolygon(PlaneId supportPlane, hkUint32 material, int numBounds)
{
	return m_polys.alloc(supportPlane, material, numBounds);
}

HK_FORCE_INLINE const hkcdPlanarGeometry::Polygon& hkcdPlanarGeometry::getPolygon(PolygonId polyId) const
{
	return m_polys.getPolygon(polyId);
}

HK_FORCE_INLINE hkcdPlanarGeometry::Polygon& hkcdPlanarGeometry::accessPolygon(PolygonId polyId)
{
	return m_polys.accessPolygon(polyId);
}

//
//	Computes the number of boundary planes

HK_FORCE_INLINE int hkcdPlanarGeometry::getNumBoundaryPlanes(PolygonId polyId) const
{
	return m_polys.getNumBoundaryPlanes(polyId);
}

//
//	Returns the collection of polygons

HK_FORCE_INLINE const hkcdPlanarGeometryPolygonCollection& hkcdPlanarGeometry::getPolygons() const	{	return m_polys;	}
HK_FORCE_INLINE hkcdPlanarGeometryPolygonCollection& hkcdPlanarGeometry::accessPolygons()			{	return m_polys;	}

//
//	Gets / Sets the plane collection associated with this geometry

HK_FORCE_INLINE void hkcdPlanarGeometry::setPlaneCollection(hkcdPlaneCollection* planes)	{	m_planes = planes;	}
HK_FORCE_INLINE const hkcdPlaneCollection* hkcdPlanarGeometry::getPlaneCollection() const	{	return m_planes;	}
HK_FORCE_INLINE hkcdPlaneCollection* hkcdPlanarGeometry::accessPlaneCollection()			{	return m_planes;	}

//
//	Returns the array of planes

HK_FORCE_INLINE const hkArray<hkcdPlanarGeometry::Plane>& hkcdPlanarGeometry::getPlanes() const	{	return m_planes->getPlanes();		}
HK_FORCE_INLINE hkArray<hkcdPlanarGeometry::Plane>& hkcdPlanarGeometry::accessPlanes()			{	return m_planes->accessPlanes();	}

//
//	Orientation cache Constructor. Initializes the multiplier with 4 large prime numbers.

template <int N>
HK_FORCE_INLINE hkcdPlanarGeometry::OrientationCache<N>::OrientationCache()
{
	m_mul.set(73856093, 19349663, 83492791, 52448047);

	hkIntVector iv;	iv.setAll(-1);
	m_data.setSize((1 << N), iv);
}

//
//	Computes the orientation for the given planes and updates the cache

template <int N>
HK_FORCE_INLINE hkcdPlanarGeometry::Orientation hkcdPlanarGeometry::OrientationCache<N>::getOrientation(hkIntVectorParameter planeIds, const Plane& pA, const Plane& pB, const Plane& pC, const Plane& pD)
{
	const int shift = 32 - hkcdPlanarGeometryPrimitives::FLIPPED_PLANE_BIT;

	// Convert plane Ids to our internal format
	hkIntVector v;
	{
		v.setShiftLeft32(planeIds, shift);
		v.setShiftRight32(v, shift);
		v.setSelect<hkVector4Comparison::MASK_XYZ>(v, planeIds);
		v.setSortS32<3, HK_SORT_ASCENDING>(v);
	}

	// Compute the hash, get the cached vector and compare with the given one
	hkIntVector vCache;	vCache.setMul(v, m_mul);
	const hkUint32 idx	= vCache.horizontalXorS32<4>() & ((1 << N) - 1);
	vCache = m_data[idx];
	
	Orientation ori = (Orientation)(vCache.getComponent<3>() & 0x7);
	vCache.setShiftRight32(vCache, shift - 1);
	if ( vCache.compareEqualS32(v).allAreSet() )
	{
		return ori;
	}

	// Not in cache, must compute now
	ori = hkcdPlanarGeometryPredicates::orientation(pA, pB, pC, pD);
	const hkBool32 cacheable = ori & hkcdPlanarGeometryPredicates::CACHEABLE;
	ori = (Orientation)(ori & hkcdPlanarGeometryPredicates::ORIENTATION_MASK);
	if ( cacheable  )
	{
		vCache.setShiftLeft32(v, shift - 1);
		vCache.setComponent<3>(vCache.getComponent<3>() | ori);
		m_data[idx] = vCache;
	}
	return ori;
}

//
//	Returns the offset & scale

HK_FORCE_INLINE const hkVector4& hkcdPlanarGeometry::getConversionOffset() const	{	return m_offsetAndScale;	}
HK_FORCE_INLINE const hkSimdReal hkcdPlanarGeometry::getConversionScale() const		{	return m_offsetAndScale.getComponent<3>();	}

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
