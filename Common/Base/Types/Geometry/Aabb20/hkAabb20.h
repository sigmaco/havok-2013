/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE


#ifndef HK_AABB_20_H
#define HK_AABB_20_H

#include <Common/Base/Math/Vector/hkIntVector.h>	// needed

//typedef hkUint64 hkBoolLL;
#if defined(HK_ARCH_SUPPORTS_INT64)
	typedef hkUint64 hkBoolLL;
#else
	typedef hkBool32 hkBoolLL;
#endif 

/// Aabb using 24 16 24 bit for each component
struct hkAabb24_16_24	
{
	public:
		//+version(0)
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CDINFO, hkAabb24_16_24 );
		HK_DECLARE_REFLECTION();

		HK_FORCE_INLINE	friend bool operator < (const hkAabb24_16_24& a, const hkAabb24_16_24& b ){ return a.m_min.m_comp.m_xxxhy < b.m_min.m_comp.m_xxxhy; }

		HK_FORCE_INLINE	void setEmpty();

		HK_FORCE_INLINE	void set( const hkAabb24_16_24& other);

		HK_FORCE_INLINE bool isEmpty() const;

		HK_FORCE_INLINE bool isEqual(const hkAabb24_16_24& testAabb) const;

		HK_FORCE_INLINE	bool isValid() const;

		HK_FORCE_INLINE	hkBoolLL disjoint(const hkAabb24_16_24& testAabb) const;

		static HK_FORCE_INLINE hkBoolLL yzDisjoint( const hkAabb24_16_24& a, const hkAabb24_16_24& b );

		/// returns true if test AABB is fully inside this, touching the border is allowed
		HK_FORCE_INLINE	bool contains( const hkAabb24_16_24& testAabb ) const;


		/// returns true if test AABB is fully inside this and is not touching the border
		HK_FORCE_INLINE	bool containsDontTouch( const hkAabb24_16_24& testAabb ) const;

// 		/// Set this to the extent of all input aabbs.
// 		void setExtents( const hkAabb24_16_24* aabbsIn, int numAabbsIn );
// 
// 		/// Set this to the extent of all input aabb centers, assumes that the bit 16 of the input aabbs is cleared
// 		void setExtentsOfCenters( const hkAabb24_16_24* aabbsIn, int numAabbsIn );
// 
// 		/// Sets this to the intersection of aabb0 and aabb1.
// 		void setIntersection( const hkAabb24_16_24& aabb0, const hkAabb24_16_24& aabb1 );

	public:
		HK_FORCE_INLINE hkBoolLL disjoint_usingUint64(const hkAabb24_16_24& b) const;
#if defined(HK_INT_VECTOR_ADD64_AVAILABLE)
		HK_FORCE_INLINE hkBool32 disjoint_usingSimd2(const hkAabb24_16_24& b) const;
		HK_FORCE_INLINE hkBool32 disjoint_usingSimd4(const hkAabb24_16_24& b) const;
#endif

	public:

		union Coords
		{
			hkUint64 m_u64;
			struct 
			{
				// We use a platform specific byte ordering to allow for a very fast disjoint_usingUint64 implementation.
#if HK_ENDIAN_LITTLE	// intel
				hkUint32 m_lyzzz;
				hkUint32 m_xxxhy;
#else	// ppc
				hkUint32 m_xxxhy;
				hkUint32 m_lyzzz;
#endif
			}        m_comp;
			hkUint8  m_u8[8];
		};

		Coords m_min; //+overridetype(hkUint64)
		Coords m_max; //+overridetype(hkUint64)
};

#include <Common/Base/Types/Geometry/IntSpaceUtil/hkIntSpaceUtil.h>

struct hkAabb24_16_24_Codec: hkIntSpaceUtil
{
	void set( const hkAabb& aabb );

	HK_FORCE_INLINE void packAabb( const hkAabb& aabbF, hkAabb24_16_24* aabbOut ) const
	{
		HK_ASSERT2( 0xf03ddfe5, 0 == (0xf & hkUlong(aabbOut)), "Your output aabb is not aligned. Note: you need to align it by hand as hkAabb16 has no alignment declaration.");

		hkVector4 mi;  mi.setAdd( m_bitOffsetLow,  aabbF.m_min );
		hkVector4 ma;  ma.setAdd( m_bitOffsetHigh, aabbF.m_max );

		hkVector4 minVal; minVal.setZero();

		mi.mul( m_bitScale );
		ma.mul( m_bitScale );

		mi.setMax( minVal, mi );
		ma.setMax( minVal, ma );
		mi.setMin( m_aabb24_16_24_Max, mi );
		ma.setMin( m_aabb24_16_24_Max, ma );

		hkIntVector imx; imx.setConvertF32toS32( mi );
		hkIntVector imy; imy.setConvertF32toS32( ma );
		hkIntVector imz = imx;

#if defined( HK_REAL_IS_DOUBLE )
		#define LOCAL_TRANSPOSE3_SWAP(a,b) t = a; a = b; b = t
		hkUint32 t;
		LOCAL_TRANSPOSE3_SWAP( ((hkUint32*)&imx)[1], ((hkUint32*)&imy)[0] );
		LOCAL_TRANSPOSE3_SWAP( ((hkUint32*)&imx)[2], ((hkUint32*)&imz)[0] );
		LOCAL_TRANSPOSE3_SWAP( ((hkUint32*)&imy)[2], ((hkUint32*)&imz)[1] );
#else
		HK_TRANSPOSE3( ((hkVector4&)imx), ((hkVector4&)imy), ((hkVector4&)imz) );
#endif

		hkIntVector imyc; imyc.setSelect( m_yzIsReversed, imz, imy );
		hkIntVector imzc; imzc.setSelect( m_yzIsReversed, imy, imz );
		hkIntVector ly; ly.setShiftLeft32<24>(imyc);
		hkIntVector hy; hy.setShiftRight32<8>(imyc);
		imx.setShiftLeft32<8>(imx);
		imzc.setOr(imzc, ly);
		imx. setOr(imx, hy);

		((hkIntVector*)aabbOut)->setMergeHead32(imzc, imx);
	}

