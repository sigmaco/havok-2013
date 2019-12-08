/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_MATH_INTVECTOR_H
#define HK_MATH_INTVECTOR_H

#ifndef HK_MATH_MATH_H
#	error You need to include Common/Base/hkBase.h before this file.
#endif

#	define HK_INT_VECTOR_UNALIGNED_PTR

namespace hkCompileError
{
	template <bool b> struct HK_INT_VECTOR_SUBVECTOR_INDEX_OUT_OF_RANGE;
	template <> struct HK_INT_VECTOR_SUBVECTOR_INDEX_OUT_OF_RANGE<true>{ };

	template <bool b> struct HK_INT_VECTOR_NOT_IMPLEMENTED_FOR_THIS_VECTOR_LENGTH;
	template <> struct HK_INT_VECTOR_NOT_IMPLEMENTED_FOR_THIS_VECTOR_LENGTH<true>{ };

	template <bool b> struct HK_INT_VECTOR_UNSUPPORTED_VECTOR_LENGTH;
	template <> struct HK_INT_VECTOR_UNSUPPORTED_VECTOR_LENGTH<true>{ };

	template <bool b> struct HK_INT_VECTOR_ILLEGAL_VALUE_FOR_IMM_SPLAT;
	template <> struct HK_INT_VECTOR_ILLEGAL_VALUE_FOR_IMM_SPLAT<true>{ };
}
#define HK_INT_VECTOR_SUBINDEX_CHECK HK_COMPILE_TIME_ASSERT2((I>=0)&&(I<4), HK_INT_VECTOR_SUBVECTOR_INDEX_OUT_OF_RANGE)
#define HK_INT_VECTOR_NOT_IMPLEMENTED HK_COMPILE_TIME_ASSERT2(N==0, HK_INT_VECTOR_NOT_IMPLEMENTED_FOR_THIS_VECTOR_LENGTH)
#define HK_INT_VECTOR_UNSUPPORTED_LENGTH_CHECK HK_COMPILE_TIME_ASSERT2((N>0)&&(N<=4), HK_INT_VECTOR_UNSUPPORTED_VECTOR_LENGTH)
#define HK_INT_VECTOR_IMM_SPLAT_VALUE_CHECK HK_COMPILE_TIME_ASSERT2((VALUE>=-16)&&(VALUE<=15), HK_INT_VECTOR_ILLEGAL_VALUE_FOR_IMM_SPLAT)

/*	Endianness, and words such as "left", "right", "head", "tail":

	hkIntVector aims to provide a compatible interface on all platforms, regardless of endian-ness,
	even though some vector units (Xbox360, PS3, other Altivec-based) are big-endian and some (x86)
	are little-endian.

	The hkIntVector API is roughly big-endian (except for type conversions, see below). The elements
	of a vector are referred to by the position in memory they'd have if they were stored out. The
	"left" side of a vector is the one loaded and stored to the *lower* memory address, and the "right"
	side is the one loaded and stored to the *higher* memory address. The "head" is the leftmost half,
	and the "tail" is the rightmost half.

	So, if an aligned array of 8 16-bit numbers is loaded into a vector:
		- the i'th element is array[i]
		- the leftmost element is array[0]
		- the rightmost element in array[7]
		- the head of the vector is array[0..3]
		- the tail of the vector is array[4..7]
		- shifting the entire vector left 32 bits will move array[i] to array[i-2]
		  and put zeros in array[6] and array[7].

	Type conversions are the one place where endianness leaks through. If an operation is done on a
	vector as a vector of 32-bit ints, and later operations are done as if it were a vector of 16-bit
	ints, it is platform-dependant which order the 16-bit ints will appear. When doing operations using
	multiple different types for the same vector, you should use the setConvert* and setCombine* 
	operations to typecast, as they get the correct byteorder on all platforms.
*/

