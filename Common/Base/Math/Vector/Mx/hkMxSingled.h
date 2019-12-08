/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#ifndef HK_MXSINGLEd_H
#define HK_MXSINGLEd_H

#define hkMxSingledParameter const hkMxSingled<M>&

/// Long vector for vectorized computing (Mx1 vectors).
///
/// This represents M 4-component vectors which are all the same. 
/// Note that although the subvectors are all the same, this vector still has a distinct length
/// as you cannot rely in general on how the storage is optimized for the replicated subvectors.
/// In this documentation we use abcd and following letters to
/// refer to one of the 4-component subvectors.
/// Example M=4: layout of the long vector: abcd abcd abcd abcd
///
/// The purpose of this vector is to implement efficient loop-unrolled algorithms without branching
/// to efficiently use the SIMD processing hardware capabilities.
///
/// \sa hkMxVectord hkMxReald
template <int M>
class hkMxSingled
{
public:

	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_MATH, hkMxSingled<M>);

	/// The number of subvectors stored in this vector.
	///
	/// When coding, this value can be retrieved using the class definition as well as from variable instances.
	/// Example: incrementing a loop counter: i += hkMxSingled<M>::mxLength;.
	/// Example: declaring an array appropriate with same length as a vector: int array[svec_var.mxLength];
	enum { mxLength = M };

#ifndef HK_DISABLE_MATH_CONSTRUCTORS
	/// Default constructor. Does not initialize.
	HK_FORCE_INLINE hkMxSingled() {}

	/// Set self to broadcast \a v: aaaa aaaa aaaa aaaa
	HK_FORCE_INLINE explicit hkMxSingled(hkSimdDouble64Parameter v);
	/// Set self to replicate \a v: abcd abcd abcd abcd
 	HK_FORCE_INLINE explicit hkMxSingled(hkVector4dParameter v);
#endif

	/// Copies all components from \a v. ( self = v )
	HK_FORCE_INLINE void operator= ( hkMxSingledParameter v );

	/// Get the replicated subvector: return abcd
	HK_FORCE_INLINE const hkVector4d& getVector() const;

	/// Set the vector
	HK_FORCE_INLINE void setVector(hkVector4dParameter r);
	HK_FORCE_INLINE void setSimdReal(hkSimdDouble64Parameter r );

	/// Set to zero.
	HK_FORCE_INLINE void setZero();

	template<int C> HK_FORCE_INLINE void setConstant();


	hkMxSingledStorage<M> m_single; ///< The replicated subvector.
};

#if defined(HK_COMPILER_HAS_INTRINSICS_IA32)
	#if (HK_SSE_VERSION >= 0x50) && !defined(HK_REAL_IS_DOUBLE)
	#include <Common/Base/Math/Vector/Mx/hkMxSingle_AVX.inl>
	#else
	#include <Common/Base/Math/Vector/Mx/hkMxSingled.inl>
	#endif
#else
	#include <Common/Base/Math/Vector/Mx/hkMxSingled.inl>
#endif

// convenient shortcut
typedef hkMxSingled<4> hk4xSingled;

#endif // HK_MXSINGLEd_H

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
