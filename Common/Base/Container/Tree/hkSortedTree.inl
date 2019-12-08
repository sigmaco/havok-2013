/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

//
HK_FORCE_INLINE hkUint32	hkSortedTreeBase::Prng::nextUint32()
{
	m_y ^= (m_y<<5);
	m_y ^= (m_y>>7);
	m_y ^= (m_y<<22);
	const hkInt32 t = (hkInt32) (m_z + m_w + m_c);
	m_z =	m_w;
	m_c =	t < 0 ? 1 : 0;
	m_w =	(hkUint32) (t & 2147483647);
	m_x +=	1411392427;

	return m_x + m_y + m_w;
}

//
template <typename T, typename COMP, typename INDEX, int GROWTH>
inline void					hkSortedTree<T,COMP,INDEX,GROWTH>::clear(int numNodes)
{
	m_root = 0;
	m_free = 0;
	m_size = 0;
	m_prng.reset();
	m_nodes.clearAndDeallocate();
	m_nodes.expandOne();
	preAllocateNodes(numNodes);
}

//
template <typename T, typename COMP, typename INDEX, int GROWTH>
inline void	hkSortedTree<T,COMP,INDEX,GROWTH>::preAllocateNodes(int count)
{
	if(count)
	{
		const int	first = m_nodes.getSize();
		const int	last = first + count-1;
		m_nodes.expandBy(count);
		for(int i=first; i< last; ++i)
		{
			m_nodes[i].m_parent			=	i+1;
			m_nodes[i].m_children[0]	=	(INDEX)i;
		}
		m_nodes[last].m_parent		= m_free;
		m_nodes[last].m_children[0]	= (INDEX)last;
		m_free = first;	
	}		
}
	
//
template <typename T, typename COMP, typename INDEX, int GROWTH>
inline INDEX	hkSortedTree<T,COMP,INDEX,GROWTH>::insert(const T& value)
{
	if(!m_free) preAllocateNodes(GROWTH);

	INDEX	nodeIndex = m_free; m_free = m_nodes[m_free].m_parent;
		
	m_nodes[nodeIndex].m_value = value;

	insertNode(nodeIndex);

	++m_size;

	return nodeIndex;
}

//
template <typename T, typename COMP, typename INDEX, int GROWTH>
inline void		hkSortedTree<T,COMP,INDEX,GROWTH>::update(INDEX nodeIndex)
{
	HK_ASSERT2(0xA0AFB4C5, nodeIndex > 0, "Invalid index");

	removeNode(nodeIndex);
	insertNode(nodeIndex);
}

//
template <typename T, typename COMP, typename INDEX, int GROWTH>
inline void		hkSortedTree<T,COMP,INDEX,GROWTH>::update(INDEX nodeIndex, const T& newValue)
{
	HK_ASSERT2(0xA0AFB4C5, nodeIndex > 0, "Invalid index");

	removeNode(nodeIndex);
	m_nodes[nodeIndex].m_value = newValue;
	insertNode(nodeIndex);
}
	
//
template <typename T, typename COMP, typename INDEX, int GROWTH>
inline void		hkSortedTree<T,COMP,INDEX,GROWTH>::remove(INDEX nodeIndex)
{
	HK_ASSERT2(0xA0AFB4C5, nodeIndex > 0, "Invalid index");

	removeNode(nodeIndex);
		
	m_nodes[nodeIndex].m_parent	=	m_free;
	m_free						=	nodeIndex;
	--m_size;
}

//
template <typename T, typename COMP, typename INDEX, int GROWTH>
inline void		hkSortedTree<T,COMP,INDEX,GROWTH>::optimize(int count, int iterations)
{
	if(count <= 0) count = getSize();

	hkArray<INDEX>	nodes; nodes.reserve(count);
	for(int iteration = 0; iteration < iterations; ++iteration)
	{
		for(int i=0; i<count && m_root; ++i)
		{
			const hkUint32	path = m_prng.nextUint32();
			INDEX			nodeIndex = m_root;
			for(hkUint32 j=0; ;++j)
			{
				const int	side = (path >> (j&31)) & 1;
				const INDEX	next = m_nodes[nodeIndex].m_children[side];
				if(next)
					nodeIndex = next;
				else
					break;
			}
			nodes.pushBackUnchecked(nodeIndex);
			removeNode(nodeIndex);
		}

		while(nodes.getSize())
		{
			const int j = m_prng.nextInt32() % nodes.getSize();
			insertNode(nodes[j]);
			nodes.removeAt(j);
		}
	}
}