/// Stores four hkUint32 in a SIMD friendly format.
HK_PASS_IN_REG
class hkIntVector
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_MATH, hkIntVector);


		/// Clear
		HK_FORCE_INLINE void setZero();

		// U32
		HK_FORCE_INLINE void setAll(const int& i);


		// Splat Immediate must be -16 >= VALUE <= 15
		template <int VALUE> HK_FORCE_INLINE void splatImmediate32();
		template <int VALUE> HK_FORCE_INLINE void splatImmediate16();
		template <int VALUE> HK_FORCE_INLINE void splatImmediate8(); 

		// other components = 0 U32
		HK_FORCE_INLINE void setFirstComponent(int value);

		// other components untouched U32
		template <int I> HK_FORCE_INLINE void setComponent(int value);
		HK_FORCE_INLINE void setComponent(int componentIdx, int value);

		// U32
		HK_FORCE_INLINE void set(int x, int y, int z, int w);

		// alias getU32
		HK_FORCE_INLINE int getComponent(int I) const;
		template <int I> HK_FORCE_INLINE int getComponent() const;

			/// Load from 16 byte aligned address.
		template <int N> HK_FORCE_INLINE void load(const hkUint32* p);

			/// Load from an unaligned address.
		template <int N> HK_FORCE_INLINE void loadNotAligned(const HK_INT_VECTOR_UNALIGNED_PTR hkUint32* p);

			/// Store to an aligned address
		template <int N> HK_FORCE_INLINE void store(hkUint32* p) const;

		template <int N> HK_FORCE_INLINE void store(hkInt32* p) const { store<N>((hkUint32*)p); }


			/// Store to an unaligned address
		template <int N> HK_FORCE_INLINE void storeNotAligned(hkUint32* p) const;


		/// cast a vector to an int vector. 
		HK_FORCE_INLINE void loadAsFloat32BitRepresentation(const hkVector4f& x);
		/// cast a vector to an int vector. 
		HK_FORCE_INLINE void loadAsFloat32BitRepresentation(const hkVector4d& x);

		/// interpret an int vector as a float vector and convert it to hkFloat32[4]
		HK_FORCE_INLINE void storeAsFloat32BitRepresentation( hkVector4f& out) const;
		/// interpret an int vector as a double vector and convert it to hkDouble64[4]
		HK_FORCE_INLINE void storeAsFloat32BitRepresentation( hkVector4d& out) const;

		/// This stores the ints in the form used by hkVector4f::getInt24W()
		HK_FORCE_INLINE void storeInto24LowerBitsOfReal(hkVector4f& vOut);
		/// This stores the ints in the form used by hkVector4d::getInt24W()
		HK_FORCE_INLINE void storeInto24LowerBitsOfReal(hkVector4d& vOut);

		// U32
		template <int I> HK_FORCE_INLINE void setBroadcast(hkIntVectorParameter v);
		template<int I> HK_FORCE_INLINE void setBroadcast16(hkIntVectorParameter v);
		template<int I> HK_FORCE_INLINE void setBroadcast8(hkIntVectorParameter v);
		
			// Logical Ops
		HK_FORCE_INLINE void setNot( hkIntVectorParameter a );
		HK_FORCE_INLINE void setOr( hkIntVectorParameter a, hkIntVectorParameter b );
		HK_FORCE_INLINE void setAnd( hkIntVectorParameter a, hkIntVectorParameter b ); 
		HK_FORCE_INLINE void setXor( hkIntVectorParameter a, hkIntVectorParameter b );
		HK_FORCE_INLINE void setAndNot( hkIntVectorParameter a, hkIntVectorParameter b );

			// Comparison.

			/// Returns != 0 if the value is negative. This function assumes that x=y=z=w.
		// sign bit compare S32
		HK_FORCE_INLINE hkBool32 isNegativeAssumingAllValuesEqual(  ) const;

		// value compare
		HK_FORCE_INLINE const hkVector4Comparison compareLessThanS32(hkIntVectorParameter b) const;
		HK_FORCE_INLINE const hkVector4Comparison compareEqualS32(hkIntVectorParameter b) const;
		HK_FORCE_INLINE const hkVector4Comparison lessZeroS32() const;
		HK_FORCE_INLINE const hkVector4Comparison greaterZeroS32() const;
		HK_FORCE_INLINE const hkVector4Comparison equalZeroS32() const;
		HK_FORCE_INLINE const hkVector4Comparison greaterEqualS32(hkIntVectorParameter b) const;

		// Will implement these as needed. There are potentially a LOT of functions to implement here
		//HK_FORCE_INLINE void setCompareEqual(32/16/8)( hkIntVectorParameter a, hkIntVectorParameter b );
		//HK_FORCE_INLINE void setCompareLessThan(S/U)(32/16/8)( hkIntVectorParameter a, hkIntVectorParameter b );
		//HK_FORCE_INLINE void setCompareLessThanEqual(S/U)(32/16/8)( hkIntVectorParameter a, hkIntVectorParameter b );
		//HK_FORCE_INLINE void setCompareGreaterThan(S/U)(32/16/8)( hkIntVectorParameter a, hkIntVectorParameter b );
		//HK_FORCE_INLINE void setCompareGreaterThanEqual(S/U)(32/16/8)( hkIntVectorParameter a, hkIntVectorParameter b );

			// Integer arithmetic
		HK_FORCE_INLINE void setSubU16( hkIntVectorParameter a, hkIntVectorParameter b );
		HK_FORCE_INLINE void setAddU16( hkIntVectorParameter a, hkIntVectorParameter b );

		HK_FORCE_INLINE void setAddU32( hkIntVectorParameter a, hkIntVectorParameter b );
		HK_FORCE_INLINE void setSubU32( hkIntVectorParameter a, hkIntVectorParameter b );

		/// you need to check HK_INT_VECTOR_ADD64_AVAILABLE if there is a fast version of this available
		HK_FORCE_INLINE void setAddU64( hkIntVectorParameter a, hkIntVectorParameter b );
		HK_FORCE_INLINE void setSubU64( hkIntVectorParameter a, hkIntVectorParameter b );

		// Will implement these as needed. 
		//HK_FORCE_INLINE void setAddSaturate(S/U)(32/16/8)( hkIntVectorParameter a, hkIntVectorParameter b ) 
		//HK_FORCE_INLINE void setSubSaturate(S/U)(32/16/8)( hkIntVectorParameter a, hkIntVectorParameter b ) 
		HK_FORCE_INLINE void setAddSaturateU32( hkIntVectorParameter a, hkIntVectorParameter b );
		HK_FORCE_INLINE void setAddSaturateS16( hkIntVectorParameter a, hkIntVectorParameter b );
		HK_FORCE_INLINE void setAddSaturateU16( hkIntVectorParameter a, hkIntVectorParameter b );
		HK_FORCE_INLINE void setSubSaturateU32( hkIntVectorParameter a, hkIntVectorParameter b );
		HK_FORCE_INLINE void setSubSaturateS16( hkIntVectorParameter a, hkIntVectorParameter b );
		HK_FORCE_INLINE void setSubSaturateU16( hkIntVectorParameter a, hkIntVectorParameter b );
		HK_FORCE_INLINE void setAddS32( hkIntVectorParameter a, hkIntVectorParameter b );
		HK_FORCE_INLINE void setSubS32( hkIntVectorParameter a, hkIntVectorParameter b );



			// Min / Max
		//HK_FORCE_INLINE void setMin(S/U)(32/16/8)( hkIntVectorParameter a, hkIntVectorParameter b ) 
		HK_FORCE_INLINE void setMinU8( hkIntVectorParameter a, hkIntVectorParameter b ) ;
		HK_FORCE_INLINE void setMinS32( hkIntVectorParameter a, hkIntVectorParameter b );
		HK_FORCE_INLINE void setMaxS32( hkIntVectorParameter a, hkIntVectorParameter b );
		HK_FORCE_INLINE void setMinS16( hkIntVectorParameter a, hkIntVectorParameter b );
		HK_FORCE_INLINE void setMaxS16( hkIntVectorParameter a, hkIntVectorParameter b );

			// Logical Rotate / Shift
		//HK_FORCE_INLINE void setShiftLeft(32/16/8)( hkIntVectorParameter a, int shift );
		//HK_FORCE_INLINE void setShiftRight(32/16/8)( hkIntVectorParameter a, int shift );
		//HK_FORCE_INLINE void setRotateLeft(32/16/8)( hkIntVectorParameter a, int shift );
		//HK_FORCE_INLINE void setRotateRight(32/16/8)( hkIntVectorParameter a, int shift );

		// immediate bit shift
		template <int shift> HK_FORCE_INLINE void setShiftLeft16( hkIntVectorParameter a );
		template <int shift> HK_FORCE_INLINE void setShiftRight16( hkIntVectorParameter a );
		template <int shift> HK_FORCE_INLINE void setShiftLeft32( hkIntVectorParameter a );
		template <int shift> HK_FORCE_INLINE void setShiftRight32( hkIntVectorParameter a );

		/// immediate byte shift: 		qu[i] = qa[i + shift];
		template <int shift> HK_FORCE_INLINE void setShiftLeft128( hkIntVectorParameter a );
		template <int shift> HK_FORCE_INLINE void setShiftRight128( hkIntVectorParameter a );

		/// arithmetic (sign-preserving) shift right
		template<int shift> HK_FORCE_INLINE void setShiftRightS32( hkIntVectorParameter a );
		template<int shift> HK_FORCE_INLINE void setShiftRightS16( hkIntVectorParameter a );

		// shift by an integer
		HK_FORCE_INLINE void setShiftLeft16( hkIntVectorParameter a, int shift);
		HK_FORCE_INLINE void setShiftLeft32( hkIntVectorParameter a, int shift);
		HK_FORCE_INLINE void setShiftRight16( hkIntVectorParameter a, int shift);
		HK_FORCE_INLINE void setShiftRight32( hkIntVectorParameter a, int shift);

		/// Shift an entire vector left or right by a number of bits specified in shiftSplat.
		/// shiftSplat must contain the shift count in all 16 of its 8-bit elements, or the results
		/// are undefined.
		HK_FORCE_INLINE void setBitShiftLeft128(hkIntVectorParameter a, hkIntVectorParameter shiftSplat);
		HK_FORCE_INLINE void setBitShiftRight128(hkIntVectorParameter a, hkIntVectorParameter shiftSplat);

		// different shifts per component
 		HK_FORCE_INLINE void setShiftLeft16( hkIntVectorParameter a, hkIntVectorParameter shift );
		HK_FORCE_INLINE void setShiftRightS16( hkIntVectorParameter a, hkIntVectorParameter shift );
		HK_FORCE_INLINE void setShiftLeft32( hkIntVectorParameter a, hkIntVectorParameter shift );
		HK_FORCE_INLINE void setShiftRight32( hkIntVectorParameter a, hkIntVectorParameter shift );


		// Merge 

		/// interleave XY components of a and b. Result = { a.X, b.X, a.Y, b.Y }
		HK_FORCE_INLINE void setMergeHead32( hkIntVectorParameter a, hkIntVectorParameter b );

		/// interleave ZW components of a and b. Result = { a.Z, b.Z, a.W, b.W }
		HK_FORCE_INLINE void setMergeTail32( hkIntVectorParameter a, hkIntVectorParameter b );

		/// 16bit interleave the front part of a with the front part of b. Second half of a and b is ignored. Result = { a.u16[0], b.u16[0], a.u16[1], b.u16[1], ... a.u16[3], b.u16[3] }
		HK_FORCE_INLINE void setMergeHead16( hkIntVectorParameter a, hkIntVectorParameter b );
		HK_FORCE_INLINE void setMergeTail16( hkIntVectorParameter a, hkIntVectorParameter b );
		HK_FORCE_INLINE void setMergeHead8( hkIntVectorParameter a, hkIntVectorParameter b ); 
		HK_FORCE_INLINE void setMergeTail8( hkIntVectorParameter a, hkIntVectorParameter b ); 


		/// result.u32[i] = highshorts.u16[i]<<16 + lowShorts.u16[i]. highShorts.u16/lowShorts.u16[4..7] are ignored
		HK_FORCE_INLINE void setCombineHead16To32( hkIntVectorParameter highShorts, hkIntVectorParameter lowShorts );
		
		/// result.u32[i] = highshorts.u16[4+i]<<16 + lowShorts.u16[4+i]. highShorts.u16/lowShorts.u16[0..3] are ignored
		HK_FORCE_INLINE void setCombineTail16To32( hkIntVectorParameter highShorts, hkIntVectorParameter lowShorts );

		/// result.u16[i] = highshorts.u8[i]<<16 + lowShorts.u8[i]. highShorts.u8/lowShorts.u8[8..15] are ignored
		HK_FORCE_INLINE void setCombineHead8To16( hkIntVectorParameter highShorts, hkIntVectorParameter lowShorts );

		/// result.u16[i] = highshorts.u8[8+i]<<16 + lowShorts.u8[8+i]. highShorts.u8/lowShorts.u8[0..7] are ignored
		HK_FORCE_INLINE void setCombineTail8To16( hkIntVectorParameter highShorts, hkIntVectorParameter lowShorts );

		/// result.u32[2*i] = (a.u16[i] << 16) | (a.u16[i+1]).
		/// Combine adjacent 16-bit quantities into a 32-bit quantity.
		/// This is a no-op only on big-endian architectures (e.g. PlayStation(R)3, Xbox VMX).
		HK_FORCE_INLINE void setCombine16To32( hkIntVectorParameter a );

		/// Uncombine (pack). Extract the low shorts from a.u32[] and b.u32[].   result.u16[] = { a.u32[0]&0xffff, a.u32[1]&0xffff, ... b.u32[3]&0xffff }.
		/// result.u16[2*i] = (a.u8[i] << 8) | (a.u8[i+1]).
		/// Combine adjacent 8-bit quantities into a 16-bit quantity.
		/// This is a no-op only on big-endian architectures (e.g. PlayStation(R)3, Xbox VMX).
		HK_FORCE_INLINE void setCombine8To16( hkIntVectorParameter a );

		/// result.u32[i] = bytes.u8[i]
		HK_FORCE_INLINE void setSplit8To32( hkIntVectorParameter bytes );


		/// Uncombine (pack). Extract the low shorts from a.u32[] and b.u32[]. result.u16[] = { a.u32[0]&0xffff, a.u32[1]&0xffff, ... b.u32[3]&0xffff }
		HK_FORCE_INLINE void setConvertU32ToU16( hkIntVectorParameter a, hkIntVectorParameter b );

		/// Sets this.u32[i] = (unsigned int)a.u16[i]
		HK_FORCE_INLINE void setConvertLowerU16ToU32(hkIntVectorParameter a);

		/// Sets this.u32[i] = (unsigned int)a.u16[i + 4]
		HK_FORCE_INLINE void setConvertUpperU16ToU32(hkIntVectorParameter a);

		/// convert first 4 16-bit unsigned values to 32-bit unsigned values
		HK_FORCE_INLINE void setConvertHeadU16ToU32( hkIntVectorParameter a );

		/// saturate and cast 8 signed 32bit value to 8 unsigned 16bit shorts.
		HK_FORCE_INLINE void setConvertSaturateS32ToU16( hkIntVectorParameter a, hkIntVectorParameter b );

		/// saturate and cast 8 signed 32bit value to 8 signed 16bit shorts.
		HK_FORCE_INLINE void setConvertSaturateS32ToS16( hkIntVectorParameter a, hkIntVectorParameter b );

		/// saturate and cast 16 signed 16bit value to 16 unsigned bytes.
		HK_FORCE_INLINE void setConvertSaturateS16ToU8( hkIntVectorParameter a, hkIntVectorParameter b );

		/// saturate and convert 16 signed 16bit value to 16 signed bytes.
		/// convert first 4 16-bit signed values to 32-bit signed values
		HK_FORCE_INLINE void setConvertHeadS16ToS32( hkIntVectorParameter a	);

		/// convert last 4 16-bit unsigned values to 32-bit unsigned values
		HK_FORCE_INLINE void setConvertTailU16ToU32( hkIntVectorParameter a );

		/// convert last 4 16-bit signed values to 32-bit signed values
		HK_FORCE_INLINE void setConvertTailS16ToS32( hkIntVectorParameter a	);

		/// sign-extend low 16-bits to 32-bits
		HK_FORCE_INLINE void setSignExtendS16ToS32( hkIntVectorParameter a );


		// U32
		template <hkVectorPermutation::Permutation P> HK_FORCE_INLINE void setPermutation(hkIntVectorParameter v);

		// U32
		HK_FORCE_INLINE void setSelect( hkVector4fComparisonParameter select, hkIntVectorParameter trueValue, hkIntVectorParameter falseValue ); 
		HK_FORCE_INLINE void setSelect( hkVector4dComparisonParameter select, hkIntVectorParameter trueValue, hkIntVectorParameter falseValue ); 
		template<hkVector4ComparisonMask::Mask M> HK_FORCE_INLINE void setSelect( hkIntVectorParameter trueValue, hkIntVectorParameter falseValue );

		// this is only used by Destruction currently
		// mask lower 4 bits = index
		// mask upper 4 bits must be 0
		HK_FORCE_INLINE void setPermuteU8(hkIntVectorParameter a, hkIntVectorParameter mask);
		// mask lower 4 bits = index
		// mask upper 4 bits: 0=a other=b
		HK_FORCE_INLINE void setPermuteU8(hkIntVectorParameter a, hkIntVectorParameter b, hkIntVectorParameter mask);

			// Convert to from fixed point
		HK_FORCE_INLINE void convertU32ToF32( hkVector4f& vOut ) const;
		HK_FORCE_INLINE void convertU32ToF32( hkVector4d& vOut ) const;
		HK_FORCE_INLINE void convertS32ToF32( hkVector4f& vOut ) const; 
		HK_FORCE_INLINE void convertS32ToF32( hkVector4d& vOut ) const; 

		HK_FORCE_INLINE void setConvertF32toU32( hkVector4fParameter vIn );
		HK_FORCE_INLINE void setConvertF32toU32( hkVector4dParameter vIn );
		HK_FORCE_INLINE void setConvertF32toS32( hkVector4fParameter vIn );		
		HK_FORCE_INLINE void setConvertF32toS32( hkVector4dParameter vIn );		

		template <int I> HK_FORCE_INLINE hkUint8  getU8 () const;
		template <int I> HK_FORCE_INLINE hkUint16 getU16() const;
		template <int I> HK_FORCE_INLINE hkUint32 getU32() const;
		HK_FORCE_INLINE hkUint32 getU32(int idx) const; // todo deprecate

		/// Assuming that this = (i0, i1, i2, i3) and v = (v0, v1, v2, v3), the function will set this = (ik, ik, ik, ik)
		/// where k ={0,..., 3} such that vk = max{v0, v1, v2, v3}.
		/// In case of equality, returns last index
		HK_FORCE_INLINE void broadcastComponentAtVectorMax(hkVector4fParameter v);
		HK_FORCE_INLINE void broadcastComponentAtVectorMax(hkVector4dParameter v);

		/// Assuming that this = (i0, i1, i2, i3) and v = (v0, v1, v2, v3), the function will return ik
		/// where k in {0,..., 3} such that vk = max{v0, v1, v2, v3}.
		/// In case of equality, returns last index
		HK_FORCE_INLINE int getComponentAtVectorMax(hkVector4fParameter v) const;
		HK_FORCE_INLINE int getComponentAtVectorMax(hkVector4dParameter v) const;

		/// Get a constant vector.
		template<hkIntVectorConstant vectorConstant>
		HK_FORCE_INLINE static const hkIntVector& HK_CALL getConstant();

		/// Get a constant vector. Use this method only if the constant is not known at compile time.
		HK_FORCE_INLINE static const hkIntVector& HK_CALL getConstant(hkIntVectorConstant constant);

		/// Sets this = abs(v)
		HK_FORCE_INLINE void setAbsS32(hkIntVectorParameter v);

		/// Sets this = sign * v
		HK_FORCE_INLINE void setFlipSignS32(hkIntVectorParameter v, hkVector4ComparisonParameter mask);

		/// Sets this = -v
		template <int I>
		HK_FORCE_INLINE void setNegS32(hkIntVectorParameter v);

		/// Returns the minimum value occurring in N components. ( return min(x,y,z,w) )
		template <int N> HK_FORCE_INLINE int horizontalMinS32() const;

		/// Returns the minimum value occurring in N components. ( return max(x,y,z,w) )
		template <int N> HK_FORCE_INLINE int horizontalMaxS32() const;

		/// Returns the index of the component with the smallest signed value among the first N components.
		/// In case of equality, returns the first component index given X,Y,Z,W ordering.
		template <int N> HK_FORCE_INLINE int getIndexOfMinComponent() const;

		/// Sets this = first N components of v sorted ascending
		template <int N, hkMathSortDir dir>
		HK_FORCE_INLINE void setSortS32(hkIntVectorParameter v);

		/// Returns the dot product of the first N components
		template <int N>
		HK_FORCE_INLINE hkInt64 dot(hkIntVectorParameter v) const;

		/// Returns the sum of the first N components
		template <int N>
		HK_FORCE_INLINE int horizontalAddS32() const;

		/// Returns the xor of the first N components
		template <int N>
		HK_FORCE_INLINE int horizontalXorS32() const;

		/// Sets this = va * vb
		HK_FORCE_INLINE void setMul(hkIntVectorParameter vA, hkIntVectorParameter vB);


			// Add versions with scaling if needed?

 	public:

		HK_ALIGN16( hkQuadUint m_quad );	
};

