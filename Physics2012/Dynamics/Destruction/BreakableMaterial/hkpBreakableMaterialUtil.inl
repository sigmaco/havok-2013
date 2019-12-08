/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#include <Physics2012/Dynamics/Destruction/Utilities/hkpDestructionSpuUtil.h>

//
//	Called to download the shape from Ppu to Spu

inline void HK_CALL hkpBreakableMaterialUtil::downloadShapeOnSpu(const hkcdShape* shapePpu, hkcdShape*& shapeSpu)
{
	hkcdShape* rootShapePpu = const_cast<hkcdShape*>(shapePpu);
	bool shapeIsMopp = true;
	do
	{
		HK_DOWNLOAD_DESTRUCTION_PTR_TO_SPU(shapeSpu, rootShapePpu, MAX_SHAPE_SIZE);
		HKCD_PATCH_SHAPE_VTABLE( const_cast<hkcdShape*>(shapeSpu) );

		shapeIsMopp = ( shapeSpu->getType() == hkcdShapeType::MOPP );
		if ( shapeIsMopp )
		{
			// The extended mesh shape is the child of the MOPP. Download it on SPU.
			hkpMoppBvTreeShape* moppSpu = reinterpret_cast<hkpMoppBvTreeShape*>(shapeSpu);
			rootShapePpu = const_cast<hkcdShape*>((const hkcdShape*)moppSpu->getChild());
		}
	} while ( shapeIsMopp );
}

//
//	Make sure the offset of shape info has a known value



//
//	Returns the material strength set on the given sub-shape. Returns true if the material is breakable, false otherwise.

inline hkBool HK_CALL hkpBreakableMaterialUtil::getSubShapeMaterialStrength(const hkpBreakableMaterial* materialSpu, const hkcdShape* shapePpu, hkpShapeKey shapeKey, hkUFloat8& materialStrengthOut)
{
	hkpBreakableMaterial* subMaterialPpu = HK_NULL;
	HK_DECLARE_SPU_LOCAL_DESTRUCTION_PTR(hkpBreakableMaterial, subMaterialSpu, sizeof(hkpBreakableMaterial));

	// Get material mapping
	const int mtlMapping = materialSpu->getMapping();

	if ( mtlMapping != hkpBreakableMaterial::MATERIAL_MAPPING_NONE )
	{
		// Download shape to Spu
		HK_DECLARE_SPU_LOCAL_DESTRUCTION_PTR(hkcdShape, shapeSpu, MAX_SHAPE_SIZE);
		downloadShapeOnSpu(shapePpu, shapeSpu);

		// Get sub-material Id
		MaterialId subMtlId;
		{
			hkUlong shapeInfoPtrPpu;
			switch ( materialSpu->getMapping() )
			{
			case hkpBreakableMaterial::MATERIAL_MAPPING_LIST_SHAPE:	// This is a hkpListShapeBreakableMaterial
				{
					HK_ASSERT2(0x623113be, shapeSpu->getType() == hkcdShapeType::LIST, "Failed to access the hkpListShape");
					const hkpListShape* ls = reinterpret_cast<const hkpListShape*>(shapeSpu);
					shapeInfoPtrPpu = ((hkUlong)ls->m_childInfo.begin()) + shapeKey * sizeof(hkpListShape::ChildInfo) + HK_OFFSET_OF(hkpListShape::ChildInfo, m_shapeInfo);
				}
				break;

			case hkpBreakableMaterial::MATERIAL_MAPPING_EMS:		// This is a hkpExtendedMeshShapeBreakableMaterial
				{		
					HK_ASSERT2(0x623113be, shapeSpu->getType() == hkcdShapeType::EXTENDED_MESH, "Failed to access the hkpExtendedMeshShape");
					const hkpExtendedMeshShape* ems = reinterpret_cast<const hkpExtendedMeshShape*>(shapeSpu);

					// Must retrieve the sub-material id. Get sub-part, the sub-material id is stored in the userData.
					const hkUint32 subpartIndex = ems->getSubPartIndex(shapeKey);
					const hkpExtendedMeshShape::SubpartType subPartType	= ems->getSubpartType(shapeKey);

					// Resolve PPU address
					shapeInfoPtrPpu = OFFSET_OF_EMS_SHAPE_INFO + (( subPartType == hkpExtendedMeshShape::SUBPART_TRIANGLES ) ?
														(((hkUlong)ems->getTriangleSubparts().begin())+ subpartIndex * sizeof(hkpExtendedMeshShape::TrianglesSubpart)	):
														(((hkUlong)ems->getShapesSubparts().begin())	+ subpartIndex * sizeof(hkpExtendedMeshShape::ShapesSubpart)	));
				}
				break;

			case hkpBreakableMaterial::MATERIAL_MAPPING_STATIC_COMPOUND:	// This is a hkpStaticCompoundShapeBreakableMaterial
				{
					HK_ASSERT2(0x623113be, shapeSpu->getType() == hkcdShapeType::STATIC_COMPOUND, "Failed to access the static compound shape");
					const hkpStaticCompoundShape* cp = reinterpret_cast<const hkpStaticCompoundShape*>(shapeSpu);

					// Must retrieve the sub-material id.
					const int numTerminalBits	= materialSpu->getExtraData();
					const hkUint32 instanceId	= (hkUint32)(shapeKey >> numTerminalBits);
					shapeInfoPtrPpu = ((hkUlong)cp->getInstanceExtraInfos().begin()) + instanceId * sizeof(hkUint16);
				}
				break;

			default:
				HK_ASSERT2(0x4e259429, false, "Unknown material mapping!");
				return false;
			}

			// Download sub-material Id from Ppu
			subMtlId						= *reinterpret_cast<const hkUint16*>(shapeInfoPtrPpu);
		}

		// Download the sub-material on SPU and return its strength
		subMaterialPpu = const_cast<hkpBreakableMaterial*>(static_cast<const hkpBreakableMultiMaterial*>(materialSpu)->getSubMaterial(subMtlId));
		HK_DOWNLOAD_DESTRUCTION_PTR_TO_SPU(subMaterialSpu, subMaterialPpu, sizeof(hkpBreakableMaterial));
		materialSpu = subMaterialSpu;
	}
	
	if ( materialSpu->isBreakable() )
	{
		materialSpu->getEncodedMaterialStrength(materialStrengthOut);
		return true;
	}
	return false;
}


