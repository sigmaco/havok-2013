/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

HK_FORCE_INLINE void hkcdClosestPointSegmentSegment(hkVector4Parameter A, hkVector4Parameter dA, hkVector4Parameter B, hkVector4Parameter dB, 
														 hkSimdReal& tOut, hkSimdReal& uOut)
{
	hkVector4 d12; d12.setSub(B,A);

	
	hkSimdReal R = dA.dot<3>(dB);
	hkSimdReal S1 = dA.dot<3>(d12);
	hkSimdReal S2 = dB.dot<3>(d12);
	const hkSimdReal D1 = dA.lengthSquared<3>();
	const hkSimdReal D2 = dB.lengthSquared<3>();

	const hkSimdReal zero = hkSimdReal::getConstant<HK_QUADREAL_0>();
	const hkSimdReal eps = hkSimdReal::getConstant<HK_QUADREAL_EPS>();

	// denom == 0 means lines are parallel
	// denom always >= 0 by triangle inequality
	hkSimdReal denom = D1 * D2 - R * R;
	denom.setMax(denom, eps); // avoid divide by zero

	hkSimdReal invDenom; invDenom.setReciprocal(denom);
	hkSimdReal invD2; invD2.setReciprocal(D2);
	hkSimdReal invD1; invD1.setReciprocal(D1);

	// find the closest point on infinite line A to the infinite line B
	hkSimdReal t;
	{
		t = (S1 * D2 - S2 * R);
		t.setClamped(t, zero, denom);
		t.mul( invDenom ); // use invDenom as late as possible
	}

	// By convention, if the segments are parallel (i.e. denom == 0 <= eps) we choose t = 1. This is how the previous version worked.
	const hkSimdReal one = hkSimdReal::getConstant<HK_QUADREAL_1>();
	t.setSelect(denom.lessEqual(eps), one, t);

	// find the closest point on B to the point we just found
	hkSimdReal u;
	{
		u = t * (invD2*R) - (invD2*S2);	// invD2 is already available earlier, multiple the factors instead of u
		u.setClamped(u, zero, one);
	}

	// if the point on B was clamped, we may need to update the point on A
	{
		t = u * (invD1*R) + (invD1*S1);	// invD1 is already available earlier, multiple the factors instead of t
		t.setClamped(t, zero, one);
	}
	uOut = u;
	tOut = t;
}

HK_FORCE_INLINE hkVector4Comparison hkcdClosestPointSegmentSegment(hkVector4Parameter A, hkVector4Parameter dA, hkVector4Parameter B, hkVector4Parameter dB, 
															hkVector4& closestPointAout, hkVector4& closestAminusClosestBout, hkSimdReal& distanceSquaredOut)
{
	hkSimdReal t,u;
	hkcdClosestPointSegmentSegment(A,dA,B,dB, t,u);

	hkVector4 closestPointA; closestPointA.setAddMul( A, dA, t );
	hkVector4 closestPointB; closestPointB.setAddMul( B, dB, u );

	hkVector4 AminusB; AminusB.setSub( closestPointA, closestPointB );


	hkVector4 ttuu; ttuu.set(t,t,u,u);
	hkVector4 c1010 = hkVector4::getConstant<HK_QUADREAL_1010>();

	closestPointAout = closestPointA;
	closestAminusClosestBout = AminusB;
	distanceSquaredOut = AminusB.lengthSquared<3>();

	return ttuu.equal(c1010);
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
