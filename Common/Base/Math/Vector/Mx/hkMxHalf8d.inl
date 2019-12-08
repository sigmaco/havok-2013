/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#include <Common/Base/Math/Vector/hkHalf8fUtil.h>


namespace hkMxHalf8d_Implementation
{
	template <int I> HK_FORCE_INLINE void reducePrecisionH8H(hkVector4d* v) { reducePrecisionH8H<I-1>(v); v[I-1].reduceToHalfPrecision(); }
	template <> HK_FORCE_INLINE void reducePrecisionH8H<1>(hkVector4d* v) { v[0].reduceToHalfPrecision(); }
}
template <int M>
HK_FORCE_INLINE /*static*/ void HK_CALL hkMxHalf8<M>::reducePrecision(hkMxVectord<M>& v )
{
	hkMxHalf8d_Implementation::reducePrecisionH8H<M>(v.m_vec.v);
}


namespace hkMxHalf8d_Implementation
{
	template <int I> HK_FORCE_INLINE void packH8H(hkVector4d* h, const hkVector4d* HK_RESTRICT vp0, const hkVector4d* HK_RESTRICT vp1) { packH8H<I-1>(h,vp0,vp1); hkHalf8Util::pack<HK_ROUND_TRUNCATE,HK_IO_SIMD_ALIGNED>(vp0[I-1], vp1[I-1], (hkHalf*)&h[I-1]); }
	template <> HK_FORCE_INLINE void packH8H<0>(hkVector4d* h, const hkVector4d* HK_RESTRICT vp0, const hkVector4d* HK_RESTRICT vp1) { }
}

template <int M>
HK_FORCE_INLINE void hkMxHalf8<M>::pack(hkMxVectordParameter v0, hkMxVectordParameter v1 )
{
	const hkVector4d* HK_RESTRICT v0p = v0.m_vec.v;
	const hkVector4d* HK_RESTRICT v1p = v1.m_vec.v;
	hkMxHalf8d_Implementation::packH8H<M>( (hkVector4d*) (m_half.h), v0p, v1p);
}


namespace hkMxHalf8d_Implementation
{
	template <int I> HK_FORCE_INLINE void packFirstH8H(hkHalf* h, const hkVector4d* vp) { packFirstH8H<I-1>(h,vp); vp[I-1].store<4,HK_IO_SIMD_ALIGNED,HK_ROUND_TRUNCATE>(h+((I-1)*8)); }
	template <> HK_FORCE_INLINE void packFirstH8H<1>(hkHalf* h, const hkVector4d* vp) { vp[0].store<4,HK_IO_SIMD_ALIGNED,HK_ROUND_TRUNCATE>(h); }
}
template <int M>
HK_FORCE_INLINE void hkMxHalf8<M>::packFirst(hkMxVectordParameter v )
{
	hkMxHalf8d_Implementation::packFirstH8H<M>(m_half.h, v.m_vec.v);
}

namespace hkMxHalf8d_Implementation
{
	template <int I> HK_FORCE_INLINE void packSecondH8H(hkHalf* h, const hkVector4d* vp) { packSecondH8H<I-1>(h,vp); vp[I-1].store<4,HK_IO_SIMD_ALIGNED,HK_ROUND_TRUNCATE>(h+((I-1)*8)+4); }
	template <> HK_FORCE_INLINE void packSecondH8H<1>(hkHalf* h, const hkVector4d* vp) { vp[0].store<4,HK_IO_SIMD_ALIGNED,HK_ROUND_TRUNCATE>(h+4); }
}
template <int M>
HK_FORCE_INLINE void hkMxHalf8<M>::packSecond(hkMxVectordParameter v )
{
	hkMxHalf8d_Implementation::packSecondH8H<M>(m_half.h, v.m_vec.v);
}




