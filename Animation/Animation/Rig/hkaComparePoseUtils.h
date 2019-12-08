/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKA_COMPARE_POSE_UTILS_H
#define HKA_COMPARE_POSE_UTILS_H

class hkaSkeleton;
class hkaInterleavedUncompressedAnimation;

	/// Utility used to compare the error between two poses
class hkaComparePoseUtils
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_EXPORT, hkaComparePoseUtils);

			/// Stores the input parameters used to compare two poses
		struct PoseComparisonInput
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_ANIMATION, PoseComparisonInput);

				/// Sets default values
			PoseComparisonInput();

				/// Skeleton of the animation
			const hkaSkeleton* m_skeleton;
				/// The animation to compare
			const hkaInterleavedUncompressedAnimation* m_animation;

				/// The time of pose a
			hkReal m_localTimePoseA;
				/// The time of pose b
			hkReal m_localTimePoseB;

				/// The amount of time to search ahead when computing velocity and acceleration.
			hkReal m_lookAheadDuration;

				/// Amount to scale differences in root velocity
			hkReal m_rootVelocityWeight;
				/// Amount to scale differences in root acceleration
			hkReal m_rootAccelerationWeight;
				/// Amount to scale differences in bone position.  Note bone positions are already weighted based 
				/// on bone length.  So smaller bones are less important.
			hkReal m_bonePositionWeight;

				/// Amount to weight duration.  Higher values will prefer longer loops, lower values will prefer 
				/// shorter loops.  After computing the error for the pose it is divided 
				/// by (m_localTimePoseB - m_localTimePoseA) ^ m_durationWeight.
			hkReal m_durationWeight;

		};
			/// Stores the result of comparing two poses
		struct PoseComparisonOutput
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_ANIMATION, PoseComparisonOutput);

				/// The time in the animation of pose a
			hkReal m_localTimePoseA;
				/// The time in the animation of pose b
			hkReal m_localTimePoseB;
				/// The error between pose a and b
			hkReal m_error;

				/// Sorts the comparison
			static bool HK_CALL sort( PoseComparisonOutput& a, PoseComparisonOutput& b )
			{
				return a.m_error < b.m_error;
			}
		};

			/// Computes the error between two poses in model space.
		static void HK_CALL compare( const PoseComparisonInput& input, PoseComparisonOutput& output );

	protected:

			/// Samples the pose, velocity and acceleration at local time.
		static void HK_CALL samplePose( const PoseComparisonInput& input, hkReal localTime, hkQsTransform* poseOut, hkReal& rootVelocityOut, hkReal& rootAccelerationOut );

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
