/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */


#include <Common/Base/Types/Geometry/Aabb/hkAabb.h>

namespace hkAabbUtil
{

void HK_CALL calcAabb( const hkTransform& localToWorld, const hkVector4& halfExtents, hkSimdRealParameter extraRadius, hkAabb& aabbOut )
{
	hkVector4 he0; he0.setBroadcast<0>( halfExtents );
	hkVector4 he1; he1.setBroadcast<1>( halfExtents );
	hkVector4 he2; he2.setBroadcast<2>( halfExtents );

	hkVector4 transformedX; transformedX.setMul( he0, localToWorld.getRotation().getColumn<0>());
	hkVector4 transformedY; transformedY.setMul( he1, localToWorld.getRotation().getColumn<1>());
	hkVector4 transformedZ; transformedZ.setMul( he2, localToWorld.getRotation().getColumn<2>());
	
	transformedX.setAbs( transformedX );
	transformedY.setAbs( transformedY );
	transformedZ.setAbs( transformedZ );

	hkVector4 extra; extra.setAll( extraRadius );
	transformedZ.add( extra );

	hkVector4 max;
	max.setAdd( transformedX, transformedY );
	max.add( transformedZ );

	hkVector4 min;	min.setNeg<4>(max);

	max.add( localToWorld.getTranslation() );
	min.add( localToWorld.getTranslation()  );

	aabbOut.m_max = max;
	aabbOut.m_min = min;
}


void HK_CALL calcAabb( const hkTransform& localToWorld, const hkVector4& halfExtents, const hkVector4& center, hkSimdRealParameter extraRadius, hkAabb& aabbOut )
{
	hkVector4 he0; he0.setBroadcast<0>( halfExtents );
	hkVector4 he1; he1.setBroadcast<1>( halfExtents );
	hkVector4 he2; he2.setBroadcast<2>( halfExtents );

	hkVector4 transformedX; transformedX.setMul( he0, localToWorld.getRotation().getColumn<0>());
	hkVector4 transformedY; transformedY.setMul( he1, localToWorld.getRotation().getColumn<1>());
	hkVector4 transformedZ; transformedZ.setMul( he2, localToWorld.getRotation().getColumn<2>());

	transformedX.setAbs( transformedX );
	transformedY.setAbs( transformedY );
	transformedZ.setAbs( transformedZ );


	hkVector4 extra; extra.setAll( extraRadius );
	transformedZ.add( extra );

	hkVector4 max;
	max.setAdd( transformedX, transformedY );
	max.add( transformedZ );

	hkVector4 min;	min.setNeg<4>(max);

	hkVector4 temp;	temp._setTransformedPos(localToWorld, center);

	max.add( temp );
	min.add( temp );

	aabbOut.m_max = max;
	aabbOut.m_min = min;
}

void HK_CALL calcAabb( const hkTransform& localToWorld, const hkVector4& halfExtents, const hkVector4& center, hkAabb& aabbOut )
{
	hkVector4 he0; he0.setBroadcast<0>( halfExtents );
	hkVector4 he1; he1.setBroadcast<1>( halfExtents );
	hkVector4 he2; he2.setBroadcast<2>( halfExtents );

	hkVector4 transformedX; transformedX.setMul( he0, localToWorld.getRotation().getColumn<0>());
	hkVector4 transformedY; transformedY.setMul( he1, localToWorld.getRotation().getColumn<1>());
	hkVector4 transformedZ; transformedZ.setMul( he2, localToWorld.getRotation().getColumn<2>());

	transformedX.setAbs( transformedX );
	transformedY.setAbs( transformedY );
	transformedZ.setAbs( transformedZ );

	hkVector4 max;
	max.setAdd( transformedX, transformedY );
	max.add( transformedZ );

	hkVector4 min;	min.setNeg<4>(max);

	hkVector4 temp;	temp._setTransformedPos(localToWorld, center);

	max.add( temp );
	min.add( temp );

	aabbOut.m_max = max;
	aabbOut.m_min = min;
}

void HK_CALL transformAabbIntoLocalSpace( const hkTransform& localToWorld, const hkAabb& aabb, hkAabb& aabbOut )
{
	hkVector4 center;		aabb.getCenter(center);
	hkVector4 halfExtents;	aabb.getHalfExtents(halfExtents);

	hkRotation rot; rot._setTranspose( localToWorld.getRotation() );

	hkVector4 transformedX; transformedX.setMul( halfExtents.getComponent<0>(), rot.getColumn<0>());
	hkVector4 transformedY; transformedY.setMul( halfExtents.getComponent<1>(), rot.getColumn<1>());
	hkVector4 transformedZ; transformedZ.setMul( halfExtents.getComponent<2>(), rot.getColumn<2>());
	transformedX.setAbs( transformedX );
	transformedY.setAbs( transformedY );
	transformedZ.setAbs( transformedZ );

	hkVector4 max;
	max.setAdd( transformedX, transformedY );
	max.add( transformedZ );

	hkVector4 min;	min.setNeg<4>(max);

	hkVector4 temp;	temp._setTransformedInversePos(localToWorld, center);

	min.add( temp );
	max.add( temp );

	aabbOut.m_max = max;
	aabbOut.m_min = min;
}



//
void calcAabb( const hkVector4& center, hkSimdRealParameter innerRadius, hkAabb& aabbOut)
{
	hkVector4	ir;	ir.setAll(innerRadius);
	aabbOut.m_min.setSub(center,ir);
	aabbOut.m_max.setAdd(center,ir);
	aabbOut.m_min.zeroComponent<3>();
	aabbOut.m_max.zeroComponent<3>();
}

//
HK_FORCE_INLINE hkSimdReal getOuterRadius(const hkAabb& aabb)
{
	return hkSimdReal_Inv2 * aabb.m_min.distanceTo(aabb.m_max);
}

//
HK_FORCE_INLINE hkSimdReal	distanceSquared(const hkAabb& a, hkVector4Parameter b)
{
	if (a.containsPoint(b))
	{
		return hkSimdReal_0;
	}
	else
	{
		hkVector4	c;		
		c.setMin(b,a.m_max);
		hkVector4	d;
		d.setMax(c,a.m_min);
		return d.distanceToSquared(b);
	}
}

HK_FORCE_INLINE hkSimdReal calcMinGap( const hkAabb& innerAabb, const hkAabb& outerAabb )
{
	hkVector4 ma; ma.setSub( outerAabb.m_max, innerAabb.m_max );
	hkVector4 mi; mi.setSub( innerAabb.m_min, outerAabb.m_min );
	hkVector4 gap; gap.setMin(mi,ma);
	return gap.horizontalMin<3>();
}


//
HK_FORCE_INLINE void getVertex(const hkAabb& aabb, int index, hkVector4& vertexOut)
{
	HK_ASSERT2(0x1ACBA392,0 <= index && index <=7,"Invalid vertex index");
	hkVector4Comparison mask; mask.set((hkVector4ComparisonMask::Mask)index);
	vertexOut.setSelect(mask, aabb.m_min, aabb.m_max);
	vertexOut.zeroComponent<3>();
}

HK_FORCE_INLINE void get8Vertices(const hkAabb& aabb, hkVector4* HK_RESTRICT verticesOut)
{
	for (int i =0; i < 8; i++)
	{
		getVertex( aabb, i, verticesOut[i] );
	}
}

//
HK_FORCE_INLINE	void scaleAabb(const hkVector4& scale, const hkAabb& aabbIn, hkAabb& aabbOut)
{
	hkVector4	newMin; newMin.setMul(aabbIn.m_min,scale);
	hkVector4	newMax; newMax.setMul(aabbIn.m_max,scale);
	aabbOut.m_min.setMin(newMin,newMax);
	aabbOut.m_max.setMax(newMin,newMax);
}

//
HK_FORCE_INLINE void	expandAabbByMotion(const hkAabb& aabbIn, const hkVector4& motion, hkAabb& aabbOut)
{
	hkVector4	minOffset; minOffset.setAdd(aabbIn.m_min, motion);
	hkVector4	maxOffset; maxOffset.setAdd(aabbIn.m_max, motion);
	hkVector4	newMin; newMin.setMin(minOffset, aabbIn.m_min);
	hkVector4	newMax; newMax.setMax(maxOffset, aabbIn.m_max);

	aabbOut.m_min = newMin;
	aabbOut.m_max = newMax;
}

//
HK_FORCE_INLINE void	expandAabbByMotion(const hkAabb& aabbIn, const hkVector4& motion, hkSimdRealParameter anyDirectionExpansion, hkAabb& aabbOut)
{
	hkVector4	radius; radius.setAll(anyDirectionExpansion);
	hkVector4	minOffset; minOffset.setAdd(aabbIn.m_min, motion);
	hkVector4	maxOffset; maxOffset.setAdd(aabbIn.m_max, motion);
	hkVector4	newMin; newMin.setMin(minOffset, aabbIn.m_min);
	hkVector4	newMax; newMax.setMax(maxOffset, aabbIn.m_max);

	aabbOut.m_min.setSub(newMin, radius);
	aabbOut.m_max.setAdd(newMax, radius);
}

HK_FORCE_INLINE void expandAabbByMotion(const hkAabb& aabbIn, hkVector4Parameter motionA, hkVector4Parameter motionB, hkSimdRealParameter anyDirectionExpansion, hkAabb& aabbOut)
{

	hkVector4 zero; zero.setZero();
	hkVector4 expandLinMin; 
	hkVector4 expandLinMax; 

	expandLinMin.setMin(zero, motionA);
	expandLinMax.setMax(zero, motionA);

	expandLinMin.setMin(expandLinMin, motionB );
	expandLinMax.setMax(expandLinMax, motionB );

	hkVector4 expandAny; expandAny.setAll(anyDirectionExpansion);
	expandLinMin.sub( expandAny );
	expandLinMax.add( expandAny );

	hkVector4 ma; ma.setAdd(aabbIn.m_max, expandLinMax);	// helper variable to avoid LHS avoidance
	aabbOut.m_min.setAdd(aabbIn.m_min, expandLinMin);
	aabbOut.m_max = ma;
}

HK_FORCE_INLINE void expandAabbByMotionCircle(const hkAabb& aabbIn, hkVector4Parameter motionA, hkVector4Parameter motionB, hkSimdRealParameter anyDirectionExpansion, hkAabb& aabbOut)
{
	hkVector4 expandLinMin; 
	hkVector4 expandLinMax; 

	{
		// Calculate the minimum aabb expansion that includes the bounding sphere around the motion.
		hkSimdReal distmoved = motionA.length<3>();
		hkVector4 expansionSize; expansionSize.setAll(distmoved*hkSimdReal_Inv2);
		hkVector4 moveCenter; moveCenter.setMul(motionA, hkSimdReal_Inv2);

		expandLinMin.setSub(moveCenter, expansionSize);
		expandLinMax.setAdd(moveCenter, expansionSize);
	}

	expandLinMin.setMin(expandLinMin, motionB );
	expandLinMax.setMax(expandLinMax, motionB );

	hkVector4 expandAny; expandAny.setAll(anyDirectionExpansion);
	expandLinMin.sub( expandAny );
	expandLinMax.add( expandAny );

	hkVector4 ma; ma.setAdd(aabbIn.m_max, expandLinMax);	// helper variable to avoid LHS avoidance
	aabbOut.m_min.setAdd(aabbIn.m_min, expandLinMin);
	aabbOut.m_max = ma;
}


//
HK_FORCE_INLINE void	projectAabbOnAxis(const hkVector4& axis, const hkAabb& aabb, hkSimdReal& minOut, hkSimdReal& maxOut)
{
	hkVector4	coeffsMin; coeffsMin.setMul(axis, aabb.m_min);
	hkVector4	coeffsMax; coeffsMax.setMul(axis, aabb.m_max);
	hkVector4	prjMin; prjMin.setMin(coeffsMin, coeffsMax);
	hkVector4	prjMax; prjMax.setMax(coeffsMin, coeffsMax);
	minOut = prjMin.horizontalAdd<3>();
	maxOut = prjMax.horizontalAdd<3>();
}

//
HK_FORCE_INLINE void	projectAabbMinOnAxis(const hkVector4& axis, const hkAabb& aabb, hkSimdReal& prjOut)
{
	hkVector4	coeffsMin; coeffsMin.setMul(axis, aabb.m_min);
	hkVector4	coeffsMax; coeffsMax.setMul(axis, aabb.m_max);
	hkVector4	prj; prj.setMin(coeffsMin, coeffsMax);
	prjOut = prj.horizontalAdd<3>();
}

//
HK_FORCE_INLINE void	projectAabbMaxOnAxis(const hkVector4& axis, const hkAabb& aabb, hkSimdReal& prjOut)
{
	hkVector4	coeffsMin; coeffsMin.setMul(axis, aabb.m_min);
	hkVector4	coeffsMax; coeffsMax.setMul(axis, aabb.m_max);
	hkVector4	prj; prj.setMax(coeffsMin, coeffsMax);
	prjOut = prj.horizontalAdd<3>();
}

//
HK_FORCE_INLINE void	computeAabbPlaneSpan(const hkVector4& plane, const hkAabb& aabb, hkSimdReal& minOut, hkSimdReal& maxOut)
{
	hkSimdReal prj[2];
	projectAabbOnAxis(plane, aabb, prj[0], prj[1]);
	minOut = prj[0] + plane.getComponent<3>();
	maxOut = prj[1] + plane.getComponent<3>();
}

void sweepAabb(const hkMotionState* motionState, hkReal tolerance, const hkAabb& aabbIn, hkAabb& aabbOut)
{
	//
	//  Expand the AABB by the angular part
	//

	hkSimdReal objectRadius; objectRadius.setFromFloat(motionState->m_objectRadius);
	{
		const hkSimdReal radius = motionState->m_deltaAngle.getW() * objectRadius;
		hkVector4 rotationalGain; rotationalGain.setAll(radius);
		aabbOut.m_min.setSub(aabbIn.m_min, rotationalGain);
		aabbOut.m_max.setAdd(aabbIn.m_max, rotationalGain);
	}

	//
	// restrict the size of the AABB to the worst case radius size
	//
	{
		hkSimdReal toleranceSr;  toleranceSr.setFromFloat(tolerance);
		hkVector4 radius4; radius4.setAll( objectRadius + toleranceSr );
		hkVector4 maxR; maxR.setAdd( motionState->getSweptTransform().m_centerOfMass1, radius4 );
		hkVector4 minR; minR.setSub( motionState->getSweptTransform().m_centerOfMass1, radius4 );

		HK_ON_DEBUG
		(
			// I consider success when (aabbInOut.m_min <= maxR) and (minR <= aabbInOut.m_max) are true for all XYZ
			hkVector4Comparison a = aabbIn.m_min.lessEqual( maxR );
			hkVector4Comparison b = minR.lessEqual( aabbIn.m_max );
			hkVector4Comparison both; both.setAnd(a,b);
			HK_ASSERT2(0x366ca7b2, both.allAreSet<hkVector4ComparisonMask::MASK_XYZ>(), "Invalid Radius. Did you make changes to a shape or change its center of mass while the owner was added to the world?" );
		);

		aabbOut.m_min.setMax( aabbOut.m_min, minR );
		aabbOut.m_min.setMin( aabbOut.m_min, aabbIn.m_min );

		aabbOut.m_max.setMin( aabbOut.m_max, maxR );
		aabbOut.m_max.setMax( aabbOut.m_max, aabbIn.m_max );
	}

	//
	// Sweep/expand the AABB along the motion path
	//

	hkVector4 invPath; invPath.setSub( motionState->getSweptTransform().m_centerOfMass0, motionState->getSweptTransform().m_centerOfMass1 );
	hkVector4 zero; zero.setZero();
	hkVector4 minPath; minPath.setMin( zero, invPath );
	hkVector4 maxPath; maxPath.setMax( zero, invPath );

	aabbOut.m_min.add( minPath );
	aabbOut.m_max.add( maxPath );

#if defined(HK_DEBUG)
	hkReal diffMinX = aabbIn.m_min(0) - aabbOut.m_min(0);
	hkReal diffMinY = aabbIn.m_min(1) - aabbOut.m_min(1);
	hkReal diffMinZ = aabbIn.m_min(2) - aabbOut.m_min(2);
	hkReal diffMaxX = aabbOut.m_max(0) - aabbIn.m_max(0);
	hkReal diffMaxY = aabbOut.m_max(1) - aabbIn.m_max(1);
	hkReal diffMaxZ = aabbOut.m_max(2) - aabbIn.m_max(2);
	HK_ASSERT2( 0xaf63e413, diffMinX >= 0.0f && diffMinY >= 0.0f && diffMinZ >= 0.0f && diffMaxX >= 0.0f && diffMaxY >= 0.0f && diffMaxZ >= 0.0f, "Expanded AABB is smaller than the unexpanded AABB." );
#endif
}


HK_ON_CPU( HK_FORCE_INLINE void HK_CALL sweepOffsetAabb(const OffsetAabbInput& input, const hkAabb& aabbIn, hkAabb& aabbOut) )
HK_ON_SPU( HK_FORCE_INLINE void HK_CALL hkAabbUtil_sweepOffsetAabb(const OffsetAabbInput& input, const hkAabb& aabbIn, hkAabb& aabbOut) )
{
	hkSimdReal half = hkSimdReal_Half;
	hkVector4 aabbHalfSize; aabbHalfSize.setSub(aabbIn.m_max, aabbIn.m_min);  aabbHalfSize.mul(half);
	hkVector4 aabbCenter; aabbCenter.setInterpolate(aabbIn.m_max, aabbIn.m_min, half);
	hkVector4 arm; arm._setTransformedPos(input.m_endTransformInv, aabbCenter);


	hkVector4 min = aabbCenter;
	hkVector4 max = aabbCenter;
	{
		hkVector4 p; p._setTransformedPos(input.m_startTransform, arm);
		min.setMin(min, p);
		max.setMax(max, p);
	}

	// extended arm for the in-between transforms (cos(22.5deg)
	const hkVector4 centerOfMassLocal = input.m_motionState->getSweptTransform().m_centerOfMassLocal;

	for (int i = 0; i < input.m_numTransforms; i++)
	{	
		hkVector4 extendedArm;
		extendedArm.setSub(arm, centerOfMassLocal);
		extendedArm.mul(input.m_transforms[i].getTranslation().getComponent<3>());
		extendedArm.add(centerOfMassLocal);

		hkVector4 p; p._setTransformedPos(input.m_transforms[i], extendedArm);
		min.setMin(min, p);
		max.setMax(max, p);
	}

	//
	// Expand the AABB due to angular rotation of the shape around the aabbIn's center
	//
	{
		hkSimdReal r = aabbHalfSize.length<3>();
		hkVector4 radius; radius.setAll(r);

		// Limit increase to largest expansion that is actually possible: (sqrt(3)-1) * r
		hkSimdReal limit; limit.setFromFloat(0.732050808f);
		
		r.setMin( input.m_motionState->m_deltaAngle.getComponent<3>(), limit * r );

		aabbHalfSize.addMul(r, radius);
		aabbHalfSize.setMin(radius, aabbHalfSize);
	}

	aabbOut.m_min.setSub(min, aabbHalfSize);
	aabbOut.m_max.setAdd(max, aabbHalfSize);

	// We need to ensure that in order for our hkAabbUint32 compression to work
	aabbOut.m_min.setMin(aabbIn.m_min, aabbOut.m_min);
	aabbOut.m_max.setMax(aabbIn.m_max, aabbOut.m_max);
}

HK_FORCE_INLINE void HK_CALL convertAabbToUint32( const hkAabb& aabb, hkVector4Parameter offsetLow, hkVector4Parameter offsetHigh, hkVector4Parameter scale, hkAabbUint32& aabbOut )
{
	HK_MATH_ASSERT(0x4868f301,  aabb.isValid(), "AABB at " << &aabb << " was invalid. (Contains a NaN or min > max)");

	hkVector4 maxVal; maxVal.m_quad = hkAabbUint32MaxVal;
	hkVector4 zero; zero.setZero();
	hkVector4Util::convertToUint32WithClip( aabb.m_min, offsetLow,  scale, zero, maxVal, aabbOut.m_min );
	hkVector4Util::convertToUint32WithClip( aabb.m_max, offsetHigh, scale, zero, maxVal, aabbOut.m_max );
}

//Based on void hkp3AxisSweep::getAabbFromNode(const hkpBpNode& node, hkAabb & aabb) const
HK_FORCE_INLINE void HK_CALL convertAabbFromUint32( const hkAabbUint32& aabbIn, hkVector4Parameter offsetLow, hkVector4Parameter scale, hkAabb& aabbOut)
{
	hkIntVector intAabbMin; intAabbMin.load<3>( &aabbIn.m_min[0] );
	hkIntVector intAabbMax; intAabbMax.load<3>( &aabbIn.m_max[0] );
	intAabbMin.convertS32ToF32(aabbOut.m_min);
	intAabbMax.convertS32ToF32(aabbOut.m_max);

	hkVector4 invScale;
	invScale.setReciprocal(scale); 
	invScale.setComponent<3>(hkSimdReal_1);

	aabbOut.m_min.mul(invScale);
	aabbOut.m_max.mul(invScale);

	aabbOut.m_min.sub(offsetLow);
	aabbOut.m_max.sub(offsetLow);
}


HK_FORCE_INLINE void HK_CALL compressExpandedAabbUint32(const hkAabbUint32& expandedAabbInt, hkAabbUint32& unexpandedAabbInt_InOut)
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED) && HK_ENDIAN_LITTLE
	hkIntVector mi,ma;
	{
		hkIntVector unexpandedAabbMin; unexpandedAabbMin.load<3>(&unexpandedAabbInt_InOut.m_min[0]);
		hkIntVector unexpandedAabbMax; unexpandedAabbMax.load<3>(&unexpandedAabbInt_InOut.m_max[0]);
		hkIntVector   expandedAabbMin;   expandedAabbMin.load<3>(&expandedAabbInt.m_min[0]);
		hkIntVector   expandedAabbMax;   expandedAabbMax.load<3>(&expandedAabbInt.m_max[0]);

		mi.setSubU32(unexpandedAabbMin, expandedAabbMin);
		ma.setSubU32(expandedAabbMax, unexpandedAabbMax);
	}

	hkInt32 m;
	{
		hkIntVector mv; mv.setOr(mi,ma);
		hkIntVector p; 
		p.setPermutation<hkVectorPermutation::YXZW>(mv); mv.setOr(mv,p);
		p.setPermutation<hkVectorPermutation::ZWXY>(mv); mv.setOr(mv,p);
		m = mv.getU32<0>();
	}

	HK_MATH_ASSERT( 0xf0ed3454, m >= 0, "Your expanded AABB is smaller than the unexpanded AABB" );
	hkInt32 shift = 24 - hkMath::countLeadingZeros(m | 0xff);
	HK_MATH_ASSERT( 0xf0ed345c, shift < 256, "Shift overflow" );

	{
		hkIntVector outMin; 
		outMin.setShiftRight32(mi, shift);
		outMin.setComponent<3>(shift);
		outMin.setConvertSaturateS32ToS16(outMin,outMin);
		outMin.setConvertSaturateS16ToU8(outMin,outMin);
		outMin.storeNotAligned<1>((hkUint32*)&unexpandedAabbInt_InOut.m_expansionMin[0]); // write 3x expansionMin 1x expansionShift
	}
	{
		hkIntVector outMax; 
		outMax.setShiftRight32(ma, shift);
		outMax.setComponent<3>(hkInt32(unexpandedAabbInt_InOut.m_shapeKeyByte));
		outMax.setConvertSaturateS32ToS16(outMax,outMax);
		outMax.setConvertSaturateS16ToU8(outMax,outMax);
		outMax.storeNotAligned<1>((hkUint32*)&unexpandedAabbInt_InOut.m_expansionMax[0]); // write 3x expansionMax 1x shapeKeyByte
	}
