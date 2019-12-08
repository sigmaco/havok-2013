/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#include <Common/Base/Container/String/hkStringBuf.h>

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<FT>::setNormalOfTriangle(typename hkRealTypes<FT>::Vector &result, typename hkRealTypes<FT>::VectorParameter a, typename hkRealTypes<FT>::VectorParameter b, typename hkRealTypes<FT>::VectorParameter c)
{
	typename hkRealTypes<FT>::Vector ba,ca;
	ba.setSub( b, a );
	ca.setSub( c, a );
	result.setCross( ba , ca);
}


#ifndef HK_VECTOR4fUTIL_atan2Approximation
template <>
HK_FORCE_INLINE hkSimdFloat32 HK_CALL hkVector4UtilImpl<hkFloat32>::atan2Approximation(hkSimdFloat32Parameter y, hkSimdFloat32Parameter x)
{
	return hkSimdFloat32::fromFloat(hkMath::atan2Approximation(y.getReal(),x.getReal()));
}
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::atan2Approximation(hkVector4fParameter y, hkVector4fParameter x, hkVector4f& result)
{
	result.set(hkMath::atan2Approximation(y(0),x(0)), hkMath::atan2Approximation(y(1),x(1)), hkMath::atan2Approximation(y(2),x(2)), hkMath::atan2Approximation(y(3),x(3)));
}
#endif
#ifndef HK_VECTOR4dUTIL_atan2Approximation
template <>
HK_FORCE_INLINE hkSimdDouble64 HK_CALL hkVector4UtilImpl<hkDouble64>::atan2Approximation(hkSimdDouble64Parameter y, hkSimdDouble64Parameter x)
{
	return hkSimdDouble64::fromFloat(hkMath::atan2Approximation(y.getReal(),x.getReal()));
}
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::atan2Approximation(hkVector4dParameter y, hkVector4dParameter x, hkVector4d& result)
{
	result.set(hkMath::atan2Approximation(y(0),x(0)), hkMath::atan2Approximation(y(1),x(1)), hkMath::atan2Approximation(y(2),x(2)), hkMath::atan2Approximation(y(3),x(3)));
}
#endif

// Average absolute error 0.063428
// Max absolute error 0.571373
// About 8.5x faster than ::atan2f for 4 simultaneous values
template <typename FT>
HK_FORCE_INLINE typename hkRealTypes<FT>::Scalar HK_CALL hkVector4UtilImpl<FT>::linearAtan2Approximation(typename hkRealTypes<FT>::ScalarParameter y, typename hkRealTypes<FT>::ScalarParameter x)
{
	const typename hkRealTypes<FT>::Scalar c2 = hkRealTypes<FT>::Scalar::fromFloat(typename hkRealTypes<FT>::Pod(2.3561944901923449288469825374596));
	const typename hkRealTypes<FT>::Scalar pi_quarter = hkRealTypes<FT>::Scalar::template getConstant<HK_QUADREAL_PI_QUARTER>();

	typename hkRealTypes<FT>::Scalar abs_y; abs_y.setAbs(y);
	const typename hkRealTypes<FT>::Scalar xPlusAbsY = x + abs_y;

	// case x<0
	typename hkRealTypes<FT>::Scalar angle0;
	{
		typename hkRealTypes<FT>::Scalar r; r.template setDiv<HK_ACC_23_BIT,HK_DIV_IGNORE>(xPlusAbsY, abs_y - x);
		angle0.setSubMul(c2, pi_quarter, r);
	}

	// case x>=0
	typename hkRealTypes<FT>::Scalar angle1;
	{
		typename hkRealTypes<FT>::Scalar r; r.template setDiv<HK_ACC_23_BIT,HK_DIV_IGNORE>(x - abs_y, xPlusAbsY);
		angle1.setSubMul(pi_quarter, pi_quarter, r);
	}

	typename hkRealTypes<FT>::Scalar result;
	// select case
	result.setSelect(x.lessZero(), angle0, angle1);

	// invert symmetry
	result.setFlipSign(result, y.lessZero());

	return result;
}

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<FT>::linearAtan2Approximation(typename hkRealTypes<FT>::VectorParameter y, typename hkRealTypes<FT>::VectorParameter x, typename hkRealTypes<FT>::Vector& result)
{
	// 3 * pi/4
	static HK_ALIGN_DOUBLE( const typename hkRealTypes<FT>::Pod c2[4] ) = { typename hkRealTypes<FT>::Pod(2.3561944901923449288469825374596), typename hkRealTypes<FT>::Pod(2.3561944901923449288469825374596), typename hkRealTypes<FT>::Pod(2.3561944901923449288469825374596), typename hkRealTypes<FT>::Pod(2.3561944901923449288469825374596) };

	const typename hkRealTypes<FT>::Vector& pi_quarter = hkRealTypes<FT>::Vector::template getConstant<HK_QUADREAL_PI_QUARTER>();

	const typename hkRealTypes<FT>::Comparison x_less_zero = x.lessZero();
	const typename hkRealTypes<FT>::Comparison y_less_zero = y.lessZero();

	typename hkRealTypes<FT>::Vector abs_y; abs_y.setAbs(y);
	typename hkRealTypes<FT>::Vector xPlusAbsY; xPlusAbsY.setAdd(x, abs_y);

	// case x<0
	typename hkRealTypes<FT>::Vector angle0;
	{
		typename hkRealTypes<FT>::Vector d; d.setSub(abs_y, x);
		typename hkRealTypes<FT>::Vector r; r.template setDiv<HK_ACC_23_BIT,HK_DIV_IGNORE>(xPlusAbsY, d);
		angle0.setSubMul(*reinterpret_cast<const typename hkRealTypes<FT>::Vector*>(c2), pi_quarter, r);
	}

	// case x>=0
	typename hkRealTypes<FT>::Vector angle1;
	{
		typename hkRealTypes<FT>::Vector n; n.setSub(x, abs_y);
		typename hkRealTypes<FT>::Vector r; r.template setDiv<HK_ACC_23_BIT,HK_DIV_IGNORE>(n, xPlusAbsY);
		angle1.setSubMul(pi_quarter, pi_quarter, r);
	}

	// select case
	result.setSelect(x_less_zero, angle0, angle1);

	// invert symmetry
	result.setFlipSign(result, y_less_zero);
}

// Average absolute error 0.063424
// Max absolute error 1.374024
// About 13x faster than ::atan2f for 4 simultaneous values
template <typename FT>
HK_FORCE_INLINE typename hkRealTypes<FT>::Scalar HK_CALL hkVector4UtilImpl<FT>::linearAtan2ApproximationRough(typename hkRealTypes<FT>::ScalarParameter y, typename hkRealTypes<FT>::ScalarParameter x)
{
	const typename hkRealTypes<FT>::Scalar c2 = hkRealTypes<FT>::Scalar::fromFloat(typename hkRealTypes<FT>::Pod(2.3561944901923449288469825374596));
	const typename hkRealTypes<FT>::Scalar pi_quarter = hkRealTypes<FT>::Scalar::template getConstant<HK_QUADREAL_PI_QUARTER>();

	typename hkRealTypes<FT>::Scalar abs_y; abs_y.setAbs(y);
	const typename hkRealTypes<FT>::Scalar xPlusAbsY = x + abs_y;

	// case x<0
	typename hkRealTypes<FT>::Scalar angle0;
	{
		typename hkRealTypes<FT>::Scalar r; r.template setDiv<HK_ACC_12_BIT,HK_DIV_IGNORE>(xPlusAbsY, abs_y - x);
		angle0.setSubMul(c2, pi_quarter, r);
	}

	// case x>=0
	typename hkRealTypes<FT>::Scalar angle1;
	{
		typename hkRealTypes<FT>::Scalar r; r.template setDiv<HK_ACC_12_BIT,HK_DIV_IGNORE>(x - abs_y, xPlusAbsY);
		angle1.setSubMul(pi_quarter, pi_quarter, r);
	}

	typename hkRealTypes<FT>::Scalar result;
	// select case
	result.setSelect(x.lessZero(), angle0, angle1);

	// invert symmetry
	result.setFlipSign(result, y.lessZero());

	return result;
}

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<FT>::linearAtan2ApproximationRough(typename hkRealTypes<FT>::VectorParameter y, typename hkRealTypes<FT>::VectorParameter x, typename hkRealTypes<FT>::Vector& result)
{
	// 3 * pi/4
	static HK_ALIGN_DOUBLE( const typename hkRealTypes<FT>::Pod c2[4] ) = { typename hkRealTypes<FT>::Pod(2.3561944901923449288469825374596), typename hkRealTypes<FT>::Pod(2.3561944901923449288469825374596), typename hkRealTypes<FT>::Pod(2.3561944901923449288469825374596), typename hkRealTypes<FT>::Pod(2.3561944901923449288469825374596) };

	const typename hkRealTypes<FT>::Vector& pi_quarter = hkRealTypes<FT>::Vector::template getConstant<HK_QUADREAL_PI_QUARTER>();

	const typename hkRealTypes<FT>::Comparison x_less_zero = x.lessZero();
	const typename hkRealTypes<FT>::Comparison y_less_zero = y.lessZero();

	typename hkRealTypes<FT>::Vector abs_y; abs_y.setAbs(y);
	typename hkRealTypes<FT>::Vector xPlusAbsY; xPlusAbsY.setAdd(x, abs_y);

	// case x<0
	typename hkRealTypes<FT>::Vector angle0;
	{
		typename hkRealTypes<FT>::Vector d; d.setSub(abs_y, x);
		typename hkRealTypes<FT>::Vector r; r.template setDiv<HK_ACC_12_BIT,HK_DIV_IGNORE>(xPlusAbsY, d);
		angle0.setSubMul(*reinterpret_cast<const typename hkRealTypes<FT>::Vector*>(c2), pi_quarter, r);
	}

	// case x>=0
	typename hkRealTypes<FT>::Vector angle1;
	{
		typename hkRealTypes<FT>::Vector n; n.setSub(x, abs_y);
		typename hkRealTypes<FT>::Vector r; r.template setDiv<HK_ACC_12_BIT,HK_DIV_IGNORE>(n, xPlusAbsY);
		angle1.setSubMul(pi_quarter, pi_quarter, r);
	}

	// select case
	result.setSelect(x_less_zero, angle0, angle1);

	// invert symmetry
	result.setFlipSign(result, y_less_zero);
}

#ifndef HK_VECTOR4fUTIL_logApproximation
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::logApproximation(hkVector4fParameter v, hkVector4f& result)
{
	result.set(hkMath::logApproximation(v(0)), hkMath::logApproximation(v(1)), hkMath::logApproximation(v(2)), hkMath::logApproximation(v(3)));
}
#endif
#ifndef HK_VECTOR4dUTIL_logApproximation
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::logApproximation(hkVector4dParameter v, hkVector4d& result)
{
	result.set(hkMath::logApproximation(v(0)), hkMath::logApproximation(v(1)), hkMath::logApproximation(v(2)), hkMath::logApproximation(v(3)));
}
#endif

#ifndef HK_VECTOR4fUTIL_sinCos
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::sinCos(hkVector4fParameter r, hkVector4f& sc)
{
	sc.set(hkMath::sin(r(0)),hkMath::cos(r(1)),hkMath::sin(r(2)),hkMath::cos(r(3)));
}
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::sinCos(hkSimdFloat32Parameter r, hkVector4f& sc)
{
	const hkFloat32 rr = r.getReal();
	const hkFloat32 sr = hkMath::sin(rr);
	const hkFloat32 cr = hkMath::cos(rr);
	sc.set(sr,cr,sr,cr);
}
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::sinCos(hkSimdFloat32Parameter r, hkSimdFloat32& s, hkSimdFloat32& c)
{
	const hkFloat32 rr = r.getReal();
	s.setFromFloat( hkMath::sin(rr) );
	c.setFromFloat( hkMath::cos(rr) );
}
#endif
#ifndef HK_VECTOR4dUTIL_sinCos
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::sinCos(hkVector4dParameter r, hkVector4d& sc)
{
	sc.set(hkMath::sin(r(0)),hkMath::cos(r(1)),hkMath::sin(r(2)),hkMath::cos(r(3)));
}
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::sinCos(hkSimdDouble64Parameter r, hkVector4d& sc)
{
	const hkDouble64 rr = r.getReal();
	const hkDouble64 sr = hkMath::sin(rr);
	const hkDouble64 cr = hkMath::cos(rr);
	sc.set(sr,cr,sr,cr);
}
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::sinCos(hkSimdDouble64Parameter r, hkSimdDouble64& s, hkSimdDouble64& c)
{
	const hkDouble64 rr = r.getReal();
	s.setFromFloat( hkMath::sin(rr) );
	c.setFromFloat( hkMath::cos(rr) );
}
#endif

