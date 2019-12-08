/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

/* quad, here for inlining */

#ifndef HK_DISABLE_MATH_CONSTRUCTORS
HK_FORCE_INLINE hkVector4f::hkVector4f(hkFloat32 a, hkFloat32 b, hkFloat32 c, hkFloat32 d)
{
	m_quad.v[0] = a;
	m_quad.v[1] = b;
	m_quad.v[2] = c;
	m_quad.v[3] = d;
}

HK_FORCE_INLINE hkVector4f::hkVector4f(const hkQuadFloat32& q)
{
	m_quad.v[0] = q.v[0];
	m_quad.v[1] = q.v[1];
	m_quad.v[2] = q.v[2];
	m_quad.v[3] = q.v[3];
}

HK_FORCE_INLINE hkVector4f::hkVector4f( const hkVector4f& v)
{
	m_quad.v[0] = v.m_quad.v[0];
	m_quad.v[1] = v.m_quad.v[1];
	m_quad.v[2] = v.m_quad.v[2];
	m_quad.v[3] = v.m_quad.v[3];
}
#endif

HK_FORCE_INLINE void hkVector4f::set(hkFloat32 a, hkFloat32 b, hkFloat32 c, hkFloat32 d)
{
	m_quad.v[0] = a;
	m_quad.v[1] = b;
	m_quad.v[2] = c;
	m_quad.v[3] = d;
}

HK_FORCE_INLINE void hkVector4f::set( hkSimdFloat32Parameter a, hkSimdFloat32Parameter b, hkSimdFloat32Parameter c, hkSimdFloat32Parameter d )
{
	m_quad.v[0] = a.getReal();
	m_quad.v[1] = b.getReal();
	m_quad.v[2] = c.getReal();
	m_quad.v[3] = d.getReal();
}

HK_FORCE_INLINE void hkVector4f::setAll(const hkFloat32& a)
{
	m_quad.v[0] = a;
	m_quad.v[1] = a;
	m_quad.v[2] = a;
	m_quad.v[3] = a;
}

HK_FORCE_INLINE void hkVector4f::setAll(hkSimdFloat32Parameter a)
{
	setAll( a.getReal() );
}

HK_FORCE_INLINE void hkVector4f::setZero()
{
	m_quad.v[0] = hkFloat32(0);
	m_quad.v[1] = hkFloat32(0);
	m_quad.v[2] = hkFloat32(0);
	m_quad.v[3] = hkFloat32(0);
}

template <int I> 
HK_FORCE_INLINE void hkVector4f::zeroComponent()
{
	HK_VECTOR4f_SUBINDEX_CHECK;
	m_quad.v[I] = hkFloat32(0);
}

HK_FORCE_INLINE void hkVector4f::zeroComponent(const int i)
{
	HK_MATH_ASSERT(0x3bc36625, (i>=0) && (i<4), "Component index out of range");
	m_quad.v[i] = hkFloat32(0);
}

HK_FORCE_INLINE void hkVector4f::setAdd(hkVector4fParameter v0, hkVector4fParameter v1)
{
	m_quad.v[0] = v0.m_quad.v[0] + v1.m_quad.v[0];
	m_quad.v[1] = v0.m_quad.v[1] + v1.m_quad.v[1];
	m_quad.v[2] = v0.m_quad.v[2] + v1.m_quad.v[2];
	m_quad.v[3] = v0.m_quad.v[3] + v1.m_quad.v[3];
}

HK_FORCE_INLINE void hkVector4f::setSub(hkVector4fParameter v0, hkVector4fParameter v1)
{
	m_quad.v[0] = v0.m_quad.v[0] - v1.m_quad.v[0];
	m_quad.v[1] = v0.m_quad.v[1] - v1.m_quad.v[1];
	m_quad.v[2] = v0.m_quad.v[2] - v1.m_quad.v[2];
	m_quad.v[3] = v0.m_quad.v[3] - v1.m_quad.v[3];
}

HK_FORCE_INLINE void hkVector4f::setMul(hkVector4fParameter v0, hkVector4fParameter v1)
{
	m_quad.v[0] = v0.m_quad.v[0] * v1.m_quad.v[0];
	m_quad.v[1] = v0.m_quad.v[1] * v1.m_quad.v[1];
	m_quad.v[2] = v0.m_quad.v[2] * v1.m_quad.v[2];
	m_quad.v[3] = v0.m_quad.v[3] * v1.m_quad.v[3];
}

HK_FORCE_INLINE void hkVector4f::setMul(hkVector4fParameter a, hkSimdFloat32Parameter rs)
{
	const hkFloat32 r = rs.getReal();
	m_quad.v[0] = r * a.m_quad.v[0];
	m_quad.v[1] = r * a.m_quad.v[1];
	m_quad.v[2] = r * a.m_quad.v[2];
	m_quad.v[3] = r * a.m_quad.v[3];
}

HK_FORCE_INLINE void hkVector4f::setSubMul(hkVector4fParameter a, hkVector4fParameter b, hkSimdFloat32Parameter r)
{
	const hkFloat32 rr = r.getReal();
	m_quad.v[0] = a.m_quad.v[0] - rr * b.m_quad.v[0];
	m_quad.v[1] = a.m_quad.v[1] - rr * b.m_quad.v[1];
	m_quad.v[2] = a.m_quad.v[2] - rr * b.m_quad.v[2];
	m_quad.v[3] = a.m_quad.v[3] - rr * b.m_quad.v[3];
}

HK_FORCE_INLINE void hkVector4f::setAddMul(hkVector4fParameter a, hkVector4fParameter b, hkSimdFloat32Parameter r)
{
	const hkFloat32 rr = r.getReal();
	m_quad.v[0] = a.m_quad.v[0] + rr * b.m_quad.v[0];
	m_quad.v[1] = a.m_quad.v[1] + rr * b.m_quad.v[1];
	m_quad.v[2] = a.m_quad.v[2] + rr * b.m_quad.v[2];
	m_quad.v[3] = a.m_quad.v[3] + rr * b.m_quad.v[3];
}

HK_FORCE_INLINE void hkVector4f::setAddMul(hkVector4fParameter a, hkVector4fParameter m0, hkVector4fParameter m1)
{
	m_quad.v[0] = a.m_quad.v[0] + m0.m_quad.v[0] * m1.m_quad.v[0];
	m_quad.v[1] = a.m_quad.v[1] + m0.m_quad.v[1] * m1.m_quad.v[1];
	m_quad.v[2] = a.m_quad.v[2] + m0.m_quad.v[2] * m1.m_quad.v[2];
	m_quad.v[3] = a.m_quad.v[3] + m0.m_quad.v[3] * m1.m_quad.v[3];
}

HK_FORCE_INLINE void hkVector4f::setSubMul(hkVector4fParameter a, hkVector4fParameter m0, hkVector4fParameter m1)
{
	m_quad.v[0] = a.m_quad.v[0] - m0.m_quad.v[0] * m1.m_quad.v[0];
	m_quad.v[1] = a.m_quad.v[1] - m0.m_quad.v[1] * m1.m_quad.v[1];
	m_quad.v[2] = a.m_quad.v[2] - m0.m_quad.v[2] * m1.m_quad.v[2];
	m_quad.v[3] = a.m_quad.v[3] - m0.m_quad.v[3] * m1.m_quad.v[3];
}

HK_FORCE_INLINE void hkVector4f::setCross( hkVector4fParameter v1, hkVector4fParameter v2 )
{
	const hkFloat32 nx = v1.m_quad.v[1]*v2.m_quad.v[2] - v1.m_quad.v[2]*v2.m_quad.v[1];
	const hkFloat32 ny = v1.m_quad.v[2]*v2.m_quad.v[0] - v1.m_quad.v[0]*v2.m_quad.v[2];
	const hkFloat32 nz = v1.m_quad.v[0]*v2.m_quad.v[1] - v1.m_quad.v[1]*v2.m_quad.v[0];
	set( nx, ny, nz , hkFloat32(0) );
}

HK_FORCE_INLINE const hkVector4fComparison hkVector4f::equal(hkVector4fParameter a) const
{
	hkVector4fComparison ret;
	ret.m_mask =
		((m_quad.v[0]==a.m_quad.v[0]) ? hkVector4ComparisonMask::MASK_X : hkVector4ComparisonMask::MASK_NONE) |
		((m_quad.v[1]==a.m_quad.v[1]) ? hkVector4ComparisonMask::MASK_Y : hkVector4ComparisonMask::MASK_NONE) |
		((m_quad.v[2]==a.m_quad.v[2]) ? hkVector4ComparisonMask::MASK_Z : hkVector4ComparisonMask::MASK_NONE) |
		((m_quad.v[3]==a.m_quad.v[3]) ? hkVector4ComparisonMask::MASK_W : hkVector4ComparisonMask::MASK_NONE);
	return ret;
}

HK_FORCE_INLINE const hkVector4fComparison hkVector4f::notEqual(hkVector4fParameter a) const
{
	hkVector4fComparison ret;
	ret.m_mask =
		((m_quad.v[0]==a.m_quad.v[0]) ? hkVector4ComparisonMask::MASK_NONE : hkVector4ComparisonMask::MASK_X) |
		((m_quad.v[1]==a.m_quad.v[1]) ? hkVector4ComparisonMask::MASK_NONE : hkVector4ComparisonMask::MASK_Y) |
		((m_quad.v[2]==a.m_quad.v[2]) ? hkVector4ComparisonMask::MASK_NONE : hkVector4ComparisonMask::MASK_Z) |
		((m_quad.v[3]==a.m_quad.v[3]) ? hkVector4ComparisonMask::MASK_NONE : hkVector4ComparisonMask::MASK_W);
	return ret;
}

HK_FORCE_INLINE const hkVector4fComparison hkVector4f::less(hkVector4fParameter a) const
{
	hkVector4fComparison ret;
	ret.m_mask =
		((m_quad.v[0]<a.m_quad.v[0]) ? hkVector4ComparisonMask::MASK_X : hkVector4ComparisonMask::MASK_NONE) |
		((m_quad.v[1]<a.m_quad.v[1]) ? hkVector4ComparisonMask::MASK_Y : hkVector4ComparisonMask::MASK_NONE) |
		((m_quad.v[2]<a.m_quad.v[2]) ? hkVector4ComparisonMask::MASK_Z : hkVector4ComparisonMask::MASK_NONE) |
		((m_quad.v[3]<a.m_quad.v[3]) ? hkVector4ComparisonMask::MASK_W : hkVector4ComparisonMask::MASK_NONE);
	return ret;
}

HK_FORCE_INLINE const hkVector4fComparison hkVector4f::lessEqual(hkVector4fParameter a) const
{
	hkVector4fComparison ret;
	ret.m_mask =
		((m_quad.v[0]<=a.m_quad.v[0]) ? hkVector4ComparisonMask::MASK_X : hkVector4ComparisonMask::MASK_NONE) |
		((m_quad.v[1]<=a.m_quad.v[1]) ? hkVector4ComparisonMask::MASK_Y : hkVector4ComparisonMask::MASK_NONE) |
		((m_quad.v[2]<=a.m_quad.v[2]) ? hkVector4ComparisonMask::MASK_Z : hkVector4ComparisonMask::MASK_NONE) |
		((m_quad.v[3]<=a.m_quad.v[3]) ? hkVector4ComparisonMask::MASK_W : hkVector4ComparisonMask::MASK_NONE);
	return ret;
}

HK_FORCE_INLINE const hkVector4fComparison hkVector4f::greater(hkVector4fParameter a) const
{
	hkVector4fComparison ret;
	ret.m_mask =
		((m_quad.v[0]>a.m_quad.v[0]) ? hkVector4ComparisonMask::MASK_X : hkVector4ComparisonMask::MASK_NONE) |
		((m_quad.v[1]>a.m_quad.v[1]) ? hkVector4ComparisonMask::MASK_Y : hkVector4ComparisonMask::MASK_NONE) |
		((m_quad.v[2]>a.m_quad.v[2]) ? hkVector4ComparisonMask::MASK_Z : hkVector4ComparisonMask::MASK_NONE) |
		((m_quad.v[3]>a.m_quad.v[3]) ? hkVector4ComparisonMask::MASK_W : hkVector4ComparisonMask::MASK_NONE);
	return ret;
}

HK_FORCE_INLINE const hkVector4fComparison hkVector4f::greaterEqual(hkVector4fParameter a) const
{
	hkVector4fComparison ret;
	ret.m_mask =
		((m_quad.v[0]>=a.m_quad.v[0]) ? hkVector4ComparisonMask::MASK_X : hkVector4ComparisonMask::MASK_NONE) |
		((m_quad.v[1]>=a.m_quad.v[1]) ? hkVector4ComparisonMask::MASK_Y : hkVector4ComparisonMask::MASK_NONE) |
		((m_quad.v[2]>=a.m_quad.v[2]) ? hkVector4ComparisonMask::MASK_Z : hkVector4ComparisonMask::MASK_NONE) |
		((m_quad.v[3]>=a.m_quad.v[3]) ? hkVector4ComparisonMask::MASK_W : hkVector4ComparisonMask::MASK_NONE);
	return ret;
}

