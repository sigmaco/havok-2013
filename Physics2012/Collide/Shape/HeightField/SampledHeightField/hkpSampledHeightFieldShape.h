/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_COLLIDE2_SAMPLED_HEIGHT_FIELD_SHAPE_H
#define HK_COLLIDE2_SAMPLED_HEIGHT_FIELD_SHAPE_H

#include <Physics2012/Collide/Shape/HeightField/hkpHeightFieldShape.h>
#include <Physics2012/Collide/Shape/HeightField/SampledHeightField/hkpSampledHeightFieldBaseCinfo.h>
#include <Common/Base/Types/Geometry/Sphere/hkSphere.h>
#include <Common/Base/Types/Geometry/Aabb/hkAabb.h>
#include <Common/Base/Math/Vector/hkVector4Util.h>


extern const hkClass hkpSampledHeightFieldShapeClass;

/// This class implements some default behaviour for the hkpSampledHeightFieldShape.
/// It uses the y coordinate for the up axis.
/// This is a template class for 2d sampled heightfields.
/// The x and z coordinates are used to lookup a height information.
/// If you want to use this class, you need to subclass it and
/// implement the following functions:
/// \code HK_FORCE_INLINE hkReal getHeightAtImpl( int x, int z ) const \endcode
/// Which returns the height at a given x,z
/// \code HK_FORCE_INLINE hkBool getTriangleFlipImpl() \endcode
/// This should return true if two triangles share the edge p(x,z) - p(x+1,z+1).
/// This should return false if the triangles share the edge p(x,z+1) - p(x+1,z)
/// \code collideSpheres \endcode
/// This should forward to collideSpheresImplementation. This inlines your
/// getHeightAtImpl and getTriangleFlipImpl.
///
/// Example:
/// \verbatim
/// class MySampledHeightFieldShape : public hkpSampledHeightFieldShape
/// {
///     HK_FORCE_INLINE hkReal getHeightAtImpl( int x, int z ) const{ return x + y; }
///     HK_FORCE_INLINE hkBool getTriangleFlipImpl(){ return false; }
///     virtual void collideSpheres( const CollideSpheresInput& input, SphereCollisionOutput* outputArray) const
///     {
///         return collideSpheresImplementation(*this, input, outputArray);
///     }
/// };
/// \endverbatim
class hkpSampledHeightFieldShape : public hkpHeightFieldShape
{
	//+hk.ReflectedFile("hkpHeightField")
	//+version(1)
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SHAPE);
		HK_DECLARE_REFLECTION();
		HKCD_DECLARE_SHAPE_TYPE(hkcdShapeType::SAMPLED_HEIGHT_FIELD);


		enum HeightFieldType
		{
			/// hkpStorageSampledHeightFieldShape, stores values as hkReals
			HEIGHTFIELD_STORAGE = 0,

			/// hkpCompressedSampledHeightFieldShape, stores values as hkUint16s
			HEIGHTFIELD_COMPRESSED,

			/// All other heightfields use this type.
			/// It's possible to run a custom heightfield on the SPU by setting s_heightFieldFunctions[HEIGHTFIELD_USER_SPU]
			/// to point to the appropriate functions in registerHeightFieldFunctions.
			/// This is recommended for experts only.
			HEIGHTFIELD_USER, 

			HEIGHTFIELD_MAX_ID
		};


		hkpSampledHeightFieldShape( const hkpSampledHeightFieldBaseCinfo& ci, HeightFieldType type = HEIGHTFIELD_USER);

		hkpSampledHeightFieldShape( )
		:	hkpHeightFieldShape(HKCD_SHAPE_TYPE_FROM_CLASS(hkpSampledHeightFieldShape))
		{}


			/// Serialization constructor
		hkpSampledHeightFieldShape( hkFinishLoadedObjectFlag flag );


		virtual ~hkpSampledHeightFieldShape();

	public:

			/// Get the construction info for this current instance. Note that this info will reflect the current state of this object, not its original construction info.
		void getCinfo( hkpSampledHeightFieldBaseCinfo& cinfo ) const;

			/// get the height at x,z. Note x,z are already clipped.
			/// On CPU/PPU, forwards to the virtual getHeightAtImpl method.
			/// On SPU, calls the static s_getHeightAtImplPtr function
		HK_FORCE_INLINE hkReal getHeightAt( int x, int z ) const;

			/// Return true if two triangles share the edge p(x,z) - p(x+1,z+1).
			/// Return false if the triangles sphere the edge p(x,z+1) - p(x+1,z);.
			/// On CPU/PPU, forwards to the virtual getTriangleFlipImpl method.
			/// On SPU, calls the static s_getTriangleFlipImplPtr method
		HK_FORCE_INLINE hkBool getTriangleFlip() const;

			/// Build a coarse min-max quadtree for raycast optimization. 
			/// Allocates storage and calls getHeightAt on the entire height field.
			/// coarseness determines the lowest level of the quadtree. The grid size at 
			/// the lowest level will be 1<<coarseness. 
		void buildCoarseMinMaxTree(int coarseness=3);

			/// Used by the coarse heightfield raycast. Returns 4 minimum and 4 maximum height values for 4 cells 
			/// packed into the xyzw components of the vectors. The four cells have coordinates (2*x,2*z), (2*x+1,2*z), (2*x+1,2*z+1) 
			/// and (2*x,2*z+1) in the coarse grid with length 1<<level (two to the level'th power). It might help to think of level as 
			/// the mipmap level of a texture. 
		virtual void getCoarseMinMax(int level, int x, int z, hkVector4& minOut, hkVector4& maxOut) const;

			/// If you use a custom getCoarseMinMax method in a derived class you need to set the coarseness your method supports
		void setMinMaxTreeCoarseness(int coarseness);

		//
		// hkpHeightFieldShape interface implementation
		//

		///	hkpShape Interface
		virtual void getAabb(const hkTransform& localToWorld, hkReal tolerance, hkAabb& out) const;

		/// hkpHeightFieldShape interface implementation
		virtual void collideSpheres( const CollideSpheresInput& input, SphereCollisionOutput* outputArray) const;

		/// hkpHeightFieldShape interface implementation
		virtual void castSphere( const hkpSphereCastInput& input, const hkpCdBody& cdBody, hkpRayHitCollector& collector ) const;

		/// hkpShape interface implementation
		///     - output.m_extraInfo = hitX << 1 + (hitZ<<16). Lowest bit is used for triangle index.
		///
		/// Notes on the implementation:
		///     -  The ray can never tunnel through two neighbouring triangles.
		///     -  The ray is not epsilon proof when it just touches the landscape.
		///     -  The ray algorithm uses a fast walking algorithm over the landscape,
		///        that means very long rays over very big height fields cost quite some CPU
		///     -  The code is somehow fast, however quite big. Try to combine many ray queries together to minimize instruction cache hits
		///     -  Rays that are nearly vertical to the heightfield get a different optimized treatment.
		///     -  There are no restrictions on the scale, it can be anything, even negative
		///     -  If the ray starts or ends outside the heightfield, no problem, it gets clipped correctly
		///     -  the size of the heightfield is limited to 16k * 16k
		virtual hkBool castRay(const hkpShapeRayCastInput& input, hkpShapeRayCastOutput& output ) const;

		/// hkpShape interface implementation
		virtual void castRayWithCollector(const hkpShapeRayCastInput& input, const hkpCdBody& cdBody, hkpRayHitCollector& collector) const;

	public:

		//
		// Collision dispatch registration
		//

		// Use vtables on PPU as usual
		virtual hkReal getHeightAtImpl( int x, int z ) const;
		virtual hkBool getTriangleFlipImpl() const;

		//
		// Ray cast registration. Allows for code stripping of unused ray cast algorithms.
		// The function pointer below should be set to one of the ray cast methods below.
		//

		typedef void ( HK_CALL hkpSampledHeightFieldShape::*RayCastInternalFunc )( const hkpShapeRayCastInput&, const hkpCdBody&, hkpRayHitCollector& ) const;	
		static RayCastInternalFunc s_rayCastFunc;

		void HK_CALL castRayDefault		( const hkpShapeRayCastInput& input, const hkpCdBody& cdBody, hkpRayHitCollector& collector ) const;
		void HK_CALL castRayDda			( const hkpShapeRayCastInput& input, const hkpCdBody& cdBody, hkpRayHitCollector& collector ) const;
		void HK_CALL castRayCoarseTree	( const hkpShapeRayCastInput& input, const hkpCdBody& cdBody, hkpRayHitCollector& collector ) const;


		//
		// Sphere cast registration. Allows for code stripping of unused sphere cast algorithms.
		// The function pointer below should be set to one of the sphere cast methods below.
		//

		typedef void ( HK_CALL hkpSampledHeightFieldShape::*SphereCastInternalFunc )( const hkpSphereCastInput&, const hkpCdBody&, hkpRayHitCollector& ) const;	
		static SphereCastInternalFunc s_sphereCastFunc;

		void HK_CALL castSphereDefault		( const hkpSphereCastInput& input, const hkpCdBody& cdBody, hkpRayHitCollector& collector ) const;
		void HK_CALL castSphereDda			( const hkpSphereCastInput& input, const hkpCdBody& cdBody, hkpRayHitCollector& collector ) const;
		void HK_CALL castSphereCoarseTree	( const hkpSphereCastInput& input, const hkpCdBody& cdBody, hkpRayHitCollector& collector ) const;

	protected:

		// Ray casting using the 3-DDA algorithm.
		void castRayDdaInternal( const hkpShapeRayCastInput& input, const hkpCdBody& cdBody, hkBool reportPenetratingStartPosition, hkReal maxExtraPenetration, hkpRayHitCollector& collector ) const;
		
		// Ray casting using the coarse min-max tree algorithm.
		// This will only work if coarse tree information has been built with buildCoarseMinMaxTree().
		void castRayCoarseTreeInternal( const hkVector4& from, const hkVector4& to, const hkpCdBody& cdBody, hkpRayHitCollector& collector ) const;

		HK_FORCE_INLINE void _getHeightAndNormalAt( int xPos, int zPos, hkReal subX, hkReal subZ, hkVector4& normalOut, hkReal& heightOut, int& triangleIndexOut ) const;

		// inline method used by buildCoarseMinMaxTree
		HK_FORCE_INLINE void calcMinMax(int coarseness, int x, int z, hkReal& minheightOut, hkReal& maxheightOut) const;

		struct AABBStackElement 
		{
			hkAabb aabb;
			int level;
			int x;
			int z;
		};

		// inline methods used by castRayCoarseInternal
		HK_FORCE_INLINE void findStartCell(AABBStackElement& startOut, const hkVector4& from, const hkVector4& to) const;

		HK_FORCE_INLINE void rayTriangleQuadCheck(const struct hkcdRay& ray, hkAabb& aabb, int x, int z, const hkVector4Comparison& flipSelect,
												  const hkpCdBody& cdBody, hkpRayHitCollector& collector, hkSimdReal* earlyOutHitFraction) const;

	public:

		struct CoarseMinMaxLevel 
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, hkpSampledHeightFieldShape::CoarseMinMaxLevel);
			HK_DECLARE_REFLECTION();
			CoarseMinMaxLevel() {}
			CoarseMinMaxLevel(hkFinishLoadedObjectFlag f) : m_minMaxData(f) {}
			CoarseMinMaxLevel(const CoarseMinMaxLevel& l) : m_xRes(l.m_xRes), m_zRes(l.m_zRes) {m_minMaxData = l.m_minMaxData;}
			hkArray<hkVector4> m_minMaxData;
			int m_xRes;
			int m_zRes;
		};
		hkArray<CoarseMinMaxLevel> m_coarseTreeData;

		void getHeightAndNormalAt( int xPos, int zPos, hkReal subX, hkReal subZ, hkVector4& normalOut, hkReal& heightOut, int& triangleIndexOut ) const;

		// For the coarse grid (coarseness==0 means not active)
		int m_coarseness;
		hkReal m_raycastMinY;
		hkReal m_raycastMaxY;

		int m_xRes;
		int m_zRes;

		hkReal m_heightCenter;

			/// The method used to calculated the height. See hkpSampledHeightFieldBaseCinfo::m_useProjectionBasedHeight for details.
		hkBool m_useProjectionBasedHeight;

			/// Height field type. This is used to determine which getHeightAt method to call on the SPU.
		hkEnum<HeightFieldType, hkUint8> m_heightfieldType; //+default(hkpSampledHeightFieldShape::HEIGHTFIELD_USER)

		hkVector4 m_intToFloatScale;
		hkVector4 m_floatToIntScale;
		hkVector4 m_floatToIntOffsetFloorCorrected;
		hkVector4 m_extents;
};

