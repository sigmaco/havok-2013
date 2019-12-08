/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_MATH_FLOAT_16_TRANSFORM_H
#define HK_MATH_FLOAT_16_TRANSFORM_H

	/// Rigid transform that stores the rotation and translation as 12 hkFloat16 values (i.e. 3
	/// hkFloat16 4-vectors). The matrix is stored in column major format, with the translation
	/// encoded in the vectors' .w components.
class hkFloat16Transform
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_MATH, hkFloat16Transform);
		HK_DECLARE_REFLECTION();
		HK_DECLARE_POD_TYPE();
	public:

			/// Inlined. Sets this transform from a hkTransformf.
		template <hkMathRoundingMode R>
		HK_FORCE_INLINE void _set(const hkTransformf& transformIn);
			/// Inlined. Sets this transform from a hkTransformf.
		template <hkMathRoundingMode R>
		HK_FORCE_INLINE void _set(const hkTransformd& transformIn);

			/// Sets this transform from a hkTransformf.
		template <hkMathRoundingMode R>
		void set(const hkTransformf& transformIn);

			/// Sets this transform from a hkTransformd.
		template <hkMathRoundingMode R>
		void set(const hkTransformd& transformIn);

			/// Inlined. Converts this to a hkTransformf.
		HK_FORCE_INLINE void _getTransform(hkTransformf& transformOut) const;

			/// Inlined. Converts this to a hkTransformd.
		HK_FORCE_INLINE void _getTransform(hkTransformd& transformOut) const;

			/// Converts this to a hkTransformf.
		void getTransform(hkTransformf& transformOut) const;

			/// Converts this to a hkTransformd.
		void getTransform(hkTransformd& transformOut) const;

			/// Read-only access to the columns
		template <int I>
		HK_FORCE_INLINE const hkFloat16* getColumn() const { return &m_elements[I << 2]; }

			/// Read-write access to the columns
		template <int I>
		HK_FORCE_INLINE hkFloat16* getColumn() { return &m_elements[I << 2]; }

	protected:

			/// The matrix elements
		hkFloat16 m_elements[12];
};

#include <Common/Base/Math/Float16Transform/hkFloat16Transform.inl>

#endif	//	HK_MATH_FLOAT_16_TRANSFORM_H

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