HK_FORCE_INLINE const hkVector4fComparison hkVector4f::lessZero() const
{
	hkVector4fComparison ret;
	ret.m_mask =
		((m_quad.v[0]<hkFloat32(0)) ? hkVector4ComparisonMask::MASK_X : hkVector4ComparisonMask::MASK_NONE) |
		((m_quad.v[1]<hkFloat32(0)) ? hkVector4ComparisonMask::MASK_Y : hkVector4ComparisonMask::MASK_NONE) |
		((m_quad.v[2]<hkFloat32(0)) ? hkVector4ComparisonMask::MASK_Z : hkVector4ComparisonMask::MASK_NONE) |
		((m_quad.v[3]<hkFloat32(0)) ? hkVector4ComparisonMask::MASK_W : hkVector4ComparisonMask::MASK_NONE);
	return ret;
}

HK_FORCE_INLINE const hkVector4fComparison hkVector4f::lessEqualZero() const
{
	hkVector4fComparison ret;
	ret.m_mask =
		((m_quad.v[0]<=hkFloat32(0)) ? hkVector4ComparisonMask::MASK_X : hkVector4ComparisonMask::MASK_NONE) |
		((m_quad.v[1]<=hkFloat32(0)) ? hkVector4ComparisonMask::MASK_Y : hkVector4ComparisonMask::MASK_NONE) |
		((m_quad.v[2]<=hkFloat32(0)) ? hkVector4ComparisonMask::MASK_Z : hkVector4ComparisonMask::MASK_NONE) |
		((m_quad.v[3]<=hkFloat32(0)) ? hkVector4ComparisonMask::MASK_W : hkVector4ComparisonMask::MASK_NONE);
	return ret;
}

HK_FORCE_INLINE const hkVector4fComparison hkVector4f::greaterZero() const
{
	hkVector4fComparison ret;
	ret.m_mask =
		((m_quad.v[0]>hkFloat32(0)) ? hkVector4ComparisonMask::MASK_X : hkVector4ComparisonMask::MASK_NONE) |
		((m_quad.v[1]>hkFloat32(0)) ? hkVector4ComparisonMask::MASK_Y : hkVector4ComparisonMask::MASK_NONE) |
		((m_quad.v[2]>hkFloat32(0)) ? hkVector4ComparisonMask::MASK_Z : hkVector4ComparisonMask::MASK_NONE) |
		((m_quad.v[3]>hkFloat32(0)) ? hkVector4ComparisonMask::MASK_W : hkVector4ComparisonMask::MASK_NONE);
	return ret;
}

HK_FORCE_INLINE const hkVector4fComparison hkVector4f::greaterEqualZero() const
{
	hkVector4fComparison ret;
	ret.m_mask =
		((m_quad.v[0]>=hkFloat32(0)) ? hkVector4ComparisonMask::MASK_X : hkVector4ComparisonMask::MASK_NONE) |
		((m_quad.v[1]>=hkFloat32(0)) ? hkVector4ComparisonMask::MASK_Y : hkVector4ComparisonMask::MASK_NONE) |
		((m_quad.v[2]>=hkFloat32(0)) ? hkVector4ComparisonMask::MASK_Z : hkVector4ComparisonMask::MASK_NONE) |
		((m_quad.v[3]>=hkFloat32(0)) ? hkVector4ComparisonMask::MASK_W : hkVector4ComparisonMask::MASK_NONE);
	return ret;
}

HK_FORCE_INLINE const hkVector4fComparison hkVector4f::equalZero() const
{
	hkVector4fComparison ret;
	ret.m_mask =
		((m_quad.v[0]==hkFloat32(0)) ? hkVector4ComparisonMask::MASK_X : hkVector4ComparisonMask::MASK_NONE) |
		((m_quad.v[1]==hkFloat32(0)) ? hkVector4ComparisonMask::MASK_Y : hkVector4ComparisonMask::MASK_NONE) |
		((m_quad.v[2]==hkFloat32(0)) ? hkVector4ComparisonMask::MASK_Z : hkVector4ComparisonMask::MASK_NONE) |
		((m_quad.v[3]==hkFloat32(0)) ? hkVector4ComparisonMask::MASK_W : hkVector4ComparisonMask::MASK_NONE);
	return ret;
}

HK_FORCE_INLINE const hkVector4fComparison hkVector4f::notEqualZero() const
{
	hkVector4fComparison ret;
	ret.m_mask =
		((m_quad.v[0]==hkFloat32(0)) ? hkVector4ComparisonMask::MASK_NONE : hkVector4ComparisonMask::MASK_X) |
		((m_quad.v[1]==hkFloat32(0)) ? hkVector4ComparisonMask::MASK_NONE : hkVector4ComparisonMask::MASK_Y) |
		((m_quad.v[2]==hkFloat32(0)) ? hkVector4ComparisonMask::MASK_NONE : hkVector4ComparisonMask::MASK_Z) |
		((m_quad.v[3]==hkFloat32(0)) ? hkVector4ComparisonMask::MASK_NONE : hkVector4ComparisonMask::MASK_W);
	return ret;
}

HK_FORCE_INLINE void hkVector4f::setSelect( hkVector4fComparisonParameter comp, hkVector4fParameter trueValue, hkVector4fParameter falseValue )
{
	m_quad.v[0] = comp.anyIsSet<hkVector4ComparisonMask::MASK_X>() ? trueValue.m_quad.v[0] : falseValue.m_quad.v[0];
	m_quad.v[1] = comp.anyIsSet<hkVector4ComparisonMask::MASK_Y>() ? trueValue.m_quad.v[1] : falseValue.m_quad.v[1];
	m_quad.v[2] = comp.anyIsSet<hkVector4ComparisonMask::MASK_Z>() ? trueValue.m_quad.v[2] : falseValue.m_quad.v[2];
	m_quad.v[3] = comp.anyIsSet<hkVector4ComparisonMask::MASK_W>() ? trueValue.m_quad.v[3] : falseValue.m_quad.v[3];
}

template<hkVector4ComparisonMask::Mask M>
HK_FORCE_INLINE void hkVector4f::setSelect( hkVector4fParameter trueValue, hkVector4fParameter falseValue )
{
	m_quad.v[0] = (M & hkVector4ComparisonMask::MASK_X) ? trueValue.m_quad.v[0] : falseValue.m_quad.v[0];
	m_quad.v[1] = (M & hkVector4ComparisonMask::MASK_Y) ? trueValue.m_quad.v[1] : falseValue.m_quad.v[1];
	m_quad.v[2] = (M & hkVector4ComparisonMask::MASK_Z) ? trueValue.m_quad.v[2] : falseValue.m_quad.v[2];
	m_quad.v[3] = (M & hkVector4ComparisonMask::MASK_W) ? trueValue.m_quad.v[3] : falseValue.m_quad.v[3];
}


HK_FORCE_INLINE void hkVector4f::zeroIfFalse( hkVector4fComparisonParameter comp )
{
	m_quad.v[0] = comp.anyIsSet<hkVector4ComparisonMask::MASK_X>() ? m_quad.v[0] : hkFloat32(0);
	m_quad.v[1] = comp.anyIsSet<hkVector4ComparisonMask::MASK_Y>() ? m_quad.v[1] : hkFloat32(0);
	m_quad.v[2] = comp.anyIsSet<hkVector4ComparisonMask::MASK_Z>() ? m_quad.v[2] : hkFloat32(0);
	m_quad.v[3] = comp.anyIsSet<hkVector4ComparisonMask::MASK_W>() ? m_quad.v[3] : hkFloat32(0);
}

HK_FORCE_INLINE void hkVector4f::zeroIfTrue( hkVector4fComparisonParameter comp )
{
	m_quad.v[0] = comp.anyIsSet<hkVector4ComparisonMask::MASK_X>() ? hkFloat32(0) : m_quad.v[0];
	m_quad.v[1] = comp.anyIsSet<hkVector4ComparisonMask::MASK_Y>() ? hkFloat32(0) : m_quad.v[1];
	m_quad.v[2] = comp.anyIsSet<hkVector4ComparisonMask::MASK_Z>() ? hkFloat32(0) : m_quad.v[2];
	m_quad.v[3] = comp.anyIsSet<hkVector4ComparisonMask::MASK_W>() ? hkFloat32(0) : m_quad.v[3];
}


template <int N>
HK_FORCE_INLINE void hkVector4f::setNeg(hkVector4fParameter v)
{
	HK_VECTOR4f_UNSUPPORTED_LENGTH_CHECK;
	m_quad.v[0] = (N>0) ? -v.m_quad.v[0] : v.m_quad.v[0];
	m_quad.v[1] = (N>1) ? -v.m_quad.v[1] : v.m_quad.v[1];
	m_quad.v[2] = (N>2) ? -v.m_quad.v[2] : v.m_quad.v[2];
	m_quad.v[3] = (N>3) ? -v.m_quad.v[3] : v.m_quad.v[3];
}

HK_FORCE_INLINE void hkVector4f::setAbs(hkVector4fParameter v)
{
	m_quad.v[0] = hkMath::fabs(v.m_quad.v[0]);
	m_quad.v[1] = hkMath::fabs(v.m_quad.v[1]);
	m_quad.v[2] = hkMath::fabs(v.m_quad.v[2]);
	m_quad.v[3] = hkMath::fabs(v.m_quad.v[3]);
}

HK_FORCE_INLINE void hkVector4f::setMin(hkVector4fParameter a, hkVector4fParameter b)
{
	m_quad.v[0] = hkMath::min2(a.m_quad.v[0], b.m_quad.v[0]);
	m_quad.v[1] = hkMath::min2(a.m_quad.v[1], b.m_quad.v[1]);
	m_quad.v[2] = hkMath::min2(a.m_quad.v[2], b.m_quad.v[2]);
	m_quad.v[3] = hkMath::min2(a.m_quad.v[3], b.m_quad.v[3]);
}

HK_FORCE_INLINE void hkVector4f::setMax(hkVector4fParameter a, hkVector4fParameter b)
{
	m_quad.v[0] = hkMath::max2(a.m_quad.v[0], b.m_quad.v[0]);
	m_quad.v[1] = hkMath::max2(a.m_quad.v[1], b.m_quad.v[1]);
	m_quad.v[2] = hkMath::max2(a.m_quad.v[2], b.m_quad.v[2]);
	m_quad.v[3] = hkMath::max2(a.m_quad.v[3], b.m_quad.v[3]);
}

HK_FORCE_INLINE void hkVector4f::_setRotatedDir(const hkMatrix3f& r, hkVector4fParameter v )
{
	const hkSimdFloat32 v0 = v.getComponent<0>();
	const hkSimdFloat32 v1 = v.getComponent<1>();
	const hkSimdFloat32 v2 = v.getComponent<2>();
	setMul(r.getColumn<0>(),v0);
	addMul(r.getColumn<1>(),v1);
	addMul(r.getColumn<2>(),v2);
}

template <int N>
HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::dot(hkVector4fParameter a) const
{
	HK_VECTOR4f_UNSUPPORTED_LENGTH_CHECK;
	hkFloat32	sum  = m_quad.v[0] * a.m_quad.v[0];
	if (N>1)sum += m_quad.v[1] * a.m_quad.v[1];
	if (N>2)sum += m_quad.v[2] * a.m_quad.v[2];
	if (N>3)sum += m_quad.v[3] * a.m_quad.v[3];
	return hkSimdFloat32::convert(sum);
}

HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::dot4xyz1(hkVector4fParameter a) const
{
	return	hkSimdFloat32::convert(	
		(m_quad.v[0] * a.m_quad.v[0]) + 
		(m_quad.v[1] * a.m_quad.v[1]) + 
		(m_quad.v[2] * a.m_quad.v[2]) + 
		 m_quad.v[3]                      );
}

HK_FORCE_INLINE void hkVector4f::_setRotatedInverseDir(const hkMatrix3f& r, hkVector4fParameter v )
{
	const hkSimdFloat32 d0 = r.getColumn<0>().dot<3>(v);
	const hkSimdFloat32 d1 = r.getColumn<1>().dot<3>(v);
	const hkSimdFloat32 d2 = r.getColumn<2>().dot<3>(v);

	set(d0,d1,d2,d2);
}

template <int N>
HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::horizontalAdd() const
{
	HK_VECTOR4f_UNSUPPORTED_LENGTH_CHECK;
	hkFloat32	sum  = m_quad.v[0];
	if (N>1)sum += m_quad.v[1];
	if (N>2)sum += m_quad.v[2];
	if (N>3)sum += m_quad.v[3];
	return hkSimdFloat32::convert(sum);
}

template <int N>
HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::horizontalMul() const
{
	HK_VECTOR4f_UNSUPPORTED_LENGTH_CHECK;
	hkFloat32   product  = m_quad.v[0];
	if (N>1) product *= m_quad.v[1];
	if (N>2) product *= m_quad.v[2];
	if (N>3) product *= m_quad.v[3];
	return hkSimdFloat32::convert(product);
}

template <>
HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::horizontalMax<1>() const
{
	return getComponent<0>();
}

