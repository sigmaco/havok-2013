/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#include <Common/Base/Types/Geometry/hkGeometry.h>


// Self-test name-space
namespace hkpShapeVirtualTableSelfTest
{
	//
	//	Attempts to run all virtual functions on the given shape

	static hkUlong HK_CALL runAllFunctions(const hkpShapeBase* shape, int fset)
	{
		hkVector4 v;
		v.set(1.0f, 0.0f, 0.0f);
		hkcdVertex supportVtx;
		hkpVertexId vid = 0;

		// Clear unimplemented functions flag
		hkcdShapeVirtualTableUtil::s_unregisteredFunctions = 0;

		shape->getSupportingVertex(v, supportVtx);
		shape->convertVertexIdsToVertices(&vid, 1, &supportVtx);

		{
			hkpVertexId featureIds[] = {0, 1, 2};
			hkUint8 numFeatures = 1;
			hkTransform id;	id.setIdentity();
			hkVector4 vN;
			hkVector4 vP;	vP.setZero();
			hkpSphereShape ssh(10.0f);
			shape->weldContactPoint((hkpVertexId*)featureIds, numFeatures, vP, &id, &ssh, &id, vN);
		}

		shape->getCentre(v);

		const int numSpheres = shape->getNumCollisionSpheres();
		hkArray<hkSphere> sphereBuf;
		sphereBuf.setSize(numSpheres);
		const hkSphere* s = shape->getCollisionSpheres(sphereBuf.begin());

		hkTransform id;
		id.setIdentity();
		hkAabb aabb;
		shape->getAabb(id, 0.0f, aabb);


		hkpShapeRayCastInput rayIn;
		rayIn.m_from.setZero();
		rayIn.m_to.setZero();
		rayIn.m_rayShapeCollectionFilter = HK_NULL;

		{
			hkpShapeRayCastOutput rayOut;
			shape->castRay(rayIn, rayOut);
		}

		{
			hkpCdBody body(reinterpret_cast<const hkpShape*>(shape), &id);

			hkpAllRayHitCollector col;
			shape->castRayWithCollector(rayIn, body, col);
		}

		{
			hkpShapeRayBundleCastInput rayBundleIn;
			hkVector4 vZero;	vZero.setZero();
			rayBundleIn.m_from.setAll(vZero);
			rayBundleIn.m_to.setAll(vZero);
			rayBundleIn.m_rayShapeCollectionFilter	= HK_NULL;

			hkpShapeRayBundleCastOutput rayOut;
			hkVector4Comparison cmp;	cmp.set<hkVector4ComparisonMask::MASK_XYZW>();
			shape->castRayBundle(rayBundleIn, rayOut, cmp);
		}


		// The un-implemented functions must match the profile
		const hkUint32 unwantedFunctions = (~fset) & HKP_FUNCTION_ID_MASK;
		HK_ASSERT(0x3571a8f2, hkcdShapeVirtualTableUtil::s_unregisteredFunctions == unwantedFunctions);

		return (hkUlong)s
			;
	}

	//
	//	Self tests - hkpSphereShape

	template <hkpShapeVirtualTableUtil::Profile profileType>
	static void HK_CALL test_hkpSphereShape()
	{
		typedef hkpShapeVirtualTableInternals::PartialShapeSet<profileType>	ShapeSet;

		hkpSphereShape sphereShape(10.0f);
		hkpShapeVirtualTableUtil::patchVirtualTable(&sphereShape);
		runAllFunctions(&sphereShape, ShapeSet::FUNCTION_SET_hkpSphereShape);
	}

	//
	//	Self tests - hkpCylinderShape

	template <hkpShapeVirtualTableUtil::Profile profileType>
	static void HK_CALL test_hkpCylinderShape()
	{
		typedef hkpShapeVirtualTableInternals::PartialShapeSet<profileType>	ShapeSet;

		hkVector4 vA;	vA.setZero();
		hkVector4 vB;	vB.set(10.0f, 0.0f, 0.0f);
		hkpCylinderShape cylinderShape(vA, vB, 10.0f, 2.0f);
		hkpShapeVirtualTableUtil::patchVirtualTable(&cylinderShape);
		runAllFunctions(&cylinderShape, ShapeSet::FUNCTION_SET_hkpCylinderShape);
	}

	//
	//	Self tests - hkpTriangleShape

	template <hkpShapeVirtualTableUtil::Profile profileType>
	static void HK_CALL test_hkpTriangleShape()
	{
		typedef hkpShapeVirtualTableInternals::PartialShapeSet<profileType>	ShapeSet;

		hkVector4 vA;	vA.setZero();
		hkVector4 vB;	vB.set(10.0f, 0.0f, 0.0f);
		hkVector4 vC;	vC.set(0.0f, 10.0f, 0.0f);
		hkpTriangleShape triShape;
		triShape.setVertex(0, vA);
		triShape.setVertex(1, vB);
		triShape.setVertex(2, vC);
		hkpShapeVirtualTableUtil::patchVirtualTable(&triShape);
		runAllFunctions(&triShape, ShapeSet::FUNCTION_SET_hkpTriangleShape);
	}

