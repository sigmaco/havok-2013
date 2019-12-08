/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_PRODUCT_FEATURES_H
#define HK_PRODUCT_FEATURES_H

	/// Singleton class whose constructor by default registers all product features.
	/// The initialize function is generated as a side effect of #include <Common/Base/Config/hkProductFeatures.cxx>
namespace hkProductFeatures
{
	void HK_CALL initialize();
}

// You only need to look further if you're doing something specialized.
// Mostly you'll just use the macros in hkProductFeatures.inl to control
// what gets linked or stripped.


//
// Common
//
		/// You'll need this in order to load assets which were generated prior to version 7.0.0.
		/// It's rather large and shouldn't be linked unless you definitely need it.
	extern void HK_CALL hkFeature_serializeDeprecatedPre700();

//
// Physics
//
#ifdef HK_FEATURE_PRODUCT_PHYSICS_2012
		/// Register height field collision agent
	extern void HK_CALL hkpHeightFieldAgent_registerSelf();

		/// Calculate accurate inertia tensor for convex hulls, otherwise calculate based on their bounding boxes
	extern void HK_CALL hkpAccurateInertiaTensorComputer_registerSelf();

		/// You'll need at least one simulation type for most of the functions in hkpWorld
	extern void HK_CALL hkpSimulation_registerSelf();
	extern void HK_CALL hkpContinuousSimulation_registerSelf();
	#if (HK_CONFIG_THREAD != HK_CONFIG_SINGLE_THREADED)
	extern void HK_CALL hkpMultiThreadedSimulation_registerSelf();
	#endif

		/// Register the broad phase types
	extern void HK_CALL hkp3AxisSweep_registerSelf();
	extern void HK_CALL hkpTreeBroadPhase_registerSelf();

		/// Register the raycast function for sampled height fields
	extern void HK_CALL hkpSampledHeightField_registerDdaRayCastFunction();
	extern void HK_CALL hkpSampledHeightField_registerCoarseTreeRayCastFunction();
	extern void HK_CALL hkpSampledHeightField_registerAllRayCastFunctions();

#endif

#ifdef HK_FEATURE_PRODUCT_DESTRUCTION_2012
	extern void HK_CALL hkdCutoutFractureRuntimeFracture_registerSelf();
	extern void HK_CALL hkdDecomposeFractureRuntimeFracture_registerSelf();
	extern void HK_CALL hkdPieFractureRuntimeFracture_registerSelf();
	extern void HK_CALL hkdRandomSplitFractureRuntimeFracture_registerSelf();
	extern void HK_CALL hkdScriptedFractureRuntimeFracture_registerSelf();
	extern void HK_CALL hkdSliceFractureRuntimeFracture_registerSelf();
	extern void HK_CALL hkdSplitInHalfFractureRuntimeFracture_registerSelf();
	extern void HK_CALL hkdVoronoiFractureRuntimeFracture_registerSelf();
	extern void HK_CALL hkdWoodFractureRuntimeFracture_registerSelf();

	extern void HK_CALL hkdDecorateFractureFaceActionImpl_registerSelf();
	extern void HK_CALL hkdConvexDecompositionActionImpl_registerSelf();
	extern void HK_CALL hkdDecalMapActionImpl_registerSelf();
	extern void HK_CALL hkdGlueFixedPiecesActionImpl_registerSelf();
	extern void HK_CALL hkdSplitByPhysicsIslandsActionImpl_registerSelf();

	extern void HK_CALL hkdFractureUtilRetriangulateRecursively_registerSelf();
	extern void HK_CALL registerDestructionRuntime();
#endif

#endif//HK_PRODUCT_FEATURES_H

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
