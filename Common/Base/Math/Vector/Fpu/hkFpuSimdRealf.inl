/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

HK_FORCE_INLINE /*static*/ const hkSimdFloat32 HK_CALL hkSimdFloat32::convert(const hkSingleFloat32& x)
{
	hkSimdFloat32 sr;
	sr.m_real = x;
	return sr;
}

template<int vectorConstant>
HK_FORCE_INLINE /*static*/ const hkSimdFloat32 HK_CALL hkSimdFloat32::getConstant()
{
	HK_COMPILE_TIME_ASSERT2( 
		(vectorConstant!=HK_QUADREAL_1000) && (vectorConstant!=HK_QUADREAL_0100) && (vectorConstant!=HK_QUADREAL_0010) && (vectorConstant!=HK_QUADREAL_0001) &&
		(vectorConstant!=HK_QUADREAL_m11m11) && (vectorConstant!=HK_QUADREAL_1248) && (vectorConstant!=HK_QUADREAL_8421) && (vectorConstant!=HK_QUADREAL_1010)  && (vectorConstant!=HK_QUADREAL_1100)
		, HK_SIMDFLOAT_ILLEGAL_CONSTANT_REQUEST);
	return convert((g_vectorfConstants + vectorConstant)->v[0]);
}

HK_FORCE_INLINE /*static*/ const hkSimdFloat32 HK_CALL hkSimdFloat32::getConstant(hkVectorConstant constant)
{	
	HK_MATH_ASSERT( 0x909ff234,
		(constant!=HK_QUADREAL_1000) && (constant!=HK_QUADREAL_0100) && (constant!=HK_QUADREAL_0010) && (constant!=HK_QUADREAL_0001) &&
		(constant!=HK_QUADREAL_m11m11) && (constant!=HK_QUADREAL_1248) && (constant!=HK_QUADREAL_8421) && (constant!=HK_QUADREAL_1010)  && (constant!=HK_QUADREAL_1100)
		, "not a simdreal constant");
	return convert((g_vectorfConstants + constant)->v[0]);
}

#ifndef HK_DISABLE_IMPLICIT_SIMDREAL_FLOAT_CONVERSION
HK_FORCE_INLINE hkSimdFloat32::hkSimdFloat32(const hkFloat32& x)
{
	m_real = x;
}

HK_FORCE_INLINE hkSimdFloat32::operator hkFloat32() const
{
	return m_real;
}
#endif

HK_FORCE_INLINE hkFloat32 hkSimdFloat32::getReal() const
{
	return m_real;
}

HK_FORCE_INLINE void hkSimdFloat32::setFromFloat(const hkFloat32& x)
{
	m_real = hkFloat32(x);
}

HK_FORCE_INLINE void hkSimdFloat32::setFromFloat(const hkDouble64& x)
{
	m_real = hkFloat32(x);
}

HK_FORCE_INLINE void hkSimdFloat32::setFromHalf(const hkHalf& h)
{
	m_real = h.getFloat32();
}

HK_FORCE_INLINE void hkSimdFloat32::setFromInt32(const hkInt32&  x)
{
	m_real = hkFloat32(x);
}

HK_FORCE_INLINE void hkSimdFloat32::setFromUint16(const hkUint16& x)
{
	int i = x;
	setFromInt32(i);
}

HK_FORCE_INLINE void hkSimdFloat32::setFromUint8(const hkUint8& x)
{
	int i = x;
	setFromInt32(i);
}
HK_FORCE_INLINE void hkSimdFloat32::setZero()
{
	m_real = hkFloat32(0);
}

HK_FORCE_INLINE void hkSimdFloat32::storeSaturateInt32(hkInt32* HK_RESTRICT result) const
{
	*result = hkMath::hkToIntFast(m_real);
}


HK_FORCE_INLINE void hkSimdFloat32::storeSaturateUint16(hkUint16* result) const
{
	const hkInt32 i = hkMath::hkToIntFast(m_real);
	const hkInt32 clampPos    = hkMath::max2(i, 0x0);
	const hkInt32 clampPosNeg = hkMath::min2(clampPos, 0xffff);
	*result = hkUint16(clampPosNeg);
}


HK_FORCE_INLINE const hkSimdFloat32 hkSimdFloat32::operator+ (hkSimdFloat32Parameter r) const
{
	return hkSimdFloat32::convert(m_real + r.m_real);
}

HK_FORCE_INLINE const hkSimdFloat32 hkSimdFloat32::operator- (hkSimdFloat32Parameter r) const
{
	return hkSimdFloat32::convert(m_real - r.m_real);
}

HK_FORCE_INLINE const hkSimdFloat32 hkSimdFloat32::operator* (hkSimdFloat32Parameter r) const
{
	return hkSimdFloat32::convert(m_real * r.m_real);
}


#ifdef HK_DISABLE_OLD_VECTOR4_INTERFACE

HK_FORCE_INLINE bool hkSimdFloat32::operator< (hkSimdFloat32Parameter r) const
{
	return (m_real < r.m_real);
}

HK_FORCE_INLINE bool hkSimdFloat32::operator<= (hkSimdFloat32Parameter r) const
{
	return (m_real <= r.m_real);
}

HK_FORCE_INLINE bool hkSimdFloat32::operator> (hkSimdFloat32Parameter r) const
{
	return (m_real > r.m_real);
}

HK_FORCE_INLINE bool hkSimdFloat32::operator>= (hkSimdFloat32Parameter r) const
{
	return (m_real >= r.m_real);
}

