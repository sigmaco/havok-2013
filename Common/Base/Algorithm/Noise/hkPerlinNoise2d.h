/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_PERLIN_NOISE_H
#define HK_PERLIN_NOISE_H

#include <Common/Base/Algorithm/PseudoRandom/hkPseudoRandomGenerator.h>

class hkPerlinNoise2d : public hkReferencedObject
{
public:

	HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_DEMO_FRAMEWORK );

	hkPerlinNoise2d(int seed, int N)
	{
		hkPseudoRandomGenerator random(seed+2);
		m_frequency.setFromFloat(0.015f);    
		m_persistence.setFromFloat(0.65f); 
		m_amplitude = hkSimdReal_1;   
		m_coverage = hkSimdReal_Inv4;

		m_octaves = 8;    
		m_N = N;
		m_r1 = 10*seed + hkMath::hkToIntFast(random.getRandRange(1.0e3f, 1.0e4f));
		m_r2 = 1000*seed + hkMath::hkToIntFast(random.getRandRange(1.0e5f, 1.0e6f));
		m_r3 = 1000000*seed + hkMath::hkToIntFast(random.getRandRange(1.0e8f, 1.0e9f));
	}

	hkSimdReal m_frequency;    
	hkSimdReal m_persistence;   
	hkSimdReal m_amplitude;   
	hkSimdReal m_coverage;

	int m_octaves;  
	int m_N;
	int m_r1;
	int m_r2;
	int m_r3;

	HK_FORCE_INLINE hkSimdReal _lerp(hkSimdRealParameter x, hkSimdRealParameter y, hkSimdRealParameter t) const
	{
		const hkSimdReal val = (hkSimdReal_1 - hkSimdReal::fromFloat(hkMath::cos((t * hkSimdReal_Pi).getReal()))) * hkSimdReal_Half;
		return x * (hkSimdReal_1 - val) + y * val;
	} 

	HK_FORCE_INLINE hkSimdReal _noise(int x, int y) const
	{
		int n = x + y*m_N;
		n = (n<<13) ^ n;
		return hkSimdReal_1 - hkSimdReal::fromInt32( (n * (n * n * m_r1 + m_r2) + m_r3) & 0x7fffffff) * hkSimdReal::fromFloat(1.0f / 1073741824.f);
	} 

	HK_FORCE_INLINE hkSimdReal _smooth(hkSimdRealParameter x, hkSimdRealParameter y) const
	{
		int xi; x.storeSaturateInt32(&xi); int xp = xi+1; const hkSimdReal xr = x-hkSimdReal::fromInt32(xi);
		int yi; y.storeSaturateInt32(&yi); int yp = yi+1; const hkSimdReal yr = y-hkSimdReal::fromInt32(yi);

		return _lerp(_lerp(_noise(xi, yi), _noise(xp, yi), xr), 
			         _lerp(_noise(xi, yp), _noise(xp, yp), xr), yr);
	} 

	// Get non-tiling noise value in range [0,1] at grid points x, y (in range 0,N-1)
	HK_FORCE_INLINE hkSimdReal ntn(hkSimdRealParameter x, hkSimdRealParameter y) const
	{
		hkSimdReal total; total.setZero();
		hkSimdReal amplitude = m_amplitude;
		hkSimdReal frequency = m_frequency;

		for(int lcv = 0; lcv<m_octaves; lcv++)
		{
			total.add(_smooth(x * frequency, y * frequency) * amplitude);
			frequency.mul(hkSimdReal_2);
			amplitude.mul(m_persistence);
		}

		total.add(m_coverage);
		return total;
	}

	HK_FORCE_INLINE hkSimdReal _scurve(hkSimdRealParameter x) const
	{
		return x * x * x * (hkSimdReal::fromFloat(10.0f) - hkSimdReal::fromFloat(15.0f) * x  + hkSimdReal_6 * x * x);
	}

	// Get tiling noise value in range [0,1] at grid points x, y (in range 0,N-1)
	HK_FORCE_INLINE hkSimdReal getValue(int x, int y) const
	{
		const hkSimdReal fx = hkSimdReal::fromInt32(x);
		const hkSimdReal fy = hkSimdReal::fromInt32(y);
		int top = m_N-1;
		const hkSimdReal ftop = hkSimdReal::fromInt32(top);
		const hkSimdReal topr = ftop.reciprocal();
		const hkSimdReal xr = _scurve(fx*topr);
		const hkSimdReal yr = _scurve(fy*topr);

		const hkSimdReal t_x = ftop - fx;
		const hkSimdReal t_y = ftop - fy;
		const hkSimdReal oxr = hkSimdReal_1 - xr;
		const hkSimdReal oyr = hkSimdReal_1 - yr;

		hkSimdReal tile; tile.setZero();
		tile.add(  xr *  yr * ntn(fx,  fy));
		tile.add( oxr *  yr * ntn(t_x, fy));
		tile.add( oyr *  xr * ntn(fx,  t_y));
		tile.add( oxr * oyr * ntn(t_x, t_y));
		return tile;
	}
};

#endif // HK_PERLIN_NOISE_H

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
