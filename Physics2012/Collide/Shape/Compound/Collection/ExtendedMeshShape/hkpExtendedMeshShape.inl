/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

int hkpExtendedMeshShape::getNumTrianglesSubparts() const
{
	return m_trianglesSubparts.getSize();
}

int hkpExtendedMeshShape::getNumShapesSubparts() const
{
	return m_shapesSubparts.getSize();
}

hkpExtendedMeshShape::TrianglesSubpart& hkpExtendedMeshShape::getTrianglesSubpartAt( int i )
{
	HK_ASSERT2(0x3031b232,  i < getNumTrianglesSubparts(), "You are trying to access a triangles-subpart which is not in the triangle subpart array");
	return m_trianglesSubparts[i];
}

const hkpExtendedMeshShape::TrianglesSubpart& hkpExtendedMeshShape::getTrianglesSubpartAt( int i ) const
{
	HK_ASSERT2(0x2bb0d984,  i < getNumTrianglesSubparts(), "You are trying to access a triangles-subpart which is not in the triangle subpart array");
	return m_trianglesSubparts[i];
}

hkpExtendedMeshShape::ShapesSubpart& hkpExtendedMeshShape::getShapesSubpartAt( int i )
{
	HK_ASSERT2(0x30312232,  i < getNumShapesSubparts(), "You are trying to access a shapes-subpart which is not in the shape subpart array");
	return m_shapesSubparts[i];
}

const hkpExtendedMeshShape::ShapesSubpart& hkpExtendedMeshShape::getShapesSubpartAt( int i ) const
{
	HK_ASSERT2(0x2bb05984,  i < getNumShapesSubparts(), "You are trying to access a shapes-subpart which is not in the shape subpart array");
	return m_shapesSubparts[i];
}

hkInt32 hkpExtendedMeshShape::getSubPartIndex( hkpShapeKey key ) const
{
	const hkUint32 subpartIndex = (key & 0x7fffffff) >> ( 32 - m_numBitsForSubpartIndex );
	return subpartIndex;
}

hkpExtendedMeshShape::SubpartType hkpExtendedMeshShape::getSubpartType( hkpShapeKey key ) const
{
	if ( !((key) & 0x80000000) )
	{
		return SUBPART_TRIANGLES;
	}
	else
	{
		return SUBPART_SHAPE;
	}
}

const hkpExtendedMeshShape::Subpart& hkpExtendedMeshShape::getSubPart( hkpShapeKey key ) const
{
	hkUint32 subpartIndex = getSubPartIndex(key);

	if ( getSubpartType(key) == SUBPART_TRIANGLES )
	{
		return m_trianglesSubparts[ subpartIndex ];
	}
	else
	{
		return m_shapesSubparts[ subpartIndex ];
	}
}

//
//	Gets the shape info for the given shape key. The shape infos are stored per sub-part in the case of extended mesh shapes.

HK_FORCE_INLINE hkUint16 hkpExtendedMeshShape::getShapeInfo(hkpShapeKey shapeKey) const
{
	const hkUint32 subpartIndex		= getSubPartIndex(shapeKey);
	const SubpartType subPartType	= getSubpartType(shapeKey);

	// Resolve PPU address
	const hkUlong arrayAddrPpu = ( subPartType == SUBPART_TRIANGLES ) ?	((hkUlong)m_trianglesSubparts.begin()	+ subpartIndex * sizeof(TrianglesSubpart)	):
																		((hkUlong)m_shapesSubparts.begin()		+ subpartIndex * sizeof(ShapesSubpart)		);
	const Subpart* subPart = reinterpret_cast<const Subpart*>(arrayAddrPpu);

	return subPart->m_shapeInfo;
}

//
//	Sets the shape info for the given shape key. The shape infos are stored per sub-part in the case of extended mesh shapes.

HK_FORCE_INLINE void hkpExtendedMeshShape::setShapeInfo(hkpShapeKey shapeKey, hkUint16 shapeInfo)
{
	const int subpartIndex = getSubPartIndex(shapeKey);
	if ( getSubpartType(shapeKey) == SUBPART_TRIANGLES )
	{
		m_trianglesSubparts[subpartIndex].m_shapeInfo = shapeInfo;
	}
	else
	{
		m_shapesSubparts[subpartIndex].m_shapeInfo = shapeInfo;
	}
}

HK_FORCE_INLINE hkInt32 hkpExtendedMeshShape::getSubpartShapeKeyBase( int subpartIndex ) const
{
	if ( subpartIndex < m_trianglesSubparts.getSize() )
	{
		return subpartIndex << ( 32 - m_numBitsForSubpartIndex );
	}

	int h = subpartIndex - m_trianglesSubparts.getSize();
	h =  h << ( 32 - m_numBitsForSubpartIndex );
	h |= 0x80000000;
	return h;
}


hkInt32 hkpExtendedMeshShape::getTerminalIndexInSubPart( hkpShapeKey key ) const
{
	hkInt32 terminalIndex = key & ( ~0U >> m_numBitsForSubpartIndex );
	return terminalIndex;
}

hkInt32 hkpExtendedMeshShape::getNumBitsForSubpartIndex() const
{
	return m_numBitsForSubpartIndex;
}

