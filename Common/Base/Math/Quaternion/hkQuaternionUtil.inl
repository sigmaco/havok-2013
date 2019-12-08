/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

//
//	Computes a 4x4 matrix that allows you to compute any product of the form (this * q) by multiplying (opOut * q)
//	Let:
//		this	= (pV, pS)
//		q		= (qV, qS)
//	Then:
//		this * q	=	(pV * qS + pS * qV + hat(pV) * qV, pS * qS - dot(pV, qV)) = opOut * q
//		opOut		=	| (pS * Identity(3) + hat(pV))		pV	|
//						| -Transpose(pV)					pS	|
//	If:
//		this	= (x, y, z, w), pS = w, pV = (x, y, z)
//		opOut	=	|	 w		-z		 y		x	|
//					|	 z		 w		-x		y	|
//					|	-y		 x		 w		z	|
//					|	-x		-y		-z		w	|

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkQuaternionUtilImpl<FT>::_computePostMultiplyOperator(typename hkRealTypes<FT>::QuaternionParameter q, typename hkRealTypes<FT>::Matrix4& opOut)
{
	// Shuffle the quantities
	typename hkRealTypes<FT>::Vector c0;	c0.template setPermutation<hkVectorPermutation::WZYX>(q.m_vec);	// c0 = (w, z, y, x)
	typename hkRealTypes<FT>::Vector c1;	c1.template setPermutation<hkVectorPermutation::ZWXY>(q.m_vec);	// c1 = (z, w, x, y)
	typename hkRealTypes<FT>::Vector c2;	c2.template setPermutation<hkVectorPermutation::YXWZ>(q.m_vec);	// c2 = (y, x, w, z)

	typename hkRealTypes<FT>::Comparison s0;	s0.template set<hkVector4ComparisonMask::MASK_ZW>();			// s0 = (1, 1, -1, -1)
	typename hkRealTypes<FT>::Comparison s1;	s1.template set<hkVector4ComparisonMask::MASK_XW>();			// s1 = (-1, 1, 1, -1)
	typename hkRealTypes<FT>::Comparison s2;	s2.template set<hkVector4ComparisonMask::MASK_YW>();			// s2 = (1, -1, 1, -1)

	// Set-up the output matrix
	c0.setFlipSign(c0, s0);		//  w  z -y -x
	c1.setFlipSign(c1, s1);		// -z  w  x -y
	c2.setFlipSign(c2, s2);		//  y -x  w -z

	opOut.setCols(c0, c1, c2, q.m_vec);
}

//
//	Computes a 4x4 matrix that allows you to compute any product of the form (q * this) by multiplying (opOut * q)
//	Let:
//		this	= (pV, pS)
//		q		= (qV, qS)
//	Then:
//		q * this	=	(pV * qS + pS * qV - hat(pV) * qV, pS * qS - dot(pV, qV)) = opOut * q
//		opOut		=	| (pS * Identity(3) - hat(pV))		pV	|
//						| -Transpose(pV)					pS	|
//	If:
//		this	= (x, y, z, w), pS = w, pV = (x, y, z)
//		opOut	=	|	 w		 z		-y		x	|
//					|	-z		 w		 x		y	|
//					|	 y		-x		 w		z	|
//					|	-x		-y		-z		w	|

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkQuaternionUtilImpl<FT>::_computePreMultiplyOperator(typename hkRealTypes<FT>::QuaternionParameter q, typename hkRealTypes<FT>::Matrix4& opOut)
{
	// Shuffle the quantities
	typename hkRealTypes<FT>::Vector c0;	c0.template setPermutation<hkVectorPermutation::WZYX>(q.m_vec);	// c0 = (w, z, y, x)
	typename hkRealTypes<FT>::Vector c1;	c1.template setPermutation<hkVectorPermutation::ZWXY>(q.m_vec);	// c1 = (z, w, x, y)
	typename hkRealTypes<FT>::Vector c2;	c2.template setPermutation<hkVectorPermutation::YXWZ>(q.m_vec);	// c2 = (y, x, w, z)

	typename hkRealTypes<FT>::Comparison s0;	s0.template set<hkVector4ComparisonMask::MASK_YW>();			// s0 = (1, -1, 1, -1)
	typename hkRealTypes<FT>::Comparison s1;	s1.template set<hkVector4ComparisonMask::MASK_ZW>();			// s1 = (1, 1, -1, -1)
	typename hkRealTypes<FT>::Comparison s2;	s2.template set<hkVector4ComparisonMask::MASK_XW>();			// s2 = (-1, 1, 1, -1)

	// Set-up the output matrix
	c0.setFlipSign(c0, s0);	//  w -z  y -x
	c1.setFlipSign(c1, s1);	//  z  w -x -y
	c2.setFlipSign(c2, s2);	// -y  x  w -z

	opOut.setCols(c0, c1, c2, q.m_vec);
}

