/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#if !defined(HK_DEBUG_COMMANDS)
#define HK_DEBUG_COMMANDS

#include <Common/Base/Container/CommandStream/hkCommandStream.h>
#include <Common/Base/Types/Color/hkColor.h>



class hkDebugCommand: public hkCommand
{
public:
	enum
	{
		CMD_DEBUG_LINE,
	};

	hkDebugCommand( hkUint16 subType, int sizeInBytes ): hkCommand(TYPE_DEBUG_DISPLAY, subType, sizeInBytes )
	{
	}
};


/// A list of default command functions to be used in the header of a command (non virtual).
#define HK_DEFAULT_DEBUG_COMMAND_FUNCTIONS \
	void printCommand  (hkOstream& stream) const

struct hkEmptyDebugCommand: public hkDebugCommand
{
	hkEmptyDebugCommand( ): hkDebugCommand( CMD_DEBUG_LINE, sizeof(*this)){ ; }
	HK_FORCE_INLINE void printCommand  (hkOstream& stream) const {}
	HK_FORCE_INLINE void checkIsEmptyCommand() const {}	// This allows the compiler to check that all commands are dispatched
};



#define HK_DECLARE_DEBUG_COMMAND_DISCRIMINATOR( TYPE, ID)	\
	template <     >	struct hkDebugCommandTypeDiscriminator<hkDebugCommand::ID>{ typedef TYPE CommandType; }

template <int X>	struct hkDebugCommandTypeDiscriminator			 { typedef hkEmptyDebugCommand CommandType; };


struct hkDebugLineCommand: public hkDebugCommand
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_PHYSICS, hkDebugLineCommand);
	hkDebugLineCommand( hkVector4Parameter start, hkVector4Parameter end, hkColor::Argb color ):
		hkDebugCommand( CMD_DEBUG_LINE, sizeof(*this)){ m_start = start; m_end = end; m_color = color; }

	hkDebugLineCommand() : hkDebugCommand( CMD_DEBUG_LINE, sizeof(*this) ) {}

	HK_DEFAULT_DEBUG_COMMAND_FUNCTIONS;

	hkColor::Argb m_color;
	hkVector4 m_start;
	hkVector4 m_end;
};
HK_DECLARE_DEBUG_COMMAND_DISCRIMINATOR( hkDebugLineCommand, CMD_DEBUG_LINE );


class hkDebugCommandProcessor: public hkSecondaryCommandDispatcher
{
	public:
		HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE);

		hkDebugCommandProcessor(){}

		/// dispatch commands
		virtual void exec( const hkCommand& command );

		virtual void print( const hkCommand& command, hkOstream& stream ) const ;
};


#endif	//HK_DEBUG_COMMANDS

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
