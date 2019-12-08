/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// construction

HK_FORCE_INLINE const hkVector4d& hkQuaterniond::getImag() const
{
	return m_vec;
}

HK_FORCE_INLINE void hkQuaterniond::setImag(hkVector4dParameter i)
{
	m_vec.setXYZ(i);
}


HK_FORCE_INLINE hkDouble64 hkQuaterniond::getReal() const
{
	return m_vec(3);
}

HK_FORCE_INLINE void hkQuaterniond::setReal(hkDouble64 r)
{
	m_vec(3) = r;
}

HK_FORCE_INLINE const hkSimdDouble64 hkQuaterniond::getRealPart() const
{
	return m_vec.getComponent<3>();
}

HK_FORCE_INLINE void hkQuaterniond::setRealPart(hkSimdDouble64Parameter r)
{
	m_vec.setComponent<3>(r);
}

#ifndef HK_DISABLE_MATH_CONSTRUCTORS
HK_FORCE_INLINE hkQuaterniond::hkQuaterniond(const hkRotationd& r)
{
	set(r);
}

HK_FORCE_INLINE hkQuaterniond::hkQuaterniond(hkDouble64 x, hkDouble64 y, hkDouble64 z, hkDouble64 w)
{
	set(x,y,z,w);
}

HK_FORCE_INLINE hkQuaterniond::hkQuaterniond(hkSimdDouble64Parameter x, hkSimdDouble64Parameter y, hkSimdDouble64Parameter z, hkSimdDouble64Parameter w)
{
	set(x,y,z,w);
}

HK_FORCE_INLINE hkQuaterniond::hkQuaterniond(hkVector4dParameter axis, hkDouble64 angle)
{
	setAxisAngle(axis,angle);
}
#endif

HK_FORCE_INLINE void hkQuaterniond::operator= (const hkQuaterniond& q)
{
	m_vec = q.m_vec;
}

HK_FORCE_INLINE void hkQuaterniond::set(hkDouble64 x, hkDouble64 y, hkDouble64 z, hkDouble64 w)
{
	m_vec.set(x,y,z,w);
	HK_MATH_ASSERT(0x1adaad0e,  isOk(), "hkQuaterniond components were not normalized." );
}

HK_FORCE_INLINE void hkQuaterniond::set(hkSimdDouble64Parameter x, hkSimdDouble64Parameter y, hkSimdDouble64Parameter z, hkSimdDouble64Parameter w)
{
	m_vec.set(x,y,z,w);
	HK_MATH_ASSERT(0x1adaad0e,  isOk(), "hkQuaterniond components were not normalized." );
}

HK_FORCE_INLINE void hkQuaterniond::setIdentity()
{
	m_vec = hkVector4d::getConstant<HK_QUADREAL_0001>();
}

HK_FORCE_INLINE /*static*/ const hkQuaterniond& HK_CALL hkQuaterniond::getIdentity()
{
	union { const hkQuadDouble64* r; const hkQuaterniond* q; } r2q;
	r2q.r = g_vectordConstants + HK_QUADREAL_0001;
	return *r2q.q;
}

HK_FORCE_INLINE void hkQuaterniond::setMul(hkSimdDouble64Parameter r, hkQuaterniondParameter q)
{
	m_vec.setMul(q.m_vec, r);
}

HK_FORCE_INLINE void hkQuaterniond::addMul(hkSimdDouble64Parameter r, hkQuaterniondParameter q)
{
	m_vec.addMul(r,q.m_vec);
}

HK_FORCE_INLINE void hkQuaterniond::setMul(hkQuaterniondParameter q0, hkQuaterniondParameter q1)
{
	const hkVector4d q0Imag = q0.getImag();
	const hkVector4d q1Imag = q1.getImag();
	const hkSimdDouble64 q0Real = q0.getRealPart();
	const hkSimdDouble64 q1Real = q1.getRealPart();

	hkVector4d vec;
	vec.setCross(q0Imag, q1Imag);
	vec.addMul(q0Real, q1Imag);
	vec.addMul(q1Real, q0Imag);
	const hkSimdDouble64 w = (q0Real * q1Real) - q0Imag.dot<3>(q1Imag);
	m_vec.setXYZ_W(vec, w);
}


