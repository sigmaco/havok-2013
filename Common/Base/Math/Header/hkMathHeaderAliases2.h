/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#include <Common/Base/Math/Matrix/hkMatrixDecomposition.h>
#include <Common/Base/Math/Matrix/hkMatrix6.h>
#include <Common/Base/Math/Util/hkConvertCoordinateSpace.h>
#include <Common/Base/Math/Vector/hkVector2.h>
#include <Common/Base/Math/Vector/hkVectorN.h>
#include <Common/Base/Math/Matrix/hkMatrixNm.h>


# if defined(HK_REAL_IS_DOUBLE)

	#define HK_TRANSPOSE3 HK_TRANSPOSE3d
	#define HK_TRANSPOSE4 HK_TRANSPOSE4d

	typedef hkVector8d hkVector8;
	typedef hkMatrix6d hkMatrix6;
	typedef hkVectorNd hkVectorN;
	typedef hkMatrixdNm hkMatrixNm;
	typedef hkVector2d hkVector2;

	template <int SIZE> class hkInplaceVectorN : public hkInplaceVectorNd<SIZE> {};
	typedef hkVectorNd hkVectorN;

#else

	#define HK_TRANSPOSE3 HK_TRANSPOSE3f
	#define HK_TRANSPOSE4 HK_TRANSPOSE4f

	typedef hkVector8f hkVector8;
	typedef hkMatrix6f hkMatrix6;
	typedef hkVectorNf hkVectorN;
	typedef hkMatrixfNm hkMatrixNm;
	typedef hkVector2f hkVector2;

	template <int SIZE> class hkInplaceVectorN : public hkInplaceVectorNf<SIZE> {};
	typedef hkVectorNf hkVectorN;

#endif


# if defined(HK_REAL_IS_DOUBLE)
	#define hkFourTransposedPoints hkFourTransposedPointsd
	#define hkSweptTransform hkSweptTransformd
	extern "C"
	{
		// implementation of _setMul as out of line function with C-binding
		HK_FORCE_INLINE void hkMatrix3_setMulMat3Mat3( hkMatrix3d* thisMatrix, const hkMatrix3d& aTb, const hkMatrix3d& bTc )
		{
			hkMatrix3d_setMulMat3Mat3( thisMatrix, aTb, bTc );
		}

		HK_FORCE_INLINE void hkMatrix3_invertSymmetric( hkMatrix3d& thisMatrix )
		{
			hkMatrix3d_invertSymmetric( thisMatrix );
		}
	}
	extern "C"
	{
		HK_FORCE_INLINE void HK_CALL hkMatrix6Add(hkMatrix6d& aOut, const hkMatrix6d& b) { hkMatrix6dAdd(aOut, b);  }
		HK_FORCE_INLINE void HK_CALL hkMatrix6Sub(hkMatrix6d& aOut, const hkMatrix6d& b) { hkMatrix6dSub(aOut, b);  }
		HK_FORCE_INLINE void HK_CALL hkMatrix6SetMul(hkMatrix6d& out, const hkMatrix6d&a, const hkMatrix6d&b ) { hkMatrix6dSetMul(out, a, b);  }
		HK_FORCE_INLINE void HK_CALL hkMatrix6SetMulV(hkVector8d& out, const hkMatrix6d&a, const hkVector8d& b) { hkMatrix6dSetMulV(out, a, b);  }
		HK_FORCE_INLINE void HK_CALL hkMatrix6SetTranspose(hkMatrix6d& out, const hkMatrix6d&in ) { hkMatrix6dSetTranspose(out, in);  }
		HK_FORCE_INLINE void HK_CALL hkMatrix6SetInvert(hkMatrix6d& out, const hkMatrix6d& in ) { hkMatrix6dSetInvert(out, in);  }
	}
# else
	#define hkFourTransposedPoints hkFourTransposedPointsf
	#define hkSweptTransform hkSweptTransformf
	extern "C"
	{
		// implementation of _setMul as out of line function with C-binding
		HK_FORCE_INLINE void hkMatrix3_setMulMat3Mat3( hkMatrix3f* thisMatrix, const hkMatrix3f& aTb, const hkMatrix3f& bTc )
		{
			hkMatrix3f_setMulMat3Mat3( thisMatrix, aTb, bTc );
		}

		HK_FORCE_INLINE void hkMatrix3_invertSymmetric( hkMatrix3f& thisMatrix )
		{
			hkMatrix3f_invertSymmetric( thisMatrix );
		}
	}
	extern "C"
	{
		HK_FORCE_INLINE void HK_CALL hkMatrix6Add(hkMatrix6f& aOut, const hkMatrix6f& b) { hkMatrix6fAdd(aOut, b);  }
		HK_FORCE_INLINE void HK_CALL hkMatrix6Sub(hkMatrix6f& aOut, const hkMatrix6f& b) { hkMatrix6fSub(aOut, b);  }
		HK_FORCE_INLINE void HK_CALL hkMatrix6SetMul(hkMatrix6f& out, const hkMatrix6f&a, const hkMatrix6f&b ) { hkMatrix6fSetMul(out, a, b);  }
		HK_FORCE_INLINE void HK_CALL hkMatrix6SetMulV(hkVector8f& out, const hkMatrix6f&a, const hkVector8f& b) { hkMatrix6fSetMulV(out, a, b);  }
		HK_FORCE_INLINE void HK_CALL hkMatrix6SetTranspose(hkMatrix6f& out, const hkMatrix6f&in ) { hkMatrix6fSetTranspose(out, in);  }
		HK_FORCE_INLINE void HK_CALL hkMatrix6SetInvert(hkMatrix6f& out, const hkMatrix6f& in ) { hkMatrix6fSetInvert(out, in);  }
	}
# endif


# if defined(HK_REAL_IS_DOUBLE)
#	define HK_REAL_PI HK_DOUBLE_PI
#	define HK_REAL_DEG_TO_RAD HK_DOUBLE_DEG_TO_RAD
#	define HK_REAL_RAD_TO_DEG HK_DOUBLE_RAD_TO_DEG	
#	define HK_REAL_EPSILON HK_DOUBLE_EPSILON
#	define HK_REAL_MIN HK_DOUBLE_MIN
#	define HK_REAL_MAX HK_DOUBLE_MAX			
#	define HK_REAL_HIGH HK_DOUBLE_HIGH
# else
#	define HK_REAL_PI HK_FLOAT_PI			
#	define HK_REAL_DEG_TO_RAD HK_FLOAT_DEG_TO_RAD
#	define HK_REAL_RAD_TO_DEG HK_FLOAT_RAD_TO_DEG
#	define HK_REAL_EPSILON HK_FLOAT_EPSILON	
#	define HK_REAL_MIN HK_FLOAT_MIN
#	define HK_REAL_MAX HK_FLOAT_MAX
#	define HK_REAL_HIGH HK_FLOAT_HIGH
# endif

# ifndef HK_MASK_TO_VECTOR
#	define HK_MASK_TO_VECTOR(x) (hkQuadReal)x
# endif

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
