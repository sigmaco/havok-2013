/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKBASE_HKBASETYPES_H
#define HKBASE_HKBASETYPES_H

#include <Common/Base/Types/hkBaseDefs.h>

typedef hkUint16 hkObjectIndex;
typedef hkReal hkTime;

#define HK_INVALID_OBJECT_INDEX 0xffff


HK_FORCE_INLINE hkInt32 HK_CALL hkPointerToInt32( const void* ptr )
{
	return static_cast<int>( hkUlong(ptr) );
}

/// get the byte offset of B - A, as a full long.
HK_FORCE_INLINE hkLong HK_CALL hkGetByteOffset( const void* base, const void* pntr)
{
	return hkLong(pntr) - hkLong(base);
}

/// get the byte offset of B - A, as an int (64bit issues, so here for easy code checks)
HK_FORCE_INLINE int HK_CALL hkGetByteOffsetInt( const void* base, const void* pntr)
{
	return static_cast<int>( hkGetByteOffset( base, pntr ) );
}

/// get the byte offset of B - A, as a full 64bit hkUint64.
HK_FORCE_INLINE hkInt32 HK_CALL hkGetByteOffsetCpuPtr( const HK_CPU_PTR(void*) base, const HK_CPU_PTR(void*) pntr)
{
	return hkInt32(hkLong((HK_CPU_PTR(const char*))(pntr) - (HK_CPU_PTR(const char*))(base)));
}

template <typename TYPE>
HK_ALWAYS_INLINE TYPE* HK_CALL hkAddByteOffset( TYPE* base, hkLong offset )
{
	return reinterpret_cast<TYPE*>( reinterpret_cast<hkUlong>(base) + offset );
}

template <typename TYPE>
HK_ALWAYS_INLINE TYPE HK_CALL hkAddByteOffsetCpuPtr( TYPE base, hkLong offset )
{
	return reinterpret_cast<TYPE>( reinterpret_cast<hkUlong>(base) + offset );
}


template <typename TYPE>
HK_ALWAYS_INLINE const TYPE* HK_CALL hkAddByteOffsetConst( const TYPE* base, hkLong offset )
{
	return reinterpret_cast<const TYPE*>( reinterpret_cast<hkUlong>(base) + offset );
}

template <typename TYPE>
HK_ALWAYS_INLINE TYPE HK_CALL hkAddByteOffsetCpuPtrConst( TYPE base, hkLong offset )
{
	return reinterpret_cast<TYPE>( reinterpret_cast<hkUlong>(base) + offset );
}

	/// If you have a pair of pointers and you have one pointer, than this function allows you to quickly get the other pointer of the pair.
template <typename TYPE>
HK_ALWAYS_INLINE TYPE HK_CALL hkSelectOther( TYPE a, TYPE pairA, TYPE pairB )
{
	return (TYPE)( hkUlong(a) ^ hkUlong(pairA) ^ hkUlong(pairB) );
}

/// If you have a pair of pointers and you have one pointer, than this function allows you to quickly get the other pointer of the pair.
template <typename TYPE>
HK_ALWAYS_INLINE TYPE* HK_CALL hkSelect( int select, TYPE* pairA, TYPE* pairB )
{
	//HK_ASSERT( 0xf0345456, select == 0 || select == 1);
	hkUlong ua = hkUlong(pairA);
	hkUlong ub = hkUlong(pairB);
	return reinterpret_cast<TYPE*>( ua ^ ((ua^ub)&(-select)) );
}

namespace hkTrait
{
	template <unsigned SIZE> struct UnsignedFor;
	template<> struct UnsignedFor<1> { typedef hkUint8 Type; };
	template<> struct UnsignedFor<2> { typedef hkUint16 Type; };
	template<> struct UnsignedFor<4> { typedef hkUint32 Type; };
	template<> struct UnsignedFor<8> { typedef hkUint64 Type; };
}

template <typename VTYPE, typename MTYPE>
HK_ALWAYS_INLINE VTYPE HK_CALL hkClearBits(VTYPE value, MTYPE mask)
{
	typedef typename hkTrait::UnsignedFor<sizeof(VTYPE)>::Type UVTYPE;
	typedef typename hkTrait::UnsignedFor<sizeof(MTYPE)>::Type UMTYPE;
	return VTYPE(UVTYPE(value) & ~UVTYPE(UMTYPE(mask)));
}

