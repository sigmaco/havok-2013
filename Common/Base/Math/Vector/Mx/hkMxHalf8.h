/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#ifndef HK_MXHALF_8_H
#define HK_MXHALF_8_H

#define hkMxHalf8Parameter const hkMxHalf8<M>&

#include <Common/Base/Math/Vector/Mx/hkMxVectorf.h>
#include <Common/Base/Math/Vector/Mx/hkMxVectord.h>

/// Long vector for vectorized computing (Mx8 packed float values).
///
/// This represents Mx8 packed floating point values. The packing reduces the precision:
/// 1 sign bit, 8 bit exponent, 7 bit mantissa.
/// Notes:
///  -  This has 1 bit higher accuracy than using native hkHalf.
///  -  This class stores 8 values because of 16 byte alignment.
///
/// In this documentation we use abcd and following letters to
/// refer to one of the floating point values. As every packed hkHalf array stores 8 values, think of
/// this class to hold two packed 4-component vectors per subvector.
/// Example M=4: interleaved layout of the long vector: abcdABCD efghEFGH ijklIJKL mnopMNOP
/// with lower/uppercase belonging together to from the two packed vectors.
///
/// The purpose of this vector is to implement efficient loop-unrolled algorithms without branching
/// to efficiently use the SIMD processing hardware capabilities.
template <int M>
class hkMxHalf8
{
public:

	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_MATH, hkMxHalf8<M>);

	/// Store \a v0 and \a v1 by reducing precision and interleaving.
	HK_FORCE_INLINE void pack(hkMxVectorfParameter v0, hkMxVectorfParameter v1 );
	/// Store \a v0 and \a v1 by reducing precision and interleaving.
	HK_FORCE_INLINE void pack(hkMxVectordParameter v0, hkMxVectordParameter v1 );
	/// Store \a v by reducing precision and interleaving with existing second vector (untouched).
	HK_FORCE_INLINE void packFirst(hkMxVectorfParameter v);
	/// Store \a v by reducing precision and interleaving with existing second vector (untouched).
	HK_FORCE_INLINE void packFirst(hkMxVectordParameter v);
	/// Store \a v by reducing precision and interleaving with existing first vector (untouched).
	HK_FORCE_INLINE void packSecond(hkMxVectorfParameter v);
	/// Store \a v by reducing precision and interleaving with existing first vector (untouched).
	HK_FORCE_INLINE void packSecond(hkMxVectordParameter v);

	/// Unpack and sort back into \a v0 and \a v1.
	HK_FORCE_INLINE void unpack(hkMxVectorf<M>& v0, hkMxVectorf<M>& v1) const;
	/// Unpack and sort back into \a v0 and \a v1.
	HK_FORCE_INLINE void unpack(hkMxVectord<M>& v0, hkMxVectord<M>& v1) const;
	/// Unpack only first interleaved vector and store back into \a v.
	HK_FORCE_INLINE void unpackFirst(hkMxVectorf<M>& v) const;
	/// Unpack only first interleaved vector and store back into \a v.
	HK_FORCE_INLINE void unpackFirst(hkMxVectord<M>& v) const;
	/// Unpack only second interleaved vector and store back into \a v.
	HK_FORCE_INLINE void unpackSecond(hkMxVectorf<M>& v) const;
	/// Unpack only second interleaved vector and store back into \a v.
	HK_FORCE_INLINE void unpackSecond(hkMxVectord<M>& v) const;

	/// Write subvectors non-linear indexed to memory using addresses \a base + ( \a m * byteAddressIncrement)
	template <hkUint32 byteAddressIncrement> HK_FORCE_INLINE void scatter(hkHalf* base) const;

	/// Set packed representation such that unpacking yields zero vectors.
	HK_FORCE_INLINE void setZero();

	/// Reduce the precision of the full bit-width vector \a v to mimic the accuracy reduction incurred by packing.
	static HK_FORCE_INLINE void HK_CALL reducePrecision( hkMxVectorf<M>& v ); 
	/// Reduce the precision of the full bit-width vector \a v to mimic the accuracy reduction incurred by packing.
	static HK_FORCE_INLINE void HK_CALL reducePrecision( hkMxVectord<M>& v ); 

protected:

	hkMxHalf8Storage<M> m_half; ///< The packed storage.
};



#if defined(HK_COMPILER_HAS_INTRINSICS_IA32)
//	#if (HK_SSE_VERSION >= 0x50)
//		#include <Common/Base/Math/Vector/Mx/hkMxHalf8f_AVX.inl>
//	#else
		#include <Common/Base/Math/Vector/Mx/hkMxHalf8f.inl>
//	#endif
	#include <Common/Base/Math/Vector/Mx/hkMxHalf8d.inl>
#else
	#include <Common/Base/Math/Vector/Mx/hkMxHalf8f.inl>
	#include <Common/Base/Math/Vector/Mx/hkMxHalf8d.inl>
#endif

// convenient shortcuts
typedef hkMxHalf8<4> hk4xHalf8;


#endif // HK_MXHALF_8_H

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
