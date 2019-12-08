/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */





#if defined(HK_USING_GENERIC_INT_VECTOR_IMPLEMENTATION)


//
// Clearing, loading, and storing
//

HK_FORCE_INLINE void hkIntVector::setZero()
{
	hkUint32* HK_RESTRICT q = m_quad.u32;
	q[0] = 0;
	q[1] = 0;
	q[2] = 0;
	q[3] = 0;
}

HK_FORCE_INLINE void hkIntVector::setAll(const int& i)
{
	hkInt32* HK_RESTRICT q = reinterpret_cast<hkInt32*>(m_quad.u32);
	q[0] = i;
	q[1] = i;
	q[2] = i;
	q[3] = i;
}

HK_FORCE_INLINE void hkIntVector::setFirstComponent(int value)
{
	hkInt32* HK_RESTRICT q = reinterpret_cast<hkInt32*>(m_quad.u32);
	q[0] = value;
	q[1] = 0;
	q[2] = 0;
	q[3] = 0;
}

template <int I>
HK_FORCE_INLINE void hkIntVector::setComponent(int value)
{
	HK_INT_VECTOR_SUBINDEX_CHECK;
	hkInt32* HK_RESTRICT q = reinterpret_cast<hkInt32*>(m_quad.u32);
	q[I] = value;
}

HK_FORCE_INLINE void hkIntVector::setComponent(int I, int value)
{
	hkInt32* HK_RESTRICT q = reinterpret_cast<hkInt32*>(m_quad.u32);
	q[I] = value;
}

HK_FORCE_INLINE void hkIntVector::set(int x, int y, int z, int w)
{
	hkInt32* HK_RESTRICT q = reinterpret_cast<hkInt32*>(m_quad.u32);
	q[0] = x;
	q[1] = y;
	q[2] = z;
	q[3] = w;
}

template <int I>
HK_FORCE_INLINE int hkIntVector::getComponent() const
{
	HK_INT_VECTOR_SUBINDEX_CHECK;
	const hkInt32* HK_RESTRICT q = reinterpret_cast<const hkInt32*>(m_quad.u32);
	return q[I];
}

HK_FORCE_INLINE int hkIntVector::getComponent(int I) const
{
	HK_MATH_ASSERT(0xfabb2300, I>=0 && I<4, "int vector subindex out of range");
	const hkInt32* HK_RESTRICT q = reinterpret_cast<const hkInt32*>(m_quad.u32);
	return q[I];
}

template <int I>
HK_FORCE_INLINE hkUint8  hkIntVector::getU8 () const
{
	HK_COMPILE_TIME_ASSERT2((I>=0)&&(I<16), HK_INT_VECTOR_SUBVECTOR_INDEX_OUT_OF_RANGE);
	const hkUint8* HK_RESTRICT q = reinterpret_cast<const hkUint8*>(m_quad.u32);
	return q[I];
}

template <int I>
HK_FORCE_INLINE hkUint16 hkIntVector::getU16() const
{
	HK_COMPILE_TIME_ASSERT2((I>=0)&&(I<8), HK_INT_VECTOR_SUBVECTOR_INDEX_OUT_OF_RANGE);
	const hkUint16* HK_RESTRICT q = reinterpret_cast<const hkUint16*>(m_quad.u32);
	return q[I];
}

template <int I>
HK_FORCE_INLINE hkUint32 hkIntVector::getU32() const
{
	return getComponent<I>();
}

HK_FORCE_INLINE hkUint32 hkIntVector::getU32(int idx) const
{
	HK_MATH_ASSERT(0xfabb2300, idx>=0 && idx<4, "int vector subindex out of range");
	const hkUint32* HK_RESTRICT q = m_quad.u32;
	return q[idx];
}

//
// Logical operations
//

HK_FORCE_INLINE void hkIntVector::setNot(hkIntVectorParameter a)
{
	const hkUint32* HK_RESTRICT qa = a.m_quad.u32;
	hkUint32* HK_RESTRICT qu = m_quad.u32;
	qu[0] = ~qa[0];
	qu[1] = ~qa[1];
	qu[2] = ~qa[2];
	qu[3] = ~qa[3];
}

template <> HK_FORCE_INLINE void hkIntVector::setNegS32<4>(hkIntVectorParameter v)
{
	const hkInt32* HK_RESTRICT qa = v.m_quad.i32;
	hkInt32* HK_RESTRICT qu = m_quad.i32;
	qu[0] = -qa[0];
	qu[1] = -qa[1];
	qu[2] = -qa[2];
	qu[3] = -qa[3];
}


HK_FORCE_INLINE hkBool32 hkIntVector::isNegativeAssumingAllValuesEqual(  ) const
{
	const hkUint32* HK_RESTRICT qu = m_quad.u32;
	HK_MATH_ASSERT(0x252d00fa, qu[0] == qu[1] && qu[0] == qu[2] && qu[0] == qu[3], "assumption all values equal failed");
	return qu[0] & 0x80000000;
}

HK_FORCE_INLINE const hkVector4Comparison hkIntVector::compareLessThanS32(hkIntVectorParameter b) const
{
	const hkInt32* HK_RESTRICT sa = reinterpret_cast<const hkInt32*>(m_quad.u32);
	const hkInt32* HK_RESTRICT sb = reinterpret_cast<const hkInt32*>(b.m_quad.u32);
	hkVector4Comparison cmp;
	cmp.m_mask =(sa[0] < sb[0] ? hkVector4ComparisonMask::MASK_X : hkVector4ComparisonMask::MASK_NONE) |
					(sa[1] < sb[1] ? hkVector4ComparisonMask::MASK_Y : hkVector4ComparisonMask::MASK_NONE) |
					(sa[2] < sb[2] ? hkVector4ComparisonMask::MASK_Z : hkVector4ComparisonMask::MASK_NONE) |
					(sa[3] < sb[3] ? hkVector4ComparisonMask::MASK_W : hkVector4ComparisonMask::MASK_NONE);
	return cmp;
}

HK_FORCE_INLINE const hkVector4Comparison hkIntVector::compareEqualS32(hkIntVectorParameter b ) const
{
	const hkInt32* HK_RESTRICT sa = reinterpret_cast<const hkInt32*>(m_quad.u32);
	const hkInt32* HK_RESTRICT sb = reinterpret_cast<const hkInt32*>(b.m_quad.u32);
	hkVector4Comparison cmp;
	cmp.m_mask =(sa[0] == sb[0] ? hkVector4ComparisonMask::MASK_X : hkVector4ComparisonMask::MASK_NONE) |
				(sa[1] == sb[1] ? hkVector4ComparisonMask::MASK_Y : hkVector4ComparisonMask::MASK_NONE) |
				(sa[2] == sb[2] ? hkVector4ComparisonMask::MASK_Z : hkVector4ComparisonMask::MASK_NONE) |
				(sa[3] == sb[3] ? hkVector4ComparisonMask::MASK_W : hkVector4ComparisonMask::MASK_NONE);
	return cmp;
}

HK_FORCE_INLINE const hkVector4Comparison hkIntVector::lessZeroS32() const
{
	const hkInt32* HK_RESTRICT sa = reinterpret_cast<const hkInt32*>(m_quad.u32);
	hkVector4Comparison cmp;
	cmp.m_mask =(sa[0] < 0 ? hkVector4ComparisonMask::MASK_X : hkVector4ComparisonMask::MASK_NONE) |
				(sa[1] < 0 ? hkVector4ComparisonMask::MASK_Y : hkVector4ComparisonMask::MASK_NONE) |
				(sa[2] < 0 ? hkVector4ComparisonMask::MASK_Z : hkVector4ComparisonMask::MASK_NONE) |
				(sa[3] < 0 ? hkVector4ComparisonMask::MASK_W : hkVector4ComparisonMask::MASK_NONE);
	return cmp;
}

HK_FORCE_INLINE const hkVector4Comparison hkIntVector::equalZeroS32() const
{
	const hkInt32* HK_RESTRICT sa = reinterpret_cast<const hkInt32*>(m_quad.u32);
	hkVector4Comparison cmp;
	cmp.m_mask =(sa[0] == 0 ? hkVector4ComparisonMask::MASK_X : hkVector4ComparisonMask::MASK_NONE) |
				(sa[1] == 0 ? hkVector4ComparisonMask::MASK_Y : hkVector4ComparisonMask::MASK_NONE) |
				(sa[2] == 0 ? hkVector4ComparisonMask::MASK_Z : hkVector4ComparisonMask::MASK_NONE) |
				(sa[3] == 0 ? hkVector4ComparisonMask::MASK_W : hkVector4ComparisonMask::MASK_NONE);
	return cmp;
}

HK_FORCE_INLINE const hkVector4Comparison hkIntVector::greaterZeroS32() const
{
	const hkInt32* HK_RESTRICT sa = reinterpret_cast<const hkInt32*>(m_quad.u32);
	hkVector4Comparison cmp;
	cmp.m_mask =(sa[0] > 0 ? hkVector4ComparisonMask::MASK_X : hkVector4ComparisonMask::MASK_NONE) |
				(sa[1] > 0 ? hkVector4ComparisonMask::MASK_Y : hkVector4ComparisonMask::MASK_NONE) |
				(sa[2] > 0 ? hkVector4ComparisonMask::MASK_Z : hkVector4ComparisonMask::MASK_NONE) |
				(sa[3] > 0 ? hkVector4ComparisonMask::MASK_W : hkVector4ComparisonMask::MASK_NONE);
	return cmp;
}

HK_FORCE_INLINE const hkVector4Comparison hkIntVector::greaterEqualS32(hkIntVectorParameter b) const
{
	const hkInt32* HK_RESTRICT sa = reinterpret_cast<const hkInt32*>(m_quad.u32);
	const hkInt32* HK_RESTRICT sb = reinterpret_cast<const hkInt32*>(b.m_quad.u32);
	hkVector4Comparison cmp;
	cmp.m_mask =(sa[0] >= sb[0] ? hkVector4ComparisonMask::MASK_X : hkVector4ComparisonMask::MASK_NONE) |
				(sa[1] >= sb[1] ? hkVector4ComparisonMask::MASK_Y : hkVector4ComparisonMask::MASK_NONE) |
				(sa[2] >= sb[2] ? hkVector4ComparisonMask::MASK_Z : hkVector4ComparisonMask::MASK_NONE) |
				(sa[3] >= sb[3] ? hkVector4ComparisonMask::MASK_W : hkVector4ComparisonMask::MASK_NONE);
	return cmp;
}


HK_FORCE_INLINE void hkIntVector::setOr(hkIntVectorParameter a, hkIntVectorParameter b)
{
	const hkUint32* HK_RESTRICT qa = a.m_quad.u32;
	const hkUint32* HK_RESTRICT qb = b.m_quad.u32;
	hkUint32* HK_RESTRICT qu = m_quad.u32;
	qu[0] = qa[0] | qb[0];
	qu[1] = qa[1] | qb[1];
	qu[2] = qa[2] | qb[2];
	qu[3] = qa[3] | qb[3];
}