#ifndef HK_VECTOR4fUTIL_sinCosApproximation
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::sinCosApproximation(hkVector4fParameter r, hkVector4f& sc)
{
	sinCos(r,sc);
}
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::sinCosApproximation(hkSimdFloat32Parameter r, hkVector4f& sc)
{
	sinCos(r,sc);
}
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::sinCosApproximation(hkSimdFloat32Parameter r, hkSimdFloat32& s, hkSimdFloat32& c)
{
	sinCos(r,s,c);
}
#endif
#ifndef HK_VECTOR4dUTIL_sinCosApproximation
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::sinCosApproximation(hkVector4dParameter r, hkVector4d& sc)
{
	sinCos(r,sc);
}
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::sinCosApproximation(hkSimdDouble64Parameter r, hkVector4d& sc)
{
	sinCos(r,sc);
}
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::sinCosApproximation(hkSimdDouble64Parameter r, hkSimdDouble64& s, hkSimdDouble64& c)
{
	sinCos(r,s,c);
}
#endif

#ifndef HK_VECTOR4fUTIL_aSinAcos
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::aSin(hkVector4fParameter r, hkVector4f& sc)
{
	sc.set(hkMath::asin(r(0)),hkMath::asin(r(1)),hkMath::asin(r(2)),hkMath::asin(r(3)));
}
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::aCos(hkVector4fParameter r, hkVector4f& sc)
{
	sc.set(hkMath::acos(r(0)),hkMath::acos(r(1)),hkMath::acos(r(2)),hkMath::acos(r(3)));
}
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::aSinAcos(hkVector4fParameter r, hkVector4f& sc)
{
	sc.set(hkMath::asin(r(0)),hkMath::acos(r(1)),hkMath::asin(r(2)),hkMath::acos(r(3)));
}
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::aSinAcos(hkSimdFloat32Parameter r, hkVector4f& sc)
{
	const hkFloat32 rr = r.getReal();
	const hkFloat32 sr = hkMath::asin(rr);
	const hkFloat32 cr = hkMath::acos(rr);
	sc.set(sr,cr,sr,cr);
}
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::aSinAcos(hkSimdFloat32Parameter r, hkSimdFloat32& s, hkSimdFloat32& c)
{
	const hkFloat32 rr = r.getReal();
	s.setFromFloat( hkMath::asin(rr) );
	c.setFromFloat( hkMath::acos(rr) );
}
#endif
#ifndef HK_VECTOR4dUTIL_aSinAcos
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::aSin(hkVector4dParameter r, hkVector4d& sc)
{
	sc.set(hkMath::asin(r(0)),hkMath::asin(r(1)),hkMath::asin(r(2)),hkMath::asin(r(3)));
}
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::aCos(hkVector4dParameter r, hkVector4d& sc)
{
	sc.set(hkMath::acos(r(0)),hkMath::acos(r(1)),hkMath::acos(r(2)),hkMath::acos(r(3)));
}
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::aSinAcos(hkVector4dParameter r, hkVector4d& sc)
{
	sc.set(hkMath::asin(r(0)),hkMath::acos(r(1)),hkMath::asin(r(2)),hkMath::acos(r(3)));
}
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::aSinAcos(hkSimdDouble64Parameter r, hkVector4d& sc)
{
	const hkDouble64 rr = r.getReal();
	const hkDouble64 sr = hkMath::asin(rr);
	const hkDouble64 cr = hkMath::acos(rr);
	sc.set(sr,cr,sr,cr);
}
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::aSinAcos(hkSimdDouble64Parameter r, hkSimdDouble64& s, hkSimdDouble64& c)
{
	const hkDouble64 rr = r.getReal();
	s.setFromFloat( hkMath::asin(rr) );
	c.setFromFloat( hkMath::acos(rr) );
}
#endif


template <typename FT>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<FT>::convertFromHalf( const hkHalf& a, const hkHalf& b, const hkHalf& c, const hkHalf& d, typename hkRealTypes<FT>::Vector& out )
{
	HK_ALIGN_DOUBLE(hkHalf h[4]);
	h[0] = a;
	h[1] = b;
	h[2] = c;
	h[3] = d;
	out.load<4>(&h[0]);
}


template <typename FT>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<FT>::convertToInt16( typename hkRealTypes<FT>::VectorParameter in, typename hkRealTypes<FT>::VectorParameter offset, typename hkRealTypes<FT>::VectorParameter scale, hkIntUnion64& out)
{
	typename hkRealTypes<FT>::Vector x;
	x.setAdd(in,offset);
	x.mul(scale);

	hkIntVector i;
	i.setConvertF32toS32(x);
	i.setConvertSaturateS32ToS16(i,i);
	i.store<2>(&out.u32[0]); // 2xu32 = 4xu16
}


#ifndef HK_VECTOR4fUTIL_convertToUint16
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::convertToUint16( hkVector4fParameter in, hkVector4fParameter offset, hkVector4fParameter scale, hkIntUnion64& out)
{
	hkVector4f x;
	x.setAdd(in,offset);
	x.mul(scale);

	hkIntVector i;
	i.setConvertF32toS32(x);
	i.setConvertSaturateS32ToU16(i,i);
	i.store<2>(&out.u32[0]); // 2xu32 = 4xu16
}
#endif
#ifndef HK_VECTOR4dUTIL_convertToUint16
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::convertToUint16( hkVector4dParameter in, hkVector4dParameter offset, hkVector4dParameter scale, hkIntUnion64& out)
{
	hkVector4d x;
	x.setAdd(in,offset);
	x.mul(scale);

	hkIntVector i;
	i.setConvertF32toS32(x);
	i.setConvertSaturateS32ToU16(i,i);
	i.store<2>(&out.u32[0]); // 2xu32 = 4xu16
}
#endif

#ifndef HK_VECTOR4fUTIL_convertToUint16WithClip
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::convertToUint16WithClip( hkVector4fParameter in, hkVector4fParameter offset, hkVector4fParameter scale, hkVector4fParameter min, hkVector4fParameter max, hkIntUnion64& out)
{
	hkVector4f x;
	x.setAdd(in,offset);
	x.mul(scale);
	x.setMin(x,max);
	x.setMax(x,min);

	hkIntVector i;
	i.setConvertF32toS32(x);
	i.setConvertSaturateS32ToU16(i,i);
	i.store<2>(&out.u32[0]); // 2xu32 = 4xu16
}
#endif
#ifndef HK_VECTOR4dUTIL_convertToUint16WithClip
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::convertToUint16WithClip( hkVector4dParameter in, hkVector4dParameter offset, hkVector4dParameter scale, hkVector4dParameter min, hkVector4dParameter max, hkIntUnion64& out)
{
	hkVector4d x;
	x.setAdd(in,offset);
	x.mul(scale);
	x.setMin(x,max);
	x.setMax(x,min);

	hkIntVector i;
	i.setConvertF32toS32(x);
	i.setConvertSaturateS32ToU16(i,i);
	i.store<2>(&out.u32[0]); // 2xu32 = 4xu16
}
#endif

#ifndef HK_VECTOR4fUTIL_convertToUint32
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::convertToUint32( hkVector4fParameter in, hkVector4fParameter offset, hkVector4fParameter scale, hkUint32* out)
{
	hkVector4f x;
	x.setAdd(in,offset);
	x.mul(scale);
	hkIntVector i;
	i.setConvertF32toU32(x);
	i.store<4>(out);
}
#endif
#ifndef HK_VECTOR4dUTIL_convertToUint32
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::convertToUint32( hkVector4dParameter in, hkVector4dParameter offset, hkVector4dParameter scale, hkUint32* out)
{
	hkVector4d x;
	x.setAdd(in,offset);
	x.mul(scale);
	hkIntVector i;
	i.setConvertF32toU32(x);
	i.store<4>(out);
}
#endif

#ifndef HK_VECTOR4fUTIL_convertToUint32WithClip
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::convertToUint32WithClip( hkVector4fParameter in, hkVector4fParameter offset, hkVector4fParameter scale, hkVector4fParameter min, hkVector4fParameter max, hkUint32* out)
{
	hkVector4f x;
	x.setAdd(in,offset);
	x.mul(scale);
	x.setMin(x,max);
	x.setMax(x,min);
	hkIntVector i;
	i.setConvertF32toU32(x);
	i.store<4>(out);
}
#endif
#ifndef HK_VECTOR4dUTIL_convertToUint32WithClip
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::convertToUint32WithClip( hkVector4dParameter in, hkVector4dParameter offset, hkVector4dParameter scale, hkVector4dParameter min, hkVector4dParameter max, hkUint32* out)
{
	hkVector4d x;
	x.setAdd(in,offset);
	x.mul(scale);
	x.setMin(x,max);
	x.setMax(x,min);
	hkIntVector i;
	i.setConvertF32toU32(x);
	i.store<4>(out);
}
#endif


template <typename FT>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<FT>::calculatePerpendicularVector(typename hkRealTypes<FT>::VectorParameter vectorIn, typename hkRealTypes<FT>::Vector& biVectorOut)
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	typename hkRealTypes<FT>::Vector h; h.setXYZ_0( vectorIn );
	typename hkRealTypes<FT>::Vector d0; d0.template setPermutation<hkVectorPermutation::YXWW>(h);
	typename hkRealTypes<FT>::Vector d1; d1.template setPermutation<hkVectorPermutation::ZWXW>(h);
	const typename hkRealTypes<FT>::Scalar l0 = d0.template lengthSquared<3>();
	const typename hkRealTypes<FT>::Scalar l1 = d1.template lengthSquared<3>();
	const typename hkRealTypes<FT>::Comparison c = l0.less( l1 );
	typename hkRealTypes<FT>::Vector out; out.setSelect(c,d1,d0);
	biVectorOut.template setNeg<1>(out);
#else
	// find the indices of (one of) the smallest component(s) and the indices of
	// the remaining two components in the vector
	int min = 0;
	int ok1 = 1;
	int ok2 = 2;

	typename hkRealTypes<FT>::Pod a0 = hkMath::fabs(vectorIn(0));
	typename hkRealTypes<FT>::Pod a1 = hkMath::fabs(vectorIn(1));
	typename hkRealTypes<FT>::Pod a2 = hkMath::fabs(vectorIn(2));

	// sort the indices to make min index point to the smallest
	if( a1 < a0 )
	{
		ok1 = 0;
		min = 1;
		a0 = a1;
	}

	if(a2 < a0)
	{
		ok2 = min;
		min = 2;
	}

	biVectorOut.setZero();
	biVectorOut(ok1) =  vectorIn(ok2);
	biVectorOut(ok2) = -vectorIn(ok1);
#endif
}



