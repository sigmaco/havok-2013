/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#ifndef HKCD_INTERNAL_GSK_H
#define HKCD_INTERNAL_GSK_H

#include <Geometry/Internal/Types/hkcdVertex.h>
#include <Geometry/Internal/Algorithms/Gsk/hkcdGskData.h>

class hkFourTransposedPoints;

	/// See hkGskData.h for the input & output structures used here.
namespace hkcdGsk
{
		/// Get closest point with penetration.
	GetClosestPointStatus HK_CALL getClosestPoint(
		const hkcdVertex* vertsA, int numVertsA,
		const hkcdVertex* shapeB, int numVertsB,
		const GetClosestPointInput& input, Cache* HK_RESTRICT cache, GetClosestPointOutput& output );

		/// Linear cast.
	hkBool HK_CALL linearCast(
		const hkcdVertex* vertsShape, int numVertsShape,
		const hkcdVertex* vertsCast, int numVertsCast,
		const LinearCastInput& input, Cache* HK_RESTRICT cache, LinearCastOutput& output );

		/// Ray cast.
	hkBool HK_CALL rayCast(
		const hkcdVertex* verts, int numVerts,
		const RayCastInput& input, RayCastOutput& output );

		/// Ray cast transposed points.
	hkBool HK_CALL rayCast(
		const hkFourTransposedPoints* verts, int numUnTransposed,
		const RayCastInput& input, RayCastOutput& output );
}

#endif // HKCD_INTERNAL_GSK_H

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