template <>
HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::horizontalMax<2>() const
{
	return hkSimdFloat32::convert(hkMath::max2(m_quad.v[0], m_quad.v[1]));
}

template <>
HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::horizontalMax<3>() const
{
	const hkFloat32 m = hkMath::max2(m_quad.v[0], m_quad.v[1]);
	return hkSimdFloat32::convert(hkMath::max2(m, m_quad.v[2]));
}

template <>
HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::horizontalMax<4>() const
{
	const hkFloat32 ma = hkMath::max2(m_quad.v[0], m_quad.v[1]);
	const hkFloat32 mb = hkMath::max2(m_quad.v[2], m_quad.v[3]);
	return hkSimdFloat32::convert(hkMath::max2(ma, mb));
}

template <int N>
HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::horizontalMax() const
{
	HK_VECTOR4f_NOT_IMPLEMENTED;
	return hkSimdFloat32::getConstant<HK_QUADREAL_0>();
}

template <>
HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::horizontalMin<1>() const
{
	return getComponent<0>();
}

template <>
HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::horizontalMin<2>() const
{
	return hkSimdFloat32::convert(hkMath::min2(m_quad.v[0], m_quad.v[1]));
}

template <>
HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::horizontalMin<3>() const
{
	const hkFloat32 m = hkMath::min2(m_quad.v[0], m_quad.v[1]);
	return hkSimdFloat32::convert(hkMath::min2(m, m_quad.v[2]));
}

template <>
HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::horizontalMin<4>() const
{
	const hkFloat32 ma = hkMath::min2(m_quad.v[0], m_quad.v[1]);
	const hkFloat32 mb = hkMath::min2(m_quad.v[2], m_quad.v[3]);
	return hkSimdFloat32::convert(hkMath::min2(ma, mb));
}

template <int N>
HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::horizontalMin() const
{
	HK_VECTOR4f_NOT_IMPLEMENTED;
	return hkSimdFloat32::getConstant<HK_QUADREAL_0>();
}

/* operator () */

HK_FORCE_INLINE hkFloat32& hkVector4f::operator() (int a)
{
	HK_MATH_ASSERT(0x6d0c31d7, a>=0 && a<4, "index out of bounds for component access");
	return m_quad.v[a];
}

HK_FORCE_INLINE const hkFloat32& hkVector4f::operator() (int a) const
{
	HK_MATH_ASSERT(0x6d0c31d7, a>=0 && a<4, "index out of bounds for component access");
	return const_cast<const hkFloat32&>(m_quad.v[a]);
}

HK_FORCE_INLINE void hkVector4f::setXYZ_W(hkVector4fParameter xyz, hkVector4fParameter ww)
{
	m_quad.v[0] = xyz.m_quad.v[0];
	m_quad.v[1] = xyz.m_quad.v[1];
	m_quad.v[2] = xyz.m_quad.v[2];
	m_quad.v[3] =  ww.m_quad.v[3];
}

HK_FORCE_INLINE void hkVector4f::setXYZ_W(hkVector4fParameter xyz, hkSimdFloat32Parameter ww)
{
	m_quad.v[0] = xyz.m_quad.v[0];
	m_quad.v[1] = xyz.m_quad.v[1];
	m_quad.v[2] = xyz.m_quad.v[2];
	m_quad.v[3] = ww.getReal();
}

HK_FORCE_INLINE void hkVector4f::setW(hkVector4fParameter w)
{
	m_quad.v[3] = w.m_quad.v[3];
}

HK_FORCE_INLINE void hkVector4f::setXYZ(hkVector4fParameter xyz)
{
	m_quad.v[0] = xyz.m_quad.v[0];
	m_quad.v[1] = xyz.m_quad.v[1];
	m_quad.v[2] = xyz.m_quad.v[2];
}

HK_FORCE_INLINE void hkVector4f::addXYZ(hkVector4fParameter xyz)
{
	m_quad.v[0] += xyz.m_quad.v[0];
	m_quad.v[1] += xyz.m_quad.v[1];
	m_quad.v[2] += xyz.m_quad.v[2];
#if defined(HK_REAL_IS_DOUBLE)
	HK_ON_DEBUG( *((hkUint64*)&(m_quad.v[3])) = 0xffffffffffffffffull; )
#else
	HK_ON_DEBUG( *((hkUint32*)&(m_quad.v[3])) = 0xffffffff; )
#endif
}

HK_FORCE_INLINE void hkVector4f::subXYZ(hkVector4fParameter xyz)
{
	m_quad.v[0] -= xyz.m_quad.v[0];
	m_quad.v[1] -= xyz.m_quad.v[1];
	m_quad.v[2] -= xyz.m_quad.v[2];
#if defined(HK_REAL_IS_DOUBLE)
	HK_ON_DEBUG( *((hkUint64*)&(m_quad.v[3])) = 0xffffffffffffffffull; )
#else
	HK_ON_DEBUG( *((hkUint32*)&(m_quad.v[3])) = 0xffffffff; )
#endif
}

HK_FORCE_INLINE void hkVector4f::setXYZ(hkFloat32 v)
{
	m_quad.v[0] = v;
	m_quad.v[1] = v;
	m_quad.v[2] = v;
}

HK_FORCE_INLINE void hkVector4f::setXYZ(hkSimdFloat32Parameter vv)
{
	setXYZ( vv.getReal() );
}

HK_FORCE_INLINE void hkVector4f::setXYZ_0(hkVector4fParameter xyz)
{
	setXYZ( xyz );
	m_quad.v[3] = hkFloat32(0);
}

HK_FORCE_INLINE void hkVector4f::setBroadcastXYZ(const int i, hkVector4fParameter v)
{
	HK_MATH_ASSERT(0x6d0c31d7, i>=0 && i<4, "index out of bounds for component access");
	setXYZ( v.m_quad.v[i] );
#if defined(HK_REAL_IS_DOUBLE)
	HK_ON_DEBUG( *((hkUint64*)&(m_quad.v[3])) = 0xffffffffffffffffull; )
#else
	HK_ON_DEBUG( *((hkUint32*)&(m_quad.v[3])) = 0xffffffff; )
#endif
}

HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::getComponent(const int i) const
{
	HK_MATH_ASSERT(0x6d0c31d7, i>=0 && i<4, "index out of bounds for component access");
	return hkSimdFloat32::convert(m_quad.v[i]);
}

template <int I>
HK_FORCE_INLINE const hkSimdFloat32 hkVector4f::getComponent() const
{
	HK_VECTOR4f_SUBINDEX_CHECK;
	return hkSimdFloat32::convert(m_quad.v[I]);
}

HK_FORCE_INLINE void hkVector4f::setComponent(const int i, hkSimdFloat32Parameter val)
{
	HK_MATH_ASSERT(0x6d0c31d7, i>=0 && i<4, "index out of bounds for component access");
	m_quad.v[i] = val.getReal();
}

template <int I>
HK_FORCE_INLINE void hkVector4f::setComponent(hkSimdFloat32Parameter val)
{
	HK_VECTOR4f_SUBINDEX_CHECK;
	m_quad.v[I] = val.getReal();
}

HK_FORCE_INLINE void hkVector4f::reduceToHalfPrecision()
{
#if defined(HK_HALF_IS_FLOAT)
	#if defined(HK_REAL_IS_DOUBLE)
		static const hkUint64 precisionMask = 0xffffffff00000000ull;
		const hkUint64* src = reinterpret_cast<const hkUint64*>( &m_quad );
		hkUint64* dest = reinterpret_cast<hkUint64*>( &m_quad );
		dest[0] = src[0] & precisionMask;
		dest[1] = src[1] & precisionMask;
		dest[2] = src[2] & precisionMask;
		dest[3] = src[3] & precisionMask;
	#endif
#else
		static const hkUint32 precisionMask = 0xffff0000;
	#if defined(HK_REAL_IS_DOUBLE)
		hkFloat32 fsrc[4];
		fsrc[0] = hkFloat32(m_quad.v[0]);
		fsrc[1] = hkFloat32(m_quad.v[1]);
		fsrc[2] = hkFloat32(m_quad.v[2]);
		fsrc[3] = hkFloat32(m_quad.v[3]);
		const hkUint32* src = reinterpret_cast<const hkUint32*>( fsrc );
		hkUint32* dest = reinterpret_cast<hkUint32*>( fsrc );
		dest[0] = src[0] & precisionMask;
		dest[1] = src[1] & precisionMask;
		dest[2] = src[2] & precisionMask;
		dest[3] = src[3] & precisionMask;
		m_quad.v[0] = hkFloat32(fsrc[0]);
		m_quad.v[1] = hkFloat32(fsrc[1]);
		m_quad.v[2] = hkFloat32(fsrc[2]);
		m_quad.v[3] = hkFloat32(fsrc[3]);
	#else
		const hkUint32* src = reinterpret_cast<const hkUint32*>( &m_quad );
		hkUint32* dest = reinterpret_cast<hkUint32*>( &m_quad );
		dest[0] = src[0] & precisionMask;
		dest[1] = src[1] & precisionMask;
		dest[2] = src[2] & precisionMask;
		dest[3] = src[3] & precisionMask;
	#endif
#endif
}

template <int N> 
HK_FORCE_INLINE hkBool32 hkVector4f::isOk() const
{
	HK_VECTOR4f_UNSUPPORTED_LENGTH_CHECK;
	if (        !hkMath::isFinite(m_quad.v[0]) ) return false;
	if ((N>1)&&(!hkMath::isFinite(m_quad.v[1]))) return false;
	if ((N>2)&&(!hkMath::isFinite(m_quad.v[2]))) return false;
	if ((N>3)&&(!hkMath::isFinite(m_quad.v[3]))) return false;
	return true;
}

template <> 
HK_FORCE_INLINE void hkVector4f::setPermutation<hkVectorPermutation::XYZW>(hkVector4fParameter v)
{
	m_quad = v.m_quad;
}

template <hkVectorPermutation::Permutation P> 
HK_FORCE_INLINE void hkVector4f::setPermutation(hkVector4fParameter v)
{
    // Store in regs before writing to the destination - to handle case when v and this are the same
    const hkFloat32 t0 = v.m_quad.v[(P & 0x3000) >> 12];
    const hkFloat32 t1 = v.m_quad.v[(P & 0x0300) >>  8];
    const hkFloat32 t2 = v.m_quad.v[(P & 0x0030) >>  4];
    const hkFloat32 t3 = v.m_quad.v[(P & 0x0003) >>  0];

    m_quad.v[0] = t0;
    m_quad.v[1] = t1;
    m_quad.v[2] = t2;
    m_quad.v[3] = t3;
}

HK_FORCE_INLINE const hkVector4fComparison hkVector4f::signBitSet() const
{
	hkVector4fComparison mask;
	mask.m_mask  = hkVector4ComparisonMask::MASK_NONE;
	mask.m_mask |= hkMath::signBitSet(m_quad.v[0]) ? hkVector4ComparisonMask::MASK_X : hkVector4ComparisonMask::MASK_NONE;
	mask.m_mask |= hkMath::signBitSet(m_quad.v[1]) ? hkVector4ComparisonMask::MASK_Y : hkVector4ComparisonMask::MASK_NONE;
	mask.m_mask |= hkMath::signBitSet(m_quad.v[2]) ? hkVector4ComparisonMask::MASK_Z : hkVector4ComparisonMask::MASK_NONE;
	mask.m_mask |= hkMath::signBitSet(m_quad.v[3]) ? hkVector4ComparisonMask::MASK_W : hkVector4ComparisonMask::MASK_NONE;
	return mask;
}

HK_FORCE_INLINE const hkVector4fComparison hkVector4f::signBitClear() const
{
	hkVector4fComparison mask;
	mask.m_mask  = hkVector4ComparisonMask::MASK_NONE;
	mask.m_mask |= hkMath::signBitSet(m_quad.v[0]) ? hkVector4ComparisonMask::MASK_NONE : hkVector4ComparisonMask::MASK_X;
	mask.m_mask |= hkMath::signBitSet(m_quad.v[1]) ? hkVector4ComparisonMask::MASK_NONE : hkVector4ComparisonMask::MASK_Y;
	mask.m_mask |= hkMath::signBitSet(m_quad.v[2]) ? hkVector4ComparisonMask::MASK_NONE : hkVector4ComparisonMask::MASK_Z;
	mask.m_mask |= hkMath::signBitSet(m_quad.v[3]) ? hkVector4ComparisonMask::MASK_NONE : hkVector4ComparisonMask::MASK_W;
	return mask;
}

HK_FORCE_INLINE void hkVector4f::setFlipSign(hkVector4fParameter v, hkVector4fComparisonParameter mask)
{
	m_quad.v[0] = mask.anyIsSet<hkVector4ComparisonMask::MASK_X>() ? -v.m_quad.v[0] : v.m_quad.v[0];
	m_quad.v[1] = mask.anyIsSet<hkVector4ComparisonMask::MASK_Y>() ? -v.m_quad.v[1] : v.m_quad.v[1];
	m_quad.v[2] = mask.anyIsSet<hkVector4ComparisonMask::MASK_Z>() ? -v.m_quad.v[2] : v.m_quad.v[2];
	m_quad.v[3] = mask.anyIsSet<hkVector4ComparisonMask::MASK_W>() ? -v.m_quad.v[3] : v.m_quad.v[3];
}