//
template <typename T, typename COMP, typename INDEX, int GROWTH>
inline INDEX	hkSortedTree<T,COMP,INDEX,GROWTH>::find(const T& value) const
{
	INDEX	nodeIndex = m_root;
	while(nodeIndex)
	{
		const Node&	node = m_nodes[nodeIndex];
		const int	comp = COMP::compare(value, node.m_value);
			
		if(comp == 0)		break;
		else if(comp < 0)	nodeIndex = node.m_children[0];
		else				nodeIndex = node.m_children[1];

	}
	return nodeIndex;
}

//
template <typename T, typename COMP, typename INDEX, int GROWTH>
inline INDEX	hkSortedTree<T,COMP,INDEX,GROWTH>::find(const T& value, INDEX& closest, int& iterations) const
{
	INDEX	nodeIndex = m_root;
	closest		=	nodeIndex;
	iterations	=	0;
	while(nodeIndex)
	{
		++iterations;

		const Node&	node = m_nodes[nodeIndex];
		const int	comp = COMP::compare(value, node.m_value);
			
		if(comp == 0)		break;
		else if(comp < 0)	closest = nodeIndex , nodeIndex = node.m_children[0];
		else				closest = nodeIndex , nodeIndex = node.m_children[1];

	}
	return nodeIndex;
}

//
template <typename T, typename COMP, typename INDEX, int GROWTH>
inline INDEX	hkSortedTree<T,COMP,INDEX,GROWTH>::getMin() const
{
	INDEX	nodeIndex = m_root;
	while(nodeIndex && m_nodes[nodeIndex].m_children[0]) nodeIndex = m_nodes[nodeIndex].m_children[0];
	return nodeIndex;
}

//
template <typename T, typename COMP, typename INDEX, int GROWTH>
inline INDEX	hkSortedTree<T,COMP,INDEX,GROWTH>::getMax() const
{
	INDEX	nodeIndex = m_root;
	while(nodeIndex && m_nodes[nodeIndex].m_children[1]) nodeIndex = m_nodes[nodeIndex].m_children[1];
	return nodeIndex;
}

//
template <typename T, typename COMP, typename INDEX, int GROWTH>
inline INDEX		hkSortedTree<T,COMP,INDEX,GROWTH>::getFirst() const
{
	for(int i=1; i<m_nodes.getSize(); ++i) if(m_nodes[i].m_children[0] != (INDEX)i) return (INDEX)i;
	return 0;
}

//
template <typename T, typename COMP, typename INDEX, int GROWTH>
inline INDEX		hkSortedTree<T,COMP,INDEX,GROWTH>::getNext(INDEX nodeIndex) const
{
	if(nodeIndex)
	{
		for(int i=nodeIndex+1; i<m_nodes.getSize(); ++i) if(m_nodes[i].m_children[0] != (INDEX)i) return (INDEX)i;
	}
	return 0;	
}

//
template <typename T, typename COMP, typename INDEX, int GROWTH>
template <typename FUNCTOR>
inline void			hkSortedTree<T,COMP,INDEX,GROWTH>::traverseMinMax(FUNCTOR& functor, INDEX root) const
{
	if(!root) root = m_root;
	if(root)
	{
		const Node& node = m_nodes[root];
		if(node.m_children[0]) traverseMinMax(functor, node.m_children[0]);
		functor(root, node.m_value);
		if(node.m_children[1]) traverseMinMax(functor, node.m_children[1]);
	}
}

//
template <typename T, typename COMP, typename INDEX, int GROWTH>
template <typename FUNCTOR>
inline void			hkSortedTree<T,COMP,INDEX,GROWTH>::traverseMaxMin(FUNCTOR& functor, INDEX root) const
{
	if(!root) root = m_root;
	if(root)
	{
		const Node& node = m_nodes[root];
		if(node.m_children[1]) traverseMaxMin(functor, node.m_children[1]);
		functor(root, node.m_value);
		if(node.m_children[0]) traverseMaxMin(functor, node.m_children[0]);
	}
}
	
