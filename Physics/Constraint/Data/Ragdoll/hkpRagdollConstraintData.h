/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_RAGDOLL_CONSTRAINT_DATA_H
#define HKP_RAGDOLL_CONSTRAINT_DATA_H

#include <Physics/Constraint/Data/hkpConstraintData.h>

extern const class hkClass hkpRagdollConstraintDataAtomsClass;
extern const hkClass hkpRagdollConstraintDataClass;


/// A ragdoll constraint. You can use this constraint to realistically simulate the behavior of body joints,
/// such as hips, shoulders, and knees. Ragdoll constraint allows you to activate motors to drive the 3 angles.
/// If you are using a motor with a target position to set, set it to 0. During the hkpConstraintMotor::motor()
/// callback the difference between the current angle the desired angle will be passed in. This will result in your
/// motor driving the difference in the angle to zero. If the motor is enabled, all friction will be disabled,
/// however once you disable the motor, friction will be enabled again.
class hkpRagdollConstraintData : public hkpConstraintData
{
	public:

		enum
		{
			SOLVER_RESULT_MOTOR_0				= 0,	// the angular motor value
			SOLVER_RESULT_MOTOR_0_INTERNAL		= 1,
			SOLVER_RESULT_MOTOR_1				= 2,	// the angular motor value
			SOLVER_RESULT_MOTOR_1_INTERNAL		= 3,
			SOLVER_RESULT_MOTOR_2				= 4,	// the angular motor value
			SOLVER_RESULT_MOTOR_2_INTERNAL		= 5,

			SOLVER_RESULT_FRICTION_0			= 6,	// the angular friction value
			SOLVER_RESULT_FRICTION_0_INTERNAL	= 7,
			SOLVER_RESULT_FRICTION_1			= 8,	// the angular friction value
			SOLVER_RESULT_FRICTION_1_INTERNAL	= 9,
			SOLVER_RESULT_FRICTION_2			= 10,	// the angular friction value
			SOLVER_RESULT_FRICTION_2_INTERNAL	= 11,

			SOLVER_RESULT_TWIST					= 12,	// angular limits defined around m_freeAxisA
			SOLVER_RESULT_CONE					= 13,	// angular constraint defined by m_constrainedAxis1A
			SOLVER_RESULT_PLANE					= 14,	// angular constraint defined by m_constrainedAxis2A

			SOLVER_RESULT_LIN_0					= 15,	// linear constraint defined by (1,0,0) in object space A
			SOLVER_RESULT_LIN_1					= 16,	// linear constraint defined by (0,1,0) in object space A
			SOLVER_RESULT_LIN_2					= 17,	// linear constraint defined by (0,0,1) in object space A

			SOLVER_RESULT_MAX					= 18
		};

