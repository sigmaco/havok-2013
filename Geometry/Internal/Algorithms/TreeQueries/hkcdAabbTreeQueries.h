/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKAI_TREE_QUERIES
#define HKAI_TREE_QUERIES

class hkAabb;

	/// Interface for queries through an hkcdStaticAabbTree or hkcdDynamicAabbTree
class hkcdAabbTreeQueries
{
public:
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_AI, hkcdAabbTreeQueries);

		/// Interface for raycasting
	class RaycastCollector
	{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_AI, RaycastCollector );
		RaycastCollector() {}
		virtual ~RaycastCollector() {}

			/// Callback that is triggered when the ray reaches a leaf of the tree.
			/// Returns true if the ray hit the leaf.
			/// If the cast against the leaf hits, hitFractionInOut should be updated to the smaller hit fraction.
		virtual hkBool32 processLeaf( hkUint32 leafKey, const hkAabb& leafAabb, hkSimdReal& hitFractionInOut) = 0;
	};

		/// Interface for AABB querues
	class AabbCollector
	{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_AI, AabbCollector );
		AabbCollector() {}
		virtual ~AabbCollector() {}

			/// Callback that is triggered when the AABB overlaps a leaf of the tree
			/// The query will stop if it returns false.
		virtual hkBool32 processLeaf( hkUint32 leafKey, const hkAabb& leafAabb ) = 0;
	};

		/// Interface for closest point queries
	class ClosestPointCollector
	{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_AI, ClosestPointCollector );
		ClosestPointCollector() {}
		virtual ~ClosestPointCollector() {}

			/// Callback that is triggered when the query is near a leaf of the tree.
			/// Returns the distance squared to leaf, and sets closestPointOut to be the closest point on the leaf
		virtual hkSimdReal processLeaf( hkUint32 leafKey, const hkAabb& leafAabb, hkVector4Parameter queryPoint, hkVector4& closestPointOut, hkSimdRealParameter closestDistanceSquared ) = 0;
	};
};

#endif //HKAI_TREE_QUERIES

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
