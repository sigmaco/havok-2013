/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_BRIDGE_CONSTRAINT_ATOM_H
#define HKP_BRIDGE_CONSTRAINT_ATOM_H

#include <Physics/Constraint/Atom/hkpConstraintAtom.h>
#include <Physics/ConstraintSolver/Constraint/hkpConstraintQueryIn.h>
#include <Physics/ConstraintSolver/Constraint/hkpConstraintQueryOut.h>

class hkpConstraintData;

// Function prototype for Jacobian builders
typedef void (HK_CALL *hkpConstraintAtomBuildJacobianFunc) ( hkpConstraintData* m_constraintData, const hkpConstraintQueryIn &in, hkpConstraintQueryOut &out );


/// Special atom used to implement a custom atomic constraint that generates its Jacobians calling the buildJacobian() 
/// function in the hkpConstraintData member.
struct hkpBridgeConstraintAtom : public hkpConstraintAtom
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CONSTRAINT, hkpBridgeConstraintAtom );
		HK_DECLARE_REFLECTION();

		hkpBridgeConstraintAtom(): hkpConstraintAtom( TYPE_BRIDGE ) {}

		hkpBridgeConstraintAtom(hkFinishLoadedObjectFlag f) : hkpConstraintAtom(f)
		{
			if( f.m_finishing )
			{
				init(m_constraintData);
			}
		}

		// call this to do stuff not done in the constructor yet
		void init (hkpConstraintData* m_constraintData);

		HK_FORCE_INLINE hkpConstraintAtom* next() { return (this+1); }

		// bridge atoms are always the last atom, so no need to increment solver result, just make sure the
		// program crashes if the result of this function is used
		HK_FORCE_INLINE int numSolverResults() const { return 100000; }

		// addToConstraintInfo not needed

	public:

		hkpConstraintAtomBuildJacobianFunc m_buildJacobianFunc;	//+nosave +overridetype(void*)

		hkpConstraintData* m_constraintData; //+owned(false)

#if defined(HK_REAL_IS_DOUBLE)
		hkUint8 m_padding[20]; //+nosave
#else
		hkUint8 m_padding[4]; //+nosave
#endif
};


//
struct hkpBridgeAtoms
{
	public:

		HK_DECLARE_REFLECTION();
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CONSTRAINT, hkpBridgeAtoms );

		hkpBridgeAtoms() {}

		hkpBridgeAtoms(hkFinishLoadedObjectFlag f) : m_bridgeAtom(f) {}

		// get a pointer to the first atom
		const hkpConstraintAtom* getAtoms() const { return &m_bridgeAtom; }

		// get the size of all atoms (we can't use sizeof(*this) because of align16 padding)
		int getSizeOfAllAtoms() const { return hkGetByteOffsetInt(this, &m_bridgeAtom+1); }

	public:
		
		HK_ALIGN_REAL(hkpBridgeConstraintAtom m_bridgeAtom);
};


#endif // HKP_BRIDGE_CONSTRAINT_ATOM_H

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
