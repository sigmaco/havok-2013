/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_SKIN_BINDING_H
#define HK_SKIN_BINDING_H

#include <Common/GeometryUtilities/Mesh/hkMeshShape.h>

extern const hkClass hkSkinBindingClass;

/// A skinned mesh
class hkSkinBinding : public hkMeshShape
{
	public:

		HK_DECLARE_REFLECTION();
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SCENE_DATA);

	public:

		/// Constructor
		hkSkinBinding(hkMeshShape* skinnedMesh, const hkMatrix4* HK_RESTRICT worldFromBoneTransforms, const hkStringPtr* HK_RESTRICT boneNames, int numBones);

		/// Serialization constructor
		hkSkinBinding(hkFinishLoadedObjectFlag flag);

	public:

		/// Returns the amount of sections
		virtual int getNumSections() const HK_OVERRIDE;

		/// Gets information about a section
		virtual void lockSection(int sectionIndex, hkUint8 accessFlags, hkMeshSection& sectionOut) const HK_OVERRIDE;

		/// Unlocks a mesh section. Must be given exactly the same structure contents as was returned from a lockSection
		/// otherwise behavior is undefined.
		virtual void unlockSection(const hkMeshSection& section) const HK_OVERRIDE;

		/// Returns an optional name of the mesh shape
		virtual const char* getName() const HK_OVERRIDE;

		/// Sets an optional name
		virtual void setName(const char* n) HK_OVERRIDE;

		/// Returns the class type
		virtual const hkClass* getClassType() const HK_OVERRIDE;

		/// Returns the index of the bone with the given name
		int findBone(const char* name) const;

	public:

		/// Returns the skin
		HK_FORCE_INLINE const hkMeshShape* getSkin() const		{	return m_skin;	}
		HK_FORCE_INLINE hkMeshShape* accessSkin()				{	return m_skin;	}

		/// Returns the number of bones
		HK_FORCE_INLINE int getNumBones() const								{	return m_worldFromBoneTransforms.getSize();	}

		/// Returns the bind pose
		HK_FORCE_INLINE const hkMatrix4* getWorldFromBoneTransform() const	{	return m_worldFromBoneTransforms.begin();	}

		/// Returns the bone names
		HK_FORCE_INLINE const hkStringPtr* getBoneNames() const	{	return m_boneNames.begin();	}

	protected:

		hkRefPtr<hkMeshShape> m_skin;						///< The skin we are working on
		hkArray<hkMatrix4> m_worldFromBoneTransforms;		///< The bind pose matrices
		hkArray<hkStringPtr> m_boneNames;					///< The array of bone names
};

#endif	// HK_SKIN_BINDING_H

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
