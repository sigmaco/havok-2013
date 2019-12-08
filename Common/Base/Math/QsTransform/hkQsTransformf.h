/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_MATH_QSTRANSFORMf_H
#define HK_MATH_QSTRANSFORMf_H

#ifndef HK_MATH_MATH_H
#	error Please include Common/Base/hkBase.h instead of this file.
#endif

/// An hkQsTransformf represents a T*R*S transformation where translation is
/// represented with a vector4, rotation is represented with a quaternion and scale
/// is represented with a vector4.
/// When applied to a point (hkVector4f::setTransformedPos()), the point is first scaled, then rotated and
/// finally translated.
/// Direct read/write access to the three components of the hkQsTransformf is available through he public
/// members m_translation, m_rotation, m_scale. Const access can be done through get() methods.
/// It is important to notice that, due to the nature of the TRS representation, and since not all affine
/// transformations can be represented with an hkQsTransformf, operations like multiplications have specific definitions
/// in order to keep the result inside the space of hkQsTransforms.
/// For more information about this, please check the Havok User Manual.
class hkQsTransformf
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_MATH, hkQsTransformf);
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
		HK_FORCE_INLINE hkQsTransformf() { }

			/// Constructor - hkQsTransformf(hkQsTransformf::IDENTITY) initializes to identity
		HK_FORCE_INLINE hkQsTransformf(IdentityInitializer init);

			/// Constructor - hkQsTransformf(hkQsTransformf::ZERO) initializes to zero
		HK_FORCE_INLINE hkQsTransformf(ZeroInitializer init);

			/// Creates a new hkQsTransformf using the rotation r, translation t and scale s
		HK_FORCE_INLINE hkQsTransformf(hkVector4fParameter translation, hkQuaternionfParameter rotation, hkVector4fParameter scale);

			/// Creates a new hkQsTransformf using the rotation r, translation t. Sets scale to identity (1,1,1)
		HK_FORCE_INLINE hkQsTransformf(hkVector4fParameter translation, hkQuaternionfParameter rotation);

			/// Copy constructor
		HK_FORCE_INLINE hkQsTransformf(const hkQsTransformf& other);

