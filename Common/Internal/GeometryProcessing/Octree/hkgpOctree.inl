/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

//
template <typename OCTREE>
inline void	hkgpOctree::enumerateDual(OCTREE& octree)
{
	// Enumerate all tetrehedra from the octree root.
	hkInplaceArray<Dual,64> stack; stack.pushBack(Dual(octree.getRoot()));
	do
	{
		const Dual	dual = stack.back(); stack.popBack();
		bool		hasChildren[8];
		bool		valid = false;
		bool		anyHasChildren = false;
		
		// Fetch cells info.
		for(int i=0; i<dual.m_type; ++i)
		{
			hasChildren[i]	=	octree.hasChildren(dual[i]);
			anyHasChildren	|=	hasChildren[i];
			valid			|=	octree.isValid(dual[i]);
		}

		// Process dual.
		switch(dual.m_type)
		{
			// INVALID
		case Dual::INVALID:
			HK_ERROR(0xE0CDF3B8, "Internal error");
			break;

			// VERTEX
		case	Dual::VERTEX:
			if(anyHasChildren && valid)
			{
				// Build volume.
				Dual	volume; volume.m_type = Dual::VOLUME;
				for(int i=0; i<8; ++i)
				{
					volume[i] = octree.getChild(dual[0],i);
				}

				// => VERTEX
				for(int i=0; i<8; ++i)
				{
					stack.pushBack(Dual(volume[i]));
				}
				
				// => EDGE
				for(int i=0; i<12; ++i)
				{
					const Dual::Axis	axis = (Dual::Axis) (i >> 2);
					const int*			idx = lut_edges[i];
					stack.pushBack(Dual(axis, volume[idx[0]], volume[idx[1]]));
				}
				
				// => FACE
				for(int i=0; i<6; ++i)
				{
					const Dual::Axis	axis = (Dual::Axis) (i >> 1);
					const int*			idx = lut_faces[i];
					stack.pushBack(Dual(axis, volume[idx[0]], volume[idx[1]], volume[idx[2]], volume[idx[3]]));
				}
				
				// => VOLUME
				stack.pushBack(volume);
			}
			break;

			// EDGE
		case	Dual::EDGE:
			if(anyHasChildren && valid)
			{
				// Build volume.
				Dual	volume; volume.m_type = Dual::VOLUME;
				for(int i=0; i<8; ++i)
				{
					const int* idx = lut_edge_volumes[dual.m_axis][i];
					volume[i] = hasChildren[idx[0]] ? octree.getChild(dual[idx[0]],idx[1]) : dual[idx[0]];
				}

				// => EDGEs
				for(int i=0,o=4*dual.m_axis; i<4; ++i)
				{
					const int*	idx = lut_edges[o+i];
					stack.pushBack(Dual(dual.m_axis, volume[idx[0]], volume[idx[1]]));
				}

				// => FACEs
				for(int i=0; i<6; ++i)
				{
					const Dual::Axis axis = (Dual::Axis) (i >> 1);
					if(dual.m_axis != axis)
					{
						const int* idx = lut_faces[i];
						stack.pushBack(Dual(axis, volume[idx[0]], volume[idx[1]], volume[idx[2]], volume[idx[3]]));
					}
				}

				// => VOLUME
				stack.pushBack(volume);
			}
			break;

			// FACE
		case	Dual::FACE:
			if(anyHasChildren && valid)
			{
				// Build volume.
				Dual	volume; volume.m_type = Dual::VOLUME;
				for(int i=0; i<8; ++i)
				{
					const int* idx = lut_face_volumes[dual.m_axis][i];
					volume[i] = hasChildren[idx[0]] ? octree.getChild(dual[idx[0]],idx[1]) : dual[idx[0]];
				}
				
				// => FACEs
				for(int i=0,o=dual.m_axis*2; i<2; ++i)
				{
					const int* idx = lut_faces[o+i];
					stack.pushBack(Dual(dual.m_axis, volume[idx[0]], volume[idx[1]], volume[idx[2]], volume[idx[3]]));
				}

				// => VOLUME
				stack.pushBack(volume);
			}
			break;
			
			// VOLUME
		case	Dual::VOLUME:
			if(valid)
			{
				// Build volume.
				Dual	volume; volume.m_type = Dual::VOLUME;
				for(int i=0,j=7; i<8; ++i,--j)
				{
					volume[i] = dual[i];
					while(octree.hasChildren(volume[i])) volume[i] = octree.getChild(volume[i],j);
				}

				// Process volume.
				if(octree.processVolume(volume.m_nodes))
				{
					// Process tetrahedra.
					for(int i=0; i<6; ++i)
					{
						const int*	idx = lut_tetras[i];						
						const int	vi[4] = { volume[idx[0]], volume[idx[1]], volume[idx[2]], volume[idx[3]]};
						bool		validTetra = true;
						for(int j=0; j<4 && valid; ++j)
						{
							for(int k=j+1; k<4; ++k)
							{
								if(vi[j] == vi[k])
								{
									validTetra = false;
									break;
								}
							}
						}

						if(validTetra)
						{
							octree.processTetrahedron(vi);
						}
					}
				}
			}
			break;
		}
	} while(stack.getSize());
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
