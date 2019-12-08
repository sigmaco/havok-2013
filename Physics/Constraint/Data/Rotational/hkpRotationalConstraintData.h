/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_ROTATIONAL_CONSTRAINT_DATA_H
#define HKP_ROTATIONAL_CONSTRAINT_DATA_H

#include <Physics/Constraint/Data/hkpConstraintData.h>

extern const class hkClass hkpRotationalConstraintDataAtomsClass;
extern const hkClass hkpRotationalConstraintDataClass;


//
class hkpRotationalConstraintData : public hkpConstraintData
{
	public:

		enum 
		{
			SOLVER_RESULT_ANG_0	= 0,	// linear constraint 
			SOLVER_RESULT_ANG_1	= 1,	// linear constraint 
			SOLVER_RESULT_ANG_2	= 2,	// linear constraint 
			SOLVER_RESULT_MAX	= 3
		};

		struct Runtime
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_DYNAMICS, hkpRotationalConstraintData::Runtime );

			hkpSolverResults m_solverResults[SOLVER_RESULT_MAX];
		};

		struct Atoms
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_DYNAMICS, hkpRotationalConstraintData::Atoms );
			HK_DECLARE_REFLECTION();

			inline Atoms() {}

			Atoms(hkFinishLoadedObjectFlag f) : m_rotations(f), m_ang(f) {}

			// get a pointer to the first atom
			const hkpConstraintAtom* getAtoms() const { return &m_rotations; }

			// get the size of all atoms (we can't use sizeof(*this) because of align16 padding)
			int getSizeOfAllAtoms() const { return hkGetByteOffsetInt(this, &m_ang+1); }

			hkpSetLocalRotationsConstraintAtom	m_rotations;
			hkpAngConstraintAtom				m_ang;
		};

	public:
	
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
		HK_DECLARE_REFLECTION();

		/// Constructor.
		hkpRotationalConstraintData();

		/// Serialization constructor.
		hkpRotationalConstraintData(hkFinishLoadedObjectFlag f) : hkpConstraintData(f), m_atoms(f) {}

		/// Sets relative orientation that is to be enforced.
		void setInBodySpace(const hkQuaternion& aTb);

		/// Will preserve the initial relative orientation of the bodies.
		void setInWorldSpace(const hkQuaternion& bodyARotation, const hkQuaternion& bodyBRotation);

		inline const Runtime* getRuntime( hkpConstraintRuntime* runtime ){ return reinterpret_cast<Runtime*>(runtime); }

		//
		// hkpConstraintData implementation
		//

		/// Get type from this constraint.
		virtual int getType() const;

		/// Check consistency of constraint members.
		virtual hkBool isValid() const;

		virtual void getConstraintInfo( hkpConstraintData::ConstraintInfo& info ) const;

		virtual void getRuntimeInfo( hkBool wantRuntime, hkpConstraintData::RuntimeInfo& infoOut ) const;

	public:
		
		HK_ALIGN_REAL( Atoms m_atoms );
};


#endif // HKP_ROTATIONAL_CONSTRAINT_DATA_H

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
