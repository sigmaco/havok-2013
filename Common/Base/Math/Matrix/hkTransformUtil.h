/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_MATH_TRANSFORM_UTIL_H
#define HK_MATH_TRANSFORM_UTIL_H

#include <Common/Base/Math/Vector/hkVector4Util.h>
#include <Common/Base/Math/Matrix/hkMatrix3Util.h>

/// Miscellaneous operations on hkTransforms
template <typename FT>
class hkTransformUtilImpl
{
public:

	typedef hkTransformUtilImpl<FT> ThisType;
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_MATH, ThisType);

	/// Sets resultOut to be the product of t1 by the inverse of t2. (resultOut = t1 * Inverse(t2))
	static HK_FORCE_INLINE void HK_CALL _computeMulInverse(const typename hkRealTypes<FT>::Transform& t1, const typename hkRealTypes<FT>::Transform& t2, typename hkRealTypes<FT>::Transform& resultOut);

	/// Converts a hkQTransform to a hkTransform
	static HK_FORCE_INLINE void HK_CALL _convert(const typename hkRealTypes<FT>::QTransform& from, typename hkRealTypes<FT>::Transform& to);

	/// Converts a (hkQuaternion, hkVector4) pair to a hkTransform
	static HK_FORCE_INLINE void HK_CALL _convert(typename hkRealTypes<FT>::QuaternionParameter fromRot, typename hkRealTypes<FT>::VectorParameter fromPos, typename hkRealTypes<FT>::Transform& to);

	static HK_FORCE_INLINE void HK_CALL _mulTransformTransform( const typename hkRealTypes<FT>::Transform& aTb, const typename hkRealTypes<FT>::Transform& bTc, typename hkRealTypes<FT>::Transform* tOut );
};

#include <Common/Base/Math/Matrix/hkTransformUtil.inl>

typedef hkTransformUtilImpl<hkFloat32>  hkTransformfUtil;
typedef hkTransformUtilImpl<hkDouble64> hkTransformdUtil;

#if defined(HK_REAL_IS_DOUBLE)
typedef hkTransformdUtil hkTransformUtil;
#else
typedef hkTransformfUtil hkTransformUtil;
#endif

#endif		//	HK_MATH_TRANSFORM_UTIL_H

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
