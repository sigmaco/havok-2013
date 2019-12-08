/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#ifndef __HAVOK_PARSER__

//
//	Sets this = i

template <int N>
inline void hkSimdInt<N>::setFromInt32(int i)
{
	m_lo.setFromInt32(i);
	m_hi.m_hi = m_hi.m_lo = m_lo.m_hi;
}

//
//	Sets this = 0

template <int N>
inline void hkSimdInt<N>::setZero()
{
	m_lo.setZero();	m_hi.setZero();
}

//
//	Sets this = ~a

template <int N>
inline void hkSimdInt<N>::setNot(const hkSimdInt<N>& a)
{
	m_hi.setNot(a.m_hi);	m_lo.setNot(a.m_lo);
}

//
//	Sets this = a & b

template <int N>
inline void hkSimdInt<N>::setAnd(const hkSimdInt<N>& a, const hkSimdInt<N>& b)
{
	m_lo.setAnd(a.m_lo, b.m_lo);	m_hi.setAnd(a.m_hi, b.m_hi);
}

//
//	Sets this = a | b

template <int N>
inline void hkSimdInt<N>::setOr(const hkSimdInt<N>& a, const hkSimdInt<N>& b)
{
	m_lo.setOr(a.m_lo, b.m_lo);	m_hi.setOr(a.m_hi, b.m_hi);
}

//
//	Returns this == 0

template <int N>
inline const hkVector4fComparison hkSimdInt<N>::equalZero() const
{
	HalfInt hilo;	hilo.setOr(m_hi, m_lo);
	return hilo.equalZero();
}

//
//	Returns this < 0

template <int N>
inline const hkVector4fComparison hkSimdInt<N>::lessZero() const
{
	// The sign bit is in the high part
	return m_hi.lessZero();
}

//
//	Sets this = this + 1

template <int N>
inline void hkSimdInt<N>::increment()
{
	// The result is (m_lo == -1) ? [m_hi + 1, m_lo + 1] : [m_hi, m_lo + 1]
	HalfInt lo		= m_lo;	lo.increment();	// m_lo + 1
	HalfInt hi		= m_hi;	hi.increment();	// m_hi + 1
	HalfInt one;	one.setFromInt32(-1);	// -1

	const hkVector4fComparison cmpFF = m_lo.equal(one);
	m_hi.setSelect(cmpFF, hi, m_hi);	// (m_lo == -1) ? m_hi + 1 : m_hi
	m_lo = lo;							// m_lo + 1
}

//
//	Sets this -v

template <int N>
inline void hkSimdInt<N>::setNeg(const hkSimdInt<N>& v)
{
	setNot(v);		// Negate first
	increment();	// Add 1
}

//
//	Set this = abs(v)

template <int N>
inline void hkSimdInt<N>::setAbs(const hkSimdInt<N>& v)
{
	hkSimdInt<N> vNeg;
	vNeg.setNeg(v);
	setSelect(v.lessZero(), vNeg, v);
}

//
//	Sets this = cmp ? vTrue : vFalse

template <int N>
inline void hkSimdInt<N>::setSelect(hkVector4fComparisonParameter cmp, const hkSimdInt<N>& vTrue, const hkSimdInt<N>& vFalse)
{
	m_hi.setSelect(cmp, vTrue.m_hi, vFalse.m_hi);
	m_lo.setSelect(cmp, vTrue.m_lo, vFalse.m_lo);
}

//
//	Returns this == v

template <int N>
inline const hkVector4fComparison hkSimdInt<N>::equal(const hkSimdInt<N>& v)
{
	hkVector4fComparison cmp;	cmp.setAnd(m_lo.equal(v.m_lo), m_hi.equal(v.m_hi));
	return cmp;
}

//
//	Returns this > 0

template <int N>
inline const hkVector4fComparison hkSimdInt<N>::greaterZero() const
{
	hkVector4fComparison cmp;
	cmp.setNot(lessZero());
	cmp.setAndNot(cmp, equalZero());
	return cmp;
}

//
//	Sets this = sign * v

template <int N>
inline void hkSimdInt<N>::setFlipSign(const hkSimdInt<N>& a, hkVector4fComparisonParameter sign)
{
	hkSimdInt<N> vNeg;	vNeg.setNeg(a);
	setSelect(sign, vNeg, a);
}

//
//	Sets this = a + b

