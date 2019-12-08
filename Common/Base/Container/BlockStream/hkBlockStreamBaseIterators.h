/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#ifndef HK_BLOCKSTREAM_ITERATORS_H
#define HK_BLOCKSTREAM_ITERATORS_H

#include <Common/Base/Container/BlockStream/hkBlockStreamBaseBlock.h>
#include <Common/Base/Container/BlockStream/hkBlockStreamBaseStream.h>

namespace hkBlockStreamBase
{
	/// A reader is a read-only iterator that goes through blocks from a stream and can return the elements it stores.	
	/// This serves as the base class for the templated version hkBlockStream<TYPE>::Reader and is intended
	/// for internal use only. On SPU it fetches several blocks at a time in a cache to avoid to many DMA calls.
	class Reader
	{
		public:

			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE, Reader );

			HK_FORCE_INLINE	Reader();
			HK_FORCE_INLINE ~Reader();

			//
			// Getters and setters
			//

			/// Returns the number of elements left to read in the current block
			HK_FORCE_INLINE int getNumUnreadElementsInThisBlock() const;

			/// Set the reader to 
			HK_FORCE_INLINE void setEmpty(); 

			/// Sets the reader to the start of a stream (on SPU, assumes stream is an SPU pointer)
			void setToStartOfStream( const Stream* stream );

			/// Sets the reader to the start of a range. (on SPU,  assume range is a PPU pointer)
			void setToRange( const Range* range );
			
			//
			// SPU memory management functions
			//

			void initSpu( int dmaGroup, int numActiveBlocks, const char* what ) {}
			void exitSpu() {}

			template<typename T>
			HK_FORCE_INLINE T* spuToPpu(T* t) const { HK_ASSERT( 0xf03df590, unsigned(hkGetByteOffsetInt(m_currentBlock, t)) < sizeof(Block)); return t; }


		protected:

			/// Advance and gives read-only access the next element, assumes the current entry is valid
			HK_FORCE_INLINE	const void* advanceAndAccessNext( int thisElemSize );

			/// Returns the current element (read-only).
			HK_FORCE_INLINE	const void* access();

			/// Advances to the next block in the stream.
			const void* advanceToNewBlock();

		protected:

			friend class Range;

			/// Pointer to the current block 
			HK_PAD_ON_SPU(const Block*)	m_currentBlock;

			/// Pointer to the current element in the block. 
			HK_PAD_ON_SPU(const char*)  m_currentByteLocation;
			
			/// Number of elements left to read in other blocks, to know whether to prefetch next block
			HK_PAD_ON_SPU(int) m_numElementsToReadInOtherBlocks;

