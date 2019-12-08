/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

//
//	Sets this matrix to be the reflection of matrix D through matrix P, i.e. this = Transpose(P) * A * P
//	Matrix D is assumed diagonal.

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkMatrix3UtilImpl<FT>::_computeReflectedDiagonal(const typename hkRealTypes<FT>::Matrix3& P, typename hkRealTypes<FT>::VectorParameter D, typename hkRealTypes<FT>::Matrix3& reflectionOut)
{
	// Resulting matrix is symmetric and element(i, j) = dot3(P(*, i) * P(*, j), D)
	// Get columns of p
	const typename hkRealTypes<FT>::Vector p0 = P.template getColumn<0>();
	const typename hkRealTypes<FT>::Vector p1 = P.template getColumn<1>();
	const typename hkRealTypes<FT>::Vector p2 = P.template getColumn<2>();

	// Compute dots
	typename hkRealTypes<FT>::Vector p00;	p00.setMul(p0, p0);
	typename hkRealTypes<FT>::Vector p01;	p01.setMul(p0, p1);
	typename hkRealTypes<FT>::Vector p02;	p02.setMul(p0, p2);
	typename hkRealTypes<FT>::Vector p11;	p11.setMul(p1, p1);
	typename hkRealTypes<FT>::Vector p12;	p12.setMul(p1, p2);
	typename hkRealTypes<FT>::Vector p22;	p22.setMul(p2, p2);

	typename hkRealTypes<FT>::Vector dotsA;	hkVector4UtilImpl<FT>::dot3_1vs4(D, p00, p01, p02, p11, dotsA);	// (m00, m01, m02, m11)
	typename hkRealTypes<FT>::Vector dotsB;	hkVector4UtilImpl<FT>::dot3_1vs4(D, p02, p12, p22, p11, dotsB);	// (m02, m12, m22, m11)

	const typename hkRealTypes<FT>::Vector mCol0 = dotsA;
	const typename hkRealTypes<FT>::Vector mCol2 = dotsB;
	typename hkRealTypes<FT>::Vector mCol1;

#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	// dotsA = (m01, m11, m02, m00)
	dotsA.template setPermutation<hkVectorPermutation::YWZX>(dotsA);

	// dotsB = (m12, m12, m12, m12)
	dotsB.template broadcast<1>();

	mCol1.template setSelect<hkVector4ComparisonMask::MASK_XY>(dotsA, dotsB);
#else
	mCol1.set(dotsA(1), dotsA(3), dotsB(1), dotsB(1));
#endif

	reflectionOut.setCols(mCol0, mCol1, mCol2);
}

//
//	Sets this = Q * D * Inverse(Q), where D is interpreted as a diagonal matrix.

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkMatrix3UtilImpl<FT>::_changeBasis(typename hkRealTypes<FT>::QuaternionParameter Q, typename hkRealTypes<FT>::VectorParameter D, typename hkRealTypes<FT>::Matrix3& matrixOut)
{
	typename hkRealTypes<FT>::Rotation R;
	hkVector4UtilImpl<FT>::convertQuaternionToRotation(Q, R);

	_changeBasis(R, D, matrixOut);
}