/// Set up the ray cast function.
///
/// One of these functions should be called from the product features mechanism (hkProductFeatures.cxx).
/// The default is to register both ray casting methods. You can force one of these methods on all
/// sampled height fields, thus stripping the other from your executable, using the exclude feature macro.
/// 
/// On SPU, you have to call one of these directly from the main function in the ray casting module.
void HK_CALL HK_INIT_FUNCTION( hkpSampledHeightField_registerAllRayCastFunctions )();
void HK_CALL HK_INIT_FUNCTION( hkpSampledHeightField_registerDdaRayCastFunction )();
void HK_CALL HK_INIT_FUNCTION( hkpSampledHeightField_registerCoarseTreeRayCastFunction )();

// Work around vc6 member templates bug. Should be hkpSampledHeightFieldShape::collideSpheres.
template<typename IMPL>
HK_FORCE_INLINE void HK_CALL hkSampledHeightFieldShape_collideSpheres(
	const IMPL& shape,
	const hkpHeightFieldShape::CollideSpheresInput& input,
	hkpHeightFieldShape::SphereCollisionOutput* outputArray);


#include <Physics2012/Collide/Shape/HeightField/SampledHeightField/hkpSampledHeightFieldShape.inl>

#endif // HK_COLLIDE2_SAMPLED_HEIGHT_FIELD_SHAPE_H

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
