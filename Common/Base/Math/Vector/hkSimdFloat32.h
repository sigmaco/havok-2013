/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_MATH_SIMDFLOAT_H
#define HK_MATH_SIMDFLOAT_H

#ifndef HK_MATH_MATH_H
#	error Please include Common/Base/hkBase.h instead of this file.
#endif

// compile time error checking
namespace hkCompileError
{
	template <bool b> struct HK_SIMDFLOAT_TEMPLATE_CONFIGURATION_NOT_IMPLEMENTED;
	template <> struct HK_SIMDFLOAT_TEMPLATE_CONFIGURATION_NOT_IMPLEMENTED<true>{ };

	template <bool b> struct HK_SIMDFLOAT_ILLEGAL_DIMENSION_USED;
	template <> struct HK_SIMDFLOAT_ILLEGAL_DIMENSION_USED<true>{ };

	template <bool b> struct HK_SIMDFLOAT_ILLEGAL_CONSTANT_REQUEST;
	template <> struct HK_SIMDFLOAT_ILLEGAL_CONSTANT_REQUEST<true>{ };
}
#define HK_SIMDFLOAT_DIMENSION_CHECK HK_COMPILE_TIME_ASSERT2(N==1, HK_SIMDFLOAT_ILLEGAL_DIMENSION_USED)
#define HK_SIMDFLOAT_TEMPLATE_CONFIG_NOT_IMPLEMENTED HK_COMPILE_TIME_ASSERT2(A<0, HK_SIMDFLOAT_TEMPLATE_CONFIGURATION_NOT_IMPLEMENTED)


/// \class hkSimdFloat32
///
/// A scalar floating point value. It holds one floating point number according to the
/// definition of hkFloat32. There are optimized SIMD implementations
/// available for several platforms. They use platform specific data structures and
/// code to provide efficient processing. Thus to be portable, nothing should be assumed
/// about the internal layout of the floating point value storage.
///
/// The setFromFloat() and getReal() methods work on ordinary hkFloat32 values. For performance
/// reasons you should only use them when the value needs to be available in
/// an ordinary processor register, because on most
/// platforms this requires leaving the SIMD processing pipeline. Calculations on hkSimdFloat32
/// are much more efficient and combine better with hkVector4f processing. For loading and
/// storing a hkSimdFloat32 from/to memory use the appropriate load() and store() methods which
/// offer aligned access.
///
/// The comparison methods produce compare masks which are compatible with hkVector4f
/// processing. For example, the selection between two hkVector4f can be based on the
/// mask produced by comparing two hkSimdReals.
///
/// Some floating point operations which involve division or square root calculations can be quite
/// slow. The implementation of this class offers improved performance for these operations
/// at the expense of accuracy and handling of denormalized floating point numbers. 
/// We have balanced performance with behavior one expects from a standard math operator,
/// but these methods will in general not behave IEEE compliant like the system math library
/// calls. See the comments on setDiv(), setReciprocal() and similar methods on how they behave.
///
/// If one needs to control the denormals handling, can do with even lower floating point
/// accuracy, or your algorithm requires full IEEE compliant behavior, the vector offers an 
/// advanced interface in the form of member template methods for the division and square
/// root routines. Each has explicit flags for controlling accuracy and denormal handling.
/// The given bit width is the calculated accuracy in the floating point mantissa.
/// The 23Bit versions are almost as precise as the full version (24Bit) but offer
/// a substantial speedup on most platforms because of less strict denorms handling. 
/// The 12Bit versions again offer faster execution with even less precision. Their 
/// usefulness depends on the algorithm at hand. When writing new code, it is 
/// recommended to start with the full precision version and then check whether a 
/// lower precision is acceptable. The template flags for controlling handling of
/// division-by-zero or negative square root arguments offer easy writing of checked
/// fail-safe math code.
///
/// The load() and store() methods do take a template parameter for interface compatibility with
/// hkVector4f. However the template parameter is checked at compile time to be 1.
/// The advanced interface in addition has template methods which take a flag for the
/// alignment of the memory pointer and for the rounding mode to apply in case of storing
/// to a lower precision floating point format.
///
/// \sa hkVector4f hkVector4fComparison hkHalf hkFloat16 hkMathAccuracyMode hkMathDivByZeroMode hkMathNegSqrtMode hkMathIoMode hkMathRoundingMode
HK_PASS_IN_REG 
class hkSimdFloat32
{
public:

	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_MATH, hkSimdFloat32);

