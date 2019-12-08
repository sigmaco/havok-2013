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

#define MXR_ONE_OPERAND(METHOD, OP) \
	namespace hkMxRealf_Implementation { \
	template <int I> HK_FORCE_INLINE void METHOD##H1R(__m256* r, const __m256* r0) { METHOD##H1R<I-1>(r, r0); r[I-1] = OP(r[I-1], r0[I-1]); } \
	template <> HK_FORCE_INLINE void METHOD##H1R<1>(__m256* r, const __m256* r0) { r[0] = OP(r[0], r0[0]); } \
	} \
	template <int M> HK_FORCE_INLINE void hkMxRealf<M>::METHOD(hkMxRealfParameter r0) { hkMxRealf_Implementation::METHOD##H1R<((M+1)>>1)>(m_real.r, r0.m_real.r); }

#define MXR_TWO_OPERANDS(METHOD, OP) \
	namespace hkMxRealf_Implementation { \
	template <int I> HK_FORCE_INLINE void METHOD##HR(__m256* r, const __m256* r0, const __m256* r1) { METHOD##HR<I-1>(r, r0, r1); r[I-1] = OP(r0[I-1], r1[I-1]); } \
	template <> HK_FORCE_INLINE void METHOD##HR<1>(__m256* r, const __m256* r0, const __m256* r1) { r[0] = OP(r0[0], r1[0]); } \
	} \
	template <int M> HK_FORCE_INLINE void hkMxRealf<M>::METHOD(hkMxRealfParameter r0, hkMxRealfParameter r1) { hkMxRealf_Implementation::METHOD##HR<((M+1)>>1)>(m_real.r, r0.m_real.r, r1.m_real.r); }

#define MXR_CMP_MXVECTOR(METHOD, OP) \
	namespace hkMxRealf_Implementation { \
	template <int I> HK_FORCE_INLINE void METHOD##HRC(const __m256* v0, const __m256* v1, __m256* m) { \
	METHOD##HRC<I-1>(v0, v1, m); \
    /*m[I-1] = _mm256_cmp_ps(v0[I-1], v1[I-1], OP);*/ \
	/* workaround VS2010 assembler bug */ \
	const __m256 masklow =  _mm256_cmp_ps(v0[I-1], v1[I-1], OP); \
	const __m256 maskhigh = _mm256_cmp_ps(_mm256_permute2f128_ps(v0[I-1],v0[I-1], _MM256_PERMUTE2(_MM256_A_LOW, _MM256_A_HIGH)), _mm256_permute2f128_ps(v1[I-1],v1[I-1], _MM256_PERMUTE2(_MM256_A_LOW, _MM256_A_HIGH)), OP); \
	m[I-1] = _mm256_permute2f128_ps(masklow,maskhigh, 0x20); } \
	template <> HK_FORCE_INLINE void METHOD##HRC<1>(const __m256* v0, const __m256* v1, __m256* m) { \
	/*m[0] = _mm256_cmp_ps(v0[0], v1[0], OP);*/ \
	/* workaround VS2010 assembler bug */ \
	const __m256 masklow =  _mm256_cmp_ps(v0[0], v1[0], OP); \
	const __m256 maskhigh = _mm256_cmp_ps(_mm256_permute2f128_ps(v0[0],v0[0], _MM256_PERMUTE2(_MM256_A_LOW, _MM256_A_HIGH)), _mm256_permute2f128_ps(v1[0],v1[0], _MM256_PERMUTE2(_MM256_A_LOW, _MM256_A_HIGH)), OP); \
	m[0] = _mm256_permute2f128_ps(masklow,maskhigh, 0x20); } \
	} \
	template <int M> HK_FORCE_INLINE void hkMxRealf<M>::METHOD(hkMxVectorfParameter v, hkMxMaskf<M>& mask) const { hkMxRealf_Implementation::METHOD##HRC<((M+1)>>1)>(m_real.r, v.m_vec.v, mask.m_comp.c); }

#define MXR_CMP_MXREAL(METHOD, OP) \
	namespace hkMxRealf_Implementation { \
	template <int I> HK_FORCE_INLINE void METHOD##HRCR(const __m256* v0, const __m256* v1, __m256* m) { \
	METHOD##HRCR<I-1>(v0, v1, m); \
	/*m[I-1] = _mm256_cmp_ps(v0[I-1], v1[I-1], OP);*/ \
	/* workaround VS2010 assembler bug */ \
	const __m256 masklow =  _mm256_cmp_ps(v0[I-1], v1[I-1], OP); \
	const __m256 maskhigh = _mm256_cmp_ps(_mm256_permute2f128_ps(v0[I-1],v0[I-1], _MM256_PERMUTE2(_MM256_A_LOW, _MM256_A_HIGH)), _mm256_permute2f128_ps(v1[I-1],v1[I-1], _MM256_PERMUTE2(_MM256_A_LOW, _MM256_A_HIGH)), OP); \
	m[I-1] = _mm256_permute2f128_ps(masklow,maskhigh, 0x20); } \
	template <> HK_FORCE_INLINE void METHOD##HRCR<1>(const __m256* v0, const __m256* v1, __m256* m) { \
	/*m[0] = _mm256_cmp_ps(v0[0], v1[0], OP);*/ \
	/* workaround VS2010 assembler bug */ \
	const __m256 masklow =  _mm256_cmp_ps(v0[0], v1[0], OP); \
	const __m256 maskhigh = _mm256_cmp_ps(_mm256_permute2f128_ps(v0[0],v0[0], _MM256_PERMUTE2(_MM256_A_LOW, _MM256_A_HIGH)), _mm256_permute2f128_ps(v1[0],v1[0], _MM256_PERMUTE2(_MM256_A_LOW, _MM256_A_HIGH)), OP); \
	m[0] = _mm256_permute2f128_ps(masklow,maskhigh, 0x20); } \
	} \
	template <int M> HK_FORCE_INLINE void hkMxRealf<M>::METHOD(hkMxRealfParameter v, hkMxMaskf<M>& mask) const { hkMxRealf_Implementation::METHOD##HRCR<((M+1)>>1)>(m_real.r, v.m_real.r, mask.m_comp.c); }

#define MXR_CMP_MXSINGLE(METHOD, OP) \
	namespace hkMxRealf_Implementation { \
	template <int I> HK_FORCE_INLINE void METHOD##HRS(const __m256* v0, const __m256& v1, __m256* m) { \
	METHOD##HRS<I-1>(v0, v1, m); \
	/*m[I-1] = _mm256_cmp_ps(v0[I-1], v1, OP);*/ \
	/* workaround VS2010 assembler bug */ \
	const __m256 masklow =  _mm256_cmp_ps(v0[I-1], v1, OP); \
	const __m256 maskhigh = _mm256_cmp_ps(_mm256_permute2f128_ps(v0[I-1],v0[I-1], _MM256_PERMUTE2(_MM256_A_LOW, _MM256_A_HIGH)), _mm256_permute2f128_ps(v1,v1, _MM256_PERMUTE2(_MM256_A_LOW, _MM256_A_HIGH)), OP); \
	m[I-1] = _mm256_permute2f128_ps(masklow,maskhigh, 0x20); } \
	template <> HK_FORCE_INLINE void METHOD##HRS<1>(const __m256* v0, const __m256& v1, __m256* m) { \
	/*m[0] = _mm256_cmp_ps(v0[0], v1, OP);*/ \
	/* workaround VS2010 assembler bug */ \
	const __m256 masklow =  _mm256_cmp_ps(v0[0], v1, OP); \
	const __m256 maskhigh = _mm256_cmp_ps(_mm256_permute2f128_ps(v0[0],v0[0], _MM256_PERMUTE2(_MM256_A_LOW, _MM256_A_HIGH)), _mm256_permute2f128_ps(v1,v1, _MM256_PERMUTE2(_MM256_A_LOW, _MM256_A_HIGH)), OP); \
	m[0] = _mm256_permute2f128_ps(masklow,maskhigh, 0x20); } \
	} \
	template <int M> HK_FORCE_INLINE void hkMxRealf<M>::METHOD(hkMxSinglefParameter v, hkMxMaskf<M>& mask) const { hkMxRealf_Implementation::METHOD##HRS<((M+1)>>1)>(m_real.r, v.m_single.s, mask.m_comp.c); }



MXR_ONE_OPERAND( add, _mm256_add_ps )
MXR_ONE_OPERAND( sub, _mm256_sub_ps )
MXR_ONE_OPERAND( mul, _mm256_mul_ps )
MXR_ONE_OPERAND( div, _mm256_div_ps )

MXR_TWO_OPERANDS( setAdd, _mm256_add_ps )
MXR_TWO_OPERANDS( setSub, _mm256_sub_ps )
MXR_TWO_OPERANDS( setMul, _mm256_mul_ps )
MXR_TWO_OPERANDS( setDiv, _mm256_div_ps )
MXR_TWO_OPERANDS( setMin, _mm256_min_ps )
MXR_TWO_OPERANDS( setMax, _mm256_max_ps )

MXR_CMP_MXREAL( compareLessThan, _CMP_LT_OQ )
MXR_CMP_MXREAL( compareLessThanEqual, _CMP_LE_OQ )
MXR_CMP_MXREAL( compareGreaterThan, _CMP_GT_OQ )
MXR_CMP_MXREAL( compareGreaterThanEqual, _CMP_GE_OQ )

MXR_CMP_MXVECTOR( compareLessThan, _CMP_LT_OQ )
MXR_CMP_MXVECTOR( compareLessThanEqual, _CMP_LE_OQ )
MXR_CMP_MXVECTOR( compareGreaterThan, _CMP_GT_OQ )
MXR_CMP_MXVECTOR( compareGreaterThanEqual, _CMP_GE_OQ )

MXR_CMP_MXSINGLE( compareLessThan, _CMP_LT_OQ )
MXR_CMP_MXSINGLE( compareLessThanEqual, _CMP_LE_OQ )
MXR_CMP_MXSINGLE( compareGreaterThan, _CMP_GT_OQ )
MXR_CMP_MXSINGLE( compareGreaterThanEqual, _CMP_GE_OQ )



namespace hkMxRealf_Implementation
{
template <int I, int N> struct setDotVHR { HK_FORCE_INLINE static void apply(__m256* r, const __m256* v0, const __m256* v1) 
{ 
	setDotVHR<I-1,N>::apply(r, v0, v1); 
	r[I-1] = hkMxCommon_Implementation::dotProdH<N>(v0[I-1], v1[I-1]); 
} };
template <int N> struct setDotVHR<1,N> { HK_FORCE_INLINE static void apply(__m256* r, const __m256* v0, const __m256* v1) 
{ 
	r[0] = hkMxCommon_Implementation::dotProdH<N>(v0[0], v1[0]); 
} };
}
template <int M> 
template <int N> 
HK_FORCE_INLINE void hkMxRealf<M>::setDot(hkMxVectorfParameter v0, hkMxVectorfParameter v1) 
{ 
	hkMxRealf_Implementation::setDotVHR<((M+1)>>1), N>::apply(m_real.r, v0.m_vec.v, v1.m_vec.v); 
}

namespace hkMxRealf_Implementation
{
template <int I, int N> struct setDotSHR { HK_FORCE_INLINE static void apply(__m256* r, const __m256& r0, const __m256* r1) 
{ 
	setDotSHR<I-1,N>::apply(r, r0, r1); 
	r[I-1] = hkMxCommon_Implementation::dotProdH<N>(r0, r1[I-1]); 
} };
template <int N> struct setDotSHR<1,N> { HK_FORCE_INLINE static void apply(__m256* r, const __m256& r0, const __m256* r1) 
{ 
	r[0] = hkMxCommon_Implementation::dotProdH<N>(r0, r1[0]); 
} };
}
template <int M> 
template <int N> 
HK_FORCE_INLINE void hkMxRealf<M>::setDot(hkMxSinglefParameter r0, hkMxVectorfParameter r1) 
{ 
	hkMxRealf_Implementation::setDotSHR<((M+1)>>1), N>::apply(m_real.r, r0.m_single.s, r1.m_vec.v); 
}

template <int M> 
HK_FORCE_INLINE void hkMxRealf<M>::setDot4xyz1(hkMxVectorfParameter v0, hkMxVectorfParameter v1) 
{ 
	hkMxRealf<M> one; one.setConstant<HK_QUADREAL_1>();
	hkMxVectorf<M> v1w; v1w.setXYZ_W(v1, one);
	hkMxRealf_Implementation::setDotVHR<((M+1)>>1), 4>::apply(m_real.r, v0.m_vec.v, v1w.m_vec.v); 
}

template <int M> 
HK_FORCE_INLINE void hkMxRealf<M>::setDot4xyz1(hkMxSinglefParameter r0, hkMxVectorfParameter r1) 
{ 
	hkMxRealf<M> one; one.setConstant<HK_QUADREAL_1>();
	hkMxVectorf<M> r1w; r1w.setXYZ_W(r1, one);
	hkMxRealf_Implementation::setDotSHR<((M+1)>>1), 4>::apply(m_real.r, r0.m_single.s, r1w.m_vec.v); 
}

#ifndef HK_DISABLE_MATH_CONSTRUCTORS

namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void constructHRS(__m256* r, hkFloat32& v) { constructHRS<I-1>(r, v); r[I-1] = _mm256_broadcast_ss(&v); }
template <> HK_FORCE_INLINE void constructHRS<1>(__m256* r, hkFloat32& v) { r[0] = _mm256_broadcast_ss(&v); }
}
template <int M>
HK_FORCE_INLINE hkMxRealf<M>::hkMxRealf(hkFloat32& v)
{
	hkMxRealf_Implementation::constructHRS<((M+1)>>1)>(m_real.r, v);
}

namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void constructHRSS(__m256* r, hkSimdFloat32Parameter v) { constructHRSS<I-1>(r, v); r[I-1] = _mm256_broadcast_ps(&v.m_real); }
template <> HK_FORCE_INLINE void constructHRSS<1>(__m256* r, hkSimdFloat32Parameter v) { r[0] = _mm256_broadcast_ps(&v.m_real); }
}
template <int M>
HK_FORCE_INLINE hkMxRealf<M>::hkMxRealf(hkSimdFloat32Parameter v)
{
	hkMxRealf_Implementation::constructHRSS<((M+1)>>1)>(m_real.r, v);
}

template <> HK_FORCE_INLINE hkMxRealf<4>::hkMxRealf(hkVector4fParameter v) { const hkFloat32 x = v(0); const hkFloat32 y = v(1); m_real.r[0] = _mm256_setr_ps(x,x,x,x,y,y,y,y); const hkFloat32 z = v(2); const hkFloat32 w = v(3); m_real.r[1] = _mm256_setr_ps(z,z,z,z,w,w,w,w); }
template <> HK_FORCE_INLINE hkMxRealf<3>::hkMxRealf(hkVector4fParameter v) { const hkFloat32 x = v(0); const hkFloat32 y = v(1); m_real.r[0] = _mm256_setr_ps(x,x,x,x,y,y,y,y); const hkFloat32 z = v(2); m_real.r[1] = _mm256_broadcast_ss(&z); }
template <> HK_FORCE_INLINE hkMxRealf<2>::hkMxRealf(hkVector4fParameter v) { const hkFloat32 x = v(0); const hkFloat32 y = v(1); m_real.r[0] = _mm256_setr_ps(x,x,x,x,y,y,y,y); }
template <> HK_FORCE_INLINE hkMxRealf<1>::hkMxRealf(hkVector4fParameter v) { const hkFloat32 x = v(0); m_real.r[0] = _mm256_broadcast_ss(&x); }
template <int M> HK_FORCE_INLINE hkMxRealf<M>::hkMxRealf(hkVector4fParameter v)
{
	HK_MXFLOAT_MX_NOT_IMPLEMENTEDf;
}

