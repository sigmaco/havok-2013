/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#define MXR_TWO_OPERANDS(METHOD, OP) namespace hkMxRealf_Implementation { template <int I> HK_FORCE_INLINE void OP##HR(hkSimdFloat32* r, const hkSimdFloat32* r0, const hkSimdFloat32* r1) { OP##HR<I-1>(r, r0, r1); r[I-1].OP(r0[I-1], r1[I-1]); } template <> HK_FORCE_INLINE void OP##HR<1>(hkSimdFloat32* r, const hkSimdFloat32* r0, const hkSimdFloat32* r1) { r[0].OP(r0[0], r1[0]); } } template <int M> HK_FORCE_INLINE void hkMxRealf<M>::METHOD(hkMxRealfParameter r0, hkMxRealfParameter r1) { hkMxRealf_Implementation::OP##HR<M>(m_real.r, r0.m_real.r, r1.m_real.r); }
#define MXR_MIXED_OPERANDS(METHOD, OP) namespace hkMxRealf_Implementation { template <int I> HK_FORCE_INLINE void OP##SHR(hkSimdFloat32* r, hkVector4fParameter r0, const hkVector4f* r1) { OP##SHR<I-1>(r, r0, r1); r[I-1] = r0.OP(r1[I-1]); } template <> HK_FORCE_INLINE void OP##SHR<1>(hkSimdFloat32* r, hkVector4fParameter r0, const hkVector4f* r1) { r[0] = r0.OP(r1[0]); } } template <int M> HK_FORCE_INLINE void hkMxRealf<M>::METHOD(hkMxSinglefParameter r0, hkMxVectorfParameter r1) { hkMxRealf_Implementation::OP##SHR<M>(m_real.r, r0.m_single.s, r1.m_vec.v); }
#define MXR_TWO_V_OPERANDS(METHOD, OP) namespace hkMxRealf_Implementation { template <int I> HK_FORCE_INLINE void OP##VHR(hkSimdFloat32* r, const hkVector4f* v0, const hkVector4f* v1) { OP##VHR<I-1>(r, v0, v1); r[I-1] = v0[I-1].OP(v1[I-1]); } template <> HK_FORCE_INLINE void OP##VHR<1>(hkSimdFloat32* r, const hkVector4f* v0, const hkVector4f* v1) { r[0] = v0[0].OP(v1[0]); } } template <int M> HK_FORCE_INLINE void hkMxRealf<M>::METHOD(hkMxVectorfParameter v0, hkMxVectorfParameter v1) { hkMxRealf_Implementation::OP##VHR<M>(m_real.r, v0.m_vec.v, v1.m_vec.v); }



MXR_TWO_OPERANDS( setMin, setMin )
MXR_TWO_OPERANDS( setMax, setMax )

namespace hkMxRealf_Implementation
{
template <int I, int N> struct setDotVHR { HK_FORCE_INLINE static void apply(hkSimdFloat32* r, const hkVector4f* v0, const hkVector4f* v1) { setDotVHR<I-1,N>::apply(r, v0, v1); r[I-1] = v0[I-1].dot<N>(v1[I-1]); } };
template <int N> struct setDotVHR<1,N> { HK_FORCE_INLINE static void apply(hkSimdFloat32* r, const hkVector4f* v0, const hkVector4f* v1) { r[0] = v0[0].dot<N>(v1[0]); } };
}
template <int M> template <int N> HK_FORCE_INLINE void hkMxRealf<M>::setDot(hkMxVectorfParameter v0, hkMxVectorfParameter v1) 
{ 
	hkMxRealf_Implementation::setDotVHR<M,N>::apply(m_real.r, v0.m_vec.v, v1.m_vec.v); 
}

MXR_TWO_V_OPERANDS( setDot4xyz1, dot4xyz1 )


namespace hkMxRealf_Implementation
{
template <int I, int N> struct setDotSHR { HK_FORCE_INLINE static void apply(hkSimdFloat32* r, hkVector4fParameter r0, const hkVector4f* r1) { setDotSHR<I-1,N>::apply(r, r0, r1); r[I-1] = r0.dot<N>(r1[I-1]); } };
template <int N> struct setDotSHR<1,N> { HK_FORCE_INLINE static void apply(hkSimdFloat32* r, hkVector4fParameter r0, const hkVector4f* r1) { r[0] = r0.dot<N>(r1[0]); } };
}
template <int M> template <int N> HK_FORCE_INLINE void hkMxRealf<M>::setDot(hkMxSinglefParameter r0, hkMxVectorfParameter r1) 
{ 
	hkMxRealf_Implementation::setDotSHR<M,N>::apply(m_real.r, r0.m_single.s, r1.m_vec.v); 
}

MXR_MIXED_OPERANDS( setDot4xyz1, dot4xyz1 )



#undef MXR_TWO_OPERANDS
#undef MXR_TWO_V_OPERANDS
#undef MXR_MIXED_OPERANDS

#ifndef HK_DISABLE_MATH_CONSTRUCTORS

namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void constructHRS(hkSimdFloat32* r, hkFloat32& v) { constructHRS<I-1>(r, v); r[I-1].setFromFloat(v); }
template <> HK_FORCE_INLINE void constructHRS<1>(hkSimdFloat32* r, hkFloat32& v) { r[0].setFromFloat(v); }
}
template <int M>
HK_FORCE_INLINE hkMxRealf<M>::hkMxRealf(hkFloat32& v)
{
	hkMxRealf_Implementation::constructHRS<M>(m_real.r, v);
}

namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void constructHRSS(hkSimdFloat32* r, hkSimdFloat32Parameter v) { constructHRSS<I-1>(r, v); r[I-1] = v; }
template <> HK_FORCE_INLINE void constructHRSS<1>(hkSimdFloat32* r, hkSimdFloat32Parameter v) { r[0] = v; }
}
template <int M>
HK_FORCE_INLINE hkMxRealf<M>::hkMxRealf(hkSimdFloat32Parameter v)
{
	hkMxRealf_Implementation::constructHRSS<M>(m_real.r, v);
}

namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void constructHR(hkSimdFloat32* v, hkVector4fParameter v0) { constructHR<I-1>(v, v0); v[I-1] = v0.getComponent<I-1>(); }
template <> HK_FORCE_INLINE void constructHR<1>(hkSimdFloat32* v, hkVector4fParameter v0) { v[0] = v0.getComponent<0>(); }
}
template <int M>
HK_FORCE_INLINE hkMxRealf<M>::hkMxRealf(hkVector4fParameter v)
{
	hkMxRealf_Implementation::constructHR<M>(m_real.r, v); // safe, v.getComponent<> asserts M<4
}

#endif

namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void moveHR(hkSimdFloat32* HK_RESTRICT v, const hkSimdFloat32* HK_RESTRICT v0) { moveHR<I-1>(v, v0); v[I-1] = v0[I-1]; }
template <> HK_FORCE_INLINE void moveHR<1>(hkSimdFloat32* HK_RESTRICT v, const hkSimdFloat32* HK_RESTRICT v0) { v[0] = v0[0]; }
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::operator= ( hkMxRealfParameter v )
{
	hkMxRealf_Implementation::moveHR<M>(m_real.r, v.m_real.r);
}


namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void setBCHR(hkSimdFloat32* v, hkVector4fParameter v0) { setBCHR<I-1>(v, v0); v[I-1] = v0.getComponent<I-1>(); }
template <> HK_FORCE_INLINE void setBCHR<1>(hkSimdFloat32* v, hkVector4fParameter v0) { v[0] = v0.getComponent<0>(); }
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::setBroadcast( hkVector4fParameter r )
{
	hkMxRealf_Implementation::setBCHR<M>(m_real.r, r); // safe, v.getComponent<> asserts M<4
}

namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void setBCHRS(hkSimdFloat32* v, hkSimdFloat32Parameter v0) { setBCHRS<I-1>(v, v0); v[I-1] = v0; }
template <> HK_FORCE_INLINE void setBCHRS<1>(hkSimdFloat32* v, hkSimdFloat32Parameter v0) { v[0] = v0; }
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::setBroadcast( hkSimdFloat32Parameter r )
{
	hkMxRealf_Implementation::setBCHRS<M>(m_real.r, r);
}

namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void loadHR(hkSimdFloat32* v, const hkFloat32* r) { loadHR<I-1>(v, r); v[I-1].load<1>(r + (I-1)); }
template <> HK_FORCE_INLINE void loadHR<1>(hkSimdFloat32* v, const hkFloat32* r) { v[0].load<1>(r); }
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::load(const hkFloat32* r)
{
	hkMxRealf_Implementation::loadHR<M>(m_real.r, r);
}

namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void loadNHR(hkSimdFloat32* v, const hkFloat32* r) { loadNHR<I-1>(v, r); v[I-1].load<1,HK_IO_NATIVE_ALIGNED>(r + (I-1)); }
template <> HK_FORCE_INLINE void loadNHR<1>(hkSimdFloat32* v, const hkFloat32* r) { v[0].load<1,HK_IO_NATIVE_ALIGNED>(r); }
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::loadNotAligned(const hkFloat32* r)
{
	hkMxRealf_Implementation::loadNHR<M>(m_real.r, r);
}

namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void loadCHR(hkSimdFloat32* v, const hkFloat32* r) { loadCHR<I-1>(v, r); v[I-1].load<1,HK_IO_NOT_CACHED>(r + (I-1)); }
template <> HK_FORCE_INLINE void loadCHR<1>(hkSimdFloat32* v, const hkFloat32* r) { v[0].load<1,HK_IO_NOT_CACHED>(r); }
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::loadNotCached(const hkFloat32* r)
{
	hkMxRealf_Implementation::loadCHR<M>(m_real.r, r);
}

namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void storeHR(const hkSimdFloat32* v, hkFloat32* r) { storeHR<I-1>(v, r); v[I-1].store<1>(r + (I-1)); }
template <> HK_FORCE_INLINE void storeHR<1>(const hkSimdFloat32* v, hkFloat32* r) { v[0].store<1>(r); }
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::store(hkFloat32* rOut) const
{
	hkMxRealf_Implementation::storeHR<M>(m_real.r, rOut);
}

namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void storeNHR(const hkSimdFloat32* v, hkFloat32* r) { storeNHR<I-1>(v, r); v[I-1].store<1,HK_IO_NATIVE_ALIGNED>(r + (I-1)); }
template <> HK_FORCE_INLINE void storeNHR<1>(const hkSimdFloat32* v, hkFloat32* r) { v[0].store<1,HK_IO_NATIVE_ALIGNED>(r); }
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::storeNotAligned(hkFloat32* rOut) const
{
	hkMxRealf_Implementation::storeNHR<M>(m_real.r, rOut);
}

namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void storeCHR(const hkSimdFloat32* v, hkFloat32* r) { storeCHR<I-1>(v, r); v[I-1].store<1,HK_IO_NOT_CACHED>(r + (I-1)); }
template <> HK_FORCE_INLINE void storeCHR<1>(const hkSimdFloat32* v, hkFloat32* r) { v[0].store<1,HK_IO_NOT_CACHED>(r); }
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::storeNotCached(hkFloat32* rOut) const
{
	hkMxRealf_Implementation::storeCHR<M>(m_real.r, rOut);
}



