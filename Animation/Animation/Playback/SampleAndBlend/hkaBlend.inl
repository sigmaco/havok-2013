/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */


static HK_FORCE_INLINE void doBlendAddMul4(hkQsTransform* base, const hkQsTransform* sample, const hkVector4& sampleWeights)
{
	hkQsTransform b0, b1, b2, b3;
	b0 = base[0];
	b1 = base[1];
	b2 = base[2];
	b3 = base[3];

	hkQsTransform s0, s1, s2, s3;
	s0 = sample[0];
	s1 = sample[1];
	s2 = sample[2];
	s3 = sample[3];

	b0.blendAddMul(s0, sampleWeights.getSimdAt(0));
	b1.blendAddMul(s1, sampleWeights.getSimdAt(1));
	b2.blendAddMul(s2, sampleWeights.getSimdAt(2));
	b3.blendAddMul(s3, sampleWeights.getSimdAt(3));

	base[0] = b0;
	base[1] = b1;
	base[2] = b2;
	base[3] = b3;
}
static HK_FORCE_INLINE void doBlendAddMul4(hkReal* base, const hkReal* sample, const hkVector4& sampleWeights)
{
	hkVector4 v; v.load4a(base);
	hkVector4 s; s.load4a(sample);
	v.addMul4(s, sampleWeights);
	v.store4a(base);
}
static HK_FORCE_INLINE void doBlendSetMul4(hkQsTransform* base, const hkQsTransform* sample, const hkVector4& sampleWeights)
{
	hkQsTransform s0, s1, s2, s3;
	s0 = sample[0];
	s1 = sample[1];
	s2 = sample[2];
	s3 = sample[3];

	s0.blendWeight(sampleWeights.getSimdAt(0));
	s1.blendWeight(sampleWeights.getSimdAt(1));
	s2.blendWeight(sampleWeights.getSimdAt(2));
	s3.blendWeight(sampleWeights.getSimdAt(3));

	base[0] = s0;
	base[1] = s1;
	base[2] = s2;
	base[3] = s3;
}

static HK_FORCE_INLINE void doBlendSetMul4(hkReal* base, const hkReal* sample, const hkVector4& sampleWeights)
{
	hkVector4 s; s.load4a(sample);
	s.setMul4(s, sampleWeights);
	s.store4a(base);
}


template <class Type, int flags>
void HK_CALL hkaBlend::blendAddMul(	Type* base, hkReal* baseW,
									const Type* sample, const hkReal* sampleW, hkSimdRealParameter sampleAlpha,
									int n)
{
	enum
	{
		useSampleW = flags & BLEND_USE_SAMPLE_WEIGHT, 
		useSampleAlpha = flags & BLEND_USE_SAMPLE_ALPHA,
		useBase = flags & BLEND_USE_BASE
	};

	HK_COMPILE_TIME_ASSERT(useSampleW || useSampleAlpha); // must be at least one blending parameter

	HK_ASSERT2( 0x0ebd6e86, ( hkUlong( base ) & 0x0F ) == 0, "base must be 16 byte aligned" );
	HK_ASSERT2( 0x1955457a, ( hkUlong( sample ) & 0x0F ) == 0, "sample must be 16 byte aligned." );

	if (useSampleW)
	{
		HK_ASSERT2( 0x109d48dc, ( hkUlong( baseW) & 0x0F ) == 0, "baseW must be 16 byte aligned." );
		HK_ASSERT2( 0x1a8e0ebc, ( hkUlong( sampleW ) & 0x0F ) == 0, "sampleW must be 16 byte aligned." );
	}
	if (!useSampleAlpha)
	{
		HK_ASSERT(0xfd32ba31, sampleAlpha.getReal() == 1.0f);
	}


	hkVector4 alphav;
	alphav.setAll( sampleAlpha );

	const int num = ( n + 3 ) / 4;

	hkVector4* baseWV = reinterpret_cast< hkVector4* >( baseW );
	const hkVector4* sampleWV = reinterpret_cast< const hkVector4* >( sampleW );

	for ( int i = 0; i < num; ++i, base += 4, sample += 4)
	{
		// calculate weights
		hkVector4 sampleWeights;
		if (useSampleAlpha && useSampleW)
		{
			sampleWeights.setMul4(alphav, *sampleWV);
		}
		else if (useSampleAlpha)
		{
			sampleWeights = alphav;
		}
		else if (useSampleW)
		{
			sampleWeights = *sampleWV;
		}

		if (useBase)
		{
			doBlendAddMul4(base, sample, sampleWeights);
		}
		else
		{
			doBlendSetMul4(base, sample, sampleWeights);
		}


		if (useBase)
		{
			baseWV->setAdd4(*baseWV, sampleWeights);
		}
		else
		{
			*baseWV = sampleWeights;
		}
		++baseWV;
		if (useSampleW)
		{
			++sampleWV;
		}
	}
}

