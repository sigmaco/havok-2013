/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_GEOMETRY_CONVERTER_H
#define HKP_GEOMETRY_CONVERTER_H

class hkpWorld;
class hkpRigidBody;
struct hkGeometry;

/// This utility class provides a set of methods useful for creating an hkGeometry from an existing physics integration
class hkpGeometryConverter
{
	public:

			/// Creates a geometry from a Havok physics world
		static void HK_CALL createSingleGeometryFromWorld( const hkpWorld& world, hkGeometry& geomOut,
			hkBool useFixedBodiesOnly = true, hkBool getMaterialFromUserData = true);

			/// Creates a geometry from a single rigid body
		static void HK_CALL appendGeometryFromRigidBody( const hkpRigidBody& body, hkGeometry& geomOut,
			hkBool getMaterialFromUserData = true);

};

#endif	// HKP_GEOMETRY_CONVERTER_H

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
