/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#include <Common/Base/Container/BlockStream/hkBlockStreamBaseRange.h>

//
// Reader
// 

HK_FORCE_INLINE hkBlockStreamBase::Reader::Reader(){}

HK_FORCE_INLINE hkBlockStreamBase::Reader::~Reader(){}

HK_FORCE_INLINE void hkBlockStreamBase::Reader::setEmpty()
{
	m_currentByteLocation = HK_NULL;
	HK_ON_SPU( m_nextBuffer = -1);
}

HK_FORCE_INLINE int hkBlockStreamBase::Reader::getNumUnreadElementsInThisBlock() const
{	return m_numElementsToReadInThisBlock; 
}

HK_FORCE_INLINE const void* hkBlockStreamBase::Reader::advanceAndAccessNext(int thisElemSize)
{
	HK_ASSERT( 0xf034df43, m_currentBlock );
	HK_ASSERT( 0xf0347687, m_numElementsToReadInThisBlock > 0 );

	m_numElementsToReadInThisBlock		= m_numElementsToReadInThisBlock-1;

	if( m_numElementsToReadInThisBlock > 0 )
	{
		const char* nextLocation = hkAddByteOffsetConst( (const char*)m_currentByteLocation, thisElemSize );
		HK_ASSERT( 0xf06576df, nextLocation <= m_currentBlock->end() );
		m_currentByteLocation = nextLocation;
		return (const void*)nextLocation;
	}
	else
	{
		const void* data = advanceToNewBlock();
		HK_ASSERT( 0xf06576df, (const char*)m_currentByteLocation + thisElemSize <= m_currentBlock->end() );
		return data;
	}
}

HK_FORCE_INLINE const void* hkBlockStreamBase::Reader::access()
{
	return (const void*)m_currentByteLocation;
}

//
// Writer
//

HK_FORCE_INLINE hkBlockStreamBase::Writer::Writer()
{
	HK_ON_DEBUG( m_finalized    = true    );
	HK_ON_DEBUG( m_accessSize   = 0       );
	HK_ON_DEBUG( m_currentBlock = HK_NULL );

	m_blockStream = HK_NULL;
}

HK_FORCE_INLINE hkBlockStreamBase::Writer::~Writer()
{
	HK_ASSERT(0xf034dedf, m_finalized);
}

// Advance functions

HK_FORCE_INLINE void hkBlockStreamBase::Writer::advance( int numBytes )
{
	// Make sure we are exactly advancing by the size of the previous (write)access.
	HK_ASSERT( 0xf03454df, numBytes <= m_accessSize );
	HK_ON_DEBUG( m_finalized  = false );
	HK_ON_DEBUG( m_accessSize = 0     );

	int nextLocation = m_currentByteLocation + numBytes;
	int numElements  = m_currentBlockNumElems + 1;

	m_currentByteLocation  = nextLocation;
	m_currentBlockNumElems = numElements;
}

HK_FORCE_INLINE void hkBlockStreamBase::Writer::setCurrentBlockFull()
{
	if (m_currentByteLocation!=0)
	{
		m_currentByteLocation = Block::BLOCK_DATA_SIZE;
		allocateAndAccessNewBlock();
	}

	HK_ON_DEBUG(checkConsistency());
}

HK_FORCE_INLINE void* hkBlockStreamBase::Writer::reserveBytes( int numBytes )
{
	HK_ASSERT( 0xf03d3401, m_currentBlock != HK_NULL && numBytes <= Block::BLOCK_DATA_SIZE );
	HK_ON_DEBUG( m_accessSize = numBytes );
	HK_ON_DEBUG( m_finalized  = false    );

	// Make sure numBytes fit into the remaining storage space in the current block. Otherwise move to next
	// block in stream.
	int nextLocation = m_currentByteLocation + numBytes;
	if( nextLocation <= Block::BLOCK_DATA_SIZE )
	{
		return hkAddByteOffset( m_currentBlock->begin(), m_currentByteLocation );
	}
	else
	{
		return allocateAndAccessNewBlock();
	}
}

HK_FORCE_INLINE void* hkBlockStreamBase::Writer::advanceAndReserveNext( int currentNumBytes, int reservedNumBytes )
{
	advance( currentNumBytes );
	return reserveBytes( reservedNumBytes );
}

HK_FORCE_INLINE int hkBlockStreamBase::Writer::getTotalNumElems()
{
	HK_ASSERT( 0xaf13e21f, m_finalized == true );
	return m_blockStream->m_numTotalElements + m_currentBlockNumElems;
}


