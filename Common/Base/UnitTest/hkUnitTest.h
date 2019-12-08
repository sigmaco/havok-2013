/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_BASE_UNITTEST_H
#define HK_BASE_UNITTEST_H

#include <Common/Base/Config/hkConfigVersion.h>
#include <Common/Base/System/Error/hkDefaultError.h>
#include <Common/Base/System/Error/hkFilterError.h>
#include <Common/Base/Container/String/hkStringBuf.h>
#include <Common/Base/Config/hkConfigThread.h>



//
//	Test report function type

typedef hkBool (HK_CALL *hkTestReportFunctionType)(hkBool32 cond, const char* desc, const char* file, int line);

/************* PUBLIC *******************/
#define HK_TEST(CONDITION)  (*hkTestReportFunction)( (CONDITION), #CONDITION, __FILE__, __LINE__)
#define HK_TEST_EQ(A,B) hkTestReportEq((A), (B), #A, #B, __FILE__, __LINE__);

#define HK_TEST2(CONDITION,DESCRIPTION)  do {	\
	char msgBuf[512];								\
	hkOstream msg(msgBuf, sizeof(msgBuf), true);	\
	msg << #CONDITION  << " (" << DESCRIPTION << ')'; \
	(*hkTestReportFunction)( (CONDITION), msgBuf, __FILE__, __LINE__); \
} while(0)

#define HK_TEST_REGISTER(func, category, menu, path) extern const hkTestEntry register##func = { func, #func, category, menu path }


// Macro needed to prevent namespace errors caused by CodeWarrior #defining setjmp as ::std::__setjmp
#if defined(HK_PLATFORM_RVL) || defined(HK_PLATFORM_ANDROID) || defined(HK_PLATFORM_WIIU) || ( defined(HK_PLATFORM_WINRT) && defined(HK_ARCH_ARM) )
#define HK_SETJMP(JUMP)	setjmp((JUMP))
#else
#define HK_SETJMP(JUMP)	HK_STD_NAMESPACE::setjmp((JUMP))
#endif


// Macro used to test if an specific error message is raised during the execution of a statement and fail
// the test if it is not. This version will restore the program state after receiving the message, and will
// not execute any code after the message is raised.
#define HK_TEST_MESSAGE(MSG_TYPE, ID, STATEMENT, DESCRIPTION)  do { \
	hkFilterError filterError; \
	hkFilterError::jumpbuf jumpBuffer; \
	if (HK_SETJMP(jumpBuffer) == 0) \
	{ \
		filterError.install(MSG_TYPE, ID, &jumpBuffer); \
		STATEMENT; \
	} \
	filterError.uninstall(); \
	HK_TEST2(filterError.wasMessageRaised(), DESCRIPTION); \
} while(0)

// Macro used to test if an specific error message is raised during the execution of a statement and fail
// the test if it is not. This version continue execution after the message is raised.
#define HK_TEST_MESSAGE_AND_CONTINUE(MSG_TYPE, ID, STATEMENT, DESCRIPTION)  do { \
	hkFilterError filterError; \
	filterError.install(MSG_TYPE, ID); \
	STATEMENT; \
	filterError.uninstall(); \
	HK_TEST2(filterError.wasMessageRaised(), DESCRIPTION); \
} while(0)


#define HK_TEST_ERROR(ID, STATEMENT)	HK_TEST_MESSAGE(hkError::MESSAGE_ERROR, ID, STATEMENT, "Error " #ID " not triggered.")
#define HK_TEST_ERROR2(ID, STATEMENT, DESCRIPTION)	HK_TEST_MESSAGE(hkError::MESSAGE_ERROR, ID, STATEMENT, DESCRIPTION)

