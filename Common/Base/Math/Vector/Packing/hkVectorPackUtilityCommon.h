/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKMATH_VECTOR_PACK_UTILITY_COMMON_H
#define HKMATH_VECTOR_PACK_UTILITY_COMMON_H

namespace hkVectorPackUtility
{

#if defined HK_COMPILER_MSVC
//  warning C4723: potential divide by 0
#	pragma warning(push)
#	pragma warning(disable: 4723)
#endif

// If the bit set in n is also set in m, this function will return ts. Otherwise it will return 0.
// Note: the 'if' statement is a compile-time 'if' (not a runtime 'if').
HK_FORCE_INLINE hkUint32 filteredStoreToStream_calcOffset( hkUint32 n, const unsigned int ts, hkVector4ComparisonMask::Mask m )
{
	if ( n > ts )
	{
		return (m&n) / (n/ts);
	}
	else
	{
		return (m&n) * (ts/n);
	}
}


} // namespace hkVectorPackUtility

#endif // HKMATH_VECTOR_PACK_UTILITY_COMMON_H

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
