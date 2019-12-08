/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */


static HK_FORCE_INLINE hkSimdReal hkVector4UtilInternal::surfaceArea(const hkAabb& aabb)
{
	hkVector4 l,u;
	l.setSub(aabb.m_max,aabb.m_min);
	u.setPermutation<hkVectorPermutation::YZXW>(l);
	return l.dot<3>(u);
}

//
#ifndef HK_VECTOR4UTIL_INTERNAL_overlaps6
HK_FORCE_INLINE hkBool32 hkVector4UtilInternal::overlaps6(const hkAabb& aabbA, const hkAabb& aabbB, const hkTransform& BtoA, const hkTransform& AtoB)
{	
	hkVector4	centerA;	centerA.setAdd(aabbA.m_min, aabbA.m_max);
	hkVector4	lengthA;	lengthA.setSub(aabbA.m_max, aabbA.m_min);	

	hkSimdReal half = hkSimdReal::getConstant<HK_QUADREAL_INV_2>();
	centerA.mul(half);	lengthA.mul(half);	

	hkVector4	heXA; heXA.setMul( lengthA.getComponent<0>(), AtoB.getColumn<0>() );
	hkVector4	heYA; heYA.setMul( lengthA.getComponent<1>(), AtoB.getColumn<1>() );
	hkVector4	heZA; heZA.setMul( lengthA.getComponent<2>(), AtoB.getColumn<2>() );
	heXA.setAbs(heXA);	heYA.setAbs(heYA);	heZA.setAbs(heZA);

	hkVector4	maxAinB;	maxAinB.setAdd(heXA,heYA);	maxAinB.add(heZA);

	hkVector4	centerAinB;	centerAinB._setTransformedPos(AtoB, centerA);
	hkVector4	minAinB;	minAinB.setNeg<4>(maxAinB);

	maxAinB.add(centerAinB);	minAinB.add(centerAinB);

	hkVector4Comparison mincompB = minAinB.greater(aabbB.m_max);
	hkVector4Comparison maxcompB = aabbB.m_min.greater(maxAinB);
	hkVector4Comparison compB; compB.setOr(mincompB, maxcompB);

	if(compB.anyIsSet<hkVector4ComparisonMask::MASK_XYZ>())
	{
		return 0;
	}

	hkVector4	centerB;	centerB.setAdd(aabbB.m_min, aabbB.m_max);
	hkVector4	lengthB;	lengthB.setSub(aabbB.m_max, aabbB.m_min);

	centerB.mul(half);	lengthB.mul(half);

	hkVector4	heXB; heXB.setMul(lengthB.getComponent<0>(), BtoA.getColumn<0>());
	hkVector4	heYB; heYB.setMul(lengthB.getComponent<1>(), BtoA.getColumn<1>());
	hkVector4	heZB; heZB.setMul(lengthB.getComponent<2>(), BtoA.getColumn<2>());
	heXB.setAbs(heXB);	heYB.setAbs(heYB);	heZB.setAbs(heZB);

	hkVector4	maxBinA;	maxBinA.setAdd(heXB,heYB); maxBinA.add(heZB);

	hkVector4	centerBinA;	centerBinA._setTransformedPos(BtoA, centerB);
	hkVector4	minBinA;	minBinA.setNeg<4>(maxBinA);

	maxBinA.add(centerBinA);	minBinA.add(centerBinA);

	hkVector4Comparison mincompA = minBinA.lessEqual(aabbA.m_max);
	hkVector4Comparison maxcompA = aabbA.m_min.lessEqual(maxBinA);
	hkVector4Comparison compA; compA.setAnd(mincompA, maxcompA);

	return compA.allAreSet<hkVector4ComparisonMask::MASK_XYZ>();
}
#endif

#ifndef HK_VECTOR4UTIL_INTERNAL_intersectRay
HK_FORCE_INLINE hkBool32 hkVector4UtilInternal::intersectRay(const hkAabb& aabb, hkVector4Parameter rayInvDir, hkSimdRealParameter maxFraction)
{
	hkVector4 dNearTemp;	dNearTemp.setMul(aabb.m_min, rayInvDir);
	hkVector4 dFarTemp;		dFarTemp.setMul(aabb.m_max, rayInvDir);

	hkVector4 dNear;		dNear.setMin(dNearTemp, dFarTemp);
	hkVector4 dFar;			dFar.setMax(dNearTemp, dFarTemp);

#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED) && !defined(HK_REAL_IS_DOUBLE)
	hkVector4 dNearY;		dNearY.setBroadcast<1>(dNear);
	hkVector4 dNearZ;		dNearZ.setBroadcast<2>(dNear);
	hkVector4 dFarY;		dFarY.setBroadcast<1>(dFar);
	hkVector4 dFarZ;		dFarZ.setBroadcast<2>(dFar);

	hkVector4	mf3;		mf3.setAll(maxFraction);
	hkVector4	nearYZ;		nearYZ.setMax(dNearY, dNearZ);
	hkVector4	farYZ;		farYZ.setMin(dFarY, dFarZ);
	hkVector4	nearX;		nearX.setMax(dNear, hkVector4::getZero());
	hkVector4	farX;		farX.setMin(dFar, mf3);

	nearX.setMax(nearX, nearYZ);
	farX.setMin(farX, farYZ);

	return nearX.lessEqual(farX).anyIsSet<hkVector4ComparisonMask::MASK_X>();
#else
	const hkSimdReal nearest = dNear.horizontalMax<3>();
	const hkSimdReal farthest = dFar.horizontalMin<3>();

	hkSimdReal nearClamped; nearClamped.setMax(nearest, hkSimdReal_0);
	hkSimdReal farClamped;  farClamped.setMin(farthest, maxFraction);

	return nearClamped.isLessEqual(farClamped);
#endif
}