//
//	Changes the basis of the the given diagonal matrix by the rotation matrix t. (this = R * D * Transpose(R))

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkMatrix3UtilImpl<FT>::_changeBasis(const typename hkRealTypes<FT>::Rotation& R, typename hkRealTypes<FT>::VectorParameter D, typename hkRealTypes<FT>::Matrix3& matrixOut)
{
	// Get cols
	typename hkRealTypes<FT>::Vector l0	= R.template getColumn<0>();		// [m00, m10, m20]
	typename hkRealTypes<FT>::Vector l1	= R.template getColumn<1>();		// [m01, m11, m21]
	typename hkRealTypes<FT>::Vector l2	= R.template getColumn<2>();		// [m02, m12, m22]

	typename hkRealTypes<FT>::Vector diag;
	{
		typename hkRealTypes<FT>::Vector t0;	t0.setMul(l0, l0);	t0.mul(D.template getComponent<0>());	// [d0 * m00 * m00, d0 * m10 * m10, d0 * m20 * m20]
		typename hkRealTypes<FT>::Vector t1;	t1.setMul(l1, l1);	t1.mul(D.template getComponent<1>());	// [d1 * m01 * m01, d1 * m11 * m11, d1 * m21 * m21]
		typename hkRealTypes<FT>::Vector t2;	t2.setMul(l2, l2);	t2.mul(D.template getComponent<2>());	// [d2 * m02 * m02, d2 * m12 * m12, d2 * m22 * m22]

		// In the end, diag is:
		//	[d0 * m00 * m00 + d1 * m01 * m01 + d2 * m02 * m02,
		//		d0 * m10 * m10 + d1 * m11 * m11 + d2 * m12 * m12,
		//			d0 * m20 * m20 + d1 * m21 * m21 + d2 * m22 * m22] = [a00, a11, a22]
		t0.add(t1);
		diag.setAdd(t0, t2);	
	}

	typename hkRealTypes<FT>::Vector offDiag;
	{
		hkVector4UtilImpl<FT>::transpose(l0, l1, l2);				// Transpose to get the lines
		typename hkRealTypes<FT>::Vector l01;	l01.setMul(l0, l1);		// [m00 * m10, m01 * m11, m02 * m12]
		typename hkRealTypes<FT>::Vector l02;	l02.setMul(l0, l2);		// [m00 * m20, m01 * m21, m02 * m22]
		typename hkRealTypes<FT>::Vector l12;	l12.setMul(l1, l2);		// [m10 * m20, m11 * m21, m12 * m22]

		// In the end, offDiag is:
		//	[d0 * m00 * m10 + d1 * m01 * m11 + d2 * m02 * m12, 
		//		d0 * m00 * m20 + d1 * m01 * m21 + d2 * m02 * m22,
		//			d0 * m10 * m20 + d1 * m11 * m21 + d2 * m12 * m22] = [a01, a02, a12]
		hkVector4UtilImpl<FT>::dot3_1vs3(D, l01, l02, l12, offDiag);
	}

	// Store results
	{
		typename hkRealTypes<FT>::Vector tmp0;	tmp0.template setPermutation<hkVectorPermutation::WXYZ>(offDiag);	// [*, a01, a02, a12]
		typename hkRealTypes<FT>::Vector tmp1;	tmp1.template setPermutation<hkVectorPermutation::YZWX>(offDiag);	// [a02, a12, *, a01]

		typename hkRealTypes<FT>::Vector mCol0, mCol1, mCol2;
		mCol0.template setSelect<hkVector4ComparisonMask::MASK_X>(diag, tmp0);		// [a00, a01, a02]
		mCol1.template setSelect<hkVector4ComparisonMask::MASK_XZ>(offDiag, diag);	// [a01, a11, a12]
		mCol2.template setSelect<hkVector4ComparisonMask::MASK_Z>(diag, tmp1);		// [a02, a12, a22]
		matrixOut.setCols(mCol0, mCol1, mCol2);
	}
}

//
//	Sets this = Identity * dot(v, v) - OuterProduct(v, v). The matrix is used to displace inertia tensors
//	by v from the center of mass.

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkMatrix3UtilImpl<FT>::_computeInertiaDisplacement(typename hkRealTypes<FT>::VectorParameter v, typename hkRealTypes<FT>::Matrix3& inertiaOut)
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	// Compute dots
	typename hkRealTypes<FT>::Vector vvx;	vvx.setZero();	vvx.template setComponent<0>(v.template dot<3>(v));	// [xx + yy + zz, 0, 0]
	typename hkRealTypes<FT>::Vector vvy;	vvy.template setPermutation<hkVectorPermutation::YXZW>(vvx);		// [0, xx + yy + zz, 0]
	typename hkRealTypes<FT>::Vector vvz;	vvz.template setPermutation<hkVectorPermutation::YZXW>(vvx);		// [0, 0, xx + yy + zz]

	// Subtract 
	typename hkRealTypes<FT>::Vector mCol0, mCol1, mCol2;
	mCol0.setSubMul(vvx, v, v.template getComponent<0>());	// [yy + zz, -xy, -xz]
	mCol1.setSubMul(vvy, v, v.template getComponent<1>());	// [-xy, xx + zz, -yz]
	mCol2.setSubMul(vvz, v, v.template getComponent<2>());	// [-xz, -yz, xx + yy]
	inertiaOut.setCols(mCol0, mCol1, mCol2);
