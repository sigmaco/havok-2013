/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#include <Common/Base/Math/Vector/hkFourTransposedPoints.h>

#ifndef	HKCD_TYPES_RAY
#define HKCD_TYPES_RAY


/// Represents the origin, direction and length of a ray.
/// Additionally, a fraction (default 1.0f) is stored in the direction W component.
/// Note that m_origin:W is free for user data.
/// Note that m_invDirection:W is free for user data.
struct hkcdRay 
{
	/// Set from end points
	HK_FORCE_INLINE	void setEndPoints(hkVector4Parameter start, hkVector4Parameter end, hkSimdRealParameter fraction = hkSimdReal::getConstant(HK_QUADREAL_1));

	/// Set from origin and direction.
	HK_FORCE_INLINE	void setOriginDirection(hkVector4Parameter origin, hkVector4Parameter direction, hkSimdRealParameter fraction = hkSimdReal::getConstant(HK_QUADREAL_1));

	/// Computes the ray end-point
	HK_FORCE_INLINE void getEndPoint(hkVector4& vEndPoint) const;

	/// Get direction
	HK_FORCE_INLINE const hkVector4& getDirection() const{ return m_direction; }

	/// Get inverse direction
	HK_FORCE_INLINE const hkVector4& getInverseDirection() const { return m_invDirection; }

	/// Get fraction.
	HK_FORCE_INLINE hkSimdReal	getFraction() const { return m_direction.getComponent<3>(); }

	/// Set fraction.
	HK_FORCE_INLINE void		setFraction(hkSimdRealParameter fraction) { m_direction.setComponent<3>(fraction); }
	
	/// Set from direction. Does not modify the origin
	HK_FORCE_INLINE	void setDirection(hkVector4Parameter direction, hkSimdRealParameter fraction = hkSimdReal::getConstant(HK_QUADREAL_1));

	hkVector4	m_origin;		///< Origin of the ray.
	hkVector4	m_direction;	///< Direction of the ray. Effectively the (endPoint - startPoint) vector (and length as |direction|).
	hkVector4	m_invDirection;	///< Precomputed direction reciprocal with +/-Inf == 0.
};


/// Represents 4 line segments (rays) bundled together.
/// The start and end position are stored in transposed form
struct hkcdRayBundle
{
	/// Returns the direction
	HK_FORCE_INLINE void getDirection(hkFourTransposedPoints& directionOut) const;

	/// The start positions of 4 rays transposed
	hkFourTransposedPoints m_start;

	/// The end positions of 4 rays transposed
	hkFourTransposedPoints m_end;

	/// A mask indicating which rays are active
	hkVector4Comparison m_activeRays;
};


/// A set of flags used to customize ray casting behavior.
struct hkcdRayQueryFlags
{
	enum Enum
	{
		/// No flags. Implies default behavior:
		///  - Triangles are treated as two sided.
		///  - No inside hits are reported.
		NO_FLAGS = 0,

		/// In triangle based shapes (e.g: mesh, height field), rays will not hit triangle back faces.
		/// Back faces are considered to be those with clockwise vertex winding.
		DISABLE_BACK_FACING_TRIANGLE_HITS	= 1 << 0,

		/// In triangle based shapes (e.g: mesh, height field), rays will not hit triangle front faces.
		/// Front faces are considered to be those with counter-clockwise vertex winding.
		DISABLE_FRONT_FACING_TRIANGLE_HITS	= 1 << 1,

		/// In non-triangle based shapes, rays will hit the insides of the shape.
		/// The normal returned for inside hits will be outward facing.
		/// Note: For shapes created using hknpConvexShape::createFromVertices(), this flag only works when
		/// hknpConvexShape::BuildConfig.m_buildFaces is set to true.
		ENABLE_INSIDE_HITS = 1 << 2
	};

	/// Extracts a specific flag as a hkVector4Comparison.
	static HK_FORCE_INLINE void extractFlag(Enum flags, Enum flag, hkVector4Comparison& out);
};


/// Helper class for ray cast results.
struct hkcdRayCastResult
{
	static HK_FORCE_INLINE hkInt32 create(hkVector4ComparisonParameter isHit, hkVector4ComparisonParameter isInsideHit);
	static HK_FORCE_INLINE hkInt32 createHit(hkVector4ComparisonParameter isInsideHit);
	static HK_FORCE_INLINE hkInt32 createInsideHit();
	static HK_FORCE_INLINE hkInt32 createOutsideHit();
	static HK_FORCE_INLINE hkInt32 createMiss();
	
	/// Returns true if the result indicates a hit.
	static HK_FORCE_INLINE hkInt32 isHit(hkInt32 result);
	/// Returns true if the result indicates an inside hit. This includes a hit on the backside of a two-sided triangle.
	static HK_FORCE_INLINE hkInt32 isInsideHit(hkInt32 result);
	/// Returns true if the result indicates an outside hit.
	static HK_FORCE_INLINE hkInt32 isOutsideHit(hkInt32 result);
};

#include <Geometry/Internal/Types/hkcdRay.inl>

#endif // HKCD_TYPES_RAY

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
