/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */


HK_FORCE_INLINE hkReal hkpSampledHeightFieldShape::getHeightAt( int x, int z ) const
{
	return getHeightAtImpl(x, z);
}

HK_FORCE_INLINE hkBool hkpSampledHeightFieldShape::getTriangleFlip() const
{
	return getTriangleFlipImpl();
}

template<class IMPL>
HK_FORCE_INLINE void HK_CALL hkSampledHeightFieldShape_collideSpheres(
	const IMPL& impl,
	const hkpHeightFieldShape::CollideSpheresInput& input,
	hkpHeightFieldShape::SphereCollisionOutput* outputArray )
{
	const hkSphere* spheres = input.m_spheres;
	hkpHeightFieldShape::SphereCollisionOutput* output = outputArray;

	hkVector4 defNormal;
	defNormal.set( 0,1,0,HK_REAL_MAX);

	for (int i = input.m_numSpheres -1; i>=0; output++, spheres++, i--)
	{
		output[0] = defNormal;

		hkVector4 pos; 	pos.setMul( spheres->getPosition(), impl.m_floatToIntScale );

		HK_ALIGN16(hkIntUnion64 out);
		hkVector4Util::convertToInt16( spheres->getPosition(), impl.m_floatToIntOffsetFloorCorrected, impl.m_floatToIntScale, out );
		hkInt32 x = out.u16[0];
		hkInt32 z = out.u16[2];


		//
		//	Check for boundaries
		//
		if ( (x >= (impl.m_xRes-1) ) || (z >= (impl.m_zRes-1) ) || (pos.getComponent<0>().isLessZero() | pos.getComponent<2>().isLessZero()) )
		{
			continue;
		}

		hkReal subX = pos(0) - hkReal(x);
		hkReal subZ = pos(2) - hkReal(z);

		//HK_ASSERT(0x668a555b,  subX >= 0.0f && subX <= 1.0f );
		//HK_ASSERT(0x20de02d8,  subZ >= 0.0f && subZ <= 1.0f );

		hkReal height;
		hkReal vertHeight;
		int 	vertX;
 		if ( impl.IMPL::getTriangleFlip() )
		{
			hkReal h00 = impl.IMPL::getHeightAt( x+0, z   );
			vertHeight = h00;
			vertX = x;
			hkReal h11 = impl.IMPL::getHeightAt( x+1, z+1 );
			if ( subX > subZ )
			{
				hkReal h10 = impl.IMPL::getHeightAt( x+1, z   );

				hkReal dx = h10 - h00;
				hkReal dz = h11 - h10;

				height = h00  + subZ * dz + subX * dx;

				output[0](0) = -dx;
				output[0](2) = -dz;
			}
			else
			{
				hkReal h01 = impl.IMPL::getHeightAt( x, z+1 );

				hkReal dx = h11 - h01;
				hkReal dz = h01 - h00;

				height = h00  + subZ * dz + subX * dx;

				output[0](0) = -dx;
				output[0](2) = -dz;
			}
		}
		else
		{
			hkReal h10 = impl.IMPL::getHeightAt( x+1, z  );
			vertHeight = h10;
			vertX = x+1;
			hkReal h01 = impl.IMPL::getHeightAt( x,   z+1 );
			if ( subX + subZ > 1.0f )
			{
				hkReal h11 = impl.IMPL::getHeightAt( x+1, z+1 );

				hkReal dx = h11 - h01;
				hkReal dz = h11 - h10;

				height = h10  + subZ * dz + (subX - 1.0f) * dx;

				output[0](0) = -dx;
				output[0](2) = -dz;
			}
			else
			{
				hkReal h00 = impl.IMPL::getHeightAt( x+0, z   );

				hkReal dx = h10 - h00;
				hkReal dz = h01 - h00;

				height = h00  + subZ * dz + subX * dx;

				output[0](0) = -dx;
				output[0](2) = -dz;
			}
		}

		output->mul( impl.m_floatToIntScale ); // reverse multiply to correct for optimized cross product
		output->normalize<3>();

		hkSimdReal absoluteDepth;
		if (!impl.m_useProjectionBasedHeight)
		{
			absoluteDepth = (pos.getComponent<1>() - hkSimdReal::fromFloat(height)) * impl.m_intToFloatScale.template getComponent<1>() - spheres->getRadiusSimdReal();
		}
		else
		{	
			hkVector4 triangleVert;	triangleVert.set((hkReal)vertX, vertHeight,(hkReal)z);
	
			hkVector4 vectorToTri;
			vectorToTri.setSub(pos, triangleVert);
			vectorToTri.mul(impl.m_intToFloatScale);

			hkSimdReal distanceToTri = output->dot<3>(vectorToTri);
			absoluteDepth = distanceToTri - spheres->getRadiusSimdReal();
		}
		output[0].setW(absoluteDepth);
	}
}


HK_FORCE_INLINE void hkpSampledHeightFieldShape::_getHeightAndNormalAt( int x, int z, hkReal subX, hkReal subZ, hkVector4& normalOut, hkReal& heightOut, int& triangleIndexOut ) const
{
	normalOut.setXYZ( hkReal(1) );

	if ( getTriangleFlip() )
	{
		hkReal h00 = this->getHeightAt( x+0, z   );
		hkReal h11 = this->getHeightAt( x+1, z+1 );
		if ( subX > subZ )
		{
			hkReal h10 = this->getHeightAt( x+1, z   );

			hkReal dx = h10 - h00;
			hkReal dz = h11 - h10;

			heightOut = h00  + subZ * dz + subX * dx;

			normalOut(0) = -dx;
			normalOut(2) = -dz;
			triangleIndexOut = 1;
		}
		else
		{
			hkReal h01 = this->getHeightAt( x, z+1 );

			hkReal dx = h11 - h01;
			hkReal dz = h01 - h00;

			heightOut = h00  + subZ * dz + subX * dx;

			normalOut(0) = -dx;
			normalOut(2) = -dz;
			triangleIndexOut = 0;
		}
	}
	else
	{
		hkReal h10 = this->getHeightAt( x+1, z  );
		hkReal h01 = this->getHeightAt( x,   z+1 );
		if ( subX + subZ > 1.0f )
		{
			hkReal h11 = this->getHeightAt( x+1, z+1 );

			hkReal dx = h11 - h01;
			hkReal dz = h11 - h10;

			heightOut = h10  + subZ * dz + (subX - 1.0f) * dx;

			normalOut(0) = -dx;
			normalOut(2) = -dz;
			triangleIndexOut = 1;
		}
		else
		{
			hkReal h00 = this->getHeightAt( x+0, z   );

			hkReal dx = h10 - h00;
			hkReal dz = h01 - h00;

			heightOut = h00  + subZ * dz + subX * dx;

			normalOut(0) = -dx;
			normalOut(2) = -dz;
			triangleIndexOut = 0;
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
