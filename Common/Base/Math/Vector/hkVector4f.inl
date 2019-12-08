/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

HK_FORCE_INLINE void hkVector4f::_setRotatedDir(hkQuaternionfParameter quat, hkVector4fParameter direction)
{
	hkSimdFloat32 qreal = quat.m_vec.getComponent<3>();
	hkSimdFloat32 q2minus1 = qreal*qreal - hkSimdFloat32_Half;

	hkVector4f ret;
	ret.setMul( direction, q2minus1 );

	hkSimdFloat32 imagDotDir = quat.getImag().dot<3>( direction );

	ret.addMul( quat.getImag(), imagDotDir ); 

	hkVector4f imagCrossDir;
	imagCrossDir.setCross( quat.getImag(), direction );
	ret.addMul( imagCrossDir, qreal );

	setAdd( ret, ret );
}

HK_FORCE_INLINE void hkVector4f::_setRotatedInverseDir(hkQuaternionfParameter quat, hkVector4fParameter direction)
{
	hkSimdFloat32 qreal = quat.m_vec.getComponent<3>();
	hkSimdFloat32 q2minus1 = qreal*qreal - hkSimdFloat32_Half;

	hkVector4f ret;
	ret.setMul( direction, q2minus1 );

	hkSimdFloat32 imagDotDir = quat.getImag().dot<3>( direction );

	ret.addMul( quat.getImag(), imagDotDir ); 

	hkVector4f imagCrossDir;
	imagCrossDir.setCross( direction, quat.getImag() );
	ret.addMul( imagCrossDir, qreal );

	setAdd( ret, ret );
}

