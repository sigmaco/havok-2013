/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_DYNAMICS2_BREAKABLE_BODY_H
#define HK_DYNAMICS2_BREAKABLE_BODY_H

#include <Physics2012/Collide/Shape/hkpShape.h>
#include <Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <Physics2012/Dynamics/Destruction/BreakableShape/hkpBreakableShape.h>

extern const class hkClass hkpBreakableBodyClass;

	/// This is the base class of Havok Destruction's hkdBreakableBody.
class hkpBreakableBody : public hkReferencedObject
{
	// +version(1)
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE_CLASS);
		HK_DECLARE_REFLECTION();

	public:

			/// Class that controls the response of the breakable body to impacts
		class Controller : public hkReferencedObject
		{
			public:

				HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE_CLASS);
				HK_DECLARE_REFLECTION();

			public:

					/// Constructor
				Controller()
				:	hkReferencedObject()
				,	m_breakingImpulse(-1.0f)
				{}

					/// Serialization constructor
				Controller(class hkFinishLoadedObjectFlag flag)
				:	hkReferencedObject(flag)
				{}

					/// Destructor
				virtual ~Controller()
				{}

			public:

					/// Returns the breaking impulse
				HK_FORCE_INLINE hkReal getBreakingImpulse() const { return m_breakingImpulse; }

					/// Sets the breaking impulse
				HK_FORCE_INLINE void setBreakingImpulse(hkReal newBreakingImpulse) { m_breakingImpulse = newBreakingImpulse; }

					/// Called by the runtime to compute the breakable threshold (i.e. strength) of the given breakable body at the given shape key. Returns true
					/// if the shape key is breakable.
				static HK_FORCE_INLINE hkBool HK_CALL getBodyStrengthAt(const hkpBreakableBody* breakableBodySpu, const hkpRigidBody* rigidBodySpu, hkpShapeKey impactShapeKey, hkUFloat8& shapeKeyStrengthOut);

			protected:

				/// Breaking impulse threshold. If set to a negative value, the controller will simply request the breaking impulse from the breakable body
				hkReal m_breakingImpulse;	//+default(-1.0)
		};

		friend class Controller;

			// Default constructor.
		hkpBreakableBody(const hkpBreakableShape* breakableShape, hkUint8 bodyType)
		:	hkReferencedObject()
		,	m_controller(HK_NULL)
		,	m_breakableShape(breakableShape)
		,	m_bodyTypeAndFlags(bodyType)
		{ m_constraintStrength.setZero(); }

		hkpBreakableBody(class hkFinishLoadedObjectFlag flag)
		:	hkReferencedObject(flag)
		,	m_controller(flag)
		,	m_breakableShape(flag)
		{}

			// Destructor.
		virtual ~hkpBreakableBody()
		{}

			/// Clone this Breakable Body. See the documentation for hkdBreakableBody for details.
		virtual hkpBreakableBody* cloneBreakableBody(hkpRigidBody* clonedRigidBody = HK_NULL) const = 0;

			/// Returns the constraint strength
		HK_FORCE_INLINE hkReal getConstraintStrength() const { return m_constraintStrength.getReal(); }

			/// Sets the constraint strength
		HK_FORCE_INLINE void setConstraintStrength(hkReal newStrength) { m_constraintStrength.setReal<true>(newStrength);}

	protected:

			/// The controller used to break this body. Can be HK_NULL. The hkdWorld will then use a default controller.
		hkRefPtr<Controller> m_controller;

			/// The breakable shape this body is an instance of.
		hkRefPtr<const hkpBreakableShape> m_breakableShape;

	public:

			/// The breakable body type and runtime flags.
		hkUint8 m_bodyTypeAndFlags;	//+default(0)

	protected:

			/// Used to calculate strengths (impulse limits) for constraints attached to this breakable body
		hkHalf m_constraintStrength; //+default(0.0)
};

#include <Physics2012/Dynamics/Destruction/BreakableBody/hkpBreakableBody.inl>

#endif // HK_DYNAMICS2_BREAKABLE_BODY_H

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
