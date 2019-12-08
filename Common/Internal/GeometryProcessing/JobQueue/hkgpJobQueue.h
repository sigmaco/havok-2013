/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKGP_JOB_QUEUE_H
#define HKGP_JOB_QUEUE_H

//
// Bare-bone job queue
//
struct	hkgpJobQueue
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE,hkgpJobQueue);
private:
	struct IJob
	{
		//+hk.MemoryTracker(ignore=True)
		virtual ~IJob() {}
		virtual void run() const=0;
	};
	template <typename T>
	struct Box : public IJob
	{
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE,Box);
		inline			Box(const T& job) : m_job(job) {}
		inline void		run() const { m_job.run(); }
		mutable T		m_job;
	};
public:
							hkgpJobQueue(int numThreads=-1);
							~hkgpJobQueue();
	void					waitForCompletion();
	int						getNumThreads() const { return(m_threads.getSize()); }
	template <typename T>
	void					appendJob(const T& job) { push(new Box<T>(job)); }
private:
	void					push(IJob* job);
	void					threadMain();
	static void* HK_CALL	threadStart(void* arg);
private:
	hkInplaceArray<class hkThread*,8>	m_threads;
	class hkCriticalSection*			m_jobsLock;	
	class hkSemaphore*					m_newJobEvent;
	class hkSemaphore*					m_endJobEvent;
	class hkSemaphore*					m_endThreadEvent;
	hkArray<IJob*>						m_jobs;
	int									m_numPendings;
};


#endif // HKGP_JOB_QUEUE_H

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
