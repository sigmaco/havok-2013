/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

hk1AxisSweep::IteratorAA::IteratorAA(const hk1AxisSweep::AabbInt* pa , int numA)
:	m_aabbs(pa),
	m_numAabbs(numA)
{
	// same asserts as in hk1AxisSweep::collide
	HK_ASSERT2(0xad8751aa, numA == 0 || pa[numA-1].m_min[0] != hkUint32(-1), "numA should not include the padding elements at the end.");

#if defined(HK_DEBUG)
	{	for (int i =0 ; i < 4; i++) { HK_ASSERT2(0xad8757ab, pa[numA+i].m_min[0] == hkUint32(-1), "Four max-value padding elements are required at the end."); } }
	// assert that the input lists are sorted
	{	for (int i =0 ; i < numA-1; i++){ HK_ASSERT( 0xf0341234, pa[i].m_min[0] <= pa[i+1].m_min[0]); }	}
#endif

	m_current = 0;
	m_potential = 0;

	next();
}

hkBool32 hk1AxisSweep::IteratorAA::isValid() const HK_RESTRICT
{
	return m_current < m_numAabbs-1;
}


void hk1AxisSweep::IteratorAA::next() HK_RESTRICT
{
	// Use HK_RESTRICT since we'll be writing to *this a lot.
	m_potential++;

	if ( !isValid() )
	{
		return;
	}

	do
	{
		HK_ASSERT(0x6b13219a, m_current < m_numAabbs+4 && m_potential < m_numAabbs+4 );
		while( m_aabbs[m_potential].m_min[0] <= m_aabbs[m_current].m_max[0] )
		{
			HK_ASSERT(0x6b13219a, m_current < m_numAabbs+4 && m_potential < m_numAabbs+4 );
			if ( !hk1AxisSweep::AabbInt::yzDisjoint( m_aabbs[m_potential], m_aabbs[m_current] ) )
			{
				return;
			}
			m_potential++;
		}

		m_current++;
		m_potential = m_current+1;
		HK_ASSERT(0x6b13219a, m_current < m_numAabbs+4 && m_potential < m_numAabbs+4 );
	} while( isValid() );

}

void hk1AxisSweep::IteratorAA::getKeyPair( hkKeyPair& pair )
{
	pair.m_keyA = m_aabbs[m_current  ].getKey();
	pair.m_keyB = m_aabbs[m_potential].getKey();
}



hk1AxisSweep::IteratorAB::IteratorAB(hk1AxisSweep::AabbInt* pa, int numA, hk1AxisSweep::AabbInt* pb, int numB )
{
	// same asserts as in hk1AxisSweep::collide
	HK_ASSERT2(0xad8750aa, numA == 0 || pa[numA-1].m_min[0] != hkUint32(-1), "numA should not include the padding elements at the end.");
	HK_ASSERT2(0xad8756aa, numB == 0 || pb[numB-1].m_min[0] != hkUint32(-1), "numA should not include the padding elements at the end.");

#if defined(HK_DEBUG)
	m_totalNumA = numA;
	m_totalNumB = numB;
	m_originalA = pa;
	m_originalB = pb;

	{	for (int i =0 ; i < 4; i++) { HK_ASSERT2(0xad8757ab, pa[numA+i].m_min[0] == hkUint32(-1), "Four max-value padding elements are required at the end."); } }
	{	for (int i =0 ; i < 4; i++) { HK_ASSERT2(0xad8757ab, pb[numB+i].m_min[0] == hkUint32(-1), "Four max-value padding elements are required at the end."); } }

	// assert that the input lists are sorted
//	{	for (int i =0 ; i < numA-1; i++){ HK_ASSERT( 0xf0341232, pa[i].m_min[0] <= pa[i+1].m_min[0]); }	}
//	{	for (int i =0 ; i < numB-1; i++){ HK_ASSERT( 0xf0341233, pb[i].m_min[0] <= pb[i+1].m_min[0]); }	}
#endif

	m_pa = pa;
	m_pb = pb;
	m_numA = numA;
	m_numB = numB;

	m_aIsBigger    = ( m_pa[0].m_min[0] > m_pb[0].m_min[0] );
	m_currentPtr   = ( m_aIsBigger ? m_pb : m_pa );
	m_potentialPtr = ( m_aIsBigger ? m_pa : m_pb );

	m_potentialPtr--; // counteract the increment that happens at the start of next()
	next();
}