#else
	typename hkRealTypes<FT>::Vector vv; vv.setMul(v,v);
	typename hkRealTypes<FT>::Pod v01 = -(v(0)*v(1));
	typename hkRealTypes<FT>::Pod v02 = -(v(0)*v(2));
	typename hkRealTypes<FT>::Pod v12 = -(v(1)*v(2));

	typename hkRealTypes<FT>::Vector mCol0, mCol1, mCol2;
	mCol0.set(vv(1)+vv(2), v01, v02);
	mCol1.set(v01, vv(0)+vv(2), v12);
	mCol2.set(v02, v12, vv(0)+vv(1));
	inertiaOut.setCols(mCol0, mCol1, mCol2);
#endif
}

//
//	Returns the diagonal of the given matrix.

template <typename FT>
HK_FORCE_INLINE	void HK_CALL hkMatrix3UtilImpl<FT>::_getDiagonal(const typename hkRealTypes<FT>::Matrix3& matrixIn, typename hkRealTypes<FT>::Vector& diagonalOut)
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	diagonalOut = matrixIn.template getColumn<0>();
	diagonalOut.template setSelect<hkVector4ComparisonMask::MASK_Y>(matrixIn.template getColumn<1>(), diagonalOut);
	diagonalOut.template setSelect<hkVector4ComparisonMask::MASK_Z>(matrixIn.template getColumn<2>(), diagonalOut);
#else
	diagonalOut.set(matrixIn(0,0),matrixIn(1,1),matrixIn(2,2),0);
#endif
}

//
//	Returns the off-diagonal elements of this matrix. The matrix is assumed to be symmetric. The returned vector is
//	[m01, m02, m12, 0]

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkMatrix3UtilImpl<FT>::_getSymmetricOffDiagonal(const typename hkRealTypes<FT>::Matrix3& matrixIn, typename hkRealTypes<FT>::Vector& offDiagonalOut)
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	typename hkRealTypes<FT>::Vector od; od.template setPermutation<hkVectorPermutation::XXYY>(matrixIn.template getColumn<2>()); // [m02, m02, m12]
	offDiagonalOut.template setSelect<hkVector4ComparisonMask::MASK_X>(matrixIn.template getColumn<1>(), od);                     // [m01, m02, m12]
	offDiagonalOut.template zeroComponent<3>();
#else
	offDiagonalOut.set(matrixIn(0,1),matrixIn(0,2),matrixIn(1,2),0);
#endif
}

//
//	Returns the maximum element

template <typename FT>
HK_FORCE_INLINE const typename hkRealTypes<FT>::Scalar HK_CALL hkMatrix3UtilImpl<FT>::_computeMaxAbsElement(const typename hkRealTypes<FT>::Matrix3& matrixIn)
{
	typename hkRealTypes<FT>::Vector vMax;
	vMax.setMax(matrixIn.template getColumn<0>(), matrixIn.template getColumn<1>());
	vMax.setMax(matrixIn.template getColumn<2>(), vMax);
	vMax.setAbs(vMax);
	return vMax.template horizontalMax<3>();
}

