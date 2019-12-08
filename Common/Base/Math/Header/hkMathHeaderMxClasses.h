/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#include <Common/Base/Math/Types/Mx/hkMxMathTypes.h>
#include <Common/Base/Math/Vector/Mx/hkMxHalf8.h>
#include <Common/Base/Math/Vector/Mx/hkMxMask.h>
#include <Common/Base/Math/Vector/Mx/hkMxQuaternion.h>
#include <Common/Base/Math/Vector/Mx/hkMxReal.h>
#include <Common/Base/Math/Vector/Mx/hkMxSingle.h>
#include <Common/Base/Math/Vector/Mx/hkMxVector.h>
#include <Common/Base/Math/Vector/Mx/hkMxVectorUtil.h>
#include <Common/Base/Math/Vector/hk4xVector2.h>

# if defined(HK_REAL_IS_DOUBLE)

template <int M> class hkMxVector : public hkMxVectord<M> {};
#define hkMxVectorParameter hkMxVectordParameter

template <int M> class hkMxQuaternion : public hkMxQuaterniond<M> {};
#define hkMxQuaternionParameter hkMxQuaterniondParameter

template <int M> class hkMxReal : public hkMxReald<M> {};
#define hkMxRealParameter hkMxRealdParameter

template <int M> class hkMxSingle : public hkMxSingled<M> {};
#define hkMxSingleParameter hkMxSingledParameter

template <int M> class hkMxMask : public hkMxMaskd<M> {};

typedef hkMxTransformd hkMxTransform;
typedef hkPackedReald hkPackedReal;
typedef hk4xSingled hk4xSingle;
typedef hk4xVector4d hk4xVector4;
typedef hk4xVector2d hk4xVector2;
typedef hk4xReald hk4xReal; 
typedef hk4xMaskd hk4xMask;

#else

template <int M> class hkMxVector : public hkMxVectorf<M> {};
#define hkMxVectorParameter hkMxVectorfParameter

template <int M> class hkMxQuaternion : public hkMxQuaternionf<M> {};
#define hkMxQuaternionParameter hkMxQuaternionfParameter;


template <int M> class hkMxReal : public hkMxRealf<M> {};
#define hkMxRealParameter hkMxRealfParameter

template <int M> class hkMxSingle : public hkMxSinglef<M> {};
#define hkMxSingleParameter hkMxSinglefParameter

template <int M> class hkMxMask : public hkMxMaskf<M> {};

typedef hkMxTransformf hkMxTransform;
typedef hkPackedRealf hkPackedReal;
typedef hk4xSinglef hk4xSingle;
typedef hk4xVector4f hk4xVector4;
typedef hk4xVector2f hk4xVector2;
typedef hk4xRealf hk4xReal; 
typedef hk4xMaskf hk4xMask;

#endif

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
