/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */


// Partial shape definition
namespace hkpShapeVirtualTableInternals
{
	// Base class for our partial shapes
	template < class DerivedShape, class BaseShape, class UnimplementedBaseShape, int FunctionSet >
	class PartialShape {};

	// Specializations
	HKP_DECLARE_PARTIAL_CLASS( HKP_FUNCTION_SET_AABB );
	HKP_DECLARE_PARTIAL_CLASS( HKP_FUNCTION_SET_AABB_CHILD_FILTER );
	HKP_DECLARE_PARTIAL_CLASS( HKP_FUNCTION_SET_SIMULATION );
	HKP_DECLARE_PARTIAL_CLASS( HKP_FUNCTION_SET_COLLIDE_QUERY );
	HKP_DECLARE_PARTIAL_CLASS( HKP_FUNCTION_SET_RAYCAST_QUERY );
	HKP_DECLARE_PARTIAL_CLASS( HKP_FUNCTION_SET_RAYCAST_QUERY_2 );
	HKP_DECLARE_PARTIAL_CLASS( HKP_FUNCTION_SET_RAYCAST_QUERY_3 );
	HKP_DECLARE_PARTIAL_CLASS( HKP_FUNCTION_SET_RAYCAST_QUERY_4 );

	// Declares a function set
	template < class ShapeClass, int FunctionSet >
	struct DeclarePartialShape
	{
		typedef hkpShapeVirtualTableInternals::PartialShape< ShapeClass, ShapeClass, hkpShapeBase, FunctionSet > Type;
	};

	// Specialization for unimplemented shapes
	template < class ShapeClass >
	struct DeclarePartialShape< ShapeClass, HKP_FUNCTION_SET_NONE >
	{
		typedef hkpShapeBase Type;
	};

	// Each ELF has its own PartialShapeSet
	template < hkpShapeVirtualTableUtil::Profile profile >
	struct PartialShapeSet {};
}


// ELF specific partial shape specializations
namespace hkpShapeVirtualTableInternals
{

	template <>
	struct PartialShapeSet< hkpShapeVirtualTableUtil::PROFILE_INTEGRATE >
	{
		HKP_DECLARE_PARTIAL_SHAPE( hkpSphereShape,						HKP_FUNCTION_SET_AABB,				hkpPartialSphereShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpCylinderShape,					HKP_FUNCTION_SET_AABB,				hkpPartialCylinderShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpTriangleShape,					HKP_FUNCTION_SET_AABB,				hkpPartialTriangleShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpBoxShape,							HKP_FUNCTION_SET_AABB,				hkpPartialBoxShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpCapsuleShape,						HKP_FUNCTION_SET_AABB,				hkpPartialCapsuleShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpConvexVerticesShape,				HKP_FUNCTION_SET_AABB,				hkpPartialConvexVerticesShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpTriSampledHeightFieldCollection,	HKP_FUNCTION_SET_NONE,				hkpPartialTriSampledHeightFieldCollection);
		HKP_DECLARE_PARTIAL_SHAPE( hkpTriSampledHeightFieldBvTreeShape,	HKP_FUNCTION_SET_NONE,				hkpPartialTriSampledHeightFieldBvTreeShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpListShape,						HKP_FUNCTION_SET_AABB,				hkpPartialListShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpMoppBvTreeShape,					HKP_FUNCTION_SET_AABB,				hkpPartialMoppBvTreeShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpConvexTranslateShape,				HKP_FUNCTION_SET_AABB,				hkpPartialConvexTranslateShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpConvexTransformShape,				HKP_FUNCTION_SET_AABB,				hkpPartialConvexTransformShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpSampledHeightFieldShape,			HKP_FUNCTION_SET_AABB,				hkpPartialSampledHeightFieldShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpExtendedMeshShape,				HKP_FUNCTION_SET_AABB_CHILD_FILTER,	hkpPartialExtendedMeshShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpCompressedMeshShape,				HKP_FUNCTION_SET_AABB_CHILD_FILTER,	hkpPartialCompressedMeshShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpTransformShape,					HKP_FUNCTION_SET_AABB,				hkpPartialTransformShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpStaticCompoundShape,				HKP_FUNCTION_SET_AABB_CHILD_FILTER,	hkpPartialStaticCompoundShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpBvCompressedMeshShape,			HKP_FUNCTION_SET_AABB_CHILD_FILTER,	hkpPartialBvCompressedMeshShape );
	};


