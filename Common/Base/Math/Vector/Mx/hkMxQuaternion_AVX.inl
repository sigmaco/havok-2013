/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#if defined(HK_REAL_IS_DOUBLE) || (HK_SSE_VERSION < 0x50)
#error This implementation is for 32-Bit float with AVX SIMD instruction set
#endif

#include <Common/Base/Math/Vector/Mx/hkMxCommon_AVX.inl>


namespace hkMxQuaternionf_Implementation
{
template <int I, int N, hkUint32 byteAddressIncrement> struct gatherQH {
HK_FORCE_INLINE static void apply(__m256* v, const __m128* base)
{
	v[N] = _mm256_insertf128_ps(_mm256_undefined_ps(), *hkAddByteOffsetConst( base, (N*2)*byteAddressIncrement ), 0x0);
	v[N] = _mm256_insertf128_ps(v[N], *hkAddByteOffsetConst( base, (N*2+1)*byteAddressIncrement ), 0x1);
	gatherQH<I-2, N+1, byteAddressIncrement>::apply(v, base);
} };
template <int N, hkUint32 byteAddressIncrement> struct gatherQH<2, N, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(__m256* v, const __m128* base)
{
	v[N] = _mm256_insertf128_ps(_mm256_undefined_ps(), *hkAddByteOffsetConst( base, (N*2)*byteAddressIncrement ), 0x0);
	v[N] = _mm256_insertf128_ps(v[N], *hkAddByteOffsetConst( base, (N*2+1)*byteAddressIncrement ), 0x1);
} };
template <int N, hkUint32 byteAddressIncrement> struct gatherQH<1, N, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(__m256* v, const __m128* base)
{
	v[N] = _mm256_broadcast_ps(hkAddByteOffsetConst( base, (N*2)*byteAddressIncrement ));
} };
}
template <int M>
template <hkUint32 byteAddressIncrement>
HK_FORCE_INLINE void hkMxQuaternionf<M>::gather(const hkQuaternionf* base)
{
	hkMxQuaternionf_Implementation::gatherQH<M, 0, byteAddressIncrement>::apply(this->m_vec.v, &(base->m_vec.m_quad));
}




namespace hkMxQuaternionf_Implementation
{
template <int I, int N, hkUint32 byteAddressIncrement> struct scatterQH {
HK_FORCE_INLINE static void apply(const __m256* v, __m128* base)
{
	__m128* HK_RESTRICT ptr0 = hkAddByteOffset(base, (N*2) * byteAddressIncrement);
	__m128* HK_RESTRICT ptr1 = hkAddByteOffset(base, (N*2+1) * byteAddressIncrement);
	*ptr0 = _mm256_extractf128_ps(v[N], 0x0);
	*ptr1 = _mm256_extractf128_ps(v[N], 0x1);
	scatterQH<I-2, N+1, byteAddressIncrement>::apply(v, base);
} };
template <int N, hkUint32 byteAddressIncrement> struct scatterQH<2, N, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(const __m256* v, __m128* base)
{
	__m128* HK_RESTRICT ptr0 = hkAddByteOffset(base, (N*2) * byteAddressIncrement);
	__m128* HK_RESTRICT ptr1 = hkAddByteOffset(base, (N*2+1) * byteAddressIncrement);
	*ptr0 = _mm256_extractf128_ps(v[N], 0x0);
	*ptr1 = _mm256_extractf128_ps(v[N], 0x1);
} };
template <int N, hkUint32 byteAddressIncrement> struct scatterQH<1, N, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(const __m256* v, __m128* base)
{
	__m128* HK_RESTRICT ptr = hkAddByteOffset(base, (N*2) * byteAddressIncrement);
	*ptr = _mm256_extractf128_ps(v[N], 0x0);
} };
}
template <int M>
template <hkUint32 byteAddressIncrement>
HK_FORCE_INLINE void hkMxQuaternionf<M>::scatter(hkQuaternionf* base) const
{
	hkMxQuaternionf_Implementation::scatterQH<M, 0, byteAddressIncrement>::apply(this->m_vec.v, &(base->m_vec.m_quad));
}



