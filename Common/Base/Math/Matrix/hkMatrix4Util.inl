/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

//
//	Sets this = Transpose(a) * b

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkMatrix4UtilImpl<FT>::_computeTransposeMul(const typename hkRealTypes<FT>::Matrix4& a, const typename hkRealTypes<FT>::Matrix4& b, typename hkRealTypes<FT>::Matrix4& aTb)
{
	typename hkRealTypes<FT>::Vector c0;	hkVector4UtilImpl<FT>::dot4_1vs4(b.template getColumn<0>(), a.template getColumn<0>(), a.template getColumn<1>(), a.template getColumn<2>(), a.template getColumn<3>(), c0);
	typename hkRealTypes<FT>::Vector c1;	hkVector4UtilImpl<FT>::dot4_1vs4(b.template getColumn<1>(), a.template getColumn<0>(), a.template getColumn<1>(), a.template getColumn<2>(), a.template getColumn<3>(), c1);
	typename hkRealTypes<FT>::Vector c2;	hkVector4UtilImpl<FT>::dot4_1vs4(b.template getColumn<2>(), a.template getColumn<0>(), a.template getColumn<1>(), a.template getColumn<2>(), a.template getColumn<3>(), c2);
	typename hkRealTypes<FT>::Vector c3;	hkVector4UtilImpl<FT>::dot4_1vs4(b.template getColumn<3>(), a.template getColumn<0>(), a.template getColumn<1>(), a.template getColumn<2>(), a.template getColumn<3>(), c3);

	aTb.setCols(c0, c1, c2, c3);
}

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkMatrix4UtilImpl<FT>::_setDiagonal( typename hkRealTypes<FT>::VectorParameter vDiagonal, typename hkRealTypes<FT>::Matrix4& mtxOut )
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	typename hkRealTypes<FT>::Vector c0;	c0.setMul(hkRealTypes<FT>::Vector::template getConstant<HK_QUADREAL_1000>(), vDiagonal);
	typename hkRealTypes<FT>::Vector c1;	c1.setMul(hkRealTypes<FT>::Vector::template getConstant<HK_QUADREAL_0100>(), vDiagonal);
	typename hkRealTypes<FT>::Vector c2;	c2.setMul(hkRealTypes<FT>::Vector::template getConstant<HK_QUADREAL_0010>(), vDiagonal);
	typename hkRealTypes<FT>::Vector c3;	c3.setMul(hkRealTypes<FT>::Vector::template getConstant<HK_QUADREAL_0001>(), vDiagonal);
	mtxOut.setCols(c0, c1, c2, c3);
#else
	mtxOut.setZero();
	mtxOut.template setElement<0, 0>(vDiagonal.template getComponent<0>());
	mtxOut.template setElement<1, 1>(vDiagonal.template getComponent<1>());
	mtxOut.template setElement<2, 2>(vDiagonal.template getComponent<2>());
	mtxOut.template setElement<3, 3>(vDiagonal.template getComponent<3>());
#endif
}

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkMatrix4UtilImpl<FT>::_setDiagonal(typename hkRealTypes<FT>::ScalarParameter diag, typename hkRealTypes<FT>::Matrix4& mtxOut)
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	typename hkRealTypes<FT>::Vector c0;	c0.setMul(hkRealTypes<FT>::Vector::template getConstant<HK_QUADREAL_1000>(), diag);
	typename hkRealTypes<FT>::Vector c1;	c1.setMul(hkRealTypes<FT>::Vector::template getConstant<HK_QUADREAL_0100>(), diag);
	typename hkRealTypes<FT>::Vector c2;	c2.setMul(hkRealTypes<FT>::Vector::template getConstant<HK_QUADREAL_0010>(), diag);
	typename hkRealTypes<FT>::Vector c3;	c3.setMul(hkRealTypes<FT>::Vector::template getConstant<HK_QUADREAL_0001>(), diag);
	mtxOut.setCols(c0, c1, c2, c3);
#else
	mtxOut.setZero();
	mtxOut.template setElement<0, 0>(diag);
	mtxOut.template setElement<1, 1>(diag);
	mtxOut.template setElement<2, 2>(diag);
	mtxOut.template setElement<3, 3>(diag);
