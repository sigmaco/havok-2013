/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

HK_FORCE_INLINE void hkQsTransformf::setIdentity()
{
	m_translation.setZero();
	m_rotation.setIdentity();
	m_scale = hkVector4f::getConstant<HK_QUADREAL_1>();
}

HK_FORCE_INLINE void hkQsTransformf::setZero()
{
	m_translation.setZero();
	m_rotation.m_vec.setZero();
	m_scale.setZero();
}

HK_FORCE_INLINE const hkVector4f& hkQsTransformf::getTranslation() const
{
	return m_translation;
}

HK_FORCE_INLINE void hkQsTransformf::setTranslation(hkVector4fParameter t)
{
	m_translation = t;
}

HK_FORCE_INLINE const hkQuaternionf& hkQsTransformf::getRotation() const
{
	return m_rotation;
}

HK_FORCE_INLINE void hkQsTransformf::setRotation(const hkRotationf& rotation)
{	
	m_rotation.set(rotation);
}

HK_FORCE_INLINE void hkQsTransformf::setRotation(hkQuaternionfParameter rotation)
{
	m_rotation = rotation;
}

HK_FORCE_INLINE const hkVector4f& hkQsTransformf::getScale() const
{
	return m_scale;
}

HK_FORCE_INLINE void hkQsTransformf::setScale(hkVector4fParameter s)
{
	m_scale = s;
}

#ifndef HK_DISABLE_MATH_CONSTRUCTORS

HK_FORCE_INLINE hkQsTransformf::hkQsTransformf(const hkQsTransformf& t)
{
	m_translation = t.m_translation;
	m_rotation = t.m_rotation;
	m_scale = t.m_scale;
}

HK_FORCE_INLINE hkQsTransformf::hkQsTransformf( IdentityInitializer /*init*/ )
{
	setIdentity();
}

HK_FORCE_INLINE hkQsTransformf::hkQsTransformf( ZeroInitializer /*init*/ )
{
	setZero();
}

HK_FORCE_INLINE hkQsTransformf::hkQsTransformf(hkVector4fParameter translation, hkQuaternionfParameter rotation, hkVector4fParameter scale)
:	m_translation(translation), m_rotation(rotation), m_scale(scale)
{
}

HK_FORCE_INLINE hkQsTransformf::hkQsTransformf(hkVector4fParameter translation, hkQuaternionfParameter rotation)
:	m_translation(translation), m_rotation(rotation)
{
	m_scale = hkVector4f::getConstant<HK_QUADREAL_1>();
}

#endif

HK_FORCE_INLINE void hkQsTransformf::set(hkVector4fParameter translation, hkQuaternionfParameter rotation, hkVector4fParameter scale)
{
	m_translation = translation;
	m_rotation = rotation;
	m_scale = scale;
}

HK_FORCE_INLINE void hkQsTransformf::set(hkVector4fParameter translation, hkQuaternionfParameter rotation)
{
	m_translation = translation;
	m_rotation = rotation;
	m_scale = hkVector4f::getConstant<HK_QUADREAL_1>();
}

HK_FORCE_INLINE /*static*/ const hkQsTransformf& HK_CALL hkQsTransformf::getIdentity()
{
	extern hkFloat32 hkQsTransformf_identityStorage[];
	union { const hkFloat32* r; const hkQsTransformf* q; } r2q;
	r2q.r = hkQsTransformf_identityStorage;
	return *r2q.q;
}

HK_FORCE_INLINE void hkQsTransformf::setInverse( const hkQsTransformf& t )
{
	// We are not "reference-safe" because quaternion inversion is not reference-safe
	HK_MATH_ASSERT(0x1acceb8d, (&t != this) , "Using unsafe references in math operation");

	m_translation.setRotatedInverseDir(t.m_rotation, t.m_translation);
	m_translation.setNeg<4>(m_translation);
	m_rotation.setInverse(t.m_rotation);

	m_scale.setReciprocal(t.m_scale); 
	
	m_scale.zeroComponent<3>();
}

