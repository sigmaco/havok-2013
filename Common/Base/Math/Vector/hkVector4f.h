/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_MATH_VECTOR4f_H
#define HK_MATH_VECTOR4f_H

#ifndef HK_MATH_MATH_H
#	error Please include Common/Base/hkBase.h instead of this file.
#endif

// compile time error checking
namespace hkCompileError
{
	template <bool b> struct HK_VECTOR4f_TEMPLATE_CONFIGURATION_NOT_IMPLEMENTED;
	template <> struct HK_VECTOR4f_TEMPLATE_CONFIGURATION_NOT_IMPLEMENTED<true>{ };

	template <bool b> struct HK_VECTOR4f_SUBVECTOR_INDEX_OUT_OF_RANGE;
	template <> struct HK_VECTOR4f_SUBVECTOR_INDEX_OUT_OF_RANGE<true>{ };

	template <bool b> struct HK_VECTOR4f_NOT_IMPLEMENTED_FOR_THIS_VECTOR_LENGTH;
	template <> struct HK_VECTOR4f_NOT_IMPLEMENTED_FOR_THIS_VECTOR_LENGTH<true>{ };

	template <bool b> struct HK_VECTOR4f_UNSUPPORTED_VECTOR_LENGTH;
	template <> struct HK_VECTOR4f_UNSUPPORTED_VECTOR_LENGTH<true>{ };
}
#define HK_VECTOR4f_SUBINDEX_CHECK           HK_COMPILE_TIME_ASSERT2((I>=0)&&(I<4), HK_VECTOR4f_SUBVECTOR_INDEX_OUT_OF_RANGE)
#define HK_VECTOR4f_NOT_IMPLEMENTED          HK_COMPILE_TIME_ASSERT2(N==0, HK_VECTOR4f_NOT_IMPLEMENTED_FOR_THIS_VECTOR_LENGTH)
#define HK_VECTOR4f_UNSUPPORTED_LENGTH_CHECK HK_COMPILE_TIME_ASSERT2((N>0)&&(N<=4), HK_VECTOR4f_UNSUPPORTED_VECTOR_LENGTH)
#define HK_VECTOR4f_TEMPLATE_CONFIG_NOT_IMPLEMENTED HK_COMPILE_TIME_ASSERT2(A<0, HK_VECTOR4f_TEMPLATE_CONFIGURATION_NOT_IMPLEMENTED)

/// \class hkVector4f
///
/// A four component vector. It holds four floating point numbers according to the
/// definition of hkFloat32. There are optimized SIMD implementations
/// available for several platforms. They use platform specific data structures and
/// code to provide efficient processing. Thus to be portable, nothing should be assumed
/// about the internal layout of the four floating point numbers.
///
/// The vector has several methods which take a template parameter for the number of
/// components to work on, for example dot<3>. This guarantees to be able to use
/// optimized implementations for the method as well as using the vector as a 3-component
/// point or a 4-component homogeneous vector which can be verified at compile time.
///
/// Methods for component access or component modification are declared both taking
/// a template argument or an integer index (broadcast() for example). Using the template
/// parameter version is preferred because it allows for compile time address calculation.
/// Use the integer index version only if the index is not known at compile time.
///
/// For accessing the contents of a vector, it is strongly recommended to use the
/// get/setComponent methods as they operate with hkSimdFloat32 which in turn has
/// efficient methods for performing arithmetic and other operations which avoid
/// leaving the SIMD processing pipeline. Using the operator() is only useful for
/// debugging or explicit storage purposes.
///
/// The methods which take a matrix and a vector to transform are available both
/// as forced inline (with _ prefix) or as out-of-line calls. The inline versions produce
/// faster code because of better interleaving of instructions but can bloat the
/// code considerably. In situations where code size matters, use the out-of-line versions.
///
/// Some floating point operations which involve division or square root calculations can be quite
/// slow. The implementations in this class offer improved performance for these operations
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
/// The load() and store() methods take as a template argument the number of components to load/store.
/// The advanced interface in addition has template methods which take a flag for the
/// alignment of the memory pointer and for the rounding mode to apply in case of storing
/// to a lower precision floating point format.
///
/// \sa hkSimdFloat32 hkVector4fComparison hkHalf hkFloat16 hkMathAccuracyMode hkMathDivByZeroMode hkMathNegSqrtMode hkMathIoMode hkMathRoundingMode
HK_PASS_IN_REG
class hkVector4f
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_MATH, hkVector4f);
		HK_DECLARE_POD_TYPE();

#ifndef HK_DISABLE_MATH_CONSTRUCTORS
		/// Empty constructor.
		HK_FORCE_INLINE hkVector4f() { }

		/// Creates a new hkVector4f from the specified three or four values, with the obvious definition. ( self = xyzw )
		HK_FORCE_INLINE hkVector4f(hkFloat32 x, hkFloat32 y, hkFloat32 z, hkFloat32 w=hkFloat32(0));

		/// Creates a new hkVector4f, copying all 4 values from \a q. ( self = q ).
		/// \warning This is a platform dependent operation.
		explicit HK_FORCE_INLINE hkVector4f(const hkQuadFloat32& q);


		/// Creates a new hkVector4f, copying all 4 values from \a v. ( self.xyzw = v.xyzw ).
		/// \warning This constructor causes the compiler NOT to pass const hkVector4f's by register.
		HK_FORCE_INLINE hkVector4f( const hkVector4f& v);
