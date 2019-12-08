/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */


#ifndef HK_COLLIDE2_AABB_UTIL_H
#define HK_COLLIDE2_AABB_UTIL_H

#include <Common/Base/Types/Physics/MotionState/hkMotionState.h>	// needed for .inl file

class hkAabb;
struct hkAabbUint32;


/// A utility class for creating AABBs that contain various geometric objects.
namespace hkAabbUtil
{
		//
		// Non-continuous AABB calculations
		//

			/// Calculates an AABB from an array of vertices.
		void HK_CALL				calcAabb( const hkReal* vertexArray, int numVertices, int striding, hkAabb& aabbOut );
		
			/// Calculates an AABB from an array of hkVector4.
		void HK_CALL				calcAabb( const hkVector4* vertexArray, int numVertices, hkAabb& aabbOut );

			/// Calculates an AABB from an array of hkVector4 pointers.
		void HK_CALL				calcAabb( const hkVector4*const* vertexArray, int numVertices, hkAabb& aabbOut );

			/// Calculates an AABB from an OBB specified by a transform, a center, and an halfExtents vector and an extra radius
		HK_FORCE_INLINE void HK_CALL		calcAabb( const hkTransform& BvToWorld, const hkVector4& halfExtents, const hkVector4& center, hkSimdRealParameter extraRadius, hkAabb& aabbOut);

			/// Calculates an AABB from an OBB specified by a transform, a center, and an halfExtents vector.
		HK_FORCE_INLINE void HK_CALL		calcAabb( const hkTransform& BvToWorld, const hkVector4& halfExtents, const hkVector4& center, hkAabb& aabbOut);

			/// Calculates an AABB from an OBB specified by a transform, and an halfExtents vector.
		HK_FORCE_INLINE void HK_CALL		calcAabb( const hkTransform& BvToWorld, const hkVector4& halfExtents, hkSimdRealParameter extraRadius, hkAabb& aabbOut);

			/// Calculates an AABB from an OBB specified by a transform, an AABB and an extra radius.
		void HK_CALL	calcAabb(const hkTransform& BvToWorld, const hkAabb& aabb, hkSimdRealParameter extraRadius, hkAabb& aabbOut);

			/// Calculates an AABB from an OBB specified by a transform and an AABB.
		void HK_CALL	calcAabb(const hkTransform& BvToWorld, const hkAabb& aabb, hkAabb& aabbOut);

			/// Calculates an AABB from an OBB specified by a transform with scale and an AABB.
		void HK_CALL				calcAabb(const hkQsTransform& bvToWorld, const hkAabb& aabb, hkAabb& aabbOut);

			/// Calculates an AABB from an OBB specified by a transform without scale and an AABB.
		void HK_CALL				calcAabb(const hkQTransform& bvToWorld, const hkAabb& aabb, hkAabb& aabbOut);

			/// Returns the minumum gap between the inner and outer aabb.
		HK_FORCE_INLINE hkSimdReal HK_CALL calcMinGap( const hkAabb& innerAabb, const hkAabb& outerAabb );

			/// Calculates an AABB from center and inner radius.
		HK_FORCE_INLINE void HK_CALL		calcAabb( const hkVector4& center, hkSimdRealParameter innerRadius, hkAabb& aabbOut);

		HK_FORCE_INLINE void HK_CALL		transformAabbIntoLocalSpace( const hkTransform& localToWorld, const hkAabb& aabb, hkAabb& aabbOut );

			/// Get the outer radius of an AABB.
		HK_FORCE_INLINE hkSimdReal HK_CALL	getOuterRadius(const hkAabb& aabb);

			/// Get the distance squared from point to an AABB, with point inside AABB distance == 0.
		HK_FORCE_INLINE hkSimdReal			distanceSquared(const hkAabb& a, hkVector4Parameter b);

			/// Get a vertex of an AABB. (with index bits set for positive as follow: Z | Y | X)
		HK_FORCE_INLINE void				getVertex(const hkAabb& aabb, int index, hkVector4& vertexOut);

			/// Get the 8 corner of an aabb
		HK_FORCE_INLINE void				get8Vertices(const hkAabb& aabb, hkVector4* verticesOut);

			/// Scale an AABB.
		HK_FORCE_INLINE void		scaleAabb(const hkVector4& scale, const hkAabb& aabbIn, hkAabb& aabbOut);

			/// Expand an AABB by a combination of linear and angular motion.
			/// The resulting AABB is as follows:
			///  - newMin = MIN(aabb.min + motionXYZ , aabb.min) - {anyDirectionExpansion,anyDirectionExpansion,anyDirectionExpansion}
			///  - newMax = MAX(aabb.max + motionXYZ , aabb.max) + {anyDirectionExpansion,anyDirectionExpansion,anyDirectionExpansion}
		HK_FORCE_INLINE void		expandAabbByMotion(const hkAabb& aabbIn, const hkVector4& motion, hkSimdRealParameter anyDirectionExpansion, hkAabb& aabbOut);

