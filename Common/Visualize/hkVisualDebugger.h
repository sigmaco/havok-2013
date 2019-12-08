/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_VISUALIZE__VISUAL_DEBUGGER
#define HK_VISUALIZE__VISUAL_DEBUGGER

#include <Common/Base/System/Stopwatch/hkStopwatch.h>
#include <Common/Visualize/hkDebugDisplay.h>
#include <Common/Visualize/hkProcessContext.h>

class hkStreamReader;
class hkStreamWriter;

static const hkUint32 HK_VISUAL_DEBUGGER_DEFAULT_PORT = 25001;

	/// Information about connected Vdb clients.
struct hkVisualDebuggerClient
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_UTILITIES, hkVisualDebuggerClient );

		// The socket connection to the Vdb client
	class hkSocket* m_socket;

		// A handler for the currently enabled hkProcesses for this Vdb client
	class hkServerProcessHandler* m_processHandler;
};

	/// Object tracking (objects that can be inspected with the hkInspectProcess, which must have a hkClass).
	/// These tracked objects show up in the Vdb under Remote Object Inspection
struct hkVisualDebuggerTrackedObject
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_UTILITIES, hkVisualDebuggerTrackedObject );

	void* m_ptr;
	const class hkClass* m_class; 
	hkUlong m_tag;
};

	/// This stores a chunk of Vdb data
struct hkVdbChunk
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_UTILITIES, hkVdbChunk );

	hkInt32 m_size;
	hkInt8 m_type;
	char m_data[1];

private:

	hkVdbChunk(); // not implemented, used only as a interface to cast the incoming buffer to
	~hkVdbChunk();  
};


	/// Callback for handling Remote Object Inspection protocol.
	/// Class will be null on remove callback ( when 'added' == false )
typedef void (HK_CALL* hkVisualDebuggerTrackedObjectCallback)( void* ptr, const hkClass* klass, hkBool wasAdded, hkUlong tagId, void* userCallbackHandle );

	/// Visual Debugger server interface.
