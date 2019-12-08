/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_SIMPLEX_SOLVER_H
#define HK_SIMPLEX_SOLVER_H

/// This represents a single constraint fed to the simplex solver
struct hkSurfaceConstraintInfo
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CONSTRAINT_SOLVER, hkSurfaceConstraintInfo );

		/// The plane direction (normally identical to the contact normal). Note: .w component is distance
	hkVector4 m_plane;

		/// The velocity of the plane
	hkVector4 m_velocity;

		/// The static friction (behaves pretty much as expected from real friction)
	hkReal m_staticFriction;

		/// An extra friction in the up direction, if this function is used (value != 0), then
		/// the overall friction will be split into two components:
		///  - one in the most up direction.
		///  - one which is perpendicular to the up direction.
		/// Then each component is solved separately (box friction instead of friction circle)
	hkReal m_extraUpStaticFriction;

		/// Extra friction downward.
	hkReal m_extraDownStaticFriction;

		/// The dynamic friction:
		///  - if set to 1.0f, then the simplex will simply project the velocity onto each plane.
		///  - if set to 0.0f, then the algorithm will try to maintain the input velocity.
	hkReal    m_dynamicFriction;

		/// The relative priority of the surface
	int		  m_priority;
};

/// The input structure for the simplex solver
struct hkSimplexSolverInput
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CONSTRAINT_SOLVER, hkSimplexSolverInput );

	inline hkSimplexSolverInput();

		/// The position of the particle
	hkVector4 m_position;

		/// The velocity of the particle
	hkVector4 m_velocity;

		/// This value is used by the simplex solver to decide whether to solve planes
		/// simultaneously or not. The problem is that when two planes are nearly parallel
		/// the simultaneous (and correct) solution to the problem can be a very large vector.
		/// It is often preferable to penetrate a plane, to avoid this result. This value
		/// is used by the solver to determine when to penetrate a plane rather than solve
		/// planes simultaneously. If a simultaneous solve results in a velocity greater than
		/// this value, then the solver will disregard this result and solve the planes
		/// sequentially. In this case, the output will be penetrating the lowest priority
		/// plane.
	hkVector4 m_maxSurfaceVelocity;

		/// This is used in conjunction with the box friction model
	hkVector4 m_upVector;

		/// The timeslice
	hkReal	  m_deltaTime;

		/// The minimum time we should walk before exiting
	hkReal	  m_minDeltaTime;

		/// The input array of surface constraints
	hkSurfaceConstraintInfo* m_constraints;

		/// The number of constraints in the array
	int	m_numConstraints;
};


/// Contains the simplex results for each surface constraint
struct hkSurfaceConstraintInteraction
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CONSTRAINT_SOLVER, hkSurfaceConstraintInteraction );

	/// The status of the internal solving. Note: this list is order dependent
	enum hkStatus
	{
			/// OK.
		HK_STATUS_OK = 0,
			/// 3D Failure.
		HK_STATUS_3D_FAILURE = 1,
			/// 2D Failure.
		HK_STATUS_2D_FAILURE = 2
	};

		/// If m_touched is set to true, then the characterController touched this plane
	hkUint8      m_touched;

		/// If this value is set to true, then the simplex had to kill the velocity of this plane to find a successful solution
	hkUint8      m_stopped;
		
		/// The time spent in contact with this surface
	hkReal    m_surfaceTime;

	hkReal    m_penaltyDistance;	// for internal use only

	hkStatus  m_status;
};

/// Output structure for the simplex solver.
struct hkSimplexSolverOutput
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CONSTRAINT_SOLVER, hkSimplexSolverOutput );

		/// Position.
	hkVector4		  m_position;

		/// Velocity.
	hkVector4		  m_velocity;

		/// The time solved to if the output m_deltaTime is < the input m_deltaTime then the simplex hit a surface.
		/// Continue to iterate to complete the timestep
	hkReal			  m_deltaTime;

		/// The output interaction array - this should be the same size as the input constraints array
	hkSurfaceConstraintInteraction* m_planeInteractions;
};

extern "C"
{
		// Solves for the motion of a particle in a set on dynamic plane constraints
	void HK_CALL hkSimplexSolverSolve( const hkSimplexSolverInput& input, hkSimplexSolverOutput& output );

}

hkSimplexSolverInput::hkSimplexSolverInput()
{
	m_upVector.set(0.f,1.f,0.f);
	m_maxSurfaceVelocity.setAll( hkSimdReal_Eps );
	m_position.setZero();
}

#endif //HK_SIMPLEX_SOLVER_H

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
