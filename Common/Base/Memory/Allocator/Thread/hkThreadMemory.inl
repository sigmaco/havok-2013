/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

int hkThreadMemory::getRow(int nbytes) const
{
	#ifdef HK_DEBUG
	if (nbytes > MEMORY_MAX_SIZE_LARGE_BLOCK)
	{
		// Allocating more than the allowed maximum memory block size
		HK_BREAKPOINT(0x3);
	}
	#endif

	return (nbytes <= MEMORY_MAX_SIZE_SMALL_BLOCK)
				? int(m_small_size_to_row_lut[(nbytes + MEMORY_SMALL_BLOCK_ADD) >> MEMORY_SMALL_BLOCK_RSHIFT_BITS])
				: m_large_size_to_row_lut[ (nbytes-1) >> MEMORY_LARGE_BLOCK_RSHIFT_BITS];
}

int hkThreadMemory::rowToSize( int row ) const
{
	return m_row_to_size_lut[row];
}

int hkThreadMemory::constSizeToRow( int size )
{
#if defined(HK_REAL_IS_DOUBLE)
#define HK_LUT_OFFSET (-1)
#else
#define HK_LUT_OFFSET (0)
#endif

	HK_ASSERT(0x2a4ab5b6, size <= hkThreadMemory::MEMORY_MAX_SIZE_LARGE_BLOCK );
	HK_ASSERT(0x5dee00b2, hkThreadMemory::MEMORY_MAX_ALL_ROW == (17+HK_LUT_OFFSET));

#if !defined(HK_REAL_IS_DOUBLE)
	if (size <= 16 ) return 1;
	else
#endif
	if (size <= 32 )	return 2+HK_LUT_OFFSET;
	else if (size <= 48 )	return 3+HK_LUT_OFFSET;
	else if (size <= 64 )	return 4+HK_LUT_OFFSET;
	else if (size <= 96 )	return 5+HK_LUT_OFFSET;
	else if (size <= 128 )	return 6+HK_LUT_OFFSET;
	else if (size <= 160 )	return 7+HK_LUT_OFFSET;
	else if (size <= 192 )	return 8+HK_LUT_OFFSET;
	else if (size <= 256 )	return 9+HK_LUT_OFFSET;
	else if (size <= 320 )	return 10+HK_LUT_OFFSET;
	else if (size <= 512 )	return 11+HK_LUT_OFFSET;
	else if (size <= hkThreadMemory::MEMORY_MAX_SIZE_SMALL_BLOCK) return 12+HK_LUT_OFFSET; // end small blocks (this is especially for hkpRigidBody)
	else if (size <= 1024)	return 13+HK_LUT_OFFSET;
	else if (size <= 2048)	return 14+HK_LUT_OFFSET;
	else if (size <= 4096)	return 15+HK_LUT_OFFSET;
	else if (size <= 8192)	return 16+HK_LUT_OFFSET; // end large blocks.
	else
	{
		HK_BREAKPOINT(0);
		return -1;
	}

#undef HK_LUT_OFFSET
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
