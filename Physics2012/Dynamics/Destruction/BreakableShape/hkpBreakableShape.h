/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_DYNAMICS2_BREAKABLE_SHAPE_H
#define HK_DYNAMICS2_BREAKABLE_SHAPE_H

#include <Physics2012/Dynamics/Destruction/BreakableMaterial/hkpBreakableMaterial.h>
#include <Physics2012/Dynamics/Destruction/BreakableMaterial/hkpBreakableMaterialUtil.h>

	//
	///	Base class for a Destruction breakable shape. Contains a physics shape and a material that controls how the shape handles impacts (i.e. breaks / deforms).
class hkpBreakableShape : public hkReferencedObject
{
	// +version(1)

	public:

		HK_DECLARE_REFLECTION();
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE_CLASS);

	public:

			/// Constructor
		HK_FORCE_INLINE hkpBreakableShape(const hkcdShape* physicsShape = HK_NULL, hkpBreakableMaterial* material = HK_NULL)
		:	hkReferencedObject()
		,	m_physicsShape(physicsShape)
		,	m_material(material)
		{}

			/// Serialization constructor
		HK_FORCE_INLINE hkpBreakableShape(class hkFinishLoadedObjectFlag flag)
		:	hkReferencedObject(flag)
		,	m_physicsShape(flag)
		,	m_material(flag)
		{}

			/// Returns the physics shape.
		HK_FORCE_INLINE const hkcdShape* getPhysicsShape() const { return m_physicsShape.val(); }

			/// Returns the material.
		HK_FORCE_INLINE const hkpBreakableMaterial* getMaterial() const { return m_material.val(); }

			/// Returns the material.
		HK_FORCE_INLINE hkpBreakableMaterial* getMaterial() { return m_material.val(); }

			/// Sets the shape.
		HK_FORCE_INLINE void setPhysicsShape(const hkcdShape* newPhysicsShape) { m_physicsShape = newPhysicsShape; }

			/// Sets the material.
		HK_FORCE_INLINE void setMaterial(hkpBreakableMaterial* newMaterial) { m_material = newMaterial; }

			/// Computes the breaking threshold for the given shape key. Returns true if the shape key is breakable, false otherwise.
		static HK_FORCE_INLINE hkBool HK_CALL getShapeKeyStrength(const hkpBreakableShape* rootBreakableShape, const hkpBreakableMaterial* rootMaterial, hkpShapeKey shapeKey, hkUFloat8& shapeKeyStrengthOut);

	protected:

			/// The physics shape
		hkRefPtr<const hkcdShape> m_physicsShape;

			/// The material controlling the way the shape breaks
		hkRefPtr<hkpBreakableMaterial> m_material;
};

#include <Physics2012/Dynamics/Destruction/BreakableShape/hkpBreakableShape.inl>

#endif	//	HK_DYNAMICS2_BREAKABLE_SHAPE_H

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
