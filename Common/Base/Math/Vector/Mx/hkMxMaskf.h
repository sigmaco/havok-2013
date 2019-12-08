/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#ifndef HK_MXMASKf_H
#define HK_MXMASKf_H

#define hkMxMaskParameterf  const hkMxMaskf<M>&

#include <Common/Base/Math/Vector/Mx/hkMxVectorf.h>

/// Long mask vector for vectorized computing (M masks).
///
/// This represents M masks for vector compares. Using this class is central for avoiding
/// branching instructions. The masks are employed by the select() methods of the data vectors.
///
/// The purpose of this mask vector is to implement efficient loop-unrolled algorithms without branching
/// to efficiently use the SIMD processing hardware capabilities.
///
/// \sa hkMxVectorf hkMxRealf
template <int M>
class hkMxMaskf
{
public:

	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_MATH, hkMxMaskf<M>);

	/// The number of masks.
	enum { mxLength = M };

	typedef hkVector4ComparisonMask::Mask Mask; ///< The mask values.

	/// Set all masks to the template MASK argument.
	template <hkVector4ComparisonMask::Mask MASK> HK_FORCE_INLINE void setAll();
	/// Set the I-th submask to \a a.
	template <int I> HK_FORCE_INLINE void set( hkVector4fComparisonParameter a );
	/// Get the I-th submask.
	template <int I> HK_FORCE_INLINE const hkVector4fComparison&	get() const;

	/// Set masks of self to the logical AND of respective masks in \a a and \a b.
	HK_FORCE_INLINE void setAnd(hkMxMaskParameterf a, hkMxMaskParameterf b);
	/// Set masks of self to the logical OR of respective masks in \a a and \a b.
	HK_FORCE_INLINE void setOr(hkMxMaskParameterf a, hkMxMaskParameterf b);

	/// Returns true if any bit in any mask in self is set.
	HK_FORCE_INLINE hkBool32 anyIsSet() const;

	/// Logical AND of bits within each submask. Unused submasks are assumed zero.
	/// \a andOut = xyzw with x=a&b&c&d, y=e&f&g&h, z=i&j&k&l, w=m&n&o&p
	/// \warning [M:1-4 only] 
	HK_FORCE_INLINE void horizontalAnd4( hkVector4fComparison& andOut ) const;


	hkMxMaskfStorage<M> m_comp; ///< The masks.
};

#if defined(HK_COMPILER_HAS_INTRINSICS_IA32)
	#if (HK_SSE_VERSION >= 0x50) && !defined(HK_REAL_IS_DOUBLE)
	#include <Common/Base/Math/Vector/Mx/hkMxMask_AVX.inl>
	#else
	#include <Common/Base/Math/Vector/Mx/hkMxMaskf.inl>
	#endif
#else
	#include <Common/Base/Math/Vector/Mx/hkMxMaskf.inl>
#endif

// convenient shortcut
typedef hkMxMaskf<4>	  hk4xMaskf;

#endif // HK_MXMASKf_H

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
