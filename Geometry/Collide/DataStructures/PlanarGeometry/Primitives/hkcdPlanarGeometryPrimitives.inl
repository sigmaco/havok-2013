/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

//
//	Gets / Sets the fixed-precision normal

HK_FORCE_INLINE void hkcdPlanarGeometryPrimitives::Plane::getExactNormal(hkInt64Vector4& iNormalOut) const
{
	const int nShr = 64 - NumBitsPlaneNormal::NUM_BITS;
	iNormalOut.setShiftRight<nShr, HK_VALUE_SIGNED>(m_iEqn);
}

HK_FORCE_INLINE void hkcdPlanarGeometryPrimitives::Plane::setExactNormal(hkInt64Vector4Parameter iNormalIn)
{
	// Make sure the .w component is zero
	hkInt64Vector4 vN = iNormalIn;
	vN.zeroComponent<3>();
	const int nShl = 64 - NumBitsPlaneNormal::NUM_BITS;
	m_iEqn.setShiftLeft<nShl>(vN);
}

//
//	Gets / Sets the fixed-precision offset

HK_FORCE_INLINE void hkcdPlanarGeometryPrimitives::Plane::getExactOffset(hkSimdInt<128>& iOffsetOut) const
{
	const int nSh = 128 - NumBitsPlaneOffset::NUM_BITS;
	hkSimdInt<128> iO;	m_iEqn.storeZw(iO);
	iO.setShiftLeft<nSh>(iO);	// At this point, we have the sign bit in position 127
	iOffsetOut.setShiftRight<nSh, HK_VALUE_SIGNED>(iO);
}

HK_FORCE_INLINE void hkcdPlanarGeometryPrimitives::Plane::setExactOffset(const hkSimdInt<128>& iOffsetIn)
{
	// Zero the top bits so we can store the offset in the same vector
	const int nSh = 128 - NumBitsPlaneOffset::NUM_BITS;
	hkSimdInt<128> iO;	iO.setShiftLeft<nSh>(iOffsetIn);
						iO.setShiftRight<nSh>(iO);
	hkSimdInt<128> zw;	m_iEqn.storeZw(zw);
						iO.setOr(zw, iO);
	m_iEqn.loadZw(iO);
}

//
//	Sets the exact plane equation

HK_FORCE_INLINE void hkcdPlanarGeometryPrimitives::Plane::setExactEquation(hkInt64Vector4Parameter iNormalIn, const hkSimdInt<128>& iOffsetIn)
{
	setExactNormal(iNormalIn);
	setExactOffset(iOffsetIn);

#if ( ENABLE_HKCD_PLANAR_GEOMETRY_DEBUG_CHECKS )
	{
		hkInt64Vector4 iN;	getExactNormal(iN);
		hkSimdInt<128> iO;	getExactOffset(iO);
		HK_ASSERT(0x6a30edf2, iN.equal(iNormalIn).horizontalAnd<3>().anyIsSet() && iO.equal(iOffsetIn).anyIsSet());
	}
#endif

	simplify();
	computeApproxEquation();
}

//
//	Computes a plane in the opposite direction of the given plane

HK_FORCE_INLINE void hkcdPlanarGeometryPrimitives::Plane::setOpposite(const Plane& srcPlane)
{
	hkInt64Vector4 iNrm;		srcPlane.getExactNormal(iNrm);
								iNrm.setNeg<4>(iNrm);
	hkSimdInt<128> iOffset;		srcPlane.getExactOffset(iOffset);
								iOffset.setNeg(iOffset);

	setExactNormal(iNrm);
	setExactOffset(iOffset);
	m_dEqn.setNeg<4>(srcPlane.m_dEqn);
}

//
//	Compares two planes for equality

HK_FORCE_INLINE hkBool32 hkcdPlanarGeometryPrimitives::Plane::isEqual(const Plane& other) const
{
	const hkVector4fComparison cmp = m_iEqn.equal(other.m_iEqn).horizontalAnd<4>();

#if ( ENABLE_HKCD_PLANAR_GEOMETRY_DEBUG_CHECKS )
	{
		hkInt64Vector4 nA;	getExactNormal(nA);
		hkInt64Vector4 nB;	other.getExactNormal(nB);
		hkSimdInt<128> oA;	getExactOffset(oA);
		hkSimdInt<128> oB;	other.getExactOffset(oB);

		hkVector4Comparison cmpN	= nA.equal(nB).horizontalAnd<3>();
		hkVector4Comparison cmpO	= oA.equal(oB);
									cmpO.setAnd(cmpN, cmpO);
									cmpO.setXor(cmpO, cmp);
		HK_ASSERT(0x3c4d65d8, !cmpO.anyIsSet());
	}
#endif

	return cmp.anyIsSet();
}

