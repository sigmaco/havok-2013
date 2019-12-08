/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_DYNAMICS2_BREAKABLE_MATERIAL_UTIL_H
#define HK_DYNAMICS2_BREAKABLE_MATERIAL_UTIL_H

#include <Physics2012/Dynamics/Destruction/BreakableMaterial/hkpBreakableMaterial.h>
#include <Physics2012/Dynamics/Destruction/BreakableMaterial/Simple/hkpSimpleBreakableMaterial.h>
#include <Physics2012/Dynamics/Destruction/BreakableMaterial/MultiMaterial/hkpBreakableMultiMaterial.h>
#include <Physics2012/Dynamics/Destruction/BreakableMaterial/MultiMaterial/ListShape/hkpListShapeBreakableMaterial.h>
#include <Physics2012/Dynamics/Destruction/BreakableMaterial/MultiMaterial/ExtendedMeshShape/hkpEmsBreakableMaterial.h>
#include <Physics2012/Dynamics/Destruction/BreakableMaterial/MultiMaterial/CompoundShape/hkpScsBreakableMaterial.h>

	/// Breakable material utility class.
class hkpBreakableMaterialUtil
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_DESTRUCTION_2012, hkpBreakableMaterialUtil);

	public:

		typedef hkpBreakableMaterial::MaterialId MaterialId;

	public:

		enum
		{
			MAX_MATERIAL_SIZE			= sizeof(hkpBreakableMultiMaterial),
			MAX_SHAPE_SIZE				= sizeof(hkpExtendedMeshShape),
			OFFSET_OF_EMS_SHAPE_INFO	= 2,
		};

	public:

			/// Returns the material strength set on the given sub-shape. Returns true if the material is breakable, false otherwise.
		static HK_FORCE_INLINE hkBool HK_CALL getSubShapeMaterialStrength(const hkpBreakableMaterial* materialSpu, const hkcdShape* shapePpu, hkpShapeKey shapeKey, hkUFloat8& materialStrengthOut);

	protected:

			/// Called to download the shape from Ppu to Spu
		static HK_FORCE_INLINE void HK_CALL downloadShapeOnSpu(const hkcdShape* shapePpu, hkcdShape*& shapeSpu);


	public:

			/// Returns the material set on the given shape key
		static HK_FORCE_INLINE hkpBreakableMaterial* HK_CALL getMaterialAtShapeKey(const hkpBreakableMaterial* materialSpu, const hkcdShape* shapePpu, hkpShapeKey shapeKey);

			/// Creates a hkpSimpleBreakableMaterial clone of the given material
		static class hkpSimpleBreakableMaterial* HK_CALL cloneAsSimpleMaterial(const hkpBreakableMaterial* mtl);

			/// Copies the behaviors and strength from the source to the destination material
		static void HK_CALL copyMaterialData(hkpBreakableMaterial* dstMtl, const hkpBreakableMaterial* srcMtl);

			/// Collects all materials recursively, starting from the given material
		static void HK_CALL collectMaterialsRecursive(const hkpBreakableMaterial* rootMtl, hkArray<const hkpBreakableMaterial*>& materialsOut);

			/// Returns the index of the sub-material belonging to the given sub-shape
		static HK_FORCE_INLINE MaterialId HK_CALL getSubShapeMaterialIndex(const hkpBreakableMaterial* rootMtl, const hkcdShape* rootShape, hkUint32 subShapeId);

			/// Appends the sub-material indices set on the given sub-shapes to the given array
		static HK_FORCE_INLINE void HK_CALL getSubShapeMaterialIndices(const hkpBreakableMaterial* rootMtl, const hkcdShape* rootShape, const hkArray<hkUint32>& subShapeIdsIn, hkArray<MaterialId>& subMaterialsOut);

};

#include <Physics2012/Dynamics/Destruction/BreakableMaterial/hkpBreakableMaterialUtil.inl>

#endif	//	HK_DYNAMICS2_BREAKABLE_MATERIAL_UTIL_H

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