#endif
}

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkMatrix4UtilImpl<FT>::_setDiagonal3x3( typename hkRealTypes<FT>::VectorParameter vDiagonal, typename hkRealTypes<FT>::Matrix4& mtxOut )
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	typename hkRealTypes<FT>::Vector c0;	c0.setMul(hkRealTypes<FT>::Vector::template getConstant<HK_QUADREAL_1000>(), vDiagonal);
	typename hkRealTypes<FT>::Vector c1;	c1.setMul(hkRealTypes<FT>::Vector::template getConstant<HK_QUADREAL_0100>(), vDiagonal);
	typename hkRealTypes<FT>::Vector c2;	c2.setMul(hkRealTypes<FT>::Vector::template getConstant<HK_QUADREAL_0010>(), vDiagonal);
	mtxOut.setCols(c0, c1, c2, hkRealTypes<FT>::Vector::template getConstant<HK_QUADREAL_0001>());
#else
	mtxOut.setZero();
	mtxOut.template setElement<0, 0>(vDiagonal.template getComponent<0>());
	mtxOut.template setElement<1, 1>(vDiagonal.template getComponent<1>());
	mtxOut.template setElement<2, 2>(vDiagonal.template getComponent<2>());
	mtxOut.template setElement<3, 3>(hkRealTypes<FT>::Scalar::template getConstant<HK_QUADREAL_1>());
#endif
}

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkMatrix4UtilImpl<FT>::_setDiagonal3x3(typename hkRealTypes<FT>::ScalarParameter diag, typename hkRealTypes<FT>::Matrix4& mtxOut)
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	typename hkRealTypes<FT>::Vector c0;	c0.setMul(hkRealTypes<FT>::Vector::template getConstant<HK_QUADREAL_1000>(), diag);
	typename hkRealTypes<FT>::Vector c1;	c1.setMul(hkRealTypes<FT>::Vector::template getConstant<HK_QUADREAL_0100>(), diag);
	typename hkRealTypes<FT>::Vector c2;	c2.setMul(hkRealTypes<FT>::Vector::template getConstant<HK_QUADREAL_0010>(), diag);
	mtxOut.setCols(c0, c1, c2, hkRealTypes<FT>::Vector::template getConstant<HK_QUADREAL_0001>());
#else
	mtxOut.setZero();
	mtxOut.template setElement<0, 0>(diag);
	mtxOut.template setElement<1, 1>(diag);
	mtxOut.template setElement<2, 2>(diag);
	mtxOut.template setElement<3, 3>(hkRealTypes<FT>::Scalar::template getConstant<HK_QUADREAL_1>());
#endif
}

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkMatrix4UtilImpl<FT>::_setMulInverseAffine ( const typename hkRealTypes<FT>::Matrix4& a, const typename hkRealTypes<FT>::Matrix4& b, typename hkRealTypes<FT>::Matrix4& out )
{
	typename hkRealTypes<FT>::Matrix4 binverse = b;
	const typename hkRealTypes<FT>::Scalar eps = hkRealTypes<FT>::Scalar::template getConstant<HK_QUADREAL_EPS>();
	__hkMatrix4UtilAlgo::invert( binverse, eps );
	out.setMulAffine( a, binverse );
}

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkMatrix4UtilImpl<FT>::_setMulInverse ( const typename hkRealTypes<FT>::Matrix4& a, const typename hkRealTypes<FT>::Matrix4& b, typename hkRealTypes<FT>::Matrix4& out )
{
	typename hkRealTypes<FT>::Matrix4 binverse = b;
	const typename hkRealTypes<FT>::Scalar eps = hkRealTypes<FT>::Scalar::template getConstant<HK_QUADREAL_EPS>();
	__hkMatrix4UtilAlgo::invert( binverse, eps );
	out.setMul( a, binverse );
}

template <typename FT>
HK_FORCE_INLINE hkResult HK_CALL hkMatrix4UtilImpl<FT>::invert(typename hkRealTypes<FT>::Matrix4& m, typename hkRealTypes<FT>::ScalarParameter epsilon)
{
	return __hkMatrix4UtilAlgo::invert(m,epsilon);
}

template <typename FT>
HK_FORCE_INLINE hkResult HK_CALL hkMatrix4UtilImpl<FT>::setInverse(const typename hkRealTypes<FT>::Matrix4& m, typename hkRealTypes<FT>::Matrix4& out, typename hkRealTypes<FT>::ScalarParameter epsilon)
{
	return __hkMatrix4UtilAlgo::setInverse(m,out,epsilon);
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
