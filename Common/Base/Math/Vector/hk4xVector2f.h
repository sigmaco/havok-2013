/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_4X_VECTOR2f_H
#define HK_4X_VECTOR2f_H

class hk4xVector2f
{
public:
	template<hkVectorPermutation::Permutation i>
	HK_FORCE_INLINE void setPermutation( const hk4xVector2f& v );

	/// this = v[i]
	template<int i>
	HK_FORCE_INLINE void selectVector( const hk4xVector2f& v );

	HK_FORCE_INLINE static void dotPerpendicular( const hk4xVector2f& a, const hk4xVector2f& b, hkVector4f& dotOut );

	HK_FORCE_INLINE static void dot( const hk4xVector2f& a, const hk4xVector2f& b, hkVector4f& dotOut );

	HK_FORCE_INLINE void setAddMul( const hk4xVector2f& a, const hk4xVector2f& b, hkVector4fParameter t );

	HK_FORCE_INLINE void setMul( const hk4xVector2f& a, hkVector4fParameter t );

	HK_FORCE_INLINE void set( hkSimdFloat32Parameter x, hkSimdFloat32Parameter y);

	//HK_FORCE_INLINE void set( const hk4xVector4& v );

	HK_FORCE_INLINE void set( hkVector4fParameter uAxis, hkVector4fParameter vAxis, hkVector4fParameter offset,
		hkVector4fParameter v0, hkVector4fParameter v1, hkVector4fParameter v2, hkVector4fParameter v3 );

	HK_FORCE_INLINE void set( hkVector4fParameter uAxis, hkVector4fParameter vAxis, 
		hkVector4fParameter v0, hkVector4fParameter v1, hkVector4fParameter v2, hkVector4fParameter v3 );

	HK_FORCE_INLINE void transform(hkVector4fParameter colX, hkVector4fParameter colY, hkVector4fParameter translate, hkVector4f &x)
	{
		x.setAddMul(translate, colX, m_x);
		x.addMul(colY, m_y);
	}

	template<hkVector4ComparisonMask::Mask M>
	HK_FORCE_INLINE void setSelect( const hk4xVector2f& v0, const hk4xVector2f& v1 );

	template<hkMathAccuracyMode A, hkMathNegSqrtMode S>
	HK_FORCE_INLINE void setNormalize( const hk4xVector2f& v0 );

	// convert to 4 vectors
	//HK_FORCE_INLINE void convertToMxVector( hk4xVector4& v ) const;

	HK_FORCE_INLINE static void getFromArray(const hk4xVector2f* HK_RESTRICT vectors, hkUint32 i, hkSimdFloat32 &xOut, hkSimdFloat32 &yOut);

	HK_FORCE_INLINE static hk4xVector2f getFromArray2D(const hk4xVector2f* HK_RESTRICT vectors, hkUint32 i);

	HK_FORCE_INLINE void setSelect(hkVector4fComparisonParameter cmp, const hk4xVector2f& a0, const hk4xVector2f& b0);

#define DEFINE_HK4XVECTOR2D_FUNCTION2(TYPE)	void TYPE( const hk4xVector2f& a0, const hk4xVector2f& b0)	{		m_x.TYPE( a0.m_x, b0.m_x );		m_y.TYPE( a0.m_y, b0.m_y );	}

//	DEFINE_HK4XVECTOR2D_FUNCTION2(setAdd);
	DEFINE_HK4XVECTOR2D_FUNCTION2(setSub);
	DEFINE_HK4XVECTOR2D_FUNCTION2(setDiv);

#undef DEFINE_HK4XVECTOR2D_FUNCTION2

	hkVector4f m_x;
	hkVector4f m_y;
};

#include <Common/Base/Math/Vector/hk4xVector2f.inl>

#endif // HK_4X_VECTOR2f_H

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