HK_FORCE_INLINE bool hkSimdFloat32::operator== (hkSimdFloat32Parameter r) const
{
	return (m_real == r.m_real);
}

HK_FORCE_INLINE bool hkSimdFloat32::operator!= (hkSimdFloat32Parameter r) const
{
	return (m_real != r.m_real);
}

#endif

HK_FORCE_INLINE const hkSimdFloat32 hkSimdFloat32::operator-() const
{
	return hkSimdFloat32::convert(-m_real);
}

HK_FORCE_INLINE const hkVector4fComparison hkSimdFloat32::less(hkSimdFloat32Parameter a) const
{
	hkVector4fComparison res;
	res.m_mask = (m_real < a.m_real) ? hkVector4ComparisonMask::MASK_XYZW : hkVector4ComparisonMask::MASK_NONE;
	return res;
}

HK_FORCE_INLINE const hkVector4fComparison hkSimdFloat32::greater(hkSimdFloat32Parameter a) const
{
	hkVector4fComparison res;
	res.m_mask = (m_real > a.m_real) ? hkVector4ComparisonMask::MASK_XYZW : hkVector4ComparisonMask::MASK_NONE;
	return res;
}

HK_FORCE_INLINE const hkVector4fComparison hkSimdFloat32::greaterEqual(hkSimdFloat32Parameter a) const
{
	hkVector4fComparison res;
	res.m_mask = (m_real >= a.m_real) ? hkVector4ComparisonMask::MASK_XYZW : hkVector4ComparisonMask::MASK_NONE;
	return res;
}

HK_FORCE_INLINE const hkVector4fComparison hkSimdFloat32::lessEqual(hkSimdFloat32Parameter a) const
{
	hkVector4fComparison res;
	res.m_mask = (m_real <= a.m_real) ? hkVector4ComparisonMask::MASK_XYZW : hkVector4ComparisonMask::MASK_NONE;
	return res;
}

HK_FORCE_INLINE const hkVector4fComparison hkSimdFloat32::equal(hkSimdFloat32Parameter a) const
{
	hkVector4fComparison res;
	res.m_mask = (m_real == a.m_real) ? hkVector4ComparisonMask::MASK_XYZW : hkVector4ComparisonMask::MASK_NONE;
	return res;
}

HK_FORCE_INLINE const hkVector4fComparison hkSimdFloat32::notEqual(hkSimdFloat32Parameter a) const
{
	hkVector4fComparison res;
	res.m_mask = (m_real != a.m_real) ? hkVector4ComparisonMask::MASK_XYZW : hkVector4ComparisonMask::MASK_NONE;
	return res;
}

HK_FORCE_INLINE const hkVector4fComparison hkSimdFloat32::lessZero() const
{
	hkVector4fComparison res;
	res.m_mask = (m_real < hkFloat32(0)) ? hkVector4ComparisonMask::MASK_XYZW : hkVector4ComparisonMask::MASK_NONE;
	return res;
}

HK_FORCE_INLINE const hkVector4fComparison hkSimdFloat32::lessEqualZero() const
{
	hkVector4fComparison res;
	res.m_mask = (m_real <= hkFloat32(0)) ? hkVector4ComparisonMask::MASK_XYZW : hkVector4ComparisonMask::MASK_NONE;
	return res;
}

HK_FORCE_INLINE const hkVector4fComparison hkSimdFloat32::greaterZero() const
{
	hkVector4fComparison res;
	res.m_mask = (m_real > hkFloat32(0)) ? hkVector4ComparisonMask::MASK_XYZW : hkVector4ComparisonMask::MASK_NONE;
	return res;
}

HK_FORCE_INLINE const hkVector4fComparison hkSimdFloat32::greaterEqualZero() const
{
	hkVector4fComparison res;
	res.m_mask = (m_real >= hkFloat32(0)) ? hkVector4ComparisonMask::MASK_XYZW : hkVector4ComparisonMask::MASK_NONE;
	return res;
}

HK_FORCE_INLINE const hkVector4fComparison hkSimdFloat32::equalZero() const
{
	hkVector4fComparison res;
	res.m_mask = (m_real == hkFloat32(0)) ? hkVector4ComparisonMask::MASK_XYZW : hkVector4ComparisonMask::MASK_NONE;
	return res;
}

HK_FORCE_INLINE const hkVector4fComparison hkSimdFloat32::notEqualZero() const
{
	hkVector4fComparison res;
	res.m_mask = (m_real != hkFloat32(0)) ? hkVector4ComparisonMask::MASK_XYZW : hkVector4ComparisonMask::MASK_NONE;
	return res;
}

HK_FORCE_INLINE hkBool32 hkSimdFloat32::isSignBitSet() const
{
	return hkMath::signBitSet(m_real);
}

HK_FORCE_INLINE hkBool32 hkSimdFloat32::isSignBitClear() const
{
	return !hkMath::signBitSet(m_real);
}

HK_FORCE_INLINE const hkVector4fComparison hkSimdFloat32::signBitSet() const
{
	hkVector4fComparison res;
	res.m_mask = hkMath::signBitSet(m_real) ? hkVector4ComparisonMask::MASK_XYZW : hkVector4ComparisonMask::MASK_NONE;
	return res;
}

HK_FORCE_INLINE const hkVector4fComparison hkSimdFloat32::signBitClear() const
{
	hkVector4fComparison res;
	res.m_mask = hkMath::signBitSet(m_real) ? hkVector4ComparisonMask::MASK_NONE : hkVector4ComparisonMask::MASK_XYZW;
	return res;
}

HK_FORCE_INLINE hkBool32 hkSimdFloat32::isLess(hkSimdFloat32Parameter a) const
{
	return (m_real < a.m_real);
}

