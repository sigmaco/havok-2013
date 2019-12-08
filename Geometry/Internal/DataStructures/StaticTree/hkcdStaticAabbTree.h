/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_STATIC_TREE
#define HK_STATIC_TREE

//HK_HAVOK_ASSEMBLY_EXCLUDE_FILE

#include <Geometry/Internal/Algorithms/TreeQueries/hkcdAabbTreeQueries.h>

extern const class hkClass hkcdStaticTreeDefaultTreeStorage6Class;
extern const class hkClass hkStaticTreeClass;

	/// Bounding volume tree that can't be updated.
	/// It is built from an hkcdDynamicAabbTree, then optimized for data size.
class hkcdStaticAabbTree : public hkReferencedObject
{
public:
		//+version(1)
	HK_DECLARE_REFLECTION();
	HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_GEOMETRY );

	typedef hkUint32 TreeHandle;

	hkcdStaticAabbTree();
	hkcdStaticAabbTree( hkFinishLoadedObjectFlag f);

	virtual ~hkcdStaticAabbTree();

		/// Construct the static tree from an existing hkcdDynamicAabbTree.
		/// Note that this does not optimize the layout of the tree; hkcdDynamicAabbTree::rebuild should be called first.
	void buildFromDynamicTree( const class hkcdDynamicAabbTree* dynTree );

		/// Cast a ray through the tree. The collector's callback is triggered for each leaf in the tree that is hit
	hkBool32 castRay( hkVector4Parameter start, hkVector4Parameter end, hkcdAabbTreeQueries::RaycastCollector* collector) const;

		/// AABB check on the tree. The collector's callback is triggered for each leaf that overlaps with the AABB.
	void queryAabb( const hkAabb& aabb, hkcdAabbTreeQueries::AabbCollector* collector) const;

		/// Special-case AABB query where only the leaf IDs are saved.
		/// This is about 10% than the collector-based version (depending on platform).
	void queryAabb( const hkAabb& aabb, hkArray<hkUint32>::Temp& hits ) const;

		/// Find the closest leaf in the tree. The collector's callback is triggered for each leaf that is closer to the current smallest distance, starting at maxDistance.
	hkUint32 getClosestPoint( hkVector4Parameter point, hkSimdRealParameter maxDistance, hkcdAabbTreeQueries::ClosestPointCollector* collector, hkVector4& closestPointOut ) const;

		/// Returns the size (in bytes) of the tree.
	int getMemoryFootPrint() const;

		/// Returns the number of leaves in the tree.
	int getNumLeaves() const;

		/// Accessor for the internal tree.
	const void* getTreePtr() const { return m_treePtr; }

		/// Accessor for the internal tree.
	void* getTreePtr() { return m_treePtr; }

		/// Whether or not the tree should be deleted in hkcdStaticAabbTree destructor.
		/// This is set automatically depending on whether or not the hkcdStaticAabbTree is reference-counted,
		/// but can be overridden.
	hkBool m_shouldDeleteTree; //+nosave

protected:
	void* m_treePtr; //+overridetype(hkcdStaticTree::DefaultTreeStorage6*)
};

#endif // HK_STATIC_TREE

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