HK_FORCE_INLINE hkBool32 hkVector4UtilInternal::intersectRay(const hkAabb& aabb, hkVector4Parameter rayOrg, hkVector4Parameter rayInvDir, hkSimdRealParameter maxFraction)
{
	hkVector4 dNearTemp;	dNearTemp.setSub(aabb.m_min, rayOrg);
	hkVector4 dFarTemp;		dFarTemp.setSub(aabb.m_max, rayOrg);

	dNearTemp.mul(rayInvDir);
	dFarTemp.mul(rayInvDir);

	hkVector4 dNear;		dNear.setMin(dNearTemp, dFarTemp);
	hkVector4 dFar;			dFar.setMax(dNearTemp, dFarTemp);

#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED) && !defined(HK_REAL_IS_DOUBLE)
	hkVector4 dNearY;		dNearY.setBroadcast<1>(dNear);
	hkVector4 dNearZ;		dNearZ.setBroadcast<2>(dNear);
	hkVector4 dFarY;		dFarY.setBroadcast<1>(dFar);
	hkVector4 dFarZ;		dFarZ.setBroadcast<2>(dFar);

	hkVector4	mf3;		mf3.setAll(maxFraction);
	hkVector4	nearYZ;		nearYZ.setMax(dNearY, dNearZ);
	hkVector4	farYZ;		farYZ.setMin(dFarY, dFarZ);
	hkVector4	nearX;		nearX.setMax(dNear, hkVector4::getZero());
	hkVector4	farX;		farX.setMin(dFar, mf3);

	nearX.setMax(nearX, nearYZ);
	farX.setMin(farX, farYZ);

	return nearX.lessEqual(farX).anyIsSet<hkVector4ComparisonMask::MASK_X>();
#else
	const hkSimdReal nearest = dNear.horizontalMax<3>();
	const hkSimdReal farthest = dFar.horizontalMin<3>();

	hkSimdReal nearClamped; nearClamped.setMax(nearest, hkSimdReal_0);
	hkSimdReal farClamped;  farClamped.setMin(farthest, maxFraction);

	return nearClamped.isLessEqual(farClamped);
#endif
}
#endif

HK_FORCE_INLINE hkVector4Comparison hkVector4UtilInternal::intersectRayBundle(const hkAabb& aabb, const hkFourTransposedPoints& rayOrg, const hkFourTransposedPoints& rayInvDir, hkVector4Parameter maxFraction)
{
	hkVector4 zero; zero.setZero();

	hkFourTransposedPoints dNearTemp;
	dNearTemp.setSub( aabb.m_min, rayOrg);

	hkFourTransposedPoints dFarTemp;
	dFarTemp.setSub(aabb.m_max, rayOrg);

	dNearTemp.mul( rayInvDir );
	dFarTemp.mul( rayInvDir );

	hkFourTransposedPoints dNear, dFar;
	dNear.setMin( dNearTemp, dFarTemp );
	dFar .setMax( dNearTemp, dFarTemp );

	
	hkVector4 vNear;
	dNear.horizontalMax(vNear);
	vNear.setMax(vNear, zero);

	hkVector4 vFar;
	dFar.horizontalMin(vFar);
	vFar.setMin(maxFraction, vFar);

	return vNear.lessEqual(vFar);
}

//

#ifndef HK_VECTOR4UTIL_INTERNAL_computeRayInverseDirection
HK_FORCE_INLINE void hkVector4UtilInternal::computeRayInverseDirection(hkVector4Parameter dir, hkVector4& invDirOut)
{
	hkVector4 invDir = dir;
	invDir.zeroComponent<3>();
	invDirOut.setReciprocal<HK_ACC_23_BIT,HK_DIV_SET_MAX>(invDir);
}
#endif





#ifndef HK_VECTOR4UTIL_INTERNAL_rayTriangle
// version with uses less registers
static HK_FORCE_INLINE hkBool32	hkVector4UtilInternal::rayTriangle(hkVector4Parameter rayOrg, hkVector4Parameter rayDir, const hkVector4 v[3], hkSimdReal& fractionInOut, hkVector4& normalOut)
{
	{
		hkVector4	v01; v01.setSub(v[1],v[0]);
		hkVector4	v20; v20.setSub(v[0],v[2]);


		hkVector4	n;   n.setCross( v01,   v20    );
		hkVector4	orig0; orig0.setSub( rayOrg, v[0] );
		hkVector4	end0;  end0.setAddMul( orig0, rayDir, fractionInOut );
		hkSimdReal d  = n.dot<3>( orig0 );
		hkSimdReal e  = n.dot<3>( end0 );

		if ( (d*e).isSignBitClear() )
		{
			return 0;
		}

		hkSimdReal fraction = d / (d-e);	// calculate the fraction here so that the compiler can get rid of d and e

		hkVector4 orig1; orig1.setSub( rayOrg, v[1] );
		hkVector4 orig2; orig2.setSub( rayOrg, v[2] );
		hkVector4	v12; v12.setSub(v[2],v[1]);

		hkVector4   c0; c0.setCross( orig0, rayDir );
		hkVector4   c1; c1.setCross( orig1, rayDir );
		hkVector4   c2; c2.setCross( orig2, rayDir );

		hkSimdReal d0 = c0.dot<3>( v01 );
		hkSimdReal d1 = c1.dot<3>( v12 );
		hkSimdReal d2 = c2.dot<3>( v20 );

		if ( (d0*d1).isSignBitSet() | (d1*d2).isSignBitSet() )
		{
			return 0;
		}

		// now we are sure to have a hit
		fractionInOut = fraction * fractionInOut;
		normalOut	  =	n;
		return 1;
	}
}
#endif

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
