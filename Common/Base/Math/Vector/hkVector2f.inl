/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
HK_FORCE_INLINE hkFloat32 hkVector2f::signedDistanceToLineTimesLength( const hkVector2f& p0, const hkVector2f& p1 ) const
{
	return ((p1.x - p0.x)*(y - p0.y) - (x - p0.x)*(p1.y - p0.y));
}

HK_FORCE_INLINE hkBool32 hkVector2f::rightOfLine( const hkVector2f& p0, const hkVector2f& p1 ) const
{
	return signedDistanceToLineTimesLength(p0,p1) < 0;
}

HK_FORCE_INLINE hkBool32 hkVector2f::leftOfLine( const hkVector2f& p0, const hkVector2f& p1 ) const
{
	return signedDistanceToLineTimesLength(p0,p1) > 0;
}

HK_FORCE_INLINE hkBool32 hkVector2f::inCircumcircle( const hkVector2f& p0, const hkVector2f& p1, const hkVector2f& p2, hkFloat32 tolerance ) const
{
	hkVector4f a; a.set( p0.x - x, p1.x - x, p2.x - x );
	hkVector4f b; b.set( p0.y - y, p1.y - y, p2.y - y );
	hkVector4f temp1; temp1.setMul( a, a );
	hkVector4f temp2; temp2.setMul( b, b );
	hkVector4f c; c.setAdd( temp1, temp2 );
	hkVector4f vCross; vCross.setCross( b, c );
	return a.dot<3>( vCross ).getReal() > -tolerance; // XXX
}

HK_FORCE_INLINE hkBool32 hkVector2f::equals( const hkVector2f& p0 ) const
{
	return x == p0.x && y == p0.y;
}

HK_FORCE_INLINE hkFloat32 hkVector2f::dot( const hkVector2f& p ) const
{
	return x*p.x + y*p.y;
}

HK_FORCE_INLINE void hkVector2f::setMax( const hkVector2f& a, const hkVector2f& b )
{
	x = hkMath::max2(a.x,b.x);
	y = hkMath::max2(a.y,b.y);
}

HK_FORCE_INLINE void hkVector2f::setMin( const hkVector2f& a, const hkVector2f& b )
{
	x = hkMath::min2(a.x,b.x);
	y = hkMath::min2(a.y,b.y);
}

HK_FORCE_INLINE void hkVector2f::setAll( hkFloat32 a )
{
	x = a;
	y = a;
}

HK_FORCE_INLINE void hkVector2f::set( hkFloat32 a, hkFloat32 b )
{
	x = a;
	y = b;
}

HK_FORCE_INLINE void hkVector2f::set( hkSimdFloat32Parameter a, hkSimdFloat32Parameter b )
{
	a.store<1>(&x);
	b.store<1>(&y);
}

HK_FORCE_INLINE void hkVector2f::load( const hkFloat32* p )
{
	x = p[0];
	y = p[1];
}

HK_FORCE_INLINE void hkVector2f::convertToVector4( hkVector4f& vOut ) const
{
	vOut.load<2,HK_IO_NATIVE_ALIGNED>( &x );
}

HK_FORCE_INLINE void hkVector2f::convertFromVector4( hkVector4fParameter vIn )
{
	vIn.store<2,HK_IO_NATIVE_ALIGNED>( &x );
}

HK_FORCE_INLINE void hkVector2f::setPerp( const hkVector2f& a )
{
	hkFloat32 t = a.x; // alias safe
	x = -a.y;
	y =  t;
}

HK_FORCE_INLINE void hkVector2f::setAdd( const hkVector2f& a, const hkVector2f& b )
{
	x = a.x + b.x;
	y = a.y + b.y;
}

HK_FORCE_INLINE void hkVector2f::add( const hkVector2f& a )
{
	x += a.x;
	y += a.y;
}

HK_FORCE_INLINE void hkVector2f::setMul( const hkVector2f& v, hkFloat32 r )
{
	x = v.x * r;
	y = v.y * r;
}

