/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

//
//	Returns true if the given planes are coplanar (i.e. coincident)
//	Must compute all 2x2 determinants of:
//		| ax ay az aw |
//		| bx by bz bw |

HK_FORCE_INLINE hkcdPlanarGeometryPredicates::Coplanarity HK_CALL hkcdPlanarGeometryPredicates::coplanar(PlaneParam planeA, PlaneParam planeB)
{
	// All planes are fully simplified, so any two coplanar planes must match identically
	hkVector4d dEqnA;	dEqnA.setAbs(planeA.getApproxEquation());
	hkVector4d dEqnB;	dEqnB.setAbs(planeB.getApproxEquation());

	if ( dEqnA.equal(dEqnB).allAreSet() )
	{	
		// We can't be sure, check with exact arithmetic!
		// Check if the two planes are identical
		if ( planeA.isEqual(planeB) )
		{
			return COINCIDENT;
		} 

		// Check if the flipped plane is equal, in which case the two plane are still coplanar
		Plane flippedA; flippedA.setOpposite(planeA);
		if ( flippedA.isEqual(planeB) )
		{
			return OPPOSITE;
		}
	}

	// Approx normals are not equal
	return NOT_COPLANAR;
}

//
//	Tests for same orientation. Should be preceded by a coincident test

HK_FORCE_INLINE int HK_CALL hkcdPlanarGeometryPredicates::sameOrientation(PlaneParam planeA, PlaneParam planeB)
{
	const hkVector4d& dNrmA		= planeA.getApproxEquation();
	const hkVector4d& dNrmB		= planeB.getApproxEquation();
	hkSimdInt<128> iOffsetA;	planeA.getExactOffset(iOffsetA);
	hkSimdInt<128> iOffsetB;	planeB.getExactOffset(iOffsetB);

	hkVector4dComparison pA;	pA.setSelect<hkVector4Comparison::MASK_XYZ>(dNrmA.lessZero(),	iOffsetA.lessZero<hkVector4dComparison>());	// [ax < 0, ay < 0, az < 0, aw < 0]
	hkVector4dComparison nA;	nA.setSelect<hkVector4Comparison::MASK_XYZ>(dNrmA.equalZero(),	iOffsetA.equalZero<hkVector4dComparison>());// [ax == 0, ay == 0, az == 0, aw == 0]
								nA.setOr(nA, pA);												// [ax <= 0, ay <= 0, az <= 0, aw <= 0]
								pA.setNot(pA);													// [ax >= 0, ay >= 0, az >= 0, aw >= 0]

	hkVector4dComparison pB;	pB.setSelect<hkVector4Comparison::MASK_XYZ>(dNrmB.lessZero(),	iOffsetB.lessZero<hkVector4dComparison>());	// [bx < 0, by < 0, bz < 0, bw < 0]
	hkVector4dComparison nB;	nB.setSelect<hkVector4Comparison::MASK_XYZ>(dNrmB.equalZero(),	iOffsetB.equalZero<hkVector4dComparison>());// [bx == 0, by == 0, bz == 0, bw == 0]
								nB.setOr(nB, pB);												// [bx <= 0, by <= 0, bz <= 0, bw <= 0]
								pB.setNot(pB);													// [bx >= 0, by >= 0, bz >= 0, bw >= 0]
	
	hkVector4dComparison nAB;	nAB.setAnd(nA, nB);		// [ax, bx <= 0, ay, by <= 0, az, bz <= 0, aw, bw <= 0]
	hkVector4dComparison pAB;	pAB.setAnd(pA, pB);		// [ax, bx >= 0, ay, by >= 0, az, bz >= 0, aw, bw >= 0]
								pAB.setOr(nAB, pAB);	// [axbx >= 0, ayby >= 0, azbz >= 0, awbw >= 0]
	return pAB.allAreSet();
}

//
//	Computes the orientation of the point v with respect to the plane p

