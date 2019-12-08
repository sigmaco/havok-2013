/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

template <typename T, typename Allocator, typename OPS >
hkSet<T,Allocator,OPS>::hkSet(void* ptr, int sizeInBytes)
{
	int maxKeys = unsigned(sizeInBytes) / (sizeof(T)); // unsigned div = shift
	HK_ASSERT( 0x6129a7bc, maxKeys >= s_minimumCapacity );
	HK_ASSERT( 0x549309be, hkMath::isPower2(maxKeys) );

	m_elem.setDataUserFree( (T*) ptr, maxKeys, maxKeys );
	m_numElems = 0;
	HK_ASSERT( 0x549309bf, (maxKeys*hkSizeOf(T)) == sizeInBytes );

	for (int i = 0; i < maxKeys; i++)
	{
		OPS::invalidate( m_elem[i] );
	}
}

template <typename T, typename Allocator, typename OPS >
inline typename hkSet<T,Allocator,OPS>::Iterator hkSet<T,Allocator,OPS>::getIterator() const
{
	int i;
	const int hashMod = getHashMod();
	for( i = 0; i <= hashMod; ++i )
	{
		if( OPS::isValid( m_elem[i]  ) )
		{
			break;
		}
	}

	return HK_MAP_INDEX_TO_ITERATOR(i);
}

template <typename T, typename Allocator, typename OPS >
void hkSet<T,Allocator,OPS>::remove( Iterator it )
{
	int hashMod = getHashMod();

	HK_ASSERT(0x5a6d564c, isValid(it));
	HK_ASSERT(0x5a6d564d, getSize() > 0);
	unsigned i = HK_MAP_ITERATOR_TO_INDEX(it);

	// remove it
	--m_numElems;
	OPS::invalidate( m_elem[i] );

	// find lowest element of this unbroken run
	unsigned lo = ( i + hashMod ) & hashMod;
	while( OPS::isValid( m_elem[lo] ) )
	{
		lo = ( lo + hashMod ) & hashMod;
	}
	lo = ( lo + 1 ) & hashMod;

	// the slot which has become empty
	unsigned empty = i;

	// shift up, closing any gaps we find
	for(i = (i + 1) & hashMod;
		OPS::isValid( m_elem[i] ); // end of run
		i = (i + 1) & hashMod )
	{
		unsigned hash = OPS::hash( m_elem[i] , hashMod );

		// Three cases to consider here. 
		// a) The normal case where lo <= empty < i.
		// b) The case where i has wrapped around.
		// c) The case where both i and empty have wrapped around.
		// The initial case will be a. (Or b if the last slot is freed).
		// and may progress to b, and finally c.
		// The algorithm will terminate before 'i' reaches 'lo'
		// otherwise the table would have no free slots.

		// 'normal'      'i wrapped'   'i and empty wrapped'
		// ===== lo      ===== i       ===== empty
		// ===== empty   ===== lo      ===== i 
		// ===== i       ===== empty   ===== lo     


		if( ( i >= lo ) && ( hash > empty ) )
		{
			continue;					
		}
		else if( ( i < empty ) && ( hash > empty || hash <= i ) )
		{
			continue;
		}
		else if( /*i > empty && */ ( hash > empty && hash < lo ) )
		{
			continue;
		}
		HK_ASSERT(0x45e3d455,  i != empty ); // by design
		HK_ASSERT(0x5ef0d6c0,  i != lo ); // table became full?!

		// copy up
		m_elem[empty] = m_elem[i];
		// source slot is now free
		OPS::invalidate( m_elem[i] );
		empty = i;
	}
}

