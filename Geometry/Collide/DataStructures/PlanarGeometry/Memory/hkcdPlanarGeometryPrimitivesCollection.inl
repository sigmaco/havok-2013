/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

//
//	Marks the block as allocated

template <int LogMaxN>
HK_FORCE_INLINE void hkcdPlanarGeometryPrimitives::Collection<LogMaxN>::Block::setAllocated()
{
	m_prevBlockAddr &= ~FREE_BLOCK_FLAG;
	reinterpret_cast<int*>(this)[m_size - 1] &= ~FREE_BLOCK_FLAG;
}

template <int LogMaxN>
HK_FORCE_INLINE int hkcdPlanarGeometryPrimitives::Collection<LogMaxN>::Block::isAllocated() const
{
	return !isFree();
}

//
//	Marks the block as free

template <int LogMaxN>
HK_FORCE_INLINE void hkcdPlanarGeometryPrimitives::Collection<LogMaxN>::Block::setFree()
{
	m_prevBlockAddr |= FREE_BLOCK_FLAG;
	reinterpret_cast<int*>(this)[m_size - 1] |= FREE_BLOCK_FLAG;
}

template <int LogMaxN>
HK_FORCE_INLINE int hkcdPlanarGeometryPrimitives::Collection<LogMaxN>::Block::isFree() const
{
	const hkUint32 f = (m_prevBlockAddr & FREE_BLOCK_FLAG);
	HK_ASSERT(0x7aeceba1, !f || (reinterpret_cast<const int*>(this)[m_size - 1] & FREE_BLOCK_FLAG));
	return f;
}

//
//	Gets / Sets the size of the block

template <int LogMaxN>
HK_FORCE_INLINE void hkcdPlanarGeometryPrimitives::Collection<LogMaxN>::Block::setSize(int size)
{
	// Store the size twice, once in m_size and another time in this[size - 1],
	// so we can retrieve it when accessing a block from the left
	m_size = size;
	reinterpret_cast<int*>(this)[size - 2] = size;
	reinterpret_cast<int*>(this)[size - 1] |= END_BLOCK_FLAG;
}

template <int LogMaxN>
HK_FORCE_INLINE hkUint32 hkcdPlanarGeometryPrimitives::Collection<LogMaxN>::Block::getSize() const
{
	HK_ASSERT(0x74d4e22f, m_size == reinterpret_cast<const hkUint32*>(this)[m_size - 2] );
	HK_ASSERT(0x13a81ca7, reinterpret_cast<const hkUint32*>(this)[m_size - 1] & END_BLOCK_FLAG);
	return m_size;
}

//
//	Gets / Sets the previous block address

template <int LogMaxN>
HK_FORCE_INLINE hkUint32 hkcdPlanarGeometryPrimitives::Collection<LogMaxN>::Block::getPrevBlockAddress() const
{
	return m_prevBlockAddr & PAYLOAD_MASK;
}

template <int LogMaxN>
HK_FORCE_INLINE void hkcdPlanarGeometryPrimitives::Collection<LogMaxN>::Block::setPrevBlockAddress(hkUint32 prevAddr)
{
	m_prevBlockAddr = (prevAddr & PAYLOAD_MASK) | (m_prevBlockAddr & BLOCK_FLAGS_MASK);
}

//
//	Gets / Sets the next block address

template <int LogMaxN>
HK_FORCE_INLINE hkUint32 hkcdPlanarGeometryPrimitives::Collection<LogMaxN>::Block::getNextBlockAddress() const
{
	return m_nextBlockAddr;
}

template <int LogMaxN>
HK_FORCE_INLINE void hkcdPlanarGeometryPrimitives::Collection<LogMaxN>::Block::setNextBlockAddress(hkUint32 nextAddr)
{
	m_nextBlockAddr = nextAddr;
}

//
//	Computes the primary and secondary map indices for allocating a block of size n.
//	The size is augmented to a higher value such that the indices always point to blocks with size >= n.

