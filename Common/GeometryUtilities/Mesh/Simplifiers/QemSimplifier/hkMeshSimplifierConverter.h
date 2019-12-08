/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_MESH_SIMPLIFIER_CONVERTER_H
#define HK_MESH_SIMPLIFIER_CONVERTER_H

#include <Common/Internal/GeometryProcessing/Topology/hkgpVertexTriangleTopology.h>

#include <Common/Base/Algorithm/Sort/hkSort.h>

#include <Common/Base/Container/MinHeap/hkMinHeap.h>

#include <Common/GeometryUtilities/Mesh/Simplifiers/QemSimplifier/hkQemSimplifier.h>
#include <Common/GeometryUtilities/Mesh/hkMeshVertexBuffer.h>
#include <Common/GeometryUtilities/Mesh/hkMeshSystem.h>
#include <Common/GeometryUtilities/Mesh/hkMeshShape.h>
#include <Common/GeometryUtilities/Mesh/Utils/VertexSharingUtil/hkVertexSharingUtil.h>


class hkQuadricMetric;

class hkVertexSharingUtil;

class hkQemSimplifier;
class hkFindUniquePositionsUtil;

class hkMeshSectionLockSet;
class hkVertexFloat32Converter;
struct hkMeshSection;
class hkMeshMaterial;


class hkMeshSimplifierConverter
{
	public:
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE,hkMeshSimplifierConverter);
		typedef hkQemSimplifier::TopologyType TopologyType;

		typedef TopologyType::EdgeId			EdgeId;
		typedef TopologyType::Edge				Edge;
		typedef TopologyType::VertexIndex		VertexIndex;
		typedef hkQemSimplifier::Triangle		Triangle;
		typedef hkVertexSharingUtil::Threshold	Threshold;
		
		struct Group
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE,hkMeshSimplifierConverter::Group);
			int m_modelIndex;									///< The model this group is associated with
			hkVertexFormat m_vertexFormat;                      ///< The vertex format in this group
			hkRefPtr<hkMeshMaterial> m_material;                ///< The material associated with this group
			int m_qemGroupIndex;								///< The group in the qem simplifier
		};
		
		
			/// Scale the weights by scale
		void scaleWeights(hkSimdRealParameter scale);

			/// Get the weight being used for this usage/subUsage
		void getWeight(hkVertexFormat::ComponentUsage usage, int subUsage, hkSimdReal& weight) const;
			/// Set the weight being used for this usage/subUsage
		void setWeight(hkVertexFormat::ComponentUsage usage, int subUsage, hkSimdRealParameter weight);
			/// Clear the weights
		void clearWeights();

			/// Set the weight (for position) of a material
		void setMaterialWeight(hkMeshMaterial* material, hkSimdRealParameter weight);
			/// Get the weight (for position) of a material
		void getMaterialWeight(hkMeshMaterial* material, hkSimdReal& weight) const;

			/// Set the default
		void setDefaultMaterialWeight(hkSimdRealParameter weight) { m_defaultMaterialWeight = weight; }
			/// Get the default
		const hkSimdReal& getDefaultMaterialWeight() const { return m_defaultMaterialWeight; }

			/// Set up a mesh to simplify. If not NULL, the thresholds will be passed to the vertex sharing utility.
		hkResult initMesh(const hkMeshShape* shape, hkQemSimplifier& simplifier, hkFindUniquePositionsUtil& positionUtil, const Threshold* thresholds, bool unitScalePosition);
			
			/// Add lots of meshes to simplify simultaneously. If not NULL, the thresholds will be passed to the vertex sharing utility.
		hkResult initMeshes(const hkMeshShape*const* srcMeshes, int numMeshes, hkQemSimplifier& simplifier, hkFindUniquePositionsUtil& positionUtil, const Threshold* thresholds, bool unitScalePosition);

			/// Create a mesh from the contents - must have been finalized before this call
		hkMeshShape* createMesh(hkMeshSystem* system, int modelIndex, hkQemSimplifier& simplifier, bool unitScalePosition);
		
			/// Works out how many triangles in a model
		int calcNumModelTriangles(int modelIndex, const hkQemSimplifier& simplifier) const;

			/// Simplifies the mesh shape as long as the error is less than maxCoplanarError.
			/// Set allowTrue to false - if the mesh is known to be closed for better performance.
			/// If no simplification is applied to the meshShape, the function may return meshShape with an increased reference count.
			/// If not NULL, the thresholds will be passed to the vertex sharing utility.
		hkMeshShape* simplifyCoplanar(hkMeshSystem* system, const hkMeshShape* meshShape, const Threshold* thresholds, hkReal maxCoplanarError = 1e-6f, bool allowOpen = true, bool unitScalePosition = true);

			/// Set the default weight for a usage
		void setDefaultWeight(hkVertexFormat::ComponentUsage usage, hkSimdRealParameter weight) { m_defaultWeights[usage] = weight; }
			/// Get the default weight for a usage
		const hkSimdReal& getDefaultWeight(hkVertexFormat::ComponentUsage usage) const { return m_defaultWeights[usage]; }


			/// Ctor
		hkMeshSimplifierConverter();


			/// Given a section, returns the positions of all the vertices (the section must contain a read vertexBuffer, and the buffer must contain position info)		
		static hkResult HK_CALL getPositions(const hkMeshSection& section, hkArray<hkVector4>& positions);

		
		hkBool m_positionOnly;													///< Do simplification through position only

	protected:
		
		void _addMeshSection(hkFindUniquePositionsUtil& positionUtil, hkVertexSharingUtil& sharingUtil, const hkMeshSection& section, int groupIndex, hkQemSimplifier& simplifier);
		static void HK_CALL _calcAabb(const hkVector4* pos, int numPos, hkAabb& aabb);
		static hkResult HK_CALL _addPositions(const hkMeshSectionLockSet& sectionLockSet, hkFindUniquePositionsUtil& positionUtil );
		void _addModelGroups(hkMeshSectionLockSet& sectionLockSet, int modelIndex, hkArray<int>& sectionMapOut);


		int _findGroup(int modelIndex, hkMeshMaterial* material, const hkVertexFormat& vertexFormat) const;
			/// Add a group, returns the index of the new group
		int _addGroup(int modelIndex, hkMeshMaterial* material, const hkVertexFormat& vertexFormat);
		void _getVertexFormat(hkMeshVertexBuffer* buffer, hkVertexFormat& vertexFormat);

		void _setWeights(hkMeshMaterial* material, const hkVertexFormat& format, hkVertexFloat32Converter& converter);
		
		void _verifyLastGroupAttributes(hkQemSimplifier& simplifier, const hkVertexFloat32Converter& converter, hkMeshMaterial* material);

		hkSimdReal m_defaultMaterialWeight;
		hkArray<hkRefPtr<hkMeshMaterial> > m_materials;
		hkArray<hkSimdReal> m_materialWeight;

		hkArray<Group> m_groups;												///< Storage for all of the groups
		hkAabb m_srcAabb;
		hkArray<hkSimdReal> m_weights;												///< This works with m_weightElement to define a weight
		hkArray<hkUint32> m_weightElements;
		hkSimdReal m_defaultWeights[hkVertexFormat::USAGE_LAST];					///< The default weights by type
};

#endif // HK_MESH_SIMPLIFIER_CONVERTER_H

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
