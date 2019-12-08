/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#ifndef HK_BLOCKSTREAM_H
#define HK_BLOCKSTREAM_H

#include <Common/Base/Container/BlockStream/hkBlockStreamBaseBlock.h>
#include <Common/Base/Container/BlockStream/hkBlockStreamBaseStream.h>
#include <Common/Base/Container/BlockStream/hkBlockStreamBaseIterators.h>
#include <Common/Base/Container/BlockStream/hkBlockStreamBaseRange.h>

/// A virtual memory stream of data.
/// Rules:
///    - Structures/Chunks of different sizes can be put into a block stream.
///    - A block stream reader has a peek method, which allows you to access the next block of bytes
///      before consuming them.
///    - The writer just reserves bytes, so you can put data into the reserved area. 
///      Any time later you can advance the stream by up to the reserved number of bytes.
template<typename T>
class hkBlockStream: public hkBlockStreamBase::Stream
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE, hkBlockStream );


		/// Constructor.
		HK_FORCE_INLINE hkBlockStream( Allocator* tlAllocator, bool zeroNewBlocks = false );

		/// Constructor. You need to manually call initBlockStream() before you can use this class.
		HK_FORCE_INLINE hkBlockStream();

		/// Destructor.
		HK_FORCE_INLINE ~hkBlockStream();

		/// Append block stream to this stream and delete inStream.
		void clearAndSteal( Allocator* tlAllocator, hkBlockStream<T>* inStream );


		/// Writes to a stream.
		class Writer : public hkBlockStreamBase::Writer
		{
			public:

				template <typename T2>
				HK_FORCE_INLINE T2*	write16( const T2* HK_RESTRICT data, int numBytes );

				/// For CW, the overload must come after the template declaration
				/// Write \a numBytes of \a data to the stream. \a numBytes has to be a multiple of 16.
				HK_FORCE_INLINE T*	write16( const T* HK_RESTRICT data, int numBytes );

				/// Write \a data to a stream if \a data has getSizeInBytes() implemented and its size is a multiple
				/// of 16.
				HK_FORCE_INLINE T*	write16( const T* HK_RESTRICT data );

				/// Write \a numBytes of \a data to the stream.
				/// If it is, use write16() instead.
				HK_FORCE_INLINE T*	write( const T* HK_RESTRICT data, int numBytes );

				/// Write \a data to a stream if \a data has getSizeInBytes() implemented and its size is NOT a
				/// multiple of 16.
				HK_FORCE_INLINE T*	write( const T* HK_RESTRICT data );
			
				/// Advance by \a currentNumBytes in the stream and return a pointer to storage space where
				/// \a reservedNumBytes can be written to.
				HK_FORCE_INLINE	T* advanceAndReserveNext( int currentNumBytes, int reservedNumBytes );

				/// Reserve \a numBytes in the stream. Returns a pointer where data can be written to.
				/// This method does not advance the stream automatically, you have to call advance() manually
				/// afterwards.

				/// Reserve in the stream a number of bytes equal to the sizeof of the function's template parameter. 
				/// Returns a pointer where data can be written to.
				/// This method does not advance the stream automatically, you have to call advance() manually
				/// afterwards.
				template<typename T2>
				HK_FORCE_INLINE	T2* reserve();

				/// Reserve numBytes in the stream. Returns a pointer where data can be written to.
				/// This method does not advance the stream automatically, you have to call advance() manually
				/// afterwards.
				template<typename T2>
				HK_FORCE_INLINE	T2* reserve( int numBytes );
			
				HK_FORCE_INLINE	T* reserve( int numBytes );

				/// Returns true if the writer is attached to a stream.
				HK_FORCE_INLINE bool isValid();
		};
		
		/// Reads from a stream.
		class Reader: public hkBlockStreamBase::Reader
		{
			public:

				/// Advance and access the next element, assumes the current entry is valid
				template <typename T2>
				HK_FORCE_INLINE const T2* advanceAndAccessNext( int thisElemSize );

				/// Advance and access the next element, assumes the current entry is valid
				HK_FORCE_INLINE	const T* advanceAndAccessNext( int thisElemSize );

				/// Advance and access the next element if data has getSizeInBytes() implemented
				HK_FORCE_INLINE const T* advanceAndAccessNext( const T* HK_RESTRICT data );

				/// Advance and access the next element, assumes the current entry is valid
				template <typename T2>
				HK_FORCE_INLINE	const T2* advanceAndAccessNext();

				/// Access the current element;
				template <typename T2>
				HK_FORCE_INLINE	const T2* access();

				/// Access the current element;
				HK_FORCE_INLINE	const T* access();
		};

		/// A reader which allows you to modify the data while reading
		class Modifier: public hkBlockStreamBase::Modifier
		{
			public:
				template <typename T2>
				HK_FORCE_INLINE	T2* advanceAndAccessNext( int thisElemSize );

				HK_FORCE_INLINE	T* advanceAndAccessNext( int thisElemSize );

				template <typename T2>
				HK_FORCE_INLINE	T2* access();

				HK_FORCE_INLINE	T* access();
		};

		/// A reader, which frees the memory once it is fully read.
		/// You can run different Consumers using different ranges of the same block stream,
		/// even in multitple threads.
		/// Be default the block stream becomes useless as soon as one consumer worked on it.
		/// If you want to continue to use the block stream you have to:
		///    - finalize with a call to hkBlockStream::fixupConsumedBlocks(). This will free completely unused blocks
		class Consumer: public hkBlockStreamBase::Consumer
		{
			public:

				/// Override to avoid calling the wrong function
				HK_FORCE_INLINE void setToRange( Allocator* allocator, const hkBlockStreamBase::Range* range ){ HK_ASSERT( 0x0f345467, false ); }	// use the other version

				/// Sets the consumer to a subrange of a stream
				HK_FORCE_INLINE void setToRange( Allocator* allocator, hkBlockStream<T>* stream, hkBlockStream<T>* streamPpu, const hkBlockStreamBase::Range* range );

				/// Get the current element.
				HK_FORCE_INLINE	const T* access();

				/// advance and access the next element, assumes the current entry is valid
				HK_FORCE_INLINE	const T* consumeAndAccessNext( int thisElemSize );

				/// Read from a stream if data has getSizeInBytes() implemented
				HK_FORCE_INLINE const T* consumeAndAccessNext( const T* HK_RESTRICT data );
		};
};

#include <Common/Base/Container/BlockStream/hkBlockStream.inl>
#endif

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
