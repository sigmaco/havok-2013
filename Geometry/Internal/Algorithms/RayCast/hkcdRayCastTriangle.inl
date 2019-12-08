/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#include <Common/Base/Math/Vector/hkVector4Util.h>

//
//	Intersects a line segment with a triangle. Returns 1 if the segment intersects the triangle,
//	and 0 otherwise.

inline hkBool32 HK_CALL hkcdSegmentTriangleIntersect(
	const hkcdRay& ray,
	hkVector4Parameter vA, hkVector4Parameter vB, hkVector4Parameter vC,
	hkSimdRealParameter tolerance, hkVector4& normalOut, hkSimdReal& fractionInOut)
{
	hkVector4Comparison cmpPQ;
	hkVector4 vN;
	{
		hkVector4 vAB;	vAB.setSub(vB, vA);
		hkVector4 vAC;	vAC.setSub(vC, vA);
		hkVector4 vAP;	vAP.setSub(ray.m_origin, vA);
		vN.setCross(vAB, vAC);

		const hkSimdReal distAP		= vN.dot<3>(vAP);				// dist_a
		const hkSimdReal projLen	= vN.dot<3>(ray.getDirection());	// dist_a - dist_b
		const hkSimdReal distAQ		= distAP + projLen;				// dist_b
		const hkSimdReal distance	= -(distAP / projLen);			// distance

		// cmpPQ = (dist_a * dist_b >= 0.0f) && ( (dist_a != 0.0f) || (dist_b == 0.0f) )
		cmpPQ.setOr(distAP.notEqualZero(), distAQ.equalZero());
		cmpPQ.setAnd((distAP * distAQ).greaterEqualZero(), cmpPQ);

		// cmpPQ = (distance < fractionInOut) && ( (dist_a * dist_b < 0.0f) || ( (dist_a == 0.0f) && (dist_b != 0.0f) ) )
		cmpPQ.setAndNot(distance.less(fractionInOut), cmpPQ);

		// Early exit
		if ( !cmpPQ.anyIsSet() )
		{
			return false;
		}

		// Set proper sign for the normal
		fractionInOut = distance;
		normalOut.setFlipSign(vN, distAP);
	}

	hkVector4 vDots;
	{
		// Compute intersection point
		hkVector4 vI;	vI.setAddMul(ray.m_origin, ray.getDirection(), fractionInOut);

		// Test whether the intersection point is inside the triangle
		hkVector4 vIA;	vIA.setSub(vA, vI);
		hkVector4 vIB;	vIB.setSub(vB, vI);
		hkVector4 vIC;	vIC.setSub(vC, vI);

		hkVector4 nIAB;	nIAB.setCross(vIA, vIB);
		hkVector4 nIBC;	nIBC.setCross(vIB, vIC);
		hkVector4 nICA;	nICA.setCross(vIC, vIA);

		hkVector4Util::dot3_1vs4(vN, nIAB, nIBC, nICA, vN, vDots);
	}

	// Decide whether we have an intersection or not
	{
		// Normalize normal
		const hkSimdReal squaredNormalLen = vDots.getComponent<3>();
		normalOut.mul(squaredNormalLen.sqrtInverse());

		hkVector4 edgeTol;	edgeTol.setAll(-squaredNormalLen * tolerance);

		hkVector4Comparison cmp0;
		cmp0.setAnd(vDots.greaterEqual(edgeTol), cmpPQ);
		return cmp0.allAreSet<hkVector4ComparisonMask::MASK_XYZ>();
	}
}



//
//	Helper function for segment bundle intersect. Returns (B - I) * (n x (A - I))

inline static void hkcdHelperEdgeDots(
	hkVector4Parameter vA, hkVector4Parameter vB, const hkFourTransposedPoints& vI, hkVector4Parameter vN,
	hkVector4& vDotsOut )
{
	hkFourTransposedPoints vAI, vBI;

	vAI.setSub(vI, vA);			// (I - A)
	vAI.setCross(vN, vAI);		// n x (I - A)
	vBI.setSub(vI, vB);			// (I - B)

	vBI.dot3(vAI, vDotsOut);	// (I - B) * (n x (I - A)) = (B - I) * (n x (A - I)) = n * ((A - I) x (B - I))
}

