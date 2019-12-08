/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_MATH_TRANSFORMd_H
#define HK_MATH_TRANSFORMd_H

#ifndef HK_MATH_MATH_H
#	error Please include Common/Base/hkBase.h instead of this file.
#endif

/// Stores a rotation and translation.
/// Note that valid hkTransforms always have an orthonormal rotation component.
/// Note that the w component of the columns may not be set correctly. Havok
/// implicitly assumes that the shear components are all 0 and that the w
/// component of the translation is 1. To get a 4x4 matrix suitable for rendering
/// use the get4x4ColumnMajor method.
///
/// The following conventions are adopted:
///     - Internal representation of rotation is column-major
///     - Applying matrix multiplication to a vector is done by premultiplying
///       by the matrix
///
/// IMPORTANT NOTE ON SCALING:
///
/// This class is not designed to represent a full transformation including
/// skewing and scaling components. The assumption is that skewing will not be
/// used and that scaling is not meaningful in a simulation of rigid bodies
/// that only change their position and orientation.
///
/// Do not attempt to put scaling into the rows or columns of the
/// rotation matrix. It must remain orthogonal at all times.
class hkTransformd
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_MATH, hkTransformd);
		HK_DECLARE_POD_TYPE();

#ifndef HK_DISABLE_MATH_CONSTRUCTORS
			/// Default constructor - all elements are uninitialized.
		HK_FORCE_INLINE hkTransformd() { }

			/// Creates a new hkTransformd using the rotation r and translation t.
		HK_FORCE_INLINE hkTransformd(const hkRotationd& r, hkVector4dParameter t);

			/// Copy constructor
		HK_FORCE_INLINE hkTransformd(const hkTransformd& r);

			/// Creates a new hkTransformd using the rotation quaternion q and translation t.
		HK_FORCE_INLINE hkTransformd(hkQuaterniondParameter q, hkVector4dParameter t);
#endif

			/// Read-write access element at (row, column)
		HK_FORCE_INLINE hkDouble64& operator() (int row, int column);

			/// Read-only access element at (row, column)
		HK_FORCE_INLINE const hkDouble64& operator() (int row, int column) const;

		template <int ROW, int COL>
		HK_FORCE_INLINE const hkSimdDouble64 getElement() const;

		template <int ROW, int COL>
		HK_FORCE_INLINE void setElement(hkSimdDouble64Parameter s);

			/// Sets the hkTransformd's values using the rotation quaternion q and translation t.
		HK_FORCE_INLINE void set(hkQuaterniondParameter q, hkVector4dParameter t);
		HK_FORCE_INLINE void set(const hkRotationd& r, hkVector4dParameter t);

			/// Sets this hkTransformd to be the identity transform.
		HK_FORCE_INLINE void setIdentity();

			/// Returns a global identity transform.
		HK_FORCE_INLINE static const hkTransformd& HK_CALL getIdentity();

			/// Checks if this transform is the identity within an optional epsilon
		bool isApproximatelyEqual( const hkTransformd& t, hkDouble64 epsilon=hkDouble64(1e-3f) ) const;

			/// Checks if this transform is the identity within an epsilon
		bool isApproximatelyEqualSimd( const hkTransformd& t, hkSimdDouble64Parameter epsilon ) const;

			/// Gets a writable translation component.
		HK_FORCE_INLINE hkVector4d& getTranslation();

			/// Gets the translation component.
		HK_FORCE_INLINE const hkVector4d& getTranslation() const;

			/// Sets the translation component.
		HK_FORCE_INLINE void setTranslation(hkVector4dParameter t);

			/// Gets a writable rotation component.
		HK_FORCE_INLINE hkRotationd& getRotation();

			/// Gets the rotation component.
		HK_FORCE_INLINE const hkRotationd& getRotation() const;

			/// Sets the rotation component (using a hkRotationd).
		HK_FORCE_INLINE void setRotation(const hkRotationd& rotation);

			/// Sets the rotation component (using a hkQuaterniond).
		HK_FORCE_INLINE void setRotation(hkQuaterniondParameter quatRotation);

			/// Sets this transform to be the inverse of the given transform t.
		void setInverse( const hkTransformd &t );

			/// Sets this transform to be the inverse of the given transform t.
		HK_FORCE_INLINE void _setInverse( const hkTransformd &t );

			/// Sets this transform to be the product of t1 and t2. (this = t1 * t2) (this is an outof line call, inline call is available in hkTransformdUtil)
		void setMul( const hkTransformd &t1, const hkTransformd &t2 );

			/// Sets this transform to be the product of t1 and t2. (this = t1 * t2)
		void setMul( const hkQsTransformd &t1, const hkTransformd &t2 );

			/// Sets this transform to be the product of the inverse of t1 by t2. (this = t1^-1 * t2)
		void setMulInverseMul( const hkTransformd& bTa, const hkTransformd &bTc );

			/// Sets this transform to be the product of the inverse of t1 by t2. (this = t1^-1 * t2)
		HK_FORCE_INLINE void _setMulInverseMul( const hkTransformd& bTa, const hkTransformd &bTc );

			/// Sets this transform to be the product of itself and the transform b. (this *= b)
		void setMulEq( const hkTransformd& b );

			/// Writes a 4x4 matrix to \a p in column-major order. 
			/// The pointer \a p must be suitably aligned, depending on the math lib build.
			/// See the notes for aligned store in hkVector4d.
		void get4x4ColumnMajor(hkFloat32* HK_RESTRICT p) const;
			/// Writes a 4x4 matrix suitable for rendering into \a p. The pointer \a p must be 32-Byte aligned.
		void get4x4ColumnMajor(hkDouble64* HK_RESTRICT p) const;

			/// Reads a 4x4 matrix from \a p in column-major order. The matrix is only valid if there is no scaling present and the rotation is orthonormal.
			/// The pointer \a p must be suitably aligned, depending on the math lib build.
			/// See the notes for aligned load in hkVector4d.
		void set4x4ColumnMajor(const hkFloat32* p);
			/// Reads a 4x4 matrix from \a p. There should be no scaling and the rotation should be orthonormal. The pointer \a p must be 32-Byte aligned.
		void set4x4ColumnMajor(const hkDouble64* p);

			/// Sets all 4 rows at once (including the .w component)
		HK_FORCE_INLINE void setRows4( hkVector4dParameter r0, hkVector4dParameter r1, hkVector4dParameter r2, hkVector4dParameter r3);


			/// Sets this transform to be the product of a and the inverse of b. (this = a * b^-1)
		void setMulMulInverse( const hkTransformd &a, const hkTransformd &b );

			/// Checks for bad values (denormals or infinities).
		bool isOk() const;

			/// Gets a read-write reference to the i'th column.
		HK_FORCE_INLINE hkVector4d& getColumn(int i);

			/// Gets a read-only reference to the i'th column.
		HK_FORCE_INLINE const hkVector4d& getColumn(int i) const;

		template <int I>
		HK_FORCE_INLINE const hkVector4d& getColumn() const;

		template <int I>
		HK_FORCE_INLINE void setColumn(hkVector4dParameter v);

	protected:

		hkRotationd m_rotation;
		hkVector4d m_translation;
};

#endif //HK_MATH_TRANSFORMd_H

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
