/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

namespace hkInt64Vector4Impl
{
	static const hkUint64 hkUint64Msb = 0x8000000000000000LU;
}

//
//	Sets all component of this to i

inline void hkInt64Vector4::setAll(hkInt64 i)
{
	set(i,i,i,i);
}

//
//	Sets this = 0

inline void hkInt64Vector4::setZero()
{
	set(0,0,0,0);
}

//
//	Sets the components of the vector to the given values

inline void hkInt64Vector4::set(hkInt64 x, hkInt64 y, hkInt64 z, hkInt64 w)
{
	m_quad.xy.setS64<0>(x);
	m_quad.xy.setS64<1>(y);
	m_quad.zw.setS64<0>(z);
	m_quad.zw.setS64<1>(w);
}

//
//	Sets the I-th component to the given value

template <> inline void hkInt64Vector4::setComponent<3>(hkInt64 value)	{	m_quad.zw.setS64<1>(value);	}
template <> inline void hkInt64Vector4::setComponent<2>(hkInt64 value)	{	m_quad.zw.setS64<0>(value);	}
template <> inline void hkInt64Vector4::setComponent<1>(hkInt64 value)	{	m_quad.xy.setS64<1>(value);	}
template <> inline void hkInt64Vector4::setComponent<0>(hkInt64 value)	{	m_quad.xy.setS64<0>(value);	}

//
//	Sets this = vA - vB

inline void hkInt64Vector4::setSub(hkInt64Vector4Parameter vA, hkInt64Vector4Parameter vB)
{
	m_quad.xy.setS64<0>(vA.m_quad.xy.getS64<0>() - vB.m_quad.xy.getS64<0>());
	m_quad.xy.setS64<1>(vA.m_quad.xy.getS64<1>() - vB.m_quad.xy.getS64<1>());
	m_quad.zw.setS64<0>(vA.m_quad.zw.getS64<0>() - vB.m_quad.zw.getS64<0>());
	m_quad.zw.setS64<1>(vA.m_quad.zw.getS64<1>() - vB.m_quad.zw.getS64<1>());
}

//
//	Returns (this < 0)

template <> inline const hkVector4fComparison hkInt64Vector4::lessZero<hkVector4fComparison>() const
{
	hkVector4ComparisonMask::Mask mask;
	mask = (hkVector4ComparisonMask::Mask)
		(
		((m_quad.xy.getS64<0>() < 0) ? hkVector4ComparisonMask::MASK_X : hkVector4ComparisonMask::MASK_NONE) |
		((m_quad.xy.getS64<1>() < 0) ? hkVector4ComparisonMask::MASK_Y : hkVector4ComparisonMask::MASK_NONE) |
		((m_quad.zw.getS64<0>() < 0) ? hkVector4ComparisonMask::MASK_Z : hkVector4ComparisonMask::MASK_NONE) |
		((m_quad.zw.getS64<1>() < 0) ? hkVector4ComparisonMask::MASK_W : hkVector4ComparisonMask::MASK_NONE)
		);
	hkVector4fComparison cmp;
	cmp.set(mask);
	return cmp;
}

template <> inline const hkVector4dComparison hkInt64Vector4::lessZero<hkVector4dComparison>() const
{
	hkVector4ComparisonMask::Mask mask;
	mask = (hkVector4ComparisonMask::Mask)
		(
		((m_quad.xy.getS64<0>() < 0) ? hkVector4ComparisonMask::MASK_X : hkVector4ComparisonMask::MASK_NONE) |
		((m_quad.xy.getS64<1>() < 0) ? hkVector4ComparisonMask::MASK_Y : hkVector4ComparisonMask::MASK_NONE) |
		((m_quad.zw.getS64<0>() < 0) ? hkVector4ComparisonMask::MASK_Z : hkVector4ComparisonMask::MASK_NONE) |
		((m_quad.zw.getS64<1>() < 0) ? hkVector4ComparisonMask::MASK_W : hkVector4ComparisonMask::MASK_NONE)
		);
	hkVector4dComparison cmp;
	cmp.set(mask);
	return cmp;
}

inline const hkVector4fComparison hkInt64Vector4::lessZero() const
{
	return lessZero<hkVector4fComparison>();
}

