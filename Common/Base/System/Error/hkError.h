/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKBASE_HKERROR_H
#define HKBASE_HKERROR_H


/// Class with static methods to provide hooks to error reporting functions.
/// You can redirect all asserts, errors and warnings by setting the handlers
/// at run time. Asserts and Warnings are only compiled into debug builds.
/// Errors are compiled in all builds. See hkDefaultError.h for a sample implementation
/// of the handlers.
class hkError : public hkReferencedObject, public hkSingleton<hkError>
{
	public:
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
		enum Message
		{
				/// Pass to setMinimumMessageLevel to ensure all messages are handled.
			MESSAGE_ALL,

				/// Diagnostic reports
			MESSAGE_REPORT = MESSAGE_ALL,
			
				/// Warnings: maybe be important e.g. for performance but not critical
			MESSAGE_WARNING,

				/// Asserts: indicates an error condition. Ignoring these may crash soon afterwards or corrupt data.
			MESSAGE_ASSERT,

				/// Error: unable to continue.
			MESSAGE_ERROR,

				/// Pass to setMinimumMessageLevel to ignore all messages.
			MESSAGE_NONE,
		};

			/// Return value indicates whether or not to trigger an HK_BREAKPOINT for errors and asserts.
		virtual int message(Message m, int id, const char* description, const char* file, int line) = 0;

			/// Enables/disables diagnostic by id.
		virtual void setEnabled( int id, hkBool enabled ) = 0;

			/// Check whether diagnostic is enabled/disabled by id.
		virtual hkBool isEnabled( int id ) = 0;

			/// Sets the minimum message level. Messages below this level are ignored.
		virtual void setMinimumMessageLevel( Message msg ) {}

			/// Check whether diagnostic is enabled/disabled by Message type.
		virtual Message getMinimumMessageLevel() { return MESSAGE_ALL; }

			/// Force all diagnostics to be enabled.
		virtual void enableAll() = 0;

			/// Begin a new report section
		virtual void sectionBegin(int id, const char* sectionName) {}

			/// End the current report section
		virtual void sectionEnd() {}

			/// Out-of-line helper methods to reduce code size
		static int HK_CALL messageReport(int id, const char* description, const char* file, int line);
		static int HK_CALL messageWarning(int id, const char* description, const char* file, int line);
		static int HK_CALL messageAssert(int id, const char* description, const char* file, int line);
		static int HK_CALL messageError(int id, const char* description, const char* file, int line);
};


	/// convenience class to disable one error id within a scope
class hkDisableError
{
	public:
		hkDisableError( int id )
		{
			hkError& error = hkError::getInstance();
			m_id = id;
			m_wasEnabled = error.isEnabled( id );
			error.setEnabled( id, false );
		}
		~hkDisableError()
		{
			hkError& error = hkError::getInstance();
			error.setEnabled( m_id, m_wasEnabled );
		}

	public:
		int m_id;
		hkBool m_wasEnabled;
};

class hkErrStream : public hkOstream
{
	public:
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
		hkErrStream( void* buf, int bufSize );
};
typedef void (HK_CALL *hkErrorReportFunction)(const char* s, void* errorReportObject);

namespace hkCompileError
{
	// -- Error types -- //

		// Generic compile time failure
	template <bool b> struct COMPILE_ASSERTION_FAILURE;
	template <> struct COMPILE_ASSERTION_FAILURE<true>{ };

		// The reflection parser and the compile time check disagree about whether a class has a vtable.
		// The script may not have detected that a class has a vtable. e.g. no virtual methods
		// declared in the body. In this case add //+virtual(true) at the start of the class definition.
		// Otherwise, the compile time vtable check may have failed if the object does not inherit from hkBaseObject.
		// In this case, you can mark the base class as virtual by adding the declaration
		// "hkBool::YesType hkIsVirtual(MyClass*);" after the class definition. A function body is not needed.
	template <bool b> struct REFLECTION_PARSER_VTABLE_DETECTION_FAILED;
	template <> struct REFLECTION_PARSER_VTABLE_DETECTION_FAILED<true>{ };

	// -- Assert struct used for typedefs -- //
	template <int x> struct StaticAssertTest {};
}

