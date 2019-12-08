/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_MATH_MATRIX4d_H
#define HK_MATH_MATRIX4d_H

#ifndef HK_MATH_MATH_H
#	error Please include Common/Base/hkBase.h instead of this file.
#endif

namespace hkCompileError
{
	template <bool b> struct HK_MATRIX4d_FUNC_NOT_IMPLEMENTED;
	template <> struct HK_MATRIX4d_FUNC_NOT_IMPLEMENTED<true>{ };
}
#define HK_MATRIX4d_NOT_IMPLEMENTED HK_COMPILE_TIME_ASSERT2(N==0, HK_MATRIX4d_FUNC_NOT_IMPLEMENTED)

/// A 4x4 matrix of hkReals, representing a transformation.
/// This transform representation is used by tools, cloth and display libraries, as
/// it can represent scale and skew.
/// Elements are stored in column major format,
/// i.e., contiguous memory locations are (x00, x10, x20, x30), (x01, x11,...)
/// where x10 means row 1, column 0 for example.
/// For orthonormal transforms, use hkTransformd instead (storage is equivalent).
/// Some operations in hkMatrix4d are optimized for affine matrices (those where
/// the last row is 0,0,0,1).
class hkMatrix4d
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_MATH, hkMatrix4d);
		HK_DECLARE_POD_TYPE();

#ifndef HK_DISABLE_MATH_CONSTRUCTORS
			/// Empty constructor. The elements of the matrix are not initialized.
		HK_FORCE_INLINE hkMatrix4d() { } 
