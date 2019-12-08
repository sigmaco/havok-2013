/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

//
//	Creates a new hkQTransformd using the rotation quaternion q and translation t.

HK_FORCE_INLINE hkQTransformd::hkQTransformd(hkQuaterniondParameter q, hkVector4dParameter t)
:	m_rotation(q)
,	m_translation(t)
{
}

//
//	Copy constructor

HK_FORCE_INLINE hkQTransformd::hkQTransformd(const hkQTransformd& qt)
:	m_rotation(qt.m_rotation)
,	m_translation(qt.m_translation)
{
}

//
//	Constructor

HK_FORCE_INLINE hkQTransformd::hkQTransformd(class hkFinishLoadedObjectFlag f)
{
}

//
//	Sets the hkQTransformd's values using the rotation quaternion q and translation t.

HK_FORCE_INLINE void hkQTransformd::set(hkQuaterniondParameter q, hkVector4dParameter t)
{
	m_rotation		= q;
	m_translation	= t;
}

//
//	Sets the hkQTransformd's values from a hkTransformd.

HK_FORCE_INLINE void hkQTransformd::set(const hkTransformd& otherTransform)
{
	m_rotation.set(otherTransform.getRotation());
	m_translation = otherTransform.getTranslation();
}

//
//	Sets this hkQTransformd to be the identity transform.

HK_FORCE_INLINE void hkQTransformd::setIdentity()
{
	m_rotation.setIdentity();
	m_translation.setZero();
}

//
//	Sets this hkQTransformd to zero

HK_FORCE_INLINE void hkQTransformd::setZero()
{
	m_rotation.m_vec.setZero();
	m_translation.setZero();
}

//
//	Sets this += qa. The rotations are added as vectors, no attempt is made to re-normalize the quaternion.

HK_FORCE_INLINE void hkQTransformd::add(const hkQTransformd& qa)
{
	m_rotation.m_vec.add(qa.m_rotation.m_vec);
	m_translation.add(qa.m_translation);
}

//
//	Returns a global identity transform.

HK_FORCE_INLINE /*static*/ const hkQTransformd& HK_CALL hkQTransformd::getIdentity()
{
	extern hkDouble64 hkQTransformdIdentity_storage[];
	union { const hkDouble64* r; const hkQTransformd* q; } r2q;
	r2q.r = hkQTransformdIdentity_storage;
	return *r2q.q;
}

//
//	Gets the translation component.

HK_FORCE_INLINE const hkVector4d& hkQTransformd::getTranslation() const
{
	return m_translation;
}

//
//	Sets the translation component.

HK_FORCE_INLINE void hkQTransformd::setTranslation(hkVector4dParameter t)
{
	m_translation = t;
}

//
//	Gets the rotation component.

HK_FORCE_INLINE const hkQuaterniond& hkQTransformd::getRotation() const
{
	return m_rotation;
}

//
//	Sets the rotation component.

HK_FORCE_INLINE void hkQTransformd::setRotation(hkQuaterniondParameter q)
{
	m_rotation = q;
}

//
//	Sets this transform to be the product of the inverse of qt1 by qt2.  (this = qt1^-1 * qt2)

HK_FORCE_INLINE void hkQTransformd::_setMulInverseMul(const hkQTransformd& qt1, const hkQTransformd& qt2)
{
	hkQuaterniond invQ1;
	invQ1.setInverse(qt1.m_rotation);
	m_rotation.setMul(invQ1, qt2.m_rotation);

	hkVector4d tempV;
	tempV.setSub(qt2.m_translation, qt1.m_translation);
	m_translation._setRotatedDir(invQ1, tempV);
}

//
//	Sets this transform to be the product of qt1 and the inverse of qt2. (this = qt1 * qt2^-1)

HK_FORCE_INLINE void hkQTransformd::_setMulMulInverse(const hkQTransformd &qt1, const hkQTransformd &qt2)
{
	hkQuaterniond invQ2;
	invQ2.setInverse(qt2.m_rotation);
	m_rotation.setMul(qt1.m_rotation, invQ2);

	hkVector4d tempV;
	tempV._setRotatedDir(m_rotation, qt2.m_translation);
	m_translation.setSub(qt1.m_translation, tempV);
}

//
//	Sets this transform to be the product of qt1 and qt2.  (this = qt1 * qt2)

HK_FORCE_INLINE void hkQTransformd::_setMul(const hkQTransformd& qt1, const hkQTransformd& qt2)
{
	hkVector4d tmp;
	tmp._setRotatedDir(qt1.m_rotation, qt2.m_translation);
	m_translation.setAdd(tmp, qt1.m_translation);

	m_rotation.setMul(qt1.m_rotation, qt2.m_rotation);
}

//
//	Sets this transform to be the inverse of the given transform qt.

HK_FORCE_INLINE void hkQTransformd::_setInverse(const hkQTransformd& qt)
{
	// We are not "reference-safe" because quaternion inversion is not reference-safe
	HK_ASSERT2(0x2a561056, (&qt != this) , "Using unsafe references in math operation");

	m_rotation.setInverse(qt.m_rotation);
	m_translation._setRotatedDir(m_rotation, qt.m_translation);
	m_translation.setNeg<4>(m_translation);
}

inline bool hkQTransformd::_isApproximatelyEqual( const hkQTransformd& other, hkSimdDouble64Parameter sEps ) const
{
	// Compare translations
	if ( !m_translation.allEqual<3>(other.m_translation, sEps) ) 
	{
		return false;
	}

	// Quaternions are slightly trickier to compare due to the duplicity (-axis,angle) <=> (axis,-angle)
	hkQuaterniond closestOther;
	closestOther.setClosest(other.m_rotation, m_rotation);
	return m_rotation.m_vec.allEqual<4>(closestOther.m_vec, sEps);
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