#endif

namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void moveHR(__m256* HK_RESTRICT v, const __m256* HK_RESTRICT v0) { moveHR<I-1>(v, v0); v[I-1] = v0[I-1]; }
template <> HK_FORCE_INLINE void moveHR<1>(__m256* HK_RESTRICT v, const __m256* HK_RESTRICT v0) { v[0] = v0[0]; }
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::operator= ( hkMxRealfParameter v )
{
	const int N = (M+1)>>1;
	hkMxRealf_Implementation::moveHR<N>(m_real.r, v.m_real.r);
}


template <> HK_FORCE_INLINE void hkMxRealf<4>::setBroadcast( hkVector4fParameter r ) 
{ 
	const hkFloat32 x = r(0); const hkFloat32 y = r(1); m_real.r[0] = _mm256_setr_ps(x,x,x,x,y,y,y,y); 
	const hkFloat32 z = r(2); const hkFloat32 w = r(3); m_real.r[1] = _mm256_setr_ps(z,z,z,z,w,w,w,w); 
}
template <> HK_FORCE_INLINE void hkMxRealf<3>::setBroadcast( hkVector4fParameter r ) 
{ 
	const hkFloat32 x = r(0); const hkFloat32 y = r(1); m_real.r[0] = _mm256_setr_ps(x,x,x,x,y,y,y,y); 
	const hkFloat32 z = r(2);                        m_real.r[1] = _mm256_broadcast_ss(&z); 
}
template <> HK_FORCE_INLINE void hkMxRealf<2>::setBroadcast( hkVector4fParameter r ) 
{ 
	const hkFloat32 x = r(0); const hkFloat32 y = r(1); m_real.r[0] = _mm256_setr_ps(x,x,x,x,y,y,y,y); 
}
template <> HK_FORCE_INLINE void hkMxRealf<1>::setBroadcast( hkVector4fParameter r ) 
{ 
	const hkFloat32 x = r(0); m_real.r[0] = _mm256_broadcast_ss(&x); 
}
template <int M> HK_FORCE_INLINE void hkMxRealf<M>::setBroadcast( hkVector4fParameter r )
{
	HK_MXFLOAT_MX_NOT_IMPLEMENTEDf;
}

namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void setBCHRS(__m256* v, hkSimdFloat32Parameter v0) { setBCHRS<I-1>(v, v0); v[I-1] = _mm256_broadcast_ps(&v0.m_real); }
template <> HK_FORCE_INLINE void setBCHRS<1>(__m256* v, hkSimdFloat32Parameter v0) { v[0] = _mm256_broadcast_ps(&v0.m_real); }
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::setBroadcast( hkSimdFloat32Parameter r )
{
	hkMxRealf_Implementation::setBCHRS<((M+1)>>1)>(m_real.r, r);
}

namespace hkMxRealf_Implementation
{
template <int I, int N> struct loadHR { HK_FORCE_INLINE static void apply(__m256* v, const hkFloat32* r) 
{ 
	const hkFloat32 r0 = r[N*2]; const hkFloat32 r1 = r[N*2+1]; 
	v[N] = _mm256_setr_ps(r0,r0,r0,r0,r1,r1,r1,r1); 
	loadHR<I-2,N+1>::apply(v, r); 
} };
template <int N> struct loadHR<2,N> { HK_FORCE_INLINE static void apply(__m256* v, const hkFloat32* r) 
{ 
	const hkFloat32 r0 = r[N*2]; const hkFloat32 r1 = r[N*2+1]; 
	v[N] = _mm256_setr_ps(r0,r0,r0,r0,r1,r1,r1,r1); 
} };
template <int N> struct loadHR<1,N> { HK_FORCE_INLINE static void apply(__m256* v, const hkFloat32* r) 
{ 
	v[N] = _mm256_broadcast_ss(r+(N*2)); 
} };
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::load(const hkFloat32* r)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)r) & 0x1f ) == 0, "r must be 32-byte aligned."); 
	hkMxRealf_Implementation::loadHR<M,0>::apply(m_real.r, r);
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::loadNotAligned(const hkFloat32* r)
{
	hkMxRealf_Implementation::loadHR<M,0>::apply(m_real.r, r);
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::loadNotCached(const hkFloat32* r)
{
	hkMxRealf_Implementation::loadHR<M,0>::apply(m_real.r, r);
}

namespace hkMxRealf_Implementation
{
template <int I, int N> struct storeHR { HK_FORCE_INLINE static void apply(const __m256* v, hkFloat32* r) 
{ 
// not supported by VS2010
//	_mm_extractmem_ps(r+(N*2), _mm256_extractf128_ps(v[N], 0x0), 0x0); 
//	_mm_extractmem_ps(r+(N*2)+1, _mm256_extractf128_ps(v[N], 0x1), 0x0); 
	const __m128 m0 = _mm256_extractf128_ps(v[N], 0x0);
	const __m128 m1 = _mm256_extractf128_ps(v[N], 0x1);
	storeHR<I-2,N+1>::apply(v, r); 
	_mm_store_ss(r+(N*2), m0);
	_mm_store_ss(r+(N*2)+1, m1);
} };
template <int N> struct storeHR<2,N> { HK_FORCE_INLINE static void apply(const __m256* v, hkFloat32* r) 
{ 
// not supported by VS2010
//	_mm_extractmem_ps(r+(N*2), _mm256_extractf128_ps(v[N], 0x0), 0x0); 
//	_mm_extractmem_ps(r+(N*2)+1, _mm256_extractf128_ps(v[N], 0x1), 0x0); 
	const __m128 m0 = _mm256_extractf128_ps(v[N], 0x0);
	const __m128 m1 = _mm256_extractf128_ps(v[N], 0x1);
	_mm_store_ss(r+(N*2), m0);
	_mm_store_ss(r+(N*2)+1, m1);
} };
template <int N> struct storeHR<1,N> { HK_FORCE_INLINE static void apply(const __m256* v, hkFloat32* r) 
{ 
// not supported by VS2010
//	_mm_extractmem_ps(r+(N*2), _mm256_extractf128_ps(v[N], 0x0), 0x0); 
	const __m128 m0 = _mm256_extractf128_ps(v[N], 0x0);
	_mm_store_ss(r+(N*2), m0);
} };
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::store(hkFloat32* rOut) const
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)rOut) & 0x1f ) == 0, "rOut must be 32-byte aligned."); 
	hkMxRealf_Implementation::storeHR<M,0>::apply(m_real.r, rOut);
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::storeNotAligned(hkFloat32* rOut) const
{
	hkMxRealf_Implementation::storeHR<M,0>::apply(m_real.r, rOut);
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::storeNotCached(hkFloat32* rOut) const
{
	hkMxRealf_Implementation::storeHR<M,0>::apply(m_real.r, rOut);
}



namespace hkMxRealf_Implementation
{
template <int I, int N, hkUint32 byteAddressIncrement> struct gatherHR {
HK_FORCE_INLINE static void apply(__m256* v, const hkFloat32* HK_RESTRICT base)
{
	const hkFloat32 r0 = *hkAddByteOffsetConst( base, (N*2)*byteAddressIncrement );
	const hkFloat32 r1 = *hkAddByteOffsetConst( base, (N*2+1)*byteAddressIncrement );
	v[N] = _mm256_setr_ps(r0,r0,r0,r0,r1,r1,r1,r1);
	gatherHR<I-2, N+1, byteAddressIncrement>::apply(v, base);
} };
template <int N, hkUint32 byteAddressIncrement> struct gatherHR<2, N, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(__m256* v, const hkFloat32* HK_RESTRICT base)
{
	const hkFloat32 r0 = *hkAddByteOffsetConst( base, (N*2)*byteAddressIncrement );
	const hkFloat32 r1 = *hkAddByteOffsetConst( base, (N*2+1)*byteAddressIncrement );
	v[N] = _mm256_setr_ps(r0,r0,r0,r0,r1,r1,r1,r1);
} };
template <int N, hkUint32 byteAddressIncrement> struct gatherHR<1, N, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(__m256* v, const hkFloat32* HK_RESTRICT base)
{
	v[N] = _mm256_broadcast_ss(hkAddByteOffsetConst( base, (N*2)*byteAddressIncrement ));
} };
}
template <int M>
template <hkUint32 byteAddressIncrement>
HK_FORCE_INLINE void hkMxRealf<M>::gather(const hkFloat32* HK_RESTRICT base)
{
	hkMxRealf_Implementation::gatherHR<M, 0, byteAddressIncrement>::apply(m_real.r, base);
}

