/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_VTABLE_CLASS_REGISTRY_H
#define HK_VTABLE_CLASS_REGISTRY_H

#if (HK_LINKONCE_VTABLES==1) || (HK_HASHCODE_VTABLE_REGISTRY==1)
#include <Common/Base/Container/PointerMap/hkPointerMap.h>
#else
#include <Common/Base/Container/StringMap/hkStringMap.h>
#endif

#include <Common/Base/Reflection/hkTypeInfo.h>

/// Registry of vtables to hkClass instances.
class hkVtableClassRegistry : public hkReferencedObject, public hkSingleton<hkVtableClassRegistry>
{
	public:
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
		hkVtableClassRegistry() {}

			/// Associate vtable with the given hkClass.
		virtual void registerVtable( const void* vtable, const hkClass* klass );

			/// Returns the class registered for the given vtable
		virtual const hkClass* getClassFromVtable(const void* vtable)
		{
			#if (HK_LINKONCE_VTABLES==1) || (HK_HASHCODE_VTABLE_REGISTRY==1)
				return m_map.getWithDefault( vtable, HK_NULL );
			#else
				return m_map.getWithDefault( (const char*)vtable, HK_NULL );
			#endif
		}

			/// Get the class from an object instance which has a vtable.
		virtual const hkClass* getClassFromVirtualInstance( const void* obj ) const
		{
			const void* vtable = HK_VTABLE_FROM_OBJECT(obj);
			#if (HK_LINKONCE_VTABLES==1) || (HK_HASHCODE_VTABLE_REGISTRY==1)
				return m_map.getWithDefault( vtable, HK_NULL );
			#else
				return m_map.getWithDefault( (const char*)vtable, HK_NULL );
			#endif
		}

			/// Register each vtable from "infos" with the corresponding class from "classes".
			/// The list is terminated by the first null info or class.
		void registerList( const hkTypeInfo* const * infos, const hkClass* const * classes);

			/// Merges all entries from "copyFrom". (potentially overwriting local entries)
		void merge(const hkVtableClassRegistry& mergeFrom);

			/// Get array of registered classes, e.g., to iterate through them.
		virtual void getClasses( hkArray<const hkClass*>& classes ) const
		{
			#if (HK_LINKONCE_VTABLES==1) || (HK_HASHCODE_VTABLE_REGISTRY==1)
				hkPointerMap<const void*, const hkClass*>::Iterator iter = m_map.getIterator();
			#else
				hkStringMap<const hkClass*>::Iterator iter =  m_map.getIterator();
			#endif
			while (m_map.isValid(iter))
			{
				classes.pushBack(m_map.getValue(iter));
				iter = m_map.getNext(iter);
			}
		}

	protected:

		#if (HK_LINKONCE_VTABLES==1) || (HK_HASHCODE_VTABLE_REGISTRY==1)
			hkPointerMap<const void*, const hkClass*> m_map;
		#else
		// No guarantee that the virtal tables at same addr, and also even using typeid that the typeid->name etc is constant
			hkStringMap<const hkClass*> m_map;
		#endif
};


#endif // HK_VTABLE_CLASS_REGISTRY_H

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
