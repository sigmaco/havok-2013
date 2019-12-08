/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKCD_PLANAR_GEOMETRY_PRIMITIVES_H
#define HKCD_PLANAR_GEOMETRY_PRIMITIVES_H

#include <Common/Base/Math/LargeInt/hkLargeIntTypes.h>
#include <Common/Base/Types/hkHandle.h>
#include <Common/Base/Types/Geometry/Aabb/hkAabb.h>

#define ENABLE_HKCD_PLANAR_GEOMETRY_DEBUG_CHECKS		(0)
#ifndef HK_DEBUG
#	undef ENABLE_HKCD_PLANAR_GEOMETRY_DEBUG_CHECKS
#	define ENABLE_HKCD_PLANAR_GEOMETRY_DEBUG_CHECKS		(0)
#endif

namespace hkcdPlanarGeometryPrimitives
{
	/// Number of bits during operations with fixed precision arithmetic.
	template <class Op1, class Op2>	struct	NumBitsMax		{ enum { NUM_BITS = Op1::NUM_BITS - ((Op1::NUM_BITS - Op2::NUM_BITS) & ((Op1::NUM_BITS - Op2::NUM_BITS) >> 31)), };	};
	template <class Op1, class Op2>	struct	NumBitsSum		{ enum { NUM_BITS = NumBitsMax<Op1, Op2>::NUM_BITS + 1, }; };
	template <class Op1, class Op2> struct	NumBitsMul		{ enum { NUM_BITS = Op1::NUM_BITS + Op2::NUM_BITS - 1, }; };
	template <class Op1, class Op2> struct	NumBitsCross	{ enum { NUM_BITS = NumBitsSum< NumBitsMul<Op1, Op2>, NumBitsMul<Op1, Op2> >::NUM_BITS, }; };
	template <class Op1, class Op2> struct	NumBitsDot2		{ enum { NUM_BITS = NumBitsSum< NumBitsMul<Op1, Op2>, NumBitsMul<Op1, Op2> >::NUM_BITS, }; };
	template <class Op1, class Op2> struct	NumBitsDot3		{ enum { NUM_BITS = NumBitsSum< NumBitsSum< NumBitsMul<Op1, Op2>, NumBitsMul<Op1, Op2> >, NumBitsMul<Op1, Op2> >::NUM_BITS, }; };

	/// Bit lengths for basic types.
	/// We use 24 bits to represent a vertex
	struct NumBitsMantissa					{ enum { NUM_BITS = 24, };  };
	struct NumBitsMantissaD					{ enum { NUM_BITS = 53, };  };
	struct NumBitsVertex					{ enum { NUM_BITS = 23 + 1, };	};															// 24 bits
	struct NumBitsEdge						{ enum { NUM_BITS = NumBitsSum<NumBitsVertex, NumBitsVertex>		::NUM_BITS,	};};		// 25 bits
	struct NumBitsPlaneNormal				{ enum { NUM_BITS = NumBitsCross<NumBitsEdge, NumBitsEdge>			::NUM_BITS,	};};		// 50 bits
	struct NumBitsPlaneOffset				{ enum { NUM_BITS = NumBitsDot3<NumBitsVertex, NumBitsPlaneNormal>	::NUM_BITS,	};};		// 75 bits

	/// Bit lengths for various derived types.
	struct NumBitsPlanesIntersectionEdgeDir	{ enum { NUM_BITS = NumBitsCross<NumBitsPlaneNormal, NumBitsPlaneNormal>					::NUM_BITS, };};		// 100 bits
	struct NumBitsPlanesDet3				{ enum { NUM_BITS = NumBitsDot3<NumBitsPlanesIntersectionEdgeDir, NumBitsPlaneNormal>		::NUM_BITS, };};		// 151 bits
	struct NumBitsPlaneMulOffset			{ enum { NUM_BITS = NumBitsMul<NumBitsPlaneNormal, NumBitsPlaneOffset>						::NUM_BITS, };};		// 124 bits
	struct NumBitsPlaneCrossOffset			{ enum { NUM_BITS = NumBitsSum<NumBitsPlaneMulOffset, NumBitsPlaneMulOffset>				::NUM_BITS, };};		// 135 bits
	struct NumBitsPlanesDet4				{ enum { NUM_BITS = NumBitsDot3<NumBitsPlanesIntersectionEdgeDir, NumBitsPlaneCrossOffset>	::NUM_BITS,	};};		// 226 bits

	typedef hkVector4d						ApproxPlaneEqn;

	/// Plane. Stores both the real world (i.e. floating point) and exact (integer) plane equations.
	struct Plane
	{
		public:

			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_GEOMETRY, hkcdPlanarGeometryPrimitives::Plane);
			HK_DECLARE_POD_TYPE();