template <int LogMaxN>
HK_FORCE_INLINE void hkcdPlanarGeometryPrimitives::Collection<LogMaxN>::computeMapIndicesAlloc(hkUint32 allocSize, hkUint32& primaryIdxOut, hkUint32& secondaryIdxOut) const
{
	const hkUint32 M	= 31 - hkMath::countLeadingZeros(allocSize);									// Compute M such that allocSize is in [2^M, 2^(M + 1) - 1]
	hkUint32 n			= allocSize & (~(1 << M));														// Cancel-out the base alloc size, i.e. 2^M
	const hkUint32 G	= hkMath::min2<hkUint32, hkUint32>(M - LOG_MIN_BLOCK_SIZE, LOG_MAX_DIVISIONS);	// Compute the granularity for this size
	n					= HK_NEXT_MULTIPLE_OF(1 << (M - G), n);											// Augment n to the next multiple of 2^(M - G) so we are certain the block size is >= n
	const hkUint32 K	= n >> (M - G);																	// Compute K such that n is in [k * 2^(M - G), (k + 1) * 2^(M - G + 1) - 1]
	HK_ASSERT(0x413de78a, K <= (hkUint32)(1 << G));														// At this point K <= 2^G

	// Propagate "carry" bit from K and store output
	primaryIdxOut	= M + (K >> G) - LOG_MIN_BLOCK_SIZE;
	secondaryIdxOut	= K & (~(1 << G));
}

//
//	Computes the primary and secondary map indices for inserting a block of size n into the free lists.

template <int LogMaxN>
HK_FORCE_INLINE void hkcdPlanarGeometryPrimitives::Collection<LogMaxN>::computeMapIndicesSearch(hkUint32 blockSize, hkUint32& primaryIdxOut, hkUint32& secondaryIdxOut) const
{
	const hkUint32 M	= 31 - hkMath::countLeadingZeros(blockSize);									// Compute M such that allocSize is in [2^M, 2^(M + 1) - 1]
	hkUint32 n			= blockSize & (~(1 << M));														// Cancel-out the base alloc size, i.e. 2^M
	const hkUint32 G	= hkMath::min2<hkUint32, hkUint32>(M - LOG_MIN_BLOCK_SIZE, LOG_MAX_DIVISIONS);	// Compute the granularity for this size
	const hkUint32 K	= n >> (M - G);																	// Compute K such that n is in [k * 2^(M - G), (k + 1) * 2^(M - G + 1) - 1]
	HK_ASSERT(0x6da75120, K < (hkUint32)(1 << G));														// At this point K < 2^G

	// Store output
	primaryIdxOut	= M - LOG_MIN_BLOCK_SIZE;
	secondaryIdxOut	= K;
}

//
//	Inserts a free block into one of the lists

template <int LogMaxN>
HK_FORCE_INLINE void hkcdPlanarGeometryPrimitives::Collection<LogMaxN>::insert(hkUint32 blockAddr)
{
	// Get block and compute the indices in the lists
	Block* block		= accessFreeBlock(blockAddr);
	const hkUint32 blockSize	= block->getSize();
	hkUint32 primaryIdx, secondaryIdx;
	computeMapIndicesSearch(blockSize, primaryIdx, secondaryIdx);

	// Insert
	{
		// Add block to the head of its list. List heads are always valid (i.e. either at
		// address 0 or another valid block). If the list head is 0, we can always change its prev
		// to point anywhere, as the other block's next will point to 0, i.e. invalid entry.
		hkUint32& headAddr	= m_freeBlocks[primaryIdx][secondaryIdx];
		Block* head	= accessFreeBlock(headAddr);

		block->setNextBlockAddress(headAddr);
		block->setPrevBlockAddress(INVALID_BLOCK_ADDR);
		head->setPrevBlockAddress(blockAddr);
		headAddr = blockAddr;

		// Mark the bitmaps appropriately
		m_primaryBitmap					|= (1 << primaryIdx);
		m_secondaryBitmaps[primaryIdx]	|= (1 << secondaryIdx);
	}
}

//
//	Removes a free block from the given free list.

