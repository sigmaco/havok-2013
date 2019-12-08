/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */


#ifndef HK_HKX_MEMORY_MESH_FACTORY_H
#define HK_HKX_MEMORY_MESH_FACTORY_H

// Mesh factory to create hkMemoryMeshShapes from hkxScene data

#include <Common/SceneData/Mesh/hkxMeshFactory.h>
#include <Common/GeometryUtilities/Mesh/Skin/hkSkinnedMeshShape.h>

class hkMemoryMeshSystem;

class hkxMemoryMeshFactory : public hkxMeshFactory
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_EXPORT);

	public:

		hkxMemoryMeshFactory();
		virtual ~hkxMemoryMeshFactory();

			// hkxMeshFactory methods
		virtual hkMeshSystem* getMeshSystem();
		virtual void extractShapes( hkRootLevelContainer* rootLevelContainer, hkStringMap<int>& extraGraphicsNodes, hkStringMap<hkMeshShape*>& shapesOut );
		virtual void storeShapes( hkRootLevelContainer* rootLevelContainer, hkArray<const hkMeshShape*>& shapes );
		virtual const hkMatrix3& getTransform() const;
		virtual void setTransform( const hkMatrix3& transform );

			/// Creates a skinned mesh shape from the given mesh shapes and transforms. A single bone will drive each of the provided shapes.
			/// Currently, the implementation returns HK_NULL.
		virtual hkSkinnedMeshShape* createSkinnedMesh(const char* skinnedMeshName, const hkMeshShape** meshShapesIn, const hkQTransform* transformsIn, int numMeshes, int maxBonesPerSection);

			/// Removes all the given shapes from the root level container
		virtual void removeShapes(hkRootLevelContainer* rootLevelContainer, hkArray<const hkMeshShape*>& shapes);

	public:

			/// Creates shapes based on the mesh data in hkxScene with the use of the supplied hkMemoryMeshSystem
		static void extractShapes( hkRootLevelContainer* rootLevelContainer, hkStringMap<int>& extraGraphicsNodes, hkMemoryMeshSystem *meshSystem, hkStringMap<hkMeshShape*>& shapesOut );

	protected:

		hkMemoryMeshSystem* m_meshSystem;
};

#endif // HK_HKX_MEMORY_MESH_FACTORY_H

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
