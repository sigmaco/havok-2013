/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */


template<>
HK_FORCE_INLINE void hkAabb16::setKey(hkUint16 key)
{
	m_key = key;
}

HK_FORCE_INLINE void hkAabb16::getKey(hkUint16& key) const
{
	key = m_key;
}

template<>
HK_FORCE_INLINE void hkAabb16::setKey(hkUint32 key)
{
	m_key = hkUint16(key & 0xffff);
	m_key1 = hkUint16(key >> 16);
}

HK_FORCE_INLINE void hkAabb16::getKey(hkUint32& key) const
{
	key = (m_key1<<16) | m_key;
}

void hkAabb16::setEmpty()
{
	m_min[0] = m_min[1] = m_min[2] = 0xffff; m_max[0] = m_max[1] = m_max[2] = 0; m_key = m_key1 = 0;
}

void hkAabb16::set( const hkAabb16& other)
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED) && !defined(HK_REAL_IS_DOUBLE)
	HK_COMPILE_TIME_ASSERT( hkSizeOf(hkAabb16) == hkSizeOf(hkVector4) );
	hkVector4 h;
	h.load<4>( (const float*)&other);
	h.store<4>( (float*)this);
#else
	*this = other;
#endif
}


bool hkAabb16::isEmpty() const
{
	hkUint16 val0 = (m_min[0]^0xfff) | m_max[0];
	hkUint16 val1 = (m_min[1]^0xfff) | m_max[1];
	hkUint16 val2 = (m_min[2]^0xfff) | m_max[2];
	return 0 == (val0|val1|val2);
}

void hkAabb16::setEmptyKeyUnchanged()
{
	m_min[0] = m_min[1] = m_min[2] = 0xffff; m_max[0] = m_max[1] = m_max[2] = 0;
}


bool hkAabb16::isValid() const
{
	return (m_max[0] > m_min[0])&&(m_max[1] > m_min[1])&&(m_max[2] > m_min[2]);
}

void hkAabb16::getExtent(hkUint16 extent[3]) const
{
	extent[0] = m_max[0] - m_min[0];
	extent[1] = m_max[1] - m_min[1];
	extent[2] = m_max[2] - m_min[2];
}

hkUint16 hkAabb16::getMajorExtent() const
{
	hkUint16 extent[3];
	getExtent( extent );

	int majorAxis = 0;
	majorAxis = ( extent[majorAxis] < extent[1] )? 1 : majorAxis;
	majorAxis = ( extent[majorAxis] < extent[2] )? 2 : majorAxis;

	return extent[ majorAxis ];
}

void hkAabb16::getCenter(hkUint16 c[3]) const
{
	c[0] = (m_max[0]>>1) + (m_min[0]>>1);
	c[1] = (m_max[1]>>1) + (m_min[1]>>1);
	c[2] = (m_max[2]>>1) + (m_min[2]>>1);
}

void hkAabb16::getCenter2(hkUint32 c[3]) const
{
	c[0] = m_max[0] + m_min[0];
	c[1] = m_max[1] + m_min[1];
	c[2] = m_max[2] + m_min[2];
}

void hkAabb16::getCenter2(hkVector4& c) const
{
	c.set(	hkReal(m_min[0] + (int)m_max[0]),
			hkReal(m_min[1] + (int)m_max[1]),
			hkReal(m_min[2] + (int)m_max[2]), 0.0f);
}

void hkAabb16::getExtents(hkVector4& c) const
{
	c.set(	hkReal(m_max[0] + m_min[0]),
			hkReal(m_max[1] + m_min[1]),
			hkReal(m_max[2] + m_min[2]), 0.0f);
}

hkBool32 hkAabb16::disjoint(const hkAabb16& testAabb) const
{
	union PointerUnion { const hkUint16* s; const hkUint32* i; };

	int z0 = int(m_max[2]) - int(testAabb.m_min[2]);
	int z1 = int(testAabb.m_max[2]) - int(m_min[2]);

	PointerUnion pmin; pmin.s = &m_min[0];
	PointerUnion pmax; pmax.s = &m_max[0];
	hkUint32 minAxy = *pmin.i;
	hkUint32 maxAxy = *pmax.i;

	PointerUnion pBmin; pBmin.s = &testAabb.m_min[0];
	PointerUnion pBmax; pBmax.s = &testAabb.m_max[0];
	hkUint32 minBxy = *pBmin.i;
	hkUint32 maxBxy = *pBmax.i;

	maxAxy -= minBxy;
	maxBxy -= minAxy;
	z0 |= z1;
	maxAxy |= maxBxy;
	maxAxy |= z0;
	return maxAxy & 0x80008000;

	// old overlap test
// 	int y0 = int(m_max[1]) - int(testAabb.m_min[1]);
// 	int z0 = int(m_max[2]) - int(testAabb.m_min[2]);
// 
// 	int y1 = int(testAabb.m_max[1]) - int(m_min[1]);
// 	int z1 = int(testAabb.m_max[2]) - int(m_min[2]);
// 
// 	x0 |= y0;
// 	x1 |= y1;
// 	x0 |= z0;
// 	x1 |= z1;
// 
// 	x0 |= x1;
// 
// 	hkBool32 ovl = (~x0) & 0x80000000;
// 
// 	return ovl;
}

