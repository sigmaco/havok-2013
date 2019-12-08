/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#ifndef	HKCD_TYPES_MANIFOLD_4
#define HKCD_TYPES_MANIFOLD_4

#include <Common/Base/DebugUtil/DeterminismUtil/hkCheckDeterminismUtil.h>

/// A manifold holding up to 4 points.
/// Note that if the number of contact points > 0, all 4 positions/distances must be initialized,
/// even if the number of contact points < 4 (in this case the first point is replicated in the last points)
struct hkcdManifold4
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE, hkcdManifold4 );

	HK_ON_DETERMINISM_CHECKS_ENABLED( hkcdManifold4() { hkString::memSet(this, 0xcd, sizeof(hkcdManifold4)); /*Deterministically set unused memory.*/ } )

	HK_FORCE_INLINE hkSimdReal getDistance( int i ) const 
	{
		// we do not use broadcast here, as i is probably not a constant and very likely hkcdManifold4 is in memory
		hkSimdReal res; res.load<1>( &m_distances(i) );	
		return res;
	}

	HK_FORCE_INLINE void flip()
	{
		m_positions[0].addMul( m_normal, m_distances.getComponent<0>() );
		m_positions[1].addMul( m_normal, m_distances.getComponent<1>() );
		m_positions[2].addMul( m_normal, m_distances.getComponent<2>() );
		m_positions[3].addMul( m_normal, m_distances.getComponent<3>() );
		m_normal.setNeg<4>( m_normal );
	}

	hkVector4 m_normal;			///< from B to A in worldspace
	hkVector4 m_positions[4];	///< on B in worldspace
	hkVector4 m_distances;		///< the distances

	/// If GSK was executed, this is the contact point position returned by GSK. This is currently used by welding.
	/// Note: the W component contains the GSK distance.
	hkVector4 m_gskPosition;
};

#endif // HKCD_TYPES_MANIFOLD_4

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
