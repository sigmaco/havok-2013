/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

HK_FORCE_INLINE const hkVector4d& hkMatrix4d::getColumn(int x) const
{
	return (&m_col0)[x];
}

HK_FORCE_INLINE hkVector4d& hkMatrix4d::getColumn(int x)
{
	return (&m_col0)[x];
}

HK_FORCE_INLINE void hkMatrix4d::setColumn(int x, hkVector4dParameter c)
{
	(&m_col0)[x] = c;
}

template <>
HK_FORCE_INLINE const hkVector4d& hkMatrix4d::getColumn<3>() const
{
	return m_col3;
}

template <>
HK_FORCE_INLINE const hkVector4d& hkMatrix4d::getColumn<2>() const
{
	return m_col2;
}

template <>
HK_FORCE_INLINE const hkVector4d& hkMatrix4d::getColumn<1>() const
{
	return m_col1;
}

template <>
HK_FORCE_INLINE const hkVector4d& hkMatrix4d::getColumn<0>() const
{
	return m_col0;
}

template <int N>
HK_FORCE_INLINE const hkVector4d& hkMatrix4d::getColumn() const
{
	HK_MATRIX4d_NOT_IMPLEMENTED;
	return hkVector4d::getConstant<HK_QUADREAL_0>();
}

template <>
HK_FORCE_INLINE void hkMatrix4d::setColumn<3>(hkVector4dParameter c)
{
	m_col3 = c;
}

template <>
HK_FORCE_INLINE void hkMatrix4d::setColumn<2>(hkVector4dParameter c)
{
	m_col2 = c;
}

template <>
HK_FORCE_INLINE void hkMatrix4d::setColumn<1>(hkVector4dParameter c)
{
	m_col1 = c;
}

template <>
HK_FORCE_INLINE void hkMatrix4d::setColumn<0>(hkVector4dParameter c)
{
	m_col0 = c;
}

template <int N>
HK_FORCE_INLINE void hkMatrix4d::setColumn(hkVector4dParameter c)
{
	HK_MATRIX4d_NOT_IMPLEMENTED;
}

HK_FORCE_INLINE hkDouble64& hkMatrix4d::operator() (int r, int c)
{
	return (&m_col0)[c](r);
}

HK_FORCE_INLINE const hkDouble64& hkMatrix4d::operator() (int r, int c) const
{
	return getColumn(c)(r);
}

template <int ROW, int COL>
HK_FORCE_INLINE const hkSimdDouble64 hkMatrix4d::getElement() const
{
// our reflection parser cannot compile this:	return getColumn<COL>().getComponent<ROW>();
	return (&m_col0)[COL].getComponent<ROW>();
}

template <int ROW, int COL>
HK_FORCE_INLINE void hkMatrix4d::setElement(hkSimdDouble64Parameter element)
{
	(&m_col0)[COL].setComponent<ROW>(element);
}

HK_FORCE_INLINE void hkMatrix4d::setRows( hkVector4dParameter r0, hkVector4dParameter r1, hkVector4dParameter r2, hkVector4dParameter r3)
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	m_col0 = r0;
	m_col1 = r1;
	m_col2 = r2;
	m_col3 = r3;
	HK_TRANSPOSE4d(m_col0,m_col1,m_col2,m_col3);
#else
	hkVector4d c0; c0.set( r0(0), r1(0), r2(0), r3(0) );
	hkVector4d c1; c1.set( r0(1), r1(1), r2(1), r3(1) );
	hkVector4d c2; c2.set( r0(2), r1(2), r2(2), r3(2) );
	hkVector4d c3; c3.set( r0(3), r1(3), r2(3), r3(3) );

	setColumn<0>(c0);
	setColumn<1>(c1);
	setColumn<2>(c2);
	setColumn<3>(c3);
#endif
}