hkReal hkpExtendedMeshShape::getRadius() const
{
	return m_triangleRadius;
}

void hkpExtendedMeshShape::setRadius(hkReal r )
{
	m_triangleRadius = r;
}

//
//	Gets the subpart type

inline hkpExtendedMeshShape::SubpartType hkpExtendedMeshShape::Subpart::getType() const
{
	return (SubpartType)(m_typeAndFlags & SUBPART_TYPE_MASK);
}

//
//	Sets the subpart type

inline void hkpExtendedMeshShape::Subpart::setType(SubpartType newValue)
{
	m_typeAndFlags = (hkUint16)( (m_typeAndFlags & (~SUBPART_TYPE_MASK)) | (newValue & SUBPART_TYPE_MASK) );
}

//
//	Gets the material index striding type

inline hkpExtendedMeshShape::MaterialIndexStridingType hkpExtendedMeshShape::Subpart::getMaterialIndexStridingType() const
{
	return (MaterialIndexStridingType)(((hkUint32)m_typeAndFlags & SUBPART_MATERIAL_INDICES_MASK) >> SUBPART_MATERIAL_INDICES_SHIFT);
}

//
//	Sets the material index striding type

inline void hkpExtendedMeshShape::Subpart::setMaterialIndexStridingType(MaterialIndexStridingType newValue)
{
	m_typeAndFlags = (hkUint16)( (m_typeAndFlags & (~SUBPART_MATERIAL_INDICES_MASK)) | ((newValue << SUBPART_MATERIAL_INDICES_SHIFT) & SUBPART_MATERIAL_INDICES_MASK) );
}

//
//	Sets the number of materials

inline hkUint16 hkpExtendedMeshShape::Subpart::getNumMaterials() const
{
	return (hkUint16)( ((hkUint32)m_typeAndFlags & SUBPART_NUM_MATERIALS_MASK) >> SUBPART_NUM_MATERIALS_SHIFT );
}

//
//	Gets the number of materials

inline void hkpExtendedMeshShape::Subpart::setNumMaterials(hkUint16 newValue)
{
	m_typeAndFlags = (hkUint16)( (m_typeAndFlags & (~SUBPART_NUM_MATERIALS_MASK)) | ((newValue << SUBPART_NUM_MATERIALS_SHIFT) & SUBPART_NUM_MATERIALS_MASK) );
}

HK_FORCE_INLINE hkpExtendedMeshShape::Subpart::Subpart(SubpartType type)
{
	setType(type);
	setMaterialIndexStridingType(MATERIAL_INDICES_INT8);
	setNumMaterials(1);
	m_materialIndexStriding = 0;
	m_materialStriding		= 0;
	m_materialBase			= HK_NULL;
	m_materialIndexBase		= HK_NULL;
	m_shapeInfo				= 0;
	m_userData				= 0;
}

HK_FORCE_INLINE hkpExtendedMeshShape::TrianglesSubpart::TrianglesSubpart(): Subpart( SUBPART_TRIANGLES )
{
	m_flipAlternateTriangles = 0;
	m_extrusion.setZero();
	m_transform.setIdentity();

	// 'must set' values, defaults are error flags effectively for HK_ASSERTS in the cpp.
#ifdef HK_DEBUG
	m_vertexBase = HK_NULL;
	m_vertexStriding = 0;
	m_numVertices = -1;
	m_indexBase = HK_NULL;
	m_stridingType = INDICES_INVALID;
	m_indexStriding = 0;
	m_numTriangleShapes = -1;
	m_triangleOffset = -1;
#endif
}

HK_FORCE_INLINE void hkpExtendedMeshShape::TrianglesSubpart::setTranslation( hkVector4Parameter translation )
{
	m_transform.setTranslation( translation );
	HK_ON_DEBUG( hkVector4 t = m_transform.getTranslation(); t(3) = 1; m_transform.setTranslation(t) );
}

HK_FORCE_INLINE void hkpExtendedMeshShape::TrianglesSubpart::setRotation( hkQuaternionParameter rotation )
{
	if( !rotation.isOk() )
	{
		HK_WARN(0x5c431ca9, "Invalid rotation" );
		return;
	}
	m_transform.setRotation( rotation );
	HK_ON_DEBUG( hkVector4 t = m_transform.getTranslation(); t(3) = 1; m_transform.setTranslation(t) );
}

HK_FORCE_INLINE void hkpExtendedMeshShape::TrianglesSubpart::setScaling( hkVector4Parameter scaling )
{
	m_transform.setScale( scaling );
	HK_ON_DEBUG( hkVector4 t = m_transform.getTranslation(); t(3) = 1; m_transform.setTranslation(t) );
}

HK_FORCE_INLINE const hkVector4& hkpExtendedMeshShape::TrianglesSubpart::getTranslation() const
{
	return m_transform.getTranslation();
}

HK_FORCE_INLINE const hkQuaternion& hkpExtendedMeshShape::TrianglesSubpart::getRotation() const
{
	return m_transform.getRotation();
}

HK_FORCE_INLINE const hkVector4& hkpExtendedMeshShape::TrianglesSubpart::getScaling() const
{
	return m_transform.getScale();
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
