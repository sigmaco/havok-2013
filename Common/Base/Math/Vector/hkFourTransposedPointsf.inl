/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

//
//	Sets the vertex bundle to the given vertices

inline void hkFourTransposedPointsf::set(hkVector4fParameter vA, hkVector4fParameter vB, hkVector4fParameter vC, hkVector4fParameter vD)
{
	hkVector4f v0 = vA;
	hkVector4f v1 = vB;
	hkVector4f v2 = vC;
	hkVector4f v3 = vD;

	HK_TRANSPOSE4f(v0, v1, v2, v3);

	m_vertices[0] = v0;
	m_vertices[1] = v1;
	m_vertices[2] = v2;
}

//
//	Extracts the vectors from the vertex bundle

inline void hkFourTransposedPointsf::extract(hkVector4f& vA, hkVector4f& vB, hkVector4f& vC, hkVector4f& vD) const
{
	vA = m_vertices[0];
	vB = m_vertices[1];
	vC = m_vertices[2];
	vD.setZero();

	HK_TRANSPOSE4f(vA, vB, vC, vD);
}

inline void hkFourTransposedPointsf::extractWithW(hkVector4fParameter wABCD, hkVector4f& vA, hkVector4f& vB, hkVector4f& vC, hkVector4f& vD) const
{
	vA = m_vertices[0];
	vB = m_vertices[1];
	vC = m_vertices[2];
	vD = wABCD;

	HK_TRANSPOSE4f(vA, vB, vC, vD);
}

//
//	Extracts the vector at index from the bundle

inline void hkFourTransposedPointsf::extract(int index, hkVector4f& vI) const
{
	HK_ASSERT(0x66e853d, index >= 0 && index < 4);

#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)

	{
		hkVector4f v[4];
		extract(v[0], v[1], v[2], v[3]);
		vI = v[index];
	}

#else

	vI.set(m_vertices[0](index), m_vertices[1](index), m_vertices[2](index), hkFloat32(0));

#endif
}

//
//	Sets the vertex bundle to the same vertex

inline void hkFourTransposedPointsf::setAll(hkVector4fParameter v)
{
	m_vertices[0].setAll(v.getComponent<0>());
	m_vertices[1].setAll(v.getComponent<1>());
	m_vertices[2].setAll(v.getComponent<2>());
}

//
//	Sets this = v - a

inline void hkFourTransposedPointsf::setSub(const hkFourTransposedPointsf& v, hkVector4fParameter a)
{
	hkVector4f ax;	ax.setAll(a.getComponent<0>());
	hkVector4f ay;	ay.setAll(a.getComponent<1>());
	hkVector4f az;	az.setAll(a.getComponent<2>());

	m_vertices[0].setSub(v.m_vertices[0], ax);
	m_vertices[1].setSub(v.m_vertices[1], ay);
	m_vertices[2].setSub(v.m_vertices[2], az);
}

//
//	Sets this = a - v

inline void hkFourTransposedPointsf::setSub(hkVector4fParameter a, const hkFourTransposedPointsf& v)
{
	hkVector4f ax;	ax.setAll(a.getComponent<0>());
	hkVector4f ay;	ay.setAll(a.getComponent<1>());
	hkVector4f az;	az.setAll(a.getComponent<2>());

	m_vertices[0].setSub(ax, v.m_vertices[0]);
	m_vertices[1].setSub(ay, v.m_vertices[1]);
	m_vertices[2].setSub(az, v.m_vertices[2]);
}

inline void hkFourTransposedPointsf::setSub(const hkFourTransposedPointsf& v, const hkFourTransposedPointsf& a)
{
	m_vertices[0].setSub(v.m_vertices[0], a.m_vertices[0]);
	m_vertices[1].setSub(v.m_vertices[1], a.m_vertices[1]);
	m_vertices[2].setSub(v.m_vertices[2], a.m_vertices[2]);
}

inline void hkFourTransposedPointsf::setAdd(const hkFourTransposedPointsf& v, const hkFourTransposedPointsf& a)
{
	m_vertices[0].setAdd(v.m_vertices[0], a.m_vertices[0]);
	m_vertices[1].setAdd(v.m_vertices[1], a.m_vertices[1]);
	m_vertices[2].setAdd(v.m_vertices[2], a.m_vertices[2]);
}

