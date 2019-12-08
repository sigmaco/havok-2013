/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */


inline void HK_CALL hkpTriangleUtil::calcNormal( hkVector4& normal, hkVector4Parameter a, hkVector4Parameter b, hkVector4Parameter c ) 
{
	hkcdTriangleUtil::calcNonUnitNormal(a, b, c, normal);
}

inline void HK_CALL hkpTriangleUtil::calcCentroid(hkVector4& centroid, hkVector4Parameter a, hkVector4Parameter b, hkVector4Parameter c) 
{
	hkcdTriangleUtil::calcCentroid(a, b, c, centroid);
}

inline bool HK_CALL hkpTriangleUtil::inFront(hkVector4Parameter point, hkVector4Parameter a, hkVector4Parameter b, hkVector4Parameter c) 
{
	return hkcdTriangleUtil::isPointInFront(point, a, b, c);
}

//
// Checks that a point is inside a triangle
// Assumes the point already lies in the plane of the triangle
//
inline bool HK_CALL hkpTriangleUtil::containsPoint(hkVector4Parameter pt, hkVector4Parameter a, hkVector4Parameter b, hkVector4Parameter c) 
{
	hkSimdReal zero; zero.setZero();
	return hkcdIntersectPointTriangle(pt, a, b, c, zero);
}

inline hkReal HK_CALL hkpTriangleUtil::dot3fullAcc(hkVector4Parameter a, hkVector4Parameter b)
{
	volatile hkReal p0 = a(0) * b(0);
	volatile hkReal p1 = a(1) * b(1);
	volatile hkReal p2 = a(2) * b(2);
	return p0 + p1 + p2;






}

inline bool HK_CALL hkpTriangleUtil::isDegenerate(hkVector4Parameter a, hkVector4Parameter b, hkVector4Parameter c, hkReal tolerance)
{
	hkSimdReal tol; tol.setFromFloat(tolerance);
	return hkcdTriangleUtil::isDegenerate(a, b, c, tol);
}

//
// Intersects a triangle with a plane

inline void HK_CALL hkpTriangleUtil::calcPlaneIntersection(hkVector4Parameter a, hkVector4Parameter b, hkVector4Parameter c, hkVector4Parameter plane, hkArray<hkVector4>& edgesOut, hkReal tolerance)
{
	HK_ALIGN_REAL(hkVector4) temp[6];
	hkSimdReal tol; tol.setFromFloat(tolerance);
	const int numEdges = hkcdTriangleUtil::clipWithPlane(a, b, c, plane, tol, temp);
	const int numVerts = numEdges << 1;

	hkVector4* dst = edgesOut.expandBy(numVerts);
	hkString::memCpy16(dst, temp, numVerts * (sizeof(hkVector4)>>4));
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
