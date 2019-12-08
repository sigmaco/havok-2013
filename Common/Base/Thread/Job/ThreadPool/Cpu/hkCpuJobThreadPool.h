/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_BASE_CPU_THREAD_POOL_H
#define HK_BASE_CPU_THREAD_POOL_H

#include <Common/Base/Thread/Job/ThreadPool/hkJobThreadPool.h>
#include <Common/Base/Thread/Pool/hkCpuThreadPool.h>

/// The construction info for the hkCpuJobThreadPool
struct hkCpuJobThreadPoolCinfo : public hkCpuThreadPoolCinfo
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_UTILITIES, hkCpuJobThreadPoolCinfo);
		
		hkCpuJobThreadPoolCinfo();
};


/// Utility class for running Havok in multiple threads.
/// The utility creates a pool of threads, and suspends them with a semaphore. On each call to
/// startStep the main thread resumes/releases all physics threads.
class hkCpuJobThreadPool : public hkJobThreadPool
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_UTILITIES);

		/// Initialize multi-threading state and create threads.
		/// This will also call hkReferencedObject::setLockMode( hkReferencedObject::LOCK_MODE_MANUAL);
		hkCpuJobThreadPool( const hkCpuJobThreadPoolCinfo& cinfo );

		/// hkJobThreadPool interface
		virtual void processAllJobs( hkJobQueue* queue, hkJobType firstJobType_unused = HK_JOB_TYPE_MAX );


		////////////////////////////
		/// hkThreadPool interface
		virtual void waitForCompletion();

		virtual bool isProcessing();

		virtual void appendTimerData(  hkArrayBase<hkTimerData>& timerDataOut, hkMemoryAllocator& alloc );

		virtual void clearTimerData();

		virtual int getNumThreads();

		virtual void setNumThreads(int numThreads);				

		virtual void gcThreadMemoryOnNextCompletion();


		/// Function called internally in every thread to process the job queue. Do not call directly
		static void workerFunction(void* workLoad);

	public:

		hkCpuThreadPool m_threadPool;
};


#endif // HK_BASE_CPU_THREAD_POOL_H

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
