/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_BASE_INERTIA_TENSOR_COMPUTER_H
#define HK_BASE_INERTIA_TENSOR_COMPUTER_H

extern const class hkClass hkMassPropertiesClass;

struct hkGeometry;
class hkpShape;
class hkpRigidBodyCinfo;
class hkpRigidBody;
class hkpConstraintInstance;
struct hkStridedVertices;


/// This structure holds the "mass and volume" properties of an object, and is filled in by each of the
/// hkInertiaTensorComputer methods.
/// Volume is not strictly a mass property, but may be useful to help determine the mass required
/// to achieve a given density for an object.
struct hkMassProperties
{
	//+version(1)

	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_INERTIA, hkMassProperties );

	HK_DECLARE_REFLECTION();

	/// Initialize (to zero data).
	hkMassProperties() : m_volume(0), m_mass(0) { m_centerOfMass.setZero(); m_inertiaTensor.setZero(); }

	hkMassProperties( class hkFinishLoadedObjectFlag flag ) {}

	void scaleToDensity( hkSimdRealParameter density );

	void scaleToMass( hkSimdRealParameter newMass );

		/// The volume of an object.
	hkReal m_volume;

		/// The mass of an object.
	hkReal m_mass;

		/// The center of mass.
	hkVector4 m_centerOfMass;

		/// The inertia tensor.
	hkMatrix3 m_inertiaTensor;
};


/// This structure is used by the hkInertiaTensorComputer to help construct mass properties of "compound" objects.
struct hkMassElement
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_INERTIA, hkMassElement );

		/// Initialize (to zero data).
	HK_FORCE_INLINE hkMassElement() { m_transform.setIdentity(); }

		/// Initialize given properties and transform.
	HK_FORCE_INLINE hkMassElement( const hkMassProperties& properties,const hkTransform& transform ) :
		m_properties(properties), m_transform(transform) {}

		/// All mass properties for this element.
	hkMassProperties m_properties;

		/// A transform for this element (usually with respect to body Local space)
		/// i.e., an ElementToLocal transform.
	hkTransform m_transform;
};


/// A class to compute the inertia tensor, center of mass and volume of various classes of objects.
class hkInertiaTensorComputer
{
	public:

		///////////////////////////////////////
		// Explicit surface types calculations
		///////////////////////////////////////

			/// Creates mass properties given a sphere, considered as a volume of uniform density.
			/// Returns HK_FAILURE on failure (radius, mass invalid), otherwise returns HK_SUCCESS.
		static hkResult HK_CALL computeSphereVolumeMassProperties( hkReal radius, hkReal mass, hkMassProperties& result);

			/// Creates mass properties given box halfextents, considered as a volume of uniform density.
			/// Returns HK_FAILURE on failure (halfExtents, mass invalid), otherwise returns HK_SUCCESS.
		static hkResult HK_CALL computeBoxVolumeMassProperties(hkVector4Parameter halfExtents, hkReal mass, hkMassProperties& result);

			/// Creates mass properties given box \a halfExtents, considered as a volume of uniform density.
			/// Returns HK_FAILURE on failue, otherwise sets \a volume of the box and the \a inertiaDiagonal and returns HK_SUCCESS.
		static hkResult HK_CALL computeBoxVolumeMassPropertiesDiagonalized(hkVector4Parameter halfExtents, hkReal mass, hkVector4 &inertiaDiagonal, hkReal& volume);

			/// Creates mass properties given a capsule considered as a volume of uniform density.
			/// The capsule is specified by the start and end points of its axis (excluding radius), and a radius.
			/// The radius MUST be greater than zero. The height (length of axis) may be zero.
			/// Returns HK_FAILURE on failure (radius, mass invalid), otherwise returns HK_SUCCESS.
		static hkResult HK_CALL computeCapsuleVolumeMassProperties( hkVector4Parameter startAxis, hkVector4Parameter endAxis, hkReal radius, hkReal mass, hkMassProperties& result);

			/// Creates mass properties given a sphere hull, assumed to have a given thickness (measured "inwards") of uniform density.
			/// The thickness MUST be greater than zero and less than radius.
			/// Returns HK_FAILURE on failure (radius, surfaceThickness, mass invalid), otherwise returns HK_SUCCESS.
		static hkResult HK_CALL computeSphereSurfaceMassProperties( hkReal radius, hkReal mass, hkReal surfaceThickness, hkMassProperties& result);

			/// Creates mass properties given box hull halfextents, assumed to have a given thickness (measured "inwards") of uniform density.
			/// The thickness MUST be greater than zero and less than min of half-extents.
			/// Returns HK_FAILURE on failure (halfExtents, surfaceThickness, mass invalid), otherwise returns HK_SUCCESS.
		static hkResult HK_CALL computeBoxSurfaceMassProperties(hkVector4Parameter halfExtents, hkReal mass, hkReal surfaceThickness, hkMassProperties& result);

			/// Creates mass properties given triangle vertices, assumed to have a given thickness, of uniform density.
			/// The thickness MUST be greater than or EQUAL to zero. It can be zero, in which case the mass properties calculated are those
			/// of a triangular lamina. Otherwise it generates a triangular prism with center equal to the triangle center.
			/// Returns HK_FAILURE on failure (surfaceThickness, mass invalid), otherwise returns HK_SUCCESS.
		static hkResult HK_CALL computeTriangleSurfaceMassProperties(hkVector4Parameter v0, hkVector4Parameter v1, hkVector4Parameter v2, hkReal mass, hkReal surfaceThickness, hkMassProperties& result);

			/// Creates mass properties given a cylinder, considered as a volume of uniform density.
			/// Returns HK_FAILURE on failure (startAxis, endAxis, radius, mass invalid), otherwise returns HK_SUCCESS.
		static hkResult HK_CALL computeCylinderVolumeMassProperties(hkVector4Parameter startAxis, hkVector4Parameter endAxis, hkReal radius, hkReal mass, hkMassProperties& result);


