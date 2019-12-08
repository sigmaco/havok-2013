/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKD_BREAK_OFF_UTIL_H
#define HKD_BREAK_OFF_UTIL_H

#include <Physics2012/Utilities/Destruction/BreakOffParts/hkpBreakOffPartsUtil.h>
#include <Physics2012/Dynamics/Destruction/BreakableBody/hkpBreakableBody.h>

	/// This utility class is an interface between the physics constraint solver and the Destruction runtime.
	/// For each contact / constraint involving an entity flagged as breakable, the solver queries the entity for the
	/// maximum impulse it can apply to maintain the constraint. The request is forwarded to the Destruction runtime,
	/// which is responsible for returning a proper impulse value back to the solver. 
class hkpDestructionBreakOffUtil :	public hkpWorldExtension, 
									public hkpContactImpulseLimitBreachedListener,
									protected hkpEntityListener, 
									protected  hkpConstraintListener
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_DESTRUCTION_2012);

	public:

		enum BreakOffGameControlResult
		{
			PROCESSING_ERROR,
			BREAK_OFF,
			DO_NOT_BREAK_OFF,
			USE_LIMIT
		};

			/// The functor for user interception of breaking events
		class GameControlFunctor : public hkReferencedObject
		{
			public:

				HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_DESTRUCTION_2012);

			public:

				GameControlFunctor()
				:	hkReferencedObject()
				{}

				virtual ~GameControlFunctor()
				{}

					/// The decision function that says whether the \a limitedBody should be broken by impact of \a otherBody.
					/// The \a key is the shape key in contact in the \a otherBody and the currently set \a maxImpulse for breaking the \a limitedBody.
					/// This implementation simply returns USE_LIMIT.
				virtual hkpDestructionBreakOffUtil::BreakOffGameControlResult test(const hkpRigidBody* limitedBody, const hkpRigidBody* otherBody, const hkpShapeKey key, const hkUFloat8& maxImpulse);
		};

			/// Contact listener for breakable bodies
		class ContactListener : public hkReferencedObject, public hkpCollisionListener
		{
			public:

				HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_DESTRUCTION_2012);

			public:

					/// Constructor
				ContactListener(hkpDestructionBreakOffUtil* breakOffUtil);

					/// Destructor
				~ContactListener();

					/// Calculate a maxImpulse value given that current entity is colliding with another at key.
					/// Returns true if the entity is breakable, false otherwise.
				static HK_FORCE_INLINE hkBool HK_CALL getMaxImpulseForKey(hkpShapeKey key, hkpEntity* entity, hkUFloat8& shapeKeyImpulseOut);

					/// Used by the CPU callbacks (the contactPointCallback and the contactPointAddedCallback), but not used by the SPU version.
				static HK_FORCE_INLINE void HK_CALL limitContactImpulse(const hkUFloat8& maxImpulse, bool isEntityA, hkpContactPointProperties* properties);


					/// Performs additional set-up to the given rigid body that marks it as breakable
				virtual void markBreakableBody(hkpRigidBody* body);

					/// Returns true if the the body can be broken-off
				virtual hkBool canBreak(const hkpRigidBody* body) const;

					/// Calculate a maxImpulse value given that current entity is colliding with other at key.
					/// \return 0 if no maxImpulse should be applied in this case.
				static HK_FORCE_INLINE hkUFloat8 HK_CALL getMaxImpulseForContactPoint(hkpShapeKey key, hkpEntity* entity, hkpEntity* other);

			protected:

					/// Given a hkpCdBody, it returns the owning entity and shape key
				static HK_FORCE_INLINE void HK_CALL getRootEntityAndKey(const hkpCdBody* bodyIn, hkpEntity*& entityOut, hkpShapeKey& keyOut);


			protected:

					/// The break-off parts util
				hkpDestructionBreakOffUtil* m_breakOffUtil;
		};

			/// Contact listener using the deprecated SPU callbacks
		class ContactListenerSpu : public ContactListener
		{
			public:

				HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_DESTRUCTION_2012);

					/// Constructor
				ContactListenerSpu(hkpDestructionBreakOffUtil* breakOffUtil)
				:	ContactListener(breakOffUtil)
				{}

			public:


					/// Returns true if the the body can be broken-off
				virtual hkBool canBreak(const hkpRigidBody* body) const;

					/// Performs additional set-up to the given rigid body that marks it as breakable
				virtual void markBreakableBody(hkpRigidBody* body);

					/// Called on PPU / CPU after a contact point is created. This contact point is still a potential one.
				void contactPointAddedCallback(hkpContactPointAddedEvent& event);

		};


			/// Contact listener using the PPU-only callbacks
		class ContactListenerPpu : public ContactListener
		{
			public:

				HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_DESTRUCTION_2012);

					/// Constructor
				ContactListenerPpu(hkpDestructionBreakOffUtil* breakOffUtil)
				:	ContactListener(breakOffUtil)
				{}

					/// Called only on PPU / CPU, after a contact point is created.
				virtual void contactPointCallback(const hkpContactPointEvent& event);
		};


		//
		//	Convenient typedefs

	public:

		typedef hkpBreakOffPartsListener::ContactImpulseLimitBreachedEvent				Event;
		typedef hkpBreakOffPartsListener::ContactImpulseLimitBreachedEvent::PointInfo	PointInfo;
		typedef ContactListenerSpu														DefaultContactListener;

	public:


			/// Constructor
		hkpDestructionBreakOffUtil(hkpBreakOffPartsListener* breakOffPartsListener);

			/// Destructor
		virtual ~hkpDestructionBreakOffUtil();

	public:

			/// Enables / disables all contact callbacks on PPU. By default, callbacks are processed on Spu. Note that this function
			/// will remove the previous collision listener assuming there are no rigid bodies still using it. 
		void enableSpuCallbacks(bool doEnable);

			/// Flag a rigid body to be breakable
		void markBreakableBody(hkpRigidBody* body);

			/// Flags a rigid body as unbreakable
		void markUnbreakableBody(hkpRigidBody* body);

			/// Returns true if the body is breakable
		HK_FORCE_INLINE hkBool canBreak(const hkpRigidBody* body) const;

			/// Called when this extension is attached to the physics world.
		virtual void performAttachments(hkpWorld* world);

			/// Called when this extension is detached from the physics world.
		virtual void performDetachments(hkpWorld* world);

	protected:

			/// Called when a constraint is added to the world.
		void constraintAddedCallback(hkpConstraintInstance* constraint);

			/// Called by the constraint solver when it needs to apply more than the maximum allowed impulse in order to maintain the given contacts.
		void contactImpulseLimitBreachedCallback(const hkpContactImpulseLimitBreachedListenerInfo* breachedContacts, int numBreachedContacts);

			/// Called by the constraint solver when it needs to apply more than the maximum allowed impulse in order to maintain the given contacts.
		void contactImpulseLimitBreachedCallbackToi(const hkpContactImpulseLimitBreachedListenerInfo* breachedContact);

			/// Returns the constraint strength set on the given entity
		static HK_FORCE_INLINE hkReal HK_CALL getConstraintStrength(const hkpEntity* entity);

			/// Flags a rigid body as unbreakable
		HK_FORCE_INLINE void _markUnbreakableBody(hkpRigidBody* body);

	protected:
		
			/// Entity contact points listener
		ContactListener* m_entityContactsListener;

			/// A critical section to serialize access to this utility
		hkCriticalSection* m_criticalSection;

			/// Break-off parts listener
		hkpBreakOffPartsListener* m_breakOffPartsListener;

	public:

			/// User-defined break-off control function
		hkRefPtr<GameControlFunctor> m_breakOffControlFunctor;

};

#include <Physics2012/Dynamics/Destruction/Utilities/hkpDestructionBreakOffUtil.inl>

#endif	//	HKD_BREAK_OFF_UTIL_H

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
