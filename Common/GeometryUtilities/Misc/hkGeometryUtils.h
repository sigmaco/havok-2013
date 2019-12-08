/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_GEOMETRY_UTILS_H
#define HK_GEOMETRY_UTILS_H

#include <Common/Base/Algorithm/Sort/hkSort.h>
#include <Common/Base/Types/Geometry/hkGeometry.h>
#include <Common/Base/Algorithm/Collide/1AxisSweep/hk1AxisSweep.h>


	/// Utility class, contains methods that operate with hkGeometry objects.
class hkGeometryUtils
{
	public:
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE,hkGeometryUtils);

	/// Virtual interface to access vertices.
	struct IVertices
	{
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE, IVertices );

		virtual			~IVertices() {}
		virtual int		getNumVertices() const=0;
		virtual void	getVertex(int index, hkVector4& vertexOut) const=0;
		virtual bool	isWeldingAllowed(int vertexA, int vertexB) const { return true; }
	};

			/// Finds identical vertices and generate the map from original indices to welded ones.
			/// Note this method virtualize access to vertices.
			/// Returns the number of unique vertices found.
		static int HK_CALL weldVerticesVirtual (const IVertices* vertices, hkArray<int>& remap, hkReal threshold = hkReal(1e-3f));

			/// Given an hkGeometry, it finds identical vertices and collapses them, updating triangles as well.
			/// Degenerate triangles are automatically removed
		static void HK_CALL weldVertices (struct hkGeometry& meshGeometry, hkReal threshold = hkReal(1e-3f));

			/// Given an hkGeometry, it finds identical vertices and collapses them, updating triangles as well.
			/// This version returns a map from the original vertex indices to the new vertex indices.
			/// Degenerate triangles are automatically removed and the triangleRemapOut array contains -1 for each degenerate.
			/// If "keep vertex order" is set to true, the original vertex ordering will be maintained as much as possible
		static void HK_CALL weldVertices (struct hkGeometry& meshGeometry, hkReal threshold, hkBool keepVertexOrder, hkArray<int>& vertexRemapOut, hkArray<int>& triangleRemapOut);

			/// Given an hkGeometry, it finds identical vertices and collapses them, updating triangles as well.
			/// All arrays used by the internal sorting are explicitly provided.
		static void HK_CALL _weldVertices (struct hkGeometry& meshGeometry, hkReal threshold, hkBool keepVertexOrder, hkArray<int>& vertexRemapOut, hkArray<int>& triangleRemapOut, hkArray<hkVector4>& uniqueVerts, hkArrayBase<hk1AxisSweep::AabbInt>& sweepAabbs, hkArrayBase<hkRadixSort::SortData32>& sortData, hkArrayBase<hk1AxisSweep::AabbInt>& sortedAabbs );

			/// Given an hkGeometry, it finds triangles that use the same three vertices. It removes these extra triangles,
			/// and returns a map from the original triangles to the new triangles.
			/// If ignoreWinding is true (the default), triangles with the same indices but different winding are considered duplicates (and will be removed).
			/// If ignoreWinding is false, triangles with the same indices but different winding are NOT considered duplicates (i.e., only duplicates with identical triangle indices will be removed).
		static void HK_CALL removeDuplicateTriangles (struct hkGeometry& meshGeometry, hkArray<int>& triangleMapOut, bool ignoreWinding=true);

			/// Given an hkGeometry, it finds and removes triangles that use the same three vertices with the same winding order.
			/// This is much faster than removeDuplicateTriangles for large geometries, but doesn't compute the map.
			/// Returns HK_FAILURE if any memory allocations failed
		static hkResult HK_CALL removeDuplicateTrianglesFast(struct hkGeometry& meshGeometry, hkArray<hkGeometry::Triangle>& newTriangles );

		static void HK_CALL quantize( hkGeometry& geomInOut, int resolution = (1 <<16) );

			/// Creates an hkGeometry that has the shape of a capsule.
		static void HK_CALL createCapsuleGeometry(const hkVector4& top, const hkVector4& bottom, hkReal radius, int numHeightSegments, int numSides, const hkTransform& transform, hkGeometry& geometryOut);

			/// Creates an hkGeometry that has the shape of a tapered capsule.
		static void HK_CALL createTaperedCapsuleGeometry(const hkVector4& start, const hkVector4& end, hkReal startRadius, hkReal endRadius, int heightSamples, int thetaSamples, const hkTransform& transform, hkGeometry& geometryOut);

			/// Creates an hkGeometry that has the shape of a cylinder.
		static void HK_CALL createCylinderGeometry(const hkVector4& top, const hkVector4& bottom, hkReal radius, int numSides, int numHeightSegments, hkGeometry& geometryOut);

			/// Creates an hkGeometry that has the shape of a plane.
		static void HK_CALL createPlaneGeometry(const hkVector4& normal, const hkVector4& perpToNormal, const hkVector4& center, const hkVector4& extents, hkGeometry& geometryOut);

			/// Transform a geometry
		static void HK_CALL transformGeometry (const hkMatrix4& transform, hkGeometry& geometryInOut);

			/// Append one geometry to another.
		static void HK_CALL appendGeometry( const hkGeometry& input, hkGeometry& geomInOut );

			/// Controls the behavior of getGeometryInsideAabb.
		enum GetGeometryInsideAabbMode
		{
				/// No data is copied to the output hkGeometry, but its arrays will be set to the minimal size
			MODE_PRESIZE_ARRAYS,

				/// Copy the triangles and vertices in the specified AABB (default behavior)
			MODE_COPY_DATA,
		};

			/// Extract the triangles from the input geometry that are within the specified AABB.
			/// The AABB of each triangle is tested against the specified AABB, so some
			/// triangles that are outside of the AABB may be included.
		static hkResult HK_CALL getGeometryInsideAabb( const hkGeometry& geomIn, hkGeometry& geomOut, const hkAabb& aabb, GetGeometryInsideAabbMode mode = MODE_COPY_DATA);

			/// Computes the volume of the given geometry
		static void HK_CALL computeVolume (const struct hkGeometry& geometry, hkSimdReal& volume);

			/// Computes the AABB of the given geometry
		static void HK_CALL computeAabb(const hkGeometry& geomIn, hkAabb& aabbOut);

			/// Data structure to allow linear time operations on triangle meshes
		struct Node
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE,hkGeometryUtils::Node);
			Node( hkUint32 vertexIndex );
			Node(const Node& other);
			Node& operator= (const Node& other);
			
			struct Triangle
			{
				Triangle(hkUint32 a, hkUint32 b, hkUint32 c);

				hkUint32 m_indices[3];
				hkUint32 m_sortedIndices[3];

				template<typename T>
				inline void _sort3(T& a, T& b, T& c);
			};

			struct Edge
			{
				HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE,hkGeometryUtils::Node::Edge);
				Edge(hkUint32 endpointIndex, const Node::Triangle& triangle, hkUint32 triangleIndex);
				Edge& operator= (const Edge& other);
				Edge(const Edge& other);

				// Return true if this edge has a parent triangle with exactly the same indices
				bool hasTriangleSameWinding(const Node::Triangle& triangle, int& triIndex);

				// Return true if this edge has a parent triangle with the same indices (in any permutation) as the given one
				bool hasTriangleIgnoreWinding(const Node::Triangle& triangle, int& triIndex);

				hkUint32 m_endpointIndex;

				// Parent triangles of edge
				hkArray<Node::Triangle> m_triangles;
				hkArray<hkUint32> m_triangleIndices;

				int m_numIncoming;
				int m_numOutgoing;

				bool m_nonManifold;
				bool m_inconsistentWinding;
				bool m_processed;
			};

			hkUint32 m_vertexIndex;
			hkArray<Edge> m_edges;

			void addEdge(hkUint32 endpointIndex, const Node::Triangle& triangle, hkUint32 triangleIndex, bool incoming=false);
			Edge* findEdge(hkUint32 endpointIndex);
			
			bool checkForNonManifoldGeometry() const;
			void warnAboutInconsistentWinding(int e) const;
		};

};

#endif //HK_GEOMETRY_UTILS_H

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
