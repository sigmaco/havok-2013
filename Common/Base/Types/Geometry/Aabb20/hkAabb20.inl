/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */


void hkAabb24_16_24::setEmpty()
{
	m_max.m_u64 = 0;
	m_min.m_u64 = 0x7fffff7fff7fffffLL;
}

void hkAabb24_16_24::set( const hkAabb24_16_24& other)
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED) && !defined(HK_REAL_IS_DOUBLE)
	HK_COMPILE_TIME_ASSERT( hkSizeOf(hkAabb24_16_24) == hkSizeOf(hkVector4) );
	hkVector4 h;
	h.load<4>( (const float*)&other);
	h.store<4>( (float*)this);
#else
	*this = other;
#endif
}



bool hkAabb24_16_24::isValid() const
{
	return true;
}


hkBoolLL hkAabb24_16_24::disjoint_usingUint64(const hkAabb24_16_24& b) const
{
	hkUint64 m0 = m_max.m_u64 - b.m_min.m_u64;
	hkUint64 m1 = b.m_max.m_u64 - m_min.m_u64;
	m0 |= m1;
	m0 &= 0x8000008000800000LL;
#if defined(HK_ARCH_SUPPORTS_INT64)
	return hkBoolLL(m0);
#else
	hkUint32 r = hkUint32(m0) | hkUint32(m0>>32);
	return r;
#endif
}

#if defined(HK_INT_VECTOR_ADD64_AVAILABLE)
hkBool32 hkAabb24_16_24::disjoint_usingSimd2(const hkAabb24_16_24& b) const
{
	hkIntVector ami; ami.load<2>((hkUint32*)&m_min);
	hkIntVector ama; ama.load<2>((hkUint32*)&m_max);
	hkIntVector bmi; bmi.load<2>((hkUint32*)&m_min);
	hkIntVector bma; bma.load<2>((hkUint32*)&m_max);

	hkIntVector m0; m0.setSubU64( ama, bmi );
	hkIntVector m1; m1.setSubU64( bma, ami );
	m0.setOr( m0, m1 );
	static HK_ALIGN16( hkUint64 ) mask[2] = { 0x8000008000800000ULL, 0 };

	m0.setAnd( (const hkIntVector&) mask[0], m0 );
	hkIntVector zero; zero.setZero();
	hkVector4Comparison isZero = m0.compareEqualS32( zero );
	return isZero.getMask();
}


hkBool32 hkAabb24_16_24::disjoint_usingSimd4( const hkAabb24_16_24& b ) const
{
	hkIntVector va; va.load<4>((hkUint32*)&m_min);
	hkIntVector vb; vb.load<4>((hkUint32*)&b.m_min);
	vb.setPermutation<hkVectorPermutation::ZWXY>(vb);

	hkIntVector m; m.setSubU64( va, vb );
	static HK_ALIGN16( hkUint64 ) mask[2] = { 0x8000008000800000ULL,  0x8000008000800000ULL };
	static HK_ALIGN16( hkUint64 ) cmp[2] =  { 0						, 0x8000008000800000ULL };

	m.setAnd( (const hkIntVector&) mask[0], m );
	hkVector4Comparison isZero = m.compareEqualS32( (const hkIntVector&)cmp );
	return isZero.getMask();
}
#endif

hkBoolLL hkAabb24_16_24::disjoint(const hkAabb24_16_24& b) const
{
#if defined(HK_ARCH_SUPPORTS_INT64)
	return disjoint_usingUint64( b );
#elif defined(HK_PLATFORM_WIN32) && defined(HK_INT_VECTOR_ADD64_AVAILABLE)
	return disjoint_usingSimd2( b );
#else
	return disjoint_usingUint64( b );
#endif

}

hkBoolLL hkAabb24_16_24::yzDisjoint( const hkAabb24_16_24& a, const hkAabb24_16_24& b )
{
	return a.disjoint( b );
}

bool hkAabb24_16_24::contains( const hkAabb24_16_24& b ) const
{
	hkUint64 m0 = m_max.m_u64 - b.m_max.m_u64;
	hkUint64 m1 = b.m_min.m_u64 - m_min.m_u64;
	m0 |= m1;
	m0 &= 0x8000008000800000LL;
	return m0 == 0;
}


bool hkAabb24_16_24::isEqual( const hkAabb24_16_24& aabb ) const
{
	hkUint64 a = m_min.m_u64 ^ aabb.m_min.m_u64;
	hkUint64 b = m_max.m_u64 ^ aabb.m_max.m_u64;
	a = a^b;
	return a == 0;
}

bool hkAabb24_16_24::containsDontTouch( const hkAabb24_16_24& b ) const
{
	hkUint64 m0 = m_max.m_u64 - b.m_max.m_u64 - 0x0000010001000001LL;
	hkUint64 m1 = b.m_min.m_u64 - m_min.m_u64 - 0x0000010001000001LL;
	m0 |= m1;
	m0 &= 0x8000008000800000LL;
	return m0 == 0;
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
