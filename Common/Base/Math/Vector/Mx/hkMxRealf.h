/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#ifndef HK_MXFLOAT_H
#define HK_MXFLOAT_H

namespace hkCompileError
{
	template <bool b> struct MXR_NOT_IMPLEMENTEDf_FOR_THIS_VECTOR_LENGTH;
	template <> struct MXR_NOT_IMPLEMENTEDf_FOR_THIS_VECTOR_LENGTH<true>{ };
}
#define HK_MXFLOAT_MX_NOT_IMPLEMENTEDf HK_COMPILE_TIME_ASSERT2(M==0, MXR_NOT_IMPLEMENTEDf_FOR_THIS_VECTOR_LENGTH)

#define hkMxRealfParameter   const hkMxRealf<M>&

template <int M> class hkMxVectorf;
#include <Common/Base/Math/Vector/Mx/hkMxVectorf.h>
#include <Common/Base/Math/Vector/Mx/hkMxSinglef.h>
#include <Common/Base/Math/Vector/Mx/hkMxMaskf.h>

/// Long vector for vectorized computing (M scalars).
///
/// This represents M scalars stored SIMD-friendly. In this documentation we use abcd and following letters to
/// refer to one of the 4-component subscalars.
/// Example M=4: layout of the long vector: aaaa eeee iiii mmmm
///
/// The purpose of this vector is to implement efficient loop-unrolled algorithms without branching
/// to efficiently use the SIMD processing hardware capabilities.
///
/// \sa hkMxVectorf hkMxSinglef
template <int M>
class hkMxRealf
{
public:

	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_MATH, hkMxRealf<M>);

	/// The number of SIMD-friendly scalars stored in this vector.
	///
	/// When coding, this value can be retrieved using the class definition as well as from variable instances.
	/// Example: incrementing a loop counter: i += hkMxRealf<M>::mxLength;.
	/// Example: declaring an array appropriate with same length as a vector: int array[realvec_var.mxLength];
	enum { mxLength = M };

#ifndef HK_DISABLE_MATH_CONSTRUCTORS
	/// Default constructor. Does not initialize.
	HK_FORCE_INLINE hkMxRealf() {}

	/// Set self to broadcast value \a v
	HK_FORCE_INLINE explicit hkMxRealf(hkFloat32& v); 

	/// Set self to broadcast value \a v
	HK_FORCE_INLINE explicit hkMxRealf(hkSimdFloat32Parameter v); 

	/// Set self to broadcast \a v.xyzw to x=aaaa y=eeee z=iiii w=mmmm
	/// \warning [M:1-4 only] 
	HK_FORCE_INLINE explicit hkMxRealf(hkVector4fParameter v); 
