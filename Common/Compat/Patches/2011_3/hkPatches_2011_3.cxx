/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Common specific product patches applied to release 2011_3.
// This file is #included by hkPatches_2011_3.cpp

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkxSplineControlPoint", 0)
        HK_PATCH_MEMBER_ADDED("position", TYPE_VEC_4, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("tangentIn", TYPE_VEC_4, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("tangentOut", TYPE_VEC_4, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("inType", TYPE_BYTE, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("outType", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkxSpline", 0)
        HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
        HK_PATCH_MEMBER_ADDED("controlPoints", TYPE_ARRAY_STRUCT, "hkxSplineControlPoint", 0)
        HK_PATCH_MEMBER_ADDED("isClosed", TYPE_BYTE, HK_NULL, 0)
        HK_PATCH_DEPENDS("hkBaseObject", 0)
        HK_PATCH_DEPENDS("hkxSplineControlPoint", 0)
        HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkxScene", 1, "hkxScene", 2)
        HK_PATCH_MEMBER_ADDED("splines", TYPE_ARRAY_OBJECT, "hkxSpline", 0)
        HK_PATCH_DEPENDS("hkxSpline", 0)
        HK_PATCH_MEMBER_ADDED("numFrames", TYPE_INT, HK_NULL, 0)
        //HK_PATCH_FUNCTION(hkxScene_1_to_2)
HK_PATCH_END()

HK_PATCH_BEGIN("hkxMaterial", 2, "hkxMaterial", 3)
        HK_PATCH_MEMBER_ADDED("uvMapScale", TYPE_TUPLE_REAL, HK_NULL, 2)
        HK_PATCH_MEMBER_ADDED("uvMapOffset", TYPE_TUPLE_REAL, HK_NULL, 2)
        HK_PATCH_MEMBER_ADDED("uvMapRotation", TYPE_REAL, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("uvMapAlgorithm", TYPE_INT, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("specularMultiplier", TYPE_REAL, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("specularExponent", TYPE_REAL, HK_NULL, 0)
        
		HK_PATCH_MEMBER_DEFAULT_SET_REAL("uvMapScale", 1.000000f)
		HK_PATCH_MEMBER_DEFAULT_SET_REAL("uvMapOffset", 0.000000f)
        HK_PATCH_MEMBER_DEFAULT_SET_REAL("uvMapRotation", 0.000000f)
        HK_PATCH_MEMBER_DEFAULT_SET_INT("uvMapAlgorithm", 2)
        HK_PATCH_MEMBER_DEFAULT_SET_REAL("specularMultiplier", 0.000000f)
        HK_PATCH_MEMBER_DEFAULT_SET_REAL("specularExponent", 0.000000f)
		HK_PATCH_FUNCTION(hkxMaterial_2_to_3)
HK_PATCH_END()

HK_PATCH_BEGIN("hkxMaterial", 3, "hkxMaterial", 4)
        HK_PATCH_MEMBER_ADDED("transparency", TYPE_BYTE, HK_NULL, 0)
        HK_PATCH_MEMBER_DEFAULT_SET_BYTE("transparency", 0) // 0 == none
        //HK_PATCH_FUNCTION(hkxMaterial_3_to_4)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkxVertexAnimation", 0)
      HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
      HK_PATCH_MEMBER_ADDED("time", TYPE_REAL, HK_NULL, 0)
      HK_PATCH_MEMBER_ADDED("vertData", TYPE_STRUCT, "hkxVertexBuffer", 0)
      HK_PATCH_MEMBER_ADDED("vertexIndexMap", TYPE_ARRAY_INT, HK_NULL, 0)
      HK_PATCH_MEMBER_ADDED("componentMap", TYPE_ARRAY_STRUCT, "hkxVertexAnimationUsageMap", 0)
      HK_PATCH_DEPENDS("hkBaseObject", 0)
      HK_PATCH_DEPENDS("hkxVertexAnimationUsageMap", 0)
      HK_PATCH_DEPENDS("hkxVertexBuffer", 1)
      HK_PATCH_DEPENDS("hkReferencedObject", 0)
      //HK_PATCH_FUNCTION(hkxVertexAnimation_0_to_1)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkxVertexAnimationUsageMap", 0)
      HK_PATCH_MEMBER_ADDED("use", TYPE_INT, HK_NULL, 0)
      HK_PATCH_MEMBER_ADDED("useIndexOrig", TYPE_BYTE, HK_NULL, 0)
      HK_PATCH_MEMBER_ADDED("useIndexLocal", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkxNode", 2, "hkxNode", 3)
      HK_PATCH_MEMBER_ADDED("linearKeyFrameHints", TYPE_ARRAY_INT, HK_NULL, 0)
      HK_PATCH_MEMBER_ADDED("bone", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkxMeshSection", 2, "hkxMeshSection", 3)
      HK_PATCH_MEMBER_ADDED("vertexAnimations", TYPE_ARRAY_OBJECT, "hkxVertexAnimation", 0)
      HK_PATCH_DEPENDS("hkxVertexAnimation", 0)
      //HK_PATCH_FUNCTION(hkxMeshSection_2_to_3)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkAabb16", 0)
	HK_PATCH_MEMBER_ADDED("min", TYPE_TUPLE_INT, HK_NULL, 3)
	HK_PATCH_MEMBER_ADDED("key", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("max", TYPE_TUPLE_INT, HK_NULL, 3)
	HK_PATCH_MEMBER_ADDED("key1", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkCompressedMassProperties", 0)
	HK_PATCH_MEMBER_ADDED("centerOfMass", TYPE_TUPLE_INT, HK_NULL, 4)
	HK_PATCH_MEMBER_ADDED("inertia", TYPE_TUPLE_INT, HK_NULL, 4)
	HK_PATCH_MEMBER_ADDED("majorAxisSpace", TYPE_TUPLE_INT, HK_NULL, 4)
	HK_PATCH_MEMBER_ADDED("mass", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("volume", TYPE_REAL, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkScriptableAttribute", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkPackedVector8_3", 0)
	HK_PATCH_MEMBER_ADDED("values", TYPE_TUPLE_INT, HK_NULL, 4)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkSymmetricMatrix3", 0)
	HK_PATCH_MEMBER_ADDED("diag", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("offDiag", TYPE_VEC_4, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkxLight", 1, "hkxLight", 2)
        HK_PATCH_MEMBER_ADDED("range", TYPE_REAL, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("fadeStart", TYPE_REAL, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("fadeEnd", TYPE_REAL, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("intensity", TYPE_REAL, HK_NULL, 1)
        HK_PATCH_MEMBER_ADDED("shadowCaster", TYPE_BYTE, HK_NULL, 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkxNode", 3, "hkxNode", 4)
	HK_PATCH_MEMBER_REMOVED("linearKeyFrameHints", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("linearKeyFrameHints", TYPE_ARRAY_REAL, HK_NULL, 0)
HK_PATCH_END()

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
