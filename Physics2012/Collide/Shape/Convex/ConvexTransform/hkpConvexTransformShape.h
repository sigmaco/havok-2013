/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_CONVEX_TRANSFORM_SHAPE_H
#define HKP_CONVEX_TRANSFORM_SHAPE_H

#include <Physics2012/Collide/Shape/Convex/hkpConvexShape.h>

class hkpConvexVerticesShape;
extern const hkClass hkpConvexTransformShapeClass;


	/// hkpConvexTransformShape contains an hkpShape and an additional transform for that shape.
	/// This is useful, for example, if you want to reuse a particular child shapes multiple
	/// times at different transforms within a parent shape container.
	/// The advantage of hkpConvexTransformShape over hkpTransformShape is that it does not
	/// require additional collision agents to be created. Instead, it intercepts the calls to
	/// getSupportVertex() (etc) from the collision detector and modifies them.
	/// For detailed information on SPU handling for this shape, see hkpConvexTranslateShape.h
class hkpConvexTransformShape : public hkpConvexTransformShapeBase
{
	//+version(2)

	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SHAPE);
		HK_DECLARE_REFLECTION();
		HKCD_DECLARE_SHAPE_TYPE(hkcdShapeType::CONVEX_TRANSFORM);

	public:

			/// Empty constructor, to be called by the shape vtable util on SPU
		HK_FORCE_INLINE hkpConvexTransformShape() {}

			/// Constructs a new convex transform shape without scale.
			/// The hkpShapeContainer::ReferencePolicy is only used for the constructor, the destructor will still always decrement the childs reference
		hkpConvexTransformShape( const hkpConvexShape* childShape, const hkTransform& transform, hkpShapeContainer::ReferencePolicy ref = hkpShapeContainer::REFERENCE_POLICY_INCREMENT );

			/// Constructs a new convex transform shape with scale. This is only supported when the child is a hkpConvexVerticesShape.
			/// The hkpShapeContainer::ReferencePolicy is only used for the constructor, the destructor will still always decrement the childs reference
		hkpConvexTransformShape( const hkpConvexShape* childShape, const hkQsTransform& transform, hkpShapeContainer::ReferencePolicy ref = hkpShapeContainer::REFERENCE_POLICY_INCREMENT );


			/// Serialization constructor
		hkpConvexTransformShape( class hkFinishLoadedObjectFlag flag );


	public:

			/// Sets the current transform. Additionally, it calculates the extra scale to apply to the child shape vertices
			/// to produce the right scaled convex shell. This process may reduce the convex radius if any of the extents of the 
			/// scaled shape is too small to allow the original radius.
			/// Don't do this once the shape is added to a world as collision agents may have cached data dependent on it.
		void setTransform( const hkQsTransform& transform );

			/// Sets the current transform and sets the extra scale to zero.
			/// Don't do this once the shape is added to a world as collision agents may have cached data dependent on it.
		inline void setTransform( const hkTransform& transform );	

			/// Creates a unscaled copy of the transform from the child shape's space to this transform shape's local space
		inline void getTransform( hkTransform* HK_RESTRICT transform ) const;

			/// Gets the full transform from the child shape's space to this transform shape's local space, including scale
		inline const hkQsTransform& getQsTransform() const;

			/// Gets the internal additional scale.
		inline const hkVector4& getExtraScale() const;

			/// Get the child shape
		inline const hkpConvexShape* getChildShape() const;

			/// Transforms a vertex in the child shape's space to the convex transform space correcting the resulting 
			/// positions to produce the right convex shell
		HK_FORCE_INLINE void transformVertex(hkVector4Parameter localVertex, hkVector4* HK_RESTRICT vertexOut) const;

	public:

		//
		// hkpShapeBase interface implementation.
		//

		virtual void getSupportingVertex(hkVector4Parameter direction, hkcdVertex& supportingVertexOut) const;

		virtual void convertVertexIdsToVertices(const hkpVertexId* ids, int numIds, hkcdVertex* verticesOut) const;

		virtual void getCentre(hkVector4& centreOut) const;

		virtual HK_FORCE_INLINE int getNumCollisionSpheres() const;

		virtual const hkSphere* getCollisionSpheres(hkSphere* sphereBuffer) const;

		virtual void getAabb(const hkTransform& localToWorld, hkReal tolerance, hkAabb& out) const;

		virtual hkBool castRay(const hkpShapeRayCastInput& input, hkpShapeRayCastOutput& results) const;

		virtual void castRayWithCollector(const hkpShapeRayCastInput& input, const hkpCdBody& cdBody, hkpRayHitCollector& collector) const;


		virtual const hkpShapeContainer* getContainer() const;

		virtual int calcSizeForSpu( const CalcSizeForSpuInput& input, int spuBufferSizeLeft ) const;

		// hkpConvexShape interface implementation.
		virtual void getFirstVertex( hkVector4& v ) const;


	protected:

			/// Transform (including non-uniform scale) applied to the child shape. Together with the m_extraScale 
			/// determine the final vertices transformed position. Components X and Y of the child shape's AABB center 
			/// in the child shape's space are stored in the W component of m_translation and m_scale respectively.
		hkQsTransform m_transform;

			/// This scale is computed automatically from the scale in the transform and the child shape's convex radius and 
			/// is used when transforming the child shape's vertices to produce the right convex shell. The W component is 
			/// used to store the Z component of the child shape's AABB center in the child shape's space.
		hkVector4 m_extraScale;
};

#include <Physics2012/Collide/Shape/Convex/ConvexTransform/hkpConvexTransformShape.inl>

#endif // HKP_CONVEX_TRANSFORM_SHAPE_H

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
