/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_MATH_FOUR_TRANSPOSED_VECTORSf_H
#define HK_MATH_FOUR_TRANSPOSED_VECTORSf_H

#include <Common/Base/Types/Geometry/Aabb/hkAabb.h>

class hkcdVertex;

	/// Represents 4 3D vertices bundled together. The vertices are transposed, i.e. (xxxx, yyyy, zzzz)
class hkFourTransposedPointsf
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_COLLIDE, hkFourTransposedPointsf );
#if defined(HK_REAL_IS_FLOAT)
		HK_DECLARE_REFLECTION();
#endif
		HK_DECLARE_POD_TYPE();
	public:

		hkFourTransposedPointsf()
		{
			m_vertices[0].setZero();
			m_vertices[1].setZero();
			m_vertices[2].setZero();
		}

			/// Sets the vertex bundle to the given vertices
		HK_FORCE_INLINE void set(hkVector4fParameter vA, hkVector4fParameter vB, hkVector4fParameter vC, hkVector4fParameter vD);

			/// Extracts the vectors from the vertex bundle
		HK_FORCE_INLINE void extract(hkVector4f& vA, hkVector4f& vB, hkVector4f& vC, hkVector4f& vD) const;

			/// Extracts the vectors from the vertex bundle, with w components inserted from wABCD.
		HK_FORCE_INLINE void extractWithW(hkVector4fParameter wABCD, hkVector4f& vA, hkVector4f& vB, hkVector4f& vC, hkVector4f& vD) const;

			/// Extracts the vector at index from the bundle
		HK_FORCE_INLINE void extract(int index, hkVector4f& vI) const;

			/// Sets the vertex bundle to the same vertex
		HK_FORCE_INLINE void setAll(hkVector4fParameter v);

			/// Sets this = v - a
		HK_FORCE_INLINE void setSub(const hkFourTransposedPointsf& v, hkVector4fParameter a);

			/// Sets this = a - v
		HK_FORCE_INLINE void setSub(hkVector4fParameter a, const hkFourTransposedPointsf& v);

			/// Sets this = v - a
		HK_FORCE_INLINE void setSub(const hkFourTransposedPointsf& v, const hkFourTransposedPointsf& a);

			/// Sets this = v + a
		HK_FORCE_INLINE void setAdd(const hkFourTransposedPointsf& v, const hkFourTransposedPointsf& a);

		/// Sets x = vx * a.x, y = vy * a.y, ...
		HK_FORCE_INLINE void setMulC(const hkFourTransposedPointsf& v, hkVector4fParameter a);

		/// Sets x(i) = v.x(i) * a(i), y(i) = v.y(i) * a(i), ...         i = 1..4
		HK_FORCE_INLINE void setMulT(const hkFourTransposedPointsf& v, hkVector4fParameter a);

			/// Sets this = v * a
		HK_FORCE_INLINE void setMul(const hkFourTransposedPointsf& v, const hkFourTransposedPointsf& a);

			/// Sets this = v * a
		HK_FORCE_INLINE void setMul(const hkFourTransposedPointsf& a, hkSimdFloat32Parameter b);

		/// Sets this = min(v,a)
		HK_FORCE_INLINE void setMin(const hkFourTransposedPointsf& v, const hkFourTransposedPointsf& a);

		/// Sets this = max(v,a)
		HK_FORCE_INLINE void setMax(const hkFourTransposedPointsf& v, const hkFourTransposedPointsf& a);

			/// Sets minOut = min( v0, v1, v2 )
		HK_FORCE_INLINE void horizontalMin( hkVector4f& minOut ) const;

			/// Sets maxOut = max( v0, v1, v2 )
		HK_FORCE_INLINE void horizontalMax( hkVector4f& maxOut ) const;

			/// Sets v0 = b*c0, v1 = b*c1, etc.
		HK_FORCE_INLINE void setOuterProduct(hkVector4fParameter b, hkVector4fParameter c);

			/// Sets v0 += b*c0, v1 = b*c1, etc.
		HK_FORCE_INLINE void addOuterProduct(hkVector4fParameter b, hkVector4fParameter c);

			/// Sets v0 += b*c0, v1 = b*c1, etc.
		HK_FORCE_INLINE void subOuterProduct(hkVector4fParameter b, hkVector4fParameter c);

			/// Returns the dot3 of this and a
		HK_FORCE_INLINE void dot3(hkVector4fParameter a, hkVector4f& dotOut) const;

			/// Returns the dot3 of this and a
		HK_FORCE_INLINE void dot3(const hkFourTransposedPointsf& a, hkVector4f& dotOut) const;

			/// Translates the points along direction dir by distances(i), i.e. x(i) = v.x(i) + dir.x * distances(i), etc..
		HK_FORCE_INLINE void setAddMul(const hkFourTransposedPointsf& v, hkVector4fParameter dir, hkVector4fParameter distances);

#if defined(HK_REAL_IS_FLOAT)
			/// Sets this = projection of each point on the given Aabb
		HK_FORCE_INLINE void setAabbProjection(const hkFourTransposedPointsf& v, const hkAabb& aabb);

			/// Computes the distance from all vertices to the given Aaabb
		HK_FORCE_INLINE void computeAabbDistanceSq(const hkAabb& aabb, hkVector4f& distancesOut) const;
