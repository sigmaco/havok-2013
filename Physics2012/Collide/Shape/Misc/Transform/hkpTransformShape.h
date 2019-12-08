/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_TRANSFORM_SHAPE_H
#define HKP_TRANSFORM_SHAPE_H

#include <Physics2012/Collide/Shape/hkpShape.h>
#include <Physics2012/Collide/Shape/hkpShapeContainer.h>

extern const hkClass hkpTransformShapeClass;


	/// An hkpTransformShape contains an hkpShape and an additional transform for that shape.
	/// This is useful, for instance, if you want to position non-convex child shapes correctly
	/// when constructing a compound shape.
	/// You should avoid using a transform shape as the root shape of a rigid body.
class hkpTransformShape : public hkpShape
{
	public:

		HK_DECLARE_REFLECTION();
		HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_SHAPE );
		HKCD_DECLARE_SHAPE_TYPE( hkcdShapeType::TRANSFORM );

	public:

			/// Empty constructor, to be called by the shape vtable util on SPU
		HK_FORCE_INLINE hkpTransformShape() {}

			/// Constructs a new transform shape.
			/// This adds a reference to the child shape.
		hkpTransformShape( const hkpShape* childShape, const hkTransform& transform );

	public:

			/// Get the child shape.
		inline const hkpShape* getChildShape() const;

			/// Gets the transform from the child shape's space to this transform shape's local space.
		inline const hkTransform& getTransform() const;

			/// Gets the rotation part of the transform as a quaternion
		inline const hkQuaternion& getRotation() const;

			/// Sets the current transform.
			/// Don't do this once the shape is added to a world
			/// as the agents may have cached data dependent on it.
		void setTransform( const hkTransform& transform );

	public:

			// hkpShapeBase interface implementation.
		virtual void getAabb( const hkTransform& localToWorld, hkReal tolerance, hkAabb& out ) const;

			// hkpShapeBase interface implementation.
		virtual hkBool castRay( const hkpShapeRayCastInput& input, hkpShapeRayCastOutput& results ) const;

			// hkpShapeBase interface implementation.
		virtual void castRayWithCollector( const hkpShapeRayCastInput& input, const hkpCdBody& cdBody, hkpRayHitCollector& collector ) const;


			/// Serialization constructor
		hkpTransformShape( hkFinishLoadedObjectFlag flag );

			/// hkpShape interface implementation.
		virtual hkReal getMaximumProjection( const hkVector4& direction ) const;

			/// hkpShape interface implementation.
		virtual const hkpShapeContainer* getContainer() const;

		virtual int calcSizeForSpu( const CalcSizeForSpuInput& input, int spuBufferSizeLeft ) const;


		void getChildShapeFromPpu() const;

	protected:

		class hkpSingleShapeContainer m_childShape;
			// 0 if the child shape is following this hkpConvexTransformShape consecutively in memory, the size of the child shape otherwise
		mutable int m_childShapeSize; // +nosave

		hkQuaternion m_rotation;
		hkTransform m_transform;
};

#include <Physics2012/Collide/Shape/Misc/Transform/hkpTransformShape.inl>

#endif // HKP_TRANSFORM_SHAPE_H

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