HK_FORCE_INLINE hkcdPlanarGeometryPredicates::Orientation HK_CALL hkcdPlanarGeometryPredicates::orientation(hkIntVectorParameter v, PlaneParam p)
{
	hkInt64Vector4 iN;	p.getExactNormal(iN);
	hkSimdInt<128> iO;	p.getExactOffset(iO);
	iO.setAdd(iO, iN.dot<3>(v));

	const hkVector4fComparison cmpLt = iO.lessZero();
	const hkVector4fComparison cmpEq = iO.equalZero();
	return cmpLt.anyIsSet() ? BEHIND : (cmpEq.anyIsSet() ? ON_PLANE : IN_FRONT_OF);
}

//
//	Approximates the intersection (i.e. in fixed coordinates) of the 3 given planes

HK_FORCE_INLINE void HK_CALL hkcdPlanarGeometryPredicates::approximateIntersection(const Plane (&planes)[3], hkIntVector& intersectionOut)
{
	hkSimdInt<256> detX, detY, detZ, detW;
	computeIntersectionDeterminants(planes, &detX, &detY, &detZ, &detW);

	// Divide by DW to get the points
	const int px = hkSimdInt<256>::computeDiv32(detX, detW);
	const int py = hkSimdInt<256>::computeDiv32(detY, detW);
	const int pz = hkSimdInt<256>::computeDiv32(detZ, detW);

	intersectionOut.set(px, py, pz, pz);
}

HK_FORCE_INLINE void HK_CALL hkcdPlanarGeometryPredicates::computeIntersectionDeterminants(ApproxPlaneEqnParam planeEqnA, ApproxPlaneEqnParam planeEqnB, ApproxPlaneEqnParam planeEqnC, ApproxPlaneEqn& determinantsOut)
{
	// Compute components
	hkVector4d xA, xB, temp;
	{
		xA.setPermutation<hkVectorPermutation::WYZX>(planeEqnA);	// [aw, ay, az]
		xB.setPermutation<hkVectorPermutation::WYZX>(planeEqnB);	// [bw, by, bz]
		temp.setPermutation<hkVectorPermutation::WYZX>(planeEqnC);	// [cw, cy, cz]
		xB.setCross(xB, temp);
	}
	hkVector4d yA, yB;
	{
		yA.setPermutation<hkVectorPermutation::XWZY>(planeEqnA);	// [ax, aw, az]
		yB.setPermutation<hkVectorPermutation::XWZY>(planeEqnB);	// [ay, bw, bz]
		temp.setPermutation<hkVectorPermutation::XWZY>(planeEqnC);	// [az, cw, cz]
		yB.setCross(yB, temp);
	}
	hkVector4d zA, zB;	
	{
		zA.setPermutation<hkVectorPermutation::XYWZ>(planeEqnA);	// [ax, ay, aw]
		zB.setPermutation<hkVectorPermutation::XYWZ>(planeEqnB);	// [ay, by, bw]
		temp.setPermutation<hkVectorPermutation::XYWZ>(planeEqnC);	// [az, cy, cw]
		zB.setCross(zB, temp);
	}

	temp.setCross(planeEqnB, planeEqnC);
	temp.set(xA.dot<3>(xB), yA.dot<3>(yB), zA.dot<3>(zB), planeEqnA.dot<3>(temp));
	hkVector4dComparison maskXYZ;	maskXYZ.set<hkVector4Comparison::MASK_XYZ>();
	determinantsOut.setFlipSign(temp, maskXYZ);
}