HK_FORCE_INLINE void hkIntVector::setAnd(hkIntVectorParameter a, hkIntVectorParameter b)
{
	const hkUint32* HK_RESTRICT qa = a.m_quad.u32;
	const hkUint32* HK_RESTRICT qb = b.m_quad.u32;
	hkUint32* HK_RESTRICT qu = m_quad.u32;
	qu[0] = qa[0] & qb[0];
	qu[1] = qa[1] & qb[1];
	qu[2] = qa[2] & qb[2];
	qu[3] = qa[3] & qb[3];
}

HK_FORCE_INLINE void hkIntVector::setXor(hkIntVectorParameter a, hkIntVectorParameter b)
{
	const hkUint32* HK_RESTRICT qa = a.m_quad.u32;
	const hkUint32* HK_RESTRICT qb = b.m_quad.u32;
	hkUint32* HK_RESTRICT qu = m_quad.u32;
	qu[0] = qa[0] ^ qb[0];
	qu[1] = qa[1] ^ qb[1];
	qu[2] = qa[2] ^ qb[2];
	qu[3] = qa[3] ^ qb[3];
}

HK_FORCE_INLINE void hkIntVector::setAndNot(hkIntVectorParameter a, hkIntVectorParameter b)
{
	const hkUint32* HK_RESTRICT qa = a.m_quad.u32;
	const hkUint32* HK_RESTRICT qb = b.m_quad.u32;
	hkUint32* HK_RESTRICT qu = m_quad.u32;
	qu[0] = qa[0] & ~qb[0];
	qu[1] = qa[1] & ~qb[1];
	qu[2] = qa[2] & ~qb[2];
	qu[3] = qa[3] & ~qb[3];
}

//
// Arithmetic operations
//

HK_FORCE_INLINE void hkIntVector::setSubU16( hkIntVectorParameter a, hkIntVectorParameter b )
{
	const hkUint16* HK_RESTRICT qa = reinterpret_cast<const hkUint16*>(a.m_quad.u32);
	const hkUint16* HK_RESTRICT qb = reinterpret_cast<const hkUint16*>(b.m_quad.u32);
	hkUint16* HK_RESTRICT qu = reinterpret_cast<hkUint16*>(m_quad.u32);
	qu[0] = qa[0] - qb[0];
	qu[1] = qa[1] - qb[1];
	qu[2] = qa[2] - qb[2];
	qu[3] = qa[3] - qb[3];
	qu[4] = qa[4] - qb[4];
	qu[5] = qa[5] - qb[5];
	qu[6] = qa[6] - qb[6];
	qu[7] = qa[7] - qb[7];
}

HK_FORCE_INLINE void hkIntVector::setAddU16( hkIntVectorParameter a, hkIntVectorParameter b )
{
	const hkUint16* HK_RESTRICT qa = reinterpret_cast<const hkUint16*>(a.m_quad.u32);
	const hkUint16* HK_RESTRICT qb = reinterpret_cast<const hkUint16*>(b.m_quad.u32);
	hkUint16* HK_RESTRICT qu = reinterpret_cast<hkUint16*>(m_quad.u32);
	qu[0] = qa[0] + qb[0];
	qu[1] = qa[1] + qb[1];
	qu[2] = qa[2] + qb[2];
	qu[3] = qa[3] + qb[3];
	qu[4] = qa[4] + qb[4];
	qu[5] = qa[5] + qb[5];
	qu[6] = qa[6] + qb[6];
	qu[7] = qa[7] + qb[7];
}

HK_FORCE_INLINE void hkIntVector::setSubU32( hkIntVectorParameter a, hkIntVectorParameter b )
{
	const hkUint32* HK_RESTRICT qa = a.m_quad.u32;
	const hkUint32* HK_RESTRICT qb = b.m_quad.u32;
	hkUint32* HK_RESTRICT qu = m_quad.u32;
	qu[0] = qa[0] - qb[0];
	qu[1] = qa[1] - qb[1];
	qu[2] = qa[2] - qb[2];
	qu[3] = qa[3] - qb[3];
}

HK_FORCE_INLINE void hkIntVector::setAddU32( hkIntVectorParameter a, hkIntVectorParameter b )
{
	const hkUint32* HK_RESTRICT qa = a.m_quad.u32;
	const hkUint32* HK_RESTRICT qb = b.m_quad.u32;
	hkUint32* HK_RESTRICT qu = m_quad.u32;
	qu[0] = qa[0] + qb[0];
	qu[1] = qa[1] + qb[1];
	qu[2] = qa[2] + qb[2];
	qu[3] = qa[3] + qb[3];
}

HK_FORCE_INLINE void hkIntVector::setSubS32( hkIntVectorParameter a, hkIntVectorParameter b )
{
	const hkInt32* HK_RESTRICT qa = a.m_quad.i32;
	const hkInt32* HK_RESTRICT qb = b.m_quad.i32;
	hkInt32* HK_RESTRICT qu = m_quad.i32;
	qu[0] = qa[0] - qb[0];
	qu[1] = qa[1] - qb[1];
	qu[2] = qa[2] - qb[2];
	qu[3] = qa[3] - qb[3];
}

HK_FORCE_INLINE void hkIntVector::setAddS32( hkIntVectorParameter a, hkIntVectorParameter b )
{
	const hkInt32* HK_RESTRICT qa = a.m_quad.i32;
	const hkInt32* HK_RESTRICT qb = b.m_quad.i32;
	hkInt32* HK_RESTRICT qu = m_quad.i32;
	qu[0] = qa[0] + qb[0];
	qu[1] = qa[1] + qb[1];
	qu[2] = qa[2] + qb[2];
	qu[3] = qa[3] + qb[3];
}

//
//	Sets this = va * vb

HK_FORCE_INLINE void hkIntVector::setMul(hkIntVectorParameter vA, hkIntVectorParameter vB)
{
	const hkInt32* HK_RESTRICT qa = vA.m_quad.i32;
	const hkInt32* HK_RESTRICT qb = vB.m_quad.i32;
	hkInt32* HK_RESTRICT qu = m_quad.i32;
	qu[0] = qa[0] * qb[0];
	qu[1] = qa[1] * qb[1];
	qu[2] = qa[2] * qb[2];
	qu[3] = qa[3] * qb[3];
}

HK_FORCE_INLINE void hkIntVector::setAddSaturateU32( hkIntVectorParameter a, hkIntVectorParameter b )
{
	const hkUint32* HK_RESTRICT qa = a.m_quad.u32;
	const hkUint32* HK_RESTRICT qb = b.m_quad.u32;
	hkUint32* HK_RESTRICT qr = m_quad.u32;
	const hkUint32 max = 0xffffffff;

	qr[0] = (qa[0] < max - qb[0]) ? (qa[0] + qb[0]) : max;
	qr[1] = (qa[1] < max - qb[1]) ? (qa[1] + qb[1]) : max;
	qr[2] = (qa[2] < max - qb[2]) ? (qa[2] + qb[2]) : max;
	qr[3] = (qa[3] < max - qb[3]) ? (qa[3] + qb[3]) : max;
}

HK_FORCE_INLINE void hkIntVector::setAddSaturateS16( hkIntVectorParameter a, hkIntVectorParameter b )
{
	const hkInt16* HK_RESTRICT qa = reinterpret_cast<const hkInt16*>(a.m_quad.u32);
	const hkInt16* HK_RESTRICT qb = reinterpret_cast<const hkInt16*>(b.m_quad.u32);
	hkInt16* HK_RESTRICT qu = reinterpret_cast<hkInt16*>(m_quad.u32);

	const int max = +32767;
	const int min = -32768;

	for(int i = 0 ; i < 8 ; i++)
	{
		qu[i] = (hkInt16)hkMath::clamp(int(qa[i]) + int(qb[i]), min, max);
	}
}

HK_FORCE_INLINE void hkIntVector::setAddSaturateU16( hkIntVectorParameter a, hkIntVectorParameter b )
{
	const hkUint16* HK_RESTRICT qa = reinterpret_cast<const hkUint16*>(a.m_quad.u32);
	const hkUint16* HK_RESTRICT qb = reinterpret_cast<const hkUint16*>(b.m_quad.u32);
	hkUint16* HK_RESTRICT qr = reinterpret_cast<hkUint16*>(m_quad.u32);
	const hkUint16 max = 0xffff;

	qr[0] = (qa[0] < max - qb[0]) ? (qa[0] + qb[0]) : max;
	qr[1] = (qa[1] < max - qb[1]) ? (qa[1] + qb[1]) : max;
	qr[2] = (qa[2] < max - qb[2]) ? (qa[2] + qb[2]) : max;
	qr[3] = (qa[3] < max - qb[3]) ? (qa[3] + qb[3]) : max;
	qr[4] = (qa[4] < max - qb[4]) ? (qa[4] + qb[4]) : max;
	qr[5] = (qa[5] < max - qb[5]) ? (qa[5] + qb[5]) : max;
	qr[6] = (qa[6] < max - qb[6]) ? (qa[6] + qb[6]) : max;
	qr[7] = (qa[7] < max - qb[7]) ? (qa[7] + qb[7]) : max;
}


HK_FORCE_INLINE void hkIntVector::setSubSaturateU32( hkIntVectorParameter a, hkIntVectorParameter b )
{
	const hkUint32* HK_RESTRICT qa = a.m_quad.u32;
	const hkUint32* HK_RESTRICT qb = b.m_quad.u32;
	hkUint32* HK_RESTRICT qr = m_quad.u32;

	qr[0] = (qa[0] > qb[0]) ? (qa[0] - qb[0]) : 0;
	qr[1] = (qa[1] > qb[1]) ? (qa[1] - qb[1]) : 0;
	qr[2] = (qa[2] > qb[2]) ? (qa[2] - qb[2]) : 0;
	qr[3] = (qa[3] > qb[3]) ? (qa[3] - qb[3]) : 0;
}

HK_FORCE_INLINE void hkIntVector::setSubSaturateS16( hkIntVectorParameter a, hkIntVectorParameter b )
{
	const hkInt16* HK_RESTRICT qa = reinterpret_cast<const hkInt16*>(a.m_quad.u32);
	const hkInt16* HK_RESTRICT qb = reinterpret_cast<const hkInt16*>(b.m_quad.u32);
	hkInt16* HK_RESTRICT qu = reinterpret_cast<hkInt16*>(m_quad.u32);

	const int min = -32768;
	const int max = +32767;

	for(int i = 0 ; i < 8 ; i++)
	{
		qu[i] = (hkInt16)hkMath::clamp(int(qa[i]) - int(qb[i]), min, max); 
	}
}

