/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

const hkTransform& hkpCdBody::getTransform() const
{
	HK_ASSERT2(0x733aae9d, m_motion, "You cannot call getTransform() on a hkpCdBody with null m_motion (eg, a hkpAabbPhantom)");
	#ifdef HK_DEBUG
		return *reinterpret_cast<const hkTransform*>( hkClearBits(m_motion, 1) );
	#else
		return *static_cast<const hkTransform*>( m_motion);
	#endif
}

const hkMotionState* hkpCdBody::getMotionState() const
{
	#ifdef HK_DEBUG
		HK_ASSERT2(0x733aae9e, (hkUlong(m_motion)&1)==0, "This cdbody has only a transform, not a motionstate");
		return reinterpret_cast<const hkMotionState*>( hkClearBits(m_motion, 1) );
	#else
		return static_cast<const hkMotionState*>( m_motion);
	#endif
}

void hkpCdBody::setMotionState( const hkMotionState* state )
{
	m_motion = state;
}

void hkpCdBody::setTransform( const hkTransform* t )
{
	#ifdef HK_DEBUG
		m_motion = hkAddByteOffsetConst(t, 1);
	#else
		m_motion = t;
	#endif
}


const hkpShape* hkpCdBody::getShape() const
{
	return m_shape;
}

const hkpCollidable* hkpCdBody::getRootCollidable() const
{	
	const hkpCdBody* body = this;
	while( body->m_parent )
	{
		body = body->m_parent;
	}
	return reinterpret_cast<const hkpCollidable*>(body);
}

const hkpCdBody* hkpCdBody::getParent() const
{
	return m_parent;
}

hkpCdBody::hkpCdBody( const hkpShape* shape, const hkMotionState* motionState )
{
	m_shape = shape;
	setMotionState(motionState);
	m_parent = HK_NULL;
	m_shapeKey = HK_INVALID_SHAPE_KEY;
}

hkpCdBody::hkpCdBody( const hkpShape* shape, const hkTransform* t )
{
	m_shape = shape;
	setTransform(t);
	m_parent = HK_NULL;
	m_shapeKey = HK_INVALID_SHAPE_KEY;
}


hkpCdBody::hkpCdBody( const hkpCdBody* parent )
{
	m_parent = parent;
	m_motion = parent->m_motion;
}

hkpCdBody::hkpCdBody( const hkpCdBody* parent, const hkMotionState* ms )
{
	m_parent = parent;
	setMotionState(ms);
}

hkpCdBody::hkpCdBody( const hkpCdBody* parent, const hkTransform* t )
{
	m_parent = parent;
	setTransform(t);
}


hkpShapeKey hkpCdBody::getShapeKey() const
{
	return m_shapeKey;
}

hkpShapeKey hkpCdBody::getTopLevelShapeKey() const
{
	const hkpCdBody* root = this;
	const hkpCdBody* topChild = root;
	while ( root->m_parent ){ topChild = root; root = root->m_parent; }
	return topChild->m_shapeKey;
}

void hkpCdBody::setShape( const hkpShape* shape, hkpShapeKey key )
{
	m_shape = shape;
	m_shapeKey = key;
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
