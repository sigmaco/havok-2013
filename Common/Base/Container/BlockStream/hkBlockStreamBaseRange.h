/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#ifndef HK_BLOCKSTREAM_RANGE_H
#define HK_BLOCKSTREAM_RANGE_H

#include <Common/Base/Container/BlockStream/hkBlockStreamBaseBlock.h>

namespace hkBlockStreamBase
{
	class Writer;

	/// A range in a stream.
	/// Ranges are pointing to blocks and not to block streams, so a range will still
	/// be valid if a block stream gets appended to another one
	class Range
	{
		public:

			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE, Range );

			/// Default constructor, initializes an empty range.
			HK_FORCE_INLINE	Range();

			/// Resets the range to an empty range.
			HK_FORCE_INLINE	void clearRange();

			/// Returns true if the range is empty (equivalent to getNumElements() == 0 ).
			HK_FORCE_INLINE bool isEmpty() const; 

			/// Returns the number of elements in the range.
			HK_FORCE_INLINE int  getNumElements() const { return m_numElements; }

			/// Sets the starting point of the range to the block pointed by the given Writer.
			HK_FORCE_INLINE void setStartPoint( const Writer* HK_RESTRICT it );

			/// Sets the end point of the range to be the block pointed by the given Writer.
			void setEndPoint( const Writer* HK_RESTRICT it );

			// Use the next functions to create exclusive ranges.
			// A range is exclusive if it doesn't share any blocks with other ranges.

			/// Sets the range to start at the block pointed by the given Writer and make it exclusive.
			HK_FORCE_INLINE void setStartPointExclusive( Writer* HK_RESTRICT it );

			/// Sets the end point of the range to be the block pointed by the given Writer and make it exclusive.
			HK_FORCE_INLINE	void setEndPointExclusive( Writer* HK_RESTRICT it );

			//HK_FORCE_INLINE void setEmpty() { clearRange(); }

			/// Set a range to cover a whole stream.
			HK_ON_CPU( HK_FORCE_INLINE void setEntireStream( Stream* HK_RESTRICT stream ) );

			/// Compares two ranges, useful for sorting.
			static HK_FORCE_INLINE hkBool compareRange ( const Range& a, const Range& b);

	public:

			/// A pointer to the block that holds the first element of THIS range.
			HK_ALIGN16(Block* m_startBlock);

			/// The offset of the first element inside the start block (m_startBlock).
			Block::CountType m_startByteLocation;

			/// The number of elements in the first block. 
			/// Note: when setStartPoint() is called this is the start element index in the start block.
			Block::CountType m_startBlockNumElements;

			/// The length of THIS range (i.e. the number of elements in THIS range).
			/// Note: this value is actually negative when not fully initialized.
			int m_numElements;
	};

	class LinkedRange : public Range
	{
		public:

			HK_FORCE_INLINE	LinkedRange();
			
			/// Append another range to this. The range MUST be persistent in memory as it will be referenced by this.
			HK_ON_CPU( template<typename T> HK_FORCE_INLINE void appendPersistentRange( T* HK_RESTRICT range ); );
			
			/// Append another range to this. The range MUST be persistent in memory as it will be referenced by this.
			/// rangeSpu is the range that will be appended, and rangePpu is the persistent address to which 
			/// the appended range (rangeSpu) should be DMA'd by the caller before or after calling this function.
			HK_ON_SPU( template<typename T> HK_FORCE_INLINE void appendPersistentRangeSpu( T* HK_RESTRICT rangeSPU, T* HK_RESTRICT rangePpu); );

			HK_FORCE_INLINE	void clearRange()
			{
				Range::clearRange();
				m_next = HK_NULL;
			}

		public:

			/// A pointer to the next range if several ranges have been linked.
			/// Note: that next range is completely independent of THIS range, i.e. m_numElements does not cross
			/// any range boundaries.
			LinkedRange*	m_next;	
	};

}
#include <Common/Base/Container/BlockStream/hkBlockStreamBaseRange.inl>
#endif //HK_BLOCKSTREAM_RANGE_H

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