HK_FORCE_INLINE void hkIntVector::setSubSaturateU16( hkIntVectorParameter a, hkIntVectorParameter b )
{
	const hkUint16* HK_RESTRICT qa = reinterpret_cast<const hkUint16*>(a.m_quad.u32);
	const hkUint16* HK_RESTRICT qb = reinterpret_cast<const hkUint16*>(b.m_quad.u32);
	hkUint16* HK_RESTRICT qr = reinterpret_cast<hkUint16*>(m_quad.u32);

	qr[0] = (qa[0] > qb[0]) ? (qa[0] - qb[0]) : 0; 
	qr[1] = (qa[1] > qb[1]) ? (qa[1] - qb[1]) : 0; 
	qr[2] = (qa[2] > qb[2]) ? (qa[2] - qb[2]) : 0; 
	qr[3] = (qa[3] > qb[3]) ? (qa[3] - qb[3]) : 0; 
	qr[4] = (qa[4] > qb[4]) ? (qa[4] - qb[4]) : 0; 
	qr[5] = (qa[5] > qb[5]) ? (qa[5] - qb[5]) : 0; 
	qr[6] = (qa[6] > qb[6]) ? (qa[6] - qb[6]) : 0; 
	qr[7] = (qa[7] > qb[7]) ? (qa[7] - qb[7]) : 0; 
}

HK_FORCE_INLINE void hkIntVector::setMinU8( hkIntVectorParameter a, hkIntVectorParameter b )
{
	const hkUint8* HK_RESTRICT qa = reinterpret_cast<const hkUint8*>(a.m_quad.u32);
	const hkUint8* HK_RESTRICT qb = reinterpret_cast<const hkUint8*>(b.m_quad.u32);
	hkUint8* HK_RESTRICT qu = reinterpret_cast<hkUint8*>(m_quad.u32);
	
	for(int i = 0; i < 16; i++)
	{
		qu[i] = hkMath::min2(qa[i], qb[i]);  
	}
}

HK_FORCE_INLINE void hkIntVector::setMinS32( hkIntVectorParameter a, hkIntVectorParameter b )
{
	const hkInt32* HK_RESTRICT qa = reinterpret_cast<const hkInt32*>(a.m_quad.u32);
	const hkInt32* HK_RESTRICT qb = reinterpret_cast<const hkInt32*>(b.m_quad.u32);
	hkInt32* HK_RESTRICT qr = reinterpret_cast<hkInt32*>(m_quad.u32);

	qr[0] = hkMath::min2(qa[0], qb[0]);
	qr[1] = hkMath::min2(qa[1], qb[1]);
	qr[2] = hkMath::min2(qa[2], qb[2]);
	qr[3] = hkMath::min2(qa[3], qb[3]);
}

HK_FORCE_INLINE void hkIntVector::setMaxS32( hkIntVectorParameter a, hkIntVectorParameter b )
{
	const hkInt32* HK_RESTRICT qa = reinterpret_cast<const hkInt32*>(a.m_quad.u32);
	const hkInt32* HK_RESTRICT qb = reinterpret_cast<const hkInt32*>(b.m_quad.u32);
	hkInt32* HK_RESTRICT qr = reinterpret_cast<hkInt32*>(m_quad.u32);

	qr[0] = hkMath::max2(qa[0], qb[0]);
	qr[1] = hkMath::max2(qa[1], qb[1]);
	qr[2] = hkMath::max2(qa[2], qb[2]);
	qr[3] = hkMath::max2(qa[3], qb[3]);
}

HK_FORCE_INLINE void hkIntVector::setMinS16( hkIntVectorParameter a, hkIntVectorParameter b )
{
	const hkInt16* HK_RESTRICT qa = reinterpret_cast<const hkInt16*>(a.m_quad.u32);
	const hkInt16* HK_RESTRICT qb = reinterpret_cast<const hkInt16*>(b.m_quad.u32);
	hkInt16* HK_RESTRICT qr = reinterpret_cast<hkInt16*>(m_quad.u32);

	qr[0] = hkMath::min2(qa[0], qb[0]);
	qr[1] = hkMath::min2(qa[1], qb[1]);
	qr[2] = hkMath::min2(qa[2], qb[2]);
	qr[3] = hkMath::min2(qa[3], qb[3]);
	qr[0] = hkMath::min2(qa[4], qb[4]);
	qr[1] = hkMath::min2(qa[5], qb[5]);
	qr[2] = hkMath::min2(qa[6], qb[6]);
	qr[3] = hkMath::min2(qa[7], qb[7]);
}

HK_FORCE_INLINE void hkIntVector::setMaxS16( hkIntVectorParameter a, hkIntVectorParameter b )
{
	const hkInt16* HK_RESTRICT qa = reinterpret_cast<const hkInt16*>(a.m_quad.u32);
	const hkInt16* HK_RESTRICT qb = reinterpret_cast<const hkInt16*>(b.m_quad.u32);
	hkInt16* HK_RESTRICT qr = reinterpret_cast<hkInt16*>(m_quad.u32);

	qr[0] = hkMath::max2(qa[0], qb[0]);
	qr[1] = hkMath::max2(qa[1], qb[1]);
	qr[2] = hkMath::max2(qa[2], qb[2]);
	qr[3] = hkMath::max2(qa[3], qb[3]);
	qr[4] = hkMath::max2(qa[4], qb[4]);
	qr[5] = hkMath::max2(qa[5], qb[5]);
	qr[6] = hkMath::max2(qa[6], qb[6]);
	qr[7] = hkMath::max2(qa[7], qb[7]);
}

//
// Shift operations
//

template <int shift> 
HK_FORCE_INLINE void hkIntVector::setShiftLeft16( hkIntVectorParameter a)
{
	const hkUint16* HK_RESTRICT qa = reinterpret_cast<const hkUint16*>(a.m_quad.u32);
	hkUint16* HK_RESTRICT qu = reinterpret_cast<hkUint16*>(m_quad.u32);
	qu[0] = qa[0] << shift;
	qu[1] = qa[1] << shift;
	qu[2] = qa[2] << shift;
	qu[3] = qa[3] << shift;
	qu[4] = qa[4] << shift;
	qu[5] = qa[5] << shift;
	qu[6] = qa[6] << shift;
	qu[7] = qa[7] << shift;
}

template <int shift> 
HK_FORCE_INLINE void hkIntVector::setShiftRight16( hkIntVectorParameter a)
{
	const hkUint16* HK_RESTRICT qa = reinterpret_cast<const hkUint16*>(a.m_quad.u32);
	hkUint16* HK_RESTRICT qu = reinterpret_cast<hkUint16*>(m_quad.u32);
	qu[0] = qa[0] >> shift;
	qu[1] = qa[1] >> shift;
	qu[2] = qa[2] >> shift;
	qu[3] = qa[3] >> shift;
	qu[4] = qa[4] >> shift;
	qu[5] = qa[5] >> shift;
	qu[6] = qa[6] >> shift;
	qu[7] = qa[7] >> shift;
}

template <int shift> 
HK_FORCE_INLINE void hkIntVector::setShiftLeft32( hkIntVectorParameter a)
{
	const hkUint32* HK_RESTRICT qa = a.m_quad.u32;
	hkUint32* HK_RESTRICT qu = m_quad.u32;
	qu[0] = qa[0] << shift;
	qu[1] = qa[1] << shift;
	qu[2] = qa[2] << shift;
	qu[3] = qa[3] << shift;
}

template <int shift> 
HK_FORCE_INLINE void hkIntVector::setShiftRight32( hkIntVectorParameter a)
{
	const hkUint32* HK_RESTRICT qa = a.m_quad.u32;
	hkUint32* HK_RESTRICT qu = m_quad.u32;
	qu[0] = qa[0] >> shift;
	qu[1] = qa[1] >> shift;
	qu[2] = qa[2] >> shift;
	qu[3] = qa[3] >> shift;
}

template<int shift>
HK_FORCE_INLINE void hkIntVector::setShiftRightS32( hkIntVectorParameter a)
{
	const hkInt32* HK_RESTRICT qa = reinterpret_cast<const hkInt32*>(a.m_quad.u32);
	hkInt32* HK_RESTRICT qu = reinterpret_cast<hkInt32*>(m_quad.u32);
	qu[0] = qa[0] >> shift;
	qu[1] = qa[1] >> shift;
	qu[2] = qa[2] >> shift;
	qu[3] = qa[3] >> shift;
}

template<int shift>
HK_FORCE_INLINE void hkIntVector::setShiftRightS16( hkIntVectorParameter a)
{
	const hkInt16* HK_RESTRICT qa = reinterpret_cast<const hkInt16*>(a.m_quad.u32);
	hkInt16* HK_RESTRICT qu = reinterpret_cast<hkInt16*>(m_quad.u32);
	qu[0] = qa[0] >> shift;
	qu[1] = qa[1] >> shift;
	qu[2] = qa[2] >> shift;
	qu[3] = qa[3] >> shift;
	qu[4] = qa[4] >> shift;
	qu[5] = qa[5] >> shift;
	qu[6] = qa[6] >> shift;
	qu[7] = qa[7] >> shift;
}

template <int shift> 
HK_FORCE_INLINE void hkIntVector::setShiftLeft128( hkIntVectorParameter a)
{
	const hkUint8* HK_RESTRICT qa = reinterpret_cast<const hkUint8*>(a.m_quad.u32);
	hkQuadUint u;
	hkUint8* HK_RESTRICT qu = reinterpret_cast<hkUint8*>(u.u32);

	for(int j = 16 - shift ; j < 16 ; j++)
	{
		qu[j] = 0;
	}

	for(int i = 15 - shift ; i >= 0 ; i--)
	{
		qu[i] = qa[i + shift];
	}

	m_quad = u;
}

template <int shift> 
HK_FORCE_INLINE void hkIntVector::setShiftRight128( hkIntVectorParameter a)
{
	const hkUint8* HK_RESTRICT qa = reinterpret_cast<const hkUint8*>(a.m_quad.u32);
	hkQuadUint u;
	hkUint8* HK_RESTRICT qu = reinterpret_cast<hkUint8*>(u.u32);

	for(int i = 15, j = 15 - shift ; i >= shift ; i--, j--)
	{
		qu[i] = qa[j];
	}
	for(int j = shift - 1 ; j >= 0 ; j--)
	{
		qu[j] = 0;
	}

	m_quad = u;
}

//
// Merge operations
// Stick to the convention that "high" means x,y, "low" means z,w
//
HK_FORCE_INLINE void hkIntVector::setMergeHead32(hkIntVectorParameter a, hkIntVectorParameter b)
{
	const hkUint32* HK_RESTRICT qa = a.m_quad.u32;
	const hkUint32* HK_RESTRICT qb = b.m_quad.u32;
	hkQuadUint u;
	hkUint32* HK_RESTRICT qu = u.u32;

	qu[0] = qa[0]; 
	qu[1] = qb[0];
	qu[2] = qa[1];
	qu[3] = qb[1];

	m_quad = u;
}

HK_FORCE_INLINE void hkIntVector::setMergeTail32(hkIntVectorParameter a, hkIntVectorParameter b)
{
	const hkUint32* HK_RESTRICT qa = a.m_quad.u32;
	const hkUint32* HK_RESTRICT qb = b.m_quad.u32;
	hkQuadUint u;
	hkUint32* HK_RESTRICT qu = u.u32;

	qu[0] = qa[2];
	qu[1] = qb[2];
	qu[2] = qa[3];
	qu[3] = qb[3];

	m_quad = u;
}

