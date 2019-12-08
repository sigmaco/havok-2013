/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

namespace hkSimdInt128Impl
{
	static const hkUint32 hkUint32AllBits = 0xffffffff;
	static const hkUint32 hkUint32Msb = 0x80000000;
	static const hkUint64 hkUint64Msb = 0x8000000000000000LU;
	static const hkUint64 hkUint64Bit32 = hkUint64(1)<<31;

	inline hkInt32 bcastSgn(hkUint32 i)
	{
		return -hkInt32((i&hkUint32Msb)>>31);
	}

	inline hkInt32 bcastSgn(hkInt32 i)
	{
		return -hkInt32((i&hkUint32Msb)>>31);
	}

	inline hkInt64 bcastSgn(hkUint64 i)
	{
		return -hkInt64((i&hkUint64Msb)>>63);
	}

	inline hkInt64 bcastSgn(hkInt64 i)
	{
		return -hkInt64((i&hkUint64Msb)>>63);
	}

	inline void fillWithSign(const hkSimdInt<128>& src, hkSimdInt<128>& dst)
	{
		dst.m_quad.setU64<0>(bcastSgn(src.m_quad.getU64<1>()));
		dst.m_quad.setU64<1>(bcastSgn(src.m_quad.getU64<1>()));
	}
}

//
//	Sets this = i

inline void hkSimdInt<128>::setFromInt32(hkInt32 i)
{
	hkUint32 sgn = (hkUint32)hkSimdInt128Impl::bcastSgn(i);
	m_quad.setU32<0>(i);
	m_quad.setU32<1>(sgn);
	m_quad.setU32<2>(sgn);
	m_quad.setU32<3>(sgn);
}

//
//	Sets this = 0

inline void hkSimdInt<128>::setZero()
{
	m_quad.setU32<0>(0);
	m_quad.setU32<1>(0);
	m_quad.setU32<2>(0);
	m_quad.setU32<3>(0);
}

inline void hkSimdInt<128>::setFromInt64(hkInt64 i)
{
	hkInt64 sgn = hkSimdInt128Impl::bcastSgn(i);
	m_quad.setS64<0>(i);
	m_quad.setS64<1>(sgn);
}

inline void hkSimdInt<128>::setFromUint64(hkUint64 i)
{
	m_quad.setU64<0>(i);
	m_quad.setU64<1>(0);
}

//
//	Sets this = a + b

inline void hkSimdInt<128>::setAdd(const hkSimdInt<128>& origA, const hkSimdInt<128>& origB)
{
	hkSimdInt<128> res;	// Support aliased variables.
	res.m_quad.setU64<0>	(origA.m_quad.getU64<0>() + origB.m_quad.getU64<0>());
	const hkUint64 carry	= res.m_quad.getU64<0>() >= origA.m_quad.getU64<0>() ? 0 : 1;
	res.m_quad.setU64<1>	(origA.m_quad.getU64<1>() + origB.m_quad.getU64<1>());
	res.m_quad.setU64<1>	(res.m_quad.getU64<1>() + carry);
	m_quad = res.m_quad;
}

//
//	Sets this = a + b

namespace hkSimdInt128Impl
{
	inline void setUnsignedAdd(hkUint64 a, hkUint64 b, hkSimdInt<128>& c)
	{
		c.m_quad.setU64<0>(a + b);
		c.m_quad.setU64<1>(c.m_quad.getU64<0>() >= a ? 0 : 1);
	}
}

//
//	Increments this = this + 1 (faster than add(1)).

inline void hkSimdInt<128>::increment()
{
	m_quad.setU64<0>(m_quad.getU64<0>() + 1);
	const hkUint64 carry = m_quad.getU64<0>() == 0 ? 1 : 0;
	m_quad.setU64<1>(m_quad.getU64<1>() + carry);
}

//
//	Returns this < 0

template <> inline const hkVector4fComparison hkSimdInt<128>::lessZero<hkVector4fComparison>() const
{
	hkInt32 sgn = hkSimdInt128Impl::bcastSgn(m_quad.getU32<3>());
	hkVector4fComparison cmp;
	cmp.set((hkVector4ComparisonMask::Mask)(sgn & hkVector4ComparisonMask::MASK_XYZW));
	return cmp;
}

