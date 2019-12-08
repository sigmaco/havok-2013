/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_COLLIDE2_BV_TREE_SHAPE_AGENT_H
#define HK_COLLIDE2_BV_TREE_SHAPE_AGENT_H

#include <Physics2012/Collide/Agent/hkpCollisionAgent.h>
#include <Common/Base/Types/Geometry/Aabb/hkAabb.h>
#include <Physics2012/Collide/Shape/Compound/Collection/hkpShapeCollection.h>
#include <Physics2012/Collide/Shape/Query/hkpAabbCastCollector.h>

class hkpCollisionDispatcher;


	/// This agent deals with collisions between hkBvTreeShapes and other shapes. It traverses the bounding volume tree and dispatches
	/// collision agents for those child shapes that are found to be collision candidates with the other shape.
	/// It assumes that bodyB is the bvtree shape
class hkpBvTreeAgent : public hkpCollisionAgent
{
	public:
	HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
			/// Registers this agent with the collision dispatcher.
		static void HK_CALL registerAgent(hkpCollisionDispatcher* dispatcher);

			// hkpCollisionAgent interface implementation.
		virtual void getPenetrations( const hkpCdBody& bodyA, const hkpCdBody& bodyB, const hkpCollisionInput& input, hkpCdBodyPairCollector& collector );

			// hkpCollisionAgent interface implementation.
		static void HK_CALL staticGetPenetrations( const hkpCdBody& bodyA, const hkpCdBody& bodyB, const hkpCollisionInput& input, hkpCdBodyPairCollector& collector );

			// hkpCollisionAgent interface implementation.
		virtual void getClosestPoints( const hkpCdBody& bodyA, const hkpCdBody& bodyB, const hkpCollisionInput& input, hkpCdPointCollector& collector ) ;

			// hkpCollisionAgent interface implementation.
		static void HK_CALL staticGetClosestPoints( const hkpCdBody& bodyA, const hkpCdBody& bodyB, const hkpCollisionInput& input, hkpCdPointCollector& collector ) ;

			// hkpCollisionAgent interface implementation.
		virtual void linearCast( const hkpCdBody& bodyA, const hkpCdBody& bodyB, const hkpLinearCastCollisionInput& input, hkpCdPointCollector& collector, hkpCdPointCollector* startCollector );

			// hkpCollisionAgent interface implementation.
		static void HK_CALL staticLinearCast( const hkpCdBody& bodyA, const hkpCdBody& bodyB, const hkpLinearCastCollisionInput& input, hkpCdPointCollector& collector, hkpCdPointCollector* startCollector );

			// hkpCollisionAgent interface implementation.
		virtual void processCollision(const hkpCdBody& bodyA, const hkpCdBody& bodyB, const hkpProcessCollisionInput& input, hkpProcessCollisionOutput& result);

			// hkpCollisionAgent interface implementation.
		virtual void cleanup(hkCollisionConstraintOwner& info);

			/// AABB caching will skip queries to the hkpShapeCollection if the AABBs between the two colliding bodies has not changed.
			/// You need to disable this if your hkpShapeCollection has changed, i.e., elements have been added or removed
		static void HK_CALL setUseAabbCaching( hkBool useIt );

			/// AABB caching will skip queries to the hkpShapeCollection if the AABBs between the two colliding bodies has not changed
		static hkBool HK_CALL getUseAabbCaching();


	public:
		static hkBool m_useFastUpdate;

		virtual void updateShapeCollectionFilter( const hkpCdBody& bodyA, const hkpCdBody& bodyB, const hkpCollisionInput& input, hkCollisionConstraintOwner& constraintOwner );

			// hkpCollisionAgent interface implementation.
		virtual void invalidateTim( const hkpCollisionInput& input);

			// hkpCollisionAgent interface implementation.
		virtual void warpTime(hkTime oldTime, hkTime newTime, const hkpCollisionInput& input);

