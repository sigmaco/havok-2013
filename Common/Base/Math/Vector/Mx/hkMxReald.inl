/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#define MXR_TWO_OPERANDS(METHOD, OP) namespace hkMxReald_Implementation { template <int I> HK_FORCE_INLINE void OP##HR(hkSimdDouble64* r, const hkSimdDouble64* r0, const hkSimdDouble64* r1) { OP##HR<I-1>(r, r0, r1); r[I-1].OP(r0[I-1], r1[I-1]); } template <> HK_FORCE_INLINE void OP##HR<1>(hkSimdDouble64* r, const hkSimdDouble64* r0, const hkSimdDouble64* r1) { r[0].OP(r0[0], r1[0]); } } template <int M> HK_FORCE_INLINE void hkMxReald<M>::METHOD(hkMxRealdParameter r0, hkMxRealdParameter r1) { hkMxReald_Implementation::OP##HR<M>(m_real.r, r0.m_real.r, r1.m_real.r); }
#define MXR_MIXED_OPERANDS(METHOD, OP) namespace hkMxReald_Implementation { template <int I> HK_FORCE_INLINE void OP##SHR(hkSimdDouble64* r, hkVector4dParameter r0, const hkVector4d* r1) { OP##SHR<I-1>(r, r0, r1); r[I-1] = r0.OP(r1[I-1]); } template <> HK_FORCE_INLINE void OP##SHR<1>(hkSimdDouble64* r, hkVector4dParameter r0, const hkVector4d* r1) { r[0] = r0.OP(r1[0]); } } template <int M> HK_FORCE_INLINE void hkMxReald<M>::METHOD(hkMxSingledParameter r0, hkMxVectordParameter r1) { hkMxReald_Implementation::OP##SHR<M>(m_real.r, r0.m_single.s, r1.m_vec.v); }
#define MXR_TWO_V_OPERANDS(METHOD, OP) namespace hkMxReald_Implementation { template <int I> HK_FORCE_INLINE void OP##VHR(hkSimdDouble64* r, const hkVector4d* v0, const hkVector4d* v1) { OP##VHR<I-1>(r, v0, v1); r[I-1] = v0[I-1].OP(v1[I-1]); } template <> HK_FORCE_INLINE void OP##VHR<1>(hkSimdDouble64* r, const hkVector4d* v0, const hkVector4d* v1) { r[0] = v0[0].OP(v1[0]); } } template <int M> HK_FORCE_INLINE void hkMxReald<M>::METHOD(hkMxVectordParameter v0, hkMxVectordParameter v1) { hkMxReald_Implementation::OP##VHR<M>(m_real.r, v0.m_vec.v, v1.m_vec.v); }



MXR_TWO_OPERANDS( setMin, setMin )
MXR_TWO_OPERANDS( setMax, setMax )

namespace hkMxReald_Implementation
{
template <int I, int N> struct setDotVHR { HK_FORCE_INLINE static void apply(hkSimdDouble64* r, const hkVector4d* v0, const hkVector4d* v1) { setDotVHR<I-1,N>::apply(r, v0, v1); r[I-1] = v0[I-1].dot<N>(v1[I-1]); } };
template <int N> struct setDotVHR<1,N> { HK_FORCE_INLINE static void apply(hkSimdDouble64* r, const hkVector4d* v0, const hkVector4d* v1) { r[0] = v0[0].dot<N>(v1[0]); } };
}
template <int M> template <int N> HK_FORCE_INLINE void hkMxReald<M>::setDot(hkMxVectordParameter v0, hkMxVectordParameter v1) 
{ 
	hkMxReald_Implementation::setDotVHR<M,N>::apply(m_real.r, v0.m_vec.v, v1.m_vec.v); 
}

MXR_TWO_V_OPERANDS( setDot4xyz1, dot4xyz1 )


namespace hkMxReald_Implementation
{
template <int I, int N> struct setDotSHR { HK_FORCE_INLINE static void apply(hkSimdDouble64* r, hkVector4dParameter r0, const hkVector4d* r1) { setDotSHR<I-1,N>::apply(r, r0, r1); r[I-1] = r0.dot<N>(r1[I-1]); } };
template <int N> struct setDotSHR<1,N> { HK_FORCE_INLINE static void apply(hkSimdDouble64* r, hkVector4dParameter r0, const hkVector4d* r1) { r[0] = r0.dot<N>(r1[0]); } };
}
template <int M> template <int N> HK_FORCE_INLINE void hkMxReald<M>::setDot(hkMxSingledParameter r0, hkMxVectordParameter r1) 
{ 
	hkMxReald_Implementation::setDotSHR<M,N>::apply(m_real.r, r0.m_single.s, r1.m_vec.v); 
}

MXR_MIXED_OPERANDS( setDot4xyz1, dot4xyz1 )



#undef MXR_TWO_OPERANDS
#undef MXR_TWO_V_OPERANDS
#undef MXR_MIXED_OPERANDS

#ifndef HK_DISABLE_MATH_CONSTRUCTORS

namespace hkMxReald_Implementation
{
template <int I> HK_FORCE_INLINE void constructHRS(hkSimdDouble64* r, hkDouble64& v) { constructHRS<I-1>(r, v); r[I-1].setFromFloat(v); }
template <> HK_FORCE_INLINE void constructHRS<1>(hkSimdDouble64* r, hkDouble64& v) { r[0].setFromFloat(v); }
}
template <int M>
HK_FORCE_INLINE hkMxReald<M>::hkMxReald(hkDouble64& v)
{
	hkMxReald_Implementation::constructHRS<M>(m_real.r, v);
}

namespace hkMxReald_Implementation
{
template <int I> HK_FORCE_INLINE void constructHRSS(hkSimdDouble64* r, hkSimdDouble64Parameter v) { constructHRSS<I-1>(r, v); r[I-1] = v; }
template <> HK_FORCE_INLINE void constructHRSS<1>(hkSimdDouble64* r, hkSimdDouble64Parameter v) { r[0] = v; }
}
template <int M>
HK_FORCE_INLINE hkMxReald<M>::hkMxReald(hkSimdDouble64Parameter v)
{
	hkMxReald_Implementation::constructHRSS<M>(m_real.r, v);
}

