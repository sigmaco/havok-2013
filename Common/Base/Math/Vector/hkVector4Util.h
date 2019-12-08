/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_MATH_VECTOR4_UTIL_H
#define HK_MATH_VECTOR4_UTIL_H

#include <Common/Base/Math/Vector/hkIntVector.h>

class hkStringBuf;

template <typename FT>
class hkVector4UtilImpl
{
public:

	typedef hkVector4UtilImpl<FT> ThisType;
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_MATH, ThisType);


	/// Sets the calling vector to be the normal to the 2 vectors (b-a) and (c-a).
	///
	/// NOTE: The calculated result is not explicitly normalized.
	/// This function is particularly fast on PlayStation(R)2.
	/// Result = (b-a) cross (c-a)
	static HK_FORCE_INLINE void HK_CALL setNormalOfTriangle(typename hkRealTypes<FT>::Vector& result, typename hkRealTypes<FT>::VectorParameter a, typename hkRealTypes<FT>::VectorParameter b, typename hkRealTypes<FT>::VectorParameter c);

	/// Compute the affine transformation that maps the triangle S to the triangle D.
	static bool HK_CALL	computeAffineTransformFromTriangles(	typename hkRealTypes<FT>::VectorParameter sa, typename hkRealTypes<FT>::VectorParameter sb, typename hkRealTypes<FT>::VectorParameter sc,
																typename hkRealTypes<FT>::VectorParameter da, typename hkRealTypes<FT>::VectorParameter db, typename hkRealTypes<FT>::VectorParameter dc,
																typename hkRealTypes<FT>::Transform& transformOut);

	static HK_FORCE_INLINE typename hkRealTypes<FT>::Scalar HK_CALL atan2Approximation(typename hkRealTypes<FT>::ScalarParameter y, typename hkRealTypes<FT>::ScalarParameter x);
	static HK_FORCE_INLINE void HK_CALL atan2Approximation(typename hkRealTypes<FT>::VectorParameter y, typename hkRealTypes<FT>::VectorParameter x, typename hkRealTypes<FT>::Vector& result);
	static HK_FORCE_INLINE typename hkRealTypes<FT>::Scalar HK_CALL linearAtan2Approximation(typename hkRealTypes<FT>::ScalarParameter y, typename hkRealTypes<FT>::ScalarParameter x);
	static HK_FORCE_INLINE void HK_CALL linearAtan2Approximation(typename hkRealTypes<FT>::VectorParameter y, typename hkRealTypes<FT>::VectorParameter x, typename hkRealTypes<FT>::Vector& result);
	static HK_FORCE_INLINE typename hkRealTypes<FT>::Scalar HK_CALL linearAtan2ApproximationRough(typename hkRealTypes<FT>::ScalarParameter y, typename hkRealTypes<FT>::ScalarParameter x);
	static HK_FORCE_INLINE void HK_CALL linearAtan2ApproximationRough(typename hkRealTypes<FT>::VectorParameter y, typename hkRealTypes<FT>::VectorParameter x, typename hkRealTypes<FT>::Vector& result);
	static HK_FORCE_INLINE void HK_CALL logApproximation(typename hkRealTypes<FT>::VectorParameter v, typename hkRealTypes<FT>::Vector& result);

	static HK_FORCE_INLINE void HK_CALL convertQuaternionToRotation( typename hkRealTypes<FT>::QuaternionParameter qi, typename hkRealTypes<FT>::Rotation& rotationOut );
	static void HK_CALL convertQuaternionToRotationNoInline( typename hkRealTypes<FT>::QuaternionParameter qi, typename hkRealTypes<FT>::Rotation& rotationOut );

	/// convert 4 quaternions to 4 rotations, much faster on Xbox 360/PlayStation(R)3, no speedup on PC
	static void HK_CALL convert4QuaternionsToRotations( const typename hkRealTypes<FT>::Quaternion* quats, typename hkRealTypes<FT>::Rotation* r0Out, typename hkRealTypes<FT>::Rotation* r1Out, typename hkRealTypes<FT>::Rotation* r2Out, typename hkRealTypes<FT>::Rotation* r3Out );

	/// 
	static HK_FORCE_INLINE void HK_CALL convertFromHalf( const hkHalf& a, const hkHalf& b, const hkHalf& c, const hkHalf& d, typename hkRealTypes<FT>::Vector& out );

	/// Converts a vector to four 16-bit signed integer values.
	static HK_FORCE_INLINE void HK_CALL convertToInt16( typename hkRealTypes<FT>::VectorParameter in, typename hkRealTypes<FT>::VectorParameter offset, typename hkRealTypes<FT>::VectorParameter scale, hkIntUnion64& out);

	/// Converts a vector to four 16-bit unsigned integer values. Negative values are clamped to 0.
	static HK_FORCE_INLINE void HK_CALL convertToUint16( typename hkRealTypes<FT>::VectorParameter in, typename hkRealTypes<FT>::VectorParameter offset, typename hkRealTypes<FT>::VectorParameter scale, hkIntUnion64& out );

	/// Converts a vector to four 16-bit unsigned integer values, clamped between min and max. Negative values are clamped to 0.
	static HK_FORCE_INLINE void HK_CALL convertToUint16WithClip( typename hkRealTypes<FT>::VectorParameter in, typename hkRealTypes<FT>::VectorParameter offset, typename hkRealTypes<FT>::VectorParameter scale, typename hkRealTypes<FT>::VectorParameter min, typename hkRealTypes<FT>::VectorParameter max, hkIntUnion64& out);

	/// calculates a value x so that convertToUint16WithClip( out, in + x/scale, ... ) == out = int(floor( (in+offset)*scale
	static void HK_CALL getFloatToInt16FloorCorrection(typename hkRealTypes<FT>::Pod& out);

	/// 
	static HK_FORCE_INLINE void HK_CALL convertToUint32( typename hkRealTypes<FT>::VectorParameter in, typename hkRealTypes<FT>::VectorParameter offset, typename hkRealTypes<FT>::VectorParameter scale, hkUint32* out );

	///
	static HK_FORCE_INLINE void HK_CALL convertToUint32WithClip( typename hkRealTypes<FT>::VectorParameter in, typename hkRealTypes<FT>::VectorParameter offset, typename hkRealTypes<FT>::VectorParameter scale, typename hkRealTypes<FT>::VectorParameter min, typename hkRealTypes<FT>::VectorParameter max, hkUint32* out);

	/// calculates a value x so that convertToUint32WithClip( out, in + x/scale, ... ) == out = int(floor( (in+offset)*scale
	static void HK_CALL getFloatToInt32FloorCorrection(typename hkRealTypes<FT>::Pod& out);

	static HK_FORCE_INLINE void HK_CALL convertComparison(typename hkRealTypes<FT>::ComparisonParameter cin, hkVector4dComparison& cout);
	static HK_FORCE_INLINE void HK_CALL convertComparison(typename hkRealTypes<FT>::ComparisonParameter cin, hkVector4fComparison& cout);

	/// Finds a vector that is perpendicular to a line segment.
	///
	/// Achieved by constructing a vector from the segment vector with the following properties
	/// (segment vector is any vector parallel to the line segment):
	/// 1. Component with the smallest index is set to 0.
	/// 2. The remaining two component are copied into the new vector but are swapped in position.
	/// 3. One of the copied components is multiplied by -1.0 (has its sign flipped!).
	///
	/// leaving (for example):
	/// segmentVector = (x, y, z), with let's say y as the smallest component.
	/// segmentNormal = (-z, 0 , x) or (z, 0, -x), either will do.
	///
	/// This will in fact be orthogonal as (in the example) the dot product will be zero.
	/// I.e., x*-z + y*0 + z*x = 0
	///
	static HK_FORCE_INLINE void HK_CALL calculatePerpendicularVector(typename hkRealTypes<FT>::VectorParameter vectorIn, typename hkRealTypes<FT>::Vector& biVectorOut);

	/// same as calculatePerpendicularVector:
	///  - if INVERSE2= false: bi2VectorOut = vectorIn.cross(biVectorOutbut)
	///  - if INVERSE2= true: bi2VectorOut  = biVectorOutbut.cross(vectorIn)
	template<bool INVERSE2>
	static HK_FORCE_INLINE void HK_CALL calculatePerpendicularNormalizedVectors(typename hkRealTypes<FT>::VectorParameter vectorIn, typename hkRealTypes<FT>::Vector& biVectorOut, typename hkRealTypes<FT>::Vector& bi2VectorOut);

	static HK_FORCE_INLINE void HK_CALL transpose(typename hkRealTypes<FT>::Vector& v0, typename hkRealTypes<FT>::Vector& v1, typename hkRealTypes<FT>::Vector& v2);
	static HK_FORCE_INLINE void HK_CALL transpose(typename hkRealTypes<FT>::Vector& v0, typename hkRealTypes<FT>::Vector& v1, typename hkRealTypes<FT>::Vector& v2, typename hkRealTypes<FT>::Vector& v3);

	/// Transforms an array of points.
	static HK_FORCE_INLINE void HK_CALL transformPoints( const typename hkRealTypes<FT>::Transform& t, const typename hkRealTypes<FT>::Vector* vectorsIn, int numVectors, typename hkRealTypes<FT>::Vector* vectorsOut );
	static HK_FORCE_INLINE void HK_CALL transformPoints( const typename hkRealTypes<FT>::QTransform& t, const typename hkRealTypes<FT>::Vector* vectorsIn, int numVectors, typename hkRealTypes<FT>::Vector* vectorsOut );
	static HK_FORCE_INLINE void HK_CALL transformPoints( const typename hkRealTypes<FT>::QsTransform& t, const typename hkRealTypes<FT>::Vector* vectorsIn, int numVectors, typename hkRealTypes<FT>::Vector* vectorsOut );

	/// Transforms an array of points including the .w component
	static HK_FORCE_INLINE void HK_CALL mul4xyz1Points( const typename hkRealTypes<FT>::Transform& t, const typename hkRealTypes<FT>::Vector* vectorsIn, int numVectors, typename hkRealTypes<FT>::Vector* vectorsOut );

	/// Transforms an array of spheres (keeps the .w component as the radius)
	static HK_FORCE_INLINE void HK_CALL transformSpheres( const typename hkRealTypes<FT>::Transform& t, const typename hkRealTypes<FT>::Vector* vectorsIn, int numVectors, typename hkRealTypes<FT>::Vector* vectorsOut );

	/// Transforms an array of spheres (keeps the .w component as the radius)
	static HK_FORCE_INLINE void HK_CALL transformSpheres( const typename hkRealTypes<FT>::QsTransform& t, const typename hkRealTypes<FT>::Vector* vectorsIn, int numVectors, typename hkRealTypes<FT>::Vector* vectorsOut );

	/// Transforms an array of plane equations
	static HK_FORCE_INLINE void HK_CALL transformPlaneEquation( const typename hkRealTypes<FT>::Transform& t, typename hkRealTypes<FT>::VectorParameter planeIn, typename hkRealTypes<FT>::Vector& planeOut );

	/// Transforms an array of plane equations
	static HK_FORCE_INLINE void HK_CALL transformPlaneEquations( const typename hkRealTypes<FT>::Transform& t, const typename hkRealTypes<FT>::Vector* planesIn, int numPlanes, typename hkRealTypes<FT>::Vector* planesOuts );

	/// Transform a plane equation with non-uniform scaling
	static HK_FORCE_INLINE void HK_CALL transformAndScalePlane( const typename hkRealTypes<FT>::Transform& transform, const typename hkRealTypes<FT>::Vector& scale, typename hkRealTypes<FT>::Vector& planeInOut );

	/// Scale a plane equation with non-uniform scaling
	static HK_FORCE_INLINE void HK_CALL scalePlane(const typename hkRealTypes<FT>::Vector& scale, typename hkRealTypes<FT>::Vector& planeInOut );

	/// Transform a plane equation with non-uniform scaling
	static HK_FORCE_INLINE void HK_CALL translatePlane( const typename hkRealTypes<FT>::Vector& translation, typename hkRealTypes<FT>::Vector& planeInOut );

	/// Rotate an array of points.
	static HK_FORCE_INLINE void HK_CALL rotatePoints( const typename hkRealTypes<FT>::Matrix3& t, const typename hkRealTypes<FT>::Vector* vectorsIn, int numVectors, typename hkRealTypes<FT>::Vector* vectorsOut );

	/// Invert rotate an array of points.
	static HK_FORCE_INLINE void HK_CALL rotateInversePoints( const typename hkRealTypes<FT>::Rotation& t, const typename hkRealTypes<FT>::Vector* vectorsIn, int numVectors, typename hkRealTypes<FT>::Vector* vectorsOut );

	/// set aTcOut = aTb * bTc
	static HK_FORCE_INLINE void HK_CALL setMul( const typename hkRealTypes<FT>::Matrix3& aTb, const typename hkRealTypes<FT>::Matrix3& bTc, typename hkRealTypes<FT>::Matrix3& aTcOut );

	/// set aTcOut = bTa^1 * bTc
	static HK_FORCE_INLINE void HK_CALL setInverseMul( const typename hkRealTypes<FT>::Rotation& bTa, const typename hkRealTypes<FT>::Matrix3& bTc, typename hkRealTypes<FT>::Matrix3& aTcOut );

	/// Fully unrolled version of typename hkRealTypes<FT>::Transform::_setMulInverseMul(), more code, faster
	static HK_FORCE_INLINE void HK_CALL _setMulInverseMul( const typename hkRealTypes<FT>::Transform& bTa, const typename hkRealTypes<FT>::Transform &bTc, typename hkRealTypes<FT>::Transform* tOut );

	/// Invert a 2x2 matrix stored in a vector containing col-major [r0c0, r1c0, r0c1, r1c1].
	/// Returns HK_FAILURE if determinant is less than or equal to \a tolerance.
	static HK_FORCE_INLINE hkResult HK_CALL invert2x2Matrix(typename hkRealTypes<FT>::VectorParameter m, typename hkRealTypes<FT>::ScalarParameter tolerance, typename hkRealTypes<FT>::Vector& out);

	/// Compute sin and cos in alternating components of sc.xyzw = sin(r.x) cos(r.y) sin(r.z) cos(r.w)
	static HK_FORCE_INLINE void HK_CALL sinCos(typename hkRealTypes<FT>::VectorParameter r, typename hkRealTypes<FT>::Vector& sc);

	/// Compute sin and cos from value \a r to sc.xyzw = sin(r) cos(r) sin(r) cos(r)
	static HK_FORCE_INLINE void HK_CALL sinCos(typename hkRealTypes<FT>::ScalarParameter r, typename hkRealTypes<FT>::Vector& sc);

	/// Compute sin \a s and cos \a c from value \a r
	static HK_FORCE_INLINE void HK_CALL sinCos(typename hkRealTypes<FT>::ScalarParameter r, typename hkRealTypes<FT>::Scalar& s, typename hkRealTypes<FT>::Scalar& c);

	/// Compute sin and cos in alternating components of sc.xyzw = sin(r.x) cos(r.y) sin(r.z) cos(r.w)
	/// using an approximation
	static HK_FORCE_INLINE void HK_CALL sinCosApproximation(typename hkRealTypes<FT>::VectorParameter r, typename hkRealTypes<FT>::Vector& sc);

	/// Compute sin and cos from value \a r to sc.xyzw = sin(r) cos(r) sin(r) cos(r)
	/// using an approximation
	static HK_FORCE_INLINE void HK_CALL sinCosApproximation(typename hkRealTypes<FT>::ScalarParameter r, typename hkRealTypes<FT>::Vector& sc);

	/// Compute sin \a s and cos \a c from value \a r using an approximation
	static HK_FORCE_INLINE void HK_CALL sinCosApproximation(typename hkRealTypes<FT>::ScalarParameter r, typename hkRealTypes<FT>::Scalar& s, typename hkRealTypes<FT>::Scalar& c);

	/// Compute asin in all components of sc.xyzw = asin(r.x) asin(r.y) asin(r.z) asin(r.w)
	static HK_FORCE_INLINE void HK_CALL aSin(typename hkRealTypes<FT>::VectorParameter r, typename hkRealTypes<FT>::Vector& sc);

	/// Compute acos in all components of sc.xyzw = acos(r.x) acos(r.y) acos(r.z) acos(r.w)
	static HK_FORCE_INLINE void HK_CALL aCos(typename hkRealTypes<FT>::VectorParameter r, typename hkRealTypes<FT>::Vector& sc);

	/// Compute asin and acos in alternating components of sc.xyzw = asin(r.x) acos(r.y) asin(r.z) acos(r.w)
	static HK_FORCE_INLINE void HK_CALL aSinAcos(typename hkRealTypes<FT>::VectorParameter r, typename hkRealTypes<FT>::Vector& sc);

	/// Compute asin and acos from value \a r to sc.xyzw = asin(r) acos(r) asin(r) acos(r)
	static HK_FORCE_INLINE void HK_CALL aSinAcos(typename hkRealTypes<FT>::ScalarParameter r, typename hkRealTypes<FT>::Vector& sc);

	/// Compute asin \a s and acos \a c from value \a r
	static HK_FORCE_INLINE void HK_CALL aSinAcos(typename hkRealTypes<FT>::ScalarParameter r, typename hkRealTypes<FT>::Scalar& s, typename hkRealTypes<FT>::Scalar& c);

	/// Compute from a value v another value cv in the range [-Radius,+Radius] such that cv = v-k*2*Radius with k integer.
	static HK_FORCE_INLINE const typename hkRealTypes<FT>::Scalar HK_CALL toRange(typename hkRealTypes<FT>::ScalarParameter v, typename hkRealTypes<FT>::ScalarParameter radius, typename hkRealTypes<FT>::Scalar& k);
	/// Compute from a value v another value cv in the range [-Radius,+Radius] such that cv = v-k*2*Radius with k integer. 
	/// Passing the diameter allows pre-computing it if wanted.
	static HK_FORCE_INLINE const typename hkRealTypes<FT>::Scalar HK_CALL toRange(typename hkRealTypes<FT>::ScalarParameter v, typename hkRealTypes<FT>::ScalarParameter radius, typename hkRealTypes<FT>::ScalarParameter diameter, typename hkRealTypes<FT>::Scalar& k);
	/// Compute from a value v another value cv in the range [-Radius,+Radius] such that cv = v-k*2*Radius with k integer. 
	/// Passing the diameter and its reciprocal allows pre-computing them if wanted.
	static HK_FORCE_INLINE const typename hkRealTypes<FT>::Scalar HK_CALL toRange(typename hkRealTypes<FT>::ScalarParameter v, typename hkRealTypes<FT>::ScalarParameter radius, typename hkRealTypes<FT>::ScalarParameter diameter, typename hkRealTypes<FT>::ScalarParameter diameterReciprocal, typename hkRealTypes<FT>::Scalar& k);

	/// Sets this vector components: this(0) = a0.dot<3>(b0), this(1) = a1.dot<3>(b1) ...
	static HK_FORCE_INLINE void HK_CALL dot3_3vs3( typename hkRealTypes<FT>::VectorParameter a0, typename hkRealTypes<FT>::VectorParameter b0, typename hkRealTypes<FT>::VectorParameter a1, typename hkRealTypes<FT>::VectorParameter b1, typename hkRealTypes<FT>::VectorParameter a2, typename hkRealTypes<FT>::VectorParameter b2, typename hkRealTypes<FT>::Vector& dotsOut);

	/// Sets this vector components: this(0) = a0.dot<3>(b0) ... this(3) = a3.dot<3>(b3)
	static HK_FORCE_INLINE void HK_CALL dot3_4vs4( typename hkRealTypes<FT>::VectorParameter a0, typename hkRealTypes<FT>::VectorParameter b0, typename hkRealTypes<FT>::VectorParameter a1, typename hkRealTypes<FT>::VectorParameter b1, typename hkRealTypes<FT>::VectorParameter a2, typename hkRealTypes<FT>::VectorParameter b2, typename hkRealTypes<FT>::VectorParameter a3, typename hkRealTypes<FT>::VectorParameter b3, typename hkRealTypes<FT>::Vector& dotsOut);

	/// Sets this vector components: this(0) = a0.dot<4>(b0) ... this(3) = a3.dot<4>(b3)
	static HK_FORCE_INLINE void HK_CALL dot4_4vs4( typename hkRealTypes<FT>::VectorParameter a0, typename hkRealTypes<FT>::VectorParameter b0, typename hkRealTypes<FT>::VectorParameter a1, typename hkRealTypes<FT>::VectorParameter b1, typename hkRealTypes<FT>::VectorParameter a2, typename hkRealTypes<FT>::VectorParameter b2, typename hkRealTypes<FT>::VectorParameter a3, typename hkRealTypes<FT>::VectorParameter b3, typename hkRealTypes<FT>::Vector& dotsOut);

	/// Sets this vector components: this(i) = vector.dot<3>(AI) for i=0..2
	static HK_FORCE_INLINE void HK_CALL dot3_1vs3( typename hkRealTypes<FT>::VectorParameter vectorIn, typename hkRealTypes<FT>::VectorParameter a0, typename hkRealTypes<FT>::VectorParameter a1, typename hkRealTypes<FT>::VectorParameter a2, typename hkRealTypes<FT>::Vector& dotsOut);

	/// Sets this vector components: this(i) = vector.dot<3>(AI) for i=0..3
	static HK_FORCE_INLINE void HK_CALL dot3_1vs4( typename hkRealTypes<FT>::VectorParameter vectorIn, typename hkRealTypes<FT>::VectorParameter a0, typename hkRealTypes<FT>::VectorParameter a1, typename hkRealTypes<FT>::VectorParameter a2, typename hkRealTypes<FT>::VectorParameter a3, typename hkRealTypes<FT>::Vector& dotsOut);

	/// Sets this vector components: this(i) = vector.dot<4>(AI) for i=0..3
	static HK_FORCE_INLINE void HK_CALL dot4_1vs4( typename hkRealTypes<FT>::VectorParameter vectorIn, typename hkRealTypes<FT>::VectorParameter a0, typename hkRealTypes<FT>::VectorParameter a1, typename hkRealTypes<FT>::VectorParameter a2, typename hkRealTypes<FT>::VectorParameter a3, typename hkRealTypes<FT>::Vector& dotsOut);

	/// Sets this vector components: this(i) = vector.dot<4>(AI) for i=0..2
	static HK_FORCE_INLINE void HK_CALL dot4_1vs3( typename hkRealTypes<FT>::VectorParameter vectorIn, typename hkRealTypes<FT>::VectorParameter a0, typename hkRealTypes<FT>::VectorParameter a1, typename hkRealTypes<FT>::VectorParameter a2, typename hkRealTypes<FT>::Vector& dotsOut);

	/// Sets this vector components: this(i) = vector.dot4xyz1(AI) for i=0..3
	static HK_FORCE_INLINE void HK_CALL dot4xyz1_1vs4( typename hkRealTypes<FT>::VectorParameter vectorIn, typename hkRealTypes<FT>::VectorParameter a0, typename hkRealTypes<FT>::VectorParameter a1, typename hkRealTypes<FT>::VectorParameter a2, typename hkRealTypes<FT>::VectorParameter a3, typename hkRealTypes<FT>::Vector& dotsOut);

	/// Sets this vector components: this(i+j) = AI.dot<3>(bj)
	static HK_FORCE_INLINE void HK_CALL dot3_2vs2( typename hkRealTypes<FT>::VectorParameter a0, typename hkRealTypes<FT>::VectorParameter a2, typename hkRealTypes<FT>::VectorParameter b0, typename hkRealTypes<FT>::VectorParameter b1, typename hkRealTypes<FT>::Vector& dotsOut);

	/// Computes an = (a x n), bn = (b x n), cn = (c x n)
	static HK_FORCE_INLINE void HK_CALL cross_3vs1(	typename hkRealTypes<FT>::VectorParameter a, typename hkRealTypes<FT>::VectorParameter b, typename hkRealTypes<FT>::VectorParameter c, typename hkRealTypes<FT>::VectorParameter n,
													typename hkRealTypes<FT>::Vector& an, typename hkRealTypes<FT>::Vector& bn, typename hkRealTypes<FT>::Vector& cn);

	/// Computes an = (a x n), bn = (b x n), cn = (c x n), dn = (d x n)
	static HK_FORCE_INLINE void HK_CALL cross_4vs1(	typename hkRealTypes<FT>::VectorParameter a, typename hkRealTypes<FT>::VectorParameter b, typename hkRealTypes<FT>::VectorParameter c, typename hkRealTypes<FT>::VectorParameter d, typename hkRealTypes<FT>::VectorParameter n,
													typename hkRealTypes<FT>::Vector& an, typename hkRealTypes<FT>::Vector& bn, typename hkRealTypes<FT>::Vector& cn, typename hkRealTypes<FT>::Vector& dn);

	/// Computes the cross products: (vA, vB), (vB, vC), (vC, vA)
	static HK_FORCE_INLINE void computeCyclicCrossProducts(	typename hkRealTypes<FT>::VectorParameter vA, typename hkRealTypes<FT>::VectorParameter vB, typename hkRealTypes<FT>::VectorParameter vC,
															typename hkRealTypes<FT>::Vector& vAB, typename hkRealTypes<FT>::Vector& vBC, typename hkRealTypes<FT>::Vector& vCA);

	/// Compute the normalized planes of the 4 edges of a quad.
	/// Note: if you only care about a triangle, just set vD = vA;
	static HK_FORCE_INLINE void computeQuadEdgePlanes( typename hkRealTypes<FT>::VectorParameter vA, typename hkRealTypes<FT>::VectorParameter vB, typename hkRealTypes<FT>::VectorParameter vC, typename hkRealTypes<FT>::VectorParameter vD, typename hkRealTypes<FT>::Vector* normalOut, typename hkRealTypes<FT>::Transform* edgesOut );


	/// build an orthonormal matrix, where the first column matches the parameter dir.
	/// Note: Dir must be normalized
	static HK_FORCE_INLINE void HK_CALL buildOrthonormal( typename hkRealTypes<FT>::VectorParameter dir, typename hkRealTypes<FT>::Matrix3& out );

	/// build an orthonormal matrix, where the first column matches the parameter dir and the second
	/// column matches dir2 as close as possible.
	/// Note: Dir must be normalized
	static HK_FORCE_INLINE void HK_CALL buildOrthonormal( typename hkRealTypes<FT>::VectorParameter dir, typename hkRealTypes<FT>::VectorParameter dir2, typename hkRealTypes<FT>::Matrix3& out );

	/// Resets the fpu after using MMX instructions on x86. No-op for other architectures.
	static HK_FORCE_INLINE void HK_CALL exitMmx();

	/// Returns the squared distance from p to the line segment ab
	static HK_FORCE_INLINE const typename hkRealTypes<FT>::Scalar HK_CALL distToLineSquared( typename hkRealTypes<FT>::VectorParameter a, typename hkRealTypes<FT>::VectorParameter b, typename hkRealTypes<FT>::VectorParameter p );

	/// Set the of 'out' to the maximum of 'a','b','c' and 'd'
	static HK_FORCE_INLINE void HK_CALL setMax44(typename hkRealTypes<FT>::VectorParameter a, typename hkRealTypes<FT>::VectorParameter b, typename hkRealTypes<FT>::VectorParameter c, typename hkRealTypes<FT>::VectorParameter d, typename hkRealTypes<FT>::Vector& out);

	/// Set the of 'out' to the minimum of 'a','b','c' and 'd'
	static HK_FORCE_INLINE void HK_CALL setMin44(typename hkRealTypes<FT>::VectorParameter a, typename hkRealTypes<FT>::VectorParameter b, typename hkRealTypes<FT>::VectorParameter c, typename hkRealTypes<FT>::VectorParameter d, typename hkRealTypes<FT>::Vector& out);

	/// Optimized implementation of the following code:
	///  - int index = check.getIndexOfMaxComponent<4>();
	///  - iVinOut.setAll( iVinOut.getU32(index) );
	///  - v0InOut.setAll( v0InOut(index) );
	///  - v1InOut.setAll( v1InOut(index) );
	static HK_FORCE_INLINE void HK_CALL setXAtVectorMax( typename hkRealTypes<FT>::VectorParameter check, hkIntVector& iVinOut, typename hkRealTypes<FT>::Vector& v0InOut, typename hkRealTypes<FT>::Vector& v1InOut);

	/// set the length of a vector 
	static HK_FORCE_INLINE void HK_CALL setLength( typename hkRealTypes<FT>::ScalarParameter desiredLength, typename hkRealTypes<FT>::Vector& vectorInOut );

	/// set the length of a vector so that its projected length matches desiredLength.
	static HK_FORCE_INLINE void HK_CALL setProjectedLength( typename hkRealTypes<FT>::ScalarParameter desiredLength, typename hkRealTypes<FT>::VectorParameter scaleMeasurePlane, typename hkRealTypes<FT>::ScalarParameter maxScale, typename hkRealTypes<FT>::Vector& vectorInOut );

	/// Helper function for use with hkAlgorithm::findMinimumIndex, etc.
	/// Sample usage (finding the index of the element of "vectors" that is closest to "point"):
	/// \code int minIndex = hkAlgorithm::findMinimumIndex( vectors.begin(), vectors.getSize(), hkVector4Util::DistanceToPoint( point ) ); \endcode
	struct DistanceToPoint
	{
		typedef typename hkVector4UtilImpl<FT>::DistanceToPoint DistType;
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_MATH, DistType);

		HK_FORCE_INLINE DistanceToPoint( typename hkRealTypes<FT>::VectorParameter p ) : m_p(p) { }
		HK_FORCE_INLINE typename hkRealTypes<FT>::Pod operator() (typename hkRealTypes<FT>::VectorParameter p) const { return m_p.distanceToSquared(p).getReal(); }

		typename hkRealTypes<FT>::Vector m_p;
	};

	//
	//	conversions
	//

	/// convert an typename hkRealTypes<FT>::Vector to a string representing the x,y,z components in that order.
	static const char* HK_CALL toString3(typename hkRealTypes<FT>::VectorParameter x, hkStringBuf& s, char separator=',');

	/// convert an typename hkRealTypes<FT>::Vector to a string representing the x,y,z,w components in that order.
	static const char* HK_CALL toString4(typename hkRealTypes<FT>::VectorParameter x, hkStringBuf& s, char separator=',');

	//
	//	compression
	//

	// packs a normalized quaternion into a single 4*8 bit integer. The error is roughly 0.01f per component
	static hkUint32 HK_CALL packQuaternionIntoInt32( typename hkRealTypes<FT>::VectorParameter qin);

	// unpack an 32 bit integer into quaternion. Note: The resulting quaternion is not normalized ( |q.length<4>()-1.0f| < 0.04f )
	static HK_FORCE_INLINE void HK_CALL unPackInt32IntoQuaternion( hkUint32 ivalue, typename hkRealTypes<FT>::Vector& qout );

	/// Fill each component of 'out' from components of 'a' and 'b'. i, j, k, and l are used as 0-based indices into 
	/// the 8-element concatenated vector [ax, ay, az, aw, bx, by, bz, bw].
	template<unsigned int i, unsigned int j, unsigned int k, unsigned int l>
	static HK_FORCE_INLINE void HK_CALL setPermutation2(hkVector4fParameter a, hkVector4fParameter b, hkVector4f & out);
	template<unsigned int i, unsigned int j, unsigned int k, unsigned int l>
	static HK_FORCE_INLINE void HK_CALL setPermutation2(hkVector4dParameter a, hkVector4dParameter b, hkVector4d & out);

	/// Sort the components of the vector in-place, such that the elements are put in increasing order
	static HK_FORCE_INLINE void HK_CALL sortVectorIncreasing(typename hkRealTypes<FT>::Vector& v);

	/// Sort the components of the vector in-place, such that the elements are put in decreasing order
	static HK_FORCE_INLINE void HK_CALL sortVectorDecreasing(typename hkRealTypes<FT>::Vector& v);

};


