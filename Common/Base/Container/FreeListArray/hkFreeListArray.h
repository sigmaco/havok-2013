/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKBASE_FREE_LIST_ARRAY_H
#define HKBASE_FREE_LIST_ARRAY_H

#if !defined(__HAVOK_PARSER__) && !defined(HK_PLATFORM_ANDROID)
#include <new>
#endif



/// Default set of operations. This will store the next empty element index in the first 4 bytes of the object.
/// By default isEmpty is not implemented and thus operations like isAllocated and clear (called from the destructor) will
/// run in linear time. If you want to implement isEmpty you must create your own operations structure, do not change
/// this class as that will affect all its instances.
template <typename T>
struct hkDefaultFreeListArrayOperations
{	
	/// Sets an uninitialized element to empty and stores in it the index of the next empty element. No destructors are 
	/// called on empty elements. If you want to serialize the free list array you need to make sure that:
	///  - Empty elements are serializable as T types
	///  - The next element index stored in the object is serialized properly
	HK_FORCE_INLINE static void setEmpty(T& element, hkUint32 next) { (hkUint32&)element = next; }

	/// Returns the index of the next free element. Will be called only with empty elements
	HK_FORCE_INLINE static hkUint32 getNext(const T& element) { return (hkUint32&)element; }

	/// Implement this method in your custom operations structures to allow operations like isAllocated and clear to run
	/// in constant time
	//HK_FORCE_INLINE static hkBool32 isEmpty(const T& element);
};


/// Structure used to store VALUE_TYPE elements as a POD type in the elements array

template <typename VALUE_TYPE>
struct hkFreeListArrayElement
{	
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, hkFreeListArrayElement);
	HK_DECLARE_REFLECTION();
	HK_DECLARE_POD_TYPE();

	VALUE_TYPE m_pod;
};


/// Array of VALUE_TYPE objects where a list of the unused elements is kept overwriting some bytes in each unused 
/// element. The specific way this is done is determined by the implementation of the free list array operations.
/// VALUE_TYPE constructor is called only when allocating an element, not for all positions in 
/// array. Correspondingly, VALUE_TYPE destructor is called only when releasing an element in use. 
/// Elements are indexed using INDEX_TYPE, which must implement hkHandle.
///
/// NOTE: See setEmpty comments in hkDefaultFreeListArrayOperations for details on serialization support
template < typename VALUE_TYPE, typename INDEX_TYPE, int GROWTH, typename OPERATIONS = hkDefaultFreeListArrayOperations<VALUE_TYPE> >
struct hkFreeListArray
{
	public:

		typedef hkFreeListArray<VALUE_TYPE, INDEX_TYPE, GROWTH, OPERATIONS>	ThisType;

