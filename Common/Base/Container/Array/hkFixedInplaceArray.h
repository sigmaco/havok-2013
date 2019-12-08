/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKBASE_HK_FIXED_INPLACE_ARRAY_H
#define HKBASE_HK_FIXED_INPLACE_ARRAY_H

/// This is an array of fixed size with inplace storage. It will ASSERT if its capacity is exhausted.
/// Essentially a wrapper around a C array with additional safety checks in debug.
template <typename T, int N>
class hkFixedInplaceArray
{
	public:

		typedef T	ItemType;

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_ARRAY, hkFixedInplaceArray);

			/// Creates a zero length array.
		HK_FORCE_INLINE hkFixedInplaceArray() : m_size(0) {}

			/// Returns the size.
		HK_FORCE_INLINE int			getSize() const { return m_size; }

			/// Returns true is the array is full.
		HK_FORCE_INLINE bool		isFull() const { return m_size == N; }

			/// Clear the array.
		HK_FORCE_INLINE void		clear() { m_size = 0; }

			/// Returns the capacity.
		HK_FORCE_INLINE int			getCapacity() const { return N; }

			/// Returns a pointer to the beginning of the array.
		HK_FORCE_INLINE T*			begin() { return m_data; }

			/// Returns a pointer to the beginning of the array.
		HK_FORCE_INLINE const T*	begin() const { return m_data; }

			/// Append elements to the array.
		HK_FORCE_INLINE void		append(const T* items, int count) { while(count--) pushBack(*items++); }

			/// Sets the size (i.e. number of used elements).
		HK_FORCE_INLINE void		setSize(int size) { m_size = size; HK_ASSERT2(0x48488B10, m_size <= N, "Fixed inplace array capacity overflow"); }

			/// Checks if the size is zero.
		HK_FORCE_INLINE hkBool		isEmpty() const { return m_size == 0; }

			/// Increments the size by 1 and returns a reference to the first element created.			
		HK_FORCE_INLINE T&			expandOne() { HK_ASSERT2(0x48488B11, m_size < N, "Fixed inplace array capacity overflow"); return m_data[m_size++]; }

			/// Read/write access to the i'th element.
		HK_FORCE_INLINE T&			operator[] (int i) { HK_ASSERT2(0x48488B12, i >= 0 && i < m_size, "Index out of range"); return m_data[i]; }

			/// Read only access to the i'th element.
		HK_FORCE_INLINE const T&	operator[] (int i) const { HK_ASSERT2(0x48488B12, i >= 0 && i < m_size, "Index out of range"); return m_data[i]; }

			/// Adds an element to the end.
		HK_FORCE_INLINE void		pushBack(const T& e) { expandOne() = e; }

			/// Remove the last element.
		HK_FORCE_INLINE void		popBack() { HK_ASSERT2(0x48488B14, m_size > 0, "Empty array"); m_size--; }

			/// Remove the i'th element and replace its location with the last element of the array.
		HK_FORCE_INLINE void		removeAt(int i) { operator[](i) = back(); popBack(); }

			/// Read/write access to the last element.
		HK_FORCE_INLINE T&			back() { return operator[](m_size-1); }

			/// Read only access to the last element.
		HK_FORCE_INLINE const T&	back() const { return operator[](m_size-1); }

			/// Linear search.
		inline int					indexOf(const T& v) const { for(int i=0; i<m_size; ++i) { if(m_data[i] == v) return i; } return -1; }
			
	protected:

		T	m_data[N];
		int	m_size;
};


#include <Common/Base/Container/Array/hkFixedInplaceArray.inl>


#endif // HKBASE_HK_FIXED_INPLACE_ARRAY_H

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