namespace hkMxReald_Implementation
{
template <int I> HK_FORCE_INLINE void constructHR(hkSimdDouble64* v, hkVector4dParameter v0) { constructHR<I-1>(v, v0); v[I-1] = v0.getComponent<I-1>(); }
template <> HK_FORCE_INLINE void constructHR<1>(hkSimdDouble64* v, hkVector4dParameter v0) { v[0] = v0.getComponent<0>(); }
}
template <int M>
HK_FORCE_INLINE hkMxReald<M>::hkMxReald(hkVector4dParameter v)
{
	hkMxReald_Implementation::constructHR<M>(m_real.r, v); // safe, v.getComponent<> asserts M<4
}

#endif

namespace hkMxReald_Implementation
{
template <int I> HK_FORCE_INLINE void moveHR(hkSimdDouble64* HK_RESTRICT v, const hkSimdDouble64* HK_RESTRICT v0) { moveHR<I-1>(v, v0); v[I-1] = v0[I-1]; }
template <> HK_FORCE_INLINE void moveHR<1>(hkSimdDouble64* HK_RESTRICT v, const hkSimdDouble64* HK_RESTRICT v0) { v[0] = v0[0]; }
}
template <int M>
HK_FORCE_INLINE void hkMxReald<M>::operator= ( hkMxRealdParameter v )
{
	hkMxReald_Implementation::moveHR<M>(m_real.r, v.m_real.r);
}


namespace hkMxReald_Implementation
{
template <int I> HK_FORCE_INLINE void setBCHR(hkSimdDouble64* v, hkVector4dParameter v0) { setBCHR<I-1>(v, v0); v[I-1] = v0.getComponent<I-1>(); }
template <> HK_FORCE_INLINE void setBCHR<1>(hkSimdDouble64* v, hkVector4dParameter v0) { v[0] = v0.getComponent<0>(); }
}
template <int M>
HK_FORCE_INLINE void hkMxReald<M>::setBroadcast( hkVector4dParameter r )
{
	hkMxReald_Implementation::setBCHR<M>(m_real.r, r); // safe, v.getComponent<> asserts M<4
}

namespace hkMxReald_Implementation
{
template <int I> HK_FORCE_INLINE void setBCHRS(hkSimdDouble64* v, hkSimdDouble64Parameter v0) { setBCHRS<I-1>(v, v0); v[I-1] = v0; }
template <> HK_FORCE_INLINE void setBCHRS<1>(hkSimdDouble64* v, hkSimdDouble64Parameter v0) { v[0] = v0; }
}
template <int M>
HK_FORCE_INLINE void hkMxReald<M>::setBroadcast( hkSimdDouble64Parameter r )
{
	hkMxReald_Implementation::setBCHRS<M>(m_real.r, r);
}

namespace hkMxReald_Implementation
{
template <int I> HK_FORCE_INLINE void loadHR(hkSimdDouble64* v, const hkDouble64* r) { loadHR<I-1>(v, r); v[I-1].load<1>(r + (I-1)); }
template <> HK_FORCE_INLINE void loadHR<1>(hkSimdDouble64* v, const hkDouble64* r) { v[0].load<1>(r); }
}
template <int M>
HK_FORCE_INLINE void hkMxReald<M>::load(const hkDouble64* r)
{
	hkMxReald_Implementation::loadHR<M>(m_real.r, r);
}

namespace hkMxReald_Implementation
{
template <int I> HK_FORCE_INLINE void loadNHR(hkSimdDouble64* v, const hkDouble64* r) { loadNHR<I-1>(v, r); v[I-1].load<1,HK_IO_NATIVE_ALIGNED>(r + (I-1)); }
template <> HK_FORCE_INLINE void loadNHR<1>(hkSimdDouble64* v, const hkDouble64* r) { v[0].load<1,HK_IO_NATIVE_ALIGNED>(r); }
}
template <int M>
HK_FORCE_INLINE void hkMxReald<M>::loadNotAligned(const hkDouble64* r)
{
	hkMxReald_Implementation::loadNHR<M>(m_real.r, r);
}

namespace hkMxReald_Implementation
{
template <int I> HK_FORCE_INLINE void loadCHR(hkSimdDouble64* v, const hkDouble64* r) { loadCHR<I-1>(v, r); v[I-1].load<1,HK_IO_NOT_CACHED>(r + (I-1)); }
template <> HK_FORCE_INLINE void loadCHR<1>(hkSimdDouble64* v, const hkDouble64* r) { v[0].load<1,HK_IO_NOT_CACHED>(r); }
}
template <int M>
HK_FORCE_INLINE void hkMxReald<M>::loadNotCached(const hkDouble64* r)
{
	hkMxReald_Implementation::loadCHR<M>(m_real.r, r);
}

namespace hkMxReald_Implementation
{
template <int I> HK_FORCE_INLINE void storeHR(const hkSimdDouble64* v, hkDouble64* r) { storeHR<I-1>(v, r); v[I-1].store<1>(r + (I-1)); }
template <> HK_FORCE_INLINE void storeHR<1>(const hkSimdDouble64* v, hkDouble64* r) { v[0].store<1>(r); }
}
template <int M>
HK_FORCE_INLINE void hkMxReald<M>::store(hkDouble64* rOut) const
{
	hkMxReald_Implementation::storeHR<M>(m_real.r, rOut);
}

namespace hkMxReald_Implementation
{
template <int I> HK_FORCE_INLINE void storeNHR(const hkSimdDouble64* v, hkDouble64* r) { storeNHR<I-1>(v, r); v[I-1].store<1,HK_IO_NATIVE_ALIGNED>(r + (I-1)); }
template <> HK_FORCE_INLINE void storeNHR<1>(const hkSimdDouble64* v, hkDouble64* r) { v[0].store<1,HK_IO_NATIVE_ALIGNED>(r); }
}
template <int M>
HK_FORCE_INLINE void hkMxReald<M>::storeNotAligned(hkDouble64* rOut) const
{
	hkMxReald_Implementation::storeNHR<M>(m_real.r, rOut);
}

namespace hkMxReald_Implementation
{
template <int I> HK_FORCE_INLINE void storeCHR(const hkSimdDouble64* v, hkDouble64* r) { storeCHR<I-1>(v, r); v[I-1].store<1,HK_IO_NOT_CACHED>(r + (I-1)); }
template <> HK_FORCE_INLINE void storeCHR<1>(const hkSimdDouble64* v, hkDouble64* r) { v[0].store<1,HK_IO_NOT_CACHED>(r); }
}
template <int M>
HK_FORCE_INLINE void hkMxReald<M>::storeNotCached(hkDouble64* rOut) const
{
	hkMxReald_Implementation::storeCHR<M>(m_real.r, rOut);
}