template <typename FT>
template<bool INVERSE2>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<FT>::calculatePerpendicularNormalizedVectors(typename hkRealTypes<FT>::VectorParameter vectorIn, typename hkRealTypes<FT>::Vector& biVectorOut, typename hkRealTypes<FT>::Vector& bi2VectorOut)
{
	HK_ASSERT( 0xf034fd5f, vectorIn.template isNormalized<3>(1e-3f) );
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	typename hkRealTypes<FT>::Vector h; h.setXYZ_0( vectorIn );
	typename hkRealTypes<FT>::Vector d0; d0.template setPermutation<hkVectorPermutation::YXWW>(h);
	typename hkRealTypes<FT>::Vector d1; d1.template setPermutation<hkVectorPermutation::ZWXW>(h);
	const typename hkRealTypes<FT>::Scalar l0 = d0.template lengthSquared<3>();
	const typename hkRealTypes<FT>::Scalar l1 = d1.template lengthSquared<3>();
	typename hkRealTypes<FT>::Scalar len; len.setMax( l0, l1 );
	const typename hkRealTypes<FT>::Comparison c = l0.less( l1 );
	typename hkRealTypes<FT>::Vector o0; o0.setSelect(c,d1,d0);
	o0.template setNeg<1>(o0);
	typename hkRealTypes<FT>::Vector o1;
	if ( INVERSE2	)
	{
		o1.setCross( o0, vectorIn );
	}
	else
	{
		o1.setCross( vectorIn, o0 );
	}
	typename hkRealTypes<FT>::Scalar invLen = len.template sqrtInverse<HK_ACC_23_BIT, HK_SQRT_IGNORE>(  );
	biVectorOut.setMul( invLen, o0 );
	bi2VectorOut.setMul( invLen, o1 );
#else
	// find the indices of (one of) the smallest component(s) and the indices of
	// the remaining two components in the vector
	int min = 0;
	int ok1 = 1;
	int ok2 = 2;

	typename hkRealTypes<FT>::Pod a0 = hkMath::fabs(vectorIn(0));
	typename hkRealTypes<FT>::Pod a1 = hkMath::fabs(vectorIn(1));
	typename hkRealTypes<FT>::Pod a2 = hkMath::fabs(vectorIn(2));

	// sort the indices to make min index point to the smallest
	if( a1 < a0 )
	{
		ok1 = 0;
		min = 1;
		a0 = a1;
	}

	if(a2 < a0)
	{
		ok2 = min;
		min = 2;
	}

	biVectorOut.setZero();
	biVectorOut(ok1) =  vectorIn(ok2);
	biVectorOut(ok2) = -vectorIn(ok1);
	biVectorOut.template normalize<3,HK_ACC_23_BIT, HK_SQRT_IGNORE>();
	bi2VectorOut.setCross( biVectorOut, vectorIn );
#endif
}



// vector containing col-major 2x2 matrix [r0c0, r1c0, r0c1, r1c1]
template <typename FT>
HK_FORCE_INLINE hkResult HK_CALL hkVector4UtilImpl<FT>::invert2x2Matrix(typename hkRealTypes<FT>::VectorParameter m, typename hkRealTypes<FT>::ScalarParameter tolerance, typename hkRealTypes<FT>::Vector& out)
{
	typename hkRealTypes<FT>::Vector mt; mt.template setPermutation<hkVectorPermutation::WZWZ>(m);
	typename hkRealTypes<FT>::Vector p; p.setMul(m,mt);
	const typename hkRealTypes<FT>::Scalar D = p.template getComponent<0>() - p.template getComponent<1>();
	typename hkRealTypes<FT>::Scalar absD; absD.setAbs(D);

	if (absD.isLessEqual(tolerance))
	{
		return HK_FAILURE;  // may be an ordinary result
	}

	const typename hkRealTypes<FT>::Scalar DI = D.reciprocal();

	typename hkRealTypes<FT>::Vector o;
	o.template setPermutation<hkVectorPermutation::YZWX>(m);
	o.template setNeg<2>(o);
	o.mul(DI);

	out.template setPermutation<hkVectorPermutation::ZYXW>(o);

	return HK_SUCCESS;
}


template <typename FT>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<FT>::transformPoints( const typename hkRealTypes<FT>::Transform& t, const typename hkRealTypes<FT>::Vector* vectorsIn, int numVectors, typename hkRealTypes<FT>::Vector* vectorsOut )
{
	HK_MATH_ASSERT( 0xf0237abd, numVectors > 0, "At least one element required");
	typename hkRealTypes<FT>::Transform unaliased = t;
	int i = numVectors - 1;
	do
	{
		vectorsOut[i]._setTransformedPos( unaliased, vectorsIn[i] );
	} while( --i >= 0 );
}


template <typename FT>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<FT>::transformPoints( const typename hkRealTypes<FT>::QTransform& t, const typename hkRealTypes<FT>::Vector* vectorsIn, int numVectors, typename hkRealTypes<FT>::Vector* vectorsOut )
{
	HK_MATH_ASSERT( 0xf0237abd, numVectors > 0, "At least one element required");
	typename hkRealTypes<FT>::QTransform unaliased = t;
	int i = numVectors - 1;
	do
	{
		vectorsOut[i]._setTransformedPos( unaliased, vectorsIn[i] );
	} while( --i >= 0 );
}


template <typename FT>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<FT>::transformPoints( const typename hkRealTypes<FT>::QsTransform& t, const typename hkRealTypes<FT>::Vector* vectorsIn, int numVectors, typename hkRealTypes<FT>::Vector* vectorsOut )
{
	HK_MATH_ASSERT( 0xf0237abd, numVectors > 0, "At least one element required");
	typename hkRealTypes<FT>::QsTransform unaliased = t;
	int i = numVectors - 1;
	do
	{
		vectorsOut[i]._setTransformedPos( unaliased, vectorsIn[i] );
	} while( --i >= 0 );
}


template <typename FT>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<FT>::transformPlaneEquations( const typename hkRealTypes<FT>::Transform& t, const typename hkRealTypes<FT>::Vector* HK_RESTRICT planes, int numPlanes, typename hkRealTypes<FT>::Vector* HK_RESTRICT planesOut )
{
	const typename hkRealTypes<FT>::Rotation rotation = t.getRotation();	// we are making a copy here to allow for better compiler support

	typename hkRealTypes<FT>::Vector tr;	tr.template setNeg<4>(t.getTranslation()); 
	typename hkRealTypes<FT>::Vector pivotShift; pivotShift._setRotatedInverseDir( rotation, tr );

	int p = numPlanes - 1;
	do
	{
		const typename hkRealTypes<FT>::Scalar newDist = planes->dot4xyz1(pivotShift);

		typename hkRealTypes<FT>::Vector h; h._setRotatedDir(rotation, planes[0] );
		planesOut->setXYZ_W(h, newDist);

		planes++;
		planesOut++;
	}
	while ( --p >=0 );
}


template <typename FT>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<FT>::transformPlaneEquation( const typename hkRealTypes<FT>::Transform& t, typename hkRealTypes<FT>::VectorParameter plane, typename hkRealTypes<FT>::Vector& planeOut )
{
	const typename hkRealTypes<FT>::Rotation rotation = t.getRotation();	// we are making a copy here to allow for better compiler support

	typename hkRealTypes<FT>::Vector tr;	tr.template setNeg<4>(t.getTranslation()); 
	typename hkRealTypes<FT>::Vector pivotShift; pivotShift._setRotatedInverseDir( rotation, tr );

	const typename hkRealTypes<FT>::Scalar newDist = plane.dot4xyz1(pivotShift);
	typename hkRealTypes<FT>::Vector h; h._setRotatedDir(rotation, plane );
	planeOut.setXYZ_W(h, newDist);
}


template <typename FT>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<FT>::transformAndScalePlane( const typename hkRealTypes<FT>::Transform& transform, const typename hkRealTypes<FT>::Vector& scale, typename hkRealTypes<FT>::Vector& planeInOut )
{
	// Transform a plane equation
	//  n^T(x-p) = 0
	//
	//    becomes
	//
	//  Tn(n)^T(x-T(p)) = 0,  where   T(x)=RSx+t   and   Tn(x) = RS^-1x 
	//
	//    T is hkQsTransformf, and Tn is the inverse transpose of RS, used
	//    to transform normal directions. 
	//  
	//  (RS^-1 n)^T( x - (RSp+t)) = 0
	//  (RS^-1 n)^T x - (RS^-1 n)^T(RSp+t)) = 0
	//  (RS^-1 n)^T x - n^T S^-1 R^T R S p - (RS^-1 n)^T t = 0
	//                      \-identity-/
	//    so
	//
	//   n'^T x - n^T p - n'^T t = 0   where  n' = RS^-1 n
	//  \xyz/     \------w-----/
	//  since we know n and n^T p, we only need to compute n'
	//  and n'^T t. Finally we must scale the equation so that
	//  the new normal (xyz) is unit length

	const typename hkRealTypes<FT>::Scalar w = planeInOut.getW();
	const typename hkRealTypes<FT>::Vector translation = transform.getTranslation();
	typename hkRealTypes<FT>::Vector invScale; invScale.setReciprocal(scale); 
	typename hkRealTypes<FT>::Vector planeLocal; planeLocal.setMul(planeInOut, invScale); 
	planeLocal._setRotatedDir(transform.getRotation(), planeLocal);
	const typename hkRealTypes<FT>::Scalar invNorm = planeLocal.template lengthInverse<3,HK_ACC_23_BIT,HK_SQRT_SET_ZERO>();
	const typename hkRealTypes<FT>::Scalar dot = planeLocal.template dot<3>(translation);
	planeLocal.setW( w-dot );
	planeLocal.mul(invNorm); // notice w must be scaled as well
	planeInOut = planeLocal;
}

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<FT>::scalePlane( const typename hkRealTypes<FT>::Vector& scale, typename hkRealTypes<FT>::Vector& planeInOut )
{
	// By setting R = identity in the derivation in transformAndScalePlane(),
	// we get a slightly simplified method for scaling plane equations
	const typename hkRealTypes<FT>::Scalar w = planeInOut.getW();
	//const typename hkRealTypes<FT>::Vector translation = transform.getTranslation();
	typename hkRealTypes<FT>::Vector invScale; invScale.setReciprocal(scale); 
	typename hkRealTypes<FT>::Vector planeLocal; planeLocal.setMul(planeInOut, invScale); 
	//planeLocal._setRotatedDir(transform.getRotation(), planeLocal);
	const typename hkRealTypes<FT>::Scalar invNorm = planeLocal.template lengthInverse<3,HK_ACC_23_BIT,HK_SQRT_SET_ZERO>();
	//const typename hkRealTypes<FT>::Scalar dot = planeLocal.template dot<3>(translation);
	planeLocal.setW( w /*-dot*/ );
	planeLocal.mul(invNorm); // notice w must be scaled as well
	planeInOut = planeLocal;
}

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<FT>::translatePlane( const typename hkRealTypes<FT>::Vector& translation, typename hkRealTypes<FT>::Vector& planeInOut )
{
	// By setting S = R = identity in the derivation in transformAndScalePlane(),
	typename hkRealTypes<FT>::Vector planeLocal = planeInOut; 
	const typename hkRealTypes<FT>::Scalar w = planeLocal.getW();
	const typename hkRealTypes<FT>::Scalar dot = planeLocal.template dot<3>(translation);
	planeLocal.setW( w-dot );
	planeInOut = planeLocal;
}


template <typename FT>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<FT>::mul4xyz1Points( const typename hkRealTypes<FT>::Transform& t, const typename hkRealTypes<FT>::Vector* vectorsIn, int numVectors, typename hkRealTypes<FT>::Vector* vectorsOut )
{
	HK_MATH_ASSERT( 0xf0237abe, numVectors > 0, "At least one element required");
	typename hkRealTypes<FT>::Transform unaliased = t;
	int i = numVectors - 1;
	do
	{
		vectorsOut[i]._setTransformedPos( unaliased, vectorsIn[i] );
	} while( --i >= 0 );
}


template <typename FT>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<FT>::transformSpheres( const typename hkRealTypes<FT>::Transform& t, const typename hkRealTypes<FT>::Vector* vectorsIn, int numVectors, typename hkRealTypes<FT>::Vector* vectorsOut )
{
	HK_MATH_ASSERT( 0xf0237abf, numVectors > 0, "At least one element required");
	typename hkRealTypes<FT>::Transform unaliased = t;
	int i = numVectors - 1;
	do
	{
		typename hkRealTypes<FT>::Vector v;
		v._setTransformedPos( unaliased, vectorsIn[i] ); // position
		v.setW(vectorsIn[i]);			// radius
		vectorsOut[i] = v;
	} while( --i >= 0 );
}


template <typename FT>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<FT>::transformSpheres( const typename hkRealTypes<FT>::QsTransform& t, const typename hkRealTypes<FT>::Vector* vectorsIn, int numVectors, typename hkRealTypes<FT>::Vector* vectorsOut )
{
	HK_MATH_ASSERT( 0xf0237abf, numVectors > 0, "At least one element required");
	typename hkRealTypes<FT>::QsTransform unaliased = t;
	int i = numVectors - 1;
	do
	{
		typename hkRealTypes<FT>::Vector v;
		v._setTransformedPos( unaliased, vectorsIn[i] ); // position
		v.setW(vectorsIn[i]);			// radius
		vectorsOut[i] = v;
	} while( --i >= 0 );
}


