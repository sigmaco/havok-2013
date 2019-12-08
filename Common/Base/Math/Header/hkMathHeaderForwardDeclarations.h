/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

class hkVector4f;
class hkVector4d;
class hkVector4fComparison;
class hkVector4dComparison;
class hkSimdFloat32;
class hkSimdDouble64;
class hkQuaternionf;
class hkQuaterniond;
class hkMatrix3f;
class hkMatrix3d;
class hkMatrix4f;
class hkMatrix4d;
class hkRotationf;
class hkRotationd;
class hkTransformf;
class hkTransformd;
class hkQTransformf;
class hkQTransformd;
class hkQsTransformf;
class hkQsTransformd;
template <typename FT> class hkSymmetricMatrix3Impl;
typedef hkSymmetricMatrix3Impl<hkFloat32>  hkSymmetricMatrix3f;
typedef hkSymmetricMatrix3Impl<hkDouble64> hkSymmetricMatrix3d;


// Type discriminator for floating point resolution
template <typename POD>
struct hkRealTypes
{};

// Specialization for single precision
template <>
struct hkRealTypes<hkFloat32>
{
	typedef hkVector4f						Vector;
	typedef hkVector4fParameter				VectorParameter;
	typedef hkQuaternionf					Quaternion;
	typedef hkQuaternionfParameter			QuaternionParameter;
	typedef hkSimdFloat32					Scalar;
	typedef hkSimdFloat32Parameter			ScalarParameter;
	typedef hkVector4fComparison			Comparison;
	typedef hkVector4fComparisonParameter	ComparisonParameter;
	typedef hkFloat32						Pod;
	typedef hkMatrix3f						Matrix3;
	typedef hkSymmetricMatrix3f				SymmetricMatrix3;
	typedef hkMatrix4f						Matrix4;
	typedef hkRotationf						Rotation;
	typedef hkTransformf					Transform;
	typedef hkQTransformf					QTransform;
	typedef hkQsTransformf					QsTransform;
};

// Specialization for double precision
template <>
struct hkRealTypes<hkDouble64>
{
	typedef hkVector4d						Vector;
	typedef hkVector4dParameter				VectorParameter;
	typedef hkQuaterniond					Quaternion;
	typedef hkQuaterniondParameter			QuaternionParameter;
	typedef hkSimdDouble64					Scalar;
	typedef hkSimdDouble64Parameter			ScalarParameter;
	typedef hkVector4dComparison			Comparison;
	typedef hkVector4dComparisonParameter	ComparisonParameter;
	typedef hkDouble64						Pod;
	typedef hkMatrix3d						Matrix3;
	typedef hkSymmetricMatrix3d				SymmetricMatrix3;
	typedef hkMatrix4d						Matrix4;
	typedef hkRotationd						Rotation;
	typedef hkTransformd					Transform;
	typedef hkQTransformd					QTransform;
	typedef hkQsTransformd					QsTransform;
};

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
