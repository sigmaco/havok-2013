/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

HK_FORCE_INLINE const hkVector4f& hkMatrix4f::getColumn(int x) const
{
	return (&m_col0)[x];
}

HK_FORCE_INLINE hkVector4f& hkMatrix4f::getColumn(int x)
{
	return (&m_col0)[x];
}

HK_FORCE_INLINE void hkMatrix4f::setColumn(int x, hkVector4fParameter c)
{
	(&m_col0)[x] = c;
}

template <>
HK_FORCE_INLINE const hkVector4f& hkMatrix4f::getColumn<3>() const
{
	return m_col3;
}

template <>
HK_FORCE_INLINE const hkVector4f& hkMatrix4f::getColumn<2>() const
{
	return m_col2;
}

template <>
HK_FORCE_INLINE const hkVector4f& hkMatrix4f::getColumn<1>() const
{
	return m_col1;
}

template <>
HK_FORCE_INLINE const hkVector4f& hkMatrix4f::getColumn<0>() const
{
	return m_col0;
}

template <int N>
HK_FORCE_INLINE const hkVector4f& hkMatrix4f::getColumn() const
{
	HK_MATRIX4f_NOT_IMPLEMENTED;
	return hkVector4f::getConstant<HK_QUADREAL_0>();
}

template <>
HK_FORCE_INLINE void hkMatrix4f::setColumn<3>(hkVector4fParameter c)
{
	m_col3 = c;
}

template <>
HK_FORCE_INLINE void hkMatrix4f::setColumn<2>(hkVector4fParameter c)
{
	m_col2 = c;
}

template <>
HK_FORCE_INLINE void hkMatrix4f::setColumn<1>(hkVector4fParameter c)
{
	m_col1 = c;
}

template <>
HK_FORCE_INLINE void hkMatrix4f::setColumn<0>(hkVector4fParameter c)
{
	m_col0 = c;
}

template <int N>
HK_FORCE_INLINE void hkMatrix4f::setColumn(hkVector4fParameter c)
{
	HK_MATRIX4f_NOT_IMPLEMENTED;
}

HK_FORCE_INLINE hkFloat32& hkMatrix4f::operator() (int r, int c)
{
	return (&m_col0)[c](r);
}

HK_FORCE_INLINE const hkFloat32& hkMatrix4f::operator() (int r, int c) const
{
	return getColumn(c)(r);
}

template <int ROW, int COL>
HK_FORCE_INLINE const hkSimdFloat32 hkMatrix4f::getElement() const
{
// our reflection parser cannot compile this:	return getColumn<COL>().getComponent<ROW>();
	return (&m_col0)[COL].getComponent<ROW>();
}

template <int ROW, int COL>
HK_FORCE_INLINE void hkMatrix4f::setElement(hkSimdFloat32Parameter element)
{
	(&m_col0)[COL].setComponent<ROW>(element);
}

HK_FORCE_INLINE void hkMatrix4f::setRows( hkVector4fParameter r0, hkVector4fParameter r1, hkVector4fParameter r2, hkVector4fParameter r3)
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	m_col0 = r0;
	m_col1 = r1;
	m_col2 = r2;
	m_col3 = r3;
	HK_TRANSPOSE4f(m_col0,m_col1,m_col2,m_col3);
#else
	hkVector4f c0; c0.set( r0(0), r1(0), r2(0), r3(0) );
	hkVector4f c1; c1.set( r0(1), r1(1), r2(1), r3(1) );
	hkVector4f c2; c2.set( r0(2), r1(2), r2(2), r3(2) );
	hkVector4f c3; c3.set( r0(3), r1(3), r2(3), r3(3) );

	setColumn<0>(c0);
	setColumn<1>(c1);
	setColumn<2>(c2);
	setColumn<3>(c3);
#endif
}


HK_FORCE_INLINE void hkMatrix4f::getRows( hkVector4f& r0, hkVector4f& r1, hkVector4f& r2, hkVector4f& r3) const
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	hkVector4f c0 = getColumn<0>();
	hkVector4f c1 = getColumn<1>();
	hkVector4f c2 = getColumn<2>();
	hkVector4f c3 = getColumn<3>();

	HK_TRANSPOSE4f(c0,c1,c2,c3);
