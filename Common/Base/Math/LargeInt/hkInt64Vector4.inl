/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

//
//	Sets this = Cross[vA, vB]

inline void hkInt64Vector4::setCross(hkIntVectorParameter vA, hkIntVectorParameter vB)
{
	// Shuffle
	hkIntVector a_yzx;	a_yzx.setPermutation<hkVectorPermutation::YZXW>(vA);	// [ay, az, ax]
	hkIntVector a_zxy;	a_zxy.setPermutation<hkVectorPermutation::ZXYW>(vA);	// [az, ax, ay]
	hkIntVector b_yzx;	b_yzx.setPermutation<hkVectorPermutation::YZXW>(vB);	// [by, bz, bx]
	hkIntVector b_zxy;	b_zxy.setPermutation<hkVectorPermutation::ZXYW>(vB);	// [bz, bx, by]

	hkInt64Vector4 abp;	abp.setMul(a_yzx, b_zxy);	// [ay bz, az bx, ax by]
	hkInt64Vector4 abn;	abn.setMul(a_zxy, b_yzx);	// [az by, ax bz, ay bx]
	setSub(abp, abn);								// [ay bz - az by, az bx - ax bz, ax by - ay bx]
}

//
//	Sets this = abs(v)

inline void hkInt64Vector4::setAbs(hkInt64Vector4Parameter v)
{
	setFlipSign(v, v.lessZero());
}

//
//	Sets this = sign * v

inline void hkInt64Vector4::setFlipSign(hkInt64Vector4Parameter v, hkVector4fComparisonParameter sign)
{
	hkInt64Vector4 vNeg;	vNeg.setNeg<4>(v);
	setSelect(sign, vNeg, v);
}

//
//	Returns the index of the component with the largest signed value among the first N components.
//	In case of equality, returns the last component index given X,Y,Z,W ordering.

template <>
inline int hkInt64Vector4::getIndexOfMaxComponent<3>() const
{
	hkInt64Vector4 mi;				mi.setAll(horizontalMax<3>());
	hkVector4fComparison isMin		= equal(mi);
	hkVector4fComparison xyzMask;	xyzMask.set<hkVector4ComparisonMask::MASK_XYZ>();

	isMin.setAnd(isMin, xyzMask);
	HK_ON_DEBUG(const int mask = isMin.getMask();)
		HK_MATH_ASSERT(0x2842fb1, mask > 0, "inconsistent min value of self");
	HK_MATH_ASSERT(0x2842fb2, (mask & hkVector4ComparisonMask::MASK_W) == 0, "selective compare failed");
	return isMin.getIndexOfFirstComponentSet();
}

template <> const hkSimdInt<128> hkInt64Vector4::dot<3>(hkInt64Vector4Parameter vB) const;

//
//	Counts the leading zeros of the first I components

#ifndef HK_INT64_VECTOR4_countLeadingZeros
#	define HK_INT64_VECTOR4_countLeadingZeros

template <>	inline void hkInt64Vector4::countLeadingZeros<1>(hkIntVector& leadingZerosOut) const
{
	leadingZerosOut.setComponent<0>(hkMath::countLeadingZeros<hkUint64>(getComponent<0>()));
}

template <int I> inline void hkInt64Vector4::countLeadingZeros(hkIntVector& leadingZerosOut) const
{
	countLeadingZeros<I - 1>(leadingZerosOut);
	leadingZerosOut.setComponent<I - 1>(hkMath::countLeadingZeros<hkUint64>(getComponent<I - 1>()));
}

#endif

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
