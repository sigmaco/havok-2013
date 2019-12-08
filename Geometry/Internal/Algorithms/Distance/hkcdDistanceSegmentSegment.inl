/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#include <Geometry/Internal/Algorithms/ClosestPoint/hkcdClosestPointSegmentSegment.h>
HK_FORCE_INLINE hkSimdReal hkcdDistanceSegmentSegment(hkVector4Parameter A, hkVector4Parameter dA, hkVector4Parameter B, hkVector4Parameter dB)
{
	hkSimdReal t,u;
	hkcdClosestPointSegmentSegment(A,dA,B,dB, t,u);

	
	hkVector4 closestPointA; closestPointA.setAddMul( A, dA, t );
	hkVector4 closestPointB; closestPointB.setAddMul( B, dB, u );

	hkVector4 AminusB; AminusB.setSub( closestPointA, closestPointB );
	return AminusB.lengthSquared<3>();
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