inline void hkFourTransposedPointsf::setMulC(const hkFourTransposedPointsf& v, hkVector4fParameter a)
{
	hkVector4f ax;	ax.setAll(a.getComponent<0>());
	hkVector4f ay;	ay.setAll(a.getComponent<1>());
	hkVector4f az;	az.setAll(a.getComponent<2>());

	m_vertices[0].setMul(v.m_vertices[0], ax);
	m_vertices[1].setMul(v.m_vertices[1], ay);
	m_vertices[2].setMul(v.m_vertices[2], az);
}

inline void hkFourTransposedPointsf::setMulT(const hkFourTransposedPointsf& v, hkVector4fParameter a)
{
	m_vertices[0].setMul(v.m_vertices[0], a);
	m_vertices[1].setMul(v.m_vertices[1], a);
	m_vertices[2].setMul(v.m_vertices[2], a);
}

inline void hkFourTransposedPointsf::setMul(const hkFourTransposedPointsf& v, const hkFourTransposedPointsf& a)
{
	m_vertices[0].setMul(v.m_vertices[0], a.m_vertices[0]);
	m_vertices[1].setMul(v.m_vertices[1], a.m_vertices[1]);
	m_vertices[2].setMul(v.m_vertices[2], a.m_vertices[2]);
}

inline void hkFourTransposedPointsf::setMul(const hkFourTransposedPointsf& a, hkSimdFloat32Parameter b)
{
	m_vertices[0].setMul(a.m_vertices[0], b);
	m_vertices[1].setMul(a.m_vertices[1], b);
	m_vertices[2].setMul(a.m_vertices[2], b);
}

inline void hkFourTransposedPointsf::setMin(const hkFourTransposedPointsf& v, const hkFourTransposedPointsf& a)
{
	m_vertices[0].setMin(v.m_vertices[0], a.m_vertices[0]);
	m_vertices[1].setMin(v.m_vertices[1], a.m_vertices[1]);
	m_vertices[2].setMin(v.m_vertices[2], a.m_vertices[2]);
}

inline void hkFourTransposedPointsf::setMax(const hkFourTransposedPointsf& v, const hkFourTransposedPointsf& a)
{
	m_vertices[0].setMax(v.m_vertices[0], a.m_vertices[0]);
	m_vertices[1].setMax(v.m_vertices[1], a.m_vertices[1]);
	m_vertices[2].setMax(v.m_vertices[2], a.m_vertices[2]);
}

inline void hkFourTransposedPointsf::horizontalMin( hkVector4f& minOut ) const
{
	hkVector4f min01; min01.setMin( m_vertices[0], m_vertices[1] );
	minOut.setMin( min01,  m_vertices[2] );
}

inline void hkFourTransposedPointsf::horizontalMax( hkVector4f& maxOut ) const
{
	hkVector4f max01; max01.setMax( m_vertices[0], m_vertices[1] );
	maxOut.setMax( max01,  m_vertices[2] );
}


//
//	Sets v0 = b*c0, v1 = b*c1, etc.

inline void hkFourTransposedPointsf::setOuterProduct(hkVector4fParameter b, hkVector4fParameter c)
{
	m_vertices[0].setMul(c, b.getComponent<0>());
	m_vertices[1].setMul(c, b.getComponent<1>());
	m_vertices[2].setMul(c, b.getComponent<2>());
}


//
//	Sets v0 += b*c0, v1 = b*c1, etc.

inline void hkFourTransposedPointsf::addOuterProduct(hkVector4fParameter b, hkVector4fParameter c)
{
	m_vertices[0].addMul(c, b.getComponent<0>());
	m_vertices[1].addMul(c, b.getComponent<1>());
	m_vertices[2].addMul(c, b.getComponent<2>());
}


//
//	Sets v0 -= b*c0, v1 = b*c1, etc.

inline void hkFourTransposedPointsf::subOuterProduct(hkVector4fParameter b, hkVector4fParameter c)
{
	m_vertices[0].subMul(c, b.getComponent<0>());
	m_vertices[1].subMul(c, b.getComponent<1>());
	m_vertices[2].subMul(c, b.getComponent<2>());
}