#else
	hkInt32 mix = unexpandedAabbInt_InOut.m_min[0] - expandedAabbInt.m_min[0];
	hkInt32 miy = unexpandedAabbInt_InOut.m_min[1] - expandedAabbInt.m_min[1];
	hkInt32 miz = unexpandedAabbInt_InOut.m_min[2] - expandedAabbInt.m_min[2];
	hkInt32 maxx= expandedAabbInt.m_max[0] - unexpandedAabbInt_InOut.m_max[0];
	hkInt32 may = expandedAabbInt.m_max[1] - unexpandedAabbInt_InOut.m_max[1];
	hkInt32 maz = expandedAabbInt.m_max[2] - unexpandedAabbInt_InOut.m_max[2];

	hkInt32 m = (mix | miy) | (miz | maxx) | (may | maz);
	HK_MATH_ASSERT( 0xf0ed3454, m >= 0, "Your expanded AABB is smaller than the unexpanded AABB" );
	int shift = 0;
	while ( m >=  0x800){ shift += 4; m = unsigned(m) >> 4; };
	while ( m >=  0x100){ shift += 1; m = unsigned(m) >> 1; };

	unexpandedAabbInt_InOut.m_expansionShift = hkUchar(shift);
	unexpandedAabbInt_InOut.m_expansionMin[0] = hkUchar(mix >> shift);
	unexpandedAabbInt_InOut.m_expansionMin[1] = hkUchar(miy >> shift);
	unexpandedAabbInt_InOut.m_expansionMin[2] = hkUchar(miz >> shift);
	unexpandedAabbInt_InOut.m_expansionMax[0] = hkUchar(maxx >> shift);
	unexpandedAabbInt_InOut.m_expansionMax[1] = hkUchar(may >> shift);
	unexpandedAabbInt_InOut.m_expansionMax[2] = hkUchar(maz >> shift);
