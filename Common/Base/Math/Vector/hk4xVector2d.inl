/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

template<hkVectorPermutation::Permutation i>
HK_FORCE_INLINE void hk4xVector2d::setPermutation( const hk4xVector2d& v )
{
	m_x.template setPermutation<i>(v.m_x );
	m_y.template setPermutation<i>(v.m_y );
}

template<int i>
HK_FORCE_INLINE void hk4xVector2d::selectVector( const hk4xVector2d& v )
{
	m_x.setBroadcast<i>( v.m_x );
	m_y.setBroadcast<i>( v.m_y );
}

HK_FORCE_INLINE void hk4xVector2d::dotPerpendicular( const hk4xVector2d& a, const hk4xVector2d& b, hkVector4d& dotOut )
{
	dotOut.setMul( a.m_x, b.m_y );
	dotOut.subMul( b.m_x, a.m_y );
}

HK_FORCE_INLINE void hk4xVector2d::dot( const hk4xVector2d& a, const hk4xVector2d& b, hkVector4d& dotOut )
{
	dotOut.setMul( a.m_x, b.m_x );
	dotOut.addMul( a.m_y, b.m_y );
}

HK_FORCE_INLINE void hk4xVector2d::setAddMul( const hk4xVector2d& a, const hk4xVector2d& b, hkVector4dParameter t )
{
	m_x.setAddMul(a.m_x, b.m_x, t );
	m_y.setAddMul(a.m_y, b.m_y, t );
}

HK_FORCE_INLINE void hk4xVector2d::setMul( const hk4xVector2d& a, hkVector4dParameter t )
{
	m_x.setMul(a.m_x, t );
	m_y.setMul(a.m_y, t );
}

HK_FORCE_INLINE void hk4xVector2d::set( hkSimdDouble64Parameter x, hkSimdDouble64Parameter y)
{
	m_x.setAll( x );
	m_y.setAll( y );
}

// HK_FORCE_INLINE void hk4xVector2d::set( const hk4xVector4& v )
// {
// 	hkVector4d v0 = v.getVector<0>();
// 	hkVector4d v1 = v.getVector<1>();
// 	hkVector4d v2 = v.getVector<2>();
// 	hkVector4d v3 = v.getVector<3>();
// 
// 	HK_TRANSPOSE4(v0,v1,v2,v3);
// 
// 	m_x = v0;
// 	m_y = v1;
// }

HK_FORCE_INLINE void hk4xVector2d::set( hkVector4dParameter uAxis, hkVector4dParameter vAxis, hkVector4dParameter offset,
	hkVector4dParameter v0, hkVector4dParameter v1, hkVector4dParameter v2, hkVector4dParameter v3 )
{
	hkVector4d uOffset; uOffset.setAll( offset.dot<3>(uAxis));
	hkVector4d vOffset; vOffset.setAll( offset.dot<3>(vAxis));

	hkVector4d u; hkVector4dUtil::dot3_1vs4(uAxis, v0, v1, v2, v3, u);
	hkVector4d v; hkVector4dUtil::dot3_1vs4(vAxis, v0, v1, v2, v3, v);

	m_x.setSub( u, uOffset );
	m_y.setSub( v, vOffset );
}


HK_FORCE_INLINE void hk4xVector2d::set( hkVector4dParameter uAxis, hkVector4dParameter vAxis,
	hkVector4dParameter v0, hkVector4dParameter v1, hkVector4dParameter v2, hkVector4dParameter v3 )
{
	hkVector4d u; hkVector4dUtil::dot3_1vs4(uAxis, v0, v1, v2, v3, u);
	hkVector4d v; hkVector4dUtil::dot3_1vs4(vAxis, v0, v1, v2, v3, v);

	m_x = u;
	m_y = v;
}

template<hkVector4ComparisonMask::Mask I>
HK_FORCE_INLINE void hk4xVector2d::setSelect( const hk4xVector2d& v0, const hk4xVector2d& v1 )
{
	m_x.setSelect<I>(v0.m_x, v1.m_x);
	m_y.setSelect<I>(v0.m_y, v1.m_y);
}


// HK_FORCE_INLINE void hk4xVector2d::convertToMxVector( hk4xVector4& v ) const
// {
// 	hkVector4d v0 = m_x;
// 	hkVector4d v1 = m_y;
// 	hkVector4d v2; v2.setZero();
// 	hkVector4d v3; v3.setZero();
// 
// 	HK_TRANSPOSE4(v0,v1,v2,v3);
// 
// 	v.setVector<0>(v0);
// 	v.setVector<1>(v1);
// 	v.setVector<2>(v2);
// 	v.setVector<3>(v3);
// }

HK_FORCE_INLINE void hk4xVector2d::getFromArray(const hk4xVector2d* HK_RESTRICT vectors, hkUint32 i, hkSimdDouble64 &xOut, hkSimdDouble64 &yOut)
{
	int arrayIndex = i >> 2;
	int componentIndex = i & 0x3;
	xOut.load<1>(((hkDouble64*) (&vectors[arrayIndex].m_x)) + componentIndex);
	yOut.load<1>(((hkDouble64*) (&vectors[arrayIndex].m_y)) + componentIndex);
}

template<hkMathAccuracyMode A, hkMathNegSqrtMode S>
HK_FORCE_INLINE void hk4xVector2d::setNormalize( const hk4xVector2d& v0 )
{
	hkVector4d len; hk4xVector2d::dot( v0, v0, len );
	hkVector4d invLen; invLen.setSqrtInverse<A, S>( len );
	m_x.setMul( v0.m_x, invLen );
	m_y.setMul( v0.m_y, invLen );
}

HK_FORCE_INLINE hk4xVector2d hk4xVector2d::getFromArray2D(const hk4xVector2d* HK_RESTRICT vectors, hkUint32 i)
{
	int arrayIndex = i >> 2;
	int componentIndex = i & 0x3;

	hkSimdDouble64 x, y;
	x.load<1>(((hkDouble64*) (&vectors[arrayIndex].m_x)) + componentIndex);
	y.load<1>(((hkDouble64*) (&vectors[arrayIndex].m_y)) + componentIndex);

	hk4xVector2d result;
	result.m_x.setAll(x);
	result.m_y.setAll(y);

	return result;
}

HK_FORCE_INLINE void hk4xVector2d::setSelect(hkVector4dComparisonParameter cmp, const hk4xVector2d& a0, const hk4xVector2d& b0)
{
	m_x.setSelect(cmp, a0.m_x, b0.m_x);
	m_y.setSelect(cmp, a0.m_y, b0.m_y);
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
