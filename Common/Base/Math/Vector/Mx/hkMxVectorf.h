/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#ifndef HK_MXVECTORf_H
#define HK_MXVECTORf_H

class hkPackedRealf: public hkVector4f{ };

namespace hkCompileError
{
	template <bool b> struct MX_SUBVECTORf_INDEX_OUT_OF_RANGE;
	template <> struct MX_SUBVECTORf_INDEX_OUT_OF_RANGE<true>{ };

	template <bool b> struct MX_VECTOR4f_SUBVECTOR_INDEX_OUT_OF_RANGE;
	template <> struct MX_VECTOR4f_SUBVECTOR_INDEX_OUT_OF_RANGE<true>{ };

	template <bool b> struct MX_UNKNOWNf_PERMUTATION;
	template <> struct MX_UNKNOWNf_PERMUTATION<true>{ };

	template <bool b> struct MX_NOT_IMPLEMENTEDf_FOR_THIS_VECTOR_LENGTH;
	template <> struct MX_NOT_IMPLEMENTEDf_FOR_THIS_VECTOR_LENGTH<true>{ };

	template <bool b> struct MX_VECTOR4f_UNSUPPORTED_VECTOR_LENGTH;
	template <> struct MX_VECTOR4f_UNSUPPORTED_VECTOR_LENGTH<true>{ };
}
#define HK_MXVECTORf_VECTOR4f_SUBINDEX_CHECK           HK_COMPILE_TIME_ASSERT2((I>=0)&&(I<4), MX_VECTOR4f_SUBVECTOR_INDEX_OUT_OF_RANGE)
#define HK_MXVECTORf_MX_SUBINDEX_CHECK                HK_COMPILE_TIME_ASSERT2((I>=0)&&(I<M), MX_SUBVECTORf_INDEX_OUT_OF_RANGE)
#define HK_MXVECTORf_MX_NOT_IMPLEMENTED               HK_COMPILE_TIME_ASSERT2(M==0, MX_NOT_IMPLEMENTEDf_FOR_THIS_VECTOR_LENGTH)
#define HK_MXVECTORf_VECTOR4f_UNSUPPORTED_LENGTH_CHECK HK_COMPILE_TIME_ASSERT2((N>0)&&(N<=4), MX_VECTOR4f_UNSUPPORTED_VECTOR_LENGTH)

#define hkMxVectorfParameter const hkMxVectorf<M>&
#define hkMxQuaternionfParameter const hkMxQuaternionf<M>&

template <int M> class hkMxRealf;
template <int M> class hkMxMaskf;
template <int M> class hkMxQuaternionf;
#include <Common/Base/Math/Vector/Mx/hkMxRealf.h>
#include <Common/Base/Math/Vector/Mx/hkMxSinglef.h>
#include <Common/Base/Math/Vector/Mx/hkMxMaskf.h>


/// Long vector for vectorized computing (Mx4 vectors).
///
/// This represents M 4-component vectors. In this documentation we use abcd and following letters to
/// refer to one of the 4-component subvectors.
/// Example M=4: layout of the long vector: abcd efgh ijlk mnop
///
/// The purpose of this vector is to implement efficient loop-unrolled algorithms without branching
/// to efficiently use the SIMD processing hardware capabilities.
template <int M>
class hkMxVectorf
{
public:

	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_MATH, hkMxVectorf<M>);

	/// The number of 4-component vectors stored in this vector.
	///
	/// When coding, this value can be retrieved using the class definition as well as from variable instances.
	/// Example: incrementing a loop counter: i += hkMxVectorf<M>::mxLength;.
	/// Example: declaring an array appropriate with same length as a vector: int array[vec_var.mxLength];
	enum { mxLength = M };

#ifndef HK_DISABLE_MATH_CONSTRUCTORS
	/// Default constructor. Does not initialize.
	HK_FORCE_INLINE hkMxVectorf() { }

	/// Set self to replicate \a v: abcd abcd abcd abcd
	HK_FORCE_INLINE explicit hkMxVectorf(hkVector4fParameter v);

	/// Set self to broadcast \a r: aaaa aaaa aaaa aaaa
	HK_FORCE_INLINE explicit hkMxVectorf(hkSimdFloat32Parameter r);

	/// Set self to broadcast \a r: aaaa eeee iiii mmmm
	HK_FORCE_INLINE explicit hkMxVectorf(hkMxRealfParameter r);

