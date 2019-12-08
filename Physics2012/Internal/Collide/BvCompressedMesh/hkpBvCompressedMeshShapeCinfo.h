/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_BV_COMPRESSED_MESH_SHAPE_CINFO_H
#define HKP_BV_COMPRESSED_MESH_SHAPE_CINFO_H

#include <Physics2012/Internal/Collide/BvCompressedMesh/hkpBvCompressedMeshShape.h>

class hkpConvexShape;
struct hkGeometry;


	/// Interface used to construct a hkpBvCompressedMeshShape
class hkpBvCompressedMeshShapeCinfo
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_SHAPE, hkpBvCompressedMeshShapeCinfo );
		
		hkpBvCompressedMeshShapeCinfo();

		virtual ~hkpBvCompressedMeshShapeCinfo() {}

		//
		// Triangles interface
		//

			/// Return the total number of vertices in the geometry.
		virtual	int getNumVertices() const = 0;

			/// Return the total number of triangles in the geometry.
		virtual	int getNumTriangles() const = 0;

			/// Retrieve a vertex given its index.
		virtual void getVertex( int vertexIndex, hkVector4& vertexOut ) const = 0;

			/// Retrieve the three vertex indices of a triangle given its index.
		virtual void getIndices( int triangleIndex, int* indices ) const = 0;

			/// Return the collision filter information for a given triangle index.
			/// Only called when m_collisionFilterInfoMode != PER_PRIMITIVE_DATA_NONE.
		virtual hkUint32 getTriangleCollisionFilterInfo( int triangleIndex ) const { return 0; }

			/// Return the user data for a given triangle index.
			/// Only called when m_userDataMode != PER_PRIMITIVE_DATA_NONE.
		virtual hkUint32 getTriangleUserData( int triangleIndex ) const { return 0; }
		
			/// Return the user provided string for a given triangle index.
			/// Only called when m_userDataMode == PER_PRIMITIVE_DATA_STRING_PALETTE.
		virtual void getTriangleUserString( int triangleIndex, hkStringPtr& stringOut ) const { stringOut.set(""); }

		//
		// Convex shapes interface
		//

			/// Return the total number of convex shapes.
		virtual int getNumConvexShapes() const = 0;

			/// Return a convex shape and its transform given its index.
			/// Note that if the shape convex radius if different to m_convexRadius, an extra storage cost of 2 bytes will occur.
		virtual void getConvexShape( int convexIndex, const hkpConvexShape*& convexShapeOut, hkQsTransform& transformOut ) const = 0;

			/// Return the collision filter information for a given convex shape index.
			/// Only called when m_collisionFilterInfoMode != PER_PRIMITIVE_DATA_NONE.
		virtual hkUint32 getConvexShapeCollisionFilterInfo( int convexIndex ) const { return 0; }

			/// Return the user data for a given convex shape index.
			/// Only called when m_userDataMode != PER_PRIMITIVE_DATA_NONE.
		virtual hkUint32 getConvexShapeUserData( int convexIndex ) const { return 0; }

			/// Return the user provided string for a given convex shape index.
			/// Only called when m_userDataMode == PER_PRIMITIVE_STRING_PALETTE.
		virtual void getConvexShapeUserString( int convexIndex, hkStringPtr& stringOut ) const { stringOut.set(""); }

		//
		// Helpers
		//

			/// Retrieve the three vertices of a triangle using the interface methods.
		HK_FORCE_INLINE void getVertices( int triangleIndex, hkVector4* verticesOut ) const
		{
			int i[3];
			getIndices( triangleIndex, i );
			getVertex( i[0], verticesOut[0] );
			getVertex( i[1], verticesOut[1] );
			getVertex( i[2], verticesOut[2] );
		}

	public:

		//
		// Inputs
		//

			/// Defines how per primitive collision filter info should be stored.
			/// Defaults to PER_PRIMITIVE_DATA_NONE, meaning no collision filter info will be stored.
		hkEnum<hkpBvCompressedMeshShape::PerPrimitiveDataMode, hkUint8> m_collisionFilterInfoMode;

			/// Defines how per primitive user data should be stored.
			/// Defaults to PER_PRIMITIVE_DATA_NONE, meaning no user data will be stored.
		hkEnum<hkpBvCompressedMeshShape::PerPrimitiveDataMode, hkUint8> m_userDataMode;

			/// Convex radius applied to each primitive, unless the primitive provides its own.
			/// Defaults to zero.
		hkReal m_convexRadius;

			/// Minimum distance between two vertices required to weld them together in the compression process. 
			/// Defaults to zero.
		hkReal m_vertexWeldingTolerance;

			/// Maximum allowed error for convex shape compression.
			/// Defaults to HK_REAL_MAX.
		hkReal m_maxConvexShapeError;

			/// Maximum allowed error for triangle vertices compression.
			/// Defaults to HK_REAL_MAX.
		hkReal m_maxVerticesError;

			/// Triangle welding type.
			/// Defaults to WELDING_TYPE_NONE.
		hkpWeldingUtility::WeldingType m_weldingType;

			/// If welding is used, snap contact normals of contacts with open edges to the triangle normal. 
			/// Defaults to true.
		hkBool m_weldOpenEdges;

			/// Set it to true if you want to force the order of triangle vertices to be preserved.
			/// Note that if welding is enabled the order will also be preserved regardless of this setting.
			/// Defaults to false.
		hkBool m_preserveVertexOrder;

		//
		// Outputs
		//

			/// If non NULL, this will be filled with a mapping between the input triangle indices
			/// and the child shape keys that were generated.
		hkArray<hkUint32>* m_triangleIndexToShapeKeyMap;					

			/// If non NULL, this will be filled with a mapping between the input convex shape indices
			/// and the child shape keys that were generated.
		hkArray<hkUint32>* m_convexShapeIndexToShapeKeyMap;				
};


	/// Default implementation of hkpBvCompressedMeshShapeCinfo,
	/// Uses hkGeometry for meshes and local storage for convex shapes and their transforms.
	/// Uses the user data contained in the convex shapes and the triangle materials.