HK_FORCE_INLINE hkUint32 hkNextPowerOf2(hkUint32 in) 
{
	in -= 1;

	in |= in >> 16;
	in |= in >> 8;
	in |= in >> 4;
	in |= in >> 2;
	in |= in >> 1;

	return in + 1; 
}

HK_FORCE_INLINE hkUint32 hkBitmask(int width)
{
	// return (1<<width) - 1,
	// except it must work for width = 32
	// (bear in mind that shift by >=32 places is undefined)
	hkUint32 maskIfNot32 = (1 << (width & 31)) - 1; // ans if width != 32, else 0
	hkUint32 is32 = ((width & 32) >> 5); // 1 if width = 32, else 0
	return maskIfNot32 - is32; // the answer in the case width=32 is -1
}

class hkFinishLoadedObjectFlag
{
	//+hk.MemoryTracker(ignore=True)
public:
	hkFinishLoadedObjectFlag() : m_finishing(0) {}
	int m_finishing;
};

#define hkSizeOf(A) int(sizeof(A))

#define HK_REFLECTION_CLASSFILE_DESTINATION(PATH)
#define HK_REFLECTION_CLASSFILE_HEADER(PATH)
#define HK_DECLARE_REFLECTION() \
	static const struct hkInternalClassMember Members[]; \
	static const hkClass& HK_CALL staticClass(); \
	struct DefaultStruct

class hkClass;

/// A generic object with metadata.

struct hkVariant
{
	//+hk.MemoryTracker(ignore=True)
	void* m_object;
	const hkClass* m_class;
};



//#define HK_HALF_IS_FLOAT

/// A floating point value stored in 16-bit. This is a non IEEE representation using
/// 1 sign bit, 8 exponent bits and 7 mantissa bits. This is basically a 32-bit float
/// truncated. It supports the same floating point range as 32-bit float,
/// but only with 6 bit precision (because the last bit is not rounded and renormalized).
class hkHalf
{
	//+hk.MemoryTracker(ignore=True)
public:

#ifndef HK_DISABLE_MATH_CONSTRUCTORS
	HK_FORCE_INLINE hkHalf() { }
	HK_FORCE_INLINE explicit hkHalf(const hkFloat32& f);
#endif

	HK_FORCE_INLINE hkHalf& operator=(const hkHalf& other)
	{
		m_value = other.m_value;
		return *this;
	}

	HK_FORCE_INLINE void store( double* d ) const
	{
		float f; store(&f);
		*d = double(f);
	}

	template <bool ROUND>
	HK_FORCE_INLINE void setReal(const hkReal& r);

	template <bool ROUND>
	HK_FORCE_INLINE void set(const float& r);

	template <bool ROUND>
	HK_FORCE_INLINE void set(const double& r);


#if defined(HK_HALF_IS_FLOAT)

#ifndef HK_DISABLE_MATH_CONSTRUCTORS
	HK_FORCE_INLINE hkHalf& operator=(const float& f)
	{
		m_value = f;
		return *this;
	}
#endif

	typedef hkFloat32 Storage;

	HK_FORCE_INLINE bool operator==(const hkHalf& other) const
	{
		const hkUint32* a = (const hkUint32*)&m_value;
		const hkUint32* b = (const hkUint32*)&other.m_value;
		return (*a == *b); // Warning: bitwise compare!
	}

	HK_FORCE_INLINE void store( float* f ) const
	{
		*f = m_value;
	}

	HK_FORCE_INLINE void setZero() { m_value = 0.0f; } 
	HK_FORCE_INLINE void setOne()  { m_value = 1.0f; }
	HK_FORCE_INLINE void setMax()  { m_value = HK_FLOAT_MAX; }
	HK_FORCE_INLINE void setNegativeOne() { m_value = -1.0f; }
	
	HK_FORCE_INLINE operator float() const
	{
		return m_value;
	}

	HK_FORCE_INLINE float getFloat32() const
	{
		return m_value;
	}

	HK_FORCE_INLINE double getDouble() const
	{
		return double(m_value);
	}