HK_FORCE_INLINE void hkIntVector::setMergeHead16(hkIntVectorParameter a, hkIntVectorParameter b)
{
	const hkUint16* HK_RESTRICT qa = reinterpret_cast<const hkUint16*>(a.m_quad.u32);
	const hkUint16* HK_RESTRICT qb = reinterpret_cast<const hkUint16*>(b.m_quad.u32);
	hkQuadUint u;
	hkUint16* HK_RESTRICT qu = reinterpret_cast<hkUint16*>(u.u32);

	for (int i=0, j=0; i<8; i+=2, j++)
	{
		qu[i]   = qa[j];
		qu[i+1] = qb[j];
	}

	m_quad = u;
}

HK_FORCE_INLINE void hkIntVector::setMergeTail16(hkIntVectorParameter a, hkIntVectorParameter b)
{
	const hkUint16* HK_RESTRICT qa = reinterpret_cast<const hkUint16*>(a.m_quad.u32);
	const hkUint16* HK_RESTRICT qb = reinterpret_cast<const hkUint16*>(b.m_quad.u32);
	hkQuadUint u;
	hkUint16* HK_RESTRICT qu = reinterpret_cast<hkUint16*>(u.u32);

	for (int i=0, j=4; i<8; i+=2, j++)
	{
		qu[i]   = qa[j];
		qu[i+1] = qb[j];
	}

	m_quad = u;
}

HK_FORCE_INLINE void hkIntVector::setMergeHead8(hkIntVectorParameter a, hkIntVectorParameter b)
{
	const hkUint8* HK_RESTRICT qa = reinterpret_cast<const hkUint8*>(a.m_quad.u32);
	const hkUint8* HK_RESTRICT qb = reinterpret_cast<const hkUint8*>(b.m_quad.u32);
	hkQuadUint u;
	hkUint8* HK_RESTRICT qu = reinterpret_cast<hkUint8*>(u.u32);

	for (int i=0, j=0; i<16; i+=2, j++)
	{
		qu[i]   = qa[j];
		qu[i+1] = qb[j];
	}

	m_quad = u;
}

HK_FORCE_INLINE void hkIntVector::setMergeTail8(hkIntVectorParameter a, hkIntVectorParameter b)
{
	const hkUint8* HK_RESTRICT qa = reinterpret_cast<const hkUint8*>(a.m_quad.u32);
	const hkUint8* HK_RESTRICT qb = reinterpret_cast<const hkUint8*>(b.m_quad.u32);
	hkQuadUint u;
	hkUint8* HK_RESTRICT qu = reinterpret_cast<hkUint8*>(u.u32);

	for (int i=0, j=8; i<16; i+=2, j++)
	{
		qu[i]   = qa[j];
		qu[i+1] = qb[j];
	}

	m_quad = u;
}


//
// Pack operations
//
HK_FORCE_INLINE void hkIntVector::setConvertU32ToU16( hkIntVectorParameter a, hkIntVectorParameter b )
{
	const hkUint32* HK_RESTRICT qa = a.m_quad.u32;
	const hkUint32* HK_RESTRICT qb = b.m_quad.u32;
	hkQuadUint u;
	hkUint16* HK_RESTRICT qu = reinterpret_cast<hkUint16*>(u.u32);

	qu[0] = (hkUint16)qa[0];
	qu[1] = (hkUint16)qa[1];
	qu[2] = (hkUint16)qa[2];
	qu[3] = (hkUint16)qa[3];
	qu[4] = (hkUint16)qb[0];
	qu[5] = (hkUint16)qb[1];
	qu[6] = (hkUint16)qb[2];
	qu[7] = (hkUint16)qb[3];

	m_quad = u;
}

HK_FORCE_INLINE void hkIntVector::setConvertSaturateS32ToU16( hkIntVectorParameter a, hkIntVectorParameter b )
{
	const hkInt32* HK_RESTRICT qa = reinterpret_cast<const hkInt32*>(a.m_quad.u32);
	const hkInt32* HK_RESTRICT qb = reinterpret_cast<const hkInt32*>(b.m_quad.u32);
	hkQuadUint u;
	hkUint16* HK_RESTRICT qu = reinterpret_cast<hkUint16*>(u.u32);

	const hkInt32 min = 0;
	const hkInt32 max = 0xffff; 

	for (int i=0; i<4; ++i)
	{
		qu[i]   = (hkUint16)hkMath::clamp(qa[i], min, max);
		qu[i+4] = (hkUint16)hkMath::clamp(qb[i], min, max);
	}

	m_quad = u;
}

HK_FORCE_INLINE void hkIntVector::setConvertSaturateS32ToS16( hkIntVectorParameter a, hkIntVectorParameter b )
{
	const hkInt32* HK_RESTRICT qa = reinterpret_cast<const hkInt32*>(a.m_quad.u32);
	const hkInt32* HK_RESTRICT qb = reinterpret_cast<const hkInt32*>(b.m_quad.u32);
	hkQuadUint u;
	hkInt16* HK_RESTRICT qu = reinterpret_cast<hkInt16*>(u.u32);

	const hkInt32 min = 0xffff8000;
	const hkInt32 max = 0x7fff; 

	for (int i=0; i<4; ++i)
	{
		qu[i]   = (hkInt16)hkMath::clamp(qa[i], min, max);
		qu[i+4] = (hkInt16)hkMath::clamp(qb[i], min, max);
	}

	m_quad = u;
}

HK_FORCE_INLINE void hkIntVector::setConvertSaturateS16ToU8( hkIntVectorParameter a, hkIntVectorParameter b )
{
	const hkInt16* HK_RESTRICT qa = reinterpret_cast<const hkInt16*>(a.m_quad.u32);
	const hkInt16* HK_RESTRICT qb = reinterpret_cast<const hkInt16*>(b.m_quad.u32);
	hkQuadUint u;
	hkUint8* HK_RESTRICT qu = reinterpret_cast<hkUint8*>(u.u32);

	const hkInt16 min = 0;
	const hkInt16 max = 255;

	for (int i=0; i<8; ++i)
	{
		qu[i]   = (hkUint8)hkMath::clamp(qa[i], min, max);
		qu[i+8] = (hkUint8)hkMath::clamp(qb[i], min, max);
	}

	m_quad = u;
}

//
//	Sets this.u32[i] = (unsigned int)a.u16[i]

HK_FORCE_INLINE void hkIntVector::setConvertLowerU16ToU32(hkIntVectorParameter a)
{
	const hkUint16* HK_RESTRICT qa = reinterpret_cast<const hkUint16*>(a.m_quad.u32);
	hkQuadUint u;
	hkUint32* HK_RESTRICT qu = u.u32;
	qu[0] = (hkUint32)qa[0];
	qu[1] = (hkUint32)qa[1];
	qu[2] = (hkUint32)qa[2];
	qu[3] = (hkUint32)qa[3];
	m_quad = u;
}

//
//	Sets this.u32[i] = (unsigned int)a.u16[i + 4]

HK_FORCE_INLINE void hkIntVector::setConvertUpperU16ToU32(hkIntVectorParameter a)
{
	const hkUint16* HK_RESTRICT qa = reinterpret_cast<const hkUint16*>(a.m_quad.u32);
	hkQuadUint u;
	hkUint32* HK_RESTRICT qu = u.u32;
	qu[0] = (hkUint32)qa[4];
	qu[1] = (hkUint32)qa[5];
	qu[2] = (hkUint32)qa[6];
	qu[3] = (hkUint32)qa[7];
	m_quad = u;
}

//
// Shuffle
//
template <hkVectorPermutation::Permutation P> 
HK_FORCE_INLINE void hkIntVector::setPermutation(hkIntVectorParameter v)
{
	const hkUint32* HK_RESTRICT qa = v.m_quad.u32;
	hkQuadUint u;
	hkUint32* HK_RESTRICT qu = u.u32;
	qu[0] = qa[(P & 0x3000) >> 12];
	qu[1] = qa[(P & 0x0300) >>  8];
	qu[2] = qa[(P & 0x0030) >>  4];
	qu[3] = qa[(P & 0x0003) >>  0];
	m_quad = u;
}

HK_FORCE_INLINE void hkIntVector::setPermuteU8(hkIntVectorParameter aIn, hkIntVectorParameter mask)
{
	const hkUint8* HK_RESTRICT m = reinterpret_cast<const hkUint8*>(mask.m_quad.u32);
	const hkUint8* HK_RESTRICT a = reinterpret_cast<const hkUint8*>(aIn.m_quad.u32);
	hkQuadUint u;
	hkUint8* HK_RESTRICT r = reinterpret_cast<hkUint8*>(u.u32);
	for (int i = 0; i < 16; i++)
	{
		HK_MATH_ASSERT(0xf820d0c2, (m[i] & 0xF0)==0, "upper 4 bits not zero");
		r[i] = a[m[i]];
	}
	m_quad = u;
}

HK_FORCE_INLINE void hkIntVector::setPermuteU8(hkIntVectorParameter aIn, hkIntVectorParameter bIn, hkIntVectorParameter mask)
{
	const hkUint8* HK_RESTRICT m = reinterpret_cast<const hkUint8*>(mask.m_quad.u32);
	const hkUint8* HK_RESTRICT a = reinterpret_cast<const hkUint8*>(aIn.m_quad.u32);
	const hkUint8* HK_RESTRICT b = reinterpret_cast<const hkUint8*>(bIn.m_quad.u32);
	hkQuadUint u;
	hkUint8* HK_RESTRICT r = reinterpret_cast<hkUint8*>(u.u32);
	for (int i = 0; i < 16; i++)
	{
		if (m[i] & 0xF0)
		{
			r[i] = b[m[i] & 0x0F];
		}
		else
		{
			r[i] = a[m[i] & 0x0F];
		}
	}
	m_quad = u;
}

//
// Splat
//
template <int VALUE> 
HK_FORCE_INLINE void hkIntVector::splatImmediate32()
{
	HK_INT_VECTOR_IMM_SPLAT_VALUE_CHECK;
	hkInt32* HK_RESTRICT qu = reinterpret_cast<hkInt32*>(m_quad.u32);
	qu[0] = VALUE;
	qu[1] = VALUE;
	qu[2] = VALUE;
	qu[3] = VALUE;
}

template <int VALUE> 
HK_FORCE_INLINE void hkIntVector::splatImmediate16()
{
	HK_INT_VECTOR_IMM_SPLAT_VALUE_CHECK;
	hkUint16* HK_RESTRICT qu = reinterpret_cast<hkUint16*>(m_quad.u32);
	qu[0] = (hkUint16) VALUE;
	qu[1] = (hkUint16) VALUE;
	qu[2] = (hkUint16) VALUE;
	qu[3] = (hkUint16) VALUE;
	qu[4] = (hkUint16) VALUE;
	qu[5] = (hkUint16) VALUE;
	qu[6] = (hkUint16) VALUE;
	qu[7] = (hkUint16) VALUE;
}

