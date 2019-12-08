/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_MATRIX_DECOMPOSITION_UTIL_H
#define HK_MATRIX_DECOMPOSITION_UTIL_H

template <typename FT>
struct hkMatrixDecompositionImpl
{
	typedef hkMatrixDecompositionImpl<FT> ThisType;
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_MATH, ThisType );

	/// Structure returned by decompose methods
	struct Decomposition
	{
		typedef typename ThisType::Decomposition DecompType;
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_MATH, DecompType );

		typename hkRealTypes<FT>::Vector m_translation;		///< T
		typename hkRealTypes<FT>::Quaternion m_rotation;	///< R
		typename hkRealTypes<FT>::Vector m_scale;			///< S

		typename hkRealTypes<FT>::Matrix4 m_scaleAndSkew;	///< M = T*R * scaleAndSkew
		typename hkRealTypes<FT>::Matrix4 m_skew;			///< M = T*R*S * skew

		typename hkRealTypes<FT>::Rotation m_basis;			///< Rotation matrix, may involve flipping: If m_flips=false, then m_basis == m_rotation

		hkBool m_hasScale;			///< True if S !=(1,1,1)
		hkBool m_hasSkew;			///< True if T*R*S != M (original Matrix)
		hkBool m_flips;				///< True if Det(M)<0
	};

	/// Decomposes M (4x4 matrix) as M == T * R * Scale * Skew == T * R * ScaleAndSkew.
	/// Useful for conversion both to orthogonal (no skew) and orthonormal (no scale or skew) transforms
	static void HK_CALL decomposeMatrix (const typename hkRealTypes<FT>::Matrix4& matrixIn, Decomposition& decomposition);

	/// Decomposes M (3x3 matrix). Same as decomposeMatrix for Matrix4, but translation component is Zero
	static void HK_CALL decomposeMatrix (const typename hkRealTypes<FT>::Matrix3& matrixIn, Decomposition& decomposition);

	/// Decomposes M (4x4 matrix, column-major) as M == T * R * Scale * Skew == T * R * ScaleAndSkew.
	/// Useful for conversion both to orthogonal (no skew) and orthonormal (no scale or skew) transforms
	static void HK_CALL decompose4x4ColTransform (const typename hkRealTypes<FT>::Pod* matrixIn, Decomposition& decomposition);

	/// Compute the polar decomposition of the matrix M into U, returns the determinant of U.
	static typename hkRealTypes<FT>::Scalar HK_CALL	polarDecompose(const typename hkRealTypes<FT>::Matrix3& m, typename hkRealTypes<FT>::Matrix3& u, int maxIterations = 128);
};

#include <Common/Base/Math/Matrix/hkMatrixDecomposition.inl>

typedef hkMatrixDecompositionImpl<hkFloat32>  hkMatrixfDecomposition;
typedef hkMatrixDecompositionImpl<hkDouble64> hkMatrixdDecomposition;

#if defined(HK_REAL_IS_DOUBLE)
typedef hkMatrixdDecomposition hkMatrixDecomposition;
#else
typedef hkMatrixfDecomposition hkMatrixDecomposition;
#endif

#endif // HK_MATRIX_DECOMPOSITION_UTIL_H

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
