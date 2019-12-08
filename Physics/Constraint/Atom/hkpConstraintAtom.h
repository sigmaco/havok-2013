/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_CONSTRAINT_ATOM_H
#define HKP_CONSTRAINT_ATOM_H

#include <Physics/Constraint/Data/hkpConstraintInfo.h>

class hkpConstraintMotor;


/// Constraint atoms are building blocks used in hkpConstraintDatas.
///
/// hkpConstraintDatas either use hkpBridgeAtoms, which allow them to implement their custom logic, or use a set of
/// generic hkpConstraintAtoms to describe the geometry of the constraint.
///
/// Each hkpConstraintAtom is used to specify a constraint's orientation in space or to create one or more
/// solver-constraints of a given type. During simulation, hkpConstraintAtoms are processed in the order in which they
/// are organized in a hkpConstraintData.
///
/// Generally the first constraint in a list is one that specifies the local bases of the constraint in each of the
/// constrained bodies' spaces. Those bases are persistent throughout processing of a list of atoms.
/// The proceeding atoms apply a kind of a constraint (linear, angular, limit, motor, etc.) in relation to one or more
/// of the axes of the specified local bases. See individual descriptions of atoms for more info.
///
struct hkpConstraintAtom
{
	public:

		// Atom enum values are saved in asset files. New atoms must be added from TYPE_OVERWRITE_PIVOT in order to
		// maintain backward compatibility
		enum AtomType
		{
			TYPE_INVALID = 0,

			TYPE_BRIDGE,					// 1

			TYPE_SET_LOCAL_TRANSFORMS,		// 2
			TYPE_SET_LOCAL_TRANSLATIONS,	// 3	
			TYPE_SET_LOCAL_ROTATIONS,		// 4

			TYPE_BALL_SOCKET,				// 5
			TYPE_STIFF_SPRING,				// 6

			TYPE_LIN,						// 7
			TYPE_LIN_SOFT,					// 8
			TYPE_LIN_LIMIT,					// 9
			TYPE_LIN_FRICTION,				// 10
			TYPE_LIN_MOTOR,					// 11

			TYPE_2D_ANG,					// 12

			TYPE_ANG,						// 13
			TYPE_ANG_LIMIT,					// 14
			TYPE_TWIST_LIMIT,				// 15
			TYPE_CONE_LIMIT,				// 16
			TYPE_ANG_FRICTION,				// 17
			TYPE_ANG_MOTOR,					// 18

			TYPE_RAGDOLL_MOTOR,				// 19

			TYPE_PULLEY,					// 20
			TYPE_RACK_AND_PINION,			// 21
			TYPE_COG_WHEEL,					// 22

			TYPE_SETUP_STABILIZATION,		// 23
			TYPE_3D_ANG,					// 24
			TYPE_DEFORMABLE_3D_LIN,			// 25
			TYPE_DEFORMABLE_3D_ANG,			// 26

			TYPE_OVERWRITE_PIVOT, //xx patch values from here [inclusive] on.
			

			TYPE_CONTACT,

			//
			// modifiers, must be the end of the list
			//
			FIRST_MODIFIER_TYPE,
			TYPE_MODIFIER_SOFT_CONTACT = FIRST_MODIFIER_TYPE,	// not supported on SPU
			TYPE_MODIFIER_MASS_CHANGER,
			TYPE_MODIFIER_VISCOUS_SURFACE,						// not supported on SPU
			TYPE_MODIFIER_MOVING_SURFACE,
			TYPE_MODIFIER_IGNORE_CONSTRAINT,
			TYPE_MODIFIER_CENTER_OF_MASS_CHANGER,				// not supported on SPU
			LAST_MODIFIER_TYPE = TYPE_MODIFIER_CENTER_OF_MASS_CHANGER,

			TYPE_MAX
		};

		/// Flags indicating whether this constraint needs some special callback treatment. These flags can be combined.
		enum CallbackRequest
		{
			CALLBACK_REQUEST_NONE					= 0,
			CALLBACK_REQUEST_NEW_CONTACT_POINT		= 1,
			CALLBACK_REQUEST_SETUP_PPU_ONLY			= 2,
			CALLBACK_REQUEST_SETUP_CALLBACK			= 4,
			CALLBACK_REQUEST_CONTACT_POINT_CALLBACK	= 8
		};
		
		/// Possible types of solving methods used by the constraint atoms.
		enum SolvingMethod
		{
			/// Stabilized - constraint equations are typically solved in block form, which adds extra stiffness.
			/// The virtual mass matrix is usually re-computed per solver step, which increases the CPU cost.
			METHOD_STABILIZED = 0,

			/// Old - constraint equations are solved sequentially and the virtual mass matrix is assumed to be constant
			/// during the solver iterations.
			METHOD_OLD = 1,
		};

	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CONSTRAINT, hkpConstraintAtom );
		HK_DECLARE_REFLECTION();

		hkpConstraintAtom(hkFinishLoadedObjectFlag f) {}

		HK_FORCE_INLINE AtomType getType() const { return m_type; }

		HK_FORCE_INLINE int isModifierType() const { return m_type >= FIRST_MODIFIER_TYPE; }

	protected:

		hkpConstraintAtom(AtomType type) : m_type(type) {}

	private:

		// Illegal constructor
		hkpConstraintAtom();

	public:

		hkEnum<AtomType,hkUint16> m_type;
};


/// Atom that computes common quantities for the stabilized versions of the atoms.
/// Specifically, it computes the arms where the joint forces will be applied,
/// and the maximum impulse that can be applied by the solver in a step to maintain the constraints.
struct hkpSetupStabilizationAtom : public hkpConstraintAtom
{
	// +version(2)
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_CONSTRAINT, hkpSetupStabilizationAtom);
		HK_DECLARE_REFLECTION();

		hkpSetupStabilizationAtom()
		:	hkpConstraintAtom(TYPE_SETUP_STABILIZATION)
		,	m_enabled(false)
		,	m_maxLinImpulse(HK_REAL_MAX)
		,	m_maxAngImpulse(HK_REAL_MAX)
		,	m_maxAngle(HK_REAL_HIGH)
		{}

		hkpSetupStabilizationAtom(hkFinishLoadedObjectFlag f) : hkpConstraintAtom(f) {}

		HK_FORCE_INLINE hkpConstraintAtom* next() const
		{
			return const_cast<hkpConstraintAtom*>( static_cast<const hkpConstraintAtom*>(this + 1) );
		}

		HK_FORCE_INLINE int numSolverResults() const { return 0; }

		/// Sets the maximum angle that can be swept by an object in a solver time-step. Used when estimating the maximum impulse
		/// the solver can apply during a step.
		HK_FORCE_INLINE void setMaxAngle(const hkReal maxAngle) { m_maxAngle = maxAngle; }

		/// Gets the maximum angle
		HK_FORCE_INLINE const hkReal& getMaxAngle() const {	return m_maxAngle; }

		/// Sets the maximum linear impulse the solver can apply to maintain the constraints
		HK_FORCE_INLINE void setMaximumLinearImpulse(hkReal maxImpulse) { m_maxLinImpulse = maxImpulse; }

		/// Returns the maximum linear impulse the solver can apply to maintain the constraints
		HK_FORCE_INLINE const hkReal& getMaximumLinearImpulse()	const { return m_maxLinImpulse; }

		/// Sets the maximum angular impulse the solver can apply to maintain the constraints
		HK_FORCE_INLINE void setMaximumAngularImpulse(hkReal maxImpulse) { m_maxAngImpulse = maxImpulse; }

		/// Returns the maximum angular impulse the solver can apply to maintain the constraints
		HK_FORCE_INLINE const hkReal& getMaximumAngularImpulse() const { return m_maxAngImpulse; }

	public:

		/// True if the atom is enabled
		hkBool m_enabled;	//+default(false)

		/// The maximum linear impulse the solver can apply to maintain the constraints. This clamps the maximum impulse estimated
		/// using the maxAngle
		hkReal m_maxLinImpulse;	//+default(HK_REAL_MAX)

		/// The maximum angular impulse the solver can apply to maintain the constraints. This clamps the maximum impulse estimated
		/// using the maxAngle
		hkReal m_maxAngImpulse;	//+default(HK_REAL_MAX)

		/// The maximum angle that can be swept by an object in a solver time-step. Used when estimating the maximum impulse
		/// the solver can apply during a step.
		hkReal m_maxAngle;		//+default(HK_REAL_HIGH)
};


