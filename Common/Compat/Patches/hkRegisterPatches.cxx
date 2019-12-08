/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_SERIALIZE_MIN_COMPATIBLE_VERSION_INTERNAL_VALUE
#error HK_SERIALIZE_MIN_COMPATIBLE_VERSION_INTERNAL_VALUE must be defined
#endif

#ifndef HK_HAVOK_KEYCODE
#	error Common/Base/KeyCode.h must be included before this file
#endif

#ifndef HK_HAVOK_VERSIONS_H
#error hkHavokVersions.h must be included before this file
#endif

// Call the patches registration functions depending on the products available
// and the selected minimum compatible version.

// Patches are organized in folders depending on the version they affect, and in
// each folder we have several files (one for each Havok product). For instance,
// the hkbPatches.cxx/hkbPatches.cpp files in 2011_2/ implement the changes 
// needed to patch Behavior classes from version 2011.2 to the next version
// (2011.3).

#if (HK_SERIALIZE_MIN_COMPATIBLE_VERSION_INTERNAL_VALUE < HK_HAVOK_VERSION_660r1)
// All the patches applied to versions older than Havok 660, needed to bring
// the classes to version 660, are available in the 
// Common/Compat/Patches/Legacy/ directory.
	#if !defined( HK_EXCLUDE_COMMON_PATCHES )
		extern void HK_CALL registerCommonPatches_Legacy(hkVersionPatchManager&);
		registerCommonPatches_Legacy(man);
 		extern void HK_CALL registerCollidePatches_Legacy(hkVersionPatchManager&);
		registerCollidePatches_Legacy(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_AI)
		extern void HK_CALL registerAiPatches_Legacy(hkVersionPatchManager&);
		registerAiPatches_Legacy(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_ANIMATION)
		extern void HK_CALL registerAnimationPatches_Legacy(hkVersionPatchManager&);
		registerAnimationPatches_Legacy(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_CLOTH)
		extern void HK_CALL registerClothPatches_Legacy(hkVersionPatchManager&);
		registerClothPatches_Legacy(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_DESTRUCTION_2012)
		extern void HK_CALL registerDestructionPatches_Legacy(hkVersionPatchManager&);
		registerDestructionPatches_Legacy(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_BEHAVIOR)
		extern void HK_CALL registerBehaviorPatches_Legacy(hkVersionPatchManager&);
		registerBehaviorPatches_Legacy(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_PHYSICS_2012)
		extern void HK_CALL registerPhysicsPatches_Legacy(hkVersionPatchManager&);
		registerPhysicsPatches_Legacy(man);
	#endif
#endif

#if (HK_SERIALIZE_MIN_COMPATIBLE_VERSION_INTERNAL_VALUE <= HK_HAVOK_VERSION_660r1)
// All patches necessary to update version 660 classes to the next version
// are available in the Common/Compat/Patches/660/ directory.
	#if !defined( HK_EXCLUDE_COMMON_PATCHES )
		extern void HK_CALL registerCommonPatches_660(hkVersionPatchManager&);
		registerCommonPatches_660(man);
 		extern void HK_CALL registerCollidePatches_660(hkVersionPatchManager&);
		registerCollidePatches_660(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_AI)
		extern void HK_CALL registerAiPatches_660(hkVersionPatchManager&);
		registerAiPatches_660(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_ANIMATION)
		extern void HK_CALL registerAnimationPatches_660(hkVersionPatchManager&);
		registerAnimationPatches_660(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_CLOTH)
		extern void HK_CALL registerClothPatches_660(hkVersionPatchManager&);
		registerClothPatches_660(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_DESTRUCTION_2012)
		extern void HK_CALL registerDestructionPatches_660(hkVersionPatchManager&);
		registerDestructionPatches_660(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_BEHAVIOR)
		extern void HK_CALL registerBehaviorPatches_660(hkVersionPatchManager&);
		registerBehaviorPatches_660(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_PHYSICS_2012)
		extern void HK_CALL registerPhysicsPatches_660(hkVersionPatchManager&);
		registerPhysicsPatches_660(man);
	#endif
#endif