namespace hkMxReald_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct gatherHR {
HK_FORCE_INLINE static void apply(hkSimdDouble64* v, const hkDouble64* HK_RESTRICT base)
{
	gatherHR<I-1, byteAddressIncrement>::apply(v, base);
	v[I-1].setFromFloat( *hkAddByteOffsetConst( base, (I-1)*byteAddressIncrement ) );
} };
template <hkUint32 byteAddressIncrement> struct gatherHR<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(hkSimdDouble64* v, const hkDouble64* HK_RESTRICT base)
{
	v[0].setFromFloat(*base);
} };
}
template <int M>
template <hkUint32 byteAddressIncrement>
HK_FORCE_INLINE void hkMxReald<M>::gather(const hkDouble64* HK_RESTRICT base)
{
	hkMxReald_Implementation::gatherHR<M, byteAddressIncrement>::apply(m_real.r, base);
}


namespace hkMxReald_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct gatherHH {
HK_FORCE_INLINE static void apply(hkSimdDouble64* v, const hkHalf* HK_RESTRICT base)
{
	gatherHH<I-1, byteAddressIncrement>::apply(v, base);
	v[I-1].setFromHalf( *hkAddByteOffsetConst( base, (I-1)*byteAddressIncrement ) );
} };
template <hkUint32 byteAddressIncrement> struct gatherHH<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(hkSimdDouble64* v, const hkHalf* HK_RESTRICT base)
{
	v[0].setFromHalf(*base);
} };
}
template <int M>
template <hkUint32 byteAddressIncrement>
HK_FORCE_INLINE void hkMxReald<M>::gather(const hkHalf* HK_RESTRICT base)
{
	hkMxReald_Implementation::gatherHH<M, byteAddressIncrement>::apply(m_real.r, base);
}

namespace hkMxReald_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct gatherUintHR {
HK_FORCE_INLINE static void apply(hkSimdDouble64* v, const hkDouble64* HK_RESTRICT base, const hkUint16* indices)
{
	gatherUintHR<I-1, byteAddressIncrement>::apply(v, base, indices);
	v[I-1].setFromFloat( *hkAddByteOffsetConst( base, indices[I-1] * byteAddressIncrement ) );
} };
template <hkUint32 byteAddressIncrement> struct gatherUintHR<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(hkSimdDouble64* v, const hkDouble64* HK_RESTRICT base, const hkUint16* indices)
{
	v[0].setFromFloat(*hkAddByteOffsetConst( base, indices[0] * byteAddressIncrement ));
} };
}
template <int M>
template <hkUint32 byteAddressIncrement>
HK_FORCE_INLINE void hkMxReald<M>::gather(const hkDouble64* HK_RESTRICT base, const hkUint16* indices)
{
	hkMxReald_Implementation::gatherUintHR<M, byteAddressIncrement>::apply(m_real.r, base, indices);
}

namespace hkMxReald_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct gatherIntHR {
HK_FORCE_INLINE static void apply(hkSimdDouble64* v, const hkDouble64* HK_RESTRICT base, const hkInt32* indices)
{
	gatherIntHR<I-1, byteAddressIncrement>::apply(v, base, indices);
	v[I-1].setFromFloat( *hkAddByteOffsetConst( base, indices[I-1] * byteAddressIncrement ) );
} };
template <hkUint32 byteAddressIncrement> struct gatherIntHR<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(hkSimdDouble64* v, const hkDouble64* HK_RESTRICT base, const hkInt32* indices)
{
	v[0].setFromFloat( *hkAddByteOffsetConst( base, indices[0] * byteAddressIncrement ));
} };
}
template <int M>
template <hkUint32 byteAddressIncrement>
HK_FORCE_INLINE void hkMxReald<M>::gather(const hkDouble64* HK_RESTRICT base, const hkInt32* indices)
{
	hkMxReald_Implementation::gatherIntHR<M, byteAddressIncrement>::apply(m_real.r, base, indices);
}

namespace hkMxReald_Implementation
{
template <int I, hkUint32 byteOffset> struct gatherWithOffsetHR {
HK_FORCE_INLINE static void apply(hkSimdDouble64* v, const void** base)
{
	const hkDouble64* HK_RESTRICT ptr0 = (const hkDouble64*)hkAddByteOffsetConst(base[I-1], byteOffset); 
	gatherWithOffsetHR<I-1, byteOffset>::apply(v, base);
	v[I-1].setFromFloat( *ptr0 );
} };
template <hkUint32 byteOffset> struct gatherWithOffsetHR<1, byteOffset> {
HK_FORCE_INLINE static void apply(hkSimdDouble64* v, const void** base)
{
	const hkDouble64* HK_RESTRICT ptr = (const hkDouble64*)hkAddByteOffsetConst(base[0], byteOffset); 
	v[0].setFromFloat(*ptr);
} };
}
template <int M>
template <hkUint32 byteOffset> 
HK_FORCE_INLINE void hkMxReald<M>::gatherWithOffset(const void* base[M])
{
	hkMxReald_Implementation::gatherWithOffsetHR<M, byteOffset>::apply(m_real.r, base);
}




namespace hkMxReald_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct scatterHR {
HK_FORCE_INLINE static void apply(const hkSimdDouble64* v, hkDouble64* base)
{
	scatterHR<I-1, byteAddressIncrement>::apply(v, base);
	v[I-1].store<1>(hkAddByteOffset(base, (I-1)*byteAddressIncrement));
} };
template <hkUint32 byteAddressIncrement> struct scatterHR<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(const hkSimdDouble64* v, hkDouble64* base)
{
	v[0].store<1>(base);
} };
}
template <int M>
template <hkUint32 byteAddressIncrement>
HK_FORCE_INLINE void hkMxReald<M>::scatter(hkDouble64* base) const
{
	hkMxReald_Implementation::scatterHR<M, byteAddressIncrement>::apply(m_real.r, base);
}

namespace hkMxReald_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct scatterUintHR {
HK_FORCE_INLINE static void apply(const hkSimdDouble64* v, hkDouble64* base, const hkUint16* indices)
{
	hkDouble64* HK_RESTRICT ptr = hkAddByteOffset(base, indices[I-1] * byteAddressIncrement);
	scatterUintHR<I-1, byteAddressIncrement>::apply(v, base, indices);
	v[I-1].store<1>(ptr);
} };
template <hkUint32 byteAddressIncrement> struct scatterUintHR<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(const hkSimdDouble64* v, hkDouble64* base, const hkUint16* indices)
{
	hkDouble64* HK_RESTRICT ptr = hkAddByteOffset(base, indices[0] * byteAddressIncrement);
	v[0].store<1>(ptr);
} };
}
template <int M>
template <hkUint32 byteAddressIncrement>
HK_FORCE_INLINE void hkMxReald<M>::scatter(hkDouble64* base, const hkUint16* indices) const
{
	hkMxReald_Implementation::scatterUintHR<M, byteAddressIncrement>::apply(m_real.r, base, indices);
}

