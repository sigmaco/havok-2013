/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKCD_INT_AABB_H
#define HKCD_INT_AABB_H

#include <Common/Base/hkBase.h>
#include <Common/Base/Math/Vector/hkIntVector.h>

/// Integer coordinates AABB
struct hkcdIntAabb
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_GEOMETRY, hkcdIntAabb);

	public:

		/// Sets this = empty AABB
		HK_FORCE_INLINE void setEmpty();

		/// Enlarges the AABB to include the given point
		HK_FORCE_INLINE void includePoint(hkIntVectorParameter v);

		/// Expands the box by the given radius
		HK_FORCE_INLINE void expandBy(int radius);

		/// Returns true if the point is inside the AABB
		HK_FORCE_INLINE hkBool32 containsPoint(hkIntVectorParameter v) const;

		/// Sets the AABB to be the intersection AABB of the two given input AABBs.
		/// The result can be invalid if the two input AABBs do not overlap. Use isEmpty() to verify this.
		HK_FORCE_INLINE void setIntersection(const hkcdIntAabb& aabb0, const hkcdIntAabb& aabb1);

		/// Returns true if the AABB is empty, e.g., its min is greater than its max for any dimension.
		HK_FORCE_INLINE bool isEmpty() const;

	public:

		hkIntVector m_min;
		hkIntVector m_max;
};

#include <Geometry/Collide/DataStructures/IntAabb/hkcdIntAabb.inl>

#endif	// HKCD_INT_AABB_H

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
