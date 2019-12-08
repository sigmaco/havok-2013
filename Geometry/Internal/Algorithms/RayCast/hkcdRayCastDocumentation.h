/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE


/// \page RayCastDocumentation Raycasting common documentation
/// This describes the common conventions of the hkcdRayCast* functions. Some functions have additional requirements/outputs which are detailed separately.
/// \section sec1 Return values
/// All functions return nonzero value on hit and zero on miss, and more detailed information can be extracted using hkcdRayCastResult.
/// \section sec2 Output parameters overwritten
/// Even in the case of a miss, output parameters such as hitFraction and normal may be written to with invalid values. It is the callers responsibility to save the originals, if needed.
/// \section sec3 Hit Fractions
/// Raycasts all take a hitFraction parameter. This value (between 0 and 1) defines a logical clip point along the ray. Intersections beyond this fraction are considered misses.
/// When a hit is successful, this fraction will be updated to the new intersection.
/// \section sec3 Normals
/// Upon hit, the surface normal is stored in as output.

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