HK_FORCE_INLINE hkBool32 hkSimdFloat32::isLessEqual(hkSimdFloat32Parameter a) const
{
	return (m_real <= a.m_real);
}

HK_FORCE_INLINE hkBool32 hkSimdFloat32::isGreater(hkSimdFloat32Parameter a) const
{
	return (m_real > a.m_real);
}

HK_FORCE_INLINE hkBool32 hkSimdFloat32::isGreaterEqual(hkSimdFloat32Parameter a) const
{
	return (m_real >= a.m_real);
}

HK_FORCE_INLINE hkBool32 hkSimdFloat32::isEqual(hkSimdFloat32Parameter a) const
{
	return (m_real == a.m_real);
}

HK_FORCE_INLINE hkBool32 hkSimdFloat32::isNotEqual(hkSimdFloat32Parameter a) const
{
	return (m_real != a.m_real);
}

HK_FORCE_INLINE hkBool32 hkSimdFloat32::isLessZero() const
{
	return (m_real < hkFloat32(0));
}

HK_FORCE_INLINE hkBool32 hkSimdFloat32::isLessEqualZero() const
{
	return (m_real <= hkFloat32(0));
}

HK_FORCE_INLINE hkBool32 hkSimdFloat32::isGreaterZero() const
{
	return (m_real > hkFloat32(0));
}

HK_FORCE_INLINE hkBool32 hkSimdFloat32::isGreaterEqualZero() const
{
	return (m_real >= hkFloat32(0));
}

HK_FORCE_INLINE hkBool32 hkSimdFloat32::isEqualZero() const
{
	return (m_real == hkFloat32(0));
}

HK_FORCE_INLINE hkBool32 hkSimdFloat32::isNotEqualZero() const
{
	return (m_real != hkFloat32(0));
}

HK_FORCE_INLINE hkBool32 hkSimdFloat32::isOk() const
{
	return hkMath::isFinite(m_real);
}

HK_FORCE_INLINE void hkSimdFloat32::setSelect( hkVector4fComparisonParameter comp, hkSimdFloat32Parameter a, hkSimdFloat32Parameter b )
{
	HK_MATH_ASSERT(0x125f0f99, comp.allAreSet() || (comp.getMask() == hkVector4ComparisonMask::MASK_NONE), "illegal compare mask");
	m_real = comp.m_mask ? a.m_real : b.m_real;
}

HK_FORCE_INLINE void hkSimdFloat32::zeroIfFalse( hkVector4fComparisonParameter comp )
{
	HK_MATH_ASSERT(0x125f0f99, comp.allAreSet() || (comp.getMask() == hkVector4ComparisonMask::MASK_NONE), "illegal compare mask");
	m_real = comp.m_mask ? m_real : hkFloat32(0);
}

HK_FORCE_INLINE void hkSimdFloat32::zeroIfTrue( hkVector4fComparisonParameter comp )
{
	HK_MATH_ASSERT(0x125f0f99, comp.allAreSet() || (comp.getMask() == hkVector4ComparisonMask::MASK_NONE), "illegal compare mask");
	m_real = comp.m_mask ? hkFloat32(0) : m_real;
}

HK_FORCE_INLINE void hkSimdFloat32::setMin(  hkSimdFloat32Parameter a, hkSimdFloat32Parameter b ) 
{
	m_real = hkMath::min2( a.m_real, b.m_real );
}

HK_FORCE_INLINE void hkSimdFloat32::setMax(  hkSimdFloat32Parameter a, hkSimdFloat32Parameter b ) 
{
	m_real = hkMath::max2( a.m_real, b.m_real );
}

HK_FORCE_INLINE void hkSimdFloat32::setAbs(  hkSimdFloat32Parameter a )
{
	m_real = hkMath::fabs(a.m_real);
}

HK_FORCE_INLINE void hkSimdFloat32::setFloor(  hkSimdFloat32Parameter a )
{
	m_real = hkMath::floor(a.m_real);
}

HK_FORCE_INLINE void hkSimdFloat32::setMod(  hkSimdFloat32Parameter a, hkSimdFloat32Parameter b )
{
	m_real = hkMath::fmod(a.m_real,b.m_real);
}

HK_FORCE_INLINE void hkSimdFloat32::setFlipSign(hkSimdFloat32Parameter v, hkSimdFloat32Parameter sSign)
{
	m_real = hkMath::signBitSet(sSign.m_real) ? -v.m_real : v.m_real;
}

HK_FORCE_INLINE void hkSimdFloat32::setFlipSign(hkSimdFloat32Parameter v, hkVector4fComparisonParameter mask)
{
	HK_MATH_ASSERT(0x39186bef, mask.allAreSet() || (mask.getMask() == hkVector4ComparisonMask::MASK_NONE), "illegal compare mask");
	m_real = mask.m_mask ? -v.m_real : v.m_real;
}

//
// advanced interface
//