template <int LogMaxN>
HK_FORCE_INLINE void hkcdPlanarGeometryPrimitives::Collection<LogMaxN>::remove(hkUint32 blockAddr, hkUint32 primaryIdx, hkUint32 secondaryIdx)
{
	// Get block and the pointers to the prev and next free blocks
	Block* block			= accessFreeBlock(blockAddr);
	const hkUint32 nextBlockAddr	= block->getNextBlockAddress();
	const hkUint32 prevBlockAddr	= block->getPrevBlockAddress();

	// Remove block from the list
	Block* next = accessFreeBlock(nextBlockAddr);
	Block* prev = accessFreeBlock(prevBlockAddr);
	next->setPrevBlockAddress(prevBlockAddr);
	prev->setNextBlockAddress(nextBlockAddr);

	// If this block is the head of the free list, set new head.
	if ( m_freeBlocks[primaryIdx][secondaryIdx] == blockAddr )
	{
		m_freeBlocks[primaryIdx][secondaryIdx] = nextBlockAddr;

		// If the new head is null, clear the bitmap.
		if ( nextBlockAddr == INVALID_BLOCK_ADDR )
		{
			m_secondaryBitmaps[primaryIdx] &= ~(1 << secondaryIdx);

			// If the second bitmap is now empty, clear the fl bitmap.
			if ( !m_secondaryBitmaps[primaryIdx] )
			{
				m_primaryBitmap &= ~(1 << primaryIdx);
			}
		}
	}
}

//
//	Searches for a suitable free block

template <int LogMaxN>
HK_FORCE_INLINE hkUint32 hkcdPlanarGeometryPrimitives::Collection<LogMaxN>::searchForSuitableBlock(hkUint32& primaryIdx, hkUint32& secondaryIdx) const
{
	// Search for a block with size >= requested size among all secondary lists.
	hkUint32 secondaryMap = m_secondaryBitmaps[primaryIdx] & (-1 << secondaryIdx);
	if ( !secondaryMap )
	{
		// No block exists. Search in the next largest first-level list.
		const hkUint32 primaryMap = m_primaryBitmap & (-1 << (primaryIdx + 1));
		if ( !primaryMap )
		{
			// No free blocks available, memory has been exhausted!
			return INVALID_BLOCK_ADDR;
		}

		primaryIdx		= hkMath::countTrailingZeros(primaryMap);
		secondaryMap	= m_secondaryBitmaps[primaryIdx];
	}

	// Sanity check - second level bitmap should be non-null
	HK_ASSERT(0x75017044, secondaryMap);
	secondaryIdx = hkMath::countTrailingZeros(secondaryMap);

	// Return the first block in the free list.
	HK_ASSERT(0x76d8e9cd, m_freeBlocks[primaryIdx][secondaryIdx] != INVALID_BLOCK_ADDR);
	return m_freeBlocks[primaryIdx][secondaryIdx];
}

//
//	Retrieves the free block at the given Id.

template <int LogMaxN>
HK_FORCE_INLINE const typename hkcdPlanarGeometryPrimitives::Collection<LogMaxN>::Block*
	hkcdPlanarGeometryPrimitives::Collection<LogMaxN>::getFreeBlock(hkUint32 polyId) const
{
	return reinterpret_cast<const Block*>(&m_storage[polyId]);
}

template <int LogMaxN>
HK_FORCE_INLINE typename hkcdPlanarGeometryPrimitives::Collection<LogMaxN>::Block*
	hkcdPlanarGeometryPrimitives::Collection<LogMaxN>::accessFreeBlock(hkUint32 polyId)
{
	return reinterpret_cast<Block*>(&m_storage[polyId]);
}

//
//	Returns true if the previous physical block relative to the given address is free

template <int LogMaxN>
HK_FORCE_INLINE int hkcdPlanarGeometryPrimitives::Collection<LogMaxN>::isPrevPhysicalBlockFree(hkUint32 blockAddr) const
{
	// Check the last entry of the previous block
	const hkUint32 prevBlockEnd = m_storage[blockAddr - 1];
	HK_ASSERT(0x123fc8ec, prevBlockEnd & END_BLOCK_FLAG);
	return (int)(prevBlockEnd & FREE_BLOCK_FLAG);
}

//
//	Returns the size of the previous block. This function will succeed only if the block is free and assert otherwise!

