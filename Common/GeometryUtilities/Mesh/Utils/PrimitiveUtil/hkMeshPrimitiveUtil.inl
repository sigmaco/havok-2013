/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

//
//	Constructor

HK_FORCE_INLINE hkMeshPrimitiveUtil::PrimitiveProvider::PrimitiveProvider(const void* ptr, hkMeshSection::PrimitiveType primitiveType, hkMeshSection::MeshSectionIndexType indexType)
:	m_a(-1)
,	m_b(-1)
,	m_c(-1)
,	m_primitiveType(primitiveType)
,	m_indexType(indexType)
,	m_bufferIdx(0)
,	m_primitiveIdx(0)
{
	m_ptr = const_cast<hkUint8*>(reinterpret_cast<const hkUint8*>(ptr));
}

//
//	Reads a single index

HK_FORCE_INLINE int hkMeshPrimitiveUtil::PrimitiveProvider::readIndex()
{
	if ( !m_ptr )											return m_bufferIdx++;	// No indices
	if ( m_indexType == hkMeshSection::INDEX_TYPE_UINT16)	return reinterpret_cast<hkUint16*>(m_ptr)[m_bufferIdx++];
	else													return reinterpret_cast<hkUint32*>(m_ptr)[m_bufferIdx++];
}

//
//	Writes a single index

HK_FORCE_INLINE void hkMeshPrimitiveUtil::PrimitiveProvider::writeIndex(int idx)
{
	if ( !m_ptr )	return;
	if ( m_indexType == hkMeshSection::INDEX_TYPE_UINT16 )	{	reinterpret_cast<hkUint16*>(m_ptr)[m_bufferIdx++] = (hkUint16)idx; }
	else													{	reinterpret_cast<hkUint32*>(m_ptr)[m_bufferIdx++] = (hkUint32)idx; }
}

//
//	Reads a primitive

HK_FORCE_INLINE void hkMeshPrimitiveUtil::PrimitiveProvider::readPrimitive()
{
	switch ( m_primitiveType )
	{
	case hkMeshSection::PRIMITIVE_TYPE_POINT_LIST:
		{
			m_a = readIndex();
			m_b = m_a;
			m_c = m_a;
		}
		break;

	case hkMeshSection::PRIMITIVE_TYPE_LINE_LIST:
		{
			m_a = readIndex();
			m_b = readIndex();
			m_c = m_b;
		}
		break;

	case hkMeshSection::PRIMITIVE_TYPE_TRIANGLE_STRIP:
		{
			if ( m_a < 0 )
			{
				m_a = readIndex();
				m_b = readIndex();
				m_c = readIndex();
			}
			else
			{
				m_a = m_b;
				m_b = m_c;
				m_c = readIndex();
				if ( m_primitiveIdx & 1 )
				{
					int tmp = m_b;
					m_b = m_c;
					m_c = tmp;
				}
			}
		}
		break;

	case hkMeshSection::PRIMITIVE_TYPE_TRIANGLE_LIST:
		{
			m_a = readIndex();
			m_b = readIndex();
			m_c = readIndex();
		}
		break;

	default:
		{
			// Should never get here!
			HK_ASSERT(0x7e4161a5, false);
		}
		break;
	}

	m_primitiveIdx++;
}

//
//	Writes a primitive

HK_FORCE_INLINE void hkMeshPrimitiveUtil::PrimitiveProvider::writePrimitive(int vidxA, int vidxB, int vidxC)
{
	switch ( m_primitiveType )
	{
	case hkMeshSection::PRIMITIVE_TYPE_POINT_LIST:
		{
			writeIndex(vidxA);
		}
		break;

	case hkMeshSection::PRIMITIVE_TYPE_LINE_LIST:
		{
			writeIndex(vidxA);
			writeIndex(vidxB);
		}
		break;

	case hkMeshSection::PRIMITIVE_TYPE_TRIANGLE_STRIP:
		{
			if ( m_a < 0 )
			{
				writeIndex(vidxA);
				writeIndex(vidxB);
				writeIndex(vidxC);

			}
			else if ( (vidxA != m_a) && (vidxA != m_b) && (vidxA != m_c) )	{	writeIndex(vidxA);	}
			else if ( (vidxB != m_a) && (vidxB != m_b) && (vidxB != m_c) )	{	writeIndex(vidxB);	}
			else															{	writeIndex(vidxC);	}
		}
		break;

	case hkMeshSection::PRIMITIVE_TYPE_TRIANGLE_LIST:
		{
			writeIndex(vidxA);
			writeIndex(vidxB);
			writeIndex(vidxC);
		}
		break;

	default:
		{
			// Should never get here!
			HK_ASSERT(0x7e4161a5, false);
		}
		break;
	}

	m_a = vidxA;	m_b = vidxB;	m_c = vidxC;
	m_primitiveIdx++;
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
