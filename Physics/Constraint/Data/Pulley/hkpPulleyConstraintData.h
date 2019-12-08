/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_PULLEY_CONSTRAINT_DATA_H
#define HKP_PULLEY_CONSTRAINT_DATA_H

#include <Physics/Constraint/Data/hkpConstraintData.h>


//
class hkpPulleyConstraintData : public hkpConstraintData
{
	public:

		enum 
		{
			SOLVER_RESULT_LIN_0	= 0,	// linear constraint 
			SOLVER_RESULT_MAX	= 1
		};

		struct Runtime
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_DYNAMICS, hkpPulleyConstraintData::Runtime );

			hkpSolverResults m_solverResults[SOLVER_RESULT_MAX];
		};

		struct Atoms
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_DYNAMICS, hkpPulleyConstraintData::Atoms );
			HK_DECLARE_REFLECTION();

			Atoms() {}

			Atoms(hkFinishLoadedObjectFlag f) : m_translations(f), m_pulley(f) {}

			// get a pointer to the first atom
			const hkpConstraintAtom* getAtoms() const { return &m_translations; }

			// get the size of all atoms (we can't use sizeof(*this) because of align16 padding)
			int getSizeOfAllAtoms() const { return hkGetByteOffsetInt(this, &m_pulley+1); }

			hkpSetLocalTranslationsConstraintAtom    m_translations;
			hkpPulleyConstraintAtom                  m_pulley;
		};

	public:
	
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
		HK_DECLARE_REFLECTION();
		
		/// Constructor.
		hkpPulleyConstraintData();

		/// Serialization constructor.
		hkpPulleyConstraintData(hkFinishLoadedObjectFlag f) : hkpConstraintData(f), m_atoms(f) {}

		/// Sets the pulley up with world space information.
		/// Will compute a rest length too (so call setlength after this if needed)
		inline void setInWorldSpace(const hkTransform& bodyATransform, const hkTransform& bodyBTransform, 
								const hkVector4& pivotAW, const hkVector4& pivotBW,
								const hkVector4& pulleyPivotAW, const hkVector4& pulleyPivotBW, hkReal leverageOnBodyB );

		/// Sets the pulley up with body space information.
		/// Will compute a rest length too (so call setlength after this if needed)
		/// and that is why the transforms are given (so that the length can be computed in world space)
		inline void setInBodySpace(const hkTransform& bodyATransform, const hkTransform& bodyBTransform,
								const hkVector4& pivotA, const hkVector4& pivotB,
								const hkVector4& pulleyPivotAW, const hkVector4& pulleyPivotBW, hkReal leverageOnBodyB );

		/// Gets the length of the rope. Full length == length of rope from bodyA to pulleyPivotA + leverageRation * (length of rope from body B to pulleyPivotB)
		inline hkReal getRopeLength(hkReal length); 
		
		/// Gets the leverage ratio of the pulley. Pulley exerts 'leverageRatio' times greater forces on bodyB.
		inline hkReal getLeverageOnBodyB();

		/// Sets the length of the rope. Full length == length of rope from bodyA to pulleyPivotA + leverageRation * (length of rope from body B to pulleyPivotB)
		inline void setRopeLength(hkReal length);

		/// Sets the leverage ratio of the pulley. Pulley exerts 'leverageRatio' times greater forces on bodyB.
		inline void setLeverageOnBodyB(hkReal leverageOnBodyB);

		inline const Runtime* getRuntime( hkpConstraintRuntime* runtime ) { return reinterpret_cast<Runtime*>(runtime); }

		//
		// hkpConstraintData implementation
		//

		virtual int getType() const;

		hkBool isValid() const;

		virtual void getConstraintInfo( hkpConstraintData::ConstraintInfo& infoOut ) const;

		virtual void getRuntimeInfo( hkBool wantRuntime, hkpConstraintData::RuntimeInfo& infoOut ) const;
		
	public:
		
		HK_ALIGN_REAL( Atoms m_atoms );
};

#include <Physics/Constraint/Data/Pulley/hkpPulleyConstraintData.inl>


#endif // HKP_PULLEY_CONSTRAINT_DATA_H

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
