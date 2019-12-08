/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKCD_PLANE_COLLECTION_H
#define HKCD_PLANE_COLLECTION_H

#include <Geometry/Collide/DataStructures/PlanarGeometry/Primitives/hkcdPlanarGeometryPrimitives.h>

/// Set of plane that can be shared amongst the geometries
class hkcdPlaneCollection : public hkReferencedObject
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_GEOMETRY);

		typedef hkcdPlanarGeometryPrimitives::Plane		Plane;
		typedef hkcdPlanarGeometryPrimitives::PlaneId	PlaneId;

	public:

		/// Constructor
		hkcdPlaneCollection();

		/// Copy constructor
		hkcdPlaneCollection(const hkcdPlaneCollection& other);

		/// Constructor from array of planes
		hkcdPlaneCollection(const hkArray<Plane>& planes);

	public:

		/// Welds the planes so that all planes are unique
		void weldPlanes(hkArray<int>* planeRemapTable = HK_NULL);

		/// Applies the given transform on the planes. Note that this will lose precision!
		void transformPlanes(const hkQTransform& transform, int numBitsTransform);

		/// Computes the maximum number of bits used by the plane equations
		void computeMaxNumUsedBits(int& numBitsNormal, int& numBitsOffset) const;

	public:

		/// Returns the given plane
		HK_FORCE_INLINE void getPlane(PlaneId planeId, Plane& planeOut) const;

		// Adds a new plane
		HK_FORCE_INLINE PlaneId addPlane(const Plane& plane);

		/// Returns the array of planes
		HK_FORCE_INLINE const hkArray<Plane>& getPlanes() const;
		HK_FORCE_INLINE hkArray<Plane>& accessPlanes();

	protected:

		hkArray<Plane> m_planes;	///< The planes

};

#include <Geometry/Collide/DataStructures/PlanarGeometry/hkcdPlaneCollection.inl>

#endif	//	HKCD_PLANE_COLLECTION_H

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
