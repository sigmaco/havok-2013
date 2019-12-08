/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#include <Common/Base/Math/Vector/hkVector4Util.h>

//
//	Computes and returns the squared distance from vP to the triangle (vA, vB, vC). The normal and barycentric coordinates of the closest point on the triangle
//	are also provided on output.

inline hkSimdReal HK_CALL hkcdPointTriangleDistanceSquared(	hkVector4Parameter point,
															hkVector4Parameter vA, hkVector4Parameter vB, hkVector4Parameter vC,
															hkVector4* HK_RESTRICT normalOut, hkVector4* HK_RESTRICT baryOut)
{
	// Set point w component to 1 to compute the plane equation easier
	hkVector4 vP;	
	{
		hkSimdReal one = hkSimdReal::getConstant<HK_QUADREAL_1>();
		vP.setXYZ_W(point, one);
	}

	// Compute plane equation
	hkVector4 planeEq;
	hkVector4 normal;
	hkcdTriangleUtil::calcUnitPlaneEquation(vA, vB, vC, planeEq);

	// Closest point in triangle computation
	{
		// Compute projection of P (i.e. Q) on the triangle plane
		hkSimdReal distanceToPlane = planeEq.dot<4>(vP);
		hkVector4 vQ;
		vQ.setSubMul(vP, planeEq, distanceToPlane);

		// Set normal to triangle normal. Will be overwritten later if case
		normal.setFlipSign(planeEq, distanceToPlane);

		// Determine whether the point is inside the triangle
		hkSimdReal epsilon = hkSimdReal::getConstant<HK_QUADREAL_EPS>();
		if ( hkcdIntersectPointTriangle(vQ, vA, vB, vC, planeEq, epsilon, baryOut) )
		{
			*normalOut = normal;
			return distanceToPlane * distanceToPlane;
		}
	}

	// Closest point is on one of the edges
	{
		hkVector4 vAB;	vAB.setSub(vB, vA);
		hkVector4 vBC;	vBC.setSub(vC, vB);
		hkVector4 vCA;	vCA.setSub(vA, vC);

		hkVector4 vAP;	vAP.setSub(vP, vA);
		hkVector4 vBP;	vBP.setSub(vP, vB);
		hkVector4 vCP;	vCP.setSub(vP, vC);

		// Compute edge lengths
		hkVector4 vEdgeLen, vSegLen;
		hkVector4Util::dot3_3vs3(vAP, vAB, vBP, vBC, vCP, vCA, vSegLen);
		hkVector4Util::dot3_3vs3(vAB, vAB, vBC, vBC, vCA, vCA, vEdgeLen);

		// Prevent division by zero
		vEdgeLen.setMax(vEdgeLen, hkVector4::getConstant<HK_QUADREAL_EPS>());

		// Compute times of intersection
		hkVector4 vTois;
		{
			hkVector4 zero = hkVector4::getConstant<HK_QUADREAL_0>();
			hkVector4 one = hkVector4::getConstant<HK_QUADREAL_1>();
			vTois.setDiv(vSegLen, vEdgeLen);
			vTois.setClamped(vTois, zero, one);
		}

		// Compute normals & distances
		hkVector4 vDistances;
		HK_ALIGN_REAL(hkVector4) normals[3];
		{
			normals[0].setSubMul(vAP, vAB, vTois.getComponent<0>());
			normals[1].setSubMul(vBP, vBC, vTois.getComponent<1>());
			normals[2].setSubMul(vCP, vCA, vTois.getComponent<2>());

			hkVector4Util::dot3_3vs3(normals[0], normals[0], normals[1], normals[1], normals[2], normals[2], vDistances);
		}

		// Compute the index of the minimum length normal
		hkSimdReal minLen = vDistances.horizontalMin<3>();
		int bestIndex = vDistances.findComponent<3>(minLen);
		normal = normals[bestIndex];
	
		// Compute barycentric coords if required
		if ( baryOut )
		{
			hkVector4 vOne= hkVector4::getConstant<HK_QUADREAL_1>();

			hkVector4 b0;	b0.setSub(vOne, vTois);	// (u0, u1, u2, *)
			hkVector4 b1 = vTois;					// (v0, v1, v2, *)
			hkVector4 b2;	b2.setZero();			// (0, 0, 0, 0)

			// b0 = (u0, v0, 0, *)
			// b1 = (u1, v1, 0, *)
			// b2 = (u2, v2, 0, *)
			HK_TRANSPOSE3(b0, b1, b2);
			b1.setPermutation<hkVectorPermutation::ZXYZ>(b1);	// b1 = (0, u1, v1, 0)
			b2.setPermutation<hkVectorPermutation::YZXZ>(b2);	// b2 = (v2, 0, u2, 0)

			HK_ALIGN_REAL(hkVector4) bary[3] = { b0, b1, b2 };
			*baryOut = bary[bestIndex];
		}

		*normalOut = normal;
		return minLen;		
	}
}