#if (HK_SERIALIZE_MIN_COMPATIBLE_VERSION_INTERNAL_VALUE <= HK_HAVOK_VERSION_700r1)
// All patches necessary to update version 700 classes to the next version
// are available in the Common/Compat/Patches/700/ directory.
	#if !defined( HK_EXCLUDE_COMMON_PATCHES )
		extern void HK_CALL registerCommonPatches_700(hkVersionPatchManager&);
		registerCommonPatches_700(man);
 		extern void HK_CALL registerCollidePatches_700(hkVersionPatchManager&);
		registerCollidePatches_700(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_AI)
		extern void HK_CALL registerAiPatches_700(hkVersionPatchManager&);
		registerAiPatches_700(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_ANIMATION)
		extern void HK_CALL registerAnimationPatches_700(hkVersionPatchManager&);
		registerAnimationPatches_700(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_CLOTH)
		extern void HK_CALL registerClothPatches_700(hkVersionPatchManager&);
		registerClothPatches_700(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_DESTRUCTION_2012)
		extern void HK_CALL registerDestructionPatches_700(hkVersionPatchManager&);
		registerDestructionPatches_700(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_BEHAVIOR)
		extern void HK_CALL registerBehaviorPatches_700(hkVersionPatchManager&);
		registerBehaviorPatches_700(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_PHYSICS_2012)
		extern void HK_CALL registerPhysicsPatches_700(hkVersionPatchManager&);
		registerPhysicsPatches_700(man);
	#endif
#endif

#if (HK_SERIALIZE_MIN_COMPATIBLE_VERSION_INTERNAL_VALUE <= HK_HAVOK_VERSION_710r1)
// All patches necessary to update version 710 classes to the next version
// are available in the Common/Compat/Patches/710/ directory.
	#if !defined( HK_EXCLUDE_COMMON_PATCHES )
		extern void HK_CALL registerCommonPatches_710(hkVersionPatchManager&);
		registerCommonPatches_710(man);
 		extern void HK_CALL registerCollidePatches_710(hkVersionPatchManager&);
		registerCollidePatches_710(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_AI)
		extern void HK_CALL registerAiPatches_710(hkVersionPatchManager&);
		registerAiPatches_710(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_ANIMATION)
		extern void HK_CALL registerAnimationPatches_710(hkVersionPatchManager&);
		registerAnimationPatches_710(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_CLOTH)
		extern void HK_CALL registerClothPatches_710(hkVersionPatchManager&);
		registerClothPatches_710(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_DESTRUCTION_2012)
		extern void HK_CALL registerDestructionPatches_710(hkVersionPatchManager&);
		registerDestructionPatches_710(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_BEHAVIOR)
		extern void HK_CALL registerBehaviorPatches_710(hkVersionPatchManager&);
		registerBehaviorPatches_710(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_PHYSICS_2012)
		extern void HK_CALL registerPhysicsPatches_710(hkVersionPatchManager&);
		registerPhysicsPatches_710(man);
	#endif
#endif

#if (HK_SERIALIZE_MIN_COMPATIBLE_VERSION_INTERNAL_VALUE <= HK_HAVOK_VERSION_201010r1)
// All patches necessary to update version 2010.1 classes to the next version
// are available in the Common/Compat/Patches/2010_1/ directory.
	#if !defined( HK_EXCLUDE_COMMON_PATCHES )
		extern void HK_CALL registerCommonPatches_2010_1(hkVersionPatchManager&);
		registerCommonPatches_2010_1(man);
 		extern void HK_CALL registerCollidePatches_2010_1(hkVersionPatchManager&);
		registerCollidePatches_2010_1(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_AI)
		extern void HK_CALL registerAiPatches_2010_1(hkVersionPatchManager&);
		registerAiPatches_2010_1(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_ANIMATION)
		extern void HK_CALL registerAnimationPatches_2010_1(hkVersionPatchManager&);
		registerAnimationPatches_2010_1(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_CLOTH)
		extern void HK_CALL registerClothPatches_2010_1(hkVersionPatchManager&);
		registerClothPatches_2010_1(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_DESTRUCTION_2012)
		extern void HK_CALL registerDestructionPatches_2010_1(hkVersionPatchManager&);
		registerDestructionPatches_2010_1(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_BEHAVIOR)
		extern void HK_CALL registerBehaviorPatches_2010_1(hkVersionPatchManager&);
		registerBehaviorPatches_2010_1(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_PHYSICS_2012)
		extern void HK_CALL registerPhysicsPatches_2010_1(hkVersionPatchManager&);
		registerPhysicsPatches_2010_1(man);
	#endif
#endif

