/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_COLLIDE2_COLLISION_SPHERES_SHAPE_H
#define HK_COLLIDE2_COLLISION_SPHERES_SHAPE_H

#include <Physics2012/Collide/Shape/hkpShape.h>

extern const class hkClass hkpSphereRepShapeClass;

extern const hkClass hkpSphereShapeClass;
class hkSphere;

#define HK_GET_COLLISION_SPHERE_BUFFER_SIZE 64

	/// This interface produces a set of spheres that represent a very simplified version of the objects surface.
	/// Note: This interface's function is used by hkpHeightFieldShape implementations
class hkpSphereRepShape : public hkpShape
{
	public:
		
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SHAPE);
		HK_DECLARE_REFLECTION();
		HKCD_DECLARE_SHAPE_TYPE(hkcdShapeType::SPHERE_REP);

	public:

			/// Empty constructor, to be called by the shape vtable util on SPU
		HK_FORCE_INLINE hkpSphereRepShape() {}
	
			/// Constructor
		hkpSphereRepShape(ShapeType type)
		:	hkpShape(type)
		{}


			/// Serialization constructor
		hkpSphereRepShape( hkFinishLoadedObjectFlag flag )
		:	hkpShape(flag)
		{
			setType(HKCD_SHAPE_TYPE_FROM_CLASS(hkpSphereRepShape));
		}

};

#include <Physics2012/Collide/Shape/HeightField/hkpSphereRepShape.inl>

#endif // HK_COLLIDE2_COLLISION_SPHERES_SHAPE_H

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