	HK_FORCE_INLINE void unpackAabbUnscaled( const hkAabb24_16_24& aabb, hkAabb* aabbFOut ) const
	{
#if defined(HK_USING_GENERIC_INT_VECTOR_IMPLEMENTATION)
		aabbFOut->m_min(0) = hkReal(aabb.m_min.m_comp.m_xxxhy>>8);
		aabbFOut->m_max(0) = hkReal(aabb.m_max.m_comp.m_xxxhy>>8);

		aabbFOut->m_min(1) = hkReal(*(const hkUint16*)&aabb.m_min.m_u8[3]);
		aabbFOut->m_max(1) = hkReal(*(const hkUint16*)&aabb.m_max.m_u8[3]);

		aabbFOut->m_min(2) = hkReal(aabb.m_min.m_comp.m_lyzzz & 0xffffff);
		aabbFOut->m_max(2) = hkReal(aabb.m_max.m_comp.m_lyzzz & 0xffffff);
		aabbFOut->m_min(3) = hkReal(0);
		aabbFOut->m_max(3) = hkReal(0);
#elif defined(HK_INT_VECTOR_NATIVE_PERMUTE8)

		static HK_ALIGN16(hkUint8 maskMin[16]) = { 0x10, 0x00, 0x01, 0x02,  0x10, 0x10, 0x03, 0x04,  0x10, 0x05, 0x06, 0x07,  0x10, 0x10, 0x10, 0x10 };
		static HK_ALIGN16(hkUint8 maskMax[16]) = { 0x10, 0x08, 0x09, 0x0a,  0x10, 0x10, 0x0b, 0x0c,  0x10, 0x0d, 0x0e, 0x0f,  0x10, 0x10, 0x10, 0x10 };
		hkIntVector zero; zero.setZero();
		hkIntVector imi; imi.setPermuteU8( (const hkIntVector&)aabb, zero, (const hkIntVector&) maskMin );
		hkIntVector ima; ima.setPermuteU8( (const hkIntVector&)aabb, zero, (const hkIntVector&) maskMax );
		imi.convertS32ToF32(aabbFOut->m_min);
		ima.convertS32ToF32(aabbFOut->m_max);
#else
		static const HK_ALIGN16( hkUint32 m_unpackMaskX[4] ) = { 0xffffff, 0, 0xffffff, 0 };
		static const HK_ALIGN16( hkUint32 m_unpackMaskY[4] ) = { 0xffff, 0, 0xffff, 0 };
		static const HK_ALIGN16( hkUint32 m_unpackMaskZ[4] ) = { 0, 0xffffff, 0, 0xffffff };

		{
			hkIntVector a; a.load<4>( (hkUint32*)(&aabb) );
#if HK_ENDIAN_LITTLE
			hkIntVector x; x.setShiftLeft128<5>( a );
			hkIntVector y; y.setShiftLeft128<3>( a );
			hkIntVector z; z.setPermutation<hkVectorPermutation::XXZZ>(a); // now we have minz minz maxz maxz
#else
			hkIntVector x; x.setPermutation<hkVectorPermutation::YXWZ>(a);
			hkIntVector y; y.setShiftRight128<3>( a );
			hkIntVector z; z.setShiftRight128<5>( a );	// now we have - minz - maxz
#endif

			y.setAnd( y, (const hkIntVector&)m_unpackMaskY );	// now we have miny - maxy -
			z.setAnd( z, (const hkIntVector&)m_unpackMaskZ );	// now we have - minz - maxz
			x.setAnd( x, (const hkIntVector&)m_unpackMaskX );	// now we have minx - maxx -

			x.setOr( x, z );								// now we have minx minz maxx maxz
			hkIntVector imi; imi.setMergeHead32( x,y );
			hkIntVector ima; ima.setMergeTail32( x,y );
			imi.convertS32ToF32(aabbFOut->m_min);
			ima.convertS32ToF32(aabbFOut->m_max);
		}
#endif
		// The next line might be correct for endian big
//		hkIntVector y; y.setShiftRight128<3>( a );
//		hkIntVector z; z.setShiftRight128<5>( a );	// now we have - minz - maxz
// 		y.setAnd( y, (const hkIntVector&)maskY );	// now we have - miny - maxy
// 
// 		z.setAnd( z, (const hkIntVector&)maskZ );
// 
// 		hkIntVector x; x.setPermutation<hkVectorPermutation::YXWZ>(a);
// 		x.setAnd( a, (const hkIntVector&)maskX );	// now we have minx - maxx -
// 
// 		x.setOr( x, y );								// now we have minx miny maxx maxy
// 		hkIntVector imi; imi.setMergeHead32( x,z );
// 		hkIntVector ima; ima.setMergeTail32( x,z );
// 		imi.convertS32ToF32(aabbFOut->m_min);
// 		ima.convertS32ToF32(aabbFOut->m_max);
	}

	hkVector4Comparison m_yzIsReversed;
	hkVector4           m_aabb24_16_24_Max;

};


#include <Common/Base/Types/Geometry/Aabb20/hkAabb20.inl>

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
