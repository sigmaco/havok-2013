/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_MATH_MATRIX4_UTIL_H
#define HK_MATH_MATRIX4_UTIL_H

#include <Common/Base/Math/Vector/hkVector4Util.h>

// internal static non-inline code, please use hkMatrix4Util methods
namespace __hkMatrix4UtilAlgo
{
	hkResult invert(hkMatrix4f& m, hkSimdFloat32Parameter  epsilon);
	hkResult invert(hkMatrix4d& m, hkSimdDouble64Parameter epsilon);

	hkResult setInverse(const hkMatrix4f& m, hkMatrix4f& out, hkSimdFloat32Parameter epsilon);
	hkResult setInverse(const hkMatrix4d& m, hkMatrix4d& out, hkSimdDouble64Parameter epsilon);
}

/// Utility functions for hkMatrix4
template <typename FT>
class hkMatrix4UtilImpl
{
public:

	typedef hkMatrix4UtilImpl<FT> ThisType;
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_MATH, ThisType);

	/// Sets aTb = Transpose(a) * b.
	static HK_FORCE_INLINE void HK_CALL _computeTransposeMul(const typename hkRealTypes<FT>::Matrix4& a, const typename hkRealTypes<FT>::Matrix4& b, typename hkRealTypes<FT>::Matrix4& aTb);

	/// (Assumes transforms are affine) Sets \a out matrix to be the product of \a a and the inverse of \a b. (out = a * b^-1)
	static HK_FORCE_INLINE void HK_CALL _setMulInverseAffine ( const typename hkRealTypes<FT>::Matrix4& a, const typename hkRealTypes<FT>::Matrix4& b, typename hkRealTypes<FT>::Matrix4& out );

	/// (Non-affine version - slower) Sets \a out matrix to be the product of \a a and the inverse of \a b. (out = a * b^-1)
	static HK_FORCE_INLINE void HK_CALL _setMulInverse ( const typename hkRealTypes<FT>::Matrix4& a, const typename hkRealTypes<FT>::Matrix4& b, typename hkRealTypes<FT>::Matrix4& out );

	/// Inverts the matrix. This function returns HK_SUCCESS if the determinant is greater than epsilon. Otherwise it returns HK_FAILURE and the matrix values are undefined.
	static HK_FORCE_INLINE hkResult HK_CALL invert (typename hkRealTypes<FT>::Matrix4& m, typename hkRealTypes<FT>::ScalarParameter epsilon);

	/// Sets the matrix to be the inverse of the given matrix. It returns HK_SUCCESS if the determinant is greater than epsilon. Otherwise it returns HK_FAILURE and the matrix values are undefined.
	static HK_FORCE_INLINE hkResult HK_CALL setInverse (const typename hkRealTypes<FT>::Matrix4& m, typename hkRealTypes<FT>::Matrix4& out, typename hkRealTypes<FT>::ScalarParameter epsilon);

	/// Sets the specified diagonal values, zeroes the non-diagonal values.
	static HK_FORCE_INLINE void HK_CALL _setDiagonal(typename hkRealTypes<FT>::VectorParameter vDiagonal, typename hkRealTypes<FT>::Matrix4& matrixOut);
	static HK_FORCE_INLINE void HK_CALL _setDiagonal(typename hkRealTypes<FT>::ScalarParameter diag, typename hkRealTypes<FT>::Matrix4& matrixOut);

	/// Sets the specified diagonal values of the upper 3x3 matrix, zeroes the non-diagonal values, sets last column to <0,0,0,1>
	static HK_FORCE_INLINE void HK_CALL _setDiagonal3x3(typename hkRealTypes<FT>::VectorParameter vDiagonal, typename hkRealTypes<FT>::Matrix4& matrixOut);
	static HK_FORCE_INLINE void HK_CALL _setDiagonal3x3(typename hkRealTypes<FT>::ScalarParameter diag, typename hkRealTypes<FT>::Matrix4& matrixOut);
};

#include <Common/Base/Math/Matrix/hkMatrix4Util.inl>

typedef hkMatrix4UtilImpl<hkFloat32>  hkMatrix4fUtil;
typedef hkMatrix4UtilImpl<hkDouble64> hkMatrix4dUtil;

#if defined(HK_REAL_IS_DOUBLE)
typedef hkMatrix4dUtil hkMatrix4Util;
#else
typedef hkMatrix4fUtil hkMatrix4Util;
#endif

#endif	//	HK_MATH_MATRIX4_UTIL_H

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
