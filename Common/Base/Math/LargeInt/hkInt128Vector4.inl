/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

//
//	Sets this = [x, y, z, w]

inline void hkInt128Vector4::set(const hkSimdInt<128>& x, const hkSimdInt<128>& y, const hkSimdInt<128>& z, const hkSimdInt<128>& w)
{
	m_x = x;	m_y = y;	m_z = z;	m_w = w;
}

//
//	Sets all components to the given value

inline void hkInt128Vector4::setAll(int i)
{
	m_x.setFromInt32(i);
	m_y = m_z = m_w = m_x;
}

//
//	Sets this = abs(v)

template <> inline void hkInt128Vector4::setAbs<1>(hkInt128Vector4Parameter v)	{	m_x.setAbs(v.m_x);	}
template <> inline void hkInt128Vector4::setAbs<2>(hkInt128Vector4Parameter v)	{	m_x.setAbs(v.m_x);	m_y.setAbs(v.m_y);	}
template <> inline void hkInt128Vector4::setAbs<3>(hkInt128Vector4Parameter v)	{	m_x.setAbs(v.m_x);	m_y.setAbs(v.m_y);	m_z.setAbs(v.m_z);	}
template <> inline void hkInt128Vector4::setAbs<4>(hkInt128Vector4Parameter v)	{	m_x.setAbs(v.m_x);	m_y.setAbs(v.m_y);	m_z.setAbs(v.m_z);	m_w.setAbs(v.m_w);	}

//
//	Sets this = a & b

template <> inline void hkInt128Vector4::setAnd<1>(hkInt128Vector4Parameter a, hkInt128Vector4Parameter b)	{	m_x.setAnd(a.m_x, b.m_x);	}
template <> inline void hkInt128Vector4::setAnd<2>(hkInt128Vector4Parameter a, hkInt128Vector4Parameter b)	{	m_x.setAnd(a.m_x, b.m_x);	m_y.setAnd(a.m_y, b.m_y);	}
template <> inline void hkInt128Vector4::setAnd<3>(hkInt128Vector4Parameter a, hkInt128Vector4Parameter b)	{	m_x.setAnd(a.m_x, b.m_x);	m_y.setAnd(a.m_y, b.m_y);	m_z.setAnd(a.m_z, b.m_z);	}
template <> inline void hkInt128Vector4::setAnd<4>(hkInt128Vector4Parameter a, hkInt128Vector4Parameter b)	{	m_x.setAnd(a.m_x, b.m_x);	m_y.setAnd(a.m_y, b.m_y);	m_z.setAnd(a.m_z, b.m_z);	m_w.setAnd(a.m_w, b.m_w);	}

namespace hkInt128Vector4Impl
{
	template <int N, int I> struct ShlHelper{};
	template <int I> struct ShlHelper<1, I>
	{
		static inline void exec(hkInt128Vector4Parameter vSrc, hkInt128Vector4& vDst)
		{
			vDst.m_x.setShiftLeft<I>(vSrc.m_x);
		}
	};
	template <int I> struct ShlHelper<2, I>
	{
		static inline void exec(hkInt128Vector4Parameter vSrc, hkInt128Vector4& vDst)
		{
			vDst.m_x.setShiftLeft<I>(vSrc.m_x);
			vDst.m_y.setShiftLeft<I>(vSrc.m_y);
		}
	};
	template <int I> struct ShlHelper<3, I>
	{
		static inline void exec(hkInt128Vector4Parameter vSrc, hkInt128Vector4& vDst)
		{
			vDst.m_x.setShiftLeft<I>(vSrc.m_x);
			vDst.m_y.setShiftLeft<I>(vSrc.m_y);
			vDst.m_z.setShiftLeft<I>(vSrc.m_z);
		}
	};
	template <int I> struct ShlHelper<4, I>
	{
		static inline void exec(hkInt128Vector4Parameter vSrc, hkInt128Vector4& vDst)
		{
			vDst.m_x.setShiftLeft<I>(vSrc.m_x);
			vDst.m_y.setShiftLeft<I>(vSrc.m_y);
			vDst.m_z.setShiftLeft<I>(vSrc.m_z);
			vDst.m_w.setShiftLeft<I>(vSrc.m_w);
		}
	};
}

