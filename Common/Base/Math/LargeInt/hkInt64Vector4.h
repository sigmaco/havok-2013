/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#ifndef HK_MATH_INT64_VECTOR4_H
#define HK_MATH_INT64_VECTOR4_H

#ifndef HK_MATH_LARGE_INT_TYPES_H
#	error Include Common/Base/Math/LargeInt/hkLargeIntTypes.h instead of this file!
#endif

/// A 4-vector of 64-bit integers
class hkInt64Vector4
{
	//+hk.MemoryTracker(ignore=True)
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_MATH, hkInt64Vector4);
		HK_DECLARE_POD_TYPE();

	public:

		/// Sets all component of this to i
		inline void setAll(hkInt64 i);

		/// Sets the components of the vector to the given values
		inline void set(hkInt64 x, hkInt64 y, hkInt64 z, hkInt64 w = 0L);

		/// Sets this = 0
		inline void setZero();

		/// Sets the I-th component to the given value
		template <int I> inline void setComponent(hkInt64 value);
		inline void setComponent(int I, hkInt64 value);

		/// Sets this = vA * vB
		inline void setMul(hkIntVectorParameter vA, hkIntVectorParameter vB);

		/// Sets this.xy = a.y * b.y this.zw = a.w * b.w, i.e. multiplies the 2 64-bit operands and returns 2 128-bit numbers
		inline void setMul_128(hkInt64Vector4Parameter vA, hkInt64Vector4Parameter vB);

		template <int N>
		inline void setUnsignedMul_128(hkInt64Vector4Parameter vA, hkInt64Vector4Parameter vB);

		// Sets this = a / b. Both a and b are assumed to be unsigned!
		inline void setUnsignedDiv(hkInt64Vector4Parameter a, hkInt64Vector4Parameter b);

		/// Sets this = vA - vB
		inline void setSub(hkInt64Vector4Parameter vA, hkInt64Vector4Parameter vB);

		/// Sets this = Cross[vA, vB]
		inline void setCross(hkIntVectorParameter vA, hkIntVectorParameter vB);

		/// Returns (this < 0)
		inline const hkVector4fComparison lessZero() const;
		template <typename T> inline const T lessZero() const;

		/// Returns (this == 0)
		inline const hkVector4fComparison equalZero() const;

		/// Returns (this == v)
		inline const hkVector4fComparison equal(hkInt64Vector4Parameter v) const;

		/// Sets this = -v
		template <int I>
		inline void setNeg(hkInt64Vector4Parameter v);

		/// Sets this = abs(v)
		inline void setAbs(hkInt64Vector4Parameter v);

		/// Sets this = vA & vB
		inline void setAnd(hkInt64Vector4Parameter vA, hkInt64Vector4Parameter vB);

		/// Sets this = sign * v
		inline void setFlipSign(hkInt64Vector4Parameter v, hkVector4fComparisonParameter sign);

		/// Sets this = cmp ? vTrue : vFalse
		inline void setSelect(hkVector4fComparisonParameter cmp, hkInt64Vector4Parameter vTrue, hkInt64Vector4Parameter vFalse);

		/// Sets this = v << I by component
		template <int I>
		inline void setShiftLeft(hkInt64Vector4Parameter v);
		inline void setShiftLeft(hkInt64Vector4Parameter v, int I);

		/// Sets this = v >> I by component
		template <int I, hkMathValueType Val>
		inline void setShiftRight(hkInt64Vector4Parameter v);

		template <int I>
		inline void setShiftRight(hkInt64Vector4Parameter v);
		template <hkMathValueType Val>
		inline void setShiftRight(hkInt64Vector4Parameter v, int I);

		/// Returns the dot product between this and v
		template <int I>
		inline const hkSimdInt<128> dot(hkIntVectorParameter v) const;

		template <int I>
		const hkSimdInt<128> dot(hkInt64Vector4Parameter v) const;

		template <int I>
		inline hkInt64 dot_64(hkIntVectorParameter v) const;

		/// Sets this = a permutation of the components of v
		template <hkVectorPermutation::Permutation perm>
		inline void setPermutation(hkInt64Vector4Parameter v);

		/// Returns the I-th component
		template <int I>
		inline hkInt64 getComponent() const;
		inline hkInt64 getComponent(int I) const;

		/// Sets the I-th component to zero
		template <int I>
		inline void zeroComponent();

		/// Returns the maximum component among the first N.
		template <int N>
		inline hkInt64 horizontalMax() const;

		/// Returns the index of the component with the largest signed value among the first N components.
		/// In case of equality, returns the last component index given X,Y,Z,W ordering.
		template <int N>
		inline int getIndexOfMaxComponent() const;

		/// Loads the .xy components of this from a 128-bit int, where x is the High part and y is the Low part.
		inline void loadXy(const hkSimdInt<128>& xyIn);

		/// Loads the .zw components of this from a 128-bit int, where z is the High part and w is the Low part.
		inline void loadZw(const hkSimdInt<128>& zwIn);

		/// Stores the .xy components of this into a 128-bit int, where x is the High part and y is the Low part.
		inline void storeXy(hkSimdInt<128>& xyOut) const;

		/// Stores the .zw components of this into a 128-bit int, where z is the High part and w is the Low part.
		inline void storeZw(hkSimdInt<128>& zwOut) const;

		/// Converts the 4 64-bit ints to doubles
		inline void convertS64ToF64(hkVector4d& vOut) const;

		/// Counts the leading zeros of the first I components
		template <int I>
		inline void countLeadingZeros(hkIntVector& leadingZerosOut) const;

	public:

		HK_ALIGN16(hkQuadUlong m_quad);
};

#endif	//	HK_MATH_LONG_VECTOR4_H

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
