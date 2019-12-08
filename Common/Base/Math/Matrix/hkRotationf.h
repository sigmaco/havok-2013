/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_MATH_ROTATIONf_H
#define HK_MATH_ROTATIONf_H

#ifndef HK_MATH_MATH_H
#	error Please include Common/Base/hkBase.h instead of this file.
#endif

#ifdef HK_COMPILER_MSVC
#	define HK_FORCE_ALIGN_ROTATION __declspec(align(HK_FLOAT_ALIGNMENT))
#else
#	define HK_FORCE_ALIGN_ROTATION
#endif

/// Stores an orthonormal rotation matrix.
/// This is the fastest way to represent a rotation in Havok.
/// If using an hkQuaternionf is more convenient, it is possible to convert
/// back and forth between an hkRotationf and an hkQuaternionf.
/// hkRotations are assumed to be orthonormal i.e., that any given hkRotationf r
/// should satisfy the property transpose(r) = (r^-1)
class HK_FORCE_ALIGN_ROTATION hkRotationf : public hkMatrix3f
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_MATH, hkRotationf);
		HK_DECLARE_POD_TYPE();

			/// Sets/initializes this rotation matrix from the quaternion q.
		void set(hkQuaternionfParameter q);

			/// Sets/initializes this rotation matrix from the given rotation axis and angle.
		void setAxisAngle(hkVector4fParameter axis, hkFloat32 angle);
		void setAxisAngle(hkVector4fParameter axis, hkSimdFloat32Parameter angle);

			/// Check if this rotation orthonormal to the given epsilon.
			/// The default epsilon is set so that it passes a rotation constructed from
			/// a quaternion (normalized with normalize() )
		bool isOrthonormal( hkFloat32 epsilon = hkFloat32(1e-5f) ) const;

			/// Checks for bad values (denormals or infinities) and orthogonality.
		bool isOk() const;

			/// Renormalize a drifted rotation.
		void renormalize();
};

#undef HK_FORCE_ALIGN_ROTATION

#endif //HK_MATH_ROTATIONf_H

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