	//
	//	Self tests - hkpBoxShape

	template <hkpShapeVirtualTableUtil::Profile profileType>
	static void HK_CALL test_hkpBoxShape()
	{
		typedef hkpShapeVirtualTableInternals::PartialShapeSet<profileType>	ShapeSet;

		hkVector4 halfExtents;
		halfExtents.set(10.0f, 20.0f, 30.0f);
		hkpBoxShape boxShape(halfExtents);
		hkpShapeVirtualTableUtil::patchVirtualTable(&boxShape);
		runAllFunctions(&boxShape, ShapeSet::FUNCTION_SET_hkpBoxShape);
	}

	//
	//	Self tests - hkpCapsuleShape

	template <hkpShapeVirtualTableUtil::Profile profileType>
	static void HK_CALL test_hkpCapsuleShape()
	{
		typedef hkpShapeVirtualTableInternals::PartialShapeSet<profileType>	ShapeSet;

		hkVector4 vA;	vA.setZero();
		hkVector4 vB;	vB.set(10.0f, 0.0f, 0.0f);
		hkpCapsuleShape capsuleShape(vA, vB, 10.0f);
		hkpShapeVirtualTableUtil::patchVirtualTable(&capsuleShape);
		runAllFunctions(&capsuleShape, ShapeSet::FUNCTION_SET_hkpCapsuleShape);
	}

	//
	//	Self tests - hkpConvexVerticesShape

	template <hkpShapeVirtualTableUtil::Profile profileType>
	static void HK_CALL test_hkpConvexVerticesShape()
	{
		typedef hkpShapeVirtualTableInternals::PartialShapeSet<profileType>	ShapeSet;

		hkVector4 verts[4];
		verts[0].set(0.0f, 0.0f, 0.0f);
		verts[1].set(10.0f, 0.0f, 0.0f);
		verts[2].set(0.0f, 10.0f, 0.0f);
		verts[3].set(0.0f, 0.0f, 10.0f);

		hkStridedVertices sv(verts, 4);
		hkpConvexVerticesShape cxv(sv);
		hkpShapeVirtualTableUtil::patchVirtualTable(&cxv);
		runAllFunctions(&cxv, ShapeSet::FUNCTION_SET_hkpConvexVerticesShape);
	}

	//
	//	Self tests - hkpTriSampledHeightFieldCollection

	template <hkpShapeVirtualTableUtil::Profile profileType>
	static void HK_CALL test_hkpTriSampledHeightFieldCollection()
	{
		typedef hkpShapeVirtualTableInternals::PartialShapeSet<profileType>	ShapeSet;

		hkpSampledHeightFieldBaseCinfo hfInfo;
		hkArray<hkReal> heights;
		for (int k = 0; k < 8; k++)
		{
			heights.pushBack(0.0f);
		}
		hkpStorageSampledHeightFieldShape hf(hfInfo, heights);
		hkpTriSampledHeightFieldCollection hfCol(&hf);

		hkpShapeVirtualTableUtil::patchVirtualTable(&hfCol);
		runAllFunctions(&hfCol, ShapeSet::FUNCTION_SET_hkpTriSampledHeightFieldCollection);
	}

	//
	//	Self tests - hkpTriSampledHeightFieldBvTreeShape

	template <hkpShapeVirtualTableUtil::Profile profileType>
	static void HK_CALL test_hkpTriSampledHeightFieldBvTreeShape()
	{
		typedef hkpShapeVirtualTableInternals::PartialShapeSet<profileType>	ShapeSet;

		hkpSampledHeightFieldBaseCinfo hfInfo;
		hkArray<hkReal> heights;
		for (int k = 0; k < 8; k++)
		{
			heights.pushBack(0.0f);
		}
		hkpStorageSampledHeightFieldShape hf(hfInfo, heights);
		hkpTriSampledHeightFieldCollection hfCol(&hf);
		hkpTriSampledHeightFieldBvTreeShape hfTree(&hfCol);

		hkpShapeVirtualTableUtil::patchVirtualTable(&hfTree);
		runAllFunctions(&hfTree, ShapeSet::FUNCTION_SET_hkpTriSampledHeightFieldBvTreeShape);
	}

	//
	//	Self tests - hkpListShape

