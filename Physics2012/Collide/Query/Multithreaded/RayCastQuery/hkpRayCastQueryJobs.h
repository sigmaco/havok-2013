/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_RAYCAST_QUERY_JOBS_H
#define HKP_RAYCAST_QUERY_JOBS_H

#include <Common/Base/Types/Geometry/Aabb/hkAabb.h>
#include <Common/Base/Thread/Semaphore/hkSemaphoreBusyWait.h>
#include <Common/Base/Thread/JobQueue/hkJobQueue.h>
#include <Physics2012/Collide/Shape/Compound/Tree/hkpBvTreeShape.h>

#include <Physics2012/Collide/Agent/Collidable/hkpCollidable.h>
#include <Physics2012/Collide/Query/CastUtil/hkpWorldRayCastInput.h>
#include <Physics2012/Collide/Query/CastUtil/hkpLinearCastInput.h>
#include <Physics2012/Collide/Shape/Query/hkpShapeRayCastInput.h>
#include <Physics2012/Collide/Shape/Query/hkpShapeRayCastOutput.h>
#include <Physics2012/Collide/Query/Multithreaded/RayCastQuery/hkpRayCastQueryJobs.h>

#include <Physics2012/Internal/Collide/Mopp/Code/hkpMoppCode.h>

#include <Physics2012/Collide/Shape/Query/hkpShapeRayBundleCastInput.h>
#include <Common/Base/Thread/Semaphore/hkSemaphoreBusyWait.h>

class hkpBroadPhase;
class hkpWorld;
class hkpTreeWorldManager;

struct hkpWorldRayCastOutput;


#include <Physics2012/Collide/Query/Multithreaded/CollisionQuery/hkpCollisionQueryJobs.h>
typedef hkpCollisionQueryJobHeader hkpRayCastQueryJobHeader;


//
// The base class for all collision query jobs
//
struct hkpRayCastQueryJob : public hkJob
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_COLLIDE, hkpRayCastQueryJob );

		// Kd tree subtypes start at 128 to keep them separate from other pathfinding jobs
		enum JobSubType
		{
			// Query jobs
			RAYCAST_QUERY_SHAPE_RAYCAST,
			RAYCAST_QUERY_WORLD_RAYCAST,

			RAYCAST_QUERY_JOB_END
		};

		void atomicIncrementAndReleaseSemaphore() const;

	protected:

		HK_FORCE_INLINE hkpRayCastQueryJob( JobSubType subType, hkUint16 size );

	public:

			// This semaphore is released once the original job (and all its spawned children) has finished.
		hkSemaphoreBusyWait*			m_semaphore;

			// this header must be set for all jobs that potentially spawn additional jobs or that have been spawned by other jobs
		hkpRayCastQueryJobHeader*		m_sharedJobHeaderOnPpu;

			// The variable at this location will be incremented (atomically) when the job is done.
		hkUint32*						m_jobDoneFlag;

			// Provides collision filter etc
		const hkpProcessCollisionInput*	m_collisionInput;
};


// ===============================================================================================================================================================================================
//  SHAPE RAYCAST
// ===============================================================================================================================================================================================

/// An hkpShapeRayCastCommand can be used to cast exactly one ray against an arbitrary number of collidables. Depending on how many hits you want
/// to be reported you have to supply a large enough m_results output array. Once this array has reached its capacity, the furthest
/// hit will be dropped.
struct hkpShapeRayCastCommand
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_COLLIDE, hkpShapeRayCastCommand );

		enum { MAXIMUM_RESULTS_CAPACITY = 96 };	// the capacity has to be limited as we need to allocate this array on the SPU stack

		enum { MAXIMUM_NUM_COLLIDABLES = 64 };		// the maximum number of collidables to cast the ray against has to be limited as we need to allocate a hkpCollidable pointer array on the SPU stack

	public:

		// ===================================================================
		// Input
		// ===================================================================

			/// The ray's input data.
		hkpShapeRayCastInput	m_rayInput;

			/// Type of the filter referenced by m_rayInput.m_rayShapeCollectionFilter.
			/// Must be assigned in order for the filter to work on SPU.
		hkUint32				m_filterType; // type is: hkpFilterType

			/// Size of the filter referenced by m_rayInput.m_rayShapeCollectionFilter.
			/// Must be assigned in order for the filter to work on SPU.
		hkInt32					m_filterSize;

			/// Pointer to an array of hkpCollidable pointers. The ray will be cast against these collidables.
			/// This array has to be 16byte aligned.
			/// PlayStation(R)3 note: this array will be DMAd to SPU and therefore must not be allocated on PPU stack.
		const hkpCollidable**	m_collidables;

			/// Number of collidables in the m_collidables array.
		int						m_numCollidables;

		// ===================================================================
		// Output
		// ===================================================================

			/// Pointer to a hkpShapeRayCastOutput array. The user has to pre-allocate this manually. Once the job has finished, this array will hold the results.
			/// PlayStation(R)3 note: this array will be DMAd from SPU and therefore must not be allocated on PPU stack.
		hkpWorldRayCastOutput*	m_results;

			/// The maximum number of results pre-allocated in m_results.
		int						m_resultsCapacity;

			/// The number of results. Remains untouched until the command has been finished.
			/// You can use this to check manually whether the command already has been completed.
		int						m_numResultsOut;

			/// When a collector is not used, only one point per hkpCollidable can be returned.
		hkBool					m_useCollector;
};