//
//	Returns (this == 0)

inline const hkVector4fComparison hkInt64Vector4::equalZero() const
{
	hkVector4ComparisonMask::Mask mask;
	mask = (hkVector4ComparisonMask::Mask)
		(
		((m_quad.xy.getS64<0>() == 0) ? hkVector4ComparisonMask::MASK_X : hkVector4ComparisonMask::MASK_NONE) |
		((m_quad.xy.getS64<1>() == 0) ? hkVector4ComparisonMask::MASK_Y : hkVector4ComparisonMask::MASK_NONE) |
		((m_quad.zw.getS64<0>() == 0) ? hkVector4ComparisonMask::MASK_Z : hkVector4ComparisonMask::MASK_NONE) |
		((m_quad.zw.getS64<1>() == 0) ? hkVector4ComparisonMask::MASK_W : hkVector4ComparisonMask::MASK_NONE)
		);
	hkVector4fComparison cmp;
	cmp.set(mask);
	return cmp;
}

//
//	Returns (this == v)

inline const hkVector4fComparison hkInt64Vector4::equal(hkInt64Vector4Parameter v) const
{
	hkVector4ComparisonMask::Mask mask;
	mask = (hkVector4ComparisonMask::Mask)
		(
		((m_quad.xy.getS64<0>() == v.m_quad.xy.getS64<0>()) ? hkVector4ComparisonMask::MASK_X : hkVector4ComparisonMask::MASK_NONE) |
		((m_quad.xy.getS64<1>() == v.m_quad.xy.getS64<1>()) ? hkVector4ComparisonMask::MASK_Y : hkVector4ComparisonMask::MASK_NONE) |
		((m_quad.zw.getS64<0>() == v.m_quad.zw.getS64<0>()) ? hkVector4ComparisonMask::MASK_Z : hkVector4ComparisonMask::MASK_NONE) |
		((m_quad.zw.getS64<1>() == v.m_quad.zw.getS64<1>()) ? hkVector4ComparisonMask::MASK_W : hkVector4ComparisonMask::MASK_NONE)
		);
	hkVector4fComparison cmp;
	cmp.set(mask);
	return cmp;
}

//
//	Sets this = -v

template <> inline void hkInt64Vector4::setNeg<4>(hkInt64Vector4Parameter v)
{
	m_quad.xy.setS64<0>(-v.m_quad.xy.getS64<0>());
	m_quad.xy.setS64<1>(-v.m_quad.xy.getS64<1>());
	m_quad.zw.setS64<0>(-v.m_quad.zw.getS64<0>());
	m_quad.zw.setS64<1>(-v.m_quad.zw.getS64<1>());
}

//
//	Sets this = vA & vB

inline void hkInt64Vector4::setAnd(hkInt64Vector4Parameter vA, hkInt64Vector4Parameter vB)
{
	m_quad.xy.setS64<0>(vA.m_quad.xy.getS64<0>() & vB.m_quad.xy.getS64<0>());
	m_quad.xy.setS64<1>(vA.m_quad.xy.getS64<1>() & vB.m_quad.xy.getS64<1>());
	m_quad.zw.setS64<0>(vA.m_quad.zw.getS64<0>() & vB.m_quad.zw.getS64<0>());
	m_quad.zw.setS64<1>(vA.m_quad.zw.getS64<1>() & vB.m_quad.zw.getS64<1>());
}

//
//	Sets this = cmp ? vTrue : vFalse

inline void hkInt64Vector4::setSelect(hkVector4fComparisonParameter cmp, hkInt64Vector4Parameter vTrue, hkInt64Vector4Parameter vFalse)
{
	m_quad.xy.setS64<0>(cmp.anyIsSet<hkVector4ComparisonMask::MASK_X>() ? vTrue.m_quad.xy.getS64<0>() : vFalse.m_quad.xy.getS64<0>());
	m_quad.xy.setS64<1>(cmp.anyIsSet<hkVector4ComparisonMask::MASK_Y>() ? vTrue.m_quad.xy.getS64<1>() : vFalse.m_quad.xy.getS64<1>());
	m_quad.zw.setS64<0>(cmp.anyIsSet<hkVector4ComparisonMask::MASK_Z>() ? vTrue.m_quad.zw.getS64<0>() : vFalse.m_quad.zw.getS64<0>());
	m_quad.zw.setS64<1>(cmp.anyIsSet<hkVector4ComparisonMask::MASK_W>() ? vTrue.m_quad.zw.getS64<1>() : vFalse.m_quad.zw.getS64<1>());
}