template <int LogMaxN>
HK_FORCE_INLINE hkUint32 hkcdPlanarGeometryPrimitives::Collection<LogMaxN>::getPrevFreePhysicalBlockSize(hkUint32 blockAddr) const
{
	HK_ASSERT(0x393b0757, m_storage[blockAddr - 1] & END_BLOCK_FLAG);
	HK_ASSERT(0x7834c449, m_storage[blockAddr - 1] & FREE_BLOCK_FLAG);
	return m_storage[blockAddr - 2];
}

//
//	Computes the size of the current allocated block

template <int LogMaxN>
HK_FORCE_INLINE hkUint32 hkcdPlanarGeometryPrimitives::Collection<LogMaxN>::computeBlockSize(hkUint32 blockAddr) const
{
	hkUint32 nextBlockAddr = blockAddr;
	while ( !(m_storage[nextBlockAddr++] & END_BLOCK_FLAG) ) {}
	return nextBlockAddr - blockAddr;
}

//
//	Computes the payload size of the given allocated block

template <int LogMaxN>
HK_FORCE_INLINE hkUint32 hkcdPlanarGeometryPrimitives::Collection<LogMaxN>::computePayloadSize(hkUint32 blockAddr) const
{
	hkUint32 nextBlockAddr = blockAddr;
	while ( !(m_storage[nextBlockAddr++] & END_PAYLOAD_FLAG) ) {}
	return nextBlockAddr - blockAddr;
}

//
//	Expands the available storage by at least the requested size. Returns the id of the free block

template <int LogMaxN>
HK_FORCE_INLINE void hkcdPlanarGeometryPrimitives::Collection<LogMaxN>::expandStorage(hkUint32 allocSize)
{
	// Need to grow the array
	hkUint32 blockAddr = m_storage.getSize() - MIN_BLOCK_SIZE;
	m_storage.setSize(blockAddr);								// Remove last guard block
	m_storage.setSize(blockAddr + allocSize + MIN_BLOCK_SIZE, 0);
	m_storage.setSize(m_storage.getCapacity(), 0);				// Take advantage of all the allocated space
	const hkUint32 lastAddr	= m_storage.getSize() - MIN_BLOCK_SIZE;
	const hkUint32 freeSize	= lastAddr - blockAddr;

	// Set-up the blocks
	Block* freeBlock	= accessFreeBlock(blockAddr);
	Block* lastBlock	= accessFreeBlock(lastAddr);

	// Configure blocks
	freeBlock->setSize(freeSize);			lastBlock->setSize(MIN_BLOCK_SIZE);
	freeBlock->setFree();					lastBlock->setAllocated();
	freeBlock->setNextBlockAddress(0);		lastBlock->setNextBlockAddress(0);
	freeBlock->setPrevBlockAddress(0);		lastBlock->setPrevBlockAddress(0);

	// Try to merge with the previous block
	if ( isPrevPhysicalBlockFree(blockAddr) )
	{
		// Get previous block
		const hkUint32 prevBlockSize	= getPrevFreePhysicalBlockSize(blockAddr);
		const hkUint32 prevBlockAddr	= blockAddr - prevBlockSize;
		Block* prevBlock		= accessFreeBlock(prevBlockAddr);
		HK_ASSERT(0x17d33011, prevBlock->isFree());						// Prev block is not free though marked as such!
		HK_ASSERT(0x13f3a389, prevBlock->getSize() == prevBlockSize);	// Make sure the block size matches ours!

		// Remove previous block from the free lists
		hkUint32 primaryIdx, secondaryIdx;
		computeMapIndicesSearch(prevBlockSize, primaryIdx, secondaryIdx);
		remove(prevBlockAddr, primaryIdx, secondaryIdx);

		// Remove all start & end block markers from the two blocks
		m_storage[blockAddr - 1] = m_storage[blockAddr] = 0;

		// Configure prevBlock to expand over the newly allocated block
		prevBlock->setSize(prevBlockSize + freeSize);
		prevBlock->setFree();
		prevBlock->setNextBlockAddress(0);
		prevBlock->setPrevBlockAddress(0);

		blockAddr = prevBlockAddr;
	}

	// Insert the block into the free list
	insert(blockAddr);
}

