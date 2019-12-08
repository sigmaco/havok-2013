/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKBASE_SET_H
#define HKBASE_SET_H

template <typename T, typename Allocator=hkContainerHeapAllocator, typename Ops=hkMapOperations<T> >
class hkSet
{
friend class hkTrackerSetLayoutHandler;

public:

	HK_DECLARE_REFLECTION();
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_MAP, hkSet );

	typedef hkSet<T,hkContainerTempAllocator> Temp;
	typedef hkSet<T,hkContainerDebugAllocator> Debug;
	typedef hkSet<T,hkContainerHeapAllocator> Heap;

	/// Iterator type.
	/// All iterators are invalidated after a mutating operation, i.e., insertion, removal.
	typedef class Dummy* Iterator;
#		define HK_MAP_INDEX_TO_ITERATOR(i) reinterpret_cast<Iterator>( hkUlong(i) )
#		define HK_MAP_ITERATOR_TO_INDEX(it) static_cast<int>( reinterpret_cast<hkUlong>(it) )

	/// Create an empty pointer map.
	hkSet() : m_numElems(0) {}
	hkSet( hkFinishLoadedObjectFlag f) : m_elem(f) {}

		/// Create a set initially using preallocated memory block.
		/// Use the getSizeInBytesFor(int numKeys) method to find the buffer size
		/// required for a given number of keys.
	hkSet(void* ptr, int sizeInBytes);

	/// Check whether or not the set contains the element
	HK_FORCE_INLINE hkBool32 contains(T elem) const { return isValid(findElement(elem)); }

	/// Adds the element to the set. Returns true if the elem is new, or false if it was already in the set.
	HK_FORCE_INLINE hkBool32 insert( T elem );

	///	Try to insert element. Elements are unique and cannot be -1.
	/// Returns true if the elem is new, or false if it was already in the set.
	/// If insertion fails (due to being unable to expand the table), res is set to HK_FAILURE,
	/// otherwise it is set to HK_SUCCESS.
	HK_FORCE_INLINE hkBool32 tryInsert( T elem, hkResult& res );

	/// Remove element at it. The iterator is no longer valid after this call.
	void remove( Iterator it );

	/// If element present, remove it and return HK_SUCCESS. Otherwise return HK_FAILURE.
	hkResult remove( T elem );

	/// Return the number of elements in this set.
	HK_FORCE_INLINE int getSize() const {return m_numElems; }

	/// Return the current capacity of the set.
	HK_FORCE_INLINE int getCapacity() const;

		/// Check whether or not the next insert() will trigger a resize.
	HK_FORCE_INLINE bool shouldResize() const;

	/// Get an iterator over the elements of this set.
	Iterator getIterator() const;

	/// Return the iterator associated with key or the end iterator if not present.
	inline Iterator findElement( T elem ) const;

	/// Get the element at iterator i.
	T getElement( Iterator i ) const;

	/// Get the next iterator after i.
	Iterator getNext( Iterator i ) const;

	/// Return if the iterator has reached the end.
	hkBool32 isValid( Iterator i ) const;

	/// clear the set
	void clear();

	/// Reserve space for at least numElements;
	void reserve( int numElements );

	HK_FORCE_INLINE int getHashMod() const { return m_elem.getSize() - 1; }

	/// Tries to reduce the capacity to avoid wasting storage.
	void optimizeCapacity( int numFreeElemsLeft = 0 );

		/// Calculates buffer size required to store the specified number of elements.
	static int HK_CALL getSizeInBytesFor(int numOfKeys);

		/// Calculates the desired capacity for the specified number of elements.
	static int HK_CALL getCapacityFor(int numOfKeys);

protected:
	hkResult resizeTable(int newcap);

	// Internal flags, set in constructor.
	enum
	{
		NUM_ELEMS_MASK = int(0x7FFFFFFF),
		s_minimumCapacity = 8
	};

	hkArray<T, Allocator> m_elem;
	int m_numElems; // high bits are flags

};

class hkSetUint32 : public hkSet<hkUint32>
{
public:
	HK_DECLARE_REFLECTION();
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_MAP, hkSetUint32);
	HK_FORCE_INLINE hkSetUint32() {}
	HK_FORCE_INLINE hkSetUint32(hkFinishLoadedObjectFlag flag) : hkSet<hkUint32>(flag) {}
};

struct hkIntRealPair
{
	HK_DECLARE_POD_TYPE();
	HK_DECLARE_REFLECTION();
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, hkIntRealPair);
	HK_FORCE_INLINE hkIntRealPair() {}
	HK_FORCE_INLINE hkIntRealPair(int k, hkReal v) { m_key = k; m_value = v; }
	HK_FORCE_INLINE hkIntRealPair(hkFinishLoadedObjectFlag flag) {}

	int m_key;
	hkReal m_value;
};

template <>
struct hkMapOperations<hkIntRealPair>
{
	inline static unsigned hash( const hkIntRealPair& pair, unsigned mod ) { return ((unsigned)pair.m_key * 2654435761U) & mod; }
	inline static void invalidate( hkIntRealPair& pair ) { pair.m_key = int(-1); pair.m_value = hkReal(-1); }
	inline static hkBool32 isValid( const hkIntRealPair& pair ) { return pair.m_key != int(-1); }
	inline static hkBool32 equal( const hkIntRealPair& pair0, const hkIntRealPair& pair1 ) { return pair0.m_key == pair1.m_key; }
};

class hkSetIntFloatPair: public hkSet<hkIntRealPair>
{
public:
	HK_DECLARE_REFLECTION();
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_MAP, hkSetIntFloatPair);
	HK_FORCE_INLINE hkSetIntFloatPair() {}
	HK_FORCE_INLINE hkSetIntFloatPair(hkFinishLoadedObjectFlag flag) : hkSet<hkIntRealPair>(flag) {}
};

#include <Common/Base/Container/Set/hkSet.inl>

#endif // HKBASE_HKPOINTERMAP_H

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
