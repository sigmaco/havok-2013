/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_SHAPE_COLLECTION_H
#define HKP_SHAPE_COLLECTION_H

#include <Physics2012/Collide/Shape/hkpShape.h>
#include <Physics2012/Collide/Shape/hkpShapeContainer.h>
#include <Physics2012/Collide/Util/Welding/hkpWeldingUtility.h>

extern hkReal hkConvexShapeDefaultRadius;
extern const hkClass hkpShapeCollectionClass;


	/// An interface to a collection of Shapes, each of which can be identified using a hkpShapeKey.
class hkpShapeCollection : public hkpShape, public hkpShapeContainer
{
	//+abstract(1)

	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SHAPE);
		HK_DECLARE_REFLECTION();
		HKCD_DECLARE_SHAPE_TYPE(hkcdShapeType::COLLECTION);

	public:

		enum CollectionType
		{
				/// hkpListShape
			COLLECTION_LIST,

				/// hkpExtendedMeshShape
			COLLECTION_EXTENDED_MESH,

				/// hkpTriSampledHeightFieldCollection
			COLLECTION_TRISAMPLED_HEIGHTFIELD,

				/// All other collections.
				/// These are not simulated on SPU by default, but can be by changing registerSimulationFunctions()
			COLLECTION_USER,

				/// hkpSimpleMeshShape. Not simulated on the SPU.
			COLLECTION_SIMPLE_MESH,

				/// hkpMeshShape. Not simulated on the SPU.
			COLLECTION_MESH_SHAPE,

				/// hkpCompressedMeshShape
			COLLECTION_COMPRESSED_MESH,

				/// Maximum count
			COLLECTION_MAX
		};

	public:

			/// Empty constructor, to be called by the shape vtable util on SPU
		HK_FORCE_INLINE hkpShapeCollection() {}

			/// Empty constructor
		hkpShapeCollection( ShapeType type, CollectionType collectionType );


			/// Serialization constructor
		hkpShapeCollection( hkFinishLoadedObjectFlag flag );

	public:
		
			/// Gets the AABB for the hkpShape given a local to world transform and an extra tolerance.
			/// This default implementation is rather slow and just iterates over all children
		virtual void getAabb( const hkTransform& localToWorld, hkReal tolerance, hkAabb& out ) const;

			/// Implements the castRay function. Note that for shape collections with many sub-shapes this
			/// function can be very slow. It is better to use a hkpBvTreeShape::castRay instead
		virtual hkBool castRay( const hkpShapeRayCastInput& input, hkpShapeRayCastOutput& results ) const;

			/// Note: the default implementation call hkpShape::castRay( ..., hkpShapeRayCastOutput& results )
		virtual void castRayWithCollector( const hkpShapeRayCastInput& input, const hkpCdBody& cdBody, hkpRayHitCollector& collector ) const;

	public:

		//
		// hkpShape interface
		//

			/// Support for creating bounding volume hierarchies of shapes.
			/// This default implementation is rather slow and just iterates over all children.
		virtual hkReal getMaximumProjection( const hkVector4& direction ) const;

		virtual const hkpShapeContainer* getContainer() const;

		//
		// Welding interface
		//

		HK_FORCE_INLINE bool isWeldingEnabled() const { return !m_disableWelding; }

			/// Sets the welding type for the collection. This is called automatically by hkpMeshWeldingUtility::computeWeldingInfo
			/// and hkpMeshWeldingUtility::computeWeldingInfoMultiShape. You can call this manually, which allows you to set the welding type to
			/// hkpWeldingUtility::WELDING_TYPE_NONE, clearing welding information
		virtual void initWeldingInfo( hkpWeldingUtility::WeldingType weldingType );


			/// Sets the welding info for a child shape in the collection. This is called automatically by hkpMeshWeldingUtility::computeWeldingInfo
			/// and hkpMeshWeldingUtility::computeWeldingInfoMultiShape
		virtual void setWeldingInfo( hkpShapeKey key, hkInt16 weldingInfo );		


	public:

			/// A flag to allow you to disable the deprecated welding. This is set automatically for a mesh when you call
			/// computeWeldingInfo
		hkBool m_disableWelding;

			/// subtype for the shape collection. Used for dispatching to the right subclass on the SPU.
		hkEnum<CollectionType, hkUint8> m_collectionType; //+default(hkpShapeCollection::COLLECTION_USER)
};

#endif // HKP_SHAPE_COLLECTION_H

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
