/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#ifndef HKCD_INTERNAL_GSK_DATA_H
#define HKCD_INTERNAL_GSK_DATA_H

#include <Geometry/Internal/Types/hkcdVertex.h>

/// Utility function to calculate the distance between 2 convex objects.
/// This function is very robust and can handle penetrating situations as well.
namespace hkcdGsk
{
		/// The cache for GSK. Stores the dimensions of the current simplices for both shapes A and B, together with the vertex indices of each simplex.
	struct Cache
	{
		typedef hkUint8 VertexId;

		HK_FORCE_INLINE void setDims(int dimA, int dimB, int userData) { m_dimAb = (hkUint8)((dimA<<6)|dimB|(userData<<2)); }
		HK_FORCE_INLINE int getDimA() const { return m_dimAb>>6; }
		HK_FORCE_INLINE int getDimB() const { return m_dimAb&0x3; }
		HK_FORCE_INLINE hkUchar dimBisNot3_orPenetrating(){ return m_dimAb ^ ((1<<6)|(0<<2)|(3<<0));  }

		void init()
		{
			union U { hkUint8 u8[4]; hkUint32 u32; };
			U* u = reinterpret_cast<U*>(&m_vertexIds);
			u->u32 = 0;
			setDims(1,1,0);
		}

			// Pack GSK results into the cache. status is the hkcdGsk::GetClosestPointStatus
		HK_FORCE_INLINE void pack(int dimA, int dimB, int status, const hkcdVertex* HK_RESTRICT verticesOfAinA, const hkcdVertex* HK_RESTRICT verticesOfBinA);

		const VertexId* getVertexIdsA() const { return m_vertexIds; }
		const VertexId* getVertexIdsB() const { return &m_vertexIds[getDimA()]; }

	protected:

		VertexId m_vertexIds[4];	// This should be aligned on a 4 byte boundary, not aligning it here because of enforced padding
		hkUint8 m_dimAb;			// dimA are bits 6-7, dimB are bits 0-1, bits 2-4 are the GetClosestPointStatus
	};


	// Closest point input and output


		/// Low level GJK and GSK output data
	struct GetClosestPointInput
	{
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(0, GetClosestPointInput);
		GetClosestPointInput()
			:	m_handlePenetration(true)
			,	m_terminationGrowthRate(1.4f)
		{
			m_coreCollisionTolerance = hkSimdReal::getConstant(HK_QUADREAL_MAX);
		}

		hkTransform					m_aTb;
		hkPadSpu<hkUint32>			m_handlePenetration;	// actually a bool

		/// The collision tolerance plus shape radii
		hkSimdReal					m_coreCollisionTolerance;
		hkPadSpu<hkReal>			m_terminationGrowthRate;
	};

		/// Low level GJK and GSK output data
	struct GetClosestPointOutput
	{
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(0, GetClosestPointOutput);

		hkSimdReal getDistance() { return m_distance; }

		hkSimdReal m_distance;
		hkVector4 m_normalInA;	///< Normal from B to A in A.
		hkVector4 m_pointAinA;
	};

		/// GetClosestPoint output status. 
	enum GetClosestPointStatus
	{
		// General success indication
		STATUS_OK_NOT_PENTRATING = 0,	///< The objects are NOT penetrating and the returned distance is OK
		STATUS_OK_PENETRATING = 1,		///< The objects are penetrating and the returned distance is OK

		// Penetration depth algorithm errors
		STATUS_PD_HEURISTIC_SAMPLING,	///< The objects are probably penetrating, but GSK ran into internal numerical issues, a fallback algorithms is used, so the output is an approximation at best.
		STATUS_PD_OUT_OF_MEMORY,		///< The objects are so deeply penetrating and have many vertices, so that the algorithms runs out of memory. There is still a valid output, but it is an approximation at best.

		STATUS_OK_FLAG,					///< Not a return value, but indicates the end of all OK statii

		STATUS_PD_DISTANCE_TOO_BIG,		///< The output only has a distance, which is bigger than the collision tolerance.
		STATUS_PENETRATING,				///< Objects are penetrating but no further details.
		STATUS_PD_UNSOLVABLE,			///< No solution because of numerical issues, this is an internal flag and NOT returned by hkcdGsk::getClosestPoint().
	};



	// Linear cast input and output

		/// Linear cast input
	struct LinearCastInput
	{
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(0, LinearCastInput);

		/// Constructor. Receives the convex radii of the cast shapes and an epsilon value to
		/// control the stopping criteria.
		HK_FORCE_INLINE LinearCastInput(hkReal convexRadiusA, hkReal convexRadiusB, hkReal eps = 0.001f);

		/// Returns convexRadiusA + convexRadiusB
		HK_FORCE_INLINE const hkSimdReal getRadiusAB() const;

		/// Returns the squared termination epsilon
		HK_FORCE_INLINE const hkSimdReal getSquaredTerminationEps() const;

		hkVector4 m_from; 
		hkVector4 m_direction; 
		hkTransform m_aTb; 
		hkVector4 m_data; 
	};

		/// Linear cast output
	struct LinearCastOutput
	{
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(0, LinearCastOutput);
		hkSimdReal m_fractionInOut;
		hkVector4 m_normalOut;
	};


		/// Ray cast input
	struct RayCastInput : public LinearCastInput
	{
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(0, RayCastInput);

		/// Constructor. Receives the convex radii of the cast shapes and an epsilon value to
		/// control the stopping criteria.
		HK_FORCE_INLINE RayCastInput(hkReal convexRadiusA, hkReal eps = 0.001f)
		:	LinearCastInput(convexRadiusA, 0.0f, eps)
		{
			m_aTb.setIdentity();
		}
	};

	struct RayCastOutput
	{
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(0, RayCastOutput);

		hkVector4 m_normalOut;
		hkSimdReal m_fractionInOut;
	};
}

#include <Geometry/Internal/Algorithms/Gsk/hkcdGskData.inl>

#endif // HKCD_INTERNAL_GSK_DATA_H

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