#endif

		/// \name Vector initialization
		///@{

		/// Sets all components from \a v. This operator is register aliasing safe. ( self = v )
		HK_FORCE_INLINE void operator= ( hkVector4fParameter v );

		/// Sets the components of self using the specified four values. Each parameter \a a, \a b, \a c and \a d is stored into
		/// one component in sequence. ( self = abcd )
		HK_FORCE_INLINE void set( hkSimdFloat32Parameter a, hkSimdFloat32Parameter b, hkSimdFloat32Parameter c, hkSimdFloat32Parameter d );

		/// Sets the components of self using the specified three or four values, with the obvious definition. ( self = xyzw )
		HK_FORCE_INLINE void set(hkFloat32 x, hkFloat32 y, hkFloat32 z, hkFloat32 w=hkFloat32(0));

		/// Sets all components of self to the same value \a x. ( self = xxxx )
		HK_FORCE_INLINE void setAll(hkSimdFloat32Parameter x);

		/// Sets all components of self to the same value \a x. ( self = xxxx )
		HK_FORCE_INLINE void setAll(const hkFloat32& x);

		/// Sets all components to zero. ( self = 0000 )
		HK_FORCE_INLINE void setZero();

		/// Set component I to zero. ( self[I] = 0 )
		template <int I> HK_FORCE_INLINE void zeroComponent();

		/// Set component \a i to zero. ( self[i] = 0 ).
		/// \remark Use this method only if the component index is not a compile time constant.
		HK_FORCE_INLINE void zeroComponent(const int i);

		///@}

		/// \name Vector calc methods
		///@{

		/// Component-wise addition of \a a. ( self += a )
		HK_FORCE_INLINE void add(hkVector4fParameter a);

		/// Component-wise subtraction of \a a. ( self -= a )
		HK_FORCE_INLINE void sub(hkVector4fParameter a);

		/// Component-wise multiplication with \a a. ( self *= a )
		HK_FORCE_INLINE void mul(hkVector4fParameter a);

		/// Component-wise division by \a a. ( self /= a )
		/// Accuracy: 23 bit, divide-by-0 not checked
		HK_FORCE_INLINE void div(hkVector4fParameter a);

		/// Set self to the component-wise sum of \a a and \a b. ( self = a+b )
		HK_FORCE_INLINE void setAdd(hkVector4fParameter a, hkVector4fParameter b);

		/// Set self to the component-wise difference of \a a and \a b. ( self = a-b )
		HK_FORCE_INLINE void setSub(hkVector4fParameter a, hkVector4fParameter b);

		/// Set self to the component-wise product of \a a and \a b. ( self = a*b )
		HK_FORCE_INLINE void setMul(hkVector4fParameter a, hkVector4fParameter b);

		/// Set self to the component-wise quotient of \a a over \a b. ( self = a/b ).
		/// Accuracy: 23 bit, divide-by-0 not checked
		HK_FORCE_INLINE void setDiv(hkVector4fParameter a, hkVector4fParameter b);



		/// Multiply each component of self with \a a. ( self *= a )
		HK_FORCE_INLINE void mul(hkSimdFloat32Parameter a);

		/// Set self to the vector \a a with each component multiplied by \a r. ( self = a*r )
		HK_FORCE_INLINE void setMul(hkVector4fParameter a, hkSimdFloat32Parameter r);

		/// Set self to the vector \a a with each component multiplied by \a r. ( self = a*r )
		HK_FORCE_INLINE void setMul(hkSimdFloat32Parameter r, hkVector4fParameter a);

		/// Set self to the component-wise reciprocal of \a v. ( self = 1/v ).
		/// Accuracy: 23 bit, divide-by-0 not checked
		HK_FORCE_INLINE void setReciprocal(hkVector4fParameter v);

		/// Set self to the component-wise square root of \a a. ( self = sqrt(a) ).
		/// Accuracy: 23 bit, negative values of \a a checked and set to zero
		HK_FORCE_INLINE void setSqrt(hkVector4fParameter a);

		/// Set self component-wise to one over square root of \a a. ( self = 1/sqrt(a) ).
		/// Accuracy: 23 bit, negative values of \a a checked and set to zero, divide-by-0 checked and set to zero
		HK_FORCE_INLINE void setSqrtInverse(hkVector4fParameter a);




		/// Component-wise add the product of \a a and \a b to self. ( self += a*b )
		HK_FORCE_INLINE void addMul(hkVector4fParameter a, hkVector4fParameter b);

		/// Set self to the component-wise sum of \a a with the product of \a b and \a c. ( self = a + b*c )
		HK_FORCE_INLINE void setAddMul(hkVector4fParameter a, hkVector4fParameter b, hkVector4fParameter c);

		/// Component-wise subtract the product of \a a and \a b from self. ( self -= a*b )
		HK_FORCE_INLINE void subMul(hkVector4fParameter a, hkVector4fParameter b);

		/// Set self to the component-wise difference of \a a with the product of \a b and \a c. ( self = a - b*c )
		HK_FORCE_INLINE void setSubMul(hkVector4fParameter a, hkVector4fParameter b, hkVector4fParameter c);

		/// Component-wise add the product of \a a and \a r. ( self += a*r )
		HK_FORCE_INLINE void addMul(hkVector4fParameter a, hkSimdFloat32Parameter r);

		/// Component-wise add the product of \a a and \a r. ( self += a*r )
		HK_FORCE_INLINE void addMul(hkSimdFloat32Parameter r, hkVector4fParameter a);

		/// Component-wise subtract the product of \a a and \a r. ( self -= a*r )
		HK_FORCE_INLINE void subMul(hkVector4fParameter a, hkSimdFloat32Parameter r);

		/// Component-wise subtract the product of \a a and \a r. ( self -= a*r )
		HK_FORCE_INLINE void subMul(hkSimdFloat32Parameter r, hkVector4fParameter a);

		/// Set self to the component-wise sum of \a a and the product of \a b and \a r. ( self = a + b*r )
		HK_FORCE_INLINE void setAddMul(hkVector4fParameter a, hkVector4fParameter b, hkSimdFloat32Parameter r);

		/// Set self to the component-wise difference of \a a and the product of \a b and \a r. ( self = a - b*r )
		HK_FORCE_INLINE void setSubMul(hkVector4fParameter a, hkVector4fParameter b, hkSimdFloat32Parameter r);

		/// Sets self to the cross product of \a a and \a b. ( self = a cross b )
		HK_FORCE_INLINE void setCross( hkVector4fParameter a, hkVector4fParameter b );

		/// Sets self to a linear interpolation of the vectors \a a and \a b.
		/// The parameter \a t specifies the relative position along the line segment defined by
		/// \a a and \a b.  With \a t = 0, the start of the line segment - the point \a a - will be returned.
		/// ( self = (1-t)*a + t*b )
		HK_FORCE_INLINE void setInterpolate( hkVector4fParameter a, hkVector4fParameter b, hkSimdFloat32Parameter t );

		///@}

		/// \name Comparisons by-value and selection
		///@{

		/// Component-wise compare self less than \a a. ( self < a )
		HK_FORCE_INLINE const hkVector4fComparison less(hkVector4fParameter a) const;

		/// Component-wise compare self less than or equal to \a a. ( self <= a )
		HK_FORCE_INLINE const hkVector4fComparison lessEqual(hkVector4fParameter a) const;

		/// Component-wise compare self greater than \a a. ( self > a )
		HK_FORCE_INLINE const hkVector4fComparison greater(hkVector4fParameter a) const;

		/// Component-wise compare self greater than or equal \a a. ( self >= a )
		HK_FORCE_INLINE const hkVector4fComparison greaterEqual(hkVector4fParameter a) const;

		/// Component-wise compare self equal to \a a. ( self == a )
		HK_FORCE_INLINE const hkVector4fComparison equal(hkVector4fParameter a) const;

		/// Component-wise compare self not equal to \a a. ( self != a )
		HK_FORCE_INLINE const hkVector4fComparison notEqual(hkVector4fParameter a) const;

		/// Component-wise compare self less than zero. ( self < 0 )
		HK_FORCE_INLINE const hkVector4fComparison lessZero() const;

		/// Component-wise compare self less than or equal zero. ( self <= 0 )
		HK_FORCE_INLINE const hkVector4fComparison lessEqualZero() const;

		/// Component-wise compare self greater than zero. ( self > 0 )
		HK_FORCE_INLINE const hkVector4fComparison greaterZero() const;

		/// Component-wise compare self greater than or equal zero. ( self >= 0 )
		HK_FORCE_INLINE const hkVector4fComparison greaterEqualZero() const;

		/// Component-wise compare self equal to zero. ( self == 0 )
		HK_FORCE_INLINE const hkVector4fComparison equalZero() const;

		/// Component-wise compare self not equal to zero. ( self != 0 )
		HK_FORCE_INLINE const hkVector4fComparison notEqualZero() const;

		/// Component-wise sign test whether negative sign is set, in which case the corresponding flag in the returned mask is set to true. ( self <= -0 ).
		/// This includes detecting floating point -0.0 which also returns true. Use the compare methods to perform arithmetic
		/// compares on the floating point value.
		HK_FORCE_INLINE const hkVector4fComparison signBitSet() const;

		/// Component-wise sign test whether negative sign is clear, in which case the corresponding flag in the returned mask is set to true. ( self >= +0 ).
		/// This includes detecting floating point +0.0 which also returns true. Use the compare methods to perform arithmetic
		/// compares on the floating point value.
		HK_FORCE_INLINE const hkVector4fComparison signBitClear() const;

		/// Compares the first N components of self to themselves and returns true if all the components are the same. ( self.x == ... == self.N )
		template <int N> HK_FORCE_INLINE hkBool32 allComponentsEqual() const;

		/// Compares the first N components of self to \a v and returns true if all the components are the same respective value. ( self == v )
		template <int N> HK_FORCE_INLINE hkBool32 allExactlyEqual(hkVector4fParameter v) const;

		/// Compares the first N components of self to zero and returns true if all the components are zero. ( self == 0 )
		template <int N> HK_FORCE_INLINE hkBool32 allExactlyEqualZero() const;

		/// Compares the first N components of self to \a v and returns true if all the differences of all components are within \a epsilon range (exclusive). ( self > v-epsilon && self < v+epsilon ).
		/// \remark This is not the Euclidean epsilon distance.
		template <int N> HK_FORCE_INLINE hkBool32 allEqual(hkVector4fParameter v, hkSimdFloat32Parameter epsilon) const;

		/// Compares the first N components of self to zero and returns true if all the differences of all components are within \a epsilon range (exclusive). ( self > -epsilon && self < +epsilon ).
		/// \remark This is not the Euclidean epsilon distance.
		template <int N> HK_FORCE_INLINE hkBool32 allEqualZero(hkSimdFloat32Parameter epsilon) const;

		/// Compares the first N components and returns true if all the components of self are less than the components of \a a. ( self < a )
		template <int N> HK_FORCE_INLINE hkBool32 allLess(hkVector4fParameter a) const;

		/// Compares the first N components and returns true if all the components of self are less than zero. ( self < 0 )
		template <int N> HK_FORCE_INLINE hkBool32 allLessZero() const;

		/// Component-wise select values from \a trueValue or \a falseValue depending on whether
		/// the component is marked true or false in the \a compareMask. ( self = mask ? trueValue : falseValue )
		HK_FORCE_INLINE void setSelect( hkVector4fComparisonParameter compareMask, hkVector4fParameter trueValue, hkVector4fParameter falseValue );

		/// Set every component to zero if the corresponding \a compareMask component is false. (this = compareMask ? this : zero)
		HK_FORCE_INLINE void zeroIfFalse( hkVector4fComparisonParameter compareMask );

		/// Set every component to zero if the corresponding \a compareMask component is true. (this = compareMask ? zero : this)
		HK_FORCE_INLINE void zeroIfTrue( hkVector4fComparisonParameter compareMask );

		/// Component-wise select values from \a trueValue or \a falseValue depending on whether
		/// the component is marked true or false in the template mask. ( self = mask ? trueValue : falseValue )
		template<hkVector4ComparisonMask::Mask M> HK_FORCE_INLINE void setSelect( hkVector4fParameter trueValue, hkVector4fParameter falseValue );

		///@}

		/// \name Sign and clamping operations
		///@{

		/// Store \a v with self while flipping the signs of the first N components. ( self = N ? -v : v )
		template <int N> HK_FORCE_INLINE void setNeg(hkVector4fParameter v);

		/// Component-wise copy values from \a v while flipping the sign of the value if the corresponding flag in the \a mask is true. ( self = mask ? -v : v )
		HK_FORCE_INLINE void setFlipSign(hkVector4fParameter v, hkVector4fComparisonParameter mask);

		/// Component-wise copy values from \a v while flipping the sign of the value if the corresponding component in \a vSign is negative. ( self = (vSign < 0) ? -v : v )
		HK_FORCE_INLINE void setFlipSign(hkVector4fParameter v, hkVector4fParameter vSign);

		/// Component-wise copy values from \a v while flipping the sign of each value if the scalar value of \a sSign is negative. ( self = (sSign < 0) ? -v : v )
		HK_FORCE_INLINE void setFlipSign(hkVector4fParameter v, hkSimdFloat32Parameter sSign);

		/// Sets the components of self to the absolute value of the components in \a v. ( self = abs(v) )
		HK_FORCE_INLINE void setAbs(hkVector4fParameter v);

		/// Component-wise compare \a a and \a b and store the smaller value to self. ( self = (a < b) ? a : b )
		HK_FORCE_INLINE void setMin(hkVector4fParameter a, hkVector4fParameter b);

		/// Component-wise compare \a a and \a b and store the larger value to self. ( self = (a > b) ? a : b )
		HK_FORCE_INLINE void setMax(hkVector4fParameter a, hkVector4fParameter b);

		/// Component-wise clamp \a a between \a minVal and \a maxVal and store to self. ( self = min( maxVal, max(a, minVal) ) ).
		/// Note that if \a a is NaN, the result will be \a maxVal.
		HK_FORCE_INLINE void setClamped( hkVector4fParameter a, hkVector4fParameter minVal, hkVector4fParameter maxVal );

		/// Sets self to a copy of \a vSrc that is rescaled to have a maximum length of \a maxLen.
		/// If \a vSrc is shorter than \a maxLen, no rescaling is performed.
		HK_FORCE_INLINE void setClampedToMaxLength(hkVector4fParameter vSrc, hkSimdFloat32Parameter maxLen);

		///@}

		/// \name Out-of-line matrix operations
		///@{

		/// Sets self to the vector \a b rotated by matrix \a a.
		void setRotatedDir(const hkMatrix3f& a, hkVector4fParameter b);

		/// Sets self to the vector \a b rotated by the inverse matrix of \a a.
		void setRotatedInverseDir(const hkMatrix3f& a, hkVector4fParameter b);

		/// Sets self to the vector \a b transformed by matrix \a a.
		void setTransformedPos(const hkTransformf& a, hkVector4fParameter b);

		/// Sets self to the vector \a b transformed by the inverse matrix of \a a.
		void setTransformedInversePos(const hkTransformf& a, hkVector4fParameter b);

		/// Sets self to the vector \a direction rotated by the quaternion \a quat.
		void setRotatedDir(hkQuaternionfParameter quat, hkVector4fParameter direction);

		/// Sets self to the vector \a direction rotated by the inverse of quaternion \a quat.
		void setRotatedInverseDir(hkQuaternionfParameter quat, hkVector4fParameter direction);

		/// Sets self to the vector \a b transformed by matrix \a a.
		/// \remark You need to use this method if scale is present.
		void setTransformedPos(const hkQsTransformf& a, hkVector4fParameter b);

		/// Sets self to the vector \a b transformed by the inverse matrix of \a a.
		/// \remark You need to use this method if scale is present.
		void setTransformedInversePos(const hkQsTransformf& a, hkVector4fParameter b);

		/// Sets self to the vector \a b transformed by matrix \a a.
		void setTransformedPos(const hkQTransformf& a, hkVector4fParameter b);

		/// Sets self to the vector \a b transformed by the inverse matrix of \a a.
		void setTransformedInversePos(const hkQTransformf& a, hkVector4fParameter b);

		///@}

		/// \name Forced in-line matrix operations
		///@{

		/// Sets self to the vector \a b rotated by matrix \a a.
		/// This method is enforced inline.
		HK_FORCE_INLINE void _setRotatedDir(const hkMatrix3f& a, hkVector4fParameter b);

		/// Sets self to the vector \a b rotated by the inverse matrix of \a a.
		/// This method is enforced inline.
		HK_FORCE_INLINE void _setRotatedInverseDir(const hkMatrix3f& a, hkVector4fParameter b);

		/// Sets self to the vector \a b transformed by matrix \a a.
		/// This method is enforced inline.
		HK_FORCE_INLINE void _setTransformedPos(const hkTransformf& a, hkVector4fParameter b);

		/// Sets self to the vector \a b transformed by the inverse matrix of \a a.
		/// This method is enforced inline.
		HK_FORCE_INLINE void _setTransformedInversePos(const hkTransformf& a, hkVector4fParameter b);

		/// Sets self to the vector \a b transformed by matrix \a a.
		/// This method is enforced inline.
		/// \remark You need to use this method if scale is present.
		HK_FORCE_INLINE void _setTransformedPos(const hkQsTransformf& a, hkVector4fParameter b);

		/// Sets self to the vector \a b transformed by the inverse matrix of \a a.
		/// This method is enforced inline.
		/// \remark You need to use this method if scale is present.
		HK_FORCE_INLINE void _setTransformedInversePos(const hkQsTransformf& a, hkVector4fParameter b);

		/// Sets self to the vector \a b transformed by matrix \a a.
		/// This method is enforced inline.
		HK_FORCE_INLINE void _setTransformedPos(const hkQTransformf& a, hkVector4fParameter b);

		/// Sets self to the vector \a b transformed by the inverse matrix of \a a.
		/// This method is enforced inline.
		HK_FORCE_INLINE void _setTransformedInversePos(const hkQTransformf& a, hkVector4fParameter b);

		/// Sets self to the vector \a direction rotated by the quaternion \a quat.
		/// This method is enforced inline.
		HK_FORCE_INLINE void _setRotatedDir(hkQuaternionfParameter quat, hkVector4fParameter direction);

		/// Sets self to the vector \a direction rotated by the inverse of quaternion \a quat.
		/// This method is enforced inline.
		HK_FORCE_INLINE void _setRotatedInverseDir(hkQuaternionfParameter quat, hkVector4fParameter direction);

		///@}

		/// \name Length and normalization
		///@{

		/// Returns the dot product of self with \a a represented by N components. ( return self dot a )
		template <int N> HK_FORCE_INLINE const hkSimdFloat32 dot(hkVector4fParameter a) const;

		/// Sets all components of self to the N component dot product of \a a and \a b. ( self = a dot b )
		template <int N> HK_FORCE_INLINE void setDot(hkVector4fParameter a, hkVector4fParameter b);

		/// Sums up N components. ( return x+y+z+w )
		template <int N> HK_FORCE_INLINE const hkSimdFloat32 horizontalAdd() const;

		/// Sums up N components of \a v and stores to all components of self. ( self = v(x+y+z+w) )
		template <int N> HK_FORCE_INLINE void setHorizontalAdd(hkVector4fParameter v);

		/// Product of N components. ( return x*y*z*w )
		template <int N> HK_FORCE_INLINE const hkSimdFloat32 horizontalMul() const;

		/// Product of N components of \a v and stores to all components of self. ( self = v(x*y*z*w) )
		template <int N> HK_FORCE_INLINE void setHorizontalMul(hkVector4fParameter v);

		/// Returns the maximum value occurring in N components. ( return max(x,y,z,w) )
		template <int N> HK_FORCE_INLINE const hkSimdFloat32 horizontalMax() const;

		/// Calculates the maximum value occurring in N components of \a v and stores to all components of self. ( self = v.max(x,y,z,w) )
		template <int N> HK_FORCE_INLINE void setHorizontalMax(hkVector4fParameter v);

		/// Returns the minimum value occurring in N components. ( return min(x,y,z,w) )
		template <int N> HK_FORCE_INLINE const hkSimdFloat32 horizontalMin() const;

		/// Calculates the minimum value occurring in N components of \a v and stores to all components of self. ( self = v.min(x,y,z,w) )
		template <int N> HK_FORCE_INLINE void setHorizontalMin(hkVector4fParameter v);


		/// Returns the length of the vector represented by N of its components. ( return sqrt(self dot self) ).
		/// Accuracy: 23 bit, negative values checked and set to zero
		template <int N> HK_FORCE_INLINE const hkSimdFloat32 length() const;

		/// Returns the squared length of the vector represented by N of its components. ( return (self dot self) )
		template <int N> HK_FORCE_INLINE const hkSimdFloat32 lengthSquared() const;

		/// Returns the inverse length of the vector represented by N of its components. ( return 1 / sqrt(self dot self) ).
		/// Accuracy: 23 bit, negative sqrt values checked and set to zero, divide-by-0 checked and set to zero
		template <int N> HK_FORCE_INLINE const hkSimdFloat32 lengthInverse() const;


		/// Normalizes self as an N-component vector. Unused components in self are undefined afterwards. ( self = |self| ).
		/// Accuracy: 23 bit, negative sqrt values checked and set to zero, divide-by-0 checked and set to zero
		template <int N> HK_FORCE_INLINE void normalize();

		/// Normalizes self as an N-component vector and returns the length of self before normalization. Unused components in self are undefined afterwards. ( return self = |self| ).
		/// Accuracy: 23 bit, negative sqrt values checked and set to zero, divide-by-0 checked and set to zero
		template <int N> HK_FORCE_INLINE const hkSimdFloat32 normalizeWithLength();

		/// Normalizes self as an N-component vector. Unused components in self are undefined afterwards. ( self = |self| ).
		/// If self is the zero vector, no normalization will occur and false is returned, else true.
		/// Accuracy: 23 bit, negative sqrt values checked and set to zero, divide-by-0 checked and set to zero
		template <int N> HK_FORCE_INLINE hkBool32 normalizeIfNotZero();

		/// Normalizes \a v as an N-component vector, stores with self and returns the length of \a v before normalization. ( return self = |v| ).
		/// If \a v is zero (within machine epsilon), self is set to the unit vector (1,0,0,0).
		/// Accuracy: 23 bit.
		template <int N> HK_FORCE_INLINE const hkSimdFloat32 setNormalizedEnsureUnitLength(hkVector4fParameter v);

		///@}

		/// \name Special functionality
		///@{

		/// Set the w component of self to the negative 3-component dot product of \a aPointOnPlane with self. The xyz components of self are unchanged.
		/// ( self.w = -p.dot<3>(self) )
		HK_FORCE_INLINE void setPlaneConstant(hkVector4fParameter aPointOnPlane );

		/// Returns the dot product of self and \a a with the w-component of \a a replaced by 1. ( return self.xyzw dot a.xyz1 )
		HK_FORCE_INLINE const hkSimdFloat32 dot4xyz1(hkVector4fParameter a) const;

		/// Returns the Euclidean distance between self as a point and the point \a p. ( return len(self - p) ).
		/// Accuracy: 23 bit, negative sqrt values checked and set to zero, divide-by-0 checked and set to zero
		HK_FORCE_INLINE const hkSimdFloat32 distanceTo( hkVector4fParameter p ) const;

		/// Returns the squared Euclidean distance between self as a point and the point \a p. ( return len*len(self - p) )
		HK_FORCE_INLINE const hkSimdFloat32 distanceToSquared( hkVector4fParameter p ) const;

		///@}

		/// \name Component access
		///@{

		/// Set the xyz components of self from \a xyz. Set the w component of self from \a w.
		HK_FORCE_INLINE void setXYZ_W(hkVector4fParameter xyz, hkVector4fParameter w);

		/// Set the xyz components of self from \a xyz. Set the w component of self from \a w.
		HK_FORCE_INLINE void setXYZ_W(hkVector4fParameter xyz, hkSimdFloat32Parameter w);

		/// Set the w component of self from \a v. The xyz components are unchanged.
		HK_FORCE_INLINE void setW(hkVector4fParameter v);

		/// Set the w component of self from \a w. The xyz components are unchanged.
		HK_FORCE_INLINE void setW(hkSimdFloat32Parameter w);

		/// Set the xyz components of self from \a v. The w component is unchanged.
		HK_FORCE_INLINE void setXYZ(hkVector4fParameter v);

		/// Set the xyz components of self all to the same value \a v. The w component is unchanged.
		HK_FORCE_INLINE void setXYZ(hkFloat32 v);

		/// Set the xyz components of self all to the same value \a v. The w component is unchanged.
		HK_FORCE_INLINE void setXYZ(hkSimdFloat32Parameter v);

		/// Set the xyz components of self from \a xyz. Set the w component of self to zero.
		HK_FORCE_INLINE void setXYZ_0(hkVector4fParameter xyz);

		/// Add the xyz components of \a v to the xyz components of self. The w component of self is undefined afterwards.
		HK_FORCE_INLINE void addXYZ(hkVector4fParameter v);

		/// Subtract the xyz components of \a v from the xyz components of self. The w component of self is undefined afterwards.
		HK_FORCE_INLINE void subXYZ(hkVector4fParameter v);

		/// Sets value of component \a i of \a v on the xyz components of self. The w component of self is undefined afterwards.
		/// \remark Use this method only if the component index is not a compile time constant.
		HK_FORCE_INLINE void setBroadcastXYZ(const int i, hkVector4fParameter v);

		/// Stores a 24 bit integer value in the w component of self. The integer can be retrieved using the getInt24W() method.
		/// Note for storing negative integers, the sign handling needs to be done prior to using this method.
		/// \warning Using the w component in floating point calculations after this can destroy the integer value and
		///          will most likely produce denormalized floating point numbers.
		HK_FORCE_INLINE void setInt24W( int value );

		/// Returns a 24 bit integer stored in the w component of self. The integer value must have been set with
		/// setInt24W() before.
		HK_FORCE_INLINE int getInt24W( ) const ;

		/// Returns a 16 bit integer stored in the w component of self. The integer value must have been set with
		/// setInt24W() before.
		HK_FORCE_INLINE int getInt16W( ) const ;


		/// Gives read/write access to element i.  (0,1,2,3) correspond to the (x,y,z,w) components respectively.
		/// \remark Use this method only for storage purposes or immediate manipulation when the component index is not a compile time constant.
		HK_FORCE_INLINE hkFloat32& operator() (int i);

		/// Gives read only access to element i.  (0,1,2,3) correspond to the (x,y,z,w) components respectively.
		/// \remark Use this method only for storage purposes when the component index is not a compile time constant.
		HK_FORCE_INLINE const hkFloat32& operator() (int i) const;

		/// Return component I.  (0,1,2,3) correspond to the (x,y,z,w) components respectively.
		template <int I> HK_FORCE_INLINE const hkSimdFloat32 getComponent() const;

		/// Return the w component, short for getComponent<3>()
		HK_FORCE_INLINE const hkSimdFloat32 getW() const;

		/// Return component \a i.  (0,1,2,3) correspond to the (x,y,z,w) components respectively.
		/// \remark Use this method only when the component index is not a compile time constant.
		HK_FORCE_INLINE const hkSimdFloat32 getComponent(const int i) const;

		/// Return address of component I for read only access.  (0,1,2,3) correspond to the (x,y,z,w) components respectively.
		template <int I> HK_FORCE_INLINE const hkFloat32* getComponentAddress() const;

		/// Return address of component I for read/write access.  (0,1,2,3) correspond to the (x,y,z,w) components respectively.
		template <int I> HK_FORCE_INLINE hkFloat32* getComponentAddress();

		/// Return address of component \a i for read only access.  (0,1,2,3) correspond to the (x,y,z,w) components respectively.
		/// \remark Use this method only when the component index is not a compile time constant.
		HK_FORCE_INLINE const hkFloat32* getComponentAddress(int i) const;

		/// Return address of component \a i for read/write access.  (0,1,2,3) correspond to the (x,y,z,w) components respectively.
		/// \remark Use this method only when the component index is not a compile time constant.
		HK_FORCE_INLINE hkFloat32* getComponentAddress(int i);

		/// Sets value of component I.  (0,1,2,3) correspond to the (x,y,z,w) components respectively.
		template <int I> HK_FORCE_INLINE void setComponent(hkSimdFloat32Parameter val);

		/// Sets value of component \a i.  (0,1,2,3) correspond to the (x,y,z,w) components respectively.
		/// \remark Use this method only when the component index is not a compile time constant.
		HK_FORCE_INLINE void setComponent(const int i, hkSimdFloat32Parameter val);

		/// Returns the index of the component for the first occurrence of the exact given \a value among the first N components.
		/// Returns -1 if no component matches. ( return self ?= component )
		template <int N> HK_FORCE_INLINE int findComponent(hkSimdFloat32Parameter value) const;

		/// Set self to a component permutation of \a v. See the symbols in hkVectorPermutation.
		template <hkVectorPermutation::Permutation P> HK_FORCE_INLINE void setPermutation(hkVector4fParameter v);

		/// Set the value of component I of self on all components of self.
		template <int I> HK_FORCE_INLINE void broadcast();

		/// Set the value of component \a i of self on all components of self.
		/// \remark Use this method only when the component index is not a compile time constant.
		HK_FORCE_INLINE void broadcast(int i);

		/// Set the value of component I of \a v on all components of self.
		template <int I> HK_FORCE_INLINE void setBroadcast(hkVector4fParameter v);

		/// Set the value of component \a i of \a v on all components of self.
		/// \remark Use this method only when the component index is not a compile time constant.
		HK_FORCE_INLINE void setBroadcast(const int i, hkVector4fParameter v);

		/// Returns the index of the component with the largest absolute value among the first N components.
		/// In case of equality, returns the last component index given X,Y,Z,W ordering.
		template <int N> HK_FORCE_INLINE int getIndexOfMaxAbsComponent() const;

		/// Returns the index of the component with the largest signed value among the first N components.
		/// In case of equality, returns the last component index given X,Y,Z,W ordering.
	    template <int N> HK_FORCE_INLINE int getIndexOfMaxComponent() const;

		/// Returns the index of the component with the smallest absolute value among the first N components.
		/// In case of equality, returns the first component index given X,Y,Z,W ordering.
		template <int N> HK_FORCE_INLINE int getIndexOfMinAbsComponent() const;

		/// Returns the index of the component with the smallest signed value among the first N components.
		/// In case of equality, returns the first component index given X,Y,Z,W ordering.
		template <int N> HK_FORCE_INLINE int getIndexOfMinComponent() const;

		///@}

		/// \name Checking, loading and storing
		///@{

		/// Returns true if the first N components are valid finite floating point numbers.
		template <int N> HK_FORCE_INLINE hkBool32 isOk() const;

		/// Returns true if the length of self is one within the given \a epsilon bounds.
		template <int N> HK_FORCE_INLINE bool isNormalized(hkFloat32 epsilon = hkFloat32(1e-4f)) const;

		/// Get a constant vector with all components zero.
		HK_FORCE_INLINE static const hkVector4f& HK_CALL getZero();

		/// Get a constant vector. See the symbols in hkVectorConstant.
		template<int vectorConstant>
		HK_FORCE_INLINE static const hkVector4f& HK_CALL getConstant();

		/// Get a constant vector. See the symbols in hkVectorConstant.
		/// \remark Use this method only when the constant is not known at compile time.
		HK_FORCE_INLINE static const hkVector4f& HK_CALL getConstant(hkVectorConstant constant);

		/// Set this vector to a constant.
		template<int vectorConstant>
		HK_FORCE_INLINE void setConstant();

		/// Load double precision floating point values for N components from linear addresses at \a p. Not loaded components are undefined. 
		/// The pointer \a p must be aligned for SIMD operations.
		template <int N> HK_FORCE_INLINE void load(const hkDouble64* p);

		/// Load single precision floating point values for N components from linear addresses at \a p. Not loaded components are undefined. 
		/// The pointer \a p must be aligned for SIMD operations.
		template <int N> HK_FORCE_INLINE void load(const hkFloat32* p);

		/// Load and unpack floating point values for N components from linear addresses at \a p. Not loaded components are undefined.
		/// The pointer \a p must be aligned for SIMD operations.
		template <int N> HK_FORCE_INLINE void load(const hkHalf* p);

		/// Load and unpack floating point values for N components from linear addresses at \a p. Not loaded components are undefined.
		/// The pointer \a p must be aligned for SIMD operations.
		template <int N> HK_FORCE_INLINE void load(const hkFloat16* p);

		/// Store double precision floating point values of N components to linear addresses at \a p.
		/// The rounding is the system default.
		/// The pointer \a p must be aligned for SIMD operations.
		template <int N> HK_FORCE_INLINE void store(hkDouble64* p) const;

		/// Store single precision floating point values of N components to linear addresses at \a p.
		/// The rounding is the system default.
		/// The pointer \a p must be aligned for SIMD operations.
		template <int N> HK_FORCE_INLINE void store(hkFloat32* p) const;

		/// Pack and store floating point values of N components to linear addresses at \a p. 
		/// The rounding is the system default.
		/// The pointer \a p must be aligned for SIMD operations.
		template <int N> HK_FORCE_INLINE void store(hkHalf* p) const;

		/// Pack and store floating point values of N components to linear addresses at \a p. 
		/// The rounding is the system default.
		/// The pointer \a p must be aligned for SIMD operations.
		template <int N> HK_FORCE_INLINE void store(hkFloat16* p) const;

		/// Reduce the precision of self to what it would be when packed into hkHalfs.
		HK_FORCE_INLINE void reduceToHalfPrecision();

		///@}


		/// \name Advanced interface
		///@{

		/// Load double precision floating point values for N components from linear addresses at \a p. Not loaded components are undefined. 
		/// See the documentation at the template values for the requested IO mode.
		template <int N, hkMathIoMode A> HK_FORCE_INLINE void load(const hkDouble64* p);

		/// Load single precision floating point values for N components from linear addresses at \a p. Not loaded components are undefined. 
		/// See the documentation at the template values for the requested IO mode.
		template <int N, hkMathIoMode A> HK_FORCE_INLINE void load(const hkFloat32* p);

		/// Load and unpack floating point values for N components from linear addresses at \a p. Not loaded components are undefined.
		/// See the documentation at the template values for the requested IO mode.
		template <int N, hkMathIoMode A> HK_FORCE_INLINE void load(const hkHalf* p);

		/// Load and unpack floating point values for N components from linear addresses at \a p. Not loaded components are undefined.
		/// See the documentation at the template values for the requested IO mode.
		template <int N, hkMathIoMode A> HK_FORCE_INLINE void load(const hkFloat16* p);

		/// Store double precision floating point values of N components to linear addresses at \a p.
		/// See the documentation at the template values for the requested IO mode.
		template <int N, hkMathIoMode A, hkMathRoundingMode R> HK_FORCE_INLINE void store(hkDouble64* p) const;

		/// Store single precision floating point values of N components to linear addresses at \a p.
		/// See the documentation at the template values for the requested IO mode.
		template <int N, hkMathIoMode A, hkMathRoundingMode R> HK_FORCE_INLINE void store(hkFloat32* p) const;

		/// Pack and store floating point values of N components to linear addresses at \a p. 
		/// See the documentation at the template values for the requested IO mode.
		template <int N, hkMathIoMode A, hkMathRoundingMode R> HK_FORCE_INLINE void store(hkHalf* p) const;

		/// Pack and store floating point values of N components to linear addresses at \a p. 
		/// See the documentation at the template values for the requested IO mode.
		template <int N, hkMathIoMode A, hkMathRoundingMode R> HK_FORCE_INLINE void store(hkFloat16* p) const;

		/// Store double precision floating point values of N components to linear addresses at \a p.
		/// The rounding is the system default.
		/// See the documentation at the template values for the requested IO mode.
		template <int N, hkMathIoMode A> HK_FORCE_INLINE void store(hkDouble64* p) const;

		/// Store single precision floating point values of N components to linear addresses at \a p.
		/// The rounding is the system default.
		/// See the documentation at the template values for the requested IO mode.
		template <int N, hkMathIoMode A> HK_FORCE_INLINE void store(hkFloat32* p) const;

		/// Pack and store floating point values of N components to linear addresses at \a p. 
		/// The rounding is the system default.
		/// See the documentation at the template values for the requested IO mode.
		template <int N, hkMathIoMode A> HK_FORCE_INLINE void store(hkHalf* p) const;

		/// Pack and store floating point values of N components to linear addresses at \a p. 
		/// The rounding is the system default.
		/// See the documentation at the template values for the requested IO mode.
		template <int N, hkMathIoMode A> HK_FORCE_INLINE void store(hkFloat16* p) const;

		/// Set self to the component-wise reciprocal of \a v. ( self = 1/v ).
		/// See the documentation at the template values for the requested behavior.
		template <hkMathAccuracyMode A, hkMathDivByZeroMode D> HK_FORCE_INLINE void setReciprocal(hkVector4fParameter v);

		/// Set self to the component-wise quotient of \a a over \a b. ( self = a/b ).
		/// See the documentation at the template values for the requested behavior.
		template <hkMathAccuracyMode A, hkMathDivByZeroMode D> HK_FORCE_INLINE void setDiv(hkVector4fParameter a, hkVector4fParameter b);

		/// Component-wise division by \a a. ( self /= a ).
		/// See the documentation at the template values for the requested behavior.
		template <hkMathAccuracyMode A, hkMathDivByZeroMode D> HK_FORCE_INLINE void div(hkVector4fParameter a);

		/// Set self to the component-wise square root of \a a. ( self = sqrt(a) ).
		/// See the documentation at the template values for the requested behavior.
		template <hkMathAccuracyMode A, hkMathNegSqrtMode S> HK_FORCE_INLINE void setSqrt(hkVector4fParameter a);

		/// Set self component-wise to one over square root of \a a. ( self = 1/sqrt(a) ).
		/// See the documentation at the template values for the requested behavior.
		template <hkMathAccuracyMode A, hkMathNegSqrtMode S> HK_FORCE_INLINE void setSqrtInverse(hkVector4fParameter a);

		/// Returns the length of the vector represented by N of its components. ( return sqrt(self dot self) ).
		/// See the documentation at the template values for the requested behavior.
		template <int N, hkMathAccuracyMode A, hkMathNegSqrtMode S> HK_FORCE_INLINE const hkSimdFloat32 length() const;

		/// Returns the inverse length of the vector represented by N of its components. ( return 1 / sqrt(self dot self) ).
		/// See the documentation at the template values for the requested behavior.
		template <int N, hkMathAccuracyMode A, hkMathNegSqrtMode S> HK_FORCE_INLINE const hkSimdFloat32 lengthInverse() const;

		/// Normalizes self as an N-component vector. Unused components in self are undefined afterwards. ( self = |self| ).
		/// See the documentation at the template values for the requested behavior.
		template <int N, hkMathAccuracyMode A, hkMathNegSqrtMode S> HK_FORCE_INLINE void normalize();

		/// Normalizes self as an N-component vector and returns the length of self before normalization. Unused components in self are undefined afterwards. ( return self = |self| ).
		/// See the documentation at the template values for the requested behavior.
		template <int N, hkMathAccuracyMode A, hkMathNegSqrtMode S> HK_FORCE_INLINE const hkSimdFloat32 normalizeWithLength();

		/// Normalizes self as an N-component vector. Unused components in self are undefined afterwards. ( self = |self| ).
		/// If self is the zero vector, no normalization will occur and false is returned, else true.
		/// See the documentation at the template values for the requested behavior.
		template <int N, hkMathAccuracyMode A, hkMathNegSqrtMode S> HK_FORCE_INLINE hkBool32 normalizeIfNotZero();

		/// Returns the Euclidean distance between self as a point and the point \a p. ( return len(self - p) ).
		/// See the documentation at the template values for the requested behavior.
		template <hkMathAccuracyMode A, hkMathNegSqrtMode S> HK_FORCE_INLINE const hkSimdFloat32 distanceTo( hkVector4fParameter p ) const;

		/// Normalizes \a v as an N-component vector, stores with self and returns the length of \a v before normalization. ( return self = |v| ).
		/// If \a v is zero (within machine epsilon), self is set to the unit vector (1,0,0,0).
		/// See the documentation at the template values for the requested behavior.
		template <int N, hkMathAccuracyMode A> HK_FORCE_INLINE const hkSimdFloat32 setNormalizedEnsureUnitLength(hkVector4fParameter v);

		///@}


		/// Internal data storage of the vector components (platform dependent).
		/// For writing portable code, nothing can be assumed about the internal layout of the values.
		HK_ALIGN_FLOAT( hkQuadFloat32 m_quad );	