namespace hkMxRealf_Implementation
{
template <int I, int N, hkUint32 byteAddressIncrement> struct gatherUintHR {
HK_FORCE_INLINE static void apply(__m256* v, const hkFloat32* HK_RESTRICT base, const hkUint16* indices)
{
	const hkFloat32 r0 = *hkAddByteOffsetConst( base, indices[N*2]*byteAddressIncrement );
	const hkFloat32 r1 = *hkAddByteOffsetConst( base, indices[N*2+1]*byteAddressIncrement );
	v[N] = _mm256_setr_ps(r0,r0,r0,r0,r1,r1,r1,r1);
	gatherUintHR<I-2, N+1, byteAddressIncrement>::apply(v, base, indices);
} };
template <int N, hkUint32 byteAddressIncrement> struct gatherUintHR<2, N, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(__m256* v, const hkFloat32* HK_RESTRICT base, const hkUint16* indices)
{
	const hkFloat32 r0 = *hkAddByteOffsetConst( base, indices[N*2]*byteAddressIncrement );
	const hkFloat32 r1 = *hkAddByteOffsetConst( base, indices[N*2+1]*byteAddressIncrement );
	v[N] = _mm256_setr_ps(r0,r0,r0,r0,r1,r1,r1,r1);
} };
template <int N, hkUint32 byteAddressIncrement> struct gatherUintHR<1, N, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(__m256* v, const hkFloat32* HK_RESTRICT base, const hkUint16* indices)
{
	v[N] = _mm256_broadcast_ss(hkAddByteOffsetConst( base, indices[N*2]*byteAddressIncrement ));
} };
}
template <int M>
template <hkUint32 byteAddressIncrement>
HK_FORCE_INLINE void hkMxRealf<M>::gather(const hkFloat32* HK_RESTRICT base, const hkUint16* indices)
{
	hkMxRealf_Implementation::gatherUintHR<M, 0, byteAddressIncrement>::apply(m_real.r, base, indices);
}

namespace hkMxRealf_Implementation
{
template <int I, int N, hkUint32 byteAddressIncrement> struct gatherIntHR {
HK_FORCE_INLINE static void apply(__m256* v, const hkFloat32* HK_RESTRICT base, const hkInt32* indices)
{
	const hkFloat32 r0 = *hkAddByteOffsetConst( base, indices[N*2]*byteAddressIncrement );
	const hkFloat32 r1 = *hkAddByteOffsetConst( base, indices[N*2+1]*byteAddressIncrement );
	v[N] = _mm256_setr_ps(r0,r0,r0,r0,r1,r1,r1,r1);
	gatherIntHR<I-2, N+1, byteAddressIncrement>::apply(v, base, indices);
} };
template <int N, hkUint32 byteAddressIncrement> struct gatherIntHR<2, N, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(__m256* v, const hkFloat32* HK_RESTRICT base, const hkInt32* indices)
{
	const hkFloat32 r0 = *hkAddByteOffsetConst( base, indices[N*2]*byteAddressIncrement );
	const hkFloat32 r1 = *hkAddByteOffsetConst( base, indices[N*2+1]*byteAddressIncrement );
	v[N] = _mm256_setr_ps(r0,r0,r0,r0,r1,r1,r1,r1);
} };
template <int N, hkUint32 byteAddressIncrement> struct gatherIntHR<1, N, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(__m256* v, const hkFloat32* HK_RESTRICT base, const hkInt32* indices)
{
	v[N] = _mm256_broadcast_ss(hkAddByteOffsetConst( base, indices[N*2]*byteAddressIncrement ));
} };
}
template <int M>
template <hkUint32 byteAddressIncrement>
HK_FORCE_INLINE void hkMxRealf<M>::gather(const hkFloat32* HK_RESTRICT base, const hkInt32* indices)
{
	hkMxRealf_Implementation::gatherIntHR<M, 0, byteAddressIncrement>::apply(m_real.r, base, indices);
}

namespace hkMxRealf_Implementation
{
template <int I, int N, hkUint32 byteOffset> struct gatherWithOffsetHR {
HK_FORCE_INLINE static void apply(__m256* v, const void** base)
{
	const hkFloat32* HK_RESTRICT ptr0 = (const hkFloat32*)hkAddByteOffsetConst(base[N*2], byteOffset); 
	const hkFloat32* HK_RESTRICT ptr1 = (const hkFloat32*)hkAddByteOffsetConst(base[N*2+1], byteOffset); 
	gatherWithOffsetHR<I-2, N+1, byteOffset>::apply(v, base);
	const hkFloat32 r0 = *ptr0;
	const hkFloat32 r1 = *ptr1;
	v[N] = _mm256_setr_ps(r0,r0,r0,r0,r1,r1,r1,r1);
} };
template <int N, hkUint32 byteOffset> struct gatherWithOffsetHR<2, N, byteOffset> {
HK_FORCE_INLINE static void apply(__m256* v, const void** base)
{
	const hkFloat32* HK_RESTRICT ptr0 = (const hkFloat32*)hkAddByteOffsetConst(base[N*2], byteOffset); 
	const hkFloat32* HK_RESTRICT ptr1 = (const hkFloat32*)hkAddByteOffsetConst(base[N*2+1], byteOffset); 
	const hkFloat32 r0 = *ptr0;
	const hkFloat32 r1 = *ptr1;
	v[N] = _mm256_setr_ps(r0,r0,r0,r0,r1,r1,r1,r1);
} };
template <int N, hkUint32 byteOffset> struct gatherWithOffsetHR<1, N, byteOffset> {
HK_FORCE_INLINE static void apply(__m256* v, const void** base)
{
	const hkFloat32* HK_RESTRICT ptr = (const hkFloat32*)hkAddByteOffsetConst(base[N*2], byteOffset); 
	v[N] = _mm256_broadcast_ss(ptr);
} };
}
template <int M>
template <hkUint32 byteOffset> 
HK_FORCE_INLINE void hkMxRealf<M>::gatherWithOffset(const void* base[M])
{
	hkMxRealf_Implementation::gatherWithOffsetHR<M, 0, byteOffset>::apply(m_real.r, base);
}




