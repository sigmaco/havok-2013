/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_BASE_STDIOSTREAMWRITER_H
#define HK_BASE_STDIOSTREAMWRITER_H

#include <Common/Base/System/Io/Writer/hkStreamWriter.h>

class hkStdioStreamWriter : public hkStreamWriter
{
	public:

		static hkStdioStreamWriter* open(const char* name, const char* mode);

		hkStdioStreamWriter(void* /*FILE**/ handle, hkBool shouldClose);
		virtual ~hkStdioStreamWriter();

		void close();

		virtual int write( const void* buf, int nbytes);
		virtual void flush();
		virtual hkBool isOk() const;
		virtual hkBool seekTellSupported() const;
		virtual hkResult seek( int offset, SeekWhence whence);
		virtual int tell() const;

	protected:

		void* m_handle;
		hkBool m_shouldClose;
};

#endif //HK_BASE_STDIOSTREAMWRITER_H

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