hkBool32 hk1AxisSweep::IteratorAB::isValid() const HK_RESTRICT
{
	return ( m_numA > 0 && m_numB > 0 );
}

void hk1AxisSweep::IteratorAB::getKeyPair( hkKeyPair& pair )
{
	const hk1AxisSweep::AabbInt* aPtr = (m_aIsBigger ? m_potentialPtr : m_pa );
	const hk1AxisSweep::AabbInt* bPtr = (m_aIsBigger ? m_pb : m_potentialPtr );

	pair.m_keyA = aPtr->getKey();
	pair.m_keyB = bPtr->getKey();
}

#define HK_1AXISSWEEP_POINTER_IN_RANGE( PTR, BASE, SIZE) ( ((PTR) >= (BASE)) && ((PTR) < (BASE) + (SIZE) ))
#define HK_1AXISSWEEP_POINTER_IN_A( PTR) ( HK_1AXISSWEEP_POINTER_IN_RANGE(PTR, m_originalA, m_totalNumA+4) )
#define HK_1AXISSWEEP_POINTER_IN_B( PTR ) ( HK_1AXISSWEEP_POINTER_IN_RANGE(PTR, m_originalB, m_totalNumB+4) )
// Check that exactly one pointer is in each range
#define HK_1AXISSWEEP_POINTERS_ARE_OK(PTRA, PTRB) (HK_1AXISSWEEP_POINTER_IN_A(PTRA) ^ HK_1AXISSWEEP_POINTER_IN_A(PTRB)) && (HK_1AXISSWEEP_POINTER_IN_B(PTRA) ^ HK_1AXISSWEEP_POINTER_IN_B(PTRB)) 
void hk1AxisSweep::IteratorAB::next() 
#if !defined(HK_BOOL32_IS_STRICT) 
	HK_RESTRICT
#endif
{
	// Use HK_RESTRICT since we'll be writing to *this a lot.
	// Also, only update local variables, then write out the "state" right before we exit.
	m_potentialPtr++;

	const hk1AxisSweep::AabbInt* HK_RESTRICT potentialPtr = m_potentialPtr;
	const hk1AxisSweep::AabbInt* HK_RESTRICT currentPtr = m_currentPtr;
	hkBool32 aIsBigger = m_aIsBigger;

	HK_ASSERT(0x287dbd56, HK_1AXISSWEEP_POINTERS_ARE_OK(currentPtr, potentialPtr) );
	do
	{
		hkUint32 maxX = currentPtr->m_max[0];

		HK_ASSERT(0x287dbd57, HK_1AXISSWEEP_POINTERS_ARE_OK(currentPtr, potentialPtr) );
		while( potentialPtr->m_min[0] < maxX )
		{
			int ov0 = hk1AxisSweep::AabbInt::yzDisjoint( *currentPtr, *potentialPtr );
			if ( !ov0 )
			{
				// Write back the "state" 
				m_potentialPtr = potentialPtr;
				m_currentPtr = currentPtr;
				m_aIsBigger = aIsBigger;

				return;
			}
			potentialPtr++;
			HK_ASSERT(0x287dbd58, HK_1AXISSWEEP_POINTERS_ARE_OK(currentPtr, potentialPtr) );
		}

		(aIsBigger ? m_pb   : m_pa   )++;
		(aIsBigger ? m_numB : m_numA )--;

		HK_ASSERT(0x287dbd59,HK_1AXISSWEEP_POINTERS_ARE_OK(m_pa, m_pb) );
		aIsBigger    = ( m_pa[0].m_min[0] > m_pb[0].m_min[0] );
		currentPtr   = (aIsBigger ? m_pb : m_pa );
		potentialPtr = (aIsBigger ? m_pa : m_pb );

	} while ( isValid() );
}

#undef HK_1AXISSWEEP_POINTER_IN_RANGE
#undef HK_1AXISSWEEP_POINTER_IN_A
#undef HK_1AXISSWEEP_POINTER_IN_B
#undef HK_1AXISSWEEP_POINTERS_ARE_OK

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
