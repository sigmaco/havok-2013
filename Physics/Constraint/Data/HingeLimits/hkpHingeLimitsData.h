/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_HINGE_LIMITS_DATA_H
#define HKP_HINGE_LIMITS_DATA_H

#include <Physics/Constraint/Data/hkpConstraintData.h>

extern const class hkClass hkpHingeLimitsDataAtomsClass;
extern const hkClass hkpHingeLimitsDataClass;


/// This is a version of a hkLimitedHingeConstraint with removed linear constraints.
/// This constraint is meant to be used with hkConstraintChains (that correspond to the ball-and-socket part).
/// Once a chain has been defined, this constraint can be simply overlayed on top of it to impose additional
/// angular constraints. When this constraint is used together with hkpPoweredChainData, care should be taken
/// not to set the target in the powered chain data to lay outside the limits defined here.
class hkpHingeLimitsData : public hkpConstraintData
{
	public:

		enum 
		{
			SOLVER_RESULT_LIMITS		= 0,	// angular limits defined around m_freeAxisA 
			SOLVER_RESULT_ANG_AXIS_1	= 1,	// angular constraint defined by m_constrainedAxis1A
			SOLVER_RESULT_ANG_AXIS_2	= 2,	// angular constraint defined by m_constrainedAxis2A
			SOLVER_RESULT_MAX			= 3
		};

		struct Runtime
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_DYNAMICS, hkpHingeLimitsData::Runtime );

			hkpSolverResults m_solverResults[SOLVER_RESULT_MAX];
			hkReal m_lastAngle;		// used by limits
		};

		struct Atoms
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_DYNAMICS, hkpHingeLimitsData::Atoms );
			HK_DECLARE_REFLECTION();

			enum Axis
			{
				AXIS_AXLE = 0,
				AXIS_PERP_TO_AXLE_1 = 1,
				AXIS_PERP_TO_AXLE_2 = 2
			};

			Atoms() {}

			Atoms(hkFinishLoadedObjectFlag f) : m_rotations(f), m_angLimit(f), m_2dAng(f) {}

			// get a pointer to the first atom
			const hkpConstraintAtom* getAtoms() const { return &m_rotations; }

			// get the size of all atoms (we can't use sizeof(*this) because of align16 padding)
			int getSizeOfAllAtoms() const { return hkGetByteOffsetInt(this, &m_2dAng+1); }

			hkpSetLocalRotationsConstraintAtom	m_rotations;
			hkpAngLimitConstraintAtom			m_angLimit; 
			hkp2dAngConstraintAtom				m_2dAng;
		};

	public:
	
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_CONSTRAINT);
		HK_DECLARE_REFLECTION();

		/// Constructor.
		hkpHingeLimitsData();

		/// Serialization constructor.
		hkpHingeLimitsData(hkFinishLoadedObjectFlag f) : hkpConstraintData(f), m_atoms(f) {}

		/// Set the data for a Limited Hinge constraint with information given in body space.
		void setInBodySpace(const hkVector4& axisA, const hkVector4& axisB, 
								const hkVector4& axisAPerp, const hkVector4& axisBPerp);

		/// Set the data for a Limited Hinge constraint with information given in world space.
		void setInWorldSpace(const hkTransform& bodyATransform, const hkTransform& bodyBTransform, const hkVector4& axis);

		static inline Runtime* HK_CALL getRuntime( hkpConstraintRuntime* runtime ) { return reinterpret_cast<Runtime*>(runtime); }
	
		//
		// Methods to set and get angle limits
		//

		/// Sets the maximum angular limit.
		inline void setMaxAngularLimit(hkReal rad);

		/// Sets the minimum angular limit.
		inline void setMinAngularLimit(hkReal rad);

		/// Gets the maximum angular limit.
		inline hkReal getMaxAngularLimit() const;

		/// Gets the minimum angular limit.
		inline hkReal getMinAngularLimit() const;

		/// sets the m_angularLimitsTauFactor. This is a factor in the range between 0 and 1
		/// which controls the stiffness of the angular limits. If you slowly increase
		/// this value from 0 to 1 for a newly created constraint,
		/// you can nicely blend in the limits.
		inline void setAngularLimitsTauFactor( hkReal mag );
			
		/// get the m_angularLimitsTauFactor;
		inline hkReal getAngularLimitsTauFactor() const;

		//
		// hkpConstraintData implementation
		//

		virtual int getType() const;

		virtual hkBool isValid() const;

		virtual void getConstraintInfo( ConstraintInfo& infoOut ) const;

		virtual void getRuntimeInfo( hkBool wantRuntime, hkpConstraintData::RuntimeInfo& infoOut ) const;
		
	public:

		HK_ALIGN_REAL( Atoms m_atoms );
};

#include <Physics/Constraint/Data/HingeLimits/hkpHingeLimitsData.inl>


#endif // HKP_HINGE_LIMITS_DATA_H

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
