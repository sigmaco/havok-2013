/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#ifndef HK_MATH_SIMD_INT_H
#define HK_MATH_SIMD_INT_H

#ifndef HK_MATH_LARGE_INT_TYPES_H
#	error Include Common/Base/Math/LargeInt/hkLargeIntTypes.h instead of this file!
#endif

/// Generic base class for a SIMD int on N bits, where N >= 128 is a power of 2.
template <int N>
class hkSimdInt
{
	//+hk.MemoryTracker(ignore=True)
	public:

		enum { NUM_BITS = N, };
		typedef hkSimdInt<N/2>			HalfInt;
		typedef const hkSimdInt<N/2>&	HalfIntParameter;

	public:

		/// Sets this = i
		inline void setFromInt32(hkInt32 i);

		/// Sets this = a & b
		inline void setAnd(const hkSimdInt<N>& a, const hkSimdInt<N>& b);

		/// Sets this = a | b
		inline void setOr(const hkSimdInt<N>& a, const hkSimdInt<N>& b);

		/// Sets this = ~a
		inline void setNot(const hkSimdInt<N>& a);

		/// Set this = abs(v)
		inline void setAbs(const hkSimdInt<N>& v);

		/// Sets this -v
		inline void setNeg(const hkSimdInt<N>& v);

		/// Sets this = this + 1
		inline void increment();

		/// Sets this = cmp ? vTrue : vFalse
		inline void setSelect(hkVector4fComparisonParameter cmp, const hkSimdInt<N>& vTrue, const hkSimdInt<N>& vFalse);

		/// Returns this == 0
		inline const hkVector4fComparison equalZero() const;

		/// Returns this < 0
		inline const hkVector4fComparison lessZero() const;

		/// Returns this == v
		inline const hkVector4fComparison equal(const hkSimdInt<N>& v);

		/// Returns this > 0
		inline const hkVector4fComparison greaterZero() const;

		/// Sets this = 0
		inline void setZero();

		/// Sets this = a << I
		template <int I>
		inline void setShiftLeft(const hkSimdInt<N>& v);
		inline void setShiftLeft(const hkSimdInt<N>& v, int shl);

		/// Sets this = a >> shr
		template <int I>
		inline void setShiftRight(const hkSimdInt<N>& v);
		inline void setShiftRight(const hkSimdInt<N>& v, int shr);

		/// Sets this = sign * v
		inline void setFlipSign(const hkSimdInt<N>& a, hkVector4fComparisonParameter sign);

		/// Sets this = a + b
		inline void setAdd(const hkSimdInt<N>& a, const hkSimdInt<N>& b);

		/// Sets this = a + b
		inline void setUnsignedAdd(HalfIntParameter a, HalfIntParameter b);

		/// Sets this = a - b
		inline void setSub(const hkSimdInt<N>& a, const hkSimdInt<N>& b);

		/// Sets this += ab
		inline void addMul(HalfIntParameter a, HalfIntParameter b);

		/// Sets this -= ab
		inline void subMul(HalfIntParameter a, HalfIntParameter b);

		/// Sets this = a * b
		inline void setMul(HalfIntParameter a, HalfIntParameter b);
		inline void setMul(HalfIntParameter a, hkInt64 b);
		inline void setUnsignedMul(HalfIntParameter a, HalfIntParameter b);
		inline void setUnsignedMul(HalfIntParameter a, hkInt64 b);
		inline void setUnsignedMul(const hkSimdInt<N>& origA, int origB);
		void setUnsignedMul(const hkSimdInt<N>& a, const hkSimdInt<N>& b);
		
		// Returns the number of leading zeros
		inline int countLeadingZeros() const;

		/// Returns a / b and a % b
		static inline void HK_CALL computeUnsignedDivMod(const hkSimdInt<N>& origA, const hkSimdInt<N>& origB, hkSimdInt<N>& divOut, hkSimdInt<N>& modOut);

		/// Returns a / b, assuming it fits in an int
		static inline int HK_CALL computeDiv32(const hkSimdInt<N>& origA, const hkSimdInt<N>& origB);

