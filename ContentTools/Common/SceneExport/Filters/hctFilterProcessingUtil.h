/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_SCENE_EXPORT_FILTERS_H
#define HK_SCENE_EXPORT_FILTERS_H

#include <ContentTools/Common/Filters/Common/FilterManager/hctFilterManagerInterface.h>
#include <Common/Base/Container/String/Deprecated/hkStringOld.h>
class hkPackfileData;

	/// Use an instance of this class to work with the filter manager DLL.
	/// The class provides methods to load the filter manager, open its UI, execute it and save and load options.
class hctFilterProcessingUtil
{
	public: 
			/// If you have an window handle, give it to the ctor so that any dialogs will be
			/// properly parented.
		hctFilterProcessingUtil(void* ownerWindowHandle = HK_NULL, hkBool interactive = true, const char* logFile = HK_NULL, unsigned int m_logVerboseLevel = 2, bool stdOuput = false); 
		
			/// Sets the handle to the owner window.
		void setOwnerHandle( void* handle ) { m_ownerHwnd = handle; }
		void* getOwnerHandle() const { return m_ownerHwnd; }

			/// Load the filter manager and the associated filters.
			/// The havokPath is the absolute path to the Havok directory where the
			/// filterManager DLL and the filters can be found, such as "d:/Programs/Maya6/Havok" etc.
		hkBool load( const char* havokPath );

			/// Merges the contents of another error handler's log with that of the filter managers.
			/// Needs to be called after the filter manager is loaded.
		void mergeErrors (const class hctSceneExportError* otherErrorHandler);

			/// Release the last setup filter manager.
			/// This will unload all DLLs (manager and also the filters) so all hkClass data
			/// that came from the filters will become invalid, so make sure to call process()
			/// before you call this.
		hkBool unload();

			/// Opens the filter manager in interactive mode.
			/// Returns whether changes to the configuration should be saved with the scene or not (depending on
			/// whether the user chose to do so).
		void openFilterManager( class hkRootLevelContainer& data, hkBool& shouldSaveConfigOut );	


			/// Process a given container of data (from file or mem) using Filters, in batch mode. All configurations
			/// will be processed.
			/// 
			/// If you don't give a memory tracker then the contents of the hkRootLevelContainer post process
			/// may be invalid as the internal tracker will have deleted the data. If you supply a tracker the
			/// hkRootLevelContainer will still have valid data (until you dealloc the tracker of course, or
			/// call release() ).
			///
			/// Filters can add arbitrary objects to a scene, some of which may be based on abstract
			/// classes, and so they will register those classes the class registry so that you can
			/// look up types based on the vtables etc. As such a class registry is required if you want to
			/// be able to use the scene fully afterwards (save it to file yourself for instance) but
			/// if you are just saving to file and have not added any abstract types to the hkRootLevelContainer
			/// already (by default the classes in hkSceneData are concrete) then supplying an
			/// empty class registry is fine.
		void processBatch ( class hkRootLevelContainer& data, hkBool& configModifiedOut, int configToRun = -1, bool allowModelessFilters = false); 
		hkRootLevelContainer* processBatchReturnData( hkRootLevelContainer& data, int configToRun, bool allowModelessFilters, hkPackfileData*& sceneCopyStorage);
	
			//
			// Access to options
			//

			/// Retrieves a version associated with the filter configuration
		unsigned int getCurrentOptionsVersion () const;

			/// Retrieve the size of the current options (filter setup). Use this in order to allocate memory before calling getOptions()
		int getOptionsSize() const; 

			/// Retrieves the current options (filter setup). The buffer to store them needs to be preallocated (use getOptionsSize() to query for its size).
			/// Use this, for example, if you want to store the setup with an asset (modeller file).
		void getOptions(void* buf) const; 

			/// Sets the options (filter setup). You can call this, for example, using saved option information you stored with the asset.
		void setOptions(const void* buf, int bufSize);

			/// Gets the result from the filter processing, 0 = success, 1 = success with warnings, 2 = error
		int getResult() const;

			/// Get the path used to load the filters
		const char* getFilterManagerPath() const;

			/// Get the path used to load attribute descriptions (for processing)
		const char* getAttributeProcessingPath() const;

			/// Get the path used to load attribute selections
		const char* getAttributeSelectionPath() const;

			/// Registers a thread callback. Check hctFilterManagerInterface::registerThreadCallback() for details).
		void registerThreadCallback( const hctFilterThreadCallback* cb );
		static hctFilterThreadCallback* getDefaultThreadCallback();

			/// Will be null until load() is called.
		hctFilterManagerInterface* getFilterManagerInterface();
	
			// Load all DLLs we may want. This will cause them to cache and be much faster to load
			// when actually required.
		static void startBackgroundFilterLoad(const char* havokPath);
		static void waitOnBackgroundFilterLoad();

	private:

		void registerDefaultThreadCallback ();
	
		class hctFilterManagerDll* m_filterManagerDll;
		class hctFilterManagerInterface* m_filterManager;

		void* m_ownerHwnd;
		hkStringOld m_filterManagerPath;

		mutable hkStringOld m_attributeProcessingPath;
		mutable hkStringOld m_attributeSelectionPath;

		hkBool m_interactive;
		const char* m_logFileName;
		unsigned int m_logVerboseLevel;
		bool m_stdOutput;
};

#endif // HK_SCENE_EXPORT_FILTERS_H

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