template <typename FT>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<FT>::rotatePoints( const typename hkRealTypes<FT>::Matrix3& t, const typename hkRealTypes<FT>::Vector* vectorsIn, int numVectors, typename hkRealTypes<FT>::Vector* vectorsOut )
{
	HK_MATH_ASSERT( 0xf0237ac0, numVectors > 0, "At least one element required");
	typename hkRealTypes<FT>::Matrix3 unaliased = t;
	int i = numVectors - 1;
	do
	{
		vectorsOut[i]._setRotatedDir( unaliased, vectorsIn[i] );
	} while( --i >= 0 );
}

#ifndef HK_VECTOR4fUTIL_transpose
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::transpose(hkVector4f& v0, hkVector4f& v1, hkVector4f& v2)
{
	HK_TRANSPOSE3f(v0, v1, v2);
}
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::transpose(hkVector4f& v0, hkVector4f& v1, hkVector4f& v2, hkVector4f& v3)
{
	HK_TRANSPOSE4f(v0, v1, v2, v3);
}
#endif
#ifndef HK_VECTOR4dUTIL_transpose
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::transpose(hkVector4d& v0, hkVector4d& v1, hkVector4d& v2)
{
	HK_TRANSPOSE3d(v0, v1, v2);
}
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::transpose(hkVector4d& v0, hkVector4d& v1, hkVector4d& v2, hkVector4d& v3)
{
	HK_TRANSPOSE4d(v0, v1, v2, v3);
}
#endif


#ifndef HK_VECTOR4fUTIL_rotateInversePoints
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::rotateInversePoints( const hkRotationf& t, const hkVector4f* vectorsIn, int numVectors, hkVector4f* vectorsOut )
{
	HK_MATH_ASSERT( 0xf0237ac1, numVectors > 0, "At least one element required");

#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	hkVector4f c0 = t.getColumn<0>();
	hkVector4f c1 = t.getColumn<1>();
	hkVector4f c2 = t.getColumn<2>();
	HK_TRANSPOSE3f(c0,c1,c2);

	for( int i = 0; i < numVectors; ++i )
	{
		const hkVector4f b = vectorsIn[i];
		const hkSimdFloat32 b0 = b.getComponent<0>();
		hkVector4f r0; r0.setMul( c0, b0 );
		const hkSimdFloat32 b1 = b.getComponent<1>();
		hkVector4f r1; r1.setMul( c1, b1 );
		const hkSimdFloat32 b2 = b.getComponent<2>();
		hkVector4f r2; r2.setMul( c2, b2 );

		hkVector4f out; 
		out.setAdd(r0,r1);
		out.add(r2);

		vectorsOut[i] = out;
	}
#else
	hkRotationf unaliased = t;
	int i = numVectors - 1;
	do
	{
		vectorsOut[i]._setRotatedInverseDir( unaliased, vectorsIn[i] );
	} while( --i >= 0 );
#endif
}
#endif
#ifndef HK_VECTOR4dUTIL_rotateInversePoints
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::rotateInversePoints( const hkRotationd& t, const hkVector4d* vectorsIn, int numVectors, hkVector4d* vectorsOut )
{
	HK_MATH_ASSERT( 0xf0237ac1, numVectors > 0, "At least one element required");

#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	hkVector4d c0 = t.getColumn<0>();
	hkVector4d c1 = t.getColumn<1>();
	hkVector4d c2 = t.getColumn<2>();
	HK_TRANSPOSE3d(c0,c1,c2);

	for( int i = 0; i < numVectors; ++i )
	{
		const hkVector4d b = vectorsIn[i];
		const hkSimdDouble64 b0 = b.getComponent<0>();
		hkVector4d r0; r0.setMul( c0, b0 );
		const hkSimdDouble64 b1 = b.getComponent<1>();
		hkVector4d r1; r1.setMul( c1, b1 );
		const hkSimdDouble64 b2 = b.getComponent<2>();
		hkVector4d r2; r2.setMul( c2, b2 );

		hkVector4d out; 
		out.setAdd(r0,r1);
		out.add(r2);

		vectorsOut[i] = out;
	}
#else
	hkRotationd unaliased = t;
	int i = numVectors - 1;
	do
	{
		vectorsOut[i]._setRotatedInverseDir( unaliased, vectorsIn[i] );
	} while( --i >= 0 );
#endif
}
#endif

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<FT>::setMul( const typename hkRealTypes<FT>::Matrix3& aTb, const typename hkRealTypes<FT>::Matrix3& bTc, typename hkRealTypes<FT>::Matrix3& aTcOut )
{
	HK_ASSERT(0x6d9d1d43,  &aTcOut != &aTb );
	HK_ASSERT(0x64a8df81,  &aTcOut != &bTc );
	rotatePoints( aTb, &bTc.getColumn(0), 3, &aTcOut.getColumn(0) );
}

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<FT>::setInverseMul( const typename hkRealTypes<FT>::Rotation& bTa, const typename hkRealTypes<FT>::Matrix3& bTc, typename hkRealTypes<FT>::Matrix3& aTcOut )
{
	rotateInversePoints( bTa, &bTc.getColumn(0), 3, &aTcOut.getColumn(0) );
}

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<FT>::_setMulInverseMul( const typename hkRealTypes<FT>::Transform& bTa, const typename hkRealTypes<FT>::Transform &bTc, typename hkRealTypes<FT>::Transform* tOut )
{
	typename hkRealTypes<FT>::Vector h; h.setSub(bTc.getTranslation(), bTa.getTranslation() );

	typename hkRealTypes<FT>::Vector tmpRot0;	tmpRot0._setRotatedInverseDir( bTa.getRotation(), bTc.template getColumn<0>() );
	typename hkRealTypes<FT>::Vector tmpRot1;	tmpRot1._setRotatedInverseDir( bTa.getRotation(), bTc.template getColumn<1>() );
	typename hkRealTypes<FT>::Vector tmpRot2;	tmpRot2._setRotatedInverseDir( bTa.getRotation(), bTc.template getColumn<2>() );
	typename hkRealTypes<FT>::Vector tmpRot3;	tmpRot3._setRotatedInverseDir( bTa.getRotation(), h);
	tOut->template setColumn<0>(tmpRot0);
	tOut->template setColumn<1>(tmpRot1);
	tOut->template setColumn<2>(tmpRot2);
	tOut->template setColumn<3>(tmpRot3);
}


template <typename FT>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<FT>::buildOrthonormal( typename hkRealTypes<FT>::VectorParameter dir, typename hkRealTypes<FT>::Matrix3& out )
{
	typename hkRealTypes<FT>::Vector perp;
	calculatePerpendicularVector( dir, perp );
	perp.template normalize<3>();

	typename hkRealTypes<FT>::Vector cross;
	cross.setCross( dir, perp );

	out.template setColumn<0>(dir);
	out.template setColumn<1>(perp);
	out.template setColumn<2>(cross);
}

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<FT>::buildOrthonormal( typename hkRealTypes<FT>::VectorParameter dir, typename hkRealTypes<FT>::VectorParameter dir2, typename hkRealTypes<FT>::Matrix3& out )
{
	typename hkRealTypes<FT>::Vector cross;
	cross.setCross( dir, dir2 );
	if ( cross.template lengthSquared<3>() < hkRealTypes<FT>::Scalar::template getConstant<HK_QUADREAL_EPS_SQRD>() )
	{
		buildOrthonormal( dir, out );
		return;
	}
	cross.template normalize<3>();

	typename hkRealTypes<FT>::Vector cross1;
	cross1.setCross( cross, dir );

	out.template setColumn<0>(dir);
	out.template setColumn<1>(cross1);
	out.template setColumn<2>(cross);
}


#ifndef HK_VECTOR4fUTIL_dot3_3vs3
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::dot3_3vs3(hkVector4fParameter a0, hkVector4fParameter b0, hkVector4fParameter a1, hkVector4fParameter b1, hkVector4fParameter a2, hkVector4fParameter b2, hkVector4f& dotsOut)
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	hkVector4f c0; c0.setMul(a0,b0);
	hkVector4f c1; c1.setMul(a1,b1);
	hkVector4f c2; c2.setMul(a2,b2);

	HK_TRANSPOSE3f(c0,c1,c2);

	dotsOut.setAdd(c0,c1);
	dotsOut.add(c2);
#else
	dotsOut.setComponent<0>( a0.dot<3>( b0 ) );
	dotsOut.setComponent<1>( a1.dot<3>( b1 ) );
	dotsOut.setComponent<2>( a2.dot<3>( b2 ) );
#if !defined(HK_DEBUG)
	dotsOut.zeroComponent<3>();
#else
	HK_ON_DEBUG( ((hkUint32*)&dotsOut)[3] = 0xffffffff; )
#endif
#endif
}
#endif
#ifndef HK_VECTOR4dUTIL_dot3_3vs3
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::dot3_3vs3(hkVector4dParameter a0, hkVector4dParameter b0, hkVector4dParameter a1, hkVector4dParameter b1, hkVector4dParameter a2, hkVector4dParameter b2, hkVector4d& dotsOut)
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	hkVector4d c0; c0.setMul(a0,b0);
	hkVector4d c1; c1.setMul(a1,b1);
	hkVector4d c2; c2.setMul(a2,b2);

	HK_TRANSPOSE3d(c0,c1,c2);

	dotsOut.setAdd(c0,c1);
	dotsOut.add(c2);
#else
	dotsOut.setComponent<0>( a0.dot<3>( b0 ) );
	dotsOut.setComponent<1>( a1.dot<3>( b1 ) );
	dotsOut.setComponent<2>( a2.dot<3>( b2 ) );
#if !defined(HK_DEBUG)
	dotsOut.zeroComponent<3>();
#else
	HK_ON_DEBUG( ((hkUint64*)&dotsOut)[3] = 0xffffffffffffffffull; )
#endif
#endif
}
#endif


#ifndef HK_VECTOR4fUTIL_dot3_4vs4
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::dot3_4vs4( hkVector4fParameter a0, hkVector4fParameter b0, hkVector4fParameter a1, hkVector4fParameter b1, hkVector4fParameter a2, hkVector4fParameter b2, hkVector4fParameter a3, hkVector4fParameter b3, hkVector4f& dotsOut)
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	hkVector4f c0; c0.setMul(a0,b0);
	hkVector4f c1; c1.setMul(a1,b1);
	hkVector4f c2; c2.setMul(a2,b2);
	hkVector4f c3; c3.setMul(a3,b3);

	HK_TRANSPOSE4f(c0,c1,c2,c3);

	dotsOut.setAdd(c0,c1);
	dotsOut.add(c2);
#else
	dotsOut.set( a0.dot<3>( b0 ),
		a1.dot<3>( b1 ),
		a2.dot<3>( b2 ),
		a3.dot<3>( b3 ) );
#endif
}
#endif
#ifndef HK_VECTOR4dUTIL_dot3_4vs4
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::dot3_4vs4( hkVector4dParameter a0, hkVector4dParameter b0, hkVector4dParameter a1, hkVector4dParameter b1, hkVector4dParameter a2, hkVector4dParameter b2, hkVector4dParameter a3, hkVector4dParameter b3, hkVector4d& dotsOut)
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	hkVector4d c0; c0.setMul(a0,b0);
	hkVector4d c1; c1.setMul(a1,b1);
	hkVector4d c2; c2.setMul(a2,b2);
	hkVector4d c3; c3.setMul(a3,b3);

	HK_TRANSPOSE4d(c0,c1,c2,c3);

	dotsOut.setAdd(c0,c1);
	dotsOut.add(c2);
#else
	dotsOut.set( a0.dot<3>( b0 ),
		a1.dot<3>( b1 ),
		a2.dot<3>( b2 ),
		a3.dot<3>( b3 ) );
#endif
}
#endif


#ifndef HK_VECTOR4fUTIL_dot4_4vs4
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::dot4_4vs4( hkVector4fParameter a0, hkVector4fParameter b0, hkVector4fParameter a1, hkVector4fParameter b1, hkVector4fParameter a2, hkVector4fParameter b2, hkVector4fParameter a3, hkVector4fParameter b3, hkVector4f& dotsOut)
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	hkVector4f c0; c0.setMul(a0,b0);
	hkVector4f c1; c1.setMul(a1,b1);
	hkVector4f c2; c2.setMul(a2,b2);
	hkVector4f c3; c3.setMul(a3,b3);

	HK_TRANSPOSE4f(c0,c1,c2,c3);

	hkVector4f s; s.setAdd(c2, c3);
	dotsOut.setAdd(c0,c1);
	dotsOut.add(s);
