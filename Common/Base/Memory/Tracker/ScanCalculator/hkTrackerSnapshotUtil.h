/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKBASE_TRACKER_SNAPSHOT_UTIL_H
#define HKBASE_TRACKER_SNAPSHOT_UTIL_H


class hkTrackerScanSnapshot;
class hkTrackerLayoutCalculator;
class hkTrackerSnapshot;

	/// Utility to capture a snapshot of allocations and their types.
	/// If using hkFreeListMemorySystem, before taking a snapshot it's recommended to release thread local memory caches.
	/// Otherwise you may see allocations with no type corresponding to freed memory in thread local freelists.
	/// hkThreadPool::gcThreadMemoryOnNextCompletion() provides an easy way to do this.
class hkTrackerSnapshotUtil
{
	//+reflected(false)
    public:
        HK_DECLARE_PLACEMENT_ALLOCATOR();

			/// Create a snapshot of the current memory state.
			/// A hkMallocAllocator is used to hold the snapshot.
		static hkTrackerScanSnapshot* HK_CALL createSnapshot();

			/// Create a snapshot of the current memory state.
			/// The given memory allocator is used for temporary storage of the snapshot and
			/// allocations through it must not change the state of the global hkMemorySystem.
		static hkTrackerScanSnapshot* HK_CALL createSnapshot(hkMemoryAllocator* a);

			/// Using the snapshot and the passed in layout calculator, produce a snapshot.
			/// Passing in layoutCalc is HK_NULL will cause a default hkTrackerLayoutCalc to be created and used.
		static hkTrackerScanSnapshot* HK_CALL createSnapshot(const hkTrackerSnapshot& snapshot, hkTrackerLayoutCalculator* layoutCalc = HK_NULL);
};

#endif // HKBASE_TRACKER_SNAPSHOT_UTIL_H

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
