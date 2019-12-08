/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_MATH_QSTRANSFORMd_H
#define HK_MATH_QSTRANSFORMd_H

#ifndef HK_MATH_MATH_H
#	error Please include Common/Base/hkBase.h instead of this file.
#endif

/// An hkQsTransformd represents a T*R*S transformation where translation is
/// represented with a vector4, rotation is represented with a quaternion and scale
/// is represented with a vector4.
/// When applied to a point (hkVector4d::setTransformedPos()), the point is first scaled, then rotated and
/// finally translated.
/// Direct read/write access to the three components of the hkQsTransformd is available through he public
/// members m_translation, m_rotation, m_scale. Const access can be done through get() methods.
/// It is important to notice that, due to the nature of the TRS representation, and since not all affine
/// transformations can be represented with an hkQsTransformd, operations like multiplications have specific definitions
/// in order to keep the result inside the space of hkQsTransforms.
/// For more information about this, please check the Havok User Manual.
class hkQsTransformd
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_MATH, hkQsTransformd);
		HK_DECLARE_POD_TYPE();

#ifndef HK_DISABLE_MATH_CONSTRUCTORS

			// This enum is used to specify a constructor that initializes to identity
		enum IdentityInitializer
		{
			IDENTITY,
		};

			// This enum is used to specify a constructor that initializes to zero
		enum ZeroInitializer
		{
			ZERO,
		};

			/// Default constructor - all elements are uninitialized.
		HK_FORCE_INLINE hkQsTransformd() { }

			/// Constructor - hkQsTransformd(hkQsTransformd::IDENTITY) initializes to identity
		HK_FORCE_INLINE hkQsTransformd(IdentityInitializer init);

			/// Constructor - hkQsTransformd(hkQsTransformd::ZERO) initializes to zero
		HK_FORCE_INLINE hkQsTransformd(ZeroInitializer init);

			/// Creates a new hkQsTransformd using the rotation r, translation t and scale s
		HK_FORCE_INLINE hkQsTransformd(hkVector4dParameter translation, hkQuaterniondParameter rotation, hkVector4dParameter scale);

			/// Creates a new hkQsTransformd using the rotation r, translation t. Sets scale to identity (1,1,1)
		HK_FORCE_INLINE hkQsTransformd(hkVector4dParameter translation, hkQuaterniondParameter rotation);

			/// Copy constructor
		HK_FORCE_INLINE hkQsTransformd(const hkQsTransformd& other);

