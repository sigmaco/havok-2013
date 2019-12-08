/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

template<hkVectorPermutation::Permutation i>
HK_FORCE_INLINE void hk4xVector2f::setPermutation( const hk4xVector2f& v )
{
	m_x.template setPermutation<i>(v.m_x );
	m_y.template setPermutation<i>(v.m_y );
}

template<int i>
HK_FORCE_INLINE void hk4xVector2f::selectVector( const hk4xVector2f& v )
{
	m_x.setBroadcast<i>( v.m_x );
	m_y.setBroadcast<i>( v.m_y );
}

HK_FORCE_INLINE void hk4xVector2f::dotPerpendicular( const hk4xVector2f& a, const hk4xVector2f& b, hkVector4f& dotOut )
{
	dotOut.setMul( a.m_x, b.m_y );
	dotOut.subMul( b.m_x, a.m_y );
}

HK_FORCE_INLINE void hk4xVector2f::dot( const hk4xVector2f& a, const hk4xVector2f& b, hkVector4f& dotOut )
{
	dotOut.setMul( a.m_x, b.m_x );
	dotOut.addMul( a.m_y, b.m_y );
}

HK_FORCE_INLINE void hk4xVector2f::setAddMul( const hk4xVector2f& a, const hk4xVector2f& b, hkVector4fParameter t )
{
	m_x.setAddMul(a.m_x, b.m_x, t );
	m_y.setAddMul(a.m_y, b.m_y, t );
}

HK_FORCE_INLINE void hk4xVector2f::setMul( const hk4xVector2f& a, hkVector4fParameter t )
{
	m_x.setMul(a.m_x, t );
	m_y.setMul(a.m_y, t );
}

HK_FORCE_INLINE void hk4xVector2f::set( hkSimdFloat32Parameter x, hkSimdFloat32Parameter y)
{
	m_x.setAll( x );
	m_y.setAll( y );
}

// HK_FORCE_INLINE void hk4xVector2f::set( const hk4xVector4& v )
// {
// 	hkVector4f v0 = v.getVector<0>();
// 	hkVector4f v1 = v.getVector<1>();
// 	hkVector4f v2 = v.getVector<2>();
// 	hkVector4f v3 = v.getVector<3>();
// 
// 	HK_TRANSPOSE4(v0,v1,v2,v3);
// 
// 	m_x = v0;
// 	m_y = v1;
// }

HK_FORCE_INLINE void hk4xVector2f::set( hkVector4fParameter uAxis, hkVector4fParameter vAxis, hkVector4fParameter offset,
	hkVector4fParameter v0, hkVector4fParameter v1, hkVector4fParameter v2, hkVector4fParameter v3 )
{
	hkVector4f uOffset; uOffset.setAll( offset.dot<3>(uAxis));
	hkVector4f vOffset; vOffset.setAll( offset.dot<3>(vAxis));

	hkVector4f u; hkVector4fUtil::dot3_1vs4(uAxis, v0, v1, v2, v3, u);
	hkVector4f v; hkVector4fUtil::dot3_1vs4(vAxis, v0, v1, v2, v3, v);

	m_x.setSub( u, uOffset );
	m_y.setSub( v, vOffset );
}


HK_FORCE_INLINE void hk4xVector2f::set( hkVector4fParameter uAxis, hkVector4fParameter vAxis,
	hkVector4fParameter v0, hkVector4fParameter v1, hkVector4fParameter v2, hkVector4fParameter v3 )
{
	hkVector4f u; hkVector4fUtil::dot3_1vs4(uAxis, v0, v1, v2, v3, u);
	hkVector4f v; hkVector4fUtil::dot3_1vs4(vAxis, v0, v1, v2, v3, v);

	m_x = u;
	m_y = v;
}

template<hkVector4ComparisonMask::Mask I>
HK_FORCE_INLINE void hk4xVector2f::setSelect( const hk4xVector2f& v0, const hk4xVector2f& v1 )
{
	m_x.setSelect<I>(v0.m_x, v1.m_x);
	m_y.setSelect<I>(v0.m_y, v1.m_y);
}


// HK_FORCE_INLINE void hk4xVector2f::convertToMxVector( hk4xVector4& v ) const
// {
// 	hkVector4f v0 = m_x;
// 	hkVector4f v1 = m_y;
// 	hkVector4f v2; v2.setZero();
// 	hkVector4f v3; v3.setZero();
// 
// 	HK_TRANSPOSE4(v0,v1,v2,v3);
// 
// 	v.setVector<0>(v0);
// 	v.setVector<1>(v1);
// 	v.setVector<2>(v2);
// 	v.setVector<3>(v3);
// }

HK_FORCE_INLINE void hk4xVector2f::getFromArray(const hk4xVector2f* HK_RESTRICT vectors, hkUint32 i, hkSimdFloat32 &xOut, hkSimdFloat32 &yOut)
{
	int arrayIndex = i >> 2;
	int componentIndex = i & 0x3;
	xOut.load<1>(((hkFloat32*) (&vectors[arrayIndex].m_x)) + componentIndex);
	yOut.load<1>(((hkFloat32*) (&vectors[arrayIndex].m_y)) + componentIndex);
}

template<hkMathAccuracyMode A, hkMathNegSqrtMode S>
HK_FORCE_INLINE void hk4xVector2f::setNormalize( const hk4xVector2f& v0 )
{
	hkVector4f len; hk4xVector2f::dot( v0, v0, len );
	hkVector4f invLen; invLen.setSqrtInverse<A, S>( len );
	m_x.setMul( v0.m_x, invLen );
	m_y.setMul( v0.m_y, invLen );
}

HK_FORCE_INLINE hk4xVector2f hk4xVector2f::getFromArray2D(const hk4xVector2f* HK_RESTRICT vectors, hkUint32 i)
{
	int arrayIndex = i >> 2;
	int componentIndex = i & 0x3;

	hkSimdFloat32 x, y;
	x.load<1>(((hkFloat32*) (&vectors[arrayIndex].m_x)) + componentIndex);
	y.load<1>(((hkFloat32*) (&vectors[arrayIndex].m_y)) + componentIndex);

	hk4xVector2f result;
	result.m_x.setAll(x);
	result.m_y.setAll(y);

	return result;
}

HK_FORCE_INLINE void hk4xVector2f::setSelect(hkVector4fComparisonParameter cmp, const hk4xVector2f& a0, const hk4xVector2f& b0)
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
