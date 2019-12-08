/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */


//
//	Sets mtxOut = outer product of the given vector, i.e [xx, yy, zz], [xy, yz, zx]

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkSymmetricMatrixUtilImpl<FT>::_computeOuterProduct(typename hkRealTypes<FT>::VectorParameter vXYZ, typename hkRealTypes<FT>::SymmetricMatrix3& mtxOut)
{
	typename hkRealTypes<FT>::Vector vYZX;	vYZX.template setPermutation<hkVectorPermutation::YZXW>(vXYZ);
	mtxOut.m_diag.setMul(vXYZ, vXYZ);		// [xx, yy, zz]
	mtxOut.m_offDiag.setMul(vXYZ, vYZX);	// [xy, yz, zx]
}

//
//	Projects the tensor on the given direction, i.e. computes Transpose(d) * mtx * d

template <typename FT>
HK_FORCE_INLINE const typename hkRealTypes<FT>::Scalar HK_CALL hkSymmetricMatrixUtilImpl<FT>::_computeProjection(const typename hkRealTypes<FT>::SymmetricMatrix3& mtx, typename hkRealTypes<FT>::VectorParameter vD)
{
	typename hkRealTypes<FT>::SymmetricMatrix3 d;			// d =	[d_xx, d_yy, d_zz]
	_computeOuterProduct(vD, d);							//		[d_xy, d_yz, d_zx]

	typename hkRealTypes<FT>::Vector diag;		diag.setMul(d.m_diag, d.m_diag);				// [m_xx * d_xx, m_yy * d_yy, m_zz * d_zz]
	typename hkRealTypes<FT>::Vector offDiag;	offDiag.setMul(d.m_offDiag, d.m_offDiag);		// [m_xy * d_xy, m_yz * d_yz, m_zx * d_zx]

	diag.addMul(hkRealTypes<FT>::Scalar::template getConstant<HK_QUADREAL_2>(), offDiag);	// [m_xx * d_xx + 2 * m_xy * d_xy, m_yy * d_yy + 2 * m_yz * d_yz, m_zz * d_zz + 2 * m_zx * d_zx]
	return diag.template horizontalAdd<3>();												// [m_xx * d_xx + 2 * m_xy * d_xy + m_yy * d_yy + 2 * m_yz * d_yz + m_zz * d_zz + 2 * m_zx * d_zx]
}

//
//	Sets mtxOut = Transpose(R) * Diag(a) * R, where Diag(a) is a diagonal matrix with diagonal elements a.

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkSymmetricMatrixUtilImpl<FT>::_computeInverseBasisTransform(const typename hkRealTypes<FT>::Matrix3& R, typename hkRealTypes<FT>::VectorParameter vD, typename hkRealTypes<FT>::SymmetricMatrix3& mtxOut)
{
	// Get columns
	const typename hkRealTypes<FT>::Vector c0 = R.template getColumn<0>();
	const typename hkRealTypes<FT>::Vector c1 = R.template getColumn<1>();
	const typename hkRealTypes<FT>::Vector c2 = R.template getColumn<2>();

	typename hkRealTypes<FT>::Vector dc0;	dc0.setMul(c0, vD);
	typename hkRealTypes<FT>::Vector dc1;	dc1.setMul(c1, vD);
	typename hkRealTypes<FT>::Vector dc2;	dc2.setMul(c2, vD);

	hkVector4UtilImpl<FT>::dot3_3vs3(dc0, c0, dc1, c1, dc2, c2, mtxOut.m_diag);
	hkVector4UtilImpl<FT>::dot3_3vs3(dc0, c1, dc1, c2, dc2, c0, mtxOut.m_offDiag);
}

//
//	Returns the element with maximum absolute value in the matrix

template <typename FT>
HK_FORCE_INLINE const typename hkRealTypes<FT>::Scalar HK_CALL hkSymmetricMatrixUtilImpl<FT>::_getMaxAbsElement(const typename hkRealTypes<FT>::SymmetricMatrix3& t)
{
	typename hkRealTypes<FT>::Vector d;	d.setAbs(t.m_diag);
	typename hkRealTypes<FT>::Vector od;	od.setAbs(t.m_offDiag);
	d.setMax(d, od);
	return d.template horizontalMax<3>();
}