		struct Runtime
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_DYNAMICS, hkpRagdollConstraintData::Runtime );

			HK_ALIGN16( hkpSolverResults m_solverResults[SOLVER_RESULT_MAX] );

			/// Tells whether the previous target angles have been initialized.
			/// This is zeroed when created.
			hkUint8 m_initialized[3];

			/// Target angles for the individual motors
			HK_ALIGN(hkReal m_previousTargetAngles[3],HK_REAL_SIZE);

			/// Soft recovery parameter for the cone limit.
			hkReal m_coneAngleOffset;
		};

		struct Atoms
		{
			// +version(1)
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_COLLIDE, hkpRagdollConstraintData::Atoms );
			HK_DECLARE_REFLECTION();

			enum Axis
			{
				AXIS_TWIST = 0,
				AXIS_PLANES = 1,
				AXIS_CROSS_PRODUCT = 2
			};

			Atoms() {}

			Atoms(hkFinishLoadedObjectFlag f);

			/// Get a pointer to the first atom
			const hkpConstraintAtom* getAtoms() const { return &m_transforms; }

			/// Get the size of all atoms.
			/// Note: we can't use sizeof(*this) because of align16 padding.
			int getSizeOfAllAtoms() const { return hkGetByteOffsetInt(this, &m_ballSocket + 1); }

			hkpSetLocalTransformsConstraintAtom	m_transforms;
			hkpSetupStabilizationAtom			m_setupStabilization;
			hkpRagdollMotorConstraintAtom		m_ragdollMotors;
			hkpAngFrictionConstraintAtom		m_angFriction;
			hkpTwistLimitConstraintAtom			m_twistLimit;
			hkpConeLimitConstraintAtom			m_coneLimit;
			hkpConeLimitConstraintAtom			m_planesLimit;
			hkpBallSocketConstraintAtom			m_ballSocket;
		};

		enum MotorIndex
		{
			MOTOR_TWIST = 0,
			MOTOR_PLANE = 1,
			MOTOR_CONE  = 2
		};

	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
		HK_DECLARE_REFLECTION();

		/// Constructor.
		hkpRagdollConstraintData();

		/// Serialization constructor.
		inline hkpRagdollConstraintData(hkFinishLoadedObjectFlag f);

		/// Destructor. Will dereference any motors held.
		~hkpRagdollConstraintData();

		/// Setup a ragdoll constraint based on information in world space.
		/// Use the set angle limit methods to add in the extra data.
		/// Use the set motors and set angle limit methods to add in the extra data.
		/// Will set the target frame B to match the current setup frame for B
		/// \param bodyA			The attached body transform
		/// \param bodyB			The reference body transform
		/// \param pivot			The pivot point, specified in world space.
		/// \param twistAxisW		The twist axis, specified in world space.
		/// \param planeAxisW		The plane axis, specified in world space.
		void setInWorldSpace(const hkTransform& bodyATransform, const hkTransform& bodyBTransform,
						const hkVector4& pivot, const hkVector4& twistAxisW,
						const hkVector4& planeAxisW);

		/// Setup a ragdoll constraint based on information in body space.
		/// Use the set angle limit methods to add in the extra data.
		/// Use the set motors and set angle limit methods to add in the extra data.
		/// Will set the target frame B to match the current setup frame for B
		/// \param pivotA			The pivot point, specified in bodyA space.
		/// \param pivotB			The pivot point, specified in bodyB space.
		/// \param twistAxisA		The twist axis, specified in bodyA space.
		/// \param twistAxisB		The twist axis, specified in bodyB space.
		/// \param planeAxisA		The plane axis, specified in bodyA space.
		/// \param planeAxisB		The plane axis, specified in bodyB space.
		void setInBodySpace( const hkVector4& pivotA, const hkVector4& pivotB,
						const hkVector4& planeAxisA, const hkVector4& planeAxisB,
						const hkVector4& twistAxisA, const hkVector4& twistAxisB);

		/// Get the constraint frame.
		/// \param constraintFrameA Column 0 = twist axis, Column 1 = plane, Column 2 = twist cross plane.
		void getConstraintFrameA( hkMatrix3& constraintFrameA ) const;

		/// Get the constraint frame.
		/// \param constraintFrameB Column 0 = twist axis, Column 1 = plane, Column 2 = twist cross plane.
		void getConstraintFrameB( hkMatrix3& constraintFrameB ) const;

		/// Set the minimum twist limit (in radians).
		inline void setTwistMinAngularLimit(hkReal rad);

		/// Set the maximum twist limit (in radians).
		inline void setTwistMaxAngularLimit(hkReal rad);

		/// Set the maximum plane limit (in radians).
		inline void setPlaneMaxAngularLimit(hkReal rad);

		/// Set the minimum plane limit (in radians).
		inline void setPlaneMinAngularLimit(hkReal rad);

		/// Set the half angle used to define the cone of possible movement (in radians).
		inline void setConeAngularLimit(hkReal rad);

		/// Enable/disable cone limit stabilization.
		void setConeLimitStabilization(hkBool enable);

		/// Set the angle used to define the cone of possible movement in terms of
		/// a min and max angle which it bisects and then calls setConeAngularLimit()
		/// and also adjusts the twist axis in body B accordingly.
		/// The angles are specified in radians.
		void setAsymmetricConeAngle(hkReal cone_min, hkReal cone_max );

		/// Set the friction value. Set this before adding to the system.
		/// Note that this value is an absolute torque value and is therefore
		/// dependent on the masses of constrained bodies and not limited
		/// between 0.0f and 1.0f. If trying to stiffen up ragdoll constraints,
		/// try setting this value sufficiently high so that constraints are
		/// completely stiff and then reduce until the desired behavior has
		/// been achieved.
		void setMaxFrictionTorque(hkReal tmag);

		/// Set the m_angularLimitsTauFactor. This is a factor in the range
		/// between 0 and 1 which controls the stiffness of the angular limits.
		/// If you slowly increase this value from 0 to 1 for a newly created
		/// constraint, you can nicely blend in the limits.
		inline void setAngularLimitsTauFactor( hkReal mag );

		/// Get the angular limits tau factor for this constraint.
		inline hkReal getAngularLimitsTauFactor() const;

		/// Get the minimum twist limit (in radians).
		inline hkReal getTwistMinAngularLimit() const;

		/// Get the maximum twist limit (in radians).
		inline hkReal getTwistMaxAngularLimit() const;

		/// Get the maximum plane limit (in radians).
		inline hkReal getPlaneMaxAngularLimit() const;

		/// Get the minimum plane limit (in radians).
		inline hkReal getPlaneMinAngularLimit() const;

		/// Get the cone angle limit (in radians).
		inline hkReal getConeAngularLimit() const;

		/// Get the state of cone limit stabilization.
		inline hkBool getConeLimitStabilization() const;

		/// Get the friction value.
		inline hkReal getMaxFrictionTorque() const;

		//
		// Motor related methods
		//

		/// Set the motor specified by the index.
		/// Increments reference of new motor, decrements counter of
		/// replaced motor (if any, can be null).
		void setMotor( MotorIndex index, hkpConstraintMotor* newMotor);

		/// Set the motor used to drive the twist axis angle.
		/// The measured angle passed in to the motor will be a relative angle
		/// between the current deflection around the twist axis and the
		/// desired deflection. i.e., the target angle that the motor should
		/// be trying to achieve is zero.
		/// Increments reference of new motor, decrements counter of replaced
		/// motor ( if any, can be null )
		void setTwistMotor( hkpConstraintMotor* motor );

		/// Return the motor used to drive the twist axis angle.
		hkpConstraintMotor* getTwistMotor() const;

		/// Set the motor used to drive the plane axis angle.
		/// The measured angle passed in to the motor will be a relative angle
		/// between the current deflection around the plane axis and the desired
		/// deflection. i.e., the target angle that the motor should be trying
		/// to achieve is zero.
		/// Increments reference of new motor, decrements counter of replaced
		/// motor (if any, can be null).
		void setPlaneMotor( hkpConstraintMotor* motor );

		/// Return the motor used to drive the plane axis angle.
		hkpConstraintMotor* getPlaneMotor() const;

		/// Set the motor used to drive the cone axis angle.
		/// The measured angle passed in to the motor will be a relative
		/// angle between the current deflection around the cone axis and
		/// the desired deflection. i.e., the target angle that the motor
		/// should be trying to achieve is zero.
		/// Increments reference of new motor, decrements counter of
		/// replaced motor (if any, can be null).
		void setConeMotor( hkpConstraintMotor* motor );

		/// Return the motor used to drive the cone axis angle.
		hkpConstraintMotor* getConeMotor() const;

		/// Turn the motors on or off
		/// \param runtime		The constraint instance's runtime data.
		/// \param areEnabled	The desired state of the motors.
		void setMotorsEnabled( hkpConstraintRuntime* runtime, hkBool areEnabled );

		/// Check is the motors are active.
		inline hkBool areMotorsEnabled() const;

		/// Set target relative orientation between the constraints reference frames attached to
		/// each of the bodies.
		/// See also: setTargetRelativeOrientationOfBodies()
		void setTarget( const hkMatrix3& target_cbRca );

		/// Set target relative orientation between bodies.
		/// This bypasses and ignores actual orientation of the constraint space in relation to each of the bodies.
		/// See also: setTarget()
		void setTargetRelativeOrientationOfBodies( const hkRotation& bRa );

		/// Get the target frame
		void getTarget( hkMatrix3& target_cbRca );

		static inline Runtime* HK_CALL getRuntime( hkpConstraintRuntime* runtime ) { return reinterpret_cast<Runtime*>(runtime); }

		//
		// hkpConstraintData implementation
		//

		/// Get type from this constraint
		virtual int getType() const;

		/// Check consistency of constraint
		hkBool isValid() const;

		virtual void getConstraintInfo( hkpConstraintData::ConstraintInfo& infoOut ) const;

		/// Sets the impulse above which this constraint is reported as breached.
		/// Set it to HK_REAL_MAX to disable breach reporting.
		virtual void setBreachImpulse(hkReal breachImpulse);

		/// Gets the impulse above which this constraint is reported as breached.
		virtual hkReal getBreachImpulse() const;

		/// Choose the body to be notified when the constraint's maximum impulse is breached.
		virtual void setBodyToNotify(int bodyIdx);

		/// Returns the index of the body that is notified when the constraint's maximum impulse limit is breached.
		virtual hkUint8 getNotifiedBodyIndex() const;

		/// Sets the solving method for this constraint. Use one of the hkpConstraintAtom::SolvingMethod as a value for method.
		virtual void setSolvingMethod(hkpConstraintAtom::SolvingMethod method);

		/// Gets the inertia stabilization factor, returns HK_FAILURE if the factor is not defined for the given constraint.
		virtual hkResult getInertiaStabilizationFactor(hkReal& inertiaStabilizationFactorOut) const;

		/// Sets the inertia stabilization factor, return HK_FAILURE if the factor is not defined for the given constraint.
		virtual hkResult setInertiaStabilizationFactor(const hkReal inertiaStabilizationFactorIn);
		
		virtual void getRuntimeInfo( hkBool wantRuntime, hkpConstraintData::RuntimeInfo& infoOut ) const;

	public:

		HK_ALIGN_REAL( Atoms m_atoms );
};

#include <Physics/Constraint/Data/Ragdoll/hkpRagdollConstraintData.inl>


#endif // HKP_RAGDOLL_CONSTRAINT_DATA_H

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
