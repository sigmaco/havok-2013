/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_ANGULAR_FRICTION_CONSTRAINT_DATA_H
#define HKP_ANGULAR_FRICTION_CONSTRAINT_DATA_H

#include <Physics/Constraint/Data/hkpConstraintData.h>


//
class hkpAngularFrictionConstraintData : public hkpConstraintData
{
	public:
		
		enum
		{
			SOLVER_RESULT_FRICTION_0	= 0,	// the angular friction value
			SOLVER_RESULT_FRICTION_1	= 1,	// the angular friction value
			SOLVER_RESULT_FRICTION_2	= 2,	// the angular friction value
			SOLVER_RESULT_MAX			= 3
		};

		struct Runtime
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_DYNAMICS, hkpAngularFrictionConstraintData::Runtime );

			hkpSolverResults m_solverResults[SOLVER_RESULT_MAX];

			/// Tells whether the previous target angles have been initialized. This is zeroed when created.
			hkUint8 m_initialized[3];

			/// Target angles for the individual motors
			HK_ALIGN(hkReal m_previousTargetAngles[3],HK_REAL_SIZE);

			/// Soft recovery parameter for the cone limit.
			hkReal m_coneAngleOffset;
		};

		struct Atoms
		{
			// +version(1)
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_COLLIDE, hkpAngularFrictionConstraintData::Atoms );
			
			enum Axis
			{
				AXIS_TWIST = 0,
				AXIS_PLANES = 1,
				AXIS_CROSS_PRODUCT = 2
			};

			Atoms() {}

			Atoms(hkFinishLoadedObjectFlag f) : m_transforms(f), m_angFriction(f) {}

			/// Get a pointer to the first atom.
			const hkpConstraintAtom* getAtoms() const { return &m_transforms; }

			/// Get the size of all atoms. Note: we can't use sizeof(*this) because of align16 padding.
			int getSizeOfAllAtoms() const { return hkGetByteOffsetInt(this, &m_angFriction + 1); }

			hkpSetLocalTransformsConstraintAtom	m_transforms;
			hkpAngFrictionConstraintAtom		m_angFriction;
		};
		
	public:
	
		HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CONSTRAINT );

		/// Constructor.
		hkpAngularFrictionConstraintData();

		/// Destructor. Will dereference any motors held.
		~hkpAngularFrictionConstraintData();
		
		/// Set up the constraint based on information in world space.
		/// \param bodyA			The attached body transform
		/// \param bodyB			The reference body transform
		/// \param pivot			The pivot point, specified in world space.
		/// \param twistAxisW		The twist axis, specified in world space.
		/// \param planeAxisW		The plane axis, specified in world space.
		void setInWorldSpace(const hkTransform& bodyATransform, const hkTransform& bodyBTransform,
			const hkVector4& pivot, const hkVector4& twistAxisW,
			const hkVector4& planeAxisW);

		/// Set up the constraint based on information in body space.
		/// \param pivotA			The pivot point, specified in bodyA space.
		/// \param pivotB			The pivot point, specified in bodyB space.
		/// \param twistAxisA		The twist axis, specified in bodyA space.
		/// \param twistAxisB		The twist axis, specified in bodyB space.
		/// \param planeAxisA		The plane axis, specified in bodyA space.
		/// \param planeAxisB		The plane axis, specified in bodyB space.
		void setInBodySpace( const hkVector4& pivotA, const hkVector4& pivotB,
			const hkVector4& planeAxisA, const hkVector4& planeAxisB,
			const hkVector4& twistAxisA, const hkVector4& twistAxisB);

		/// Gets the constraint frame.
		/// \param constraintFrameA Column 0 = twist axis, Column 1 = plane, Column 2 = twist cross plane.
		void getConstraintFrameA( hkMatrix3& constraintFrameA ) const;

		/// Gets the constraint frame.
		/// \param constraintFrameB Column 0 = twist axis, Column 1 = plane, Column 2 = twist cross plane.
		void getConstraintFrameB( hkMatrix3& constraintFrameB ) const;
		
		/// Sets the friction value. Set this before adding to the system.
		/// Note that this value is an absolute torque value and is therefore dependent on the masses of constrained
		/// bodies and not limited between 0.0f and 1.0f. If trying to stiffen up ragdoll constraints, try setting this
		/// value sufficiently high so that constraints are completely stiff and then reduce until the desired behavior
		/// has been achieved.
		void setMaxFrictionTorque(hkReal tmag);

		/// Gets the friction value.
		inline hkReal getMaxFrictionTorque() const;

		static inline Runtime* HK_CALL getRuntime( hkpConstraintRuntime* runtime ) { return reinterpret_cast<Runtime*>(runtime); }

		//
		// hkpConstraintData implementation
		//

		virtual int getType() const;

		hkBool isValid() const;

		virtual void getConstraintInfo( hkpConstraintData::ConstraintInfo& infoOut ) const;

		virtual void setBodyToNotify(int bodyIdx);

		virtual hkUint8 getNotifiedBodyIndex() const;

		virtual void setSolvingMethod(hkpConstraintAtom::SolvingMethod method);

		virtual void getRuntimeInfo( hkBool wantRuntime, hkpConstraintData::RuntimeInfo& infoOut ) const;

	public:

		HK_ALIGN_REAL( Atoms m_atoms );
};


#endif	// HKP_ANGULAR_FRICTION_CONSTRAINT_DATA_H

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