namespace hkMxHalf8d_Implementation
{
	template <int I> HK_FORCE_INLINE void unpackH8H(const hkVector4d* h, hkVector4d* HK_RESTRICT vp0, hkVector4d* HK_RESTRICT vp1) { unpackH8H<I-1>(h,vp0,vp1); hkHalf8Util::unpack<HK_IO_SIMD_ALIGNED>( (const hkHalf*)&h[I-1],vp0+(I-1),vp1+(I-1)); }
	template <> HK_FORCE_INLINE void unpackH8H<0>(const hkVector4d* h, hkVector4d* HK_RESTRICT vp0, hkVector4d* HK_RESTRICT vp1) {  }
}
template <int M>
HK_FORCE_INLINE void hkMxHalf8<M>::unpack(hkMxVectord<M>& v0, hkMxVectord<M>& v1) const
{
	HK_MATH_ASSERT(0xad342288, (hkUlong(&v0) + sizeof(hkMxVectord<M>) <= hkUlong(this) || hkUlong(this) + sizeof(hkMxHalf8<M>) <= hkUlong(&v0))
		&& (hkUlong(&v1) + sizeof(hkMxVectord<M>) <= hkUlong(this) || hkUlong(this) + sizeof(hkMxHalf8<M>) <= hkUlong(&v1)), 
		"hkMxHalf8 overlaps with the vectors being packed.");
	hkVector4d* HK_RESTRICT v0p = v0.m_vec.v;
	hkVector4d* HK_RESTRICT v1p = v1.m_vec.v;
	hkMxHalf8d_Implementation::unpackH8H<M>((const hkVector4d*) m_half.h, v0p, v1p);
}

namespace hkMxHalf8d_Implementation
{
	template <int I> HK_FORCE_INLINE void unpackFirstH8H(const hkHalf* h, hkVector4d* HK_RESTRICT vp) { unpackFirstH8H<I-1>(h,vp); vp[I-1].load<4,HK_IO_SIMD_ALIGNED>(h+((I-1)*8)); }
	template <> HK_FORCE_INLINE void unpackFirstH8H<1>(const hkHalf* h, hkVector4d* HK_RESTRICT vp) { vp[0].load<4,HK_IO_SIMD_ALIGNED>(h); }
}
template <int M>
HK_FORCE_INLINE void hkMxHalf8<M>::unpackFirst(hkMxVectord<M>& v) const
{
	HK_MATH_ASSERT(0xad342289, hkUlong(&v) + sizeof(hkMxVectord<M>) <= hkUlong(this) || hkUlong(this) + sizeof(hkMxHalf8<M>) <= hkUlong(&v), 
		"hkMxHalf8 overlaps with the vectors being packed.");
	hkVector4d* HK_RESTRICT vp = v.m_vec.v;
	hkMxHalf8d_Implementation::unpackFirstH8H<M>(m_half.h, vp);
}

namespace hkMxHalf8d_Implementation
{
	template <int I> HK_FORCE_INLINE void unpackSecondH8H(const hkHalf* h, hkVector4d* HK_RESTRICT vp) { unpackSecondH8H<I-1>(h,vp); vp[I-1].load<4,HK_IO_SIMD_ALIGNED>(h+((I-1)*8)+4); }
	template <> HK_FORCE_INLINE void unpackSecondH8H<1>(const hkHalf* h, hkVector4d* HK_RESTRICT vp) { vp[0].load<4,HK_IO_SIMD_ALIGNED>(h+4); }
}
template <int M>
HK_FORCE_INLINE void hkMxHalf8<M>::unpackSecond(hkMxVectord<M>& v) const
{
	HK_MATH_ASSERT(0xad34228a, hkUlong(&v) + sizeof(hkMxVectord<M>) <= hkUlong(this) || hkUlong(this) + sizeof(hkMxHalf8<M>) <= hkUlong(&v), 
		"hkMxHalf8 overlaps with the vectors being packed.");
	hkVector4d* HK_RESTRICT vp = v.m_vec.v;
	hkMxHalf8d_Implementation::unpackSecondH8H<M>(m_half.h, vp);
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
