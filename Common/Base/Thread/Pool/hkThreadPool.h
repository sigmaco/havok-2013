/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_THREAD_POOL_H
#define HK_THREAD_POOL_H

struct hkTimerData;


/// This class defines an interface for managing the synchronization of a pool of threads that can be assigned to work 
/// on a generic work load and waited on to finish.
class hkThreadPool : public hkReferencedObject
{
public:	

	HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);

	virtual ~hkThreadPool() {}

	/// Begin processing the given work load using the thread pool and return immediately (non-blocking call).
	virtual void processWorkLoad(void * workLoad) = 0;

	/// Waits for the work load being processed by the thread pool to be completed before returning.			
	virtual void waitForCompletion() = 0;

	/// Returns true if processWorkLoad has been called but waitForCompletion has not been
	virtual bool isProcessing() = 0;

	/// Get number of threads currently running
	virtual int getNumThreads() = 0;

	/// Set the number of threads currently running. Returns the number of threads actually set.
	virtual void setNumThreads( int numThreads ) = 0;

	/// Get the timer data collected during processWorkLoad
	virtual void appendTimerData( hkArrayBase<hkTimerData>& timerDataOut, hkMemoryAllocator& alloc ) = 0;

	/// Clear the timer data. This must be done every frame or the timers will overrun
	virtual void clearTimerData() = 0;	

	/// Cause threads to garbage collect their memory immediately before signaling completion.
	/// Call this method before processWorkLoad(). Note this only applies to the next completion, it is reset to 
	/// false when waitForCompletion() returns. This allows a subsequent garbage collection of the main heap 
	/// (hkMemorySystem::garbageCollect) to recover more memory. This operation should only be called when needed 
	/// since repopulating the thread local caches can be expensive.
	virtual void gcThreadMemoryOnNextCompletion() = 0;
};


#endif // HK_THREAD_POOL_H

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