	template <>
	struct PartialShapeSet< hkpShapeVirtualTableUtil::PROFILE_COLLIDE >
	{
		HKP_DECLARE_PARTIAL_SHAPE( hkpSphereShape,						HKP_FUNCTION_SET_SIMULATION,		hkpPartialSphereShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpCylinderShape,					HKP_FUNCTION_SET_SIMULATION,		hkpPartialCylinderShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpTriangleShape,					HKP_FUNCTION_SET_SIMULATION,		hkpPartialTriangleShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpBoxShape,							HKP_FUNCTION_SET_SIMULATION,		hkpPartialBoxShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpCapsuleShape,						HKP_FUNCTION_SET_SIMULATION,		hkpPartialCapsuleShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpConvexVerticesShape,				HKP_FUNCTION_SET_SIMULATION,		hkpPartialConvexVerticesShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpTriSampledHeightFieldCollection,	HKP_FUNCTION_SET_AABB_CHILD_FILTER,	hkpPartialTriSampledHeightFieldCollection);
		HKP_DECLARE_PARTIAL_SHAPE( hkpTriSampledHeightFieldBvTreeShape,	HKP_FUNCTION_SET_AABB,				hkpPartialTriSampledHeightFieldBvTreeShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpListShape,						HKP_FUNCTION_SET_AABB_CHILD_FILTER,	hkpPartialListShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpMoppBvTreeShape,					HKP_FUNCTION_SET_AABB,				hkpPartialMoppBvTreeShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpConvexTranslateShape,				HKP_FUNCTION_SET_SIMULATION,		hkpPartialConvexTranslateShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpConvexTransformShape,				HKP_FUNCTION_SET_SIMULATION,		hkpPartialConvexTransformShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpSampledHeightFieldShape,			HKP_FUNCTION_SET_AABB,				hkpPartialSampledHeightFieldShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpExtendedMeshShape,				HKP_FUNCTION_SET_AABB_CHILD_FILTER,	hkpPartialExtendedMeshShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpCompressedMeshShape,				HKP_FUNCTION_SET_AABB_CHILD_FILTER,	hkpPartialCompressedMeshShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpTransformShape,					HKP_FUNCTION_SET_AABB,				hkpPartialTransformShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpStaticCompoundShape,				HKP_FUNCTION_SET_NONE,				hkpPartialStaticCompoundShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpBvCompressedMeshShape,			HKP_FUNCTION_SET_NONE,				hkpPartialBvCompressedMeshShape );
	};


	template <>
	struct PartialShapeSet< hkpShapeVirtualTableUtil::PROFILE_COLLIDE_STATIC_COMPOUND >
	{
		HKP_DECLARE_PARTIAL_SHAPE( hkpSphereShape,						HKP_FUNCTION_SET_SIMULATION,		hkpPartialSphereShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpCylinderShape,					HKP_FUNCTION_SET_SIMULATION,		hkpPartialCylinderShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpTriangleShape,					HKP_FUNCTION_SET_SIMULATION,		hkpPartialTriangleShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpBoxShape,							HKP_FUNCTION_SET_SIMULATION,		hkpPartialBoxShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpCapsuleShape,						HKP_FUNCTION_SET_SIMULATION,		hkpPartialCapsuleShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpConvexVerticesShape,				HKP_FUNCTION_SET_SIMULATION,		hkpPartialConvexVerticesShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpTriSampledHeightFieldCollection,	HKP_FUNCTION_SET_AABB_CHILD_FILTER,	hkpPartialTriSampledHeightFieldCollection);
		HKP_DECLARE_PARTIAL_SHAPE( hkpTriSampledHeightFieldBvTreeShape,	HKP_FUNCTION_SET_AABB,				hkpPartialTriSampledHeightFieldBvTreeShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpListShape,						HKP_FUNCTION_SET_AABB_CHILD_FILTER,	hkpPartialListShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpMoppBvTreeShape,					HKP_FUNCTION_SET_AABB,				hkpPartialMoppBvTreeShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpConvexTranslateShape,				HKP_FUNCTION_SET_SIMULATION,		hkpPartialConvexTranslateShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpConvexTransformShape,				HKP_FUNCTION_SET_SIMULATION,		hkpPartialConvexTransformShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpSampledHeightFieldShape,			HKP_FUNCTION_SET_AABB,				hkpPartialSampledHeightFieldShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpExtendedMeshShape,				HKP_FUNCTION_SET_NONE,				hkpPartialExtendedMeshShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpCompressedMeshShape,				HKP_FUNCTION_SET_NONE,				hkpPartialCompressedMeshShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpTransformShape,					HKP_FUNCTION_SET_AABB,				hkpPartialTransformShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpStaticCompoundShape,				HKP_FUNCTION_SET_AABB_CHILD_FILTER,	hkpPartialStaticCompoundShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpBvCompressedMeshShape,			HKP_FUNCTION_SET_AABB_CHILD_FILTER,	hkpPartialBvCompressedMeshShape );
	};


