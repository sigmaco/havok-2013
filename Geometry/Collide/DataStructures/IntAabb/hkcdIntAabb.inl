/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

//
//	Sets this = empty AABB

HK_FORCE_INLINE void hkcdIntAabb::setEmpty()
{
	m_min.setAll(0x7FFFFFFF);
	m_max.setNegS32<4>(m_min);
}

//
//	Enlarges the AABB to include the given point

HK_FORCE_INLINE void hkcdIntAabb::includePoint(hkIntVectorParameter v)
{
	m_min.setMinS32(m_min, v);
	m_max.setMaxS32(m_max, v);
}

//
//	Expands the box by the given radius

HK_FORCE_INLINE void hkcdIntAabb::expandBy(int radius)
{
	hkIntVector v;	v.setAll(radius);
	m_min.setSubS32(m_min, v);
	m_max.setAddU32(m_max, v);
}

//
//	Returns true if the point is inside the AABB

HK_FORCE_INLINE hkBool32 hkcdIntAabb::containsPoint(hkIntVectorParameter v) const
{
	hkVector4Comparison cmp;
	cmp.setAnd(v.greaterEqualS32(m_min), m_max.greaterEqualS32(v));
	return cmp.horizontalAnd<3>().anyIsSet();
}

//
//	Sets the AABB to be the intersection AABB of the two given input AABBs.
//	The result can be invalid if the two input AABBs do not overlap. Use isEmpty() to verify this.

HK_FORCE_INLINE void hkcdIntAabb::setIntersection(const hkcdIntAabb& aabb0, const hkcdIntAabb& aabb1)
{
	m_min.setMaxS32(aabb0.m_min, aabb1.m_min);
	m_max.setMinS32(aabb0.m_max, aabb1.m_max);
}

//
//	Returns true if the AABB is empty, e.g., its min is greater than its max for any dimension.

HK_FORCE_INLINE bool hkcdIntAabb::isEmpty() const
{
	hkVector4Comparison comp = m_min.greaterEqualS32(m_max);
	return comp.horizontalOr<3>().anyIsSet();
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
