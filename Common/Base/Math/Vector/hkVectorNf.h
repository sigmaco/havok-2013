/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_MATH_VECTOR_Nf_H
#define HK_MATH_VECTOR_Nf_H

/// A column vector of any size.
class hkVectorNf
{
	friend class hkMatrixfNm;
	public:
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_MATH, hkVectorNf);

		enum
		{
			IS_ALLOCATED = 0x80000000,
		};

			/// Get elements (read only)
		const hkFloat32* getElements() const { return (const hkFloat32*)(m_elements); }
			/// Get elements (read/write)
		hkFloat32* getElements() { return (hkFloat32*)m_elements; }

			/// [] access
		hkFloat32& operator[] (int i) { HK_ASSERT(0x3244aa23, i >= 0 && i < m_size); return ((hkFloat32*)m_elements)[i]; }
			/// []
		const hkFloat32& operator[] (int i) const { HK_ASSERT(0x424234aa, i >= 0 && i < m_size); return ((const hkFloat32*)m_elements)[i]; }
			
			/// Set to a - b
		void setSub(const hkVectorNf& a, const hkVectorNf& b);
			/// Set to a + b
		void setAdd(const hkVectorNf& a, const hkVectorNf& b);

			/// Add rhs to this (must be same size)
		void add(const hkVectorNf& rhs);
			/// Sub rhs from this (must be same size)
		void sub(const hkVectorNf& rhs);

			/// Set to v * s
		void setMul(hkSimdFloat32Parameter s, const hkVectorNf& v);

			/// Multiply by a value
		void mul(hkSimdFloat32Parameter v);

			/// Dot product between this and rhs (must be same size)
		hkSimdFloat32 dot(const hkVectorNf& rhs) const;

			/// Does equality test - all values must be less than threshold
		hkBool equals(const hkVectorNf& rhs, hkFloat32 epsilon = 1e-5f) const;

			/// Tests if equal based on strided input
		hkBool equalsStrided(const hkFloat32* ele, int size, int stride, hkFloat32 epsilon = 1e-5f) const;

			/// Get the length squared
		hkSimdFloat32 lengthSquared() const;
			/// Get the length
		hkSimdFloat32 length() const;
			/// Normalize, returns the original length.
			/// If the length is close to zero, sets to 1,0,0,0...
		hkSimdFloat32 normalize();

			/// Do a horizontal add
		hkSimdFloat32 horizontalAdd() const;

			/// Sets the contents
		void set(const hkFloat32* v, int size);

			/// Sets the size, the contents values are undefined
		HK_FORCE_INLINE void setSize(int size);
			/// Sets the size and zeros the content
		void setSizeAndZero(int size);

			/// Sets all of the content to zero
		void setZero();

			/// Negates in place
		void negate();

			/// Returns true if the vector is ok
		hkBool isOk() const;

			/// Ctor
		hkVectorNf(int size);
			/// Ctor
		hkVectorNf(const hkFloat32* v, int size);
			/// Default Ctor
		hkVectorNf(): m_elements(HK_NULL), m_size(0), m_flags(0) {}

			/// Copy Ctor
		hkVectorNf(const hkVectorNf& rhs);
			/// Assignment
		void operator=(const hkVectorNf& rhs);

			/// Gets the amount of elements
		HK_FORCE_INLINE int getSize() const { return m_size; }

			/// Get the number of vectors
		HK_FORCE_INLINE int getNumVectors() const { return (m_size + 3) >> 2; }
			/// Returns true if its allocated
		HK_FORCE_INLINE hkBool isAllocated() const { return (m_flags & IS_ALLOCATED) != 0; }

			/// Get the elements
		HK_FORCE_INLINE const hkVector4f* getVectors() const { return m_elements; }
			/// Get the elements
		HK_FORCE_INLINE hkVector4f* getVectors() { return m_elements; }

			/// Uses the vecs, as passed in. The memory pointed to by vecs, must stay in scope as log as the vector.
			/// Assumes the end of vecs has been zeroed correctly
		void alias(hkVector4f* vecs, int size);
			/// Stops aliasing (by making an internal copy)
		void unalias();

			/// For the plane defined by the points, a, b, c. This works out 2 unit length perpendicular axies in the plane.
			/// This can be used to work out the squared distance from the plane
		static void HK_CALL calcUnitAxes(const hkVectorNf& a, const hkVectorNf& b, const hkVectorNf& c, hkVectorNf& e1, hkVectorNf& e2);

			/// Works out the squared distance of point p, from a plane described by 2 perpendicular axes in the plane and a point on the plane
		static hkSimdFloat32 HK_CALL calcPlaneDistanceSquared(const hkVectorNf& p, hkVectorNf& e1, hkVectorNf& e2, const hkVectorNf& planePoint);

			/// Dtor
		HK_FORCE_INLINE ~hkVectorNf();

#ifdef HK_DEBUG
		static void HK_CALL selfTest();
#endif

    protected:

		hkVectorNf(hkVector4f* vecs, int size):m_elements(vecs), m_size(size), m_flags(0) {}

		        /// Sets the values (zeros end values if necessary).
		static void _setValues(hkVector4f* dst, const hkFloat32* v, int size);
			/// Set the size
		void _setSize(int size);
		void _setSizeAndZeroLast(int size);

		// For clearing out the end bits
		static const hkVector4ComparisonMask::Mask s_zeroMask[4];


		hkVector4f* m_elements;
		int m_size;
		int m_flags;
};

#include <Common/Base/Math/Vector/hkVectorNf.inl>

// Inplace (ie storage is allocated on stack or object contained in) version of hkVectorNf.
// SIZE is the size of the vector in hkReals.

template <int SIZE>
class hkInplaceVectorNf: public hkVectorNf
{
	public:
		enum { NUM_VECS = (SIZE + 3) >> 2 };

		hkInplaceVectorNf():
			hkVectorNf(m_vecs, SIZE)
		{
			m_vecs[NUM_VECS - 1].setZero();
		}

		hkInplaceVectorNf(hkInplaceVectorNf const& other):
			hkVectorNf(m_vecs, SIZE)
		{
			hkMemUtil::memCpy<HK_FLOAT_ALIGNMENT>(m_vecs, other.m_vecs, sizeof(hkVector4f)/4*SIZE);
		}
		
		~hkInplaceVectorNf() { HK_ASSERT(0x6dadaa2d, !wasReallocated() ); }

			/// Returne
		HK_FORCE_INLINE bool wasReallocated() const 
		{
			return m_elements != m_vecs;
		}
	protected:
		hkVector4f m_vecs[NUM_VECS];
};

#endif //HK_MATH_VECTOR_Nf_H

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
