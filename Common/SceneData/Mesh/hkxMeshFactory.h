/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_HKX_MESH_FACTORY_H
#define HK_HKX_MESH_FACTORY_H

// This is an abstract mesh factory to be able to do different
// processing for different mesh system implementations.
// Primary reason is to support close integration with customer
// graphics engines.

#include <Common/Base/Container/StringMap/hkStringMap.h>
#include <Common/Serialize/Util/hkRootLevelContainer.h>
#include <Common/GeometryUtilities/Mesh/Skin/hkSkinnedMeshShape.h>

class hkMeshShape;
class hkMeshSystem;

class hkxMeshFactory : public hkReferencedObject
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SCENE_DATA);

	public:

			/// Destructor
		virtual ~hkxMeshFactory() {}

	public:

			/// Returns mesh system
		virtual hkMeshSystem* getMeshSystem() = 0;

			/// Creates/extracts mesh shapes according to ( hkxScene ) data in the root continer
		virtual void extractShapes( hkRootLevelContainer* rootLevelContainer, hkStringMap<int>& extraGraphicsNodes, hkStringMap<hkMeshShape*>& shapesOut ) = 0;

			/// Creates additional data based on the mesh shapes and embeds them in the root container
			/// Primary use is to create engine-dependent graphical representation for dynamically
			/// created shapes and embed them as engine-dependent data.
		virtual void storeShapes( hkRootLevelContainer* rootLevelContainer, hkArray<const hkMeshShape*>& shapes ) = 0;

			/// Removes all the given shapes from the root level container
		virtual void removeShapes(hkRootLevelContainer* rootLevelContainer, hkArray<const hkMeshShape*>& shapes) = 0;

			/// Gets the transform to Havok's coordinate system
		virtual const hkMatrix3& getTransform() const = 0;

			/// Sets the transform to Havok's coordinate system
		virtual void setTransform( const hkMatrix3& transform ) = 0;

	public:

			/// Creates a skinned mesh shape from the given mesh shapes and transforms. A single bone will drive each of the provided shapes.
			/// May return null if the factory does not support the operation
		virtual hkSkinnedMeshShape* createSkinnedMesh(const char* skinnedMeshName, const hkMeshShape** meshShapesIn, const hkQTransform* transformsIn, int numMeshes, int maxBonesPerSection) = 0;
};

#endif // HK_HKX_MESH_FACTORY_H

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
