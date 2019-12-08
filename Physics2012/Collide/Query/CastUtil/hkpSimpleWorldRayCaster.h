/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_SIMPLE_WORLD_RAY_CASTER
#define HK_SIMPLE_WORLD_RAY_CASTER

#include <Physics2012/Collide/BroadPhase/hkpBroadPhaseCastCollector.h>
#include <Physics2012/Collide/Shape/Query/hkpShapeRayCastInput.h>
#include <Physics2012/Collide/Query/CastUtil/hkpWorldRayCastInput.h>

struct hkpWorldRayCastInput;
struct hkpWorldRayCastOutput;
class hkpCollisionFilter;
class hkpRayCollidableFilter;
class hkpBroadPhase;
typedef char hkpBroadPhaseAabbCache;

	/// This is a utility class which queries the broad phase for ray intersections and then checks if the corresponding hkpShape was hit.
	/// In other words, it connects hkpBroadPhase::castRay to hkpShape::castRay.
	/// This method uses the output structure interface (instead of the collector interface used by hkpWorldRayCaster).
	/// It is called by hkpWorld::castRay. Usually you should call hkpWorld::castRay instead of
	/// using this class directly.
class hkpSimpleWorldRayCaster : public hkpBroadPhaseCastCollector
{
	public:
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE,hkpSimpleWorldRayCaster);
		hkpSimpleWorldRayCaster(){}

		~hkpSimpleWorldRayCaster(){}

			/// This function casts a ray through the world.
			/// The "output" will be filled with the ray hit upon completion.
		void castRay( const hkpBroadPhase& broadphase, const hkpWorldRayCastInput& input, const hkpCollisionFilter* filter, hkpWorldRayCastOutput& output );

			/// Casts a group of rays in close proximity
		void castRayGroup( const hkpBroadPhase& broadphase, const hkpWorldRayCastInput* inputArray, int numRays, const hkpCollisionFilter* filter, hkpWorldRayCastOutput* outputs ) ;

			/// Same as castRay, only for experts. Uses an hkpBroadPhaseAabbCache: See hkpBroadPhase for Details
		void castRay( const hkpBroadPhase& broadphase, const hkpWorldRayCastInput& input, const hkpCollisionFilter* filter, const hkpBroadPhaseAabbCache* cache, hkpWorldRayCastOutput& output );


			/// Cast multiple rays having the same startpoint.
			/// Notes:
			///   - the startpoint is taken only from the first input
			///   - However filtering can be done separate for each ray.
		void castRaysFromSinglePoint( const hkpBroadPhase& broadphase, const hkpWorldRayCastInput* inputArray, int numRays, const hkpCollisionFilter* filter, const hkpBroadPhaseAabbCache* cache, hkpWorldRayCastOutput* outputs );
	protected:
		virtual	hkReal addBroadPhaseHandle( const hkpBroadPhaseHandle* broadPhaseHandle, int castIndex );

	protected:
		const hkpWorldRayCastInput*   m_input;
		const hkpRayCollidableFilter* m_filter;
		hkpWorldRayCastOutput*  m_result;

		// used as a temporary storage
		hkpShapeRayCastInput    m_shapeInput;
};


#endif //HK_SIMPLE_WORLD_RAY_CASTER

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