HK_FORCE_INLINE void hkVector4f::setFlipSign(hkVector4fParameter a, hkVector4fParameter signs)
{
	m_quad.v[0] = hkMath::signBitSet(signs.m_quad.v[0]) ? -a.m_quad.v[0] : a.m_quad.v[0];
	m_quad.v[1] = hkMath::signBitSet(signs.m_quad.v[1]) ? -a.m_quad.v[1] : a.m_quad.v[1];
	m_quad.v[2] = hkMath::signBitSet(signs.m_quad.v[2]) ? -a.m_quad.v[2] : a.m_quad.v[2];
	m_quad.v[3] = hkMath::signBitSet(signs.m_quad.v[3]) ? -a.m_quad.v[3] : a.m_quad.v[3];
}

HK_FORCE_INLINE void hkVector4f::setFlipSign(hkVector4fParameter a, hkSimdFloat32Parameter sharedSign)
{
	const bool flip = hkMath::signBitSet(sharedSign.getReal());
	if (flip)
	{
		m_quad.v[0] = -a.m_quad.v[0];
		m_quad.v[1] = -a.m_quad.v[1];
		m_quad.v[2] = -a.m_quad.v[2];
		m_quad.v[3] = -a.m_quad.v[3];
	}
	else
	{
		m_quad.v[0] = a.m_quad.v[0];
		m_quad.v[1] = a.m_quad.v[1];
		m_quad.v[2] = a.m_quad.v[2];
		m_quad.v[3] = a.m_quad.v[3];
	}
}



//
// advanced interface
//

namespace hkVector4_AdvancedInterface
{

template <hkMathAccuracyMode A, hkMathDivByZeroMode D>
struct unrollf_setReciprocal { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, hkVector4fParameter a)
{
	HK_VECTOR4f_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <hkMathAccuracyMode A>
struct unrollf_setReciprocal<A, HK_DIV_IGNORE> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, hkVector4fParameter a)
{
	switch (A)
	{
		case HK_ACC_23_BIT: 
			{
				self.v[0] = hkFloat32(hkMath::rcpF32Approx23Bit(hkFloat32(a.m_quad.v[0])));
				self.v[1] = hkFloat32(hkMath::rcpF32Approx23Bit(hkFloat32(a.m_quad.v[1])));
				self.v[2] = hkFloat32(hkMath::rcpF32Approx23Bit(hkFloat32(a.m_quad.v[2])));
				self.v[3] = hkFloat32(hkMath::rcpF32Approx23Bit(hkFloat32(a.m_quad.v[3])));
			}
			break;
		case HK_ACC_12_BIT: 
			{
				self.v[0] = hkFloat32(hkMath::rcpF32Approx12Bit(hkFloat32(a.m_quad.v[0])));
				self.v[1] = hkFloat32(hkMath::rcpF32Approx12Bit(hkFloat32(a.m_quad.v[1])));
				self.v[2] = hkFloat32(hkMath::rcpF32Approx12Bit(hkFloat32(a.m_quad.v[2])));
				self.v[3] = hkFloat32(hkMath::rcpF32Approx12Bit(hkFloat32(a.m_quad.v[3])));
			}
			break;
		default:         
			{
				self.v[0] = hkFloat32(1) / a.m_quad.v[0];
				self.v[1] = hkFloat32(1) / a.m_quad.v[1];
				self.v[2] = hkFloat32(1) / a.m_quad.v[2];
				self.v[3] = hkFloat32(1) / a.m_quad.v[3];
			}
			break; // HK_ACC_FULL
	}
} };
template <hkMathAccuracyMode A>
struct unrollf_setReciprocal<A, HK_DIV_SET_ZERO> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, hkVector4fParameter a)
{
	switch (A)
	{
		case HK_ACC_23_BIT: 
			{
				self.v[0] = ((a.m_quad.v[0] == hkFloat32(0)) ? hkFloat32(0) : hkFloat32(hkMath::rcpF32Approx23Bit(hkFloat32(a.m_quad.v[0]))));
				self.v[1] = ((a.m_quad.v[1] == hkFloat32(0)) ? hkFloat32(0) : hkFloat32(hkMath::rcpF32Approx23Bit(hkFloat32(a.m_quad.v[1]))));
				self.v[2] = ((a.m_quad.v[2] == hkFloat32(0)) ? hkFloat32(0) : hkFloat32(hkMath::rcpF32Approx23Bit(hkFloat32(a.m_quad.v[2]))));
				self.v[3] = ((a.m_quad.v[3] == hkFloat32(0)) ? hkFloat32(0) : hkFloat32(hkMath::rcpF32Approx23Bit(hkFloat32(a.m_quad.v[3]))));
			}
			break;
		case HK_ACC_12_BIT: 
			{
				self.v[0] = ((a.m_quad.v[0] == hkFloat32(0)) ? hkFloat32(0) : hkFloat32(hkMath::rcpF32Approx12Bit(hkFloat32(a.m_quad.v[0]))));
				self.v[1] = ((a.m_quad.v[1] == hkFloat32(0)) ? hkFloat32(0) : hkFloat32(hkMath::rcpF32Approx12Bit(hkFloat32(a.m_quad.v[1]))));
				self.v[2] = ((a.m_quad.v[2] == hkFloat32(0)) ? hkFloat32(0) : hkFloat32(hkMath::rcpF32Approx12Bit(hkFloat32(a.m_quad.v[2]))));
				self.v[3] = ((a.m_quad.v[3] == hkFloat32(0)) ? hkFloat32(0) : hkFloat32(hkMath::rcpF32Approx12Bit(hkFloat32(a.m_quad.v[3]))));
			}
			break;
		default:         
			{
				self.v[0] = ((a.m_quad.v[0] == hkFloat32(0)) ? hkFloat32(0) : hkFloat32(1) / a.m_quad.v[0]);
				self.v[1] = ((a.m_quad.v[1] == hkFloat32(0)) ? hkFloat32(0) : hkFloat32(1) / a.m_quad.v[1]);
				self.v[2] = ((a.m_quad.v[2] == hkFloat32(0)) ? hkFloat32(0) : hkFloat32(1) / a.m_quad.v[2]);
				self.v[3] = ((a.m_quad.v[3] == hkFloat32(0)) ? hkFloat32(0) : hkFloat32(1) / a.m_quad.v[3]);
			}
			break; // HK_ACC_FULL
	}
} };
template <hkMathAccuracyMode A>
struct unrollf_setReciprocal<A, HK_DIV_SET_HIGH> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, hkVector4fParameter a)
{
	hkFloat32 high0 = hkMath::signBitSet(a.m_quad.v[0]) ? -HK_FLOAT_HIGH : HK_FLOAT_HIGH;
	hkFloat32 high1 = hkMath::signBitSet(a.m_quad.v[1]) ? -HK_FLOAT_HIGH : HK_FLOAT_HIGH;
	hkFloat32 high2 = hkMath::signBitSet(a.m_quad.v[2]) ? -HK_FLOAT_HIGH : HK_FLOAT_HIGH;
	hkFloat32 high3 = hkMath::signBitSet(a.m_quad.v[3]) ? -HK_FLOAT_HIGH : HK_FLOAT_HIGH;
	switch (A)
	{
	case HK_ACC_23_BIT: 
		{
			self.v[0] = ((a.m_quad.v[0] == hkFloat32(0)) ? high0 : hkFloat32(hkMath::rcpF32Approx23Bit(hkFloat32(a.m_quad.v[0]))));
			self.v[1] = ((a.m_quad.v[1] == hkFloat32(0)) ? high1 : hkFloat32(hkMath::rcpF32Approx23Bit(hkFloat32(a.m_quad.v[1]))));
			self.v[2] = ((a.m_quad.v[2] == hkFloat32(0)) ? high2 : hkFloat32(hkMath::rcpF32Approx23Bit(hkFloat32(a.m_quad.v[2]))));
			self.v[3] = ((a.m_quad.v[3] == hkFloat32(0)) ? high3 : hkFloat32(hkMath::rcpF32Approx23Bit(hkFloat32(a.m_quad.v[3]))));
		}
		break;
	case HK_ACC_12_BIT: 
		{
			self.v[0] = ((a.m_quad.v[0] == hkFloat32(0)) ? high0 : hkFloat32(hkMath::rcpF32Approx12Bit(hkFloat32(a.m_quad.v[0]))));
			self.v[1] = ((a.m_quad.v[1] == hkFloat32(0)) ? high1 : hkFloat32(hkMath::rcpF32Approx12Bit(hkFloat32(a.m_quad.v[1]))));
			self.v[2] = ((a.m_quad.v[2] == hkFloat32(0)) ? high2 : hkFloat32(hkMath::rcpF32Approx12Bit(hkFloat32(a.m_quad.v[2]))));
			self.v[3] = ((a.m_quad.v[3] == hkFloat32(0)) ? high3 : hkFloat32(hkMath::rcpF32Approx12Bit(hkFloat32(a.m_quad.v[3]))));
		}
		break;
	default:         
		{
			self.v[0] = ((a.m_quad.v[0] == hkFloat32(0)) ? high0 : hkFloat32(1) / a.m_quad.v[0]);
			self.v[1] = ((a.m_quad.v[1] == hkFloat32(0)) ? high1 : hkFloat32(1) / a.m_quad.v[1]);
			self.v[2] = ((a.m_quad.v[2] == hkFloat32(0)) ? high2 : hkFloat32(1) / a.m_quad.v[2]);
			self.v[3] = ((a.m_quad.v[3] == hkFloat32(0)) ? high3 : hkFloat32(1) / a.m_quad.v[3]);
		}
		break; // HK_ACC_FULL
	}
} };
template <hkMathAccuracyMode A>
struct unrollf_setReciprocal<A, HK_DIV_SET_MAX> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, hkVector4fParameter a)
{
	hkFloat32 max0 = hkMath::signBitSet(a.m_quad.v[0]) ? -HK_FLOAT_MAX : HK_FLOAT_MAX;
	hkFloat32 max1 = hkMath::signBitSet(a.m_quad.v[1]) ? -HK_FLOAT_MAX : HK_FLOAT_MAX;
	hkFloat32 max2 = hkMath::signBitSet(a.m_quad.v[2]) ? -HK_FLOAT_MAX : HK_FLOAT_MAX;
	hkFloat32 max3 = hkMath::signBitSet(a.m_quad.v[3]) ? -HK_FLOAT_MAX : HK_FLOAT_MAX;
	switch (A)
	{
	case HK_ACC_23_BIT: 
		{
			self.v[0] = ((a.m_quad.v[0] == hkFloat32(0)) ? max0 : hkFloat32(hkMath::rcpF32Approx23Bit(hkFloat32(a.m_quad.v[0]))));
			self.v[1] = ((a.m_quad.v[1] == hkFloat32(0)) ? max1 : hkFloat32(hkMath::rcpF32Approx23Bit(hkFloat32(a.m_quad.v[1]))));
			self.v[2] = ((a.m_quad.v[2] == hkFloat32(0)) ? max2 : hkFloat32(hkMath::rcpF32Approx23Bit(hkFloat32(a.m_quad.v[2]))));
			self.v[3] = ((a.m_quad.v[3] == hkFloat32(0)) ? max3 : hkFloat32(hkMath::rcpF32Approx23Bit(hkFloat32(a.m_quad.v[3]))));
		}
		break;
	case HK_ACC_12_BIT: 
		{
			self.v[0] = ((a.m_quad.v[0] == hkFloat32(0)) ? max0 : hkFloat32(hkMath::rcpF32Approx12Bit(hkFloat32(a.m_quad.v[0]))));
			self.v[1] = ((a.m_quad.v[1] == hkFloat32(0)) ? max1 : hkFloat32(hkMath::rcpF32Approx12Bit(hkFloat32(a.m_quad.v[1]))));
			self.v[2] = ((a.m_quad.v[2] == hkFloat32(0)) ? max2 : hkFloat32(hkMath::rcpF32Approx12Bit(hkFloat32(a.m_quad.v[2]))));
			self.v[3] = ((a.m_quad.v[3] == hkFloat32(0)) ? max3 : hkFloat32(hkMath::rcpF32Approx12Bit(hkFloat32(a.m_quad.v[3]))));
		}
		break;
	default:         
		{
			self.v[0] = ((a.m_quad.v[0] == hkFloat32(0)) ? max0 : hkFloat32(1) / a.m_quad.v[0]);
			self.v[1] = ((a.m_quad.v[1] == hkFloat32(0)) ? max1 : hkFloat32(1) / a.m_quad.v[1]);
			self.v[2] = ((a.m_quad.v[2] == hkFloat32(0)) ? max2 : hkFloat32(1) / a.m_quad.v[2]);
			self.v[3] = ((a.m_quad.v[3] == hkFloat32(0)) ? max3 : hkFloat32(1) / a.m_quad.v[3]);
		}
		break; // HK_ACC_FULL
	}
} };
template <hkMathAccuracyMode A>
struct unrollf_setReciprocal<A, HK_DIV_SET_ZERO_AND_ONE> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, hkVector4fParameter a)
{
	hkQuadFloat32 val; unrollf_setReciprocal<A, HK_DIV_SET_ZERO>::apply(val,a);