HK_FORCE_INLINE void hkMatrix4d::getRows( hkVector4d& r0, hkVector4d& r1, hkVector4d& r2, hkVector4d& r3) const
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	hkVector4d c0 = getColumn<0>();
	hkVector4d c1 = getColumn<1>();
	hkVector4d c2 = getColumn<2>();
	hkVector4d c3 = getColumn<3>();

	HK_TRANSPOSE4d(c0,c1,c2,c3);
#else
	hkVector4d c0; c0.set( m_col0(0), m_col1(0), m_col2(0), m_col3(0) );
	hkVector4d c1; c1.set( m_col0(1), m_col1(1), m_col2(1), m_col3(1) );
	hkVector4d c2; c2.set( m_col0(2), m_col1(2), m_col2(2), m_col3(2) );
	hkVector4d c3; c3.set( m_col0(3), m_col1(3), m_col2(3), m_col3(3) );
#endif

	r0 = c0;
	r1 = c1;
	r2 = c2;
	r3 = c3;
}

HK_FORCE_INLINE void hkMatrix4d::setCols( hkVector4dParameter c0, hkVector4dParameter c1, hkVector4dParameter c2, hkVector4dParameter c3)
{
	m_col0 = c0;
	m_col1 = c1;
	m_col2 = c2;
	m_col3 = c3;
}

HK_FORCE_INLINE void hkMatrix4d::operator= ( const hkMatrix4d& a )
{
	m_col0 = a.getColumn<0>();
	m_col1 = a.getColumn<1>();
	m_col2 = a.getColumn<2>();
	m_col3 = a.getColumn<3>();
}

HK_FORCE_INLINE void hkMatrix4d::getCols( hkVector4d& c0, hkVector4d& c1, hkVector4d& c2, hkVector4d& c3) const
{
	c0 = m_col0;
	c1 = m_col1;
	c2 = m_col2;
	c3 = m_col3;
}

HK_FORCE_INLINE void hkMatrix4d::getRow( int row, hkVector4d& r) const
{
	r.set( m_col0(row), m_col1(row), m_col2(row), m_col3(row) );
}

template <int I>
HK_FORCE_INLINE void hkMatrix4d::getRow( hkVector4d& r ) const
{
	r.set( getElement<I,0>(), getElement<I,1>(), getElement<I,2>(), getElement<I,3>() );
}

HK_FORCE_INLINE void hkMatrix4d::setRow( int row, hkVector4dParameter r )
{
	m_col0(row) = r(0);
	m_col1(row) = r(1);
	m_col2(row) = r(2);
	m_col3(row) = r(3);
}

template <int I>
HK_FORCE_INLINE void hkMatrix4d::setRow( hkVector4dParameter r )
{
	setElement<I,0>( r.getComponent<0>() );
	setElement<I,1>( r.getComponent<1>() );
	setElement<I,2>( r.getComponent<2>() );
	setElement<I,3>( r.getComponent<3>() );
}

HK_FORCE_INLINE void hkMatrix4d::setZero()
{
	m_col0.setZero();
	m_col1.setZero();
	m_col2.setZero();
	m_col3.setZero();
}

HK_FORCE_INLINE void hkMatrix4d::setDiagonal( hkDouble64 m00, hkDouble64 m11, hkDouble64 m22, hkDouble64 m33 )
{
	setZero();
	m_col0(0) = m00;
	m_col1(1) = m11;
	m_col2(2) = m22;
	m_col3(3) = m33;
}

HK_FORCE_INLINE void hkMatrix4d::setDiagonal( hkSimdDouble64Parameter m00, hkSimdDouble64Parameter m11, hkSimdDouble64Parameter m22, hkSimdDouble64Parameter m33 )
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	const hkVector4d* HK_RESTRICT id = (const hkVector4d* HK_RESTRICT)(g_vectordConstants + HK_QUADREAL_1000);
	m_col0.setMul(id[0], m00);
	m_col1.setMul(id[1], m11);
	m_col2.setMul(id[2], m22);
	m_col3.setMul(id[3], m33);