//
HK_FORCE_INLINE hkBool32 HK_CALL hkcdPointTriangleProject(	hkVector4Parameter x,
														hkVector4Parameter a, hkVector4Parameter b, hkVector4Parameter c,
														hkVector4* HK_RESTRICT projectionOut, hkVector4* HK_RESTRICT normalOut)
{
	hkVector4	loBounds; loBounds.setXYZ_W(hkVector4::getConstant<HK_QUADREAL_0>(), hkSimdReal::getConstant<HK_QUADREAL_MINUS_MAX>());
	hkVector4	hiBounds; hiBounds.setXYZ_W(hkVector4::getConstant<HK_QUADREAL_1>(), hkSimdReal::getConstant<HK_QUADREAL_MAX>());
		
	hkVector4	ab; ab.setSub(b,a);
	hkVector4	bc; bc.setSub(c,b);
	hkVector4	ca; ca.setSub(a,c);
		
	hkVector4	ax; ax.setSub(x,a);
	hkVector4	bx; bx.setSub(x,b);
	hkVector4	cx; cx.setSub(x,c);

	hkVector4	n; n.setCross(ab,bc);
	
	hkVector4	cab; cab.setCross(ab, ax);
	hkVector4	cbc; cbc.setCross(bc, bx);
	hkVector4	cca; cca.setCross(ca, cx);
	
	hkVector4	signs; hkVector4Util::dot3_3vs3(n, cab, n, cbc, n, cca, signs);
	
	hkBool32 isInside;
	if(signs.greater(loBounds).allAreSet<hkVector4ComparisonMask::MASK_XYZ>())
	{
		hkSimdReal	sol; sol.setDiv<HK_ACC_12_BIT,HK_DIV_SET_ZERO>(n.dot<3>(ax), n.lengthSquared<3>());
		projectionOut->setSubMul(x, n, sol);
		isInside = true;
	}
	else
	{
		isInside = false;
		hkVector4	dens; hkVector4Util::dot3_3vs3(ab, ab, bc, bc, ca, ca, dens);
		hkVector4	nums; hkVector4Util::dot3_3vs3(ab, ax, bc, bx, ca, cx, nums);
		
		hkVector4	sols; sols.setDiv<HK_ACC_12_BIT,HK_DIV_SET_ZERO>(nums, dens);
		sols.setClamped(sols, loBounds, hiBounds);
		
		hkVector4	prj0, prj1, prj2;
		prj0.setSubMul(ax, ab, sols.getComponent<0>());
		prj1.setSubMul(bx, bc, sols.getComponent<1>());
		prj2.setSubMul(cx, ca, sols.getComponent<2>());

			// Find the projection vector with the smallest magnitude
		hkVector4 minProj = prj0;
		{
			hkVector4Comparison minProj_lt_prj1 = minProj.lengthSquared<3>().less(prj1.lengthSquared<3>() );
			minProj.setSelect( minProj_lt_prj1, minProj, prj1 );
		}
		{
			hkVector4Comparison minProj_lt_prj2 = minProj.lengthSquared<3>().less(prj2.lengthSquared<3>() );
			minProj.setSelect( minProj_lt_prj2, minProj, prj2 );
		}

		projectionOut->setSub(x, minProj);

	}

	if(normalOut)
	{
		*normalOut = n;
	}

	return isInside;
}

