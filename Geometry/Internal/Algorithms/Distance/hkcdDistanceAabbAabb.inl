/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

//
HK_FORCE_INLINE hkSimdReal hkcdAabbAabbDistanceSquared(const hkAabb& a, hkVector4Parameter center, hkVector4Parameter halfExtents)
{
	hkAabb		aabb;
	aabb.m_min.setSub(a.m_min, halfExtents);
	aabb.m_max.setAdd(a.m_max, halfExtents);

	hkVector4	projection;
	projection.setMin(aabb.m_max, center);
	projection.setMax(aabb.m_min, projection);

	return projection.distanceToSquared(center);
}

//
//	Computes the squared distance between a point and an AABB

HK_FORCE_INLINE const hkSimdReal hkcdPointAaabbDistanceSquared(hkVector4Parameter vPt, const hkAabb& aabb)
{
	hkVector4 projection;
	projection.setMin(aabb.m_max, vPt);
	projection.setMax(aabb.m_min, projection);
	projection.sub(vPt);

	return projection.lengthSquared<3>();
}

//
HK_FORCE_INLINE hkSimdReal hkcdAabbAabbDistanceSquared(const hkAabb& a, const hkAabb& b)
{
	hkVector4	halfExtents; b.getHalfExtents(halfExtents);
	hkVector4	center; b.getCenter(center);

	return hkcdAabbAabbDistanceSquared(a, center, halfExtents);
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
