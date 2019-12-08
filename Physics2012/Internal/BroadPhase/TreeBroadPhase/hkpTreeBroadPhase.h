/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_COLLIDE_TREE_BROADPHASE_H
#define HK_COLLIDE_TREE_BROADPHASE_H

#include <Physics2012/Collide/BroadPhase/hkpBroadPhase.h>

	/// Broad phase implementation using spatial trees.
	/// This is optimized for fast queries, for example raycasting and AABB queries.
	/// The current memory overhead is 72 bytes per object.
	///
	/// A optional child broad phase implementation can be provided - usually a hkp3AxisSweep - in which case that
	/// implementation is generally used for tree updates, while queries are performed in the tree version.
	///
	/// This broad phase implementation also provides additional convex queries, which could be used for example
	/// in frustum culling.
class hkpTreeBroadPhase : public hkpBroadPhase
{
	//+hk.ReflectedFile("TreeBroadPhase")
	public:
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);		

		//
		// Types.
		//

		/// Object groups.
		enum Group
		{
			GROUP_GHOST=0,	///< Holds objects never reported by queries.
			GROUP_PHANTOM,	///< Holds phantom objects.
			GROUP_STATIC,	///< Holds fixed objects.
			GROUP_DYNAMIC,	///< Holds movable objects.
			GROUP_USER,		///< Holds user objects that are reported by queries but not part of the physics simulation.
			
			GROUPS_COUNT,
			FIRST_QUERY_GROUP = GROUP_PHANTOM
		};
		
		/// Predefined groups masks
		enum GroupsMasks
		{
			ALL_GROUPS							=	0xffffffff,
			ALL_GROUPS_BUT_PHANTOM_AND_GHOST	=	~((1<<GROUP_PHANTOM) | (1<<GROUP_GHOST))
		};

		/// Hold extras informations about registered broadphase object.
		struct Handle
		{
			//+hk.ReflectedFile("TreeBroadPhase")
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, Handle);
			HK_FORCE_INLINE Handle() : m_bpHandle(HK_NULL) , m_spHandle(0) , m_group(0) , m_skips(0) {}

			hkpBroadPhaseHandle*	m_bpHandle;		///< Broadphase handle.
			hkUint32				m_spHandle:21;	///< Spatial partition handle.
			hkUint32				m_group:4;		///< Group id.
			hkUint32				m_skips:7;		///< Skips.
		};

		/// HandleArray
		typedef hkArray<Handle>	HandleArray;
		
		//
		// Constructor and destructor
		//

		hkpTreeBroadPhase(hkpBroadPhase* broadphase);
		virtual ~hkpTreeBroadPhase();

		//
		// API.
		//

		/// Perform per-frame internal state update.
		/// Note: Automatically call ::optimize with the current update quality (see setUpdateQuality).
		void			update(hkReal timeStep);

		/// Retrieve the underlying broadphase.
		hkpBroadPhase*	getChildBroadPhase() { return m_childBroadPhase; }

		/// Retrieve the memory foot print of the broadphase (not including the child broadphase).
		int				getMemoryFootPrint() const;

		/// Get the jitter margin.
		hkReal			getJitterMargin() const { return m_parameters(0); }

		/// Set the jitter margin.
		void			setJitterMargin(hkReal margin) { m_parameters(0) = margin; }

		/// Get the motion prediction factor.
		hkReal			getMotionPredictionFactor() const { return m_parameters(2); }

		/// Set the motion prediction factor.
		void			setMotionPredictionFactor(hkReal factor) { m_parameters(2) = factor; }

		/// Get the update optimization quality.
		hkReal			getUpdateQuality() const { return m_parameters(1); }

		/// Set the update optimization quality.
		void			setUpdateQuality(hkReal quality) { m_parameters(1) = quality; }

		/// Get the cache optimization quality.
		int				getCacheQuality() const { return m_parameters.getInt24W(); }

		/// Set the cache optimization quality.
		void			setCacheQuality(int quality) { m_parameters.setInt24W(quality); }
		
		/// Fully optimize the acceleration data structure.
		/// Its is recommended to call this function before the first frame and after most objects have been inserted into the broadphase.
		void			fullOptimize();

		/// Improve cache performance (especially for PlayStation(R)3 SPU queries).
		void			compact();

		/// Optimize the broadphase for faster queries, quality is a factor a the number of object registered in the broadphase [0 +inf].
		/// The time required to optimize is a linear function of \a quality.
		void			optimize(hkReal updateQuality, int cacheQuality);

		/// Add user objects.
		void			addUserObjects(int numObjects, hkpBroadPhaseHandle*const* handles, const hkAabb* aabbs);

		/// Update user objects.
		void			updateUserObjects(int numObjects, const hkpBroadPhaseHandle*const* handles, const hkAabb* aabbs, const hkVector4* velocities=HK_NULL);

		/// Remove user objects.
		void			removeUserObjects(int numObjects, hkpBroadPhaseHandle*const* handles);
		
		/// Check if a broad-phase handle is a user object.
		HK_FORCE_INLINE hkBool32			isUserObject(const hkpBroadPhaseHandle* object) const { return object->m_id >> 31; }

		/// Get an hkHandle from a hkpBroadPhaseHandle.
		HK_FORCE_INLINE Handle&				getHandleFromObject(const hkpBroadPhaseHandle* object) { return m_handles[object->m_id >> 31][object->m_id & 0x7fffffff]; }

		/// Get an hkHandle from a hkpBroadPhaseHandle.
		HK_FORCE_INLINE const Handle&		getHandleFromObject(const hkpBroadPhaseHandle* object) const { return m_handles[object->m_id >> 31][object->m_id & 0x7fffffff]; }

		/// Get handle array from group.
		HK_FORCE_INLINE HandleArray&		getHandlesFromGroup(int group) { return m_handles[group == GROUP_USER? 1:0]; }

		/// Get handle array from group.
		HK_FORCE_INLINE const HandleArray&	getHandlesFromGroup(int group) const { return m_handles[group == GROUP_USER? 1:0]; }
		
		//
		// Implement hkpBroadPhase
		//
		
		/// Return the broadphase type.
		virtual BroadPhaseType			getType() const { return BROADPHASE_TREE; }
		
		/// Return the actual broadphase implementing a capability.
		virtual const hkpBroadPhase*	getCapabilityDelegate(Capabilities cap) const;

		//
		// Tracked / Checked hkpBroadPhase members.
		//

		virtual int		getNumObjects() const;
		virtual void	getAllAabbs( hkArray<hkAabb>& allAabbs ) const;
		virtual void	getExtents(hkVector4& worldMinOut, hkVector4& worldMaxOut) const;
		virtual void	reQuerySingleObject( const hkpBroadPhaseHandle* object, hkArray<hkpBroadPhaseHandlePair>& pairs_out) const;
		virtual void	querySingleAabbWithCollector( const hkAabb& aabb, hkpBroadPhaseCastCollector* collector) const;
		virtual void	shiftBroadPhase( const hkVector4& shiftDistance, hkVector4& effectiveShiftDistanceOut, hkArray<hkpBroadPhaseHandlePair>& newCollisionPairs );
		virtual void	getOffsetLowHigh32bit(hkVector4& offsetLow32bit, hkVector4& offsetHigh32bit) const;
		virtual int		getAabbCacheSize() const;
		virtual void	calcAabbCache( const hkAabb& aabb, hkpBroadPhaseAabbCache* aabbCacheOut) const;
		virtual void	calcAabbCache( const hkArrayBase<class hkpCollidable*>& overlappingCollidables, hkpBroadPhaseAabbCache* aabbCacheOut) const;
		virtual void	getAabb(const hkpBroadPhaseHandle* object, hkAabb& aabb) const;
		virtual bool	areAabbsOverlapping( const hkpBroadPhaseHandle* bhA, const hkpBroadPhaseHandle* bhB ) const;
		virtual void	addObject( hkpBroadPhaseHandle* object, const hkAabbUint32& aabb, hkArray<hkpBroadPhaseHandlePair>& pairsOut, bool border = false  );
		virtual void	addObject( hkpBroadPhaseHandle* object, const hkAabb& aabb, hkArray<hkpBroadPhaseHandlePair>& pairsOut, bool border = false  );
		virtual void	addObjectBatch( const hkArrayBase<hkpBroadPhaseHandle*>& addObjectList, const hkArrayBase<hkAabb>& addAabbList, hkArray<hkpBroadPhaseHandlePair>& newPairs );
		virtual void	removeObject( hkpBroadPhaseHandle* object, hkArray<hkpBroadPhaseHandlePair>& pairsOut );
		virtual void	removeObjectBatch( const hkArrayBase<hkpBroadPhaseHandle*>& removeObjectList, hkArray<hkpBroadPhaseHandlePair>& delPairsOut );
		virtual void	updateAabbs( hkpBroadPhaseHandle* objects[], const hkAabb* aabbs, int numObjects, hkArray<hkpBroadPhaseHandlePair>& addedPairs, hkArray<hkpBroadPhaseHandlePair>& removedPairs );
		virtual void	updateAabbsUint32( hkpBroadPhaseHandle* objects[], const hkAabbUint32* aabbs, int numObjects, hkArray<hkpBroadPhaseHandlePair>& addedPairs, hkArray<hkpBroadPhaseHandlePair>& removedPairs );
		virtual void	defragment();
		virtual void	shiftAllObjects( const hkVector4& shiftDistance, hkVector4& effectiveShiftDistanceOut, hkArray<hkpBroadPhaseHandlePair>& newCollisionPairs );
		virtual void	set32BitOffsetAndScale(const hkVector4& offsetLow, const hkVector4& offsetHigh, const hkVector4& scale);
		
		//
		// Faster implementations of hkpBroadPhase members.
		//
		
		virtual	void	castRay( const hkpCastRayInput& input, hkpBroadPhaseCastCollector* collectorBase, int collectorStriding) const;
		virtual void	castAabb( const hkpCastAabbInput& input, hkpBroadPhaseCastCollector& collector ) const;
		virtual void	querySingleAabb( const hkAabb& aabb, hkArray<hkpBroadPhaseHandlePair>& pairs_out) const;

		//
		// Advanced queries.
		//


		/// Query objects located inside a convex set of planes.
		/// Planes must be oriented such as distances to planes for a point inside the set are all negatives or zero.
		/// The convex region defined to planes do not have to be closed.
		void			queryConvex(const hkVector4* planes, int numPlanes, hkArray<const hkpBroadPhaseHandle*>& objects, hkUint32 groupsMask = ALL_GROUPS_BUT_PHANTOM_AND_GHOST) const;

		/// Same as queryConvex but with an additional sorting along axis.
		void			queryConvexSorted(const hkVector4& axis, const hkVector4* planes, int numPlanes, hkArray<const hkpBroadPhaseHandle*>& objects, hkUint32 groupsMask = ALL_GROUPS_BUT_PHANTOM_AND_GHOST) const;
		

		//
		// Internals
		//
	private:

		void	addHandles(const hkpBroadPhaseHandle*const* handles, const hkAabb* aabbs, int count);
		void	addHandlesStandalone(hkpBroadPhaseHandle*const* handles, const hkAabb* aabbs, int count, hkArray<hkpBroadPhaseHandlePair>& addPairs);
		
		void	updateHandles(const hkpBroadPhaseHandle*const* handles, const hkAabb* aabbs, int count);
		void	updateHandlesStandalone(hkpBroadPhaseHandle*const* handles, const hkAabb* aabbs, int count, hkArray<hkpBroadPhaseHandlePair>& addPairs, hkArray<hkpBroadPhaseHandlePair>& remPairs);
		
		void	removeHandles(const hkpBroadPhaseHandle*const* handles, int count);
		void	removeHandlesStandalone(hkpBroadPhaseHandle*const* handles, int count, hkArray<hkpBroadPhaseHandlePair>& remPairs);
		
		void	updateHandlesMapping();
		void	indexAndCompact(int count);

		void	updateAabbs( hkpBroadPhaseHandle* objects[], const hkAabb* aabbs, const hkAabbUint32* aabbsInt, int numObjects, hkArray<hkpBroadPhaseHandlePair>& addedPairs, hkArray<hkpBroadPhaseHandlePair>& removedPairs );

		void	querySingleAabb( const hkAabb& aabb, const hkpBroadPhaseHandle* object, hkArray<hkpBroadPhaseHandlePair>& pairs_out) const;
		
		//
		// Fields
		//
		
	public:
		
		/// Internals.