namespace hkMxQuaternionf_Implementation
{
template <int I> HK_FORCE_INLINE void setMulQH(__m256* v, const __m256* p, const __m256* q)
{
	setMulQH<I-1>(v, p, q);

	const __m256 pImag = p[I-1];
	const __m256 qImag = q[I-1];
	const __m256 pReal = _mm256_permute_ps(p[I-1], _MM256_PERMUTE(3,3,3,3));
	const __m256 qReal = _mm256_permute_ps(q[I-1], _MM256_PERMUTE(3,3,3,3));

	__m256 vec = hkMxCommon_Implementation::crossH(pImag, qImag);
	vec = _mm256_add_ps(vec, _mm256_mul_ps(pReal, qImag));
	vec = _mm256_add_ps(vec, _mm256_mul_ps(qReal, pImag));

	const __m256 w = _mm256_sub_ps(_mm256_mul_ps(pReal, qReal), hkMxCommon_Implementation::dotProdH<3>(pImag,qImag));
	v[I-1] = _mm256_blend_ps(vec, w, 0x88);
}

template <> HK_FORCE_INLINE void setMulQH<1>(__m256* v, const __m256* p, const __m256* q)
{
	const __m256 pImag = p[0];
	const __m256 qImag = q[0];
	const __m256 pReal = _mm256_permute_ps(p[0], _MM256_PERMUTE(3,3,3,3));
	const __m256 qReal = _mm256_permute_ps(q[0], _MM256_PERMUTE(3,3,3,3));

	__m256 vec = hkMxCommon_Implementation::crossH(pImag, qImag);
	vec = _mm256_add_ps(vec, _mm256_mul_ps(pReal, qImag));
	vec = _mm256_add_ps(vec, _mm256_mul_ps(qReal, pImag));

	const __m256 w = _mm256_sub_ps(_mm256_mul_ps(pReal, qReal), hkMxCommon_Implementation::dotProdH<3>(pImag,qImag));
	v[0] = _mm256_blend_ps(vec, w, 0x88);
}
}
template <int M>
HK_FORCE_INLINE void hkMxQuaternionf<M>::setMulQ(hkMxQuaternionfParameter p, hkMxQuaternionfParameter q)
{
	hkMxQuaternionf_Implementation::setMulQH<((M+1)>>1)>( this->m_vec.v, p.m_vec.v, q.m_vec.v);
}


namespace hkMxQuaternionf_Implementation
{
template <int I> HK_FORCE_INLINE void setMulInverseQH(__m256* v, const __m256* p, const __m256* q)
{
	setMulInverseQH<I-1>(v, p, q);

	const __m256 pImag = p[I-1];
	const __m256 qImag = q[I-1];
	const __m256 pReal = _mm256_permute_ps(p[I-1], _MM256_PERMUTE(3,3,3,3));
	const __m256 qReal = _mm256_permute_ps(q[I-1], _MM256_PERMUTE(3,3,3,3));

	__m256 xyz = hkMxCommon_Implementation::crossH(qImag, pImag);
	xyz = _mm256_sub_ps(xyz, _mm256_mul_ps(pReal, qImag));
	xyz = _mm256_add_ps(xyz, _mm256_mul_ps(qReal, pImag));
	const __m256 w = hkMxCommon_Implementation::dotProdH<4>(pImag,qImag);
	v[I-1] = _mm256_blend_ps(xyz, w, 0x88);
}
template <> HK_FORCE_INLINE void setMulInverseQH<1>(__m256* v, const __m256* p, const __m256* q)
{
	const __m256 pImag = p[0];
	const __m256 qImag = q[0];
	const __m256 pReal = _mm256_permute_ps(p[0], _MM256_PERMUTE(3,3,3,3));
	const __m256 qReal = _mm256_permute_ps(q[0], _MM256_PERMUTE(3,3,3,3));

	__m256 xyz = hkMxCommon_Implementation::crossH(qImag, pImag);
	xyz = _mm256_sub_ps(xyz, _mm256_mul_ps(pReal, qImag));
	xyz = _mm256_add_ps(xyz, _mm256_mul_ps(qReal, pImag));
	const __m256 w = hkMxCommon_Implementation::dotProdH<4>(pImag,qImag);
	v[0] = _mm256_blend_ps(xyz, w, 0x88);
}
}
template <int M>
HK_FORCE_INLINE void hkMxQuaternionf<M>::setMulInverseQ(hkMxQuaternionfParameter p, hkMxQuaternionfParameter q)
{
	hkMxQuaternionf_Implementation::setMulInverseQH<((M+1)>>1)>( this->m_vec.v, p.m_vec.v, q.m_vec.v);
}




