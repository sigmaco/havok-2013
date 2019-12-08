/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef INC_HK_MAX_CONVEX_DECOMPOSITION_UTILITY_INTERFACE__H
#define INC_HK_MAX_CONVEX_DECOMPOSITION_UTILITY_INTERFACE__H

#include <iFnPub.h>

// Class ID
#define HK_CONVEX_DECOMPOSITION_UTILITY_CLASS_ID Class_ID(0x30445f93, 0x245e334a)

/*
** FUNCTION PUBLISHING
*/

#define HK_CONVEX_DECOMPOSITION_UTILITY_FPINTERFACE_ID Interface_ID(0x7d4a26d1, 0x399371a)

enum
{
	FPI_CheckValidity,
	FPI_Decompose,
	FPI_Combine
};

/*
** C++ Interface to the Havok Content Tools Convex Decompostion Utilities
**
** Exposed to MAXScript as hctConvexDecompositionUtilGUP
**
** The methods here correspond to the methods exposed to MaxScript
**
*/
class hctConvexDecompositionUtilGUPInterface : public FPStaticInterface
{
public:
	virtual BOOL iCheckValidity() = 0;
	virtual BOOL iDecompose (Tab<INode*>& nodesIn, Tab<INode*>& nodesOut, BOOL detachParts, BOOL singleOut, double guardTolerance, BOOL hideMesh, INT reduceOverlapPasses, INT octreeDepth, INT method, INT reduceMethod, INT witerations, double wconcavity) = 0;
	virtual BOOL iCombine (INode* baseNode, Tab<INode*>& origMeshNodes, Tab<INode*>& nodesIn, Tab<INode*>& nodesOut, double accuracyCombine, BOOL singleOutCombine, BOOL genGuards, INT octreeDepth, INT reduceMethod ) = 0;
};

#endif // INC_HK_MAX_CONVEX_DECOMPOSITION_UTILITY_INTERFACE__H

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
