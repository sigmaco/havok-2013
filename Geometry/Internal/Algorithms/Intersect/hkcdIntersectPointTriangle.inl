/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#include <Common/Base/Math/Vector/hkVector4Util.h>


//
//	Tests whether the given point vP is inside the triangle (vA, vB, vC). The triangle normal is also required as input in vN.
//	On success (i.e. point in triangle), the function provides the barycentric coordinates if baryOut is not null.

HK_FORCE_INLINE hkBool32 HK_CALL hkcdIntersectPointTriangle(hkVector4Parameter vP,
											hkVector4Parameter vA, hkVector4Parameter vB, hkVector4Parameter vC,
											hkVector4Parameter vN,
											hkSimdRealParameter tolerance,
											hkVector4* HK_RESTRICT baryOut)
{
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

	// Output barycentric coords
	if ( baryOut )
	{
		// Barycentric coordinates need normalization.
		hkSimdReal baryInvSum;
		baryInvSum.setReciprocal(vDots.horizontalAdd<3>());
		baryOut->setMul(vDots, baryInvSum);
	}

	// vDots contains the un-normalized barycentric coordinates
	hkVector4 tolerance4; tolerance4.setAll(tolerance);
	return vDots.greater(tolerance4).allAreSet<hkVector4ComparisonMask::MASK_XYZ>();
}

//
//	Tests whether the given point vP is inside the triangle (vA, vB, vC).
//	On success (i.e. point in triangle), the function provides the barycentric coordinates if baryOut is not null.
HK_FORCE_INLINE hkBool32 HK_CALL hkcdIntersectPointTriangle(hkVector4Parameter vP,
											hkVector4Parameter vA, hkVector4Parameter vB, hkVector4Parameter vC, hkSimdRealParameter tolerance,
											hkVector4* HK_RESTRICT baryOut)
{
	// Compute the triangle normal
	hkVector4 vN;
	hkcdTriangleUtil::calcNonUnitNormal(vA, vB, vC, vN);

	// Call test with provided normal
	return hkcdIntersectPointTriangle(vP, vA, vB, vC, vN, tolerance, baryOut);
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
