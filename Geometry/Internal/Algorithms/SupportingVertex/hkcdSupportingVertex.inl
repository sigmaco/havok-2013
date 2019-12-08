/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */


//
HK_DISABLE_OPTIMIZATION_VS2008_X64
	//	Returns the furthest vertex in the given direction
HK_FORCE_INLINE void HK_CALL hkcdSupportingVertexPoints(const hkcdVertex* HK_RESTRICT vertices, int numVertices, hkVector4Parameter direction, hkcdVertex* HK_RESTRICT vertexOut)
{
	#if defined(HK_DEBUG)
		for( int i = numVertices; i < HK_NEXT_MULTIPLE_OF(4,numVertices); ++i )
		{
			const hkVector4 first = vertices[0];
			const hkVector4 last = vertices[numVertices-1];
			const hkVector4 v = vertices[i];
			HK_ASSERT2(0x588428b2, v.equal(last).allAreSet() || v.equal(first).allAreSet(), "last or first vertex must be duplicated to a multiple of 4" );
		}
	#endif
	const hkVector4* HK_RESTRICT fvA = vertices;

	hk4xSingle directionAVec; directionAVec.setVector(direction);
	hk4xVector4 bestVertA;	


	// Fastest version, requires multiple of 4 vertices
	bestVertA.moveLoad( fvA );
	fvA += 4;
	int mainLoopVectors = numVertices-4;

	hk4xReal bestDotA; bestDotA.setDot<3>( directionAVec, bestVertA  );


	while( mainLoopVectors > 0 )
	{
		hk4xVector4 vertA;	vertA.moveLoad(fvA);
		hk4xReal curDotA; curDotA.setDot<3>( directionAVec, vertA  );
		hk4xVector4 cmp; cmp.setBroadcast(curDotA);
		hk4xMask compA; bestDotA.less( cmp, compA );

		bestDotA.setSelect ( compA, curDotA, bestDotA  );
		bestVertA.setSelect( compA, vertA,   bestVertA );

		fvA+=4;
		mainLoopVectors -= 4;
	}

	// binary combine
	hkVector4 bestA;
	{
		hkVector4Comparison cmp1gt0 = bestDotA.getReal<1>().greater( bestDotA.getReal<0>() );
		hkVector4Comparison cmp3gt2 = bestDotA.getReal<3>().greater( bestDotA.getReal<2>() );

		hkSimdReal bestDotA01;  bestDotA01.setSelect( cmp1gt0, bestDotA.getReal<1>(),    bestDotA.getReal<0>() );
		hkVector4 bestVertA01; bestVertA01.setSelect( cmp1gt0, bestVertA.getVector<1>(),   bestVertA.getVector<0>()	  );
		hkSimdReal bestDotA23;  bestDotA23.setSelect( cmp3gt2, bestDotA.getReal<3>(),    bestDotA.getReal<2>() );
		hkVector4 bestVertA23; bestVertA23.setSelect( cmp3gt2, bestVertA.getVector<3>(),   bestVertA.getVector<2>()      );

		hkVector4Comparison a01GTa23 = bestDotA01.greater(bestDotA23);
		bestA.setSelect( a01GTa23, bestVertA01,  bestVertA23 );
	}
	*(hkVector4*)vertexOut = bestA;
}