//
//	Sets this = a << I per component

template <int N, int I>
inline void hkInt128Vector4::setShiftLeft(hkInt128Vector4Parameter v)
{
	hkInt128Vector4Impl::ShlHelper<N, I>(v, *this);
}

//
//	Returns this == 0

template <> inline const hkVector4fComparison hkInt128Vector4::equalZero<3>() const
{
	hkVector4fComparison cmpXY;		cmpXY.setSelect<hkVector4ComparisonMask::MASK_X>(m_x.equalZero(), m_y.equalZero());	// [x == 0, y == 0, *, *]
	hkVector4fComparison cmpXYZ;	cmpXYZ.setSelect<hkVector4ComparisonMask::MASK_XY>(cmpXY, m_z.equalZero());			// [x == 0, y == 0, z == 0, *]
	return cmpXYZ;
}

template <> inline const hkVector4fComparison hkInt128Vector4::equalZero<4>() const
{
	hkVector4fComparison cmpXY;		cmpXY.setSelect<hkVector4ComparisonMask::MASK_X>(m_x.equalZero(), m_y.equalZero());	// [x == 0, y == 0, *, *]
	hkVector4fComparison cmpZW;		cmpZW.setSelect<hkVector4ComparisonMask::MASK_Z>(m_z.equalZero(), m_w.equalZero());	// [*, *, z == 0, w == 0]
	hkVector4fComparison cmpXYZW;	cmpXYZW.setSelect<hkVector4ComparisonMask::MASK_XY>(cmpXY, cmpZW);					// [x == 0, y == 0, z == 0, w == 0]
	return cmpXYZW;
}

//
//	Returns this != 0

template <int N>
inline const hkVector4fComparison hkInt128Vector4::notEqualZero() const
{
	hkVector4fComparison cmpEq;	cmpEq.setNot(equalZero<N>());
	return cmpEq;
}

//
//	Sets this = vA * vB

template <> inline void hkInt128Vector4::setMul<3>(hkInt64Vector4Parameter vA, hkInt64Vector4Parameter vB)
{
	// Compute final signs
	hkVector4fComparison cmpFlip;
	{
		const hkVector4fComparison negA	= vA.lessZero();							// [ax < 0, ay < 0, az < 0, aw < 0]
		const hkVector4fComparison negB	= vB.lessZero();							// [bx < 0, by < 0, bz < 0, bw < 0]
		hkVector4fComparison negZeroA;	negZeroA.setOr(negA, vA.equalZero());		// [ax <= 0, ay <= 0, az <= 0, aw <= 0]
		hkVector4fComparison negZeroB;	negZeroB.setOr(negB, vB.equalZero());		// [bx <= 0, by <= 0, bz <= 0, bw <= 0]

		hkVector4fComparison negA_posB;	negA_posB.setAndNot(negA, negZeroB);		// [(ax < 0) && (bx > 0), ...]
		hkVector4fComparison posA_negB;	posA_negB.setAndNot(negB, negZeroA);		// [(ax > 0) && (bx < 0), ...]
										cmpFlip.setOr(negA_posB, posA_negB);		// [sign(ax * bx), ...]
	}

	// Set absolute values
	hkInt64Vector4 absA;	absA.setAbs(vA);
	hkInt64Vector4 absB;	absB.setAbs(vB);


	// vA = [ax, ay, az, aw]
	// vB = [bx, by, bz, bw]
	hkInt64Vector4 ab_yw;		ab_yw.setUnsignedMul_128<2>(absA, absB);				// [ayby, *]	
	hkInt64Vector4 a_yxwz;		a_yxwz.setPermutation<hkVectorPermutation::YXWZ>(absA);	// [ay, ax, aw, az]
	hkInt64Vector4 b_yxwz;		b_yxwz.setPermutation<hkVectorPermutation::YXWZ>(absB);	// [by, bx, bw, bz]
	hkInt64Vector4 ab_xz;		ab_xz.setUnsignedMul_128<2>(a_yxwz, b_yxwz);			// [axbx, azbz]

	// Store
	ab_xz.storeXy(m_x);	ab_xz.storeZw(m_z);
	ab_yw.storeXy(m_y);
	setFlipSign<3>(*this, cmpFlip);
}

