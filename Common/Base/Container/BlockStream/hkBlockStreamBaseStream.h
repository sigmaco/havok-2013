/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#ifndef HK_BLOCKSTREAM_STREAM_H
#define HK_BLOCKSTREAM_STREAM_H

#include<Common/Base/Container/BlockStream/hkBlockStreamBaseBlock.h>

class hkBlockStreamAllocator;
class hkThreadLocalBlockStreamAllocator;

namespace hkBlockStreamBase
{
	class Range;


	/// A Stream is a sequence of arbitrary blocks to be accessed by readers and writers.
	/// Writers make it grow by allocating more block into the stream as they add more data, while
	/// Consumers free the blocks as they read it (so the consumed blocks of the stream are
	/// no longer valid).
	class Stream
	{
		public:

			/// The allocator used by this stream.
			typedef hkThreadLocalBlockStreamAllocator Allocator;

			/// Iterator classes
			friend class Consumer;
			friend class Reader;
			friend class Writer;

			friend class Range;

			/// The capacity of the in-place block array.
			enum { INPLACE_PBLOCK_STORAGE = 24 };

		public:

			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE, Stream );

			/// Convenience constructor.
			HK_FORCE_INLINE Stream( Allocator* tlAllocator, bool zeroNewBlocks = false ); 
			/// Empty constructor. Call initBlockStream to initialize a stream.
			HK_FORCE_INLINE Stream(){}

			/// Destructor. You have to call clear() before calling the destructor 
			/// since destructors do not take parameters, you can't pass a thread allocator.
			HK_FORCE_INLINE ~Stream();

			//
			// Block management functions
			//

			/// Initializes the stream by taking a new block from the given allocator.
			
			void initBlockStream( Allocator* tlAllocator, bool zeroNewBlocks = false );

			/// Resets the stream : clears it and allocates 1 empty block.
			void reset( Allocator* HK_RESTRICT tlAllocator );

			/// Clears the stream (without resetting it) only use if you call append immediately after this
			/// or before destruction.
			void clear( Allocator* HK_RESTRICT tlAllocator );

			/// Appends all the blocks of the stream to this one, and delete the other.
			/// If both streams are empty the stream will be initialized with 1 empty block.
			void append( Allocator* HK_RESTRICT tlAllocator, Stream* inStream );

			/// Removes the consumed blocks from the stream. Call this if you want to reuse this block stream after you
			/// consumed some blocks.
			void fixupConsumedBlocks(Allocator* HK_RESTRICT tlAllocator);

			/// Releases all blocks that precede the given range
			void freeAllBlocksBeforeRange(Allocator* HK_RESTRICT tlAllocator, const Range* range);

			/// Moves an exclusive range to the back of the stream. A range is exclusive if it doesn't share
			/// any blocks with other ranges.
			void moveExclusiveRangeToBack( Allocator* HK_RESTRICT tlAllocator, const Range* rangeInOut );

			//
			// Getters
			//
			
			/// Returns true if the stream has no elements in its blocks (equivalent to getTotalNumElems() == 0).
			HK_FORCE_INLINE bool isEmpty() const;

			/// Returns the total number of elements stored in the stream's blocks.
			HK_FORCE_INLINE int getTotalNumElems() const;

			/// Returns the total size of all the blocks in the stream.
			HK_FORCE_INLINE int getTotalBytesAllocated() const;

			/// Returns the underlying block stream allocator.
			HK_FORCE_INLINE const hkBlockStreamAllocator* getAllocator() const;

			//
			// Consistency checks
			//

			/// Checks the consistency of the block headers, not the block contents
			void checkConsistency( ) const;

			/// Checks whether an input array of ranges is consistent with the block stream
			void checkConsistencyWithGrid( const Range* rangesIn, int numRanges, int rangeStriding, bool allowForUnusedData ) const;
			
			/// Checks whether a single range is consistent with the block stream.
			void checkConsistencyOfRange( const Range& range );

		protected:

			//
			// Accessors for beginning and end of stream. 
			//

			/// Returns the first block of the stream. 
			HK_ON_CPU( HK_FORCE_INLINE ) const Block* begin() const; 

			/// Returns the first block of the stream.
			HK_ON_CPU( HK_FORCE_INLINE ) const Block* last() const;

			/// Returns the first block of the stream, with read-write access.
			HK_FORCE_INLINE Block* beginRw();

			/// Returns the last block of the stream, with read-write access.  
			HK_FORCE_INLINE Block* lastRw(); 

			// append a list of ranges, creates lots of holes but is really fast
			//void append( Allocator* HK_RESTRICT tlAllocator, Range* ranges, int numRanges, int rangeStriding );

			/// Allocate and append a new block to the stream.
			Block* blockAlloc(Allocator* tlAllocator);

			/// Remove and free the last block of the stream.
			Block* popBack( Allocator* tlAllocator );

			/// Explicitely frees a block in the stream;
			void freeBlockWithIndex(Allocator* HK_RESTRICT tlAllocator, Block* HK_RESTRICT blockPpu, int index);		

		public:
			/// The base allocator used to get the blocks
			protected:		hkBlockStreamAllocator* m_allocator;	

			/// True if some blocks of the stream have been freed.
			public: 		hkBool	m_partiallyFreed;
			
			/// If set, all new blocks will be entirely zeroed (instead of only the header).
			public:			hkBool  m_zeroNewBlocks;			

			/// Lock for readers and writers.
			protected:		hkBool	m_isLocked;

			/// If set, a block was sent back to PPU which was touched by a consumer
			protected:		hkBool  m_spuWronglySentConsumedBlockStreamBack;

			///< The total number of elements in this stream. This value is only valid after a call to Writer::finalizeLastBlock().
							int		m_numTotalElements;	
		private:

			/// Blocks owned by this stream.
			/// This array is aligned because it needs to be accessed using SPU DMA transfers.
			hkInplaceArrayAligned16< Block*, INPLACE_PBLOCK_STORAGE > m_blocks;
	};
}
#include <Common/Base/Container/BlockStream/hkBlockStreamBaseStream.inl>

#endif //HK_BLOCKSTREAM_STREAM_H

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