namespace hkSimdFloat32_AdvancedInterface
{

template <hkMathAccuracyMode A, hkMathDivByZeroMode D>
struct unroll_setReciprocal { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, hkSimdFloat32Parameter a)
{
	HK_SIMDFLOAT_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <hkMathAccuracyMode A>
struct unroll_setReciprocal<A, HK_DIV_IGNORE> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, hkSimdFloat32Parameter a)
{
	switch (A)
	{
		case HK_ACC_23_BIT: { hkFloat32 x = hkMath::rcpF32Approx23Bit(hkFloat32(a.m_real)); self = hkFloat32(x); } break;
		case HK_ACC_12_BIT: { hkFloat32 x = hkMath::rcpF32Approx12Bit(hkFloat32(a.m_real)); self = hkFloat32(x); } break;
		default:         self = hkFloat32(1) / a.m_real; break; // HK_ACC_FULL
	}
} };
template <hkMathAccuracyMode A>
struct unroll_setReciprocal<A, HK_DIV_SET_ZERO> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, hkSimdFloat32Parameter a)
{
	if (a.m_real == hkFloat32(0)) { self = hkFloat32(0); return; }
	unroll_setReciprocal<A, HK_DIV_IGNORE>::apply(self,a);
} };
template <hkMathAccuracyMode A>
struct unroll_setReciprocal<A, HK_DIV_SET_HIGH> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, hkSimdFloat32Parameter a)
{
	if (a.m_real == hkFloat32(0)) { self = HK_FLOAT_HIGH; return; }
	unroll_setReciprocal<A, HK_DIV_IGNORE>::apply(self,a);
} };
template <hkMathAccuracyMode A>
struct unroll_setReciprocal<A, HK_DIV_SET_MAX> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, hkSimdFloat32Parameter a)
{
	if (a.m_real == hkFloat32(0)) { self = HK_FLOAT_MAX; return; }
	unroll_setReciprocal<A, HK_DIV_IGNORE>::apply(self,a);
} };
template <hkMathAccuracyMode A>
struct unroll_setReciprocal<A, HK_DIV_SET_ZERO_AND_ONE> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, hkSimdFloat32Parameter a)
{
	unroll_setReciprocal<A, HK_DIV_SET_ZERO>::apply(self,a);
	const hkSingleFloat32 absValLessOne = hkMath::fabs(self - hkFloat32(1));
	if (absValLessOne <= HK_FLOAT_EPSILON)
		self = hkFloat32(1);
} };

} // namespace 

template <hkMathAccuracyMode A, hkMathDivByZeroMode D> 
HK_FORCE_INLINE void hkSimdFloat32::setReciprocal(hkSimdFloat32Parameter a)
{
	hkSimdFloat32_AdvancedInterface::unroll_setReciprocal<A,D>::apply(m_real,a);
}

HK_FORCE_INLINE void hkSimdFloat32::setReciprocal(hkSimdFloat32Parameter a)
{
	hkSimdFloat32_AdvancedInterface::unroll_setReciprocal<HK_ACC_23_BIT,HK_DIV_IGNORE>::apply(m_real,a);
}



namespace hkSimdFloat32_AdvancedInterface
{

template <hkMathAccuracyMode A, hkMathDivByZeroMode D>
struct unroll_setDiv { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, hkSimdFloat32Parameter a, hkSimdFloat32Parameter b)
{
	HK_SIMDFLOAT_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <hkMathAccuracyMode A>
struct unroll_setDiv<A, HK_DIV_IGNORE> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, hkSimdFloat32Parameter a, hkSimdFloat32Parameter b)
{
	switch (A)
	{
		case HK_ACC_23_BIT: { hkFloat32 x = hkMath::rcpF32Approx23Bit(hkFloat32(b.m_real)); self = a.m_real * hkFloat32(x); } break;
		case HK_ACC_12_BIT: { hkFloat32 x = hkMath::rcpF32Approx12Bit(hkFloat32(b.m_real)); self = a.m_real * hkFloat32(x); } break;
		default:         self = a.m_real / b.m_real; break; // HK_ACC_FULL
	}
} };
template <hkMathAccuracyMode A>
struct unroll_setDiv<A, HK_DIV_SET_ZERO> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, hkSimdFloat32Parameter a, hkSimdFloat32Parameter b)
{
	if (b.m_real == hkFloat32(0)) { self = hkFloat32(0); return; }
	unroll_setDiv<A, HK_DIV_IGNORE>::apply(self,a,b);
} };
template <hkMathAccuracyMode A>
struct unroll_setDiv<A, HK_DIV_SET_HIGH> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, hkSimdFloat32Parameter a, hkSimdFloat32Parameter b)
{
	if (b.m_real == hkFloat32(0)) { self = (a.m_real < 0) ? -HK_FLOAT_HIGH : HK_FLOAT_HIGH; return; }
	unroll_setDiv<A, HK_DIV_IGNORE>::apply(self,a,b);
} };
template <hkMathAccuracyMode A>
struct unroll_setDiv<A, HK_DIV_SET_MAX> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, hkSimdFloat32Parameter a, hkSimdFloat32Parameter b)
{
	if (b.m_real == hkFloat32(0)) { self = (a.m_real < 0) ? -HK_FLOAT_MAX : HK_FLOAT_MAX; return; }
	unroll_setDiv<A, HK_DIV_IGNORE>::apply(self,a,b);
} };
template <hkMathAccuracyMode A>
struct unroll_setDiv<A, HK_DIV_SET_ZERO_AND_ONE> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, hkSimdFloat32Parameter a, hkSimdFloat32Parameter b)
{
	unroll_setDiv<A, HK_DIV_SET_ZERO>::apply(self,a,b);
	const hkSingleFloat32 absValLessOne = hkMath::fabs(self - hkFloat32(1));
	if (absValLessOne <= HK_FLOAT_EPSILON)
		self = hkFloat32(1);
} };

} // namespace 

template <hkMathAccuracyMode A, hkMathDivByZeroMode D> 
HK_FORCE_INLINE void hkSimdFloat32::setDiv(hkSimdFloat32Parameter a, hkSimdFloat32Parameter b)
{
	hkSimdFloat32_AdvancedInterface::unroll_setDiv<A,D>::apply(m_real,a,b);
}