template <int N>
inline void hkSimdInt<N>::setAdd(const hkSimdInt<N>& origA, const hkSimdInt<N>& origB)
{
	// a	= [hiA, loA]
	// b	= [hiB, loB]
	// a+b	= [lo(hiA + hiB) + hi(loA + loB), lo(loA + loB)]
	const hkSimdInt<N> a	= origA;
	const hkSimdInt<N> b	= origB;
	hkSimdInt<N> loA_loB;	loA_loB.setUnsignedAdd(a.m_lo, b.m_lo);			// loA + loB
	hkSimdInt<N> hiA_hiB;	hiA_hiB.setUnsignedAdd(a.m_hi, b.m_hi);			// hiA + hiB
	hkSimdInt<N> hi;		hi.setUnsignedAdd(hiA_hiB.m_lo, loA_loB.m_hi);	// lo(hiA + hiB) + hi(loA + loB)

	// Write output
	m_lo = loA_loB.m_lo;
	m_hi = hi.m_lo;
}

//
//	Sets this = a - b

template <int N>
inline void hkSimdInt<N>::setSub(const hkSimdInt<N>& a, const hkSimdInt<N>& b)
{
	hkSimdInt<N> negB;	negB.setNeg(b);
	setAdd(a, negB);
}

//
//	Sets this += ab

template <int N>
inline void hkSimdInt<N>::addMul(HalfIntParameter a, HalfIntParameter b)
{
	hkSimdInt<N> tmp;	tmp.setMul(a, b);
	setAdd(*this, tmp);
}

//
//	Sets this -= ab

template <int N>
inline void hkSimdInt<N>::subMul(HalfIntParameter a, HalfIntParameter b)
{
	hkSimdInt<N> tmp;	tmp.setMul(a, b);
	setSub(*this, tmp);
}

//
//	Returns the number of leading zeros

template <int N>
inline int hkSimdInt<N>::countLeadingZeros() const
{
	const int nz1 = m_hi.countLeadingZeros();
	const int nz0 = m_lo.countLeadingZeros();
	return (nz1 < (N >> 1)) ? nz1 : ((N >> 1) + nz0);
}

//
//	Sets this = a << I

template <int N>
template <int I>
inline void hkSimdInt<N>::setShiftLeft(const hkSimdInt<N>& origV)
{
	hkSimdInt<N> v = origV;
	const int shl = I > (N >> 1) ? (I - (N >> 1)) : I;
	if ( I > shl )
	{
		v.m_hi = v.m_lo;
		v.m_lo.setZero();
	}

	HalfInt hi;	hi.template setShiftLeft<shl>(v.m_hi);
	HalfInt lo;	lo.template setShiftRight<(N >> 1) - shl>(v.m_lo);
	m_hi.setOr(hi, lo);
	m_lo.template setShiftLeft<shl>(v.m_lo);
}

template <int N>
inline	void hkSimdInt<N>::setShiftLeft(const hkSimdInt<N>& origV, int I)
{
	hkSimdInt<N> v = origV;
	const int shl = I > (N >> 1) ? (I - (N >> 1)) : I;
	if ( I > shl )
	{
		v.m_hi = v.m_lo;
		v.m_lo.setZero();
	}

	HalfInt hi;	hi.setShiftLeft(v.m_hi, shl);
	HalfInt lo;	lo.setShiftRight(v.m_lo, (N >> 1) - shl);
	m_hi.setOr(hi, lo);
	m_lo.setShiftLeft(v.m_lo, shl);
}

//
//	Sets this = a >> I

template <int N>
template <int I>
inline void hkSimdInt<N>::setShiftRight(const hkSimdInt<N>& origV)
{
	const int shr = (I > (N >> 1)) ? (I - (N >> 1)) : I;
	hkVector4fComparison cmp;
	cmp.set((hkVector4ComparisonMask::Mask)((I > shr) ? hkVector4ComparisonMask::MASK_XYZW : hkVector4ComparisonMask::MASK_NONE));

	hkSimdInt<N> v;	v.m_hi.setZero();
	v.m_lo.setSelect(cmp, origV.m_hi, origV.m_lo);
	v.m_hi.setSelect(cmp, v.m_hi, origV.m_hi);

	HalfInt hi;	hi.setShiftRight(v.m_lo, shr);
	HalfInt lo;	lo.setShiftLeft(v.m_hi, 128 - shr);
	m_lo.setOr(hi, lo);
	m_hi.setShiftRight(v.m_hi, shr);
}

template <int N>
inline void hkSimdInt<N>::setShiftRight(const hkSimdInt<N>& origV, int I)
{
	const int shr = (I > (N >> 1)) ? (I - (N >> 1)) : I;
	hkVector4fComparison cmp;
	cmp.set((hkVector4ComparisonMask::Mask)((I > shr) ? hkVector4ComparisonMask::MASK_XYZW : hkVector4ComparisonMask::MASK_NONE));

	hkSimdInt<N> v;	v.m_hi.setZero();
	v.m_lo.setSelect(cmp, origV.m_hi, origV.m_lo);
	v.m_hi.setSelect(cmp, v.m_hi, origV.m_hi);

	HalfInt hi;	hi.setShiftRight(v.m_lo, shr);
	HalfInt lo;	lo.setShiftLeft(v.m_hi, (N >> 1) - shr);
	m_lo.setOr(hi, lo);
	m_hi.setShiftRight(v.m_hi, shr);
}