//
//	Computes a 4x4 matrix that allows you to compute any product of the form (Inverse(this) * q) by multiplying (opOut * q)
//	If:
//		this	= (x, y, z, w), pS = w, pV = (x, y, z)
//		opOut	=	|	 w		 z		-y		-x	|
//					|	-z		 w		 x		-y	|
//					|	 y		-x		 w		-z	|
//					|	 x		 y		 z		 w	|

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkQuaternionUtilImpl<FT>::_computeInversePostMultiplyOperator(typename hkRealTypes<FT>::QuaternionParameter q, typename hkRealTypes<FT>::Matrix4& opOut)
{
	// Shuffle the quantities
	typename hkRealTypes<FT>::Vector c0;	c0.template setPermutation<hkVectorPermutation::WZYX>(q.m_vec);	// c0 = (w, z, y, x)
	typename hkRealTypes<FT>::Vector c1;	c1.template setPermutation<hkVectorPermutation::ZWXY>(q.m_vec);	// c1 = (z, w, x, y)
	typename hkRealTypes<FT>::Vector c2;	c2.template setPermutation<hkVectorPermutation::YXWZ>(q.m_vec);	// c2 = (y, x, w, z)
	typename hkRealTypes<FT>::Vector c3		= q.m_vec;														// c3 = (x, y, z, w)
	
	typename hkRealTypes<FT>::Comparison s0;	s0.template set<hkVector4ComparisonMask::MASK_Y>();			// s0 = (1, -1, 1, 1)
	typename hkRealTypes<FT>::Comparison s1;	s1.template set<hkVector4ComparisonMask::MASK_Z>();			// s1 = (1, 1, -1, 1)

	// Set-up the output matrix
	c0.setFlipSign(c0, s0);				//  w -z  y  x
	c1.setFlipSign(c1, s1);				//  z  w -x  y
	c2.template setNeg<1>(c2);			// -y  x  w  z
	c3.template setNeg<3>(c3);			// -x -y -z  w

	opOut.setCols(c0, c1, c2, c3);
}

//
//	Computes a 4x4 matrix that allows you to compute any product of the form (q * Inverse(this)) by multiplying (opOut * q)
//	If:
//		this	= (x, y, z, w), pS = w, pV = (x, y, z)
//		opOut	=	|	 w		-z		 y		-x	|
//					|	 z		 w		-x		-y	|
//					|	-y		 x		 w		-z	|
//					|	 x		 y		 z		 w	|

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkQuaternionUtilImpl<FT>::_computeInversePreMultiplyOperator(typename hkRealTypes<FT>::QuaternionParameter q, typename hkRealTypes<FT>::Matrix4& opOut)
{
	typename hkRealTypes<FT>::Vector c0;	c0.template setPermutation<hkVectorPermutation::WZYX>(q.m_vec);	// c0 = (w, z, y, x)
	typename hkRealTypes<FT>::Vector c1;	c1.template setPermutation<hkVectorPermutation::ZWXY>(q.m_vec);	// c1 = (z, w, x, y)
	typename hkRealTypes<FT>::Vector c2;	c2.template setPermutation<hkVectorPermutation::YXWZ>(q.m_vec);	// c2 = (y, x, w, z)
	typename hkRealTypes<FT>::Vector c3		= q.m_vec;														// c3 = (x, y, z, w)

	typename hkRealTypes<FT>::Comparison s0;	s0.template set<hkVector4ComparisonMask::MASK_Z>();			// s0 = (1,  1, -1, 1)
	typename hkRealTypes<FT>::Comparison s2;	s2.template set<hkVector4ComparisonMask::MASK_Y>();			// s2 = (1, -1,  1, 1)

	// Set-up the output matrix
	c0.setFlipSign(c0, s0);				//  w  z -y  x
	c1.template setNeg<1>(c1);			// -z  w  x  y
	c2.setFlipSign(c2, s2);				//  y -x  w  z
	c3.template setNeg<3>(c3);			// -x -y -z  w

	opOut.setCols(c0, c1, c2, c3);
}

//
//	Sets this = Transpose(op) * q, where op is a 4x4 matrix operator and q is a quaternion interpreted as a 4-element vector.

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkQuaternionUtilImpl<FT>::_computeTransposeMul(const typename hkRealTypes<FT>::Matrix4& op, typename hkRealTypes<FT>::QuaternionParameter qIn, typename hkRealTypes<FT>::Quaternion& qOut)
{
	hkVector4UtilImpl<FT>::dot4_1vs4(qIn.m_vec, op.template getColumn<0>(), op.template getColumn<1>(), op.template getColumn<2>(), op.template getColumn<3>(), qOut.m_vec);
}

//
//	N-lerp

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkQuaternionUtilImpl<FT>::_computeNlerp(typename hkRealTypes<FT>::QuaternionParameter q0, typename hkRealTypes<FT>::QuaternionParameter q1, typename hkRealTypes<FT>::ScalarParameter t, typename hkRealTypes<FT>::Quaternion& qOut)
{
	typename hkRealTypes<FT>::Vector v;
	v.setInterpolate(q0.m_vec, q1.m_vec, t);
	v.template normalize<4>();
	qOut.m_vec = v;
}