/// Atom that limits angular movement on all three axes. Constraints using this atom must precede it with a hkpSetupStabilizationAtom.
/// The solver is not allowed to apply more than hkpSetupStabilizationAtom::m_maxAngImpulse to maintain the constraint.
/// The constraint gets solved in block-form, on all 3 axes. The constraint Jacobian blocks are quaternion-based and therefore,
/// near the point where the constraint is satisfied, they have full rank and a determinant of +/-1.
struct hkp3dAngConstraintAtom : public hkpConstraintAtom
{
	//+version(1)
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_CONSTRAINT, hkp3dAngConstraintAtom);
		HK_DECLARE_REFLECTION();

		hkp3dAngConstraintAtom() : hkpConstraintAtom(TYPE_3D_ANG) {}
		hkp3dAngConstraintAtom(hkFinishLoadedObjectFlag f) : hkpConstraintAtom(f) {}

		HK_FORCE_INLINE hkpConstraintAtom* next() const { return const_cast<hkpConstraintAtom*>( static_cast<const hkpConstraintAtom*>(this + 1) ); }
		HK_FORCE_INLINE int numSolverResults() const { return hkpJacobianSchemaInfo::StableAngular3D::Results; }
		HK_FORCE_INLINE void addToConstraintInfo(hkpConstraintInfo& infoOut) const { infoOut.add<hkpJacobianSchemaInfo::StableAngular3D>(); }

	public:

#if defined(HK_REAL_IS_DOUBLE)
		// padding to 32 bytes
		hkUint8 m_padding[30]; //+nosave
#else
		// Padding to 16 bytes
		hkUint8	m_padding[14]; //+nosave
#endif
};


/// Deformable 3D linear atom. This is similar to a ball-in-socket constraint, i.e. the solver will try to maintain an
/// offset (initial deformation) between the constrained body pivots. The solver cannot apply more than a certain force
/// to maintain the constraint. Normally, if the constraint violation remains under the maximum allowed distance, the
/// solver is allowed to apply no more than the yield strength force. However, if the violation grows beyond the maximum
/// allowed distance, the solver is allowed to apply forces up to the ultimate strength force. The actual force limit is
/// linearly interpolated between the yield and the ultimate values, based on the violation amount.
struct hkpDeformableLinConstraintAtom : public hkpConstraintAtom
{
	public:
		//+version(1)

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_CONSTRAINT, hkpDeformableLinConstraintAtom);
		HK_DECLARE_REFLECTION();

		hkpDeformableLinConstraintAtom() : hkpConstraintAtom(TYPE_DEFORMABLE_3D_LIN) { m_offset.setZero(); }
		hkpDeformableLinConstraintAtom(hkFinishLoadedObjectFlag f) : hkpConstraintAtom(f) {}

		HK_FORCE_INLINE hkpConstraintAtom* next() const { return const_cast<hkpConstraintAtom*>( static_cast<const hkpConstraintAtom*>(this + 1) ); }
		HK_FORCE_INLINE int numSolverResults() const { return hkpJacobianSchemaInfo::DeformableLinear3D::Results; }
		HK_FORCE_INLINE void addToConstraintInfo(hkpConstraintInfo& infoOut) const { infoOut.add<hkpJacobianSchemaInfo::DeformableLinear3D>(); }

		// Getters
		HK_FORCE_INLINE const hkSimdReal			getMaxDistance() const		{ return m_offset.getComponent<3>();	}
		HK_FORCE_INLINE const hkVector4&			getOffset() const			{ return m_offset;						}
		HK_FORCE_INLINE const hkVector4&			getYieldStrengthDiag() const	{ return m_yieldStrengthDiag; 		}
		HK_FORCE_INLINE const hkVector4&			getYieldStrengthOffDiag() const	{ return m_yieldStrengthOffDiag; 	}
		HK_FORCE_INLINE const hkVector4&			getUltimateStrengthDiag() const	{ return m_ultimateStrengthDiag;	}
		HK_FORCE_INLINE const hkVector4&			getUltimateStrengthOffDiag() const	{ return m_ultimateStrengthOffDiag;	}

		// Setters
		HK_FORCE_INLINE void setMaxDistance(hkSimdRealParameter d)				{ m_offset.setXYZ_W(getOffset(), d);		}
		HK_FORCE_INLINE void setOffset(hkVector4Parameter v)					{ m_offset.setXYZ_W(v, getMaxDistance());	}
		HK_FORCE_INLINE void setYieldStrength(const hkSymmetricMatrix3& t)		{ m_yieldStrengthDiag = t.m_diag; m_yieldStrengthOffDiag = t.m_offDiag; }
		HK_FORCE_INLINE void setUltimateStrength(const hkSymmetricMatrix3& t)	{ m_ultimateStrengthDiag = t.m_diag; m_ultimateStrengthOffDiag = t.m_offDiag; }

	public:

		/// Offset that must be preserved between pivots, i.e. pivotB - pivotA = offset, in local space of body A. Maximum allowed distance
		/// between pivots is stored in the .w component 
		hkVector4 m_offset;	//+default(0.0f,0.0f,0.0f,0.0f)

		/// Yield strength tensor. Has force units (i.e. N) when projected on an axis. Gives the maximum force the solver can apply
		/// in any direction to maintain the constraint, in the case where the constraint error is less than getMaxDistance().
		hkVector4 m_yieldStrengthDiag;
		hkVector4 m_yieldStrengthOffDiag;

		/// Ultimate strength tensor. Has force units (i.e. N) when projected on an axis. Gives the maximum force the solver can apply
		// in any direction to maintain the constraint, in the case where the constraint error is greater than getMaxDistance().
		hkVector4 m_ultimateStrengthDiag;
		hkVector4 m_ultimateStrengthOffDiag;
};