HK_FORCE_INLINE void hkSimdFloat32::setDiv(hkSimdFloat32Parameter a, hkSimdFloat32Parameter b)
{
	hkSimdFloat32_AdvancedInterface::unroll_setDiv<HK_ACC_23_BIT,HK_DIV_IGNORE>::apply(m_real,a,b);
}

template <hkMathAccuracyMode A, hkMathDivByZeroMode D> 
HK_FORCE_INLINE void hkSimdFloat32::div(hkSimdFloat32Parameter a)
{
	setDiv<A,D>( *this, a );
}

HK_FORCE_INLINE void hkSimdFloat32::div(hkSimdFloat32Parameter a)
{
	setDiv( *this, a );
}

HK_FORCE_INLINE const hkSimdFloat32 hkSimdFloat32::operator/ (hkSimdFloat32Parameter r) const
{
	hkSimdFloat32 q;
	q.setDiv(*this,r);
	return q;
}



namespace hkSimdFloat32_AdvancedInterface
{

template <hkMathAccuracyMode A, hkMathNegSqrtMode S>
struct unroll_sqrt { HK_FORCE_INLINE static hkSingleFloat32 apply(hkSimdFloat32Parameter self)
{
	HK_SIMDFLOAT_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
	return hkFloat32(0);
} };
template <hkMathAccuracyMode A>
struct unroll_sqrt<A, HK_SQRT_IGNORE> { HK_FORCE_INLINE static hkSingleFloat32 apply(hkSimdFloat32Parameter self)
{
	switch (A)
	{
		case HK_ACC_23_BIT: return hkFloat32( hkFloat32(self.m_real) * hkMath::invSqrtF32Approx23Bit(hkFloat32(self.m_real)) ); break;
		case HK_ACC_12_BIT: return hkFloat32( hkFloat32(self.m_real) * hkMath::invSqrtF32Approx12Bit(hkFloat32(self.m_real)) ); break;
		default:         return hkMath::sqrt(self.m_real); break; // HK_ACC_FULL
	}
} };
template <hkMathAccuracyMode A>
struct unroll_sqrt<A, HK_SQRT_SET_ZERO> { HK_FORCE_INLINE static hkSingleFloat32 apply(hkSimdFloat32Parameter self)
{
	if (self.m_real <= hkFloat32(0)) { return hkFloat32(0); }
	return unroll_sqrt<A, HK_SQRT_IGNORE>::apply(self);
} };

} // namespace 

template <hkMathAccuracyMode A, hkMathNegSqrtMode S> 
HK_FORCE_INLINE const hkSimdFloat32 hkSimdFloat32::sqrt() const
{
	return hkSimdFloat32::convert(hkSimdFloat32_AdvancedInterface::unroll_sqrt<A,S>::apply(*this));
}
HK_FORCE_INLINE const hkSimdFloat32 hkSimdFloat32::sqrt() const
{
	return hkSimdFloat32::convert(hkSimdFloat32_AdvancedInterface::unroll_sqrt<HK_ACC_23_BIT,HK_SQRT_SET_ZERO>::apply(*this));
}



namespace hkSimdFloat32_AdvancedInterface
{

template <hkMathAccuracyMode A, hkMathNegSqrtMode S>
struct unroll_sqrtInverse { HK_FORCE_INLINE static hkSingleFloat32 apply(hkSimdFloat32Parameter self)
{
	HK_SIMDFLOAT_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
	return hkFloat32(0);
} };
template <hkMathAccuracyMode A>
struct unroll_sqrtInverse<A, HK_SQRT_IGNORE> { HK_FORCE_INLINE static hkSingleFloat32 apply(hkSimdFloat32Parameter self)
{
	switch (A)
	{
		case HK_ACC_23_BIT: return hkFloat32(hkMath::invSqrtF32Approx23Bit(hkFloat32(self.m_real))); break;
		case HK_ACC_12_BIT: return hkFloat32(hkMath::invSqrtF32Approx12Bit(hkFloat32(self.m_real))); break;
		default:			return hkMath::sqrtInverse(self.m_real); break; // HK_ACC_FULL
	}
} };
template <hkMathAccuracyMode A>
struct unroll_sqrtInverse<A, HK_SQRT_SET_ZERO> { HK_FORCE_INLINE static hkSingleFloat32 apply(hkSimdFloat32Parameter self)
{
	if (self.m_real <= hkFloat32(0)) return hkFloat32(0);
	return unroll_sqrtInverse<A, HK_SQRT_IGNORE>::apply(self);
} };
} // namespace 

template <hkMathAccuracyMode A, hkMathNegSqrtMode S> 
HK_FORCE_INLINE const hkSimdFloat32 hkSimdFloat32::sqrtInverse() const
{
	return hkSimdFloat32::convert(hkSimdFloat32_AdvancedInterface::unroll_sqrtInverse<A,S>::apply(*this));
}

HK_FORCE_INLINE const hkSimdFloat32 hkSimdFloat32::sqrtInverse() const
{
	return hkSimdFloat32::convert(hkSimdFloat32_AdvancedInterface::unroll_sqrtInverse<HK_ACC_23_BIT,HK_SQRT_SET_ZERO>::apply(*this));
}




