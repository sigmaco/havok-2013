/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef INC_HK_TAPEREDCAPSULE_OBJECT_INTERFACE__H
#define INC_HK_TAPEREDCAPSULE_OBJECT_INTERFACE__H

// Class ID
#define HK_TAPEREDCAPSULE_CLASS_ID Class_ID(0x4d8357c2, 0x20855371)

// Normal Parameter Blocks
enum
{
	PB_TAPEREDCAPSULE_OBJ_PBLOCK, // has two rollouts
};

// Normal Parameters
enum
{
	// GENERAL PROPERTIES ROLLOUT
	PA_TAPEREDCAPSULE_OBJ_RADIUS = 0,
	PA_TAPEREDCAPSULE_OBJ_TAPER,	
	PA_TAPEREDCAPSULE_OBJ_HEIGHT,				
	PA_TAPEREDCAPSULE_OBJ_VERSION_INTERNAL,			
};

#endif //INC_HK_TAPEREDCAPSULE_OBJECT_INTERFACE__H

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
