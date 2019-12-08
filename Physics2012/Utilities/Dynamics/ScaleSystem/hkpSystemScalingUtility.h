/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_UTILS_SYSTEM_SCALING_UTILITY__H
#define HK_UTILS_SYSTEM_SCALING_UTILITY__H

class hkpPhysicsSystem;

#include <Physics2012/Utilities/Collide/ShapeUtils/ShapeScaling/hkpShapeScalingUtility.h>

/// This utility class uniformly scales physics systems.
/// Note that this is not meant to be used at runtime, but in the tool chain and preprocess stages.
class hkpSystemScalingUtility
{
	public:

		static void HK_CALL scaleSystemSimd( hkpPhysicsSystem* system, hkSimdRealParameter scale, hkArray<hkpShapeScalingUtility::ShapePair>* doneShapes = HK_NULL );

		static HK_FORCE_INLINE void HK_CALL scaleSystem( hkpPhysicsSystem* system, hkReal scale, hkArray<hkpShapeScalingUtility::ShapePair>* doneShapes = HK_NULL )
		{
			scaleSystemSimd(system, hkSimdReal::fromFloat(scale), doneShapes);
		}
};


#endif // HK_UTILS_SYSTEM_SCALING_UTILITY__H

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
