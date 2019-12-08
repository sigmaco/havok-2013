/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKX_SPLINE_H
#define HKX_SPLINE_H

class hkxSpline : public hkReferencedObject
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_SCENE_DATA );
		HK_DECLARE_REFLECTION();

		hkxSpline() { }
		hkxSpline(hkFinishLoadedObjectFlag f) : hkReferencedObject(f), m_controlPoints(f) { }

		// Very simmple Hermite curve evaluation. Pick a section (so 0 == ctrl point 0 to 1, etc), and a value t (0..1) alone that section to return for
		void evaluateHermite( int section, float t, hkVector4& r);

		void evaluateByType( int section, float t, hkVector4& r);

		inline int getNumSections() const { return m_isClosed? m_controlPoints.getSize() : m_controlPoints.getSize() - 1; }

		enum ControlType
		{
		  BEZIER_SMOOTH = 0,
		  BEZIER_CORNER = 1, // independant in and out tangents, can create a discontinous change at cps
		  LINEAR = 2,
		  CUSTOM = 3 // unknown, assume user knows
		};

			/// Control point
		struct ControlPoint
		{
			HK_DECLARE_REFLECTION();

				/// Position of the knot (control point)
			hkVector4 m_position;
				/// Incoming tangent.
			hkVector4 m_tangentIn;
				/// Outgoing tangent.
			hkVector4 m_tangentOut;
			
			/// Type of curve from the ctrl point in either direction (linear, smooth biezer, etc).
			hkEnum<ControlType, hkUint8> m_inType;
			hkEnum<ControlType, hkUint8> m_outType;
		};
  
			/// Array of control points defining the spline
		hkArray<ControlPoint> m_controlPoints;
 
			/// Whether the spline is open or closed
		hkBool m_isClosed;


};

#endif // HKX_SPLINE_H

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
