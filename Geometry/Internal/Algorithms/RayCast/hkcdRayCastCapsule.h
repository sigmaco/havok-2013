/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#ifndef	HKCD_INTERSECTIONS_RAY_CAPSULE
#define	HKCD_INTERSECTIONS_RAY_CAPSULE

#include <Geometry/Internal/Types/hkcdRay.h>

	/// Hit type for hkcdRayCastCapsule
enum hkcdRayCastCapsuleHitType
{
	HK_CD_RAY_CAPSULE_NONE = 0,
	HK_CD_RAY_CAPSULE_CAP0,
	HK_CD_RAY_CAPSULE_CAP1,
	HK_CD_RAY_CAPSULE_BODY,
};


	/// Raycast against a capsule.
	/// See \ref RayCastDocumentation for common input and output parameter descriptions.
	/// \param[out] hitTypeOut the part of the capsule hit (the ends or cylindrical "body")
HK_FORCE_INLINE hkInt32 hkcdRayCastCapsule(const hkcdRay& ray,
											hkVector4Parameter vertex0,
											hkVector4Parameter vertex1,
											hkSimdRealParameter radius, 
											hkSimdReal* HK_RESTRICT fractionInOut,
											hkVector4* HK_RESTRICT normalOut,
											hkcdRayCastCapsuleHitType* HK_RESTRICT hitTypeOut,
											hkcdRayQueryFlags::Enum flags 
											);


	/// Bundle version or ray capsule intersection check.
HK_FORCE_INLINE hkVector4Comparison hkcdRayBundleCapsuleIntersect( const hkcdRayBundle& rayBundle,
																  hkVector4Parameter vertex0, hkVector4Parameter vertex1, hkSimdRealParameter radius, 
																  hkVector4& fractionsInOut, hkFourTransposedPoints& normalsOut );


	/// Bundle version of hkcdRayCastCapsule
//HK_FORCE_INLINE hkVector4Comparison hkcdRayCastBundleCapsule(
//	const hkcdRayBundle& rayBundle,
//	hkVector4Parameter vertex0, 
//	hkVector4Parameter vertex1,
//	hkSimdRealParameter radius, 
//	hkVector4* HK_RESTRICT fractionsInOut,
//	hkFourTransposedPoints* HK_RESTRICT normalsOut );

#include <Geometry/Internal/Algorithms/RayCast/hkcdRayCastCapsule.inl>

#endif // HKCD_INTERSECTIONS_RAY_CAPSULE

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