	HK_FORCE_INLINE hkReal getReal() const
	{
		return hkReal(m_value);
	}


#else

#ifndef HK_DISABLE_MATH_CONSTRUCTORS
	HK_FORCE_INLINE hkHalf& operator=(const float& f)
	{
		int t = ((const int*)&f)[0];
		m_value = hkInt16(t>>16);
		return *this;
	}
#endif

	typedef hkInt16 Storage;

	HK_FORCE_INLINE bool operator==(const hkHalf& other) const
	{
		return (m_value == other.m_value); // Warning: bitwise compare!
	}

	HK_FORCE_INLINE void store( float* f ) const
	{
		hkUint32* asInt = (hkUint32*)f;
		asInt[0] = m_value << 16;
	}

	HK_FORCE_INLINE bool isZero()  const { return 0 == (0x7fff & m_value); } 
	HK_FORCE_INLINE void setZero() { m_value = 0x0000; } 
	HK_FORCE_INLINE void setOne()  { m_value = 0x3f80; }
	HK_FORCE_INLINE void setMax()  { m_value = 0x7f7f; }
	HK_FORCE_INLINE void setNegativeOne() { m_value = -16512; /*0xbf80*/ }

	HK_FORCE_INLINE operator float() const
	{
		return getFloat32();
	}

	HK_FORCE_INLINE float getFloat32() const
	{
		union
		{
			int i;
			float f;
		} u;
		u.i = (m_value <<16);
		return u.f;
	}

	HK_FORCE_INLINE double getDouble() const
	{
		return double(getFloat32());
	}

	HK_FORCE_INLINE hkReal getReal() const
	{
		return hkReal(getFloat32());
	}

#endif

	Storage getStorage() const 
	{
		return m_value;
	}

	void setStorage( Storage val )
	{
		m_value = val;
	}

	private:
		Storage m_value;
};

#if defined(HK_HALF_IS_FLOAT)

template <bool ROUND>
HK_FORCE_INLINE void hkHalf::set(const float& r)
{
	m_value = r;
}

template <bool ROUND>
HK_FORCE_INLINE void hkHalf::set(const double& r)
{
	const hkUint64 mask = 0xFFFFFFFF00000000ull;
	hkUint64 t = ((const hkUint64*)&r)[0];
	hkUint64 val = t & mask;
	hkDouble64* f = (hkDouble64*)&val;
	m_value = hkFloat32(*f);
}

template <>
HK_FORCE_INLINE void hkHalf::set<true>(const float& r)
{
	m_value = hkFloat32(r);
}

template <>
HK_FORCE_INLINE void hkHalf::set<true>(const double& r)
{
	m_value = hkFloat32(r);
}

template <bool ROUND>
HK_FORCE_INLINE void hkHalf::setReal(const hkReal& r)
{
	set<ROUND>(r);
}

#else

template <bool ROUND>
HK_FORCE_INLINE void hkHalf::set(const float& r)
{
	union { float f; int i; } u;
	u.f = hkFloat32(r);
	m_value = hkInt16(u.i>>16);
}

template <>
HK_FORCE_INLINE void hkHalf::set<true>(const float& r)
{
	union { float f; int i; } u;
	u.f = hkFloat32(r) * (1.0f + 1.0f/256.f);
	m_value = hkInt16(u.i>>16);
}


template <bool ROUND>
HK_FORCE_INLINE void hkHalf::set(const double& r)
{
	union { float f; int i; } u;
	u.f = hkFloat32(r);
	m_value = hkInt16(u.i>>16);
}

template <>
HK_FORCE_INLINE void hkHalf::set<true>(const double& r)
{
	union { float f; int i; } u;
	u.f = hkFloat32(r) * (1.0f + 1.0f/256.f);
	m_value = hkInt16(u.i>>16);
}

template <bool ROUND>
HK_FORCE_INLINE void hkHalf::setReal(const hkReal& r)
{
	set<ROUND>(r);
}


#endif

#ifndef HK_DISABLE_MATH_CONSTRUCTORS
HK_FORCE_INLINE hkHalf::hkHalf(const hkFloat32& f)
{
	setReal<true>(f);
}
#endif


