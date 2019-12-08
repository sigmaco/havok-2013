/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKBASE_HKUFLOAT8_H
#define HKBASE_HKUFLOAT8_H

#define HK_UFLOAT8_MAX_VALUE 256

/// A wrapper to store an unsigned float into 8 bit.
/// This has a reduced range. Basically the encoding
/// uses a table holding an exponential function.
/// The range is [0.010f to 1000002.f] with an average error of 7%
class hkUFloat8
{
	//+hk.MemoryTracker(ignore=True)
public:

	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, hkUFloat8);
	HK_DECLARE_REFLECTION();
	HK_DECLARE_POD_TYPE();

	enum
	{
		MAX_VALUE = HK_UFLOAT8_MAX_VALUE,

		// Constants used in compressing / decompressing the values table
		ENCODED_EXPONENT_BITS	= 5,
		ENCODED_MANTISSA_BITS	= (16 - ENCODED_EXPONENT_BITS),
		ENCODED_EXPONENT_BIAS	= 119,
		ENCODED_EXPONENT_MASK	= (1 << ENCODED_EXPONENT_BITS) - 1,
		ENCODED_MANTISSA_MASK	= (1 << ENCODED_MANTISSA_BITS) - 1,

		FLOAT_MANTISSA_BITS		= 23,
		FLOAT_MANTISSA_MASK		= (1 << FLOAT_MANTISSA_BITS) - 1,

		ENCODE_MANTISSA_SHIFT	= (FLOAT_MANTISSA_BITS - ENCODED_MANTISSA_BITS),
		DECODE_EXPONENT_BIAS	= (ENCODED_EXPONENT_BIAS << (FLOAT_MANTISSA_BITS - ENCODE_MANTISSA_SHIFT)),
	};

	// the minimum value to encode which is non zero
#define hkUFloat8_eps 0.01f

	// the maximum value to encode
#define hkUFloat8_maxValue 1000000.0f

	HK_FORCE_INLINE hkUFloat8(){		}

	hkUFloat8& operator=(const double& dv);
	hkUFloat8& operator=(const float& fv);

	HK_FORCE_INLINE bool isZero() const { return m_value == 0; }
	HK_FORCE_INLINE void setZero(){ m_value = 0; }

	HK_FORCE_INLINE bool isMax() const { return m_value == 255; }
	HK_FORCE_INLINE void setMax(){ m_value = 255; }

	HK_FORCE_INLINE hkBool operator==( const hkUFloat8& other ) const 
	{
		return m_value == other.m_value;
	}

	HK_FORCE_INLINE hkUFloat8(const float f)
	{
		*this = f;
	}

	HK_FORCE_INLINE hkUFloat8(const double d)
	{
		*this = d;
	}

	/// this = sqrt(a*b)
	HK_FORCE_INLINE void setArithmeticMean( const hkUFloat8& a, const hkUFloat8& b)
	{
		m_value = hkUint8( (int(a.m_value) + int(b.m_value) )>>1 );
	}

	HK_FORCE_INLINE operator float() const
	{
		return decodeFloat(getEncodedFloat(m_value));
	}

	static HK_FORCE_INLINE float HK_CALL decodeFloat(const hkUint16 i)
	{
		const int intExpo = (i + hkUFloat8::DECODE_EXPONENT_BIAS) << hkUFloat8::ENCODE_MANTISSA_SHIFT;
		union { const float* f; const int* i; } f2i;	f2i.i = &intExpo;
		return i ? *f2i.f : 0.0f;
	}

public:

	hkUint8 m_value;

protected:

	/// Function used to access the table of encoded float values. Required to make sure that the 
	/// table is initialized before any construction occurs
	static hkUint16 HK_CALL getEncodedFloat(hkUint8 index);
};

#endif // HKBASE_HKUFLOAT8_H

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