//
//	Computes matrixOut = matrixIn * hat(v), whereh hat(v) is the skew-symmetric matrix of v

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkMatrix3UtilImpl<FT>::_computeCrossProduct(const typename hkRealTypes<FT>::Matrix3& matrixIn, typename hkRealTypes<FT>::VectorParameter v, typename hkRealTypes<FT>::Matrix3& matrixOut)
{
	const typename hkRealTypes<FT>::Scalar x = v.template getComponent<0>();
	const typename hkRealTypes<FT>::Scalar y = v.template getComponent<1>();
	const typename hkRealTypes<FT>::Scalar z = v.template getComponent<2>();

	// Get source columns
	const typename hkRealTypes<FT>::Vector sc0 = matrixIn.template getColumn<0>();
	const typename hkRealTypes<FT>::Vector sc1 = matrixIn.template getColumn<1>();
	const typename hkRealTypes<FT>::Vector sc2 = matrixIn.template getColumn<2>();

	// Compute destination columns
	typename hkRealTypes<FT>::Vector dc0;	dc0.setMul(sc1, z);	dc0.subMul(sc2, y);
	typename hkRealTypes<FT>::Vector dc1;	dc1.setMul(sc2, x);	dc1.subMul(sc0, z);
	typename hkRealTypes<FT>::Vector dc2;	dc2.setMul(sc0, y);	dc2.subMul(sc1, x);
	matrixOut.setCols(dc0, dc1, dc2);
}

//
//	Sets this = Transpose(a) * b.

template <typename FT>
HK_FORCE_INLINE void hkMatrix3UtilImpl<FT>::_computeTransposeMul(const typename hkRealTypes<FT>::Matrix3& a, const typename hkRealTypes<FT>::Matrix3& b, typename hkRealTypes<FT>::Matrix3& aTb)
{
	typename hkRealTypes<FT>::Vector c0, c1, c2;
	hkVector4UtilImpl<FT>::dot3_3vs3(a.template getColumn<0>(), b.template getColumn<0>(), a.template getColumn<1>(), b.template getColumn<0>(), a.template getColumn<2>(), b.template getColumn<0>(), c0);
	hkVector4UtilImpl<FT>::dot3_3vs3(a.template getColumn<0>(), b.template getColumn<1>(), a.template getColumn<1>(), b.template getColumn<1>(), a.template getColumn<2>(), b.template getColumn<1>(), c1);
	hkVector4UtilImpl<FT>::dot3_3vs3(a.template getColumn<0>(), b.template getColumn<2>(), a.template getColumn<1>(), b.template getColumn<2>(), a.template getColumn<2>(), b.template getColumn<2>(), c2);

	aTb.setCols(c0, c1, c2);
}

