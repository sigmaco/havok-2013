/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_CONSTRAINT_STABILIZATION_UTIL_H
#define HKP_CONSTRAINT_STABILIZATION_UTIL_H

#include <Physics/Constraint/Atom/hkpConstraintAtom.h>
class hkpRigidBody;

	///	This class implements utility functions used to compute stable configurations for pairs of
	///	rigid bodies constrained with various types of joints.
class hkpConstraintStabilizationUtil
{
	public:

			/// Computes a pair of scaling factors for the current inverse inertia tensors of the constrained rigid bodies, that will stabilize the
			/// ball and socket part of the given constraint. The amount of stabilization is controlled by stabilizationAmount, ranging from 0 (no
			/// stabilization) to 1 (full stabilization).
		static void HK_CALL computeBallSocketInertiaStabilizationFactors(	const class hkpConstraintInstance* constraint, const hkSimdReal& stabilizationAmount,
																			hkSimdReal& inertiaScaleOutA, hkSimdReal& inertiaScaleOutB);

			/// Changes the inertia of the given rigid body so that the constraints attached to it are stable. The amount of stabilization is controlled by
			/// stabilizationAmount, ranging from 0 (no stabilization) to 1 (full stabilization). In the case where the rigid body inertia has been stabilized,
			/// there is no need for the solver to further stabilize the constraint, so the solverStabilizationAmount can be set to 0. However, you may want to
			/// distribute part of the stabilization in the inertia and delegate the rest to the solver step, e.g., set solverStabilizationAmount to 1 and
			/// use a stabilizationAmount < 1. You should note that visual artifacts may appear in this latter case, especially when collisions are involved.
			/// Returns the number of stabilized bodies, i.e. 1 if the body was stabilized or 0 otherwise.
		static int HK_CALL stabilizeRigidBodyInertia(hkpRigidBody* rigidBody, const hkReal stabilizationAmount = 1.0f, const hkReal solverStabilizationAmount = 0.0f);

			/// Changes the inertia of the given rigid body so that given constraints in which the body is assumed to participate are stable.
			/// The amount of stabilization is controlled by stabilizationAmount, ranging from 0 (no stabilization) to 1 (full stabilization). In the case where
			/// the rigid body inertia has been stabilized, there is no need for the solver to further stabilize the constraint, so solverStabilizationAmount can be set to 0.
			/// However, you may want to distribute part of the stabilization in the inertia and delegate the rest to the solver step, e.g., set solverStabilizationAmount to 1 and
			/// use a stabilizationAmount < 1. You should note that visual artifacts may appear in this latter case, especially when collisions are involved.
			/// Returns the number of stabilized bodies, i.e. 1 if the body was stabilized or 0 otherwise.
		static int HK_CALL stabilizeRigidBodyInertia(hkpRigidBody* rigidBody, hkArray<class hkpConstraintInstance*>& constraints, const hkReal stabilizationAmount = 1.0f, const hkReal solverStabilizationAmount = 0.0f);

			/// Calls stabilizeRigidBodyInertia for all bodies in the given physics system. Returns the number of stabilized bodies.
		static int HK_CALL stabilizePhysicsSystemInertias(class hkpPhysicsSystem* physicsSystem, const hkReal stabilizationAmount = 1.0f, const hkReal solverStabilizationAmount = 0.0f);

			/// Calls stabilizeRigidBodyInertia for all bodies in the given physics world. Returns the number of stabilized bodies.
		static int HK_CALL stabilizePhysicsWorldInertias(class hkpWorld* physicsWorld, const hkReal stabilizationAmount = 1.0f, const hkReal solverStabilizationAmount = 0.0f);

	public:

			/// Sets the solving method for all given constraints.
		static void HK_CALL setConstraintsSolvingMethod(const hkArray<class hkpConstraintInstance*>& constraints, hkpConstraintAtom::SolvingMethod method);

			/// Sets the solving method for all constraints attached to the given rigid body.
		static void HK_CALL setConstraintsSolvingMethod(class hkpRigidBody* rigidBody, hkpConstraintAtom::SolvingMethod method);

			/// Sets the solving method for all constraints in the given physics system.
		static void HK_CALL setConstraintsSolvingMethod(class hkpPhysicsSystem* physicsSystem, hkpConstraintAtom::SolvingMethod method);

			/// Sets the solving method for all constraints in the given physics world.
		static void HK_CALL setConstraintsSolvingMethod(class hkpWorld* physicsWorld, hkpConstraintAtom::SolvingMethod method);
};


#endif	// HKP_CONSTRAINT_STABILIZATION_UTIL_H

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