//
//	Returns the dot3 of this and a

inline void hkFourTransposedPointsf::dot3(hkVector4fParameter a, hkVector4f& dotOut) const
{
	hkVector4f ax;	ax.setBroadcast<0>(a);
	hkVector4f ay;	ay.setBroadcast<1>(a);
	hkVector4f az;	az.setBroadcast<2>(a);

	ax.mul(m_vertices[0]);
	ay.mul(m_vertices[1]);
	az.mul(m_vertices[2]);

	dotOut.setAdd(ax, ay);
	dotOut.add(az);
}

//
//	Returns the dot3 of this and a

inline void hkFourTransposedPointsf::dot3(const hkFourTransposedPointsf& a, hkVector4f& dotOut) const
{
	hkVector4f vx;	vx.setMul(m_vertices[0], a.m_vertices[0]);
	vx.addMul( m_vertices[1], a.m_vertices[1] );
	vx.addMul( m_vertices[2], a.m_vertices[2] );
	dotOut = vx;
}

//
//	Translates the points along direction dir by distances(i), i.e. x(i) = v.x(i) + dir.x * distances(i), etc..

HK_FORCE_INLINE void hkFourTransposedPointsf::setAddMul(const hkFourTransposedPointsf& v, hkVector4fParameter dir, hkVector4fParameter distances)
{
	m_vertices[0].setAddMul(v.m_vertices[0], distances, dir.getComponent<0>());
	m_vertices[1].setAddMul(v.m_vertices[1], distances, dir.getComponent<1>());
	m_vertices[2].setAddMul(v.m_vertices[2], distances, dir.getComponent<2>());
}

#if defined(HK_REAL_IS_FLOAT)
//
//	Sets this = projection of each point on the given Aabb

HK_FORCE_INLINE void hkFourTransposedPointsf::setAabbProjection(const hkFourTransposedPointsf& v, const hkAabb& aabb)
{
	{
		hkVector4f xMin;	xMin.setBroadcast<0>(aabb.m_min);
		hkVector4f xMax;	xMax.setBroadcast<0>(aabb.m_max);
		hkVector4f x;	x.setMax(xMin, v.m_vertices[0]);	m_vertices[0].setMin(xMax, x);
	}

	{
		hkVector4f yMin;	yMin.setBroadcast<1>(aabb.m_min);
		hkVector4f yMax;	yMax.setBroadcast<1>(aabb.m_max);
		hkVector4f y;	y.setMax(yMin, v.m_vertices[1]);	m_vertices[1].setMin(yMax, y);
	}

	{
		hkVector4f zMin;	zMin.setBroadcast<2>(aabb.m_min);
		hkVector4f zMax;	zMax.setBroadcast<2>(aabb.m_max);
		hkVector4f z;	z.setMax(zMin, v.m_vertices[2]);	m_vertices[2].setMin(zMax, z);
	}
}

//
//	Computes the distance from all vertices to the given Aaabb

HK_FORCE_INLINE void hkFourTransposedPointsf::computeAabbDistanceSq(const hkAabb& aabb, hkVector4f& distancesOut) const
{
	// Project points on AABB
	hkFourTransposedPointsf proj;
	proj.setAabbProjection(*this, aabb);
	proj.setSub(proj, *this);
	proj.dot3(proj, distancesOut);
}
#endif // defined(HK_REAL_IS_FLOAT)

//
//	Translates the points along direction -dir by distances(i), i.e. x(i) = v.x(i) - dir.x * distances(i), etc..

HK_FORCE_INLINE void hkFourTransposedPointsf::setSubMul(const hkFourTransposedPointsf& v, hkVector4fParameter dir, hkVector4fParameter distances)
{
	m_vertices[0].setSubMul(v.m_vertices[0], distances, dir.getComponent<0>());
	m_vertices[1].setSubMul(v.m_vertices[1], distances, dir.getComponent<1>());
	m_vertices[2].setSubMul(v.m_vertices[2], distances, dir.getComponent<2>());
}

//
//	Returns the dot4 of this and a, with the w-coordinates of this assumed to be 1

