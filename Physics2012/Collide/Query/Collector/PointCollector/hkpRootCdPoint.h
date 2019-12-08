/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_ROOT_CD_POINT_H
#define HK_ROOT_CD_POINT_H

#include <Common/Base/Types/Physics/ContactPoint/hkContactPoint.h>
#include <Physics2012/Collide/Shape/hkpShape.h>

class hkpCollidable;
	/// This class is used by the default collectors, hkpAllCdPointCollector, and hkpClosestCdPointCollector.
	/// As most of data in a hkpCdPoint is just temporary,
	/// we can only extract the root information from a hkpCdPoint.
	///
	/// If you need more detailed information, you have to implement a collector yourself.
struct hkpRootCdPoint
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_COLLIDE, hkpRootCdPoint );

	HK_FORCE_INLINE const hkContactPoint& getContact() const { return m_contact; }
	HK_FORCE_INLINE void setContact(const hkContactPoint& cp) { m_contact = cp; }
	HK_FORCE_INLINE void setContact(hkVector4Parameter pos, hkVector4Parameter norm, hkReal d) { m_contact.set(pos,norm,d); }
	HK_FORCE_INLINE void setContactDistance(hkReal d) { m_contact.setDistance(d); }
	HK_FORCE_INLINE void setContactDistance(hkSimdRealParameter d) { m_contact.setDistanceSimdReal(d); }

		/// The physical information of the contact point.
		/// Note: if this information contains cast results, then m_contact.getDistance
		/// is a fraction between 0 and 1 (and not the Euclidean distance).
	hkContactPoint m_contact;

		/// The root collidable of object A
	const hkpCollidable*	m_rootCollidableA;

		/// The shape key of the colliding shape of object A.
		/// Note: if your root collidable is a hkpMeshShape, this will be the subpart and triangle index
	hkpShapeKey m_shapeKeyA;

		/// The root collidable of object B
	const hkpCollidable*	m_rootCollidableB;

		/// The shape key of the colliding shape of object B.
		/// Note: if your root collidable is a hkpMeshShape, this will be the subpart and triangle index
	hkpShapeKey m_shapeKeyB;

		/// Comparison operator for sorting RootCdPoints
	inline hkBool operator<( const hkpRootCdPoint& b ) const;
};

#include <Physics2012/Collide/Query/Collector/PointCollector/hkpRootCdPoint.inl>

#endif //HK_ROOT_CD_POINT_H

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