//
template <typename T, typename COMP, typename INDEX, int GROWTH>
inline void	hkSortedTree<T,COMP,INDEX,GROWTH>::insertNode(INDEX nodeIndex)
{
	Node&	node = m_nodes[nodeIndex];
	if(m_root)
	{
		INDEX	parentIndex = m_root;
		for(;;)
		{
			Node&		parent = m_nodes[parentIndex];
			const int	side = COMP::compare(node.m_value, parent.m_value) < 0 ? 0 : 1;
				
			if(parent.m_children[side])
			{
				parentIndex = parent.m_children[side];
			}
			else
			{
				parent.m_children[side]	=	nodeIndex;
				node.m_parent			=	parentIndex;
				break;
			}
		}
	}
	else
	{
		m_root			=	nodeIndex;
		node.m_parent	=	0;
	}
	node.m_children[0] =
	node.m_children[1] = 0;
}

//
template <typename T, typename COMP, typename INDEX, int GROWTH>
inline void	hkSortedTree<T,COMP,INDEX,GROWTH>::removeNode(INDEX nodeIndex)
{
	Node&	node = m_nodes[nodeIndex];
	INDEX	parentIndex = node.m_parent;
	INDEX&	parentRef = parentIndex ? (m_nodes[parentIndex].m_children[0] == nodeIndex ? m_nodes[parentIndex].m_children[0] : m_nodes[parentIndex].m_children[1]) : m_root;
		
	if(node.m_children[0])
	{
		if(node.m_children[1])
		{
			const int	side = m_prng.nextInt32() & 1;
			const int	opp = 1 - side;
				
			INDEX		sideIndex = node.m_children[side];
			while(m_nodes[sideIndex].m_children[opp]) sideIndex = m_nodes[sideIndex].m_children[opp];
				
			m_nodes[sideIndex].m_children[opp]		=	node.m_children[opp];
			m_nodes[node.m_children[opp]].m_parent	=	sideIndex;

			parentRef					=	node.m_children[side];
			m_nodes[parentRef].m_parent	=	parentIndex;
		}
		else
		{
			parentRef					=	node.m_children[0];
			m_nodes[parentRef].m_parent	=	parentIndex;
		}
	}
	else
	{
		if(node.m_children[1])
		{
			parentRef					=	node.m_children[1];
			m_nodes[parentRef].m_parent	=	parentIndex;
		}
		else
		{
			parentRef	=	0;
		}
	}

	node.m_parent		= 0;
	node.m_children[0]	= nodeIndex;
}

//
template <typename T, typename COMP, typename INDEX, int GROWTH>
inline bool			hkSortedTree<T,COMP,INDEX,GROWTH>::checkIntegrity() const
{
	INDEX		minValue = getFirst();
	INDEX		maxValue = getFirst();
	const char*	error = HK_NULL;

	#define THROW_ERROR(_msg_) { error = _msg_; goto catchError; }

	for(INDEX i=getFirst(); i && !error; i=getNext(i))
	{
		const Node&	node = m_nodes[i];
		
		if(COMP::compare(node.m_value,m_nodes[minValue].m_value) < 0) minValue = i;
		if(COMP::compare(node.m_value,m_nodes[maxValue].m_value) > 0) maxValue = i;

		if(COMP::compare(m_nodes[find(node.m_value)].m_value , node.m_value) != 0)
			THROW_ERROR("Failed to lookup by value.");
		
		if(node.m_children[0])
		{
			const Node&	c0 = m_nodes[node.m_children[0]];
			if(c0.m_parent != i)
				THROW_ERROR("Invalid link with left child.");
			if(COMP::compare(node.m_value, c0.m_value) < 0)
				THROW_ERROR("Invalid left value wrt. parent.");
		}
		if(node.m_children[1])
		{
			const Node&	c1 = m_nodes[node.m_children[1]];
			if(c1.m_parent != i)
				THROW_ERROR("Invalid link with right child.");
			if(COMP::compare(node.m_value, c1.m_value) > 0)	
				THROW_ERROR("Invalid right child value wrt. parent.");
		}
	}

	if(minValue && maxValue)
	{
		if(COMP::compare(getValue(minValue) , getValue(getMin())) != 0)
			THROW_ERROR("Invalid min-bound.");
		if(COMP::compare(getValue(maxValue) , getValue(getMax())) != 0)
			THROW_ERROR("Invalid max-bound.");
	}

	return true;

	#undef THROW_ERROR
	catchError: {}

	HK_ASSERT3(0x4BD186F2, error == HK_NULL, "Integrity error: "<<error);

	return false;
}

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
