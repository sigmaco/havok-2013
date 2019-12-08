/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_COLLIDE2_CAPSULE_SHAPE_H
#define HK_COLLIDE2_CAPSULE_SHAPE_H

#include <Physics2012/Collide/Shape/Convex/hkpConvexShape.h>

extern const hkClass hkpCapsuleShapeClass;

	/// A capsule defined by two points and a radius.
	/// The points are stored internally as hkSpheres, each point being the center of one of the
	/// end spheres of the capsule.
class hkpCapsuleShape : public hkpConvexShape
{
	public:
		
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SHAPE);
		HK_DECLARE_REFLECTION();
		HKCD_DECLARE_SHAPE_TYPE(hkcdShapeType::CAPSULE);
		HK_DECLARE_GET_SIZE_FOR_SPU(hkpCapsuleShape);

	public:

			/// For raycasting, the part of the shape hit.
		enum RayHitType
		{
			HIT_CAP0,
			HIT_CAP1,
			HIT_BODY,
		};

	public:

		/// Empty constructor, to be called by the shape vtable util on SPU
		HK_FORCE_INLINE hkpCapsuleShape()
		{}

			/// Creates a new hkpCapsuleShape using the specified points and radius
		hkpCapsuleShape( const hkVector4& vertexA,const hkVector4& vertexB, hkReal radius );

			/// Allocates a new capsule shape at the given memory location
		static HK_FORCE_INLINE hkpCapsuleShape* HK_CALL createInPlace(hkUint8*& memPtr, const hkVector4& vertexA,const hkVector4& vertexB, hkReal radius);

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
		virtual const hkSphere* getCollisionSpheres(hkSphere* sphereBuffer) const;

			// hkpShapeBase interface implementation.
		virtual void getAabb(const hkTransform& localToWorld, hkReal tolerance, hkAabb& out) const;

			// hkpShapeBase interface implementation.
		virtual hkBool castRay(const hkpShapeRayCastInput& input, hkpShapeRayCastOutput& results) const;

	public:

			/// Gets the pointer to the first vertex. This casts the corresponding hkSphere (m_vertexA) to a hkVector4*.
			/// You can then index by 0 or 1, to get the first or second vertex respectively.
		inline const hkVector4* getVertices() const;

			/// Gets a vertex given an index "i". "i" can be 0 or 1. This casts the corresponding hkSphere to a hkVector4.
		HK_FORCE_INLINE const hkVector4& getVertex(int i) const;
		template <int I> HK_FORCE_INLINE const hkVector4& getVertex() const;

			/// Sets a vertex given an index "i". "i" can be 0 or 1.
		HK_FORCE_INLINE void setVertex(int i, const hkVector4& position );
		template <int I> HK_FORCE_INLINE void setVertex(hkVector4Parameter position );


			/// Serialization constructor
		hkpCapsuleShape( hkFinishLoadedObjectFlag flag );

			// hkpConvexShape interface implementation.
		virtual void getFirstVertex(hkVector4& v) const;


	public:

		static void HK_CALL closestPointLineSeg( const hkVector4& A, const hkVector4& B, const hkVector4& B2, hkVector4& pt );
		static void HK_CALL closestInfLineSegInfLineSeg( const hkVector4& A, const hkVector4& dA, const hkVector4& B, const hkVector4& dB, hkReal& distSquared, hkReal& t, hkReal &u, hkVector4& p, hkVector4& q );

	protected:

		// The line's first point.
		hkVector4  m_vertexA;

		// The line's second point.
		hkVector4  m_vertexB;
};

#include <Physics2012/Collide/Shape/Convex/Capsule/hkpCapsuleShape.inl>

#endif // HK_COLLIDE2_CAPSULE_SHAPE_H

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
