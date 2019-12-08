/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKBASE_hkCheckingMemorySystem_H
#define HKBASE_hkCheckingMemorySystem_H

#include <Common/Base/Memory/System/Debug/hkDebugMemorySystem.h>
#include <Common/Base/System/StackTracer/hkStackTracer.h>
#include <Common/Base/Thread/CriticalSection/hkCriticalSection.h>
#include <Common/Base/Memory/Allocator/Checking/hkPaddedAllocator.h>
#include <Common/Base/Memory/Allocator/Checking/hkDelayedFreeAllocator.h>
#include <Common/Base/Memory/Allocator/Stats/hkStatsAllocator.h>
#include <Common/Base/Memory/Allocator/Recall/hkRecallAllocator.h>

	/// Debugging memory system checks for some common errors.
	/// It detects memory leaks and some bad memory writes. The default is
	/// to perform a stack trace (if the platform supports it) on every allocation
	/// to pinpoint leaks. This may be disabled for increased speed.
	///
	/// Several other logical errors are detected, such as allocating and freeing
	/// memory with incompatible allocators.
	///
	/// This class owns several proxy allocators which forward requests
	/// back to central methods along with a context indicating where the
	/// request came from.
class hkCheckingMemorySystem : public hkDebugMemorySystem
{
	//+hk.MemoryTracker(ignore=True)
	public:

		HK_DECLARE_PLACEMENT_ALLOCATOR();

			/// Checks the allocator can perform.
		enum CheckBits
		{
				/// No checks, just forward the request.
			CHECK_NONE = 0,
			// CHECK_UNUSED= 1, available for reuse
				/// Check for matching free for each alloc.
			CHECK_LEAKS = 2,
				/// Store a callstack for each allocation, especially useful for leak checking.
			CHECK_CALLSTACK = 4,
				/// Pad each allocation with some canary bytes.
			CHECK_PAD_BLOCK = 8,
				/// Cache some free blocks to detect use-after-free errors.
			CHECK_DELAYED_FREE = 16,

				/// Default is everything enabled.
			CHECK_DEFAULT = CHECK_LEAKS|CHECK_PAD_BLOCK|CHECK_DELAYED_FREE|CHECK_CALLSTACK
		};

		typedef hkFlags<CheckBits, int> CheckFlags;

			///
		enum AllocatorBits
		{
				/// Freeing thread must also be the allocating thread.
			ALLOCATOR_INVALID = 0,
			ALLOCATOR_HEAP = 1,
			ALLOCATOR_STACK = 2,
			ALLOCATOR_TEMP = 4,
			ALLOCATOR_SOLVER = 8,
			ALLOCATOR_MAX
		};
		typedef hkFlags<AllocatorBits, hkUint32> AllocatorFlags;


			///
		struct AllocationContext
		{
			AllocationContext() : threadId(0), curInUse(0), peakInUse(0) {}
			//+hk.MemoryTracker(ignore=True)
				/// Thread identifier
			hkUint64 threadId;
				///
			AllocatorFlags flags;
				/// Stats
			mutable int curInUse;
				/// Stats
			mutable int peakInUse;
		};

			/// This allocator forwards requests to a checking memory allocator along with a context.
		struct AllocatorForwarder : public hkMemoryAllocator
		{
			//+hk.MemoryTracker(ignore=True)
			HK_DECLARE_PLACEMENT_ALLOCATOR();

			AllocatorForwarder() : m_parent(HK_NULL) {}
			virtual void* blockAlloc( int numBytes );
			virtual void blockFree( void* p, int numBytes );
			virtual void* bufAlloc( int& reqNumInOut );
			virtual void bufFree( void* p, int num );
			virtual void* bufRealloc( void* pold, int oldNum, int& reqNumInOut );
			virtual void getMemoryStatistics( MemoryStatistics& u );
			virtual int getAllocatedSize(const void* obj, int nbytes);
		
			virtual void resetPeakMemoryStatistics();

			hkCheckingMemorySystem* m_parent;
			AllocationContext m_context;
		};

			/// Callback printing function type
		typedef void (HK_CALL *OutputStringFunc)(const char* s, void* userData);

		hkCheckingMemorySystem();

			///
		void init(hkMemoryAllocator* a, OutputStringFunc output, void* outputUserData, CheckBits checks=CHECK_DEFAULT);

			///
		hkBool isInit(); 

			///
		hkResult quit();

		void* checkedAlloc( hkBool32 isBuf, const AllocationContext& context, int numBytes );
		void checkedFree( hkBool32 isBuf, const AllocationContext& context, void* p, int numBytes );

		virtual hkResult getMemorySnapshot(hkMemorySnapshot& snapshot) HK_OVERRIDE;
		virtual hkResult getAllocationCallStack(const void* ptr, hkUlong* callStack, int& stackSize, hk_size_t& allocSize) HK_OVERRIDE;

		virtual void setHeapScrubValues(hkUint32 allocValue, hkUint32 freeValue) HK_OVERRIDE;


