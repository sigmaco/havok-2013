/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#ifndef HK_MXDOUBLE_H
#define HK_MXDOUBLE_H

namespace hkCompileError
{
	template <bool b> struct MXR_NOT_IMPLEMENTEDd_FOR_THIS_VECTOR_LENGTH;
	template <> struct MXR_NOT_IMPLEMENTEDd_FOR_THIS_VECTOR_LENGTH<true>{ };
}
#define HK_MXDOUBLE_MX_NOT_IMPLEMENTEDd HK_COMPILE_TIME_ASSERT2(M==0, MXR_NOT_IMPLEMENTEDd_FOR_THIS_VECTOR_LENGTH)

#define hkMxRealdParameter   const hkMxReald<M>&

template <int M> class hkMxVectord;
#include <Common/Base/Math/Vector/Mx/hkMxVectord.h>
#include <Common/Base/Math/Vector/Mx/hkMxSingled.h>
#include <Common/Base/Math/Vector/Mx/hkMxMaskd.h>

/// Long vector for vectorized computing (M scalars).
///
/// This represents M scalars stored SIMD-friendly. In this documentation we use abcd and following letters to
/// refer to one of the 4-component subscalars.
/// Example M=4: layout of the long vector: aaaa eeee iiii mmmm
///
/// The purpose of this vector is to implement efficient loop-unrolled algorithms without branching
/// to efficiently use the SIMD processing hardware capabilities.
///
/// \sa hkMxVectord hkMxSingled
template <int M>
class hkMxReald
{
public:

	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_MATH, hkMxReald<M>);

	/// The number of SIMD-friendly scalars stored in this vector.
	///
	/// When coding, this value can be retrieved using the class definition as well as from variable instances.
	/// Example: incrementing a loop counter: i += hkMxReald<M>::mxLength;.
	/// Example: declaring an array appropriate with same length as a vector: int array[realvec_var.mxLength];
	enum { mxLength = M };

#ifndef HK_DISABLE_MATH_CONSTRUCTORS
	/// Default constructor. Does not initialize.
	HK_FORCE_INLINE hkMxReald() {}

	/// Set self to broadcast value \a v
	HK_FORCE_INLINE explicit hkMxReald(hkDouble64& v); 

	/// Set self to broadcast value \a v
	HK_FORCE_INLINE explicit hkMxReald(hkSimdDouble64Parameter v); 

	/// Set self to broadcast \a v.xyzw to x=aaaa y=eeee z=iiii w=mmmm
	/// \warning [M:1-4 only] 
	HK_FORCE_INLINE explicit hkMxReald(hkVector4dParameter v); 
