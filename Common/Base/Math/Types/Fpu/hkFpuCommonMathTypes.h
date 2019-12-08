/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_MATH_FPU_COMMON_MATH_TYPES_H
#define HK_MATH_FPU_COMMON_MATH_TYPES_H

// no special includes necessary


// storage  type for hkIntVector
union hkQuadUint 
{
	//+hk.MemoryTracker(ignore = True)
	HK_ALIGN_REAL(hkUint32 u32[4]);
	HK_ALIGN_REAL(hkInt32 i32[4]);
};

struct hkSingleInt128
{
	public:

#if ( HK_ENDIAN_LITTLE )
		// Unsigned int access
		template <int I> HK_FORCE_INLINE hkUint32 getU32() const	{	return u.u32[I];	}
		HK_FORCE_INLINE hkUint32 getU32(int I) const				{	return u.u32[I];	}
		template <int I> HK_FORCE_INLINE void setU32(hkUint32 x)	{	u.u32[I] = x;		}
		HK_FORCE_INLINE void setU32(int I, hkUint32 x)				{	u.u32[I] = x;		}

		// Signed int access
		template <int I> HK_FORCE_INLINE hkInt32 getS32() const		{	return u.i32[I];	}
		HK_FORCE_INLINE hkInt32 getS32(int I) const					{	return u.i32[I];	}
		template <int I> HK_FORCE_INLINE void setS32(hkInt32 x)		{	u.i32[I] = x;		}
		HK_FORCE_INLINE void setS32(int I, hkInt32 x)				{	u.i32[I] = x;		}

		// Unsigned long access
		template <int I> HK_FORCE_INLINE hkUint64 getU64() const	{	return u.u64[I];	}
		HK_FORCE_INLINE hkUint64 getU64(int I) const				{	return u.u64[I];	}
		template <int I> HK_FORCE_INLINE void setU64(hkUint64 x)	{	u.u64[I] = x;		}
		HK_FORCE_INLINE void setU64(int I, hkUint64 x)				{	u.u64[I] = x;		}

		// Signed long access
		template <int I> HK_FORCE_INLINE hkInt64 getS64() const		{	return u.i64[I];	}
		HK_FORCE_INLINE hkInt64 getS64(int I) const					{	return u.i64[I];	}
		template <int I> HK_FORCE_INLINE void setS64(hkInt64 x)		{	u.i64[I] = x;		}
		HK_FORCE_INLINE void setS64(int I, hkInt64 x)				{	u.i64[I] = x;		}
#endif

#if ( HK_ENDIAN_BIG )
		// Unsigned int access
		template <int I> HK_FORCE_INLINE hkUint32 getU32() const	{	return u.u32[3 - I];	}
		HK_FORCE_INLINE hkUint32 getU32(int I) const				{	return u.u32[3 - I];	}
		template <int I> HK_FORCE_INLINE void setU32(hkUint32 x)	{	u.u32[3 - I] = x;		}
		HK_FORCE_INLINE void setU32(int I, hkUint32 x)				{	u.u32[3 - I] = x;		}

		// Signed int access
		template <int I> HK_FORCE_INLINE hkInt32 getS32() const		{	return u.i32[3 - I];	}
		HK_FORCE_INLINE hkInt32 getS32(int I) const					{	return u.i32[3 - I];	}
		template <int I> HK_FORCE_INLINE void setS32(hkInt32 x)		{	u.i32[3 - I] = x;		}
		HK_FORCE_INLINE void setS32(int I, hkInt32 x)				{	u.i32[3 - I] = x;		}

		// Unsigned long access
		template <int I> HK_FORCE_INLINE hkUint64 getU64() const	{	return u.u64[1 - I];	}
		HK_FORCE_INLINE hkUint64 getU64(int I) const				{	return u.u64[1 - I];	}
		template <int I> HK_FORCE_INLINE void setU64(hkUint64 x)	{	u.u64[1 - I] = x;		}
		HK_FORCE_INLINE void setU64(int I, hkUint64 x)				{	u.u64[1 - I] = x;		}

		// Signed long access
		template <int I> HK_FORCE_INLINE hkInt64 getS64() const		{	return u.i64[1 - I];	}
		HK_FORCE_INLINE hkInt64 getS64(int I) const					{	return u.i64[1 - I];	}
		template <int I> HK_FORCE_INLINE void setS64(hkInt64 x)		{	u.i64[1 - I] = x;		}
		HK_FORCE_INLINE void setS64(int I, hkInt64 x)				{	u.i64[1 - I] = x;		}
#endif

	protected:
		
		union
		{
			HK_ALIGN_REAL(hkUint32 u32[4]);
			HK_ALIGN_REAL(hkInt32 i32[4]);
			HK_ALIGN_REAL(hkUint64 u64[2]);
			HK_ALIGN_REAL(hkInt64 i64[2]);
		} u;
};

struct hkQuadUlong
{
	//+hk.MemoryTracker(ignore = True)
	hkSingleInt128 xy;
	hkSingleInt128 zw;
};

class hkIntVector;
typedef const hkIntVector& hkIntVectorParameter;

#define HK_QUADINT_CONSTANT(a, b, c, d)		{(a), (b), (c), (d)}


#endif // HK_MATH_FPU_COMMON_MATH_TYPES_H

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