template <int VALUE> 
HK_FORCE_INLINE void hkIntVector::splatImmediate8()
{
	HK_INT_VECTOR_IMM_SPLAT_VALUE_CHECK;
	hkUint8* HK_RESTRICT qu = reinterpret_cast<hkUint8*>(m_quad.u32);
	for (int i=0; i<16; i++)
	{
		qu[i] = (hkUint8) VALUE;
	}
}

template <int I> 
HK_FORCE_INLINE void hkIntVector::setBroadcast(hkIntVectorParameter a)
{
	HK_INT_VECTOR_SUBINDEX_CHECK;
	const hkUint32* HK_RESTRICT qa = a.m_quad.u32;
	hkUint32* HK_RESTRICT qu = m_quad.u32;
	hkUint32 value = qa[I];
	qu[0] = value;
	qu[1] = value;
	qu[2] = value;
	qu[3] = value;
}

template<int I>
HK_FORCE_INLINE void hkIntVector::setBroadcast8(hkIntVectorParameter a)
{
	const hkUint8* HK_RESTRICT qa = reinterpret_cast<const hkUint8*>(a.m_quad.u32);
	hkUint8* HK_RESTRICT qu = reinterpret_cast<hkUint8*>(m_quad.u32);
	hkUint8 value = qa[I];

	qu[0] = value;
	qu[1] = value;
	qu[2] = value;
	qu[3] = value;
	qu[4] = value;
	qu[5] = value;
	qu[6] = value;
	qu[7] = value;
	qu[8] = value;
	qu[9] = value;
	qu[10] = value;
	qu[11] = value;
	qu[12] = value;
	qu[13] = value;
	qu[14] = value;
	qu[15] = value;
}

template<int I>
HK_FORCE_INLINE void hkIntVector::setBroadcast16(hkIntVectorParameter a)
{
	const hkUint16* HK_RESTRICT qa = reinterpret_cast<const hkUint16*>(a.m_quad.u32);
	hkUint16* HK_RESTRICT qu = reinterpret_cast<hkUint16*>(m_quad.u32);
	hkUint16 value = qa[I];

	qu[0] = value;
	qu[1] = value;
	qu[2] = value;
	qu[3] = value;
	qu[4] = value;
	qu[5] = value;
	qu[6] = value;
	qu[7] = value;
}

template <> HK_FORCE_INLINE int hkIntVector::horizontalMinS32<1>() const
{
	return getComponent<0>();
}

template <> HK_FORCE_INLINE int hkIntVector::horizontalMinS32<2>() const
{
	const hkInt32* HK_RESTRICT qa = m_quad.i32;
	return hkMath::min2(qa[0], qa[1]);
}

template <> HK_FORCE_INLINE int hkIntVector::horizontalMinS32<3>() const
{
	const hkInt32* HK_RESTRICT qa = m_quad.i32;
	const hkInt32 xy = hkMath::min2(qa[0], qa[1]);
	return hkMath::min2(xy, qa[2]);
}

template <> HK_FORCE_INLINE int hkIntVector::horizontalMinS32<4>() const
{
	const hkInt32* HK_RESTRICT qa = m_quad.i32;
	const hkInt32 xy = hkMath::min2(qa[0], qa[1]);
	const hkInt32 zw = hkMath::min2(qa[2], qa[3]);
	return hkMath::min2(xy, zw);
}

template <int N> HK_FORCE_INLINE int hkIntVector::horizontalMinS32() const
{
	HK_INT_VECTOR_NOT_IMPLEMENTED;
	return 0;
}

template <> HK_FORCE_INLINE int hkIntVector::horizontalMaxS32<1>() const
{
	return getComponent<0>();
}

template <> HK_FORCE_INLINE int hkIntVector::horizontalMaxS32<2>() const
{
	const hkInt32* HK_RESTRICT qa = m_quad.i32;
	return hkMath::max2(qa[0], qa[1]);
}

template <> HK_FORCE_INLINE int hkIntVector::horizontalMaxS32<3>() const
{
	const hkInt32* HK_RESTRICT qa = m_quad.i32;
	const hkInt32 xy = hkMath::max2(qa[0], qa[1]);
	return hkMath::max2(xy, qa[2]);
}

template <> HK_FORCE_INLINE int hkIntVector::horizontalMaxS32<4>() const
{
	const hkInt32* HK_RESTRICT qa = m_quad.i32;
	const hkInt32 xy = hkMath::max2(qa[0], qa[1]);
	const hkInt32 zw = hkMath::max2(qa[2], qa[3]);
	return hkMath::max2(xy, zw);
}

//
//	Returns the sum of the first N components

template <> HK_FORCE_INLINE int hkIntVector::horizontalAddS32<1>() const
{
	return getComponent<0>();
}

template <> HK_FORCE_INLINE int hkIntVector::horizontalAddS32<2>() const
{
	const hkInt32* HK_RESTRICT qa = m_quad.i32;
	return (qa[0] + qa[1]);
}

template <> HK_FORCE_INLINE int hkIntVector::horizontalAddS32<3>() const
{
	const hkInt32* HK_RESTRICT qa = m_quad.i32;
	return (qa[0] + qa[1] + qa[2]);
}

template <> HK_FORCE_INLINE int hkIntVector::horizontalAddS32<4>() const
{
	const hkInt32* HK_RESTRICT qa = m_quad.i32;
	return (qa[0] + qa[1] + qa[2] + qa[3]);
}

//
//	Returns the xor of the first N components

template <> HK_FORCE_INLINE int hkIntVector::horizontalXorS32<1>() const
{
	return getComponent<0>();
}

template <> HK_FORCE_INLINE int hkIntVector::horizontalXorS32<2>() const
{
	const hkInt32* HK_RESTRICT qa = m_quad.i32;
	return (qa[0] ^ qa[1]);
}

template <> HK_FORCE_INLINE int hkIntVector::horizontalXorS32<3>() const
{
	const hkInt32* HK_RESTRICT qa = m_quad.i32;
	return (qa[0] ^ qa[1] ^ qa[2]);
}

template <> HK_FORCE_INLINE int hkIntVector::horizontalXorS32<4>() const
{
	const hkInt32* HK_RESTRICT qa = m_quad.i32;
	return (qa[0] ^ qa[1] ^ qa[2] ^ qa[3]);
}

template <int N> HK_FORCE_INLINE int hkIntVector::horizontalXorS32() const
{
	HK_INT_VECTOR_NOT_IMPLEMENTED;
	return 0;
}

//
//	Returns the dot product of the first N components

template <> HK_FORCE_INLINE hkInt64 hkIntVector::dot<1>(hkIntVectorParameter v) const
{
	const hkInt32* HK_RESTRICT qa = m_quad.i32;
	const hkInt32* HK_RESTRICT qb = v.m_quad.i32;
	return	((hkInt64)qa[0]) * ((hkInt64)qb[0]);
}

template <> HK_FORCE_INLINE hkInt64 hkIntVector::dot<2>(hkIntVectorParameter v) const
{
	const hkInt32* HK_RESTRICT qa = m_quad.i32;
	const hkInt32* HK_RESTRICT qb = v.m_quad.i32;
	return ((hkInt64)qa[0]) * ((hkInt64)qb[0]) + ((hkInt64)qa[1]) * ((hkInt64)qb[1]);
}

template <> HK_FORCE_INLINE hkInt64 hkIntVector::dot<3>(hkIntVectorParameter v) const
{
	const hkInt32* HK_RESTRICT qa = m_quad.i32;
	const hkInt32* HK_RESTRICT qb = v.m_quad.i32;
	return ((hkInt64)qa[0]) * ((hkInt64)qb[0]) + ((hkInt64)qa[1]) * ((hkInt64)qb[1]) + ((hkInt64)qa[2]) * ((hkInt64)qb[2]);
}

template <> HK_FORCE_INLINE hkInt64 hkIntVector::dot<4>(hkIntVectorParameter v) const
{
	const hkInt32* HK_RESTRICT qa = m_quad.i32;
	const hkInt32* HK_RESTRICT qb = v.m_quad.i32;
	return ((hkInt64)qa[0]) * ((hkInt64)qb[0]) + ((hkInt64)qa[1]) * ((hkInt64)qb[1]) + ((hkInt64)qa[2]) * ((hkInt64)qb[2]) + ((hkInt64)qa[3]) * ((hkInt64)qb[3]);
}

template <int N> HK_FORCE_INLINE hkInt64 hkIntVector::dot(hkIntVectorParameter v) const
{
	HK_INT_VECTOR_NOT_IMPLEMENTED;
	return 0;
}

HK_FORCE_INLINE void hkIntVector::setShiftLeft32( hkIntVectorParameter a, int shift)
{
	hkQuadUintUnion qu, qa;
	qa.q = a.m_quad;

	qu.u[0] = qa.u[0] << shift;
	qu.u[1] = qa.u[1] << shift;
	qu.u[2] = qa.u[2] << shift;
	qu.u[3] = qa.u[3] << shift;

	m_quad = qu.q;
}

HK_FORCE_INLINE void hkIntVector::setShiftRight32( hkIntVectorParameter a, int shift)
{
	hkQuadUintUnion qu, qa;
	qa.q = a.m_quad;

	qu.u[0] = qa.u[0] >> shift;
	qu.u[1] = qa.u[1] >> shift;
	qu.u[2] = qa.u[2] >> shift;
	qu.u[3] = qa.u[3] >> shift;

	m_quad = qu.q;
}

//
// int <-> float conversion
//
HK_FORCE_INLINE void hkIntVector::convertU32ToF32(hkVector4f& vOut) const
{
	const hkUint32* HK_RESTRICT qu = m_quad.u32;
	vOut.set( hkFloat32(qu[0]), hkFloat32(qu[1]), hkFloat32(qu[2]), hkFloat32(qu[3]));
}

HK_FORCE_INLINE void hkIntVector::convertU32ToF32(hkVector4d& vOut) const
{
	const hkUint32* HK_RESTRICT qu = m_quad.u32;
	vOut.set( hkDouble64(qu[0]), hkDouble64(qu[1]), hkDouble64(qu[2]), hkDouble64(qu[3]));
}

HK_FORCE_INLINE void hkIntVector::convertS32ToF32(hkVector4f& vOut) const
{
	const hkInt32* HK_RESTRICT qu = reinterpret_cast<const hkInt32*>(m_quad.u32);
	vOut.set( hkFloat32(qu[0]), hkFloat32(qu[1]), hkFloat32(qu[2]), hkFloat32(qu[3]));
}

HK_FORCE_INLINE void hkIntVector::convertS32ToF32(hkVector4d& vOut) const
{
	const hkInt32* HK_RESTRICT qu = reinterpret_cast<const hkInt32*>(m_quad.u32);
	vOut.set( hkDouble64(qu[0]), hkDouble64(qu[1]), hkDouble64(qu[2]), hkDouble64(qu[3]));
}

