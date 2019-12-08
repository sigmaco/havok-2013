/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef INC_SELECTIONUTILGUPINTERFACE
#define INC_SELECTIONUTILGUPINTERFACE

#include <iFnPub.h>

// Class ID
#define HK_SELECTION_UTIL_GUP_CLASS_ID	Class_ID(0x1623201a, 0x367c0374)

/*
** FUNCTION PUBLISHING
*/

#define HK_SELECTION_UTIL_GUP_FPINTERFACE_ID	Interface_ID(0x29130c9, 0x30cd04ab)

enum 
{
	FPI_GetVertSelectionsNames, 
	FPI_GetFaceSelectionsNames,
	FPI_GetEdgeSelectionsNames,
	FPI_CreateNamedSelectionFromCurrent,
	FPI_OverwriteNamedVertSelectionFromCurrent,
	FPI_OverwriteNamedFaceSelectionFromCurrent,
	FPI_OverwriteNamedEdgeSelectionFromCurrent,
	FPI_RenameVertSelection,
	FPI_RenameFaceSelection,
	FPI_RenameEdgeSelection,
	FPI_DeleteVertSelection,
	FPI_DeleteFaceSelection,
	FPI_DeleteEdgeSelection,
	FPI_LoadVertSelection,
	FPI_LoadFaceSelection,
	FPI_LoadEdgeSelection
};

/*
** C++ Interface to the Havok Content Tools Selection Utilities.
**
** Exposed to MAXScript as hctSelectionUtilGUP
**
** The methods here correspond to the methods exposed to MaxScript.
** 
*/
class hctSelectionUtilGUPInterface : public FPStaticInterface 
{
	public:

		virtual Tab<const MCHAR*>* iGetVertSelectionsNames( INode* selectedNode ) = 0;
		virtual Tab<const MCHAR*>* iGetFaceSelectionsNames( INode* selectedNode ) = 0;
		virtual Tab<const MCHAR*>* iGetEdgeSelectionsNames( INode* selectedNode ) = 0;
		virtual BOOL iCreateNamedSelectionFromCurrent( INode* selectedNode, const MCHAR* selectionName ) = 0;
		virtual BOOL iOverwriteNamedVertSelectionFromCurrent( INode* selectedNode, const MCHAR* selectionName ) = 0;
		virtual BOOL iOverwriteNamedFaceSelectionFromCurrent( INode* selectedNode, const MCHAR* selectionName ) = 0;
		virtual BOOL iOverwriteNamedEdgeSelectionFromCurrent( INode* selectedNode, const MCHAR* selectionName ) = 0;
		virtual BOOL iRenameVertSelection( INode* selectedNode, const MCHAR* oldName, const MCHAR* newName ) = 0;
		virtual BOOL iRenameFaceSelection( INode* selectedNode, const MCHAR* oldName, const MCHAR* newName ) = 0;
		virtual BOOL iRenameEdgeSelection( INode* selectedNode, const MCHAR* oldName, const MCHAR* newName ) = 0;
		virtual BOOL iDeleteVertSelection( INode* selectedNode, const MCHAR* name ) = 0;
		virtual BOOL iDeleteFaceSelection( INode* selectedNode, const MCHAR* name ) = 0;
		virtual BOOL iDeleteEdgeSelection( INode* selectedNode, const MCHAR* name ) = 0;
		virtual BOOL iLoadVertSelection( INode* selectedNode, const MCHAR* name ) = 0;
		virtual BOOL iLoadFaceSelection( INode* selectedNode, const MCHAR* name ) = 0;
		virtual BOOL iLoadEdgeSelection( INode* selectedNode, const MCHAR* name ) = 0;
};

#endif //INC_SELECTIONUTILGUPINTERFACE

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