#endif

	/// Copies all components from \a v. ( self = v )
	HK_FORCE_INLINE void operator= ( hkMxVectorfParameter v );

	/// Set self to broadcast \a r: aaaa eeee iiii mmmm
	HK_FORCE_INLINE void setBroadcast( hkMxRealfParameter r );

	HK_FORCE_INLINE void setAll( hkSimdFloat32Parameter r );

	/// Read subvectors contiguous from memory as abcd efgh ijkl mnop
	HK_FORCE_INLINE void moveLoad(const hkVector4f* HK_RESTRICT v);

	template<int N>
	HK_FORCE_INLINE void load(const hkFloat32* r);	// load N components of a vector sequential in memory SIMD aligned

	HK_FORCE_INLINE void loadNotAligned(const hkFloat32* r);
	HK_FORCE_INLINE void loadNotCached(const hkFloat32* r);
	/// Store subvectors contiguous to memory \a vOut = abcd efgh ijkl mnop
	HK_FORCE_INLINE void moveStore(hkVector4f* HK_RESTRICT vOut) const;
	HK_FORCE_INLINE void store(hkFloat32* rOut) const;
	HK_FORCE_INLINE void storeNotAligned(hkFloat32* rOut) const;
	HK_FORCE_INLINE void storeNotCached(hkFloat32* rOut) const;

	/// Read N subvector components contiguous from memory. Not loaded components are undefined. 
	/// See the documentation at the template values for the requested IO mode.
	template <hkUint32 byteAddressIncrement, int N, hkMathIoMode A> HK_FORCE_INLINE void load(const hkFloat32* r);
	/// Read N subvector components non-linear from memory using addresses \a base[m] + byteAddressOffset. Not loaded components are undefined.
	/// See the documentation at the template values for the requested IO mode.
	template <hkUint32 byteAddressOffset, int N, hkMathIoMode A> HK_FORCE_INLINE void loadWithOffset(const hkFloat32* r[M]);

	/// Read N subvector components contiguous from memory. Not loaded components are undefined. 
	/// See the documentation at the template values for the requested IO mode.
	template <hkUint32 byteAddressIncrement, int N, hkMathIoMode A> HK_FORCE_INLINE void loadUnpack(const hkHalf* r);
	/// Read N subvector components non-linear from memory using addresses \a base[m] + byteAddressOffset. Not loaded components are undefined.
	/// See the documentation at the template values for the requested IO mode.
	template <hkUint32 byteAddressOffset, int N, hkMathIoMode A> HK_FORCE_INLINE void loadUnpackWithOffset(const hkHalf* r[M]);

	/// Store N subvector components contiguous to memory.
	/// See the documentation at the template values for the requested IO mode.
	template <hkUint32 byteAddressIncrement, int N, hkMathIoMode A> HK_FORCE_INLINE void store(hkFloat32* r) const;
	/// Store N subvector components non-linear to memory using addresses \a base[m] + byteAddressOffset.
	/// See the documentation at the template values for the requested IO mode.
	template <hkUint32 byteAddressOffset, int N, hkMathIoMode A> HK_FORCE_INLINE void storeWithOffset(hkFloat32* r[M]) const;

	/// Store N subvector components contiguous to memory.
	/// See the documentation at the template values for the requested IO and rounding mode.
	template <hkUint32 byteAddressIncrement, int N, hkMathIoMode A, hkMathRoundingMode R> HK_FORCE_INLINE void storePack(hkHalf* r) const;
	/// Store N subvector components non-linear to memory using addresses \a base[m] + byteAddressOffset.
	/// See the documentation at the template values for the requested IO and rounding mode.
	template <hkUint32 byteAddressOffset, int N, hkMathIoMode A, hkMathRoundingMode R> HK_FORCE_INLINE void storePackWithOffset(hkHalf* r[M]) const;



	/// Read subvectors non-contiguous from memory using addresses \a base + (m * byteAddressIncrement)
	template <hkUint32 byteAddressIncrement> HK_FORCE_INLINE void gather(const hkVector4f* base);

	/// Read N subvector components non-contiguous from memory using addresses \a base + (m * byteAddressIncrement)
	template <hkUint32 byteAddressIncrement, int N> HK_FORCE_INLINE void gather(const hkVector4f* base);

	/// Read subvectors non-linear indexed from memory using addresses \a base + ( \a indices[m] * byteAddressIncrement)
	template <hkUint32 byteAddressIncrement> HK_FORCE_INLINE void gather(const hkVector4f* base, const hkUint16* indices);

	/// Read subvectors non-linear indexed from memory using addresses \a base + ( \a indices[m] * byteAddressIncrement)
	template <hkUint32 byteAddressIncrement> HK_FORCE_INLINE void gather(const hkVector4f* base, const hkInt32* indices);

	/// Read subvectors non-linear from memory using addresses \a base[m] + byteAddressOffset
	template <hkUint32 byteAddressOffset> HK_FORCE_INLINE void gatherWithOffset(const void* base[M]);

	/// Read N subvector components non-linear from memory using addresses \a base[m] + byteAddressOffset
	template <hkUint32 byteAddressOffset, int N> HK_FORCE_INLINE void gatherWithOffset(const void* base[M]);
	
	/// Read N subvector components non-linear from memory (hkHalf) using addresses \a base[m] + byteAddressOffset
	template <hkUint32 byteAddressOffset> HK_FORCE_INLINE void gatherHalfsWithOffset(const void* base[M]);

	/// Write subvectors non-contiguous to memory using addresses \a base + (m * byteAddressIncrement)
	template <hkUint32 byteAddressIncrement> HK_FORCE_INLINE void scatter(hkVector4f* base) const;
	/// Write N subvector components non-contiguous to memory using addresses \a base + (m * byteAddressIncrement)
	template <hkUint32 byteAddressIncrement, int N> HK_FORCE_INLINE void scatter(hkVector4f* base) const;
	/// Write subvectors non-linear indexed to memory using addresses \a base + ( \a indices[m] * byteAddressIncrement)
	template <hkUint32 byteAddressIncrement> HK_FORCE_INLINE void scatter(hkVector4f* base, const hkUint16* indices) const;
	/// Write subvectors non-linear indexed to memory using addresses \a base + ( \a indices[m] * byteAddressIncrement)
	template <hkUint32 byteAddressIncrement> HK_FORCE_INLINE void scatter(hkVector4f* base, const hkInt32* indices) const;
	/// Write subvectors non-linear to memory using addresses \a base[m] + byteAddressOffset
	template <hkUint32 byteAddressOffset> HK_FORCE_INLINE void scatterWithOffset(void* base[M]) const;
	/// Write N subvector components non-linear to memory using addresses \a base[m] + byteAddressOffset
	template <hkUint32 byteAddressOffset, int N> HK_FORCE_INLINE void scatterWithOffset(void* base[M]) const;
	
	/// Set the I-th subvector to \a v.
 	template <int I> HK_FORCE_INLINE void setVector(hkVector4fParameter v);

	/// Get the I-th subvector: return [I=0]abcd [I=1]efgh [I=2]ijkl [I=3]mnop
	template <int I> HK_FORCE_INLINE const hkVector4f& getVector() const;

	/// Get the I-th subvector: set \a vOut to [I=0]abcd [I=1]efgh [I=2]ijkl [I=3]mnop
	template <int I> HK_FORCE_INLINE void getVector(hkVector4f& vOut) const;

	/// Take the I-th component from every subvector in \a v and broadcast within the subvector only. Example: [I=1] gives bbbb ffff jjjj nnnn
	template <int I> HK_FORCE_INLINE void setScalarBroadcast(hkMxVectorfParameter v);

	// no operands
	HK_FORCE_INLINE void setZero();
	/// Set component I in every subvector to zero.
	template <int I> HK_FORCE_INLINE void zeroComponent();

	template <int N> HK_FORCE_INLINE void normalize(); // 23bit, sqrt set 0
	template <int N, hkMathAccuracyMode A, hkMathNegSqrtMode S> HK_FORCE_INLINE void normalize();

	// one operand
	HK_FORCE_INLINE void add(hkMxVectorfParameter v);
	HK_FORCE_INLINE void sub(hkMxVectorfParameter v);
	HK_FORCE_INLINE void mul(hkMxVectorfParameter v);
	HK_FORCE_INLINE void setXYZ(hkMxVectorfParameter v);
	HK_FORCE_INLINE void setW(hkMxVectorfParameter v);
	template <int N> HK_FORCE_INLINE void setNeg(hkMxVectorfParameter v0);
	HK_FORCE_INLINE void setAbs(hkMxVectorfParameter v0);
	HK_FORCE_INLINE void setSqrtInverse( hkMxVectorfParameter v ); // 23 bit, sqrt set 0
	template <hkMathAccuracyMode A, hkMathNegSqrtMode S> HK_FORCE_INLINE void setSqrtInverse( hkMxVectorfParameter v );

	// two operands
	HK_FORCE_INLINE void setAdd(hkMxVectorfParameter v0, hkMxVectorfParameter v1);
	HK_FORCE_INLINE void setSub(hkMxVectorfParameter v0, hkMxVectorfParameter v1);

	HK_FORCE_INLINE void setMul(hkMxVectorfParameter v0, hkMxVectorfParameter v1);
	HK_FORCE_INLINE void setMul(hkMxVectorfParameter v, hkMxSinglefParameter s);
	HK_FORCE_INLINE void setMul(hkMxRealfParameter v, hkMxSinglefParameter s);
	HK_FORCE_INLINE void setMul(hkMxRealfParameter v, hkMxVectorfParameter s);

	HK_FORCE_INLINE void setDiv(hkMxVectorfParameter v0, hkMxVectorfParameter v1);

	HK_FORCE_INLINE void setRotatedDir(hkMxQuaternionfParameter v0, hkMxVectorfParameter v1);
	HK_FORCE_INLINE void setRotatedInverseDir(hkMxQuaternionfParameter v0, hkMxVectorfParameter v1);

	template <hkMathAccuracyMode A, hkMathDivByZeroMode D> HK_FORCE_INLINE void setDiv(hkMxVectorfParameter v0, hkMxVectorfParameter v1);
	HK_FORCE_INLINE void setCross(hkMxVectorfParameter v0, hkMxVectorfParameter v1);
	HK_FORCE_INLINE void setXYZ_W(hkMxVectorfParameter v0, hkMxVectorfParameter v1);
	HK_FORCE_INLINE void setXYZ_W(hkMxVectorfParameter v0, hkMxRealfParameter v1);
	HK_FORCE_INLINE void setMax(hkMxVectorfParameter v0, hkMxVectorfParameter v1);
	HK_FORCE_INLINE void setMin(hkMxVectorfParameter v0, hkMxVectorfParameter v1);

	HK_FORCE_INLINE void addMul(hkMxVectorfParameter v0, hkMxVectorfParameter v1);
	HK_FORCE_INLINE void addMul(hkMxVectorfParameter v, hkMxSinglefParameter s);
	HK_FORCE_INLINE void addMul(hkMxSinglefParameter v, hkMxSinglefParameter s);
	HK_FORCE_INLINE void addMul(hkMxRealfParameter v, hkMxVectorfParameter s);
	HK_FORCE_INLINE void subMul(hkMxVectorfParameter v0, hkMxVectorfParameter v1);
	HK_FORCE_INLINE void subMul(hkMxVectorfParameter v, hkMxSinglefParameter s);
	HK_FORCE_INLINE void subMul(hkMxSinglefParameter v, hkMxSinglefParameter s);
	HK_FORCE_INLINE void subMul(hkMxRealfParameter v, hkMxVectorfParameter s);
	HK_FORCE_INLINE void setAddMul(hkMxVectorfParameter v0, hkMxVectorfParameter v1, hkMxVectorfParameter v2);
	HK_FORCE_INLINE void setAddMul(hkMxVectorfParameter v0, hkMxVectorfParameter v1, hkMxSinglefParameter v2);


	// three operands
	HK_FORCE_INLINE void setSubMul(hkMxVectorfParameter v0, hkMxVectorfParameter v1, hkMxVectorfParameter v2);


	// one single operand
	HK_FORCE_INLINE void add(hkMxSinglefParameter s);
	HK_FORCE_INLINE void sub(hkMxSinglefParameter s);
	HK_FORCE_INLINE void mul(hkMxSinglefParameter s);
	HK_FORCE_INLINE void setW(hkMxRealfParameter s);
	HK_FORCE_INLINE void setW(hkMxSinglefParameter s);


	// mixed operands

	HK_FORCE_INLINE void mul(hkMxRealfParameter s);


	HK_FORCE_INLINE void setAdd(hkMxVectorfParameter v, hkMxSinglefParameter s);
	HK_FORCE_INLINE void setSub(hkMxVectorfParameter v, hkMxSinglefParameter s);
	HK_FORCE_INLINE void setSub(hkMxSinglefParameter s, hkMxVectorfParameter v);
	HK_FORCE_INLINE void setCross(hkMxVectorfParameter v, hkMxSinglefParameter s);
	HK_FORCE_INLINE void setCross(hkMxSinglefParameter s, hkMxVectorfParameter v);
	HK_FORCE_INLINE void setSubMul(hkMxVectorfParameter v0, hkMxVectorfParameter v1, hkMxSinglefParameter v2);
	HK_FORCE_INLINE void setSubMul(hkMxVectorfParameter v0, hkMxVectorfParameter v1, hkMxRealfParameter   v2);
	HK_FORCE_INLINE void setSubMul(hkMxVectorfParameter v0, hkMxSinglefParameter v1, hkMxRealfParameter   v2);
	HK_FORCE_INLINE void setMax(hkMxVectorfParameter v, hkMxSinglefParameter s);
	HK_FORCE_INLINE void setMin(hkMxVectorfParameter v, hkMxSinglefParameter s);
	HK_FORCE_INLINE void setInterpolate(hkMxVectorfParameter v0, hkMxVectorfParameter v1, hkMxRealfParameter t);


	// comparisons
 	HK_FORCE_INLINE void greater(hkMxVectorfParameter v, hkMxMaskf<M>& mask) const;
	HK_FORCE_INLINE void greater(hkMxSinglefParameter s, hkMxMaskf<M>& mask) const;
 	HK_FORCE_INLINE void less(hkMxVectorfParameter v, hkMxMaskf<M>& mask) const;
	HK_FORCE_INLINE void less(hkMxSinglefParameter s, hkMxMaskf<M>& mask) const;
 	HK_FORCE_INLINE void lessEqual(hkMxVectorfParameter v, hkMxMaskf<M>& mask) const;
	HK_FORCE_INLINE void lessEqual(hkMxSinglefParameter v, hkMxMaskf<M>& mask) const;
	HK_FORCE_INLINE void greaterEqual(hkMxVectorfParameter v, hkMxMaskf<M>& mask) const;
	HK_FORCE_INLINE void greaterEqual(hkMxSinglefParameter v, hkMxMaskf<M>& mask) const;
 	HK_FORCE_INLINE void equal(hkMxVectorfParameter v, hkMxMaskf<M>& mask) const;
	HK_FORCE_INLINE void equal(hkMxSinglefParameter s, hkMxMaskf<M>& mask) const;
	HK_FORCE_INLINE void notEqual(hkMxVectorfParameter v, hkMxMaskf<M>& mask) const;
	HK_FORCE_INLINE void notEqual(hkMxSinglefParameter s, hkMxMaskf<M>& mask) const;

	HK_FORCE_INLINE void setSelect(hkMxMaskParameterf mask, hkMxVectorfParameter trueValue, hkMxVectorfParameter falseValue );
	HK_FORCE_INLINE void setSelect(hkMxMaskParameterf mask, hkMxSinglefParameter trueValue, hkMxVectorfParameter falseValue );
	HK_FORCE_INLINE void setSelect(hkMxMaskParameterf mask, hkMxVectorfParameter trueValue, hkMxSinglefParameter falseValue );

	/// Set to a constant vector.
	template<int vectorConstant> HK_FORCE_INLINE void setConstant();

	/// Add up all subvectors
	HK_FORCE_INLINE void reduceAdd( hkVector4f& addOut ) const;

	/// Work on every subvector and return a scalar vector of same length as self
	template <int N> HK_FORCE_INLINE void length( hkMxRealf<M>& lensOut ) const; // 23 bit, sqrt set 0
	template <int N, hkMathAccuracyMode A, hkMathNegSqrtMode S> HK_FORCE_INLINE void length( hkMxRealf<M>& lensOut ) const;
	template <int N> HK_FORCE_INLINE void lengthSquared( hkMxRealf<M>& lensOut ) const;
	template <int N> HK_FORCE_INLINE void lengthInverse( hkMxRealf<M>& lensOut ) const; // 23 bit, sqrt set 0
	template <int N, hkMathAccuracyMode A, hkMathNegSqrtMode S> HK_FORCE_INLINE void lengthInverse( hkMxRealf<M>& lensOut ) const;
	template <int N> HK_FORCE_INLINE void dot(hkMxSinglefParameter v, hkMxRealf<M>& dotsOut ) const;
	template <int N> HK_FORCE_INLINE void dot(hkMxVectorfParameter v, hkMxRealf<M>& dotsOut ) const;

	/// Set self to a permutation of \a v. It is required that self and \a v are non-overlapping.
	template <hkMxVectorPermutation::Permutation P> HK_FORCE_INLINE void setVectorPermutation(hkMxVectorfParameter v);

	/// Set each compenent of self to a permutation of \a v. 
	template <hkVectorPermutation::Permutation P> HK_FORCE_INLINE void setComponentPermutation(hkMxVectorfParameter v);

	/// Check whether xyz components of all subvectors are ok.
	/// \warning Expensive function. Use for debugging purposes only.
	template <int N> HK_FORCE_INLINE hkBool32 isOk() const;


	// special methods, which do not exist for all mx lengths
	// return value of special methods

	/// Transpose self and store into \a matrix4. Unused subvectors are assumed zero.
	/// \warning [M:1-4 only] 
	HK_FORCE_INLINE void storeTransposed4(hkMatrix4f& matrix4) const;

	/// Add \a v0 to \a v1 scaled by one component of \a v2. Unused subvectors or components are assumed zero. Example: self[1] = v0[1] + (v1[1] * v2.y)
	/// \warning [M:1-4 only] 
	HK_FORCE_INLINE void setAddMul(hkMxVectorfParameter v0, hkMxVectorfParameter v1, hkVector4fParameter v2); 

	/// Add up all components of each subvector and store into \a addsOut. Unused subvectors or components are assumed zero.
	/// \a addsOut = xyzw with x=a+b+c+d, y=e+f+g+h, z=i+j+k+l, w=m+n+o+p
	/// \warning [M:1-4 only] 
	template <int N> HK_FORCE_INLINE void horizontalAdd( hkVector4f& addsOut ) const; 

	/// Add up all components of each subvector and store into \a addsOut. Unused subvectors or components are assumed zero.
	/// \a addsOut = xyzw with x=a+b+c+d, y=e+f+g+h, z=i+j+k+l, w=m+n+o+p
	/// \warning [M:1 only] 
	template <int N> HK_FORCE_INLINE void horizontalAdd( hkSimdFloat32& addsOut ) const; 

	/// Calc minimum on every subvector and store into \a minsOut = xyzw with x=min(abcd) y=min(efgh) z=min(ijkl) w=min(mnop)
	/// \warning [M:1-4 only] 
	template <int N> HK_FORCE_INLINE void horizontalMin( hkVector4f& minsOut ) const;

	/// Calc maximum on every subvector and store into \a maxsOut = xyzw with x=max(abcd) y=max(efgh) z=max(ijkl) w=max(mnop)
	/// \warning [M:1-4 only] 
	template <int N> HK_FORCE_INLINE void horizontalMax( hkVector4f& maxsOut ) const;

	/// Set each subvector of self to a broadcast value of one of the components of \a v: abcd=x efgh=y ijkl=z mnop=w
	/// creating the same data that a hkMxRealf holds virtually
	/// \warning [M:1-4 only] 
	HK_FORCE_INLINE void setAsBroadcast( hkVector4fParameter v );

	HK_FORCE_INLINE void setAll( const hkPackedRealf& v ){ setAsBroadcast( v ); }
	

	hkMxVectorfStorage<M> m_vec; ///< The subvectors.
};

#if defined(HK_COMPILER_HAS_INTRINSICS_IA32)
	#if (HK_SSE_VERSION >= 0x50)
	#include <Common/Base/Math/Vector/Mx/hkMxVector_AVX.inl>
	#else
	#include <Common/Base/Math/Vector/Mx/hkMxVectorf.inl>
	#endif
#else
	#include <Common/Base/Math/Vector/Mx/hkMxVectorf.inl>
#endif

// convenient shortcuts
typedef hkMxVectorf<4> hk4xVector4f;


#endif // HK_MXVECTORf_H

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
