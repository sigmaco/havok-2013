/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_COMMAND_STREAM_H
#define HK_COMMAND_STREAM_H

#include <Common/Base/Container/BlockStream/hkBlockStream.h>
#include <Common/Base/DebugUtil/DeterminismUtil/hkCheckDeterminismUtil.h>

class hkOstream;


/// Base class of a command.
/// Commands are used so that different parts of Havok can communicate with each other. Each command has a primary and a
/// secondary type. This is done to allow for a more flexible way to configure and custom implement command dispatchers.
/// Commands should be stream-able between platforms of the same endianness like between PPU and SPU, therefore they
/// have no vtable.
class hkCommand
{
	public:

		/// Primary types are used
		enum PrimaryType
		{
			TYPE_DEBUG_DISPLAY,

			TYPE_PHYSICS_API,		///< like body::setVelocity
			TYPE_PHYSICS_INTERNAL,
			TYPE_PHYSICS_EVENTS,

			TYPE_DESTRUCTION_API,
			TYPE_DESTRUCTION_INTERNAL,
			TYPE_DESTRUCTION_EVENTS,

			TYPE_MAX
		};

		hkCommand( PrimaryType type, hkUint16 subType, int sizeInBytes );

		/// Called by block stream functions.
		HK_FORCE_INLINE int getSizeInBytes() const { return m_sizePaddedTo16; }

#if defined (HK_ENABLE_DETERMINISM_CHECKS)  
		HK_FORCE_INLINE int determinismGetSizeInBytes() const { return m_determinismSizeInBytes; }
#endif

	public:

		hkUint16 m_sizePaddedTo16;	///< Size in bytes rounded to the next multiple of 16 for performance.
		hkUint8  m_filterBits;		///< Allows for selectively executing commands.
		hkEnum<PrimaryType, hkUint8> m_primaryType;
		hkUint16 m_secondaryType;

#if defined (HK_ENABLE_DETERMINISM_CHECKS)  
		hkUint16 m_determinismSizeInBytes;		///< Real size in bytes needed for determinism checks.
#endif
};


/// Command dispatcher which dispatches commands using the secondary type.
class hkSecondaryCommandDispatcher : public hkReferencedObject
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE );

		virtual ~hkSecondaryCommandDispatcher() {}
		virtual void exec( const hkCommand& command ) = 0;

		/// optional print function for debugging
		virtual void print( const hkCommand& command, hkOstream& stream ) const {}
};


/// Implementation of hkCommandProcessor which streams into a block stream.
class hkBlockStreamCommandWriter HK_ON_CPU( :public hkSecondaryCommandDispatcher )
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(0);

		hkBlockStreamCommandWriter();

		/// Write a command.
		void exec( const hkCommand& command );
		
		// non virtual function of exec
		HK_ON_CPU(void append( const hkCommand& command ));
		
		/// Write a command.
		HK_FORCE_INLINE void* allocBuffer( int size );

	public:

		hkBlockStream<hkCommand>::Writer m_writer;
};

/// command dispatcher which dispatches using the primary type
class hkPrimaryCommandDispatcher
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE, hkPrimaryCommandDispatcher);

		hkPrimaryCommandDispatcher();		
		~hkPrimaryCommandDispatcher();

		void registerDispatcher( hkCommand::PrimaryType type, hkSecondaryCommandDispatcher* dispatcher );

		void exec( const hkCommand& command );

		void print( const hkCommand& command, hkOstream& stream );

	public:

		hkRefPtr<hkSecondaryCommandDispatcher> m_commandDispatcher[ hkCommand::TYPE_MAX ];
};


#include <Common/Base/Container/CommandStream/hkCommandStream.inl>

#endif //HK_COMMAND_STREAM_H

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
