/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#include <Physics2012/Dynamics/Destruction/Utilities/hkpDestructionSpuUtil.h>


//
//	Flags a rigid body as unbreakable

HK_FORCE_INLINE void hkpDestructionBreakOffUtil::_markUnbreakableBody(hkpRigidBody* body)
{
	// Un-mark it as breakable
	body->m_limitContactImpulseUtilAndFlag = 0;

	// Remove the contact listener from the body
	body->removeContactListener(m_entityContactsListener);
}

//
//	Returns true if the body is breakable

HK_FORCE_INLINE hkBool hkpDestructionBreakOffUtil::canBreak(const hkpRigidBody* body) const
{
	return body && m_entityContactsListener->canBreak(body);
}

//
//	Given a hkpCdBody, it returns the owning entity and shape key

inline void HK_CALL hkpDestructionBreakOffUtil::ContactListener::getRootEntityAndKey(const hkpCdBody* bodyIn, hkpEntity*& entityOut, hkpShapeKey& keyOut)
{
	const hkpCdBody* rootCollidable = bodyIn;
	const hkpCdBody* topChild = rootCollidable;
	while ( rootCollidable->m_parent )
	{
		topChild = rootCollidable;
		rootCollidable = rootCollidable->m_parent;
	}
	keyOut		= topChild->getShapeKey();
	entityOut	= hkpGetRigidBody(reinterpret_cast<const hkpCollidable*>(rootCollidable));
}


//
//	Calculate a maxImpulse value given that current entity is colliding with another at key.
//	Returns true if the entity is breakable, false otherwise.

inline hkBool HK_CALL hkpDestructionBreakOffUtil::ContactListener::getMaxImpulseForKey(hkpShapeKey key, hkpEntity* entity, hkUFloat8& shapeKeyImpulseOut)
{
	// Get rigid body and its breakable body if any
	const hkpRigidBody* rigidBodySpu	= reinterpret_cast<const hkpRigidBody*>(entity);
	hkpBreakableBody* breakableBodyPpu	= const_cast<hkpBreakableBody*>(rigidBodySpu->m_breakableBody);

	// Try to call the breakable body controller to get the strength
	if ( breakableBodyPpu )
	{
		// Need to download the breakable body on the SPU
		HK_DECLARE_SPU_LOCAL_DESTRUCTION_PTR(hkpBreakableBody, breakableBodySpu, sizeof(hkpBreakableBody));
		HK_DOWNLOAD_DESTRUCTION_PTR_TO_SPU(breakableBodySpu, breakableBodyPpu, sizeof(hkpBreakableBody));

		// Call the body controller to get the strength
		if ( hkpBreakableBody::Controller::getBodyStrengthAt(breakableBodySpu, rigidBodySpu, key, shapeKeyImpulseOut) )
		{
			return true;
		}
	}

	return false;
}

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
