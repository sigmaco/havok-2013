/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKBASE_HK_SIMPLE_SCHEDULER_H
#define HKBASE_HK_SIMPLE_SCHEDULER_H

#include <Common/Base/Types/hkHandle.h>
#include <Common/Base/Container/String/hkStringBuf.h>

/// Builder and storage of tasks with dependencies.
/// The basic idea is that all tasks and dependencies are known at start of frame time
/// and that no dependencies or tasks are changed by the worker threads.
/// If your schedule is completely constant over frames, you could keep an instance of this class around.
class hkSimpleSchedulerTaskBuilder
{
	public:
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE, hkSimpleSchedulerTaskBuilder );

		/// maximum number of threads, 2 bytes per thread overhead
		enum { MAX_NUM_THREADS = 16 };

		/// An id for your task, needed as an iterator by the scheduler.
		HK_DECLARE_HANDLE(TaskId, hkUint16, 0xffff);

		/// ctor.
		hkSimpleSchedulerTaskBuilder(int taskCapacity = 32);

		~hkSimpleSchedulerTaskBuilder();

		/// Add a task.
		/// \a dependentTasksCapacity must be higher than the number of tasks depending on this task.
		/// This is typically the number of output objects of this task.
		/// Your specific task data is treated as a simply chunk of memory, which will be aligned on a 4 byte boundary.
		TaskId addTask(const void* taskData, int numBytesTaskData, int dependentTasksCapacity = 2);

		/// Get the task data of task \a id.
		void* getTaskData(TaskId id) { return getTaskHeader(id).getTaskData(); }

		/// Add a dependency to another task directly.
		void addDependency(TaskId baseTask, TaskId dependentTask);


		/// Helper object which is an abstraction of any data object. This objects are either input or an output
		/// of a task. Using this helper objects you can build the dependency graph of tasks.
		/// To do this simply declare your tasks with input and output objects in
		/// the order they should be scheduled. Basically you write a 'pseudo' single
		/// threaded version and the dependency builder will work out the parallelism automatically.
		struct Object
		{
			Object() { m_lastOutput = TaskId::invalid(); }
			TaskId m_lastOutput;
		};

		/// Adds an input object dependency.
		HK_FORCE_INLINE void addInput(TaskId myTask, const Object& input)
		{
			if ( input.m_lastOutput.isValid() )
			{
				addDependency( input.m_lastOutput, myTask );
			}
		}

		/// Adds an output object dependency. Note all outputs have to be declared after the inputs.
		HK_FORCE_INLINE void addOutput(TaskId myTask, Object& output)
		{
			HK_ASSERT2(0xf034dccc, myTask != output.m_lastOutput, "Please declare outputs after inputs");
			output.m_lastOutput = myTask;
		}


		/// Call this after you added the last task and dependency.
		/// Needs to be called before you can call hkSimpleScheduler::initScheduler().
		void finalize();

		/// After you run the scheduler, the data in this class has been modified.
		/// This method resets the runtime data to its original state.
		void resetRuntimeData(); 

		/// Prints out batches of independent tasks which can run in parallel.
		/// Task needs to implement sprint( buffer[256] ).
		template<class Task>
		inline void printSimulatedRun();


	protected:

		friend class hkSimpleScheduler;

		// Head of a task. Task data simply is appended to the header.
		struct TaskHeader
		{
			HK_FORCE_INLINE hkUchar* getTaskData()	{return (hkUchar*)&m_dependentTasks[m_capacity];	}

			HK_FORCE_INLINE const hkUchar* getTaskData() const	{ return (const hkUchar*)&m_dependentTasks[m_capacity]; }

			HK_FORCE_INLINE void addDependentTask(TaskId id);

			hkUchar m_numDependencies;
			hkUchar m_capacity;
			TaskId  m_dependentTasks[1];
		};

		HK_FORCE_INLINE TaskHeader& getTaskHeader(TaskId id);

		struct TaskInfo
		{
			hkUint16 m_referenceCount;
			hkUint16 m_taskOffset;
		};

		// The initial reference count as well as the task offsets.
		hkArray<TaskInfo> m_initialReferenceCounts;

		//
		//	Shared data by hkSimpleScheduler
		//

		/// Array holding all task data with dependencies.
		hkArray<hkUchar> m_taskData;

		/// An array of Ids of finished tasks. This is written by the hkSimpleScheduler.
		/// 
		mutable hkArray<TaskId> m_finishedTasks;

		/// The number of finished tasks (atomically incremented by the hkSimpleScheduler).
		mutable hkUint32 m_numFinishedTasks;

		//
		//	Internal debugging variables
		//

		hkBool m_finalized;						// set if finalized
		mutable hkUint32 m_lockCount;			// how many hkSimpleScheduler are using this
		mutable hkUint32 m_numActiveThreads;	// how many threads are active
};

