#endif

	/// Copies all components from \a v. ( self = v )
	HK_FORCE_INLINE void operator= ( hkMxRealdParameter v );

	/// Set self to broadcast \a r: xxxx yyyy zzzz wwww
	HK_FORCE_INLINE void setBroadcast( hkVector4dParameter r );

	/// Set self to broadcast \a r: xxxx xxxx xxxx xxxx
	HK_FORCE_INLINE void setBroadcast( hkSimdDouble64Parameter r );

	/// Read scalars contiguous from memory as aeim and convert to SIMD-friendly storage
	HK_FORCE_INLINE void load(const hkDouble64* r);
	HK_FORCE_INLINE void loadNotAligned(const hkDouble64* r);
	HK_FORCE_INLINE void loadNotCached(const hkDouble64* r);
	/// Convert from SIMD-friendly storage and store contiguous to memory \a rOut = aeim
	HK_FORCE_INLINE void store(hkDouble64* rOut) const;
	HK_FORCE_INLINE void storeNotAligned(hkDouble64* rOut) const;
	HK_FORCE_INLINE void storeNotCached(hkDouble64* rOut) const;

	/// Set to a constant vector.
	template<int vectorConstant> HK_FORCE_INLINE void setConstant();

	/// Read scalars non-contiguous from memory using addresses \a base + (m * byteAddressIncrement) and convert to SIMD-friendly storage
	template <hkUint32 byteAddressIncrement> HK_FORCE_INLINE void gather(const hkDouble64* base);
	/// Read scalars non-linear indexed from memory using addresses \a base + ( \a indices[m] * byteAddressIncrement) and convert to SIMD-friendly storage
	template <hkUint32 byteAddressIncrement> HK_FORCE_INLINE void gather(const hkDouble64* base, const hkUint16* indices);
	/// Read scalars non-linear indexed from memory using addresses \a base + ( \a indices[m] * byteAddressIncrement) and convert to SIMD-friendly storage
	template <hkUint32 byteAddressIncrement> HK_FORCE_INLINE void gather(const hkDouble64* base, const hkInt32* indices);
	/// Read scalars non-linear from memory using addresses \a base[m] + byteAddressOffset and convert to SIMD-friendly storage
	template <hkUint32 byteAddressOffset>    HK_FORCE_INLINE void gatherWithOffset(const void* base[M]);
	/// Read scalars non-contiguous from memory using addresses \a base + (m * byteAddressIncrement) and convert to SIMD-friendly storage
	template <hkUint32 byteAddressIncrement> HK_FORCE_INLINE void gather(const hkHalf* base);

	/// Convert from SIMD-friendly storage and write scalars non-contiguous to memory using addresses \a base + (m * byteAddressIncrement)
	template <hkUint32 byteAddressIncrement> HK_FORCE_INLINE void scatter(hkDouble64* base) const;
	/// Convert from SIMD-friendly storage and write scalars non-linear indexed to memory using addresses \a base + ( \a indices[m] * byteAddressIncrement)
	template <hkUint32 byteAddressIncrement> HK_FORCE_INLINE void scatter(hkDouble64* base, const hkUint16* indices) const;
	/// Convert from SIMD-friendly storage and write scalars non-linear indexed to memory using addresses \a base + ( \a indices[m] * byteAddressIncrement)
	template <hkUint32 byteAddressIncrement> HK_FORCE_INLINE void scatter(hkDouble64* base, const hkInt32* indices) const;
	/// Convert from SIMD-friendly storage and write scalars non-linear to memory using addresses \a base[m] + byteAddressOffset
	template <hkUint32 byteAddressOffset>    HK_FORCE_INLINE void scatterWithOffset(void* base[M]) const;


	// comparisons
	HK_FORCE_INLINE void less(hkMxVectordParameter v, hkMxMaskd<M>& mask) const;
	HK_FORCE_INLINE void less(hkMxSingledParameter v, hkMxMaskd<M>& mask) const;
	HK_FORCE_INLINE void less(hkMxRealdParameter v, hkMxMaskd<M>& mask) const;
	HK_FORCE_INLINE void lessEqual(hkMxVectordParameter v, hkMxMaskd<M>& mask) const;
	HK_FORCE_INLINE void lessEqual(hkMxSingledParameter v, hkMxMaskd<M>& mask) const;
	HK_FORCE_INLINE void lessEqual(hkMxRealdParameter v, hkMxMaskd<M>& mask) const;
	HK_FORCE_INLINE void greater(hkMxVectordParameter v, hkMxMaskd<M>& mask) const;
	HK_FORCE_INLINE void greater(hkMxSingledParameter v, hkMxMaskd<M>& mask) const;
	HK_FORCE_INLINE void greater(hkMxRealdParameter v, hkMxMaskd<M>& mask) const;
	HK_FORCE_INLINE void greaterEqual(hkMxVectordParameter v, hkMxMaskd<M>& mask) const;
	HK_FORCE_INLINE void greaterEqual(hkMxSingledParameter v, hkMxMaskd<M>& mask) const;
	HK_FORCE_INLINE void greaterEqual(hkMxRealdParameter v, hkMxMaskd<M>& mask) const;

	HK_FORCE_INLINE void setSelect(hkMxMaskParameterd mask, hkMxRealdParameter trueValue, hkMxRealdParameter falseValue );
	HK_FORCE_INLINE void setSelect(hkMxMaskParameterd mask, hkMxSingledParameter trueValue, hkMxRealdParameter falseValue ); // bad interface !
	HK_FORCE_INLINE void setSelect(hkMxMaskParameterd mask, hkMxRealdParameter trueValue, hkMxSingledParameter falseValue ); // bad interface !

	// no operands
	HK_FORCE_INLINE void sqrt(); // 23 bit, sqrt set 0
	template <hkMathAccuracyMode A, hkMathNegSqrtMode S> HK_FORCE_INLINE void sqrt();

	
	// one operand
	HK_FORCE_INLINE void add(hkMxRealdParameter r);
	HK_FORCE_INLINE void sub(hkMxRealdParameter r);
	HK_FORCE_INLINE void mul(hkMxRealdParameter r);
	HK_FORCE_INLINE void div(hkMxRealdParameter r); // 23 bit, div 0 ignore
	template <hkMathAccuracyMode A, hkMathDivByZeroMode D> HK_FORCE_INLINE void div(hkMxRealdParameter r);
	HK_FORCE_INLINE void setNeg(hkMxRealdParameter r);		

	HK_FORCE_INLINE void setReciprocal(hkMxRealdParameter r); // 23 bit, div 0 ignore
	template <hkMathAccuracyMode A, hkMathDivByZeroMode D> HK_FORCE_INLINE void setReciprocal(hkMxRealdParameter r);

	template <hkMathAccuracyMode A, hkMathNegSqrtMode S> HK_FORCE_INLINE void setSqrtInverse(hkMxRealdParameter r);

	// Zero I-th scalar if the corresponding mask is set.
	HK_FORCE_INLINE void zeroIfTrue(hkMxMaskParameterd mask);
	// Zero I-th scalar if the corresponding mask is not set.
	HK_FORCE_INLINE void zeroIfFalse(hkMxMaskParameterd mask);

	// two operands
	HK_FORCE_INLINE void setAdd(hkMxRealdParameter v0, hkMxRealdParameter v1);
	HK_FORCE_INLINE void setSub(hkMxRealdParameter v0, hkMxRealdParameter v1);
	HK_FORCE_INLINE void setMul(hkMxRealdParameter v0, hkMxRealdParameter v1);
	HK_FORCE_INLINE void setDiv(hkMxRealdParameter v0, hkMxRealdParameter v1); // 23 bit, div 0 ignore
	template <hkMathAccuracyMode A, hkMathDivByZeroMode D> HK_FORCE_INLINE void setDiv(hkMxRealdParameter v0, hkMxRealdParameter v1);
	HK_FORCE_INLINE void setMax(hkMxRealdParameter v0, hkMxRealdParameter v1);
	HK_FORCE_INLINE void setMin(hkMxRealdParameter v0, hkMxRealdParameter v1);

	// mixed operands
	template <int N> HK_FORCE_INLINE void setDot(hkMxVectordParameter v0, hkMxVectordParameter v1);
	template <int N> HK_FORCE_INLINE void setDot(hkMxSingledParameter s, hkMxVectordParameter v);
	HK_FORCE_INLINE void setDot4xyz1(hkMxVectordParameter v0, hkMxVectordParameter v1);
	HK_FORCE_INLINE void setDot4xyz1(hkMxSingledParameter s, hkMxVectordParameter v);

	/// Return the I-th scalar by broadcasting it to \a vOut = [i=0]aaaa [i=1]eeee [i=2]iiii [i=3]mmmm
	template <int I> HK_FORCE_INLINE void getAsBroadcast(hkVector4d& vOut) const;
	/// Return the I-th scalar broadcasted as [i=0]aaaa [i=1]eeee [i=2]iiii [i=3]mmmm
	template <int I> HK_FORCE_INLINE const hkVector4d getAsBroadcast() const;

	/// Return the I-th scalar in a SIMD-friendly way.
	template <int I> HK_FORCE_INLINE const hkSimdDouble64 getReal() const;
	/// Set the I-th subscalar to \a r.
	template <int I> HK_FORCE_INLINE void setReal(hkSimdDouble64Parameter r);

	/// Special store method to write to \a vOut = aeim.
	/// Excess components of \a vOut are undefined.
	/// \warning [M:1-4 only] 
	HK_FORCE_INLINE void storePacked(hkVector4d& vOut) const;



	hkMxRealdStorage<M> m_real; ///< The SIMD-friendly scalars.
};

#if defined(HK_COMPILER_HAS_INTRINSICS_IA32)
	#if (HK_SSE_VERSION >= 0x50) && !defined(HK_REAL_IS_DOUBLE)
	#include <Common/Base/Math/Vector/Mx/hkMxReal_AVX.inl>
	#else
	#include <Common/Base/Math/Vector/Mx/hkMxReald.inl>
	#endif
#else
	#include <Common/Base/Math/Vector/Mx/hkMxReald.inl>
#endif

// convenient shortcut
typedef hkMxReald<4>   hk4xReald;

#endif // HK_MXDOUBLE_H

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
