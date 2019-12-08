/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#ifndef HK_GEOMETRY_PROCESSING_OCTREE_H
#define HK_GEOMETRY_PROCESSING_OCTREE_H

#include <Common/Base/Config/hkProductFeatures.h>

/// Octree data-structure and related utilities.
struct hkgpOctree
{	
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_GEOMETRY, hkgpOctree);

	/// Node
	struct Node
	{
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_GEOMETRY, Node);

		HK_FORCE_INLINE			Node() { m_children[0] = -1; }
		HK_FORCE_INLINE hkBool	hasChildren() const { return m_children[0] != -1; }
		HK_FORCE_INLINE hkBool	isLeaf() const { return m_children[0] == -1; }
		HK_FORCE_INLINE int		operator[](int index) const { HK_ASSERT2(0x24C87FF9, hasChildren() && index >= 0 && index <= 7, "Invalid index"); return m_children[index]; }
		HK_FORCE_INLINE int&	operator[](int index) { HK_ASSERT2(0x24C87FFA, index >= 0 && index <= 7, "Invalid index"); return m_children[index]; }
		
		int	m_children[8];	///< Children node indices.
	};

	/// Structure holding dual information during enumeration.
	struct Dual
	{
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_GEOMETRY, Dual);

		/// Type of feature.
		enum Type { INVALID = 0, VERTEX = 1, EDGE = 2, FACE = 4, VOLUME = 8 };

		/// Feature axis.
		enum Axis { NONE = -1, AXE_X = 0, AXE_Y = 1, AXE_Z = 2 };

		HK_FORCE_INLINE			Dual() : m_type(INVALID), m_axis(NONE) {}
		HK_FORCE_INLINE			Dual(int a) : m_type(VERTEX), m_axis(NONE) { m_nodes[0] = a; }
		HK_FORCE_INLINE			Dual(Axis axis, int a,int b) : m_type(EDGE), m_axis(axis) { m_nodes[0] = a; m_nodes[1] = b; }
		HK_FORCE_INLINE			Dual(Axis axis, int a,int b,int c,int d) : m_type(FACE), m_axis(axis) { m_nodes[0] = a; m_nodes[1] = b; m_nodes[2] = c; m_nodes[3] = d; }
		HK_FORCE_INLINE			Dual(int a,int b,int c,int d,int e,int f,int g,int h) : m_type(VOLUME), m_axis(NONE) { m_nodes[0] = a; m_nodes[1] = b; m_nodes[2] = c; m_nodes[3] = d; m_nodes[4] = e; m_nodes[5] = f; m_nodes[6] = g; m_nodes[7] = h; }
		HK_FORCE_INLINE int		operator[](int index) const { HK_ASSERT2(0x297A8AE0, index < m_type, "Invalid index"); return m_nodes[index]; }
		HK_FORCE_INLINE int&	operator[](int index) { HK_ASSERT2(0x297A8AE0, index < m_type, "Invalid index"); return m_nodes[index]; }
			
		Type	m_type:16;	///< Type of feature.
		Axis	m_axis:16;	///< Feature axis.
		int		m_nodes[8];	///< Node indices.
	};

	/// Wrapper that provides support for virtual boundaries.
	template <typename OCTREE>
	struct PrimalOctree
	{		
		HK_FORCE_INLINE			PrimalOctree(OCTREE& octree) : m_octree(octree) {}

		HK_FORCE_INLINE int		getRoot() const { return m_octree.getRoot(); }
		HK_FORCE_INLINE int		getChild(int node, int index) const { return m_octree.getChild(node,index); }
		HK_FORCE_INLINE bool	hasChildren(int node) const { return m_octree.hasChildren(node); }
		HK_FORCE_INLINE bool	isValid(int node) const { return m_octree.isValid(node); }
		HK_FORCE_INLINE bool	processVolume(const int nodes[8]) const { return m_octree.processVolume(nodes); }
		HK_FORCE_INLINE void	processTetrahedron(const int nodes[4]) const { m_octree.processTetrahedron(nodes); }

		OCTREE&	m_octree;
	};

	// Utilities.

	/// Enumerate all valid volumes and tetrahedra of an octree dual.
	/// OCTREE must implement the following methods:
	/// - int getRoot() const , return the root of the octree.
	/// - int getChild(int node,int index) const, returns the child node at a given index (0-7).
	/// - bool hasChildren(int node) const, returns true if the node has children.
	/// - bool isValid(int node) const, returns true if the node is valid.
	/// - void processVolume(const int nodes[8]) const, called to process a volume.
	/// - void processTetrahedron(const int nodes[4]) const, called to process a tetrahedron (only called if processVolume() returns true).
	/// Note: a valid node index must be greater or equal to zero.
	template <typename OCTREE>
	static inline void	enumerateDual(OCTREE& octree);
	
	// Lookup tables.
	
	static const int	lut_tetras[6][4];
	static const int	lut_edges[12][2];
	static const int	lut_faces[6][4];
	static const int	lut_edge_volumes[3][8][2];
	static const int	lut_face_volumes[3][8][2];
};

#include <Common/Internal/GeometryProcessing/Octree/hkgpOctree.inl>

#endif // HK_GEOMETRY_PROCESSING_OCTREE_H

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