/// Deformable 3D angular atom. This is similar to a 3D angular constraint, i.e. the solver will try to maintain an
/// angular offset (initial deformation) between the constrained body pivots. The solver cannot apply more than a
/// certain torque to maintain the constraint. Normally, if the constraint violation remains under the maximum allowed
/// angle, the solver is allowed to apply no more than the yield strength torque. However, if the violation grows beyond
/// the maximum allowed angle, the solver is allowed to apply torques up to the ultimate strength torque. The actual
/// torque limit is linearly interpolated between the yield and the ultimate values, based on the violation amount.
struct hkpDeformableAngConstraintAtom : public hkpConstraintAtom
{
	public:
		//+version(1)

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_CONSTRAINT, hkpDeformableAngConstraintAtom);
		HK_DECLARE_REFLECTION();

		hkpDeformableAngConstraintAtom() : hkpConstraintAtom(TYPE_DEFORMABLE_3D_ANG) { m_offset.setIdentity(); }
		hkpDeformableAngConstraintAtom(hkFinishLoadedObjectFlag f) : hkpConstraintAtom(f) {}

		HK_FORCE_INLINE hkpConstraintAtom* next() const { return const_cast<hkpConstraintAtom*>( static_cast<const hkpConstraintAtom*>(this + 1) ); }
		HK_FORCE_INLINE int numSolverResults() const { return hkpJacobianSchemaInfo::DeformableAngular3D::Results; }
		HK_FORCE_INLINE void addToConstraintInfo( hkpConstraintInfo& infoOut ) const { infoOut.add<hkpJacobianSchemaInfo::DeformableAngular3D>(); }

		// Getters
		HK_FORCE_INLINE const hkSimdReal			getCosMaxAngle() const		{ return m_yieldStrengthDiag.getComponent<3>();	}
		HK_FORCE_INLINE const hkQuaternion&			getOffset() const			{ return m_offset;									}
		HK_FORCE_INLINE const hkVector4&			getYieldStrengthDiag() const	{ return m_yieldStrengthDiag; 		}
		HK_FORCE_INLINE const hkVector4&			getYieldStrengthOffDiag() const	{ return m_yieldStrengthOffDiag; 	}
		HK_FORCE_INLINE const hkVector4&			getUltimateStrengthDiag() const	{ return m_ultimateStrengthDiag;	}
		HK_FORCE_INLINE const hkVector4&			getUltimateStrengthOffDiag() const	{ return m_ultimateStrengthOffDiag;	}

		// Setters
		HK_FORCE_INLINE void setCosMaxAngle(hkSimdRealParameter c)				{ m_yieldStrengthDiag.setComponent<3>(c);								}
		HK_FORCE_INLINE void setOffset(hkQuaternionParameter q)					{ m_offset = q;																}
		HK_FORCE_INLINE void setYieldStrength(const hkSymmetricMatrix3& t)		{ hkSimdReal c = getCosMaxAngle(); m_yieldStrengthDiag = t.m_diag; m_yieldStrengthOffDiag = t.m_offDiag; setCosMaxAngle(c);	}
		HK_FORCE_INLINE void setUltimateStrength(const hkSymmetricMatrix3& t)	{ m_ultimateStrengthDiag = t.m_diag; m_ultimateStrengthOffDiag = t.m_offDiag; }

	public:

		/// Relative angle that must be preserved between pivots. Defined as Inverse(worldFromPivotA) * worldFromPivotB
		hkQuaternion m_offset;	//+default(0.0f,0.0f,0.0f,1.0f)

		/// Angular yield strength tensor. Has torque units when projected on an axis. Gives the maximum torque the solver can apply in any direction
		/// to maintain the constraint, in the case where the constraint error is less than the maximum allowed angle. The cosine of the
		/// maximum allowed angle is encoded in .m_diag.w component.
		hkVector4 m_yieldStrengthDiag;
		hkVector4 m_yieldStrengthOffDiag;

		/// Angular ultimate strength tensor. Has torque units when projected on an axis. Gives the maximum torque the solver can apply in any direction
		/// to maintain the constraint, in the case where the constraint error is greater than the maximum allowed angle.
		hkVector4 m_ultimateStrengthDiag;
		hkVector4 m_ultimateStrengthOffDiag;
};


/// Atom that fully eliminates relative linear movement of bodies' pivots. This is the most common atom.
/// It is advised to place it at the end of the list of atoms to minimize results error.
/// This atom eliminates 3 degrees of freedom and returns 3 solver results. It has no parameters.
struct hkpBallSocketConstraintAtom : public hkpConstraintAtom
{
	//+version(5)
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CONSTRAINT, hkpBallSocketConstraintAtom );
		HK_DECLARE_REFLECTION();

		hkpBallSocketConstraintAtom()
		:	hkpConstraintAtom(TYPE_BALL_SOCKET)
		,	m_solvingMethod(METHOD_OLD)
		,	m_bodiesToNotify(0)
		,	m_velocityStabilizationFactor(1.0f)
		,	m_enableLinearImpulseLimit(false)
		,	m_breachImpulse(HK_REAL_MAX)
		,	m_inertiaStabilizationFactor(0.0f)
		{}

		hkpBallSocketConstraintAtom(hkFinishLoadedObjectFlag f) : hkpConstraintAtom(f) {}

			/// Return the next atom after this.
		HK_FORCE_INLINE hkpConstraintAtom* next() const { return const_cast<hkpConstraintAtom*>( static_cast<const hkpConstraintAtom*>(this+1) ); }

			/// This tells how many solver-constraints this atom generates and how may solver-results slots it requires.
		HK_FORCE_INLINE int numSolverResults() const    
		{ 
			const int numResults = hkMath::_max2<int>(3 * hkpJacobianSchemaInfo::Bilateral1D::Results, hkpJacobianSchemaInfo::StableBallSocket::Results);
			return numResults; 
		}

			/// This tells how much memory the system will need to store solver schemas and Jacobian's for this atom.
		HK_FORCE_INLINE void addToConstraintInfo(hkpConstraintInfo& infoOut) const
		{
			const int schemaSize = hkMath::_max2<int>(3 * hkpJacobianSchemaInfo::Bilateral1D::Sizeof, hkpJacobianSchemaInfo::StableBallSocket::Sizeof);
			const int numTemps = hkMath::_max2<int>(3 * hkpJacobianSchemaInfo::Bilateral1D::Temps, hkpJacobianSchemaInfo::StableBallSocket::Temps);
			infoOut.add(schemaSize, numSolverResults(), numTemps);
		}

			/// Returns the value of the velocity stabilization factor.
		HK_FORCE_INLINE hkUFloat8 getVelocityStabilizationFactor() const
		{
			return m_velocityStabilizationFactor;
		}

			/// Sets the value of the velocity stabilization factor.
		HK_FORCE_INLINE void setVelocityStabilizationFactor(const hkUFloat8 velocityStabilizationFactor)
		{
			m_velocityStabilizationFactor = velocityStabilizationFactor;
		}

			/// Returns the value of the inertia stabilization factor.
		HK_FORCE_INLINE hkReal getInertiaStabilizationFactor() const
		{
			return m_inertiaStabilizationFactor;
		}

			/// Sets the value of the inertia stabilization factor. The passed value will be clamped to [0, 1].
		HK_FORCE_INLINE void setInertiaStabilizationFactor(const hkReal inertiaStabilizationFactor)
		{
			m_inertiaStabilizationFactor = hkMath::clamp(inertiaStabilizationFactor, hkReal(0.0f), hkReal(1.0f) );
		}

			/// Sets the breach impulse
		HK_FORCE_INLINE void setBreachImpulse(hkReal breachImpulse)
		{
			m_breachImpulse = breachImpulse;
		}

			/// Returns the breach impulse
		HK_FORCE_INLINE const hkReal& getBreachImpulse() const
		{
			return m_breachImpulse;
		}

	public:

		/// The method used by the solver to maintain this constraint. Can be one of the values in the hkpConstraintAtom::SolvingMethod enum.
		/// Note that maxImpulse and stabilization factor are not handled by the STABLE method. Also, the solverStabilizationFactor is only used by the
		/// STABLE method in an attempt to stabilize constrained body pairs with large mass ratios / long arm lengths.
		hkEnum<SolvingMethod, hkUint8> m_solvingMethod;	 //+default(hkpConstraintAtom::METHOD_OLD)

		/// Marks the body to be notified when the m_breachImpulse is breached.
		hkUint8 m_bodiesToNotify; //+default(0)

	protected:

		/// Deprecated. This sets the multiplier that's used to add bodies' velocities to the solver's Jacobians RHS.
		/// This defaults to 1.0f and results in the constraints positional constraint being slightly violated for the advantage of
		/// extra stabilization. At low (low frame rate, few solver iterations) this setting can cause uncontrollable jitter however.
		/// In such cases disable it setting the factor to lower values or zero. Note that this parameter is only used by the OLD solving mode.
		hkUFloat8 m_velocityStabilizationFactor; 

	public:

		/// Set to true if the solver is allowed to limit the linear part of the applied impulse. Note that this is disabled by default and
		/// enabling it may negatively affect stability.
		hkBool m_enableLinearImpulseLimit;	//+default(false)

		/// Breach impulse of each of the three 1d bilinear constraints.
		/// When any of the three limits is breached and the constraint has runtime allocated, a constraint-impulse-limit breached callback is triggered.
		hkReal m_breachImpulse;  //+default(HK_REAL_MAX)

	protected:

		/// A scaling factor that controls how much the solver is allowed to numerically
		/// adjust the angular terms of the inverse virtual mass matrix while in the STABILIZED solving mode. Must be inside [0, 1]. A value of 0 means
		/// no adjustments are made to the mass distributions. A value closer to 1 stabilizes bodies having large mass ratios or long / disproportionate arm lengths.
		/// Note that this can generally be set to zero (i.e., disabled) if the inertia tensors have been already stabilized in the Create Constraints pipeline
		/// filter of by manually calling hkpConstraintStabilizationUtil::stabilizeRigidBodyInertia().
		/// Default value is zero.
		hkReal m_inertiaStabilizationFactor;	//+default(0.0f)