namespace hkMxReald_Implementation
{
template <int I, hkUint32 byteAddressIncrement> struct scatterIntHR {
HK_FORCE_INLINE static void apply(const hkSimdDouble64* v, hkDouble64* base, const hkInt32* indices)
{
	hkDouble64* HK_RESTRICT ptr = hkAddByteOffset(base, indices[I-1] * byteAddressIncrement);
	scatterIntHR<I-1, byteAddressIncrement>::apply(v, base, indices);
	v[I-1].store<1>(ptr);
} };
template <hkUint32 byteAddressIncrement> struct scatterIntHR<1, byteAddressIncrement> {
HK_FORCE_INLINE static void apply(const hkSimdDouble64* v, hkDouble64* base, const hkInt32* indices)
{
	hkDouble64* HK_RESTRICT ptr = hkAddByteOffset(base, indices[0] * byteAddressIncrement);
	v[0].store<1>(ptr);
} };
}
template <int M>
template <hkUint32 byteAddressIncrement>
HK_FORCE_INLINE void hkMxReald<M>::scatter(hkDouble64* base, const hkInt32* indices) const
{
	hkMxReald_Implementation::scatterIntHR<M, byteAddressIncrement>::apply(m_real.r, base, indices);
}

namespace hkMxReald_Implementation
{
template <int I, hkUint32 byteOffset> struct scatterWithOffsetHR {
HK_FORCE_INLINE static void apply(const hkSimdDouble64* v, void** base)
{
	hkDouble64* HK_RESTRICT ptr0 = (hkDouble64*)hkAddByteOffset(base[I-1], byteOffset); 
	scatterWithOffsetHR<I-1, byteOffset>::apply(v, base);
	v[I-1].store<1>(ptr0);
} };
template <hkUint32 byteOffset> struct scatterWithOffsetHR<1, byteOffset> {
HK_FORCE_INLINE static void apply(const hkSimdDouble64* v, void** base)
{
	hkDouble64* HK_RESTRICT ptr0 = (hkDouble64*)hkAddByteOffset(base[0], byteOffset); 
	v[0].store<1>(ptr0);
} };
}
template <int M>
template <hkUint32 byteOffset> 
HK_FORCE_INLINE void hkMxReald<M>::scatterWithOffset(void* base[M]) const 
{
	hkMxReald_Implementation::scatterWithOffsetHR<M, byteOffset>::apply(m_real.r, base);
}








template <int M>
template <int I>
HK_FORCE_INLINE void hkMxReald<M>::setReal(hkSimdDouble64Parameter r)
{
	HK_MXVECTORd_MX_SUBINDEX_CHECK;
	m_real.r[I] = r;
}

template <int M>
template <int I> 
HK_FORCE_INLINE void hkMxReald<M>::getAsBroadcast(hkVector4d& vOut) const
{
	HK_MXVECTORd_MX_SUBINDEX_CHECK;
	vOut.setAll(m_real.r[I]);
}

template <int M>
template <int I> 
HK_FORCE_INLINE const hkVector4d hkMxReald<M>::getAsBroadcast() const
{
	HK_MXVECTORd_MX_SUBINDEX_CHECK;
	hkVector4d h; h.setAll(m_real.r[I]);
	return h;
}

template <int M>
template <int I> 
HK_FORCE_INLINE const hkSimdDouble64 hkMxReald<M>::getReal() const
{
	HK_MXVECTORd_MX_SUBINDEX_CHECK;
	return m_real.r[I];
}


namespace hkMxReald_Implementation
{
template <int I> HK_FORCE_INLINE void setConstHR(hkSimdDouble64* v, hkSimdDouble64Parameter vC) { setConstHR<I-1>(v,vC); v[I-1] = vC; }
template <> HK_FORCE_INLINE void setConstHR<1>(hkSimdDouble64* v, hkSimdDouble64Parameter vC) { v[0] = vC; }
}
template <int M>
template<int vectorConstant> 
HK_FORCE_INLINE void hkMxReald<M>::setConstant()
{
	const hkSimdDouble64 vC = hkSimdDouble64::getConstant<vectorConstant>();
	hkMxReald_Implementation::setConstHR<M>(m_real.r, vC);
}


namespace hkMxReald_Implementation
{
template <int I> HK_FORCE_INLINE void addHR(hkSimdDouble64* v, const hkSimdDouble64* v0) { addHR<I-1>(v, v0); v[I-1] = v[I-1] + v0[I-1]; }
template <> HK_FORCE_INLINE void addHR<1>(hkSimdDouble64* v, const hkSimdDouble64* v0) { v[0] = v[0] + v0[0]; }
}
template <int M>
HK_FORCE_INLINE void hkMxReald<M>::add(hkMxRealdParameter r)
{
	hkMxReald_Implementation::addHR<M>(m_real.r, r.m_real.r);
}

namespace hkMxReald_Implementation
{
template <int I> HK_FORCE_INLINE void subHR(hkSimdDouble64* v, const hkSimdDouble64* v0) { subHR<I-1>(v, v0); v[I-1] = v[I-1] - v0[I-1]; }
template <> HK_FORCE_INLINE void subHR<1>(hkSimdDouble64* v, const hkSimdDouble64* v0) { v[0] = v[0] - v0[0]; }
}
template <int M>
HK_FORCE_INLINE void hkMxReald<M>::sub(hkMxRealdParameter r)
{
	hkMxReald_Implementation::subHR<M>(m_real.r, r.m_real.r);
}

namespace hkMxReald_Implementation
{
template <int I> HK_FORCE_INLINE void mulHR(hkSimdDouble64* v, const hkSimdDouble64* v0) { mulHR<I-1>(v, v0); v[I-1] = v[I-1] * v0[I-1]; }
template <> HK_FORCE_INLINE void mulHR<1>(hkSimdDouble64* v, const hkSimdDouble64* v0) { v[0] = v[0] * v0[0]; }
}
template <int M>
HK_FORCE_INLINE void hkMxReald<M>::mul(hkMxRealdParameter r)
{
	hkMxReald_Implementation::mulHR<M>(m_real.r, r.m_real.r);
}

