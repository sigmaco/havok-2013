/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_COG_WHEEL_CONSTRAINT_DATA_H
#define HKP_COG_WHEEL_CONSTRAINT_DATA_H

#include <Physics/Constraint/Data/hkpConstraintData.h>


/// This constraint represents interaction between two cogwheels.
///
/// This is a simple one-dimensional constraint only. In order to create a meaningful mechanism, the elements linked
/// must be connected to other external constraints with additional hinge constraints. hkpConstraintUtils has helper
/// functions that will allow you to easily create those.
///
/// Note that the axes of the cog wheels don't have to be fixed at one relative position. The wheel axes are free
/// to move in a (physically sensible) range. And the constraints should properly track the contact point of the wheels.
/// It will also work, when the cogs are physically disjoint at times.
///
/// If you experience stability problems in bigger setups, the external prismatic and hinge constraints should be given
/// higher priority, or the rack-and-pinion constraint added first.
///
class hkpCogWheelConstraintData : public hkpConstraintData
{
	public:

		enum
		{
			SOLVER_RESULT_COG_WHEEL	= 0,
			SOLVER_RESULT_MAX		= 1
		};

		struct Runtime
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_DYNAMICS, hkpCogWheelConstraintData::Runtime );

			hkpSolverResults m_solverResults[SOLVER_RESULT_MAX];

			// This stores the initial relative angular orientation of the bodies. 0 if uninitialized (triggers 
			// initialization of m_revolutionCounter too). Non-zero when initialized (set to a tiny number 
			// (< HK_REAL_EPSILON) for zero values).
			HK_ALIGN(hkReal m_initialAngleOffset[2],HK_REAL_SIZE);

			// Previously calculated relative angle.
			HK_ALIGN(hkReal m_prevAngle[2],HK_REAL_SIZE);

			// This counts revolutions of the cog wheel to properly calculate the Rhs. Auto-initialized to 0.
			hkInt32	m_revolutionCounter[2];
		};

		struct Atoms
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_DYNAMICS, hkpCogWheelConstraintData::Atoms );
			HK_DECLARE_REFLECTION();

			Atoms() {}

			Atoms(hkFinishLoadedObjectFlag f) : m_transforms(f), m_cogWheels(f) {}

			// get a pointer to the first atom
			const hkpConstraintAtom* getAtoms() const { return &m_transforms; }

			// get the size of all atoms (we can't use sizeof(*this) because of align16 padding)
			int getSizeOfAllAtoms() const { return hkGetByteOffsetInt(this, &m_cogWheels+1); }

			hkpSetLocalTransformsConstraintAtom	m_transforms;
			hkpCogWheelConstraintAtom			m_cogWheels;
		};
		
	public:
		
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
		HK_DECLARE_REFLECTION();

		/// Constructor
		hkpCogWheelConstraintData();

		/// Serialization constructor
		hkpCogWheelConstraintData(hkFinishLoadedObjectFlag f) : hkpConstraintData(f), m_atoms(f) {}

		/// Sets the cog wheels up with world space information.
		void setInWorldSpace(	const hkTransform& bodyATransform, const hkTransform& bodyBTransform,
								const hkVector4& rotationPivotA, const hkVector4& rotationAxisA, hkReal radiusA,
								const hkVector4& rotationPivotB, const hkVector4& rotationAxisB, hkReal radiusB);
										
		/// Sets the cog wheels up with body space information.
		/// The parameters are analogical to setInWorldSpace().
		void setInBodySpace( const hkVector4& rotationPivotAInA, const hkVector4& rotationAxisAInA, hkReal radiusA,
							 const hkVector4& rotationPivotBInB, const hkVector4& rotationAxisBInB, hkReal radiusB);

		inline Runtime* getRuntime( hkpConstraintRuntime* runtime ){ return reinterpret_cast<Runtime*>(runtime); }

		//
		// hkpConstraintData implementation
		//

		virtual int getType() const;
		
		virtual hkBool isValid() const;

		virtual void getConstraintInfo( hkpConstraintData::ConstraintInfo& infoOut ) const;

		virtual void getRuntimeInfo( hkBool wantRuntime, hkpConstraintData::RuntimeInfo& infoOut ) const;
		
	public:

		HK_ALIGN_REAL( Atoms m_atoms );
};

#include <Physics/Constraint/Data/CogWheel/hkpCogWheelConstraintData.inl>


#endif // HKP_COG_WHEEL_CONSTRAINT_DATA_H

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
