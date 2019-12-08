/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_MATH_QUATERNION_UTIL_H
#define HK_MATH_QUATERNION_UTIL_H

#include <Common/Base/Math/Vector/hkVector4Util.h>

/// Utility functions for hkQuaternion
template <typename FT>
struct hkQuaternionUtilImpl
{
	/// Sets qOut to be the shortest rotation which brings 'from' to 'to'.
	/// NOTE: The vectors 'from ' and 'to' must be normalized.
	static HK_FORCE_INLINE void HK_CALL _computeShortestRotation(typename hkRealTypes<FT>::VectorParameter from, typename hkRealTypes<FT>::VectorParameter to, typename hkRealTypes<FT>::Quaternion& qOut);

	/// Sets qOut to be the shortest rotation which brings 'from' to 'to'.
	/// NOTE: The vectors 'from ' and 'to' must be normalized.
	/// This version is damped and the result interpolates from 'from' to to' as gain goes from 0 to 1.
	/// This is similar to scaling the angle of rotation according to the gain.
	
	static HK_FORCE_INLINE void HK_CALL _computeShortestRotationDamped(typename hkRealTypes<FT>::VectorParameter from, typename hkRealTypes<FT>::VectorParameter to, typename hkRealTypes<FT>::ScalarParameter gain, typename hkRealTypes<FT>::Quaternion& qOut);

	/// Computes a 4x4 matrix that allows you to compute any product of the form (this * q) by multiplying (opOut * q).
	/// This is also equal to Transpose(getInversePostMultiplyOperator(this)).
	/// Also, the first 3x3 block is equal to the first 3x3 block of Transpose(getPreMultiplyOperator(this))
	static HK_FORCE_INLINE void HK_CALL _computePostMultiplyOperator(typename hkRealTypes<FT>::QuaternionParameter q, typename hkRealTypes<FT>::Matrix4& opOut);

	/// Computes a 4x4 matrix that allows you to compute any product of the form (q * this) by multiplying (opOut * q).
	/// This is also equal to Transpose(getInversePreMultiplyOperator(this)).
	/// Also, the first 3x3 block is equal to the first 3x3 block of Transpose(getPostMultiplyOperator(this))
	static HK_FORCE_INLINE void HK_CALL _computePreMultiplyOperator(typename hkRealTypes<FT>::QuaternionParameter q, typename hkRealTypes<FT>::Matrix4& opOut);

	/// Computes a 4x4 matrix that allows you to compute any product of the form (Inverse(this) * q) by multiplying (opOut * q).
	/// This is also equal to Transpose(getPostMultiplyOperator(this)).
	static HK_FORCE_INLINE void HK_CALL _computeInversePostMultiplyOperator(typename hkRealTypes<FT>::QuaternionParameter q, typename hkRealTypes<FT>::Matrix4& opOut);

	/// Computes a 4x4 matrix that allows you to compute any product of the form (q * Inverse(this)) by multiplying (opOut * q).
	/// This is also equal to Transpose(getPreMultiplyOperator(this)).
	static HK_FORCE_INLINE void HK_CALL _computeInversePreMultiplyOperator(typename hkRealTypes<FT>::QuaternionParameter q, typename hkRealTypes<FT>::Matrix4& opOut);

	/// Computes qOut = Transpose(op) * qIn, where op is a 4x4 matrix operator and qIn is a quaternion interpreted as a 4-element vector.
	static HK_FORCE_INLINE void HK_CALL _computeTransposeMul(const typename hkRealTypes<FT>::Matrix4& op, typename hkRealTypes<FT>::QuaternionParameter qIn, typename hkRealTypes<FT>::Quaternion& qOut);

	///	Computes the logarithm of a quaternion
	static HK_FORCE_INLINE void HK_CALL _computeLog(typename hkRealTypes<FT>::QuaternionParameter q, typename hkRealTypes<FT>::Vector& vOut);

	///	Computes the the exponential (quaternion) of the given (axis-angle) vector
	static HK_FORCE_INLINE void HK_CALL _computeExp(typename hkRealTypes<FT>::VectorParameter vIn, typename hkRealTypes<FT>::Quaternion& qOut);
	static HK_FORCE_INLINE void HK_CALL _computeExp_Approximate(typename hkRealTypes<FT>::VectorParameter vIn, typename hkRealTypes<FT>::Quaternion& qOut);

	/// N-lerp
	static HK_FORCE_INLINE void HK_CALL _computeNlerp(typename hkRealTypes<FT>::QuaternionParameter q0, typename hkRealTypes<FT>::QuaternionParameter q1, typename hkRealTypes<FT>::ScalarParameter t, typename hkRealTypes<FT>::Quaternion& qOut);

	/// Computes a clamped quaternion such that the rotation angle is less than the given value
	static HK_FORCE_INLINE hkBool32 HK_CALL _computeClampedRotation(typename hkRealTypes<FT>::QuaternionParameter q0, typename hkRealTypes<FT>::ScalarParameter cosMaxAngle, typename hkRealTypes<FT>::Quaternion& qClamped);

	/// Computes the maximum angular velocity that can be applied to quaternion qA along rotation axis dw (ASSUMED normalized) that will keep
	/// the relative angle between qA and qB under the given threshold.
	static HK_FORCE_INLINE const typename hkRealTypes<FT>::Scalar HK_CALL _computeMaximumAllowedVelocity(typename hkRealTypes<FT>::QuaternionParameter qA, typename hkRealTypes<FT>::QuaternionParameter qB, typename hkRealTypes<FT>::VectorParameter dw, typename hkRealTypes<FT>::ScalarParameter cosMaxAngle);

	/// Increments (integrates) the given quaternion with the given axis-angle delta
	static HK_FORCE_INLINE void HK_CALL _increment(typename hkRealTypes<FT>::QuaternionParameter qSrc, typename hkRealTypes<FT>::VectorParameter axisAngleDelta, typename hkRealTypes<FT>::Quaternion& qDst);

	/// Computes the cosine of the rotation angle
	static HK_FORCE_INLINE const typename hkRealTypes<FT>::Scalar HK_CALL _computeCosRotationAngle(typename hkRealTypes<FT>::QuaternionParameter q);
};

#include <Common/Base/Math/Quaternion/hkQuaternionUtil.inl>

typedef hkQuaternionUtilImpl<hkFloat32>  hkQuaternionfUtil;
typedef hkQuaternionUtilImpl<hkDouble64> hkQuaterniondUtil;

#if defined(HK_REAL_IS_DOUBLE)
typedef hkQuaterniondUtil hkQuaternionUtil;
#else
typedef hkQuaternionfUtil hkQuaternionUtil;
#endif

#endif	//	HK_MATH_QUATERNION_UTIL_H

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
