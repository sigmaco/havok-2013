/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKBASE_HKFIXEDCAPACITYARRAY_H
#define HKBASE_HKFIXEDCAPACITYARRAY_H


/// This is an array of fixed size. Once its capacity is exhausted it will continue to re-use the last element.
template <typename T>
class hkFixedCapacityArray
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_ARRAY, hkFixedCapacityArray<T>);

			/// Creates a zero length array.
		HK_FORCE_INLINE hkFixedCapacityArray();

			/// Creates an array of capacity \a capacity. All elements are uninitialized.
		explicit HK_FORCE_INLINE hkFixedCapacityArray(int capacity, const char* descriptor = "");

			/// Creates an array using an external buffer. All elements are untouched.
		explicit HK_FORCE_INLINE hkFixedCapacityArray(void* buffer, int bufferSize, const char* descriptor = "");

			/// For serialization, we want to initialize the vtables
			/// in classes post data load, and NOT call the default constructor
			/// for the arrays (as the data has already been set).
		hkFixedCapacityArray(hkFinishLoadedObjectFlag f) { }

			/// Deallocates array memory.
		HK_FORCE_INLINE ~hkFixedCapacityArray();

			/// Returns the size.
		HK_FORCE_INLINE int getSize() const;

			/// Returns the capacity.
		HK_FORCE_INLINE int getCapacity() const;

			/// Sets the size (i.e. number of used elements).
		HK_FORCE_INLINE void setSize(int size);

			/// Checks if the size is zero.
		HK_FORCE_INLINE bool isEmpty() const;

			/// Checks if the array is full.
		HK_FORCE_INLINE bool isFull() const;

			/// Increments the size by 1 and returns a reference to the first element created.
			/// If the capacity has been exhausted, this will return a reference to the last element instead.
		HK_FORCE_INLINE T& expandOne();

			/// Read/write access to the i'th element.
		HK_FORCE_INLINE T& operator[] (int i);

			/// Read only access to the i'th element.
		HK_FORCE_INLINE const T& operator[] (int i) const;

			/// Returns the index of the first occurrence of t, or -1 if not found.
		int indexOf(const T& t) const;

			/// Adds an element to the end. If the capacity has been exhausted, the last element will be overwritten.
		HK_FORCE_INLINE void pushBack(const T& e);

			/// Read/write access to the last element.
		HK_FORCE_INLINE T& back();

			/// Read only access to the last element.
		HK_FORCE_INLINE const T& back() const;

			/// 
		typedef T* iterator;
			/// 
		typedef const T* const_iterator;

			/// Returns an STL-like iterator to the first element.
		HK_FORCE_INLINE iterator begin();
			/// Returns an STL-like iterator to the 'one past the last' element.
		HK_FORCE_INLINE iterator end();
			/// Returns an STL-like const iterator to the first element.
		HK_FORCE_INLINE const_iterator begin() const;
			/// Returns an STL-like const iterator to the 'one past the last' element.
		HK_FORCE_INLINE const_iterator end() const;

			/// Returns the number of times the array could not be expanded because the capacity had been exhausted
		HK_FORCE_INLINE int getNumOverflows() const;

			/// Sets the size to zero and deallocates storage.
		void clearAndDeallocate();

	protected:

		hkFixedCapacityArray(const hkFixedCapacityArray&) { }
		void operator=(const hkFixedCapacityArray&) { }

		void releaseMemory();

		HK_PAD_ON_SPU(T*)		m_data;
		HK_PAD_ON_SPU(int)		m_size; 
		HK_PAD_ON_SPU(int)		m_numOverflows; 
		HK_PAD_ON_SPU(int)		m_capacity;
		HK_PAD_ON_SPU(hkBool32)	m_usesExternalBuffer;


};


#include <Common/Base/Container/Array/hkFixedCapacityArray.inl>


#endif // HKBASE_HKFIXEDCAPACITYARRAY_H

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
