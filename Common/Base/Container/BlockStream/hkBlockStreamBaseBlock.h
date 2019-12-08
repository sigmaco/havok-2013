/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_BLOCKSTREAM_BLOCK_H
#define HK_BLOCKSTREAM_BLOCK_H
class hkBlockStreamAllocator;

namespace hkBlockStreamBase 
{
	class Stream;

	/// The basic storage container for the hkBlockStream::Stream. A stream consists of an arbitrary number of blocks.
	/// Each block can be filled with values/objects of a shared size (maximum allowed size is BLOCK_DATA_SIZE).
	/// Blocks should be aligned to 'BLOCK_ALIGNMENT' bytes.
	struct Block
	{
	public:
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE, Block );

		/// Defines the size of the block depending on the platform.
		enum
		{
	#if defined( HK_TINY_SPU_ELF )
			BLOCK_TOTAL_SIZE = 512, 
	#elif defined(HK_PLATFORM_HAS_SPU)
			BLOCK_TOTAL_SIZE = 1024*2, 
	#elif defined(HK_PLATFORM_CTR)
			BLOCK_TOTAL_SIZE = 512, 
	#else
			BLOCK_TOTAL_SIZE = 1024*4, 
	#endif
			BLOCK_HEADER_SIZE = 32,
			BLOCK_DATA_SIZE = BLOCK_TOTAL_SIZE - BLOCK_HEADER_SIZE,
			BLOCK_ALIGNMENT = 128,
		};

		/// Integral type big enough to count the number of bytes used.
		
		typedef hkUint16 CountType;

		/// The constructor. Note that the simple block stream allocator does not call it, so the block is uninitialized
		/// until it is used by a stream.
		HK_FORCE_INLINE Block();

		/// Zeros the block header. Usually called by the stream just after the block has been handed by the allocator.
		HK_FORCE_INLINE void setHeaderToZero();

		/// Read-only and read-write access to the beginning of the data int the block.
		HK_FORCE_INLINE void*		begin();	
		HK_FORCE_INLINE const void* begin() const; 

		/// Returns a pointer past the end of the block;
		HK_FORCE_INLINE void*		end();
		HK_FORCE_INLINE const void* end() const;

		/// Get the number of elements in the block.
		HK_FORCE_INLINE CountType getNumElements() const; 

		/// Get the number of bytes used in the block
		HK_FORCE_INLINE CountType getBytesUsed() const;	

		/// Change the number of elements.
		HK_FORCE_INLINE void setNumElements( CountType numElements );

		/// Change the number of bytes used.
		HK_FORCE_INLINE void setBytesUsed( CountType numBytes );

		/// Atomically decreases the number of elements. We need to do this (only in the Consumer) to avoid other 
		/// Consumers to interrupt it and try to free elements that are now invalid.
		HK_FORCE_INLINE void atomicDecreaseElementCount( int numElementsToFree );

	protected:
		/// This variable stores two 16-bits integers, respectively the number of elements that have yet not been
		/// consumed, and the number of bytes used in the block. They should be accessed by the get and set functions.
		/// numElements needs to be atomically decreased by Consumers, but atomic operations are only guaranteed
		/// on 32 bits int on every platform, so that's why it's stored in the least 16 significant bits.
		HK_ALIGN16( hkUint32 m_numElementsAndBytesUsed );	

	public:
		int						m_blockIndexInStream;		///< The index of this block in a stream
		Block*					m_next;						///< Next block in this linked list
		hkBlockStreamAllocator* m_allocator;				///< for debugging check and reporting
		Stream*					m_debugBlockStream;			///< for debugging checks and reporting
		HK_ALIGN_REAL( hkUchar  m_data[ BLOCK_DATA_SIZE ] );///< the actual data
	};

}
#include <Common/Base/Container/BlockStream/hkBlockStreamBaseBlock.inl>
#endif // HK_BLOCKSTREAM_BLOCK_H

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
