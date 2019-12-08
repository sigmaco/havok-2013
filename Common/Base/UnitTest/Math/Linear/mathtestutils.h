/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_MATH_TEST_UTIL_H
#define HK_MATH_TEST_UTIL_H

#include <Common/Base/UnitTest/hkUnitTest.h>
#include <Common/Base/Math/Vector/hkPackedVector3.h>


static bool hkIsEqual23BitAccurate( const hkReal& x, const hkReal& y)
{
#ifdef  HK_REAL_IS_DOUBLE
	hkInt64 a = *(hkInt64*)&x;
	hkInt64 b = *(hkInt64*)&y;
	hkInt64 accuracy = ( hkInt64(1)<<30) + (hkInt64(1)<<28);
#else
	hkInt32 a = *(hkInt32*)&x;
	hkInt32 b = *(hkInt32*)&y;
	hkInt32 accuracy = hkInt32(1)<<1;
#endif
	return (a>=b-accuracy) && (a<=b+accuracy);
}

static bool hkIsEqual12BitAccurate( const hkReal& x, const hkReal& y)
{
#ifdef  HK_REAL_IS_DOUBLE
	hkInt64 a = *(hkInt64*)&x;
	hkInt64 b = *(hkInt64*)&y;
	hkInt64 accuracy = ( hkInt64(1)<<41) + (hkInt64(1)<<39);
#else
	hkInt32 a = *(hkInt32*)&x;
	hkInt32 b = *(hkInt32*)&y;
	hkInt32 accuracy =( hkInt32(1)<<12) + (hkInt32(1)<<10);
#endif
	return (a>=b-accuracy) && (a<=b+accuracy);
}

#ifdef HK_DEBUG
static void checkEqualNan(const hkReal& x)
{
#ifdef  HK_REAL_IS_DOUBLE
	HK_TEST( *((hkUint64*)&(x)) == 0xffffffffffffffffULL);
#else
	HK_TEST( *((hkUint32*)&(x)) == 0xffffffff);
#endif
}
#endif

#endif // HK_MATH_TEST_UTIL_H

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
