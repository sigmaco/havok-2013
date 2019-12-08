/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

//
HK_FORCE_INLINE	hkBool32	hkcdRayDirectionAabbIntersect(hkVector4Parameter rayInvDirection, const hkAabb& aabb, hkSimdReal* HK_RESTRICT fractionInOut)
{
	#if HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED
	hkVector4 dNearTemp;	dNearTemp.setMul(aabb.m_min, rayInvDirection);
	hkVector4 dFarTemp;		dFarTemp.setMul(aabb.m_max, rayInvDirection);

	hkVector4 dNear;	dNear.setMin(dNearTemp, dFarTemp);
	hkVector4 dFar;		dFar.setMax(dNearTemp, dFarTemp);

	const hkSimdReal fraction = *fractionInOut;

	hkSimdReal nearMax = dNear.horizontalMax<3>();
	hkSimdReal farMin  = dFar.horizontalMin<3>();

	nearMax.setMax(nearMax, hkSimdReal_0);
	farMin.setMin(farMin, fraction);

	*fractionInOut = nearMax;
	return nearMax.isLessEqual(farMin);

	#else
	hkReal	fmin = 0.0f, fmax = fractionInOut->getReal();
	for(int i=0; i<3; ++i)
	{
		const hkReal	mi = rayInvDirection(i) * aabb.m_min(i);
		const hkReal	mx = rayInvDirection(i) * aabb.m_max(i);
		if(mi > mx)
		{
			fmin = hkMath::max2(fmin, mx);
			fmax = hkMath::min2(fmax, mi);
		}
		else
		{
			fmin = hkMath::max2(fmin, mi);
			fmax = hkMath::min2(fmax, mx);
		}
	}

	fractionInOut->setFromFloat(fmin);

	return fmin <= fmax;
	#endif
}

//
HK_FORCE_INLINE	hkBool32	hkcdIntersectRayAabb(const hkcdRay& ray, const hkAabb& aabb, hkSimdReal* fractionInOut)
{
	#if HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED
	hkAabb	relAabb;
	relAabb.m_min.setSub(aabb.m_min, ray.m_origin);
	relAabb.m_max.setSub(aabb.m_max, ray.m_origin);
	
	return hkcdRayDirectionAabbIntersect(ray.m_invDirection, relAabb, fractionInOut);
	#else
	hkReal	fmin = 0.0f, fmax = fractionInOut->getReal();
	for(int i=0; i<3; ++i)
	{
		const hkReal	mi = ray.m_invDirection(i) * (aabb.m_min(i) - ray.m_origin(i));
		const hkReal	mx = ray.m_invDirection(i) * (aabb.m_max(i) - ray.m_origin(i));
		if(mi > mx)
		{
			fmin = hkMath::max2(fmin, mx);
			fmax = hkMath::min2(fmax, mi);
		}
		else
		{
			fmin = hkMath::max2(fmin, mi);
			fmax = hkMath::min2(fmax, mx);
		}
	}

	fractionInOut->setFromFloat(fmin);

	return fmin <= fmax;
	#endif
}