HK_FORCE_INLINE void hkQsTransformf::setInterpolate4( const hkQsTransformf& a, const hkQsTransformf& b, hkSimdFloat32Parameter t)
{
	m_scale.setInterpolate(a.m_scale, b.m_scale, t);
	m_translation.setInterpolate(a.m_translation, b.m_translation, t);

	const hkSimdFloat32 oneMinusT = hkSimdFloat32::getConstant<HK_QUADREAL_1>() - t;

	// Check quaternion polarity
	hkVector4fComparison lessZero = a.m_rotation.m_vec.dot<4>(b.m_rotation.m_vec).lessZero();
	hkSimdFloat32 signedT; signedT.setFlipSign(t, lessZero);

	hkQuaternionf rot;
	rot.m_vec.setMul( signedT, b.m_rotation.m_vec);
	rot.m_vec.addMul( oneMinusT, a.m_rotation.m_vec);
	rot.normalize();

	m_rotation = rot;
}

/*
** Blending stuff
*/

HK_FORCE_INLINE void hkQsTransformf::blendAddMul(const hkQsTransformf& other, hkSimdFloat32Parameter weight)
{
	m_translation.addMul(weight, other.m_translation);
	m_scale.addMul(weight, other.m_scale);

	// Check quaternion polarity
	const hkVector4fComparison ltz = m_rotation.m_vec.dot<4>(other.m_rotation.m_vec).lessZero();
	hkVector4f polarityRotation; polarityRotation.setFlipSign( other.m_rotation.m_vec, ltz );
	m_rotation.m_vec.addMul(weight, polarityRotation);
}

HK_FORCE_INLINE void hkQsTransformf::blendAddMul(const hkQsTransformf& other)
{
	// Weight = 1
	m_translation.add(other.m_translation);
	m_scale.add(other.m_scale);

	// Check quaternion polarity
	const hkVector4fComparison ltz = m_rotation.m_vec.dot<4>(other.m_rotation.m_vec).lessZero();
	hkVector4f polarityRotation; polarityRotation.setFlipSign( other.m_rotation.m_vec, ltz );
	m_rotation.m_vec.add(polarityRotation);
}

HK_FORCE_INLINE void hkQsTransformf::blendWeight(hkSimdFloat32Parameter weight )
{
	m_translation.mul(weight);
	m_scale.mul(weight);
	m_rotation.m_vec.mul(weight);
}

HK_FORCE_INLINE void hkQsTransformf::blendNormalize( hkSimdFloat32Parameter totalWeight )
{
	const hkSimdFloat32 eps = hkSimdFloat32::getConstant<HK_QUADREAL_EPS>();

	// If weight is almost zero, blend is identity
	hkSimdFloat32 absWeight; absWeight.setAbs(totalWeight);
	if ( absWeight < eps )
	{
		setIdentity();
		return;
	}

	// If weight is almost one, we don't blend our translation and scale
	// otherwise, weight all accumulators by inverse
	{
		hkSimdFloat32 invWeight; invWeight.setReciprocal<HK_ACC_23_BIT,HK_DIV_SET_ZERO_AND_ONE>(totalWeight);
		m_translation.mul(invWeight);
		m_scale.mul(invWeight);
	}

	// Now, check for the special cases

	// Rotation
	{
		const hkSimdFloat32 quatNorm = m_rotation.m_vec.lengthSquared<4>();
		hkQuaternionf normRotation = m_rotation; normRotation.normalize();

		// no rotations blended (or canceled each other) -> set to identity
		m_rotation.m_vec.setSelect(quatNorm.less(eps), hkVector4f::getConstant<HK_QUADREAL_0001>(), normRotation.m_vec);
	}

	// Scale
	{
		// no scale blended (or scale canceled each other) -> set to identity
		const hkSimdFloat32 scaleNorm = m_scale.lengthSquared<3>();
		const hkVector4fComparison smallScale = scaleNorm.less(eps);
		m_scale.setSelect(smallScale, hkVector4f::getConstant<HK_QUADREAL_1>(), m_scale);
	}
}

