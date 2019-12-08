/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

HK_FORCE_INLINE /*static*/ const hkSimdDouble64 HK_CALL hkSimdDouble64::convert(const hkSingleDouble64& x)
{
	hkSimdDouble64 sr;
	sr.m_real = x;
	return sr;
}

template<int vectorConstant>
HK_FORCE_INLINE /*static*/ const hkSimdDouble64 HK_CALL hkSimdDouble64::getConstant()
{
	HK_COMPILE_TIME_ASSERT2( 
		(vectorConstant!=HK_QUADREAL_1000) && (vectorConstant!=HK_QUADREAL_0100) && (vectorConstant!=HK_QUADREAL_0010) && (vectorConstant!=HK_QUADREAL_0001) &&
		(vectorConstant!=HK_QUADREAL_m11m11) && (vectorConstant!=HK_QUADREAL_1248) && (vectorConstant!=HK_QUADREAL_8421) && (vectorConstant!=HK_QUADREAL_1010)  && (vectorConstant!=HK_QUADREAL_1100)
		, HK_SIMDDOUBLE_ILLEGAL_CONSTANT_REQUEST);
	return convert((g_vectordConstants + vectorConstant)->v[0]);
}

HK_FORCE_INLINE /*static*/ const hkSimdDouble64 HK_CALL hkSimdDouble64::getConstant(hkVectorConstant constant)
{	
	HK_MATH_ASSERT( 0x909ff234,
		(constant!=HK_QUADREAL_1000) && (constant!=HK_QUADREAL_0100) && (constant!=HK_QUADREAL_0010) && (constant!=HK_QUADREAL_0001) &&
		(constant!=HK_QUADREAL_m11m11) && (constant!=HK_QUADREAL_1248) && (constant!=HK_QUADREAL_8421) && (constant!=HK_QUADREAL_1010)  && (constant!=HK_QUADREAL_1100)
		, "not a simdreal constant");
	return convert((g_vectordConstants + constant)->v[0]);
}

#ifndef HK_DISABLE_IMPLICIT_SIMDREAL_FLOAT_CONVERSION
HK_FORCE_INLINE hkSimdDouble64::hkSimdDouble64(const hkDouble64& x)
{
	m_real = x;
}

HK_FORCE_INLINE hkSimdDouble64::operator hkDouble64() const
{
	return m_real;
}
#endif

HK_FORCE_INLINE hkDouble64 hkSimdDouble64::getReal() const
{
	return m_real;
}

HK_FORCE_INLINE void hkSimdDouble64::setFromFloat(const hkFloat32& x)
{
	m_real = hkDouble64(x);
}

HK_FORCE_INLINE void hkSimdDouble64::setFromFloat(const hkDouble64& x)
{
	m_real = hkDouble64(x);
}

HK_FORCE_INLINE void hkSimdDouble64::setFromHalf(const hkHalf& h)
{
	m_real = h.getDouble();
}

HK_FORCE_INLINE void hkSimdDouble64::setFromInt32(const hkInt32&  x)
{
	m_real = hkDouble64(x);
}

HK_FORCE_INLINE void hkSimdDouble64::setFromUint16(const hkUint16& x)
{
	int i = x;
	setFromInt32(i);
}

HK_FORCE_INLINE void hkSimdDouble64::setFromUint8(const hkUint8& x)
{
	int i = x;
	setFromInt32(i);
}
HK_FORCE_INLINE void hkSimdDouble64::setZero()
{
	m_real = hkDouble64(0);
}

HK_FORCE_INLINE void hkSimdDouble64::storeSaturateInt32(hkInt32* HK_RESTRICT result) const
{
	*result = hkMath::hkToIntFast(m_real);
}


HK_FORCE_INLINE void hkSimdDouble64::storeSaturateUint16(hkUint16* result) const
{
	const hkInt32 i = hkMath::hkToIntFast(m_real);
	const hkInt32 clampPos    = hkMath::max2(i, 0x0);
	const hkInt32 clampPosNeg = hkMath::min2(clampPos, 0xffff);
	*result = hkUint16(clampPosNeg);
}


HK_FORCE_INLINE const hkSimdDouble64 hkSimdDouble64::operator+ (hkSimdDouble64Parameter r) const
{
	return hkSimdDouble64::convert(m_real + r.m_real);
}

HK_FORCE_INLINE const hkSimdDouble64 hkSimdDouble64::operator- (hkSimdDouble64Parameter r) const
{
	return hkSimdDouble64::convert(m_real - r.m_real);
}

HK_FORCE_INLINE const hkSimdDouble64 hkSimdDouble64::operator* (hkSimdDouble64Parameter r) const
{
	return hkSimdDouble64::convert(m_real * r.m_real);
}


#ifdef HK_DISABLE_OLD_VECTOR4_INTERFACE

HK_FORCE_INLINE bool hkSimdDouble64::operator< (hkSimdDouble64Parameter r) const
{
	return (m_real < r.m_real);
}

HK_FORCE_INLINE bool hkSimdDouble64::operator<= (hkSimdDouble64Parameter r) const
{
	return (m_real <= r.m_real);
}

HK_FORCE_INLINE bool hkSimdDouble64::operator> (hkSimdDouble64Parameter r) const
{
	return (m_real > r.m_real);
}

HK_FORCE_INLINE bool hkSimdDouble64::operator>= (hkSimdDouble64Parameter r) const
{
	return (m_real >= r.m_real);
}

HK_FORCE_INLINE bool hkSimdDouble64::operator== (hkSimdDouble64Parameter r) const
{
	return (m_real == r.m_real);
}

HK_FORCE_INLINE bool hkSimdDouble64::operator!= (hkSimdDouble64Parameter r) const
{
	return (m_real != r.m_real);
}

#endif

HK_FORCE_INLINE const hkSimdDouble64 hkSimdDouble64::operator-() const
{
	return hkSimdDouble64::convert(-m_real);
}

