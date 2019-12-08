/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

/// Permutations of 4-component vectors hkVector4 and hkIntVector
struct hkVectorPermutation
{
	enum Permutation 
	{
		XYZW = 0x0123, // identity
		WZYX = 0x3210, // reverse

		WXYZ = 0x3012, // shift
		ZWXY = 0x2301,
		YZWX = 0x1230,

		XYWZ = 0x0132, // swap
		YXWZ = 0x1032,
		YXZW = 0x1023,
		YZXW = 0x1203,
		YWZX = 0x1320,
		WYZX = 0x3120,
		XZYW = 0x0213,
		XZZW = 0x0223,
		XYYW = 0x0113,
		ZXYW = 0x2013,
		ZYZW = 0x2123,

		XYXY = 0x0101, // pairs
		XXYY = 0x0011,
		ZZWW = 0x2233,
		YYXX = 0x1100,
		ZWZW = 0x2323,
		ZWXW = 0x2303,
		ZYXZ = 0x2102,
		ZYZZ = 0x2122,
		XZXZ = 0x0202,
		XZYZ = 0x0212,
		YWYW = 0x1313,
		YXWW = 0x1033,
		YXYX = 0x1010,
		XYWW = 0x0133,
		XYZZ = 0x0122,
		XWYW = 0x0313,
		WZWZ = 0x3232,
		XWZY = 0x0321,

		ZWYW = 0x2313,

		XXZZ = 0x0022,
		YYWW = 0x1133,
		YYZZ = 0x1122,
		YZZZ = 0x1222,
		YZZY = 0x1221,
		ZZXX = 0x2200,
		WWYY = 0x3311,
		WXXW = 0x3003,
		WWZZ = 0x3322,
		WZXY = 0x3201,

		XWYZ = 0x0312,
		XZWY = 0x0231, 

		XXXX = 0x0000, // broadcasts
		YYYY = 0x1111,
		ZZZZ = 0x2222,
		WWWW = 0x3333,
		XWWW = 0x0333,
		WXWW = 0x3033,
		WWXW = 0x3303,
		WYWW = 0x3133,
		WWYW = 0x3313,
		WWZW = 0x3323,
		ZWWW = 0x2333,
		WWWZ = 0x3332,

		ZXYZ = 0x2012,
		YZXZ = 0x1202,
		YXXY = 0x1001,
		ZZYY = 0x2211,
		YZZW = 0x1223,

		XYYX = 0x0110,
		WZYW = 0x3213,
		ZYXW = 0x2103,
		XXYZ = 0x0012,
		YZWW = 0x1233,
	};
};



struct hkVector4ComparisonMask
{
	/// Defines the various mask combinations possible.
	/// This is a platform independent description of possible outcomes of compare operations.
	/// Although these symbols are assigned to values here, nothing should be assumed about the
	/// bit pattern employed. It is not guaranteed to be invariant over releases.
	enum Mask
	{
		INDEX_W		= 3,	// Index of the w component
		INDEX_Z		= 2,
		INDEX_Y		= 1,
		INDEX_X		= 0,

		MASK_NONE	= 0x0,					// 0000
		MASK_W		= (1 << INDEX_W),		// 0001
		MASK_Z		= (1 << INDEX_Z),		// 0010
		MASK_ZW		= (MASK_Z | MASK_W),	// 0011

		MASK_Y		= (1 << INDEX_Y),		// 0100
		MASK_YW		= (MASK_Y | MASK_W),	// 0101
		MASK_YZ		= (MASK_Y | MASK_Z),	// 0110
		MASK_YZW	= (MASK_YZ | MASK_W),	// 0111

		MASK_X		= (1 << INDEX_X),		// 1000
		MASK_XW		= (MASK_X | MASK_W),	// 1001
		MASK_XZ		= (MASK_X | MASK_Z),	// 1010
		MASK_XZW	= (MASK_XZ | MASK_W),	// 1011

		MASK_XY		= (MASK_X | MASK_Y),	// 1100
		MASK_XYW	= (MASK_XY | MASK_W),	// 1101
		MASK_XYZ	= (MASK_XY | MASK_Z),	// 1110
		MASK_XYZW	= (MASK_XY | MASK_ZW)	// 1111
	};
};


