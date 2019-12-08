/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_REGISTER_CHECK_UTIL_H
#define HK_REGISTER_CHECK_UTIL_H

#include <Common/Base/Thread/CriticalSection/hkCriticalSection.h>

class hkOstream;

/// Utility to determine if systems registered typically by _registerSelf methods, are actually used.
/// If the system is registered but never used, it is taking up resources which would be available
/// if it had not been registered.
///
/// In order to make a system able to report this information 3 things are in general are need.
/// 
/// 1) In the xxx_registerSelf method, use the macro HK_REGISTER_REGISTER_CHECK(systemName).
/// 2) Somewhere in that same file, before the registerSelf method, use the macro HK_IMPLEMENT_REGISTER_CHECK(systemName).
/// 3) In any methods that indicate the system has been used place HK_USE_REGISTER_CHECK(systemName).
class hkRegisterCheckUtil: public hkReferencedObject, public hkSingleton<hkRegisterCheckUtil>
{
public:
	HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);

	struct Info
	{
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, Info);

		friend class hkRegisterCheckUtil;
			/// Called to register the info (called when register is called)
		void registerSelf();
			/// Set used
		HK_FORCE_INLINE void setUsed() { m_used = true; if (!m_added) registerSelf(); }
			/// Get the name
		const char* getName() const { return m_name; }
			/// True if it has been used
		hkBool isUsed() const { return m_used; }

	//protected:

		const char* m_name;
		Info* m_next;
		hkBool m_used;
		hkBool m_added;
	};
		
		/// Add info
	void add(Info& info);
		/// Find all that are registered which haven't been used
	void findUnused(hkArray<Info*>& unused);
		/// Remove all 
	void removeAll();
		/// Set used
	void setUsed(Info& info);

		/// Dump out to the stream a list of systems which were registered, but not used
	void dumpUnused(hkOstream& stream);

		/// Ctor
	hkRegisterCheckUtil();
protected:
	hkCriticalSection m_criticalSection;
	Info* m_infos;
};



#define HK_DECLARE_REGISTER_CHECK(NAME) \
	extern hkRegisterCheckUtil::Info s_##NAME##RegisterCheck;

#define HK_IMPLEMENT_REGISTER_CHECK(NAME) \
	hkRegisterCheckUtil::Info s_##NAME##RegisterCheck = { #NAME, HK_NULL, false, false };

#define HK_REGISTER_REGISTER_CHECK(NAME) \
	s_##NAME##RegisterCheck.registerSelf();

#define HK_USE_REGISTER_CHECK(NAME) \
	s_##NAME##RegisterCheck.setUsed();


#endif // HK_REGISTER_CHECK_UTIL_H

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
