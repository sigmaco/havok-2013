/*
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HCT_CONSTRAINT_MODIFIER_H
#define HCT_CONSTRAINT_MODIFIER_H

#include <ContentTools/Max/MaxSceneExport/Modifiers/hctBasicModifier.h>

#include <ContentTools/Max/MaxFpInterfaces/Physics/Constraints/hctConstraintModifierInterface.h>

// Rollout Category : The spaces/parent parameters appear before other rollouts, while the breakable stuff
// should appear after
// (default category is ROLLUP_CAT_STANDARD = 4000)
enum
{
	ROLLOUT_CATEGORY_CONSTRAINT_BEFORE_PARAMS = 3500,
	ROLLOUT_CATEGORY_CONSTRAINT_POST_PARAMS = 4500
};

// The two rollouts used for the common parameters
enum
{
	MAP_BODIES_ROLLOUT,
	MAP_SPACES_ROLLOUT,
	MAP_BREAKABLE_ROLLOUT,
};

// Subobjects
enum 
{
	SOBJ_CONSTRAINT_MOD_PARENT_SPACE = 0,
	SOBJ_CONSTRAINT_MOD_CHILD_SPACE = 1
};

// Each constraint type must share a static instance of hctConstraintDescriptor and return it in 
// the abstract method getConstraintDescriptor().
class hctConstraintDescriptor
{
	public:

		// IMPORTANT : The constructor of inheriting classes should create:
		// the common pblock descripto (m_commonSpacesPBD) using hkModifier::setupCommonSpacesPBD ()
		// the common fpinterface using hkModifier::addCommonFPInterfacec()

		// Return the Class Descriptor of the modifier implementing the constraint
		virtual ClassDesc2* getClassDesc() const = 0;

		// Return a string ID for the Class Name ("Havok Hinge Constraint" for ex)
		virtual int getClassNameStringID () const = 0;

		// Return a string ID for the Object NAme ("Hinge" for ex)
		virtual int getObjectNameStringID () const = 0;

		// Return the constraint name (name for the pblock)
		virtual MCHAR* getConstraintName() const = 0;

		// Enabling of D.O.F. of the child and parent spaces
		virtual bool ignoreRotations() const { return false; }

		// This affets the interpretation of resetting spaces.
		// If true, resetting the parent space will align it with the child space
		// If false, the parent space will be aligned to the pivot of the parent object.
		virtual bool parentSpaceResetsToChildSpace() const { return true; }

		// Default values for the "lock" check boxes. By default the child space is unlocked
		virtual bool getDefaultLockParentTranslation() const { return true; }
		virtual bool getDefaultLockParentRotation() const  { return true; }
		virtual bool getDefaultLockChildTranslation() const  { return false; }
		virtual bool getDefaultLockChildRotation() const  { return false; }

	public:

		ParamBlockDesc2* m_commonSpacesPBD;

		hctConstraintDescriptor();
		virtual ~hctConstraintDescriptor();

};

// The hctConstraintModifier defines a modifier with common operations and data shared by all constraint types
// In particular, it handles the manipulation of two constraint spaces, stored in a shared parameter block
// It also handles unselected display (through a custom XTC Object)

class hctConstraintModifier : public hctBasicModifier, public hctConstraintModifierFPInterface
{
	public:

		// Constructor/Destructor
		hctConstraintModifier(ClassDesc2* theClassDesc);
		/*virtual*/ ~hctConstraintModifier();		

		// Sets up the common (spaces) pblockdesc using the information in the descriptor
		static ParamBlockDesc2* setupCommonSpacesPBD (hctConstraintDescriptor* constraintDescriptor);

		// Sets up the common fpinterface desc using the information in the descriptor
		static void addCommonFPInterface (hctConstraintDescriptor* constraintDescriptor);

		// Request information about the constraint
		virtual hctConstraintDescriptor* getConstraintDescriptor() = 0;

		// Constraint spaces
		void getSpaceInWorld (int subobjId, TimeValue t, INode* inode, Matrix3& spaceToWorldOut);
		void setSpaceInWorld (int subobjId, TimeValue t, INode* inode, const Matrix3& spaceToWorld);

		// Used for display
		struct ConstraintSpaceData
		{
			INode* m_parentNode;
			INode* m_childNode;
			Matrix3 m_childSpaceRotation;
			Point3 m_childSpaceTranslation;
			Matrix3 m_parentSpaceRotation;
			Point3 m_parentSpaceTranslation;
			bool m_parentSpaceRotationLocked;
			bool m_parentSpaceTranslationLocked;
		};		
		void getConstraintSpaceData (TimeValue t, INode* inode, ConstraintSpaceData& dataOut);

		// Static version, called by hctConstraintXTCObject
		static void getSpaceInWorld (const ConstraintSpaceData& data, int subobjId, TimeValue t, Matrix3& spaceToWorldOut);

		// Update UI. Updates the common UI elements in the rollout. Called when params change.
		void updateCommonUI (TimeValue t);

		/*
		** FPI : From hkConstraintModifierInterface
		*/

		/*virtual*/ FPInterfaceDesc* getCommonFPInterfaceDescriptor();

		/*virtual*/ Matrix3 iGetParentSpaceInWorld (TimeValue t);
		/*virtual*/ void iSetParentSpaceInWorld (Matrix3 parentSpaceWorld, TimeValue t);
		
		/*virtual*/ Matrix3 iGetChildSpaceInWorld (TimeValue t);
		/*virtual*/ void iSetChildSpaceInWorld (Matrix3 childSpaceWorld, TimeValue t);

		/*virtual*/ BOOL iResetChildSpaceTranslation();
		/*virtual*/ BOOL iResetChildSpaceRotation();
		/*virtual*/ BOOL iResetParentSpaceTranslation();
		/*virtual*/ BOOL iResetParentSpaceRotation();

		//From Interface
		/*virtual*/ BaseInterface* GetInterface(Interface_ID id);

		/*
		** Object, class name and ID - Taken from the ConstraintDescriptor.
		*/

		/*virtual*/ CONST15 MCHAR *GetObjectName();
		/*virtual*/ Class_ID ClassID();
		/*virtual*/ void GetClassName(MSTR& s);

		/*
		** SUBOBJECTS : From hctBasicModifier
		*/
		/*virtual*/ int getNumSubobjects ();
		/*virtual*/ bool canSubobjectMove (int subobjId);
		/*virtual*/ bool canSubobjectRotate (int subobjId);
		/*virtual*/ bool canSubobjectScale (int subobjId);
		/*virtual*/ bool isSubobjectEnabled (int subobjId);
		/*virtual*/ void getSubobjectTransform (int subobjId, TimeValue t, INode* node, Matrix3& transformOut);
		/*virtual*/ ISubObjType* getSubobjectTypeByID (int subobjId);

		/*
		** EXTENSION CHANNEL (unselected display) : From hctBasicModifier
		*/
		virtual int getNumXTCObjects () { return 1; }
		/*virtual*/ hctBasicXTCObject* getXTCObject (int number, TimeValue t, ModContext &mc, ObjectState * os, INode *node);

		// From Modifier
		/*virtual*/ void Move(TimeValue t, Matrix3& partm, Matrix3& tmAxis, Point3& despAxis, BOOL localOrigin=FALSE );
		/*virtual*/ void Rotate(TimeValue t, Matrix3& partm, Matrix3& tmAxis, Quat& val, BOOL localOrigin=FALSE );

		// From Object
		// Local Bounding box is calculated from world bounding box
		/*virtual*/ void GetLocalBoundBox(TimeValue t, INode* inode, ViewExp* vp, Box3& box );

		/* From Animatable. It sets ups dialog procs. Make sure inheriting classes call them too */
		/*virtual*/ void BeginEditParams(IObjParam *ip, ULONG flags,Animatable *prev);
		/*virtual*/ void EndEditParams(IObjParam *ip, ULONG flags,Animatable *next);

		// From RefMaker. We forward to hctBasicModifier, but if we are changing our pblock, we make
		// sure the cached values (m_previous...) are updated (calling makePreviousValuesCurrent)
		/*virtual*/ void SetReference(int i, RefTargetHandle rtarg);

	public:

		static void setupMaterials();

		static Material m_parentSpaceMaterial;
		static Material m_childSpaceMaterial;
		static Material m_limitsMaterial;

	public:

		// Previous values, not great, but max doesn't tell us about changes until they happened already
		void makePreviousValuesCurrent();
		int m_previousConstrainTo;
		INode* m_previousParentNode;
		bool m_previousParentTranslationLocked;
		bool m_previousParentRotationLocked;

	private:

		static void setupMeshesAndMaterials();

		static bool m_meshesAndMaterialsSetup;

};

/*
** Constraint XTCObject : It displays two markers at the constraint pivots
*/

#define HK_CONSTRAINT_XTCOBJECT_CLASS_ID	 Class_ID(0x52585340, 0x4e742d40)

class hctConstraintXTCObject : public hctBasicXTCObject
{
	public:

		hctConstraintXTCObject(const hctConstraintModifier::ConstraintSpaceData& data);
		~hctConstraintXTCObject();

		/*virtual*/ Class_ID ExtensionID() { return HK_CONSTRAINT_XTCOBJECT_CLASS_ID; }

		/*virtual*/ XTCObject *Clone() { return new hctConstraintXTCObject (m_data); }

		/*virtual*/ int Display (TimeValue t, INode* inode, ViewExp *vpt, int flags, Object *pObj);

		/*virtual*/ void MaybeEnlargeViewportRect(GraphicsWindow *gw, Rect &rect);

	private:

		hctConstraintModifier::ConstraintSpaceData m_data;
};

#endif //INC_CONSTRAINT_MODIFIER_H

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