	template <>
	struct PartialShapeSet< hkpShapeVirtualTableUtil::PROFILE_COLLISION_QUERY >
	{
		HKP_DECLARE_PARTIAL_SHAPE( hkpSphereShape,						HKP_FUNCTION_SET_COLLIDE_QUERY,		hkpPartialSphereShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpCylinderShape,					HKP_FUNCTION_SET_COLLIDE_QUERY,		hkpPartialCylinderShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpTriangleShape,					HKP_FUNCTION_SET_COLLIDE_QUERY,		hkpPartialTriangleShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpBoxShape,							HKP_FUNCTION_SET_COLLIDE_QUERY,		hkpPartialBoxShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpCapsuleShape,						HKP_FUNCTION_SET_COLLIDE_QUERY,		hkpPartialCapsuleShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpConvexVerticesShape,				HKP_FUNCTION_SET_COLLIDE_QUERY,		hkpPartialConvexVerticesShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpTriSampledHeightFieldCollection,	HKP_FUNCTION_SET_AABB_CHILD_FILTER,	hkpPartialTriSampledHeightFieldCollection);
		HKP_DECLARE_PARTIAL_SHAPE( hkpTriSampledHeightFieldBvTreeShape,	HKP_FUNCTION_SET_AABB,				hkpPartialTriSampledHeightFieldBvTreeShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpListShape,						HKP_FUNCTION_SET_AABB_CHILD_FILTER,	hkpPartialListShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpMoppBvTreeShape,					HKP_FUNCTION_SET_AABB,				hkpPartialMoppBvTreeShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpConvexTranslateShape,				HKP_FUNCTION_SET_COLLIDE_QUERY,		hkpPartialConvexTranslateShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpConvexTransformShape,				HKP_FUNCTION_SET_COLLIDE_QUERY,		hkpPartialConvexTransformShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpSampledHeightFieldShape,			HKP_FUNCTION_SET_AABB,				hkpPartialSampledHeightFieldShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpExtendedMeshShape,				HKP_FUNCTION_SET_AABB_CHILD_FILTER,	hkpPartialExtendedMeshShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpCompressedMeshShape,				HKP_FUNCTION_SET_AABB_CHILD_FILTER,	hkpPartialCompressedMeshShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpTransformShape,					HKP_FUNCTION_SET_AABB,				hkpPartialTransformShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpStaticCompoundShape,				HKP_FUNCTION_SET_AABB_CHILD_FILTER,	hkpPartialStaticCompoundShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpBvCompressedMeshShape,			HKP_FUNCTION_SET_AABB_CHILD_FILTER,	hkpPartialBvCompressedMeshShape );
	};


	template <>
	struct PartialShapeSet< hkpShapeVirtualTableUtil::PROFILE_RAYCAST_QUERY >
	{
		HKP_DECLARE_PARTIAL_SHAPE( hkpSphereShape,						HKP_FUNCTION_SET_RAYCAST_QUERY,		hkpPartialSphereShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpCylinderShape,					HKP_FUNCTION_SET_RAYCAST_QUERY,		hkpPartialCylinderShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpTriangleShape,					HKP_FUNCTION_SET_RAYCAST_QUERY,		hkpPartialTriangleShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpBoxShape,							HKP_FUNCTION_SET_RAYCAST_QUERY,		hkpPartialBoxShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpCapsuleShape,						HKP_FUNCTION_SET_RAYCAST_QUERY,		hkpPartialCapsuleShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpConvexVerticesShape,				HKP_FUNCTION_SET_RAYCAST_QUERY_2,	hkpPartialConvexVerticesShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpTriSampledHeightFieldCollection,	HKP_FUNCTION_SET_AABB_CHILD_FILTER,	hkpPartialTriSampledHeightFieldCollection);
		HKP_DECLARE_PARTIAL_SHAPE( hkpTriSampledHeightFieldBvTreeShape,	HKP_FUNCTION_SET_RAYCAST_QUERY,		hkpPartialTriSampledHeightFieldBvTreeShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpListShape,						HKP_FUNCTION_SET_RAYCAST_QUERY_4,	hkpPartialListShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpMoppBvTreeShape,					HKP_FUNCTION_SET_RAYCAST_QUERY,		hkpPartialMoppBvTreeShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpConvexTranslateShape,				HKP_FUNCTION_SET_RAYCAST_QUERY,		hkpPartialConvexTranslateShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpConvexTransformShape,				HKP_FUNCTION_SET_RAYCAST_QUERY,		hkpPartialConvexTransformShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpSampledHeightFieldShape,			HKP_FUNCTION_SET_RAYCAST_QUERY,		hkpPartialSampledHeightFieldShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpExtendedMeshShape,				HKP_FUNCTION_SET_AABB_CHILD_FILTER,	hkpPartialExtendedMeshShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpCompressedMeshShape,				HKP_FUNCTION_SET_AABB_CHILD_FILTER,	hkpPartialCompressedMeshShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpTransformShape,					HKP_FUNCTION_SET_RAYCAST_QUERY,		hkpPartialTransformShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpStaticCompoundShape,				HKP_FUNCTION_SET_RAYCAST_QUERY_3,	hkpPartialStaticCompoundShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpBvCompressedMeshShape,			HKP_FUNCTION_SET_RAYCAST_QUERY_4,	hkpPartialBvCompressedMeshShape );
	};


