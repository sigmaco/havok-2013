/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKMATH_VECTOR2f_UTIL_H
#define HKMATH_VECTOR2f_UTIL_H

class hkVector2f;

namespace hkVector2Util
{
	hkBool HK_CALL edgesIntersect( const hkVector2f& a1, const hkVector2f& a2, const hkVector2f& b1, const hkVector2f& b2);
	void HK_CALL convexHullSimplePolyline( const hkArrayBase<hkVector2f>& polyline, hkArray<int>& indicesOut );
	void HK_CALL convexHullVertices( const hkArrayBase<hkVector2f>& points, hkArray<hkVector2f>& hullOut );
	hkResult HK_CALL convexHullIndices( const hkArrayBase<hkVector2f>& points, hkArrayBase<int>& indicesOut );

		/// Computes the center and axes of the OBB of the points, and returns the area.
		/// The hkResult is used to indicate that all memory allocations succeeded.
	hkFloat32 HK_CALL computeObb(const hkArrayBase<hkVector2f>& points, hkVector2f& centerOut, hkVector2f& e0Out, hkVector2f& e1Out, hkResult& resOut);

#ifdef HK_REAL_IS_FLOAT
	/// Helper to get the number of bytes allocated on stack for hull generation
	int  HK_CALL getStackSizeInBytesRequiredForConvexHullIndices(int inputPointsSize);
#endif
}

#endif //HKMATH_VECTOR2f_UTIL_H

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
