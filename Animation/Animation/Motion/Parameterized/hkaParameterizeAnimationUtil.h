/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKA_PARAMETERIZE_ANIMATION_UTIL_H
#define HKA_PARAMETERIZE_ANIMATION_UTIL_H

#include <Animation/Animation/Motion/Default/hkaDefaultAnimatedReferenceFrame.h>


class hkaAnimatedReferenceFrame;

	/// A collection of utility methods that parameterize an animation or 
	/// animation reference frame.
class hkaParameterizeAnimationUtil
{
	public:
			/// Samples the reference frame at the specified time in order  to extract the root transform at that time.
		static hkQsTransform HK_CALL sampleReferenceFrame( hkReal sampleTime, const hkQsTransform* t, int numT, hkReal duration );

			/// Projects the transform and extracts its motion that began in the specified root position
		static void HK_CALL project( const hkaDefaultAnimatedReferenceFrame::MotionExtractionOptions& options, const hkQsTransform& rootMotion, hkQsTransform& projectionOut );

			/// Computes the linear speed of the reference frame.  Assumes that the reference frame is moving 
			/// in a straight line.
		static void HK_CALL computeLinearSpeed( const hkaAnimatedReferenceFrame* referenceFrame, hkReal& linearSpeedOut );

			/// Computes the direction of the reference frame in radians around up.
		static void HK_CALL computeLinearDirection( const hkaAnimatedReferenceFrame* referenceFrame, const hkVector4& forwardAxis, const hkVector4& upAxis, hkReal& linearDirectionOut );

			/// Computes the movement displacement in the specified reference frame
		static void HK_CALL computeMovementDisplacement( const hkaAnimatedReferenceFrame* referenceFrame, hkVector4Parameter rotationAxis, hkVector4& outDirection );

			/// Fits the motion in the reference frame to a circle.  The speed of the motion around the circle 
			/// is returned in linearSpeedOut while the turn speed is returned in angularSpeedOut.
		static hkBool HK_CALL computeTurnParameters( const hkaAnimatedReferenceFrame* referenceFrame, const hkReal sampleRate, const hkVector4& sideAxis, const hkVector4& forwardAxis, const hkVector4& upAxis, hkReal& outRotationAngle, hkReal& outRadius, hkVector4& outRadiusDir );

			/// Computes the turning speed based on the parameters of a turn returned by one of the 'computeTurnParameters' method
		static void HK_CALL computeTurnSpeed(  hkReal rotationAngle, hkReal radius, hkReal duration, hkReal& outLinearSpeed, hkReal& outAngularSpeed );

		
	protected:

			/// Fits a circle to points.  The center of the circle is returned in centerOut and the radius in 
			/// radiusOut.  If a circle could not be fit HK_FAILURE is returned.
		static hkResult HK_CALL fitCircle(const hkVector4* points, int numPoints, const hkVector4& sideAxis, const hkVector4& forwardAxis, hkVector4& centerOut, hkReal& radiusOut);

			/// Projects pointIn onto the circle defined by center and radius.  The result is stored in pointOut.
		static void HK_CALL projectPointOntoCircle(const hkVector4& pointIn, const hkVector4& center, const hkReal radius, hkVector4& pointOut );

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