//
//	Sets inverseOut = Inverse(t).

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkSymmetricMatrixUtilImpl<FT>::_computeInverse(const typename hkRealTypes<FT>::SymmetricMatrix3& origT, typename hkRealTypes<FT>::SymmetricMatrix3& inverseOut)
{
	// We need to scale the elements to reduce precision errors!
	const typename hkRealTypes<FT>::Scalar pivot		= _getMaxAbsElement(origT);
	typename hkRealTypes<FT>::Scalar invPivot;		invPivot.template setReciprocal<HK_ACC_FULL, HK_DIV_SET_ZERO>(pivot);

	typename hkRealTypes<FT>::Vector d_xyz;		d_xyz.setMul(invPivot, origT.m_diag);								// [m00, m11, m22]
	typename hkRealTypes<FT>::Vector od_xyz;	od_xyz.setMul(invPivot, origT.m_offDiag);							// [m01, m12, m20]
	typename hkRealTypes<FT>::Vector d_yzx;		d_yzx.template setPermutation<hkVectorPermutation::YZXW>(d_xyz);	// [m11, m22, m00]
	typename hkRealTypes<FT>::Vector d_zxy;		d_zxy.template setPermutation<hkVectorPermutation::ZXYW>(d_xyz);	// [m22, m00, m11]
	typename hkRealTypes<FT>::Vector diag;		diag.setMul(d_yzx, d_zxy);											// [m11 * m22, m22 * m00, m00 * m11]
	typename hkRealTypes<FT>::Vector det;		det.setMul(d_xyz, diag);											// [m00 * m11 * m22, *]

	typename hkRealTypes<FT>::Vector od_yzx;		od_yzx.template setPermutation<hkVectorPermutation::YZXW>(od_xyz);	// [m12, m20, m01]
	typename hkRealTypes<FT>::Vector od_zxy;		od_zxy.template setPermutation<hkVectorPermutation::ZXYW>(od_xyz);	// [m20, m01, m12]
	typename hkRealTypes<FT>::Vector od_yzx_Sq;	od_yzx_Sq.setMul(od_yzx, od_yzx);										// [m12 * m12, m20 * m20, m01 * m01]
	diag.sub(od_yzx_Sq);																								// [m11 * m22 - m12 * m12, m22 * m00 - m20 * m20, m00 * m11 - m01 * m01]

	typename hkRealTypes<FT>::Vector offDiag;		offDiag.setMul(od_yzx, od_zxy);				// [m12 * m20, m20 * m01, m01 * m12]
	typename hkRealTypes<FT>::Vector offDiagProd;	offDiagProd.setMul(od_xyz, offDiag);		// [m01 * m12 * m20, *]
	det.addMul(hkRealTypes<FT>::Scalar::template getConstant<HK_QUADREAL_2>(), offDiagProd);	// [m00 * m11 * m22 + 2 * m01 * m12 * m20, *]
	offDiag.subMul(d_zxy, od_xyz);																// [m12 * m20 - m22 * m01, m20 * m01 - m00 * m12, m01 * m12 - m11 * m20]

	// Compute and invert determinant
	const typename hkRealTypes<FT>::Scalar determinant	= det.template getComponent<0>() - d_xyz.template dot<3>(od_yzx_Sq);	
														// m00 * m11 * m22 + 2 * m01 * m12 * m20 - m00 * m12 * m12 - m11 * m20 * m20 - m22 * m01 * m01
	typename hkRealTypes<FT>::Scalar absDet;				absDet.setAbs(determinant);
	typename hkRealTypes<FT>::Scalar invDet;				invDet.setReciprocal(determinant);
	invDet.zeroIfFalse(absDet.greater(hkRealTypes<FT>::Scalar::template getConstant<HK_QUADREAL_EPS>()));
	invDet.mul(invPivot);

	// Store inverse tensor
	inverseOut.m_diag.setMul(diag, invDet);
	inverseOut.m_offDiag.setMul(offDiag, invDet);
}

//
//	Computes vOut = t * vIn

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkSymmetricMatrixUtilImpl<FT>::_multiply(const typename hkRealTypes<FT>::SymmetricMatrix3& t, typename hkRealTypes<FT>::VectorParameter vIn, typename hkRealTypes<FT>::Vector& vOut)
{
	typename hkRealTypes<FT>::Vector tmp0;		tmp0.setMul(t.m_diag, vIn);		// [m00 * x, m11 * y, m22 * z]
	typename hkRealTypes<FT>::Vector tmp1;		tmp1.setMul(t.m_offDiag, vIn);	// [m01 * x, m12 * y, m20 * z]
	typename hkRealTypes<FT>::Vector tmp2;		
	tmp2.template setPermutation<hkVectorPermutation::YZXW>(vIn);				// [y, z, x, w]
	tmp1.template setPermutation<hkVectorPermutation::ZXYW>(tmp1);				// [m20 * z, m01 * x, m12 * y]

	tmp0.addMul(t.m_offDiag, tmp2);												// [m00 * x + m01 * y, m11 * y + m12 * z, m22 * z + m20 * x]
	vOut.setAdd(tmp0, tmp1);													// [m00 * x + m01 * y + m20 * z, m01 * x + m11 * y + m12 * z, m20 * x + m12 * y + m22 * z]
}

//
//	Solves the linear system: mtx * v = b, for v.

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkSymmetricMatrixUtilImpl<FT>::_solve(const typename hkRealTypes<FT>::SymmetricMatrix3& mtx, typename hkRealTypes<FT>::VectorParameter b, typename hkRealTypes<FT>::Vector& solutionOut)
{
	typename hkRealTypes<FT>::SymmetricMatrix3 inv;
	_computeInverse(mtx, inv);
	_multiply(inv, b, solutionOut);
}

//
//	Solves the linear system: mtx * v = b for v, where |v| < vMax per component.
//	The problem is a LCP and the returned solution is an approximation computed via Jacobi iterations.
//	The number of iterations is given as a template parameter