//
//	Sets this = a * b

template <>
inline void hkSimdInt<256>::setUnsignedMul(HalfIntParameter origX, HalfIntParameter origY)
{
	const HalfInt x = origX;	// [a1, a0]
	const HalfInt y = origY;	// [b1, b0]

	// Compute 64-bit products
	HalfInt a0b0, a1b0, a0b1, a1b1;
	{
		hkInt64Vector4 vTempX;		vTempX.loadXy(x);	vTempX.loadZw(x);						// [a1, a0, a1, a0]
		hkInt64Vector4 vTempY;		vTempY.loadXy(y);	vTempY.loadZw(y);						// [b1, b0, b1, b0]
									vTempY.setPermutation<hkVectorPermutation::XYWZ>(vTempY);	// [b1, b0, b0, b1]						
		hkInt64Vector4 a0bx;		a0bx.setUnsignedMul_128<2>(vTempX, vTempY);					// [a0b0, a0b1]
		a0bx.storeXy(a0b0);
		a0bx.storeZw(a0b1);

									vTempX.setPermutation<hkVectorPermutation::YXWZ>(vTempX);	// [a0, a1, a0, a1]
		hkInt64Vector4 a1bx;		a1bx.setUnsignedMul_128<2>(vTempX, vTempY);					// [a1b0, a1b1]
		a1bx.storeXy(a1b0);
		a1bx.storeZw(a1b1);
	}

	// Accumulate 64-bit products
	{
		HalfInt hi_a1b0;	hi_a1b0.setShiftRight<64>(a1b0);		// [0, hi(a1b0)]
		HalfInt hi_a0b1;	hi_a0b1.setShiftRight<64>(a0b1);		// [0, hi(a0b1)]
		HalfInt r2;			r2.setAdd(hi_a1b0, hi_a0b1);			// hi(a1b0) + hi(a0b1)
							r2.setAdd(a1b1, r2);					// a1b1 + hi(a1b0) + hi(a0b1)

		HalfInt lo_a0b1;	lo_a0b1.setShiftLeft<64>(a0b1);			// [lo(a0b1), 0]
							lo_a0b1.setShiftRight<64>(lo_a0b1);		// [0, lo(a0b1)]
		HalfInt lo_a1b0;	lo_a1b0.setShiftLeft<64>(a1b0);			// [lo(a1b0), 0]
							lo_a1b0.setShiftRight<64>(lo_a1b0);		// [0, lo(a1b0)]
		HalfInt r1;			r1.setAdd(lo_a0b1, lo_a1b0);			// lo(a0b1) + lo(a1b0)

		HalfInt hi_a0b0;	hi_a0b0.setShiftRight<64>(a0b0);		// [0, hi(a0b0)]
							r1.setAdd(r1, hi_a0b0);					// hi(a0b0) + lo(a0b1) + lo(a1b0)

		HalfInt hi_r1;		hi_r1.setShiftRight<64>(r1);			// hi(hi(a0b0) + lo(a0b1) + lo(a1b0))
							r2.setAdd(r2, hi_r1);					// a1b1 + hi(a1b0) + hi(a0b1) + hi(hi(a0b0) + lo(a0b1) + lo(a1b0))

		HalfInt r0;			r0.setShiftLeft<64>(a0b0);				// [lo(a0b0), 0]
							r0.setShiftRight<64>(r0);				// [0, lo(a0b0)]
		HalfInt lo_r1;		lo_r1.setShiftLeft<64>(r1);				// [lo(r1), 0]
							r0.setOr(r0, lo_r1);					// [lo(r1), lo(a0b0)]

		m_hi = r2;
		m_lo = r0;
	}
}

//
//	Sets this = a / b. Both a and b are assumed unsigned!

inline void hkSimdInt<128>::setUnsignedDiv(const hkSimdInt<128>& origA, const hkSimdInt<128>& origB)
{
	HK_ASSERT(0x72f8c17b, !origB.equalZero().anyIsSet());

	// Compute log(b), i.e. y = such that (1 << y) <= b < (1 << (y + 1)
	const int logB			= 127 - origB.countLeadingZeros();
	hkSimdInt<128> maskA;	maskA.setFromInt32(-1);
							maskA.setShiftLeft(maskA, logB + 1);
	hkSimdInt<128> aMask;	aMask.setAnd(origA, maskA);
	hkSimdInt<128> aDivB;	aDivB.setZero();
	hkSimdInt<128> a		= origA;

	while ( !aMask.equalZero().anyIsSet() )
	{
		// a >= b, so we can compute dx = a / (1 << logB) = (a >> logB)
		hkSimdInt<128> dx;		dx.setShiftRight(a, logB + 1);
								aDivB.setAdd(aDivB, dx);

		// Subtract dx * b from a
		hkSimdInt<256> bdx;
		bdx.setUnsignedMul(origB, dx);	// b * dx
		a.setSub(a, bdx.m_lo);			// a -= b * dx
		
 		// Update a & maskA
		aMask.setAnd(a, maskA);
	}

	// Last iterations, linear convergence
	{
		hkSimdInt<128> negB;	negB.setNeg(origB);
								a.setAdd(a, negB);
		while ( !a.lessZero().anyIsSet() )
		{
			aDivB.increment();
			a.setAdd(a, negB);
		}
	}

	// Store
	*this = aDivB;
}

