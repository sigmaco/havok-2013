/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
HK_FORCE_INLINE hkDouble64 hkVector2d::signedDistanceToLineTimesLength( const hkVector2d& p0, const hkVector2d& p1 ) const
{
	return ((p1.x - p0.x)*(y - p0.y) - (x - p0.x)*(p1.y - p0.y));
}

HK_FORCE_INLINE hkBool32 hkVector2d::rightOfLine( const hkVector2d& p0, const hkVector2d& p1 ) const
{
	return signedDistanceToLineTimesLength(p0,p1) < 0;
}

HK_FORCE_INLINE hkBool32 hkVector2d::leftOfLine( const hkVector2d& p0, const hkVector2d& p1 ) const
{
	return signedDistanceToLineTimesLength(p0,p1) > 0;
}

HK_FORCE_INLINE hkBool32 hkVector2d::inCircumcircle( const hkVector2d& p0, const hkVector2d& p1, const hkVector2d& p2, hkDouble64 tolerance ) const
{
	hkVector4d a; a.set( p0.x - x, p1.x - x, p2.x - x );
	hkVector4d b; b.set( p0.y - y, p1.y - y, p2.y - y );
	hkVector4d temp1; temp1.setMul( a, a );
	hkVector4d temp2; temp2.setMul( b, b );
	hkVector4d c; c.setAdd( temp1, temp2 );
	hkVector4d vCross; vCross.setCross( b, c );
	return a.dot<3>( vCross ).getReal() > -tolerance; // XXX
}

HK_FORCE_INLINE hkBool32 hkVector2d::equals( const hkVector2d& p0 ) const
{
	return x == p0.x && y == p0.y;
}

HK_FORCE_INLINE hkDouble64 hkVector2d::dot( const hkVector2d& p ) const
{
	return x*p.x + y*p.y;
}

HK_FORCE_INLINE void hkVector2d::setMax( const hkVector2d& a, const hkVector2d& b )
{
	x = hkMath::max2(a.x,b.x);
	y = hkMath::max2(a.y,b.y);
}

HK_FORCE_INLINE void hkVector2d::setMin( const hkVector2d& a, const hkVector2d& b )
{
	x = hkMath::min2(a.x,b.x);
	y = hkMath::min2(a.y,b.y);
}

HK_FORCE_INLINE void hkVector2d::setAll( hkDouble64 a )
{
	x = a;
	y = a;
}

HK_FORCE_INLINE void hkVector2d::set( hkDouble64 a, hkDouble64 b )
{
	x = a;
	y = b;
}

HK_FORCE_INLINE void hkVector2d::set( hkSimdDouble64Parameter a, hkSimdDouble64Parameter b )
{
	a.store<1>(&x);
	b.store<1>(&y);
}

HK_FORCE_INLINE void hkVector2d::load( const hkDouble64* p )
{
	x = p[0];
	y = p[1];
}

HK_FORCE_INLINE void hkVector2d::convertToVector4( hkVector4d& vOut ) const
{
	vOut.load<2,HK_IO_NATIVE_ALIGNED>( &x );
}

HK_FORCE_INLINE void hkVector2d::convertFromVector4( hkVector4dParameter vIn )
{
	vIn.store<2,HK_IO_NATIVE_ALIGNED>( &x );
}

HK_FORCE_INLINE void hkVector2d::setPerp( const hkVector2d& a )
{
	hkDouble64 t = a.x; // alias safe
	x = -a.y;
	y =  t;
}

HK_FORCE_INLINE void hkVector2d::setAdd( const hkVector2d& a, const hkVector2d& b )
{
	x = a.x + b.x;
	y = a.y + b.y;
}

HK_FORCE_INLINE void hkVector2d::add( const hkVector2d& a )
{
	x += a.x;
	y += a.y;
}

HK_FORCE_INLINE void hkVector2d::setMul( const hkVector2d& v, hkDouble64 r )
{
	x = v.x * r;
	y = v.y * r;
}

