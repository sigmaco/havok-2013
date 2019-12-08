/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */


#ifndef HK_AABB_16_H
#define HK_AABB_16_H

/// Aabb using 15 bit storage (highest bit cannot be used), you can use the hkIntspaceUtil to convert back and forth this class.
struct hkAabb16	
{
	public:
		//+version(0)
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CDINFO, hkAabb16 );
		HK_DECLARE_REFLECTION();

		//hkAabb16(){}

		HK_FORCE_INLINE	friend hkBool32 operator < (const hkAabb16& a, const hkAabb16& b ){ return a.m_min[0] < b.m_min[0]; }

		template<typename KeyType>
		HK_FORCE_INLINE	void setKey(KeyType key);

		HK_FORCE_INLINE	void getKey(hkUint16& key) const;

		HK_FORCE_INLINE	void getKey(hkUint32& key) const;

		HK_FORCE_INLINE	void setEmpty();

		HK_FORCE_INLINE	void set( const hkAabb16& other);

		HK_FORCE_INLINE bool isEmpty() const;

		HK_FORCE_INLINE bool isEqual(const hkAabb16& testAabb) const;
		
		HK_FORCE_INLINE void setEmptyKeyUnchanged();


		HK_FORCE_INLINE	bool isValid() const;

		HK_FORCE_INLINE	void getExtent(hkUint16 extent[3]) const;

		HK_FORCE_INLINE	hkUint16 getMajorExtent() const;

		HK_FORCE_INLINE	hkBool32 disjoint(const hkAabb16& testAabb) const;

		HK_FORCE_INLINE	hkBool32 overlaps(const hkUint16 p[3]) const;

		HK_FORCE_INLINE	hkBool32 overlaps(const hkAabb16& testAabb) const;

		HK_FORCE_INLINE	void includePoint( hkUint16 c[3] );

		HK_FORCE_INLINE	void includeAabb( const hkAabb16& in );

		/// Set this to the extent of all input aabbs.
		void setExtents( const hkAabb16* aabbsIn, int numAabbsIn );

		/// Set this to the extent of all input aabb centers, assumes that the bit 16 of the input aabbs is cleared
		void setExtentsOfCenters( const hkAabb16* aabbsIn, int numAabbsIn );

		/// Sets this to the intersection of aabb0 and aabb1.
		void setIntersection( const hkAabb16& aabb0, const hkAabb16& aabb1 );

		/// Sets this to the union of aabb0 and aabb1.
		HK_FORCE_INLINE void setUnion( const hkAabb16& aabb0, const hkAabb16& aabb1 );

		/// returns true if test AABB is fully inside this, touching the border is allowed
		HK_FORCE_INLINE	hkBool32 contains( const hkAabb16& testAabb ) const;

		/// returns true if test AABB is fully inside this and is not touching the border
		HK_FORCE_INLINE	hkBool32 containsDontTouch( const hkAabb16& testAabb ) const;

		/// returns (min+max)/2
		HK_FORCE_INLINE	void getCenter(hkUint16 c[3]) const;

		/// returns (min+max)  faster than getCenter()
		HK_FORCE_INLINE	void getCenter2(hkUint32 c[3]) const;

		/// returns (min+max)  faster than getCenter()
		HK_FORCE_INLINE	void getCenter2(hkVector4& c) const;

		/// returns (max-min)  faster than getCenter()
		HK_FORCE_INLINE	void getExtents(hkVector4& e) const;

		static HK_FORCE_INLINE hkUint32 yzDisjoint( const hkAabb16& a, const hkAabb16& b );

	public:
		hkUint16 m_min[3];
		hkUint16 m_key;
		hkUint16 m_max[3];
		hkUint16 m_key1;
};


#include <Common/Base/Types/Geometry/Aabb16/hkAabb16.inl>

#endif // HK_AABB_16_H

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