#ifndef HK_DISABLE_IMPLICIT_SIMDREAL_FLOAT_CONVERSION
	/// Creates an uninitialized hkSimdFloat32.
	/// Empty constructor required when the conversion constructors is defined.
	HK_FORCE_INLINE hkSimdFloat32() {}

	/// Creates a new hkSimdFloat32 with value \a x.
	HK_FORCE_INLINE hkSimdFloat32(const hkFloat32& x);

	/// Converts self to a floating point value and returns it.
	HK_FORCE_INLINE operator hkFloat32() const;

#endif //DISABLED CONVERSION


	/// Static conversion method to create a hkSimdFloat32 from its platform dependent storage value \a x. ( self.storage = x ).
	/// This method is implemented platform-specific to avoid constructor initialization overhead
	/// or read-modify-write data dependencies which might occur.
	HK_FORCE_INLINE static const hkSimdFloat32 HK_CALL convert(const hkSingleFloat32& x);	

	/// Static conversion method to create a hkSimdFloat32 from hkFloat32 \a x avoiding constructor overhead if possible. ( return hkSimdFloat32(x) )
	HK_FORCE_INLINE static hkSimdFloat32 HK_CALL fromFloat(const hkFloat32& x);

	/// Static conversion method to create a hkSimdFloat32 from hkHalf \a x avoiding constructor overhead if possible. ( return hkSimdFloat32(x) )
	HK_FORCE_INLINE static hkSimdFloat32 HK_CALL fromHalf(const hkHalf& x);

	/// Static conversion method to create a hkSimdFloat32 from hkUint16 \a x avoiding constructor overhead if possible. ( return hkSimdFloat32(x) )
	HK_FORCE_INLINE static hkSimdFloat32 HK_CALL fromUint16(const hkUint16& x);

	/// Static conversion method to create a hkSimdFloat32 from hkUint8 \a x avoiding constructor overhead if possible. ( return hkSimdFloat32(x) )
	HK_FORCE_INLINE static hkSimdFloat32 HK_CALL fromUint8(const hkUint8& x);

	/// Static conversion method to create a hkSimdFloat32 from hkInt32 \a x avoiding constructor overhead if possible. ( return hkSimdFloat32(x) )
	HK_FORCE_INLINE static hkSimdFloat32 HK_CALL fromInt32(const hkInt32& x);

	/// Copies the content from \a v. This operator is register aliasing safe. ( self = v )
	HK_FORCE_INLINE void operator= ( hkSimdFloat32Parameter v );

	/// Sets the value of self to \a x. ( self = x )
	HK_FORCE_INLINE void setFromFloat(const hkFloat32& x);

	/// Sets the value of self to \a x. ( self = x )
	HK_FORCE_INLINE void setFromFloat(const hkDouble64& x);

	/// Expand the value of \a h to full precision and store with self. ( self = hkFloat32(h) )
	HK_FORCE_INLINE void setFromHalf(const hkHalf& h);

	/// Convert the value of \a x to floating point and store with self. ( self = hkFloat32(x) )
	HK_FORCE_INLINE void setFromUint16(const hkUint16& x);

	/// Convert the value of \a x to floating point and store with self. ( self = hkFloat32(x) )
	HK_FORCE_INLINE void setFromUint8(const hkUint8& x);

	/// Convert the value of \a x to floating point and store with self. ( self = hkFloat32(x) )
	HK_FORCE_INLINE void setFromInt32(const hkInt32&  x);

	/// Set the value of self to zero. ( self = 0 )
	HK_FORCE_INLINE void setZero();

	/// Return self as floating point value. ( return self )
	HK_FORCE_INLINE hkFloat32 getReal() const;

	/// Convert the value of self to integer and return it. The integer is
	/// clamped to the valid min/max range of the return type. ( out = int(self) )
	HK_FORCE_INLINE void storeSaturateInt32( hkInt32* out) const;

	/// Convert the value of self to integer and return it. The integer is
	/// clamped to the valid min/max range of the return type. ( out = int(self) )
	HK_FORCE_INLINE void storeSaturateUint16(hkUint16* result) const;

	/// Get a constant value. See the symbols in hkVectorConstant.
	template<int constant>
	HK_FORCE_INLINE static const hkSimdFloat32 HK_CALL getConstant();

	/// Get a constant value. See the symbols in hkVectorConstant.
	/// \remark Use this method only when the constant is not known at compile time.
	HK_FORCE_INLINE static const hkSimdFloat32 HK_CALL getConstant(hkVectorConstant constant);

	/// Set self to the larger of the two values \a a and \a b. ( self = ( a > b ) ? a : b )
	HK_FORCE_INLINE void setMax(  hkSimdFloat32Parameter a, hkSimdFloat32Parameter b );

	/// Set self to the smaller of the two values \a a and \a b. ( self = ( a < b ) ? a : b )
	HK_FORCE_INLINE void setMin(  hkSimdFloat32Parameter a, hkSimdFloat32Parameter b );

	/// Set self to \a a clamped between \a minVal and \a maxVal. ( self = min( maxVal, max(a, minVal) ) ).
	/// Note that if \a a is NAN, the result will be \a maxVal.
	HK_FORCE_INLINE void setClamped( hkSimdFloat32Parameter a, hkSimdFloat32Parameter minVal, hkSimdFloat32Parameter maxVal );

	/// Set self to the absolute value of \a a. ( self = abs(a) )
	HK_FORCE_INLINE void setAbs(  hkSimdFloat32Parameter a );

	/// Set self to the floor-rounded value of \a a. ( self = floor(a) )
	HK_FORCE_INLINE void setFloor(  hkSimdFloat32Parameter a );

	/// Set self to the remainder of the division of \a a and \a b. ( self = fmod(a,b) )
	HK_FORCE_INLINE void setMod(  hkSimdFloat32Parameter a, hkSimdFloat32Parameter b );

	/// Copy the value from \a v while flipping the sign if the value of \a sSign is negative. ( self = ( sSign < 0 ) ? -v : v )
	HK_FORCE_INLINE void setFlipSign(hkSimdFloat32Parameter v, hkSimdFloat32Parameter sSign);

	/// Copy the value from \a v while flipping the sign if the \a mask bits are set. ( self = mask ? -v : v ).
	/// \remark All bits of the \a mask must be set consistently. Partial masks are not allowed.
	HK_FORCE_INLINE void setFlipSign(hkSimdFloat32Parameter v, hkVector4fComparisonParameter mask);
	
	/// Set self to either \a trueValue or \a falseValue depending on \a comp. ( self = comp ? trueValue : falseValue ).
	/// \remark All bits of the \a comp mask must be set consistently. Partial masks are not allowed.
	HK_FORCE_INLINE void setSelect( hkVector4fComparisonParameter comp, hkSimdFloat32Parameter trueValue, hkSimdFloat32Parameter falseValue );

	/// Set self to zero if the \a compareMask is false (this = compareMask ? this : zero).
	HK_FORCE_INLINE void zeroIfFalse( hkVector4fComparisonParameter compareMask );

	/// Set self to zero if the \a compareMask is true (this = compareMask ? zero : this).
	HK_FORCE_INLINE void zeroIfTrue( hkVector4fComparisonParameter compareMask );

	/// Store the floating point value of self to address \a p as double precision value. The pointer \a p must be aligned to the size of hkDouble64.
	/// The rounding is the system default.
	/// \remark Template parameter N needs to be 1. It is there for compatibility with hkVector4f.
	template <int N> HK_FORCE_INLINE void store(  hkDouble64 *p ) const;

	/// Store the floating point value of self to address \a p as single precision value. The pointer \a p must be aligned to the size of hkFloat32.
	/// The rounding is the system default.
	/// \remark Template parameter N needs to be 1. It is there for compatibility with hkVector4f.
	template <int N> HK_FORCE_INLINE void store(  hkFloat32 *p ) const;

	/// Pack and Store the floating point value of self to address \a p. The pointer \a p must be aligned to the size of hkHalf.
	/// The rounding is the system default.
	/// \remark Template parameter N needs to be 1. It is there for compatibility with hkVector4f.
	template <int N> HK_FORCE_INLINE void store(  hkHalf *p ) const;

	/// Pack and store the floating point value of self to address \a p. The pointer \a p must be aligned to the size of hkFloat16.
	/// The rounding is the system default.
	/// \remark Template parameter N needs to be 1. It is there for compatibility with hkVector4f.
	template <int N> HK_FORCE_INLINE void store(  hkFloat16 *p ) const;

	/// Load a double precision floating point value from address \a p. The pointer \a p must be aligned to the size of hkDouble64.
	/// \remark Template parameter N needs to be 1. It is there for compatibility with hkVector4f.
	template <int N> HK_FORCE_INLINE void load(const hkDouble64 *p );

	/// Load a single precision floating point value from address \a p. The pointer \a p must be aligned to the size of hkFloat32.
	/// \remark Template parameter N needs to be 1. It is there for compatibility with hkVector4f.
	template <int N> HK_FORCE_INLINE void load(const hkFloat32 *p );

	/// Load and unpack a floating point value from address \a p. The pointer \a p must be aligned to the size of hkHalf.
	/// \remark Template parameter N needs to be 1. It is there for compatibility with hkVector4f.
	template <int N> HK_FORCE_INLINE void load(const hkHalf *p );

	/// Load and unpack a floating point value from address \a p. The pointer \a p must be aligned to the size of hkFloat16.
	/// \remark Template parameter N needs to be 1. It is there for compatibility with hkVector4f.
	template <int N> HK_FORCE_INLINE void load(const hkFloat16 *p );

	/// Unary negation operator. ( return -self )
	HK_FORCE_INLINE const hkSimdFloat32 operator-() const;

	/// Return the sum of self and \a r. ( return self + r )
	HK_FORCE_INLINE const hkSimdFloat32 operator+ (hkSimdFloat32Parameter r) const;

	/// Return the difference of self and \a r. ( return self - r )
	HK_FORCE_INLINE const hkSimdFloat32 operator- (hkSimdFloat32Parameter r) const;

	/// Return the product of self and \a r. ( return self * r )
	HK_FORCE_INLINE const hkSimdFloat32 operator* (hkSimdFloat32Parameter r) const;

	/// Return the quotient of self divided by \a r. ( return self / r ).
	/// Accuracy: 23 bit, divide-by-0 not checked
	HK_FORCE_INLINE const hkSimdFloat32 operator/ (hkSimdFloat32Parameter r) const;

	/// Add the value of \a a to self. ( self += a )
	HK_FORCE_INLINE void add(hkSimdFloat32Parameter a);

	/// Subtract the value of \a a from self. ( self -= a )
	HK_FORCE_INLINE void sub(hkSimdFloat32Parameter a);

	/// Multiply self with the value of \a a. ( self *= a )
	HK_FORCE_INLINE void mul(hkSimdFloat32Parameter a);

	/// Divide self by the value of \a a. ( self /= a ).
	/// Accuracy: 23 bit, divide-by-0 not checked
	HK_FORCE_INLINE void div(hkSimdFloat32Parameter a);

	/// Set self to the sum of \a a and \a b. ( self = a+b )
	HK_FORCE_INLINE void setAdd(hkSimdFloat32Parameter a, hkSimdFloat32Parameter b);

	/// Set self to the difference of \a a and \a b. ( self = a-b )
	HK_FORCE_INLINE void setSub(hkSimdFloat32Parameter a, hkSimdFloat32Parameter b);

	/// Set self to the product of \a a and \a b. ( self = a*b )
	HK_FORCE_INLINE void setMul(hkSimdFloat32Parameter a, hkSimdFloat32Parameter b);

	/// Set self to the quotient of \a a over \a b. ( self = a/b )
	/// Accuracy: 23 bit, divide-by-0 not checked
	HK_FORCE_INLINE void setDiv(hkSimdFloat32Parameter a, hkSimdFloat32Parameter b);

	/// Add the product of \a a and \a b to self. ( self += a*b )
	HK_FORCE_INLINE void addMul(hkSimdFloat32Parameter a, hkSimdFloat32Parameter b);

	/// Subtract the product of \a a and \a b from self. ( self -= a*b )
	HK_FORCE_INLINE void subMul(hkSimdFloat32Parameter a, hkSimdFloat32Parameter b);

	/// Set self to the sum of \a a with the product of \a b and \a c. ( self = a + b*c )
	HK_FORCE_INLINE void setAddMul(hkSimdFloat32Parameter a, hkSimdFloat32Parameter b, hkSimdFloat32Parameter c);

	/// Set self to the difference of \a a and the product of \a b and \a c. ( self = a - b*c )
	HK_FORCE_INLINE void setSubMul(hkSimdFloat32Parameter a, hkSimdFloat32Parameter b, hkSimdFloat32Parameter c);

	/// this = a.dot<N>(b)
	template <int N> 
	HK_FORCE_INLINE void setDot( hkVector4fParameter a, hkVector4fParameter b );


	/// Sets self to a linear interpolation of the values \a a and \a b.
	/// The parameter \a t specifies the relative position between
	/// \a a and \a b.  With \a t = 0, the value \a a will be returned.
	/// ( self = (1-t)*a + t*b )
	HK_FORCE_INLINE void setInterpolate( hkSimdFloat32Parameter a, hkSimdFloat32Parameter b, hkSimdFloat32Parameter t );


