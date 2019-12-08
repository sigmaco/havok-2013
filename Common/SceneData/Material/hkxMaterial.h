/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKSCENEDATA_MATERIAL_HKXMATERIAL_HKCLASS_H
#define HKSCENEDATA_MATERIAL_HKXMATERIAL_HKCLASS_H

#include <Common/SceneData/Attributes/hkxAttributeHolder.h>

extern const class hkClass hkxMaterialPropertyClass;

extern const class hkClass hkxMaterialTextureStageClass;

/// hkxMaterial meta information
extern const class hkClass hkxMaterialClass;

/// A serialization wrapper for the color and texture layers of a mesh section.
class hkxMaterial : public hkxAttributeHolder
{
	//+vtable(true)
	//+version(4)
	public:

		HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_SCENE_DATA );
		HK_DECLARE_REFLECTION();
	
		hkxMaterial() {}
		hkxMaterial(hkFinishLoadedObjectFlag f) : hkxAttributeHolder(f), m_name(f), m_stages(f), m_subMaterials(f), m_extraData(f), m_properties(f) {}
		virtual ~hkxMaterial();

			/// Used by textures to hint at their usage.
		enum TextureType
		{
				/// 
			TEX_UNKNOWN,
				/// 
			TEX_DIFFUSE,
				/// 
			TEX_REFLECTION,
				/// 
			TEX_BUMP,
				/// 
			TEX_NORMAL,
				/// 
			TEX_DISPLACEMENT,
				/// 
			TEX_SPECULAR, // Specular Level map
				/// 
			TEX_SPECULARANDGLOSS, // Specular Level map with the Gloss (power) in the Alpha channel
				///
			TEX_OPACITY, // Opacity (transparency) map. Normally not used, just use the alpha channel in one of the diffuse maps instead.
				/// 
			TEX_EMISSIVE, // Emissive (self illumination) map
				///
			TEX_REFRACTION,
				///	
			TEX_GLOSS, // Specular Power map, normally not used (alpha in specmap quicker)
				///
			TEX_NOTEXPORTED
		};

		enum PropertyKey
		{
			PROPERTY_MTL_TYPE_BLEND = 0x00000001,		///< Property set to non-zero value by blend materials. The value represents the blend map stage

			PROPERTY_MTL_UV_ID_STAGE0	= 0x00000100,	///< Property set to the uvChooser id we must link to. Only exported from Maya and used on re-import
			PROPERTY_MTL_UV_ID_STAGE1	= (PROPERTY_MTL_UV_ID_STAGE0 + 1),
			PROPERTY_MTL_UV_ID_STAGE2	= (PROPERTY_MTL_UV_ID_STAGE0 + 2),
			PROPERTY_MTL_UV_ID_STAGE3	= (PROPERTY_MTL_UV_ID_STAGE0 + 3),
			PROPERTY_MTL_UV_ID_STAGE4	= (PROPERTY_MTL_UV_ID_STAGE0 + 4),
			PROPERTY_MTL_UV_ID_STAGE5	= (PROPERTY_MTL_UV_ID_STAGE0 + 5),
			PROPERTY_MTL_UV_ID_STAGE6	= (PROPERTY_MTL_UV_ID_STAGE0 + 6),
			PROPERTY_MTL_UV_ID_STAGE7	= (PROPERTY_MTL_UV_ID_STAGE0 + 7),

			PROPERTY_MTL_UV_ID_STAGE8	= (PROPERTY_MTL_UV_ID_STAGE0 + 8),
			PROPERTY_MTL_UV_ID_STAGE9	= (PROPERTY_MTL_UV_ID_STAGE0 + 9),
			PROPERTY_MTL_UV_ID_STAGE10	= (PROPERTY_MTL_UV_ID_STAGE0 + 10),
			PROPERTY_MTL_UV_ID_STAGE11	= (PROPERTY_MTL_UV_ID_STAGE0 + 11),
			PROPERTY_MTL_UV_ID_STAGE12	= (PROPERTY_MTL_UV_ID_STAGE0 + 12),
			PROPERTY_MTL_UV_ID_STAGE13	= (PROPERTY_MTL_UV_ID_STAGE0 + 13),
			PROPERTY_MTL_UV_ID_STAGE14	= (PROPERTY_MTL_UV_ID_STAGE0 + 14),
			PROPERTY_MTL_UV_ID_STAGE15	= (PROPERTY_MTL_UV_ID_STAGE0 + 15),
			PROPERTY_MTL_UV_ID_STAGE_MAX= (PROPERTY_MTL_UV_ID_STAGE0 + 16),

		};
		
			/// Used by textures to hint at what conventions they are assuming for mapping.
		enum UVMappingAlgorithm
		{
				/// assumes pivot being in top-left for scale and offset, center for rotations, positive rotation is counter-clockwise
			UVMA_SRT          = 0,  
				/// assumes pivot being in top-left for scale and offset, center for rotations, positive rotation is counter-clockwise
			UVMA_TRS          = 1,  
				/// assumes pivot being in center for scale, rotation and offset, positive rotation is clockwise, offsets are negated, order is SRT
			UVMA_3DSMAX_STYLE = 2,  
				/// assumes pivot being in top-left for scale and offset, center for rotations, positive rotation is clockwise, order is RST
			UVMA_MAYA_STYLE   = 3   
		};

			/// The information needed to texture an object in the correct way. A stage contains
			/// just a texture map (one of two types, so a hkReferencedObject*) and some hint information.
		struct TextureStage
		{
			//+version(1)
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_SCENE_DATA, hkxMaterial::TextureStage );
			HK_DECLARE_REFLECTION();

			TextureStage() : m_usageHint(TEX_UNKNOWN), m_tcoordChannel(-1) {}
			TextureStage(hkFinishLoadedObjectFlag f) : m_texture(f) {}

				/// The texture map. Usually an inplace or file texture pointer
			hkRefVariant m_texture;
			
				/// What the texture is meant for. Is it a normal map etc. An int so not assumed to
				/// be one of the default above enums.
			hkEnum< TextureType, hkInt32 > m_usageHint;

				/// Which of the texture coords it meant to use in the vertex buffer. Starts at 0. -1 for unknown.
			hkInt32 m_tcoordChannel; //+default(-1)
		};

			/// Material property
		struct Property
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_SCENE_DATA, hkxMaterial::Property );
			HK_DECLARE_REFLECTION();

			Property() {}
			Property(hkFinishLoadedObjectFlag f) {}

				/// Property key
			hkUint32 m_key;

				/// Property value
			hkUint32 m_value;
		};

		//Enumeration type for the transparency setting
		//of the Vision engine
		enum Transparency
		{
			transp_none = 0,
			transp_alpha = 2,
			transp_additive = 3,
			transp_colorkey = 4,
			transp_subtractive = 9
		};
		
		void sortTextureStageOrder();

			/// Adds a property to the material
		void addProperty(int key, int value);

			/// Returns a property value
		hkUint32 getProperty(int key);

			/// Returns true if the material has the given property
		hkBool hasProperty(int key);
		
		//
		// Members
		//
	public:
		
			/// The name of the material as seen in the modeler
		hkStringPtr m_name;

			/// Ordered list of textures. Stages (or samplers) in a graphics engine.
		hkArray<struct hkxMaterial::TextureStage> m_stages;
		
			/// Diffuse RGBA == the vector XYZW
		hkVector4 m_diffuseColor;
		
			/// Ambient RGB == the vector XYZ
		hkVector4 m_ambientColor;
		
			/// Specular RGB == the vector XYZ. Specular Power (shininess in OGL) is the W
			/// (0..20..100 are normal for the power)
		hkVector4 m_specularColor;
		
			/// Emissive RGB == the vector XYZ
		hkVector4 m_emissiveColor;
		
			/// Sub materials. Assumes a ref, will remove ref in dtor
		hkArray< hkRefPtr<hkxMaterial> > m_subMaterials;
		
			/// extra material info such as a shader (FX file or whatever, usually a hkxMaterialEffect if it comes from our exporters, or a hkxMaterialShaderSet if specific single pass shader sets)
		hkRefVariant m_extraData;

      // material mapping information (used by Vision etc)
    hkReal m_uvMapScale[2];  //+default(1.f,1.f)
    hkReal m_uvMapOffset[2]; //+default(0.f,0.f) 
    hkReal m_uvMapRotation;  //+default(0.f)
    hkEnum<UVMappingAlgorithm, hkUint32> m_uvMapAlgorithm; //+default(2)

    // Specular multiplier for material for the Vision engine
    hkReal m_specularMultiplier;

    //Specular exponent for materials for the Vision engine
    hkReal m_specularExponent;

		//Transparency setting for materials in the Vision engine
		hkEnum<Transparency, hkUint8> m_transparency;

	protected:

			/// Material properties
		hkArray<struct Property>	m_properties;
};

#endif // HKSCENEDATA_MATERIAL_HKXMATERIAL_HKCLASS_H

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
