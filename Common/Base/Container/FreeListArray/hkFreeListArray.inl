/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */



#include <Common/Base/Container/BitField/hkBitField.h>


// Constructor.
template < typename VALUE_TYPE, typename INDEX_TYPE, int GROWTH, typename OPERATIONS >
HK_FORCE_INLINE hkFreeListArray<VALUE_TYPE, INDEX_TYPE, GROWTH, OPERATIONS>::hkFreeListArray() : m_firstFree(-1) 
{ }


// Destructor
template < typename VALUE_TYPE, typename INDEX_TYPE, int GROWTH, typename OPERATIONS >
HK_FORCE_INLINE hkFreeListArray<VALUE_TYPE, INDEX_TYPE, GROWTH, OPERATIONS>::~hkFreeListArray()
{
	clear();
}

// Copies the list
template < typename VALUE_TYPE, typename INDEX_TYPE, int GROWTH, typename OPERATIONS >
HK_FORCE_INLINE void hkFreeListArray<VALUE_TYPE, INDEX_TYPE, GROWTH, OPERATIONS>::copy(const hkFreeListArray& other)
{
	m_elements.setSize(0);
	m_elements.append(other.m_elements);
	m_firstFree = other.m_firstFree;
}


// Clear the free list
template < typename VALUE_TYPE, typename INDEX_TYPE, int GROWTH, typename OPERATIONS >
HK_FORCE_INLINE void hkFreeListArray<VALUE_TYPE, INDEX_TYPE, GROWTH, OPERATIONS>::clear()
{
	hkTraitBool<OperationsImplementIsEmpty::VALUE> hasIsEmpty;
	_clear(hasIsEmpty);
}

template < typename VALUE_TYPE, typename INDEX_TYPE, int GROWTH, typename OPERATIONS >
HK_FORCE_INLINE void hkFreeListArray<VALUE_TYPE, INDEX_TYPE, GROWTH, OPERATIONS>::_clear(CanNotCheckForEmpty notUsed)
{
	// Traverse free list keeping track of free elements
	hkBitField::Stack isElementFree(m_elements.getSize(), 0);	
	while (m_firstFree != -1)
	{
		isElementFree.set(m_firstFree);
		m_firstFree = OPERATIONS::getNext((VALUE_TYPE&)m_elements[m_firstFree]);
	}

	// Call destructor in elements that are allocated
	for (int i = 0; i < isElementFree.getSize(); ++i)
	{
		if (!isElementFree.get(i))
		{
			((VALUE_TYPE&)m_elements[i]).~VALUE_TYPE();
		}
	}

	m_elements.clear();
}

template < typename VALUE_TYPE, typename INDEX_TYPE, int GROWTH, typename OPERATIONS >
HK_FORCE_INLINE void hkFreeListArray<VALUE_TYPE, INDEX_TYPE, GROWTH, OPERATIONS>::_clear(CanCheckForEmpty notUsed)
{
	// Call destructor in elements that are allocated
	for (int i = 0; i < m_elements.getSize(); ++i)
	{
		VALUE_TYPE& element = ((VALUE_TYPE&)m_elements[i]);
		if (!OPERATIONS::isEmpty(element))
		{
			element.~VALUE_TYPE();
		}
	}

	m_elements.clear();
}

template < typename VALUE_TYPE, typename INDEX_TYPE, int GROWTH, typename OPERATIONS >
HK_FORCE_INLINE void hkFreeListArray<VALUE_TYPE, INDEX_TYPE, GROWTH, OPERATIONS>::grow(int growth)
{
	const int oldCapacity	= m_elements.getSize();
	const int newCapacity	= hkMath::max2(oldCapacity + growth, oldCapacity ? (oldCapacity << 1) : 1);	// Double the capacity if negative growth provided!
	growth					= newCapacity - oldCapacity;
	m_elements.reserveExactly(newCapacity);
	m_elements.expandByUnchecked(growth);

	for (int i = oldCapacity, last = newCapacity - 1; i <= last; ++i)
	{
		VALUE_TYPE& element = operator[](INDEX_TYPE(i));			
		OPERATIONS::setEmpty(element, (i < last ? i + 1 : m_firstFree));
	}
	m_firstFree	= oldCapacity;
}


// Allocate one element, call VALUE_TYPE ctor.
template < typename VALUE_TYPE, typename INDEX_TYPE, int GROWTH, typename OPERATIONS >
HK_FORCE_INLINE INDEX_TYPE hkFreeListArray<VALUE_TYPE, INDEX_TYPE, GROWTH, OPERATIONS>::allocate()
{
	if (m_firstFree < 0)
	{		
		grow();
	}

	hkUint32 elementIndex = m_firstFree;
	VALUE_TYPE&	element = operator[](INDEX_TYPE(elementIndex));
	m_firstFree = OPERATIONS::getNext(element);
	::new (reinterpret_cast<hkPlacementNewArg*>(&element)) VALUE_TYPE();
	return INDEX_TYPE(elementIndex);
}

