/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

HK_FORCE_INLINE hkVector4f& hkTransformf::getColumn(int x)
{
	return m_rotation.getColumn(x);
}

HK_FORCE_INLINE const hkVector4f& hkTransformf::getColumn(int x) const
{
	return m_rotation.getColumn(x);
}

template <int I>
HK_FORCE_INLINE const hkVector4f& hkTransformf::getColumn() const
{
	return m_rotation.getColumn<I>();
}

template <int I>
HK_FORCE_INLINE void hkTransformf::setColumn(hkVector4fParameter v)
{
	m_rotation.setColumn<I>(v);
}

HK_FORCE_INLINE void hkTransformf::setTranslation(hkVector4fParameter t)
{
	m_translation = t;
}

HK_FORCE_INLINE hkRotationf& hkTransformf::getRotation()
{
	return m_rotation;
}

HK_FORCE_INLINE const hkRotationf& hkTransformf::getRotation() const
{
	return m_rotation;
}

HK_FORCE_INLINE void hkTransformf::setRotation(const hkRotationf& rotation)
{	
	m_rotation = rotation;
}

HK_FORCE_INLINE void hkTransformf::setRotation(hkQuaternionfParameter quatRotation)
{
	m_rotation.set(quatRotation);
}

#ifndef HK_DISABLE_MATH_CONSTRUCTORS
HK_FORCE_INLINE hkTransformf::hkTransformf(const hkTransformf& t)
{
	const hkVector4f r0 = t.getColumn<0>();
	const hkVector4f r1 = t.getColumn<1>();
	const hkVector4f r2 = t.getColumn<2>();
	const hkVector4f r3 = t.getColumn<3>();
	setColumn<0>(r0);
	setColumn<1>(r1);
	setColumn<2>(r2);
	setColumn<3>(r3);
}

HK_FORCE_INLINE hkTransformf::hkTransformf(hkQuaternionfParameter q, hkVector4fParameter t)
	:	m_translation(t)
{
	m_rotation.set(q);
}


HK_FORCE_INLINE hkTransformf::hkTransformf(const hkRotationf& r, hkVector4fParameter t)
	:	m_rotation(r),
		m_translation(t)
{
}
#endif

HK_FORCE_INLINE hkFloat32& hkTransformf::operator() (int r, int c)
{
	return m_rotation(r,c);
}

HK_FORCE_INLINE const hkFloat32& hkTransformf::operator() (int r, int c) const
{
	return m_rotation(r,c);
}

template <int ROW, int COL>
HK_FORCE_INLINE const hkSimdFloat32 hkTransformf::getElement() const
{
	return m_rotation.getElement<ROW,COL>();
}

template <int ROW, int COL>
HK_FORCE_INLINE void hkTransformf::setElement(hkSimdFloat32Parameter s)
{
	m_rotation.setElement<ROW,COL>(s);
}

HK_FORCE_INLINE void hkTransformf::set(hkQuaternionfParameter q, hkVector4fParameter t)
{
	m_rotation.set(q);
	m_translation = t;
}

HK_FORCE_INLINE void hkTransformf::set(const hkRotationf& r, hkVector4fParameter t)
{
	m_rotation = r;
	m_translation = t;
}

HK_FORCE_INLINE /*static*/ const hkTransformf& HK_CALL hkTransformf::getIdentity()
{
	union { const hkQuadFloat32* r; const hkTransformf* t; } r2t;
	r2t.r = g_vectorfConstants + HK_QUADREAL_1000;
	return *r2t.t;
}

HK_FORCE_INLINE void hkTransformf::setIdentity()
{
	m_rotation.setIdentity();
	m_translation.setZero();
}

HK_FORCE_INLINE hkVector4f& hkTransformf::getTranslation()
{ 
	return m_translation; 
}

HK_FORCE_INLINE const hkVector4f& hkTransformf::getTranslation() const 
{ 
	return m_translation; 
}

HK_FORCE_INLINE void hkTransformf::_setInverse( const hkTransformf &t )
{
	m_rotation._setTranspose( t.getRotation() ); 

	hkVector4f tr;	tr.setNeg<4>(t.getTranslation()); 
	m_translation._setRotatedDir( m_rotation, tr);
}



HK_FORCE_INLINE void hkTransformf::_setMulInverseMul( const hkTransformf& bTa, const hkTransformf &bTc )
{
	int i = 3;
	do
	{
		getColumn(i)._setRotatedInverseDir( bTa.getRotation(), bTc.getColumn(i) );
	} while( --i >= 0 );
	hkVector4f h; h.setSub(bTc.m_translation, bTa.m_translation );
	m_translation._setRotatedInverseDir( bTa.m_rotation, h);
}

HK_FORCE_INLINE void hkTransformf::setRows4( hkVector4fParameter r0, hkVector4fParameter r1, hkVector4fParameter r2, hkVector4fParameter r3)
{
	hkVector4f c0 = r0;
	hkVector4f c1 = r1;
	hkVector4f c2 = r2;
	hkVector4f c3 = r3;

	HK_TRANSPOSE4f(c0, c1, c2, c3);

	setColumn<0>(c0);
	setColumn<1>(c1);
	setColumn<2>(c2);
	setColumn<3>(c3);
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