template <typename FT>
template <int NIter>
HK_FORCE_INLINE void HK_CALL hkSymmetricMatrixUtilImpl<FT>::_solve(const typename hkRealTypes<FT>::SymmetricMatrix3& mtx, typename hkRealTypes<FT>::VectorParameter b, typename hkRealTypes<FT>::VectorParameter vMax, typename hkRealTypes<FT>::Vector& solutionOut)
{
	// Compute the unbounded solution
	typename hkRealTypes<FT>::Vector x;	_solve(mtx, b, x);
	typename hkRealTypes<FT>::Vector vMin;	vMin.template setNeg<3>(vMax);

	// Applying the limit makes the problem a LCP. Run a few Jacobi iterations
	// to compute an approximate solution that obeys the limits.
	typename hkRealTypes<FT>::Vector invD;	invD.template setReciprocal<HK_ACC_23_BIT, HK_DIV_SET_ZERO>(mtx.m_diag);
	for (int iter = NIter - 1; iter >= 0; iter--)
	{
		// Compute new solution
		typename hkRealTypes<FT>::Vector tmp1;		tmp1.setMul(mtx.m_offDiag, x);	// [m01 * x, m12 * y, m20 * z]
		typename hkRealTypes<FT>::Vector tmp2;		
		tmp2.template setPermutation<hkVectorPermutation::YZXW>(x);					// [y, z, x, w]
		tmp1.template setPermutation<hkVectorPermutation::ZXYW>(tmp1);				// [m20 * z, m01 * x, m12 * y]
		x.setAddMul(tmp1, mtx.m_offDiag, tmp2);										// [m01 * y + m20 * z, m01 * x + m12 * z, m20 * x + m12 * y]
		x.setSub(b, x);
		x.mul(invD);

		// Clamp to interval
		x.setMin(x, vMax);
		x.setMax(x, vMin);
	}

	solutionOut = x;
}

//
//	Computes tOut = rot * ta * Transpose[rot]

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkSymmetricMatrixUtilImpl<FT>::_computeBasisTransform(const typename hkRealTypes<FT>::Rotation& rot, const typename hkRealTypes<FT>::SymmetricMatrix3& ta, typename hkRealTypes<FT>::SymmetricMatrix3& tOut)
{
	// Transpose matrix R
	// c0 = [r00, r01, r02]
	// c1 = [r10, r11, r12]
	// c2 = [r20, r21, r22]
	typename hkRealTypes<FT>::Vector cr0, cr1, cr2;
	rot.getCols(cr0, cr1, cr2);
	hkVector4UtilImpl<FT>::transpose(cr0, cr1, cr2);

	typename hkRealTypes<FT>::Vector dc0, dc1, dc2;
	{
		dc0.setMul(ta.m_diag, cr0);		// [m00 * r00, m11 * r01, m22 * r02]
		dc1.setMul(ta.m_diag, cr1);		// [m00 * r10, m11 * r11, m22 * r12]
		dc2.setMul(ta.m_diag, cr2);		// [m00 * r20, m11 * r21, m22 * r22]
		typename hkRealTypes<FT>::Vector od = ta.m_offDiag;	// [m01, m12, m02]

		typename hkRealTypes<FT>::Vector c0;	c0.template setPermutation<hkVectorPermutation::YZXW>(cr0);	// [r01, r02, r00]
		typename hkRealTypes<FT>::Vector c1;	c1.template setPermutation<hkVectorPermutation::YZXW>(cr1);	// [r11, r12, r10]
		typename hkRealTypes<FT>::Vector c2;	c2.template setPermutation<hkVectorPermutation::YZXW>(cr2);	// [r21, r22, r20]
		dc0.addMul(od, c0);													// [m00 * r00 + m01 * r01, m11 * r01 + m12 * r02, m22 * r02 + m02 * r00]
		dc1.addMul(od, c1);													// [m00 * r10 + m01 * r11, m11 * r11 + m12 * r12, m22 * r12 + m02 * r10]
		dc2.addMul(od, c2);													// [m00 * r20 + m01 * r21, m11 * r21 + m12 * r22, m22 * r22 + m02 * r20]

		od.template setPermutation<hkVectorPermutation::ZXYW>(od);					// [m02, m01, m12]

		c0.template setPermutation<hkVectorPermutation::YZXW>(c0);					// [r02, r00, r01]
		c1.template setPermutation<hkVectorPermutation::YZXW>(c1);					// [r12, r10, r11]
		c2.template setPermutation<hkVectorPermutation::YZXW>(c2);					// [r22, r20, r21]
		dc0.addMul(od, c0);													// [m00 * r00 + m01 * r01 + m02 * r02, m01 * r00 + m11 * r01 + m12 * r02, m02 * r00 + m12 * r01 + m22 * r02]
		dc1.addMul(od, c1);													// [m00 * r10 + m01 * r11 + m02 * r12, m01 * r10 + m11 * r11 + m12 * r12, m02 * r10 + m12 * r11 + m22 * r12]
		dc2.addMul(od, c2);													// [m00 * r20 + m01 * r21 + m02 * r22, m01 * r20 + m11 * r21 + m12 * r22, m02 * r20 + m12 * r21 + m22 * r22]
	}

	// We need to compute the dots between dc0, dc1, dc2 and the rows of matrix R
	hkVector4UtilImpl<FT>::dot3_3vs3(cr0, dc0, cr1, dc1, cr2, dc2, tOut.m_diag);
	hkVector4UtilImpl<FT>::dot3_3vs3(cr0, dc1, cr1, dc2, cr2, dc0, tOut.m_offDiag);
}