template <> inline const hkVector4dComparison hkSimdInt<128>::lessZero<hkVector4dComparison>() const
{
	hkInt32 sgn = hkSimdInt128Impl::bcastSgn(m_quad.getU32<3>());
	hkVector4dComparison cmp;
	cmp.set((hkVector4ComparisonMask::Mask)(sgn & hkVector4ComparisonMask::MASK_XYZW));
	return cmp;
}

inline const hkVector4fComparison hkSimdInt<128>::lessZero() const
{
	return lessZero<hkVector4fComparison>();
}

//
//	Returns this == 0

template <> inline const hkVector4fComparison hkSimdInt<128>::equalZero<hkVector4fComparison>() const
{
	hkUint64 or64 = m_quad.getU64<0>() | m_quad.getU64<1>();
	hkVector4fComparison cmp;
	cmp.set(or64 ? hkVector4ComparisonMask::MASK_NONE : hkVector4ComparisonMask::MASK_XYZW);
	return cmp;
}

template <> inline const hkVector4dComparison hkSimdInt<128>::equalZero<hkVector4dComparison>() const
{
	hkUint64 or64 = m_quad.getU64<0>() | m_quad.getU64<1>();
	hkVector4dComparison cmp;
	cmp.set(or64 ? hkVector4ComparisonMask::MASK_NONE : hkVector4ComparisonMask::MASK_XYZW);
	return cmp;
}

inline const hkVector4fComparison hkSimdInt<128>::equalZero() const
{
	return equalZero<hkVector4fComparison>();
}

//
//	Returns this == v

inline const hkVector4fComparison hkSimdInt<128>::equal(const hkSimdInt<128>& v) const
{
	bool alleq = (m_quad.getU64<0>() == v.m_quad.getU64<0>()) && (m_quad.getU64<1>() == v.m_quad.getU64<1>());
	hkVector4fComparison cmp;
	cmp.set( alleq ? hkVector4ComparisonMask::MASK_XYZW : hkVector4ComparisonMask::MASK_NONE);
	return cmp;
}

//
//	Sets this = cmp ? vTrue : vFalse

inline void hkSimdInt<128>::setSelect(hkVector4fComparisonParameter cmp, const hkSimdInt<128>& vTrue, const hkSimdInt<128>& vFalse)
{
	m_quad.setU64<0>(cmp.allAreSet() ? vTrue.m_quad.getU64<0>() : vFalse.m_quad.getU64<0>());
	m_quad.setU64<1>(cmp.allAreSet() ? vTrue.m_quad.getU64<1>() : vFalse.m_quad.getU64<1>());
}

//
//	Sets this = a & b

inline void hkSimdInt<128>::setAnd(const hkSimdInt<128>& a, const hkSimdInt<128>& b)
{
	m_quad.setU64<0>(a.m_quad.getU64<0>() & b.m_quad.getU64<0>());
	m_quad.setU64<1>(a.m_quad.getU64<1>() & b.m_quad.getU64<1>());
}

//
//	Sets this = a | b

inline void hkSimdInt<128>::setOr(const hkSimdInt<128>& a, const hkSimdInt<128>& b)
{
	m_quad.setU64<0>(a.m_quad.getU64<0>() | b.m_quad.getU64<0>());
	m_quad.setU64<1>(a.m_quad.getU64<1>() | b.m_quad.getU64<1>());
}

//
//	Sets this = ~a

inline void hkSimdInt<128>::setNot(const hkSimdInt<128>& v)
{
	m_quad.setU64<0>(~v.m_quad.getU64<0>());
	m_quad.setU64<1>(~v.m_quad.getU64<1>());
}

//
//	Sets this = a << I

namespace hkSimdInt128Impl
{
	template <int I, bool under64> struct ShlBitsFpu {};
	template <int I> struct ShlBitsFpu<I, true>
	{
		static HK_FORCE_INLINE void HK_CALL shl(const hkSimdInt<128>& src, hkSimdInt<128>& dest)
		{
			hkSimdInt<128> res;	// Support aliased variables.
			res.m_quad.setU64<0>((src.m_quad.getU64<0>() << (I)));
			res.m_quad.setU64<1>((src.m_quad.getU64<1>() << (I)) | (src.m_quad.getU64<0>() >> (64 - (I))));
			dest = res;
		}
	};
	template <int I> struct ShlBitsFpu<I, false>
	{
		static HK_FORCE_INLINE void HK_CALL shl(const hkSimdInt<128>& src, hkSimdInt<128>& dest)
		{
			hkSimdInt<128> res;	// Support aliased variables.
			res.m_quad.setU64<0>(0);
			res.m_quad.setU64<1>(src.m_quad.getU64<0>() << ((I) - 64));
			dest = res;
		}
	};

