/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

template <typename Vector, typename Scalar>
HK_FORCE_INLINE	/*static*/ Scalar HK_CALL hkcdPointLineDistanceSquared( const Vector& point, const Vector& lineStart, const Vector& lineEnd, Vector* HK_RESTRICT projectionOut /* = HK_NULL */)
{
	// Compute projection fraction.
	Vector delta;		delta.setSub(lineStart, lineEnd);
	Vector origin;		origin.setSub(lineStart, point);
	Scalar fraction;	fraction.setDiv(delta.template dot<3>(origin), delta.template dot<3>(delta));

	// Compute distance and set projectionOut if required.
	Vector projection;	projection.setSubMul(origin, delta, fraction);

	
	Scalar projLengthSqrd = projection.template dot<3>(projection);
	if ( projectionOut )
	{
		Vector projectionOnLine; projectionOnLine.setAdd(point, projection);
		projectionOut->setXYZ_W(projectionOnLine, fraction);
	}
	return projLengthSqrd;
}

HK_FORCE_INLINE	/*static*/ hkSimdReal HK_CALL hkcdPointLineDistanceSquared(hkVector4Parameter point, hkVector4Parameter lineA, hkVector4Parameter lineB, hkVector4* HK_RESTRICT projectionOut/* = HK_NULL*/ )
{
	return hkcdPointLineDistanceSquared<hkVector4, hkSimdReal>(point, lineA, lineB, projectionOut);
}

//
HK_FORCE_INLINE	/*static*/ hkSimdReal HK_CALL hkcdPointSegmentDistanceSquared(hkVector4Parameter point, hkVector4Parameter lineStart, hkVector4Parameter lineEnd, hkVector4* HK_RESTRICT projectionOut)
{
	// Load constants.
	hkSimdReal	zero; zero.setZero();
	hkSimdReal	one = hkSimdReal_1;

	// Compute projection fraction.
	hkVector4	delta; delta.setSub(lineStart, lineEnd);
	hkVector4	origin; origin.setSub(lineStart, point);
	hkSimdReal	fraction = delta.dot<3>(origin) / delta.lengthSquared<3>();

	// Clip fraction (handle the case where |delta|^2 == 0).
	fraction.setClamped(fraction, zero, one);

	// Compute distance and set projectionOut if required.
	hkVector4	projection; projection.setSubMul(origin, delta, fraction);

	
	hkSimdReal projLengthSqrd = projection.lengthSquared<3>();
	if(projectionOut)
	{
		hkVector4 projectionOnLine; projectionOnLine.setAdd(point, projection);
		projectionOut->setXYZ_W(projectionOnLine, fraction);
	}
	return projLengthSqrd;
}

HK_FORCE_INLINE	/*static*/ hkVector4 HK_CALL hkcdPointSegmentDistanceSquared(const hkFourTransposedPoints& points, hkVector4Parameter lineStart, hkVector4Parameter lineEnd, hkFourTransposedPoints* HK_RESTRICT projectionsOut)
{
	// Load constants.
	hkVector4 zero; zero.setZero();
	hkVector4 one = hkVector4::getConstant<HK_QUADREAL_1>();

	// Compute projection fraction.
	hkVector4	delta; delta.setSub(lineStart, lineEnd);
	hkSimdReal deltaSqr = delta.lengthSquared<3>();

	hkFourTransposedPoints origins; origins.setSub(lineStart, points);
	hkVector4 fractions;
	origins.dot3(delta, fractions);

	
	hkSimdReal invDeltaSqr; invDeltaSqr.setReciprocal(deltaSqr);
	fractions.mul(invDeltaSqr);

	// Clip fraction (handle the case where |delta|^2 == 0).
	fractions.setClamped(fractions, zero, one);

	// Compute distance and set projectionOut if required.
	hkFourTransposedPoints delta4; delta4.setAll(delta);
	hkFourTransposedPoints projections; projections.setSubMulT(origins, delta4, fractions);

	
	hkVector4 projLengthSqrd;
	projections.dot3(projections, projLengthSqrd);

	if (projectionsOut)
	{
		projectionsOut->setAdd(points, projections);
	}
	

	return projLengthSqrd;
}

template<int M>
HK_FORCE_INLINE	/*static*/ hkMxReal<M> HK_CALL hkcdPointSegmentDistanceSquared(hkMxVectorParameter point, hkMxVectorParameter lineStart, hkMxVectorParameter lineEnd, hkMxVector<M>* HK_RESTRICT projectionOut)
{
	// Load constants.
	hkMxReal<M>	zero; 
	zero.template setConstant<HK_QUADREAL_0>();
	hkMxReal<M>	one;
	one.template setConstant<HK_QUADREAL_1>();

	// Compute projection fraction.
	hkMxVector<M>	delta; delta.setSub(lineStart, lineEnd);
	hkMxVector<M>	origin; origin.setSub(lineStart, point);
	hkMxReal<M> deltaDotOrigin;
	delta.template dot<3>(origin, deltaDotOrigin);
	hkMxReal<M> deltaSquared;
	delta.template dot<3>(delta, deltaSquared);
	hkMxReal<M> fraction; fraction.template setDiv<HK_ACC_FULL,HK_DIV_IGNORE>(deltaDotOrigin, deltaSquared);

	// Clip fraction (handle the case where |delta|^2 == 0).
	fraction.setMax(fraction, zero);
	fraction.setMin(fraction, one);

	// Compute distance and set projectionOut if required.
	hkMxVector<M> projection; projection.setSubMul(origin, delta, fraction);

	
	if (projectionOut)
	{
		hkMxVector<M> projectionOnLine; projectionOnLine.setAdd(point, projection);
		projectionOut->setXYZ_W(projectionOnLine, fraction);
	}

	hkMxReal<M> lenSquared;
	projection.template dot<3>(projection, lenSquared);
	return lenSquared;
}

HK_FORCE_INLINE /*static*/ hkSimdReal HK_CALL hkcdPointCapsuleClosestPoint( hkVector4Parameter point, hkVector4Parameter rayStart, hkVector4Parameter rayEnd,
														hkSimdRealParameter capsuleRadius, hkVector4* HK_RESTRICT closestPointAndFractionOut, hkVector4* HK_RESTRICT normalOut )
{
	hkVector4 closestPointAndFraction;
	hkSimdReal lenSqr = hkcdPointSegmentDistanceSquared( point, rayStart, rayEnd, &closestPointAndFraction );
	hkSimdReal invLength = lenSqr.sqrtInverse();

	hkVector4 normal;
	normal.setSub( point, closestPointAndFraction);
	normal.setMul( normal, invLength );
	
	hkVector4 closestPointOnCapsule; closestPointOnCapsule.setAddMul( closestPointAndFraction, normal, capsuleRadius );
	closestPointAndFraction.setXYZ( closestPointOnCapsule ); // keep original .w

	*closestPointAndFractionOut = closestPointAndFraction;
	*normalOut = normal;

	return invLength * lenSqr;
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
