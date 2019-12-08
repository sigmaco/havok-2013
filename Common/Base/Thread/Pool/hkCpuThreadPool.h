/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_THREAD_POOL_CPU_H
#define HK_THREAD_POOL_CPU_H

#include <Common/Base/Thread/Pool/hkThreadPool.h>
#include <Common/Base/Thread/Thread/hkThread.h>
#include <Common/Base/Thread/Semaphore/hkSemaphore.h>


struct hkCpuThreadPoolCinfo;
class hkWorkerThreadContext;


/// A CPU implementation of the hkThreadPool interface. Users must provide a WorkerFunction that will be called 
/// from every thread each time a work load is made available through a processWorkLoad call.
class hkCpuThreadPool : public hkThreadPool
{
	public:

		/// Type of the worker function pointer that will contain the function to be executed in every thread each 
		/// time a work load is made available through a processWorkLoad call
		typedef void (HK_CALL *WorkerFunction)(void* workLoad);

	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);

			/// Initialize multi-threading state and create threads.
			/// This will also call hkReferencedObject::setLockMode( hkReferencedObject::LOCK_MODE_MANUAL);
		hkCpuThreadPool(const hkCpuThreadPoolCinfo& cinfo);

			/// Destroy threads and delete state.
			/// This will also call hkReferencedObject::setLockMode( hkReferencedObject::LOCK_MODE_NONE);
		~hkCpuThreadPool();


		//////////////////////////
		// hkThreadPool interface

		virtual void processWorkLoad(void * workLoad);
			
		virtual void waitForCompletion();

		virtual bool isProcessing();

		virtual void appendTimerData(  hkArrayBase<hkTimerData>& timerDataOut, hkMemoryAllocator& alloc );

		virtual void clearTimerData();

		virtual int getNumThreads();

		virtual void setNumThreads(int numThreads);

		virtual void gcThreadMemoryOnNextCompletion();
		
	protected:

		void addThread();
		void removeThread();
		static void* HK_CALL threadMain(void* workerThreadData);

	public:

		struct SharedThreadData;

			/// Thread state data. Used only by one worker thread
		struct WorkerThreadData
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_ENTITY, WorkerThreadData);

			WorkerThreadData();

				/// Pointer to the data shared between threads.
			SharedThreadData* m_sharedThreadData;

				/// System handle to the thread.
			hkThread m_thread;

				/// Thread Id from 0 - N
			int m_threadId;

				//
			int m_hardwareThreadId;

				/// Flag is set to true when the thread is requested to close.
			bool m_killThread;
			
			bool m_clearTimers;

				/// Semaphore used to pause a physics thread after it's done its calculations.
				/// This semaphore is released by the main thread on every simulation step.
			hkSemaphore m_semaphore;				

				// Internal buffer used for collecting timer information
			char* m_monitorStreamBegin;
			char* m_monitorStreamEnd;

			hkWorkerThreadContext* m_context;
		};		

			/// Data shared by all threads.
		struct SharedThreadData
		{
			public:

				HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_UTILITIES, hkCpuThreadPool::SharedThreadData );

				SharedThreadData();

			public:

				WorkerFunction m_workerFunction;

				void* m_workLoad;
				
					/// Semaphore used to pause the main thread when it waits for threads
					/// to finish their calculations.
				hkSemaphore m_workerThreadFinished;

					/// Number of threads.
				int m_numThreads;
			
				int m_timerBufferAllocation;

				hkBool m_gcThreadMemoryOnCompletion;
		};

	public:

		/// Data local to each physics thread.
		WorkerThreadData m_workerThreads[ HK_MAX_NUM_THREADS ];

	protected:

		SharedThreadData m_sharedThreadData;

			/// Debugging flag set to true when worker threads are stepping
		hkBool m_isRunning;

			/// String for thread names (depending on platform support)
		const char* m_threadName;

			/// See comments for hkCpuThreadPoolCinfo::m_stackSize
		int m_stackSize;
};


/// Construction info for hkCpuThreadPool
struct hkCpuThreadPoolCinfo
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_UTILITIES, hkCpuThreadPoolCinfo );

	hkCpuThreadPoolCinfo(hkCpuThreadPool::WorkerFunction workerFunction);

	/// Function to be called in each thread to process a work load (see hkCpuThreadPool::WorkerFunction)
	hkCpuThreadPool::WorkerFunction m_workerFunction;

	/// The number of threads (defaults to 1)
	int m_numThreads;

	/// The program stack size for each thread.
	/// On Win32 and Xbox 360, defaults to 0, meaning the thread inherits the executable's stack size.
	/// On PlayStation(R)3, defaults to 256K.
	/// Has no effect on other platforms (e.g., posix)
	int m_stackSize;


	/// This is the buffer size allocated in each thread for collecting timer
	/// information. It defaults to 0, which means timers will be disabled.
	/// To view timers in the VDB, you need to set this buffer size to a non zero value.
	/// 2000000 (2 Mb) is a good recommended size. Smaller buffers are ok, but you may
	/// lose timer info.
	int m_timerBufferPerThreadAllocation;

	/// If this data is used to set the hardware thread ids, on XBox360, XSetThreadProcessor is called on each thread
	/// with the hardware id. If this array is not set then it defaults to {2, 4, 1, 3, 5, 0} (i.e., the first 3 threads
	/// are set to separate cores).
	/// On Windows, it will use SetThreadIdealProcessor, and will use {1,2...,(numProcessors-1),0} by default if this array
	/// not set.
	/// The two defaults assume that you are using core 0 as your main calling thread (that will do work too)
	hkArray<int> m_hardwareThreadIds;

	/// The thread name to be passed to hkThread::startThread
	const char* m_threadName;	
};


#endif // HK_THREAD_POOL_CPU_H

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
