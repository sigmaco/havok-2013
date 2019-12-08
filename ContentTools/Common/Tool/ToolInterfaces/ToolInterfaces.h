/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#pragma once

namespace Havok
{
	using namespace Graphics;

	namespace Tool
	{
		public ref class VersionCheck
		{
		public: static void getVersionInfo(System::String^% interfaceVersion, System::String^% havokSdkVersion );
		};

		/// If an impl of this interface is found, it will look after the mem sub system etc (Havok base system init and quit)
		public interface class IBaseSystem
		{
			void initBaseSystem(System::IntPtr baseInfo, System::IntPtr graphicsInfo); // this is rarely null, usually the base system the Tool is using. Just call normally
			void pushErrorHandler(System::IntPtr errorInstance); // can normally only push one new error handler at a time before a pop (1 elem stack)
			void popErrorHandler();
			void getVersionInfo(System::String^% interfaceVersion, System::String^% havokSdkVersion );
			void quitBaseSystem(); // just call hkBaseSystem::quit normally
		};

		public interface class IConsole
		{
			enum struct MessageType
			{
				REPORT,
				WARNING,
				ERROR
			};

			void addMessage( MessageType t, System::String^ message );			
		};


		public interface class IPlugin
		{
		
			void init();
			bool step(float dt); // returns true if did anything for step
			bool isPlaying();

			void setContentsFromMemory(System::IntPtr root /* hkRootLevelContainer* */, System::IntPtr vtableReg, System::Boolean copyData, System::Boolean allowInstances); // if dragIn, will allow instances so will Add
			void setContentsFromFile(System::String^ path, bool dragIn, int dragX, int dragY, bool prompt); // if dragIn, will ask how to add it
			void updateContentsFromPackfile(array< System::Byte >^ data); // -> update preview from remote asset
			
			void serveContentsToHost(System::String^ hostName, int port, System::Windows::Forms::Label^ statusField, System::Windows::Forms::Form^ form);   // -> update remote demo with preview assets
			
			System::IntPtr getObjectOfType( System::IntPtr klass );

			enum struct ExportFormat
			{
				XML,
				HKT,
				HKX
			};

			value class PlatformLayout
			{
			public:
				System::Int32 m_bytesInPointer;
				System::Int32 m_littleEndian;
				System::Int32 m_reusePaddingOptimization;
				System::Int32 m_emptyBaseClassOptimization;
			};

			void saveContentsToFile(System::String^ fileName, ExportFormat format, PlatformLayout layout, System::Boolean writeMeta );   

			void startDragDrop( System::String^ filename ); // can be >1 start before end (multi file drop)
			void endDragDrop(); // end all current drops. Should have called setContentsFromFile before now.

			void createFirstPersonController(hkgVector3CLR^ pos, hkgVector3CLR^ dir, hkgVector3CLR^ up);
			void deleteFirstPersonController();

			void quit();
		};

		// Display context
		public ref struct PickInfo
		{
			PickInfo();

			hkgDisplayObjectCLR^ m_object; // always not null
			int m_faceSetIndex; // which set of faces (split by material etc normally), -1 for none
			int m_geomIndex;	// the instance index for instanced objects
			
			hkgFaceSetCLR^ getPickedFaceSet();
			int m_facePrimIndex; // which set of primitives (tri strip etc) the face is in
			int m_faceIndex; // which face was picked in that primitive, -1 for none
			
			hkgFaceSetPrimitiveCLR^ getPickedPrimitive();
			array<int, 1>^ m_vertexIndices; // which vertices that make up the picked face (index into vbufer), 3 elems

			hkgVector3CLR^ m_localPos;
			int m_closestVert; // 0,1, or 2,   into the m_vertexIndices. -1 if not set.
		};

		public interface class IPluginDisplay
		{
			void preWorldRender( hkgViewportCLR^ v );
			void postWorldRender( hkgViewportCLR^ v );
			
			void setContext( hkgDisplayWorldCLR^ world, hkgDisplayContextCLR^ ctx, hkgWindowCLR^ window );

			hkgDisplayObjectCLR^ getSelectedDisplayObject();
			void objectPicked( PickInfo^ obj, hkgVector3CLR^ worldPos);
			void objectMoved( hkgVector3CLR^ worldPos);
			void objectReleased( );		
		};

		public interface class IPluginOwner
		{
			// get array of all IPlugins
			::cli::array<IPlugin^>^ getAllPlugins();
		};

		public interface class IPluginUI
		{
			System::String^ getName();

			void setPluginOwner( IPluginOwner^ owner );
			void setParentControl( System::Windows::Forms::Control^ parent, IConsole^ errorConsole );
			void setParentMenu( System::Windows::Forms::MenuStrip^ parent );
			void setNavigationToolBar( System::Windows::Forms::ToolStrip^ navigationToolBar );

			void restoreDefaultProperties();
		};

		// Tweaker

		public value struct HavokReflectedObject
		{
			System::IntPtr instance;
			System::IntPtr klass;
		};

		public interface class IDataSource
		{
			void getDataAndClassForObject( PickInfo^ currentDisplayObject, HavokReflectedObject% obj); 

			void verifyClass( System::IntPtr klass); // more for remote tweaking (recursion down to classes we don't know etc), make sure we load that klass.
			void commit( HavokReflectedObject origObject, System::IntPtr newData );
		};

		public interface class IDataEditor
		{
			void setDataSource( IDataSource^ dataSource );
			void editData( HavokReflectedObject obj, System::String^ name ); // should copy the data, edit the values in it, and if ok by user, use commit in the datasource
		};
	}
}

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
