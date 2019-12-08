/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

namespace hkMxQuaterniond_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct gatherQH {
HK_FORCE_INLINE static void apply(hkVector4d* v, const hkQuaterniond* base)
{
	gatherQH<I-1, byteAddressIncrement>::apply(v, base);
	v[I-1] = hkAddByteOffsetConst( base, (I-1)*byteAddressIncrement )->m_vec;
} };
template <hkUint32 byteAddressIncrement> struct gatherQH<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(hkVector4d* v, const hkQuaterniond* base)
{
	v[0] = base->m_vec;
} };
}
template <int M>
template <hkUint32 byteAddressIncrement>
HK_FORCE_INLINE void hkMxQuaterniond<M>::gather(const hkQuaterniond* base)
{
	hkMxQuaterniond_Implementation::gatherQH<M, byteAddressIncrement>::apply(this->m_vec.v, base);
}




namespace hkMxQuaterniond_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct scatterQH {
HK_FORCE_INLINE static void apply(const hkVector4d* v, hkQuaterniond* base)
{
	scatterQH<I-1, byteAddressIncrement>::apply(v, base);
	hkAddByteOffset(base, (I-1)*byteAddressIncrement)->m_vec = v[I-1];
} };
template <hkUint32 byteAddressIncrement> struct scatterQH<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(const hkVector4d* v, hkQuaterniond* base)
{
	base->m_vec = v[0];
} };
}
template <int M>
template <hkUint32 byteAddressIncrement>
HK_FORCE_INLINE void hkMxQuaterniond<M>::scatter(hkQuaterniond* base) const
{
	hkMxQuaterniond_Implementation::scatterQH<M, byteAddressIncrement>::apply(this->m_vec.v, base);
}



namespace hkMxQuaterniond_Implementation
{
template <int I>
HK_FORCE_INLINE void setMulQH(hkQuaterniond* v, const hkQuaterniond* p, const hkQuaterniond* q)
{
	setMulQH<I-1>(v, p, q);
	v[I-1].setMul(p[I-1], q[I-1]);
}

template <>
HK_FORCE_INLINE void setMulQH<1>(hkQuaterniond* v, const hkQuaterniond* p, const hkQuaterniond* q)
{
	v[0].setMul(p[0], q[0]);
}
}
template <int M>
HK_FORCE_INLINE void hkMxQuaterniond<M>::setMulQ(hkMxQuaterniondParameter p, hkMxQuaterniondParameter q)
{
	hkMxQuaterniond_Implementation::setMulQH<M>( (hkQuaterniond*)this->m_vec.v, (const hkQuaterniond*)p.m_vec.v, (const hkQuaterniond*)q.m_vec.v);
}


namespace hkMxQuaterniond_Implementation
{
template <int I>
HK_FORCE_INLINE void setMulInverseQH(hkQuaterniond* v, const hkQuaterniond* p, const hkQuaterniond* q)
{
	setMulInverseQH<I-1>(v, p, q);
	v[I-1].setMulInverse(p[I-1], q[I-1]);
}

template <>
HK_FORCE_INLINE void setMulInverseQH<1>(hkQuaterniond* v, const hkQuaterniond* p, const hkQuaterniond* q)
{
	v[0].setMulInverse(p[0], q[0]);
}
}
template <int M>
HK_FORCE_INLINE void hkMxQuaterniond<M>::setMulInverseQ(hkMxQuaterniondParameter p, hkMxQuaterniondParameter q)
{
	hkMxQuaterniond_Implementation::setMulInverseQH<M>( (hkQuaterniond*)this->m_vec.v, (const hkQuaterniond*)p.m_vec.v, (const hkQuaterniond*)q.m_vec.v);
}


namespace hkMxQuaterniond_Implementation
{
template <int I>
HK_FORCE_INLINE void setInverseMulQH(hkQuaterniond* v, const hkQuaterniond* p, const hkQuaterniond* q)
{
	setInverseMulQH<I-1>(v, p, q);
	v[I-1].setInverseMul(p[I-1], q[I-1]);
}

template <>
HK_FORCE_INLINE void setInverseMulQH<1>(hkQuaterniond* v, const hkQuaterniond* p, const hkQuaterniond* q)
{
	v[0].setInverseMul(p[0], q[0]);
}
}
template <int M>
HK_FORCE_INLINE void hkMxQuaterniond<M>::setInverseMulQ(hkMxQuaterniondParameter p, hkMxQuaterniondParameter q)
{
	hkMxQuaterniond_Implementation::setInverseMulQH<M>( (hkQuaterniond*)this->m_vec.v, (const hkQuaterniond*)p.m_vec.v, (const hkQuaterniond*)q.m_vec.v);
}


namespace hkMxQuaterniond_Implementation
{
template <int I>
HK_FORCE_INLINE void setInverseQH(hkQuaterniond* v, const hkQuaterniond* p)
{
	setInverseQH<I-1>(v, p);
	v[I-1].setInverse(p[I-1]);
}

template <>
HK_FORCE_INLINE void setInverseQH<1>(hkQuaterniond* v, const hkQuaterniond* p)
{
	v[0].setInverse(p[0]);
}
}
template <int M>
HK_FORCE_INLINE void hkMxQuaterniond<M>::setInverse(hkMxQuaterniondParameter p)
{
	hkMxQuaterniond_Implementation::setInverseQH<M>( (hkQuaterniond*)this->m_vec.v, (const hkQuaterniond*)p.m_vec.v);
}



template <int M>
template <int I> 
HK_FORCE_INLINE const hkQuaterniond& hkMxQuaterniond<M>::getQuaternion() const
{
	HK_MXVECTORd_MX_SUBINDEX_CHECK;
	return (const hkQuaterniond&)this->m_vec.v[I];
}



namespace hkMxQuaterniond_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct scatterQHR {
HK_FORCE_INLINE static void apply(const hkVector4d* v, hkRotationd* base)
{
	scatterQHR<I-1, byteAddressIncrement>::apply(v, base);
	hkAddByteOffset(base, (I-1)*byteAddressIncrement)->set( (const hkQuaterniond&)v[I-1] );
} };
template <hkUint32 byteAddressIncrement> struct scatterQHR<4, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(const hkVector4d* v, hkRotationd* base)
{
	hkVector4dUtil::convert4QuaternionsToRotations( (const hkQuaterniond*)v,  // out of line call
		hkAddByteOffset(base, 0 * byteAddressIncrement),
		hkAddByteOffset(base, 1 * byteAddressIncrement),
		hkAddByteOffset(base, 2 * byteAddressIncrement),
		hkAddByteOffset(base, 3 * byteAddressIncrement)
		);
} };
template <hkUint32 byteAddressIncrement> struct scatterQHR<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(const hkVector4d* v, hkRotationd* base)
{
	hkVector4dUtil::convertQuaternionToRotation( (const hkQuaterniond&)v[0], base[0] );	// inline 
	//base->set( (const hkQuaterniond&)v[0] );	// out of line
} };
}
template <int M>
template <hkUint32 byteAddressIncrement>
HK_FORCE_INLINE void hkMxQuaterniond<M>::convertAndScatter(hkRotationd* HK_RESTRICT base) const
{
	hkMxQuaterniond_Implementation::scatterQHR<M, byteAddressIncrement>::apply(this->m_vec.v, base);
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
