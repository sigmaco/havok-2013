/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Cloth specific product patches applied to release 2012_1.
// This file is #included by hclPatches_2012_1.cpp

HK_PATCH_BEGIN("hclHingeConstraintSetHinge", 0, HK_NULL, HK_CLASS_REMOVED)
	HK_PATCH_MEMBER_REMOVED("particleA", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("particleB", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("particle1", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("particle2", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("hingeStiffness", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("relaxFactor", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("sinHalfAngle", TYPE_REAL, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclHingeSetupObject", 0, HK_NULL, HK_CLASS_REMOVED)
	HK_PATCH_PARENT_SET("hclConstraintSetSetupObject", HK_NULL)
	HK_PATCH_MEMBER_REMOVED("name", TYPE_CSTRING, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("simulationMesh", TYPE_OBJECT, "hclSimulationSetupMesh", 0)
	HK_PATCH_MEMBER_REMOVED("vertexSelection", TYPE_STRUCT, "hclVertexSelectionInput", 0)
	HK_PATCH_MEMBER_REMOVED("hingeStiffness", TYPE_STRUCT, "hclVertexFloatInput", 0)
	HK_PATCH_MEMBER_REMOVED("relaxFactor", TYPE_STRUCT, "hclVertexFloatInput", 0)
	HK_PATCH_DEPENDS("hclSimulationSetupMesh", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hclVertexSelectionInput", 0)
	HK_PATCH_DEPENDS("hclVertexFloatInput", 0)
	HK_PATCH_DEPENDS("hclConstraintSetSetupObject", 0)
	HK_PATCH_DEPENDS("hclSetupMesh", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclHingeConstraintSet", 0, HK_NULL, HK_CLASS_REMOVED)
	HK_PATCH_PARENT_SET("hclConstraintSet", HK_NULL)
	HK_PATCH_MEMBER_REMOVED("hinges", TYPE_ARRAY_STRUCT, "hclHingeConstraintSetHinge", 0)
	HK_PATCH_DEPENDS("hclHingeConstraintSetHinge", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hclConstraintSet", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclRecalculateNormalsSetupObject", 0, HK_NULL, HK_CLASS_REMOVED)
	HK_PATCH_PARENT_SET("hclOperatorSetupObject", HK_NULL)
	HK_PATCH_MEMBER_REMOVED("name", TYPE_CSTRING, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("buffer", TYPE_OBJECT, "hclBufferSetupObject", 0)
	HK_PATCH_MEMBER_REMOVED("vertexSelection", TYPE_STRUCT, "hclVertexSelectionInput", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hclVertexSelectionInput", 0)
	HK_PATCH_DEPENDS("hclOperatorSetupObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hclBufferSetupObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclRecalculateSomeNormalsOperator", 0, HK_NULL, HK_CLASS_REMOVED)
	HK_PATCH_PARENT_SET("hclOperator", HK_NULL)
	HK_PATCH_MEMBER_REMOVED("bufferIdx", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("vertexIndices", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("triangleIndices", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hclOperator", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclRecalculateAllNormalsOperator", 0, HK_NULL, HK_CLASS_REMOVED)
	HK_PATCH_PARENT_SET("hclOperator", HK_NULL)
	HK_PATCH_MEMBER_REMOVED("bufferIdx", TYPE_INT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hclOperator", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclVolumeConstraintSetupObject", 1, "hclVolumeConstraintSetupObject", 2)
	HK_PATCH_MEMBER_REMOVED("useDeprecatedMethod", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclVolumeConstraint", 1, "hclVolumeConstraint", 2)
	HK_PATCH_MEMBER_REMOVED("useDeprecatedMethod", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclSimulateSetupObject", 1, "hclSimulateSetupObject", 2)
	HK_PATCH_MEMBER_REMOVED("collideAndSolve", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclSimulateOperator", 1, "hclSimulateOperator", 2)
	HK_PATCH_MEMBER_REMOVED("collideAndSolve", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hclBoneSpaceDeformerLocalBlockUnpackedPN", 0)
	HK_PATCH_MEMBER_ADDED("localPosition", TYPE_TUPLE_VEC_4, HK_NULL, 16)
	HK_PATCH_MEMBER_ADDED("localNormal", TYPE_TUPLE_VEC_4, HK_NULL, 16)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hclBoneSpaceDeformerLocalBlockUnpackedPNT", 0)
	HK_PATCH_MEMBER_ADDED("localPosition", TYPE_TUPLE_VEC_4, HK_NULL, 16)
	HK_PATCH_MEMBER_ADDED("localNormal", TYPE_TUPLE_VEC_4, HK_NULL, 16)
	HK_PATCH_MEMBER_ADDED("localTangent", TYPE_TUPLE_VEC_4, HK_NULL, 16)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hclObjectSpaceDeformerLocalBlockUnpackedP", 0)
	HK_PATCH_MEMBER_ADDED("localPosition", TYPE_TUPLE_VEC_4, HK_NULL, 16)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hclObjectSpaceDeformerLocalBlockUnpackedPN", 0)
	HK_PATCH_MEMBER_ADDED("localPosition", TYPE_TUPLE_VEC_4, HK_NULL, 16)
	HK_PATCH_MEMBER_ADDED("localNormal", TYPE_TUPLE_VEC_4, HK_NULL, 16)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hclObjectSpaceDeformerLocalBlockUnpackedPNTB", 0)
	HK_PATCH_MEMBER_ADDED("localPosition", TYPE_TUPLE_VEC_4, HK_NULL, 16)
	HK_PATCH_MEMBER_ADDED("localNormal", TYPE_TUPLE_VEC_4, HK_NULL, 16)
	HK_PATCH_MEMBER_ADDED("localTangent", TYPE_TUPLE_VEC_4, HK_NULL, 16)
	HK_PATCH_MEMBER_ADDED("localBiTangent", TYPE_TUPLE_VEC_4, HK_NULL, 16)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hclObjectSpaceDeformerLocalBlockUnpackedPNT", 0)
	HK_PATCH_MEMBER_ADDED("localPosition", TYPE_TUPLE_VEC_4, HK_NULL, 16)
	HK_PATCH_MEMBER_ADDED("localNormal", TYPE_TUPLE_VEC_4, HK_NULL, 16)
	HK_PATCH_MEMBER_ADDED("localTangent", TYPE_TUPLE_VEC_4, HK_NULL, 16)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hclBoneSpaceDeformerLocalBlockUnpackedPNTB", 0)
	HK_PATCH_MEMBER_ADDED("localPosition", TYPE_TUPLE_VEC_4, HK_NULL, 16)
	HK_PATCH_MEMBER_ADDED("localNormal", TYPE_TUPLE_VEC_4, HK_NULL, 16)
	HK_PATCH_MEMBER_ADDED("localTangent", TYPE_TUPLE_VEC_4, HK_NULL, 16)
	HK_PATCH_MEMBER_ADDED("localBiTangent", TYPE_TUPLE_VEC_4, HK_NULL, 16)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hclBoneSpaceDeformerLocalBlockUnpackedP", 0)
	HK_PATCH_MEMBER_ADDED("localPosition", TYPE_TUPLE_VEC_4, HK_NULL, 16)
HK_PATCH_END()

HK_PATCH_BEGIN("hclObjectSpaceMeshMeshDeformPNOperator", 0, "hclObjectSpaceMeshMeshDeformPNOperator", 1)
	HK_PATCH_MEMBER_ADDED("localUnpackedPNs", TYPE_ARRAY_STRUCT, "hclObjectSpaceDeformerLocalBlockUnpackedPN", 0)
	HK_PATCH_DEPENDS("hclObjectSpaceDeformerLocalBlockUnpackedPN", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclBoneSpaceMeshMeshDeformPOperator", 0, "hclBoneSpaceMeshMeshDeformPOperator", 1)
	HK_PATCH_MEMBER_ADDED("localUnpackedPs", TYPE_ARRAY_STRUCT, "hclBoneSpaceDeformerLocalBlockUnpackedP", 0)
	HK_PATCH_DEPENDS("hclBoneSpaceDeformerLocalBlockUnpackedP", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclObjectSpaceSkinPNOperator", 0, "hclObjectSpaceSkinPNOperator", 1)
	HK_PATCH_MEMBER_ADDED("localUnpackedPNs", TYPE_ARRAY_STRUCT, "hclObjectSpaceDeformerLocalBlockUnpackedPN", 0)
	HK_PATCH_DEPENDS("hclObjectSpaceDeformerLocalBlockUnpackedPN", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclBoneSpaceSkinPNOperator", 0, "hclBoneSpaceSkinPNOperator", 1)
	HK_PATCH_MEMBER_ADDED("localUnpackedPNs", TYPE_ARRAY_STRUCT, "hclBoneSpaceDeformerLocalBlockUnpackedPN", 0)
	HK_PATCH_DEPENDS("hclBoneSpaceDeformerLocalBlockUnpackedPN", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclBoneSpaceSkinPNTOperator", 0, "hclBoneSpaceSkinPNTOperator",1)
	HK_PATCH_MEMBER_ADDED("localUnpackedPNTs", TYPE_ARRAY_STRUCT, "hclBoneSpaceDeformerLocalBlockUnpackedPNT", 0)
	HK_PATCH_DEPENDS("hclBoneSpaceDeformerLocalBlockUnpackedPNT", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclBoneSpaceSkinPNTBOperator", 0, "hclBoneSpaceSkinPNTBOperator", 1)
	HK_PATCH_MEMBER_ADDED("localUnpackedPNTBs", TYPE_ARRAY_STRUCT, "hclBoneSpaceDeformerLocalBlockUnpackedPNTB", 0)
	HK_PATCH_DEPENDS("hclBoneSpaceDeformerLocalBlockUnpackedPNTB", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclObjectSpaceMeshMeshDeformPOperator", 0, "hclObjectSpaceMeshMeshDeformPOperator", 1)
	HK_PATCH_MEMBER_ADDED("localUnpackedPs", TYPE_ARRAY_STRUCT, "hclObjectSpaceDeformerLocalBlockUnpackedP", 0)
	HK_PATCH_DEPENDS("hclObjectSpaceDeformerLocalBlockUnpackedP", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclBoneSpaceMeshMeshDeformPNOperator", 0, "hclBoneSpaceMeshMeshDeformPNOperator", 1)
	HK_PATCH_MEMBER_ADDED("localUnpackedPNs", TYPE_ARRAY_STRUCT, "hclBoneSpaceDeformerLocalBlockUnpackedPN", 0)
	HK_PATCH_DEPENDS("hclBoneSpaceDeformerLocalBlockUnpackedPN", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclBoneSpaceMeshMeshDeformPNTBOperator", 0, "hclBoneSpaceMeshMeshDeformPNTBOperator", 1)
	HK_PATCH_MEMBER_ADDED("localUnpackedPNTBs", TYPE_ARRAY_STRUCT, "hclBoneSpaceDeformerLocalBlockUnpackedPNTB", 0)
	HK_PATCH_DEPENDS("hclBoneSpaceDeformerLocalBlockUnpackedPNTB", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclObjectSpaceMeshMeshDeformPNTOperator", 0, "hclObjectSpaceMeshMeshDeformPNTOperator", 1)
	HK_PATCH_MEMBER_ADDED("localUnpackedPNTs", TYPE_ARRAY_STRUCT, "hclObjectSpaceDeformerLocalBlockUnpackedPNT", 0)
	HK_PATCH_DEPENDS("hclObjectSpaceDeformerLocalBlockUnpackedPNT", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclObjectSpaceMeshMeshDeformPNTBOperator", 0, "hclObjectSpaceMeshMeshDeformPNTBOperator", 1)
	HK_PATCH_MEMBER_ADDED("localUnpackedPNTBs", TYPE_ARRAY_STRUCT, "hclObjectSpaceDeformerLocalBlockUnpackedPNTB", 0)
	HK_PATCH_DEPENDS("hclObjectSpaceDeformerLocalBlockUnpackedPNTB", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclBoneSpaceMeshMeshDeformPNTOperator", 0, "hclBoneSpaceMeshMeshDeformPNTOperator", 1)
	HK_PATCH_MEMBER_ADDED("localUnpackedPNTs", TYPE_ARRAY_STRUCT, "hclBoneSpaceDeformerLocalBlockUnpackedPNT", 0)
	HK_PATCH_DEPENDS("hclBoneSpaceDeformerLocalBlockUnpackedPNT", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclObjectSpaceSkinPNTBOperator", 0, "hclObjectSpaceSkinPNTBOperator", 1)
	HK_PATCH_MEMBER_ADDED("localUnpackedPNTBs", TYPE_ARRAY_STRUCT, "hclObjectSpaceDeformerLocalBlockUnpackedPNTB", 0)
	HK_PATCH_DEPENDS("hclObjectSpaceDeformerLocalBlockUnpackedPNTB", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclObjectSpaceSkinPOperator", 0, "hclObjectSpaceSkinPOperator",1)
	HK_PATCH_MEMBER_ADDED("localUnpackedPs", TYPE_ARRAY_STRUCT, "hclObjectSpaceDeformerLocalBlockUnpackedP", 0)
	HK_PATCH_DEPENDS("hclObjectSpaceDeformerLocalBlockUnpackedP", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclBoneSpaceSkinPOperator", 0, "hclBoneSpaceSkinPOperator", 1)
	HK_PATCH_MEMBER_ADDED("localUnpackedPs", TYPE_ARRAY_STRUCT, "hclBoneSpaceDeformerLocalBlockUnpackedP", 0)
	HK_PATCH_DEPENDS("hclBoneSpaceDeformerLocalBlockUnpackedP", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclObjectSpaceSkinPNTOperator", 0, "hclObjectSpaceSkinPNTOperator", 1)
	HK_PATCH_MEMBER_ADDED("localUnpackedPNTs", TYPE_ARRAY_STRUCT, "hclObjectSpaceDeformerLocalBlockUnpackedPNT", 0)
	HK_PATCH_DEPENDS("hclObjectSpaceDeformerLocalBlockUnpackedPNT", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclBoneSpaceSkinOperator", 0, "hclBoneSpaceSkinOperator", 1)
	HK_PATCH_MEMBER_ADDED("transformSubset", TYPE_ARRAY_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclObjectSpaceSkinOperator", 0, "hclObjectSpaceSkinOperator", 1)
	HK_PATCH_MEMBER_ADDED("transformSubset", TYPE_ARRAY_INT, HK_NULL, 0)
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
