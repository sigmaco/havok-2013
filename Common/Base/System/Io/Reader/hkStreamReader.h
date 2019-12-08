/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKBASE_HKSTREAMREADER_H
#define HKBASE_HKSTREAMREADER_H

class hkBufferedStreamReader;
class hkSeekableStreamReader;

/// A generic interface to reading a stream of bytes.
/// The reader may optionally support mark/rewind or may be
/// wrapped as a child stream of an hkBufferedStreamReader.
/// Derived classes need only override isOk() and read(). Usually
/// readers which do not support buffering are wrapped in an
/// hkBufferedStreamReader.
class hkStreamReader : public hkReferencedObject
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_STREAM);

		hkStreamReader() {}
			/// Return false after we have tried to read past the end of file or some other error.
			/// Otherwise return true.
		virtual hkBool isOk() const = 0;

			/// Read 'nbytes' into the buffer 'buf'.
			/// Return the number of characters read or zero for end of file.
		virtual int read(void* buf, int nbytes) = 0;

			/// Skip nbytes bytes of input.
			/// Return the actual number of bytes skipped.
			/// The default implementation uses read().
		virtual int skip(int nbytes);

			/// Read at most n characters without changing the stream position.
			/// Returns the number of characters peeked.
		virtual int peek(void* buf, int n);
			
			/// Return a seekable stream if seeking is supported on this stream. By default not supported.
		virtual hkSeekableStreamReader* isSeekTellSupported() { return HK_NULL; }
};


class hkSeekableStreamReader : public hkStreamReader
{
	public:
	
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_STREAM);

		virtual hkSeekableStreamReader* isSeekTellSupported() { return this; }

			/// Parameter for seek method.
		enum SeekWhence { STREAM_SET=0, STREAM_CUR=1, STREAM_END=2 };

			/// Seek to offset from whence.
		virtual hkResult seek(int offset, SeekWhence whence) = 0;

			/// Get the current file offset if supported or -1 on error.
		virtual int tell() const = 0;
};

#endif //HKBASE_HKSTREAMREADER_H

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
