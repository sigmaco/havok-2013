/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#include <Common/Base/PreProcessor/hkPreProcessor.h>

//
// Function IDs. These are duplicates of hkpShapeVirtualTableUtil::FunctionId so that the pre-processor can work with the values
//

#define	HKP_FUNCTION_ID_getSupportingVertex				1
#define	HKP_FUNCTION_ID_convertVertexIdsToVertices		2
#define HKP_FUNCTION_ID_weldContactPoint				4
#define HKP_FUNCTION_ID_getCentre						8
#define HKP_FUNCTION_ID_getNumCollisionSpheres			16
#define HKP_FUNCTION_ID_getCollisionSpheres				32
#define HKP_FUNCTION_ID_getAabb							64
#define HKP_FUNCTION_ID_castRay							128
#define HKP_FUNCTION_ID_castRayWithCollector			256
#define HKP_FUNCTION_ID_castRayBundle					512
#define HKP_FUNCTION_ID_getChildShape					1024
#define HKP_FUNCTION_ID_getCollisionFilterInfo			2048

// Make sure the IDs match
HK_COMPILE_TIME_ASSERT( hkpShapeVirtualTableUtil::FUNCTION_ID_getSupportingVertex			== HKP_FUNCTION_ID_getSupportingVertex );
HK_COMPILE_TIME_ASSERT( hkpShapeVirtualTableUtil::FUNCTION_ID_convertVertexIdsToVertices	== HKP_FUNCTION_ID_convertVertexIdsToVertices );
HK_COMPILE_TIME_ASSERT( hkpShapeVirtualTableUtil::FUNCTION_ID_weldContactPoint				== HKP_FUNCTION_ID_weldContactPoint );
HK_COMPILE_TIME_ASSERT( hkpShapeVirtualTableUtil::FUNCTION_ID_getCentre						== HKP_FUNCTION_ID_getCentre );
HK_COMPILE_TIME_ASSERT( hkpShapeVirtualTableUtil::FUNCTION_ID_getNumCollisionSpheres		== HKP_FUNCTION_ID_getNumCollisionSpheres );
HK_COMPILE_TIME_ASSERT( hkpShapeVirtualTableUtil::FUNCTION_ID_getCollisionSpheres			== HKP_FUNCTION_ID_getCollisionSpheres );
HK_COMPILE_TIME_ASSERT( hkpShapeVirtualTableUtil::FUNCTION_ID_getAabb						== HKP_FUNCTION_ID_getAabb );
HK_COMPILE_TIME_ASSERT( hkpShapeVirtualTableUtil::FUNCTION_ID_castRay						== HKP_FUNCTION_ID_castRay );
HK_COMPILE_TIME_ASSERT( hkpShapeVirtualTableUtil::FUNCTION_ID_castRayWithCollector			== HKP_FUNCTION_ID_castRayWithCollector );
HK_COMPILE_TIME_ASSERT( hkpShapeVirtualTableUtil::FUNCTION_ID_castRayBundle					== HKP_FUNCTION_ID_castRayBundle );

// Define a mask of all the above
#define __FID_MASK_0__				HK_PREPROCESSOR_BITWISE_OR( HKP_FUNCTION_ID_getSupportingVertex,	HKP_FUNCTION_ID_convertVertexIdsToVertices )
#define __FID_MASK_1__				HK_PREPROCESSOR_BITWISE_OR( HKP_FUNCTION_ID_weldContactPoint,		HKP_FUNCTION_ID_getCentre )
#define __FID_MASK_2__				HK_PREPROCESSOR_BITWISE_OR( HKP_FUNCTION_ID_getNumCollisionSpheres,	HKP_FUNCTION_ID_getCollisionSpheres )
#define __FID_MASK_3__				HK_PREPROCESSOR_BITWISE_OR( HKP_FUNCTION_ID_getAabb,				HKP_FUNCTION_ID_castRay )
#define __FID_MASK_4__				HK_PREPROCESSOR_BITWISE_OR( HKP_FUNCTION_ID_castRayWithCollector,	HKP_FUNCTION_ID_castRayBundle )
#define __FID_MASK_01__				HK_PREPROCESSOR_BITWISE_OR( __FID_MASK_0__, __FID_MASK_1__ )
#define __FID_MASK_23__				HK_PREPROCESSOR_BITWISE_OR( __FID_MASK_2__, __FID_MASK_3__ )
#	define HKP_FUNCTION_ID_MASK		HK_PREPROCESSOR_BITWISE_OR_3( __FID_MASK_01__, __FID_MASK_23__,	__FID_MASK_4__ )


//
// Function sets
//

#define HKP_FUNCTION_SET_NONE					0	// No functions

#define HKP_FUNCTION_SET_AABB					HKP_FUNCTION_ID_getAabb

