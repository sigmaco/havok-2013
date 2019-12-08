/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_MATH_MATH_FUNCS_H
#define HK_MATH_MATH_FUNCS_H

#define HK_INT32_MIN		(-2147483647 - 1)	// Minimum (signed) int 32-bit value
#define HK_INT32_MAX		2147483647			// Maximum (signed) int 32-bit value
#define HK_SIMD_FLOAT(x)		hkSimdFloat32(x)

#	define HK_FLOAT_PI			3.14159265358979f
#	define HK_FLOAT_DEG_TO_RAD	(HK_FLOAT_PI / 180.0f)
#	define HK_FLOAT_RAD_TO_DEG	(180.0f / HK_FLOAT_PI)
#	define HK_FLOAT_EPSILON		FLT_EPSILON			// smallest such that 1.0+FLT_EPSILON != 1.0
#	define HK_FLOAT_MIN			FLT_MIN				// min positive value
#	define HK_FLOAT_MAX			3.40282e+38f		// max value - not actually FLT_MAX since on some systems
// FLT_MAX is indistinguishable from NaN or Inf which we reserve
// for error checking.
#	define HK_FLOAT_HIGH		1.8446726e+019f		// Slightly less that sqrt(HK_FLOAT_MAX).

#define HK_SIMD_DOUBLE(x)		hkSimdDouble64(x)

#	define HK_DOUBLE_PI			3.1415926535897932384626433832795
#	define HK_DOUBLE_DEG_TO_RAD	(HK_DOUBLE_PI / 180.0)
#	define HK_DOUBLE_RAD_TO_DEG	(180.0 / HK_DOUBLE_PI)
#	define HK_DOUBLE_EPSILON		DBL_EPSILON			// smallest such that 1.0+DBL_EPSILON != 1.0
#	define HK_DOUBLE_MIN			DBL_MIN				// min positive value
#	define HK_DOUBLE_MAX			1.7970e+308		// max value - not actually DBL_MAX since on some systems
// FLT_MAX is indistinguishable from NaN or Inf which we reserve
// for error checking.
#	define HK_DOUBLE_HIGH		1.8446726e+150		// Slightly less that sqrt(HK_DOUBLE_MAX).



//
// math functions, might have special implementations on some platforms
//
namespace hkMath
{

#if !defined(HK_MATH_sqrt) && !defined(HK_MATH_sqrt_f)
	HK_FORCE_INLINE static hkFloat32 HK_CALL sqrt(const hkFloat32 r) 
	{ 
		return HK_STD_NAMESPACE::sqrtf(r); 
	}
#endif
#if !defined(HK_MATH_sqrt) && !defined(HK_MATH_sqrt_d)
	HK_FORCE_INLINE static hkDouble64 HK_CALL sqrt(const hkDouble64 r) 
	{ 
		return HK_STD_NAMESPACE::sqrt(r); 
	}
#endif


#if !defined(HK_MATH_sqrtInverse) && !defined(HK_MATH_sqrtInverse_f)
	HK_FORCE_INLINE static hkFloat32 HK_CALL sqrtInverse(const hkFloat32 r) 
	{ 
		return 1.0f / hkMath::sqrt(r); 
	}
#endif
#if !defined(HK_MATH_sqrtInverse) && !defined(HK_MATH_sqrtInverse_d)
	HK_FORCE_INLINE static hkDouble64 HK_CALL sqrtInverse(const hkDouble64 r) 
	{ 
		return 1.0 / hkMath::sqrt(r); 
	}
#endif

#if !defined(HK_MATH_fabs) && !defined(HK_MATH_fabs_f)
	HK_FORCE_INLINE static hkFloat32 HK_CALL fabs(const hkFloat32 r) 
	{ 
		return HK_STD_NAMESPACE::fabsf(r); 
	}
#endif
#if !defined(HK_MATH_fabs) && !defined(HK_MATH_fabs_d)
	HK_FORCE_INLINE static hkDouble64 HK_CALL fabs(const hkDouble64 r) 
	{ 
		return HK_STD_NAMESPACE::fabs(r); 
	}
#endif


#if !defined(HK_MATH_abs)
	template<typename T>
	HK_FORCE_INLINE static T HK_CALL abs(T t) { return t < T(0) ? -t : t; }
	// this GCC has a setting to disallow storage modifiers on specializations
	template<>
	HK_FORCE_INLINE hkFloat32 HK_CALL abs(hkFloat32 r) { return hkMath::fabs(r); }
	template<>
	HK_FORCE_INLINE hkDouble64 HK_CALL abs(hkDouble64 r) { return hkMath::fabs(r); }
#endif


#if !defined(HK_MATH_pow) && !defined(HK_MATH_pow_f)
	HK_FORCE_INLINE static hkFloat32 HK_CALL pow( const hkFloat32 r, const hkFloat32 s ) 
	{ 
		return HK_STD_NAMESPACE::powf( r, s ); 
	}
#endif
#if !defined(HK_MATH_pow) && !defined(HK_MATH_pow_d)
	HK_FORCE_INLINE static hkDouble64 HK_CALL pow( const hkDouble64 r, const hkDouble64 s ) 
	{ 
		return HK_STD_NAMESPACE::pow( r, s ); 
	}
#endif


#ifndef  HK_MATH_powi
	namespace hkMath_Implementation
	{
		template<unsigned int E, typename T>
		struct unroll_pow 
		{
			HK_FORCE_INLINE static T HK_CALL apply( const T& r )
			{
				return r * (unroll_pow<E-1, T>::apply( r ));
			}
		};

		template<typename T>
		struct unroll_pow<1, T> 
		{
			HK_FORCE_INLINE static T HK_CALL apply( const T& r )
			{
				return r;
			}
		};

		template<typename T>
		struct unroll_pow<0, T> 
		{
			HK_FORCE_INLINE static T HK_CALL apply( const T& r )
			{
				return (T) 1;
			}
		};
	}

	template<unsigned int E, typename T>
	HK_FORCE_INLINE static T HK_CALL pow( const T& r ) 
	{ 
		return hkMath_Implementation::unroll_pow<E, T>::apply(r);
	}