namespace hkMxReald_Implementation
{
template <int I, hkMathAccuracyMode A, hkMathDivByZeroMode D> struct divHR { HK_FORCE_INLINE static void apply(hkSimdDouble64* v, const hkSimdDouble64* v0) { divHR<I-1,A,D>::apply(v, v0); v[I-1].div<A,D>(v0[I-1]); } };
template <hkMathAccuracyMode A, hkMathDivByZeroMode D> struct divHR<1,A,D> { HK_FORCE_INLINE static void apply(hkSimdDouble64* v, const hkSimdDouble64* v0) { v[0].div<A,D>(v0[0]); } };
}
template <int M>
template <hkMathAccuracyMode A, hkMathDivByZeroMode D>
HK_FORCE_INLINE void hkMxReald<M>::div(hkMxRealdParameter r)
{
	hkMxReald_Implementation::divHR<M,A,D>::apply(m_real.r, r.m_real.r);
}

template <int M>
HK_FORCE_INLINE void hkMxReald<M>::div(hkMxRealdParameter r)
{
	hkMxReald_Implementation::divHR<M,HK_ACC_23_BIT,HK_DIV_IGNORE>::apply(m_real.r, r.m_real.r);
}



namespace hkMxReald_Implementation
{
template <int I> HK_FORCE_INLINE void setNegHR(hkSimdDouble64* v, const hkSimdDouble64* v0) { setNegHR<I-1>(v, v0); v[I-1] = -v0[I-1]; }
template <> HK_FORCE_INLINE void setNegHR<1>(hkSimdDouble64* v, const hkSimdDouble64* v0) { v[0] = -v0[0]; }
}
template <int M>
HK_FORCE_INLINE void hkMxReald<M>::setNeg(hkMxRealdParameter r)
{
	hkMxReald_Implementation::setNegHR<M>(m_real.r, r.m_real.r);
}

namespace hkMxReald_Implementation
{
	template <int I, hkMathAccuracyMode A, hkMathDivByZeroMode D> struct setReciprocalHR { HK_FORCE_INLINE static void apply(hkSimdDouble64* v, const hkSimdDouble64* v0) { setReciprocalHR<I-1,A,D>::apply(v, v0); v[I-1].setReciprocal<A,D>(v0[I-1]); } };
	template <hkMathAccuracyMode A, hkMathDivByZeroMode D> struct setReciprocalHR<1,A,D> { HK_FORCE_INLINE static void apply(hkSimdDouble64* v, const hkSimdDouble64* v0) { v[0].setReciprocal<A,D>(v0[0]); } };

	template <int I, hkMathAccuracyMode A, hkMathNegSqrtMode D> struct setSqrtInverseHR { HK_FORCE_INLINE static void apply(hkSimdDouble64* v, const hkSimdDouble64* v0) { setSqrtInverseHR<I-1,A,D>::apply(v, v0); v[I-1] = v0[I-1].sqrtInverse<A,D>(); } };
	template <hkMathAccuracyMode A, hkMathNegSqrtMode D> struct setSqrtInverseHR<1,A,D> { HK_FORCE_INLINE static void apply(hkSimdDouble64* v, const hkSimdDouble64* v0) { v[0] = v0[0].sqrtInverse<A,D>(); } };
}
template <int M>
template <hkMathAccuracyMode A, hkMathDivByZeroMode D> 
HK_FORCE_INLINE void hkMxReald<M>::setReciprocal(hkMxRealdParameter r)
{
	hkMxReald_Implementation::setReciprocalHR<M,A,D>::apply(m_real.r, r.m_real.r);
}

template <int M>
HK_FORCE_INLINE void hkMxReald<M>::setReciprocal(hkMxRealdParameter r)
{
	hkMxReald_Implementation::setReciprocalHR<M,HK_ACC_23_BIT,HK_DIV_IGNORE>::apply(m_real.r, r.m_real.r);
}

template <int M>
template <hkMathAccuracyMode A, hkMathNegSqrtMode D> 
HK_FORCE_INLINE void hkMxReald<M>::setSqrtInverse(hkMxRealdParameter r)
{
	hkMxReald_Implementation::setSqrtInverseHR<M,A,D>::apply(m_real.r, r.m_real.r);
}

namespace hkMxReald_Implementation
{
template <int I, hkMathAccuracyMode A, hkMathNegSqrtMode S> struct sqrtHR { HK_FORCE_INLINE static void apply(hkSimdDouble64* v) { sqrtHR<I-1,A,S>::apply(v); v[I-1] = v[I-1].sqrt<A,S>(); } };
template <hkMathAccuracyMode A, hkMathNegSqrtMode S> struct sqrtHR<1,A,S> { HK_FORCE_INLINE static void apply(hkSimdDouble64* v) { v[0] = v[0].sqrt<A,S>(); } };
}
template <int M>
template <hkMathAccuracyMode A, hkMathNegSqrtMode S> 
HK_FORCE_INLINE void hkMxReald<M>::sqrt()
{
	hkMxReald_Implementation::sqrtHR<M,A,S>::apply(m_real.r);
}

template <int M>
HK_FORCE_INLINE void hkMxReald<M>::sqrt()
{
	hkMxReald_Implementation::sqrtHR<M,HK_ACC_23_BIT,HK_SQRT_SET_ZERO>::apply(m_real.r);
}



namespace hkMxReald_Implementation
{
template <int I>
HK_FORCE_INLINE void selectRH(hkSimdDouble64* r, const hkVector4dComparison* mask, const hkSimdDouble64* trueValue, const hkSimdDouble64* falseValue)
{
	selectRH<I-1>(r, mask, trueValue, falseValue);
	r[I-1].setSelect(mask[I-1], trueValue[I-1], falseValue[I-1]);
}

template <>
HK_FORCE_INLINE void selectRH<1>(hkSimdDouble64* r, const hkVector4dComparison* mask, const hkSimdDouble64* trueValue, const hkSimdDouble64* falseValue)
{
	r[0].setSelect(mask[0], trueValue[0], falseValue[0]);
}
}
template <int M>
HK_FORCE_INLINE void hkMxReald<M>::setSelect(hkMxMaskParameterd mask, hkMxRealdParameter trueValue, hkMxRealdParameter falseValue)
{
	hkMxReald_Implementation::selectRH<M>(m_real.r, mask.m_comp.c, trueValue.m_real.r, falseValue.m_real.r);
}