		HK_FORCE_INLINE static hkResult HK_CALL calcAabbAndQueryTree(
											const hkpCdBody& bodyA,	const hkpCdBody& bodyB, const hkTransform& bTa,
											const hkVector4& linearTimInfo, const hkpProcessCollisionInput& input,
											hkAabb* cachedAabb, hkArray<hkpShapeKey>& hitListOut );
	public:

		/// Constructor, called by the agent creation function.
		hkpBvTreeAgent( hkpContactMgr* mgr );

	protected:

		static hkpCollisionAgent* HK_CALL defaultAgentCreate( const hkpCdBody& bodyA, const hkpCdBody& bodyB, const hkpCollisionInput& env, hkpContactMgr* mgr );


			// interal method
		HK_FORCE_INLINE void prepareCollisionPartnersProcess   ( const hkpCdBody& bodyA,	const hkpCdBody& bodyB,	const hkpProcessCollisionInput& input, hkCollisionConstraintOwner& constraintOwner);

		static void HK_CALL calcAabbLinearCast(const hkpCdBody& bodyA, const hkpCdBody& bodyB, const hkpLinearCastCollisionInput& input, hkAabb& aabbOut);

		static void HK_CALL staticCalcAabb(const hkpCdBody& bodyA, const hkpCdBody& bodyB, const hkpCollisionInput& input, hkAabb& aabbOut);



		///Destructor, called by cleanup().
		~hkpBvTreeAgent(){}

		struct hkpBvAgentEntryInfo
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_COLLIDE, hkpBvTreeAgent::hkpBvAgentEntryInfo );

			hkpShapeKey m_key;
			hkInt32 m_userInfo;
			hkpCollisionAgent* m_collisionAgent;

			hkpShapeKey& getKey() { return m_key; }
			void setKey( hkpShapeKey& key) { m_key = key; }
		};

		/// AabbCast collector used in some linear cast implementations to process the aabb cast results
		struct LinearCastAabbCastCollector : public hkpAabbCastCollector
		{		
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_COLLIDE, hkpBvTreeAgent::LinearCastAabbCastCollector);

			HK_FORCE_INLINE LinearCastAabbCastCollector(const hkpCdBody& castBody, const hkpCdBody& bvTreeBody, 
														const hkpLinearCastCollisionInput& input,	 
														hkpCdPointCollector& castCollector, 
														hkpCdPointCollector* startCollector)
				: m_castBody(castBody), m_bvTreeBody(bvTreeBody), m_input(input), m_castCollector(castCollector),
				  m_startCollector(startCollector)				  
			{}

			virtual void addHit(hkpShapeKey key);

			const hkpCdBody& m_castBody;
			const hkpCdBody& m_bvTreeBody;
			const hkpLinearCastCollisionInput& m_input;
			hkpCdPointCollector& m_castCollector;
			hkpCdPointCollector* m_startCollector;			
		};

		hkArray<hkpBvAgentEntryInfo> m_collisionPartners;
		hkAabb	m_cachedAabb;

		/// You'll need to set this to false if you want changes to your ShapeCollection, which do not alter the AABB, to be reflected
		/// in the collision detection.
		static hkBool m_useAabbCaching;


			/// Agent creation function used by the hkpCollisionDispatcher.
		static hkpCollisionAgent* HK_CALL createShapeBvAgent( const hkpCdBody& bodyA, const hkpCdBody& bodyB, const hkpCollisionInput& input, hkpContactMgr* mgr );

			/// Agent creation function used by the hkpCollisionDispatcher.
		static hkpCollisionAgent* HK_CALL createBvTreeShapeAgent( const hkpCdBody& bodyA, const hkpCdBody& bodyB, const hkpCollisionInput& input, hkpContactMgr* mgr );

			/// Agent creation function used by the hkpCollisionDispatcher.
		static hkpCollisionAgent* HK_CALL createBvBvAgent( const hkpCdBody& bodyA, const hkpCdBody& bodyB, const hkpCollisionInput& input, hkpContactMgr* mgr );

};

#endif // HK_COLLIDE2_BV_TREE_SHAPE_AGENT_H

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
