/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKA_PARAMETERIZED_ANIMATION_REFERENCE_FRAME_H
#define HKA_PARAMETERIZED_ANIMATION_REFERENCE_FRAME_H

#include <Animation/Animation/Motion/Default/hkaDefaultAnimatedReferenceFrame.h>

extern const hkClass hkaParameterizedAnimationReferenceFrameClass;

	/// [DEPRECATED] This class is deprecated and should not be used.  Expect this class to be removed from
	/// the Havok SDK in a future release.  Use the Extract Motion filter with
	/// Angular/Directional motion extraction instead.
	/// (See hkbAngularReferenceFrame and hkbDirecitonalReferanceFrame.)
	/// Reference frame stores parameters which describe the motion represented by the reference frame.
class hkaParameterizedAnimationReferenceFrame: public hkaDefaultAnimatedReferenceFrame
{
	public:
		
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_ANIM_MOTION);
		HK_DECLARE_REFLECTION();
			
			/// Types of parameters that can be stored in the reference frame. 
		enum ParameterType
		{			
			UNKNOWN = 0,
			LINEAR_SPEED,
			LINEAR_DIRECTION,
			TURN_SPEED,
		};

			/// Initializes a new reference frame without any motion parameters
		hkaParameterizedAnimationReferenceFrame( const hkaDefaultAnimatedReferenceFrame& other );

			/// DOC
		void addParameter( ParameterType type, hkReal value	);
			/// DOC
		void removeParameter( ParameterType type, hkReal value);

			/// Tells if th frame contains the specified parameter type
		hkBool containsParameter( ParameterType type ) const;

			/// DOC
		void getParameterValue1D( ParameterType type, hkReal& valueOut ) const;
			/// DOC
		void getParameterValue2D( ParameterType typeA, ParameterType typeB, hkReal& valueAOut, hkReal& valueBOut ) const;

			/// DOC		
		static void HK_CALL transformCoordinates( ParameterType typeA, ParameterType typeB, hkReal& valueAInOut, hkReal& valueBInOut );
	public:

			/// Parameters stored in the reference frame
		hkArray<hkReal> m_parameterValues;
			/// The types of parameters stored in the reference frame
		hkArray<hkInt32> m_parameterTypes;

	public:

			/// Serialization constructor
		hkaParameterizedAnimationReferenceFrame( hkFinishLoadedObjectFlag flag ) : hkaDefaultAnimatedReferenceFrame(flag), m_parameterValues(flag), m_parameterTypes(flag) {}

};

#endif

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