class hkpDefaultBvCompressedMeshShapeCinfo : public hkpBvCompressedMeshShapeCinfo
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_SHAPE, hkpDefaultBvCompressedMeshShapeCinfo );

		hkpDefaultBvCompressedMeshShapeCinfo( const hkGeometry* geometry = HK_NULL ) : m_geometry( geometry ) {}

		virtual ~hkpDefaultBvCompressedMeshShapeCinfo();

			/// Add a convex shape with a transform to the construction info.
		void addConvexShape(const hkpConvexShape* convexShape, const hkQsTransform& transform = hkQsTransform::getIdentity());

		//
		// hkpBvCompressedMeshShapeCinfo interface implementation
		//

		virtual int getNumVertices() const;
		virtual int getNumTriangles() const;
		virtual void getVertex( int vi, hkVector4& vertexOut ) const;
		virtual void getIndices( int ti, int* indices ) const;
		virtual hkUint32 getTriangleUserData( int triangleIndex ) const;

		virtual int getNumConvexShapes() const;
		virtual void getConvexShape( int convexIndex, const hkpConvexShape*& convexShapeOut, hkQsTransform& transformOut ) const;
		virtual hkUint32 getConvexShapeUserData( int convexIndex ) const;

	public:

			/// A convex shape with a transform
		struct ConvexShapeInfo
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_SHAPE, ConvexShapeInfo );

			const hkpConvexShape*	m_shape;
			hkQsTransform			m_transform;
		};

			/// Input geometry
		const hkGeometry* m_geometry;

			/// Input convex shapes
		hkArray<ConvexShapeInfo> m_shapes;
};

#endif // HKP_BV_COMPRESSED_MESH_SHAPE_CINFO_H

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
