/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

HK_SIGNAL_PARAMETERS
struct HK_SIGNAL_TYPE : hkSignal
{
	//+hk.MemoryTracker(ignore=True)
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, hkSignal);

	/// Base slot declaration.
	struct Slot : hkSlot
	{
		//+hk.MemoryTracker(ignore=True)
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, Slot);
		
		/// Contructor.
		template <typename TYPE>
		HK_FORCE_INLINE Slot(hkSlot*& _slots, TYPE* object, const char* name) : hkSlot(_slots, object, name) {}

		/// Virtual destructor.
		virtual			~Slot() {}
		
		/// Fire method.
		virtual void	call(HK_SIGNAL_ARGUMENTS)=0;
	};
	
	/// Global slot.
	template <typename METHOD>
	struct GlobalSlot : Slot
	{
		//+hk.MemoryTracker(ignore=True)
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, GlobalSlot);
		
		HK_FORCE_INLINE		GlobalSlot(hkSlot*& _slots, METHOD method, const char* name) : Slot(_slots, (void*)HK_NULL, name), m_method(method) {}
		virtual void		call(HK_SIGNAL_ARGUMENTS) { m_method(HK_SIGNAL_NAMES); }
		virtual hkBool32	matchMethod(const void* methodData, int methodLength) const { return methodLength == sizeof(METHOD) && *reinterpret_cast<const METHOD*>(methodData) == m_method; }

		METHOD	m_method;
	};
	
	/// Member slot.
	template <typename TYPE, typename METHOD>
	struct MemberSlot : Slot
	{
		//+hk.MemoryTracker(ignore=True)
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, MemberSlot);
		
		HK_FORCE_INLINE		MemberSlot(hkSlot*& _slots, TYPE* object, METHOD method, const char* name) : Slot(_slots, object, name), m_method(method) {}

		/// Call the signal handler. If you have a compile error here, your functions signiture does not match the signiture of the signal.
		virtual void		call(HK_SIGNAL_ARGUMENTS) { (reinterpret_cast<TYPE*>(Slot::m_object)->*m_method)(HK_SIGNAL_NAMES); }

		virtual hkBool32	matchMethod(const void* methodData, int methodLength) const { return methodLength == sizeof(METHOD) && *reinterpret_cast<const METHOD*>(methodData) == m_method; }

		METHOD	m_method;
	};
	
	// Signal constructor.
	HK_FORCE_INLINE			HK_SIGNAL_TYPE(const char* name="") : hkSignal(name) {}

	#ifndef HK_PLATFORM_SPU
	
	// Connect a global method to this signal.
	template <typename METHOD>
	HK_NEVER_INLINE Slot*	subscribe(METHOD method, const char* name)
	{
		#ifdef HK_SIGNAL_DEBUG
		if(find(HK_NULL, &method, sizeof(METHOD)))
		{
			HK_ERROR(0x11D7EEA0, "Global slot already subscribing to signal '" << getName() << "'");
		}
		#endif
		return new GlobalSlot<METHOD>(m_slots, method, name);
	}

	// Returns true if the given method is already registered
	template <typename TYPE, typename METHOD>
	HK_NEVER_INLINE bool hasSubscription(TYPE* object, METHOD method)
	{
		return find(object, &method, sizeof(METHOD)) != HK_NULL;
	}

	// Connect a member method to this signal.
	template <typename TYPE, typename METHOD>
	HK_NEVER_INLINE Slot*	subscribe(TYPE* object, METHOD method, const char* name )
	{
		#ifdef HK_SIGNAL_DEBUG
		if(find(object, &method, sizeof(METHOD)))
		{
			HK_ERROR(0x11D7EEA1, "Member slot already subscribing to signal '" << getName() << "'");
		}
		#endif
		return new MemberSlot<TYPE,METHOD>(m_slots, object, method, name);
	}	

	// Disconnect a member method from this signal.
	template <typename TYPE, typename METHOD>
	HK_NEVER_INLINE hkBool	unsubscribe(TYPE* object, METHOD method) { return hkSignal::unsubscribeInternal(object, &method, sizeof(METHOD)); }

	// Disconnect a global method from this signal.
	template <typename METHOD>
	HK_FORCE_INLINE hkBool	unsubscribe(METHOD method) { return hkSignal::unsubscribeInternal(HK_NULL, &method, sizeof(METHOD)); }
	
	// Fire the signal.
#ifndef HK_COMPILER_GHS
	HK_NEVER_INLINE	
#endif
		void	fire(HK_SIGNAL_ARGUMENTS) { _fire(HK_SIGNAL_NAMES); }

	// Fire the signal inlined.
	HK_FORCE_INLINE	void	_fire(HK_SIGNAL_ARGUMENTS)
	{
		hkSlot**	prev = &m_slots;
		for(hkSlot* slot = *prev; slot;)
		{
			hkSlot*	next = slot->getNext();
			if(slot->hasNoSubscription())
			{
				delete slot;
				*prev = next;
			}
			else
			{
				((Slot*)slot)->call(HK_SIGNAL_NAMES);

				// It is possible that the slot was unsubscribed during this call, so check again
				if (slot->hasNoSubscription())
				{
					// We need to delete right now; otherwise there is a chance this slot will be left orphan
					delete slot;
					*prev = next;
				}
				else
				{
					prev = &slot->m_next;
				}

			}
			slot = next;
		}
	}
	#endif
};

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
