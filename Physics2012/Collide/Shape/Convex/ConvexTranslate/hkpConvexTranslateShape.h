/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_CONVEX_TRANSLATE_SHAPE_H
#define HKP_CONVEX_TRANSLATE_SHAPE_H

#include <Physics2012/Collide/Shape/Convex/hkpConvexShape.h>
#include <Physics2012/Collide/Shape/hkpShapeContainer.h>

extern const hkClass hkpConvexTranslateShapeClass;

	/// An hkpConvexTranslateShape contains an hkpShape and an additional translation for that shape.
	/// This is useful, for instance, if you
	/// want to position child shapes correctly when constructing a compound shape.
	/// The advantage of using hkpConvexTranslateShape over hkpTransformShape is that
	/// it does not require additional agents to be created, as the hkpConvexTranslateShape is
	/// a convex shape and directly works with GSK.
	/// However, if you use the hkpConvexTranslateShape wrapping an hkpBoxShape, no hkpBoxBoxAgent will be
	/// created, but the hkpGskfAgent.
	///
	/// On PlayStation(R)3 this shape's collision detection will only be allowed to move onto an SPU if
	///     -# all its children are supported on SPU
	///     -# its total size including all its children will fit into one of the SPU's shape buffers
	///
	/// If this is the case a call to getChildShape() on the SPU will DMA in the child shape from
	/// main memory (and thus cause a code execution stall). To improve this we have added
	/// support for the situation where the child shape follows this hkpConvexTranslateShape consecutively in memory.
	/// In such a case both the hkpConvexTranslateShape and its child shape are brought in in one
	/// single DMA operation. Note that this properly takes care of cascades as well, i.e., several
	/// hkConvexTranslateShapes in a row are all brought in in one go.
	/// hkpConvexTransformShape supports the same mechanism and thus works as part of such a cascade as well.
class hkpConvexTranslateShape : public hkpConvexTransformShapeBase
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SHAPE);
		HK_DECLARE_REFLECTION();
		HKCD_DECLARE_SHAPE_TYPE(hkcdShapeType::CONVEX_TRANSLATE);

	public:

			/// Empty constructor, to be called by the shape vtable util on SPU
		HK_FORCE_INLINE hkpConvexTranslateShape() {}

			/// Constructs a new convex translate shape.
			/// Note: The hkpShapeContainer::ReferencePolicy is only used for the constructor, the destructor will still always decrement the childs reference
		HK_FORCE_INLINE hkpConvexTranslateShape(const hkpConvexShape* childShape, const hkVector4& translation, hkpShapeContainer::ReferencePolicy ref = hkpShapeContainer::REFERENCE_POLICY_INCREMENT );

	public:

			/// Get the child shape.
		inline const hkpConvexShape* getChildShape() const;

			// hkpSpuShape interface implementation.
		virtual void getSupportingVertex(hkVector4Parameter direction, hkcdVertex& supportingVertexOut) const;

			// hkpSpuShape interface implementation.
		virtual void convertVertexIdsToVertices(const hkpVertexId* ids, int numIds, hkcdVertex* verticesOut) const;

			// hkpConvexShape interface implementation.
		virtual void getCentre(hkVector4& centreOut) const;

			// hkpShapeBase interface implementation.
		virtual HK_FORCE_INLINE int getNumCollisionSpheres() const;

			// hkpShapeBase interface implementation.
		virtual const hkSphere* getCollisionSpheres(hkSphere* sphereBuffer) const;

			// hkpShapeBase interface implementation.
		virtual void getAabb(const hkTransform& localToWorld, hkReal tolerance, hkAabb& out) const;

			// hkpShapeBase interface implementation.
		virtual hkBool castRay(const hkpShapeRayCastInput& input, hkpShapeRayCastOutput& results) const;

			// hkpShapeBase interface implementation.
		virtual void castRayWithCollector(const hkpShapeRayCastInput& input, const hkpCdBody& cdBody, hkpRayHitCollector& collector) const;

	public:

			/// Gets the child shape position in local space
		inline hkVector4& getTranslation();

			/// Gets the child shape position in local space
		inline const hkVector4& getTranslation() const;


			/// Serialization constructor
		hkpConvexTranslateShape( class hkFinishLoadedObjectFlag flag );

			// hkpShape interface implementation.
		virtual void getFirstVertex(hkVector4& v) const;

			// hkpShape interface implementation.
		virtual hkReal getMaximumProjection( const hkVector4& direction ) const;

			// hkpShape interface implementation.
		virtual const hkpShapeContainer* getContainer() const;

			// hkpShape interface implementation.
		virtual int calcSizeForSpu(const CalcSizeForSpuInput& input, int spuBufferSizeLeft) const;


	protected:

		hkVector4 m_translation;
};

#include <Physics2012/Collide/Shape/Convex/ConvexTranslate/hkpConvexTranslateShape.inl>

#endif // HKP_CONVEX_TRANSLATE_SHAPE_H

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
