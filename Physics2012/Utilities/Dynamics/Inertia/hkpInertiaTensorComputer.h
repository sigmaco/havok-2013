/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_DYNAMICS2_INERTIA_TENSOR_COMPUTER_H
#define HK_DYNAMICS2_INERTIA_TENSOR_COMPUTER_H

#include <Common/GeometryUtilities/Inertia/hkInertiaTensorComputer.h>

extern const class hkClass hkMassPropertiesClass;

struct hkGeometry;
class hkcdShape;
class hkpShape;
class hkpRigidBodyCinfo;
class hkpRigidBody;
class hkpConstraintInstance;
struct hkStridedVertices;



/// A class to compute the inertia tensor, center of mass and volume of various classes of objects.
class hkpInertiaTensorComputer: public hkInertiaTensorComputer
{
	public:


		///////////////////////////////////////
		// "Shape" calculation 
		///////////////////////////////////////

			/// Computes the inertia tensor and the center of mass given a total mass for a hkcdShape (using "volume" methods).
			/// N.B. Every child shape of the shape passed in MUST have a volume. Triangles are given a minimum thickness of 0.01f
		static void HK_CALL computeShapeVolumeMassProperties(const hkcdShape* shape, hkReal mass, hkMassProperties &result);

			/// "Shape" calculation and assignment to a hkpRigidBodyCinfo (using "volume" methods).
			/// Useful for 1-line RigidBody mass property calculation.
			/// N.B. Every child shape of the shape passed in MUST have a volume. Triangles are given a minimum thickness of 0.01f
		static void HK_CALL setShapeVolumeMassProperties(const hkpShape* shape, hkReal mass, hkpRigidBodyCinfo& bodyInfo);

			/// assignment to a hkpRigidBodyCinfo (using "volume" methods).
		static void HK_CALL setMassProperties(const hkMassProperties& props, hkpRigidBodyCinfo& bodyInfo);

			/// assignment to a hkpRigidBodyCinfo (using "volume" methods).
		static void HK_CALL setAndScaleToDensity(const hkMassProperties& props, hkSimdRealParameter density, hkpRigidBodyCinfo& bodyInfo);

			/// assignment to a hkpRigidBodyCinfo (using "volume" methods).
		static void HK_CALL setAndScaleToMass(const hkMassProperties& props, hkSimdRealParameter mass, hkpRigidBodyCinfo& bodyInfo);


			/// Increase the inertia of all axes to be at least (max(inertia of all axes)/maxInertiaRatio)
		static void HK_CALL clipInertia(hkReal maxInertiaRatio, hkpRigidBodyCinfo& bodyInfo);

		///////////////////////////////////////
		// Inertia Tensor Simplification  
		///////////////////////////////////////


			/// Recompute the inertia tensors of a constraint tree.
			/// The idea is that bodies up in the hierarchy should not get an inertia tensor smaller than the inertia
			/// of its children.
			/// The overall inertia of the constraint tree should not change significantly, however the individual inertias
			/// can change a lot.
			/// The purpose of the function is to make motors and constraint limits of a ragdoll
			/// much stiffer, without changing the "normal" behavior of the ragdoll visibly.
			/// Set inertiaFactorHint to 1 if you want the minimal amount of inertia increase,
			/// set inertiaFactorHint to > 1 (e.g. 5) if you allow for higher inertia increase
		static void HK_CALL optimizeInertiasOfConstraintTree( hkpConstraintInstance*const* constraints, int numConstraints, hkpRigidBody* rootBody, hkReal inertiaFactorHint = 1.5f );
};



#endif // HK_DYNAMICS2_INERTIA_TENSOR_COMPUTER_H

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