			/// Perform an internal consistency check.
		virtual hkBool32 isOk() const HK_OVERRIDE;

		struct AllocInfo
		{
			//+hk.MemoryTracker(ignore=True)
			hkUint64 m_threadId;
			hkUint64 m_allocOrder;
			hkUint64 m_time;
			const void* m_tagData;
			AllocatorFlags m_flags;
			hkStackTracer::CallTree::TraceId m_traceId;
			int m_size;
			int m_locks;
			int m_bookmarkIndex;

			// Used when grouping allocations for reports
			hkUint64 getKey() const;
		};

			/// String and timestamp to mark different sections.
			/// This is used in the leak report in addition to the callstack information.
		struct Bookmark
		{
			//+hk.MemoryTracker(ignore=True)
			Bookmark() : m_name(HK_NULL), m_time(0)
			{
			}

			void set( class hkMemoryAllocator* alloc, const char* name );
			void clear( class hkMemoryAllocator* alloc );

			char* m_name;
			hkUint64 m_time;
		};

		//
		// hkDebugMemorySystem interface
		//
		virtual const void* findBaseAddress(const void* p, int nbytes) HK_OVERRIDE;
		virtual void lockBaseAddress(const void* p) HK_OVERRIDE;
		virtual void unlockBaseAddress(const void* p) HK_OVERRIDE;
		virtual void tagAddress(const void* baseAddress, const void* tag) HK_OVERRIDE;
		virtual void addBookmark( const char* bookmarkName ) HK_OVERRIDE;
		virtual hkBool32 isCheckCallstackEnabled() const HK_OVERRIDE;
		virtual void setCheckCallstackEnabled(bool enabled) HK_OVERRIDE;


		//
		// Memory system methods.
		//
		virtual hkMemoryRouter* mainInit(const FrameInfo& info, Flags f=FLAG_ALL) HK_OVERRIDE;
		virtual hkResult mainQuit(Flags f=FLAG_ALL) HK_OVERRIDE;
		virtual void threadInit(hkMemoryRouter& r, const char* name, Flags f=FLAG_ALL) HK_OVERRIDE;
		virtual void threadQuit(hkMemoryRouter& r, Flags f=FLAG_ALL) HK_OVERRIDE;
		virtual void getMemoryStatistics(MemoryStatistics& stats);
		virtual void printStatistics(hkOstream& ostr) HK_OVERRIDE;
		virtual void advanceFrame() HK_OVERRIDE;
		virtual void garbageCollectShared() HK_OVERRIDE;
		virtual hkMemoryAllocator* getUncachedLockedHeapAllocator() HK_OVERRIDE;

		/// Report active memory allocations, ordered by time.
		void leakReportByTime();
		/// Report active memory allocations, attempting to report the 'root' allocations first
		void leakReportByOwnership();


	protected:

			/// Create a new forwarding allocator
		AllocatorForwarder* newAllocator(AllocatorFlags flags, hkUint64 tid);
			///
		void deleteAllocator( hkMemoryAllocator* a );

		void dumpLeak(const hkArrayBase<int>& owned, const hkArrayBase<hkUlong>& addrs, const hkArrayBase<AllocInfo>& allocs);
		int findPrecedingBookmark( hkUint64 timeStamp ) const;

	protected:

		typedef hkMapBase<hkUlong,AllocInfo> MapType;

		hkStackTracer m_stackTracer;
		hkStackTracer::CallTree m_callTree;
		mutable hkCriticalSection m_section;

			/// The allocator we use for most allocations, it will be cooked using the checking memory system configuration
		hkMemoryAllocator* m_baseAllocator;
			/// Components used to build the base allocator (might not all be valid)
		hkPaddedAllocator m_paddedAllocator; // checks for under/overruns
		hkDelayedFreeAllocator m_delayedFreeAllocator; // 
		hkMemoryAllocator* m_rawAllocator; // the one given to init
			/// We need a stats allocator for call tree nodes in order to keep statistics about
			/// allocations, we can't use the default allocator forwarder behaviour since call tree
			/// nodes get allocated during other allocations. This allocator is usually directly
			/// connected to the raw allocator.
		hkRecallAllocator m_debugAllocator;
		hkStatsAllocator m_callTreeAllocator;

		hkArrayBase< Bookmark > m_bookmarks;

			/// These forward tagged requests to the checkedAlloc and checkedFree
		hkArrayBase<AllocatorForwarder*> m_allocators;

		CheckFlags m_checkFlags;

		MapType m_activePointers;
		hk_size_t m_currentInUse;
		hk_size_t m_peakInUse;
		
		hkUint64 m_allocOrder;

		OutputStringFunc m_outputFunc;
		void* m_outputFuncArg;

		FrameInfo m_frameInfo;

		hk_size_t m_sumAllocatedStackMemory;	 // sum of all stack memories
		hkMemoryRouter m_mainRouter;
		hkUint64 m_timeOfConstruction;


		void danger(const char* message, const void*, const AllocInfo& info) const;
};

#endif // HKBASE_hkCheckingMemorySystem_H

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