class hkVisualDebugger : public hkReferencedObject
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_VDB);

			/// Creates a visual debugger for a given set of contexts.
			/// A context is a container for interesting game data such
			/// as hkpWorlds or user / animation data.
			/// This ctor will set the context owner as this VDB (assumes only one VDB).
			/// It will also register common hkProcesses and enable some default processes
			/// (see addDefaultProcess).
		hkVisualDebugger( const hkArray<hkProcessContext*>& contexts, const class hkVtableClassRegistry* classReg = HK_NULL );

			/// Instructs the visual debugger to start listening for client connections
			/// from the given TCP/IP port number. For the server to actually work
			/// hkVisualDebugger::step must be called.
		void serve(int listenPort = HK_VISUAL_DEBUGGER_DEFAULT_PORT);

			/// Instructs the visual debugger to start capturing the output of all
			/// of the default viewers to the specified filename. Note you do not
			/// have to call hkVisualDebugger::serve this is completely independent
			/// and can be used without any network serving.
		void capture(const char* captureFilename);

			/// Instructs the visual debugger to create a connection to a memory stream. After
			/// connected the debugger will communicate over these memory streams as if they
			/// were a network connection.
		void capture(hkMemoryTrack* outgoingMemory, hkMemoryTrack* incommingMemory);

			/// End (all) captures to file.
		void endCapture();

			/// Shutdown the VDB. Can call shutdown and then serve again later.
			/// It removes all clients and shuts down the server.
			/// Shutdown is called automatically by the dtor, but is safe to call more than once.
		void shutdown();

			/// Clear out the default and required process lists
		void clearDefaultAndRequiredProcesses();

			/// Add a process to the list of default processes. All processes in this
			/// list will be selected by a client when a new connection is established.
		void addDefaultProcess(const char* processName);

			/// Removes a viewer from the list of default viewers. If a viewer is not
			/// in this list it will not be selected by a client when a new connection
			/// is established.
		void removeDefaultProcess(const char* processName);

			/// Immediately create this process on the server when a client connects,
			/// don't wait for a client to request it (as through Viewer selection).
		void addRequiredProcess(const char* processName);

			/// Added an object (with associated class) to the top level
			/// objects that can be inspected by clients.
			/// Group string currently ignored.
		void addTrackedObject(void* obj, const hkClass& klass, const char* group, hkUlong tagId );

			/// Removes an object from the top level
			/// objects that can be inspected by clients (removed by listeners
			/// in the code that added the object on deletion usually).
		void removeTrackedObject(void* obj);

			/// Creates any required or default processes
		void createRequiredAndDefaultProcessList( hkVisualDebuggerClient& vdbClient, hkStringBuf& viewerNames );

			/// Advances all clients by frameTimeInMs. If no value is passed in, then it will automatically
			/// be computed as the difference from the last step.  This call is essential for all
			/// hkVisualDebugger operations such as client connection/creation, sending data,
			/// receiving data, etc.
		virtual void step(hkReal frameTimeInMs = 0);

			/// Called internally to poll for new clients.
		virtual void pollForNewClients();

			/// Destructor.
		virtual ~hkVisualDebugger();

			/// Get the contexts that the Processes can run under
			/// such as a context that lists hkpWorlds, or one that has animation data for instance.
		const hkArray<hkProcessContext*>& getContexts() { return m_contexts; }

			/// Gets a list of process used by clients of the server.
		void getCurrentProcesses( hkArray< class hkProcess* >& process ) const;
		
			/// Searches for a process in the current process list by name. Returns HK_NULL if not found.
		hkProcess* getCurrentProcessByName( const char* name ) const;		

		void addContext( hkProcessContext* context );
		void removeContext( hkProcessContext* context );

			/// Internal used by the inspection process:
			/// Get the list of tracked objects. Use add and remove tracked object to change (e.g., upon deletion)
		const hkArray<hkVisualDebuggerTrackedObject>& getTrackedObjects() const { return m_trackedObjects; }
		void addTrackedObjectCallback( hkVisualDebuggerTrackedObjectCallback callback, void* userHandle);
		void removeTrackedObjectCallback( hkVisualDebuggerTrackedObjectCallback callback );
		inline const hkVtableClassRegistry* getClassReg() const { return m_classReg; }
		
			/// By default ::step will use the wall clock time if frameTimeInMs is equal 
			/// to 0.  Call disableOverrideFrameTimeIfZero to disable this behavior and use
			/// the value of frameTimeInMs for the frame time.
		void disableOverrideFrameTimeIfZero() { m_overrideFrameTimeIfZero = false; }
		void SupressPollForNewClient(bool val);
	protected:

		void deleteClient(int i);
		void createClient( hkSocket* socket, hkStreamReader* reader, hkStreamWriter* writer );
		void writeStep(int i, float t);  // step cmd to given client id.

		// Server socket (we listen for new Clients on it)
		hkSocket* m_server;
		bool s_SuppressPollForNewClients;

		// All clients get a separate process handler.
		hkArray<hkVisualDebuggerClient> m_clients; 
		hkArray<hkProcessContext*> m_contexts;

		// Master list of currently tracked objects. Any changes raise the callbacks
		hkArray<hkVisualDebuggerTrackedObject> m_trackedObjects;
		hkArray<hkVisualDebuggerTrackedObjectCallback> m_trackCallbacks;
		hkArray<void*> m_trackCallbackHandles;
		const hkVtableClassRegistry* m_classReg;
		
			/// Processes that will always service a Client (auto created)
		hkArray<hkStringPtr> m_defaultProcesses;
			
			/// Processes that will be created without any handshaking required (create instead of select)
		hkArray<hkStringPtr> m_requiredProcesses;
		
		hkBool m_amTimingFrame;
		hkStopwatch m_frameTimer;
		hkBool m_overrideFrameTimeIfZero;
};

#endif // HK_VISUALIZE__VISUAL_DEBUGGER

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
