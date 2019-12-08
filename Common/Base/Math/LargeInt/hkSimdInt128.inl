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
//	Sets this = -v

inline void hkSimdInt<128>::setNeg(const hkSimdInt<128>& v)
{
	// Negate first
	setNot(v);
	
	// Add 1 to the negation
	increment();
}

//
//	Sets this = sign * v

inline void hkSimdInt<128>::setFlipSign(const hkSimdInt<128>& v, hkVector4fComparisonParameter sign)
{
	hkSimdInt<128> vNeg;
	vNeg.setNeg(v);
	setSelect(sign, vNeg, v);
}

//
//	Set this = abs(v)

inline void hkSimdInt<128>::setAbs(const hkSimdInt<128>& v)
{
	hkSimdInt<128> vNeg;
	vNeg.setNeg(v);
	setSelect(v.lessZero(), vNeg, v);
}

namespace hkSimdInt128Impl
{
	template <int N, int M>
	static inline void shlHelper(hkSimdInt<128>& v, hkIntVector& shl, hkIntVector& val)
	{
		const hkVector4Comparison cmp	= shl.greaterEqualS32(val);		// (shl >= N)
#ifdef HK_REAL_IS_DOUBLE
		hkVector4fComparison cmpf;		cmpf.set(cmp.getMask());
#else
		const hkVector4Comparison cmpf	= cmp;
#endif
		hkSimdInt<128> vs;				vs.setShiftLeft<N>(v);			// (v << N)
										v.setSelect(cmpf, vs, v);		// v = (shl >= N) ? (v << N) : v
		hkIntVector vals;				vals.setSubS32(shl, val);		// (shl - N)
										shl.setSelect(cmp, vals, shl);	// shl = (shl >= N) ? (shl - N) : shl
										val.setShiftRightS32<M>(val);	// N = N >> 1
	}
}

inline void hkSimdInt<128>::setShiftLeft(const hkSimdInt<128>& a, int shiftL)
{
	hkSimdInt<128> v = a;
	hkIntVector shl;	shl.setAll(shiftL);
	hkIntVector val;	val.setAll(64);

	hkSimdInt128Impl::shlHelper<64, 1>(v, shl, val);
	hkSimdInt128Impl::shlHelper<32, 1>(v, shl, val);
	hkSimdInt128Impl::shlHelper<16, 1>(v, shl, val);
	hkSimdInt128Impl::shlHelper<8, 1>(v, shl, val);
	hkSimdInt128Impl::shlHelper<4, 1>(v, shl, val);
	hkSimdInt128Impl::shlHelper<2, 1>(v, shl, val);
	hkSimdInt128Impl::shlHelper<1, 0>(v, shl, val);
	hkSimdInt128Impl::shlHelper<1, 0>(v, shl, val);

	*this = v;
}

namespace hkSimdInt128Impl
{
	template <int N, int M>
	static inline void shrHelper(hkSimdInt<128>& v, hkIntVector& shr, hkIntVector& val)
	{
		const hkVector4Comparison cmp	= shr.greaterEqualS32(val);		// (shr >= N)
#ifdef HK_REAL_IS_DOUBLE
		hkVector4fComparison cmpf;		cmpf.set(cmp.getMask());
#else
		const hkVector4fComparison cmpf	= cmp;
#endif
		hkSimdInt<128> vs;				vs.setShiftRight<N>(v);			// (v >> N)
										v.setSelect(cmpf, vs, v);		// v = (shr >= N) ? (v >> N) : v
		hkIntVector vals;				vals.setSubS32(shr, val);		// (shr - N)
										shr.setSelect(cmp, vals, shr);	// shr = (shr >= N) ? (shr - N) : shr
										val.setShiftRightS32<M>(val);	// N = N >> 1
	}
}

inline void hkSimdInt<128>::setShiftRight(const hkSimdInt<128>& a, int shiftR)
{
	hkSimdInt<128> v = a;
	hkIntVector shr;	shr.setAll(shiftR);
	hkIntVector val;	val.setAll(64);

	hkSimdInt128Impl::shrHelper<64, 1>(v, shr, val);	// 64
	hkSimdInt128Impl::shrHelper<32, 1>(v, shr, val);	// 96
	hkSimdInt128Impl::shrHelper<16, 1>(v, shr, val);	// 112
	hkSimdInt128Impl::shrHelper<8, 1>(v, shr, val);		// 120
	hkSimdInt128Impl::shrHelper<4, 1>(v, shr, val);		// 124
	hkSimdInt128Impl::shrHelper<2, 1>(v, shr, val);		// 126
	hkSimdInt128Impl::shrHelper<1, 0>(v, shr, val);		// 127
	hkSimdInt128Impl::shrHelper<1, 0>(v, shr, val);		// 128

	*this = v;
}

//
//	Sets this = a - b

inline void hkSimdInt<128>::setSub(const hkSimdInt<128>& a, const hkSimdInt<128>& b)
{
	hkSimdInt<128> negB;	negB.setNeg(b);
	setAdd(a, negB);
}

//
//	Sets this = the greatest common divisor of the given numbers. Both numbers are assumed to be positive!

