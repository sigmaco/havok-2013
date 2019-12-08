/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_BV_TREE_SHAPE_H
#define HKP_BV_TREE_SHAPE_H

#include <Physics2012/Collide/Shape/hkpShape.h>
#include <Physics2012/Collide/Shape/hkpShapeContainer.h>
#include <Physics2012/Collide/Shape/Compound/Collection/hkpShapeCollection.h>
#include <Common/Base/Types/Geometry/Sphere/hkSphere.h>

class hkpShapeCollection;
struct hkpAabbCastCollector;

extern const hkClass hkpBvTreeShapeClass;

	// The maximum number of keys returned by a single queryAabb query. Must be a power of 2
	enum { HK_MAX_NUM_HITS_PER_AABB_QUERY = 2048 };


	/// An hkpBvTreeShape adds bounding volume tree information to an hkpShapeCollection, such as an hkpMeshShape.
	/// This is an abstract base class. See hkpMoppBvTreeShape for an implementation.
	///
	/// What does the bounding volume tree do?
	///
	/// A bounding volume tree is useful in situations where you need to check for collisions between a moving object
	/// and a large static geometry, such as a landscape.
	///
	/// The shapes that make up the landscape are hierarchically grouped in
	/// a binary bounding volume tree.
	/// At every node in the tree there exists a bounding polytope, which encapsulates all
	/// of its children. The top-level bounding volume contains the entire landscape, while
	/// the nodes on the leaf levels encapsulate one geometric primitive, normally a
	/// triangle. The fit of this bounding volume can be perfect (as in some AABB trees), or can
	/// have an extra margin/tolerance built in (e.g. MOPP). For more information please see the
	/// section on Creating Shapes in the Collision Detection chapter of the Physics manual.
	///
	/// Instead of checking whether the moving object is colliding with each of the triangles in the landscape in turn,
	/// which would be extremely time-consuming, the bounding box of the moving object
	/// is checked against the bounding volume tree - first, whether it is intersecting with the top-level bounding volume, then with
	/// any of its child bounding volumes, and so on until the check reaches the leaf nodes. A list of any potentially colliding triangles
	/// is then passed to the narrowphase collision detection. You can think of
	/// the bounding volume tree as a filter to the narrowphase collision
	/// detection system.
class hkpBvTreeShape: public hkpShape
{
	// +version(1)

	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SHAPE);
		HK_DECLARE_REFLECTION();
		HKCD_DECLARE_SHAPE_TYPE(hkcdShapeType::BV_TREE);

		enum BvTreeType
		{
			BVTREE_MOPP,
			BVTREE_TRISAMPLED_HEIGHTFIELD,
			BVTREE_STATIC_COMPOUND,
			BVTREE_COMPRESSED_MESH,
			BVTREE_USER,			
			BVTREE_MAX
		};

			/// Empty constructor, to be called by the shape vtable util on SPU
		HK_FORCE_INLINE hkpBvTreeShape() {}

			/// Creates an hkpBvTreeShape with the specified hkpShapeCollection.
		inline hkpBvTreeShape( ShapeType type, BvTreeType bvType );

	public:

			/// Returns the hkpShapeKey for all shapes in the hkpShapeCollection that intersect with the AABB. The initial contents of the
			/// hits array are preserved, query results are appended at the end.
		virtual void queryAabb( const hkAabb& aabb, hkArray<hkpShapeKey>& hits ) const = 0;

			/// Populates the preallocated hits buffer with shape keys, returns the number of actual hits which may be greater than maxNumKeys.
			/// The hits array should be able to hold maxNumKeys keys. On SPU this is no more than HK_MAX_NUM_HITS_PER_AABB_QUERY
		HK_FORCE_INLINE hkUint32 queryAabb( const hkAabb& aabb, hkpShapeKey* hits, int maxNumKeys ) const;

			/// Adds a hit to the collector for every shape in the hkpShapeCollection whose aabb overlaps with the 
			/// casted one at any point on its path.
			/// \param from Cast aabb in its initial position in the hkpBvTreeShape space
			/// \param to Final position of the aabb center in the hkpBvTreeShape space
			/// \param collector Collector used to gather the cast results
		HK_FORCE_INLINE void castAabb( const hkAabb& from, hkVector4Parameter to, hkpAabbCastCollector& collector ) const;
		
			/// Default implementation for the castAabb method. Call castAabb to make sure the optimal implementation 
			/// for the object's dynamic type is used.
		HKP_SHAPE_VIRTUAL void castAabbImpl( HKP_SHAPE_VIRTUAL_THIS const hkAabb& from, hkVector4Parameter to, hkpAabbCastCollector& collector ) HKP_SHAPE_VIRTUAL_CONST;

			// Set up the bv-tree specific tables on the SPU
		static void HK_CALL HK_INIT_FUNCTION( registerBvTreeCollideFunctions )();
		static void HK_CALL HK_INIT_FUNCTION( registerBvTreeCollideFunctions_StaticCompound )();
		static void HK_CALL HK_INIT_FUNCTION( registerBvTreeCollideQueryFunctions )();


		hkpBvTreeShape( hkFinishLoadedObjectFlag flag );
		
		virtual const hkpShapeContainer* getContainer() const = 0;

		HKP_SHAPE_VIRTUAL hkUint32 queryAabbImpl(HKP_SHAPE_VIRTUAL_THIS const hkAabb& aabb, hkpShapeKey* hits, int maxNumKeys ) HKP_SHAPE_VIRTUAL_CONST = 0;


	public:

		hkEnum<BvTreeType, hkUint8> m_bvTreeType; //+default(hkpBvTreeShape::BVTREE_USER)
};

#include <Physics2012/Collide/Shape/Compound/Tree/hkpBvTreeShape.inl>

#endif // HKP_BV_TREE_SHAPE_H

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