inline void hkFourTransposedPointsf::dot4xyz1(hkVector4fParameter a, hkVector4f& dotOut) const
{
	dotOut.setBroadcast<3>(a);
	dotOut.addMul(m_vertices[0], a.getComponent<0>());
	dotOut.addMul(m_vertices[1], a.getComponent<1>());
	dotOut.addMul(m_vertices[2], a.getComponent<2>());
}

//
//	Sets v0 += a, v1 += a, etc.

inline void hkFourTransposedPointsf::add(hkVector4fParameter a)
{
	hkVector4f ax; ax.setBroadcast<0>(a);
	hkVector4f ay; ay.setBroadcast<1>(a);
	hkVector4f az; az.setBroadcast<2>(a);

	m_vertices[0].add(ax);
	m_vertices[1].add(ay);
	m_vertices[2].add(az);
}

inline void hkFourTransposedPointsf::add( const hkFourTransposedPointsf& v )
{
	m_vertices[0].add(v.m_vertices[0]);
	m_vertices[1].add(v.m_vertices[1]);
	m_vertices[2].add(v.m_vertices[2]);
}

//
//	Sets v0 -= a, v1 -= a, etc.

inline void hkFourTransposedPointsf::sub(hkVector4fParameter a)
{
	hkVector4f ax; ax.setBroadcast<0>(a);
	hkVector4f ay; ay.setBroadcast<1>(a);
	hkVector4f az; az.setBroadcast<2>(a);

	m_vertices[0].sub(ax);
	m_vertices[1].sub(ay);
	m_vertices[2].sub(az);
}


inline void hkFourTransposedPointsf::sub( const hkFourTransposedPointsf& v )
{
	m_vertices[0].sub(v.m_vertices[0]);
	m_vertices[1].sub(v.m_vertices[1]);
	m_vertices[2].sub(v.m_vertices[2]);
}


//
//	Multiply all components by a
inline void hkFourTransposedPointsf::mul(hkSimdFloat32Parameter a)
{
	m_vertices[0].mul(a);
	m_vertices[1].mul(a);
	m_vertices[2].mul(a);
}

inline void hkFourTransposedPointsf::mul( const hkFourTransposedPointsf& v )
{
	m_vertices[0].mul(v.m_vertices[0]);
	m_vertices[1].mul(v.m_vertices[1]);
	m_vertices[2].mul(v.m_vertices[2]);
}


//
//	Sets this = v + u * a

inline void hkFourTransposedPointsf::setAddMulT(const hkFourTransposedPointsf& v, const hkFourTransposedPointsf& u, hkVector4fParameter a)
{
	m_vertices[0].setAddMul(v.m_vertices[0], u.m_vertices[0], a);
	m_vertices[1].setAddMul(v.m_vertices[1], u.m_vertices[1], a);
	m_vertices[2].setAddMul(v.m_vertices[2], u.m_vertices[2], a);
}

//
//	Sets this = v - u * a

inline void hkFourTransposedPointsf::setSubMulT(const hkFourTransposedPointsf& v, const hkFourTransposedPointsf& u, hkVector4fParameter a)
{
	m_vertices[0].setSubMul(v.m_vertices[0], u.m_vertices[0], a);
	m_vertices[1].setSubMul(v.m_vertices[1], u.m_vertices[1], a);
	m_vertices[2].setSubMul(v.m_vertices[2], u.m_vertices[2], a);
}

//
//	Sets this += ui * a, i = 0..3

inline void hkFourTransposedPointsf::addMulT(const hkFourTransposedPointsf& u, hkVector4fParameter a)
{
	m_vertices[0].addMul(u.m_vertices[0], a);
	m_vertices[1].addMul(u.m_vertices[1], a);
	m_vertices[2].addMul(u.m_vertices[2], a);
}

//
//	Sets this -= ui * a, i = 0..3

inline void hkFourTransposedPointsf::subMulT(const hkFourTransposedPointsf& u, hkVector4fParameter a)
{
	m_vertices[0].subMul(u.m_vertices[0], a);
	m_vertices[1].subMul(u.m_vertices[1], a);
	m_vertices[2].subMul(u.m_vertices[2], a);
}

//
//	Sets this *= a

inline void hkFourTransposedPointsf::mulT(hkVector4fParameter a)
{
	m_vertices[0].mul(a);
	m_vertices[1].mul(a);
	m_vertices[2].mul(a);
}