//
//	Allocates a polygon having the given number of boundary planes

template <int LogMaxN>
hkUint32 hkcdPlanarGeometryPrimitives::Collection<LogMaxN>::blockAlloc(hkUint32& allocSizeOut)
{
	// Search for a big enough free block
	const hkUint32 allocSize = allocSizeOut;
	hkUint32 primaryIdx = 0, secondaryIdx = 0;
	computeMapIndicesAlloc(allocSize, primaryIdx, secondaryIdx);
	hkUint32 blockAddr = searchForSuitableBlock(primaryIdx, secondaryIdx);

	// Expand storage if necessary
	if ( blockAddr == INVALID_BLOCK_ADDR )
	{
		const hkUint32 M			= (primaryIdx + LOG_MIN_BLOCK_SIZE);
		const hkUint32 G			= hkMath::min2<hkUint32, hkUint32>(primaryIdx, LOG_MAX_DIVISIONS);
		const hkUint32 expandSize	= (1 << M) + secondaryIdx * (1 << (M - G));
		HK_ASSERT(0x37195836, expandSize >= allocSize);

		expandStorage(expandSize);
		blockAddr = searchForSuitableBlock(primaryIdx, secondaryIdx);
	}

	// We found a block, mark it as used
	HK_ASSERT(0x47d308b8, blockAddr != INVALID_BLOCK_ADDR);

	// Get block
	Block* block		= accessFreeBlock(blockAddr);
	const hkUint32 blockSize	= block->getSize();
	HK_ASSERT(0x330d9364, blockSize >= allocSize);

	// Remove it from the free list
	remove(blockAddr, primaryIdx, secondaryIdx);
	HK_ASSERT(0x2932123a, block->isFree());

	// Trim any trailing free block space at the end of block
	allocSizeOut = blockSize;
	if ( blockSize >= allocSize + MIN_BLOCK_SIZE )
	{
		// Calculate the amount of space left in the remaining block.
		const hkUint32 remainingSize		= blockSize - allocSize;
		const hkUint32 remainingBlockAddr	= blockAddr + allocSize;
		Block* remainingBlock		= accessFreeBlock(remainingBlockAddr);

		// Configure blocks
		block->setSize(allocSize);
		remainingBlock->setSize(remainingSize);
		remainingBlock->setFree();
		remainingBlock->setNextBlockAddress(0);
		remainingBlock->setPrevBlockAddress(0);

		// Insert the remaining block into the free list
		allocSizeOut = allocSize;
		insert(remainingBlockAddr);
	}

	// Mark the block as allocated
	block->setAllocated();
	return blockAddr;
}

//
//	Creates the collection with the given initial size

template <int LogMaxN>
void hkcdPlanarGeometryPrimitives::Collection<LogMaxN>::create(int initialFreeSize)
{
	// Alloc storage
	m_storage.setSize(0);
	m_storage.setSize((MIN_BLOCK_SIZE << 1) + initialFreeSize, 0);
	const hkUint32 firstBlockAddr	= 0;
	const hkUint32 midBlockAddr	= firstBlockAddr + MIN_BLOCK_SIZE;
	const hkUint32 lastBlockAddr	= midBlockAddr + initialFreeSize;

	// Initialize it. We will create two allocated blocks, marking the beginning and end of the
	// entire memory buffer.
	Block* firstBlock	= accessFreeBlock(firstBlockAddr);
	Block* midBlock		= accessFreeBlock(midBlockAddr);
	Block* lastBlock	= accessFreeBlock(lastBlockAddr);

	// Configure blocks
	firstBlock->setSize(MIN_BLOCK_SIZE);	midBlock->setSize(initialFreeSize);	lastBlock->setSize(MIN_BLOCK_SIZE);
	firstBlock->setAllocated();				midBlock->setFree();				lastBlock->setAllocated();
	firstBlock->setNextBlockAddress(0);		midBlock->setNextBlockAddress(0);	lastBlock->setNextBlockAddress(0);
	firstBlock->setPrevBlockAddress(0);		midBlock->setPrevBlockAddress(0);	lastBlock->setPrevBlockAddress(0);

	// Insert the midBlock into the free lists
	insert(midBlockAddr);
}

