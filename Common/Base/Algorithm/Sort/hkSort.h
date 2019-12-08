/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKBASE_HKALGORITHM_H
#define HKBASE_HKALGORITHM_H

#include <Common/Base/Algorithm/Sort/hkRadixSort.h>

namespace hkAlgorithm
{

	/// swap the elements
	template<typename T>
	HK_FORCE_INLINE void HK_CALL swap(T& x, T& y)
	{
		T t(x);
		x = y;
		y = t;
	}


	/// swap the 16 byte aligned elements
	template<typename T>
	HK_FORCE_INLINE void HK_CALL swapAligned16(T& x, T& y)
	{
		HK_ALIGN16( T t ) = x;
		x = y;
		y = t;
	}

	/// swap the 32 byte aligned elements
	template<typename T>
	HK_FORCE_INLINE void HK_CALL swapAligned32(T& x, T& y)
	{
		HK_ALIGN32( T t ) = x;
		x = y;
		y = t;
	}
			
	/// use to change endian-ness. Swaps the bytes pointed to by start.
	HK_FORCE_INLINE void swapBytes(void* start, int count)
	{
		hkUint8* front = (hkUint8*)start;
		hkUint8* back  = (hkUint8*)hkAddByteOffset(start, count-1);
		for (int i = 0; i < count / 2; i++)
		{
			hkAlgorithm::swap(*(front++), *(back--));
		}
	}

	/// function object that routes calls to operator<
	template<typename T>
	class less
	{
		public:

			HK_FORCE_INLINE hkBool32 operator() ( const T& a, const T& b )
			{
				return ( a < b );
			}
	};


	/// function object that routes calls to operator>
	template<typename T>
	class greater
	{
	public:

		HK_FORCE_INLINE hkBool32 operator() ( const T& a, const T& b )
		{
			return ( a > b );
		}
	};

	/// function object that routes calls to operator==
	template <typename T>
	class eq
	{
	public:

		HK_FORCE_INLINE hkBool32 operator() (const T& a, const T& b)
		{
			return (a == b);
		}
	};

	/// Binary search, returns the index of the key in the array or -1 if not found.
	template <typename K, typename T, typename L>
	static inline int	binarySearch(const K& key, const T* items, int numItems, L cmpLess)
	{
		int	i=0, j = numItems-1;
		while(j > i)
		{
			const int m = (i+j) >> 1;
			if(cmpLess(items[m] , key)) i = m + 1; else j = m;
		}
		if(i == j && !(cmpLess(items[i] , key) || cmpLess(key , items[i])))
			return i;
		else
			return -1;
	}

	/// Computes the insertion index for key K in the sorted array of items.
	template <typename K, typename T, typename L>
	static HK_FORCE_INLINE int HK_CALL findInsertionIndex(const K& key, const T* items, int numItems, L cmpLess)
	{
		int	i=0, j = numItems-1;
		while(j > i)
		{
			const int m = (i+j) >> 1;
			if(cmpLess(items[m] , key)) i = m + 1; else j = m;
		}

		HK_ASSERT(0x318b4c19, (!i && !numItems) || ((i < numItems) && cmpLess(key, items[i])) );
		return i;
	}

	/// Binary search, returns the index of the key in the array or -1 if not found.
	template <typename K, typename T>
	static inline int	binarySearch(const K& key, const T* items, int numItems)
	{
		return binarySearch(key, items, numItems, less<T>());
	}
	
	/// heap sort. You supply the functor, see hkAlgorithm::less for an example functor.
	template<typename T, typename L>
	void HK_CALL heapSort(T *pArr, int iSize, L cmpLess);


	/// Heap sort for the elements of the specified array.
	///
	/// \param *pArr		A pointer to the array to sort.
	/// \param iSize		The size of the array pointed to by *pArr.
	///
	template<typename T>
	void HK_CALL heapSort(T *pArr, int iSize)
	{
		heapSort( pArr, iSize, less<T>() );
	}

	// used by heapSort
	template<typename T, typename L>
	void HK_CALL downHeap(T *pArr, int k, int n, L cmpLess);

	template<typename T, typename L>
	void HK_CALL insertionSort(T* pArr, int size, L cmpLess);

	template<typename T>
	void HK_CALL insertionSort(T* pArr, int size)
	{
		insertionSort( pArr, size, less<T>() );
	}

	/// quick sort. You supply the functor, see hkAlgorithm::less for an example functor.
	template<typename T, typename L>
	HK_FORCE_INLINE	void HK_CALL quickSort(T *pArr, int iSize, L cmpLess);