template <typename T, typename Allocator, typename OPS >
typename hkSet<T,Allocator,OPS>::Iterator hkSet<T,Allocator,OPS>::findElement( T key ) const
{
	const int hashMod = getHashMod();
	if( hashMod > 0 )
	{
		for( unsigned i = OPS::hash(key, hashMod);
			OPS::isValid( m_elem[i] );	
			i = (i+1) & hashMod)
		{
			if( OPS::equal( m_elem[i], key ) )
			{
				return HK_MAP_INDEX_TO_ITERATOR(i); // found
			}
		}
	}
	return HK_MAP_INDEX_TO_ITERATOR(hashMod+1); // not found
}

template <typename T, typename Allocator, typename OPS >
hkResult hkSet<T,Allocator,OPS>::remove( T key )
{
	Iterator it = findElement(key);
	if( isValid(it) )
	{
		remove(it);
		return HK_SUCCESS;
	}
	return HK_FAILURE;	
}

template <typename T, typename Allocator, typename OPS >
inline hkBool32 hkSet<T,Allocator,OPS>::isValid( Iterator it ) const
{
	const int hashMod = getHashMod();
	// range [0, hashMod] is valid
	// hashMod+1 invalid
	// anything else is bad input
	int i = HK_MAP_ITERATOR_TO_INDEX(it);
	HK_ASSERT(0x7f305156, i>=0 && i<=hashMod+1);
	return i <= hashMod;
}

template <typename T, typename Allocator, typename OPS >
inline typename hkSet<T,Allocator,OPS>::Iterator hkSet<T,Allocator,OPS>::getNext( Iterator it ) const
{
	const int hashMod = getHashMod();
	int i = HK_MAP_ITERATOR_TO_INDEX(it);
	HK_ASSERT(0x7f305156, i>=0 && i<=hashMod);
	for( i += 1; i <= hashMod; ++i )
	{
		if( OPS::isValid( m_elem[i] ) )
		{
			break;
		}
	}
	return HK_MAP_INDEX_TO_ITERATOR(i);
}

template <typename T, typename Allocator, typename OPS >
inline T hkSet<T,Allocator,OPS>::getElement(Iterator it) const
{
	int i = HK_MAP_ITERATOR_TO_INDEX(it);
	HK_ASSERT(0x7f305156, i>=0 && i<=getHashMod());
	return m_elem[i];
}

template <typename T, typename Allocator, typename OPS >
hkResult hkSet<T,Allocator,OPS>::resizeTable(int newcap)
{
	int hashMod = getHashMod();

	newcap = hkMath::max2( newcap, (int) s_minimumCapacity );
	HK_ASSERT2(0x57c91b4a,  m_numElems < newcap, "table size is not big enough" );
	HK_ASSERT2(0x6c8f2576,  HK_NEXT_MULTIPLE_OF(2, newcap) == newcap, "table size should be a power of 2" );

	//hkBool32 dontDeallocate = m_numElems & static_cast<int>(DONT_DEALLOCATE_FLAG);
	int oldcap = hashMod+1;
	//Pair* oldelem = m_elem;
	//Pair* newelem = static_cast<Pair*>( alloc.blockAlloc( sizeof(Pair)*newcap ) ); // space for values too

	hkArray<T, Allocator> oldelem;
	oldelem.swap(m_elem);
	hkResult reserveRes = m_elem.reserveExactly(newcap);

	// Make sure alloc succeeded
	if ( HK_VERY_UNLIKELY((reserveRes != HK_SUCCESS)) )
	{
		return HK_FAILURE;
	}

	m_elem.setSizeUnchecked(newcap);

	//m_elem = newelem;

	for (int i = 0; i < newcap; i++) 
	{
		OPS::invalidate( m_elem[i] ); 
	} 
	m_numElems = 0;
	hashMod = newcap - 1;

	for( int i = 0; i < oldcap; ++i )
	{
		if( OPS::isValid( oldelem[i]) )
		{
			insert( oldelem[i] );
		}
	}

	return HK_SUCCESS;
}

