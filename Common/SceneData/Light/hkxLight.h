/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKSCENEDATA_LIGHT_HKXLIGHT_HKCLASS_H
#define HKSCENEDATA_LIGHT_HKXLIGHT_HKCLASS_H

#include <Common/Base/Types/Color/hkColor.h>

/// hkxLight meta information
extern const class hkClass hkxLightClass;

/// The information needed to construct a simple light.
class hkxLight : public hkReferencedObject
{
	//+vtable(true)
	//+version(3)
	public:

		HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_SCENE_DATA );
		HK_DECLARE_REFLECTION();
	
		hkxLight() { }
		hkxLight(hkFinishLoadedObjectFlag f) : hkReferencedObject(f) { }

			/// Used to specify the type of the light.
		enum LightType
		{
				/// 
			POINT_LIGHT,
				/// 
			DIRECTIONAL_LIGHT,
				/// 
			SPOT_LIGHT
		};
		
		//
		// Members
		//
	public:
		
			/// The type of the light.
		hkEnum<LightType, hkInt8> m_type;
		
			/// The position (used for point and spot lights).
		hkVector4 m_position;
		
			/// The direction (used for directional and spot lights).
		hkVector4 m_direction;
		
			/// The RGB value of the light color.
		hkColor::Argb m_color;
		
			/// The angle, in radians of the spot light (full extent).
		hkReal m_angle;
		
			/// Range of influence
		hkReal m_range;

			/// Fade start (use decay rate for attenuation)
		hkReal m_fadeStart;
		
			/// Fade end
		hkReal m_fadeEnd;

			/// Decay rate (0 = no decay (currently not supported), 1 = linear, 2 = quadratic, 3 = cubic, ...)
		hkInt16 m_decayRate;

			/// Intensity multiplier (1 is default)
		hkReal m_intensity;

			/// Does it cast shadows
		hkBool m_shadowCaster;
};

#endif // HKSCENEDATA_LIGHT_HKXLIGHT_HKCLASS_H

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