#ifdef HK_DISABLE_OLD_VECTOR4_INTERFACE

	/// Returns true if the value of self is less than the value of \a r. ( return self < r )
	HK_FORCE_INLINE bool operator< (hkSimdFloat32Parameter r) const;

	/// Returns true if the value of self is less or equal to the value of \a r. ( return self <= r )
	HK_FORCE_INLINE bool operator<= (hkSimdFloat32Parameter r) const;

	/// Returns true if the value of self is greater than the value of \a r. ( return self > r )
	HK_FORCE_INLINE bool operator> (hkSimdFloat32Parameter r) const;

	/// Returns true if the value of self is greater or equal to the value of \a r. ( return self >= r )
	HK_FORCE_INLINE bool operator>= (hkSimdFloat32Parameter r) const;

	/// Returns true if the value of self is equal to the value of \a r. ( return self == r )
	HK_FORCE_INLINE bool operator== (hkSimdFloat32Parameter b) const;

	/// Returns true if the value of self is not equal to the value of \a r. ( return self != r )
	HK_FORCE_INLINE bool operator!= (hkSimdFloat32Parameter b) const;

#endif

	/// Sign test whether negative sign is set, in which case true is returned. ( return self <= -0 ).
	/// This includes detecting floating point -0.0 which also returns true. Use the isEqual... methods 
	/// or the overloaded comparison operators to perform arithmetic compares on the value.
	HK_FORCE_INLINE hkBool32 isSignBitSet() const;

	/// Sign test whether negative sign is clear, in which case true is returned. ( return self >= +0 ).
	/// This includes detecting floating point +0.0 which also returns true. Use the isEqual... methods 
	/// or the overloaded comparison operators to perform arithmetic compares on the value.
	HK_FORCE_INLINE hkBool32 isSignBitClear() const;

	/// Returns true if the value of self is less than the value of \a a. ( return self < a )
	HK_FORCE_INLINE hkBool32 isLess(hkSimdFloat32Parameter a) const;

	/// Returns true if the value of self is less than or equal to the value of \a a. ( return self <= a )
	HK_FORCE_INLINE hkBool32 isLessEqual(hkSimdFloat32Parameter a) const;

	/// Returns true if the value of self is greater than the value of \a a. ( return self > a )
	HK_FORCE_INLINE hkBool32 isGreater(hkSimdFloat32Parameter a) const;

	/// Returns true if the value of self is greater than or equal to the value of \a a. ( return self >= a )
	HK_FORCE_INLINE hkBool32 isGreaterEqual(hkSimdFloat32Parameter a) const;

	/// Returns true if the value of self is equal to the value of \a a. ( return self == a )
	HK_FORCE_INLINE hkBool32 isEqual(hkSimdFloat32Parameter a) const;

	/// Returns true if the value of self is not equal to the value of \a a. ( return self != a )
	HK_FORCE_INLINE hkBool32 isNotEqual(hkSimdFloat32Parameter a) const;

	/// Returns true if the value of self is less than zero. ( return self < 0 )
	HK_FORCE_INLINE hkBool32 isLessZero() const;

	/// Returns true if the value of self is less than or equal zero. ( return self <= 0 )
	HK_FORCE_INLINE hkBool32 isLessEqualZero() const;

	/// Returns true if the value of self is greater than zero. ( return self > 0 )
	HK_FORCE_INLINE hkBool32 isGreaterZero() const;

	/// Returns true if the value of self is greater than or equal zero. ( return self >= 0 )
	HK_FORCE_INLINE hkBool32 isGreaterEqualZero() const;

	/// Returns true if the value of self is zero. ( return self == 0 )
	HK_FORCE_INLINE hkBool32 isEqualZero() const;

	/// Returns true if the value of self is not zero. ( return self != 0 )
	HK_FORCE_INLINE hkBool32 isNotEqualZero() const;

	/// Returns true if self contains a valid finite floating point number.
	HK_FORCE_INLINE hkBool32 isOk() const;

	/// Sign test whether negative sign is set, in which case the mask returned is true. ( self <= -0 ).
	/// This includes detecting floating point -0.0 which also returns true. Use the compare methods 
	/// or the overloaded comparison operators to perform arithmetic compares on the value.
	HK_FORCE_INLINE const hkVector4fComparison signBitSet() const;

	/// Sign test whether negative sign is clear, in which case the mask returned is true. ( self >= +0 ).
	/// This includes detecting floating point +0.0 which also returns true. Use the compare methods 
	/// or the overloaded comparison operators to perform arithmetic compares on the value.
	HK_FORCE_INLINE const hkVector4fComparison signBitClear() const;

	/// Compare the value of self less than the value of \a a. ( self < a )
	HK_FORCE_INLINE const hkVector4fComparison less(hkSimdFloat32Parameter a) const;

	/// Compare the value of self less than or equal the value of \a a. ( self <= a )
	HK_FORCE_INLINE const hkVector4fComparison lessEqual(hkSimdFloat32Parameter a) const;

	/// Compare the value of self greater than the value of \a a. ( self > a )
	HK_FORCE_INLINE const hkVector4fComparison greater(hkSimdFloat32Parameter a) const;

	/// Compare the value of self greater than or equal the value of \a a. ( self >= a )
	HK_FORCE_INLINE const hkVector4fComparison greaterEqual(hkSimdFloat32Parameter a) const;

	/// Compare the value of self equal to the value of \a a. ( self == a )
	HK_FORCE_INLINE const hkVector4fComparison equal(hkSimdFloat32Parameter a) const;

	/// Compare the value of self not equal to the value of \a a. ( self != a )
	HK_FORCE_INLINE const hkVector4fComparison notEqual(hkSimdFloat32Parameter a) const;

	/// Compare the value of self less than zero. ( self < 0 )
	HK_FORCE_INLINE const hkVector4fComparison lessZero() const;

	/// Compare the value of self less than or equal zero. ( self <= 0 )
	HK_FORCE_INLINE const hkVector4fComparison lessEqualZero() const;

	/// Compare the value of self greater than zero. ( self > 0 )
	HK_FORCE_INLINE const hkVector4fComparison greaterZero() const;

	/// Compare the value of self greater than or equal zero. ( self >= 0 )
	HK_FORCE_INLINE const hkVector4fComparison greaterEqualZero() const;

	/// Compare the value of self equal to zero. ( self == 0 )
	HK_FORCE_INLINE const hkVector4fComparison equalZero() const;

	/// Compare the value of self not equal to zero. ( self != 0 )
	HK_FORCE_INLINE const hkVector4fComparison notEqualZero() const;

	/// Compares self to \a v and returns true if the difference is within \a epsilon range (exclusive). ( self > v-epsilon && self < v+epsilon )
	HK_FORCE_INLINE bool approxEqual(hkSimdFloat32Parameter v, hkSimdFloat32Parameter epsilon) const;

	/// Return the square root value of self. ( return sqrt(self) ).
	/// Accuracy: 23 bit, negative values checked and set to zero
	HK_FORCE_INLINE const hkSimdFloat32 sqrt() const;

	/// Return the inverse square root of self. ( return 1/sqrt(self) ).
	/// Accuracy: 23 bit, negative values checked and set to zero, divide-by-0 checked and set to zero
	HK_FORCE_INLINE const hkSimdFloat32 sqrtInverse() const;

	/// Set self to the reciprocal value of \a a. ( self = 1/a ).
	/// Accuracy: 23 bit, divide-by-0 not checked
	HK_FORCE_INLINE void setReciprocal(hkSimdFloat32Parameter a);

	/// Returns the reciprocal value of self.
	/// Accuracy: 23 bit, divide-by-0 not checked
	HK_FORCE_INLINE const hkSimdFloat32 reciprocal() const;