#endif // defined(HK_REAL_IS_FLOAT)

			/// Translates the points along direction -dir by distances(i), i.e. x(i) = v.x(i) - dir.x * distances(i), etc..
		HK_FORCE_INLINE void setSubMul(const hkFourTransposedPointsf& v, hkVector4fParameter dir, hkVector4fParameter distances);

			/// Returns the dot4 of this and a, with the w-coordinates of this assumed to be 1
		HK_FORCE_INLINE void dot4xyz1(hkVector4fParameter a, hkVector4f& dotOut) const;

			/// Sets v0 += a, v1 += a, etc.
		HK_FORCE_INLINE void add(hkVector4fParameter a);

			/// Sets v0 -= a, v1 -= a, etc.
		HK_FORCE_INLINE void sub(hkVector4fParameter a);

			/// Multiply all components by a
		HK_FORCE_INLINE void mul(hkSimdFloat32Parameter a);

			/// Sets this = this - v
		HK_FORCE_INLINE void sub( const hkFourTransposedPointsf& v );

			/// Sets this = this + v
		HK_FORCE_INLINE void add( const hkFourTransposedPointsf& v );

			/// Sets this = this * v
		HK_FORCE_INLINE void mul( const hkFourTransposedPointsf& v );

			/// Sets x(i) = v.x(i) + u.x(i) * a(i), y(i) = v.y(i) + u.y(i) * a(i), ...         i = 1..4
		HK_FORCE_INLINE void setAddMulT(const hkFourTransposedPointsf& v, const hkFourTransposedPointsf& u, hkVector4fParameter a);

		/// Sets x(i) = v.x(i) - u.x(i) * a(i), y(i) = v.y(i) - u.y(i) * a(i), ...         i = 1..4
		HK_FORCE_INLINE void setSubMulT(const hkFourTransposedPointsf& v, const hkFourTransposedPointsf& u, hkVector4fParameter a);

		/// Sets x(i) += u.x(i) * a(i), y(i) += u.y(i) * a(i), ...         i = 1..4
		HK_FORCE_INLINE void addMulT(const hkFourTransposedPointsf& u, hkVector4fParameter a);

		/// Sets x(i) -= u.x(i) * a(i), y(i) -= u.y(i) * a(i), ...         i = 1..4
		HK_FORCE_INLINE void subMulT(const hkFourTransposedPointsf& u, hkVector4fParameter a);

		/// Sets x(i) *= a(i),	 y(i) *= a(i), ...         i = 1..4
		HK_FORCE_INLINE void mulT(hkVector4fParameter a);

			/// Sets this = cross(n, v)
		HK_FORCE_INLINE void setCross(hkVector4fParameter n, const hkFourTransposedPointsf& v);
		HK_FORCE_INLINE void setCross(const hkFourTransposedPointsf& v, hkVector4fParameter n);

			/// Flips the signs, i.e. v0 = sign(ax) * v0, ..., v3 = sign(aw) * v3
		HK_FORCE_INLINE void flipSigns(hkVector4fParameter a);
		
			/// Selects a set of vectors i.e. vi = mask(i) ? ai : bi, for i = 0..3
		HK_FORCE_INLINE void setSelect(hkVector4fComparisonParameter mask, const hkFourTransposedPointsf& trueVecs, const hkFourTransposedPointsf& falseVecs);

			/// Sets this = Transpose(m) * v
		void setTransformedInverseDir(const hkMatrix3f& m, const hkFourTransposedPointsf& v);

			/// Inlined. Sets this = Transpose(m) * v
		HK_FORCE_INLINE void _setTransformedInverseDir(const hkMatrix3f& m, const hkFourTransposedPointsf& v);

			/// Sets this = Transpose(Rotation(m)) * (v - Translation(m))
		void setTransformedInversePos(const hkTransformf& m, const hkFourTransposedPointsf& v);

			/// Inlined. Sets this = Transpose(Rotation(m)) * (v - Translation(m))
		HK_FORCE_INLINE void _setTransformedInversePos(const hkTransformf& m, const hkFourTransposedPointsf& v);

			/// Sets this = m * v
		void setRotatedDir(const hkMatrix3f& m, const hkFourTransposedPointsf& v);

			/// Inlined. Sets this = m * v
		HK_FORCE_INLINE void _setRotatedDir(const hkMatrix3f& m, const hkFourTransposedPointsf& v);
		
			/// Normalizes the points
		HK_FORCE_INLINE void normalize();

			/// Copies the points from a hkVector4f array into a hkFourTransposedPointsf array
		static void HK_CALL copyVertexData(const hkVector4f* HK_RESTRICT sourceVerts, const int numVerts, hkArray<hkFourTransposedPointsf>& pointsOut);

			/// The output array must have space for a multiple of 4 vertices = (numVertices|3) & ~3.
		#	if defined(HK_REAL_IS_FLOAT)
		static void getOriginalVertices( const hkFourTransposedPointsf* verts4in, int numVertices, hkcdVertex* verticesOut );
		#endif

			/// Permutes the original vectors, NOT their components!
		template <hkVectorPermutation::Permutation perm>
		HK_FORCE_INLINE void setPermutation(const hkFourTransposedPointsf& pts);

		/// Computes the average of the four points
		HK_FORCE_INLINE void computeAverage(hkVector4f& avgOut) const;
		
	public:

			/// The vertices
		hkVector4f m_vertices[3];
};

#include <Common/Base/Math/Vector/hkFourTransposedPointsf.inl>

#endif	//	HK_MATH_FOUR_TRANSPOSED_VECTORSf_H

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