	template<typename T>
	HK_FORCE_INLINE static T HK_CALL square( const T& r ) 
	{ 
		return hkMath::pow<2,T>(r);
	}
#endif

#if !defined(HK_MATH_ceil) && !defined(HK_MATH_ceil_f)
	HK_FORCE_INLINE static hkFloat32 HK_CALL ceil( const hkFloat32 r ) 
	{ 
		return HK_STD_NAMESPACE::ceilf( r ); 
	}
#endif
#if !defined(HK_MATH_ceil) && !defined(HK_MATH_ceil_d)
	HK_FORCE_INLINE static hkDouble64 HK_CALL ceil( const hkDouble64 r ) 
	{ 
		return HK_STD_NAMESPACE::ceil( r ); 
	}
#endif

#if !defined(HK_MATH_sin) && !defined(HK_MATH_sin_f)
	HK_FORCE_INLINE static hkFloat32 HK_CALL sin (const hkFloat32 r) 
	{ 
		return HK_STD_NAMESPACE::sinf(r); 
	}
#endif
#if !defined(HK_MATH_sin) && !defined(HK_MATH_sin_d)
	HK_FORCE_INLINE static hkDouble64 HK_CALL sin (const hkDouble64 r) 
	{ 
		return HK_STD_NAMESPACE::sin(r); 
	}
#endif

#if !defined(HK_MATH_cos) && !defined(HK_MATH_cos_f)
	HK_FORCE_INLINE static hkFloat32 HK_CALL cos (const hkFloat32 r) 
	{ 
		return HK_STD_NAMESPACE::cosf(r); 
	}
#endif
#if !defined(HK_MATH_cos) && !defined(HK_MATH_cos_d)
	HK_FORCE_INLINE static hkDouble64 HK_CALL cos (const hkDouble64 r) 
	{ 
		return HK_STD_NAMESPACE::cos(r); 
	}
#endif

#if !defined(HK_MATH_acos) && !defined(HK_MATH_acos_f)
	HK_FORCE_INLINE static hkFloat32 HK_CALL acos(const hkFloat32 r)
	{
		// be generous about numbers slightly outside range
		HK_ASSERT(0x41278654,  hkMath::fabs(r) < 1.001f );
		if( hkMath::fabs(r) >= 1.0f )
		{
			hkFloat32 ret = ( r>0.0f ) ? 0.0f : float(HK_FLOAT_PI);
			return ret;
		}
		return HK_STD_NAMESPACE::acosf(r);
	}
#endif
#if !defined(HK_MATH_acos) && !defined(HK_MATH_acos_d)
	HK_FORCE_INLINE static hkDouble64 HK_CALL acos(const hkDouble64 r)
	{
		// be generous about numbers slightly outside range
		HK_ASSERT(0x41278654,  hkMath::fabs(r) < 1.001 );
		if( hkMath::fabs(r) >= 1.0 )
		{
			hkDouble64 ret = ( r>0.0 ) ? 0.0 : hkDouble64(HK_DOUBLE_PI);
			return ret;
		}
		return HK_STD_NAMESPACE::acos(r);
	}
#endif

#if !defined(HK_MATH_asin) && !defined(HK_MATH_asin_f)
	HK_FORCE_INLINE static hkFloat32 HK_CALL asin(const hkFloat32 r)
	{
		// be generous about numbers outside range
		HK_ASSERT(0x286a6f5f,  hkMath::fabs(r) < 1.001f );
		if( hkMath::fabs(r) >= 1.0f )
		{
			hkFloat32 ret = ( r>0.0f )	? 0.5f * float(HK_FLOAT_PI) : -0.5f * float(HK_FLOAT_PI);
			return ret;
		}
		return HK_STD_NAMESPACE::asinf(r);
	}
#endif
#if !defined(HK_MATH_asin) && !defined(HK_MATH_asin_d)
	HK_FORCE_INLINE static hkDouble64 HK_CALL asin(const hkDouble64 r)
	{
		// be generous about numbers outside range
		HK_ASSERT(0x286a6f5f,  hkMath::fabs(r) < 1.001 );
		if( hkMath::fabs(r) >= 1.0 )
		{
			hkDouble64 ret = ( r>0.0 )	? 0.5 * hkDouble64(HK_DOUBLE_PI) : -0.5 * hkDouble64(HK_DOUBLE_PI);
			return ret;
		}
		return HK_STD_NAMESPACE::asin(r);
	}
#endif

#if !defined(HK_MATH_log) && !defined(HK_MATH_log_f)
	HK_FORCE_INLINE static hkFloat32 HK_CALL log(const hkFloat32 r)
	{
		return HK_STD_NAMESPACE::logf(r);
	}
#endif
#if !defined(HK_MATH_log) && !defined(HK_MATH_log_d)
	HK_FORCE_INLINE static hkDouble64 HK_CALL log(const hkDouble64 r)
	{
		return HK_STD_NAMESPACE::log(r);
	}
#endif

#if !defined(HK_MATH_atan2) && !defined(HK_MATH_atan2_f)
	HK_FORCE_INLINE static hkFloat32 HK_CALL atan2(const hkFloat32 y, const hkFloat32 x)
	{
		return HK_STD_NAMESPACE::atan2f(y,x);
	}
#endif
#if !defined(HK_MATH_atan2) && !defined(HK_MATH_atan2_d)
	HK_FORCE_INLINE static hkDouble64 HK_CALL atan2(const hkDouble64 y, const hkDouble64 x)
	{
		return HK_STD_NAMESPACE::atan2(y,x);
	}
#endif

#if !defined(HK_MATH_floor) && !defined(HK_MATH_floor_f)
	HK_FORCE_INLINE static hkFloat32 HK_CALL floor(const hkFloat32 r) 
	{ 
		return HK_STD_NAMESPACE::floorf(r); 
	}
#endif
#if !defined(HK_MATH_floor) && !defined(HK_MATH_floor_d)
	HK_FORCE_INLINE static hkDouble64 HK_CALL floor(const hkDouble64 r) 
	{ 
		return HK_STD_NAMESPACE::floor(r); 
	}
#endif

#if !defined(HK_MATH_fmod) && !defined(HK_MATH_fmod_f)
	HK_FORCE_INLINE static hkFloat32 HK_CALL fmod(const hkFloat32 n, const hkFloat32 d) 
	{ 
		return HK_STD_NAMESPACE::fmodf(n,d); 
	}
#endif
#if !defined(HK_MATH_fmod) && !defined(HK_MATH_fmod_d)
	HK_FORCE_INLINE static hkDouble64 HK_CALL fmod(const hkDouble64 n, const hkDouble64 d) 
	{ 
		return HK_STD_NAMESPACE::fmod(n,d); 
	}
#endif

	HK_FORCE_INLINE static hkFloat32 HK_CALL rcpF32Approx23Bit(const hkFloat32 x);
	HK_FORCE_INLINE static hkFloat32 HK_CALL invSqrtF32Approx23Bit(const hkFloat32 x);

	namespace FallbackImpl
	{
		template<typename T> struct TypesForQuadType {};
		template<> struct TypesForQuadType<hkQuadFloat32> { typedef hkVector4f VType; typedef hkFloat32 RType; };
		template<> struct TypesForQuadType<hkQuadDouble64> { typedef hkVector4d VType; typedef hkDouble64 RType; };