#define HKP_FUNCTION_SET_AABB_CHILD_FILTER		HK_PREPROCESSOR_BITWISE_OR_3(	HKP_FUNCTION_ID_getAabb, \
																				HKP_FUNCTION_ID_getChildShape,\
																				HKP_FUNCTION_ID_getCollisionFilterInfo )

#define HKP_FUNCTION_SET_COLLIDE_QUERY			HK_PREPROCESSOR_BITWISE_OR_4(	HKP_FUNCTION_ID_getAabb, \
																				HKP_FUNCTION_ID_convertVertexIdsToVertices, \
																				HKP_FUNCTION_ID_getSupportingVertex, \
																				HKP_FUNCTION_ID_getNumCollisionSpheres )

#define HKP_FUNCTION_SET_SIMULATION				HK_PREPROCESSOR_BITWISE_OR_4(	HKP_FUNCTION_SET_COLLIDE_QUERY, \
																				HKP_FUNCTION_ID_weldContactPoint, \
																				HKP_FUNCTION_ID_getCentre, \
																				HKP_FUNCTION_ID_getCollisionSpheres )

#define HKP_FUNCTION_SET_RAYCAST_QUERY			HK_PREPROCESSOR_BITWISE_OR_4(	HKP_FUNCTION_ID_getAabb, \
																				HKP_FUNCTION_ID_castRay, \
																				HKP_FUNCTION_ID_castRayBundle, \
																				HKP_FUNCTION_ID_castRayWithCollector )

#define HKP_FUNCTION_SET_RAYCAST_QUERY_2		HK_PREPROCESSOR_BITWISE_OR(		HKP_FUNCTION_SET_RAYCAST_QUERY, \
																				HKP_FUNCTION_ID_getSupportingVertex )

#define HKP_FUNCTION_SET_RAYCAST_QUERY_3		HK_PREPROCESSOR_BITWISE_OR(		HKP_FUNCTION_SET_RAYCAST_QUERY, \
																				HKP_FUNCTION_ID_getCollisionFilterInfo )

#define HKP_FUNCTION_SET_RAYCAST_QUERY_4		HK_PREPROCESSOR_BITWISE_OR(		HKP_FUNCTION_SET_RAYCAST_QUERY_3, \
																				HKP_FUNCTION_ID_getChildShape )


//
//	hkpShapeBase virtual function implementations that bypass the vtable
//

#define HKP_VIRTUAL_SHAPE_getSupportingVertex(Derived)\
	virtual void getSupportingVertex(hkVector4Parameter direction, hkcdVertex &supportVertex) const\
	{\
		reinterpret_cast<const Derived*>(this)->Derived::getSupportingVertex(direction, supportVertex);\
	}

#define HKP_VIRTUAL_SHAPE_convertVertexIdsToVertices(Derived)\
	virtual void convertVertexIdsToVertices(const hkpVertexId* ids, int numIds, hkcdVertex* vertexArrayOut) const\
	{\
		reinterpret_cast<const Derived*>(this)->Derived::convertVertexIdsToVertices(ids, numIds, vertexArrayOut);\
	}

#define HKP_VIRTUAL_SHAPE_weldContactPoint(Derived)\
	virtual int weldContactPoint(hkpVertexId* featurePoints, hkUint8& numFeaturePoints, hkVector4& contactPointWs, const hkTransform* thisObjTransform, const class hkpConvexShape* collidingConvexShape, const hkTransform* collidingTransform, hkVector4& separatingNormalInOut) const\
	{\
		return reinterpret_cast<const Derived*>(this)->Derived::weldContactPoint(featurePoints, numFeaturePoints, contactPointWs, thisObjTransform, collidingConvexShape, collidingTransform, separatingNormalInOut);\
	}

#define HKP_VIRTUAL_SHAPE_getCentre(Derived)\
	virtual void getCentre(hkVector4& centreOut) const\
	{\
		reinterpret_cast<const Derived*>(this)->Derived::getCentre(centreOut);\
	}

#define HKP_VIRTUAL_SHAPE_getNumCollisionSpheres(Derived)\
	virtual int getNumCollisionSpheres() const\
	{\
		return reinterpret_cast<const Derived*>(this)->Derived::getNumCollisionSpheres();\
	}

#define HKP_VIRTUAL_SHAPE_getCollisionSpheres(Derived)\
	virtual const hkSphere* getCollisionSpheres(hkSphere* sphereBuffer) const\
	{\
		return reinterpret_cast<const Derived*>(this)->Derived::getCollisionSpheres(sphereBuffer);\
	}

#define HKP_VIRTUAL_SHAPE_getAabb(Derived)\
	virtual void getAabb(const hkTransform& localToWorld, hkReal tolerance, hkAabb& out) const\
	{\
		reinterpret_cast<const Derived*>(this)->Derived::getAabb(localToWorld, tolerance, out);\
	}

