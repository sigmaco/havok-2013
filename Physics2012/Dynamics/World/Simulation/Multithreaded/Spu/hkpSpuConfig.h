/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_SPU_CONFIG_H
#define HK_SPU_CONFIG_H

#include <Physics2012/Collide/Query/Multithreaded/Spu/hkpSpuConfig.h>
#include <Physics2012/Collide/Agent/hkpProcessCollisionData.h>
#include <Physics/ConstraintSolver/Solve/hkpSolve.h>

	//
	//	Note: This file references symbols in other files.
	//  You might have to include another file to use them properly
	//

//  Important:  after modifying those values, check that you have at least 16k left for the normal stack
//				Also use the simulator to verify this size


// ************************************************************************
// *******  General defines and limits of the engine                 ******
// *******  These values are Havok tunable + require a full rebuild  ******
// ************************************************************************

			// The maximum number of contact points which are created between 2 objects
		#define HK_MAX_NUM_CONTACT_POINTS_IN_CONSTRAINT_ON_SPU      HK_MAX_CONTACT_POINT

			// The size of the cache lines on SPU. Only collision agents using shapes
			// with a size smaller than this value are processed on the spu; all others are left on PPU.
		#define HK_SPU_AGENT_SECTOR_JOB_MAX_SHAPE_SIZE					HK_SPU_MAXIMUM_SHAPE_SIZE
		#define HK_SPU_AGENT_SECTOR_JOB_MAX_UNTYPED_CACHE_LINE_SIZE		HK_SPU_UNTYPED_CACHE_LINE_SIZE
		#define	HK_SPU_AGENT_SECTOR_JOB_MOPP_CACHE_LINE_SIZE			512

			// The maximum number of jacobians for a normal constraint (excluding contact point constraint)
			// This maximum is currently reached by a powered ragdoll constraint with friction and limits (hkpRagdollConstraintData::Runtime)
		#define HK_SPU_CONSTRAINT_RUNTIME_BUFFER_SIZE (16 * 11) 

			// This is the maximum number of hits in a MOPP query, this includes the HK_INVALID_SHAPE_KEY end flag
		#define HK_MAX_AGENTS_IN_1N_MACHINE			HK_MAX_NUM_HITS_PER_AABB_QUERY


// ******************************************************
// *******  General flags to tune the performance  ******
// *******  client rebuild required                ******
// ******************************************************

	//
	// Collision detection buffers 
	//

			// This is the size of the top level shape cache cache. A cache miss is not really expensive, as the DMA is prefetched.
			// Must be power of 2, minimum 1k
		#define HK_SPU_AGENT_SECTOR_JOB_ROOT_SHAPE_CACHE_SIZE		2048

			// This is the cache used by the user of shapes with child shapes. A cache miss is stalling and expensive
			// Must be power of 2, minimum 1k
		#define HK_SPU_AGENT_SECTOR_JOB_UNTYPED_CACHE_SIZE			4096

			// This is the cache used by the MOPP.
			// Must be power of 2, minimum 2k
		#define HK_SPU_AGENT_SECTOR_JOB_MOPP_CACHE_SIZE				8192
		#define HK_SPU_AGENT_SECTOR_JOB_MOPP_CACHE_SIZE_MIN			2048


