/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#ifndef	HKCD_CONVEX_HULL_QUAD_2D_H
#define HKCD_CONVEX_HULL_QUAD_2D_H

/// Computes the 2D convex hull of the 4 given vertices. The vertices are assumed to lie into the same plane. Returns the indices of the vertices on the convex hull
/// in remapOut.
HK_FORCE_INLINE void HK_CALL hkcdConvexHullQuad2d(const hkVector4* HK_RESTRICT srcVertsIn, int remapOut[4]);

#include <Geometry/Internal/Algorithms/ConvexHull/hkcdConvexHullQuad2d.inl>

#endif	//	HKCD_CONVEX_HULL_QUAD_2D_H

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
