/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef INC_HK_FIXED_CONSTRAINT_MODIFIER_INTERFACE__H
#define INC_HK_FIXED_CONSTRAINT_MODIFIER_INTERFACE__H

// Class ID
#define HK_CONSTRAINT_FIXED_CLASS_ID Class_ID(0x18600a44, 0x7111456d)

// Parameter Blocks
enum
{
	PB_FIXED_MOD_PBLOCK = PB_CONSTRAINT_MOD_FIRST_FREE_PARAMBLOCK
};

// Parameters
enum
{
	PA_FIXED_MOD_MAX_LIN_IMPULSE = 0,
	PA_FIXED_MOD_MAX_ANG_IMPULSE,
};

#endif //INC_HK_FIXED_CONSTRAINT_MODIFIER_INTERFACE__H

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