		template<typename T>
		HK_FORCE_INLINE static T HK_CALL quadReciprocal( const T& r )
		{
			typedef typename TypesForQuadType<T>::VType VType;
			typedef typename TypesForQuadType<T>::RType RType;

			VType q;
			q.set(	RType(rcpF32Approx23Bit(hkFloat32(r.v[0]))), 
					RType(rcpF32Approx23Bit(hkFloat32(r.v[1]))), 
					RType(rcpF32Approx23Bit(hkFloat32(r.v[2]))),
					RType(rcpF32Approx23Bit(hkFloat32(r.v[3])))
					);
			return q.m_quad;
		}

		template<typename T>
		HK_FORCE_INLINE static T HK_CALL quadReciprocalSquareRoot( const T& r )
		{
			typedef typename TypesForQuadType<T>::VType VType;
			typedef typename TypesForQuadType<T>::RType RType;

			VType q;
			q.set(	RType(invSqrtF32Approx23Bit(hkFloat32(r.v[0]))), 
					RType(invSqrtF32Approx23Bit(hkFloat32(r.v[1]))), 
					RType(invSqrtF32Approx23Bit(hkFloat32(r.v[2]))),
					RType(invSqrtF32Approx23Bit(hkFloat32(r.v[3])))
					);
			return q.m_quad;
		}

		template<typename T>
		HK_FORCE_INLINE static T HK_CALL quadReciprocalTwoIter( const T& r )
		{
			typedef typename TypesForQuadType<T>::VType VType;
			typedef typename TypesForQuadType<T>::RType RType;

			VType q;
			q.set(	RType(1) / r.v[0], RType(1) / r.v[1], RType(1) / r.v[2], RType(1) / r.v[3] );
			return q.m_quad;
		}

