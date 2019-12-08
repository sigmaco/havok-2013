/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKBASE_hkDebugMemorySystem_H
#define HKBASE_hkDebugMemorySystem_H

#include <Common/Base/Memory/System/hkMemorySystem.h>

	/// Interface for debug memory operations.
class hkDebugMemorySystem : public hkMemorySystem
{
public:

	HK_DECLARE_PLACEMENT_ALLOCATOR();

		/// Override so that the debug methods are accessible.
	hkDebugMemorySystem* getDebugInterface() HK_OVERRIDE { return this; }

		/// Special return values for findBaseAddress.
	enum BaseAddressResuls
	{
			/// The base address for the requested block could not be located.
		ADDRESS_NOT_FOUND = -1,

			/// The hkMemorySystem implementation doesn't support this interface.
		INTERFACE_NOT_SUPPORTED = -2,
	};

		/// Optional interface to search for the originally allocated memory block within
		/// which the supplied memory block is located. This method returns the originally allocated
		/// memory block's base address. It will assert if it cannot find a matching block.
		/// Returns INTERFACE_NOT_SUPPORTED if the operation is not supported.
	virtual const void* findBaseAddress(const void* p, int nbytes) { return (const void*)(INTERFACE_NOT_SUPPORTED); }

		/// Optional interface to ensure block is not freed until unlocked.
		/// Multiple locks stack. If this method is implemented, attempts to free
		/// this block without first unlocking will assert.
	virtual void lockBaseAddress(const void* baseAddress) = 0;

		/// Optional interface to unlock a previously locked block.
	virtual void unlockBaseAddress(const void* baseAddress) = 0;

		/// Optional interface to associate a piece of data with an allocation.
		/// The meaning of the tag depends on the caller.
	virtual void tagAddress(const void* baseAddress, const void* tag) = 0;

		/// Log a user-specified string.
		/// This can be used to help narrow down memory leaks to specific areas.
		/// It is up to the implementation to store the string if desired.
	virtual void addBookmark( const char* bookmarkName ) = 0;

		/// Determines whether callstack checking is currently enabled
		/// by the memory system.
	virtual hkBool32 isCheckCallstackEnabled() const = 0;

		/// Turns callstack checking on or off, if the memory system
		/// supports it. Has no effect if the memory system does not
		/// support callstack checking. This function should only be 
		/// used to temporarily disable callstack checking; it must
		/// not enable callstack checking if callstack checking was not
		/// initially enabled, and after it is disabled, it must be
		/// reenabled before the memory system is destroyed.
	virtual void setCheckCallstackEnabled(bool enabled) = 0;

};

#endif // #ifndef HKBASE_hkDebugMemorySystem_H

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
