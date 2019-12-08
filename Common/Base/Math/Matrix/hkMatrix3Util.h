/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_MATH_MATRIX3_UTIL_H
#define HK_MATH_MATRIX3_UTIL_H

#include <Common/Base/Math/Vector/hkVector4Util.h>

/// Utility functions for hkMatrix3
template <typename FT>
class hkMatrix3UtilImpl
{
public:

	typedef hkMatrix3UtilImpl<FT> ThisType;
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_MATH, ThisType);

	/// Sets reflectionOut to be the reflection of matrix D through matrix P, i.e., reflectionOut = Transpose(P) * A * P.
	/// Matrix D is assumed diagonal.
	static HK_FORCE_INLINE void HK_CALL _computeReflectedDiagonal(const typename hkRealTypes<FT>::Matrix3& P, typename hkRealTypes<FT>::VectorParameter D, typename hkRealTypes<FT>::Matrix3& reflectionOut);
	static void HK_CALL computeReflectedDiagonal(const typename hkRealTypes<FT>::Matrix3& P, typename hkRealTypes<FT>::VectorParameter D, typename hkRealTypes<FT>::Matrix3& reflectionOut);

	/// Sets matrixOut = Q * D * Inverse(Q), where D is interpreted as a diagonal matrix.
	static HK_FORCE_INLINE void HK_CALL _changeBasis(typename hkRealTypes<FT>::QuaternionParameter Q, typename hkRealTypes<FT>::VectorParameter D, typename hkRealTypes<FT>::Matrix3& matrixOut);
	static void HK_CALL changeBasis(typename hkRealTypes<FT>::QuaternionParameter Q, typename hkRealTypes<FT>::VectorParameter D, typename hkRealTypes<FT>::Matrix3& matrixOut);

	/// Sets matrixOut = R * D * Transpose(R), where D is interpreted as a diagonal matrix.
	static HK_FORCE_INLINE void HK_CALL _changeBasis(const typename hkRealTypes<FT>::Rotation& R, typename hkRealTypes<FT>::VectorParameter D, typename hkRealTypes<FT>::Matrix3& matrixOut);
	static void HK_CALL changeBasis(const typename hkRealTypes<FT>::Rotation& R, typename hkRealTypes<FT>::VectorParameter D, typename hkRealTypes<FT>::Matrix3& matrixOut);

	/// Sets inertiaOut = Identity * dot(v, v) - OuterProduct(v, v). The matrix is used to displace inertia tensors
	/// by v from the center of mass.
	static HK_FORCE_INLINE void HK_CALL _computeInertiaDisplacement(typename hkRealTypes<FT>::VectorParameter v, typename hkRealTypes<FT>::Matrix3& inertiaOut);
	static void HK_CALL computeInertiaDisplacement(typename hkRealTypes<FT>::VectorParameter v, typename hkRealTypes<FT>::Matrix3& inertiaOut);

	/// Returns the diagonal of the given matrix.
	static HK_FORCE_INLINE	void HK_CALL _getDiagonal(const typename hkRealTypes<FT>::Matrix3& matrixIn, typename hkRealTypes<FT>::Vector& diagonalOut);
	static void HK_CALL getDiagonal(const typename hkRealTypes<FT>::Matrix3& matrixIn, typename hkRealTypes<FT>::Vector& diagonalOut);

	/// Returns the off-diagonal elements of the given matrix. The matrix is assumed to be symmetric. The returned vector is
	/// [m01, m02, m12, 0]
	static HK_FORCE_INLINE void HK_CALL _getSymmetricOffDiagonal(const typename hkRealTypes<FT>::Matrix3& matrixIn, typename hkRealTypes<FT>::Vector& offDiagonalOut);
	static void HK_CALL getSymmetricOffDiagonal(const typename hkRealTypes<FT>::Matrix3& matrixIn, typename hkRealTypes<FT>::Vector& offDiagonalOut);

	/// Returns the absolute maximum element
	static HK_FORCE_INLINE const typename hkRealTypes<FT>::Scalar HK_CALL _computeMaxAbsElement(const typename hkRealTypes<FT>::Matrix3& matrixIn);
	static const typename hkRealTypes<FT>::Scalar HK_CALL computeMaxAbsElement(const typename hkRealTypes<FT>::Matrix3& matrixIn);

	/// Computes matrixOut = matrixIn * hat(v), whereh hat(v) is the skew-symmetric matrix of v
	static HK_FORCE_INLINE void HK_CALL _computeCrossProduct(const typename hkRealTypes<FT>::Matrix3& matrixIn, typename hkRealTypes<FT>::VectorParameter v, typename hkRealTypes<FT>::Matrix3& matrixOut);

	/// Sets aTb = Transpose(a) * b.
	static HK_FORCE_INLINE void HK_CALL _computeTransposeMul(const typename hkRealTypes<FT>::Matrix3& a, const typename hkRealTypes<FT>::Matrix3& b, typename hkRealTypes<FT>::Matrix3& aTb);

	/// Sets this matrix as the cross product between the given vector and each of the given matrix's columns.
	/// Specifically, it sets mtxOut.column(i) = cross(v, src.column(i))
	static HK_FORCE_INLINE void HK_CALL _computeCrossMul(typename hkRealTypes<FT>::VectorParameter v, const typename hkRealTypes<FT>::Matrix3& src, typename hkRealTypes<FT>::Matrix3& mtxOut);

	/// Checks if matrixIn is equal to the identity matrix within an epsilon.
	static HK_FORCE_INLINE hkBool32 HK_CALL _isApproximatelyIdentity(const typename hkRealTypes<FT>::Matrix3& matrixIn, typename hkRealTypes<FT>::ScalarParameter eps);

	/// Sets the specified diagonal values, zeroes the non-diagonal values.
	static HK_FORCE_INLINE void HK_CALL _setDiagonal(typename hkRealTypes<FT>::Pod m00, typename hkRealTypes<FT>::Pod m11, typename hkRealTypes<FT>::Pod m22, typename hkRealTypes<FT>::Matrix3& matrixOut);
	static HK_FORCE_INLINE void HK_CALL _setDiagonal(typename hkRealTypes<FT>::ScalarParameter m00, typename hkRealTypes<FT>::ScalarParameter m11, typename hkRealTypes<FT>::ScalarParameter m22, typename hkRealTypes<FT>::Matrix3& matrixOut);
	static HK_FORCE_INLINE void HK_CALL _setDiagonal(typename hkRealTypes<FT>::VectorParameter vDiagonal, typename hkRealTypes<FT>::Matrix3& matrixOut);
	static HK_FORCE_INLINE void HK_CALL _setDiagonal(typename hkRealTypes<FT>::ScalarParameter diag, typename hkRealTypes<FT>::Matrix3& matrixOut);

	/// Sets the specified diagonal values, leaves the non-diagonal values alone.
	static HK_FORCE_INLINE void HK_CALL _setDiagonalOnly(typename hkRealTypes<FT>::VectorParameter vDiagonal, typename hkRealTypes<FT>::Matrix3& matrixOut);
	static HK_FORCE_INLINE void HK_CALL _setDiagonalOnly(typename hkRealTypes<FT>::ScalarParameter diag, typename hkRealTypes<FT>::Matrix3& matrixOut);

	/// Computes mtxOut to be the product of a and the inverse of b. (mtxOut = a * b^-1)
	static HK_FORCE_INLINE void HK_CALL _computeMulInverse(const typename hkRealTypes<FT>::Matrix3& a, const typename hkRealTypes<FT>::Rotation& b, typename hkRealTypes<FT>::Matrix3& mtxOut);

	/// Computes the outer product of the given vectors, i.e. mtxOut = u * Transpose[v]
	static HK_FORCE_INLINE void HK_CALL _computeOuterProduct(typename hkRealTypes<FT>::VectorParameter u, typename hkRealTypes<FT>::VectorParameter v, typename hkRealTypes<FT>::Matrix3& mtxOut);

	/// Computes the displacement given by the two vectors rA and rB, i.e. mtxOut = Hat[rA] * Hat[rB]
	static HK_FORCE_INLINE void HK_CALL _computeDisplacement(typename hkRealTypes<FT>::VectorParameter rA, typename hkRealTypes<FT>::VectorParameter rB, typename hkRealTypes<FT>::Matrix3& mtxOut);
};

#include <Common/Base/Math/Matrix/hkMatrix3Util.inl>

typedef hkMatrix3UtilImpl<hkFloat32>  hkMatrix3fUtil;
typedef hkMatrix3UtilImpl<hkDouble64> hkMatrix3dUtil;

#if defined(HK_REAL_IS_DOUBLE)
typedef hkMatrix3dUtil hkMatrix3Util;
#else
typedef hkMatrix3fUtil hkMatrix3Util;
#endif

#endif	//	HK_MATH_MATRIX3_UTIL_H

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
