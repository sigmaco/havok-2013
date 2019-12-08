/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */


//
//	Sets resultOut to be the product of t1 by the inverse of t2. (resultOut = t1 * Inverse(t2))

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkTransformUtilImpl<FT>::_computeMulInverse(const typename hkRealTypes<FT>::Transform& t1, const typename hkRealTypes<FT>::Transform& t2, typename hkRealTypes<FT>::Transform& resultOut)
{
	typename hkRealTypes<FT>::Rotation rot;		hkMatrix3UtilImpl<FT>::_computeMulInverse(t1.getRotation(), t2.getRotation(), rot);
	typename hkRealTypes<FT>::Vector pos;		pos._setRotatedDir(rot, t2.getTranslation());
	pos.setSub(t1.getTranslation(), pos);
	resultOut.set(rot, pos);
}

//
//	Converts a (hkQuaternion, hkVector) pair to a hkTransform

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkTransformUtilImpl<FT>::_convert(typename hkRealTypes<FT>::QuaternionParameter fromRot, typename hkRealTypes<FT>::VectorParameter fromPos, typename hkRealTypes<FT>::Transform& to)
{
	typename hkRealTypes<FT>::Rotation rot;
	hkVector4UtilImpl<FT>::convertQuaternionToRotation(fromRot, rot);
	to.set(rot, fromPos);
}

//
//	Converts a hkQTransform to a hkTransform

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkTransformUtilImpl<FT>::_convert(const typename hkRealTypes<FT>::QTransform& from, typename hkRealTypes<FT>::Transform& to)
{
	_convert(from.m_rotation, from.m_translation, to);
}

//
//	Sets this transform to be the product of t1 and t2. (this = t1 * t2)

template <typename FT>
HK_FORCE_INLINE void hkTransformUtilImpl<FT>::_mulTransformTransform( const typename hkRealTypes<FT>::Transform& aTb, const typename hkRealTypes<FT>::Transform& bTc, typename hkRealTypes<FT>::Transform* HK_RESTRICT tOut )
{
	HK_ASSERT(0x4763da71,  tOut != &aTb );

	hkVector4UtilImpl<FT>::rotatePoints( aTb.getRotation(), &bTc.getRotation().template getColumn<0>(), 4, &tOut->getRotation().template getColumn<0>() );
	tOut->getTranslation().add( aTb.getTranslation());
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