//
//    Sets this = a / b

inline int HK_CALL hkSimdInt<128>::computeDiv32(const hkSimdInt<128>& origA, const hkSimdInt<128>& origB)
{
	// Make values absolute
	hkSimdInt<128> a;    a.setAbs(origA);
	hkSimdInt<128> b;    b.setAbs(origB);
	HK_ASSERT(0x65c143c8, !b.equalZero().anyIsSet());    // Check division by zero!

	// Compute log(b), i.e. y = such that (1 << y) <= b < (1 << (y + 1)
	const int logB			= (128 - 1) - b.countLeadingZeros();
	hkSimdInt<128> maskA;	maskA.setFromInt32(-1);
							maskA.setShiftLeft(maskA, logB + 1);
	hkSimdInt<128> aMask;	aMask.setAnd(a, maskA);
	hkSimdInt<128> aDivB;	aDivB.setZero();

	while ( !aMask.equalZero().anyIsSet() )
	{
		// a >= b, so we can compute dx = a / (1 << logB) = (a >> logB)
		hkSimdInt<128> dx;	dx.setShiftRight(a, logB + 1);
							aDivB.setAdd(aDivB, dx);

		// Subtract dx * b from a
		hkSimdInt<256> bdx;
		bdx.setUnsignedMul(b, dx);		// b * dx
		a.setSub(a, bdx.m_lo);			// a -= b * dx

		// Update a & maskA
		aMask.setAnd(a, maskA);
	}

	// Last iterations, linear convergence
	{
		hkSimdInt<128> negB;	negB.setNeg(b);
								a.setAdd(a, negB);
		while ( !a.lessZero().anyIsSet() )
		{
			aDivB.increment();
			a.setAdd(a, negB);
		}
	}

	// Set proper signs!
	{
		const hkVector4fComparison negX	= origA.lessZero();							// (x < 0)
		const hkVector4fComparison negY	= origB.lessZero();							// (y < 0)
		hkVector4fComparison negZeroX;	negZeroX.setOr(negX, origA.equalZero());	// (x <= 0)
		hkVector4fComparison negZeroY;	negZeroY.setOr(negY, origB.equalZero());	// (y <= 0)
		hkVector4fComparison negX_posY;	negX_posY.setAndNot(negX, negZeroY);		// (x < 0) && (y > 0)
		hkVector4fComparison posX_negY;	posX_negY.setAndNot(negY, negZeroX);		// (y < 0) && (x > 0)
		hkVector4fComparison neg;		neg.setOr(negX_posY, posX_negY);			// sign(xy)

		// Set proper signs
		const int sign = 1 - ((neg.getMask() & 1) << 1);
		HK_ASSERT(0x40f075ee, (neg.anyIsSet() && (sign == -1)) || (!neg.anyIsSet() && (sign == 1)));
		return sign * aDivB.getWord<0>();
	}
}

template <>
inline void hkSimdInt<256>::setUnsignedMul(HalfIntParameter origX, hkInt64 origY)
{
	const HalfInt x = origX;	// [a1, a0]
	const hkInt64 y = origY;	// [0, b0]

	// Compute 64-bit products
	HalfInt a0b0, a1b0;
	{
		hkInt64Vector4 vTempX;		vTempX.loadXy(x);	vTempX.loadZw(x);						// [a1, a0, a1, a0]
		hkInt64Vector4 vTempY;		vTempY.setAll(y);											// [b0, b0, b0, b0]
									vTempX.setPermutation<hkVectorPermutation::XYWZ>(vTempX);	// [a1, a0, a0, a1]						
		hkInt64Vector4 axb0;		axb0.setUnsignedMul_128<2>(vTempX, vTempY);					// [a0b0, a1b0]
		axb0.storeXy(a0b0);
		axb0.storeZw(a1b0);
	}

	// Accumulate 64-bit products
	{
		HalfInt r2;			r2.setShiftRight<64>(a1b0);				// [0, hi(a1b0)]
		HalfInt r1;			r1.setShiftLeft<64>(a1b0);				// [lo(a1b0), 0]
							r1.setShiftRight<64>(r1);				// [0, lo(a1b0)]

		HalfInt hi_a0b0;	hi_a0b0.setShiftRight<64>(a0b0);		// [0, hi(a0b0)]
							r1.setAdd(r1, hi_a0b0);					// hi(a0b0) + lo(a0b1) + lo(a1b0)

		HalfInt hi_r1;		hi_r1.setShiftRight<64>(r1);			// hi(hi(a0b0) + lo(a0b1) + lo(a1b0))
							r2.setAdd(r2, hi_r1);					// a1b1 + hi(a1b0) + hi(a0b1) + hi(hi(a0b0) + lo(a0b1) + lo(a1b0))

		HalfInt r0;			r0.setShiftLeft<64>(a0b0);				// [lo(a0b0), 0]
							r0.setShiftRight<64>(r0);				// [0, lo(a0b0)]
		HalfInt lo_r1;		lo_r1.setShiftLeft<64>(r1);				// [lo(r1), 0]
							r0.setOr(r0, lo_r1);					// [lo(r1), lo(a0b0)]

		m_hi = r2;
		m_lo = r0;
	}
}

