/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_MATH_AABB_HALF_H
#define HK_MATH_AABB_HALF_H

#include <Common/Base/Types/Geometry/Aabb/hkAabb.h>
#include <Common/Base/Math/Vector/hkIntVector.h>

struct hkAabbHalf
{
	union IntVecUnion // for strict aliasing
	{
		hkIntVector* v;
		const hkUint32*    i;
	};

	union IntUnion
	{
		const hkUint16* s;
		const hkUint32*    i;
	};

	HK_DECLARE_REFLECTION();
	HK_FORCE_INLINE	void	pack(const hkAabb& aabb)
	{
		const hkUint16		extras0 = m_extras[0];
		const hkUint16		extras1 = m_extras[1];
		hkVector4Comparison	maskMin = aabb.m_min.lessZero();
		hkVector4Comparison	maskMax = aabb.m_max.lessZero();
		IntVecUnion rdown;  rdown.i = cstRoundingD;
		IntVecUnion rup;    rup.i   = cstRoundingU;

		hkIntVector minI; minI.loadAsFloat32BitRepresentation( aabb.m_min );
		hkIntVector maxI; maxI.loadAsFloat32BitRepresentation( aabb.m_max );
		hkIntVector			iminD; iminD.setAnd(	minI, *rdown.v);
		hkIntVector			iminU; iminU.setAddU32(	minI, *rup.v);
		hkIntVector			imaxD; imaxD.setAnd(	maxI, *rdown.v);
		hkIntVector			imaxU; imaxU.setAddU32(	maxI, *rup.v);
		hkIntVector			imin; imin.setSelect(maskMin,iminU,iminD);
		hkIntVector			imax; imax.setSelect(maskMax,imaxD,imaxU);
		hkIntVector			interleaved;
		imin.setShiftRight32<16>(imin);
		imax.setAnd(imax,*rdown.v);
		interleaved.setOr(imin,imax);
		interleaved.storeNotAligned<4>((hkUint32*)m_data);
		m_extras[0] = extras0;
		m_extras[1] = extras1;
	}

	HK_FORCE_INLINE void	unpackUnaligned(hkAabb& aabb) const
	{
		IntUnion idata; idata.s = m_data;
		hkIntVector	interleaved; interleaved.loadNotAligned<4>(idata.i);
		hkIntVector zero; zero.setZero();
		IntVecUnion rdown; rdown.i = cstRoundingD;
		hkIntVector	imin; imin.setShiftLeft32<16>(interleaved); imin.setAnd(imin,*rdown.v);
		hkIntVector	imax; imax.setAnd(interleaved,*rdown.v);
		imax.storeAsFloat32BitRepresentation( aabb.m_max );
		imin.storeAsFloat32BitRepresentation( aabb.m_min );
	}

	HK_FORCE_INLINE void	unpackAligned(hkAabb& aabb) const
	{
		IntUnion idata; idata.s = m_data;
		hkIntVector	interleaved; interleaved.load<4>(idata.i);
		hkIntVector zero; zero.setZero();
		IntVecUnion rdown; rdown.i = cstRoundingD;
		hkIntVector	imin; imin.setShiftLeft32<16>(interleaved); imin.setAnd(imin,*rdown.v);
		hkIntVector	imax; imax.setAnd(interleaved,*rdown.v);
		imax.storeAsFloat32BitRepresentation( aabb.m_max );
		imin.storeAsFloat32BitRepresentation( aabb.m_min );
	}

	hkUint16	m_data[6];			///< Packed bounding box min/max.
	hkUint16	m_extras[2];		///< Extras padding data, kept intact during packing operation

	static HK_ALIGN16(const hkUint32 cstRoundingU[4]);
	static HK_ALIGN16(const hkUint32 cstRoundingD[4]);
};

#endif // HK_MATH_AABB_HALF_H

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
