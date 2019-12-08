/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_COLLIDE2_COLLISION_AGENT3_FILE_H
#define HK_COLLIDE2_COLLISION_AGENT3_FILE_H

extern const class hkClass hkpAgent1nSectorClass;

typedef void hkpAgentData;

struct hkpAgent1nSector
{
	HK_DECLARE_REFLECTION();

	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_AGENT, hkpAgent1nSector);
	
	enum { SECTOR_SIZE = 512, NET_SECTOR_SIZE = SECTOR_SIZE - HK_REAL_ALIGNMENT };

	hkUint32 m_bytesAllocated;

	hkUint32 m_pad0;
	hkUint32 m_pad1;
	hkUint32 m_pad2;
#if (HK_REAL_ALIGNMENT == 32)
	hkUint32 m_padTo32[4];
	hkUint8 m_data[512-32]; /*[ NET_SECTOR_SIZE ]*/ // Serialization script cannot take enum as array size.
#else
	hkUint8 m_data[512-16]; /*[ NET_SECTOR_SIZE ]*/ // Serialization script cannot take enum as array size.
#endif
	
	HK_FORCE_INLINE hkpAgentData* getBegin()
	{
		return reinterpret_cast<hkpAgentData*>( &m_data[0] );
	}

	hkpAgentData* getEnd()
	{
		HK_ASSERT( 0xf032ef45, unsigned(m_bytesAllocated) <= NET_SECTOR_SIZE );
		return reinterpret_cast<hkpAgentData*>( &m_data[m_bytesAllocated] );
	}

	hkpAgentData* getEndOfCapacity()
	{
		return reinterpret_cast<hkpAgentData*>( &m_data[NET_SECTOR_SIZE] );
	}

	int getCapacity()
	{
		return NET_SECTOR_SIZE;
	}
	
	int getFreeBytes()
	{
		return static_cast<int>(NET_SECTOR_SIZE - m_bytesAllocated);
	}
	
	inline hkpAgent1nSector(): m_bytesAllocated(0){}
	inline hkpAgent1nSector(class hkFinishLoadedObjectFlag flag) {}
};

struct hkpAgent1nTrack
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CDINFO, hkpAgent1nTrack );

	hkArray<hkpAgent1nSector*> m_sectors;

};




#endif // HK_COLLIDE2_COLLISION_AGENT3_FILE_H

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
