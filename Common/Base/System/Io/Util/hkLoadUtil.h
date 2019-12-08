/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_hkLoadUtil_H
#define HK_hkLoadUtil_H

class hkStreamReader;
class hkMemoryAllocator;
class hkStringPtr;
class hkStringBuf;
class hkIstream;

	/// Utility class to 
class hkLoadUtil
{
	public:

		HK_DECLARE_PLACEMENT_ALLOCATOR();

		//
		// inputs
		//
		
			/// Load from the hkFileSystem singleton.
		hkLoadUtil(const char* fname);

			/// Load from the given hkStreamReader.
		hkLoadUtil( hkStreamReader* sr );

			/// Load from the given hkIstream
		hkLoadUtil( hkIstream& is );
		
			///
		~hkLoadUtil();


		//
		// outputs
		//

			/// Read into an hkArray::Temp
		bool toArray( hkArray<char>::Temp& out );

			/// Read into a heap hkArray
		bool toArray( hkArray<char>& out );

			/// 
		bool toArray( hkArrayBase<char>& out, hkMemoryAllocator& mem );


			/// Read into a newly allocated block. Free with mem.blockFree(p, sizeOut)
		void* toAllocation( int* sizeOut, hkMemoryAllocator& mem );

			/// Get as a null terminated string.
		bool toString( hkStringBuf& buf );

			/// Get as a null terminated string.
		bool toString( hkStringPtr& buf );

			/// Get as a null-terminated string. The return value is the length of
			/// the string. The buffer is always terminated. Thus the return value
			/// is at most bufSize-1.
		int toString( char* buf, int bufSize );

	private:

		const char* m_fileName;
		hkRefPtr<hkStreamReader> m_reader;
};

#endif // HK_hkLoadUtil_H

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
