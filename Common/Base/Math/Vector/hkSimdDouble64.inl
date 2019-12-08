/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

/*static*/ HK_FORCE_INLINE hkSimdDouble64 HK_CALL hkSimdDouble64::fromFloat(const hkDouble64& x)
{ 
	hkSimdDouble64 r; 
	r.setFromFloat(x); 
	return r; 
}

/*static*/ HK_FORCE_INLINE hkSimdDouble64 HK_CALL hkSimdDouble64::fromHalf(const hkHalf& x)
{ 
	hkSimdDouble64 r; 
	r.setFromHalf(x); 
	return r; 
}

/*static*/ HK_FORCE_INLINE hkSimdDouble64 HK_CALL hkSimdDouble64::fromUint16(const hkUint16& x)
{ 
	hkSimdDouble64 r; 
	r.setFromUint16(x); 
	return r; 
}

/*static*/ HK_FORCE_INLINE hkSimdDouble64 HK_CALL hkSimdDouble64::fromUint8(const hkUint8& x)
{ 
	hkSimdDouble64 r; 
	r.setFromUint8(x); 
	return r; 
}

/*static*/ HK_FORCE_INLINE hkSimdDouble64 HK_CALL hkSimdDouble64::fromInt32(const hkInt32& x)
{ 
	hkSimdDouble64 r; 
	r.setFromInt32(x); 
	return r; 
}

HK_FORCE_INLINE void hkSimdDouble64::operator= (hkSimdDouble64Parameter v)
{
	m_real = v.m_real;
}

HK_FORCE_INLINE void hkSimdDouble64::setAdd(hkSimdDouble64Parameter a, hkSimdDouble64Parameter b)
{
	*this = a + b;
}
HK_FORCE_INLINE void hkSimdDouble64::setSub(hkSimdDouble64Parameter a, hkSimdDouble64Parameter b)
{
	*this = a - b;
}
HK_FORCE_INLINE void hkSimdDouble64::setMul(hkSimdDouble64Parameter a, hkSimdDouble64Parameter b)
{
	*this = a * b;
}

HK_FORCE_INLINE void hkSimdDouble64::setAddMul(hkSimdDouble64Parameter a, hkSimdDouble64Parameter b, hkSimdDouble64Parameter c)
{
	*this = a + (b * c);
}
HK_FORCE_INLINE void hkSimdDouble64::setSubMul(hkSimdDouble64Parameter a, hkSimdDouble64Parameter b, hkSimdDouble64Parameter c)
{
	*this = a - (b * c);
}

HK_FORCE_INLINE void hkSimdDouble64::add(hkSimdDouble64Parameter a)
{
	setAdd( *this, a );
}
HK_FORCE_INLINE void hkSimdDouble64::sub(hkSimdDouble64Parameter a)
{
	setSub( *this, a );
}
HK_FORCE_INLINE void hkSimdDouble64::mul(hkSimdDouble64Parameter a)
{
	setMul( *this, a );
}

HK_FORCE_INLINE void hkSimdDouble64::addMul(hkSimdDouble64Parameter a, hkSimdDouble64Parameter b)
{
	setAddMul( *this, a, b );
}
HK_FORCE_INLINE void hkSimdDouble64::subMul(hkSimdDouble64Parameter a, hkSimdDouble64Parameter b)
{
	setSubMul( *this, a, b );
}

HK_FORCE_INLINE void hkSimdDouble64::setInterpolate( hkSimdDouble64Parameter a, hkSimdDouble64Parameter b, hkSimdDouble64Parameter t )
{
	const hkSimdDouble64 bminusA = b-a;
	setAddMul( a, t, bminusA );
}

template <int N> 
HK_FORCE_INLINE void hkSimdDouble64::setDot( hkVector4dParameter a, hkVector4dParameter b )
{
	*this = a.dot<N>(b);
}

HK_FORCE_INLINE bool hkSimdDouble64::approxEqual(hkSimdDouble64Parameter v, hkSimdDouble64Parameter epsilon) const
{
	hkSimdDouble64 t; t.setAbs(*this - v);
	return t.isLess(epsilon);
}

HK_FORCE_INLINE void hkSimdDouble64::setClamped( hkSimdDouble64Parameter a, hkSimdDouble64Parameter minVal, hkSimdDouble64Parameter maxVal )
{
	// This ensures that if a is NAN, clamped will be maxVal afterwards	
	const hkVector4dComparison maxValGtA = maxVal.greater(a);
	hkSimdDouble64 clamped; clamped.setSelect(maxValGtA, a, maxVal);
	setMax(minVal, clamped);
}

//
//	Returns the reciprocal value of self.
//	Accuracy: 23 bit, divide-by-0 not checked

HK_FORCE_INLINE const hkSimdDouble64 hkSimdDouble64::reciprocal() const
{
	hkSimdDouble64 r;
	r.setReciprocal(*this);
	return r;
}

#ifndef HK_DISABLE_OLD_VECTOR4_INTERFACE

//
// old interface
//
HK_FORCE_INLINE hkVector4dComparison hkSimdDouble64::isNegative() const { return signBitSet(); }
HK_FORCE_INLINE hkVector4dComparison hkSimdDouble64::isPositive() const { return signBitClear(); }
HK_FORCE_INLINE hkBool32 hkSimdDouble64::isZero() const { return isEqualZero(); }
HK_FORCE_INLINE hkVector4dComparison hkSimdDouble64::compareLessThanZero() const { return lessZero(); }
HK_FORCE_INLINE hkVector4dComparison hkSimdDouble64::compareGreaterThanZero() const { return greaterZero(); }
HK_FORCE_INLINE hkVector4dComparison hkSimdDouble64::compareLessThan(hkSimdDouble64Parameter a) const { return less(a); }
HK_FORCE_INLINE hkVector4dComparison hkSimdDouble64::compareLessThanEqual(hkSimdDouble64Parameter a) const { return lessEqual(a); }
HK_FORCE_INLINE hkVector4dComparison hkSimdDouble64::compareGreaterThan(hkSimdDouble64Parameter a) const { return greater(a); }
HK_FORCE_INLINE hkVector4dComparison hkSimdDouble64::compareGreaterThanEqual(hkSimdDouble64Parameter a) const { return greaterEqual(a); }

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
