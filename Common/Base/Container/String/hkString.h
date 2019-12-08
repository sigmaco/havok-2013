/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKBASE_HKSTRING_H
#define HKBASE_HKSTRING_H

/// String and buffer functions normally found in libc.
namespace hkString
{
		/// Parameter to hkString::replace functions
	enum ReplaceType
	{
		REPLACE_ONE,
		REPLACE_ALL
	};

		/// Return the upper case of character c
	char HK_CALL toUpper( char c );
		/// Return the lower case of character c
	char HK_CALL toLower( char c );

		/// Equivalent to sprintf except at most n characters are written.
	int HK_CALL snprintf(char* buf, int n, const char* fmt, ...);
		/// Equivalent to snprintf, but with a va_list of arguments.
	int HK_CALL vsnprintf(char* buf, int len, const char* fmt, hk_va_list hkargs);
		/// Printf formatting to a string buffer.
	int HK_CALL sprintf(char* buf, const char* fmt, ...);

		/// Returns <=1,0,>=1 if s1 is lexicographically less than, equal to or greater than s2.
	int HK_CALL strCmp(const char* s1, const char* s2 );
		/// Returns <=1,0,>=1 if s1 is lexicographically less than, equal to or greater than s2. Comparison is done using at most the first n characters.
	int HK_CALL strNcmp(const char* s1, const char* s2, int n);
		/// Returns <=1,0,>=1 if s1 is lexicographically less than, equal to or greater than s2, ignoring case.
	int HK_CALL strCasecmp(const char* s1, const char* s2 );
		/// Returns <=1,0,>=1 if s1 is lexicographically less than, equal to or greater than s2, ignoring case. Comparison is done using at most the first n characters.
	int HK_CALL strNcasecmp(const char* s1, const char* s2, int n);
		/// Copy null terminated src into dst. dst must be large enough to hold src.
	void HK_CALL strCpy(char* dst, const char* src);
		/// Copy at most n characters of null terminated src into dst. DST must be large enough to hold src.
	void HK_CALL strNcpy(char* dst, const char* src, int n);
		/// Return the length of null terminated string src.
	int HK_CALL strLen(const char* src);
		/// Appends a copy of the source string to the destination string.
	void HK_CALL strCat(char* dst, const char* src);
		/// Appends the first n characters of source to destination, plus a terminating null-character.
	void HK_CALL strNcat(char* dst, const char* src, int n);

		/// Return an integer representing the string (signed, undefined for invalid input).
		/// If a base of 0 is specified atoi will attempt to determine the base from string prefix e.g. '0' for octal 'Ox' or 'OX' for hex
	int HK_CALL atoi(const char* in, int base = 0);
		/// Return a 64-bit integer representing the string (signed, undefined for invalid input).
		/// If a base of 0 is specified atoll will attempt to determine the base from string prefix e.g. '0' for octal 'Ox' or 'OX' for hex
	hkInt64 HK_CALL atoll(const char* in, int base = 0);
		/// Return a 64 bits integer representing the string (unsigned, undefined for invalid input).
		/// If a base of 0 is specified atoll will attempt to determine the base from string prefix e.g. '0' for octal 'Ox' or 'OX' for hex
	hkUint64 HK_CALL atoull(const char* in, int base = 0);
		/// Return a hkReal representing the string.
	hkReal HK_CALL atof(const char* in); 

		/// Return the first occurrence of needle in haystack or null if not found.
	const char* HK_CALL strStr(const char* haystack, const char* needle);
		/// Find all the occurrences of needle in haystack and put their start indices in the array.
		/// Return true if at least one was found.
	hkBool HK_CALL findAllOccurrences(const char* haystack, const char* needle, hkArray<int>& indices, hkString::ReplaceType rtype);
		/// Return the first occurrence of needle in haystack or null if not found.
	const char* HK_CALL strChr(const char* haystack, int needle);
		/// Return the last occurrence of needle in haystack or null if not found.
	const char* HK_CALL strRchr(const char* haystack, int needle);

	hkBool HK_CALL beginsWith(const char* str, const char* prefix);
	hkBool HK_CALL beginsWithCase(const char* str, const char* prefix);
	hkBool HK_CALL endsWith(const char* str, const char* suffix);
	hkBool HK_CALL endsWithCase(const char* str, const char* suffix);
	int HK_CALL lastIndexOf(const char* str, char c);
		/// Start and end are inclusive and exclusive ranges respectively.
	int HK_CALL indexOf(const char* str, char c, int startIndex=0, int endIndex=HK_INT32_MAX);