#if (HK_SERIALIZE_MIN_COMPATIBLE_VERSION_INTERNAL_VALUE <= HK_HAVOK_VERSION_201020r1)
// All patches necessary to update version 2010.2 classes to the next version
// are available in the Common/Compat/Patches/2010_2/ directory.
	#if !defined( HK_EXCLUDE_COMMON_PATCHES )
		extern void HK_CALL registerCommonPatches_2010_2(hkVersionPatchManager&);
		registerCommonPatches_2010_2(man);
 		extern void HK_CALL registerCollidePatches_2010_2(hkVersionPatchManager&);
		registerCollidePatches_2010_2(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_AI)
		extern void HK_CALL registerAiPatches_2010_2(hkVersionPatchManager&);
		registerAiPatches_2010_2(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_ANIMATION)
		extern void HK_CALL registerAnimationPatches_2010_2(hkVersionPatchManager&);
		registerAnimationPatches_2010_2(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_CLOTH)
		extern void HK_CALL registerClothPatches_2010_2(hkVersionPatchManager&);
		registerClothPatches_2010_2(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_DESTRUCTION_2012)
		extern void HK_CALL registerDestructionPatches_2010_2(hkVersionPatchManager&);
		registerDestructionPatches_2010_2(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_BEHAVIOR)
		extern void HK_CALL registerBehaviorPatches_2010_2(hkVersionPatchManager&);
		registerBehaviorPatches_2010_2(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_PHYSICS_2012)
		extern void HK_CALL registerPhysicsPatches_2010_2(hkVersionPatchManager&);
		registerPhysicsPatches_2010_2(man);
	#endif
#endif

#if (HK_SERIALIZE_MIN_COMPATIBLE_VERSION_INTERNAL_VALUE <= HK_HAVOK_VERSION_201110r1)
// All patches necessary to update version 2011.1 classes to the next version
// are available in the Common/Compat/Patches/2011_1/ directory.
	#if !defined( HK_EXCLUDE_COMMON_PATCHES )
		extern void HK_CALL registerCommonPatches_2011_1(hkVersionPatchManager&);
		registerCommonPatches_2011_1(man);
 		extern void HK_CALL registerCollidePatches_2011_1(hkVersionPatchManager&);
		registerCollidePatches_2011_1(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_AI)
		extern void HK_CALL registerAiPatches_2011_1(hkVersionPatchManager&);
		registerAiPatches_2011_1(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_ANIMATION)
		extern void HK_CALL registerAnimationPatches_2011_1(hkVersionPatchManager&);
		registerAnimationPatches_2011_1(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_CLOTH)
		extern void HK_CALL registerClothPatches_2011_1(hkVersionPatchManager&);
		registerClothPatches_2011_1(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_DESTRUCTION_2012)
		extern void HK_CALL registerDestructionPatches_2011_1(hkVersionPatchManager&);
		registerDestructionPatches_2011_1(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_BEHAVIOR)
		extern void HK_CALL registerBehaviorPatches_2011_1(hkVersionPatchManager&);
		registerBehaviorPatches_2011_1(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_PHYSICS_2012)
		extern void HK_CALL registerPhysicsPatches_2011_1(hkVersionPatchManager&);
		registerPhysicsPatches_2011_1(man);
	#endif
#endif

#if (HK_SERIALIZE_MIN_COMPATIBLE_VERSION_INTERNAL_VALUE <= HK_HAVOK_VERSION_201120r1)
// All patches necessary to update version 2011.2 classes to the next version
// are available in the Common/Compat/Patches/2011_2/ directory.
	#if !defined( HK_EXCLUDE_COMMON_PATCHES )
		extern void HK_CALL registerCommonPatches_2011_2(hkVersionPatchManager&);
		registerCommonPatches_2011_2(man);
 		extern void HK_CALL registerCollidePatches_2011_2(hkVersionPatchManager&);
		registerCollidePatches_2011_2(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_AI)
		extern void HK_CALL registerAiPatches_2011_2(hkVersionPatchManager&);
		registerAiPatches_2011_2(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_ANIMATION)
		extern void HK_CALL registerAnimationPatches_2011_2(hkVersionPatchManager&);
		registerAnimationPatches_2011_2(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_CLOTH)
		extern void HK_CALL registerClothPatches_2011_2(hkVersionPatchManager&);
		registerClothPatches_2011_2(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_DESTRUCTION_2012)
		extern void HK_CALL registerDestructionPatches_2011_2(hkVersionPatchManager&);
		registerDestructionPatches_2011_2(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_BEHAVIOR)
		extern void HK_CALL registerBehaviorPatches_2011_2(hkVersionPatchManager&);
		registerBehaviorPatches_2011_2(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_PHYSICS_2012)
		extern void HK_CALL registerPhysicsPatches_2011_2(hkVersionPatchManager&);
		registerPhysicsPatches_2011_2(man);
	#endif
#endif