/// A floating point value stored in 16-bit according to the IEEE 754-2008
/// format 'binary16' which has 1 sign bit, 5 exponent bits and 10 mantissa bits.
/// This format is compatible with the widely used GPU 'half' variable format.
/// The supported value range is 6.1035156e-5 to 131008.0 (both pos/neg) with
/// 10 bit precision.
///
/// \warning For performance reasons, our implementation differs from the 
///          IEEE and some GPU definitions in that 32-bit values greater than 
///          the max half value do not get mapped to infinity but to max.
class hkFloat16
{
public:

	//+hk.MemoryTracker(ignore=True)
	HK_DECLARE_REFLECTION();

public:

	HK_FORCE_INLINE hkFloat16& operator=(const hkFloat16& other)
	{
		m_value = other.m_value;
		return *this;
	}

	HK_FORCE_INLINE void setZero()
	{
		m_value = 0x0000;
	} 

	HK_FORCE_INLINE void setOne()
	{
		m_value = 0x3c00;
	}

	template <bool ROUND>
	HK_FORCE_INLINE void setReal(hkReal r);

	HK_FORCE_INLINE hkFloat32 getFloat32() const
	{
		enum {
			sign_pos = 15,
			half_sign = 1 << sign_pos,
			half_exponent = 0x00007C00,
			mantissa_width   = 23,
			mantissa_width_h = 10,
			mantissa_mask = (1 << mantissa_width_h) - 1,
			adjust = mantissa_width - mantissa_width_h,
			half_bias_offset = 0x0001C000
		};

		const hkUint32
			sign = m_value & half_sign,
			exponent = m_value & half_exponent,
			mantissa = m_value & mantissa_mask,
			exp_offset = exponent + half_bias_offset,
			bits = (sign << (sign_pos+1)) | ((exp_offset | mantissa) << adjust);

		const hkFloat32* bits_f = (const hkFloat32*)&bits;
		return exponent ? hkFloat32(*bits_f) : hkFloat32(0);
	}

	HK_FORCE_INLINE hkReal getReal() const
	{
		return hkReal(getFloat32());
	}

	HK_FORCE_INLINE hkUint16 getBits() const
	{
		return m_value;
	}

	HK_FORCE_INLINE void setBits(hkUint16 b)
	{
		m_value = b;
	}

#ifndef HK_DISABLE_MATH_CONSTRUCTORS
	HK_FORCE_INLINE hkFloat16() { }
	HK_FORCE_INLINE explicit hkFloat16(const hkFloat32& f);
#endif

private:
	hkUint16 m_value;
};


template <>
HK_FORCE_INLINE void hkFloat16::setReal<true>(hkReal r)
{
	const hkUint32 infinity_i  = 0x47FFE000; // Largest positive half
	const hkUint32 halfNormMin = 0x38800000; // Smallest positive normalized half

	union { float f; int i; } infinity; infinity.i = infinity_i;

	enum {
		mantissa_width   = 23,
		mantissa_width_h = 10,
		mantissa_mask = (1<<mantissa_width) - 1,
		sign_mask = 0x80000000,
		adjust = mantissa_width - mantissa_width_h,
		exponent_fix = hkUint8(-(127-15)) << mantissa_width
	};

	union { float f; int i; } bits; bits.f = hkFloat32(r);
	const hkUint32
		bits_i = (bits.f > infinity.f) ? infinity.i : bits.i,
		exp = bits_i + exponent_fix,
		round = (bits_i + 0xFFFu) + ((bits_i >> adjust) & 1u),
		result = (exp & ~mantissa_mask) | (round & mantissa_mask),
		h = (result >> adjust) | ((bits_i & sign_mask) >> 16),
		absbits = bits_i & 0x7FFFFFFF;
	m_value = (absbits >= halfNormMin) ? (hkUint16)h : 0;
}

template <bool ROUND>
HK_FORCE_INLINE void hkFloat16::setReal(hkReal r)
{
	const hkUint32 infinity_i  = 0x47FFE000; // Largest positive half
	const hkUint32 halfNormMin = 0x38800000; // Smallest positive normalized half

	union { float f; int i; } infinity; infinity.i = infinity_i;

	enum {
		mantissa_width   = 23,
		mantissa_width_h = 10,
		mantissa_mask = (1<<mantissa_width) - 1,
		sign_mask = 0x80000000,
		adjust = mantissa_width - mantissa_width_h,
		exponent_fix = hkUint8(-(127-15)) << mantissa_width
	};

	union { float f; int i; } bits; bits.f = hkFloat32(r);
	const hkUint32
		bits_i = (bits.f > infinity.f) ? infinity.i : bits.i,
		exp = bits_i + exponent_fix,
		result = (exp & ~mantissa_mask) | (bits_i & mantissa_mask),
		h = (result >> adjust) | ((bits_i & sign_mask) >> 16),
		absbits = bits_i & 0x7FFFFFFF;
	m_value = (absbits >= halfNormMin) ? (hkUint16)h : 0;
}

