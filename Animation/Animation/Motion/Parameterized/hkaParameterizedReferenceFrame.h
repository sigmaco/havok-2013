/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKA_PARAMETERIZED_REFERENCE_FRAME_H
#define HKA_PARAMETERIZED_REFERENCE_FRAME_H

#include <Animation/Animation/Motion/Default/hkaDefaultAnimatedReferenceFrame.h>

extern const hkClass hkaParameterizedReferenceFrameClass;

/// Interface for a range of parametrized reference frames
class hkaParameterizedReferenceFrame : public hkaDefaultAnimatedReferenceFrame
{
	public:
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_ANIM_MOTION);
		HK_DECLARE_REFLECTION();

			/// Default constructor.
		hkaParameterizedReferenceFrame() : hkaDefaultAnimatedReferenceFrame( REFERENCE_FRAME_PARAMETRIC ) {}

			/// Creates a reference frame based on the specified motion extraction options
		hkaParameterizedReferenceFrame( const MotionExtractionOptions& options ) : hkaDefaultAnimatedReferenceFrame( options, REFERENCE_FRAME_PARAMETRIC ) {}

			/// Creates a reference frame based on an existing default reference frame
		hkaParameterizedReferenceFrame( const hkaDefaultAnimatedReferenceFrame* baseReferenceFrame ) { static_cast<hkaDefaultAnimatedReferenceFrame&>(*this) = *baseReferenceFrame; m_frameType = REFERENCE_FRAME_PARAMETRIC; }

			/// Serialization constructor.
		hkaParameterizedReferenceFrame( hkFinishLoadedObjectFlag flag ) : hkaDefaultAnimatedReferenceFrame( flag, REFERENCE_FRAME_PARAMETRIC ) {}

			/// Destructor.
		virtual ~hkaParameterizedReferenceFrame() {}

			/// Returns a vector containing the parameters that describe the motion.
		virtual void getParameters( hkVector4& outParamVec ) const = 0;

			/// Returns a virtual distance covered by a character moving during a portion of the clip.
			/// Virtual distance defines an abstract ( non-euclidean ) value of displacement in the corresponding 
			/// motion space that is used to synchronize to animation clips together.
		virtual hkReal getDistanceCovered() const = 0;
};

#endif // HKA_PARAMETERIZED_REFERENCE_FRAME_H

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
