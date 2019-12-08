/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_MATH_SYMMETRIC_MATRIX3_UTIL_H
#define HK_MATH_SYMMETRIC_MATRIX3_UTIL_H

#include <Common/Base/Math/Vector/hkVector4Util.h>

/// Miscellaneous operations involving symmetric 3x3 matrices
template <typename FT>
class hkSymmetricMatrixUtilImpl
{
public:

	typedef hkSymmetricMatrixUtilImpl<FT> ThisType;
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_MATH, ThisType);

	/// Sets mtxOut = outer product of the given vector, i.e [xx, yy, zz], [xy, yz, zx]
	static HK_FORCE_INLINE void HK_CALL _computeOuterProduct(typename hkRealTypes<FT>::VectorParameter v, typename hkRealTypes<FT>::SymmetricMatrix3& mtxOut);

	/// Projects the tensor on the given direction, i.e. computes Transpose(d) * mtx * d
	static HK_FORCE_INLINE const typename hkRealTypes<FT>::Scalar HK_CALL _computeProjection(const typename hkRealTypes<FT>::SymmetricMatrix3& mtx, typename hkRealTypes<FT>::VectorParameter vD);

	/// Sets mtxOut = Transpose(R) * Diag(a) * R, where Diag(a) is a diagonal matrix with diagonal elements a.
	static HK_FORCE_INLINE void HK_CALL _computeInverseBasisTransform(const typename hkRealTypes<FT>::Matrix3& R, typename hkRealTypes<FT>::VectorParameter diagA, typename hkRealTypes<FT>::SymmetricMatrix3& mtxOut);

	/// Solves the linear system: mtx * v = b, for v.
	static HK_FORCE_INLINE void HK_CALL _solve(const typename hkRealTypes<FT>::SymmetricMatrix3& mtx, typename hkRealTypes<FT>::VectorParameter b, typename hkRealTypes<FT>::Vector& solutionOut);

	/// Sets inverseOut = Inverse(t).
	static HK_FORCE_INLINE void HK_CALL _computeInverse(const typename hkRealTypes<FT>::SymmetricMatrix3& t, typename hkRealTypes<FT>::SymmetricMatrix3& inverseOut);

	/// Computes vOut = t * vIn
	static HK_FORCE_INLINE void HK_CALL _multiply(const typename hkRealTypes<FT>::SymmetricMatrix3& t, typename hkRealTypes<FT>::VectorParameter vIn, typename hkRealTypes<FT>::Vector& vOut);

	/// Computes tOut = rot * ta * Transpose[rot]
	static HK_FORCE_INLINE void HK_CALL _computeBasisTransform(const typename hkRealTypes<FT>::Rotation& rot, const typename hkRealTypes<FT>::SymmetricMatrix3& ta, typename hkRealTypes<FT>::SymmetricMatrix3& tOut);
	static HK_FORCE_INLINE void HK_CALL _computeBasisTransform(const typename hkRealTypes<FT>::Rotation& rot, typename hkRealTypes<FT>::VectorParameter vDiag, typename hkRealTypes<FT>::SymmetricMatrix3& tOut);
	static HK_FORCE_INLINE void HK_CALL _computeBasisTransform(typename hkRealTypes<FT>::QuaternionParameter rot, const typename hkRealTypes<FT>::SymmetricMatrix3& ta, typename hkRealTypes<FT>::SymmetricMatrix3& tOut);
	static HK_FORCE_INLINE void HK_CALL _computeBasisTransform(typename hkRealTypes<FT>::QuaternionParameter rot, typename hkRealTypes<FT>::VectorParameter vDiag, typename hkRealTypes<FT>::SymmetricMatrix3& tOut);

	/// Solves the linear system: mtx * v = b for v, where |v| < vMax per component.
	/// The problem is a LCP and the returned solution is an approximation computed via Jacobi iterations.
	/// The number of iterations is given as a template parameter
	template <int NIter>
	static HK_FORCE_INLINE void HK_CALL _solve(const typename hkRealTypes<FT>::SymmetricMatrix3& mtx, typename hkRealTypes<FT>::VectorParameter b, typename hkRealTypes<FT>::VectorParameter vMax, typename hkRealTypes<FT>::Vector& solutionOut);

	/// Computes tOut = Hat[r] * ta * Hat[r]
	static HK_FORCE_INLINE void HK_CALL _computeDisplacedTensor(typename hkRealTypes<FT>::VectorParameter r, const typename hkRealTypes<FT>::SymmetricMatrix3& ta, typename hkRealTypes<FT>::SymmetricMatrix3& tOut);
	static HK_FORCE_INLINE void HK_CALL _computeDisplacedTensor(typename hkRealTypes<FT>::VectorParameter r, typename hkRealTypes<FT>::VectorParameter diag, typename hkRealTypes<FT>::SymmetricMatrix3& tOut);

	/// Computes tOut = Hat[r] * Hat[r]
	static HK_FORCE_INLINE void HK_CALL _computeDisplacement(typename hkRealTypes<FT>::VectorParameter r, typename hkRealTypes<FT>::SymmetricMatrix3& tOut);

	/// Returns the element with maximum absolute value in the matrix
	static HK_FORCE_INLINE const typename hkRealTypes<FT>::Scalar HK_CALL _getMaxAbsElement(const typename hkRealTypes<FT>::SymmetricMatrix3& t);

	/// Computes the SVD of the given matrix t = R * D * Transpose[R]
	static HK_FORCE_INLINE void HK_CALL _computeSvd(const typename hkRealTypes<FT>::SymmetricMatrix3& t, typename hkRealTypes<FT>::Rotation& eigenVecsOut, typename hkRealTypes<FT>::Vector& eigenValsOut);

	/// Computes the coefficients of the characteristic polynomial
	static HK_FORCE_INLINE void HK_CALL _computeCharacteristicPolynomial(const typename hkRealTypes<FT>::SymmetricMatrix3& t, typename hkRealTypes<FT>::Vector& coeffsOut);

	/// Computes the eigenvalues using the characteristic polynomial. Note that the results are often affected by numerical imprecisions!
	static HK_FORCE_INLINE hkResult HK_CALL _computeEigenValues(const typename hkRealTypes<FT>::SymmetricMatrix3& t, typename hkRealTypes<FT>::Vector& eigenValsOut);

	/// Computes the symmetric matrix obtained by computing the cross products between consecutive columns, i.e. {Cross[c1,c2], Cross[c2, c0], Cross[c0, c1]}
	static HK_FORCE_INLINE void HK_CALL _computeColumnCrossProducts(const typename hkRealTypes<FT>::SymmetricMatrix3& t, typename hkRealTypes<FT>::SymmetricMatrix3& crossProductsOut);

	/// Computes an eigenvector for the given eigenvalue
	static HK_FORCE_INLINE void HK_CALL _computeEigenVector(const typename hkRealTypes<FT>::SymmetricMatrix3& t, typename hkRealTypes<FT>::ScalarParameter eigenValueIn, typename hkRealTypes<FT>::Vector& eigenVectorOut);

	/// Computes the squared lengths of the given matrix's columns
	static HK_FORCE_INLINE void HK_CALL _computeColumnLengthsSq(const typename hkRealTypes<FT>::SymmetricMatrix3& t, typename hkRealTypes<FT>::Vector& sqLengthsOut);
};

#include <Common/Base/Math/SymmetricMatrix/hkSymmetricMatrix3Util.inl>

typedef hkSymmetricMatrixUtilImpl<hkFloat32>  hkSymmetricMatrix3fUtil;
typedef hkSymmetricMatrixUtilImpl<hkDouble64> hkSymmetricMatrix3dUtil;

#if defined(HK_REAL_IS_DOUBLE)
typedef hkSymmetricMatrix3dUtil hkSymmetricMatrix3Util;
#else
typedef hkSymmetricMatrix3fUtil hkSymmetricMatrix3Util;
#endif

#endif	//	HK_MATH_SYMMETRIC_MATRIX3_UTIL_H

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
