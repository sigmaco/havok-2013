/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_CONSTRAINT_INFO_H
#define HKP_CONSTRAINT_INFO_H


// Descriptions of the layout of each type of Jacobian schema.
namespace hkpJacobianSchemaInfo
{
	enum
	{
	#if defined(HK_REAL_IS_DOUBLE)
		DoubleSize = 2,
	#else
		DoubleSize = 1,
	#endif
	};

	// Size of End and Header should be the same (HVK-6329).
	struct End
	{ enum {
	#if HK_POINTER_SIZE == 4
		Sizeof = HK_REAL_ALIGNMENT,  
	#else 
		Sizeof = 32,  
	#endif
	}; };

	struct Header 
	{ enum {
	#if HK_POINTER_SIZE == 4
		Sizeof = HK_REAL_ALIGNMENT,  
	#else
		Sizeof = 32,  
	#endif
	}; };

	struct Goto
	{ enum {
		Temps = 0,
		Results = 0,
		Sizeof = DoubleSize*16,
	}; };

	struct ShiftSolverResults
	{ enum {
		Temps = 0,
		Sizeof = DoubleSize*16,
	}; };

	struct Bilateral1D
	{ enum {
		Temps = 1,
		Results = 1,
		Sizeof = DoubleSize*48,
	}; };

	struct BilateralUserTau1D
	{ enum {
		Temps = 1,
		Results = 1,
		Sizeof = DoubleSize*64,
	}; };

	struct LinearLimits1D
	{ enum {
		Temps = 1,
		Results = 1,
		Sizeof = DoubleSize*64,
	}; };

	struct Friction1D
	{ enum {
		Temps = 2,
		Results = 2,
		Sizeof = DoubleSize*64,
	}; };

	struct LinearMotor1D
	{ enum {
		Temps = 2,
		Results = 2,
		Sizeof = DoubleSize*80,
	}; };

	struct StableBallSocket
	{ enum {
		Temps = 3,
		Results = 3,
		Sizeof = DoubleSize*64,
	}; };

	struct NpStableBallSocket
	{ enum {
		Temps = 3,
		Results = 3,
		Sizeof = StableBallSocket::Sizeof + (4*sizeof(hkVector4)),
	}; };

	struct StableAngular3D
	{ enum {
		Temps = 3,
		Results = 3,
		Sizeof = DoubleSize*48,
	}; };

	struct NpStableAngular3D
	{ enum {
		Temps = 3,
		Results = 3,
		Sizeof = StableAngular3D::Sizeof + (4*sizeof(hkVector4)),
	}; };

	struct Pulley1D
	{ enum {
		Temps = 1,
		Results = 1,
		Sizeof = DoubleSize*64,
	}; };

	struct Angular1D
	{ enum {
		Temps = 1,
		Results = 1,
		Sizeof = DoubleSize*32,
	}; };

	struct AngularLimits1D
	{ enum {
		Temps = 1,
		Results = 1,
		Sizeof = DoubleSize*48,
	}; };

	struct AngularFriction1D
	{ enum {
		Temps = 2,
		Results = 2,
		Sizeof = DoubleSize*48,
	}; };

	struct AngularMotor1D
	{ enum {
		Temps = 2,
		Results = 2,
		Sizeof = DoubleSize*64,
	}; };

	struct SingleContact
	{ enum {
		Temps = 1,
		Sizeof = DoubleSize*48,
	}; };

	struct PairContact
	{ enum {
		Temps = 2,
		Results = 2,
		Sizeof = DoubleSize*112,
	}; };

	struct Friction2D
	{ enum {
		Temps = 3,
		Results = 0,
		Sizeof = DoubleSize*112,
	}; };

	struct Friction3D
	{ enum {
		Temps = 4,
		Results = 0,

		Sizeof_Ptr4 = DoubleSize*144,
		Sizeof_Ptr8 = DoubleSize*160,

	#if HK_POINTER_SIZE == 4
		Sizeof = Sizeof_Ptr4,
	#else
		Sizeof = Sizeof_Ptr8,
	#endif
	}; };

