/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_LOCAL_FRAME_VIEWER_H
#define HKP_LOCAL_FRAME_VIEWER_H

#include <Physics2012/Utilities/VisualDebugger/Viewer/Dynamics/hkpWorldViewerBase.h>
#include <Physics2012/Dynamics/World/Listener/hkpWorldPostSimulationListener.h>

class hkpWorld;
class hkLocalFrame;

/// Shows the local frames of all rigid bodies added to the world.
class hkpRigidBodyLocalFrameViewer : public hkpWorldViewerBase, protected hkpWorldPostSimulationListener						   
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_TOOLS);
			
			/// Create the 
		static hkProcess* HK_CALL create(const hkArray<hkProcessContext*>& contexts);

			/// Registers the hkpRigidBodyLocalFrameViewer with the hkProcessFactory.
		static void HK_CALL registerViewer();

			/// Gets the tag associated with this viewer type
		virtual int getProcessTag() HK_OVERRIDE { return m_tag; }

			/// Initialize
		virtual void init();

			/// The name of the viewer shown in the VDB
		static inline const char* HK_CALL getName() { return "Physics Local Frames"; }
	
	protected:

			/// Initializes the viewer
		hkpRigidBodyLocalFrameViewer(const hkArray<hkProcessContext*>& contexts);
			/// Destructs the viewer
		~hkpRigidBodyLocalFrameViewer();

			/// Draws the local frames on all rigid bodies in the world.
		virtual void postSimulationCallback( hkpWorld* world );

		virtual void worldAddedCallback( hkpWorld* world );

		virtual void worldRemovedCallback( hkpWorld* world );

			/// Unique ID for the viewer
		static int m_tag;
	
	public:
		
			/// Scale to draw the local frame
		static hkReal m_scale;
};

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