#if HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED
#	if defined(HK_COMPILER_HAS_INTRINSICS_IA32)
#			include <Common/Base/Math/Vector/Sse/hkSseVector4Util.inl>
#			if HK_SSE_VERSION >= 0x50
#				include <Common/Base/Math/Vector/Sse/hkSseVector4Util_D_AVX.inl>
#			else
#				include <Common/Base/Math/Vector/Sse/hkSseVector4Util_D.inl>
#			endif
#	elif defined(HK_PLATFORM_PS3_SPU) || defined(HK_PLATFORM_PS3_PPU)
#		include <Common/Base/Math/Vector/Ps3/hkPs3Vector4Util.inl>
#	elif defined(HK_PLATFORM_XBOX360)
#		include <Common/Base/Math/Vector/Xbox360/hkXbox360Vector4Util.inl>
#	endif
#endif // HK_CONFIG_SIMD

#include <Common/Base/Math/Vector/hkVector4Util.inl>


typedef hkVector4UtilImpl<hkFloat32>  hkVector4fUtil;
typedef hkVector4UtilImpl<hkDouble64> hkVector4dUtil;

#if defined(HK_REAL_IS_DOUBLE)
typedef hkVector4dUtil hkVector4Util;
#else
typedef hkVector4fUtil hkVector4Util;
#endif


#endif // HK_MATH_VECTOR4_UTIL_H

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