/// An hkpShapeRayCastJob will take an arbitrary number of hkShapeRayCastCommands and perform the raycasts. The job is able
/// to split itself into two jobs if it holds more commands than the maximum allowed number that can be executed in one go.
/// Jobs will be processed multithreaded (i.e., in parallel by different PPU and/or SPU threads, if available).
struct hkpShapeRayCastJob : public hkpRayCastQueryJob
{
	public:

		friend struct hkpRayCastQueryJobQueueUtils;

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_COLLIDE, hkpShapeRayCastJob );

		enum { MAXIMUM_NUMBER_OF_COMMANDS_PER_TASK = 90 };

	public:

			/// When creating an hkpShapeRayCastJob you have to pass in an unique jobHeader as well as an array of commands.
			/// The supplied semaphore is released once all commands of this job have been completed and the job has been removed from the job queue.
			/// The number of commands that are grouped into one task is customizable.
			/// PlayStation(R)3 note: the jobHeader and the commandArray will be DMAd to SPU and therefore must not be allocated on PPU stack.
		HK_FORCE_INLINE hkpShapeRayCastJob( const hkpProcessCollisionInput* input, hkpCollisionQueryJobHeader* jobHeader, const hkpShapeRayCastCommand* commandArray, int numCommands, hkSemaphoreBusyWait* semaphore, int numCommandsPerTask = MAXIMUM_NUMBER_OF_COMMANDS_PER_TASK);

			/// Only necessary on PlayStation(R)3.
			/// Use this method to assign this job to be processed on the SPU or PPU. This is automatically set depending on what the job references.
			/// If it references objects which are not supported on the SPU
			/// this function will produce a warning (in debug) and the job will be processed on PPU.
		void setRunsOnSpuOrPpu();

	public:

		HK_FORCE_INLINE hkJobQueue::JobPopFuncResult popJobTask( hkpShapeRayCastJob& out );

		int								m_numCommandsPerTask;	// maximum # of commands per task; once this limit is breached a subjob is spawned
		const hkpShapeRayCastCommand*	m_commandArray;
		int								m_numCommands;
};


// ===============================================================================================================================================================================================
//  WORLD RAYCAST
// ===============================================================================================================================================================================================

/// An hkpWorldRayCastCommand can be used to cast exactly one ray through the broadphase. Depending on how many hits you want
/// to be reported you have to supply a large enough m_results output array. Once this array has reached its capacity, the furthest
/// hit will be dropped.
/// Performance note: when supplying a m_results array-size of exactly 1, the broadphase will use an early-out algorithm to significantly
/// speedup things. With an array-size > 1 this speedup will be lost.
struct hkpWorldRayCastCommand
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_COLLIDE, hkpWorldRayCastCommand );

		enum { MAXIMUM_RESULTS_CAPACITY = 32 };		// the capacity has to be limited as we need to allocate this array on the SPU stack

	public:

		hkpWorldRayCastCommand(){m_useCollector = false; m_stopAfterFirstHit = false;}

		// ===================================================================
		// Input
		// ===================================================================

			/// The ray's input data.
		hkpWorldRayCastInput	m_rayInput;

		// ===================================================================
		// Output
		// ===================================================================

			/// Pointer to a hkpWorldRayCastOutput array. The user has to pre-allocate this manually. Once the job has finished, this array will hold the results.
			/// PlayStation(R)3 note: this array will be DMAd from SPU and therefore must not be allocated on PPU stack.
			/// If m_stopAfterFirstHit is set m_results->m_hitFraction does not work (just set to 0 when hit)
		hkpWorldRayCastOutput*	m_results;

			/// The maximum number of results pre-allocated in m_results.
		int						m_resultsCapacity;

			/// The number of results.
			/// This value is only valid after the job's semaphore has been released.
		int						m_numResultsOut;

			/// When a collector is not used, only one point per hkpCollidable can be returned.
			/// When treeManager is set to the job, this is ignored
		hkBool					m_useCollector;

		/// Whether or not the raycast should terminate after the first (not necessarily closest) hit.
		/// This can speed up queries such as line-of-sight checks, when you only care if the path is clear or not.
		/// If this is set m_results->m_hitFraction does not work (just set to 0 when hit)
		hkBool					m_stopAfterFirstHit;
};

