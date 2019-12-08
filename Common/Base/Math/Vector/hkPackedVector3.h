/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKMATH_MATH_PACKED_VECTOR3_H
#define HKMATH_MATH_PACKED_VECTOR3_H

#include <Common/Base/Math/Vector/hkIntVector.h>

/// Compressed 8 byte sized float vector3 with 1 sign bit, 15 bit mantissa and a shared 8 bit exponent.
/// 
/// This class is great to store positions or normals using an accuracy of 1.0f/32000
/// (e.g., a position which is 100meters off the origin has a precision of +-3mm.
/// pack() takes a little time (~100-200 cycles), unpack is pretty fast on SIMD platforms (6 assembly instructions).
/// See also hkPackedUnitVector and hkVectorPackUtil.
struct hkPackedVector3
{
	public:

		HK_DECLARE_REFLECTION();

		/// pack a vector4 into this
		void pack( hkVector4fParameter v );
		/// pack a vector4 into this
		void pack( hkVector4dParameter v );

		/// unpack
		HK_FORCE_INLINE void unpack( hkVector4f& vOut ) const
		{
			// bring m_values into the high bits
			hkIntVector iv;		
			{
				iv.loadNotAligned<2>( (const hkUint32*)m_values ); // loads 2*uint32 = 4*uint16
				hkIntVector zero; zero.setZero();
				iv.setCombineHead16To32( iv, zero );
			}

			// cast to integer
			hkVector4f v;		iv.convertS32ToF32( v );

			// calculate the exp correction
			hkIntVector iexp; iexp.setBroadcast<3>(iv);
			hkVector4f vexp; iexp.storeAsFloat32BitRepresentation( vexp );
			v.mul( vexp );

			vOut = v;
		}

		/// unpack
		HK_FORCE_INLINE void unpack( hkVector4d& vOut ) const
		{
			// bring m_values into the high bits
			hkIntVector iv;		
			{
				iv.loadNotAligned<2>( (const hkUint32*)m_values ); // loads 2*uint32 = 4*uint16
				hkIntVector zero; zero.setZero();
				iv.setCombineHead16To32( iv, zero );
			}

			const int* iiv = (const int*)&iv;
			const hkFloat32 fexp = *((const hkFloat32*)&iiv[3]);
			vOut.set( hkFloat32(hkFloat32(iiv[0]) * fexp), hkFloat32(hkFloat32(iiv[1]) * fexp), hkFloat32(hkFloat32(iiv[2]) * fexp) );
		}

		/// unpack assuming this is aligned to a 16 byte boundary
		HK_FORCE_INLINE void unpackAligned16( hkVector4f& vOut ) const
		{
			// bring m_values into the high bits
			hkIntVector iv;		
			{
				iv.load<2>( (const hkUint32*)m_values ); // loads 2*uint32 = 4*uint16
				hkIntVector zero; zero.setZero();
				iv.setCombineHead16To32( iv, zero );
			}

			// cast to integer
			hkVector4f v;		iv.convertS32ToF32( v );

			// calculate the exp correction
			hkIntVector iexp; iexp.setBroadcast<3>(iv);
			hkVector4f vexp; iexp.storeAsFloat32BitRepresentation( vexp );
			v.mul( vexp );

			vOut = v;
		}

		/// unpack assuming this is aligned to a 16 byte boundary
		HK_FORCE_INLINE void unpackAligned16( hkVector4d& vOut ) const
		{
			// bring m_values into the high bits
			hkIntVector iv;		
			{
				iv.load<2>( (const hkUint32*)m_values ); // loads 2*uint32 = 4*uint16
				hkIntVector zero; zero.setZero();
				iv.setCombineHead16To32( iv, zero );
			}

			const int* iiv = (const int*)&iv;
			const hkFloat32 fexp = *((const hkFloat32*)&iiv[3]);
			vOut.set( hkFloat32(hkFloat32(iiv[0]) * fexp), hkFloat32(hkFloat32(iiv[1]) * fexp), hkFloat32(hkFloat32(iiv[2]) * fexp) );
		}

	public:
		HK_ALIGN( hkInt16 m_values[4], 8 );
};

extern const hkUint32 hkPackedVector8_3_exponentCorrection[4];

/// Compressed 4 byte sized float vector3 with 1 sign bit, 7 bit mantissa and a shared 8 bit exponent.
/// 
/// This class is great to store velocities in a network environment.
/// pack() takes a little time (~100-200 cycles), unpack is pretty fast on SIMD platforms (7 assembly instructions).
/// See also hkPackedUnitVector and hkVectorPackUtil.
struct hkPackedVector8_3		// aligning members break serialization, so we need to do it here
{
public:

	HK_DECLARE_REFLECTION();

	/// pack a vector4 into this
	void pack( hkVector4fParameter v );
	void pack( hkVector4dParameter v );

