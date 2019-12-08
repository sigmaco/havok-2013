/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#include <Common/Base/Math/Vector/hkHalf8Util.h>

namespace hkMxHalf8_Implementation
{
	template <int I> HK_FORCE_INLINE void reducePrecisionH8H(hkVector4* v) { reducePrecisionH8H<I-1>(v); v[I-1].reduceToHalfPrecision(); }
	template <> HK_FORCE_INLINE void reducePrecisionH8H<1>(hkVector4* v) { v[0].reduceToHalfPrecision(); }
}
template <int M>
HK_FORCE_INLINE /*static*/ void HK_CALL hkMxHalf8<M>::reducePrecision(hkMxVector<M>& v )
{
	hkMxHalf8_Implementation::reducePrecisionH8H<M>(v.m_vec.v);
}


namespace hkMxHalf8_Implementation
{
	template <int I> HK_FORCE_INLINE void packH8H(hkVector4* h, const hkVector4* HK_RESTRICT vp0, const hkVector4* HK_RESTRICT vp1) { packH8H<I-1>(h,vp0,vp1); hkHalf8Util::pack<HK_ROUND_TRUNCATE,HK_IO_SIMD_ALIGNED>(vp0[I-1], vp1[I-1], (hkHalf*)&h[I-1]); }
	template <> HK_FORCE_INLINE void packH8H<0>(hkVector4* h, const hkVector4* HK_RESTRICT vp0, const hkVector4* HK_RESTRICT vp1) { }
}

template <int M>
HK_FORCE_INLINE void hkMxHalf8<M>::pack(hkMxVectorParameter v0, hkMxVectorParameter v1 )
{
	const hkVector4* HK_RESTRICT v0p = v0.m_vec.v;
	const hkVector4* HK_RESTRICT v1p = v1.m_vec.v;
	hkMxHalf8_Implementation::packH8H<M>( (hkVector4*) (m_half.h), v0p, v1p);
}


namespace hkMxHalf8_Implementation
{
	template <int I> HK_FORCE_INLINE void packFirstH8H(hkHalf* h, const hkVector4* vp) { packFirstH8H<I-1>(h,vp); vp[I-1].store<4,HK_IO_SIMD_ALIGNED,HK_ROUND_TRUNCATE>(h+((I-1)*8)); }
	template <> HK_FORCE_INLINE void packFirstH8H<1>(hkHalf* h, const hkVector4* vp) { vp[0].store<4,HK_IO_SIMD_ALIGNED,HK_ROUND_TRUNCATE>(h); }
}
template <int M>
HK_FORCE_INLINE void hkMxHalf8<M>::packFirst(hkMxVectorParameter v )
{
	hkMxHalf8_Implementation::packFirstH8H<M>(m_half.h, v.m_vec.v);
}

namespace hkMxHalf8_Implementation
{
	template <int I> HK_FORCE_INLINE void packSecondH8H(hkHalf* h, const hkVector4* vp) { packSecondH8H<I-1>(h,vp); vp[I-1].store<4,HK_IO_SIMD_ALIGNED,HK_ROUND_TRUNCATE>(h+((I-1)*8)+4); }
	template <> HK_FORCE_INLINE void packSecondH8H<1>(hkHalf* h, const hkVector4* vp) { vp[0].store<4,HK_IO_SIMD_ALIGNED,HK_ROUND_TRUNCATE>(h+4); }
}
template <int M>
HK_FORCE_INLINE void hkMxHalf8<M>::packSecond(hkMxVectorParameter v )
{
	hkMxHalf8_Implementation::packSecondH8H<M>(m_half.h, v.m_vec.v);
}




namespace hkMxHalf8_Implementation
{
	template <int I> HK_FORCE_INLINE void unpackH8H(const hkVector4* h, hkVector4* HK_RESTRICT vp0, hkVector4* HK_RESTRICT vp1) { unpackH8H<I-1>(h,vp0,vp1); hkHalf8Util::unpack<HK_IO_SIMD_ALIGNED>( (const hkHalf*)&h[I-1],vp0+(I-1),vp1+(I-1)); }
	template <> HK_FORCE_INLINE void unpackH8H<0>(const hkVector4* h, hkVector4* HK_RESTRICT vp0, hkVector4* HK_RESTRICT vp1) {  }
}
template <int M>
HK_FORCE_INLINE void hkMxHalf8<M>::unpack(hkMxVector<M>& v0, hkMxVector<M>& v1) const
{
	HK_MATH_ASSERT(0xad342288, (hkUlong(&v0) + sizeof(hkMxVector<M>) <= hkUlong(this) || hkUlong(this) + sizeof(hkMxHalf8<M>) <= hkUlong(&v0))
		&& (hkUlong(&v1) + sizeof(hkMxVector<M>) <= hkUlong(this) || hkUlong(this) + sizeof(hkMxHalf8<M>) <= hkUlong(&v1)), 
		"hkMxHalf8 overlaps with the vectors being packed.");
	hkVector4* HK_RESTRICT v0p = v0.m_vec.v;
	hkVector4* HK_RESTRICT v1p = v1.m_vec.v;
	hkMxHalf8_Implementation::unpackH8H<M>((const hkVector4*) m_half.h, v0p, v1p);
}