static HK_FORCE_INLINE void doBlendAdditive4(hkQsTransform* base, const hkQsTransform* sample, const hkVector4& sampleWeights)
{
	// Additive transforms are multiplied in, so they need to be attenuated toward identity.
	// Therefore, we use the additive weight as an interpolant between the original bone and
	// the bone after having had the additive transform multiplied in.

	// the original bones
	hkQsTransform b0, b1, b2, b3;
	b0 = base[0];
	b1 = base[1];
	b2 = base[2];
	b3 = base[3];

	// the additive transforms
	hkQsTransform s0, s1, s2, s3;
	s0 = sample[0];
	s1 = sample[1];
	s2 = sample[2];
	s3 = sample[3];

	// the original bone combined with the additive transform with a weight of 1
	hkQsTransform a0, a1, a2, a3;
	a0.setMul( s0, b0 );
	a1.setMul( s1, b1 );
	a2.setMul( s2, b2 );
	a3.setMul( s3, b3 );

	// interpolate between the original bones and the combined bones
	b0.setInterpolate4(b0, a0, sampleWeights.getSimdAt(0));
	b1.setInterpolate4(b1, a1, sampleWeights.getSimdAt(1));
	b2.setInterpolate4(b2, a2, sampleWeights.getSimdAt(2));
	b3.setInterpolate4(b3, a3, sampleWeights.getSimdAt(3));

	base[0] = b0;
	base[1] = b1;
	base[2] = b2;
	base[3] = b3;
}

static HK_FORCE_INLINE void doBlendAdditive4(hkReal* base, const hkReal* sample, const hkVector4& sampleWeights)
{
	doBlendAddMul4( base, sample, sampleWeights );
}

template <class Type, int flags>
void HK_CALL hkaBlend::blendAdditive(	Type* base,
										const Type* sample, const hkReal* sampleW, hkSimdRealParameter sampleAlpha, // new pose
										int n)
{
	enum
	{
		useSampleW = flags & BLEND_USE_SAMPLE_WEIGHT, 
		useSampleAlpha = flags & BLEND_USE_SAMPLE_ALPHA,
		useBase = flags & BLEND_USE_BASE
	};

	HK_COMPILE_TIME_ASSERT(useSampleW || useSampleAlpha); // must be at least one blending parameter
	HK_COMPILE_TIME_ASSERT(useBase); // you have to use the base pose

	HK_ASSERT2( 0x0ebd6e86, ( hkUlong( base ) & 0x0F ) == 0, "base must be 16 byte aligned" );
	HK_ASSERT2( 0x1955457a, ( hkUlong( sample ) & 0x0F ) == 0, "sample must be 16 byte aligned." );

	if (useSampleW)
	{
		HK_ASSERT2( 0x1a8e0ebc, ( hkUlong( sampleW ) & 0x0F ) == 0, "sampleW must be 16 byte aligned." );
	}
	if (!useSampleAlpha)
	{
		HK_ASSERT( 0xfd32ba31, sampleAlpha.getReal() == 1.0f );
	}

	hkVector4 alphav;
	alphav.setAll( sampleAlpha );

	const int num = ( n + 3 ) / 4;

	const hkVector4* sampleWV = reinterpret_cast< const hkVector4* >( sampleW );

	for ( int i = 0; i < num; ++i, base += 4, sample += 4)
	{
		// calculate weights
		hkVector4 sampleWeights;
		if (useSampleAlpha && useSampleW)
		{
			sampleWeights.setMul4(alphav, *sampleWV);
		}
		else if (useSampleAlpha)
		{
			sampleWeights = alphav;
		}
		else if (useSampleW)
		{
			sampleWeights = *sampleWV;
		}

		doBlendAdditive4(base, sample, sampleWeights);

		if (useSampleW)
		{
			++sampleWV;
		}
	}
}

static HK_FORCE_INLINE void doBlendNormalize4(hkReal* floats, hkVector4Parameter weights, int nleft)
{
	hkVector4 data; data.load4a(floats);
	data.setDiv4(data, weights);
	data.store4a(floats);
}

namespace hkaBlend
{
	template <>
	void HK_FORCE_INLINE blendNormalize<hkReal>(hkReal* floats, hkReal* weights, int n)
	{
		HK_ASSERT2( 0x0ebd6e86, ( hkUlong( floats ) & 0x0F ) == 0, "transforms must be 16 byte aligned" );
		HK_ASSERT2( 0x1955457a, ( hkUlong( weights ) & 0x0F ) == 0, "weights must be 16 byte aligned." );
		hkVector4* weightV = reinterpret_cast<hkVector4*>(weights);
		for (int i=0; i<n; i+=4)
		{
			hkVector4 w = *weightV;
			doBlendNormalize4(floats, w, n - i);

			floats += 4;
			weightV++;
		}
	}

	template <>
	void HK_FORCE_INLINE blendNormalize<hkQsTransform>(hkQsTransform* poseOut, hkReal* weight, int numTransforms)
	{
		hkQsTransform::fastRenormalizeBatch( poseOut, weight, numTransforms );
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
