/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */



HK_FORCE_INLINE const hkArray<hkpStaticCompoundShape::Instance>& hkpStaticCompoundShape::getInstances() const
{
	return m_instances;
}

HK_FORCE_INLINE hkInt8 hkpStaticCompoundShape::getNumBitsForChildShapeKey() const
{
	return m_numBitsForChildShapeKey;
}

HK_FORCE_INLINE hkpShapeKey hkpStaticCompoundShape::composeShapeKey( int instanceId, hkpShapeKey childKey ) const
{
	HK_ASSERT2(0x24fbe155, m_numBitsForChildShapeKey > 0, "Shape not baked yet!" );
	HK_ASSERT2(0x2f7b7cd9, (childKey & m_childShapeKeyMask) == childKey, "Child shape key is too big!" );
	return ( instanceId << m_numBitsForChildShapeKey ) | childKey;
}

HK_FORCE_INLINE void hkpStaticCompoundShape::decomposeShapeKey( hkpShapeKey keyIn, int& instanceIdOut, hkpShapeKey& childKeyOut ) const
{
	HK_ASSERT2(0x24fbe155, m_numBitsForChildShapeKey > 0, "Shape not baked yet!" );
	instanceIdOut = keyIn >> m_numBitsForChildShapeKey;
	HK_ASSERT(0x5cfbaf05, instanceIdOut >= 0 && instanceIdOut < m_instances.getSize() );
	childKeyOut = keyIn & m_childShapeKeyMask;
}


HK_FORCE_INLINE const hkQsTransform& hkpStaticCompoundShape::Instance::getTransform() const
{
	return m_transform;
}

HK_FORCE_INLINE const hkpShape* hkpStaticCompoundShape::Instance::getShape() const
{
	return m_shape;
}


HK_FORCE_INLINE void hkpStaticCompoundShape::Instance::setFlags( hkUint32 flags )
{
	m_transform.m_translation.setInt24W( ( m_transform.m_translation.getInt24W() & ~FLAGS_ALL ) | flags );
}

HK_FORCE_INLINE hkUint32 hkpStaticCompoundShape::Instance::getFlags() const
{
	return m_transform.m_translation.getInt24W() & FLAGS_ALL;
}


HK_FORCE_INLINE void hkpStaticCompoundShape::Instance::setShapeSizeForSpu( hkUint32 size )
{
	const hkUint32 shapeSizeMask = ((1 << (hkUint32)NUM_BITS_FOR_SHAPE_SIZE) - 1) << NUM_BITS_FOR_FLAGS;
	hkUint32 bitfield = ( m_transform.m_translation.getInt24W() & ~shapeSizeMask );

	const hkUint32 storedShapeSize = size / 16;
	HK_ASSERT(0x8b3e4bd, storedShapeSize <= ((1 << (hkUint32)NUM_BITS_FOR_SHAPE_SIZE) - 1) );

	bitfield |= storedShapeSize << NUM_BITS_FOR_FLAGS;
	m_transform.m_translation.setInt24W( bitfield );
}

HK_FORCE_INLINE hkUint32 hkpStaticCompoundShape::Instance::getShapeSizeForSpu() const
{
	return ( (m_transform.m_translation.getInt24W() >> NUM_BITS_FOR_FLAGS) & ((1 << (hkUint32)NUM_BITS_FOR_SHAPE_SIZE) - 1) ) * 16;
}


HK_FORCE_INLINE void hkpStaticCompoundShape::setInstanceFilterInfo( int instanceId, hkUint32 filterInfo )
{
	HK_ASSERT(0x17a29c, instanceId < m_instances.getSize() );
	m_instances[instanceId].m_filterInfo = filterInfo;
}

HK_FORCE_INLINE hkUint32 hkpStaticCompoundShape::getInstanceFilterInfo( int instanceId ) const
{
	HK_ASSERT(0x17a29c, instanceId < m_instances.getSize() );
	return m_instances[instanceId].m_filterInfo;
}


HK_FORCE_INLINE void hkpStaticCompoundShape::setInstanceFilterInfoMask( int instanceId, hkUint32 filterInfoMask )
{
	HK_ASSERT(0x17a29c, instanceId < m_instances.getSize() );
	m_instances[instanceId].m_childFilterInfoMask = filterInfoMask;
}

HK_FORCE_INLINE hkUint32 hkpStaticCompoundShape::getInstanceFilterInfoMask( int instanceId ) const
{
	HK_ASSERT(0x17a29c, instanceId < m_instances.getSize() );
	return m_instances[instanceId].m_childFilterInfoMask;
}


HK_FORCE_INLINE void hkpStaticCompoundShape::setInstanceUserData( int instanceId, hkUlong userData )
{
	HK_ASSERT(0x17a29c, instanceId < m_instances.getSize() );
	m_instances[instanceId].m_userData = userData;
}

HK_FORCE_INLINE hkUlong hkpStaticCompoundShape::getInstanceUserData( int instanceId ) const
{
	HK_ASSERT(0x17a29c, instanceId < m_instances.getSize() );
	return m_instances[instanceId].m_userData;
}


HK_FORCE_INLINE void hkpStaticCompoundShape::setInstanceExtraInfo( int instanceId, hkUint16 extraInfo )
{
	HK_ASSERT(0x17a29c, instanceId < m_instances.getSize() );
	const int maxSize = hkMath::max2( m_instanceExtraInfos.getSize(), instanceId + 1 );
	m_instanceExtraInfos.setSize( maxSize );
	m_instanceExtraInfos[instanceId] = extraInfo;
}


HK_FORCE_INLINE hkUint16 hkpStaticCompoundShape::getInstanceExtraInfo( int instanceId ) const
{
	HK_ASSERT(0x17a29c, instanceId < m_instances.getSize() && instanceId < m_instanceExtraInfos.getSize() );
	return m_instanceExtraInfos[instanceId];
}


HK_FORCE_INLINE void hkpStaticCompoundShape::setInstanceEnabled( int instanceId, hkBool32 isEnabled )
{
	HK_ASSERT(0x17a29c, instanceId < m_instances.getSize() );
	Instance& instance = m_instances[instanceId];
	hkUint32 flags = instance.getFlags();
	flags = (isEnabled ? (flags & ~Instance::FLAG_IS_DISABLED) : (flags | Instance::FLAG_IS_DISABLED));	
	instance.setFlags(flags);	
}

HK_FORCE_INLINE hkBool32 hkpStaticCompoundShape::isInstanceEnabled( int instanceId ) const
{
	HK_ASSERT(0x17a29c, instanceId < m_instances.getSize() );
	return !( m_instances[instanceId].getFlags() & Instance::FLAG_IS_DISABLED );
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
