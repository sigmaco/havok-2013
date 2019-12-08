/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef INC_HK_BONES_FROM_MESH_UTILITY_INTERFACE__H
#define INC_HK_BONES_FROM_MESH_UTILITY_INTERFACE__H

#include <iFnPub.h>

/*
** C++ Interface to the create bones for a simulation mesh.
**
** Exposed to MAXScript as hctBonesFromMeshUtility
**
** The methods here correspond to the methods and properties (get/set) exposed to MaxScript.
** Those, in turn, correspond to the fields exposed to the 3ds max UI
**
*/

// Class ID
#define HK_BONES_FROM_MESH_UTILITY_CLASS_ID Class_ID(0x2c7f91ee, 0xa114e3b6)

// Reference number of the PBlock
#define PBLOCK_BonesFromMeshUtility	0

// Param block IDs
enum
{
	PB_BONES_FROM_MESH_UTILITY_PBLOCK,
};

enum
{
	PA_BONES_FROM_MESH_UTILITY_BONENORMALAXIS,
	PA_BONES_FROM_MESH_UTILITY_BONETANGENTAXIS,
	PA_BONES_FROM_MESH_UTILITY_GLOBALTANGENTAXIS,
	PA_BONES_FROM_MESH_UTILITY_BONECREATIONMETHOD
};
//
// Function publishing
//

#define HK_BONES_FROM_MESH_UTILITY_FPINTERFACE_ID Interface_ID(0x62ed5ad2, 0xdf34ffa2)

enum
{
	FPI_GetBoneCreationMethod,
	FPI_SetBoneCreationMethod,
	FPI_GetBoneNormalAxis,
	FPI_SetBoneNormalAxis,
	FPI_GetBoneTangentAxis,
	FPI_SetBoneTangentAxis,
	FPI_GetGlobalTangentAxis,
	FPI_SetGlobalTangentAxis,
	FPI_CreateBonesFromMesh
};

enum
{
	FPI_ENUM_BoneCreationMethod,
	FPI_ENUM_BoneAxis,
	FPI_ENUM_GlobalAxis
};


class hctBonesFromMeshUtilityFPInterface : public FPStaticInterface
{
public:

	virtual BOOL iCreateBonesFromMesh() = 0;
};


//
// Action publishing
//

#define HK_BONES_FROM_MESH_UTILITY_ACTIONS_ID Interface_ID(0xf1ed017b, 0xca3ad12f)

enum
{
	ACT_CreateBonesFromMesh,
};

class hctBonesFromMeshUtilityActions : public FPStaticInterface
{
public:
	virtual BOOL iCreateBonesFromMesh() = 0;
};


#endif //INC_HK_BONES_FROM_MESH_UTILITY_INTERFACE__H

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