#if defined(HK_REAL_IS_DOUBLE)
		// padding to 32 bytes
		hkUint8 m_padding[8]; //+nosave
#endif
};


/// Atom that enforces a minimum and maximum distance between the pivot points of each body.
struct hkpStiffSpringConstraintAtom : public hkpConstraintAtom
{
	//+version(1)
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CONSTRAINT, hkpStiffSpringConstraintAtom );
		HK_DECLARE_REFLECTION();

		hkpStiffSpringConstraintAtom() : hkpConstraintAtom(TYPE_STIFF_SPRING) {}
		hkpStiffSpringConstraintAtom(hkFinishLoadedObjectFlag f) : hkpConstraintAtom(f) {}

		HK_FORCE_INLINE hkpConstraintAtom* next() const { return const_cast<hkpConstraintAtom*>( static_cast<const hkpConstraintAtom*>(this+1) ); }
		HK_FORCE_INLINE int numSolverResults() const { return hkpJacobianSchemaInfo::StableStiffSpring::Results; }
		HK_FORCE_INLINE void addToConstraintInfo(hkpConstraintInfo& infoOut) const { infoOut.add<hkpJacobianSchemaInfo::StableStiffSpring>(); }

	public:

		hkReal m_length;		///< The minimum rest length / distance between pivot points.
		hkReal m_maxLength;		///< The maximum rest length / distance between pivot points.

#if defined(HK_REAL_IS_DOUBLE)
		// padding to 32 bytes
		hkUint8 m_padding[8]; //+nosave
#endif
};


/// Atom which specifies constraint spaces and pivot points in the local spaces of each body.
/// Pivot points are stored in the translation part of the transforms.
struct hkpSetLocalTransformsConstraintAtom : public hkpConstraintAtom
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CONSTRAINT, hkpSetLocalTransformsConstraintAtom );
		HK_DECLARE_REFLECTION();

		hkpSetLocalTransformsConstraintAtom() : hkpConstraintAtom(TYPE_SET_LOCAL_TRANSFORMS) {}
		hkpSetLocalTransformsConstraintAtom(hkFinishLoadedObjectFlag f) : hkpConstraintAtom(f) {}

		HK_FORCE_INLINE hkpConstraintAtom* next() const { return const_cast<hkpConstraintAtom*>( static_cast<const hkpConstraintAtom*>(this+1) ); }
		HK_FORCE_INLINE int numSolverResults() const { return 0; }
		// addToConstraintInfo not needed

	public:

		hkTransform m_transformA;	///< Constraint orientation and origin/pivot point in bodyA's local space.
		hkTransform m_transformB;	///< Constraint orientation and origin/pivot point in bodyB's local space.
};


/// Atom which specifies pivot points in the local spaces of each body.
/// Note that this does not overwrite the constraint space's orientation.
/// This is used when constraint orientation is irrelevant, e.g., in hkpBallAndSocketConstraintData.
struct hkpSetLocalTranslationsConstraintAtom : public hkpConstraintAtom
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CONSTRAINT, hkpSetLocalTranslationsConstraintAtom );
		HK_DECLARE_REFLECTION();

		hkpSetLocalTranslationsConstraintAtom() : hkpConstraintAtom(TYPE_SET_LOCAL_TRANSLATIONS) {}
		hkpSetLocalTranslationsConstraintAtom(hkFinishLoadedObjectFlag f) : hkpConstraintAtom(f) {}

		HK_FORCE_INLINE hkpConstraintAtom* next() const { return const_cast<hkpConstraintAtom*>( static_cast<const hkpConstraintAtom*>(this+1) ); }
		HK_FORCE_INLINE int numSolverResults() const { return 0; }
		// addToConstraintInfo not needed

	public:

		hkVector4 m_translationA;	///< Pivot point in bodyA's local space.
		hkVector4 m_translationB;	///< Pivot point in bodyB's local space.
};


/// Atom which specifies constraint spaces in the local spaces of each body.
/// Note that this does not overwrite the pivot points.
/// This is used when the constraint space must be reoriented for some atoms in more complex hkConstraintDatas, e.g., in the hkpWheelConstraintData.
struct hkpSetLocalRotationsConstraintAtom : public hkpConstraintAtom
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CONSTRAINT, hkpSetLocalRotationsConstraintAtom );
		HK_DECLARE_REFLECTION();

		hkpSetLocalRotationsConstraintAtom() : hkpConstraintAtom(TYPE_SET_LOCAL_ROTATIONS) {}
		hkpSetLocalRotationsConstraintAtom(hkFinishLoadedObjectFlag f) : hkpConstraintAtom(f) {}

		HK_FORCE_INLINE hkpConstraintAtom* next() const { return const_cast<hkpConstraintAtom*>( static_cast<const hkpConstraintAtom*>(this+1) ); }
		HK_FORCE_INLINE int numSolverResults() const { return 0; }
		// addToConstraintInfo not needed

	public:

		hkRotation m_rotationA;		///< Constraint orientation in bodyA's local space.
		hkRotation m_rotationB;		///< Constraint orientation in bodyB's local space.
};



struct hkpOverwritePivotConstraintAtom : public hkpConstraintAtom
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CONSTRAINT, hkpOverwritePivotConstraintAtom );
		HK_DECLARE_REFLECTION();

		hkpOverwritePivotConstraintAtom() : hkpConstraintAtom(TYPE_OVERWRITE_PIVOT), m_copyToPivotBFromPivotA(true) { }
		hkpOverwritePivotConstraintAtom(hkFinishLoadedObjectFlag f) : hkpConstraintAtom(f) {}

		HK_FORCE_INLINE hkpConstraintAtom* next() const { return const_cast<hkpConstraintAtom*>( static_cast<const hkpConstraintAtom*>(this+1) ); }
		HK_FORCE_INLINE int numSolverResults() const { return 0; }

	public:

		hkUint8 m_copyToPivotBFromPivotA;

#if defined(HK_REAL_IS_DOUBLE)
		// padding to 32 bytes
		hkUint8 m_padding[28]; //+nosave
#else
		hkUint8 m_padding[12]; //+nosave
#endif
};


