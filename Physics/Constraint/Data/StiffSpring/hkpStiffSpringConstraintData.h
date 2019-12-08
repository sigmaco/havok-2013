/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_STIFF_SPRING_CONSTRAINT_DATA_H
#define HKP_STIFF_SPRING_CONSTRAINT_DATA_H

#include <Physics/Constraint/Data/hkpConstraintData.h>

extern const class hkClass hkpStiffSpringConstraintDataAtomsClass;
extern const hkClass hkpStiffSpringConstraintDataClass;


/// A stiff spring constraint. It holds the constrained bodies apart at a specified distance,
/// as if they were attached at each end of an invisible rod.
class hkpStiffSpringConstraintData : public hkpConstraintData
{
	public:

		enum
		{
			SOLVER_RESULT_LIN_0	= 0,	// linear constraint 
			SOLVER_RESULT_MAX	= 1
		};

		struct Runtime
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_DYNAMICS, hkpStiffSpringConstraintData::Runtime );

			hkpSolverResults m_solverResults[SOLVER_RESULT_MAX];
		};

		struct Atoms
		{
			//+version(1)
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_DYNAMICS, hkpStiffSpringConstraintData::Atoms );
			HK_DECLARE_REFLECTION();

			Atoms() {}

			Atoms(hkFinishLoadedObjectFlag f) : m_pivots(f), m_setupStabilization(f), m_spring(f) {}

			// get a pointer to the first atom
			const hkpConstraintAtom* getAtoms() const { return &m_pivots; }

			// get the size of all atoms (we can't use sizeof(*this) because of align16 padding)
			int getSizeOfAllAtoms() const { return hkGetByteOffsetInt(this, &m_spring+1); }

			hkpSetLocalTranslationsConstraintAtom	m_pivots;
			hkpSetupStabilizationAtom				m_setupStabilization;
			hkpStiffSpringConstraintAtom			m_spring;
		};

	public:
	
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
		HK_DECLARE_REFLECTION();
		
		/// Constructor.
		hkpStiffSpringConstraintData();
		
		/// Serialization constructor.
		hkpStiffSpringConstraintData(hkFinishLoadedObjectFlag f) : hkpConstraintData(f), m_atoms(f) {}

		/// Sets the spring up with world space information.
		/// Will compute a rest length too (so call setlength after this if needed)
		/// \param pivotA			bodyA's pivot point, specified in world space.
		/// \param pivotB			bodyB's pivot point, specified in world space.
		inline void setInWorldSpace(const hkTransform& bodyATransform, const hkTransform& bodyBTransform, 
								const hkVector4& pivotAW, const hkVector4& pivotBW);

		/// Sets the spring up with body space information.
		/// \param pivotA			bodyA's pivot point, specified in bodyA's space.
		/// \param pivotB			bodyB's pivot point, specified in bodyB's space.
		/// \param restLength		The length of the stiff spring when at rest
		inline void setInBodySpace(const hkVector4& pivotA, const hkVector4& pivotB, hkReal restLength);

		/// Gets the length of the stiff spring.
		inline hkReal getSpringMinLength() const;
		inline hkReal getSpringMaxLength() const;

		/// Sets the length of the stiff spring when at rest.
		inline void setSpringLength( hkReal minLength, hkReal maxLength );

		/// Sets the length of the stiff spring when at rest.
		inline void setSpringLength( hkReal length );

		inline const Runtime* getRuntime( hkpConstraintRuntime* runtime ){ return reinterpret_cast<Runtime*>(runtime); }

		//
		// hkpConstraintData implementation
		//

		hkBool isValid() const;

		virtual int getType() const;

		virtual void getConstraintInfo( ConstraintInfo& infoOut ) const;

		virtual void getRuntimeInfo( hkBool wantRuntime, hkpConstraintData::RuntimeInfo& infoOut ) const;

	public:

		HK_ALIGN_REAL( Atoms m_atoms );
};

#include <Physics/Constraint/Data/StiffSpring/hkpStiffSpringConstraintData.inl>


#endif // HKP_STIFF_SPRING_CONSTRAINT_DATA_H

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