#ifndef HK_DISABLE_OLD_VECTOR4_INTERFACE

	// old interface methods
	HK_FORCE_INLINE hkVector4fComparison isNegative() const;
	HK_FORCE_INLINE hkVector4fComparison isPositive() const;
	HK_FORCE_INLINE hkBool32 isZero() const;
	HK_FORCE_INLINE hkVector4fComparison compareLessThanZero() const;
	HK_FORCE_INLINE hkVector4fComparison compareGreaterThanZero() const;
	HK_FORCE_INLINE hkVector4fComparison compareLessThan(hkSimdFloat32Parameter a) const;
	HK_FORCE_INLINE hkVector4fComparison compareLessThanEqual(hkSimdFloat32Parameter a) const;
	HK_FORCE_INLINE hkVector4fComparison compareGreaterThan(hkSimdFloat32Parameter a) const;
	HK_FORCE_INLINE hkVector4fComparison compareGreaterThanEqual(hkSimdFloat32Parameter a) const;

#endif


	//
	// advanced interface
	//

	/// Load a double precision floating point value from address \a p.
	/// See the documentation at the template values for the requested behavior.
	/// \remark Template parameter N needs to be 1. It is there for compatibility with hkVector4f.
	template <int N, hkMathIoMode A> HK_FORCE_INLINE void load(const hkDouble64 *p );

	/// Load a single precision floating point value from address \a p.
	/// See the documentation at the template values for the requested behavior.
	/// \remark Template parameter N needs to be 1. It is there for compatibility with hkVector4f.
	template <int N, hkMathIoMode A> HK_FORCE_INLINE void load(const hkFloat32 *p );

	/// Load and unpack a floating point value from address \a p.
	/// See the documentation at the template values for the requested behavior.
	/// \remark Template parameter N needs to be 1. It is there for compatibility with hkVector4f.
	template <int N, hkMathIoMode A> HK_FORCE_INLINE void load(const hkHalf *p );

	/// Load and unpack a floating point value from address \a p.
	/// See the documentation at the template values for the requested behavior.
	/// \remark Template parameter N needs to be 1. It is there for compatibility with hkVector4f.
	template <int N, hkMathIoMode A> HK_FORCE_INLINE void load(const hkFloat16 *p );

	/// Store the floating point value of self to address \a p as a double precision value.
	/// The rounding is the system default.
	/// See the documentation at the template values for the requested behavior.
	/// \remark Template parameter N needs to be 1. It is there for compatibility with hkVector4f.
	template <int N, hkMathIoMode A> HK_FORCE_INLINE void store(  hkDouble64 *p ) const;

	/// Store the floating point value of self to address \a p as a single precision value.
	/// The rounding is the system default.
	/// See the documentation at the template values for the requested behavior.
	/// \remark Template parameter N needs to be 1. It is there for compatibility with hkVector4f.
	template <int N, hkMathIoMode A> HK_FORCE_INLINE void store(  hkFloat32 *p ) const;

	/// Pack and store the floating point value of self to address \a p.
	/// The rounding is the system default.
	/// See the documentation at the template values for the requested behavior.
	/// \remark Template parameter N needs to be 1. It is there for compatibility with hkVector4f.
	template <int N, hkMathIoMode A> HK_FORCE_INLINE void store(  hkHalf *p ) const;

	/// Pack and store the floating point value of self to address \a p.
	/// The rounding is the system default.
	/// See the documentation at the template values for the requested behavior.
	/// \remark Template parameter N needs to be 1. It is there for compatibility with hkVector4f.
	template <int N, hkMathIoMode A> HK_FORCE_INLINE void store(  hkFloat16 *p ) const;

	/// Store the floating point value of self to address \a p as a double precision value.
	/// See the documentation at the template values for the requested behavior.
	/// \remark Template parameter N needs to be 1. It is there for compatibility with hkVector4f.
	template <int N, hkMathIoMode A, hkMathRoundingMode R> HK_FORCE_INLINE void store(  hkDouble64 *p ) const;

	/// Store the floating point value of self to address \a p as a single precision value.
	/// See the documentation at the template values for the requested behavior.
	/// \remark Template parameter N needs to be 1. It is there for compatibility with hkVector4f.
	template <int N, hkMathIoMode A, hkMathRoundingMode R> HK_FORCE_INLINE void store(  hkFloat32 *p ) const;

	/// Pack and store the floating point value of self to address \a p.
	/// See the documentation at the template values for the requested behavior.
	/// \remark Template parameter N needs to be 1. It is there for compatibility with hkVector4f.
	template <int N, hkMathIoMode A, hkMathRoundingMode R> HK_FORCE_INLINE void store(  hkHalf *p ) const;

	/// Pack and store the floating point value of self to address \a p.
	/// See the documentation at the template values for the requested behavior.
	/// \remark Template parameter N needs to be 1. It is there for compatibility with hkVector4f.
	template <int N, hkMathIoMode A, hkMathRoundingMode R> HK_FORCE_INLINE void store(  hkFloat16 *p ) const;

	/// Set self to the reciprocal value of \a a. ( self = 1/a ).
	/// See the documentation at the template values for the requested behavior.
	template <hkMathAccuracyMode A, hkMathDivByZeroMode D> HK_FORCE_INLINE void setReciprocal(hkSimdFloat32Parameter a);

	/// Set self to the quotient of \a a over \a b. ( self = a/b ).
	/// See the documentation at the template values for the requested behavior.
	template <hkMathAccuracyMode A, hkMathDivByZeroMode D> HK_FORCE_INLINE void setDiv(hkSimdFloat32Parameter a, hkSimdFloat32Parameter b);

	/// Divide self by the value of \a a. ( self /= a ).
	/// See the documentation at the template values for the requested behavior.
	template <hkMathAccuracyMode A, hkMathDivByZeroMode D> HK_FORCE_INLINE void div(hkSimdFloat32Parameter a);

	/// Return the square root value of self. ( return sqrt(self) ).
	/// See the documentation at the template values for the requested behavior.
	template <hkMathAccuracyMode A, hkMathNegSqrtMode S> HK_FORCE_INLINE const hkSimdFloat32 sqrt() const;

	/// Return the inverse square root of self. ( return 1/sqrt(self) ).
	/// See the documentation at the template values for the requested behavior.
	template <hkMathAccuracyMode A, hkMathNegSqrtMode S> HK_FORCE_INLINE const hkSimdFloat32 sqrtInverse() const;




	/// Internal data storage for the floating point value (platform dependent).
	/// For writing portable code, nothing can be assumed about the internal layout of the value.
	hkSingleFloat32 m_real;
};

