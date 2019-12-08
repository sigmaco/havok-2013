/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

//
// PHYSICS_2012
//
#if defined( HAVOK_PHYSICS_2012_KEYCODE )
#define HK_FEATURE_PRODUCT_PHYSICS_2012
#endif

//
// PHYSICS
//
#if defined( HAVOK_PHYSICS_KEYCODE )
#define HK_FEATURE_PRODUCT_PHYSICS
#endif

//
// ANIMATION
//
#if defined( HAVOK_ANIMATION_KEYCODE )
#define HK_FEATURE_PRODUCT_ANIMATION
#endif

//
// BEHAVIOR
//
#if defined( HAVOK_BEHAVIOR_KEYCODE )
#define HK_FEATURE_PRODUCT_BEHAVIOR
#endif

//
// CLOTH
//
#if defined( HAVOK_CLOTH_KEYCODE )
#define HK_FEATURE_PRODUCT_CLOTH
#endif

//
// DESTRUCTION_2012
//
#if defined( HAVOK_DESTRUCTION_2012_KEYCODE )
#define HK_FEATURE_PRODUCT_DESTRUCTION_2012
#endif

//
// DESTRUCTION
//
#if defined( HAVOK_DESTRUCTION_KEYCODE )
#define HK_FEATURE_PRODUCT_DESTRUCTION
#endif

//
// AI
//
#if defined( HAVOK_AI_KEYCODE )
#define HK_FEATURE_PRODUCT_AI
#endif

//
// SCRIPT
//
#if defined( HAVOK_SCRIPT_KEYCODE )
#define HK_FEATURE_PRODUCT_SCRIPT
#endif

//
// SIMULATION
//
#if defined( HAVOK_SIMULATION_KEYCODE )
#define HK_FEATURE_PRODUCT_MILSIM
#endif

//
// Raise an error if no keycodes are set.
//

//
// Product dependency checks:
//
#if defined(HK_FEATURE_PRODUCT_BEHAVIOR) && !defined(HK_FEATURE_PRODUCT_ANIMATION)
#error "Can't use BEHAVIOR without ANIMATION. Please add your ANIMATION keycode to <Common/Base/KeyCode.h>"
#endif

#if defined(HK_FEATURE_PRODUCT_DESTRUCTION_2012) && !defined(HK_FEATURE_PRODUCT_PHYSICS_2012)
#error "Can't use DESTRUCTION_2012 without PHYSICS_2012. Please add your PHYSICS_2012 keycode to <Common/Base/KeyCode.h>"
#endif

#if defined(HK_FEATURE_PRODUCT_DESTRUCTION) && !defined(HK_FEATURE_PRODUCT_PHYSICS)
#error "Can't use DESTRUCTION without PHYSICS. Please add your PHYSICS keycode to <Common/Base/KeyCode.h>"
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