HK_FORCE_INLINE const hkVector4dComparison hkSimdDouble64::less(hkSimdDouble64Parameter a) const
{
	hkVector4dComparison res;
	res.m_mask = (m_real < a.m_real) ? hkVector4ComparisonMask::MASK_XYZW : hkVector4ComparisonMask::MASK_NONE;
	return res;
}

HK_FORCE_INLINE const hkVector4dComparison hkSimdDouble64::greater(hkSimdDouble64Parameter a) const
{
	hkVector4dComparison res;
	res.m_mask = (m_real > a.m_real) ? hkVector4ComparisonMask::MASK_XYZW : hkVector4ComparisonMask::MASK_NONE;
	return res;
}

HK_FORCE_INLINE const hkVector4dComparison hkSimdDouble64::greaterEqual(hkSimdDouble64Parameter a) const
{
	hkVector4dComparison res;
	res.m_mask = (m_real >= a.m_real) ? hkVector4ComparisonMask::MASK_XYZW : hkVector4ComparisonMask::MASK_NONE;
	return res;
}

HK_FORCE_INLINE const hkVector4dComparison hkSimdDouble64::lessEqual(hkSimdDouble64Parameter a) const
{
	hkVector4dComparison res;
	res.m_mask = (m_real <= a.m_real) ? hkVector4ComparisonMask::MASK_XYZW : hkVector4ComparisonMask::MASK_NONE;
	return res;
}

HK_FORCE_INLINE const hkVector4dComparison hkSimdDouble64::equal(hkSimdDouble64Parameter a) const
{
	hkVector4dComparison res;
	res.m_mask = (m_real == a.m_real) ? hkVector4ComparisonMask::MASK_XYZW : hkVector4ComparisonMask::MASK_NONE;
	return res;
}

HK_FORCE_INLINE const hkVector4dComparison hkSimdDouble64::notEqual(hkSimdDouble64Parameter a) const
{
	hkVector4dComparison res;
	res.m_mask = (m_real != a.m_real) ? hkVector4ComparisonMask::MASK_XYZW : hkVector4ComparisonMask::MASK_NONE;
	return res;
}

HK_FORCE_INLINE const hkVector4dComparison hkSimdDouble64::lessZero() const
{
	hkVector4dComparison res;
	res.m_mask = (m_real < hkDouble64(0)) ? hkVector4ComparisonMask::MASK_XYZW : hkVector4ComparisonMask::MASK_NONE;
	return res;
}

HK_FORCE_INLINE const hkVector4dComparison hkSimdDouble64::lessEqualZero() const
{
	hkVector4dComparison res;
	res.m_mask = (m_real <= hkDouble64(0)) ? hkVector4ComparisonMask::MASK_XYZW : hkVector4ComparisonMask::MASK_NONE;
	return res;
}

HK_FORCE_INLINE const hkVector4dComparison hkSimdDouble64::greaterZero() const
{
	hkVector4dComparison res;
	res.m_mask = (m_real > hkDouble64(0)) ? hkVector4ComparisonMask::MASK_XYZW : hkVector4ComparisonMask::MASK_NONE;
	return res;
}

HK_FORCE_INLINE const hkVector4dComparison hkSimdDouble64::greaterEqualZero() const
{
	hkVector4dComparison res;
	res.m_mask = (m_real >= hkDouble64(0)) ? hkVector4ComparisonMask::MASK_XYZW : hkVector4ComparisonMask::MASK_NONE;
	return res;
}

HK_FORCE_INLINE const hkVector4dComparison hkSimdDouble64::equalZero() const
{
	hkVector4dComparison res;
	res.m_mask = (m_real == hkDouble64(0)) ? hkVector4ComparisonMask::MASK_XYZW : hkVector4ComparisonMask::MASK_NONE;
	return res;
}

HK_FORCE_INLINE const hkVector4dComparison hkSimdDouble64::notEqualZero() const
{
	hkVector4dComparison res;
	res.m_mask = (m_real != hkDouble64(0)) ? hkVector4ComparisonMask::MASK_XYZW : hkVector4ComparisonMask::MASK_NONE;
	return res;
}

HK_FORCE_INLINE hkBool32 hkSimdDouble64::isSignBitSet() const
{
	return hkMath::signBitSet(m_real);
}

HK_FORCE_INLINE hkBool32 hkSimdDouble64::isSignBitClear() const
{
	return !hkMath::signBitSet(m_real);
}

HK_FORCE_INLINE const hkVector4dComparison hkSimdDouble64::signBitSet() const
{
	hkVector4dComparison res;
	res.m_mask = hkMath::signBitSet(m_real) ? hkVector4ComparisonMask::MASK_XYZW : hkVector4ComparisonMask::MASK_NONE;
	return res;
}

HK_FORCE_INLINE const hkVector4dComparison hkSimdDouble64::signBitClear() const
{
	hkVector4dComparison res;
	res.m_mask = hkMath::signBitSet(m_real) ? hkVector4ComparisonMask::MASK_NONE : hkVector4ComparisonMask::MASK_XYZW;
	return res;
}

HK_FORCE_INLINE hkBool32 hkSimdDouble64::isLess(hkSimdDouble64Parameter a) const
{
	return (m_real < a.m_real);
}

HK_FORCE_INLINE hkBool32 hkSimdDouble64::isLessEqual(hkSimdDouble64Parameter a) const
{
	return (m_real <= a.m_real);
}

HK_FORCE_INLINE hkBool32 hkSimdDouble64::isGreater(hkSimdDouble64Parameter a) const
{
	return (m_real > a.m_real);
}

HK_FORCE_INLINE hkBool32 hkSimdDouble64::isGreaterEqual(hkSimdDouble64Parameter a) const
{
	return (m_real >= a.m_real);
}