//
//	Gets / Sets the floating-point equation

HK_FORCE_INLINE const hkVector4d& hkcdPlanarGeometryPrimitives::Plane::getApproxEquation() const
{
	return m_dEqn;
}

//
//	Returns the Id of the opposite plane

HK_FORCE_INLINE hkcdPlanarGeometryPrimitives::PlaneId HK_CALL hkcdPlanarGeometryPrimitives::getOppositePlaneId(PlaneId planeId)
{
	const int pid	= planeId.value() & (~FLIPPED_PLANE_FLAG);
	const int flip	= (planeId.value() ^ FLIPPED_PLANE_FLAG) & FLIPPED_PLANE_FLAG;
	return PlaneId(pid | flip);
}

//
//	Computes the plane passing through 3 vertices

HK_FORCE_INLINE hkResult HK_CALL hkcdPlanarGeometryPrimitives::computePlaneEquation(hkIntVectorParameter vA, hkIntVectorParameter vB, hkIntVectorParameter vC, hkInt64Vector4& normalOut, hkSimdInt<128>& offsetOut)
{
	// Compute edges
	hkIntVector eAB;	eAB.setSubU32(vB, vA);
	hkIntVector eAC;	eAC.setSubS32(vC, vA);

	// Compute normal & plane offset
	normalOut.setCross(eAB, eAC);
	if ( normalOut.equalZero().allAreSet<hkVector4Comparison::MASK_XYZ>() )
	{
		return HK_FAILURE;
	}

	offsetOut.setNeg(normalOut.dot<3>(vA));
	return HK_SUCCESS;
}

//
//	Returns true if the plane Ids are coplanar

HK_FORCE_INLINE bool HK_CALL hkcdPlanarGeometryPrimitives::coplanarPlaneIds(PlaneId planeIdA, PlaneId planeIdB)
{
	const int pidA	= planeIdA.value() & (~FLIPPED_PLANE_FLAG);
	const int pidB	= planeIdB.value() & (~FLIPPED_PLANE_FLAG);
	return pidA == pidB;
}

//
//	Returns true if the plane Ids are coplanar. Note that this only compares the Ids and does not evaluate any geometric predicate.
//	The mesh must be built such that all planes are distinct!

HK_FORCE_INLINE bool HK_CALL hkcdPlanarGeometryPrimitives::sameOrientationPlaneIds(PlaneId planeIdA, PlaneId planeIdB)
{
	return (planeIdA == planeIdB);
}

//
//	Simplifies the fixed-precision equation so that gcd(nx, ny, nz, offset) = 1

HK_FORCE_INLINE void hkcdPlanarGeometryPrimitives::Plane::simplify()
{
	// Get normal and offset
	hkInt64Vector4 iNrm;		getExactNormal(iNrm);
	hkSimdInt<128> iOff;		getExactOffset(iOff);

	// Compute gcd
	hkInt64Vector4 iAbsNrm;		iAbsNrm.setAbs(iNrm);
	const hkUint64 gcdXY		= hkMath::greatestCommonDivisor<hkUint64>(iAbsNrm.getComponent<0>(), iAbsNrm.getComponent<1>());
	hkUint64 gcdXYZ				= hkMath::greatestCommonDivisor<hkUint64>(gcdXY, iAbsNrm.getComponent<2>());
	hkSimdInt<128> iAbsOff;		iAbsOff.setAbs(iOff);
	hkSimdInt<128> gcdXYZO;		gcdXYZO.setFromUint64(gcdXYZ);
								gcdXYZO.setGreatestCommonDivisor(iAbsOff, gcdXYZO);
	
	// Divide everything by gcd
	iAbsOff.setUnsignedDiv(iAbsOff, gcdXYZO);
	hkInt64Vector4 vGcd;	vGcd.loadZw(gcdXYZO);
							vGcd.setPermutation<hkVectorPermutation::WWWW>(vGcd);
	iAbsNrm.setUnsignedDiv(iAbsNrm, vGcd);

	// Set signs and store
	hkInt64Vector4 iScaledNrm;	iScaledNrm.setFlipSign(iAbsNrm, iNrm.lessZero());
	hkSimdInt<128> iScaledOff;	iScaledOff.setFlipSign(iAbsOff, iOff.lessZero());
	setExactNormal(iScaledNrm);
	setExactOffset(iScaledOff);
}

