/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_CONTACT_IMPULSE_LIMIT_BREACHED_LISTENER_H
#define HKP_CONTACT_IMPULSE_LIMIT_BREACHED_LISTENER_H

#include <Physics2012/Dynamics/Constraint/hkpConstraintInstance.h>
#include <Physics2012/Dynamics/Collide/hkpSimpleConstraintContactMgr.h>

class hkpContactPointProperties;
class hkContactPointMaterial;


	/// Data used to identify breached contact points.
	/// This does not store any hkpShapeKey information.
	/// You have to retrieve the hkpShapeKey by using the userDataField in the hkContactPointMaterial structure
class hkpContactImpulseLimitBreachedListenerInfo
{
	public:
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_DYNAMICS, hkpContactImpulseLimitBreachedListenerInfo );

			/// Returns the contact mgr
		hkpSimpleConstraintContactMgr* getContactMgr() const;

			/// returns the array of all contact point properties
		hkpContactPointProperties* getContactPointProperties() const;

		hkContactPoint* getContactPoint() const;

		hkpRigidBody* getBodyA() const;
		
		hkpRigidBody* getBodyB() const;

		const hkpConstraintInstance* getConstraintInstance() const;
		
		void set( hkpConstraintInstance* constraintInstance, hkpContactPointProperties* properties, hkContactPoint* cp, bool isToi );

		hkBool isToi() const;

		hkBool isContact() const;

	protected:
		struct SingleImpulseElem
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_DYNAMICS, hkpContactImpulseLimitBreachedListenerInfo::SingleImpulseElem );

			HK_ALIGN16(hkUint16				m_type);				// 1
			hkUint16 m_isContact;
			hkpConstraintInstance*			m_constraintInstance;	
			hkpContactPointProperties*		m_properties;
			hkContactPoint*			m_contactPoint;
		};

		union ListenerData
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_DYNAMICS, hkpContactImpulseLimitBreachedListenerInfo::SingleImpulseElem );

			hkpImpulseLimitBreachedElem m_solver;
			SingleImpulseElem          m_single;
		};
		ListenerData m_data;
};

	/// This
class hkpContactImpulseLimitBreachedListener
{
	public:
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE,hkpContactImpulseLimitBreachedListener);
		
		virtual ~hkpContactImpulseLimitBreachedListener(){}
		virtual void contactImpulseLimitBreachedCallback( const hkpContactImpulseLimitBreachedListenerInfo* breachedContacts, int numBreachedContacts ) = 0;
};

#include <Physics2012/Dynamics/Constraint/Contact/hkpContactImpulseLimitBreachedListener.inl>


#endif // HKP_CONTACT_IMPULSE_LIMIT_BREACHED_LISTENER_H

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