template <> inline void hkInt128Vector4::setMul<4>(hkInt64Vector4Parameter vA, hkInt64Vector4Parameter vB)
{
	// vA = [ax, ay, az, aw]
	// vB = [bx, by, bz, bw]
	hkInt64Vector4 ab_yw;		ab_yw.setMul_128(vA, vB);								// [ayby, awbw]
	hkInt64Vector4 a_yxwz;		a_yxwz.setPermutation<hkVectorPermutation::YXWZ>(vA);	// [ay, ax, aw, az]
	hkInt64Vector4 b_yxwz;		b_yxwz.setPermutation<hkVectorPermutation::YXWZ>(vB);	// [by, bx, bw, bz]
	hkInt64Vector4 ab_xz;		ab_xz.setMul_128(a_yxwz, b_yxwz);						// [axbx, azbz]

	// Store
	ab_xz.storeXy(m_x);	ab_xz.storeZw(m_z);
	ab_yw.storeXy(m_y);	ab_yw.storeZw(m_w);
}

//
//	Sets this = sA * vB

template <> inline void hkInt128Vector4::setMul<1>(const hkSimdInt<128>& sA, hkInt64Vector4Parameter vB)	{	m_x.setMul(sA, vB.getComponent<0>());	}
template <> inline void hkInt128Vector4::setMul<2>(const hkSimdInt<128>& sA, hkInt64Vector4Parameter vB)	{	m_x.setMul(sA, vB.getComponent<0>());	m_y.setMul(sA, vB.getComponent<1>());	}
template <> inline void hkInt128Vector4::setMul<3>(const hkSimdInt<128>& sA, hkInt64Vector4Parameter vB)	{	m_x.setMul(sA, vB.getComponent<0>());	m_y.setMul(sA, vB.getComponent<1>());	m_z.setMul(sA, vB.getComponent<2>());	}
template <> inline void hkInt128Vector4::setMul<4>(const hkSimdInt<128>& sA, hkInt64Vector4Parameter vB)	{	m_x.setMul(sA, vB.getComponent<0>());	m_y.setMul(sA, vB.getComponent<1>());	m_z.setMul(sA, vB.getComponent<2>());	m_w.setMul(sA, vB.getComponent<3>());	}

//
//	Sets this = vA - vB

template <> inline void hkInt128Vector4::setSub<1>(hkInt128Vector4Parameter vA, hkInt128Vector4Parameter vB)	{	m_x.setSub(vA.m_x, vB.m_x);	}
template <> inline void hkInt128Vector4::setSub<2>(hkInt128Vector4Parameter vA, hkInt128Vector4Parameter vB)	{	m_x.setSub(vA.m_x, vB.m_x);	m_y.setSub(vA.m_y, vB.m_y);	}
template <> inline void hkInt128Vector4::setSub<3>(hkInt128Vector4Parameter vA, hkInt128Vector4Parameter vB)	{	m_x.setSub(vA.m_x, vB.m_x);	m_y.setSub(vA.m_y, vB.m_y);	m_z.setSub(vA.m_z, vB.m_z);	}
template <> inline void hkInt128Vector4::setSub<4>(hkInt128Vector4Parameter vA, hkInt128Vector4Parameter vB)	{	m_x.setSub(vA.m_x, vB.m_x);	m_y.setSub(vA.m_y, vB.m_y);	m_z.setSub(vA.m_z, vB.m_z);	m_w.setSub(vA.m_w, vB.m_w);	}

//
//	Sets this -= sa * vB

template <int N>
inline void hkInt128Vector4::subMul(const hkSimdInt<128>& sA, hkInt64Vector4Parameter vB)
{
	hkInt128Vector4 ab;	ab.setMul<N>(sA, vB);
	setSub<N>(*this, ab);
}

//
//	Returns the dot product of this and v using the first I components

template <>
inline const hkSimdInt<256> hkInt128Vector4::dot<3>(hkInt64Vector4Parameter v)
{
	hkSimdInt<256> vx;	vx.setMul(m_x, v.getComponent<0>());
	hkSimdInt<256> vy;	vy.setMul(m_y, v.getComponent<1>());
	hkSimdInt<256> vz;	vz.setMul(m_z, v.getComponent<2>());
	
	vx.setAdd(vx, vy);
	vx.setAdd(vx, vz);
	return vx;
}

