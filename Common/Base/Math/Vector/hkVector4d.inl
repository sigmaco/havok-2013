/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

HK_FORCE_INLINE void hkVector4d::_setRotatedDir(hkQuaterniondParameter quat, hkVector4dParameter direction)
{
	hkSimdDouble64 qreal = quat.m_vec.getComponent<3>();
	hkSimdDouble64 q2minus1 = qreal*qreal - hkSimdDouble64_Half;

	hkVector4d ret;
	ret.setMul( direction, q2minus1 );

	hkSimdDouble64 imagDotDir = quat.getImag().dot<3>( direction );

	ret.addMul( quat.getImag(), imagDotDir ); 

	hkVector4d imagCrossDir;
	imagCrossDir.setCross( quat.getImag(), direction );
	ret.addMul( imagCrossDir, qreal );

	setAdd( ret, ret );
}

HK_FORCE_INLINE void hkVector4d::_setRotatedInverseDir(hkQuaterniondParameter quat, hkVector4dParameter direction)
{
	hkSimdDouble64 qreal = quat.m_vec.getComponent<3>();
	hkSimdDouble64 q2minus1 = qreal*qreal - hkSimdDouble64_Half;

	hkVector4d ret;
	ret.setMul( direction, q2minus1 );

	hkSimdDouble64 imagDotDir = quat.getImag().dot<3>( direction );

	ret.addMul( quat.getImag(), imagDotDir ); 

	hkVector4d imagCrossDir;
	imagCrossDir.setCross( direction, quat.getImag() );
	ret.addMul( imagCrossDir, qreal );

	setAdd( ret, ret );
}

