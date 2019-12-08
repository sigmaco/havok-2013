/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#ifndef	HKCD_INTERSECTIONS_RAY_SPHERE
#define HKCD_INTERSECTIONS_RAY_SPHERE

#include <Common/Base/Math/Vector/hkFourTransposedPoints.h>
#include <Geometry/Internal/Types/hkcdRay.h>


	//// Raycast against a sphere.
	/// See \ref RayCastDocumentation for common input and output parameter descriptions.
	/// \param[in] spherePosAndRadius	Sphere position and radius (stored in the w component)
	/// \note Limit cases:
	/// -	If the ray is completely contained inside the sphere there is no intersection unless the start lies 
	///		exactly on the sphere surface.
	/// -	If the ray start lies on the sphere surface and the end is not contained in the sphere there is no intersection
	///
	/// \sa hkcdRayBundleSphereIntersect for a version for multiple rays.
	HK_FORCE_INLINE	hkInt32 hkcdRayCastSphere(const hkcdRay& ray, 
												hkVector4Parameter spherePosAndRadius, 
												hkSimdReal* HK_RESTRICT hitFractionInOut,
												hkVector4* HK_RESTRICT normalOut,
												hkcdRayQueryFlags::Enum flags);




HK_FORCE_INLINE hkVector4Comparison hkcdRayBundleSphereIntersect(const hkcdRayBundle& rayBundle, hkSimdRealParameter sphereRadius, 
																 hkVector4& fractionsInOut, hkFourTransposedPoints& normalsOut);

#include <Geometry/Internal/Algorithms/RayCast/hkcdRayCastSphere.inl>

#endif // HKCD_INTERSECTIONS_RAY_SPHERE

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
