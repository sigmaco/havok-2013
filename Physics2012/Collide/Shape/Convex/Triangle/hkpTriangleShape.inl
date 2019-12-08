/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

hkUint16 hkpTriangleShape::getWeldingInfo() const
{
	return m_weldingInfo;

}

void hkpTriangleShape::setWeldingInfo( hkUint16 info )
{
	m_weldingInfo = info;
}

HK_FORCE_INLINE hkpWeldingUtility::WeldingType hkpTriangleShape::getWeldingType() const
{
	return m_weldingType;
}

HK_FORCE_INLINE void hkpTriangleShape::setWeldingType( hkpWeldingUtility::WeldingType type )
{
	m_weldingType = type;
}


HK_FORCE_INLINE hkpTriangleShape::hkpTriangleShape(hkReal radius, hkUint16 weldingInfo, hkpWeldingUtility::WeldingType type)
: hkpConvexShape( HKCD_SHAPE_TYPE_FROM_CLASS(hkpTriangleShape), radius)
{
	setWeldingInfo(weldingInfo);
	setWeldingType( type );
	m_extrusion.setZero();
	m_isExtruded = 0;
}

HK_FORCE_INLINE hkpTriangleShape::hkpTriangleShape(const hkVector4& v0, const hkVector4& v1, const hkVector4& v2, hkReal radius)
: hkpConvexShape(HKCD_SHAPE_TYPE_FROM_CLASS(hkpTriangleShape), radius)
{
	m_vertexA = v0;
	m_vertexB = v1;
	m_vertexC = v2;

	setWeldingInfo(0);
	setWeldingType(hkpWeldingUtility::WELDING_TYPE_NONE);
	m_extrusion.setZero();
	m_isExtruded = 0;
}


const hkVector4* hkpTriangleShape::getVertices() const
{
	return &m_vertexA;
}

hkVector4& hkpTriangleShape::getVertex(int i)
{
	HK_ASSERT2(0x312d54aa,  i>=0 && i < 3, "A triangle has only 3 vertices");
	return (&m_vertexA)[i];
}

const hkVector4& hkpTriangleShape::getVertex(int i) const
{
	HK_ASSERT2(0x7d790924,  i>=0 && i < 3, "A triangle has only 3 vertices");
	return (&m_vertexA)[i];
}

template <int I>
const hkVector4& hkpTriangleShape::getVertex() const
{
	HK_COMPILE_TIME_ASSERT((I>=0)&&(I<3));
	return (&m_vertexA)[I];
}

void hkpTriangleShape::setVertex(int i, const hkVector4& vertex)
{
	HK_ASSERT2(0x18d4155c,  i>=0 && i < 3, "A triangle has only 3 vertices");
	(&m_vertexA)[i] = vertex;
}

template <int I>
HK_FORCE_INLINE void hkpTriangleShape::setVertex(hkVector4Parameter vertex)
{
	HK_COMPILE_TIME_ASSERT((I>=0 && I < 3));
	(&m_vertexA)[I] = vertex;
}

bool hkpTriangleShape::isExtruded() const
{
	return (m_isExtruded != 0);
}

const hkVector4& hkpTriangleShape::getExtrusion() const
{
	return m_extrusion;
}

void hkpTriangleShape::setExtrusion( const hkVector4& extrusion )
{
	m_isExtruded = extrusion.lengthSquared<3>().isGreaterZero() ? 1 : 0;
	m_extrusion = extrusion;
}

//
//	Allocates a new triangle at the given memory location

inline hkpTriangleShape* HK_CALL hkpTriangleShape::createInPlace(	hkUint8*& memPtr,
																	hkReal convexRadius,
																	hkpWeldingUtility::WeldingType weldingType, hkUint16 weldingInfo)
{
	hkpTriangleShape* triangleShape;

	HK_CHECK_ALIGN_REAL(memPtr);
	triangleShape = new(memPtr) hkpTriangleShape(convexRadius, weldingInfo, weldingType);	
	HKCD_PATCH_SHAPE_VTABLE( triangleShape );

	// Increment memory location
	const int memSize = HK_NEXT_MULTIPLE_OF(HK_REAL_ALIGNMENT, sizeof(hkpTriangleShape));
	memPtr = hkAddByteOffset( memPtr, memSize );

	return triangleShape;
}

HK_FORCE_INLINE int hkpTriangleShape::getNumCollisionSpheres() const
{
	return 3 + m_isExtruded * 3;
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
