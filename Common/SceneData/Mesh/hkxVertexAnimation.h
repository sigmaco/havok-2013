/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKSCENEDATA_MESH_HKXVERTEXBUFFERANIMATION__H
#define HKSCENEDATA_MESH_HKXVERTEXBUFFERANIMATION__H

#include <Common/SceneData/Mesh/hkxVertexBuffer.h>
#include <Common/Base/Container/BitField/hkBitField.h>

class hkxVertexAnimation : public hkReferencedObject
{
  //+vtable(true)
  //+version(0)
  public: 
    
    HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_SCENE_DATA );
    HK_DECLARE_REFLECTION();

    inline hkxVertexAnimation();
    inline hkxVertexAnimation( hkFinishLoadedObjectFlag f );

    hkReal m_time; // in seconds, so (0..hkxScene::m_sceneLength scale normally)
    hkxVertexBuffer m_vertData; // vertex sub set (both in #num verts and in what is animated)
    hkArray<hkInt32> m_vertexIndexMap; // index in m_vertData back to original, as very rarely change all verts per frame. If becomes large mem hit, can set this to size 0 which would indicate a 1:1 map for above vert data

    struct UsageMap 
    { 
      HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_SCENE_DATA, UsageMap );
      HK_DECLARE_REFLECTION();

      hkEnum<hkxVertexDescription::DataUsage, hkUint16> m_use;
      hkUint8 m_useIndexOrig;  // origVertxBuffer->getElementDecl( m_use, m_useIndexOrig );
      hkUint8 m_useIndexLocal; // m_vertData->getElementDecl( m_use, m_useIndexLocal );
    };
    hkArray<UsageMap> m_componentMap;
};

/// A util class to keep track of all applied partial vertex anims on a vert buffer.
/// It does no interpolation, so is just a raw state as per last applied keys (used in exporters to see if new key needed per vert, etc.).
class hkxVertexAnimationStateCache : public hkReferencedObject
{
  public:
    HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_SCENE_DATA );

    // Will copy the vb assumming you will be animating it
    hkxVertexAnimationStateCache(hkxVertexBuffer* b, bool alterInPlace );
    hkxVertexAnimationStateCache(const hkxVertexBuffer* b);

    virtual ~hkxVertexAnimationStateCache();

     // will take all new vert data from anim and alter the cached vb with it
    void apply(const hkxVertexAnimation* anim, float interplotate = 0.f);

	 // reset the cache back to base state
	void reset(hkxVertexBuffer* b, bool alterInPlace);

      // get the state. You can assume it has identical layout to the original.
    inline const hkxVertexBuffer& getState() const { return *m_state; }
    inline hkReal getKeyTime() const { return m_curKeyTime; }

    inline const hkBitField& getTouchedData() const { return m_alteredVerts; }

  protected:

    void copyState(const hkxVertexBuffer* vb);

    hkxVertexBuffer* m_state;
    hkBitField m_alteredVerts;

    hkBool m_ownState;
    hkReal m_curKeyTime;
    
};
#include <Common/SceneData/Mesh/hkxVertexAnimation.inl>

#endif //HKSCENEDATA_MESH_HKXVERTEXBUFFERANIMATION__H

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