namespace hkMxReald_Implementation
{
template <int I>
HK_FORCE_INLINE void selectRH(hkSimdDouble64* r, const hkVector4dComparison* mask, hkSimdDouble64Parameter trueValue, const hkSimdDouble64* falseValue)
{
	selectRH<I-1>(r, mask, trueValue, falseValue);
	r[I-1].setSelect(mask[I-1], trueValue, falseValue[I-1]);
}

template <>
HK_FORCE_INLINE void selectRH<1>(hkSimdDouble64* r, const hkVector4dComparison* mask, hkSimdDouble64Parameter trueValue, const hkSimdDouble64* falseValue)
{
	r[0].setSelect(mask[0], trueValue, falseValue[0]);
}
}
template <int M>
HK_FORCE_INLINE void hkMxReald<M>::setSelect(hkMxMaskParameterd mask, hkMxSingledParameter trueValue, hkMxRealdParameter falseValue)
{
	hkMxReald_Implementation::selectRH<M>(m_real.r, mask.m_comp.c, trueValue.m_single.s.template getComponent<0>(), falseValue.m_real.r);
}



namespace hkMxReald_Implementation
{
template <int I>
HK_FORCE_INLINE void selectRH(hkSimdDouble64* r, const hkVector4dComparison* mask, const hkSimdDouble64* trueValue, hkSimdDouble64Parameter falseValue)
{
	selectRH<I-1>(r, mask, trueValue, falseValue);
	r[I-1].setSelect(mask[I-1], trueValue[I-1], falseValue);
}

template <>
HK_FORCE_INLINE void selectRH<1>(hkSimdDouble64* r, const hkVector4dComparison* mask, const hkSimdDouble64* trueValue, hkSimdDouble64Parameter falseValue)
{
	r[0].setSelect(mask[0], trueValue[0], falseValue);
}
}
template <int M>
HK_FORCE_INLINE void hkMxReald<M>::setSelect(hkMxMaskParameterd mask, hkMxRealdParameter trueValue, hkMxSingledParameter falseValue)
{
	hkMxReald_Implementation::selectRH<M>(m_real.r, mask.m_comp.c, trueValue.m_real.r, falseValue.m_single.s.template getComponent<0>());
}

template <int M>
HK_FORCE_INLINE void hkMxReald<M>::zeroIfTrue(hkMxMaskParameterd mask)
{
	hkMxReald<M> zero; zero.setConstant<HK_QUADREAL_0>( );
	setSelect(mask, zero, *this);
}

template <int M>
HK_FORCE_INLINE void hkMxReald<M>::zeroIfFalse(hkMxMaskParameterd mask)
{
	hkMxReald<M> zero; zero.setConstant<HK_QUADREAL_0>( );
	setSelect(mask, *this, zero);
}

namespace hkMxReald_Implementation
{
template <int I> HK_FORCE_INLINE void compareLessThanHR(const hkSimdDouble64* v0, const hkVector4d* v1, hkVector4dComparison* m) { hkVector4d v; v.setAll(v0[I-1]); compareLessThanHR<I-1>(v0, v1, m); m[I-1] = v.less(v1[I-1]); }
template <> HK_FORCE_INLINE void compareLessThanHR<1>(const hkSimdDouble64* v0, const hkVector4d* v1, hkVector4dComparison* m) { hkVector4d v; v.setAll(v0[0]); m[0] = v.less(v1[0]); }
}
template <int M>
HK_FORCE_INLINE void hkMxReald<M>::less(hkMxVectordParameter v, hkMxMaskd<M>& mask) const
{
	hkMxReald_Implementation::compareLessThanHR<M>(m_real.r, v.m_vec.v, mask.m_comp.c);
}

namespace hkMxReald_Implementation
{
template <int I> HK_FORCE_INLINE void compareLessThanEqualHR(const hkSimdDouble64* v0, const hkVector4d* v1, hkVector4dComparison* m) { hkVector4d v; v.setAll(v0[I-1]); compareLessThanEqualHR<I-1>(v0, v1, m); m[I-1] = v.lessEqual(v1[I-1]); }
template <> HK_FORCE_INLINE void compareLessThanEqualHR<1>(const hkSimdDouble64* v0, const hkVector4d* v1, hkVector4dComparison* m) { hkVector4d v; v.setAll(v0[0]); m[0] = v.lessEqual(v1[0]); }
}
template <int M>
HK_FORCE_INLINE void hkMxReald<M>::lessEqual(hkMxVectordParameter v, hkMxMaskd<M>& mask) const
{
	hkMxReald_Implementation::compareLessThanEqualHR<M>(m_real.r, v.m_vec.v, mask.m_comp.c);
}

namespace hkMxReald_Implementation
{
template <int I> HK_FORCE_INLINE void compareGreaterThanHR(const hkSimdDouble64* v0, const hkVector4d* v1, hkVector4dComparison* m) { hkVector4d v; v.setAll(v0[I-1]); compareGreaterThanHR<I-1>(v0, v1, m); m[I-1] = v.greater(v1[I-1]); }
template <> HK_FORCE_INLINE void compareGreaterThanHR<1>(const hkSimdDouble64* v0, const hkVector4d* v1, hkVector4dComparison* m) { hkVector4d v; v.setAll(v0[0]); m[0] = v.greater(v1[0]); }
}
template <int M>
HK_FORCE_INLINE void hkMxReald<M>::greater(hkMxVectordParameter v, hkMxMaskd<M>& mask) const
{
	hkMxReald_Implementation::compareGreaterThanHR<M>(m_real.r, v.m_vec.v, mask.m_comp.c);
}

namespace hkMxReald_Implementation
{
template <int I> HK_FORCE_INLINE void compareGreaterThanEqualHR(const hkSimdDouble64* v0, const hkVector4d* v1, hkVector4dComparison* m) { hkVector4d v; v.setAll(v0[I-1]); compareGreaterThanEqualHR<I-1>(v0, v1, m); m[I-1] = v.greaterEqual(v1[I-1]); }
template <> HK_FORCE_INLINE void compareGreaterThanEqualHR<1>(const hkSimdDouble64* v0, const hkVector4d* v1, hkVector4dComparison* m) { hkVector4d v; v.setAll(v0[0]); m[0] = v.greaterEqual(v1[0]); }
}
template <int M>
HK_FORCE_INLINE void hkMxReald<M>::greaterEqual(hkMxVectordParameter v, hkMxMaskd<M>& mask) const
{
	hkMxReald_Implementation::compareGreaterThanEqualHR<M>(m_real.r, v.m_vec.v, mask.m_comp.c);
}