	/// unpack
	HK_FORCE_INLINE void unpack( hkVector4f& vOut ) const
	{
		// bring m_values into the high bits
		hkIntVector iv;		
		{
			iv.loadNotAligned<1>( (const hkUint32*)m_values ); // loads 1*uint32 = 4*uint8
			hkIntVector zero; zero.setZero();
			iv.setCombineHead8To16( iv, zero );
			iv.setCombineHead16To32( iv, zero );
		}

		// cast to integer
		hkVector4f v;		iv.convertS32ToF32( v );

		// calculate the exp correction
		hkIntVector iexp; iexp.setBroadcast<3>(iv);
		iexp.setShiftRight32<1>(iexp); // shift the exponent to the right place
		hkVector4f vexp; iexp.storeAsFloat32BitRepresentation( vexp );
		v.mul( vexp );

		vOut = v;
	}

	HK_FORCE_INLINE void unpack( hkVector4d& vOut ) const
	{
		// bring m_values into the high bits
		hkIntVector iv;		
		{
			iv.loadNotAligned<1>( (const hkUint32*)m_values ); // loads 1*uint32 = 4*uint8
			hkIntVector zero; zero.setZero();
			iv.setCombineHead8To16( iv, zero );
			iv.setCombineHead16To32( iv, zero );
		}

		// cast to integer
		hkVector4d v;		iv.convertS32ToF32( v );

		// calculate the exp correction
		hkIntVector iexp; iexp.setBroadcast<3>(iv);
		iexp.setShiftRight32<1>(iexp); // shift the exponent to the right place
		hkVector4d vexp; iexp.storeAsFloat32BitRepresentation( vexp );
		v.mul( vexp );

		vOut = v;
	}

public:
	hkInt8 m_values[4];	// HK_ALIGN(xx,4) is not supported by Havok reflection yet.
};


extern const hkUint32 hkPackedUnitVector_m_offset[4];

#ifdef HK_ARCH_ARM
#	define HK_VECTOR4f_ALIGN_CHECK 0x7
#else
#	define HK_VECTOR4f_ALIGN_CHECK (HK_FLOAT_ALIGNMENT-1)
#endif

/// Store a set of unit values (normals/quaternions (1-4 floats)) using 15 bit accuracy
template<int NUM_ELEMS>
class hkPackedUnitVector
{
	public:

		HK_FORCE_INLINE void set(int x, int y, int z, int w = int(0))
		{
			set(hkFloat32(x), hkFloat32(y), hkFloat32(z), hkFloat32(w));
		}

		HK_FORCE_INLINE void set(hkFloat32 x, hkFloat32 y, hkFloat32 z, hkFloat32 w = hkFloat32(0))
		{
			HK_COMPILE_TIME_ASSERT( NUM_ELEMS >= 3 );
			hkVector4f v; v.set(x,y,z,w);
			pack(v);
		}

		HK_FORCE_INLINE void set(hkDouble64 x, hkDouble64 y, hkDouble64 z, hkDouble64 w = hkDouble64(0))
		{
			HK_COMPILE_TIME_ASSERT( NUM_ELEMS >= 3 );
			hkVector4d v; v.set(x,y,z,w);
			pack(v);
		}

		HK_FORCE_INLINE void set(hkSimdFloat32Parameter x, hkSimdFloat32Parameter y, hkSimdFloat32Parameter z, hkSimdFloat32Parameter w)
		{
			HK_COMPILE_TIME_ASSERT( NUM_ELEMS >= 4 );
			hkVector4f v; v.set(x,y,z,w);
			pack(v);
		}

		HK_FORCE_INLINE void set(hkSimdDouble64Parameter x, hkSimdDouble64Parameter y, hkSimdDouble64Parameter z, hkSimdDouble64Parameter w)
		{
			HK_COMPILE_TIME_ASSERT( NUM_ELEMS >= 4 );
			hkVector4d v; v.set(x,y,z,w);
			pack(v);
		}

		HK_FORCE_INLINE void setZero()
		{
			m_vec[0] = 0x8000;
			if ( NUM_ELEMS >=2 ) m_vec[1%NUM_ELEMS] = 0x8000;
			if ( NUM_ELEMS >=3 ) m_vec[2%NUM_ELEMS] = 0x8000;
			if ( NUM_ELEMS >=4 ) m_vec[3%NUM_ELEMS] = 0x8000;
		}

		/// pack the vector
		HK_FORCE_INLINE void pack( hkVector4fParameter vIn )
		{
			hkVector4f v; v.setMul( hkVector4f::getConstant<HK_QUADREAL_PACK16_UNIT_VEC>(), vIn );
			hkIntVector iv32; iv32.setConvertF32toS32( v );
			iv32.setAddU32(iv32, *(const hkIntVector*)hkPackedUnitVector_m_offset);
#if (HK_ENDIAN_BIG) 
			const int hoffset = 0;	// extract the high word
#else
			const int hoffset = 1;
#endif
			m_vec[0] = iv32.getU16<hoffset>();
			if ( NUM_ELEMS >=2 ) m_vec[1%NUM_ELEMS] = iv32.getU16<2+hoffset>();
			if ( NUM_ELEMS >=3 ) m_vec[2%NUM_ELEMS] = iv32.getU16<4+hoffset>();
			if ( NUM_ELEMS >=4 ) m_vec[3%NUM_ELEMS] = iv32.getU16<6+hoffset>();
		}