HK_FORCE_INLINE hkBool32 hkSimdDouble64::isEqual(hkSimdDouble64Parameter a) const
{
	return (m_real == a.m_real);
}

HK_FORCE_INLINE hkBool32 hkSimdDouble64::isNotEqual(hkSimdDouble64Parameter a) const
{
	return (m_real != a.m_real);
}

HK_FORCE_INLINE hkBool32 hkSimdDouble64::isLessZero() const
{
	return (m_real < hkDouble64(0));
}

HK_FORCE_INLINE hkBool32 hkSimdDouble64::isLessEqualZero() const
{
	return (m_real <= hkDouble64(0));
}

HK_FORCE_INLINE hkBool32 hkSimdDouble64::isGreaterZero() const
{
	return (m_real > hkDouble64(0));
}

HK_FORCE_INLINE hkBool32 hkSimdDouble64::isGreaterEqualZero() const
{
	return (m_real >= hkDouble64(0));
}

HK_FORCE_INLINE hkBool32 hkSimdDouble64::isEqualZero() const
{
	return (m_real == hkDouble64(0));
}

HK_FORCE_INLINE hkBool32 hkSimdDouble64::isNotEqualZero() const
{
	return (m_real != hkDouble64(0));
}

HK_FORCE_INLINE hkBool32 hkSimdDouble64::isOk() const
{
	return hkMath::isFinite(m_real);
}

HK_FORCE_INLINE void hkSimdDouble64::setSelect( hkVector4dComparisonParameter comp, hkSimdDouble64Parameter a, hkSimdDouble64Parameter b )
{
	HK_MATH_ASSERT(0x125f0f99, comp.allAreSet() || (comp.getMask() == hkVector4ComparisonMask::MASK_NONE), "illegal compare mask");
	m_real = comp.m_mask ? a.m_real : b.m_real;
}

HK_FORCE_INLINE void hkSimdDouble64::zeroIfFalse( hkVector4dComparisonParameter comp )
{
	HK_MATH_ASSERT(0x125f0f99, comp.allAreSet() || (comp.getMask() == hkVector4ComparisonMask::MASK_NONE), "illegal compare mask");
	m_real = comp.m_mask ? m_real : hkDouble64(0);
}

HK_FORCE_INLINE void hkSimdDouble64::zeroIfTrue( hkVector4dComparisonParameter comp )
{
	HK_MATH_ASSERT(0x125f0f99, comp.allAreSet() || (comp.getMask() == hkVector4ComparisonMask::MASK_NONE), "illegal compare mask");
	m_real = comp.m_mask ? hkDouble64(0) : m_real;
}

HK_FORCE_INLINE void hkSimdDouble64::setMin(  hkSimdDouble64Parameter a, hkSimdDouble64Parameter b ) 
{
	m_real = hkMath::min2( a.m_real, b.m_real );
}

HK_FORCE_INLINE void hkSimdDouble64::setMax(  hkSimdDouble64Parameter a, hkSimdDouble64Parameter b ) 
{
	m_real = hkMath::max2( a.m_real, b.m_real );
}

HK_FORCE_INLINE void hkSimdDouble64::setAbs(  hkSimdDouble64Parameter a )
{
	m_real = hkMath::fabs(a.m_real);
}

HK_FORCE_INLINE void hkSimdDouble64::setFloor(  hkSimdDouble64Parameter a )
{
	m_real = hkMath::floor(a.m_real);
}

HK_FORCE_INLINE void hkSimdDouble64::setMod(  hkSimdDouble64Parameter a, hkSimdDouble64Parameter b )
{
	m_real = hkMath::fmod(a.m_real,b.m_real);
}

HK_FORCE_INLINE void hkSimdDouble64::setFlipSign(hkSimdDouble64Parameter v, hkSimdDouble64Parameter sSign)
{
	m_real = hkMath::signBitSet(sSign.m_real) ? -v.m_real : v.m_real;
}

HK_FORCE_INLINE void hkSimdDouble64::setFlipSign(hkSimdDouble64Parameter v, hkVector4dComparisonParameter mask)
{
	HK_MATH_ASSERT(0x39186bef, mask.allAreSet() || (mask.getMask() == hkVector4ComparisonMask::MASK_NONE), "illegal compare mask");
	m_real = mask.m_mask ? -v.m_real : v.m_real;
}

//
// advanced interface
//

