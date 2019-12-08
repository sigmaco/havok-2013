/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_4X_VECTOR2d_H
#define HK_4X_VECTOR2d_H

class hk4xVector2d
{
public:
	template<hkVectorPermutation::Permutation i>
	HK_FORCE_INLINE void setPermutation( const hk4xVector2d& v );

	/// this = v[i]
	template<int i>
	HK_FORCE_INLINE void selectVector( const hk4xVector2d& v );

	HK_FORCE_INLINE static void dotPerpendicular( const hk4xVector2d& a, const hk4xVector2d& b, hkVector4d& dotOut );

	HK_FORCE_INLINE static void dot( const hk4xVector2d& a, const hk4xVector2d& b, hkVector4d& dotOut );

	HK_FORCE_INLINE void setAddMul( const hk4xVector2d& a, const hk4xVector2d& b, hkVector4dParameter t );

	HK_FORCE_INLINE void setMul( const hk4xVector2d& a, hkVector4dParameter t );

	HK_FORCE_INLINE void set( hkSimdDouble64Parameter x, hkSimdDouble64Parameter y);

	//HK_FORCE_INLINE void set( const hk4xVector4& v );

	HK_FORCE_INLINE void set( hkVector4dParameter uAxis, hkVector4dParameter vAxis, hkVector4dParameter offset,
		hkVector4dParameter v0, hkVector4dParameter v1, hkVector4dParameter v2, hkVector4dParameter v3 );

	HK_FORCE_INLINE void set( hkVector4dParameter uAxis, hkVector4dParameter vAxis, 
		hkVector4dParameter v0, hkVector4dParameter v1, hkVector4dParameter v2, hkVector4dParameter v3 );

	HK_FORCE_INLINE void transform(hkVector4dParameter colX, hkVector4dParameter colY, hkVector4dParameter translate, hkVector4d &x)
	{
		x.setAddMul(translate, colX, m_x);
		x.addMul(colY, m_y);
	}

	template<hkVector4ComparisonMask::Mask M>
	HK_FORCE_INLINE void setSelect( const hk4xVector2d& v0, const hk4xVector2d& v1 );

	template<hkMathAccuracyMode A, hkMathNegSqrtMode S>
	HK_FORCE_INLINE void setNormalize( const hk4xVector2d& v0 );

	// convert to 4 vectors
	//HK_FORCE_INLINE void convertToMxVector( hk4xVector4& v ) const;

	HK_FORCE_INLINE static void getFromArray(const hk4xVector2d* HK_RESTRICT vectors, hkUint32 i, hkSimdDouble64 &xOut, hkSimdDouble64 &yOut);

	HK_FORCE_INLINE static hk4xVector2d getFromArray2D(const hk4xVector2d* HK_RESTRICT vectors, hkUint32 i);

	HK_FORCE_INLINE void setSelect(hkVector4dComparisonParameter cmp, const hk4xVector2d& a0, const hk4xVector2d& b0);

#define DEFINE_HK4XVECTOR2D_FUNCTION2(TYPE)	void TYPE( const hk4xVector2d& a0, const hk4xVector2d& b0)	{		m_x.TYPE( a0.m_x, b0.m_x );		m_y.TYPE( a0.m_y, b0.m_y );	}

//	DEFINE_HK4XVECTOR2D_FUNCTION2(setAdd);
	DEFINE_HK4XVECTOR2D_FUNCTION2(setSub);
	DEFINE_HK4XVECTOR2D_FUNCTION2(setDiv);

#undef DEFINE_HK4XVECTOR2D_FUNCTION2

	hkVector4d m_x;
	hkVector4d m_y;
};

#include <Common/Base/Math/Vector/hk4xVector2d.inl>

#endif // HK_4X_VECTOR2d_H

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
