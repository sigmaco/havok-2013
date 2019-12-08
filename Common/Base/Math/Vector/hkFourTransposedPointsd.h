/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_MATH_FOUR_TRANSPOSED_VECTORSd_H
#define HK_MATH_FOUR_TRANSPOSED_VECTORSd_H

#include <Common/Base/Types/Geometry/Aabb/hkAabb.h>

class hkcdVertex;

	/// Represents 4 3D vertices bundled together. The vertices are transposed, i.e. (xxxx, yyyy, zzzz)
class hkFourTransposedPointsd
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_COLLIDE, hkFourTransposedPointsd );
#if defined(HK_REAL_IS_DOUBLE)
		HK_DECLARE_REFLECTION();
#endif
		HK_DECLARE_POD_TYPE();
	public:

		hkFourTransposedPointsd()
		{
			m_vertices[0].setZero();
			m_vertices[1].setZero();
			m_vertices[2].setZero();
		}

			/// Sets the vertex bundle to the given vertices
		HK_FORCE_INLINE void set(hkVector4dParameter vA, hkVector4dParameter vB, hkVector4dParameter vC, hkVector4dParameter vD);

			/// Extracts the vectors from the vertex bundle
		HK_FORCE_INLINE void extract(hkVector4d& vA, hkVector4d& vB, hkVector4d& vC, hkVector4d& vD) const;

			/// Extracts the vectors from the vertex bundle, with w components inserted from wABCD.
		HK_FORCE_INLINE void extractWithW(hkVector4dParameter wABCD, hkVector4d& vA, hkVector4d& vB, hkVector4d& vC, hkVector4d& vD) const;

			/// Extracts the vector at index from the bundle
		HK_FORCE_INLINE void extract(int index, hkVector4d& vI) const;

			/// Sets the vertex bundle to the same vertex
		HK_FORCE_INLINE void setAll(hkVector4dParameter v);

			/// Sets this = v - a
		HK_FORCE_INLINE void setSub(const hkFourTransposedPointsd& v, hkVector4dParameter a);

			/// Sets this = a - v
		HK_FORCE_INLINE void setSub(hkVector4dParameter a, const hkFourTransposedPointsd& v);

			/// Sets this = v - a
		HK_FORCE_INLINE void setSub(const hkFourTransposedPointsd& v, const hkFourTransposedPointsd& a);

			/// Sets this = v + a
		HK_FORCE_INLINE void setAdd(const hkFourTransposedPointsd& v, const hkFourTransposedPointsd& a);

		/// Sets x = vx * a.x, y = vy * a.y, ...
		HK_FORCE_INLINE void setMulC(const hkFourTransposedPointsd& v, hkVector4dParameter a);

		/// Sets x(i) = v.x(i) * a(i), y(i) = v.y(i) * a(i), ...         i = 1..4
		HK_FORCE_INLINE void setMulT(const hkFourTransposedPointsd& v, hkVector4dParameter a);

			/// Sets this = v * a
		HK_FORCE_INLINE void setMul(const hkFourTransposedPointsd& v, const hkFourTransposedPointsd& a);

			/// Sets this = v * a
		HK_FORCE_INLINE void setMul(const hkFourTransposedPointsd& a, hkSimdDouble64Parameter b);

		/// Sets this = min(v,a)
		HK_FORCE_INLINE void setMin(const hkFourTransposedPointsd& v, const hkFourTransposedPointsd& a);

		/// Sets this = max(v,a)
		HK_FORCE_INLINE void setMax(const hkFourTransposedPointsd& v, const hkFourTransposedPointsd& a);

			/// Sets minOut = min( v0, v1, v2 )
		HK_FORCE_INLINE void horizontalMin( hkVector4d& minOut ) const;

			/// Sets maxOut = max( v0, v1, v2 )
		HK_FORCE_INLINE void horizontalMax( hkVector4d& maxOut ) const;

			/// Sets v0 = b*c0, v1 = b*c1, etc.
		HK_FORCE_INLINE void setOuterProduct(hkVector4dParameter b, hkVector4dParameter c);

			/// Sets v0 += b*c0, v1 = b*c1, etc.
		HK_FORCE_INLINE void addOuterProduct(hkVector4dParameter b, hkVector4dParameter c);

			/// Sets v0 += b*c0, v1 = b*c1, etc.
		HK_FORCE_INLINE void subOuterProduct(hkVector4dParameter b, hkVector4dParameter c);

			/// Returns the dot3 of this and a
		HK_FORCE_INLINE void dot3(hkVector4dParameter a, hkVector4d& dotOut) const;

			/// Returns the dot3 of this and a
		HK_FORCE_INLINE void dot3(const hkFourTransposedPointsd& a, hkVector4d& dotOut) const;

			/// Translates the points along direction dir by distances(i), i.e. x(i) = v.x(i) + dir.x * distances(i), etc..
		HK_FORCE_INLINE void setAddMul(const hkFourTransposedPointsd& v, hkVector4dParameter dir, hkVector4dParameter distances);

#if defined(HK_REAL_IS_DOUBLE)
			/// Sets this = projection of each point on the given Aabb
		HK_FORCE_INLINE void setAabbProjection(const hkFourTransposedPointsd& v, const hkAabb& aabb);

			/// Computes the distance from all vertices to the given Aaabb
		HK_FORCE_INLINE void computeAabbDistanceSq(const hkAabb& aabb, hkVector4d& distancesOut) const;