/// Atom which eliminates relative linear velocity of bodies' pivot points along one specified axis.
/// This is used when relative linear movement is only partly constrained as it is in e.g., prismatic or point-to-plane constraints.
struct hkpLinConstraintAtom : public hkpConstraintAtom
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CONSTRAINT, hkpLinConstraintAtom );
		HK_DECLARE_REFLECTION();

		hkpLinConstraintAtom() : hkpConstraintAtom(TYPE_LIN) {}
		hkpLinConstraintAtom(hkFinishLoadedObjectFlag f) : hkpConstraintAtom(f) {}

		HK_FORCE_INLINE hkpConstraintAtom* next() const { return const_cast<hkpConstraintAtom*>( static_cast<const hkpConstraintAtom*>(this+1) ); }
		HK_FORCE_INLINE int numSolverResults() const { return hkpJacobianSchemaInfo::Bilateral1D::Results; }
		HK_FORCE_INLINE void addToConstraintInfo(hkpConstraintInfo& infoOut) const { infoOut.add<hkpJacobianSchemaInfo::Bilateral1D>(); }

	public:

		hkUint8 m_axisIndex;	///< Specifies the index of the axis of the bodyB's constraint base, that will be constrained.

#if defined(HK_REAL_IS_DOUBLE)
		// padding to 32 bytes
		hkUint8 m_padding[28];  //+nosave
#else
		hkUint8 m_padding[12]; //+nosave
#endif
};


/// Atom which softens/controls relative linear velocity of bodies' pivot points along one specified axis.
/// This results in a spring-like reaction. It is used in the hkpWheelConstraintData.
struct hkpLinSoftConstraintAtom : public hkpConstraintAtom
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CONSTRAINT, hkpLinSoftConstraintAtom );
		HK_DECLARE_REFLECTION();

		hkpLinSoftConstraintAtom() : hkpConstraintAtom(TYPE_LIN_SOFT) {}
		hkpLinSoftConstraintAtom(hkFinishLoadedObjectFlag f) : hkpConstraintAtom(f) {}

		HK_FORCE_INLINE hkpConstraintAtom* next() const { return const_cast<hkpConstraintAtom*>( static_cast<const hkpConstraintAtom*>(this+1) ); }
		HK_FORCE_INLINE int numSolverResults() const { return hkpJacobianSchemaInfo::BilateralUserTau1D::Results; }
		HK_FORCE_INLINE void addToConstraintInfo(hkpConstraintInfo& infoOut) const { infoOut.add<hkpJacobianSchemaInfo::BilateralUserTau1D>(); }

	public:
			
		hkUint8 m_axisIndex;	///< Specifies the index of the axis of the bodyB's constraint base, that will be constrained.
		hkReal m_tau;			///< Specifies a custom value for the tau parameter used by the solver.
		hkReal m_damping;		///< Specifies a custom value for the damping parameter used by the solver.

#if defined(HK_REAL_IS_DOUBLE)
		// padding to 32 bytes
		hkUint8 m_padding[8]; //+nosave
#else
		hkUint8 m_padding[4]; //+nosave
#endif
};


/// Atom which limits allowed relative distance between bodies' pivot points along one specified axis.
/// This allows unconstrained movement within the specified range, and applies hard limits at its ends.
struct hkpLinLimitConstraintAtom : public hkpConstraintAtom
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CONSTRAINT, hkpLinLimitConstraintAtom );
		HK_DECLARE_REFLECTION();

		hkpLinLimitConstraintAtom() : hkpConstraintAtom(TYPE_LIN_LIMIT) {}
		hkpLinLimitConstraintAtom(hkFinishLoadedObjectFlag f) : hkpConstraintAtom(f) {}

		HK_FORCE_INLINE hkpConstraintAtom* next() const { return const_cast<hkpConstraintAtom*>( static_cast<const hkpConstraintAtom*>(this+1) ); }
		HK_FORCE_INLINE int numSolverResults() const { return hkpJacobianSchemaInfo::LinearLimits1D::Results; }
		HK_FORCE_INLINE void addToConstraintInfo(hkpConstraintInfo& infoOut) const { infoOut.add<hkpJacobianSchemaInfo::LinearLimits1D>(); }

	public:

		hkUint8 m_axisIndex;	///< The index of the axis of the bodyB's constraint base, that will be limited.
		hkReal m_min;			///< Minimum distance along the axis (may be negative).
		hkReal m_max;			///< Maximum distance along the axis (may be negative).

#if defined(HK_REAL_IS_DOUBLE)
		// padding to 32 bytes
		hkUint8 m_padding[8]; //+nosave
#else
		hkUint8 m_padding[4]; //+nosave
#endif
};


/// Atom which eliminates two degrees of freedom of angular movement and allows relative rotation along a specified axis only.
/// Angular-constraint atoms are often combined with linear-constraint atoms, e.g., this atoms combined with the ball-and-socket
/// atom forms a hkpHingeConstraintData.
struct hkp2dAngConstraintAtom : public hkpConstraintAtom
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CONSTRAINT, hkp2dAngConstraintAtom );
		HK_DECLARE_REFLECTION();

		hkp2dAngConstraintAtom() : hkpConstraintAtom(TYPE_2D_ANG) {}
		hkp2dAngConstraintAtom(hkFinishLoadedObjectFlag f) : hkpConstraintAtom(f) {}

		HK_FORCE_INLINE hkpConstraintAtom* next() const { return const_cast<hkpConstraintAtom*>( static_cast<const hkpConstraintAtom*>(this+1) ); }
		HK_FORCE_INLINE int numSolverResults() const { return 2 * hkpJacobianSchemaInfo::Angular1D::Results; }
		HK_FORCE_INLINE void addToConstraintInfo(hkpConstraintInfo& infoOut) const { infoOut.addMultiple<hkpJacobianSchemaInfo::Angular1D>(2); }

	public:
		
		hkUint8 m_freeRotationAxis;	///< Specifies the index of the unconstrained axis of relative rotation in bodyB's constraint base.

#if defined(HK_REAL_IS_DOUBLE)
		hkUint8 m_padding[28]; //+nosave
#else
		hkUint8 m_padding[12]; //+nosave
#endif
};


/// Atom which eliminates one, two, or three degrees of freedom of angular movement.
/// Note: this is only tested for eliminating three degrees of freedom.
struct hkpAngConstraintAtom : public hkpConstraintAtom
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CONSTRAINT, hkpAngConstraintAtom );
		HK_DECLARE_REFLECTION();

		hkpAngConstraintAtom() : hkpConstraintAtom(TYPE_ANG) {}
		hkpAngConstraintAtom(hkFinishLoadedObjectFlag f) : hkpConstraintAtom(f) {}

		HK_FORCE_INLINE hkpConstraintAtom* next() const { return const_cast<hkpConstraintAtom*>( static_cast<const hkpConstraintAtom*>(this+1) ); }
		HK_FORCE_INLINE int numSolverResults() const { return m_numConstrainedAxes * hkpJacobianSchemaInfo::Angular1D::Results; }
		HK_FORCE_INLINE void addToConstraintInfo(hkpConstraintInfo& infoOut) const { infoOut.addMultiple<hkpJacobianSchemaInfo::Angular1D>(m_numConstrainedAxes); }

	public:
			
		hkUint8 m_firstConstrainedAxis;		///< Index of the first axis to constrain, in bodyA's constraint base.
		hkUint8 m_numConstrainedAxes;		///< Number of subsequent base axes to constrain.

#if defined(HK_REAL_IS_DOUBLE)
		// padding to 32 bytes
		hkUint8 m_padding[28]; //+nosave
#else
		// padding to 16 bytes
		hkUint8 m_padding[12]; //+nosave
#endif
};