HK_FORCE_INLINE void hkQsTransformf::blendNormalize()
{
	const hkSimdFloat32 eps = hkSimdFloat32::getConstant<HK_QUADREAL_EPS>();

	// Weight = 1, so just check for the special cases

	// Rotation
	{
		const hkSimdFloat32 quatNorm = m_rotation.m_vec.lengthSquared<4>();
		hkQuaternionf normRotation = m_rotation; normRotation.normalize();

		// no rotations blended (or canceled each other) -> set to identity
		m_rotation.m_vec.setSelect(quatNorm.less(eps), hkVector4f::getConstant<HK_QUADREAL_0001>(), normRotation.m_vec);
	}

	// Scale
	{
		// no scale blended (or scale canceled each other) -> set to identity
		const hkSimdFloat32 scaleNorm = m_scale.lengthSquared<3>();
		const hkVector4fComparison smallScale = scaleNorm.less(eps);
		m_scale.setSelect(smallScale, hkVector4f::getConstant<HK_QUADREAL_1>(), m_scale);
	}
}

HK_FORCE_INLINE void hkQsTransformf::fastRenormalize( hkSimdFloat32Parameter totalWeight )
{
	hkSimdFloat32 invWeight; invWeight.setReciprocal(totalWeight);

	m_translation.mul(invWeight);

	m_scale.mul(invWeight);

	m_rotation.normalize();
}

HK_FORCE_INLINE void hkQsTransformf::fastRenormalize()
{
	m_rotation.normalize();
}

// aTc = aTb * bTc
HK_FORCE_INLINE void hkQsTransformf::setMul( const hkQsTransformf& aTb, const hkQsTransformf& bTc )
{
	// Rotation and position go together
	hkVector4f extraTrans;	
	extraTrans._setRotatedDir(aTb.m_rotation, bTc.m_translation);
	m_translation.setAdd(aTb.m_translation, extraTrans);
	m_rotation.setMul(aTb.m_rotation, bTc.m_rotation);

	// Scale goes apart
	m_scale.setMul(aTb.m_scale, bTc.m_scale);
}

// T3 = T1 * T2
HK_FORCE_INLINE void hkQsTransformf::setMulScaled( const hkQsTransformf& T1, const hkQsTransformf& T2 )
{
	// basic affine transform:
	//   T(x) = RSx+t
	//
	// composite transform:
	//    T1(T2(x)) = R1 S1(R2 S2 x + t2) + t1 
	//              = R1 S1 R2 S2 x + R1 S1 t2 + t1
	//                -----\/----     ------\/-----
	//                    R3S3              t3
	// If S1 only contains uniform scaling, skewing is 
	// avoided and the new transform becomes R1 R2 S1 S2. 
	// We assume S1 is uniform scaling, even though it may
	// not be.

	// translational part of new transform
	hkVector4f translation;
	translation.setMul(T1.m_scale,T2.m_translation);
	translation._setRotatedDir(T1.m_rotation, translation);
	translation.add(T1.m_translation);

	// rotational part
	hkQuaternionf rotation;
	rotation.setMul(T1.m_rotation, T2.m_rotation);

	// scaling part (assume T1 is uniform scaling)
	hkVector4f scale;
	scale.setMul(T1.m_scale, T2.m_scale);

	m_translation = translation;
	m_rotation = rotation;
	m_scale = scale;
}

HK_FORCE_INLINE void hkQsTransformf::setMulInverseMul( const hkQsTransformf& a, const hkQsTransformf &b )
{
	hkQsTransformf h;
	h.setInverse( a );
	setMul(h, b);
}

HK_FORCE_INLINE void hkQsTransformf::setMulMulInverse( const hkQsTransformf &a, const hkQsTransformf &b )
{
	hkQsTransformf h;
	h.setInverse( b );
	setMul( a, h);	
}

HK_FORCE_INLINE void hkQsTransformf::setMulEq( const hkQsTransformf& b )
{
	// We are not "reference-safe" because quaternion multiplication is not reference-safe
	HK_MATH_ASSERT(0x1acceb8d, (&b!=this) , "Using unsafe references in math operation");

	// Rotation and position go together
	hkVector4f extraTrans;
	extraTrans._setRotatedDir(m_rotation, b.m_translation);
	m_translation.add(extraTrans);
	m_rotation.mul(b.m_rotation);

	// Scale goes apart
	m_scale.mul(b.m_scale);
}

HK_FORCE_INLINE hkBool32 hkQsTransformf::isScaleUniform() const
{
	hkVector4f scaleX; scaleX.setAll(m_scale.getComponent<0>());
	return m_scale.allExactlyEqual<3>(scaleX);
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
