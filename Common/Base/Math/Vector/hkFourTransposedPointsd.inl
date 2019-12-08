/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

//
//	Sets the vertex bundle to the given vertices

inline void hkFourTransposedPointsd::set(hkVector4dParameter vA, hkVector4dParameter vB, hkVector4dParameter vC, hkVector4dParameter vD)
{
	hkVector4d v0 = vA;
	hkVector4d v1 = vB;
	hkVector4d v2 = vC;
	hkVector4d v3 = vD;

	HK_TRANSPOSE4d(v0, v1, v2, v3);

	m_vertices[0] = v0;
	m_vertices[1] = v1;
	m_vertices[2] = v2;
}

//
//	Extracts the vectors from the vertex bundle

inline void hkFourTransposedPointsd::extract(hkVector4d& vA, hkVector4d& vB, hkVector4d& vC, hkVector4d& vD) const
{
	vA = m_vertices[0];
	vB = m_vertices[1];
	vC = m_vertices[2];
	vD.setZero();

	HK_TRANSPOSE4d(vA, vB, vC, vD);
}

inline void hkFourTransposedPointsd::extractWithW(hkVector4dParameter wABCD, hkVector4d& vA, hkVector4d& vB, hkVector4d& vC, hkVector4d& vD) const
{
	vA = m_vertices[0];
	vB = m_vertices[1];
	vC = m_vertices[2];
	vD = wABCD;

	HK_TRANSPOSE4d(vA, vB, vC, vD);
}

//
//	Extracts the vector at index from the bundle

inline void hkFourTransposedPointsd::extract(int index, hkVector4d& vI) const
{
	HK_ASSERT(0x66e853d, index >= 0 && index < 4);

#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	{
		hkVector4d v[4];
		extract(v[0], v[1], v[2], v[3]);
		vI = v[index];
	}
#else

	vI.set(m_vertices[0](index), m_vertices[1](index), m_vertices[2](index), hkDouble64(0));

#endif
}

//
//	Sets the vertex bundle to the same vertex

inline void hkFourTransposedPointsd::setAll(hkVector4dParameter v)
{
	m_vertices[0].setAll(v.getComponent<0>());
	m_vertices[1].setAll(v.getComponent<1>());
	m_vertices[2].setAll(v.getComponent<2>());
}

//
//	Sets this = v - a

inline void hkFourTransposedPointsd::setSub(const hkFourTransposedPointsd& v, hkVector4dParameter a)
{
	hkVector4d ax;	ax.setAll(a.getComponent<0>());
	hkVector4d ay;	ay.setAll(a.getComponent<1>());
	hkVector4d az;	az.setAll(a.getComponent<2>());

	m_vertices[0].setSub(v.m_vertices[0], ax);
	m_vertices[1].setSub(v.m_vertices[1], ay);
	m_vertices[2].setSub(v.m_vertices[2], az);
}

//
//	Sets this = a - v

inline void hkFourTransposedPointsd::setSub(hkVector4dParameter a, const hkFourTransposedPointsd& v)
{
	hkVector4d ax;	ax.setAll(a.getComponent<0>());
	hkVector4d ay;	ay.setAll(a.getComponent<1>());
	hkVector4d az;	az.setAll(a.getComponent<2>());

	m_vertices[0].setSub(ax, v.m_vertices[0]);
	m_vertices[1].setSub(ay, v.m_vertices[1]);
	m_vertices[2].setSub(az, v.m_vertices[2]);
}

inline void hkFourTransposedPointsd::setSub(const hkFourTransposedPointsd& v, const hkFourTransposedPointsd& a)
{
	m_vertices[0].setSub(v.m_vertices[0], a.m_vertices[0]);
	m_vertices[1].setSub(v.m_vertices[1], a.m_vertices[1]);
	m_vertices[2].setSub(v.m_vertices[2], a.m_vertices[2]);
}

inline void hkFourTransposedPointsd::setAdd(const hkFourTransposedPointsd& v, const hkFourTransposedPointsd& a)
{
	m_vertices[0].setAdd(v.m_vertices[0], a.m_vertices[0]);
	m_vertices[1].setAdd(v.m_vertices[1], a.m_vertices[1]);
	m_vertices[2].setAdd(v.m_vertices[2], a.m_vertices[2]);
}

