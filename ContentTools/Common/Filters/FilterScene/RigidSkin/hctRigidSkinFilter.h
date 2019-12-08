/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HAVOK_FILTER_SCENE_RIGID_SKIN_MESH__H
#define HAVOK_FILTER_SCENE_RIGID_SKIN_MESH__H

#include <ContentTools/Common/Filters/FilterScene/RigidSkin/hctRigidSkinOptions.h>

class hctRigidSkinFilter : public hctFilterInterface
{
	public: 

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_EXPORT);

		hctRigidSkinFilter( const hctFilterManagerInterface* owner );
		/*virtual*/ ~hctRigidSkinFilter();

		/*virtual*/ void setOptions(const void* optionData, int optionDataSize, unsigned int version);
		/*virtual*/ HWND showOptions(HWND owner);

		/*virtual*/ void process( class hkRootLevelContainer& data );

		/// Option ptr only valid until the filter is deleted and/or the filter dll is unloaded
		/*virtual*/ int getOptionsSize() const;
		/*virtual*/ void getOptions(void* optionData) const;

		/*virtual*/ void hideOptions();

	public: 

		HWND m_optionsDialog;
		void updateOptions();
		
		const hkRootLevelContainer* m_dialogScene;
		hctRigidSkinOptions m_options;

		// A buffer for storing the options in XML form.
		mutable hkArray<char> m_optionsBuf;
};

class hctRigidSkinFilterDesc : public hctFilterDescriptor
{
	public:

   /*virtual*/ unsigned int getID() const { return 0xDF66801E; }
		/*virtual*/ FilterCategory getCategory() const { return HK_CATEGORY_CORE; }
		/*virtual*/ FilterBehaviour getFilterBehaviour() const { return HK_DATA_MUTATES_INPLACE; }
		/*virtual*/ const char* getShortName() const { return "Rigid Skin Mesh"; }
		/*virtual*/ const char* getLongName() const { return "Alter the mesh data so that it is a skin with a single bone."; }
		/*virtual*/ unsigned int getFilterVersion() const { return HCT_FILTER_VERSION(1,0,0); }
		/*virtual*/ hctFilterInterface* createFilter(const hctFilterManagerInterface* owner) const { return new hctRigidSkinFilter(owner); }

		/*virtual*/ HavokComponentMask getRequiredHavokComponents () const { return HK_COMPONENT_COMMON; }
};

extern hctRigidSkinFilterDesc g_rigidSkinDesc;

#endif // HAVOK_FILTER_SCENE_RIGID_SKIN_MESH__H

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
