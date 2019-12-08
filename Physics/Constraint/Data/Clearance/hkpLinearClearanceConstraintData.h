/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_LINEAR_CLEARANCE_CONSTRAINT_DATA_H
#define HKP_LINEAR_CLEARANCE_CONSTRAINT_DATA_H

#include <Physics/Constraint/Data/hkpConstraintData.h>


/// Linear Clearance constraint. 
class hkpLinearClearanceConstraintData : public hkpConstraintData
{
	public:

		enum Type
		{
			PRISMATIC,
			HINGE,
			BALL_SOCKET,
		};

		enum 
		{
			SOLVER_RESULT_MOTOR				= 0,	// the motor
			SOLVER_RESULT_MOTOR_INTERNAL	= 1, 

			SOLVER_RESULT_FRICTION_0			= 2,	// the friction
			SOLVER_RESULT_FRICTION_0_INTERNAL	= 3,
			SOLVER_RESULT_FRICTION_1			= 4,	
			SOLVER_RESULT_FRICTION_1_INTERNAL	= 5,
			SOLVER_RESULT_FRICTION_2			= 6,	
			SOLVER_RESULT_FRICTION_3_INTERNAL	= 7,

			SOLVER_RESULT_ANG_0				= 8,	// angular constraint 0
			SOLVER_RESULT_ANG_1				= 9,	// angular constraint 1
			SOLVER_RESULT_ANG_2				= 0,	// angular constraint 2

			SOLVER_RESULT_LIMIT_0			= 11,	// linear limit 0
			SOLVER_RESULT_LIMIT_1			= 12,	// linear limit 1
			SOLVER_RESULT_LIMIT_2			= 13,	// linear limit 2

			SOLVER_RESULT_MAX				= 14
		};

		struct Runtime
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_DYNAMICS, hkpLinearClearanceConstraintData::Runtime );

			hkpSolverResults m_solverResults[SOLVER_RESULT_MAX];		
			hkUint8 m_initialized;				///< Whether the previous position has been initialized.
			hkReal m_previousTargetPosition;	///< The previous target position
		};

		struct Atoms
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_DYNAMICS, hkpLinearClearanceConstraintData::Atoms );
			HK_DECLARE_REFLECTION();

			enum Axis
			{
				AXIS_SHAFT = 0,
				AXIS_PERP_TO_SHAFT = 1
			};

			Atoms() {}

			Atoms(hkFinishLoadedObjectFlag f);

			// get a pointer to the first atom
			const hkpConstraintAtom* getAtoms() const { return &m_transforms; }

			// get the size of all atoms (we can't use sizeof(*this) because of align16 padding)
			int getSizeOfAllAtoms() const { return hkGetByteOffsetInt(this, &m_linLimit2+1); }

			hkpSetLocalTransformsConstraintAtom	m_transforms;
			hkpLinMotorConstraintAtom			m_motor;
			hkpLinFrictionConstraintAtom		m_friction0;
			hkpLinFrictionConstraintAtom		m_friction1;
			hkpLinFrictionConstraintAtom		m_friction2;
			hkpAngConstraintAtom				m_ang;
			hkpLinLimitConstraintAtom			m_linLimit0;
			hkpLinLimitConstraintAtom			m_linLimit1;
			hkpLinLimitConstraintAtom			m_linLimit2;
		};

	public:
	
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
		HK_DECLARE_REFLECTION();

		/// Constructor.
		hkpLinearClearanceConstraintData();

		/// Serialization constructor.
		hkpLinearClearanceConstraintData(hkFinishLoadedObjectFlag f) : hkpConstraintData(f), m_atoms(f) {}

		/// Destructor.
		~hkpLinearClearanceConstraintData();

		/// Construct a prismatic constraint with a pivot and axis in world space.
		/// \param bodyATransform	The attached body transform.
		/// \param bodyBTransform	The reference body transform.
		/// \param pivot			The pivot point, specified in world space.
		/// \param axis1			The first (main) axis, specified in world space.
		/// \param axis2			The second axis, specified in world space.
		void setInWorldSpace( hkpLinearClearanceConstraintData::Type type,
			const hkTransform& bodyATransform, const hkTransform& bodyBTransform,
			const hkVector4& pivot,const hkVector4& axis1, const hkVector4& axis2 );

		/// Construct a prismatic constraint with a pivot and axis in the two body spaces.
		/// \param pivotA			The pivot point, specified in bodyA space.
		/// \param pivotB			The pivot point, specified in bodyB space.
		/// \param axis1A			The first (main) axis, specified in bodyA space.
		/// \param axis1B			The first (main) axis, specified in bodyB space.
		/// \param axis2A			The second axis, specified in bodyA space.
		/// \param axis2B			The second axis, specified in bodyB space.
		void setInBodySpace( hkpLinearClearanceConstraintData::Type type,
			const hkVector4& pivotA, const hkVector4& pivotB,
			const hkVector4& axis1A, const hkVector4& axis1B,
			const hkVector4& axis2A, const hkVector4& axis2B );

		/// This allows you to change this prismatic constraint into a cylindrical constraint, where
		/// rotation around the shift axis is allowed.
		inline void allowRotationAroundPrismaticAxis(bool allowRotation);
		
		//
		// Methods to set and get limits and friction
		//

		/// Set the slack limits for the pivot.
		inline void setLimits(hkReal min0, hkReal max0, hkReal min1, hkReal max1, hkReal min2, hkReal max2);

		/// Set the friction value.
		inline void setMaxFrictionForce(hkReal mag);	

		/// Get the friction value.
		inline hkReal getMaxFrictionForce() const;

		//
		// Motor related methods
		//

		/// Set the motor. Setting this to null will disable any motor computations.
		/// Increments reference of new motor, decrements counter of replaced motor ( if any ).
		void setMotor( hkpConstraintMotor* motor );

		/// Get the motor.
		inline hkpConstraintMotor* getMotor() const;

		/// Turn the motor on or off.
		void setMotorEnabled( hkpConstraintRuntime* runtime, hkBool isEnabled );

		/// Is the motor enabled?
		inline hkBool isMotorEnabled() const;

		/// Set the target position for the motor. Only used by motors which use positions.
		inline void setMotorTargetPosition( hkReal position );

		/// Get the target angle for the motor.
		inline hkReal getMotorTargetPosition();

		static inline Runtime* HK_CALL getRuntime( hkpConstraintRuntime* runtime ) { return reinterpret_cast<Runtime*>(runtime); }

		//
		// hkpConstraintData implementation
		//

		virtual int getType() const;

		hkBool isValid() const;

		virtual void getConstraintInfo( ConstraintInfo& infoOut ) const ;

		virtual void getRuntimeInfo( hkBool wantRuntime, hkpConstraintData::RuntimeInfo& infoOut ) const;
		
	public:

		HK_ALIGN_REAL( Atoms m_atoms );
};

#include <Physics/Constraint/Data/Clearance/hkpLinearClearanceConstraintData.inl>


#endif // HKP_LINEAR_CLEARANCE_CONSTRAINT_DATA_H

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
