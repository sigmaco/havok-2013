/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKFILTERSCENE_HKFILTERSCENEEXECUTECOMMANDOPTIONS_HKCLASS_H
#define HKFILTERSCENE_HKFILTERSCENEEXECUTECOMMANDOPTIONS_HKCLASS_H

/// hctExecuteCommandOptions meta information
extern const class hkClass hctExecuteCommandOptionsClass;

/// Describes the execute command options.
class hctExecuteCommandOptions
{
public:

	HK_DECLARE_REFLECTION();
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_EXPORT, hctExecuteCommandOptions);

	/// Default constructor
	hctExecuteCommandOptions() :
			m_commands(HK_NULL) { }

		/// Finish constructor
		hctExecuteCommandOptions(hkFinishLoadedObjectFlag f) { }

		//
		// Members
		//
public:

	/// The commands to execute. Commands are on a separate line and are separated by '\n'.
	char* m_commands;
};

#endif // HKFILTERSCENE_HKFILTERSCENEEXECUTECOMMANDOPTIONS_HKCLASS_H

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