	template <int I, bool under64> struct ShrBitsFpu {};
	template <int I> struct ShrBitsFpu<I, true>
	{
		static HK_FORCE_INLINE void HK_CALL shr(const hkSimdInt<128>& src, hkSimdInt<128>& dest)
		{
			hkSimdInt<128> res;	// Support aliased variables.
			res.m_quad.setU64<0>((src.m_quad.getU64<0>() >> (I)) | (src.m_quad.getU64<1>() << (64 - (I))));
			res.m_quad.setU64<1>((src.m_quad.getU64<1>() >> (I)));
			dest = res;
		}
	};
	template <int I> struct ShrBitsFpu<I, false>
	{
		static HK_FORCE_INLINE void HK_CALL shr(const hkSimdInt<128>& src, hkSimdInt<128>& dest)
		{
			hkSimdInt<128> res;	// Support aliased variables.
			res.m_quad.setU64<0>(src.m_quad.getU64<1>() >> ((I) - 64));
			res.m_quad.setU64<1>(0);
			dest = res;
		}
	};

	template<int I> void shiftLeftBytes(const hkSimdInt<128>& src, hkSimdInt<128>& dest)
	{
		const int NB		= I << 3;
		const bool under64	= NB < 64;
		ShlBitsFpu<NB, under64>::shl(src, dest);
	}

	template<int I> void shiftRightBytes(const hkSimdInt<128>& src, hkSimdInt<128>& dest)
	{
		const int NB		= I << 3;
		const bool under64	= NB < 64;
		ShrBitsFpu<NB, under64>::shr(src, dest);
	}
}

template <> inline void hkSimdInt<128>::setShiftLeft<0>	(const hkSimdInt<128>& a)	{	*this = a;	}
template <> inline void hkSimdInt<128>::setShiftLeft<8>	(const hkSimdInt<128>& a)	{	hkSimdInt128Impl::shiftLeftBytes<1>(a, *this);	}
template <> inline void hkSimdInt<128>::setShiftLeft<16>(const hkSimdInt<128>& a)	{	hkSimdInt128Impl::shiftLeftBytes<2>(a, *this);	}
template <> inline void hkSimdInt<128>::setShiftLeft<24>(const hkSimdInt<128>& a)	{	hkSimdInt128Impl::shiftLeftBytes<3>(a, *this);	}
template <> inline void hkSimdInt<128>::setShiftLeft<32>(const hkSimdInt<128>& a)	{	hkSimdInt128Impl::shiftLeftBytes<4>(a, *this);	}
template <> inline void hkSimdInt<128>::setShiftLeft<40>(const hkSimdInt<128>& a)	{	hkSimdInt128Impl::shiftLeftBytes<5>(a, *this);	}
template <> inline void hkSimdInt<128>::setShiftLeft<48>(const hkSimdInt<128>& a)	{	hkSimdInt128Impl::shiftLeftBytes<6>(a, *this);	}
template <> inline void hkSimdInt<128>::setShiftLeft<56>(const hkSimdInt<128>& a)	{	hkSimdInt128Impl::shiftLeftBytes<7>(a, *this);	}
template <> inline void hkSimdInt<128>::setShiftLeft<64>(const hkSimdInt<128>& a)	{	hkSimdInt128Impl::shiftLeftBytes<8>(a, *this);	}
template <> inline void hkSimdInt<128>::setShiftLeft<72>(const hkSimdInt<128>& a)	{	hkSimdInt128Impl::shiftLeftBytes<9>(a, *this);	}
template <> inline void hkSimdInt<128>::setShiftLeft<80>(const hkSimdInt<128>& a)	{	hkSimdInt128Impl::shiftLeftBytes<10>(a, *this);	}
template <> inline void hkSimdInt<128>::setShiftLeft<88>(const hkSimdInt<128>& a)	{	hkSimdInt128Impl::shiftLeftBytes<11>(a, *this);	}
template <> inline void hkSimdInt<128>::setShiftLeft<96>(const hkSimdInt<128>& a)	{	hkSimdInt128Impl::shiftLeftBytes<12>(a, *this);	}
template <> inline void hkSimdInt<128>::setShiftLeft<104>(const hkSimdInt<128>& a)	{	hkSimdInt128Impl::shiftLeftBytes<13>(a, *this);	}
template <> inline void hkSimdInt<128>::setShiftLeft<112>(const hkSimdInt<128>& a)	{	hkSimdInt128Impl::shiftLeftBytes<14>(a, *this);	}
template <> inline void hkSimdInt<128>::setShiftLeft<120>(const hkSimdInt<128>& a)	{	hkSimdInt128Impl::shiftLeftBytes<15>(a, *this);	}
template <> inline void hkSimdInt<128>::setShiftLeft<128>(const hkSimdInt<128>& a)	{	setZero();										}

