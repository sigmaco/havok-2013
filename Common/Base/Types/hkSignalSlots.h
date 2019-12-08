/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_SIGNAL_SLOTS_H
#define HK_SIGNAL_SLOTS_H

// Compile time configuration.
// By default, enable debugging and tracking only when HK_DEBUG is defined.
#if defined(HK_DEBUG) && !defined(HK_PLATFORM_SPU)
	
	//#define HK_SIGNAL_DEBUG
#endif

#ifdef HK_SIGNAL_DEBUG
	#include <Common/Base/DebugUtil/GlobalProperties/hkGlobalProperties.h>
	#define HK_ENABLE_SIGNAL_TRACKING
	#define HK_SIGNAL_ON_DEBUG(_code_)			_code_
	#define HK_SIGNAL_SET_NAME(_key_, _value_)	hkGlobalProperties::getInstance().set(_key_, _value_);
	#define HK_SIGNAL_GET_NAME(_key_)			hkGlobalProperties::getInstance().get(_key_, "Unnamed")
	#define HK_SIGNAL_CLR_NAME(_key_)			hkGlobalProperties::getInstance().clear(_key_);
#else
	#define HK_SIGNAL_ON_DEBUG(_code_)
	#define HK_SIGNAL_SET_NAME(_key_, _value_)
	#define HK_SIGNAL_GET_NAME(_key_)			"Unnamed"
	#define HK_SIGNAL_CLR_NAME(_key_)
#endif

/// Abstract slot.
struct hkSlot
{
	//+hk.MemoryTracker(ignore=True)
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, hkSlot);
	
	HK_FORCE_INLINE				hkSlot(hkSlot*& slots, void* object, const char* name) : m_next(slots), m_object(object) { slots = this; HK_SIGNAL_SET_NAME(this, name); }
	HK_FORCE_INLINE virtual		~hkSlot()					{ HK_SIGNAL_CLR_NAME(this); }
	HK_FORCE_INLINE void		unsubscribe()				{ reinterpret_cast<hkUlong&>(m_next) |= 1; }
	HK_FORCE_INLINE hkBool32	hasNoSubscription() const	{ return (hkBool32)(reinterpret_cast<hkUlong>(m_next) & 1); }
	HK_FORCE_INLINE hkSlot*		getNext() const				{ return hkClearBits(m_next, 1); }
	HK_FORCE_INLINE const char*	getName() const				{ return reinterpret_cast<const char*>(HK_SIGNAL_GET_NAME(this)); }
	virtual hkBool32			matchMethod(const void* methodData, int methodLength) const=0;

	mutable hkSlot*	m_next;
	void*			m_object;
};

/// Abstract signal.
struct hkSignal
{	
	//+hk.MemoryTracker(ignore=True)
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, hkSlot);

	
	HK_FORCE_INLINE				hkSignal(const char* name) : m_slots(HK_NULL)	{ hkSignal::beginTrack(this); HK_SIGNAL_SET_NAME(this, name); }
	HK_FORCE_INLINE				~hkSignal()										{ hkSignal::endTrack(this); destroy(); HK_SIGNAL_CLR_NAME(this); }
	HK_FORCE_INLINE const char*	getName() const									{ return reinterpret_cast<const char*>(HK_SIGNAL_GET_NAME(this)); }
	HK_FORCE_INLINE bool		hasSubscriptions()								{ return m_slots != HK_NULL; }
	int							getNumSubscriptions() const;
	void						unsubscribeAll(void* object);
	hkBool						unsubscribeInternal(void* object, const void* method, int length);
	hkSlot*						find(void* object, const void* method, int length);
	void						printReport() const;
	void						destroy();
	void						reset();

	#ifdef HK_ENABLE_SIGNAL_TRACKING
	static void HK_CALL					beginTrack(hkSignal* signal);
	static void	HK_CALL					endTrack(hkSignal* signal);
	static HK_FORCE_INLINE hkSignal*	getFirstSignal()			{ return s_root; }
	HK_FORCE_INLINE hkSignal*			getNext() const				{ return m_links[1]; }

	hkSignal*				m_links[2];
	static hkSignal*		s_root;
	#else
	static HK_FORCE_INLINE void			beginTrack(hkSignal*) {}
	static HK_FORCE_INLINE void			endTrack(hkSignal*) {}
	#endif


	mutable hkSlot*	m_slots;

private:
	hkSignal(const hkSignal&) {}
	void operator==(const hkSignal&) {}

};

/// Declare a signal.
#define HK_QUOTE_SIGNAL_NAME(_name_) #_name_
#define HK_DECLARE_SIGNAL(_name_ , ...) \
	struct _name_ : __VA_ARGS__ \
	{ \
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, _name_); \
		HK_FORCE_INLINE _name_() : __VA_ARGS__(HK_QUOTE_SIGNAL_NAME(_name_)) {} \
		template <typename CLASS_TYPE> \
		HK_FORCE_INLINE hkSlot* implicitSubscribe(CLASS_TYPE* instance, const char* slotname) \
		{ \
			return subscribe( instance , &CLASS_TYPE::on##_name_ , slotname ); \
		} \
	}

/// Subscribe to a signal using the implicit method match of a class instance ('on_' + signal type name, i.e. 'hkMySignal' -> 'on_hkMySignal').
#define HK_SUBSCRIBE_TO_SIGNAL( _signal_ , _instance_, _class_ ) ((_signal_).implicitSubscribe(_instance_, HK_QUOTE_SIGNAL_NAME(_class_)))

//
// Implementations.
//

