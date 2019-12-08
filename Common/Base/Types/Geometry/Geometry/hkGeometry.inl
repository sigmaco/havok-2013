/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */


HK_FORCE_INLINE void hkGeometry::getTriangle(int triangleIndex, hkVector4* HK_RESTRICT vertices) const
{ 
	HK_ASSERT2(0xB9C6C634, triangleIndex >= 0 && triangleIndex < m_triangles.getSize(), "Index out-of-range"); 
	vertices[0] = m_vertices[m_triangles[triangleIndex].m_a];
	vertices[1] = m_vertices[m_triangles[triangleIndex].m_b];
	vertices[2] = m_vertices[m_triangles[triangleIndex].m_c];
}

HK_FORCE_INLINE hkResult hkGeometry::appendGeometry(const hkGeometry& geometry, const hkTransform& transform)
{
	hkMatrix4 transformMatrix;
	transformMatrix.set(transform);
	return appendGeometry(geometry, &transformMatrix);
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
