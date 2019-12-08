/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

//
//	Intersects a line segment with a box. Returns 1 if the segment intersects the triangle,
//	and 0 otherwise.

inline hkBool32 HK_CALL hkcdRayCastBox(
	const hkcdRay& ray,
	hkVector4Parameter vHalfExtents,
	hkSimdReal* HK_RESTRICT fractionInOut,
	hkVector4* HK_RESTRICT normalOut)
{
	// Let A and B be the start and end of the ray
	hkVector4 vA = ray.m_origin;
	hkVector4 vAB = ray.getDirection();
	hkVector4 vB;	ray.getEndPoint(vB);
	{
		hkVector4 negHalfExtents;	negHalfExtents.setNeg<3>(vHalfExtents);
		const hkVector4Comparison cmpRayStartOutR = vHalfExtents.lessEqual(vA);		// rayStart is exterior, to the right
		const hkVector4Comparison cmpRayStartOutL = vA.lessEqual(negHalfExtents);	// rayStart is exterior, to the left
		hkVector4Comparison cmpRayOutR;	cmpRayOutR.setAnd(	cmpRayStartOutR,
															vHalfExtents.lessEqual(vB));		// ray is completely exterior, to the right
		hkVector4Comparison cmpRayOutL;	cmpRayOutL.setAnd(	cmpRayStartOutL,
															vB.lessEqual(negHalfExtents));	// ray is completely exterior, to the left

		hkVector4Comparison cmpRayOut;		cmpRayOut.setOr(cmpRayOutL, cmpRayOutR);					// ray is outside either on the left or on the right
		hkVector4Comparison cmpRayStartOut;	cmpRayStartOut.setOr(cmpRayStartOutL, cmpRayStartOutR);		// ray start is exterior

		if ( cmpRayOut.anyIsSet<hkVector4ComparisonMask::MASK_XYZ>() ||		// Ray is outside, no intersection!
			 !cmpRayStartOut.anyIsSet<hkVector4ComparisonMask::MASK_XYZ>()	// Ray start is completely inside, no intersection!
			)
		{
			return false;
		}
	}

	// Intersection times (for all 3 slabs) are given by:
	//		T1 = -(halfExtents + vA) / vAB
	//		T2 = +(halfExtents - vA) / vAB
	// where the division is component-wise.
	hkSimdReal fEntry, fExit;
	{
		hkVector4 T1;	T1.setAdd(vHalfExtents, vA);
		hkVector4 T2;	T2.setSub(vHalfExtents, vA);
		hkVector4Comparison cmp0 = vAB.notEqualZero();

		// Prevent division by zero and invert
		vAB.setSelect(cmp0, vAB, hkVector4::getConstant<HK_QUADREAL_EPS>());
		vAB.setReciprocal(vAB);
		T1.mul(vAB);
		T2.mul(vAB);
		T1.setNeg<4>(T1);

		// Pick minimum time as entry time and maximum time as exit time
		hkVector4 tEntry, tExit;
		tEntry.setMin(T1, T2);
		tExit.setMax(T1, T2);

		// Select only the intersection times for the slabs not parallel to the ray direction
		hkVector4 tFar = hkVector4::getConstant<HK_QUADREAL_MAX>();
		hkVector4 tNear = hkVector4::getConstant<HK_QUADREAL_MINUS_MAX>();
		tNear.setSelect(cmp0, tEntry, tNear);
		tFar.setSelect(cmp0, tExit, tFar);

		fEntry = tNear.horizontalMax<3>();
		fExit = tFar.horizontalMin<3>();

		// T1 comes from the "negative" planes, the normal sign will have to be negated if the entry time comes from T1
		int normalIndex = tNear.findComponent<3>(fEntry);
		normalOut->setFlipSign(hkVector4::getConstant((hkVectorConstant)(HK_QUADREAL_1000 + normalIndex)), T1.less(T2));
	}

	// Determine whether we have an intersection
	{
		hkVector4Comparison cmp0 = fEntry.lessEqual(fExit);		// (tEntry <= tExit)
		hkVector4Comparison cmp1 = fEntry.greaterEqualZero();	// (tEntry >= 0)
		hkVector4Comparison cmp2 = fEntry.less(*fractionInOut);	// (tEntry <= rayLength)
		cmp0.setAnd(cmp0, cmp1);
		cmp0.setAnd(cmp0, cmp2);

		fractionInOut->setSelect(cmp0, fEntry, *fractionInOut);
		return cmp0.anyIsSet();
	}
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
