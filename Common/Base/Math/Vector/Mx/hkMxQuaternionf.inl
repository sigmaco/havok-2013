/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

namespace hkMxQuaternionf_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct gatherQH {
HK_FORCE_INLINE static void apply(hkVector4f* v, const hkQuaternionf* base)
{
	gatherQH<I-1, byteAddressIncrement>::apply(v, base);
	v[I-1] = hkAddByteOffsetConst( base, (I-1)*byteAddressIncrement )->m_vec;
} };
template <hkUint32 byteAddressIncrement> struct gatherQH<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(hkVector4f* v, const hkQuaternionf* base)
{
	v[0] = base->m_vec;
} };
}
template <int M>
template <hkUint32 byteAddressIncrement>
HK_FORCE_INLINE void hkMxQuaternionf<M>::gather(const hkQuaternionf* base)
{
	hkMxQuaternionf_Implementation::gatherQH<M, byteAddressIncrement>::apply(this->m_vec.v, base);
}




namespace hkMxQuaternionf_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct scatterQH {
HK_FORCE_INLINE static void apply(const hkVector4f* v, hkQuaternionf* base)
{
	scatterQH<I-1, byteAddressIncrement>::apply(v, base);
	hkAddByteOffset(base, (I-1)*byteAddressIncrement)->m_vec = v[I-1];
} };
template <hkUint32 byteAddressIncrement> struct scatterQH<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(const hkVector4f* v, hkQuaternionf* base)
{
	base->m_vec = v[0];
} };
}
template <int M>
template <hkUint32 byteAddressIncrement>
HK_FORCE_INLINE void hkMxQuaternionf<M>::scatter(hkQuaternionf* base) const
{
	hkMxQuaternionf_Implementation::scatterQH<M, byteAddressIncrement>::apply(this->m_vec.v, base);
}



namespace hkMxQuaternionf_Implementation
{
template <int I>
HK_FORCE_INLINE void setMulQH(hkQuaternionf* v, const hkQuaternionf* p, const hkQuaternionf* q)
{
	setMulQH<I-1>(v, p, q);
	v[I-1].setMul(p[I-1], q[I-1]);
}

template <>
HK_FORCE_INLINE void setMulQH<1>(hkQuaternionf* v, const hkQuaternionf* p, const hkQuaternionf* q)
{
	v[0].setMul(p[0], q[0]);
}
}
template <int M>
HK_FORCE_INLINE void hkMxQuaternionf<M>::setMulQ(hkMxQuaternionfParameter p, hkMxQuaternionfParameter q)
{
	hkMxQuaternionf_Implementation::setMulQH<M>( (hkQuaternionf*)this->m_vec.v, (const hkQuaternionf*)p.m_vec.v, (const hkQuaternionf*)q.m_vec.v);
}


namespace hkMxQuaternionf_Implementation
{
template <int I>
HK_FORCE_INLINE void setMulInverseQH(hkQuaternionf* v, const hkQuaternionf* p, const hkQuaternionf* q)
{
	setMulInverseQH<I-1>(v, p, q);
	v[I-1].setMulInverse(p[I-1], q[I-1]);
}

template <>
HK_FORCE_INLINE void setMulInverseQH<1>(hkQuaternionf* v, const hkQuaternionf* p, const hkQuaternionf* q)
{
	v[0].setMulInverse(p[0], q[0]);
}
}
template <int M>
HK_FORCE_INLINE void hkMxQuaternionf<M>::setMulInverseQ(hkMxQuaternionfParameter p, hkMxQuaternionfParameter q)
{
	hkMxQuaternionf_Implementation::setMulInverseQH<M>( (hkQuaternionf*)this->m_vec.v, (const hkQuaternionf*)p.m_vec.v, (const hkQuaternionf*)q.m_vec.v);
}


namespace hkMxQuaternionf_Implementation
{
template <int I>
HK_FORCE_INLINE void setInverseMulQH(hkQuaternionf* v, const hkQuaternionf* p, const hkQuaternionf* q)
{
	setInverseMulQH<I-1>(v, p, q);
	v[I-1].setInverseMul(p[I-1], q[I-1]);
}

template <>
HK_FORCE_INLINE void setInverseMulQH<1>(hkQuaternionf* v, const hkQuaternionf* p, const hkQuaternionf* q)
{
	v[0].setInverseMul(p[0], q[0]);
}
}
template <int M>
HK_FORCE_INLINE void hkMxQuaternionf<M>::setInverseMulQ(hkMxQuaternionfParameter p, hkMxQuaternionfParameter q)
{
	hkMxQuaternionf_Implementation::setInverseMulQH<M>( (hkQuaternionf*)this->m_vec.v, (const hkQuaternionf*)p.m_vec.v, (const hkQuaternionf*)q.m_vec.v);
}


namespace hkMxQuaternionf_Implementation
{
template <int I>
HK_FORCE_INLINE void setInverseQH(hkQuaternionf* v, const hkQuaternionf* p)
{
	setInverseQH<I-1>(v, p);
	v[I-1].setInverse(p[I-1]);
}

template <>
HK_FORCE_INLINE void setInverseQH<1>(hkQuaternionf* v, const hkQuaternionf* p)
{
	v[0].setInverse(p[0]);
}
}
template <int M>
HK_FORCE_INLINE void hkMxQuaternionf<M>::setInverse(hkMxQuaternionfParameter p)
{
	hkMxQuaternionf_Implementation::setInverseQH<M>( (hkQuaternionf*)this->m_vec.v, (const hkQuaternionf*)p.m_vec.v);
}



template <int M>
template <int I> 
HK_FORCE_INLINE const hkQuaternionf& hkMxQuaternionf<M>::getQuaternion() const
{
	HK_MXVECTORf_MX_SUBINDEX_CHECK;
	return (const hkQuaternionf&)this->m_vec.v[I];
}



namespace hkMxQuaternionf_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct scatterQHR {
HK_FORCE_INLINE static void apply(const hkVector4f* v, hkRotationf* base)
{
	scatterQHR<I-1, byteAddressIncrement>::apply(v, base);
	hkAddByteOffset(base, (I-1)*byteAddressIncrement)->set( (const hkQuaternionf&)v[I-1] );
} };
template <hkUint32 byteAddressIncrement> struct scatterQHR<4, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(const hkVector4f* v, hkRotationf* base)
{
	hkVector4fUtil::convert4QuaternionsToRotations( (const hkQuaternionf*)v,  // out of line call
		hkAddByteOffset(base, 0 * byteAddressIncrement),
		hkAddByteOffset(base, 1 * byteAddressIncrement),
		hkAddByteOffset(base, 2 * byteAddressIncrement),
		hkAddByteOffset(base, 3 * byteAddressIncrement)
		);
} };
template <hkUint32 byteAddressIncrement> struct scatterQHR<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(const hkVector4f* v, hkRotationf* base)
{
	hkVector4fUtil::convertQuaternionToRotation( (const hkQuaternionf&)v[0], base[0] );	// inline 
	//base->set( (const hkQuaternionf&)v[0] );	// out of line
} };
}
template <int M>
template <hkUint32 byteAddressIncrement>
HK_FORCE_INLINE void hkMxQuaternionf<M>::convertAndScatter(hkRotationf* HK_RESTRICT base) const
{
	hkMxQuaternionf_Implementation::scatterQHR<M, byteAddressIncrement>::apply(this->m_vec.v, base);
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
