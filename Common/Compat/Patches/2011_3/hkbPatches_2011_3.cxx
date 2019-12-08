/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Behavior specific product patches applied to release 2011_3.
// This file is #included by hkbPatches_2011_3.cpp
HK_PATCH_BEGIN("hkbExtrapolatingTransitionEffectInternalState", 0, "hkbExtrapolatingTransitionEffectInternalState", 1)
	HK_PATCH_MEMBER_ADDED("fromGeneratorPartitionInfo", TYPE_STRUCT, "hkbGeneratorPartitionInfo", 0)
	HK_PATCH_MEMBER_ADDED("boneWeights", TYPE_ARRAY_REAL, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkbGeneratorPartitionInfo", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkbLayer", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkbBindable")
	HK_PATCH_MEMBER_ADDED("generator", TYPE_OBJECT, "hkbGenerator", 0)
	HK_PATCH_MEMBER_ADDED_REAL("weight", 1.000000f)
	HK_PATCH_MEMBER_ADDED("boneWeights", TYPE_OBJECT, "hkbBoneWeightArray",0)
	HK_PATCH_MEMBER_ADDED_REAL("fadeInDuration", 0.000000f)
	HK_PATCH_MEMBER_ADDED_REAL("fadeOutDuration", 0.000000f)
	HK_PATCH_MEMBER_ADDED_INT("onEventId", -1)
	HK_PATCH_MEMBER_ADDED_INT("offEventId", -1)
	HK_PATCH_MEMBER_ADDED_BYTE("onByDefault", 0)
	HK_PATCH_MEMBER_ADDED_BYTE("useMotion", 1)
	HK_PATCH_DEPENDS("hkbBoneWeightArray", 0)
	HK_PATCH_DEPENDS("hkbNode", 1)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkbGenerator", 0)
	HK_PATCH_DEPENDS("hkbBindable", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkbLayerGeneratorLayerInternalState", 0)
	HK_PATCH_MEMBER_ADDED("weight", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("timeElapsed", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("onFraction", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("fadingState", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("useMotion", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("syncNextFrame", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("isActive", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkbLayerGeneratorInternalState", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("numActiveLayers", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("initSync", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("layerInternalStates", TYPE_ARRAY_STRUCT, "hkbLayerGeneratorLayerInternalState", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkbLayerGeneratorLayerInternalState", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkbLayerGenerator", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkbGenerator")
	HK_PATCH_MEMBER_ADDED("layers", TYPE_ARRAY_OBJECT, "hkbLayer", 0)
	HK_PATCH_MEMBER_ADDED_INT("indexOfSyncMasterChild", -1)
	HK_PATCH_MEMBER_ADDED_INT("flags", 0)
	HK_PATCH_DEPENDS("hkbNode", 1)
	HK_PATCH_DEPENDS("hkbLayer", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkbGenerator", 0)
	HK_PATCH_DEPENDS("hkbBindable", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkbGeneratorSyncInfoActiveInterval", 0)
	HK_PATCH_MEMBER_ADDED("syncPoints", TYPE_TUPLE_STRUCT, "hkbGeneratorSyncInfoSyncPoint", 2)
	HK_PATCH_MEMBER_ADDED("fraction", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkbGeneratorSyncInfoSyncPoint", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkbGeneratorSyncInfo", 0, "hkbGeneratorSyncInfo", 1)
	HK_PATCH_MEMBER_REMOVED("syncPoints", TYPE_TUPLE_STRUCT, "hkbGeneratorSyncInfoSyncPoint", 8)
	HK_PATCH_MEMBER_ADDED("syncPoints", TYPE_TUPLE_STRUCT, "hkbGeneratorSyncInfoSyncPoint", 16)
	HK_PATCH_MEMBER_REMOVED("baseFrequency", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("duration", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("activeInterval", TYPE_STRUCT, "hkbGeneratorSyncInfoActiveInterval", 0)
	HK_PATCH_DEPENDS("hkbGeneratorSyncInfoSyncPoint", 0)
	HK_PATCH_DEPENDS("hkbGeneratorSyncInfoActiveInterval", 0)    
HK_PATCH_END()

HK_PATCH_BEGIN("hkbContext", 1, "hkbContext", 2)
	HK_PATCH_MEMBER_ADDED("rootBehavior", TYPE_OBJECT, "hkbBehaviorGraph", 0)
	HK_PATCH_DEPENDS("hkbNode", 1)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkbGenerator", 0)
	HK_PATCH_DEPENDS("hkbBindable", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkbBehaviorGraph", 1)    
HK_PATCH_END()

HK_PATCH_BEGIN("hkbMirroredSkeletonInfo", 0, "hkbMirroredSkeletonInfo", 1)
	HK_PATCH_MEMBER_ADDED("partitionPairMap", TYPE_ARRAY_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkbAssetBundleStringData", 0)
	HK_PATCH_MEMBER_ADDED("bundleName", TYPE_CSTRING, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("assetNames", TYPE_ARRAY_CSTRING, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkbAssetBundle", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("assets", TYPE_ARRAY_OBJECT, "hkReferencedObject", 0)
	HK_PATCH_MEMBER_ADDED("name", TYPE_CSTRING, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("type", TYPE_INT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkbCharacterStringData", 8, "hkbCharacterStringData", 9)
	HK_PATCH_MEMBER_ADDED("animationBundleNameData", TYPE_ARRAY_STRUCT, "hkbAssetBundleStringData", 0)
	HK_PATCH_MEMBER_ADDED("animationBundleFilenameData", TYPE_ARRAY_STRUCT, "hkbAssetBundleStringData", 0)
	HK_PATCH_FUNCTION(hkbCharacterStringData_8_to_9)
	HK_PATCH_MEMBER_REMOVED("animationNames", TYPE_ARRAY_CSTRING, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("animationFilenames", TYPE_ARRAY_CSTRING, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkbAssetBundleStringData", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkbClipGenerator", 2, "hkbClipGenerator", 3)
	HK_PATCH_MEMBER_ADDED("segmentIndex", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkbClipGenerator", 3, "hkbClipGenerator", 4)
	HK_PATCH_MEMBER_ADDED("animationBundleName", TYPE_CSTRING, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("segmentIndex", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("userPartitionMask", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkbParametricMotionGenerator", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkbGenerator")
	HK_PATCH_MEMBER_ADDED("generators", TYPE_ARRAY_OBJECT, "hkbGenerator", 0)
	HK_PATCH_MEMBER_ADDED_REAL("xAxisParameterValue", 0.000000f)
	HK_PATCH_MEMBER_ADDED_REAL("yAxisParameterValue", 0.000000f)
	HK_PATCH_MEMBER_ADDED("xAxisParameterType", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("yAxisParameterType", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED_BYTE("addExtrapolationSamples", 1)
	HK_PATCH_DEPENDS("hkbNode", 1)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkbGenerator", 0)
	HK_PATCH_DEPENDS("hkbBindable", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkbPinBonesGenerator", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkbGenerator")
	HK_PATCH_MEMBER_ADDED("referenceFrameGenerator", TYPE_OBJECT, "hkbGenerator", 0)
	HK_PATCH_MEMBER_ADDED("pinnedGenerator", TYPE_OBJECT, "hkbGenerator", 0)
	HK_PATCH_MEMBER_ADDED("boneIndices", TYPE_OBJECT, "hkbBoneIndexArray", 0)
	HK_PATCH_MEMBER_ADDED_REAL("fraction", 0.000000f)
	HK_PATCH_DEPENDS("hkbNode", 1)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkbGenerator", 0)
	HK_PATCH_DEPENDS("hkbBindable", 0)
	HK_PATCH_DEPENDS("hkbBoneIndexArray", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkbGeneratorPartitionInfo", 0)
	HK_PATCH_MEMBER_ADDED("boneMask", TYPE_TUPLE_INT, HK_NULL, 8)
	HK_PATCH_MEMBER_ADDED("partitionMask", TYPE_TUPLE_INT, HK_NULL, 1)
	HK_PATCH_MEMBER_ADDED("numBones", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("numMaxPartitions", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkbCameraVariablesChangedCommand", 0)
    HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
    HK_PATCH_MEMBER_ADDED("cameraVariableFloatNames", TYPE_ARRAY_CSTRING, HK_NULL, 0)
    HK_PATCH_MEMBER_ADDED("cameraFloatValues", TYPE_ARRAY_REAL, HK_NULL, 0)
    HK_PATCH_MEMBER_ADDED("cameraVariableVectorNames", TYPE_ARRAY_CSTRING, HK_NULL, 0)
    HK_PATCH_MEMBER_ADDED("cameraVectorValues", TYPE_ARRAY_VEC_4, HK_NULL, 0)
    HK_PATCH_DEPENDS("hkBaseObject", 0)
    HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkbBehaviorInfoIdToNamePair", 0, "hkbBehaviorInfoIdToNamePair",1)
	HK_PATCH_MEMBER_REMOVED("toolType", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("toolType", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkbAuxiliaryNodeInfo", 1, "hkbAuxiliaryNodeInfo", 2)
	HK_PATCH_MEMBER_REMOVED("type", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("type", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkbScriptCondition", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkbCondition")
	HK_PATCH_MEMBER_ADDED("conditionScript", TYPE_CSTRING, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkbCondition", 0)
HK_PATCH_END()


HK_PATCH_BEGIN("hkbParametricMotionGenerator", 0, "hkbParametricMotionGenerator", 1)
HK_PATCH_PARENT_SET(HK_NULL, "hkbGenerator")
HK_PATCH_MEMBER_ADDED("motionSpace", TYPE_INT, HK_NULL, 0)
HK_PATCH_MEMBER_REMOVED("xAxisParameterType", TYPE_INT, HK_NULL, 0)
HK_PATCH_MEMBER_REMOVED("yAxisParameterType", TYPE_INT, HK_NULL, 0)
HK_PATCH_MEMBER_REMOVED("addExtrapolationSamples", TYPE_INT, HK_NULL, 0)
HK_PATCH_DEPENDS("hkbNode", 1)
HK_PATCH_DEPENDS("hkBaseObject", 0)
HK_PATCH_DEPENDS("hkbGenerator", 0)
HK_PATCH_DEPENDS("hkbBindable", 0)
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
