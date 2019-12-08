/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_SHAPE_TYPES_H
#define HKP_SHAPE_TYPES_H

#include <Geometry/Collide/Shapes/hkcdShape.h>

	/// Use the hkcd shape type.
typedef hkcdShape::ShapeType hkpShapeType;
	/// A utility function to return a useful name for a given shape type
const char* HK_CALL hkGetShapeTypeName( hkpShapeType type );

	/// Register all Havok specific shape types.
	/// This needs to be called at setup time to tell the dispatcher which
	/// shapes inherit from other shapes.
void HK_CALL hkpRegisterAlternateShapeTypes( class hkpCollisionDispatcher* dis );


#endif // HKP_SHAPE_TYPES_H

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
