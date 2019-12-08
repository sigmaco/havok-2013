/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_MATH_MATRIX3d_H
#define HK_MATH_MATRIX3d_H

#ifndef HK_MATH_MATH_H
#	error Please include Common/Base/hkBase.h instead of this file.
#endif

namespace hkCompileError
{
	template <bool b> struct HK_MATRIX3d_FUNC_NOT_IMPLEMENTED;
	template <> struct HK_MATRIX3d_FUNC_NOT_IMPLEMENTED<true>{ };
}
#define HK_MATRIX3d_NOT_IMPLEMENTED HK_COMPILE_TIME_ASSERT2(N==0, HK_MATRIX3d_FUNC_NOT_IMPLEMENTED)

#if defined(HK_TINY_SPU_ELF)
#define HK_MATRIX3d_INLINE HK_ALWAYS_INLINE
#else
#define HK_MATRIX3d_INLINE HK_FORCE_INLINE
#endif

/// A 3x3 matrix of hkReals.
/// Due to alignment issues internal storage is 12 hkReals in a 4x3 matrix.
/// Elements are stored in column major format.
///
/// i.e., contiguous memory locations are (x00, x10, x20, pad), (x01, x11,...)
/// where x10 means row 1, column 0 for example.
class hkMatrix3d
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_MATH, hkMatrix3d);
		HK_DECLARE_POD_TYPE();

#ifndef HK_DISABLE_MATH_CONSTRUCTORS
			/// Empty constructor. The elements of the matrix are not initialized.
		HK_ALWAYS_INLINE hkMatrix3d() {}

			/// Copy matrix from 'other'.
		HK_FORCE_INLINE hkMatrix3d( const hkMatrix3d& other );
