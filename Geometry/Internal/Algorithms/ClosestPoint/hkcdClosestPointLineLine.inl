/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

HK_FORCE_INLINE hkBool32 hkcdClosestPointLineLine(hkVector4Parameter A, hkVector4Parameter dA, hkVector4Parameter B, hkVector4Parameter dB, 
												hkSimdReal& t, hkSimdReal &u)
{
	
	hkVector4 d12; d12.setSub(B,A);
	hkSimdReal R = dA.dot<3>(dB);

	hkSimdReal S1 = dA.dot<3>(d12);
	hkSimdReal S2 = dB.dot<3>(d12);

	hkSimdReal D1 = dA.dot<3>(dA);
	hkSimdReal D2 = dB.dot<3>(dB);

	HK_ASSERT2(0x7b0f0426, D1.getReal() > 0 && D2.getReal() > 0, "edge lengths must be nonzero");

	// denom == 0 means the lines are parallel
	hkSimdReal numer = (S1 * D2 - S2 * R);
	hkSimdReal denom = D1 * D2 - R * R;

	
	hkSimdReal epsFactor = hkSimdReal_Eps;
	epsFactor.add(epsFactor); //2e
	epsFactor.add(epsFactor); //4e
	epsFactor.add(epsFactor); //8e
	
	hkSimdReal epsilon = (D1 * D2 + R * R) * epsFactor;

	// We can't use the trick or relying on the clamp in seg-seg to handle parallel lines.
	// If we are parallel, we arbitrarily choose t=1
	hkVector4Comparison mask = denom.greater(epsilon);
	hkSimdReal safeDenom; safeDenom.setSelect(mask, denom, numer);

	t = numer / safeDenom;
	u = (t * R - S2) / D2;

	return mask.anyIsSet();
}

HK_FORCE_INLINE void hkcdClosestPointLineLine(const hkFourTransposedPoints& A, const hkFourTransposedPoints& dA, hkVector4Parameter B, hkVector4Parameter dB, 
											   hkVector4& t, hkVector4& u)
{
	hkFourTransposedPoints d12; d12.setSub(B, A);
	hkVector4 R; dA.dot3(dB, R);

	hkVector4 S1; dA.dot3(d12, S1);
	hkVector4 S2; d12.dot3(dB, S2);

	hkVector4 D1; dA.dot3(dA, D1);
	hkVector4 D2; D2.setAll(dB.dot<3>(dB));

	// Step 1, compute D1, D2, R and the denominator.
	// The cases (a), (b) and (c) are covered in Steps 2, 3 and 4 as
	// checks for division by zero.

	hkVector4 D1D2; D1D2.setMul(D1, D2);
	hkVector4 RSqr; RSqr.setMul(R, R);
	hkVector4 denom; denom.setSub(D1D2, RSqr);
	
	D1D2.setAbs(D1D2);
	hkVector4 epsConst = hkVector4::getConstant<HK_QUADREAL_EPS>();
	const hkSimdReal eight = hkSimdReal::fromFloat(8.0f);
	epsConst.mul(eight);
	
	hkVector4 eps; eps.setAdd(D1D2, RSqr);
	eps.mul(epsConst);

	hkVector4 denomAbs; denomAbs.setAbs(denom);
	hkVector4Comparison mask = denomAbs.greater(eps);
	t.setMul(S1, D2);
	t.setSubMul(t, S2, R);
	t.div(denom);
	t.zeroIfFalse(mask);

	// Step 2
	u.setMul(t, R);
	u.sub(S2);
	u.div(D2);
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
