/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_DYNAMICS2_BREAKABLE_MATERIAL_H
#define HK_DYNAMICS2_BREAKABLE_MATERIAL_H

#include <Common/Base/Types/Properties/hkRefCountedProperties.h>

	//
	/// A material is associated with a (part of a) breakable shape and stores its strength (i.e. the maximum impulse the solver can apply at a contact
	/// point on the breakable shape) to prevent inter-penetrations.
class hkpBreakableMaterial : public hkReferencedObject
{
	public:

		HK_DECLARE_REFLECTION();
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_DESTRUCTION_2012);

		friend class hkpBreakableMaterialUtil;

	public:

			/// Material types and flags
		enum
		{
			// Types
			MATERIAL_TYPE_UNKNOWN				=	0x00000000,	///< Unknown material type
			MATERIAL_TYPE_SIMPLE				=	0x00000001,	///< Single material type, no sub-materials
			MATERIAL_TYPE_MULTI					=	0x00000002,	///< Multi-material, potentially has sub-materials
			MATERIAL_TYPE_MASK					=	0x0000000F,	///< Masks only the type bits in m_typeAndFlags

			// Mapping (from sub-shape id i.e. hkpShapeKey to hkpBreakableMaterial*)
			MATERIAL_MAPPING_UNKNOWN			=	0x00000000,	///< Mapping was not defined
			MATERIAL_MAPPING_NONE				=	0x00000010,	///< The mapping is inexistent, the returned material is always == this
			MATERIAL_MAPPING_STATIC_COMPOUND	=	0x00000020,	///< The mapping works on hkpStaticCompoundShapes
			MATERIAL_MAPPING_LIST_SHAPE			=	0x00000030,	///< The mapping works on hkpListShapes
			MATERIAL_MAPPING_EMS				=	0x00000040,	///< The mapping works on hkpExtendedMeshShapes
			MATERIAL_MAPPING_MASK				=	0x000000F0,	///< Masks only the mapping bits in m_typeAndFlags

			// Material extra data
			MATERIAL_EXTRA_DATA_SHIFT			=	8,
			MATERIAL_EXTRA_DATA_MASK			=	0x0000FF00,	///< Extra 8 bits a material can use to save specific data.

			// Flags
			MATERIAL_FLAG_UNBREAKABLE			=	0x80000000,	///< The material is unbreakable
		};

			/// Types
		typedef hkInt16									MaterialId;
		typedef hkRefCountedProperties					Properties;
		typedef hkRefCountedProperties::PropertyKey		PropertyKey;

			/// Constants
		enum
		{
			INVALID_MATERIAL_ID	=	(MaterialId)(-1),
		};

	public:

			/// Shape key collector interface.
		class ShapeKeyCollector
		{
			public:

				HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_DESTRUCTION_2012, hkpBreakableMaterial::ShapeKeyCollector);

			public:
					
					/// Constructor
				HK_FORCE_INLINE ShapeKeyCollector()
				{}

					/// Destructor
				virtual ~ShapeKeyCollector()
				{}

					/// Called to add a shape key
				virtual void addShapeKey(hkpShapeKey shapeKey) = 0;

					/// Called to add multiple shape keys
				virtual void addShapeKeyBatch(const hkpShapeKey* shapeKeys, int numShapeKeys);

					/// Called to add a contiguous range of shape keys, i.e. from shapeKeyBase to shapeKeyBase + n - 1
				virtual void addContiguousShapeKeyRange(hkpShapeKey baseShapeKey, int numShapeKeys);
		};

	public:

			/// Constructor
		HK_FORCE_INLINE hkpBreakableMaterial(int typeAndFlags, hkReal strength)
		:	hkReferencedObject()
		,	m_strength(strength)
		,	m_typeAndFlags(typeAndFlags)
		,	m_properties(HK_NULL)
		{}

			/// Copy constructor
		HK_FORCE_INLINE hkpBreakableMaterial(const hkpBreakableMaterial& other)
		:	hkReferencedObject(other)
		,	m_strength(other.m_strength)
		,	m_typeAndFlags(other.m_typeAndFlags)
		,	m_properties(other.m_properties)
		{}

			/// Serialization constructor
		HK_FORCE_INLINE hkpBreakableMaterial(class hkFinishLoadedObjectFlag flag)
		:	hkReferencedObject(flag)
		{}

		/// Destructor
		virtual ~hkpBreakableMaterial();

	public:

			/// Returns the material type
		HK_FORCE_INLINE int getType() const { return (m_typeAndFlags & MATERIAL_TYPE_MASK); }

			/// Returns the mapping type
		HK_FORCE_INLINE int getMapping() const { return (m_typeAndFlags & MATERIAL_MAPPING_MASK); }

			/// Sets the mapping type
		HK_FORCE_INLINE void setMapping(hkUint32 newMapping) { m_typeAndFlags = (m_typeAndFlags & (~MATERIAL_MAPPING_MASK)) | newMapping; }

			/// Returns true if the material is breakable
		HK_FORCE_INLINE bool isBreakable() const { return !(m_typeAndFlags & MATERIAL_FLAG_UNBREAKABLE); }

			/// Returns the strength of the material
		HK_FORCE_INLINE hkReal getMaterialStrength() const { return m_strength; }

			/// Sets the material as unbreakable
		HK_FORCE_INLINE void setUnbreakable() { m_typeAndFlags |= MATERIAL_FLAG_UNBREAKABLE; }

			/// Sets the material as breakable
		HK_FORCE_INLINE void setBreakable() { m_typeAndFlags &= (~MATERIAL_FLAG_UNBREAKABLE); }

			/// Sets the material strength
		HK_FORCE_INLINE void setMaterialStrength(hkReal newStrength);

			/// Sets the material extra data
		HK_FORCE_INLINE void setExtraData(hkUint8 extraData);

			/// Returns the material extra data
		HK_FORCE_INLINE hkUint8 getExtraData() const;

			/// Returns the encoded material strength. For internal use only!
		HK_FORCE_INLINE void getEncodedMaterialStrength(hkUFloat8& strengthOut) const;

	public:
	

			/// Creates the inverse mapping
		virtual void createInverseMapping(const hkcdShape* shape) {}

			/// Clones the given material
		virtual hkpBreakableMaterial* duplicate() = 0;

			/// Sets the default mapping
		virtual void setDefaultMapping();

			/// Returns the index of the sub-material belonging to the given sub-shape. Default implementation returns an invalid material Id.
		virtual MaterialId getSubShapeMaterialIndex(const hkcdShape* rootShape, hkUint32 subShapeId) const { return INVALID_MATERIAL_ID; }

			/// Returns the material set on the given shape key
		virtual hkpBreakableMaterial* getShapeKeyMaterial(const hkcdShape* shapePpu, hkpShapeKey subShapeKey) const { return HK_NULL; }

			/// Converts a shape key into a sub-shape id the material is working with. For instance, in the case of hkpStaticCompoundShapes
			/// the subShapeId is the instance index.
		virtual hkUint32 convertShapeKeyToSubShapeId(hkpShapeKey shapeKey) const { return shapeKey; }

			/// Converts a set of shape keys into their corresponding sub-shape ids in-place
		virtual void convertShapeKeysToSubShapeIds(hkArray<hkpShapeKey>& shapeKeysInOut) const {}

			/// Disables a set of sub-shapes based on their sub-material Id
		virtual void disableSubShapes(hkcdShape* rootShape, const MaterialId* subMaterialIndices, int numSubMaterialIndices) {}

			/// Returns the number of sub-materials or zero if the material does not support sub-materials
		virtual int getNumSubMaterials() const { return 0; }

			/// Collects the shape keys belonging to the given sub-shape
		virtual void getShapeKeysForSubShapes(const hkcdShape* rootShape, const hkUint32* subShapeIdPtr, int numSubShapeIds, ShapeKeyCollector* collector) const {}

			/// Appends the sub-material indices set on the given sub-shapes to the given array
		virtual void getSubShapeMaterialIndices(const hkcdShape* rootShape, const hkArray<hkUint32>& subShapeIdsIn, hkArray<MaterialId>& subMaterialsOut) const {}

			/// Ensures the material is capable of storing custom properties
		HK_FORCE_INLINE void ensurePropertiesExist();

			/// Removes the custom properties
		HK_FORCE_INLINE void removeProperties();

			/// Gets the material properties. Read / write.
		HK_FORCE_INLINE Properties* getProperties();

			/// Gets the material properties. Read-only.
		HK_FORCE_INLINE const Properties* getProperties() const;

			/// Shortcut for retrieving a given material property
		HK_FORCE_INLINE hkReferencedObject* getProperty(PropertyKey propertyKey);
		
			/// Shortcut for retrieving a given material property
		HK_FORCE_INLINE const hkReferencedObject* getProperty(PropertyKey propertyKey) const;

	public:

			/// The maximum impulse the solver can apply to maintain the integrity of the shape having this
			/// material. This is equivalent to the breakable shape strength and it acts as an override value.
		hkReal m_strength;

			/// Material type and flags
		int m_typeAndFlags;

	protected:

			/// Material properties
		Properties* m_properties;
};

#include <Physics2012/Dynamics/Destruction/BreakableMaterial/hkpBreakableMaterial.inl>

#endif	//	HK_DYNAMICS2_BREAKABLE_MATERIAL_H

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
