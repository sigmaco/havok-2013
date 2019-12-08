/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKA_PHYSICS_2012_BRIDGE__H
#define HKA_PHYSICS_2012_BRIDGE__H

#include <Common/Base/hkBase.h>
#include <Common/Base/KeyCode.h>

#if !defined HK_FEATURE_PRODUCT_PHYSICS_2012 || !defined HK_FEATURE_PRODUCT_ANIMATION
	# if !defined __HAVOK_PARSER__ // Not in the Havok parser pass
		#error Physics 2012 and Animation are needed to use this library.
	#endif
#endif

#include <Common/Base/Container/LocalArray/hkLocalArray.h>
#include <Common/Base/Container/LocalArray/hkLocalBuffer.h>

#include <Physics2012/Dynamics/World/hkpWorld.h>

#endif // HKA_PHYSICS_2012_BRIDGE__H

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