#else
	hkVector4f c0; c0.set( m_col0(0), m_col1(0), m_col2(0), m_col3(0) );
	hkVector4f c1; c1.set( m_col0(1), m_col1(1), m_col2(1), m_col3(1) );
	hkVector4f c2; c2.set( m_col0(2), m_col1(2), m_col2(2), m_col3(2) );
	hkVector4f c3; c3.set( m_col0(3), m_col1(3), m_col2(3), m_col3(3) );
#endif

	r0 = c0;
	r1 = c1;
	r2 = c2;
	r3 = c3;
}

HK_FORCE_INLINE void hkMatrix4f::setCols( hkVector4fParameter c0, hkVector4fParameter c1, hkVector4fParameter c2, hkVector4fParameter c3)
{
	m_col0 = c0;
	m_col1 = c1;
	m_col2 = c2;
	m_col3 = c3;
}

HK_FORCE_INLINE void hkMatrix4f::operator= ( const hkMatrix4f& a )
{
	m_col0 = a.getColumn<0>();
	m_col1 = a.getColumn<1>();
	m_col2 = a.getColumn<2>();
	m_col3 = a.getColumn<3>();
}

HK_FORCE_INLINE void hkMatrix4f::getCols( hkVector4f& c0, hkVector4f& c1, hkVector4f& c2, hkVector4f& c3) const
{
	c0 = m_col0;
	c1 = m_col1;
	c2 = m_col2;
	c3 = m_col3;
}

HK_FORCE_INLINE void hkMatrix4f::getRow( int row, hkVector4f& r) const
{
	r.set( m_col0(row), m_col1(row), m_col2(row), m_col3(row) );
}

template <int I>
HK_FORCE_INLINE void hkMatrix4f::getRow( hkVector4f& r ) const
{
	r.set( getElement<I,0>(), getElement<I,1>(), getElement<I,2>(), getElement<I,3>() );
}

HK_FORCE_INLINE void hkMatrix4f::setRow( int row, hkVector4fParameter r )
{
	m_col0(row) = r(0);
	m_col1(row) = r(1);
	m_col2(row) = r(2);
	m_col3(row) = r(3);
}

template <int I>
HK_FORCE_INLINE void hkMatrix4f::setRow( hkVector4fParameter r )
{
	setElement<I,0>( r.getComponent<0>() );
	setElement<I,1>( r.getComponent<1>() );
	setElement<I,2>( r.getComponent<2>() );
	setElement<I,3>( r.getComponent<3>() );
}

HK_FORCE_INLINE void hkMatrix4f::setZero()
{
	m_col0.setZero();
	m_col1.setZero();
	m_col2.setZero();
	m_col3.setZero();
}

HK_FORCE_INLINE void hkMatrix4f::setDiagonal( hkFloat32 m00, hkFloat32 m11, hkFloat32 m22, hkFloat32 m33 )
{
	setZero();
	m_col0(0) = m00;
	m_col1(1) = m11;
	m_col2(2) = m22;
	m_col3(3) = m33;
}

HK_FORCE_INLINE void hkMatrix4f::setDiagonal( hkSimdFloat32Parameter m00, hkSimdFloat32Parameter m11, hkSimdFloat32Parameter m22, hkSimdFloat32Parameter m33 )
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	const hkVector4f* HK_RESTRICT id = (const hkVector4f* HK_RESTRICT)(g_vectorfConstants + HK_QUADREAL_1000);
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

HK_FORCE_INLINE void hkMatrix4f::setDiagonal( hkVector4fParameter v )
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	const hkVector4f* HK_RESTRICT id = (const hkVector4f* HK_RESTRICT)(g_vectorfConstants + HK_QUADREAL_1000);
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

HK_FORCE_INLINE void hkMatrix4f::getDiagonal( hkVector4f& v ) const
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	const hkVector4f* HK_RESTRICT id = (const hkVector4f* HK_RESTRICT)(g_vectorfConstants + HK_QUADREAL_1000);
	v.setZero();
	v.addMul(id[0], m_col0);
	v.addMul(id[1], m_col1);
	v.addMul(id[2], m_col2);
	v.addMul(id[3], m_col3);
#else
	v.set(m_col0(0), m_col1(1), m_col2(2), m_col3(3));
#endif
}