		template<typename T>
		HK_FORCE_INLINE static T HK_CALL quadReciprocalSquareRootTwoIter( const T& r )
		{
			typedef typename TypesForQuadType<T>::VType VType;
			typedef typename TypesForQuadType<T>::RType RType;

			VType q;
			q.set(	RType(1) / RType(HK_STD_NAMESPACE::sqrt(r.v[0])), 
					RType(1) / RType(HK_STD_NAMESPACE::sqrt(r.v[1])), 
					RType(1) / RType(HK_STD_NAMESPACE::sqrt(r.v[2])), 
					RType(1) / RType(HK_STD_NAMESPACE::sqrt(r.v[3]))
				);
			return q.m_quad;
		}
	}

#if !defined(HK_MATH_quadReciprocal) && !defined(HK_MATH_quadReciprocal_f)
	HK_FORCE_INLINE static hkQuadFloat32 HK_CALL quadReciprocal( const hkQuadFloat32& r )
	{
		return FallbackImpl::quadReciprocal<hkQuadFloat32>(r);
	}
#endif
#if !defined(HK_MATH_quadReciprocal) && !defined(HK_MATH_quadReciprocal_d)
	HK_FORCE_INLINE static hkQuadDouble64 HK_CALL quadReciprocal( const hkQuadDouble64& r )
	{
		return FallbackImpl::quadReciprocal<hkQuadDouble64>(r);
	}
#endif

		
#if !defined(HK_MATH_quadReciprocalSquareRoot) && !defined(HK_MATH_quadReciprocalSquareRoot_f)
	HK_FORCE_INLINE static hkQuadFloat32 HK_CALL quadReciprocalSquareRoot( const hkQuadFloat32& r )
	{
		return FallbackImpl::quadReciprocalSquareRoot<hkQuadFloat32>(r);
	}
#endif
#if !defined(HK_MATH_quadReciprocalSquareRoot) && !defined(HK_MATH_quadReciprocalSquareRoot_d)
	HK_FORCE_INLINE static hkQuadDouble64 HK_CALL quadReciprocalSquareRoot( const hkQuadDouble64& r )
	{
		return FallbackImpl::quadReciprocalSquareRoot<hkQuadDouble64>(r);
	}
#endif


#if !defined(HK_MATH_quadReciprocalTwoIter) && !defined(HK_MATH_quadReciprocalTwoIter_f)
	HK_FORCE_INLINE static hkQuadFloat32 HK_CALL quadReciprocalTwoIter( const hkQuadFloat32& r )
	{
		return FallbackImpl::quadReciprocalTwoIter<hkQuadFloat32>(r);
	}
#endif
#if !defined(HK_MATH_quadReciprocalTwoIter) && !defined(HK_MATH_quadReciprocalTwoIter_d)
	HK_FORCE_INLINE static hkQuadDouble64 HK_CALL quadReciprocalTwoIter( const hkQuadDouble64& r )
	{
		return FallbackImpl::quadReciprocalTwoIter<hkQuadDouble64>(r);
	}
#endif


#if !defined(HK_MATH_quadReciprocalSquareRootTwoIter) && !defined(HK_MATH_quadReciprocalSquareRootTwoIter_f)
	HK_FORCE_INLINE static hkQuadFloat32 HK_CALL quadReciprocalSquareRootTwoIter( const hkQuadFloat32& r )
	{
		return FallbackImpl::quadReciprocalSquareRootTwoIter<hkQuadFloat32>(r);
	}
#endif
#if !defined(HK_MATH_quadReciprocalSquareRootTwoIter) && !defined(HK_MATH_quadReciprocalSquareRootTwoIter_d)
	HK_FORCE_INLINE static hkQuadDouble64 HK_CALL quadReciprocalSquareRootTwoIter( const hkQuadDouble64& r )
	{
		return FallbackImpl::quadReciprocalSquareRootTwoIter<hkQuadDouble64>(r);
	}
#endif


#ifndef HK_MATH_prefetch128
	HK_FORCE_INLINE static void HK_CALL prefetch128( const void* p) {}
#endif

#ifndef HK_MATH_forcePrefetch
	template<int SIZE>
	HK_FORCE_INLINE static void HK_CALL forcePrefetch( const void* p ) {}
#endif


#if !defined(HK_MATH_signBitSet) && !defined(HK_MATH_signBitSet_f)
	HK_FORCE_INLINE static bool HK_CALL signBitSet(const hkFloat32& r)
	{
		return (*(reinterpret_cast<const unsigned int*>(&r)) & 0x80000000) ? true : false;
	}
#endif
#if !defined(HK_MATH_signBitSet) && !defined(HK_MATH_signBitSet_d)
	HK_FORCE_INLINE static bool HK_CALL signBitSet(const hkDouble64& r)
	{
		return (*(reinterpret_cast<const unsigned long long*>(&r)) & 0x8000000000000000ull) ? true : false;
	}
#endif


#if !defined(HK_MATH_hkFloor) && !defined(HK_MATH_hkFloor_f)
	HK_FORCE_INLINE static hkFloat32 HK_CALL hkFloor(const hkFloat32 r)
	{
		union fiu
		{
			hkFloat32 f;
			int i;
			unsigned u;
		};

		//interpret as int
		fiu convert;
		convert.f = r;

		//mask out the fractional part
		int fracMask = 0xff800000;

		//mask out the sign and mantissa
		unsigned exp = convert.u & 0x7f800000;

		//work out the exponent
		//
		//shift down to bottom of number
		exp >>= 0x017;
		//subtract bias of 127
		exp -= 0x07f;

		//rshift is used to shift the fracmask (down to the fractional part)
		int rshift = 0x17 - int(exp);

		//if the exponent is greater than 0x17 (23 bits), then we don't need a
		//frackmask (there is no fractional part, not enough bits to store it)
		//i.e. if rshift >= 0, then leave alone, otherwise set rshift to zero
		int sign = ~(rshift >> 0x01f);
		rshift &= sign;

		//if none of the bits are set in the original number (see ieee floating point
		//standard), then the number = 0
		//we mask out the sign bit, and check if anything is set
		//if it is, we must keep convert.i, otherwise we can set it to 0
		int nexp = (convert.i) & 0x7fffffff;
		nexp = (nexp - 1) >> 0x01f;
		//if the number had no bits, the sign is also destroyed
		convert.i &= ~nexp;

		//shift down to the fractional part
		//if the exponent had been >= 0x17 (23) then the sign destroys with an AND
		//and preserves with an OR (and vice versa). In the case of sign preserving
		//with AND, we end up with frackmask >> exp, else frackmask = 0xffffffff
		fracMask >>= (0x17 & sign) - rshift;
		fracMask |= ~sign;

		//find out whether the floating point is negative
		//sign -> 0xffffffff if neg. 0x00000000 otherwise
		sign = int(convert.u & 0x80000000);
		sign >>= 0x01f;

		int addMask = 0x00800000;

		//if the number is negative AND NOT whole
		//we increase it's magnitude, this is due
		//to the definition of floor
		addMask >>= int(exp);
		//if negative, do the addition (broadcast with sign)
		addMask &= sign;
		//check to see if there was anything in the fractional part
		addMask &= ~((convert.i & (~fracMask)) - 1);
		convert.i += addMask;

		convert.i &= fracMask;

		//if the exponent is negative AND the number is positive
		//then the number is less than 1.0f and floor sets it to 0.0f
		//if it is negative, it gets set to -1.0f
		nexp = int(exp);
		nexp = nexp >> 0x01f;
		//note: 0xbf800000 is -1.0f - which we need to assign in (easier than calculating)
		exp = (0xbf800000 & nexp) & sign;
		convert.i &= ~nexp;
		convert.u |= exp;

		return convert.f;
	}
#endif
#if !defined(HK_MATH_hkFloor) && !defined(HK_MATH_hkFloor_d)
	HK_FORCE_INLINE static hkDouble64 HK_CALL hkFloor(const hkDouble64 r)
	{
		return hkMath::floor(r);
	}
#endif


#if !defined(HK_MATH_hkFloatToInt) && !defined(HK_MATH_hkFloatToInt_f)
	HK_FORCE_INLINE static int HK_CALL hkFloatToInt(const hkFloat32 r)
	{
		union fiu
		{
			hkFloat32 f;
			int i;
			unsigned u;
		};

		//performs a truncation
		//interpret as int
		fiu convert;
		convert.f = r;

		//mask out the fractional part
		int fracMask = 0xff800000;

		//mask out the sign and mantissa
		unsigned int exp = convert.u & 0x7f800000;

		//work out the exponent
		//
		//shift down to bottom of number
		exp >>= 0x017;
		//subtract bias of 127
		exp -= 0x07f;

		//now split the exp into two shift magnitudes, a left
		//shift and a right shift, one of which must be 0
		int lshift = int(exp) - 0x17;
		int rshift = 0x17 - int(exp);

		//if lshift is <=0, then set to zero, otherwise set rshift to zero
		int sign = (lshift-1) >> 0x01f;
		lshift &= ~sign;
		rshift &= sign;

		//if none of the bits are set in the original number (see ieee floating point
		//standard), then the number = 0
		//we mask out the sign bit, and check if anything is set
		//if it is, we must keep convert.i, otherwise we can set it to 0
		int nexp = (convert.i) & 0x7fffffff;
		nexp = (nexp - 1) >> 0x01f;
		//if the number had no bits, the sign is also destroyed
		convert.i &= ~nexp;

		//shift down to the fractional part
		//if the exponent had been >= 0x17 (23) then the sign destroys with an AND
		//and preserves with an OR (and vice versa). In the case of sign preserving
		//with AND, we end up with frackmask >> exp, else frackmask = 0xffffffff
		fracMask >>= (0x17 & sign) - rshift;
		fracMask |= ~sign;

		//find out whether the floating point is negative
		//sign -> 0xffffffff if neg. 0x00000000 otherwise
		sign = int(convert.u & 0x80000000);
		sign >>= 0x01f;

		//get rid of the exponent and sign
		convert.i &= 0x007fffff;
		//insert the 1 that is assumed in the floating point standard
		convert.i |= 0x00800000;

		//truncate
		convert.i &= fracMask;

		//if the sign is negative, convert to 2's complement
		//otherwise leave untouched (ie subtract x from 0 or
		//subtract from x from 2x => -x or x)
		int temp = 0x0;
		temp = (convert.i << 0x01) - 1;
		temp |= sign;
		convert.i = (temp - convert.i) + 1;

		//if the exponent is negative, then the number is less than 1.0f
		//and float to int truncates that to 0
		nexp = int(exp);
		nexp = ~(nexp >> 0x1f);
		convert.i &= nexp;

		//shift mantissa to correct place (one of these will be zero)
		convert.i >>= rshift;
		convert.i <<= lshift;

		return convert.i;
	}
#endif
#if !defined(HK_MATH_hkFloatToInt) && !defined(HK_MATH_hkFloatToInt_d)
	HK_FORCE_INLINE static int HK_CALL hkFloatToInt(const hkDouble64 r)
	{
		return int(r);
	}
#endif


#if !defined(HK_MATH_hkFloorToInt) && !defined(HK_MATH_hkFloorToInt_f)
	HK_FORCE_INLINE static int HK_CALL hkFloorToInt(const hkFloat32 r)
	{
		union fiu
		{
			hkFloat32 f;
			int i;
			unsigned u;
		};

		//interpret as int
		fiu convert;
		convert.f = r;

		//mask out the fractional part
		int fracMask = 0xff800000;

		//mask out the sign and mantissa
		unsigned exp = convert.u & 0x7f800000;

		//work out the exponent
		//
		//shift down to bottom of number
		exp >>= 0x017;
		//subtract bias of 127
		exp -= 0x07f;

		//now split the exp into two shift magnitudes, a left
		//shift and a right shift, one of which must be 0
		int lshift = int(exp) - 0x17;
		int rshift = 0x17 - int(exp);

		//if lshift is <=0, then set to zero, otherwise set rshift to zero
		int sign = (lshift-1) >> 0x01f;
		lshift &= ~sign;
		rshift &= sign;

		
		// check if shift will result in undefined behavior
		// remove bits greater than sizeof( type )
		// if clipped, set mask to set shift to 0x1f
		int clipShift = ( lshift > 0x1f );
		lshift &= 0x1f;
		clipShift = 0 - clipShift;
		lshift |= ( clipShift & 0x1f );

		// clip rshift
		clipShift = ( rshift > 0x1f );
		rshift &= 0x1f;
		clipShift = 0 - clipShift;
		rshift |= ( clipShift & 0x1f );

		//if none of the bits are set in the original number (see ieee floating point
		//standard), then the number = 0
		//we mask out the sign bit, and check if anything is set
		//if it is, we must keep convert.i, otherwise we can set it to 0
		int nexp = (convert.i) & 0x7fffffff;
		nexp = (nexp - 1) >> 0x01f;
		//if the number had no bits, the sign is also destroyed
		convert.i &= ~nexp;

		//shift down to the fractional part
		//if the exponent had been >= 0x17 (23) then the sign destroys with an AND
		//and preserves with an OR (and vice versa). In the case of sign preserving
		//with AND, we end up with frackmask >> exp, else frackmask = 0xffffffff
		fracMask >>= (0x17 & sign) - rshift;
		fracMask |= ~sign;

		//find out whether the floating point number is whole
		//check if a v large number (lshift will be >= 0, => rshift will == 0)
		int whole = ( ( rshift - 1 ) >> 0x1f );
		//check if not < 1 (fracMask will == -1), and if fraction part == 0
		whole |= ( ( fracMask + 1 ) >> 0x1f ) & ( ( ( convert.i & ~fracMask ) - 1 ) >> 0x1f );

		//find out whether the floating point is negative
		//sign -> 0xffffffff if neg. 0x00000000 otherwise
		sign = int(convert.u & 0x80000000);
		sign >>= 0x01f;

		//get rid of the exponent and sign
		convert.i &= 0x007fffff;
		//insert the 1 that is assumed in the floating point standard
		convert.i |= 0x00800000;

		//truncate
		convert.i &= fracMask;

		//if the sign is negative, convert to 2's complement
		//otherwise leave untouched (ie subtract x from 0 or
		//subtract from x from 2x -> -x or x
		int temp = 0x0;
		temp = (convert.i << 0x01) - 1;
		temp |= sign;
		convert.i = (temp - convert.i) + 1;

		//if the exponent is negative, then the number is less than 1.0f. truncate to 0
		nexp = int(exp);
		nexp = ~(nexp >> 0x1f);
		convert.i &= nexp;

		//shift mantissa to correct place (one of these will be zero)
		convert.i >>= rshift;
		convert.i <<= lshift;

		// floor increases the magnitude of negative, non-whole values by 1
		// subtract 0x01 if negative and not whole
		int incNeg = ( 0x00000001 & sign ) & ~whole;
		convert.i -= incNeg;

		return convert.i;
	}
#endif
#if !defined(HK_MATH_hkFloorToInt) && !defined(HK_MATH_hkFloorToInt_d)
	HK_FORCE_INLINE static int HK_CALL hkFloorToInt(const hkDouble64 r)
	{
		return int(hkMath::floor(r));
	}
#endif

#if !defined(HK_MATH_hkToIntFast) && !defined(HK_MATH_hkToIntFast_f)
	HK_FORCE_INLINE static int HK_CALL hkToIntFast( const hkFloat32 r )
	{
		return int(r);
	}
#endif
#if !defined(HK_MATH_hkToIntFast) && !defined(HK_MATH_hkToIntFast_d)
	HK_FORCE_INLINE static int HK_CALL hkToIntFast( const hkDouble64 r )
	{
		return int(r);
	}
#endif

#ifndef HK_MATH_equal
	HK_FORCE_INLINE static bool HK_CALL equal(hkFloat32 x, hkFloat32 y, hkFloat32 tolerance2)
	{
		return hkMath::fabs(x-y) <= tolerance2;
	}
	HK_FORCE_INLINE static bool HK_CALL equal(hkDouble64 x, hkDouble64 y, hkDouble64 tolerance2)
	{
		return hkMath::fabs(x-y) <= tolerance2;
	}
	HK_FORCE_INLINE static bool HK_CALL equal(hkFloat32 x, hkFloat32 y)
	{
		return equal(x, y, 1e-5f);
	}
	HK_FORCE_INLINE static bool HK_CALL equal(hkDouble64 x, hkFloat32 y)
	{
		return equal(hkFloat32(x), y, 1e-5f);
	}
	HK_FORCE_INLINE static bool HK_CALL equal(hkDouble64 x, hkFloat32 y, hkFloat32 tolerance2)
	{
		return equal(hkFloat32(x), y, 1e-5f);
	}
	HK_FORCE_INLINE static bool HK_CALL equal(hkFloat32 x, hkDouble64 y)
	{
		return equal(x, hkFloat32(y));
	}
	HK_FORCE_INLINE static bool HK_CALL equal(hkFloat32 x, hkDouble64 y, hkFloat32 tolerance2)
	{
		return equal(x, hkFloat32(y), tolerance2);
	}
	HK_FORCE_INLINE static bool HK_CALL equal(hkDouble64 x, hkDouble64 y)
	{
		return equal(x, y, hkDouble64(1e-5));
	}
	HK_FORCE_INLINE static bool HK_CALL equal(hkDouble64 x, hkDouble64 y, hkFloat32 tolerance2)
	{
		return equal(x, y, hkDouble64(tolerance2));
	}

#endif
	

#ifndef HK_MATH_max2
	template <typename T1, typename T2>
	HK_FORCE_INLINE static T1 HK_CALL max2( T1 x, T2 y)
	{
		return x > T1(y) ? x : T1(y);
	}
#endif

