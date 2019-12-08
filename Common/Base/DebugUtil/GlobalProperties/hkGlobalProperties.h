/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKBASE_GLOBAL_PROPERTIES_H
#define HKBASE_GLOBAL_PROPERTIES_H

#include <Common/Base/Container/PointerMap/hkPointerMap.h>

	/// This class is used to debug the internal core of Havok.
	/// This class in not intended to be used by clients yet.
	/// This is a draft impl. meant to be rewritten.
class hkGlobalProperties : public hkReferencedObject, public hkSingleton<hkGlobalProperties>
{
	public:
	
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);

		typedef hkPointerMap<const void*, const void*> Storage;

		hkGlobalProperties();
		
		~hkGlobalProperties();
		
		void		set(const void* key, const void* value);

		const void*	get(const void* key, const void* defaultValue);

		void		clear(const void* key);

		Storage						m_data;
		class hkCriticalSection*	m_lock;
};


#endif // HKBASE_GLOBAL_PROPERTIES_H

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
