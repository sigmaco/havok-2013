/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_BASE_CONTAINER_ALLOCATORS_H
#define HK_BASE_CONTAINER_ALLOCATORS_H

// These helper classes exist to allow containers to use different allocators
// without necessarily storing the allocator in the container.


		/// Forwards to the temp allocator
	struct hkContainerTempAllocator
	{
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, hkContainerTempAllocator);
		struct Allocator : public hkMemoryAllocator
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, Allocator);
			virtual void* blockAlloc( int numBytes );
			virtual void blockFree( void* p, int numBytes );
			virtual void* bufAlloc( int& reqNumBytesInOut );
			virtual void bufFree( void* p, int numBytes );
			virtual void* bufRealloc( void* pold, int oldNumBytes, int& reqNumBytesInOut );
			virtual void getMemoryStatistics( MemoryStatistics& u );
			virtual int getAllocatedSize(const void* obj, int nbytes);
		};
		static Allocator s_alloc;
		hkMemoryAllocator& get(const void*) { return s_alloc; }
	};

		/// Forwards to the heap allocator
	struct hkContainerHeapAllocator
	{
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, hkContainerHeapAllocator);
		struct Allocator : public hkMemoryAllocator
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, Allocator);
			virtual void* blockAlloc( int numBytes );
			virtual void blockFree( void* p, int numBytes );
			virtual void* bufAlloc( int& reqNumBytesInOut );
			virtual void bufFree( void* p, int numBytes );
			virtual void* bufRealloc( void* pold, int oldNumBytes, int& reqNumBytesInOut );
			virtual void getMemoryStatistics( MemoryStatistics& u );
			virtual int getAllocatedSize(const void* obj, int nbytes);
		};
		static Allocator s_alloc;
		hkMemoryAllocator& get(const void*) { return s_alloc; }
	};

		/// Forwards to the debug allocator
	struct hkContainerDebugAllocator
	{
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, hkContainerDebugAllocator);
		struct Allocator : public hkMemoryAllocator
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, Allocator);
			virtual void* blockAlloc( int numBytes );
			virtual void blockFree( void* p, int numBytes );
			virtual void* bufAlloc( int& reqNumBytesInOut );
			virtual void bufFree( void* p, int numBytes );
			virtual void* bufRealloc( void* pold, int oldNumBytes, int& reqNumBytesInOut );
			virtual void getMemoryStatistics( MemoryStatistics& u );
			virtual int getAllocatedSize(const void* obj, int nbytes);
		};
		static Allocator s_alloc;
		hkMemoryAllocator& get(const void*) { return s_alloc; }
	};


/// Allocator used when generic allocation is required without affecting the
/// other allocators.
struct hkContainerDefaultMallocAllocator
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, hkContainerDefaultMallocAllocator);
	hkMemoryAllocator& get(const void*);
};

#endif // HK_BASE_CONTAINER_ALLOCATORS_H

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
