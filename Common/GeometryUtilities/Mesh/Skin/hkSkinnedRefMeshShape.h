/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_SKINNED_REF_MESH_SHAPE_H
#define HK_SKINNED_REF_MESH_SHAPE_H

#include <Common/GeometryUtilities/Mesh/hkMeshShape.h>
#include <Common/GeometryUtilities/Mesh/Skin/hkSkinnedMeshShape.h>

extern const hkClass hkSkinnedRefMeshShapeClass;

	/// Mesh shape that references a sub-set of the bones in a hkSkinnedMeshShape
class hkSkinnedRefMeshShape : public hkMeshShape
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SCENE_DATA);
		HK_DECLARE_REFLECTION();

	public:

			/// Constructor
		hkSkinnedRefMeshShape(hkSkinnedMeshShape* fullSkin, const short* bones, const hkQTransform* localFromRootTransforms, int numBones);

			/// Constructor
		hkSkinnedRefMeshShape(hkSkinnedMeshShape* fullSkin);

			/// Serialization constructor
		hkSkinnedRefMeshShape(class hkFinishLoadedObjectFlag flag);

			/// Destructor
		virtual ~hkSkinnedRefMeshShape();

	public:

			/// Returns the skinned mesh shape
		HK_FORCE_INLINE hkSkinnedMeshShape* getSkinnedMeshShape() const				{ return m_skinnedMeshShape; }

			/// Sets the skinned mesh shape
		HK_FORCE_INLINE void setSkinnedMeshShape(hkSkinnedMeshShape* newShape)		{ m_skinnedMeshShape = newShape; }

			/// Returns the array of bones
		HK_FORCE_INLINE const hkArray<short>& getBones() const				{ return m_bones; }

			/// Returns the array of transforms
		HK_FORCE_INLINE const hkArray<hkQTransform>& getTransforms() const	{ return m_localFromRootTransforms; }

			/// Creates a compound mesh by merging all the given Vision meshes
		static hkSkinnedRefMeshShape* HK_CALL create(const hkMeshShape*const* shapes, const hkQTransform* transforms, int numShapes);

	public:

			/// Returns the amount of sections
		virtual int getNumSections() const;

			/// Gets information about a section
		virtual void lockSection(int sectionIndex, hkUint8 accessFlags, hkMeshSection& sectionOut) const;

			/// Unlocks a mesh section. Must be given exactly the same structure contents as was returned from a lockSection
			/// otherwise behavior is undefined.
		virtual void unlockSection(const hkMeshSection& section) const;

			/// Returns an optional name of the mesh shape
		virtual const char* getName() const;

			/// Sets an optional name
		virtual void setName(const char* n);
	
			/// Returns the class type
		virtual const hkClass* getClassType() const;

	protected:

			/// The skinned mesh shape we're referencing
		hkRefPtr<hkSkinnedMeshShape> m_skinnedMeshShape;

			/// The sub-set of bones we're referencing
		hkArray<short> m_bones;

			/// The array of bone matrices that transform from root skin to current shape local space
		hkArray<hkQTransform> m_localFromRootTransforms;

			/// The name
		hkStringPtr m_name;
};

#endif	//	HK_SKINNED_REF_MESH_SHAPE_H

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
