/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_SKINNED_MESH_SHAPE_H
#define HK_SKINNED_MESH_SHAPE_H

#include <Common/Base/Types/hkHandle.h>
#include <Common/GeometryUtilities/Mesh/hkMeshShape.h>
#include <Common/GeometryUtilities/Mesh/IndexedTransformSet/hkIndexedTransformSet.h>

extern const hkClass hkSkinnedMeshShapeClass;
extern const hkClass hkStorageSkinnedMeshShapeClass;

	/// Abstract skinned mesh shape. It is a collection of bone sections, where a bone section is driven by a contiguous range of bones.
	/// Each bone section has a collection of parts, where a part represents a contiguous portion of the vertex and index buffers, rendered
	/// with the same material. 
class hkSkinnedMeshShape : public hkReferencedObject
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SCENE_DATA);
		HK_DECLARE_REFLECTION();

	public:

		/// Types
		HK_DECLARE_HANDLE(BoneSetId, hkUint16, 0xFFFF);

		/// Set of bones deforming a part
		struct BoneSet
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SCENE_DATA, hkSkinnedMeshShape::BoneSet);
			HK_DECLARE_REFLECTION();

			hkUint16 m_boneBufferOffset;	///< Offset in the bones buffer
			hkUint16 m_numBones;			///< Number of bones in the set
		};

			/// Bone section deforming a hkMeshShape
		struct BoneSection
		{
			//+version(1)
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SCENE_DATA, hkSkinnedMeshShape::BoneSection);
			HK_DECLARE_REFLECTION();

				/// Constructor
			BoneSection();

				/// Serialization constructor
			BoneSection(class hkFinishLoadedObjectFlag flag);

			hkRefPtr<hkMeshShape> m_meshBuffer;		///< The mesh buffer

			/// Start boneSet
			BoneSetId m_startBoneSetId;				//+overridetype(hkUint16)
			hkInt16 m_numBoneSets;					///< Number of bones
		};

			/// Vertex / index buffer part. Driven by a set of bones, with a single material, has a contiguous section of the vertex and index buffer.
		struct Part
		{
			//+version(1)
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SCENE_DATA, hkSkinnedMeshShape::Part);
			HK_DECLARE_REFLECTION();

			/// Compares two parts by boneSetId
			static HK_FORCE_INLINE bool HK_CALL less(const Part& pA, const Part& pB)	{	return pA.m_boneSetId < pB.m_boneSetId;	}

			int m_startVertex;				///< Start vertex
			int m_numVertices;				///< Number of vertices

			int m_startIndex;				///< Start index
			int m_numIndices;				///< Number of indices

			/// BoneSet index
			BoneSetId m_boneSetId;			//+overridetype(hkUint16)
			hkUint16 m_meshSectionIndex;	///< Mesh section index
			hkVector4 m_boundingSphere;		///< Bounding sphere
		};

	public:

			/// Constructor
		hkSkinnedMeshShape();

			/// Serialization constructor
		hkSkinnedMeshShape(class hkFinishLoadedObjectFlag flag);

			/// Destructor
		virtual ~hkSkinnedMeshShape();

	public:

			/// Gets the number of bone sections
		virtual int getNumBoneSections() const = 0;

			/// Returns the bone section at the given index
		virtual void getBoneSection(int boneSectionIndex, BoneSection& boneSectionOut) const = 0;

			/// Returns the bone set associated with the given id
		virtual void getBoneSet(BoneSetId boneSetId, BoneSet& boneSetOut) const = 0;

			/// Returns the bones associated with the given BoneSet
		virtual void getBoneSetBones(BoneSetId boneSetId, hkArray<hkInt16>& bonesOut) const = 0;

			/// Returns the number of parts
		virtual int getNumParts() const = 0;

			/// Returns the part at the given index
		virtual void getPart(int partIndex, Part& partOut) const = 0;

			/// Prints a lot of debug info about the mesh
		virtual void dbgOut() const;

			/// Gets the name of this shape
		virtual const char* getName() const { return HK_NULL; }

			/// Sets the name of this shape
		virtual void setName(const char* name) {}

			/// Computes the bone mapping for the given bone section
		void computeBoneSectionMapping(int boneSectionIdx, hkMeshBoneIndexMapping& mappingOut) const;

		/// Computes all mesh section mappings. There will be one mapping per bone section, stored in boneSectionMappingsOut. For each unique mesh section
		/// in each bone section, there will be an entry in the perSectionBoneMappingIdicesOut, indicating which of the boneSectionMappingsOut to use.
		void computeMeshSectionMappings(hkArray<hkMeshBoneIndexMapping>& boneSectionMappingsOut, hkArray<hkUint16>& perSectionBoneMappingIndicesOut);

		//
		//	Builder interface
		//

	public:

			/// Adds a new bone section
		virtual void addBoneSection(hkMeshShape* meshShape, BoneSetId startBoneSetId, hkInt16 numBoneSets) {}

			/// Adds a new part
		virtual void addPart(const Part& p) {}

			/// Sorts the parts by increasing bone indices
		virtual void sortParts() {}

			/// Creates a BoneSet out of the provided array of bones. Returns the index of the newly created BoneSet
		virtual BoneSetId addBoneSet(const hkInt16* HK_RESTRICT boneIndices, int numBones) { return BoneSetId::invalid(); }
};

	/// Skinned mesh shape which stores the sections and parts in internal arrays