//
//	Computes tOut = rot * ta * Transpose[rot]

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkSymmetricMatrixUtilImpl<FT>::_computeBasisTransform(const typename hkRealTypes<FT>::Rotation& rot, typename hkRealTypes<FT>::VectorParameter vDiag, typename hkRealTypes<FT>::SymmetricMatrix3& tOut)
{
	// Transpose matrix R
	// c0 = [r00, r01, r02]
	// c1 = [r10, r11, r12]
	// c2 = [r20, r21, r22]
	typename hkRealTypes<FT>::Vector cr0, cr1, cr2;
	rot.getCols(cr0, cr1, cr2);
	hkVector4UtilImpl<FT>::transpose(cr0, cr1, cr2);

	typename hkRealTypes<FT>::Vector dc0;	dc0.setMul(vDiag, cr0);		// [m00 * r00, m11 * r01, m22 * r02]
	typename hkRealTypes<FT>::Vector dc1;	dc1.setMul(vDiag, cr1);		// [m00 * r10, m11 * r11, m22 * r12]
	typename hkRealTypes<FT>::Vector dc2;	dc2.setMul(vDiag, cr2);		// [m00 * r20, m11 * r21, m22 * r22]

	// We need to compute the dots between dc0, dc1, dc2 and the rows of matrix R
	hkVector4UtilImpl<FT>::dot3_3vs3(cr0, dc0, cr1, dc1, cr2, dc2, tOut.m_diag);
	hkVector4UtilImpl<FT>::dot3_3vs3(cr0, dc1, cr1, dc2, cr2, dc0, tOut.m_offDiag);
}

//
//	Computes tOut = rot * ta * Transpose[rot]

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkSymmetricMatrixUtilImpl<FT>::_computeBasisTransform(typename hkRealTypes<FT>::QuaternionParameter rot, const typename hkRealTypes<FT>::SymmetricMatrix3& ta, typename hkRealTypes<FT>::SymmetricMatrix3& tOut)
{
	typename hkRealTypes<FT>::Rotation R;
	hkVector4UtilImpl<FT>::convertQuaternionToRotation(rot, R);
	_computeBasisTransform(R, ta, tOut);
}

//
//	Computes tOut = rot * ta * Transpose[rot]

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkSymmetricMatrixUtilImpl<FT>::_computeBasisTransform(typename hkRealTypes<FT>::QuaternionParameter rot, typename hkRealTypes<FT>::VectorParameter vDiag, typename hkRealTypes<FT>::SymmetricMatrix3& tOut)
{
	typename hkRealTypes<FT>::Rotation R;
	hkVector4UtilImpl<FT>::convertQuaternionToRotation(rot, R);
	_computeBasisTransform(R, vDiag, tOut);
}

