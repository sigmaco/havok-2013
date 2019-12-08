/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_INT_SPACE_UTIL_H
#define HK_INT_SPACE_UTIL_H

#include <Common/Base/Types/Geometry/Aabb/hkAabb.h>
#include <Common/Base/Types/Geometry/Aabb16/hkAabb16.h>

/// Converts a float AABB to an hkAabb16.
/// Important: assumes the hkAabb16 is aligned on a 16 byte boundary (not aligned by default)
class hkIntSpaceUtil
{
	public:
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CDINFO, hkIntSpaceUtil );

		void set( const hkAabb& aabb );

		/// Convert a floating point aabb in world space to the integer aabb.
		HK_FORCE_INLINE	void convertAabb(const hkAabb& aabbF,  hkAabb16& aabbOut) const;

		/// Convert an integer aabb into worldspace
		HK_FORCE_INLINE	void restoreAabb(const hkAabb16& aabbI, hkAabb& aabbOut) const;

		/// Move a position from worldspace into int space
		HK_FORCE_INLINE void HK_CALL transformPositionIntoIntSpace( hkVector4Parameter vecWorldSpace, hkVector4& vecIntSpaceOut ) const;

		/// Move a direcion from worldspace into int space
		HK_FORCE_INLINE void HK_CALL transformDirectionIntoIntSpace( hkVector4Parameter vecWorldSpace, hkVector4& vecIntSpaceOut ) const;

		/// Move a position from int space into worldspace 
		HK_FORCE_INLINE void HK_CALL transformPositionToWorldSpace( hkVector4Parameter vecIntSpace, hkVector4& vecWorldSpaceOut ) const;

		HK_FORCE_INLINE void convertWithOffsetLow( const hkVector4& vIn, hkUint16 vOut[3] ) const;

		/// Convert float to int, no scaling of offseting.
		/// restoreAabb = convertIntToFloatAabbIntSpace+convertIntToWorldSpace.
		HK_FORCE_INLINE static void HK_CALL convertIntToFloatAabbIntSpace( const hkAabb16& aabbI, hkAabb& aabbOut);

		/// Convert a aabbs, float to int, no scaling of offseting. This outputs 4 aabbs rotated!!!!
		/// restoreAabb = convertIntToFloatAabbIntSpace+convertIntToWorldSpace.
		HK_FORCE_INLINE static void HK_CALL convert4IntToFloatAabbIntSpaceTransposed(const hkAabb16* aabbI, hkVector4* minXYZOut, hkVector4* maxXYZOut);

		/// Convert a float aabb in int space to world space. 
		/// restoreAabb = convertIntToFloatAabbIntSpace+convertIntToWorldSpace.
		HK_FORCE_INLINE void convertIntToWorldSpace( const hkAabb& intSpaceAabb, hkAabb& worldSpaceAabbOut ) const;

	public:

		enum { AABB_UINT16_MAX_VALUE = 0x7fff };
		static const hkQuadReal s_aabb16Max;

		hkVector4 m_bitOffsetLow;
		hkVector4 m_bitOffsetHigh;
		hkVector4 m_bitScale;
		hkVector4 m_bitScaleInv;
		hkAabb m_aabb;				///< The original aabb that was set as a base for conversion.
};

#include <Common/Base/Types/Geometry/IntSpaceUtil/hkIntSpaceUtil.inl>


#endif // HK_INT_SPACE_UTIL_H

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
