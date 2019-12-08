/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

HK_FORCE_INLINE /*static*/ const hkVector4dComparison HK_CALL hkVector4dComparison::convert(const hkVector4dMask& x)
{
	hkVector4dComparison c;
	c.m_mask = x;
	return c;
}

HK_FORCE_INLINE void hkVector4dComparison::setAnd( hkVector4dComparisonParameter a, hkVector4dComparisonParameter b )
{ 
	m_mask = a.m_mask & b.m_mask; 
}

HK_FORCE_INLINE void hkVector4dComparison::setAndNot( hkVector4dComparisonParameter a, hkVector4dComparisonParameter b )
{
	m_mask = a.m_mask & (~b.m_mask);
}

HK_FORCE_INLINE void hkVector4dComparison::setXor( hkVector4dComparisonParameter a, hkVector4dComparisonParameter b )
{
	m_mask = a.m_mask ^ b.m_mask;
}

HK_FORCE_INLINE void hkVector4dComparison::setNot( hkVector4dComparisonParameter a )
{ 
	m_mask = (~a.m_mask) & MASK_XYZW;
}

HK_FORCE_INLINE void hkVector4dComparison::setOr( hkVector4dComparisonParameter a, hkVector4dComparisonParameter b ) 
{ 
	m_mask = a.m_mask | b.m_mask;
}

HK_FORCE_INLINE void hkVector4dComparison::setSelect( hkVector4dComparisonParameter comp, hkVector4dComparisonParameter trueValue, hkVector4dComparisonParameter falseValue ) 
{
	m_mask = (comp.m_mask & trueValue.m_mask) | (~comp.m_mask & falseValue.m_mask);
}

template<hkVector4ComparisonMask::Mask M> 
HK_FORCE_INLINE void hkVector4dComparison::setSelect( hkVector4dComparisonParameter trueValue, hkVector4dComparisonParameter falseValue )
{
	HK_VECTORfCOMPARISON_MASK_CHECK;
	m_mask = (M & trueValue.m_mask) | (~M & falseValue.m_mask);
}

HK_FORCE_INLINE void hkVector4dComparison::set( Mask m ) 
{ 
	HK_MATH_ASSERT(0x610ba416, (m&0xf)==m, "illegal mask value handed in");
	m_mask = m;
}

template <hkVector4ComparisonMask::Mask M>
HK_FORCE_INLINE void hkVector4dComparison::set()
{ 
	HK_VECTORdCOMPARISON_MASK_CHECK;
	m_mask = M;
}

HK_FORCE_INLINE hkBool32 hkVector4dComparison::allAreSet( Mask m ) const 
{ 
	HK_MATH_ASSERT(0x217e76eb, (m&0xf)==m, "illegal mask value handed in");
	return (m_mask & m) == m;
}

template <hkVector4ComparisonMask::Mask M>
HK_FORCE_INLINE hkBool32 hkVector4dComparison::allAreSet() const 
{ 
	HK_VECTORdCOMPARISON_MASK_CHECK;
	if (M == MASK_NONE)
	{
		return true;
	}
	else if (M == MASK_XYZW)
	{
		return m_mask == MASK_XYZW;
	}
	else
	{
		return (m_mask & M) == M;
	}
}

HK_FORCE_INLINE hkBool32 hkVector4dComparison::anyIsSet( Mask m ) const 
{ 
	HK_MATH_ASSERT(0x21e05e49, (m&0xf)==m, "illegal mask value handed in");
	return m_mask & m;
}

template <hkVector4ComparisonMask::Mask M>
HK_FORCE_INLINE hkBool32 hkVector4dComparison::anyIsSet() const 
{ 
	HK_VECTORdCOMPARISON_MASK_CHECK;
	if (M == MASK_NONE)
	{
		return false;
	}
	else if (M == MASK_XYZW)
	{
		return m_mask;
	}
	else
	{
		return m_mask & M;
	}
}

HK_FORCE_INLINE hkBool32 hkVector4dComparison::allAreSet() const 
{ 
	return m_mask == MASK_XYZW;
}

HK_FORCE_INLINE hkBool32 hkVector4dComparison::anyIsSet() const 
{ 
	return m_mask;
}

HK_FORCE_INLINE hkVector4ComparisonMask::Mask hkVector4dComparison::getMask() const 
{ 
	return (hkVector4ComparisonMask::Mask)(m_mask);
}

HK_FORCE_INLINE hkVector4ComparisonMask::Mask hkVector4dComparison::getMask(Mask m) const 
{ 
	HK_MATH_ASSERT(0x6b7c1f6a, (m&0xf)==m, "illegal mask value handed in");
	return (hkVector4ComparisonMask::Mask)(m_mask & m);
}

template <hkVector4ComparisonMask::Mask M>
HK_FORCE_INLINE hkVector4ComparisonMask::Mask hkVector4dComparison::getMask() const 
{ 
	HK_VECTORdCOMPARISON_MASK_CHECK;
	return (hkVector4ComparisonMask::Mask)(m_mask & M);
}

HK_FORCE_INLINE /*static*/ hkUint32 HK_CALL hkVector4dComparison::getCombinedMask(hkVector4dComparisonParameter ca, hkVector4dComparisonParameter cb, hkVector4dComparisonParameter cc )
{
	return ca.m_mask | (cb.m_mask<<4 ) | (cc.m_mask<<8);
}

//
//	Horizontal or

template <>
HK_FORCE_INLINE const hkVector4dComparison hkVector4dComparison::horizontalOr<1>() const
{
	return hkVector4dComparison::convert((hkVector4dMask)((m_mask & MASK_X) ? MASK_XYZW : MASK_NONE));
}

template <>
HK_FORCE_INLINE const hkVector4dComparison hkVector4dComparison::horizontalOr<2>() const
{
	return hkVector4dComparison::convert((hkVector4dMask)((m_mask & MASK_XY) ? MASK_XYZW : MASK_NONE));
}

template <>
HK_FORCE_INLINE const hkVector4dComparison hkVector4dComparison::horizontalOr<3>() const
{
	return hkVector4dComparison::convert((hkVector4dMask)((m_mask & MASK_XYZ) ? MASK_XYZW : MASK_NONE));
}

template <>
HK_FORCE_INLINE const hkVector4dComparison hkVector4dComparison::horizontalOr<4>() const
{
	return hkVector4dComparison::convert((hkVector4dMask)(m_mask ? MASK_XYZW : MASK_NONE));
}

template <int N>
HK_FORCE_INLINE const hkVector4dComparison hkVector4dComparison::horizontalOr() const
{
	HK_VECTORdCOMPARISON_SUBINDEX_CHECK;
	hkVector4dComparison cmp;
	cmp.set<hkVector4ComparisonMask::MASK_NONE>();
	return cmp;
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
