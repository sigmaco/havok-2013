/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_UTILITIES2_WINDING_VIEWER_H
#define HK_UTILITIES2_WINDING_VIEWER_H

#include <Physics2012/Utilities/VisualDebugger/Viewer/Dynamics/hkpWorldViewerBase.h>
#include <Physics2012/Dynamics/World/Listener/hkpWorldPostSimulationListener.h>

class hkDebugDisplayHandler;
class hkpWorld;
class hkListener;

	/// A class for viewing welding data
class hkpInconsistentWindingViewer : public hkpWorldViewerBase, public hkpWorldPostSimulationListener, protected hkpEntityListener
{
	public:
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_TOOLS);


		/// Creates a hkpConstraintViewer.
		static hkProcess* HK_CALL create( const hkArray<hkProcessContext*>& contexts );

		/// Registers the hkpConstraintViewer with the hkProcessFactory.
		static void HK_CALL registerViewer();

		/// Get the name of this viewer
		static inline const char* HK_CALL getName() { return "InconsistentWindingViewer"; }


		/// Gets the tag associated with this viewer type
		virtual int getProcessTag( void ) { return m_tag; }

		void postSimulationCallback(hkpWorld* world);

		virtual void init();
		
	protected:
		hkpInconsistentWindingViewer(const hkArray<hkProcessContext*>& contexts);
		virtual ~hkpInconsistentWindingViewer();

		virtual void worldAddedCallback( hkpWorld* world );
		virtual void worldRemovedCallback( hkpWorld* world );

		virtual void entityAddedCallback( hkpEntity* entity );

		static int m_tag;
};

#endif	// HK_UTILITIES2_WINDING_VIEWER_H

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
