/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

HK_FORCE_INLINE hkpSimpleConstraintContactMgr* hkpContactImpulseLimitBreachedListenerInfo::getContactMgr() const
{
	const hkUlong offset = hkUlong(-HK_OFFSET_OF( hkpSimpleConstraintContactMgr, m_constraint ));
	return (hkpSimpleConstraintContactMgr*)hkAddByteOffset( m_data.m_single.m_constraintInstance, (hkLong)offset );
}

HK_FORCE_INLINE hkpContactPointProperties *hkpContactImpulseLimitBreachedListenerInfo::getContactPointProperties() const
{
	if ( m_data.m_single.m_type != 0)
	{
		return m_data.m_single.m_properties;
	}
	return static_cast<hkpContactPointProperties*>( m_data.m_solver.m_solverResult );
}

HK_FORCE_INLINE hkContactPoint *hkpContactImpulseLimitBreachedListenerInfo::getContactPoint() const
{
	if ( m_data.m_single.m_type != 0)
	{
		return m_data.m_single.m_contactPoint;
	}
	hkpSimpleConstraintContactMgr* mgr = getContactMgr();
	hkpSimpleContactConstraintAtom* atom = mgr->m_contactConstraintData.m_atom;
	const hkpContactPointPropertiesStream* cpp = reinterpret_cast<hkpContactPointPropertiesStream*>( m_data.m_solver.m_solverResult );
	hkUlong contactIndex = hkGetByteOffset(atom->getContactPointPropertiesStream(), cpp) / atom->getContactPointPropertiesStriding() ;
	hkContactPoint* cp = &atom->getContactPoints()[contactIndex];
	return cp;
}

HK_FORCE_INLINE void hkpContactImpulseLimitBreachedListenerInfo::set(hkpConstraintInstance* constraintInstance, hkpContactPointProperties* properties, hkContactPoint* cp, bool toi)
{
	m_data.m_single.m_type = 1 + toi;
	m_data.m_single.m_isContact = true;
	m_data.m_single.m_constraintInstance = constraintInstance;
	m_data.m_single.m_contactPoint = cp;
	m_data.m_single.m_properties = properties;
}

HK_FORCE_INLINE hkpRigidBody* hkpContactImpulseLimitBreachedListenerInfo::getBodyA() const 
{ 
	return m_data.m_single.m_constraintInstance->getRigidBodyA();
}

HK_FORCE_INLINE hkpRigidBody* hkpContactImpulseLimitBreachedListenerInfo::getBodyB() const 
{ 
	return m_data.m_single.m_constraintInstance->getRigidBodyB(); 
}

HK_FORCE_INLINE const hkpConstraintInstance* hkpContactImpulseLimitBreachedListenerInfo::getConstraintInstance() const 
{ 
	return m_data.m_solver.m_constraintInstance; 
}

HK_FORCE_INLINE hkBool hkpContactImpulseLimitBreachedListenerInfo::isToi() const
{ 
	return m_data.m_single.m_type == 2;
}

HK_FORCE_INLINE hkBool hkpContactImpulseLimitBreachedListenerInfo::isContact() const
{ 
	return m_data.m_solver.m_isContact == 1;
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
