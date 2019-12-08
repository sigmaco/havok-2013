/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#include <Common/Base/Math/Vector/hkVector4Util.h>

//
//	Method to calculate the (non-normalized) triangle normal.
//	Given the vertices, set normal to be the non-unit normal.
//		normal (Output) The normal of the triangle
//		a First vertex.
//		b Second vertex.
//		c Third vertex.

inline void HK_CALL hkcdTriangleUtil::calcUnitNormal(hkVector4Parameter vA, hkVector4Parameter vB, hkVector4Parameter vC, hkVector4& normal)
{
	hkVector4 vAB;	vAB.setSub(vB, vA);
	hkVector4 vAC;	vAC.setSub(vC, vA);
	hkVector4 vN;	vN.setCross(vAB, vAC);

	vN.normalize<3>();
	normal = vN;
}

//
//	Method to calculate the (non-normalized) triangle normal.
//	Given the vertices, set normal to be the non-unit normal.
//		normal (Output) The normal of the triangle
//		a First vertex.
//		b Second vertex.
//		c Third vertex.

inline void HK_CALL hkcdTriangleUtil::calcNonUnitNormal(hkVector4Parameter vA, hkVector4Parameter vB, hkVector4Parameter vC, hkVector4& normal)
{
	hkVector4 vAB;	vAB.setSub(vB, vA);
	hkVector4 vAC;	vAC.setSub(vC, vA);
	normal.setCross(vAB, vAC);
}

//
//	Computes the normalized plane equation from the three given vertices

inline void HK_CALL hkcdTriangleUtil::calcUnitPlaneEquation(hkVector4Parameter vA, hkVector4Parameter vB, hkVector4Parameter vC, hkVector4& planeOut)
{
	// Compute triangle normal
	hkVector4 vN;
	hkcdTriangleUtil::calcUnitNormal(vA, vB, vC, vN);

	// Compute and store plane offset in w
	planeOut.setXYZ_W(vN, -vN.dot<3>(vA));
}

//
//	Computes the unnormalized plane equation from the three given vertices

inline void HK_CALL hkcdTriangleUtil::calcNonUnitPlaneEquation(hkVector4Parameter vA, hkVector4Parameter vB, hkVector4Parameter vC, hkVector4& planeOut)
{
	// Compute triangle normal
	hkVector4 vN;
	hkcdTriangleUtil::calcNonUnitNormal(vA, vB, vC, vN);

	// Compute and store plane offset in w
	planeOut.setXYZ_W(vN, -vN.dot<3>(vA));
}

//
//	Computes twice the area of the given triangle

inline hkSimdReal HK_CALL hkcdTriangleUtil::calcDoubleArea(hkVector4Parameter vA, hkVector4Parameter vB, hkVector4Parameter vC)
{
	hkVector4 vAB;	vAB.setSub(vB, vA);
	hkVector4 vAC;	vAC.setSub(vC, vA);
	hkVector4 vN;	vN.setCross(vAB, vAC);
	return vN.length<3>();
}

//
//	Method to calculate the triangle centroid.
//	Given the vertices list, set the centroid to be the centroid of the three vertices.
//		centroid (output) The centroid of the triangle
//		a First vertex.
//		b Second vertex.
//		c Third vertex.

inline void HK_CALL hkcdTriangleUtil::calcCentroid(hkVector4Parameter a, hkVector4Parameter b, hkVector4Parameter c, hkVector4& centroid)
{
	centroid.setAdd(a, b);
	centroid.add(c);
	centroid.mul( hkSimdReal_Inv3);
}

//
//	Returns true if the point is in front of the Triangle.
//	Given the plane in which the triangle is embedded, the point is in front if (and only if)
//	the point is in the half space (defined by the plane) that the normal points into.
//		point The point to examine
//		a First vertex.
//		b Second vertex.
//		c Third vertex.

inline hkBool32 HK_CALL hkcdTriangleUtil::isPointInFront(hkVector4Parameter point, hkVector4Parameter a, hkVector4Parameter b, hkVector4Parameter c)
{
	hkVector4 triangleNormal;
	hkcdTriangleUtil::calcNonUnitNormal(a, b, c, triangleNormal);

	hkVector4 d;
	d.setSub(point, a);

	hkSimdReal dot = d.dot<3>(triangleNormal);

	return dot.isGreaterZero();
}

void HK_CALL hkcdTriangleUtil::calcBarycentricCoordinatesNonDegenerate(hkVector4Parameter vP, hkVector4Parameter vA, hkVector4Parameter vB, hkVector4Parameter vC, hkVector4& result)
{
	// If the triangle is non-degenerate, we should be able to return proper barycentric coordinates
	{
		// Compute the triangle normal
		hkVector4 vN;
		hkcdTriangleUtil::calcNonUnitNormal(vA, vB, vC, vN);

		// Determine whether the point is inside the triangle
		hkVector4 vDots;
		{
			hkVector4 vPA;	vPA.setSub(vA, vP);
			hkVector4 vPB;	vPB.setSub(vB, vP);
			hkVector4 vPC;	vPC.setSub(vC, vP);

			hkVector4 nPAB, nPBC, nPCA;
			hkVector4Util::cross_3vs1(vPB, vPC, vPA, vN, nPAB, nPBC, nPCA);
			hkVector4Util::dot3_3vs3(vPB, nPBC, vPC, nPCA, vPA, nPAB, vDots);
		}

		// Barycentric coordinates need normalization.
		// We can normalize the barycentric coordinates and exit!
		hkSimdReal barySum = vDots.horizontalAdd<3>();
		hkSimdReal baryInvSum;
		baryInvSum.setReciprocal<HK_ACC_23_BIT, HK_DIV_SET_ZERO>(barySum);
		result.setMul(vDots, baryInvSum);
		return;
	}
}


HK_FORCE_INLINE hkSimdReal hkcdTriangleUtil::calcConvexity( hkVector4Parameter normalA, hkVector4Parameter normalB, hkVector4Parameter edgePoint0, hkVector4Parameter edgePoint1 )
{
	hkVector4 edge; edge.setSub( edgePoint1, edgePoint0 );
	hkVector4 cross; cross.setCross( normalA, normalB );
	edge.normalize<3, HK_ACC_23_BIT, HK_SQRT_IGNORE>();
	return edge.dot<3>( cross );
}

//
//	END!
//

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