namespace hkSimdFloat32_AdvancedInterface
{
template <hkMathIoMode A>
struct unroll_load { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, const hkFloat32* HK_RESTRICT p)
{
	HK_SIMDFLOAT_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <hkMathIoMode A>
struct unroll_load_D { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, const hkDouble64* HK_RESTRICT p)
{
	HK_SIMDFLOAT_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <>
struct unroll_load<HK_IO_BYTE_ALIGNED> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, const hkFloat32* HK_RESTRICT p)
{
	self = hkFloat32(p[0]);
} };
template <>
struct unroll_load_D<HK_IO_BYTE_ALIGNED> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, const hkDouble64* HK_RESTRICT p)
{
	self = hkFloat32(p[0]);
} };
template <>
struct unroll_load<HK_IO_NATIVE_ALIGNED> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, const hkFloat32* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & (sizeof(hkFloat32)-1) ) == 0, "pointer must be aligned to native size of hkFloat32.");
	self = hkFloat32(p[0]);
} };
template <>
struct unroll_load_D<HK_IO_NATIVE_ALIGNED> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, const hkDouble64* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & (sizeof(hkDouble64)-1) ) == 0, "pointer must be aligned to native size of hkDouble64.");
	self = hkFloat32(p[0]);
} };
template <>
struct unroll_load<HK_IO_SIMD_ALIGNED> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, const hkFloat32* HK_RESTRICT p)
{
	unroll_load<HK_IO_NATIVE_ALIGNED>::apply(self,p);
} };
template <>
struct unroll_load_D<HK_IO_SIMD_ALIGNED> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, const hkDouble64* HK_RESTRICT p)
{
	unroll_load_D<HK_IO_NATIVE_ALIGNED>::apply(self,p);
} };
template <>
struct unroll_load<HK_IO_NOT_CACHED> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, const hkFloat32* HK_RESTRICT p)
{
	unroll_load<HK_IO_SIMD_ALIGNED>::apply(self,p);
} };
template <>
struct unroll_load_D<HK_IO_NOT_CACHED> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, const hkDouble64* HK_RESTRICT p)
{
	unroll_load_D<HK_IO_SIMD_ALIGNED>::apply(self,p);
} };
} // namespace 

template <int N, hkMathIoMode A>
HK_FORCE_INLINE void hkSimdFloat32::load(const hkFloat32 *p )
{
	HK_SIMDFLOAT_DIMENSION_CHECK;
	hkSimdFloat32_AdvancedInterface::unroll_load<A>::apply(m_real, p);
}

template <int N, hkMathIoMode A>
HK_FORCE_INLINE void hkSimdFloat32::load(const hkDouble64 *p )
{
	HK_SIMDFLOAT_DIMENSION_CHECK;
	hkSimdFloat32_AdvancedInterface::unroll_load_D<A>::apply(m_real, p);
}

template <int N>
HK_FORCE_INLINE void hkSimdFloat32::load(const hkFloat32 *p )
{
	HK_SIMDFLOAT_DIMENSION_CHECK;
	hkSimdFloat32_AdvancedInterface::unroll_load<HK_IO_SIMD_ALIGNED>::apply(m_real, p);
}

template <int N>
HK_FORCE_INLINE void hkSimdFloat32::load(const hkDouble64 *p )
{
	HK_SIMDFLOAT_DIMENSION_CHECK;
	hkSimdFloat32_AdvancedInterface::unroll_load_D<HK_IO_SIMD_ALIGNED>::apply(m_real, p);
}



namespace hkSimdFloat32_AdvancedInterface
{
template <hkMathIoMode A>
struct unroll_loadH { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, const hkHalf* HK_RESTRICT p)
{
	HK_SIMDFLOAT_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <>
struct unroll_loadH<HK_IO_BYTE_ALIGNED> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, const hkHalf* HK_RESTRICT p)
{
	self = p[0].getFloat32();
} };
template <>
struct unroll_loadH<HK_IO_NATIVE_ALIGNED> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, const hkHalf* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & (sizeof(hkHalf)-1) ) == 0, "pointer must be aligned to native size of hkHalf.");
	self = p[0].getFloat32();
} };
template <>
struct unroll_loadH<HK_IO_SIMD_ALIGNED> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, const hkHalf* HK_RESTRICT p)
{
	unroll_loadH<HK_IO_NATIVE_ALIGNED>::apply(self,p);
} };
template <>
struct unroll_loadH<HK_IO_NOT_CACHED> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, const hkHalf* HK_RESTRICT p)
{
	unroll_loadH<HK_IO_SIMD_ALIGNED>::apply(self,p);
} };
} // namespace 

template <int N, hkMathIoMode A>
HK_FORCE_INLINE void hkSimdFloat32::load(const hkHalf *p )
{
	HK_SIMDFLOAT_DIMENSION_CHECK;
	hkSimdFloat32_AdvancedInterface::unroll_loadH<A>::apply(m_real, p);
}

template <int N>
HK_FORCE_INLINE void hkSimdFloat32::load(const hkHalf *p )
{
	HK_SIMDFLOAT_DIMENSION_CHECK;
	hkSimdFloat32_AdvancedInterface::unroll_loadH<HK_IO_SIMD_ALIGNED>::apply(m_real, p);
}




