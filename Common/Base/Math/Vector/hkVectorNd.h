/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_MATH_VECTOR_Nd_H
#define HK_MATH_VECTOR_Nd_H

/// A column vector of any size.
class hkVectorNd
{
	friend class hkMatrixdNm;
	public:
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_MATH, hkVectorNd);

		enum
		{
			IS_ALLOCATED = 0x80000000,
		};

			/// Get elements (read only)
		const hkDouble64* getElements() const { return (const hkDouble64*)(m_elements); }
			/// Get elements (read/write)
		hkDouble64* getElements() { return (hkDouble64*)m_elements; }

			/// [] access
		hkDouble64& operator[] (int i) { HK_ASSERT(0x3244aa23, i >= 0 && i < m_size); return ((hkDouble64*)m_elements)[i]; }
			/// []
		const hkDouble64& operator[] (int i) const { HK_ASSERT(0x424234aa, i >= 0 && i < m_size); return ((const hkDouble64*)m_elements)[i]; }
			
			/// Set to a - b
		void setSub(const hkVectorNd& a, const hkVectorNd& b);
			/// Set to a + b
		void setAdd(const hkVectorNd& a, const hkVectorNd& b);

			/// Add rhs to this (must be same size)
		void add(const hkVectorNd& rhs);
			/// Sub rhs from this (must be same size)
		void sub(const hkVectorNd& rhs);

			/// Set to v * s
		void setMul(hkSimdDouble64Parameter s, const hkVectorNd& v);

			/// Multiply by a value
		void mul(hkSimdDouble64Parameter v);

			/// Dot product between this and rhs (must be same size)
		hkSimdDouble64 dot(const hkVectorNd& rhs) const;

			/// Does equality test - all values must be less than threshold
		hkBool equals(const hkVectorNd& rhs, hkDouble64 epsilon = 1e-5f) const;

			/// Tests if equal based on strided input
		hkBool equalsStrided(const hkDouble64* ele, int size, int stride, hkDouble64 epsilon = 1e-5f) const;

			/// Get the length squared
		hkSimdDouble64 lengthSquared() const;
			/// Get the length
		hkSimdDouble64 length() const;
			/// Normalize, returns the original length.
			/// If the length is close to zero, sets to 1,0,0,0...
		hkSimdDouble64 normalize();

			/// Do a horizontal add
		hkSimdDouble64 horizontalAdd() const;

			/// Sets the contents
		void set(const hkDouble64* v, int size);

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
		hkVectorNd(int size);
			/// Ctor
		hkVectorNd(const hkDouble64* v, int size);
			/// Default Ctor
		hkVectorNd(): m_elements(HK_NULL), m_size(0), m_flags(0) {}

			/// Copy Ctor
		hkVectorNd(const hkVectorNd& rhs);
			/// Assignment
		void operator=(const hkVectorNd& rhs);

			/// Gets the amount of elements
		HK_FORCE_INLINE int getSize() const { return m_size; }

			/// Get the number of vectors
		HK_FORCE_INLINE int getNumVectors() const { return (m_size + 3) >> 2; }
			/// Returns true if its allocated
		HK_FORCE_INLINE hkBool isAllocated() const { return (m_flags & IS_ALLOCATED) != 0; }

			/// Get the elements
		HK_FORCE_INLINE const hkVector4d* getVectors() const { return m_elements; }
			/// Get the elements
		HK_FORCE_INLINE hkVector4d* getVectors() { return m_elements; }

			/// Uses the vecs, as passed in. The memory pointed to by vecs, must stay in scope as log as the vector.
			/// Assumes the end of vecs has been zeroed correctly
		void alias(hkVector4d* vecs, int size);
			/// Stops aliasing (by making an internal copy)
		void unalias();

			/// For the plane defined by the points, a, b, c. This works out 2 unit length perpendicular axies in the plane.
			/// This can be used to work out the squared distance from the plane
		static void HK_CALL calcUnitAxes(const hkVectorNd& a, const hkVectorNd& b, const hkVectorNd& c, hkVectorNd& e1, hkVectorNd& e2);

			/// Works out the squared distance of point p, from a plane described by 2 perpendicular axes in the plane and a point on the plane
		static hkSimdDouble64 HK_CALL calcPlaneDistanceSquared(const hkVectorNd& p, hkVectorNd& e1, hkVectorNd& e2, const hkVectorNd& planePoint);

			/// Dtor
		HK_FORCE_INLINE ~hkVectorNd();

#ifdef HK_DEBUG
		static void HK_CALL selfTest();
#endif

    protected:

		hkVectorNd(hkVector4d* vecs, int size):m_elements(vecs), m_size(size), m_flags(0) {}

		        /// Sets the values (zeros end values if necessary).
		static void _setValues(hkVector4d* dst, const hkDouble64* v, int size);
			/// Set the size
		void _setSize(int size);
		void _setSizeAndZeroLast(int size);

		// For clearing out the end bits
		static const hkVector4dComparison::Mask s_zeroMask[4];


		hkVector4d* m_elements;
		int m_size;
		int m_flags;
};

#include <Common/Base/Math/Vector/hkVectorNd.inl>

// Inplace (ie storage is allocated on stack or object contained in) version of hkVectorNd.
// SIZE is the size of the vector in hkReals.

template <int SIZE>
class hkInplaceVectorNd: public hkVectorNd
{
	public:
		enum { NUM_VECS = (SIZE + 3) >> 2 };

		hkInplaceVectorNd():
			hkVectorNd(m_vecs, SIZE)
		{
			m_vecs[NUM_VECS - 1].setZero();
		}

		hkInplaceVectorNd(hkInplaceVectorNd const& other):
			hkVectorNd(m_vecs, SIZE)
		{
			hkMemUtil::memCpy<HK_DOUBLE_ALIGNMENT>(m_vecs, other.m_vecs, sizeof(hkVector4d)/4*SIZE);
		}
		
		~hkInplaceVectorNd() { HK_ASSERT(0x6dadaa2d, !wasReallocated() ); }

			/// Returne
		HK_FORCE_INLINE bool wasReallocated() const 
		{
			return m_elements != m_vecs;
		}
	protected:
		hkVector4d m_vecs[NUM_VECS];
};

#endif //HK_MATH_VECTOR_Nd_H

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