	struct RollingFriction2D
	{ enum {
		Temps = 3,
		Results = 0,

	#if defined(HK_REAL_IS_DOUBLE)
		Sizeof_Ptr4 = DoubleSize*80,
		Sizeof_Ptr8 = DoubleSize*80,
	#else
		Sizeof_Ptr4 = 1*80,
		Sizeof_Ptr8 = 1*96,
	#endif

	#if HK_POINTER_SIZE == 4
		Sizeof = Sizeof_Ptr4,
	#else
		Sizeof = Sizeof_Ptr8,
	#endif
	}; };

	struct SetMass
	{ enum {
		Temps = 0,
		Results = 0,
		Sizeof = DoubleSize*32,
	}; };

	struct AddVelocity
	{ enum {
		Temps = 0,
		Results = 0,
		Sizeof = DoubleSize*32,
	}; };

	struct SetCenterOfMass
	{ enum {
		Temps = 0,
		Results = 0,
		Sizeof = DoubleSize*96,
	}; };

	struct StiffSpringChain
	{ enum {
		Sizeof = 1*32,
	}; };

	struct BallSocketChain
	{ enum {
		Sizeof = 1*32,
	}; };

	struct StabilizedBallSocketChain
	{ enum {
		Sizeof = DoubleSize*32,
	}; };

	struct PoweredChain
	{ enum {
		Sizeof = DoubleSize*32,
	}; };

	struct StableStiffSpring
	{ enum {
		Temps = 1,
		Results = 1,
		Sizeof = DoubleSize*48
	}; };

	struct NpStableStiffSpring
	{ enum {
		Temps = StableStiffSpring::Temps,
		Results = StableStiffSpring::Results,
		Sizeof = StableStiffSpring::Sizeof + (4*sizeof(hkVector4))
	}; };

	struct DeformableLinear3D
	{ enum {
		Temps = 3,
		Results = 3,
		Sizeof = DoubleSize*128
	}; };

	struct NpDeformableLinear3D
	{ enum {
		Temps = DeformableLinear3D::Temps,
		Results = DeformableLinear3D::Results,
		Sizeof = DeformableLinear3D::Sizeof + (4*sizeof(hkVector4))
	}; };

	struct DeformableAngular3D
	{ enum {
		Temps = 3,
		Results = 3,
		Sizeof = DoubleSize*128
	}; };

	struct NpDeformableAngular3D
	{ enum {
		Temps = DeformableAngular3D::Temps,
		Results = DeformableAngular3D::Results,
		Sizeof = DeformableAngular3D::Sizeof + (4*sizeof(hkVector4))
	}; };
}



#define hkpConstraintInfoSpu2 hkpConstraintInfo


/// Contains information about the memory size required for Jacobians (m_sizeOfSchemas) and the number of solver results (m_numSolverResults)
/// and temporal elements (m_numSolverElemTemps) for an associated constraint (hkpConstraintData).

struct hkpConstraintInfo
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_DYNAMICS, hkpConstraintInfo );

		// This variable only has a meaning in an island (it is equal to sizeOfJacobians for constraints).
		
	int m_maxSizeOfSchema;
	int m_sizeOfSchemas;
	int m_numSolverResults;
	int m_numSolverElemTemps;

	inline void clear() { m_maxSizeOfSchema = 0; m_sizeOfSchemas = 0; m_numSolverResults = 0; m_numSolverElemTemps = 0; }
	inline void addHeader() { m_sizeOfSchemas += hkpJacobianSchemaInfo::Header::Sizeof; }
	inline void add( int schemaSize, int numSolverResults, int numSolverTempElems ) { m_sizeOfSchemas += schemaSize; m_numSolverResults += numSolverResults; m_numSolverElemTemps += numSolverTempElems; }
	template <typename T> inline void add() { add( T::Sizeof, T::Results, T::Temps ); }
	template <typename T> inline void addMultiple(int n) { add( n*T::Sizeof, n*T::Results, n*T::Temps ); }

	inline void add( const hkpConstraintInfo& other);
	inline void sub( const hkpConstraintInfo& other);

	inline void merge( const hkpConstraintInfo& other);

#if !defined(hkpConstraintInfoSpu2)
	inline hkpConstraintInfo& operator= (const struct hkpConstraintInfoSpu2& s);
#endif
};


inline void hkpConstraintInfo::merge( const hkpConstraintInfo& delta)
{
	m_maxSizeOfSchema = hkMath::max2( m_maxSizeOfSchema, delta.m_maxSizeOfSchema);
	m_sizeOfSchemas    += delta.m_sizeOfSchemas;
	m_numSolverResults += delta.m_numSolverResults;
	m_numSolverElemTemps += delta.m_numSolverElemTemps;
}