	hkQuadFloat32 absValLessOne;
	absValLessOne.v[0] = hkMath::fabs(val.v[0] - hkFloat32(1));
	absValLessOne.v[1] = hkMath::fabs(val.v[1] - hkFloat32(1));
	absValLessOne.v[2] = hkMath::fabs(val.v[2] - hkFloat32(1));
	absValLessOne.v[3] = hkMath::fabs(val.v[3] - hkFloat32(1));

	self.v[0] = ((absValLessOne.v[0] <= HK_FLOAT_EPSILON) ? hkFloat32(1) : val.v[0]);
	self.v[1] = ((absValLessOne.v[1] <= HK_FLOAT_EPSILON) ? hkFloat32(1) : val.v[1]);
	self.v[2] = ((absValLessOne.v[2] <= HK_FLOAT_EPSILON) ? hkFloat32(1) : val.v[2]);
	self.v[3] = ((absValLessOne.v[3] <= HK_FLOAT_EPSILON) ? hkFloat32(1) : val.v[3]);
} };

} // namespace 

template <hkMathAccuracyMode A, hkMathDivByZeroMode D>
HK_FORCE_INLINE void hkVector4f::setReciprocal(hkVector4fParameter v)
{
	hkVector4_AdvancedInterface::unrollf_setReciprocal<A,D>::apply(m_quad,v);
}

HK_FORCE_INLINE void hkVector4f::setReciprocal(hkVector4fParameter v)
{
	hkVector4_AdvancedInterface::unrollf_setReciprocal<HK_ACC_23_BIT,HK_DIV_IGNORE>::apply(m_quad,v);
}


namespace hkVector4_AdvancedInterface
{

template <hkMathAccuracyMode A, hkMathDivByZeroMode D>
struct unrollf_setDiv { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, hkVector4fParameter a, hkVector4fParameter b)
{
	HK_VECTOR4f_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <hkMathAccuracyMode A>
struct unrollf_setDiv<A, HK_DIV_IGNORE> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, hkVector4fParameter a, hkVector4fParameter b)
{
	switch (A)
	{
	case HK_ACC_23_BIT: 
		{
			self.v[0] = a.m_quad.v[0] * hkFloat32(hkMath::rcpF32Approx23Bit(hkFloat32(b.m_quad.v[0])));
			self.v[1] = a.m_quad.v[1] * hkFloat32(hkMath::rcpF32Approx23Bit(hkFloat32(b.m_quad.v[1])));
			self.v[2] = a.m_quad.v[2] * hkFloat32(hkMath::rcpF32Approx23Bit(hkFloat32(b.m_quad.v[2])));
			self.v[3] = a.m_quad.v[3] * hkFloat32(hkMath::rcpF32Approx23Bit(hkFloat32(b.m_quad.v[3])));
		}
		break;
	case HK_ACC_12_BIT: 
		{
			self.v[0] = a.m_quad.v[0] * hkFloat32(hkMath::rcpF32Approx12Bit(hkFloat32(b.m_quad.v[0])));
			self.v[1] = a.m_quad.v[1] * hkFloat32(hkMath::rcpF32Approx12Bit(hkFloat32(b.m_quad.v[1])));
			self.v[2] = a.m_quad.v[2] * hkFloat32(hkMath::rcpF32Approx12Bit(hkFloat32(b.m_quad.v[2])));
			self.v[3] = a.m_quad.v[3] * hkFloat32(hkMath::rcpF32Approx12Bit(hkFloat32(b.m_quad.v[3])));
		}
		break;
	default:         
		{
			self.v[0] = a.m_quad.v[0] / b.m_quad.v[0];
			self.v[1] = a.m_quad.v[1] / b.m_quad.v[1];
			self.v[2] = a.m_quad.v[2] / b.m_quad.v[2];
			self.v[3] = a.m_quad.v[3] / b.m_quad.v[3];
		}
		break; // HK_ACC_FULL
	}
} };
template <hkMathAccuracyMode A>
struct unrollf_setDiv<A, HK_DIV_SET_ZERO> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, hkVector4fParameter a, hkVector4fParameter b)
{
	switch (A)
	{
	case HK_ACC_23_BIT: 
		{
			self.v[0] = ((b.m_quad.v[0] == hkFloat32(0)) ? hkFloat32(0) : (a.m_quad.v[0] * hkFloat32(hkMath::rcpF32Approx23Bit(hkFloat32(b.m_quad.v[0])))));
			self.v[1] = ((b.m_quad.v[1] == hkFloat32(0)) ? hkFloat32(0) : (a.m_quad.v[1] * hkFloat32(hkMath::rcpF32Approx23Bit(hkFloat32(b.m_quad.v[1])))));
			self.v[2] = ((b.m_quad.v[2] == hkFloat32(0)) ? hkFloat32(0) : (a.m_quad.v[2] * hkFloat32(hkMath::rcpF32Approx23Bit(hkFloat32(b.m_quad.v[2])))));
			self.v[3] = ((b.m_quad.v[3] == hkFloat32(0)) ? hkFloat32(0) : (a.m_quad.v[3] * hkFloat32(hkMath::rcpF32Approx23Bit(hkFloat32(b.m_quad.v[3])))));
		}
		break;
	case HK_ACC_12_BIT: 
		{
			self.v[0] = ((b.m_quad.v[0] == hkFloat32(0)) ? hkFloat32(0) : (a.m_quad.v[0] * hkFloat32(hkMath::rcpF32Approx12Bit(hkFloat32(b.m_quad.v[0])))));
			self.v[1] = ((b.m_quad.v[1] == hkFloat32(0)) ? hkFloat32(0) : (a.m_quad.v[1] * hkFloat32(hkMath::rcpF32Approx12Bit(hkFloat32(b.m_quad.v[1])))));
			self.v[2] = ((b.m_quad.v[2] == hkFloat32(0)) ? hkFloat32(0) : (a.m_quad.v[2] * hkFloat32(hkMath::rcpF32Approx12Bit(hkFloat32(b.m_quad.v[2])))));
			self.v[3] = ((b.m_quad.v[3] == hkFloat32(0)) ? hkFloat32(0) : (a.m_quad.v[3] * hkFloat32(hkMath::rcpF32Approx12Bit(hkFloat32(b.m_quad.v[3])))));
		}
		break;
	default:         
		{
			self.v[0] = ((b.m_quad.v[0] == hkFloat32(0)) ? hkFloat32(0) : (a.m_quad.v[0] / b.m_quad.v[0]));
			self.v[1] = ((b.m_quad.v[1] == hkFloat32(0)) ? hkFloat32(0) : (a.m_quad.v[1] / b.m_quad.v[1]));
			self.v[2] = ((b.m_quad.v[2] == hkFloat32(0)) ? hkFloat32(0) : (a.m_quad.v[2] / b.m_quad.v[2]));
			self.v[3] = ((b.m_quad.v[3] == hkFloat32(0)) ? hkFloat32(0) : (a.m_quad.v[3] / b.m_quad.v[3]));
		}
		break; // HK_ACC_FULL
	}
} };
template <hkMathAccuracyMode A>
struct unrollf_setDiv<A, HK_DIV_SET_HIGH> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, hkVector4fParameter a, hkVector4fParameter b)
{
	switch (A)
	{
	case HK_ACC_23_BIT: 
		{
			self.v[0] = ((b.m_quad.v[0] == hkFloat32(0)) ? ((a.m_quad.v[0] < hkFloat32(0)) ? -HK_FLOAT_HIGH : HK_FLOAT_HIGH) : (a.m_quad.v[0] * hkFloat32(hkMath::rcpF32Approx23Bit(hkFloat32(b.m_quad.v[0])))));
			self.v[1] = ((b.m_quad.v[1] == hkFloat32(0)) ? ((a.m_quad.v[1] < hkFloat32(0)) ? -HK_FLOAT_HIGH : HK_FLOAT_HIGH) : (a.m_quad.v[1] * hkFloat32(hkMath::rcpF32Approx23Bit(hkFloat32(b.m_quad.v[1])))));
			self.v[2] = ((b.m_quad.v[2] == hkFloat32(0)) ? ((a.m_quad.v[2] < hkFloat32(0)) ? -HK_FLOAT_HIGH : HK_FLOAT_HIGH) : (a.m_quad.v[2] * hkFloat32(hkMath::rcpF32Approx23Bit(hkFloat32(b.m_quad.v[2])))));
			self.v[3] = ((b.m_quad.v[3] == hkFloat32(0)) ? ((a.m_quad.v[3] < hkFloat32(0)) ? -HK_FLOAT_HIGH : HK_FLOAT_HIGH) : (a.m_quad.v[3] * hkFloat32(hkMath::rcpF32Approx23Bit(hkFloat32(b.m_quad.v[3])))));
		}
		break;
	case HK_ACC_12_BIT: 
		{
			self.v[0] = ((b.m_quad.v[0] == hkFloat32(0)) ? ((a.m_quad.v[0] < hkFloat32(0)) ? -HK_FLOAT_HIGH : HK_FLOAT_HIGH) : (a.m_quad.v[0] * hkFloat32(hkMath::rcpF32Approx12Bit(hkFloat32(b.m_quad.v[0])))));
			self.v[1] = ((b.m_quad.v[1] == hkFloat32(0)) ? ((a.m_quad.v[1] < hkFloat32(0)) ? -HK_FLOAT_HIGH : HK_FLOAT_HIGH) : (a.m_quad.v[1] * hkFloat32(hkMath::rcpF32Approx12Bit(hkFloat32(b.m_quad.v[1])))));
			self.v[2] = ((b.m_quad.v[2] == hkFloat32(0)) ? ((a.m_quad.v[2] < hkFloat32(0)) ? -HK_FLOAT_HIGH : HK_FLOAT_HIGH) : (a.m_quad.v[2] * hkFloat32(hkMath::rcpF32Approx12Bit(hkFloat32(b.m_quad.v[2])))));
			self.v[3] = ((b.m_quad.v[3] == hkFloat32(0)) ? ((a.m_quad.v[3] < hkFloat32(0)) ? -HK_FLOAT_HIGH : HK_FLOAT_HIGH) : (a.m_quad.v[3] * hkFloat32(hkMath::rcpF32Approx12Bit(hkFloat32(b.m_quad.v[3])))));
		}
		break;
	default:         
		{
			self.v[0] = ((b.m_quad.v[0] == hkFloat32(0)) ? ((a.m_quad.v[0] < hkFloat32(0)) ? -HK_FLOAT_HIGH : HK_FLOAT_HIGH) : (a.m_quad.v[0] / b.m_quad.v[0]));
			self.v[1] = ((b.m_quad.v[1] == hkFloat32(0)) ? ((a.m_quad.v[1] < hkFloat32(0)) ? -HK_FLOAT_HIGH : HK_FLOAT_HIGH) : (a.m_quad.v[1] / b.m_quad.v[1]));
			self.v[2] = ((b.m_quad.v[2] == hkFloat32(0)) ? ((a.m_quad.v[2] < hkFloat32(0)) ? -HK_FLOAT_HIGH : HK_FLOAT_HIGH) : (a.m_quad.v[2] / b.m_quad.v[2]));
			self.v[3] = ((b.m_quad.v[3] == hkFloat32(0)) ? ((a.m_quad.v[3] < hkFloat32(0)) ? -HK_FLOAT_HIGH : HK_FLOAT_HIGH) : (a.m_quad.v[3] / b.m_quad.v[3]));
		}
		break; // HK_ACC_FULL
	}
} };
template <hkMathAccuracyMode A>
struct unrollf_setDiv<A, HK_DIV_SET_MAX> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, hkVector4fParameter a, hkVector4fParameter b)
{
	switch (A)
	{
	case HK_ACC_23_BIT: 
		{
			self.v[0] = ((b.m_quad.v[0] == hkFloat32(0)) ? ((a.m_quad.v[0] < hkFloat32(0)) ? -HK_FLOAT_MAX : HK_FLOAT_MAX) : (a.m_quad.v[0] * hkFloat32(hkMath::rcpF32Approx23Bit(hkFloat32(b.m_quad.v[0])))));
			self.v[1] = ((b.m_quad.v[1] == hkFloat32(0)) ? ((a.m_quad.v[1] < hkFloat32(0)) ? -HK_FLOAT_MAX : HK_FLOAT_MAX) : (a.m_quad.v[1] * hkFloat32(hkMath::rcpF32Approx23Bit(hkFloat32(b.m_quad.v[1])))));
			self.v[2] = ((b.m_quad.v[2] == hkFloat32(0)) ? ((a.m_quad.v[2] < hkFloat32(0)) ? -HK_FLOAT_MAX : HK_FLOAT_MAX) : (a.m_quad.v[2] * hkFloat32(hkMath::rcpF32Approx23Bit(hkFloat32(b.m_quad.v[2])))));
			self.v[3] = ((b.m_quad.v[3] == hkFloat32(0)) ? ((a.m_quad.v[3] < hkFloat32(0)) ? -HK_FLOAT_MAX : HK_FLOAT_MAX) : (a.m_quad.v[3] * hkFloat32(hkMath::rcpF32Approx23Bit(hkFloat32(b.m_quad.v[3])))));
		}
		break;
	case HK_ACC_12_BIT: 
		{
			self.v[0] = ((b.m_quad.v[0] == hkFloat32(0)) ? ((a.m_quad.v[0] < hkFloat32(0)) ? -HK_FLOAT_MAX : HK_FLOAT_MAX) : (a.m_quad.v[0] * hkFloat32(hkMath::rcpF32Approx12Bit(hkFloat32(b.m_quad.v[0])))));
			self.v[1] = ((b.m_quad.v[1] == hkFloat32(0)) ? ((a.m_quad.v[1] < hkFloat32(0)) ? -HK_FLOAT_MAX : HK_FLOAT_MAX) : (a.m_quad.v[1] * hkFloat32(hkMath::rcpF32Approx12Bit(hkFloat32(b.m_quad.v[1])))));
			self.v[2] = ((b.m_quad.v[2] == hkFloat32(0)) ? ((a.m_quad.v[2] < hkFloat32(0)) ? -HK_FLOAT_MAX : HK_FLOAT_MAX) : (a.m_quad.v[2] * hkFloat32(hkMath::rcpF32Approx12Bit(hkFloat32(b.m_quad.v[2])))));
			self.v[3] = ((b.m_quad.v[3] == hkFloat32(0)) ? ((a.m_quad.v[3] < hkFloat32(0)) ? -HK_FLOAT_MAX : HK_FLOAT_MAX) : (a.m_quad.v[3] * hkFloat32(hkMath::rcpF32Approx12Bit(hkFloat32(b.m_quad.v[3])))));
		}
		break;
	default:         
		{
			self.v[0] = ((b.m_quad.v[0] == hkFloat32(0)) ? ((a.m_quad.v[0] < hkFloat32(0)) ? -HK_FLOAT_MAX : HK_FLOAT_MAX) : (a.m_quad.v[0] / b.m_quad.v[0]));
			self.v[1] = ((b.m_quad.v[1] == hkFloat32(0)) ? ((a.m_quad.v[1] < hkFloat32(0)) ? -HK_FLOAT_MAX : HK_FLOAT_MAX) : (a.m_quad.v[1] / b.m_quad.v[1]));
			self.v[2] = ((b.m_quad.v[2] == hkFloat32(0)) ? ((a.m_quad.v[2] < hkFloat32(0)) ? -HK_FLOAT_MAX : HK_FLOAT_MAX) : (a.m_quad.v[2] / b.m_quad.v[2]));
			self.v[3] = ((b.m_quad.v[3] == hkFloat32(0)) ? ((a.m_quad.v[3] < hkFloat32(0)) ? -HK_FLOAT_MAX : HK_FLOAT_MAX) : (a.m_quad.v[3] / b.m_quad.v[3]));
		}
		break; // HK_ACC_FULL
	}
} };
template <hkMathAccuracyMode A>
struct unrollf_setDiv<A, HK_DIV_SET_ZERO_AND_ONE> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, hkVector4fParameter a, hkVector4fParameter b)
{
	hkQuadFloat32 val; unrollf_setDiv<A, HK_DIV_SET_ZERO>::apply(val,a,b);