	/// Quick sort for the elements of the specified array.
	///
	/// \param *pArr		A pointer to the data to sort.
	/// \param iSize		The size of the array pointed to by *pArr.
	///
	template<typename T>
	HK_FORCE_INLINE	void HK_CALL quickSort(T *pArr, int iSize)
	{
		quickSort( pArr, iSize, less<T>() );
	}

	template< typename T, typename L >
	void HK_CALL quickSortRecursive(T *pArr, int d, int h, L cmpLess);

        /// Quick sort using an explicit stack for efficiency reasons.
	template<typename T>
    HK_FORCE_INLINE void HK_CALL explicitStackQuickSort(T *pArr, int iSize)
	{
        explicitStackQuickSort( pArr, iSize, less<T>() );
	}


	/// Bubble sort. You supply the functor, see hkAlgorithm::less for an example functor.
	template<typename T, typename L>
	HK_FORCE_INLINE	void HK_CALL bubbleSort(T *pArr, int iSize, L cmpLess);


	/// Bubble sort for the elements of the specified array.
	/// THIS IS NOT AN EFFICIENT SORTING ALGORITHM: O(n^2).
	/// It's almost always better to use quickSort or heapSort.
	/// Unlike quickSort or heapSort, this algorithm is STABLE:
	/// the relative order of equal elements is preserved.
	/// Bubble sort is a good choice for sorting or re-sorting a list
	/// that is approximately sorted already.
	///
	/// \param *pArr		A pointer to the data to sort.
	/// \param iSize		The size of the array pointed to by *pArr.
	///
	template<typename T>
	HK_FORCE_INLINE	void HK_CALL bubbleSort(T *pArr, int iSize)
	{
		bubbleSort( pArr, iSize, less<T>() );
	}

