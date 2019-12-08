/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

/*static*/ HK_FORCE_INLINE hkSimdFloat32 HK_CALL hkSimdFloat32::fromFloat(const hkFloat32& x)
{ 
	hkSimdFloat32 r; 
	r.setFromFloat(x); 
	return r; 
}

/*static*/ HK_FORCE_INLINE hkSimdFloat32 HK_CALL hkSimdFloat32::fromHalf(const hkHalf& x)
{ 
	hkSimdFloat32 r; 
	r.setFromHalf(x); 
	return r; 
}

/*static*/ HK_FORCE_INLINE hkSimdFloat32 HK_CALL hkSimdFloat32::fromUint16(const hkUint16& x)
{ 
	hkSimdFloat32 r; 
	r.setFromUint16(x); 
	return r; 
}

/*static*/ HK_FORCE_INLINE hkSimdFloat32 HK_CALL hkSimdFloat32::fromUint8(const hkUint8& x)
{ 
	hkSimdFloat32 r; 
	r.setFromUint8(x); 
	return r; 
}

/*static*/ HK_FORCE_INLINE hkSimdFloat32 HK_CALL hkSimdFloat32::fromInt32(const hkInt32& x)
{ 
	hkSimdFloat32 r; 
	r.setFromInt32(x); 
	return r; 
}

HK_FORCE_INLINE void hkSimdFloat32::operator= (hkSimdFloat32Parameter v)
{
	m_real = v.m_real;
}

HK_FORCE_INLINE void hkSimdFloat32::setAdd(hkSimdFloat32Parameter a, hkSimdFloat32Parameter b)
{
	*this = a + b;
}
HK_FORCE_INLINE void hkSimdFloat32::setSub(hkSimdFloat32Parameter a, hkSimdFloat32Parameter b)
{
	*this = a - b;
}
HK_FORCE_INLINE void hkSimdFloat32::setMul(hkSimdFloat32Parameter a, hkSimdFloat32Parameter b)
{
	*this = a * b;
}

HK_FORCE_INLINE void hkSimdFloat32::setAddMul(hkSimdFloat32Parameter a, hkSimdFloat32Parameter b, hkSimdFloat32Parameter c)
{
	*this = a + (b * c);
}
HK_FORCE_INLINE void hkSimdFloat32::setSubMul(hkSimdFloat32Parameter a, hkSimdFloat32Parameter b, hkSimdFloat32Parameter c)
{
	*this = a - (b * c);
}

HK_FORCE_INLINE void hkSimdFloat32::add(hkSimdFloat32Parameter a)
{
	setAdd( *this, a );
}
HK_FORCE_INLINE void hkSimdFloat32::sub(hkSimdFloat32Parameter a)
{
	setSub( *this, a );
}
HK_FORCE_INLINE void hkSimdFloat32::mul(hkSimdFloat32Parameter a)
{
	setMul( *this, a );
}

HK_FORCE_INLINE void hkSimdFloat32::addMul(hkSimdFloat32Parameter a, hkSimdFloat32Parameter b)
{
	setAddMul( *this, a, b );
}
HK_FORCE_INLINE void hkSimdFloat32::subMul(hkSimdFloat32Parameter a, hkSimdFloat32Parameter b)
{
	setSubMul( *this, a, b );
}

HK_FORCE_INLINE void hkSimdFloat32::setInterpolate( hkSimdFloat32Parameter a, hkSimdFloat32Parameter b, hkSimdFloat32Parameter t )
{
	const hkSimdFloat32 bminusA = b-a;
	setAddMul( a, t, bminusA );
}

template <int N> 
HK_FORCE_INLINE void hkSimdFloat32::setDot( hkVector4fParameter a, hkVector4fParameter b )
{
	*this = a.dot<N>(b);
}

HK_FORCE_INLINE bool hkSimdFloat32::approxEqual(hkSimdFloat32Parameter v, hkSimdFloat32Parameter epsilon) const
{
	hkSimdFloat32 t; t.setAbs(*this - v);
	return t.isLess(epsilon);
}

HK_FORCE_INLINE void hkSimdFloat32::setClamped( hkSimdFloat32Parameter a, hkSimdFloat32Parameter minVal, hkSimdFloat32Parameter maxVal )
{
	// This ensures that if a is NAN, clamped will be maxVal afterwards	
	const hkVector4fComparison maxValGtA = maxVal.greater(a);
	hkSimdFloat32 clamped; clamped.setSelect(maxValGtA, a, maxVal);
	setMax(minVal, clamped);
}

//
//	Returns the reciprocal value of self.
//	Accuracy: 23 bit, divide-by-0 not checked

HK_FORCE_INLINE const hkSimdFloat32 hkSimdFloat32::reciprocal() const
{
	hkSimdFloat32 r;
	r.setReciprocal(*this);
	return r;
}

#ifndef HK_DISABLE_OLD_VECTOR4_INTERFACE

//
// old interface
//
HK_FORCE_INLINE hkVector4fComparison hkSimdFloat32::isNegative() const { return signBitSet(); }
HK_FORCE_INLINE hkVector4fComparison hkSimdFloat32::isPositive() const { return signBitClear(); }
HK_FORCE_INLINE hkBool32 hkSimdFloat32::isZero() const { return isEqualZero(); }
HK_FORCE_INLINE hkVector4fComparison hkSimdFloat32::compareLessThanZero() const { return lessZero(); }
HK_FORCE_INLINE hkVector4fComparison hkSimdFloat32::compareGreaterThanZero() const { return greaterZero(); }
HK_FORCE_INLINE hkVector4fComparison hkSimdFloat32::compareLessThan(hkSimdFloat32Parameter a) const { return less(a); }
HK_FORCE_INLINE hkVector4fComparison hkSimdFloat32::compareLessThanEqual(hkSimdFloat32Parameter a) const { return lessEqual(a); }
HK_FORCE_INLINE hkVector4fComparison hkSimdFloat32::compareGreaterThan(hkSimdFloat32Parameter a) const { return greater(a); }
HK_FORCE_INLINE hkVector4fComparison hkSimdFloat32::compareGreaterThanEqual(hkSimdFloat32Parameter a) const { return greaterEqual(a); }

#endif

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