#else
	dotsOut.set( a0.dot<4>( b0 ),
		a1.dot<4>( b1 ),
		a2.dot<4>( b2 ),
		a3.dot<4>( b3 ) );
#endif
}
#endif
#ifndef HK_VECTOR4dUTIL_dot4_4vs4
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::dot4_4vs4( hkVector4dParameter a0, hkVector4dParameter b0, hkVector4dParameter a1, hkVector4dParameter b1, hkVector4dParameter a2, hkVector4dParameter b2, hkVector4dParameter a3, hkVector4dParameter b3, hkVector4d& dotsOut)
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	hkVector4d c0; c0.setMul(a0,b0);
	hkVector4d c1; c1.setMul(a1,b1);
	hkVector4d c2; c2.setMul(a2,b2);
	hkVector4d c3; c3.setMul(a3,b3);

	HK_TRANSPOSE4d(c0,c1,c2,c3);

	hkVector4d s; s.setAdd(c2, c3);
	dotsOut.setAdd(c0,c1);
	dotsOut.add(s);
#else
	dotsOut.set( a0.dot<4>( b0 ),
		a1.dot<4>( b1 ),
		a2.dot<4>( b2 ),
		a3.dot<4>( b3 ) );
#endif
}
#endif



#ifndef HK_VECTOR4fUTIL_dot3_1vs4
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::dot3_1vs4( hkVector4fParameter vectorIn, hkVector4fParameter a0, hkVector4fParameter a1, hkVector4fParameter a2, hkVector4fParameter a3, hkVector4f& dotsOut)
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	hkVector4f c0; c0.setMul(a0, vectorIn);
	hkVector4f c1; c1.setMul(a1, vectorIn);
	hkVector4f c2; c2.setMul(a2, vectorIn);
	hkVector4f c3; c3.setMul(a3, vectorIn);

	HK_TRANSPOSE4f(c0, c1, c2, c3);

	dotsOut.setAdd(c0, c1);
	dotsOut.add(c2);
#else
	dotsOut.set( a0.dot<3>( vectorIn ),
		a1.dot<3>( vectorIn ),
		a2.dot<3>( vectorIn ),
		a3.dot<3>( vectorIn ) );
#endif
}
#endif
#ifndef HK_VECTOR4dUTIL_dot3_1vs4
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::dot3_1vs4( hkVector4dParameter vectorIn, hkVector4dParameter a0, hkVector4dParameter a1, hkVector4dParameter a2, hkVector4dParameter a3, hkVector4d& dotsOut)
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	hkVector4d c0; c0.setMul(a0, vectorIn);
	hkVector4d c1; c1.setMul(a1, vectorIn);
	hkVector4d c2; c2.setMul(a2, vectorIn);
	hkVector4d c3; c3.setMul(a3, vectorIn);

	HK_TRANSPOSE4d(c0, c1, c2, c3);

	dotsOut.setAdd(c0, c1);
	dotsOut.add(c2);
#else
	dotsOut.set( a0.dot<3>( vectorIn ),
		a1.dot<3>( vectorIn ),
		a2.dot<3>( vectorIn ),
		a3.dot<3>( vectorIn ) );
#endif
}
#endif


//
//	Sets this vector components: this(i) = vector.dot<3>(AI) for i=0..2

#ifndef HK_VECTOR4fUTIL_dot3_1vs3
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::dot3_1vs3(hkVector4fParameter vectorIn, hkVector4fParameter a0, hkVector4fParameter a1, hkVector4fParameter a2, hkVector4f& dotsOut)
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	hkVector4f c0; c0.setMul(a0, vectorIn);
	hkVector4f c1; c1.setMul(a1, vectorIn);
	hkVector4f c2; c2.setMul(a2, vectorIn);

	HK_TRANSPOSE3f(c0, c1, c2);

	dotsOut.setAdd(c0, c1);
	dotsOut.add(c2);
#else
	dotsOut.set( a0.dot<3>( vectorIn ),
		a1.dot<3>( vectorIn ),
		a2.dot<3>( vectorIn ),
		hkSimdFloat32_0 );
#endif
}
#endif
#ifndef HK_VECTOR4dUTIL_dot3_1vs3
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::dot3_1vs3(hkVector4dParameter vectorIn, hkVector4dParameter a0, hkVector4dParameter a1, hkVector4dParameter a2, hkVector4d& dotsOut)
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	hkVector4d c0; c0.setMul(a0, vectorIn);
	hkVector4d c1; c1.setMul(a1, vectorIn);
	hkVector4d c2; c2.setMul(a2, vectorIn);

	HK_TRANSPOSE3d(c0, c1, c2);

	dotsOut.setAdd(c0, c1);
	dotsOut.add(c2);
#else
	dotsOut.set( a0.dot<3>( vectorIn ),
		a1.dot<3>( vectorIn ),
		a2.dot<3>( vectorIn ),
		hkSimdDouble64_0 );
#endif
}
#endif



#ifndef HK_VECTOR4fUTIL_dot4_1vs4
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::dot4_1vs4( hkVector4fParameter vectorIn, hkVector4fParameter a0, hkVector4fParameter a1, hkVector4fParameter a2, hkVector4fParameter a3, hkVector4f& dotsOut)
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	hkVector4f c0; c0.setMul(a0, vectorIn);
	hkVector4f c1; c1.setMul(a1, vectorIn);
	hkVector4f c2; c2.setMul(a2, vectorIn);
	hkVector4f c3; c3.setMul(a3, vectorIn);

	HK_TRANSPOSE4f(c0, c1, c2, c3);

	hkVector4f s; s.setAdd(c2, c3);
	dotsOut.setAdd(c0, c1);
	dotsOut.add(s);
#else
	dotsOut.set( a0.dot<4>( vectorIn ),
		a1.dot<4>( vectorIn ),
		a2.dot<4>( vectorIn ),
		a3.dot<4>( vectorIn ) );
#endif
}
#endif
#ifndef HK_VECTOR4dUTIL_dot4_1vs4
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::dot4_1vs4( hkVector4dParameter vectorIn, hkVector4dParameter a0, hkVector4dParameter a1, hkVector4dParameter a2, hkVector4dParameter a3, hkVector4d& dotsOut)
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	hkVector4d c0; c0.setMul(a0, vectorIn);
	hkVector4d c1; c1.setMul(a1, vectorIn);
	hkVector4d c2; c2.setMul(a2, vectorIn);
	hkVector4d c3; c3.setMul(a3, vectorIn);

	HK_TRANSPOSE4d(c0, c1, c2, c3);

	hkVector4d s; s.setAdd(c2, c3);
	dotsOut.setAdd(c0, c1);
	dotsOut.add(s);
#else
	dotsOut.set( a0.dot<4>( vectorIn ),
		a1.dot<4>( vectorIn ),
		a2.dot<4>( vectorIn ),
		a3.dot<4>( vectorIn ) );
#endif
}
#endif


//
//	Sets this vector components: this(i) = vector.dot<4>(AI) for i=0..2

#ifndef HK_VECTOR4fUTIL_dot4_1vs3
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::dot4_1vs3( hkVector4fParameter vectorIn, hkVector4fParameter a0, hkVector4fParameter a1, hkVector4fParameter a2, hkVector4f& dotsOut)
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	hkVector4f c0; c0.setMul(a0, vectorIn);
	hkVector4f c1; c1.setMul(a1, vectorIn);
	hkVector4f c2; c2.setMul(a2, vectorIn);
	hkVector4f c3; c3.setZero();
	HK_TRANSPOSE4f(c0, c1, c2, c3);

	hkVector4f s; s.setAdd(c2, c3);
	dotsOut.setAdd(c0, c1);
	dotsOut.add(s);
#else
	dotsOut.set( a0.dot<4>( vectorIn ), a1.dot<4>( vectorIn ), a2.dot<4>( vectorIn ), hkSimdFloat32_0 );
#endif
}
#endif	
#ifndef HK_VECTOR4dUTIL_dot4_1vs3
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::dot4_1vs3( hkVector4dParameter vectorIn, hkVector4dParameter a0, hkVector4dParameter a1, hkVector4dParameter a2, hkVector4d& dotsOut)
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	hkVector4d c0; c0.setMul(a0, vectorIn);
	hkVector4d c1; c1.setMul(a1, vectorIn);
	hkVector4d c2; c2.setMul(a2, vectorIn);
	hkVector4d c3; c3.setZero();
	HK_TRANSPOSE4d(c0, c1, c2, c3);

	hkVector4d s; s.setAdd(c2, c3);
	dotsOut.setAdd(c0, c1);
	dotsOut.add(s);
#else
	dotsOut.set( a0.dot<4>( vectorIn ), a1.dot<4>( vectorIn ), a2.dot<4>( vectorIn ), hkSimdDouble64_0 );
#endif
}
#endif	

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<FT>::dot4xyz1_1vs4( typename hkRealTypes<FT>::VectorParameter vectorIn, typename hkRealTypes<FT>::VectorParameter a0, typename hkRealTypes<FT>::VectorParameter a1, typename hkRealTypes<FT>::VectorParameter a2, typename hkRealTypes<FT>::VectorParameter a3, typename hkRealTypes<FT>::Vector& dotsOut)
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	typename hkRealTypes<FT>::Vector c0; c0.setMul(a0, vectorIn);
	typename hkRealTypes<FT>::Vector c1; c1.setMul(a1, vectorIn);
	typename hkRealTypes<FT>::Vector c2; c2.setMul(a2, vectorIn);
	typename hkRealTypes<FT>::Vector c3; c3.setMul(a3, vectorIn);

	transpose(c0, c1, c2, c3);
	typename hkRealTypes<FT>::Vector w; w.setAll(vectorIn.getW());
	typename hkRealTypes<FT>::Vector s; s.setAdd(c2, w);
	dotsOut.setAdd(c0, c1);
	dotsOut.add(s);
#else
	dotsOut.set( vectorIn.dot4xyz1( a0 ),
		vectorIn.dot4xyz1( a1 ),
		vectorIn.dot4xyz1( a2 ),
		vectorIn.dot4xyz1( a3 ) );
#endif
}


#ifndef HK_VECTOR4fUTIL_dot3_2vs2
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::dot3_2vs2( hkVector4fParameter a0, hkVector4fParameter a2, hkVector4fParameter b0, hkVector4fParameter b1, hkVector4f& dotsOut)
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	hkVector4f c0; c0.setMul(a0,b0);
	hkVector4f c1; c1.setMul(a0,b1);
	hkVector4f c2; c2.setMul(a2,b0);
	hkVector4f c3; c3.setMul(a2,b1);

	HK_TRANSPOSE4f(c0,c1,c2,c3);

	dotsOut.setAdd(c0,c1);
	dotsOut.add(c2);
#else
	dotsOut.set( a0.dot<3>( b0 ),
		a0.dot<3>( b1 ),
		a2.dot<3>( b0 ),
		a2.dot<3>( b1 ) );
#endif
}
#endif
#ifndef HK_VECTOR4dUTIL_dot3_2vs2
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::dot3_2vs2( hkVector4dParameter a0, hkVector4dParameter a2, hkVector4dParameter b0, hkVector4dParameter b1, hkVector4d& dotsOut)
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	hkVector4d c0; c0.setMul(a0,b0);
	hkVector4d c1; c1.setMul(a0,b1);
	hkVector4d c2; c2.setMul(a2,b0);
	hkVector4d c3; c3.setMul(a2,b1);

	HK_TRANSPOSE4d(c0,c1,c2,c3);

	dotsOut.setAdd(c0,c1);
	dotsOut.add(c2);
#else
	dotsOut.set( a0.dot<3>( b0 ),
		a0.dot<3>( b1 ),
		a2.dot<3>( b0 ),
		a2.dot<3>( b1 ) );
#endif
}
#endif