			/// Number of elements left to read in the block.
			HK_PAD_ON_SPU(int) m_numElementsToReadInThisBlock;

	};

	/// A Writer is an iterator that adds data in a stream, allocating new blocks into the stream on the fly.
	/// This serves as the base class for the templated version hkBlockStream<TYPE>::Writer and is intended
	/// for internal use only. On SPU it fetches several blocks at a time in a cache to avoid to many DMA calls.
	class Writer
	{
		public:

			friend class Range;


		public:

			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE, Writer );

			/// Constructor
			HK_FORCE_INLINE Writer();

			/// Destructor
			HK_FORCE_INLINE ~Writer();

			//
			// Initializers.
			//

			/// Set to the start of an existing stream to write data in the stream from the beginning.
			void setToStartOfStream( Stream::Allocator* allocator, Stream* blockStreamPpu);

			/// Set to the end to an existing stream to append data
			void setToEndOfStream( Stream::Allocator* allocator, Stream* blockStreamPpu);
			
			//
			// Advance functions.
			//

			/// Advance by numBytes. This will move the write location in the current block.
			HK_FORCE_INLINE void advance( int numBytes );

			/// Reserve and advance a number of reservations in one go.
			/// This is faster than calling reserve and advance for large numbers of reservations, however, 
			/// no addresses are returned for writing.
			void batchReserveAndAdvance( int numReservations, int numBytesPerReservation );

			/// Call this method to put the stream back in a consistent and trimmed state.
			/// On SPU this will trigger the (final) write-back to PPU memory.
			void finalize();

			/// Returns the total number of elements in the writer's stream. This method should only be called
			/// after a call to finalize().
			HK_FORCE_INLINE int getTotalNumElems();

		#if defined(HK_DEBUG)
			HK_FORCE_INLINE void checkConsistency()
			{
				if (m_blockStream) { m_blockStream->checkConsistency(); }
			}
		#endif

			//
			// SPU memory management.
			// 

		protected:

			/// Will make sure that the next reserve will access a new block. It is used to create exclusive ranges.
			HK_FORCE_INLINE void setCurrentBlockFull();

			/// Return the address where we are allowed to write \a numBytes number of bytes to. This method will move
			/// to the next block in the stream if the free storage space in the current block is not enough.
			HK_FORCE_INLINE	void* reserveBytes( int numBytes );

			/// Allocates a new block, appends it to the end of the stream and returns the pointer to the new
			/// block's storage space.
			void *allocateAndAccessNewBlock();

			/// Advance by \a currentNumBytes in the stream and return a pointer to storage space where
			/// \a reservedNumBytes can be written to.
			HK_FORCE_INLINE	void* advanceAndReserveNext( int currentNumBytes, int reservedNumBytes );

			/// Wrap up the current block and link the next block. Make sure that \a thisBlock is actually pointing to
			/// the last block in the stream!
			HK_FORCE_INLINE void finalizeLastBlock( Block* HK_RESTRICT thisBlock, Block* HK_RESTRICT nextBlock, int thisBlockNumElements, int bytesUsed );

		public:

			/// The block stream this Writer is working on.
			HK_PAD_ON_SPU(Stream*)				m_blockStream;

		protected:

			/// The current block data is written to.
			HK_PAD_ON_SPU(Block*)				m_currentBlock;

			/// The current byte location where data is written to in the current block (m_currentBlock). 
			/// This value is an offset into the current block and NOT an absolute address.
			HK_PAD_ON_SPU(int)					m_currentByteLocation;	

			/// The number of elements stored in the current block.
			HK_PAD_ON_SPU(int)					m_currentBlockNumElems;	
			
			/// The underlying thread allocator that will allocate blocks when writing.
			HK_PAD_ON_SPU(Stream::Allocator*)	m_tlAllocator;

			/// Debugging flag
			hkBool								m_finalized;		

			/// Debugging value : the numBytes used in the last call to reserveBytes()
			int									m_accessSize;		

	};

	/// A Consumer inherits from the Reader iterator and adds the additional effect of freeing the block after having read
	/// its last element.
	class Consumer : public Reader
	{
		public:

			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE, Consumer );

			HK_FORCE_INLINE	Consumer() {}

			/// Sets the consumer to the first block of a stream.
			void setToStartOfStream( Stream::Allocator* allocator, Stream* stream, Stream* m_blockStreamPpu );
			
			/// Set to a whole range.
			void setToRange( Stream::Allocator* allocator, Stream* stream, Stream* m_blockStreamPpu, const Range* range );

		protected:

			/// Advance and access the next element, freeing the old data. Assumes the current entry is valid.
			HK_FORCE_INLINE	const void* consumeAndAccessNext( int thisElemSize );

			/// Frees current block and advance to next one.
			const void* freeAndAdvanceToNewBlock();

			/// Non-const accessors (casts the const away).
			HK_FORCE_INLINE Block* getCurrentBlock();
			HK_FORCE_INLINE char*  getCurrentByteLocation();

		protected:

			friend class Range;

			Stream* m_blockStream;	// points to SPU version
			HK_PAD_ON_SPU(int) m_numElementsToFreeInThisBlock;
			HK_PAD_ON_SPU(Stream::Allocator*) m_allocator;
	};


	/// Modifier inherits from reader but allows to get read-write access to modify its current element.
	class Modifier : public Reader
	{
		public:

			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE, Modifier );

			HK_FORCE_INLINE	Modifier() {}

			/// Sets the modifier to the first block of a stream.
			HK_FORCE_INLINE void setToStartOfStream( Stream::Allocator* allocator, Stream* stream, Stream* m_blockStreamPpu );

			/// Set to a whole range. 
			HK_FORCE_INLINE void setToRange( const Range* range );

		protected:

			/// Advance and gives read-write access the next element, assumes the current entry is valid
			HK_FORCE_INLINE	void* advanceAndAccessNext( int thisElemSize );

			/// Read-write access to the current element.
			HK_FORCE_INLINE	void* access();

			/// Advances to the next block (when we are at the end of a block).
			void* advanceToNewBlock();

			/// Non-const accessors (casts the const away).
			Block* getCurrentBlock();
			char*  getCurrentByteLocation();

		protected:

			HK_PAD_ON_SPU(Stream::Allocator*) m_allocator;
	};
}

#include <Common/Base/Container/BlockStream/hkBlockStreamBaseIterators.inl>

#endif// HK_BLOCKSTREAM_ITERATORS_H

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
