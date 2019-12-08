/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_FILTER_ERROR
#define HK_FILTER_ERROR

#include <Common/Base/System/hkBaseSystem.h>
#include <Common/Base/Container/PointerMap/hkPointerMap.h>

#include <Common/Base/Fwd/hkstandardheader.h>
#if !defined(HK_PLATFORM_ANDROID) && !defined(__HAVOK_PARSER__)
#include HK_STANDARD_HEADER(setjmp)
#else
#include <setjmp.h>
#endif

#if defined HK_COMPILER_MSVC
// C4611 interaction between '_setjmp' and C++ object destruction is non-portable
// yes we know.
#	pragma warning(disable: 4611)
#endif

/// Error handler used to filter a specific error message, optionally transferring execution to a given jump location.
/// All other messages and method calls are forwarded to the previously installed error handler.
class hkFilterError : public hkError
{
	//+hk.MemoryTracker(ignore=True)
public:
	typedef HK_STD_NAMESPACE::jmp_buf jumpbuf;
	HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);

	hkFilterError() : m_prevHandler(HK_NULL) {}	

	/// Replaces current error handler instance while maintaining a reference to it to forward 
	/// all calls that are not filtered. If a jumpBuffer is provided, the jumpBuffer must be valid
	/// while the filter is installed, i.e. the function where the call to setjmp was performed must not have returned.
	void install(Message m, int id, jumpbuf* jumpBuffer = HK_NULL);

	/// Recovers the original error handler instance
	void uninstall();

	/// Returns whether or not the message in question has been raised
	hkBool wasMessageRaised() const { return m_messageRaised; }

	/// Return value indicates whether or not to trigger an HK_BREAKPOINT for errors and asserts.
	virtual int message(Message m, int id, const char* description, const char* file, int line);

	/// Enables/disables diagnostic by id.
	virtual void setEnabled(int id, hkBool enabled);

	/// Enables/disables diagnostic by id.
	virtual hkBool isEnabled(int id);

	/// Force all diagnostics to be enabled.
	virtual void enableAll();

	/// Begin a new report section
	virtual void sectionBegin(int id, const char* sectionName);

	/// End the current report section
	virtual void sectionEnd();

private:

	hkError* m_prevHandler;
	jumpbuf* m_jumpBuffer;
	Message m_message;
	int m_id;
	hkBool m_messageRaised;
};

#endif // HK_FILTER_ERROR

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
