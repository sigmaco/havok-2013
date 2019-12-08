/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_WORKER_THREAD_H
#define HK_WORKER_THREAD_H


#include <Common/Base/Memory/Router/hkMemoryRouter.h>


/// This class performs the required initialization steps for a Havok worker thread like setting up the memory and base 
/// systems. Create an object of this class in your worker thread before performing any Havok work. Object 
/// destruction takes care of shutting down the context appropriately. See hkCpuThreadPool::threadMain for an example
/// of use.
class hkWorkerThreadContext
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, hkWorkerThreadContext);

		//// Thread IDs must be assigned sequentially starting from 1. ID 0 is used by the main Havok thread.
		hkWorkerThreadContext(int threadId);
		~hkWorkerThreadContext();		

	public:

		hkMemoryRouter m_memoryRouter;		
};


#endif // HK_WORKER_THREAD_H

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