template < typename VALUE_TYPE, typename INDEX_TYPE, int GROWTH, typename OPERATIONS >
HK_FORCE_INLINE INDEX_TYPE hkFreeListArray<VALUE_TYPE, INDEX_TYPE, GROWTH, OPERATIONS>::allocate(const VALUE_TYPE& valueToCopy)
{
	if (m_firstFree < 0)
	{
		grow();
	}

	hkUint32 elementIndex = m_firstFree;
	VALUE_TYPE&	element = operator[](INDEX_TYPE(elementIndex));
	m_firstFree = OPERATIONS::getNext(element);
	::new (reinterpret_cast<hkPlacementNewArg*>(&element)) VALUE_TYPE(valueToCopy);
	return INDEX_TYPE(elementIndex);
}


// Release one element, call VALUE_TYPE dtor.
template < typename VALUE_TYPE, typename INDEX_TYPE, int GROWTH, typename OPERATIONS >
HK_FORCE_INLINE void hkFreeListArray<VALUE_TYPE, INDEX_TYPE, GROWTH, OPERATIONS>::release(INDEX_TYPE index)
{
	VALUE_TYPE&	element = operator[](index);
	element.~VALUE_TYPE();	
	OPERATIONS::setEmpty(element, m_firstFree);	
	m_firstFree = index.value();
}


// Compact the storage.
template < typename VALUE_TYPE, typename INDEX_TYPE, int GROWTH, typename OPERATIONS >
HK_FORCE_INLINE void hkFreeListArray<VALUE_TYPE, INDEX_TYPE, GROWTH, OPERATIONS>::compact()
{
	m_elements.optimizeCapacity(0, true);
	m_firstFree = -1;
}

//
//	Swaps the storage with the given array

template < typename VALUE_TYPE, typename INDEX_TYPE, int GROWTH, typename OPERATIONS >
HK_FORCE_INLINE void hkFreeListArray<VALUE_TYPE, INDEX_TYPE, GROWTH, OPERATIONS>::swapStorage(hkArray<VALUE_TYPE>& newStorage)
{
	m_elements.swap((hkArray<ElementAsPod>&)newStorage);
}



// Read-only indexed access.
template < typename VALUE_TYPE, typename INDEX_TYPE, int GROWTH, typename OPERATIONS >
HK_FORCE_INLINE	const VALUE_TYPE& hkFreeListArray<VALUE_TYPE, INDEX_TYPE, GROWTH, OPERATIONS>::operator[](INDEX_TYPE index) const
{	
	return (const VALUE_TYPE&) m_elements[index.value()];
}


// Read-write indexed access.
template < typename VALUE_TYPE, typename INDEX_TYPE, int GROWTH, typename OPERATIONS >
HK_FORCE_INLINE	VALUE_TYPE& hkFreeListArray<VALUE_TYPE, INDEX_TYPE, GROWTH, OPERATIONS>::operator[](INDEX_TYPE index)			
{
	return const_cast<VALUE_TYPE&>(const_cast<const ThisType&>(*this).operator[](index));	
}


// Check if a given ID is allocated.
template < typename VALUE_TYPE, typename INDEX_TYPE, int GROWTH, typename OPERATIONS >
HK_FORCE_INLINE hkBool32 hkFreeListArray<VALUE_TYPE, INDEX_TYPE, GROWTH, OPERATIONS>::isAllocated(INDEX_TYPE index) const
{
	hkTraitBool<OperationsImplementIsEmpty::VALUE> hasIsEmpty;
	return _isAllocated(index, hasIsEmpty);
}

template < typename VALUE_TYPE, typename INDEX_TYPE, int GROWTH, typename OPERATIONS >
HK_FORCE_INLINE hkBool32 hkFreeListArray<VALUE_TYPE, INDEX_TYPE, GROWTH, OPERATIONS>::isFull() const
{
	return m_firstFree == -1;
}

template < typename VALUE_TYPE, typename INDEX_TYPE, int GROWTH, typename OPERATIONS >
HK_FORCE_INLINE hkBool32 hkFreeListArray<VALUE_TYPE, INDEX_TYPE, GROWTH, OPERATIONS>::_isAllocated(INDEX_TYPE index, 
																								   CanNotCheckForEmpty notUsed) const
{
	hkInt32 c = m_firstFree;
	while (c >= 0)
	{
		if (c == index.value()) return 0;
		c = OPERATIONS::getNext((VALUE_TYPE&)m_elements[c]);
	}
	return 1;
}