#endif
}


HK_FORCE_INLINE void HK_CALL uncompressExpandedAabbUint32(const hkAabbUint32& unexpandedAabbInt, hkAabbUint32& expandedAabbOut)
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED) && HK_ENDIAN_LITTLE && ! defined(HK_COMPILER_GCC)
	hkIntVector zero; zero.setZero();
	hkUint32 shift;

	{
		hkIntVector expansion; 
		expansion.loadNotAligned<1>((const hkUint32*)&unexpandedAabbInt.m_expansionMin[0]); // 3x expansionMin 1x expansionShift
		expansion.setMergeHead8(expansion,zero); 
		expansion.setMergeHead16(expansion,zero);
		shift = expansion.getComponent<3>();
		hkIntVector shiftedExpansion; shiftedExpansion.setShiftLeft32(expansion,shift);
		hkIntVector unexpandedAabb; unexpandedAabb.load<3>(&unexpandedAabbInt.m_min[0]);
		hkIntVector expandedAabb; expandedAabb.setSubU32(unexpandedAabb, shiftedExpansion);
		expandedAabb.store<3>(&expandedAabbOut.m_min[0]);
	}
	{
		hkIntVector expansion; 
		expansion.loadNotAligned<1>((const hkUint32*)&unexpandedAabbInt.m_expansionMax[0]); // 3x expansionMax 1x shapeKeyByte
		expansion.setMergeHead8(expansion,zero); 
		expansion.setMergeHead16(expansion,zero);
		hkIntVector shiftedExpansion; shiftedExpansion.setShiftLeft32(expansion,shift);
		hkIntVector unexpandedAabb; unexpandedAabb.load<3>(&unexpandedAabbInt.m_max[0]);
		hkIntVector expandedAabb; expandedAabb.setAddU32(unexpandedAabb, shiftedExpansion);
		expandedAabb.store<3>(&expandedAabbOut.m_max[0]);
	}
#else
	const int shift = unexpandedAabbInt.m_expansionShift;
	hkUint32 mix = unexpandedAabbInt.m_min[0] - (unexpandedAabbInt.m_expansionMin[0] << shift);
	hkUint32 miy = unexpandedAabbInt.m_min[1] - (unexpandedAabbInt.m_expansionMin[1] << shift);
	hkUint32 miz = unexpandedAabbInt.m_min[2] - (unexpandedAabbInt.m_expansionMin[2] << shift);
	expandedAabbOut.m_min[0]= mix;
	expandedAabbOut.m_min[1]= miy;
	expandedAabbOut.m_min[2]= miz;

	hkUint32 maxx = unexpandedAabbInt.m_max[0] + (unexpandedAabbInt.m_expansionMax[0] << shift);
	hkUint32 may  = unexpandedAabbInt.m_max[1] + (unexpandedAabbInt.m_expansionMax[1] << shift);
	hkUint32 maz  = unexpandedAabbInt.m_max[2] + (unexpandedAabbInt.m_expansionMax[2] << shift);
	expandedAabbOut.m_max[0]= maxx;
	expandedAabbOut.m_max[1]= may;
	expandedAabbOut.m_max[2]= maz;
#endif
}


} // namespace hkAabbUtil

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
