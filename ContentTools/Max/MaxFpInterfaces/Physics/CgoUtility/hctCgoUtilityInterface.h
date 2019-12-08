/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef INC_HK_MAX_CGO_UTILITY_INTERFACE__H
#define INC_HK_MAX_CGO_UTILITY_INTERFACE__H

#include <iFnPub.h>

/*
** C++ Interface to the Collision geometry optimizer Utility.
**
** Exposed to MAXScript as hctCgoUtility
**
** The methods here correspond to the methods and properties (get/set) exposed to MaxScript.
** Those, in turn, correspond to the fields exposed to the 3ds max UI
**
*/

// Class ID
#define HK_CGO_UTILITY_CLASS_ID Class_ID(0x4EAC64CB, 0x4EA84181)

// Reference number of the PBlock
#define PBLOCK_CgoUtility	0

// Param block IDs
enum
{
	PB_CGO_UTILITY_PBLOCK,
};

// Normal Parameters
enum
{
	PA_CGO_UTILITY_MAXERROR,
	PA_CGO_UTILITY_MAXVERTS,
	PA_CGO_UTILITY_SHRINKING,
	PA_CGO_UTILITY_PROTECT_MATERIALS,
	PA_CGO_UTILITY_PROTECT_EDGES,
	PA_CGO_UTILITY_USE_WEIGHTS,
	PA_CGO_UTILITY_DELETE_INPUT,
	PA_CGO_UTILITY_MULTIPASS,
	PA_CGO_UTILITY_ANALYSE,
};

//
// Function publishing
//

#define HK_CGO_UTILITY_FPINTERFACE_ID Interface_ID(0x62ed5ad2, 0xdf34ffa2)

enum
{
	FPI_CanOptimize,
	FPI_Optimize,
	FPI_GetMaxError,
	FPI_SetMaxError,
	FPI_GetMaxVerts,
	FPI_SetMaxVerts,
	FPI_GetShrinking,
	FPI_SetShrinking,
	FPI_GetProtectMaterials,
	FPI_SetProtectMaterials,
	FPI_GetProtectEdges,
	FPI_SetProtectEdges,
	FPI_GetUseWeights,
	FPI_SetUseWeights,
	FPI_GetDeleteInput,
	FPI_SetDeleteInput,
	FPI_GetMultipass,
	FPI_SetMultipass,
	FPI_GetAnalyse,
	FPI_SetAnalyse,
};

/// WARNING: This feature is currently in BETA. Changes in interface, behaviour or performance may be expected.
class hctCgoUtilityFPInterface : public FPStaticInterface
{
	public:

		virtual BOOL	iCanOptimize() = 0;
		virtual INode*	iOptimize(INode* node) = 0;
		
		virtual void	iSetMaxError (float value) = 0;
		virtual float	iGetMaxError () = 0;

		virtual void	iSetMaxVerts (float value) = 0;
		virtual float	iGetMaxVerts () = 0;
		
		virtual void	iSetShrinking(float value) = 0;
		virtual float	iGetShrinking() = 0;

		virtual void	iSetProtectMaterials (bool value)=0;
		virtual bool	iGetProtectMaterials ()=0;

		virtual void	iSetProtectEdges (bool value)=0;
		virtual bool	iGetProtectEdges ()=0;

		virtual void	iSetUseWeights (bool value)=0;
		virtual bool	iGetUseWeights ()=0;

		virtual void	iSetDeleteInput (bool value)=0;
		virtual bool	iGetDeleteInput ()=0;

		virtual void	iSetMultipass (bool value)=0;
		virtual bool	iGetMultipass ()=0;

		virtual void	iSetAnalyse (bool value)=0;
		virtual bool	iGetAnalyse ()=0;
};


//
// Action publishing
//

#define HK_CGO_UTILITY_ACTIONS_ID Interface_ID(0xf1ed017b, 0xca3ad130)

enum
{
	ACT_OptimizeEnabled,
	ACT_Optimize,
};

class hctCgoUtilityActions : public FPStaticInterface
{
	public:

		virtual BOOL		iOptimizeEnabled() = 0;
		virtual FPStatus	iOptimize() = 0;
};


#endif //INC_HK_MAX_CGO_UTILITY_INTERFACE__H

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