HK_FORCE_INLINE void hkMatrix4f::setIdentity()
{
	const hkVector4f* HK_RESTRICT id = (const hkVector4f* HK_RESTRICT)(g_vectorfConstants + HK_QUADREAL_1000);
	m_col0 = id[0];
	m_col1 = id[1];
	m_col2 = id[2];
	m_col3 = id[3];
}

HK_FORCE_INLINE void hkMatrix4f::transformPosition (hkVector4fParameter positionIn, hkVector4f& positionOut) const
{
	
	//HK_WARN_ON_DEBUG_IF(!isAffineTransformation(),0x872bbf1a, "Trying to transform a position by a 4x4 matrix not representing an affine transformation");	// removing warning (note: there is still hkTransformf)

	hkSimdFloat32 xb = positionIn.getComponent<0>();
	hkSimdFloat32 yb = positionIn.getComponent<1>();
	hkSimdFloat32 zb = positionIn.getComponent<2>();

	hkVector4f t0;	
	t0.setAddMul( m_col3, m_col0, xb );
	t0.addMul( yb, m_col1 );
	t0.addMul( zb, m_col2 );

	positionOut = t0;
}

HK_FORCE_INLINE void hkMatrix4f::multiplyVector (hkVector4fParameter v, hkVector4f& resultOut) const
{
	hkSimdFloat32 xb = v.getComponent<0>();
	hkSimdFloat32 yb = v.getComponent<1>();
	hkSimdFloat32 zb = v.getComponent<2>();
	hkSimdFloat32 wb = v.getComponent<3>();

	hkVector4f t0;
	t0.setMul( xb, m_col0 );
	t0.addMul( yb, m_col1 );
	t0.addMul( zb, m_col2 );
	t0.addMul( wb, m_col3 );

	resultOut = t0;
}

HK_FORCE_INLINE void hkMatrix4f::transformDirection (hkVector4fParameter directionIn, hkVector4f& directionOut) const
{
	hkSimdFloat32 xb = directionIn.getComponent<0>();
	hkSimdFloat32 yb = directionIn.getComponent<1>();
	hkSimdFloat32 zb = directionIn.getComponent<2>();

	hkVector4f t0;
	t0.setMul( xb, m_col0 );
	t0.addMul( yb, m_col1 );
	t0.addMul( zb, m_col2 );

	directionOut = t0;
}

HK_FORCE_INLINE void hkMatrix4f::setTranspose( const hkMatrix4f& s )
{
	setRows(s.getColumn<0>(), s.getColumn<1>(), s.getColumn<2>(), s.getColumn<3>());
}

HK_FORCE_INLINE void hkMatrix4f::transformInverseDirection (hkVector4fParameter directionIn, hkVector4f& directionOut) const
{
	hkMatrix4f	t; t.setTranspose(*this);
	t.transformDirection(directionIn,directionOut);
}

HK_FORCE_INLINE void hkMatrix4f::setMulAffine ( const hkMatrix4f& a, const hkMatrix4f& b )
{
	HK_WARN_ON_DEBUG_IF(!a.isAffineTransformation(),0x872bbf1d, "Matrix A in setMulAffine() is not an affine transformation");
	HK_WARN_ON_DEBUG_IF(!b.isAffineTransformation(),0x872bbf1e, "Matrix B in setMulAffine() is not an affine transformation");

	// We need to make it alias save
	hkVector4f col0; a.transformDirection(b.m_col0, col0);
	hkVector4f col1; a.transformDirection(b.m_col1, col1);
	hkVector4f col2; a.transformDirection(b.m_col2, col2);
	hkVector4f col3; a.transformPosition(b.m_col3, col3);

	m_col0 = col0; 
	m_col1 = col1; 
	m_col2 = col2; 
	m_col3 = col3;
}

HK_FORCE_INLINE void hkMatrix4f::mulAffine ( const hkMatrix4f& a )
{
	// SetMul is alias safe
	setMulAffine(*this, a);
}

HK_FORCE_INLINE /*static*/ const hkMatrix4f& HK_CALL hkMatrix4f::getIdentity()
{
	return reinterpret_cast<const hkMatrix4f&>( g_vectorfConstants[HK_QUADREAL_1000] );
}