namespace hkMxReald_Implementation
{
template <int I> HK_FORCE_INLINE void compareLessThanHRS(const hkSimdDouble64* v0, hkVector4dParameter v1, hkVector4dComparison* m) { hkVector4d v; v.setAll(v0[I-1]); compareLessThanHRS<I-1>(v0, v1, m); m[I-1] = v.less(v1); }
template <> HK_FORCE_INLINE void compareLessThanHRS<1>(const hkSimdDouble64* v0, hkVector4dParameter v1, hkVector4dComparison* m) { hkVector4d v; v.setAll(v0[0]); m[0] = v.less(v1); }
}
template <int M>
HK_FORCE_INLINE void hkMxReald<M>::less(hkMxSingledParameter v, hkMxMaskd<M>& mask) const
{
	hkMxReald_Implementation::compareLessThanHRS<M>(m_real.r, v.m_single.s, mask.m_comp.c);
}

namespace hkMxReald_Implementation
{
template <int I> HK_FORCE_INLINE void compareLessThanEqualHRS(const hkSimdDouble64* v0, hkVector4dParameter v1, hkVector4dComparison* m) { hkVector4d v; v.setAll(v0[I-1]); compareLessThanEqualHRS<I-1>(v0, v1, m); m[I-1] = v.lessEqual(v1); }
template <> HK_FORCE_INLINE void compareLessThanEqualHRS<1>(const hkSimdDouble64* v0, hkVector4dParameter v1, hkVector4dComparison* m) { hkVector4d v; v.setAll(v0[0]); m[0] = v.lessEqual(v1); }
}
template <int M>
HK_FORCE_INLINE void hkMxReald<M>::lessEqual(hkMxSingledParameter v, hkMxMaskd<M>& mask) const
{
	hkMxReald_Implementation::compareLessThanEqualHRS<M>(m_real.r, v.m_single.s, mask.m_comp.c);
}

namespace hkMxReald_Implementation
{
template <int I> HK_FORCE_INLINE void compareGreaterThanHRS(const hkSimdDouble64* v0, hkVector4dParameter v1, hkVector4dComparison* m) { hkVector4d v; v.setAll(v0[I-1]); compareGreaterThanHRS<I-1>(v0, v1, m); m[I-1] = v.greater(v1); }
template <> HK_FORCE_INLINE void compareGreaterThanHRS<1>(const hkSimdDouble64* v0, hkVector4dParameter v1, hkVector4dComparison* m) { hkVector4d v; v.setAll(v0[0]); m[0] = v.greater(v1); }
}
template <int M>
HK_FORCE_INLINE void hkMxReald<M>::greater(hkMxSingledParameter v, hkMxMaskd<M>& mask) const
{
	hkMxReald_Implementation::compareGreaterThanHRS<M>(m_real.r, v.m_single.s, mask.m_comp.c);
}

namespace hkMxReald_Implementation
{
template <int I> HK_FORCE_INLINE void compareGreaterThanEqualHRS(const hkSimdDouble64* v0, hkVector4dParameter v1, hkVector4dComparison* m) { hkVector4d v; v.setAll(v0[I-1]); compareGreaterThanEqualHRS<I-1>(v0, v1, m); m[I-1] = v.greaterEqual(v1); }
template <> HK_FORCE_INLINE void compareGreaterThanEqualHRS<1>(const hkSimdDouble64* v0, hkVector4dParameter v1, hkVector4dComparison* m) { hkVector4d v; v.setAll(v0[0]); m[0] = v.greaterEqual(v1); }
}
template <int M>
HK_FORCE_INLINE void hkMxReald<M>::greaterEqual(hkMxSingledParameter v, hkMxMaskd<M>& mask) const
{
	hkMxReald_Implementation::compareGreaterThanEqualHRS<M>(m_real.r, v.m_single.s, mask.m_comp.c);
}


namespace hkMxReald_Implementation
{
template <int I> HK_FORCE_INLINE void compareLessThanHR(const hkSimdDouble64* v0, const hkSimdDouble64* v1, hkVector4dComparison* m) { compareLessThanHR<I-1>(v0, v1, m); m[I-1] = v0[I-1].less(v1[I-1]); }
template <> HK_FORCE_INLINE void compareLessThanHR<1>(const hkSimdDouble64* v0, const hkSimdDouble64* v1, hkVector4dComparison* m) { m[0] = v0[0].less(v1[0]); }
}
template <int M>
HK_FORCE_INLINE void hkMxReald<M>::less(hkMxRealdParameter v, hkMxMaskd<M>& mask) const
{
	hkMxReald_Implementation::compareLessThanHR<M>(m_real.r, v.m_real.r, mask.m_comp.c);
}

namespace hkMxReald_Implementation
{
template <int I> HK_FORCE_INLINE void compareLessThanEqualHR(const hkSimdDouble64* v0, const hkSimdDouble64* v1, hkVector4dComparison* m) { compareLessThanEqualHR<I-1>(v0, v1, m); m[I-1] = v0[I-1].lessEqual(v1[I-1]); }
template <> HK_FORCE_INLINE void compareLessThanEqualHR<1>(const hkSimdDouble64* v0, const hkSimdDouble64* v1, hkVector4dComparison* m) { m[0] = v0[0].lessEqual(v1[0]); }
}
template <int M>
HK_FORCE_INLINE void hkMxReald<M>::lessEqual(hkMxRealdParameter v, hkMxMaskd<M>& mask) const
{
	hkMxReald_Implementation::compareLessThanEqualHR<M>(m_real.r, v.m_real.r, mask.m_comp.c);
}

namespace hkMxReald_Implementation
{
template <int I> HK_FORCE_INLINE void compareGreaterThanHR(const hkSimdDouble64* v0, const hkSimdDouble64* v1, hkVector4dComparison* m) { compareGreaterThanHR<I-1>(v0, v1, m); m[I-1] = v0[I-1].greater(v1[I-1]); }
template <> HK_FORCE_INLINE void compareGreaterThanHR<1>(const hkSimdDouble64* v0, const hkSimdDouble64* v1, hkVector4dComparison* m) { m[0] = v0[0].greater(v1[0]); }
}
template <int M>
HK_FORCE_INLINE void hkMxReald<M>::greater(hkMxRealdParameter v, hkMxMaskd<M>& mask) const
{
	hkMxReald_Implementation::compareGreaterThanHR<M>(m_real.r, v.m_real.r, mask.m_comp.c);
}

