/*
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef INC_STIFF_SPRING_MODIFIER_H
#define INC_STIFF_SPRING_MODIFIER_H

#include <ContentTools/Max/MaxSceneExport/resource.h>
#include <ContentTools/Max/MaxSceneExport/Modifiers/Constraints/hctConstraintModifier.h>
#include <ContentTools/Max/MaxFpInterfaces/Physics/Constraints/hctStiffSpringConstraintModifierInterface.h>

class hctStiffSpringConstraintModifier : public hctConstraintModifier
{
	public:

		//Constructor/Destructor
		hctStiffSpringConstraintModifier(ClassDesc2* theClassDesc);
		/*virtual*/  ~hctStiffSpringConstraintModifier();		

		/*virtual*/ hctConstraintDescriptor* getConstraintDescriptor();

		// From Object - Display stuff. We want to display just two markers.
		/*virtual*/ int Display(TimeValue t, INode* inode, ViewExp *vpt, int flagst, ModContext *mc);
		/*virtual*/ void GetWorldBoundBox(TimeValue t,INode* inode, ViewExp *vpt, Box3& box, ModContext *mc);

		// From RefMaker
		/*virtual*/ RefResult NotifyRefChanged( Interval changeInt, RefTargetHandle hTarget, PartID& partID,  RefMessage message);

	private:

		void getRodDisplayTransform (TimeValue t, INode* inode, ViewExp* vpt, Matrix3& transformOut);

		// The mesh is static since it is reused by all stiff springs
		static Mesh m_rodMesh;
		static bool m_rodMeshSetup;
		void setupRodMesh();

		// Set the rest length based on the current distance between spaces
		void setRestLengthBasedOnCurrentDistance();

};

#endif // INC_STIFF_SPRING_MODIFIER_H

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
