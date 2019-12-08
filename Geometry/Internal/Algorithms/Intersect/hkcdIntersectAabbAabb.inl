/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

//
HK_FORCE_INLINE	hkBool32	hkcdIntersectAabbAabb(const hkAabb& aabbA, const hkAabb& aabbB, const hkTransform& BtoA, const hkTransform& AtoB)
{
	const hkSimdReal half = hkSimdReal_Inv2;

	hkVector4	centerA;	centerA.setAdd(aabbA.m_min, aabbA.m_max);
	hkVector4	lengthA;	lengthA.setSub(aabbA.m_max, aabbA.m_min);	

	centerA.mul(half);	lengthA.mul(half);	

	hkVector4	heXA; heXA.setMul( lengthA.getComponent<0>(), AtoB.getColumn<0>() );
	hkVector4	heYA; heYA.setMul( lengthA.getComponent<1>(), AtoB.getColumn<1>() );
	hkVector4	heZA; heZA.setMul( lengthA.getComponent<2>(), AtoB.getColumn<2>() );
	heXA.setAbs(heXA);	heYA.setAbs(heYA);	heZA.setAbs(heZA);

	hkVector4	maxAinB;	maxAinB.setAdd(heXA,heYA);	maxAinB.add(heZA);

	hkVector4	centerAinB;	centerAinB._setTransformedPos(AtoB, centerA);

	hkVector4	minAinB;	minAinB.setSub(centerAinB, maxAinB);
	maxAinB.add(centerAinB);	

	hkVector4Comparison mincompB = minAinB.greater(aabbB.m_max);
	hkVector4Comparison maxcompB = aabbB.m_min.greater(maxAinB);
	hkVector4Comparison compB; compB.setOr(mincompB, maxcompB);

// #if defined(HK_PLATFORM_XBOX360) ||  defined(HK_PLATFORM_PS3 )
// #else
	if(compB.anyIsSet<hkVector4ComparisonMask::MASK_XYZ>())
	{
		return 0;
	}
//#endif

	hkVector4	centerB;	centerB.setAdd(aabbB.m_min, aabbB.m_max);
	hkVector4	lengthB;	lengthB.setSub(aabbB.m_max, aabbB.m_min);

	centerB.mul(half);	lengthB.mul(half);

	hkVector4	heXB; heXB.setMul(lengthB.getComponent<0>(), BtoA.getColumn<0>());
	hkVector4	heYB; heYB.setMul(lengthB.getComponent<1>(), BtoA.getColumn<1>());
	hkVector4	heZB; heZB.setMul(lengthB.getComponent<2>(), BtoA.getColumn<2>());
	heXB.setAbs(heXB);	heYB.setAbs(heYB);	heZB.setAbs(heZB);

	hkVector4	maxBinA;	maxBinA.setAdd(heXB,heYB); maxBinA.add(heZB);

	hkVector4	centerBinA;	centerBinA._setTransformedPos(BtoA, centerB);
	hkVector4	minBinA;	minBinA.setSub(centerBinA, maxBinA);

	maxBinA.add(centerBinA);

	hkVector4Comparison mincompA = minBinA.lessEqual(aabbA.m_max);
	hkVector4Comparison maxcompA = aabbA.m_min.lessEqual(maxBinA);
	hkVector4Comparison compA; compA.setAnd(mincompA, maxcompA);

	return compA.allAreSet<hkVector4ComparisonMask::MASK_XYZ>();
}

//
HK_FORCE_INLINE	hkBool32	hkcdIntersectAabbAabb(const hkAabb& aabbA, const hkAabb& aabbB, const hkTransform& BtoA)
{
	hkTransform	AtoB; AtoB._setInverse(BtoA);
	return hkcdIntersectAabbAabb(aabbA, aabbB, BtoA, AtoB);
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
