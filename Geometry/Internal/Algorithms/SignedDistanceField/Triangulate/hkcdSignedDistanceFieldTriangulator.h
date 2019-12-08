/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#ifndef HKCD_SDF_TRIANGULATOR_H
#define HKCD_SDF_TRIANGULATOR_H


#include <Common/Base/hkBase.h>
#include <Common/Base/Types/Geometry/Aabb/hkAabb.h>
#include <Common/Base/Types/Geometry/hkGeometry.h>


struct hkcdSignedDistanceFieldTriangulator
{

	struct Function
	{
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_UTILITIES, Function );

		virtual			~Function() {}
		virtual	hkReal	evaluate(const hkVector4& position, hkVector4* normal = HK_NULL) const=0;
	};

	struct Config
	{
		Config() : m_maxDepth(7),  m_sharpnessPasses(8), m_fairingPasses(4), m_minCurvature(10.0f * HK_REAL_DEG_TO_RAD), m_scale(1.0f) {}

		int		m_maxDepth;
		int		m_sharpnessPasses;
		int		m_fairingPasses;
		hkReal	m_minCurvature;
		hkReal	m_scale;
	};

	static void HK_CALL triangulateSignedDistanceField(const Config& config, const Function* function, const hkAabb& domain, hkGeometry& geometry);
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
