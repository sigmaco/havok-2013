/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_MATH_MX_MATH_TYPES_H
#define HK_MATH_MX_MATH_TYPES_H

// long vector types

#if defined(HK_COMPILER_HAS_INTRINSICS_IA32)

// storage type for hkMxVector
#if (HK_SSE_VERSION >= 0x50)
template <int M>
struct hkMxVectorfStorage
{
	__m256 v[(M+1)>>1];
};
#else
template <int M>
struct hkMxVectorfStorage
{
	hkVector4f v[M];
};
#endif

template <int M>
struct hkMxVectordStorage
{
	hkVector4d v[M];
};

// storage type for hkMxSingle
#if (HK_SSE_VERSION >= 0x50)
template <int M>
struct hkMxSinglefStorage
{
	__m256 s;
};
#else
template <int M>
struct hkMxSinglefStorage
{
	hkVector4f s;
};
#endif

template <int M>
struct hkMxSingledStorage
{
	hkVector4d s;
};

// storage type for hkMxReal
#if (HK_SSE_VERSION >= 0x50)
template <int M>
struct hkMxRealfStorage
{
	__m256 r[(M+1)>>1];
};
#else
template <int M>
struct hkMxRealfStorage
{
	hkSimdFloat32 r[M];
};
#endif

template <int M>
struct hkMxRealdStorage
{
	hkSimdDouble64 r[M];
};

// storage type for hkMxMask
#if (HK_SSE_VERSION >= 0x50)
template <int M>
struct hkMxMaskStorage
{
	__m256 c[(M+1)>>1];
};
#else
template <int M>
struct hkMxMaskfStorage
{
	hkVector4fComparison c[M];
};
#endif

template <int M>
struct hkMxMaskdStorage
{
	hkVector4dComparison c[M];
};


#else // !IA32


// storage type for hkMxVector
template <int M>
struct hkMxVectorfStorage
{
	hkVector4f v[M];
};

template <int M>
struct hkMxVectordStorage
{
	hkVector4d v[M];
};

// storage type for hkMxSingle
template <int M>
struct hkMxSinglefStorage
{
	hkVector4f s;
};

template <int M>
struct hkMxSingledStorage
{
	hkVector4d s;
};

// storage type for hkMxReal
template <int M>
struct hkMxRealfStorage
{
	hkSimdFloat32 r[M];
};

template <int M>
struct hkMxRealdStorage
{
	hkSimdDouble64 r[M];
};

// storage type for hkMxMask
template <int M>
struct hkMxMaskfStorage
{
	hkVector4fComparison c[M];
};

template <int M>
struct hkMxMaskdStorage
{
	hkVector4dComparison c[M];
};

#endif

// storage type for hkMxMask
template <int M>
struct hkMxHalf8Storage
{
	HK_ALIGN16( hkHalf h[M*8] );
};


#endif // HK_MATH_MX_MATH_TYPES_H

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