class hkStorageSkinnedMeshShape : public hkSkinnedMeshShape
{
	//+version(1)
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SCENE_DATA);
		HK_DECLARE_REFLECTION();

	public:

			/// Constructor
		hkStorageSkinnedMeshShape();

			/// Serialization constructor
		hkStorageSkinnedMeshShape(class hkFinishLoadedObjectFlag flag);

	public:

			/// Sets the mesh shape on the given bone section
		HK_FORCE_INLINE void setBoneSectionMeshShape(int idx, hkMeshShape* newShape) { m_boneSections[idx].m_meshBuffer = newShape; }

	public:

			/// Gets the number of bone sections
		virtual int getNumBoneSections() const HK_OVERRIDE;

			/// Returns the bone section at the given index
		virtual void getBoneSection(int boneSectionIndex, BoneSection& boneSectionOut) const HK_OVERRIDE;

			/// Returns the bone set associated with the given id
		virtual void getBoneSet(BoneSetId boneSetId, BoneSet& boneSetOut) const HK_OVERRIDE;

			/// Returns the bones associated with the given BoneSet
		virtual void getBoneSetBones(BoneSetId boneSetId, hkArray<hkInt16>& bonesOut) const HK_OVERRIDE;

			/// Returns the number of parts
		virtual int getNumParts() const HK_OVERRIDE;

			/// Returns the part at the given index
		virtual void getPart(int partIndex, Part& partOut) const HK_OVERRIDE;

			/// Sorts the parts by increasing bone indices
		virtual void sortParts() HK_OVERRIDE;

			/// Adds a new bone section
		virtual void addBoneSection(hkMeshShape* meshShape, BoneSetId startBoneSetId, hkInt16 numBoneSets) HK_OVERRIDE;

			/// Adds a new part
		virtual void addPart(const Part& p) HK_OVERRIDE;

			/// Returns the class type
		virtual const hkClass* getClassType() const HK_OVERRIDE;

			/// Gets the name of this shape
		virtual const char* getName() const HK_OVERRIDE;

			/// Sets the name of this shape
		virtual void setName(const char* name) HK_OVERRIDE;

		/// Creates a BoneSet out of the provided array of bones. Returns the index of the newly created BoneSet
		virtual BoneSetId addBoneSet(const hkInt16* HK_RESTRICT boneIndices, int numBones) HK_OVERRIDE;

	protected:

		hkArray<hkInt16> m_bonesBuffer;				///< Bones buffer
		hkArray<BoneSet> m_boneSets;				///< Array of bone sets defined on the bones buffer

			/// Bone sections
		hkArray<BoneSection> m_boneSections;

			/// Parts
		hkArray<Part> m_parts;

			/// Name
		hkStringPtr m_name;
};

#endif	//	HK_SKINNED_MESH_SHAPE_H

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