HK_FORCE_INLINE void hkVector2d::setMul( const hkVector2d& v, const hkVector2d& w )
{
	x = v.x * w.x;
	y = v.y * w.y;
}

HK_FORCE_INLINE void hkVector2d::mul( hkDouble64 r )
{
	x *= r;
	y *= r;
}

HK_FORCE_INLINE void hkVector2d::setAddMul( const hkVector2d& a, const hkVector2d& b, hkDouble64 r )
{
	x = a.x + b.x * r;
	y = a.y + b.y * r;
}

HK_FORCE_INLINE void hkVector2d::addMul( const hkVector2d& a, const hkVector2d& b )
{
	x += a.x * b.x;
	y += a.y * b.y;
}

HK_FORCE_INLINE void hkVector2d::addMul( const hkVector2d& a, hkDouble64 b )
{
	x += a.x * b;
	y += a.y * b;
}

HK_FORCE_INLINE void hkVector2d::addMul( hkDouble64 a, const hkVector2d& b )
{
	x += a * b.x;
	y += a * b.y;
}

HK_FORCE_INLINE void hkVector2d::setSub( const hkVector2d& a, const hkVector2d& b )
{
	x = a.x - b.x;
	y = a.y - b.y;
}

HK_FORCE_INLINE void hkVector2d::setInterpolate( const hkVector2d& a, const hkVector2d& b, hkDouble64 t)
{
	x = a.x + t * (b.x-a.x);
	y = a.y + t * (b.y-a.y);
}

HK_FORCE_INLINE hkDouble64 hkVector2d::distanceTo( const hkVector2d& p ) const
{
	hkDouble64 dx = x - p.x;
	hkDouble64 dy = y - p.y;
	return hkMath::sqrt( dx*dx + dy*dy );
}

HK_FORCE_INLINE void hkVector2d::setProject( hkVector4dParameter p, hkVector4dParameter ax, hkVector4dParameter ay )
{
	x = ax.dot<3>(p).getReal();
	y = ay.dot<3>(p).getReal();
}

inline void hkVector2d::normalize()
{
	normalize<HK_ACC_23_BIT, HK_SQRT_SET_ZERO>();
}

inline hkDouble64 hkVector2d::normalizeWithLength()
{
	return normalizeWithLength<HK_ACC_23_BIT, HK_SQRT_SET_ZERO>();
}

template <hkMathAccuracyMode A, hkMathNegSqrtMode S>
HK_FORCE_INLINE void hkVector2d::normalize()
{
	hkVector4d v;
	convertToVector4(v);
	v.normalize<2, A, S>();
	convertFromVector4(v);
}


template <hkMathAccuracyMode A, hkMathNegSqrtMode S>
HK_FORCE_INLINE hkDouble64 hkVector2d::normalizeWithLength()
{
	hkVector4d v;
	convertToVector4(v);
	hkSimdDouble64 len = v.normalizeWithLength<2, A, S>();
	convertFromVector4(v);

	return len.getReal();
}

HK_FORCE_INLINE hkDouble64 hkVector2d::length() const
{
	return hkMath::sqrt(x*x + y*y);
}

HK_FORCE_INLINE void hkVector2d::setZero()
{
	x = y = 0;
}

HK_FORCE_INLINE hkBool32 hkVector2d::lexLess( const hkVector2d& v )
{
	return (x<v.x) || (x==v.x && y<v.y);
}

//
//	Sets this = -v

HK_FORCE_INLINE void hkVector2d::setNeg(const hkVector2d& v)
{
	x = -v.x;
	y = -v.y;
}

//
//	Computes the cross product of the two vectors

HK_FORCE_INLINE hkDouble64 HK_CALL hkVector2d::cross(const hkVector2d& vA, const hkVector2d& vB)
{
	return vA.x * vB.y - vA.y * vB.x;
}

HK_FORCE_INLINE void HK_CALL hkVector2d::cross(const hkVector2d& vA, const hkVector2d& vB, hkVector4d& crossOut)
{
	crossOut.set(0.0f, 0.0f, hkVector2d::cross(vA, vB));
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
