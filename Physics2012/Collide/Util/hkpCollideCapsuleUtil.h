/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_COLLIDE2_COLLIDE_CAPSULE_UTIL_H
#define HK_COLLIDE2_COLLIDE_CAPSULE_UTIL_H

#include <Physics2012/Collide/Util/hkpCollideTriangleUtil.h>
#include <Common/Base/Algorithm/Collide/LineSegment/hkLineSegmentUtil.h>



hkResult HK_CALL hkCollideCapsuleUtilClostestPointCapsVsCaps( const  hkVector4* capsA, const hkReal& capsARadius, const hkVector4* capsB, const hkReal& capsBRadius,	hkReal collisionTolerance, hkContactPoint& pointOut);

/// Returns a maximum of three closest points (only if searchManifold is set to true).
/// The shortest point is always one of the first two points.
/// \param featureOutput if non-null, it should point to an array of three FeatureOutputs to which feature information about the collision will be written.
void hkCollideCapsuleUtilCapsVsTri( const  hkVector4* capsAPoints, hkReal capsARadius, const hkVector4* triVertices, hkReal triBRadius,
	const hkpCollideTriangleUtil::PointTriangleDistanceCache& cache, hkReal collisionTolerance, int searchManifold, hkContactPoint* points , hkpFeatureOutput* featuresOut = HK_NULL );


#endif // HK_COLLIDE2_COLLIDE_CAPSULE_UTIL_H

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