#if defined(HK_PLATFORM_WIN32) && (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED) && !defined(HK_ARCH_ARM)
static HK_FORCE_INLINE hkSingleFloat32 __acos(const hkSingleFloat32& r)
{
	return hkMath::quadAcos(r);
}
static HK_FORCE_INLINE hkSingleDouble64 __acos(const hkSingleDouble64& r)
{
	return hkMath::twoAcos(r);
}
static HK_FORCE_INLINE hkSingleFloat32 __sin(const hkSingleFloat32& r)
{
	return hkMath::quadSin(r);
}
static HK_FORCE_INLINE hkSingleDouble64 __sin(const hkSingleDouble64& r)
{
	return hkMath::twoSin(r);
}
#endif
//
//	Computes the logarithm of a quaternion

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkQuaternionUtilImpl<FT>::_computeLog(typename hkRealTypes<FT>::QuaternionParameter q, typename hkRealTypes<FT>::Vector& vOut)
{
	// Get axis and cos(angle)
	const typename hkRealTypes<FT>::Scalar cosA = q.getRealPart();
	vOut = q.getImag();

	// If the angle is not zero, return angle * axis,
	// otherwise return just axis, because axis = sin(angle) * direction
	// and for very small angles, the angle / sin(angle) -> 1.
	typename hkRealTypes<FT>::Scalar absCosA; absCosA.setAbs(cosA);
	if ( absCosA.isLess(hkRealTypes<FT>::Scalar::template getConstant<HK_QUADREAL_1>()) )
	{
		typename hkRealTypes<FT>::Scalar a,sA;
#if defined(HK_PLATFORM_WIN32) && (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED) && !defined(HK_ARCH_ARM)
		const typename hkRealTypes<FT>::Scalar qReal = q.getRealPart();
		a.m_real = __acos(qReal.m_real);
		sA.m_real = __sin(a.m_real);
#else
		const typename hkRealTypes<FT>::Pod angle = hkMath::acos(q.getReal()); // use indep cosA
		a.setFromFloat(angle);
		const typename hkRealTypes<FT>::Pod sinA = hkMath::sin(angle);
		sA.setFromFloat(sinA);
#endif
		typename hkRealTypes<FT>::Scalar absSinA; absSinA.setAbs(sA);
		const typename hkRealTypes<FT>::Comparison absSinAGreaterEqualEps = absSinA.greaterEqual(hkRealTypes<FT>::Scalar::template getConstant<HK_QUADREAL_EPS>());

		typename hkRealTypes<FT>::Scalar d; d.setDiv(a,sA);
		typename hkRealTypes<FT>::Vector logV; logV.setMul(vOut, d);

		vOut.setSelect(absSinAGreaterEqualEps, logV, vOut);
	}
}

