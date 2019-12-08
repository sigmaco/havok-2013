/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKBASE_HKREFPTR_H
#define HKBASE_HKREFPTR_H

	/// Intermediate value for pointer return values. To avoid a resource leak,
	/// it needs to have a reference removed when the object is no longer needed.
	/// Usually this type is used as an intermediate return value for functions and will
	/// be assigned directly to a hkRefPtr.
	/// Note that this indicates a newly added reference, not necessarily a new object, i.e.
	/// the returned object may be shared.
template <typename TYPE>
class hkRefNew
{
	public:

			/// Implicit conversion from raw pointer.
		hkRefNew(TYPE* t) : m_pntr(t) {}
			/// Assume ownership of this reference.
			/// Assumes responsibility for calling removeReference in the future.
		TYPE* stealOwnership() { TYPE* t = m_pntr; m_pntr = HK_NULL; return t; }

	private:

		hkRefNew(); ///< Not implemented
		void operator=(const hkRefNew& b); ///< Not implemented
		TYPE* m_pntr;
};

	/// The contained object is owned by another object. Usually used as an intermediate
	/// value for function return types, it indicates that a reference has not been added to
	/// the returned object. It is still owned and managed by somebody else. If the owning object
	/// is modified, the reference may become invalid (dangling pointer).
	/// Assign to a hkRefPtr to prevent the reference being removed prematurely.
template <typename TYPE>
class hkRefLoan
{
	public:

			/// Implicit conversion from raw pointer.
		hkRefLoan(TYPE* t) : m_pntr(t) {}
			/// Implicit conversion to raw pointer.
		operator TYPE*() const { return m_pntr; }

	private:

		hkRefLoan(); ///< Not implemented
		void operator=(const hkRefLoan& b); ///< Not implemented
		TYPE* m_pntr;
};

	/// A simple helper class to automatically add and remove references to objects.
template <class TYPE>
class hkRefPtr
{
	public:

		typedef hkRefPtr<TYPE> ThisType;
		HK_DECLARE_PLACEMENT_ALLOCATOR();

			/// Default constructor.
			/// Stored pointer is set to HK_NULL.
		HK_FORCE_INLINE hkRefPtr();

			/// Copy constructor.
			/// Increase reference count for object in 'rp' and set pointer to it.
		HK_FORCE_INLINE hkRefPtr(const hkRefPtr& rp);

			/// Add a reference count for object in 'rp' and set pointer to it.
		HK_FORCE_INLINE hkRefPtr(hkRefLoan<TYPE> rp);

			/// Steal (don't increment) the reference from 'rp'.
		HK_FORCE_INLINE hkRefPtr(hkRefNew<TYPE> rp);

			/// Finish constructor.
		HK_FORCE_INLINE hkRefPtr (hkFinishLoadedObjectFlag );

			/// Constructor from pointer.
			/// Increase reference count for object 'e' and set the pointer to it.
		HK_FORCE_INLINE hkRefPtr(TYPE* e);

			/// Destructor.
			/// Decrease reference count for stored object.
		HK_FORCE_INLINE ~hkRefPtr();

			/// Assignment operator.
			/// Increase reference count for object in 'rp',
			/// decrease reference count for stored object and set pointer to object from 'rp'.
		HK_FORCE_INLINE void operator=(const hkRefPtr& rp);

			/// Assignment operator.
			/// Increase reference count for object in 'rp',
			/// decrease reference count for stored object and set pointer to object from 'rp'.
		HK_FORCE_INLINE void operator=(hkRefLoan<TYPE> rp);

			/// Assignment operator.
			/// Steals (does not increment) the reference from 'rp'.
			/// Decrease the original reference count and set pointer to object from 'rp'.
		HK_FORCE_INLINE void operator=(hkRefNew<TYPE> rp);

			/// Assignment operator.
			/// Increase reference count for object 'e',
			/// decrease reference count for stored object and set pointer to 'e'.
		HK_FORCE_INLINE void operator=(TYPE* e);

			/// Return pointer to stored object.
		HK_FORCE_INLINE TYPE* val() const;

			/// Pointer to stored object.
		HK_FORCE_INLINE TYPE* operator->() const;

			/// Replace stored pointer with 'e' without incrementing reference count for 'e'.
			/// Reference count for previously stored object is decreased.
		HK_FORCE_INLINE void setAndDontIncrementRefCount( TYPE* e );

			/// Return pointer to stored object.
		HK_FORCE_INLINE operator TYPE*() const;

	private:

		TYPE* m_pntr;
};

#include <Common/Base/Types/hkRefPtr.inl>

#endif // HKBASE_HKREFPTR_H

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
