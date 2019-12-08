/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKCD_PARTICLE_TRIANGLE_UTIL_H
#define HKCD_PARTICLE_TRIANGLE_UTIL_H



#define hkcdParticleTriangleUtilMxSize 4

class hkAabb;

class hkcdParticleTriangleUtil
{
	public:
		struct TriangleCollisionInfo
		{
			hkVector4 m_a;
			hkVector4 m_b;
			hkVector4 m_c;
			TriangleCollisionInfo(hkVector4Parameter a, hkVector4Parameter b, hkVector4Parameter c): m_a(a), m_b(b), m_c(c) {}
			TriangleCollisionInfo() {}
		};


		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(0,hkcdParticleTriangleUtil);

		struct ParticleInfo
		{
			ParticleInfo(): minDistance(1e10), nearestTriIndex(-1) {}

			hkVector4 m_contactPoint;
			hkReal minDistance;
			int nearestTriIndex;
		};

		struct TriangleCache
		{
			hkVector4 e01;
			hkVector4 e02;
			hkVector4 e12;
			hkVector4 normal;
			hkVector4 lengths;
			hkVector4 b0, b1, b2;
		};

		static void HK_CALL collideMx(const hkVector4* tri, const hkVector4* positions, int particleCount, hkArray<ParticleInfo>& particleInfo);
		static void HK_CALL collide(const hkVector4* tri, const hkVector4* positions, int particleCount, hkArray<ParticleInfo>& particleInfo);
		static void HK_CALL beginCollide(hkVector4* positions, int particleCount);
		static void HK_CALL endCollide(hkVector4* positions, int particleCount, hkArray<hkcdParticleTriangleUtil::ParticleInfo>& particleInfo);
		static int HK_CALL findCollisions(hkArray<hkVector4>& particlePositions, hkArray<hkcdParticleTriangleUtil::ParticleInfo>& particleInfo, hkArray<TriangleCollisionInfo>& triangles, int triangleCount, int particleCount);
		static void HK_CALL setupCache(const hkVector4* tri, hkcdParticleTriangleUtil::TriangleCache& cache);
//		static hkReal HK_CALL collideSphereTriangle(const hkVector4& pos, const hkVector4* v);
		static hkReal HK_CALL collideSphereTriangle(const hkVector4& pos, const hkVector4* v, hkVector4& posAndDistanceOut);
		static hkReal HK_CALL collideSphereTriangle(const hkVector4& pos, hkVector4Parameter vA, hkVector4Parameter vB, hkVector4Parameter vC, hkVector4& posAndDistanceOut);
		static hkBool HK_CALL AabbTriangleIntersect(const hkAabb& aabb, const hkVector4* tri);
		static hkBool HK_CALL AabbTriangleIntersect(const hkAabb& aabb, hkVector4Parameter vA, hkVector4Parameter vB, hkVector4Parameter vC);
private:

		static void HK_CALL collideSphereTriangle_SomeVectorCode(const hkVector4& pos, const hkVector4* v, const TriangleCache& cache, hkVector4& positionAndDistanceOut);
		static void HK_CALL collideSphereTriangle_VectorCode(const hkVector4& pos, const hkVector4* v, const TriangleCache& cache, hkVector4& posAndDistanceOut);
		static hkReal HK_CALL collideSphereTriangle_NoVectorCode(const hkVector4& pos, const hkVector4* v, hkVector4& posOut);
		HK_FORCE_INLINE static void HK_CALL collideSphereTriangle_MxVectorCode(const hkMxVector<hkcdParticleTriangleUtilMxSize>& pos, const hkVector4* v, const TriangleCache& cache, hkMxVector<hkcdParticleTriangleUtilMxSize>& posAndDistanceOut);
		static void setDistances(hkVector4* positions, int particleCount, hkReal distance);
};

#endif //HKCD_PARTICLE_TRIANGLE_UTIL_H

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
