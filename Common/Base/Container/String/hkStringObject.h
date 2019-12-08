/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKBASE_HKSTRINOBJECT_H
#define HKBASE_HKSTRINOBJECT_H

#include <Common/Base/Types/hkBaseTypes.h>
#include <Common/Base/Container/String/hkStringPtr.h>

extern const hkClass hkStringObjectClass;

/// A serializable string wrapper
class hkStringObject : public hkReferencedObject
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
		HK_DECLARE_REFLECTION();

	public:

		/// Constructor
		hkStringObject(const char* str = HK_NULL)
		:	m_string(str)
		{}

		/// Serialization constructor
		hkStringObject(class hkFinishLoadedObjectFlag flag)
		:	hkReferencedObject(flag)
		,	m_string(flag)
		{}

	public:

		hkStringPtr m_string;
};

#endif	//	HKBASE_HKSTRINOBJECT_H

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