#ifndef HK_DISABLE_MATH_CONSTRUCTORS
HK_FORCE_INLINE hkFloat16::hkFloat16(const hkFloat32& f)
{
	setReal<true>(f);
}
#endif

//#define HK_BOOL32_IS_STRICT
enum hkBool32FalseType { hkFalse32 = 0 };

#if defined(HK_BOOL32_IS_STRICT)
class hkBool32;
#else
#	if defined(HK_COMPILER_MSVC) || defined(HK_COMPILER_INTEL)
#		pragma warning( disable : 4800 ) // forcing value to bool 'true' or 'false' (performance warning)
#	endif
	/// Bool used for inner loops.
	///
	/// False is zero, true is _any_ non-zero value. Advice: simply check for != false.
	/// \warning The following operations on hkBool32 will not work as expected: ==, >, <, ~, ^, &
	/// These will work: ! , &&, ||, |
typedef hkUint32 hkBool32;
#endif

	/// A wrapper to store a hkBool in one byte, regardless of compiler options.
class hkBool
{
	//+hk.MemoryTracker(ignore=True)
	public:

			// used in compile time asserts
		typedef char CompileTimeTrueType;
		typedef int CompileTimeFalseType;

		HK_ALWAYS_INLINE hkBool()
		{
		}

		HK_FORCE_INLINE hkBool(bool b)
		{
			m_bool = static_cast<char>(b);
		}


#if defined(HK_BOOL32_IS_STRICT)
		HK_FORCE_INLINE hkBool(int  b){ m_bool = b!=0; }
		HK_FORCE_INLINE hkBool(hkUint32  b){ m_bool = b!=0; }
		HK_FORCE_INLINE hkBool(const hkBool32& b);
		HK_FORCE_INLINE hkBool& operator=(const hkBool32& e);
#endif

		HK_FORCE_INLINE operator bool() const
		{
			return m_bool != 0;
		}

		HK_FORCE_INLINE hkBool& operator=(bool e)
		{
			m_bool = static_cast<char>(e);
			return *this;
		}


		HK_FORCE_INLINE hkBool operator==(bool e) const
		{
			return (m_bool != 0) == e;
		}

		HK_FORCE_INLINE hkBool operator!=(bool e) const
		{
			return (m_bool != 0) != e;
		}

	private:
#if defined(HK_BOOL32_IS_STRICT)
		friend class hkBool32;
#endif
		char m_bool;
};


#if defined(HK_BOOL32_IS_STRICT)
class hkBool32
{
	// operators that work as expected
public:

	HK_FORCE_INLINE hkBool32() {}

	HK_FORCE_INLINE hkBool32(const hkBool& b)  { m_bool = b.m_bool; }

	HK_FORCE_INLINE hkBool32(hkUint32 i) : m_bool(i) {}

	HK_FORCE_INLINE hkBool32(const hkBool32& rhs): m_bool(rhs.m_bool) {}

	HK_FORCE_INLINE operator bool() const { return m_bool != 0; }

	HK_FORCE_INLINE operator hkBool() const { return hkBool(m_bool != 0); }

	//HK_FORCE_INLINE hkBool32& operator =(const hkBool32& b) { m_bool = b.m_bool; return *this; }

	HK_FORCE_INLINE bool operator !() const { return !m_bool; }

	HK_FORCE_INLINE bool operator &&(const hkBool32& b) const { return m_bool && b.m_bool; }
	HK_FORCE_INLINE bool operator &&(const hkBool& b) const { return m_bool && b; }
	HK_FORCE_INLINE bool operator &&(const bool b) const { return (m_bool!=0) && b; }