//
//	Sets this matrix as the cross product between the given vector and each of the given matrix's columns.
//	Specifically, it sets mtxOut.column(i) = cross(v, src.column(i))

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkMatrix3UtilImpl<FT>::_computeCrossMul(typename hkRealTypes<FT>::VectorParameter v, const typename hkRealTypes<FT>::Matrix3& src, typename hkRealTypes<FT>::Matrix3& mtxOut)
{
	// Get source columns
	const typename hkRealTypes<FT>::Vector sc0 = src.template getColumn<0>();
	const typename hkRealTypes<FT>::Vector sc1 = src.template getColumn<1>();
	const typename hkRealTypes<FT>::Vector sc2 = src.template getColumn<2>();

	// Target columns
	typename hkRealTypes<FT>::Vector tc0, tc1, tc2;

#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	// First part
	{
		typename hkRealTypes<FT>::Vector shufV;	// (vy, vz, vx, *)
		shufV.template setPermutation<hkVectorPermutation::YZXW>(v);

		typename hkRealTypes<FT>::Vector shufC0;	// (c0z, c0x, c0y)
		shufC0.template setPermutation<hkVectorPermutation::ZXYW>(sc0);

		typename hkRealTypes<FT>::Vector shufC1;	// (c1z, c1x, c1y)
		shufC1.template setPermutation<hkVectorPermutation::ZXYW>(sc1);

		typename hkRealTypes<FT>::Vector shufC2;	// (c2z, c2x, c2y)
		shufC2.template setPermutation<hkVectorPermutation::ZXYW>(sc2);

		tc0.setMul(shufV, shufC0);	// (vy * c0z, vz * c0x, vx * c0y)
		tc1.setMul(shufV, shufC1);	// (vy * c1z, vz * c1x, vx * c1y)
		tc2.setMul(shufV, shufC2);	// (vy * c2z, vz * c2x, vx * c2y)
	}

	// Second part
	{
		typename hkRealTypes<FT>::Vector shufV;	// (vz, vx, vy, *)
		shufV.template setPermutation<hkVectorPermutation::ZXYW>(v);

		typename hkRealTypes<FT>::Vector shufC0;	// (c0y, c0z, c0x)
		shufC0.template setPermutation<hkVectorPermutation::YZXW>(sc0);

		typename hkRealTypes<FT>::Vector shufC1;	// (c1y, c1z, c1x)
		shufC1.template setPermutation<hkVectorPermutation::YZXW>(sc1);

		typename hkRealTypes<FT>::Vector shufC2;	// (c2y, c2z, c2x)
		shufC2.template setPermutation<hkVectorPermutation::YZXW>(sc2);

		tc0.subMul(shufV, shufC0);	// (vy * c0z - vz * c0y, vz * c0x - vx * c0z, vx * c0y - vy * c0x)
		tc1.subMul(shufV, shufC1);	// (vy * c1z - vz * c1y, vz * c1x - vx * c1z, vx * c1y - vy * c1x)
		tc2.subMul(shufV, shufC2);	// (vy * c2z - vz * c2y, vz * c2x - vx * c2z, vx * c2y - vy * c2x)
	}
#else
	tc0.set( v(1) * sc0(2) - v(2) * sc0(1), v(2) * sc0(0) - v(0) * sc0(2), v(0) * sc0(1) - v(1) * sc0(0) );
	tc1.set( v(1) * sc1(2) - v(2) * sc1(1), v(2) * sc1(0) - v(0) * sc1(2), v(0) * sc1(1) - v(1) * sc1(0) );
	tc2.set( v(1) * sc2(2) - v(2) * sc2(1), v(2) * sc2(0) - v(0) * sc2(2), v(0) * sc2(1) - v(1) * sc2(0) );
#endif

	// Store
	mtxOut.setCols(tc0, tc1, tc2);
}

//
//	Checks if matrixIn is equal to the identity matrix within an epsilon.

template <typename FT>
HK_FORCE_INLINE hkBool32 HK_CALL hkMatrix3UtilImpl<FT>::_isApproximatelyIdentity(const typename hkRealTypes<FT>::Matrix3& matrixIn, typename hkRealTypes<FT>::ScalarParameter eps)
{
	// non_euclidean, manhattan based
	typename hkRealTypes<FT>::Vector t0,t1,t2;
	t0.setSub(matrixIn.template getColumn<0>(), hkRealTypes<FT>::Vector::template getConstant<HK_QUADREAL_1000>());
	t0.setAbs( t0 );
	t1.setSub(matrixIn.template getColumn<1>(), hkRealTypes<FT>::Vector::template getConstant<HK_QUADREAL_0100>());
	t1.setAbs( t1 );
	t2.setSub(matrixIn.template getColumn<2>(), hkRealTypes<FT>::Vector::template getConstant<HK_QUADREAL_0010>());
	t2.setAbs( t2 );

	typename hkRealTypes<FT>::Vector epsilon_v;
	epsilon_v.setAll(eps);

	typename hkRealTypes<FT>::Comparison cmp0 = t0.less( epsilon_v );
	typename hkRealTypes<FT>::Comparison cmp1 = t1.less( epsilon_v );
	typename hkRealTypes<FT>::Comparison cmp2 = t2.less( epsilon_v );

	typename hkRealTypes<FT>::Comparison all; 
	all.setAnd(cmp0,cmp1);
	all.setAnd(cmp2,all);

	return all.template allAreSet<hkVector4ComparisonMask::MASK_XYZ>();
}

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkMatrix3UtilImpl<FT>::_setDiagonal( typename hkRealTypes<FT>::Pod m00, typename hkRealTypes<FT>::Pod m11, typename hkRealTypes<FT>::Pod m22, typename hkRealTypes<FT>::Matrix3& mtxOut )
{
	mtxOut.setZero();
	mtxOut(0,0) = m00;
	mtxOut(1,1) = m11;
	mtxOut(2,2) = m22;
}

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkMatrix3UtilImpl<FT>::_setDiagonal( typename hkRealTypes<FT>::ScalarParameter m00, typename hkRealTypes<FT>::ScalarParameter m11, typename hkRealTypes<FT>::ScalarParameter m22, typename hkRealTypes<FT>::Matrix3& mtxOut )
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	typename hkRealTypes<FT>::Vector c0;	c0.setMul(hkRealTypes<FT>::Vector::template getConstant<HK_QUADREAL_1000>(), m00);
	typename hkRealTypes<FT>::Vector c1;	c1.setMul(hkRealTypes<FT>::Vector::template getConstant<HK_QUADREAL_0100>(), m11);
	typename hkRealTypes<FT>::Vector c2;	c2.setMul(hkRealTypes<FT>::Vector::template getConstant<HK_QUADREAL_0010>(), m22);
	mtxOut.setCols(c0, c1, c2);