//
//	Computes an = (a x n), bn = (b x n), cn = (c x n)

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<FT>::cross_3vs1(	typename hkRealTypes<FT>::VectorParameter a, typename hkRealTypes<FT>::VectorParameter b, typename hkRealTypes<FT>::VectorParameter c, typename hkRealTypes<FT>::VectorParameter n,
																typename hkRealTypes<FT>::Vector& an, typename hkRealTypes<FT>::Vector& bn, typename hkRealTypes<FT>::Vector& cn)
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	typename hkRealTypes<FT>::Vector tmp_n; tmp_n.template setPermutation<hkVectorPermutation::ZXYW>(n);
	typename hkRealTypes<FT>::Vector tmp_a; tmp_a.template setPermutation<hkVectorPermutation::YZXW>(a);
	typename hkRealTypes<FT>::Vector tmp_b; tmp_b.template setPermutation<hkVectorPermutation::YZXW>(b);
	typename hkRealTypes<FT>::Vector tmp_c; tmp_c.template setPermutation<hkVectorPermutation::YZXW>(c);

	tmp_a.mul(tmp_n);
	tmp_b.mul(tmp_n);
	tmp_c.mul(tmp_n);

	typename hkRealTypes<FT>::Vector p_n; p_n.template setPermutation<hkVectorPermutation::YZXW>(n);
	typename hkRealTypes<FT>::Vector p_a; p_a.template setPermutation<hkVectorPermutation::ZXYW>(a);
	typename hkRealTypes<FT>::Vector p_b; p_b.template setPermutation<hkVectorPermutation::ZXYW>(b);
	typename hkRealTypes<FT>::Vector p_c; p_c.template setPermutation<hkVectorPermutation::ZXYW>(c);

	an.setSubMul(tmp_a, p_n, p_a);
	bn.setSubMul(tmp_b, p_n, p_b);
	cn.setSubMul(tmp_c, p_n, p_c);
#else
	an.setCross(a, n);
	bn.setCross(b, n);
	cn.setCross(c, n);
#endif
}


//
//	Computes an = (a x n), bn = (b x n), cn = (c x n), dn = (d x n)

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<FT>::cross_4vs1(	typename hkRealTypes<FT>::VectorParameter a, typename hkRealTypes<FT>::VectorParameter b, typename hkRealTypes<FT>::VectorParameter c, typename hkRealTypes<FT>::VectorParameter d, typename hkRealTypes<FT>::VectorParameter n,
																typename hkRealTypes<FT>::Vector& an, typename hkRealTypes<FT>::Vector& bn, typename hkRealTypes<FT>::Vector& cn, typename hkRealTypes<FT>::Vector& dn)
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	typename hkRealTypes<FT>::Vector tmp4; tmp4.template setPermutation<hkVectorPermutation::ZXYW>(n);

	typename hkRealTypes<FT>::Vector t_a; t_a.template setPermutation<hkVectorPermutation::YZXW>(a);
	typename hkRealTypes<FT>::Vector t_b; t_b.template setPermutation<hkVectorPermutation::YZXW>(b);
	typename hkRealTypes<FT>::Vector t_c; t_c.template setPermutation<hkVectorPermutation::YZXW>(c);
	typename hkRealTypes<FT>::Vector t_d; t_d.template setPermutation<hkVectorPermutation::YZXW>(d);

	t_a.mul(tmp4);
	t_b.mul(tmp4);
	t_c.mul(tmp4);
	t_d.mul(tmp4);

	typename hkRealTypes<FT>::Vector ntmp4; ntmp4.template setPermutation<hkVectorPermutation::YZXW>(n);

	typename hkRealTypes<FT>::Vector p_a; p_a.template setPermutation<hkVectorPermutation::ZXYW>(a);
	typename hkRealTypes<FT>::Vector p_b; p_b.template setPermutation<hkVectorPermutation::ZXYW>(b);
	typename hkRealTypes<FT>::Vector p_c; p_c.template setPermutation<hkVectorPermutation::ZXYW>(c);
	typename hkRealTypes<FT>::Vector p_d; p_d.template setPermutation<hkVectorPermutation::ZXYW>(d);

	an.setSubMul(t_a, ntmp4, p_a);
	bn.setSubMul(t_b, ntmp4, p_b);
	cn.setSubMul(t_c, ntmp4, p_c);
	dn.setSubMul(t_d, ntmp4, p_d);
#else
	an.setCross(a, n);
	bn.setCross(b, n);
	cn.setCross(c, n);
	dn.setCross(d, n);
#endif
}


//
//	Computes the cross products: (vA, vB), (vB, vC), (vC, vA)

template <typename FT>
HK_FORCE_INLINE void hkVector4UtilImpl<FT>::computeCyclicCrossProducts(	typename hkRealTypes<FT>::VectorParameter vA, typename hkRealTypes<FT>::VectorParameter vB, typename hkRealTypes<FT>::VectorParameter vC,
																		typename hkRealTypes<FT>::Vector& vAB, typename hkRealTypes<FT>::Vector& vBC, typename hkRealTypes<FT>::Vector& vCA)
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	typename hkRealTypes<FT>::Vector tmpa; tmpa.template setPermutation<hkVectorPermutation::YZXW>(vA);	// tmpa = (ay, az, ax, *)
	typename hkRealTypes<FT>::Vector tmpb; tmpb.template setPermutation<hkVectorPermutation::ZXYW>(vB);	// tmpb = (bz, bx, by, *)
	typename hkRealTypes<FT>::Vector tmpc; tmpc.template setPermutation<hkVectorPermutation::YZXW>(vC);	// tmpc = (cy, cz, cx, *)
	typename hkRealTypes<FT>::Vector tmpd; tmpd.template setPermutation<hkVectorPermutation::ZXYW>(vA);	// tmpd = (az, ax, ay, *)

	typename hkRealTypes<FT>::Vector ab; ab.setMul(tmpa, tmpb);	// (ay * bz, az * bx, ax * by, *)
	typename hkRealTypes<FT>::Vector bc; bc.setMul(tmpb, tmpc);	// (bz * cy, bx * cz, by * cx, *)
	typename hkRealTypes<FT>::Vector ca; ca.setMul(tmpc, tmpd);	// (cy * az, cz * ax, cx * ay, *)

	typename hkRealTypes<FT>::Vector pb; pb.template setPermutation<hkVectorPermutation::YZXW>(vB);	// tmpb = (by, bz, bx, *)
	typename hkRealTypes<FT>::Vector pc; pc.template setPermutation<hkVectorPermutation::ZXYW>(vC);	// tmpc = (cz, cx, cy, *)
	vAB.setSubMul(ab, tmpd, pb);					// (ay * bz, az * bx, ax * by, *) - (az * by, ax * bz, ay * bx, *) = (vA x vB)
	typename hkRealTypes<FT>::Vector sb; sb.setMul(pb, pc);											// tmpb = (by * cz, bz * cx, bx * cy, *)
	vCA.setSubMul(ca, pc, tmpa);					// (cy * az, cz * ax, cx * ay, *) - (cz * ay, cx * az, cy * ax, *) = (vC x vA)
	vBC.setSub(sb, bc);										// (by * cz, bz * cx, bx * cy, *) - (bz * cy, bx * cz, by * cx, *) = (vB x vC)*/
#else
	vAB.setCross(vA, vB);
	vBC.setCross(vB, vC);
	vCA.setCross(vC, vA);
#endif
}


template <typename FT>
HK_FORCE_INLINE void hkVector4UtilImpl<FT>::computeQuadEdgePlanes( typename hkRealTypes<FT>::VectorParameter vA, typename hkRealTypes<FT>::VectorParameter vB, typename hkRealTypes<FT>::VectorParameter vC, typename hkRealTypes<FT>::VectorParameter vD, typename hkRealTypes<FT>::Vector* normalOut, typename hkRealTypes<FT>::Transform* edgesOut )
{
	typename hkRealTypes<FT>::Vector vAB;	vAB.setSub(vB, vA);
	typename hkRealTypes<FT>::Vector vBC;	vBC.setSub(vC, vB);
	typename hkRealTypes<FT>::Vector normal;	normal.setCross(vAB, vBC );
	normal.template normalize<3>();

	// Find closest point in A
	normal.setW(-normal.template dot<3>(vA));
	*normalOut = normal;

	// edges
	typename hkRealTypes<FT>::Vector vCD;	vCD.setSub(vD, vC);
	typename hkRealTypes<FT>::Vector vDA;	vDA.setSub(vA, vD);
	typename hkRealTypes<FT>::Vector epA, epB, epC, epD; 
	cross_4vs1( vAB, vBC, vCD, vDA, normal, epA, epB, epC, epD );

	typename hkRealTypes<FT>::Vector o; dot3_4vs4( vA, epA, vB, epB, vC, epC, vD, epD, o );

	edgesOut->setRows4( epA, epB, epC, epD );
	typename hkRealTypes<FT>::Vector len2; 
	len2.setMul( edgesOut->template getColumn<0>(), edgesOut->template getColumn<0>() );
	len2.addMul( edgesOut->template getColumn<1>(), edgesOut->template getColumn<1>() );
	len2.addMul( edgesOut->template getColumn<2>(), edgesOut->template getColumn<2>() );
	typename hkRealTypes<FT>::Vector invLen; invLen.template setSqrtInverse<HK_ACC_12_BIT, HK_SQRT_SET_ZERO>( len2 );

	typename hkRealTypes<FT>::Vector offset; 
	offset.setMul( edgesOut->template getColumn<0>(), vA );
	offset.addMul( edgesOut->template getColumn<1>(), vB );
	offset.addMul( edgesOut->template getColumn<2>(), edgesOut->template getColumn<2>() );

	edgesOut->getColumn(0).mul(invLen);
	edgesOut->getColumn(1).mul(invLen);
	edgesOut->getColumn(2).mul(invLen);
	invLen.template setNeg<4>(invLen);
	edgesOut->getColumn(3).setMul( o, invLen);
}



#ifndef HK_VECTOR4UTIL_exitMmx
template <typename FT>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<FT>::exitMmx()
{
}
#endif


template <typename FT>
HK_FORCE_INLINE const typename hkRealTypes<FT>::Scalar HK_CALL hkVector4UtilImpl<FT>::distToLineSquared( typename hkRealTypes<FT>::VectorParameter a, typename hkRealTypes<FT>::VectorParameter b, typename hkRealTypes<FT>::VectorParameter p )
{
	typename hkRealTypes<FT>::Vector ab, ap;
	ab.setSub( b, a );
	ap.setSub( p, a );

	typename hkRealTypes<FT>::Scalar projectionAsPercentOfSegment; 
	projectionAsPercentOfSegment.setDiv( ap.template dot<3>(ab), ab.template lengthSquared<3>() );
	ap.subMul( projectionAsPercentOfSegment, ab );
	return ap.template lengthSquared<3>();
}


template <typename FT>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<FT>::setMax44(typename hkRealTypes<FT>::VectorParameter a, typename hkRealTypes<FT>::VectorParameter b, typename hkRealTypes<FT>::VectorParameter c, typename hkRealTypes<FT>::VectorParameter d, typename hkRealTypes<FT>::Vector& out)
{
	typename hkRealTypes<FT>::Vector	t0; t0.setMax(a,b);
	typename hkRealTypes<FT>::Vector	t1; t1.setMax(c,d);
	out.setMax(t0,t1);
}

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<FT>::setMin44(typename hkRealTypes<FT>::VectorParameter a, typename hkRealTypes<FT>::VectorParameter b, typename hkRealTypes<FT>::VectorParameter c, typename hkRealTypes<FT>::VectorParameter d, typename hkRealTypes<FT>::Vector& out)
{
	typename hkRealTypes<FT>::Vector	t0; t0.setMin(a,b);
	typename hkRealTypes<FT>::Vector	t1; t1.setMin(c,d);
	out.setMin(t0,t1);
}


// we need to convert the quaternion to int. To avoid problems
// at -1 and 1, we encode [-1.1 .. 1.1]
#define HK_VECTOR4UTIL_PACK_RANGE 1.1f
template <typename FT>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<FT>::unPackInt32IntoQuaternion( hkUint32 ivalue, typename hkRealTypes<FT>::Vector& qout )
{
	HK_ALIGN_FLOAT(hkUint32 abcd[4]);
	abcd[0] = ivalue;
	abcd[1] = ivalue >> 8;
	abcd[2] = ivalue >> 16;
	abcd[3] = ivalue >> 24;

	hkIntVector p; p.load<4>(&abcd[0]);
	hkIntVector f; f.setAll(0xff);
	hkIntVector c; c.setAnd(p,f);
	hkIntVector h; h.setAll(0x80);
	hkIntVector i; i.setSubU32(c,h); i.convertS32ToF32(qout);

	typename hkRealTypes<FT>::Scalar scale; scale.setFromFloat(typename hkRealTypes<FT>::Pod(HK_VECTOR4UTIL_PACK_RANGE/128.0f));
	qout.mul(scale);
}


