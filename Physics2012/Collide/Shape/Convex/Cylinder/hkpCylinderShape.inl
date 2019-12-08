/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

HK_FORCE_INLINE hkpCylinderShape* hkpCylinderShape::createInPlace(	hkUint8*& memPtr,
																	const hkVector4& vertexA,
																	const hkVector4& vertexB,
																	hkReal cylinderRadius,
																	hkReal paddingRadius)
{
	hkpCylinderShape* shape;


	HK_CHECK_ALIGN_REAL(memPtr);
	shape = new(memPtr) hkpCylinderShape( vertexA, vertexB, cylinderRadius, paddingRadius );


	HKCD_PATCH_SHAPE_VTABLE( shape );

	// Increment memory location
	const int memSize = HK_NEXT_MULTIPLE_OF(HK_REAL_ALIGNMENT, sizeof(hkpCylinderShape));
	memPtr = hkAddByteOffset<hkUint8>( memPtr, memSize );

	// Return the shape
	return shape;
}

void hkpCylinderShape::setVertex(int i, const hkVector4& position )
{
	HK_ASSERT2(0x4d78b768,  i>=0 && i < 2, "A cylinder has only 2 vertices. getVertex() must be passed either 0 or 1. ");
	(&m_vertexA)[i] = position;
}

template <int I>
HK_FORCE_INLINE void hkpCylinderShape::setVertex(hkVector4Parameter position )
{
	HK_COMPILE_TIME_ASSERT((I>=0 && I < 2));
	(&m_vertexA)[I] = position;
}


const hkVector4* hkpCylinderShape::getVertices() const
{
	return &m_vertexA;
}

const hkVector4& hkpCylinderShape::getVertex(int i) const
{
	HK_ASSERT2(0x5e57e9fc,  i>=0 && i < 2, "A cylinder has only 2 vertices. getVertex() must be passed either 0 or 1. ");
	return (getVertices())[i];
}

template <int I>
HK_FORCE_INLINE const hkVector4& hkpCylinderShape::getVertex() const
{
	HK_COMPILE_TIME_ASSERT((I>=0 && I < 2));
	return (&m_vertexA)[I];
}

void hkpCylinderShape::initRoundUpThreshold()
{
	if (s_intRoundUpThreshold < 0.0f)
	{
		for (hkReal value = 0.0f; value < 1.1f; value += 0.01f)
		{
			int intValue = hkMath::hkToIntFast(value);
			HK_ASSERT2(0xad564bb4, (intValue & ~1) == 0, "Fast float-to-int conversion doesn't work as needed.");
			if ( intValue != 0 )
			{
				s_intRoundUpThreshold = 1.0f - value;
				return;
			}
		}

		HK_ASSERT2(0xad564bb4, false, "Fast float-to-int conversion doesn't work as needed.");
		s_intRoundUpThreshold = 0.0f;
	}
}

HK_FORCE_INLINE int hkpCylinderShape::getNumCollisionSpheres() const
{
	return  16 + 2;
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
