/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Cloth specific product patches applied to release 2011_3.
// This file is #included by hclPatches_2011_3.cpp

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hclSimClothDataTransferMotionData", 0)
	HK_PATCH_MEMBER_ADDED("transformSetIndex", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("transformIndex", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("transferTranslationMotion", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("minTranslationSpeed", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("maxTranslationSpeed", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("minTranslationBlend", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("maxTranslationBlend", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("transferRotationMotion", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("minRotationSpeed", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("maxRotationSpeed", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("minRotationBlend", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("maxRotationBlend", TYPE_REAL, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hclSimClothSetupObjectTransferMotionSetupData", 0)
	HK_PATCH_MEMBER_ADDED("transferMotionTransformSetSetup", TYPE_OBJECT, "hclTransformSetSetupObject", 0)
	HK_PATCH_MEMBER_ADDED("transferMotionTransformName", TYPE_CSTRING, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("transferTranslationMotion", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("minTranslationSpeed", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("maxTranslationSpeed", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("minTranslationBlend", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("maxTranslationBlend", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("transferRotationMotion", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("minRotationSpeed", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("maxRotationSpeed", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("minRotationBlend", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("maxRotationBlend", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hclTransformSetSetupObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclSimClothSetupObject", 4, "hclSimClothSetupObject", 5)
	HK_PATCH_MEMBER_ADDED("enableTransferMotion", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("transferMotionSetupData", TYPE_STRUCT, "hclSimClothSetupObjectTransferMotionSetupData", 0)
	HK_PATCH_DEPENDS("hclSimClothSetupObjectTransferMotionSetupData", 0)
	//HK_PATCH_FUNCTION(hclSimClothSetupObject_4_to_5)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hclSimClothDataOverridableSimulationInfo", 0)
	HK_PATCH_MEMBER_ADDED("gravity", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("globalDampingPerSecond", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("collisionTolerance", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("pinchDetectionEnabled", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("landscapeCollisionEnabled", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("transferMotionEnabled", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclSimClothData", 8, "hclSimClothData", 9)
	HK_PATCH_MEMBER_ADDED("transferMotionData", TYPE_STRUCT, "hclSimClothDataTransferMotionData", 0)
	HK_PATCH_DEPENDS("hclSimClothDataTransferMotionData", 0)
	HK_PATCH_MEMBER_ADDED("doNormals", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_DEPENDS("hclSimClothDataSimulationInfo", 2)
	HK_PATCH_DEPENDS("hclSimClothDataOverridableSimulationInfo", 0)
	HK_PATCH_MEMBER_RENAMED("simulationInfo", "old_simulationInfo")
	HK_PATCH_MEMBER_ADDED("simulationInfo", TYPE_STRUCT, "hclSimClothDataOverridableSimulationInfo", 0)
	HK_PATCH_FUNCTION(hclSimClothData_8_to_9)
	HK_PATCH_MEMBER_REMOVED("old_simulationInfo", TYPE_STRUCT, "hclSimClothDataSimulationInfo", 0)
	HK_PATCH_MEMBER_REMOVED("pinchDetectionEnabled", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("landscapeCollisionEnabled", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclSimClothDataSimulationInfo", 2, HK_NULL, HK_CLASS_REMOVED)
	HK_PATCH_MEMBER_REMOVED("gravity", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("globalDampingPerSecond", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("collisionTolerance", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("doNormals", TYPE_BYTE, HK_NULL, 0)
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
