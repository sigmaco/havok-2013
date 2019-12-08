/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_CONVEX_VERTICES_SHAPE_H
#define HKP_CONVEX_VERTICES_SHAPE_H

#include <Common/Base/Math/Vector/hkFourTransposedPoints.h>
#include <Common/Base/Types/Geometry/Aabb/hkAabbUtil.h>

#include <Physics2012/Collide/Shape/Convex/hkpConvexShape.h>

extern const class hkClass hkpConvexVerticesShapeFourVectorsClass;
extern const hkClass hkpConvexVerticesShapeClass;

struct hkStridedVertices;
class hkpConvexVerticesConnectivity;


	/// A convex geometric shape, specified by a set of vertices in the shape's local space.
	/// An optional set of corresponding planes may be provided - if present, they will improve
	/// ray cast performance. Optional connectivity information may also be provided - this is
	/// required for certain algorithms, but not for most use cases.
class hkpConvexVerticesShape : public hkpConvexShape
{
	//+version(4)

	public:

		HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_SHAPE );
		HK_DECLARE_REFLECTION();
		HK_DECLARE_GET_SIZE_FOR_SPU( hkpConvexVerticesShape );
		HKCD_DECLARE_SHAPE_TYPE( hkcdShapeType::CONVEX_VERTICES );

	public:

			/// Build configuration.
			/// Warning: m_useOptimizedShrinking is not always robust and is disable by default.
		struct BuildConfig
		{
			BuildConfig();
			hkBool	m_createConnectivity;					///< Create connectivity (default: false).
			hkBool	m_shrinkByConvexRadius;					///< Shrink vertices by convex radius (default: true), so that raycast and physics collisions are consistent.
			hkBool	m_useOptimizedShrinking;				///< Optimized shrinking such as the number of vertices after shrinking is less or equal to the unshrunk shape vertices count.
			hkReal	m_convexRadius;							///< Convex radius (default: hkConvexShapeDefaultRadius).
			int		m_maxVertices;							///< Maximum vertices, used for simplification (default: 0, no simplification).
			hkReal	m_maxRelativeShrink;					///< Maximum relative shrink factor (default: 0.05) (relative to the AABB of the object).
			hkReal	m_maxShrinkingVerticesDisplacement;		///< Maximum vertices displacement due to shrinking (default: 0.07).
			hkReal  m_maxCosAngleForBevelPlanes;			///< If the cos angle (== dot product) of two neighboring face normals is smaller than this, a bevel plane is inserted to optimize raycast behavior (default -0.1f)
		};

	public:

			/// Create a shape from the given vertices, automatically setting planes equations and connectivity.
			/// Also shrink the shape vertices so that collision detection and ray cast results are consistent.
			/// Notes: This is the recommended way to create a convex vertices shape.
		hkpConvexVerticesShape(	const hkStridedVertices& vertices, const BuildConfig& config=BuildConfig() );

			/// Create a shape from the given vertices and matching plane equations.
			/// These are plane equations of the convex hull and can be generated
			/// using the hkGeometryUtility::createConvexGeometry method.
			/// This constructor makes an internal copy of the vertices.
			/// You should take care of not passing in unnecessary vertices, e.g., inner vertices or
			/// duplicated vertices. hkGeometryUtility::createConvexGeometry will also give
			/// you back a clean list of vertices to use.
		hkpConvexVerticesShape( const hkStridedVertices& vertsIn, const hkArray<hkVector4>& planeEquations, hkReal radius = hkConvexShapeDefaultRadius );

			/// Create a shape from precomputed data.
			/// Note: numVertices is the actual number of vertices, not the number of hkFourTransposedPoints structures.
		hkpConvexVerticesShape( hkFourTransposedPoints* rotatedVertices, int numVertices, hkVector4* planes, int numPlanes, const hkAabb& aabb, hkReal radius = hkConvexShapeDefaultRadius );			


			/// Create an empty shape.
		hkpConvexVerticesShape(	hkReal radius = hkConvexShapeDefaultRadius );

			/// Serialization constructor.
		hkpConvexVerticesShape( hkFinishLoadedObjectFlag flag );


			/// Destructor
		~hkpConvexVerticesShape();

			/// Allocates a new convex vertices shape at the given memory location
		static HK_FORCE_INLINE hkpConvexVerticesShape* HK_CALL createInPlace( hkUint8*& memPtr, hkReal convexRadius );

	public:

			/// The original vertices passed during construction are stored in a packed form within the shape.
			/// This retrieves the original vertices into the provided array.
		void getOriginalVertices( hkArray<hkVector4>& vertices ) const;

			/// Returns the plane equations, if any
		const hkArray<hkVector4>& getPlaneEquations() const;
			
			/// Overwrite plane equations
		void setPlaneEquations( const hkArray<hkVector4>& planes );

			/// Overwrite only the convex radius without caring about plane equations or shape shrinking.
		void setRadiusUnchecked( hkReal radius ) { m_radius = radius; }

			// Utility function to convert this shape to a new space
		void transformVerticesAndPlaneEquations( const hkTransform& t );

			// Utility function to overwrite the vertices
		void copyVertexData( const hkReal* vertexIn, int byteStriding, int numVertices );

		//
		// Connectivity
		//

			// Get the connectivity. This is optional for this shape. Returns HK_NULL if connectivity is not present.
		HK_FORCE_INLINE const hkpConvexVerticesConnectivity* getConnectivity() const { return m_connectivity; }

			// Set the connectivity. Setting to HK_NULL will remove connectivity information.
			// The connectivity information is a 'cache' of information - so can be used to modify a const shape
		void setConnectivity( const hkpConvexVerticesConnectivity* connect, bool sort=true );
		

			// hkpConvexShape interface implementation
		void getFirstVertex(hkVector4& v) const;

	protected:

		void sortPlanes(void);


	public:

		//
		// hkpShapeBase interface implementation
		//

		virtual void getSupportingVertex( hkVector4Parameter direction, hkcdVertex& supportingVertexOut ) const;

			// Note: You must be able to supply one valid vertex corresponding to ID 0.
			// This is a requirement because getFirstVertex() is not supported on SPU.
		virtual void convertVertexIdsToVertices( const hkpVertexId* ids, int numIds, hkcdVertex* verticesOut ) const;

		virtual void getCentre( hkVector4& centreOut ) const;

		virtual HK_FORCE_INLINE int getNumCollisionSpheres() const;

		virtual const hkSphere* getCollisionSpheres( hkSphere* sphereBuffer ) const;

		virtual void getAabb( const hkTransform& localToWorld, hkReal tolerance, hkAabb& out ) const;

		virtual hkBool castRay( const hkpShapeRayCastInput& input, hkpShapeRayCastOutput& results ) const;

	public:

			// Cached AABB
		hkVector4 m_aabbHalfExtents;
		hkVector4 m_aabbCenter;

			/// The vertices, packed in a transposed format
		hkArray<hkFourTransposedPoints> m_rotatedVertices;
		hkInt32 m_numVertices;

			// Internal flag indicating whether the vertices reside in SPU memory.
			// This should be true only if constructed on-the-fly by some container shapes.
		hkBool m_useSpuBuffer; //+default(0) +nosave

			/// Optional plane equations, for faster ray cast queries.
		mutable hkArray<hkVector4> m_planeEquations;

			/// Optional (reference counted) vertex connectivity information for this shape.
			/// Set to HK_NULL if connectivity information is not present.
        mutable const hkpConvexVerticesConnectivity* m_connectivity;
};

#include <Physics2012/Collide/Shape/Convex/ConvexVertices/hkpConvexVerticesShape.inl>

#endif // HKP_CONVEX_VERTICES_SHAPE_H

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
