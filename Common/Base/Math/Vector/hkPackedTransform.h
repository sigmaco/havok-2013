/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKMATH_MATH_PACKED_TRANSFORM_H
#define HKMATH_MATH_PACKED_TRANSFORM_H

#include <Common/Base/Math/Vector/hkPackedVector3.h>

/// Compressed hkTransformf into 16 bytes.
/// For accuracy informations, please refer to hkPackedVector3 and hkPackUnitVector.
struct hkPackedTransform
{
	HK_FORCE_INLINE void	pack(const hkTransformf& t)		{ hkQuaternionf q; q.set(t.getRotation()); m_translation.pack(t.getTranslation()); m_orientation.pack(q.m_vec); }
	HK_FORCE_INLINE void	unpack(hkTransformf& t) const	{ hkQuaternionf q; m_orientation.unpack(&q.m_vec); m_translation.unpack(t.getTranslation()); t.getRotation().set(q); }

	HK_FORCE_INLINE void	pack(const hkTransformd& t)		{ hkQuaterniond q; q.set(t.getRotation()); m_translation.pack(t.getTranslation()); m_orientation.pack(q.m_vec); }
	HK_FORCE_INLINE void	unpack(hkTransformd& t) const	{ hkQuaterniond q; m_orientation.unpack(&q.m_vec); m_translation.unpack(t.getTranslation()); t.getRotation().set(q); }


	hkPackedVector3			m_translation;	///< Compressed translation.
	hkPackedUnitVector<4>	m_orientation;	///< Compressed orientation.
};

#endif //HKMATH_MATH_PACKED_TRANSFORM_H

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