#if (HK_SERIALIZE_MIN_COMPATIBLE_VERSION_INTERNAL_VALUE <= HK_HAVOK_VERSION_201130r1)
// All patches necessary to update version 2011.3 classes to the next version
// are available in the Common/Compat/Patches/2011_3/ directory.
	#if !defined( HK_EXCLUDE_COMMON_PATCHES )
		extern void HK_CALL registerCommonPatches_2011_3(hkVersionPatchManager&);
		registerCommonPatches_2011_3(man);
		extern void HK_CALL registerCollidePatches_2011_3(hkVersionPatchManager&);
		registerCollidePatches_2011_3(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_AI)
		extern void HK_CALL registerAiPatches_2011_3(hkVersionPatchManager&);
		registerAiPatches_2011_3(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_ANIMATION)
		extern void HK_CALL registerAnimationPatches_2011_3(hkVersionPatchManager&);
		registerAnimationPatches_2011_3(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_CLOTH)
		extern void HK_CALL registerClothPatches_2011_3(hkVersionPatchManager&);
		registerClothPatches_2011_3(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_DESTRUCTION_2012)
		extern void HK_CALL registerDestructionPatches_2011_3(hkVersionPatchManager&);
		registerDestructionPatches_2011_3(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_BEHAVIOR)
		extern void HK_CALL registerBehaviorPatches_2011_3(hkVersionPatchManager&);
		registerBehaviorPatches_2011_3(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_PHYSICS_2012)
		extern void HK_CALL registerPhysicsPatches_2011_3(hkVersionPatchManager&);
		registerPhysicsPatches_2011_3(man);
	#endif
#endif

#if (HK_SERIALIZE_MIN_COMPATIBLE_VERSION_INTERNAL_VALUE <= HK_HAVOK_VERSION_201210r1)
// All patches necessary to update version 2011.3 classes to the next version
// are available in the Common/Compat/Patches/2012_1/ directory.
	#if !defined( HK_EXCLUDE_COMMON_PATCHES )
		extern void HK_CALL registerCommonPatches_2012_1(hkVersionPatchManager&);
		registerCommonPatches_2012_1(man);
		extern void HK_CALL registerCollidePatches_2012_1(hkVersionPatchManager&);
		registerCollidePatches_2012_1(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_AI)
		extern void HK_CALL registerAiPatches_2012_1(hkVersionPatchManager&);
		registerAiPatches_2012_1(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_ANIMATION)
		extern void HK_CALL registerAnimationPatches_2012_1(hkVersionPatchManager&);
		registerAnimationPatches_2012_1(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_CLOTH)
		extern void HK_CALL registerClothPatches_2012_1(hkVersionPatchManager&);
		registerClothPatches_2012_1(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_DESTRUCTION_2012)
		extern void HK_CALL registerDestructionPatches_2012_1(hkVersionPatchManager&);
		registerDestructionPatches_2012_1(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_BEHAVIOR)
		extern void HK_CALL registerBehaviorPatches_2012_1(hkVersionPatchManager&);
		registerBehaviorPatches_2012_1(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_PHYSICS_2012)
		extern void HK_CALL registerPhysicsPatches_2012_1(hkVersionPatchManager&);
		registerPhysicsPatches_2012_1(man);
	#endif
#endif

#if (HK_SERIALIZE_MIN_COMPATIBLE_VERSION_INTERNAL_VALUE <= HK_HAVOK_VERSION_201220r1)
// All patches necessary to update version 2012.1 classes to the next version
// are available in the Common/Compat/Patches/2012_2/ directory.
	#if !defined( HK_EXCLUDE_COMMON_PATCHES )
		extern void HK_CALL registerCommonPatches_2012_2(hkVersionPatchManager&);
		registerCommonPatches_2012_2(man);
		extern void HK_CALL registerCollidePatches_2012_2(hkVersionPatchManager&);
		registerCollidePatches_2012_2(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_AI)
		extern void HK_CALL registerAiPatches_2012_2(hkVersionPatchManager&);
		registerAiPatches_2012_2(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_ANIMATION)
		extern void HK_CALL registerAnimationPatches_2012_2(hkVersionPatchManager&);
		registerAnimationPatches_2012_2(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_CLOTH)
		extern void HK_CALL registerClothPatches_2012_2(hkVersionPatchManager&);
		registerClothPatches_2012_2(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_DESTRUCTION_2012)
		extern void HK_CALL registerDestructionPatches_2012_2(hkVersionPatchManager&);
		registerDestructionPatches_2012_2(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_BEHAVIOR)
		extern void HK_CALL registerBehaviorPatches_2012_2(hkVersionPatchManager&);
		registerBehaviorPatches_2012_2(man);
	#endif
	#if defined(HK_FEATURE_PRODUCT_PHYSICS_2012)
		extern void HK_CALL registerPhysicsPatches_2012_2(hkVersionPatchManager&);
		registerPhysicsPatches_2012_2(man);
	#endif
#endif

#if defined(HK_FEATURE_PRODUCT_PHYSICS)
	extern void HK_CALL registerNewPhysicsPatches(hkVersionPatchManager&);
	registerNewPhysicsPatches(man);
#endif

#if defined(HK_FEATURE_PRODUCT_DESTRUCTION)
	extern void HK_CALL registerNewDestructionPatches(hkVersionPatchManager&);
	registerNewDestructionPatches(man);
#endif

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