inline void hkFourTransposedPointsd::setMulC(const hkFourTransposedPointsd& v, hkVector4dParameter a)
{
	hkVector4d ax;	ax.setAll(a.getComponent<0>());
	hkVector4d ay;	ay.setAll(a.getComponent<1>());
	hkVector4d az;	az.setAll(a.getComponent<2>());

	m_vertices[0].setMul(v.m_vertices[0], ax);
	m_vertices[1].setMul(v.m_vertices[1], ay);
	m_vertices[2].setMul(v.m_vertices[2], az);
}

inline void hkFourTransposedPointsd::setMulT(const hkFourTransposedPointsd& v, hkVector4dParameter a)
{
	m_vertices[0].setMul(v.m_vertices[0], a);
	m_vertices[1].setMul(v.m_vertices[1], a);
	m_vertices[2].setMul(v.m_vertices[2], a);
}

inline void hkFourTransposedPointsd::setMul(const hkFourTransposedPointsd& v, const hkFourTransposedPointsd& a)
{
	m_vertices[0].setMul(v.m_vertices[0], a.m_vertices[0]);
	m_vertices[1].setMul(v.m_vertices[1], a.m_vertices[1]);
	m_vertices[2].setMul(v.m_vertices[2], a.m_vertices[2]);
}

inline void hkFourTransposedPointsd::setMul(const hkFourTransposedPointsd& a, hkSimdDouble64Parameter b)
{
	m_vertices[0].setMul(a.m_vertices[0], b);
	m_vertices[1].setMul(a.m_vertices[1], b);
	m_vertices[2].setMul(a.m_vertices[2], b);
}

inline void hkFourTransposedPointsd::setMin(const hkFourTransposedPointsd& v, const hkFourTransposedPointsd& a)
{
	m_vertices[0].setMin(v.m_vertices[0], a.m_vertices[0]);
	m_vertices[1].setMin(v.m_vertices[1], a.m_vertices[1]);
	m_vertices[2].setMin(v.m_vertices[2], a.m_vertices[2]);
}

inline void hkFourTransposedPointsd::setMax(const hkFourTransposedPointsd& v, const hkFourTransposedPointsd& a)
{
	m_vertices[0].setMax(v.m_vertices[0], a.m_vertices[0]);
	m_vertices[1].setMax(v.m_vertices[1], a.m_vertices[1]);
	m_vertices[2].setMax(v.m_vertices[2], a.m_vertices[2]);
}

inline void hkFourTransposedPointsd::horizontalMin( hkVector4d& minOut ) const
{
	hkVector4d min01; min01.setMin( m_vertices[0], m_vertices[1] );
	minOut.setMin( min01,  m_vertices[2] );
}

inline void hkFourTransposedPointsd::horizontalMax( hkVector4d& maxOut ) const
{
	hkVector4d max01; max01.setMax( m_vertices[0], m_vertices[1] );
	maxOut.setMax( max01,  m_vertices[2] );
}


//
//	Sets v0 = b*c0, v1 = b*c1, etc.

inline void hkFourTransposedPointsd::setOuterProduct(hkVector4dParameter b, hkVector4dParameter c)
{
	m_vertices[0].setMul(c, b.getComponent<0>());
	m_vertices[1].setMul(c, b.getComponent<1>());
	m_vertices[2].setMul(c, b.getComponent<2>());
}


//
//	Sets v0 += b*c0, v1 = b*c1, etc.

inline void hkFourTransposedPointsd::addOuterProduct(hkVector4dParameter b, hkVector4dParameter c)
{
	m_vertices[0].addMul(c, b.getComponent<0>());
	m_vertices[1].addMul(c, b.getComponent<1>());
	m_vertices[2].addMul(c, b.getComponent<2>());
}


//
//	Sets v0 -= b*c0, v1 = b*c1, etc.

