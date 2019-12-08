/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_UNIONFIND_H
#define HK_UNIONFIND_H

#include <Common/Base/Container/LocalArray/hkLocalBuffer.h>

/// A class for partitioning sets into connected subsets.
/// This implementation uses the integers [0,n] as nodes
/// and generates subsets all at once via the setEdges method.
/// We can then query for (a) connected nodes or (b) the sets
/// of edges which connect the nodes.
///
/// Example use:
/// \code
/// hkUnionFind unionFind;
/// hkUnionFind::EdgeVector edges;
/// // pushBack objects created using hk_make_pair(edgeStart,edgeEnd)
/// unionFind.setEdges(edges, numberOfVertices);
/// // Now we can extract all groups one at a time using getNextGroup()
/// \endcode
class hkUnionFind
{
	public:

		typedef hkFixedArray<int>	IntArray;

	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, hkUnionFind);

			/// Constructor which takes a pointer to a working buffer
		hkUnionFind( IntArray& parents, int numElements );

			/// Destructor.
		~hkUnionFind(){}

			/// Start adding edges
		HK_FORCE_INLINE void beginAddEdges();
			/// add an edge
		void addEdge( int i1, int i2 );
			/// Stop adding edges
		HK_FORCE_INLINE void endAddEdges();

			/// Replace each parent by the group number. Also returns the number of elements in each group.
			/// Can only be called once.
			/// The return value indicates if the necessary memory was allocated successfully
		hkResult assignGroups( hkArray<int>& elementsPerGroup );

		HK_FORCE_INLINE hkBool isOneGroup() { return m_parents[0] == -m_numNodes; }

			/// Produces an array of the elements of each group in order. If there are n0 members in group 0, and n1 in group 1 etc, then
			/// first n0 elements will be the members of group 0 the next n1 will be elements of group2 and so forth.
			/// This method must be called after 'assignGroups'.
			/// The return value indicates if the necessary memory was allocated successfully
        hkResult sortByGroupId(const hkArray<int>& elementsPerGroup,hkArray<int>& orderedGroups) const;

			/// Reindex the parents end elementsPerGroup. Can only be called after assignGroups()
		void reindex( const hkFixedArray<int>& reindex, int numNewGroups, hkArray<int>& elementsPerGroup );

			/// Reindex, so that the biggest group is now on index 0. Returns the old index of the biggest group
		int moveBiggestGroupToIndexZero( hkArray<int>& elementsPerGroup );

			// Find the root node of node i
		int findRootOfNode(int i);

			// Merge two sets
		void unionRoots(int r1, int r2);

			// Adds all edges from another hkUnionFind. Both hkUnionFinds must be of the same size.
		void merge(const hkUnionFind& uf);

			// Flattens the tree so that all nodes are either leaves of roots
			// Returns the number of roots.
		int collapseTree();

	private:

		HK_FORCE_INLINE int _findRootOfNode(int i);
		HK_FORCE_INLINE void _unionRoots(int r1, int r2);

	public:
			// i'th element contains parent of node i
		IntArray&	m_parents;
		int m_numNodes;
		hkBool32 m_isCollapsed;	// true if the tree is collapsed
		int m_numRoots;			// The number of roots, only valid for collapsed trees.
		hkBool32 m_isAddingEdgesDebug;	// Debug helper to assert on incorrect beginAddEdges/endAddEdges usage.
};


HK_FORCE_INLINE void hkUnionFind::beginAddEdges()
{
	m_isCollapsed = 0;
	HK_ON_DEBUG( m_isAddingEdgesDebug = true; )
}

HK_FORCE_INLINE void hkUnionFind::endAddEdges()
{
	HK_ON_DEBUG( m_isAddingEdgesDebug = false; )
}

#endif //HAVOK_UNIONFIND_H

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