//
//	Sets this = a * b

template <int N>
inline void hkSimdInt<N>::setUnsignedMul(HalfIntParameter origX, HalfIntParameter origY)
{
	const HalfInt x = origX;	// [a1, a0]
	const HalfInt y = origY;	// [b1, b0]

	// Compute 64-bit products
	HalfInt a0b0;	a0b0.setUnsignedMul(x.m_lo, y.m_lo);	// a0b0
	HalfInt a1b0;	a1b0.setUnsignedMul(x.m_hi, y.m_lo);	// a1b0
	HalfInt a0b1;	a0b1.setUnsignedMul(x.m_lo, y.m_hi);	// a0b1
	HalfInt a1b1;	a1b1.setUnsignedMul(x.m_hi, y.m_hi);	// a1b1

	// Accumulate 64-bit products
	{
		HalfInt hi_a1b0;	hi_a1b0.template setShiftRight	<(N >> 2)>	(a1b0);	// [0, hi(a1b0)]
		HalfInt hi_a0b1;	hi_a0b1.template setShiftRight	<(N >> 2)>	(a0b1);	// [0, hi(a0b1)]
		HalfInt r2;			r2.setAdd(hi_a1b0, hi_a0b1);						// hi(a1b0) + hi(a0b1)
							r2.setAdd(a1b1, r2);								// a1b1 + hi(a1b0) + hi(a0b1)

		HalfInt lo_a0b1;	lo_a0b1.template setShiftLeft	<(N >> 2)>	(a0b1);		// [lo(a0b1), 0]
							lo_a0b1.template setShiftRight	<(N >> 2)>	(lo_a0b1);	// [0, lo(a0b1)]
		HalfInt lo_a1b0;	lo_a1b0.template setShiftLeft	<(N >> 2)>	(a1b0);		// [lo(a1b0), 0]
							lo_a1b0.template setShiftRight	<(N >> 2)>	(lo_a1b0);	// [0, lo(a1b0)]
		HalfInt r1;			r1.setAdd(lo_a0b1, lo_a1b0);							// lo(a0b1) + lo(a1b0)

		HalfInt hi_a0b0;	hi_a0b0.template setShiftRight	<(N >> 2)>	(a0b0);		// [0, hi(a0b0)]
							r1.setAdd(r1, hi_a0b0);									// hi(a0b0) + lo(a0b1) + lo(a1b0)

		HalfInt hi_r1;		hi_r1.template setShiftRight	<(N >> 2)>	(r1);		// hi(hi(a0b0) + lo(a0b1) + lo(a1b0))
							r2.setAdd(r2, hi_r1);									// a1b1 + hi(a1b0) + hi(a0b1) + hi(hi(a0b0) + lo(a0b1) + lo(a1b0))

		HalfInt r0;			r0.template setShiftLeft		<(N >> 2)>	(a0b0);		// [lo(a0b0), 0]
							r0.template setShiftRight		<(N >> 2)>	(r0);		// [0, lo(a0b0)]
		HalfInt lo_r1;		lo_r1.template setShiftLeft		<(N >> 2)>	(r1);		// [lo(r1), 0]
							r0.setOr(r0, lo_r1);									// [lo(r1), lo(a0b0)]

		m_hi = r2;
		m_lo = r0;
	}
}

//
//	Sets this = a * b