HK_FORCE_INLINE int HK_CALL hkcdPlanarGeometryPredicates::mulSigns(hkVector4dComparisonParameter negA, hkVector4dComparisonParameter zeroA, hkVector4dComparisonParameter negB, hkVector4dComparisonParameter zeroB)
{
	hkVector4dComparison posA;			posA.setOr(negA, zeroA);				// (a <= 0)
	hkVector4dComparison posB;			posB.setOr(negB, zeroB);				// (b <= 0)

	hkVector4dComparison negA_posB;		negA_posB.setAndNot(negA, posB);		// (a < 0) && (b > 0)
	hkVector4dComparison posA_negB;		posA_negB.setAndNot(negB, posA);		// (a > 0) && (b < 0)
	hkVector4dComparison negAB;			negAB.setOr(negA_posB, posA_negB);		// (ab < 0)
	hkVector4dComparison zeroAB;		zeroAB.setOr(zeroA, zeroB);				// (ab == 0)			

	return negAB.anyIsSet() ? -1 : (zeroAB.anyIsSet() ? 0 : 1);
}

//
//	Computes the orientation of the point (ptPlaneA, ptPlaneB, ptPlaneC) with respect to the planeD

HK_FORCE_INLINE hkcdPlanarGeometryPredicates::Orientation HK_CALL hkcdPlanarGeometryPredicates::approximateOrientation(PlaneParam ptPlaneA, PlaneParam ptPlaneB, PlaneParam ptPlaneC, PlaneParam planeD)
{
	HK_ON_DEBUG(m_numApproxCalls++);

	const ApproxPlaneEqn fEqnA	= ptPlaneA.getApproxEquation();
	const ApproxPlaneEqn fEqnB	= ptPlaneB.getApproxEquation();
	const ApproxPlaneEqn fEqnC	= ptPlaneC.getApproxEquation();
	const ApproxPlaneEqn fEqnD	= planeD.getApproxEquation();

	hkVector4d nAB;		nAB.setCross(fEqnA, fEqnB);
	hkVector4d nBC;		nBC.setCross(fEqnB, fEqnC);
	hkVector4d nCD;		nCD.setCross(fEqnC, fEqnD);
	hkVector4d nA;		nA.setMul(fEqnB.getComponent<3>(),	fEqnA);
						nA.subMul(fEqnA.getComponent<3>(),	fEqnB);
	hkVector4d nC;		nC.setMul(fEqnD.getComponent<3>(),	fEqnC);
						nC.subMul(fEqnC.getComponent<3>(),	fEqnD);


	const hkSimdDouble64 detLeft	= nAB.dot<3>(nC);
	const hkSimdDouble64 detRight	= nCD.dot<3>(nA);
	const hkSimdDouble64 det3		= nBC.dot<3>(fEqnA);
	hkSimdDouble64 det4;			det4.setAdd(detLeft, detRight);

	// Check signs, return proper orientation
	{
		const int sign = mulSigns(det3.lessZero(), det3.equalZero(), det4.lessZero(), det4.equalZero());
		return (sign < 0) ? BEHIND : ((sign > 0) ? IN_FRONT_OF : ON_PLANE);
	}
}

//
//	Computes the winding of the 3 given vertices w.r.t. the given triangle normal.

HK_FORCE_INLINE hkcdPlanarGeometryPredicates::Winding HK_CALL hkcdPlanarGeometryPredicates::triangleWinding(const Plane (&planesA)[3], const Plane (&planesB)[3], const Plane (&planesC)[3], PlaneParam supportPlane)
{
	// Project everything on a single plane, as it will be much easier to compute the exact stuff. Pick the largest component of the normal as the projection plane
	int axisX, axisY, axisZ;
	{
		hkInt64Vector4 absN;	supportPlane.getExactNormal(absN);
								absN.setAbs(absN);
		axisZ	= absN.getIndexOfMaxComponent<3>();
		axisX	= ((1 << axisZ) & 3);
		axisY	= ((1 << axisX) & 3);
	}

	// Use floating point first
	HK_ON_DEBUG(m_numApproxCalls++);
	const Winding winding = estimateTriangleWinding(planesA, planesB, planesC, supportPlane, axisX, axisY, axisZ);
	if ( winding != WINDING_UNKNOWN )
	{
		return winding;
	}

	HK_ON_DEBUG(m_numExactCalls++);
	return computeExactTriangleWinding(planesA, planesB, planesC, supportPlane, axisX, axisY, axisZ);
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