	struct ListElement
	{
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, ListElement);
		ListElement* next;
	};
		/// Inplace singly linked list sort.
		/// Elements are sorted by address.
		/// Performs a merge sort (O(n log n) without any allocations.
	ListElement* _sortList(ListElement* head);

		/// Inplace singly linked list sort.
		/// Assumes the first element of each object is a pointer to next.
		/// Elements are sorted by address.
		/// Performs a merge sort (O(n log n) without any allocations.
	template<typename T>
	T* sortList(T* head)
	{
		return reinterpret_cast<T*>( _sortList( reinterpret_cast<ListElement*>(head) ) );
	}

	/// Removes identical entries in the given list. Returns the number of unique elements found.
	/// The list is assumed to be sorted
	template <typename T, typename Eq>
	HK_FORCE_INLINE int removeDuplicatesFromSortedList(T* HK_RESTRICT elements, int numElements, Eq eq)
	{
		if ( ! numElements )
		{
			return 0;
		}

		int prev = 0;
		for (int crt = 1; crt < numElements; crt++)
		{
			if ( !eq(elements[prev], elements[crt]) )
			{
				// Element not equal, crt survives
				elements[++prev] = elements[crt];
			}
		}

		return prev + 1;
	}

	template <typename T>
	HK_FORCE_INLINE int removeDuplicatesFromSortedList(T* HK_RESTRICT elements, int numElements)
	{
		return removeDuplicatesFromSortedList(elements, numElements, eq<T>());
	}

	/// Computes the intersection of two sorted lists. Returns the number of elements in the intersection
	template <typename T, typename Less, typename Eq>
	HK_FORCE_INLINE int HK_CALL intersectionOfSortedLists(	const T* HK_RESTRICT elementsA, int numElementsA, 
															const T* HK_RESTRICT elementsB, int numElementsB, 
															T* HK_RESTRICT elementsAB, Less cmpLess, Eq cmpEq)
	{
		int iA = 0, iB = 0, iAB = 0;
		while ( (iA < numElementsA) && (iB < numElementsB) )
		{
			const T& valA = elementsA[iA];
			const T& valB = elementsB[iB];
			if		( cmpLess(valA, valB) )	{	iA++;			}
			else if	( cmpEq(valA, valB) )	{	elementsAB[iAB++] = valA;	iA++;	iB++;	}
			else 							{	iB++;			}						
		}

		return iAB;
	}

	/// Computes the union of two sorted lists. Returns the number of elements in the union
	template <typename T, typename Less, typename Eq>
	HK_FORCE_INLINE int HK_CALL unionOfSortedLists(	const T* HK_RESTRICT elementsA, int numElementsA, 
													const T* HK_RESTRICT elementsB, int numElementsB, 
													T* HK_RESTRICT elementsAB, Less cmpLess, Eq cmpEq)
	{
		int iA = 0, iB = 0, iAB = 0;
		while ( (iA < numElementsA) && (iB < numElementsB) )
		{
			const T& valA = elementsA[iA];
			const T& valB = elementsB[iB];
			if		( cmpLess(valA, valB) )		{	elementsAB[iAB++] = valA;	iA++;			}
			else if	( cmpEq(valA, valB) )		{	elementsAB[iAB++] = valA;	iA++;	iB++;	}
			else /* ( valA > valB ) */			{	elementsAB[iAB++] = valB;	iB++;			}
		}
		while ( iA < numElementsA )	{	elementsAB[iAB++] = elementsA[iA++];	}
		while ( iB < numElementsB )	{	elementsAB[iAB++] = elementsB[iB++];	}

		return iAB;
	}

	/// Computes the difference of two sorted lists. Returns the number of elements in the difference
	template <typename T, typename Less, typename Eq>
	HK_FORCE_INLINE int HK_CALL differenceOfSortedLists(const T* HK_RESTRICT elementsA, int numElementsA, 
														const T* HK_RESTRICT elementsB, int numElementsB, 
														T* HK_RESTRICT elementsAB, Less cmpLess, Eq cmpEq)
	{
		int iA = 0, iB = 0, iAB = 0;
		while ( (iA < numElementsA) && (iB < numElementsB) )
		{
			const T& valA = elementsA[iA];
			const T& valB = elementsB[iB];
			if		( cmpLess(valA, valB) )		{	elementsAB[iAB++] = valA;	iA++;			}
			else if	( valA == valB )			{	iA++;	iB++;	}
			else /* ( valA > valB ) */			{	iB++;			}						
		}
		while ( iA < numElementsA )	{	elementsAB[iAB++] = elementsA[iA++];	}

		return iAB;
	}

	/// Returns true if the sorted list A is included in the sorted list B
	template <typename T, typename Less, typename Eq>
	HK_FORCE_INLINE bool HK_CALL testInclusionOfSortedLists(const T* HK_RESTRICT elementsA, int numElementsA, 
															const T* HK_RESTRICT elementsB, int numElementsB, 
															Less cmpLess, Eq cmpEq)
	{
		int ia = numElementsA - 1, ib = numElementsB - 1;
		while ( (ia >= 0) && (ib >= 0) )
		{
			const T& eA = elementsA[ia];
			const T& eB = elementsB[ib];

			if ( cmpLess(eB, eA) )
			{
				return false;	// eA is unique to A, no containment!
			}

			if ( cmpEq(eA, eB) )
			{
				ia--;	// eA = eB is common to both A and B
			}
			ib--;		// eA <= eB
		}
		return (ia < 0);
	}

	template <typename T>
	HK_FORCE_INLINE int HK_CALL intersectionOfSortedLists(	const T* HK_RESTRICT elementsA, int numElementsA, 
															const T* HK_RESTRICT elementsB, int numElementsB, 
															T* HK_RESTRICT elementsAB)
	{
		return intersectionOfSortedLists(elementsA, numElementsA, elementsB, numElementsB, elementsAB, less<T>(), eq<T>());
	}

	template <typename T>
	HK_FORCE_INLINE int HK_CALL unionOfSortedLists(	const T* HK_RESTRICT elementsA, int numElementsA,
													const T* HK_RESTRICT elementsB, int numElementsB,
													T* HK_RESTRICT elementsAB)
	{
		return unionOfSortedLists(elementsA, numElementsA, elementsB, numElementsB, elementsAB, less<T>(), eq<T>());
	}

	template <typename T>
	HK_FORCE_INLINE int HK_CALL differenceOfSortedLists(	const T* HK_RESTRICT elementsA, int numElementsA,
															const T* HK_RESTRICT elementsB, int numElementsB,
															T* HK_RESTRICT elementsAB)
	{
		return differenceOfSortedLists(elementsA, numElementsA, elementsB, numElementsB, elementsAB, less<T>(), eq<T>());
	}

	template <typename T>
	HK_FORCE_INLINE bool HK_CALL testInclusionOfSortedLists(const T* HK_RESTRICT elementsA, int numElementsA, 
															const T* HK_RESTRICT elementsB, int numElementsB)
	{
		return testInclusionOfSortedLists(elementsA, numElementsA, elementsB, numElementsB, less<T>(), eq<T>());
	}
}

#define hkSort hkAlgorithm::quickSort
//#define hkSort hkAlgorithm::explicitStackQuickSort

#include <Common/Base/Algorithm/Sort/hkSort.inl>

#endif // HKBASE_HKALGORITHM_H

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