/// Atom which limits allowed relative angle between bodies' rotations along one specified rotation axis.
///
/// This allows unconstrained movement within the specified range, and applies hard limits at its ends.
/// Note: This atom can introduce instability issues when angle limits are too large (> 65 degrees).
/// This can be addressed by lowering the angle limits, if possible, or lowering the tau factor
/// (which controls the stiffness of the constraint). The best solution is to use a ragdoll
/// constraint, which has in-built dynamic stability-enforcing algorithms. More information
/// is available in the Constraints documentation section.
struct hkpAngLimitConstraintAtom : public hkpConstraintAtom
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CONSTRAINT, hkpAngLimitConstraintAtom );
		HK_DECLARE_REFLECTION();

		hkpAngLimitConstraintAtom() : hkpConstraintAtom(TYPE_ANG_LIMIT), m_isEnabled(true) {}
		hkpAngLimitConstraintAtom(hkFinishLoadedObjectFlag f) : hkpConstraintAtom(f) {}

		HK_FORCE_INLINE hkpConstraintAtom* next() const { return const_cast<hkpConstraintAtom*>( static_cast<const hkpConstraintAtom*>(this+1) ); }
		HK_FORCE_INLINE int numSolverResults() const { return hkpJacobianSchemaInfo::AngularLimits1D::Results; }
		HK_FORCE_INLINE void addToConstraintInfo(hkpConstraintInfo& infoOut) const { infoOut.add<hkpJacobianSchemaInfo::AngularLimits1D>(); }

	public:

		/// Tells whether the atom should be handled by the solver.
		/// Note that if it is not, the atom's corresponding hkpSolverResults are not updated.
		hkUint8 m_isEnabled;

		hkUint8 m_limitAxis;	///< The index of the axis in the bodyA's constraint base, that will be limited.
		hkReal m_minAngle;		///< Minimum angle value in radians (may be negative).
		hkReal m_maxAngle;		///< Maximum angle value in radians (may be negative).

		/// A stiffness factor [0..1] used by the solver; defaults to 1.0.
		hkReal m_angularLimitsTauFactor; //+default(1.0) +absmin(0) +absmax(1)
};


/// Atom which limits allowed relative angle between bodies' rotations along one specified rotation axis.
/// This constraint allows unconstrained movement within the specified range, and applies hard limits at its ends.
struct hkpTwistLimitConstraintAtom : public hkpConstraintAtom
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CONSTRAINT, hkpTwistLimitConstraintAtom );
		HK_DECLARE_REFLECTION();

		hkpTwistLimitConstraintAtom() : hkpConstraintAtom(TYPE_TWIST_LIMIT), m_isEnabled(true) {}
		hkpTwistLimitConstraintAtom(hkFinishLoadedObjectFlag f) : hkpConstraintAtom(f) {}
		HK_FORCE_INLINE hkpConstraintAtom* next() const { return const_cast<hkpConstraintAtom*>( static_cast<const hkpConstraintAtom*>(this+1) ); }
		HK_FORCE_INLINE int numSolverResults() const { return hkpJacobianSchemaInfo::AngularLimits1D::Results; }
		HK_FORCE_INLINE void addToConstraintInfo(hkpConstraintInfo& infoOut) const { infoOut.add<hkpJacobianSchemaInfo::AngularLimits1D>(); }

	public:

		/// Tells whether the atom should be handled by the solver.
		/// Note that if it is not, the atom's corresponding hkpSolverResults are not updated.
		hkUint8 m_isEnabled;
					
		hkUint8 m_twistAxis;	///< The index of the axis in the bodyA's constraint base, that will be limited.
		hkUint8 m_refAxis;		///< The index of a perpendicular axis used as a reference to measure the angle.
		hkReal m_minAngle;		///< Minimum angle value in radians (may be negative).
		hkReal m_maxAngle;		///< Maximum angle value in radians (may be negative).

		/// A stiffness factor [0..1] used by the solver; defaults to 1.0.
		hkReal m_angularLimitsTauFactor; //+default(1.0) +absmin(0) +absmax(1)

#if !defined(HK_REAL_IS_DOUBLE)
		hkUint8 m_padding[12]; //+nosave
#endif
};


/// Atom which limits allowed relative angle between bodies' rotations as measured between two chosen axes.
/// This allows unconstrained movement within the specified range, and applies hard limits at its ends.
struct hkpConeLimitConstraintAtom : public hkpConstraintAtom
{
	public:

		/// Specifies how the angle between the two reference vectors is measured.
		// Do not change enumeration values! They are used in calculations.
		enum MeasurementMode
		{
			/// Zero-angle corresponds to situation where the two vectors are aligned.
			ZERO_WHEN_VECTORS_ALIGNED = 0,
			/// Zero-angle corresponds to situation where the two vectors are perpendicular, and (+)90-degree corresponds to vectors being aligned.
			ZERO_WHEN_VECTORS_PERPENDICULAR = 1
		};

	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CONSTRAINT, hkpConeLimitConstraintAtom );
		HK_DECLARE_REFLECTION();

		hkpConeLimitConstraintAtom() : hkpConstraintAtom(TYPE_CONE_LIMIT), m_isEnabled(true), m_memOffsetToAngleOffset(0) {}
		hkpConeLimitConstraintAtom(hkFinishLoadedObjectFlag f) : hkpConstraintAtom(f) {}

		HK_FORCE_INLINE hkpConstraintAtom* next() const { return const_cast<hkpConstraintAtom*>( static_cast<const hkpConstraintAtom*>(this+1) ); }
		HK_FORCE_INLINE int numSolverResults() const { return hkpJacobianSchemaInfo::AngularLimits1D::Results; }
		HK_FORCE_INLINE void addToConstraintInfo(hkpConstraintInfo& infoOut) const { infoOut.add<hkpJacobianSchemaInfo::AngularLimits1D>(); }

	public:

		/// Tells whether the atom should be handled by the solver.
		/// Note that if it is not, the atom's corresponding hkpSolverResults are not updated.
		hkUint8 m_isEnabled;

		/// The index of the axis in the bodyA's constraint base, that will be used as a reference vector and constrained to lie within the limit cone.
		hkUint8 m_twistAxisInA;

		/// The index of the axis in the bodyB's constraint base, that will be used as a reference and limit-cone axis.
		hkUint8 m_refAxisInB;

		/// Specifies how the angle between the two reference vectors is measured.
		hkEnum<MeasurementMode, hkUint8> m_angleMeasurementMode;

		/// Memory offset to location in runtime where m_coneAngleOffset is stored.
		/// That is used to stabilize the constraint.
		/// Zero offset means, that no extra stabilization is done.
		hkUint8 m_memOffsetToAngleOffset; //+default(1)

		hkReal m_minAngle;		///< Minimum angle value in radians (may be negative).
		hkReal m_maxAngle;		///< Maximum angle value in radians (may be negative).

		/// A stiffness factor [0..1] used by the solver; defaults to 1.0.
		hkReal m_angularLimitsTauFactor; //+default(1.0) +absmin(0) +absmax(1)

#if !defined(HK_REAL_IS_DOUBLE)
		hkUint8 m_padding[12]; //+nosave
#endif
};


/// Atom which applies friction torque along one, two, or three specified rotation axes.
struct hkpAngFrictionConstraintAtom : public hkpConstraintAtom
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CONSTRAINT, hkpAngFrictionConstraintAtom );
		HK_DECLARE_REFLECTION();

		hkpAngFrictionConstraintAtom() : hkpConstraintAtom(TYPE_ANG_FRICTION), m_isEnabled(true), m_numFrictionAxes(1) {}
		hkpAngFrictionConstraintAtom(hkFinishLoadedObjectFlag f) : hkpConstraintAtom(f) {}

		HK_FORCE_INLINE hkpConstraintAtom* next() const { return const_cast<hkpConstraintAtom*>( static_cast<const hkpConstraintAtom*>(this+1) ); }
		HK_FORCE_INLINE int numSolverResults() const { return m_numFrictionAxes * hkpJacobianSchemaInfo::AngularFriction1D::Results; }
		HK_FORCE_INLINE void addToConstraintInfo(hkpConstraintInfo& infoOut) const { infoOut.addMultiple<hkpJacobianSchemaInfo::AngularFriction1D>(m_numFrictionAxes); }

	public:

		/// Tells whether the atom should be handled by the solver.
		/// Note that if it is not, the atom's corresponding hkpSolverResults are not updated.
		hkUint8 m_isEnabled;
				
		hkUint8 m_firstFrictionAxis;	///< Index of the first axis to apply friction along, in bodyA's constraint base.
		hkUint8 m_numFrictionAxes;		///< Number of subsequent base axes to constrain.			
		hkReal m_maxFrictionTorque;		///< Maximum allowed torque to be applied due to friction.