//
//	Set the quaternion as the exponential of the given (axis-angle) vector

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkQuaternionUtilImpl<FT>::_computeExp(typename hkRealTypes<FT>::VectorParameter vIn, typename hkRealTypes<FT>::Quaternion& qOut)
{
	const typename hkRealTypes<FT>::Scalar angle = vIn.template length<3>();

	typename hkRealTypes<FT>::Vector sc;
	hkVector4UtilImpl<FT>::sinCos(angle,sc);
	const typename hkRealTypes<FT>::Scalar sA = sc.template getComponent<0>();

	typename hkRealTypes<FT>::Scalar absSinA; absSinA.setAbs(sA);
	const typename hkRealTypes<FT>::Comparison absSinAGreaterEqualEps = absSinA.greaterEqual(hkRealTypes<FT>::Scalar::template getConstant<HK_QUADREAL_EPS>());

	typename hkRealTypes<FT>::Scalar d; d.setDiv(sA,angle);
	typename hkRealTypes<FT>::Vector expV; expV.setMul(vIn, d);

	typename hkRealTypes<FT>::Vector quatDir; quatDir.setSelect(absSinAGreaterEqualEps, expV, vIn);

	qOut.m_vec.setXYZ_W(quatDir, sc.template getComponent<1>());
}

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkQuaternionUtilImpl<FT>::_computeExp_Approximate(typename hkRealTypes<FT>::VectorParameter vIn, typename hkRealTypes<FT>::Quaternion& qOut)
{
#if defined(HK_PLATFORM_WIN32) && (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED) && !defined(HK_ARCH_ARM)
	const typename hkRealTypes<FT>::Scalar angle = vIn.template length<3>();

	typename hkRealTypes<FT>::Vector sinCos;
	hkVector4UtilImpl<FT>::sinCosApproximation(angle,sinCos);
	typename hkRealTypes<FT>::Scalar sA = sinCos.template getComponent<0>();

	typename hkRealTypes<FT>::Scalar absSinA; absSinA.setAbs(sA);
	const typename hkRealTypes<FT>::Comparison absSinAGreaterEqualEps = absSinA.greaterEqual(hkRealTypes<FT>::Scalar::template getConstant<HK_QUADREAL_EPS>());

	typename hkRealTypes<FT>::Scalar d; d.template setDiv<HK_ACC_12_BIT,HK_DIV_IGNORE>(sA,angle);
	typename hkRealTypes<FT>::Vector expV; expV.setMul(vIn, d);

	typename hkRealTypes<FT>::Vector quatDir; quatDir.setSelect(absSinAGreaterEqualEps, expV, vIn);

	qOut.m_vec.setXYZ_W(quatDir, sinCos.template getComponent<1>());
#else
	_computeExp(vIn, qOut);
#endif
}

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkQuaternionUtilImpl<FT>::_computeShortestRotation(typename hkRealTypes<FT>::VectorParameter from, typename hkRealTypes<FT>::VectorParameter to, typename hkRealTypes<FT>::Quaternion& qOut)
{
	HK_MATH_ASSERT(0xad87ba22, from.template isNormalized<3>() && to.template isNormalized<3>(), "hkQuaternion::setShortestRotation input vectors are not normalized.");

#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)

	const typename hkRealTypes<FT>::Scalar dotProd = from.template dot<3>( to ); // cos(theta)

	typename hkRealTypes<FT>::Scalar nearlyOne; nearlyOne.setFromFloat(typename hkRealTypes<FT>::Pod(1.0f - 1e-5f));

	if( dotProd.isGreater(nearlyOne) )
	{
		qOut.setIdentity();
	}
	else 
	{
		nearlyOne = -nearlyOne;

		if( dotProd.isLess(nearlyOne) )
		{
			qOut.setFlippedRotation( from );
		}
		else
		{
			// Using cos(theta) = 2*cos^2(theta/2) - 1
			const typename hkRealTypes<FT>::Scalar oneHalf = hkRealTypes<FT>::Scalar::template getConstant<HK_QUADREAL_INV_2>();
			typename hkRealTypes<FT>::Scalar c; c.setAddMul(oneHalf, oneHalf, dotProd); // .5 * ( 1 + dotProd) 
			const typename hkRealTypes<FT>::Scalar sqrtInverseC = c.sqrtInverse();

			//const typename hkRealTypes<FT>::Pod cosT2 = hkMath::sqrt( c );

			typename hkRealTypes<FT>::Vector cross;
			cross.setCross( from, to ); // ~sin(theta)* axis -- this is not exact sin(theta) .. error around 1-e2 for angles close to 180deg

			//typename hkRealTypes<FT>::Pod rescaleSin  = 0.5f / cosT2;
			typename hkRealTypes<FT>::Scalar rescaleSin = oneHalf * sqrtInverseC;

			typename hkRealTypes<FT>::Scalar somewhatNearlyNegOne; somewhatNearlyNegOne.setFromFloat(typename hkRealTypes<FT>::Pod(-(1.0f - 1e-3f)));

			if (dotProd.isLess(somewhatNearlyNegOne))
			{
				// Extra correction needed for angles around 180deg
				//
				//const typename hkRealTypes<FT>::Pod sinT2 = hkMath::sqrt( cosT2 * cosT2 - dotProd );
				const typename hkRealTypes<FT>::Scalar sinT4 = c - dotProd;
				const typename hkRealTypes<FT>::Scalar invApproxSinT = cross.template lengthInverse<3>(); // this has errors around 1-e2 for angles around 180 deg.
				//const typename hkRealTypes<FT>::Pod sinT = 2 * sinT2 * cosT2;
				//rescaleSin *= (sinT / approxSinT);

				//rescaleSin = sinT2 / approxSinT;
				rescaleSin = sinT4 * sinT4.sqrtInverse() * invApproxSinT;
			}

			// Using sin(theta) = 2*cos(theta/2)*sin(theta/2)
			cross.mul( rescaleSin );
			qOut.m_vec.setXYZ_W( cross, c * sqrtInverseC ); // = sqrt(c)
		}
	}

#else

	const typename hkRealTypes<FT>::Pod dotProd = from.template dot<3>( to ).getReal(); // cos(theta)
	const typename hkRealTypes<FT>::Pod nearlyOne = typename hkRealTypes<FT>::Pod(1.0f - 1e-5f);
	const typename hkRealTypes<FT>::Pod somewhatNearlyNegativeOne = typename hkRealTypes<FT>::Pod(-(1.0f - 1e-3f));
	if( dotProd > nearlyOne )
	{
		qOut.setIdentity();
	}
	else if( dotProd < -nearlyOne )
	{
		qOut.setFlippedRotation( from );
	}
	else
	{
		// Using cos(theta) = 2*cos^2(theta/2) - 1
		const typename hkRealTypes<FT>::Pod c = (dotProd + typename hkRealTypes<FT>::Pod(1)) * typename hkRealTypes<FT>::Pod(0.5f);
		const typename hkRealTypes<FT>::Pod cosT2 = hkMath::sqrt( c );

		typename hkRealTypes<FT>::Vector cross;
		cross.setCross( from, to ); // ~sin(theta)* axis -- this is not exact sin(theta) .. error around 1-e2 for angles close to 180deg

		typename hkRealTypes<FT>::Pod rescaleSin  = typename hkRealTypes<FT>::Pod(0.5f) / cosT2;

		if (dotProd < somewhatNearlyNegativeOne)
		{
			// Extra correction needed for angles around 180deg
			//
			const typename hkRealTypes<FT>::Pod sinT2 = hkMath::sqrt( cosT2 * cosT2 - dotProd );
			const typename hkRealTypes<FT>::Pod approxSinT = cross.template length<3>().getReal(); // this has errors around 1-e2 for angles around 180 deg.
			const typename hkRealTypes<FT>::Pod sinT = typename hkRealTypes<FT>::Pod(2) * sinT2 * cosT2;
			rescaleSin *= (sinT / approxSinT);
		}

		// Using sin(theta) = 2*cos(theta/2)*sin(theta/2)
		typename hkRealTypes<FT>::Scalar rescaleSinV; rescaleSinV.setFromFloat(rescaleSin);
		cross.mul( rescaleSinV );
		cross(3) = cosT2;
		qOut.m_vec = cross;
	}

#endif

	HK_MATH_ASSERT(0xad78999d, qOut.isOk(), "Resulting quaternion is not normalized.");
}

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkQuaternionUtilImpl<FT>::_computeShortestRotationDamped(typename hkRealTypes<FT>::VectorParameter from, typename hkRealTypes<FT>::VectorParameter to, typename hkRealTypes<FT>::ScalarParameter gain, typename hkRealTypes<FT>::Quaternion& qOut)
{
	const typename hkRealTypes<FT>::Scalar one =  hkRealTypes<FT>::Scalar::template getConstant<HK_QUADREAL_1>();
	const typename hkRealTypes<FT>::Scalar half = hkRealTypes<FT>::Scalar::template getConstant<HK_QUADREAL_INV_2>();

	const typename hkRealTypes<FT>::Scalar dotProd = from.template dot<3>( to ); // cos(theta)
	const typename hkRealTypes<FT>::Scalar dampedDot = one - gain + gain * dotProd;
	typename hkRealTypes<FT>::Scalar nearlyOne; nearlyOne.setFromFloat(typename hkRealTypes<FT>::Pod(1.0f - 1e-6f));

	const typename hkRealTypes<FT>::Scalar c = (dampedDot + one) * half;
	if ( c.isLessEqualZero() | dotProd.isLess(-nearlyOne) )
	{
		qOut.setFlippedRotation( from );
	}
	else
	{
		if( dotProd.isGreater(nearlyOne) )
		{
			qOut.setIdentity();
		}
		else
		{
			const typename hkRealTypes<FT>::Scalar cosT2 = c.template sqrt<HK_ACC_23_BIT,HK_SQRT_IGNORE>();

			typename hkRealTypes<FT>::Vector cross; cross.setCross( from, to ); // sin(theta)* axis

			// Using sin(theta) = 2*cos(theta/2)*sin(theta/2)
			typename hkRealTypes<FT>::Scalar rescaleSin; rescaleSin.setDiv(gain * half, cosT2);
			cross.mul( rescaleSin );
			cross.template setComponent<3>(cosT2);

			// renormalize for gain.
			cross.template normalize<4>();
			qOut.m_vec = cross;
		}
	}

	HK_MATH_ASSERT(0xad78999e, qOut.isOk(), "Resulting quaternion is not normalized.");
}

