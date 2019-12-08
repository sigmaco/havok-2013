/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

inline const hkpConvexShape* hkpConvexTransformShape::getChildShape() const 
{
	return static_cast<const hkpConvexShape*>( m_childShape.getChild() ); 
}

inline void hkpConvexTransformShape::setTransform( const hkTransform& transform)
{
	m_transform.setFromTransformNoScale( transform );
	m_extraScale.setZero();
}

inline void hkpConvexTransformShape::getTransform( hkTransform* HK_RESTRICT transform ) const
{ 
	HK_ON_DEBUG( hkSimdReal eps; eps.setFromFloat( HK_REAL_EPSILON ); );
	HK_WARN_ON_DEBUG_IF( !m_transform.m_scale.allEqual<3>( hkVector4::getConstant<HK_QUADREAL_1>(), eps ), 0x37b36bdf, "Non-identity scale is being lost in hkQsTransform to hkTransform conversion" );
	m_transform.copyToTransformNoScale( *transform );
}

inline const hkQsTransform& hkpConvexTransformShape::getQsTransform() const 
{
	return m_transform; 
}

inline const hkVector4& hkpConvexTransformShape::getExtraScale() const 
{
	return m_extraScale;
}


HK_FORCE_INLINE int hkpConvexTransformShape::getNumCollisionSpheres() const
{
	return getChildShape()->getNumCollisionSpheres();
}

HK_FORCE_INLINE void hkpConvexTransformShape::transformVertex(hkVector4Parameter localVertex, hkVector4* HK_RESTRICT vertexOut) const
{
	// Reconstruct aabb center from w coordinates
	hkVector4 center;
	center.set(m_transform.m_translation.getW(), m_transform.m_scale.getW(), m_extraScale.getW(), hkSimdReal_0);

	// Apply transform's scale and add then apply the extra scale relative to the aabb center
	hkVector4 vertexInAabb; vertexInAabb.setSub(localVertex, center);	
	vertexOut->setMul(localVertex, m_transform.getScale());
	vertexOut->addMul(m_extraScale, vertexInAabb);

	// Rotate and translate
	vertexOut->_setRotatedDir(m_transform.getRotation(), *vertexOut);
	vertexOut->add(m_transform.getTranslation());
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