#else
	mtxOut.setZero();
	mtxOut.template setElement<0, 0>(m00);
	mtxOut.template setElement<1, 1>(m11);
	mtxOut.template setElement<2, 2>(m22);
#endif
}

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkMatrix3UtilImpl<FT>::_setDiagonal( typename hkRealTypes<FT>::VectorParameter vDiagonal, typename hkRealTypes<FT>::Matrix3& mtxOut )
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	typename hkRealTypes<FT>::Vector c0;	c0.setMul(hkRealTypes<FT>::Vector::template getConstant<HK_QUADREAL_1000>(), vDiagonal);
	typename hkRealTypes<FT>::Vector c1;	c1.setMul(hkRealTypes<FT>::Vector::template getConstant<HK_QUADREAL_0100>(), vDiagonal);
	typename hkRealTypes<FT>::Vector c2;	c2.setMul(hkRealTypes<FT>::Vector::template getConstant<HK_QUADREAL_0010>(), vDiagonal);
	mtxOut.setCols(c0, c1, c2);
#else
	mtxOut.setZero();
	mtxOut.template setElement<0, 0>(vDiagonal.template getComponent<0>());
	mtxOut.template setElement<1, 1>(vDiagonal.template getComponent<1>());
	mtxOut.template setElement<2, 2>(vDiagonal.template getComponent<2>());
#endif
}

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkMatrix3UtilImpl<FT>::_setDiagonal(typename hkRealTypes<FT>::ScalarParameter diag, typename hkRealTypes<FT>::Matrix3& mtxOut)
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	typename hkRealTypes<FT>::Vector c0;	c0.setMul(hkRealTypes<FT>::Vector::template getConstant<HK_QUADREAL_1000>(), diag);
	typename hkRealTypes<FT>::Vector c1;	c1.setMul(hkRealTypes<FT>::Vector::template getConstant<HK_QUADREAL_0100>(), diag);
	typename hkRealTypes<FT>::Vector c2;	c2.setMul(hkRealTypes<FT>::Vector::template getConstant<HK_QUADREAL_0010>(), diag);
	mtxOut.setCols(c0, c1, c2);
#else
	mtxOut.setZero();
	mtxOut.template setElement<0, 0>(diag);
	mtxOut.template setElement<1, 1>(diag);
	mtxOut.template setElement<2, 2>(diag);
#endif
}

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkMatrix3UtilImpl<FT>::_setDiagonalOnly( typename hkRealTypes<FT>::VectorParameter vDiagonal, typename hkRealTypes<FT>::Matrix3& mtxOut )
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	typename hkRealTypes<FT>::Vector c0;	c0.template setSelect<hkVector4ComparisonMask::MASK_X>(vDiagonal, mtxOut.template getColumn<0>());
	typename hkRealTypes<FT>::Vector c1;	c1.template setSelect<hkVector4ComparisonMask::MASK_Y>(vDiagonal, mtxOut.template getColumn<1>());
	typename hkRealTypes<FT>::Vector c2;	c2.template setSelect<hkVector4ComparisonMask::MASK_Z>(vDiagonal, mtxOut.template getColumn<2>());
	mtxOut.setCols(c0, c1, c2);
