/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#include <ContentTools/Common/Filters/FilterTutorial/hctFilterTutorial.h>

#include <ContentTools/Common/Filters/FilterTutorial/hctFilterTutorialDll.h>

#include <Common/Serialize/Util/hkBuiltinTypeRegistry.h>

// REGISTER ALL COMPLETE CLASSES
#define HK_CLASSES_FILE <ContentTools/Common/Filters/FilterTutorial/hctFilterTutorialClasses.h>
#include <Common/Base/Config/hkProductFeaturesNoPatchesOrCompat.h>
#include <Common/Base/Config/hkProductFeatures.cxx>

#include <Physics2012/Collide/Util/Welding/hkpWeldingUtility.h>
#include <Physics2012/Dynamics/World/hkpWorldCinfo.h>


// Filters we want to expose in this dll:
#include <ContentTools/Common/Filters/FilterTutorial/ConvertToPhantomAction/hctConvertToPhantomActionFilter.h>

__declspec( dllexport ) hctFilterDll* getFilterDll (HMODULE dllModule)
{
	static hctFilterTutorialDll gFilterAssetDll (dllModule);

	return &gFilterAssetDll;
}


hctFilterTutorialDll::hctFilterTutorialDll (HMODULE dllModule) : hctFilterDll (dllModule) 
{

}

/*virtual*/ int hctFilterTutorialDll::getNumberOfFilters() const
{ 
	return 1; 
}

/*virtual*/ hctFilterDescriptor* hctFilterTutorialDll::getFilterDescriptor (int index) const
{
	static hctFilterDescriptor* m_filterDescs[] = 
	{
		&g_convertToPhantomActionDesc,
	};

	return m_filterDescs[index];
}

/*virtual*/ void hctFilterTutorialDll::initDll ( const hkMemoryInitUtil::SyncInfo& baseSystemInfo, hkError* errorStream )
{
	hctFilterDll::initDll(baseSystemInfo, errorStream);

	// HVK-3632
	if (isInitialized())
	{
		hkpWorldCinfo defaults;
		hkpWeldingUtility::initWeldingTable(defaults.m_snapCollisionToConvexEdgeThreshold, defaults.m_snapCollisionToConcaveEdgeThreshold);
	}
}

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
