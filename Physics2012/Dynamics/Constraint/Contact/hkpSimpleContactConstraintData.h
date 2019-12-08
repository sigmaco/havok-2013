/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_SIMPLE_CONTACT_CONSTRAINT_DATA_H
#define HKP_SIMPLE_CONTACT_CONSTRAINT_DATA_H

#include <Physics/Constraint/Data/hkpConstraintData.h>

#include <Common/Base/Types/Physics/ContactPoint/hkContactPoint.h>
#include <Physics2012/Internal/Solver/Contact/hkpSimpleContactConstraintInfo.h>
#include <Physics2012/Dynamics/Constraint/Atom/hkpSimpleContactConstraintAtom.h>
#include <Physics2012/Dynamics/Constraint/Contact/hkpContactPointProperties.h>
#include <Physics2012/Dynamics/Constraint/Atom/hkpSimpleContactConstraintAtomUtil.h>
#include <Physics2012/Dynamics/Constraint/Contact/hkpDynamicsCpIdMgr.h>
#include <Physics2012/Dynamics/Constraint/hkpConstraintInstance.h>

class hkContactPoint;
class hkpSolverResults;
class hkpRigidBody;
class hkpSimpleConstraintContactMgr;


/// A group of simple contacts.
class hkpSimpleContactConstraintData : public hkpConstraintData
{
	public:
	
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_CONTACT);

		inline ~hkpSimpleContactConstraintData();

			/// Get number of contact points.
		inline int getNumContactPoints() const;

			/// Get contactPoint at position i.
		inline hkContactPointId getContactPointIdAt( int index ) const;

			/// Get the contact point for an id.
		inline const hkContactPoint& getContactPoint( int /*hkContactPointId*/ id ) const;

			/// Get the contact point for an id.
		inline hkContactPoint& getContactPoint( int /*hkContactPointId*/ id );

			/// Get the result for the same id.
		inline hkpContactPointProperties* getContactPointProperties( int /*hkContactPointId*/ id );

		hkContactPointId allocateContactPoint( hkpConstraintOwner& constraintOwner, hkContactPoint** cpOut, hkpContactPointProperties** cpPropsOut);

			// return the new number of contact points
		int freeContactPoint( hkpConstraintOwner& constraintOwner, hkContactPointId id );

		virtual hkBool isValid() const;

		// hkpConstraintData interface implementations
		virtual void getConstraintInfo( hkpConstraintData::ConstraintInfo& infoOut ) const;

			// hkpConstraintData interface implementation
		virtual void getRuntimeInfo( hkBool wantRuntime, hkpConstraintData::RuntimeInfo& infoOut ) const;

		virtual hkpSolverResults* getSolverResults( hkpConstraintRuntime* runtime );

		virtual int getType() const;
	
			/// This function is just called before a TOI or a normal collision response.
			/// Those collision response functions are called for every new contact point
			/// where the objects have a colliding velocity > hkpWorldCinfo.m_contactRestingVelocity
		virtual void collisionResponseBeginCallback( const hkContactPoint& cp, struct hkpSimpleConstraintInfoInitInput& inA, struct hkpBodyVelocity& velA, hkpSimpleConstraintInfoInitInput& inB, hkpBodyVelocity& velB );

		virtual void collisionResponseEndCallback( const hkContactPoint& cp, hkReal impulseApplied, struct hkpSimpleConstraintInfoInitInput& inA, struct hkpBodyVelocity& velA, hkpSimpleConstraintInfoInitInput& inB, hkpBodyVelocity& velB);

			/// Returns a pointer to the containing contact manager.
		hkpSimpleConstraintContactMgr* getSimpleConstraintContactMgr() const;

	public:
		inline hkpSimpleContactConstraintData( hkFinishLoadedObjectFlag f ) { }

	private:
			/// The constructor is private to ensure that objects of this class only ever exist as contained members
			/// of hkpSimpleConstraintContactMgr.
		hkpSimpleContactConstraintData(hkpConstraintInstance* constraint, hkpRigidBody* bodyA, hkpRigidBody* bodyB);
			/// Required for the constructor of hkpSimpleConstraintContactMgr.
		friend class hkpSimpleConstraintContactMgr;

	public:

		hkpDynamicsCpIdMgr		m_idMgrA;
		void*					m_clientData;
		hkpConstraintInstance*	m_constraint;

		hkpSimpleContactConstraintAtom*	m_atom;
		int								m_atomSize;	
};

#include <Physics2012/Dynamics/Constraint/Contact/hkpSimpleContactConstraintData.inl> 


#endif // HKP_SIMPLE_CONTACT_CONSTRAINT_DATA_H

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
