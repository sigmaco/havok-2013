/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HCT_FILTER_DIALOG_UTILS_H
#define HCT_FILTER_DIALOG_UTILS_H

#include <ContentTools/Common/SceneExport/Error/hctSceneExportError.h> 

// This functions is used by filter Dialogs to display ToolTips
BOOL CreateToolTip(int toolID, HWND hDlg, HINSTANCE hInst, hkStringOld toolText);

// This function will print (incl. formatting) the LogEntry to the provided RichEdit control.
void hctPrintLogEntryToRichEditControl(const hctSceneExportError::LogEntry& entry, HWND richEditControl);

#endif	// HCT_FILTER_DIALOG_UTILS_H

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