namespace hkMxRealf_Implementation
{
template <int I, int N, hkUint32 byteAddressIncrement> struct scatterHR {
HK_FORCE_INLINE static void apply(const __m256* v, hkFloat32* base)
{
	hkFloat32* HK_RESTRICT ptr0 = hkAddByteOffset(base, (N*2) * byteAddressIncrement);
	hkFloat32* HK_RESTRICT ptr1 = hkAddByteOffset(base, (N*2+1) * byteAddressIncrement);
// not supported by VS2010
//	_mm_extractmem_ps(ptr0, _mm256_extractf128_ps(v[N], 0x0), 0x0);
//	_mm_extractmem_ps(ptr1, _mm256_extractf128_ps(v[N], 0x1), 0x0);
	const __m128 m0 = _mm256_extractf128_ps(v[N], 0x0);
	const __m128 m1 = _mm256_extractf128_ps(v[N], 0x1);
	scatterHR<I-2, N+1, byteAddressIncrement>::apply(v, base);
	_mm_store_ss(ptr0, m0);
	_mm_store_ss(ptr1, m1);
} };
template <int N, hkUint32 byteAddressIncrement> struct scatterHR<2, N, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(const __m256* v, hkFloat32* base)
{
	hkFloat32* HK_RESTRICT ptr0 = hkAddByteOffset(base, (N*2) * byteAddressIncrement);
	hkFloat32* HK_RESTRICT ptr1 = hkAddByteOffset(base, (N*2+1) * byteAddressIncrement);
// not supported by VS2010
//	_mm_extractmem_ps(ptr0, _mm256_extractf128_ps(v[N], 0x0), 0x0);
//	_mm_extractmem_ps(ptr1, _mm256_extractf128_ps(v[N], 0x1), 0x0);
	const __m128 m0 = _mm256_extractf128_ps(v[N], 0x0);
	const __m128 m1 = _mm256_extractf128_ps(v[N], 0x1);
	_mm_store_ss(ptr0, m0);
	_mm_store_ss(ptr1, m1);
} };
template <int N, hkUint32 byteAddressIncrement> struct scatterHR<1, N, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(const __m256* v, hkFloat32* base)
{
	hkFloat32* HK_RESTRICT ptr = hkAddByteOffset(base, (N*2) * byteAddressIncrement);
// not supported by VS2010
//	_mm_extractmem_ps(ptr, _mm256_extractf128_ps(v[N], 0x0), 0x0);
	const __m128 m0 = _mm256_extractf128_ps(v[N], 0x0);
	_mm_store_ss(ptr, m0);
} };
}
template <int M>
template <hkUint32 byteAddressIncrement>
HK_FORCE_INLINE void hkMxRealf<M>::scatter(hkFloat32* base) const
{
	hkMxRealf_Implementation::scatterHR<M, 0, byteAddressIncrement>::apply(m_real.r, base);
}

namespace hkMxRealf_Implementation
{
template <int I, int N, hkUint32 byteAddressIncrement> struct scatterUintHR {
HK_FORCE_INLINE static void apply(const __m256* v, hkFloat32* base, const hkUint16* indices)
{
	hkFloat32* HK_RESTRICT ptr0 = hkAddByteOffset(base, indices[N*2] * byteAddressIncrement);
	hkFloat32* HK_RESTRICT ptr1 = hkAddByteOffset(base, indices[N*2+1] * byteAddressIncrement);
// not supported by VS2010
//	_mm_extractmem_ps(ptr0, _mm256_extractf128_ps(v[N], 0x0), 0x0);
//	_mm_extractmem_ps(ptr1, _mm256_extractf128_ps(v[N], 0x1), 0x0);
	const __m128 m0 = _mm256_extractf128_ps(v[N], 0x0);
	const __m128 m1 = _mm256_extractf128_ps(v[N], 0x1);
	scatterUintHR<I-2, N+1, byteAddressIncrement>::apply(v, base, indices);
	_mm_store_ss(ptr0, m0);
	_mm_store_ss(ptr1, m1);
} };
template <int N, hkUint32 byteAddressIncrement> struct scatterUintHR<2, N, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(const __m256* v, hkFloat32* base, const hkUint16* indices)
{
	hkFloat32* HK_RESTRICT ptr0 = hkAddByteOffset(base, indices[N*2] * byteAddressIncrement);
	hkFloat32* HK_RESTRICT ptr1 = hkAddByteOffset(base, indices[N*2+1] * byteAddressIncrement);
// not supported by VS2010
//	_mm_extractmem_ps(ptr0, _mm256_extractf128_ps(v[N], 0x0), 0x0);
//	_mm_extractmem_ps(ptr1, _mm256_extractf128_ps(v[N], 0x1), 0x0);
	const __m128 m0 = _mm256_extractf128_ps(v[N], 0x0);
	const __m128 m1 = _mm256_extractf128_ps(v[N], 0x1);
	_mm_store_ss(ptr0, m0);
	_mm_store_ss(ptr1, m1);
} };
template <int N, hkUint32 byteAddressIncrement> struct scatterUintHR<1, N, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(const __m256* v, hkFloat32* base, const hkUint16* indices)
{
	hkFloat32* HK_RESTRICT ptr = hkAddByteOffset(base, indices[N*2] * byteAddressIncrement);
// not supported by VS2010
//	_mm_extractmem_ps(ptr, _mm256_extractf128_ps(v[N], 0x0), 0x0);
	const __m128 m0 = _mm256_extractf128_ps(v[N], 0x0);
	_mm_store_ss(ptr, m0);
} };
}
template <int M>
template <hkUint32 byteAddressIncrement>
HK_FORCE_INLINE void hkMxRealf<M>::scatter(hkFloat32* base, const hkUint16* indices) const
{
	hkMxRealf_Implementation::scatterUintHR<M, 0, byteAddressIncrement>::apply(m_real.r, base, indices);
}

