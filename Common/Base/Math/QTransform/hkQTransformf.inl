/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

//
//	Creates a new hkQTransformf using the rotation quaternion q and translation t.

HK_FORCE_INLINE hkQTransformf::hkQTransformf(hkQuaternionfParameter q, hkVector4fParameter t)
:	m_rotation(q)
,	m_translation(t)
{
}

//
//	Copy constructor

HK_FORCE_INLINE hkQTransformf::hkQTransformf(const hkQTransformf& qt)
:	m_rotation(qt.m_rotation)
,	m_translation(qt.m_translation)
{
}

//
//	Constructor

HK_FORCE_INLINE hkQTransformf::hkQTransformf(class hkFinishLoadedObjectFlag f)
{
}

//
//	Sets the hkQTransformf's values using the rotation quaternion q and translation t.

HK_FORCE_INLINE void hkQTransformf::set(hkQuaternionfParameter q, hkVector4fParameter t)
{
	m_rotation		= q;
	m_translation	= t;
}

//
//	Sets the hkQTransformf's values from a hkTransformf.

HK_FORCE_INLINE void hkQTransformf::set(const hkTransformf& otherTransform)
{
	m_rotation.set(otherTransform.getRotation());
	m_translation = otherTransform.getTranslation();
}

//
//	Sets this hkQTransformf to be the identity transform.

HK_FORCE_INLINE void hkQTransformf::setIdentity()
{
	m_rotation.setIdentity();
	m_translation.setZero();
}

//
//	Sets this hkQTransformf to zero

HK_FORCE_INLINE void hkQTransformf::setZero()
{
	m_rotation.m_vec.setZero();
	m_translation.setZero();
}

//
//	Sets this += qa. The rotations are added as vectors, no attempt is made to re-normalize the quaternion.

HK_FORCE_INLINE void hkQTransformf::add(const hkQTransformf& qa)
{
	m_rotation.m_vec.add(qa.m_rotation.m_vec);
	m_translation.add(qa.m_translation);
}

//
//	Returns a global identity transform.

HK_FORCE_INLINE /*static*/ const hkQTransformf& HK_CALL hkQTransformf::getIdentity()
{
	extern hkFloat32 hkQTransformfIdentity_storage[];
	union { const hkFloat32* r; const hkQTransformf* q; } r2q;
	r2q.r = hkQTransformfIdentity_storage;
	return *r2q.q;
}

//
//	Gets the translation component.

HK_FORCE_INLINE const hkVector4f& hkQTransformf::getTranslation() const
{
	return m_translation;
}

//
//	Sets the translation component.

HK_FORCE_INLINE void hkQTransformf::setTranslation(hkVector4fParameter t)
{
	m_translation = t;
}

//
//	Gets the rotation component.

HK_FORCE_INLINE const hkQuaternionf& hkQTransformf::getRotation() const
{
	return m_rotation;
}

//
//	Sets the rotation component.

HK_FORCE_INLINE void hkQTransformf::setRotation(hkQuaternionfParameter q)
{
	m_rotation = q;
}

//
//	Sets this transform to be the product of the inverse of qt1 by qt2.  (this = qt1^-1 * qt2)

HK_FORCE_INLINE void hkQTransformf::_setMulInverseMul(const hkQTransformf& qt1, const hkQTransformf& qt2)
{
	hkQuaternionf invQ1;
	invQ1.setInverse(qt1.m_rotation);
	m_rotation.setMul(invQ1, qt2.m_rotation);

	hkVector4f tempV;
	tempV.setSub(qt2.m_translation, qt1.m_translation);
	m_translation._setRotatedDir(invQ1, tempV);
}

//
//	Sets this transform to be the product of qt1 and the inverse of qt2. (this = qt1 * qt2^-1)

HK_FORCE_INLINE void hkQTransformf::_setMulMulInverse(const hkQTransformf &qt1, const hkQTransformf &qt2)
{
	hkQuaternionf invQ2;
	invQ2.setInverse(qt2.m_rotation);
	m_rotation.setMul(qt1.m_rotation, invQ2);

	hkVector4f tempV;
	tempV._setRotatedDir(m_rotation, qt2.m_translation);
	m_translation.setSub(qt1.m_translation, tempV);
}

//
//	Sets this transform to be the product of qt1 and qt2.  (this = qt1 * qt2)

HK_FORCE_INLINE void hkQTransformf::_setMul(const hkQTransformf& qt1, const hkQTransformf& qt2)
{
	hkVector4f tmp;
	tmp._setRotatedDir(qt1.m_rotation, qt2.m_translation);
	m_translation.setAdd(tmp, qt1.m_translation);

	m_rotation.setMul(qt1.m_rotation, qt2.m_rotation);
}

//
//	Sets this transform to be the inverse of the given transform qt.

HK_FORCE_INLINE void hkQTransformf::_setInverse(const hkQTransformf& qt)
{
	// We are not "reference-safe" because quaternion inversion is not reference-safe
	HK_ASSERT2(0x2a561056, (&qt != this) , "Using unsafe references in math operation");

	m_rotation.setInverse(qt.m_rotation);
	m_translation._setRotatedDir(m_rotation, qt.m_translation);
	m_translation.setNeg<4>(m_translation);
}

inline bool hkQTransformf::_isApproximatelyEqual( const hkQTransformf& other, hkSimdFloat32Parameter sEps ) const
{
	// Quaternions are slightly trickier to compare due to the duplicity (-axis,angle) <=> (axis,-angle)
	hkQuaternionf closestOther;
	closestOther.setClosest(other.m_rotation, m_rotation);
	return m_rotation.m_vec.allEqual<4>(closestOther.m_vec, sEps) && m_translation.allEqual<3>(other.m_translation, sEps);
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
