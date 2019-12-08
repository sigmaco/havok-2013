/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_VISUALIZE_DEBUG_DISPLAY_PROCESS
#define HK_VISUALIZE_DEBUG_DISPLAY_PROCESS

#include <Common/Visualize/hkProcess.h>
#include <Common/Visualize/hkDebugDisplayHandler.h>

class hkProcessContext;

/// This class implements the hkDisplayHandler interface. It serializes
/// hkDisplayHandler calls so that they can be streamed over the network.
class hkDebugDisplayProcess : public hkReferencedObject, public hkProcess, public hkDebugDisplayHandler
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_VDB);

			/// Serializes hkDisplayHandler messages, the stream must be writable.
		hkDebugDisplayProcess();

			/// Destructor.
		virtual ~hkDebugDisplayProcess();
		
		//
		// Process
		//

		static hkProcess* HK_CALL create(const hkArray<hkProcessContext*>& contexts);

		/// Registers the hkDebugDisplayProcess with the hkProcessFactory.
		static void HK_CALL registerProcess();

		/// Gets the tag associated with this viewer type
		virtual int getProcessTag() { return m_tag; }

		static inline const char* HK_CALL getName() { return "Debug Display"; }

		//
		// Display handler functions
		//
		using hkDebugDisplayHandler::addGeometry;

		virtual hkResult addGeometry(const hkArrayBase<hkDisplayGeometry*>& geometries, const hkTransform& transform, hkUlong id, int tag, hkUlong shapeIdHint, hkGeometry::GeometryType geomType) HK_OVERRIDE;
		virtual hkResult addGeometryInstance(hkUlong instID, const hkTransform& transform, hkUlong id, int tag, hkUlong shapeIdHint) HK_OVERRIDE;
		virtual hkResult setGeometryPickable( hkBool isPickable, hkUlong id, int tag ) HK_OVERRIDE;
		virtual hkResult setGeometryVisibility(int geometryIndex, bool isVisible, hkUlong id, int tag) HK_OVERRIDE;
		virtual hkResult setGeometryColor(hkColor::Argb color, hkUlong id, int tag) HK_OVERRIDE;
		virtual hkResult setGeometryTransparency(float alpha, hkUlong id, int tag) HK_OVERRIDE;
		virtual hkResult updateGeometry(const hkTransform& transform, hkUlong id, int tag) HK_OVERRIDE;
		virtual hkResult updateGeometry( const hkMatrix4& transform, hkUlong id, int tag ) HK_OVERRIDE;
		virtual hkResult skinGeometry(hkUlong* ids, int numIds, const hkMatrix4* poseModel, int numPoseModel, const hkMatrix4& worldFromModel, int tag ) HK_OVERRIDE;
		virtual hkResult removeGeometry(hkUlong id, int tag, hkUlong shapeIdHint) HK_OVERRIDE;
		
		virtual hkResult updateCamera(const hkVector4& from, const hkVector4& to, const hkVector4& up, hkReal nearPlane, hkReal farPlane, hkReal fov, const char* name) HK_OVERRIDE;
			
		virtual hkResult displayPoint(const hkVector4& position, hkColor::Argb color, int id, int tag) HK_OVERRIDE;
		virtual hkResult displayLine(const hkVector4& start, const hkVector4& end, hkColor::Argb color, int id, int tag) HK_OVERRIDE;
		virtual hkResult displayTriangle(const hkVector4& a, const hkVector4& b, const hkVector4& c, hkColor::Argb color, int id, int tag) HK_OVERRIDE;

		virtual hkResult displayPoint2d(const hkVector4& position, hkColor::Argb color, int id, int tag) HK_OVERRIDE;
		virtual hkResult displayLine2d(const hkVector4& start, const hkVector4& end, hkColor::Argb color, int id, int tag) HK_OVERRIDE;
		virtual hkResult displayTriangle2d(const hkVector4& a, const hkVector4& b, const hkVector4& c, hkColor::Argb color, int id, int tag) HK_OVERRIDE;
		virtual hkResult displayText2d(const char* text, const hkVector4& pos, hkReal sizeScale, hkColor::Argb color, int id, int tag) HK_OVERRIDE;

		virtual hkResult displayText(const char* text, hkColor::Argb color, int id, int tag);
		virtual hkResult display3dText(const char* text, const hkVector4& pos, hkColor::Argb color, int id, int tag) HK_OVERRIDE;
		virtual hkResult displayAnnotation(const char* text, int id, int tag) HK_OVERRIDE;

		virtual hkResult displayGeometry(const hkArrayBase<hkDisplayGeometry*>& geometries, const hkTransform& transform, hkColor::Argb color, int id, int tag) HK_OVERRIDE;
		virtual hkResult displayGeometry(const hkArrayBase<hkDisplayGeometry*>& geometries, hkColor::Argb color, int id, int tag) HK_OVERRIDE;

		virtual hkResult sendMemStatsDump(const char* data, int length);

		virtual hkResult holdImmediate();

	protected:
	
		static int m_tag;

};

#endif // HK_VISUALIZE_DEBUG_DISPLAY_PROCESS

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