/// Constants.
/// Example usage:
/// \code
///    static hkIntVectorConstantU32 myconst = HK_INT_VECTOR_CONSTANT_U32(0, 23, 47, 0x432432);
///    ...
///    myvec.setAddU32(myvec, myconst.v)
/// \endcode
union hkIntVectorConstantU32_
{
	hkQuadUintUnion q;
	hkIntVector v;
};
typedef const hkIntVectorConstantU32_ hkIntVectorConstantU32;
union hkIntVectorConstantU16_
{
	hkQuadUshortUnion q;
	hkIntVector v;
};
typedef const hkIntVectorConstantU16_ hkIntVectorConstantU16;
union hkIntVectorConstantU8_
{
	hkQuadUcharUnion q;
	hkIntVector v;
};
typedef const hkIntVectorConstantU8_ hkIntVectorConstantU8;

#define HK_INT_VECTOR_CONSTANT_U32(a,b,c,d) {{{a,b,c,d}}}
#define HK_INT_VECTOR_CONSTANT_U16(a,b,c,d,e,f,g,h) {{{a,b,c,d,e,f,g,h}}}
#define HK_INT_VECTOR_CONSTANT_U8(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p) {{{a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p}}}


/// Constant permutations.
/// Example usage:
/// \code
///    static hkIntVectorPermutation myperm = HK_INT_VECTOR_PERMUTATION_U16(1, 1, 1, 1, 1, 1, 1, 1)
///    ...
///    myvec.setPermuteU8(myvec, myperm.v); // splats element 1 to all positions in vector
/// \endcode
/// There is no HK_INT_VECTOR_PERMUTATION_U32, use setShuffle instead.
/// This will not be fast on platforms not defining HK_INT_VECTOR_NATIVE_PERMUTE
typedef hkIntVectorConstantU8 hkIntVectorPermutation;