inline void hkFourTransposedPointsd::subOuterProduct(hkVector4dParameter b, hkVector4dParameter c)
{
	m_vertices[0].subMul(c, b.getComponent<0>());
	m_vertices[1].subMul(c, b.getComponent<1>());
	m_vertices[2].subMul(c, b.getComponent<2>());
}


//
//	Returns the dot3 of this and a

inline void hkFourTransposedPointsd::dot3(hkVector4dParameter a, hkVector4d& dotOut) const
{
	hkVector4d ax;	ax.setBroadcast<0>(a);
	hkVector4d ay;	ay.setBroadcast<1>(a);
	hkVector4d az;	az.setBroadcast<2>(a);

	ax.mul(m_vertices[0]);
	ay.mul(m_vertices[1]);
	az.mul(m_vertices[2]);

	dotOut.setAdd(ax, ay);
	dotOut.add(az);
}

//
//	Returns the dot3 of this and a

inline void hkFourTransposedPointsd::dot3(const hkFourTransposedPointsd& a, hkVector4d& dotOut) const
{
	hkVector4d vx;	vx.setMul(m_vertices[0], a.m_vertices[0]);
	vx.addMul( m_vertices[1], a.m_vertices[1] );
	vx.addMul( m_vertices[2], a.m_vertices[2] );
	dotOut = vx;
}

//
//	Translates the points along direction dir by distances(i), i.e. x(i) = v.x(i) + dir.x * distances(i), etc..

HK_FORCE_INLINE void hkFourTransposedPointsd::setAddMul(const hkFourTransposedPointsd& v, hkVector4dParameter dir, hkVector4dParameter distances)
{
	m_vertices[0].setAddMul(v.m_vertices[0], distances, dir.getComponent<0>());
	m_vertices[1].setAddMul(v.m_vertices[1], distances, dir.getComponent<1>());
	m_vertices[2].setAddMul(v.m_vertices[2], distances, dir.getComponent<2>());
}

#if defined(HK_REAL_IS_DOUBLE)
//
//	Sets this = projection of each point on the given Aabb
HK_FORCE_INLINE void hkFourTransposedPointsd::setAabbProjection(const hkFourTransposedPointsd& v, const hkAabb& aabb)
{
	{
		hkVector4d xMin;	xMin.setBroadcast<0>(aabb.m_min);
		hkVector4d xMax;	xMax.setBroadcast<0>(aabb.m_max);
		hkVector4d x;	x.setMax(xMin, v.m_vertices[0]);	m_vertices[0].setMin(xMax, x);
	}

	{
		hkVector4d yMin;	yMin.setBroadcast<1>(aabb.m_min);
		hkVector4d yMax;	yMax.setBroadcast<1>(aabb.m_max);
		hkVector4d y;	y.setMax(yMin, v.m_vertices[1]);	m_vertices[1].setMin(yMax, y);
	}

	{
		hkVector4d zMin;	zMin.setBroadcast<2>(aabb.m_min);
		hkVector4d zMax;	zMax.setBroadcast<2>(aabb.m_max);
		hkVector4d z;	z.setMax(zMin, v.m_vertices[2]);	m_vertices[2].setMin(zMax, z);
	}
}

//
//	Computes the distance from all vertices to the given Aaabb
HK_FORCE_INLINE void hkFourTransposedPointsd::computeAabbDistanceSq(const hkAabb& aabb, hkVector4d& distancesOut) const
{
	// Project points on AABB
	hkFourTransposedPointsd proj;
	proj.setAabbProjection(*this, aabb);
	proj.setSub(proj, *this);
	proj.dot3(proj, distancesOut);
}
#endif // defined(HK_REAL_IS_DOUBLE)

//
//	Translates the points along direction -dir by distances(i), i.e. x(i) = v.x(i) - dir.x * distances(i), etc..

HK_FORCE_INLINE void hkFourTransposedPointsd::setSubMul(const hkFourTransposedPointsd& v, hkVector4dParameter dir, hkVector4dParameter distances)
{
	m_vertices[0].setSubMul(v.m_vertices[0], distances, dir.getComponent<0>());
	m_vertices[1].setSubMul(v.m_vertices[1], distances, dir.getComponent<1>());
	m_vertices[2].setSubMul(v.m_vertices[2], distances, dir.getComponent<2>());
}