HK_FORCE_INLINE void hkQuaterniond::mul(hkQuaterniondParameter q)
{
	const hkVector4d thisImag = getImag();
	const hkVector4d qImag = q.getImag();
	const hkSimdDouble64 thisReal = getRealPart();
	const hkSimdDouble64 qReal = q.getRealPart();

	hkVector4d vec;
	vec.setCross(thisImag, qImag);
	vec.addMul(thisReal, qImag);
	vec.addMul(qReal, thisImag);
	const hkSimdDouble64 w = (thisReal * qReal) - thisImag.dot<3>(qImag);
	m_vec.setXYZ_W(vec, w);
}

HK_FORCE_INLINE void hkQuaterniond::setMulInverse(hkQuaterniondParameter q0, hkQuaterniondParameter q1)
{
	const hkVector4d q0Imag = q0.getImag();
	const hkVector4d q1Imag = q1.getImag();

	hkVector4d xyz; 
	xyz.setCross(q1Imag, q0Imag);
	xyz.subMul(q0.getRealPart(), q1Imag);
	xyz.addMul(q1.getRealPart(), q0Imag);
	const hkSimdDouble64 w = q0Imag.dot<4>(q1Imag);
	m_vec.setXYZ_W(xyz, w);
}

HK_FORCE_INLINE void hkQuaterniond::setInverseMul(hkQuaterniondParameter q0, hkQuaterniondParameter q1)
{
	const hkVector4d q0Imag = q0.getImag();
	const hkVector4d q1Imag = q1.getImag();

	hkVector4d xyz; 
	xyz.setCross(q1Imag, q0Imag);
	xyz.addMul(q0.getRealPart(), q1Imag);
	xyz.subMul(q1.getRealPart(), q0Imag);
	const hkSimdDouble64 w = q0Imag.dot<4>(q1Imag);
	m_vec.setXYZ_W(xyz,w);
}

HK_FORCE_INLINE void hkQuaterniond::estimateAngleTo(hkQuaterniondParameter to, hkVector4d& angleOut) const
{
	const hkVector4d fromImag = getImag();
	const hkVector4d toImag = to.getImag();

	hkVector4d angle;
	angle.setCross(fromImag, toImag);
	angle.subMul(to.getRealPart(), fromImag);
	angle.addMul(   getRealPart(), toImag);
	angle.add(angle);
	angleOut.setFlipSign( angle, toImag.dot<4>(fromImag) );
}


HK_FORCE_INLINE void hkQuaterniond::setInverse( hkQuaterniondParameter q )
{
	m_vec.setNeg<3>( q.getImag() );
}

HK_FORCE_INLINE const hkDouble64& hkQuaterniond::operator()(int i) const
{
	return m_vec(i);
}

template <int I> 
HK_FORCE_INLINE const hkSimdDouble64 hkQuaterniond::getComponent() const
{
	return m_vec.getComponent<I>(); // has asserts
}

HK_FORCE_INLINE hkDouble64 hkQuaterniond::getAngle() const
{
	hkSimdDouble64 absangle; absangle.setAbs(m_vec.getComponent<3>());
#if defined(HK_PLATFORM_WIN32) && (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED) && !defined(HK_ARCH_ARM)
	hkSimdDouble64 angle;

	angle.m_real = hkMath::twoAcos(absangle.m_real);

	angle.mul(hkSimdDouble64_2);
	return angle.getReal();
#else
	hkDouble64 angle = hkMath::acos(absangle.getReal());
	return angle * hkDouble64(2);
#endif
}

HK_FORCE_INLINE hkBool32 hkQuaterniond::hasValidAxis() const
{
	return m_vec.lengthSquared<3>().isGreater(hkSimdDouble64::getConstant<HK_QUADREAL_EPS_SQRD>());
}

HK_FORCE_INLINE void hkQuaterniond::getAxis(hkVector4d &axisOut) const
{
	hkVector4d axisTmp = m_vec;

	HK_MATH_ASSERT(0x266e2bd7, hasValidAxis(), "Cannot extract axis from a Quaternion representing (within numerical tolerance) the Identity rotation (or Quaternion may not be normalized).");
	axisTmp.normalize<3>();

#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	const hkVector4dComparison wLessZero = m_vec.getComponent<3>().lessZero();
	axisOut.setFlipSign(axisTmp, wLessZero);
#else
	if(m_vec(3) < hkDouble64(0))
	{
		axisOut.setNeg<4>(axisTmp);
	}
	else
	{
		axisOut = axisTmp;
	}
#endif
}

//
//	Sets the quaternion to the given quaternion, eventually transforming it so they are in the same hemisphere