/// Flag for advanced hkSimdReal/hkVector4 interface to control the
/// floating point accuracy of division and sqrt calculations.
/// Note that for full precision the returned accuracy depends on the definition
/// of hkReal.
enum hkMathAccuracyMode
{
	HK_ACC_FULL,    ///< Do calculations using full floating point precision and produce IEEE compliant return values.
	HK_ACC_23_BIT,  ///< Do calculations such that at least 23 mantissa bits are accurate. Denormals handling is allowed to be different to IEEE if it results in better performance.
	HK_ACC_12_BIT   ///< Do calculations such that at least 12 mantissa bits are accurate. Denormals handling is allowed to be different to IEEE if it results in better performance.
};

/// Flag for advanced hkSimdReal/hkVector4 interface to control the
/// behavior of the method to check for division by zero.
enum hkMathDivByZeroMode
{
	HK_DIV_IGNORE,           ///< No checking. The result is platform dependent and can signal floating point errors.
	HK_DIV_SET_ZERO,         ///< Check and return zero in case. The sign of the fraction is lost. This will not produce floating point errors.
	HK_DIV_SET_ZERO_AND_ONE, ///< Check and return zero in case. The sign of the fraction is lost. This will not produce floating point errors. Additionally round all values to 1.0 which are closer than machine epsilon.
	HK_DIV_SET_MAX,          ///< Check and return the maximum representable floating point value in case. The sign of the fraction is preserved. This will not produce floating point errors.
	HK_DIV_SET_HIGH          ///< Check and return a huge value in case. The sign of the fraction is preserved. This will not produce floating point errors.
};

/// Flag for advanced hkSimdReal/hkVector4 interface to control the
/// behavior of the method to check for negative arguments of square root.
/// For inverse square roots, the checking versions also catch divide by zero.
enum hkMathNegSqrtMode
{
	HK_SQRT_IGNORE,   ///< No checking. The result is platform dependent and can signal floating point errors.
	HK_SQRT_SET_ZERO  ///< Check and return zero in case. This will not produce floating point errors.
};

/// Flag for advanced hkSimdReal/hkVector4 interface to control the
/// way values are loaded/written from memory. In general more aligned addresses
/// give faster reads/writes.
enum hkMathIoMode
{
	HK_IO_BYTE_ALIGNED,		///< The pointer can have an arbitrary address.
	HK_IO_NATIVE_ALIGNED,	///< The pointer must be aligned to the native size of the data pointed to. Example: load floats: align to sizeof(float)
	HK_IO_SIMD_ALIGNED,		///< The pointer must be aligned to the next power of 2 of the number of bytes to load. Example: load 3 floats: 3*4=12 -> 16
	HK_IO_NOT_CACHED		///< HK_IO_SIMD_ALIGNED + On platforms which support it, the values are loaded bypassing the processor caches. Use for reading data which is only needed once or for writing data which is not needed until much later.
};

/// Flag for advanced hkSimdReal/hkVector4 interface to control the
/// rounding behavior when floating point values are written to lower precision formats.
enum hkMathRoundingMode
{
	HK_ROUND_DEFAULT,	///< No explicit rounding is done. If the platform has native conversion instructions, the current system rounding mode is used.
	HK_ROUND_TRUNCATE,	///< The values get truncated to the packed representation.
	HK_ROUND_NEAREST	///< The values get rounded to the packed representation.
};

/// Permutations of a hkMxVectord vector
struct hkMxVectorPermutation
{
	enum Permutation 
	{
		SHIFT_RIGHT_CYCLIC, ///< Shift the subvectors to the right (higher indices). Example: 0123 -> 3012
		SHIFT_LEFT_CYCLIC,  ///< Shift the subvectors to the left (lower indices). Example: 0123 -> 1230
		REVERSE				///< Reverse the subvector order. Example: 0123 -> 3210
	};
};

/// Flag for specifying value types in operations involving ints
enum hkMathValueType
{
	HK_VALUE_SIGNED,
	HK_VALUE_UNSIGNED,
};

/// Flag that controls the sort direction of hkIntVector::setSort()
enum hkMathSortDir
{
	HK_SORT_ASCENDING,
	HK_SORT_DESCENDING,
};

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