//
//	Recomputes the floating-point equation to match the fixed-precision one within a known eps

HK_FORCE_INLINE void hkcdPlanarGeometryPrimitives::Plane::computeApproxEquation()
{
	// We want to shift everything so we have at least a bit in the highest allowed position
	hkInt64Vector4 iNrm;		getExactNormal(iNrm);
	hkSimdInt<128> iOff;		getExactOffset(iOff);
	hkInt64Vector4 iAbsNrm;		iAbsNrm.setAbs(iNrm);
	hkSimdInt<128> iAbsOff;		iAbsOff.setAbs(iOff);

	// At least one of these is non-zero
	hkIntVector msb;	iAbsNrm.countLeadingZeros<3>(msb);
	const int msbXYZ	= 63 - msb.horizontalMinS32<3>();
	const int msbW		= 127 - iAbsOff.countLeadingZeros();
	const int shlXYZ	= (hkcdPlanarGeometryPrimitives::NumBitsPlaneNormal::NUM_BITS - 1 - 1) - msbXYZ;
	const int shlW		= (hkcdPlanarGeometryPrimitives::NumBitsPlaneOffset::NUM_BITS - 1 - 1) - msbW;
	const int shlXYZW	= hkMath::min2(shlXYZ, shlW);

	// Shift normal and offset so we have at least one MSB != 0.
	iAbsNrm.setShiftLeft(iAbsNrm, shlXYZW);
	iAbsOff.setShiftLeft(iAbsOff, shlXYZW);

	// Convert to double
	{
		const int shl	= 4;
		const int shrN	= shl + NumBitsPlaneNormal::NUM_BITS - 1 - NumBitsMantissaD::NUM_BITS;
		const int shrO	= shl + NumBitsPlaneOffset::NUM_BITS - 1 - NumBitsMantissaD::NUM_BITS;

		hkInt64Vector4 nxyzw;		nxyzw.setShiftLeft<shl>(iAbsNrm);
									nxyzw.setShiftRight<shrN>(nxyzw);
		hkSimdInt<128> nw;			nw.setShiftLeft<shl>(iAbsOff);
									nw.setShiftRight<shrO>(nw);
									nxyzw.setComponent<3>(nw.getDoubleWord<0>());

		hkVector4d dEqn;			nxyzw.convertS64ToF64(dEqn);
		const double scaleN			= 1.0 / (double)(hkInt64)(1LL << (hkInt64)NumBitsMantissaD::NUM_BITS);	// 1 / 2^53 = 1 / 9007199254740992
		const double scaleO			= 1.0 / (double)(hkInt64)(1LL << (hkInt64)(NumBitsMantissaD::NUM_BITS + NumBitsPlaneNormal::NUM_BITS - NumBitsPlaneOffset::NUM_BITS));	// 1 / 2^29 = 1 / 2^(25 - (53 + 1)) =  1 / 536870912
		hkVector4d dScale;			dScale.set(scaleN, scaleN, scaleN, scaleO);
									dEqn.mul(dScale);

		// Set proper signs
		hkVector4d dEqnW;		dEqnW.setFlipSign(dEqn, iOff.lessZero<hkVector4dComparison>());
		hkVector4d dEqnN;		dEqnN.setFlipSign(dEqn, iNrm.lessZero<hkVector4dComparison>());
		m_dEqn.setXYZ_W(dEqnN, dEqnW);
	}
}

//
//	Sets the position of this vertex

HK_FORCE_INLINE void hkcdPlanarGeometryPrimitives::Vertex::set(hkIntVectorParameter iPos)
{
	m_iPos = iPos;
	m_dPos.set((hkDouble64)iPos.getComponent<0>(), (hkDouble64)iPos.getComponent<1>(), (hkDouble64)iPos.getComponent<2>(), 0.0);
}

//
//	Returns the fixed precision position

HK_FORCE_INLINE const hkIntVector& hkcdPlanarGeometryPrimitives::Vertex::getExactPosition() const			{	return m_iPos;	}
HK_FORCE_INLINE const hkVector4d& hkcdPlanarGeometryPrimitives::Vertex::getApproxPosition() const			{	return m_dPos;	}

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
