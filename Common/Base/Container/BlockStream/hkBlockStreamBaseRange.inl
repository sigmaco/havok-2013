/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#include <Common/Base/Container/BlockStream/hkBlockStreamBaseIterators.h> 
HK_FORCE_INLINE hkBool hkBlockStreamBase::Range::compareRange( const hkBlockStreamBase::Range& a, const hkBlockStreamBase::Range& b)
{
	if ( a.isEmpty() && b.isEmpty() )
	{
		return false;
	}
	if ( a.isEmpty() )
	{
		return false;
	}
	if ( b.isEmpty())
	{
		return true;
	}
	if ( a.m_startBlock->m_blockIndexInStream == b.m_startBlock->m_blockIndexInStream)
	{
		return a.m_startByteLocation < b.m_startByteLocation;
	}
	return a.m_startBlock->m_blockIndexInStream < b.m_startBlock->m_blockIndexInStream;
}

HK_FORCE_INLINE hkBlockStreamBase::Range::Range() : m_numElements(0) {}

HK_FORCE_INLINE void hkBlockStreamBase::Range::clearRange()
{
	m_startBlock  = HK_NULL;
	m_numElements = 0;
}

HK_FORCE_INLINE bool hkBlockStreamBase::Range::isEmpty() const
{
	 return m_numElements == 0; 
}

HK_FORCE_INLINE void hkBlockStreamBase::Range::setStartPoint(const hkBlockStreamBase::Writer* HK_RESTRICT writer)
{
	Block* currentBlock						= writer->m_currentBlock;
	Block::CountType startByteLocation		= Block::CountType(writer->m_currentByteLocation);
	Block::CountType startBlockNumElements	= Block::CountType(writer->m_currentBlockNumElems);
	int numElements							= -(writer->m_blockStream->m_numTotalElements + writer->m_currentBlockNumElems);

	HK_ASSERT(0x5a000196, startBlockNumElements < 0x1000 );

	m_startBlock			= currentBlock;
	m_startByteLocation		= startByteLocation;
	m_startBlockNumElements	= startBlockNumElements;
	m_numElements			= numElements;
}

HK_FORCE_INLINE void hkBlockStreamBase::Range::setStartPointExclusive(hkBlockStreamBase::Writer* HK_RESTRICT it)
{
	it->setCurrentBlockFull();
	setStartPoint(it);
}

HK_FORCE_INLINE void hkBlockStreamBase::Range::setEndPointExclusive(hkBlockStreamBase::Writer* HK_RESTRICT it)
{
	it->setCurrentBlockFull();
	setEndPoint(it);
}

HK_FORCE_INLINE void hkBlockStreamBase::Range::setEntireStream(hkBlockStreamBase::Stream* HK_RESTRICT stream )
{
	bool empty = stream->isEmpty();
	m_startBlock = (!empty)? stream->beginRw(): HK_NULL;
	m_startByteLocation = 0;
	m_startBlockNumElements = (!empty)? Block::CountType(m_startBlock->getNumElements()) : 0;
	m_numElements = stream->getTotalNumElems();
}





hkBlockStreamBase::LinkedRange::LinkedRange():Range(), m_next(HK_NULL){}

template<typename T>
HK_FORCE_INLINE void hkBlockStreamBase::LinkedRange::appendPersistentRange( T* range )
{
	HK_ASSERT2( 0xf0ed3454, range->m_numElements, "You can only append non empty ranges" );
	HK_ASSERT2( 0xeeed3454, range->m_next == HK_NULL, "You can only append ranges that are not linked" );

	// If the current range is already empty we can re-use it...
	if ( m_numElements == 0 )
	{
		HK_ASSERT2( 0xeeed3454, m_next == HK_NULL, "You cannot append empty ranges" );
		*((T*) this) = *range;
		return;
	}

	// ... otherwise we insert the new range after the current one.
	range->m_next = m_next;
	m_next = range;
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
