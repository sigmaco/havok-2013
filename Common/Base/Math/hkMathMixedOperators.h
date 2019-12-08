/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_MATH_MATH_MIXED_OPERATORS_H
#define HK_MATH_MATH_MIXED_OPERATORS_H

/// Old deprecated functions needed when using the old vector4 interface, do not use in new code.
#ifndef HK_DISABLE_OLD_VECTOR4_INTERFACE
#ifndef HK_DISABLE_MIXED_FLOAT_DOUBLE_OPERATORS

HK_FORCE_INLINE hkBool32 operator<( hkSimdDouble64Parameter a, hkSimdFloat32Parameter b)
{
	return hkBool32( hkFloat32(a.getReal()) < b.getReal() );
}

HK_FORCE_INLINE hkBool32 operator<( hkSimdFloat32Parameter a, hkSimdDouble64Parameter b)
{
	return hkBool32( a.getReal() < hkFloat32(b.getReal()) );
}

HK_FORCE_INLINE hkBool32 operator<( hkSimdDouble64Parameter a, hkFloat32 b)
{
	return hkBool32( hkFloat32(a.getReal()) < b );
}

HK_FORCE_INLINE hkBool32 operator<( hkSimdFloat32Parameter a, hkDouble64 b)
{
	return hkBool32( a.getReal() < hkFloat32(b) );
}

HK_FORCE_INLINE hkBool32 operator<( hkDouble64 a, hkSimdFloat32Parameter b)
{
	return hkBool32( hkFloat32(a) < b.getReal() );
}

HK_FORCE_INLINE hkBool32 operator<( hkFloat32 a, hkSimdDouble64Parameter b)
{
	return hkBool32( a < hkFloat32(b.getReal()) );
}

HK_FORCE_INLINE bool operator<=( hkSimdDouble64Parameter a, hkSimdFloat32Parameter b)
{
	return hkBool32( hkFloat32(a.getReal()) <= b.getReal() );
}

HK_FORCE_INLINE bool operator<=( hkSimdFloat32Parameter a, hkSimdDouble64Parameter b)
{
	return hkBool32( a.getReal() <= hkFloat32(b.getReal()) );
}

HK_FORCE_INLINE bool operator<=( hkSimdDouble64Parameter a, hkFloat32 b)
{
	return hkBool32( hkFloat32(a.getReal()) <= b );
}

HK_FORCE_INLINE bool operator<=( hkSimdFloat32Parameter a, hkDouble64 b)
{
	return hkBool32( a.getReal() <= hkFloat32(b) );
}

HK_FORCE_INLINE bool operator<=( hkDouble64 a, hkSimdFloat32Parameter b)
{
	return hkBool32( hkFloat32(a) <= b.getReal() );
}

HK_FORCE_INLINE bool operator<=( hkFloat32 a, hkSimdDouble64Parameter b)
{
	return hkBool32( a <= hkFloat32(b.getReal()) );
}


HK_FORCE_INLINE hkBool32 operator>( hkSimdDouble64Parameter a, hkSimdFloat32Parameter b)
{
	return hkBool32( hkFloat32(a.getReal()) > b.getReal() );
}

HK_FORCE_INLINE hkBool32 operator>( hkSimdFloat32Parameter a, hkSimdDouble64Parameter b)
{
	return hkBool32( a.getReal() > hkFloat32(b.getReal()) );
}

HK_FORCE_INLINE hkBool32 operator>( hkSimdDouble64Parameter a, hkFloat32 b)
{
	return hkBool32( hkFloat32(a.getReal()) > b );
}

HK_FORCE_INLINE hkBool32 operator>( hkSimdFloat32Parameter a, hkDouble64 b)
{
	return hkBool32( a.getReal() > hkFloat32(b) );
}

HK_FORCE_INLINE hkBool32 operator>( hkDouble64 a, hkSimdFloat32Parameter b)
{
	return hkBool32( hkFloat32(a) > b.getReal() );
}

HK_FORCE_INLINE hkBool32 operator>( hkFloat32 a, hkSimdDouble64Parameter b)
{
	return hkBool32( a > hkFloat32(b.getReal()) );
}

HK_FORCE_INLINE bool operator>=( hkSimdDouble64Parameter a, hkSimdFloat32Parameter b)
{
	return hkBool32( hkFloat32(a.getReal()) >= b.getReal() );
}

HK_FORCE_INLINE bool operator>=( hkSimdFloat32Parameter a, hkSimdDouble64Parameter b)
{
	return hkBool32( a.getReal() >= hkFloat32(b.getReal()) );
}

HK_FORCE_INLINE bool operator>=( hkSimdDouble64Parameter a, hkFloat32 b)
{
	return hkBool32( hkFloat32(a.getReal()) >= b );
}

HK_FORCE_INLINE bool operator>=( hkSimdFloat32Parameter a, hkDouble64 b)
{
	return hkBool32( a.getReal() >= hkFloat32(b) );
}

HK_FORCE_INLINE bool operator>=( hkDouble64 a, hkSimdFloat32Parameter b)
{
	return hkBool32( hkFloat32(a) >= b.getReal() );
}

HK_FORCE_INLINE bool operator>=( hkFloat32 a, hkSimdDouble64Parameter b)
{
	return hkBool32( a >= hkFloat32(b.getReal()) );
}



#endif // HK_DISABLE_MIXED_FLOAT_DOUBLE_OPERATORS
#endif // HK_DISABLE_OLD_VECTOR4_INTERFACE

#endif // HK_MATH_MATH_MIXED_OPERATORS_H

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
