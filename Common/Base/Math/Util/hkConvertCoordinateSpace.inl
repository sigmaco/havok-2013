/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#include <Common/Base/Algorithm/Sort/hkSort.h>

template <typename FT>
hkConvertCSImpl<FT>::hkConvertCSImpl(ConversionType type)
{
	setConversionType(type);
}

template <typename FT>
void hkConvertCSImpl<FT>::setConversionType (ConversionType type)
{
	typename hkRealTypes<FT>::Rotation rotation;
	typename hkRealTypes<FT>::Vector c0 = hkRealTypes<FT>::Vector::template getConstant<HK_QUADREAL_1000>();
	typename hkRealTypes<FT>::Vector c1 = hkRealTypes<FT>::Vector::template getConstant<HK_QUADREAL_0100>();
	typename hkRealTypes<FT>::Vector c2 = hkRealTypes<FT>::Vector::template getConstant<HK_QUADREAL_0010>();

	switch (type)
	{
	case CT_IDENTITY:
		{
			// Do nothing
			break;
		}
	case CT_FLIP_X:
		{
			c0.template setNeg<4>(c0);
			break;
		}
	case CT_FLIP_Y:
		{
			c1.template setNeg<4>(c1);
			break;
		}
	case CT_FLIP_Z:
		{
			c2.template setNeg<4>(c2);
			break;
		}
	case CT_SWITCH_YZ:
		{
			c1 = c2;
			c2 = hkRealTypes<FT>::Vector::template getConstant<HK_QUADREAL_0100>();
			break;
		}
	default:
		HK_ASSERT2(0x74224073, 0, "Unknown Coordinate System Conversion Type");
		return;
	}	
	rotation.setCols(c0,c1,c2);

	setConversionRotation(rotation);
}

template <typename FT>
void hkConvertCSImpl<FT>::setConversionRotation (const typename hkRealTypes<FT>::Rotation& rotation)
{
	m_conversionRotation = rotation;

	// We calculate the determinant
	typename hkRealTypes<FT>::Vector r0;
	r0.setCross(rotation.template getColumn<1>(), rotation.template getColumn<2>());
	const typename hkRealTypes<FT>::Scalar determinant = rotation.template getColumn<0>().template dot<3>(r0);

	HK_ASSERT2(0x2e6d8741, hkMath::fabs(hkMath::fabs(determinant.getReal()) -1) < typename hkRealTypes<FT>::Pod(1e-2f), "Matrix (rotation) for conversion has scale!");

	// If determinant is (close to) -1, we are doing a handedness conversion
	typename hkRealTypes<FT>::Scalar absDet; 
	absDet.setAbs(determinant + hkRealTypes<FT>::Scalar::template getConstant<HK_QUADREAL_1>());
	m_flippingC = absDet.less( hkRealTypes<FT>::Scalar::fromFloat(typename hkRealTypes<FT>::Pod(1e-2f)) );
	m_flipping  = m_flippingC.anyIsSet();
}

template <typename FT>
void hkConvertCSImpl<FT>::convertVector (typename hkRealTypes<FT>::Vector& vectorInOut) const
{
	vectorInOut._setRotatedDir(m_conversionRotation, vectorInOut);
}

template <typename FT>
void hkConvertCSImpl<FT>::convertQuaternion (typename hkRealTypes<FT>::Quaternion& quaternionInOut) const
{
	// First we transform the axis of rotation
	typename hkRealTypes<FT>::Vector imag;
	imag._setRotatedDir(m_conversionRotation, quaternionInOut.getImag());

	// Second, if the transformation is a "flipping" one (one that changes handedness) we also flip the sign
	typename hkRealTypes<FT>::Scalar realPart;
	realPart.setFlipSign(quaternionInOut.getRealPart(), m_flippingC);

	quaternionInOut.m_vec.setXYZ_W(imag,realPart);
}

template <typename FT>
void hkConvertCSImpl<FT>::convertRotation (typename hkRealTypes<FT>::Rotation& rotationInOut) const
{
	rotationInOut.changeBasis(m_conversionRotation);
}

template <typename FT>
void hkConvertCSImpl<FT>::convertTransform (typename hkRealTypes<FT>::Transform& transformInOut) const
{
	convertRotation(transformInOut.getRotation());

	typename hkRealTypes<FT>::Vector t = transformInOut.getTranslation();
	convertVector(t);
	transformInOut.setTranslation(t);
}

template <typename FT>
void hkConvertCSImpl<FT>::convertQTransform (typename hkRealTypes<FT>::QTransform& transformInOut) const
{
	typename hkRealTypes<FT>::Quaternion r = transformInOut.getRotation();
	convertQuaternion(r);
	transformInOut.setRotation(r);

	typename hkRealTypes<FT>::Vector t = transformInOut.getTranslation();
	convertVector(t);
	transformInOut.setTranslation(t);
}

template <typename FT>
void hkConvertCSImpl<FT>::convertQsTransform (typename hkRealTypes<FT>::QsTransform& transformInOut) const
{
	typename hkRealTypes<FT>::Quaternion r = transformInOut.getRotation();
	convertQuaternion(r);
	transformInOut.setRotation(r);

	typename hkRealTypes<FT>::Vector t = transformInOut.getTranslation();
	convertVector(t);
	transformInOut.setTranslation(t);

	// no need to change the scale
}


template <typename FT>
void hkConvertCSImpl<FT>::convertRotationAngle (typename hkRealTypes<FT>::Pod& angle) const
{
	if (m_flipping)
	{
		angle = -angle;
	}
}

template <typename FT>
void hkConvertCSImpl<FT>::convertMinMaxAngles (typename hkRealTypes<FT>::Pod& minAngle, typename hkRealTypes<FT>::Pod& maxAngle) const
{
	convertRotationAngle(minAngle);
	convertRotationAngle(maxAngle);
	if (minAngle>maxAngle)
	{
		hkAlgorithm::swap(minAngle, maxAngle);
	}
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