	template <typename T>
	HK_FORCE_INLINE static T HK_CALL _max2( T x, T y)
	{
		return max2<T, T>(x, y);
	}

#ifndef HK_MATH_min2
	template <typename T1, typename T2>
	HK_FORCE_INLINE static T1 HK_CALL min2( T1 x, T2 y)
	{
		return x < T1(y) ? x : T1(y);
	}
#endif

	template <typename T>
	HK_FORCE_INLINE static T HK_CALL _min2( T x, T y)
	{
		return min2<T, T>(x, y);
	}

#ifndef HK_MATH_clamp
	template <typename T1, typename T2, typename T3>
	HK_FORCE_INLINE static T1 HK_CALL clamp( T1 x, T2 mi, T3 ma)
	{
		if ( x < mi ) return (T1) mi;
		if ( x > ma ) return (T1) ma;
		return x;
	}
#endif

	template <typename T>
	HK_FORCE_INLINE static T HK_CALL _clamp( T x, T mi, T ma)
	{
		return clamp<T, T, T>(x, mi, ma);
	}


#if !defined(HK_MATH_isFinite) && !defined(HK_MATH_isFinite_f)
	HK_FORCE_INLINE static bool HK_CALL isFinite(const hkFloat32 r)
	{
		// Check the 8 exponent bits.
		// Usually NAN == (exponent = all 1, mantissa = non-zero)
		//         INF == (exponent = all 1, mantissa = zero)
		// This simply checks the exponent
		HK_ASSERT(0x2d910c70, sizeof(hkFloat32) == sizeof(unsigned int));
		union {
			hkFloat32 f;
			unsigned int i;
		} val;

		val.f = r;
		return ((val.i & 0x7f800000) != 0x7f800000);
	}
#endif
#if !defined(HK_MATH_isFinite) && !defined(HK_MATH_isFinite_d)
	HK_FORCE_INLINE static bool HK_CALL isFinite(const hkDouble64 r)
	{
		// Check the 11 exponent bits.
		// Usually NAN == (exponent = all 1, mantissa = non-zero)
		//         INF == (exponent = all 1, mantissa = zero)
		// This simply checks the exponent
		HK_ASSERT(0x2d910c70, sizeof(hkDouble64) == sizeof(unsigned long long));
		union {
			hkDouble64 f;
			unsigned long long i;
		} val;
		val.f = r;
		return ((val.i & 0x7ff0000000000000ull) != 0x7ff0000000000000ull);
	}
#endif	

#ifndef HK_MATH_isPower2
	HK_FORCE_INLINE static bool isPower2(unsigned int v)
	{
		return v && !(v & (v - 1));
	}
#endif


#ifndef HK_MATH_calculateGcd
	/// Calculates the greatest common divisor of A and B (using the Euclidean algorithm)
	HK_FORCE_INLINE static int HK_CALL calculateGcd (int a, int b)
	{
		while (b!=0)
		{
			int t=b;
			b = a % b;
			a=t;
		}

		return a;
	}
#endif

#ifndef HK_MATH_calculateLcm
	/// Calculates the least common multiple of A and B (using the Euclidean algorithm)
	HK_FORCE_INLINE static int HK_CALL calculateLcm (int a, int b)
	{
		return (a*b) / calculateGcd (a,b);
	}
#endif

#if !defined(HK_MATH_fselectGreaterEqualZero) && !defined(HK_MATH_fselectGreaterEqualZero_f)
	HK_FORCE_INLINE static hkFloat32 HK_CALL fselectGreaterEqualZero( hkFloat32 testVar, hkFloat32 ifTrue, hkFloat32 ifFalse)
	{
		return (testVar >= hkFloat32(0)) ? ifTrue : ifFalse;
	}
#endif
#if !defined(HK_MATH_fselectGreaterEqualZero) && !defined(HK_MATH_fselectGreaterEqualZero_d)
	HK_FORCE_INLINE static hkDouble64 HK_CALL fselectGreaterEqualZero( hkDouble64 testVar, hkDouble64 ifTrue, hkDouble64 ifFalse)
	{
		return (testVar >= hkDouble64(0)) ? ifTrue : ifFalse;
	}
#endif

#if !defined(HK_MATH_fselectGreaterZero) && !defined(HK_MATH_fselectGreaterZero_f)
	HK_FORCE_INLINE static hkFloat32 HK_CALL fselectGreaterZero( hkFloat32 testVar, hkFloat32 ifTrue, hkFloat32 ifFalse)
	{
		return (testVar > hkFloat32(0)) ? ifTrue : ifFalse;
	}
#endif
#if !defined(HK_MATH_fselectGreaterZero) && !defined(HK_MATH_fselectGreaterZero_d)
	HK_FORCE_INLINE static hkDouble64 HK_CALL fselectGreaterZero( hkDouble64 testVar, hkDouble64 ifTrue, hkDouble64 ifFalse)
	{
		return (testVar > hkDouble64(0)) ? ifTrue : ifFalse;
	}
#endif

#if !defined(HK_MATH_fselectLessEqualZero) && !defined(HK_MATH_fselectLessEqualZero_f)
	HK_FORCE_INLINE static hkFloat32 HK_CALL fselectLessEqualZero( hkFloat32 testVar, hkFloat32 ifTrue, hkFloat32 ifFalse)
	{
		return (testVar <= hkFloat32(0)) ? ifTrue : ifFalse;
	}
#endif
#if !defined(HK_MATH_fselectLessEqualZero) && !defined(HK_MATH_fselectLessEqualZero_d)
	HK_FORCE_INLINE static hkDouble64 HK_CALL fselectLessEqualZero( hkDouble64 testVar, hkDouble64 ifTrue, hkDouble64 ifFalse)
	{
		return (testVar <= hkDouble64(0)) ? ifTrue : ifFalse;
	}
#endif

#if !defined(HK_MATH_fselectLessZero) && !defined(HK_MATH_fselectLessZero_f)
	HK_FORCE_INLINE static hkFloat32 HK_CALL fselectLessZero( hkFloat32 testVar, hkFloat32 ifTrue, hkFloat32 ifFalse)
	{
		return (testVar < hkFloat32(0)) ? ifTrue : ifFalse;
	}
#endif
#if !defined(HK_MATH_fselectLessZero) && !defined(HK_MATH_fselectLessZero_d)
	HK_FORCE_INLINE static hkDouble64 HK_CALL fselectLessZero( hkDouble64 testVar, hkDouble64 ifTrue, hkDouble64 ifFalse)
	{
		return (testVar < hkDouble64(0)) ? ifTrue : ifFalse;
	}
#endif

#if !defined(HK_MATH_fselectEqualZero) && !defined(HK_MATH_fselectEqualZero_f)
	HK_FORCE_INLINE static hkFloat32 HK_CALL fselectEqualZero( hkFloat32 testVar, hkFloat32 ifTrue, hkFloat32 ifFalse)
	{
		return (testVar == hkFloat32(0)) ? ifTrue : ifFalse;
	}
#endif
#if !defined(HK_MATH_fselectEqualZero) && !defined(HK_MATH_fselectEqualZero_d)
	HK_FORCE_INLINE static hkDouble64 HK_CALL fselectEqualZero( hkDouble64 testVar, hkDouble64 ifTrue, hkDouble64 ifFalse)
	{
		return (testVar == hkDouble64(0)) ? ifTrue : ifFalse;
	}
#endif

#if !defined(HK_MATH_fselectNotEqualZero) && !defined(HK_MATH_fselectNotEqualZero_f)
	HK_FORCE_INLINE static hkFloat32 HK_CALL fselectNotEqualZero( hkFloat32 testVar, hkFloat32 ifTrue, hkFloat32 ifFalse)
	{
		return (testVar != hkFloat32(0)) ? ifTrue : ifFalse;
	}
#endif
#if !defined(HK_MATH_fselectNotEqualZero) && !defined(HK_MATH_fselectNotEqualZero_d)
	HK_FORCE_INLINE static hkDouble64 HK_CALL fselectNotEqualZero( hkDouble64 testVar, hkDouble64 ifTrue, hkDouble64 ifFalse)
	{
		return (testVar != hkDouble64(0)) ? ifTrue : ifFalse;
	}
#endif

#if !defined(HK_MATH_atan2Approximation) && !defined(HK_MATH_atan2Approximation_f)
	HK_FORCE_INLINE static hkFloat32 HK_CALL atan2Approximation( const hkFloat32& y, const hkFloat32& x )
	{
		return hkMath::atan2(y,x);
	}
#endif
#if !defined(HK_MATH_atan2Approximation) && !defined(HK_MATH_atan2Approximation_d)
	HK_FORCE_INLINE static hkDouble64 HK_CALL atan2Approximation( const hkDouble64& y, const hkDouble64& x )
	{
		return hkMath::atan2(y,x);
	}
#endif

