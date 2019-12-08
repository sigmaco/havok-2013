/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#include <Common/Base/Thread/CriticalSection/hkCriticalSection.h>
namespace hkBlockStreamBase 
{
	HK_FORCE_INLINE Block::Block()
	{
		setHeaderToZero();
	}

	HK_FORCE_INLINE void Block::setHeaderToZero()
	{
		HK_COMPILE_TIME_ASSERT((sizeof(hkBlockStreamBase::Block) & 0xf)==0);
		HK_COMPILE_TIME_ASSERT((BLOCK_HEADER_SIZE & 0xf)==0);
		HK_COMPILE_TIME_ASSERT(HK_OFFSET_OF(Block,m_data)==BLOCK_HEADER_SIZE);
		// Make sure the two elements fit in the 'packed' variable.
		HK_COMPILE_TIME_ASSERT(sizeof(m_numElementsAndBytesUsed) >= 2 * sizeof(Block::CountType));

		hkString::memClear16( this, BLOCK_HEADER_SIZE>>4 );	// shorter code on spu
		HK_ON_DEBUG( hkString::memSet(m_data, 0xcf, BLOCK_DATA_SIZE) );
	}

	//
	// Accessors
	//

	HK_FORCE_INLINE void* Block::begin()
	{
		return m_data;
	}
	HK_FORCE_INLINE const void* Block::begin() const
	{
		return m_data;
	}

	HK_FORCE_INLINE void* Block::end()
	{ 
		return this+1;
	}
	
	HK_FORCE_INLINE const void* Block::end() const
	{ 
		return this+1;
	}

	//
	// Wrapper functions for the elements & bytes packed in the same variable.
	//

	HK_FORCE_INLINE Block::CountType Block::getNumElements() const
	{ 
		return static_cast<CountType>(m_numElementsAndBytesUsed); 
	}

	HK_FORCE_INLINE Block::CountType Block::getBytesUsed() const
	{ 
		return static_cast<CountType>( m_numElementsAndBytesUsed >> 16);
 	}

	HK_FORCE_INLINE void Block::setNumElements( CountType numElements ) 
	{ 
		m_numElementsAndBytesUsed = ( (m_numElementsAndBytesUsed & 0xffff0000) | (static_cast<hkUint32>(numElements)) );
	}

	HK_FORCE_INLINE void Block::setBytesUsed( CountType numBytes )
	{ 
		m_numElementsAndBytesUsed = ( (static_cast<hkUint32>(numBytes) << 16) | (m_numElementsAndBytesUsed & 0x0000ffff ) );
	}

	HK_FORCE_INLINE void Block::atomicDecreaseElementCount( int numElementsToFree )
	{
		// We cant perform this check on SPU as the method is called with a PPU this pointer
		HK_ON_CPU(HK_ASSERT(0xab759838, getNumElements() - numElementsToFree >= 0));

		hkDmaManager::atomicExchangeAdd( &m_numElementsAndBytesUsed, hkUint32(-numElementsToFree) );
	} 

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
