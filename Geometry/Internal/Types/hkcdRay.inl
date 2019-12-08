/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */


//
HK_FORCE_INLINE	void hkcdRay::setDirection(hkVector4Parameter direction, hkSimdRealParameter fraction)
{
	m_direction.setXYZ_W(direction, fraction);
	m_invDirection.setReciprocal<HK_ACC_23_BIT,HK_DIV_SET_MAX>(direction);	
}

//
HK_FORCE_INLINE	void hkcdRay::setEndPoints(hkVector4Parameter start, hkVector4Parameter end, hkSimdRealParameter fraction)
{
	hkVector4	direction; direction.setSub(end, start);
	setOriginDirection(start, direction, fraction);
}

//
HK_FORCE_INLINE	void hkcdRay::setOriginDirection(hkVector4Parameter origin, hkVector4Parameter direction, hkSimdRealParameter fraction)
{
	setDirection(direction, fraction);
	m_origin	=	origin;
}

//
//	Computes the ray end-point

HK_FORCE_INLINE void hkcdRay::getEndPoint(hkVector4& vEndPoint) const
{
	vEndPoint.setAddMul(m_origin, m_direction, getFraction());
}

//
//	Returns the direction

inline void hkcdRayBundle::getDirection(hkFourTransposedPoints& directionOut) const
{
	directionOut.setSub(m_end, m_start);
}


/*static*/ HK_FORCE_INLINE void hkcdRayQueryFlags::extractFlag(Enum flags, Enum flag, hkVector4Comparison& out) 
{ 
	out.set((flags & flag) ? hkVector4ComparisonMask::MASK_XYZW : hkVector4ComparisonMask::MASK_NONE ); 
}

	
/*static*/ HK_FORCE_INLINE hkInt32 hkcdRayCastResult::create(hkVector4ComparisonParameter isHit, hkVector4ComparisonParameter isInsideHit)
{
	// Make sure we return exactly zero if isHit is zero.
	int innerBits = isHit.getMask() * isInsideHit.getMask();
	return (isHit.getMask()) | ((innerBits << 4) | (innerBits & 0xf0));
}

/*static*/ HK_FORCE_INLINE hkInt32 hkcdRayCastResult::createHit(hkVector4ComparisonParameter isInsideHit)
{
	return 1 | (isInsideHit.getMask() << 4);
}

/*static*/ HK_FORCE_INLINE hkInt32 hkcdRayCastResult::createInsideHit()
{
	return 0xff;
}

/*static*/ HK_FORCE_INLINE hkInt32 hkcdRayCastResult::createOutsideHit()
{
	return 0xf;
}

/*static*/ HK_FORCE_INLINE hkInt32 hkcdRayCastResult::createMiss()
{
	return 0;
}

/*static*/ HK_FORCE_INLINE hkInt32 hkcdRayCastResult::isHit(hkInt32 result)
{
	return result;
}

/*static*/ HK_FORCE_INLINE hkInt32 hkcdRayCastResult::isInsideHit(hkInt32 result)
{
	return (result & 0xf0) * (result & 0xf);
}

/*static*/ HK_FORCE_INLINE hkInt32 hkcdRayCastResult::isOutsideHit(hkInt32 result)
{
	return !isInsideHit(result);
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