#else
	setZero();
	m_col0(0) = m00.getReal();
	m_col1(1) = m11.getReal();
	m_col2(2) = m22.getReal();
	m_col3(3) = m33.getReal();
#endif
}

HK_FORCE_INLINE void hkMatrix4d::setDiagonal( hkVector4dParameter v )
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	const hkVector4d* HK_RESTRICT id = (const hkVector4d* HK_RESTRICT)(g_vectordConstants + HK_QUADREAL_1000);
	m_col0.setMul(id[0], v);
	m_col1.setMul(id[1], v);
	m_col2.setMul(id[2], v);
	m_col3.setMul(id[3], v);
#else
	setZero();
	m_col0(0) = v(0);
	m_col1(1) = v(1);
	m_col2(2) = v(2);
	m_col3(3) = v(3);
#endif
}

HK_FORCE_INLINE void hkMatrix4d::getDiagonal( hkVector4d& v ) const
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	const hkVector4d* HK_RESTRICT id = (const hkVector4d* HK_RESTRICT)(g_vectordConstants + HK_QUADREAL_1000);
	v.setZero();
	v.addMul(id[0], m_col0);
	v.addMul(id[1], m_col1);
	v.addMul(id[2], m_col2);
	v.addMul(id[3], m_col3);
#else
	v.set(m_col0(0), m_col1(1), m_col2(2), m_col3(3));
#endif
}

HK_FORCE_INLINE void hkMatrix4d::setIdentity()
{
	const hkVector4d* HK_RESTRICT id = (const hkVector4d* HK_RESTRICT)(g_vectordConstants + HK_QUADREAL_1000);
	m_col0 = id[0];
	m_col1 = id[1];
	m_col2 = id[2];
	m_col3 = id[3];
}

HK_FORCE_INLINE void hkMatrix4d::transformPosition (hkVector4dParameter positionIn, hkVector4d& positionOut) const
{
	
	//HK_WARN_ON_DEBUG_IF(!isAffineTransformation(),0x872bbf1a, "Trying to transform a position by a 4x4 matrix not representing an affine transformation");	// removing warning (note: there is still hkTransformd)

	hkSimdDouble64 xb = positionIn.getComponent<0>();
	hkSimdDouble64 yb = positionIn.getComponent<1>();
	hkSimdDouble64 zb = positionIn.getComponent<2>();

	hkVector4d t0;	
	t0.setAddMul( m_col3, m_col0, xb );
	t0.addMul( yb, m_col1 );
	t0.addMul( zb, m_col2 );

	positionOut = t0;
}

HK_FORCE_INLINE void hkMatrix4d::multiplyVector (hkVector4dParameter v, hkVector4d& resultOut) const
{
	hkSimdDouble64 xb = v.getComponent<0>();
	hkSimdDouble64 yb = v.getComponent<1>();
	hkSimdDouble64 zb = v.getComponent<2>();
	hkSimdDouble64 wb = v.getComponent<3>();

	hkVector4d t0;
	t0.setMul( xb, m_col0 );
	t0.addMul( yb, m_col1 );
	t0.addMul( zb, m_col2 );
	t0.addMul( wb, m_col3 );

	resultOut = t0;
}

HK_FORCE_INLINE void hkMatrix4d::transformDirection (hkVector4dParameter directionIn, hkVector4d& directionOut) const
{
	hkSimdDouble64 xb = directionIn.getComponent<0>();
	hkSimdDouble64 yb = directionIn.getComponent<1>();
	hkSimdDouble64 zb = directionIn.getComponent<2>();

	hkVector4d t0;
	t0.setMul( xb, m_col0 );
	t0.addMul( yb, m_col1 );
	t0.addMul( zb, m_col2 );

	directionOut = t0;
}

