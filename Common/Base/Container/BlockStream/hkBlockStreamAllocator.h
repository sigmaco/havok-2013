/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_BLOCK_STREAM_ALLOCATOR_H
#define HK_BLOCK_STREAM_ALLOCATOR_H

#include <Common/Base/Container/BlockStream/hkBlockStream.h>
#include <Common/Base/Thread/CriticalSection/hkCriticalSection.h>

	#define HK_NOT_VIRTUAL_ON_SPU	virtual


class hkBlockStreamAllocator: public hkReferencedObject
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_COLLIDE);

		typedef hkBlockStreamBase::Block Block;		


		/// Allocate blocks.
		/// Notes:
		///     - 'this' is a pointer to ppu.
		virtual void blockAllocBatch( Block** blocksOut, int nblocks ) = 0;

		/// Free blocks.
		/// Note: 'this' is a pointer to ppu
		virtual void blockFreeBatch( Block** blocks, int nblocks ) = 0;

		/// Get the current bytes used. Note that data in the thread local allocator will
		/// count as bytes used (as they are not available to other threads in a worst case
		/// scenario).
		virtual int getBytesUsed() const= 0;

		/// Get the peak usage.
		virtual int getMaxBytesUsed() const = 0;

		/// Get the maximum amount of memory that can be allocated through this allocator.
		virtual int getCapacity() const = 0;

		/// Sets all data to be free, even if there are outstanding allocations.
		virtual void freeAllRemainingAllocations() = 0;
		
		/// Returns an aggregate on memory statistics of this allocator.
		virtual void getMemoryStatistics( hkMemoryAllocator::MemoryStatistics& statsOut ) const = 0;

};


/// A simple implementation of block stream allocators, this is the only implementation available on SPU
class hkSimpleBlockStreamAllocator : public hkBlockStreamAllocator
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_COLLIDE);

		typedef hkBlockStreamBase::Block Block;		
		
		HK_NOT_VIRTUAL_ON_SPU void blockAllocBatch(Block** blocksOut, int nblocks);
		
		HK_NOT_VIRTUAL_ON_SPU void blockFreeBatch(Block** blocks, int nblocks);


		/// get the current bytes used. Note that data in the thread local allocator will
		/// count as bytes used (as they are not available to other threads in a worst case
		/// scenario).
		virtual int getBytesUsed() const;

		/// the peak usage
		virtual int getMaxBytesUsed() const;

		/// Returns the total number of bytes available
		virtual int getCapacity() const;

		void init( int byteSize );

		void init( void* buffer, int byteSize );

		/// free all memory, only necessary if this class allocated the memory
		void clear();

		/// Asserts if any data is allocated.
		void freeAllRemainingAllocations();

		hkSimpleBlockStreamAllocator(int allocSize = 0);

		~hkSimpleBlockStreamAllocator();

		void addMemory( void* buffer, int byteSize );

		void getMemoryStatistics( hkMemoryAllocator::MemoryStatistics& statsOut ) const;


	private:

		void rebuildFreelist();

	public:

		Block* m_storage;

		hkArray< Block* > m_freeList;

		int		m_capacity;			// number of total blocks available
		int     m_minFreeListSize;	// for peak memory usage
		hkBool	m_dontDeallocate;
		hkBool  m_enableAllocationTimerInfo;	///< add extra used memory timer infos into the timer stream, debug only
		HK_ALIGN16(mutable hkCriticalSection m_criticalSection);	///< the critical section, must be the last element
};


/// Thread local allocator, which caches a number of blocks, not overridable.
class hkThreadLocalBlockStreamAllocator
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_COLLIDE, hkThreadLocalBlockStreamAllocator );

		/// Constructor.
		/// Note that on SPU, bsAllocator must be a PPU pointer
		hkThreadLocalBlockStreamAllocator( hkBlockStreamAllocator* bsAllocator, int threadId ): m_blockStreamAllocator( bsAllocator ), m_numFreeBlocks(0)
		{
			HK_ON_CPU( m_threadId = threadId );
		}

		~hkThreadLocalBlockStreamAllocator()
		{
			clear();
		}

		/// Allocate a block
		hkBlockStreamAllocator::Block* blockAlloc();

		/// Deallocate a block
		void blockFree( hkBlockStreamAllocator::Block* blockPpu );

		/// Free a batch
		void blockFreeBatch( hkBlockStreamAllocator::Block** blocks, int nblocks );

		/// Clear all locally cached blocks
		void clear();

		enum
		{
			BATCH_ALLOC_SIZE		= 6,	///< The number of blocks freed/allocated in one go in the m_blockStreamManager
			MAX_FREE_LIST_SIZE		= 8,	///< The maximum number of elements cached locally
		};

	protected:
		void checkConsistency( );

	public:

		HK_ON_CPU( int m_threadId );
		hkPadSpu<hkBlockStreamAllocator*> m_blockStreamAllocator;

		hkPadSpu<int> m_numFreeBlocks;
		hkBlockStreamAllocator::Block* m_freeBlocks[MAX_FREE_LIST_SIZE];
};

#include <Common/Base/Container/BlockStream/hkBlockStreamAllocator.inl>


#endif // HK_BLOCK_STREAM_ALLOCATOR_H

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
