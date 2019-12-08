/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_BASE_COMPRESSED_INERTIA_TENSOR_H
#define HK_BASE_COMPRESSED_INERTIA_TENSOR_H

#include <Common/Base/Math/Vector/hkPackedVector3.h>

struct hkMassProperties;

	//#define HK_CHECK_PADDING	// only enable on visual studio compiler
#if defined(HK_CHECK_PADDING)
#	pragma warning( 3 : 4820 )
#endif


/// 
struct hkDiagonalizedMassProperties
{
	void pack( const hkMassProperties& mp );

	void unpack( hkMassProperties* massPropertiesOut ) const;

	/// The volume.
	hkReal	m_volume;

	/// The mass.
	hkReal	m_mass;

#if defined(HK_REAL_IS_DOUBLE)
	hkUint8 m_padding[16]; //+nosave
#else
	hkUint8 m_padding[8]; //+nosave
#endif

	/// The center of mass.
	hkVector4 m_centerOfMass;

	/// The inertia tensor.
	hkVector4 m_inertiaTensor;

	/// The rotation rotating from inertia major axis space to world space
	hkQuaternion m_majorAxisSpace;
};


/// Packed inertia, 15 bit accuracy, 32 bytes (hkMassProperties is 96 bytes)
HK_CLASSALIGN(struct,8) hkCompressedMassProperties
{
	HK_DECLARE_REFLECTION();
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_PHYSICS, hkCompressedMassProperties );

	/// pack
	void pack( const hkMassProperties& massPropertiesIn );
	void pack( const hkDiagonalizedMassProperties& massPropertiesIn );

	/// unpack
	void unpack( hkMassProperties& massPropertiesOut ) const;

	void unpack( hkDiagonalizedMassProperties* massPropertiesOut ) const;

	HK_ALIGN(hkPackedVector3,8)			m_centerOfMass;	 //+overridetype(hkInt16[4])
	HK_ALIGN(hkPackedVector3,8)			m_inertia;		 //+overridetype(hkInt16[4])
	HK_ALIGN(hkPackedUnitVector<4>,8)	m_majorAxisSpace;//+overridetype(hkInt16[4])
	hkReal m_mass;
	hkReal m_volume;
};

#if defined(HK_CHECK_PADDING)
#	pragma warning( disable : 4820 )
#endif

#endif // HK_BASE_COMPRESSED_INERTIA_TENSOR_H

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
