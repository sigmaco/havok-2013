/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_CONSTRAINT_CHAIN_LENGTH_UTIL_H
#define HKP_CONSTRAINT_CHAIN_LENGTH_UTIL_H

#include <Physics2012/Dynamics/Constraint/Chain/hkpConstraintChainInstance.h>
#include <Physics2012/Dynamics/Constraint/Chain/BallSocket/hkpBallSocketChainData.h>
#include <Physics2012/Dynamics/Entity/hkpRigidBodyCinfo.h>

class hkpConstraintChainInstance;
class hkpBallSocketChainData;


class hkpConstraintChainLengthUtil
{
	public: 

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_DEMO, hkpConstraintChainLengthUtil);

		struct RopeInfo
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_DEMO, hkpConstraintChainLengthUtil::RopeInfo);

			hkVector4 m_settings; // cableCrossSection, materialDensity, segmentLength, materialStretchingConstant
			hkSimdReal m_inertiaMultiplier;

			RopeInfo() 
			{
				m_settings.set( 28.0f * 1e-4f,  // [m2]
								6.7f * 1e3f,    // [kg/m3]
								0.30f,		    // [m]
								280.0f * 1e6f); // [N]
				m_inertiaMultiplier = hkSimdReal_1;
			}

			HK_FORCE_INLINE const hkSimdReal getCableCrossSection() const  { return m_settings.getComponent<0>(); }
			HK_FORCE_INLINE const hkSimdReal getMaterialDensity() const    { return m_settings.getComponent<1>(); }
			HK_FORCE_INLINE const hkSimdReal getSegmentLength() const      { return m_settings.getComponent<2>(); }
			HK_FORCE_INLINE const hkSimdReal getMaterialStretching() const { return m_settings.getComponent<3>(); }
		};


		RopeInfo m_ropeInfo;
		hkVector4 m_pivotOnCrane;
		hkpRigidBodyCinfo m_segmentCinfo;
		hkpConstraintChainInstance* m_instance;

		hkSimdReal m_currentUnstretchedLength;

		int m_numLoadBodies;

	private:

		hkpConstraintChainLengthUtil(); // only allow creation via create functions.

	public:

		// Creates rope from hook, to crane pivot. Sets the unstretched length of the rope to the exact distance from load to crane pivot.
		// A length rope of at least two segmentLengths is needed, otherwise it should auto add extra segments.
		hkpConstraintChainLengthUtil(const RopeInfo& info, hkpRigidBody* craneBody, hkVector4Parameter pivotOnCrane, hkVector4Parameter ropeEndInWorld);

		~hkpConstraintChainLengthUtil();

		void attachHook(hkpRigidBody* hookBody, hkVector4Parameter pivotOnHook);
			
		void attachLoad(hkpRigidBody* loadBody, hkVector4Parameter pivotOnLoad, hkVector4Parameter pivotOnHook);

		void detachHookOrLoad();

		HK_FORCE_INLINE const hkSimdReal getUnstretchedLength() { return m_currentUnstretchedLength; }

		void setUnstretchedLength(hkSimdRealParameter length);

		void updatePivotOnStretchedRope(); // just use the stretch above. simple. // consider also multiplying the inertia of the topmost element to compensate for the longer arm.

		void updateChainProperties(hkSimdRealParameter solverStepDeltaTime, int numSolverMicroSteps, hkSimdRealParameter solverTau);

		void getRopeBodies(hkArray<hkpRigidBody*>& ropeBodies);

		hkpBallSocketChainData* getChainData() { return (hkpBallSocketChainData*)m_instance->getData(); }
		const hkpBallSocketChainData* getChainData() const { return (const hkpBallSocketChainData*)m_instance->getData(); }

		const hkVector4 getSegmentAPivot() const { hkVector4 p; p.setMul(hkVector4::getConstant<HK_QUADREAL_0010>(), hkSimdReal_Inv2 * m_ropeInfo.getSegmentLength()); return p; }
		const hkVector4 getSegmentBPivot() const { hkVector4 p; p.setMul(hkVector4::getConstant<HK_QUADREAL_0010>(),-hkSimdReal_Inv2 * m_ropeInfo.getSegmentLength()); return p; }

		int getNumSegments(hkSimdRealParameter length) const;

		const hkVector4 getLastSegmentAPivot() const;

		const hkSimdReal getStretchAtCraneLess1() const;

		const hkSimdReal getStretchAtCrane() const;

	private:

		void updateConstraintInstanceBaseEntities(hkpConstraintChainInstance* chain);
};


#endif	// HKP_CONSTRAINT_CHAIN_LENGTH_UTIL_H

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