#endif

			/// Gets a read-only reference to the i'th column.
		HK_FORCE_INLINE const hkVector4d& getColumn(int i) const;

			/// Gets a read-write reference to the i'th column.
		HK_FORCE_INLINE hkVector4d& getColumn(int i);

		HK_FORCE_INLINE void setColumn(int i, hkVector4dParameter c);

		template <int I>
		HK_FORCE_INLINE const hkVector4d& getColumn() const;

		template <int I>
		HK_FORCE_INLINE void setColumn(hkVector4dParameter c);

			/// Returns a copy of the i'th row.
		HK_FORCE_INLINE void getRow( int row, hkVector4d& r) const;

		template <int I>
		HK_FORCE_INLINE void getRow( hkVector4d& r ) const;

		HK_FORCE_INLINE void setRow( int row, hkVector4dParameter r );

		template <int I>
		HK_FORCE_INLINE void setRow( hkVector4dParameter r );

			/// Gets read-write access to the specified element.
		HK_FORCE_INLINE hkDouble64& operator() (int row, int col);

			/// Gets read-only access to the specified elements.
		HK_FORCE_INLINE const hkDouble64& operator() (int row, int col) const;

		template <int ROW, int COL>
		HK_FORCE_INLINE const hkSimdDouble64 getElement() const;

		template <int ROW, int COL>
		HK_FORCE_INLINE void setElement(hkSimdDouble64Parameter s);

			/// Sets all rows at once.
		HK_FORCE_INLINE void setRows( hkVector4dParameter r0, hkVector4dParameter r1, hkVector4dParameter r2, hkVector4dParameter r3);

			/// Writes the rows 0 to 3 in to the parameters r0, r1, r2, r3 respectively.
		HK_FORCE_INLINE void getRows( hkVector4d& r0, hkVector4d& r1, hkVector4d& r2, hkVector4d& r3) const;

			/// Sets all columns of the current matrix. Where column is set to r0 and so on.
		HK_FORCE_INLINE void setCols( hkVector4dParameter c0, hkVector4dParameter c1, hkVector4dParameter c2, hkVector4dParameter c3);

			/// Writes the columns 0 to 3 into the parameters c0, c1, c2 and c3 respectively.
		HK_FORCE_INLINE void getCols( hkVector4d& c0, hkVector4d& c1, hkVector4d& c2, hkVector4d& c3) const;

			/// Zeroes all values in this matrix.
		HK_FORCE_INLINE void setZero();

			/// Sets the specified diagonal values, zeroes the non-diagonal values.
		HK_FORCE_INLINE void setDiagonal( hkDouble64 m00, hkDouble64 m11, hkDouble64 m22, hkDouble64 m33 );

		HK_FORCE_INLINE void setDiagonal( hkSimdDouble64Parameter m00, hkSimdDouble64Parameter m11, hkSimdDouble64Parameter m22, hkSimdDouble64Parameter m33 );

		HK_FORCE_INLINE void setDiagonal( hkVector4dParameter v );

		HK_FORCE_INLINE void getDiagonal( hkVector4d& v ) const;

			/// Sets the diagonal values to 1, zeroes the non-diagonal values.
		HK_FORCE_INLINE void setIdentity();

			/// Returns a global identity transform.
		HK_FORCE_INLINE static const hkMatrix4d& HK_CALL getIdentity();

			/// Set the contents based on the given hkTransformd. Will set the bottom row to (0,0,0,1) in this hkMatrix4d as
			/// it is undefined in a hkTransformd (not used)
		HK_FORCE_INLINE void set (const hkTransformd& t);

			/// Set the contents based on the given hkQTransformd. Will set the bottom row to (0,0,0,1).
		void set (const hkQTransformd& qt);

			/// Set the contents based on the given hkQsTransformd. Will set the bottom row to (0,0,0,1).
		void set (const hkQsTransformd& qt);


			/// Configure the given transform with the content of self. As the transform is missing the bottom matrix row,
			/// it is simply discarded. Converting back and forth will thus not give the same matrix.
		HK_FORCE_INLINE void get (hkTransformd& t) const;

			/// Writes a 4x4 matrix to \a p in column-major order. 
			/// The pointer \a p must be suitably aligned, depending on the math lib build.
			/// See the notes for aligned store in hkVector4d.
		void get4x4ColumnMajor(hkFloat32* HK_RESTRICT p) const;
		void get4x4ColumnMajor(hkDouble64* HK_RESTRICT p) const;

			/// Reads a 4x4 matrix from \a p in column-major order.
			/// The pointer \a p must be suitably aligned, depending on the math lib build.
			/// See the notes for aligned load in hkVector4d.
		void set4x4ColumnMajor(const hkFloat32* p);
		void set4x4ColumnMajor(const hkDouble64* p);

			/// Writes a 4x4 matrix to \a p in row-major order. 
			/// The pointer \a p must be suitably aligned, depending on the math lib build.
			/// See the notes for aligned store in hkVector4d.
		void get4x4RowMajor(hkFloat32* HK_RESTRICT p) const;
		void get4x4RowMajor(hkDouble64* HK_RESTRICT p) const;

			/// Reads a 4x4 matrix from \a p in row-major order.
			/// The pointer \a p must be suitably aligned, depending on the math lib build.
			/// See the notes for aligned load in hkVector4d.
		void set4x4RowMajor(const hkFloat32* p);
		void set4x4RowMajor(const hkDouble64* p);

			/// Checks if this matrix is equal to m within an optional epsilon.
		HK_FORCE_INLINE bool isApproximatelyEqual ( const hkMatrix4d& m, hkSimdDouble64Parameter epsilon ) const;

			/// Checks if this matrix is identity within \a epsilon.
		HK_FORCE_INLINE hkBool32 isApproximatelyIdentity ( hkSimdDouble64Parameter epsilon ) const;

			/// Transposes this matrix in place.
		void transpose();

			/// set to the transpose of another matrix
		HK_FORCE_INLINE void setTranspose( const hkMatrix4d& s );
		
			/// (Assumes transforms are affine) Set this matrix to be the product of a and b. (this = a * b)
		HK_FORCE_INLINE void setMulAffine ( const hkMatrix4d& a, const hkMatrix4d& b );

			/// (Non-affine version - slower) Set this matrix to be the product of a and b. (this = a * b)
		HK_FORCE_INLINE void setMul ( const hkMatrix4d& a, const hkMatrix4d& b );

			/// Sets this matrix to be the product of a and scale (this = a * scale)
		HK_FORCE_INLINE void setMul( hkSimdDouble64Parameter scale, const hkMatrix4d& a );

			/// Modifies this matrix by adding the matrix a to it. (this += a)
		void add ( const hkMatrix4d& a );

			/// Modifies this matrix by adding the matrix a to it. (this += a)
			/// This method is enforced inline.
		HK_FORCE_INLINE void _add ( const hkMatrix4d& a );

			/// Modifies this matrix by subtracting the matrix a from it. (this += a)
		void sub ( const hkMatrix4d& a );

			/// (Assumes transforms are affine) Modifies this matrix by post multiplying it by the matrix a. (this = this*a)
		HK_FORCE_INLINE void mulAffine ( const hkMatrix4d& a);

			/// (Non-affine version - slower) modifies this matrix by post multiplying it by the matrix a. (this = this*a)
		HK_FORCE_INLINE void mul ( const hkMatrix4d& a);

			/// Modifies this matrix by multiplying by scale (this *= scale)
		HK_FORCE_INLINE void mul ( hkSimdDouble64Parameter scale );

			/// Copies all elements from a into this matrix.
		HK_FORCE_INLINE void operator= ( const hkMatrix4d& a );

			/// Checks for bad values (denormals or infinities)
		bool isOk() const;

			/// Checks whether the matrix represents an affine transformation (the 4th row is 0,0,0,1)
		hkBool32 isAffineTransformation() const;

			/// Forces the matrix to represent an affine transformation (resets the 4th row to 0,0,0,1)
		void resetFourthRow ();

			/// Transforms a position - implicitly sets positionIn.w to 1.0f. positionOut.w is undefined
		HK_FORCE_INLINE void transformPosition (hkVector4dParameter positionIn, hkVector4d& positionOut) const;

			/// Transforms a direction - implicitly sets directionIn.w to 0.0f, the directionOut.w is undefined.
		HK_FORCE_INLINE void transformDirection (hkVector4dParameter directionIn, hkVector4d& directionOut) const;

			/// Transforms a direction with the transposed of this - implicitly sets directionIn.w to 0.0f.
		HK_FORCE_INLINE void transformInverseDirection (hkVector4dParameter directionIn, hkVector4d& directionOut) const;

			/// Multiplies a 4-element vector by this matrix4. Notice that the 4th component of the vector (w) is very relevant here.
			/// Use "transformPosition" or "transformDirection" to transform vectors representing positions or directions by matrices
			/// representing transformations.
		HK_FORCE_INLINE void multiplyVector (hkVector4dParameter vectorIn, hkVector4d& resultOut) const;

	protected:
		friend class hkQuaterniond;

		hkVector4d m_col0;
		hkVector4d m_col1;
		hkVector4d m_col2;
		hkVector4d m_col3;
};

#endif // HK_MATH_MATRIX4d_H

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
