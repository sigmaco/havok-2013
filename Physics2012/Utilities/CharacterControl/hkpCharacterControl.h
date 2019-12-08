/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_CHARACTER_CONTROLLER_H
#define HK_CHARACTER_CONTROLLER_H

#include <Common/Base/hkBase.h>
#include <Physics2012/Dynamics/Motion/hkpMotion.h>

/// Surface information returned from user queries with hkRigidBodyCharacterProxy::checkSupport.
struct hkpSurfaceInfo
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_UTILITIES, hkpSurfaceInfo );

	/// The supported state of the character
	enum SupportedState
	{
		/// This state implies there are no surfaces underneath the character.
		UNSUPPORTED = 0,

		/// This state means that there are surfaces underneath the character, but they are too
		/// steep to prevent the character sliding downwards.
		SLIDING = 1,

		/// This state means the character is supported, and will not slide.
		SUPPORTED = 2
	};

	/// The supported state of the character.
	SupportedState m_supportedState;

	/// The average surface normal in this given direction
	hkVector4	m_surfaceNormal;	

	/// The average surface velocity
	hkVector4	m_surfaceVelocity;

	/// The excess distance to the surface, which the controller should try to reduce this by applying
	/// gravity.
	/// This behavior is not required by the proxy character controller, so it sets the surfaceDistance to 0.
	hkReal	m_surfaceDistanceExcess;

	/// Is the surface dynamic (i.e., not fixed or keyframed).
	hkBool	m_surfaceIsDynamic; 

	/// Constructors
	hkpSurfaceInfo()
	{
		m_supportedState = SUPPORTED; 
		m_surfaceNormal = hkVector4::getConstant<HK_QUADREAL_0010>();
		m_surfaceVelocity.setZero();
		m_surfaceDistanceExcess = hkReal(0);
		m_surfaceIsDynamic = false;
	}	

	hkpSurfaceInfo(const hkVector4& up, const hkVector4& velocity = hkVector4::getZero(), const SupportedState state = SUPPORTED, hkBool isDynamic = false )
	{
		m_supportedState = state; 
		m_surfaceNormal = up;
		m_surfaceVelocity = velocity;
		m_surfaceDistanceExcess = hkReal(0);
		m_surfaceIsDynamic = isDynamic;
	}	

	/// Set structure from other
	inline void set(const hkpSurfaceInfo& other)
	{
		m_supportedState = other.m_supportedState;
		m_surfaceNormal = other.m_surfaceNormal;
		m_surfaceVelocity = other.m_surfaceVelocity;
		m_surfaceDistanceExcess = other.m_surfaceDistanceExcess;
		m_surfaceIsDynamic = other.m_surfaceIsDynamic;
	}

	/// Checks if the numeric data members have valid values
	hkBool isValid() const
	{		
		return ((m_supportedState == UNSUPPORTED) || (m_surfaceNormal.isOk<3>() && m_surfaceNormal.isNormalized<3>() && 
				m_surfaceVelocity.isOk<3>() && hkMath::isFinite(m_surfaceDistanceExcess)));
	}
};

/// Surface information returned from user queries with hkpCharacterProxy::checkSupportDeprecated
struct hkpSurfaceInfoDeprecated
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_UTILITIES, hkpSurfaceInfoDeprecated );

	/// Am I supported by the surface, i.e., is there any surface of any slope in this direction
	hkBool		m_isSupported;

	/// Am I sliding
	hkBool		m_isSliding;		

	/// The average surface normal in this given direction
	hkVector4	m_surfaceNormal;	

	/// The average surface velocity
	hkVector4	m_surfaceVelocity;	
};

#endif //HK_CHARACTER_CONTROLLER_H

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
