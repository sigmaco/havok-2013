/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_MATH_FPU_FLOAT_MATH_TYPES_H
#define HK_MATH_FPU_FLOAT_MATH_TYPES_H

// no special includes necessary

#define HK_TRANSPOSEf_SWAP(a,b) __tmp = a; a = b; b = __tmp


// transpose 4 hkVector4
#define HK_TRANSPOSE4f(v0,v1,v2,v3) { hkFloat32 __tmp; \
	HK_TRANSPOSEf_SWAP( v0(1), v1(0) ); \
	HK_TRANSPOSEf_SWAP( v0(2), v2(0) ); \
	HK_TRANSPOSEf_SWAP( v0(3), v3(0) ); \
	HK_TRANSPOSEf_SWAP( v1(2), v2(1) ); \
	HK_TRANSPOSEf_SWAP( v1(3), v3(1) ); \
	HK_TRANSPOSEf_SWAP( v2(3), v3(2) ); }

// transpose 3 hkVector4: w component is undefined
#define HK_TRANSPOSE3f(v0,v1,v2) { hkFloat32 __tmp; \
	HK_TRANSPOSEf_SWAP( v0(1), v1(0) ); \
	HK_TRANSPOSEf_SWAP( v0(2), v2(0) ); \
	HK_TRANSPOSEf_SWAP( v1(2), v2(1) ); }


// storage type for hkVector4 (and thus hkQuaternion)
struct hkQuadFloat32
{
	HK_ALIGN_FLOAT( hkFloat32 v[4] );
};
#define HK_MATH_VECTORf_IS_NOT_SIMD

// storage type for hkSimdReal
typedef hkFloat32 hkSingleFloat32;

// storage type for hkVector4Comparison
typedef hkInt32 hkVector4fMask;


// argument types
class hkVector4f;
typedef const hkVector4f& hkVector4fParameter;

class hkSimdFloat32;
typedef const hkSimdFloat32& hkSimdFloat32Parameter;

class hkVector4fComparison;
typedef const hkVector4fComparison& hkVector4fComparisonParameter;

class hkQuaternionf;
typedef const hkQuaternionf& hkQuaternionfParameter;

// this causes problems for the optimizer, use for debug checks only
#define HK_QUADFLOAT_CONSTANT(a, b, c, d)	{{a,b,c,d}}


#endif // HK_MATH_FPU_FLOAT_MATH_TYPES_H

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
