/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKBASE_HKUTF8_H
#define HKBASE_HKUTF8_H


	/// Utf8 string utilities.
namespace hkUtf8
{
	typedef hkUint32 CodePoint;

		/// Return the number of codepoints in this utf8 string.
	int strLen(const char* utf8);

		/// Convert a single codepoint to utf8. Returns the number of bytes needed to encode this codepoint.
	int utf8FromWide( char dst[4], wchar_t src );

		/// Convert from wide to utf8. src may be null terminated and/or a limit on the number of source characters may be supplied.
		/// At most dstSize bytes are written into dst and if dstSize is nonzero, dst is always null terminated.
		/// The buffer size required to hold the null terminated utf8 is returned in any case.
	int utf8FromWide( char* dst, int dstSize, const wchar_t* src, int srcCount=-1);

		/// Helper to hold a temporary utf8 encoded version of a wide string.
	class Utf8FromWide // todo: inherit stringbuf?
	{
		public:

			HK_DECLARE_PLACEMENT_ALLOCATOR();

				/// Create a converter.
			Utf8FromWide(const wchar_t* s);

			#if defined(_MANAGED)
				Utf8FromWide(System::String^ s);
			#endif

				/// Access the null or null terminated utf8 string.
			const char* cString() const { return m_utf8.begin(); }
				/// Access the null or null terminated wide string.
			operator const char*() const { return m_utf8.begin(); }

		private:

				// Invariant: m_utf8.getSize() is the number of bytes in the utf8 encoding.
				// If not null, there is a null "past-the-end".
			hkArray<char>::Temp m_utf8;
	};

		/// Helper to hold a temporary "wide" encoded version of a utf8 string.
	class WideFromUtf8
	{
		public:

			HK_DECLARE_PLACEMENT_ALLOCATOR();

				/// Create a converter.
			WideFromUtf8(const char* utf8);

				/// Access the null or null terminated wide string.
			const wchar_t* cString() const { return m_wide.begin(); }
				/// Access the null or null terminated wide string.
			operator const wchar_t*() const { return m_wide.begin(); }

			#if defined(_MANAGED)
				/// Convert Utf8 to wide managed String
				operator System::String^() const;
			#endif

				/// Internal access. The array size is the number of non-null characters. It is the users responsibility
				/// to ensure that the element past the end is null. e.g. by calling pushBack(0) then popBack();
			hkArray<wchar_t>::Temp& getArray() { return m_wide; }
		private:
 				// Invariant: m_wide.getSize() is the number of codepoints
				// If not null, there is a null "past-the-end".
			hkArray<wchar_t>::Temp m_wide;
	};

		/// Walk over the codepoints of a utf8 encoded string.
		/// Note that there is no isValid() method : the iterator starts in an invalid state
		/// and advance() must be called before current().
	class Iterator
	{
		public:
			HK_DECLARE_PLACEMENT_ALLOCATOR();

				/// Create an iterator.
			Iterator(const char* s) : m_utf8( reinterpret_cast<const hkUint8*>(s) ), m_current( CodePoint(-1) ) {}

				/// Return the current codepoint.
			CodePoint current() { return m_current; }

				/// Move to the next codepoint, returning false if there are no more codpoints and true otherwise.
				/// If non-null the number of bytes consumed is written into lenOut.
				/// If there is an encoding error we still return true and U+FFFD (REPLACEMENT CHARACTER) will be returned from current().
			bool advance(int* lenOut=HK_NULL);

		private:

			const hkUint8* m_utf8;
			CodePoint m_current;
	};
}

#endif // HKBASE_HKUTF8_H

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