		/// Compares the fractions (a / b) and (c / d), returning 1 if (a/b) > (c/d), 0 if they are equal, or -1 otherwise
		static int HK_CALL compareFractions(const hkSimdInt<N>& a, const hkSimdInt<N>& b, const hkSimdInt<N>& c, const hkSimdInt<N>& d);

	public:

#ifndef __HAVOK_PARSER__
		HalfInt m_hi;
		HalfInt m_lo;
#endif
};

/// Specialization for 128-bits, start of template recursion
template <>
class hkSimdInt<128>
{
	//+hk.MemoryTracker(ignore=True)
	public:

		/// Sets this = i
		inline void setFromInt32(hkInt32 i);
		inline void setFromInt64(hkInt64 i);
		inline void setFromUint64(hkUint64 i);

		/// Sets this = 0
		inline void setZero();

		/// Sets this = -v
		inline void setNeg(const hkSimdInt<128>& v);

		/// Set this = abs(v)
		inline void setAbs(const hkSimdInt<128>& v);

		/// Sets this = a + b
		inline void setAdd(const hkSimdInt<128>& a, const hkSimdInt<128>& b);

		/// Sets this = a - b
		inline void setSub(const hkSimdInt<128>& a, const hkSimdInt<128>& b);

		/// Sets this = sign * v
		inline void setFlipSign(const hkSimdInt<128>& v, hkVector4fComparisonParameter sign);

		///	Increments this = this + 1 (faster than add(1)).
		inline void increment();

		/// Sets this = cmp ? vTrue : vFalse
		inline void setSelect(hkVector4fComparisonParameter cmp, const hkSimdInt<128>& vTrue, const hkSimdInt<128>& vFalse);

		/// Returns this < 0
		inline const hkVector4fComparison lessZero() const;
		template <typename T> inline const T lessZero() const;

		/// Returns this == 0
		inline const hkVector4fComparison equalZero() const;
		template <typename T> inline const T equalZero() const;

		/// Returns this == v
		inline const hkVector4fComparison equal(const hkSimdInt<128>& v) const;

		/// Sets this = a & b
		inline void setAnd(const hkSimdInt<128>& a, const hkSimdInt<128>& b);

		/// Sets this = ~a
		inline void setNot(const hkSimdInt<128>& a);

		/// Sets this = a | b
		inline void setOr(const hkSimdInt<128>& a, const hkSimdInt<128>& b);

		/// Sets this = a << I
		template <int I>
		inline void setShiftLeft(const hkSimdInt<128>& a);
		inline void setShiftLeft(const hkSimdInt<128>& a, int I);

		/// Sets this = a >> I
		template <int I, hkMathValueType Val>
		inline void setShiftRight(const hkSimdInt<128>& a);
		template <int I>
		inline void setShiftRight(const hkSimdInt<128>& a);
		inline void setShiftRight(const hkSimdInt<128>& a, int I);

		/// Sets this = a * b. The operands are assumed to be small enough so they are not causing overflow
		inline void setMul(const hkSimdInt<128>& a, hkInt64 b);
		inline void setUnsignedMul(hkInt64 a, hkInt64 b);

		/// Returns the number of leading zeros
		inline int countLeadingZeros() const;

		/// Returns the number of trailing zeros
		inline int countTrailingZeros() const;

		/// Returns the I-th 32-bit word, where LSB = 0, MSB = 3
		template <int I>
		inline int getWord() const;

		/// Returns the I-th 64-bit word, where LSB = 0, MSB = 3
		template <int I>
		inline hkInt64 getDoubleWord() const;

		/// Sets this = the greatest common divisor of the given numbers. Both numbers are assumed to be positive!
		inline void setGreatestCommonDivisor(const hkSimdInt<128>& a, const hkSimdInt<128>& b);

		/// Sets this = a / b. Both a and b are assumed unsigned!
		inline void setUnsignedDiv(const hkSimdInt<128>& a, const hkSimdInt<128>& b);
		static inline int HK_CALL computeDiv32(const hkSimdInt<128>& a, const hkSimdInt<128>& b);

	public:

		HK_ALIGN16(hkSingleInt128 m_quad);
};

#endif	//	HK_MATH_SIMD_INT_H

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