namespace hkMxRealf_Implementation
{
template <int I, int N, hkUint32 byteAddressIncrement> struct scatterIntHR {
HK_FORCE_INLINE static void apply(const __m256* v, hkFloat32* base, const hkInt32* indices)
{
	hkFloat32* HK_RESTRICT ptr0 = hkAddByteOffset(base, indices[N*2] * byteAddressIncrement);
	hkFloat32* HK_RESTRICT ptr1 = hkAddByteOffset(base, indices[N*2+1] * byteAddressIncrement);
// not supported by VS2010
//	_mm_extractmem_ps(ptr0, _mm256_extractf128_ps(v[N], 0x0), 0x0);
//	_mm_extractmem_ps(ptr1, _mm256_extractf128_ps(v[N], 0x1), 0x0);
	const __m128 m0 = _mm256_extractf128_ps(v[N], 0x0);
	const __m128 m1 = _mm256_extractf128_ps(v[N], 0x1);
	scatterIntHR<I-2, N+1, byteAddressIncrement>::apply(v, base, indices);
	_mm_store_ss(ptr0, m0);
	_mm_store_ss(ptr1, m1);
} };
template <int N, hkUint32 byteAddressIncrement> struct scatterIntHR<2, N, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(const __m256* v, hkFloat32* base, const hkInt32* indices)
{
	hkFloat32* HK_RESTRICT ptr0 = hkAddByteOffset(base, indices[N*2] * byteAddressIncrement);
	hkFloat32* HK_RESTRICT ptr1 = hkAddByteOffset(base, indices[N*2+1] * byteAddressIncrement);
// not supported by VS2010
//	_mm_extractmem_ps(ptr0, _mm256_extractf128_ps(v[N], 0x0), 0x0);
//	_mm_extractmem_ps(ptr1, _mm256_extractf128_ps(v[N], 0x1), 0x0);
	const __m128 m0 = _mm256_extractf128_ps(v[N], 0x0);
	const __m128 m1 = _mm256_extractf128_ps(v[N], 0x1);
	_mm_store_ss(ptr0, m0);
	_mm_store_ss(ptr1, m1);
} };
template <int N, hkUint32 byteAddressIncrement> struct scatterIntHR<1, N, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(const __m256* v, hkFloat32* base, const hkInt32* indices)
{
	hkFloat32* HK_RESTRICT ptr = hkAddByteOffset(base, indices[N*2] * byteAddressIncrement);
// not supported by VS2010
//	_mm_extractmem_ps(ptr, _mm256_extractf128_ps(v[N], 0x0), 0x0);
	const __m128 m0 = _mm256_extractf128_ps(v[N], 0x0);
	_mm_store_ss(ptr, m0);
} };
}
template <int M>
template <hkUint32 byteAddressIncrement>
HK_FORCE_INLINE void hkMxRealf<M>::scatter(hkFloat32* base, const hkInt32* indices) const
{
	hkMxRealf_Implementation::scatterIntHR<M, 0, byteAddressIncrement>::apply(m_real.r, base, indices);
}

namespace hkMxRealf_Implementation
{
template <int I, int N, hkUint32 byteOffset> struct scatterWithOffsetHR {
HK_FORCE_INLINE static void apply(const __m256* v, void** base)
{
	hkFloat32* HK_RESTRICT ptr0 = (hkFloat32*)hkAddByteOffset(base[N*2], byteOffset); 
	hkFloat32* HK_RESTRICT ptr1 = (hkFloat32*)hkAddByteOffset(base[N*2+1], byteOffset); 
	const __m128 m0 = _mm256_extractf128_ps(v[N], 0x0);
	const __m128 m1 = _mm256_extractf128_ps(v[N], 0x1);
	scatterWithOffsetHR<I-2, N+1, byteOffset>::apply(v, base);
	_mm_store_ss(ptr0, m0);
	_mm_store_ss(ptr1, m1);
// not supported by VS2010
//	_mm_extractmem_ps(ptr0, _mm256_extractf128_ps(v[N], 0x0), 0x0);
//	_mm_extractmem_ps(ptr1, _mm256_extractf128_ps(v[N], 0x1), 0x0);
} };
template <int N, hkUint32 byteOffset> struct scatterWithOffsetHR<2, N, byteOffset> {
HK_FORCE_INLINE static void apply(const __m256* v, void** base)
{
	hkFloat32* HK_RESTRICT ptr0 = (hkFloat32*)hkAddByteOffset(base[N*2], byteOffset); 
	hkFloat32* HK_RESTRICT ptr1 = (hkFloat32*)hkAddByteOffset(base[N*2+1], byteOffset); 
// not supported by VS2010
//	_mm_extractmem_ps(ptr0, _mm256_extractf128_ps(v[N], 0x0), 0x0);
//	_mm_extractmem_ps(ptr1, _mm256_extractf128_ps(v[N], 0x1), 0x0);
	const __m128 m0 = _mm256_extractf128_ps(v[N], 0x0);
	const __m128 m1 = _mm256_extractf128_ps(v[N], 0x1);
	_mm_store_ss(ptr0, m0);
	_mm_store_ss(ptr1, m1);
} };
template <int N, hkUint32 byteOffset> struct scatterWithOffsetHR<1, N, byteOffset> {
HK_FORCE_INLINE static void apply(const __m256* v, void** base)
{
	hkFloat32* HK_RESTRICT ptr = (hkFloat32*)hkAddByteOffset(base[N*2], byteOffset); 
// not supported by VS2010
//	_mm_extractmem_ps(ptr, _mm256_extractf128_ps(v[N], 0x0), 0x0);
	const __m128 m0 = _mm256_extractf128_ps(v[N], 0x0);
	_mm_store_ss(ptr, m0);
} };
}
template <int M>
template <hkUint32 byteOffset> 
HK_FORCE_INLINE void hkMxRealf<M>::scatterWithOffset(void* base[M]) const 
{
	hkMxRealf_Implementation::scatterWithOffsetHR<M, 0, byteOffset>::apply(m_real.r, base);
}








template <int M>
template <int I>
HK_FORCE_INLINE void hkMxRealf<M>::setReal(hkSimdFloat32Parameter r)
{
	HK_MXVECTORff_MX_SUBINDEX_CHECK;
	const int N = (I+1)>>1;
	const int J = I>>1;
	m_real.r[J] = _mm256_insertf128_ps(m_real.r[J], r.m_real, N-J);
}

template <int M>
template <int I> 
HK_FORCE_INLINE void hkMxRealf<M>::getAsBroadcast(hkVector4f& vOut) const
{
	HK_MXVECTORff_MX_SUBINDEX_CHECK;
	const int N = (I+1)>>1;
	const int J = I>>1;
	vOut.m_quad = _mm256_extractf128_ps(m_real.r[J], N-J);
}

template <int M>
template <int I> 
HK_FORCE_INLINE const hkVector4f hkMxRealf<M>::getAsBroadcast() const
{
	HK_MXVECTORff_MX_SUBINDEX_CHECK;
	hkVector4f h;
	const int N = (I+1)>>1;
	const int J = I>>1;
	h.m_quad = _mm256_extractf128_ps(m_real.r[J], N-J);
	return h;
}

template <int M>
template <int I> 
HK_FORCE_INLINE const hkSimdFloat32 hkMxRealf<M>::getReal() const
{
	HK_MXVECTORff_MX_SUBINDEX_CHECK;
	hkSimdFloat32 h;
	const int N = (I+1)>>1;
	const int J = I>>1;
	h.m_real = _mm256_extractf128_ps(m_real.r[J], N-J);
	return h;
}


namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void setConstHR(__m256* v, const __m256& vC) { setConstHR<I-1>(v,vC); v[I-1] = vC; }
template <> HK_FORCE_INLINE void setConstHR<1>(__m256* v, const __m256& vC) { v[0] = vC; }
}
template <int M>
template<int vectorConstant> 
HK_FORCE_INLINE void hkMxRealf<M>::setConstant()
{
	const __m256 vC = _mm256_broadcast_ps(g_vectorfConstants+vectorConstant);
	hkMxRealf_Implementation::setConstHR<((M+1)>>1)>(m_real.r, vC);
}


namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void div12HR(__m256* v, const __m256* v0) { div12HR<I-1>(v, v0); v[I-1] = _mm256_mul_ps(v[I-1], _mm256_rcp_ps(v0[I-1])); }
template <> HK_FORCE_INLINE void div12HR<1>(__m256* v, const __m256* v0) { v[0] = _mm256_mul_ps(v[0], _mm256_rcp_ps(v0[0])); }
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::div_12BitAccurate(hkMxRealfParameter r)
{
	hkMxRealf_Implementation::div12HR<((M+1)>>1)>(m_real.r, r.m_real.r);
}

namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void div23HR(__m256* v, const __m256* v0) { div23HR<I-1>(v, v0); v[I-1] = _mm256_mul_ps(v[I-1], hkMxCommon_Implementation::reciprocalH(v0[I-1])); }
template <> HK_FORCE_INLINE void div23HR<1>(__m256* v, const __m256* v0) { v[0] = _mm256_mul_ps(v[0], hkMxCommon_Implementation::reciprocalH(v0[0])); }
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::div_23BitAccurate(hkMxRealfParameter r)
{
	hkMxRealf_Implementation::div23HR<((M+1)>>1)>(m_real.r, r.m_real.r);
}

namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void setNegHR(__m256* v, const __m256* v0, const __m256& mask) { setNegHR<I-1>(v, v0, mask); v[I-1] = _mm256_xor_ps(v0[I-1],mask); }
template <> HK_FORCE_INLINE void setNegHR<1>(__m256* v, const __m256* v0, const __m256& mask) { v[0] = _mm256_xor_ps(v0[0],mask); }
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::setNeg(hkMxRealfParameter r)
{
	static HK_ALIGN32( const hkUint32 mask[8] ) = { 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000, 0x80000000 };
	hkMxRealf_Implementation::setNegHR<((M+1)>>1)>(m_real.r, r.m_real.r, *(__m256*)&mask);
}

namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void setReciprocalHR(__m256* v, const __m256* v0, const __m256& one) { setReciprocalHR<I-1>(v, v0, one); v[I-1] = _mm256_div_ps(one, v0[I-1]); }
template <> HK_FORCE_INLINE void setReciprocalHR<1>(__m256* v, const __m256* v0, const __m256& one) { v[0] = _mm256_div_ps(one, v0[0]); }
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::setReciprocal(hkMxRealfParameter r)
{
	const __m256 one = _mm256_set1_ps(1.0f);
	hkMxRealf_Implementation::setReciprocalHR<((M+1)>>1)>(m_real.r, r.m_real.r, one);
}

namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void setReciprocal12HR(__m256* v, const __m256* v0) { setReciprocal12HR<I-1>(v, v0); v[I-1] = _mm256_rcp_ps(v0[I-1]); }
template <> HK_FORCE_INLINE void setReciprocal12HR<1>(__m256* v, const __m256* v0) { v[0] = _mm256_rcp_ps(v0[0]); }
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::setReciprocal_12BitAccurate(hkMxRealfParameter r)
{
	hkMxRealf_Implementation::setReciprocal12HR<((M+1)>>1)>(m_real.r, r.m_real.r);
}

namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void setReciprocal23HR(__m256* v, const __m256* v0) { setReciprocal23HR<I-1>(v, v0); v[I-1] = hkMxCommon_Implementation::reciprocalH(v0[I-1]); }
template <> HK_FORCE_INLINE void setReciprocal23HR<1>(__m256* v, const __m256* v0) { v[0] = hkMxCommon_Implementation::reciprocalH(v0[0]); }
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::setReciprocal_23BitAccurate(hkMxRealfParameter r)
{
	hkMxRealf_Implementation::setReciprocal23HR<((M+1)>>1)>(m_real.r, r.m_real.r);
}

namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void sqrt12HR(__m256* v) 
{ 
	sqrt12HR<I-1>(v); 
	// workaround VS2010 assembler bug
	const __m256 masklow =  _mm256_cmp_ps(v[I-1], _mm256_setzero_ps(), _CMP_EQ_OQ);
	const __m256 maskhigh = _mm256_cmp_ps(_mm256_permute2f128_ps(v[I-1],v[I-1], _MM256_PERMUTE2(_MM256_A_LOW, _MM256_A_HIGH)), _mm256_setzero_ps(), _CMP_EQ_OQ);
	const __m256 equalsZero = _mm256_permute2f128_ps(masklow,maskhigh, 0x20);
	const __m256 e = _mm256_rcp_ps(_mm256_rsqrt_ps(v[I-1]));
	v[I-1] = _mm256_andnot_ps(equalsZero, e);
}
template <> HK_FORCE_INLINE void sqrt12HR<1>(__m256* v) 
{ 
	// workaround VS2010 assembler bug
	const __m256 masklow =  _mm256_cmp_ps(v[0], _mm256_setzero_ps(), _CMP_EQ_OQ);
	const __m256 maskhigh = _mm256_cmp_ps(_mm256_permute2f128_ps(v[0],v[0], _MM256_PERMUTE2(_MM256_A_LOW, _MM256_A_HIGH)), _mm256_setzero_ps(), _CMP_EQ_OQ);
	const __m256 equalsZero = _mm256_permute2f128_ps(masklow,maskhigh, 0x20);
	const __m256 e = _mm256_rcp_ps(_mm256_rsqrt_ps(v[0]));
	v[0] = _mm256_andnot_ps(equalsZero, e);
}
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::sqrt_12BitAccurate()
{
	hkMxRealf_Implementation::sqrt12HR<((M+1)>>1)>(m_real.r);
}

namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void sqrt23HR(__m256* v) 
{ 
	sqrt23HR<I-1>(v); 
	// workaround VS2010 assembler bug
	const __m256 masklow =  _mm256_cmp_ps(v[I-1], _mm256_setzero_ps(), _CMP_EQ_OQ);
	const __m256 maskhigh = _mm256_cmp_ps(_mm256_permute2f128_ps(v[I-1],v[I-1], _MM256_PERMUTE2(_MM256_A_LOW, _MM256_A_HIGH)), _mm256_setzero_ps(), _CMP_EQ_OQ);
	const __m256 equalsZero = _mm256_permute2f128_ps(masklow,maskhigh, 0x20);
	const __m256 e = hkMxCommon_Implementation::reciprocalH(hkMxCommon_Implementation::reciprocalSquareRootH(v[I-1]));
	v[I-1] = _mm256_andnot_ps(equalsZero, e);
}
template <> HK_FORCE_INLINE void sqrt23HR<1>(__m256* v) 
{ 
	// workaround VS2010 assembler bug
	const __m256 masklow =  _mm256_cmp_ps(v[0], _mm256_setzero_ps(), _CMP_EQ_OQ);
	const __m256 maskhigh = _mm256_cmp_ps(_mm256_permute2f128_ps(v[0],v[0], _MM256_PERMUTE2(_MM256_A_LOW, _MM256_A_HIGH)), _mm256_setzero_ps(), _CMP_EQ_OQ);
	const __m256 equalsZero = _mm256_permute2f128_ps(masklow,maskhigh, 0x20);
	const __m256 e = hkMxCommon_Implementation::reciprocalH(hkMxCommon_Implementation::reciprocalSquareRootH(v[0]));
	v[0] = _mm256_andnot_ps(equalsZero, e);
}
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::sqrt_23BitAccurate()
{
	hkMxRealf_Implementation::sqrt23HR<((M+1)>>1)>(m_real.r);
}

namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void sqrtHR(__m256* v) { sqrtHR<I-1>(v); v[I-1] = _mm256_sqrt_ps(v[I-1]); }
template <> HK_FORCE_INLINE void sqrtHR<1>(__m256* v) { v[0] = _mm256_sqrt_ps(v[0]); }
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::sqrt()
{
	hkMxRealf_Implementation::sqrtHR<((M+1)>>1)>(m_real.r);
}



namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void selectRH(__m256* r, const __m256* mask, const __m256* trueValue, const __m256* falseValue)
{
	selectRH<I-1>(r, mask, trueValue, falseValue);
	r[I-1] = _mm256_blendv_ps(falseValue[I-1], trueValue[I-1], mask[I-1]);
}
template <> HK_FORCE_INLINE void selectRH<1>(__m256* r, const __m256* mask, const __m256* trueValue, const __m256* falseValue)
{
	r[0] = _mm256_blendv_ps(falseValue[0], trueValue[0], mask[0]);
}
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::setSelect(hkMxMaskParameterf mask, hkMxRealfParameter trueValue, hkMxRealfParameter falseValue)
{
	hkMxRealf_Implementation::selectRH<((M+1)>>1)>(m_real.r, mask.m_comp.c, trueValue.m_real.r, falseValue.m_real.r);
}



namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void selectRH(__m256* r, const __m256* mask, const __m256& trueValue, const __m256* falseValue)
{
	selectRH<I-1>(r, mask, trueValue, falseValue);
	r[I-1] = _mm256_blendv_ps(falseValue[I-1], trueValue, mask[I-1]);
}
template <> HK_FORCE_INLINE void selectRH<1>(__m256* r, const __m256* mask, const __m256& trueValue, const __m256* falseValue)
{
	r[0] = _mm256_blendv_ps(falseValue[0], trueValue, mask[0]);
}
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::setSelect(hkMxMaskParameterf mask, hkMxSinglefParameter trueValue, hkMxRealfParameter falseValue)
{
	const __m256 tV = _mm256_permute_ps(trueValue.m_single.s, 0x00);
	hkMxRealf_Implementation::selectRH<((M+1)>>1)>(m_real.r, mask.m_comp.c, tV, falseValue.m_real.r);
}



namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void selectRH(__m256* r, const __m256* mask, const __m256* trueValue, const __m256& falseValue)
{
	selectRH<I-1>(r, mask, trueValue, falseValue);
	r[I-1] = _mm256_blendv_ps(falseValue, trueValue[I-1], mask[I-1]);
}
template <> HK_FORCE_INLINE void selectRH<1>(__m256* r, const __m256* mask, const __m256* trueValue, const __m256& falseValue)
{
	r[0] = _mm256_blendv_ps(falseValue, trueValue[0], mask[0]);
}
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::setSelect(hkMxMaskParameterf mask, hkMxRealfParameter trueValue, hkMxSinglefParameter falseValue)
{
	const __m256 fV = _mm256_permute_ps(falseValue.m_single.s, 0x00);
	hkMxRealf_Implementation::selectRH<((M+1)>>1)>(m_real.r, mask.m_comp.c, trueValue.m_real.r, fV);
}


template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::storePacked(hkVector4f& vOut) const
{
	HK_MXFLOAT_MX_NOT_IMPLEMENTEDf;
}

template <>
HK_FORCE_INLINE void hkMxRealf<1>::storePacked(hkVector4f& vOut) const
{
	vOut.m_quad = _mm256_extractf128_ps(m_real.r[0], 0x0);
	HK_ON_DEBUG(HK_M128(vOut.m_quad).m128_u32[1] = 0xffffffff; HK_M128(vOut.m_quad).m128_u32[2] = 0xffffffff; HK_M128(vOut.m_quad).m128_u32[3] = 0xffffffff;)
}

template <>
HK_FORCE_INLINE void hkMxRealf<2>::storePacked(hkVector4f& vOut) const
{
	hkSimdFloat32 a; a.m_real = _mm256_extractf128_ps(m_real.r[0], 0x0);
	hkSimdFloat32 b; b.m_real = _mm256_extractf128_ps(m_real.r[0], 0x1);

	vOut.set(a,b,b,b);
	HK_ON_DEBUG(HK_M128(vOut.m_quad).m128_u32[2] = 0xffffffff; HK_M128(vOut.m_quad).m128_u32[3] = 0xffffffff;)
}

template <>
HK_FORCE_INLINE void hkMxRealf<3>::storePacked(hkVector4f& vOut) const
{
	hkSimdFloat32 a; a.m_real = _mm256_extractf128_ps(m_real.r[0], 0x0);
	hkSimdFloat32 b; b.m_real = _mm256_extractf128_ps(m_real.r[0], 0x1);
	hkSimdFloat32 c; c.m_real = _mm256_extractf128_ps(m_real.r[1], 0x0);

	vOut.set(a,b,c,c);
	HK_ON_DEBUG(HK_M128(vOut.m_quad).m128_u32[3] = 0xffffffff;)
}

template <>
HK_FORCE_INLINE void hkMxRealf<4>::storePacked(hkVector4f& vOut) const
{
	hkSimdFloat32 a; a.m_real = _mm256_extractf128_ps(m_real.r[0], 0x0);
	hkSimdFloat32 b; b.m_real = _mm256_extractf128_ps(m_real.r[0], 0x1);
	hkSimdFloat32 c; c.m_real = _mm256_extractf128_ps(m_real.r[1], 0x0);
	hkSimdFloat32 d; d.m_real = _mm256_extractf128_ps(m_real.r[1], 0x1);

	vOut.set(a,b,c,d);
}



namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void setDiv12HR(__m256* v, const __m256* v0, const __m256* v1) { setDiv12HR<I-1>(v, v0, v1); v[I-1] = _mm256_mul_ps(v0[I-1], _mm256_rcp_ps(v1[I-1])); }
template <> HK_FORCE_INLINE void setDiv12HR<1>(__m256* v, const __m256* v0, const __m256* v1) { v[0] = _mm256_mul_ps(v0[0], _mm256_rcp_ps(v1[0])); }
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::setDiv_12BitAccurate(hkMxRealfParameter v0, hkMxRealfParameter v1)
{
	hkMxRealf_Implementation::setDiv12HR<((M+1)>>1)>(m_real.r, v0.m_real.r, v1.m_real.r);
}

namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void setDiv23HR(__m256* v, const __m256* v0, const __m256* v1) { setDiv23HR<I-1>(v, v0, v1); v[I-1] = _mm256_mul_ps(v0[I-1], hkMxCommon_Implementation::reciprocalH(v1[I-1])); }
template <> HK_FORCE_INLINE void setDiv23HR<1>(__m256* v, const __m256* v0, const __m256* v1) { v[0] = _mm256_mul_ps(v0[0], hkMxCommon_Implementation::reciprocalH(v1[0])); }
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::setDiv_23BitAccurate(hkMxRealfParameter v0, hkMxRealfParameter v1)
{
	hkMxRealf_Implementation::setDiv23HR<((M+1)>>1)>(m_real.r, v0.m_real.r, v1.m_real.r);
}


#undef MXR_ONE_OPERAND
#undef MXR_TWO_OPERANDS
#undef MXR_CMP_MXREAL
#undef MXR_CMP_MXVECTOR
#undef MXR_CMP_MXSINGLE

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
