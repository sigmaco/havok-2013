/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_BASE_STDIOSTREAMREADER_H
#define HK_BASE_STDIOSTREAMREADER_H

#include <Common/Base/System/Io/Reader/hkStreamReader.h>

class hkStdioStreamReader : public hkSeekableStreamReader
{
	public:
		static hkStdioStreamReader* open( const char* nameIn );

		hkStdioStreamReader( /*FILE*/void* handle );
		virtual ~hkStdioStreamReader();

		virtual int read( void* buf, int nbytes);	
		virtual hkBool isOk() const;
		virtual int peek(void* buf, int n);

		virtual hkResult seek( int offset, SeekWhence whence);
		virtual int tell() const;

	protected:

		void* m_handle; //FILE*
		hkBool m_isOk;
};

#endif //HK_BASE_STDIOSTREAMREADER_H

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