//
//	Computes tOut = Hat[r] * ta * Hat[r]

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkSymmetricMatrixUtilImpl<FT>::_computeDisplacedTensor(typename hkRealTypes<FT>::VectorParameter r, const typename hkRealTypes<FT>::SymmetricMatrix3& ta, typename hkRealTypes<FT>::SymmetricMatrix3& tOut)
{
	const typename hkRealTypes<FT>::Vector xyz		= r;														// [x, y, z]
	const typename hkRealTypes<FT>::Vector d_xyz	= ta.m_diag;												// [m00, m11, m22]
	const typename hkRealTypes<FT>::Vector od_xyz	= ta.m_offDiag;												// [m01, m12, m02]

	typename hkRealTypes<FT>::Vector yzx;			yzx.template setPermutation<hkVectorPermutation::YZXW>(xyz);			// [y, z, x]
	typename hkRealTypes<FT>::Vector zxy;			zxy.template setPermutation<hkVectorPermutation::ZXYW>(xyz);			// [z, x, y]
	typename hkRealTypes<FT>::Vector d_yzx;		d_yzx.template setPermutation<hkVectorPermutation::YZXW>(d_xyz);		// [m11, m22, m00]
	typename hkRealTypes<FT>::Vector d_zxy;		d_zxy.template setPermutation<hkVectorPermutation::ZXYW>(d_xyz);		// [m22, m00, m11]
	typename hkRealTypes<FT>::Vector od_yzx;		od_yzx.template setPermutation<hkVectorPermutation::YZXW>(od_xyz);	// [m12, m02, m01]
	typename hkRealTypes<FT>::Vector od_zxy;		od_zxy.template setPermutation<hkVectorPermutation::ZXYW>(od_xyz);	// [m02, m01, m12]

	d_zxy.mul(yzx);			// [y * m22, z * m00, x * m11]
	d_yzx.mul(zxy);			// [z * m11, x * m22, y * m00]

	typename hkRealTypes<FT>::Vector v;
	v.setMul(od_xyz, zxy);		// [z * m01, x * m12, y * m02]
	v.subMul(od_zxy, yzx);		// [z * m01 - y * m02, x * m12 - z * m01, y * m02 - x * m12]
	v.subMul(od_yzx, xyz);		// [z * m01 - y * m02 - x * m12, x * m12 - z * m01 - y * m02, y * m02 - x * m12 - z * m01]
	v.mul(zxy);					// [z^2 * m01 - yz * m02 - xz * m12, x^2 * m12 - xz * m01 - xy * m02, y^2 * m02 - xy * m12 - yz * m01]
	tOut.m_offDiag.setAddMul(v, xyz, d_zxy);	// [z^2 * m01 + xy * m22 - yz * m02 - xz * m12,
												//	x^2 * m12 + yz * m00 - xz * m01 - xy * m02,
												//	y^2 * m02 + xz * m11 - xy * m12 - yz * m01]

	v.setMul(od_yzx, yzx);		// [y * m12, z * m02, x * m01]
	d_yzx.setSub(v, d_yzx);		// [y * m12 - z * m11, z * m02 - x * m22, x * m01 - y * m00]
	d_yzx.mul(zxy);				// [yz * m12 - z^2 * m11, xz * m02 - x^2 * m22, xy * m01 - y^2 * m00]

	v.setMul(od_yzx, zxy);						// [z * m12, x * m02, y * m01]
	d_zxy.setSub(v, d_zxy);						// [z * m12 - y * m22, x * m02 - z * m00, y * m01 - x * m11]
	tOut.m_diag.setAddMul(d_yzx, d_zxy, yzx);	// [2yz * m12 - y^2 * m22 - z^2 * m11,
												//	2xz * m02 - z^2 * m00 - x^2 * m22,
												//	2xy * m01 - x^2 * m11 - y^2 * m00]
}

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkSymmetricMatrixUtilImpl<FT>::_computeDisplacedTensor(typename hkRealTypes<FT>::VectorParameter r, typename hkRealTypes<FT>::VectorParameter d_xyz, typename hkRealTypes<FT>::SymmetricMatrix3& tOut)
{
	const typename hkRealTypes<FT>::Vector xyz		= r;															// [x, y, z]
	typename hkRealTypes<FT>::Vector yzx;			yzx.template setPermutation<hkVectorPermutation::YZXW>(xyz);	// [y, z, x]
	typename hkRealTypes<FT>::Vector zxy;			zxy.template setPermutation<hkVectorPermutation::ZXYW>(xyz);	// [z, x, y]
	typename hkRealTypes<FT>::Vector d_yzx;		d_yzx.template setPermutation<hkVectorPermutation::YZXW>(d_xyz);	// [m11, m22, m00]
	typename hkRealTypes<FT>::Vector d_zxy;		d_zxy.template setPermutation<hkVectorPermutation::ZXYW>(d_xyz);	// [m22, m00, m11]

	d_zxy.mul(yzx);							// [y * m22, z * m00, x * m11]
	d_yzx.mul(zxy);							// [z * m11, x * m22, y * m00]
	tOut.m_offDiag.setMul(xyz, d_zxy);		// [xy * m22, yz * m00, xz * m11]

	d_yzx.mul(zxy);							// [z^2 * m11, x^2 * m22, y^2 * m00]
	d_yzx.addMul(d_zxy, yzx);				// [z^2 * m11 + y^2 * m22, x^2 * m22 + z^2 * m00, y^2 * m00 + x^2 * m11]
	tOut.m_diag.template setNeg<3>(d_yzx);	// [-y^2 * m22 - z^2 * m11, -z^2 * m00 - x^2 * m22, - x^2 * m11 - y^2 * m00]
}

//
//	Computes tOut = Hat[r] * Hat[r] = {{-y^2 - z^2, xy, xz}, {xy, -x^2 - z^2, yz}, {xz, yz, -x^2 - y^2}}
//		diag	= [-yy -zz, -xx -zz, -xx -yy]
//		offDiag	= [xy, yz, xz]

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkSymmetricMatrixUtilImpl<FT>::_computeDisplacement(typename hkRealTypes<FT>::VectorParameter r, typename hkRealTypes<FT>::SymmetricMatrix3& tOut)
{
	typename hkRealTypes<FT>::Vector tmp;		tmp.template setPermutation<hkVectorPermutation::YZXW>(r);		// [y, z, x]
	tOut.m_offDiag.setMul(r, tmp);										// [xy, yz, xz]

	const typename hkRealTypes<FT>::Scalar d	= r.template dot<3>(r);	// (xx + yy + zz)
	tmp.setMul(r, r);													// [xx, yy, zz]
	typename hkRealTypes<FT>::Vector dd;		dd.setAll(d);			// [xx + yy + zz, xx + yy + zz, xx + yy + zz]
	tOut.m_diag.setSub(tmp, dd);										// [-yy - zz, -xx - zz, -xx - yy]
}

//
//	Computes the SVD of the given matrix t = R * D * Transpose[R]

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkSymmetricMatrixUtilImpl<FT>::_computeSvd(const typename hkRealTypes<FT>::SymmetricMatrix3& t, typename hkRealTypes<FT>::Rotation& eigenVecsOut, typename hkRealTypes<FT>::Vector& eigenValsOut)
{
	typename hkRealTypes<FT>::Matrix3 tmp;	t.getMatrix(tmp);
	tmp.diagonalizeSymmetricApproximation(eigenVecsOut, eigenValsOut);
}