// *******************************************************
// ******* Internal data, don't touch               ******
// *******************************************************

	//
	// Collision detection
	//

			// the number of rows, each of them has 4 lines
		enum { HK_SPU_AGENT_SECTOR_JOB_ROOT_SHAPE_NUM_CACHE_ROWS    = HK_SPU_AGENT_SECTOR_JOB_ROOT_SHAPE_CACHE_SIZE / (4*HK_SPU_AGENT_SECTOR_JOB_MAX_SHAPE_SIZE) };
		enum { HK_SPU_AGENT_SECTOR_JOB_UNTYPED_NUM_CACHE_ROWS		= HK_SPU_AGENT_SECTOR_JOB_UNTYPED_CACHE_SIZE    / (4*HK_SPU_AGENT_SECTOR_JOB_MAX_UNTYPED_CACHE_LINE_SIZE) };
		enum { HK_SPU_AGENT_SECTOR_JOB_MOPP_NUM_CACHE_ROWS			= HK_SPU_AGENT_SECTOR_JOB_MOPP_CACHE_SIZE       / (4*HK_SPU_AGENT_SECTOR_JOB_MOPP_CACHE_LINE_SIZE) };

		enum { HK_SPU_TOTAL_PHYSICS_BUFFER_SIZE						= 56000 + HK_SPU_AGENT_SECTOR_JOB_ROOT_SHAPE_CACHE_SIZE + HK_SPU_AGENT_SECTOR_JOB_UNTYPED_CACHE_SIZE + HK_SPU_AGENT_SECTOR_JOB_MOPP_CACHE_SIZE };

			// reduced versions (for static compound ELF)
		enum { HK_SPU_AGENT_SECTOR_JOB_MOPP_NUM_CACHE_ROWS_MIN		= HK_SPU_AGENT_SECTOR_JOB_MOPP_CACHE_SIZE_MIN  / (4*HK_SPU_AGENT_SECTOR_JOB_MOPP_CACHE_LINE_SIZE) };
		enum { HK_SPU_TOTAL_STATIC_COMPOUND_ELF_BUFFER_SIZE			= 54000 + HK_SPU_AGENT_SECTOR_JOB_ROOT_SHAPE_CACHE_SIZE + HK_SPU_AGENT_SECTOR_JOB_UNTYPED_CACHE_SIZE + HK_SPU_AGENT_SECTOR_JOB_MOPP_CACHE_SIZE_MIN };

	//
	//	Solver
	//
	
			// - for schemas writer, when this buffer is full a DMA write is triggered
		#define HK_SPU_SCHEMA_WRITER_BASE_BUFFER_SIZE (1024 + 128) 

			// this is the overflow buffer size. 
			// it has to accommodate the entire max contact constraint == some 6000 bytes ??
			// it also has to accommodate all the modifiers that my be attached to the constraint
		enum { HK_SPU_SCHEMA_WRITER_OVERFLOW_BUFFER_SIZE = (128 + (HK_MAX_CONTACT_POINT/2) * hkpJacobianSchemaInfo::PairContact::Sizeof + (HK_MAX_CONTACT_POINT%2) * hkpJacobianSchemaInfo::SingleContact::Sizeof + hkpJacobianSchemaInfo::Friction3D::Sizeof + hkpJacobianSchemaInfo::Header::Sizeof + 2 *(hkpJacobianSchemaInfo::SetMass::Sizeof + hkpJacobianSchemaInfo::AddVelocity::Sizeof + hkpJacobianSchemaInfo::SetCenterOfMass::Sizeof) + 3 * hkpJacobianSchemaInfo::Header::Sizeof), };
		                                                  
		#define HK_SPU_SOLVE_SCHEMA_READER_BASE_BUFFER_SIZE     (512)
		#define HK_SPU_SOLVE_SCHEMA_READER_OVERFLOW_BUFFER_SIZE (1024)	
		enum { HK_SPU_SOLVE_MORE_LESS_MAX_SIZE_OF_CONTACT_SCHEMAS_WITHOUT_BUFFER_CHECK = (4 * hkpJacobianSchemaInfo::PairContact::Sizeof + hkpJacobianSchemaInfo::SingleContact::Sizeof + 1 * hkpJacobianSchemaInfo::Header::Sizeof + (hkpJacobianSchemaInfo::SetMass::Sizeof + 2 * hkpJacobianSchemaInfo::AddVelocity::Sizeof + hkpJacobianSchemaInfo::SetCenterOfMass::Sizeof)), };
			// this below is 880
		enum { HK_SPU_SOLVE_MORE_THAN_MAX_SIZE_OF_CONTACT_SCHEMAS_WITHOUT_BUFFER_CHECK		= ( 4 * hkpJacobianSchemaInfo::PairContact::Sizeof + hkpJacobianSchemaInfo::SingleContact::Sizeof + 4 * hkpJacobianSchemaInfo::Header::Sizeof + 2 * (hkpJacobianSchemaInfo::SetMass::Sizeof + hkpJacobianSchemaInfo::AddVelocity::Sizeof + hkpJacobianSchemaInfo::SetCenterOfMass::Sizeof)), };

	

			// solverTempElems for ragdoll:
			// 3 * (frictionAngular+motorAngular+limitAngular+linear) == 3 * (2+3+1+1)  = 21 
			// solverTempElems for contact point (we have accessor checks every 8th contact point)
			// ((8+1) * cp + 3d friction) == (8+1) * 1 + 4 = 13 
		#define HK_SPU_SOLVE_ELEM_TEMP_READER_BASE_BUFFER_SIZE		256 
		#define HK_SPU_SOLVE_ELEM_TEMP_READER_OVERFLOW_BUFFER_SIZE	128  

			// Solver export : solver results writer buffer sizes
		#define HK_SPU_SOLVE_RESULTS_WRITER_BASE_BUFFER_SIZE 512 
		#define HK_SPU_SOLVE_RESULTS_WRITER_OVERFLOW_BUFFER_SIZE 128

			// - for accumulator fetching (sizeof(hkpVelocityAccumulator) == 128, cacheRow = 4*cacheLine, cacheLine = hkpVelocityAccumulator + 2*int)
		#define HK_SPU_ACCUMULATOR_CACHE_NUM_CACHE_ROWS			16 

			// - for constraintAtoms
		#define HK_CONSTRAINTATOM_SIZE_PER_CONTACT_POINT (sizeof(hkContactPoint) + sizeof(hkpContactPointProperties))
		#define HK_SPU_CONSTRAINT_ATOM_BUFFER_SIZE ( HK_NEXT_MULTIPLE_OF(16, HK_MAX_NUM_CONTACT_POINTS_IN_CONSTRAINT_ON_SPU * HK_CONSTRAINTATOM_SIZE_PER_CONTACT_POINT) + sizeof(hkpSimpleContactConstraintAtom)) 


