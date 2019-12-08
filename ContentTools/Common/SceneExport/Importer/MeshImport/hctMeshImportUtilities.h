/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_MODELER_MESH_BUILDER_UTILITIES__H
#define HK_MODELER_MESH_BUILDER_UTILITIES__H


///
/// This utility class provides a modeler-independent way to build a modeler mesh/node from a Havok mesh.
///
class hctModelerMeshBuilderUtilities
{
	public:

		/// Locks the required sections from the mesh. Prunes all sections from the set that don't contain triangle information.
		/// Returns the number of 'triangle' sections available in the pruned set (can be 0 if none available/left).
		static int HK_CALL prepareMeshSectionLockSet(const hkMeshBody& meshBody, hkMeshSectionLockSet* lockSet);

		/// Converts the given Havok mesh into modeler mesh/node. Requires the lock set to be processed by prepareMeshSectionLockSet() first.
		static hkResult HK_CALL convertHavokMeshToModelerNode(const hkMeshBody& meshBody, const hkMeshSectionLockSet& lockSet, hctModelerMeshBuilder& modelerMeshBuilder);
};


#endif // HK_MODELER_MESH_BUILDER_UTILITIES__H

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