inline void hkpConstraintInfo::add( const hkpConstraintInfo& delta)
{
	//	HK_ASSERT2(0XAD7865543, m_maxSizeOfSchema < 10000 && delta.m_maxSizeOfSchema < 10000 && delta.m_sizeOfSchemas  < 10000, "Warning: Max schema size very (too?) large.");
	m_maxSizeOfSchema = hkMath::max2( m_maxSizeOfSchema, int(delta.m_maxSizeOfSchema));
	m_maxSizeOfSchema = hkMath::max2( m_maxSizeOfSchema, int(delta.m_sizeOfSchemas));
	m_sizeOfSchemas    += delta.m_sizeOfSchemas;
	m_numSolverResults += delta.m_numSolverResults;
	m_numSolverElemTemps += delta.m_numSolverElemTemps;
}

inline void hkpConstraintInfo::sub( const hkpConstraintInfo& delta)
{
	m_sizeOfSchemas    -= delta.m_sizeOfSchemas;
	m_numSolverResults -= delta.m_numSolverResults;
	m_numSolverElemTemps -= delta.m_numSolverElemTemps;
}


#if !defined(hkpConstraintInfoSpu2)
struct hkpConstraintInfoSpu2
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_DYNAMICS, hkpConstraintInfo );

	// This variable only has a meaning in an island (it is equal to sizeOfJacobians for constraints).
	
	hkPadSpu<int> m_maxSizeOfSchema;
	hkPadSpu<int> m_sizeOfSchemas;
	hkPadSpu<int> m_numSolverResults;
	hkPadSpu<int> m_numSolverElemTemps;

	inline void clear() { m_maxSizeOfSchema = 0; m_sizeOfSchemas = 0; m_numSolverResults = 0; m_numSolverElemTemps = 0; }
	inline void addHeader() { m_sizeOfSchemas = m_sizeOfSchemas + hkpJacobianSchemaInfo::Header::Sizeof; }
	inline void add( int schemaSize, int numSolverResults, int numSolverTempElems )
	{
		m_sizeOfSchemas = m_sizeOfSchemas + schemaSize;
		m_numSolverResults = m_numSolverResults + numSolverResults;
		m_numSolverElemTemps = m_numSolverElemTemps + numSolverTempElems;
	}

	inline void add( const hkpConstraintInfo& other);
	inline void sub( const hkpConstraintInfo& other);
};

inline void hkpConstraintInfoSpu2::add( const hkpConstraintInfo& delta)
{
	//	HK_ASSERT2(0XAD7865543, m_maxSizeOfSchema < 10000 && delta.m_maxSizeOfSchema < 10000 && delta.m_sizeOfSchemas  < 10000, "Warning: Max schema size very (too?) large.");
	m_maxSizeOfSchema = hkMath::max2( int(m_maxSizeOfSchema), int(delta.m_maxSizeOfSchema));
	m_maxSizeOfSchema = hkMath::max2( int(m_maxSizeOfSchema), int(delta.m_sizeOfSchemas));
	m_sizeOfSchemas      = m_sizeOfSchemas + delta.m_sizeOfSchemas;
	m_numSolverResults   = m_numSolverResults + delta.m_numSolverResults;
	m_numSolverElemTemps = m_numSolverElemTemps + delta.m_numSolverElemTemps;
}

inline void hkpConstraintInfoSpu2::sub( const hkpConstraintInfo& delta)
{
	m_sizeOfSchemas      = m_sizeOfSchemas - delta.m_sizeOfSchemas;
	m_numSolverResults   = m_numSolverResults - delta.m_numSolverResults;
	m_numSolverElemTemps = m_numSolverElemTemps - delta.m_numSolverElemTemps;
}

inline hkpConstraintInfo& hkpConstraintInfo::operator= (const struct hkpConstraintInfoSpu2& s)
{
	m_maxSizeOfSchema = s.m_maxSizeOfSchema;
	m_sizeOfSchemas = s.m_sizeOfSchemas;
	m_numSolverResults = s.m_numSolverResults;
	m_numSolverElemTemps = s.m_numSolverElemTemps;
	return *this;
}

#endif


#endif // HKP_CONSTRAINT_INFO_H

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