//
//	Computes the coefficients of the characteristic polynomial
//	Let matrix be:
//		[m00, m01, m02]
//		[m01, m11, m12]
//		[m02, m12, m22]
//
//	Coefficients of the characteristic polynomial are:
//		a3 = 1
//		a2 = -(m00 + m11 + m22)
//		a1 = (m00 * m11 + m11 * m22 + m22 * m00) - (Sqr(m01) + Sqr(m02) + Sqr(m12))
//		a0 = (m00 * Sqr(m12) + m11 * Sqr(m02) + m22 * Sqr(m01)) - m00 m11 m22 - 2 m01 m02 m12

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkSymmetricMatrixUtilImpl<FT>::_computeCharacteristicPolynomial(const typename hkRealTypes<FT>::SymmetricMatrix3& matrixIn, typename hkRealTypes<FT>::Vector& coeffsOut)
{
	const typename hkRealTypes<FT>::Vector d	= matrixIn.m_diag;									// [m00, m11, m22]
	const typename hkRealTypes<FT>::Vector od	= matrixIn.m_offDiag;								// [m01, m12, m02]

	typename hkRealTypes<FT>::Vector rd;		rd.template setPermutation<hkVectorPermutation::YZXW>(d);	// [m11, m22, m00]
	typename hkRealTypes<FT>::Vector rod;		rod.template setPermutation<hkVectorPermutation::YZXW>(od);	// [m12, m02, m01]
	typename hkRealTypes<FT>::Vector rodSq;	rodSq.setMul(rod, rod);								// [Sqr(m12), Sqr(m02), Sqr(m01)]

	// dots = [	Sqr(m01) + Sqr(m02) + Sqr(m12), 
	//			m00 * m11 + m11 * m22 + m22 * m00,
	//			m00 * Sqr(m12) + m11 * Sqr(m02) + m22 * Sqr(m01) ]
	typename hkRealTypes<FT>::Vector dots;
	hkVector4UtilImpl<FT>::dot3_3vs3(od, od, d, rd, d, rodSq, dots);
	const typename hkRealTypes<FT>::Scalar c1 = dots.template getComponent<1>() - dots.template getComponent<0>();	// (m00 * m11 + m11 * m22 + m22 * m00) - (Sqr(m01) + Sqr(m02) + Sqr(m12))

	{
		typename hkRealTypes<FT>::Vector sumD;		sumD.setAdd(d, rd);				// [m00 + m11, m11 + m22, m22 + m00]
		typename hkRealTypes<FT>::Vector prodD;	prodD.setMul(d, rd);			// [m00 m11, m11 m22, m22 m00]
		typename hkRealTypes<FT>::Vector prodOd;	prodOd.setMul(od, rod);			// [m01 m12, m12 m02, m02 m01]

		rd.template setPermutation<hkVectorPermutation::ZXYW>(d);	// [m22, m00, m11]
		rod.template setPermutation<hkVectorPermutation::ZXYW>(od);	// [m02, m01, m12]

		sumD.add(rd);										// [m00 + m11 + m22]
		prodD.mul(rd);										// [m00 m11 m22]
		prodOd.mul(rod);									// [m01 m12 m02]
		sumD.template setNeg<4>(sumD);								// -(m00 + m11 + m22) = c2

		dots.sub(prodD);									// [*, *, m00 Sqr(m12) + m11 Sqr(m02) + m22 Sqr(m01) - m00 m11 m22]
		dots.subMul(hkRealTypes<FT>::Scalar::template getConstant<HK_QUADREAL_2>(), prodOd);					// [*, *, m00 Sqr(m12) + m11 Sqr(m02) + m22 Sqr(m01) - m00 m11 m22 - 2 m01 m02 m12] = c0

		dots.template setSelect<hkVector4ComparisonMask::MASK_Y>(sumD, dots);	// [*, c2, c0, *]
		dots.template setComponent<0>(hkRealTypes<FT>::Scalar::template getConstant<HK_QUADREAL_1>());							// [1, c2, c0, *]
		dots.template setComponent<3>(c1);									// [1, c2, c0, c1]
	}

	coeffsOut.template setPermutation<hkVectorPermutation::XYWZ>(dots);		// [1, c2, c1, c0]
}

#if defined(HK_PLATFORM_WIN32) && (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED) && !defined(HK_ARCH_ARM)
static HK_FORCE_INLINE hkSingleFloat32 __atan2(const hkSingleFloat32& y, const hkSingleFloat32& x)
{
	return hkMath::quadAtan2(y,x);
}
static HK_FORCE_INLINE hkSingleDouble64 __atan2(const hkSingleDouble64& y, const hkSingleDouble64& x)
{
	return hkMath::twoAtan2(y,x);
}
#endif

//
//	Computes the eigenvalues using the characteristic polynomial