HK_FORCE_INLINE void hkQuaterniond::setClosest(hkQuaterniondParameter q, hkQuaterniondParameter qReference)
{
	m_vec.setFlipSign(q.m_vec, qReference.m_vec.dot<4>(q.m_vec));
}

//
//	HK_FORCE_INLINEd. Sets/initializes this quaternion from a given rotation matrix.
//	The rotation r must be orthonormal.

HK_FORCE_INLINE void hkQuaternion_setFromRotationSimd(const hkRotationd& r, hkVector4d& vec)
{
	HK_ALIGN_DOUBLE(const hkDouble64 pmmp[4]) = {  1, -1, -1,  1 };
	HK_ALIGN_DOUBLE(const hkDouble64 mpmp[4]) = { -1,  1, -1,  1 };
	HK_ALIGN_DOUBLE(const hkDouble64 mmpp[4]) = { -1, -1,  1,  1 };

	// Get constants
	const hkSimdDouble64 half = hkSimdDouble64::getConstant(HK_QUADREAL_INV_2);
	// Trace setup
	const hkSimdDouble64 m00 = r.getElement<0,0>();
	const hkSimdDouble64 m11 = r.getElement<1,1>();
	const hkSimdDouble64 m22 = r.getElement<2,2>();

#ifdef HK_DEBUG
	hkDouble64 t = (m00+m11+m22).getReal();
	HK_MATH_ASSERT(0x23957faa, t > -1, "The matrix is not special orthogonal (=has a reflection component).");
#endif

	hkVector4d trace = hkVector4d::getConstant<HK_QUADREAL_1>();
	trace.addMul(m00, *(const hkVector4d*)&pmmp);
	trace.addMul(m11, *(const hkVector4d*)&mpmp);
	trace.addMul(m22, *(const hkVector4d*)&mmpp);

	// Calculate quaternion using the traces
	hkVector4d root;
	root.setSqrt<HK_ACC_23_BIT,HK_SQRT_SET_ZERO>(trace);
	root.mul(half); 

	// Fix reflections
	hkVector4d rotSigns;
	rotSigns.set( r.getElement<2,1>() - r.getElement<1,2>(),
				  r.getElement<0,2>() - r.getElement<2,0>(),
				  r.getElement<1,0>() - r.getElement<0,1>(),
				  half );

	vec.setFlipSign(root, rotSigns);
}

//
//	HK_FORCE_INLINEd. Sets/initializes this quaternion from a given rotation matrix.
//	The rotation r must be orthonormal.

HK_FORCE_INLINE void hkQuaternion_setFromRotationFpu(const hkRotationd& r, hkVector4d& vec)
{
	const hkDouble64 trace = r(0,0) + r(1,1) + r(2,2);
	const hkDouble64 half = hkDouble64(0.5f);

	// This is an exceptional case:
	// if trace==-1.0 since this means real=sqrt(trace+1) =0.0
	// hence we can't use real to compute the imaginary terms
	// if trace is close to -1.0, then the normal algorithm is
	// subject to numerical error.
	// Either way, we should use an alternate algorithm.
	// Please see doc "Numerical Problem In Quaternion-Matrix Conversion.doc"

	HK_ALIGN_DOUBLE(hkDouble64 v[4]);
	if( trace > hkDouble64(0) )
	{
		// else we calculate simply:
		hkDouble64 s = hkMath::sqrt( trace + hkDouble64(1) );
		hkDouble64 t = half / s;
		v[0] = (r(2,1)-r(1,2)) * t;
		v[1] = (r(0,2)-r(2,0)) * t;
		v[2] = (r(1,0)-r(0,1)) * t;
		v[3] = half * s;
	}
	else
	{
		const int next[] = {1,2,0};
		int i=0;

		if(r(1,1) > r(0,0)) i=1;
		if(r(2,2) > r(i,i)) i=2;

		int j = next[i];
		int k = next[j];

		hkDouble64 s = hkMath::sqrt(r(i,i) - (r(j,j)+r(k,k)) + hkDouble64(1));
		hkDouble64 t = half / s;

		v[i] = half * s;
		v[3] = (r(k,j)-r(j,k)) * t;
		v[j] = (r(j,i)+r(i,j)) * t;
		v[k] = (r(k,i)+r(i,k)) * t;
	}

	vec.load<4>(v);
}

//
//	HK_FORCE_INLINEd. Sets/initializes this quaternion from a given rotation matrix.
//	The rotation r must be orthonormal.

