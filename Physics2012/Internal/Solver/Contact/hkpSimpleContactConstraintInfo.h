/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_SIMPLE_CONTACT_CONSTRAINT_INFO_H
#define HKP_SIMPLE_CONTACT_CONSTRAINT_INFO_H

#include <Physics/ConstraintSolver/Solve/hkpSolverResults.h>

extern const class hkClass hkpSimpleContactConstraintDataInfoClass;

class hkpConstraintQueryIn;
class hkpConstraintQueryOut;
class hkContactPoint;
class hkpContactPointProperties;
struct hkpSimpleContactConstraintAtom; 



class hkpSimpleContactConstraintDataInfo
{
	//+version(2)
	public:

		HK_DECLARE_REFLECTION();
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CONSTRAINT_SOLVER, hkpSimpleContactConstraintDataInfo );

		enum
		{
			HK_FLAG_OK				= 0x00,
			HK_FLAG_POINT_REMOVED	= 0x01,
			HK_FLAG_AREA_CHANGED	= 0x04
		};

		void init()
		{
			m_flags = HK_FLAG_OK;
			m_biNormalAxis = 3;
			m_contactRadius = 0.0f;
			m_internalData1.setZero();
			m_rhsRolling[0].setZero();
			m_rhsRolling[1].setZero();
			m_rollingFrictionMultiplier.setZero();
			for(int i = 0; i < 4; ++i)
			{
				m_data[i] = 0;
			}
		}

		hkpSimpleContactConstraintDataInfo() 
		{
			init();
		}

		HK_ALIGN16(hkUint16 m_flags);
		hkUint16 m_biNormalAxis;
		hkHalf m_rollingFrictionMultiplier;
		hkHalf m_internalData1;
		hkHalf m_rhsRolling[2];
		hkReal m_contactRadius;
		HK_ALIGN(hkReal m_data[4],HK_REAL_SIZE);

		hkpSimpleContactConstraintDataInfo(hkFinishLoadedObjectFlag f) {}
};


class hkpSimpleContactConstraintDataInfoInternal
{
	public:

		enum
		{
			HK_FLAG_OK				= 0x00,
			HK_FLAG_POINT_REMOVED	= 0x01,
			HK_FLAG_AREA_CHANGED	= 0x04
		};

		hkpSimpleContactConstraintDataInfoInternal() : m_flags(HK_FLAG_OK) {}
		
		HK_ALIGN_REAL(hkUint16 m_flags);
		
		// a guess for a biNormal of the friction contact point,
		// it will be updated each frame by projecting it's old direction onto the plane defined by the friction point normal
		hkUint16 m_biNormalAxis;

		// the radius of the contactArea, this gets updated every time a contact point is added or removed

		hkHalf m_rollingFrictionMultiplier;
		hkHalf m_rollingImpulseSqr;
		hkHalf m_rhsRolling[2];

		hkReal m_contactRadius;
		hkReal m_impulseSqr; // this includes impulses for lin, lin, and ang
		hkReal m_rhsAng;
		HK_ALIGN(hkReal m_rhsLin[2],HK_REAL_SIZE);
};


/// This parameter helps to tune penetration recovery of contacts. This is
/// especially useful:
///   - For non standard sized worlds: set it to how quickly deep penetrating objects should separate
///   - Or if you run the solver at a high number of iterations, you should set:
///         HK_CONTACT_LINEAR_ERROR_RECOVERY_VELOCITY = 10/solverIterations
extern hkReal HK_CONTACT_LINEAR_ERROR_RECOVERY_VELOCITY;
extern hkReal HK_CONTACT_EXPONENTIAL_ERROR_RECOVERY_VELOCITY;


extern "C"
{
		/// Build the Jacobian for a contact constraint.
	void HK_CALL hkSimpleContactConstraintDataBuildJacobian( hkpSimpleContactConstraintAtom* atom, const hkpConstraintQueryIn& in, hkBool writeHeaderSchema, hkpConstraintQueryOut& out );

	void HK_CALL hkSimpleContactConstraintDataAddALittleSurfaceViscosity( hkpSimpleContactConstraintDataInfo* info );
}


#endif // HKP_SIMPLE_CONTACT_CONSTRAINT_INFO_H

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
