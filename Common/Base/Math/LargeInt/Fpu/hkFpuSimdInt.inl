/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

//
//	Sets this = i
template <>
inline void hkSimdInt<256>::setFromInt32(int i)
{
	hkInt64 sgn = hkSimdInt128Impl::bcastSgn(hkInt64(i));
	m_lo.setFromInt32(i);
	m_hi.m_quad.setS64<0>(sgn);
	m_hi.m_quad.setS64<1>(sgn);
}

//
//	Sets this = a + b
template <>
inline void hkSimdInt<256>::setUnsignedAdd(const hkSimdInt<128>& a, const hkSimdInt<128>& b)
{
	HalfInt	a0b0;	hkSimdInt128Impl::setUnsignedAdd(a.m_quad.getU64<0>(), b.m_quad.getU64<0>(), a0b0);		// (a0 + b0)
	HalfInt a1b1;	hkSimdInt128Impl::setUnsignedAdd(a.m_quad.getU64<1>(), b.m_quad.getU64<1>(), a1b1);		// (a1 + b1)
	HalfInt r1;		hkSimdInt128Impl::setUnsignedAdd(a1b1.m_quad.getU64<0>(), a0b0.m_quad.getU64<1>(), r1);	// r1 = hi(a0 + b0) + lo(a1 + b1)
	HalfInt r2;		hkSimdInt128Impl::setUnsignedAdd(r1.m_quad.getU64<1>(), a1b1.m_quad.getU64<1>(), r2);		// r2 = hi(a1 + b1) + hi(r1)

	m_lo.m_quad.setU64<0>(a0b0.m_quad.getU64<0>());
	m_lo.m_quad.setU64<1>(r1.m_quad.getU64<0>());
	m_hi.m_quad.setU64<0>(r2.m_quad.getU64<0>());
	m_hi.m_quad.setU64<1>(0);
}

//
//	Sets this = a * b while ignoring any potential overflows

template <>
inline void hkSimdInt<256>::setUnsignedMul(const hkSimdInt<256>& origA, int origB)
{
	// a = [a7 a6 a5 a4][a3 a2 a1 a0], b = [*, *, *, b]
	const hkUint64 b	= (hkUint64)((hkUint32)origB);
	hkUint64 a0b		= ((hkUint64)origA.m_lo.m_quad.getU32<0>()) * b;
	hkUint64 a1b		= ((hkUint64)origA.m_lo.m_quad.getU32<1>()) * b;
	hkUint64 a2b		= ((hkUint64)origA.m_lo.m_quad.getU32<2>()) * b;
	hkUint64 a3b		= ((hkUint64)origA.m_lo.m_quad.getU32<3>()) * b;

	hkUint64 a4b		= ((hkUint64)origA.m_hi.m_quad.getU32<0>()) * b;
	hkUint64 a5b		= ((hkUint64)origA.m_hi.m_quad.getU32<1>()) * b;
	hkUint64 a6b		= ((hkUint64)origA.m_hi.m_quad.getU32<2>()) * b;
	hkUint64 a7b		= ((hkUint64)origA.m_hi.m_quad.getU32<3>()) * b;

	// Propagate carry bits & store result
	m_lo.m_quad.setU32<0>((hkUint32)(a0b & 0xFFFFFFFF));		a1b += (a0b >> 32L);
	m_lo.m_quad.setU32<1>((hkUint32)(a1b & 0xFFFFFFFF));		a2b += (a1b >> 32L);
	m_lo.m_quad.setU32<2>((hkUint32)(a2b & 0xFFFFFFFF));		a3b += (a2b >> 32L);
	m_lo.m_quad.setU32<3>((hkUint32)(a3b & 0xFFFFFFFF));		a4b += (a3b >> 32L);
	
	m_hi.m_quad.setU32<0>((hkUint32)(a4b & 0xFFFFFFFF));		a5b += (a4b >> 32L);
	m_hi.m_quad.setU32<1>((hkUint32)(a5b & 0xFFFFFFFF));		a6b += (a5b >> 32L);
	m_hi.m_quad.setU32<2>((hkUint32)(a6b & 0xFFFFFFFF));		a7b += (a6b >> 32L);
	m_hi.m_quad.setU32<3>((hkUint32)(a7b & 0xFFFFFFFF));
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
