/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_DISABLE_MATH_CONSTRUCTORS
inline hkAabb::hkAabb(const hkVector4& min, const hkVector4& max)
	: m_min(min), m_max(max)
{
}
#endif

hkBool32 hkAabb::overlaps( const hkAabb& other ) const
{
	HK_ASSERT2(0x3f5578fc,  isValid() || isEmpty(), "Invalid AABB in hkAabb::overlaps." );
	HK_ASSERT2(0x76dd800a,  other.isValid() || other.isEmpty(), "Invalid AABB in hkAabb::overlaps.");
	#if HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED
	hkVector4Comparison mincomp = m_min.lessEqual(other.m_max);
	hkVector4Comparison maxcomp = other.m_min.lessEqual(m_max);
	hkVector4Comparison both; both.setAnd( mincomp, maxcomp );
	return both.allAreSet<hkVector4ComparisonMask::MASK_XYZ>();
	#else
	if(m_min(0) > other.m_max(0)) return 0;
	if(m_min(1) > other.m_max(1)) return 0;
	if(m_min(2) > other.m_max(2)) return 0;
	if(m_max(0) < other.m_min(0)) return 0;
	if(m_max(1) < other.m_min(1)) return 0;
	if(m_max(2) < other.m_min(2)) return 0;
	return 1;
	#endif
}


hkBool32 hkAabb::overlapsUpdateSmallestNonExtraHitAabb( const hkAabb& other, hkAabb& smallestNonHitAabbInOut ) const
{
	HK_ASSERT2(0x3f5578fc,  isValid(), "Invalid AABB in hkAabb::overlaps." );
	//HK_ASSERT2(0x76dd800a,  other.isValid(), "Invalid AABB in hkAabb::overlaps.");
	hkVector4Comparison mincomp = m_min.less(other.m_max);
	hkVector4Comparison maxcomp = other.m_min.less(m_max);

	hkVector4 newMax; newMax.setMin( smallestNonHitAabbInOut.m_max, other.m_min );
	hkVector4 newMin; newMin.setMax( smallestNonHitAabbInOut.m_min, other.m_max );

	hkVector4Comparison both; both.setAnd( mincomp, maxcomp );

	smallestNonHitAabbInOut.m_min.setSelect( mincomp, smallestNonHitAabbInOut.m_min, newMin );
	smallestNonHitAabbInOut.m_max.setSelect( maxcomp, smallestNonHitAabbInOut.m_max, newMax );

	return both.allAreSet<hkVector4ComparisonMask::MASK_XYZ>();
}


hkBool32 hkAabb::contains(const hkAabb& other) const
{
	hkVector4Comparison mincomp = m_min.lessEqual(other.m_min);
	hkVector4Comparison maxcomp = other.m_max.lessEqual(m_max);
	hkVector4Comparison both; both.setAnd( mincomp, maxcomp );
	return both.allAreSet<hkVector4ComparisonMask::MASK_XYZ>();
}

hkBool32 hkAabb::notContains(const hkAabb& other) const
{
	hkVector4Comparison mincomp = other.m_min.less(m_min);
	hkVector4Comparison maxcomp = other.m_max.greater(m_max);
	hkVector4Comparison both; both.setOr( mincomp, maxcomp );
	return both.anyIsSet<hkVector4ComparisonMask::MASK_XYZ>();
}

hkBool32 hkAabb::containsPoint(const hkVector4& other) const
{
	hkVector4Comparison mincomp = m_min.lessEqual(other);
	hkVector4Comparison maxcomp = other.lessEqual(m_max);
	hkVector4Comparison both; both.setAnd( mincomp, maxcomp );
	return both.allAreSet<hkVector4ComparisonMask::MASK_XYZ>();
}

bool hkAabb::isEmpty() const
{
	hkVector4Comparison comp = m_min.greaterEqual(m_max);
	return comp.anyIsSet<hkVector4ComparisonMask::MASK_XYZ>();
}

void hkAabb::includePoint (const hkVector4& point)
{
	m_min.setMin(m_min, point);
	m_max.setMax(m_max, point);
}

void hkAabb::includeAabb (const hkAabb& aabb)
{
	m_min.setMin(m_min, aabb.m_min);
	m_max.setMax(m_max, aabb.m_max);
}

void hkAabb::setFull()
{
	m_max = hkVector4::getConstant<HK_QUADREAL_MAX>();
	m_min.setNeg<4>( m_max );
}

void hkAabb::setEmpty()
{
	m_min = hkVector4::getConstant<HK_QUADREAL_MAX>();
	m_max.setNeg<4>( m_min );
}

//
//	Sets the AABB to empty if it is invalid