	hkQuadFloat32 absValLessOne;
	absValLessOne.v[0] = hkMath::fabs(val.v[0]) - hkFloat32(1);
	absValLessOne.v[1] = hkMath::fabs(val.v[1]) - hkFloat32(1);
	absValLessOne.v[2] = hkMath::fabs(val.v[2]) - hkFloat32(1);
	absValLessOne.v[3] = hkMath::fabs(val.v[3]) - hkFloat32(1);

	self.v[0] = ((absValLessOne.v[0] <= HK_FLOAT_EPSILON) ? hkFloat32(1) : val.v[0]);
	self.v[1] = ((absValLessOne.v[1] <= HK_FLOAT_EPSILON) ? hkFloat32(1) : val.v[1]);
	self.v[2] = ((absValLessOne.v[2] <= HK_FLOAT_EPSILON) ? hkFloat32(1) : val.v[2]);
	self.v[3] = ((absValLessOne.v[3] <= HK_FLOAT_EPSILON) ? hkFloat32(1) : val.v[3]);
} };

} // namespace 

template <hkMathAccuracyMode A, hkMathDivByZeroMode D>
HK_FORCE_INLINE void hkVector4f::setDiv(hkVector4fParameter v0, hkVector4fParameter v1)
{
	hkVector4_AdvancedInterface::unrollf_setDiv<A,D>::apply(m_quad,v0,v1);
}

HK_FORCE_INLINE void hkVector4f::setDiv(hkVector4fParameter v0, hkVector4fParameter v1)
{
	hkVector4_AdvancedInterface::unrollf_setDiv<HK_ACC_23_BIT,HK_DIV_IGNORE>::apply(m_quad,v0,v1);
}

template <hkMathAccuracyMode A, hkMathDivByZeroMode D>
HK_FORCE_INLINE void hkVector4f::div(hkVector4fParameter a)
{
	setDiv<A,D>( *this, a );
}

HK_FORCE_INLINE void hkVector4f::div(hkVector4fParameter a)
{
	setDiv( *this, a );
}



namespace hkVector4_AdvancedInterface
{

template <hkMathAccuracyMode A, hkMathNegSqrtMode S>
struct unrollf_setSqrt { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, hkVector4fParameter a)
{
	HK_VECTOR4f_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <hkMathAccuracyMode A>
struct unrollf_setSqrt<A, HK_SQRT_IGNORE> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, hkVector4fParameter a)
{
	switch (A)
	{
		case HK_ACC_23_BIT: 
			{
				self.v[0] = hkFloat32(hkMath::rcpF32Approx23Bit(hkMath::invSqrtF32Approx23Bit(hkFloat32(a.m_quad.v[0]))));
				self.v[1] = hkFloat32(hkMath::rcpF32Approx23Bit(hkMath::invSqrtF32Approx23Bit(hkFloat32(a.m_quad.v[1]))));
				self.v[2] = hkFloat32(hkMath::rcpF32Approx23Bit(hkMath::invSqrtF32Approx23Bit(hkFloat32(a.m_quad.v[2]))));
				self.v[3] = hkFloat32(hkMath::rcpF32Approx23Bit(hkMath::invSqrtF32Approx23Bit(hkFloat32(a.m_quad.v[3]))));
			}
			break;
		case HK_ACC_12_BIT: 
			{
				self.v[0] = hkFloat32(hkMath::rcpF32Approx12Bit(hkMath::invSqrtF32Approx12Bit(hkFloat32(a.m_quad.v[0]))));
				self.v[1] = hkFloat32(hkMath::rcpF32Approx12Bit(hkMath::invSqrtF32Approx12Bit(hkFloat32(a.m_quad.v[1]))));
				self.v[2] = hkFloat32(hkMath::rcpF32Approx12Bit(hkMath::invSqrtF32Approx12Bit(hkFloat32(a.m_quad.v[2]))));
				self.v[3] = hkFloat32(hkMath::rcpF32Approx12Bit(hkMath::invSqrtF32Approx12Bit(hkFloat32(a.m_quad.v[3]))));
			}
			break;
		default:         
			{
				self.v[0] = hkMath::sqrt(a.m_quad.v[0]);
				self.v[1] = hkMath::sqrt(a.m_quad.v[1]);
				self.v[2] = hkMath::sqrt(a.m_quad.v[2]);
				self.v[3] = hkMath::sqrt(a.m_quad.v[3]);
			}
			break; // HK_ACC_FULL
	}
} };
template <hkMathAccuracyMode A>
struct unrollf_setSqrt<A, HK_SQRT_SET_ZERO> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, hkVector4fParameter a)
{
	switch (A)
	{
	case HK_ACC_23_BIT: 
		{
			self.v[0] = ((a.m_quad.v[0] <= hkFloat32(0)) ? hkFloat32(0) : hkFloat32(hkMath::rcpF32Approx23Bit(hkMath::invSqrtF32Approx23Bit(hkFloat32(a.m_quad.v[0])))));
			self.v[1] = ((a.m_quad.v[1] <= hkFloat32(0)) ? hkFloat32(0) : hkFloat32(hkMath::rcpF32Approx23Bit(hkMath::invSqrtF32Approx23Bit(hkFloat32(a.m_quad.v[1])))));
			self.v[2] = ((a.m_quad.v[2] <= hkFloat32(0)) ? hkFloat32(0) : hkFloat32(hkMath::rcpF32Approx23Bit(hkMath::invSqrtF32Approx23Bit(hkFloat32(a.m_quad.v[2])))));
			self.v[3] = ((a.m_quad.v[3] <= hkFloat32(0)) ? hkFloat32(0) : hkFloat32(hkMath::rcpF32Approx23Bit(hkMath::invSqrtF32Approx23Bit(hkFloat32(a.m_quad.v[3])))));
		}
		break;
	case HK_ACC_12_BIT: 
		{
			self.v[0] = ((a.m_quad.v[0] <= hkFloat32(0)) ? hkFloat32(0) : hkFloat32(hkMath::rcpF32Approx12Bit(hkMath::invSqrtF32Approx12Bit(hkFloat32(a.m_quad.v[0])))));
			self.v[1] = ((a.m_quad.v[1] <= hkFloat32(0)) ? hkFloat32(0) : hkFloat32(hkMath::rcpF32Approx12Bit(hkMath::invSqrtF32Approx12Bit(hkFloat32(a.m_quad.v[1])))));
			self.v[2] = ((a.m_quad.v[2] <= hkFloat32(0)) ? hkFloat32(0) : hkFloat32(hkMath::rcpF32Approx12Bit(hkMath::invSqrtF32Approx12Bit(hkFloat32(a.m_quad.v[2])))));
			self.v[3] = ((a.m_quad.v[3] <= hkFloat32(0)) ? hkFloat32(0) : hkFloat32(hkMath::rcpF32Approx12Bit(hkMath::invSqrtF32Approx12Bit(hkFloat32(a.m_quad.v[3])))));
		}
		break;
	default:         
		{
			self.v[0] = ((a.m_quad.v[0] <= hkFloat32(0)) ? hkFloat32(0) : hkMath::sqrt(a.m_quad.v[0]));
			self.v[1] = ((a.m_quad.v[1] <= hkFloat32(0)) ? hkFloat32(0) : hkMath::sqrt(a.m_quad.v[1]));
			self.v[2] = ((a.m_quad.v[2] <= hkFloat32(0)) ? hkFloat32(0) : hkMath::sqrt(a.m_quad.v[2]));
			self.v[3] = ((a.m_quad.v[3] <= hkFloat32(0)) ? hkFloat32(0) : hkMath::sqrt(a.m_quad.v[3]));
		}
		break; // HK_ACC_FULL
	}
} };

} // namespace 

template <hkMathAccuracyMode A, hkMathNegSqrtMode S>
HK_FORCE_INLINE void hkVector4f::setSqrt(hkVector4fParameter a)
{
	hkVector4_AdvancedInterface::unrollf_setSqrt<A,S>::apply(m_quad, a);
}

HK_FORCE_INLINE void hkVector4f::setSqrt(hkVector4fParameter a)
{
	hkVector4_AdvancedInterface::unrollf_setSqrt<HK_ACC_23_BIT,HK_SQRT_SET_ZERO>::apply(m_quad, a);
}