#endif

			/// Sets the hkQsTransformd's values using the rotation quaternion q, translation t and scale s
		HK_FORCE_INLINE void set(hkVector4dParameter translation, hkQuaterniondParameter rotation, hkVector4dParameter scale);

		/// Creates a new hkQsTransformd using the rotation r, translation t. Sets scale to identity (1,1,1)
		HK_FORCE_INLINE void set(hkVector4dParameter translation, hkQuaterniondParameter rotation);

			/// Sets this hkQsTransformd to be the identity transform.
		HK_FORCE_INLINE void setIdentity();

			/// Returns a global identity transform.
		HK_FORCE_INLINE static const hkQsTransformd& HK_CALL getIdentity();

			/// Gets the translation component.
		HK_FORCE_INLINE const hkVector4d& getTranslation() const;

			/// Sets the translation component.
		HK_FORCE_INLINE void setTranslation(hkVector4dParameter t);

			/// Gets the scale component.
		HK_FORCE_INLINE const hkVector4d& getScale() const;
	
			/// Sets the scale component.
		HK_FORCE_INLINE void setScale(hkVector4dParameter s);

			/// Gets the rotation component.
		HK_FORCE_INLINE const hkQuaterniond& getRotation() const;

			/// Sets the rotation component (using a hkQuaterniond).
		HK_FORCE_INLINE void setRotation(hkQuaterniondParameter rotation);

			/// Sets the rotation component (using a hkRotationd).
		HK_FORCE_INLINE void setRotation(const hkRotationd& rotation);

			/// Sets this transform to a linear interpolation of the transforms a and b.
			/// Quaternions are checked for polarity and the resulting rotation is normalized
		HK_FORCE_INLINE void setInterpolate4( const hkQsTransformd& a, const hkQsTransformd& b, hkSimdDouble64Parameter t);

			/// Conversion from hkTransformd. Assume no scale
		void setFromTransformNoScale (const hkTransformd& transform);

			/// Conversion to hkTransformd. Assume no scale
		void copyToTransformNoScale (hkTransformd& transformOut) const;

			/// Conversion from hkTransformd - scale.
		void setFromTransform (const hkTransformd& transform);

			/// Conversion from hkQTransformd
		void setFromTransform(const hkQTransformd& qt);

			/// Conversion to hkTransformd - scale.
		void copyToTransform (hkTransformd& transformOut) const;

			/// Sets this transform to be the inverse of the given transform t.
		HK_FORCE_INLINE void setInverse( const hkQsTransformd &t );

			/// Sets this transform to be the product of t1 and t2. (this = t1 * t2)
		HK_FORCE_INLINE void setMul( const hkQsTransformd &t1, const hkQsTransformd &t2 );

			/// Sets this transform to be the product of t1 and t2. (this = t1 * t2), including scaling of translation.
		HK_FORCE_INLINE void setMulScaled( const hkQsTransformd &t1, const hkQsTransformd &t2 );

			/// Sets this transform to be the product of the inverse of t1 by t2. (this = t1^-1 * t2)
		HK_FORCE_INLINE void setMulInverseMul( const hkQsTransformd& t1, const hkQsTransformd &t2 );

		/// Sets this transform to be the product of t1 and the inverse of t2. (this = t1 * t2^-1)
		HK_FORCE_INLINE void setMulMulInverse( const hkQsTransformd &t1, const hkQsTransformd &t2 );

		/// Sets this transform to be the product of itself and the transform b. (this *= b)
		HK_FORCE_INLINE void setMulEq( const hkQsTransformd& b );

			/// Writes a 4x4 matrix suitable for rendering into p.
		void get4x4ColumnMajor(hkDouble64* HK_RESTRICT p) const;

			/// Sets the components from a 4x4 matrix. Returns false if the matrix cannot be
			/// decomposed to form a proper hkQsTransformd.
		bool set4x4ColumnMajor(const hkDouble64* p);

			/// Sets the components from an hkMatrix4. Returns false if the matrix cannot be
			/// decomposed to form a proper hkQsTransform.
		bool set(const hkMatrix4d& m);

			/// Checks for bad values (denormals or infinities) and normalization of the quaternion (within \a epsilon).
		bool isOk(const hkDouble64 epsilon = hkDouble64(1e-3f)) const;

			/// Checks if this transform is equal to the other within an optional epsilon.
		bool isApproximatelyEqual( const hkQsTransformd& other, hkDouble64 epsilon=hkDouble64(1e-3f) ) const;

		HK_FORCE_INLINE hkBool32 isScaleUniform() const;

			/*
			** Blending operations
			*/

			/// Prepares the qs transform for blending (sets all to zero)
		HK_FORCE_INLINE void setZero();
			
			/// Blends a weighted qs transform into this one.
			/// Quaternions are checked for polarity but the resulting rotation is NOT normalized.
			/// Start with a hkQsTransformd with all zeros (including the quaternion).
			/// Call blendAddMul for each transform.
			/// Call blendNormalize or fastRenormalize when finished blending.
		HK_FORCE_INLINE void blendAddMul(const hkQsTransformd& other, hkSimdDouble64Parameter weight );
		HK_FORCE_INLINE void blendAddMul(const hkQsTransformd& other );

		/// Weights this QsTransform by a real number for blending
		HK_FORCE_INLINE void blendWeight(hkSimdDouble64Parameter weight );


			/// Renormalizes after blending. If a total weight is given,
			/// the whole transformation is weighted by 1.0f / total weight.
			/// Takes the "near zero" and "near one" cases into account.
		HK_FORCE_INLINE void blendNormalize( hkSimdDouble64Parameter totalWeight );
		HK_FORCE_INLINE void blendNormalize();

			/// Renormalizes without error checking.
			/// This should not be used for transforms that require frame coherency
			/// as numerical drift can occur far from origin (eg. character worldFromModel).
		HK_FORCE_INLINE void fastRenormalize( hkSimdDouble64Parameter totalWeight );
		HK_FORCE_INLINE void fastRenormalize();

			/// Renormalizes a group of quaternions at once. This allows for some
			/// vector optimizations on different platforms.
			/// This should not be used for transforms that require frame coherency
			/// as numerical drift can occur far from origin (eg. character worldFromModel).
		static void HK_CALL fastRenormalizeBatch( hkQsTransformd* poseOut, hkDouble64* weight, hkUint32 numTransforms);
		static void HK_CALL fastRenormalizeBatch( hkQsTransformd* poseOut, hkDouble64 weight, hkUint32 numTransforms);
		static void HK_CALL fastRenormalizeQuaternionBatch( hkQsTransformd* poseOut, hkUint32 numTransforms );

	public:

			/// Direct access to the translation component (vector4) of this hkQsTransformd.
			/// Fourth component is not used.
		hkVector4d m_translation;

			/// Direct access to the rotation component (quaternion) of this hkQsTransformd
		hkQuaterniond m_rotation;

			/// Direct access to the scale component (vector4) of this hkQsTransformd.
			/// The fourth component is not used.
		hkVector4d m_scale;
};

#endif //HK_MATH_QSTRANSFORMd_H

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