hkBool32 hkAabb16::overlaps(const hkUint16 p[3]) const
{
	hkUint16 x0 = m_max[0] - p[0];
	hkUint16 y0 = m_max[1] - p[1];
	hkUint16 z0 = m_max[2] - p[2];

	hkUint16 x1 = p[0] - m_min[0];
	hkUint16 y1 = p[1] - m_min[1];
	hkUint16 z1 = p[2] - m_min[2];

	x0 |= y0;
	x1 |= y1;
	x0 |= z0;
	x1 |= z1;

	x0 |= x1;

	hkBool32 ovl = (~x0) & 0x8000;

	return ovl;
}

hkBool32 hkAabb16::overlaps(const hkAabb16& other) const
{
	hkUint16 x0 = m_max[0] - other.m_min[0];
	hkUint16 y0 = m_max[1] - other.m_min[1];
	hkUint16 z0 = m_max[2] - other.m_min[2];

	hkUint16 x1 = other.m_max[0] - m_min[0];
	hkUint16 y1 = other.m_max[1] - m_min[1];
	hkUint16 z1 = other.m_max[2] - m_min[2];

	x0 |= y0;
	x1 |= y1;
	x0 |= z0;
	x1 |= z1;

	x0 |= x1;

	hkBool32 ovl = (~x0) & 0x8000;

	return ovl;
}

void hkAabb16::includePoint( hkUint16 c[3] )
{
	m_max[0] = hkMath::max2( m_max[0], c[0] );
	m_max[1] = hkMath::max2( m_max[1], c[1] );
	m_max[2] = hkMath::max2( m_max[2], c[2] );

	m_min[0] = hkMath::min2( m_min[0], c[0] );
	m_min[1] = hkMath::min2( m_min[1], c[1] );
	m_min[2] = hkMath::min2( m_min[2], c[2] );
}

void hkAabb16::includeAabb( const hkAabb16& in )
{
	m_max[0] = hkMath::max2( m_max[0], in.m_max[0] );
	m_max[1] = hkMath::max2( m_max[1], in.m_max[1] );
	m_max[2] = hkMath::max2( m_max[2], in.m_max[2] );

	m_min[0] = hkMath::min2( m_min[0], in.m_min[0] );
	m_min[1] = hkMath::min2( m_min[1], in.m_min[1] );
	m_min[2] = hkMath::min2( m_min[2], in.m_min[2] );
}

hkBool32 hkAabb16::contains( const hkAabb16& testAabb ) const
{
	hkUint16 x0 = m_max[0] - testAabb.m_max[0];
	hkUint16 y0 = m_max[1] - testAabb.m_max[1];
	hkUint16 z0 = m_max[2] - testAabb.m_max[2];

	hkUint16 x1 = testAabb.m_min[0] - m_min[0];
	hkUint16 y1 = testAabb.m_min[1] - m_min[1];
	hkUint16 z1 = testAabb.m_min[2] - m_min[2];

	x0 |= y0;
	x1 |= y1;
	x0 |= z0;
	x1 |= z1;

	x0 |= x1;

	hkBool32 ovl = (~x0) & 0x8000;

	return ovl;
}

void hkAabb16::setUnion( const hkAabb16& aabb0, const hkAabb16& aabb1 )
{
	set(aabb0);
	includeAabb(aabb1);
}

bool hkAabb16::isEqual( const hkAabb16& testAabb ) const
{
	hkUint16 x0 = m_max[0] - testAabb.m_max[0];
	hkUint16 y0 = m_max[1] - testAabb.m_max[1];
	hkUint16 z0 = m_max[2] - testAabb.m_max[2];

	hkUint16 x1 = testAabb.m_min[0] - m_min[0];
	hkUint16 y1 = testAabb.m_min[1] - m_min[1];
	hkUint16 z1 = testAabb.m_min[2] - m_min[2];

	x0 |= y0;
	x1 |= y1;
	x0 |= z0;
	x1 |= z1;

	x0 |= x1;

	return x0 == 0;
}

hkBool32 hkAabb16::containsDontTouch( const hkAabb16& testAabb ) const
{
	int x0 = (m_max[0] - testAabb.m_max[0])-1;
	int y0 = (m_max[1] - testAabb.m_max[1])-1;
	int z0 = (m_max[2] - testAabb.m_max[2])-1;

	int x1 = (testAabb.m_min[0] - m_min[0])-1;
	int y1 = (testAabb.m_min[1] - m_min[1])-1;
	int z1 = (testAabb.m_min[2] - m_min[2])-1;

	x0 |= y0;
	x1 |= y1;
	x0 |= z0;
	x1 |= z1;

	x0 |= x1;

	hkBool32 ovl = (~x0) & 0x8000;

	return ovl;
}



hkUint32 hkAabb16::yzDisjoint( const hkAabb16& a, const hkAabb16& b )
{
	union PointerUnion { const hkUint16* s; const hkUint32* i; };

	PointerUnion pamin; pamin.s = &a.m_min[1];
	PointerUnion pamax; pamax.s = &a.m_max[1];
	hkUint32 minA = *pamin.i;
	hkUint32 maxA = *pamax.i;

	PointerUnion pbmin; pbmin.s = &b.m_min[1];
	PointerUnion pbmax; pbmax.s = &b.m_max[1];
	hkUint32 minB = *pbmin.i;
	hkUint32 maxB = *pbmax.i;

	maxA -= minB;
	maxB -= minA;
	maxA |= maxB;
	return maxA & 0x80008000;
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
