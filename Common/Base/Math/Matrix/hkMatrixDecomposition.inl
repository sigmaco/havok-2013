/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

template <typename FT>
void HK_CALL hkMatrixDecompositionImpl<FT>::decompose4x4ColTransform (const typename hkRealTypes<FT>::Pod* matrixIn, typename hkMatrixDecompositionImpl<FT>::Decomposition& decompOut)
{
	typename hkRealTypes<FT>::Matrix4 m; m.set4x4ColumnMajor(matrixIn);
	decomposeMatrix(m, decompOut);
}

template <typename FT>
void HK_CALL hkMatrixDecompositionImpl<FT>::decomposeMatrix (const typename hkRealTypes<FT>::Matrix3& matrixIn, typename hkMatrixDecompositionImpl<FT>::Decomposition& decompOut)
{
	typename hkRealTypes<FT>::Matrix4 matrix4;
	matrix4.setCols(matrixIn.template getColumn<0>(), matrixIn.template getColumn<1>(), matrixIn.template getColumn<2>(), hkRealTypes<FT>::Vector::getZero());
	decomposeMatrix (matrix4, decompOut);
}

template <typename FT>
void HK_CALL hkMatrixDecompositionImpl<FT>::decomposeMatrix (const typename hkRealTypes<FT>::Matrix4& matrixIn, typename hkMatrixDecompositionImpl<FT>::Decomposition& decompOut)
{
	// Change this if you change the tolerance
	const int maxNumIterations = 30; // Usually around 7
	const typename hkRealTypes<FT>::Pod tolerance = hkRealTypes<FT>::Scalar::template getConstant<HK_QUADREAL_EPS>().getReal();

	typename hkRealTypes<FT>::Matrix4 m4 = matrixIn;
	m4.resetFourthRow();

	typename hkRealTypes<FT>::Transform t; m4.get(t);

	// Translation
	{
		decompOut.m_translation = t.getTranslation();
	}

	// Basis (rotation matrix)
	{
		typename hkRealTypes<FT>::Rotation qCur, qNext, qInvT;

		int numIterations = 0;

		qNext = t.getRotation();
		do
		{
			qCur = qNext;

			qInvT = qCur;
			qInvT.invert(tolerance);
			qInvT.transpose();

			typename hkRealTypes<FT>::Matrix3 temp;
			temp = qCur;
			temp.add(qInvT);
			qNext.setMul( hkRealTypes<FT>::Scalar::template getConstant<HK_QUADREAL_INV_2>(), temp );	

			numIterations++;
		} while((numIterations<maxNumIterations) && (!qNext.isApproximatelyEqual( qCur, tolerance )));

		decompOut.m_basis = qNext;
	}

	// Quaternion + "flips" flag
	{
		typename hkRealTypes<FT>::Vector c1 = decompOut.m_basis.template getColumn<0>();
		c1.template normalize<3>();
		typename hkRealTypes<FT>::Vector c2 = decompOut.m_basis.template getColumn<1>();
		c2.template normalize<3>();
		typename hkRealTypes<FT>::Vector c3 = decompOut.m_basis.template getColumn<2>();
		c3.template normalize<3>();

		typename hkRealTypes<FT>::Vector r0; r0.setCross( c2, c3 );
		const typename hkRealTypes<FT>::Scalar determinant = c1.template dot<3>(r0);
		const typename hkRealTypes<FT>::Comparison detLessZero = determinant.lessZero();

		{
			// The rotation is a change of hand-ness
			// Switch one of the columns
			// The scale component should counter-act this
			c1.setFlipSign(c1, detLessZero);
		}

		decompOut.m_flips = detLessZero.anyIsSet();

		// Rotation quaternion
		{
			typename hkRealTypes<FT>::Rotation rot;
			rot.setCols( c1, c2, c3 );
			decompOut.m_rotation.set(rot);
			decompOut.m_rotation.normalize();
		}

	}


	// Scale and Skew
	{
		typename hkRealTypes<FT>::Transform TR; TR.set(decompOut.m_rotation, decompOut.m_translation);
		typename hkRealTypes<FT>::Transform TRInv; TRInv.setInverse(TR);

		typename hkRealTypes<FT>::Matrix4 TRInv4; TRInv4.set(TRInv);
		decompOut.m_scaleAndSkew.setMul(TRInv4, m4);
	}

	// Scale
	const typename hkRealTypes<FT>::Vector one = hkRealTypes<FT>::Vector::template getConstant<HK_QUADREAL_1>();
	typename hkRealTypes<FT>::Scalar eps; eps.setFromFloat(typename hkRealTypes<FT>::Pod(1e-3f));
	{

		// Diagonal
		decompOut.m_scaleAndSkew.getDiagonal(decompOut.m_scale);
		decompOut.m_scale.setW(one);
		decompOut.m_hasScale = ! decompOut.m_scale.template allEqual<4>( one,eps );
	}

	// Skew
	{
		// scale and skew = scale * skew
		// skew = inv(scale) * scaleAndSkew
		typename hkRealTypes<FT>::Vector iscale; iscale.setReciprocal(decompOut.m_scale); iscale.setW(one);
		typename hkRealTypes<FT>::Matrix4 scaleInv; scaleInv.setDiagonal(iscale);
		decompOut.m_skew.setMul(scaleInv, decompOut.m_scaleAndSkew);

		decompOut.m_hasSkew = ! decompOut.m_skew.isApproximatelyIdentity(eps);
	}
}

