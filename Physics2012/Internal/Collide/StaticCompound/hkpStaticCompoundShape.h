/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_STATIC_COMPOUND_SHAPE_H
#define HKP_STATIC_COMPOUND_SHAPE_H

#include <Physics2012/Collide/Shape/Compound/Tree/hkpBvTreeShape.h>
#include <Physics2012/Internal/Collide/StaticCompound/hkpShapeKeyTable.h>

//HK_HAVOK_ASSEMBLY_EXCLUDE_FILE

struct hkpAabbCastCollector;

extern const hkClass hkcdStaticTreeDefaultTreeStorage6Class;

	/// A shape containing a static set of other hkpShape instances, positioned using hkQsTransforms,
	/// which allow for non-uniform scaling. A bounding volume wraps the instance AABBs, so it it not
	/// necessary to wrap this shape with any further bounding volume shapes.
	///
	/// Each instance also stores user data and collision filter information. A filter mask allows
	/// users to choose whether collision filter info for the instance's leaf shapes should come from
	/// those leaf shapes or from the instance itself.
	///
	/// Instances and shape keys can be disabled and enabled at runtime. Disabling shape keys does
	/// not modify the underlying hkpShapes, so while the same hkpShape can appear in multiple instances,
	/// shape keys of one particular instance of that hkpShape can be disabled without altering any
	/// other instances.
	///
	/// Shape keys used by this shape refer to a specific child shape key of a specific instance shape.
	/// This means that the engine will often see this shape as a flat list of leaf shapes rather than
	/// a hierarchy of shapes, which results in reduced collision agent overhead versus a shape hierarchy.
	/// Note that this also means that the instanced hkpShapes may not be readily available in collision
	/// events. Users can always recover that shape if necessary, by using the shape key decomposition
	/// functions.
class hkpStaticCompoundShape : public hkpBvTreeShape, public hkpShapeContainer
{
	public:

			/// An instance of a child shape.
		struct Instance
		{
			public:

				enum
				{
					FLAG_IS_LEAF					= 0x01,		// is a simple convex shape, no container
					FLAG_HAS_TRANSFORM				= 0x02,		// has a non-identity transform
					FLAG_HAS_SCALE					= 0x04,		// has a non-identity scale
					FLAG_HAS_FLIP					= 0x08,		// has a flipping scale

					FLAG_IS_DISABLED				= 0x10,		// the whole instance is disabled
					FLAG_HAS_DISABLED_SMALL_KEYS	= 0x20,		// is using the local instance bits for disabled keys
					FLAG_HAS_DISABLED_LARGE_KEYS	= 0x40,		// is using the shape key table for disabled keys

					FLAGS_HAS_DISABLED_KEYS			= 0x60,		// combination of _SMALL_KEYS and _LARGE_KEYS
					FLAGS_ALL						= 0x7f
				};

				
				enum
				{
					NUM_BITS_FOR_FLAGS					= 7,
					NUM_BITS_FOR_SHAPE_SIZE				= 4,	
					NUM_BITS_FOR_DISABLED_SMALL_KEYS	= 37
				};

			protected:

				HK_FORCE_INLINE void setShapeSizeForSpu( hkUint32 size );
				HK_FORCE_INLINE void setFlags( hkUint32 flags );

				hkQsTransform		m_transform;	// flags, child size and small key states stored across T(3), S(3)
				const hkpShape*		m_shape;

			public:

				HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_COLLIDE, hkpStaticCompoundShape::Instance );
				HK_DECLARE_REFLECTION();

				HK_FORCE_INLINE const hkQsTransform& getTransform() const;
				HK_FORCE_INLINE const hkpShape* getShape() const;
				HK_FORCE_INLINE hkUint32 getShapeSizeForSpu() const;
				HK_FORCE_INLINE hkUint32 getFlags() const;

				hkUint32	m_filterInfo;
				hkUint32	m_childFilterInfoMask;
				hkUlong		m_userData;

