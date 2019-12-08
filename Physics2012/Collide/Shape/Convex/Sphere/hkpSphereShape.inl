/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#include <Common/Base/Types/Geometry/Sphere/hkSphere.h>

HK_FORCE_INLINE void hkpSphereShape::getSupportingVertex(hkVector4Parameter direction, hkcdVertex& supportingVertexOut) const
{
	supportingVertexOut.setZero();
}

HK_FORCE_INLINE void hkpSphereShape::convertVertexIdsToVertices(const hkpVertexId* ids, int numIds, hkcdVertex* verticesOut) const
{
	for (int i = numIds - 1; i >= 0; i--)
	{
		verticesOut[i].setZero();
	}
}

HK_FORCE_INLINE void hkpSphereShape::getCentre(hkVector4& centreOut) const
{
	centreOut.setZero();
}

HK_FORCE_INLINE int hkpSphereShape::getNumCollisionSpheres() const
{
	return 1;
}

HK_FORCE_INLINE void hkpSphereShape::getAabb(const hkTransform& localToWorld, hkReal tolerance, hkAabb& out) const
{
	hkVector4 tol4; tol4.setAll( tolerance + m_radius );

	out.m_min.setSub( localToWorld.getTranslation(), tol4 );
	out.m_max.setAdd( localToWorld.getTranslation(), tol4 );
}

HK_FORCE_INLINE const hkSphere* hkpSphereShape::getCollisionSpheres(hkSphere* sphereBuffer) const
{
	sphereBuffer->setPositionAndRadius(hkVector4::getZero(), hkSimdReal::fromFloat(m_radius));
	return sphereBuffer;
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
