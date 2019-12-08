/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_CONSTRAINT_SOLVE_H
#define HKP_CONSTRAINT_SOLVE_H

#include <Physics/ConstraintSolver/Solve/hkpSolverInfo.h>
#include <Physics/Constraint/Data/hkpConstraintInfo.h>
#include <Physics/ConstraintSolver/Solve/hkpSolverElemTemp.h>

class hkpJacobianSchema;
class hkpVelocityAccumulator;
class hkSpuDmaAccessor;
class hkSpuDmaReader;
class hkpSolverResults;


//
struct hkpImpulseLimitBreachedElem
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CONSTRAINT_SOLVER, hkpImpulseLimitBreachedElem );

	HK_ALIGN16(hkUint16	  m_type);				// set to 0
	hkUint16 m_isContact;
	hkpConstraintInstance* m_constraintInstance;	// this is the value set in hkpConstraintQueryIn.m_constraintInstance
	hkpSolverResults*	  m_solverResult;		// a pointer to the solver results
};


// This class is followed by an array of hkpImpulseLimitBreachedElem
struct hkpImpulseLimitBreachedHeader
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CONSTRAINT_SOLVER, hkpImpulseLimitBreachedHeader );

	HK_ALIGN16( int m_numBreached );

		// for multi threading this points to the next array
	hkpImpulseLimitBreachedHeader* m_next;

	inline hkpImpulseLimitBreachedElem& getElem(int index){ return *(hkpImpulseLimitBreachedElem*)hkAddByteOffset(this,index*sizeof(hkpImpulseLimitBreachedElem) + sizeof(hkpImpulseLimitBreachedHeader) ); }
};


extern "C"  
{
	// info pretty much read only, but cannot be shared between threads, returns !=0 if solved
	bool HK_CALL hkSolveConstraints( const hkpSolverInfo& info, hkpJacobianSchema *schemas,  hkpVelocityAccumulator * accumulators, hkpSolverElemTemp* temp );	

	void HK_CALL hkSolveApplyGravityByTheSteps( const hkpSolverInfo& info, hkpVelocityAccumulator* accumulators, hkpVelocityAccumulator* accumulatorsEnd );

	bool HK_CALL hkSolveConstraintsByTheSteps( const hkpSolverInfo& info, int currentSolverStep, int currentSolverMicroStep, const hkpJacobianSchema *schemas,  hkpVelocityAccumulator * accumulators, hkpSolverElemTemp* temp );

	int HK_CALL hkSolveIntegrateVelocitiesByTheSteps( const hkpSolverInfo& info, int currentSolverStep, hkpVelocityAccumulator* accumulators, hkpVelocityAccumulator* accumulatorsEnd, hkBool& outSolveFinished );

	void HK_CALL hkSolveStepJacobians ( const hkpSolverInfo& i, const hkpJacobianSchema *schemas, hkpVelocityAccumulator* accumulators, hkpSolverElemTemp* tmp );

	// this function exports the result from the solver into the solver results.
	// it also exports the impulse breached constraints within the schemas memory;
	void HK_CALL hkExportImpulsesAndRhs( const hkpSolverInfo& i, const hkpSolverElemTemp* temp, const hkpJacobianSchema *schemas, const hkpVelocityAccumulator* accums );



//#if ! defined (HK_PLATFORM_SPU)
//	// This function exports the impulse breached constraints within the schemas memory. No solver results per se are exported.
//	void HK_CALL hkExportBreachedImpulses( const hkpSolverInfo& i, const hkpSolverElemTemp* temp, const hkpJacobianSchema *schemas, const hkpVelocityAccumulator* accums );
//#endif


		/// Get the violating velocities for some constraints.
		/// Contact constraint - returns min( 0.0f, seperatingVelocity ).
		/// Bilateral constraint - returns the violating velocity.
		/// All the rest return 0.0f.
		///
		/// Continues until:
		///  - the constraint is finished by finding the end mark or a new header schema.
		///  - we reach the friction part a contact constraint.
		///  - we reach maxNumVelocities.
		///
		/// Returns the number of velocities calculated.
	int HK_CALL hkSolveGetToiViolatingConstraintVelocity( hkpSolverInfo& i,	const hkpJacobianSchema *schemas, const hkpVelocityAccumulator* accums, int maxNumVelocities, hkReal* velocitiesOut );
}


#endif // HKP_CONSTRAINT_SOLVE_H

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
