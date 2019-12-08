/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKA_JOB_DONE_NOTIFIER_H
#define HKA_JOB_DONE_NOTIFIER_H

#include <Common/Base/Thread/Semaphore/hkSemaphoreBusyWait.h>


/// A container for two kinds of notification for when an animation job completes.
struct hkaJobDoneNotifier
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_ANIMATION, hkaJobDoneNotifier);

	hkaJobDoneNotifier();

	/// Calls release() on the semaphore and sets *m_flag to true.
	void signal();

	/// This semaphore is released when the work is finished.
	/// It can be set to HK_NULL if you don't need to wait on a specific job.
	/// The same semaphore can be shared by multiple jobs.
	hkSemaphoreBusyWait* m_semaphore;

	/// This flag is incremented when the work is finished.
	/// It can be set to HK_NULL if you don't need to wait on a specific job.
	/// Each job must point to its own flag to avoid a race condition.
	/// This is a lightweight mechanism to determine if a job has completed.
	hkUint32* m_flag;
};

#include <Animation/Animation/Playback/Multithreaded/hkaJobDoneNotifier.inl>

#endif

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
