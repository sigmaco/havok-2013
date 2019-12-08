/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_MATH_AABB_H
#define HK_MATH_AABB_H

extern const class hkClass hkAabbClass;

extern const class hkClass hkAabbUint32Class;

/// Axis aligned bounding box.
class hkAabb
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_CDINFO, hkAabb);
		HK_DECLARE_REFLECTION();
#ifndef HK_DISABLE_MATH_CONSTRUCTORS
			/// An empty constructor, does not initialize anything.
		hkAabb() { }

			///Creates a new AABB with the specified dimensions.
		HK_FORCE_INLINE hkAabb(const hkVector4& min, const hkVector4& max);
#endif
			
			/// Set from center and radius.
		HK_FORCE_INLINE void setFromCenterRadius(const hkVector4& center, const hkSimdReal& radius) { hkVector4 r; r.setAll(radius); m_min.setSub(center, r); m_max.setAdd(center, r); }

			/// Set from a point.
		HK_FORCE_INLINE void setFromPoint(const hkVector4& x) { m_min = x; m_max = x; }

			/// Set from a line.
		HK_FORCE_INLINE void setFromLine(const hkVector4& x, const hkVector4& y) { m_min.setMin(x, y); m_max.setMax(x, y); }

			/// Set from a triangle.
		HK_FORCE_INLINE void setFromTriangle(const hkVector4& x, const hkVector4& y, const hkVector4& z) { setFromLine(x,y); includePoint(z); }

			/// Set from a tetrahedron.
		HK_FORCE_INLINE void setFromTetrahedron(const hkVector4& x, const hkVector4& y, const hkVector4& z, const hkVector4& w) { setFromTriangle(x,y,z); includePoint(w); }

			/// Returns true if the given AABB overlaps with this one. Zero volume overlaps are reported as an overlap.
		HK_FORCE_INLINE hkBool32 overlaps( const hkAabb& testAabb ) const;

			/// Returns true if the given AABB overlaps with this one. Zero volume overlaps are reported as NOT as an overlap.
			/// If there is no hit, smallestNonHitAabbInOut is reduced so that if 'this' is replaced by the new smallestNonHitAabbInOut,
			/// no hit will be produced as well.
		HK_FORCE_INLINE hkBool32 overlapsUpdateSmallestNonExtraHitAabb( const hkAabb& other, hkAabb& smallestNonHitAabbInOut ) const;


			/// Is this a valid AABB? I.e. no NaNs and min[i] <= max[i].
		bool isValid() const;

			/// Return true if 'other' is enclosed in this AABB.
			/// Boundaries are inclusive.
		HK_FORCE_INLINE hkBool32 contains(const hkAabb& other) const;

			/// Return true if 'other' is not enclosed by this AABB.
			/// Boundaries are exclusive.
		HK_FORCE_INLINE hkBool32 notContains(const hkAabb& other) const;

			/// Return true if 'other' is enclosed in this AABB.
			/// Boundaries are inclusive.
		HK_FORCE_INLINE hkBool32 containsPoint(const hkVector4& other) const;

			/// Extends the AABB to include the given point.
		HK_FORCE_INLINE void includePoint (const hkVector4& point);

			/// Extends the AABB to include the given AABB.
		HK_FORCE_INLINE void includeAabb (const hkAabb& aabb);

			/// Set the AABB to encompass all values between -HK_REAL_MAX and HK_REAL_MAX.
		HK_FORCE_INLINE void setFull();

			/// Sets the AABB to an empty (invalid) MAX_REAL/MIN_REAL box.
		HK_FORCE_INLINE void setEmpty ();

			/// Returns true if the AABB is empty, e.g., its min is greater than its max for any dimension.
		HK_FORCE_INLINE bool isEmpty() const;

			/// Returns the centre of the AABB.
		HK_FORCE_INLINE void getCenter( hkVector4& c ) const;

			/// Returns the sum of min and max (getCenter() * 2).
		HK_FORCE_INLINE void getCenter2( hkVector4& c ) const;

			/// Returns the half extents of the AABB.
		HK_FORCE_INLINE void getHalfExtents( hkVector4& he ) const;

			/// Returns the extents of the AABB.
		HK_FORCE_INLINE void getExtents( hkVector4& e ) const;

			/// Return a corner vertex of an AABB.
		HK_FORCE_INLINE void getVertex(int index, hkVector4& vertex) const;

			/// Increase the maximum and decrease the minimum in each direction by the given amount
		HK_FORCE_INLINE void expandBy( hkSimdRealParameter exp );

			/// Extrude the AABB in the direction specified.
		HK_FORCE_INLINE void expandInDirection( hkVector4Parameter exp );

			/// Scale the AABB.
		HK_FORCE_INLINE void scaleBy( hkSimdRealParameter scale );

			/// Increase the maximum and decrease the minimum in each direction by the given amount
		HK_FORCE_INLINE void setExpandBy( const hkAabb& aabb, hkSimdRealParameter exp );

			/// Returns true if the AABB is strictly the same as \a a.
		HK_FORCE_INLINE hkBool32 equals(const hkAabb& aabb) const;

			/// Sets the AABB to be the intersection AABB of the two given input AABBs.
			/// The result can be invalid if the two input AABBs do not overlap. Use isEmpty() to verify this.
		HK_FORCE_INLINE void setIntersection(const hkAabb& aabb0, const hkAabb& aabb1);

			/// Sets the AABB to empty if (m_min > m_max)
		HK_FORCE_INLINE void setEmptyIfInvalid();

			/// Sets the AABB to be the union of two others.
		HK_FORCE_INLINE void setUnion(const hkAabb& aabb0, const hkAabb& aabb1);

			/// Sets the AABB to be the Minkowski sum of two others.
		HK_FORCE_INLINE void setMinkowskiSum(const hkAabb& aabb0, const hkAabb& aabb1);

			/// Project a point on the AABB, Note: projection == point if the point is inside the AABB.
		HK_FORCE_INLINE void projectPoint(const hkVector4& point, hkVector4& projection) const;

	public:

			/// The minimum boundary of the AABB (i.e., the coordinates of the corner with the lowest numerical values).
		hkVector4 m_min;

			/// The maximum boundary of the AABB (i.e., the coordinates of the corner with the highest numerical values).
		hkVector4 m_max;
};

HK_CLASSALIGN16(struct) hkAabbUint32
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_CDINFO, hkAabbUint32);
	HK_DECLARE_REFLECTION();

	inline void operator=( const hkAabbUint32& other );

		/// set completely invalid
	inline void setInvalid();

		/// just make it non colliding for the midphase agent
	inline void setInvalidY();

	HK_ALIGN16( hkUint32 m_min[3] );
	hkUint8 m_expansionMin[3];
	hkUint8 m_expansionShift;
	hkUint32 m_max[3];
	hkUint8 m_expansionMax[3];
	hkUint8 m_shapeKeyByte; // lowest byte of the hkpShapeKey. Useful for hkpListShapes of less then 256 bodies.
};

#include <Common/Base/Types/Geometry/Aabb/hkAabb.inl>

#endif // HK_MATH_AABB_H

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