//
//	Intersects a ray bundle with the triangle.

inline hkVector4Comparison HK_CALL hkcdSegmentBundleTriangleIntersect(
	const hkcdRayBundle& rayBundle,
	hkVector4Parameter vA, hkVector4Parameter vB, hkVector4Parameter vC,
	hkSimdRealParameter tolerance, hkFourTransposedPoints& normalsOut, hkVector4& fractionsInOut )
{
	const hkFourTransposedPoints& vStart	= rayBundle.m_start;
	hkFourTransposedPoints vDir;	rayBundle.getDirection(vDir);

	hkVector4Comparison cmpPQ;
	hkVector4 vN, distAP;
	hkVector4 distance;
	{
		hkVector4 vAB;	vAB.setSub(vB, vA);
		hkVector4 vAC;	vAC.setSub(vC, vA);
		vN.setCross(vAB, vAC);

		hkFourTransposedPoints vAP;
		vAP.setSub(vStart, vA);

		vAP.dot3(vN, distAP);									// dist_a
		hkVector4 projLen;	vDir.dot3(vN, projLen);				// dist_b - dist_a
		hkVector4 distAQ;	distAQ.setAdd(distAP, projLen);		// dist_b
		distance.setDiv(distAP, projLen);
		distance.setNeg<4>(distance);							// distance

		// cmpPQ = (dist_a * dist_b >= 0.0f) && ( (dist_a != 0.0f) || (dist_b == 0.0f) )
		cmpPQ.setOr(distAP.notEqualZero(), distAQ.equalZero());

		distAQ.mul(distAP);
		cmpPQ.setAnd(distAQ.greaterEqualZero(), cmpPQ);

		// cmpPQ = (distance < fractionInOut) && ( (dist_a * dist_b < 0.0f) || ( (dist_a == 0.0f) && (dist_b != 0.0f) ) )
		cmpPQ.setAndNot(distance.less(fractionsInOut), cmpPQ);
		cmpPQ.setAnd(cmpPQ, rayBundle.m_activeRays);

		// Early exit
		if ( !cmpPQ.anyIsSet() )
		{
			return cmpPQ;
		}
	}

	// Get normal length and compute a tolerance
	const hkSimdReal normalLengthSquared = vN.lengthSquared<3>();
	hkVector4 edgeTol;
	edgeTol.setAll(-normalLengthSquared * tolerance);

	// Decide whether we have a valid intersection
	{
		// Compute intersection point
		hkFourTransposedPoints vI;
		vI.setAddMulT(vStart, vDir, distance);

		// Test for point I inside edge AB
		{
			hkVector4 vDotsAB;
			hkcdHelperEdgeDots(vA, vB, vI, vN, vDotsAB);
			cmpPQ.setAnd(cmpPQ, vDotsAB.greaterEqual(edgeTol));
		}

		// Test for point I inside edge BC
		{
			hkVector4 vDotsBC;
			hkcdHelperEdgeDots(vB, vC, vI, vN, vDotsBC);
			cmpPQ.setAnd(cmpPQ, vDotsBC.greaterEqual(edgeTol));
		}

		// Test for point I inside edge CA
		{
			hkVector4 vDotsCA;
			hkcdHelperEdgeDots(vC, vA, vI, vN, vDotsCA);
			cmpPQ.setAnd(cmpPQ, vDotsCA.greaterEqual(edgeTol));
		}
	}

	// Output fractions
	fractionsInOut.setSelect(cmpPQ, distance, fractionsInOut);

	// Output normals
	{
		vN.normalize<3>();

		hkFourTransposedPoints allNormals;
		allNormals.setAll(vN);

		// Set proper signs
		allNormals.flipSigns(distAP);

		// Select only colliding normals in the output
		normalsOut.setSelect(cmpPQ, allNormals, normalsOut);
	}

	return cmpPQ;
}

