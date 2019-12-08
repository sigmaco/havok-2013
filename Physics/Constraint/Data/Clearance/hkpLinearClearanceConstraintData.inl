/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

inline void hkpLinearClearanceConstraintData::allowRotationAroundPrismaticAxis(bool allowRotation)
{
	if (allowRotation)
	{
		// We unfix rotation along the prismatic constraint's axis. Meaning, we change it into a cylindrical constraint.
		m_atoms.m_ang.m_firstConstrainedAxis = 1; // Originally was 0. 0 is the direction of the shaft axis.
		m_atoms.m_ang.m_numConstrainedAxes = 2; // Originally was 3. And was constraining all 3 axes of rotation.
	}
	else
	{
		m_atoms.m_ang.m_firstConstrainedAxis = 0; // Originally was 0. 0 is the direction of the shaft axis.
		m_atoms.m_ang.m_numConstrainedAxes = 3; // Originally was 3. And was constraining all 3 axes of rotation.
	}
}

inline void hkpLinearClearanceConstraintData::setLimits(hkReal min0, hkReal max0, hkReal min1, hkReal max1, hkReal min2, hkReal max2)
{
	m_atoms.m_linLimit0.m_min = min0;
	m_atoms.m_linLimit0.m_max = max0;
	m_atoms.m_linLimit1.m_min = min1;
	m_atoms.m_linLimit1.m_max = max1;
	m_atoms.m_linLimit2.m_min = min2;
	m_atoms.m_linLimit2.m_max = max2;
}

inline void hkpLinearClearanceConstraintData::setMaxFrictionForce(hkReal fmag)
{
	m_atoms.m_friction0.m_maxFrictionForce = fmag;	
	m_atoms.m_friction1.m_maxFrictionForce = fmag;	
	m_atoms.m_friction2.m_maxFrictionForce = fmag;	
}


inline hkReal hkpLinearClearanceConstraintData::getMaxFrictionForce() const
{
	return m_atoms.m_friction0.m_maxFrictionForce;
}

inline hkpConstraintMotor* hkpLinearClearanceConstraintData::getMotor() const
{
	return m_atoms.m_motor.m_motor;
}

inline hkBool hkpLinearClearanceConstraintData::isMotorEnabled() const
{
	return m_atoms.m_motor.m_isEnabled;
}

inline void hkpLinearClearanceConstraintData::setMotorTargetPosition( hkReal pos )
{
	m_atoms.m_motor.m_targetPosition = pos;
}

inline hkReal hkpLinearClearanceConstraintData::getMotorTargetPosition()
{
	return m_atoms.m_motor.m_targetPosition;
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