/// Cause a compile error if the assert fails.
#define HK_COMPILE_TIME_ASSERT(a) \
	typedef hkCompileError::StaticAssertTest< sizeof(hkCompileError::COMPILE_ASSERTION_FAILURE< static_cast<bool>(a) >) > \
	HK_PREPROCESSOR_JOIN_TOKEN(hkStaticAssertTypedef, __LINE__)

/// Compile time assert with an error message.
/// The MSG argument should give a hint about why the assert failed as the cause may not be apparent
/// from the compile error. MSG should be defined in the hkCompileError namespace.
#define HK_COMPILE_TIME_ASSERT2(a,MSG) \
	typedef hkCompileError::StaticAssertTest< sizeof(hkCompileError::MSG< static_cast<bool>(a) >) > \
	HK_PREPROCESSOR_JOIN_TOKEN(hkStaticAssertTypedef, __LINE__)

#define HK_REPORT_SECTION_BEGIN(id, name)	hkError::getInstance().sectionBegin(id, name);

#define HK_REPORT_SECTION_END()				hkError::getInstance().sectionEnd();


#define HK_CURRENT_FILE __FILE__

// asserts and warnings may be compiled out

#	define HK_WARN_ALWAYS(id, TEXT)		HK_MULTILINE_MACRO_BEGIN													\
	char assertBuf[512];																							\
	hkErrStream ostr(assertBuf, sizeof(assertBuf));																	\
	ostr << TEXT;																									\
	hkError::messageWarning(id, assertBuf, HK_CURRENT_FILE, __LINE__);														\
	HK_MULTILINE_MACRO_END


#	define HK_ERROR(id, TEXT)			HK_MULTILINE_MACRO_BEGIN																						\
										char assertBuf[512];																							\
										hkErrStream ostr(assertBuf,sizeof(assertBuf));																	\
										ostr << TEXT;																									\
										if ( hkError::messageError(id, assertBuf, HK_CURRENT_FILE, __LINE__) )													\
										{																												\
											HK_BREAKPOINT(id);																							\
										}																												\
										HK_MULTILINE_MACRO_END

#	define HK_REPORT(TEXT)				HK_MULTILINE_MACRO_BEGIN																						\
										char reportBuf[512];																							\
										hkErrStream ostr(reportBuf,sizeof(reportBuf));																	\
										ostr << TEXT;																									\
										hkError::messageReport(-1, reportBuf, HK_CURRENT_FILE, __LINE__);														\
										HK_MULTILINE_MACRO_END

#	define HK_REPORT2(id, TEXT)			HK_MULTILINE_MACRO_BEGIN																						\
										char reportBuf[512];																							\
										hkErrStream ostr(reportBuf,sizeof(reportBuf));																	\
										ostr << TEXT;																									\
										hkError::messageReport(id, reportBuf, HK_CURRENT_FILE, __LINE__);														\
										HK_MULTILINE_MACRO_END

#	define HK_TRACE(TEXT)				HK_MULTILINE_MACRO_BEGIN																						\
										char reportBuf[512];																							\
										hkErrStream ostr(reportBuf,sizeof(reportBuf));																	\
										ostr << TEXT;																									\
										hkError::messageReport(0, reportBuf, HK_NULL, HK_NULL);															\
										HK_MULTILINE_MACRO_END

#	if defined HK_DEBUG // NOSPU + DEBUG

// Branch prediction will assume the positive branch is more likely to be taken