#ifndef HK_VECTOR4fUTIL_convertQuaternionToRotation
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::convertQuaternionToRotation( hkQuaternionfParameter qi, hkRotationf& rotationOut )
{
	
	HK_MATH_ASSERT(0x1ff88f0e, qi.isOk(), "hkQuaternionf not normalized/invalid!");
	const hkVector4f q = qi.m_vec;

	hkVector4f q2; q2.setAdd(q,q);
	hkVector4f xq2; xq2.setMul(q2, q.getComponent<0>());
	hkVector4f yq2; yq2.setMul(q2, q.getComponent<1>());
	hkVector4f zq2; zq2.setMul(q2, q.getComponent<2>());
	hkVector4f wq2; wq2.setMul(q2, q.getComponent<3>());

	const hkSimdFloat32 one = hkSimdFloat32_1;
	hkSimdFloat32 zero; zero.setZero();

	// 	1-(yy+zz),	xy+wz,		xz-wy
	// 	xy-wz,		1-(xx+zz),	yz+wx
	// 	xz+wy,		yz-wx,		1-(xx+yy)
	hkVector4f c0; c0.set( one-(yq2.getComponent<1>()+zq2.getComponent<2>()), xq2.getComponent<1>()+wq2.getComponent<2>(), xq2.getComponent<2>()-wq2.getComponent<1>(), zero );
	hkVector4f c1; c1.set( xq2.getComponent<1>()-wq2.getComponent<2>(), one-(xq2.getComponent<0>()+zq2.getComponent<2>()), yq2.getComponent<2>()+wq2.getComponent<0>(), zero );
	hkVector4f c2; c2.set( xq2.getComponent<2>()+wq2.getComponent<1>(), yq2.getComponent<2>()-wq2.getComponent<0>(), one-(xq2.getComponent<0>()+yq2.getComponent<1>()), zero );

	rotationOut.setColumn<0>(c0);
	rotationOut.setColumn<1>(c1);
	rotationOut.setColumn<2>(c2);
}
#endif
#ifndef HK_VECTOR4dUTIL_convertQuaternionToRotation
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::convertQuaternionToRotation( hkQuaterniondParameter qi, hkRotationd& rotationOut )
{
	
	HK_MATH_ASSERT(0x1ff88f0e, qi.isOk(), "hkQuaterniond not normalized/invalid!");
	const hkVector4d q = qi.m_vec;

	hkVector4d q2; q2.setAdd(q,q);
	hkVector4d xq2; xq2.setMul(q2, q.getComponent<0>());
	hkVector4d yq2; yq2.setMul(q2, q.getComponent<1>());
	hkVector4d zq2; zq2.setMul(q2, q.getComponent<2>());
	hkVector4d wq2; wq2.setMul(q2, q.getComponent<3>());

	const hkSimdDouble64 one = hkSimdDouble64_1;
	hkSimdDouble64 zero; zero.setZero();

	// 	1-(yy+zz),	xy+wz,		xz-wy
	// 	xy-wz,		1-(xx+zz),	yz+wx
	// 	xz+wy,		yz-wx,		1-(xx+yy)
	hkVector4d c0; c0.set( one-(yq2.getComponent<1>()+zq2.getComponent<2>()), xq2.getComponent<1>()+wq2.getComponent<2>(), xq2.getComponent<2>()-wq2.getComponent<1>(), zero );
	hkVector4d c1; c1.set( xq2.getComponent<1>()-wq2.getComponent<2>(), one-(xq2.getComponent<0>()+zq2.getComponent<2>()), yq2.getComponent<2>()+wq2.getComponent<0>(), zero );
	hkVector4d c2; c2.set( xq2.getComponent<2>()+wq2.getComponent<1>(), yq2.getComponent<2>()-wq2.getComponent<0>(), one-(xq2.getComponent<0>()+yq2.getComponent<1>()), zero );

	rotationOut.setColumn<0>(c0);
	rotationOut.setColumn<1>(c1);
	rotationOut.setColumn<2>(c2);
}
#endif


template <typename FT>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<FT>::setXAtVectorMax( typename hkRealTypes<FT>::VectorParameter check, hkIntVector& iVinOut, typename hkRealTypes<FT>::Vector& v0InOut, typename hkRealTypes<FT>::Vector& v1InOut)
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED) && !defined(HK_USING_GENERIC_INT_VECTOR_IMPLEMENTATION)
	typename hkRealTypes<FT>::Vector zw; zw.template setPermutation<hkVectorPermutation::ZWZW>( check );
	typename hkRealTypes<FT>::Comparison zwGreater = zw.greater( check );

	zw.setMax( zw, check );
	hkIntVector ivXY, ivZW;   ivZW.setPermutation<hkVectorPermutation::ZWZW>( iVinOut ); ivXY.setSelect( zwGreater, ivZW, iVinOut );
	typename hkRealTypes<FT>::Vector   v0XY, v0ZW;   v0ZW.template setPermutation<hkVectorPermutation::ZWZW>( v0InOut ); v0XY.setSelect( zwGreater, v0ZW, v0InOut );
	typename hkRealTypes<FT>::Vector   v1XY, v1ZW;   v1ZW.template setPermutation<hkVectorPermutation::ZWZW>( v1InOut ); v1XY.setSelect( zwGreater, v1ZW, v1InOut );

	typename hkRealTypes<FT>::Vector y; y.template setBroadcast<1>( zw );
	typename hkRealTypes<FT>::Comparison yGreater = y.greater( zw );

	hkIntVector ivY; ivY.setBroadcast<1>( ivXY ); iVinOut.setSelect( yGreater, ivY, ivXY );
	typename hkRealTypes<FT>::Vector v0Y;   v0Y.template setBroadcast<1>( v0XY ); v0InOut.setSelect( yGreater, v0Y, v0XY );
	typename hkRealTypes<FT>::Vector v1Y;   v1Y.template setBroadcast<1>( v1XY ); v1InOut.setSelect( yGreater, v1Y, v1XY );

#else
	int index = check.template getIndexOfMaxComponent<4>();
	iVinOut.setAll( iVinOut.getU32(index) );
	v0InOut.setBroadcast(index, v0InOut );
	v1InOut.setBroadcast(index, v1InOut );
#endif
}


#define HK_VECTOR4UTIL_PERM_MASK \
	hkVectorPermutation::Permutation( \
	((i & 0x3) << 12) \
	| ((j & 0x3) << 8) \
	| ((k & 0x3) << 4) \
	| ((l & 0x3) << 0))

#define HK_VECTOR4UTIL_SELECT_MASK \
	hkVector4ComparisonMask::Mask( \
	((i & 0x4) ? 0 : hkVector4ComparisonMask::MASK_X) \
	| ((j & 0x4) ? 0 : hkVector4ComparisonMask::MASK_Y) \
	| ((k & 0x4) ? 0 : hkVector4ComparisonMask::MASK_Z) \
	| ((l & 0x4) ? 0 : hkVector4ComparisonMask::MASK_W))

#ifndef HK_VECTOR4fUTIL_setPermutation2
template <typename FT>
template<unsigned int i, unsigned int j, unsigned int k, unsigned int l>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<FT>::setPermutation2(hkVector4fParameter a, hkVector4fParameter b, hkVector4f & out)
{
	HK_COMPILE_TIME_ASSERT(i<8 && j<8 && k<8 && l<8);

	hkVector4f aPerm; aPerm.setPermutation<HK_VECTOR4UTIL_PERM_MASK>(a);
	hkVector4f bPerm; bPerm.setPermutation<HK_VECTOR4UTIL_PERM_MASK>(b);
	out.setSelect<HK_VECTOR4UTIL_SELECT_MASK>(aPerm, bPerm);
}
#endif
#ifndef HK_VECTOR4dUTIL_setPermutation2
template <typename FT>
template<unsigned int i, unsigned int j, unsigned int k, unsigned int l>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<FT>::setPermutation2(hkVector4dParameter a, hkVector4dParameter b, hkVector4d & out)
{
	HK_COMPILE_TIME_ASSERT(i<8 && j<8 && k<8 && l<8);

	hkVector4d aPerm; aPerm.setPermutation<HK_VECTOR4UTIL_PERM_MASK>(a);
	hkVector4d bPerm; bPerm.setPermutation<HK_VECTOR4UTIL_PERM_MASK>(b);
	out.setSelect<HK_VECTOR4UTIL_SELECT_MASK>(aPerm, bPerm);
}
#endif

#undef HK_VECTOR4UTIL_PERM_MASK
#undef HK_VECTOR4UTIL_SELECT_MASK

#ifndef HK_VECTOR4UTIL_sortVectorIncreasing
template <typename FT>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<FT>::sortVectorIncreasing(typename hkRealTypes<FT>::Vector& xyzw)
{
	// Implemented as a 5-comparator, 3-round sorting network
	// Round 1: X/Z, Y/W
	{
		hkVector4 zwxy; zwxy.setPermutation<hkVectorPermutation::ZWXY>(xyzw);
		hkVector4Comparison comp = xyzw.less(zwxy);
		hkVector4Comparison czw; czw.set<hkVector4Comparison::MASK_ZW>();
		comp.setXor(comp, czw);
		xyzw.setSelect(comp, xyzw, zwxy);
	}

	// Round 2: X/Y, Z/W
	{
		hkVector4 yxwz; yxwz.setPermutation<hkVectorPermutation::YXWZ>(xyzw);
		hkVector4Comparison comp = xyzw.less(yxwz);
		hkVector4Comparison cyw; cyw.set<hkVector4Comparison::MASK_YW>();
		comp.setXor(comp, cyw);
		xyzw.setSelect(comp, xyzw, yxwz);
	}

	// Round 3: Y/Z
	{
		hkVector4 xzyw; xzyw.setPermutation<hkVectorPermutation::XZYW>(xyzw);
		hkVector4Comparison comp = xyzw.less(xzyw);
		hkVector4Comparison cz; cz.set<hkVector4Comparison::MASK_Z>();
		comp.setXor(comp, cz);
		xyzw.setSelect(comp, xyzw, xzyw);
	}
}
#endif

#ifndef HK_VECTOR4UTIL_sortVectorDecreasing
template <typename FT>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<FT>::sortVectorDecreasing(typename hkRealTypes<FT>::Vector& xyzw)
{
	// Implemented as a 5-comparator, 3-round sorting network
	// Round 1: X/Z, Y/W
	{
		hkVector4 zwxy; zwxy.setPermutation<hkVectorPermutation::ZWXY>(xyzw);
		hkVector4Comparison comp = xyzw.greater(zwxy);
		hkVector4Comparison czw; czw.set<hkVector4Comparison::MASK_ZW>();
		comp.setXor(comp, czw);
		xyzw.setSelect(comp, xyzw, zwxy);
	}

	// Round 2: X/Y, Z/W
	{
		hkVector4 yxwz; yxwz.setPermutation<hkVectorPermutation::YXWZ>(xyzw);
		hkVector4Comparison comp = xyzw.greater(yxwz);
		hkVector4Comparison cyw; cyw.set<hkVector4Comparison::MASK_YW>();
		comp.setXor(comp, cyw);
		xyzw.setSelect(comp, xyzw, yxwz);
	}

	// Round 3: Y/Z
	{
		hkVector4 xzyw; xzyw.setPermutation<hkVectorPermutation::XZYW>(xyzw);
		hkVector4Comparison comp = xyzw.greater(xzyw);
		hkVector4Comparison cz; cz.set<hkVector4Comparison::MASK_Z>();
		comp.setXor(comp, cz);
		xyzw.setSelect(comp, xyzw, xzyw);
	}
}
#endif

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<FT>::setLength( typename hkRealTypes<FT>::ScalarParameter desiredLength, typename hkRealTypes<FT>::Vector& vectorInOut )
{
	typename hkRealTypes<FT>::Vector v = vectorInOut;
	typename hkRealTypes<FT>::Scalar newLenInv = v.template lengthInverse<3, HK_ACC_23_BIT, HK_SQRT_SET_ZERO>();
	typename hkRealTypes<FT>::Scalar factor = newLenInv * desiredLength;
	vectorInOut.setMul( v, factor );
}

