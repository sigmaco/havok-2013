/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_RACK_AND_PINION_CONSTRAINT_DATA_H
#define HKP_RACK_AND_PINION_CONSTRAINT_DATA_H

#include <Physics/Constraint/Data/hkpConstraintData.h>


/// This constraint represents interaction between a pinion and a rack elements; or between a screw and its nut.
///
/// This is a simple one-dimensional constraint only. In order to create a meaningful mechanism, the elements linked
/// must be connected to other external constraints -- most probably a prismatic constraint for the rack, and a hinge,
/// or limited-hinge for the pinion. This constraintData has helper functions that will allow you to easily create
/// those.
///
/// Note that the axes of the rack and pinion don't have to be fixed at one relative position. The axes are free
/// to move in a (physically sensible) range. And the constraints should properly track the contact point of the parts.
/// It will also work, when the parts are physically disjoint at times. Note that the interaction force is always
/// determined by the direction of the bodyB (and it's shiftAxis, which is stored in bodyB's local space).
/// 
/// If you experience stability problems in bigger setups, the external prismatic and hinge constraints should
/// have higher priority or the rack-and-pinion constraint should be added first.
///
class hkpRackAndPinionConstraintData : public hkpConstraintData
{
	public:

		enum Type
		{
			TYPE_RACK_AND_PINION,
			TYPE_SCREW
		};

		enum 
		{
			SOLVER_RESULT_RACK_AND_PINION	= 0,
			SOLVER_RESULT_MAX				= 1
		};

		struct Runtime
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_DYNAMICS, hkpRackAndPinionConstraintData::Runtime );

			hkpSolverResults m_solverResults[SOLVER_RESULT_MAX];

			// This stores the initial relative angular orientation of the bodies. 0 if uninitialized (triggers 
			// initialization of m_revolutionCounter too). Non-zero when initialized (set to a tiny number 
			// (< HK_REAL_EPSILON) for zero values).
			hkReal m_initialAngleOffset;

			// Previously calculated relative angle.
			hkReal m_prevAngle;

			// This counts revolutions of the cog wheel to properly calculate the Rhs. Auto-initialized to 0.
			hkInt32	m_revolutionCounter;
		};

		struct Atoms
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_DYNAMICS, hkpRackAndPinionConstraintData::Atoms );
			HK_DECLARE_REFLECTION();

			Atoms() {}

			Atoms(hkFinishLoadedObjectFlag f) : m_transforms(f), m_rackAndPinion(f) {}

			// get a pointer to the first atom
			const hkpConstraintAtom* getAtoms() const { return &m_transforms; }

			// get the size of all atoms (we can't use sizeof(*this) because of align16 padding)
			int getSizeOfAllAtoms() const { return hkGetByteOffsetInt(this, &m_rackAndPinion+1); }

			hkpSetLocalTransformsConstraintAtom	m_transforms;
			hkpRackAndPinionConstraintAtom		m_rackAndPinion;
		};

	public:
	
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
		HK_DECLARE_REFLECTION();

		/// Constructor.
		hkpRackAndPinionConstraintData();

		/// Serialization constructor.
		hkpRackAndPinionConstraintData(hkFinishLoadedObjectFlag f) : hkpConstraintData(f), m_atoms(f) {}
		
		/// Sets the rack-and-pinion up with world space information.
		/// \param pinionARotationPivot Is also the reference 'zero-point' for the linear limits along rackShiftAxis
		/// \param rackBShiftAxis Shift axis of bodyB. Note that this cannot be parallel to pinionRotationAxis for
		///                       rack-and-pinion type, and it cannot be perpendicular to pinionRotationAxis for
		///                       screw-type constraints.
		/// \param pinionRadiusOrScrewPitch Is equal to linear displacement caused by one full rotation of elements.
		///                                 The sign can be negative to reverse the shift direction.
		void setInWorldSpace(	const hkTransform& bodyATransform, const hkTransform& bodyBTransform,
								const hkVector4& pinionARotationPivot, const hkVector4& pinionARotationAxis, 
								const hkVector4& rackBhiftAxis, hkReal pinionRadiusOrScrewPitch,
								Type type = TYPE_RACK_AND_PINION);
										
		/// Sets the rack-and-pinion up with body space information.
		/// The parameters are analogical to setInWorldSpace().
		void setInBodySpace(	const hkVector4& pinionARotationPivotInA, const hkVector4& pinionARotationPivotInB,
								const hkVector4& pinionARotationAxisInA, const hkVector4& rackBShiftAxisInB,
								hkReal pinionRadiusOrScrewPitch, Type type = TYPE_RACK_AND_PINION);

		inline Runtime* getRuntime( hkpConstraintRuntime* runtime ){ return reinterpret_cast<Runtime*>(runtime); }

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

#include <Physics/Constraint/Data/RackAndPinion/hkpRackAndPinionConstraintData.inl>


#endif // HKP_RACK_AND_PINION_CONSTRAINT_DATA_H

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