HK_FORCE_INLINE bool hkMatrix4f::isApproximatelyEqual( const hkMatrix4f& m, hkSimdFloat32Parameter epsilon) const
{
	hkVector4f epsilon_v; epsilon_v.setAll(epsilon);

	hkVector4f t0; t0.setSub(m_col0, m.getColumn<0>());	t0.setAbs( t0 );
	hkVector4f t1; t1.setSub(m_col1, m.getColumn<1>());	t1.setAbs( t1 );
	hkVector4f t2; t2.setSub(m_col2, m.getColumn<2>());	t2.setAbs( t2 );
	hkVector4f t3; t3.setSub(m_col3, m.getColumn<3>());	t3.setAbs( t3 );

	t0.setMax( t0, t1 );
	t2.setMax( t2, t3 );
	t0.setMax( t0, t2 );
	return t0.lessEqual( epsilon_v ).allAreSet();
}

HK_FORCE_INLINE hkBool32 hkMatrix4f::isApproximatelyIdentity( hkSimdFloat32Parameter epsilon) const
{
	hkVector4f epsilon_v; epsilon_v.setAll(epsilon);
	const hkVector4f* HK_RESTRICT id = (const hkVector4f* HK_RESTRICT)(g_vectorfConstants + HK_QUADREAL_1000);

	hkVector4f t0; t0.setSub(m_col0, id[0]);	t0.setAbs( t0 );
	hkVector4f t1; t1.setSub(m_col1, id[1]);	t1.setAbs( t1 );
	hkVector4f t2; t2.setSub(m_col2, id[2]);	t2.setAbs( t2 );
	hkVector4f t3; t3.setSub(m_col3, id[3]);	t3.setAbs( t3 );

	t0.setMax( t0, t1 );
	t2.setMax( t2, t3 );
	t0.setMax( t0, t2 );
	return t0.lessEqual( epsilon_v ).allAreSet();
}

HK_FORCE_INLINE void hkMatrix4f::setMul( const hkMatrix4f& a, const hkMatrix4f& b )
{
	HK_ASSERT(0x6d9d1d43,  this != &a );
	HK_ASSERT(0x64a8df81,  this != &b );

#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	hkVector4f col0, col1, col2, col3;

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
	hkMatrix4f aTrans = a;
	aTrans.transpose();

	hkMatrix4f& result = *this;

	for (int c=0; c < 4; c++)
	{
		for (int r=0; r < 4; r++)
		{
			result(r,c) = aTrans.getColumn(r).dot<4>( b.getColumn(c) ).getReal();
		}
	}
#endif
}


HK_FORCE_INLINE void hkMatrix4f::mul( const hkMatrix4f& a )
{
	
	hkMatrix4f temp;
	temp.setMul( *this, a );
	*this = temp;
}

HK_FORCE_INLINE void hkMatrix4f::setMul( hkSimdFloat32Parameter scale, const hkMatrix4f& a)
{
	m_col0.setMul(a.getColumn<0>(), scale);
	m_col1.setMul(a.getColumn<1>(), scale);
	m_col2.setMul(a.getColumn<2>(), scale);
	m_col3.setMul(a.getColumn<3>(), scale);
}

HK_FORCE_INLINE void hkMatrix4f::mul( hkSimdFloat32Parameter scale)
{
	m_col0.mul(scale);
	m_col1.mul(scale);
	m_col2.mul(scale);
	m_col3.mul(scale);
}

HK_FORCE_INLINE void hkMatrix4f::resetFourthRow ()
{
	m_col0.zeroComponent<3>();
	m_col1.zeroComponent<3>();
	m_col2.zeroComponent<3>();
	m_col3.setComponent<3>( hkSimdFloat32::getConstant<HK_QUADREAL_1>() );
}

HK_FORCE_INLINE void hkMatrix4f::set(const hkTransformf& t)
{
	m_col0 = t.getColumn<0>();
	m_col1 = t.getColumn<1>();
	m_col2 = t.getColumn<2>();
	m_col3 = t.getTranslation();
	resetFourthRow();
}

HK_FORCE_INLINE void hkMatrix4f::get(hkTransformf& t) const
{
	t.setColumn<0>(m_col0);
	t.setColumn<1>(m_col1);
	t.setColumn<2>(m_col2);
	t.setColumn<3>(m_col3);
}

HK_FORCE_INLINE void hkMatrix4f::_add( const hkMatrix4f& a )
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