namespace hkMxRealf_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct gatherHR {
HK_FORCE_INLINE static void apply(hkSimdFloat32* v, const hkFloat32* HK_RESTRICT base)
{
	gatherHR<I-1, byteAddressIncrement>::apply(v, base);
	v[I-1].setFromFloat( *hkAddByteOffsetConst( base, (I-1)*byteAddressIncrement ) );
} };
template <hkUint32 byteAddressIncrement> struct gatherHR<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(hkSimdFloat32* v, const hkFloat32* HK_RESTRICT base)
{
	v[0].setFromFloat(*base);
} };
}
template <int M>
template <hkUint32 byteAddressIncrement>
HK_FORCE_INLINE void hkMxRealf<M>::gather(const hkFloat32* HK_RESTRICT base)
{
	hkMxRealf_Implementation::gatherHR<M, byteAddressIncrement>::apply(m_real.r, base);
}


namespace hkMxRealf_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct gatherHH {
HK_FORCE_INLINE static void apply(hkSimdFloat32* v, const hkHalf* HK_RESTRICT base)
{
	gatherHH<I-1, byteAddressIncrement>::apply(v, base);
	v[I-1].setFromHalf( *hkAddByteOffsetConst( base, (I-1)*byteAddressIncrement ) );
} };
template <hkUint32 byteAddressIncrement> struct gatherHH<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(hkSimdFloat32* v, const hkHalf* HK_RESTRICT base)
{
	v[0].setFromHalf(*base);
} };
}
template <int M>
template <hkUint32 byteAddressIncrement>
HK_FORCE_INLINE void hkMxRealf<M>::gather(const hkHalf* HK_RESTRICT base)
{
	hkMxRealf_Implementation::gatherHH<M, byteAddressIncrement>::apply(m_real.r, base);
}

namespace hkMxRealf_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct gatherUintHR {
HK_FORCE_INLINE static void apply(hkSimdFloat32* v, const hkFloat32* HK_RESTRICT base, const hkUint16* indices)
{
	gatherUintHR<I-1, byteAddressIncrement>::apply(v, base, indices);
	v[I-1].setFromFloat( *hkAddByteOffsetConst( base, indices[I-1] * byteAddressIncrement ) );
} };
template <hkUint32 byteAddressIncrement> struct gatherUintHR<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(hkSimdFloat32* v, const hkFloat32* HK_RESTRICT base, const hkUint16* indices)
{
	v[0].setFromFloat(*hkAddByteOffsetConst( base, indices[0] * byteAddressIncrement ));
} };
}
template <int M>
template <hkUint32 byteAddressIncrement>
HK_FORCE_INLINE void hkMxRealf<M>::gather(const hkFloat32* HK_RESTRICT base, const hkUint16* indices)
{
	hkMxRealf_Implementation::gatherUintHR<M, byteAddressIncrement>::apply(m_real.r, base, indices);
}

namespace hkMxRealf_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct gatherIntHR {
HK_FORCE_INLINE static void apply(hkSimdFloat32* v, const hkFloat32* HK_RESTRICT base, const hkInt32* indices)
{
	gatherIntHR<I-1, byteAddressIncrement>::apply(v, base, indices);
	v[I-1].setFromFloat( *hkAddByteOffsetConst( base, indices[I-1] * byteAddressIncrement ) );
} };
template <hkUint32 byteAddressIncrement> struct gatherIntHR<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(hkSimdFloat32* v, const hkFloat32* HK_RESTRICT base, const hkInt32* indices)
{
	v[0].setFromFloat( *hkAddByteOffsetConst( base, indices[0] * byteAddressIncrement ));
} };
}
template <int M>
template <hkUint32 byteAddressIncrement>
HK_FORCE_INLINE void hkMxRealf<M>::gather(const hkFloat32* HK_RESTRICT base, const hkInt32* indices)
{
	hkMxRealf_Implementation::gatherIntHR<M, byteAddressIncrement>::apply(m_real.r, base, indices);
}

namespace hkMxRealf_Implementation
{
template <int I, hkUint32 byteOffset> struct gatherWithOffsetHR {
HK_FORCE_INLINE static void apply(hkSimdFloat32* v, const void** base)
{
	const hkFloat32* HK_RESTRICT ptr0 = (const hkFloat32*)hkAddByteOffsetConst(base[I-1], byteOffset); 
	gatherWithOffsetHR<I-1, byteOffset>::apply(v, base);
	v[I-1].setFromFloat( *ptr0 );
} };
template <hkUint32 byteOffset> struct gatherWithOffsetHR<1, byteOffset> {
HK_FORCE_INLINE static void apply(hkSimdFloat32* v, const void** base)
{
	const hkFloat32* HK_RESTRICT ptr = (const hkFloat32*)hkAddByteOffsetConst(base[0], byteOffset); 
	v[0].setFromFloat(*ptr);
} };
}
template <int M>
template <hkUint32 byteOffset> 
HK_FORCE_INLINE void hkMxRealf<M>::gatherWithOffset(const void* base[M])
{
	hkMxRealf_Implementation::gatherWithOffsetHR<M, byteOffset>::apply(m_real.r, base);
}




namespace hkMxRealf_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct scatterHR {
HK_FORCE_INLINE static void apply(const hkSimdFloat32* v, hkFloat32* base)
{
	scatterHR<I-1, byteAddressIncrement>::apply(v, base);
	v[I-1].store<1>(hkAddByteOffset(base, (I-1)*byteAddressIncrement));
} };
template <hkUint32 byteAddressIncrement> struct scatterHR<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(const hkSimdFloat32* v, hkFloat32* base)
{
	v[0].store<1>(base);
} };
}
template <int M>
template <hkUint32 byteAddressIncrement>
HK_FORCE_INLINE void hkMxRealf<M>::scatter(hkFloat32* base) const
{
	hkMxRealf_Implementation::scatterHR<M, byteAddressIncrement>::apply(m_real.r, base);
}