template <int N>
inline void hkSimdInt<N>::setMul(HalfIntParameter origX, HalfIntParameter origY)
{
	// Make both terms positive
	HalfInt x;		x.setAbs(origX);	// [a1, a0]
	HalfInt y;		y.setAbs(origY);	// [b1, b0]

	hkSimdInt<N> prodXY;
	prodXY.setUnsignedMul(x, y);

	// Set proper signs
	{
		const hkVector4fComparison negX	= origX.lessZero();							// (x < 0)
		const hkVector4fComparison negY	= origY.lessZero();							// (y < 0)
		hkVector4fComparison negZeroX;	negZeroX.setOr(negX, origX.equalZero());	// (x <= 0)
		hkVector4fComparison negZeroY;	negZeroY.setOr(negY, origY.equalZero());	// (y <= 0)
		hkVector4fComparison negX_posY;	negX_posY.setAndNot(negX, negZeroY);		// (x < 0) && (y > 0)
		hkVector4fComparison posX_negY;	posX_negY.setAndNot(negY, negZeroX);		// (y < 0) && (x > 0)
		hkVector4fComparison neg;		neg.setOr(negX_posY, posX_negY);			// sign(xy)

		// Set proper signs
		setFlipSign(prodXY, neg);
	}
}

template <int N>
inline void hkSimdInt<N>::setMul(HalfIntParameter origX, hkInt64 origY)
{
	// Make both terms positive
	HalfInt x;		x.setAbs(origX);		// [a1, a0]
	hkInt64 y		= hkMath::abs(origY);	// [0, b0]

	hkSimdInt<N> prodXY;
	prodXY.setUnsignedMul(x, y);

	// Set proper signs
	{
		const hkVector4fComparison negX	= origX.lessZero();																		// (x < 0)
		hkVector4fComparison negY;		negY.set((hkVector4ComparisonMask::Mask)(hkVector4ComparisonMask::MASK_XYZW & (origY >> 63L)));	// (y < 0)
		hkVector4fComparison zeroY;		zeroY.set(origY ? hkVector4ComparisonMask::MASK_NONE : hkVector4ComparisonMask::MASK_XYZW);		// (y == 0)
		hkVector4fComparison negZeroX;	negZeroX.setOr(negX, origX.equalZero());	// (x <= 0)
		hkVector4fComparison negZeroY;	negZeroY.setOr(negY, zeroY);				// (y <= 0)
		hkVector4fComparison negX_posY;	negX_posY.setAndNot(negX, negZeroY);		// (x < 0) && (y > 0)
		hkVector4fComparison posX_negY;	posX_negY.setAndNot(negY, negZeroX);		// (y < 0) && (x > 0)
		hkVector4fComparison neg;		neg.setOr(negX_posY, posX_negY);			// sign(xy)

		// Set proper signs
		setFlipSign(prodXY, neg);
	}
}

//
//	Sets this = a * b

template <int N>
void hkSimdInt<N>::setUnsignedMul(const hkSimdInt<N>& x, const hkSimdInt<N>& y)
{
	// Compute 128-bit products
	hkSimdInt<N> a0b0;	a0b0.setUnsignedMul(x.m_lo, y.m_lo);
	hkSimdInt<N> a1b0;	a1b0.setUnsignedMul(x.m_hi, y.m_lo);
	hkSimdInt<N> a0b1;	a0b1.setUnsignedMul(x.m_lo, y.m_hi);

	// Accumulate 128-bit products
	{
		hkSimdInt<N> lo_a0b1;	lo_a0b1.setShiftLeft<(N >> 1)>(a0b1);		// [lo(a0b1), 0]
								lo_a0b1.setShiftRight<(N >> 1)>(lo_a0b1);	// [0, lo(a0b1)]
		hkSimdInt<N> lo_a1b0;	lo_a1b0.setShiftLeft<(N >> 1)>(a1b0);		// [lo(a1b0), 0]
								lo_a1b0.setShiftRight<(N >> 1)>(lo_a1b0);	// [0, lo(a1b0)]
		hkSimdInt<N> r1;		r1.setAdd(lo_a0b1, lo_a1b0);				// lo(a0b1) + lo(a1b0)

		hkSimdInt<N> hi_a0b0;	hi_a0b0.setShiftRight<(N >> 1)>(a0b0);		// [0, hi(a0b0)]
								r1.setAdd(r1, hi_a0b0);						// hi(a0b0) + lo(a0b1) + lo(a1b0)

		hkSimdInt<N> r0;		r0.setShiftLeft<(N >> 1)>(a0b0);			// [lo(a0b0), 0]
								r0.setShiftRight<(N >> 1)>(r0);				// [0, lo(a0b0)]
		hkSimdInt<N> lo_r1;		lo_r1.setShiftLeft<(N >> 1)>(r1);			// [lo(r1), 0]
								r0.setOr(r0, lo_r1);						// [lo(r1), lo(a0b0)]
		*this = r0;
	}
}

//
//	Returns a / b and a % b

