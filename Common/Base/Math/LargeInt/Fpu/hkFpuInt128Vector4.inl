/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

//
//	Returns this < 0

inline const hkVector4fComparison hkInt128Vector4::lessZero() const
{
	hkVector4ComparisonMask::Mask mask;
	mask = (hkVector4ComparisonMask::Mask)
		(	
		((m_x.lessZero().anyIsSet()) ? hkVector4ComparisonMask::MASK_X : hkVector4ComparisonMask::MASK_NONE) |
		((m_y.lessZero().anyIsSet()) ? hkVector4ComparisonMask::MASK_Y : hkVector4ComparisonMask::MASK_NONE) |
		((m_z.lessZero().anyIsSet()) ? hkVector4ComparisonMask::MASK_Z : hkVector4ComparisonMask::MASK_NONE) |
		((m_w.lessZero().anyIsSet()) ? hkVector4ComparisonMask::MASK_W : hkVector4ComparisonMask::MASK_NONE)
		);
	hkVector4fComparison cmp;
	cmp.set(mask);
	return cmp;
}

//
//	Flips the sign of v

template <> inline void hkInt128Vector4::setFlipSign<3>(hkInt128Vector4Parameter v, hkVector4fComparisonParameter signFlip)
{
	set(v.m_x, v.m_y, v.m_z, m_w);
	if (signFlip.allAreSet<hkVector4ComparisonMask::MASK_X>())	m_x.setNeg(v.m_x);
	if (signFlip.allAreSet<hkVector4ComparisonMask::MASK_Y>())	m_y.setNeg(v.m_y);
	if (signFlip.allAreSet<hkVector4ComparisonMask::MASK_Z>())	m_z.setNeg(v.m_z);
}

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