//
//	Computes a clamped quaternion such that the rotation angle is less than the given value.
//		q0 = [u * sin(a/2), cos(a/2)]

template <typename FT>
HK_FORCE_INLINE hkBool32 HK_CALL hkQuaternionUtilImpl<FT>::_computeClampedRotation(typename hkRealTypes<FT>::QuaternionParameter q0, typename hkRealTypes<FT>::ScalarParameter cosMaxAngle, typename hkRealTypes<FT>::Quaternion& qClamped)
{
	// Make sure the rotation angle is between [0, 180] degrees
	typename hkRealTypes<FT>::Quaternion q;
	q.setIdentity();		// [0, 0, 0, 1]
	q.setClosest(q0, q);	// +/-[u * sin(a/2), cos(a/2)] such that cos(a/2) is positive

	// Extract rotation axis
	typename hkRealTypes<FT>::Vector u;
	const typename hkRealTypes<FT>::Vector vRotationAxis	= q.getImag();							// u * sin(a/2)
	const typename hkRealTypes<FT>::Scalar sinHalfSq		= vRotationAxis.template lengthSquared<3>();		// = sin(a/2) * (sin(a/2)
	const typename hkRealTypes<FT>::Scalar invSinHalf		= sinHalfSq.sqrtInverse();				// = 1 / sin(a/2)
	u.setMul(invSinHalf, vRotationAxis);
	u.setSelect(sinHalfSq.greater(hkRealTypes<FT>::Scalar::template getConstant<HK_QUADREAL_EPS_SQRD>()), u, hkRealTypes<FT>::Vector::template getConstant<HK_QUADREAL_1000>());

	// Compute cos(a) = cos(a/2) * cos(a/2) - sin(a/2) * (sin(a/2) = 1 - 2 * sin(a/2) * (sin(a/2)
	// We want cos(a) >= cos(aMax), with 0 <= aMax  <= PI
	const typename hkRealTypes<FT>::Scalar cosA			= hkRealTypes<FT>::Scalar::template getConstant<HK_QUADREAL_1>() - hkRealTypes<FT>::Scalar::template getConstant<HK_QUADREAL_2>() * sinHalfSq;

	// Compute the clamped quaternion
	typename hkRealTypes<FT>::Vector v;
	v.setAll(cosMaxAngle);								// [cos(b), cos(b), cos(b), cos(b)]
	v.template setNeg<3>(v);										// [-cos(b), -cos(b), -cos(b), cos(b)]
	v.add(hkRealTypes<FT>::Vector::template getConstant<HK_QUADREAL_1>());		// [1 - cos(b), 1 - cos(b), 1 - cos(b), 1 + cos(b)]
	v.mul(hkRealTypes<FT>::Scalar::template getConstant<HK_QUADREAL_INV_2>());								// [sin(b/2), sin(b/2), sin(b/2), cos(b/2)]^2
	v.setSqrt(v);										// [sin(b/2), sin(b/2), sin(b/2), cos(b/2)]
	u.template setComponent<3>(hkRealTypes<FT>::Scalar::template getConstant<HK_QUADREAL_1>());					// [u, 1]
	u.mul(v);											// [u * sin(b/2), cos(b/2)]
	const typename hkRealTypes<FT>::Comparison cmp = cosA.less(cosMaxAngle);
	qClamped.m_vec.setSelect(cmp, u, q0.m_vec);
	return cmp.anyIsSet();
}