template <int N>
inline void HK_CALL hkSimdInt<N>::computeUnsignedDivMod(const hkSimdInt<N>& origA, const hkSimdInt<N>& origB, hkSimdInt<N>& divOut, hkSimdInt<N>& modOut)
{
	HK_ASSERT(0x65c143c8, !origB.equalZero().anyIsSet());    // Check division by zero!

	// Compute log(b), i.e. y = such that (1 << y) <= b < (1 << (y + 1)
	const int logB			= (N - 1) - origB.countLeadingZeros();
	hkSimdInt<N> maskA;		maskA.setFromInt32(-1);
							maskA.setShiftLeft(maskA, logB + 1);
 	hkSimdInt<N> aMask;		aMask.setAnd(origA, maskA);
	hkSimdInt<N> aDivB;		aDivB.setZero();
	hkSimdInt<N> a			= origA;	// This will contain a % b in the end

	while ( !aMask.equalZero().anyIsSet() )
	{
		// a >= b, so we can compute dx = a / (1 << logB) = (a >> logB)
		hkSimdInt<N> dx;	dx.setShiftRight(a, logB + 1);
							aDivB.setAdd(aDivB, dx);

		// Subtract dx * b from a
		dx.setUnsignedMul(origB, dx);	// b * dx
		a.setSub(a, dx);				// a -= b * dx
		
 		// Update a & maskA
		aMask.setAnd(a, maskA);
	}

	// Last iterations, linear convergence
	{
		hkSimdInt<N> negB;	negB.setNeg(origB);

		modOut = a;		a.setAdd(a, negB);
		while ( !a.lessZero().anyIsSet() )
		{
			aDivB.increment();
			modOut = a;	a.setAdd(a, negB);
		}
	}

	divOut = aDivB;
}

//
//	Compares the fractions (a / b) and (c / d), returning 1 if (a/b) > (c/d), 0 if they are equal, or -1 otherwise

template <int N>
int HK_CALL hkSimdInt<N>::compareFractions(const hkSimdInt<N>& origA, const hkSimdInt<N>& origB, const hkSimdInt<N>& origC, const hkSimdInt<N>& origD)
{
	// Compute signs of a, b, c, d and reduce the problem to comparing positive quantities
	int flipResult = 0;
	{
		hkVector4fComparison sAB;	sAB.setXor(origA.lessZero(), origB.lessZero());						// [(a/b) <= 0, *, *, *]
									sAB.setSelect<hkVector4ComparisonMask::MASK_X>(sAB, origA.equalZero());	// [(a/b) <= 0, (a/b) == 0, *, *]
		hkVector4fComparison sCD;	sCD.setXor(origC.lessZero(), origD.lessZero());						// [*, *, (c/d) <= 0, *]
									sCD.setSelect<hkVector4ComparisonMask::MASK_Z>(sCD, origC.equalZero());	// [*, *, (c/d) <= 0, (c/d) == 0]
		hkVector4fComparison sABCD;	sABCD.setSelect<hkVector4ComparisonMask::MASK_XY>(sAB, sCD);			// [(a/b) <= 0, (a/b) == 0, (c/d) <= 0, (c/d) == 0]
		const int signsMask			= sABCD.getMask();													// (c/d) == 0, (c/d) <= 0, (a/b) == 0, (a/b) <= 0
		const int retCode			= (0x5252AE03 >> (signsMask << 1)) & 3;

		// See if we can early exit based on signs!
		if ( retCode != 3 )
		{
			return retCode - 1;
		}

		// We only need to compute if both are positive or both are negative, i.e signsMask = 0 or 5.
		// For signsMask == 5 we need to flip the sign of the result!
		HK_ASSERT(0x2d843cbf, (signsMask == 0) || (signsMask == 5));
		flipResult = (signsMask == 5);
	}

	// Work on the absolute values
	hkSimdInt<N> a;	a.setAbs(origA);
	hkSimdInt<N> b;	b.setAbs(origB);
	hkSimdInt<N> c;	c.setAbs(origC);
	hkSimdInt<N> d;	d.setAbs(origD);

	// Start iterating
	do
	{
		// Divide a by b and c by d
		hkSimdInt<N> aDivB, aModB;	hkSimdInt<N>::computeUnsignedDivMod(a, b, aDivB, aModB);	// (a / b) = aDivB * b + aModB, aModB < b
		hkSimdInt<N> cDivD, cModD;	hkSimdInt<N>::computeUnsignedDivMod(c, d, cDivD, cModD);	// (c / d) = cDivD * d + cModD, cModD < d

		// Compare aDivB against cDivD. If inequality, we can stop!
		hkSimdInt<N> abSubCd;		abSubCd.setSub(aDivB, cDivD);	// (aDivB - cDivD)
		if ( !abSubCd.equalZero().anyIsSet() )
		{
			// Integer parts not equal, we can stop!
			const int ret = abSubCd.lessZero().anyIsSet() ? -1 : 1;	// aDivB < cDivD ? -1 : 1
			return flipResult ? -ret : ret;
		}

		// At this point aDivB == cDivD. We've reduced the problem to comparing aModB / b with cModD / d
		// Check if the remainders are non-zero
		{
			hkVector4fComparison modZero;	modZero.setSelect<hkVector4ComparisonMask::MASK_X>(aModB.equalZero(), cModD.equalZero());
			const int modZeroMask			= modZero.getMask() & 3;		// (cModD == 0), (aModB == 0)
			const int ret					= ((0x53 >> (modZeroMask << 1)) & 3) - 1;
			if ( ret != 2 )
			{
				return flipResult ? -ret : ret;
			}
		}

		// Reverse the fractions and flip the result
		a = b;	b = aModB;
		c = d;	d = cModD;
		flipResult = 1 - flipResult;
	} while ( true );

	return 0;
}