#ifndef HK_DISABLE_OLD_VECTOR4_INTERFACE

		//
		// old interface
		//

		HK_FORCE_INLINE hkQuadFloat32& getQuad();
		HK_FORCE_INLINE const hkQuadFloat32& getQuad() const;
		HK_FORCE_INLINE void operator= ( const hkQuadFloat32& v );
		HK_FORCE_INLINE void add4(hkVector4fParameter v);
		HK_FORCE_INLINE void sub4(hkVector4fParameter v);
		HK_FORCE_INLINE void mul4(hkVector4fParameter a);
		HK_FORCE_INLINE void mul4(hkSimdFloat32Parameter a);
		HK_FORCE_INLINE void div4(hkVector4fParameter a);
		HK_FORCE_INLINE void div4fast(hkVector4fParameter a);
		HK_FORCE_INLINE hkSimdFloat32 dot3(hkVector4fParameter v) const;
		HK_FORCE_INLINE hkSimdFloat32 dot4(hkVector4fParameter a) const;
		HK_FORCE_INLINE hkFloat32 dot3fpu(hkVector4fParameter a) const;
		HK_FORCE_INLINE void setMul4(hkVector4fParameter a, hkVector4fParameter b);
		HK_FORCE_INLINE void setMul4(hkSimdFloat32Parameter a, hkVector4fParameter b);
		HK_FORCE_INLINE void _setMul3(const hkMatrix3f& m, hkVector4fParameter v);
		HK_FORCE_INLINE void setMul3(const hkMatrix3f& a, hkVector4fParameter b );
		HK_FORCE_INLINE void subMul4(hkVector4fParameter a, hkVector4fParameter b);
		HK_FORCE_INLINE void subMul4(hkSimdFloat32Parameter a, hkVector4fParameter b);
		HK_FORCE_INLINE void setSubMul4(hkVector4fParameter a, hkVector4fParameter x, hkVector4fParameter y);
		HK_FORCE_INLINE void setSubMul4(hkVector4fParameter a, hkVector4fParameter x, hkSimdFloat32Parameter y);
		HK_FORCE_INLINE void setDot3(hkVector4fParameter a, hkVector4fParameter b);
		HK_FORCE_INLINE void setDot4(hkVector4fParameter a, hkVector4fParameter b);
		HK_FORCE_INLINE void setSelect4( hkVector4fComparisonParameter comp, hkVector4fParameter trueValue, hkVector4fParameter falseValue);
		HK_FORCE_INLINE void select32( hkVector4fParameter falseValue, hkVector4fParameter trueValue, hkVector4fComparisonParameter comp);
		HK_FORCE_INLINE void setBroadcast(hkVector4fParameter v, int i);
		HK_FORCE_INLINE void setBroadcast3clobberW(hkVector4fParameter v, int i);
		HK_FORCE_INLINE void setXYZW(hkVector4fParameter xyz, hkVector4fParameter w);
		HK_FORCE_INLINE void setXYZW(hkVector4fParameter xyz, hkSimdFloat32Parameter w);
		HK_FORCE_INLINE void setXYZ0(hkVector4fParameter xyz);
		HK_FORCE_INLINE void addMul4(hkVector4fParameter a, hkVector4fParameter b);
		HK_FORCE_INLINE void addMul4(hkSimdFloat32Parameter a, hkVector4fParameter b);
		HK_FORCE_INLINE void setZero4();
		HK_FORCE_INLINE void zeroElement( int i );
		HK_FORCE_INLINE void setAll3(hkFloat32 x);
		HK_FORCE_INLINE void setSwapXY(const hkVector4f& x);
		HK_FORCE_INLINE void setNeg3(hkVector4fParameter v);
		HK_FORCE_INLINE void setNeg4(hkVector4fParameter v);
		HK_FORCE_INLINE void setNegMask4(hkVector4fParameter v, int mask);
		HK_FORCE_INLINE void setDiv4(hkVector4fParameter a, hkVector4fParameter b);
		HK_FORCE_INLINE void setDiv4fast(hkVector4fParameter a, hkVector4fParameter b);
		HK_FORCE_INLINE hkSimdFloat32 getSimdAt(int i) const;
		HK_FORCE_INLINE void normalize3();
		HK_FORCE_INLINE void normalize4();
		HK_FORCE_INLINE void fastNormalize3();
		HK_FORCE_INLINE void setFastNormalize3NonZero(hkVector4fParameter other);
		HK_FORCE_INLINE hkSimdFloat32 normalizeWithLength3();
		HK_FORCE_INLINE hkSimdFloat32 normalizeWithLength4();
		HK_FORCE_INLINE hkSimdFloat32 fastNormalizeWithLength3();
		HK_FORCE_INLINE void fastNormalize3NonZero();
		HK_FORCE_INLINE hkResult normalize3IfNotZero ();
		HK_FORCE_INLINE hkBool isNormalized3(hkFloat32 eps = 1e-4f) const;
		HK_FORCE_INLINE hkBool isNormalized4(hkFloat32 eps = 1e-4f) const;
		HK_FORCE_INLINE hkSimdFloat32 length3() const;
		HK_FORCE_INLINE hkSimdFloat32 length4() const;
		HK_FORCE_INLINE hkSimdFloat32 lengthSquared3() const;
		HK_FORCE_INLINE hkSimdFloat32 lengthSquared4() const;
		HK_FORCE_INLINE hkSimdFloat32 lengthInverse3() const;
		HK_FORCE_INLINE hkSimdFloat32 lengthInverse4() const;
		HK_FORCE_INLINE void setMulSigns4(hkVector4fParameter a, hkVector4fParameter signs);
		HK_FORCE_INLINE void setMulSigns4(hkVector4fParameter a, hkSimdFloat32Parameter sharedSign);
		HK_FORCE_INLINE void setAdd4(hkVector4fParameter a, hkVector4fParameter b);
		HK_FORCE_INLINE void setSub4(hkVector4fParameter a, hkVector4fParameter b);
		HK_FORCE_INLINE void setSqrtInverse4(hkVector4fParameter v);
		HK_FORCE_INLINE void setSqrtInverse4_7BitAccuracy(hkVector4fParameter v);
		HK_FORCE_INLINE void setReciprocal3(hkVector4fParameter v);
		HK_FORCE_INLINE void setReciprocal4(hkVector4fParameter v);
		HK_FORCE_INLINE void setAddMul4(hkVector4fParameter a, hkVector4fParameter x, hkVector4fParameter y);
		HK_FORCE_INLINE void setAddMul4(hkVector4fParameter a, hkVector4fParameter b, hkSimdFloat32Parameter r);
		HK_FORCE_INLINE void setAbs4(hkVector4fParameter v);
		HK_FORCE_INLINE void setMin4(hkVector4fParameter a, hkVector4fParameter b);
		HK_FORCE_INLINE void setMax4(hkVector4fParameter a, hkVector4fParameter b);
		HK_FORCE_INLINE hkBool32 equals3(const hkVector4f &a, hkFloat32 epsilon = 1e-3f ) const;
		HK_FORCE_INLINE hkBool32 equals4(const hkVector4f &a, hkFloat32 epsilon = 1e-3f ) const;
		HK_FORCE_INLINE hkVector4fComparison compareEqual4(hkVector4fParameter a) const;
		HK_FORCE_INLINE hkVector4fComparison compareLessThan4(hkVector4fParameter a) const;
		HK_FORCE_INLINE hkVector4fComparison compareLessThanEqual4(hkVector4fParameter a) const;
		HK_FORCE_INLINE hkVector4fComparison compareGreaterThan4(hkVector4fParameter a) const;
		HK_FORCE_INLINE hkVector4fComparison compareGreaterThanEqual4(hkVector4fParameter a) const;
		HK_FORCE_INLINE hkVector4fComparison compareLessThanZero4() const;
		HK_FORCE_INLINE hkBool32 allLessThan3(hkVector4fParameter a) const;
		HK_FORCE_INLINE hkBool32 allLessThan4(hkVector4fParameter a) const;
		HK_FORCE_INLINE void setInterpolate4( hkVector4fParameter a, hkVector4fParameter b, hkSimdFloat32Parameter t );
		HK_FORCE_INLINE hkSimdFloat32 distanceTo3( hkVector4fParameter p ) const;
		HK_FORCE_INLINE hkSimdFloat32 distanceToSquared3( hkVector4fParameter p ) const;
		HK_FORCE_INLINE hkSimdFloat32 horizontalAdd3() const;
		HK_FORCE_INLINE void setHorizontalMax4( hkVector4fParameter p);
		HK_FORCE_INLINE hkSimdFloat32 getHorizontalMin3() const;
		HK_FORCE_INLINE hkSimdFloat32 getHorizontalMax3() const;
		HK_FORCE_INLINE void _setMul4xyz1(const hkTransformf& a, hkVector4fParameter b );
		HK_FORCE_INLINE void add3clobberW(hkVector4fParameter a);
		template <int S> HK_FORCE_INLINE void setShuffle(hkVector4fParameter v);
		HK_FORCE_INLINE hkBool isOk3() const;
		HK_FORCE_INLINE hkBool isOk4() const;
		HK_FORCE_INLINE const hkVector4fComparison isNegative() const;
		HK_FORCE_INLINE const hkVector4fComparison isPositive() const;
		HK_FORCE_INLINE void load3(const hkFloat32* p);
		HK_FORCE_INLINE void load4(const hkFloat32* p);
		HK_FORCE_INLINE void load4a(const hkFloat32* p);
		HK_FORCE_INLINE void store3(hkFloat32* p) const;
		HK_FORCE_INLINE void store4(hkFloat32* p) const;
		HK_FORCE_INLINE void store4a(hkFloat32* p) const;
		HK_FORCE_INLINE void storeX( hkFloat32* dest) const;
		HK_FORCE_INLINE void load3(const hkDouble64* p);
		HK_FORCE_INLINE void load4(const hkDouble64* p);
		HK_FORCE_INLINE void load4a(const hkDouble64* p);
		HK_FORCE_INLINE void store3(hkDouble64* p) const;
		HK_FORCE_INLINE void store4(hkDouble64* p) const;
		HK_FORCE_INLINE void store4a(hkDouble64* p) const;
		HK_FORCE_INLINE void storeX( hkDouble64* dest) const;
		HK_FORCE_INLINE hkSimdFloat32 horizontalAdd4() const;
		HK_FORCE_INLINE void setClamped(hkVector4fParameter vSrc, const hkSimdFloat32& maxLen);
		HK_FORCE_INLINE	int getMaxElementIndex4() const;
		HK_FORCE_INLINE	int getMajorAxis3() const;
		HK_FORCE_INLINE void storeUncached( void* dest) const;
		HK_FORCE_INLINE void _setMul4(const hkMatrix3f& a, hkVector4fParameter b );
		HK_FORCE_INLINE void sub3clobberW(hkVector4fParameter a);
		HK_FORCE_INLINE void setAnd( hkVector4fParameter v0, hkVector4fParameter v1 );

#endif

};

#endif //HK_MATH_VECTOR4f_H

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