#define HK_INT_VECTOR_PERMUTATION_U8(p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15)\
	HK_INT_VECTOR_CONSTANT_U8(p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15)

#define HK_INT_VECTOR_PERMUTATION_U16(p0, p1, p2, p3, p4, p5, p6, p7)\
	HK_INT_VECTOR_CONSTANT_U8((p0)*2,(p0)*2+1,(p1)*2,(p1)*2+1,\
							  (p2)*2,(p2)*2+1,(p3)*2,(p3)*2+1,\
							  (p4)*2,(p4)*2+1,(p5)*2,(p5)*2+1,\
							  (p6)*2,(p6)*2+1,(p7)*2,(p7)*2+1)
#define HK_INT_VECTOR_PERMUTATION_U32(p0, p1, p2, p3)\
	HK_INT_VECTOR_CONSTANT_U8((p0)*4, (p0)*4+1, (p0)*4+2, (p0)*4+3,\
							  (p1)*4, (p1)*4+1, (p1)*4+2, (p1)*4+3,\
							  (p2)*4, (p2)*4+1, (p2)*4+2, (p2)*4+3,\
							  (p3)*4, (p3)*4+1, (p3)*4+2, (p3)*4+3)

#if HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED
#	if defined(HK_COMPILER_HAS_INTRINSICS_IA32)
#		include <Common/Base/Math/Vector/Sse/hkSseIntVector.inl>
#	elif defined(HK_COMPILER_HAS_INTRINSICS_NEON)
#		include <Common/Base/Math/Vector/Neon/hkNeonIntVector.inl>
#	elif defined(HK_PLATFORM_PS3_PPU) || defined(HK_PLATFORM_PS3_SPU)
#		include <Common/Base/Math/Vector/Ps3/hkPs3IntVector.inl>
#	elif defined(HK_PLATFORM_XBOX360)
#		include <Common/Base/Math/Vector/Xbox360/hkXbox360IntVector.inl>
#	else
#		define HK_USING_GENERIC_INT_VECTOR_IMPLEMENTATION
#	endif
#else
#	define HK_USING_GENERIC_INT_VECTOR_IMPLEMENTATION
#endif

#include <Common/Base/Math/Vector/hkIntVector.inl>


#endif //HK_MATH_INTVECTOR_H

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