#else
	mtxOut.template setElement<0, 0>(vDiagonal.template getComponent<0>());
	mtxOut.template setElement<1, 1>(vDiagonal.template getComponent<1>());
	mtxOut.template setElement<2, 2>(vDiagonal.template getComponent<2>());
#endif
}

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkMatrix3UtilImpl<FT>::_setDiagonalOnly(typename hkRealTypes<FT>::ScalarParameter diag, typename hkRealTypes<FT>::Matrix3& mtxOut)
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	typename hkRealTypes<FT>::Vector diagV; diagV.setAll(diag);
	typename hkRealTypes<FT>::Vector c0;	c0.template setSelect<hkVector4ComparisonMask::MASK_X>(diagV, mtxOut.template getColumn<0>());
	typename hkRealTypes<FT>::Vector c1;	c1.template setSelect<hkVector4ComparisonMask::MASK_Y>(diagV, mtxOut.template getColumn<1>());
	typename hkRealTypes<FT>::Vector c2;	c2.template setSelect<hkVector4ComparisonMask::MASK_Z>(diagV, mtxOut.template getColumn<2>());
	mtxOut.setCols(c0, c1, c2);
#else
	mtxOut.template setElement<0, 0>(diag);
	mtxOut.template setElement<1, 1>(diag);
	mtxOut.template setElement<2, 2>(diag);
#endif
}

//
//	Computes mtxOut to be the product of a and the inverse of b. (mtxOut = a * b^-1)

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkMatrix3UtilImpl<FT>::_computeMulInverse(const typename hkRealTypes<FT>::Matrix3& mtxA, const typename hkRealTypes<FT>::Rotation& mtxB, typename hkRealTypes<FT>::Matrix3& mtxOut)
{
	typename hkRealTypes<FT>::Rotation invB;	invB._setTranspose(mtxB);
	typename hkRealTypes<FT>::Matrix3 ret;		hkVector4UtilImpl<FT>::rotatePoints(mtxA, &invB.template getColumn<0>(), 3, &ret.template getColumn<0>());
	mtxOut = ret;
}

//
//	Computes the outer product of the given vectors, i.e. mtxOut = u * Transpose[v]

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkMatrix3UtilImpl<FT>::_computeOuterProduct(typename hkRealTypes<FT>::VectorParameter u, typename hkRealTypes<FT>::VectorParameter v, typename hkRealTypes<FT>::Matrix3& mtxOut)
{
	// u = [ux, uy, uz], v = [vx, vy, vz]
	typename hkRealTypes<FT>::Vector c0;	c0.setMul(v.template getComponent<0>(), u);	// [ux * vx, uy * vx, uz * vx]
	typename hkRealTypes<FT>::Vector c1;	c1.setMul(v.template getComponent<1>(), u);	// [ux * vy, uy * vy, uz * vy]
	typename hkRealTypes<FT>::Vector c2;	c2.setMul(v.template getComponent<2>(), u);	// [ux * vz, uy * vz, uz * vz]
	mtxOut.setCols(c0, c1, c2);
}

