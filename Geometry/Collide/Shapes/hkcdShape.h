/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKCD_SHAPE_BASE_H
#define HKCD_SHAPE_BASE_H

#include <Common/Base/Types/Geometry/Sphere/hkSphere.h>
#include <Geometry/Internal/Types/hkcdVertex.h>


	/// Shape types
struct hkcdShapeType
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_GEOMETRY, hkcdShapeType );
	HK_DECLARE_REFLECTION();

	enum ShapeTypeEnum
	{
		//
		//	SPU supported shapes
		//

		SPHERE								= 0,	///< hkpSphereShape type.
		CYLINDER							= 1,	///< hkpCylinderShape type. 
		TRIANGLE							= 2,	///< hkpTriangleShape type.
		BOX									= 3,	///< hkpBoxShape type.
		CAPSULE								= 4,	///< hkpCapsuleShape type.
		CONVEX_VERTICES						= 5,	///< hkpConvexVerticesShape type.
		TRI_SAMPLED_HEIGHT_FIELD_COLLECTION	= 6,	///< hkpTriSampledHeightFieldCollection type.	
		TRI_SAMPLED_HEIGHT_FIELD_BV_TREE	= 7,	///< hkpTriSampledHeightFieldBvTreeShape type.
		LIST								= 8,	///< hkpListShape type.
		MOPP								= 9,	///< hkpMoppBvTreeShape type.
		CONVEX_TRANSLATE					= 10,	///< hkpConvexTranslateShape type.
		CONVEX_TRANSFORM					= 11,	///< hkpConvexTransformShape type.
		SAMPLED_HEIGHT_FIELD				= 12,	///< hkpSampledHeightFieldShape type.
		EXTENDED_MESH						= 13,	///< hkpExtendedMeshShape type.
		TRANSFORM							= 14,	///< hkpTransformShape type.
		COMPRESSED_MESH						= 15,	///< hkpCompressedMeshShape type.
		STATIC_COMPOUND						= 16,	///< hkpStaticCompoundShape type.
		BV_COMPRESSED_MESH					= 17,	///< hkpBvCompressedMeshShape type.
		COLLECTION							= 18,	///< All shapes which inherit from hkpShapeCollection have this as an alternate type.	
		USER0								= 19,	///< Custom user type.
		USER1								= 20,	///< Custom user type.
		USER2								= 21,	///< Custom user type.

		//
		//	Non-SPU supported shapes
		//

		BV_TREE								= 22,	///< All shapes which inherit from hkpBvTreeShape have this as an alternate type.
		CONVEX								= 23,	///< All shapes which inherit from hkpConvexShape have this as an alternate type.
		CONVEX_PIECE						= 24,	///< DEPRECATED - hkpConvexPieceShape type.
		MULTI_SPHERE						= 25,	///< DEPRECATED - hkpMultiSphereShape type.
		CONVEX_LIST							= 26,	///< DEPRECATED - hkpConvexListShape.
		TRIANGLE_COLLECTION					= 27,	///< A shape collection which only returns triangles as child shapes, e.g., hkpMeshShape.
		HEIGHT_FIELD						= 28,	///< hkpHeightFieldShape type.
		SPHERE_REP							= 29,	///< hkpSphereRepShape type.
		BV									= 30,	///< hkpBvShape type.
		PLANE								= 31,	///< hkpPlaneShape type.
		PHANTOM_CALLBACK					= 32,	///< hkpPhantomCallbackShape type.
		MULTI_RAY							= 33,	///< hkpMultiRayShape type.
		INVALID								= 34,	///< Invalid shape

		FIRST_SHAPE_TYPE					= SPHERE,			///< The first real shape.
		MAX_SPU_SHAPE_TYPE					= USER2 + 1,		///< Last SPU support shape type.
		MAX_PPU_SHAPE_TYPE					= INVALID + 1,		///< The end of the shape type list.
		ALL_SHAPE_TYPES						= -1,				///< All shapes flag, used by the hkpCollisionDispatcher.
	};
};

	/// Shape dispatch types
struct hkcdShapeDispatchType
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_GEOMETRY, hkcdShapeDispatchType );
	HK_DECLARE_REFLECTION();

	enum ShapeDispatchTypeEnum
	{
		CONVEX_IMPLICIT,	///< A convex object which has no faces, only a single contact point will be generated.
		CONVEX,
		HEIGHT_FIELD,
		COMPOSITE,
		USER, 
		NUM_DISPATCH_TYPES,
	};
};

	/// Shape info codec types
struct hkcdShapeInfoCodecType
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_GEOMETRY, hkcdShapeInfoCodecType );
	HK_DECLARE_REFLECTION();

		/// Reserved types for the default Shape Info Codecs.
	enum ShapeInfoCodecTypeEnum
	{
		NULL_CODEC		=  0,	///< Default codec. Will not decode anything but will issue a warning if called with shapeInfo values != 0.
		UFM358			=  1,	///< User data: 3bit, Collision Filter Info: 5bit, Material Id: 8bit.
		MAX_NUM_CODECS	= 16	///< Maximum number of codecs that can be registered.
	};
};

	/// Base class for all Havok shapes
class hkcdShape : public hkReferencedObject
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_GEOMETRY );
		HK_DECLARE_REFLECTION();

		typedef hkcdShapeType::ShapeTypeEnum						ShapeType;
		typedef hkcdShapeDispatchType::ShapeDispatchTypeEnum		DispatchType;
		typedef hkcdShapeInfoCodecType::ShapeInfoCodecTypeEnum		ShapeInfoCodecType;

	public:

			/// Constructor
		HK_FORCE_INLINE hkcdShape( ShapeType shapeType )
		:	hkReferencedObject()
		,	m_type( shapeType )
		,	m_dispatchType( hkcdShapeDispatchType::USER )
		,	m_bitsPerKey(0)
		,	m_shapeInfoCodecType( hkcdShapeInfoCodecType::NULL_CODEC )
		{}
		
			/// Empty constructor, leaves everything uninitialized, as it will only be called on SPU from the shape vtable util
		HK_FORCE_INLINE hkcdShape() {}


			/// Serialization constructor
		hkcdShape( class hkFinishLoadedObjectFlag flag );


	public:

			/// Get the shape type
		HK_FORCE_INLINE ShapeType getType() const;

			/// Set the shape type
			
		HK_FORCE_INLINE void setType( ShapeType newType );

	public:

			/// Shape type
		hkEnum<ShapeType, hkUint8> m_type;	// +nosave

		hkEnum<DispatchType, hkUint8> m_dispatchType;

			/// Number of bits required to store a shape key local to this shape.
			/// This do NOT include bits used by children shapes if any, so that to mask out a key for this shape, one can use the following:
			/// key & ((1 << m_bitsPerKey) - 1) = Masked key.
		hkUint8 m_bitsPerKey;

			// The codec to be used for decoding the Shape Info of any child shapes.
		hkEnum<ShapeInfoCodecType, hkUint8> m_shapeInfoCodecType;
};

// Helper macros
#define HKCD_DECLARE_SHAPE_TYPE(shapeType)		enum { THIS_SHAPE_TYPE = shapeType }
#define HKCD_SHAPE_TYPE_FROM_CLASS(ShapeClass)	(hkcdShape::ShapeType)ShapeClass::THIS_SHAPE_TYPE

#include <Geometry/Collide/Shapes/hkcdShape.inl>

#endif	// HKCD_SHAPE_BASE_H

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
