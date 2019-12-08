/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

//
//	Intersects a line segment with a cylinder. Returns 1 if the segment intersects the cylinder,
//	and 0 otherwise.
//	Let the cylinder be defined by the vertices P -> Q. Let the ray be defined by vertices A -> B.
//	A valid intersection point must project between P and Q

HK_FORCE_INLINE hkBool32 HK_CALL hkcdRayCastCylinder(
	const hkcdRay& ray,
	hkVector4Parameter vP,
	hkVector4Parameter vQ,
	hkSimdRealParameter radius,
	hkSimdReal* HK_RESTRICT fractionInOut,
	hkVector4* HK_RESTRICT normalOut)
{
	// Compute the normalized cylinder direction, u
	hkVector4 u;
	u.setSub(vQ, vP);
	u.normalize<3>();
	hkVector4 normal;
	
	// Compute the intersection time limits first, defined by the cylinder end-caps
	hkSimdReal t0, t1;
	hkVector4Comparison capPHitFirst;
	{
		const hkVector4 vA = ray.m_origin;		// A = start of the ray
		const hkVector4 vAB = ray.getDirection();	// AB = B - A, B = end of the ray
		hkVector4 vPA;	vPA.setSub(vA, vP);		// PA = A - P
		hkVector4 vQA;	vQA.setSub(vA, vQ);		// QA = A - Q

		// Compute the 3 dots, i.e. (PA * u, QA * u, AB * u)
		hkVector4 vDots;
		hkVector4Util::dot3_3vs3(vPA, u, vQA, u, vAB, u, vDots);

		// Compare the dots with zero
		t0 = vDots.getComponent<0>();
		t1 = vDots.getComponent<1>();
		hkSimdReal dotABu = vDots.getComponent<2>(); // AB * u

		// If (AB * u == 0), the cylinder is perpendicular to the ray. We have an intersection only if the ray falls inside the two caps.
		hkSimdReal invDotABu;	invDotABu.setReciprocal<HK_ACC_23_BIT,HK_DIV_SET_HIGH>(dotABu); // Prevent division by zero

		// if (AB * u == 0) then t0 = sign(vPA * u) * Infinity, else t0 = vPA * u / dotABu
		// tmp0 and tmp1 will be the intersection times in case the ray is perpendicular to the cylinder.
		// If both A and B are on the same side of a cap, tmp0 = tmp1 = either + / - Infinity, and will result in no intersection
		hkSimdReal tmp0 = hkSimdReal_Max;
		hkSimdReal tmp1 = tmp0;
		tmp0.setFlipSign(tmp0, t0);
		tmp1.setFlipSign(tmp1, t1);
		hkVector4Comparison cmpPerpendicular = dotABu.equalZero();
		tmp0.setSelect(cmpPerpendicular, tmp0, -t0 * invDotABu);
		tmp1.setSelect(cmpPerpendicular, tmp1, -t1 * invDotABu);

		t0.setMin(tmp0, tmp1);
		t1.setMax(tmp0, tmp1);

		if ( t0.isEqual(t1) )
		{
			return false;	// The intersection times coincide, no intersection!
		}

		// Store normal. tmp0 comes from the back cap (i.e. normal = -u), tmp1 from the top cap (i.e. normal = u)
		capPHitFirst = tmp0.less(tmp1);
		normal.setFlipSign(u, capPHitFirst);
	}

	// We need to intersect with the infinite cylinder. The intersection times will have to fall inside [t0, t1]
	hkSimdReal t2, t3;
	{
		const hkVector4 vA = ray.m_origin;
		const hkVector4 vAB = ray.getDirection();
		hkVector4 vPA; vPA.setSub(vA, vP);

		// Compute all dots
		hkVector4 vDots;
		hkVector4Util::dot3_4vs4(	vAB, vAB,
									vAB, u,
									vAB, vPA,
									vPA, u, vDots);

		// Compute the factors of the quadratic equation
		const hkSimdReal AB_AB	= vDots.getComponent<0>();
		const hkSimdReal ABu	= vDots.getComponent<1>();
		const hkSimdReal AB_PA	= vDots.getComponent<2>();
		const hkSimdReal PAu	= vDots.getComponent<3>();
		const hkSimdReal PA_PA	= vPA.dot<3>(vPA);
		hkSimdReal a = AB_AB - ABu * ABu;
		hkSimdReal b = AB_PA - PAu * ABu;
		hkSimdReal c = PA_PA - PAu * PAu - radius * radius;

		// In theory, when the ray is inside the infinite cylinder and parallel to it, then the 
		// discriminant of the quadratic is exactly zero.
		// Because of limited precision, we might actually end up with a negative (tiny) discriminant
		// in this case.
		// Therefore, to avoid missing certain obvious end cap intersections, it is always better
		// for parallel rays, to check end cap intersection  and ignore the discriminant.
		//
		// The trade-off is that when the ray is considered parallel (hkSimdReal_Eps) but the ignored 
		// discriminant would have provided 2 valid intersections, we are always choosing the end cap intersection 
		// and ignoring the possibly earlier infinite cylinder intersection that is extremely close to it.

		
		// Handle the case where the cylinder is parallel to the ray.
		if ( a.isLess(hkSimdReal_Eps) )
		{
			// Check that a cap is actually hit
			hkVector4 hitPoint; hitPoint.setAddMul(vA, vAB, t0);
			hkVector4 closestCapPoint; closestCapPoint.setSelect(capPHitFirst, vP, vQ);
			hkSimdReal distToCapCenter = hitPoint.distanceToSquared(closestCapPoint);
			if ( distToCapCenter.isGreater(radius*radius) )
			{
				return false;
			}
			t2 = -hkSimdReal_Max;
			t3 = hkSimdReal_Max;
		}
		else
		{
			// Compute discriminant. If less than zero, we have no intersection!
			hkSimdReal delta = b * b - a * c;
			if ( delta.isLessZero() ) 
			{
				return false;
			}
			else
			{
				delta = delta.sqrt();
				a.setReciprocal(a);

				// Compute entry and exit times. For any t in [t2, t3], the distance between a point on the ray and the cylinder axis <= R.
				hkSimdReal tmp2 = -(delta + b) * a;
				hkSimdReal tmp3 = (delta - b) * a;
				t2.setMin(tmp2, tmp3);
				t3.setMax(tmp2, tmp3);

				// Compute cylinder normal at t2
				{
					hkVector4 vX;	vX.setAddMul(vA, vAB, t2);		// X = intersection point on ray / cylinder
					hkVector4 vPX;	vPX.setSub(vX, vP);				// PX = from cylinder start to X
					hkVector4 vPX0;	vPX0.setMul(vPX.dot<3>(u), u);	// PX projected on cylinder axis
					hkVector4 vX0X;	vX0X.setSub(vPX, vPX0);			// normal vector in X, unnormalized
					vX0X.normalize<3>();

					// Select proper output normal
					normal.setSelect(t0.greater(t2), normal, vX0X);
				}
			}
		}
	}

	// Finally, compute tEntry and tExit
	hkSimdReal fEntry, fExit;
	fEntry.setMax(t0, t2);
	fExit.setMin(t1, t3);

	// And test for valid intersection
	{
		hkSimdReal fraction = *fractionInOut;
		hkVector4Comparison cmp0 = fEntry.lessEqual(fExit);		// (tEntry <= tExit)
		hkVector4Comparison cmp1 = fEntry.greaterEqualZero();	// (tEntry >= 0)
		hkVector4Comparison cmp2 = fEntry.less(fraction);	// (tEntry <= rayLength)
		cmp0.setAnd(cmp0, cmp1);
		cmp0.setAnd(cmp0, cmp2);

		fractionInOut->setSelect(cmp0, fEntry, fraction);
		*normalOut = normal;
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