		/// pack the vector
		HK_FORCE_INLINE void pack( hkVector4dParameter vIn )
		{
			hkVector4d v; v.setMul( hkVector4d::getConstant<HK_QUADREAL_PACK16_UNIT_VEC>(), vIn );
			hkIntVector iv32; iv32.setConvertF32toS32( v );
			iv32.setAddU32(iv32, *(const hkIntVector*)hkPackedUnitVector_m_offset);
#if (HK_ENDIAN_BIG) 
			const int hoffset = 0;	// extract the high word
#else
			const int hoffset = 1;
#endif
			m_vec[0] = iv32.getU16<hoffset>();
			if ( NUM_ELEMS >=2 ) m_vec[1%NUM_ELEMS] = iv32.getU16<2+hoffset>();
			if ( NUM_ELEMS >=3 ) m_vec[2%NUM_ELEMS] = iv32.getU16<4+hoffset>();
			if ( NUM_ELEMS >=4 ) m_vec[3%NUM_ELEMS] = iv32.getU16<6+hoffset>();
		}


		// unpack
		HK_FORCE_INLINE void unpack( hkVector4f* HK_RESTRICT vecOut ) const
		{
			HK_ASSERT( 0xf04523ef, (hkUlong(vecOut) & HK_VECTOR4f_ALIGN_CHECK) == 0 );
			hkIntVector zero; zero.setZero();
			hkIntVector iv16; iv16.loadNotAligned<(NUM_ELEMS+1)/2>( (hkUint32*)&m_vec[0]);
			hkIntVector iv32; iv32.setCombineHead16To32( iv16, zero );
			iv32.setAddU32( iv32, *(const hkIntVector*)hkPackedUnitVector_m_offset);
			hkVector4f v; iv32.convertS32ToF32( v );
			vecOut->setMul( hkVector4f::getConstant<HK_QUADREAL_UNPACK16_UNIT_VEC>(), v );
		}

		// unpack
		HK_FORCE_INLINE void unpack( hkVector4d* HK_RESTRICT vecOut ) const
		{
			HK_ASSERT( 0xf04523ef, (hkUlong(vecOut) & HK_VECTOR4f_ALIGN_CHECK) == 0 );
			hkIntVector zero; zero.setZero();
			hkIntVector iv16; iv16.loadNotAligned<(NUM_ELEMS+1)/2>( (hkUint32*)&m_vec[0]);
			hkIntVector iv32; iv32.setCombineHead16To32( iv16, zero );
			iv32.setAddU32( iv32, *(const hkIntVector*)hkPackedUnitVector_m_offset);
			hkVector4d v; iv32.convertS32ToF32( v );
			vecOut->setMul( hkVector4d::getConstant<HK_QUADREAL_UNPACK16_UNIT_VEC>(), v );
		}

		/// Gets the vector assuming that this instance is aligned on a 16 byte boundary
		HK_FORCE_INLINE void unpackAligned16( hkVector4f* HK_RESTRICT vecOut ) const
		{
			HK_COMPILE_TIME_ASSERT( NUM_ELEMS <= 4 );
			HK_ASSERT( 0xf04523ed, (hkUlong(this) & 0xf) == 0 );
			HK_ASSERT( 0xf04523ef, (hkUlong(vecOut) & HK_VECTOR4f_ALIGN_CHECK) == 0 );
			hkIntVector iv16 = *( (hkIntVector*)&m_vec[0]);
			hkIntVector iv32; iv32.setCombineHead16To32( iv16, hkIntVector::getConstant<HK_QUADINT_0>() );
			iv32.setAddU32( iv32, *(const hkIntVector*)hkPackedUnitVector_m_offset);
			hkVector4f v; iv32.convertS32ToF32( v );
			vecOut->setMul( hkVector4f::getConstant<HK_QUADREAL_UNPACK16_UNIT_VEC>(), v );
		}

		/// Gets the vector assuming that this instance is aligned on a 16 byte boundary
		HK_FORCE_INLINE void unpackAligned16( hkVector4d* HK_RESTRICT vecOut ) const
		{
			HK_COMPILE_TIME_ASSERT( NUM_ELEMS <= 4 );
			HK_ASSERT( 0xf04523ed, (hkUlong(this) & 0xf) == 0 );
			HK_ASSERT( 0xf04523ef, (hkUlong(vecOut) & HK_VECTOR4f_ALIGN_CHECK) == 0 );
			hkIntVector iv16 = *( (hkIntVector*)&m_vec[0]);
			hkIntVector iv32; iv32.setCombineHead16To32( iv16, hkIntVector::getConstant<HK_QUADINT_0>() );
			iv32.setAddU32( iv32, *(const hkIntVector*)hkPackedUnitVector_m_offset);
			hkVector4d v; iv32.convertS32ToF32( v );
			vecOut->setMul( hkVector4d::getConstant<HK_QUADREAL_UNPACK16_UNIT_VEC>(), v );
		}

	protected:
		hkUint16 m_vec[NUM_ELEMS];	
};

#undef HK_VECTOR4f_ALIGN_CHECK

#endif //HKMATH_MATH_PACKED_VECTOR3_H

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
