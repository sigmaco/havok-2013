/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKCD_PLANAR_GEOMETRY_PRIMITIVES_COLLECTION_H
#define HKCD_PLANAR_GEOMETRY_PRIMITIVES_COLLECTION_H

#include <Geometry/Collide/DataStructures/PlanarGeometry/Primitives/hkcdPlanarGeometryPrimitives.h>

namespace hkcdPlanarGeometryPrimitives
{
	/// Low-level memory management for a collection of primitives
	template <int LogMaxN>
	class Collection
	{
		public:

			/// Constants. We store free blocks in lists as follows:
			///		32 - LOG_MIN_BLOCK_SIZE master lists, each storing free blocks with sizes between [2^M, 2^(M + 1) - 1]
			///		Each master list is divided into a set of sub-lists, the number of divisions being maximum 32.
			enum
			{
				LOG_MIN_BLOCK_SIZE	= 2,										///< L = log_2(MIN_BLOCK_SIZE)
				LOG_MAX_BLOCK_SIZE	= LogMaxN,									///< Cannot allocate more than this, as we would overwrite our block flags
				MIN_BLOCK_SIZE		= (1 << LOG_MIN_BLOCK_SIZE),				///< Minimum block size is 4 ints.
				MAX_BLOCK_SIZE		= (1 << LOG_MAX_BLOCK_SIZE),				///< Maximum block size in ints.
				LOG_MAX_DIVISIONS	= 5,										///< log_2(MAX_DIVISIONS)
				MAX_DIVISIONS		= (1 << LOG_MAX_DIVISIONS),					///< We divide blocks into at most 32 subdivisions
				NUM_SECONDARY_BMPS	= LOG_MAX_BLOCK_SIZE - LOG_MIN_BLOCK_SIZE,	///< The number of secondary bitmaps

				/// The first block is reserved for internal use, so we use address 0 to mark invalid addresses.
				INVALID_BLOCK_ADDR	= 0,

				/// Special block markers
				END_PAYLOAD_BIT		= LogMaxN			+ 1,	///< Marks the end of the used data in an allocated block.
				END_BLOCK_BIT		= END_PAYLOAD_BIT	+ 1,	///< Marks the end of the allocated block.
				FREE_BLOCK_BIT		= END_BLOCK_BIT		+ 1,	///< Marks a free block
				END_PAYLOAD_FLAG	= 1 << END_PAYLOAD_BIT,
				END_BLOCK_FLAG		= 1 << END_BLOCK_BIT,
				FREE_BLOCK_FLAG		= 1 << FREE_BLOCK_BIT,

				BLOCK_FLAGS_MASK	= (hkUint32)(-1 << END_PAYLOAD_BIT),
				PAYLOAD_MASK		= ~BLOCK_FLAGS_MASK,
			};

		protected:

			// A free memory block
			struct Block
			{
				/// Marks the block as allocated
				HK_FORCE_INLINE void setAllocated();
				HK_FORCE_INLINE int isAllocated() const;

				/// Marks the block as free
				HK_FORCE_INLINE void setFree();
				HK_FORCE_INLINE int isFree() const;

				/// Gets / Sets the size of the block
				HK_FORCE_INLINE void setSize(int size);
				HK_FORCE_INLINE hkUint32 getSize() const;

				// Gets / Sets the previous block address
				HK_FORCE_INLINE hkUint32 getPrevBlockAddress() const;
				HK_FORCE_INLINE void setPrevBlockAddress(hkUint32 prevAddr);

				// Gets / Sets the next block address
				HK_FORCE_INLINE hkUint32 getNextBlockAddress() const;
				HK_FORCE_INLINE void setNextBlockAddress(hkUint32 nextAddr);

				hkUint32 m_prevBlockAddr;		///< Address of the previous free block in the list
				hkUint32 m_nextBlockAddr;		///< Address of the next free block in the list
				hkUint32 m_size;				///< Block size (in ints)
				hkUint32 m_endTerminator;		///< Block end terminator
			};

		public:

			/// Allocates a block having the given size (in ints).
			hkUint32 blockAlloc(hkUint32& blockSize);

			/// Frees the given polygon
			HK_FORCE_INLINE void blockFree(hkUint32 blockAddr);
			void blockFree(hkUint32 blockAddr, hkUint32 payloadLen);

			/// Creates the collection with the given initial size
			void create(int initialFreeSize);

			/// Deallocates all polygons
			void clear();

			/// Copies the given polygon collection over this
			void copy(const Collection& other);

			// Expands the available storage by at least the requested size.
			HK_FORCE_INLINE void expandStorage(hkUint32 allocSize);

		protected:

			// Retrieves the free block at the given Id.
			HK_FORCE_INLINE const Block* getFreeBlock(hkUint32 polyId) const;
			HK_FORCE_INLINE Block* accessFreeBlock(hkUint32 polyId);

			/// Computes the primary and secondary map indices for allocating a block of size n.
			/// The size is augmented to a higher value such that the indices always point to blocks with size >= n.
			HK_FORCE_INLINE void computeMapIndicesAlloc(hkUint32 allocSize, hkUint32& primaryIdxOut, hkUint32& secondaryIdxOut) const;

			/// Searches for a suitable free block
			HK_FORCE_INLINE hkUint32 searchForSuitableBlock(hkUint32& primaryIdxOut, hkUint32& secondaryIdxOut) const;

			/// Computes the primary and secondary map indices for inserting a block of size n into the free lists.
			HK_FORCE_INLINE void computeMapIndicesSearch(hkUint32 blockSize, hkUint32& primaryIdxOut, hkUint32& secondaryIdxOut) const;

			/// Inserts a free block into one of the lists
			HK_FORCE_INLINE void insert(hkUint32 blockAddr);

			// Removes a free block from the given free list.
			HK_FORCE_INLINE void remove(hkUint32 blockAddr, hkUint32 primaryIdx, hkUint32 secondaryIdx);

			// Returns true if the previous physical block relative to the given address is free
			HK_FORCE_INLINE int isPrevPhysicalBlockFree(hkUint32 blockAddr) const;

			// Returns the size of the previous block. This function will succeed only if the block is free and assert otherwise!
			HK_FORCE_INLINE hkUint32 getPrevFreePhysicalBlockSize(hkUint32 blockAddr) const;

			// Computes the size of the given allocated block
			HK_FORCE_INLINE hkUint32 computeBlockSize(hkUint32 blockAddr) const;

			/// Computes the payload size of the given allocated block
			HK_FORCE_INLINE hkUint32 computePayloadSize(hkUint32 blockAddr) const;

			/// Returns the next allocated block address
			HK_FORCE_INLINE hkUint32 getNextAllocatedAddress(hkUint32 blockAddr) const;

			/// Returns the previous allocated block address
			HK_FORCE_INLINE hkUint32 getPrevAllocatedAddress(int blockAddr) const;

		protected:

			hkArray<int> m_storage;	///< The memory buffer

			/// Primary free blocks bit-field. If the I-th bit is set, we have available
			/// free blocks with sizes in [2^(I + L), 2^(I + L + 1) - 1]
			hkUint32 m_primaryBitmap;

			/// Secondary free blocks bit-fields. If the I-th bit of the M-th bitmap is set, we have available
			/// free blocks with sizes[2^(M + L) + I * 2^(M + L - G), 2^(M + L) + (I + 1) * 2^(M + L - G) - 1],
			/// where G = min(M, LOG_MAX_DIVISIONS)
			hkUint32 m_secondaryBitmaps[NUM_SECONDARY_BMPS];

			/// Heads of the free block lists
			hkUint32 m_freeBlocks[NUM_SECONDARY_BMPS][MAX_DIVISIONS];
	};
}

#include <Geometry/Collide/DataStructures/PlanarGeometry/Memory/hkcdPlanarGeometryPrimitivesCollection.inl>

#endif	//	HKCD_PLANAR_GEOMETRY_PRIMITIVES_COLLECTION_H

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