namespace hkSimdFloat32_AdvancedInterface
{
template <hkMathIoMode A>
struct unroll_loadF16 { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, const hkFloat16* HK_RESTRICT p)
{
	HK_SIMDFLOAT_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <>
struct unroll_loadF16<HK_IO_BYTE_ALIGNED> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, const hkFloat16* HK_RESTRICT p)
{
	self = p[0].getFloat32();
} };
template <>
struct unroll_loadF16<HK_IO_NATIVE_ALIGNED> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, const hkFloat16* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & (sizeof(hkFloat16)-1) ) == 0, "pointer must be aligned to native size of hkFloat16.");
	self = p[0].getFloat32();
} };
template <>
struct unroll_loadF16<HK_IO_SIMD_ALIGNED> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, const hkFloat16* HK_RESTRICT p)
{
	unroll_loadF16<HK_IO_NATIVE_ALIGNED>::apply(self,p);
} };
template <>
struct unroll_loadF16<HK_IO_NOT_CACHED> { HK_FORCE_INLINE static void apply(hkSingleFloat32& self, const hkFloat16* HK_RESTRICT p)
{
	unroll_loadF16<HK_IO_SIMD_ALIGNED>::apply(self,p);
} };
} // namespace 

template <int N, hkMathIoMode A>
HK_FORCE_INLINE void hkSimdFloat32::load(const hkFloat16 *p )
{
	HK_SIMDFLOAT_DIMENSION_CHECK;
	hkSimdFloat32_AdvancedInterface::unroll_loadF16<A>::apply(m_real, p);
}

template <int N>
HK_FORCE_INLINE void hkSimdFloat32::load(const hkFloat16 *p )
{
	HK_SIMDFLOAT_DIMENSION_CHECK;
	hkSimdFloat32_AdvancedInterface::unroll_loadF16<HK_IO_SIMD_ALIGNED>::apply(m_real, p);
}



namespace hkSimdFloat32_AdvancedInterface
{
template <hkMathIoMode A>
struct unroll_store { HK_FORCE_INLINE static void apply(const hkSingleFloat32& self, hkFloat32* HK_RESTRICT p)
{
	HK_SIMDFLOAT_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <hkMathIoMode A>
struct unroll_store_D { HK_FORCE_INLINE static void apply(const hkSingleFloat32& self, hkDouble64* HK_RESTRICT p)
{
	HK_SIMDFLOAT_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <>
struct unroll_store<HK_IO_BYTE_ALIGNED> { HK_FORCE_INLINE static void apply(const hkSingleFloat32& self, hkFloat32* HK_RESTRICT p)
{
	p[0] = hkFloat32(self);
} };
template <>
struct unroll_store_D<HK_IO_BYTE_ALIGNED> { HK_FORCE_INLINE static void apply(const hkSingleFloat32& self, hkDouble64* HK_RESTRICT p)
{
	p[0] = hkDouble64(self);
} };
template <>
struct unroll_store<HK_IO_NATIVE_ALIGNED> { HK_FORCE_INLINE static void apply(const hkSingleFloat32& self, hkFloat32* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & (sizeof(hkFloat32)-1) ) == 0, "pointer must be aligned to native size of hkFloat32.");
	p[0] = hkFloat32(self);
} };
template <>
struct unroll_store_D<HK_IO_NATIVE_ALIGNED> { HK_FORCE_INLINE static void apply(const hkSingleFloat32& self, hkDouble64* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & (sizeof(hkDouble64)-1) ) == 0, "pointer must be aligned to native size of hkDouble64.");
	p[0] = hkDouble64(self);
} };
template <>
struct unroll_store<HK_IO_SIMD_ALIGNED> { HK_FORCE_INLINE static void apply(const hkSingleFloat32& self, hkFloat32* HK_RESTRICT p)
{
	unroll_store<HK_IO_NATIVE_ALIGNED>::apply(self,p);
} };
template <>
struct unroll_store_D<HK_IO_SIMD_ALIGNED> { HK_FORCE_INLINE static void apply(const hkSingleFloat32& self, hkDouble64* HK_RESTRICT p)
{
	unroll_store_D<HK_IO_NATIVE_ALIGNED>::apply(self,p);
} };
template <>
struct unroll_store<HK_IO_NOT_CACHED> { HK_FORCE_INLINE static void apply(const hkSingleFloat32& self, hkFloat32* HK_RESTRICT p)
{
	unroll_store<HK_IO_SIMD_ALIGNED>::apply(self,p);
} };
template <>
struct unroll_store_D<HK_IO_NOT_CACHED> { HK_FORCE_INLINE static void apply(const hkSingleFloat32& self, hkDouble64* HK_RESTRICT p)
{
	unroll_store_D<HK_IO_SIMD_ALIGNED>::apply(self,p);
} };
} // namespace 

template <int N, hkMathIoMode A, hkMathRoundingMode R>
HK_FORCE_INLINE void hkSimdFloat32::store(  hkFloat32 *p ) const
{
	HK_SIMDFLOAT_DIMENSION_CHECK;
	hkSimdFloat32_AdvancedInterface::unroll_store<A>::apply(m_real, p);
}

template <int N, hkMathIoMode A, hkMathRoundingMode R>
HK_FORCE_INLINE void hkSimdFloat32::store(  hkDouble64 *p ) const
{
	HK_SIMDFLOAT_DIMENSION_CHECK;
	hkSimdFloat32_AdvancedInterface::unroll_store_D<A>::apply(m_real, p);
}

template <int N, hkMathIoMode A>
HK_FORCE_INLINE void hkSimdFloat32::store(  hkFloat32 *p ) const
{
	HK_SIMDFLOAT_DIMENSION_CHECK;
	hkSimdFloat32_AdvancedInterface::unroll_store<A>::apply(m_real, p);
}

template <int N, hkMathIoMode A>
HK_FORCE_INLINE void hkSimdFloat32::store(  hkDouble64 *p ) const
{
	HK_SIMDFLOAT_DIMENSION_CHECK;
	hkSimdFloat32_AdvancedInterface::unroll_store_D<A>::apply(m_real, p);
}

