/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_DATA_OBJECT_DECLARATIONS_H
#define HK_DATA_OBJECT_DECLARATIONS_H

#include <Common/Serialize/TypeManager/hkTypeManager.h>

class hkDataObject;
class hkDataArray;
class hkDataClass;
class hkDataWorld;

class hkDataObjectImpl;
class hkDataArrayImpl;
class hkDataClassImpl;

// Opaque handle for accessing members of an object
struct _hkDataObject_MemberHandle;
typedef const _hkDataObject_MemberHandle* hkDataObject_MemberHandle;
typedef int hkDataObject_Iterator;
typedef hkTypeManager::Type* hkDataObject_Type;

class hkDataObject_Value;
struct hkStridedBasicArray;

/// This structure is used to describe a member of hkDataClass.
struct hkDataClass_MemberInfo
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, hkDataClass_MemberInfo);

	hkDataClass_MemberInfo() : m_name(HK_NULL), m_owner(HK_NULL), m_type(HK_NULL), m_valuePtr(HK_NULL) {}
	const char* m_name;
	const hkDataClassImpl* m_owner;
	hkTypeManager::Type* m_type;
	const void *m_valuePtr;
};

	/// A handle which can be used to uniquely identify an object in a world.
	/// In contrast to implementation pointers, handles are persistent and provide
	/// a unique identity. They are particularly useful for native worlds since only
	/// the subset of data currently being examined needs to have a live wrapper.
struct hkDataObject_Handle
{ 
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE,hkDataObject_Handle);
		/// Use this as the "main" memento. Null here means the null object.
	void* p0;
		/// Optional extra data.
	void* p1;
	hkBool32 operator==(const hkDataObject_Handle& h) const { return p0 == h.p0 && p1 == h.p1; }
	hkBool32 operator!=(const hkDataObject_Handle& h) const { return p0 != h.p0 || p1 != h.p1; }
};



#endif // HK_DATA_OBJECT_DECLARATIONS_H

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