		///////////////////////////////////////
		// Geometric/vertex-based calculations
		///////////////////////////////////////


			/// Function ptr type to override convex hull mass properties calculation
		typedef hkResult (HK_CALL *ConvexHullMassPropertiesFunction)(const hkStridedVertices&, hkReal, hkMassProperties&);

			/// Function ptr to calculate convex hull mass properties.
			/// To enable dead-stripping of geometry code, this points to a simple implementation
		static ConvexHullMassPropertiesFunction computeConvexHullMassProperties;

	protected:

			/// Calculate mass properties of a convex hull specified by its vertices.
			/// The convex hull might by expanded by 'radius' or automatically if the convex hull is not a value.
			/// Returns HK_FAILURE only if no vertices are provided, else always compute a valid mass properties and HK_SUCCESS
		static hkResult HK_CALL	computeApproximateConvexHullMassProperties(const hkStridedVertices& vertices, hkReal radius, hkMassProperties& result);

	public:

			/// Creates mass properties given a point cloud, using the convex hull of the cloud, considered as a volume of uniform density.
			/// Returns HK_FAILURE on failure (vertices coplanar, mass invalid), otherwise returns HK_SUCCESS.
		static hkResult HK_CALL computeVertexHullVolumeMassProperties(const hkReal* vertexIn, int striding, int numVertices, hkReal mass, hkMassProperties &result);

			/// Creates mass properties given a point cloud, using vertices as point masses, with uniform mass distribution.
			/// Returns HK_FAILURE on failure (vertices, mass invalid), otherwise returns HK_SUCCESS.
			/// No volume is assumed/calculated.
		static hkResult HK_CALL computeVertexCloudMassProperties(const hkReal* vertexIn, int striding, int numVertices, hkReal mass, hkMassProperties &result);

			/// Creates mass properties for the given (possibly open/disconnected) geometry using triangles assumed to have a given thickness to provide volume.
			/// If distributeUniformly is true, the mass is distributed proportional to the area of each triangle.
			/// If distributeUniformly is false, the same mass is given to each triangle, independent of its area. This means that "highly tessellated"
			/// areas will have more mass, usually undesirable, but perhaps useful in some instances.
			/// The thickness MUST be greater than zero.
			/// Returns HK_FAILURE on failure (geometry, surfaceThickness, mass invalid), otherwise returns HK_SUCCESS.
		static hkResult HK_CALL computeGeometrySurfaceMassProperties(const hkGeometry* geom, hkReal surfaceThickness, hkBool distributeUniformly, hkReal mass, hkMassProperties &result);

		/// Computes the inertia tensor and the center of mass given a total mass for the provided geometry.
		/// Asserts on failure (geometry, surfaceThickness, mass invalid), otherwise returns.
		/// \warning This function assumes the geometry is properly closed.
		static void HK_CALL computeGeometryVolumeMassProperties(const hkGeometry* geom, hkReal mass, hkMassProperties &result);

		/// Computes the inertia tensor and the center of mass given a total mass for the provided geometry.
		/// returns HK_FAILURE on failure (geometry, surfaceThickness, mass invalid), otherwise returns.
		/// \warning This function assumes the geometry is properly closed.
		static hkResult HK_CALL computeGeometryVolumeMassPropertiesChecked(const hkGeometry* geom, hkReal mass, hkMassProperties &result);



		///////////////////////////////////////
		// Compound calculation
		///////////////////////////////////////

			/// Creates mass properties given a group of mass properties/transforms in a common space.
			/// For example, to compute mass properties for an hkpListShape-based compound body with children of different
			/// masses, use computeShapeVolumeMassProperties() to compute each child's mass element.
			/// (with m_transform left as identity), and then combine them using this method.
			/// Returns HK_FAILURE on failure (mass invalid), otherwise returns HK_SUCCESS.
		static hkResult HK_CALL combineMassProperties(const hkArray<hkMassElement>& elements, hkMassProperties& result );


		///////////////////////////////////////
		// Inertia Tensor Simplification  
		///////////////////////////////////////

			/// Computes a "best" approximation of a full inertia tensor as an oriented particle inertia tensor, which
			/// is constant along the diagonal, and zero on the off-diagonals, i.e., = I * k for some k. The matrix passed in
			/// is set to this approximation.
		static void HK_CALL simplifyInertiaTensorToOrientedParticle(hkMatrix3 &inertia);

			/// Converts a full inertia tensor to a space, where the inertia is just a diagonal
			/// matrix. principleAxisOut is a matrix converting from the new principle axis space
			/// to the old inertia tensor space.
		static void HK_CALL convertInertiaTensorToPrincipleAxis( hkMatrix3& inertia, hkRotation& principleAxisOut );


		///////////////////////////////////////
		// Helper functions
		///////////////////////////////////////


			/// Given an inertia tensor calculated in a space, and the center of mass in this space
			/// this function calculates the inertia around the center of mass. The physics simulation
			/// expects all inertia tensors to be expressed around the center of mass.
		static void HK_CALL shiftInertiaToCom(hkVector4Parameter shift, hkSimdRealParameter mass, hkMatrix3& inertia);

			/// Given an inertia tensor calculated around the center of mass, and the center of mass itself
			/// this function calculates the inertia around a point shifted away from the
			/// center of mass. This allows you to move inertia tensors to a common space so they can be combined.
		static void HK_CALL shiftInertiaFromCom(hkVector4Parameter shift, hkSimdRealParameter mass, hkMatrix3& inertia);
};


#endif // HK_BASE_INERTIA_TENSOR_COMPUTER_H

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
