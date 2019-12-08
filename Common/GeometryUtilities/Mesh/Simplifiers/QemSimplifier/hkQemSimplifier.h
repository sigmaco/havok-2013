/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_QEM_SIMPLIFIER_H
#define HK_QEM_SIMPLIFIER_H

#include <Common/Internal/GeometryProcessing/Topology/hkgpVertexTriangleTopology.h>
#include <Common/Base/Algorithm/Sort/hkSort.h>
#include <Common/Base/Container/MinHeap/hkMinHeap.h>
#include <Common/Base/Types/Geometry/Aabb/hkAabb.h>
#include <Common/GeometryUtilities/Mesh/hkMeshVertexBuffer.h>
#include <Common/GeometryUtilities/Mesh/Utils/VertexSharingUtil/hkVertexSharingUtil.h>

class hkQuadricMetric;

class hkVertexSharingUtil;

/// Implementation of a Quadric Error Metric (QEM) style triangular mesh simplifier.
/// Can handle both open and closed triangular meshes. The QEM simplification method works
/// by calculating the amount of error an edge contraction will produce. Contractions are generally 
/// applied from the contraction of lowest error to that of the largest.
///
/// In usage the first stage is to inform the simplifier of the geometry that needs simplification.
/// This is performed using 'startMesh', and 'endMesh' to surround the actual construction of the mesh. 
/// Generally speaking vertices of a graphics mesh can have a variety of 'attributes' - such as texture 
/// coordinates, colors, normals and so forth. 
///
/// The simplifier defines a triangle to consist of positions indices, as well as attribute indices. The 
/// data is represented this way because a vertex may have more that one attribute associated with it,
/// depending on what triangles it is associated with. Consider the example of two triangles with different
/// materials sharing a vertex. One material requires a color the other does not. The position vertex index
/// will be shared, but the attribute index will not.
///
/// To control simplification the simplifier has a method 'getTopContraction' which specifies the current contraction
/// which is the one that will introduce the minimum QEM error. The top contraction can be applied or discarded. 
/// A QEM contraction can invert the direction of neighboring faces. Such a contraction can introduce undesirable 
/// artifacts in models - so there is a method which tests for this case 'doesTopContractionFlipTriangle'. If such 
/// a contraction is a problem it can be discarded.
///
/// Sometimes it is desirable to make some triangles never get removed during simplification. One way of looking 
/// at this problem would be to never contract an edge that belonged to the triangle. Unfortunately this is complicated
/// by when a contraction is applied it may introduce a new vertex, or use a previously existing vertex, making it
/// hard to identify an edge from the original triangle. One way around such problems is before any simplification 
/// occurs: find all of the edge contractions that are on triangles that we want to maintain, and remove them before
/// any simplification takes place. This can be achieved using the 'getContraction' method to get all of the contractions,
/// and 'discardContraction' to discard any of the unwanted contractions. 
/// 
/// Open geometry introduces extra issues in simplification. With a closed mesh contracting an edge generally 
/// produces small visual errors, if the QEM error is small. But with an open edge, a small QEM error can produce
/// a large graphical change, because the effect of the open edge is ignored. To work around this problem,
/// extra QEM planes can be added to the open edge, to make the open edge of visual importance, and thus less 
/// likely for reduction. This is performed by adding a 'plane' perpendicular to the open edge, scaling it by the 
/// edges length, and scaling again by another factor which controls the importance of open edges. 
/// Geometry that can be open requires extra processing, and so to enable usage, the feature must be enabled on the
/// simplifier by using the 'setEnableOpenGeometry' method. To control the strength of the weighting of open edges 
/// use the method 'setOpenEdgeScale'. Setting this value to 1, will make the strength controlled by the edge
/// length alone.
/// 
/// NOTE! The simplifier will report an error if open geometry is specified but 'setEnableOpenGeometry' has not 
/// been set to true.
class hkQemSimplifier: public hkReferencedObject
{
	public:
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SCENE_DATA);

		struct Triangle;
		struct EdgeContraction;

		typedef hkgpVertexTriangleTopology<Triangle>	TopologyType;
		typedef TopologyType::EdgeId					EdgeId;
		typedef TopologyType::Edge						Edge;
		typedef TopologyType::VertexIndex				VertexIndex;
		typedef hkVertexSharingUtil::Threshold			Threshold;
		
		struct EdgeMap
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE,hkQemSimplifier::EdgeMap);

				/// Add a triangle
			void addTriangle(const Triangle& tri);
				/// Get an edge id
			EdgeId getEdge(int start, int end) const { return m_edgeMap.getWithDefault((hkUint64(start) << 32) | end, TopologyType::INVALID_EDGE_ID); }
				/// Returns true if it has the edge
			hkBool32 hasEdge(int start, int end) const { return getEdge(start, end) != TopologyType::INVALID_EDGE_ID; }

			hkPointerMap<hkUint64, EdgeId> m_edgeMap;
		};

		class ContractionController: public hkReferencedObject
		{
		public:
			HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SCENE_DATA);

				/// Returns true if a contraction is allowed, between the position indices specified
			virtual hkBool32 allowContraction(const EdgeContraction& contraction) = 0;
		};

		class ScaleCalculator: public hkReferencedObject
		{
		public:
			HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SCENE_DATA);
				/// The index is the index of the triangle (0-2) that is being calculated for
			virtual hkSimdReal calcScale(hkQemSimplifier& simplifier, const Triangle& tri, int index) = 0;
		};

		class SizeScaleCalculator: public ScaleCalculator
		{
			public:
			HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SCENE_DATA);
			// ScaleCalculator
			virtual hkSimdReal calcScale(hkQemSimplifier& simplifier, const Triangle& tri, int index)
			{
				hkVector4 va; simplifier.getPosition01(tri.m_vertexIndices[0], va);
				hkVector4 vb; simplifier.getPosition01(tri.m_vertexIndices[1], vb);
				hkVector4 vc; simplifier.getPosition01(tri.m_vertexIndices[2], vc);

				hkVector4 e0; e0.setSub(vb, va);
				hkVector4 e1; e1.setSub(vc, va);
				hkVector4 cross; cross.setCross(e0, e1);
				return cross.length<3>();
			}
		};

		class AngleScaleCalculator: public ScaleCalculator
		{
			public:
			HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SCENE_DATA);
			// ScaleCalculator
			virtual hkSimdReal calcScale(hkQemSimplifier& simplifier, const Triangle& tri, int index)
			{
				const int nextIdx = (1 << index) & 3;
				const int prevIdx = (1 << nextIdx) & 3;

				const hkArray<hkVector4>& positions = simplifier.getPositions();

				const hkVector4& v0 = positions[tri.m_vertexIndices[prevIdx]];
				const hkVector4& v1 = positions[tri.m_vertexIndices[index]];
				const hkVector4& v2 = positions[tri.m_vertexIndices[nextIdx]];

				hkVector4 e0; e0.setSub(v2, v1);
				hkVector4 e1; e1.setSub(v0, v1);

				const hkSimdReal abSquared = e0.lengthSquared<3>() * e1.lengthSquared<3>();

				// 'Angle' is cos(theta) + 1, where theta is the inner angle between the edges leaving the point being accumulated to
				// the scale will be in the range 0-2
				const hkSimdReal angle = e0.dot<3>(e1) * abSquared.sqrtInverse() + hkSimdReal_1;
				return angle;
			}
		};

			/// Attribute types
		enum AttributeType
		{
			ATTRIB_TYPE_POSITION	= 1,
			ATTRIB_TYPE_NORMAL		= 2,	// Normal, binormal, or tangent
			ATTRIB_TYPE_UV			= 3,
			ATTRIB_TYPE_COLOR		= 4,
			ATTRIB_TYPE_BINORMAL	= 5,
			ATTRIB_TYPE_TANGENT		= 6,
			ATTRIB_TYPE_UNKNOWN		= 0,
		};

			/// Attribute entry
		struct AttributeEntry
		{
			HK_DECLARE_POD_TYPE();
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SCENE_DATA, AttributeEntry);

			hkUint8 m_type;		///< Attribute type, one of AttributeType values
			hkUint8 m_size;		///< Number of reals the attribute has
		};
	
			/// Attribute format
		struct AttributeFormat
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SCENE_DATA, AttributeFormat);
			hkArray<AttributeEntry> m_entries;

				/// Sets the format
			void set(const hkVertexFormat& vfmt);
		};

		// Attributes are stored, with first the attribute data, followed by the quadric error data.
		// Ie an attribute size is m_attributeVecSize + m_quadricVecSize
		struct Group
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE,hkQemSimplifier::Group);
			Group() {}
			Group(const Group& rhs)
			:	m_positionOffset(rhs.m_positionOffset)
			,	m_attributeSize(rhs.m_attributeSize)
			,	m_attributeVecSize(rhs.m_attributeVecSize)
			,	m_quadricSize(rhs.m_quadricSize)
			,	m_quadricVecSize(rhs.m_quadricVecSize)
			,	m_positionToAttribScale(rhs.m_positionToAttribScale)
			{
				m_availableAttributeIndices = rhs.m_availableAttributeIndices;
				m_attributes = rhs.m_attributes;
				m_attributeFreeList = rhs.m_attributeFreeList;
				m_fmt = rhs.m_fmt;
			}
				/// Returns the attribute data at the index
			hkVector4* getAttribute(int index) { return m_attributes[index]; }
				/// Get an attribute
			const hkVector4* getAttribute(int index) const { return m_attributes[index]; }

				/// Get the quadric data at the index
			hkVector4* getQuadric(int index) { return m_attributes[index] + m_attributeVecSize; }
				/// Get the attribute position
			hkReal* getAttributePosition(int index) { return ((hkReal*)m_attributes[index]) + m_positionOffset; }
				/// Get the attribute position
			const hkReal* getAttributePosition(int index) const { return ((hkReal*)m_attributes[index]) + m_positionOffset; }
				/// Set the attribute position
			void setAttributePosition(int index, hkVector4Parameter pos) { pos.store<3,HK_IO_NATIVE_ALIGNED>(((hkReal*)m_attributes[index]) + m_positionOffset); }
				/// Create an attribute, zero it and add to the end of the m_attributes list
			int createAttribute();
				/// Delete an attribute
			void deleteAttribute(int index);
				/// Get the position
			void getPosition(int index, hkVector4& pos) { pos.load<3,HK_IO_NATIVE_ALIGNED>(((hkReal*)getAttribute(index)) + m_positionOffset); }
				/// Get the num attributes
			int getNumAttributes() const { return m_attributes.getSize(); }

			int m_positionOffset;                               ///< The offset of the position held int the attributes (offset is in hkReals)

			// There is a quadric for each vertex/attribute
			int m_attributeSize;
			int m_attributeVecSize;								///< Size in vec4s

			int m_quadricSize;									///< Size of the quadric store size
			int m_quadricVecSize;								///< Size in vec4s

			hkSimdReal m_positionToAttribScale;					///< Multiply by a position in 0-1 space to get in weighted attribute space

			hkArray<int> m_availableAttributeIndices;			///< List of indices available
			hkArray<hkVector4*> m_attributes;					///< Attribute index to attribute data
			hkFreeList m_attributeFreeList;						///< Storage for attributes

			AttributeFormat m_fmt;								///< Attributes format.
		};
		struct EdgeContraction
		{
			enum Type
			{
				TYPE_INVALID,				///< Invalid
				TYPE_SELECT_START,			///< Shift to the start
				TYPE_SELECT_END,			///< Shift to the end
				TYPE_NEW,					///< Its a new vertex
				TYPE_USED,					///< Its been used, so if there is an attribute index, don't delete it
			};
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_DEMO, EdgeContraction);

			HK_FORCE_INLINE static hkBool32 lessThan(const EdgeContraction* a, const EdgeContraction* b)
			{
				return a->m_error.isLess(b->m_error);
			}
			HK_FORCE_INLINE static void setIndex(EdgeContraction* a, int index) { a->m_contractionIndex = index; }
			HK_FORCE_INLINE static void swap(EdgeContraction*& a, EdgeContraction*&b)
			{
				hkAlgorithm::swap(a->m_contractionIndex, b->m_contractionIndex);
				hkAlgorithm::swap(a, b);
			}
			HK_FORCE_INLINE static hkBool32 hasIndex(const EdgeContraction* a, int index) { return a->m_contractionIndex == index; }

			hkSimdReal m_error;									///< The amount of error in applying this contraction

			Type m_type;

			int m_start;										///< The start vertex index
			int m_end;											///< The end vertex index. The start is always

			int m_contractionIndex;								///< The current index in the hkMinHeap

			int m_groupIndex;									///< The group the new attribute belongs to (will be != -1 is TYPE_NEW)
			int m_attributeIndex;								///< The new attribute index (Will be != -1 if TYPE_NEW)
		};
		struct Triangle: public hkgpVertexTriangleTopologyBase::Triangle
		{
			// The extra data we need
			int m_attributeIndices[3];			///< The attribute indices
			int m_groupIndex;					///< The group this triangle belongs to
			hkReal m_weight;
		};

		struct Attribute
		{
			HK_FORCE_INLINE hkBool32 operator==(const Attribute& rhs) const { return m_attributeIndex == rhs.m_attributeIndex && m_groupIndex == rhs.m_groupIndex; }

			int m_attributeIndex;
			int m_groupIndex;
		};

			/// Start the mesh
		void startMesh(const hkAabb& aabb, const hkVector4* uniquePositions, int numPositions, bool unitScalePosition);
			/// Start a group. A group defines a set of triangles that share attributes.
		void startGroup(int attribSize, const AttributeFormat& fmt, hkSimdRealParameter positionToAttribScale);
			/// Add a triangle
		void addTriangle(const int positionIndices[], const int attributeIndices[], hkReal weight = 1);
			/// Add an attribute, returns the index for the attribute
		int addAttribute(hkVector4* attribute);
			/// Adds an attrib + returns its index
		hkVector4* addAttribute(int& attribIndex);
			/// Adds an attribute to the current group
		hkVector4* addAttribute();
			/// End a group
		void endGroup();
			/// End the mesh construction
		hkResult endMesh();
		
			/// Get all of the groups
		const hkArray<Group>& getGroups() const { return m_groups; }
			/// Get the num of triangles
		int getNumTriangles() const { return m_topology.getNumTriangles(); }
			/// Get a triangle
		const Triangle* getTriangle(int index) const { return m_topology.getTriangle(index); }

			/// Get the top contraction, returns HK_NULL if there aren't any remaining contractions
		EdgeContraction* getTopContraction() const;
			/// Returns true if applying the contraction will cause a triangle to flip
		bool doesTopContractionFlipTriangle();
			/// Apply the contraction
		void applyTopContraction();
			/// Discard the top contraction
		void discardTopContraction();

			/// Returns the cost of the top contraction
		hkSimdReal getTopContractionError() const;

			/// Get the number of remaining contractions
		int getNumContractions() const { return m_contractions.getSize(); }

			/// Apply contractions
		void applyContractions(int numContractions, bool allowFlip);
			/// Simplify by applying contractions until the percentage of triangles requested is removed.
		void simplify(hkSimdRealParameter percentageRemoveTris, bool allowFlip);

			/// Get the array of all contractions
		const hkArray<EdgeContraction*>& getContractions() const { return m_contractions.getContents(); }
			/// Discard an arbitrary contraction
		void discardContraction(EdgeContraction* conn);

			/// Removes all content
		void clear();

			/// Returns true if everything appears with internal structures
		hkBool32 isOk() const; 

            /// Remove all the unused attributes and vertices, and clear up memory.
        void finalize();

			/// Display
		void debugDisplay();
		
			/// Must be set for open edged geometry to be processed correctly
		void setEnableOpenGeometry(hkBool enable) { m_enableOpenEdgeGeometry = enable; }
			/// Get if open edge geometry will be processed
		hkBool getEnableOpenEdgeGeometry() const { return m_enableOpenEdgeGeometry; }

			/// Sets the discard invalid attribute moves flag
		HK_FORCE_INLINE void setDiscardInvalidAttributes(hkBool enable) { m_discardInvalidAttributeMoves = enable; }

			/// Sets the material boundary tolerance
		HK_FORCE_INLINE void setPreserveMaterialBoundaryTolerance(hkBool enable, hkReal tol) { m_preserveMaterialBoundary = enable; m_materialBoundaryTolerance.setFromFloat(tol); }

			/// Sets the coplanar simplification mode
		HK_FORCE_INLINE void enableCoplanarSimplify(hkBool enable, hkReal tol)	{ m_simplifyCoplanar = enable; m_coplanarTolerance.setFromFloat(tol); }

			/// Sets the attribute thresholds
		HK_FORCE_INLINE void setAttributeThresholds(const Threshold& thresholds) { m_thresholds = thresholds; }

			/// Set the 'open edge' scale. The QEM will be scaled depending on this, and the amount of open edges (i.e. not connected to another triangle)
			/// The effect of making this greater is to bias such triangles that have open edges, are less likely to be removed 
		void setOpenEdgeScale(hkReal scale) { m_openEdgeScale.setFromFloat(scale); }
			/// Get the open edge scale
		const hkSimdReal& getOpenEdgeScale() const { return m_openEdgeScale; }

			/// Set the scale calculator. If set to HK_NULL - the scaling defaults to 1.
		void setScaleCalculator(ScaleCalculator* calc) { m_scaleCalc = calc; }	
			/// Get the scale calculator
		HK_FORCE_INLINE ScaleCalculator* getScaleCalculator() { return m_scaleCalc; }

			/// Get the positions
		HK_FORCE_INLINE const hkArray<hkVector4>& getPositions() const { return m_positions; }

			/// Calculates the number of triangles per group
		void calcNumTrianglesPerGroup(hkArray<int>& trisPerGroup) const;

			/// Find the contraction for an edge (start, end)
		EdgeContraction* findContraction(int start, int end) const;

			/// Set a contraction controller
		void setContrationController(ContractionController* controller) { m_controller = controller; }
			/// Get the contraction controller
		ContractionController* getContractionController() const { return m_controller; }

			/// Get the position in world space
		HK_FORCE_INLINE const hkVector4& getPosition(int index) const { return m_positions[index]; }

			/// Get a position in the 0-1 space.
		void getPosition01(int index, hkVector4& pos) const;
			/// Get a position int the attrib space.
		void getPositionAttrib(int groupIndex, int index, hkVector4& pos) const;
			/// Get the position from an attribute, in world space.
		void getAttribPosition(int groupIndex, int attribIndex, hkVector4& pos) const;

			/// Ctor
		hkQemSimplifier();

	protected:

		struct BoundaryEdge
		{
			HK_FORCE_INLINE void set(int vA, int vB);
			HK_FORCE_INLINE bool equals(const BoundaryEdge& be) const;
			HK_FORCE_INLINE bool containsVertex(int v) const;
			HK_FORCE_INLINE void replaceVertex(int srcVertex, int dstVertex);
			HK_FORCE_INLINE bool isDegenerate() const;

				/// Start vertex
			int m_start;

				/// End vertex
			int m_end;
		};


	protected:

			/// Creates the list of material boundary edges
		void findMaterialBoundaries();

			/// Tests whether the given contraction (srcVertex -> dstVertex) preserves the material border
		bool contractionPreservesMaterialBoundary(int srcVertex, int dstVertex);

			/// Propagates a contraction (srcVertex -> dstVertex) to the boundary edges
		void applyContractionOnBoundary(int srcVertex, int dstVertex);

			/// Locates the boundary edge and returns its index, -1 if nothing was found
		HK_FORCE_INLINE int findBoundaryEdge(int srcVertex, int  dstVertex);

			/// Adds a boundary edge
		HK_FORCE_INLINE void addBoundaryEdge(int srcVertex, int  dstVertex);

	protected:

			/// Tests whether the given contraction (srcVertex -> dstVertex) preserves the co-planarity
		bool contractionPreservesCoplanarity(int srcVertex, int dstVertex);

			/// Tests whether the given contraction (srcVertex -> dstVertex) preserves the attributes
		bool contractionPreservesAttributes(int srcVertex, int dstVertex);

			/// Computes an interpolated attribute for the given vertex relative to the given triangle
		void computeInterpolatedAttribute(const Triangle* tri, hkVector4Parameter vP, hkArray<hkReal>& attribOut);

			/// Returns true if the given attribute is almost equal with another
		bool attributeIsApproxEqual(const hkArray<hkReal>& attribIn, const Attribute& tgtAttribute);

	protected:
		
		void _accumulateTriangleQem(const Triangle& tri, const hkVector4* triQem);
		bool _calcQuadrics();

		static void HK_CALL _calcNormal(hkVector4Parameter a, hkVector4Parameter b, hkVector4Parameter c, hkVector4& normal);
		bool _doesFlipTriangle(int vertexIndex, const EdgeContraction& contraction, hkVector4Parameter newPosition);
		bool _doesContractionFlipTriangle(const EdgeContraction& contraction);

		void _applyContraction(EdgeContraction* contraction);
		void _applyVertexChange(int positionIndex, const EdgeContraction& contraction);

		hkBool32 _findMove(const Attribute& attrib, const hkArray<EdgeId>& contractionEdgeIds, Attribute& move);
		void _calcVertexUniqueAttributes(int vertexIndex, hkArray<Attribute>& attribs);
		void _calcChooseError(int startIndex, int endIndex, const hkArray<EdgeId>& contractionEdgeIds, hkSimdReal& error);

		int _addGroup(int attribSize, const AttributeFormat& fmt, hkSimdRealParameter positionToAttribScale);

		bool _areGroupIndicesValid(int groupIndex) const;

			/// Work out a contraction which introduces the least error - works on any type of edge (even different attributes)
		EdgeContraction* _createChooseContraction(int start, int end, const hkArray<EdgeId>& edgeIds);
			/// Create a contraction
		EdgeContraction* _createContraction(int start, int end);
			/// Goes through all triangles, adding contractions for edges, that don't currently have any
		bool _calcContractions();
			/// Calc the sum of the qems for attrib indices start + end
		void _calcSumQems(int groupIndex, int start, int end, hkQuadricMetric& qm);

			/// Delete a contraction - removes from maps and min heap too
		void _deleteContraction(EdgeContraction* contraction);

		void _applyChooseContraction(int fromIndex, int targetIndex);


			/// Delete all of the contractions indexing the passed in vertex index
		void _deleteVertexContractions(VertexIndex index);

			/// Checks to see if all of the edges have the same attributes (and are in the same group id)
		hkBool32 _allEdgesHaveSameAttribs(const hkArray<EdgeId>& edgeIds);

			/// Check if attribute indexing seems reasonable
		hkBool32 _areAttributesOk() const;


			/// Returns true if there is a triangle, which is facing in the opposite direction to tri.
		bool _oppositeTriangleExists(Triangle* tri) const;

			/// Accumulate qem for the triangle - taking into account values from the ScaleCalculator
		void _accumulateScaleTriangleQem(const Triangle& tri, const hkVector4* triQem);
			/// Accumulate boundary qem metrics for triangles that have open edges. 
		void _accumulateOpenEdgeQem(const hkArray<Triangle*>& groupTris, const EdgeMap& edgeMap);


		hkFreeList m_contractionFreeList;										///< Storage for all the contractions.
		hkMinHeap<EdgeContraction*, EdgeContraction> m_contractions;			///< Provides a fast way to get the min error.
		hkPointerMap<hkUint64, EdgeContraction*> m_edgeContractionMap;			///< Map edge keys, to contractions.

		hkArray<Group> m_groups;												///< Storage for all of the groups.

		hkgpVertexTriangleTopology<Triangle> m_topology;						///< The topology.

		hkAabb m_positionsAabb;													///< AABB surrounding all positions in world space.
		hkVector4 m_aabbScale;													///< subtract AABB min, and mult by scale to get in 0-1 space.

		hkArray<hkVector4> m_positions;											///< All of the vertex positions in world space.

		hkBool m_isFinalized;
		hkBool m_inMesh;
		hkBool m_inGroup;

		hkBool m_enableOpenEdgeGeometry;										///< If set will handle geometry with open edges
		hkBool m_discardInvalidAttributeMoves;									///< If set and _findMove fails to translate an attribute, the returned cost of the contraction will be HK_REAL_MAX

		hkBool m_preserveMaterialBoundary;										///< Preserve material boundaries

		hkBool m_simplifyCoplanar;												///< Only simplifies triangles that are coplanar

		hkSimdReal m_openEdgeScale;												///< Scaling used for open edge processing
		hkSimdReal m_materialBoundaryTolerance;									///< Allows preservation of material boundaries by setting a very high cost on contractions that change it beyond this value
		hkSimdReal m_coplanarTolerance;											///< Tolerance for co-planarity (i.e. maximum distance from a vertex to a plane for the vertex to be considered coplanar)

		Threshold m_thresholds;													///< Thresholds used in attribute matching

		hkRefPtr<ContractionController> m_controller;

		hkRefPtr<ScaleCalculator> m_scaleCalc;

		hkArray<BoundaryEdge> m_materialBoundaries;								///< Material boundary edges
};

#endif // HK_QEM_SIMPLIFIER_H

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
