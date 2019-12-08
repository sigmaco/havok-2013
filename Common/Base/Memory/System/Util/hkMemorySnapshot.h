/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_MEMORY_SNAPSHOT_H
#define HK_MEMORY_SNAPSHOT_H

#include <Common/Base/System/StackTracer/hkStackTracer.h>

/// BETA - A memory snapshot which shows all levels of hierarchical allocations.
///
/// A memory snapshot can be obtained by a supported memory system by using the
/// hkMemorySystem::getMemorySnapshot() call. The memory system is the only entity
/// that knows exactly how the allocator hierarchy being used is laid out, and it is
/// therefore its responsibility to fill the memory snapshot properly. Every allocation
/// contains the ID of the entity (provider) it comes from; a full snapshot should
/// always contain an allocation at every level in the allocator hierarchy for each
/// top-level allocation (down to the system allocator).
/// Assuming we have a plain allocator stack like the following one:
/// 
/// 1. System allocator
/// 2. Large block allocator
/// 3. Padded allocator
/// 4. Memory system
/// 
/// For every user allocation recorded in the memory system (level 4), we should 
/// have a corresponding allocation at level 3 (plus some overhead caused by the padding),
/// which should be contained in an allocation at level 2 (a large block also containing some
/// overhead eventually). And the large block should be obtained from the system allocator
/// itself (with unknown compiler- and OS-driven overhead).
/// Depending on the specific memory system, we might instead end up with an incomplete
/// allocation tree where, for instance, there is no level 3, 2 or 1 allocation containing
/// an allocation registered by the memory system. In this case we assume that at the
/// missing levels we have no overhead (they behave as simple pass-through allocators
/// for that specific allocation).
/// The memory snapshot doesn't need to be complete, but it should be as complete
/// as possible.
///
/// Generally, only allocations from the system heap should be reported; if a memory
/// system (or an allocator used by it) allocates space to the user from some static
/// buffer, those allocations should NOT be reported.
///
class hkMemorySnapshot
{
    public:

    	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, hkMemorySnapshot);

		typedef hkStackTracer::CallTree::TraceId TraceId;
		typedef int SourceId;
		typedef int ProviderId;
		typedef int AllocationId;

		enum StatusBits
		{
			STATUS_OVERHEAD,
			STATUS_USED,
			STATUS_UNUSED,
		};
		typedef hkEnum<StatusBits,hkInt8> Status;

		explicit hkMemorySnapshot(hkMemoryAllocator* a=HK_NULL);
		hkMemorySnapshot(const hkMemorySnapshot& rhs);
		void setAllocator(hkMemoryAllocator* a);
		void swap(hkMemorySnapshot& m);
		void clear();

		~hkMemorySnapshot();

			/// If -1 is used as parent ID then the provider is configured without any parent.
		ProviderId addProvider(const char* name, ProviderId parent = -1);

			/// Add a new parent to the specified provider
		void addParentProvider(ProviderId provider, ProviderId parent);

			

		AllocationId addItem(ProviderId id, Status status, const void* address, int size);

		AllocationId addAllocation(ProviderId id, const void* address, int size) { return addItem(id, STATUS_USED, address, size);  }
		AllocationId addUnused(ProviderId id, const void* address, int size) { return addItem(id, STATUS_UNUSED, address, size);  }
		AllocationId addOverhead(ProviderId id, const void* address, int size) { return addItem(id, STATUS_OVERHEAD, address, size);  }

			/// Describes how a sample hkMemoryRouter is connected to the provider hierarchy.
		void setRouterWiring(ProviderId stack, ProviderId temp, ProviderId heap, ProviderId debug, ProviderId solver);

		void setCallStack(AllocationId id, const hkUlong* addresses, int numAddresses);
			/// Get the call tree. Can be used with the m_traceId, to get a call stack for each allocation.
		const hkStackTracer::CallTree& getCallTree() const { return m_callTree; }

		void sort();

		struct Allocation
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE,Allocation);

			/// ==
			hkBool operator==(const Allocation& rhs) const;
			/// !=
			hkBool operator!=(const Allocation& rhs) const;

			const void* m_start;	///< Base of allocation
			int m_size;				///< Size of allocation
			SourceId m_sourceId;	///< Index of the allocator it came from
			TraceId m_traceId;		///< Index of the callstack or -1 if none
			Status m_status;		///< Status (type of the allocation)
		};

		/// A provider is an entity capable of obtaining allocations; in case the
		/// provider has no parent we assume that the allocations are coming from
		/// the system allocator. If the provider has at least one parent then the
		/// allocations will be obtained from any of the parent providers.
		struct Provider
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE,Allocation);
			char m_name[32];					///< name of the allocator
			hkArrayBase<int> m_parentIndices;	///< index of a parent or -1 if none
		};

		const hkArrayBase<Allocation>& getAllocations() const { return m_allocations; }

		/// Works out the allocations which are different
		static void HK_CALL allocationDiff(const hkMemorySnapshot& snapA, 
			const hkMemorySnapshot& snapB, hkArray<Allocation>& onlyInA, hkArray<Allocation>& onlyInB);

		/// Dump details (including stack trace if there is one) about an allocation
		void dumpAllocation(const Allocation& alloc, hkOstream& stream) const;

	protected:

		friend class hkVdbStreamReportUtil;
		hkMemoryAllocator* m_mem;
		hkArrayBase<Allocation> m_allocations;
		hkArrayBase<Provider> m_providers;
		/// Describes how a sample router is connected to the provider hierarchy
		/// (i.e. which provider is used for the different kind of allocations),
		/// in the following order: stack, temp, heap, debug, solver.
		ProviderId m_routerWiring[5]; 
		hkStackTracer::CallTree m_callTree;
};

#endif // HK_MEMORY_SNAPSHOT_H

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