#ifndef HK_DISABLE_OLD_VECTOR4_INTERFACE

// old interface static methods

namespace hkMath
{
	HK_FORCE_INLINE int isNegative(hkSimdFloat32Parameter r0)
	{
		return (r0.getReal()<0)? hkVector4ComparisonMask::MASK_X : 0;
	}

	HK_FORCE_INLINE int isLess( hkSimdFloat32Parameter a, hkSimdFloat32Parameter b)
	{
		hkSimdFloat32 sub = a - b;
		return isNegative( sub );
	}

	HK_FORCE_INLINE int isGreater( hkSimdFloat32Parameter a, hkSimdFloat32Parameter b)
	{
		hkSimdFloat32 sub = b - a;
		return isNegative( sub );
	}
}

// old interface implemented comparisons using implicit casts

HK_FORCE_INLINE hkBool32 operator<( hkSimdFloat32Parameter a, hkSimdFloat32Parameter b)
{
	return a.isLess(b);
}

HK_FORCE_INLINE hkBool32 operator<( hkSimdFloat32Parameter a, hkFloat32 b)
{
	return hkBool32( a.getReal() < b );
}

HK_FORCE_INLINE hkBool32 operator<( hkFloat32 a, hkSimdFloat32Parameter b)
{
	return hkBool32( a < b.getReal() );
}