				friend class hkpStaticCompoundShape;
				friend class hkpStaticCompoundShape_Internals;
		};

			/// Compile-time configuration.
		enum Config
		{
			
			
			#ifdef HK_REAL_IS_DOUBLE
				NUM_BYTES_FOR_TREE = 96
			#else
				NUM_BYTES_FOR_TREE = 48
			#endif
		};

	public:

		HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_SHAPE );
		HK_DECLARE_REFLECTION();
		HKCD_DECLARE_SHAPE_TYPE( hkcdShapeType::STATIC_COMPOUND );

		//
		// Construction
		//

			/// Construct an empty shape. Use addInstance() to populate the shape.
			/// The \a ref policy defines how addInstance() and the destructor will change the reference count of the children.
			/// The \a ref policy is not serialized - serialized shapes will thus always perform ref counting.
		hkpStaticCompoundShape(ReferencePolicy ref = REFERENCE_POLICY_INCREMENT);


			/// Finishing constructor.
		hkpStaticCompoundShape( class hkFinishLoadedObjectFlag flag );

			/// Destructor.
		virtual ~hkpStaticCompoundShape();

			/// Add an instance of a child shape. The returned ID can be used to mutate the instance at any time later.
			/// Returns -1 if the instance could not be added because of lack of shape key space.
		int addInstance( const hkpShape* shape, const hkQsTransform& transform );

			/// Finish construction. Must be called after adding all the instances and before the shape is used.
		void bake();

		//
		// Shape key helpers
		//

			/// Decompose a shape key of this shape into the instance index and the key of that instance's child shape
		HK_FORCE_INLINE void decomposeShapeKey( hkpShapeKey keyIn, int& instanceIdOut, hkpShapeKey& childKeyOut ) const;

			/// Compose a shape key from an instance index and a key of that instance's child shape
		HK_FORCE_INLINE hkpShapeKey composeShapeKey( int instanceId, hkpShapeKey childKey ) const;

			/// Get the number of shape key bits used for the child shape key (the rest is used for the instance index)
		HK_FORCE_INLINE hkInt8 getNumBitsForChildShapeKey() const;

		//
		// Instance access
		//

			/// Read-only access to the instances.
		HK_FORCE_INLINE const hkArray<Instance>& getInstances() const;

			/// Per-instance filter info access. See set/getInstanceFilterInfoMask() for how this filter info is interpreted.
		HK_FORCE_INLINE void setInstanceFilterInfo( int instanceId, hkUint32 filterInfo );
		HK_FORCE_INLINE hkUint32 getInstanceFilterInfo( int instanceId ) const;

			/// Per-instance filter info mask access. The actual filter info returned by getCollisionFilterInfo() is:
			/// ( (child shape key filter info) & (mask) ) | (instance filter info)
		HK_FORCE_INLINE void setInstanceFilterInfoMask( int instanceId, hkUint32 filterInfoMask );
		HK_FORCE_INLINE hkUint32 getInstanceFilterInfoMask( int instanceId ) const;

			/// Per-instance user data access. Not used by the engine.
		HK_FORCE_INLINE void setInstanceUserData( int instanceId, hkUlong userData );
		HK_FORCE_INLINE hkUlong getInstanceUserData( int instanceId ) const;

			/// Per-instance extra info. Used by Destruction.
		HK_FORCE_INLINE void setInstanceExtraInfo( int instanceId, hkUint16 instanceInfo );
		HK_FORCE_INLINE hkUint16 getInstanceExtraInfo( int instanceId ) const;
		HK_FORCE_INLINE const hkArray<hkUint16>& getInstanceExtraInfos() const { return m_instanceExtraInfos; }

		//
		// Disabling
		//

			/// Enable or disable any instance. More efficient than disabling all the keys of the instance.
		HK_FORCE_INLINE void setInstanceEnabled( int instanceId, hkBool32 isEnabled );
		HK_FORCE_INLINE hkBool32 isInstanceEnabled( int instanceId ) const;

			/// Enable or disable any shape key.
			/// NOTE: Disabling lots of keys of large child collections costs performance and memory.
			/// It is recommended to disable at the instance level or use a filtering approach if possible.
		void setShapeKeyEnabled( hkpShapeKey key, hkBool32 isEnabled );
		hkBool32 isShapeKeyEnabled( hkpShapeKey key ) const;

			/// Enable all instances and shape keys, resetting the shape to its original state.
		void enableAllInstancesAndShapeKeys();

		//
		// Queries
		//

			/// Perform an AABB cast on the shape. This is recommended over hkpBvTreeShape:castAabbImpl()
			/// as here the cast shape is used to recompute the AABB in the space of each relevant instance
			/// instead of just transforming (and growing) an initial AABB.
			/// \param shape Shape whose AABB will be cast.
			/// \param transform Initial cast shape transform in the compound shape space.
			/// \param to Final cast shape position in the compound shape space.
			/// \param collector Collector used to gather the cast results.
			/// \param tolerance Tolerance used when (re)calculating the shape AABB.
		void castAabb( const hkpShape* shape, const hkTransform& transform, hkVector4Parameter to, 
					   hkpAabbCastCollector& collector, hkReal tolerance = 0.0f ) const;

		//
		// hkpShape interface
		//


		virtual const hkpShapeContainer* getContainer() const { return this; }

		virtual int calcSizeForSpu( const CalcSizeForSpuInput& input, int spuBufferSizeLeft ) const;

		virtual hkReal getMaximumProjection( const hkVector4& direction ) const;


		virtual void getAabb(const hkTransform& localToWorld, hkReal tolerance, hkAabb& out) const;

		virtual hkBool castRay(const hkpShapeRayCastInput& input, hkpShapeRayCastOutput& results) const;

		virtual void castRayWithCollector(const hkpShapeRayCastInput& input, const hkpCdBody& body, hkpRayHitCollector& collector) const;

		//
		// hkpBvTreeShape interface
		//

		virtual void queryAabb( const hkAabb& aabb, hkArray<hkpShapeKey>& hits ) const;

		HKP_SHAPE_VIRTUAL hkUint32 queryAabbImpl( HKP_SHAPE_VIRTUAL_THIS const hkAabb& aabb, hkpShapeKey* hits, int maxNumKeys ) HKP_SHAPE_VIRTUAL_CONST;
			
		HKP_SHAPE_VIRTUAL void castAabbImpl( HKP_SHAPE_VIRTUAL_THIS const hkAabb& from, hkVector4Parameter to, 
											 hkpAabbCastCollector& collector ) HKP_SHAPE_VIRTUAL_CONST;
		
		//
		// hkpShapeContainer interface
		//

		virtual int getNumChildShapes() const;

		virtual hkpShapeKey getFirstKey() const;

		virtual hkpShapeKey getNextKey( hkpShapeKey oldKey ) const;

		virtual const hkpShape* getChildShape( hkpShapeKey key, hkpShapeBuffer& buffer ) const;

		virtual hkUint32 getCollisionFilterInfo( hkpShapeKey key ) const;

	protected:

		// Shape key configuration
		hkInt8					m_numBitsForChildShapeKey;
		hkInt8					m_referencePolicy;				//+nosave
		hkUint32				m_childShapeKeyMask;			//+nosave

		// Instance data
		hkArray< Instance >		m_instances;					// the transformed child shape instances
		hkArray< hkUint16 >		m_instanceExtraInfos;			// optional extra info per instance (used by Destruction)
		hkpShapeKeyTable		m_disabledLargeShapeKeyTable;	// stores disabled large shape keys (disabled small keys are stored with the instances)

		// Tree data
		HK_ALIGN_REAL( hkUint8 m_tree[NUM_BYTES_FOR_TREE] );	//+overridetype(class hkcdStaticTree::DefaultTreeStorage6)

		friend class hkpStaticCompoundShape_Internals;
};

#include <Physics2012/Internal/Collide/StaticCompound/hkpStaticCompoundShape.inl>

#endif // HKP_STATIC_COMPOUND_SHAPE_H

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