namespace hkSimdDouble64_AdvancedInterface
{

template <hkMathAccuracyMode A, hkMathDivByZeroMode D>
struct unroll_setReciprocal { HK_FORCE_INLINE static void apply(hkSingleDouble64& self, hkSimdDouble64Parameter a)
{
	HK_SIMDDOUBLE_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <hkMathAccuracyMode A>
struct unroll_setReciprocal<A, HK_DIV_IGNORE> { HK_FORCE_INLINE static void apply(hkSingleDouble64& self, hkSimdDouble64Parameter a)
{
	switch (A)
	{
		case HK_ACC_23_BIT: { hkFloat32 x = hkMath::rcpF32Approx23Bit(hkFloat32(a.m_real)); self = hkDouble64(x); } break;
		case HK_ACC_12_BIT: { hkFloat32 x = hkMath::rcpF32Approx12Bit(hkFloat32(a.m_real)); self = hkDouble64(x); } break;
		default:         self = hkDouble64(1) / a.m_real; break; // HK_ACC_FULL
	}
} };
template <hkMathAccuracyMode A>
struct unroll_setReciprocal<A, HK_DIV_SET_ZERO> { HK_FORCE_INLINE static void apply(hkSingleDouble64& self, hkSimdDouble64Parameter a)
{
	if (a.m_real == hkDouble64(0)) { self = hkDouble64(0); return; }
	unroll_setReciprocal<A, HK_DIV_IGNORE>::apply(self,a);
} };
template <hkMathAccuracyMode A>
struct unroll_setReciprocal<A, HK_DIV_SET_HIGH> { HK_FORCE_INLINE static void apply(hkSingleDouble64& self, hkSimdDouble64Parameter a)
{
	if (a.m_real == hkDouble64(0)) { self = HK_DOUBLE_HIGH; return; }
	unroll_setReciprocal<A, HK_DIV_IGNORE>::apply(self,a);
} };
template <hkMathAccuracyMode A>
struct unroll_setReciprocal<A, HK_DIV_SET_MAX> { HK_FORCE_INLINE static void apply(hkSingleDouble64& self, hkSimdDouble64Parameter a)
{
	if (a.m_real == hkDouble64(0)) { self = HK_DOUBLE_MAX; return; }
	unroll_setReciprocal<A, HK_DIV_IGNORE>::apply(self,a);
} };
template <hkMathAccuracyMode A>
struct unroll_setReciprocal<A, HK_DIV_SET_ZERO_AND_ONE> { HK_FORCE_INLINE static void apply(hkSingleDouble64& self, hkSimdDouble64Parameter a)
{
	unroll_setReciprocal<A, HK_DIV_SET_ZERO>::apply(self,a);
	const hkSingleDouble64 absValLessOne = hkMath::fabs(self - hkDouble64(1));
	if (absValLessOne <= HK_DOUBLE_EPSILON)
		self = hkDouble64(1);
} };

} // namespace 

template <hkMathAccuracyMode A, hkMathDivByZeroMode D> 
HK_FORCE_INLINE void hkSimdDouble64::setReciprocal(hkSimdDouble64Parameter a)
{
	hkSimdDouble64_AdvancedInterface::unroll_setReciprocal<A,D>::apply(m_real,a);
}

HK_FORCE_INLINE void hkSimdDouble64::setReciprocal(hkSimdDouble64Parameter a)
{
	hkSimdDouble64_AdvancedInterface::unroll_setReciprocal<HK_ACC_23_BIT,HK_DIV_IGNORE>::apply(m_real,a);
}



namespace hkSimdDouble64_AdvancedInterface
{

template <hkMathAccuracyMode A, hkMathDivByZeroMode D>
struct unroll_setDiv { HK_FORCE_INLINE static void apply(hkSingleDouble64& self, hkSimdDouble64Parameter a, hkSimdDouble64Parameter b)
{
	HK_SIMDDOUBLE_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <hkMathAccuracyMode A>
struct unroll_setDiv<A, HK_DIV_IGNORE> { HK_FORCE_INLINE static void apply(hkSingleDouble64& self, hkSimdDouble64Parameter a, hkSimdDouble64Parameter b)
{
	switch (A)
	{
		case HK_ACC_23_BIT: { hkFloat32 x = hkMath::rcpF32Approx23Bit(hkFloat32(b.m_real)); self = a.m_real * hkDouble64(x); } break;
		case HK_ACC_12_BIT: { hkFloat32 x = hkMath::rcpF32Approx12Bit(hkFloat32(b.m_real)); self = a.m_real * hkDouble64(x); } break;
		default:         self = a.m_real / b.m_real; break; // HK_ACC_FULL
	}
} };
template <hkMathAccuracyMode A>
struct unroll_setDiv<A, HK_DIV_SET_ZERO> { HK_FORCE_INLINE static void apply(hkSingleDouble64& self, hkSimdDouble64Parameter a, hkSimdDouble64Parameter b)
{
	if (b.m_real == hkDouble64(0)) { self = hkDouble64(0); return; }
	unroll_setDiv<A, HK_DIV_IGNORE>::apply(self,a,b);
} };
template <hkMathAccuracyMode A>
struct unroll_setDiv<A, HK_DIV_SET_HIGH> { HK_FORCE_INLINE static void apply(hkSingleDouble64& self, hkSimdDouble64Parameter a, hkSimdDouble64Parameter b)
{
	if (b.m_real == hkDouble64(0)) { self = (a.m_real < 0) ? -HK_DOUBLE_HIGH : HK_DOUBLE_HIGH; return; }
	unroll_setDiv<A, HK_DIV_IGNORE>::apply(self,a,b);
} };
template <hkMathAccuracyMode A>
struct unroll_setDiv<A, HK_DIV_SET_MAX> { HK_FORCE_INLINE static void apply(hkSingleDouble64& self, hkSimdDouble64Parameter a, hkSimdDouble64Parameter b)
{
	if (b.m_real == hkDouble64(0)) { self = (a.m_real < 0) ? -HK_DOUBLE_MAX : HK_DOUBLE_MAX; return; }
	unroll_setDiv<A, HK_DIV_IGNORE>::apply(self,a,b);
} };
template <hkMathAccuracyMode A>
struct unroll_setDiv<A, HK_DIV_SET_ZERO_AND_ONE> { HK_FORCE_INLINE static void apply(hkSingleDouble64& self, hkSimdDouble64Parameter a, hkSimdDouble64Parameter b)
{
	unroll_setDiv<A, HK_DIV_SET_ZERO>::apply(self,a,b);
	const hkSingleDouble64 absValLessOne = hkMath::fabs(self - hkDouble64(1));
	if (absValLessOne <= HK_DOUBLE_EPSILON)
		self = hkDouble64(1);
} };

} // namespace 

template <hkMathAccuracyMode A, hkMathDivByZeroMode D> 
HK_FORCE_INLINE void hkSimdDouble64::setDiv(hkSimdDouble64Parameter a, hkSimdDouble64Parameter b)
{
	hkSimdDouble64_AdvancedInterface::unroll_setDiv<A,D>::apply(m_real,a,b);
}

HK_FORCE_INLINE void hkSimdDouble64::setDiv(hkSimdDouble64Parameter a, hkSimdDouble64Parameter b)
{
	hkSimdDouble64_AdvancedInterface::unroll_setDiv<HK_ACC_23_BIT,HK_DIV_IGNORE>::apply(m_real,a,b);
}

template <hkMathAccuracyMode A, hkMathDivByZeroMode D> 
HK_FORCE_INLINE void hkSimdDouble64::div(hkSimdDouble64Parameter a)
{
	setDiv<A,D>( *this, a );
}

HK_FORCE_INLINE void hkSimdDouble64::div(hkSimdDouble64Parameter a)
{
	setDiv( *this, a );
}

HK_FORCE_INLINE const hkSimdDouble64 hkSimdDouble64::operator/ (hkSimdDouble64Parameter r) const
{
	hkSimdDouble64 q;
	q.setDiv(*this,r);
	return q;
}



namespace hkSimdDouble64_AdvancedInterface
{

template <hkMathAccuracyMode A, hkMathNegSqrtMode S>
struct unroll_sqrt { HK_FORCE_INLINE static hkSingleDouble64 apply(hkSimdDouble64Parameter self)
{
	HK_SIMDDOUBLE_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
	return hkDouble64(0);
} };
template <hkMathAccuracyMode A>
struct unroll_sqrt<A, HK_SQRT_IGNORE> { HK_FORCE_INLINE static hkSingleDouble64 apply(hkSimdDouble64Parameter self)
{
	switch (A)
	{
		case HK_ACC_23_BIT: return hkDouble64( hkFloat32(self.m_real) * hkMath::invSqrtF32Approx23Bit(hkFloat32(self.m_real)) ); break;
		case HK_ACC_12_BIT: return hkDouble64( hkFloat32(self.m_real) * hkMath::invSqrtF32Approx12Bit(hkFloat32(self.m_real)) ); break;
		default:         return hkMath::sqrt(self.m_real); break; // HK_ACC_FULL
	}
} };
template <hkMathAccuracyMode A>
struct unroll_sqrt<A, HK_SQRT_SET_ZERO> { HK_FORCE_INLINE static hkSingleDouble64 apply(hkSimdDouble64Parameter self)
{
	if (self.m_real <= hkDouble64(0)) { return hkDouble64(0); }
	return unroll_sqrt<A, HK_SQRT_IGNORE>::apply(self);
} };

} // namespace 

template <hkMathAccuracyMode A, hkMathNegSqrtMode S> 
HK_FORCE_INLINE const hkSimdDouble64 hkSimdDouble64::sqrt() const
{
	return hkSimdDouble64::convert(hkSimdDouble64_AdvancedInterface::unroll_sqrt<A,S>::apply(*this));
}
HK_FORCE_INLINE const hkSimdDouble64 hkSimdDouble64::sqrt() const
{
	return hkSimdDouble64::convert(hkSimdDouble64_AdvancedInterface::unroll_sqrt<HK_ACC_23_BIT,HK_SQRT_SET_ZERO>::apply(*this));
}



namespace hkSimdDouble64_AdvancedInterface
{

template <hkMathAccuracyMode A, hkMathNegSqrtMode S>
struct unroll_sqrtInverse { HK_FORCE_INLINE static hkSingleDouble64 apply(hkSimdDouble64Parameter self)
{
	HK_SIMDDOUBLE_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
	return hkDouble64(0);
} };
template <hkMathAccuracyMode A>
struct unroll_sqrtInverse<A, HK_SQRT_IGNORE> { HK_FORCE_INLINE static hkSingleDouble64 apply(hkSimdDouble64Parameter self)
{
	switch (A)
	{
		case HK_ACC_23_BIT: return hkDouble64(hkMath::invSqrtF32Approx23Bit(hkFloat32(self.m_real))); break;
		case HK_ACC_12_BIT: return hkDouble64(hkMath::invSqrtF32Approx12Bit(hkFloat32(self.m_real))); break;
		default:			return hkMath::sqrtInverse(self.m_real); break; // HK_ACC_FULL
	}
} };
template <hkMathAccuracyMode A>
struct unroll_sqrtInverse<A, HK_SQRT_SET_ZERO> { HK_FORCE_INLINE static hkSingleDouble64 apply(hkSimdDouble64Parameter self)
{
	if (self.m_real <= hkDouble64(0)) return hkDouble64(0);
	return unroll_sqrtInverse<A, HK_SQRT_IGNORE>::apply(self);
} };
} // namespace 

template <hkMathAccuracyMode A, hkMathNegSqrtMode S> 
HK_FORCE_INLINE const hkSimdDouble64 hkSimdDouble64::sqrtInverse() const
{
	return hkSimdDouble64::convert(hkSimdDouble64_AdvancedInterface::unroll_sqrtInverse<A,S>::apply(*this));
}

HK_FORCE_INLINE const hkSimdDouble64 hkSimdDouble64::sqrtInverse() const
{
	return hkSimdDouble64::convert(hkSimdDouble64_AdvancedInterface::unroll_sqrtInverse<HK_ACC_23_BIT,HK_SQRT_SET_ZERO>::apply(*this));
}




namespace hkSimdDouble64_AdvancedInterface
{
template <hkMathIoMode A>
struct unroll_load { HK_FORCE_INLINE static void apply(hkSingleDouble64& self, const hkFloat32* HK_RESTRICT p)
{
	HK_SIMDDOUBLE_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <hkMathIoMode A>
struct unroll_load_D { HK_FORCE_INLINE static void apply(hkSingleDouble64& self, const hkDouble64* HK_RESTRICT p)
{
	HK_SIMDDOUBLE_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <>
struct unroll_load<HK_IO_BYTE_ALIGNED> { HK_FORCE_INLINE static void apply(hkSingleDouble64& self, const hkFloat32* HK_RESTRICT p)
{
	self = hkDouble64(p[0]);
} };
template <>
struct unroll_load_D<HK_IO_BYTE_ALIGNED> { HK_FORCE_INLINE static void apply(hkSingleDouble64& self, const hkDouble64* HK_RESTRICT p)
{
	self = hkDouble64(p[0]);
} };
template <>
struct unroll_load<HK_IO_NATIVE_ALIGNED> { HK_FORCE_INLINE static void apply(hkSingleDouble64& self, const hkFloat32* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & (sizeof(hkFloat32)-1) ) == 0, "pointer must be aligned to native size of hkFloat32.");
	self = hkDouble64(p[0]);
} };
template <>
struct unroll_load_D<HK_IO_NATIVE_ALIGNED> { HK_FORCE_INLINE static void apply(hkSingleDouble64& self, const hkDouble64* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & (sizeof(hkDouble64)-1) ) == 0, "pointer must be aligned to native size of hkDouble64.");
	self = hkDouble64(p[0]);
} };
template <>
struct unroll_load<HK_IO_SIMD_ALIGNED> { HK_FORCE_INLINE static void apply(hkSingleDouble64& self, const hkFloat32* HK_RESTRICT p)
{
	unroll_load<HK_IO_NATIVE_ALIGNED>::apply(self,p);
} };
template <>
struct unroll_load_D<HK_IO_SIMD_ALIGNED> { HK_FORCE_INLINE static void apply(hkSingleDouble64& self, const hkDouble64* HK_RESTRICT p)
{
	unroll_load_D<HK_IO_NATIVE_ALIGNED>::apply(self,p);
} };
template <>
struct unroll_load<HK_IO_NOT_CACHED> { HK_FORCE_INLINE static void apply(hkSingleDouble64& self, const hkFloat32* HK_RESTRICT p)
{
	unroll_load<HK_IO_SIMD_ALIGNED>::apply(self,p);
} };
template <>
struct unroll_load_D<HK_IO_NOT_CACHED> { HK_FORCE_INLINE static void apply(hkSingleDouble64& self, const hkDouble64* HK_RESTRICT p)
{
	unroll_load_D<HK_IO_SIMD_ALIGNED>::apply(self,p);
} };
} // namespace 

template <int N, hkMathIoMode A>
HK_FORCE_INLINE void hkSimdDouble64::load(const hkFloat32 *p )
{
	HK_SIMDDOUBLE_DIMENSION_CHECK;
	hkSimdDouble64_AdvancedInterface::unroll_load<A>::apply(m_real, p);
}

template <int N, hkMathIoMode A>
HK_FORCE_INLINE void hkSimdDouble64::load(const hkDouble64 *p )
{
	HK_SIMDDOUBLE_DIMENSION_CHECK;
	hkSimdDouble64_AdvancedInterface::unroll_load_D<A>::apply(m_real, p);
}

template <int N>
HK_FORCE_INLINE void hkSimdDouble64::load(const hkFloat32 *p )
{
	HK_SIMDDOUBLE_DIMENSION_CHECK;
	hkSimdDouble64_AdvancedInterface::unroll_load<HK_IO_SIMD_ALIGNED>::apply(m_real, p);
}

template <int N>
HK_FORCE_INLINE void hkSimdDouble64::load(const hkDouble64 *p )
{
	HK_SIMDDOUBLE_DIMENSION_CHECK;
	hkSimdDouble64_AdvancedInterface::unroll_load_D<HK_IO_SIMD_ALIGNED>::apply(m_real, p);
}



namespace hkSimdDouble64_AdvancedInterface
{
template <hkMathIoMode A>
struct unroll_loadH { HK_FORCE_INLINE static void apply(hkSingleDouble64& self, const hkHalf* HK_RESTRICT p)
{
	HK_SIMDDOUBLE_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <>
struct unroll_loadH<HK_IO_BYTE_ALIGNED> { HK_FORCE_INLINE static void apply(hkSingleDouble64& self, const hkHalf* HK_RESTRICT p)
{
	self = p[0].getDouble();
} };
template <>
struct unroll_loadH<HK_IO_NATIVE_ALIGNED> { HK_FORCE_INLINE static void apply(hkSingleDouble64& self, const hkHalf* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & (sizeof(hkHalf)-1) ) == 0, "pointer must be aligned to native size of hkHalf.");
	self = p[0].getDouble();
} };
template <>
struct unroll_loadH<HK_IO_SIMD_ALIGNED> { HK_FORCE_INLINE static void apply(hkSingleDouble64& self, const hkHalf* HK_RESTRICT p)
{
	unroll_loadH<HK_IO_NATIVE_ALIGNED>::apply(self,p);
} };
template <>
struct unroll_loadH<HK_IO_NOT_CACHED> { HK_FORCE_INLINE static void apply(hkSingleDouble64& self, const hkHalf* HK_RESTRICT p)
{
	unroll_loadH<HK_IO_SIMD_ALIGNED>::apply(self,p);
} };
} // namespace 

template <int N, hkMathIoMode A>
HK_FORCE_INLINE void hkSimdDouble64::load(const hkHalf *p )
{
	HK_SIMDDOUBLE_DIMENSION_CHECK;
	hkSimdDouble64_AdvancedInterface::unroll_loadH<A>::apply(m_real, p);
}

template <int N>
HK_FORCE_INLINE void hkSimdDouble64::load(const hkHalf *p )
{
	HK_SIMDDOUBLE_DIMENSION_CHECK;
	hkSimdDouble64_AdvancedInterface::unroll_loadH<HK_IO_SIMD_ALIGNED>::apply(m_real, p);
}




namespace hkSimdDouble64_AdvancedInterface
{
template <hkMathIoMode A>
struct unroll_loadF16 { HK_FORCE_INLINE static void apply(hkSingleDouble64& self, const hkFloat16* HK_RESTRICT p)
{
	HK_SIMDDOUBLE_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <>
struct unroll_loadF16<HK_IO_BYTE_ALIGNED> { HK_FORCE_INLINE static void apply(hkSingleDouble64& self, const hkFloat16* HK_RESTRICT p)
{
	self = p[0].getReal();
} };
template <>
struct unroll_loadF16<HK_IO_NATIVE_ALIGNED> { HK_FORCE_INLINE static void apply(hkSingleDouble64& self, const hkFloat16* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & (sizeof(hkFloat16)-1) ) == 0, "pointer must be aligned to native size of hkFloat16.");
	self = p[0].getReal();
} };
template <>
struct unroll_loadF16<HK_IO_SIMD_ALIGNED> { HK_FORCE_INLINE static void apply(hkSingleDouble64& self, const hkFloat16* HK_RESTRICT p)
{
	unroll_loadF16<HK_IO_NATIVE_ALIGNED>::apply(self,p);
} };
template <>
struct unroll_loadF16<HK_IO_NOT_CACHED> { HK_FORCE_INLINE static void apply(hkSingleDouble64& self, const hkFloat16* HK_RESTRICT p)
{
	unroll_loadF16<HK_IO_SIMD_ALIGNED>::apply(self,p);
} };
} // namespace 

template <int N, hkMathIoMode A>
HK_FORCE_INLINE void hkSimdDouble64::load(const hkFloat16 *p )
{
	HK_SIMDDOUBLE_DIMENSION_CHECK;
	hkSimdDouble64_AdvancedInterface::unroll_loadF16<A>::apply(m_real, p);
}

template <int N>
HK_FORCE_INLINE void hkSimdDouble64::load(const hkFloat16 *p )
{
	HK_SIMDDOUBLE_DIMENSION_CHECK;
	hkSimdDouble64_AdvancedInterface::unroll_loadF16<HK_IO_SIMD_ALIGNED>::apply(m_real, p);
}



namespace hkSimdDouble64_AdvancedInterface
{
template <hkMathIoMode A>
struct unroll_store { HK_FORCE_INLINE static void apply(const hkSingleDouble64& self, hkFloat32* HK_RESTRICT p)
{
	HK_SIMDDOUBLE_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <hkMathIoMode A>
struct unroll_store_D { HK_FORCE_INLINE static void apply(const hkSingleDouble64& self, hkDouble64* HK_RESTRICT p)
{
	HK_SIMDDOUBLE_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <>
struct unroll_store<HK_IO_BYTE_ALIGNED> { HK_FORCE_INLINE static void apply(const hkSingleDouble64& self, hkFloat32* HK_RESTRICT p)
{
	p[0] = hkFloat32(self);
} };
template <>
struct unroll_store_D<HK_IO_BYTE_ALIGNED> { HK_FORCE_INLINE static void apply(const hkSingleDouble64& self, hkDouble64* HK_RESTRICT p)
{
	p[0] = hkDouble64(self);
} };
template <>
struct unroll_store<HK_IO_NATIVE_ALIGNED> { HK_FORCE_INLINE static void apply(const hkSingleDouble64& self, hkFloat32* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & (sizeof(hkFloat32)-1) ) == 0, "pointer must be aligned to native size of hkFloat32.");
	p[0] = hkFloat32(self);
} };
template <>
struct unroll_store_D<HK_IO_NATIVE_ALIGNED> { HK_FORCE_INLINE static void apply(const hkSingleDouble64& self, hkDouble64* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & (sizeof(hkDouble64)-1) ) == 0, "pointer must be aligned to native size of hkDouble64.");
	p[0] = hkDouble64(self);
} };
template <>
struct unroll_store<HK_IO_SIMD_ALIGNED> { HK_FORCE_INLINE static void apply(const hkSingleDouble64& self, hkFloat32* HK_RESTRICT p)
{
	unroll_store<HK_IO_NATIVE_ALIGNED>::apply(self,p);
} };
template <>
struct unroll_store_D<HK_IO_SIMD_ALIGNED> { HK_FORCE_INLINE static void apply(const hkSingleDouble64& self, hkDouble64* HK_RESTRICT p)
{
	unroll_store_D<HK_IO_NATIVE_ALIGNED>::apply(self,p);
} };
template <>
struct unroll_store<HK_IO_NOT_CACHED> { HK_FORCE_INLINE static void apply(const hkSingleDouble64& self, hkFloat32* HK_RESTRICT p)
{
	unroll_store<HK_IO_SIMD_ALIGNED>::apply(self,p);
} };
template <>
struct unroll_store_D<HK_IO_NOT_CACHED> { HK_FORCE_INLINE static void apply(const hkSingleDouble64& self, hkDouble64* HK_RESTRICT p)
{
	unroll_store_D<HK_IO_SIMD_ALIGNED>::apply(self,p);
} };
} // namespace 

template <int N, hkMathIoMode A, hkMathRoundingMode R>
HK_FORCE_INLINE void hkSimdDouble64::store(  hkFloat32 *p ) const
{
	HK_SIMDDOUBLE_DIMENSION_CHECK;
	hkSimdDouble64_AdvancedInterface::unroll_store<A>::apply(m_real, p);
}

template <int N, hkMathIoMode A, hkMathRoundingMode R>
HK_FORCE_INLINE void hkSimdDouble64::store(  hkDouble64 *p ) const
{
	HK_SIMDDOUBLE_DIMENSION_CHECK;
	hkSimdDouble64_AdvancedInterface::unroll_store_D<A>::apply(m_real, p);
}

template <int N, hkMathIoMode A>
HK_FORCE_INLINE void hkSimdDouble64::store(  hkFloat32 *p ) const
{
	HK_SIMDDOUBLE_DIMENSION_CHECK;
	hkSimdDouble64_AdvancedInterface::unroll_store<A>::apply(m_real, p);
}

template <int N, hkMathIoMode A>
HK_FORCE_INLINE void hkSimdDouble64::store(  hkDouble64 *p ) const
{
	HK_SIMDDOUBLE_DIMENSION_CHECK;
	hkSimdDouble64_AdvancedInterface::unroll_store_D<A>::apply(m_real, p);
}

template <int N>
HK_FORCE_INLINE void hkSimdDouble64::store(  hkFloat32 *p ) const
{
	HK_SIMDDOUBLE_DIMENSION_CHECK;
	hkSimdDouble64_AdvancedInterface::unroll_store<HK_IO_SIMD_ALIGNED>::apply(m_real, p);
}

template <int N>
HK_FORCE_INLINE void hkSimdDouble64::store(  hkDouble64 *p ) const
{
	HK_SIMDDOUBLE_DIMENSION_CHECK;
	hkSimdDouble64_AdvancedInterface::unroll_store_D<HK_IO_SIMD_ALIGNED>::apply(m_real, p);
}




namespace hkSimdDouble64_AdvancedInterface
{
template <hkMathIoMode A, hkMathRoundingMode R>
struct unroll_storeH { HK_FORCE_INLINE static void apply(const hkSingleDouble64& self, hkHalf* HK_RESTRICT p)
{
	HK_SIMDDOUBLE_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <hkMathRoundingMode R>
struct unroll_storeH<HK_IO_BYTE_ALIGNED,R> { HK_FORCE_INLINE static void apply(const hkSingleDouble64& self, hkHalf* HK_RESTRICT p)
{
	p[0].setReal<(R == HK_ROUND_NEAREST)>(self);
} };
template <hkMathRoundingMode R>
struct unroll_storeH<HK_IO_NATIVE_ALIGNED,R> { HK_FORCE_INLINE static void apply(const hkSingleDouble64& self, hkHalf* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & (sizeof(hkHalf)-1) ) == 0, "pointer must be aligned to native size of hkHalf.");
	p[0].setReal<(R == HK_ROUND_NEAREST)>(self);
} };
template <hkMathRoundingMode R>
struct unroll_storeH<HK_IO_SIMD_ALIGNED,R> { HK_FORCE_INLINE static void apply(const hkSingleDouble64& self, hkHalf* HK_RESTRICT p)
{
	unroll_storeH<HK_IO_NATIVE_ALIGNED,R>::apply(self,p);
} };
template <hkMathRoundingMode R>
struct unroll_storeH<HK_IO_NOT_CACHED,R> { HK_FORCE_INLINE static void apply(const hkSingleDouble64& self, hkHalf* HK_RESTRICT p)
{
	unroll_storeH<HK_IO_SIMD_ALIGNED,R>::apply(self,p);
} };
} // namespace 

template <int N, hkMathIoMode A, hkMathRoundingMode R>
HK_FORCE_INLINE void hkSimdDouble64::store(  hkHalf *p ) const
{
	HK_SIMDDOUBLE_DIMENSION_CHECK;
	hkSimdDouble64_AdvancedInterface::unroll_storeH<A,R>::apply(m_real, p);
}

template <int N>
HK_FORCE_INLINE void hkSimdDouble64::store(  hkHalf *p ) const
{
	HK_SIMDDOUBLE_DIMENSION_CHECK;
	hkSimdDouble64_AdvancedInterface::unroll_storeH<HK_IO_SIMD_ALIGNED,HK_ROUND_DEFAULT>::apply(m_real, p);
}


namespace hkSimdDouble64_AdvancedInterface
{
template <hkMathIoMode A, hkMathRoundingMode R>
struct unroll_storeF16 { HK_FORCE_INLINE static void apply(const hkSingleDouble64& self, hkFloat16* HK_RESTRICT p)
{
	HK_SIMDDOUBLE_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <hkMathRoundingMode R>
struct unroll_storeF16<HK_IO_BYTE_ALIGNED,R> { HK_FORCE_INLINE static void apply(const hkSingleDouble64& self, hkFloat16* HK_RESTRICT p)
{
	p[0].setReal<(R == HK_ROUND_NEAREST)>(self);
} };
template <hkMathRoundingMode R>
struct unroll_storeF16<HK_IO_NATIVE_ALIGNED,R> { HK_FORCE_INLINE static void apply(const hkSingleDouble64& self, hkFloat16* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & (sizeof(hkFloat16)-1) ) == 0, "pointer must be aligned to native size of hkFloat16.");
	p[0].setReal<(R == HK_ROUND_NEAREST)>(self);
} };
template <hkMathRoundingMode R>
struct unroll_storeF16<HK_IO_SIMD_ALIGNED,R> { HK_FORCE_INLINE static void apply(const hkSingleDouble64& self, hkFloat16* HK_RESTRICT p)
{
	unroll_storeF16<HK_IO_NATIVE_ALIGNED,R>::apply(self,p);
} };
template <hkMathRoundingMode R>
struct unroll_storeF16<HK_IO_NOT_CACHED,R> { HK_FORCE_INLINE static void apply(const hkSingleDouble64& self, hkFloat16* HK_RESTRICT p)
{
	unroll_storeF16<HK_IO_SIMD_ALIGNED,R>::apply(self,p);
} };
} // namespace 

template <int N, hkMathIoMode A, hkMathRoundingMode R>
HK_FORCE_INLINE void hkSimdDouble64::store(  hkFloat16 *p ) const
{
	HK_SIMDDOUBLE_DIMENSION_CHECK;
	hkSimdDouble64_AdvancedInterface::unroll_storeF16<A,R>::apply(m_real, p);
}

template <int N>
HK_FORCE_INLINE void hkSimdDouble64::store(  hkFloat16 *p ) const
{
	HK_SIMDDOUBLE_DIMENSION_CHECK;
	hkSimdDouble64_AdvancedInterface::unroll_storeF16<HK_IO_SIMD_ALIGNED,HK_ROUND_DEFAULT>::apply(m_real, p);
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