#ifdef HK_ARCH_X64
		hkSimdReal		m_internals[(48 * GROUPS_COUNT) / sizeof(hkSimdReal)];
#else
		hkSimdReal		m_internals[(32 * GROUPS_COUNT) / sizeof(hkSimdReal)];
#endif
		/// Handles.
		HandleArray		m_handles[2];

		//
		// Starting from here, fields are not available on PlayStation(R)3 SPUs.
		//

		/// Parameters, X: Jitter margin, Y: Update optimization quality, Z: Motion prediction factor, W: Cache quality (integer).
		hkVector4		m_parameters;
		
		/// Used to unpack hkAabbUint32 AABBs (actually, -offset).
		/// As well as the current time step in W.
		hkVector4		m_offsetAndTimeStep;

		/// Offset low copy from the last call to set32BitOffsetAndScale.
		hkVector4		m_offsetLow;

		/// Offset high copy from the last call to set32BitOffsetAndScale.
		hkVector4		m_offsetHigh;

		/// Used to unpack hkAabbUint32 AABBs (actually, 1/scale).
		hkVector4		m_scale;		

		/// Underlying broadphase.
		hkpBroadPhase*	m_childBroadPhase;

		/// Has been fully optimized?
		hkBool			m_optimized;
};

#endif // HK_COLLIDE_TREE_BROADPHASE_H

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
