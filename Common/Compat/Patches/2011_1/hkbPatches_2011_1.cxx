/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Behavior specific product patches applied to release 2011_1.
// This file is #included by hkbPatches_2011_1.cpp

HK_PATCH_BEGIN("hkbCharacter", 2, "hkbCharacter", 3)
	HK_PATCH_MEMBER_ADDED_INT("userData", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkbManualSelectorGenerator", 1, "hkbManualSelectorGenerator", 2)
    HK_PATCH_MEMBER_ADDED_POINTER("generatorChangedTransitionEffect", "hkbTransitionEffect", 0)    
	HK_PATCH_MEMBER_DEFAULT_SET_POINTER("generatorChangedTransitionEffect", 0)
    HK_PATCH_DEPENDS("hkbTransitionEffect", 0)	
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkbManualSelectorGeneratorInternalState", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("currentGeneratorIndex", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("generatorIndexAtActivate", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("activeTransitions", TYPE_ARRAY_STRUCT, "hkbStateMachineActiveTransitionInfo", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkbStateMachineActiveTransitionInfo", 1)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkbSetWordVariableCommand", 0)
    HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
    HK_PATCH_MEMBER_ADDED("characterId", TYPE_INT, HK_NULL, 0)
    HK_PATCH_MEMBER_ADDED("variableName", TYPE_CSTRING, HK_NULL, 0)
    HK_PATCH_MEMBER_ADDED("value", TYPE_STRUCT, "hkbVariableValue", 0)
    HK_PATCH_MEMBER_ADDED("quadValue", TYPE_VEC_4, HK_NULL, 0)
    HK_PATCH_MEMBER_ADDED("type", TYPE_BYTE, HK_NULL, 0)
    HK_PATCH_MEMBER_ADDED("global", TYPE_BYTE, HK_NULL, 0)
    HK_PATCH_DEPENDS("hkBaseObject", 0)
    HK_PATCH_DEPENDS("hkbVariableValue", 0)
    HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

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