template < typename VALUE_TYPE, typename INDEX_TYPE, int GROWTH, typename OPERATIONS >
HK_FORCE_INLINE hkBool32 hkFreeListArray<VALUE_TYPE, INDEX_TYPE, GROWTH, OPERATIONS>::_isAllocated(INDEX_TYPE index, 
																								   CanCheckForEmpty notUsed) const
{
	return !OPERATIONS::isEmpty(operator[](index));
}


// Get the capacity of the free list.
template < typename VALUE_TYPE, typename INDEX_TYPE, int GROWTH, typename OPERATIONS >
HK_FORCE_INLINE int hkFreeListArray<VALUE_TYPE, INDEX_TYPE, GROWTH, OPERATIONS>::getCapacity() const
{ 
	return m_elements.getSize(); 
}


// Get the storage buffer address.
template < typename VALUE_TYPE, typename INDEX_TYPE, int GROWTH, typename OPERATIONS >
HK_FORCE_INLINE const VALUE_TYPE* hkFreeListArray<VALUE_TYPE, INDEX_TYPE, GROWTH, OPERATIONS>::getBuffer() const
{ 
	return (const VALUE_TYPE*) m_elements.begin(); 
}


// Get the end index of the free list.
template < typename VALUE_TYPE, typename INDEX_TYPE, int GROWTH, typename OPERATIONS >
HK_FORCE_INLINE INDEX_TYPE hkFreeListArray<VALUE_TYPE, INDEX_TYPE, GROWTH, OPERATIONS>::getMaxIndex() const
{ 
	return INDEX_TYPE(getCapacity()); 
}


// Get an read-only element from its index using software cache on if called from an SPU.
template < typename VALUE_TYPE, typename INDEX_TYPE, int GROWTH, typename OPERATIONS >
HK_FORCE_INLINE	const VALUE_TYPE& hkFreeListArray<VALUE_TYPE, INDEX_TYPE, GROWTH, OPERATIONS>::getAtWithCache(INDEX_TYPE index) const
{ 		
	return operator[](index);
}


// Get a read-only access to the underlying storage.
template < typename VALUE_TYPE, typename INDEX_TYPE, int GROWTH, typename OPERATIONS >
HK_FORCE_INLINE const hkArray<VALUE_TYPE>& hkFreeListArray<VALUE_TYPE, INDEX_TYPE, GROWTH, OPERATIONS>::getStorage() const
{ 
	return (const hkArray<VALUE_TYPE>&)m_elements;
}


template < typename VALUE_TYPE, typename INDEX_TYPE, int GROWTH, typename OPERATIONS >
HK_FORCE_INLINE	hkFreeListArray<VALUE_TYPE, INDEX_TYPE, GROWTH, OPERATIONS>::Iterator::Iterator( const ThisType& fla )
:	m_freeListArray( fla ),
	m_index( -1 )
{
	next();
}

template < typename VALUE_TYPE, typename INDEX_TYPE, int GROWTH, typename OPERATIONS >
HK_FORCE_INLINE	void hkFreeListArray<VALUE_TYPE, INDEX_TYPE, GROWTH, OPERATIONS>::Iterator::next()
{
	const int max = m_freeListArray.getCapacity();
	while( ++m_index < max )
	{
		// Require OPERATIONS::isEmpty() to be implemented, otherwise don't compile
		if( m_freeListArray._isAllocated( INDEX_TYPE(m_index), hkTraitBool<true>() ) )
		{
			return;
		}
	}
	m_index = -1;
}

template < typename VALUE_TYPE, typename INDEX_TYPE, int GROWTH, typename OPERATIONS >
HK_FORCE_INLINE	bool hkFreeListArray<VALUE_TYPE, INDEX_TYPE, GROWTH, OPERATIONS>::Iterator::isValid() const
{
	return m_index != -1;
}

template < typename VALUE_TYPE, typename INDEX_TYPE, int GROWTH, typename OPERATIONS >
HK_FORCE_INLINE	INDEX_TYPE hkFreeListArray<VALUE_TYPE, INDEX_TYPE, GROWTH, OPERATIONS>::Iterator::getIndex() const
{
	return INDEX_TYPE(m_index);
}

template < typename VALUE_TYPE, typename INDEX_TYPE, int GROWTH, typename OPERATIONS >
HK_FORCE_INLINE	const VALUE_TYPE& hkFreeListArray<VALUE_TYPE, INDEX_TYPE, GROWTH, OPERATIONS>::Iterator::getValue() const
{
	return m_freeListArray[INDEX_TYPE(m_index)];
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
