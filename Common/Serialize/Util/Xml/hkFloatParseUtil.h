/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_FLOAT_PARSE_UTIL_H
#define HK_FLOAT_PARSE_UTIL_H

#include <Common/Base/Container/SubString/hkSubString.h>

/// A utility useful for writing and reading. In particular it handles
/// Nan/Inf etc.
class hkFloatParseUtil
{
	public:

		enum Type
		{
			// Keep in order - else tables will be wrong
			TYPE_NEG_INF,
			TYPE_INF,
			TYPE_NEG_NAN,
			TYPE_NAN,
			TYPE_IND, ///< Indeterminate
			TYPE_FINITE,

			TYPE_COUNT_OF,		// End marker
		};

			/// Get the type of floating point number
		static Type HK_CALL getFloatType(hkFloat32 f);
		static Type HK_CALL getFloatType(hkDouble64 f);

			/// Returns true if the numbers are 'equal'; they are identical either if they are finite
			/// or if they are the same type.
		static bool HK_CALL equals(hkFloat32 a, hkFloat32 b);
		static bool HK_CALL equals(hkDouble64 a, hkDouble64 b);

			/// Write a float to the buf
		static void HK_CALL calcFloatText(hkFloat32 a, hkStringBuf& buf);
		static void HK_CALL calcFloatText(hkDouble64 a, hkStringBuf& buf);

			/// Gets a float as text, and stores in buf. Makes sure the number has a decimal point in it
		static void HK_CALL calcFloatTextWithPoint(hkFloat32 a, hkStringBuf& buf);
		static void HK_CALL calcFloatTextWithPoint(hkDouble64 a, hkStringBuf& buf);

			/// Parses the float from the substring
		static hkResult HK_CALL parseFloat(const hkSubString& str, hkReal& value);

			/// Get a float of the type
		HK_FORCE_INLINE static hkReal HK_CALL getFloatFromType(Type type) { return *(hkReal*)&s_valuesLut[type]; }

		//static void HK_CALL findTypeRanges();

	protected:

#if defined(HK_REAL_IS_DOUBLE)
		static const hkUint64 s_valuesLut[];
#else
		static const hkUint32 s_valuesLut[];
#endif
};

#endif // HK_PARSER_BUFFER_H

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