	HK_FORCE_INLINE bool operator ||(const hkBool32& b) const { return m_bool || b.m_bool; }
	HK_FORCE_INLINE bool operator ||(const hkBool& b) const { return m_bool || b; }
	HK_FORCE_INLINE bool operator ||(const bool b) const { return (m_bool!=0) || b; }

	//	HK_FORCE_INLINE	bool operator !=(const bool b) const{ if ( b!= false) {HK_BREAKPOINT(0xf0345456);}; return m_bool != 0; }
	//	HK_FORCE_INLINE	bool operator ==(const bool b) const{ if ( b!= false) {HK_BREAKPOINT(0xf0345456);}; return m_bool == 0; }
	//	HK_FORCE_INLINE	bool operator !=(const int b) const{ if ( b!= 0) {HK_BREAKPOINT(0xf0345456);}; return m_bool != 0; }
	HK_FORCE_INLINE	bool operator ==(hkBool32FalseType) const{ return m_bool == 0; }
	HK_FORCE_INLINE	bool operator !=(hkBool32FalseType) const{ return m_bool != 0; }

	HK_FORCE_INLINE hkBool32 operator |(const hkBool32& b) const { return m_bool | b.m_bool; }

	HK_FORCE_INLINE hkBool32& operator |=(const hkBool32& b) { m_bool |= b.m_bool; return *this; }

	// operators that don't work
private:

	bool operator ==(const hkBool32& b) const;
	bool operator !=(const hkBool32& b) const;
	bool operator <=(const hkBool32& b) const;
	bool operator >=(const hkBool32& b) const;
	bool operator < (const hkBool32& b) const;
	bool operator > (const hkBool32& b) const;

	hkBool32 operator ~() const;
	hkBool32 operator &(const hkBool32& b) const;
	hkBool32 operator ^(const hkBool32& b) const;

	hkBool32& operator &=(const hkBool32& b);
	hkBool32& operator ^=(const hkBool32& b);

public:

	hkUint32 m_bool;
};
#endif

#if defined(HK_BOOL32_IS_STRICT)
	HK_FORCE_INLINE hkBool::hkBool(const hkBool32& b)
	{
		m_bool = bool(b);
	}

	HK_FORCE_INLINE hkBool& hkBool::operator=(const hkBool32& b)
	{
		m_bool = bool(b);
		return *this;
	}
#endif


// A lookup table for converting unsigned char to float
// useful for avoiding LHS

extern "C"
{
	extern const hkFloat32 hkUInt8ToFloat32[256];
}

	/// A wrapper to store an enum with explicit size.
template<typename ENUM, typename STORAGE>
class hkEnum
{
	public:

		HK_ALWAYS_INLINE hkEnum()
		{
		}

		hkEnum(ENUM e)
		{
			m_storage = static_cast<STORAGE>(e);
		}

		operator ENUM() const
		{
			return static_cast<ENUM>(m_storage);
		}
		void operator=(ENUM e)
		{
			m_storage = static_cast<STORAGE>(e);
		}
		hkBool operator==(ENUM e) const
		{
			return m_storage == static_cast<STORAGE>(e);
		}
		hkBool operator!=(ENUM e) const
		{
			return m_storage != static_cast<STORAGE>(e);
		}

	private:

		STORAGE m_storage;
};

	/// A wrapper to store bitfield with an explicit size.
template<typename BITS, typename STORAGE>
class hkFlags
{
	public:

		HK_FORCE_INLINE hkFlags()					{}
		HK_FORCE_INLINE hkFlags(STORAGE s)			{	m_storage = s;	}

		HK_FORCE_INLINE void clear()				{	m_storage = 0;		}
		HK_FORCE_INLINE void clear(STORAGE mask)	{	m_storage &= ~mask;	}
		HK_FORCE_INLINE void setAll( STORAGE s )	{	m_storage = s;	}

		HK_FORCE_INLINE void orWith( STORAGE s )	{	m_storage |= s;	}
		HK_FORCE_INLINE void xorWith( STORAGE s )	{	m_storage ^= s;	}
		HK_FORCE_INLINE void andWith( STORAGE s )	{	m_storage &= s;	}