//
//	Returns the dot4 of this and a, with the w-coordinates of this assumed to be 1

inline void hkFourTransposedPointsd::dot4xyz1(hkVector4dParameter a, hkVector4d& dotOut) const
{
	dotOut.setBroadcast<3>(a);
	dotOut.addMul(m_vertices[0], a.getComponent<0>());
	dotOut.addMul(m_vertices[1], a.getComponent<1>());
	dotOut.addMul(m_vertices[2], a.getComponent<2>());
}

//
//	Sets v0 += a, v1 += a, etc.

inline void hkFourTransposedPointsd::add(hkVector4dParameter a)
{
	hkVector4d ax; ax.setBroadcast<0>(a);
	hkVector4d ay; ay.setBroadcast<1>(a);
	hkVector4d az; az.setBroadcast<2>(a);

	m_vertices[0].add(ax);
	m_vertices[1].add(ay);
	m_vertices[2].add(az);
}

inline void hkFourTransposedPointsd::add( const hkFourTransposedPointsd& v )
{
	m_vertices[0].add(v.m_vertices[0]);
	m_vertices[1].add(v.m_vertices[1]);
	m_vertices[2].add(v.m_vertices[2]);
}

//
//	Sets v0 -= a, v1 -= a, etc.

inline void hkFourTransposedPointsd::sub(hkVector4dParameter a)
{
	hkVector4d ax; ax.setBroadcast<0>(a);
	hkVector4d ay; ay.setBroadcast<1>(a);
	hkVector4d az; az.setBroadcast<2>(a);

	m_vertices[0].sub(ax);
	m_vertices[1].sub(ay);
	m_vertices[2].sub(az);
}


inline void hkFourTransposedPointsd::sub( const hkFourTransposedPointsd& v )
{
	m_vertices[0].sub(v.m_vertices[0]);
	m_vertices[1].sub(v.m_vertices[1]);
	m_vertices[2].sub(v.m_vertices[2]);
}


//
//	Multiply all components by a
inline void hkFourTransposedPointsd::mul(hkSimdDouble64Parameter a)
{
	m_vertices[0].mul(a);
	m_vertices[1].mul(a);
	m_vertices[2].mul(a);
}

inline void hkFourTransposedPointsd::mul( const hkFourTransposedPointsd& v )
{
	m_vertices[0].mul(v.m_vertices[0]);
	m_vertices[1].mul(v.m_vertices[1]);
	m_vertices[2].mul(v.m_vertices[2]);
}


//
//	Sets this = v + u * a

inline void hkFourTransposedPointsd::setAddMulT(const hkFourTransposedPointsd& v, const hkFourTransposedPointsd& u, hkVector4dParameter a)
{
	m_vertices[0].setAddMul(v.m_vertices[0], u.m_vertices[0], a);
	m_vertices[1].setAddMul(v.m_vertices[1], u.m_vertices[1], a);
	m_vertices[2].setAddMul(v.m_vertices[2], u.m_vertices[2], a);
}

//
//	Sets this = v - u * a

inline void hkFourTransposedPointsd::setSubMulT(const hkFourTransposedPointsd& v, const hkFourTransposedPointsd& u, hkVector4dParameter a)
{
	m_vertices[0].setSubMul(v.m_vertices[0], u.m_vertices[0], a);
	m_vertices[1].setSubMul(v.m_vertices[1], u.m_vertices[1], a);
	m_vertices[2].setSubMul(v.m_vertices[2], u.m_vertices[2], a);
}

//
//	Sets this += ui * a, i = 0..3

inline void hkFourTransposedPointsd::addMulT(const hkFourTransposedPointsd& u, hkVector4dParameter a)
{
	m_vertices[0].addMul(u.m_vertices[0], a);
	m_vertices[1].addMul(u.m_vertices[1], a);
	m_vertices[2].addMul(u.m_vertices[2], a);
}

//
//	Sets this -= ui * a, i = 0..3

