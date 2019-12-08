/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_CONSTRAINT_OWNER_H
#define HKP_CONSTRAINT_OWNER_H

#include <Common/Base/DebugUtil/MultiThreadCheck/hkMultiThreadCheck.h>
#include <Physics2012/Dynamics/Constraint/hkpConstraintInstance.h>
#include <Physics/Constraint/Data/hkpConstraintData.h>


class hkpConstraintOwner : public hkReferencedObject
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_DYNAMICS);

		inline void addConstraintInfo( hkpConstraintInstance* constraint, hkpConstraintInfo& delta )
		{
			HK_ON_DEBUG_MULTI_THREADING( checkAccessRw() );
			if ( constraint->m_internal )
			{
				m_constraintInfo.add( delta );
				constraint->m_internal->addConstraintInfo( delta );
					// we have to do this because the delta might not include the full modifier list, see HVK-3602
				m_constraintInfo.m_maxSizeOfSchema = hkMath::max2( int(m_constraintInfo.m_maxSizeOfSchema), int(constraint->m_internal->m_sizeOfSchemas) );
			}
		}

		inline void subConstraintInfo( hkpConstraintInstance* constraint, hkpConstraintInfo& delta )
		{
			HK_ON_DEBUG_MULTI_THREADING(checkAccessRw());
			if ( constraint->m_internal )
			{
				m_constraintInfo.sub( delta );
				constraint->m_internal->subConstraintInfo( delta );
			}
		}

	public:

		virtual void addConstraintToCriticalLockedIsland(      hkpConstraintInstance* constraint ) {}
		virtual void removeConstraintFromCriticalLockedIsland( hkpConstraintInstance* constraint ) {}
		virtual void addCallbackRequest( hkpConstraintInstance* constraint, int request ) {}
		
		virtual void checkAccessRw() {}

	public:
	
		hkpConstraintInfoSpu2 m_constraintInfo;
		
};


#endif // HKP_CONSTRAINT_OWNER_H

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
