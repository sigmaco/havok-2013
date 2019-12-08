/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_CONSTRAINT_MOTOR_H
#define HKP_CONSTRAINT_MOTOR_H

#include <Physics/ConstraintSolver/Solve/hkpSolverResults.h>

extern const hkClass hkpConstraintMotorClass; 


/// Takes 1DOF state as input, and calculates the data, which goes into the constraint solver.
class hkpConstraintMotor : public hkReferencedObject
{
	public:

		enum MotorType
		{
			TYPE_INVALID,
			TYPE_POSITION,
			TYPE_VELOCITY,
			TYPE_SPRING_DAMPER,
			TYPE_CALLBACK,
			TYPE_MAX
		};

	public:

		HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CONSTRAINT );
		HK_DECLARE_REFLECTION();

		/// Constructor
		inline hkpConstraintMotor() : m_type(TYPE_INVALID) {}

		/// Serialization constructor.
		hkpConstraintMotor(hkFinishLoadedObjectFlag f) : hkReferencedObject(f) {}

		/// Gets the type of the motor.
		inline MotorType getType() const { return m_type; }

		/// Clone the motor. As constraint data can be shared, but motors can't (normally, as they
		/// have per instance targets in them) we use a motor clone method to create new ones if required.
		virtual hkpConstraintMotor* clone() const = 0;

	public:

		hkEnum<MotorType, hkInt8> m_type;
}; 


//
class hkpMaxSizeConstraintMotor : public hkpConstraintMotor
{
	public:
	
		HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CONSTRAINT );

		hkpMaxSizeConstraintMotor() { m_type = TYPE_MAX; }

		virtual hkpConstraintMotor* clone() const  { HK_ASSERT2(0xad67ddab, false, "Dummy implementation used."); return HK_NULL; }
	
	public:

#if defined(HK_REAL_IS_DOUBLE)
		hkUint32 m_dummy[1+2*8];
#else
		// Padding up to 32 bytes
#	if HK_POINTER_SIZE == 4
		hkUint32 m_dummy[1+2*4];
#	else // HK_POINTER_SIZE == 8
		hkUint32 m_dummy[1+2*8];
#	endif
#endif
};


#endif // HKP_CONSTRAINT_MOTOR_H

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