inline void hkSimdInt<128>::setGreatestCommonDivisor(const hkSimdInt<128>& a, const hkSimdInt<128>& b)
{
	if ( a.equalZero().anyIsSet() )	{	*this = b;	return;	}
	if ( b.equalZero().anyIsSet() )	{	*this = a;	return;	}

	// Divide by 2 as much as possible
	int shift;
	hkSimdInt<128> u, v;
	{
		const int numTrailingZerosA = a.countTrailingZeros();
		const int numTrailingZerosB = b.countTrailingZeros();
		shift = hkMath::min2(numTrailingZerosA, numTrailingZerosB);

		u.setShiftRight(a, numTrailingZerosA);
		v.setShiftRight(b, shift);
	}

	// From here on, u is always odd.
	do
	{
		// Remove all factors of 2 in v; they are not common. Note: v is not zero!
		const int numTrailingZerosV = v.countTrailingZeros();
		v.setShiftRight(v, numTrailingZerosV);

		// Now u and v are both odd. Swap if necessary so u <= v, then set v = v - u (which is even).
		hkSimdInt<128> v_minus_u;			v_minus_u.setSub(v, u);			// (v - u)
		const hkVector4fComparison u_gt_v	= v_minus_u.lessZero();			// (u > v)
		hkSimdInt<128> u_minus_v;			u_minus_v.setNeg(v_minus_u);	// (u - v)

		u.setSelect(u_gt_v, v, u);
		v.setSelect(u_gt_v, u_minus_v, v_minus_u);
		// Here v >= u.
	} while ( !v.equalZero().anyIsSet() );

	// Restore common factors of 2
	setShiftLeft(u, shift);
}

//
//	Sets this = a * b. The operands are assumed to be small enough so they are not causing overflow

inline void hkSimdInt<128>::setMul(const hkSimdInt<128>& origX, hkInt64 iOrigY)
{
	// Make both terms positive
	hkSimdInt<128> x;		x.setAbs(origX);								// [a1, a0]
	hkSimdInt<128> y;		y.setFromUint64((hkUint64)hkMath::abs(iOrigY));	// [0, b0]

	// Compute 64-bit products
	hkSimdInt<128> a0b0, a1b0;
	{
		hkInt64Vector4 vTempX;		vTempX.loadXy(x);	vTempX.loadZw(x);						// [a1, a0, a1, a0]
		hkInt64Vector4 vTempY;		vTempY.loadXy(y);	vTempY.loadZw(y);						// [0, b0, 0, b0]
									vTempX.setPermutation<hkVectorPermutation::XYWZ>(vTempX);	// [a1, a0, a0, a1]
		hkInt64Vector4 a0bx;		a0bx.setUnsignedMul_128<2>(vTempX, vTempY);					// [a0b0, a1b0]
		a0bx.storeXy(a0b0);
		a0bx.storeZw(a1b0);
	}

	// Accumulate 64-bit products
	hkSimdInt<128> prodXY;
	{
		hkSimdInt<128> r2;		r2.setShiftRight<64>(a1b0);			// [0, hi(a1b0)]

		hkSimdInt<128> r1;		r1.setShiftLeft<64>(a1b0);			// [lo(a1b0), 0]
								r1.setShiftRight<64>(r1);			// [0, lo(a1b0)]

		hkSimdInt<128> hi_a0b0;	hi_a0b0.setShiftRight<64>(a0b0);	// [0, hi(a0b0)]
								r1.setAdd(r1, hi_a0b0);				// hi(a0b0) + lo(a0b1) + lo(a1b0)

		hkSimdInt<128> hi_r1;	hi_r1.setShiftRight<64>(r1);		// hi(hi(a0b0) + lo(a0b1) + lo(a1b0))
								r2.setAdd(r2, hi_r1);				// a1b1 + hi(a1b0) + hi(hi(a0b0) + lo(a1b0))

		hkSimdInt<128> r0;		r0.setShiftLeft<64>(a0b0);			// [lo(a0b0), 0]
								r0.setShiftRight<64>(r0);			// [0, lo(a0b0)]
		hkSimdInt<128> lo_r1;	lo_r1.setShiftLeft<64>(r1);			// [lo(r1), 0]

		prodXY.setOr(r0, lo_r1);									// [lo(r1), lo(a0b0)]
		HK_ASSERT(0x6ae1e28f, r2.equalZero().anyIsSet());
	}

	// Set proper signs
	{
		const hkVector4fComparison negX	= origX.lessZero();							// (x < 0)
		hkVector4fComparison negY;		negY.set((hkVector4ComparisonMask::Mask)(hkVector4ComparisonMask::MASK_XYZW & (iOrigY >> 63L)));	// (y < 0)
		hkVector4fComparison zeroY;		zeroY.set(iOrigY ? hkVector4ComparisonMask::MASK_NONE : hkVector4ComparisonMask::MASK_XYZW);		// (y == 0)
		hkVector4fComparison negZeroX;	negZeroX.setOr(negX, origX.equalZero());	// (x <= 0)
		hkVector4fComparison negZeroY;	negZeroY.setOr(negY, zeroY);				// (y <= 0)
		hkVector4fComparison negX_posY;	negX_posY.setAndNot(negX, negZeroY);		// (x < 0) && (y > 0)
		hkVector4fComparison posX_negY;	posX_negY.setAndNot(negY, negZeroX);		// (y < 0) && (x > 0)
		hkVector4fComparison neg;		neg.setOr(negX_posY, posX_negY);			// sign(xy)

		// Set proper signs
		setFlipSign(prodXY, neg);
	}
}

#endif	//__HAVOK_PARSER__

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
