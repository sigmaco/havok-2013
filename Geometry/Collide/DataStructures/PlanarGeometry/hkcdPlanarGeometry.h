/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKCD_PLANAR_GEOMETRY_H
#define HKCD_PLANAR_GEOMETRY_H

#include <Common/Base/Math/Vector/hkIntVector.h>
#include <Geometry/Collide/DataStructures/PlanarGeometry/hkcdPlanarEntity.h>
#include <Geometry/Collide/DataStructures/PlanarGeometry/Predicates/hkcdPlanarGeometryPredicates.h>
#include <Geometry/Collide/DataStructures/PlanarGeometry/hkcdPlaneCollection.h>

#include <Common/Base/Container/BitField/hkBitField.h>

/// Geometry representation where vertices are stored implicitly as intersections of 3 planes.
class hkcdPlanarGeometry : public hkcdPlanarEntity
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_GEOMETRY);

	public:

		/// Orientation cache
		template <int N>
		struct OrientationCache
		{
			public:

				/// Constructor. Initializes the multiplier with 4 large prime numbers
				HK_FORCE_INLINE OrientationCache();

				/// Computes the orientation for the given planes and updates the cache
				HK_FORCE_INLINE Orientation getOrientation(hkIntVectorParameter planeIds, const Plane& pA, const Plane& pB, const Plane& pC, const Plane& pD);

			protected:

				hkIntVector m_mul;
				hkArray<hkIntVector> m_data;
		};

		typedef OrientationCache<12> DefaultOrientationCache;

	public:

		/// Constructor
		hkcdPlanarGeometry(hkcdPlanarEntityDebugger* debugger = HK_NULL);

		// Constructor
		hkcdPlanarGeometry(const hkAabb& coordinateConversionAabb, int initialPolyCapacity = 0, int initialPlaneCapacity = 0, hkcdPlanarEntityDebugger* debugger = HK_NULL);

		/// Copy constructor
		hkcdPlanarGeometry(const hkcdPlanarGeometry& other, bool copyPolygons, bool clonePlanes);

	public:

		/// Converts a vertex from / to float to / from fixed-precision
		HK_FORCE_INLINE void convertWorldPosition(hkVector4Parameter vSrc, hkIntVector& vDst) const;
		HK_FORCE_INLINE void convertFixedPosition(hkIntVectorParameter vSrc, hkVector4& vDst) const;

		/// Converts a direction from world to fixed-precision
		HK_FORCE_INLINE void convertWorldDirection(hkVector4Parameter vSrc, hkIntVector& vDst) const;

		/// Converts the plane equation for the given planeId to world
		HK_FORCE_INLINE void convertPlaneEquation(PlaneId planeId, hkVector4& worldPlaneEqnOut) const;

		/// Gets / sets the offset that has been applied to all coordinates
		HK_FORCE_INLINE const hkVector4& getPositionOffset() const;
		HK_FORCE_INLINE void setPositionOffset(hkVector4Parameter vOffset);

		/// Gets / sets the scale that has been applied to all coordinates
		HK_FORCE_INLINE const hkSimdReal getPositionScale() const;
		HK_FORCE_INLINE void setPositionScale(hkSimdRealParameter scale);

		/// Retrieves all valid polygon Ids
		void getAllPolygons(hkArray<PolygonId>& polygonsOut) const;

		/// Collects all planes used by the given polygons
		void getAllPolygonsPlanes(const hkArray<PolygonId>& polygonsIn, hkArray<PlaneId>& planesOut, bool collectBoundaryPlanes) const;

		/// Classifies a triangle w.r.t. a plane. The result is approximative, as it uses floating-point operations
		hkcdPlanarGeometryPredicates::Orientation approxClassify(PolygonId polygonId, PlaneId planeId) const;

		/// Classifies a triangle w.r.t. a plane
		hkcdPlanarGeometryPredicates::Orientation classify(PolygonId polygonId, PlaneId planeId, DefaultOrientationCache& orientationCache) const;

		/// Splits a polygon with the given splitting plane. Returns the part of the polygon inside the given plane
		void split(PolygonId polygonId, PlaneId splitPlaneId, DefaultOrientationCache& orientationCache, PolygonId& insidePolygonIdOut, PolygonId& outsidePolygonIdOut);

		/// Returns true if two given polygon on the same support plane potentially overlap. False means that the surfaces of the two polygon do not overlap.
		bool check2dIntersection(const PolygonId& polygonA, const PolygonId& polygonB, DefaultOrientationCache& orientationCache) const;
		static bool HK_CALL check2dIntersection(const hkcdPlanarGeometry& geomA, const PolygonId& polygonIdA,
												const hkcdPlanarGeometry& geomB, const PolygonId& polygonIdB,
												DefaultOrientationCache& orientationCache);

		/// Clips a polygon with the given planes. Returns the number of boundary planes.
		hkUint32 clipPolygon(PlaneId supportPlaneId, PlaneId*& boundsIn, PlaneId*& boundsOut, int numBounds, DefaultOrientationCache& orientationCache, const PlaneId* clippingPlanesIn, int numClippingPlanesIn);

		/// Removes the given polygons from the mesh
		void removePolygons(const hkArray<PolygonId>& polygonIds);

		/// Removes all polygons that are not present in the given list. The given list of polygon Ids must be sorted ascending!
		void keepPolygons(const hkArray<PolygonId>& polygonIds);

		/// Builds a vertex-based geometry representation from this entity.
		virtual void extractGeometry(hkGeometry& geomOut) const HK_OVERRIDE;

		/// Builds a vertex-based geometry representation for the given polygon
		void extractPolygonGeometry(PolygonId polyId, hkGeometry& geomOut) const;

		/// Welds the planes so that all planes are unique
		void weldPlanes(hkArray<int>* planeRemapTable = HK_NULL);

		/// Adds all polygons from the given geometry to this geometry. The planes are assumed to be already present in this geometry,
		/// and a mapping from other to this geometry planes is expected as input
		void appendGeometryPolygons(const hkcdPlanarGeometry& srcGeom, const int* HK_RESTRICT planeRemapTable, hkArray<PolygonId>& addedPolygonIdsOut);

		/// Adds the given polygons to this geometry and returns the newly added polygon Ids.
		void appendGeometryPolygons(const hkcdPlanarGeometry& srcGeom, const hkArray<PolygonId>& srcPolygonIds, bool flipWinding, hkArray<PolygonId>& dstPolygonIds);

		/// Applies the given transform on the planes. Note that this will lose precision!
		void transformPlanes(const hkQTransform& transform, int numBitsTransform);

		/// Inverts all the polygons
		void invert();

		/// Computes the maximum number of bits used by the plane equations
		void computeMaxNumUsedBits(int& numBitsNormal, int& numBitsOffset) const;

		/// Removes all unused planes from the geometry.
		void removeUnusedPlanes(const hkBitField& keepPlanes, hkArray<int>* planeRemapOut);

	public:

		/// Set the plane collection associated with this geometry
		HK_FORCE_INLINE void setPlaneCollection(hkcdPlaneCollection* planes);

		/// Returns the plane collection associated with this geometry
		HK_FORCE_INLINE const hkcdPlaneCollection* getPlaneCollection() const;
		HK_FORCE_INLINE hkcdPlaneCollection* accessPlaneCollection();

		/// Return whether this geometry shares its plane with an other one
		HK_FORCE_INLINE bool sharesPlanesWith(const hkcdPlanarGeometry& other) const;

		/// Adds a new polygon
		HK_FORCE_INLINE PolygonId addPolygon(PlaneId supportPlane, hkUint32 material, int numBounds);

		/// Returns the polygon at the given Id
		HK_FORCE_INLINE const Polygon& getPolygon(PolygonId polyId) const;
		HK_FORCE_INLINE Polygon& accessPolygon(PolygonId polyId);

		/// Computes the number of boundary planes
		HK_FORCE_INLINE int getNumBoundaryPlanes(PolygonId polyId) const;

		/// Returns the collection of polygons
		HK_FORCE_INLINE const hkcdPlanarGeometryPolygonCollection& getPolygons() const;
		HK_FORCE_INLINE hkcdPlanarGeometryPolygonCollection& accessPolygons();

		/// Returns the array of planes
		HK_FORCE_INLINE const hkArray<Plane>& getPlanes() const;
		HK_FORCE_INLINE hkArray<Plane>& accessPlanes();

		/// Returns the offset & scale
		HK_FORCE_INLINE const hkVector4& getConversionOffset() const;
		HK_FORCE_INLINE const hkSimdReal getConversionScale() const;

	protected:

		hkVector4 m_offsetAndScale;						///< Offset that needs to be added to all points stored in the mesh. The scale is encoded in the .w component.
		hkRefPtr<hkcdPlaneCollection> m_planes;			///< The planes
		hkcdPlanarGeometryPolygonCollection m_polys;	///< The polygons
};

#include <Geometry/Collide/DataStructures/PlanarGeometry/hkcdPlanarGeometry.inl>

#endif	//	HKCD_PLANAR_GEOMETRY_H

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
