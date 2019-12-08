/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#ifndef HK_MATH_VECTOR4f_COMPARISON_H
#define HK_MATH_VECTOR4f_COMPARISON_H
#ifndef HK_MATH_MATH_H
#	error Please include Common/Base/hkBase.h instead of this file.
#endif

// compile time error checking
namespace hkCompileError
{
	template <bool b> struct HK_VECTORfCOMPARISON_ILLEGAL_MASK_VALUE;
	template <> struct HK_VECTORfCOMPARISON_ILLEGAL_MASK_VALUE<true> {};

	template <bool b> struct HK_VECTORfCOMPARISON_SUBINDEX_OUT_OF_RANGE;
	template <> struct HK_VECTORfCOMPARISON_SUBINDEX_OUT_OF_RANGE<true> {};
}
#define HK_VECTORfCOMPARISON_MASK_CHECK           HK_COMPILE_TIME_ASSERT2((M&0xf)==M, HK_VECTORfCOMPARISON_ILLEGAL_MASK_VALUE)
#define HK_VECTORfCOMPARISON_SUBINDEX_CHECK		 HK_COMPILE_TIME_ASSERT2((N>0)&&(N<=4), HK_VECTORfCOMPARISON_SUBINDEX_OUT_OF_RANGE);

/// \class hkVector4fComparison
///
/// A mask for floating point comparisons. It holds a special representation for a boolean 
/// for every component of a hkVector4f or hkSimdFloat32. There are optimized SIMD implementations
/// available for several platforms. They use platform specific data structures and
/// code to provide efficient processing. Thus to be portable, nothing should be assumed
/// about the internal boolean value or layout of the storage.
///
/// This class also defines a list of platform independent symbols in 'Mask' which should
/// exclusively be used in code to hand-craft known masks. For compatibility with possible
/// future extensions, nothing should be assumed about the value of these symbols.
///
/// This mask can hold up to four comparison results and can be used with both hkVector4f and
/// hkSimdFloat32 interchangeably. 
///
/// \sa hkVector4f hkSimdFloat32
HK_PASS_IN_REG
class hkVector4fComparison : public hkVector4ComparisonMask
{
public:

	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_MATH, hkVector4fComparison);

	using hkVector4ComparisonMask::Mask;

	/// Static conversion method to create a hkVector4fComparison from a platform dependent comparison mask \a x. ( self.storage = x ).
	/// This method is implemented platform-specific to avoid constructor initialization overhead
	/// or read-modify-write data dependencies which might occur.
	HK_FORCE_INLINE static const hkVector4fComparison HK_CALL convert(const hkVector4fMask& x);

	/// Static helper method which returns the appropriate mask for the specified component \a i. ( return self[i] ).
	/// \remark Use this method only when the component index is not a compile time constant.
	HK_FORCE_INLINE static Mask HK_CALL getMaskForComponent(int i);

	/// Return the index of the last component set in self. If no component is set, zero is returned.
	HK_FORCE_INLINE int getIndexOfLastComponentSet() const;

	/// Return the index of the first component set in self. If no component is set, zero is returned.
	HK_FORCE_INLINE int getIndexOfFirstComponentSet() const;

	/// Sets the comparison mask to be the component-wise logical 'and' of \a a and \a b. ( self = a && b )
	HK_FORCE_INLINE void setAnd( hkVector4fComparisonParameter a, hkVector4fComparisonParameter b );

	/// Sets the comparison mask to the component-wise logical 'and not' of \a a and \a b. ( self = a && !b )
	HK_FORCE_INLINE void setAndNot( hkVector4fComparisonParameter a, hkVector4fComparisonParameter b );

	/// Sets the comparison mask to the component-wise logical 'xor' of \a a and \a b. ( self = a ^ b )
	HK_FORCE_INLINE void setXor( hkVector4fComparisonParameter a, hkVector4fComparisonParameter b );

	/// Sets the comparison mask to the component-wise logical 'or' of \a a and \a b. ( self = a || b )
	HK_FORCE_INLINE void setOr( hkVector4fComparisonParameter a, hkVector4fComparisonParameter b );

	/// Sets the comparison mask to the component-wise logical 'not' of \a a. ( self = !a )
	HK_FORCE_INLINE void setNot( hkVector4fComparisonParameter a );

	/// Component-wise select mask values from \a trueValue or \a falseValue depending on whether
	/// the component is marked set or clear in the \a comp mask. ( self = comp ? trueValue : falseValue )
	HK_FORCE_INLINE void setSelect( hkVector4fComparisonParameter comp, hkVector4fComparisonParameter trueValue, hkVector4fComparisonParameter falseValue );
	template <Mask M> HK_FORCE_INLINE void setSelect(hkVector4fComparisonParameter trueValue, hkVector4fComparisonParameter falseValue);

	/// Set self to form the mask \a m. ( self.storage = m ).
	/// \remark Use this method only when the component mask is not a compile time constant.
	HK_FORCE_INLINE void set( Mask m );

	/// Set self to form the mask \a M. ( self.storage = M )
	template <Mask M> HK_FORCE_INLINE void set();

	/// Returns true if every component which is selected in the mask \a m is also set
	/// in self. Returns false otherwise. ( return ( self && m ) == m ).
	/// \remark Use this method only when the component mask is not a compile time constant.
	/// \remark If MASK_NONE is passed in as a parameter this method will always return true.
	HK_FORCE_INLINE hkBool32 allAreSet( Mask m ) const;

	/// Returns true if every component which is selected in the mask \a M is also set
	/// in self. Returns false otherwise. ( return ( self && M ) == M ).
	/// \remark If MASK_NONE is passed in as a parameter this method will always return true.
	template <Mask M> HK_FORCE_INLINE hkBool32 allAreSet() const;

	/// Returns true only if all components of self are set. ( return self == ALL )
	HK_FORCE_INLINE hkBool32 allAreSet() const;

	/// Returns true if any component which is selected in the mask \a m is also set
	/// in self. Returns false otherwise. ( return ( self && m ) != NONE ).
	/// \remark Use this method only when the component mask is not a compile time constant.
	/// \remark If MASK_NONE is passed in as a parameter this method will always return false.
	HK_FORCE_INLINE hkBool32 anyIsSet( Mask m ) const;

	/// Returns true if any component which is selected in the mask \a m is also set
	/// in self. Returns false otherwise. ( return ( self && M ) != NONE ).
	/// \remark If MASK_NONE is passed in as a parameter this method will always return false.
	template <Mask M> HK_FORCE_INLINE hkBool32 anyIsSet() const;

	/// Returns true as soon as any component of self is set. ( return self != NONE )
	HK_FORCE_INLINE hkBool32 anyIsSet() const;

	/// Returns a mask describing which components of self are set. ( return self.storage )
	HK_FORCE_INLINE Mask getMask() const;

	/// Returns a mask describing which of the components of self, selected by \a m, are set. ( return self.storage && m )
	/// \remark Use this method only when the component mask is not a compile time constant.
	HK_FORCE_INLINE Mask getMask(Mask m) const;

	/// Returns a mask describing which of the components of self, selected by \a M, are set. ( return self.storage && M )
	template <Mask M> HK_FORCE_INLINE Mask getMask() const;

	/// Sets all components of this to the bitwise or of the first N components, i.e. (mask[0] | mask[1] | ... | mask[I - 1])
	template <int N>
	HK_FORCE_INLINE const hkVector4fComparison horizontalOr() const;

	/// Sets all components of this to the bitwise AND of the first N components, i.e. (mask[0] | mask[1] | ... | mask[I - 1])
	template <int N>
	HK_FORCE_INLINE const hkVector4fComparison horizontalAnd() const;

	/// Static method to return a 32 bit integer holding the combined masks of \a ca, \a cb and \a cc.
	/// The mask of \a ca is returned in Bits [0-7], the mask of \a cb in [8-15] and the mask of \a cc in [16-23].
	static HK_FORCE_INLINE hkUint32 HK_CALL getCombinedMask(hkVector4fComparisonParameter ca, hkVector4fComparisonParameter cb, hkVector4fComparisonParameter cc );


	/// Internal data storage of the boolean value components (platform dependent).
	/// For writing portable code, nothing can be assumed about the internal layout of the values.
	hkVector4fMask m_mask;

	protected:

};

extern const hkUint8 hkVector4Comparison_maskToFirstIndex[16]; ///< selection map to lowest index set
extern const hkUint8 hkVector4Comparison_maskToLastIndex[16];  ///< selection map to highest index set

#endif //HK_MATH_VECTOR4f_COMPARISON_H

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