	/// Old deprecated function, do not use in new code.
	/// - Average absolute error 0.003315
	/// - Max absolute error 0.016747
	/// - About 4x faster than ::atan2f
	/// \warning x and y parameter names are wrong! You have to call this with the same
	/// parameter sequence as ::atan2f
	HK_FORCE_INLINE static hkFloat32 HK_CALL atan2fApproximation( hkFloat32 x, hkFloat32 y ) 
	{
		HK_WARN_ONCE(0x890c71ad, "hkMath::atan2fApproximation is deprecated. Consider using hkMath::atan2Approximation or the methods in hkVector4fUtil.");
		hkFloat32 fx = hkMath::fabs(x);
		hkFloat32 fy = hkMath::fabs(y);

		hkFloat32 result;
		const hkFloat32 c2 = hkFloat32(-0.121079f);
		const hkFloat32 c3 = HK_FLOAT_PI * hkFloat32(0.25f) - hkFloat32(1) - c2;

		{
			if ( fx <= fy )
			{
				fy += HK_FLOAT_EPSILON;
				hkFloat32 a = fx / fy;
				result = a;
				result += c2 * a*a;
				result += c3 * a*a*a;
			}
			else
			{
				fx += HK_FLOAT_EPSILON;
				hkFloat32 a = fy / fx;
				result = a;
				result += c2 * a*a;
				result += c3 * a*a*a;
				result = HK_FLOAT_PI * hkFloat32(0.5f) - result;
			}
		}

		if ( y < hkFloat32(0))
		{
			result = HK_FLOAT_PI - result;
		}

		if ( x < hkFloat32(0) )
		{
			result = -result;
		}
		return result;
	}

