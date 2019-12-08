/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_DYNAMICS2_SIMPLE_BREAKABLE_MATERIAL_H
#define HK_DYNAMICS2_SIMPLE_BREAKABLE_MATERIAL_H

#include <Physics2012/Dynamics/Destruction/BreakableMaterial/hkpBreakableMaterial.h>

extern const hkClass hkpSimpleBreakableMaterialClass;

	//
	/// Simple breakable material with no sub-materials
class hkpSimpleBreakableMaterial : public hkpBreakableMaterial
{
	public:

		HK_DECLARE_REFLECTION();
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_DESTRUCTION);

		enum
		{
			DEFAULT_FLAGS = hkpBreakableMaterial::MATERIAL_TYPE_SIMPLE |
							hkpBreakableMaterial::MATERIAL_MAPPING_NONE,
		};

	public:

			/// Constructor
		hkpSimpleBreakableMaterial(hkReal strength = 0.0f);

			/// Serialization constructor
		hkpSimpleBreakableMaterial(class hkFinishLoadedObjectFlag flag);

			/// Copy constructor
		hkpSimpleBreakableMaterial(const hkpSimpleBreakableMaterial& other);

	public:


			/// Returns the class type
		virtual const hkClass* getClassType() const;

			/// Clones the given material
		virtual hkpBreakableMaterial* duplicate();

			/// Sets the default mapping
		virtual void setDefaultMapping();

			/// Returns the material set on the given shape key
		virtual hkpBreakableMaterial* getShapeKeyMaterial(const hkcdShape* shapePpu, hkpShapeKey shapeKey) const;

};

#endif	//	HK_DYNAMICS2_SIMPLE_BREAKABLE_MATERIAL_H

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