template <typename T, typename Allocator, typename OPS >
hkBool32 hkSet<T,Allocator,OPS>::insert( T key )
{
	HK_ASSERT2(0x19291575, OPS::isValid(key), "pointer map keys must not be the empty value");
	{
		if( shouldResize() )
		{
			const int hashMod = getHashMod();
			resizeTable( hashMod + hashMod + 2 );
		}
	}

	const int hashMod = getHashMod();

	unsigned i;
	hkBool32 isNewKey = true;
	for( i = OPS::hash(key, hashMod);
		OPS::isValid(m_elem[i]);
		i = (i+1) & hashMod )
	{
		// find free slot
		if( OPS::equal( m_elem[i], key ) )
		{
			isNewKey = false;
			break;
		}
	}

	// dont increment m_numElems if overwriting.
	m_numElems += isNewKey;

	// insert key,value
	m_elem[i] = key;
	return isNewKey;
}

template <typename T, typename Allocator, typename OPS >
hkBool32 hkSet<T,Allocator,OPS>::tryInsert( T key, hkResult& res)
{
	HK_ASSERT2(0x19291575, OPS::isValid(key), "hkSet elements must not be the empty value");
	{
		if( shouldResize() )
		{
			const int hashMod = getHashMod();
			res = resizeTable( hashMod + hashMod + 2);
			if (res != HK_SUCCESS)
			{
				return false;
			}
		}
		else
		{
			res = HK_SUCCESS;
		}
	}

	return insert( key );
}

template <typename T, typename Allocator, typename OPS >
void hkSet<T,Allocator,OPS>::clear()
{
	const int hashMod = getHashMod();
	int capacity = hashMod+1;
	for (int i = 0; i < capacity; i++)
	{
		OPS::invalidate( m_elem[i] ); 
	} 
	m_numElems = 0;
}

template <typename T, typename Allocator, typename OPS >
void hkSet<T,Allocator,OPS>::reserve( int numElements )
{
	// Make sure that the actual table size is not going to be less than twice the current number of elements
	HK_ASSERT(0x4d0c5314, numElements >= 0 && (m_numElems & static_cast<int>(NUM_ELEMS_MASK)) * 2 <= numElements * 3 );
	int minCap = numElements * 2;
	int cap = s_minimumCapacity;
	while (cap < minCap) { cap *= 2; }

	resizeTable( cap );
}

template <typename T, typename Allocator, typename OPS >
void hkSet<T,Allocator,OPS>::optimizeCapacity( int numFreeElemsLeft /* = 0 */ )
{
	int desiredNumElem = m_numElems + numFreeElemsLeft;
	int newCap = getCapacityFor(desiredNumElem);

	if (newCap != getCapacity())
	{
		resizeTable(newCap);
	}
}

template <typename T, typename Allocator, typename OPS >
int hkSet<T,Allocator,OPS>::getSizeInBytesFor(int numOfKeys)
{
	return getCapacityFor(numOfKeys) * hkSizeOf(T);
}

template <typename T, typename Allocator, typename OPS >
int hkSet<T,Allocator,OPS>::getCapacityFor(int numOfKeys)
{
	// adjust the number to the power of 2
	int numSlots = numOfKeys * 2; // half full
	int cap;
	for( cap = s_minimumCapacity; cap < numSlots; cap *= 2 )
	{
		// double until sufficient capacity
	}
	return cap;
}


template <typename T, typename Allocator, typename OPS >
int hkSet<T,Allocator,OPS>::getCapacity( ) const
{ 
	return (getHashMod() + 1) & static_cast<int>(NUM_ELEMS_MASK); 
}

template <typename T, typename Allocator, typename OPS >
bool hkSet<T,Allocator,OPS>::shouldResize( ) const
{ 
	// This is quite conservative. We could grow more
	// slowly at the cost of potentially longer searches.

	const int hashMod = getHashMod();
	int numElems = m_numElems & static_cast<int>(NUM_ELEMS_MASK);
	return  (numElems + numElems) > hashMod;
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