//
//	Returns true and the fraction if the ray intersect the triangle between 0 and fractionInOut.


HK_FORCE_INLINE hkBool32 HK_CALL hkcdSegmentTriangleIntersect(
	const hkcdRay& ray, hkVector4Parameter vA, hkVector4Parameter vB, hkVector4Parameter vC,
	hkVector4& nonUnitNormalOut, hkSimdReal& fractionInOut )
{
	{
		hkVector4 vAB;	vAB.setSub(vB, vA);	// v01
		hkVector4 vCA;	vCA.setSub(vA, vC);	// v20

		hkVector4 vN;   vN.setCross(vAB, vCA);
		hkVector4 vAP;	vAP.setSub(ray.m_origin, vA);
		hkVector4 end0;  end0.setAddMul(vAP, ray.getDirection(), fractionInOut);

		hkSimdReal d  = vN.dot<3>( vAP );
		hkSimdReal e  = vN.dot<3>( end0 );
		
		if ( (d*e).isSignBitClear() )
		{
			return 0;
		}

		hkSimdReal fraction = d / (d-e);	// calculate the fraction here so that the compiler can get rid of d and e

		hkVector4 vBP;	vBP.setSub(ray.m_origin, vB);
		hkVector4 vCP;	vCP.setSub(ray.m_origin, vC);
		hkVector4 vBC;	vBC.setSub(vC, vB);	// v12

		hkVector4 c0;	c0.setCross(vAP, ray.getDirection());
		hkVector4 c1;	c1.setCross(vBP, ray.getDirection());
		hkVector4 c2;	c2.setCross(vCP, ray.getDirection());

		hkSimdReal d0 = c0.dot<3>(vAB);
		hkSimdReal d1 = c1.dot<3>(vBC);
		hkSimdReal d2 = c2.dot<3>(vCA);

		if ( (d0*d1).isSignBitSet() | (d1*d2).isSignBitSet() )
		{
			return 0;
		}

		// now we are sure to have a hit
		fractionInOut = fraction * fractionInOut;
		nonUnitNormalOut = vN;
		
		return 1;
	}
}

HK_FORCE_INLINE void hkcdSortVerticesDeterministically(
	hkVector4Parameter va, hkVector4Parameter vb, hkVector4Comparison* cmpOut )
{
	extern hkChar hkcdSortVerticesDeterministicallyTable[];
	hkVector4Comparison equal   = va.equal( vb );
	hkVector4Comparison greater = va.greater( vb );
	hkVector4Comparison::Mask me = equal.getMask();
	hkVector4Comparison::Mask mg = greater.getMask();
	cmpOut->set( hkVector4ComparisonMask::Mask(hkcdSortVerticesDeterministicallyTable[me<<4 | mg]) );
}