	template <>
	struct PartialShapeSet< hkpShapeVirtualTableUtil::PROFILE_CHARACTER_PROXY >
	{
		HKP_DECLARE_PARTIAL_SHAPE( hkpSphereShape,						HKP_FUNCTION_SET_COLLIDE_QUERY,		hkpPartialSphereShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpCylinderShape,					HKP_FUNCTION_SET_COLLIDE_QUERY,		hkpPartialCylinderShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpTriangleShape,					HKP_FUNCTION_SET_COLLIDE_QUERY,		hkpPartialTriangleShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpBoxShape,							HKP_FUNCTION_SET_COLLIDE_QUERY,		hkpPartialBoxShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpCapsuleShape,						HKP_FUNCTION_SET_COLLIDE_QUERY,		hkpPartialCapsuleShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpConvexVerticesShape,				HKP_FUNCTION_SET_COLLIDE_QUERY,		hkpPartialConvexVerticesShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpTriSampledHeightFieldCollection,	HKP_FUNCTION_SET_NONE,				hkpPartialTriSampledHeightFieldCollection);
		HKP_DECLARE_PARTIAL_SHAPE( hkpTriSampledHeightFieldBvTreeShape,	HKP_FUNCTION_SET_NONE,				hkpPartialTriSampledHeightFieldBvTreeShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpListShape,						HKP_FUNCTION_SET_AABB_CHILD_FILTER,	hkpPartialListShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpMoppBvTreeShape,					HKP_FUNCTION_SET_AABB,				hkpPartialMoppBvTreeShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpConvexTranslateShape,				HKP_FUNCTION_SET_COLLIDE_QUERY,		hkpPartialConvexTranslateShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpConvexTransformShape,				HKP_FUNCTION_SET_COLLIDE_QUERY,		hkpPartialConvexTransformShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpSampledHeightFieldShape,			HKP_FUNCTION_SET_AABB,				hkpPartialSampledHeightFieldShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpExtendedMeshShape,				HKP_FUNCTION_SET_AABB_CHILD_FILTER,	hkpPartialExtendedMeshShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpCompressedMeshShape,				HKP_FUNCTION_SET_AABB_CHILD_FILTER,	hkpPartialCompressedMeshShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpTransformShape,					HKP_FUNCTION_SET_AABB,				hkpPartialTransformShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpStaticCompoundShape,				HKP_FUNCTION_SET_AABB_CHILD_FILTER,	hkpPartialStaticCompoundShape );
		HKP_DECLARE_PARTIAL_SHAPE( hkpBvCompressedMeshShape,			HKP_FUNCTION_SET_AABB_CHILD_FILTER,	hkpPartialBvCompressedMeshShape );
	};