//
//    Sets this = a / b

template <int N>
inline int HK_CALL hkSimdInt<N>::computeDiv32(const hkSimdInt<N>& origA, const hkSimdInt<N>& origB)
{
	// Make values absolute
	hkSimdInt<N> a;    a.setAbs(origA);
	hkSimdInt<N> b;    b.setAbs(origB);
	HK_ASSERT(0x65c143c8, !b.equalZero().anyIsSet());    // Check division by zero!

	// Compute log(b), i.e. y = such that (1 << y) <= b < (1 << (y + 1)
	const int logB			= (N - 1) - b.countLeadingZeros();
	hkSimdInt<N> maskA;		maskA.setFromInt32(-1);
							maskA.setShiftLeft(maskA, logB + 1);
	hkSimdInt<N> aMask;		aMask.setAnd(a, maskA);
	int aDivB = 0;

	while ( !aMask.equalZero().anyIsSet() )
	{
		// a >= b, so we can compute dx = a / (1 << logB) = (a >> logB)
		hkSimdInt<N> dx256;		dx256.setShiftRight(a, logB + 1);
		const int dx		   = dx256.m_lo.template getWord<0>();

		// dx should be just an int!
		aDivB += dx;
		HK_ASSERT(0x3ad9a760, dx256.m_hi.equalZero().anyIsSet());

		// Subtract dx * b from a
		dx256.setUnsignedMul(b, dx);    // b * dx
		a.setSub(a, dx256);				// a -= b * dx

		// Update a & maskA
		aMask.setAnd(a, maskA);
	}

	// Last iterations, linear convergence
	{
		hkSimdInt<N> negB;	negB.setNeg(b);
		a.setAdd(a, negB);
		while ( !a.lessZero().anyIsSet() )
		{
			aDivB++;
			a.setAdd(a, negB);
		}
	}

	// Set proper signs!
	{
		const hkVector4fComparison negX	= origA.lessZero();							// (x < 0)
		const hkVector4fComparison negY	= origB.lessZero();							// (y < 0)
		hkVector4fComparison negZeroX;	negZeroX.setOr(negX, origA.equalZero());	// (x <= 0)
		hkVector4fComparison negZeroY;	negZeroY.setOr(negY, origB.equalZero());	// (y <= 0)
		hkVector4fComparison negX_posY;	negX_posY.setAndNot(negX, negZeroY);		// (x < 0) && (y > 0)
		hkVector4fComparison posX_negY;	posX_negY.setAndNot(negY, negZeroX);		// (y < 0) && (x > 0)
		hkVector4fComparison neg;		neg.setOr(negX_posY, posX_negY);			// sign(xy)

		// Set proper signs
		const int sign = 1 - ((neg.getMask() & 1) << 1);
		HK_ASSERT(0x158ec83e, (neg.anyIsSet() && (sign == -1)) || (!neg.anyIsSet() && (sign == 1)));
		return sign * aDivB;
	}
}

//
//	Sets this = a + b

template <int N>
inline void hkSimdInt<N>::setUnsignedAdd(HalfIntParameter a, HalfIntParameter b)
{
	// a = [0, 0, a1, a0]
	// b = [0, 0, b1, b0]
	HalfInt	a0b0;	a0b0.setUnsignedAdd(a.m_lo, b.m_lo);		// (a0 + b0)
	HalfInt a1b1;	a1b1.setUnsignedAdd(a.m_hi, b.m_hi);		// (a1 + b1)
	HalfInt r1;		r1.setUnsignedAdd(a1b1.m_lo, a0b0.m_hi);	// r1 = hi(a0 + b0) + lo(a1 + b1)
	HalfInt r2;		r2.setUnsignedAdd(r1.m_hi, a1b1.m_hi);		// r2 = hi(a1 + b1) + hi(r1)

	m_lo.m_lo = a0b0.m_lo;
	m_lo.m_hi = r1.m_lo;
	m_hi.m_lo = r2.m_lo;
	m_hi.m_hi.setZero();
}

#endif	// __HAVOK_PARSER__

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