inline void hkFourTransposedPointsd::subMulT(const hkFourTransposedPointsd& u, hkVector4dParameter a)
{
	m_vertices[0].subMul(u.m_vertices[0], a);
	m_vertices[1].subMul(u.m_vertices[1], a);
	m_vertices[2].subMul(u.m_vertices[2], a);
}

//
//	Sets this *= a

inline void hkFourTransposedPointsd::mulT(hkVector4dParameter a)
{
	m_vertices[0].mul(a);
	m_vertices[1].mul(a);
	m_vertices[2].mul(a);
}

//
//	Sets this = cross(n, v)

inline void hkFourTransposedPointsd::setCross(hkVector4dParameter n, const hkFourTransposedPointsd& v)
{
	const hkSimdDouble64 nx = n.getComponent<0>();
	const hkSimdDouble64 ny = n.getComponent<1>();
	const hkSimdDouble64 nz = n.getComponent<2>();

	hkVector4d v0;	v0.setMul(v.m_vertices[2], ny);	// ny * z0123
	hkVector4d v1;	v1.setMul(v.m_vertices[0], nz);	// nz * x0123
	hkVector4d v2;	v2.setMul(v.m_vertices[1], nx);	// nx * y0123

	v0.subMul(v.m_vertices[1], nz);	// ny * z0123 - nz * y0123
	v1.subMul(v.m_vertices[2], nx);	// nz * x0123 - nx * z0123
	v2.subMul(v.m_vertices[0], ny);	// nx * y0123 - ny * x0123

	m_vertices[0] = v0;
	m_vertices[1] = v1;
	m_vertices[2] = v2;
}

//
//	Sets this = cross(v, n)

HK_FORCE_INLINE void hkFourTransposedPointsd::setCross(const hkFourTransposedPointsd& v, hkVector4dParameter n)
{
	const hkSimdDouble64 nx = n.getComponent<0>();
	const hkSimdDouble64 ny = n.getComponent<1>();
	const hkSimdDouble64 nz = n.getComponent<2>();

	hkVector4d v0;	v0.setMul(v.m_vertices[1], nz);	// y0123 * nz
	hkVector4d v1;	v1.setMul(v.m_vertices[2], nx);	// z0123 * nx
	hkVector4d v2;	v2.setMul(v.m_vertices[0], ny);	// x0123 * ny

	v0.subMul(v.m_vertices[2], ny);	// y0123 * nz - z0123 * ny
	v1.subMul(v.m_vertices[0], nz);	// z0123 * nx - x0123 * nz
	v2.subMul(v.m_vertices[1], nx);	// x0123 * ny - y0123 * nx

	m_vertices[0] = v0;
	m_vertices[1] = v1;
	m_vertices[2] = v2;
}

//
//	Flips the signs, i.e. v0 = sign(ax) * v0, ..., v3 = sign(aw) * v3

inline void hkFourTransposedPointsd::flipSigns(hkVector4dParameter a)
{
	m_vertices[0].setFlipSign(m_vertices[0], a);
	m_vertices[1].setFlipSign(m_vertices[1], a);
	m_vertices[2].setFlipSign(m_vertices[2], a);
}

//
//	Selects a set of vectors i.e. vi = mask(i) ? ai : bi, for i = 0..3

inline void hkFourTransposedPointsd::setSelect(hkVector4dComparisonParameter mask, const hkFourTransposedPointsd& trueVecs, const hkFourTransposedPointsd& falseVecs)
{
	m_vertices[0].setSelect(mask, trueVecs.m_vertices[0], falseVecs.m_vertices[0]);
	m_vertices[1].setSelect(mask, trueVecs.m_vertices[1], falseVecs.m_vertices[1]);
	m_vertices[2].setSelect(mask, trueVecs.m_vertices[2], falseVecs.m_vertices[2]);
}

//
//	Sets this = Transpose(m) * v

inline void hkFourTransposedPointsd::_setTransformedInverseDir(const hkMatrix3d& m, const hkFourTransposedPointsd& v)
{
	hkVector4d vDots0;	v.dot3(m.getColumn<0>(), vDots0);
	hkVector4d vDots1;	v.dot3(m.getColumn<1>(), vDots1);
	hkVector4d vDots2;	v.dot3(m.getColumn<2>(), vDots2);

	m_vertices[0] = vDots0;
	m_vertices[1] = vDots1;
	m_vertices[2] = vDots2;
}