//
template <typename FT>
typename hkRealTypes<FT>::Scalar HK_CALL	hkMatrixDecompositionImpl<FT>::polarDecompose(const typename hkRealTypes<FT>::Matrix3& m, typename hkRealTypes<FT>::Matrix3& uOut, int maxIterations)
{
	typename hkRealTypes<FT>::Matrix3	k,u; k.setZero(); u = m;
	typename hkRealTypes<FT>::Scalar	invDet; invDet.setReciprocal(u.getDeterminant());
	for(int i=0; i<maxIterations; ++i)
	{
		// Compute k = adj(u)^T / det.
		typename hkRealTypes<FT>::Vector u0YZX; u0YZX.template setPermutation<hkVectorPermutation::YZXW>(u.template getColumn<0>());
		typename hkRealTypes<FT>::Vector u0ZXY; u0ZXY.template setPermutation<hkVectorPermutation::ZXYW>(u.template getColumn<0>());

		typename hkRealTypes<FT>::Vector u1YZX; u1YZX.template setPermutation<hkVectorPermutation::YZXW>(u.template getColumn<1>());
		typename hkRealTypes<FT>::Vector u1ZXY; u1ZXY.template setPermutation<hkVectorPermutation::ZXYW>(u.template getColumn<1>());

		typename hkRealTypes<FT>::Vector u2YZX; u2YZX.template setPermutation<hkVectorPermutation::YZXW>(u.template getColumn<2>());
		typename hkRealTypes<FT>::Vector u2ZXY; u2ZXY.template setPermutation<hkVectorPermutation::ZXYW>(u.template getColumn<2>());

		typename hkRealTypes<FT>::Vector c0;
		{
			c0.setMul(u1YZX,u2ZXY);
			c0.subMul(u2YZX,u1ZXY);
		}
			
		typename hkRealTypes<FT>::Vector c1;
		{
			c1.setMul(u2YZX,u0ZXY);
			c1.subMul(u0YZX,u2ZXY);
		}

		typename hkRealTypes<FT>::Vector c2;
		{
			c2.setMul(u0YZX,u1ZXY);
			c2.subMul(u1YZX,u0ZXY);
		}

		k.setCols(c0,c1,c2);
		k.mul(invDet);
		u._add(k);
		u.mul(hkRealTypes<FT>::Scalar::template getConstant<HK_QUADREAL_INV_2>());
		invDet.setReciprocal(u.getDeterminant());

		typename hkRealTypes<FT>::Scalar	conv = invDet - hkRealTypes<FT>::Scalar::template getConstant<HK_QUADREAL_1>();
		if(conv * conv <= hkRealTypes<FT>::Scalar::template getConstant<HK_QUADREAL_EPS_SQRD>()) break;
	}
	uOut = u;
	return invDet.reciprocal();
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