namespace hkMxReald_Implementation
{
template <int I> HK_FORCE_INLINE void compareGreaterThanEqualHR(const hkSimdDouble64* v0, const hkSimdDouble64* v1, hkVector4dComparison* m) { compareGreaterThanEqualHR<I-1>(v0, v1, m); m[I-1] = v0[I-1].greaterEqual(v1[I-1]); }
template <> HK_FORCE_INLINE void compareGreaterThanEqualHR<1>(const hkSimdDouble64* v0, const hkSimdDouble64* v1, hkVector4dComparison* m) { m[0] = v0[0].greaterEqual(v1[0]); }
}
template <int M>
HK_FORCE_INLINE void hkMxReald<M>::greaterEqual(hkMxRealdParameter v, hkMxMaskd<M>& mask) const
{
	hkMxReald_Implementation::compareGreaterThanEqualHR<M>(m_real.r, v.m_real.r, mask.m_comp.c);
}


template <int M>
HK_FORCE_INLINE void hkMxReald<M>::storePacked(hkVector4d& vOut) const
{
	HK_MXDOUBLE_MX_NOT_IMPLEMENTEDd;
}

template <>
HK_FORCE_INLINE void hkMxReald<1>::storePacked(hkVector4d& vOut) const
{
	vOut.setComponent<0>(m_real.r[0]);
	//HK_ON_DEBUG(HK_M128(vOut.m_quad).m128_u32[1] = 0xffffffff; HK_M128(vOut.m_quad).m128_u32[2] = 0xffffffff; HK_M128(vOut.m_quad).m128_u32[3] = 0xffffffff;)
}

template <>
HK_FORCE_INLINE void hkMxReald<2>::storePacked(hkVector4d& vOut) const
{
	vOut.set(m_real.r[0], m_real.r[1], m_real.r[1], m_real.r[1]);
	//HK_ON_DEBUG(HK_M128(vOut.m_quad).m128_u32[2] = 0xffffffff; HK_M128(vOut.m_quad).m128_u32[3] = 0xffffffff;)
}

template <>
HK_FORCE_INLINE void hkMxReald<3>::storePacked(hkVector4d& vOut) const
{
	vOut.set(m_real.r[0], m_real.r[1], m_real.r[2], m_real.r[2]);
	//HK_ON_DEBUG(HK_M128(vOut.m_quad).m128_u32[3] = 0xffffffff;)
}

template <>
HK_FORCE_INLINE void hkMxReald<4>::storePacked(hkVector4d& vOut) const
{
	vOut.set(m_real.r[0], m_real.r[1], m_real.r[2], m_real.r[3]);
}




namespace hkMxReald_Implementation
{
template <int I> HK_FORCE_INLINE void setAddHR(hkSimdDouble64* v, const hkSimdDouble64* v0, const hkSimdDouble64* v1) { setAddHR<I-1>(v, v0, v1); v[I-1] = v0[I-1] + v1[I-1]; }
template <> HK_FORCE_INLINE void setAddHR<1>(hkSimdDouble64* v, const hkSimdDouble64* v0, const hkSimdDouble64* v1) { v[0] = v0[0] + v1[0]; }
}
template <int M>
HK_FORCE_INLINE void hkMxReald<M>::setAdd(hkMxRealdParameter v0, hkMxRealdParameter v1)
{
	hkMxReald_Implementation::setAddHR<M>(m_real.r, v0.m_real.r, v1.m_real.r);
}

namespace hkMxReald_Implementation
{
template <int I> HK_FORCE_INLINE void setSubHR(hkSimdDouble64* v, const hkSimdDouble64* v0, const hkSimdDouble64* v1) { setSubHR<I-1>(v, v0, v1); v[I-1] = v0[I-1] - v1[I-1]; }
template <> HK_FORCE_INLINE void setSubHR<1>(hkSimdDouble64* v, const hkSimdDouble64* v0, const hkSimdDouble64* v1) { v[0] = v0[0] - v1[0]; }
}
template <int M>
HK_FORCE_INLINE void hkMxReald<M>::setSub(hkMxRealdParameter v0, hkMxRealdParameter v1)
{
	hkMxReald_Implementation::setSubHR<M>(m_real.r, v0.m_real.r, v1.m_real.r);
}

namespace hkMxReald_Implementation
{
template <int I> HK_FORCE_INLINE void setMulHR(hkSimdDouble64* v, const hkSimdDouble64* v0, const hkSimdDouble64* v1) { setMulHR<I-1>(v, v0, v1); v[I-1] = v0[I-1] * v1[I-1]; }
template <> HK_FORCE_INLINE void setMulHR<1>(hkSimdDouble64* v, const hkSimdDouble64* v0, const hkSimdDouble64* v1) { v[0] = v0[0] * v1[0]; }
}
template <int M>
HK_FORCE_INLINE void hkMxReald<M>::setMul(hkMxRealdParameter v0, hkMxRealdParameter v1)
{
	hkMxReald_Implementation::setMulHR<M>(m_real.r, v0.m_real.r, v1.m_real.r);
}

namespace hkMxReald_Implementation
{
template <int I, hkMathAccuracyMode A, hkMathDivByZeroMode D> struct setDivHR { HK_FORCE_INLINE static void apply(hkSimdDouble64* v, const hkSimdDouble64* v0, const hkSimdDouble64* v1) { setDivHR<I-1,A,D>::apply(v, v0, v1); v[I-1].setDiv<A,D>(v0[I-1], v1[I-1]); } };
template <hkMathAccuracyMode A, hkMathDivByZeroMode D> struct setDivHR<1,A,D> { HK_FORCE_INLINE static void apply(hkSimdDouble64* v, const hkSimdDouble64* v0, const hkSimdDouble64* v1) { v[0].setDiv<A,D>(v0[0], v1[0]); } };
}
template <int M>
template <hkMathAccuracyMode A, hkMathDivByZeroMode D>
HK_FORCE_INLINE void hkMxReald<M>::setDiv(hkMxRealdParameter v0, hkMxRealdParameter v1)
{
	hkMxReald_Implementation::setDivHR<M,A,D>::apply(m_real.r, v0.m_real.r, v1.m_real.r);
}

template <int M>
HK_FORCE_INLINE void hkMxReald<M>::setDiv(hkMxRealdParameter v0, hkMxRealdParameter v1)
{
	hkMxReald_Implementation::setDivHR<M,HK_ACC_23_BIT,HK_DIV_IGNORE>::apply(m_real.r, v0.m_real.r, v1.m_real.r);
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
