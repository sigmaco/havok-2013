/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#ifndef	HKCD_SUPPORTING_VERTEX_H
#define HKCD_SUPPORTING_VERTEX_H

#include <Common/Base/Math/Vector/hkIntVector.h>
#include <Common/Base/Math/Vector/hkFourTransposedPoints.h>
#include <Geometry/Internal/Types/hkcdVertex.h>

	/// Returns the furthest vertex in the given direction.
	/// Usually vertices will have their index stored in the w component, so both the vertexOut contains both the point and index in the w component.
	/// The numberVertices must be a multiple of 4, dupicate the last one if necessary.
HK_FORCE_INLINE void HK_CALL hkcdSupportingVertexPoints(const hkcdVertex* HK_RESTRICT vertices, int numVertices, hkVector4Parameter direction, hkcdVertex* HK_RESTRICT vertexOut);

	/// Run two get supporting vertex calls in parallel.
HK_FORCE_INLINE void HK_CALL hkcdSupportingVertexPoints2(
	const hkcdVertex* HK_RESTRICT verticesA, int numVerticesA,
	const hkcdVertex* HK_RESTRICT verticesB, int numVerticesB,
	hkVector4Parameter directionInA, const hkTransform& aTb,
	hkcdVertex* HK_RESTRICT vertexAinAOut,
	hkcdVertex* HK_RESTRICT vertexBinBOut,
	hkVector4* HK_RESTRICT vertexBinAOut );

	/// Returns the furthest vertex in the given direction.
	/// The vertexOut contains both the point and index in the w component.
HK_FORCE_INLINE void HK_CALL hkcdSupportingVertexPoints(const hkFourTransposedPoints* HK_RESTRICT transposedVertices, int numTransposedVertices, hkVector4Parameter direction, hkcdVertex* HK_RESTRICT vertexOut);

#include <Geometry/Internal/Algorithms/SupportingVertex/hkcdSupportingVertex.inl>

#endif // HKCD_SUPPORTING_VERTEX_H

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