// **********************************
// ******* Internal dma groups ******
// **********************************

		// These groups are for reference only.
		// If you use sub functions to the relevant jobs,
		// you should avoid conflicts with DMA groups

		/// DMA groups used by the Jacobians builder.
	namespace hkSpuBuildJacobiansJobDmaGroups
	{
		enum
		{
			GET_QUERYIN_DMA_GROUP							= 0,
			GET_DATA_BASE_DMA_GROUP							= 1, // we are using double buffering, so we need to reserve 2 DMA groups for this!
			WRITE_BACK_CONTACT_CONSTRAINT_ATOM_DMA_GROUP	= 3,
			WRITE_BACK_RUNTIME_DMA_GROUP					= 4,
			// next free dma group to use: 5
		};
	}

	namespace hkSpuAgentSectorJobDmaGroups
	{
		enum
		{
			GET_ELEMENT_PTRS_DMA_GROUP	= 1,
			GET_ENTRY_DATA_DMA_GROUP	= 2, // we use 5 pipeline stages, so we need to reserve 5 DMA groups
			GET_BIG_ATOMS_DMA_GROUP		= 7,
			GET_UNTYPED_CACHE_DATA		= 8,
			SHAPE_KEY_TRACK_DMA_GROUP	= 9  // Only used in split pipeline.
		};
	}

	namespace hk1nMachineDmaGroups	// these groups should not collide with hkSpuAgentSectorJobDmaGroups
	{
		enum
		{
			GET_SECTOR_POINTERS_DMA_GROUP = 10,
			GET_SECTOR_DMA_GROUP          = 12,
			WRITE_SECTOR_DMA_GROUP        = 14,
		};
	}

#endif // HK_SPU_CONFIG_H

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
