/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_SOLVER_RESULTS_H
#define HKP_SOLVER_RESULTS_H


/// Constraint solver results. This class is used internally by the system, however it may be used to query the results
/// of the constraint solver for this constraint on the last solve() call.
class hkpSolverResults
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CONSTRAINT_SOLVER, hkpSolverResults );
		
		/// Get the impulse applied by the solver on the last time step. This structure may be returned prior to the application of the
		/// constraint solver. For the case of a contact constraint it is initialized to a very crude guess at the expected initial impulse.
		HK_FORCE_INLINE hkReal getImpulseApplied() const;

		// internal use only
		HK_FORCE_INLINE hkpSolverResults();

		// internal use only
		HK_FORCE_INLINE void init();

	public:
		
		// internal use only
		hkReal m_impulseApplied;

		// internal use only
		hkReal m_internalSolverData;
};

#include <Physics/ConstraintSolver/Solve/hkpSolverResults.inl>


#endif // HKP_SOLVER_RESULTS_H

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