	// Register the vtables for a set of partial shape implementations
	template <class ShapeSet>
	static HK_FORCE_INLINE void HK_CALL registerVirtualTables( hkUlong* vTablesOut )
	{
		typedef typename ShapeSet::hkpPartialSphereShape						PsSphere;
		typedef typename ShapeSet::hkpPartialCylinderShape						PsCylinder;
		typedef typename ShapeSet::hkpPartialTriangleShape						PsTriangle;
		typedef typename ShapeSet::hkpPartialBoxShape							PsBox;
		typedef typename ShapeSet::hkpPartialCapsuleShape						PsCapsule;
		typedef typename ShapeSet::hkpPartialConvexVerticesShape				PsConvexVertices;
		typedef typename ShapeSet::hkpPartialTriSampledHeightFieldCollection	PsTriSampledHfCol;
		typedef typename ShapeSet::hkpPartialTriSampledHeightFieldBvTreeShape	PsTriSampledHfTree;
		typedef typename ShapeSet::hkpPartialListShape							PsList;
		typedef typename ShapeSet::hkpPartialMoppBvTreeShape					PsMopp;
		typedef typename ShapeSet::hkpPartialConvexTranslateShape				PsCvxTranslate;
		typedef typename ShapeSet::hkpPartialConvexTransformShape				PsCvxTransform;
		typedef typename ShapeSet::hkpPartialSampledHeightFieldShape			PsSampledHf;
		typedef typename ShapeSet::hkpPartialExtendedMeshShape					PsEms;
		typedef typename ShapeSet::hkpPartialTransformShape						PsTransform;
		typedef typename ShapeSet::hkpPartialCompressedMeshShape				PsCms;
		typedef typename ShapeSet::hkpPartialStaticCompoundShape				PsScs;
		typedef typename ShapeSet::hkpPartialBvCompressedMeshShape				PsBvCms;

		// Create an instance each partial shape and copy its vtable pointer
		// (which appears at the start of its memory)
		hkpShapeBuffer buffer;
		hkUlong& vTablePtr = reinterpret_cast<hkUlong*>(buffer)[0];

		new (buffer) PsSphere;				vTablesOut[hkcdShapeType::SPHERE]								= vTablePtr;
		new (buffer) PsCylinder;			vTablesOut[hkcdShapeType::CYLINDER]								= vTablePtr;
		new (buffer) PsTriangle;			vTablesOut[hkcdShapeType::TRIANGLE]								= vTablePtr;
		new (buffer) PsBox;					vTablesOut[hkcdShapeType::BOX]									= vTablePtr;
		new (buffer) PsCapsule;				vTablesOut[hkcdShapeType::CAPSULE]								= vTablePtr;
		new (buffer) PsConvexVertices;		vTablesOut[hkcdShapeType::CONVEX_VERTICES]						= vTablePtr;
		new (buffer) PsTriSampledHfCol;		vTablesOut[hkcdShapeType::TRI_SAMPLED_HEIGHT_FIELD_COLLECTION]	= vTablePtr;
		new (buffer) PsTriSampledHfTree;	vTablesOut[hkcdShapeType::TRI_SAMPLED_HEIGHT_FIELD_BV_TREE]		= vTablePtr;
		new (buffer) PsList;				vTablesOut[hkcdShapeType::LIST]									= vTablePtr;
		new (buffer) PsMopp;				vTablesOut[hkcdShapeType::MOPP]									= vTablePtr;
		new (buffer) PsCvxTranslate;		vTablesOut[hkcdShapeType::CONVEX_TRANSLATE]						= vTablePtr;
		new (buffer) PsCvxTransform;		vTablesOut[hkcdShapeType::CONVEX_TRANSFORM]						= vTablePtr;
		new (buffer) PsSampledHf;			vTablesOut[hkcdShapeType::SAMPLED_HEIGHT_FIELD]					= vTablePtr;
		new (buffer) PsEms;					vTablesOut[hkcdShapeType::EXTENDED_MESH]						= vTablePtr;
		new (buffer) PsTransform;			vTablesOut[hkcdShapeType::TRANSFORM]							= vTablePtr;
		new (buffer) PsCms;					vTablesOut[hkcdShapeType::COMPRESSED_MESH]						= vTablePtr;
		new (buffer) PsScs;					vTablesOut[hkcdShapeType::STATIC_COMPOUND]						= vTablePtr;
		new (buffer) PsBvCms;				vTablesOut[hkcdShapeType::BV_COMPRESSED_MESH]					= vTablePtr;

		// User shapes: Add your partial shape implementations here
		/*
		new (buffer) ShapeSet::PartialUser0Shape;	vTablesOut[hkcdShapeType::USER0]						= vTablePtr;
		new (buffer) ShapeSet::PartialUser1Shape;	vTablesOut[hkcdShapeType::USER1]						= vTablePtr;
		new (buffer) ShapeSet::PartialUser2Shape;	vTablesOut[hkcdShapeType::USER2]						= vTablePtr;
		*/
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