HK_FORCE_INLINE void hkMatrix4d::setTranspose( const hkMatrix4d& s )
{
	setRows(s.getColumn<0>(), s.getColumn<1>(), s.getColumn<2>(), s.getColumn<3>());
}

HK_FORCE_INLINE void hkMatrix4d::transformInverseDirection (hkVector4dParameter directionIn, hkVector4d& directionOut) const
{
	hkMatrix4d	t; t.setTranspose(*this);
	t.transformDirection(directionIn,directionOut);
}

HK_FORCE_INLINE void hkMatrix4d::setMulAffine ( const hkMatrix4d& a, const hkMatrix4d& b )
{
	HK_WARN_ON_DEBUG_IF(!a.isAffineTransformation(),0x872bbf1d, "Matrix A in setMulAffine() is not an affine transformation");
	HK_WARN_ON_DEBUG_IF(!b.isAffineTransformation(),0x872bbf1e, "Matrix B in setMulAffine() is not an affine transformation");

	// We need to make it alias save
	hkVector4d col0; a.transformDirection(b.m_col0, col0);
	hkVector4d col1; a.transformDirection(b.m_col1, col1);
	hkVector4d col2; a.transformDirection(b.m_col2, col2);
	hkVector4d col3; a.transformPosition(b.m_col3, col3);

	m_col0 = col0; 
	m_col1 = col1; 
	m_col2 = col2; 
	m_col3 = col3;
}

HK_FORCE_INLINE void hkMatrix4d::mulAffine ( const hkMatrix4d& a )
{
	// SetMul is alias safe
	setMulAffine(*this, a);
}

HK_FORCE_INLINE /*static*/ const hkMatrix4d& HK_CALL hkMatrix4d::getIdentity()
{
	return reinterpret_cast<const hkMatrix4d&>( g_vectordConstants[HK_QUADREAL_1000] );
}

HK_FORCE_INLINE bool hkMatrix4d::isApproximatelyEqual( const hkMatrix4d& m, hkSimdDouble64Parameter epsilon) const
{
	hkVector4d epsilon_v; epsilon_v.setAll(epsilon);

	hkVector4d t0; t0.setSub(m_col0, m.getColumn<0>());	t0.setAbs( t0 );
	hkVector4d t1; t1.setSub(m_col1, m.getColumn<1>());	t1.setAbs( t1 );
	hkVector4d t2; t2.setSub(m_col2, m.getColumn<2>());	t2.setAbs( t2 );
	hkVector4d t3; t3.setSub(m_col3, m.getColumn<3>());	t3.setAbs( t3 );

	t0.setMax( t0, t1 );
	t2.setMax( t2, t3 );
	t0.setMax( t0, t2 );
	return t0.lessEqual( epsilon_v ).allAreSet();
}

HK_FORCE_INLINE hkBool32 hkMatrix4d::isApproximatelyIdentity( hkSimdDouble64Parameter epsilon) const
{
	hkVector4d epsilon_v; epsilon_v.setAll(epsilon);
	const hkVector4d* HK_RESTRICT id = (const hkVector4d* HK_RESTRICT)(g_vectordConstants + HK_QUADREAL_1000);

	hkVector4d t0; t0.setSub(m_col0, id[0]);	t0.setAbs( t0 );
	hkVector4d t1; t1.setSub(m_col1, id[1]);	t1.setAbs( t1 );
	hkVector4d t2; t2.setSub(m_col2, id[2]);	t2.setAbs( t2 );
	hkVector4d t3; t3.setSub(m_col3, id[3]);	t3.setAbs( t3 );

	t0.setMax( t0, t1 );
	t2.setMax( t2, t3 );
	t0.setMax( t0, t2 );
	return t0.lessEqual( epsilon_v ).allAreSet();
}