//
//	Increments (integrates) the given quaternion with the given axis-angle delta

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkQuaternionUtilImpl<FT>::_increment(typename hkRealTypes<FT>::QuaternionParameter qSrc, typename hkRealTypes<FT>::VectorParameter axisAngleDelta, typename hkRealTypes<FT>::Quaternion& qDst)
{
	typename hkRealTypes<FT>::Vector halfAxisAngle;	halfAxisAngle.setMul(hkRealTypes<FT>::Scalar::template getConstant<HK_QUADREAL_INV_2>(), axisAngleDelta);
	typename hkRealTypes<FT>::Quaternion dq;			dq.m_vec.setXYZ_W(halfAxisAngle, hkRealTypes<FT>::Scalar::template getConstant<HK_QUADREAL_1>());			// [angle * axis / 2, 1]
	typename hkRealTypes<FT>::Quaternion q;				q.setMul(dq, qSrc);
														q.normalize();
	qDst = q;
}

//
//	Computes the maximum angular velocity that can be applied to quaternion qA along rotation axis dw (ASSUMED normalized) that will keep
//	the relative angle between qA and qB under the given threshold.

template <typename FT>
HK_FORCE_INLINE const typename hkRealTypes<FT>::Scalar HK_CALL hkQuaternionUtilImpl<FT>::_computeMaximumAllowedVelocity(typename hkRealTypes<FT>::QuaternionParameter qA, typename hkRealTypes<FT>::QuaternionParameter qB, typename hkRealTypes<FT>::VectorParameter rotAxis, typename hkRealTypes<FT>::ScalarParameter cosMax)
{
	// We want to limit the relative rotation between qA and qB
	// Let pAB = Inverse[qB] * qA.
	// 
	// A displacement of qA can be expressed w.r.t. the rotation angle a as:
	//		qA[a] = Quaternion[u * a / 2, 1] * qA
	//		pAB[a]	= Normalize[Inverse[qB] * qW * qA], and moving to quaternion operator notation
	//				= Normalize[ Transpose[Post[qB]] * Pre[qA] * Quaternion[u * a / 2, 1] ]
	//
	// Let M = Transpose[Post[qB]] * Pre[qA], a 4x4 matrix
	//		pAB[a] = {x[a], y[a], z[a], w[a]} = {v * sin(b/2), cos(b/2)} and we want to limit cos(b) >= cosMax
	//		cos(b) = cos(b/2)^2 - sin(b/2)^2 = (w^2 - (x^2 + y^2 + z^2)) / (x^2 + y^2 + z^2 + w^2) >= cosMax
	//
	// Therefore, we have to solve the equation for a:
	//		(1 + cosMax) * (x^2 + y^2 + z^2) + (cosMax - 1) * w^2 <= 0
	//
	//	Let M = {M00, M01, M10, M11}, where M00 is 3x3, M01 = 3x1, M10 = 1x3, M11 = 1x1.
	//		pAB = {x, y, z, w}	= {(M00 * u/2) * a + M01, (M10 * u/2) * a + M11}
	//		(x^2 + y^2 + z^2)	= (M00 * u/2)^2 * a^2 + 2 * (M00 * u/2 * M01) * a + M01^2
	//		w^2					= (M10 * u/2)^2 * a^2 + 2 * (M10 * u/2 * M11) * a + M11^2

	// Compute matrix M based on connection pivots
	typename hkRealTypes<FT>::Matrix4 M;
	{
		typename hkRealTypes<FT>::Matrix4 preA;		_computePreMultiplyOperator(qA, preA);
		typename hkRealTypes<FT>::Matrix4 postB;	_computePostMultiplyOperator(qB, postB);
		//hkMatrix4Util::_computeTransposeMul(postB, preA, M); inlined here to minimize dependencies
		{
			typename hkRealTypes<FT>::Vector c0;	hkVector4UtilImpl<FT>::dot4_1vs4(preA.template getColumn<0>(), postB.template getColumn<0>(), postB.template getColumn<1>(), postB.template getColumn<2>(), postB.template getColumn<3>(), c0);
			typename hkRealTypes<FT>::Vector c1;	hkVector4UtilImpl<FT>::dot4_1vs4(preA.template getColumn<1>(), postB.template getColumn<0>(), postB.template getColumn<1>(), postB.template getColumn<2>(), postB.template getColumn<3>(), c1);
			typename hkRealTypes<FT>::Vector c2;	hkVector4UtilImpl<FT>::dot4_1vs4(preA.template getColumn<2>(), postB.template getColumn<0>(), postB.template getColumn<1>(), postB.template getColumn<2>(), postB.template getColumn<3>(), c2);
			typename hkRealTypes<FT>::Vector c3;	hkVector4UtilImpl<FT>::dot4_1vs4(preA.template getColumn<3>(), postB.template getColumn<0>(), postB.template getColumn<1>(), postB.template getColumn<2>(), postB.template getColumn<3>(), c3);

			M.setCols(c0, c1, c2, c3);
		}
	}

	// Compute equation coeffs, i.e. c0 * a^2 + 2 * c1 * a + c0 = 0
	typename hkRealTypes<FT>::Scalar c0, c1, c2;
	{
		typename hkRealTypes<FT>::Vector halfU;		halfU.setMul(hkRealTypes<FT>::Scalar::template getConstant<HK_QUADREAL_INV_2>(), rotAxis);
		typename hkRealTypes<FT>::Vector M00_u;		M.transformDirection(halfU, M00_u);		// (M00 * u/2)
		const typename hkRealTypes<FT>::Vector M01		= M.template getColumn<3>();						// M01
		const typename hkRealTypes<FT>::Scalar M11	= M01.template getComponent<3>();				// M11
		const typename hkRealTypes<FT>::Scalar M10_u	= M00_u.template getComponent<3>();				// (M10 * u/2), this results as a by-product of transformDirection

		// (x^2 + y^2 + z^2) = xyz_c2 * a^2 + 2 * xyz_c1 * a + xyz_c0
		typename hkRealTypes<FT>::Scalar cos_p1;		cos_p1.setAdd(hkRealTypes<FT>::Scalar::template getConstant<HK_QUADREAL_1>(), cosMax);				// (1 + cosMax)
		typename hkRealTypes<FT>::Scalar xyz_c2;		xyz_c2.setMul(cos_p1, M00_u.template lengthSquared<3>());	// (1 + cosMax) * (M00 * u/2)^2
		typename hkRealTypes<FT>::Scalar xyz_c1;		xyz_c1.setMul(cos_p1, M00_u.template dot<3>(M01));			// (1 + cosMax) * (M00 * u/2) * M01
		typename hkRealTypes<FT>::Scalar xyz_c0;		xyz_c0.setMul(cos_p1, M01.template lengthSquared<3>());		// (1 + cosMax) * M01^2

		// w^2 = w_c2 * a^2 + 2 * w_c1 * a + w_c0
		typename hkRealTypes<FT>::Scalar w_c2;		w_c2.setMul(M10_u, M10_u);				// (M10 * u/2)^2
		typename hkRealTypes<FT>::Scalar w_c1;		w_c1.setMul(M10_u, M11);				// (M10 * u/2 * M11)
		typename hkRealTypes<FT>::Scalar w_c0;		w_c0.setMul(M11, M11);					// M11^2

		typename hkRealTypes<FT>::Scalar cos_m1;		cos_m1.setSub(cosMax, hkRealTypes<FT>::Scalar::template getConstant<HK_QUADREAL_1>());	// (cosMax - 1)
		c2.setAddMul(xyz_c2, cos_m1, w_c2);		// (1 + cosMax) * (M00 * u/2)^2		+ (cosMax - 1) * (M10 * u/2)^2
		c1.setAddMul(xyz_c1, cos_m1, w_c1);		// (1 + cosMax) * (M00 * u/2) * M01 + (cosMax - 1) * (M10 * u/2 * M11)
		c0.setAddMul(xyz_c0, cos_m1, w_c0);		// (1 + cosMax) * M01^2				+ (cosMax - 1) * M11^2
	}

	// Solve equation for a
	typename hkRealTypes<FT>::Scalar absC2;	absC2.setAbs(c2);
	if ( absC2.isGreaterEqual(hkRealTypes<FT>::Scalar::template getConstant<HK_QUADREAL_EPS>()) )
	{
		// Quadratic
		typename hkRealTypes<FT>::Scalar DSq;			DSq.setMul(c1, c1);			DSq.subMul(c2, c0);
		typename hkRealTypes<FT>::Scalar D;			D.setAbs(DSq);				D = D.sqrt();
		const typename hkRealTypes<FT>::Scalar invC2	= -c2.reciprocal();
		typename hkRealTypes<FT>::Scalar a1;			a1.setAdd(c1, D);			a1.mul(invC2);	// -(c1 + D) / c0
		typename hkRealTypes<FT>::Scalar a2;			a2.setSub(c1, D);			a2.mul(invC2);	// -(c1 - D) / c0
		typename hkRealTypes<FT>::Scalar a12;			a12.setMax(a1, a2);

		// Back-up. If the (discriminant < 0 or a12 < 0) then: if c2 > 0, the function will always be positive for positive a, so limit is 0.
		// If c2 < 0, the function will always be negative for positive a, so no limit!
		{
			typename hkRealTypes<FT>::Scalar aBackup;				aBackup.setZero();
			aBackup.setSelect(c2.lessZero(), hkRealTypes<FT>::Scalar::template getConstant<HK_QUADREAL_MAX>(), aBackup);
			typename hkRealTypes<FT>::Comparison cmpDegen;	cmpDegen.setOr(DSq.lessZero(), a12.lessZero());
			a12.setSelect(cmpDegen, aBackup, a12);
		}

		return a12;
	}

	typename hkRealTypes<FT>::Scalar absC1;	absC1.setAbs(c1);
	if ( absC1.isGreaterEqual(hkRealTypes<FT>::Scalar::template getConstant<HK_QUADREAL_EPS>()) )
	{
		// Linear, i.e. 2 * c1 * a + c0 = 0
		//		a = -c0 / (2 c1)
		typename hkRealTypes<FT>::Scalar a1;			a1.setDiv(-hkRealTypes<FT>::Scalar::template getConstant<HK_QUADREAL_INV_2>() * c0, c1);
		typename hkRealTypes<FT>::Scalar aBackup;		aBackup.setZero();
		aBackup.setSelect(c1.lessZero(), hkRealTypes<FT>::Scalar::template getConstant<HK_QUADREAL_MAX>(), aBackup);
		a1.setSelect(a1.lessZero(), aBackup, a1);
		return a1;
	}

	{
		// Else, either 0 or no limit, based on the sign of c0
		typename hkRealTypes<FT>::Scalar a0;		a0.setZero();
		a0.setSelect(c0.lessEqualZero(), hkRealTypes<FT>::Scalar::template getConstant<HK_QUADREAL_MAX>(), a0);
		return a0;
	}
}