namespace hkVector4_AdvancedInterface
{

template <hkMathAccuracyMode A, hkMathNegSqrtMode S>
struct unrollf_setSqrtInverse { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, hkVector4fParameter a)
{
	HK_VECTOR4f_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <hkMathAccuracyMode A>
struct unrollf_setSqrtInverse<A, HK_SQRT_IGNORE> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, hkVector4fParameter a)
{
	switch (A)
	{
	case HK_ACC_23_BIT: 
		{
			self.v[0] = hkFloat32(hkMath::invSqrtF32Approx23Bit(hkFloat32(a.m_quad.v[0])));
			self.v[1] = hkFloat32(hkMath::invSqrtF32Approx23Bit(hkFloat32(a.m_quad.v[1])));
			self.v[2] = hkFloat32(hkMath::invSqrtF32Approx23Bit(hkFloat32(a.m_quad.v[2])));
			self.v[3] = hkFloat32(hkMath::invSqrtF32Approx23Bit(hkFloat32(a.m_quad.v[3])));
		}
		break;
	case HK_ACC_12_BIT: 
		{
			self.v[0] = hkFloat32(hkMath::invSqrtF32Approx12Bit(hkFloat32(a.m_quad.v[0])));
			self.v[1] = hkFloat32(hkMath::invSqrtF32Approx12Bit(hkFloat32(a.m_quad.v[1])));
			self.v[2] = hkFloat32(hkMath::invSqrtF32Approx12Bit(hkFloat32(a.m_quad.v[2])));
			self.v[3] = hkFloat32(hkMath::invSqrtF32Approx12Bit(hkFloat32(a.m_quad.v[3])));
		}
		break;
	default:         
		{
			self.v[0] = hkMath::sqrtInverse(a.m_quad.v[0]);
			self.v[1] = hkMath::sqrtInverse(a.m_quad.v[1]);
			self.v[2] = hkMath::sqrtInverse(a.m_quad.v[2]);
			self.v[3] = hkMath::sqrtInverse(a.m_quad.v[3]);
		}
		break; // HK_ACC_FULL
	}
} };
template <hkMathAccuracyMode A>
struct unrollf_setSqrtInverse<A, HK_SQRT_SET_ZERO> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, hkVector4fParameter a)
{
	switch (A)
	{
	case HK_ACC_23_BIT: 
		{
			self.v[0] = ((a.m_quad.v[0] <= hkFloat32(0)) ? hkFloat32(0) : hkFloat32(hkMath::invSqrtF32Approx23Bit(hkFloat32(a.m_quad.v[0]))));
			self.v[1] = ((a.m_quad.v[1] <= hkFloat32(0)) ? hkFloat32(0) : hkFloat32(hkMath::invSqrtF32Approx23Bit(hkFloat32(a.m_quad.v[1]))));
			self.v[2] = ((a.m_quad.v[2] <= hkFloat32(0)) ? hkFloat32(0) : hkFloat32(hkMath::invSqrtF32Approx23Bit(hkFloat32(a.m_quad.v[2]))));
			self.v[3] = ((a.m_quad.v[3] <= hkFloat32(0)) ? hkFloat32(0) : hkFloat32(hkMath::invSqrtF32Approx23Bit(hkFloat32(a.m_quad.v[3]))));
		}
		break;
	case HK_ACC_12_BIT: 
		{
			self.v[0] = ((a.m_quad.v[0] <= hkFloat32(0)) ? hkFloat32(0) : hkFloat32(hkMath::invSqrtF32Approx12Bit(hkFloat32(a.m_quad.v[0]))));
			self.v[1] = ((a.m_quad.v[1] <= hkFloat32(0)) ? hkFloat32(0) : hkFloat32(hkMath::invSqrtF32Approx12Bit(hkFloat32(a.m_quad.v[1]))));
			self.v[2] = ((a.m_quad.v[2] <= hkFloat32(0)) ? hkFloat32(0) : hkFloat32(hkMath::invSqrtF32Approx12Bit(hkFloat32(a.m_quad.v[2]))));
			self.v[3] = ((a.m_quad.v[3] <= hkFloat32(0)) ? hkFloat32(0) : hkFloat32(hkMath::invSqrtF32Approx12Bit(hkFloat32(a.m_quad.v[3]))));
		}
		break;
	default:         
		{
			self.v[0] = ((a.m_quad.v[0] <= hkFloat32(0)) ? hkFloat32(0) : hkMath::sqrtInverse(a.m_quad.v[0]));
			self.v[1] = ((a.m_quad.v[1] <= hkFloat32(0)) ? hkFloat32(0) : hkMath::sqrtInverse(a.m_quad.v[1]));
			self.v[2] = ((a.m_quad.v[2] <= hkFloat32(0)) ? hkFloat32(0) : hkMath::sqrtInverse(a.m_quad.v[2]));
			self.v[3] = ((a.m_quad.v[3] <= hkFloat32(0)) ? hkFloat32(0) : hkMath::sqrtInverse(a.m_quad.v[3]));
		}
		break; // HK_ACC_FULL
	}
} };
} // namespace 

template <hkMathAccuracyMode A, hkMathNegSqrtMode S>
HK_FORCE_INLINE void hkVector4f::setSqrtInverse(hkVector4fParameter a)
{
	hkVector4_AdvancedInterface::unrollf_setSqrtInverse<A,S>::apply(m_quad, a);
}

HK_FORCE_INLINE void hkVector4f::setSqrtInverse(hkVector4fParameter a)
{
	hkVector4_AdvancedInterface::unrollf_setSqrtInverse<HK_ACC_23_BIT,HK_SQRT_SET_ZERO>::apply(m_quad, a);
}


namespace hkVector4_AdvancedInterface
{
template <int N, hkMathIoMode A>
struct unrollf_load { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, const hkFloat32* HK_RESTRICT p)
{
	HK_VECTOR4f_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <int N, hkMathIoMode A>
struct unrollf_load_D { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, const hkDouble64* HK_RESTRICT p)
{
	HK_VECTOR4f_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };

template <int N>
struct unrollf_load<N, HK_IO_BYTE_ALIGNED> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, const hkFloat32* HK_RESTRICT p)
{
				  self.v[0] = hkFloat32(p[0]);
	if ( N >= 2){ self.v[1] = hkFloat32(p[1]);	}
	if ( N >= 3){ self.v[2] = hkFloat32(p[2]);	}
	if ( N >= 4){ self.v[3] = hkFloat32(p[3]);	}

#if defined(HK_DEBUG)
#if defined(HK_REAL_IS_DOUBLE)
	for(int i=N; i<4; ++i) *((hkUint64*)&(self.v[i])) = 0xffffffffffffffffull;
#else
	for(int i=N; i<4; ++i) *((hkUint32*)&(self.v[i])) = 0xffffffff;
#endif
#endif
} };
template <int N>
struct unrollf_load_D<N, HK_IO_BYTE_ALIGNED> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, const hkDouble64* HK_RESTRICT p)
{
				  self.v[0] = hkFloat32(p[0]);
	if ( N >= 2){ self.v[1] = hkFloat32(p[1]);	}
	if ( N >= 3){ self.v[2] = hkFloat32(p[2]);	}
	if ( N >= 4){ self.v[3] = hkFloat32(p[3]);	}

#if defined(HK_DEBUG)
#if defined(HK_REAL_IS_DOUBLE)
	for(int i=N; i<4; ++i) *((hkUint64*)&(self.v[i])) = 0xffffffffffffffffull;
#else
	for(int i=N; i<4; ++i) *((hkUint32*)&(self.v[i])) = 0xffffffff;
#endif
#endif
} };

template <int N>
struct unrollf_load<N, HK_IO_NATIVE_ALIGNED> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, const hkFloat32* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & (sizeof(hkFloat32)-1) ) == 0, "pointer must be aligned to native size of hkFloat32.");
	unrollf_load<N, HK_IO_BYTE_ALIGNED>::apply(self,p);
} };
template <int N>
struct unrollf_load_D<N, HK_IO_NATIVE_ALIGNED> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, const hkDouble64* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & (sizeof(hkDouble64)-1) ) == 0, "pointer must be aligned to native size of hkDouble64.");
	unrollf_load_D<N, HK_IO_BYTE_ALIGNED>::apply(self,p);
} };

template <int N>
struct unrollf_load<N, HK_IO_SIMD_ALIGNED> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, const hkFloat32* HK_RESTRICT p)
{
#if !defined(HK_ALIGN_RELAX_CHECKS)
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & ((sizeof(hkFloat32)*(N!=3?N:4) )-1) ) == 0, "pointer must be aligned for SIMD.");
#endif
	unrollf_load<N, HK_IO_NATIVE_ALIGNED>::apply(self,p);
} };
template <int N>
struct unrollf_load_D<N, HK_IO_SIMD_ALIGNED> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, const hkDouble64* HK_RESTRICT p)
{
#if !defined(HK_ALIGN_RELAX_CHECKS)
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & ((sizeof(hkDouble64)*(N!=3?N:4) )-1) ) == 0, "pointer must be aligned for SIMD.");
#endif
	unrollf_load_D<N, HK_IO_NATIVE_ALIGNED>::apply(self,p);
} };

template <int N>
struct unrollf_load<N, HK_IO_NOT_CACHED> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, const hkFloat32* HK_RESTRICT p)
{
	unrollf_load<N, HK_IO_SIMD_ALIGNED>::apply(self,p);
} };
template <int N>
struct unrollf_load_D<N, HK_IO_NOT_CACHED> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, const hkDouble64* HK_RESTRICT p)
{
	unrollf_load_D<N, HK_IO_SIMD_ALIGNED>::apply(self,p);
} };
} // namespace 

template <int N, hkMathIoMode A>
HK_FORCE_INLINE void hkVector4f::load(const hkFloat32* p)
{
	HK_VECTOR4f_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrollf_load<N,A>::apply(m_quad, p);
}

template <int N, hkMathIoMode A>
HK_FORCE_INLINE void hkVector4f::load(const hkDouble64* p)
{
	HK_VECTOR4f_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrollf_load_D<N,A>::apply(m_quad, p);
}

template <int N>
HK_FORCE_INLINE void hkVector4f::load(const hkFloat32* p)
{
	HK_VECTOR4f_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrollf_load<N,HK_IO_SIMD_ALIGNED>::apply(m_quad, p);
}

template <int N>
HK_FORCE_INLINE void hkVector4f::load(const hkDouble64* p)
{
	HK_VECTOR4f_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrollf_load_D<N,HK_IO_SIMD_ALIGNED>::apply(m_quad, p);
}



namespace hkVector4_AdvancedInterface
{
template <int N, hkMathIoMode A>
struct unrollf_loadH { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, const hkHalf* HK_RESTRICT p)
{
	HK_VECTOR4f_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <int N>
struct unrollf_loadH<N, HK_IO_BYTE_ALIGNED> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, const hkHalf* HK_RESTRICT p)
{
	switch (N)
	{
		case 4:  self.v[3] = p[3].getFloat32();
		case 3:  self.v[2] = p[2].getFloat32();
		case 2:  self.v[1] = p[1].getFloat32();
		default: self.v[0] = p[0].getFloat32(); break;
	}
#if defined(HK_REAL_IS_DOUBLE)
	for(int i=N; i<4; ++i) *((hkUint64*)&(self.v[i])) = 0xffffffffffffffffull;
#else
	for(int i=N; i<4; ++i) *((hkUint32*)&(self.v[i])) = 0xffffffff;
#endif
} };

template <int N>
struct unrollf_loadH<N, HK_IO_NATIVE_ALIGNED> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, const hkHalf* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & (sizeof(hkHalf)-1) ) == 0, "pointer must be aligned to native size of hkHalf.");
	unrollf_loadH<N, HK_IO_BYTE_ALIGNED>::apply(self,p);
} };

template <int N>
struct unrollf_loadH<N, HK_IO_SIMD_ALIGNED> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, const hkHalf* HK_RESTRICT p)
{
#if !defined(HK_ALIGN_RELAX_CHECKS)
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & ((sizeof(hkHalf)*(N!=3?N:4) )-1) ) == 0, "pointer must be aligned for SIMD.");
#endif
	unrollf_loadH<N, HK_IO_NATIVE_ALIGNED>::apply(self,p);
} };

template <int N>
struct unrollf_loadH<N, HK_IO_NOT_CACHED> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, const hkHalf* HK_RESTRICT p)
{
	unrollf_loadH<N, HK_IO_SIMD_ALIGNED>::apply(self,p);
} };
} // namespace 

template <int N, hkMathIoMode A>
HK_FORCE_INLINE void hkVector4f::load(const hkHalf* p)
{
	HK_VECTOR4f_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrollf_loadH<N,A>::apply(m_quad, p);
}

template <int N>
HK_FORCE_INLINE void hkVector4f::load(const hkHalf* p)
{
	HK_VECTOR4f_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrollf_loadH<N,HK_IO_SIMD_ALIGNED>::apply(m_quad, p);
}



namespace hkVector4_AdvancedInterface
{
	template <int N, hkMathIoMode A>
	struct unrollf_loadF16 { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, const hkFloat16* HK_RESTRICT p)
	{
		HK_VECTOR4f_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
	} };

	template <int N>
	struct unrollf_loadF16<N, HK_IO_BYTE_ALIGNED> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, const hkFloat16* HK_RESTRICT p)
	{
		switch (N)
		{
		case 4:  self.v[3] = p[3].getFloat32();
		case 3:  self.v[2] = p[2].getFloat32();
		case 2:  self.v[1] = p[1].getFloat32();
		default: self.v[0] = p[0].getFloat32(); break;
		}
#if defined(HK_DEBUG)
#if defined(HK_REAL_IS_DOUBLE)
		for(int i=N; i<4; ++i) *((hkUint64*)&(self.v[i])) = 0xffffffffffffffffull;
#else
		for(int i=N; i<4; ++i) *((hkUint32*)&(self.v[i])) = 0xffffffff;
#endif
#endif
	} };

	template <int N>
	struct unrollf_loadF16<N, HK_IO_NATIVE_ALIGNED> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, const hkFloat16* HK_RESTRICT p)
	{
		HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & (sizeof(hkFloat16)-1) ) == 0, "pointer must be aligned to native size of hkFloat16.");
		unrollf_loadF16<N, HK_IO_BYTE_ALIGNED>::apply(self,p);
	} };
	template <int N>
	struct unrollf_loadF16<N, HK_IO_SIMD_ALIGNED> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, const hkFloat16* HK_RESTRICT p)
	{
#if !defined(HK_ALIGN_RELAX_CHECKS)
		HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & ((sizeof(hkFloat16)*(N!=3?N:4) )-1) ) == 0, "pointer must be aligned for SIMD.");
