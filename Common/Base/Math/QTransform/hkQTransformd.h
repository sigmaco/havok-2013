/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_MATH_Q_TRANSFORMd_H
#define HK_MATH_Q_TRANSFORMd_H

#ifndef HK_MATH_MATH_H
#	error Please include Common/Base/hkBase.h instead of this file.
#endif

	/// An hkQTransformd represents a T*R transformation where translation is
	/// represented with a vector4 and rotation is represented with a quaternion.
	/// When applied to a point (hkVector4d::setTransformedPos()), the point is first rotated and
	/// then translated.
class hkQTransformd
{
public:

	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_MATH, hkQTransformd);
#if defined(HK_REAL_IS_DOUBLE)
	HK_DECLARE_REFLECTION();
#endif
	

	/// Default constructor - all elements are uninitialized.
	HK_FORCE_INLINE hkQTransformd() { }

	/// Creates a new hkQTransformd using the rotation quaternion q and translation t.
	HK_FORCE_INLINE hkQTransformd(hkQuaterniondParameter q, hkVector4dParameter t);

	/// Copy constructor
	HK_FORCE_INLINE hkQTransformd(const hkQTransformd& qt);

	HK_FORCE_INLINE hkQTransformd(class hkFinishLoadedObjectFlag f);

	/// Sets the hkQTransformd's values using the rotation quaternion q and translation t.
	HK_FORCE_INLINE void set(hkQuaterniondParameter q, hkVector4dParameter t);

	/// Sets the hkQTransformd's values from a hkTransformd.
	HK_FORCE_INLINE void set(const hkTransformd& otherTransform);

	/// Sets this hkQTransformd to be the identity transform.
	HK_FORCE_INLINE void setIdentity();

	/// Sets this hkQTransformd to zero
	HK_FORCE_INLINE void setZero();

	/// Sets this += qa. The rotations are added as vectors, no attempt is made to re-normalize the quaternion.
	HK_FORCE_INLINE void add(const hkQTransformd& qa);

	/// Returns a global identity transform.
	HK_FORCE_INLINE static const hkQTransformd& HK_CALL getIdentity();

	/// Gets the translation component.
	HK_FORCE_INLINE const hkVector4d& getTranslation() const;

	/// Sets the translation component.
	HK_FORCE_INLINE void setTranslation(hkVector4dParameter t);

	/// Gets the rotation component.
	HK_FORCE_INLINE const hkQuaterniond& getRotation() const;

	/// Sets the rotation component.
	HK_FORCE_INLINE void setRotation(hkQuaterniondParameter q);

	/// Sets this transform to be the inverse of the given transform qt.
	void setInverse(const hkQTransformd& qt);

	/// Sets this transform to be the inverse of the given transform qt.
	HK_FORCE_INLINE void _setInverse(const hkQTransformd& qt);

	/// Sets this transform to be the product of qt1 and qt2. (this = qt1 * qt2)
	void setMul(const hkQTransformd& qt1, const hkQTransformd& qt2);

	/// Inlined. Sets this transform to be the product of qt1 and qt2. (this = qt1 * qt2)
	HK_FORCE_INLINE void _setMul(const hkQTransformd& qt1, const hkQTransformd& qt2);

	/// Sets this transform to be the product of t1 and qt2. (this = t1 * qt2)
	void setMul(const hkTransformd& t1, const hkQTransformd& qt2);

	/// Sets this transform to be the product of t1 and t2. (this = t1 * t2)
	void setMul(const hkTransformd& t1, const hkTransformd& t2);

	/// Sets this transform to be the product of qt1 and t2. (this = qt1 * t2)
	void setMul(const hkQTransformd& qt1, const hkTransformd& t2);

	/// Sets this transform to be the product of the inverse of qt1 by qt2. (this = qt1^-1 * qt2)
	void setMulInverseMul(const hkQTransformd& qt1, const hkQTransformd& qt2);

	/// Sets this transform to be the product of the inverse of t1 by qt2. (this = t1^-1 * qt2)
	void setMulInverseMul(const hkTransformd& t1, const hkQTransformd& qt2);

	/// Sets this transform to be the product of the inverse of qt1 by t2. (this = qt1^-1 * t2)
	void setMulInverseMul(const hkQTransformd& qt1, const hkTransformd& t2);

	/// Sets this transform to be the product of the inverse of t1 by t2. (this = t1^-1 * t2)
	void setMulInverseMul(const hkTransformd& t1, const hkTransformd& t2);

	/// Sets this transform to be the product of the inverse of qt1 by qt2. (this = qt1^-1 * qt2)
	HK_FORCE_INLINE void _setMulInverseMul(const hkQTransformd& qt1, const hkQTransformd& qt2);

	/// Sets this transform to be the product of qt1 and the inverse of qt2. (this = qt1 * qt2^-1)
	void setMulMulInverse(const hkQTransformd &qt1, const hkQTransformd &qt2);

	/// Sets this transform to be the product of qt1 and the inverse of qt2. (this = qt1 * qt2^-1)
	HK_FORCE_INLINE void _setMulMulInverse(const hkQTransformd &qt1, const hkQTransformd &qt2);

	/// Checks if this transform is equal to the other within an optional epsilon.
	bool isApproximatelyEqual( const hkQTransformd& other, hkDouble64 epsilon=hkDouble64(1e-3f) ) const;

	/// Checks if this transform is equal to the other within an epsilon.
	HK_FORCE_INLINE bool _isApproximatelyEqual( const hkQTransformd& other, hkSimdDouble64Parameter epsilon) const;

	/// Sets this transform to a linear interpolation of the transforms qtA and qtB.
	/// Quaternions are checked for polarity and the resulting rotation is normalized
	void setInterpolate4(const hkQTransformd& qtA, const hkQTransformd& qtB, hkSimdDouble64Parameter t);

	/// Checks for bad values (denormals or infinities)
	bool isOk() const;

public:
	
		/// The rotation part
	hkQuaterniond m_rotation;

		/// The translation part
	hkVector4d m_translation;
};

#endif	// HK_MATH_Q_TRANSFORMd_H

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
