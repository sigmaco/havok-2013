/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_AABB_CAST_COLLECTOR
#define HK_AABB_CAST_COLLECTOR

/// Structure used to collect the results of hkpBvTreeShape::castAabb queries
struct hkpAabbCastCollector
{		
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_COLLIDE, hkpAabbCastCollector);

		HK_FORCE_INLINE hkpAabbCastCollector() : m_earlyOutFraction(hkSimdReal_1) {}

		/// Called for each child shape whose aabb intersects the aabb cast
		virtual void addHit(hkpShapeKey key) = 0;

		virtual ~hkpAabbCastCollector() {}

	public:

		/// Caller queries may read this value after adding hits to optimize performance
		hkSimdReal m_earlyOutFraction;
};


#endif // HK_AABB_CAST_COLLECTOR

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