		HK_FORCE_INLINE void setWithMask( STORAGE s, STORAGE mask )		{	m_storage = (m_storage & ~mask) | (s & mask);	}
		HK_FORCE_INLINE STORAGE get() const								{	return m_storage;			}
		HK_FORCE_INLINE STORAGE get( STORAGE mask ) const				{	return m_storage & mask;	}
		HK_FORCE_INLINE hkBool32 anyIsSet( STORAGE mask ) const			{	return (m_storage & mask);	}
		HK_FORCE_INLINE hkBool32 noneIsSet( STORAGE mask ) const		{	return (m_storage & mask) == 0;	}
		HK_FORCE_INLINE bool allAreSet( STORAGE mask ) const			{	return (m_storage & mask) == mask;	}

		HK_FORCE_INLINE bool operator==( const hkFlags& f ) const		{	return f.m_storage == m_storage;	}
		HK_FORCE_INLINE hkBool32 operator!=( const hkFlags& f ) const	{	return f.m_storage ^ m_storage;		}

	private:

		STORAGE m_storage;
};

#	define HK_PADSPU_PROMOTE(e) e
#	define HK_PADSPU_EXTRACT(e) e

	/// wrapper class for variables in structures.
	/// Basically on the PlayStation(R)3 SPU, the SPU can only poorly
	/// access non aligned members. This class give each variable
	/// 16 bytes, thereby dramatically decreasing code size and CPU overhead
template <typename TYPE>
class hkPadSpu
{
	public:

		HK_ALWAYS_INLINE hkPadSpu() {}

		HK_ALWAYS_INLINE hkPadSpu(TYPE e)
			: m_storage( HK_PADSPU_PROMOTE(e) )
		{
		}

		HK_ALWAYS_INLINE void operator=(TYPE e)
		{
			m_storage = HK_PADSPU_PROMOTE(e);
		}

		HK_ALWAYS_INLINE TYPE val() const
		{
			return HK_PADSPU_EXTRACT(m_storage);
		}

		HK_ALWAYS_INLINE TYPE& ref() const
		{
			return *(TYPE*)&m_storage;
		}

		HK_ALWAYS_INLINE TYPE operator->() const
		{
			return HK_PADSPU_EXTRACT(m_storage);
		}

		HK_ALWAYS_INLINE operator TYPE() const
		{
			return HK_PADSPU_EXTRACT(m_storage);
		}

		HK_ALWAYS_INLINE void operator+=(TYPE e)
		{
			*this = val() + e;
		}

		HK_ALWAYS_INLINE void operator|=(TYPE e)
		{
			*this = val() | e;
		}

		HK_ALWAYS_INLINE void operator&=(TYPE e)
		{
			*this = val() & e;
		}

		HK_ALWAYS_INLINE void operator-=(TYPE e)
		{
			*this = val() - e;
		}

		HK_ALWAYS_INLINE hkPadSpu& operator++()
		{
			operator+=(1);
			return *this;
		}

		HK_ALWAYS_INLINE TYPE operator++(int)
		{
			const TYPE value = val();
			operator+=(1);
			return value;
		}

		HK_ALWAYS_INLINE hkPadSpu& operator--()
		{
			operator-=(1);
			return *this;
		}

		HK_FORCE_INLINE TYPE operator--(int)
		{
			const TYPE value = val();
			operator-=(1);
			return value;
		}

	private:

		TYPE m_storage;
};

/// a simple success/failure enum.
enum hkResultEnum
{
	HK_SUCCESS = 0,
	HK_FAILURE = 1
};


/// A return type for functions.
struct hkResult
{
	//+hk.MemoryTracker(ignore=True)

	HK_FORCE_INLINE hkResult()
	{
	}

	// In debug, force the constructor and operator= to be out of line.
	// This allows us to put conditional breakpoints in to detect when an HK_FAILURE is generated.
#if defined(HK_DEBUG) && !defined(HK_COMPILER_GHS)
	HK_NEVER_INLINE
#else
	HK_FORCE_INLINE
#endif
		hkResult(hkResultEnum b)
	{
		m_enum = b;
	}


#if defined(HK_DEBUG) && !defined(HK_COMPILER_GHS)
	HK_NEVER_INLINE
#else
	HK_FORCE_INLINE
#endif
		hkResult& operator=(hkResultEnum e)
	{
		m_enum = e;
		return *this;
	}

	HK_FORCE_INLINE bool operator==(hkResultEnum e) const
	{
		return m_enum == e;
	}

