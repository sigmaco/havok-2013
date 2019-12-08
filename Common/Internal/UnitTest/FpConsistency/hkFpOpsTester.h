/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_FP_OPS_TESTER_H
#define HK_FP_OPS_TESTER_H

#include <Common/Base/System/Io/Writer/Crc/hkCrcStreamWriter.h>



class hkFpOpsTester
{
public:
	union DoubleUnion
	{
		double m_float64;
		int m_int32[2];
	};

	//fp
	virtual void cancelOpFp(float arg1, float arg2, float arg3, float arg4);
	virtual void cancelOp2Fp(float arg1, float arg2);

	virtual float testAddFp(float arg1, float arg2);
	virtual float testSubFp(float arg1, float arg2);
	virtual float testMulFp(float arg1, float arg2);
	virtual float testDivFp(float arg1, float arg2);

	virtual float testSqrtFp(float arg1);
	virtual float testSinFp(float arg1);
	virtual float testCosFp(float arg1);
	virtual float testTanFp(float arg1);
	virtual float testLogFp(float arg1);
	virtual float testAtan2Fp(float arg1, float arg2);

	virtual void testContractionFp(float arg1, float arg2, float arg3);

	//simd
	virtual void cancelOpSimd(float arg1, float arg2, float arg3, float arg4);
	virtual void cancelOp2Simd(float arg1, float arg2);

	virtual float testAddSimd(float arg1, float arg2);
	virtual float testSubSimd(float arg1, float arg2);
	virtual float testMulSimd(float arg1, float arg2);
	virtual float testDivSimd(float arg1, float arg2);

	virtual float testSqrtSimd(float arg1);

	virtual void testContractionSimd(float arg1, float arg2, float arg3);

	//double
	virtual double testAddDouble(double arg1, double arg2);
	virtual double testMulDouble(double arg1, double arg2);
	virtual double testDivDouble(double arg1, double arg2);

	virtual double testAddDoubleSimd(double arg1, double arg2);
	virtual double testMulDoubleSimd(double arg1, double arg2);
	virtual double testDivDoubleSimd(double arg1, double arg2);


	virtual unsigned int getCrcFp();
	virtual unsigned int getCrcFpDiv(); 
	virtual unsigned int getCrcFpContract(); 
	virtual unsigned int getCrcSimd(); 
	virtual unsigned int getCrcSimdDiv(); 
	virtual unsigned int getCrcSimdContract(); 

	//functions that do not register in the writers, can still be used for testing
	float unregistered_cancelOp();
	double unregistered_cancelOpDenormDouble(double mulFactor);
	float unregistered_cancelOpSimd();

private:
	hkCrc32StreamWriter m_crcWriterFp;
	hkCrc32StreamWriter m_crcWriterFpDiv;
	hkCrc32StreamWriter m_crcWriterFpContract;
	hkCrc32StreamWriter m_crcWriterSimd;
	hkCrc32StreamWriter m_crcWriterSimdDiv;
	hkCrc32StreamWriter m_crcWriterSimdContract;
};

#endif _FP_OPS_H_

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
