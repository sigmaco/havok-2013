/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKA_COMPRESSION_H
#define HKA_COMPRESSION_H

#include <Common/Base/hkBase.h>

/// Internal utilities for animation compression.
class hkaCompression
{
public:

		/*
		 *	Quaternion 32 bit compression
		 */

		/// Computes a NURBS curve that approximates the input data.
	static void HK_CALL approximateNURBSCurve(
		int numSamples, const hkReal *sampleTimes, const hkVector4 *sampleData,
		int degree, hkReal tolerance,
		int *numKnotsOut, hkReal *knotsOut,
		int *numPointsOut, hkVector4 *pointsOut );

	/// Compute offsets into packed NURBS data.
	static const hkUint8* HK_CALL computePackedNurbsOffsets( const hkUint8* base, const hkUint32* p, hkUint32 o2, hkUint32 o3 );

	/// hkaQuantizedAnimation utility.
	static void HK_CALL sampleDynamicScalarsInternal( hkReal* poseOut, int numPoseOut, const hkUint16* elements, const hkReal* minimums, const hkReal* spans, const hkUint16* values, int n );
};


#endif

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