HK_FORCE_INLINE hkBool32 HK_CALL hkcdSegmentTriangleIntersectImprovedAccuracy(
	const hkcdRay& ray, hkVector4Parameter vA, hkVector4Parameter vB, hkVector4Parameter vC,
	hkVector4& nonUnitNormalOut, hkSimdReal& fractionInOut)
{
	{
		hkVector4 vAB;	vAB.setSub(vB, vA);	// v01
		hkVector4 vCA;	vCA.setSub(vA, vC);	// v20

		hkVector4 vN;   vN.setCross(vAB, vCA);
		hkVector4 vAP;	vAP.setSub(ray.m_origin, vA);
		hkVector4 end0;  end0.setAddMul(vAP, ray.getDirection(), fractionInOut);

		hkSimdReal d  = vN.dot<3>( vAP );
		hkSimdReal e  = vN.dot<3>( end0 );

		if ( (d*e).isSignBitClear() )
		{
			return 0;
		}

		hkSimdReal fraction = d / (d-e);	// calculate the fraction here so that the compiler can get rid of d and e

		// sort edges

		//edge0;
		hkVector4Comparison e0c; hkcdSortVerticesDeterministically( vA, vB, &e0c );
		hkVector4 e0A; e0A.setSelect( e0c, vA, vB );

		hkVector4Comparison e1c; hkcdSortVerticesDeterministically( vB, vC, &e1c );
		hkVector4 e1A; e1A.setSelect( e1c, vB, vC );

		hkVector4Comparison e2c; hkcdSortVerticesDeterministically( vC, vA, &e2c );
		hkVector4 e2A; e2A.setSelect( e2c, vC, vA );
		hkVector4 vBC;	vBC.setSub(vC, vB);	// v12

		hkVector4 v0P; v0P.setSub( ray.m_origin, e0A );
		hkVector4 v1P; v1P.setSub( ray.m_origin, e1A );
		hkVector4 v2P; v2P.setSub( ray.m_origin, e2A );

		hkVector4 c0; c0.setCross( v0P, ray.getDirection() );
		hkVector4 c1; c1.setCross( v1P, ray.getDirection() );
		hkVector4 c2; c2.setCross( v2P, ray.getDirection() );


		hkSimdReal d0 = c0.dot<3>(vAB);
		hkSimdReal d1 = c1.dot<3>(vBC);
		hkSimdReal d2 = c2.dot<3>(vCA);

		if ( (d0*d1).isSignBitSet() | (d1*d2).isSignBitSet() )
		{
			return 0;
		}

		// now we are sure to have a hit
		fractionInOut = fraction * fractionInOut;
		nonUnitNormalOut = vN;

		return 1;
	}
}

//
HK_FORCE_INLINE hkInt32 hkcdRayTriangleIntersect(
	const hkcdRay& ray, const hkVector4& a, const hkVector4& b, const hkVector4& c,
	hkSimdReal* HK_RESTRICT fractionOut, hkVector4* HK_RESTRICT normalOut,
	hkcdRayQueryFlags::Enum flags )
{
	hkVector4	org; org.setSub(ray.m_origin, a);
	hkVector4	ab; ab.setSub(b,a);
	hkVector4	ac; ac.setSub(c,a);
	hkVector4	n; n.setCross(ab,ac);
	hkSimdReal	den = n.dot<3>(ray.getDirection());

	if((den * den) < hkSimdReal_Eps) return 0;
	if((flags & hkcdRayQueryFlags::DISABLE_BACK_FACING_TRIANGLE_HITS) && den.isSignBitClear()) return 0;
	if((flags & hkcdRayQueryFlags::DISABLE_FRONT_FACING_TRIANGLE_HITS) && den.isSignBitSet()) return 0;

	hkSimdReal	num = n.dot<3>(org);
	hkSimdReal	fraction = - num / den;
	if((den * num).isSignBitSet() && fraction < ray.getFraction())
	{
		hkVector4	impact; impact.setAddMul(org, ray.getDirection(), fraction);
		hkVector4	epsilon; epsilon.setAll(-2.e-4f); epsilon.mul(n.lengthSquared<3>()); // use faster length
		hkVector4	ab0; ab0.setSub(ab, impact);
		hkVector4	ac0; ac0.setSub(ac, impact);
		hkVector4	c0; c0.setCross(ab0, ac0);
		hkVector4	c1; c1.setCross(ab, impact);
		hkVector4	c2; c2.setCross(impact, ac);
		hkVector4	dots; hkVector4Util::dot3_3vs3(c0,n, c1,n, c2,n, dots);
		if(dots.greaterEqual(epsilon).allAreSet<hkVector4ComparisonMask::MASK_XYZ>())
		{
			if(fractionOut)
			{
				*fractionOut = fraction;
			}
			if(normalOut)
			{
				normalOut->setFlipSign( n, den.signBitClear() );
			}
			return hkcdRayCastResult::createOutsideHit();
		}
	}
	return hkcdRayCastResult::createMiss();
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
