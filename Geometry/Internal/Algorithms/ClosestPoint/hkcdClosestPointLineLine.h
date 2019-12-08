/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#ifndef	HKCD_CLOSEST_POINT_LINE_LINE
#define HKCD_CLOSEST_POINT_LINE_LINE

#include <Common/Base/Math/Vector/hkFourTransposedPoints.h>

	/// Computes the closest points pair between two infinite lines and returns the parameters t,u of the closest point.
	/// If the lines are parallel, false is returned and t is arbitrarily set to 1.
	/// Each line is given by its starting point and its direction.
	/// The closest point on the first line is A+tOut*dA and the closest point on the second line is B+uOut*dB.
HK_FORCE_INLINE hkBool32 hkcdClosestPointLineLine(hkVector4Parameter A, hkVector4Parameter dA, hkVector4Parameter B, hkVector4Parameter dB, 
												hkSimdReal& t, hkSimdReal& u);

	/// Batch version of infinite line closest check.
HK_FORCE_INLINE void hkcdClosestPointLineLine(const hkFourTransposedPoints& A, const hkFourTransposedPoints& dA, hkVector4Parameter B, hkVector4Parameter dB, 
											   hkVector4& t, hkVector4& u);

#include <Geometry/Internal/Algorithms/ClosestPoint/hkcdClosestPointLineLine.inl>

#endif // HKCD_CLOSEST_POINT_LINE_LINE

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
