/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_MODIFIER_CONSTRAINT_ATOM_H
#define HKP_MODIFIER_CONSTRAINT_ATOM_H

#include <Physics/Constraint/Atom/hkpConstraintAtom.h>
#include <Physics2012/Dynamics/Constraint/Atom/hkpSimpleContactConstraintAtom.h>


/// Base class for modifier atoms
struct hkpModifierConstraintAtom : public hkpConstraintAtom
{
	//+version(1)
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_CONSTRAINT, hkpModifierConstraintAtom );
		HK_DECLARE_REFLECTION();

		hkpModifierConstraintAtom(hkFinishLoadedObjectFlag f) : hkpConstraintAtom(f) {}

		// adds the constraintInfo of one modifier to cinfo and returns the hkpConstraintAtom::CallbackRequest
		int addModifierDataToConstraintInfo( hkpConstraintInfo& cinfo, hkUint8& usedFlagsOut ) const;

		// adds its constraintInfo of all linked modifiers to cinfo and returns the hkpConstraintAtom::CallbackRequest
		static int HK_CALL addAllModifierDataToConstraintInfo( hkpModifierConstraintAtom* firstModifier, hkpConstraintInfo& cinfo, hkUint8& usedFlagsOut );

	protected:

		hkpModifierConstraintAtom(enum AtomType type, int size) : hkpConstraintAtom(type), m_modifierAtomSize( hkUint16(size)) {}
		
	public:

		HK_ALIGN16( hkUint16			m_modifierAtomSize );
		hkUint16						m_childSize;
		HK_CPU_PTR(hkpConstraintAtom*)	m_child;
		hkUint32						m_pad[2]; //+nosave
};


/// Modifier atom which changes the body masses as seen by the solver.
struct hkpMassChangerModifierConstraintAtom : public hkpModifierConstraintAtom
{
	//+version(1)
	public:

		HK_DECLARE_REFLECTION();
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_CONSTRAINT, hkpMassChangerModifierConstraintAtom );
		
		hkpMassChangerModifierConstraintAtom() : hkpModifierConstraintAtom(TYPE_MODIFIER_MASS_CHANGER, sizeof(hkpMassChangerModifierConstraintAtom)) {}
		hkpMassChangerModifierConstraintAtom(hkFinishLoadedObjectFlag f) : hkpModifierConstraintAtom(f) {}

		HK_FORCE_INLINE int numSolverResults() const { return 0; }

		void collisionResponseBeginCallback( const hkContactPoint& cp, struct hkpSimpleConstraintInfoInitInput& inA, struct hkpBodyVelocity& velA, hkpSimpleConstraintInfoInitInput& inB, hkpBodyVelocity& velB);
		void collisionResponseEndCallback(   const hkContactPoint& cp, hkReal impulseApplied, struct hkpSimpleConstraintInfoInitInput& inA, struct hkpBodyVelocity& velA, hkpSimpleConstraintInfoInitInput& inB, hkpBodyVelocity& velB);

		static const hkUint16 ADDITIONAL_SCHEMA_SIZE = 2 * hkpJacobianSchemaInfo::SetMass::Sizeof  + hkpJacobianSchemaInfo::Header::Sizeof;
		
		int getConstraintInfo( hkpConstraintInfo& info ) const
		{
			info.m_sizeOfSchemas += ADDITIONAL_SCHEMA_SIZE;
			return hkpConstraintAtom::CALLBACK_REQUEST_NONE;
		}

	public:

		hkVector4 m_factorA;
		hkVector4 m_factorB;
};


/// Modifier atom which changes the body center of masses as seen by the solver.
struct hkpCenterOfMassChangerModifierConstraintAtom : public hkpModifierConstraintAtom
{
	public:

		HK_DECLARE_REFLECTION();
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_CONSTRAINT, hkpMassChangerModifierConstraintAtom );

		hkpCenterOfMassChangerModifierConstraintAtom() : hkpModifierConstraintAtom(TYPE_MODIFIER_CENTER_OF_MASS_CHANGER, sizeof(hkpCenterOfMassChangerModifierConstraintAtom)) {}
		hkpCenterOfMassChangerModifierConstraintAtom(hkFinishLoadedObjectFlag f) : hkpModifierConstraintAtom(f) {}

		HK_FORCE_INLINE int numSolverResults() const { return 0; }

		void collisionResponseBeginCallback( const hkContactPoint& cp, struct hkpSimpleConstraintInfoInitInput& inA, struct hkpBodyVelocity& velA, hkpSimpleConstraintInfoInitInput& inB, hkpBodyVelocity& velB);
		void collisionResponseEndCallback(   const hkContactPoint& cp, hkReal impulseApplied, struct hkpSimpleConstraintInfoInitInput& inA, struct hkpBodyVelocity& velA, hkpSimpleConstraintInfoInitInput& inB, hkpBodyVelocity& velB);

		static const hkUint16 ADDITIONAL_SCHEMA_SIZE = 2 * hkpJacobianSchemaInfo::SetCenterOfMass::Sizeof  + hkpJacobianSchemaInfo::Header::Sizeof;

		int getConstraintInfo( hkpConstraintInfo& info ) const
		{
			info.m_sizeOfSchemas += ADDITIONAL_SCHEMA_SIZE;
			return hkpConstraintAtom::CALLBACK_REQUEST_NONE;
		}

	public:

			// Two displacements in local space of each of the bodies
		hkVector4 m_displacementA;
		hkVector4 m_displacementB;
};