//
//	Sets this = cross(n, v)

inline void hkFourTransposedPointsf::setCross(hkVector4fParameter n, const hkFourTransposedPointsf& v)
{
	const hkSimdFloat32 nx = n.getComponent<0>();
	const hkSimdFloat32 ny = n.getComponent<1>();
	const hkSimdFloat32 nz = n.getComponent<2>();

	hkVector4f v0;	v0.setMul(v.m_vertices[2], ny);	// ny * z0123
	hkVector4f v1;	v1.setMul(v.m_vertices[0], nz);	// nz * x0123
	hkVector4f v2;	v2.setMul(v.m_vertices[1], nx);	// nx * y0123

	v0.subMul(v.m_vertices[1], nz);	// ny * z0123 - nz * y0123
	v1.subMul(v.m_vertices[2], nx);	// nz * x0123 - nx * z0123
	v2.subMul(v.m_vertices[0], ny);	// nx * y0123 - ny * x0123

	m_vertices[0] = v0;
	m_vertices[1] = v1;
	m_vertices[2] = v2;
}

//
//	Sets this = cross(v, n)

HK_FORCE_INLINE void hkFourTransposedPointsf::setCross(const hkFourTransposedPointsf& v, hkVector4fParameter n)
{
	const hkSimdFloat32 nx = n.getComponent<0>();
	const hkSimdFloat32 ny = n.getComponent<1>();
	const hkSimdFloat32 nz = n.getComponent<2>();

	hkVector4f v0;	v0.setMul(v.m_vertices[1], nz);	// y0123 * nz
	hkVector4f v1;	v1.setMul(v.m_vertices[2], nx);	// z0123 * nx
	hkVector4f v2;	v2.setMul(v.m_vertices[0], ny);	// x0123 * ny

	v0.subMul(v.m_vertices[2], ny);	// y0123 * nz - z0123 * ny
	v1.subMul(v.m_vertices[0], nz);	// z0123 * nx - x0123 * nz
	v2.subMul(v.m_vertices[1], nx);	// x0123 * ny - y0123 * nx

	m_vertices[0] = v0;
	m_vertices[1] = v1;
	m_vertices[2] = v2;
}

//
//	Flips the signs, i.e. v0 = sign(ax) * v0, ..., v3 = sign(aw) * v3

inline void hkFourTransposedPointsf::flipSigns(hkVector4fParameter a)
{
	m_vertices[0].setFlipSign(m_vertices[0], a);
	m_vertices[1].setFlipSign(m_vertices[1], a);
	m_vertices[2].setFlipSign(m_vertices[2], a);
}

//
//	Selects a set of vectors i.e. vi = mask(i) ? ai : bi, for i = 0..3

inline void hkFourTransposedPointsf::setSelect(hkVector4fComparisonParameter mask, const hkFourTransposedPointsf& trueVecs, const hkFourTransposedPointsf& falseVecs)
{
	m_vertices[0].setSelect(mask, trueVecs.m_vertices[0], falseVecs.m_vertices[0]);
	m_vertices[1].setSelect(mask, trueVecs.m_vertices[1], falseVecs.m_vertices[1]);
	m_vertices[2].setSelect(mask, trueVecs.m_vertices[2], falseVecs.m_vertices[2]);
}

//
//	Sets this = Transpose(m) * v

inline void hkFourTransposedPointsf::_setTransformedInverseDir(const hkMatrix3f& m, const hkFourTransposedPointsf& v)
{
	hkVector4f vDots0;	v.dot3(m.getColumn<0>(), vDots0);
	hkVector4f vDots1;	v.dot3(m.getColumn<1>(), vDots1);
	hkVector4f vDots2;	v.dot3(m.getColumn<2>(), vDots2);

	m_vertices[0] = vDots0;
	m_vertices[1] = vDots1;
	m_vertices[2] = vDots2;
}

//
//	Sets this = Transpose(Rotation(m)) * (v - Translation(m))

inline void hkFourTransposedPointsf::_setTransformedInversePos(const hkTransformf& m, const hkFourTransposedPointsf& v)
{
	hkFourTransposedPointsf tmp;
	tmp.setSub(v, m.getTranslation());

	setTransformedInverseDir(m.getRotation(), tmp);
}