HK_FORCE_INLINE void hkVector4f::setPlaneConstant(hkVector4fParameter p)
{
	const hkSimdFloat32 w = dot<3>(p);
	setW(-w);
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4f::allExactlyEqual<1>(hkVector4fParameter v) const
{
	return getComponent<0>().isEqual(v.getComponent<0>());
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4f::allExactlyEqual<2>(hkVector4fParameter v) const
{
	return equal(v).allAreSet<hkVector4ComparisonMask::MASK_XY>();
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4f::allExactlyEqual<3>(hkVector4fParameter v) const
{
	return equal(v).allAreSet<hkVector4ComparisonMask::MASK_XYZ>();
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4f::allExactlyEqual<4>(hkVector4fParameter v) const
{
	return equal(v).allAreSet();
}

template <int N>
HK_FORCE_INLINE hkBool32 hkVector4f::allExactlyEqual(hkVector4fParameter v) const
{
	HK_VECTOR4f_NOT_IMPLEMENTED;
	return false;
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4f::allExactlyEqualZero<1>() const
{
	return getComponent<0>().isEqualZero();
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4f::allExactlyEqualZero<2>() const
{
	return equalZero().allAreSet<hkVector4ComparisonMask::MASK_XY>();
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4f::allExactlyEqualZero<3>() const
{
	return equalZero().allAreSet<hkVector4ComparisonMask::MASK_XYZ>();
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4f::allExactlyEqualZero<4>() const
{
	return equalZero().allAreSet();
}

template <int N>
HK_FORCE_INLINE hkBool32 hkVector4f::allExactlyEqualZero() const
{
	HK_VECTOR4f_NOT_IMPLEMENTED;
	return false;
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4f::allComponentsEqual<4>() const
{
	hkVector4f yxwz; yxwz.setPermutation<hkVectorPermutation::YXWZ>(*this);
	const hkVector4fComparison xz_eq_yw = equal(yxwz);

	hkVector4f zwxy; zwxy.setPermutation<hkVectorPermutation::ZWXY>(*this);
	const hkVector4fComparison xy_eq_zw = equal(zwxy);

	hkVector4fComparison all_eq; all_eq.setAnd(xz_eq_yw, xy_eq_zw);
	return all_eq.allAreSet();
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4f::allComponentsEqual<3>() const
{
	hkVector4f yxzw; yxzw.setPermutation<hkVectorPermutation::YXZW>(*this);
	const hkVector4fComparison x_eq_y = equal(yxzw);

	hkVector4f zwxy; zwxy.setPermutation<hkVectorPermutation::ZWXY>(*this);
	const hkVector4fComparison x_eq_z = equal(zwxy);

	hkVector4fComparison x_eq_y_eq_z; x_eq_y_eq_z.setAnd(x_eq_y, x_eq_z);
	return x_eq_y_eq_z.allAreSet<hkVector4ComparisonMask::MASK_X>();
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4f::allComponentsEqual<2>() const
{
	hkVector4f yx; yx.setPermutation<hkVectorPermutation::YXZW>(*this);
	return allExactlyEqual<2>(yx);
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4f::allComponentsEqual<1>() const
{
	return true;
}

template <int N>
HK_FORCE_INLINE hkBool32 hkVector4f::allComponentsEqual() const
{
	HK_VECTOR4f_NOT_IMPLEMENTED;
	return false;
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4f::allEqual<1>(hkVector4fParameter v, hkSimdFloat32Parameter epsilon) const
{
	hkSimdFloat32 t = getComponent<0>() - v.getComponent<0>();
	t.setAbs( t );
	return t.isLess(epsilon);
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4f::allEqual<2>(hkVector4fParameter v, hkSimdFloat32Parameter epsilon) const
{
	// non_euclidean, manhattan based
	hkVector4f t;
	t.setSub(*this, v);
	t.setAbs( t );
	hkVector4f epsilon_v;
	epsilon_v.setAll(epsilon);
	return t.less( epsilon_v ).allAreSet<hkVector4ComparisonMask::MASK_XY>();
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4f::allEqual<3>(hkVector4fParameter v, hkSimdFloat32Parameter epsilon) const
{
	// non_euclidean, manhattan based
	hkVector4f t;
	t.setSub(*this, v);
	t.setAbs( t );
	hkVector4f epsilon_v;
	epsilon_v.setAll(epsilon);
	return t.less( epsilon_v ).allAreSet<hkVector4ComparisonMask::MASK_XYZ>();
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4f::allEqual<4>(hkVector4fParameter v, hkSimdFloat32Parameter epsilon) const
{
	// non_euclidean, manhattan based
	hkVector4f t;
	t.setSub(*this, v);
	t.setAbs( t );
	hkVector4f epsilon_v;
	epsilon_v.setAll(epsilon);
	return t.less( epsilon_v ).allAreSet();
}

template <int N>
HK_FORCE_INLINE hkBool32 hkVector4f::allEqual(hkVector4fParameter v, hkSimdFloat32Parameter epsilon) const
{
	HK_VECTOR4f_NOT_IMPLEMENTED;
	return false;
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4f::allEqualZero<1>(hkSimdFloat32Parameter epsilon) const
{
	hkSimdFloat32 t = getComponent<0>();
	t.setAbs( t );
	return t.isLess(epsilon);
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4f::allEqualZero<2>(hkSimdFloat32Parameter epsilon) const
{
	// non_euclidean, manhattan based
	hkVector4f t;
	t.setAbs( *this );
	hkVector4f epsilon_v;
	epsilon_v.setAll(epsilon);
	return t.less( epsilon_v ).allAreSet<hkVector4ComparisonMask::MASK_XY>();
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4f::allEqualZero<3>(hkSimdFloat32Parameter epsilon) const
{
	// non_euclidean, manhattan based
	hkVector4f t;
	t.setAbs( *this );
	hkVector4f epsilon_v;
	epsilon_v.setAll(epsilon);
	return t.less( epsilon_v ).allAreSet<hkVector4ComparisonMask::MASK_XYZ>();
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4f::allEqualZero<4>(hkSimdFloat32Parameter epsilon) const
{
	// non_euclidean, manhattan based
	hkVector4f t;
	t.setAbs( *this );
	hkVector4f epsilon_v;
	epsilon_v.setAll(epsilon);
	return t.less( epsilon_v ).allAreSet();
}

template <int N>
HK_FORCE_INLINE hkBool32 hkVector4f::allEqualZero(hkSimdFloat32Parameter epsilon) const
{
	HK_VECTOR4f_NOT_IMPLEMENTED;
	return false;
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4f::allLess<1>(hkVector4fParameter a) const
{
	return getComponent<0>().isLess(a.getComponent<0>());
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4f::allLess<2>(hkVector4fParameter a) const
{
	return less(a).allAreSet<hkVector4ComparisonMask::MASK_XY>();
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4f::allLess<3>(hkVector4fParameter a) const
{
	return less(a).allAreSet<hkVector4ComparisonMask::MASK_XYZ>();
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4f::allLess<4>(hkVector4fParameter a) const
{
	return less(a).allAreSet();
}

template <int N>
HK_FORCE_INLINE hkBool32 hkVector4f::allLess(hkVector4fParameter a) const
{
	HK_VECTOR4f_NOT_IMPLEMENTED;
	return false;
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4f::allLessZero<1>() const
{
	return getComponent<0>().isLessZero();
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4f::allLessZero<2>() const
{
	return lessZero().allAreSet<hkVector4ComparisonMask::MASK_XY>();
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4f::allLessZero<3>() const
{
	return lessZero().allAreSet<hkVector4ComparisonMask::MASK_XYZ>();
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4f::allLessZero<4>() const
{
	return lessZero().allAreSet();
}

template <int N>
HK_FORCE_INLINE hkBool32 hkVector4f::allLessZero() const
{
	HK_VECTOR4f_NOT_IMPLEMENTED;
	return false;
}

HK_FORCE_INLINE void hkVector4f::setW(hkSimdFloat32Parameter w)
{
	setComponent<3>(w);
}

template <int I>
HK_FORCE_INLINE void hkVector4f::setBroadcast(hkVector4fParameter v)
{
	setAll( v.getComponent<I>() );
}

HK_FORCE_INLINE void hkVector4f::setBroadcast(const int i, hkVector4fParameter v)
{
	setAll( v.getComponent(i) );
}

HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::getW() const
{
	return getComponent<3>();
}

template <int I> 
HK_FORCE_INLINE const hkFloat32* hkVector4f::getComponentAddress() const
{
	HK_VECTOR4f_SUBINDEX_CHECK;
	return ((const hkFloat32*)&m_quad) + I;
}

template <int I> 
HK_FORCE_INLINE hkFloat32* hkVector4f::getComponentAddress()
{
	HK_VECTOR4f_SUBINDEX_CHECK;
	return ((hkFloat32*)&m_quad) + I;
}

HK_FORCE_INLINE const hkFloat32* hkVector4f::getComponentAddress(int i) const
{
	HK_MATH_ASSERT(0x6d0431d7, i>=0 && i<4, "index out of bounds for component access");
	return ((const hkFloat32*)&m_quad) + i;
}

HK_FORCE_INLINE hkFloat32* hkVector4f::getComponentAddress(int i)
{
	HK_MATH_ASSERT(0x6d0431d7, i>=0 && i<4, "index out of bounds for component access");
	return ((hkFloat32*)&m_quad) + i;
}

template <int N>
HK_FORCE_INLINE int hkVector4f::getIndexOfMaxAbsComponent() const
{
	hkVector4f abs; abs.setAbs( *this );
	return abs.getIndexOfMaxComponent<N>();
}

template <>
HK_FORCE_INLINE int hkVector4f::getIndexOfMaxComponent<4>() const
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	hkVector4f ma; ma.setHorizontalMax<4>( *this );
	const hkVector4fComparison isMax = greaterEqual(ma);
	HK_ON_DEBUG(const int mask = isMax.getMask();)
	HK_MATH_ASSERT(0x2842fb1, mask > 0, "inconsistent max value of self");
	return isMax.getIndexOfLastComponentSet();
#else
	const hkFloat32* HK_RESTRICT tmp = (const hkFloat32* HK_RESTRICT)this;

	int		xyIndex = 0;
	hkFloat32	xyValue = tmp[0];
	if ( tmp[0] <= tmp[1] )
	{
		xyIndex = 1;
		xyValue = tmp[1];
	}

	int		zwIndex = 2;
	hkFloat32	zwValue = tmp[2];
	if ( tmp[2] <= tmp[3] )
	{
		zwIndex = 3;
		zwValue = tmp[3];
	}
	if ( xyValue <= zwValue )
	{
		return zwIndex;
	}
	return xyIndex;
#endif
}

template <>
HK_FORCE_INLINE int hkVector4f::getIndexOfMaxComponent<3>() const
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	hkVector4f ma; ma.setHorizontalMax<3>( *this );
	hkVector4fComparison isMax = greaterEqual(ma);
	hkVector4fComparison xyzMask; xyzMask.set<hkVector4ComparisonMask::MASK_XYZ>();
	isMax.setAnd(isMax,xyzMask);
	HK_ON_DEBUG(const int mask = isMax.getMask();)
	HK_MATH_ASSERT(0x2842fb1, mask > 0, "inconsistent max value of self");
	HK_MATH_ASSERT(0x2842fb2, (mask & hkVector4ComparisonMask::MASK_W) == 0, "selective compare failed");
	return isMax.getIndexOfLastComponentSet();
#else
	const hkFloat32* HK_RESTRICT tmp = (const hkFloat32* HK_RESTRICT)this;

	int		xyIndex = 0;
	hkFloat32	xyValue = tmp[0];
	if ( tmp[0] <= tmp[1] )
	{
		xyIndex = 1;
		xyValue = tmp[1];
	}

	if ( xyValue <= tmp[2] )
	{
		return 2;
	}
	return xyIndex;
#endif
}

template <>
HK_FORCE_INLINE int hkVector4f::getIndexOfMaxComponent<2>() const
{
	return getComponent<0>().isGreater(getComponent<1>()) ? 0 : 1;
}

template <>
HK_FORCE_INLINE int hkVector4f::getIndexOfMaxComponent<1>() const
{
	return 0;
}

template <int N>
HK_FORCE_INLINE int hkVector4f::getIndexOfMaxComponent() const
{
	HK_VECTOR4f_NOT_IMPLEMENTED;
	return 0;
}

template <int N>
HK_FORCE_INLINE int hkVector4f::getIndexOfMinAbsComponent() const
{
	hkVector4f abs; abs.setAbs( *this );
	return abs.getIndexOfMinComponent<N>();
}

template <>
HK_FORCE_INLINE int hkVector4f::getIndexOfMinComponent<4>() const
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	hkVector4f mi; mi.setHorizontalMin<4>( *this );
	const hkVector4fComparison isMin = lessEqual(mi);
	HK_ON_DEBUG(const int mask = isMin.getMask();)
	HK_MATH_ASSERT(0x2842fb1, mask > 0, "inconsistent min value of self");
	return isMin.getIndexOfFirstComponentSet();
#else
	const hkFloat32* HK_RESTRICT tmp = (const hkFloat32* HK_RESTRICT)this;

	int		xyIndex = 0;
	hkFloat32	xyValue = tmp[0];
	if ( tmp[0] > tmp[1] )
	{
		xyIndex = 1;
		xyValue = tmp[1];
	}

	int		zwIndex = 2;
	hkFloat32	zwValue = tmp[2];
	if ( tmp[2] > tmp[3] )
	{
		zwIndex = 3;
		zwValue = tmp[3];
	}
	if ( xyValue > zwValue )
	{
		return zwIndex;
	}
	return xyIndex;
#endif
}

template <>
HK_FORCE_INLINE int hkVector4f::getIndexOfMinComponent<3>() const
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	hkVector4f mi; mi.setHorizontalMin<3>( *this );
	hkVector4fComparison isMin = lessEqual(mi);
	hkVector4fComparison xyzMask; xyzMask.set<hkVector4ComparisonMask::MASK_XYZ>();
	isMin.setAnd(isMin,xyzMask);
	HK_ON_DEBUG(const int mask = isMin.getMask();)
	HK_MATH_ASSERT(0x2842fb1, mask > 0, "inconsistent min value of self");
	HK_MATH_ASSERT(0x2842fb2, (mask & hkVector4ComparisonMask::MASK_W) == 0, "selective compare failed");
	return isMin.getIndexOfFirstComponentSet();
#else
	const hkFloat32* HK_RESTRICT tmp = (const hkFloat32* HK_RESTRICT)this;

	int		xyIndex = 0;
	hkFloat32	xyValue = tmp[0];
	if ( tmp[0] > tmp[1] )
	{
		xyIndex = 1;
		xyValue = tmp[1];
	}

	if ( xyValue > tmp[2] )
	{
		return 2;
	}
	return xyIndex;
#endif
}

template <>
HK_FORCE_INLINE int hkVector4f::getIndexOfMinComponent<2>() const
{
	return getComponent<0>().isGreater(getComponent<1>()) ? 1 : 0;
}

template <>
HK_FORCE_INLINE int hkVector4f::getIndexOfMinComponent<1>() const
{
	return 0;
}

template <int N>
HK_FORCE_INLINE int hkVector4f::getIndexOfMinComponent() const
{
	HK_VECTOR4f_NOT_IMPLEMENTED;
	return 0;
}

HK_FORCE_INLINE /*static*/ const hkVector4f& HK_CALL hkVector4f::getZero()
{
	return getConstant<HK_QUADREAL_0>();
}

template<int vectorConstant>
HK_FORCE_INLINE /*static*/ const hkVector4f& HK_CALL hkVector4f::getConstant()
{
	return *(const hkVector4f*) (g_vectorfConstants + vectorConstant);
}

HK_FORCE_INLINE /*static*/ const hkVector4f& HK_CALL hkVector4f::getConstant(hkVectorConstant vectorConstant)
{
	return *(const hkVector4f*) (g_vectorfConstants + vectorConstant);
}

template<int vectorConstant>
HK_FORCE_INLINE void hkVector4f::setConstant()
{
	*this = getConstant<vectorConstant>();
}


HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::distanceToSquared(hkVector4fParameter p) const
{
	hkVector4f d; d.setSub(*this, p);
	return d.lengthSquared<3>();
}

template <int N>
HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::lengthSquared() const
{
	return dot<N>(*this);
}

template <int N>
HK_FORCE_INLINE void hkVector4f::setDot(hkVector4fParameter a, hkVector4fParameter b)
{
	setAll( a.dot<N>(b) );
}

HK_FORCE_INLINE void hkVector4f::operator= (hkVector4fParameter v)
{
	m_quad = v.m_quad;
}

HK_FORCE_INLINE void hkVector4f::add(hkVector4fParameter a)
{
	setAdd( *this, a );
}

HK_FORCE_INLINE void hkVector4f::sub(hkVector4fParameter a)
{
	setSub( *this, a );
}

HK_FORCE_INLINE void hkVector4f::mul(hkVector4fParameter a)
{
	setMul( *this, a );
}

HK_FORCE_INLINE void hkVector4f::mul(hkSimdFloat32Parameter s)
{              
	setMul( *this, s );
}

HK_FORCE_INLINE void hkVector4f::setMul(hkSimdFloat32Parameter r, hkVector4fParameter v1)
{
	setMul(v1,r);
}

HK_FORCE_INLINE void hkVector4f::addMul(hkVector4fParameter x, hkVector4fParameter y)
{
	setAddMul(*this, x, y);
}

HK_FORCE_INLINE void hkVector4f::subMul(hkVector4fParameter x, hkVector4fParameter y)
{
	setSubMul(*this, x, y);
}

HK_FORCE_INLINE void hkVector4f::subMul(hkSimdFloat32Parameter r, hkVector4fParameter a)
{
	setSubMul(*this, a, r);
}

template <int N> 
HK_FORCE_INLINE void hkVector4f::setHorizontalAdd(hkVector4fParameter v)
{
	setAll( v.horizontalAdd<N>() );
}

template <int N> 
HK_FORCE_INLINE void hkVector4f::setHorizontalMax(hkVector4fParameter v)
{
	setAll( v.horizontalMax<N>() );
}

template <int N> 
HK_FORCE_INLINE void hkVector4f::setHorizontalMin(hkVector4fParameter v)
{
	setAll( v.horizontalMin<N>() );
}

template <int I>
HK_FORCE_INLINE void hkVector4f::broadcast()
{
	setBroadcast<I>(*this);
}

HK_FORCE_INLINE void hkVector4f::broadcast(const int i)
{
	setBroadcast(i, *this);
}

template<> 
HK_FORCE_INLINE void hkVector4f::setSelect<hkVector4ComparisonMask::MASK_NONE>( hkVector4fParameter trueValue, hkVector4fParameter falseValue )
{
	*this = falseValue;
}

template<> 
HK_FORCE_INLINE void hkVector4f::setSelect<hkVector4ComparisonMask::MASK_XYZW>( hkVector4fParameter trueValue, hkVector4fParameter falseValue )
{
	*this = trueValue;
}

HK_FORCE_INLINE void hkVector4f::setInterpolate(hkVector4fParameter v0, hkVector4fParameter v1, hkSimdFloat32Parameter t)
{
	// v0 + t * (v1 - v0)
	hkVector4f d; d.setSub(v1, v0);
	setAddMul( v0, d, t );
}


template <int N> 
HK_FORCE_INLINE bool hkVector4f::isNormalized(hkFloat32 epsilon) const
{
	if( isOk<N>() )
	{
		const hkSimdFloat32 lenZero = lengthSquared<N>() - hkSimdFloat32_1;
		hkSimdFloat32 absLenZero; absLenZero.setAbs(lenZero);
		return absLenZero < hkSimdFloat32::fromFloat(epsilon);
	}
	return false;
}

HK_FORCE_INLINE void hkVector4f::_setTransformedPos(const hkTransformf& t, hkVector4fParameter b)
{
	hkVector4f tb; tb._setRotatedDir(t.getRotation(), b);
	setAdd(tb, t.getTranslation());
}

HK_FORCE_INLINE void hkVector4f::_setTransformedInversePos(const hkTransformf& a, hkVector4fParameter b)
{
	hkVector4f t0; t0.setSub( b, a.getTranslation() );
	_setRotatedInverseDir(a.getRotation(), t0);
}

HK_FORCE_INLINE void hkVector4f::_setTransformedPos(const hkQsTransformf& a, hkVector4fParameter b)
{
	hkVector4f temp = b;
	temp.mul(a.getScale());
	temp._setRotatedDir(a.getRotation(), temp);
	setAdd(temp, a.getTranslation());
}

HK_FORCE_INLINE void hkVector4f::_setTransformedInversePos(const hkQsTransformf& a, hkVector4fParameter b)
{
	hkVector4f temp = b;
	temp.sub(a.getTranslation());
	temp._setRotatedInverseDir(a.getRotation(), temp);

	hkVector4f invScale; invScale.setReciprocal<HK_ACC_23_BIT,HK_DIV_IGNORE>(a.getScale());
	setMul(temp, invScale);
}

HK_FORCE_INLINE void hkVector4f::_setTransformedPos(const hkQTransformf& a, hkVector4fParameter b)
{
	hkVector4f temp = b;
	temp._setRotatedDir(a.getRotation(), temp);
	setAdd(temp, a.getTranslation());
}

HK_FORCE_INLINE void hkVector4f::_setTransformedInversePos(const hkQTransformf& a, hkVector4fParameter b)
{
	hkVector4f temp = b;
	temp.sub(a.getTranslation());
	_setRotatedInverseDir(a.getRotation(), temp);
}

HK_FORCE_INLINE void hkVector4f::addMul(hkVector4fParameter v1, hkSimdFloat32Parameter r)
{
	setAddMul(*this, v1, r);
}

HK_FORCE_INLINE void hkVector4f::addMul(hkSimdFloat32Parameter r, hkVector4fParameter v1)
{
	setAddMul(*this, v1, r);
}

HK_FORCE_INLINE void hkVector4f::subMul(hkVector4fParameter v1, hkSimdFloat32Parameter r)
{
	setSubMul(*this, v1, r);
}

HK_FORCE_INLINE void hkVector4f::setClamped( hkVector4fParameter a, hkVector4fParameter minVal, hkVector4fParameter maxVal )
{
	// This ensures that if a is NAN, clamped will be maxVal afterwards	
	const hkVector4fComparison maxValGtA = maxVal.greater(a);
	hkVector4f clamped; clamped.setSelect(maxValGtA, a, maxVal);
	setMax(minVal, clamped);
}

HK_FORCE_INLINE void hkVector4f::setClampedToMaxLength(hkVector4fParameter vSrc, hkSimdFloat32Parameter constMaxLen)
{
	// Make sure maxLen is > 0
	hkSimdFloat32 maxLen; maxLen.setMax(constMaxLen, hkSimdFloat32_Eps);

	// maxLen can be big, i.e. HK_FLOAT_MAX, so we can't square it
	hkSimdFloat32 len = vSrc.length<3>();
	hkSimdFloat32 invLen; invLen.setReciprocal(len);

	// calc rescaled
	hkVector4f rescaledSrc;
	rescaledSrc.setMul(maxLen * invLen, vSrc);

	// choose
	setSelect(len.lessEqual(maxLen), vSrc, rescaledSrc);
}

HK_FORCE_INLINE void hkVector4f::setInt24W( int value )
{
	HK_MATH_ASSERT(0xf0781100, (value & 0xff000000) == 0, "can only store 24 bit integer");
	hkInt32 fValue = hkInt32(value) | 0x3f000000;
	(reinterpret_cast<hkInt32*>(this))[3] = fValue;
}

HK_FORCE_INLINE int hkVector4f::getInt24W( ) const
{
	return (reinterpret_cast<const hkInt32*>(this))[3] & ~0x3f000000;
}

HK_FORCE_INLINE int hkVector4f::getInt16W( ) const
{
#if HK_ENDIAN_LITTLE == 1
	return (reinterpret_cast<const hkUint16*>(this))[6];
#else
	return (reinterpret_cast<const hkUint16*>(this))[7];
#endif
}

template <>
HK_FORCE_INLINE int hkVector4f::findComponent<4>(hkSimdFloat32Parameter value) const
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	hkVector4f v; v.setAll(value);
	const hkVector4fComparison isEqual = equal(v);
	if (isEqual.anyIsSet())
		return isEqual.getIndexOfFirstComponentSet();
#else
	const hkFloat32* HK_RESTRICT tmp = (const hkFloat32* HK_RESTRICT)this;
	const hkFloat32* HK_RESTRICT v   = (const hkFloat32* HK_RESTRICT)&value;

	if (v[0] == tmp[0]) return 0;
	if (v[0] == tmp[1]) return 1;
	if (v[0] == tmp[2]) return 2;
	if (v[0] == tmp[3]) return 3;
#endif
	return -1;
}

template <>
HK_FORCE_INLINE int hkVector4f::findComponent<3>(hkSimdFloat32Parameter value) const
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	hkVector4f v; v.setAll(value);
	const hkVector4fComparison isEqual = equal(v);
	if (isEqual.anyIsSet<hkVector4ComparisonMask::MASK_XYZ>())
		return isEqual.getIndexOfFirstComponentSet();
#else
	const hkFloat32* HK_RESTRICT tmp = (const hkFloat32* HK_RESTRICT)this;
	const hkFloat32* HK_RESTRICT v   = (const hkFloat32* HK_RESTRICT)&value;

	if (v[0] == tmp[0]) return 0;
	if (v[0] == tmp[1]) return 1;
	if (v[0] == tmp[2]) return 2;
#endif
	return -1;
}

template <>
HK_FORCE_INLINE int hkVector4f::findComponent<2>(hkSimdFloat32Parameter value) const
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	hkVector4f v; v.setAll(value);
	const hkVector4fComparison isEqual = equal(v);
	if (isEqual.anyIsSet<hkVector4ComparisonMask::MASK_XY>())
		return isEqual.getIndexOfFirstComponentSet();
#else
	const hkFloat32* HK_RESTRICT tmp = (const hkFloat32* HK_RESTRICT)this;
	const hkFloat32* HK_RESTRICT v   = (const hkFloat32* HK_RESTRICT)&value;

	if (v[0] == tmp[0]) return 0;
	if (v[0] == tmp[1]) return 1;
#endif
	return -1;
}

template <>
HK_FORCE_INLINE int hkVector4f::findComponent<1>(hkSimdFloat32Parameter value) const
{
	return getComponent<0>().isEqual(value) ? 0 : -1;
}

template <int N>
HK_FORCE_INLINE int hkVector4f::findComponent(hkSimdFloat32Parameter value) const
{
	HK_VECTOR4f_NOT_IMPLEMENTED;
	return 0;
}


#ifndef HK_DISABLE_OLD_VECTOR4_INTERFACE

//
// old interface
//

HK_FORCE_INLINE hkQuadFloat32& hkVector4f::getQuad() { return m_quad; }
HK_FORCE_INLINE const hkQuadFloat32& hkVector4f::getQuad() const { return m_quad; }
HK_FORCE_INLINE void hkVector4f::operator=(const hkQuadFloat32& r) { m_quad = r; }
HK_FORCE_INLINE void hkVector4f::add4(hkVector4fParameter v) { add(v); }
HK_FORCE_INLINE void hkVector4f::sub4(hkVector4fParameter v) { sub(v); }
HK_FORCE_INLINE void hkVector4f::mul4(hkVector4fParameter a) { mul(a); }
HK_FORCE_INLINE void hkVector4f::mul4(hkSimdFloat32Parameter a) { mul(a); }
HK_FORCE_INLINE void hkVector4f::div4(hkVector4fParameter a) { div<HK_ACC_FULL,HK_DIV_IGNORE>(a); }
HK_FORCE_INLINE void hkVector4f::div4fast(hkVector4fParameter a) { div<HK_ACC_23_BIT,HK_DIV_IGNORE>(a); }
HK_FORCE_INLINE hkSimdFloat32 hkVector4f::dot3(hkVector4fParameter v) const { return dot<3>(v); }
HK_FORCE_INLINE hkSimdFloat32 hkVector4f::dot4(hkVector4fParameter a) const { return dot<4>(a); }
HK_FORCE_INLINE hkFloat32 hkVector4f::dot3fpu(hkVector4fParameter a) const { const hkVector4f& t = *this; return (t(0) * a(0)) + ( t(1) * a(1)) + ( t(2) * a(2) ); }
HK_FORCE_INLINE void hkVector4f::setMul4(hkVector4fParameter a, hkVector4fParameter b) { setMul(a,b); }
HK_FORCE_INLINE void hkVector4f::setMul4(hkSimdFloat32Parameter a, hkVector4fParameter b) { setMul(b,a); }
HK_FORCE_INLINE void hkVector4f::_setMul4xyz1(const hkTransformf& a, hkVector4fParameter b ) { _setTransformedPos(a,b); }
HK_FORCE_INLINE void hkVector4f::subMul4(hkVector4fParameter a, hkVector4fParameter b) { subMul(a,b); }
HK_FORCE_INLINE void hkVector4f::subMul4(hkSimdFloat32Parameter a, hkVector4fParameter b) { subMul(b,a); }
HK_FORCE_INLINE void hkVector4f::setSubMul4(hkVector4fParameter a, hkVector4fParameter x, hkVector4fParameter y) { setSubMul(a,x,y); }
HK_FORCE_INLINE void hkVector4f::setSubMul4(hkVector4fParameter a, hkVector4fParameter x, hkSimdFloat32Parameter y) { setSubMul(a,x,y); }
HK_FORCE_INLINE void hkVector4f::setDot3(hkVector4fParameter a, hkVector4fParameter b) { setDot<3>(a,b); }
HK_FORCE_INLINE void hkVector4f::setDot4(hkVector4fParameter a, hkVector4fParameter b) { setDot<4>(a,b); }
HK_FORCE_INLINE void hkVector4f::setSelect4( hkVector4fComparisonParameter comp, hkVector4fParameter trueValue, hkVector4fParameter falseValue) { setSelect(comp,trueValue,falseValue); }
HK_FORCE_INLINE void hkVector4f::select32( hkVector4fParameter falseValue, hkVector4fParameter trueValue, hkVector4fComparisonParameter comp) { setSelect(comp,trueValue,falseValue); }
HK_FORCE_INLINE void hkVector4f::setBroadcast(hkVector4fParameter v, int i) { setBroadcast(i,v); }
HK_FORCE_INLINE void hkVector4f::setBroadcast3clobberW(hkVector4fParameter v, int i) { setBroadcastXYZ(i,v); }
HK_FORCE_INLINE void hkVector4f::setXYZW(hkVector4fParameter xyz, hkVector4fParameter w) { setXYZ_W(xyz,w); }
HK_FORCE_INLINE void hkVector4f::setXYZW(hkVector4fParameter xyz, hkSimdFloat32Parameter w) { setXYZ_W(xyz,w); }
HK_FORCE_INLINE void hkVector4f::setXYZ0(hkVector4fParameter xyz) { setXYZ_0(xyz); }
HK_FORCE_INLINE void hkVector4f::addMul4(hkVector4fParameter a, hkVector4fParameter b) { addMul(a,b); }
HK_FORCE_INLINE void hkVector4f::addMul4(hkSimdFloat32Parameter a, hkVector4fParameter b) { addMul(b,a); }
HK_FORCE_INLINE void hkVector4f::setZero4() { setZero(); }
HK_FORCE_INLINE void hkVector4f::setAll3(hkFloat32 x) { setZero(); setXYZ(x); }
HK_FORCE_INLINE void hkVector4f::zeroElement( int i ) { zeroComponent(i); }
HK_FORCE_INLINE void hkVector4f::setNeg3(hkVector4fParameter v) { setNeg<3>(v); }
HK_FORCE_INLINE void hkVector4f::setNeg4(hkVector4fParameter v) { setNeg<4>(v); }
HK_FORCE_INLINE void hkVector4f::setNegMask4(hkVector4fParameter v, int mask) { hkVector4fComparison cmp; cmp.set((hkVector4ComparisonMask::Mask)mask); setFlipSign(v, cmp); }
HK_FORCE_INLINE void hkVector4f::setDiv4(hkVector4fParameter a, hkVector4fParameter b) { setDiv<HK_ACC_FULL,HK_DIV_IGNORE>(a,b); }
HK_FORCE_INLINE void hkVector4f::setDiv4fast(hkVector4fParameter a, hkVector4fParameter b) { setDiv<HK_ACC_12_BIT,HK_DIV_IGNORE>(a,b); }
HK_FORCE_INLINE hkSimdFloat32 hkVector4f::getSimdAt(int i) const { return getComponent(i); }
HK_FORCE_INLINE void hkVector4f::normalize3() { normalize<3,HK_ACC_23_BIT,HK_SQRT_SET_ZERO>(); }
HK_FORCE_INLINE void hkVector4f::normalize4() { normalize<4,HK_ACC_23_BIT,HK_SQRT_SET_ZERO>(); }
HK_FORCE_INLINE void hkVector4f::fastNormalize3() { normalize<3,HK_ACC_12_BIT,HK_SQRT_SET_ZERO>(); }
HK_FORCE_INLINE void hkVector4f::fastNormalize3NonZero() { normalize<3,HK_ACC_12_BIT,HK_SQRT_IGNORE>(); }
HK_FORCE_INLINE void hkVector4f::setFastNormalize3NonZero(hkVector4fParameter a) { *this = a; normalize<3,HK_ACC_12_BIT,HK_SQRT_IGNORE>(); }
HK_FORCE_INLINE hkSimdFloat32 hkVector4f::normalizeWithLength3() { return normalizeWithLength<3,HK_ACC_23_BIT,HK_SQRT_SET_ZERO>(); }
HK_FORCE_INLINE hkSimdFloat32 hkVector4f::normalizeWithLength4() { return normalizeWithLength<4,HK_ACC_23_BIT,HK_SQRT_SET_ZERO>(); }
HK_FORCE_INLINE hkSimdFloat32 hkVector4f::fastNormalizeWithLength3() { return normalizeWithLength<3,HK_ACC_12_BIT,HK_SQRT_SET_ZERO>(); }
HK_FORCE_INLINE hkResult hkVector4f::normalize3IfNotZero () { return (normalizeIfNotZero<3>() ? HK_SUCCESS : HK_FAILURE); }
HK_FORCE_INLINE hkSimdFloat32 hkVector4f::length3() const { return length<3>(); }
HK_FORCE_INLINE hkSimdFloat32 hkVector4f::length4() const { return length<4>(); }
HK_FORCE_INLINE hkSimdFloat32 hkVector4f::lengthSquared3() const { return lengthSquared<3>(); }
HK_FORCE_INLINE hkSimdFloat32 hkVector4f::lengthSquared4() const { return lengthSquared<4>(); }
HK_FORCE_INLINE hkSimdFloat32 hkVector4f::lengthInverse3() const { return lengthInverse<3,HK_ACC_23_BIT,HK_SQRT_SET_ZERO>(); }
HK_FORCE_INLINE hkSimdFloat32 hkVector4f::lengthInverse4() const { return lengthInverse<4,HK_ACC_23_BIT,HK_SQRT_SET_ZERO>(); }
HK_FORCE_INLINE void hkVector4f::setAdd4(hkVector4fParameter a, hkVector4fParameter b) { setAdd(a,b); }
HK_FORCE_INLINE void hkVector4f::setSub4(hkVector4fParameter a, hkVector4fParameter b) { setSub(a,b); }
HK_FORCE_INLINE void hkVector4f::setSqrtInverse4(hkVector4fParameter v) { setSqrtInverse<HK_ACC_23_BIT,HK_SQRT_IGNORE>(v); }
HK_FORCE_INLINE void hkVector4f::setSqrtInverse4_7BitAccuracy(hkVector4fParameter v) { setSqrtInverse<HK_ACC_12_BIT,HK_SQRT_IGNORE>(v); }
HK_FORCE_INLINE void hkVector4f::setReciprocal3(hkVector4fParameter v) { setReciprocal<HK_ACC_23_BIT,HK_DIV_IGNORE>(v); setComponent<3>(hkSimdFloat32::getConstant(HK_QUADREAL_1)); }
HK_FORCE_INLINE void hkVector4f::setReciprocal4(hkVector4fParameter v) { setReciprocal<HK_ACC_23_BIT,HK_DIV_IGNORE>(v); }
HK_FORCE_INLINE void hkVector4f::setAddMul4(hkVector4fParameter a, hkVector4fParameter x, hkVector4fParameter y) { setAddMul(a,x,y); }
HK_FORCE_INLINE void hkVector4f::setAddMul4(hkVector4fParameter a, hkVector4fParameter b, hkSimdFloat32Parameter r) { setAddMul(a,b,r); }
HK_FORCE_INLINE void hkVector4f::setAbs4(hkVector4fParameter v) { setAbs(v); }
HK_FORCE_INLINE void hkVector4f::setMin4(hkVector4fParameter a, hkVector4fParameter b) { setMin(a,b); }
HK_FORCE_INLINE void hkVector4f::setMax4(hkVector4fParameter a, hkVector4fParameter b) { setMax(a,b); }
HK_FORCE_INLINE hkBool32 hkVector4f::equals3(const hkVector4f &v, hkFloat32 epsilon ) const
{
	hkVector4f t;
	t.setSub(*this, v);
	t.setAbs( t );
	hkVector4f epsilon_v;
	epsilon_v.setAll(epsilon);
	return t.lessEqual( epsilon_v ).allAreSet<hkVector4ComparisonMask::MASK_XYZ>();
}	
HK_FORCE_INLINE hkBool32 hkVector4f::equals4(const hkVector4f &v, hkFloat32 epsilon ) const
{
	hkVector4f t;
	t.setSub(*this, v);
	t.setAbs( t );
	hkVector4f epsilon_v;
	epsilon_v.setAll(epsilon);
	return t.lessEqual( epsilon_v ).allAreSet();
}
HK_FORCE_INLINE hkVector4fComparison hkVector4f::compareEqual4(hkVector4fParameter a) const { return equal(a); }
HK_FORCE_INLINE hkVector4fComparison hkVector4f::compareLessThan4(hkVector4fParameter a) const { return less(a); }
HK_FORCE_INLINE hkVector4fComparison hkVector4f::compareLessThanEqual4(hkVector4fParameter a) const { return lessEqual(a); }
HK_FORCE_INLINE hkVector4fComparison hkVector4f::compareGreaterThan4(hkVector4fParameter a) const { return greater(a); }
HK_FORCE_INLINE hkVector4fComparison hkVector4f::compareGreaterThanEqual4(hkVector4fParameter a) const { return greaterEqual(a); }
HK_FORCE_INLINE hkVector4fComparison hkVector4f::compareLessThanZero4() const { return lessZero(); }
HK_FORCE_INLINE hkBool32 hkVector4f::allLessThan3(hkVector4fParameter a) const { return allLess<3>(a); }
HK_FORCE_INLINE hkBool32 hkVector4f::allLessThan4(hkVector4fParameter a) const { return allLess<4>(a); }
HK_FORCE_INLINE void hkVector4f::setInterpolate4( hkVector4fParameter a, hkVector4fParameter b, hkSimdFloat32Parameter t ) { setInterpolate(a,b,t); }
HK_FORCE_INLINE hkSimdFloat32 hkVector4f::distanceTo3( hkVector4fParameter p ) const { return distanceTo(p); }
HK_FORCE_INLINE hkSimdFloat32 hkVector4f::distanceToSquared3( hkVector4fParameter p ) const { return distanceToSquared(p); }
HK_FORCE_INLINE hkSimdFloat32 hkVector4f::horizontalAdd3() const { return horizontalAdd<3>(); }
HK_FORCE_INLINE void hkVector4f::setHorizontalMax4( hkVector4fParameter p) { setHorizontalMax<4>(p); }
HK_FORCE_INLINE hkSimdFloat32 hkVector4f::getHorizontalMin3() const { return horizontalMin<3>(); }
HK_FORCE_INLINE hkSimdFloat32 hkVector4f::getHorizontalMax3() const { return horizontalMax<3>(); }
HK_FORCE_INLINE void hkVector4f::add3clobberW(hkVector4fParameter a) { addXYZ(a); }
HK_FORCE_INLINE hkSimdFloat32 hkVector4f::horizontalAdd4() const { return horizontalAdd<4>(); }
HK_FORCE_INLINE void hkVector4f::setClamped(hkVector4fParameter vSrc, const hkSimdFloat32& constMaxLen) { setClampedToMaxLength(vSrc, constMaxLen); }
HK_FORCE_INLINE	int hkVector4f::getMaxElementIndex4() const { return getIndexOfMaxComponent<4>(); }
HK_FORCE_INLINE	int hkVector4f::getMajorAxis3() const { return getIndexOfMaxAbsComponent<3>(); }
HK_FORCE_INLINE void hkVector4f::storeUncached( void* dest) const { store<4,HK_IO_NOT_CACHED>((hkFloat32*)dest); }
HK_FORCE_INLINE void hkVector4f::storeX( hkFloat32* dest)  const { store<1>(dest); }
HK_FORCE_INLINE void hkVector4f::storeX( hkDouble64* dest) const { store<1>(dest); }
HK_FORCE_INLINE void hkVector4f::sub3clobberW(hkVector4fParameter a) { subXYZ(a); }
HK_FORCE_INLINE void hkVector4f::_setMul3(const hkMatrix3f& a, hkVector4fParameter b) { _setRotatedDir(a,b); }
template <int S> HK_FORCE_INLINE void hkVector4f::setShuffle(hkVector4fParameter v) { setPermutation<(hkVectorPermutation::Permutation)S>(v); }
HK_FORCE_INLINE void hkVector4f::setAnd( hkVector4fParameter v0, hkVector4fParameter v1 ) { HK_ERROR(0x650a4a31,"not implemented"); }
HK_FORCE_INLINE void hkVector4f::setSwapXY(const hkVector4f& w) { setPermutation<hkVectorPermutation::YXZW>(w); }
HK_FORCE_INLINE void hkVector4f::setMulSigns4(hkVector4fParameter a, hkVector4fParameter signs) { setFlipSign(a, signs); }
HK_FORCE_INLINE void hkVector4f::setMulSigns4(hkVector4fParameter a, hkSimdFloat32Parameter sharedSign) { setFlipSign(a, sharedSign); }
HK_FORCE_INLINE hkBool hkVector4f::isNormalized3(hkFloat32 eps) const { return isNormalized<3>(eps); }
HK_FORCE_INLINE hkBool hkVector4f::isNormalized4(hkFloat32 eps) const { return isNormalized<4>(eps); }
HK_FORCE_INLINE hkBool hkVector4f::isOk3() const { return (hkBool)isOk<3>(); }
HK_FORCE_INLINE hkBool hkVector4f::isOk4() const { return (hkBool)isOk<4>(); }
HK_FORCE_INLINE const hkVector4fComparison hkVector4f::isNegative() const { return signBitSet(); }
HK_FORCE_INLINE const hkVector4fComparison hkVector4f::isPositive() const { return signBitClear(); }
HK_FORCE_INLINE void hkVector4f::load3(const hkFloat32* p) { load<3,HK_IO_NATIVE_ALIGNED>(p); }
HK_FORCE_INLINE void hkVector4f::load4(const hkFloat32* p) { load<4,HK_IO_NATIVE_ALIGNED>(p); }
HK_FORCE_INLINE void hkVector4f::load4a(const hkFloat32* p) { load<4,HK_IO_SIMD_ALIGNED>(p); }
HK_FORCE_INLINE void hkVector4f::load3(const hkDouble64* p) { load<3,HK_IO_NATIVE_ALIGNED>(p); }
HK_FORCE_INLINE void hkVector4f::load4(const hkDouble64* p) { load<4,HK_IO_NATIVE_ALIGNED>(p); }
HK_FORCE_INLINE void hkVector4f::load4a(const hkDouble64* p) { load<4,HK_IO_SIMD_ALIGNED>(p); }
HK_FORCE_INLINE void hkVector4f::store3(hkFloat32* p) const { store<3,HK_IO_NATIVE_ALIGNED>(p); }
HK_FORCE_INLINE void hkVector4f::store4(hkFloat32* p) const { store<4,HK_IO_NATIVE_ALIGNED>(p); }
HK_FORCE_INLINE void hkVector4f::store4a(hkFloat32* p) const { store<4,HK_IO_SIMD_ALIGNED>(p); }
HK_FORCE_INLINE void hkVector4f::store3(hkDouble64* p) const { store<3,HK_IO_NATIVE_ALIGNED>(p); }
HK_FORCE_INLINE void hkVector4f::store4(hkDouble64* p) const { store<4,HK_IO_NATIVE_ALIGNED>(p); }
HK_FORCE_INLINE void hkVector4f::store4a(hkDouble64* p) const { store<4,HK_IO_SIMD_ALIGNED>(p); }
HK_FORCE_INLINE void hkVector4f::setMul3(const hkMatrix3f& a, hkVector4fParameter b ) { _setRotatedDir(a,b); }
HK_FORCE_INLINE void hkVector4f::_setMul4(const hkMatrix3f& a, hkVector4fParameter b ) { _setRotatedDir(a,b); }

#endif

//
// advanced interface
//

template <int N, hkMathAccuracyMode A, hkMathNegSqrtMode S> 
HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::length() const
{
	const hkSimdFloat32 len2 = lengthSquared<N>();
	return len2.sqrt<A,S>();
}

template <int N>
HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::length() const
{
	return length<N,HK_ACC_23_BIT,HK_SQRT_SET_ZERO>();
}

template <int N, hkMathAccuracyMode A, hkMathNegSqrtMode S> 
HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::lengthInverse() const
{
	const hkSimdFloat32 len2 = lengthSquared<N>();
	return len2.sqrtInverse<A,S>();
}

template <int N>
HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::lengthInverse() const
{
	return lengthInverse<N,HK_ACC_23_BIT,HK_SQRT_SET_ZERO>();
}

template <int N, hkMathAccuracyMode A, hkMathNegSqrtMode S>
HK_FORCE_INLINE void hkVector4f::normalize()
{
	mul( lengthInverse<N,A,S>() );
}

template <int N>
HK_FORCE_INLINE void hkVector4f::normalize()
{
	normalize<N,HK_ACC_23_BIT,HK_SQRT_SET_ZERO>();
}

template <int N, hkMathAccuracyMode A, hkMathNegSqrtMode S>
HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::normalizeWithLength()
{
	const hkSimdFloat32 len2 = lengthSquared<N>();
	const hkSimdFloat32 lenInv = len2.sqrtInverse<A,S>();
	mul(lenInv);
	return (len2 * lenInv); // quicker to return x^2/x
}

template <int N>
HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::normalizeWithLength()
{
	return normalizeWithLength<N,HK_ACC_23_BIT,HK_SQRT_SET_ZERO>();
}

template <int N, hkMathAccuracyMode A, hkMathNegSqrtMode S>
HK_FORCE_INLINE hkBool32 hkVector4f::normalizeIfNotZero()
{
	const hkSimdFloat32 lengthSqrd = lengthSquared<N>();
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	const hkVector4fComparison less0 = ( -lengthSqrd ).lessZero();

	hkVector4f normThis; normThis.setMul(*this, lengthSqrd.sqrtInverse<A,S>());
	setSelect(less0, normThis, *this);

	return less0.anyIsSet();
#else
	if ( ( -lengthSqrd ).isLessZero() )
	{
		mul(lengthSqrd.sqrtInverse<A,S>());
		return 1;
	}
	return 0;
#endif
}

template <int N>
HK_FORCE_INLINE hkBool32 hkVector4f::normalizeIfNotZero()
{
	return normalizeIfNotZero<N,HK_ACC_23_BIT,HK_SQRT_SET_ZERO>();
}

template <hkMathAccuracyMode A, hkMathNegSqrtMode S>
HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::distanceTo(hkVector4fParameter p) const
{
	const hkSimdFloat32 d2 = distanceToSquared(p);
	const hkSimdFloat32 ri = d2.sqrtInverse<A,S>();
	return (d2 * ri);
}

HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::distanceTo(hkVector4fParameter p) const
{
	return distanceToSquared(p).sqrt<HK_ACC_23_BIT,HK_SQRT_SET_ZERO>();
}


template <int N, hkMathAccuracyMode A>
HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::setNormalizedEnsureUnitLength(hkVector4fParameter v)
{
	const hkSimdFloat32 length2 = v.lengthSquared<N>();
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	const hkVector4fComparison lengthLessEps = length2.less(hkSimdFloat32_EpsSqrd);

	hkSimdFloat32 invLength;
	if ( A == HK_ACC_FULL )
	{
		 invLength = length2.sqrtInverse<A,HK_SQRT_SET_ZERO>();
	}
	else
	{
		 invLength = length2.sqrtInverse<A,HK_SQRT_IGNORE>();
	}
	hkVector4f normV; normV.setMul(v,invLength);
	setSelect(lengthLessEps, hkVector4f::getConstant<HK_QUADREAL_1000>(), normV);

	hkSimdFloat32 oldLength = length2 * invLength;
	oldLength.zeroIfTrue(lengthLessEps);
	return oldLength;
#else
	if (length2.isGreaterEqual(hkSimdFloat32::getConstant<HK_QUADREAL_EPS_SQRD>()))
	{
		const hkSimdFloat32 invLength = length2.sqrtInverse<A,HK_SQRT_IGNORE>();
		setMul(v,invLength);
		return (length2 * invLength);
	}
	m_quad = g_vectorfConstants[HK_QUADREAL_1000];
	return hkSimdFloat32_0;
#endif
}

template <int N>
HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::setNormalizedEnsureUnitLength(hkVector4fParameter v)
{
	return setNormalizedEnsureUnitLength<N,HK_ACC_23_BIT>(v);
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