HK_FORCE_INLINE void hkQuaterniond::_set(const hkRotationd& r)
{

	hkQuaternion_setFromRotationFpu(r, m_vec);


	// Note: we don't renormalize here as we assume the rotation is orthonormal
	// <pk.todo> this assert breaks setAndNormalize method.
	// HK_MATH_ASSERT(0x70dc41cb, isOk(), "hkRotationd used for hkQuaterniond construction is invalid. hkQuaterniond is not normalized/invalid!");
}

template <hkMathAccuracyMode A, hkMathNegSqrtMode S>
HK_FORCE_INLINE void hkQuaterniond::setAndNormalize(const hkRotationd& r)
{
	_set(r);
	normalize<A,S>();
	HK_MATH_ASSERT(0x70dc41cc, isOk(), "hkRotationd used for hkQuaterniond construction is invalid.");
}

HK_FORCE_INLINE void hkQuaterniond::setAndNormalize(const hkRotationd& r)
{
	_set(r);
	normalize<HK_ACC_23_BIT,HK_SQRT_IGNORE>();
	HK_MATH_ASSERT(0x70dc41cc, isOk(), "hkRotationd used for hkQuaterniond construction is invalid.");
}

template <hkMathAccuracyMode A, hkMathNegSqrtMode S>
HK_FORCE_INLINE void hkQuaterniond::normalize()
{
	m_vec.normalize<4,A,S>();
}

HK_FORCE_INLINE void hkQuaterniond::normalize()
{
	m_vec.normalize<4,HK_ACC_23_BIT,HK_SQRT_IGNORE>();
}

//
//	Sets this = Slerp(q0, q1, t)
#define HK_ONE_MINUS_QUATERNIONd_DELTA hkDouble64(1.0f - 1e-3f)

HK_FORCE_INLINE void hkQuaterniond::_setSlerp(hkQuaterniondParameter q0, hkQuaterniondParameter q1, hkSimdDouble64Parameter t)
{
	const hkSimdDouble64 one = hkSimdDouble64::getConstant<HK_QUADREAL_1>();
	hkSimdDouble64 qdelta; qdelta.setFromFloat(HK_ONE_MINUS_QUATERNIONd_DELTA);

	hkSimdDouble64 cosTheta = q0.m_vec.dot<4>(q1.m_vec);

	// If B is on the opposite hemisphere use -B instead of B
	const hkVector4dComparison cosThetaLessZero = cosTheta.lessZero();
	cosTheta.setFlipSign(cosTheta, cosThetaLessZero);

	hkSimdDouble64 t0,t1;

	if (cosTheta < qdelta)
	{
		hkSimdDouble64 theta; 
#if defined(HK_PLATFORM_WIN32) && (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED) && !defined(HK_ARCH_ARM)
		theta.m_real = hkMath::twoAcos(cosTheta.m_real);
#else
		theta.setFromFloat( hkMath::acos(cosTheta.getReal()) );
#endif

		// use sqrtInv(1+c^2) instead of 1.0/sin(theta) 
		const hkSimdDouble64 iSinTheta = ( one - (cosTheta*cosTheta) ).sqrtInverse<HK_ACC_23_BIT,HK_SQRT_IGNORE>();
		const hkSimdDouble64 tTheta = t * theta;

		hkSimdDouble64 s0,s1; 
#if defined(HK_PLATFORM_WIN32) && (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED) && !defined(HK_ARCH_ARM)
		hkVector4d ss; ss.set(theta-tTheta, tTheta, tTheta, tTheta);
		hkVector4d s01; 
		s01.m_quad.xy = hkMath::twoSin(ss.m_quad.xy);
		s0 = s01.getComponent<0>();
		s1 = s01.getComponent<1>();
#else
		s0.setFromFloat(hkMath::sin((theta-tTheta).getReal()));
		s1.setFromFloat(hkMath::sin(tTheta.getReal()));
#endif
		t0 = s0 * iSinTheta;
		t1 = s1 * iSinTheta;
	}
	else
	{
		// If q0 is nearly the same as q1 we just linearly interpolate
		t0 = one - t;
		t1 = t;
	}	

	t1.setFlipSign(t1, cosThetaLessZero);

	hkVector4d slerp;
	slerp.setMul( t0, q0.m_vec);
	slerp.addMul( t1, q1.m_vec);
	slerp.normalize<4>();

	m_vec = slerp;
}
#undef HK_ONE_MINUS_QUATERNIONd_DELTA

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
