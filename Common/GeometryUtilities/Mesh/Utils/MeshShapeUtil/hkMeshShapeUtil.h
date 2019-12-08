/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_MESH_SHAPE_UTIL_H
#define HK_MESH_SHAPE_UTIL_H

#include <Common/GeometryUtilities/Mesh/hkMeshShape.h>
#include <Common/GeometryUtilities/Mesh/IndexedTransformSet/hkIndexedTransformSet.h>

class hkMeshSystem;
class hkMeshMaterialRegistry;
class hkAabb;

	/// A simple utility for processing hkMeshShapes
class hkMeshShapeUtil
{
    public:
        HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_SCENE_DATA, hkMeshShapeUtil );


        struct Statistics
        {
            HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_SCENE_DATA, hkMeshShapeUtil::Statistics );

            void clear()
            {
                m_totalNumVertices = 0;
                m_totalNumPrimitives = 0;
                m_numUniqueVertexBuffers = 0;
                m_numUniqueMaterials = 0;
            }

            int m_totalNumVertices;
            int m_totalNumPrimitives;
            int m_numUniqueVertexBuffers;
            int m_numUniqueMaterials;
        };

            /// Calculate statistics for a single shape
        static void HK_CALL calculateStatistics(const hkMeshShape* shape, Statistics& statsOut);

            /// Calculate statistics across multiple shapes
        static void HK_CALL calculateStatistics(const hkMeshShape** shape, int numShapes, Statistics& statsOut);

            /// Goes through all of the vertex buffers referenced in the shape, and finds their
            /// unique positions.
        static void HK_CALL findUniqueVertexPositions(hkMeshShape* shape, hkArray<hkVector4>& verticesOut);

            /// Converts a mesh shape constructed in one mesh system to another
        static hkMeshShape* HK_CALL convert(hkMeshMaterialRegistry* srcRegistry, const hkMeshShape* srcShape, hkMeshMaterialRegistry* dstRegistry, hkMeshSystem* dstSystem);

			/// Replace all of the vertex buffers in meshShape with those specified in the buffer map. If not found will just keep the original.
		static hkMeshShape* HK_CALL replaceShapeVertexBuffers(hkMeshSystem* meshSystem, const hkMeshShape* meshShape, hkPointerMap<hkMeshVertexBuffer*, hkMeshVertexBuffer*>& bufferMap);

            /// Transforms the meshShape by the input transform (normalizes normals if normalize is set)
        static hkResult HK_CALL transform(hkMeshShape* meshShape, const hkMatrix4& transformIn, hkBool normalize);

			/// Calc the aabb surrounding a shape
		static void HK_CALL calcAabb(const hkMeshShape* shape, hkAabb& aabbOut);

		/// Returns a new mesh shape with at most maxBones in each mesh section. If the mesh has less than the maximum number of bones per section,
		/// the function returns the unchanged original mesh. The function also returns the array of bone mappings, one for each mesh section.
		static const hkMeshShape* HK_CALL createMeshWithLimitedNumBones(hkMeshSystem* meshSystem, const hkMeshShape* srcShape, int maxBonesPerSection, int numTotalMeshBones, hkArray<hkMeshBoneIndexMapping>& boneMappingsOut);
};

#endif // HK_MESH_SHAPE_UTIL_H

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