HK_FORCE_INLINE bool operator<=( hkSimdFloat32Parameter a, hkSimdFloat32Parameter b)
{
	return a.isLessEqual(b);
}

HK_FORCE_INLINE bool operator<=( hkSimdFloat32Parameter a, hkFloat32 b)
{
	return ( a.getReal() <= b );
}

HK_FORCE_INLINE bool operator<=( hkFloat32 a, hkSimdFloat32Parameter b)
{
	return ( a <= b.getReal() );
}

HK_FORCE_INLINE hkBool32 operator>( hkSimdFloat32Parameter a, hkSimdFloat32Parameter b)
{
	return a.isGreater(b);
}

HK_FORCE_INLINE hkBool32 operator>( hkSimdFloat32Parameter a, hkFloat32 b)
{
	return hkBool32( a.getReal() > b );
}

HK_FORCE_INLINE hkBool32 operator>( hkFloat32 a, hkSimdFloat32Parameter b)
{
	return hkBool32( a > b.getReal() );
}

HK_FORCE_INLINE bool operator>=( hkSimdFloat32Parameter a, hkSimdFloat32Parameter b)
{
	return a.isGreaterEqual(b);
}

HK_FORCE_INLINE bool operator>=( hkSimdFloat32Parameter a, hkFloat32 b)
{
	return ( a.getReal() >= b );
}

HK_FORCE_INLINE bool operator>=( hkFloat32 a, hkSimdFloat32Parameter b)
{
	return ( a >= b.getReal() );
}

#endif

#endif //HK_MATH_SIMDFLOAT_H

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
