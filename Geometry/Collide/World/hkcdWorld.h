/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_HAVOK_ASSEMBLY_EXCLUDE_FILE

#ifndef HKCD_WORLD_H
#define HKCD_WORLD_H

#include <Common/Base/Types/hkHandle.h>
#include <Common/Base/Types/Geometry/Aabb/hkAabb.h>
#include <Common/Base/Container/FreeListArray/hkFreeListArray.h>

#include <Geometry/Internal/Types/hkcdRay.h>

class hkcdWorld : public hkReferencedObject
{
	public:

	HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_COLLIDE);

	//
	// Forward decl.
	//

	struct ICodec;

	//
	// Typedefs.
	//

	typedef hkUint32	DataType;

	//
	// Handles.
	//

	/// Object handle
	HK_DECLARE_HANDLE(HObject, hkUint32, 0);

	/// Group handle
	HK_DECLARE_HANDLE(HGroup, hkUint32, 0);

	//
	// Types.
	//
	
	/// Object
	struct Object
	{
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_COLLIDE, Object);

		hkAabb		m_previousAabb;	///< Previous AABB.
		hkUint32	m_leaf;			///< Leaf handle.
		DataType	m_data;			///< User data.
		HGroup		m_group;		///< Group.
	};

	/// Group
	struct Group
	{
		enum AabbType
		{
			EMPTY_AABB,
			CURRENT_AABB,
		};

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_COLLIDE, Group);

		const char*	m_name;			///< Group name.
		ICodec*		m_codec;		///< Group CODEC.
		HGroup		m_next;			///< Next valid group.
		HGroup		m_prev;			///< Previous valid group.
		AabbType	m_aabbType;		///< Previous AABB type.
		
		HK_ALIGN16(hkUint8	m_tree[256]);	///< Internal tree.
	};

	/// GroupSet
	struct GroupSet
	{
		HK_FORCE_INLINE			GroupSet() : m_groups(HK_NULL), m_numGroups(0) {}
		HK_FORCE_INLINE			GroupSet(const GroupSet& other) { operator=(other); }
		HK_FORCE_INLINE			GroupSet(HGroup hgroup) : m_hgroup(hgroup), m_groups(&m_hgroup), m_numGroups(1) {}
		HK_FORCE_INLINE			GroupSet(const HGroup* groups, int numGroups) : m_groups(groups), m_numGroups(numGroups) {}

		HK_FORCE_INLINE int			getSize() const { return m_numGroups; }
		HK_FORCE_INLINE HGroup		operator[](int i) const { HK_ASSERT3(0x828B509A, 0 <= i && i < m_numGroups, "Index out of range ("<<i<<")"); return m_groups[i]; }
		HK_FORCE_INLINE GroupSet&	operator=(const GroupSet& other);

	private:
		
		HGroup			m_hgroup;
		const HGroup*	m_groups;
		int				m_numGroups;
	};

	//
	// Interfaces.
	//

	/// ICodec : Interface used interpret object data on a per-group basis.
	struct ICodec
	{
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_COLLIDE, ICodec);

		virtual			~ICodec() {}
		virtual void	getAabbs(const DataType* objectsData, int numObjects, hkAabb* aabbsOut) const=0;
	};

	/// Unary query processor interface.
	struct IUnaryProcessor
	{
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_COLLIDE, IUnaryProcessor);

		virtual				~IUnaryProcessor()	{}
		virtual	void		process(const DataType* xs, int count)=0;
	};

	/// Linear cast query processor interface.
	struct ILinearCastProcessor
	{
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_COLLIDE, ILinearCastProcessor);

		virtual				~ILinearCastProcessor()	{}
		virtual	void		process(DataType x, const hkcdRay& ray)=0;
	};

	/// Binary query processor interface.
	struct IBinaryProcessor
	{
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_COLLIDE, IBinaryProcessor);

		virtual				~IBinaryProcessor()	{}
		virtual	void		process(const DataType* xs, const DataType* ys, int count)=0;
	};
	
	//
	// World.
	//


	/// Constructor.
	hkcdWorld();
	
	/// Destructor.
	~hkcdWorld();

	/// Reset world.
	void		reset();


	//
	// Groups.
	//


	/// Create a new group.
	HGroup		createGroup(ICodec* codec, Group::AabbType aabbType, const char* name = "Unnamed group");

	/// Destroy a group.
	void		destroyGroup(HGroup hgroup);	

	/// Clear a group.
	void		clearGroup(HGroup hgroup);

	/// Store current objects AABBs to the previous AABBs.
	void		updatePreviousAabbs(HGroup hgroup);

	/// Get first group.
	HGroup		getFirstGroup() const { return m_firstGroup; }

	/// Get next group.
	HGroup		getNext(HGroup hgroup) const { return hgroup.isValid() ? m_groups[hgroup].m_next : HGroup::invalid(); }


	//
	// Objects.
	//


	/// Add objects to the world.
	void		addObjects(HGroup hgroup, const hkAabb* aabbs, const DataType* datas, int numObjects, HObject* handlesOut);

	/// Add one object to the world.
	HObject		addObject(HGroup hgroup, const hkAabb& aabb, DataType data);

	/// Remove objects from the world.
	void		removeObjects(const HObject* hobjects, int numObjects);

	/// Remove one object from the world.
	void		removeObject(HObject hobject);

	/// Transfer one object to another group.
	void		transferObject(HObject hobject, HGroup hnewgroup);

	/// Start an objects update session.
	void		startUpdate();

	/// Update objects.
	void		updateObjects(const HObject* hobjects, const hkAabb* aabbs, int numObjects);

	/// Update one object.
	void		updateObject(HObject hobject, const hkAabb& aabb);

	/// Update all objects from a group using the group codec to retrieve new AABBs.
	void		updateGroupObjects(HGroup hgroup);

	/// End an objects update session.
	void		endUpdate();	

	/// Retrieve the group handle from an object handle.
	HGroup		getGroup(HObject hobject) const { return m_objects[hobject].m_group; }

	/// Retrieve the current AABB of an object.
	void		getCurrentAabb(HObject hobject, hkAabb& aabbOut) const;

	/// Retrieve the previous AABB of an object.
	void		getPreviousAabb(HObject hobject, hkAabb& aabbOut) const;

	/// Set the previous AABB of an object.
	void		setPreviousAabb(HObject hobject, const hkAabb& previousAabb);


	//
	// Queries.
	//

	
	/// Retrieve all new pairs from a group set.
	void		queryNewPairs(const GroupSet& groups, IBinaryProcessor* processor) const;
	
	/// Retrieve all new pairs between two group sets.
	void		queryNewPairs(const GroupSet& groupsA, const GroupSet& groupsB, IBinaryProcessor* processor) const;

	/// Retrieve all overlaping objects between a group set and an AABB.
	void		queryOverlaps(const GroupSet& groups, const hkAabb& aabb, IUnaryProcessor* processor, hkAabb* nmpOut = HK_NULL) const;

	/// Perform a raycast against a group set.
	void		queryRayCast(const GroupSet& groups, hkcdRay& ray, ILinearCastProcessor* processor) const;

	
	//
	// Fields.
	//

	hkFreeListArray<Object, HObject, 32>	m_objects;		///< Objects allocator.
	hkFreeListArray<Group, HGroup, 8>		m_groups;		///< Groups allocator.
	HGroup										m_firstGroup;	///< First group.
};

#include <Geometry/Collide/World/hkcdWorld.inl>

#endif // HKCD_WORLD_H

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