namespace
{
	HK_FORCE_INLINE hkUint32 __f32_u32(hkFloat32 a)
	{
		union F32U32
		{
			hkFloat32 m_asF32;
			hkUint32 m_asU32;
		};

		F32U32 value; value.m_asF32 = a;
		const hkUint32 biasedExponent = (value.m_asU32 & 0x7F800000) >> 23; 
		const int exponent = (hkInt32)biasedExponent - 127;

		// Clip negative and fractional numbers
		if (exponent < 0 || (value.m_asU32 & 0x80000000)) 
		{
			return 0;
		}

		// Obtain mantissa and shift it according to the exponent
		hkUint32 mantissa = (value.m_asU32 & 0x007FFFFF) | 0x00800000;	
		if (exponent <= 23)
		{
			mantissa >>= (23 - exponent);
		}
		else
		{		
			if (exponent < 32)
			{
				mantissa <<= (exponent - 23);
			}

			// Saturate values over 2^32 - 1
			else
			{
				mantissa = 0xFFFFFFFF;
			}
		}

		return mantissa;
	}
}

HK_FORCE_INLINE void hkIntVector::setConvertF32toU32(hkVector4fParameter vIn)
{
	hkUint32* HK_RESTRICT qu = m_quad.u32;
	qu[0] = __f32_u32( hkFloat32(vIn(0)) );
	qu[1] = __f32_u32( hkFloat32(vIn(1)) );
	qu[2] = __f32_u32( hkFloat32(vIn(2)) );
	qu[3] = __f32_u32( hkFloat32(vIn(3)) );
}

HK_FORCE_INLINE void hkIntVector::setConvertF32toU32(hkVector4dParameter vIn)
{
	hkUint32* HK_RESTRICT qu = m_quad.u32;
	qu[0] = __f32_u32( hkFloat32(vIn(0)) );
	qu[1] = __f32_u32( hkFloat32(vIn(1)) );
	qu[2] = __f32_u32( hkFloat32(vIn(2)) );
	qu[3] = __f32_u32( hkFloat32(vIn(3)) );
}

HK_FORCE_INLINE void hkIntVector::setConvertF32toS32(hkVector4fParameter vIn)
{
	hkInt32* HK_RESTRICT qu = reinterpret_cast<hkInt32*>(m_quad.u32);
	qu[0] = hkMath::hkToIntFast( vIn(0) );
	qu[1] = hkMath::hkToIntFast( vIn(1) );
	qu[2] = hkMath::hkToIntFast( vIn(2) );
	qu[3] = hkMath::hkToIntFast( vIn(3) );
}

HK_FORCE_INLINE void hkIntVector::setConvertF32toS32(hkVector4dParameter vIn)
{
	hkInt32* HK_RESTRICT qu = reinterpret_cast<hkInt32*>(m_quad.u32);
	qu[0] = hkMath::hkToIntFast( vIn(0) );
	qu[1] = hkMath::hkToIntFast( vIn(1) );
	qu[2] = hkMath::hkToIntFast( vIn(2) );
	qu[3] = hkMath::hkToIntFast( vIn(3) );
}

template <int N>
HK_FORCE_INLINE void hkIntVector::loadNotAligned(const hkUint32* p)
{
	HK_INT_VECTOR_UNSUPPORTED_LENGTH_CHECK;
	hkMemUtil::memCpy<sizeof(hkUint32)>(&m_quad, p, N*sizeof(hkUint32));
	HK_ON_DEBUG( { for(int i=N; i<4; ++i) m_quad.u32[i] = 0xffffffff; } );
}

template <int N>
HK_FORCE_INLINE void hkIntVector::storeNotAligned(hkUint32* p) const
{
	HK_INT_VECTOR_UNSUPPORTED_LENGTH_CHECK;
	hkMemUtil::memCpy<sizeof(hkUint32)>(p, &m_quad, N*sizeof(hkUint32));
}

template <>
HK_FORCE_INLINE void hkIntVector::load<4>(const hkUint32* p)
{
#if !defined(HK_PLATFORM_CTR) && !defined(HK_PLATFORM_ANDROID)  && !(defined(HK_PLATFORM_IOS) && (HK_CONFIG_SIMD != HK_CONFIG_SIMD_ENABLED)) && !defined(HK_ALIGN_RELAX_CHECKS)
	HK_MATH_ASSERT(0x70aae483, ((hkUlong)p & 0xf) == 0, "pointer for hkIntVector::load<4> must be 16-byte aligned");
#endif
	hkMemUtil::memCpyOneAligned<4*sizeof(hkUint32), 16>(&m_quad, p);
}

template <int N>
HK_FORCE_INLINE void hkIntVector::load(const hkUint32* p)
{
#if !defined(HK_PLATFORM_CTR) && !(defined(HK_PLATFORM_IOS) && HK_CONFIG_SIMD != HK_CONFIG_SIMD_ENABLED) && !defined(HK_ALIGN_RELAX_CHECKS)
	HK_MATH_ASSERT(0x70aae483, ( ((hkUlong)p) & ((sizeof(hkUint32)*(N!=3?N:4))-1) ) == 0, "p must be aligned.");
#endif
	loadNotAligned<N>(p);
}

//
//	Store to an aligned address

template <>
HK_FORCE_INLINE void hkIntVector::store<4>(hkUint32* p) const
{
#if !defined(HK_PLATFORM_CTR) && !(defined(HK_PLATFORM_IOS) && (HK_CONFIG_SIMD != HK_CONFIG_SIMD_ENABLED)) && !defined(HK_ALIGN_RELAX_CHECKS)
	HK_MATH_ASSERT(0x70aae483, ((hkUlong)p & 0xf) == 0, "pointer for hkIntVector::store<4> must be 16-byte aligned");
#endif
	hkMemUtil::memCpyOneAligned<4*sizeof(hkUint32), 16>(p, &m_quad);
}

template <int N>
HK_FORCE_INLINE void hkIntVector::store(hkUint32* p) const
{
#if !defined(HK_PLATFORM_CTR) && !(defined(HK_PLATFORM_IOS) && HK_CONFIG_SIMD != HK_CONFIG_SIMD_ENABLED) && !defined(HK_ALIGN_RELAX_CHECKS)
	HK_MATH_ASSERT(0x70aae483, ( ((hkUlong)p) & ((sizeof(hkUint32)*(N!=3?N:4))-1) ) == 0, "p must be aligned.");
#endif
	storeNotAligned<N>(p);
}


//
//	Assuming that this = (i0, i1, i2, i3) and v = (v0, v1, v2, v3), the function will set this = (ik, ik, ik, ik)
//	where k ={0,..., 3} such that vk = max{v0, v1, v2, v3}.

HK_FORCE_INLINE void hkIntVector::broadcastComponentAtVectorMax(hkVector4fParameter v)
{
	setAll(getComponentAtVectorMax(v));
}

HK_FORCE_INLINE void hkIntVector::broadcastComponentAtVectorMax(hkVector4dParameter v)
{
	setAll(getComponentAtVectorMax(v));
}

/// Assuming that this = (i0, i1, i2, i3) and v = (v0, v1, v2, v3), the function will return ik
/// where k in {0,..., 3} such that vk = max{v0, v1, v2, v3}.

HK_FORCE_INLINE int hkIntVector::getComponentAtVectorMax(hkVector4fParameter v) const
{
	const hkInt32* HK_RESTRICT qu = reinterpret_cast<const hkInt32*>(m_quad.u32);

	const int vmax = v.getIndexOfMaxComponent<4>();

	return qu[vmax];
}

HK_FORCE_INLINE int hkIntVector::getComponentAtVectorMax(hkVector4dParameter v) const
{
	const hkInt32* HK_RESTRICT qu = reinterpret_cast<const hkInt32*>(m_quad.u32);

	const int vmax = v.getIndexOfMaxComponent<4>();

	return qu[vmax];
}

HK_FORCE_INLINE void hkIntVector::setSelect(hkVector4fComparisonParameter selectMask, hkIntVectorParameter trueValue, hkIntVectorParameter falseValue)
{
	const hkUint32* HK_RESTRICT qt = trueValue.m_quad.u32;
	const hkUint32* HK_RESTRICT qf = falseValue.m_quad.u32;
	hkUint32* HK_RESTRICT qu = m_quad.u32;

	qu[0] = selectMask.anyIsSet<hkVector4ComparisonMask::MASK_X>() ? qt[0] : qf[0];
	qu[1] = selectMask.anyIsSet<hkVector4ComparisonMask::MASK_Y>() ? qt[1] : qf[1];
	qu[2] = selectMask.anyIsSet<hkVector4ComparisonMask::MASK_Z>() ? qt[2] : qf[2];
	qu[3] = selectMask.anyIsSet<hkVector4ComparisonMask::MASK_W>() ? qt[3] : qf[3];
}

HK_FORCE_INLINE void hkIntVector::setSelect(hkVector4dComparisonParameter selectMask, hkIntVectorParameter trueValue, hkIntVectorParameter falseValue)
{
	const hkUint32* HK_RESTRICT qt = trueValue.m_quad.u32;
	const hkUint32* HK_RESTRICT qf = falseValue.m_quad.u32;
	hkUint32* HK_RESTRICT qu = m_quad.u32;

	qu[0] = selectMask.anyIsSet<hkVector4ComparisonMask::MASK_X>() ? qt[0] : qf[0];
	qu[1] = selectMask.anyIsSet<hkVector4ComparisonMask::MASK_Y>() ? qt[1] : qf[1];
	qu[2] = selectMask.anyIsSet<hkVector4ComparisonMask::MASK_Z>() ? qt[2] : qf[2];
	qu[3] = selectMask.anyIsSet<hkVector4ComparisonMask::MASK_W>() ? qt[3] : qf[3];
}

template<hkVector4ComparisonMask::Mask M> 
HK_FORCE_INLINE void hkIntVector::setSelect( hkIntVectorParameter trueValue, hkIntVectorParameter falseValue )
{
	const hkUint32* HK_RESTRICT qt = trueValue.m_quad.u32;
	const hkUint32* HK_RESTRICT qf = falseValue.m_quad.u32;
	hkUint32* HK_RESTRICT qu = m_quad.u32;

	qu[0] = (M & hkVector4ComparisonMask::MASK_X) ? qt[0] : qf[0];
	qu[1] = (M & hkVector4ComparisonMask::MASK_Y) ? qt[1] : qf[1];
	qu[2] = (M & hkVector4ComparisonMask::MASK_Z) ? qt[2] : qf[2];
	qu[3] = (M & hkVector4ComparisonMask::MASK_W) ? qt[3] : qf[3];
}


template <hkIntVectorConstant vectorConstant>
HK_FORCE_INLINE /*static*/ const hkIntVector& HK_CALL hkIntVector::getConstant()
{
	return *(const hkIntVector*) (g_intVectorConstants + vectorConstant);
}

HK_FORCE_INLINE /*static*/ const hkIntVector& HK_CALL hkIntVector::getConstant(hkIntVectorConstant constant)
{
	return *(const hkIntVector*) (g_intVectorConstants + constant);
}

// result.u32[i] = highshorts.u16[i]<<16 + lowShorts.u16[i]. highShorts.u16/lowShorts.u16[4..7] are ignored
HK_FORCE_INLINE void hkIntVector::setCombineHead16To32( hkIntVectorParameter highShorts, hkIntVectorParameter lowShorts )
{
#if HK_ENDIAN_BIG
	setMergeHead16(highShorts, lowShorts);
#else
	setMergeHead16(lowShorts, highShorts);
#endif
}

