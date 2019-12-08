/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKBASE_TRACKER_SNAPSHOT_H
#define HKBASE_TRACKER_SNAPSHOT_H

#include <Common/Base/Memory/Tracker/Default/hkDefaultMemoryTracker.h>
#include <Common/Base/Algorithm/Sort/hkSort.h>
#include <Common/Base/System/StackTracer/hkStackTracer.h>
#include <Common/Base/Memory/System/Util/hkMemorySnapshot.h>

struct hkSubString;
class hkMemorySystem;

    /// This class represents a snapshot of the current memory state using both
    /// the information coming from the memory system and from the memory tracker.
    /// While this class has dynamically allocated members (arrays), we cannot use
    /// the default allocators to allocate them since allocating and deallocating them
    /// will perturb the status of the memory system which we are trying to capture.
class hkTrackerSnapshot  
{
    public:

		//+hk.MemoryTracker(ignore=True)
        HK_DECLARE_PLACEMENT_ALLOCATOR();

		typedef hkDefaultMemoryTracker::ClassAlloc ClassAlloc;

			/// Initialize
		hkResult init(hkMemorySystem* memorySystem = HK_NULL, hkDefaultMemoryTracker* tracker = HK_NULL);

			/// Returns HK_SUCCESS if the data appears consistent
		hkResult checkConsistent() const;

			/// Find the class allocation at the address specified
		const ClassAlloc* findClassAllocation(const void* ptr) const;

			/// Find the allocation that contains the given class allocation.
			/// We assume that the member raw snapshot has already been sorted.
		const hkMemorySnapshot::Allocation* findAllocationForClassAllocation( const ClassAlloc& classAlloc ); 

			/// Get the class allocs (ordered by start pointer)
		const hkArrayBase<ClassAlloc>& getClassAllocs() const;

			/// Write access to class allocs. If the data is changed, a call to orderClassAllocs is needed
			/// for functionality such as findClassAllocation to work
		hkArrayBase<ClassAlloc>& getClassAllocs();

			/// Order class allocs. The classAllocs must be ordered for findClassAllocation to work. Generally
			/// it is - but getClassAllocs can be used to modify allocs. If that happens, call
			/// orderClassAllocs to fix up the order.
		void orderClassAllocs();

		const hkMemorySnapshot& getRawSnapshot() const { return m_rawSnapshot; }

			/// Swap
		void swap(hkTrackerSnapshot& rhs);

			/// Get the memory statistics dump obtained from the memory system
			/// When we take a tracker snapshot, the memory system statistics will
			/// be dumped and stored in the snapshot for future usage (by the Memory
			/// Analyzer for instance).
			/// The returned pointer will be valid until the hkTrackerSnapshot instance
			/// is destroyed.
		const char* getMemorySystemStatistics() const;

			/// ==
		hkBool operator==(const hkTrackerSnapshot& rhs) const;
			/// !=
		hkBool operator!=(const hkTrackerSnapshot& rhs) const;

			/// Ctor, using malloc
		hkTrackerSnapshot();
		hkTrackerSnapshot(hkMemoryAllocator* mem);
			/// Copy ctor
		hkTrackerSnapshot(const hkTrackerSnapshot& rhs);
			/// Dtor
		~hkTrackerSnapshot();

    protected:
	

		hkMemoryAllocator* m_mem;
		hkArrayBase<ClassAlloc> m_classAllocations;
		hkMemorySnapshot m_rawSnapshot;

		hkArrayBase<char> m_memSysStatistics;
};

#include <Common/Base/Memory/Tracker/ScanCalculator/hkTrackerSnapshot.inl>

#endif // HKBASE_TRACKER_SNAPSHOT_H

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
