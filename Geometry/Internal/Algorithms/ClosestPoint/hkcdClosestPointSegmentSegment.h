/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#ifndef	HKCD_CLOSEST_POINT_SEGMENT_SEGMENT
#define HKCD_CLOSEST_POINT_SEGMENT_SEGMENT


	/// Computes the closest points pair between two line segments and as segment fractions t,u of the inputs.
	/// Each segment is given by its starting point and its direction.
	/// The closest point on the first line is A+tOut*dA and the closest point on the second line is B+uOut*dB.
	/// You can check if the closest point is an endpoint by comparing the t and u values against 0 and 1.
HK_FORCE_INLINE void hkcdClosestPointSegmentSegment(hkVector4Parameter A, hkVector4Parameter dA, hkVector4Parameter B, hkVector4Parameter dB, 
													 hkSimdReal& tOut, hkSimdReal& uOut);

	/// Compute and return the closest points and distance between two segments.
	/// The return value contains is a mask indicating which endpoints, if any, of the line
	/// are not part of the closest distance. MASK_X and MASK_Y correspond to the start and end point
	/// of the first segment respectively. Similarly MASK_Z and MASK_W correspond to the start and end
	/// of the second segment.
HK_FORCE_INLINE hkVector4Comparison hkcdClosestPointSegmentSegment(hkVector4Parameter A, hkVector4Parameter dA, hkVector4Parameter B, hkVector4Parameter dB, 
													 hkVector4& closestPointB, hkVector4& closestAminusClosestB, hkSimdReal& squareDistanceOut);

#include <Geometry/Internal/Algorithms/ClosestPoint/hkcdClosestPointSegmentSegment.inl>

#endif // HKCD_CLOSEST_POINT_SEGMENT_SEGMENT

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
