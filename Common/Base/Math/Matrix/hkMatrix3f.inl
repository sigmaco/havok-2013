/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */


HK_FORCE_INLINE hkVector4f& hkMatrix3f::getColumn(int x)
{
	return (&m_col0)[x];
}

HK_FORCE_INLINE const hkVector4f& hkMatrix3f::getColumn(int x) const
{
	return (&m_col0)[x];
}

#if defined(HK_TINY_SPU_ELF)
template <int N>
HK_MATRIX3f_INLINE const hkVector4f& hkMatrix3f::getColumn() const
{
	return getColumn(N);
}
#else
template <int N>
HK_MATRIX3f_INLINE const hkVector4f& hkMatrix3f::getColumn() const
{
	return (&m_col0)[N];
}
#endif

template <int N>
HK_MATRIX3f_INLINE hkVector4f& hkMatrix3f::getColumn()
{
	return (&m_col0)[N];
}

template <int N> 
HK_MATRIX3f_INLINE void hkMatrix3f::setColumn(hkVector4fParameter c)
{
	(&m_col0)[N] = c;
}


#ifndef HK_DISABLE_MATH_CONSTRUCTORS
HK_FORCE_INLINE hkMatrix3f::hkMatrix3f( const hkMatrix3f& t )
{
	m_col0 = t.getColumn<0>();
	m_col1 = t.getColumn<1>();
	m_col2 = t.getColumn<2>();
}
#endif


HK_FORCE_INLINE hkFloat32& hkMatrix3f::operator() (int r, int c)
{
	return getColumn(c)(r);
}

HK_FORCE_INLINE const hkFloat32& hkMatrix3f::operator() (int r, int c) const
{
	return getColumn(c)(r);
}


template <int ROW, int COL> 
HK_FORCE_INLINE const hkSimdFloat32 hkMatrix3f::getElement() const
{
// our reflection parser cannot compile this:	return getColumn<COL>().getComponent<ROW>();
	return (&m_col0)[COL].getComponent<ROW>();
}

template <int ROW, int COL>
HK_FORCE_INLINE void hkMatrix3f::setElement(hkSimdFloat32Parameter element)
{
	(&m_col0)[COL].setComponent<ROW>(element);
}


HK_FORCE_INLINE void hkMatrix3f::setRows( hkVector4fParameter r0, hkVector4fParameter r1, hkVector4fParameter r2)
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	m_col0 = r0;
	m_col1 = r1;
	m_col2 = r2;
	HK_TRANSPOSE3f(m_col0,m_col1,m_col2);
#else
	hkVector4f c0; c0.set( r0(0), r1(0), r2(0) );
	hkVector4f c1; c1.set( r0(1), r1(1), r2(1) );
	hkVector4f c2; c2.set( r0(2), r1(2), r2(2) );
	hkVector4f c3; c3.set( r0(3), r1(3), r2(3) );

	setColumn<0>(c0);
	setColumn<1>(c1);
	setColumn<2>(c2);
#endif
}


HK_FORCE_INLINE void hkMatrix3f::getRows( hkVector4f& r0, hkVector4f& r1, hkVector4f& r2) const
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	hkVector4f c0 = getColumn<0>();
	hkVector4f c1 = getColumn<1>();
	hkVector4f c2 = getColumn<2>();

	HK_TRANSPOSE3f(c0,c1,c2);
#else
	hkVector4f c0; c0.set( m_col0(0), m_col1(0), m_col2(0) );
	hkVector4f c1; c1.set( m_col0(1), m_col1(1), m_col2(1) );
	hkVector4f c2; c2.set( m_col0(2), m_col1(2), m_col2(2) );
#endif

	r0 = c0;
	r1 = c1;
	r2 = c2;
}

HK_FORCE_INLINE void hkMatrix3f::setCols( hkVector4fParameter c0, hkVector4fParameter c1, hkVector4fParameter c2)
{
	m_col0 = c0;
	m_col1 = c1;
	m_col2 = c2;
}

HK_FORCE_INLINE void hkMatrix3f::operator= ( const hkMatrix3f& a )
{
	m_col0 = a.getColumn<0>();
	m_col1 = a.getColumn<1>();
	m_col2 = a.getColumn<2>();
}

HK_FORCE_INLINE void hkMatrix3f::getCols( hkVector4f& c0, hkVector4f& c1, hkVector4f& c2) const
{
	c0 = m_col0;
	c1 = m_col1;
	c2 = m_col2;
}

HK_FORCE_INLINE void hkMatrix3f::getRow( int row, hkVector4f& r) const
{
	r.set( m_col0(row), m_col1(row), m_col2(row) );
}

template <int I>
HK_FORCE_INLINE void hkMatrix3f::getRow( hkVector4f& r ) const
{
	r.set( getElement<I,0>(), getElement<I,1>(), getElement<I,2>(), getElement<I,2>() );
}

	/// copy and transpose 