//
//	Sets this = v << shr by component

template <int I>
inline void hkInt64Vector4::setShiftLeft(hkInt64Vector4Parameter v)
{
	m_quad.xy.setS64<0>(v.m_quad.xy.getS64<0>() << I);
	m_quad.xy.setS64<1>(v.m_quad.xy.getS64<1>() << I);
	m_quad.zw.setS64<0>(v.m_quad.zw.getS64<0>() << I);
	m_quad.zw.setS64<1>(v.m_quad.zw.getS64<1>() << I);
}

inline void hkInt64Vector4::setShiftLeft(hkInt64Vector4Parameter v, int I)
{
	m_quad.xy.setS64<0>(v.m_quad.xy.getS64<0>() << I);
	m_quad.xy.setS64<1>(v.m_quad.xy.getS64<1>() << I);
	m_quad.zw.setS64<0>(v.m_quad.zw.getS64<0>() << I);
	m_quad.zw.setS64<1>(v.m_quad.zw.getS64<1>() << I);
}

namespace hkInt64Vector4Impl
{
	template <hkMathValueType VAL> struct Shr {};

	template <> struct Shr<HK_VALUE_UNSIGNED>
	{
		static inline void HK_CALL shr(hkInt64Vector4Parameter vIn, hkInt64Vector4& vOut, int I)
		{
			vOut.m_quad.xy.setU64<0>(vIn.m_quad.xy.getU64<0>() >> I);
			vOut.m_quad.xy.setU64<1>(vIn.m_quad.xy.getU64<1>() >> I);
			vOut.m_quad.zw.setU64<0>(vIn.m_quad.zw.getU64<0>() >> I);
			vOut.m_quad.zw.setU64<1>(vIn.m_quad.zw.getU64<1>() >> I);
		}
	};

	template <> struct Shr<HK_VALUE_SIGNED>
	{
		static inline void HK_CALL shr(hkInt64Vector4Parameter vIn, hkInt64Vector4& vOut, int I)
		{
			using namespace hkInt64Vector4Impl;
			const int II = (I >= 1) ? (I - 1) : 0;
			vOut.m_quad.xy.setU64<0>((vIn.m_quad.xy.getU64<0>() >> I) | (1 + (~((vIn.m_quad.xy.getU64<0>() & hkUint64Msb) >> II))));
			vOut.m_quad.xy.setU64<1>((vIn.m_quad.xy.getU64<1>() >> I) | (1 + (~((vIn.m_quad.xy.getU64<1>() & hkUint64Msb) >> II))));
			vOut.m_quad.zw.setU64<0>((vIn.m_quad.zw.getU64<0>() >> I) | (1 + (~((vIn.m_quad.zw.getU64<0>() & hkUint64Msb) >> II))));
			vOut.m_quad.zw.setU64<1>((vIn.m_quad.zw.getU64<1>() >> I) | (1 + (~((vIn.m_quad.zw.getU64<1>() & hkUint64Msb) >> II))));
		}
	};
}

//
//	Sets this = v >> I by component

template <int I, hkMathValueType VAL>
inline void hkInt64Vector4::setShiftRight(hkInt64Vector4Parameter v)
{
	hkInt64Vector4Impl::Shr<VAL>::shr(v, *this, I);
}

template <int I>
inline void hkInt64Vector4::setShiftRight(hkInt64Vector4Parameter v)
{
	setShiftRight<HK_VALUE_UNSIGNED>(v, I);
}

template <hkMathValueType VAL>
inline void hkInt64Vector4::setShiftRight(hkInt64Vector4Parameter v, int I)
{
	hkInt64Vector4Impl::Shr<VAL>::shr(v, *this, I);
}

//
//	Returns the dot product between this and v

