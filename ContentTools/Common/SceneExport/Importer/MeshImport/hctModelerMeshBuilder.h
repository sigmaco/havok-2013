/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_MODELER_MESH_BUILDER_H
#define HK_MODELER_MESH_BUILDER_H


///
/// This Mesh Builder class is an abstract interface that hides the modeler-specific implementations
/// for common tasks that are required for creating a new mesh/node in all modelers.
///
/// Most functions offer an 'immediate' variant (which performs the respective action right away) as
/// well as a 'delayed' variant (which, if supported by the modeler, collects that data and performs
/// the operation only once the corresponding 'realize' function is called).
///
/// Functions working on channels (e.g. Color and Texture) require the 'selectXXXChannel()' function
/// to be called before data is added to the respective channel.
///
class hctModelerMeshBuilder
{
	public:

		typedef int VertexId;
		typedef int ColorId;
		typedef int UvId;
		typedef int NormalId;

	public:

		//
		// Mesh
		//
		virtual VertexId	addMeshVertexDelayed(const hkVector4& position) = 0;
		virtual int			addMeshTriangleDelayed(VertexId positionIndex0, VertexId positionIndex1, VertexId positionIndex2) = 0;
		virtual void		realizeDelayedMesh() = 0;

		//
		// Vertex Colors
		//
		// Note: Vertex Color triangles and Mesh triangles have to match 1:1
		// Note: If you are adding Vertex Colors using addVertexColorDelayed(), make sure to call realizeDelayedVertexColors() *before*
		//       your (first) call to addVertexColorTriangleImmediate() or realizeDelayedVertexColorTriangles().
		//
		virtual void		selectColorChannel(int channel) = 0;

		virtual ColorId		addVertexColorImmediate(float r, float g, float b) = 0;
		virtual ColorId		addVertexColorDelayed  (float r, float g, float b) = 0;
		virtual void		realizeDelayedVertexColors() = 0;

		virtual int			addVertexColorTriangleImmediate(int triangleIndex, ColorId colorIndexVertex0, ColorId colorIndexVertex1, ColorId colorIndexVertex2) = 0;
		virtual int			addVertexColorTriangleDelayed                     (ColorId colorIndexVertex0, ColorId colorIndexVertex1, ColorId colorIndexVertex2) = 0;
		virtual void		realizeDelayedVertexColorTriangles() = 0;

		//
		// Textures
		//
		// Note: Vertex UV triangles and Mesh triangles have to match 1:1
		// Note: If you are adding Vertex Colors using addVertexUvDelayed(), make sure to call realizeDelayedVertexUvs() *before*
		//       your (first) call to addVertexUvTriangleImmediate() or realizeDelayedVertexUvTriangles().
		//
		virtual void		selectUvChannel(int channel) = 0;

		virtual UvId		addVertexUvImmediate(float u, float v) = 0;
		virtual UvId		addVertexUvDelayed  (float u, float v) = 0;
		virtual void		realizeDelayedVertexUvs() = 0;

		virtual int			addVertexUvTriangleImmediate(int triangleIndex, UvId uvIndexVertex0, UvId uvIndexVertex1, UvId uvIndexVertex2) = 0;
		virtual int			addVertexUvTriangleDelayed                     (UvId uvIndexVertex0, UvId uvIndexVertex1, UvId uvIndexVertex2) = 0;
		virtual void		realizeDelayedVertexUvTriangles() = 0;

		//
		// Normals
		//
		virtual NormalId	addNormalDelayed(const hkVector4& normal) = 0;
		virtual int			addNormalTriangleDelayed(NormalId triangleVertex0, NormalId triangleVertex1, NormalId triangleVertex2) = 0;
		virtual void		realizeDelayedNormals() = 0;

		//
		// Materials
		//
		virtual void		setTriangleMaterialImmediate(int triangleIndex, const char* materialName) = 0;
		virtual void		setTriangleMaterialDelayed  (int triangleIndex, const char* materialName) = 0;
		virtual void		realizeDelayedTriangleMaterials() = 0;

};


#endif //HK_MODELER_MESH_BUILDER_H

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