HK_FORCE_INLINE void HK_CALL hkcdSupportingVertexPoints2(
	const hkcdVertex* HK_RESTRICT fvA, int numVerticesA,
	const hkcdVertex* HK_RESTRICT fvB, int numVerticesB,
	hkVector4Parameter directionA, const hkTransform& aTb,
	hkcdVertex* HK_RESTRICT vertexAinAOut,
	hkcdVertex* HK_RESTRICT vertexBinBOut,
	hkVector4* HK_RESTRICT vertexBinAOut )
{
	hkVector4 negDir;	 negDir.setNeg<4>(directionA);
	hkVector4 directionB; directionB._setRotatedInverseDir( aTb.getRotation(), negDir);

	hk4xVector4 bestVertA;	bestVertA.moveLoad( fvA );
	hk4xVector4 bestVertB;	bestVertB.moveLoad( fvB );

	hk4xSingle directionAVec; directionAVec.setVector(directionA);
	hk4xSingle directionBVec; directionBVec.setVector(directionB);

	hk4xReal bestDotA; bestDotA.setDot<3>( directionAVec, bestVertA  ); 
	hk4xReal bestDotB; bestDotB.setDot<3>( directionBVec, bestVertB  );

	fvA += 4;
	fvB += 4;

	int a = numVerticesA-4;
	int b = numVerticesB-4;

	// if we are fighting for codesize, don't do this unrolled loop
	int maxNum = hkMath::min2( a, b );	// optimize me

	while ( maxNum > 0)
	{
		hk4xVector4 vertA;	vertA.moveLoad(fvA);
		hk4xVector4 vertB;	vertB.moveLoad(fvB);

		hk4xReal dotA; dotA.setDot<3>( directionAVec, vertA  );
		hk4xReal dotB; dotB.setDot<3>( directionBVec, vertB  );

		hk4xVector4 bA; bA.setBroadcast(bestDotA);
		hk4xVector4 bB; bB.setBroadcast(bestDotB);

		hk4xMask compA; dotA.greater( bA, compA );
		hk4xMask compB; dotB.greater( bB, compB );

		bestDotA.setSelect(  compA, dotA,	bestDotA   );
		bestVertA.setSelect( compA, vertA, bestVertA  );
		bestDotB.setSelect(  compB, dotB,  bestDotB   );
		bestVertB.setSelect( compB, vertB, bestVertB  );

		fvA+=4;
		fvB+=4;
		a -= 4;
		b -= 4;
		maxNum -= 4;
	}

	while( a > 0 )
	{
		hk4xVector4 vertA;	vertA.moveLoad(fvA);
		hk4xReal dotA;   dotA.setDot<3>( directionAVec, vertA  );
		hk4xVector4 bA; bA.setBroadcast(bestDotA);
		hk4xMask compA; dotA.greater( bA, compA );

		bestDotA.setSelect ( compA, dotA,  bestDotA  );
		bestVertA.setSelect ( compA, vertA, bestVertA  );

		fvA+=4;
		a -= 4;
	}


	while( b > 0 )
	{
		hk4xVector4 vertB;	vertB.moveLoad(fvB);
		hk4xReal dotB;   dotB.setDot<3>( directionBVec, vertB  );
		hk4xVector4 bB; bB.setBroadcast(bestDotB);
		hk4xMask compB; dotB.greater( bB, compB );
		bestDotB.setSelect(  compB, dotB,    bestDotB   );
		bestVertB.setSelect( compB, vertB,   bestVertB  );

		fvB+=4;
		b -= 4;
	}

	// binary combine a 
	hkVector4 bestA;
	{
		hkVector4Comparison cmp1gt0 = bestDotA.getReal<1>().greater( bestDotA.getReal<0>() );
		hkVector4Comparison cmp3gt2 = bestDotA.getReal<3>().greater( bestDotA.getReal<2>() );

		hkSimdReal bestDotA01;  bestDotA01.setSelect( cmp1gt0, bestDotA.getReal<1>(),    bestDotA. getReal<0>() );
		hkVector4 bestVertA01; bestVertA01.setSelect( cmp1gt0, bestVertA.getVector<1>(),   bestVertA.getVector<0>()	  );
		hkSimdReal bestDotA23;  bestDotA23.setSelect( cmp3gt2, bestDotA.getReal<3>(),    bestDotA. getReal<2>() );
		hkVector4 bestVertA23; bestVertA23.setSelect( cmp3gt2, bestVertA.getVector<3>(),   bestVertA.getVector<2>()      );

		hkVector4Comparison a01GTa23 = bestDotA01.greater(bestDotA23);
		bestA.setSelect( a01GTa23, bestVertA01,  bestVertA23 );
	}
	hkVector4 bestB;
	{
		hkVector4Comparison cmp1gt0 = bestDotB.getReal<1>().greater( bestDotB.getReal<0>() );
		hkVector4Comparison cmp3gt2 = bestDotB.getReal<3>().greater( bestDotB.getReal<2>() );

		hkSimdReal bestDotB01;  bestDotB01.setSelect( cmp1gt0, bestDotB. getReal<1>(),   bestDotB.getReal<0>() );
		hkVector4 bestVertB01; bestVertB01.setSelect( cmp1gt0, bestVertB.getVector<1>(),	 bestVertB.getVector<0>()   );
		hkSimdReal bestDotB23;  bestDotB23.setSelect( cmp3gt2, bestDotB. getReal<3>(),   bestDotB.getReal<2>() );
		hkVector4 bestVertB23; bestVertB23.setSelect( cmp3gt2, bestVertB.getVector<3>(),     bestVertB.getVector<2>()   );

		hkVector4Comparison b01GTb23 = bestDotB01.greater(bestDotB23);
		bestB.setSelect( b01GTb23, bestVertB01, bestVertB23  );
	}

	vertexBinAOut->_setTransformedPos(aTb, bestB);
	vertexAinAOut->assign( bestA );
	vertexBinBOut->assign( bestB );
}
HK_RESTORE_OPTIMIZATION_VS2008_X64

