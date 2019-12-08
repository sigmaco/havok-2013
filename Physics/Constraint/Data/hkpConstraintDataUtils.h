/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#include <Physics/Constraint/hkpConstraint.h>

class hkpConstraintMotor;
class hkpConstraintData;
struct hkpConstraintRuntime;

/// Utility functions to operate on a constraint data.
namespace hkpConstraintDataUtils
{
	/// Converts a constraint data to its powered version. Works only with Ragdoll and Hinge constraints.
	void HK_CALL convertToPowered ( hkpConstraintData* data, hkpConstraintMotor* motor, hkBool enableMotors );

	/// Creates a copy of the constraint data in its limited version (dynamically allocates).
	hkpConstraintData* HK_CALL createLimited( const hkpConstraintData* data );

	/// Extracts pivot vectors from the constraint.
	hkResult HK_CALL getConstraintPivots ( const hkpConstraintData* data, hkVector4& pivotInAOut, hkVector4& pivotInBOut );
	

	/// Extracts motors from the constraints.
	hkResult HK_CALL getConstraintMotors( const hkpConstraintData* data, hkpConstraintMotor*& motor0, hkpConstraintMotor*& motor1, hkpConstraintMotor*& motor2 );

	/// Loosen the constraint limits so that its constrained bodies' transforms are no longer violating them.
	///
	/// NOTE: This class only operates on the limits of CONSTRAINT_TYPE_RAGDOLL and CONSTRAINT_TYPE_LIMITEDHINGE constraints.
	///		  Other constraint types are currently not supported. Additionally, this cannot loosen constrained axes which
	///		  are not controlled by a limit (i.e., the non-principle axes of the limited hinge constraint, positional constraint, etc.).
	hkResult HK_CALL loosenConstraintLimits( hkpConstraintData* data, const hkTransform& bodyATransform, const hkTransform& bodyBTransform );

	/// Returns largest linear impulse. Needs runtime info.
	hkVector4 getLargestLinearImpulse( const hkpConstraintData* dataIn, const hkpConstraintRuntime* runtimeIn, const hkQTransform& transformA, const hkQTransform& transformB );

	/// Checks if the constraint supports getting and setting of its pivot points.
	hkBool HK_CALL constraintSupportsPivotGetSet(const hkpConstraintData* data);

	/// Get the constraint's pivot for body A.
	const hkVector4& HK_CALL getPivotA(const hkpConstraintData* data);

	/// Get the constraint's pivot for body B.
	const hkVector4& HK_CALL getPivotB(const hkpConstraintData* data);

	/// Get the constraint's pivot for body i = 0 / 1.
	hkVector4Parameter HK_CALL getPivot(const hkpConstraintData* data, int pivotIndex);

	/// Set the constraint's pivot for body A.
	void HK_CALL setPivot(hkpConstraintData* data, const hkVector4& pivot, int pivotIndex);

	/// Set the constraint's pivot for body A.
	void HK_CALL setPivotTransform(hkpConstraintData* data, const hkTransform& pivot, int pivotIndex);

	/// Get the pivot transform.
	void HK_CALL getPivotTransform( const hkpConstraintData* data, int index, hkTransform& pivot );

	/// This creates a clone of the three constraints that can have motors,
	/// namely hkpLimitedHingeConstraintData, hkpPrismaticConstraintData and hkpRagdollConstraintData.
	/// This does not support the powered chains.
	/// The function returns HK_NULL for unsupported types of constraints.
	hkpConstraintData* HK_CALL cloneIfCanHaveMotors(const hkpConstraintData* data);

	/// Returns a deep copy of the constraint data.
	/// If the constraint wraps another, for example, a breakable or
	/// malleable constraint, it clones the child constraint also.
	hkpConstraintData* HK_CALL deepClone(const hkpConstraintData* data);
}

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
