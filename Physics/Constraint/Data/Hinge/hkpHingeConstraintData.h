/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_HINGE_CONSTRAINT_DATA_H
#define HKP_HINGE_CONSTRAINT_DATA_H

#include <Physics/Constraint/Data/hkpConstraintData.h>

extern const class hkClass hkpHingeConstraintDataAtomsClass;
extern const hkClass hkpHingeConstraintDataClass;


/// Basic hinge constraint
class hkpHingeConstraintData : public hkpConstraintData
{
	public:

		enum
		{
			SOLVER_RESULT_ANG_0	= 0,	// angular constraint 0
			SOLVER_RESULT_ANG_1	= 1,	// angular constraint 1
			SOLVER_RESULT_LIN_0	= 2,	// linear constraint defined by m_constrainedAxis1B
			SOLVER_RESULT_LIN_1	= 3,	// linear constraint defined by m_constrainedAxis2B
			SOLVER_RESULT_LIN_2	= 4,	// linear constraint defined by m_constrainedAxis2B
			SOLVER_RESULT_MAX	= 5
		};

		struct Runtime
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_DYNAMICS, hkpHingeConstraintData::Runtime );

			hkpSolverResults m_solverResults[SOLVER_RESULT_MAX];
		};

		struct Atoms
		{
			// +version(1)
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_DYNAMICS, hkpHingeConstraintData::Atoms );
			HK_DECLARE_REFLECTION();

			enum Axis
			{
				AXIS_AXLE = 0
			};

			inline Atoms() {}

			Atoms(hkFinishLoadedObjectFlag f) : m_transforms(f), m_setupStabilization(f), m_2dAng(f), m_ballSocket(f) {}

			// get a pointer to the first atom
			const hkpConstraintAtom* getAtoms() const { return &m_transforms; }

			// get the size of all atoms (we can't use sizeof(*this) because of align16 padding)
			int getSizeOfAllAtoms() const { return hkGetByteOffsetInt(this, &m_ballSocket + 1); }

			hkpSetLocalTransformsConstraintAtom	m_transforms;
			hkpSetupStabilizationAtom			m_setupStabilization;
			hkp2dAngConstraintAtom				m_2dAng;
			hkpBallSocketConstraintAtom			m_ballSocket;
		};

	public:
		
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
		HK_DECLARE_REFLECTION();

		/// Constructor.
		hkpHingeConstraintData();

		/// Serialization constructor.
		hkpHingeConstraintData(hkFinishLoadedObjectFlag f) : hkpConstraintData(f), m_atoms(f) {}

		/// Set the data for a Hinge constraint with information given in body space.
		/// \param pivotA The constraint pivot point, specified in bodyA space.
		/// \param pivotB The constraint pivot point, specified in bodyB space.
		/// \param axisA The hinge axis, specified in bodyA space.
		/// \param axisB The hinge axis, specified in bodyB space.
		void setInBodySpace(const hkVector4& pivotA, const hkVector4& pivotB, const hkVector4& axisA, const hkVector4& axisB);
	
		/// Set the data for a Hinge constraint with information given in world space.
		/// \param bodyA The first rigid body transform
		/// \param bodyB The second rigid body transform
		/// \param pivot The pivot point, specified in world space.
		/// \param axis The hinge axis, specified in world space.
		void setInWorldSpace(const hkTransform& bodyATransform, const hkTransform& bodyBTransform, const hkVector4& pivot, const hkVector4& axis);

		static inline Runtime* HK_CALL getRuntime( hkpConstraintRuntime* runtime ) { return reinterpret_cast<Runtime*>(runtime); }

		//
		// hkpConstraintData implementation
		//

		/// Get type from this constraint
		virtual int getType() const;

		/// Check consistency of constraint members
		virtual hkBool isValid() const;

		virtual void getConstraintInfo( hkpConstraintData::ConstraintInfo& infoOut ) const ;

		/// Sets the impulse above which this constraint is reported as breached.
		/// Set it to HK_REAL_MAX to effectively disable the limit.
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


#endif // HKP_HINGE_CONSTRAINT_DATA_H

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