template <int I>
inline void hkSimdInt<128>::setShiftLeft(const hkSimdInt<128>& a)
{
	const bool under64 = I < 64;
	hkSimdInt128Impl::ShlBitsFpu<I, under64>::shl(a, *this);
}

//
//	Sets this = a >> I

template <> inline void hkSimdInt<128>::setShiftRight<0, HK_VALUE_UNSIGNED>	(const hkSimdInt<128>& a)	{	*this = a;	}
template <> inline void hkSimdInt<128>::setShiftRight<8, HK_VALUE_UNSIGNED>	(const hkSimdInt<128>& a)	{	hkSimdInt128Impl::shiftRightBytes<1>(a, *this);	}
template <> inline void hkSimdInt<128>::setShiftRight<16, HK_VALUE_UNSIGNED>(const hkSimdInt<128>& a)	{	hkSimdInt128Impl::shiftRightBytes<2>(a, *this);	}
template <> inline void hkSimdInt<128>::setShiftRight<24, HK_VALUE_UNSIGNED>(const hkSimdInt<128>& a)	{	hkSimdInt128Impl::shiftRightBytes<3>(a, *this);	}
template <> inline void hkSimdInt<128>::setShiftRight<32, HK_VALUE_UNSIGNED>(const hkSimdInt<128>& a)	{	hkSimdInt128Impl::shiftRightBytes<4>(a, *this);	}
template <> inline void hkSimdInt<128>::setShiftRight<40, HK_VALUE_UNSIGNED>(const hkSimdInt<128>& a)	{	hkSimdInt128Impl::shiftRightBytes<5>(a, *this);	}
template <> inline void hkSimdInt<128>::setShiftRight<48, HK_VALUE_UNSIGNED>(const hkSimdInt<128>& a)	{	hkSimdInt128Impl::shiftRightBytes<6>(a, *this);	}
template <> inline void hkSimdInt<128>::setShiftRight<56, HK_VALUE_UNSIGNED>(const hkSimdInt<128>& a)	{	hkSimdInt128Impl::shiftRightBytes<7>(a, *this);	}
template <> inline void hkSimdInt<128>::setShiftRight<64, HK_VALUE_UNSIGNED>(const hkSimdInt<128>& a)	{	hkSimdInt128Impl::shiftRightBytes<8>(a, *this);	}
template <> inline void hkSimdInt<128>::setShiftRight<72, HK_VALUE_UNSIGNED>(const hkSimdInt<128>& a)	{	hkSimdInt128Impl::shiftRightBytes<9>(a, *this);	}
template <> inline void hkSimdInt<128>::setShiftRight<80, HK_VALUE_UNSIGNED>(const hkSimdInt<128>& a)	{	hkSimdInt128Impl::shiftRightBytes<10>(a, *this);}
template <> inline void hkSimdInt<128>::setShiftRight<88, HK_VALUE_UNSIGNED>(const hkSimdInt<128>& a)	{	hkSimdInt128Impl::shiftRightBytes<11>(a, *this);}
template <> inline void hkSimdInt<128>::setShiftRight<96, HK_VALUE_UNSIGNED>(const hkSimdInt<128>& a)	{	hkSimdInt128Impl::shiftRightBytes<12>(a, *this);}
template <> inline void hkSimdInt<128>::setShiftRight<104, HK_VALUE_UNSIGNED>(const hkSimdInt<128>& a)	{	hkSimdInt128Impl::shiftRightBytes<13>(a, *this);}
template <> inline void hkSimdInt<128>::setShiftRight<112, HK_VALUE_UNSIGNED>(const hkSimdInt<128>& a)	{	hkSimdInt128Impl::shiftRightBytes<14>(a, *this);}
template <> inline void hkSimdInt<128>::setShiftRight<120, HK_VALUE_UNSIGNED>(const hkSimdInt<128>& a)	{	hkSimdInt128Impl::shiftRightBytes<15>(a, *this);}
template <> inline void hkSimdInt<128>::setShiftRight<128, HK_VALUE_UNSIGNED>(const hkSimdInt<128>& a)	{	setZero();	}

