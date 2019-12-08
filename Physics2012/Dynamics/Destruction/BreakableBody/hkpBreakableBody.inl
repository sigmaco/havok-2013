/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#include <Physics2012/Dynamics/Destruction/Utilities/hkpDestructionSpuUtil.h>

//
//	Called by the runtime to return the breakable threshold (i.e. strength) of the given breakable body at the given shape key

inline hkBool HK_CALL hkpBreakableBody::Controller::getBodyStrengthAt(const hkpBreakableBody* breakableBodySpu, const hkpRigidBody* rigidBodySpu, hkpShapeKey impactShapeKey, hkUFloat8& shapeKeyStrengthOut)
{
	// Get controller
	Controller* controllerPpu = const_cast<Controller*>(breakableBodySpu->m_controller.val());

	// Dispatch to specific functionality based on controller type
	if ( controllerPpu )
	{
		HK_DECLARE_SPU_LOCAL_DESTRUCTION_PTR(Controller, controllerSpu, sizeof(Controller));
		HK_DOWNLOAD_DESTRUCTION_PTR_TO_SPU(controllerSpu, controllerPpu, sizeof(Controller));

		// Download controller on SPU
		const hkReal strengthOverride = controllerSpu->getBreakingImpulse();
		if ( strengthOverride >= 0.0f )
		{
			shapeKeyStrengthOut = hkFloat32(strengthOverride);
			return true;
		}
	}

	// Default implementation simply requests the strength from the shape
	{
		// Download breakable shape on SPU
		hkpBreakableShape* breakableShapePpu = const_cast<hkpBreakableShape*>(breakableBodySpu->m_breakableShape.val());
		HK_DECLARE_SPU_LOCAL_DESTRUCTION_PTR(hkpBreakableShape, breakableShapeSpu, sizeof(hkpBreakableShape));
		HK_DOWNLOAD_DESTRUCTION_PTR_TO_SPU(breakableShapeSpu, breakableShapePpu, sizeof(hkpBreakableShape));
	
		// Download its material on SPU. You can override the material here!
		hkpBreakableMaterial* rootMtlPpu =  const_cast<hkpBreakableMaterial*>(breakableShapeSpu->getMaterial());
		if ( rootMtlPpu )
		{
			// Download maximum material size on SPU
			HK_DECLARE_SPU_LOCAL_DESTRUCTION_PTR(hkpBreakableMaterial, rootMtlSpu, hkpBreakableMaterialUtil::MAX_MATERIAL_SIZE);
			HK_DOWNLOAD_DESTRUCTION_PTR_TO_SPU(rootMtlSpu, rootMtlPpu, hkpBreakableMaterialUtil::MAX_MATERIAL_SIZE);

			// Get the shape key strength, based on the material
			return hkpBreakableShape::getShapeKeyStrength(breakableShapeSpu, rootMtlSpu, impactShapeKey, shapeKeyStrengthOut);
		}
	}

	// No material, return not breakable!
	return false;
}

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