namespace hkMxQuaternionf_Implementation
{
template <int I> HK_FORCE_INLINE void setInverseQH(__m256* v, const __m256* p, const __m256& mask)
{
	setInverseQH<I-1>(v, p);
	v[I-1] = _mm256_xor_ps(p[I-1], mask);
}
template <> HK_FORCE_INLINE void setInverseQH<1>(__m256* v, const __m256* p, const __m256& mask)
{
	v[0] = _mm256_xor_ps(p[0], mask);
}
}
template <int M>
HK_FORCE_INLINE void hkMxQuaternionf<M>::setInverse(hkMxQuaternionfParameter p)
{
	static HK_ALIGN32( const hkUint32 mask[8] ) = { 0x80000000, 0x80000000, 0x80000000, 0x00000000, 0x80000000, 0x80000000, 0x80000000, 0x00000000 };
	hkMxQuaternionf_Implementation::setInverseQH<((M+1)>>1)>( this->m_vec.v, p.m_vec.v, *(const __m256*)&mask);
}



template <int M>
template <int I> 
HK_FORCE_INLINE const hkQuaternionf hkMxQuaternionf<M>::getQuaternion() const
{
	HK_MXVECTORff_MX_SUBINDEX_CHECK;
	const int subvector = I>>1;
	const int subvectorsubindex = ((I+1)>>1) - subvector;
	hkQuaternionf q;
	q.m_vec.m_quad = _mm256_extractf128_ps(this->m_vec.v[subvector], subvectorsubindex);
	return q;
}



namespace hkMxQuaternionf_Implementation
{
template <int I, int N, hkUint32 byteAddressIncrement> struct scatterQHR {
HK_FORCE_INLINE static void apply(const __m256* v, hkRotationf* base)
{
	hkQuaternionf q0,q1;
	q0.m_vec.m_quad = _mm256_extractf128_ps(v[N], 0x0);
	q1.m_vec.m_quad = _mm256_extractf128_ps(v[N], 0x1);

	hkRotationf* r0 = hkAddByteOffset(base, (2*N) * byteAddressIncrement);
	hkRotationf* r1 = hkAddByteOffset(base, (2*N+1) * byteAddressIncrement);
	r0->set(q0);	// out of line
	r1->set(q1);	// out of line

	scatterQHR<I-2, N+1, byteAddressIncrement>::apply(v, base);
} };
template <int N, hkUint32 byteAddressIncrement> struct scatterQHR<4, N, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(const __m256* v, hkRotationf* base)
{
	hkQuaternionf q[4];
	q[0].m_vec.m_quad = _mm256_extractf128_ps(v[N], 0x0);
	q[1].m_vec.m_quad = _mm256_extractf128_ps(v[N], 0x1);
	q[2].m_vec.m_quad = _mm256_extractf128_ps(v[N+1], 0x0);
	q[3].m_vec.m_quad = _mm256_extractf128_ps(v[N+1], 0x1);

	hkVector4Util::convert4QuaternionsToRotations( (const hkQuaternionf*)q,  // out of line call
		hkAddByteOffset(base, (2*N+0) * byteAddressIncrement),
		hkAddByteOffset(base, (2*N+1) * byteAddressIncrement),
		hkAddByteOffset(base, (2*N+2) * byteAddressIncrement),
		hkAddByteOffset(base, (2*N+3) * byteAddressIncrement)
		);
} };
template <int N, hkUint32 byteAddressIncrement> struct scatterQHR<2, N, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(const __m256* v, hkRotationf* base)
{
	hkQuaternionf q0,q1;
	q0.m_vec.m_quad = _mm256_extractf128_ps(v[N], 0x0);
	q1.m_vec.m_quad = _mm256_extractf128_ps(v[N], 0x1);

	hkRotationf* r0 = hkAddByteOffset(base, (2*N) * byteAddressIncrement);
	hkRotationf* r1 = hkAddByteOffset(base, (2*N+1) * byteAddressIncrement);
	r0->set(q0);	// out of line
	r1->set(q1);	// out of line
} };
template <int N, hkUint32 byteAddressIncrement> struct scatterQHR<1, N, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(const __m256* v, hkRotationf* base)
{
	hkQuaternionf q;
	q.m_vec.m_quad = _mm256_extractf128_ps(v[N], 0x0);

	hkRotationf* r = hkAddByteOffset(base, (2*N) * byteAddressIncrement);
	r->set(q);	// out of line
} };
}
template <int M>
template <hkUint32 byteAddressIncrement>
HK_FORCE_INLINE void hkMxQuaternionf<M>::convertAndScatter(hkRotationf* HK_RESTRICT base) const
{
	hkMxQuaternionf_Implementation::scatterQHR<M, 0, byteAddressIncrement>::apply(this->m_vec.v, base);
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