HK_FORCE_INLINE void hkAabb::setEmptyIfInvalid()
{
	const hkVector4Comparison cmpValid	= m_min.greaterEqual(m_max);
	const hkVector4Comparison cmp		= cmpValid.horizontalOr<3>();

	hkVector4 vMin = hkVector4::getConstant<HK_QUADREAL_MAX>();	
	hkVector4 vMax;	vMax.setNeg<4>(vMin);

	m_min.setSelect(cmp, vMin, m_min);
	m_max.setSelect(cmp, vMax, m_max);
}

void hkAabb::getCenter( hkVector4& c ) const
{
	hkVector4 g; g.setAdd( m_min, m_max );
	c.setMul( g, hkSimdReal::getConstant<HK_QUADREAL_INV_2>() );
}

void hkAabb::getCenter2( hkVector4& c ) const
{
	c.setAdd( m_min, m_max );
}

void hkAabb::getHalfExtents( hkVector4& he ) const
{
	hkVector4 sub; sub.setSub( m_max, m_min );
	he.setMul( sub, hkSimdReal::getConstant<HK_QUADREAL_INV_2>() );
}

void hkAabb::getExtents( hkVector4& e ) const
{
	e.setSub( m_max, m_min );
}

void hkAabb::getVertex(int index, hkVector4& vertex) const
{
	HK_ASSERT2(0xF7BD00CA, index >= 0 && index <= 7, "Index out-of-range");
	hkVector4Comparison	comp; comp.set((hkVector4Comparison::Mask)index);
	vertex.setSelect(comp, m_max, m_min);
}

void hkAabb::expandBy( hkSimdRealParameter exp )
{
	hkVector4 expansion; expansion.setAll(exp);
	m_max.add(expansion);
	m_min.sub(expansion);
}

void hkAabb::expandInDirection( hkVector4Parameter exp )
{
	hkVector4 newMax; newMax.setAdd(m_max, exp);
	hkVector4 newMin; newMin.setAdd(m_min, exp);
	m_max.setMax(m_max, newMax);
	m_min.setMin(m_min, newMin);
}

void hkAabb::scaleBy( hkSimdRealParameter scale )
{
	hkVector4	e; e.setSub(m_min, m_max);
	e.mul(- hkSimdReal::getConstant<HK_QUADREAL_INV_2>() * (scale - hkSimdReal::getConstant<HK_QUADREAL_1>()));
	m_min.sub(e);
	m_max.add(e);
}

void hkAabb::setExpandBy( const hkAabb& aabb, hkSimdRealParameter exp )
{
	hkVector4 expansion; expansion.setAll(exp);
	m_max.setAdd( aabb.m_max, expansion );
	m_min.setSub( aabb.m_min, expansion );
}


hkBool32 hkAabb::equals(const hkAabb& aabb) const
{
	hkVector4Comparison mi = aabb.m_min.equal(m_min);
	hkVector4Comparison ma = aabb.m_max.equal(m_max);
	hkVector4Comparison co; co.setAnd( mi, ma );
	return co.allAreSet<hkVector4ComparisonMask::MASK_XYZ>();
}

void hkAabb::setIntersection(const hkAabb& aabb0, const hkAabb& aabb1)
{
	m_min.setMax(aabb0.m_min, aabb1.m_min);
	m_max.setMin(aabb0.m_max, aabb1.m_max);
}

void hkAabb::setUnion(const hkAabb& aabb0, const hkAabb& aabb1)
{
	m_min.setMin(aabb0.m_min, aabb1.m_min);
	m_max.setMax(aabb0.m_max, aabb1.m_max);
}

void hkAabb::setMinkowskiSum(const hkAabb& aabb0, const hkAabb& aabb1)
{
	m_min.setSub(aabb1.m_min, aabb0.m_max);
	m_max.setSub(aabb1.m_max, aabb0.m_min);
}

void hkAabb::projectPoint(const hkVector4& point, hkVector4& projection) const
{
	projection.setMax(point, m_min);
	projection.setMin(projection, m_max);
}

inline void hkAabbUint32::setInvalid()
{
	const int ma = 0x7fffffff;

	// SNC warning workaround
	hkUint32* minP = m_min;
	hkUint32* maxP = m_max;

	minP[0] = ma;
	minP[1] = ma;
	minP[2] = ma;
	minP[3] = 0;
	maxP[0] = 0;
	maxP[1] = 0;
	maxP[2] = 0;
	maxP[3] = 0;
}

inline void hkAabbUint32::setInvalidY()
{
	const int ma = 0x7fff0000;
	hkUint32* minP = m_min;
	hkUint32* maxP = m_max;

	minP[1] = ma;
	minP[2] = ma;
	minP[3] = 0;
	maxP[1] = 0;
	maxP[2] = 0;
}

void hkAabbUint32::operator=( const hkAabbUint32& other )
{
	hkMemUtil::memCpyOneAligned<sizeof(hkAabbUint32),16>( this, &other );
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