template <typename FT>
HK_FORCE_INLINE hkResult HK_CALL hkSymmetricMatrixUtilImpl<FT>::_computeEigenValues(const typename hkRealTypes<FT>::SymmetricMatrix3& t, typename hkRealTypes<FT>::Vector& eigenValsOut)
{
	// Compute characteristic polynomial
	typename hkRealTypes<FT>::Vector vCoeffs;		_computeCharacteristicPolynomial(t, vCoeffs);

	// Solve cubic equation
	typename hkRealTypes<FT>::Scalar deltaSq;
	{
		// Get coefficients
		const typename hkRealTypes<FT>::Scalar a1 = vCoeffs.template getComponent<1>();
		const typename hkRealTypes<FT>::Scalar a2 = vCoeffs.template getComponent<2>();
		const typename hkRealTypes<FT>::Scalar a3 = vCoeffs.template getComponent<3>();

		// Compute discriminant
		const typename hkRealTypes<FT>::Scalar inv3		= hkRealTypes<FT>::Scalar::template getConstant<HK_QUADREAL_INV_3>();
		typename hkRealTypes<FT>::Scalar a1_div_3;		a1_div_3.setMul(inv3, a1);			// (a1 / 3)
		typename hkRealTypes<FT>::Scalar a1Sq_div_3;		a1Sq_div_3.setMul(a1, a1_div_3);// (a1^2 / 3)
		typename hkRealTypes<FT>::Scalar Q;				Q.setSub(a1Sq_div_3, a2);			// (a1^2 / 3 - a2)
		Q.mul(inv3);																		// (a1^2 - 3 a2) / 9
		typename hkRealTypes<FT>::Scalar R;				R.setMul(a1_div_3, a1_div_3);		// (a1^2 / 9)
		const typename hkRealTypes<FT>::Scalar inv2		= hkRealTypes<FT>::Scalar::template getConstant<HK_QUADREAL_INV_2>();
		R.subMul(inv2, a2);					// (a1^2 / 9 - a2 / 2)
		R.mul(a1_div_3);					// (a1/3) * (a1^2 / 9 - a2 / 2)
		R.addMul(inv2, a3);					// (2 a1^3 - 9 a1 a2 + 27 a3) / 54 
		typename hkRealTypes<FT>::Scalar Q_pow_3;			Q_pow_3.setMul(Q, Q);
		Q_pow_3.mul(Q);						// Q^3
		typename hkRealTypes<FT>::Scalar R_pow_2;			R_pow_2.setMul(R, R);	// R^2
		deltaSq.setSub(Q_pow_3, R_pow_2);	// squared discriminant = Q^3 - R^2

		if ( deltaSq.isGreaterEqual(-hkRealTypes<FT>::Scalar::template getConstant<HK_QUADREAL_EPS>()) )
		{
			// Compute angle
			deltaSq.setAbs(deltaSq);
			const typename hkRealTypes<FT>::Scalar delta	= deltaSq.sqrt();
			typename hkRealTypes<FT>::Scalar sA;
#if defined(HK_PLATFORM_WIN32) && (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED) && !defined(HK_ARCH_ARM)
			sA.m_real = __atan2(delta.m_real, R.m_real);
#else
			sA.setFromFloat(hkMath::atan2(delta.getReal(), R.getReal()));
#endif
			typename hkRealTypes<FT>::Scalar angle;		angle.setMul( inv3, sA );	// t1

			// Compute solutions
			typename hkRealTypes<FT>::Vector sinA;
			typename hkRealTypes<FT>::Vector cosA;
			hkVector4UtilImpl<FT>::sinCos(angle, sinA);								// [sinA, cosA, sinA, cosA]
			cosA.template setPermutation<hkVectorPermutation::YYWW>(sinA);	// [cosA, cosA, cosA, cosA]
			sinA.template setPermutation<hkVectorPermutation::XXZZ>(sinA);	// [sinA, sinA, sinA, sinA]
			sinA.template zeroComponent<0>();								// [   0, sinA, sinA, sinA]

			typename hkRealTypes<FT>::Comparison cmpSin;	cmpSin.template set<hkVector4ComparisonMask::MASK_Z>();
			sinA.setFlipSign(sinA, cmpSin);									// [0, sinA, -sinA]

			typename hkRealTypes<FT>::Vector sol;
			sol.setAddMul(cosA, sinA, hkRealTypes<FT>::Scalar::fromFloat(typename hkRealTypes<FT>::Pod(1.7320508075688772935274463415059f)));	// [cosA, cosA + sinA * Sqrt[3], cosA - sinA * Sqrt[3]]
			sol.mul(inv2);																						// [cosA / 2, (cosA + sinA * Sqrt[3]) / 2, (cosA - sinA * Sqrt[3]) / 2]
			cosA.template setNeg<4>(cosA);
			sol.template setSelect<hkVector4ComparisonMask::MASK_X>(cosA, sol);									// [-cosA, (cosA + sinA * Sqrt[3]) / 2, (cosA - sinA * Sqrt[3]) / 2]

			typename hkRealTypes<FT>::Scalar v0 = Q.sqrt();
			v0.add(v0);					// 2 * Sqrt[Q]
			typename hkRealTypes<FT>::Vector v2;	v2.setAll(a1_div_3);		// a1 / 3
			sol.setSubMul(v2, v0, sol);
			sol.template setNeg<3>(sol);

			// Run a Newton-Raphson iteration to improve the precision
			{
				typename hkRealTypes<FT>::Vector vA1;	vA1.setAll(a1);
				typename hkRealTypes<FT>::Vector vA2;	vA2.setAll(a2);
				typename hkRealTypes<FT>::Vector vA3;	vA3.setAll(a3);

				// Polynomial
				typename hkRealTypes<FT>::Vector fx;	fx.setAdd(vA1, sol);	// fx = (x + a1)
				fx.setAddMul(vA2, fx, sol);				// fx = (x^2 + a1 x + a2)
				fx.setAddMul(vA3, fx, sol);				// fx = (x^3 + a1 x^2 + a2 x + a3)

				// Derivative
				vA1.add(vA1);											// 2 a1
				typename hkRealTypes<FT>::Vector dfx;	dfx.setAddMul(vA1, sol, hkRealTypes<FT>::Scalar::template getConstant<HK_QUADREAL_3>());	// dfx = (3 x + 2 a1)
				dfx.setAddMul(vA2, dfx, sol);							// dfx = (3 x^2 + 2 a1 x + a2)

				typename hkRealTypes<FT>::Vector inc;	inc.setDiv(fx, dfx);
				eigenValsOut.setSub(sol, inc);
			}

			return HK_SUCCESS;
		}
	}

	return HK_FAILURE;
}