#endif

			/// Sets the hkQsTransformf's values using the rotation quaternion q, translation t and scale s
		HK_FORCE_INLINE void set(hkVector4fParameter translation, hkQuaternionfParameter rotation, hkVector4fParameter scale);

		/// Creates a new hkQsTransformf using the rotation r, translation t. Sets scale to identity (1,1,1)
		HK_FORCE_INLINE void set(hkVector4fParameter translation, hkQuaternionfParameter rotation);

			/// Sets this hkQsTransformf to be the identity transform.
		HK_FORCE_INLINE void setIdentity();

			/// Returns a global identity transform.
		HK_FORCE_INLINE static const hkQsTransformf& HK_CALL getIdentity();

			/// Gets the translation component.
		HK_FORCE_INLINE const hkVector4f& getTranslation() const;

			/// Sets the translation component.
		HK_FORCE_INLINE void setTranslation(hkVector4fParameter t);

			/// Gets the scale component.
		HK_FORCE_INLINE const hkVector4f& getScale() const;
	
			/// Sets the scale component.
		HK_FORCE_INLINE void setScale(hkVector4fParameter s);

			/// Gets the rotation component.
		HK_FORCE_INLINE const hkQuaternionf& getRotation() const;

			/// Sets the rotation component (using a hkQuaternionf).
		HK_FORCE_INLINE void setRotation(hkQuaternionfParameter rotation);

			/// Sets the rotation component (using a hkRotationf).
		HK_FORCE_INLINE void setRotation(const hkRotationf& rotation);

			/// Sets this transform to a linear interpolation of the transforms a and b.
			/// Quaternions are checked for polarity and the resulting rotation is normalized
		HK_FORCE_INLINE void setInterpolate4( const hkQsTransformf& a, const hkQsTransformf& b, hkSimdFloat32Parameter t);

			/// Conversion from hkTransformf. Assume no scale
		void setFromTransformNoScale (const hkTransformf& transform);

			/// Conversion to hkTransformf. Assume no scale
		void copyToTransformNoScale (hkTransformf& transformOut) const;

			/// Conversion from hkTransformf - scale.
		void setFromTransform (const hkTransformf& transform);

			/// Conversion from hkQTransformf
		void setFromTransform(const hkQTransformf& qt);

			/// Conversion to hkTransformf - scale.
		void copyToTransform (hkTransformf& transformOut) const;

			/// Sets this transform to be the inverse of the given transform t.
		HK_FORCE_INLINE void setInverse( const hkQsTransformf &t );

			/// Sets this transform to be the product of t1 and t2. (this = t1 * t2)
		HK_FORCE_INLINE void setMul( const hkQsTransformf &t1, const hkQsTransformf &t2 );

			/// Sets this transform to be the product of t1 and t2. (this = t1 * t2), including scaling of translation.
		HK_FORCE_INLINE void setMulScaled( const hkQsTransformf &t1, const hkQsTransformf &t2 );

			/// Sets this transform to be the product of the inverse of t1 by t2. (this = t1^-1 * t2)
		HK_FORCE_INLINE void setMulInverseMul( const hkQsTransformf& t1, const hkQsTransformf &t2 );

		/// Sets this transform to be the product of t1 and the inverse of t2. (this = t1 * t2^-1)
		HK_FORCE_INLINE void setMulMulInverse( const hkQsTransformf &t1, const hkQsTransformf &t2 );

		/// Sets this transform to be the product of itself and the transform b. (this *= b)
		HK_FORCE_INLINE void setMulEq( const hkQsTransformf& b );

			/// Writes a 4x4 matrix suitable for rendering into p.
		void get4x4ColumnMajor(hkFloat32* HK_RESTRICT p) const;

			/// Sets the components from a 4x4 matrix. Returns false if the matrix cannot be
			/// decomposed to form a proper hkQsTransformf.
		bool set4x4ColumnMajor(const hkFloat32* p);

			/// Sets the components from an hkMatrix4. Returns false if the matrix cannot be
			/// decomposed to form a proper hkQsTransform.
		bool set(const hkMatrix4f& m);

			/// Checks for bad values (denormals or infinities) and normalization of the quaternion (within \a epsilon).
		bool isOk(const hkFloat32 epsilon = hkFloat32(1e-3f)) const;

			/// Checks if this transform is equal to the other within an optional epsilon.
		bool isApproximatelyEqual( const hkQsTransformf& other, hkFloat32 epsilon=hkFloat32(1e-3f) ) const;

		HK_FORCE_INLINE hkBool32 isScaleUniform() const;

			/*
			** Blending operations
			*/

			/// Prepares the qs transform for blending (sets all to zero)
		HK_FORCE_INLINE void setZero();
			
			/// Blends a weighted qs transform into this one.
			/// Quaternions are checked for polarity but the resulting rotation is NOT normalized.
			/// Start with a hkQsTransformf with all zeros (including the quaternion).
			/// Call blendAddMul for each transform.
			/// Call blendNormalize or fastRenormalize when finished blending.
		HK_FORCE_INLINE void blendAddMul(const hkQsTransformf& other, hkSimdFloat32Parameter weight );
		HK_FORCE_INLINE void blendAddMul(const hkQsTransformf& other );

		/// Weights this QsTransform by a real number for blending
		HK_FORCE_INLINE void blendWeight(hkSimdFloat32Parameter weight );


			/// Renormalizes after blending. If a total weight is given,
			/// the whole transformation is weighted by 1.0f / total weight.
			/// Takes the "near zero" and "near one" cases into account.
		HK_FORCE_INLINE void blendNormalize( hkSimdFloat32Parameter totalWeight );
		HK_FORCE_INLINE void blendNormalize();

			/// Renormalizes without error checking.
			/// This should not be used for transforms that require frame coherency
			/// as numerical drift can occur far from origin (eg. character worldFromModel).
		HK_FORCE_INLINE void fastRenormalize( hkSimdFloat32Parameter totalWeight );
		HK_FORCE_INLINE void fastRenormalize();

			/// Renormalizes a group of quaternions at once. This allows for some
			/// vector optimizations on different platforms.
			/// This should not be used for transforms that require frame coherency
			/// as numerical drift can occur far from origin (eg. character worldFromModel).
		static void HK_CALL fastRenormalizeBatch( hkQsTransformf* poseOut, hkFloat32* weight, hkUint32 numTransforms);
		static void HK_CALL fastRenormalizeBatch( hkQsTransformf* poseOut, hkFloat32 weight, hkUint32 numTransforms);
		static void HK_CALL fastRenormalizeQuaternionBatch( hkQsTransformf* poseOut, hkUint32 numTransforms );

	public:

			/// Direct access to the translation component (vector4) of this hkQsTransformf.
			/// Fourth component is not used.
		hkVector4f m_translation;

			/// Direct access to the rotation component (quaternion) of this hkQsTransformf
		hkQuaternionf m_rotation;

			/// Direct access to the scale component (vector4) of this hkQsTransformf.
			/// The fourth component is not used.
		hkVector4f m_scale;
};

#endif //HK_MATH_QSTRANSFORMf_H

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
