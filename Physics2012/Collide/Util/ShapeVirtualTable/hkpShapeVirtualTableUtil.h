/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_SHAPE_VTABLE_UTIL_H
#define HKP_SHAPE_VTABLE_UTIL_H

#include <Geometry/Collide/Util/ShapeVirtualTable/hkcdShapeVirtualTableUtil.h>


	/// Utility to patch hkpShapeBase virtual tables.
	/// This associates subsets of hkpShapeBase virtual functions with each "profile",
	/// and patches shape vtables to partial shape implementations based on those subsets.
struct hkpShapeVirtualTableUtil : hkcdShapeVirtualTableUtil
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_SHAPE, hkpShapeVirtualTableUtil );

	public:

			/// Profiles corresponding to the various ELFs.
		enum Profile
		{
			PROFILE_INTEGRATE,					///< For hkSpuIntegrate.
			PROFILE_COLLIDE,					///< For hkSpuCollide. 
			PROFILE_COLLIDE_STATIC_COMPOUND,	///< For hkSpuCollide_StaticCompound.
			PROFILE_RAYCAST_QUERY,				///< For hkSpuRayCastQuery.
			PROFILE_COLLISION_QUERY,			///< For hkSpuCollisionQuery.
			PROFILE_CHARACTER_PROXY,			///< For hkSpuCharacterProxy.
			PROFILE_AI_DYNAMIC_NAV_MESH			///< For hkaiSpuDynamicNavMeshMain.
		};

			/// Function IDs. Each virtual function available on SPU must have an unique ID.
			
		enum FunctionId
		{
			FUNCTION_ID_getSupportingVertex				= 0x0001,
			FUNCTION_ID_convertVertexIdsToVertices		= 0x0002,
			FUNCTION_ID_weldContactPoint				= 0x0004,
			FUNCTION_ID_getCentre						= 0x0008,
			FUNCTION_ID_getNumCollisionSpheres			= 0x0010,
			FUNCTION_ID_getCollisionSpheres				= 0x0020,
			FUNCTION_ID_getAabb							= 0x0040,
			FUNCTION_ID_castRay							= 0x0080,
			FUNCTION_ID_castRayWithCollector			= 0x0100,
			FUNCTION_ID_castRayBundle					= 0x0200,
		};

	public:

			/// Set the current profile.
			/// This registers a partial shape implementation for each shape type,
			/// where the subset of implemented functions depends on the profile.
		template < Profile >
		static void HK_CALL HK_INIT_FUNCTION( setProfile )();

#if	defined(HK_DEBUG) && !defined(HK_PLATFORM_SPU)

			/// Test all shape implementations in the current profile.
		static void HK_CALL selfTest();

#endif
};


#endif	// HKP_SHAPE_VTABLE_UTIL_H

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
