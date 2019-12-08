/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_COLLIDE2_SPHERE_SHAPE_H
#define HK_COLLIDE2_SPHERE_SHAPE_H

#include <Physics2012/Collide/Shape/Convex/hkpConvexShape.h>
#include <Common/Base/Types/Geometry/Aabb/hkAabb.h>

extern const hkClass hkpSphereShapeClass;


	/// The hkpSphereShape class is a utility class for storing information representing a basic
	/// sphere shape. Note that the functions for getting and setting the radius are in the hkpConvexShape base class.
	/// Thus a sphere shape need not hold any data, it is simply an implicit point at the origin with a radius.
class hkpSphereShape : public hkpConvexShape
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SHAPE);
		HK_DECLARE_REFLECTION();
		HKCD_DECLARE_SHAPE_TYPE(hkcdShapeType::SPHERE);
		HK_DECLARE_GET_SIZE_FOR_SPU(hkpSphereShape);

	public:

			/// Empty constructor, to be called by the shape vtable util on SPU
		HK_FORCE_INLINE hkpSphereShape() {}
	
			/// Creates an arbitrary sphere with given radius.
		hkpSphereShape(hkReal radius);

		//
		// hkpShapeBase implementation

	public:

			// hkpShapeBase interface implementation.
		virtual HK_FORCE_INLINE void getSupportingVertex(hkVector4Parameter direction, hkcdVertex& supportingVertexOut) const;

			// hkpShapeBase interface implementation.
		virtual HK_FORCE_INLINE void convertVertexIdsToVertices(const hkpVertexId* ids, int numIds, hkcdVertex* verticesOut) const;

			// hkpShapeBase interface implementation.
		virtual HK_FORCE_INLINE void getCentre(hkVector4& centreOut) const;

			// hkpShapeBase interface implementation.
		virtual HK_FORCE_INLINE int getNumCollisionSpheres() const;

			// hkpShapeBase interface implementation.
		virtual HK_FORCE_INLINE const hkSphere* getCollisionSpheres(hkSphere* sphereBuffer) const;

			// hkpShapeBase interface implementation.
		virtual HK_FORCE_INLINE void getAabb(const hkTransform& localToWorld, hkReal tolerance, hkAabb& out) const;

			// hkpShapeBase interface implementation.
		virtual hkBool castRay(const hkpShapeRayCastInput& input, hkpShapeRayCastOutput& results) const;

			// hkpShapeBase interface implementation.
		virtual hkVector4Comparison castRayBundle(const hkpShapeRayBundleCastInput& input, hkpShapeRayBundleCastOutput& results, hkVector4ComparisonParameter mask) const;

	public:


			/// Serialization constructor
		hkpSphereShape( hkFinishLoadedObjectFlag flag );

			// hkpConvexShape interface implementation.
		virtual void getFirstVertex(hkVector4& v) const;


	public:

		hkUint32 m_pad16[3]; //+nosave
};

#include <Physics2012/Collide/Shape/Convex/Sphere/hkpSphereShape.inl>

#endif // HK_COLLIDE2_SPHERE_SHAPE_H

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
