/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKANIMATION_RIG_HKSKELETON_HKCLASS_H
#define HKANIMATION_RIG_HKSKELETON_HKCLASS_H

#include <Common/Base/Types/Geometry/LocalFrame/hkLocalFrame.h>
#include <Animation/Animation/Rig/hkaBone.h>

extern const class hkClass hkaSkeletonLocalFrameOnBoneClass;

/// hkaSkeleton meta information
extern const class hkClass hkaSkeletonClass;

/// The class that represents a combination of a character rig and arbitrary float data.
/// The bone/transform data is designed to represent a skeletal animation rig - bone(transform) names, hierarchy and reference pose.
/// The float slot data is designed to store arbitrary floating point data.
///
/// Either bones or float slots may be empty (but not both). For example:
///     - A character rig might have only bones.
///     - A character rig with auxiliary animated data might have both bones and float slots.
///     - A morph target 'rig' might have only float slots.
///
/// Note that size of m_bones.getSize()==m_parentIndices.getSize()==m_referencePose.getSize().
class hkaSkeleton: public hkReferencedObject
{
	public:

		//+version(5)
		//+vtable(true)

		HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_ANIM_RIG );
		HK_DECLARE_REFLECTION();

			/// A local frame and the index of the bone it is attached to.
		struct LocalFrameOnBone
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_ANIM_RIG, LocalFrameOnBone );
			HK_DECLARE_REFLECTION();

				/// The local frame attached to a bone.
			hkRefPtr<hkLocalFrame> m_localFrame;

				/// The index of the bone that the frame is attached to.
			hkInt16 m_boneIndex;

			HK_FORCE_INLINE LocalFrameOnBone();
			HK_FORCE_INLINE LocalFrameOnBone( hkFinishLoadedObjectFlag f );
		};

			/// A sequence of contiguous bones in the skeleton.
		struct Partition
		{
         //+version(1)
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_ANIM_RIG, Partition );
			HK_DECLARE_REFLECTION();

			Partition() : m_name(HK_NULL), m_startBoneIndex(-1), m_numBones(-1){}

			Partition(hkInt16 startIndex, hkInt16 numBones) : m_name(HK_NULL), m_startBoneIndex(startIndex), m_numBones(numBones){}

			Partition( hkFinishLoadedObjectFlag f ) : m_name(f) {}

			Partition(const Partition& partition) : m_name(partition.m_name), m_startBoneIndex(partition.m_startBoneIndex), m_numBones(partition.m_numBones){}

			hkStringPtr m_name;
			hkInt16 m_startBoneIndex;
			hkInt16 m_numBones;

				/// initialize the partition
			HK_FORCE_INLINE void initWithoutName( hkInt16 startBoneIndex, hkInt16 numBones );

				/// Returns true if the partition contains the specified bone.
			HK_FORCE_INLINE hkBool32 isBonePresentWithinPartition( hkInt16 boneIndex ) const;

				/// Get the end bone index of the partition
			HK_FORCE_INLINE hkInt16 getEndBoneIndex() const;
		};

		class PartitionStartBoneLess
		{
		public:

			HK_FORCE_INLINE hkBool operator() ( const Partition& a, const Partition& b )
			{
				return ( a.m_startBoneIndex < b.m_startBoneIndex );
			}
		};

			/// A constructor for null initialization
		HK_FORCE_INLINE hkaSkeleton();

			/// Copy the given skeleton into this one.
		HK_FORCE_INLINE hkaSkeleton( const hkaSkeleton& skel );

			/// Get the local frame that is attached to a bone. Returns HK_NULL if there isn't one.
		hkLocalFrame* getLocalFrameForBone( int boneIndex ) const;

			/// Get the partition index from the partition name. 
		hkInt16 getPartitionIndexFromName( const char* partitionName ) const;

			/// Get the partition index to which this bone belongs to.
		hkInt16 getPartitionIndexForBone( hkInt16 boneIndex ) const;

		//
		// Members
		//

			/// A user name to aid in identifying the skeleton
		hkStringPtr m_name;

			/// Parent relationship
		hkArray<hkInt16> m_parentIndices;

			/// Bones for this skeleton
		hkArray<class hkaBone> m_bones;

			/// The reference pose for the bones of this skeleton. This pose is stored in local space.
		hkArray<hkQsTransform> m_referencePose;

			/// The reference values for the float slots of this skeleton. This pose is stored in local space.
		hkArray<hkReal> m_referenceFloats;

			/// Floating point track slots. Often used for auxiliary float data or morph target parameters etc.
			/// This defines the target when binding animations to a particular rig.
		hkArray<hkStringPtr> m_floatSlots;

			/// The local frames that are attached to the bones of this skeleton. These must be ordered
			/// in order of increasing bone index.
		hkArray<struct LocalFrameOnBone> m_localFrames;

			/// A set of partitions of the skeleton.
		hkArray<struct Partition> m_partitions;

			// Constructor for initialisation of vtable fixup
		HK_FORCE_INLINE hkaSkeleton( hkFinishLoadedObjectFlag f );

};

#include <Animation/Animation/Rig/hkaSkeleton.inl>

#endif // HKANIMATION_RIG_HKSKELETON_HKCLASS_H

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
