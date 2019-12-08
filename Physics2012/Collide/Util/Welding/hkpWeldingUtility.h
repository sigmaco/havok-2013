/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_WELDINGUTILITY_H
#define HK_WELDINGUTILITY_H

extern const class hkClass hkpWeldingUtilityClass;


	/// Utility functions for building and querying at runtime welding information
class hkpWeldingUtility
{
	public:
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_UTILITIES, hkpWeldingUtility );
		HK_DECLARE_REFLECTION();

		//
		// Initialization methods
		//

			/// This function must be called at initialization. It is called by the hkpWorld constructor.
		static void HK_CALL initWeldingTable(hkReal edgeNormalSnapDeltaAngle, hkReal triangleNormalSnapDeltaAngle);


		//
		// Runtime methods
		//

			/// Note: The numbering of this enum are used as offsets into 'm_sinCosTable' during the actual snapping of the collision normal
			/// to retrieve the proper snapping vector information.
		enum WeldingType
		{
			WELDING_TYPE_ANTICLOCKWISE = 0,
			WELDING_TYPE_CLOCKWISE = 4,
			WELDING_TYPE_TWO_SIDED = 5,
			WELDING_TYPE_NONE = 6
		};


			// Note: The numbering of this enum are used as offsets into 'm_sinCosTable' during the actual snapping of the collision normal
			// to retrieve the proper snapping vector information.
		enum SectorType
		{
			ACCEPT_0	= 1,
			SNAP_0		= 0,
			REJECT		= 2,
			SNAP_1		= 4,
			ACCEPT_1	= 3
		};

			/// For a given edge of a triangle, get the snap vector.
		static HK_FORCE_INLINE void calcSnapVector( const hkVector4& triangleNormal, const hkVector4& edge, int edgeBitcode, SectorType sector, hkVector4& snapVectorOut );

			/// For a given edge of a triangle and a corresponding collisionNormal, determine whether it should be snapped.
		static HK_FORCE_INLINE SectorType getSector(const hkVector4& triangleNormal, const hkVector4& collisionNormal, int edgeBitcode);		
		
			/// Snap a collision normal based on edge info.
		static HK_FORCE_INLINE void snapCollisionNormal( const hkVector4& triangleNormal, const hkVector4& edge, int edgeBitcode, SectorType sector, hkVector4& collisionNormalInOut );


			/// Determine whether an collision normal should be snapped for one sided welding.
		static HK_FORCE_INLINE hkBool shouldSnapOneSided(hkpWeldingUtility::WeldingType weldingType, const hkVector4& triangleNormal, const hkVector4& collisionNormal, int edgeBitcode );

			/// Get the snap vector for a collision with one sided welding.
		static HK_FORCE_INLINE void calcSnapVectorOneSided( const hkVector4& triangleNormal, const hkVector4& edge, int edgeBitcode, hkpWeldingUtility::WeldingType weldingType, hkVector4& snapVectorOut );

			/// Receives the vertices of the unscaled triangle, its welding info and type and the scale and calculates 
			/// the welding info for the scaled triangle. This is less accurate than calculating the welding info directly 
			/// over the scaled mesh because the resulting welding angle has been quantized twice -when the original welding 
			/// info was calculated and after scaling.
		static hkUint16 HK_CALL calcScaledWeldingInfo(const hkVector4* vertices, hkUint16 weldingInfo, hkpWeldingUtility::WeldingType weldingType, hkVector4Parameter scale);

			/// Calculates the bitcode for a given welding angle
		static int HK_CALL calcEdgeAngleBitcode(hkReal angle);

		enum NumAngles
		{
			NUM_ANGLES = 31

		};


	public:


		struct SinCosTableEntry
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_COLLIDE, hkpWeldingUtility::SinCosTableEntry );

			hkReal m_cosAccept0;
			hkReal m_sinAccept0;
			hkReal m_cosSnap0;
			hkReal m_cosSnap1;
			hkReal m_cosAccept1;
			hkReal m_sinAccept1;
		};

		static HK_ALIGN16(SinCosTableEntry m_sinCosTable[NUM_ANGLES+1]);	// the 1 is needed to make the whole array size a multiple of 6 for the spu

};


#include <Physics2012/Collide/Util/Welding/hkpWeldingUtility.inl>


#endif // HK_WELDINGUTILITY_H

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
