/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_POINT_TO_PLANE_CONSTRAINT_DATA_H
#define HKP_POINT_TO_PLANE_CONSTRAINT_DATA_H

#include <Physics/Constraint/Data/hkpConstraintData.h>

extern const class hkClass hkpPointToPlaneConstraintDataAtomsClass;
extern const hkClass hkpPointToPlaneConstraintDataClass;


/// This constrains a point of one body to lie on a plane relative to the second body.
class hkpPointToPlaneConstraintData : public hkpConstraintData
{
	public:

		enum 
		{
			SOLVER_RESULT_LIN_0	= 0,	// linear constraint 
			SOLVER_RESULT_MAX	= 1
		};

		struct Runtime
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_DYNAMICS, hkpPointToPlaneConstraintData::Runtime );

			hkpSolverResults m_solverResults[SOLVER_RESULT_MAX];
		};

		struct Atoms
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_DYNAMICS, hkpPointToPlaneConstraintData::Atoms );
			HK_DECLARE_REFLECTION();

			Atoms() {}

			Atoms(hkFinishLoadedObjectFlag f) : m_transforms(f), m_lin(f) {}

			// get a pointer to the first atom
			const hkpConstraintAtom* getAtoms() const { return &m_transforms; }

			// get the size of all atoms (we can't use sizeof(*this) because of align16 padding)
			int getSizeOfAllAtoms() const { return hkGetByteOffsetInt(this, &m_lin+1); }

			hkpSetLocalTransformsConstraintAtom	m_transforms;
			hkpLinConstraintAtom				m_lin;
		};

	public:
	
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
		HK_DECLARE_REFLECTION();
			
		/// Constructor.
		hkpPointToPlaneConstraintData();
		
		/// Serialization constructor.
		hkpPointToPlaneConstraintData(hkFinishLoadedObjectFlag f) : hkpConstraintData(f), m_atoms(f) {}

		/// Sets the point-to-plane up with world space information.
		/// \param pivotW Specifies both the origin point for the constraining plane, and bodyB's pivot point, specified in world space.
		/// \param planeNormalW Specifies the normal direction of the constraining plane, specified in world space.
		void setInWorldSpace(const hkTransform& bodyATransform, const hkTransform& bodyBTransform, 
								const hkVector4& pivotW, const hkVector4& planeNormalW);

		/// Sets the point-to-plane up with body space information.
		/// \param pivotA Specifies the origin point for the constraining plane, specified in bodyA's space.
		/// \param pivotB BodyB's pivot point, specified in bodyB's space.
		/// \param planeNormalB Specifies the normal direction of the constraining plane, specified in bodyB's space.
		void setInBodySpace(const hkVector4& pivotA, const hkVector4& pivotB, const hkVector4& planeNormalB);

		inline const Runtime* getRuntime( hkpConstraintRuntime* runtime ){ return reinterpret_cast<Runtime*>(runtime); }

		//
		// hkpConstraintData implementation
		//

		virtual int getType() const;

		virtual hkBool isValid() const;

		virtual void getConstraintInfo( ConstraintInfo& infoOut ) const ;

		virtual void getRuntimeInfo( hkBool wantRuntime, hkpConstraintData::RuntimeInfo& infoOut ) const;
		
	public:

		HK_ALIGN_REAL( Atoms m_atoms );
};


#endif // HKP_POINT_TO_PLANE_CONSTRAINT_DATA_H

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