//
//	Sets this = m * v

inline void hkFourTransposedPointsf::_setRotatedDir(const hkMatrix3f& m, const hkFourTransposedPointsf& v)
{
	hkVector4f outLine0, outLine1, outLine2;
	{
		const hkVector4f& c0 = m.getColumn<0>();
		const hkVector4f& l0 = v.m_vertices[0];
		const hkSimdFloat32 m00 = c0.getComponent<0>();
		const hkSimdFloat32 m10 = c0.getComponent<1>();
		const hkSimdFloat32 m20 = c0.getComponent<2>();

		outLine0.setMul(m00, l0);	// l0 = (m00 * ax, m00 * bx, m00 * cx, m00 * dx)
		outLine1.setMul(m10, l0);	// l1 = (m10 * ax, m10 * bx, m10 * cx, m10 * dx)
		outLine2.setMul(m20, l0);	// l2 = (m20 * ax, m20 * bx, m20 * cx, m20 * dx)
	}

	{
		const hkVector4f& c1 = m.getColumn<1>();
		const hkVector4f& l1 = v.m_vertices[1];
		const hkSimdFloat32 m01 = c1.getComponent<0>();
		const hkSimdFloat32 m11 = c1.getComponent<1>();
		const hkSimdFloat32 m21 = c1.getComponent<2>();

		outLine0.addMul(m01, l1);	// l0 = (m00 * ax + m01 * ay, m00 * bx + m01 * by, m00 * cx + m01 * cy, m00 * dx + m01 * dy)
		outLine1.addMul(m11, l1);	// l1 = (m10 * ax + m11 * ay, m10 * bx + m11 * by, m10 * cx + m11 * cy, m10 * dx + m11 * dy)
		outLine2.addMul(m21, l1);	// l2 = (m20 * ax + m21 * ay, m20 * bx + m01 * by, m20 * cx + m21 * cy, m20 * dx + m21 * dy)
	}

	{
		const hkVector4f& c2 = m.getColumn<2>();
		const hkVector4f& l2 = v.m_vertices[2];
		const hkSimdFloat32 m02 = c2.getComponent<0>();
		const hkSimdFloat32 m12 = c2.getComponent<1>();
		const hkSimdFloat32 m22 = c2.getComponent<2>();

		outLine0.addMul(m02, l2);	// l0 = (mLine0 * a, mLine0 * b, mLine0 * c, mLine0 * d)
		outLine1.addMul(m12, l2);	// l1 = (mLine1 * a, mLine1 * b, mLine1 * c, mLine1 * d)
		outLine2.addMul(m22, l2);	// l2 = (mLine2 * a, mLine2 * b, mLine2 * c, mLine2 * d)
	}

	m_vertices[0] = outLine0;
	m_vertices[1] = outLine1;
	m_vertices[2] = outLine2;
}

//
// 	Normalizes all 4 points

HK_FORCE_INLINE void hkFourTransposedPointsf::normalize()
{
	hkVector4f lengthsSquared;
	dot3(*this, lengthsSquared);
	
	hkVector4f lengthsInv;
	
	lengthsInv.setSqrtInverse(lengthsSquared);

	m_vertices[0].mul(lengthsInv);
	m_vertices[1].mul(lengthsInv);
	m_vertices[2].mul(lengthsInv);
}

//
//	Permutes the vectors

template <hkVectorPermutation::Permutation perm>
HK_FORCE_INLINE void hkFourTransposedPointsf::setPermutation(const hkFourTransposedPointsf& pts)
{
	m_vertices[0].setPermutation<perm>(pts.m_vertices[0]);
	m_vertices[1].setPermutation<perm>(pts.m_vertices[1]);
	m_vertices[2].setPermutation<perm>(pts.m_vertices[2]);
}

//
//	Computes the average of the four points

HK_FORCE_INLINE void hkFourTransposedPointsf::computeAverage(hkVector4f& avgOut) const
{
	hkVector4f v0, v1, v2, v3;
	extract(v0, v1, v2, v3);
	v0.add(v1);
	v2.add(v3);
	v0.add(v2);
	avgOut.setMul(hkSimdFloat32_Inv4, v0);
}

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
