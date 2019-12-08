/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

//
//	Returns the given plane

HK_FORCE_INLINE void hkcdPlaneCollection::getPlane(PlaneId planeId, Plane& planeOut) const
{
	const int idx = planeId.value() & (~hkcdPlanarGeometryPrimitives::FLIPPED_PLANE_FLAG);
	const Plane& p = m_planes[idx];

	if ( planeId.value() & hkcdPlanarGeometryPrimitives::FLIPPED_PLANE_FLAG )
	{
		planeOut.setOpposite(p);
	}
	else
	{
		planeOut = p;
	}
}

//
//	Adds a new plane

HK_FORCE_INLINE hkcdPlaneCollection::PlaneId hkcdPlaneCollection::addPlane(const Plane& plane)
{
	const PlaneId planeId(m_planes.getSize());
	m_planes.pushBack(plane);
	return planeId;
}

//
//	Returns the array of planes

HK_FORCE_INLINE const hkArray<hkcdPlaneCollection::Plane>& hkcdPlaneCollection::getPlanes() const	{	return m_planes;	}
HK_FORCE_INLINE hkArray<hkcdPlaneCollection::Plane>& hkcdPlaneCollection::accessPlanes()			{	return m_planes;	}

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
