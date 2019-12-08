/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKX_SCENE_DATA_CONTEXT_H
#define HKX_SCENE_DATA_CONTEXT_H

#include <Common/Visualize/hkProcessContext.h>

#define HK_SCENE_DATA_CONTEXT_TYPE_STRING "SceneData"

class hkxScene;

	/// Callback interface for hkxSceneDataContext.
class hkxSceneDataContextListener
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_TOOLS, hkxSceneDataContextListener);

			/// Empty destructor
		virtual ~hkxSceneDataContextListener() {}

			/// Called when a scene is added to the context
		virtual void sceneAddedCallback( hkxScene* scene ) {}
			/// Called when a scene is removed from the context
		virtual void sceneRemovedCallback( hkxScene* scene ) {}		
};

	/// Context that controls what scene data viewers are registered and how they access hkxScene information.
class hkxSceneDataContext: public hkReferencedObject,
						   public hkProcessContext						  
{
	public:	

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_TOOLS);

			/// Initializes an empty context.
		hkxSceneDataContext();
			/// Destroys the context and removes all scenes.
		virtual ~hkxSceneDataContext();

			/// Register all scene data viewers
		static void HK_CALL registerAllSceneDataViewers();

			/// hkProcessContext interface
		virtual const char* getType(); 

			/// Adds a scene to the context.
		void addScene( hkxScene* scene );
			/// Removes a scene from the context.
		void removeScene( hkxScene* scene );
			/// Gets a list of scenes in the context.
		const hkArray<hkxScene*>& getScenes() const;		

			/// Adds a listener to the context
		void addListener( hkxSceneDataContextListener* listener );
			/// Remove a listener from the context
		void removeListener( hkxSceneDataContextListener* listener );

			/// Add a texture search path for finding non-embedded textures
		void addTextureSearchPath(const char* path);
			/// Clear texture search paths
		void clearTextureSearchPaths();
			/// Get the current texture path array
		const hkArray<const char*>& getTextureSearchPaths() const;
			/// Set whether or not to allow mipmapping
		void setAllowTextureMipmap( hkBool on );
			/// Get whether or not to allow mipmapping
		bool getAllowTextureMipmap();

	protected:

			/// Scenes in this context
		hkArray<hkxScene*> m_scenes;

			/// Listeners in this context
		hkArray<hkxSceneDataContextListener*> m_listeners;
		
			/// Texture search paths
		hkArray<const char*> m_searchPaths;

			/// Allow mipmaps
		hkBool m_allowMipmap;
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
