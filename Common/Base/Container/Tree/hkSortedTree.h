/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_BASE_SORTED_TREE_H
#define HK_BASE_SORTED_TREE_H

/// Sorted tree base, declare default comparator.
struct	hkSortedTreeBase
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_TREE, hkSortedTreeBase);

	// Default comparators.
	
	/// Values.
	struct CompareValues
	{
		template <typename T>
		static HK_FORCE_INLINE int	compare(const T& a, const T& b) { return a < b ? -1 : (b < a ? 1 : 0); }
	};

	/// Pointers.
	struct ComparePointers
	{
		template <typename T>
		static HK_FORCE_INLINE int	compare(const T& a, const T& b) { return (*a) < (*b) ? -1 : ((*b) < (*a) ? 1 : 0); }
	};

	/// PRNG.	
	struct Prng
	{
		// KISS Based PRNG (http://www.cs.ucl.ac.uk/staff/d.jones/GoodPracticeRNG.pdf)
		HK_FORCE_INLINE				Prng() { reset(); }
		HK_FORCE_INLINE void		reset()	{ m_x=123456789; m_y=234567891; m_z=345678912; m_w=456789123; m_c=0; }
		HK_FORCE_INLINE hkUint32	nextUint32();
		HK_FORCE_INLINE hkInt32		nextInt32() { return hkInt32(nextUint32() >> 1); }
		
		hkUint32	m_x, m_y, m_z, m_w, m_c;
	};
};

/// Sorted tree template.
template <typename T, typename COMP = hkSortedTreeBase::CompareValues, typename INDEX = int, int GROWTH = 16>
struct	hkSortedTree : hkSortedTreeBase
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_TREE, hkSortedTree);

	/// Tree node.
	struct Node
	{
		T		m_value;		///< Node value.
		INDEX	m_children[2];	///< Node children.
		INDEX	m_parent;		///< Node parent.
	};	

	/// Constructor.
								hkSortedTree(int numNodes = 0) { clear(numNodes); }

	/// Reset the tree.
	inline void					clear(int numNodes = 0);
	
	/// Returns the number of used nodes.
	HK_FORCE_INLINE int			getSize() const { return m_size; }

	/// Pre-allocate 'count' nodes.
	inline void					preAllocateNodes(int count);
	
	/// Insert a new node.
	inline INDEX				insert(const T& value);

	/// Update an existing node.
	inline void					update(INDEX nodeIndex);

	/// Update an existing node.
	inline void					update(INDEX nodeIndex, const T& newValue);
	
	/// Remove an existing node.
	inline void					remove(INDEX nodeIndex);
	
	/// Optimize the tree by re-inserting 'count' nodes 'iterations' times.
	/// Note: If count is zero, all the nodes will be optimized.
	inline void					optimize(int count = 0, int iterations = 1);
	
	/// Find a value.
	inline INDEX				find(const T& value) const;

	/// Find a value.
	inline INDEX				find(const T& value, INDEX& closest, int& iterations) const;
	
	/// Get tree root
	HK_FORCE_INLINE INDEX		getRoot() const { return m_root; }
	
	/// Get node from index.
	HK_FORCE_INLINE	const Node&	getNode(INDEX index) const { return m_nodes[index]; }
	
	/// Get node value from index.
	HK_FORCE_INLINE	const T&	getValue(INDEX index) const { return getNode(index).m_value; }

	/// Get node value from index.
	HK_FORCE_INLINE	T&			getValue(INDEX index) { return m_nodes[index].m_value; }

	/// Get the node with the minimum value.
	inline INDEX				getMin() const;
	
	/// Get the node with the maximum value.
	inline INDEX				getMax() const;
	
	/// Get the first node.
	inline INDEX				getFirst() const;
	
	/// Get the next node.
	inline INDEX				getNext(INDEX nodeIndex) const;

	/// Traverse all node from min to max.
	template <typename FUNCTOR>
	inline void					traverseMinMax(FUNCTOR& functor, INDEX root = 0) const;

	/// Traverse all node from max to min.
	template <typename FUNCTOR>
	inline void					traverseMaxMin(FUNCTOR& functor, INDEX root = 0) const;

	//
	// Internals.
	//
	
	//
	inline void					insertNode(INDEX nodeIndex);
	
	//
	inline void					removeNode(INDEX nodeIndex);

	//
	inline bool					checkIntegrity() const;
	
	hkArray<Node>	m_nodes;	///< Nodes storage.
	int				m_size;		///< Number of used nodes.
	INDEX			m_root;		///< Tree root node.
	INDEX			m_free;		///< First free node.
	Prng			m_prng;		///< PRNG.
};

#include <Common/Base/Container/Tree/hkSortedTree.inl>

#endif //HK_BASE_SORTED_TREE_H

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