namespace hkMxRealf_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct scatterUintHR {
HK_FORCE_INLINE static void apply(const hkSimdFloat32* v, hkFloat32* base, const hkUint16* indices)
{
	hkFloat32* HK_RESTRICT ptr = hkAddByteOffset(base, indices[I-1] * byteAddressIncrement);
	scatterUintHR<I-1, byteAddressIncrement>::apply(v, base, indices);
	v[I-1].store<1>(ptr);
} };
template <hkUint32 byteAddressIncrement> struct scatterUintHR<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(const hkSimdFloat32* v, hkFloat32* base, const hkUint16* indices)
{
	hkFloat32* HK_RESTRICT ptr = hkAddByteOffset(base, indices[0] * byteAddressIncrement);
	v[0].store<1>(ptr);
} };
}
template <int M>
template <hkUint32 byteAddressIncrement>
HK_FORCE_INLINE void hkMxRealf<M>::scatter(hkFloat32* base, const hkUint16* indices) const
{
	hkMxRealf_Implementation::scatterUintHR<M, byteAddressIncrement>::apply(m_real.r, base, indices);
}

namespace hkMxRealf_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct scatterIntHR {
HK_FORCE_INLINE static void apply(const hkSimdFloat32* v, hkFloat32* base, const hkInt32* indices)
{
	hkFloat32* HK_RESTRICT ptr = hkAddByteOffset(base, indices[I-1] * byteAddressIncrement);
	scatterIntHR<I-1, byteAddressIncrement>::apply(v, base, indices);
	v[I-1].store<1>(ptr);
} };
template <hkUint32 byteAddressIncrement> struct scatterIntHR<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(const hkSimdFloat32* v, hkFloat32* base, const hkInt32* indices)
{
	hkFloat32* HK_RESTRICT ptr = hkAddByteOffset(base, indices[0] * byteAddressIncrement);
	v[0].store<1>(ptr);
} };
}
template <int M>
template <hkUint32 byteAddressIncrement>
HK_FORCE_INLINE void hkMxRealf<M>::scatter(hkFloat32* base, const hkInt32* indices) const
{
	hkMxRealf_Implementation::scatterIntHR<M, byteAddressIncrement>::apply(m_real.r, base, indices);
}

namespace hkMxRealf_Implementation
{
template <int I, hkUint32 byteOffset> struct scatterWithOffsetHR {
HK_FORCE_INLINE static void apply(const hkSimdFloat32* v, void** base)
{
	hkFloat32* HK_RESTRICT ptr0 = (hkFloat32*)hkAddByteOffset(base[I-1], byteOffset); 
	scatterWithOffsetHR<I-1, byteOffset>::apply(v, base);
	v[I-1].store<1>(ptr0);
} };
template <hkUint32 byteOffset> struct scatterWithOffsetHR<1, byteOffset> {
HK_FORCE_INLINE static void apply(const hkSimdFloat32* v, void** base)
{
	hkFloat32* HK_RESTRICT ptr0 = (hkFloat32*)hkAddByteOffset(base[0], byteOffset); 
	v[0].store<1>(ptr0);
} };
}
template <int M>
template <hkUint32 byteOffset> 
HK_FORCE_INLINE void hkMxRealf<M>::scatterWithOffset(void* base[M]) const 
{
	hkMxRealf_Implementation::scatterWithOffsetHR<M, byteOffset>::apply(m_real.r, base);
}








template <int M>
template <int I>
HK_FORCE_INLINE void hkMxRealf<M>::setReal(hkSimdFloat32Parameter r)
{
	HK_MXVECTORf_MX_SUBINDEX_CHECK;
	m_real.r[I] = r;
}

template <int M>
template <int I> 
HK_FORCE_INLINE void hkMxRealf<M>::getAsBroadcast(hkVector4f& vOut) const
{
	HK_MXVECTORf_MX_SUBINDEX_CHECK;
	vOut.setAll(m_real.r[I]);
}

template <int M>
template <int I> 
HK_FORCE_INLINE const hkVector4f hkMxRealf<M>::getAsBroadcast() const
{
	HK_MXVECTORf_MX_SUBINDEX_CHECK;
	hkVector4f h; h.setAll(m_real.r[I]);
	return h;
}

template <int M>
template <int I> 
HK_FORCE_INLINE const hkSimdFloat32 hkMxRealf<M>::getReal() const
{
	HK_MXVECTORf_MX_SUBINDEX_CHECK;
	return m_real.r[I];
}


namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void setConstHR(hkSimdFloat32* v, hkSimdFloat32Parameter vC) { setConstHR<I-1>(v,vC); v[I-1] = vC; }
template <> HK_FORCE_INLINE void setConstHR<1>(hkSimdFloat32* v, hkSimdFloat32Parameter vC) { v[0] = vC; }
}
template <int M>
template<int vectorConstant> 
HK_FORCE_INLINE void hkMxRealf<M>::setConstant()
{
	const hkSimdFloat32 vC = hkSimdFloat32::getConstant<vectorConstant>();
	hkMxRealf_Implementation::setConstHR<M>(m_real.r, vC);
}


namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void addHR(hkSimdFloat32* v, const hkSimdFloat32* v0) { addHR<I-1>(v, v0); v[I-1] = v[I-1] + v0[I-1]; }
template <> HK_FORCE_INLINE void addHR<1>(hkSimdFloat32* v, const hkSimdFloat32* v0) { v[0] = v[0] + v0[0]; }
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::add(hkMxRealfParameter r)
{
	hkMxRealf_Implementation::addHR<M>(m_real.r, r.m_real.r);
}

namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void subHR(hkSimdFloat32* v, const hkSimdFloat32* v0) { subHR<I-1>(v, v0); v[I-1] = v[I-1] - v0[I-1]; }
template <> HK_FORCE_INLINE void subHR<1>(hkSimdFloat32* v, const hkSimdFloat32* v0) { v[0] = v[0] - v0[0]; }
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::sub(hkMxRealfParameter r)
{
	hkMxRealf_Implementation::subHR<M>(m_real.r, r.m_real.r);
}

namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void mulHR(hkSimdFloat32* v, const hkSimdFloat32* v0) { mulHR<I-1>(v, v0); v[I-1] = v[I-1] * v0[I-1]; }
template <> HK_FORCE_INLINE void mulHR<1>(hkSimdFloat32* v, const hkSimdFloat32* v0) { v[0] = v[0] * v0[0]; }
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::mul(hkMxRealfParameter r)
{
	hkMxRealf_Implementation::mulHR<M>(m_real.r, r.m_real.r);
}

namespace hkMxRealf_Implementation
{
template <int I, hkMathAccuracyMode A, hkMathDivByZeroMode D> struct divHR { HK_FORCE_INLINE static void apply(hkSimdFloat32* v, const hkSimdFloat32* v0) { divHR<I-1,A,D>::apply(v, v0); v[I-1].div<A,D>(v0[I-1]); } };
template <hkMathAccuracyMode A, hkMathDivByZeroMode D> struct divHR<1,A,D> { HK_FORCE_INLINE static void apply(hkSimdFloat32* v, const hkSimdFloat32* v0) { v[0].div<A,D>(v0[0]); } };
}
template <int M>
template <hkMathAccuracyMode A, hkMathDivByZeroMode D>
HK_FORCE_INLINE void hkMxRealf<M>::div(hkMxRealfParameter r)
{
	hkMxRealf_Implementation::divHR<M,A,D>::apply(m_real.r, r.m_real.r);
}

template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::div(hkMxRealfParameter r)
{
	hkMxRealf_Implementation::divHR<M,HK_ACC_23_BIT,HK_DIV_IGNORE>::apply(m_real.r, r.m_real.r);
}



namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void setNegHR(hkSimdFloat32* v, const hkSimdFloat32* v0) { setNegHR<I-1>(v, v0); v[I-1] = -v0[I-1]; }
template <> HK_FORCE_INLINE void setNegHR<1>(hkSimdFloat32* v, const hkSimdFloat32* v0) { v[0] = -v0[0]; }
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::setNeg(hkMxRealfParameter r)
{
	hkMxRealf_Implementation::setNegHR<M>(m_real.r, r.m_real.r);
}

namespace hkMxRealf_Implementation
{
	template <int I, hkMathAccuracyMode A, hkMathDivByZeroMode D> struct setReciprocalHR { HK_FORCE_INLINE static void apply(hkSimdFloat32* v, const hkSimdFloat32* v0) { setReciprocalHR<I-1,A,D>::apply(v, v0); v[I-1].setReciprocal<A,D>(v0[I-1]); } };
	template <hkMathAccuracyMode A, hkMathDivByZeroMode D> struct setReciprocalHR<1,A,D> { HK_FORCE_INLINE static void apply(hkSimdFloat32* v, const hkSimdFloat32* v0) { v[0].setReciprocal<A,D>(v0[0]); } };

	template <int I, hkMathAccuracyMode A, hkMathNegSqrtMode D> struct setSqrtInverseHR { HK_FORCE_INLINE static void apply(hkSimdFloat32* v, const hkSimdFloat32* v0) { setSqrtInverseHR<I-1,A,D>::apply(v, v0); v[I-1] = v0[I-1].sqrtInverse<A,D>(); } };
	template <hkMathAccuracyMode A, hkMathNegSqrtMode D> struct setSqrtInverseHR<1,A,D> { HK_FORCE_INLINE static void apply(hkSimdFloat32* v, const hkSimdFloat32* v0) { v[0] = v0[0].sqrtInverse<A,D>(); } };
}
template <int M>
template <hkMathAccuracyMode A, hkMathDivByZeroMode D> 
HK_FORCE_INLINE void hkMxRealf<M>::setReciprocal(hkMxRealfParameter r)
{
	hkMxRealf_Implementation::setReciprocalHR<M,A,D>::apply(m_real.r, r.m_real.r);
}

template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::setReciprocal(hkMxRealfParameter r)
{
	hkMxRealf_Implementation::setReciprocalHR<M,HK_ACC_23_BIT,HK_DIV_IGNORE>::apply(m_real.r, r.m_real.r);
}

template <int M>
template <hkMathAccuracyMode A, hkMathNegSqrtMode D> 
HK_FORCE_INLINE void hkMxRealf<M>::setSqrtInverse(hkMxRealfParameter r)
{
	hkMxRealf_Implementation::setSqrtInverseHR<M,A,D>::apply(m_real.r, r.m_real.r);
}

namespace hkMxRealf_Implementation
{
template <int I, hkMathAccuracyMode A, hkMathNegSqrtMode S> struct sqrtHR { HK_FORCE_INLINE static void apply(hkSimdFloat32* v) { sqrtHR<I-1,A,S>::apply(v); v[I-1] = v[I-1].sqrt<A,S>(); } };
template <hkMathAccuracyMode A, hkMathNegSqrtMode S> struct sqrtHR<1,A,S> { HK_FORCE_INLINE static void apply(hkSimdFloat32* v) { v[0] = v[0].sqrt<A,S>(); } };
}
template <int M>
template <hkMathAccuracyMode A, hkMathNegSqrtMode S> 
HK_FORCE_INLINE void hkMxRealf<M>::sqrt()
{
	hkMxRealf_Implementation::sqrtHR<M,A,S>::apply(m_real.r);
}

template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::sqrt()
{
	hkMxRealf_Implementation::sqrtHR<M,HK_ACC_23_BIT,HK_SQRT_SET_ZERO>::apply(m_real.r);
}