#endif
		unrollf_loadF16<N, HK_IO_NATIVE_ALIGNED>::apply(self,p);
	} };
	template <int N>
	struct unrollf_loadF16<N, HK_IO_NOT_CACHED> { HK_FORCE_INLINE static void apply(hkQuadFloat32& self, const hkFloat16* HK_RESTRICT p)
	{
		unrollf_loadF16<N, HK_IO_SIMD_ALIGNED>::apply(self,p);
	} };
} // namespace 

template <int N, hkMathIoMode A>
HK_FORCE_INLINE void hkVector4f::load(const hkFloat16* p)
{
	HK_VECTOR4f_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrollf_loadF16<N,A>::apply(m_quad, p);
}

template <int N>
HK_FORCE_INLINE void hkVector4f::load(const hkFloat16* p)
{
	HK_VECTOR4f_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrollf_loadF16<N,HK_IO_SIMD_ALIGNED>::apply(m_quad, p);
}



namespace hkVector4_AdvancedInterface
{
template <int N, hkMathIoMode A>
struct unrollf_store { HK_FORCE_INLINE static void apply(const hkQuadFloat32& self, hkFloat32* HK_RESTRICT p)
{
	HK_VECTOR4f_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <int N, hkMathIoMode A>
struct unrollf_store_D { HK_FORCE_INLINE static void apply(const hkQuadFloat32& self, hkDouble64* HK_RESTRICT p)
{
	HK_VECTOR4f_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };

template <int N>
struct unrollf_store<N, HK_IO_BYTE_ALIGNED> { HK_FORCE_INLINE static void apply(const hkQuadFloat32& self, hkFloat32* HK_RESTRICT p)
{
				  p[0] = hkFloat32(self.v[0]);
	if ( N >= 2){ p[1] = hkFloat32(self.v[1]); }
	if ( N >= 3){ p[2] = hkFloat32(self.v[2]); }
	if ( N >= 4){ p[3] = hkFloat32(self.v[3]); }
} };
template <int N>
struct unrollf_store_D<N, HK_IO_BYTE_ALIGNED> { HK_FORCE_INLINE static void apply(const hkQuadFloat32& self, hkDouble64* HK_RESTRICT p)
{
				  p[0] = hkDouble64(self.v[0]);
	if ( N >= 2){ p[1] = hkDouble64(self.v[1]); }
	if ( N >= 3){ p[2] = hkDouble64(self.v[2]); }
	if ( N >= 4){ p[3] = hkDouble64(self.v[3]); }
} };

template <int N>
struct unrollf_store<N, HK_IO_NATIVE_ALIGNED> { HK_FORCE_INLINE static void apply(const hkQuadFloat32& self, hkFloat32* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & (sizeof(hkFloat32)-1) ) == 0, "pointer must be aligned to native size of hkFloat32.");
	unrollf_store<N, HK_IO_BYTE_ALIGNED>::apply(self,p);
} };
template <int N>
struct unrollf_store_D<N, HK_IO_NATIVE_ALIGNED> { HK_FORCE_INLINE static void apply(const hkQuadFloat32& self, hkDouble64* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & (sizeof(hkDouble64)-1) ) == 0, "pointer must be aligned to native size of hkDouble64.");
	unrollf_store_D<N, HK_IO_BYTE_ALIGNED>::apply(self,p);
} };

template <int N>
struct unrollf_store<N, HK_IO_SIMD_ALIGNED> { HK_FORCE_INLINE static void apply(const hkQuadFloat32& self, hkFloat32* HK_RESTRICT p)
{
#if !defined(HK_ALIGN_RELAX_CHECKS)
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & ((sizeof(hkFloat32)*(N!=3?N:4) )-1) ) == 0, "pointer must be aligned for SIMD.");
#endif
	unrollf_store<N, HK_IO_NATIVE_ALIGNED>::apply(self,p);
} };
template <int N>
struct unrollf_store_D<N, HK_IO_SIMD_ALIGNED> { HK_FORCE_INLINE static void apply(const hkQuadFloat32& self, hkDouble64* HK_RESTRICT p)
{
#if !defined(HK_ALIGN_RELAX_CHECKS)
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & ((sizeof(hkDouble64)*(N!=3?N:4) )-1) ) == 0, "pointer must be aligned for SIMD.");
#endif
	unrollf_store_D<N, HK_IO_NATIVE_ALIGNED>::apply(self,p);
} };

template <int N>
struct unrollf_store<N, HK_IO_NOT_CACHED> { HK_FORCE_INLINE static void apply(const hkQuadFloat32& self, hkFloat32* HK_RESTRICT p)
{
	unrollf_store<N, HK_IO_SIMD_ALIGNED>::apply(self,p);
} };
template <int N>
struct unrollf_store_D<N, HK_IO_NOT_CACHED> { HK_FORCE_INLINE static void apply(const hkQuadFloat32& self, hkDouble64* HK_RESTRICT p)
{
	unrollf_store_D<N, HK_IO_SIMD_ALIGNED>::apply(self,p);
} };
} // namespace 

template <int N, hkMathIoMode A, hkMathRoundingMode R> 
HK_FORCE_INLINE void hkVector4f::store(hkFloat32* p) const
{
	HK_VECTOR4f_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrollf_store<N,A>::apply(m_quad, p);
}

template <int N, hkMathIoMode A, hkMathRoundingMode R> 
HK_FORCE_INLINE void hkVector4f::store(hkDouble64* p) const
{
	HK_VECTOR4f_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrollf_store_D<N,A>::apply(m_quad, p);
}

template <int N, hkMathIoMode A> 
HK_FORCE_INLINE void hkVector4f::store(hkFloat32* p) const
{
	HK_VECTOR4f_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrollf_store<N,A>::apply(m_quad, p);
}

template <int N, hkMathIoMode A> 
HK_FORCE_INLINE void hkVector4f::store(hkDouble64* p) const
{
	HK_VECTOR4f_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrollf_store_D<N,A>::apply(m_quad, p);
}

template <int N> 
HK_FORCE_INLINE void hkVector4f::store(hkFloat32* p) const
{
	HK_VECTOR4f_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrollf_store<N,HK_IO_SIMD_ALIGNED>::apply(m_quad, p);
}

template <int N> 
HK_FORCE_INLINE void hkVector4f::store(hkDouble64* p) const
{
	HK_VECTOR4f_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrollf_store_D<N,HK_IO_SIMD_ALIGNED>::apply(m_quad, p);
}



namespace hkVector4_AdvancedInterface
{
template <int N, hkMathIoMode A, hkMathRoundingMode R>
struct unrollf_storeH { HK_FORCE_INLINE static void apply(const hkQuadFloat32& self, hkHalf* HK_RESTRICT p)
{
	HK_VECTOR4f_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <int N, hkMathRoundingMode R>
struct unrollf_storeH<N, HK_IO_BYTE_ALIGNED, R> { HK_FORCE_INLINE static void apply(const hkQuadFloat32& self, hkHalf* HK_RESTRICT p)
{
	switch (N)
	{
		case 4:  p[3].set<(R == HK_ROUND_NEAREST)>(self.v[3]);
		case 3:  p[2].set<(R == HK_ROUND_NEAREST)>(self.v[2]);
		case 2:  p[1].set<(R == HK_ROUND_NEAREST)>(self.v[1]);
		default: p[0].set<(R == HK_ROUND_NEAREST)>(self.v[0]); break;
	}
} };
template <int N, hkMathRoundingMode R>
struct unrollf_storeH<N, HK_IO_NATIVE_ALIGNED, R> { HK_FORCE_INLINE static void apply(const hkQuadFloat32& self, hkHalf* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & (sizeof(hkHalf)-1) ) == 0, "pointer must be aligned to native size of hkHalf.");
	unrollf_storeH<N, HK_IO_BYTE_ALIGNED, R>::apply(self,p);
} };
template <int N, hkMathRoundingMode R>
struct unrollf_storeH<N, HK_IO_SIMD_ALIGNED, R> { HK_FORCE_INLINE static void apply(const hkQuadFloat32& self, hkHalf* HK_RESTRICT p)
{
#if !defined(HK_ALIGN_RELAX_CHECKS)
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & ((sizeof(hkHalf)*(N!=3?N:4) )-1) ) == 0, "pointer must be aligned for SIMD.");
#endif
	unrollf_storeH<N, HK_IO_NATIVE_ALIGNED, R>::apply(self,p);
} };
template <int N, hkMathRoundingMode R>
struct unrollf_storeH<N, HK_IO_NOT_CACHED, R> { HK_FORCE_INLINE static void apply(const hkQuadFloat32& self, hkHalf* HK_RESTRICT p)
{
	unrollf_storeH<N, HK_IO_SIMD_ALIGNED, R>::apply(self,p);
} };
} // namespace 

template <int N, hkMathIoMode A, hkMathRoundingMode R> 
HK_FORCE_INLINE void hkVector4f::store(hkHalf* p) const
{
	HK_VECTOR4f_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrollf_storeH<N,A,R>::apply(m_quad, p);
}

template <int N, hkMathIoMode A> 
HK_FORCE_INLINE void hkVector4f::store(hkHalf* p) const
{
	HK_VECTOR4f_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrollf_storeH<N,A,HK_ROUND_DEFAULT>::apply(m_quad, p);
}

template <int N> 
HK_FORCE_INLINE void hkVector4f::store(hkHalf* p) const
{
	HK_VECTOR4f_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrollf_storeH<N,HK_IO_SIMD_ALIGNED,HK_ROUND_DEFAULT>::apply(m_quad, p);
}






namespace hkVector4_AdvancedInterface
{
template <int N, hkMathIoMode A, hkMathRoundingMode R>
struct unrollf_storeF16 { HK_FORCE_INLINE static void apply(const hkQuadFloat32& self, hkFloat16* HK_RESTRICT p)
{
	HK_VECTOR4f_TEMPLATE_CONFIG_NOT_IMPLEMENTED;
} };
template <int N, hkMathRoundingMode R>
struct unrollf_storeF16<N, HK_IO_BYTE_ALIGNED, R> { HK_FORCE_INLINE static void apply(const hkQuadFloat32& self, hkFloat16* HK_RESTRICT p)
{
	switch (N)
	{
		case 4:  p[3].setReal<(R == HK_ROUND_NEAREST)>(self.v[3]);
		case 3:  p[2].setReal<(R == HK_ROUND_NEAREST)>(self.v[2]);
		case 2:  p[1].setReal<(R == HK_ROUND_NEAREST)>(self.v[1]);
		default: p[0].setReal<(R == HK_ROUND_NEAREST)>(self.v[0]); break;
	}
} };
template <int N, hkMathRoundingMode R>
struct unrollf_storeF16<N, HK_IO_NATIVE_ALIGNED, R> { HK_FORCE_INLINE static void apply(const hkQuadFloat32& self, hkFloat16* HK_RESTRICT p)
{
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & (sizeof(hkFloat16)-1) ) == 0, "pointer must be aligned to native size of hkFloat16.");
	unrollf_storeF16<N, HK_IO_BYTE_ALIGNED, R>::apply(self,p);
} };
template <int N, hkMathRoundingMode R>
struct unrollf_storeF16<N, HK_IO_SIMD_ALIGNED, R> { HK_FORCE_INLINE static void apply(const hkQuadFloat32& self, hkFloat16* HK_RESTRICT p)
{
#if !defined(HK_ALIGN_RELAX_CHECKS)
	HK_MATH_ASSERT(0x64211c2f, ( ((hkUlong)p) & ((sizeof(hkFloat16)*(N!=3?N:4) )-1) ) == 0, "pointer must be aligned for SIMD.");
#endif
	unrollf_storeF16<N, HK_IO_NATIVE_ALIGNED, R>::apply(self,p);
} };
template <int N, hkMathRoundingMode R>
struct unrollf_storeF16<N, HK_IO_NOT_CACHED, R> { HK_FORCE_INLINE static void apply(const hkQuadFloat32& self, hkFloat16* HK_RESTRICT p)
{
	unrollf_storeF16<N, HK_IO_SIMD_ALIGNED, R>::apply(self,p);
} };
} // namespace 

template <int N, hkMathIoMode A, hkMathRoundingMode R> 
HK_FORCE_INLINE void hkVector4f::store(hkFloat16* p) const
{
	HK_VECTOR4f_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrollf_storeF16<N,A,R>::apply(m_quad, p);
}

template <int N, hkMathIoMode A> 
HK_FORCE_INLINE void hkVector4f::store(hkFloat16* p) const
{
	HK_VECTOR4f_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrollf_storeF16<N,A,HK_ROUND_DEFAULT>::apply(m_quad, p);
}

template <int N> 
HK_FORCE_INLINE void hkVector4f::store(hkFloat16* p) const
{
	HK_VECTOR4f_UNSUPPORTED_LENGTH_CHECK;
	hkVector4_AdvancedInterface::unrollf_storeF16<N,HK_IO_SIMD_ALIGNED,HK_ROUND_DEFAULT>::apply(m_quad, p);
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