#if !defined(HK_PLATFORM_CTR) && defined(HK_DEBUG)
#	define HK_TEST_ASSERT(ID, STATEMENT)	HK_TEST_MESSAGE(hkError::MESSAGE_ASSERT, ID, STATEMENT, "Assert " #ID " not triggered.")
#	define HK_TEST_ASSERT2(ID, STATEMENT, DESCRIPTION)	HK_TEST_MESSAGE(hkError::MESSAGE_ASSERT, ID, STATEMENT, DESCRIPTION)
#	define HK_TEST_ASSERT_AND_CONTINUE(ID, STATEMENT)	HK_TEST_MESSAGE_AND_CONTINUE(hkError::MESSAGE_ASSERT, ID, STATEMENT, "Assert " #ID " not triggered.")
#	define HK_TEST_ASSERT_AND_CONTINUE2(ID, STATEMENT, DESCRIPTION)	HK_TEST_MESSAGE_AND_CONTINUE(hkError::MESSAGE_ASSERT, ID, STATEMENT, DESCRIPTION)
#	define HK_ON_TEST_ASSERT_ENABLED(STATEMENT) STATEMENT
#else	// no asserts in debug
#	define HK_TEST_ASSERT(ID, STATEMENT)
#	define HK_ON_TEST_ASSERT_ENABLED(STATEMENT)
#	define HK_TEST_ASSERT2(ID, STATEMENT, DESCRIPTION)	
#	define HK_TEST_ASSERT_AND_CONTINUE(ID, STATEMENT)
#	define HK_TEST_ASSERT_AND_CONTINUE2(ID, STATEMENT, DESCRIPTION)
#endif



//
//	Test report function pointer

extern hkTestReportFunctionType hkTestReportFunction;


	template <class T>
	inline void hkTestReportEq(const T& l, const T& r, const char* left, const char* right, const char* file, int line)
	{
		if (!(l == r))
		{
			char buf[512];
			hkOstream s(buf, 512, true);
			s<<left<<" {"<<l<<"} == "<<right<<" {"<<r<<"}";
			s.flush();
			(*hkTestReportFunction)(false, buf, file, line);
		}
	}


/************* INTERNAL USE ONLY *******************/


struct hkTestEntry
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE_CLASS, hkTestEntry );
	typedef int (HK_CALL *hkTestFunction)();

	hkTestFunction m_func;
	const char* m_name;
	const char* m_category;
	const char* m_path;
};
extern const hkTestEntry* hkUnitTestDatabase[];

class TestDemo;

#define HK_REGRESSION_REPORT(NAME, TYPE, VALUE)	HK_MULTILINE_MACRO_BEGIN				\
	char reportBuf[512];																\
	hkErrStream ostr(reportBuf,sizeof(reportBuf));										\
	ostr << "[REGRESSION:" << NAME << ":" << TYPE << ":" << VALUE << "]";				\
	hkError::messageReport(0, reportBuf, HK_NULL, 0);									\
	HK_MULTILINE_MACRO_END

#define HK_REGRESSION_CHECK_RANGE(NAME, TYPE, VALUE, MINVALUE, MAXVALUE)	HK_MULTILINE_MACRO_BEGIN																			\
	char reportBuf[512];																				\
	hkErrStream ostr(reportBuf,sizeof(reportBuf));														\
	if ((VALUE >= MINVALUE) && ( VALUE <= MAXVALUE ))													\
{																										\
	ostr << "[REGRESSION:" << NAME << ":" << TYPE << ":" << VALUE << "]";								\
	hkError::messageReport(0, reportBuf, HK_NULL, 0);													\
}																										\
																			else						\
{																										\
	ostr << "[REGRESSION FAILED:" << NAME << ":" << TYPE << ":" << VALUE << ": Range(" << MINVALUE << "," << MAXVALUE << ") ]"; \
	hkError::messageError(-1, reportBuf, __FILE__, __LINE__);									 		\
}																										\
	HK_MULTILINE_MACRO_END


class hkUnitTest
{
public:
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_DEMO, hkUnitTest);

	static hkUint32 randSeed;

	static hkUint32 HK_CALL rand();
	static hkReal HK_CALL rand01();
	static inline hkReal HK_CALL randRange(hkReal minv, hkReal maxv)
	{
		return minv + rand01() * (maxv-minv);
	}

#if (HK_CONFIG_THREAD == HK_CONFIG_MULTI_THREADED)
	static class hkJobQueue* s_jobQueue;
	static class hkJobThreadPool* s_jobThreadPool ;
#endif
};


#endif // HK_TEST_UNITTEST_REGISTERTEST_H

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
