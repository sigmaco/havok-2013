/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

namespace hkSweptTransformUtil
{

HK_FORCE_INLINE void HK_CALL _lerp2( const hkSweptTransformd& sweptTrans, hkDouble64 t, hkQuaterniond& quatOut )
{
	_lerp2(sweptTrans, hkSimdDouble64::fromFloat(t), quatOut);
}

HK_FORCE_INLINE void HK_CALL _lerp2( const hkSweptTransformd& sweptTrans, hkSimdDouble64Parameter st, hkQuaterniond& quatOut )
{
	hkVector4d rot0 = sweptTrans.m_rotation0.m_vec;
	hkVector4d rot1 = sweptTrans.m_rotation1.m_vec;
	const hkSimdDouble64 half = hkSimdDouble64_Inv2;
	const hkSimdDouble64 two = hkSimdDouble64_2;
	const hkSimdDouble64 one = hkSimdDouble64_1;
	{
		quatOut.m_vec.setAdd( rot0, rot1 );
		const hkSimdDouble64 len2 = quatOut.m_vec.lengthSquared<4>();
		hkSimdDouble64 threequarter; threequarter.setFromFloat(0.75f);
		hkSimdDouble64 oneeighth; oneeighth.setFromFloat(0.125f);
		hkSimdDouble64 r = threequarter - oneeighth * len2;
		r = r * ((one + half) - half * len2 * r * r);
		quatOut.m_vec.mul(r);
	}

	if ( st < half )
	{
		quatOut.m_vec.setInterpolate( rot0, quatOut.m_vec, st * two);
	}
	else
	{
		quatOut.m_vec.setInterpolate( quatOut.m_vec, rot1, (two * st) - one);
	}
	quatOut.normalize();
}


HK_FORCE_INLINE void HK_CALL _lerp2( const hkSweptTransformd& sweptTrans, hkDouble64 t, hkTransformd& transformOut )
{
	_lerp2(sweptTrans, hkSimdDouble64::fromFloat(t), transformOut);
}

HK_FORCE_INLINE void HK_CALL _lerp2( const hkSweptTransformd& sweptTrans, hkSimdDouble64Parameter t, hkTransformd& transformOut )
{
	hkQuaterniond qt;
	_lerp2( sweptTrans, t, qt );

	transformOut.setRotation( qt );
	transformOut.getTranslation().setInterpolate( sweptTrans.m_centerOfMass0, sweptTrans.m_centerOfMass1, t);

	hkVector4d centerShift;
	centerShift._setRotatedDir( transformOut.getRotation(), sweptTrans.m_centerOfMassLocal);
	transformOut.getTranslation().sub( centerShift );
}


HK_FORCE_INLINE void HK_CALL calcTransAtT0( const hkSweptTransformd& sweptTrans, hkTransformd& transformOut )
{
	const hkQuaterniond& qt = sweptTrans.m_rotation0;

	transformOut.setRotation( qt );

	hkVector4d centerShift;
	centerShift._setRotatedDir( transformOut.getRotation(), sweptTrans.m_centerOfMassLocal);
	transformOut.getTranslation().setSub( sweptTrans.m_centerOfMass0, centerShift );
}


HK_FORCE_INLINE void HK_CALL calcTransAtT1( const hkSweptTransformd& sweptTrans, hkTransformd& transformOut )
{
	const hkQuaterniond& qt = sweptTrans.m_rotation1;

	transformOut.setRotation( qt );

	hkVector4d centerShift;
	centerShift._setRotatedDir( transformOut.getRotation(), sweptTrans.m_centerOfMassLocal);
	transformOut.getTranslation().setSub( sweptTrans.m_centerOfMass1, centerShift );
}

#	if defined(HK_REAL_IS_DOUBLE)

HK_FORCE_INLINE void HK_CALL _clipVelocities( const hkMotionState& motionState, hkVector4d& linearVelocity, hkVector4d& angularVelocity )
{
	const hkSimdDouble64 linVelSq = linearVelocity.lengthSquared<3>();
	const hkSimdDouble64 angVelSq = angularVelocity.lengthSquared<3>();
	hkSimdDouble64 maxLinear; maxLinear = hkSimdDouble64::fromFloat(hkDouble64(motionState.m_maxLinearVelocity));
	const hkSimdDouble64 maxLinear2 = maxLinear * maxLinear;
	hkSimdDouble64 maxAngularRadians; maxAngularRadians = hkSimdDouble64::fromFloat(hkDouble64(motionState.m_maxAngularVelocity)); 
	const hkSimdDouble64 maxAngularRadians2 = maxAngularRadians * maxAngularRadians;

	if ( (linVelSq > maxLinear2) || (linVelSq!=linVelSq) )
	{
		const hkSimdDouble64 f = maxLinear * linVelSq.sqrtInverse();
		linearVelocity.mul( f );
		if ( linVelSq!=linVelSq )
		{
			linearVelocity = hkVector4d::getConstant<HK_QUADREAL_1000>();
			HK_ASSERT2(0xf0124242, false, "NaN velocity detected, something is seriously wrong (bad inertia tensors?)");
		}
	}
	if ((angVelSq > maxAngularRadians2) || ( angVelSq != angVelSq ))
	{
		const hkSimdDouble64 f = maxAngularRadians * angVelSq.sqrtInverse();
		angularVelocity.mul( f );
		if ( angVelSq!=angVelSq )
		{
			angularVelocity = hkVector4d::getConstant<HK_QUADREAL_1000>();
			HK_ASSERT2(0xf0143243, false, "NaN velocity detected, something is seriously wrong (bad inertia tensors?)");
		}
	}
}


HK_FORCE_INLINE void HK_CALL _stepMotionState( const hkStepInfo& info,
											 hkVector4d& linearVelocity, hkVector4d& angularVelocity,
											 hkMotionState& motionState )
{
	hkSimdDouble64	deltaTime; deltaTime.setFromFloat( info.m_deltaTime.val() * motionState.m_timeFactor );
#ifdef HK_DEBUG
	{
		if ( motionState.getSweptTransform().getInvDeltaTime() != hkDouble64(0))
		{
			hkDouble64 motionEndTime = motionState.getSweptTransform().getBaseTime() + hkDouble64(1) / motionState.getSweptTransform().getInvDeltaTime();
			HK_ASSERT(0xf0f0083, hkMath::equal(info.m_startTime, motionEndTime ) ) ;
		}
	}
#endif
	// check for nans in velocities
	// fix nans to (1,0,0)
	{
		hkVector4d absLin; absLin.setAbs( linearVelocity );
		hkVector4d absAng; absAng.setAbs( angularVelocity );

		hkVector4d maxVel; maxVel.m_quad = _stepMotionStateMaxVeld;

		hkVector4dComparison isNormal = absLin.less( maxVel );
		isNormal.setAnd( isNormal, absAng.less( maxVel ) );
		isNormal.setAnd( isNormal, linearVelocity.equal( linearVelocity ) );
		isNormal.setAnd( isNormal, angularVelocity.equal( angularVelocity ) );

		if ( !isNormal.allAreSet<hkVector4ComparisonMask::MASK_XYZ>() )
		{
			// velocity to a 'random' non zero velocity
			const hkVector4d id0 = hkVector4d::getConstant<HK_QUADREAL_1000>();
			linearVelocity  = id0;
			angularVelocity = id0;
		}
	}

	{
		hkSimdDouble64 startT; startT.setFromFloat(info.m_startTime.val());
		motionState.getSweptTransform().m_centerOfMass0.setXYZ_W( motionState.getSweptTransform().m_centerOfMass1, startT );
	}

	{
		hkSimdDouble64 stateMaxLin; stateMaxLin.setFromFloat(hkDouble64(motionState.m_maxLinearVelocity));
		const hkSimdDouble64 linVelSq = linearVelocity.lengthSquared<3>();
		if ( linVelSq > stateMaxLin * stateMaxLin )
		{
			//HK_WARN_ONCE(0xf0327683, "Object exceeding maximum velocity, velocity clipped" );
			const hkSimdDouble64 f = stateMaxLin * linVelSq.sqrtInverse<HK_ACC_23_BIT,HK_SQRT_IGNORE>();
			linearVelocity.mul( f );
		}
	}

	motionState.getSweptTransform().m_centerOfMass1.addMul(deltaTime, linearVelocity);
	motionState.getSweptTransform().m_centerOfMass1(3) = info.m_invDeltaTime.val();

	hkQuaterniond newRotation = motionState.getSweptTransform().m_rotation1;
	motionState.getSweptTransform().m_rotation0 = newRotation;

	//
	//	Calculate a new rotation, the fabs angle and angle squared
	//
	{
		hkQuaterniond rotationRadians;	rotationRadians.m_vec.setMul( deltaTime * hkSimdReal_Inv2 , angularVelocity );
		hkSimdDouble64 numHalfRotations2 = rotationRadians.m_vec.lengthSquared<3>() * hkSimdDouble64::fromFloat(hkDouble64(4) / (HK_DOUBLE_PI*HK_DOUBLE_PI));

		
		const hkSimdDouble64 a = hkSimdDouble64::fromFloat(0.822948f);
		const hkSimdDouble64 b = hkSimdDouble64::fromFloat(0.130529f);
		const hkSimdDouble64 c = hkSimdDouble64::fromFloat(0.044408f);

		hkSimdDouble64 maxAngleHalfRotations; maxAngleHalfRotations.setMin( hkSimdDouble64::fromFloat(0.9f), ( deltaTime * hkSimdDouble64::fromFloat(hkDouble64(motionState.m_maxAngularVelocity)) ) / hkSimdDouble64::getConstant<HK_QUADREAL_PI>() );

		// clipping angular velocity to be between [0, PI*0.9/dt]
		// info: was "<", is "<=" -- works ok for zero dt now.
		if ( numHalfRotations2 <= maxAngleHalfRotations * maxAngleHalfRotations )
		{
			const hkSimdDouble64 numHalfRotations4 = numHalfRotations2 * numHalfRotations2;
			const hkSimdDouble64 w = hkSimdDouble64::getConstant<HK_QUADREAL_1>() - a * numHalfRotations2 - b * numHalfRotations4 - c * numHalfRotations2 * numHalfRotations4;
			rotationRadians.m_vec.setW(w);
		}
		else
		{
			const hkSimdDouble64 factor = maxAngleHalfRotations * numHalfRotations2.sqrtInverse();
			angularVelocity.mul( factor );
			rotationRadians.m_vec.mul( factor );

			numHalfRotations2  = maxAngleHalfRotations * maxAngleHalfRotations;
			const hkSimdDouble64 numHalfRotations4  = numHalfRotations2 * numHalfRotations2;
			const hkSimdDouble64 w = hkSimdDouble64::getConstant<HK_QUADREAL_1>() - a * numHalfRotations2 - b * numHalfRotations4 - c * numHalfRotations2 * numHalfRotations4;
			rotationRadians.m_vec.setW(w);
		}

		newRotation.setMul( rotationRadians, newRotation );
		newRotation.normalize();

		motionState.m_deltaAngle.setAdd( rotationRadians.m_vec, rotationRadians.m_vec );
		const hkSimdDouble64 angle = numHalfRotations2.sqrt() * hkSimdDouble64::getConstant<HK_QUADREAL_PI>();
		motionState.m_deltaAngle.setW(angle);
	}
	motionState.getSweptTransform().m_rotation1 = newRotation;
	calcTransAtT1( motionState.getSweptTransform(), motionState.getTransform());
}







HK_FORCE_INLINE void HK_CALL deactivate( hkMotionState& ms )
{
	hkSweptTransformd& sweptTransform = ms.getSweptTransform();
	ms.m_deltaAngle.setZero();

	sweptTransform.m_rotation0 = sweptTransform.m_rotation1;
	sweptTransform.m_centerOfMass0 = sweptTransform.m_centerOfMass1;
	sweptTransform.m_centerOfMass1.zeroComponent<3>();
}



//HK_FORCE_INLINE void HK_CALL calcTimInfo( const hkMotionState& ms0, const hkMotionState& ms1, hkVector4d& timOut)
//{
//	HK_ASSERT2(0xad44d321, st0.getInvDeltaTime() == st1.getInvDeltaTime(), "Internal error: hkSweptTransformd's must correspond to the same deltaTime in order to use void HK_CALL calcTimInfo( const hkMotionState& ms0, const hkMotionState& ms1, hkVector4d& timOut)");
//
//	const hkSweptTransformd& st0 = ms0.getSweptTransform();
//	const hkSweptTransformd& st1 = ms1.getSweptTransform();
//
//	hkVector4d diff0; diff0.setSub( st0.m_centerOfMass0, st0.m_centerOfMass1 );
//	hkVector4d diff1; diff1.setSub( st1.m_centerOfMass1, st1.m_centerOfMass0 );
//
//	timOut.setAdd( diff0, diff1 );
//
//	timOut(3) = ms0.m_deltaAngle(3) * ms0.m_objectRadius + ms1.m_deltaAngle(3) * ms1.m_objectRadius;
//
//}

HK_FORCE_INLINE void HK_CALL calcTimInfo( const hkMotionState& ms0, const hkMotionState& ms1, hkDouble64 deltaTime, hkVector4d& timOut)
{
	const hkSweptTransformd& st0 = ms0.getSweptTransform();
	const hkSweptTransformd& st1 = ms1.getSweptTransform();

	hkVector4d diff0; diff0.setSub( st0.m_centerOfMass0, st0.m_centerOfMass1 );
	hkVector4d diff1; diff1.setSub( st1.m_centerOfMass1, st1.m_centerOfMass0 );

	hkSimdDouble64 dt; dt.setFromFloat(deltaTime);
	const hkSimdDouble64 f0 = dt * st0.getInvDeltaTimeSr();
	const hkSimdDouble64 f1 = dt * st1.getInvDeltaTimeSr();

	HK_ASSERT2(0xad56daaa, f0.getReal() <= hkDouble64(1.01f) && f1.getReal() <= hkDouble64(1.01f), "Internal error: input for TIM calculation may be corrupted.");

	timOut.setMul( f0, diff0 );
	timOut.addMul( f1, diff1 );
	timOut.setW(f0 * ms0.m_deltaAngle.getComponent<3>() * hkSimdDouble64::fromFloat(ms0.m_objectRadius) +
				f1 * ms1.m_deltaAngle.getComponent<3>() * hkSimdDouble64::fromFloat(ms1.m_objectRadius) );

	// we don't project angular velocity just to keep it simple ( no cross products)
}

