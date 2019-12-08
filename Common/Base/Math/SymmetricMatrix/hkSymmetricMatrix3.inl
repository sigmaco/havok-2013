/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

//
//	Multiplies the matrix with the given scalar

template <typename FT>
HK_FORCE_INLINE void hkSymmetricMatrix3Impl<FT>::setMul(typename hkRealTypes<FT>::ScalarParameter scale, const hkSymmetricMatrix3Impl<FT>& tensor)
{
	m_diag.setMul(tensor.m_diag, scale);
	m_offDiag.setMul(tensor.m_offDiag, scale);
}

//
//	Sets this *= scale

template <typename FT>
HK_FORCE_INLINE void hkSymmetricMatrix3Impl<FT>::mul(typename hkRealTypes<FT>::ScalarParameter scale)
{
	m_diag.mul(scale);
	m_offDiag.mul(scale);
}

//
//	Sets this = ta + tb

template <typename FT>
HK_FORCE_INLINE void hkSymmetricMatrix3Impl<FT>::setAdd(const hkSymmetricMatrix3Impl<FT>& ta, const hkSymmetricMatrix3Impl<FT>& tb)
{
	m_diag.setAdd(ta.m_diag, tb.m_diag);
	m_offDiag.setAdd(ta.m_offDiag, tb.m_offDiag);
}

//
//	Sets this += ta

template <typename FT>
HK_FORCE_INLINE void hkSymmetricMatrix3Impl<FT>::add(const hkSymmetricMatrix3Impl<FT>& ta)
{
	m_diag.add(ta.m_diag);
	m_offDiag.add(ta.m_offDiag);
}

//
//	Sets this = ta - tb

template <typename FT>
HK_FORCE_INLINE void hkSymmetricMatrix3Impl<FT>::setSub(const hkSymmetricMatrix3Impl<FT>& ta, const hkSymmetricMatrix3Impl<FT>& tb)
{
	m_diag.setSub(ta.m_diag, tb.m_diag);
	m_offDiag.setSub(ta.m_offDiag, tb.m_offDiag);
}

//
//	Sets this -= ta

template <typename FT>
HK_FORCE_INLINE void hkSymmetricMatrix3Impl<FT>::sub(const hkSymmetricMatrix3Impl<FT>& ta)
{
	m_diag.sub(ta.m_diag);
	m_offDiag.sub(ta.m_offDiag);
}

//
//	Sets this -= u * ta 

template <typename FT>
HK_FORCE_INLINE void hkSymmetricMatrix3Impl<FT>::subMul(typename hkRealTypes<FT>::ScalarParameter u, const hkSymmetricMatrix3Impl<FT>& ta)
{
	m_diag.subMul(u, ta.m_diag);
	m_offDiag.subMul(u, ta.m_offDiag);
}

//
//	Sets this += Diag(a), where Diag(a) is a diagonal matrix with diagonal elements a.

template <typename FT>
HK_FORCE_INLINE void hkSymmetricMatrix3Impl<FT>::addDiag(typename hkRealTypes<FT>::VectorParameter diagA)
{
	m_diag.add(diagA);
}

template <typename FT>
HK_FORCE_INLINE void hkSymmetricMatrix3Impl<FT>::addDiag(typename hkRealTypes<FT>::ScalarParameter diagA)
{
	typename hkRealTypes<FT>::Vector vDiag;
	vDiag.setAll(diagA);
	addDiag(vDiag);
}

//
//	Sets this tensor from the given matrix m. The matrix is assumed to be symmetric

template <typename FT>
HK_FORCE_INLINE void hkSymmetricMatrix3Impl<FT>::setFromSymmetricMatrix(const typename hkRealTypes<FT>::Matrix3& m)
{
	{
		m_diag.template setSelect<hkVector4ComparisonMask::MASK_X>(m.template getColumn<0>(), hkRealTypes<FT>::Vector::template getConstant<HK_QUADREAL_0>());
		m_diag.template setSelect<hkVector4ComparisonMask::MASK_Y>(m.template getColumn<1>(), m_diag);
		m_diag.template setSelect<hkVector4ComparisonMask::MASK_Z>(m.template getColumn<2>(), m_diag);
	}
	{
		typename hkRealTypes<FT>::Vector od; od.template setPermutation<hkVectorPermutation::XYXY>(m.template getColumn<2>()); // [m02, m12, m02]
		m_offDiag.template setSelect<hkVector4ComparisonMask::MASK_X>(m.template getColumn<1>(), od);                          // [m01, m12, m02]
		m_offDiag.template zeroComponent<3>();
	}
}

//
//	Gets the 3x3 matrix equivalent to this tensor

template <typename FT>
HK_FORCE_INLINE void hkSymmetricMatrix3Impl<FT>::getMatrix(typename hkRealTypes<FT>::Matrix3& m) const
{
	const typename hkRealTypes<FT>::Vector d	= m_diag;		// [m00, m11, m22]
	const typename hkRealTypes<FT>::Vector od	= m_offDiag;	// [m01, m12, m02]

	typename hkRealTypes<FT>::Vector c0;	c0.template setPermutation<hkVectorPermutation::YXZW>(od);	// [*, m01, m02]
	typename hkRealTypes<FT>::Vector c1;	c1.template setPermutation<hkVectorPermutation::XZYW>(od);	// [m01, *, m12]
	typename hkRealTypes<FT>::Vector c2;	c2.template setPermutation<hkVectorPermutation::ZYZW>(od);	// [m02, m12, *]

	c0.template setSelect<hkVector4ComparisonMask::MASK_X>(d, c0);	// [m00, m01, m02]
	c1.template setSelect<hkVector4ComparisonMask::MASK_Y>(d, c1);	// [m01, m11, m12]
	c2.template setSelect<hkVector4ComparisonMask::MASK_Z>(d, c2);	// [m02, m12, m22]
	m.setCols(c0, c1, c2);
}

//
//	Sets this = Diagonal(v)

template <typename FT>
HK_FORCE_INLINE void hkSymmetricMatrix3Impl<FT>::setDiagonal(typename hkRealTypes<FT>::VectorParameter v)
{
	m_offDiag.setZero();
	m_diag = v;
}

template <typename FT>
HK_FORCE_INLINE void hkSymmetricMatrix3Impl<FT>::setDiagonal(typename hkRealTypes<FT>::ScalarParameter v)
{
	m_offDiag.setZero();
	m_diag.setAll(v);
}

//
//	Sets all entries to zero

template <typename FT>
HK_FORCE_INLINE void hkSymmetricMatrix3Impl<FT>::setZero()
{
	m_diag.setZero();
	m_offDiag.setZero();
}

//
//	Sets this = min(ta, tb) component-wise.

template <typename FT>
HK_FORCE_INLINE void hkSymmetricMatrix3Impl<FT>::setMin(const hkSymmetricMatrix3Impl<FT>& ta, const hkSymmetricMatrix3Impl<FT>& tb)
{
	m_diag.setMin(ta.m_diag, tb.m_diag);
	m_offDiag.setMin(ta.m_offDiag, tb.m_offDiag);
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
