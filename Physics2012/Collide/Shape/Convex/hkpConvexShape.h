/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_CONVEX_SHAPE_H
#define HKP_CONVEX_SHAPE_H

#include <Physics2012/Collide/Shape/HeightField/hkpSphereRepShape.h>
#include <Physics2012/Collide/Shape/hkpShapeContainer.h>

extern const class hkClass hkpConvexTransformShapeBaseClass;
 

class hkcdVertex;
extern const hkClass hkpConvexShapeClass;

extern hkReal hkConvexShapeDefaultRadius;

#define HK_W_NOT_SET_TO_VERTEX_ID "The function getSupportingVertex did not set the .w component of the supporting vertex to the vertex id using setInt24W"


	/// An interface shape class that allows its implementations to work with GJK. It also holds an extra radius to allow for shells around objects.
class hkpConvexShape : public hkpSphereRepShape
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_SHAPE );
		HK_DECLARE_REFLECTION();
		HKCD_DECLARE_SHAPE_TYPE( hkcdShapeType::CONVEX );

		typedef hkpVertexId VertexId;

		enum WeldResult
		{
			WELD_RESULT_REJECT_CONTACT_POINT,
			WELD_RESULT_ACCEPT_CONTACT_POINT_MODIFIED,
			WELD_RESULT_ACCEPT_CONTACT_POINT_UNMODIFIED
		};

	public:

			/// Empty constructor, called by the shape vtable util on SPU
		HK_FORCE_INLINE hkpConvexShape() {}

	protected:

			// Protected constructor which must be supplied with a type and a radius
		inline hkpConvexShape( ShapeType type, hkReal radius );

	public:

			/// This function returns the center point of the convex object. This is used for welding calculations.
		virtual void getCentre( hkVector4& centreOut ) const;

			/// Called internally to "weld" contact points. This is only called for convex objects that are in a shape collection.
		virtual int weldContactPoint(hkpVertexId* featurePoints, hkUint8& numFeaturePoints, hkVector4& contactPointWs, const hkTransform* thisObjTransform, const hkpConvexShape* collidingShape, const hkTransform* collidingTransform, hkVector4& separatingNormalInOut ) const;

			/// This implementation of the callback driven castRay uses the data driven castRay function.
			/// Implementation notes: For all convex shapes except hkSphere and hkCapsule the radius of the shape will be ignored.
		virtual void castRayWithCollector(const hkpShapeRayCastInput& input, const hkpCdBody& cdBody, hkpRayHitCollector& collector) const;

	public:


			/// Serialization constructor
		hkpConvexShape( hkFinishLoadedObjectFlag flag );
		
			/// Returns the first vertex of this shape. This is only used for initialization of collision detection data.
			/// it has to set the .w component of v to the vertex id using hkVector4::setInt24W
		virtual void getFirstVertex(hkVector4& v) const = 0;

		virtual bool isConvex() const { return true; }

			/// This is an implementation of the hkpShape::getMaximumProjection() function using getSupportingVertex.
		virtual hkReal getMaximumProjection( const hkVector4& direction ) const;

			/// Returns the size of the derived class.
		virtual int getSize() const { HK_ERROR( 0x97ef335c, "Not implemented" ); return 0; }


			/// Gets the extra radius.
			/// The radius is used to create a thin "shell" around the object that is used as the shape's surface for collision detection purposes.
			/// This can improve performance, as calculations for shapes that are actually interpenetrating are much more time-consuming than for interpenetrating shells.
		inline const hkReal& getRadius() const;

			/// Sets the extra radius
		inline void setRadius         (hkReal radius);
		inline void setRadiusUnchecked(hkReal radius);

	protected:

		hkReal m_radius;
};


	/// Base class for convex transform shapes
class hkpConvexTransformShapeBase : public hkpConvexShape
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_SHAPE );
		HK_DECLARE_REFLECTION();

	public:

			/// Empty constructor, to be called by the shape vtable util on SPU
		HK_FORCE_INLINE hkpConvexTransformShapeBase() {}


			/// Serialization constructor
		hkpConvexTransformShapeBase( class hkFinishLoadedObjectFlag flag )
		:	hkpConvexShape(flag)
		,	m_childShape(flag)
		{}

		
	protected:

			// The protected constructor which must be supplied with a type and a radius
		hkpConvexTransformShapeBase( ShapeType type, hkReal radius, const hkpConvexShape* childShape, hkpShapeContainer::ReferencePolicy ref );

	protected:

		void getChildShapeFromPpu(int thisShapeSize) const;

		class hkpSingleShapeContainer m_childShape;

			// 0 if the child shape is following this shape consecutively in memory, the size of the child shape otherwise
		mutable int m_childShapeSizeForSpu; // +nosave
};

#include <Physics2012/Collide/Shape/Convex/hkpConvexShape.inl>

#endif // HKP_CONVEX_SHAPE_H

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
