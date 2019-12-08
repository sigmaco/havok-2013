/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_CONSTRAINT_CHAIN_DRAWER_H
#define HK_CONSTRAINT_CHAIN_DRAWER_H

#include <Physics/Constraint/Visualize/Drawer/hkpConstraintDrawer.h>
#include <Physics2012/Dynamics/Constraint/Chain/hkpConstraintChainData.h>

class hkpEntity;

/// Displays information about the ballSocket constraint.
class hkpConstraintChainDrawer : public hkpConstraintDrawer
{
	public:
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_VDB, hkpConstraintChainDrawer );

		void drawConstraint(const hkpConstraintChainData* constraintData, const hkTransform& localToWorldA, const hkTransform& localToWorldB, hkDebugDisplayHandler* displayHandler, int id, int tag, const hkArray<hkpEntity*>& chainedEntities);
};

#endif //HK_CONSTRAINT_CHAIN_DRAWER_H

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
