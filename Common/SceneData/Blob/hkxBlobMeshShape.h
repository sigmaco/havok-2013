/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKSCENEDATA_BLOB_MESH_SHAPE_H
#define HKSCENEDATA_BLOB_MESH_SHAPE_H

extern const hkClass hkxBlobMeshShapeClass;

#include <Common/SceneData/Blob/hkxBlob.h>
#include <Common/GeometryUtilities/Mesh/hkMeshShape.h>

	/// A storage only mesh shape implementation. The stored data is a blob.
class hkxBlobMeshShape : public hkMeshShape
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SCENE_DATA);
		HK_DECLARE_REFLECTION();

	public:

			/// Constructor
		hkxBlobMeshShape()
		:	hkMeshShape()
		,	m_name(HK_NULL)
		{}

			/// Serialization constructor
		hkxBlobMeshShape(hkFinishLoadedObjectFlag flag)
		:	hkMeshShape(flag)
		,	m_blob(flag)
		,	m_name(flag)
		{}

	public:

			/// Returns the amount of sections
		virtual int getNumSections() const { return -1; }

			/// Gets information about a section
		virtual void lockSection(int sectionIndex, hkUint8 accessFlags, hkMeshSection& sectionOut) const {}

			/// Unlocks a mesh section.
		virtual void unlockSection(const hkMeshSection& section) const {}

			/// Returns an optional name of the mesh shape
		virtual const char* getName() const { return m_name; }

			/// Sets an optional name
		virtual void setName(const char* n) { m_name = n; }

			/// Returns the class type
		virtual const hkClass* getClassType() const { return &hkxBlobMeshShapeClass; }

	public:

			/// The mesh shape data, as a blob
		hkxBlob m_blob;

			/// The name
		hkStringPtr m_name;
};

#endif	// HKSCENEDATA_BLOB_MESH_SHAPE_H

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