namespace hkMxRealf_Implementation
{
template <int I>
HK_FORCE_INLINE void selectRH(hkSimdFloat32* r, const hkVector4fComparison* mask, const hkSimdFloat32* trueValue, const hkSimdFloat32* falseValue)
{
	selectRH<I-1>(r, mask, trueValue, falseValue);
	r[I-1].setSelect(mask[I-1], trueValue[I-1], falseValue[I-1]);
}

template <>
HK_FORCE_INLINE void selectRH<1>(hkSimdFloat32* r, const hkVector4fComparison* mask, const hkSimdFloat32* trueValue, const hkSimdFloat32* falseValue)
{
	r[0].setSelect(mask[0], trueValue[0], falseValue[0]);
}
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::setSelect(hkMxMaskParameterf mask, hkMxRealfParameter trueValue, hkMxRealfParameter falseValue)
{
	hkMxRealf_Implementation::selectRH<M>(m_real.r, mask.m_comp.c, trueValue.m_real.r, falseValue.m_real.r);
}



namespace hkMxRealf_Implementation
{
template <int I>
HK_FORCE_INLINE void selectRH(hkSimdFloat32* r, const hkVector4fComparison* mask, hkSimdFloat32Parameter trueValue, const hkSimdFloat32* falseValue)
{
	selectRH<I-1>(r, mask, trueValue, falseValue);
	r[I-1].setSelect(mask[I-1], trueValue, falseValue[I-1]);
}

template <>
HK_FORCE_INLINE void selectRH<1>(hkSimdFloat32* r, const hkVector4fComparison* mask, hkSimdFloat32Parameter trueValue, const hkSimdFloat32* falseValue)
{
	r[0].setSelect(mask[0], trueValue, falseValue[0]);
}
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::setSelect(hkMxMaskParameterf mask, hkMxSinglefParameter trueValue, hkMxRealfParameter falseValue)
{
	hkMxRealf_Implementation::selectRH<M>(m_real.r, mask.m_comp.c, trueValue.m_single.s.template getComponent<0>(), falseValue.m_real.r);
}



namespace hkMxRealf_Implementation
{
template <int I>
HK_FORCE_INLINE void selectRH(hkSimdFloat32* r, const hkVector4fComparison* mask, const hkSimdFloat32* trueValue, hkSimdFloat32Parameter falseValue)
{
	selectRH<I-1>(r, mask, trueValue, falseValue);
	r[I-1].setSelect(mask[I-1], trueValue[I-1], falseValue);
}

template <>
HK_FORCE_INLINE void selectRH<1>(hkSimdFloat32* r, const hkVector4fComparison* mask, const hkSimdFloat32* trueValue, hkSimdFloat32Parameter falseValue)
{
	r[0].setSelect(mask[0], trueValue[0], falseValue);
}
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::setSelect(hkMxMaskParameterf mask, hkMxRealfParameter trueValue, hkMxSinglefParameter falseValue)
{
	hkMxRealf_Implementation::selectRH<M>(m_real.r, mask.m_comp.c, trueValue.m_real.r, falseValue.m_single.s.template getComponent<0>());
}

template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::zeroIfTrue(hkMxMaskParameterf mask)
{
	hkMxRealf<M> zero; zero.setConstant<HK_QUADREAL_0>( );
	setSelect(mask, zero, *this);
}

template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::zeroIfFalse(hkMxMaskParameterf mask)
{
	hkMxRealf<M> zero; zero.setConstant<HK_QUADREAL_0>( );
	setSelect(mask, *this, zero);
}

namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void compareLessThanHR(const hkSimdFloat32* v0, const hkVector4f* v1, hkVector4fComparison* m) { hkVector4f v; v.setAll(v0[I-1]); compareLessThanHR<I-1>(v0, v1, m); m[I-1] = v.less(v1[I-1]); }
template <> HK_FORCE_INLINE void compareLessThanHR<1>(const hkSimdFloat32* v0, const hkVector4f* v1, hkVector4fComparison* m) { hkVector4f v; v.setAll(v0[0]); m[0] = v.less(v1[0]); }
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::less(hkMxVectorfParameter v, hkMxMaskf<M>& mask) const
{
	hkMxRealf_Implementation::compareLessThanHR<M>(m_real.r, v.m_vec.v, mask.m_comp.c);
}

namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void compareLessThanEqualHR(const hkSimdFloat32* v0, const hkVector4f* v1, hkVector4fComparison* m) { hkVector4f v; v.setAll(v0[I-1]); compareLessThanEqualHR<I-1>(v0, v1, m); m[I-1] = v.lessEqual(v1[I-1]); }
template <> HK_FORCE_INLINE void compareLessThanEqualHR<1>(const hkSimdFloat32* v0, const hkVector4f* v1, hkVector4fComparison* m) { hkVector4f v; v.setAll(v0[0]); m[0] = v.lessEqual(v1[0]); }
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::lessEqual(hkMxVectorfParameter v, hkMxMaskf<M>& mask) const
{
	hkMxRealf_Implementation::compareLessThanEqualHR<M>(m_real.r, v.m_vec.v, mask.m_comp.c);
}

namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void compareGreaterThanHR(const hkSimdFloat32* v0, const hkVector4f* v1, hkVector4fComparison* m) { hkVector4f v; v.setAll(v0[I-1]); compareGreaterThanHR<I-1>(v0, v1, m); m[I-1] = v.greater(v1[I-1]); }
template <> HK_FORCE_INLINE void compareGreaterThanHR<1>(const hkSimdFloat32* v0, const hkVector4f* v1, hkVector4fComparison* m) { hkVector4f v; v.setAll(v0[0]); m[0] = v.greater(v1[0]); }
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::greater(hkMxVectorfParameter v, hkMxMaskf<M>& mask) const
{
	hkMxRealf_Implementation::compareGreaterThanHR<M>(m_real.r, v.m_vec.v, mask.m_comp.c);
}

namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void compareGreaterThanEqualHR(const hkSimdFloat32* v0, const hkVector4f* v1, hkVector4fComparison* m) { hkVector4f v; v.setAll(v0[I-1]); compareGreaterThanEqualHR<I-1>(v0, v1, m); m[I-1] = v.greaterEqual(v1[I-1]); }
template <> HK_FORCE_INLINE void compareGreaterThanEqualHR<1>(const hkSimdFloat32* v0, const hkVector4f* v1, hkVector4fComparison* m) { hkVector4f v; v.setAll(v0[0]); m[0] = v.greaterEqual(v1[0]); }
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::greaterEqual(hkMxVectorfParameter v, hkMxMaskf<M>& mask) const
{
	hkMxRealf_Implementation::compareGreaterThanEqualHR<M>(m_real.r, v.m_vec.v, mask.m_comp.c);
}


namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void compareLessThanHRS(const hkSimdFloat32* v0, hkVector4fParameter v1, hkVector4fComparison* m) { hkVector4f v; v.setAll(v0[I-1]); compareLessThanHRS<I-1>(v0, v1, m); m[I-1] = v.less(v1); }
template <> HK_FORCE_INLINE void compareLessThanHRS<1>(const hkSimdFloat32* v0, hkVector4fParameter v1, hkVector4fComparison* m) { hkVector4f v; v.setAll(v0[0]); m[0] = v.less(v1); }
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::less(hkMxSinglefParameter v, hkMxMaskf<M>& mask) const
{
	hkMxRealf_Implementation::compareLessThanHRS<M>(m_real.r, v.m_single.s, mask.m_comp.c);
}

namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void compareLessThanEqualHRS(const hkSimdFloat32* v0, hkVector4fParameter v1, hkVector4fComparison* m) { hkVector4f v; v.setAll(v0[I-1]); compareLessThanEqualHRS<I-1>(v0, v1, m); m[I-1] = v.lessEqual(v1); }
template <> HK_FORCE_INLINE void compareLessThanEqualHRS<1>(const hkSimdFloat32* v0, hkVector4fParameter v1, hkVector4fComparison* m) { hkVector4f v; v.setAll(v0[0]); m[0] = v.lessEqual(v1); }
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::lessEqual(hkMxSinglefParameter v, hkMxMaskf<M>& mask) const
{
	hkMxRealf_Implementation::compareLessThanEqualHRS<M>(m_real.r, v.m_single.s, mask.m_comp.c);
}

namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void compareGreaterThanHRS(const hkSimdFloat32* v0, hkVector4fParameter v1, hkVector4fComparison* m) { hkVector4f v; v.setAll(v0[I-1]); compareGreaterThanHRS<I-1>(v0, v1, m); m[I-1] = v.greater(v1); }
template <> HK_FORCE_INLINE void compareGreaterThanHRS<1>(const hkSimdFloat32* v0, hkVector4fParameter v1, hkVector4fComparison* m) { hkVector4f v; v.setAll(v0[0]); m[0] = v.greater(v1); }
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::greater(hkMxSinglefParameter v, hkMxMaskf<M>& mask) const
{
	hkMxRealf_Implementation::compareGreaterThanHRS<M>(m_real.r, v.m_single.s, mask.m_comp.c);
}

namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void compareGreaterThanEqualHRS(const hkSimdFloat32* v0, hkVector4fParameter v1, hkVector4fComparison* m) { hkVector4f v; v.setAll(v0[I-1]); compareGreaterThanEqualHRS<I-1>(v0, v1, m); m[I-1] = v.greaterEqual(v1); }
template <> HK_FORCE_INLINE void compareGreaterThanEqualHRS<1>(const hkSimdFloat32* v0, hkVector4fParameter v1, hkVector4fComparison* m) { hkVector4f v; v.setAll(v0[0]); m[0] = v.greaterEqual(v1); }
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::greaterEqual(hkMxSinglefParameter v, hkMxMaskf<M>& mask) const
{
	hkMxRealf_Implementation::compareGreaterThanEqualHRS<M>(m_real.r, v.m_single.s, mask.m_comp.c);
}


namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void compareLessThanHR(const hkSimdFloat32* v0, const hkSimdFloat32* v1, hkVector4fComparison* m) { compareLessThanHR<I-1>(v0, v1, m); m[I-1] = v0[I-1].less(v1[I-1]); }
template <> HK_FORCE_INLINE void compareLessThanHR<1>(const hkSimdFloat32* v0, const hkSimdFloat32* v1, hkVector4fComparison* m) { m[0] = v0[0].less(v1[0]); }
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::less(hkMxRealfParameter v, hkMxMaskf<M>& mask) const
{
	hkMxRealf_Implementation::compareLessThanHR<M>(m_real.r, v.m_real.r, mask.m_comp.c);
}

namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void compareLessThanEqualHR(const hkSimdFloat32* v0, const hkSimdFloat32* v1, hkVector4fComparison* m) { compareLessThanEqualHR<I-1>(v0, v1, m); m[I-1] = v0[I-1].lessEqual(v1[I-1]); }
template <> HK_FORCE_INLINE void compareLessThanEqualHR<1>(const hkSimdFloat32* v0, const hkSimdFloat32* v1, hkVector4fComparison* m) { m[0] = v0[0].lessEqual(v1[0]); }
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::lessEqual(hkMxRealfParameter v, hkMxMaskf<M>& mask) const
{
	hkMxRealf_Implementation::compareLessThanEqualHR<M>(m_real.r, v.m_real.r, mask.m_comp.c);
}

namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void compareGreaterThanHR(const hkSimdFloat32* v0, const hkSimdFloat32* v1, hkVector4fComparison* m) { compareGreaterThanHR<I-1>(v0, v1, m); m[I-1] = v0[I-1].greater(v1[I-1]); }
template <> HK_FORCE_INLINE void compareGreaterThanHR<1>(const hkSimdFloat32* v0, const hkSimdFloat32* v1, hkVector4fComparison* m) { m[0] = v0[0].greater(v1[0]); }
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::greater(hkMxRealfParameter v, hkMxMaskf<M>& mask) const
{
	hkMxRealf_Implementation::compareGreaterThanHR<M>(m_real.r, v.m_real.r, mask.m_comp.c);
}

namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void compareGreaterThanEqualHR(const hkSimdFloat32* v0, const hkSimdFloat32* v1, hkVector4fComparison* m) { compareGreaterThanEqualHR<I-1>(v0, v1, m); m[I-1] = v0[I-1].greaterEqual(v1[I-1]); }
template <> HK_FORCE_INLINE void compareGreaterThanEqualHR<1>(const hkSimdFloat32* v0, const hkSimdFloat32* v1, hkVector4fComparison* m) { m[0] = v0[0].greaterEqual(v1[0]); }
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::greaterEqual(hkMxRealfParameter v, hkMxMaskf<M>& mask) const
{
	hkMxRealf_Implementation::compareGreaterThanEqualHR<M>(m_real.r, v.m_real.r, mask.m_comp.c);
}


template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::storePacked(hkVector4f& vOut) const
{
	HK_MXFLOAT_MX_NOT_IMPLEMENTEDf;
}

template <>
HK_FORCE_INLINE void hkMxRealf<1>::storePacked(hkVector4f& vOut) const
{
	vOut.setComponent<0>(m_real.r[0]);
	//HK_ON_DEBUG(HK_M128(vOut.m_quad).m128_u32[1] = 0xffffffff; HK_M128(vOut.m_quad).m128_u32[2] = 0xffffffff; HK_M128(vOut.m_quad).m128_u32[3] = 0xffffffff;)
}

template <>
HK_FORCE_INLINE void hkMxRealf<2>::storePacked(hkVector4f& vOut) const
{
	vOut.set(m_real.r[0], m_real.r[1], m_real.r[1], m_real.r[1]);
	//HK_ON_DEBUG(HK_M128(vOut.m_quad).m128_u32[2] = 0xffffffff; HK_M128(vOut.m_quad).m128_u32[3] = 0xffffffff;)
}

template <>
HK_FORCE_INLINE void hkMxRealf<3>::storePacked(hkVector4f& vOut) const
{
	vOut.set(m_real.r[0], m_real.r[1], m_real.r[2], m_real.r[2]);
	//HK_ON_DEBUG(HK_M128(vOut.m_quad).m128_u32[3] = 0xffffffff;)
}

template <>
HK_FORCE_INLINE void hkMxRealf<4>::storePacked(hkVector4f& vOut) const
{
	vOut.set(m_real.r[0], m_real.r[1], m_real.r[2], m_real.r[3]);
}




namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void setAddHR(hkSimdFloat32* v, const hkSimdFloat32* v0, const hkSimdFloat32* v1) { setAddHR<I-1>(v, v0, v1); v[I-1] = v0[I-1] + v1[I-1]; }
template <> HK_FORCE_INLINE void setAddHR<1>(hkSimdFloat32* v, const hkSimdFloat32* v0, const hkSimdFloat32* v1) { v[0] = v0[0] + v1[0]; }
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::setAdd(hkMxRealfParameter v0, hkMxRealfParameter v1)
{
	hkMxRealf_Implementation::setAddHR<M>(m_real.r, v0.m_real.r, v1.m_real.r);
}

namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void setSubHR(hkSimdFloat32* v, const hkSimdFloat32* v0, const hkSimdFloat32* v1) { setSubHR<I-1>(v, v0, v1); v[I-1] = v0[I-1] - v1[I-1]; }
template <> HK_FORCE_INLINE void setSubHR<1>(hkSimdFloat32* v, const hkSimdFloat32* v0, const hkSimdFloat32* v1) { v[0] = v0[0] - v1[0]; }
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::setSub(hkMxRealfParameter v0, hkMxRealfParameter v1)
{
	hkMxRealf_Implementation::setSubHR<M>(m_real.r, v0.m_real.r, v1.m_real.r);
}

namespace hkMxRealf_Implementation
{
template <int I> HK_FORCE_INLINE void setMulHR(hkSimdFloat32* v, const hkSimdFloat32* v0, const hkSimdFloat32* v1) { setMulHR<I-1>(v, v0, v1); v[I-1] = v0[I-1] * v1[I-1]; }
template <> HK_FORCE_INLINE void setMulHR<1>(hkSimdFloat32* v, const hkSimdFloat32* v0, const hkSimdFloat32* v1) { v[0] = v0[0] * v1[0]; }
}
template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::setMul(hkMxRealfParameter v0, hkMxRealfParameter v1)
{
	hkMxRealf_Implementation::setMulHR<M>(m_real.r, v0.m_real.r, v1.m_real.r);
}

namespace hkMxRealf_Implementation
{
template <int I, hkMathAccuracyMode A, hkMathDivByZeroMode D> struct setDivHR { HK_FORCE_INLINE static void apply(hkSimdFloat32* v, const hkSimdFloat32* v0, const hkSimdFloat32* v1) { setDivHR<I-1,A,D>::apply(v, v0, v1); v[I-1].setDiv<A,D>(v0[I-1], v1[I-1]); } };
template <hkMathAccuracyMode A, hkMathDivByZeroMode D> struct setDivHR<1,A,D> { HK_FORCE_INLINE static void apply(hkSimdFloat32* v, const hkSimdFloat32* v0, const hkSimdFloat32* v1) { v[0].setDiv<A,D>(v0[0], v1[0]); } };
}
template <int M>
template <hkMathAccuracyMode A, hkMathDivByZeroMode D>
HK_FORCE_INLINE void hkMxRealf<M>::setDiv(hkMxRealfParameter v0, hkMxRealfParameter v1)
{
	hkMxRealf_Implementation::setDivHR<M,A,D>::apply(m_real.r, v0.m_real.r, v1.m_real.r);
}

template <int M>
HK_FORCE_INLINE void hkMxRealf<M>::setDiv(hkMxRealfParameter v0, hkMxRealfParameter v1)
{
	hkMxRealf_Implementation::setDivHR<M,HK_ACC_23_BIT,HK_DIV_IGNORE>::apply(m_real.r, v0.m_real.r, v1.m_real.r);
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
