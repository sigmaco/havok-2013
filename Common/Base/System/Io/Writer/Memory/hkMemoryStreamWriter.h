/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKBASE_MEMORY_STREAM_WRITER_H
#define HKBASE_MEMORY_STREAM_WRITER_H

#include <Common/Base/System/Io/Writer/hkStreamWriter.h>

	/// Write to a fixed size memory block.
class hkMemoryStreamWriter : public hkStreamWriter
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_STREAM);

			/// The memory is not cleared before writing.
			/// Normally this is not a problem, but if you plan to perform random access with seek(),
			/// you may want to clear the buffer.
		hkMemoryStreamWriter(void* buf, int bufSize) : m_buf(buf), m_bufSize(bufSize), m_cur(0) {}

		virtual int write(const void* b, int nb);

		virtual hkBool isOk() const;

		virtual hkBool seekTellSupported() const;
		virtual int tell() const;
		virtual hkResult seek(int offset, SeekWhence whence);

	protected:

		void* m_buf;
		int m_bufSize;
		int m_cur;
};

#endif //HKBASE_MEMORY_STREAM_WRITER_H

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