HK_FORCE_INLINE void hkVector4d::setPlaneConstant(hkVector4dParameter p)
{
	const hkSimdDouble64 w = dot<3>(p);
	setW(-w);
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4d::allExactlyEqual<1>(hkVector4dParameter v) const
{
	return getComponent<0>().isEqual(v.getComponent<0>());
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4d::allExactlyEqual<2>(hkVector4dParameter v) const
{
	return equal(v).allAreSet<hkVector4ComparisonMask::MASK_XY>();
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4d::allExactlyEqual<3>(hkVector4dParameter v) const
{
	return equal(v).allAreSet<hkVector4ComparisonMask::MASK_XYZ>();
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4d::allExactlyEqual<4>(hkVector4dParameter v) const
{
	return equal(v).allAreSet();
}

template <int N>
HK_FORCE_INLINE hkBool32 hkVector4d::allExactlyEqual(hkVector4dParameter v) const
{
	HK_VECTOR4d_NOT_IMPLEMENTED;
	return false;
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4d::allExactlyEqualZero<1>() const
{
	return getComponent<0>().isEqualZero();
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4d::allExactlyEqualZero<2>() const
{
	return equalZero().allAreSet<hkVector4ComparisonMask::MASK_XY>();
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4d::allExactlyEqualZero<3>() const
{
	return equalZero().allAreSet<hkVector4ComparisonMask::MASK_XYZ>();
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4d::allExactlyEqualZero<4>() const
{
	return equalZero().allAreSet();
}

template <int N>
HK_FORCE_INLINE hkBool32 hkVector4d::allExactlyEqualZero() const
{
	HK_VECTOR4d_NOT_IMPLEMENTED;
	return false;
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4d::allComponentsEqual<4>() const
{
	hkVector4d yxwz; yxwz.setPermutation<hkVectorPermutation::YXWZ>(*this);
	const hkVector4dComparison xz_eq_yw = equal(yxwz);

	hkVector4d zwxy; zwxy.setPermutation<hkVectorPermutation::ZWXY>(*this);
	const hkVector4dComparison xy_eq_zw = equal(zwxy);

	hkVector4dComparison all_eq; all_eq.setAnd(xz_eq_yw, xy_eq_zw);
	return all_eq.allAreSet();
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4d::allComponentsEqual<3>() const
{
	hkVector4d yxzw; yxzw.setPermutation<hkVectorPermutation::YXZW>(*this);
	const hkVector4dComparison x_eq_y = equal(yxzw);

	hkVector4d zwxy; zwxy.setPermutation<hkVectorPermutation::ZWXY>(*this);
	const hkVector4dComparison x_eq_z = equal(zwxy);

	hkVector4dComparison x_eq_y_eq_z; x_eq_y_eq_z.setAnd(x_eq_y, x_eq_z);
	return x_eq_y_eq_z.allAreSet<hkVector4ComparisonMask::MASK_X>();
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4d::allComponentsEqual<2>() const
{
	hkVector4d yx; yx.setPermutation<hkVectorPermutation::YXZW>(*this);
	return allExactlyEqual<2>(yx);
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4d::allComponentsEqual<1>() const
{
	return true;
}

template <int N>
HK_FORCE_INLINE hkBool32 hkVector4d::allComponentsEqual() const
{
	HK_VECTOR4d_NOT_IMPLEMENTED;
	return false;
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4d::allEqual<1>(hkVector4dParameter v, hkSimdDouble64Parameter epsilon) const
{
	hkSimdDouble64 t = getComponent<0>() - v.getComponent<0>();
	t.setAbs( t );
	return t.isLess(epsilon);
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4d::allEqual<2>(hkVector4dParameter v, hkSimdDouble64Parameter epsilon) const
{
	// non_euclidean, manhattan based
	hkVector4d t;
	t.setSub(*this, v);
	t.setAbs( t );
	hkVector4d epsilon_v;
	epsilon_v.setAll(epsilon);
	return t.less( epsilon_v ).allAreSet<hkVector4ComparisonMask::MASK_XY>();
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4d::allEqual<3>(hkVector4dParameter v, hkSimdDouble64Parameter epsilon) const
{
	// non_euclidean, manhattan based
	hkVector4d t;
	t.setSub(*this, v);
	t.setAbs( t );
	hkVector4d epsilon_v;
	epsilon_v.setAll(epsilon);
	return t.less( epsilon_v ).allAreSet<hkVector4ComparisonMask::MASK_XYZ>();
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4d::allEqual<4>(hkVector4dParameter v, hkSimdDouble64Parameter epsilon) const
{
	// non_euclidean, manhattan based
	hkVector4d t;
	t.setSub(*this, v);
	t.setAbs( t );
	hkVector4d epsilon_v;
	epsilon_v.setAll(epsilon);
	return t.less( epsilon_v ).allAreSet();
}

template <int N>
HK_FORCE_INLINE hkBool32 hkVector4d::allEqual(hkVector4dParameter v, hkSimdDouble64Parameter epsilon) const
{
	HK_VECTOR4d_NOT_IMPLEMENTED;
	return false;
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4d::allEqualZero<1>(hkSimdDouble64Parameter epsilon) const
{
	hkSimdDouble64 t = getComponent<0>();
	t.setAbs( t );
	return t.isLess(epsilon);
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4d::allEqualZero<2>(hkSimdDouble64Parameter epsilon) const
{
	// non_euclidean, manhattan based
	hkVector4d t;
	t.setAbs( *this );
	hkVector4d epsilon_v;
	epsilon_v.setAll(epsilon);
	return t.less( epsilon_v ).allAreSet<hkVector4ComparisonMask::MASK_XY>();
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4d::allEqualZero<3>(hkSimdDouble64Parameter epsilon) const
{
	// non_euclidean, manhattan based
	hkVector4d t;
	t.setAbs( *this );
	hkVector4d epsilon_v;
	epsilon_v.setAll(epsilon);
	return t.less( epsilon_v ).allAreSet<hkVector4ComparisonMask::MASK_XYZ>();
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4d::allEqualZero<4>(hkSimdDouble64Parameter epsilon) const
{
	// non_euclidean, manhattan based
	hkVector4d t;
	t.setAbs( *this );
	hkVector4d epsilon_v;
	epsilon_v.setAll(epsilon);
	return t.less( epsilon_v ).allAreSet();
}

template <int N>
HK_FORCE_INLINE hkBool32 hkVector4d::allEqualZero(hkSimdDouble64Parameter epsilon) const
{
	HK_VECTOR4d_NOT_IMPLEMENTED;
	return false;
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4d::allLess<1>(hkVector4dParameter a) const
{
	return getComponent<0>().isLess(a.getComponent<0>());
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4d::allLess<2>(hkVector4dParameter a) const
{
	return less(a).allAreSet<hkVector4ComparisonMask::MASK_XY>();
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4d::allLess<3>(hkVector4dParameter a) const
{
	return less(a).allAreSet<hkVector4ComparisonMask::MASK_XYZ>();
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4d::allLess<4>(hkVector4dParameter a) const
{
	return less(a).allAreSet();
}

template <int N>
HK_FORCE_INLINE hkBool32 hkVector4d::allLess(hkVector4dParameter a) const
{
	HK_VECTOR4d_NOT_IMPLEMENTED;
	return false;
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4d::allLessZero<1>() const
{
	return getComponent<0>().isLessZero();
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4d::allLessZero<2>() const
{
	return lessZero().allAreSet<hkVector4ComparisonMask::MASK_XY>();
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4d::allLessZero<3>() const
{
	return lessZero().allAreSet<hkVector4ComparisonMask::MASK_XYZ>();
}

template <>
HK_FORCE_INLINE hkBool32 hkVector4d::allLessZero<4>() const
{
	return lessZero().allAreSet();
}

template <int N>
HK_FORCE_INLINE hkBool32 hkVector4d::allLessZero() const
{
	HK_VECTOR4d_NOT_IMPLEMENTED;
	return false;
}

HK_FORCE_INLINE void hkVector4d::setW(hkSimdDouble64Parameter w)
{
	setComponent<3>(w);
}

template <int I>
HK_FORCE_INLINE void hkVector4d::setBroadcast(hkVector4dParameter v)
{
	setAll( v.getComponent<I>() );
}

HK_FORCE_INLINE void hkVector4d::setBroadcast(const int i, hkVector4dParameter v)
{
	setAll( v.getComponent(i) );
}

HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::getW() const
{
	return getComponent<3>();
}

template <int I> 
HK_FORCE_INLINE const hkDouble64* hkVector4d::getComponentAddress() const
{
	HK_VECTOR4d_SUBINDEX_CHECK;
	return ((const hkDouble64*)&m_quad) + I;
}

template <int I> 
HK_FORCE_INLINE hkDouble64* hkVector4d::getComponentAddress()
{
	HK_VECTOR4d_SUBINDEX_CHECK;
	return ((hkDouble64*)&m_quad) + I;
}

HK_FORCE_INLINE const hkDouble64* hkVector4d::getComponentAddress(int i) const
{
	HK_MATH_ASSERT(0x6d0431d7, i>=0 && i<4, "index out of bounds for component access");
	return ((const hkDouble64*)&m_quad) + i;
}

HK_FORCE_INLINE hkDouble64* hkVector4d::getComponentAddress(int i)
{
	HK_MATH_ASSERT(0x6d0431d7, i>=0 && i<4, "index out of bounds for component access");
	return ((hkDouble64*)&m_quad) + i;
}

template <int N>
HK_FORCE_INLINE int hkVector4d::getIndexOfMaxAbsComponent() const
{
	hkVector4d abs; abs.setAbs( *this );
	return abs.getIndexOfMaxComponent<N>();
}

template <>
HK_FORCE_INLINE int hkVector4d::getIndexOfMaxComponent<4>() const
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	hkVector4d ma; ma.setHorizontalMax<4>( *this );
	const hkVector4dComparison isMax = greaterEqual(ma);
	HK_ON_DEBUG(const int mask = isMax.getMask();)
	HK_MATH_ASSERT(0x2842fb1, mask > 0, "inconsistent max value of self");
	return isMax.getIndexOfLastComponentSet();
#else
	const hkDouble64* HK_RESTRICT tmp = (const hkDouble64* HK_RESTRICT)this;

	int		xyIndex = 0;
	hkDouble64	xyValue = tmp[0];
	if ( tmp[0] <= tmp[1] )
	{
		xyIndex = 1;
		xyValue = tmp[1];
	}

	int		zwIndex = 2;
	hkDouble64	zwValue = tmp[2];
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
HK_FORCE_INLINE int hkVector4d::getIndexOfMaxComponent<3>() const
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	hkVector4d ma; ma.setHorizontalMax<3>( *this );
	hkVector4dComparison isMax = greaterEqual(ma);
	hkVector4dComparison xyzMask; xyzMask.set<hkVector4ComparisonMask::MASK_XYZ>();
	isMax.setAnd(isMax,xyzMask);
	HK_ON_DEBUG(const int mask = isMax.getMask();)
	HK_MATH_ASSERT(0x2842fb1, mask > 0, "inconsistent max value of self");
	HK_MATH_ASSERT(0x2842fb2, (mask & hkVector4ComparisonMask::MASK_W) == 0, "selective compare failed");
	return isMax.getIndexOfLastComponentSet();
#else
	const hkDouble64* HK_RESTRICT tmp = (const hkDouble64* HK_RESTRICT)this;

	int		xyIndex = 0;
	hkDouble64	xyValue = tmp[0];
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
HK_FORCE_INLINE int hkVector4d::getIndexOfMaxComponent<2>() const
{
	return getComponent<0>().isGreater(getComponent<1>()) ? 0 : 1;
}

template <>
HK_FORCE_INLINE int hkVector4d::getIndexOfMaxComponent<1>() const
{
	return 0;
}

template <int N>
HK_FORCE_INLINE int hkVector4d::getIndexOfMaxComponent() const
{
	HK_VECTOR4d_NOT_IMPLEMENTED;
	return 0;
}

template <int N>
HK_FORCE_INLINE int hkVector4d::getIndexOfMinAbsComponent() const
{
	hkVector4d abs; abs.setAbs( *this );
	return abs.getIndexOfMinComponent<N>();
}

template <>
HK_FORCE_INLINE int hkVector4d::getIndexOfMinComponent<4>() const
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	hkVector4d mi; mi.setHorizontalMin<4>( *this );
	const hkVector4dComparison isMin = lessEqual(mi);
	HK_ON_DEBUG(const int mask = isMin.getMask();)
	HK_MATH_ASSERT(0x2842fb1, mask > 0, "inconsistent min value of self");
	return isMin.getIndexOfFirstComponentSet();
#else
	const hkDouble64* HK_RESTRICT tmp = (const hkDouble64* HK_RESTRICT)this;

	int		xyIndex = 0;
	hkDouble64	xyValue = tmp[0];
	if ( tmp[0] > tmp[1] )
	{
		xyIndex = 1;
		xyValue = tmp[1];
	}

	int		zwIndex = 2;
	hkDouble64	zwValue = tmp[2];
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
HK_FORCE_INLINE int hkVector4d::getIndexOfMinComponent<3>() const
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	hkVector4d mi; mi.setHorizontalMin<3>( *this );
	hkVector4dComparison isMin = lessEqual(mi);
	hkVector4dComparison xyzMask; xyzMask.set<hkVector4ComparisonMask::MASK_XYZ>();
	isMin.setAnd(isMin,xyzMask);
	HK_ON_DEBUG(const int mask = isMin.getMask();)
	HK_MATH_ASSERT(0x2842fb1, mask > 0, "inconsistent min value of self");
	HK_MATH_ASSERT(0x2842fb2, (mask & hkVector4ComparisonMask::MASK_W) == 0, "selective compare failed");
	return isMin.getIndexOfFirstComponentSet();
#else
	const hkDouble64* HK_RESTRICT tmp = (const hkDouble64* HK_RESTRICT)this;

	int		xyIndex = 0;
	hkDouble64	xyValue = tmp[0];
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
HK_FORCE_INLINE int hkVector4d::getIndexOfMinComponent<2>() const
{
	return getComponent<0>().isGreater(getComponent<1>()) ? 1 : 0;
}

template <>
HK_FORCE_INLINE int hkVector4d::getIndexOfMinComponent<1>() const
{
	return 0;
}

template <int N>
HK_FORCE_INLINE int hkVector4d::getIndexOfMinComponent() const
{
	HK_VECTOR4d_NOT_IMPLEMENTED;
	return 0;
}

HK_FORCE_INLINE /*static*/ const hkVector4d& HK_CALL hkVector4d::getZero()
{
	return getConstant<HK_QUADREAL_0>();
}

template<int vectorConstant>
HK_FORCE_INLINE /*static*/ const hkVector4d& HK_CALL hkVector4d::getConstant()
{
	return *(const hkVector4d*) (g_vectordConstants + vectorConstant);
}

HK_FORCE_INLINE /*static*/ const hkVector4d& HK_CALL hkVector4d::getConstant(hkVectorConstant vectorConstant)
{
	return *(const hkVector4d*) (g_vectordConstants + vectorConstant);
}

template<int vectorConstant>
HK_FORCE_INLINE void hkVector4d::setConstant()
{
	*this = getConstant<vectorConstant>();
}


HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::distanceToSquared(hkVector4dParameter p) const
{
	hkVector4d d; d.setSub(*this, p);
	return d.lengthSquared<3>();
}

template <int N>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::lengthSquared() const
{
	return dot<N>(*this);
}

template <int N>
HK_FORCE_INLINE void hkVector4d::setDot(hkVector4dParameter a, hkVector4dParameter b)
{
	setAll( a.dot<N>(b) );
}

HK_FORCE_INLINE void hkVector4d::operator= (hkVector4dParameter v)
{
	m_quad = v.m_quad;
}

HK_FORCE_INLINE void hkVector4d::add(hkVector4dParameter a)
{
	setAdd( *this, a );
}

HK_FORCE_INLINE void hkVector4d::sub(hkVector4dParameter a)
{
	setSub( *this, a );
}

HK_FORCE_INLINE void hkVector4d::mul(hkVector4dParameter a)
{
	setMul( *this, a );
}

HK_FORCE_INLINE void hkVector4d::mul(hkSimdDouble64Parameter s)
{              
	setMul( *this, s );
}

HK_FORCE_INLINE void hkVector4d::setMul(hkSimdDouble64Parameter r, hkVector4dParameter v1)
{
	setMul(v1,r);
}

HK_FORCE_INLINE void hkVector4d::addMul(hkVector4dParameter x, hkVector4dParameter y)
{
	setAddMul(*this, x, y);
}

HK_FORCE_INLINE void hkVector4d::subMul(hkVector4dParameter x, hkVector4dParameter y)
{
	setSubMul(*this, x, y);
}

HK_FORCE_INLINE void hkVector4d::subMul(hkSimdDouble64Parameter r, hkVector4dParameter a)
{
	setSubMul(*this, a, r);
}

template <int N> 
HK_FORCE_INLINE void hkVector4d::setHorizontalAdd(hkVector4dParameter v)
{
	setAll( v.horizontalAdd<N>() );
}

template <int N> 
HK_FORCE_INLINE void hkVector4d::setHorizontalMax(hkVector4dParameter v)
{
	setAll( v.horizontalMax<N>() );
}

template <int N> 
HK_FORCE_INLINE void hkVector4d::setHorizontalMin(hkVector4dParameter v)
{
	setAll( v.horizontalMin<N>() );
}

template <int I>
HK_FORCE_INLINE void hkVector4d::broadcast()
{
	setBroadcast<I>(*this);
}

HK_FORCE_INLINE void hkVector4d::broadcast(const int i)
{
	setBroadcast(i, *this);
}

template<> 
HK_FORCE_INLINE void hkVector4d::setSelect<hkVector4ComparisonMask::MASK_NONE>( hkVector4dParameter trueValue, hkVector4dParameter falseValue )
{
	*this = falseValue;
}

template<> 
HK_FORCE_INLINE void hkVector4d::setSelect<hkVector4ComparisonMask::MASK_XYZW>( hkVector4dParameter trueValue, hkVector4dParameter falseValue )
{
	*this = trueValue;
}

HK_FORCE_INLINE void hkVector4d::setInterpolate(hkVector4dParameter v0, hkVector4dParameter v1, hkSimdDouble64Parameter t)
{
	// v0 + t * (v1 - v0)
	hkVector4d d; d.setSub(v1, v0);
	setAddMul( v0, d, t );
}


template <int N> 
HK_FORCE_INLINE bool hkVector4d::isNormalized(hkDouble64 epsilon) const
{
	if( isOk<N>() )
	{
		const hkSimdDouble64 lenZero = lengthSquared<N>() - hkSimdDouble64_1;
		hkSimdDouble64 absLenZero; absLenZero.setAbs(lenZero);
		return absLenZero < hkSimdDouble64::fromFloat(epsilon);
	}
	return false;
}

HK_FORCE_INLINE void hkVector4d::_setTransformedPos(const hkTransformd& t, hkVector4dParameter b)
{
	hkVector4d tb; tb._setRotatedDir(t.getRotation(), b);
	setAdd(tb, t.getTranslation());
}

HK_FORCE_INLINE void hkVector4d::_setTransformedInversePos(const hkTransformd& a, hkVector4dParameter b)
{
	hkVector4d t0; t0.setSub( b, a.getTranslation() );
	_setRotatedInverseDir(a.getRotation(), t0);
}

HK_FORCE_INLINE void hkVector4d::_setTransformedPos(const hkQsTransformd& a, hkVector4dParameter b)
{
	hkVector4d temp = b;
	temp.mul(a.getScale());
	temp._setRotatedDir(a.getRotation(), temp);
	setAdd(temp, a.getTranslation());
}

HK_FORCE_INLINE void hkVector4d::_setTransformedInversePos(const hkQsTransformd& a, hkVector4dParameter b)
{
	hkVector4d temp = b;
	temp.sub(a.getTranslation());
	temp._setRotatedInverseDir(a.getRotation(), temp);

	hkVector4d invScale; invScale.setReciprocal<HK_ACC_23_BIT,HK_DIV_IGNORE>(a.getScale());
	setMul(temp, invScale);
}

HK_FORCE_INLINE void hkVector4d::_setTransformedPos(const hkQTransformd& a, hkVector4dParameter b)
{
	hkVector4d temp = b;
	temp._setRotatedDir(a.getRotation(), temp);
	setAdd(temp, a.getTranslation());
}

HK_FORCE_INLINE void hkVector4d::_setTransformedInversePos(const hkQTransformd& a, hkVector4dParameter b)
{
	hkVector4d temp = b;
	temp.sub(a.getTranslation());
	_setRotatedInverseDir(a.getRotation(), temp);
}

HK_FORCE_INLINE void hkVector4d::addMul(hkVector4dParameter v1, hkSimdDouble64Parameter r)
{
	setAddMul(*this, v1, r);
}

HK_FORCE_INLINE void hkVector4d::addMul(hkSimdDouble64Parameter r, hkVector4dParameter v1)
{
	setAddMul(*this, v1, r);
}

HK_FORCE_INLINE void hkVector4d::subMul(hkVector4dParameter v1, hkSimdDouble64Parameter r)
{
	setSubMul(*this, v1, r);
}

HK_FORCE_INLINE void hkVector4d::setClamped( hkVector4dParameter a, hkVector4dParameter minVal, hkVector4dParameter maxVal )
{
	// This ensures that if a is NAN, clamped will be maxVal afterwards	
	const hkVector4dComparison maxValGtA = maxVal.greater(a);
	hkVector4d clamped; clamped.setSelect(maxValGtA, a, maxVal);
	setMax(minVal, clamped);
}

HK_FORCE_INLINE void hkVector4d::setClampedToMaxLength(hkVector4dParameter vSrc, hkSimdDouble64Parameter constMaxLen)
{
	// Make sure maxLen is > 0
	hkSimdDouble64 maxLen; maxLen.setMax(constMaxLen, hkSimdDouble64_Eps);

	// maxLen can be big, i.e. HK_DOUBLE_MAX, so we can't square it
	hkSimdDouble64 len = vSrc.length<3>();
	hkSimdDouble64 invLen; invLen.setReciprocal(len);

	// calc rescaled
	hkVector4d rescaledSrc;
	rescaledSrc.setMul(maxLen * invLen, vSrc);

	// choose
	setSelect(len.lessEqual(maxLen), vSrc, rescaledSrc);
}

HK_FORCE_INLINE void hkVector4d::setInt24W( int value )
{
	HK_MATH_ASSERT(0xf0781100, (value & 0xff000000) == 0, "can only store 24 bit integer");
	hkInt64 wideValue = hkInt64(value) | 0x3ff0000000000000ull;
	(reinterpret_cast<hkInt64*>(this))[3] = wideValue;
}

HK_FORCE_INLINE int hkVector4d::getInt24W( ) const
{
	return int ((reinterpret_cast<const hkInt64*>(this))[3] & ~0x3ff0000000000000ull);
}

HK_FORCE_INLINE int hkVector4d::getInt16W( ) const
{
#if HK_ENDIAN_LITTLE == 1
	return (reinterpret_cast<const hkUint16*>(this))[12];
#else
	return (reinterpret_cast<const hkUint16*>(this))[15];
#endif
}

template <>
HK_FORCE_INLINE int hkVector4d::findComponent<4>(hkSimdDouble64Parameter value) const
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	hkVector4d v; v.setAll(value);
	const hkVector4dComparison isEqual = equal(v);
	if (isEqual.anyIsSet())
		return isEqual.getIndexOfFirstComponentSet();
#else
	const hkDouble64* HK_RESTRICT tmp = (const hkDouble64* HK_RESTRICT)this;
	const hkDouble64* HK_RESTRICT v   = (const hkDouble64* HK_RESTRICT)&value;

	if (v[0] == tmp[0]) return 0;
	if (v[0] == tmp[1]) return 1;
	if (v[0] == tmp[2]) return 2;
	if (v[0] == tmp[3]) return 3;
#endif
	return -1;
}

template <>
HK_FORCE_INLINE int hkVector4d::findComponent<3>(hkSimdDouble64Parameter value) const
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	hkVector4d v; v.setAll(value);
	const hkVector4dComparison isEqual = equal(v);
	if (isEqual.anyIsSet<hkVector4ComparisonMask::MASK_XYZ>())
		return isEqual.getIndexOfFirstComponentSet();
#else
	const hkDouble64* HK_RESTRICT tmp = (const hkDouble64* HK_RESTRICT)this;
	const hkDouble64* HK_RESTRICT v   = (const hkDouble64* HK_RESTRICT)&value;

	if (v[0] == tmp[0]) return 0;
	if (v[0] == tmp[1]) return 1;
	if (v[0] == tmp[2]) return 2;
#endif
	return -1;
}

template <>
HK_FORCE_INLINE int hkVector4d::findComponent<2>(hkSimdDouble64Parameter value) const
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	hkVector4d v; v.setAll(value);
	const hkVector4dComparison isEqual = equal(v);
	if (isEqual.anyIsSet<hkVector4ComparisonMask::MASK_XY>())
		return isEqual.getIndexOfFirstComponentSet();
#else
	const hkDouble64* HK_RESTRICT tmp = (const hkDouble64* HK_RESTRICT)this;
	const hkDouble64* HK_RESTRICT v   = (const hkDouble64* HK_RESTRICT)&value;

	if (v[0] == tmp[0]) return 0;
	if (v[0] == tmp[1]) return 1;
#endif
	return -1;
}

template <>
HK_FORCE_INLINE int hkVector4d::findComponent<1>(hkSimdDouble64Parameter value) const
{
	return getComponent<0>().isEqual(value) ? 0 : -1;
}

template <int N>
HK_FORCE_INLINE int hkVector4d::findComponent(hkSimdDouble64Parameter value) const
{
	HK_VECTOR4d_NOT_IMPLEMENTED;
	return 0;
}


#ifndef HK_DISABLE_OLD_VECTOR4_INTERFACE

//
// old interface
//

HK_FORCE_INLINE hkQuadDouble64& hkVector4d::getQuad() { return m_quad; }
HK_FORCE_INLINE const hkQuadDouble64& hkVector4d::getQuad() const { return m_quad; }
HK_FORCE_INLINE void hkVector4d::operator=(const hkQuadDouble64& r) { m_quad = r; }
HK_FORCE_INLINE void hkVector4d::add4(hkVector4dParameter v) { add(v); }
HK_FORCE_INLINE void hkVector4d::sub4(hkVector4dParameter v) { sub(v); }
HK_FORCE_INLINE void hkVector4d::mul4(hkVector4dParameter a) { mul(a); }
HK_FORCE_INLINE void hkVector4d::mul4(hkSimdDouble64Parameter a) { mul(a); }
HK_FORCE_INLINE void hkVector4d::div4(hkVector4dParameter a) { div<HK_ACC_FULL,HK_DIV_IGNORE>(a); }
HK_FORCE_INLINE void hkVector4d::div4fast(hkVector4dParameter a) { div<HK_ACC_23_BIT,HK_DIV_IGNORE>(a); }
HK_FORCE_INLINE hkSimdDouble64 hkVector4d::dot3(hkVector4dParameter v) const { return dot<3>(v); }
HK_FORCE_INLINE hkSimdDouble64 hkVector4d::dot4(hkVector4dParameter a) const { return dot<4>(a); }
HK_FORCE_INLINE hkDouble64 hkVector4d::dot3fpu(hkVector4dParameter a) const { const hkVector4d& t = *this; return (t(0) * a(0)) + ( t(1) * a(1)) + ( t(2) * a(2) ); }
HK_FORCE_INLINE void hkVector4d::setMul4(hkVector4dParameter a, hkVector4dParameter b) { setMul(a,b); }
HK_FORCE_INLINE void hkVector4d::setMul4(hkSimdDouble64Parameter a, hkVector4dParameter b) { setMul(b,a); }
HK_FORCE_INLINE void hkVector4d::_setMul4xyz1(const hkTransformd& a, hkVector4dParameter b ) { _setTransformedPos(a,b); }
HK_FORCE_INLINE void hkVector4d::subMul4(hkVector4dParameter a, hkVector4dParameter b) { subMul(a,b); }
HK_FORCE_INLINE void hkVector4d::subMul4(hkSimdDouble64Parameter a, hkVector4dParameter b) { subMul(b,a); }
HK_FORCE_INLINE void hkVector4d::setSubMul4(hkVector4dParameter a, hkVector4dParameter x, hkVector4dParameter y) { setSubMul(a,x,y); }
HK_FORCE_INLINE void hkVector4d::setSubMul4(hkVector4dParameter a, hkVector4dParameter x, hkSimdDouble64Parameter y) { setSubMul(a,x,y); }
HK_FORCE_INLINE void hkVector4d::setDot3(hkVector4dParameter a, hkVector4dParameter b) { setDot<3>(a,b); }
HK_FORCE_INLINE void hkVector4d::setDot4(hkVector4dParameter a, hkVector4dParameter b) { setDot<4>(a,b); }
HK_FORCE_INLINE void hkVector4d::setSelect4( hkVector4dComparisonParameter comp, hkVector4dParameter trueValue, hkVector4dParameter falseValue) { setSelect(comp,trueValue,falseValue); }
HK_FORCE_INLINE void hkVector4d::select32( hkVector4dParameter falseValue, hkVector4dParameter trueValue, hkVector4dComparisonParameter comp) { setSelect(comp,trueValue,falseValue); }
HK_FORCE_INLINE void hkVector4d::setBroadcast(hkVector4dParameter v, int i) { setBroadcast(i,v); }
HK_FORCE_INLINE void hkVector4d::setBroadcast3clobberW(hkVector4dParameter v, int i) { setBroadcastXYZ(i,v); }
HK_FORCE_INLINE void hkVector4d::setXYZW(hkVector4dParameter xyz, hkVector4dParameter w) { setXYZ_W(xyz,w); }
HK_FORCE_INLINE void hkVector4d::setXYZW(hkVector4dParameter xyz, hkSimdDouble64Parameter w) { setXYZ_W(xyz,w); }
HK_FORCE_INLINE void hkVector4d::setXYZ0(hkVector4dParameter xyz) { setXYZ_0(xyz); }
HK_FORCE_INLINE void hkVector4d::addMul4(hkVector4dParameter a, hkVector4dParameter b) { addMul(a,b); }
HK_FORCE_INLINE void hkVector4d::addMul4(hkSimdDouble64Parameter a, hkVector4dParameter b) { addMul(b,a); }
HK_FORCE_INLINE void hkVector4d::setZero4() { setZero(); }
HK_FORCE_INLINE void hkVector4d::setAll3(hkDouble64 x) { setZero(); setXYZ(x); }
HK_FORCE_INLINE void hkVector4d::zeroElement( int i ) { zeroComponent(i); }
HK_FORCE_INLINE void hkVector4d::setNeg3(hkVector4dParameter v) { setNeg<3>(v); }
HK_FORCE_INLINE void hkVector4d::setNeg4(hkVector4dParameter v) { setNeg<4>(v); }
HK_FORCE_INLINE void hkVector4d::setNegMask4(hkVector4dParameter v, int mask) { hkVector4dComparison cmp; cmp.set((hkVector4ComparisonMask::Mask)mask); setFlipSign(v, cmp); }
HK_FORCE_INLINE void hkVector4d::setDiv4(hkVector4dParameter a, hkVector4dParameter b) { setDiv<HK_ACC_FULL,HK_DIV_IGNORE>(a,b); }
HK_FORCE_INLINE void hkVector4d::setDiv4fast(hkVector4dParameter a, hkVector4dParameter b) { setDiv<HK_ACC_12_BIT,HK_DIV_IGNORE>(a,b); }
HK_FORCE_INLINE hkSimdDouble64 hkVector4d::getSimdAt(int i) const { return getComponent(i); }
HK_FORCE_INLINE void hkVector4d::normalize3() { normalize<3,HK_ACC_23_BIT,HK_SQRT_SET_ZERO>(); }
HK_FORCE_INLINE void hkVector4d::normalize4() { normalize<4,HK_ACC_23_BIT,HK_SQRT_SET_ZERO>(); }
HK_FORCE_INLINE void hkVector4d::fastNormalize3() { normalize<3,HK_ACC_12_BIT,HK_SQRT_SET_ZERO>(); }
HK_FORCE_INLINE void hkVector4d::fastNormalize3NonZero() { normalize<3,HK_ACC_12_BIT,HK_SQRT_IGNORE>(); }
HK_FORCE_INLINE void hkVector4d::setFastNormalize3NonZero(hkVector4dParameter a) { *this = a; normalize<3,HK_ACC_12_BIT,HK_SQRT_IGNORE>(); }
HK_FORCE_INLINE hkSimdDouble64 hkVector4d::normalizeWithLength3() { return normalizeWithLength<3,HK_ACC_23_BIT,HK_SQRT_SET_ZERO>(); }
HK_FORCE_INLINE hkSimdDouble64 hkVector4d::normalizeWithLength4() { return normalizeWithLength<4,HK_ACC_23_BIT,HK_SQRT_SET_ZERO>(); }
HK_FORCE_INLINE hkSimdDouble64 hkVector4d::fastNormalizeWithLength3() { return normalizeWithLength<3,HK_ACC_12_BIT,HK_SQRT_SET_ZERO>(); }
HK_FORCE_INLINE hkResult hkVector4d::normalize3IfNotZero () { return (normalizeIfNotZero<3>() ? HK_SUCCESS : HK_FAILURE); }
HK_FORCE_INLINE hkSimdDouble64 hkVector4d::length3() const { return length<3>(); }
HK_FORCE_INLINE hkSimdDouble64 hkVector4d::length4() const { return length<4>(); }
HK_FORCE_INLINE hkSimdDouble64 hkVector4d::lengthSquared3() const { return lengthSquared<3>(); }
HK_FORCE_INLINE hkSimdDouble64 hkVector4d::lengthSquared4() const { return lengthSquared<4>(); }
HK_FORCE_INLINE hkSimdDouble64 hkVector4d::lengthInverse3() const { return lengthInverse<3,HK_ACC_23_BIT,HK_SQRT_SET_ZERO>(); }
HK_FORCE_INLINE hkSimdDouble64 hkVector4d::lengthInverse4() const { return lengthInverse<4,HK_ACC_23_BIT,HK_SQRT_SET_ZERO>(); }
HK_FORCE_INLINE void hkVector4d::setAdd4(hkVector4dParameter a, hkVector4dParameter b) { setAdd(a,b); }
HK_FORCE_INLINE void hkVector4d::setSub4(hkVector4dParameter a, hkVector4dParameter b) { setSub(a,b); }
HK_FORCE_INLINE void hkVector4d::setSqrtInverse4(hkVector4dParameter v) { setSqrtInverse<HK_ACC_23_BIT,HK_SQRT_IGNORE>(v); }
HK_FORCE_INLINE void hkVector4d::setSqrtInverse4_7BitAccuracy(hkVector4dParameter v) { setSqrtInverse<HK_ACC_12_BIT,HK_SQRT_IGNORE>(v); }
HK_FORCE_INLINE void hkVector4d::setReciprocal3(hkVector4dParameter v) { setReciprocal<HK_ACC_23_BIT,HK_DIV_IGNORE>(v); setComponent<3>(hkSimdDouble64::getConstant(HK_QUADREAL_1)); }
HK_FORCE_INLINE void hkVector4d::setReciprocal4(hkVector4dParameter v) { setReciprocal<HK_ACC_23_BIT,HK_DIV_IGNORE>(v); }
HK_FORCE_INLINE void hkVector4d::setAddMul4(hkVector4dParameter a, hkVector4dParameter x, hkVector4dParameter y) { setAddMul(a,x,y); }
HK_FORCE_INLINE void hkVector4d::setAddMul4(hkVector4dParameter a, hkVector4dParameter b, hkSimdDouble64Parameter r) { setAddMul(a,b,r); }
HK_FORCE_INLINE void hkVector4d::setAbs4(hkVector4dParameter v) { setAbs(v); }
HK_FORCE_INLINE void hkVector4d::setMin4(hkVector4dParameter a, hkVector4dParameter b) { setMin(a,b); }
HK_FORCE_INLINE void hkVector4d::setMax4(hkVector4dParameter a, hkVector4dParameter b) { setMax(a,b); }
HK_FORCE_INLINE hkBool32 hkVector4d::equals3(const hkVector4d &v, hkDouble64 epsilon ) const
{
	hkVector4d t;
	t.setSub(*this, v);
	t.setAbs( t );
	hkVector4d epsilon_v;
	epsilon_v.setAll(epsilon);
	return t.lessEqual( epsilon_v ).allAreSet<hkVector4ComparisonMask::MASK_XYZ>();
}	
HK_FORCE_INLINE hkBool32 hkVector4d::equals4(const hkVector4d &v, hkDouble64 epsilon ) const
{
	hkVector4d t;
	t.setSub(*this, v);
	t.setAbs( t );
	hkVector4d epsilon_v;
	epsilon_v.setAll(epsilon);
	return t.lessEqual( epsilon_v ).allAreSet();
}
HK_FORCE_INLINE hkVector4dComparison hkVector4d::compareEqual4(hkVector4dParameter a) const { return equal(a); }
HK_FORCE_INLINE hkVector4dComparison hkVector4d::compareLessThan4(hkVector4dParameter a) const { return less(a); }
HK_FORCE_INLINE hkVector4dComparison hkVector4d::compareLessThanEqual4(hkVector4dParameter a) const { return lessEqual(a); }
HK_FORCE_INLINE hkVector4dComparison hkVector4d::compareGreaterThan4(hkVector4dParameter a) const { return greater(a); }
HK_FORCE_INLINE hkVector4dComparison hkVector4d::compareGreaterThanEqual4(hkVector4dParameter a) const { return greaterEqual(a); }
HK_FORCE_INLINE hkVector4dComparison hkVector4d::compareLessThanZero4() const { return lessZero(); }
HK_FORCE_INLINE hkBool32 hkVector4d::allLessThan3(hkVector4dParameter a) const { return allLess<3>(a); }
HK_FORCE_INLINE hkBool32 hkVector4d::allLessThan4(hkVector4dParameter a) const { return allLess<4>(a); }
HK_FORCE_INLINE void hkVector4d::setInterpolate4( hkVector4dParameter a, hkVector4dParameter b, hkSimdDouble64Parameter t ) { setInterpolate(a,b,t); }
HK_FORCE_INLINE hkSimdDouble64 hkVector4d::distanceTo3( hkVector4dParameter p ) const { return distanceTo(p); }
HK_FORCE_INLINE hkSimdDouble64 hkVector4d::distanceToSquared3( hkVector4dParameter p ) const { return distanceToSquared(p); }
HK_FORCE_INLINE hkSimdDouble64 hkVector4d::horizontalAdd3() const { return horizontalAdd<3>(); }
HK_FORCE_INLINE void hkVector4d::setHorizontalMax4( hkVector4dParameter p) { setHorizontalMax<4>(p); }
HK_FORCE_INLINE hkSimdDouble64 hkVector4d::getHorizontalMin3() const { return horizontalMin<3>(); }
HK_FORCE_INLINE hkSimdDouble64 hkVector4d::getHorizontalMax3() const { return horizontalMax<3>(); }
HK_FORCE_INLINE void hkVector4d::add3clobberW(hkVector4dParameter a) { addXYZ(a); }
HK_FORCE_INLINE hkSimdDouble64 hkVector4d::horizontalAdd4() const { return horizontalAdd<4>(); }
HK_FORCE_INLINE void hkVector4d::setClamped(hkVector4dParameter vSrc, const hkSimdDouble64& constMaxLen) { setClampedToMaxLength(vSrc, constMaxLen); }
HK_FORCE_INLINE	int hkVector4d::getMaxElementIndex4() const { return getIndexOfMaxComponent<4>(); }
HK_FORCE_INLINE	int hkVector4d::getMajorAxis3() const { return getIndexOfMaxAbsComponent<3>(); }
HK_FORCE_INLINE void hkVector4d::storeUncached( void* dest) const { store<4,HK_IO_NOT_CACHED>((hkDouble64*)dest); }
HK_FORCE_INLINE void hkVector4d::storeX( hkFloat32* dest)  const { store<1>(dest); }
HK_FORCE_INLINE void hkVector4d::storeX( hkDouble64* dest) const { store<1>(dest); }
HK_FORCE_INLINE void hkVector4d::sub3clobberW(hkVector4dParameter a) { subXYZ(a); }
HK_FORCE_INLINE void hkVector4d::_setMul3(const hkMatrix3d& a, hkVector4dParameter b) { _setRotatedDir(a,b); }
template <int S> HK_FORCE_INLINE void hkVector4d::setShuffle(hkVector4dParameter v) { setPermutation<(hkVectorPermutation::Permutation)S>(v); }
HK_FORCE_INLINE void hkVector4d::setAnd( hkVector4dParameter v0, hkVector4dParameter v1 ) { HK_ERROR(0x650a4a31,"not implemented"); }
HK_FORCE_INLINE void hkVector4d::setSwapXY(const hkVector4d& w) { setPermutation<hkVectorPermutation::YXZW>(w); }
HK_FORCE_INLINE void hkVector4d::setMulSigns4(hkVector4dParameter a, hkVector4dParameter signs) { setFlipSign(a, signs); }
HK_FORCE_INLINE void hkVector4d::setMulSigns4(hkVector4dParameter a, hkSimdDouble64Parameter sharedSign) { setFlipSign(a, sharedSign); }
HK_FORCE_INLINE hkBool hkVector4d::isNormalized3(hkDouble64 eps) const { return isNormalized<3>(eps); }
HK_FORCE_INLINE hkBool hkVector4d::isNormalized4(hkDouble64 eps) const { return isNormalized<4>(eps); }
HK_FORCE_INLINE hkBool hkVector4d::isOk3() const { return (hkBool)isOk<3>(); }
HK_FORCE_INLINE hkBool hkVector4d::isOk4() const { return (hkBool)isOk<4>(); }
HK_FORCE_INLINE const hkVector4dComparison hkVector4d::isNegative() const { return signBitSet(); }
HK_FORCE_INLINE const hkVector4dComparison hkVector4d::isPositive() const { return signBitClear(); }
HK_FORCE_INLINE void hkVector4d::load3(const hkFloat32* p) { load<3,HK_IO_NATIVE_ALIGNED>(p); }
HK_FORCE_INLINE void hkVector4d::load4(const hkFloat32* p) { load<4,HK_IO_NATIVE_ALIGNED>(p); }
HK_FORCE_INLINE void hkVector4d::load4a(const hkFloat32* p) { load<4,HK_IO_SIMD_ALIGNED>(p); }
HK_FORCE_INLINE void hkVector4d::load3(const hkDouble64* p) { load<3,HK_IO_NATIVE_ALIGNED>(p); }
HK_FORCE_INLINE void hkVector4d::load4(const hkDouble64* p) { load<4,HK_IO_NATIVE_ALIGNED>(p); }
HK_FORCE_INLINE void hkVector4d::load4a(const hkDouble64* p) { load<4,HK_IO_SIMD_ALIGNED>(p); }
HK_FORCE_INLINE void hkVector4d::store3(hkFloat32* p) const { store<3,HK_IO_NATIVE_ALIGNED>(p); }
HK_FORCE_INLINE void hkVector4d::store4(hkFloat32* p) const { store<4,HK_IO_NATIVE_ALIGNED>(p); }
HK_FORCE_INLINE void hkVector4d::store4a(hkFloat32* p) const { store<4,HK_IO_SIMD_ALIGNED>(p); }
HK_FORCE_INLINE void hkVector4d::store3(hkDouble64* p) const { store<3,HK_IO_NATIVE_ALIGNED>(p); }
HK_FORCE_INLINE void hkVector4d::store4(hkDouble64* p) const { store<4,HK_IO_NATIVE_ALIGNED>(p); }
HK_FORCE_INLINE void hkVector4d::store4a(hkDouble64* p) const { store<4,HK_IO_SIMD_ALIGNED>(p); }
HK_FORCE_INLINE void hkVector4d::setMul3(const hkMatrix3d& a, hkVector4dParameter b ) { _setRotatedDir(a,b); }
HK_FORCE_INLINE void hkVector4d::_setMul4(const hkMatrix3d& a, hkVector4dParameter b ) { _setRotatedDir(a,b); }

#endif

//
// advanced interface
//

template <int N, hkMathAccuracyMode A, hkMathNegSqrtMode S> 
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::length() const
{
	const hkSimdDouble64 len2 = lengthSquared<N>();
	return len2.sqrt<A,S>();
}

template <int N>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::length() const
{
	return length<N,HK_ACC_23_BIT,HK_SQRT_SET_ZERO>();
}

template <int N, hkMathAccuracyMode A, hkMathNegSqrtMode S> 
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::lengthInverse() const
{
	const hkSimdDouble64 len2 = lengthSquared<N>();
	return len2.sqrtInverse<A,S>();
}

template <int N>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::lengthInverse() const
{
	return lengthInverse<N,HK_ACC_23_BIT,HK_SQRT_SET_ZERO>();
}

template <int N, hkMathAccuracyMode A, hkMathNegSqrtMode S>
HK_FORCE_INLINE void hkVector4d::normalize()
{
	mul( lengthInverse<N,A,S>() );
}

template <int N>
HK_FORCE_INLINE void hkVector4d::normalize()
{
	normalize<N,HK_ACC_23_BIT,HK_SQRT_SET_ZERO>();
}

template <int N, hkMathAccuracyMode A, hkMathNegSqrtMode S>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::normalizeWithLength()
{
	const hkSimdDouble64 len2 = lengthSquared<N>();
	const hkSimdDouble64 lenInv = len2.sqrtInverse<A,S>();
	mul(lenInv);
	return (len2 * lenInv); // quicker to return x^2/x
}

template <int N>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::normalizeWithLength()
{
	return normalizeWithLength<N,HK_ACC_23_BIT,HK_SQRT_SET_ZERO>();
}

template <int N, hkMathAccuracyMode A, hkMathNegSqrtMode S>
HK_FORCE_INLINE hkBool32 hkVector4d::normalizeIfNotZero()
{
	const hkSimdDouble64 lengthSqrd = lengthSquared<N>();
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	const hkVector4dComparison less0 = ( -lengthSqrd ).lessZero();

	hkVector4d normThis; normThis.setMul(*this, lengthSqrd.sqrtInverse<A,S>());
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
HK_FORCE_INLINE hkBool32 hkVector4d::normalizeIfNotZero()
{
	return normalizeIfNotZero<N,HK_ACC_23_BIT,HK_SQRT_SET_ZERO>();
}

template <hkMathAccuracyMode A, hkMathNegSqrtMode S>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::distanceTo(hkVector4dParameter p) const
{
	const hkSimdDouble64 d2 = distanceToSquared(p);
	const hkSimdDouble64 ri = d2.sqrtInverse<A,S>();
	return (d2 * ri);
}

HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::distanceTo(hkVector4dParameter p) const
{
	return distanceToSquared(p).sqrt<HK_ACC_23_BIT,HK_SQRT_SET_ZERO>();
}


template <int N, hkMathAccuracyMode A>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::setNormalizedEnsureUnitLength(hkVector4dParameter v)
{
	const hkSimdDouble64 length2 = v.lengthSquared<N>();
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	const hkVector4dComparison lengthLessEps = length2.less(hkSimdDouble64_EpsSqrd);

	hkSimdDouble64 invLength;
	if ( A == HK_ACC_FULL )
	{
		 invLength = length2.sqrtInverse<A,HK_SQRT_SET_ZERO>();
	}
	else
	{
		 invLength = length2.sqrtInverse<A,HK_SQRT_IGNORE>();
	}
	hkVector4d normV; normV.setMul(v,invLength);
	setSelect(lengthLessEps, hkVector4d::getConstant<HK_QUADREAL_1000>(), normV);

	hkSimdDouble64 oldLength = length2 * invLength;
	oldLength.zeroIfTrue(lengthLessEps);
	return oldLength;
#else
	if (length2.isGreaterEqual(hkSimdDouble64::getConstant<HK_QUADREAL_EPS_SQRD>()))
	{
		const hkSimdDouble64 invLength = length2.sqrtInverse<A,HK_SQRT_IGNORE>();
		setMul(v,invLength);
		return (length2 * invLength);
	}
	m_quad = g_vectordConstants[HK_QUADREAL_1000];
	return hkSimdDouble64_0;
#endif
}

template <int N>
HK_FORCE_INLINE const hkSimdDouble64 hkVector4d::setNormalizedEnsureUnitLength(hkVector4dParameter v)
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