template <int N>
HK_FORCE_INLINE void hkSimdFloat32::store(  hkFloat32 *p ) const
{
	HK_SIMDFLOAT_DIMENSION_CHECK;
	hkSimdFloat32_AdvancedInterface::unroll_store<HK_IO_SIMD_ALIGNED>::apply(m_real, p);
}

template <int N>
HK_FORCE_INLINE void hkSimdFloat32::store(  hkDouble64 *p ) const
{
	HK_SIMDFLOAT_DIMENSION_CHECK;
	hkSimdFloat32_AdvancedInterface::unroll_store_D<HK_IO_SIMD_ALIGNED>::apply(m_real, p);
}




namespace hkSimdFloat32_AdvancedInterface
{
template <hkMathIoMode A, hkMathRoundingMode R>
struct unroll_storeH { HK_FORCE_INLINE static void apply(const hkSingleFloat32& self, hkHalf* HK_RESTRICT p)
{
	HK_SIMDFLOAT_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <hkMathRoundingMode R>
struct unroll_storeH<HK_IO_BYTE_ALIGNED,R> { HK_FORCE_INLINE static void apply(const hkSingleFloat32& self, hkHalf* HK_RESTRICT p)
{
	p[0].setReal<(R == HK_ROUND_NEAREST)>(self);
} };
template <hkMathRoundingMode R>
struct unroll_storeH<HK_IO_NATIVE_ALIGNED,R> { HK_FORCE_INLINE static void apply(const hkSingleFloat32& self, hkHalf* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & (sizeof(hkHalf)-1) ) == 0, "pointer must be aligned to native size of hkHalf.");
	p[0].setReal<(R == HK_ROUND_NEAREST)>(self);
} };
template <hkMathRoundingMode R>
struct unroll_storeH<HK_IO_SIMD_ALIGNED,R> { HK_FORCE_INLINE static void apply(const hkSingleFloat32& self, hkHalf* HK_RESTRICT p)
{
	unroll_storeH<HK_IO_NATIVE_ALIGNED,R>::apply(self,p);
} };
template <hkMathRoundingMode R>
struct unroll_storeH<HK_IO_NOT_CACHED,R> { HK_FORCE_INLINE static void apply(const hkSingleFloat32& self, hkHalf* HK_RESTRICT p)
{
	unroll_storeH<HK_IO_SIMD_ALIGNED,R>::apply(self,p);
} };
} // namespace 

template <int N, hkMathIoMode A, hkMathRoundingMode R>
HK_FORCE_INLINE void hkSimdFloat32::store(  hkHalf *p ) const
{
	HK_SIMDFLOAT_DIMENSION_CHECK;
	hkSimdFloat32_AdvancedInterface::unroll_storeH<A,R>::apply(m_real, p);
}

template <int N>
HK_FORCE_INLINE void hkSimdFloat32::store(  hkHalf *p ) const
{
	HK_SIMDFLOAT_DIMENSION_CHECK;
	hkSimdFloat32_AdvancedInterface::unroll_storeH<HK_IO_SIMD_ALIGNED,HK_ROUND_DEFAULT>::apply(m_real, p);
}


namespace hkSimdFloat32_AdvancedInterface
{
template <hkMathIoMode A, hkMathRoundingMode R>
struct unroll_storeF16 { HK_FORCE_INLINE static void apply(const hkSingleFloat32& self, hkFloat16* HK_RESTRICT p)
{
	HK_SIMDFLOAT_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <hkMathRoundingMode R>
struct unroll_storeF16<HK_IO_BYTE_ALIGNED,R> { HK_FORCE_INLINE static void apply(const hkSingleFloat32& self, hkFloat16* HK_RESTRICT p)
{
	p[0].setReal<(R == HK_ROUND_NEAREST)>(self);
} };
template <hkMathRoundingMode R>
struct unroll_storeF16<HK_IO_NATIVE_ALIGNED,R> { HK_FORCE_INLINE static void apply(const hkSingleFloat32& self, hkFloat16* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & (sizeof(hkFloat16)-1) ) == 0, "pointer must be aligned to native size of hkFloat16.");
	p[0].setReal<(R == HK_ROUND_NEAREST)>(self);
} };
template <hkMathRoundingMode R>
struct unroll_storeF16<HK_IO_SIMD_ALIGNED,R> { HK_FORCE_INLINE static void apply(const hkSingleFloat32& self, hkFloat16* HK_RESTRICT p)
{
	unroll_storeF16<HK_IO_NATIVE_ALIGNED,R>::apply(self,p);
} };
template <hkMathRoundingMode R>
struct unroll_storeF16<HK_IO_NOT_CACHED,R> { HK_FORCE_INLINE static void apply(const hkSingleFloat32& self, hkFloat16* HK_RESTRICT p)
{
	unroll_storeF16<HK_IO_SIMD_ALIGNED,R>::apply(self,p);
} };
} // namespace 

template <int N, hkMathIoMode A, hkMathRoundingMode R>
HK_FORCE_INLINE void hkSimdFloat32::store(  hkFloat16 *p ) const
{
	HK_SIMDFLOAT_DIMENSION_CHECK;
	hkSimdFloat32_AdvancedInterface::unroll_storeF16<A,R>::apply(m_real, p);
}

template <int N>
HK_FORCE_INLINE void hkSimdFloat32::store(  hkFloat16 *p ) const
{
	HK_SIMDFLOAT_DIMENSION_CHECK;
	hkSimdFloat32_AdvancedInterface::unroll_storeF16<HK_IO_SIMD_ALIGNED,HK_ROUND_DEFAULT>::apply(m_real, p);
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