		enum
		{
			ARRAY_GROWTH = GROWTH
		};

	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE,hkFreeListArray);
		HK_DECLARE_REFLECTION();		

		hkFreeListArray(hkFinishLoadedObjectFlag f) : m_elements(f) {}


		/// Constructor.
		HK_FORCE_INLINE hkFreeListArray();

		/// Destructor
		HK_FORCE_INLINE ~hkFreeListArray();

		/// Clear the free list
		HK_FORCE_INLINE void clear();

		/// Copies the list
		HK_FORCE_INLINE void copy(const hkFreeListArray& other);

		/// Allocate one element, call VALUE_TYPE ctor.
		HK_FORCE_INLINE INDEX_TYPE allocate();

		/// Allocate one element and call VALUE_TYPE copy constructor.
		HK_FORCE_INLINE INDEX_TYPE allocate(const VALUE_TYPE& valueToCopy);

		/// Release one element, call VALUE_TYPE dtor.
		HK_FORCE_INLINE void release(INDEX_TYPE index);

		/// Grows the array by the specified quantity. New elements are not constructed, instead OPERATIONS::setEmpty()
		/// is called on them.
		HK_FORCE_INLINE void grow(int growth = GROWTH);

		/// Compact the storage.
		HK_FORCE_INLINE void compact();

		/// Swaps the storage with the given array
		HK_FORCE_INLINE void swapStorage(hkArray<VALUE_TYPE>& newStorage);


		/// Read-write indexed access.
		HK_FORCE_INLINE	VALUE_TYPE& operator[](INDEX_TYPE index);

		/// Read-only indexed access.
		HK_FORCE_INLINE	const VALUE_TYPE& operator[](INDEX_TYPE index) const;
		
		/// Returns non-zero if a given ID is allocated.
		HK_FORCE_INLINE hkBool32 isAllocated(INDEX_TYPE index) const;

		/// Returns non-zero if all slots are allocated. Any further allocation will grow the storage.
		HK_FORCE_INLINE hkBool32 isFull() const;
	
		/// Get the capacity of the free list.
		HK_FORCE_INLINE int getCapacity() const;

		/// Get the storage buffer address.
		HK_FORCE_INLINE const VALUE_TYPE* getBuffer() const;

		/// Get the end index of the free list.
		HK_FORCE_INLINE INDEX_TYPE getMaxIndex() const;
			
		/// Get an read-only element from its index using software cache on if called from an SPU.
		HK_FORCE_INLINE	const VALUE_TYPE& getAtWithCache(INDEX_TYPE index) const;

		/// Get a read-only access to the underlying storage.
		HK_FORCE_INLINE const hkArray<VALUE_TYPE>& getStorage() const;

		/// An iterator to enumerate all allocated elements in a hkFreeListArray.
		/// This requires OPERATIONS::isEmpty() to be implemented.
		class Iterator
		{
			public:

				HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_PHYSICS, ThisType::Iterator );

				HK_FORCE_INLINE Iterator( const ThisType& freeListArray );	///< Constructor
				HK_FORCE_INLINE void next();								///< Advance to the next allocated element
				HK_FORCE_INLINE bool isValid() const;						///< Is the iterator still valid?

				HK_FORCE_INLINE INDEX_TYPE getIndex() const;				///< Get the current index 
				HK_FORCE_INLINE const VALUE_TYPE& getValue() const;			///< Get the current element

			protected:

				const ThisType& m_freeListArray;
				int m_index;
		};

	private:

		typedef hkFreeListArrayElement<VALUE_TYPE> ElementAsPod;

		// Structure used to check at compilation time if OPERATIONS implements a static method with
		// the signature:  hkBool32 isEmpty(const VALUE_TYPE&)
		class OperationsImplementIsEmpty
		{
			protected:

				typedef char Yes;
				typedef long No;

				// Instantiation of this type will fail if the type of the value passed as second parameter does not match the 
				// first parameter.
				template <typename T, T> struct TypeCheck;

				// Type of the isEmpty function
				typedef hkBool32 (HK_CALL *IsEmptyPtr) (const VALUE_TYPE&);

				// If the first method cannot be compiled the second one will be used (see SFINAE)
				template <typename T> static Yes HasIsEmpty(TypeCheck< IsEmptyPtr, &T::isEmpty >*);
				template <typename T> static No  HasIsEmpty(...);

			public:

				enum { VALUE = (sizeof(HasIsEmpty<OPERATIONS>(0)) == sizeof(Yes)) };
		};

		typedef hkTraitBool<true> CanCheckForEmpty;
		typedef hkTraitBool<false> CanNotCheckForEmpty;

	private:
		
		HK_FORCE_INLINE void _clear(CanCheckForEmpty notUsed);
		HK_FORCE_INLINE void _clear(CanNotCheckForEmpty notUsed);

		HK_FORCE_INLINE hkBool32 _isAllocated(INDEX_TYPE index, CanCheckForEmpty notUsed) const;
		HK_FORCE_INLINE hkBool32 _isAllocated(INDEX_TYPE index, CanNotCheckForEmpty notUsed) const;

	protected:
		
		/// Elements storage (free and allocated).
		hkArray<ElementAsPod> m_elements;

		/// First free element index.
		hkInt32 m_firstFree;
};

#include <Common/Base/Container/FreeListArray/hkFreeListArray.inl>

#endif // HKBASE_FREE_LIST_ARRAY_H

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
