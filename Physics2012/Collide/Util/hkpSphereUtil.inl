/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#include <Physics2012/Collide/Util/hkpSphereUtil.h>
#include <Geometry/Internal/Algorithms/RayCast/hkcdRayCastSphere.h>


HK_FORCE_INLINE hkBool hkpRayCastSphere(hkVector4Parameter rayFrom, hkVector4Parameter rayTo, hkReal radius, hkpShapeRayCastOutput& results)
{
	// Adapt the parameters for calling hkcdRayCastSphere.
	hkcdRay ray; ray.setEndPoints(rayFrom, rayTo);
	hkVector4 spherePosRadius; spherePosRadius.setXYZ_W(hkVector4::getZero(), hkSimdReal::fromFloat(radius));
	hkSimdReal hitFraction; hitFraction.load<1>( (const hkReal*)&(results.m_hitFraction) );

	if(hkcdRayCastSphere(ray, spherePosRadius, &hitFraction, &results.m_normal, hkcdRayQueryFlags::NO_FLAGS))
	{
		hitFraction.store<1>( (hkReal*)&(results.m_hitFraction) );
		results.setKey(HK_INVALID_SHAPE_KEY);
		return true;
	}

	return false;
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
