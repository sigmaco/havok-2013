/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_BASE_TYPE_INFO_H
#define HK_BASE_TYPE_INFO_H

class hkClass;

class hkTypeInfo
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, hkTypeInfo);

		typedef void (HK_CALL *FinishLoadedObjectFunction)(void*, int);
		typedef void (HK_CALL *CleanupLoadedObjectFunction)(void*);

		hkTypeInfo( const char* name,
			        const char* scopedName,
				FinishLoadedObjectFunction finish,
				CleanupLoadedObjectFunction cleanup,
				const void* vtable,
				hk_size_t size)
			:   m_typeName(name),
				m_scopedName(scopedName),
				m_finishLoadedObjectFunction(finish),
				m_cleanupLoadedObjectFunction(cleanup),
				m_vtable(vtable),
				m_size(size)
		{
		}
		const char* getTypeName() const
		{
			return m_typeName;
		}
		const char* getScopedName() const
		{
			return m_scopedName;
		}
		const void* getVtable() const
		{
			return m_vtable;
		}
			/// Cleanup a loaded object (run destructor etc)
		void cleanupLoadedObject(void* ptr) const;
			/// Finish loading an object
		void finishLoadedObject(void* ptr, int finishFlag) const;
			/// Finish the loaded object without informing the tracker.
			/// The object must be cleaned up independently of cleanupLoadedObject - as that function will
			/// inform the tracker.
		void finishLoadedObjectWithoutTracker(void* ptr, int finishFlag) const;

			/// Returns true if has a finish function
		hkBool hasFinishFunction() const { return m_finishLoadedObjectFunction != HK_NULL; }
			/// Returns true if has a cleanup function
		hkBool hasCleanupFunction() const { return m_cleanupLoadedObjectFunction != HK_NULL; }

			/// Get the size of an instantiation in bytes
		hk_size_t getSize() const { return m_size; }

			/// Returns true if the type is virtual
		hkBool isVirtual() const { return m_vtable != HK_NULL; }

	private:

		const char* m_typeName;
		const char* m_scopedName;
		FinishLoadedObjectFunction m_finishLoadedObjectFunction;
		CleanupLoadedObjectFunction m_cleanupLoadedObjectFunction;
		const void* m_vtable;
		hk_size_t m_size;
};

#if HK_LINKONCE_VTABLES==1
#	define HK_VTABLE_FROM_OBJECT(x) (*reinterpret_cast<const void*const*>(x))
#else
#	include <typeinfo>
#	if HK_HASHCODE_VTABLE_REGISTRY == 1
		// If typeinfo::hash_code() is implemented, this is more efficient than a string map of names
#		define HK_VTABLE_FROM_OBJECT(x) ((const void*)(typeid(*(hkReferencedObject*)(void*)x).hash_code()))
#		define HK_VTABLE_FROM_CLASS(x) ((const void*)(typeid(x).hash_code()))
#	else
#		define HK_VTABLE_FROM_OBJECT(x) ((const void*)(typeid(*(hkReferencedObject*)(void*)x).name()))
#		define HK_VTABLE_FROM_CLASS(x) ((const void*)(typeid(x).name()))
#	endif
#endif

/// Utility to define an empty stub hkClass instance.
#define HK_REFLECTION_DEFINE_STUB_VIRTUAL_BASE(KLASS) \
    const hkClass KLASS##Class(#KLASS, HK_NULL, sizeof(KLASS), HK_NULL, 0, HK_NULL, 0, HK_NULL, 0, HK_NULL, HK_NULL, 0)
/// Utility to define an empty stub hkClass instance.
#define HK_REFLECTION_DEFINE_STUB_VIRTUAL(KLASS, PARENT) \
    const hkClass KLASS##Class(#KLASS, &PARENT##Class, sizeof(KLASS), HK_NULL, 0, HK_NULL, 0, HK_NULL, 0, HK_NULL, HK_NULL, 0)

#endif // HK_BASE_TYPE_INFO_H

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
