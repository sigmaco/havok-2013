/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

//
//	Transforms the given array of entries into bone weights / indices

template <typename WeightType, typename IndexType>
void HK_CALL hkSkinningUtil::computeBoneIndicesAndWeights(	const hkArray<Entry>& entries, hkReal maxD, int numEntriesPerVertex,
															WeightType* HK_RESTRICT weightsOut, IndexType* HK_RESTRICT indicesOut)
{
	const hkSimdReal maxDistance = hkSimdReal::fromFloat(maxD);
	const hkSimdReal maxDistance2 = (maxDistance * maxDistance);
	hkSimdReal invMaxDistance2; invMaxDistance2.setSelect( maxDistance2.greaterZero(), maxDistance2.reciprocal(), hkSimdReal_0);
	const int numEntries = entries.getSize();

	for (int i = 0; i < numEntries; i += numEntriesPerVertex)
	{
		const Entry* cur = entries.begin() + i;

		int usedWeights = 0;
		hkSimdReal sum; sum.setZero();

		for (int j = 0; j < numEntriesPerVertex; j++)
		{
			if (cur[j].m_index >= 0)
			{
				const hkSimdReal curDist = hkSimdReal::fromFloat(cur[j].m_distanceSquared);
				hkSimdReal e; e.setSelect(curDist.less(maxDistance2), hkSimdReal_1 - (curDist * invMaxDistance2), hkSimdReal_0);
				hkSimdReal dist; dist.setMax(hkSimdReal::fromFloat(hkReal(0.001f)), e);	// To avoid division by zero if all are on the 'edge' of the bounding sphere
					
				indicesOut[i + j]	= (IndexType)(cur[j].m_index);
				dist.store<1>(&weightsOut[i + j]);
				sum.add(dist);
				usedWeights++;
			}
			else
			{
				indicesOut[i + j] = (IndexType)(0);
				weightsOut[i + j] = WeightType(0);
			}
		}

		if ( usedWeights > 0 )
		{
			hkSimdReal recipSum; recipSum.setReciprocal(sum);
			for (int j = 0; j < usedWeights; j++)
			{
				hkSimdReal w; 
				w.load<1>(&weightsOut[i + j]);
				w.mul(recipSum);
				w.store<1>(&weightsOut[i + j]);
			}
		}
		else
		{
			// None of the bones were in range... I could try and find the closest bone...
			// But for now I'll just attach to the first bone
			weightsOut[i] = WeightType(1);
		}
	}
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