/// Modifier atom which softens contacts.
struct hkpSoftContactModifierConstraintAtom : public hkpModifierConstraintAtom
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_CONSTRAINT, hkpSoftContactModifierConstraintAtom );
		HK_DECLARE_REFLECTION();

		hkpSoftContactModifierConstraintAtom() : hkpModifierConstraintAtom(TYPE_MODIFIER_SOFT_CONTACT, sizeof(hkpSoftContactModifierConstraintAtom)),  m_tau(0.1f), m_maxAcceleration( 20.0f) { }
		hkpSoftContactModifierConstraintAtom(hkFinishLoadedObjectFlag f) : hkpModifierConstraintAtom(f) {}

		void collisionResponseBeginCallback( const hkContactPoint& cp, struct hkpSimpleConstraintInfoInitInput& inA, struct hkpBodyVelocity& velA, hkpSimpleConstraintInfoInitInput& inB, hkpBodyVelocity& velB);
		void collisionResponseEndCallback(   const hkContactPoint& cp, hkReal impulseApplied, struct hkpSimpleConstraintInfoInitInput& inA, struct hkpBodyVelocity& velA, hkpSimpleConstraintInfoInitInput& inB, hkpBodyVelocity& velB);
		HK_FORCE_INLINE int numSolverResults() const { return 0; }

		static const hkUint16 ADDITIONAL_SCHEMA_SIZE = 0;

		int getConstraintInfo( hkpConstraintInfo& info ) const	{ return hkpConstraintAtom::CALLBACK_REQUEST_NONE; }

	public:

		hkReal m_tau;

			/// The maximum acceleration the solver will apply
		hkReal m_maxAcceleration;

#if defined(HK_REAL_IS_DOUBLE)
		hkUint8 m_padding[16]; //+nosave
#endif
};


/// Moving atom which simulates a viscous surface.
struct hkpViscousSurfaceModifierConstraintAtom : public hkpModifierConstraintAtom
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_CONSTRAINT, hkpViscousSurfaceModifierConstraintAtom );
		HK_DECLARE_REFLECTION();

		hkpViscousSurfaceModifierConstraintAtom() : hkpModifierConstraintAtom(TYPE_MODIFIER_VISCOUS_SURFACE, sizeof(hkpViscousSurfaceModifierConstraintAtom)) { }

		hkpViscousSurfaceModifierConstraintAtom(hkFinishLoadedObjectFlag f) : hkpModifierConstraintAtom(f) {}

		static const hkUint16 ADDITIONAL_SCHEMA_SIZE = 0;

		int getConstraintInfo( hkpConstraintInfo& info ) const	{ return hkpConstraintAtom::CALLBACK_REQUEST_NONE; }

		HK_FORCE_INLINE int numSolverResults() const { return 0; }
};


/// Moving atom which simulates a moving surface.
struct hkpMovingSurfaceModifierConstraintAtom : public hkpModifierConstraintAtom
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_CONSTRAINT, hkpMovingSurfaceModifierConstraintAtom );
		HK_DECLARE_REFLECTION();

		hkpMovingSurfaceModifierConstraintAtom() : hkpModifierConstraintAtom(TYPE_MODIFIER_MOVING_SURFACE, sizeof(hkpMovingSurfaceModifierConstraintAtom)) { }
		hkpMovingSurfaceModifierConstraintAtom(hkFinishLoadedObjectFlag f) : hkpModifierConstraintAtom(f) {}

		HK_FORCE_INLINE int numSolverResults() const { return 0; }

		static const hkUint16 ADDITIONAL_SCHEMA_SIZE = 2 * hkpJacobianSchemaInfo::AddVelocity::Sizeof + hkpJacobianSchemaInfo::Header::Sizeof;

		int getConstraintInfo( hkpConstraintInfo& info ) const
		{
			info.m_sizeOfSchemas += ADDITIONAL_SCHEMA_SIZE;
			return hkpConstraintAtom::CALLBACK_REQUEST_NONE;
		}

		void collisionResponseBeginCallback( const hkContactPoint& cp, struct hkpSimpleConstraintInfoInitInput& inA, struct hkpBodyVelocity& velA, hkpSimpleConstraintInfoInitInput& inB, hkpBodyVelocity& velB);
		void collisionResponseEndCallback(   const hkContactPoint& cp, hkReal impulseApplied, struct hkpSimpleConstraintInfoInitInput& inA, struct hkpBodyVelocity& velA, hkpSimpleConstraintInfoInitInput& inB, hkpBodyVelocity& velB);

		hkVector4& getVelocity() { return m_velocity; }
		const hkVector4& getVelocity() const { return m_velocity; }

	public:

		hkVector4 m_velocity;
};


/// Modifier atom which causes the constraint to be ignored by the solver.
struct hkpIgnoreModifierConstraintAtom : public hkpModifierConstraintAtom
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_CONSTRAINT, hkpIgnoreModifierConstraintAtom );
		HK_DECLARE_REFLECTION();
		
		hkpIgnoreModifierConstraintAtom() : hkpModifierConstraintAtom(TYPE_MODIFIER_IGNORE_CONSTRAINT, sizeof(hkpIgnoreModifierConstraintAtom)) { }
		hkpIgnoreModifierConstraintAtom(hkFinishLoadedObjectFlag f) : hkpModifierConstraintAtom(f) {}

		HK_FORCE_INLINE int numSolverResults() const { return 0; }

		int getConstraintInfo( hkpConstraintInfo& info ) const;
};


#endif // HKP_MODIFIER_CONSTRAINT_ATOM_H

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
