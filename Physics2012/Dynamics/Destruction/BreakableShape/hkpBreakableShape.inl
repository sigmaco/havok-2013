/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

//
//	Returns the breaking threshold for the given shape key

hkBool HK_CALL hkpBreakableShape::getShapeKeyStrength(const hkpBreakableShape* rootBreakableShapeSpu, const hkpBreakableMaterial* rootMaterialSpu, hkpShapeKey shapeKey, hkUFloat8& shapeKeyStrengthOut)
{
	HK_ASSERT(0x71e403ca, rootMaterialSpu);

	// Get the sub-material if any, for the given shape key
	// If the shape key is invalid, we'll use the root material; we cannot locate the proper child anyway.
	if ( shapeKey != HK_INVALID_SHAPE_KEY )
	{
		// Get physics shape pointer on PPU
		const hkcdShape* physicsShapePpu = rootBreakableShapeSpu->getPhysicsShape();
		return hkpBreakableMaterialUtil::getSubShapeMaterialStrength(rootMaterialSpu, physicsShapePpu, shapeKey, shapeKeyStrengthOut);
	}

	// Return the root material strength
	if ( rootMaterialSpu->isBreakable() )
	{
		rootMaterialSpu->getEncodedMaterialStrength(shapeKeyStrengthOut);
		return true;
	}
	
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
