/*
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef INC_BASIC_MODIFIER_H
#define INC_BASIC_MODIFIER_H

// This modifier type handles
// * Arbitrary number of subobjects with scale, rotate and move operations. Each subobject can be enabled and
// disabled, and is referred through a subobject ID
// * Addition of an XTCObject (extension channel object) to the pipeline
// * Handling of integer parameters through a ComboBox UI (not supported by max)
// * Survival of modifier stack collapsing operations
// * Handling of paramblocks and references
// * Cloning
// * Other max sdk operations
// All modifiers used by the havok exporter inherit from this class (or one of its subsclasses).

class hctBasicModifier : public Modifier 
{
	public:

		hctBasicModifier (ClassDesc2* theClassDesc);
		virtual ~hctBasicModifier();


		/*
		** SUBOBJECT HANDLING
		** By default, no subobjects are available
		*/

		virtual int getNumSubobjects () {return 0;}
		virtual ISubObjType* getSubobjectTypeByID (int subobjId) {return NULL;}
		virtual bool canSubobjectMove (int subobjId) {return false;}
		virtual bool canSubobjectRotate (int subobjId) {return false;}
		virtual bool canSubobjectScale (int subobjId) {return false;}
		virtual bool isSubobjectEnabled (int subobjId) {return false;}

		virtual void getSubobjectTransform (int subobjId, TimeValue t, INode* node, Matrix3& transformOut);

		/* Utility Methods */

		// Updates the subobject list in the interface.
		void updateSubobjects ();

		// Gets the ID of the subobject currently selected
		int getCurrentSubobjectID ();
		
		// Selects the given subobject ID
		void selectSubobjectByID (int subobjId);

		// Conversion between current subobject level and ID
		int subobjectLevelToID (int subobjLevel);
		int subobjectIDToLevel (int subobjId);

		// Manually set the ClassDesc2 pointer. Caution! Use at own risk!
		void setClassDesc2(ClassDesc2* classDesc);

		/*
		** Update UI
		*/

		// Implement it with any code that updates the state of controls, etc..
		virtual void updateUI() {}

		/*
		** EXTENSION CHANNEL : If the modifier wants to add an XTC object for display, it can do so by returning it here
		*/

		virtual int getNumXTCObjects () { return 0; }
		virtual class hctBasicXTCObject* getXTCObject (int number, TimeValue t, ModContext &mc, ObjectState * os, INode *node) { return NULL; }

		/*
		** COMBO BOXES : Max SDK doesn't handle parameters using Combo Box UI, but we like combo boxes
		*/

		class ComboBoxDescriptor
		{
			public:
				virtual BlockID getParamBlockID() = 0;
				virtual MapID getParamMapID() = 0;
				virtual ParamID getParamID() = 0;
				virtual int getControlID() = 0;
				virtual int getNumElements() = 0;
				virtual const char* getElementString (int i) = 0;
				virtual const int getElementValue (int i) = 0;
		};

		virtual int getNumComboBoxes () { return 0; }
		virtual ComboBoxDescriptor* getComboBoxDescriptor (int comboBoxID) {return NULL;}

		// The dialog proc of the rollout having a combo box should always call this method
		// If you use the default dlg proc (getComboBoxHandlerDlgProc()), this is done for you
		BOOL handleComboBoxMessages (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

		// You can use this default dlgProc if you don't need to do any other processing.
		static const ParamMap2UserDlgProc* getComboBoxHandlerDlgProc();

		/*
		** MaxSDK Methods implemented by our basic modifier
		*/

		// Does basic setup. Needs to be called by inheriting plugins.
		/*virtual*/ void BeginEditParams(IObjParam *ip, ULONG flags,Animatable *prev);
		/*virtual*/ void EndEditParams(IObjParam *ip, ULONG flags,Animatable *next);

		// We use the extension channel
		/*virtual*/ ChannelMask ChannelsUsed()  { return EXTENSION_CHANNEL | GEOM_CHANNEL; }
		/*virtual*/ ChannelMask ChannelsChanged() { return EXTENSION_CHANNEL ; }

		// From Modifier
		/*virtual*/ void ModifyObject(TimeValue t, ModContext &mc, ObjectState * os, INode *node);
		/*virtual*/ Class_ID InputType() {return defObjectClassID;}
		/*virtual*/ Interval LocalValidity (TimeValue t);

		// From BaseObject
		/*virtual*/ CreateMouseCallBack* GetCreateMouseCallBack() {return NULL;}

		// From Animatable
		/*virtual*/ SClass_ID SuperClassID() { return OSM_CLASS_ID; }

		/*virtual*/ BOOL HasUVW() {return FALSE;}

		// Subobject manipulation
		/*virtual*/ int NumSubObjTypes();
		/*virtual*/ ISubObjType *GetSubObjType(int i);
		/*virtual*/ void ActivateSubobjSel(int level, XFormModes& modes );
		/*virtual*/ void GetSubObjectTMs(SubObjAxisCallback *cb, TimeValue t,INode *node, ModContext *mc);
		/*virtual*/ void GetSubObjectCenters(SubObjAxisCallback *cb,TimeValue t,INode *node, ModContext *mc);

		// To avoid stack collapsing
		/*virtual*/ void NotifyPreCollapse(INode *node, IDerivedObject *derObj, int index);
		/*virtual*/ void NotifyPostCollapse(INode *node,Object *obj, IDerivedObject *derObj, int index);

		// Display
		/*virtual*/ int HitTest(TimeValue t, INode* inode, int type, int crossing, int flags, IPoint2 *p, ViewExp *vpt, ModContext* mc);

		// Reference maker
		/*virtual*/ RefTargetHandle Clone( RemapDir &remap );
		/*virtual*/ void BaseClone(ReferenceTarget* from, ReferenceTarget* to, RemapDir& remap);

		/*virtual*/ int NumRefs();
		/*virtual*/ RefTargetHandle GetReference(int i);
		/*virtual*/ void SetReference(int i, RefTargetHandle rtarg);
		/*virtual*/ RefResult NotifyRefChanged( Interval changeInt, RefTargetHandle hTarget, PartID& partID,  RefMessage message);
		
		/*virtual*/ int	NumParamBlocks() { return m_pblocks.Count(); }	// return number of ParamBlocks in this instance
		/*virtual*/ IParamBlock2* GetParamBlock(int i) { if (i < m_pblocks.Count()) { return m_pblocks[i]; } else { return NULL; } } // return i'th ParamBlock
		/*virtual*/ IParamBlock2* GetParamBlockByID(BlockID id);

		// From Animatable
		/*virtual*/ int NumSubs() {return m_pblocks.Count();}
		/*virtual*/ Animatable* SubAnim(int i) {return GetParamBlock(i);}
		/*virtual*/ MSTR SubAnimName(int i) {return GetParamBlock(i)->GetLocalName();}
		/*virtual*/ int SubNumToRefNum(int subNum) {return subNum;}

		/*virtual*/ void DeleteThis() { delete this; }		

		virtual float getScaleDisplay(TimeValue t, INode* inode, ViewExp* vpt);
		virtual float getScaleDisplay(const Point3& posWorld, ViewExp* vpt);

		/*
		** Force Notify Accesor : Enforces the reevaluation of modifiers after a parameter change.
		** Useful for class parameters. Add a pb_accessor clause pointing to a static instance (one for each modifier class).
		*/
		class ForceNotifyPBAccessor: public PBAccessor
		{ 
			public:

				// Called automatically by the paramblock.
				void Set(PB2Value& v, ReferenceMaker* owner, ParamID id, int tabIndex, TimeValue t);

				// Call this on construction of each modifier
				void addModifier(hctBasicModifier* modifier);

				// Call this on destruction of each modifier
				void removeModifier(hctBasicModifier* modifier);

			private:

				Tab<ReferenceMaker*> m_modifiers;
		};

	public:

		// Access to the interface
		static IObjParam* m_interface;			

		// Move Command Mode
		static MoveModBoxCMode* m_moveMode;
		// Scale Command Mode
		static NUScaleModBoxCMode* m_scaleMode;
		// Rotate Command Mode
		static RotateModBoxCMode* m_rotateMode;

		// Last Selected Subobject ID. Used to restore selection after update.
		int m_lastSelectedSubobjectID;
		
	private:

		// Our parameter blocks
		Tab<IParamBlock2*> m_pblocks;	

		// The class descriptor
		ClassDesc2* m_classDesc;

		// Handling of combo boxes
		void fillComboBoxes();
		void updateComboBoxFromParam (int comboBoxId);
		void updateParamFromComboBox (int comboBoxId);
		bool m_updatingParamsFromComboBoxes;
		bool m_updatingComboBoxesFromParams;

	protected:

		// Utilities

		// Gets a quaternion from a matrix (matrix may have scale)
		static Quat getRotationFromMatrix (const Matrix3& matrix);
		
		// Gets a matrix containing only rotation and translation
		static Matrix3 removeScale (const Matrix3& matrix);
};

/*
** Basic XTC Object : We usually are only interested on display; this class implements all methods except Display, ExtensionID() and Clone()
*/
class hctBasicXTCObject : public XTCObject
{
	public:

		hctBasicXTCObject () {}
		virtual ~hctBasicXTCObject() {}
		void DeleteThis() { delete this; }
		ChannelMask DependsOn() { return 0; }
		ChannelMask ChannelsChanged() { return 0; }
		void PreChanChangedNotify(TimeValue t, ModContext &mc, ObjectState* os, INode *node,Modifier *mod, bool bEndOfPipeline) {}
		void PostChanChangedNotify(TimeValue t, ModContext &mc, ObjectState* os, INode *node,Modifier *mod, bool bEndOfPipeline) {}
		BOOL SuspendObjectDisplay() { return FALSE; }
};


#endif // INC_BASIC_MODIFIER_H

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