class hkSimpleScheduler
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, hkSimpleScheduler);

		/// ctor
		hkSimpleScheduler(){}

		/// Task Id
		typedef hkSimpleSchedulerTaskBuilder::TaskId	 TaskId;
		typedef hkSimpleSchedulerTaskBuilder::TaskHeader TaskHeader;

		/// Init the scheduler.
		/// On Spu this allocates memory from the SPU stack.
		void initScheduler(const hkSimpleSchedulerTaskBuilder* tasksPpu);

		/// Exit the scheduler.
		/// Important on SPU to release SPU stack memory.
		void exitScheduler(const hkSimpleSchedulerTaskBuilder* tasksPpu);

		/// Get the first task.
		/// \a taskDataOut is a pointer to the task data.
		HK_FORCE_INLINE TaskId getFirstTask(void** taskDataOut);

		/// Get the next task. Returns TaskId::invalid() if no more tasks are available.
		/// \a taskDataOut is a pointer to the task data.
		/// You can pass in TaskId(0) as a dummy task for the first call.
		TaskId finishTaskAndGetNextTask(TaskId previousTask, void** taskDataOut);

		/// Resets the thread local scheduler.
		/// This needs to be done by all threads if you want to reuse the thread local scheduler
		/// when resetTasksRuntimeData() is called by the master thread.
		void resetScheduler();

		/// Resets the shared runtime data of ALL tasks. 
		/// That means the next call by any thread to getFirstTask will return the very first task in the shared data.
		/// Warning: you can only call this if no other threads are using this scheduler.
		void resetTasksRuntimeData(hkSimpleSchedulerTaskBuilder* tasksPpu);

	protected:

		HK_FORCE_INLINE TaskHeader& getTaskHeader(TaskId id);

		hkArray<hkSimpleSchedulerTaskBuilder::TaskInfo> m_referenceCounts;	// this is a thread local copy of the main reference count to keep the data thread local
		enum { MAX_ACTIVE_TASKS = 128 };

		/// An array of active tasks.
		TaskId   m_activeTasks[MAX_ACTIVE_TASKS];

		HK_PAD_ON_SPU(int) m_numActiveTasks;

		/// Pointer to a shared list of finished tasks.
		/// Access to this memory is controlled by m_numFinishedTasks.
		HK_PAD_ON_SPU(TaskId::Type*)   m_finishedTasks;

		HK_PAD_ON_SPU( int )	m_finishTasksByteSize;

		/// Each thread will finish a dummy 0 task, so we have to correct for that
		HK_PAD_ON_SPU( int )	m_numActiveThreadsDetected;

		/// Points to a shared (Ppu) variable which counts the number of finished tasks.
		HK_PAD_ON_SPU(hkUint32*) m_numFinishedTasks;

		/// The total number of tasks in the system.
		HK_PAD_ON_SPU(int)	m_numTotalTasks;

		/// The number of finished tasks this thread has processed.
		HK_PAD_ON_SPU(int)	m_numProcessedFinishedTask;

		/// the number of tasks removed from the queue
		HK_PAD_ON_SPU(int) m_numTasksRemovedFromTheActiveList;

		/// Points to the task data (Spu memory).
		HK_PAD_ON_SPU(const hkUchar*) m_taskData;

		HK_PAD_ON_SPU(int)		m_taskDataSize;		// needed to deallocateStack on SPU

		/// Debugging.
		const hkSimpleSchedulerTaskBuilder* m_schedulerPpu;
};

HK_FORCE_INLINE hkSimpleSchedulerTaskBuilder::TaskHeader& hkSimpleSchedulerTaskBuilder::getTaskHeader(TaskId id )
{
	int offset = m_initialReferenceCounts[id.value()].m_taskOffset;
	return *(TaskHeader*)&m_taskData[ offset ];
}

HK_FORCE_INLINE hkSimpleSchedulerTaskBuilder::TaskHeader& hkSimpleScheduler::getTaskHeader(TaskId id )
{
	int offset = m_referenceCounts[id.value()].m_taskOffset;
	return *(TaskHeader*)&m_taskData[ offset ];
}

template<class Task>
void hkSimpleSchedulerTaskBuilder::printSimulatedRun()
{
	hkArray<TaskInfo> referenceCounts;  referenceCounts= m_initialReferenceCounts;
	hkArray<TaskId> activeTasks;
	HK_REPORT("");
	HK_REPORT("hkSimpleSchedulerTaskBuilder::printSimulatedRun:");
	HK_REPORT("************************************************");
	HK_REPORT("");


	while(1)
	{
		hkStringBuf msg;
		char buffer[256];

		// collect all tasks with reference count 0 and print
		{
			activeTasks.clear();
			for (int i=0; i < referenceCounts.getSize(); i++ )
			{
				if (referenceCounts[i].m_referenceCount == 0 )
				{
					activeTasks.pushBack(TaskId(i) );
					TaskHeader& header = getTaskHeader( TaskId(i) );
					Task& task = *(Task*)header.getTaskData();
					hkString::sprintf( buffer, "T%i", i );
					msg.append( buffer );
					task.sprint( buffer );
					msg.append( buffer );
					msg.append( " " );

				}
			}
		}
		HK_REPORT( msg.cString() );
		if ( activeTasks.isEmpty() )
		{
			break;
		}

		//
		//	decrement the reference count of all dependent tasks 
		//  and set the reference count of the active tasks to 0xffff
		//
		{
			for (int i=0; i < activeTasks.getSize(); i++)
			{
				TaskId activeTask = activeTasks[i];
				referenceCounts[activeTask.value()].m_referenceCount = 0xffff;
				TaskHeader& header = getTaskHeader( activeTask );
				for (int k=0; k < header.m_numDependencies; k++)
				{
					TaskId dependentTask = header.m_dependentTasks[k];
					referenceCounts[dependentTask.value()].m_referenceCount--;
				}
			}
		}
	}
}

hkSimpleScheduler::TaskId hkSimpleScheduler::getFirstTask(void** taskDataOut )
{
	return finishTaskAndGetNextTask(TaskId (0), taskDataOut );
}


#endif // HKBASE_HK_SIMPLE_SCHEDULER_H

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