HK_FORCE_INLINE void hkMatrix4d::setMul( const hkMatrix4d& a, const hkMatrix4d& b )
{
	HK_ASSERT(0x6d9d1d43,  this != &a );
	HK_ASSERT(0x64a8df81,  this != &b );

#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	hkVector4d col0, col1, col2, col3;

	col0.setMul( b.m_col0.getComponent<0>(), a.m_col0);
	col1.setMul( b.m_col1.getComponent<0>(), a.m_col0);
	col2.setMul( b.m_col2.getComponent<0>(), a.m_col0);
	col3.setMul( b.m_col3.getComponent<0>(), a.m_col0);

	col0.addMul( b.m_col0.getComponent<1>(), a.m_col1);
	col1.addMul( b.m_col1.getComponent<1>(), a.m_col1);
	col2.addMul( b.m_col2.getComponent<1>(), a.m_col1);
	col3.addMul( b.m_col3.getComponent<1>(), a.m_col1);

	col0.addMul( b.m_col0.getComponent<2>(), a.m_col2);
	col1.addMul( b.m_col1.getComponent<2>(), a.m_col2);
	col2.addMul( b.m_col2.getComponent<2>(), a.m_col2);
	col3.addMul( b.m_col3.getComponent<2>(), a.m_col2);

	col0.addMul( b.m_col0.getComponent<3>(), a.m_col3 );
	col1.addMul( b.m_col1.getComponent<3>(), a.m_col3 );
	col2.addMul( b.m_col2.getComponent<3>(), a.m_col3 );
	col3.addMul( b.m_col3.getComponent<3>(), a.m_col3 );
	
	m_col0 = col0;
	m_col1 = col1;
	m_col2 = col2;
	m_col3 = col3;

#else
	hkMatrix4d aTrans = a;
	aTrans.transpose();

	hkMatrix4d& result = *this;

	for (int c=0; c < 4; c++)
	{
		for (int r=0; r < 4; r++)
		{
			result(r,c) = aTrans.getColumn(r).dot<4>( b.getColumn(c) ).getReal();
		}
	}
#endif
}


HK_FORCE_INLINE void hkMatrix4d::mul( const hkMatrix4d& a )
{
	
	hkMatrix4d temp;
	temp.setMul( *this, a );
	*this = temp;
}

HK_FORCE_INLINE void hkMatrix4d::setMul( hkSimdDouble64Parameter scale, const hkMatrix4d& a)
{
	m_col0.setMul(a.getColumn<0>(), scale);
	m_col1.setMul(a.getColumn<1>(), scale);
	m_col2.setMul(a.getColumn<2>(), scale);
	m_col3.setMul(a.getColumn<3>(), scale);
}

HK_FORCE_INLINE void hkMatrix4d::mul( hkSimdDouble64Parameter scale)
{
	m_col0.mul(scale);
	m_col1.mul(scale);
	m_col2.mul(scale);
	m_col3.mul(scale);
}

HK_FORCE_INLINE void hkMatrix4d::resetFourthRow ()
{
	m_col0.zeroComponent<3>();
	m_col1.zeroComponent<3>();
	m_col2.zeroComponent<3>();
	m_col3.setComponent<3>( hkSimdDouble64::getConstant<HK_QUADREAL_1>() );
}

HK_FORCE_INLINE void hkMatrix4d::set(const hkTransformd& t)
{
	m_col0 = t.getColumn<0>();
	m_col1 = t.getColumn<1>();
	m_col2 = t.getColumn<2>();
	m_col3 = t.getTranslation();
	resetFourthRow();
}

HK_FORCE_INLINE void hkMatrix4d::get(hkTransformd& t) const
{
	t.setColumn<0>(m_col0);
	t.setColumn<1>(m_col1);
	t.setColumn<2>(m_col2);
	t.setColumn<3>(m_col3);
}

HK_FORCE_INLINE void hkMatrix4d::_add( const hkMatrix4d& a )
{
	m_col0.add( a.getColumn<0>() );
	m_col1.add( a.getColumn<1>() );
	m_col2.add( a.getColumn<2>() );
	m_col3.add( a.getColumn<3>() );
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