//
//	Computes the symmetric matrix obtained by computing the cross products between consecutive columns, i.e. {Cross[c1,c2], Cross[c2, c0], Cross[c0, c1]}

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkSymmetricMatrixUtilImpl<FT>::_computeColumnCrossProducts(const typename hkRealTypes<FT>::SymmetricMatrix3& t, typename hkRealTypes<FT>::SymmetricMatrix3& crossProductsOut)
{
	// The elements are:
	//		diagonal		[-m12^2 + m11 m22, -m02^2 + m00 m22, -m01^2 + m00 m11]
	//		off-diagonal	[m02 m12 - m01 m22, m01 m02 - m00 m12, m01 m12 - m02 m11]
	const typename hkRealTypes<FT>::Vector d	= t.m_diag;		// [m00, m11, m22]
	const typename hkRealTypes<FT>::Vector od	= t.m_offDiag;	// [m01, m12, m02]

	// Compute all permutations we need
	typename hkRealTypes<FT>::Vector d_201;	d_201.template setPermutation<hkVectorPermutation::ZXYW>(d);		// [m22, m00, m11]
	typename hkRealTypes<FT>::Vector d_120;	d_120.template setPermutation<hkVectorPermutation::YZXW>(d);		// [m11, m22, m00]
	typename hkRealTypes<FT>::Vector od_201;	od_201.template setPermutation<hkVectorPermutation::ZXYW>(od);	// [m02, m01, m12]
	typename hkRealTypes<FT>::Vector od_120;	od_120.template setPermutation<hkVectorPermutation::YZXW>(od);	// [m12, m02, m01]

	// Build output
	typename hkRealTypes<FT>::Vector dOut;		dOut.setMul(d_120, d_201);	// [m11 m22, m00 m22, m00 m11]
	crossProductsOut.m_diag.setSubMul(dOut, od_120, od_120);				// [m11 m22 - m12^2, m00 m22 - m02^2, m00 m11 - m01^2]
	dOut.setMul(od_201, od_120);											// [m02 m12, m01 m02, m01 m12]
	crossProductsOut.m_offDiag.setSubMul(dOut, od, d_201);					// [m02 m12 - m01 m22, m01 m02 - m00 m12, m01 m12 - m02 m11]
}

//
//	Computes the squared lengths of the given matrix's columns

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkSymmetricMatrixUtilImpl<FT>::_computeColumnLengthsSq(const typename hkRealTypes<FT>::SymmetricMatrix3& t, typename hkRealTypes<FT>::Vector& sqLengthsOut)
{
	const typename hkRealTypes<FT>::Vector d	= t.m_diag;				// [m00, m11, m22]
	typename hkRealTypes<FT>::Vector od;		
	od.template setPermutation<hkVectorPermutation::YZXW>(t.m_offDiag);	// [m12, m02, m01]
	typename hkRealTypes<FT>::Vector odDot;	
	odDot.setAll(od.template lengthSquared<3>());
	odDot.subMul(od, od);												// [m01^2 + m02^2, m01^2 + m12^2, m12^2 + m02^2]
	sqLengthsOut.setAddMul(odDot, d, d);								// [m00^2 + m01^2 + m02^2, m01^2 + m11^2 + m12^2, m02^2 + m12^2 + m22^2]
}

//
//	Computes an eigenvector for the given eigenvalue

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkSymmetricMatrixUtilImpl<FT>::_computeEigenVector(const typename hkRealTypes<FT>::SymmetricMatrix3& t, typename hkRealTypes<FT>::ScalarParameter eigenValueIn, typename hkRealTypes<FT>::Vector& eigenVectorOut)
{
	// Compute T - lambda * I
	typename hkRealTypes<FT>::SymmetricMatrix3 tmp = t;
	{
		typename hkRealTypes<FT>::Vector v;	v.setAll(eigenValueIn);
		tmp.m_diag.sub(v);
	}

	// Compute cross products between all pairs of columns
	typename hkRealTypes<FT>::SymmetricMatrix3 crossProds;
	_computeColumnCrossProducts(tmp, crossProds);

	// Compute their squared lengths
	typename hkRealTypes<FT>::Vector sqLengths;
	_computeColumnLengthsSq(crossProds, sqLengths);

	// Get the index of the maximum component
	const int maxIdx = sqLengths.template getIndexOfMaxComponent<3>();

	// Extract vector
	typename hkRealTypes<FT>::Matrix3 m;	crossProds.getMatrix(m);
	eigenVectorOut = m.getColumn(maxIdx);
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