//
//	Computes the cosine of the rotation angle

template <typename FT>
HK_FORCE_INLINE const typename hkRealTypes<FT>::Scalar HK_CALL hkQuaternionUtilImpl<FT>::_computeCosRotationAngle(typename hkRealTypes<FT>::QuaternionParameter q)
{
	// q = len[q] * [v * sin(a/2), cos(a/2)] = [x, y, z, w]
	// cos(a/2)^2 = w^2 / (x^2 + y^2 + z^2 + w^2)
	// sin(a/2)^2 = (x^2 + y^2 + z^2) / (x^2 + y^2 + z^2 + w^2)
	// cos(a) = cos(a/2)^2 - sin(a/2)^2 = (w^2 - x^2 - y^2 - z^2)  / (x^2 + y^2 + z^2 + w^2)
	const typename hkRealTypes<FT>::Scalar sinSq	= q.getImag().template lengthSquared<3>();		// (x^2 + y^2 + z^2)
	typename hkRealTypes<FT>::Scalar cosSq;		cosSq.setMul(q.getRealPart(), q.getRealPart());		// (w^2)
	typename hkRealTypes<FT>::Scalar lenSq;		lenSq.setAdd(sinSq, cosSq);							// (x^2 + y^2 + z^2 + w^2)
	typename hkRealTypes<FT>::Scalar cosA;		cosA.setSub(cosSq, sinSq);							// (w^2 - w^2 - x^2 - y^2 - z^2)
												cosA.div(lenSq);									// (w^2 - w^2 - x^2 - y^2 - z^2) / (x^2 + y^2 + z^2 + w^2)
	return cosA;
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