//
//	Returns the index of the sub-material belonging to the given sub-shape

inline hkpBreakableMaterialUtil::MaterialId HK_CALL hkpBreakableMaterialUtil::getSubShapeMaterialIndex(const hkpBreakableMaterial* rootMtl, const hkcdShape* rootShape, hkUint32 subShapeId)
{
	return ( rootMtl->getMapping() == hkpBreakableMaterial::MATERIAL_MAPPING_NONE ) ? -1 : rootMtl->getSubShapeMaterialIndex(rootShape, subShapeId);
}

//
//	Returns the material set on the given shape key

inline hkpBreakableMaterial* HK_CALL hkpBreakableMaterialUtil::getMaterialAtShapeKey(const hkpBreakableMaterial* materialSpu, const hkcdShape* shapePpu, hkpShapeKey shapeKey)
{
	return ( materialSpu->getMapping() == hkpBreakableMaterial::MATERIAL_MAPPING_NONE ) ? const_cast<hkpBreakableMaterial*>(materialSpu) : materialSpu->getShapeKeyMaterial(shapePpu, shapeKey);
}

//
//	Appends the sub-material indices set on the given sub-shapes to the given array

inline void HK_CALL hkpBreakableMaterialUtil::getSubShapeMaterialIndices(const hkpBreakableMaterial* rootMtl, const hkcdShape* rootShape, const hkArray<hkUint32>& subShapeIdsIn, hkArray<MaterialId>& subMaterialsOut)
{
	if ( rootMtl->getMapping() != hkpBreakableMaterial::MATERIAL_MAPPING_NONE )
	{
		return rootMtl->getSubShapeMaterialIndices(rootShape, subShapeIdsIn, subMaterialsOut);
	}
}

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