HK_FORCE_INLINE void hkBlockStreamBase::Writer::finalizeLastBlock(
	hkBlockStreamBase::Block* HK_RESTRICT thisBlock,
	hkBlockStreamBase::Block* HK_RESTRICT nextBlockPpu,
	int thisBlockNumElements,
	int bytesUsed
	)
{
	thisBlock->m_next = nextBlockPpu;
	//int newElements = thisBlockNumElements - thisBlock->m_numElements;
	thisBlock->setNumElements(hkBlockStreamBase::Block::CountType(thisBlockNumElements));
	thisBlock->setBytesUsed(hkBlockStreamBase::Block::CountType(bytesUsed));
	m_blockStream->m_numTotalElements += thisBlockNumElements;
}
// SPU memory management

//
// Consumer
//

HK_FORCE_INLINE const void* hkBlockStreamBase::Consumer::consumeAndAccessNext(int thisElemSize)
{
	HK_ASSERT( 0xf034df43, m_currentBlock );
	HK_ASSERT( 0xf0347687, m_numElementsToReadInThisBlock > 0 );

	int numElementsToReadInThisBlock		= m_numElementsToReadInThisBlock-1;
	const char* nextLocation = hkAddByteOffsetConst( (const char*)m_currentByteLocation, thisElemSize );	// get this here as this is the most common code path and allows the compiler to optimize better

	m_numElementsToReadInThisBlock		= numElementsToReadInThisBlock;
	if( numElementsToReadInThisBlock > 0 )
	{
		HK_ASSERT( 0xf06576df, nextLocation <= m_currentBlock->end() );
		m_currentByteLocation = nextLocation;
		return (const void*)nextLocation;
	}
	else
	{
		const void* data = freeAndAdvanceToNewBlock();
		HK_ASSERT( 0xf06576df, (const char*)m_currentByteLocation + thisElemSize <= m_currentBlock->end() );
		return data;
	}
}


HK_FORCE_INLINE hkBlockStreamBase::Block* hkBlockStreamBase::Consumer::getCurrentBlock()
{
	return const_cast<Block*>((const Block*)m_currentBlock); 
}

HK_FORCE_INLINE char* hkBlockStreamBase::Consumer::getCurrentByteLocation()
{	return const_cast<char*> ((const char*) m_currentByteLocation); 
}


//
// Modifier
//

HK_FORCE_INLINE void hkBlockStreamBase::Modifier::setToRange( const Range* HK_RESTRICT range )
{
	Reader::setToRange(range);
	HK_ON_SPU( m_writeBackBlockStartOffset = range->m_startByteLocation );
}

HK_FORCE_INLINE void hkBlockStreamBase::Modifier::setToStartOfStream( hkBlockStreamBase::Stream::Allocator* HK_RESTRICT allocator, hkBlockStreamBase::Stream* HK_RESTRICT stream, hkBlockStreamBase::Stream* streamPpu )
{
	// 	HK_ASSERT( 0xf0345dfe, !blockStream->m_isLocked );	// enable this, but writer requires a finalize()
	// 	HK_ON_DEBUG( blockStream->m_isLocked = true );
	Reader::setToStartOfStream(stream);
	HK_ON_SPU(m_writeBackBlockStartOffset = 0);
}

HK_FORCE_INLINE void* hkBlockStreamBase::Modifier::advanceAndAccessNext(int thisElemSize)
{
	HK_ASSERT( 0xf034df43, m_currentBlock );
	HK_ASSERT( 0xf0347687, m_numElementsToReadInThisBlock > 0 );

	const char* nextLocation = hkAddByteOffsetConst( (const char*)m_currentByteLocation, thisElemSize );	// get this here as this is the most common code path and allows the compiler to optimize better
	m_numElementsToReadInThisBlock		= m_numElementsToReadInThisBlock-1;

	if( m_numElementsToReadInThisBlock > 0 )
	{
		HK_ASSERT( 0xf06576df, nextLocation <= m_currentBlock->end() );
		m_currentByteLocation = nextLocation;
		return const_cast<void*>((void*)nextLocation);
	}
	else
	{
		const void* data = advanceToNewBlock(  );	// there is a special spu implementation
		HK_ASSERT( 0xf06576df, (const char*)m_currentByteLocation + thisElemSize <= m_currentBlock->end() );
		return const_cast<void*>(data);
	}
}
HK_FORCE_INLINE void* hkBlockStreamBase::Modifier::access()
{
	 return const_cast<void*>( Reader::access() );
}
HK_FORCE_INLINE hkBlockStreamBase::Block* hkBlockStreamBase::Modifier::getCurrentBlock()
{
	return const_cast<Block*>((const Block*)m_currentBlock); 
}

HK_FORCE_INLINE char* hkBlockStreamBase::Modifier::getCurrentByteLocation()
{	return const_cast<char*> ((const char*) m_currentByteLocation); 
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
