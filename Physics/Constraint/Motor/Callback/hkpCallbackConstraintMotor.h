/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_CALLBACK_CONSTRAINT_MOTOR_H
#define HKP_CALLBACK_CONSTRAINT_MOTOR_H

#include <Physics/Constraint/Motor/LimitedForce/hkpLimitedForceConstraintMotor.h>

extern const hkClass hkpCallbackConstraintMotorClass;
class hkpConstraintMotorInput;
class hkpConstraintMotorOutput;

/// This motor simply tries to reach and keep a desired target velocity.
class hkpCallbackConstraintMotor : public hkpLimitedForceConstraintMotor
{
	public:

		typedef void (HK_CALL *CalcMotorDataCallbackFunc)(const class hkpCallbackConstraintMotor& motor, const hkpConstraintMotorInput* input, hkpConstraintMotorOutput* output);

		enum CallbackType
		{
			CALLBACK_MOTOR_TYPE_HAVOK_DEMO_SPRING_DAMPER,
			CALLBACK_MOTOR_TYPE_USER_0,
			CALLBACK_MOTOR_TYPE_USER_1,
			CALLBACK_MOTOR_TYPE_USER_2,
			CALLBACK_MOTOR_TYPE_USER_3,
		};

	public:
	
		HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CONSTRAINT );
		HK_DECLARE_REFLECTION();

		/// Construct a motor with the given properties.
		hkpCallbackConstraintMotor( enum CallbackType callbackType, CalcMotorDataCallbackFunc callbackFunc );

		/// Serialization constructor.
		hkpCallbackConstraintMotor( hkFinishLoadedObjectFlag f ) : hkpLimitedForceConstraintMotor(f)  {}

		/// Motor clone method
		virtual hkpConstraintMotor* clone() const;

	public:

		CalcMotorDataCallbackFunc m_callbackFunc; //+overridetype(void*) +nosave
		hkEnum<CallbackType,hkUint32> m_callbackType;
		hkUlong m_userData0; // +default(0)
		hkUlong m_userData1; // +default(0)
		hkUlong m_userData2; // +default(0)
};


#endif // HKP_CALLBACK_CONSTRAINT_MOTOR_H

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