	/// Old deprecated function, do not use in new code
	/// - Average absolute error 0.003315
	/// - Max absolute error 0.016747
	/// - About 4x faster than ::atan2f
	/// \warning x and y parameter names are wrong! You have to call this with the same
	/// parameter sequence as ::atan2f
	HK_FORCE_INLINE static hkDouble64 HK_CALL atan2fApproximation( hkDouble64 x, hkDouble64 y ) 
	{
		HK_WARN_ONCE(0x890c71ad, "hkMath::atan2fApproximation is deprecated. Consider using hkMath::atan2Approximation or the methods in hkVector4dUtil.");
		hkDouble64 fx = hkMath::fabs(x);
		hkDouble64 fy = hkMath::fabs(y);

		hkDouble64 result;
		const hkDouble64 c2 = hkDouble64(-0.121079f);
		const hkDouble64 c3 = HK_DOUBLE_PI * hkDouble64(0.25f) - hkDouble64(1) - c2;

		{
			if ( fx <= fy )
			{
				fy += HK_DOUBLE_EPSILON;
				hkDouble64 a = fx / fy;
				result = a;
				result += c2 * a*a;
				result += c3 * a*a*a;
			}
			else
			{
				fx += HK_DOUBLE_EPSILON;
				hkDouble64 a = fy / fx;
				result = a;
				result += c2 * a*a;
				result += c3 * a*a*a;
				result = HK_DOUBLE_PI * hkDouble64(0.5f) - result;
			}
		}

		if ( y < hkDouble64(0))
		{
			result = HK_DOUBLE_PI - result;
		}

		if ( x < hkDouble64(0) )
		{
			result = -result;
		}
		return result;
	}


#if !defined(HK_MATH_logApproximation) && !defined(HK_MATH_logApproximation_f)
	HK_FORCE_INLINE static hkFloat32 HK_CALL logApproximation(const hkFloat32& r)
	{
		return hkMath::log(r);
	}
#endif
#if !defined(HK_MATH_logApproximation) && !defined(HK_MATH_logApproximation_d)
	HK_FORCE_INLINE static hkDouble64 HK_CALL logApproximation(const hkDouble64& r)
	{
		return hkMath::log(r);
	}
#endif

#ifndef HK_MATH_intInRange
		/// Returns any nonzero value if lowInclusive<=value and value<highExclusive.
	HK_FORCE_INLINE static hkBool32 HK_CALL intInRange( int value, int lowInclusive, int highExclusive )
	{
		return (lowInclusive <= value) & (value < highExclusive);
	}
#endif


#if !defined(HK_MATH_interpolate2d) && !defined(HK_MATH_interpolate2d_f)
	/// Interpolates between y0 and y1 using x0,x1 interval as the basis
	HK_FORCE_INLINE static hkFloat32 HK_CALL interpolate2d( hkFloat32 x, hkFloat32 x0, hkFloat32 x1, hkFloat32 y0, hkFloat32 y1 )
	{
		//HK_MATH_ASSERT(0x2342ab9,(x<=x0)||(x>=x1),"x is not from interval <x0,x1>!");
		HK_MATH_ASSERT(0x2342ab9,(x0 != x1), "no proper interval defined!");
		return y0 + (x-x0)*(y1-y0)/(x1-x0);
	}
#endif
#if !defined(HK_MATH_interpolate2d) && !defined(HK_MATH_interpolate2d_d)
	/// Interpolates between y0 and y1 using x0,x1 interval as the basis
	HK_FORCE_INLINE static hkDouble64 HK_CALL interpolate2d( hkDouble64 x, hkDouble64 x0, hkDouble64 x1, hkDouble64 y0, hkDouble64 y1 )
	{
		//HK_MATH_ASSERT(0x2342ab9,(x<=x0)||(x>=x1),"x is not from interval <x0,x1>!");
		HK_MATH_ASSERT(0x2342ab9,(x0 != x1), "no proper interval defined!");
		return y0 + (x-x0)*(y1-y0)/(x1-x0);
	}
#endif