	// Calculates angular distance (angVelocity * dt) travelled by the bodies. 
HK_FORCE_INLINE void HK_CALL calcAngularTimInfo( const hkMotionState& ms0, const hkMotionState& ms1, hkDouble64 deltaTime, hkVector4d* HK_RESTRICT deltaAngleOut0, hkVector4d* HK_RESTRICT deltaAngleOut1)
{
	const hkSweptTransformd& st0 = ms0.getSweptTransform();
	const hkSweptTransformd& st1 = ms1.getSweptTransform();
	hkSimdDouble64 dt; dt.setFromFloat(deltaTime);
	const hkSimdDouble64 f0 = dt * st0.getInvDeltaTimeSr();
	const hkSimdDouble64 f1 = dt * st1.getInvDeltaTimeSr();

	hkVector4d ang0; ang0.setMul( f0, ms0.m_deltaAngle );
	hkVector4d ang1; ang1.setMul( f1, ms1.m_deltaAngle );

	deltaAngleOut0[0] = ang0;
	deltaAngleOut1[0] = ang1;
}

HK_FORCE_INLINE void HK_CALL calcCenterOfMassAt( const hkMotionState& ms, hkSimdDouble64Parameter t, hkVector4d& centerOut )
{
	const hkSimdDouble64 iv = ms.getSweptTransform().getInterpolationValue(t);
	centerOut.setInterpolate( ms.getSweptTransform().m_centerOfMass0, ms.getSweptTransform().m_centerOfMass1, iv );
}

HK_FORCE_INLINE void HK_CALL calcCenterOfMassAt( const hkMotionState& ms, hkTime t, hkVector4d& centerOut )
{
	calcCenterOfMassAt(ms, hkSimdDouble64::fromFloat(t), centerOut);
}

HK_FORCE_INLINE void HK_CALL getVelocity( const hkMotionState& ms, hkVector4d& linearVelOut, hkVector4d& angularVelOut )
{
	linearVelOut.setSub (ms.getSweptTransform().m_centerOfMass1, ms.getSweptTransform().m_centerOfMass0);
	const hkSimdDouble64 idt = ms.getSweptTransform().getInvDeltaTimeSr();
	linearVelOut.mul( idt );
	angularVelOut.setMul( idt, ms.m_deltaAngle );
}

#endif // defined(HK_REAL_IS_DOUBLE)

} // namespace hkSweptTransformUtil

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
