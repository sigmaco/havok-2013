/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKBASE_EXTERNAL_LAYOUT_HANDLER_MANAGER_H
#define HKBASE_EXTERNAL_LAYOUT_HANDLER_MANAGER_H

#include <Common/Base/Container/StringMap/hkStorageStringMap.h>

class hkTrackerLayoutHandler;
class hkTrackerLayoutCalculator;

/// This singleton is used by entities outside of the Havok SDK to register custom handlers
/// for specific class types. The manager will simply store those handlers and when a new
/// hkTrackerLayoutCalculator is created we will register those as additional handlers in the
/// calculator. The Havok demo framework uses this to register handlers for external classes.
class hkTrackerExternalLayoutHandlerManager : public hkReferencedObject, public hkSingleton<hkTrackerExternalLayoutHandlerManager>
{
public:
	HK_DECLARE_CLASS_ALLOCATOR(ExtHandlerManager);

	/// Add a handler.
	/// If a handler is found with the associated name, it's overwritten.
	void addHandler(const char* name, hkTrackerLayoutHandler* handler);

	/// Get the handler associated with type name.
	hkTrackerLayoutHandler* getHandler(const char* name) const;

	/// Remove a handler.
	/// If a handler for the given name is not found, nothing happens.
	void removeHandler(const char* name);

	/// Add all registered external handlers to the provided layout calculator.
	void addHandlersToLayoutCalculator(hkTrackerLayoutCalculator* layoutCalc);

	/// Removes all stored handlers.
	void clear();

	~hkTrackerExternalLayoutHandlerManager();

protected:
	hkStorageStringMap<hkTrackerLayoutHandler*> m_handlers;
};


#endif // HKBASE_EXTERNAL_LAYOUT_HANDLER_MANAGER_H

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