///
struct hkpWorldRayCastBundleCommand
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_COLLIDE, hkpWorldRayCastBundleCommand );

	public:

		// ===================================================================
		// Input
		// ===================================================================

		/// The rays' input data.
		hkpWorldRayCastInput	m_rayInput[4];

		/// Rays have to filled from the start
		int						m_numActiveRays;

		/// Whether or not the raycast should terminate after the first (not necessarily closest) hit.
		/// This can speed up queries such as line-of-sight checks, when you only care if the path is clear or not.
		hkBool					m_stopAfterFirstHit;

		// ===================================================================
		// Output
		// ===================================================================

		/// Pointer to a hkpWorldRayCastOutput array. The user has to pre-allocate this manually. Once the job has finished, this array will hold the results.
		/// PlayStation(R)3 note: this array will be DMAd from SPU and therefore must not be allocated on PPU stack.
		hkpWorldRayCastOutput*	m_results[4];

		/// The number of results.
		/// This value is only valid after the job's semaphore has been released.
		HK_ALIGN16(int			m_numResultsOut[4]);

		//	for broadphase implementation
		hkBool					m_useCollector;
};


/// An hkpWorldRayCastJob will take an arbitrary number of hkWorldRayCastCommands and perform the raycasts. The job is able
/// to split itself into two jobs if it holds more commands than the maximum allowed number that can be executed in one go.
/// Jobs will be processed multithreaded (i.e., in parallel by different PPU and/or SPU threads, if available).
struct hkpWorldRayCastJob : public hkpRayCastQueryJob
{
	public:

		friend struct hkpRayCastQueryJobQueueUtils;

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_COLLIDE, hkpWorldRayCastJob );

		enum { MAXIMUM_NUMBER_OF_COMMANDS_PER_TASK = 64 };

	public:

			/// When creating an hkpWorldRayCastJob you have to pass in an unique jobHeader as well as an array of commands.
			/// The supplied broadphase is used to limit the number of possible object pairs and thus helps increasing performance.
			/// The supplied semaphore is released once all commands of this job have been completed and the job has been removed from the job queue.
			/// The number of commands that are grouped into one task is customizable.
			/// PlayStation(R)3 note: the jobHeader and the commandArray will be DMAd to SPU and therefore must not be allocated on PPU stack.
		HK_FORCE_INLINE hkpWorldRayCastJob( const hkpProcessCollisionInput* input, hkpCollisionQueryJobHeader* jobHeader, const hkpWorldRayCastCommand* commandArray, int numCommands, const hkpBroadPhase* broadphase, hkSemaphoreBusyWait* semaphore, int numCommandsPerTask = MAXIMUM_NUMBER_OF_COMMANDS_PER_TASK);

			/// Only necessary on PlayStation(R)3.
			/// Use this method to assign this job to be processed on the SPU or PPU. This is automatically set depending on what the job references.
			/// If it references objects which are not supported on the SPU
			/// this function will produce a warning (in debug) and the job will be processed on PPU.
		void setRunsOnSpuOrPpu();

	protected:

		HK_FORCE_INLINE hkJobQueue::JobPopFuncResult popJobTask( hkpWorldRayCastJob& out );

	public:

			// Inputs
		int								m_numCommandsPerTask;	// maximum # of commands per task; once this limit is breached a subjob is spawned
		const hkpWorldRayCastCommand*	m_commandArray;
		int								m_numCommands;

		//	if broadphase is used, these bundles are calculated one by one like single commands
		const hkpWorldRayCastBundleCommand* m_bundleCommandArray;
		int									m_numBundleCommands;

		const hkpBroadPhase*				m_broadphase;
};


#include <Physics2012/Collide/Query/Multithreaded/RayCastQuery/hkpRayCastQueryJobs.inl>

#endif // HKP_RAYCAST_QUERY_JOBS_H

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
