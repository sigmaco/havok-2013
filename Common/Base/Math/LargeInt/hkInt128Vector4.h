/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#ifndef HK_MATH_INT128_VECTOR4_H
#define HK_MATH_INT128_VECTOR4_H

#ifndef HK_MATH_LARGE_INT_TYPES_H
#	error Include Common/Base/Math/LargeInt/hkLargeIntTypes.h instead of this file!
#endif

/// A 4-vector of 128-bit integers
class hkInt128Vector4
{
	//+hk.MemoryTracker(ignore=True)
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_MATH, hkInt128Vector4);

	public:

		/// Sets this = [x, y, z, w]
		inline void set(const hkSimdInt<128>& x, const hkSimdInt<128>& y, const hkSimdInt<128>& z, const hkSimdInt<128>& w);

		/// Sets all components to the given value
		inline void setAll(int i);

		/// Sets this = abs(v)
		template <int N>
		inline void setAbs(hkInt128Vector4Parameter v);

		/// Flips the sign of v
		template <int N>
		inline void setFlipSign(hkInt128Vector4Parameter v, hkVector4fComparisonParameter signFlip);

		/// Sets this = a & b
		template <int N>
		inline void setAnd(hkInt128Vector4Parameter a, hkInt128Vector4Parameter b);

		/// Sets this = a << I per component
		template <int N, int I>
		inline void setShiftLeft(hkInt128Vector4Parameter v);

		/// Sets this = Cross[vA, vB]
		inline void setCross(hkInt64Vector4Parameter vA, hkInt64Vector4Parameter vB);

		/// Sets this = vA * vB
		template <int N>
		inline void setMul(hkInt64Vector4Parameter vA, hkInt64Vector4Parameter vB);
		template <int N>
		inline void setMul(const hkSimdInt<128>& sA, hkInt64Vector4Parameter vB);

		/// Sets this = vA - vB
		template <int N>
		inline void setSub(hkInt128Vector4Parameter vA, hkInt128Vector4Parameter vB);

		/// Sets this -= sa * vB
		template <int N>
		inline void subMul(const hkSimdInt<128>& sA, hkInt64Vector4Parameter vB);

		/// Returns this < 0
		inline const hkVector4fComparison lessZero() const;

		/// Returns this < v
		template <int N>
		inline const hkVector4fComparison less(hkInt128Vector4Parameter v) const;

		/// Returns this == 0
		template <int N>
		inline const hkVector4fComparison equalZero() const;

		/// Returns this != 0
		template <int N>
		inline const hkVector4fComparison notEqualZero() const;

		/// Returns the dot product of this and v using the first I components
		template <int I>
		inline const hkSimdInt<256> dot(hkInt64Vector4Parameter v);
		template <int I>
		inline const hkSimdInt<256> dot(hkInt128Vector4Parameter v);
		
		/// Returns the index of the component with the smallest signed value among the first N components.
		/// In case of equality, returns the last component index given X,Y,Z,W ordering.
		template <int N> inline int getIndexOfMinComponent() const;

		/// Returns the index of the component with the largest signed value among the first N components.
		/// In case of equality, returns the last component index given X,Y,Z,W ordering.
		template <int N> inline int getIndexOfMaxComponent() const;

		/// Returns the i-th component
		inline const hkSimdInt<128> getComponent(int i) const;

		/// Sets this = a / b. Both a and b are assumed to be unsigned!
		template <int N>
		inline void setUnsignedDiv(hkInt128Vector4Parameter a, hkInt128Vector4Parameter b);

	public:

		hkSimdInt<128> m_x, m_y, m_z, m_w;
};

#endif	//	HK_MATH_INT128_VECTOR4_H

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