//
//	Sets this = Transpose(Rotation(m)) * (v - Translation(m))

inline void hkFourTransposedPointsd::_setTransformedInversePos(const hkTransformd& m, const hkFourTransposedPointsd& v)
{
	hkFourTransposedPointsd tmp;
	tmp.setSub(v, m.getTranslation());

	setTransformedInverseDir(m.getRotation(), tmp);
}

//
//	Sets this = m * v

inline void hkFourTransposedPointsd::_setRotatedDir(const hkMatrix3d& m, const hkFourTransposedPointsd& v)
{
	hkVector4d outLine0, outLine1, outLine2;
	{
		const hkVector4d& c0 = m.getColumn<0>();
		const hkVector4d& l0 = v.m_vertices[0];
		const hkSimdDouble64 m00 = c0.getComponent<0>();
		const hkSimdDouble64 m10 = c0.getComponent<1>();
		const hkSimdDouble64 m20 = c0.getComponent<2>();

		outLine0.setMul(m00, l0);	// l0 = (m00 * ax, m00 * bx, m00 * cx, m00 * dx)
		outLine1.setMul(m10, l0);	// l1 = (m10 * ax, m10 * bx, m10 * cx, m10 * dx)
		outLine2.setMul(m20, l0);	// l2 = (m20 * ax, m20 * bx, m20 * cx, m20 * dx)
	}

	{
		const hkVector4d& c1 = m.getColumn<1>();
		const hkVector4d& l1 = v.m_vertices[1];
		const hkSimdDouble64 m01 = c1.getComponent<0>();
		const hkSimdDouble64 m11 = c1.getComponent<1>();
		const hkSimdDouble64 m21 = c1.getComponent<2>();

		outLine0.addMul(m01, l1);	// l0 = (m00 * ax + m01 * ay, m00 * bx + m01 * by, m00 * cx + m01 * cy, m00 * dx + m01 * dy)
		outLine1.addMul(m11, l1);	// l1 = (m10 * ax + m11 * ay, m10 * bx + m11 * by, m10 * cx + m11 * cy, m10 * dx + m11 * dy)
		outLine2.addMul(m21, l1);	// l2 = (m20 * ax + m21 * ay, m20 * bx + m01 * by, m20 * cx + m21 * cy, m20 * dx + m21 * dy)
	}

	{
		const hkVector4d& c2 = m.getColumn<2>();
		const hkVector4d& l2 = v.m_vertices[2];
		const hkSimdDouble64 m02 = c2.getComponent<0>();
		const hkSimdDouble64 m12 = c2.getComponent<1>();
		const hkSimdDouble64 m22 = c2.getComponent<2>();

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

HK_FORCE_INLINE void hkFourTransposedPointsd::normalize()
{
	hkVector4d lengthsSquared;
	dot3(*this, lengthsSquared);
	
	hkVector4d lengthsInv;
	
	lengthsInv.setSqrtInverse(lengthsSquared);

	m_vertices[0].mul(lengthsInv);
	m_vertices[1].mul(lengthsInv);
	m_vertices[2].mul(lengthsInv);
}

//
//	Permutes the vectors

template <hkVectorPermutation::Permutation perm>
HK_FORCE_INLINE void hkFourTransposedPointsd::setPermutation(const hkFourTransposedPointsd& pts)
{
	m_vertices[0].setPermutation<perm>(pts.m_vertices[0]);
	m_vertices[1].setPermutation<perm>(pts.m_vertices[1]);
	m_vertices[2].setPermutation<perm>(pts.m_vertices[2]);
}

//
//	Computes the average of the four points

HK_FORCE_INLINE void hkFourTransposedPointsd::computeAverage(hkVector4d& avgOut) const
{
	hkVector4d v0, v1, v2, v3;
	extract(v0, v1, v2, v3);
	v0.add(v1);
	v2.add(v3);
	v0.add(v2);
	avgOut.setMul(hkSimdDouble64_Inv4, v0);
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