	template <hkpShapeVirtualTableUtil::Profile profileType>
	static void HK_CALL test_hkpListShape()
	{
		typedef hkpShapeVirtualTableInternals::PartialShapeSet<profileType>	ShapeSet;

		hkpSphereShape ss(10.0f);
		const hkpShape* sa = &ss;
		hkpListShape ls(&sa, 1);

		hkpShapeVirtualTableUtil::patchVirtualTable(&ls);
		runAllFunctions(&ls, ShapeSet::FUNCTION_SET_hkpListShape);
	}

	//
	//	Self tests - hkpMoppBvTreeShape

	template <hkpShapeVirtualTableUtil::Profile profileType>
	static void HK_CALL test_hkpMoppBvTreeShape()
	{
		typedef hkpShapeVirtualTableInternals::PartialShapeSet<profileType>	ShapeSet;

		hkpSphereShape ss(10.0f);
		const hkpShape* sa = &ss;
		hkpListShape ls(&sa, 1);
		hkpMoppCompilerInput cinput;
		hkpMoppCode* code = hkpMoppUtility::buildCode(&ls, cinput);
		hkpMoppBvTreeShape mopp = hkpMoppBvTreeShape(&ls, code);
		code->removeReference();

		hkpShapeVirtualTableUtil::patchVirtualTable(&mopp);
		runAllFunctions(&mopp, ShapeSet::FUNCTION_SET_hkpMoppBvTreeShape);
	}

	//
	//	Self tests - hkpConvexTranslateShape

	template <hkpShapeVirtualTableUtil::Profile profileType>
	static void HK_CALL test_hkpConvexTranslateShape()
	{
		typedef hkpShapeVirtualTableInternals::PartialShapeSet<profileType>	ShapeSet;

		hkpSphereShape ssh(10.0f);
		hkVector4 vZero;	vZero.setZero();
		hkpConvexTranslateShape cxt(&ssh, vZero);
		hkpShapeVirtualTableUtil::patchVirtualTable(&cxt);
		runAllFunctions(&cxt, ShapeSet::FUNCTION_SET_hkpConvexTranslateShape);
	}

	//
	//	Self tests - hkpConvexTransformShape

	template <hkpShapeVirtualTableUtil::Profile profileType>
	static void HK_CALL test_hkpConvexTransformShape()
	{
		typedef hkpShapeVirtualTableInternals::PartialShapeSet<profileType>	ShapeSet;

		hkpSphereShape ssh(10.0f);
		hkTransform tm; tm.setIdentity();
		hkpConvexTransformShape cxt(&ssh, tm);
		hkpShapeVirtualTableUtil::patchVirtualTable(&cxt);
		runAllFunctions(&cxt, ShapeSet::FUNCTION_SET_hkpConvexTransformShape);
	}

	//
	//	Self tests - hkpSampledHeightFieldShape

	template <hkpShapeVirtualTableUtil::Profile profileType>
	static void HK_CALL test_hkpSampledHeightFieldShape()
	{
		typedef hkpShapeVirtualTableInternals::PartialShapeSet<profileType>	ShapeSet;

		hkpSampledHeightFieldBaseCinfo hfInfo;
		hkArray<hkReal> heights;
		for (int k = 0; k < 8; k++)
		{
			heights.pushBack(0.0f);
		}
		hkpStorageSampledHeightFieldShape hf(hfInfo, heights);

		hkpShapeVirtualTableUtil::patchVirtualTable(&hf);
		runAllFunctions(&hf, ShapeSet::FUNCTION_SET_hkpSampledHeightFieldShape);
	}

	//
	//	Self tests - hkpExtendedMeshShape

	template <hkpShapeVirtualTableUtil::Profile profileType>
	static void HK_CALL test_hkpExtendedMeshShape()
	{
		typedef hkpShapeVirtualTableInternals::PartialShapeSet<profileType>	ShapeSet;

		HK_ALIGN16(hkUint16) tris[] = {0, 1, 2};
		HK_ALIGN_REAL(hkReal) verts[] = {0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f};
		hkpExtendedMeshShape ems;
		hkpExtendedMeshShape::TrianglesSubpart tri;
		tri.m_numTriangleShapes = 1;
		tri.m_vertexBase		= verts;
		tri.m_vertexStriding	= sizeof(hkReal) * 3;
		tri.m_numVertices		= 3;
		tri.m_stridingType		= hkpExtendedMeshShape::INDICES_INT16;
		tri.m_indexBase			= tris;
		tri.m_indexStriding		= sizeof(hkUint16);
		ems.addTrianglesSubpart(tri);
		hkpShapeVirtualTableUtil::patchVirtualTable(&ems);
		runAllFunctions(&ems, ShapeSet::FUNCTION_SET_hkpExtendedMeshShape);
	}

	//
	//	Self tests - hkpTransformShape