HK_FORCE_INLINE void hkMatrix3f::_setTranspose( const hkMatrix3f& s )
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	hkVector4f c0 = s.getColumn<0>();
	hkVector4f c1 = s.getColumn<1>();
	hkVector4f c2 = s.getColumn<2>();
	HK_TRANSPOSE3f(c0,c1,c2);
	m_col0 = c0;
	m_col1 = c1;
	m_col2 = c2;
#else
	hkMatrix3f	cs = s;
	m_col0.set( cs.getElement<0,0>(), cs.getElement<0,1>(), cs.getElement<0,2>(), cs.getElement<0,2>() );
	m_col1.set( cs.getElement<1,0>(), cs.getElement<1,1>(), cs.getElement<1,2>(), cs.getElement<1,2>() );
	m_col2.set( cs.getElement<2,0>(), cs.getElement<2,1>(), cs.getElement<2,2>(), cs.getElement<2,2>() );
#endif
}

//
//	Sets this matrix to be the product of a diagonal matrix (given as a vector) and matrix a (this = diag * a)

HK_FORCE_INLINE void hkMatrix3f::setDiagonalMul(hkVector4fParameter vDiag, const hkMatrix3f& a)
{
	m_col0.setMul(vDiag, a.getColumn<0>());
	m_col1.setMul(vDiag, a.getColumn<1>());
	m_col2.setMul(vDiag, a.getColumn<2>());
}

//
//	Set this matrix to be the product of qa and b.  (this = qa * b)

HK_FORCE_INLINE void hkMatrix3f::setMul(hkQuaternionfParameter qa, const hkMatrix3f& b)
{
#if defined(HK_TINY_SPU_ELF)
	m_col0.setRotatedDir(qa, b.getColumn<0>());
	m_col1.setRotatedDir(qa, b.getColumn<1>());
	m_col2.setRotatedDir(qa, b.getColumn<2>());
#else
	m_col0._setRotatedDir(qa, b.getColumn<0>());
	m_col1._setRotatedDir(qa, b.getColumn<1>());
	m_col2._setRotatedDir(qa, b.getColumn<2>());
#endif
}

/// aTc = aTb * bTc
HK_FORCE_INLINE void hkMatrix3f::_setMul( const hkMatrix3f& aTb, const hkMatrix3f& bTc )
{
	HK_ASSERT(0x6d9d1d43,  this != &aTb );

#if defined(HK_TINY_SPU_ELF)
	m_col0.setRotatedDir(aTb, bTc.getColumn<0>());
	m_col1.setRotatedDir(aTb, bTc.getColumn<1>());
	m_col2.setRotatedDir(aTb, bTc.getColumn<2>());
#else
	m_col0._setRotatedDir(aTb, bTc.getColumn<0>());
	m_col1._setRotatedDir(aTb, bTc.getColumn<1>());
	m_col2._setRotatedDir(aTb, bTc.getColumn<2>());
#endif
}

HK_FORCE_INLINE void hkMatrix3f::_setMul( hkSimdFloat32Parameter scale, const hkMatrix3f& a)
{
	m_col0.setMul(scale, a.getColumn<0>());
	m_col1.setMul(scale, a.getColumn<1>());
	m_col2.setMul(scale, a.getColumn<2>());
}

HK_FORCE_INLINE void hkMatrix3f::_add( const hkMatrix3f& a )
{
	m_col0.add( a.getColumn<0>() );
	m_col1.add( a.getColumn<1>() );
	m_col2.add( a.getColumn<2>() );
}

HK_FORCE_INLINE void hkMatrix3f::_sub( const hkMatrix3f& a )
{
	m_col0.sub( a.getColumn<0>() );
	m_col1.sub( a.getColumn<1>() );
	m_col2.sub( a.getColumn<2>() );
}

HK_FORCE_INLINE void hkMatrix3f::_invertSymmetric()
{
	hkVector4f r0; r0.setCross( m_col1, m_col2 );
    hkVector4f r1; r1.setCross( m_col2, m_col0 );
    hkVector4f r2; r2.setCross( m_col0, m_col1 );

    const hkSimdFloat32 determinant = m_col0.dot<3>(r0);
	HK_MATH_ASSERT( 0xf0140200, hkMath::pow( determinant.getReal(), hkFloat32(1.0f/3.0f) ) > hkMath::sqrt( frobeniusNormSqr().getReal() * HK_FLOAT_EPSILON ) , "You cannot invert this matrix");

	hkSimdFloat32 dinv; dinv.setReciprocal(determinant);
	m_col0.setMul(r0, dinv);
	m_col1.setMul(r1, dinv);
	m_col2.setMul(r2, dinv);
}

HK_FORCE_INLINE void hkMatrix3f::_mul( hkSimdFloat32Parameter scale)
{
	m_col0.mul(scale);
	m_col1.mul(scale);
	m_col2.mul(scale);
}

//
//	Sets the current matrix to be the inverse of the given matrix. Matrix src is assumed to be symmetric non-singular. If the matrix
//	is singular (up to machine precision), the inverse will be set to zero.