		public:

			// Gets the fixed-precision normal
			HK_FORCE_INLINE void getExactNormal(hkInt64Vector4& iNormalOut) const;

			// Gets the fixed-precision offset
			HK_FORCE_INLINE void getExactOffset(hkSimdInt<128>& iOffsetOut) const;

			// Gets the floating-point equation
			HK_FORCE_INLINE const ApproxPlaneEqn& getApproxEquation() const;
			
			// Sets the exact plane equation
			HK_FORCE_INLINE void setExactEquation(hkInt64Vector4Parameter iNormalIn, const hkSimdInt<128>& iOffsetIn);

			//	Computes a plane in the opposite direction of the given plane
			HK_FORCE_INLINE void setOpposite(const Plane& srcPlane);

			// Compares two planes for equality
			HK_FORCE_INLINE hkBool32 isEqual(const Plane& other) const;

		protected:
	
			// Sets the exact normal. Does not preserve offset
			HK_FORCE_INLINE void setExactNormal(hkInt64Vector4Parameter iNormalIn);

			// Sets the exact offset. Assumes the normal has already been set
			HK_FORCE_INLINE void setExactOffset(const hkSimdInt<128>& iOffsetIn);

			// Simplifies the fixed-precision equation so that gcd(nx, ny, nz, offset) = 1
			HK_FORCE_INLINE void simplify();

			// Recomputes the floating-point equation to match the fixed-precision one within a known eps
			HK_FORCE_INLINE void computeApproxEquation();

		protected:

			hkInt64Vector4 m_iEqn;		///< Plane equation, fixed precision
			ApproxPlaneEqn m_dEqn;		///< Plane equation, double precision
	};

	/// Vertex. Stores both a floating point and fixed precision representation
	struct Vertex
	{
		public:

			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_GEOMETRY, hkcdPlanarGeometryPrimitives::Vertex);

		public:

			/// Sets the position of this vertex
			HK_FORCE_INLINE void set(hkIntVectorParameter iPos);

			/// Returns the fixed precision position
			HK_FORCE_INLINE const hkIntVector& getExactPosition() const;

			/// Returns the approximate floating-point precision
			HK_FORCE_INLINE const hkVector4d& getApproxPosition() const;

		protected:

			hkIntVector m_iPos;		///< Vertex position, fixed precision
			hkVector4d m_dPos;		///< Vertex position, double precision
	};

	// Plane Id constants
	enum PlaneIdConstants
	{
		NUM_BITS_PLANE_ID	= 28,								///< A plane Id cannot have more than 28 bits
		FLIPPED_PLANE_BIT	= NUM_BITS_PLANE_ID,
		FLIPPED_PLANE_FLAG	= 1 << FLIPPED_PLANE_BIT,			///< A plane with opposite orientation is marked by having this flag set in its Id .
		INVALID_PLANE_ID	= (1 << NUM_BITS_PLANE_ID) - 1,		///< We'll reserve this value for invalid plane Ids
		PLANE_ID_MASK		= ~(-1 << (FLIPPED_PLANE_BIT + 1)),	///< Mask for selecting only the valid bits in a plane Id.
	};

	/// Plane Id
	HK_DECLARE_HANDLE(PlaneId, hkUint32, INVALID_PLANE_ID);

	/// Returns the Id of the opposite plane
	HK_FORCE_INLINE PlaneId HK_CALL getOppositePlaneId(PlaneId planeId);

	///	Computes the plane passing through 3 vertices
	HK_FORCE_INLINE hkResult HK_CALL computePlaneEquation(hkIntVectorParameter vA, hkIntVectorParameter vB, hkIntVectorParameter vC, hkInt64Vector4& normalOut, hkSimdInt<128>& offsetOut);

	/// Returns true if the plane Ids are coplanar. Note that this only compares the Ids and does not evaluate any geometric predicate.
	/// The mesh must be built such that all planes are distinct!
	static HK_FORCE_INLINE bool HK_CALL coplanarPlaneIds(PlaneId planeIdA, PlaneId planeIdB);

	/// Returns true if the plane Ids are coplanar. Note that this only compares the Ids and does not evaluate any geometric predicate.
	/// The mesh must be built such that all planes are distinct!
	static HK_FORCE_INLINE bool HK_CALL sameOrientationPlaneIds(PlaneId planeIdA, PlaneId planeIdB);
}

#include <Geometry/Collide/DataStructures/PlanarGeometry/Primitives/hkcdPlanarGeometryPrimitives.inl>

#endif	//	HKCD_PLANAR_GEOMETRY_PRIMITIVES_H

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
