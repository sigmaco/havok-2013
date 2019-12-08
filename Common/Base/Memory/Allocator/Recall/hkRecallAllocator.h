/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_RECALL_ALLOCATOR_H
#define HK_RECALL_ALLOCATOR_H

#include <Common/Base/Thread/CriticalSection/hkCriticalSection.h>

	/// Debugging passthrough allocator which remembers requests and forwards them to another allocator.
	/// WARNING: this class is extremely slow for large number of allocations.
	/// It maintains a linked list of all active allocations.
class hkRecallAllocator : public hkMemoryAllocator
{
	//+hk.MemoryTracker(ignore=True)
	public:

		hkRecallAllocator(hkMemoryAllocator* a);

		void init(hkMemoryAllocator* a);
		virtual void* blockAlloc( int numBytes );
		virtual void blockFree( void* p, int numBytes );

		virtual void getMemoryStatistics( hkMemoryAllocator::MemoryStatistics& u );
		virtual int getAllocatedSize(const void* obj, int nbytes);
		virtual void resetPeakMemoryStatistics();

		struct Header
		{
			protected:
				friend class hkRecallAllocator;
				Header* m_next;			// Next allocation in the list.
				int m_requestedSize;	// The size we requested from the next allocator.
				int m_payloadSize;		// The size which was requested from this allocator.

			public:
				int getRequestedSize() const { return m_requestedSize; }
				int getPayloadSize() const { return m_payloadSize; }
				const void* getPayload() const { return hkAddByteOffsetConst(this,16); }
				void* getPayload() { return hkAddByteOffset(this,16); }
				const Header* getNext() const { return m_next; }
		};
		const Header* getHead() const { return m_head; }

	protected:

		hkCriticalSection m_criticalSection;
		hkMemoryAllocator* m_alloc;
		MemoryStatistics m_stats;
		Header* m_head;
};

#endif // HK_RECALL_ALLOCATOR_H

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
