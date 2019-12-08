/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_COLLIDE2_BOX_SHAPE_H
#define HK_COLLIDE2_BOX_SHAPE_H

#include <Physics2012/Collide/Shape/Convex/hkpConvexShape.h>

extern const hkClass hkpBoxShapeClass;

	/// A simple box shape centered around the origin.
class hkpBoxShape : public hkpConvexShape
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SHAPE);
		HK_DECLARE_REFLECTION();
		HKCD_DECLARE_SHAPE_TYPE(hkcdShapeType::BOX);
		HK_DECLARE_GET_SIZE_FOR_SPU(hkpBoxShape);

	public:

			/// Empty constructor, to be called by the shape vtable util on SPU
		HK_FORCE_INLINE hkpBoxShape()
		{}

			/// Creates a box with the given half extents ( An (X by Y by Z) box has the half-extents (X/2, Y/2, Z/2) ).
		hkpBoxShape(const hkVector4& halfExtents, hkReal radius = hkConvexShapeDefaultRadius);

		//
		//	hkpShapeBase implementation

	public:
		
		// Override for hkpShapeBase::getSupportingVertex.
		virtual void getSupportingVertex(hkVector4Parameter direction, hkcdVertex& supportingVertexOut) const;

		// Override for hkpShapeBase::convertVertexIdsToVertices.
		virtual void convertVertexIdsToVertices(const hkpVertexId* ids, int numIds, hkcdVertex* verticesOut) const;

		// Override for hkpShapeBase::getCentre.
		virtual void getCentre(hkVector4& centreOut) const;

		// Override for hkpShapeBase::getNumCollisionSpheres.
		virtual HK_FORCE_INLINE int getNumCollisionSpheres() const;

		// Override for hkpShapeBase::getCollisionSpheres.
		virtual const hkSphere* getCollisionSpheres(hkSphere* sphereBuffer) const;

		// Override for hkpShapeBase::getAabb.
		virtual void getAabb(const hkTransform& localToWorld, hkReal tolerance, hkAabb& out) const;

		// Override for hkpShapeBase::castRay.
		virtual hkBool castRay(const hkpShapeRayCastInput& input, hkpShapeRayCastOutput& results) const;

	public:

			/// Gets the half extents ( An (X by Y by Z) box has the half-extent (X/2, Y/2, Z/2) ).
		inline const hkVector4& getHalfExtents() const;

			/// Sets the half extents. Note that changing the half extents will not wake up sleeping objects.
		void setHalfExtents(const hkVector4& halfExtents);


			/// Serialization constructor
		hkpBoxShape( hkFinishLoadedObjectFlag flag );

			/// Destructor
		~hkpBoxShape();

			// hkpConvexShape interface implementation.
		virtual void getFirstVertex(hkVector4& v) const;

		
	protected:

		hkVector4 m_halfExtents;
};

#include <Physics2012/Collide/Shape/Convex/Box/hkpBoxShape.inl>

#endif // HK_COLLIDE2_BOX_SHAPE_H

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