template <>
inline const hkSimdInt<256> hkInt128Vector4::dot<3>(hkInt128Vector4Parameter v)
{
	hkSimdInt<256> ret;
	ret.setMul(m_x, v.m_x);
	ret.addMul(m_y, v.m_y);
	ret.addMul(m_z, v.m_z);
	return ret;
}

//
//	Sets this = Cross[vA, vB]

inline void hkInt128Vector4::setCross(hkInt64Vector4Parameter vA, hkInt64Vector4Parameter vB)
{
	// Permute vectors
	hkInt64Vector4 a_yzx;	a_yzx.setPermutation<hkVectorPermutation::YZXW>(vA);	// [ay, az, ax]
	hkInt64Vector4 a_zxy;	a_zxy.setPermutation<hkVectorPermutation::ZXYW>(vA);	// [az, ax, ay]
	hkInt64Vector4 b_yzx;	b_yzx.setPermutation<hkVectorPermutation::YZXW>(vB);	// [by, bz, bx]
	hkInt64Vector4 b_zxy;	b_zxy.setPermutation<hkVectorPermutation::ZXYW>(vB);	// [bz, bx, by]

	hkInt128Vector4 abp;	abp.setMul<3>(a_yzx, b_zxy);	// [aybz, azbx, axby]
	hkInt128Vector4 abn;	abn.setMul<3>(a_zxy, b_yzx);	// [azby, axbz, aybx]
	setSub<3>(abp, abn);	// [aybz - azby, azbx - axbz, axby - aybx]
}

//
//	Returns the i-th component

inline const hkSimdInt<128> hkInt128Vector4::getComponent(int i) const
{
	return reinterpret_cast<const hkSimdInt<128>*>(this)[i];
}

//
//	Sets this = a / b. Both a and b are assumed to be unsigned!

template <> inline void hkInt128Vector4::setUnsignedDiv<1>(hkInt128Vector4Parameter a, hkInt128Vector4Parameter b)	{	m_x.setUnsignedDiv(a.m_x, b.m_x);	}
template <> inline void hkInt128Vector4::setUnsignedDiv<2>(hkInt128Vector4Parameter a, hkInt128Vector4Parameter b)	{	m_x.setUnsignedDiv(a.m_x, b.m_x);	m_y.setUnsignedDiv(a.m_y, b.m_y);	}
template <> inline void hkInt128Vector4::setUnsignedDiv<3>(hkInt128Vector4Parameter a, hkInt128Vector4Parameter b)	{	m_x.setUnsignedDiv(a.m_x, b.m_x);	m_y.setUnsignedDiv(a.m_y, b.m_y);	m_z.setUnsignedDiv(a.m_z, b.m_z);	}
template <> inline void hkInt128Vector4::setUnsignedDiv<4>(hkInt128Vector4Parameter a, hkInt128Vector4Parameter b)	{	m_x.setUnsignedDiv(a.m_x, b.m_x);	m_y.setUnsignedDiv(a.m_y, b.m_y);	m_z.setUnsignedDiv(a.m_z, b.m_z);	m_w.setUnsignedDiv(a.m_w, b.m_w);	}

//
//	Returns the index of the component with the largest signed value among the first N components.
//	In case of equality, returns the last component index given X,Y,Z,W ordering.

template <> inline int hkInt128Vector4::getIndexOfMaxComponent<3>() const
{
	// Shuffle
	hkInt128Vector4 xxy;	xxy.m_x = m_x;	xxy.m_y = m_x;	xxy.m_z = m_y;	// [x, x, y]
	hkInt128Vector4 yzz;	yzz.m_x = m_y;	yzz.m_y = m_z;	yzz.m_z = m_z;	// [y, z, z]

	// Compare
	const hkVector4fComparison cmp = yzz.less<3>(xxy);	// [*, y > z, x > z, x > y]
	const int mask = (cmp.getMask() & 7) << 1;
	return (0x192A >> mask) & 3;
}

//
//	Returns this < v

template <int N>
inline const hkVector4fComparison hkInt128Vector4::less(hkInt128Vector4Parameter v) const
{
	hkInt128Vector4 amb;	amb.setSub<N>(*this, v);
	return amb.lessZero();
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