HK_FORCE_INLINE int hkcdIntersectRayBundleAabb(	const hkcdRay& ray, 
													const hkAabb& aabb0, const hkAabb& aabb1, const hkAabb& aabb2, const hkAabb& aabb3, 
													const hkSimdReal& earlyOutHitFraction)  
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	hkVector4 dNearTemp0, dNearTemp1, dNearTemp2, dNearTemp3;
	hkVector4 dFarTemp0, dFarTemp1, dFarTemp2, dFarTemp3;

	dNearTemp0.setSub( aabb0.m_min, ray.m_origin );
	dFarTemp0.setSub( aabb0.m_max, ray.m_origin );
	dNearTemp1.setSub( aabb1.m_min, ray.m_origin );
	dFarTemp1.setSub( aabb1.m_max, ray.m_origin );
	dNearTemp2.setSub( aabb2.m_min, ray.m_origin );
	dFarTemp2.setSub( aabb2.m_max, ray.m_origin );
	dNearTemp3.setSub( aabb3.m_min, ray.m_origin );
	dFarTemp3.setSub( aabb3.m_max, ray.m_origin );

	dNearTemp0.mul( ray.m_invDirection );
	dFarTemp0.mul( ray.m_invDirection );
	dNearTemp1.mul( ray.m_invDirection );
	dFarTemp1.mul( ray.m_invDirection );
	dNearTemp2.mul( ray.m_invDirection );
	dFarTemp2.mul( ray.m_invDirection );
	dNearTemp3.mul( ray.m_invDirection );
	dFarTemp3.mul( ray.m_invDirection );

	hkVector4 dNear0; dNear0.setMin( dNearTemp0, dFarTemp0 );
	hkVector4 dFar0;  dFar0.setMax(  dNearTemp0, dFarTemp0 );
	hkVector4 dNear1; dNear1.setMin( dNearTemp1, dFarTemp1 );
	hkVector4 dFar1;  dFar1.setMax(  dNearTemp1, dFarTemp1 );
	hkVector4 dNear2; dNear2.setMin( dNearTemp2, dFarTemp2 );
	hkVector4 dFar2;  dFar2.setMax(  dNearTemp2, dFarTemp2 );
	hkVector4 dNear3; dNear3.setMin( dNearTemp3, dFarTemp3 );
	hkVector4 dFar3;  dFar3.setMax(  dNearTemp3, dFarTemp3 );

	//Transpose so we can do a combined min, max
	HK_TRANSPOSE4(dNear0, dNear1, dNear2, dNear3);
	HK_TRANSPOSE4(dFar0, dFar1, dFar2, dFar3);
	
	hkVector4 fraction; fraction.setAll(earlyOutHitFraction);

	dNear0.setMax(dNear0, dNear1);
	dNear2.setMax(dNear2, hkVector4::getZero());

	dFar0.setMin(dFar0, dFar1);
	dFar2.setMin(dFar2, fraction);

	dNear0.setMax(dNear0, dNear2);
	dFar0.setMin(dFar0, dFar2);
	
	hkVector4Comparison nearLtFar = dNear0.lessEqual(dFar0);
	return nearLtFar.getMask();
#else
	hkSimdReal f[4] = {earlyOutHitFraction,earlyOutHitFraction,earlyOutHitFraction,earlyOutHitFraction};
	const int _0 = (hkcdIntersectRayAabb(ray, aabb0, &f[0]) ? hkVector4ComparisonMask::MASK_X : 0);
	const int _1 = (hkcdIntersectRayAabb(ray, aabb1, &f[1]) ? hkVector4ComparisonMask::MASK_Y : 0);
	const int _2 = (hkcdIntersectRayAabb(ray, aabb2, &f[2]) ? hkVector4ComparisonMask::MASK_Z : 0);
	const int _3 = (hkcdIntersectRayAabb(ray, aabb3, &f[3]) ? hkVector4ComparisonMask::MASK_W : 0);
	return _0 | _1 | _2 | _3;
#endif
}


HK_FORCE_INLINE	hkVector4Comparison	hkcdRayDirectionAabbBundleIntersect(hkVector4Parameter rayInvDirection,
																const hkFourTransposedPoints& aabbMin, const hkFourTransposedPoints& aabbMax,
																const hkVector4& fraction)
{
	hkFourTransposedPoints dNearTemp;	dNearTemp.setMulC(aabbMin, rayInvDirection);
	hkFourTransposedPoints dFarTemp;	dFarTemp.setMulC(aabbMax, rayInvDirection);

	hkFourTransposedPoints dNear;	dNear.setMin(dNearTemp, dFarTemp);
	hkFourTransposedPoints dFar;	dFar.setMax(dNearTemp, dFarTemp);

	hkVector4 nearYZ;	nearYZ.setMax( dNear.m_vertices[1], dNear.m_vertices[2] );
	hkVector4 farYZ;	farYZ .setMin( dFar.m_vertices[1],  dFar.m_vertices[2] );
	hkVector4 nearX;	nearX .setMax( dNear.m_vertices[0], hkVector4::getZero() );
	hkVector4 farX;		farX  .setMin( dFar.m_vertices[0],  fraction);

	nearX.setMax(nearX, nearYZ);
	farX.setMin(farX, farYZ);

	return nearX.lessEqual(farX);
}

HK_FORCE_INLINE	hkVector4Comparison	hkcdIntersectRayAabbBundle(const hkcdRay& ray,
															   const hkFourTransposedPoints& aabbMin, const hkFourTransposedPoints& aabbMax,
															   const hkVector4& fraction)
{
	hkFourTransposedPoints relMin; relMin.setSub( aabbMin, ray.m_origin );
	hkFourTransposedPoints relMax; relMax.setSub( aabbMax, ray.m_origin );
	return hkcdRayDirectionAabbBundleIntersect( ray.m_invDirection, relMin, relMax, fraction );
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
