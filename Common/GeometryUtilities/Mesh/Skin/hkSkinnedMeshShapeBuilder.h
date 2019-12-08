/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_SKINNED_MESH_SHAPE_BUILDER_H
#define HK_SKINNED_MESH_SHAPE_BUILDER_H

#include <Common/GeometryUtilities/Mesh/Skin/hkSkinnedMeshShape.h>
#include <Common/GeometryUtilities/Mesh/hkMeshSystem.h>
#include <Common/GeometryUtilities/Mesh/hkMeshVertexBuffer.h>
#include <Common/GeometryUtilities/Mesh/Utils/PrimitiveUtil/hkMeshPrimitiveUtil.h>
#include <Common/GeometryUtilities/Mesh/IndexedTransformSet/hkIndexedTransformSet.h>
#include <Common/Base/Container/BitField/hkBitField.h>

class hkAabb;

/// Skinned mesh builder
class hkSkinnedMeshBuilder
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SCENE_DATA, hkSkinnedMeshBuilder);

		// Type shortcuts
		typedef hkSkinnedMeshShape::BoneSetId	BoneSetId;

		/// Skinning info
		struct SkinningInfo
		{
			int	m_boneIndex;		///< First bone of the bone-set
			int	m_lastVertex;		///< Index of the last vertex in the group
		};

	public:

			/// Constructor
		hkSkinnedMeshBuilder(hkSkinnedMeshShape* skinnedMeshShape, hkMeshSystem* meshSystem, int maxBonesPerMesh);

			/// Destructor
		~hkSkinnedMeshBuilder();

	public:

			/// Adds a mesh
		void addMesh(const hkMeshShape* meshShape, const hkQTransform& meshTransform, int numBones);

			/// Builds the skinned mesh shape
		void build(bool buildSingleMesh = false);

			/// Gets skinning info
		void getSkinningInfo( hkArray<SkinningInfo>& sectionsOut );

	protected:

		/// Descriptor for a mesh section
		struct MeshSection
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SCENE_DATA, hkSkinnedMeshBuilder::MeshSection);

			/// Compares two sections by surface index
			static HK_FORCE_INLINE bool HK_CALL less(const MeshSection& sA, const MeshSection& sB);

			/// Constructor
			MeshSection();

			/// Copy constructor
			MeshSection(const MeshSection& other);

			int m_meshIndex;					///< Index of the mesh in m_sourceMeshes
			int m_surfaceIndex;					///< Index of the surface in m_surfaces
			int m_subMeshIndex;					///< Index of the sub-mesh
			int m_boneSetIndex;					///< Index of the bone-set driving this mesh section
			BoneSetId m_meshBoneSetId;			///< BoneSet Id in the built mesh

			hkBitField m_originalUsedVertices;	///< Bit-field marking the vertices used in this section
		};

		/// Descriptor for a skin
		struct SkinDescriptor
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SCENE_DATA, hkSkinnedMeshBuilder::SkinDescriptor);

			/// Counts the number of sub-meshes
			int countSubmeshes() const;

			hkMeshBoneIndexMapping m_localFromWorldBoneMap;	///< Bone mapping. Maps a global bone index to a descriptor bone index
			hkMeshBoneIndexMapping m_worldFromLocalBoneMap;	///< Bone mapping. Maps a descriptor bone index to the global bone index
			hkBitField m_usedBones;							///< A bit-field of used bones
			hkArray<MeshSection> m_sections;				///< Mesh sections in this skin
		};

	protected:

			/// Computes the descriptors from the source meshes
		void computeDescriptors();

			/// Converts an array of indices from mesh-section bone-set "space" to skin-descriptor "space"
		void convertBoneIndices(hkArray<int>& boneSetIndices, hkArray<hkFloat32>& boneSetWeights, int boneSetId, const SkinDescriptor& sd) const;

			/// Adds a new part
		void addPart(BoneSetId boneSetId, hkUint16 meshSectionIndex, int startVtx, int numVertices, int startIdx, int numIndices, const hkAabb& aabb);

			/// Adds a surface. Returns its index
		int addSurface(hkMeshMaterial* surface);

			/// Computes the shared vertex buffer format
		void computeVertexFormat();

			/// Computes the number of vertices in the given skin
		int computeNumVertices(SkinDescriptor& sd);

			/// Fills the provided skinned vertex buffer with the data from the given skin descriptor
		void fillSkinnedVertexBuffer(hkMeshVertexBuffer* skinnedVb, int vbOffset, int numVbVerts, const SkinDescriptor& sd);

			/// Copies a sub-set of vertices from one locked vertex buffer to another
		void copyVertices(	const hkMeshVertexBuffer::LockedVertices& dstVerts, const hkVertexFormat& dstVtxFmt, int dstStartVertex, 
							const hkMeshVertexBuffer::LockedVertices& srcVerts, const hkVertexFormat& srcVtxFmt, const hkBitField& srcVertsToCopy);

			/// Set-up the bone weights & indices
		void createBoneWeightsAndIndices(hkMeshVertexBuffer* skinnedVb, int vbOffset, int numVbVerts, const SkinDescriptor& sd);

			/// Compute common index buffer format
		void computeIndexFormat(const SkinDescriptor& sd, hkMergeMeshPrimitvesCalculator& mpc);

			/// Creates the mesh for the given descriptor. The indices are not properly set at this stage
		hkMeshShape* createMesh(const SkinDescriptor* HK_RESTRICT descriptors, int numDescriptors, const hkMergeMeshPrimitvesCalculator& mpc, hkMeshVertexBuffer* vb);

			/// Fills the provided skinned index buffer with the data from the given skin descriptor
		void fillSkinnedIndexBuffer(const SkinDescriptor* HK_RESTRICT descriptors, int numDescriptors, hkMeshShape* skinnedMesh);

			/// Computes the render vertex range
		void calcRenderVertexRange(const hkMeshSection& meshSection, hkBitField& usedVertsOut);

			/// Applies the given transform to the given range of vertices
		void applyTransform(const hkQTransform& mtx, const hkMeshVertexBuffer::LockedVertices& verts, int startVertex, int numVertices);

			/// Computes the AABB of the given sub-set of vertices in the given vertex buffer
		void calcAabb(const hkMeshVertexBuffer::LockedVertices& verts, int startVertex, int numVertices, hkAabb& aabbOut);

			///	Adds a bone section for the given skin descriptor
		void addBoneSection(hkMeshShape* boneSectionMesh, SkinDescriptor& sd);

	protected:

		int m_maxNumBonesPerMesh;									///< Maximum number of bones per mesh
		int m_numTotalBones;										///< The total number of bones in the mesh
		
		hkArray<hkMeshMaterial*> m_surfaces;						///< Array of unique materials

		hkArray< hkRefPtr<const hkMeshShape> > m_sourceMeshes;		///< Array of source meshes
		hkArray<hkQTransform> m_sourceMeshTransforms;				///< Array of source mesh transforms
		hkArray<MeshSection> m_sourceMeshSections;					///< Array of mesh sections collected from the source meshes
		hkArray<hkMeshBoneIndexMapping> m_boneSets;					///< Array of bone sets. A mesh section is driven by a single bone set
		hkArray<SkinDescriptor> m_skinDescriptors;					///< Array of existing skins

		hkVertexFormat m_vfmt;										///< Vertex buffer format
		hkSkinnedMeshShape* m_skinnedMeshShape;						///< The resulting skinned mesh shape
		hkMeshSystem* m_meshSystem;									///< The mesh system
};

#endif	//	HK_SKINNED_MESH_SHAPE_BUILDER_H

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