#if defined(HK_REAL_IS_DOUBLE)
		// padding to 32 bytes
		hkUint8 m_padding[16]; //+nosave
#else
		// padding to 16 bytes
		hkUint8 m_padding[4]; //+nosave
#endif
};


/// Atom which controls relative rotation angle between bodies around a specified rotation axes.
///
/// Note that motor atoms require access to external variables stored in hkpConstraintInstance's runtime.
/// The atom accesses those variables using memory offsets (stored in the atom's members).
/// Also when the motor is to operate in a range exceeding the [-Pi, Pi] range it must have a reference
/// onto solver results of a corresponding hkpAngLimitConstraintAtom to retrieve the proper angle value.
struct hkpAngMotorConstraintAtom : public hkpConstraintAtom
{
	//+version(1)
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CONSTRAINT, hkpAngMotorConstraintAtom );
		HK_DECLARE_REFLECTION();

		hkpAngMotorConstraintAtom() : hkpConstraintAtom(TYPE_ANG_MOTOR), m_isEnabled(true),
			m_initializedOffset(-1), m_previousTargetAngleOffset(-1), m_correspondingAngLimitSolverResultOffset(-1) {}
		hkpAngMotorConstraintAtom(hkFinishLoadedObjectFlag f) : hkpConstraintAtom(f),
			m_initializedOffset(-1), m_previousTargetAngleOffset(-1), m_correspondingAngLimitSolverResultOffset(-1) {}

		HK_FORCE_INLINE hkpConstraintAtom* next() const { return const_cast<hkpConstraintAtom*>( static_cast<const hkpConstraintAtom*>(this+1) ); }
		HK_FORCE_INLINE int numSolverResults() const { return hkpJacobianSchemaInfo::AngularMotor1D::Results; }
		HK_FORCE_INLINE void addToConstraintInfo(hkpConstraintInfo& infoOut) const { infoOut.add<hkpJacobianSchemaInfo::AngularMotor1D>(); }

	public:

		/// Tells whether the atom should be handled by the solver.
		/// Note that if it is not, the atom's corresponding hkpSolverResults are not updated.
		hkBool m_isEnabled;

		/// The index of the axis in the bodyA's constraint base, that will be controlled.
		hkUint8 m_motorAxis;

		/// Memory offset from atom's solver results to runtime's m_initialized member.
		hkInt16 m_initializedOffset;	//+nosave

		/// Memory offset from atom's solver results to runtime's m_previousTargetAngle member
		hkInt16 m_previousTargetAngleOffset;	//+nosave

		/// This is an optional offset to solver results of an angular limit atom.
		/// The results store the actual angle from the last frame, and are needed if the motor
		/// is to allow 'screw' functionality (i.e., orientation is not represented by a cyclic
		/// [-180deg, 180deg] range, but as an unlimited number of degrees/rotations).
		hkInt16 m_correspondingAngLimitSolverResultOffset;	//+nosave

		/// The target angle for the motor.
		hkReal m_targetAngle;

		/// Motor; note that it is reference counted and should be handled by the owning constraint's get/set methods.
		HK_CPU_PTR(hkpConstraintMotor*) m_motor;

#if !defined(HK_REAL_IS_DOUBLE)
		// padding to 16 bytes
		hkUint8 m_padding[12]; //+nosave
#endif
};


/// Atom which controls relative rotation angle between bodies in three dimensions; used by the hkpRagdollConstraintData.
/// Note that motor atoms require access to external variables stored in hkpConstraintInstance's runtime.
/// The atom accesses those variables using memory offsets (stored in the atom's members).
struct hkpRagdollMotorConstraintAtom : public hkpConstraintAtom
{
	//+version(1)
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CONSTRAINT, hkpRagdollMotorConstraintAtom );
		HK_DECLARE_REFLECTION();

		hkpRagdollMotorConstraintAtom() : hkpConstraintAtom(TYPE_RAGDOLL_MOTOR), m_isEnabled(true),
			m_initializedOffset(-1), m_previousTargetAnglesOffset(-1) {}
		hkpRagdollMotorConstraintAtom(hkFinishLoadedObjectFlag f) : hkpConstraintAtom(f),
			m_initializedOffset(-1), m_previousTargetAnglesOffset(-1) {}

		HK_FORCE_INLINE hkpConstraintAtom* next() const { return const_cast<hkpConstraintAtom*>( static_cast<const hkpConstraintAtom*>(this+1) ); }
		HK_FORCE_INLINE int numSolverResults() const { return 3*hkpJacobianSchemaInfo::AngularMotor1D::Results; }
		HK_FORCE_INLINE void addToConstraintInfo(hkpConstraintInfo& infoOut) const { infoOut.addMultiple<hkpJacobianSchemaInfo::AngularMotor1D>(3); }

	public:

		/// Tells whether the atom should be handled by the solver.
		/// Note that if it is not, the atom's corresponding hkpSolverResults are not updated.
		hkBool m_isEnabled;

		/// Memory offset from atom's solver results to runtime's m_initialized member.
		hkInt16 m_initializedOffset;	//+nosave

		/// Memory offset from atom's solver results to runtime's m_previousTargetAngle member.
		hkInt16 m_previousTargetAnglesOffset;	//+nosave

		/// The target relative rotation the motors will try to match.
		/// This is the target rotation from bodyA's constraint space into the bodyB's (non-constraint) space.
		hkMatrix3 m_target_bRca;

		/// Three motors; note that they are reference counted and should be handled by the owning constraint's get/set methods.
		HK_CPU_PTR(hkpConstraintMotor*) m_motors[3];
};


/// Atom which applies friction force along a specified axes.
struct hkpLinFrictionConstraintAtom : public hkpConstraintAtom
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CONSTRAINT, hkpLinFrictionConstraintAtom );
		HK_DECLARE_REFLECTION();

		hkpLinFrictionConstraintAtom() : hkpConstraintAtom(TYPE_LIN_FRICTION), m_isEnabled(true) {}
		hkpLinFrictionConstraintAtom(hkFinishLoadedObjectFlag f) : hkpConstraintAtom(f) {}

		HK_FORCE_INLINE hkpConstraintAtom* next() const { return const_cast<hkpConstraintAtom*>( static_cast<const hkpConstraintAtom*>(this+1) ); }
		HK_FORCE_INLINE int numSolverResults() const { return  hkpJacobianSchemaInfo::Friction1D::Results; }
		HK_FORCE_INLINE void addToConstraintInfo(hkpConstraintInfo& infoOut) const { infoOut.add<hkpJacobianSchemaInfo::Friction1D>(); }

	public:

		/// Tells whether the atom should be handled by the solver.
		/// Note that if it is not, the atom's corresponding hkpSolverResults are not updated.
		hkUint8 m_isEnabled;
					
		hkUint8 m_frictionAxis;		///< Index of the axis to apply friction along, in bodyB's constraint base.
		hkReal m_maxFrictionForce;	///< Maximum allowed force to be applied due to friction.

#if defined(HK_REAL_IS_DOUBLE)
		// padding to 32 bytes
		hkUint8 m_padding[16]; //+nosave
#else
		// padding to 16 bytes
		hkUint8 m_padding[8]; //+nosave
#endif
};