HK_FORCE_INLINE void hkVector2f::setMul( const hkVector2f& v, const hkVector2f& w )
{
	x = v.x * w.x;
	y = v.y * w.y;
}

HK_FORCE_INLINE void hkVector2f::mul( hkFloat32 r )
{
	x *= r;
	y *= r;
}

HK_FORCE_INLINE void hkVector2f::setAddMul( const hkVector2f& a, const hkVector2f& b, hkFloat32 r )
{
	x = a.x + b.x * r;
	y = a.y + b.y * r;
}

HK_FORCE_INLINE void hkVector2f::addMul( const hkVector2f& a, const hkVector2f& b )
{
	x += a.x * b.x;
	y += a.y * b.y;
}

HK_FORCE_INLINE void hkVector2f::addMul( const hkVector2f& a, hkFloat32 b )
{
	x += a.x * b;
	y += a.y * b;
}

HK_FORCE_INLINE void hkVector2f::addMul( hkFloat32 a, const hkVector2f& b )
{
	x += a * b.x;
	y += a * b.y;
}

HK_FORCE_INLINE void hkVector2f::setSub( const hkVector2f& a, const hkVector2f& b )
{
	x = a.x - b.x;
	y = a.y - b.y;
}

HK_FORCE_INLINE void hkVector2f::setInterpolate( const hkVector2f& a, const hkVector2f& b, hkFloat32 t)
{
	x = a.x + t * (b.x-a.x);
	y = a.y + t * (b.y-a.y);
}

HK_FORCE_INLINE hkFloat32 hkVector2f::distanceTo( const hkVector2f& p ) const
{
	hkFloat32 dx = x - p.x;
	hkFloat32 dy = y - p.y;
	return hkMath::sqrt( dx*dx + dy*dy );
}

HK_FORCE_INLINE void hkVector2f::setProject( hkVector4fParameter p, hkVector4fParameter ax, hkVector4fParameter ay )
{
	x = ax.dot<3>(p).getReal();
	y = ay.dot<3>(p).getReal();
}

inline void hkVector2f::normalize()
{
	normalize<HK_ACC_23_BIT, HK_SQRT_SET_ZERO>();
}

inline hkFloat32 hkVector2f::normalizeWithLength()
{
	return normalizeWithLength<HK_ACC_23_BIT, HK_SQRT_SET_ZERO>();
}

template <hkMathAccuracyMode A, hkMathNegSqrtMode S>
HK_FORCE_INLINE void hkVector2f::normalize()
{
	hkVector4f v;
	convertToVector4(v);
	v.normalize<2, A, S>();
	convertFromVector4(v);
}


template <hkMathAccuracyMode A, hkMathNegSqrtMode S>
HK_FORCE_INLINE hkFloat32 hkVector2f::normalizeWithLength()
{
	hkVector4f v;
	convertToVector4(v);
	hkSimdFloat32 len = v.normalizeWithLength<2, A, S>();
	convertFromVector4(v);

	return len.getReal();
}

HK_FORCE_INLINE hkFloat32 hkVector2f::length() const
{
	return hkMath::sqrt(x*x + y*y);
}

HK_FORCE_INLINE void hkVector2f::setZero()
{
	x = y = 0;
}

HK_FORCE_INLINE hkBool32 hkVector2f::lexLess( const hkVector2f& v )
{
	return (x<v.x) || (x==v.x && y<v.y);
}

//
//	Sets this = -v

HK_FORCE_INLINE void hkVector2f::setNeg(const hkVector2f& v)
{
	x = -v.x;
	y = -v.y;
}

//
//	Computes the cross product of the two vectors

HK_FORCE_INLINE hkFloat32 HK_CALL hkVector2f::cross(const hkVector2f& vA, const hkVector2f& vB)
{
	return vA.x * vB.y - vA.y * vB.x;
}

HK_FORCE_INLINE void HK_CALL hkVector2f::cross(const hkVector2f& vA, const hkVector2f& vB, hkVector4f& crossOut)
{
	crossOut.set(0.0f, 0.0f, hkVector2f::cross(vA, vB));
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