#endif

	/// Copies all components from \a v. ( self = v )
	HK_FORCE_INLINE void operator= ( hkMxRealfParameter v );

	/// Set self to broadcast \a r: xxxx yyyy zzzz wwww
	HK_FORCE_INLINE void setBroadcast( hkVector4fParameter r );

	/// Set self to broadcast \a r: xxxx xxxx xxxx xxxx
	HK_FORCE_INLINE void setBroadcast( hkSimdFloat32Parameter r );

	/// Read scalars contiguous from memory as aeim and convert to SIMD-friendly storage
	HK_FORCE_INLINE void load(const hkFloat32* r);
	HK_FORCE_INLINE void loadNotAligned(const hkFloat32* r);
	HK_FORCE_INLINE void loadNotCached(const hkFloat32* r);
	/// Convert from SIMD-friendly storage and store contiguous to memory \a rOut = aeim
	HK_FORCE_INLINE void store(hkFloat32* rOut) const;
	HK_FORCE_INLINE void storeNotAligned(hkFloat32* rOut) const;
	HK_FORCE_INLINE void storeNotCached(hkFloat32* rOut) const;

	/// Set to a constant vector.
	template<int vectorConstant> HK_FORCE_INLINE void setConstant();

	/// Read scalars non-contiguous from memory using addresses \a base + (m * byteAddressIncrement) and convert to SIMD-friendly storage
	template <hkUint32 byteAddressIncrement> HK_FORCE_INLINE void gather(const hkFloat32* base);
	/// Read scalars non-linear indexed from memory using addresses \a base + ( \a indices[m] * byteAddressIncrement) and convert to SIMD-friendly storage
	template <hkUint32 byteAddressIncrement> HK_FORCE_INLINE void gather(const hkFloat32* base, const hkUint16* indices);
	/// Read scalars non-linear indexed from memory using addresses \a base + ( \a indices[m] * byteAddressIncrement) and convert to SIMD-friendly storage
	template <hkUint32 byteAddressIncrement> HK_FORCE_INLINE void gather(const hkFloat32* base, const hkInt32* indices);
	/// Read scalars non-linear from memory using addresses \a base[m] + byteAddressOffset and convert to SIMD-friendly storage
	template <hkUint32 byteAddressOffset>    HK_FORCE_INLINE void gatherWithOffset(const void* base[M]);
	/// Read scalars non-contiguous from memory using addresses \a base + (m * byteAddressIncrement) and convert to SIMD-friendly storage
	template <hkUint32 byteAddressIncrement> HK_FORCE_INLINE void gather(const hkHalf* base);

	/// Convert from SIMD-friendly storage and write scalars non-contiguous to memory using addresses \a base + (m * byteAddressIncrement)
	template <hkUint32 byteAddressIncrement> HK_FORCE_INLINE void scatter(hkFloat32* base) const;
	/// Convert from SIMD-friendly storage and write scalars non-linear indexed to memory using addresses \a base + ( \a indices[m] * byteAddressIncrement)
	template <hkUint32 byteAddressIncrement> HK_FORCE_INLINE void scatter(hkFloat32* base, const hkUint16* indices) const;
	/// Convert from SIMD-friendly storage and write scalars non-linear indexed to memory using addresses \a base + ( \a indices[m] * byteAddressIncrement)
	template <hkUint32 byteAddressIncrement> HK_FORCE_INLINE void scatter(hkFloat32* base, const hkInt32* indices) const;
	/// Convert from SIMD-friendly storage and write scalars non-linear to memory using addresses \a base[m] + byteAddressOffset
	template <hkUint32 byteAddressOffset>    HK_FORCE_INLINE void scatterWithOffset(void* base[M]) const;


	// comparisons
	HK_FORCE_INLINE void less(hkMxVectorfParameter v, hkMxMaskf<M>& mask) const;
	HK_FORCE_INLINE void less(hkMxSinglefParameter v, hkMxMaskf<M>& mask) const;
	HK_FORCE_INLINE void less(hkMxRealfParameter v, hkMxMaskf<M>& mask) const;
	HK_FORCE_INLINE void lessEqual(hkMxVectorfParameter v, hkMxMaskf<M>& mask) const;
	HK_FORCE_INLINE void lessEqual(hkMxSinglefParameter v, hkMxMaskf<M>& mask) const;
	HK_FORCE_INLINE void lessEqual(hkMxRealfParameter v, hkMxMaskf<M>& mask) const;
	HK_FORCE_INLINE void greater(hkMxVectorfParameter v, hkMxMaskf<M>& mask) const;
	HK_FORCE_INLINE void greater(hkMxSinglefParameter v, hkMxMaskf<M>& mask) const;
	HK_FORCE_INLINE void greater(hkMxRealfParameter v, hkMxMaskf<M>& mask) const;
	HK_FORCE_INLINE void greaterEqual(hkMxVectorfParameter v, hkMxMaskf<M>& mask) const;
	HK_FORCE_INLINE void greaterEqual(hkMxSinglefParameter v, hkMxMaskf<M>& mask) const;
	HK_FORCE_INLINE void greaterEqual(hkMxRealfParameter v, hkMxMaskf<M>& mask) const;

	HK_FORCE_INLINE void setSelect(hkMxMaskParameterf mask, hkMxRealfParameter trueValue, hkMxRealfParameter falseValue );
	HK_FORCE_INLINE void setSelect(hkMxMaskParameterf mask, hkMxSinglefParameter trueValue, hkMxRealfParameter falseValue ); // bad interface !
	HK_FORCE_INLINE void setSelect(hkMxMaskParameterf mask, hkMxRealfParameter trueValue, hkMxSinglefParameter falseValue ); // bad interface !

	// no operands
	HK_FORCE_INLINE void sqrt(); // 23 bit, sqrt set 0
	template <hkMathAccuracyMode A, hkMathNegSqrtMode S> HK_FORCE_INLINE void sqrt();

	
	// one operand
	HK_FORCE_INLINE void add(hkMxRealfParameter r);
	HK_FORCE_INLINE void sub(hkMxRealfParameter r);
	HK_FORCE_INLINE void mul(hkMxRealfParameter r);
	HK_FORCE_INLINE void div(hkMxRealfParameter r); // 23 bit, div 0 ignore
	template <hkMathAccuracyMode A, hkMathDivByZeroMode D> HK_FORCE_INLINE void div(hkMxRealfParameter r);
	HK_FORCE_INLINE void setNeg(hkMxRealfParameter r);		

	HK_FORCE_INLINE void setReciprocal(hkMxRealfParameter r); // 23 bit, div 0 ignore
	template <hkMathAccuracyMode A, hkMathDivByZeroMode D> HK_FORCE_INLINE void setReciprocal(hkMxRealfParameter r);

	template <hkMathAccuracyMode A, hkMathNegSqrtMode S> HK_FORCE_INLINE void setSqrtInverse(hkMxRealfParameter r);

	// Zero I-th scalar if the corresponding mask is set.
	HK_FORCE_INLINE void zeroIfTrue(hkMxMaskParameterf mask);
	// Zero I-th scalar if the corresponding mask is not set.
	HK_FORCE_INLINE void zeroIfFalse(hkMxMaskParameterf mask);

	// two operands
	HK_FORCE_INLINE void setAdd(hkMxRealfParameter v0, hkMxRealfParameter v1);
	HK_FORCE_INLINE void setSub(hkMxRealfParameter v0, hkMxRealfParameter v1);
	HK_FORCE_INLINE void setMul(hkMxRealfParameter v0, hkMxRealfParameter v1);
	HK_FORCE_INLINE void setDiv(hkMxRealfParameter v0, hkMxRealfParameter v1); // 23 bit, div 0 ignore
	template <hkMathAccuracyMode A, hkMathDivByZeroMode D> HK_FORCE_INLINE void setDiv(hkMxRealfParameter v0, hkMxRealfParameter v1);
	HK_FORCE_INLINE void setMax(hkMxRealfParameter v0, hkMxRealfParameter v1);
	HK_FORCE_INLINE void setMin(hkMxRealfParameter v0, hkMxRealfParameter v1);

	// mixed operands
	template <int N> HK_FORCE_INLINE void setDot(hkMxVectorfParameter v0, hkMxVectorfParameter v1);
	template <int N> HK_FORCE_INLINE void setDot(hkMxSinglefParameter s, hkMxVectorfParameter v);
	HK_FORCE_INLINE void setDot4xyz1(hkMxVectorfParameter v0, hkMxVectorfParameter v1);
	HK_FORCE_INLINE void setDot4xyz1(hkMxSinglefParameter s, hkMxVectorfParameter v);

	/// Return the I-th scalar by broadcasting it to \a vOut = [i=0]aaaa [i=1]eeee [i=2]iiii [i=3]mmmm
	template <int I> HK_FORCE_INLINE void getAsBroadcast(hkVector4f& vOut) const;
	/// Return the I-th scalar broadcasted as [i=0]aaaa [i=1]eeee [i=2]iiii [i=3]mmmm
	template <int I> HK_FORCE_INLINE const hkVector4f getAsBroadcast() const;

	/// Return the I-th scalar in a SIMD-friendly way.
	template <int I> HK_FORCE_INLINE const hkSimdFloat32 getReal() const;
	/// Set the I-th subscalar to \a r.
	template <int I> HK_FORCE_INLINE void setReal(hkSimdFloat32Parameter r);

	/// Special store method to write to \a vOut = aeim.
	/// Excess components of \a vOut are undefined.
	/// \warning [M:1-4 only] 
	HK_FORCE_INLINE void storePacked(hkVector4f& vOut) const;



	hkMxRealfStorage<M> m_real; ///< The SIMD-friendly scalars.
};

#if defined(HK_COMPILER_HAS_INTRINSICS_IA32)
	#if (HK_SSE_VERSION >= 0x50) && !defined(HK_REAL_IS_DOUBLE)
	#include <Common/Base/Math/Vector/Mx/hkMxReal_AVX.inl>
	#else
	#include <Common/Base/Math/Vector/Mx/hkMxRealf.inl>
	#endif
#else
	#include <Common/Base/Math/Vector/Mx/hkMxRealf.inl>
#endif

// convenient shortcut
typedef hkMxRealf<4>   hk4xRealf;

#endif // HK_MXFLOAT_H

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
