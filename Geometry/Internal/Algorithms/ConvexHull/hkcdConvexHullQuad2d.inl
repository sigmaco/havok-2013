/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

//
//	Computes the 2D convex hull of the 4 given vertices. The vertices are assumed to lie into the same plane. Returns the indices of the vertices on the convex hull
//	in remapOut.

HK_FORCE_INLINE void HK_CALL hkcdConvexHullQuad2d(const hkVector4* HK_RESTRICT vSrc, int remapOut[4])
{
	// Compute the source verts' Aabb
	hkAabb aabb;	aabb.setEmpty();
	aabb.includePoint(vSrc[0]);	aabb.includePoint(vSrc[1]);	aabb.includePoint(vSrc[2]);	aabb.includePoint(vSrc[3]);

	// Remap such that the first two vertices are furthest apart
	int remap[4] = { 0, 1, 2, 3 };
	{
		hkVector4 vExtents;			aabb.getExtents(vExtents);
		hkVector4 vMaxExtent;		vMaxExtent.setAll(vExtents.horizontalMax<3>());
		hkVector4Comparison cmp;	cmp.set<hkVector4ComparisonMask::MASK_XYZ>();
		cmp.setAnd(cmp, vExtents.greaterEqual(vMaxExtent));
		const int maxDispersionAxis	= cmp.getIndexOfFirstComponentSet();

		// Transpose points to get the maximum dispersed coordinates
		hkVector4 vCoords;
		{
			hkFourTransposedPoints pts;
			pts.set(vSrc[0], vSrc[1], vSrc[2], vSrc[3]);
			vCoords = pts.m_vertices[maxDispersionAxis];
		}

		// Get indices of the min and max points on the maximum dispersion axis
		hkVector4 coordMin;	coordMin.setAll(vCoords.horizontalMin<4>());
		hkVector4 coordMax;	coordMax.setAll(vCoords.horizontalMax<4>());
		const int idxA = vCoords.lessEqual(coordMin).getIndexOfFirstComponentSet();
		const int idxB = vCoords.greaterEqual(coordMax).getIndexOfLastComponentSet();

		// Compute the other two indices
		const int idxCD = 0xF & (~((1 << idxA) | (1 << idxB)));
		remap[0] = idxA;
		remap[1] = idxB;
		remap[2] = 31 - hkMath::countLeadingZeros(idxCD);
		remap[3] = hkMath::countTrailingZeros(idxCD);
	}

	// Compute third vertex as furthest apart from the first 2
	const hkVector4 vA	= vSrc[remap[0]];
	const hkVector4 vB	= vSrc[remap[1]];
	hkVector4 vAB;		vAB.setSub(vB, vA);
	{
		// Compute a perpendicular vector
		hkVector4 vPerp;	hkVector4Util::calculatePerpendicularVector(vAB, vPerp);

		// Pick the furthest point along this vector
		hkVector4 vC;		vC.setSub(vSrc[remap[2]], vA);	vC.setInt24W(remap[2]);
		hkVector4 vD;		vD.setSub(vSrc[remap[3]], vA);	vD.setInt24W(remap[3]);
		hkSimdReal dotC;	dotC.setAbs(vC.dot<3>(vPerp));
		hkSimdReal dotD;	dotD.setAbs(vD.dot<3>(vPerp));

		const hkVector4Comparison cmp = dotC.greater(dotD);
		hkVector4 newC;		newC.setSelect(cmp, vC, vD);
		hkVector4 newD;		newD.setSelect(cmp, vD, vC);
		remap[2] = newC.getInt24W();
		remap[3] = newD.getInt24W();
	}

	// Last vertex
	{
		const hkVector4 vC = vSrc[remap[2]];
		const hkVector4 vD = vSrc[remap[3]];

		// Compute edges
		hkVector4 vBC, vCA;				vBC.setSub(vC, vB);		vCA.setSub(vA, vC);
		hkVector4 vAD, vBD, vCD;		vAD.setSub(vD, vA);		vBD.setSub(vD, vB);		vCD.setSub(vD, vC);

		// Triangle normals
		hkVector4 vN;					vN.setCross(vCA, vAB);												// N = AB x AC
		hkVector4 vABD, vBCD, vCAD;		hkVector4Util::cross_3vs1(vAD, vBD, vCD, vN, vABD, vBCD, vCAD);		//	AD x N, BD x N, CD x N

		// Compute the Voronoi region of D w.r.t. ABC
		//	dots.x		dots.y		dots.z	Mask	| Hull
		//	+			+			+		0		|	ABCC
		//	-			+			+		1		|	ADBC
		//	+			-			+		2		|	ABDC
		//	-			-			+		3		|	ADCC
		//	+			+			-		4		|	ABCD
		//	-			+			-		5		|	DBCC
		//	+			-			-		6		|	ABDD
		//	-			-			-		7		|	ABCC
		hkVector4 vDots; hkVector4Util::dot3_3vs3(vAB, vABD, vBC, vBCD, vCA, vCAD, vDots);

		const int cmpMask = (vDots.lessZero().getMask() & 7) << 1;
		remapOut[0] = remap[(0x0C00 >> cmpMask) & 3];
		remapOut[1] = remap[(0x55DD >> cmpMask) & 3];
		remapOut[2] = remap[(0xBAB6 >> cmpMask) & 3];
		remapOut[3] = remap[(0xBBAA >> cmpMask) & 3];
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
