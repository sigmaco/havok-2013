/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_PRE_PROCESSOR_OPERATIONS_H
#define HK_PRE_PROCESSOR_OPERATIONS_H

#include <Common/Base/PreProcessor/Values/hkPreProcessorBool.h>
#include <Common/Base/PreProcessor/Values/hkPreProcessorShr.h>
#include <Common/Base/PreProcessor/Values/hkPreProcessorShl.h>
#include <Common/Base/PreProcessor/Values/hkPreProcessorLsb.h>
#include <Common/Base/PreProcessor/Values/hkPreProcessorOr.h>
#include <Common/Base/PreProcessor/Values/hkPreProcessorAnd.h>

//
//	Macro that conditionally selects t or f based on x, i.e. (x ? t : f)

#define HK_PREPROCESSOR_EVAL_IF(boolX, t, f)		HK_PREPROCESSOR_TEMP_IF(boolX, t, f)
#define HK_PREPROCESSOR_IF(x, t, f)					HK_PREPROCESSOR_EVAL_IF(HK_PREPROCESSOR_BOOL(x), t, f)

//
//	Macro that returns the Least Significant Bit of x

#define HK_PREPROCESSOR_LSB(x)					HK_PREPROCESSOR_TEMP_LSB(x)

//
//	Macro that shifts x to the right by count

#define HK_PREPROCESSOR_SHR(x, count)			HK_PREPROCESSOR_SHR_COUNT_##count(x)

//
//	Macro that shifts x to the left by count

#define HK_PREPROCESSOR_SHL(x, count)			HK_PREPROCESSOR_SHL_COUNT_##count(x)

//
//	Macro that returns A | B bitwise, 16 bits

#define HK_PREPROCESSOR_BITWISE_OR(x, y)			HK_PREPROCESSOR_BITWISE_OR_16_BITS(x, y)
#define HK_PREPROCESSOR_BITWISE_OR_3(x, y, z)		HK_PREPROCESSOR_BITWISE_OR(HK_PREPROCESSOR_BITWISE_OR(x, y), z)
#define HK_PREPROCESSOR_BITWISE_OR_4(x, y, z, w)	HK_PREPROCESSOR_BITWISE_OR(HK_PREPROCESSOR_BITWISE_OR(x, y), HK_PREPROCESSOR_BITWISE_OR(z, w))

//
//	Macro that returns A & B bitiwise, 16 bits

#define HK_PREPROCESSOR_BITWISE_AND(x, y)			HK_PREPROCESSOR_BITWISE_AND_16_BITS(x, y)

#endif	//	HK_PRE_PROCESSOR_OPERATIONS_H

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