	// Approximate, fast versions of e^x. See http://cnl.salk.edu/~schraudo/pubs/Schraudolph99.pdf for further info.

#if !defined(HK_MATH_fastExp) && !defined(HK_MATH_fastExp_d)
		// Double version. Error: Mean 1.5%, RMS: 1.8%, max 4.4%
	HK_FORCE_INLINE hkDouble64 fastExp(hkDouble64 val) 
	{
		int tmp = (int) (1512775 * val + 1072693248 - 68243); // 1512775 = 2^20/ln(2)  1072693248 = (2^10-1)*2^20  68243 = 0.045111411*2^20/ln(2) (lowest mean error) (60801 = lowest RMS)
		union { double d; int i[2]; } u; u.d = 0.0;
		#if HK_ENDIAN_LITTLE
			u.i[1] = tmp;
		#else
			u.i[0] = tmp;
		#endif
		return u.d;
	}
#endif
#if !defined(HK_MATH_fastExp) && !defined(HK_MATH_fastExp_f)
	// Float version. Error (over the interval -5.0 to 5.0): Mean 1.5%, RMS is 1.9%, max 4.4%
	HK_FORCE_INLINE hkFloat32 fastExp(hkFloat32 x) 
	{
		union { float f; int i; } u; u.i = (int) (12102203*x + 1065353216 - 545947); 
		// 12102203 = 2^23/ln(2)  1065353216 = (2^7-1)*2^23  545947 = 0.045111411*2^23/ln(2) (lowest mean error)
		return u.f;
	}
#endif

	// Returns the number of bits set to one in the given number
#ifndef HK_MATH_countBitsSet
	HK_FORCE_INLINE static int HK_CALL countBitsSet(hkUint32 v)
	{
		// Taken from http://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetParallel
		v =	(v - ((v >> 1) & 0x55555555));
		v =	(v & 0x33333333) + ((v >> 2) & 0x33333333);
		v =	(v + (v >> 4)) & 0xF0F0F0F;
		return (v * 0x1010101) >> 24;
	}
#endif

	// Returns the number of zeros at the start (MSB) of the given bitMask
#ifndef HK_MATH_countLeadingZeros
	template <typename T>
	HK_FORCE_INLINE int HK_CALL countLeadingZeros(T x);

	template <>
	HK_FORCE_INLINE int HK_CALL countLeadingZeros<hkUint32>(hkUint32 x)
	{
		// Fill all the bits to the right of set bits
		x |= (x >> 1);
		x |= (x >> 2);
		x |= (x >> 4);
		x |= (x >> 8);
		x |= (x >> 16);

		// Do a bit population count (number of ones)
		return 32 - countBitsSet(x);
	}

	template <>
	HK_FORCE_INLINE int HK_CALL countLeadingZeros<int>(int x)
	{
		return countLeadingZeros<hkUint32>((hkUint32)x);
	}

	template <>
	HK_FORCE_INLINE int HK_CALL countLeadingZeros<hkInt16>(hkInt16 x)
	{
		return countLeadingZeros<hkUint32>((hkUint32)x);
	}

	template <>
	HK_FORCE_INLINE int HK_CALL countLeadingZeros<hkUint64>(hkUint64 x)
	{
		const int loBits = countLeadingZeros<hkUint32>(x & 0xFFFFFFFF);
		const int hiBits = countLeadingZeros<hkUint32>((x >> 32L) & 0xFFFFFFFF);
		return (hiBits < 32) ? hiBits : (32 + loBits);
	}

#endif

	// Compile time integer log2
	template <int VALUE>	struct Log2		{ enum { ANSWER = Log2<VALUE/2>::ANSWER + 1 }; };
	template <>				struct Log2<1>	{ enum { ANSWER = 0 }; };

	// Returns the number of zeros at the end (LSB) of the given bitMask
#ifndef HK_MATH_countTrailingZeros
	template <typename T>
	HK_FORCE_INLINE int HK_CALL countTrailingZeros(T x);

	template <>
	HK_FORCE_INLINE int HK_CALL countTrailingZeros<hkUint32>(hkUint32 x)
	{
		// Taken from http://aggregate.org/MAGIC/#Population%20Count%20%28Ones%20Count%29
		return countBitsSet((x & -int(x)) - 1);
	}

	template <>
	HK_FORCE_INLINE int HK_CALL countTrailingZeros<int>(int x)
	{
		return countTrailingZeros<hkUint32>((hkUint32)x);
	}

	template <>
	HK_FORCE_INLINE int HK_CALL countTrailingZeros<hkInt16>(hkInt16 x)
	{
		return countTrailingZeros<hkUint32>((hkUint32)x);
	}

	template <>
	HK_FORCE_INLINE int HK_CALL countTrailingZeros<hkUint64>(hkUint64 x)
	{
		const int loBits = countTrailingZeros<hkUint32>(x & 0xFFFFFFFF);
		const int hiBits = countTrailingZeros<hkUint32>((x >> 32L) & 0xFFFFFFFF);
		return (loBits < 32) ? loBits : (32 + hiBits);
	}
#endif

	// Returns the greatest common divisor of the given numbers. Both numbers are assumed to be positive!
	template <typename T>
	inline T HK_CALL greatestCommonDivisor(T a, T b)
	{
		if ( !a )	{	return b;	}
		if ( !b )	{	return a;	}

		// Divide by 2 as much as possible
		int shift;
		T u, v;
		{
			const int numTrailingZerosA = countTrailingZeros<T>(a);
			const int numTrailingZerosB = countTrailingZeros<T>(b);
			shift = hkMath::min2(numTrailingZerosA, numTrailingZerosB);

			u = a >> numTrailingZerosA;
			v = b >> shift;
		}

		// From here on, u is always odd.
		do
		{
			// Remove all factors of 2 in v; they are not common. Note: v is not zero!
			const int numTrailingZerosV = countTrailingZeros<T>(v);
			v >>= numTrailingZerosV;

			// Now u and v are both odd. Swap if necessary so u <= v, then set v = v - u (which is even).
			if ( v < u )	{	const T vv = v;	v = u - v;	u = vv;	}
			else			{					v -= u;				}

			// Here v >= u.
		} while ( v );

		// Restore common factors of 2
		return u << shift;
	}

	/// Compute from a value v another value cv in the range [-Radius,+Radius] such that cv = v-k*2*Radius with k integer.
	template<typename T>
	static HK_FORCE_INLINE T toRange(T v, const T& radius, T& k)
	{
		const T diameter = T(2)*radius;
		// Compute the number of diameter multiples needed.
		T kf = ((v)+radius) / diameter;
		k = hkMath::floor(kf);
		T cv = v - k*diameter;

		// Be paranoid about edge cases (TODO J.N: check numerical analysis).
		if(cv > radius)
		{
			cv -= diameter;
			k += T(1);
		}
		else if(cv < -radius)
		{
			cv += diameter;
			k -= T(1);
		}

#ifdef HK_DEBUG
		HK_ASSERT(0x55f29308, (cv >= -radius) && (cv <= radius));	
#endif

		return cv;
	}
}

#endif // HK_MATH_MATH_FUNCS_H

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
