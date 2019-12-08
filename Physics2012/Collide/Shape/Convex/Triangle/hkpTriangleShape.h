/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_TRIANGLE_SHAPE_H
#define HKP_TRIANGLE_SHAPE_H

#include <Physics2012/Collide/Shape/Convex/hkpConvexShape.h>
#include <Physics2012/Collide/Util/Welding/hkpWeldingUtility.h>

extern const hkClass hkpTriangleShapeClass;


	/// A triangle shape stored as 3 vertices and an optional extrusion.
	/// This shape is typically created on-the-fly at runtime, for example by a mesh shape.
class hkpTriangleShape : public hkpConvexShape
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_SHAPE );
		HK_DECLARE_REFLECTION();
		HKCD_DECLARE_SHAPE_TYPE( hkcdShapeType::TRIANGLE );
		HK_DECLARE_GET_SIZE_FOR_SPU( hkpTriangleShape );

	public:


			/// Serialization constructor
		hkpTriangleShape( hkFinishLoadedObjectFlag flag );

			/// Default constructor
		HK_FORCE_INLINE hkpTriangleShape( hkReal radius = hkConvexShapeDefaultRadius, hkUint16 weldingInfo = 0, hkpWeldingUtility::WeldingType type = hkpWeldingUtility::WELDING_TYPE_NONE );

			/// Constructor that sets the points of the triangle.
		HK_FORCE_INLINE hkpTriangleShape( const hkVector4& v0, const hkVector4& v1, const hkVector4& v2, hkReal radius = hkConvexShapeDefaultRadius );


			/// Allocates a new triangle at the given memory location
		static HK_FORCE_INLINE hkpTriangleShape* HK_CALL createInPlace( hkUint8*& memPtr, hkReal convexRadius, hkpWeldingUtility::WeldingType weldingType, hkUint16 weldingInfo );

	public:

			/// Get a pointer to the vertices of the triangle.
		HK_FORCE_INLINE const hkVector4* getVertices() const;

			/// Get a non const reference to a vertex.
			/// The parameter "i" must be 0, 1 or 2
		HK_FORCE_INLINE hkVector4& getVertex( int i );

			/// Get a const reference to a vertex.
			/// The parameter "i" must be 0, 1 or 2
		HK_FORCE_INLINE const hkVector4& getVertex( int i ) const;
		template <int I> HK_FORCE_INLINE const hkVector4& getVertex() const;

			/// Set a vertex.
			/// The parameter "i" must be 0, 1 or 2
		HK_FORCE_INLINE void setVertex( int i, const hkVector4& vertex );
		template <int I> HK_FORCE_INLINE void setVertex(hkVector4Parameter vertex );

		//
		// Welding Info
		//

			/// Get the welding info for this triangle
		HK_FORCE_INLINE hkUint16 getWeldingInfo() const;

			/// Set the welding info for this triangle
		HK_FORCE_INLINE void setWeldingInfo( hkUint16 info );

			/// Get the welding type for the triangle
		HK_FORCE_INLINE hkpWeldingUtility::WeldingType getWeldingType() const;

			/// Set the welding type for the triangle
		HK_FORCE_INLINE void setWeldingType( hkpWeldingUtility::WeldingType type );

		//
		// Extrusion info
		//

		HK_FORCE_INLINE bool isExtruded() const;

		HK_FORCE_INLINE const hkVector4& getExtrusion() const;

		HK_FORCE_INLINE void setExtrusion( const hkVector4& extrusion );

	public:

		//
		// hkpShapeBase interface implementation
		//

		virtual void getSupportingVertex( hkVector4Parameter direction, hkcdVertex& supportingVertexOut ) const;

		virtual void convertVertexIdsToVertices( const hkpVertexId* ids, int numIds, hkcdVertex* verticesOut ) const;

		virtual int weldContactPoint( hkpVertexId* featurePoints, hkUint8& numFeaturePoints, hkVector4& contactPointWs, const hkTransform* thisObjTransform, const hkpConvexShape* collidingShape, const hkTransform* collidingTransform, hkVector4& separatingNormalInOut ) const;

		virtual void getCentre( hkVector4& centreOut ) const;

		virtual HK_FORCE_INLINE int getNumCollisionSpheres() const;

		virtual const hkSphere* getCollisionSpheres( hkSphere* sphereBuffer ) const;

		virtual void getAabb( const hkTransform& localToWorld, hkReal tolerance, hkAabb& out ) const;

		virtual hkBool castRay( const hkpShapeRayCastInput& input, hkpShapeRayCastOutput& results ) const;

		virtual hkVector4Comparison castRayBundle( const hkpShapeRayBundleCastInput& input, hkpShapeRayBundleCastOutput& results, hkVector4ComparisonParameter mask ) const;


			// hkpConvexShape interface implementation.
		virtual void getFirstVertex( hkVector4& v ) const;


	protected:

		hkUint16 m_weldingInfo; //+default(0)
		hkEnum<hkpWeldingUtility::WeldingType, hkUint8> m_weldingType; // +default(hkpWeldingUtility::WELDING_TYPE_NONE)
		hkUint8 m_isExtruded;

		hkVector4 m_vertexA;
		hkVector4 m_vertexB;
		hkVector4 m_vertexC;

		hkVector4 m_extrusion;
};

#include <Physics2012/Collide/Shape/Convex/Triangle/hkpTriangleShape.inl>

#endif // HKP_TRIANGLE_SHAPE_H

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