namespace hkSimdInt128Impl
{
	template <int N, hkMathValueType VAL> struct Shr {};

	template <int N> struct Shr<N, HK_VALUE_UNSIGNED>
	{
		static inline void HK_CALL shr(const hkSimdInt<128>& iIn, hkSimdInt<128>& iOut)
		{
			const bool under64 = N < 64;
			hkSimdInt128Impl::ShrBitsFpu<N, under64>::shr(iIn, iOut);
		}
	};

	template <int N> struct Shr<N, HK_VALUE_SIGNED>
	{
		static inline void HK_CALL shr(const hkSimdInt<128>& iIn, hkSimdInt<128>& iOut)
		{
			hkSimdInt<128> u;	u.setShiftRight<N, HK_VALUE_UNSIGNED>(iIn);
			hkSimdInt<128> s;	hkSimdInt128Impl::fillWithSign(iIn, s);
			s.setShiftLeft<128 - N>(s);
			iOut.setOr(u, s);
		}
	};
}

template <int I, hkMathValueType VAL>
inline void hkSimdInt<128>::setShiftRight(const hkSimdInt<128>& a)
{
	hkSimdInt128Impl::Shr<I, VAL>::shr(a, *this);
}

template <int I>
inline void hkSimdInt<128>::setShiftRight(const hkSimdInt<128>& a)
{
	setShiftRight<I, HK_VALUE_UNSIGNED>(a);
}

//
//	Returns the I-th 32-bit word, where LSB = 0, MSB = 3

template <>	inline int hkSimdInt<128>::getWord<0>() const	{	return m_quad.getS32<0>();	}
template <>	inline int hkSimdInt<128>::getWord<1>() const	{	return m_quad.getS32<1>();	}
template <>	inline int hkSimdInt<128>::getWord<2>() const	{	return m_quad.getS32<2>();	}
template <>	inline int hkSimdInt<128>::getWord<3>() const	{	return m_quad.getS32<3>();	}

//
//	Returns the I-th 64-bit word, where LSB = 0, MSB = 3

template <> inline hkInt64 hkSimdInt<128>::getDoubleWord<1>() const	
{	
	return m_quad.getS64<1>();
}

template <> inline hkInt64 hkSimdInt<128>::getDoubleWord<0>() const	
{	
	return m_quad.getS64<0>();
}

//
//	Returns the number of leading zeros

inline int hkSimdInt<128>::countLeadingZeros() const
{
	const int nz3 = hkMath::countLeadingZeros(m_quad.getS32<3>());
	const int nz2 = hkMath::countLeadingZeros(m_quad.getS32<2>());
	const int nz1 = hkMath::countLeadingZeros(m_quad.getS32<1>());
	const int nz0 = hkMath::countLeadingZeros(m_quad.getS32<0>());

	return	( nz3 < 32 ) ? nz3			: ( 
			( nz2 < 32 ) ? (32 + nz2)	: (
			( nz1 < 32 ) ? (64 + nz1)	: (96 + nz0) ) );
}

//
//	Returns the number of trailing zeros

inline int hkSimdInt<128>::countTrailingZeros() const
{
	const int nz3 = hkMath::countTrailingZeros(m_quad.getS32<3>());
	const int nz2 = hkMath::countTrailingZeros(m_quad.getS32<2>());
	const int nz1 = hkMath::countTrailingZeros(m_quad.getS32<1>());
	const int nz0 = hkMath::countTrailingZeros(m_quad.getS32<0>());

	return	( nz0 < 32 ) ? nz0			: ( 
			( nz1 < 32 ) ? (32 + nz1)	: (
			( nz2 < 32 ) ? (64 + nz2)	: (96 + nz3) ) );
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