template <> inline const hkSimdInt<128> hkInt64Vector4::dot<3>(hkIntVectorParameter vB) const
{
	hkSimdInt<128> dx; dx.setFromInt64(m_quad.xy.getS64<0>()); dx.setMul(dx, vB.getComponent<0>());
	hkSimdInt<128> dy; dy.setFromInt64(m_quad.xy.getS64<1>()); dy.setMul(dy, vB.getComponent<1>());
	hkSimdInt<128> dz; dz.setFromInt64(m_quad.zw.getS64<0>()); dz.setMul(dz, vB.getComponent<2>());
	hkSimdInt<128> dxy; dxy.setAdd(dx, dy);
	hkSimdInt<128> ret; ret.setAdd(dxy, dz);
	return ret;
}

//
//	Returns the dot product between this and v

template <> inline hkInt64 hkInt64Vector4::dot_64<3>(hkIntVectorParameter vB) const
{
	return m_quad.xy.getS64<0>() * vB.getComponent<0>() + m_quad.xy.getS64<1>() * vB.getComponent<1>() + m_quad.zw.getS64<0>() * vB.getComponent<2>();
}

//
//	Sets this = a permutation of the components of v

template <> inline void hkInt64Vector4::setPermutation<hkVectorPermutation::YZXW>(hkInt64Vector4Parameter v_)
{
	// Support aliased variables
	hkInt64Vector4 v = v_;
	m_quad.xy.setS64<0>(v.m_quad.xy.getS64<1>());
	m_quad.xy.setS64<1>(v.m_quad.zw.getS64<0>());
	m_quad.zw.setS64<0>(v.m_quad.xy.getS64<0>());
	m_quad.zw.setS64<1>(v.m_quad.zw.getS64<1>());
}

template <> inline void hkInt64Vector4::setPermutation<hkVectorPermutation::ZXYW>(hkInt64Vector4Parameter v_)
{
	// Support aliased variables
	hkInt64Vector4 v = v_;
	m_quad.xy.setS64<0>(v.m_quad.zw.getS64<0>());
	m_quad.xy.setS64<1>(v.m_quad.xy.getS64<0>());
	m_quad.zw.setS64<0>(v.m_quad.xy.getS64<1>());
	m_quad.zw.setS64<1>(v.m_quad.zw.getS64<1>());
}

template <> inline void hkInt64Vector4::setPermutation<hkVectorPermutation::YXWZ>(hkInt64Vector4Parameter v_)
{
	// Support aliased variables
	hkInt64Vector4 v = v_;
	m_quad.xy.setS64<0>(v.m_quad.xy.getS64<1>());
	m_quad.xy.setS64<1>(v.m_quad.xy.getS64<0>());
	m_quad.zw.setS64<0>(v.m_quad.zw.getS64<1>());
	m_quad.zw.setS64<1>(v.m_quad.zw.getS64<0>());
}

template <> inline void hkInt64Vector4::setPermutation<hkVectorPermutation::XYWZ>(hkInt64Vector4Parameter v_)
{
	// Support aliased variables
	hkInt64Vector4 v = v_;
	m_quad.xy.setS64<0>(v.m_quad.xy.getS64<0>());
	m_quad.xy.setS64<1>(v.m_quad.xy.getS64<1>());
	m_quad.zw.setS64<0>(v.m_quad.zw.getS64<1>());
	m_quad.zw.setS64<1>(v.m_quad.zw.getS64<0>());
}

template <> inline void hkInt64Vector4::setPermutation<hkVectorPermutation::YYWW>(hkInt64Vector4Parameter v_)
{
	// Support aliased variables
	hkInt64Vector4 v = v_;
	m_quad.xy.setS64<0>(v.m_quad.xy.getS64<1>());
	m_quad.xy.setS64<1>(v.m_quad.xy.getS64<1>());
	m_quad.zw.setS64<0>(v.m_quad.zw.getS64<1>());
	m_quad.zw.setS64<1>(v.m_quad.zw.getS64<1>());
}

template <> inline void hkInt64Vector4::setPermutation<hkVectorPermutation::WWWW>(hkInt64Vector4Parameter v)
{
	m_quad.xy.setS64<0>(v.m_quad.zw.getS64<1>());
	m_quad.xy.setS64<1>(v.m_quad.zw.getS64<1>());
	m_quad.zw.setS64<0>(v.m_quad.zw.getS64<1>());
	m_quad.zw.setS64<1>(v.m_quad.zw.getS64<1>());
}