namespace hkMxHalf8_Implementation
{
	template <int I> HK_FORCE_INLINE void unpackFirstH8H(const hkHalf* h, hkVector4* HK_RESTRICT vp) { unpackFirstH8H<I-1>(h,vp); vp[I-1].load<4,HK_IO_SIMD_ALIGNED>(h+((I-1)*8)); }
	template <> HK_FORCE_INLINE void unpackFirstH8H<1>(const hkHalf* h, hkVector4* HK_RESTRICT vp) { vp[0].load<4,HK_IO_SIMD_ALIGNED>(h); }
}
template <int M>
HK_FORCE_INLINE void hkMxHalf8<M>::unpackFirst(hkMxVector<M>& v) const
{
	HK_MATH_ASSERT(0xad342289, hkUlong(&v) + sizeof(hkMxVector<M>) <= hkUlong(this) || hkUlong(this) + sizeof(hkMxHalf8<M>) <= hkUlong(&v), 
		"hkMxHalf8 overlaps with the vectors being packed.");
	hkVector4* HK_RESTRICT vp = v.m_vec.v;
	hkMxHalf8_Implementation::unpackFirstH8H<M>(m_half.h, vp);
}

namespace hkMxHalf8_Implementation
{
	template <int I> HK_FORCE_INLINE void unpackSecondH8H(const hkHalf* h, hkVector4* HK_RESTRICT vp) { unpackSecondH8H<I-1>(h,vp); vp[I-1].load<4,HK_IO_SIMD_ALIGNED>(h+((I-1)*8)+4); }
	template <> HK_FORCE_INLINE void unpackSecondH8H<1>(const hkHalf* h, hkVector4* HK_RESTRICT vp) { vp[0].load<4,HK_IO_SIMD_ALIGNED>(h+4); }
}
template <int M>
HK_FORCE_INLINE void hkMxHalf8<M>::unpackSecond(hkMxVector<M>& v) const
{
	HK_MATH_ASSERT(0xad34228a, hkUlong(&v) + sizeof(hkMxVector<M>) <= hkUlong(this) || hkUlong(this) + sizeof(hkMxHalf8<M>) <= hkUlong(&v), 
		"hkMxHalf8 overlaps with the vectors being packed.");
	hkVector4* HK_RESTRICT vp = v.m_vec.v;
	hkMxHalf8_Implementation::unpackSecondH8H<M>(m_half.h, vp);
}




namespace hkMxHalf8_Implementation
{
	template <int I> HK_FORCE_INLINE void setZeroH8H(hkHalf* v) { setZeroH8H<I-1>(v); v[((I-1)*8)+0].setZero(); v[((I-1)*8)+1].setZero(); v[((I-1)*8)+2].setZero(); v[((I-1)*8)+3].setZero(); v[((I-1)*8)+4].setZero(); v[((I-1)*8)+5].setZero(); v[((I-1)*8)+6].setZero(); v[((I-1)*8)+7].setZero(); }
	template <> HK_FORCE_INLINE void setZeroH8H<1>(hkHalf* v) { v[0].setZero(); v[1].setZero(); v[2].setZero(); v[3].setZero(); v[4].setZero(); v[5].setZero(); v[6].setZero(); v[7].setZero(); }
}
template <int M>
HK_FORCE_INLINE void hkMxHalf8<M>::setZero()
{
	hkMxHalf8_Implementation::setZeroH8H<M>(m_half.h);
}


namespace hkMxHalf8_Implementation
{
	template <int I, hkUint32 byteAddressIncrement> struct scatterH8H {
		HK_FORCE_INLINE static void apply(const hkVector4* v, hkHalf* base)
		{
			hkHalf* HK_RESTRICT ptr0 = hkAddByteOffset(base, (I-1) * byteAddressIncrement); 
			scatterH8H<I-1, byteAddressIncrement>::apply(v, base);
			v[I-1].store<4>( (hkReal*) ptr0 );
		} };
		template <hkUint32 byteAddressIncrement> struct scatterH8H<0, byteAddressIncrement> {
			HK_FORCE_INLINE static void apply(const hkVector4* v, hkHalf* base)
			{
			} };
}
template <int M>
template <hkUint32 byteAddressIncrement>
HK_FORCE_INLINE void hkMxHalf8<M>::scatter(hkHalf* base) const
{
	hkMxHalf8_Implementation::scatterH8H<M, byteAddressIncrement>::apply((hkVector4*) (m_half.h), base);
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
