/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

# if defined(HK_REAL_IS_DOUBLE)
	typedef hkDouble64 hkReal;
	typedef hkQuadDouble64 hkQuadReal;
	typedef hkSingleDouble64 hkSingleReal;

	typedef hkQuadDouble64Union hkQuadRealUnion;

	typedef hkVector4d hkVector4;
	typedef hkVector4dParameter hkVector4Parameter;
	typedef hkVector4dComparison hkVector4Comparison;
	typedef hkVector4dComparisonParameter hkVector4ComparisonParameter;
	typedef hkSimdDouble64 hkSimdReal;
	typedef hkSimdDouble64Parameter hkSimdRealParameter;
	typedef hkQuaterniond hkQuaternion;
	typedef hkQuaterniondParameter hkQuaternionParameter;
	typedef hkMatrix3d hkMatrix3;
	typedef hkMatrix4d hkMatrix4;
	typedef hkRotationd hkRotation;
	typedef hkTransformd hkTransform;
	typedef hkQTransformd hkQTransform;
	typedef hkQsTransformd hkQsTransform;
	typedef hkSymmetricMatrix3d hkSymmetricMatrix3;
	#define g_vectorConstants g_vectordConstants
	#define HK_QUADREAL_CONSTANT HK_QUADDOUBLE_CONSTANT
# else
	typedef hkFloat32 hkReal;
	typedef hkQuadFloat32 hkQuadReal;
	typedef hkSingleFloat32 hkSingleReal;

	typedef hkQuadFloat32Union hkQuadRealUnion;

	typedef hkVector4f hkVector4;
	typedef hkVector4fParameter hkVector4Parameter;
	typedef hkVector4fComparison hkVector4Comparison;
	typedef hkVector4fComparisonParameter hkVector4ComparisonParameter;
	typedef hkSimdFloat32 hkSimdReal;
	typedef hkSimdFloat32Parameter hkSimdRealParameter; 
	typedef hkQuaternionf hkQuaternion;
	typedef hkQuaternionfParameter hkQuaternionParameter;
	typedef hkMatrix3f hkMatrix3;
	typedef hkMatrix4f hkMatrix4;
	typedef hkRotationf hkRotation;
	typedef hkTransformf hkTransform;
	typedef hkQTransformf hkQTransform;
	typedef hkQsTransformf hkQsTransform;
	typedef hkSymmetricMatrix3f hkSymmetricMatrix3;
	#define g_vectorConstants g_vectorfConstants
	#define HK_QUADREAL_CONSTANT HK_QUADFLOAT_CONSTANT
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