/// Atom which controls relative velocity of bodies along a specified axis.
///
/// Note that motor atoms require access to external variables stored in hkpConstraintInstance's runtime.
/// The atom accesses those variables using memory offsets (stored in the atom's members).
struct hkpLinMotorConstraintAtom : public hkpConstraintAtom
{
	//+version(1)
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CONSTRAINT, hkpLinMotorConstraintAtom );
		HK_DECLARE_REFLECTION();

		hkpLinMotorConstraintAtom() : hkpConstraintAtom(TYPE_LIN_MOTOR), m_isEnabled(true),
			m_initializedOffset(-1), m_previousTargetPositionOffset(-1) {}
		hkpLinMotorConstraintAtom(hkFinishLoadedObjectFlag f) : hkpConstraintAtom(f),
			m_initializedOffset(-1), m_previousTargetPositionOffset(-1) {}

		HK_FORCE_INLINE hkpConstraintAtom* next() const { return const_cast<hkpConstraintAtom*>( static_cast<const hkpConstraintAtom*>(this+1) ); }
		HK_FORCE_INLINE int numSolverResults() const { return hkpJacobianSchemaInfo::LinearMotor1D::Results; }
		HK_FORCE_INLINE void addToConstraintInfo(hkpConstraintInfo& infoOut) const { infoOut.add<hkpJacobianSchemaInfo::LinearMotor1D>(); }

	public:

		hkBool m_isEnabled;						///< A flag saying whether the motor is active
		hkUint8 m_motorAxis;					///< The index of the axis in the bodyB's constraint base, that will be controlled.
		
		/// Memory offset from atom's solver results to runtime's m_initialized member.
		hkInt16 m_initializedOffset;	//+nosave

		/// Memory offset from atom's solver results to runtime's m_previousTargetPosition member.
		hkInt16 m_previousTargetPositionOffset;	//+nosave

		hkReal m_targetPosition;				///< The target position for the motor.

		/// Motor; note that it is reference counted and should be handled by the owning constraint's get/set methods.
		HK_CPU_PTR(hkpConstraintMotor*) m_motor;

#if defined(HK_REAL_IS_DOUBLE)
		hkUint8 m_padding[8]; //+nosave
#endif
};


/// Atom which implements a functionality of a pulley, where bodies are attached to a rope, and the rope is lead
/// through two pulley wheels at fixed world positions.
struct hkpPulleyConstraintAtom : public hkpConstraintAtom
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CONSTRAINT, hkpPulleyConstraintAtom );
		HK_DECLARE_REFLECTION();

		hkpPulleyConstraintAtom() : hkpConstraintAtom(TYPE_PULLEY) { }
		hkpPulleyConstraintAtom(hkFinishLoadedObjectFlag f) : hkpConstraintAtom(f) {}

		HK_FORCE_INLINE hkpConstraintAtom* next() const { return const_cast<hkpConstraintAtom*>( static_cast<const hkpConstraintAtom*>(this+1) ); }
		HK_FORCE_INLINE int numSolverResults() const { return hkpJacobianSchemaInfo::Pulley1D::Results; }
		HK_FORCE_INLINE void addToConstraintInfo(hkpConstraintInfo& infoOut) const { infoOut.add<hkpJacobianSchemaInfo::Pulley1D>(); }

	public:
		
		hkVector4 m_fixedPivotAinWorld;		///< Pulley's first fixed pivot point.
		hkVector4 m_fixedPivotBinWorld;		///< Pulley's second fixed pivot point.
		hkReal m_ropeLength;				///< The rest length (equal to ((BodyA's rope) + leverageOnBodyB * (BodyB's rope length)) )

		/// Leverage ratio: e.g., value of 2 means that bodyA's rope length changes by twice as much as bodyB's,
		/// and the constraint exerts twice as big forces upon bodyB.
		hkReal m_leverageOnBodyB;
};


/// Atom which implements functionality of a rack-and-pinion or also a screw.
struct hkpRackAndPinionConstraintAtom : public hkpConstraintAtom
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CONSTRAINT, hkpRackAndPinionConstraintAtom );
		HK_DECLARE_REFLECTION();

		hkpRackAndPinionConstraintAtom() : hkpConstraintAtom(TYPE_RACK_AND_PINION) {}
		hkpRackAndPinionConstraintAtom(hkFinishLoadedObjectFlag f) : hkpConstraintAtom(f) {}

		HK_FORCE_INLINE hkpConstraintAtom* next() const { return const_cast<hkpConstraintAtom*>( static_cast<const hkpConstraintAtom*>(this+1) ); }
		HK_FORCE_INLINE int numSolverResults() const { return hkpJacobianSchemaInfo::BilateralUserTau1D::Results; }
		HK_FORCE_INLINE void addToConstraintInfo(hkpConstraintInfo& infoOut) const { infoOut.add<hkpJacobianSchemaInfo::BilateralUserTau1D>(); }

	public:

		/// Pinion radius. In the case of a screw constraint, this has represents the screw's pitch (thread width),
		/// which is the distance along the screw's axis covered by one full rotation.
		///
		/// To reverse the direction of linear movement (and, at the same time, flip the generated point where force
		/// is applied) you can reverse the shift axis or use negative pinionRadius/screwPitch.
		hkReal m_pinionRadiusOrScrewPitch;

		/// This marks the atom as operating in the screw mode.
		hkBool m_isScrew;

		/// Memory offset from atom's solver results to runtime's m_initialAngleOffset member.
		/// The member is set to non-zero value to mark runtime as initialized.
		hkInt8 m_memOffsetToInitialAngleOffset;

		/// Memory offset from atom's solver results to runtime's m_prevAngle member.
		hkInt8 m_memOffsetToPrevAngle;

		/// Memory offset from atom's solver results to runtime's m_revolutionCounter member.
		hkInt8 m_memOffsetToRevolutionCounter;

#if defined(HK_REAL_IS_DOUBLE)
		// padding to 32 bytes
		hkUint8 m_padding[8]; //+nosave
#else
		// padding to 16 bytes
		hkUint8 m_padding[4]; //+nosave
#endif
};


/// Atom which implements functionality of cog wheels.
struct hkpCogWheelConstraintAtom : public hkpConstraintAtom
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CONSTRAINT, hkpCogWheelConstraintAtom );
		HK_DECLARE_REFLECTION();
	
		hkpCogWheelConstraintAtom() : hkpConstraintAtom(TYPE_COG_WHEEL) {}
		hkpCogWheelConstraintAtom(hkFinishLoadedObjectFlag f) : hkpConstraintAtom(f) {}

		HK_FORCE_INLINE hkpConstraintAtom* next() const { return const_cast<hkpConstraintAtom*>( static_cast<const hkpConstraintAtom*>(this+1) ); }
		HK_FORCE_INLINE int numSolverResults() const { return hkpJacobianSchemaInfo::BilateralUserTau1D::Results; }
		HK_FORCE_INLINE void addToConstraintInfo(hkpConstraintInfo& infoOut) const { infoOut.add<hkpJacobianSchemaInfo::BilateralUserTau1D>(); }

	public:

		hkReal m_cogWheelRadiusA;	///< Radius of the cog wheel A.
		hkReal m_cogWheelRadiusB;	///< Radius of the cog wheel B.
		hkBool m_isScrew;			// unused

		/// Memory offset from atom's solver results to runtime's m_initialAngleOffset[2] member.
		/// The first element is set to non-zero value to mark runtime as initialized.
		hkInt8 m_memOffsetToInitialAngleOffset;

		/// Memory offset from atom's solver results to runtime's m_prevAngle[2] member.
		hkInt8 m_memOffsetToPrevAngle;

		/// Memory offset from atom's solver results to runtime's m_revolutionCounter[2] member.
		hkInt8 m_memOffsetToRevolutionCounter;
};


#endif // HKP_CONSTRAINT_ATOM_H

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
