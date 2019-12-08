/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#ifndef HKP_VEHICLE_FRICTION_SOLVER_H
#define HKP_VEHICLE_FRICTION_SOLVER_H

#include <Physics/ConstraintSolver/VehicleFriction/hkpVehicleFriction.h>
#include <Physics/ConstraintSolver/Accumulator/hkpVelocityAccumulator.h>


/// The class hkVehicleFrictionSolver is used is an input and output to the vehicle dynamics.
/// It holds all values which change every frame.
struct hkpVehicleFrictionSolverAxleParams
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_ACTION, hkpVehicleFrictionSolverAxleParams);
		
		/// Initializes all data members to default values.
		inline void initialize();

	public:

		//
		//	Geometry of the vehicle
		//

		hkVector4 m_contactPointWs;
		hkVector4 m_constraintNormalWs;
		hkVector4 m_forwardDirWs;

		//
		//	Ground Object
		//

		hkpVelocityAccumulator* m_groundObject;
		hkpVelocityAccumulator* m_groundObjectAtLastIntegration;

		//
		// Friction Info: 
		//  formula:   finalFriction = min( m_maxFrictionCoefficient, m_frictionCoefficient + slipVelocity * m_viscosityFrictionCoefficient );
		//             maxForce = finalFriction * m_wheelDownForce
		//

		hkReal	m_frictionCoefficient;
		hkReal	m_viscosityFrictionCoefficient;
		hkReal  m_maxFrictionCoefficient;
		hkReal	m_wheelDownForce;

		/// The net combined braking and transmission force applied at the surface of a wheel.
		/// If the total force applied at the wheel (forward force and side force) exceed a threshold then the wheel will slide.
		hkReal	m_forwardForce;

		/// This parameter defines how fast the vehicle tyres will slip (not slide)
		/// if the sideforce = downforce (that means the vehicle is standing on a 45 degree slope).
		/// The purpose of this parameter is to control the slip angle of the wheel:
		/// Assume you want to have a slip angle of 0.1 radians for a car cornering with 0.6g while driving
		/// at 20 meters/second. In this case you set m_slipVelocityFactor to (sin(0.1f) * 20.0f)/0.6g.
		/// This parameter only works if the velocity of the car is greater than params.m_maxVelocityForPositionalFriction
		hkReal  m_slipVelocityFactor;

		//
		//	Handbrake Info
		//

		hkUint8	m_wheelFixed;
};

inline void hkpVehicleFrictionSolverAxleParams::initialize()
{
	m_contactPointWs.setZero();
	m_constraintNormalWs.setZero();
	m_forwardDirWs.setZero();
	m_frictionCoefficient = hkReal(0);
	m_viscosityFrictionCoefficient = hkReal(0);
	m_maxFrictionCoefficient = hkReal(0);
	m_wheelDownForce = hkReal(0);
	m_forwardForce = hkReal(0);
	m_wheelFixed = false;
	m_groundObject = HK_NULL;
	m_groundObjectAtLastIntegration = HK_NULL;
	m_slipVelocityFactor = hkReal(0);
}


/// The class hkpVehicleFrictionSolverParams is used by vehicle dynamics.
/// See hkRaycastVehicle for more details.
struct hkpVehicleFrictionSolverParams
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_ACTION, hkpVehicleFrictionSolverParams);

	public:

		hkpVehicleFrictionSolverAxleParams m_axleParams[2];/*HK_VEHICLE_FRICTION_N_AXIS*/

		hkReal m_maxVelocityForPositionalFriction;

		hkpVelocityAccumulator m_chassis;
		hkpVelocityAccumulator m_chassisAtLastIntegration;
};


extern "C"
{
		/// Setup internal cache information hkpVehicleFrictionDescription for fast solving of the vehicle.
	void hkVehicleFrictionDescriptionInitValues( const hkpVehicleFrictionDescription::Cinfo& ci, hkpVehicleFrictionDescription& out);

		/// Solve the vehicle friction.
	void hkVehicleFrictionApplyVehicleFriction(	const hkpVehicleStepInfo& stepInfo,
												const hkpVehicleFrictionDescription& descr,
												hkpVehicleFrictionSolverParams &params,
												hkpVehicleFrictionStatus &status);
}


#endif // HKP_VEHICLE_FRICTION_SOLVER_H

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
