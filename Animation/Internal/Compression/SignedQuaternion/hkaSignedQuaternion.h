/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

class hkaSignedQuaternion
{
public:
	// Signed quaternion packing/unpacking/endian
	static void HK_CALL packSignedQuaternion16( const hkQuaternion* in, hkUint8* out );
	static void HK_CALL packSignedQuaternion24( const hkQuaternion* in, hkUint8* out );
	static void HK_CALL packSignedQuaternion32( const hkQuaternion* in, hkUint8* out8 );
	static void HK_CALL packSignedQuaternion40( const hkQuaternion* in, hkUint8* out );
	static void HK_CALL packSignedQuaternion48( const hkQuaternion* in, hkUint8* out8 );
	static void HK_CALL packSignedQuaternion128( const hkQuaternion* in, hkUint8* out8 );
	static void HK_CALL unpackSignedQuaternion16( const hkUint8* in, hkQuaternion* out );
	static void HK_CALL unpackSignedQuaternion24( const hkUint8* in, hkQuaternion* out );
	static void HK_CALL unpackSignedQuaternion32( const hkUint8* in8, hkQuaternion* out );
	static void HK_CALL unpackSignedQuaternion40( const hkUint8* in, hkQuaternion* out );
	static void HK_CALL unpackSignedQuaternion48( const hkUint8* in8, hkQuaternion* out );
	static void HK_CALL unpackSignedQuaternion128( const hkUint8* in8, hkQuaternion* out );
	static void HK_CALL handleEndianSignedQuaternion24( hkUint8* dataInOut );
	static void HK_CALL handleEndianSignedQuaternion16( hkUint8* dataInOut );
	static void HK_CALL handleEndianSignedQuaternion32( hkUint8* dataInOut );
	static void HK_CALL handleEndianSignedQuaternion40( hkUint8* dataInOut );
	static void HK_CALL handleEndianSignedQuaternion48( hkUint8* dataInOut );
	static void HK_CALL handleEndianSignedQuaternion128( hkUint8* dataInOut );
	static hkReal HK_CALL getApproximateAccuracySignedQuaternion16();
	static hkReal HK_CALL getApproximateAccuracySignedQuaternion24();
	static hkReal HK_CALL getApproximateAccuracySignedQuaternion32();
	static hkReal HK_CALL getApproximateAccuracySignedQuaternion40();
	static hkReal HK_CALL getApproximateAccuracySignedQuaternion48();
	static hkReal HK_CALL getApproximateAccuracySignedQuaternion128();
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