#define HKP_VIRTUAL_SHAPE_castRay(Derived)\
	virtual hkBool castRay(const hkpShapeRayCastInput& input, hkpShapeRayCastOutput& output) const\
	{\
		return reinterpret_cast<const Derived*>(this)->Derived::castRay(input, output);\
	}

#define HKP_VIRTUAL_SHAPE_castRayWithCollector(Derived)\
	virtual void castRayWithCollector(const hkpShapeRayCastInput& input, const hkpCdBody& cdBody, hkpRayHitCollector& collector) const\
	{\
		return reinterpret_cast<const Derived*>(this)->Derived::castRayWithCollector(input, cdBody, collector);\
	}

#define HKP_VIRTUAL_SHAPE_castRayBundle(Derived)\
	virtual hkVector4Comparison castRayBundle(const hkpShapeRayBundleCastInput& input, hkpShapeRayBundleCastOutput& output,  hkVector4ComparisonParameter mask) const\
	{\
		return reinterpret_cast<const Derived*>(this)->Derived::castRayBundle(input, output, mask);\
	}

#	define HKP_VIRTUAL_SHAPE_getChildShape(Derived)

#	define HKP_VIRTUAL_SHAPE_getCollisionFilterInfo(Derived)


// On PPU we'll derive the partial classes from the Derived class, because they usually have extra virtual functions,
// and we need them to be valid as well. On SPU we'll derive from hkpShapeBase, as the implemented virtual functions should not
// call other virtual functions that are not in the hkpShapeBase.
#	define HKP_VIRTUAL_IMPLEMENT(Function)		HKP_VIRTUAL_SHAPE_##Function(DerivedShape)
#	define HKP_VIRTUAL_DUMMY(Function)			HKP_VIRTUAL_SHAPE_##Function(UnimplementedBaseShape)

// If the function is enabled in the function set, this will get a valid implementation, otherwise will default to the dummy one
#define EVAL_VIRTUAL_FUNCTION( Function, FunctionSet )\
	HK_PREPROCESSOR_IF(\
		HK_PREPROCESSOR_BITWISE_AND( FunctionSet, HKP_FUNCTION_ID_##Function ),\
		HKP_VIRTUAL_IMPLEMENT( Function ),\
		HKP_VIRTUAL_DUMMY( Function ) )

// Declares a partial class with a subset of implemented functions
#define HKP_DECLARE_PARTIAL_CLASS( FunctionSet )\
	template < class DerivedShape, class BaseShape, class UnimplementedBaseShape >\
	class PartialShape< DerivedShape, BaseShape, UnimplementedBaseShape, FunctionSet > : public BaseShape\
	{\
		public:\
		\
			EVAL_VIRTUAL_FUNCTION( getSupportingVertex,			FunctionSet );\
			EVAL_VIRTUAL_FUNCTION( convertVertexIdsToVertices,	FunctionSet );\
			EVAL_VIRTUAL_FUNCTION( weldContactPoint,			FunctionSet );\
			EVAL_VIRTUAL_FUNCTION( getCentre,					FunctionSet );\
			EVAL_VIRTUAL_FUNCTION( getNumCollisionSpheres,		FunctionSet );\
			EVAL_VIRTUAL_FUNCTION( getCollisionSpheres,			FunctionSet );\
			EVAL_VIRTUAL_FUNCTION( getAabb,						FunctionSet );\
			EVAL_VIRTUAL_FUNCTION( castRay,						FunctionSet );\
			EVAL_VIRTUAL_FUNCTION( castRayWithCollector,		FunctionSet );\
			EVAL_VIRTUAL_FUNCTION( castRayBundle,				FunctionSet );\
			EVAL_VIRTUAL_FUNCTION( getChildShape,				FunctionSet );\
			EVAL_VIRTUAL_FUNCTION( getCollisionFilterInfo,		FunctionSet );\
	}


// Declares a PartialShape for the given shape and function set
#define HKP_DECLARE_PARTIAL_SHAPE( ShapeClass, FunctionSet, PartialClass )\
	typedef DeclarePartialShape< ShapeClass, FunctionSet >::Type PartialClass;\
	enum { FUNCTION_SET_##ShapeClass = FunctionSet, }


// Declares a function to set the current profile.

#define HKP_DECLARE_SHAPE_VTABLE_SET_PROFILE( Profile ) \
	template <> void HK_CALL HK_INIT_FUNCTION2(hkpShapeVirtualTableUtil::setProfile<Profile>, hkpShapeVirtualTableUtil_setProfile)()\
	{\
		typedef hkpShapeVirtualTableInternals::PartialShapeSet< Profile > ShapeSet;\
		hkpShapeVirtualTableInternals::registerVirtualTables< ShapeSet >( hkcdShapeVirtualTableUtil::s_virtualTablePatches );\
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
