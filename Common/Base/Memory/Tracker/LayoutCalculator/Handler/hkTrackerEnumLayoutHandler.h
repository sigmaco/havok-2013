/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKBASE_ENUM_LAYOUT_HANDLER_H
#define HKBASE_ENUM_LAYOUT_HANDLER_H

#include <Common/Base/Memory/Tracker/LayoutCalculator/hkTrackerLayoutCalculator.h>

// When a class contains an hkEnum instance, the Tracker reflection will not contain that member as we are not
// interested in looking for references out of hkEnum (they never have any reference).
// Nevertheless, if hkEnum is given as argument in another template class, we will encounter an hkEnum instance
// during the reference collection phase. That's why we need a handler for this template class.

class hkTrackerEnumLayoutHandler: public hkTrackerLayoutHandler
{
	public: 
		//+hk.MemoryTracker(ignore=True)
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);

		virtual void getReferences(
			hkTrackerLayoutBlock* curBlock,
			const void* curData,
			const hkTrackerTypeTreeNode* curType,
			hkTrackerLayoutCalculator* layoutCalc,
			hkArray<const hkTrackerLayoutBlock*>::Temp& newBlocks );
		virtual hk_size_t getSize(
			const hkTrackerTypeTreeNode* curType,
			hkTrackerLayoutCalculator* layoutCalc );
};

#endif // HKBASE_ENUM_LAYOUT_HANDLER_H

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