	template <hkpShapeVirtualTableUtil::Profile profileType>
	static void HK_CALL test_hkpTransformShape()
	{
		typedef hkpShapeVirtualTableInternals::PartialShapeSet<profileType>	ShapeSet;

		hkpSphereShape ssh(10.0f);
		hkTransform tm;	tm.setIdentity();
		hkpTransformShape ts(&ssh, tm);

		hkpShapeVirtualTableUtil::patchVirtualTable(&ts);
		runAllFunctions(&ts, ShapeSet::FUNCTION_SET_hkpTransformShape);
	}

	//
	//	Self tests - hkpCompressedMeshShape

	template <hkpShapeVirtualTableUtil::Profile profileType>
	static void HK_CALL test_hkpCompressedMeshShape()
	{
		typedef hkpShapeVirtualTableInternals::PartialShapeSet<profileType>	ShapeSet;

		hkpCompressedMeshShape cms;
		cms.m_bigTriangles.setSize(1);
		hkpCompressedMeshShape::BigTriangle& tri = cms.m_bigTriangles[0];
		tri.m_a = 0;
		tri.m_b = 1;
		tri.m_c = 2;
		tri.m_transformIndex = 0;
		cms.m_bigVertices.setSize(3);
		cms.m_bigVertices[0].set(0.0f, 0.0f, 0.0f);
		cms.m_bigVertices[1].set(0.0f, 10.0f, 0.0f);
		cms.m_bigVertices[2].set(0.0f, 0.0f, 10.0f);
		cms.m_transforms.pushBack(hkQsTransform::getIdentity());

		hkpShapeVirtualTableUtil::patchVirtualTable(&cms);
		runAllFunctions(&cms, ShapeSet::FUNCTION_SET_hkpCompressedMeshShape);
	}

	//
	//	Self tests - hkpStaticCompoundShape

	template <hkpShapeVirtualTableUtil::Profile profileType>
	static void HK_CALL test_hkpStaticCompoundShape()
	{
		typedef hkpShapeVirtualTableInternals::PartialShapeSet<profileType>	ShapeSet;
		hkpStaticCompoundShape scs;

		hkpSphereShape ssh(10.0f);
		hkQsTransform tm;	tm.setIdentity();
		scs.addInstance(&ssh, tm);
		scs.bake();

		hkpShapeVirtualTableUtil::patchVirtualTable(&scs);
		runAllFunctions(&scs, ShapeSet::FUNCTION_SET_hkpStaticCompoundShape);
	}

	//
	//	Self tests - hkpBvCompressedMeshShape

	template <hkpShapeVirtualTableUtil::Profile profileType>
	static void HK_CALL test_hkpBvCompressedMeshShape()
	{
		typedef hkpShapeVirtualTableInternals::PartialShapeSet<profileType>	ShapeSet;
		
		hkGeometry geom;
		geom.m_vertices.setSize(3);
		geom.m_vertices[0].set(0.0f, 0.0f, 0.0f);
		geom.m_vertices[1].set(0.0f, 10.0f, 0.0f);
		geom.m_vertices[2].set(0.0f, 0.0f, 10.0f);
		geom.m_triangles.setSize(1);
		geom.m_triangles[0].set(0, 1, 2);
		hkpDefaultBvCompressedMeshShapeCinfo cinfo(&geom);
		hkpBvCompressedMeshShape bvcms(cinfo);

		hkpShapeVirtualTableUtil::patchVirtualTable(&bvcms);
		runAllFunctions(&bvcms, ShapeSet::FUNCTION_SET_hkpBvCompressedMeshShape);
	}

	//
	//	Tests the current profile

	template <hkpShapeVirtualTableUtil::Profile profileType>
	static void HK_CALL testCurrentProfile()
	{
		test_hkpSphereShape						<profileType>();
		test_hkpCylinderShape					<profileType>();
		test_hkpTriangleShape					<profileType>();
		test_hkpBoxShape						<profileType>();
		test_hkpCapsuleShape					<profileType>();
		test_hkpConvexVerticesShape				<profileType>();
		test_hkpTriSampledHeightFieldCollection	<profileType>();
		test_hkpTriSampledHeightFieldBvTreeShape<profileType>();
		test_hkpListShape						<profileType>();
		test_hkpMoppBvTreeShape					<profileType>();
		test_hkpConvexTranslateShape			<profileType>();
		test_hkpConvexTransformShape			<profileType>();
		test_hkpSampledHeightFieldShape			<profileType>();
		test_hkpExtendedMeshShape				<profileType>();
		test_hkpTransformShape					<profileType>();
		test_hkpCompressedMeshShape				<profileType>();
		test_hkpStaticCompoundShape				<profileType>();
		test_hkpBvCompressedMeshShape			<profileType>();
	}

	//
	//	Tests the given profile

	template <hkpShapeVirtualTableUtil::Profile profileType>
	static HK_FORCE_INLINE void HK_CALL testProfile()
	{
		hkpShapeVirtualTableUtil::setProfile<profileType>();
		testCurrentProfile<profileType>();
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
