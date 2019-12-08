/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_SHAPE_KEY_TABLE_H
#define HKP_SHAPE_KEY_TABLE_H


	/// A table of shape keys designed for quick lookup and SPU support.
class hkpShapeKeyTable
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_SHAPE, hkpShapeKeyTable );
		HK_DECLARE_REFLECTION();

		enum
		{
			NUM_LISTS = 32,
			NUM_SLOTS_PER_BLOCK = 63	
		};

		// A block of shape key slots.
		// Free slots have a value of HK_INVALID_SHAPEKEY.
		struct Block
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_SHAPE, hkpShapeKeyTable::Block );
			HK_DECLARE_REFLECTION();

			Block();
			~Block();

			HK_ALIGN16( hkpShapeKey m_slots[NUM_SLOTS_PER_BLOCK] );
			Block* m_next;
		};

		enum
		{
			NUM_BYTES_PER_BLOCK = sizeof(Block)
		};

	public:

		hkpShapeKeyTable();
		hkpShapeKeyTable( class hkFinishLoadedObjectFlag flag );
		~hkpShapeKeyTable();

			/// Add a shape key to the table, if not already present
		void insert( hkpShapeKey key );

			/// Remove a shape key from the table, if present
		void remove( hkpShapeKey key );

			/// Check if a shape key exists in the table
		bool exists( hkpShapeKey key ) const;

			/// Returns true if the table is empty
		bool isEmpty() const { return (m_occupancyBitField == 0); }

			/// Empty the table
		void clear();

			// Get number of keys per list (for debugging)
		void getDistribution( hkArray<int>& counts ) const;

	protected:

			// Pointer to fixed size array of linked list heads.
			// Keys are assigned to the lists using a hash function.
		Block* m_lists;

			// Bitfield indicating whether each list has any used slots.
			// Provides an early out from the list lookup.
		hkUint32 m_occupancyBitField;
};

#endif //HKP_SHAPE_KEY_TABLE_H

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
