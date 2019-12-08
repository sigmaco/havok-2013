/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */


HK_FORCE_INLINE hkTime hkSweptTransformf::getBaseTime() const
{
	return hkTime(m_centerOfMass0(3));
}

HK_FORCE_INLINE hkSimdFloat32 hkSweptTransformf::getBaseTimeSr() const
{
	return m_centerOfMass0.getComponent<3>();
}

HK_FORCE_INLINE hkFloat32 hkSweptTransformf::getInvDeltaTime() const 
{
	return m_centerOfMass1(3);
}

HK_FORCE_INLINE hkSimdFloat32 hkSweptTransformf::getInvDeltaTimeSr() const 
{
	return m_centerOfMass1.getComponent<3>();
}

#define HK_SWEPT_TRANSFORMf_ASSERT_STRING "Disable this assert if it gets fired from your user code. It is only used to check internal consistency."

HK_FORCE_INLINE hkFloat32 hkSweptTransformf::getInterpolationValue( hkTime t ) const
{
	HK_MATH_ASSERT(0xf0ff0080, getInvDeltaTime() == hkFloat32(0) || getInvDeltaTime() > hkFloat32(0.01f), "hkSweptTransforms time period (which corresponds to simulation-step deltaTime) is neither set to infinity (as for fixed/not-integrated motion) nor is less than 100 seconds.");
	hkFloat32 dt = hkFloat32((t - getBaseTime()) * getInvDeltaTime());
	//HK_MATH_ASSERT(0xf0ff0080, hkMath::isFinite(dt), HK_SWEPT_TRANSFORMf_ASSERT_STRING);
	HK_MATH_ASSERT(0xf0ff0080, dt >= hkFloat32(0),  HK_SWEPT_TRANSFORMf_ASSERT_STRING);
	HK_MATH_ASSERT(0xf0ff0080, dt <= hkFloat32(1.01f), HK_SWEPT_TRANSFORMf_ASSERT_STRING);
	return dt;
}

HK_FORCE_INLINE hkSimdFloat32 hkSweptTransformf::getInterpolationValue( hkSimdFloat32Parameter t ) const
{
	HK_MATH_ASSERT(0xf0ff0080, getInvDeltaTime() == hkFloat32(0) || getInvDeltaTime() > hkFloat32(0.01f), "hkSweptTransforms time period (which corresponds to simulation-step deltaTime) is neither set to infinity (as for fixed/not-integrated motion) nor is less than 100 seconds.");
	hkSimdFloat32 dt = (t - getBaseTimeSr()) * getInvDeltaTimeSr();
	//HK_MATH_ASSERT(0xf0ff0080, hkMath::isFinite(dt), HK_SWEPT_TRANSFORMf_ASSERT_STRING);
	HK_MATH_ASSERT(0xf0ff0080, dt.isGreaterEqualZero(),  HK_SWEPT_TRANSFORMf_ASSERT_STRING);
	HK_MATH_ASSERT(0xf0ff0080, dt.getReal() <= hkFloat32(1.01f), HK_SWEPT_TRANSFORMf_ASSERT_STRING);
	return dt;
}

HK_FORCE_INLINE hkFloat32 hkSweptTransformf::getInterpolationValueHiAccuracy( hkTime t, hkFloat32 deltaTimeAddon ) const
{
	HK_MATH_ASSERT(0xad67fa3a, getInvDeltaTime() == hkFloat32(0) || getInvDeltaTime() > hkFloat32(0.01f), "hkSweptTransforms time period (which corresponds to simulation-step deltaTime) is neither set to infinity (as for fixed/not-integrated motion) nor is less than 100 seconds.");
	hkFloat32 dt = hkFloat32(t - getBaseTime());
	dt += deltaTimeAddon;
	hkFloat32 ddt = dt * getInvDeltaTime();
	//HK_MATH_ASSERT(0xad67fa3a, hkMath::isFinite(ddt), HK_SWEPT_TRANSFORMf_ASSERT_STRING);
	HK_MATH_ASSERT(0xad67fa3a, ddt >= hkFloat32(0),  HK_SWEPT_TRANSFORMf_ASSERT_STRING);
	HK_MATH_ASSERT(0xad67fa3a, ddt <= hkFloat32(1.01f), HK_SWEPT_TRANSFORMf_ASSERT_STRING);
	return ddt;
}

HK_FORCE_INLINE hkSimdFloat32 hkSweptTransformf::getInterpolationValueHiAccuracy( hkSimdFloat32Parameter t, hkSimdFloat32Parameter deltaTimeAddon ) const
{
	HK_MATH_ASSERT(0xad67fa3a, getInvDeltaTime() == hkFloat32(0) || getInvDeltaTime() > hkFloat32(0.01f), "hkSweptTransforms time period (which corresponds to simulation-step deltaTime) is neither set to infinity (as for fixed/not-integrated motion) nor is less than 100 seconds.");
	const hkSimdFloat32 dt = t - getBaseTimeSr() + deltaTimeAddon;
	const hkSimdFloat32 ddt = dt * getInvDeltaTimeSr();
	//HK_MATH_ASSERT(0xad67fa3a, hkMath::isFinite(ddt), HK_SWEPT_TRANSFORMf_ASSERT_STRING);
	HK_MATH_ASSERT(0xad67fa3a, ddt.isGreaterEqualZero(),  HK_SWEPT_TRANSFORMf_ASSERT_STRING);
	HK_MATH_ASSERT(0xad67fa3a, ddt.getReal() <= hkFloat32(1.01f), HK_SWEPT_TRANSFORMf_ASSERT_STRING);
	return ddt;
}

HK_FORCE_INLINE void hkSweptTransformf::_approxTransformAt( hkTime t, hkTransformf& transformOut ) const 
{
	_approxTransformAt(hkSimdFloat32::fromFloat(hkFloat32(t)),transformOut);
}

HK_FORCE_INLINE void hkSweptTransformf::_approxTransformAt( hkSimdFloat32Parameter t, hkTransformf& transformOut ) const 
{
	const hkSimdFloat32 dt = getInterpolationValue(t);

	hkQuaternionf q;
	q.m_vec.setInterpolate( m_rotation0.m_vec, m_rotation1.m_vec, dt );
	q.normalize();

	transformOut.setRotation( q );
	transformOut.getTranslation().setInterpolate( m_centerOfMass0, m_centerOfMass1, dt);

	hkVector4f centerShift;
	centerShift._setRotatedDir( transformOut.getRotation(), m_centerOfMassLocal);
	transformOut.getTranslation().sub( centerShift );
}

#undef HK_SWEPT_TRANSFORMf_ASSERT_STRING

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
