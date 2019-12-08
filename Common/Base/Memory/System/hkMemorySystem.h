/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKBASE_hkMemorySystem_H
#define HKBASE_hkMemorySystem_H

	#include <Common/Base/Memory/Router/hkMemoryRouter.h>
	typedef hkMemoryAllocator::MemoryStatistics hkAllocatorStatistics;

class hkMemorySnapshot;
class hkThreadMemory;
class hkDebugMemorySystem;

//struct hkMemoryPointerInfo;

	/// Interface to high level memory operations.
	/// These operations apply to the system as a whole i.e., initialization
	/// and shutdown, memory statistics and debugging methods.
class hkMemorySystem
{
	//+hk.MemoryTracker(ignore=True)
	public:

		HK_DECLARE_PLACEMENT_ALLOCATOR();

			/// Construction info for hkMemorySystem
		struct FrameInfo
		{
			//+hk.MemoryTracker(ignore=True)
				/// Construct a FrameInfo with the specified physics solver buffer.
				/// See Common Havok Components > 1.1 Havok Base Library > 1.1.7. Memory Customization > 1.1.7.2. Solver Buffer Size
				/// for more information. May be zero if physics is not being used.
			FrameInfo(int solverBufferSize);

				/// If set, a buffer will be allocated and given to hkSolverAllocator::s_solverAllocator
			int m_solverBufferSize;
		};

		/// An aggregate of all the memory statistics of underlying providers.
		struct MemoryStatistics
		{
			HK_DECLARE_PLACEMENT_ALLOCATOR();
			struct Entry
			{
				HK_DECLARE_PLACEMENT_ALLOCATOR();
				hkStringPtr m_allocatorName;
				hkAllocatorStatistics m_allocatorStats;
			};
			hkArray < Entry > m_entries;
		};
			/// Flags for init and quit
		enum FlagBits
		{
				/// Apply to persistent parts, heap(), debug()
			FLAG_PERSISTENT = 1,
				/// Apply to all frame local allocators such as temp(), stack() and solver()
			FLAG_TEMPORARY = 2,
				/// Apply to all allocators.
			FLAG_ALL = FLAG_PERSISTENT|FLAG_TEMPORARY,
				// old names for the above
			FLAG_ROUTER = FLAG_PERSISTENT,
			FLAG_FRAME = FLAG_TEMPORARY,
		};
		typedef hkFlags<FlagBits, int> Flags;

			/// Destructor, usually empty as the real work is done in mainQuit.
		virtual ~hkMemorySystem();

			/// Memory system methods.
			/// These are not normal methods of hkMemoryRouter because each instance is
			/// thread local, but the methods operate on the global system.
			/// The code which initializes the memory system will set these pointers
			/// as only it knows how they should be implemented.
		virtual hkMemoryRouter* mainInit(const FrameInfo& info, Flags f=FLAG_ALL) = 0;

			/// Shut down the memory system.
			/// Some implementations will return HK_FAILURE if leaks are detected.
		virtual hkResult mainQuit(Flags f=FLAG_ALL) = 0;

			/// Method for threads to construct their local instances.
		virtual void threadInit(hkMemoryRouter& r, const char* name, Flags f=FLAG_ALL) = 0;
			/// Method for threads to deinitialize their local instances.
		virtual void threadQuit(hkMemoryRouter& r, Flags f=FLAG_ALL) = 0;

			// Limiting memory

			/// Set the soft limit for the heap.
		virtual hkResult setHeapSoftLimit(int nbytes);

			/// Get the soft limit for the heap.
		virtual int getHeapSoftLimit() const;

			/// Returns true if a certain allocation can be done.
		virtual bool solverCanAllocSingleBlock( int numBytes );

			/// Returns true if a total amount of memory of at least 'size' is available.
		virtual bool heapCanAllocTotal( int numBytes );


			/// Print memory usage statistics to the given ostream.
		virtual void printStatistics(hkOstream& ostr) = 0;

			/// Collects the memory statistics from underlying allocators.
		virtual void getMemoryStatistics(MemoryStatistics& stats) = 0;

			/// Specialized heap access.
			/// For regular heap access use hkMemoryRouter::getInstance().heap(). This method
			/// accesses the underlying heap beyond the thread local caches. Currently only used
			/// by the PlayStation(R)3 SPU allocator.
		virtual hkMemoryAllocator* getUncachedLockedHeapAllocator() = 0;

			/// Try to free any unused thread local memory, see also garbageCollect().
			/// Because this method will typically access thread local which is not protected
			/// with a lock, the calling thread should generally own the memory router. Otherwise
			/// if the router belongs to another thread, it must be ensure that the other thread
			/// does not enter any memory functions or corruption is likely.
		virtual void garbageCollectThread(hkMemoryRouter& router);
			/// Try to free unused memory in the shared area.
			/// This method may be called after one or more threads have called garbageCollectThread.
			/// While this method is thread safe, note that it will generally lock the shared area
			/// for its entire duration.
		virtual void garbageCollectShared();
			/// Default implementation garbage calls garbageCollectThread then garbageCollectShared.
			/// Depending on the memory system, there are often two levels of block caching. The first
			/// level is private to each thread and the second level is shared between all threads.
			/// This method frees the current threads cache and the shared cache. Note that the
			/// other threads caches are not garbage collected. See also garbageCollectThread().
		virtual void garbageCollect();

			/// Users may call this for each logical frame.
			/// It is used by some checking allocators. For instance the optimizer memory needs it
			/// to detect allocations within the frame which could be moved to the temp allocator.
		virtual void advanceFrame() {}

		// Optional debugging interfaces.

			/// Access to the debug interface (if present).
		virtual hkDebugMemorySystem* getDebugInterface() { return HK_NULL; }

			/// Optional interface to retrieve a snapshot of all allocations.
		virtual hkResult getMemorySnapshot(hkMemorySnapshot& snapshot) { return HK_FAILURE; }

			/// Returns HK_FAILURE if not implemented, or the address wasn't allocated by this system.
			/// callStack should point to a buffer that will receive the call stack. stackSize is the size of the buffer
			/// will be modified to the call stack size written to the buffer.
			/// allocSize returns the size of the allocation.
		virtual hkResult getAllocationCallStack(const void* ptr, hkUlong* callStack, int& stackSize, hk_size_t& allocSize) { return HK_FAILURE; }
		
			/// This virtual function will run through the used heap allocators and
			/// set a new scrub value for heap allocations and deallocations.
			/// By default we will do anything with those values as this function is
			/// currently only used by the hkCheckDeterminismUtil. If a specific memory
			/// system requires handling of this, it can always be overriden.
			/// At the moment only the hkCheckingMemorySystem and the hkFreeListMemorySystem
			/// handle heap scrubbing.
		virtual void setHeapScrubValues(hkUint32 allocValue, hkUint32 freeValue) {}

			/// Perform an internal consistency check.
		virtual hkBool32 isOk() const { return true; }

			/// Set the global instance pointer
		static void HK_CALL replaceInstance( hkMemorySystem* m );

			/// Get the global instance
		static hkMemorySystem& HK_CALL getInstance();

			/// Get the global instance pointer
		static hkMemorySystem* HK_CALL getInstancePtr();

	protected:

		static hkMemorySystem* s_instance;
};

#endif // HKBASE_hkMemorySystem_H

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
