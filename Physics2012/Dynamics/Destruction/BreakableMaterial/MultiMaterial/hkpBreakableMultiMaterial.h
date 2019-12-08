/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_DYNAMICS2_BREAKABLE_MULTI_MATERIAL_H
#define HK_DYNAMICS2_BREAKABLE_MULTI_MATERIAL_H

#include <Physics2012/Collide/Shape/Compound/Collection/List/hkpListShape.h>
#include <Physics2012/Dynamics/Destruction/BreakableMaterial/hkpBreakableMaterial.h>

extern const hkClass hkpBreakableMultiMaterialClass;

	//
	/// Base class for a multi-material. By default, this has no mapping between the shape keys and the sub-materials.
class hkpBreakableMultiMaterial : public hkpBreakableMaterial
{
	public:

		HK_DECLARE_REFLECTION();
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_DESTRUCTION_2012);

		friend class hkpBreakableMaterialUtil;

		enum
		{
			DEFAULT_FLAGS = hkpBreakableMaterial::MATERIAL_TYPE_MULTI		|
							hkpBreakableMaterial::MATERIAL_MAPPING_UNKNOWN,
		};

	protected:

			/// Constructor
		hkpBreakableMultiMaterial(const hkArray<hkpBreakableMaterial*>& subMaterials, hkReal strength = 0.0f);
			
			/// Copy constructor
		hkpBreakableMultiMaterial(const hkpBreakableMultiMaterial& other);

	public:

			/// Serialization constructor
		hkpBreakableMultiMaterial(class hkFinishLoadedObjectFlag flag);

	public:

			/// Inverse mapping descriptor
		struct InverseMappingDescriptor
		{
			public:

				HK_DECLARE_REFLECTION();
				HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_DESTRUCTION_2012, hkpBreakableMultiMaterial::InverseMappingDescriptor);

			public:

					/// Constructor
				HK_FORCE_INLINE InverseMappingDescriptor();

			public:

					/// Offset of the first sub-shape id in the InverseMapping buffer
				hkUint16 m_offset;

					/// Number of sub-shape ids in the InverseMapping buffer
				hkUint16 m_numKeys;
		};

			/// Inverse mapping (from sub-material to sub-shape ids, i.e. one to many)
		struct InverseMapping : public hkReferencedObject
		{
			public:

				HK_DECLARE_REFLECTION();
				HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_DESTRUCTION_2012);

			public:

					/// Constructor
				InverseMapping();

					/// Serialization constructor
				InverseMapping(class hkFinishLoadedObjectFlag flag);

			public:

					/// Array of inverse mapping descriptors, one for each material
				hkArray<InverseMappingDescriptor> m_descriptors;

					/// Array of sub-shape ids
				hkArray<hkUint32> m_subShapeIds;
		};

	public:

			/// Returns the i-th sub-material. The returned pointer is on PPU.
		HK_FORCE_INLINE const hkpBreakableMaterial* getSubMaterial(MaterialId subMaterialIndex) const;


			/// Returns the class type
		virtual const hkClass* getClassType() const;

			/// Creates the inverse mapping
		virtual void createInverseMapping(const hkcdShape* shape);

			/// Returns the number of sub-materials or zero if the material does not support sub-materials
		virtual int getNumSubMaterials() const;

			/// Returns the index of the given material in the m_subMaterials array. If the material is not found, the function returns -1.
		int findSubMaterial(const hkpBreakableMaterial* mtl) const;

			/// Sets the i-th sub-material
		HK_FORCE_INLINE void setSubMaterial(MaterialId subMaterialIndex, hkpBreakableMaterial* subMaterial);
		
			/// Returns the inverse mapping
		HK_FORCE_INLINE const InverseMapping* getInverseMapping() const;

			/// Clears the inverse mapping
		HK_FORCE_INLINE void clearInverseMapping();


	protected:

			/// Array of sub-materials
		hkArray< hkRefPtr<hkpBreakableMaterial> > m_subMaterials;

			/// Inverse mapping (can be NULL)
		hkRefPtr<InverseMapping> m_inverseMapping;
};

#include <Physics2012/Dynamics/Destruction/BreakableMaterial/MultiMaterial/hkpBreakableMultiMaterial.inl>

#endif	//	HK_DYNAMICS2_BREAKABLE_MULTI_MATERIAL_H

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