HK_FORCE_INLINE void hkMatrix3f::setInverseSymmetric(const hkMatrix3f& src)
{
	// Get source columns
	const hkVector4f c0 = src.getColumn<0>();
	const hkVector4f c1 = src.getColumn<1>();
	const hkVector4f c2 = src.getColumn<2>();

	hkVector4f r0; r0.setCross(c1, c2);
	hkVector4f r1; r1.setCross(c2, c0);
	hkVector4f r2; r2.setCross(c0, c1);

	// Compute 1 / determinant. Set it to zero in case of singular matrices!
	
	const hkSimdFloat32 determinant = c0.dot<3>(r0);
	const hkVector4fComparison cmp = determinant.greater(hkSimdFloat32_Eps);

	hkSimdFloat32 dInv;	
	dInv.setReciprocal(determinant);
	dInv.zeroIfFalse(cmp);

	m_col0.setMul(r0, dInv);
	m_col1.setMul(r1, dInv);
	m_col2.setMul(r2, dInv);
}

//
//	Solves the linear system: (this) * v = b, for v. The matrix is assumed non-singular and symmetric

HK_FORCE_INLINE void hkMatrix3f::solveSymmetric(hkVector4fParameter b, hkVector4f& v)
{
	// Invert matrix
	hkMatrix3f inv;
	inv.setInverseSymmetric(*this);

	// v = inv * b
	inv.multiplyVector(b, v);
}

//
//	Adds the same value to all elements of the diagonal

HK_FORCE_INLINE void hkMatrix3f::addDiagonal(hkSimdFloat32Parameter diag)
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	m_col0.addMul(diag, hkVector4f::getConstant<HK_QUADREAL_1000>());
	m_col1.addMul(diag, hkVector4f::getConstant<HK_QUADREAL_0100>());
	m_col2.addMul(diag, hkVector4f::getConstant<HK_QUADREAL_0010>());
#else
	const hkFloat32 d = diag.getReal();
	m_col0(0) += d;
	m_col1(1) += d;
	m_col2(2) += d;
#endif
}

HK_FORCE_INLINE void hkMatrix3f::multiplyVector (hkVector4fParameter v, hkVector4f& resultOut) const
{
	const hkSimdFloat32 xb = v.getComponent<0>();
	const hkSimdFloat32 yb = v.getComponent<1>();
	const hkSimdFloat32 zb = v.getComponent<2>();

	hkVector4f t0;
	t0.setMul( xb, m_col0 );
	t0.addMul( yb, m_col1 );
	t0.addMul( zb, m_col2 );

	resultOut = t0;
}

//
//	Add the product of a and scale (this += a * scale)

HK_FORCE_INLINE void hkMatrix3f::_addMul( hkSimdFloat32Parameter scale, const hkMatrix3f& a)
{
	m_col0.addMul(scale, a.getColumn<0>());
	m_col1.addMul(scale, a.getColumn<1>());
	m_col2.addMul(scale, a.getColumn<2>());
}

HK_FORCE_INLINE void hkMatrix3f::setZero()
{
	m_col0.setZero();
	m_col1.setZero();
	m_col2.setZero();
}

HK_FORCE_INLINE void hkMatrix3f::setIdentity()
{
	hkMatrix3f* HK_RESTRICT d = this;
	d->m_col0 = hkVector4f::getConstant<HK_QUADREAL_1000>();
	d->m_col1 = hkVector4f::getConstant<HK_QUADREAL_0100>();
	d->m_col2 = hkVector4f::getConstant<HK_QUADREAL_0010>();
}

HK_FORCE_INLINE /*static*/ const hkMatrix3f& HK_CALL hkMatrix3f::getIdentity()
{
	union { const hkQuadFloat32* r; const hkMatrix3f* m; } r2m;
	r2m.r = g_vectorfConstants + HK_QUADREAL_1000;
	return *r2m.m;
}

//
//	Sets this = A - D, where D is interpreted as a diagonal matrix

HK_FORCE_INLINE void hkMatrix3f::_setSubDiag(const hkMatrix3f& A, hkVector4fParameter D)
{
	m_col0.setSubMul(A.getColumn<0>(), hkVector4f::getConstant<HK_QUADREAL_1000>(), D.getComponent<0>());
	m_col1.setSubMul(A.getColumn<1>(), hkVector4f::getConstant<HK_QUADREAL_0100>(), D.getComponent<1>());
	m_col2.setSubMul(A.getColumn<2>(), hkVector4f::getConstant<HK_QUADREAL_0010>(), D.getComponent<2>());
}

//
//	Sets this = A - D, where D is interpreted as a diagonal matrix

HK_FORCE_INLINE void hkMatrix3f::_setSubDiag(const hkMatrix3f& A, hkSimdFloat32Parameter D)
{
	m_col0.setSubMul(A.getColumn<0>(), hkVector4f::getConstant<HK_QUADREAL_1000>(), D);
	m_col1.setSubMul(A.getColumn<1>(), hkVector4f::getConstant<HK_QUADREAL_0100>(), D);
	m_col2.setSubMul(A.getColumn<2>(), hkVector4f::getConstant<HK_QUADREAL_0010>(), D);
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