//
HK_FORCE_INLINE hkcdTriangleVoronoi::Region HK_CALL hkcdPointTriangleProjectWithVoronoi(	hkVector4Parameter x,
																			 hkVector4Parameter a, hkVector4Parameter b, hkVector4Parameter c,
																			 hkVector4* HK_RESTRICT projectionOut, hkVector4* HK_RESTRICT normalOut)
{
	hkVector4	loBounds; loBounds.setXYZ_W(hkVector4::getConstant<HK_QUADREAL_0>(), hkSimdReal::getConstant<HK_QUADREAL_MINUS_MAX>());
	hkVector4	hiBounds; hiBounds.setXYZ_W(hkVector4::getConstant<HK_QUADREAL_1>(), hkSimdReal::getConstant<HK_QUADREAL_MAX>());

	hkVector4	ab; ab.setSub(b,a);
	hkVector4	bc; bc.setSub(c,b);
	hkVector4	ca; ca.setSub(a,c);

	hkVector4	ax; ax.setSub(x,a);
	hkVector4	bx; bx.setSub(x,b);
	hkVector4	cx; cx.setSub(x,c);

	hkVector4	n; n.setCross(ab,bc);

	hkVector4	cab; cab.setCross(ab, ax);
	hkVector4	cbc; cbc.setCross(bc, bx);
	hkVector4	cca; cca.setCross(ca, cx);

	hkVector4	signs; hkVector4Util::dot3_3vs3(n, cab, n, cbc, n, cca, signs);

	hkcdTriangleVoronoi::Region	ret = hkcdTriangleVoronoi::INSIDE;

	if(signs.greater(loBounds).allAreSet<hkVector4ComparisonMask::MASK_XYZ>())
	{
		hkSimdReal	sol; sol.setDiv<HK_ACC_12_BIT,HK_DIV_SET_ZERO>(n.dot<3>(ax), n.lengthSquared<3>());
		projectionOut->setSubMul(x, n, sol);
	}
	else
	{
		hkVector4	dens; hkVector4Util::dot3_3vs3(ab, ab, bc, bc, ca, ca, dens);
		hkVector4	nums; hkVector4Util::dot3_3vs3(ab, ax, bc, bx, ca, cx, nums);

		hkVector4	sols; sols.setDiv<HK_ACC_12_BIT,HK_DIV_SET_ZERO>(nums, dens);
		sols.setClamped(sols, loBounds, hiBounds);

		hkVector4	prj[3];
		prj[0].setSubMul(ax, ab, sols.getComponent<0>());
		prj[1].setSubMul(bx, bc, sols.getComponent<1>());
		prj[2].setSubMul(cx, ca, sols.getComponent<2>());

		hkVector4	distancesSquared;
		hkVector4Util::dot3_3vs3(prj[0], prj[0], prj[1], prj[1], prj[2], prj[2], distancesSquared);

		static const hkcdTriangleVoronoi::Region regions[3][3] =
		{
			{ hkcdTriangleVoronoi::VERTEX_0 , hkcdTriangleVoronoi::EDGE_0 , hkcdTriangleVoronoi::VERTEX_1 } ,
			{ hkcdTriangleVoronoi::VERTEX_1 , hkcdTriangleVoronoi::EDGE_1 , hkcdTriangleVoronoi::VERTEX_2 } ,
			{ hkcdTriangleVoronoi::VERTEX_2 , hkcdTriangleVoronoi::EDGE_2 , hkcdTriangleVoronoi::VERTEX_0 }
		};

		const int			minDist = distancesSquared.getIndexOfMinComponent<3>();
		const hkSimdReal	sol = sols.getComponent(minDist);
		int					solRegion = 1;
		if(sol.isEqualZero())				--solRegion;
		else if(sol.isEqual(hkSimdReal_1))	++solRegion;

		projectionOut->setSub(x, prj[minDist]);

		ret = regions[minDist][solRegion];
	}

	if(normalOut)
	{
		*normalOut = n;
	}

	return ret;
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
