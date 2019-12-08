/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

	//	Constructor. Receives the convex radii of the cast shapes and an epsilon value to
	//	control the stopping criteria.
inline hkcdGsk::LinearCastInput::LinearCastInput(hkReal convexRadiusA, hkReal convexRadiusB, hkReal eps)
{
	const hkReal radiusAB = convexRadiusA + convexRadiusB;
	const hkReal tol = radiusAB + eps;
	const hkReal tol2 = tol * tol;

	m_data.set(radiusAB, tol2, 0.0f);
}

	//	Returns convexRadiusA + convexRadiusB
inline const hkSimdReal hkcdGsk::LinearCastInput::getRadiusAB() const
{
	return m_data.getComponent<0>();
}

	//	Returns the squared termination epsilon
inline const hkSimdReal hkcdGsk::LinearCastInput::getSquaredTerminationEps() const
{
	return m_data.getComponent<1>();
}

inline void hkcdGsk::Cache::pack(int dimA, int dimB, int status, const hkcdVertex* HK_RESTRICT verticesOfAinA, const hkcdVertex* HK_RESTRICT verticesOfBinA)
{
	

	VertexId a0 =  VertexId( verticesOfAinA[0].getInt16W() );
	VertexId a1 =  VertexId( verticesOfAinA[1].getInt16W() );
	VertexId a2 =  VertexId( verticesOfAinA[2].getInt16W() );
	VertexId b0 =  VertexId( verticesOfBinA[0].getInt16W() );
	VertexId b1 =  VertexId( verticesOfBinA[1].getInt16W() );
	VertexId b2 =  VertexId( verticesOfBinA[2].getInt16W() );

	m_vertexIds[0x3 & (dimA+2)]	= b2; // last vertex, index might overspill, but can only be valid for dimA=1 and dimB=3 -> index = 3

	m_vertexIds[0]		= a0;
	m_vertexIds[1]		= a1;
	m_vertexIds[2]		= a2;

	m_vertexIds[dimA]	= b0;
	m_vertexIds[dimA+1]	= b1;			// this potentially overrides cache->m_dimAb

	setDims(dimA, dimB, status );	
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
