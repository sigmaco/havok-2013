/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_COLLIDE_SHAPE_BASE_H
#define HKP_COLLIDE_SHAPE_BASE_H

#include <Geometry/Collide/Shapes/hkcdShape.h>
#include <Physics2012/Collide/Shape/hkpShapeBuffer.h>

class hkAabb;
struct hkpShapeRayCastInput;
struct hkpShapeRayCastOutput;
struct hkpShapeRayBundleCastInput;
struct hkpShapeRayBundleCastOutput;
class hkpRayHitCollector;
class hkpCdBody;
class hkpShapeContainer;
class hkSphere;
class hkpConvexShape;

typedef hkUint16 hkpVertexId;
typedef hkUint32 hkpShapeKey;


	/// Base interface for all physics shapes.
	/// Each virtual member function is implemented as a stub in this class, and should be reimplemented by derived shapes as required.
	/// Subsets of these functions may be registered on different SPU ELFs for each shape.
class hkpShapeBase : public hkcdShape
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_SHAPE );
		HK_DECLARE_REFLECTION();
		HKCD_DECLARE_SHAPE_TYPE( hkcdShapeType::INVALID );

	public:

			/// Empty constructor, leaves everything uninitialized, as it will only be called on SPU from the shape vtable util.
		HK_FORCE_INLINE hkpShapeBase() {}

			/// Constructor.
		HK_FORCE_INLINE hkpShapeBase( ShapeType type ) : hkcdShape(type) {}


			/// Serialization constructor.
		hkpShapeBase( class hkFinishLoadedObjectFlag flag );

			/// Returns true if the shape is a hkpConvexShape.
			
		virtual bool isConvex() const { return false; }


			/// Returns true if the shape is a hkpBvTreeShape.
		HK_FORCE_INLINE bool isBvTree() const;

			/// Returns true if the shape is a hkpShapeCollection.
		HK_FORCE_INLINE bool isCollection() const;

		//
		// Basic shape functions
		//

			/// Gets the AABB for the shape given a local to world transform and an extra tolerance.
		virtual void getAabb( const hkTransform& localToWorld, hkReal tolerance, hkAabb& aabbOut ) const;

			/// Finds the closest intersection between the shape and a ray defined in the shape's local space, starting 
			/// at fromLocal, ending at toLocal. The initial hit fraction in \a output will be used to clip the ray.
			/// The results will be placed in \a output, appending the shape key hierarchy to the current one. 
			/// If there is no hit, \a output remains unchanged.
			/// Implementation notes: For all convex shapes except hkSphere and hkCapsule the radius of the shape will 
			/// be ignored.			
		virtual hkBool castRay( const hkpShapeRayCastInput& input, hkpShapeRayCastOutput& output ) const;

			/// Finds the closest intersection between the shape and a ray defined in the shape's local space, starting at fromLocal, ending at toLocal.
			/// This is a callback driven raycast. For each hit found, the hkpRayHitCollector receives a callback with the hit info.
			/// Implementation notes: For all convex shapes except hkSphere and hkCapsule the radius of the shape will be ignored.
		virtual void castRayWithCollector( const hkpShapeRayCastInput& input, const hkpCdBody& cdBody, hkpRayHitCollector& collector ) const;

			/// Casts a bundle of rays against the shape.
			
		virtual hkVector4Comparison castRayBundle( const hkpShapeRayBundleCastInput& input, hkpShapeRayBundleCastOutput& output, hkVector4ComparisonParameter mask ) const;

		//
		// Convex shape functions
		//

			/// Returns the vertex furthest along a given input direction.
			/// Each vertex must be identifiable by a 16bit vertex id, which must be stored in the result using hkVector4::setInt24W().
		virtual void getSupportingVertex( hkVector4Parameter direction, hkcdVertex& supportingVertexOut ) const;

			/// Converts an array of input vertex ids as returned by getSupportingVertex into an array of vertices.
			/// The .w component of the vertices out has to be set to the vertex id using hkVector4::setInt24W().
		virtual void convertVertexIdsToVertices( const hkpVertexId* ids, int numIds, hkcdVertex* vertexArrayOut ) const;

			/// This function returns the center point of the convex object.
		virtual void getCentre( hkVector4& centreOut ) const;

			/// Returns the number of spheres that will be put into the sphereBuffer in the getCollisionSpheres() call.
		virtual int getNumCollisionSpheres() const;

			/// Gets a set of spheres representing a simplified shape. For instance, a box could return its eight corners.
		virtual const hkSphere* getCollisionSpheres( hkSphere* sphereBuffer ) const;

		//
		// Shape container functions
		//


			/// Called internally to "weld" contact points. This is only called for convex objects that are in a shape collection.
		virtual int weldContactPoint( hkpVertexId* featurePoints, hkUint8& numFeaturePoints, hkVector4& contactPointWs, const hkTransform* thisObjTransform, const class hkpConvexShape* collidingConvexShape, const hkTransform* collidingTransform, hkVector4& separatingNormalInOut ) const;
};

#include <Physics2012/Collide/Shape/hkpShapeBase.inl>

#endif	// HKP_COLLIDE_SHAPE_BASE_H

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