//
//	Computes the displacement given by the two vectors rA and rB, i.e. mtxOut = Hat[rA] * Hat[rB]

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkMatrix3UtilImpl<FT>::_computeDisplacement(typename hkRealTypes<FT>::VectorParameter rA, typename hkRealTypes<FT>::VectorParameter rB, typename hkRealTypes<FT>::Matrix3& mtxOut)
{
	// We need to compute the following matrix:
	//	{ {	-aY bY - aZ bZ,	aY bX,				aZ bX			},
	//	  {	aX bY,			-aX bX - aZ bZ,		aZ bY			},
	//	  {	aX bZ,			aY bZ,				-aX bX - aY bY	} }

	const typename hkRealTypes<FT>::Scalar d	= rA.template dot<3>(rB);											// (aX bx + aY bY + aZ bZ)
	typename hkRealTypes<FT>::Vector c0;		c0.setMul(rA.template getComponent<0>(), rB);						// [aX bX, aX bY, aX bZ]
	c0.subMul(hkRealTypes<FT>::Vector::template getConstant<HK_QUADREAL_1000>(), d);								// [-aY bY - aZ bZ, aX bY, aX bZ]
	typename hkRealTypes<FT>::Vector c1;		c1.setMul(rA.template getComponent<1>(), rB);						// [aY bX, aY bY, aY bZ]
	c1.subMul(hkRealTypes<FT>::Vector::template getConstant<HK_QUADREAL_0100>(), d);								// [aY bX, -aX bx - aZ bZ, aY bZ]
	typename hkRealTypes<FT>::Vector c2;		c2.setMul(rA.template getComponent<2>(), rB);						// [aZ bX, aZ bY, aZ bZ]
	c2.subMul(hkRealTypes<FT>::Vector::template getConstant<HK_QUADREAL_0010>(), d);								// [aZ bX, aZ bY, -aX bx - aY bY]

	mtxOut.setCols(c0, c1, c2);
}

//
//	Sets this matrix to be the reflection of matrix D through matrix P, i.e., this = Transpose(P) * A * P.
//	Matrix D is assumed diagonal.

template <typename FT>
void HK_CALL hkMatrix3UtilImpl<FT>::computeReflectedDiagonal(const typename hkRealTypes<FT>::Matrix3& P, typename hkRealTypes<FT>::VectorParameter D, typename hkRealTypes<FT>::Matrix3& reflectionOut)
{
	_computeReflectedDiagonal(P, D, reflectionOut);
}

//
//	Sets matrixOut = Q * D * Inverse(Q), where D is interpreted as a diagonal matrix.

template <typename FT>
void HK_CALL hkMatrix3UtilImpl<FT>::changeBasis(typename hkRealTypes<FT>::QuaternionParameter Q, typename hkRealTypes<FT>::VectorParameter D, typename hkRealTypes<FT>::Matrix3& matrixOut)
{
	_changeBasis(Q, D, matrixOut);
}

//
//	Sets matrixOut = R * D * Transpose(R), where D is interpreted as a diagonal matrix.

template <typename FT>
void HK_CALL hkMatrix3UtilImpl<FT>::changeBasis(const typename hkRealTypes<FT>::Rotation& R, typename hkRealTypes<FT>::VectorParameter D, typename hkRealTypes<FT>::Matrix3& matrixOut)
{
	_changeBasis(R, D, matrixOut);
}

//
//	Sets this = Identity * dot(v, v) - OuterProduct(v, v). The matrix is used to displace inertia tensors
//	by v from the center of mass.

template <typename FT>
void HK_CALL hkMatrix3UtilImpl<FT>::computeInertiaDisplacement(typename hkRealTypes<FT>::VectorParameter v, typename hkRealTypes<FT>::Matrix3& inertiaOut)
{
	_computeInertiaDisplacement(v, inertiaOut);
}

//
//	Returns the diagonal of the given matrix.

template <typename FT>
void HK_CALL hkMatrix3UtilImpl<FT>::getDiagonal(const typename hkRealTypes<FT>::Matrix3& matrixIn, typename hkRealTypes<FT>::Vector& diagonalOut)
{
	_getDiagonal(matrixIn, diagonalOut);
}

//
//	Returns the off-diagonal elements of this matrix. The matrix is assumed to be symmetric. The returned vector is
//	[m01, m02, m12, 0]

template <typename FT>
void HK_CALL hkMatrix3UtilImpl<FT>::getSymmetricOffDiagonal(const typename hkRealTypes<FT>::Matrix3& matrixIn, typename hkRealTypes<FT>::Vector& offDiagonalOut)
{
	_getSymmetricOffDiagonal(matrixIn, offDiagonalOut);
}

//
//	Returns the absolute maximum element

template <typename FT>
const typename hkRealTypes<FT>::Scalar HK_CALL hkMatrix3UtilImpl<FT>::computeMaxAbsElement(const typename hkRealTypes<FT>::Matrix3& matrixIn)
{
	return _computeMaxAbsElement(matrixIn);
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
