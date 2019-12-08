/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

//
//	Returns the squared distance between a point and a convex quad assumed to have proper winding.

HK_FORCE_INLINE	const hkSimdReal HK_CALL hkcdPointConvexQuadDistanceSquared(hkVector4Parameter vP, hkVector4Parameter quadVtx0, hkVector4Parameter quadVtx1, hkVector4Parameter quadVtx2, hkVector4Parameter quadVtx3,
																			hkVector4Parameter quadNormalIn, hkVector4* HK_RESTRICT projectionOut)
{
	// Get points
	hkFourTransposedPoints vABCD;		vABCD.set(quadVtx0, quadVtx1, quadVtx2, quadVtx3);
	hkFourTransposedPoints edges;		edges.setPermutation<hkVectorPermutation::YZWX>(vABCD);
	hkFourTransposedPoints p;			p.setAll(vP);

	// Compute edges
	edges.setSub(edges, vABCD);	// = [AB, BC, CD, DA]
	p.setSub(p, vABCD);			// = [AP, BP, CP, DP]

	// Compute normals
	hkFourTransposedPoints normals;		normals.setCross(p, quadNormalIn);
	hkVector4 vDots;					normals.dot3(edges, vDots);
	if ( vDots.lessEqualZero().anyIsSet() )
	{
		// Compute distances from all edges and points
		hkVector4 pointDistSq;	p.dot3(p, pointDistSq);														// = [AP, BP, CP, DP] ^ 2
		hkVector4 edgeLenSq;	edges.dot3(edges, edgeLenSq);												// = [AB, BC, CD, DA] ^ 2
		hkVector4 proj;			p.dot3(edges, proj);														// = [AP.AB, BP.BC, CP.CD, DP.DA]
		hkVector4 invEdgeLenSq;	invEdgeLenSq.setReciprocal<HK_ACC_23_BIT, HK_DIV_SET_ZERO>(edgeLenSq);		// = 1 / / [AB, BC, CD, DA] ^ 2
		hkVector4 tEdge;		tEdge.setMul(proj, invEdgeLenSq);											// = [AP.AB / AB^2, BP.BC / BC^2, CP.CD / CD^2, DP.DA / DA^2]
		tEdge.setMax(tEdge, hkVector4::getConstant<HK_QUADREAL_0>());										// Clamp intersection points to edge borders
		tEdge.setMin(tEdge, hkVector4::getConstant<HK_QUADREAL_1>());

		// Compute edge intersection points
		p.subMulT(edges, tEdge);	// = [AP - (AP.AB / AB^2) * AB, ...]
		hkVector4 edgeDistSq;	p.dot3(p, edgeDistSq);

		// Pick minimum distance. If the point distance is less than the edge distance starting from the same point, set the intersection time to 0.
		tEdge.zeroIfTrue(pointDistSq.less(edgeDistSq));
		edgeDistSq.setMin(pointDistSq, edgeDistSq);

		// Compute intersection points
		vABCD.addMulT(edges, tEdge);

		// Minimum distance is on edge [i, i+1], where i is the index of the minimum component of edgeDistSq
		if ( projectionOut )
		{
			const int idx = edgeDistSq.getIndexOfMinComponent<4>();
			vABCD.extract(idx, *projectionOut);
		}

		// Return distance
		return edgeDistSq.horizontalMin<4>();	
	}

	// Point inside quad, return zero
	if ( projectionOut )
	{
		*projectionOut = vP;
	}
	
	return hkSimdReal_0;
}

HK_FORCE_INLINE	const hkSimdReal HK_CALL hkcdPointConvexQuadDistanceSquared(hkVector4Parameter vP, const hkVector4* HK_RESTRICT quadVertsIn, hkVector4Parameter quadNormalIn, hkVector4* HK_RESTRICT projectionOut)
{
	return hkcdPointConvexQuadDistanceSquared(vP, quadVertsIn[0], quadVertsIn[1], quadVertsIn[2], quadVertsIn[3], quadNormalIn, projectionOut);
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