		/// Return a copy of string src. This copy is allocated using hkAllocate<char> and therefore it should be deallocated using hkDeallocate<char>
	char* HK_CALL strDup(const char* src, hkMemoryAllocator& a);
		/// Return a copy of at most maxlen characters of src.
	char* HK_CALL strNdup(const char* src, int maxlen, hkMemoryAllocator& a);
		///
	void HK_CALL strFree(char* s, hkMemoryAllocator& a);
	void HK_CALL strFree(char* s);

		/// Return a copy of string src. This copy is allocated using hkAllocate<char> and therefore it should be deallocated using hkDeallocate<char>
	char* HK_CALL strDup(const char* src);
		/// Return a copy of at most maxlen characters of src.
	char* HK_CALL strNdup(const char* src, int maxlen);
		/// Change src to lower case in place.
	char* HK_CALL strLwr(char* src);
		/// Change src to upper case in place.
	char* HK_CALL strUpr(char* src);

		/// Copy n bytes of src into dst.
	void HK_CALL memCpy(void* dst, const void* src, int n);
		/// Copy n words of src into dst.
	HK_FORCE_INLINE void HK_CALL memCpy4(void* dst, const void* src, int numWords);
		/// Copy n quad words of src into dst.
	HK_FORCE_INLINE void HK_CALL memCpy16(void* dst, const void* src, int numQuads);

		/// Super fast copy of a constant size less than 128 bytes
	template<int size>
	HK_FORCE_INLINE void HK_CALL memCpy16(void* dst, const void* src);

		/// Copy n quad words of src into dst. n must be greater than 0
	HK_FORCE_INLINE void HK_CALL memCpy16NonEmpty(void* dst, const void* src, int numQuads);
		/// Copy 128 bytes of src into dst.
	HK_FORCE_INLINE void HK_CALL memCpy128(void* dst, const void* src);
		/// Copy 256 bytes of src into dst.
	HK_FORCE_INLINE void HK_CALL memCpy256(void* dst, const void* src);
		/// Copy n bytes of src into dst, possibly overlapping.
	void HK_CALL memMove(void* dst, const void* src, int n);
		/// Set n bytes of dst to c.
	void HK_CALL memSet(void* dst, const int c, int nBytes);

		/// Set n*4 bytes to c
	HK_FORCE_INLINE void HK_CALL memSet4(void* dst, const int value, int numWords);

		/// Set n*16 bytes to 0
	HK_FORCE_INLINE void HK_CALL memClear16(void* dst, int numQuads);

		/// Clear a multiple of 128 bytes which are 128 byte aligned
	void HK_CALL memClear128(void* dst, int numBytes);

		/// Set n*16 bytes to c
	HK_FORCE_INLINE void HK_CALL memSet16(void* dst, const void* value, int numQuads);

		/// Set n*16 bytes to c.
		/// Size must be positive and a multiple of 16
	template<int size>
	HK_FORCE_INLINE void HK_CALL memSet16(void* dst, const void* src);

		/// Returns a negative number,  0  or positive number  if n bytes of buf1 is less than, equal to or greater than those of buf2.
	int HK_CALL memCmp(const void* buf1, const void* buf2, int n);

		/// Returns a negative number,  0  or positive number  if n hkUint32 of buf1 is less than, equal to or greater than those of buf2.
	HK_FORCE_INLINE int HK_CALL memCmpUint32(const hkUint32* buf1, const hkUint32* buf2, int n);
}

#	define HK_PRINTF_FORMAT_INT64_SIZE	"I64"

#	define HK_PRINTF_FORMAT_INT64		"%" HK_PRINTF_FORMAT_INT64_SIZE "i"
#	define HK_PRINTF_FORMAT_UINT64		"%" HK_PRINTF_FORMAT_INT64_SIZE "u"

#if HK_POINTER_SIZE==4
#	define HK_PRINTF_FORMAT_ULONG "%u"
#else
#	define HK_PRINTF_FORMAT_ULONG HK_PRINTF_FORMAT_UINT64
#endif

#include <Common/Base/Container/String/hkString.inl>

#endif // HKBASE_HKSTRING_H

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
