/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_LEGACY_SHAPE_TYPE_H
#define HKP_LEGACY_SHAPE_TYPE_H

#include <Physics2012/Collide/Shape/hkpShapeType.h>

// A mapping of pre-2011.3 shape types (e.g. HK_SHAPE_LIST)
// to current shape types (e.g. hkcdShapeType::LIST).
// Warning: This exists only to help users who are migrating from pre-2011.3 versions.
// It will be removed in future versions.
#define HK_SHAPE_INVALID				( hkcdShapeType::INVALID )
#define HK_SHAPE_SPHERE					( hkcdShapeType::SPHERE )
#define HK_SHAPE_CYLINDER				( hkcdShapeType::CYLINDER )
#define HK_SHAPE_TRIANGLE				( hkcdShapeType::TRIANGLE )
#define HK_SHAPE_BOX					( hkcdShapeType::BOX )
#define HK_SHAPE_CAPSULE				( hkcdShapeType::CAPSULE )
#define HK_SHAPE_CONVEX_VERTICES		( hkcdShapeType::CONVEX_VERTICES )
#define HK_SHAPE_COLLECTION				( hkcdShapeType::COLLECTION )
#define HK_SHAPE_BV_TREE				( hkcdShapeType::BV_TREE )
#define HK_SHAPE_LIST					( hkcdShapeType::LIST )
#define HK_SHAPE_MOPP					( hkcdShapeType::MOPP )
#define HK_SHAPE_CONVEX_TRANSLATE		( hkcdShapeType::CONVEX_TRANSLATE )
#define HK_SHAPE_CONVEX_TRANSFORM		( hkcdShapeType::CONVEX_TRANSFORM )
#define HK_SHAPE_SAMPLED_HEIGHT_FIELD	( hkcdShapeType::SAMPLED_HEIGHT_FIELD )
#define HK_SHAPE_EXTENDED_MESH			( hkcdShapeType::EXTENDED_MESH )
#define HK_SHAPE_TRANSFORM				( hkcdShapeType::TRANSFORM )
#define HK_SHAPE_COMPRESSED_MESH		( hkcdShapeType::COMPRESSED_MESH )
#define HK_SHAPE_STATIC_COMPOUND		( hkcdShapeType::STATIC_COMPOUND )
#define HK_SHAPE_BV_COMPRESSED_MESH		( hkcdShapeType::BV_COMPRESSED_MESH )
#define HK_SHAPE_CONVEX					( hkcdShapeType::CONVEX )
#define HK_SHAPE_CONVEX_PIECE			( hkcdShapeType::CONVEX_PIECE )
#define HK_SHAPE_MULTI_SPHERE			( hkcdShapeType::MULTI_SPHERE )
#define HK_SHAPE_CONVEX_LIST			( hkcdShapeType::CONVEX_LIST )
#define HK_SHAPE_TRIANGLE_COLLECTION	( hkcdShapeType::TRIANGLE_COLLECTION )
#define HK_SHAPE_HEIGHT_FIELD			( hkcdShapeType::HEIGHT_FIELD )
#define HK_SHAPE_SPHERE_REP				( hkcdShapeType::SPHERE_REP )
#define HK_SHAPE_BV						( hkcdShapeType::BV )
#define HK_SHAPE_PLANE					( hkcdShapeType::PLANE )
#define HK_SHAPE_PHANTOM_CALLBACK		( hkcdShapeType::PHANTOM_CALLBACK )
#define HK_SHAPE_MULTI_RAY				( hkcdShapeType::MULTI_RAY )
#define HK_SHAPE_USER0					( hkcdShapeType::USER0 )
#define HK_SHAPE_USER1					( hkcdShapeType::USER1 )
#define HK_SHAPE_USER2					( hkcdShapeType::USER2 )

#endif // HKP_LEGACY_SHAPE_TYPE_H

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