// result.u32[i] = highshorts.u16[4+i]<<16 + lowShorts.u16[4+i]. highShorts.u16/lowShorts.u16[0..3] are ignored
HK_FORCE_INLINE void hkIntVector::setCombineTail16To32( hkIntVectorParameter highShorts, hkIntVectorParameter lowShorts )
{
#if HK_ENDIAN_BIG
	setMergeTail16(highShorts, lowShorts);
#else
	setMergeTail16(lowShorts, highShorts);
#endif
}

// result.u16[i] = highshorts.u8[i]<<16 + lowShorts.u8[i]. highShorts.u8/lowShorts.u8[8..15] are ignored
HK_FORCE_INLINE void hkIntVector::setCombineHead8To16( hkIntVectorParameter highShorts, hkIntVectorParameter lowShorts )
{
#if HK_ENDIAN_BIG
	setMergeHead8(highShorts, lowShorts);
#else
	setMergeHead8(lowShorts, highShorts);
#endif
}

// result.u16[i] = highshorts.u8[8+i]<<16 + lowShorts.u8[8+i]. highShorts.u8/lowShorts.u8[0..7] are ignored
HK_FORCE_INLINE void hkIntVector::setCombineTail8To16( hkIntVectorParameter highShorts, hkIntVectorParameter lowShorts )
{
#if HK_ENDIAN_BIG
	setMergeTail8(highShorts, lowShorts);
#else
	setMergeTail8(lowShorts, highShorts);
#endif
}

HK_FORCE_INLINE void hkIntVector::setSplit8To32( hkIntVectorParameter bytes )
{
	hkIntVector zero;zero.setZero();
	hkIntVector i16; i16.setCombineHead8To16( zero, bytes );
	setCombineHead16To32(zero, i16);
}

#endif // defined(HK_USING_GENERIC_INT_VECTOR_IMPLEMENTATION)

/////////////////////////////
// Variable shifts (shift all vector members by different amounts)
#if !defined(HK_INT_VECTOR_NATIVE_VARIABLESHIFT)

HK_FORCE_INLINE void hkIntVector::setShiftLeft32( hkIntVectorParameter a, hkIntVectorParameter shift )
{
	hkQuadUintUnion qu, qa, qshift;
	qa.q = a.m_quad;
	qshift.q = shift.m_quad;

	qu.u[0] = qa.u[0] << qshift.u[0];
	qu.u[1] = qa.u[1] << qshift.u[1];
	qu.u[2] = qa.u[2] << qshift.u[2];
	qu.u[3] = qa.u[3] << qshift.u[3];

	m_quad = qu.q;
}

HK_FORCE_INLINE void hkIntVector::setShiftRight32( hkIntVectorParameter a, hkIntVectorParameter shift )
{
	hkQuadUintUnion qu, qa, qshift;
	qa.q = a.m_quad;
	qshift.q = shift.m_quad;

	qu.u[0] = qa.u[0] >> qshift.u[0];
	qu.u[1] = qa.u[1] >> qshift.u[1];
	qu.u[2] = qa.u[2] >> qshift.u[2];
	qu.u[3] = qa.u[3] >> qshift.u[3];

	m_quad = qu.q;
}

HK_FORCE_INLINE void hkIntVector::setShiftLeft16( hkIntVectorParameter a, hkIntVectorParameter shift )
{
	hkQuadUshortUnion qu, qa, qshift;
	qa.q = a.m_quad;
	qshift.q = shift.m_quad;

	qu.u[0] = qa.u[0] << qshift.u[0];
	qu.u[1] = qa.u[1] << qshift.u[1];
	qu.u[2] = qa.u[2] << qshift.u[2];
	qu.u[3] = qa.u[3] << qshift.u[3];
	qu.u[4] = qa.u[4] << qshift.u[4];
	qu.u[5] = qa.u[5] << qshift.u[5];
	qu.u[6] = qa.u[6] << qshift.u[6];
	qu.u[7] = qa.u[7] << qshift.u[7];

	m_quad = qu.q;
}

HK_FORCE_INLINE void hkIntVector::setShiftRightS16( hkIntVectorParameter a, hkIntVectorParameter shift )
{
	hkQuadShortUnion qu, qa, qshift;
	qa.q = a.m_quad;
	qshift.q = shift.m_quad;

	qu.u[0] = qa.u[0] >> qshift.u[0];
	qu.u[1] = qa.u[1] >> qshift.u[1];
	qu.u[2] = qa.u[2] >> qshift.u[2];
	qu.u[3] = qa.u[3] >> qshift.u[3];
	qu.u[4] = qa.u[4] >> qshift.u[4];
	qu.u[5] = qa.u[5] >> qshift.u[5];
	qu.u[6] = qa.u[6] >> qshift.u[6];
	qu.u[7] = qa.u[7] >> qshift.u[7];

	m_quad = qu.q;
}

#endif // !defined(HK_INT_VECTOR_NATIVE_VARIABLESHIFT)

/////////////////////////////
// 128-bit bitwise shifts by a variable
#if !defined(HK_INT_VECTOR_NATIVE_BITSHIFT128)

HK_FORCE_INLINE void hkIntVector::setBitShiftLeft128(hkIntVectorParameter a, hkIntVectorParameter shiftSplat)
{
	int shift = shiftSplat.getU8<0>();
	int bitcount = shift % 8;
	int bytecount = shift / 8;
	hkQuadUcharUnion q;
	q.q = a.m_quad;
	int i;
	for (i = 0; i < 16 - (bytecount + 1); i++)
	{
		q.u[i] = (hkUint8)((q.u[i+bytecount] << bitcount) | (q.u[i+bytecount+1] >> (8 - bitcount)));
	}
	q.u[i++] = (hkUint8)(q.u[15] << bitcount);
	for (; i < 16; i++)
	{
		q.u[i] = 0;
	}
	m_quad = q.q;
}

HK_FORCE_INLINE void hkIntVector::setBitShiftRight128(hkIntVectorParameter a, hkIntVectorParameter shiftSplat)
{
	int shift = shiftSplat.getU8<0>();
	int bitcount = shift % 8;
	int bytecount = shift / 8;
	hkQuadUcharUnion q;
	q.q = a.m_quad;
	int i;
	for (i = 15; i >= bytecount + 1; i--)
	{
		q.u[i] = (hkUint8)((q.u[i-bytecount] >> bitcount) | (q.u[i-bytecount-1] << (8 - bitcount)));
	}
	q.u[i--] = (hkUint8)(q.u[0] >> bitcount);
	for (; i >= 0; i--)
	{
		q.u[i] = 0;
	}
	m_quad = q.q;
}

#endif // !defined(HK_INT_VECTOR_NATIVE_BITSHIFT128)



#if !defined(HK_INT_VECTOR_loadAsFloat32BitRepresentation) && !defined(HK_INT_VECTOR_loadAsFloat32BitRepresentation_f)
	HK_FORCE_INLINE void hkIntVector::loadAsFloat32BitRepresentation(const hkVector4f& x)
	{
		this->m_quad = *((hkQuadUint*)&x.m_quad);
	}

	HK_FORCE_INLINE void hkIntVector::storeAsFloat32BitRepresentation( hkVector4f& out ) const
	{
		hkQuadUint* assignAsInt = (hkQuadUint*)&out;
		*assignAsInt = this->m_quad;
	}
#endif
#if !defined(HK_INT_VECTOR_loadAsFloat32BitRepresentation) && !defined(HK_INT_VECTOR_loadAsFloat32BitRepresentation_d)

	HK_FORCE_INLINE void hkIntVector::loadAsFloat32BitRepresentation(const hkVector4d& x)
	{
		x.store<4>( (hkFloat32*)this );
	}

	HK_FORCE_INLINE void hkIntVector::storeAsFloat32BitRepresentation( hkVector4d& out ) const
	{
		out.load<4>( (hkFloat32*)this );
	}
#endif

///////////////////////////////////////////////////////////
// everything below this is common code for all platforms
///////////////////////////////////////////////////////////

HK_FORCE_INLINE void hkIntVector::setSignExtendS16ToS32( hkIntVectorParameter a )
{
	setShiftLeft32<16>(*this);
	setShiftRightS32<16>(*this);
}

HK_FORCE_INLINE void hkIntVector::setCombine16To32( hkIntVectorParameter a )
{
	if (HK_ENDIAN_LITTLE)
	{
		// we need to swap shorts on little-endian machines
		hkIntVector zeros; zeros.setZero();
		hkIntVector ones; ones.setNot(zeros);

		hkIntVector leftmask; leftmask.setMergeHead16(ones, zeros);

		hkIntVector left; left.setAnd(a, leftmask);
		hkIntVector right; right.setAndNot(a, leftmask);
		left.setShiftLeft32<16>(left);
		right.setShiftRight32<16>(right);
		setOr(left, right);
	}
	else
	{
		m_quad = a.m_quad;
	}
}

HK_FORCE_INLINE void hkIntVector::setCombine8To16( hkIntVectorParameter a )
{
	if (HK_ENDIAN_LITTLE)
	{
		// we need to swap bytes on little-endian machines
		hkIntVector zeros; zeros.setZero();
		hkIntVector ones; ones.setNot(zeros);

		hkIntVector leftmask; leftmask.setMergeHead8(ones, zeros);

		hkIntVector left; left.setAnd(a, leftmask);
		hkIntVector right; right.setAndNot(a, leftmask);
		left.setShiftLeft16<8>(left);
		right.setShiftRight16<8>(right);
		setOr(left, right);
	}
	else
	{
		m_quad = a.m_quad;
	}
}

HK_FORCE_INLINE void hkIntVector::setConvertHeadU16ToU32( hkIntVectorParameter a )
{
	hkIntVector zero; zero.setZero();
	setCombineHead16To32(zero, a);
}

HK_FORCE_INLINE void hkIntVector::setConvertHeadS16ToS32( hkIntVectorParameter a )
{
	setConvertHeadU16ToU32(a);
	setSignExtendS16ToS32(*this);
}

HK_FORCE_INLINE void hkIntVector::setConvertTailU16ToU32( hkIntVectorParameter a )
{
	hkIntVector zero; zero.setZero();
	setCombineTail16To32(zero, a);
}

HK_FORCE_INLINE void hkIntVector::setConvertTailS16ToS32( hkIntVectorParameter a )
{
	setConvertTailU16ToU32(a);
	setSignExtendS16ToS32(*this);
}


HK_FORCE_INLINE void hkIntVector::storeInto24LowerBitsOfReal(hkVector4f& vOut)
{
	HK_MATH_ASSERT(0xf0781100, (getU32(0) & 0xff000000) == 0, "can only store 24 bit integer");
	HK_MATH_ASSERT(0xf0781100, (getU32(1) & 0xff000000) == 0, "can only store 24 bit integer");
	HK_MATH_ASSERT(0xf0781100, (getU32(2) & 0xff000000) == 0, "can only store 24 bit integer");
	HK_MATH_ASSERT(0xf0781100, (getU32(3) & 0xff000000) == 0, "can only store 24 bit integer");
#if defined(HK_VECTOR_PARTS_MUST_BE_VALID)
	static HK_ALIGN16(int) mask[4] = { 0x3f000000, 0x3f000000, 0x3f000000, 0x3f000000 };
	hkIntVector vTemp; vTemp.setOr( *this, (const hkIntVector&)mask );
	vOut.load<4>( (hkFloat32*)&vTemp );
#else
	this->storeAsFloat32BitRepresentation( vOut );
#endif
}