//
//	Deallocates all polygons

template <int LogMaxN>
void hkcdPlanarGeometryPrimitives::Collection<LogMaxN>::clear()
{
	// We will create two allocated blocks, marking the beginning and end of the entire memory buffer.
	m_storage.setSize(0);
	m_storage.setSize((MIN_BLOCK_SIZE << 1), 0);
	Block* firstBlock	= accessFreeBlock(0);
	Block* lastBlock	= accessFreeBlock(MIN_BLOCK_SIZE);

	// Configure blocks
	firstBlock->setSize(MIN_BLOCK_SIZE);	lastBlock->setSize(MIN_BLOCK_SIZE);
	firstBlock->setAllocated();				lastBlock->setAllocated();
	firstBlock->setNextBlockAddress(0);		lastBlock->setNextBlockAddress(0);
	firstBlock->setPrevBlockAddress(0);		lastBlock->setPrevBlockAddress(0);

	// No free blocks
	m_primaryBitmap	= 0;
	for (int i = 0; i < NUM_SECONDARY_BMPS; i++)
	{
		m_secondaryBitmaps[i] = 0;
		for (int j = 0; j < MAX_DIVISIONS; j++)
		{
			m_freeBlocks[i][j] = INVALID_BLOCK_ADDR;
		}
	}
}

//
//	Copies the given polygon collection over this

template <int LogMaxN>
void hkcdPlanarGeometryPrimitives::Collection<LogMaxN>::copy(const Collection& other)
{
	// Copy storage
	m_storage.setSize(0);
	m_storage.append(other.m_storage);

	// Copy bitmaps and free lists
	m_primaryBitmap	= other.m_primaryBitmap;
	for (int i = 0; i < NUM_SECONDARY_BMPS; i++)
	{
		m_secondaryBitmaps[i] = other.m_secondaryBitmaps[i];
		for (int j = 0; j < MAX_DIVISIONS; j++)
		{
			m_freeBlocks[i][j] = other.m_freeBlocks[i][j];
		}
	}
}

//
//	Frees the given polygon

template <int LogMaxN>
HK_FORCE_INLINE void hkcdPlanarGeometryPrimitives::Collection<LogMaxN>::blockFree(hkUint32 blockAddr)
{
	// Get the polygon and compute the payload size
	HK_ASSERT(0x72e86d4, blockAddr != INVALID_BLOCK_ADDR);
	blockFree(blockAddr, computePayloadSize(blockAddr));
}