#endif // defined(HK_REAL_IS_DOUBLE)

			/// Translates the points along direction -dir by distances(i), i.e. x(i) = v.x(i) - dir.x * distances(i), etc..
		HK_FORCE_INLINE void setSubMul(const hkFourTransposedPointsd& v, hkVector4dParameter dir, hkVector4dParameter distances);

			/// Returns the dot4 of this and a, with the w-coordinates of this assumed to be 1
		HK_FORCE_INLINE void dot4xyz1(hkVector4dParameter a, hkVector4d& dotOut) const;

			/// Sets v0 += a, v1 += a, etc.
		HK_FORCE_INLINE void add(hkVector4dParameter a);

			/// Sets v0 -= a, v1 -= a, etc.
		HK_FORCE_INLINE void sub(hkVector4dParameter a);

			/// Multiply all components by a
		HK_FORCE_INLINE void mul(hkSimdDouble64Parameter a);

			/// Sets this = this - v
		HK_FORCE_INLINE void sub( const hkFourTransposedPointsd& v );

			/// Sets this = this + v
		HK_FORCE_INLINE void add( const hkFourTransposedPointsd& v );

			/// Sets this = this * v
		HK_FORCE_INLINE void mul( const hkFourTransposedPointsd& v );

			/// Sets x(i) = v.x(i) + u.x(i) * a(i), y(i) = v.y(i) + u.y(i) * a(i), ...         i = 1..4
		HK_FORCE_INLINE void setAddMulT(const hkFourTransposedPointsd& v, const hkFourTransposedPointsd& u, hkVector4dParameter a);

		/// Sets x(i) = v.x(i) - u.x(i) * a(i), y(i) = v.y(i) - u.y(i) * a(i), ...         i = 1..4
		HK_FORCE_INLINE void setSubMulT(const hkFourTransposedPointsd& v, const hkFourTransposedPointsd& u, hkVector4dParameter a);

		/// Sets x(i) += u.x(i) * a(i), y(i) += u.y(i) * a(i), ...         i = 1..4
		HK_FORCE_INLINE void addMulT(const hkFourTransposedPointsd& u, hkVector4dParameter a);

		/// Sets x(i) -= u.x(i) * a(i), y(i) -= u.y(i) * a(i), ...         i = 1..4
		HK_FORCE_INLINE void subMulT(const hkFourTransposedPointsd& u, hkVector4dParameter a);

		/// Sets x(i) *= a(i),	 y(i) *= a(i), ...         i = 1..4
		HK_FORCE_INLINE void mulT(hkVector4dParameter a);

			/// Sets this = cross(n, v)
		HK_FORCE_INLINE void setCross(hkVector4dParameter n, const hkFourTransposedPointsd& v);
		HK_FORCE_INLINE void setCross(const hkFourTransposedPointsd& v, hkVector4dParameter n);

			/// Flips the signs, i.e. v0 = sign(ax) * v0, ..., v3 = sign(aw) * v3
		HK_FORCE_INLINE void flipSigns(hkVector4dParameter a);
		
			/// Selects a set of vectors i.e. vi = mask(i) ? ai : bi, for i = 0..3
		HK_FORCE_INLINE void setSelect(hkVector4dComparisonParameter mask, const hkFourTransposedPointsd& trueVecs, const hkFourTransposedPointsd& falseVecs);

			/// Sets this = Transpose(m) * v
		void setTransformedInverseDir(const hkMatrix3d& m, const hkFourTransposedPointsd& v);

			/// Inlined. Sets this = Transpose(m) * v
		HK_FORCE_INLINE void _setTransformedInverseDir(const hkMatrix3d& m, const hkFourTransposedPointsd& v);

			/// Sets this = Transpose(Rotation(m)) * (v - Translation(m))
		void setTransformedInversePos(const hkTransformd& m, const hkFourTransposedPointsd& v);

			/// Inlined. Sets this = Transpose(Rotation(m)) * (v - Translation(m))
		HK_FORCE_INLINE void _setTransformedInversePos(const hkTransformd& m, const hkFourTransposedPointsd& v);

			/// Sets this = m * v
		void setRotatedDir(const hkMatrix3d& m, const hkFourTransposedPointsd& v);

			/// Inlined. Sets this = m * v
		HK_FORCE_INLINE void _setRotatedDir(const hkMatrix3d& m, const hkFourTransposedPointsd& v);
		
			/// Normalizes the points
		HK_FORCE_INLINE void normalize();

			/// Copies the points from a hkVector4d array into a hkFourTransposedPointsd array
		static void HK_CALL copyVertexData(const hkVector4d* HK_RESTRICT sourceVerts, const int numVerts, hkArray<hkFourTransposedPointsd>& pointsOut);

			/// The output array must have space for a multiple of 4 vertices = (numVertices|3) & ~3.
		#	if defined(HK_REAL_IS_DOUBLE)
		static void getOriginalVertices( const hkFourTransposedPointsd* verts4in, int numVertices, hkcdVertex* verticesOut );
		#endif

			/// Permutes the original vectors, NOT their components!
		template <hkVectorPermutation::Permutation perm>
		HK_FORCE_INLINE void setPermutation(const hkFourTransposedPointsd& pts);

		/// Computes the average of the four points
		HK_FORCE_INLINE void computeAverage(hkVector4d& avgOut) const;
		
	public:

			/// The vertices
		hkVector4d m_vertices[3];
};

#include <Common/Base/Math/Vector/hkFourTransposedPointsd.inl>

#endif	//	HK_MATH_FOUR_TRANSPOSED_VECTORSd_H

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
