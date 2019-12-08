/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

HK_FORCE_INLINE hkBlockStreamBase::Stream::Stream( hkBlockStreamBase::Stream::Allocator* tlAllocator, bool zeroNewBlocks) 
{ 
	initBlockStream( tlAllocator, zeroNewBlocks ); 
}

hkBlockStreamBase::Stream::~Stream()
{
	HK_ASSERT2( 0xf03454ed, m_blocks.getSize() == 0, "You must call clear before the destructor" );
}

HK_FORCE_INLINE bool hkBlockStreamBase::Stream::isEmpty() const
{
	HK_ASSERT2(0xf034dfdf, !m_isLocked, "You cannot use isEmpty() while writing to writer (call writer::finalize() first.");
	return m_numTotalElements == 0;
}

HK_FORCE_INLINE int hkBlockStreamBase::Stream::getTotalNumElems() const
{
	HK_ASSERT2( 0xf032defd, m_isLocked == false, "You cannot call this function, when non-finalized write itrators are "
												 "linked to the stream.");
	HK_ASSERT2( 0xf032defd, m_partiallyFreed == false, "You cannot call this function when some blocks are freed "
													   "by a hkBlockStream::Consumer" );
	return m_numTotalElements;
}
HK_FORCE_INLINE int hkBlockStreamBase::Stream::getTotalBytesAllocated() const
{
	return m_blocks.getSize() * sizeof(hkBlockStreamBase::Block);
}

HK_FORCE_INLINE const hkBlockStreamAllocator* hkBlockStreamBase::Stream::getAllocator() const
{ 
	return m_allocator; 
}
// These functions have a non-inlined version in the .cpp file for SPU
HK_FORCE_INLINE const hkBlockStreamBase::Block* hkBlockStreamBase::Stream::begin() const
{
	return m_blocks[0];
}

HK_FORCE_INLINE const hkBlockStreamBase::Block* hkBlockStreamBase::Stream::last() const
{
	return m_blocks[m_blocks.getSize() - 1 ];
}

// Rw versions call the const versions (which are not the same on CPU and on SPU).
HK_FORCE_INLINE hkBlockStreamBase::Block* hkBlockStreamBase::Stream::beginRw()
{
	return const_cast<Block*>(begin()); 
}

HK_FORCE_INLINE hkBlockStreamBase::Block* hkBlockStreamBase::Stream::lastRw()
{
	return const_cast<Block*>(last()); 
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
