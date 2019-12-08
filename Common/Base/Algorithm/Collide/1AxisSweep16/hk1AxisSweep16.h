/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_1AXIS_SWEEP_16_H
#define HK_1AXIS_SWEEP_16_H

#include <Common/Base/Types/Geometry/Aabb16/hkAabb16.h>

#if !defined(HK_ARCH_PPC) && (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
#	define HK_1AXIS_SWEEP_USE_SIMD
#endif


template <typename T>
class hk1AxisSweep16
{
	public:
		struct KeyPair
		{
			T m_keyA;
			T m_keyB;
		};

		/// collide 2 lists, needs 4 padding elements at the end of pb.
		static int HK_CALL collide(
			const hkAabb16* pa, int numA,
			const hkAabb16* pb, int numB, 
			KeyPair* HK_RESTRICT pairsOut, int maxNumPairs, hkPadSpu<int>& numPairsSkipped );

		/// collide 2 lists, needs 2 padding elements at the end of pb.
		static int HK_CALL collidePadding2(
			const hkAabb16* pa, int numA,
			const hkAabb16* pb, int numB, 
			KeyPair* HK_RESTRICT pairsOut, int maxNumPairs, hkPadSpu<int>& numPairsSkipped );

		/// collide 2 lists, if HK_1AXIS_SWEEP_USE_SIMD is defined you have to pass in a buffer with size = sizeof(hkAabb16) * (numB+5)/2
		static int HK_CALL collideSIMD(
			const hkAabb16* pa, int numA,
			const hkAabb16* pb, int numB, 
			void* buffer, int bufferSizeInBytes,
			KeyPair* HK_RESTRICT pairsOut, int maxNumPairs, hkPadSpu<int>& numPairsSkipped );

		/// collide 1 list with itself, needs 4 padding elements at the end.
		static int HK_CALL collide(
			const hkAabb16* pa, int numA, 
			KeyPair* HK_RESTRICT pairsOut, int maxNumPairs, hkPadSpu<int>& numPairsSkippedOut );

		/// collide 1 list with itself, needs 2 padding elements at the end.
		static int HK_CALL collidePadding2(
			const hkAabb16* pa, int numA, 
			KeyPair* HK_RESTRICT pairsOut, int maxNumPairs, hkPadSpu<int>& numPairsSkippedOut );

		/// collide 1 list with itself trying to use SIMD code if SIMD code is faster.
		static int HK_CALL collideSIMD(
			const hkAabb16* pa, int numA, 
			void* buffer, int bufferSizeInBytes,
			KeyPair* HK_RESTRICT pairsOut, int maxNumPairs, hkPadSpu<int>& numPairsSkippedOut );

		static void HK_CALL sortAabbs(hkAabb16* aabbs, int size);
};

#endif // HK_1AXIS_SWEEP_16_H

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