HK_FORCE_INLINE void hkIntVector::storeInto24LowerBitsOfReal(hkVector4d& vOut)
{
	HK_MATH_ASSERT(0xf0781100, (getU32(0) & 0xff000000) == 0, "can only store 24 bit integer");
	HK_MATH_ASSERT(0xf0781100, (getU32(1) & 0xff000000) == 0, "can only store 24 bit integer");
	HK_MATH_ASSERT(0xf0781100, (getU32(2) & 0xff000000) == 0, "can only store 24 bit integer");
	HK_MATH_ASSERT(0xf0781100, (getU32(3) & 0xff000000) == 0, "can only store 24 bit integer");
	HK_ALIGN_DOUBLE(hkInt64 v[4]);
	v[0] = hkInt64(getU32<0>()) | 0x3ff0000000000000ull;
	v[1] = hkInt64(getU32<1>()) | 0x3ff0000000000000ull;
	v[2] = hkInt64(getU32<2>()) | 0x3ff0000000000000ull;
	v[3] = hkInt64(getU32<3>()) | 0x3ff0000000000000ull;
	vOut.load<4>( (hkDouble64*)&v[0] );
}

//
//	Sets this = abs(v)

#ifndef HK_INT_VECTOR_setAbs
#	define HK_INT_VECTOR_setAbs

HK_FORCE_INLINE void hkIntVector::setAbsS32(hkIntVectorParameter v)
{
	setFlipSignS32(v, v.lessZeroS32());
}

#endif

//
//	Sets this = sign * v

HK_FORCE_INLINE void hkIntVector::setFlipSignS32(hkIntVectorParameter v, hkVector4ComparisonParameter mask)
{
	hkIntVector vNeg;	vNeg.setNegS32<4>(v);
	setSelect(mask, vNeg, v);
}

//
// Sets this = first N components of v sorted ascending

template <> HK_FORCE_INLINE void hkIntVector::setSortS32<1, HK_SORT_ASCENDING>(hkIntVectorParameter v)	{	*this = v;	}
template <> HK_FORCE_INLINE void hkIntVector::setSortS32<1, HK_SORT_DESCENDING>(hkIntVectorParameter v)	{	*this = v;	}

template <> HK_FORCE_INLINE void hkIntVector::setSortS32<2, HK_SORT_ASCENDING>(hkIntVectorParameter v)
{
	hkIntVector vyx;	vyx.setPermutation<hkVectorPermutation::YXZW>(v);	//[y, x, z, w]
	hkIntVector vmin;	vmin.setMinS32(vyx, v);		// [min(x, y), min(x, y), z, w]
	hkIntVector vmax;	vmax.setMaxS32(vyx, v);		// [max(x, y), max(x, y), z, w]
	setSelect<hkVector4Comparison::MASK_X>(vmin, vmax);
}

template <> HK_FORCE_INLINE void hkIntVector::setSortS32<2, HK_SORT_DESCENDING>(hkIntVectorParameter v)
{
	hkIntVector vyx;	vyx.setPermutation<hkVectorPermutation::YXZW>(v);	//[y, x, z, w]
	hkIntVector vmin;	vmin.setMinS32(vyx, v);		// [min(x, y), min(x, y), z, w]
	hkIntVector vmax;	vmax.setMaxS32(vyx, v);		// [max(x, y), max(x, y), z, w]
	setSelect<hkVector4Comparison::MASK_X>(vmax, vmin);
}


//
//	Sets this = components of v sorted ascending

template <> HK_FORCE_INLINE void hkIntVector::setSortS32<3, HK_SORT_ASCENDING>(hkIntVectorParameter vIn)
{
	hkIntVector v = vIn;

	// Stage 1. v = (v.xxzz > v.yyww) ? v.yxwz : v.xyzw.
	// In the end, v = [min(x, y), max(x, y), z, w]
	{
		hkIntVector v_yxzw;	v_yxzw.setPermutation<hkVectorPermutation::YXZW>(v);
		hkIntVector v_yyww;	v_yyww.setPermutation<hkVectorPermutation::YYWW>(v);
		hkIntVector v_xxzz;	v_xxzz.setPermutation<hkVectorPermutation::XXZZ>(v);
		v.setSelect(v_yyww.compareLessThanS32(v_xxzz), v_yxzw, v);
	}

	// Stage 2. v = (v.xyxy > v.zwzw) ? v.zyxw : v.xyzw
	// In the end, v = [min(x, y, z), max(x, y), max(min(x, y), z), w]
	{
		hkIntVector v_zyxw;	v_zyxw.setPermutation<hkVectorPermutation::ZYXW>(v);	
		hkIntVector v_zwzw;	v_zwzw.setPermutation<hkVectorPermutation::ZWZW>(v);
		hkIntVector v_xyxy;	v_xyxy.setPermutation<hkVectorPermutation::XYXY>(v);
		v.setSelect(v_zwzw.compareLessThanS32(v_xyxy), v_zyxw, v);
	}

	// Stage 3. The first and last components are already sorted, we only need to sort the middle components
	// v = (v.xyyw > v.xzzw) ? v.xzyw : v.xyzw
	{
		hkIntVector v_xzyw;	v_xzyw.setPermutation<hkVectorPermutation::XZYW>(v);
		hkIntVector v_xzzw;	v_xzzw.setPermutation<hkVectorPermutation::XZZW>(v);
		hkIntVector v_xyyw;	v_xyyw.setPermutation<hkVectorPermutation::XYYW>(v);

		// Save result
		setSelect(v_xzzw.compareLessThanS32(v_xyyw), v_xzyw, v);
	}
}

//
//	Sets this = components of v sorted ascending

template <> HK_FORCE_INLINE void hkIntVector::setSortS32<4, HK_SORT_ASCENDING>(hkIntVectorParameter vIn)
{
	hkIntVector v = vIn;

	// Stage 1. v = (v.xxzz > v.yyww) ? v.yxwz : v.xyzw.
	// In the end, v = [min(x, y), max(x, y), min(z, w), max(z, w)]
	{
		hkIntVector v_yxwz;	v_yxwz.setPermutation<hkVectorPermutation::YXWZ>(v);
		hkIntVector v_yyww;	v_yyww.setPermutation<hkVectorPermutation::YYWW>(v);
		hkIntVector v_xxzz;	v_xxzz.setPermutation<hkVectorPermutation::XXZZ>(v);
		v.setSelect(v_yyww.compareLessThanS32(v_xxzz), v_yxwz, v);
	}

	// Stage 2. v = (v.xyxy > v.zwzw) ? v.zwxy : v.xyzw
	// In the end, v = [min(x, y, z, w), min(max(x, y), max(z, w)), max(min(x, y), min(z, w)), max(x, y, z, w)]
	{
		hkIntVector v_zwxy;	v_zwxy.setPermutation<hkVectorPermutation::ZWXY>(v);	
		hkIntVector v_zwzw;	v_zwzw.setPermutation<hkVectorPermutation::ZWZW>(v);
		hkIntVector v_xyxy;	v_xyxy.setPermutation<hkVectorPermutation::XYXY>(v);
		v.setSelect(v_zwzw.compareLessThanS32(v_xyxy), v_zwxy, v);	
	}

	// Stage 3. The first and last components are already sorted, we only need to sort the middle components
	// v = (v.xyyw > v.xzzw) ? v.xzyw : v.xyzw
	{
		hkIntVector v_xzyw;	v_xzyw.setPermutation<hkVectorPermutation::XZYW>(v);
		hkIntVector v_xzzw;	v_xzzw.setPermutation<hkVectorPermutation::XZZW>(v);
		hkIntVector v_xyyw;	v_xyyw.setPermutation<hkVectorPermutation::XYYW>(v);

		// Save result
		setSelect(v_xzzw.compareLessThanS32(v_xyyw), v_xzyw, v);
	}
}

template <> HK_FORCE_INLINE int hkIntVector::getIndexOfMinComponent<4>() const
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	hkIntVector mi;					mi.setAll(horizontalMinS32<4>());
	const hkVector4Comparison isMin	= compareEqualS32(mi);
	HK_ON_DEBUG(const int mask = isMin.getMask();)
	HK_MATH_ASSERT(0x2842fb1, mask > 0, "inconsistent min value of self");
	return isMin.getIndexOfFirstComponentSet();
#else
	const hkInt32* HK_RESTRICT tmp = (const hkInt32* HK_RESTRICT)this;

	int		xyIndex = 0;
	hkInt32	xyValue = tmp[0];
	if ( tmp[0] > tmp[1] )
	{
		xyIndex = 1;
		xyValue = tmp[1];
	}

	int		zwIndex = 2;
	hkInt32	zwValue = tmp[2];
	if ( tmp[2] > tmp[3] )
	{
		zwIndex = 3;
		zwValue = tmp[3];
	}
	if ( xyValue > zwValue )
	{
		return zwIndex;
	}
	return xyIndex;
#endif
}

template <>
HK_FORCE_INLINE int hkIntVector::getIndexOfMinComponent<3>() const
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	hkIntVector mi;				mi.setAll(horizontalMinS32<3>());
	hkVector4Comparison isMin	= compareEqualS32(mi);
	hkVector4Comparison xyzMask; xyzMask.set<hkVector4ComparisonMask::MASK_XYZ>();
	isMin.setAnd(isMin,xyzMask);

	HK_ON_DEBUG(const int mask = isMin.getMask();)
	HK_MATH_ASSERT(0x2842fb1, mask > 0, "inconsistent min value of self");
	HK_MATH_ASSERT(0x2842fb2, (mask & hkVector4ComparisonMask::MASK_W) == 0, "selective compare failed");
	return isMin.getIndexOfFirstComponentSet();
#else
	const hkInt32* HK_RESTRICT tmp = (const hkInt32* HK_RESTRICT)this;

	int		xyIndex = 0;
	hkInt32	xyValue = tmp[0];
	if ( tmp[0] > tmp[1] )
	{
		xyIndex = 1;
		xyValue = tmp[1];
	}

	if ( xyValue > tmp[2] )
	{
		return 2;
	}
	return xyIndex;
#endif
}

template <> HK_FORCE_INLINE int hkIntVector::getIndexOfMinComponent<2>() const
{
	return getComponent<0>() > getComponent<1>() ? 1 : 0;
}

template <> HK_FORCE_INLINE int hkIntVector::getIndexOfMinComponent<1>() const
{
	return 0;
}

template <int N> HK_FORCE_INLINE int hkIntVector::getIndexOfMinComponent() const
{
	HK_INT_VECTOR_NOT_IMPLEMENTED;
	return 0;
}

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
