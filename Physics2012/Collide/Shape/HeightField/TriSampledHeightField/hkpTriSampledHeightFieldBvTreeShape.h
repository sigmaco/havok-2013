/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_TRI_SAMPLED_HEIGHTFIELD_BVTREE_SHAPE
#define HKP_TRI_SAMPLED_HEIGHTFIELD_BVTREE_SHAPE

#include <Physics2012/Collide/Shape/Compound/Tree/hkpBvTreeShape.h>

extern const hkClass hkpTriSampledHeightFieldBvTreeShapeClass;

class hkpTriSampledHeightFieldCollection;

/// This shape must be used in conjunction with the hkpTriSampledHeightFieldCollection. Please see the documentation for
/// the hkpTriSampledHeightFieldCollection for details on what the classes do.
class hkpTriSampledHeightFieldBvTreeShape : public hkpBvTreeShape
{
	//+hk.ReflectedFile("hkpHeightField")
	//+version(1)
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SHAPE);
		HK_DECLARE_REFLECTION();
		HKCD_DECLARE_SHAPE_TYPE(hkcdShapeType::TRI_SAMPLED_HEIGHT_FIELD_BV_TREE);

		/// Empty constructor, leaves everything uninitialized, as it will only be called on SPU from the shape vtable util
		HK_FORCE_INLINE hkpTriSampledHeightFieldBvTreeShape() {}

			/// The constructor takes a pointer to hkpTriSampledHeightFieldCollection.
			/// This class is designed to work together with the hkpTriSampledHeightFieldCollection.
			/// The value "doAabbRejection" can be used to turn off the AABB rejection test.
			/// The queryAabb() method (which will be used by agents/user queries using
			/// the hkpBvTreeShape interface) uses its projection onto the heightfield grid
			/// space to determine what triangles to return.
			/// To ensure that the resulting triangles are at least close to the
			/// AABB in the direction of projection (that the AABB is not hovering completely
			/// above or below all points in that area of heightfield), this test checks that it
			/// at least overlaps the single AABB bounding all those triangles.
			/// By default it is true. Setting it to false disables the test,
			/// which may give a small speedup for flat heightfields.
		hkpTriSampledHeightFieldBvTreeShape( const hkpTriSampledHeightFieldCollection* c, hkBool doAabbRejection = true );

		//
		// hkpBvTreeShape interface
		//

			/// Returns the hkpShapeKey for all shapes in the hkpShapeCollection that intersect with the OBB (defined by obbTransform and obbExtent).
			/// This implementation simply bounds the OBB by an AABB and uses the queryAabb() method. Thus it is not as
			/// accurate as it could be if using a more sophisticated algorithm, and can return triangles completely outside the OBB.
		virtual void queryObb( const hkTransform& obbTransform, const hkVector4& obbExtent, hkReal tolerance, hkArray< hkpShapeKey >& hits ) const;

			/// Returns the hkpShapeKey for all shapes in the hkpShapeCollection that intersect with the AABB.
		virtual void queryAabb( const hkAabb& aabb, hkArray<hkpShapeKey>& hits ) const;

			// hkpBvTreeShape interface implementation.
		HKP_SHAPE_VIRTUAL hkUint32 queryAabbImpl(HKP_SHAPE_VIRTUAL_THIS const hkAabb& aabb, hkpShapeKey* hits, int maxNumKeys ) HKP_SHAPE_VIRTUAL_CONST;
			
		//
		// hkpShape interface
		//

			// hkpShape interface implementation.
		virtual void getAabb(const hkTransform& localToWorld, hkReal tolerance, hkAabb& out) const;

			// hkpShape interface implementation.
		virtual hkBool castRay(const hkpShapeRayCastInput& input, hkpShapeRayCastOutput& output) const;

			// hkpShape interface implementation.
		virtual void castRayWithCollector(const hkpShapeRayCastInput& input, const hkpCdBody& cdBody, hkpRayHitCollector& collector) const;


			/// Serialization constructor
		hkpTriSampledHeightFieldBvTreeShape( hkFinishLoadedObjectFlag flag );

			// Retrieves the shape collection, DMAing from PPU if necessary
		inline const hkpTriSampledHeightFieldCollection* getShapeCollection() const;

			// hkpBvTreeShape interface implementation.
		inline const hkpShapeContainer* getContainer() const;

			// hkpShape interface implementation.
		virtual int calcSizeForSpu(const CalcSizeForSpuInput& input, int spuBufferSizeLeft) const;


		HK_FORCE_INLINE hkBool getWantAabbRejectionTest() const { return m_wantAabbRejectionTest; }
		HK_FORCE_INLINE void   setWantAabbRejectionTest(hkBool newVal) { m_wantAabbRejectionTest = newVal; }

	protected:
		
		static hkBool HK_CALL getExtentsForQueryAabb(hkAabb& aabb, const hkpTriSampledHeightFieldCollection* collection, hkUint32& minX, hkUint32& maxX, hkUint32& minZ, hkUint32& maxZ);

		class hkpSingleShapeContainer m_childContainer;
		mutable int	m_childSize;	//+nosave
		
		hkBool m_wantAabbRejectionTest;
		
		// Need to pad to a multiple of 16 on SPU
		hkUint8 m_padding[12];	//+nosave
};

#include <Physics2012/Collide/Shape/HeightField/TriSampledHeightField/hkpTriSampledHeightFieldBvTreeShape.inl>

#endif // HKP_TRI_SAMPLED_HEIGHTFIELD_BVTREE_SHAPE

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
