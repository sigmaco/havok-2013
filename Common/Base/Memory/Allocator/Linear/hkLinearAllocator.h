/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_LINEAR_ALLOCATOR_H
#define HK_LINEAR_ALLOCATOR_H

#include <Common/Base/Thread/CriticalSection/hkCriticalSection.h>

/// Linear allocator which allocates from a given buffer.
/// This allocator performs allocations from a given memory buffer. Memory chunks 
/// taken from this buffer are never reused.
/// Eventually this allocator will run out of memory, it is only useful for debug
/// and designed for internal use only.
class hkLinearAllocator : public hkMemoryAllocator
{
	//+hk.MemoryTracker(ignore=True)
	public:
		HK_DECLARE_PLACEMENT_ALLOCATOR();

		hkLinearAllocator(hkUint8* buffer, int bufferSize);
		virtual ~hkLinearAllocator();
		virtual void* blockAlloc(int n);
		virtual void blockFree(void*p, int n);
		virtual void getMemoryStatistics( MemoryStatistics& u );
		virtual int getAllocatedSize(const void* obj, int nbytes);

        template< hkUint32 BUFFER_SIZE >
        class Inplace;

	protected:
		hkUint32 m_index; // initialized to 0
		// static buffer
		hkUint8* m_bufferPtr;
		hkUint32 m_bufferSize;
		// used for statistics
		hkUint32 m_inUse; // without overhead
		hkUint32 m_peakInUse; // usage peak without overhead
		// critical section used for multi-threading
		hkCriticalSection m_criticalSection;
};

template< hkUint32 BUFFER_SIZE >
class hkLinearAllocator::Inplace : public hkLinearAllocator
{
		//+hk.MemoryTracker(ignore=True)
	public:
		HK_DECLARE_PLACEMENT_ALLOCATOR();

		Inplace() : hkLinearAllocator(&m_buffer[0], BUFFER_SIZE) {}

	protected:
		// allocation buffer
		HK_ALIGN_REAL( hkUint8 m_buffer[BUFFER_SIZE] );
};

#endif // HK_LINEAR_ALLOCATOR_H

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
