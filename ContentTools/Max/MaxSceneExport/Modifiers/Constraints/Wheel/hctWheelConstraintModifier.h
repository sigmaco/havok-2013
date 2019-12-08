/*
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef INC_WHEEL_CONSTRAINT_MODIFIER_H
#define INC_WHEEL_CONSTRAINT_MODIFIER_H

#include <ContentTools/Max/MaxSceneExport/resource.h>
#include <ContentTools/Max/MaxSceneExport/Modifiers/Constraints/hctConstraintModifier.h>
#include <ContentTools/Max/MaxFpInterfaces/Physics/Constraints/hctWheelConstraintModifierInterface.h>


class hctWheelConstraintModifier : public hctConstraintModifier
{
	public:

		//Constructor/Destructor
		hctWheelConstraintModifier(ClassDesc2* theClassDesc);
		/*virtual*/  ~hctWheelConstraintModifier();		

		/*virtual*/ hctConstraintDescriptor* getConstraintDescriptor();

		// From Object - Display stuff. We want to display just two markers.
		/*virtual*/ int Display(TimeValue t, INode* inode, ViewExp *vpt, int flagst, ModContext *mc);
		/*virtual*/ void GetWorldBoundBox(TimeValue t,INode* inode, ViewExp *vpt, Box3& box, ModContext *mc);

	private:

		// The meshes for both spaces are static (shared by all instances)
		static Mesh m_parentSpaceMesh;			// rotation and steering axis
		static Mesh m_parentSuspensionMesh;		// suspension axis and zero plane
		static Mesh m_childSpaceMesh;			// wheel and rotation axis (child)
		static Mesh m_halfCylinder;				// top/bottom suspension volume
		static Mesh m_middleVolume;				// middle suspension volume
		static bool m_staticsMeshesSetup;
		void setupStaticMeshes();

		// Suspension transform = parent transform + rotation caused by steering-suspension offset
		void getSuspensionTransform (TimeValue t, INode* node, Matrix3& transformOut);
		void getBottomVolumeDisplayTransform (TimeValue t, INode* inode, ViewExp* vpt, Matrix3& transformOut);
		void getTopVolumeDisplayTransform (TimeValue t, INode* inode, ViewExp* vpt, Matrix3& transformOut);
		void getMiddleVolumeDisplayTransform (TimeValue t, INode* inode, ViewExp* vpt, Matrix3& transformOut);

};


#endif // INC_WHEEL_CONSTRAINT_MODIFIER_H

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
