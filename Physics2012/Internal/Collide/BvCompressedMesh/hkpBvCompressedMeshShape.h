/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_BV_COMPRESSED_MESH_SHAPE_H
#define HKP_BV_COMPRESSED_MESH_SHAPE_H

//HK_HAVOK_ASSEMBLY_EXCLUDE_FILE

#include <Physics2012/Collide/Shape/Compound/Tree/hkpBvTreeShape.h>
#include <Physics2012/Collide/Util/Welding/hkpWeldingUtility.h>

class hkpBvCompressedMeshShapeCinfo;
struct hkGeometry;

extern const class hkClass hkpBvCompressedMeshShapeTreeClass;


	/// A shape representing a compressed triangulated geometry and/or compressed convex shapes, stored
	/// in a bounding volume. It is not necessary to wrap this shape in any other bounding volume shapes.
	///
	/// This shape allows for per-primitive (triangle or convex shape) user data and collision filter information,
	/// and instrumented welding information for triangles. This per-primitive data must be provided during
	/// construction and cannot be changed later. Note that there is a limit of 256 distinct values for both
	/// user data and filter info.
	///
	/// A construction info structure provides a set of virtual functions which must be overridden to provide
	/// the input primitive geometries and their per-primitive data. Welding information will be computed during
	/// construction if a welding type is specified in the construction info, but note that this computation
	/// can take some time so this shape should not be constructed at runtime if possible.
	///
	/// All convex shapes are returned as a hkpConvexVerticesShape from getChildShape(), other than triangles
	/// and cylinders which use their corresponding shape types.
class hkpBvCompressedMeshShape : public hkpBvTreeShape, public hkpShapeContainer
{
	// +version(2)
	public:

			/// Indicates how per primitive collision filter info or user data should be stored.
		enum PerPrimitiveDataMode
		{
			PER_PRIMITIVE_DATA_NONE,			///< No per primitive data.
			PER_PRIMITIVE_DATA_8_BIT,			///< Data is stored with the primitive, using up to 8 bits.
			PER_PRIMITIVE_DATA_PALETTE,			///< Data is stored in a 32 bit palette, indexed using the 8 bit data.
			PER_PRIMITIVE_DATA_STRING_PALETTE	///< Data is stored in a string palette, indexed using the 8 bit data.
		};

			/// Primitive convex shape types.
		enum PrimitiveType
		{
			PRIMITIVE_TYPE_BOX,
			PRIMITIVE_TYPE_HULL,
			PRIMITIVE_TYPE_SPHERE,
			PRIMITIVE_TYPE_CAPSULE,
			PRIMITIVE_TYPE_CYLINDER,
		};

			/// Compile-time configuration.
		enum Config
		{
			
			#if HK_POINTER_SIZE == 8
				#ifdef HK_REAL_IS_DOUBLE
					NUM_BYTES_FOR_TREE = 224,
				#else
					NUM_BYTES_FOR_TREE = 160,
				#endif
			#else
				#ifdef HK_REAL_IS_DOUBLE
						NUM_BYTES_FOR_TREE = 224,
				#else
					NUM_BYTES_FOR_TREE = 144,
				#endif
			#endif

			
				MAX_NUM_VERTICES_PER_HULL = 255,

			
			MAX_NUM_PRIMITIVES = 1 << 23
		};

	public:

		HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_SHAPE );
		HK_DECLARE_REFLECTION();
		HKCD_DECLARE_SHAPE_TYPE( hkcdShapeType::BV_COMPRESSED_MESH );

			/// Constructor
		hkpBvCompressedMeshShape( const hkpBvCompressedMeshShapeCinfo& cInfo );

			/// Empty constructor, only to be called by the shape vtable utility on SPU
		HK_FORCE_INLINE hkpBvCompressedMeshShape() {}


			/// Finishing constructor
		hkpBvCompressedMeshShape( hkFinishLoadedObjectFlag flag );


			/// Destructor
		virtual ~hkpBvCompressedMeshShape();

			/// Get the convex radius which will be applied to each primitive unless they provide their own.
			/// This value was passed in during construction.
		HK_FORCE_INLINE hkReal getConvexRadius() const;

			/// Returns the relevant primitive's user data, or zero if there is no user data stored.
		hkUint32 getPrimitiveUserData( hkpShapeKey key ) const;

			/// Returns the relevant primitive's user string, or HK_NULL if there is no user string stored.
		hkStringPtr getPrimitiveUserString( hkpShapeKey key ) const;

			/// Returns the storage mode for per primitive collision filter info.
		HK_FORCE_INLINE PerPrimitiveDataMode getCollisionFilterInfoMode() const;

			/// Returns the storage mode for per primitive user data.
		HK_FORCE_INLINE PerPrimitiveDataMode getUserDataMode() const;

			/// Read write access to the collision filter info palette that is indexed with a primitive's 8-bit
			/// collision filter value when the collision filter mode is PER_PRIMITIVE_DATA_PALETTE.
		HK_FORCE_INLINE hkArray<hkUint32>& accessCollisionFilterInfoPalette();

			/// Read write access to the user data palette that is indexed with a primitive's 8-bit
			/// user data value when the user data mode is PER_PRIMITIVE_DATA_PALETTE.
		HK_FORCE_INLINE hkArray<hkUint32>& accessUserDataPalette();

			/// Read write access to the user string palette that is indexed with a primitive's 8-bit
			/// user data value when the user data mode is PER_PRIMITIVE_DATA_STRING_PALETTE.
		HK_FORCE_INLINE hkArray<hkStringPtr>& accessUserStringPalette();

			/// Decompress the mesh into a geometry object (for visualization).
			/// Note: This stores primitives raw data in the m_material member of each triangles for debugging purposes.
		void convertToGeometry( hkGeometry& geometryOut, const hkArray<hkpShapeKey>* inclKeys = HK_NULL, const hkArray<hkpShapeKey>* exclKeys = HK_NULL ) const;

		//
		// hkpShape interface
		//


		virtual const hkpShapeContainer* getContainer() const { return this; }

		virtual int calcSizeForSpu( const CalcSizeForSpuInput& input, int spuBufferSizeLeft ) const;


		virtual void getAabb( const hkTransform& localToWorld, hkReal tolerance, hkAabb& out ) const;

		virtual hkBool castRay( const hkpShapeRayCastInput& input, hkpShapeRayCastOutput& results ) const;

		virtual void castRayWithCollector( const hkpShapeRayCastInput& input, const hkpCdBody& body, hkpRayHitCollector& collector ) const;

		//
		// hkpBvTreeShape interface
		//

		virtual void queryAabb( const hkAabb& aabb, hkArray<hkpShapeKey>& hits ) const;

		HKP_SHAPE_VIRTUAL hkUint32 queryAabbImpl( HKP_SHAPE_VIRTUAL_THIS const hkAabb& aabb, hkpShapeKey* hits, int maxNumKeys ) HKP_SHAPE_VIRTUAL_CONST;

		HKP_SHAPE_VIRTUAL void castAabbImpl( HKP_SHAPE_VIRTUAL_THIS const hkAabb& from, hkVector4Parameter to, hkpAabbCastCollector& collector ) HKP_SHAPE_VIRTUAL_CONST;

		//
		// hkpShapeContainer interface
		//

		virtual int getNumChildShapes() const;

		virtual hkpShapeKey getFirstKey() const;

		virtual hkpShapeKey getNextKey( hkpShapeKey oldKey ) const;

		virtual const hkpShape* getChildShape( hkpShapeKey key, hkpShapeBuffer& buffer ) const;

		virtual hkUint32 getCollisionFilterInfo( hkpShapeKey key ) const;

	protected:

			/// Default convex radius to apply to each primitive, unless they provide their own.
		hkReal m_convexRadius;

			/// Welding type applied to each triangle.
		hkEnum<hkpWeldingUtility::WeldingType, hkUint8> m_weldingType; //+default(hkpWeldingUtility::WELDING_TYPE_NONE)

			/// Indicates if the shape has per primitive collision filter info. If this is false all primitives will have
			/// the default collision filter info value (0).
		hkBool m_hasPerPrimitiveCollisionFilterInfo;

			/// Indicates if the shape has per primitive user data. If this is false all primitives will have
			/// the default user data value (0).
		hkBool m_hasPerPrimitiveUserData;

			/// Collision filter info palette, indexed using the collision filter index stored with each primitive.
		hkArray<hkUint32> m_collisionFilterInfoPalette;

			/// User data palette, indexed using the user data index stored with each primitive.
		hkArray<hkUint32> m_userDataPalette;

			/// User string palette, indexed using the user data index stored with each primitive.
		hkArray<hkStringPtr> m_userStringPalette;

			/// The internal static mesh tree.
		HK_ALIGN_REAL( hkUint8 m_tree[NUM_BYTES_FOR_TREE] ); //+overridetype(class hkpBvCompressedMeshShapeTree)

		friend struct hkpBvCompressedMeshShape_Internals;

	public:

			/// Global pool(s) to temporarily store decompressed vertices of convex shapes
		HK_ALIGN_REAL( static hkVector4 g_vertexBufferPool[HK_MAX_NUM_THREADS][MAX_NUM_VERTICES_PER_HULL]);
};

#include <Physics2012/Internal/Collide/BvCompressedMesh/hkpBvCompressedMeshShape.inl>

#endif	// HKP_BV_COMPRESSED_MESH_SHAPE_H

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
