/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_COLLIDE2_LIST_SHAPE_H
#define HK_COLLIDE2_LIST_SHAPE_H

#include <Common/Base/Algorithm/Collide/1AxisSweep/hk1AxisSweep.h>

#include <Physics2012/Collide/Shape/Compound/Collection/hkpShapeCollection.h>
#include <Common/Base/Types/Geometry/Aabb/hkAabbUtil.h>

extern const class hkClass hkpListShapeChildInfoClass;

extern const hkClass hkpListShapeClass;

class hkBitField;
struct hkAabbUint32;
struct hkpCollisionInput;

/// A simple static list of hkpShapes. You can use this shape class to create compound bodies.
/// A list shape can hold a mix of different shape types e.g., an ice cream cone could be made
/// from a list shape containing a sphere for the ice cream and a convex vertices shape
/// for the wafer cone.
/// If your list shape contains many subshapes, consider using a hkpBvTreeShape for faster access
class hkpListShape : public hkpShapeCollection
{
	public:
		
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SHAPE);
		HK_DECLARE_REFLECTION();
		HKCD_DECLARE_SHAPE_TYPE(hkcdShapeType::LIST);

	public:

		enum { MAX_CHILDREN_FOR_SPU_MIDPHASE = 252 };

		struct ChildInfo
		{
			//+version(1)
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_COLLIDE, hkpListShape::ChildInfo );
			HK_DECLARE_REFLECTION();
			HK_ALIGN16(const hkpShape* m_shape);	// we need this because all the child infos might not fit into a cacheline
			hkUint32 m_collisionFilterInfo;
			hkUint16 m_shapeInfo;					///< Data used by Destruction, stores the sub-material Id.
			mutable hkInt16 m_shapeSize; // +nosave
			mutable int m_numChildShapes; // +nosave	
		};

			/// Flags for controlling list shape algorithms
		enum ListShapeFlags
		{
			ALL_FLAGS_CLEAR = 0,							///< No flags set
			DISABLE_SPU_CACHE_FOR_LIST_CHILD_INFO = 1<<0	///< A cache is used for the childInfo array when accessing child shapes on SPUs. Disable the cache if you mutate list shapes on the PPU while collision detection is running on SPU.
		};

	public:

		/// Empty constructor, to be called by the shape vtable util on SPU
		HK_FORCE_INLINE hkpListShape()
		{}

			/// Constructs a list shape with an array of pointers to shapes.
			/// Note: The hkpShapeContainer::ReferencePolicy is only used for the constructor, the destructor will still always decrement the childs reference
		hkpListShape( const hkpShape*const* shapeArray, int numShapes, hkpShapeContainer::ReferencePolicy ref = hkpShapeContainer::REFERENCE_POLICY_INCREMENT );


		hkpListShape( class hkFinishLoadedObjectFlag flag );


			/// The destructor removes references to child shapes.
		~hkpListShape();

	public:

			// hkpShapeBase interface implementation.
		virtual const hkpShape* getChildShape(hkpShapeKey key, hkpShapeBuffer& buffer) const;

			// hkpShapeBase interface implementation.
		virtual hkUint32 getCollisionFilterInfo(hkpShapeKey key) const;

			// hkpShapeBase interface implementation.
		virtual void getAabb(const hkTransform& localToWorld, hkReal tolerance, hkAabb& out) const;

			// hkpShapeBase interface implementation.
		virtual hkBool castRay(const hkpShapeRayCastInput& input, hkpShapeRayCastOutput& results) const;

			// hkpShapeBase interface implementation.
		virtual void castRayWithCollector(const hkpShapeRayCastInput& input, const hkpCdBody& cdBody, hkpRayHitCollector& collector) const;

	public:

			/// Sets the shape info at the given shape key
		HK_FORCE_INLINE void setShapeInfo(hkpShapeKey shapeKey, hkUint16 newShapeInfo);

			/// Gets the shape info at the given shape key
		HK_FORCE_INLINE hkUint16 getShapeInfo(hkpShapeKey shapeKey) const;

			/// Returns the i'th child shape.
		inline const hkpShape* getChildShapeInl(int i) const { return m_childInfo[i].m_shape; }

			/// Call this whenever your underlying child shapes moves or increases its AABB.
		void recalcAabbExtents();

			/// Call this whenever your underlying child shapes moves or increases its AABB.
			/// Also returns the AABB.
		void recalcAabbExtents( hkAabb& aabbOut );

			/// Allows for quickly disabling a child shape.
			/// Warning: you also have to invalidate the corresponding cached AABB in the hkpCollidable::m_boundingVolumeData::m_childShapeAabbs.
			/// You can use the hkpBreakOffPartsUtil::removeKeysFromListShape() to do this for you.
		void disableChild( hkpShapeKey index );

			/// Allows for quickly enabling a child shape.
		void enableChild( hkpShapeKey index );

			/// sets the enabled children by using a bitfield. All other items will be disabled.
		void setEnabledChildren( const hkBitField& enabledChildren );

			/// Check whether a child is enabled.
		HK_FORCE_INLINE hkBool32 isChildEnabled( hkpShapeKey index ) const
		{
			HK_ASSERT2(0xad808208, index < hkUint32(m_childInfo.getSize()), "hkpListShape child index out of bounds");
			if ( index < MAX_DISABLED_CHILDREN )
			{
				return m_enabledChildren[ index>>5 ] & (1<<(index&0x1f));
			}
			return true;
		}

			/// Sets the collisionFilterInfo for a given index.
		void setCollisionFilterInfo( hkpShapeKey index, hkUint32 filterInfo );

		//
		// hkpShapeCollection interface
		//

			// hkpShapeCollection interface implementation.
		inline virtual int getNumChildShapes() const { return m_childInfo.getSize() - m_numDisabledChildren; }
		
			/// Get the first child shape key.
		inline virtual hkpShapeKey getFirstKey() const { return hkpListShape::getNextKey( hkpShapeKey(-1) ); }

			/// Get the next child shape key.
		inline virtual hkpShapeKey getNextKey( hkpShapeKey key ) const 
		{
			for ( int i = key+1; i < m_childInfo.getSize(); i++ )
			{
				if (isChildEnabled( i ))
				{
					return hkpShapeKey(i);
				}
			}
			return HK_INVALID_SHAPE_KEY;
		}


			//	hkpShape interface implementation.
		virtual int calcSizeForSpu(const CalcSizeForSpuInput& input, int spuBufferSizeLeft) const;


		//
		// SPU registration
		//

	public:


		inline int getNumAabbsForSharedBufferForAabbsAndChildInfos() const
		{
			int maxByteSize = hkpListShape::getNumChildShapes() * sizeof(hkAabbUint32) + (m_childInfo.getSize()-hkpListShape::getNumChildShapes())*sizeof(ChildInfo);
			int maxNumAabbs = (maxByteSize + sizeof(hkAabbUint32) - 1) / sizeof(hkAabbUint32) + 1;
			return maxNumAabbs;
		}

	public:

		friend class hkpListAgent;

		hkArray<struct ChildInfo>	m_childInfo;

		hkUint16 m_flags;				///< Flags for controlling list shape algorithms, see hkListShape::ListShapeFlags
		hkUint16 m_numDisabledChildren; ///< the number of disabled children

		hkVector4					m_aabbHalfExtents;
		hkVector4					m_aabbCenter;

			// if one of the bits is set, the child is disabled
		enum { MAX_DISABLED_CHILDREN = 256 };

		hkUint32 m_enabledChildren[ 8 ]; // [MAX_DISABLED_CHILDREN/32]

	protected:

		void setShapes( const hkpShape*const* shapeArray, int numShapes, const hkUint32* filterInfoArray = HK_NULL, hkpShapeContainer::ReferencePolicy ref = hkpShapeContainer::REFERENCE_POLICY_INCREMENT );
};

#	define HK_ACCESS_COLLECTION_METHOD(obj, func) obj->func

#include <Physics2012/Collide/Shape/Compound/Collection/List/hkpListShape.inl>

#endif // HK_COLLIDE2_LIST_SHAPE_H

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