			/// expand aabb by the linear motion of a body.
		HK_FORCE_INLINE void		expandAabbByMotion(const hkAabb& aabbIn, const hkVector4& motion, hkAabb& aabbOut);

			/// expand aabb by two different linear motions plus any direction motion of a body.
		HK_FORCE_INLINE void		expandAabbByMotion(const hkAabb& aabbIn, hkVector4Parameter motionA, hkVector4Parameter motionB, hkSimdRealParameter anyDirectionExpansion, hkAabb& aabbOut);

			/// expand aabb by two different linear motions plus any direction motion of a body. This version is needed for neighbour welding (needs a larger aabb)
		HK_FORCE_INLINE void		expandAabbByMotionCircle(const hkAabb& aabbIn, hkVector4Parameter motionA, hkVector4Parameter motionB, hkSimdRealParameter anyDirectionExpansion, hkAabb& aabbOut);

			/// Project an AABB on an axis.
		HK_FORCE_INLINE void		projectAabbOnAxis(const hkVector4& axis, const hkAabb& aabb, hkSimdReal& minOut, hkSimdReal& maxOut);

			/// Project the minimum extend of an AABB on an axis.
		HK_FORCE_INLINE void		projectAabbMinOnAxis(const hkVector4& axis, const hkAabb& aabb, hkSimdReal& prjOut);

			/// Project the maximum extend of an AABB on an axis.
		HK_FORCE_INLINE void		projectAabbMaxOnAxis(const hkVector4& axis, const hkAabb& aabb, hkSimdReal& prjOut);

			/// Compute the widths span of an AABB wrt. a plane.
		HK_FORCE_INLINE void		computeAabbPlaneSpan(const hkVector4& plane, const hkAabb& aabb, hkSimdReal& minOut, hkSimdReal& maxOut);

		/// Converts a floating-point AABB to an integer AABB
		HK_FORCE_INLINE void HK_CALL convertAabbToUint32( const hkAabb& aabb, hkVector4fParameter offsetLow, hkVector4fParameter offsetHigh, hkVector4fParameter scale, hkAabbUint32& aabbOut );

		/// Converts an integer AABB to a floating-point AABB
		HK_FORCE_INLINE void HK_CALL convertAabbFromUint32( const hkAabbUint32& aabbIn, hkVector4fParameter offsetLow, hkVector4fParameter scale, hkAabb& aabbOut);

		/// Store the difference between a big expandedAabbInt and a smaller, enclosed unexpandedAabbInt_InOut in m_expansionXXX components of unexpandedAabbInt_InOut.
		HK_FORCE_INLINE void HK_CALL compressExpandedAabbUint32(const hkAabbUint32& expandedAabbInt, hkAabbUint32& unexpandedAabbInt_InOut);

		/// Expand a compressed unexpandedAabbInt to an expandedAabbOut using the information stored in the m_expansionXXX components.
		HK_FORCE_INLINE void HK_CALL uncompressExpandedAabbUint32(const hkAabbUint32& unexpandedAabbInt, hkAabbUint32& expandedAabbOut);

		enum { AABB_UINT32_MAX_FVALUE = 0x7ffe0000 };
		extern hkQuadReal hkAabbUint32MaxVal;

		//
		// Continuous AABB calculations
		//

		struct OffsetAabbInput
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_COLLIDE, hkAabbUtil::OffsetAabbInput );

			hkPadSpu<const hkMotionState*> m_motionState;

			// intermediate transforms
			hkTransform m_transforms[4];
			hkPadSpu<int> m_numTransforms;

			// start-end transforms
			hkTransform m_startTransform;
			hkTransform m_endTransformInv;
		};

			/// Sweep a discrete AABB and convert it into a 'continuous' swept AABB.
		HK_FORCE_INLINE void HK_CALL sweepAabb(const hkMotionState* motionstate, hkReal tolerance, const hkAabb& aabbIn, hkAabb& aabbOut);

			/// Calculate OffsetAabbInput.
		void HK_CALL initOffsetAabbInput(const hkMotionState* motionstate, OffsetAabbInput& input);

			/// Sweep a discrete AABB which has a huge offset from the mass center and convert it into a 'continuous' swept AABB.
		void HK_CALL sweepOffsetAabb(const OffsetAabbInput& input, const hkAabb& aabbIn, hkAabb& aabbOut);
}

#include <Common/Base/Types/Geometry/Aabb/hkAabbUtil.inl>

#endif // HK_COLLIDE2_AABB_UTIL_H

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