	HK_FORCE_INLINE bool operator!=(hkResultEnum e) const
	{
		return m_enum != e ;
	}

	HK_FORCE_INLINE hkBool32 isSuccess() const
	{
		return m_enum ^ HK_FAILURE;
	}

	public:
		hkResultEnum m_enum;
};

inline bool operator==(hkResultEnum e, hkResult r){ return r.m_enum == e; }
inline bool operator!=(hkResultEnum e, hkResult r){ return r.m_enum != e; }



#	define HK_PAD_ON_SPU(TYPE)	TYPE
#	define HK_PADSPU_REF(VALUE)	VALUE
#	define HK_ON_CPU(code)		code
#	define HK_ON_SPU(code)
#	define HK_CPU_ARG(code)		, code
#	define HK_SPU_ARG(code)


#define HK_HINT_SIZE16(A) hkInt16(A)


namespace hkCompileError
{
	template <bool b> struct VAR_UNROLL_X_OUT_OF_RANGE;
	template <> struct VAR_UNROLL_X_OUT_OF_RANGE<true>{ };
}


#define hkVAR_UNROLL(x,c)	HK_MULTILINE_MACRO_BEGIN \
{	\
	HK_COMPILE_TIME_ASSERT2( (x) <= 4, VAR_UNROLL_X_OUT_OF_RANGE );	\
{ const int hkI = 0%(x); if ( 0 < (x) ){c;} }	\
{ const int hkI = 1%(x); if ( 1 < (x) ){c;} }	\
{ const int hkI = 2%(x); if ( 2 < (x) ){c;} }	\
{ const int hkI = 3%(x); if ( 3 < (x) ){c;} }	\
}	\
	HK_MULTILINE_MACRO_END



// This hkStruckPackingCheck checks whether hkUint64 data elements are aligned
// on 8 bytes boundaries. This is an implicit assumption that the current serialization
// system relies on, and this compile time check will make sure that it is true
// (at least on windows platforms).
#if defined(HK_PLATFORM_WIN32) && !defined(__HAVOK_PARSER__)
// Remove struct packing check from LLVM parsing.

namespace hkStructPackingCheck
{
	struct PackTester
	{
		hkUint32 m_a;
		hkUint64 m_b;
	};

	// Compile-time check to check the compiler settings for struct alignment.
	// Havok relies on the default structure packing of 8 bytes. If a different
	// struct alignment is used (for example by another 3rd party library),
	// use the following code to wrap all Havok includes:
	// #pragma pack( push, 8 )
	// #include "any havok include"
	// #pragma pack( pop )
	template <bool b> struct STRUCT_PACKING_IS_NOT_DEFAULT;
	template <> struct STRUCT_PACKING_IS_NOT_DEFAULT<true>{ };
	enum 
	{
		IsDefaultPacking = (sizeof(PackTester) == 16),
		Token = sizeof(STRUCT_PACKING_IS_NOT_DEFAULT< bool(IsDefaultPacking) >)
	};
}

#endif

struct hkCountOfBadArgCheck
{
	//+hk.MemoryTracker(ignore=True)
	class ArgIsNotAnArray;
	template<typename T> static ArgIsNotAnArray isArrayType(const T*, const T* const*);
	static int isArrayType(const void*, const void*);
};

	/// Returns the number of elements in the C array.
#define HK_COUNT_OF(x) ( \
	0 * sizeof( reinterpret_cast<const ::hkCountOfBadArgCheck*>(x) ) + \
	0 * sizeof( ::hkCountOfBadArgCheck::isArrayType((x), &(x)) ) + \
	sizeof(x) / sizeof((x)[0]) ) 

#	define HK_SPU_INIT_STACK_SIZE_TRACE()
#	define HK_SPU_UPDATE_STACK_SIZE_TRACE()
#	define HK_SPU_OUTPUT_STACK_SIZE_TRACE()
#	define HK_SPU_BSS_GUARD_INIT()
#	define HK_SPU_BSS_GUARD_CHECK()
#	define HK_SPU_STACK_POINTER_CHECK()

#ifndef HK_PASS_IN_REG 
	#define HK_PASS_IN_REG 
#endif

#endif // HKBASE_HKBASETYPES_H

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