template <>
inline void hkInt64Vector4::setUnsignedMul_128<2>(hkInt64Vector4Parameter vA, hkInt64Vector4Parameter vB)
{
	{
		hkUint64 ahi = hkUint64(vA.m_quad.xy.getU32<3>());
		hkUint64 alo = hkUint64(vA.m_quad.xy.getU32<2>());
		hkUint64 bhi = hkUint64(vB.m_quad.xy.getU32<3>());
		hkUint64 blo = hkUint64(vB.m_quad.xy.getU32<2>());

		hkSimdInt<128> p; p.setFromUint64(alo*blo);
		hkSimdInt<128> phi; phi.setFromUint64(ahi*bhi); phi.setShiftLeft<64>(phi);
		hkSimdInt<128> p1; p1.setFromUint64(ahi*blo); p1.setShiftLeft<32>(p1);
		hkSimdInt<128> p2; p2.setFromUint64(alo*bhi); p2.setShiftLeft<32>(p2);
		p.setAdd(p, p1);
		p.setAdd(p, p2);
		p.setAdd(p, phi);
		m_quad.xy.setU64<0>(p.getDoubleWord<1>());
		m_quad.xy.setU64<1>(p.getDoubleWord<0>());
	}
	{
		hkUint64 ahi = hkUint64(vA.m_quad.zw.getU32<3>());
		hkUint64 alo = hkUint64(vA.m_quad.zw.getU32<2>());
		hkUint64 bhi = hkUint64(vB.m_quad.zw.getU32<3>());
		hkUint64 blo = hkUint64(vB.m_quad.zw.getU32<2>());

		hkSimdInt<128> p; p.setFromUint64(alo*blo);
		hkSimdInt<128> phi; phi.setFromUint64(ahi*bhi); phi.setShiftLeft<64>(phi);
		hkSimdInt<128> p1; p1.setFromUint64(ahi*blo); p1.setShiftLeft<32>(p1);
		hkSimdInt<128> p2; p2.setFromUint64(alo*bhi); p2.setShiftLeft<32>(p2);
		p.setAdd(p, p1);
		p.setAdd(p, p2);
		p.setAdd(p, phi);
		m_quad.zw.setU64<0>(p.getDoubleWord<1>());
		m_quad.zw.setU64<1>(p.getDoubleWord<0>());
	}
}

//
//	Sets this.xy = a.x * b.x this.zw = a.z * b.z, i.e. multiplies the 2 64-bit operands and returns 2 128-bit numbers

inline void hkInt64Vector4::setMul_128(hkInt64Vector4Parameter origA, hkInt64Vector4Parameter origB)
{
	hkSimdInt<128> x; x.setFromInt64(origA.m_quad.xy.getS64<1>()); x.setMul(x, origB.m_quad.xy.getS64<1>());
	hkSimdInt<128> z; z.setFromInt64(origA.m_quad.zw.getS64<1>()); z.setMul(z, origB.m_quad.zw.getS64<1>());
	m_quad.xy.setU64<0>(x.getDoubleWord<1>()); m_quad.xy.setU64<1>(x.getDoubleWord<0>());
	m_quad.zw.setU64<0>(z.getDoubleWord<1>()); m_quad.zw.setU64<1>(z.getDoubleWord<0>());
}

//
//	Sets this = vA * vB

inline void hkInt64Vector4::setMul(hkIntVectorParameter origA, hkIntVectorParameter origB)
{
	m_quad.xy.setS64<0>(hkInt64(origA.getComponent<0>()) * hkInt64(origB.getComponent<0>()));
	m_quad.xy.setS64<1>(hkInt64(origA.getComponent<1>()) * hkInt64(origB.getComponent<1>()));
	m_quad.zw.setS64<0>(hkInt64(origA.getComponent<2>()) * hkInt64(origB.getComponent<2>()));
	m_quad.zw.setS64<1>(hkInt64(origA.getComponent<3>()) * hkInt64(origB.getComponent<3>()));
}

//
//	Returns the I-th component

