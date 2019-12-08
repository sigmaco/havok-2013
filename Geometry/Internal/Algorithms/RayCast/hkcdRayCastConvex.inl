/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */


HK_FORCE_INLINE hkInt32 HK_CALL hkcdRayCastConvex(
	const hkcdRay& ray,
	const hkVector4* HK_RESTRICT planeEquations,
	int numPlaneEquations,
	hkSimdReal* HK_RESTRICT fractionInOut,
	hkVector4* HK_RESTRICT normalOut,
	hkcdRayQueryFlags::Enum flags
	)
{
	HK_ASSERT2( 0xeb015a17, numPlaneEquations >= 4, "Convex hull requires at least 4 planes." );

	hkVector4Comparison insideHits; hkcdRayQueryFlags::extractFlag(flags, hkcdRayQueryFlags::ENABLE_INSIDE_HITS, insideHits);

	hkIntVector bestNrm0;	bestNrm0.setZero();
	hkIntVector bestNrm1;	bestNrm1.setZero();
	hkVector4 vLambda0 = hkVector4::getConstant<HK_QUADREAL_MINUS1>();
	hkVector4 vLambda1 = hkVector4::getConstant<HK_QUADREAL_2>();

	// The main loop reads 4 at a time. Deal with the array not being a multiple of 4
	// (and potentially reading into unmapped memory) by doing the leftovers first.
	// e.g. for a shape with 9 verts, we do 3 loops - [5678], then [0123], then [4567]
	hkIntVector crtIdx;
	hkVector4 planes0, planes1, planes2, planes3;
	{
		int n = numPlaneEquations - 4;
		crtIdx.set( n, n+1, n+2, n+3 );

		planes0 = planeEquations[n+0];
		planes1 = planeEquations[n+1];
		planes2 = planeEquations[n+2];
		planes3 = planeEquations[n+3];
	}
	
	hkIntVector	nextIdx = hkIntVector::getConstant<HK_QUADINT_0123>();

	// Set w to 1 to compute the plane equations
	hkVector4 vFrom, vTo;
	{
		const hkSimdReal one = hkSimdReal_1;
		vFrom.setXYZ_W(ray.m_origin, one);
		vTo.setAddMul( ray.m_origin, ray.getDirection(), *fractionInOut );
		vTo.setXYZ_W(vTo, one);
	}

	const int lastBatchIndex = numPlaneEquations & ~3;
	int batchIndex = 0;
	while(true)
	{
		// Compute start and end distances to the planes
		hkVector4 dStart, dEnd;	
		hkVector4Util::dot4_1vs4(vFrom, planes0, planes1, planes2, planes3, dStart);
		hkVector4Util::dot4_1vs4(vTo, planes0, planes1, planes2, planes3, dEnd);

		// Calculate the intersection lambda between ray and the current plane
		hkVector4 vLambda;
		vLambda.setSub(dStart, dEnd);
		vLambda.setDiv<HK_ACC_23_BIT, HK_DIV_IGNORE>(dStart, vLambda); // we can have a /0 if dStart==dEnt

		hkVector4Comparison ds_ge_0		= dStart.greaterEqualZero();	// (dStart >= 0.0f)
		hkVector4Comparison de_ge_0		= dEnd.greaterEqualZero();	// (dEnd >= 0.0f)

		// Check for not colliding
		{
			hkVector4Comparison notColliding;
			notColliding.setAnd(ds_ge_0, de_ge_0);
			if ( notColliding.anyIsSet() )
			{
				return hkcdRayCastResult::createMiss();	// At least one of the planes is not colliding
			}
		}

		// Select entry lambda
		{
			hkVector4Comparison cmp;
			cmp.setAnd(ds_ge_0, vLambda0.less(vLambda));
			cmp.setAndNot(cmp, de_ge_0);	// valid && (dStart >= 0) && (dEnd < 0) && (lambda0 < lambda)

			vLambda0.setSelect(cmp, vLambda, vLambda0);
			bestNrm0.setSelect(cmp, crtIdx, bestNrm0);
		}

		// Select exit lambda
		{
			hkVector4Comparison cmp;
			cmp.setAnd(de_ge_0, vLambda1.greater(vLambda));
			cmp.setAndNot(cmp, ds_ge_0);	// valid && (dStart < 0) && (dEnd >= 0) && (lambda < lambda1)

			vLambda1.setSelect(cmp, vLambda, vLambda1);
			bestNrm1.setSelect(cmp, crtIdx, bestNrm1);
		}

		if( batchIndex < lastBatchIndex )
		{
			// another full batch to go
			planes0 = planeEquations[batchIndex+0];
			planes1 = planeEquations[batchIndex+1];
			planes2 = planeEquations[batchIndex+2];
			planes3 = planeEquations[batchIndex+3];

			hkIntVector four; four.splatImmediate32<4>();
			crtIdx = nextIdx;
			nextIdx.setAddU32(nextIdx, four);
			batchIndex += 4;
		}
		else
		{
			break;
		}
	}

	// Final checks
	{
		hkSimdReal lambda0 = vLambda0.horizontalMax<4>();
		hkSimdReal lambda1 = vLambda1.horizontalMin<4>();

		hkVector4Comparison isInside = lambda0.lessZero();
		hkVector4Comparison pathSelect; pathSelect.setAnd( isInside, insideHits );

		hkSimdReal lambda; lambda.setSelect( pathSelect, lambda1, lambda0 );
		hkIntVector bestNrm; bestNrm.setSelect( pathSelect, bestNrm1, bestNrm0 );

		// Set fraction
		fractionInOut->mul( lambda );

		// Set normal
		{
			hkVector4 nvLambda1; nvLambda1.setNeg<4>( vLambda1 );
			hkVector4 vLambda; vLambda.setSelect( pathSelect, nvLambda1, vLambda0);
			int bestNrmIndex = bestNrm.getComponentAtVectorMax( vLambda );
			*normalOut = planeEquations[bestNrmIndex];
		}

		// no inside hits: (lambda1 < lambda0) || (lambda0 < 0) means no intersection
		hkVector4Comparison inter0; inter0.setAnd(lambda1.greaterEqual(lambda0), lambda0.greaterEqualZero());
		// inside hits: lambda1 was never set means no intersection
		hkVector4Comparison inter1 = lambda1.notEqual( hkSimdReal_2);

		hkVector4Comparison inter; inter.setSelect(pathSelect, inter1, inter0);
		return hkcdRayCastResult::create(inter, pathSelect);
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