template <int LogMaxN>
void hkcdPlanarGeometryPrimitives::Collection<LogMaxN>::blockFree(hkUint32 blockAddr, hkUint32 payloadLen)
{
	// Clear the end plane marker
	HK_ASSERT(0x72e86d4, blockAddr != INVALID_BLOCK_ADDR);
	HK_ASSERT(0x7096791d, m_storage[blockAddr + payloadLen - 1] & END_PAYLOAD_FLAG);
	m_storage[blockAddr + payloadLen - 1] &= ~END_PAYLOAD_FLAG;

	// Get block and compute its size
	Block* block	= accessFreeBlock(blockAddr);
	hkUint32 blockSize	= computeBlockSize(blockAddr);
	HK_ASSERT(0xf8ee515, block->isAllocated());

	// Init block
	block->setSize(blockSize);
	block->setFree();
	block->setNextBlockAddress(0);
	block->setPrevBlockAddress(0);

	// Try to merge with the previous block
	if ( isPrevPhysicalBlockFree(blockAddr) )
	{
		// Get previous block
		const hkUint32 prevBlockSize	= getPrevFreePhysicalBlockSize(blockAddr);
		const hkUint32 prevBlockAddr	= blockAddr - prevBlockSize;
		Block* prevBlock		= accessFreeBlock(prevBlockAddr);
		HK_ASSERT(0x305ef864, prevBlock->isFree());						// Prev block is not free though marked as such!
		HK_ASSERT(0x3ccde7ed, prevBlock->getSize() == prevBlockSize);	// Make sure the block size matches ours!

		// Remove previous block from the free lists
		hkUint32 primaryIdx, secondaryIdx;
		computeMapIndicesSearch(prevBlockSize, primaryIdx, secondaryIdx);
		remove(prevBlockAddr, primaryIdx, secondaryIdx);

		// Remove all start & end block markers from the two blocks
		m_storage[blockAddr - 1] = m_storage[blockAddr] = 0;

		// Configure prevBlock to expand over the newly allocated block
		prevBlock->setSize(prevBlockSize + blockSize);
		prevBlock->setFree();
		prevBlock->setNextBlockAddress(0);
		prevBlock->setPrevBlockAddress(0);

		blockSize  += prevBlockSize;
		blockAddr	= prevBlockAddr;
		block		= accessFreeBlock(blockAddr);
	}

	//	Try to merge with the next block
	const hkUint32 nextBlockAddr	= blockAddr + blockSize;
	Block* nextBlock		= accessFreeBlock(nextBlockAddr);
	if ( nextBlock->isFree() )
	{
		// Get next block size
		const hkUint32 nextBlockSize = nextBlock->getSize();

		// Remove previous block from the free lists
		hkUint32 primaryIdx, secondaryIdx;
		computeMapIndicesSearch(nextBlockSize, primaryIdx, secondaryIdx);
		remove(nextBlockAddr, primaryIdx, secondaryIdx);

		// Remove all start & end block markers from the two blocks
		m_storage[nextBlockAddr - 1] = m_storage[nextBlockAddr] = 0;

		// Configure prevBlock to expand over the newly allocated block
		block->setSize(blockSize + nextBlockSize);
		block->setFree();
		block->setNextBlockAddress(0);
		block->setPrevBlockAddress(0);
	}

	// Insert into the free list
	insert(blockAddr);
}

//
//	Returns the next allocated block address

template <int LogMaxN>
HK_FORCE_INLINE hkUint32 hkcdPlanarGeometryPrimitives::Collection<LogMaxN>::getNextAllocatedAddress(hkUint32 blockAddr) const
{
	const hkUint32 maxAddr	= m_storage.getSize() - MIN_BLOCK_SIZE;

	// Go from block to block and stop when we find something that's marked as allocated
	do
	{
		const Block* block = getFreeBlock(blockAddr);
		if ( block->isAllocated() )
		{
			while ( !(m_storage[blockAddr++] & END_BLOCK_FLAG) ) {}
		}
		else
		{
			// This is a free block, we can get the size
			const hkUint32 blockSize = block->getSize();
			blockAddr += blockSize;
		}
	} while ( (blockAddr < maxAddr) && getFreeBlock(blockAddr)->isFree() );

	return (blockAddr < maxAddr) ? blockAddr : (int)INVALID_BLOCK_ADDR;
}

//
//	Returns the previous allocated block address

template <int LogMaxN>
HK_FORCE_INLINE hkUint32 hkcdPlanarGeometryPrimitives::Collection<LogMaxN>::getPrevAllocatedAddress(int blockAddr) const
{
	// Go from block to block and stop when we find something that's marked as allocated
	do
	{
		if ( isPrevPhysicalBlockFree((hkUint32)blockAddr) )
		{
			// The previous block is free, we can get its size
			const hkUint32 prevBlockSize = getPrevFreePhysicalBlockSize(blockAddr);
			blockAddr -= prevBlockSize;
		}
		else
		{
			HK_ASSERT(0x6e94f2a8, blockAddr >= MIN_BLOCK_SIZE);
			HK_ASSERT(0x68cbaab2, m_storage[blockAddr - 1] & END_BLOCK_FLAG);
			blockAddr -= 2;	// This is the end block marker of the prev block
			while ( !((blockAddr < INVALID_BLOCK_ADDR) || (m_storage[blockAddr] & END_BLOCK_FLAG)) )
			{
				blockAddr--;
			}
			HK_ASSERT(0x40a06a2d, (blockAddr < INVALID_BLOCK_ADDR) || (m_storage[blockAddr] & END_BLOCK_FLAG));
			blockAddr++;
		}
	} while ( (blockAddr > INVALID_BLOCK_ADDR) && getFreeBlock(blockAddr)->isFree() );

	return blockAddr;
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