template <> inline hkInt64 hkInt64Vector4::getComponent<0>()	const	
{	
	return m_quad.xy.getS64<0>();	
}
template <> inline hkInt64 hkInt64Vector4::getComponent<1>()	const	
{	
	return m_quad.xy.getS64<1>();	
}
template <> inline hkInt64 hkInt64Vector4::getComponent<2>()	const	
{	
	return m_quad.zw.getS64<0>();	
}
template <> inline hkInt64 hkInt64Vector4::getComponent<3>()	const	
{	
	return m_quad.zw.getS64<1>();	
}
inline hkInt64 hkInt64Vector4::getComponent(int I) const
{
	return (I < 2) ? m_quad.xy.getS64(I) : m_quad.zw.getS64(I - 2);
}

//
//	Returns the maximum component among the first N.

template <>
inline hkInt64 hkInt64Vector4::horizontalMax<3>() const
{
	return hkMath::max2(hkMath::max2(m_quad.xy.getS64<0>(), m_quad.xy.getS64<1>()), m_quad.zw.getS64<0>());
}

//
//	Sets the I-th component to zero.

template <> inline void hkInt64Vector4::zeroComponent<0>()		
{	
	m_quad.xy.setS64<0>(0);
}
template <> inline void hkInt64Vector4::zeroComponent<1>()		
{	
	m_quad.xy.setS64<1>(0);
}
template <> inline void hkInt64Vector4::zeroComponent<2>()		
{
	m_quad.zw.setS64<0>(0);
}
template <> inline void hkInt64Vector4::zeroComponent<3>()		
{	
	m_quad.zw.setS64<1>(0);
}

//
//	Loads the .xy components of this from a 128-bit int, where x is the High part and y is the Low part.

inline void hkInt64Vector4::loadXy(const hkSimdInt<128>& xyIn)
{
	m_quad.xy.setU64<0>(xyIn.m_quad.getU64<1>());
	m_quad.xy.setU64<1>(xyIn.m_quad.getU64<0>());
}

//
//	Loads the .zw components of this from a 128-bit int, where z is the High part and w is the Low part.

inline void hkInt64Vector4::loadZw(const hkSimdInt<128>& zwIn)
{
	m_quad.zw.setU64<0>(zwIn.m_quad.getU64<1>());
	m_quad.zw.setU64<1>(zwIn.m_quad.getU64<0>());
}

//
//	Retrieves the x and y components as an 128-bit int i, where x = Hi[i] and y = Lo[i]

inline void hkInt64Vector4::storeXy(hkSimdInt<128>& x) const
{
	x.m_quad.setU64<1>(m_quad.xy.getU64<0>());
	x.m_quad.setU64<0>(m_quad.xy.getU64<1>());
}

//
//	Retrieves the z and w components as an 128-bit int x, where z = Hi[x] and w = Lo[x]

inline void hkInt64Vector4::storeZw(hkSimdInt<128>& x) const
{
	x.m_quad.setU64<1>(m_quad.zw.getU64<0>());
	x.m_quad.setU64<0>(m_quad.zw.getU64<1>());
}

//
//	Sets this = a / b. Both a and b are assumed to be unsigned!

inline void hkInt64Vector4::setUnsignedDiv(hkInt64Vector4Parameter a, hkInt64Vector4Parameter b)
{
	m_quad.xy.setU64<0>(a.m_quad.xy.getU64<0>() / b.m_quad.xy.getU64<0>());
	m_quad.xy.setU64<1>(a.m_quad.xy.getU64<1>() / b.m_quad.xy.getU64<1>());
	m_quad.zw.setU64<0>(a.m_quad.zw.getU64<0>() / b.m_quad.zw.getU64<0>());
	m_quad.zw.setU64<1>(a.m_quad.zw.getU64<1>() / b.m_quad.zw.getU64<1>());
}

//
//	Converts the 4 64-bit ints to doubles

inline void hkInt64Vector4::convertS64ToF64(hkVector4d& vOut) const
{
	vOut.set((double)m_quad.xy.getS64<0>(), (double)m_quad.xy.getS64<1>(), (double)m_quad.zw.getS64<0>(), (double)m_quad.zw.getS64<1>());
}

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
