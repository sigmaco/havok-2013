/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_MATH_STRIDEDVERTICES
#define HK_MATH_STRIDEDVERTICES

	///	Simple structure to contain information about vertex arrays.
struct hkStridedVertices
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE_CLASS, hkStridedVertices );
		/// Pointer to the array of vertices
	const hkReal* m_vertices;

		/// The number of vertices in the array.
	int m_numVertices;

		/// The striding is the byte difference between one float triple
		/// and the next float triple (so usually 12 or 16 or greater).
	int m_striding;

	
	/// Initialize as empty
	hkStridedVertices() : m_numVertices(0)	{}
	
	/// Initialize with an array of hkVector4
	hkStridedVertices(const hkArrayBase<hkVector4>& vertices) { set(vertices); }
	
	/// Initialize with a pointer to hkVector4
	hkStridedVertices(const hkVector4* vertices, int count) { set(vertices,count); }

	/// Return the number of vertices.
	HK_FORCE_INLINE int	getSize() const { return(m_numVertices); }

	/// Retrieve a vertex
	HK_FORCE_INLINE void getVertex(int index, hkVector4& vertexOut) const
	{
		HK_ASSERT2(0x15625423,index>=0 && index<m_numVertices,"Index out of range");
		const hkReal* pv=(const hkReal*) (((const hkUint8*)m_vertices) + m_striding*index);
		vertexOut.set(pv[0],pv[1],pv[2],m_striding>=(int)sizeof(hkVector4)?pv[3]:0);
	}
	
	inline void set(const hkArrayBase<hkVector4>& vertices)
	{
		set(vertices.begin(),vertices.getSize());
	}

	template <typename T>
	inline void set(const T* vertices, int numVertices)
	{
		HK_ASSERT(0x75cf3975, sizeof(T)>sizeof(hkReal)*3 );
		m_vertices		=	(const hkReal*)vertices;
		m_numVertices	=	numVertices;
		m_striding		=	sizeof(T);
	}

};

#endif // HK_MATH_STRIDEDVERTICES

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