template <typename FT>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<FT>::setProjectedLength( typename hkRealTypes<FT>::ScalarParameter desiredLength, typename hkRealTypes<FT>::VectorParameter scaleMeasurePlane, typename hkRealTypes<FT>::ScalarParameter maxScale, typename hkRealTypes<FT>::Vector& vectorInOut )
{
	typename hkRealTypes<FT>::Vector v = vectorInOut;
	typename hkRealTypes<FT>::Scalar dot2 = v.template dot<3>(scaleMeasurePlane);
	typename hkRealTypes<FT>::Vector v2; v2.setSubMul( v, scaleMeasurePlane, dot2 );

	typename hkRealTypes<FT>::Scalar newLenInv = v2.template lengthInverse<3, HK_ACC_23_BIT, HK_SQRT_SET_ZERO>();
	typename hkRealTypes<FT>::Scalar factor = newLenInv * desiredLength;
	factor.setMin( factor, maxScale );
	factor.setMax( factor, -maxScale );
	vectorInOut.setMul( v, factor );
}


#ifndef HK_VECTOR4fUTIL_convertComparison
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::convertComparison(hkVector4fComparisonParameter cin, hkVector4dComparison& cout)
{
	cout.set(cin.getMask());
}
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkFloat32>::convertComparison(hkVector4fComparisonParameter cin, hkVector4fComparison& cout)
{
	cout.m_mask = cin.m_mask;
}
#endif
#ifndef HK_VECTOR4dUTIL_convertComparison
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::convertComparison(hkVector4dComparisonParameter cin, hkVector4fComparison& cout)
{
	cout.set(cin.getMask());
}
template <>
HK_FORCE_INLINE void HK_CALL hkVector4UtilImpl<hkDouble64>::convertComparison(hkVector4dComparisonParameter cin, hkVector4dComparison& cout)
{
	cout.m_mask = cin.m_mask;
}
#endif

template <typename FT>
void hkVector4UtilImpl<FT>::getFloatToInt16FloorCorrection(typename hkRealTypes<FT>::Pod& out)
{
	typename hkRealTypes<FT>::Pod l = typename hkRealTypes<FT>::Pod(10);
	typename hkRealTypes<FT>::Pod h = typename hkRealTypes<FT>::Pod(11);
	typename hkRealTypes<FT>::Vector one = hkRealTypes<FT>::Vector::template getConstant<HK_QUADREAL_1>();

	for (int i = 0; i < 23; i++ )
	{
		typename hkRealTypes<FT>::Pod m = (l+h) * typename hkRealTypes<FT>::Pod(0.5f);
		typename hkRealTypes<FT>::Vector p; p.setAll( m );

		hkIntUnion64 iout;
		convertToUint16( p, hkRealTypes<FT>::Vector::getZero(), one, iout );

		if ( iout.u16[0] < 11 )
		{
			l = m;
		}
		else
		{
			h = m;
		}
	}
	out = (l+h) * typename hkRealTypes<FT>::Pod(0.5f) - typename hkRealTypes<FT>::Pod(11);
}

template <typename FT>
void hkVector4UtilImpl<FT>::getFloatToInt32FloorCorrection(typename hkRealTypes<FT>::Pod& out)
{
	typename hkRealTypes<FT>::Pod l = typename hkRealTypes<FT>::Pod(10);
	typename hkRealTypes<FT>::Pod h = typename hkRealTypes<FT>::Pod(11);
	typename hkRealTypes<FT>::Vector one = hkRealTypes<FT>::Vector::template getConstant<HK_QUADREAL_1>();

	for (int i = 0; i < 23; i++ )
	{
		typename hkRealTypes<FT>::Pod m = (l+h) * typename hkRealTypes<FT>::Pod(0.5f);
		typename hkRealTypes<FT>::Vector p; p.setAll( m );

		hkUint32 iout[4];
		convertToUint32( p, hkRealTypes<FT>::Vector::getZero(), one, iout );

		if ( iout[0] < 11 )
		{
			l = m;
		}
		else
		{
			h = m;
		}
	}
	out = (l+h) * typename hkRealTypes<FT>::Pod(0.5f) - typename hkRealTypes<FT>::Pod(11);
}


// we need to convert the quaternion to int. To avoid problems
// at -1 and 1, we encode [-1.1 .. 1.1]
// pack a quaternion into a single 32 bit integer
template <typename FT>
hkUint32 hkVector4UtilImpl<FT>::packQuaternionIntoInt32( typename hkRealTypes<FT>::VectorParameter qin )
{
	typename hkRealTypes<FT>::Vector x;
	x.setAddMul(hkRealTypes<FT>::Vector::template getConstant<HK_QUADREAL_INV_2>(), qin, hkRealTypes<FT>::Scalar::fromFloat(typename hkRealTypes<FT>::Pod(128.0f/HK_VECTOR4UTIL_PACK_RANGE)));

	hkIntVector i; i.setConvertF32toS32(x);
	hkIntVector c; c.setAll(0x80);
	hkIntVector r; r.setAddU32(i,c);
	hkIntVector f; f.setAll(0xff);
	hkIntVector p; p.setAnd(r,f);

	HK_ALIGN_FLOAT(hkUint32 abcd[4]);
	p.store<4>(&abcd[0]);

	return abcd[0] | (abcd[1] << 8) | (abcd[2] << 16) | (abcd[3] << 24);
}
#undef HK_VECTOR4UTIL_PACK_RANGE


//
// Conversions
//

//
template <typename FT>
const char* hkVector4UtilImpl<FT>::toString3(typename hkRealTypes<FT>::VectorParameter x, hkStringBuf& s, char separator)
{
	s.printf("%f%c%f%c%f",(float)x(0),separator,(float)x(1),separator,(float)x(2));
	return s;
}

//
template <typename FT>
const char* hkVector4UtilImpl<FT>::toString4(typename hkRealTypes<FT>::VectorParameter x, hkStringBuf& s, char separator)
{
	s.printf("%f%c%f%c%f%c%f",(float)x(0),separator,(float)x(1),separator,(float)x(2),separator,(float)x(3));
	return s;
}

template <typename FT>
void HK_CALL hkVector4UtilImpl<FT>::convert4QuaternionsToRotations( const typename hkRealTypes<FT>::Quaternion* HK_RESTRICT quats, 
	typename hkRealTypes<FT>::Rotation* HK_RESTRICT r0Out, typename hkRealTypes<FT>::Rotation* HK_RESTRICT r1Out,
	typename hkRealTypes<FT>::Rotation* HK_RESTRICT r2Out, typename hkRealTypes<FT>::Rotation* HK_RESTRICT r3Out )
{
	convertQuaternionToRotation( quats[0], *r0Out );
	convertQuaternionToRotation( quats[1], *r1Out );
	convertQuaternionToRotation( quats[2], *r2Out );
	convertQuaternionToRotation( quats[3], *r3Out );
}

template <typename FT>
void HK_CALL hkVector4UtilImpl<FT>::convertQuaternionToRotationNoInline( typename hkRealTypes<FT>::QuaternionParameter qi, typename hkRealTypes<FT>::Rotation& rotationOut )
{
	convertQuaternionToRotation(qi,rotationOut);
}

//
template <typename FT>
bool HK_CALL hkVector4UtilImpl<FT>::computeAffineTransformFromTriangles(	typename hkRealTypes<FT>::VectorParameter sa, typename hkRealTypes<FT>::VectorParameter sb, typename hkRealTypes<FT>::VectorParameter sc,
	typename hkRealTypes<FT>::VectorParameter da, typename hkRealTypes<FT>::VectorParameter db, typename hkRealTypes<FT>::VectorParameter dc,
	typename hkRealTypes<FT>::Transform& transformOut)
{
	typename hkRealTypes<FT>::Vector c0,c1,c2;

	c0.setSub(sb,sa);
	c1.setSub(sc,sa);
	c2.setCross(c0,c1);
	typename hkRealTypes<FT>::Matrix3	sm; sm.setCols(c0,c1,c2);

	typename hkRealTypes<FT>::Scalar eps = hkRealTypes<FT>::Scalar::template getConstant<HK_QUADREAL_EPS>();
	if(sm.invert(eps.getReal()) == HK_SUCCESS)
	{
		c0.setSub(db,da);
		c1.setSub(dc,da);
		c2.setCross(c0,c1);
		typename hkRealTypes<FT>::Matrix3	dm; dm.setCols(c0,c1,c2);

		transformOut.getRotation().setMul(dm,sm);

		typename hkRealTypes<FT>::Vector	offset; offset._setRotatedDir(transformOut.getRotation(), sa);

		transformOut.getTranslation().setSub(da, offset);

		return true;
	}
	return false;
}

//
template <typename FT>
/*static*/ HK_FORCE_INLINE const typename hkRealTypes<FT>::Scalar HK_CALL hkVector4UtilImpl<FT>::toRange(typename hkRealTypes<FT>::ScalarParameter v, typename hkRealTypes<FT>::ScalarParameter radius, typename hkRealTypes<FT>::ScalarParameter diameter, typename hkRealTypes<FT>::Scalar& k)
{
	typedef typename hkRealTypes<FT>::Scalar Sc;

	Sc diamr; diamr.template setReciprocal<HK_ACC_FULL, HK_DIV_IGNORE>(diameter);
	
	return toRange(v, radius, diameter, diamr, k);
}

template <typename FT>
/*static*/ HK_FORCE_INLINE const typename hkRealTypes<FT>::Scalar HK_CALL hkVector4UtilImpl<FT>::toRange(typename hkRealTypes<FT>::ScalarParameter v, typename hkRealTypes<FT>::ScalarParameter radius, typename hkRealTypes<FT>::Scalar& k)
{
	typedef typename hkRealTypes<FT>::Scalar Sc;

	Sc diam; diam.setMul(radius, Sc::template getConstant<HK_QUADREAL_2>());
	Sc diamr; diamr.template setReciprocal<HK_ACC_FULL, HK_DIV_IGNORE>(diam);

	return toRange(v, radius, diam, diamr, k);
}

template <typename FT>
/*static*/ HK_FORCE_INLINE const typename hkRealTypes<FT>::Scalar HK_CALL hkVector4UtilImpl<FT>::toRange(typename hkRealTypes<FT>::ScalarParameter v, typename hkRealTypes<FT>::ScalarParameter radius, typename hkRealTypes<FT>::ScalarParameter diameter, typename hkRealTypes<FT>::ScalarParameter diameterReciprocal, typename hkRealTypes<FT>::Scalar& k)
{
	typedef typename hkRealTypes<FT>::Scalar Sc;
	typedef typename hkRealTypes<FT>::Comparison Cmp;

	// Compute the number of 2Pi multiples needed.
	Sc kf; kf.setAdd(v, radius); kf.mul(diameterReciprocal); 
	k.setFloor(kf);
	Sc cv; cv.setSubMul(v, k, diameter);

	// Be paranoid about edge cases (TODO J.N: check numerical analysis).
	Sc mradius; mradius.setMul(radius, Sc::template getConstant<HK_QUADREAL_MINUS1>());
	Sc cvc; cvc.setClamped(cv, mradius, radius);
	if (!cvc.isEqual(cv))
	{
		Cmp gt = cv.greater(radius);
		Cmp lt = cv.less(mradius);

		Sc gkfi; gkfi.setAdd(k, Sc::template getConstant<HK_QUADREAL_1>());
		Sc gcv; gcv.setSub(cv, diameter);
		Sc lkfi; lkfi.setSub(k, Sc::template getConstant<HK_QUADREAL_1>());
		Sc lcv; lcv.setAdd(cv, diameter);
	
		cv.setSelect(gt, gcv, cv);
		k.setSelect(gt, gkfi, k);
		cv.setSelect(lt, lcv, cv);
		k.setSelect(lt, lkfi, k);

#ifdef HK_DEBUG
		Sc clamped; clamped.setClamped(cv, mradius, radius);
		HK_ASSERT(0x15a82a34, clamped.isEqual(cv));
#endif
	}

	return cv;
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