#		define HK_ASSERT(id, a)			HK_MULTILINE_MACRO_BEGIN 																						\
										if ( HK_VERY_LIKELY(a) )																						\
										{																												\
										}																												\
										else																											\
										{																												\
											if( hkError::messageAssert( id, #a, HK_CURRENT_FILE,__LINE__) )													\
											{																											\
												HK_BREAKPOINT(0);																						\
											}																											\
										}																												\
										HK_MULTILINE_MACRO_END

#		define HK_ASSERT2(id, a, TEXT)	HK_MULTILINE_MACRO_BEGIN 																						\
										if ( HK_VERY_LIKELY(a) )																						\
										{																												\
										}																												\
										else																											\
										{																												\
											if( hkError::messageAssert( id, TEXT, HK_CURRENT_FILE, __LINE__) )													\
											{																											\
												HK_BREAKPOINT(0);																						\
											}																											\
										}																												\
										HK_MULTILINE_MACRO_END

#		define HK_ASSERT3(id, a, ARGS)	HK_MULTILINE_MACRO_BEGIN 																						\
										if ( HK_VERY_LIKELY(a) )																						\
										{																												\
										}																												\
										else																											\
										{																												\
											char assertBuf[512];																						\
											hkErrStream ostr(assertBuf, sizeof(assertBuf));																\
											ostr << #a << "\n";																							\
											ostr << ARGS;																								\
											if( hkError::messageAssert( id, assertBuf, HK_CURRENT_FILE, __LINE__) )												\
											{																											\
												HK_BREAKPOINT(0);																						\
											}																											\
										}																												\
										HK_MULTILINE_MACRO_END

#		define HK_WARN(id, TEXT)		HK_WARN_ALWAYS (id, TEXT)

#		define HK_WARN_ONCE(id, TEXT)	HK_MULTILINE_MACRO_BEGIN																						\
										if ( HK_VERY_LIKELY(!hkError::getInstance().isEnabled(id)) )													\
										{																												\
										}																												\
										else																											\
										{																												\
											char assertBuf[512];																						\
											hkErrStream ostr( assertBuf, sizeof(assertBuf) );															\
											ostr << TEXT;																								\
											hkError::messageWarning( id, assertBuf, HK_CURRENT_FILE, __LINE__);				\
											hkError::getInstance().setEnabled(id, false); 																\
										}																												\
										HK_MULTILINE_MACRO_END


#	else	// NOSPU + RELEASE

#		define HK_WARN(id, a)				//nothing
#		define HK_WARN_ONCE(id, a)			//nothing
#		define HK_ASSERT(id, a)				//nothing 
#		define HK_ASSERT2(id, a, TEXT)		//nothing 
#		define HK_ASSERT3(id, a, TEXT)		//nothing 
#	endif	


// A dedicated assert to be used in math functions.
// For now this will simply forward to a regular HK_ASSERT.
#define HK_MATH_ASSERT(id, a, TEXT) HK_ASSERT(id, a)

// Critical asserts - these will trigger breakpoints on the SPU. Additionally, they show up as comments in the assembly file.
//	On non-SPU platforms, they revert to normal asserts.
#	define HK_CRITICAL_ASSERT  HK_ASSERT
#	define HK_CRITICAL_ASSERT2 HK_ASSERT2

#if (HK_NATIVE_ALIGNMENT==16) && !defined(HK_ALIGN_RELAX_CHECKS)
	#define HK_CHECK_ALIGN_NATIVE(ADDR) HK_ASSERT(0xff00ff00, (hkUlong(ADDR) & 0xF) == 0 )
#elif (HK_NATIVE_ALIGNMENT==8) && !defined(HK_ALIGN_RELAX_CHECKS)
	#define HK_CHECK_ALIGN_NATIVE(ADDR) HK_ASSERT(0xff00ff00, (hkUlong(ADDR) & 0x7) == 0 )
#else // 4
	#define HK_CHECK_ALIGN_NATIVE(ADDR) HK_ASSERT(0xff00ff00, (hkUlong(ADDR) & 0x3) == 0 )
#endif
#define HK_CHECK_ALIGN16(ADDR) HK_ASSERT(0xff00ff00, (hkUlong(ADDR) & HK_NATIVE_ALIGN_CHECK) == 0 )
#if defined(HK_ALIGN_RELAX_CHECKS) || defined(HK_PLATFORM_IOS_SIM)
// Some ARM platforms will only actually align on 8 bytes. This is ok as they also accept 8-byte aligned vectors
#define HK_CHECK_ALIGN_REAL(ADDR) HK_ASSERT(0xff00ff00, (hkUlong(ADDR) & (8-1)) == 0 )
#else
#define HK_CHECK_ALIGN_REAL(ADDR) HK_ASSERT(0xff00ff00, (hkUlong(ADDR) & (HK_REAL_ALIGNMENT-1)) == 0 )
#endif

#define HK_WARN_ON_DEBUG_IF(check,id,TEXT)		HK_ON_DEBUG(if (check) HK_WARN(id,TEXT))
#define HK_WARN_ONCE_ON_DEBUG_IF(check,id,TEXT)	HK_ON_DEBUG(if (check) HK_WARN_ONCE(id,TEXT))

#endif // HKBASE_HKERROR_H

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
