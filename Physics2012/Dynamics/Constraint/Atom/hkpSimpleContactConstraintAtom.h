/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_SIMPLE_CONTACT_CONSTRAINT_ATOM_H
#define HKP_SIMPLE_CONTACT_CONSTRAINT_ATOM_H

#include <Physics2012/Internal/Solver/Contact/hkpSimpleContactConstraintInfo.h>
#include <Common/Base/Types/Physics/ContactPoint/hkContactPoint.h>
#include <Physics/ConstraintSolver/Solve/hkpSolve.h>
#include <Physics/Constraint/Data/hkpConstraintInfo.h>
#include <Physics/Constraint/Atom/hkpConstraintAtom.h>

class hkContactPoint;
class hkpContactPointPropertiesStream;


/// Atom holding contact information for a single hkpSimpleContactConstraintData.
///
/// It is for internal use only and is unique in the following ways:
///     - it is not a member of the owning hkpConstraintData, it is allocated externally
///     - its size is dynamic and varies depending on the number of contact points in the constraint
///     - it is a stand-alone constraint, therefore it derives from hkpConstraintAtom and cannot be followed by any other atom
struct hkpSimpleContactConstraintAtom : public hkpConstraintAtom
{
	public:
	
		HK_DECLARE_REFLECTION();
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CONSTRAINT, hkpSimpleContactConstraintAtom );

		// Size of hkpSimpleContactConstraintAtom is dynamically changed by the engine. It holds up to 256 contact points.
		// We initialize the size of the atom to what it is when no contact points are present.
		hkpSimpleContactConstraintAtom() : hkpConstraintAtom(TYPE_CONTACT) {}

		hkpSimpleContactConstraintAtom(hkFinishLoadedObjectFlag f);

		HK_FORCE_INLINE hkContactPoint* getContactPoints() const { return const_cast<hkContactPoint*>( reinterpret_cast<const hkContactPoint*>( this+1 ) ); }
		HK_FORCE_INLINE int getContactPointPropertiesStriding() const;
		HK_FORCE_INLINE hkpContactPointPropertiesStream* getContactPointPropertiesStream() const { return const_cast<hkpContactPointPropertiesStream*>( reinterpret_cast<const hkpContactPointPropertiesStream*>( hkAddByteOffsetConst( getContactPoints(), sizeof(hkContactPoint) * m_numReservedContactPoints ) ) ); }
		HK_FORCE_INLINE hkpContactPointPropertiesStream* getContactPointPropertiesStream(int i) const;

	public:

		HK_FORCE_INLINE hkpConstraintAtom* next() const { HK_ASSERT2(0x5b5a6955, false, "Not implemented. Need to compute the entire size of contact points & properties."); return HK_NULL; }
		HK_FORCE_INLINE int numSolverResults() const    { return m_numContactPoints+3; }  // this seems wrong looking at the calc below

		HK_FORCE_INLINE void addToConstraintInfo(hkpConstraintInfo& infoOut) const
		{
			int size = m_numContactPoints;

			infoOut.m_sizeOfSchemas    += hkpJacobianSchemaInfo::Header::Sizeof 
										+ (size >> 1) * hkpJacobianSchemaInfo::PairContact::Sizeof 
										+ (size & 1) * hkpJacobianSchemaInfo::SingleContact::Sizeof 
										+ hkpJacobianSchemaInfo::Friction2D::Sizeof;

			infoOut.m_maxSizeOfSchema = infoOut.m_sizeOfSchemas + (hkpJacobianSchemaInfo::Friction3D::Sizeof - hkpJacobianSchemaInfo::Friction2D::Sizeof);
			infoOut.m_numSolverResults   += size + 2;
			infoOut.m_numSolverElemTemps += size + (2 + 1); // extra one for friction

			if ( size >= 2 )
			{
				infoOut.m_sizeOfSchemas   += hkpJacobianSchemaInfo::Friction3D::Sizeof - hkpJacobianSchemaInfo::Friction2D::Sizeof;
				infoOut.m_numSolverResults   += 1; // is that needed ?? solver results are stroed in the info struct
				infoOut.m_numSolverElemTemps += 1 + 0; // just one elem for both 2d & 3d friction anyways.
			}

			if (m_info.m_rollingFrictionMultiplier != 0.0f)
			{
				infoOut.m_sizeOfSchemas += hkpJacobianSchemaInfo::RollingFriction2D::Sizeof;
				infoOut.m_maxSizeOfSchema += hkpJacobianSchemaInfo::RollingFriction2D::Sizeof;
				infoOut.m_numSolverResults += 2; 
				infoOut.m_numSolverElemTemps += 2 + 1;
			}
		}

	public:

		hkUint16 m_sizeOfAllAtoms;
		hkUint16 m_numContactPoints;
		hkUint16 m_numReservedContactPoints;

			// 8 bytes left from here

			// Extra storage for bodyA. Holds hkpShapeKey hierarchy, by default.
		hkUint8 m_numUserDatasForBodyA;

			// Extra storage for bodyA. Holds hkpShapeKey hierarchy, by default.
		hkUint8 m_numUserDatasForBodyB;

			// store striding in here to avoid recomputing in getContactPointPropsStriding()..
		hkUint8 m_contactPointPropertiesStriding;

			// Maximum number for contact points. The limitation is driven by buffer size on SPU, and by contactPointProperties size.
		hkUint16 m_maxNumContactPoints; 
		
		HK_ALIGN16(class hkpSimpleContactConstraintDataInfo m_info);

#if defined(HK_REAL_IS_DOUBLE)
		// align the contact points
		hkUint8 m_padding[16]; //+nosave
#endif
};


// Only include it after the hkpSimpleContactConstraintAtom is defined
#include <Physics2012/Dynamics/Constraint/Contact/hkpContactPointProperties.h>


HK_FORCE_INLINE int hkpSimpleContactConstraintAtom::getContactPointPropertiesStriding() const { return m_contactPointPropertiesStriding; }
HK_FORCE_INLINE hkpContactPointPropertiesStream* hkpSimpleContactConstraintAtom::getContactPointPropertiesStream(int i) const 
{
	const hkContactPoint* endContactPoint = hkAddByteOffsetConst( getContactPoints(), sizeof(hkContactPoint) * m_numReservedContactPoints);
	const hkpContactPointPropertiesStream* beginningOfProperties = reinterpret_cast<const hkpContactPointPropertiesStream*>( endContactPoint );
	return const_cast<hkpContactPointPropertiesStream*>( hkAddByteOffsetConst(  beginningOfProperties, HK_HINT_SIZE16(i) * HK_HINT_SIZE16( getContactPointPropertiesStriding())  ) );
}


#	define HK_GET_LOCAL_CONTACT_ATOM(ATOM) ATOM
#	define HK_CONTACT_ATOM_SET_PPU(ATOM)


#endif // HKP_SIMPLE_CONTACT_CONSTRAINT_ATOM_H

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