// COM-1776 Remedy 
// hkcdSupportingVertexPoints assumes dot products computed 
// from the same pairs of vectors will always produce the 
// exact same result. On FPU, this requires precise mode. 
#if (HK_CONFIG_SIMD==HK_CONFIG_SIMD_DISABLED)
#pragma float_control(precise, on) 
#endif

inline void HK_CALL hkcdSupportingVertexPoints(const hkFourTransposedPoints* HK_RESTRICT transposedVertices, int numTransposedVertices, hkVector4Parameter direction, hkcdVertex* HK_RESTRICT vertexOut)
{
	HK_ASSERT2(0x6c61af08, numTransposedVertices > 0, "At least one vertex required");
	hkIntVector currentIdx = hkIntVector::getConstant<HK_QUADINT_0123>();
	hkIntVector stepIdx;	stepIdx.splatImmediate32<4>();

	const hkFourTransposedPoints* HK_RESTRICT fv = transposedVertices;

	hkFourTransposedPoints vDir;
	vDir.setAll(direction);

	hkVector4 v0; v0 = fv[0].m_vertices[0];
	hkVector4 v1; v1 = fv[0].m_vertices[1];
	hkVector4 v2; v2 = fv[0].m_vertices[2];
	hkIntVector vi; vi = currentIdx;

	hkVector4 bestDots;
	vDir.dot3(*fv, bestDots);

	for(int bi = 1; bi < numTransposedVertices; bi++)
	{
		// Increment indices
		currentIdx.setAddU32(currentIdx, stepIdx);

		// Compute current dots
		hkVector4 currentDots;
		vDir.dot3(fv[bi], currentDots);

		// Select best dots & indices
		const hkVector4Comparison cmp = bestDots.less(currentDots);
		bestDots.setSelect(cmp, currentDots, bestDots);
		v0.setSelect(cmp, fv[bi].m_vertices[0], v0 );
		v1.setSelect(cmp, fv[bi].m_vertices[1], v1 );
		v2.setSelect(cmp, fv[bi].m_vertices[2], v2 );
		vi.setSelect(cmp, currentIdx, vi );
	}

	hkVector4 v3; vi.storeInto24LowerBitsOfReal( v3 );
	HK_TRANSPOSE4(v0,v1,v2,v3);

	{
		const hkSimdReal dots0 = bestDots.getComponent<0>();
		const hkSimdReal dots1 = bestDots.getComponent<1>();
		const hkVector4Comparison cmp1gt0 = dots1.greater( dots0 );
		const hkSimdReal dots2 = bestDots.getComponent<2>();
		const hkSimdReal dots3 = bestDots.getComponent<3>();
		const hkVector4Comparison cmp3gt2 = dots3.greater( dots2 );

		hkSimdReal dots01; dots01.setSelect( cmp1gt0, dots1, dots0 );
		hkVector4 vert01;  vert01.setSelect( cmp1gt0, v1, v0 );
		hkSimdReal dots23; dots23.setSelect( cmp3gt2, dots3, dots2 );
		hkVector4 vert23;  vert23.setSelect( cmp3gt2, v3, v2);

		const hkVector4Comparison cmp23gt01 = dots23.greater(dots01);
		vertexOut->setSelect( cmp23gt01, vert23, vert01);
	}
}

// COM-1776
#if (HK_CONFIG_SIMD==HK_CONFIG_SIMD_DISABLED)
#pragma float_control(precise, off) 
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
