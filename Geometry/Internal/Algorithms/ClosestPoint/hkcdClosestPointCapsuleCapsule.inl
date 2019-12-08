/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#include <Common/Base/Math/Vector/hkVector4Util.h>


HK_FORCE_INLINE hkResult hkcdClosestPointCapsuleCapsule(hkVector4Parameter capsA0, hkVector4Parameter capsA1, hkSimdRealParameter capsARadius, 
														hkVector4Parameter capsB0, hkVector4Parameter capsB1, hkSimdRealParameter capsBRadius, 
														hkSimdRealParameter collisionTolerance, hkVector4* HK_RESTRICT pointOut, hkVector4* HK_RESTRICT normalOut)
{
	hkVector4 dA; dA.setSub( capsA1, capsA0 );
	hkVector4 dB; dB.setSub( capsB1, capsB0 );

	hkVector4 closestPointA;
	hkVector4 closestAminusClosestB;
	hkSimdReal distanceSquared;
	hkcdClosestPointSegmentSegment( capsA0, dA, capsB0, dB, closestPointA, closestAminusClosestB, distanceSquared );

	// Early out if separating distance is larger than threshold
	const hkSimdReal radiusSum = capsARadius + capsBRadius;
	const hkSimdReal refDist = collisionTolerance + radiusSum;
	if ( distanceSquared.isGreater( refDist * refDist ) )
	{
		return HK_FAILURE;
	}

	const hkSimdReal dist = distanceSquared.sqrt();

	// Determine the normal
	hkVector4 normal;
	if ( distanceSquared.isGreaterZero() )
	{
		// Simply use the vector between the closest segment points.
		normal = closestAminusClosestB;
	}
	else
	{
		// We cannot use the vector between the closest segment points as the normal since they are the same point.
		hkVector4 altNormal; altNormal.setCross( dA, dB );
		const hkSimdReal altNormLengthSquared = altNormal.lengthSquared<3>();
		const hkSimdReal epsilon = hkSimdReal::getConstant<HK_QUADREAL_EPS>();
		if ( altNormLengthSquared.isGreater(epsilon) )
		{
			// The segments intersect but are not parallel, use the cross product of the capsule directions as the normal.
			const hkSimdReal dot = altNormal.dot<3>( closestAminusClosestB );
			normal.setFlipSign(altNormal, dot.lessZero());
		}
		else
		{
			// The segments almost coincide, any normal to their common direction will do.
			hkVector4Util::calculatePerpendicularVector( dA, normal );
		}
	}

	normal.normalize<3>();
	normal.setComponent<3>( dist - radiusSum );
	hkVector4 point; point.setAddMul( closestPointA, normal, capsBRadius - dist );
	*normalOut = normal;
	*pointOut = point;

	return HK_SUCCESS;
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
