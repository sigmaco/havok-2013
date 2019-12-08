/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKA_PARAMETRIC_ANIMATION_EXTRAPOLATION_UTIL_H
#define HKA_PARAMETRIC_ANIMATION_EXTRAPOLATION_UTIL_H


/// A utility class for calculating animation extrapolation parameters for a triangulated parametric motion space.
class hkaParametricAnimationExtrapolationUtil
{
	public:
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_ANIMATION, hkaParametricAnimationExtrapolationUtil );

			/// Calculates the values required by the 'extrapolateTransform' method:
			/// positions of two points in the motion space from which we'll extract the transforms that will serve as an extrapolation basis
			/// extrapolation distance.
			///
			/// The edge vertices should be specified in the winding order.
		static int HK_CALL calculateExtrapolationParams( const hkVector4* inArrVtxPosInMotionSpace, hkVector4Parameter inExtrapolatedPosition, hkVector4* outArrSamplePoints, hkReal& outExtrapolationDistance );

			/// The method extrapolates a transform located outside the specified triangle. 
		static void HK_CALL extrapolateTransform( const hkQsTransform& inStartVtxTransform, const hkQsTransform& inEndVtxTransform, hkReal dist, hkQsTransform& outTransform );

	private:
			/// Extrapolates two vectors
		static void HK_CALL extrapolateVector( hkVector4Parameter inStartVec, hkVector4Parameter inEndVec, hkReal dist, hkVector4& outVector );

			/// Extrapolates two quaternions
		static void HK_CALL extrapolateQuaternion( const hkQuaternion& inStartQuat, const hkQuaternion& inEndQuat, hkReal dist, hkQuaternion& outQuaternion );

			/// Calculates the intersection point of 2 rays in 2 dimensions (we're assuming they are coplanar and that their first 2 coordinates
			/// express the position on the plane they both share).
		static void HK_CALL intersectRays2D( const hkVector4* inArrayRayPoints, hkVector4& outIntersectionPoint );
};

#endif // HKA_PARAMETRIC_ANIMATION_EXTRAPOLATION_UTIL_H

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
