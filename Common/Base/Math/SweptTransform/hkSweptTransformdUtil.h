/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_MATH_SWEPT_TRANSFORMd_UTIL_H
#define HK_MATH_SWEPT_TRANSFORMd_UTIL_H

#include <Common/Base/Types/Physics/MotionState/hkMotionState.h>
#include <Common/Base/Types/Physics/hkStepInfo.h>

	/// A set of useful functions changing a hkMotionState or a SweptTransform
namespace hkSweptTransformUtil
{
			/// inline version of lerp2
		HK_FORCE_INLINE void HK_CALL _lerp2( const hkSweptTransformd& sweptTrans, hkDouble64 t, hkQuaterniond& quatOut );
		HK_FORCE_INLINE void HK_CALL _lerp2( const hkSweptTransformd& sweptTrans, hkSimdDouble64Parameter t, hkQuaterniond& quatOut );

			/// inline version of lerp2
		HK_FORCE_INLINE void HK_CALL _lerp2( const hkSweptTransformd& sweptTrans, hkDouble64 t, hkTransformd& transformOut );
		HK_FORCE_INLINE void HK_CALL _lerp2( const hkSweptTransformd& sweptTrans, hkSimdDouble64Parameter t, hkTransformd& transformOut );

			/// approximate a transform given an interpolation time
		void HK_CALL lerp2( const hkSweptTransformd& sweptTrans, hkTime time, hkTransformd& transformOut );
		void HK_CALL lerp2( const hkSweptTransformd& sweptTrans, hkSimdDouble64Parameter time, hkTransformd& transformOut );

			// internal function: approximate a transform given an interpolation time with a higher accuracy time input
		void HK_CALL lerp2Ha( const hkSweptTransformd& sweptTrans, hkTime t, hkDouble64 tAddOn, hkTransformd& transformOut );
		void HK_CALL lerp2Ha( const hkSweptTransformd& sweptTrans, hkSimdDouble64Parameter t, hkSimdDouble64Parameter tAddOn, hkTransformd& transformOut );

			/// approximate a transform given an interpolation value r between 0.0f and 1.0f.
			/// This uses an internal modified lerp (=linear interpolation of quaternion) functionality
		void HK_CALL lerp2Rel( const hkSweptTransformd& sweptTrans, hkDouble64 r, hkTransformd& transformOut );
		void HK_CALL lerp2Rel( const hkSweptTransformd& sweptTrans, hkSimdDouble64Parameter r, hkTransformd& transformOut );

			/// Calculate the transform at time0
		HK_FORCE_INLINE void HK_CALL calcTransAtT0( const hkSweptTransformd& sweptTrans, hkTransformd& transformOut );

			/// Calculate the transform at time1
		HK_FORCE_INLINE void HK_CALL calcTransAtT1( const hkSweptTransformd& sweptTrans, hkTransformd& transformOut );

#	if defined(HK_REAL_IS_DOUBLE)
			/// Sets the center of mass in local space.
			/// This does not change the position of the object, however it does change m_centerOfMass0 and m_centerOfMass1
		void HK_CALL setCentreOfRotationLocal( hkVector4dParameter newCenterOfRotation, hkMotionState& sweptTrans);

			/// Step the motion forward in time.
			///
			/// Notes:
			///    - The angular velocity is clipped to 0.9*pi*invDeltatime
		HK_FORCE_INLINE void HK_CALL _stepMotionState( const hkStepInfo& stepInfo, hkVector4d& linearVelocity, hkVector4d& angularVelocity, hkMotionState& motionState );

			/// clips the input velocities
		HK_FORCE_INLINE void HK_CALL _clipVelocities( const hkMotionState& motionState, hkVector4d& linearVelocity, hkVector4d& angularVelocity );

			/// Allows you to integrate a motions state by not using velocities, but by specifying the next mass center position and rotation.
		void HK_CALL keyframeMotionState( const hkStepInfo& stepInfo, hkVector4dParameter pos1, hkQuaterniondParameter rot1, hkMotionState& motionState );

			/// Gets the mass center at a given time t.
		HK_FORCE_INLINE void HK_CALL calcCenterOfMassAt( const hkMotionState& ms, hkTime t, hkVector4d& centerOut );
		HK_FORCE_INLINE void HK_CALL calcCenterOfMassAt( const hkMotionState& ms, hkSimdDouble64Parameter t, hkVector4d& centerOut );

			/// Return the velocity which was used to integrate the motion state from state 0 to state 1
		HK_FORCE_INLINE void HK_CALL getVelocity( const hkMotionState& ms, hkVector4d& linearVelOut, hkVector4d& angularVelOut );

			// interpolates the information of t1 to be at time t.
		void HK_CALL backStepMotionState( hkTime t, hkMotionState& motionState );
		void HK_CALL backStepMotionState( hkSimdDouble64Parameter t, hkMotionState& motionState );

			// Internal function. Only used upon deactivation of entities
		void HK_CALL freezeMotionState( hkTime time, hkMotionState& motionState );
		void HK_CALL freezeMotionState( hkSimdDouble64Parameter time, hkMotionState& motionState );

			// Call this if you deactivate a body (otherwise numerical problems can result in strange extrapolation of body movement)
		HK_FORCE_INLINE void HK_CALL deactivate( hkMotionState& ms );
			
			// Internal function. Only used upon activation of entities 
		void HK_CALL setTimeInformation( hkTime startTime, hkDouble64 invDeltaTime, hkMotionState& motionState);
		void HK_CALL setTimeInformation( hkSimdDouble64Parameter startTime, hkSimdDouble64Parameter invDeltaTime, hkMotionState& motionState);

			/// Warp the geometry center of both frames to position
		void HK_CALL warpToPosition( hkVector4dParameter position, hkMotionState& ms );

			/// Warp the orientation of both frames to rotations. Note: This changes the m_centerOfMass
		void HK_CALL warpToRotation( hkQuaterniondParameter rotation, hkMotionState& ms );

			/// Warp to position and orientation
		void HK_CALL warpTo( hkVector4dParameter position, hkQuaterniondParameter rotation, hkMotionState& ms );

			/// Warp to a new transform (includes both frames)
		void HK_CALL warpTo( const hkTransformd& transform, hkMotionState& ms );

			// For a given delta time: Calc the relative linear movement (xyz) and the worst case angular movment (w)
		HK_FORCE_INLINE void HK_CALL calcTimInfo( const hkMotionState& ms0, const hkMotionState& ms1, hkDouble64 deltaTime, hkVector4d& timOut);

			// calc the relative angular movement for a reduced step
		HK_FORCE_INLINE void HK_CALL calcAngularTimInfo( const hkMotionState& ms0, const hkMotionState& ms1, hkDouble64 deltaTime, hkVector4d* deltaAngleOut0, hkVector4d* deltaAngleOut1 );
#endif // #	if defined(HK_REAL_IS_DOUBLE)

		extern const hkQuadDouble64 _stepMotionStateMaxVeld; 
}

#include <Common/Base/Math/SweptTransform/hkSweptTransformdUtil.inl>


#endif // HK_MATH_SWEPT_TRANSFORMd_UTIL_H

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