#endif

			/// Gets a read-write reference to the i'th column.
		HK_FORCE_INLINE hkVector4d& getColumn(int i);

			/// Gets a read-only reference to the i'th column.
		HK_FORCE_INLINE const hkVector4d& getColumn(int i) const;
		template <int I> HK_MATRIX3d_INLINE const hkVector4d& getColumn() const;

		template <int I> HK_MATRIX3d_INLINE void setColumn(hkVector4dParameter c);

			/// Gets a read-write reference to the i'th column.
		template <int I> HK_MATRIX3d_INLINE hkVector4d& getColumn();

			/// Returns a copy of the i'th row.
		HK_FORCE_INLINE void getRow( int row, hkVector4d& r) const;
		template <int I> HK_FORCE_INLINE void getRow(hkVector4d& r) const;

			/// Gets read-write access to the specified element.
		HK_FORCE_INLINE hkDouble64& operator() (int row, int col);

			/// Gets read-only access to the specified elements.
		HK_FORCE_INLINE const hkDouble64& operator() (int row, int col) const;

		template <int ROW, int COL> HK_FORCE_INLINE const hkSimdDouble64 getElement() const;
		template <int ROW, int COL> HK_FORCE_INLINE void setElement(hkSimdDouble64Parameter s);

			/// Sets all rows at once.
		HK_FORCE_INLINE void setRows( hkVector4dParameter r0, hkVector4dParameter r1, hkVector4dParameter r2);

			/// Writes the rows 0 to 2 in to the parameters r0, r1 and r2 respectively.
		HK_FORCE_INLINE void getRows( hkVector4d& r0, hkVector4d& r1, hkVector4d& r2) const;

			/// Sets all columns of the current matrix. Where column is set to c0 and so on.
		HK_FORCE_INLINE void setCols( hkVector4dParameter c0, hkVector4dParameter c1, hkVector4dParameter c2);

			/// Writes the columns 0 to 2 into the parameters c0, c1 and c2 respectively.
		HK_FORCE_INLINE void getCols( hkVector4d& c0, hkVector4d& c1, hkVector4d& c2) const;

			/// Zeroes all values in this matrix.
		HK_FORCE_INLINE void setZero();

			/// Sets the diagonal values to 1, zeroes the non-diagonal values.
		HK_FORCE_INLINE void setIdentity();

			/// Returns a global identity matrix3.
		HK_FORCE_INLINE static const hkMatrix3d& HK_CALL getIdentity();

			/// Checks if this matrix is equal to m within an optional epsilon.
		bool isApproximatelyEqual( const hkMatrix3d& m, hkDouble64 epsilon=hkDouble64(1e-3f) ) const;

			/// Checks if this matrix is equal to m within an epsilon.
		bool isApproximatelyEqualSimd( const hkMatrix3d& m, hkSimdDouble64Parameter eps) const;
		
			/// Checks if this matrix is symmetric to within an optional epsilon.
		bool isSymmetric( hkDouble64 epsilon=hkDouble64(1e-3f) ) const;

			/// Sets this to be r star (cross skew symmetric of vector r).
		void setCrossSkewSymmetric( hkVector4dParameter r );

			/// Inverts the matrix. This function returns HK_SUCCESS if the determinant is greater than epsilon^3. Otherwise it returns HK_FAILURE and the matrix values are undefined.
		hkResult invert(hkDouble64 epsilon); 

			/// Sets the current matrix to be the inverse of the given matrix. Matrix src is assumed to be symmetric non-singular. If the matrix
			/// is singular (up to machine precision), the inverse will be set to zero.
		HK_FORCE_INLINE void setInverseSymmetric(const hkMatrix3d& src);

			/// Solves the linear system: (this) * v = b, for v. The matrix is assumed non-singular and symmetric
		HK_FORCE_INLINE void solveSymmetric(hkVector4dParameter b, hkVector4d& v);

			/// Inverts a symmetric matrix. This function assumes an invertible, symmetric, positive-definite matrix
		void invertSymmetric();

			/// Frobenius norm squared
		hkSimdDouble64 frobeniusNormSqr() const ;


		/// Inverts a symmetric matrix. This function assumes an invertible, symmetric, positive-definite matrix
		HK_FORCE_INLINE void _invertSymmetric();

		//	///
		//void setRotatedDiagonalMatrix( const hkRotationd &r, const hkVector4d &diagonalMatrix3 );

			/// Transposes this matrix in place.
		void transpose();

			/// set to the transpose of another matrix
		void setTranspose( const hkMatrix3d& s );

			/// set to the transpose of another matrix
		HK_FORCE_INLINE void _setTranspose( const hkMatrix3d& s );

			/// Set this matrix to be the product of a and b. (this = a * b)
		void setMul( const hkMatrix3d& a, const hkMatrix3d& b );

			/// Set this matrix to be the product of qa and b. (this = qa * b)
		HK_FORCE_INLINE void setMul(hkQuaterniondParameter qa, const hkMatrix3d& b);

			/// Set this matrix to be the product of a and b. (this = a * b)
		HK_FORCE_INLINE void _setMul( const hkMatrix3d& a, const hkMatrix3d& b );

			/// Sets this matrix to be the product of a and the inverse of b. (this = a * b^-1)
		void setMulInverse( const hkMatrix3d& a, const hkRotationd& b );

			/// Sets this matrix to be the product of the inverse of a and b. (this = a^-1 * b)
		void setMulInverseMul( const hkRotationd& a, const hkMatrix3d& b );

			/// Sets this matrix to be the product of a and scale. (this = a * scale)
		void setMul( hkSimdDouble64Parameter scale, const hkMatrix3d& a );

			/// Sets this matrix to be the product of a diagonal matrix (given as a vector) and matrix a. (this = diag * a)
		HK_FORCE_INLINE void setDiagonalMul(hkVector4dParameter vDiag, const hkMatrix3d& a);

			/// Sets this matrix to be the product of a and scale. (this = a * scale)
		HK_FORCE_INLINE void _setMul( hkSimdDouble64Parameter scale, const hkMatrix3d& a );

			/// Adds the same value to all elements of the diagonal
		HK_FORCE_INLINE void addDiagonal(hkSimdDouble64Parameter diag);

			/// Sets this = Transpose(a) * b.
		void setTransposeMul(const hkMatrix3d& a, const hkMatrix3d& b);

			/// Add the product of a and scale. (this += a * scale)
		void addMul( hkSimdDouble64Parameter scale, const hkMatrix3d& a );

			/// Add the product of a and scale. (this += a * scale)
		HK_FORCE_INLINE void _addMul( hkSimdDouble64Parameter scale, const hkMatrix3d& a );

			/// Sets this = A - D, where D is interpreted as a diagonal matrix
		HK_FORCE_INLINE void _setSubDiag(const hkMatrix3d& A, hkVector4dParameter D);

			/// Sets this = A - D, where D is interpreted as a diagonal matrix
		HK_FORCE_INLINE void _setSubDiag(const hkMatrix3d& A, hkSimdDouble64Parameter D);

			/// Rotates this matrix by the rotation matrix t. (this = t * this * t^-1)
		void changeBasis(const hkRotationd& t);

			/// Modifies this matrix by adding the matrix a to it. (this += a)
		void add( const hkMatrix3d& a );

			/// Modifies this matrix by adding the matrix a to it. (this += a)
		HK_FORCE_INLINE void _add( const hkMatrix3d& a );

			/// Modifies this matrix by subtracting the matrix a from it. (this += a)
		void sub( const hkMatrix3d& a );

			/// Modifies this matrix by subtracting the matrix a from it. (this += a)
		HK_FORCE_INLINE void _sub( const hkMatrix3d& a );

			/// Modifies this matrix by post multiplying it by the matrix a. (this = this*a)
		void mul( const hkMatrix3d& a);

			/// Modifies this matrix by multiplying by scale. (this *= scale)
		void mul( hkSimdDouble64Parameter scale );

		/// Modifies this matrix by multiplying by scale. (this *= scale)
		HK_FORCE_INLINE void _mul( hkSimdDouble64Parameter scale );

			/// Copies all elements from a into this matrix.
		HK_FORCE_INLINE void operator= ( const hkMatrix3d& a );

			/// Checks for bad values (denormals or infinities)
		bool isOk() const;

			/// Multiplies a 3-element vector by this 3x3 matrix.
		HK_FORCE_INLINE void multiplyVector (hkVector4dParameter vectorIn, hkVector4d& resultOut) const;

			/// Returns the determinant of this 3x3 matrix.
		const hkSimdDouble64 getDeterminant() const;

			/// Diagonalizes a symmetric matrix, returning the eigenvectors in the columns of eigenVec (which is orthogonal) and the
			/// corresponding eigenvalues in eigenVal, with a specified tolerance epsilon and maximum number of Jacobi iterations maxIter.
			/// Returns HK_SUCCESS if the fractional off-diagonal norm was reduced below the specified epsilon, otherwise HK_FAILURE.
			/// You can interpret the eigenVec as a matrix which rotates points from eigenVal space to this space.
		hkResult diagonalizeSymmetric( hkRotationd& eigenVec, hkVector4d& eigenVal, int maxIter=20, hkDouble64 epsilon=HK_DOUBLE_EPSILON ) const;

			/// Diagonalizes a symmetric matrix using cached eigenvectors, returning the eigenvectors in the columns of eigenVec (which is orthogonal) and the
			/// corresponding eigenvalues in eigenVal, with a specified tolerance epsilon and maximum number of Jacobi iterations maxIter.
			/// Returns HK_SUCCESS if the fractional off-diagonal norm was reduced below the specified epsilon, otherwise HK_FAILURE.
		hkResult diagonalizeSymmetricWarmStart( hkMatrix3d& eigenVec, hkVector4d& eigenVal, int maxIter=20, hkDouble64 epsilon=HK_DOUBLE_EPSILON ) const;

			/// Like diagonalizeSymmetric() but without epsilon checks. Diagonalize by just iterating the max iter of times, no error checking.
		void diagonalizeSymmetricApproximation( hkRotationd& eigenVec, hkVector4d& eigenVal, int maxIter=10 ) const;

	protected:

		hkVector4d m_col0;
		hkVector4d m_col1;
		hkVector4d m_col2;
};

extern "C"
{
	// implementation of _setMul as out of line function with C-binding
	void hkMatrix3d_setMulMat3Mat3( hkMatrix3d* thisMatrix, const hkMatrix3d& aTb, const hkMatrix3d& bTc );
	void hkMatrix3d_invertSymmetric( hkMatrix3d& thisMatrix );
}

#endif //HK_MATH_MATRIX3d_H

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
