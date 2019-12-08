/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

HK_FORCE_INLINE void hkpDeformableFixedConstraintData::setLinearLimit(hkReal maxDistance)
{
	m_atoms.m_lin.setMaxDistance(hkSimdReal::fromFloat(maxDistance));
}

HK_FORCE_INLINE void hkpDeformableFixedConstraintData::setLinearOffset(hkVector4Parameter vOffset)
{
	m_atoms.m_lin.setOffset(vOffset);
}

HK_FORCE_INLINE void hkpDeformableFixedConstraintData::setLinearStrength(const hkSymmetricMatrix3& linearYieldStrength, const hkSymmetricMatrix3& linearUltimateStrength)
{
	m_atoms.m_lin.setYieldStrength(linearYieldStrength);
	m_atoms.m_lin.setUltimateStrength(linearUltimateStrength);
}

HK_FORCE_INLINE void hkpDeformableFixedConstraintData::setAngularLimit(hkReal maxAngle)
{
	const hkReal cosAMax = hkMath::cos(maxAngle);
	m_atoms.m_ang.setCosMaxAngle(hkSimdReal::fromFloat(cosAMax));
}

HK_FORCE_INLINE void hkpDeformableFixedConstraintData::setAngularOffset(hkQuaternionParameter qOffset)
{
	m_atoms.m_ang.setOffset(qOffset);
}

HK_FORCE_INLINE void hkpDeformableFixedConstraintData::setAngularStrength(const hkSymmetricMatrix3& angularYieldStrength, const hkSymmetricMatrix3& angularUltimateStrength)
{
	m_atoms.m_ang.setYieldStrength(angularYieldStrength);
	m_atoms.m_ang.setUltimateStrength(angularUltimateStrength);
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
