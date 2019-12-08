/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKMATH_VECTOR2D_H
#define HKMATH_VECTOR2D_H

/// Two dimensional vector.
class hkVector2d
{
	public:

		HK_DECLARE_POD_TYPE();

			/// Return value indicates on which side of the infinite line this point lies.
			/// Note that this is not the Euclidean distance unless [p0,p1] is normalized.
			/// Greater than zero, zero, less than zero indicate left of, on the line
			/// and right of the line respectively. Mnemonic - if the line segment is the
			/// positive x-axis, then distance signedness matches the y-axis.
		HK_FORCE_INLINE hkDouble64 signedDistanceToLineTimesLength( const hkVector2d& p0, const hkVector2d& p1 ) const;

			/// Return true if this is strictly right of the infinite line p0,p1
		HK_FORCE_INLINE hkBool32 rightOfLine( const hkVector2d& p0, const hkVector2d& p1 ) const;

			/// Return true if this is strictly left of the infinite line p0,p1
		HK_FORCE_INLINE hkBool32 leftOfLine( const hkVector2d& p0, const hkVector2d& p1 ) const;

			/// Returns true if the point is inside the circumcircle of the triangle p0, p1, p2 (wound CCW)
		HK_FORCE_INLINE hkBool32 inCircumcircle( const hkVector2d& p0, const hkVector2d& p1, const hkVector2d& p2, hkDouble64 tolerance = .01f ) const;

			/// Test for exact equality.
		HK_FORCE_INLINE hkBool32 equals( const hkVector2d& p0 ) const;

			/// Return the dot product of this and p.
		HK_FORCE_INLINE hkDouble64 dot( const hkVector2d& p ) const;

			/// Elementwise maximum.
		HK_FORCE_INLINE void setMax( const hkVector2d& a, const hkVector2d& b );
		
			/// Elementwise minimum.
		HK_FORCE_INLINE void setMin( const hkVector2d& a, const hkVector2d& b );
		
			/// Set both elements.
		HK_FORCE_INLINE void setAll( hkDouble64 a );

			/// Load from address.
		HK_FORCE_INLINE void load( const hkDouble64* p );

			/// Load from the 0th and 1st component of the hkVector4d.
		HK_FORCE_INLINE void convertFromVector4( hkVector4dParameter v);

			/// Store the x and y components to the hkVector4d's 0th and 1st components. Its 2nd and 3rd component are unspecified.
		HK_FORCE_INLINE void convertToVector4( hkVector4d& vOut ) const;

			/// Set both elements.
		HK_FORCE_INLINE void set( hkDouble64 a, hkDouble64 b );

			/// Set both elements.
		HK_FORCE_INLINE void set( hkSimdDouble64Parameter a, hkSimdDouble64Parameter b );

			/// Set this to the perp of a (90 degree anticlockwise rotation)
		HK_FORCE_INLINE void setPerp( const hkVector2d& a );
		
			/// Set this to the elementwise sum of a and b.
		HK_FORCE_INLINE void setAdd( const hkVector2d& a, const hkVector2d& b );

			/// Set this += a
		HK_FORCE_INLINE void add( const hkVector2d& a );
		
			/// Set this to the elementwise product of v and r.
		HK_FORCE_INLINE void setMul( const hkVector2d& v, hkDouble64 r );
		
			/// Set this to the elementwise product of a and b.
		HK_FORCE_INLINE void setMul( const hkVector2d& a, const hkVector2d& b );
			
			/// Multiply each element by r.
		HK_FORCE_INLINE void mul( hkDouble64 r );
			
			/// Set this to a+b*r.
		HK_FORCE_INLINE void setAddMul( const hkVector2d& a, const hkVector2d& b, hkDouble64 r );

			/// Sets this += a * b
		HK_FORCE_INLINE void addMul( const hkVector2d& a, const hkVector2d& b );
		HK_FORCE_INLINE void addMul( const hkVector2d& a, hkDouble64 b );
		HK_FORCE_INLINE void addMul( hkDouble64 a, const hkVector2d& b );

			/// Set this to the elementwise subtraction of a and b.
		HK_FORCE_INLINE void setSub( const hkVector2d& a, const hkVector2d& b );
		
			/// Set this to be the vector (1-t)*a + t*b
		HK_FORCE_INLINE void setInterpolate( const hkVector2d& a, const hkVector2d& b, hkDouble64 t);

			/// Return the distance between this and p.
		HK_FORCE_INLINE hkDouble64 distanceTo( const hkVector2d& p ) const;

			/// Set this to be the point on the segment end0,end1 which is closest to p.
		void setClosestPointOnSegmentToPoint( const hkVector2d& end0, const hkVector2d& end1, const hkVector2d& p );
		
			/// Set this to { p.dot<3>(ax), p.dot<3>(ay) }
		HK_FORCE_INLINE void setProject( hkVector4dParameter p, hkVector4dParameter ax, hkVector4dParameter ay );
			
			/// Normalize this vector.
		HK_FORCE_INLINE void normalize();
			
			/// Normalize and return the original length.
		HK_FORCE_INLINE hkDouble64 normalizeWithLength();

			/// Length.
		HK_FORCE_INLINE hkDouble64 length() const;

			/// Set both elements to zero.
		HK_FORCE_INLINE void setZero();

			/// Return true if this is lexicographically less than v.
			/// The x components are compared and the y component used to break a tie if any.
		HK_FORCE_INLINE hkBool32 lexLess( const hkVector2d& v );

			/// Sets this = -v
		HK_FORCE_INLINE void setNeg(const hkVector2d& v);

		/// Computes the cross product of the two vectors
		static HK_FORCE_INLINE void HK_CALL cross(const hkVector2d& vA, const hkVector2d& vB, hkVector4d& crossOut);
		static HK_FORCE_INLINE hkDouble64 HK_CALL cross(const hkVector2d& vA, const hkVector2d& vB);

		//
		// Advanced control for vector normalization.
		//

			/// Normalize this vector.
			/// See the documentation at the template values for the requested behavior.
		template <hkMathAccuracyMode A, hkMathNegSqrtMode S> HK_FORCE_INLINE void normalize();

			/// Normalize this vector.
			/// See the documentation at the template values for the requested behavior.
		template <hkMathAccuracyMode A, hkMathNegSqrtMode S> HK_FORCE_INLINE hkDouble64 normalizeWithLength();

	public:

			/// Public access
		hkDouble64 x;
			/// Public access
		hkDouble64 y;
};

#include <Common/Base/Math/Vector/hkVector2d.inl>

#endif //HKMATH_VECTOR2D_H

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
