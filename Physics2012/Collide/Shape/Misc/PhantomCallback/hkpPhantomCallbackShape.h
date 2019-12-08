/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_PHANTOM_CALLBACK_SHAPE_H
#define HKP_PHANTOM_CALLBACK_SHAPE_H

#include <Physics2012/Collide/Shape/hkpShape.h>

extern const hkClass hkpPhantomCallbackShapeClass;

class hkpCollidable;
struct hkpCollisionInput;


	/// This shape allows you to create "phantom" shapes, which have no physical effect in a scene but which can trigger events
	/// when other shapes come close. This shape is typically the child shape of a hkpBvShape,
	/// where the bounding volume of the hkpBvShape is the boundary used for the phantom.
class hkpPhantomCallbackShape : public hkpShape
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
		HK_DECLARE_REFLECTION();
		HKCD_DECLARE_SHAPE_TYPE( hkcdShapeType::PHANTOM_CALLBACK );

	public:
			
			/// Constructor
		hkpPhantomCallbackShape()
		:	hkpShape( HKCD_SHAPE_TYPE_FROM_CLASS(hkpPhantomCallbackShape) )
		{}


			/// Serialization constructor
		hkpPhantomCallbackShape( hkFinishLoadedObjectFlag flag );


	public:

			/// This callback is called when the phantom shape starts intersecting with another shape.
		virtual void phantomEnterEvent( const hkpCollidable* phantomColl, const hkpCollidable* otherColl,	const hkpCollisionInput& env ) = 0;

			/// This callback is called when the phantom shape stops intersecting with another shape.
		virtual void phantomLeaveEvent( const hkpCollidable* phantomColl, const hkpCollidable* otherColl ) = 0;

	public:

			/// hkpShapeBase interface implementation. Note that phantom shapes are most usually used in combination with an hkpBvShape,
			/// so getAabb() never gets called. However, if you are using the phantom shape directly with the broadphase, you need to
			/// implement this function. The default implementation returns an AABB with no volume.
 		virtual void getAabb(const hkTransform& localToWorld, hkReal tolerance, hkAabb& out) const;

			/// hkpShapeBase interface implementation. Always returns false
		virtual hkBool castRay( const hkpShapeRayCastInput& input, hkpShapeRayCastOutput& results ) const;

			// hkpShapeBase interface implementation
		virtual void castRayWithCollector( const hkpShapeRayCastInput& input, const hkpCdBody& cdBody, hkpRayHitCollector& collector ) const;
};

#endif // HKP_PHANTOM_CALLBACK_SHAPE_H

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
