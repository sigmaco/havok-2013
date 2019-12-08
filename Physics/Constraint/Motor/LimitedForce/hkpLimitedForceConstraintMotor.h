/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_LIMITED_FORCE_CONSTRAINT_MOTOR_H
#define HKP_LIMITED_FORCE_CONSTRAINT_MOTOR_H

#include <Physics/Constraint/Motor/hkpConstraintMotor.h>

extern const class hkClass hkpLimitedForceConstraintMotorClass;
//extern const hkClass hkpLimitedForceConstraintMotorClass;


/// Takes 1DOF state as input, and calculates the data, which goes into the constraint solver
class hkpLimitedForceConstraintMotor : public hkpConstraintMotor
{
	public:

		//+abstract(1)
		HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CONSTRAINT );
		HK_DECLARE_REFLECTION();

		/// Constructor
		inline hkpLimitedForceConstraintMotor()
		{
			m_minForce = hkReal(-1e6f);
			m_maxForce = hkReal( 1e6f);
		}

		/// Serialization constructor
		hkpLimitedForceConstraintMotor( hkFinishLoadedObjectFlag f ) : hkpConstraintMotor(f) {}

		/// Helper function to set absolute max force applied to achieve the velocity target
		inline void setMaxForce( hkReal f ) { HK_ASSERT2(0x3f728237, f >= 0, "Max force must be a non-negative value."); m_minForce = -f; m_maxForce = f; }

		/// Helper function to set min and max forces applied to achieve the velocity target
		inline void setMinMaxForces( hkReal fMin, hkReal fMax ) { HK_ASSERT2(0x43a73169, fMin <= fMax, "Max force must be greater or equal to min force."); m_minForce = fMin; m_maxForce = fMax; }

	public:

		/// Minimum force exerted by the motor.
		hkReal m_minForce;

		/// Maximum force exerted by the motor.
		hkReal m_maxForce;
}; 


#endif // HKP_LIMITED_FORCE_CONSTRAINT_MOTOR_H

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