// 0
#define HK_SIGNAL_TYPE			hkSignal0
#define HK_SIGNAL_PARAMETERS
#define HK_SIGNAL_ARGUMENTS
#define HK_SIGNAL_NAMES
	#include <Common/Base/Types/hkSignalSlots.hxx>
#undef HK_SIGNAL_PARAMETERS
#undef HK_SIGNAL_ARGUMENTS
#undef HK_SIGNAL_NAMES
#undef HK_SIGNAL_TYPE

// 1
#define HK_SIGNAL_TYPE			hkSignal1
#define HK_SIGNAL_PARAMETERS	template <typename P0>
#define HK_SIGNAL_ARGUMENTS		P0 p0
#define HK_SIGNAL_NAMES			p0
	#include <Common/Base/Types/hkSignalSlots.hxx>
#undef HK_SIGNAL_PARAMETERS
#undef HK_SIGNAL_ARGUMENTS
#undef HK_SIGNAL_NAMES
#undef HK_SIGNAL_TYPE

// 2
#define HK_SIGNAL_TYPE			hkSignal2
#define HK_SIGNAL_PARAMETERS	template <typename P0,typename P1>
#define HK_SIGNAL_ARGUMENTS		P0 p0, P1 p1
#define HK_SIGNAL_NAMES			p0, p1
	#include <Common/Base/Types/hkSignalSlots.hxx>
#undef HK_SIGNAL_PARAMETERS
#undef HK_SIGNAL_ARGUMENTS
#undef HK_SIGNAL_NAMES
#undef HK_SIGNAL_TYPE

// 3
#define HK_SIGNAL_TYPE			hkSignal3
#define HK_SIGNAL_PARAMETERS	template <typename P0,typename P1,typename P2>
#define HK_SIGNAL_ARGUMENTS		P0 p0, P1 p1, P2 p2
#define HK_SIGNAL_NAMES			p0, p1, p2
	#include <Common/Base/Types/hkSignalSlots.hxx>
#undef HK_SIGNAL_PARAMETERS
#undef HK_SIGNAL_ARGUMENTS
#undef HK_SIGNAL_NAMES
#undef HK_SIGNAL_TYPE

// 4
#define HK_SIGNAL_TYPE			hkSignal4
#define HK_SIGNAL_PARAMETERS	template <typename P0,typename P1,typename P2,typename P3>
#define HK_SIGNAL_ARGUMENTS		P0 p0, P1 p1, P2 p2, P3 p3
#define HK_SIGNAL_NAMES			p0, p1, p2, p3
	#include <Common/Base/Types/hkSignalSlots.hxx>
#undef HK_SIGNAL_PARAMETERS
#undef HK_SIGNAL_ARGUMENTS
#undef HK_SIGNAL_NAMES
#undef HK_SIGNAL_TYPE

// 5
#define HK_SIGNAL_TYPE			hkSignal5
#define HK_SIGNAL_PARAMETERS	template <typename P0,typename P1,typename P2,typename P3,typename P4>
#define HK_SIGNAL_ARGUMENTS		P0 p0, P1 p1, P2 p2, P3 p3, P4 p4
#define HK_SIGNAL_NAMES			p0, p1, p2, p3, p4
	#include <Common/Base/Types/hkSignalSlots.hxx>
#undef HK_SIGNAL_PARAMETERS
#undef HK_SIGNAL_ARGUMENTS
#undef HK_SIGNAL_NAMES
#undef HK_SIGNAL_TYPE
// 
// // 6
// #define HK_SIGNAL_TYPE			hkSignal6
// #define HK_SIGNAL_PARAMETERS	template <typename P0,typename P1,typename P2,typename P3,typename P4,typename P5>
// #define HK_SIGNAL_ARGUMENTS		P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5
// #define HK_SIGNAL_NAMES			p0, p1, p2, p3, p4, p5
// 	#include <Common/Base/Types/hkSignalSlots.hxx>
// #undef HK_SIGNAL_PARAMETERS
// #undef HK_SIGNAL_ARGUMENTS
// #undef HK_SIGNAL_NAMES
// #undef HK_SIGNAL_TYPE
// 
// // 7
// #define HK_SIGNAL_TYPE			hkSignal7
// #define HK_SIGNAL_PARAMETERS	template <typename P0,typename P1,typename P2,typename P3,typename P4,typename P5, typename P6>
// #define HK_SIGNAL_ARGUMENTS		P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6
// #define HK_SIGNAL_NAMES			p0, p1, p2, p3, p4, p5, p6
// 	#include <Common/Base/Types/hkSignalSlots.hxx>
// #undef HK_SIGNAL_PARAMETERS
// #undef HK_SIGNAL_ARGUMENTS
// #undef HK_SIGNAL_NAMES
// #undef HK_SIGNAL_TYPE
// 
// // 8
// #define HK_SIGNAL_TYPE			hkSignal8
// #define HK_SIGNAL_PARAMETERS	template <typename P0,typename P1,typename P2,typename P3,typename P4,typename P5, typename P6, typename P7>
// #define HK_SIGNAL_ARGUMENTS		P0 p0, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7
// #define HK_SIGNAL_NAMES			p0, p1, p2, p3, p4, p5, p6, p7
// 	#include <Common/Base/Types/hkSignalSlots.hxx>
// #undef HK_SIGNAL_PARAMETERS
// #undef HK_SIGNAL_ARGUMENTS
// #undef HK_SIGNAL_NAMES
// #undef HK_SIGNAL_TYPE

// Cleanup PP.

#undef HK_SIGNAL_SET_NAME
#undef HK_SIGNAL_GET_NAME
#undef HK_SIGNAL_CLR_NAME

#endif // HK_SIGNAL_SLOTS_H

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
