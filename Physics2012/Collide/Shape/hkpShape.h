/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_SHAPE_H
#define HKP_SHAPE_H

#include <Common/Base/Types/Physics/ContactPoint/hkContactPoint.h>

#include <Geometry/Collide/Util/ShapeVirtualTable/hkcdShapeVirtualTableUtil.h>
#include <Geometry/Internal/Types/hkcdVertex.h>

#include <Physics2012/Collide/Shape/hkpShapeBase.h>
#include <Physics2012/Collide/Shape/hkpShapeType.h>


#define HK_INVALID_SHAPE_KEY 0xffffffff
#define HK_INVALID_VERTEX_ID 0xffff

#	define HKP_SHAPE_VIRTUAL					virtual
#	define HKP_SHAPE_VIRTUAL_CONST				const
#	define HKP_SHAPE_VIRTUAL_THIS 
#	define HKP_SHAPE_VIRTUAL_THIS2 
#	define HK_GET_THIS_PTR						this
#	define HK_DECLARE_GET_SIZE_FOR_SPU(CLASS)	int getSize() const { return sizeof(*this); }; \
												int calcSizeForSpu(const CalcSizeForSpuInput& input, int spuBufferSizeLeft) const { return sizeof(*this); }
#	define HK_SHAPE_CONTAINER hkpShapeContainer

#define HKP_PATCH_CONST_SHAPE_VTABLE(shapePtr)	HKCD_PATCH_SHAPE_VTABLE( (const_cast<hkpShape*>(shapePtr)) )


extern const hkClass hkpShapeClass;


	/// The base class for narrowphase collision detection objects.
	/// All narrowphase collision detection is performed between pairs of hkpShape objects by creating appropriate hkpCollisionAgent objects.
	/// An hkpShape can be a simple shape such as a box or sphere, a shape with additional transform information,
	/// or a compound shape made up of simpler hkShapes. hkpShape instances can be shared within or even between
	/// rigid bodies. See the hkpShape subclasses for more details.
class hkpShape : public hkpShapeBase
{
	// +version(1)

	public:

		HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_SHAPE );
		HK_DECLARE_REFLECTION();
		HKCD_DECLARE_SHAPE_TYPE( hkcdShapeType::INVALID );

			/// Input structure for calcSizeForSpu()
		struct CalcSizeForSpuInput
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_COLLIDE, hkpShape::CalcSizeForSpuInput );

			bool m_midphaseAgent3Registered;
			bool m_isFixedOrKeyframed;
			bool m_hasDynamicMotionSaved;
		};

	public:

			/// Empty constructor, to be called by the shape vtable util on SPU.
		HK_FORCE_INLINE hkpShape() {}

			/// Sets the type to the specified type.
			/// Sets the user data to 0.
		HK_FORCE_INLINE hkpShape( ShapeType type );


			/// Serialization constructor
		hkpShape( class hkFinishLoadedObjectFlag flag );

			/// Query if the shape supports the container interface.
			/// Returns a pointer to the interface if the shape has one or more child shapes.
			/// Otherwise returns null.
		virtual const hkpShapeContainer* getContainer() const { return HK_NULL; }

			/// Support for creating bounding volume hierarchies of shapes.
			/// This function returns the maximal extent of a shape along a given direction. The result will be scaled 
			/// by the direction's length.
			/// It is not the same as hkpConvexShape::getSupportingVertex, because the extent does not have to be exact, 
			/// it just has to at least contain the shape. It is for the purposes of creating bounding volumes around 
			/// the shape ( mid-phase ) rather than exact collision detection (narrow-phase).
			/// The default implementation of this function uses the AABB of the shape. For custom shapes, you can get 
			/// a better fit.
		virtual hkReal getMaximumProjection( const hkVector4& direction ) const;

			/// Returns the size of the shape class. The default implementation returns -1 which will force the shape onto the PPU.
		virtual int calcSizeForSpu( const CalcSizeForSpuInput& input, int spuBufferSizeLeft ) const;


			/// Get the user data for the shape (initialized to 0).
		inline hkUlong getUserData() const;

			/// Set the user data of the shape. This is a real user data and not used by the engine otherwise.
		inline void setUserData( hkUlong data );

		//
		// hkpShapeBase interface
		//

			/// Default implementation of castRayBundle() that does 4 single raycasts.
		virtual hkVector4Comparison castRayBundle(const hkpShapeRayBundleCastInput& input, hkpShapeRayBundleCastOutput& output, hkVector4ComparisonParameter mask) const;

	public:

		hkUlong m_userData;
};


	/// A pair of shape keys, with sorting criteria
class hkpShapeKeyPair
{
public:
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CDINFO, hkpShapeKeyPair );

	hkpShapeKey m_shapeKeyA; // only used by nm machine
	hkpShapeKey m_shapeKeyB; // used by 1n & nm machines

	HK_FORCE_INLINE bool operator==(const hkpShapeKeyPair& p1) const { return m_shapeKeyB == p1.m_shapeKeyB && m_shapeKeyA == p1.m_shapeKeyA; }
	HK_FORCE_INLINE bool operator< (const hkpShapeKeyPair& p1) const { return (m_shapeKeyA < p1.m_shapeKeyA) || (m_shapeKeyA == p1.m_shapeKeyA && m_shapeKeyB < p1.m_shapeKeyB); }
};


	/// Interface for an object capable of modifying a shape's internal data (i.e., alter the vertices of a convex vertices shape)
class hkpShapeModifier
{
	//+hk.MemoryTracker(ignore=True)
	public:

		virtual ~hkpShapeModifier()	{}

			/// This function will be called from hkWorldOperation::WORLD_OBJECT_UPDATE_SHAPE if the shape to be updated has a valid modifier
		virtual void modifyShape(hkpShape* shapeInOut) = 0;
};

#include <Physics2012/Collide/Shape/hkpShape.inl>

#endif // HKP_SHAPE_H

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
